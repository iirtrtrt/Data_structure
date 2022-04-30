// Practice 7. Heaps
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <map>

using namespace std;

struct byValue
{
  bool operator()(pair<string, int> const &a, pair<string, int> const &b)
  {
    if (a.second == b.second)
    {
      return a.first > b.first;
    }
    return a.second < b.second;
  }
};

priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> myFucntion(vector<pair<string, int>> v, int k)
{
  map<string, int> m;
  priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> pq;
  for (int i = 0; i < v.size(); i++)
  {
    for (int j = i; j < v.size(); j++)
    {
      if (v[i].first != v[j].first and v[i].second == v[j].second)
      {
        if (m.count(v[i].first + " " + v[j].first))
        {
          m[v[i].first + " " + v[j].first]++;
        }
        else
        {
          m.insert(pair<string, int>(v[i].first + " " + v[j].first, 1));
        }
      }
    }
  }

  for (auto i = m.begin(); i != m.end(); i++)
  {
    pq.push(make_pair(i->first, i->second));
  }

  return pq;
}

void write(priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> &pq, int k, ofstream &outFile)
{
  for (int i = 0; i < k; i++)
  {
    outFile << pq.top().first << endl;
    pq.pop();
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cerr << "Correct usage: [exe] [input] [output]" << endl;
    exit(1);
  }
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line, website;
  int k, user;
  vector<pair<string, int>> history;
  if (getline(inFile, line))
  {
    istringstream iss(line);
    if (!(iss >> k))
    {
      cerr << "Error: invalid input" << endl;
    }
  }
  while (getline(inFile, line))
  {
    istringstream iss(line);
    if (!(iss >> website >> user))
    {
      cerr << "Error: invalid input" << endl;
    }
    else
    {
      history.push_back(make_pair(website, user));
    }
  }
  // TODO. Call your function with arguments "history" and "k",
  // and write the result into "outFile"
  priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> pq = myFucntion(history, k);
  write(pq, k, outFile);

  outFile.close();
  inFile.close();
}
