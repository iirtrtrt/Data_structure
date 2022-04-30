// Practice 7. Heaps
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>

using namespace std;

struct Heap
{
  int *array;
  int count;
  int capacity;
  Heap(int);
  // ~Heap();
  // int Parent(int);
  // int Left(int);
  // int Right(int);
  // int Maximum(Heap &);
  // void Insert(Heap &, int);
  // void MaxHeapify(Heap &, int);
  // int DeletingMax(Heap &);
  // void Heapsort(int[], int);
  // void BuildMaxHeap(Heap &, int[], int);
};
Heap::Heap(int cap)
{
  count = 0;
  capacity = cap;
  array = new int[cap];
}

// Heap::~Heap()
// {
//   // delete array[cap];
// }

int Parent(int i)
{
  return (i - 1) / 2;
}

int Left(int i)
{
  return 2 * i + 1;
}

int Right(int i)
{
  return 2 * i + 2;
}

int Maximum(Heap &h)
{
  if (h.count == 0)
  {
    cerr << "no elements" << endl;
    exit(1);
  }
  return h.array[0];
}

void Insert(Heap &h, int key)
{
  int i = h.count;
  int p = Parent(i);
  while (i > 0 and h.array[p] < key)
  {
    h.array[i] = h.array[p];
    i = p;
    p = Parent(i);
  }
  h.array[i] = key;
  h.count++;
}

void MaxHeapify(Heap &h, int i)
{
  int l = Left(i);
  int r = Right(i);
  int largest;
  int temp;

  if (i != -1 && h.array[1] > h.array[i])
  {
    largest = 1;
  }
  else
  {
    largest = i;
  }

  if (r != -1 && h.array[r] > h.array[largest])
  {
    largest = r;
  }

  if (largest != i)
  {
    temp = h.array[i];
    h.array[i] = h.array[largest];
    h.array[largest] = temp;
    MaxHeapify(h, largest);
  }
}

int DeletingMax(Heap &h)
{
  if (h.count == 0)
  {
    cerr << "heap underflow" << endl;
    exit(1);
  }
  int largest = h.array[0];
  h.array[0] = h.array[h.count - 1];
  h.count--;
  MaxHeapify(h, 0);
  return largest;
}

void BuildMaxHeap(Heap &h, int A[], int n)
{
  for (int i = 0; i < n; i++)
  {
    h.array[i] = A[i];
  }

  h.count = n;
  for (int i = (n - 1) / 2; i >= 0; i--)
  {
    MaxHeapify(h, i);
  }
}

void Heapsort(int A[], int n)
{
  Heap h(n);
  BuildMaxHeap(h, A, n);
  int oldSize = h.count;
  for (int i = n - 1; i > 0; i--)
  {
    int temp = h.array[0];
    h.array[0] = h.array[h.count - 1];
    h.array[0] = temp;
    h.count--;
    MaxHeapify(h, 0);
  }

  h.count = oldSize;
}

struct byValue
{
  constexpr bool operator()(
      pair<string, int> const &a,
      pair<string, int> const &b)
      const noexcept
  {
    return a.second < b.second;
  }
};

bool pqKeyExists(const priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> &pq, string s)
{
  priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> temp = pq;
  while (!temp.empty())
  {
    if (temp.top().first == s)
    {
      return 1;
    }
    temp.pop();
  }
  return 0;
}

void myFucntion(vector<pair<string, int>> v, int k)
{
  map<string, int> m;
  priority_queue<pair<string, int>, vector<pair<string, int>>, byValue> pq;
  for (int i = 0; i < v.size(); i++)
  {
    for (int j = i; j < v.size(); j++)
    {
      if (v[i].first != v[j].first and v[i].second == v[j].second)
      {
        // if (pqKeyExists(pq, v[i].first + " " + v[j].first))
        // {
        //   m[v[i].first + " " + v[j].first]++;
        // }
        // else
        // {
        //   m.insert(pair<string, int>(v[i].first + " " + v[j].first, 1));
        // }
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

  // for (auto i = m.begin(); i != m.end(); i++)
  // {
  //   cout << i->first << " " << i->second << endl;
  // }

  while (!pq.empty())
  {
    cout << pq.top().first
         << " " << pq.top().second
         << endl;
    pq.pop();
  }
  cout << endl;
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
  myFucntion(history, k);
  // priority_queue<vector<pair<string, int>>, int, myFucntion> pq;

  outFile.close();
  inFile.close();
}
