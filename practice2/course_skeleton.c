#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct student {
  //TODO
} Student;

typedef struct course {
  Student* head;
} Course; 

bool isEmpty(Course* c) {
  return (c->head == NULL);
}

bool addStudent(Course* c, int id, char* name) {
  //TODO
}

bool deleteStudent(Course* c, int id) {
  //TODO
}

Student* find(Course* c, int id) {
  //TODO
}

void write(Course* c, FILE* outFile) {
  //TODO
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Correct usage: [program] [input] [output]\n");
    exit(1);
  }
  FILE* inFile = fopen(argv[1], "r");
  if (inFile == NULL) {
    printf("no such file %s\n", argv[1]);
    exit(1);
  }
  FILE* outFile = fopen(argv[2], "w");
  if (outFile == NULL) {
    printf("no such file %s\n", argv[2]);
    exit(1);
  }
  Course course;
  char line[512];
  while (fgets(line, sizeof(line), inFile))
  {
    char* token = strtok(line, " \n");
    const char op = line[0];
    int id;
    Student* found = NULL;
    token = strtok(NULL, " \n");
    if (!token) {
      printf("invalid input\n");
      exit(1);
    }
    id = atoi(token);
    switch(op)
    {
      case 'A':
        token = strtok(NULL, " \n");
        if (!token) {
          printf("ADD: invalid input\n");
          exit(1);
        }
        if (addStudent(&course, id, token))
          write(&course, outFile);
        else
          fprintf(outFile, "Addition failed\n");
        break;
      case 'D':
        if (deleteStudent(&course, id))
          write(&course, outFile);
        else
          fprintf(outFile, "Deletion failed\n");
        break;
      case 'F':
        found = find(&course, id);
        if (found == NULL)
          fprintf(outFile, "Search failed\n");
        else
          fprintf(outFile, "%d %s\n", found->id, found->name);
        break;
      default:
        printf("Undefined operator\n");
        exit(1);
    }
  }
  fclose(outFile);
  fclose(inFile);
}
