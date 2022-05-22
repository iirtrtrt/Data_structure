#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <map>
#include <list>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

const char CONSTRUCT = 'C';
const char DIJKSTRA = 'S';

struct shortest
{
    bool operator()(pair<int, int> const &a, pair<int, int> const &b)
    {
        if (a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second > b.second;
    }
};

class Graph
{
    int nVertices;
    // vector<vector<pair<int, int>>> adj;
    vector<vector<int>> adj;

public:
    void setVertical(int);
    void addEdge(vector<tuple<int, int, int>> &);
    void dijkstra(int, int, ofstream &);
    int minDistance(int[], bool[]);
    void printPath(int[], int);
    void printSolution(int[], int, int[]);
};

void Graph::setVertical(int nVertices)
{
    this->nVertices = nVertices;
    // adj.resize(nVertices, vector<pair<int, int>>(nVertices));
    adj.resize(nVertices, vector<int>(nVertices, 0));
}

void Graph::addEdge(vector<tuple<int, int, int>> &data)
{
    int u;
    int v;
    int wgt;

    for (auto i = data.begin(); i != data.end(); ++i)
    {
        tie(u, v, wgt) = *i;
        assert(u >= 0 && u < nVertices);
        assert(v >= 0 && v < nVertices);
        adj[u][v] = wgt;
    }
}

int Graph::minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = 99999999, min_index;
    for (int i = 0; i < nVertices; i++)
        if (sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

// Function to print shortest path from source to j using
// parent array
void Graph::printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << j << " ";
}

// A utility function to print the constructed distance
// array
void Graph::printSolution(int dist[], int n, int parent[])
{
    int src = 0;
    cout << "Vertex\t Distance\tPath";
    for (int i = 1; i < nVertices; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i],
               src);
        printPath(parent, i);
    }
}

void Graph::dijkstra(int s, int e, ofstream &outFile)
{
    int dist[nVertices];

    // sptSet[i] will true if vertex i is included / in
    // shortest path tree or shortest distance from src to i
    // is finalized
    bool sptSet[nVertices] = {false};

    // Parent array to store shortest path tree
    int parent[nVertices] = {-1};

    // Initialize all distances as INFINITE
    for (int i = 0; i < nVertices; i++)
        dist[i] = 99999999;

    // Distance of source vertex from itself is always 0
    dist[s] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < nVertices - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        cout << u << endl;
        sptSet[u] = true;
        for (int v = 0; v < nVertices; v++)
            if (!sptSet[v] && adj[u][v] && dist[u] + adj[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + adj[u][v];
            }
    }
    printSolution(dist, nVertices, parent);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Correct usage: [exe] [input] [output]" << endl;
        exit(1);
    }
    Graph g;
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    string line;
    while (getline(inFile, line))
    {
        char op = line[0];
        istringstream iss(line.substr(1));
        int u, v, wgt, nVertices, nEdges, cnt, s, e;
        vector<tuple<int, int, int>> data;
        vector<int> p, nbrs;
        switch (op)
        {
        case CONSTRUCT:
            if (!(iss >> nVertices >> nEdges))
            {
                cerr << "CONSTRUCT: invalid input" << endl;
                exit(1);
            }
            g.setVertical(nVertices);

            cnt = nEdges;
            while (cnt)
            {
                if (!getline(inFile, line))
                {
                    cerr << "CONSTRUCT: invalid input" << endl;
                    exit(1);
                }
                istringstream eiss(line);
                if (!(eiss >> u >> v >> wgt))
                {
                    cerr << "CONSTRUCT: invalid input" << endl;
                    exit(1);
                }
                data.push_back(make_tuple(u, v, wgt));
                --cnt;
            }
            g.addEdge(data);
            break;
        case DIJKSTRA:
            if (!(iss >> s >> e))
            {
                cerr << "DIJKSTRA: invalid input" << endl;
                exit(1);
            }
            g.dijkstra(s, e, outFile);
            break;
        default:
            cerr << "Undefined operator" << endl;
            exit(1);
        }
    }
    outFile.close();
    inFile.close();
}
