# Practice 12. Use hash tables
import sys
TWO_SUM = 'T';
SYMMETRIC_PAIRS = 'S';

def readIntegers(n: int, s: str) -> list:
  words = s.split()
  assert(len(words) == n)
  arr = [int(w) for w in words]
  return arr

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    i = 0
    while i < len(lines):
      words = lines[i].split()
      op = words[0]
      if op == TWO_SUM:
        if len(words) != 3:
          raise Exception("TWO_SUM: invalid input")
        k, n = int(words[1]), int(words[2])
        i += 1
        nums = readIntegers(n, lines[i])
        # TODO 
        # Take k and nums as input, and run twoSum(k, nums)
        # Write whether two sum exists into output file
      elif op == SYMMETRIC_PAIRS:
        if len(words) != 2:
          raise Exception("SYMMETRIC_PAIRS: invalid input")
        n = int(words[1])
        pairs = []
        while n:
          i += 1
          words = lines[i].split()
          if len(words) != 2:
            raise Exception("SYMMETRIC_PAIRS: invalid input")
          a, b = int(words[0]), int(words[1])
          pairs.append((a, b))
          n -= 1
        # TODO
        # Take pairs as input, and run symmetricPairs(pairs)
        # Write every symmetric pair into output file
      else:
        raise Exception("Undefined operator")
      i += 1

