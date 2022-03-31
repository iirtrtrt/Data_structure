// Practice 3. Queue
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const char ENQUEUE = 'E';
const char DEQUEUE = 'D';
const char FRONT = 'F';
const char PUSH = 'U';
const char POP = 'O';
const char TOP = 'T';

struct Node
{
  int element;
  Node *next;
};

class Queue
{
private:
  Node *head;

public:
  Queue()
  {
    head = nullptr;
  }
  ~Queue()
  {
    Node *ptr = head;
    while (ptr != nullptr)
    {
      Node *temp = ptr->next;
      delete ptr;
      ptr = temp;
    }
  }

  // Enqueue an ele to the queue
  bool enqueue(int d)
  {
    Node *temp = new Node;
    temp->element = d;
    temp->next = nullptr;

    if (head == nullptr)
    {
      head = temp;
    }
    else
    {
      Node *ptr = head;
      while (ptr->next != nullptr)
      {
        ptr = ptr->next;
      }
      ptr->next = temp;
    }

    return 1;
  }

  // Dequeue an ele from the queue and return the its value
  int dequeue()
  {
    if (head == nullptr)
    {
      return 0;
    }
    else
    {
      Node *ptr = head;
      head = ptr->next;
      int temp = ptr->element;
      delete ptr;

      return temp;
    }
  }

  // Get the front of the queue
  int front()
  {
    return head->element;
  }

  // Write the value of every ele in the queue to the output file
  void write(ofstream &outFile)
  {
    Node *ptr = head;
    while (ptr != nullptr)
    {
      outFile << ptr->element << " ";

      ptr = ptr->next;
    }
    outFile << endl;
  }
};

class StackViaQueues
{
private:
  Queue q1;
  Queue q2;
  int len = 0;

public:
  // TODO. Define constructor/destructor/methods here
  // Push an ele to the stack
  bool push(int d)
  {
    q2.enqueue(d);

    for (int i = 0; i < len; i++)
    {
      q2.enqueue(q1.dequeue());
    }

    Queue temp = q1;
    q1 = q2;
    q2 = temp;
    len++;

    return 1;
  }

  // Pop the top ele from the stack
  int pop()
  {
    int re = q1.dequeue();
    len--;

    return re;
  }

  // Retrieve the top of the stack
  int peek()
  {
    return q1.front();
  }

  // Write the value of every ele from the bottom to the top
  // to the output file
  void write(ofstream &outFile)
  {
    int arr[len];
    for (int i = 0; i < len; i++)
    {
      arr[i] = q1.dequeue();
      q1.enqueue(arr[i]);
    }
    for (int i = len - 1; i >= 0; i--)
    {
      outFile << arr[i] << " ";
    }
    outFile << endl;
  }
};

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cerr << "Correct usage: [program] [input] [output]" << endl;
    exit(1);
  }
  Queue q;
  StackViaQueues s;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int data;
    switch (op)
    {
    case ENQUEUE:
      if (!(iss >> data))
      {
        cerr << "ADD: invalid input" << endl;
        exit(1);
      }
      if (q.enqueue(data))
        q.write(outFile);
      else
        outFile << "Enqueue failed" << endl;
      break;
    case DEQUEUE:
      q.dequeue();
      q.write(outFile);
      break;
    case FRONT:
      outFile << q.front() << endl;
      break;
    case PUSH:
      if (!(iss >> data))
      {
        cerr << "PUSH: invalid input" << endl;
        exit(1);
      }
      if (s.push(data))
        s.write(outFile);
      else
        outFile << "Push failed" << endl;
      break;
    case POP:
      s.pop();
      s.write(outFile);
      break;
    case TOP:
      data = s.peek();
      outFile << data << endl;
      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
