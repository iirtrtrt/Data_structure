# Practice 4. Binary Search Tree
import sys
from collections import deque
BUILD = 'B'
FIND_MIN = 'm'
FIND_MAX = 'M'

# Node implementation
class TreeNode:
  # TODO
  pass

class BinarySearchTree:
  def __init__(self):
    self.root = None

  # Return True if tree is empty; False otherwise
  def isEmpty(self):
    # TODO
    pass

  # Given a sequence arr of integers, start index l, the end index r, 
  # build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
  # Return the root node of the tree
  def arrayToBST(self, arr, l, r):
    # TODO
    pass

  # Return the node with the minimum value 
  def findMin(self):
    # TODO
    pass

  # Return the node with the maximum value 
  def findMax(self):
    # TODO
    pass

  def _getHeight(self, curr):
    if not curr:
      return 0
    return 1 + max(self._getHeight(curr.left), self._getHeight(curr.right))

  def _printSpaces(self, n, curr):
    for i in range(int(n)):
      print("  ", end="")
    if not curr:
      print(" ", end="")
    else:
      print(str(curr.key), end="")

  def printTree(self):
    if not self.root:
      return 
    q = deque()
    q.append(self.root)
    temp = deque()
    cnt = 0
    height = self._getHeight(self.root) - 1
    nMaxNodes = 2**(height + 1) - 1
    while cnt <= height:
      curr = q.popleft()
      if len(temp) == 0:
        self._printSpaces(nMaxNodes / (2**(cnt+1)), curr)
      else:
        self._printSpaces(nMaxNodes / (2**cnt), curr)
      if not curr:
        temp.append(None)
        temp.append(None)
      else:
        temp.append(curr.left)
        temp.append(curr.right)
      if len(q) == 0:
        print("\n")
        q = temp
        temp = deque()
        cnt += 1

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  
  tree = BinarySearchTree()
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == BUILD:
        data = [int(s) for s in words[1:]]
        tree.root = tree.arrayToBST(data, 0, len(data) - 1)
        if tree.root:
          outFile.write(BUILD + "\n")
          tree.printTree()
        else:
          raise Exception("BUILD: invalid input")
      elif op == FIND_MIN:
        found = tree.findMin()
        if not found:
          raise Exception("FindMin failed")
        else:
          outFile.write(str(found.key) + "\n")
      elif op == FIND_MAX:
        found = tree.findMax()
        if not found:
          raise Exception("FindMax failed")
        else:
          outFile.write(str(found.key) + "\n")
      else:
        raise Exception("Undefined operator")
        
