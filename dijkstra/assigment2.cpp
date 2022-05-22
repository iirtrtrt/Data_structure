#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <map>
#include <cassert>
#include <vector>

using namespace std;

const char CONSTRUCT = 'C';
const char DIJKSTRA = 'S';

struct shortest // To sort the priority queue (greater)
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
    vector<vector<pair<int, int>>> adj;

public:
    void setVertical(int);
    void addEdge(vector<tuple<int, int, int>> &);
    void dijkstra(int, int, ofstream &);
    void routeOut(vector<int> &, int, ofstream &);
};

void Graph::setVertical(int nVertices) // Makes a vector iwth input size
{
    this->nVertices = nVertices;
    adj.resize(nVertices, vector<pair<int, int>>(nVertices));
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
        adj[u].push_back(make_pair(v, wgt)); // Stores 'u' for index, 'v' for pair.first, and 'wgt' for pair.second
    }
}

void Graph::dijkstra(int s, int e, ofstream &outFile)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, shortest> pq;

    vector<int> dist(nVertices, 999999999); // Sets maximum distances, 999999999

    pq.push(make_pair(-1, s));
    dist[s] = 0; // The distance of the route is saved

    vector<bool> visited;             // To list a visited points
    visited.resize(nVertices, false); // Makes all elements false
    visited[s] = true;                // Starting point is visited
    vector<int> route;                // Lists the shortest route (the element is for going to its index)
    route.resize(nVertices, -1);

    while (!pq.empty()) // Till this queue is empty checks the 'u'
    {
        int u = pq.top().second;
        pq.pop();
        visited[u] = true; // Make it true if the point, u, is visited
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int wgt = adj[u][i].second;
            if (!visited[v] && dist[v] > dist[u] + wgt) // At unvisited place, changes the distance, if it found shorter distance
            {
                route[v] = u;
                dist[v] = dist[u] + wgt;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    routeOut(route, e, outFile);
}

void Graph::routeOut(vector<int> &route, int i, ofstream &outFile)
{
    if (route[i] == -1) // Prints the start point and stop this function
    {
        outFile << i;
        return;
    }
    routeOut(route, route[i], outFile); // Prints the index and go to the elements
    outFile << " " << i;
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
