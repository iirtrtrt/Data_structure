#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;
const char BINARY_SEARCH = 'B';
const char ROTATED_ARRAY = 'R';
const char DUPLICATES = 'D';

void getNumbers(ifstream &inFile, string &splited, string &line, vector<int> &vec) // To read the numbers
{
  if (getline(inFile, line))
  {
    istringstream eiss(line);
    while (getline(eiss, splited, ' ')) // Split by ' '
    {
      vec.push_back(stoi(splited)); // Cast to integer and add to vector
    }
  }
}

int BinarySearchRec(vector<int> &vec, int x, int low, int high) // Binary Searching
{
  if (low > high) // Return -1 which means the x value could not be found, if the low value reverses the high value
  {
    return -1;
  }
  else
  {
    int mid = (low + high) / 2; // Get the middle index

    if (x == vec[mid]) // Return middle index, if middle element equals the x value
    {
      return mid;
    }
    else if (x < vec[mid]) // if the x value is smaller than the value of middle, we can know between the low index and middle index
    {
      return BinarySearchRec(vec, x, low, mid - 1); // Search again between the low index and middle -1 index
    }
    else
    {
      return BinarySearchRec(vec, x, mid + 1, high); // Opposite of low
    }
  }
}

int getPivot(vector<int> &vec, int low, int high) // Pivot is the end index of the rotation
{
  if (low > high) // Return -1 which means the pivot was not found, if the low value reverses the high value
  {
    return -1;
  }
  else if (low == high) // Return the value of low or high which means both all are a pivot
  {
    return low;
  }

  int mid = (low + high) / 2;

  if (mid < high && vec[mid] > vec[mid + 1]) // Return the middle value is a pivot because the middle value is bigger than next value
  {
    return mid;
  }
  else if (mid > low && vec[mid] < vec[mid - 1]) // Opposite of high
  {
    return mid - 1;
  }
  else if (vec[mid] <= vec[low]) // Run this function again between the low index and middle - 1 if the middle value is smaller than the low value
  {
    return getPivot(vec, low, mid - 1);
  }
  else // Run this function again if the middle value is smaller than the low value
  {
    return getPivot(vec, mid + 1, high);
  }
}

int rotatedBinarySearch(vector<int> &vec, int x, int low, int high)
{
  int pivot = getPivot(vec, low, high);

  if (pivot == -1) // Run binary search function immediately
  {
    return BinarySearchRec(vec, x, low, high);
  }
  else if (vec[pivot] == x) // Return pivot if the value of pivot equals the x value
  {
    return pivot;
  }
  else if (vec[low] <= x) // Run the function again between the low index and pivot - 1 if the low value is smaller than the value of x
  {
    return BinarySearchRec(vec, x, low, pivot - 1);
  }
  else
  {
    return BinarySearchRec(vec, x, pivot + 1, high); // Run the function again between pivot + 1 and the high index if the low value is smaller than the value of x
  }
}

int dublicated(vector<int> &vec, int x, int low, int high)
{
  if (low > high) // Return -1 which means the x value could not be found, if the low value reverses the high value
  {
    return -1;
  }

  int mid = (low + high) / 2;

  if (vec[mid] == x) // Return the middle index if the middle value equals the value x
  {
    return mid;
  }
  else if (vec[mid] == vec[low]) // If the values of middle and low are the same
  {
    while (vec[mid] == vec[low]) // The low index is increasing till getting the different than the value of middle
    {
      low++;
    }
    return dublicated(vec, x, low, high); // Run this function again with the new low index
  }
  else if (vec[mid] == vec[high]) // If the values of middle and low are the same
  {
    while (vec[mid] == vec[high]) // The high index is decreasing till getting the different than the value of middle
    {
      high--;
    }
    return dublicated(vec, x, low, high); // Run this function again with the new high index
  }
  else
  {
    return rotatedBinarySearch(vec, x, low, high); // Run this function
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
