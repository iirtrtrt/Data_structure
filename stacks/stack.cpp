#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const char PUSH = 'U';
const char POP = 'O';
const char TOP = 'T';
const char PALINDROME = 'P';
const char BRACKETS = 'B';

struct node
{
    int element;
    node *next;
};

class Stack
{
private:
    node *head;
    int length = 0;

public:
    Stack()
    {
        head = nullptr;
    }

    ~Stack()
    {
        node *ptr = head;

        while (ptr != nullptr)
        {
            node *temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
    }

    bool push(int element)
    {
        node *ptr = new node;
        ptr->element = element;
        ptr->next = nullptr;
        length++;

        if (head == nullptr)
        {
            head = ptr;
            return 1;
        }
        else
        {
            ptr->next = head;
            head = ptr;
            return 1;
        }

        return 0;
    }

    int pop()
    {
        if (IsEmpty())
        {
            return 0;
        }
        else
        {
            node *ptr = head;
            int temp = ptr->element;
            head = ptr->next;

            length--;
            delete ptr;
            return temp;
        }
    }

    int top()
    {
        if (IsEmpty())
        {
            return 0;
        }
        else
        {
            return head->element;
        }
        return 0;
    }

    bool IsEmpty()
    {
        return length == 0;
    }

    void write(ofstream &outFile)
    {
        node *ptr = head;
        Stack reverse;
        while (ptr)
        {
            reverse.push(ptr->element);
            ptr = ptr->next;
        }

        for (int i = 0; i < length; i++)
        {
            outFile << reverse.pop() << " ";
        }
        outFile << endl;
    }
};

bool palindrome(string data)
{
    Stack s;
    int middle = data.size() / 2;
    for (int i = 0; i < data.size(); i++)
    {
        if (i < middle)
        {
            s.push(data[i]);
        }
        else if (i > middle)
        {
            if (s.pop() != data[i])
            {
                return 0;
            }
        }
    }
    return 1;
}

bool barcket(string data)
{
    Stack s;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == '(')
        {
            s.push(data[i]);
        }
        else if (data[i] == '{')
        {
            s.push(data[i]);
        }
        else if (data[i] == '[')
        {
            s.push(data[i]);
        }
        else if (data[i] == ')' and s.pop() != '(')
        {
            return 0;
        }
        else if (data[i] == '}' and s.pop() != '{')
        {
            return 0;
        }
        else if (data[i] == ']' and s.pop() != '[')
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Correct usage: [program] [input] [output]" << endl;
        exit(1);
    }
    Stack s;
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    string line;
    while (getline(inFile, line))
    {
        char op = line[0];
        istringstream iss(line.substr(1));
        int data1;
        string data2;
        switch (op)
        {
        case PUSH:
            if (!(iss >> data1))
            {
                cerr << "ADD: invalid input" << endl;
                exit(1);
            }
            if (s.push(data1))
                s.write(outFile);
            else
                outFile << "Enqueue failed" << endl;
            break;
        case POP:
            s.pop();
            s.write(outFile);
            break;
        case TOP:
            outFile << s.top() << endl;
            break;
        case PALINDROME:
            if (!(iss >> data2))
            {
                cerr << "PUSH: invalid input" << endl;
                exit(1);
            }
            if (palindrome(data2))
            {
                outFile << "T" << endl;
            }
            else
            {
                outFile << "F" << endl;
            }
            break;
        case BRACKETS:
            if (!(iss >> data2))
            {
                cerr << "PUSH: invalid input" << endl;
                exit(1);
            }
            if (barcket(data2))
            {
                outFile << "T" << endl;
            }
            else
            {
                outFile << "F" << endl;
            }
            break;
        default:
            cerr << "Undefined operator" << endl;
            exit(1);
        }
    }
    outFile.close();
    inFile.close();
    return 0;
}
