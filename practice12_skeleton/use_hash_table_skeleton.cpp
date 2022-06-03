// Practice 12. Use hash tables
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;
const char TWO_SUM = 'T';
const char SYMMETRIC_PAIRS = 'S';

vector<int> readIntegers(int k, string &line)
{
  vector<int> arr;
  istringstream liss(line);
  int val;
  for (int i = 0; i < k; ++i)
  {
    if (!(liss >> val))
    {
      cerr << "Error: invalid input value" << endl;
      exit(1);
    }
    else
    {
      arr.push_back(val);
    }
  }
  return arr;
}

void twoSum(int k, vector<int> &nums, ofstream &outFile)
{
  unordered_map<int, int> m;

  for (int i = 0; i < nums.size(); i++)
  {
    if (m.find(k - nums[i]) != m.end())
    {
      outFile << "T" << endl;
      return;
    }

    m[nums[i]] = i;
  }

  outFile << "F" << endl;
  return;
}

void symmetricPairs(vector<pair<int, int>> &pairs, ofstream &outFile)
{
  unordered_map<int, int> m;

  for (int i = 0; i < pairs.size(); i++)
  {
    int first = pairs[i].first;
    int second = pairs[i].second;

    if (m.find(second) != m.end() && m[second] == first)
    {
      outFile << first << " " << second << endl;
    }

    m[first] = second;
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
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<int> nums;
    vector<pair<int, int>> pairs;
    vector<pair<int, int>> ans;
    vector<pair<int, int>>::iterator it;
    int k, n, a, b;
    bool exist;
    switch (op)
    {
    case TWO_SUM:
      if (!(iss >> k >> n))
      {
        cerr << "TWO_SUM: invalid input" << endl;
        exit(1);
      }
      if (!getline(inFile, line))
      {
        cerr << "TWO_SUM: unable to read a line" << endl;
        exit(1);
      }
      nums = readIntegers(n, line);
      // TODO
      // Take k and nums as input, and run twoSum(k, nums)
      // Write whether two sum exists into output file
      twoSum(k, nums, outFile);
      break;
    case SYMMETRIC_PAIRS:
      if (!(iss >> n))
      {
        cerr << "SYMMETRIC_PAIRS: invalid input" << endl;
        exit(1);
      }
      for (int i = 0; i < n; ++i)
      {
        if (!getline(inFile, line))
        {
          cerr << "SYMMERIC_PAIRS: invalid input" << endl;
          exit(1);
        }
        istringstream tiss(line);
        if (!(tiss >> a >> b))
        {
          cerr << "SYMMETRIC_PAIRS: invalid input" << endl;
          exit(1);
        }
        pairs.push_back(make_pair(a, b));
      }
      // TODO
      // Take pairs as input, and run symmetricPairs(pairs)
      // Write every symmetric pair into output file
      symmetricPairs(pairs, outFile);
      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
