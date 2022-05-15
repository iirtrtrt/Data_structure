#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>
#include <list>
#include <map>

using namespace std;

const char CONSTRUCT = 'C';
const char BFS = 'B';
const char DFS = 'D';

class Graph
{
public:
  int nVertices;
  int nEdges;
  pair<int, int> **neighbors;
  int *nNeighbors;

  map<int, bool> visited;
  map<int, list<int>> adj;

  Graph();
  ~Graph();
  void build(int, int, vector<tuple<int, int, int>> &);
  void bfs(int, ofstream &);
  void dfs(int, ofstream &);
  void addEdge(int v, int w);
};

Graph::Graph()
{
  neighbors = nullptr;
  nNeighbors = nullptr;
}

Graph::~Graph()
{
  if (neighbors != nullptr)
  {
    for (int i = 0; i < nVertices; ++i)
    {
      if (neighbors[i] != nullptr)
      {
        delete neighbors[i];
      }
    }
    neighbors = nullptr;
  }

  if (nNeighbors != nullptr)
  {
    delete nNeighbors;
    nNeighbors = nullptr;
  }
}

void Graph::build(int n, int m, vector<tuple<int, int, int>> &data)
{
  int u;
  int v;
  int wgt;
  nVertices = n;
  nEdges = m;
  nNeighbors = new int[n]();
  for (auto i = data.begin(); i != data.end(); ++i)
  {
    tie(u, v, wgt) = *i;
    assert(u >= 0 && u < nVertices);
    assert(v >= 0 && v < nVertices);
    ++nNeighbors[u];
    adj[u].push_back(v);
  }

  neighbors = new pair<int, int> *[nVertices];
  for (int i = 0; i < nVertices; ++i)
  {
    if (nNeighbors[i] > 0)
    {
      neighbors[i] = new pair<int, int>[nNeighbors[i]];
    }
    else
    {
      neighbors[i] = nullptr;
    }
  }

  memset(nNeighbors, 0, sizeof(int) * nVertices);
  for (auto i = data.begin(); i != data.end(); ++i)
  {
    tie(u, v, wgt) = *i;
    neighbors[u][nNeighbors[u]++] = make_pair(v, wgt);
    cout << *neighbors[u][nNeighbors[u]]->first << endl;
  }
}

void Graph::bfs(int s, ofstream &outFile)
{
  vector<bool> visited;
  visited.resize(nVertices, false);

  list<int> queue;

  visited[s] = true;
  queue.push_back(s);

  while (!queue.empty())
  {
    s = queue.front();
    outFile << s << " ";
    cout << s << " ";
    queue.pop_front();

    for (int i = 0; i < 4; i++)
    {
      if (!visited[neighbors[i]->second])
      {
        visited[neighbors[i]->second] = true;
        queue.push_back(neighbors[i]->second);
      }
    }
  }
  outFile << endl;
  cout << endl;
}

void Graph::dfs(int s, ofstream &outFile)
{
  // Mark the current node as visited and
  // print it
  visited[s] = true;
  cout << s << " ";

  // Recur for all the vertices adjacent
  // to this vertex
  list<int>::iterator i;
  for (i = adj[s].begin(); i != adj[s].end(); ++i)
    if (!visited[*i])
    {
      // cout << *i << endl;
      dfs(*i, outFile);
    }
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
    int u, v, wgt, nVertices, nEdges, cnt, s;
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
      g.build(nVertices, nEdges, data);
      break;
    case BFS:
      if (!(iss >> s))
      {
        cerr << "BFS: invalid input" << endl;
        exit(1);
      }
      g.bfs(s, outFile);
      break;
    case DFS:
      if (!(iss >> s))
      {
        cerr << "DFS: invalid input" << endl;
        exit(1);
      }
      g.dfs(s, outFile);
      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
