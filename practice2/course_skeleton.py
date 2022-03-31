import sys
ADD = 'A'
DELETE = 'D'
FIND = 'F'


class Student:
    def __init__(self, i, n, p=None):
        self.id = i
        self.name = n
        self.next = p
        pass


class Course:
    def __init__(self, l=[]):
        self.head = l
        pass

    def __len__(self):
        return self.size

    def isEmpty(self):
        return self.size == 0

    def addStudent(self, newID, newName):
        info = Student(newID, newName)

        if (self.head != []):
            pre = self.head
            cur = self.head
            while (cur is not None):
                if (newID == cur.id):
                    print(newID)
                    print(cur.id)
                    return 0
                elif (newID < cur.id):
                    if (cur == self.head):
                        info.next = cur
                        self.head = info
                    else:
                        pre.next = info
                        info.next = cur
                    return 1
                elif ((cur.next is None) and newID > cur.id):
                    cur.next = info
                    return 1

                pre.next = cur
                cur = cur.next
        else:
            self.head = info
            return 1
        pass

    def deleteStudent(self, queryID):
        pre = self.head
        cur = self.head
        while (cur is not None):
            if (queryID == cur.id):
                if (cur is self.head):
                    self.head = cur.next
                    return 1
                elif (cur.next is None):
                    pre.next = None
                    return 1
                else:
                    pre.next = cur.next
                    return 1

            pre = cur
            cur = cur.next
        pass

    def find(self, queryID):
        ptr = self.head
        while (ptr is not None):
            if (queryID == ptr.id):
                return ptr

            ptr = ptr.next
        pass

    def write(self, outFile):
        ptr = self.head
        while (ptr is not None):
            outFile.write(str(ptr.id) + " " + ptr.name + " ")
            ptr = ptr.next

        outFile.write("\n")
        pass


if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise Exception("Correct usage: [program] [input] [output]")

    course = Course()
    with open(sys.argv[1], 'r') as inFile:
        lines = inFile.readlines()
    with open(sys.argv[2], 'w') as outFile:
        for line in lines:
            words = line.split()
            op = words[0]
            if op == ADD:
                if len(words) != 3:
                    raise Exception("ADD: invalid input")
                i, n = int(words[1]), words[2]
                if course.addStudent(i, n):
                    course.write(outFile)
                else:
                    outFile.write("Addition failed\n")
            elif op == DELETE:
                if len(words) != 2:
                    raise Exception("DELETE: invalid input")
                i = int(words[1])
                if course.deleteStudent(i):
                    course.write(outFile)
                else:
                    outFile.write("Deletion failed\n")
            elif op == FIND:
                if len(words) != 2:
                    raise Exception("DELETE: invalid input")
                i = int(words[1])
                found = course.find(i)
                if not found:
                    outFile.write("Search failed\n")
                else:
                    outFile.write(str(found.id) + " " + found.name + "\n")
            else:
                raise Exception("Undefined operator")
