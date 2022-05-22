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
};

void Graph::setVertical(int nVertices)
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
        adj[u].push_back(make_pair(v, wgt));
    }
}

void Graph::dijkstra(int s, int e, ofstream &outFile)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, shortest> pq;

    vector<int> dist(nVertices, 999999999);

    pq.push(make_pair(0, s));
    dist[s] = 0;

    vector<bool> visited;
    visited.resize(nVertices, false);
    string path = to_string(s);
    visited[s] = true;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int wei = adj[u][i].second;

            if (dist[v] > dist[u] + wei && v <= e)
            {
                if (!visited[u])
                {
                    visited[u] = true;
                    path = path + " " + to_string(u);
                }
                dist[v] = dist[u] + wei;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    path = path + " " + to_string(e);

    outFile << path << endl;
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
