#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>
#include <list>
#include <stack>

using namespace std;

const char CONSTRUCT = 'C';
const char BFS = 'B';
const char DFS = 'D';

class Graph
{
  int nVertices;
  vector<list<int>> adj;

public:
  Graph(){};
  void setVertical(int);
  void addEdge(vector<tuple<int, int, int>> &);
  void bfs(int s, ofstream &);
  void dfs(int s, ofstream &);
};

void Graph::setVertical(int nVertices)
{
  this->nVertices = nVertices;
  adj.resize(nVertices);
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
    adj[u].push_back(v);
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
    queue.pop_front();

    for (auto adjecent : adj[s])
    {
      if (!visited[adjecent])
      {
        visited[adjecent] = true;
        queue.push_back(adjecent);
      }
    }
  }
  outFile << endl;
}

void Graph::dfs(int s, ofstream &outFile)
{
  vector<bool> visited(nVertices, false);

  stack<int> stack;

  stack.push(s);

  while (!stack.empty())
  {
    int s = stack.top();
    stack.pop();

    if (!visited[s])
    {
      outFile << s << " ";
      visited[s] = true;
    }

    for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
      if (!visited[*i])
        stack.push(*i);
  }
  outFile << endl;
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
