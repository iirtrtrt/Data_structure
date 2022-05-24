#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const char MERGE = 'M';
const char QUICK = 'Q';

void merge(vector<int> &v, int s, int m, int e)
{
  vector<int> temp;

  int i, j;
  i = s;
  j = m + 1;

  while (i <= m && j <= e)
  {

    if (v[i] <= v[j])
    {
      temp.push_back(v[i]);
      ++i;
    }
    else
    {
      temp.push_back(v[j]);
      ++j;
    }
  }

  while (i <= m)
  {
    temp.push_back(v[i]);
    ++i;
  }

  while (j <= e)
  {
    temp.push_back(v[j]);
    ++j;
  }

  for (int i = s; i <= e; ++i)
    v[i] = temp[i - s];
}

void mergeSort(vector<int> &v, int s, int e)
{
  if (s < e)
  {
    int m = (s + e) / 2;
    mergeSort(v, s, m);
    mergeSort(v, m + 1, e);
    merge(v, s, m, e);
  }
}

int paritition(vector<int> &v, int left, int right)
{

  int pivot = v[left];
  int low = left + 1;
  int high = right;

  while (low <= high)
  {
    while (low <= right && pivot >= v[low])
    {
      low++;
    }
    while (high >= (left + 1) && pivot <= v[high])
    {
      high--;
    }
    if (low <= high)
    {

      int temp = v[low];
      v[low] = v[high];
      v[high] = temp;
    }
  }

  int temp = v[left];
  v[left] = v[high];
  v[high] = temp;

  return high;
}

void quickSort(vector<int> &v, int left, int right)
{
  if (left < right)
  {
    int q = paritition(v, left, right);
    quickSort(v, left, q - 1);
    quickSort(v, q + 1, right);
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
  string line;
  string stringBuffer;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int s, cnt, val;
    vector<int> vec;

    switch (op)
    {
    case MERGE:
      if (!(iss >> s))
      {
        cerr << "MERGE: invalid input" << endl;
        exit(1);
      }

      if (getline(inFile, line))
      {
        istringstream eiss(line);
        while (getline(eiss, stringBuffer, ' '))
        {
          vec.push_back(stoi(stringBuffer));
        }
      }

      mergeSort(vec, 0, s - 1);
      for (int i = 0; i < s; i++)
      {
        outFile << vec[i] << " ";
      }
      outFile << endl;
      break;
    case QUICK:
      if (!(iss >> s))
      {
        cerr << "QUICK: invalid input" << endl;
        exit(1);
      }
      if (getline(inFile, line))
      {
        istringstream eiss(line);
        while (getline(eiss, stringBuffer, ' '))
        {
          vec.push_back(stoi(stringBuffer));
        }
      }

      quickSort(vec, 0, s - 1);
      for (int i = 0; i < s; i++)
      {
        outFile << vec[i] << " ";
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
