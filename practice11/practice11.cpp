#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const char MERGE = 'M';
const char QUICK = 'Q';

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

void write(ofstream &outFile, int s, vector<int> &vec)
{
  for (int i = 0; i < s; i++)
  {
    outFile << vec[i] << " ";
  }
  outFile << endl;
}

void merge(vector<int> &vec, int sta, int mid, int end)
{
  vector<int> temp;
  int i = sta;
  int j = mid + 1;

  while (i <= mid && j <= end)
  {

    if (vec[i] <= vec[j])
    {
      temp.push_back(vec[i]);
      i++;
    }
    else
    {
      temp.push_back(vec[j]);
      j++;
    }
  }

  while (i <= mid)
  {
    temp.push_back(vec[i]);
    i++;
  }

  while (j <= end)
  {
    temp.push_back(vec[j]);
    j++;
  }

  for (int i = sta; i <= end; i++)
    vec[i] = temp[i - sta];
}

void mergeSort(vector<int> &vec, int sta, int end)
{
  if (sta < end)
  {
    int mid = (sta + end) / 2;
    mergeSort(vec, sta, mid);
    mergeSort(vec, mid + 1, end);
    merge(vec, sta, mid, end);
  }
}

int paritition(vector<int> &vec, int left, int right)
{

  int pivot = vec[left];
  int low = left + 1;
  int high = right;

  while (low <= high)
  {
    while (low <= right && pivot >= vec[low])
    {
      low++;
    }
    while (high >= (left + 1) && pivot <= vec[high])
    {
      high--;
    }
    if (low <= high)
    {

      int temp = vec[low];
      vec[low] = vec[high];
      vec[high] = temp;
    }
  }

  int temp = vec[left];
  vec[left] = vec[high];
  vec[high] = temp;

  return high;
}

void quickSort(vector<int> &vec, int left, int right)
{
  if (left < right)
  {
    int par = paritition(vec, left, right);
    quickSort(vec, left, par - 1);
    quickSort(vec, par + 1, right);
  }
}

int main(int argc, char *argvec[])
{
  if (argc != 3)
  {
    cerr << "Correct usage: [exe] [input] [output]" << endl;
    exit(1);
  }

  ifstream inFile(argvec[1]);
  ofstream outFile(argvec[2]);
  string line;
  string splited;

  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int s;
    vector<int> vec;

    switch (op)
    {
    case MERGE:
      if (!(iss >> s))
      {
        cerr << "MERGE: invalid input" << endl;
        exit(1);
      }

      getNumbers(inFile, splited, line, vec);
      mergeSort(vec, 0, s - 1);
      write(outFile, s, vec);

      break;
    case QUICK:
      if (!(iss >> s))
      {
        cerr << "QUICK: invalid input" << endl;
        exit(1);
      }

      getNumbers(inFile, splited, line, vec);
      quickSort(vec, 0, s - 1);
      write(outFile, s, vec);

      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
