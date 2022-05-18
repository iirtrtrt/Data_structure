#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

const char CONSTRUCT = 'C';
const char IS_ADJACENT = 'I';
const char GET_NEIGHBORS = 'N';

class Graph
{
public:
  int nVertices;
  int nEdges;
  pair<int, int> **neighbors;
  int *nNeighbors;

  Graph();
  ~Graph();
  void build(int, int, vector<tuple<int, int, int>> &);
  bool isAdjacent(int, int);
  vector<int> getNeighbors(int);
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
  }
}

bool Graph::isAdjacent(int u, int v)
{
  assert(u >= 0 && u < nVertices);
  assert(v >= 0 && v < nVertices);
  for (int i = 0; i < nNeighbors[u]; ++i)
  {
    if (neighbors[u][i].first == v)
    {
      return 1;
    }
  }
  return 0;
}

vector<int> Graph::getNeighbors(int u)
{
  assert(u >= 0 && u < nVertices);
  vector<int> nbrs(nNeighbors[u]);
  for (int i = 0; i < nNeighbors[u]; ++i)
  {
    nbrs[i] = neighbors[u][i].first;
  }
  return nbrs;
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
    int u, v, wgt, nVertices, nEdges, cnt;
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
    case IS_ADJACENT:
      if (!(iss >> u >> v))
      {
        cerr << "isAdjacent: invalid input" << endl;
        exit(1);
      }
      outFile << u << " " << v << " " << (g.isAdjacent(u, v) ? "T" : "F") << endl;
      break;
    case GET_NEIGHBORS:
      if (!(iss >> u))
      {
        cerr << "getNeighbors: invalid input" << endl;
        exit(1);
      }
      nbrs = g.getNeighbors(u);
      for (auto i = nbrs.begin(); i != nbrs.end(); ++i)
      {
        if (i != nbrs.begin())
        {
          outFile << " ";
        }
        outFile << *i;
      }
      outFile << endl;
      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
