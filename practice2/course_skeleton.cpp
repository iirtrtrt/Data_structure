#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const char ADD = 'A';
const char DELETE = 'D';
const char FIND = 'F';

class Student
{
public:
  int id;
  string name;
  Student *next;
};

class Course
{
public:
  Student *head;
  Course()
  {
    head = nullptr;
  }
  ~Course()
  {
    Student *ptr = head;
    while (ptr != NULL)
    {
      Student *temp = ptr->next;
      delete ptr;
      ptr = temp;
    }
  }

  bool isEmpty()
  {
    return (head == nullptr);
  }

  bool addStudent(int id, string name);
  bool deleteStudent(int id);
  Student *find(int id);
  void write(ofstream &outFile);
};

bool Course::addStudent(int id, string name)
{
  Student *info = new Student;
  info->id = id;
  info->name = name;
  info->next = nullptr;

  if (head == nullptr)
  {
    head = info;
    return 1;
  }
  else
  {
    Student *pre = head;
    Student *cur = head;
    while (cur != nullptr)
    {
      if (id == cur->id)
      {
        return 0;
      }
      else if (id < cur->id)
      {
        if (cur == head)
        {
          info->next = cur;
          head = info;
        }
        else
        {
          pre->next = info;
          info->next = cur;
        }
        return 1;
      }
      else if (id > cur->id and !cur->next)
      {
        cur->next = info;
        return 1;
      }

      pre = cur;
      cur = cur->next;
    }
  }
  return 0;
}

bool Course::deleteStudent(int id)
{
  Student *pre = head;
  Student *cur = head;
  while (cur != nullptr)
  {
    if (id == cur->id)
    {
      if (cur == head)
      {
        head = cur->next;
        delete cur;
        return 1;
      }
      else if (cur->next == nullptr)
      {
        pre->next = nullptr;
        delete cur;
        return 1;
      }
      else
      {
        pre->next = cur->next;
        delete cur;
        return 1;
      }
    }

    pre = cur;
    cur = cur->next;
  }
  return 0;
}

Student *Course::find(int id)
{
  Student *ptr = head;
  while (ptr != nullptr)
  {
    if (id == ptr->id)
    {
      return ptr;
    }
    ptr = ptr->next;
  }

  return 0;
}

void Course::write(ofstream &outFile)
{
  Student *ptr = head;
  while (ptr != nullptr)
  {
    outFile << ptr->id << " " << ptr->name << " ";

    ptr = ptr->next;
  }
  outFile << endl;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cerr << "Correct usage: [program] [input] [output]" << endl;
    exit(1);
  }
  Course course;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int id;
    string name;
    Student *found = nullptr;
    cout << line << endl;
    switch (op)
    {
    case ADD:
      if (!(iss >> id >> name))
      {
        cerr << "ADD: invalid input" << endl;
        exit(1);
      }
      if (course.addStudent(id, name))
        course.write(outFile);
      else
        outFile << "Addition failed" << endl;
      break;
    case DELETE:
      if (!(iss >> id))
      {
        cerr << "DELETE: invalid input" << endl;
        exit(1);
      }
      if (course.deleteStudent(id))
        course.write(outFile);
      else
        outFile << "Deletion failed" << endl;
      break;
    case FIND:
      if (!(iss >> id))
      {
        cerr << "FIND: invalid input" << endl;
        exit(1);
      }
      found = course.find(id);
      if (found == nullptr)
        outFile << "Search failed" << endl;
      else
        outFile << found->id << " " << found->name << endl;
      break;
    default:
      cerr << "Undefined operator" << endl;
      exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
