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

  int mid = (low + high) / 2;

  if (mid < high && vec[mid] > vec[mid + 1])
  {
    return mid;
  }
  else if (mid > low && vec[mid] < vec[mid - 1])
  {
    return mid - 1;
  }
  else if (vec[mid] <= vec[low])
  {
    return getPivot(vec, low, mid - 1);
  }
  else
  {
    return getPivot(vec, mid + 1, high);
  }
}

int rotatedBinarySearch(vector<int> &vec, int x, int low, int high)
{
  int pivot = getPivot(vec, low, high);

  if (pivot == -1)
  {
    return BinarySearchRec(vec, x, low, high);
  }
  else if (vec[pivot] == x)
  {
    return pivot;
  }
  else if (vec[low] <= x)
  {
    return BinarySearchRec(vec, x, low, pivot - 1);
  }
  else
  {
    return BinarySearchRec(vec, x, pivot + 1, high);
  }
}

int dublicated(vector<int> &vec, int x, int low, int high)
{
  if (low > high)
  {
    return -1;
  }
  else if (low == high)
  {
    return low;
  }

  int mid = (low + high) / 2;

  if (vec[mid] == x)
  {
    return mid;
  }
  else if (vec[mid] == vec[low])
  {
    while (vec[mid] == vec[low])
    {
      low++;
    }
    return dublicated(vec, x, low, high);
  }
  else if (vec[mid] == vec[high])
  {
    while (vec[mid] == vec[high])
    {
      high--;
    }
    return dublicated(vec, x, low, high);
  }
  else
  {
    return rotatedBinarySearch(vec, x, low, high);
  }
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
      if (n != 0)
      {
        getNumbers(inFile, splited, line, vec);
        outFile << BinarySearchRec(vec, x, 0, n - 1) << endl;
      }
      else
      {
        outFile << -1 << endl;
      }

      break;
    case ROTATED_ARRAY:
      if (!(iss >> x >> n))
      {
        cerr << "ROTATED_ARRAY: invalid input" << endl;
        exit(1);
      }
      if (n != 0)
      {
        getNumbers(inFile, splited, line, vec);
        outFile << rotatedBinarySearch(vec, x, 0, n - 1) << endl;
      }
      else
      {
        outFile << -1 << endl;
      }

      break;
    case DUPLICATES:
      if (!(iss >> x >> n))
      {
        cerr << "DUPLICATES: invalid input" << endl;
        exit(1);
      }
      if (n != 0)
      {
        getNumbers(inFile, splited, line, vec);
        outFile << dublicated(vec, x, 0, n - 1) << endl;
      }
      else
      {
        outFile << -1 << endl;
      }

      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
