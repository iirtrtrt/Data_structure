// Practice 12. Use hash tables
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;
const char BINARY_SEARCH = 'B';
const char ROTATED_ARRAY = 'R';
const char DUPLICATES = 'D';

void getNumbers(ifstream &inFile, string &splited, string &line, vector<int> &vec)
{
  if (getline(inFile, line))
  {
    istringstream eiss(line);
    while (getline(eiss, splited, ' '))
    {
      vec.push_back(stoi(splited));
    }
  }
}

int BinarySearchRec(vector<int> &vec, int x, int low, int high)
{
  if (low > high)
  {
    return -1;
  }
  else
  {
    int mid = (low + high) / 2;

    if (x == vec[mid])
    {
      return mid;
    }
    else if (x < vec[mid])
    {
      return BinarySearchRec(vec, x, low, mid - 1);
    }
    else
    {
      return BinarySearchRec(vec, x, mid + 1, high);
    }
  }
}

int getPivot(vector<int> &vec, int low, int high)
{
  if (low > high)
  {
    return -1;
  }
  else if (low == high)
  {
    return low;
  }
  else
  {
    int mid = (low + high) / 2;

    if (mid < high && vec[mid] > vec[mid + 1])
    {
      return mid;
    }

    if (mid > low && vec[mid] < vec[mid - 1])
    {
      return mid - 1;
    }

    if (vec[low] >= vec[mid])
    {
      return getPivot(vec, low, mid - 1);
    }

    return getPivot(vec, mid + 1, high);
  }
}

int rotatedBinarySearch(vector<int> &vec, int x)
{
  int pivot = getPivot(vec, 0, vec.size() - 1);

  if (pivot == -1)
  {
    return BinarySearchRec(vec, x, 0, vec.size() - 1);
  }

  if (vec[pivot] == x)
  {
    return pivot;
  }

  if (vec[0] <= x)
  {
    return BinarySearchRec(vec, x, 0, pivot - 1);
  }

  return BinarySearchRec(vec, x, pivot + 1, vec.size() - 1);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cerr << "Correct usage: [program] [input] [output]" << endl;
    exit(1);
  }
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  string splited;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<int> vec;
    int x, n;
    switch (op)
    {
    case BINARY_SEARCH:
      if (!(iss >> x >> n))
      {
        cerr << "BINARY_SEARCH: invalid input" << endl;
        exit(1);
      }
      getNumbers(inFile, splited, line, vec);
      outFile << BinarySearchRec(vec, x, 0, n - 1) << endl;

      break;
    case ROTATED_ARRAY:
      if (!(iss >> x >> n))
      {
        cerr << "ROTATED_ARRAY: invalid input" << endl;
        exit(1);
      }
      getNumbers(inFile, splited, line, vec);
      cout << rotatedBinarySearch(vec, x) << endl;

      break;
    case DUPLICATES:
      if (!(iss >> x >> n))
      {
        cerr << "DUPLICATES: invalid input" << endl;
        exit(1);
      }
      getNumbers(inFile, splited, line, vec);
      // cout << BinarySearchRec(vec, x, 0, n - 1);

      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
