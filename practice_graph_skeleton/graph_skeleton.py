# Practice 8. Graph Representation 
import sys
from collections import deque
CONSTRUCT = 'C'
IS_ADJACENT = 'I'
GET_NEIGHBORS = 'N'
BFS = 'B'
DFS = 'D'
REACHABILITY = 'R'
TOPOLOGICAL_SORT = 'T'
SHORTEST_PATH = 'S'

class Graph:
  # TODO. Define a constructor and proper methods
  def __init__(self):
    pass

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  
  g = Graph()
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    i = 0
    while i < len(lines):
      words = lines[i].split()
      op = words[0]
      if op == CONSTRUCT:
        if len(words) != 3:
          raise Exception("CONSTRUCT: invalid input")
        n, m = int(words[1]), int(words[2])
        cnt, data = m, []
        while cnt: 
          i += 1
          words = lines[i].split()
          if len(words) != 3:
            raise Exception("CONSTRUCT: invalid input")
          u, v, wgt = int(words[0]), int(words[1]), int(words[2])
          data.append((u, v, wgt))
          cnt -= 1
        # TODO. Construct a graph
      elif op == IS_ADJACENT:
        if len(words) != 3:
          raise Exception("IS_ADJACENT: invalid input")
        u, v = int(words[1]), int(words[2])
        # TODO. Check if edge (u, v) exists in the graph
      elif op == GET_NEIGHBORS:
        if len(words) != 2:
          raise Exception("GET_NEIGHBORS: invalid input")
        u = int(words[1])
        # TODO. Get all the neighbors of u
      else:
        raise Exception("Undefined operator")
      i += 1
