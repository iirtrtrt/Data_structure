# Practice 3. Queue
import sys

class Empty(Exception):
  pass

class Queue:
  def __init__(self):
    # TODO
    pass

  # Enqueue an element to the queue
  def enqueue(self, d):
    # TODO
    pass

  # Dequeue an element from the queue and return the its value
  def dequeue(self):
    # TODO
    pass

  # Get the front of the queue
  def front(self):
    # TODO
    pass

  # Write the value of every element in the queue to the output file
  def write(self, outFile):
    # TODO
    pass

# Stack via queues
class StackViaQueues:
  def __init__(self):
    # TODO
    pass

  # Push an element to the stack
  def push(self, d):
    # TODO
    pass

  # Pop the top element from the stack
  def pop(self):
    # TODO
    pass

  # Retreive the top of the stack
  def peek(self):
    # TODO
    pass

  # Write the value of every element from the bottom to the top 
  # to the output file
  def write(self, outFile):
    # TODO
    pass

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  Q = Queue()
  S = StackViaQueues()
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == 'E':
        if len(words) != 2:
          raise Exception("ENQUEUE: invalid input")
        if Q.enqueue(words[1]):
          Q.write(outFile)
        else:
          outFile.write("Enqueue failed\n")   
      elif op == 'D':
        if len(words) != 1:
          raise Exception("DEQUEUE: invalid input")
        Q.dequeue()
        Q.write(outFile)
      elif op == 'F':
        if len(words) != 1:
          raise Exception("FRONT: invalid input")
        val = Q.front()
        outFile.write(val + "\n")
      elif op == 'U':
        if len(words) != 2:
          raise Exception("PUSH: invalid input")
        S.push(words[1])
        S.write(outFile)
      elif op == 'O':
        if len(words) != 1:
          raise Exception("POP: invalid input")
        S.pop()
        S.write(outFile)
      elif op == 'T':
        if len(words) != 1:
          raise Exception("TOP: invalid input")
        val = S.peek()
        outFile.write(val + "\n")
      else:
        raise Exception("Undefined operator")

