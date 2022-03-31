// Practice 4. Binary Search Tree
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const char BUILD = 'B';
const char FIND_MIN = 'm';
const char FIND_MAX = 'M';
const char SEARCH = 'S';
const char INSERT = 'I';
const char DELETE = 'D';
const char INORDER = 'N';
const char PREORDER = 'R';
const char POSTORDER = 'O';

class TreeNode
{
public:
  int key;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int k, TreeNode *l = nullptr, TreeNode *r = nullptr)
  {
    key = k;
    left = l;
    right = r;
  }
};

class BinarySearchTree
{
public:
  TreeNode *root;
  BinarySearchTree() : root(nullptr) {}
  ~BinarySearchTree();

  TreeNode *arrayToBST(vector<int> &, int, int);
  TreeNode *findMin();
  TreeNode *findMax();
  void printTree();
  void deleteTree(TreeNode *);

private:
  int _getHeight(TreeNode *);
  void _printSpaces(double, TreeNode *);
};

BinarySearchTree::~BinarySearchTree()
{
  deleteTree(root);
}

// Given a sequence arr of integers, start index l, the end index r,
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
TreeNode *BinarySearchTree::arrayToBST(vector<int> &arr, int l, int r)
{
  for (int i = l; i < r; i++)
  {
    if (arr[i] >= arr[i + 1])
    {
      return 0;
    }
  }

  int middle = r / 2;
  TreeNode *tn = new TreeNode(arr[middle]);
  root = tn;

  while (l < middle)
  {
    TreeNode *temp = root;
    TreeNode *fl = new TreeNode(arr[l]);
    TreeNode *fr = new TreeNode(arr[r]);

    while (1)
    {
      if (arr[l] < temp->key)
      {
        if (temp->left == nullptr)
        {
          temp->left = fl;
          break;
        }
        temp = temp->left;
      }
      else
      {
        if (temp->right == nullptr)
        {
          temp->right = fl;
          break;
        }
        temp = temp->right;
      }
    }

    temp = root;
    while (1)
    {
      if (arr[r] < temp->key)
      {
        if (temp->left == nullptr)
        {
          temp->left = fr;
          break;
        }
        temp = temp->left;
      }
      else
      {
        if (temp->right == nullptr)
        {
          temp->right = fr;
          break;
        }
        temp = temp->right;
      }
    }

    l++;
    r--;
  }

  return root;
}

// Return the node with the minimum value
TreeNode *BinarySearchTree::findMin()
{
  if (root == nullptr)
  {
    return 0;
  }

  TreeNode *temp = root;
  while (temp->left)
  {
    temp = temp->left;
  }
  return temp;
}

// Return the node with the maximum value
TreeNode *BinarySearchTree::findMax()
{
  if (root == nullptr)
  {
    return 0;
  }

  TreeNode *temp = root;
  while (temp->right)
  {
    temp = temp->right;
  }
  return temp;
}

int BinarySearchTree::_getHeight(TreeNode *curr)
{
  if (curr == nullptr)
    return 0;
  return 1 + max(_getHeight(curr->left), _getHeight(curr->right));
}

void BinarySearchTree::_printSpaces(double n, TreeNode *curr)
{
  for (double i = 0; i < n; ++i)
    cout << "  ";
  if (curr == nullptr)
    cout << " ";
  else
    cout << curr->key;
}

void BinarySearchTree::printTree()
{
  if (root == nullptr)
    return;
  queue<TreeNode *> q;
  q.push(root);
  queue<TreeNode *> temp;
  int cnt = 0;
  int height = _getHeight(root) - 1;
  double nMaxNodes = pow(2, height + 1) - 1;
  while (cnt <= height)
  {
    TreeNode *curr = q.front();
    q.pop();
    if (temp.empty())
      _printSpaces(nMaxNodes / pow(2, cnt + 1) + height - cnt, curr);
    else
      _printSpaces(nMaxNodes / pow(2, cnt), curr);
    if (curr == nullptr)
    {
      temp.push(nullptr);
      temp.push(nullptr);
    }
    else
    {
      temp.push(curr->left);
      temp.push(curr->right);
    }
    if (q.empty())
    {
      cout << endl
           << endl;
      q = temp;
      queue<TreeNode *> empty;
      swap(temp, empty);
      ++cnt;
    }
  }
}

void BinarySearchTree::deleteTree(TreeNode *node)
{
  if (node)
  {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cerr << "Correct usage: [exe] [input] [output]" << endl;
    exit(1);
  }
  BinarySearchTree tree;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int k;
    TreeNode *found = nullptr;
    vector<int> data;
    switch (op)
    {
    case BUILD:
      while (iss >> k)
        data.push_back(k);
      tree.root = tree.arrayToBST(data, 0, data.size() - 1);
      if (tree.root)
      {
        outFile << BUILD << endl;
      }
      else
      {
        cerr << "BUILD: invalid input" << endl;
        exit(1);
      }
      tree.printTree();
      break;
    case FIND_MIN:
      found = tree.findMin();
      if (found == nullptr)
      {
        cerr << "FindMin failed" << endl;
        exit(1);
      }
      else
      {
        outFile << found->key << endl;
      }
      break;
    case FIND_MAX:
      found = tree.findMax();
      if (found == nullptr)
      {
        cerr << "FindMax failed" << endl;
        exit(1);
      }
      else
      {
        outFile << found->key << endl;
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
