# Practice 7. Heaps
import heapq
import sys

if __name__ == '__main__':
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  k = 0
  history = []
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
    words = lines[0].split()
    if len(words) != 1:
      raise Exception("Error: invalid input")
    k = int(words[0])
    for line in lines[1:]:
      words = line.split()
      if len(words) != 2:
        raise Exception("Error: invalid input")
      history.append((words[0], int(words[1])))
  with open(sys.argv[2], 'w') as outFile:
    # TODO. Call your function with arguments "history" and "k",
    # and write the result into "outFile"
    pass
