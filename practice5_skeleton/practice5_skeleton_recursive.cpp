// Practice 5. Search and Traversals in Binary Search Tree
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
  // Return true if tree is empty; false otherwise
  bool isEmpty() { return (root == nullptr); }
  TreeNode *findMin();
  TreeNode *findMax();
  TreeNode *search(int, TreeNode *);
  void writeInorder(ofstream &, TreeNode *);
  void writePreorder(ofstream &, TreeNode *);
  void writePostorder(ofstream &, TreeNode *);
  void printTree();

private:
  int _getHeight(TreeNode *);
  void _printSpaces(double, TreeNode *);
};

BinarySearchTree::~BinarySearchTree()
{
  // Practice 4
  vector<TreeNode *> stack;
  vector<TreeNode *> nodes;
  TreeNode *curr = root;
  TreeNode *prev = nullptr;
  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push_back(curr);
      curr = curr->left;
    }
    curr = stack.back();
    if (curr->right == nullptr || curr->right == prev)
    {
      stack.pop_back();
      nodes.push_back(curr);
      prev = curr;
      curr = nullptr;
    }
    else
    {
      curr = curr->right;
    }
  }
  vector<TreeNode *>::iterator it;
  for (it = nodes.begin(); it != nodes.end(); ++it)
    delete *it;
}

// Given a sequence arr of integers, start index l, the end index r,
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
TreeNode *BinarySearchTree::arrayToBST(vector<int> &arr, int l, int r)
{
  // Practice 4
  if (l > r)
    return nullptr;
  vector<int>::iterator it = arr.begin();
  int prev = *it;
  for (; it != arr.end(); ++it)
  {
    if (prev > *it)
      return nullptr;
    prev = *it;
  }
  int mid = (l + r) / 2;
  TreeNode *node = new TreeNode(arr[mid]);
  node->left = arrayToBST(arr, l, mid - 1);
  node->right = arrayToBST(arr, mid + 1, r);
  return node;
}

// Return the node with the minimum value
TreeNode *BinarySearchTree::findMin()
{
  // Practice 4
  if (isEmpty())
    return nullptr;
  TreeNode *p = root;
  while (p->left != nullptr)
    p = p->left;
  return p;
}

// Return the node with the maximum value
TreeNode *BinarySearchTree::findMax()
{
  // Practice 4
  if (isEmpty())
    return nullptr;
  TreeNode *p = root;
  while (p->right != nullptr)
    p = p->right;
  return p;
}

// Given a query, search for the node whose key is equal to query.
// If the node exists, return the key
// Otherwise, return nullptr
TreeNode *BinarySearchTree::search(int query, TreeNode *ptr)
{
  // TODO. Practice 5
  if (ptr->key == query or ptr == nullptr)
  {
    return ptr;
  }
  else if (query < ptr->key and ptr->left)
  {
    return search(query, ptr->left);
  }
  else if (query > ptr->key and ptr->right)
  {
    return search(query, ptr->right);
  }
  return 0;
}

// Given an output file stream, write the keys of all the nodes
// visited in inorder traversal
void BinarySearchTree::writeInorder(ofstream &outFile, TreeNode *ptr)
{
  // TODO. Practice 5
  if (ptr == nullptr)
  {
    return;
  }
  writeInorder(outFile, ptr->left);
  outFile << ptr->key << " ";
  writeInorder(outFile, ptr->right);
}

// Given an output file stream, write the keys of all the nodes
// visited in preorder traversal
void BinarySearchTree::writePreorder(ofstream &outFile, TreeNode *ptr)
{
  // TODO. Practice 5
  if (ptr == nullptr)
  {
    return;
  }
  outFile << ptr->key << " ";
  writePreorder(outFile, ptr->left);
  writePreorder(outFile, ptr->right);
}

// Given an output file stream, write the keys of all the nodes
// visited in postorder traversal
void BinarySearchTree::writePostorder(ofstream &outFile, TreeNode *ptr)
{
  // TODO. Practice 5
  if (ptr == nullptr)
  {
    return;
  }
  writePostorder(outFile, ptr->left);
  writePostorder(outFile, ptr->right);
  outFile << ptr->key << " ";
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
    case SEARCH:
      if (!(iss >> k))
      {
        cerr << "SEARCH: invalid input" << endl;
        exit(1);
      }
      // TODO. Practice 5. Call the function for search
      if (tree.search(k, tree.root))
      {
        outFile << tree.search(k, tree.root)->key << endl;
      }
      else
      {
        cerr << "Search Failed" << endl;
      }
      break;
    case INORDER:
      // TODO. Practice 5. Call the function for inorder traversal;
      if (tree.search(k, tree.root))
      {
        tree.writeInorder(outFile, tree.root);
        outFile << endl;
      }
      break;
    case PREORDER:
      // TODO. Practice 5. Call the function for preorder traversal;
      if (tree.search(k, tree.root))
      {
        tree.writePreorder(outFile, tree.root);
        outFile << endl;
      }
      break;
    case POSTORDER:
      // TODO. Practice 5. Call the function for postorder traversal;
      if (tree.search(k, tree.root))
      {
        tree.writePostorder(outFile, tree.root);
        outFile << endl;
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
