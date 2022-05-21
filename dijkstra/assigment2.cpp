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
};

void Graph::setVertical(int nVertices)
{
    this->nVertices = nVertices;
    adj.resize(nVertices, vector<int>(nVertices, -1));
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

void Graph::dijkstra(int s, int e)
{
    priority_queue<pair<string, int>, vector<pair<string, int>>, shortest> pq;

    // for (auto i = 0; i < adj.size(); i++)
    // {
    //     for (int j = 0; j < adj[i].size(); j++)
    //     {
    //         cout << adj[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // vector<bool> visited;
    // visited.resize(nVertices, false);
    // list<int> queue;

    // visited[s] = true;
    // queue.push_back(s);

    // while (!queue.empty())
    // {
    //     s = queue.front();
    //     cout << s << " ";
    //     queue.pop_front();

    //     for (auto adjecent : adj[s])
    //     {
    //         if (!visited[adjecent])
    //         {
    //             visited[adjecent] = true;
    //             queue.push_back(adjecent);
    //         }
    //     }
    // }
    // cout << endl;

    // for (int i = 0; i < nVertices; i++)
    // {
    //     for (int j = 0; i < nVertices; j++)
    //     {
    //         vector<bool> visited;
    //         visited.resize(nVertices, false);
    //         list<int> queue;

    //         visited[s] = true;
    //         queue.push_back(s);
    //         s = queue.front();
    //         cout << s << " ";
    //         queue.pop_front();
    //         for (int l = 0; l < nVertices; l++)
    //         {
    //         }
    //     }
    //     cout << endl;
    // }
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
