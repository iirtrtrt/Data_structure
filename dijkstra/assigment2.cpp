#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <map>
#include <list>
#include <cassert>
#include <vector>

using namespace std;

const char CONSTRUCT = 'C';
const char DIJKSTRA = 'S';

struct shortest
{
    bool operator()(pair<string, int> const &a, pair<string, int> const &b)
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
    vector<vector<int>> adj;

public:
    void setVertical(int);
    void addEdge(vector<tuple<int, int, int>> &);
    void dijkstra(int, int);
    int minDistance(int[], bool[]);
    void printSolution(int[], int);
};

void Graph::setVertical(int nVertices)
{
    this->nVertices = nVertices;
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
    int min = 999999999;
    int min_index;

    for (int v = 0; v < nVertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void Graph::printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < nVertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void Graph::dijkstra(int s, int e)
{
    priority_queue<pair<string, int>, vector<pair<string, int>>, shortest> pq;

    int dist[nVertices]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[nVertices]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < nVertices; i++)
        dist[i] = 999999999, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[s] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < nVertices - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);
        cout << "What is u : " << u << endl;
        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < nVertices; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && adj[u][v] && dist[u] != 999999999 && dist[u] + adj[u][v] < dist[v])
                dist[v] = dist[u] + adj[u][v];
    }
    printSolution(dist, nVertices);
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
            g.dijkstra(s, e);
            break;
        default:
            cerr << "Undefined operator" << endl;
            exit(1);
        }
    }
    outFile.close();
    inFile.close();
}
