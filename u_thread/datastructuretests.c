#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Node
struct thread {
  struct thread* next;
  struct thread* prev;

  int value;
};

struct thread* HEAD;
struct thread* TAIL;

void add(struct thread* t) {
  if(t == NULL) {
    fprintf(stderr, "Error, thread is NULL \n");
    exit(EXIT_FAILURE);
  } else {
    if(HEAD == NULL) HEAD = t;
    else {
      TAIL->next = t;
      t->next = NULL;
      t->prev = TAIL;
    }
    TAIL = t;
  }
}

//Since it is FCFS, it will remove the first element
struct thread* removeThread() {
  if (HEAD == NULL) {
    return NULL;
  } else {
      struct thread* t;
      t = HEAD;
      HEAD = HEAD->next;
      return t;
  }
}

int main() {
  struct thread* n0 =  (struct thread*)malloc(sizeof(struct thread));
  struct thread* n1 =  (struct thread*)malloc(sizeof(struct thread));
  struct thread* n2 =  (struct thread*)malloc(sizeof(struct thread));
  struct thread* n3 =  (struct thread*)malloc(sizeof(struct thread));
  struct thread* n4 =  (struct thread*)malloc(sizeof(struct thread));

  n0->value = 0;
  n0->next = NULL;
  n0->prev = NULL;
  n1->value = 1;
  n1->next = NULL;
  n1->prev = NULL;
  n2->value = 2;
  n2->next = NULL;
  n2->prev = NULL;
  n3->value = 3;
  n3->next = NULL;
  n3->prev = NULL;
  n4->value = 4;
  n4->next = NULL;
  n4->prev = NULL;

  HEAD = NULL;
  TAIL = NULL;

  add(n0);
  printf("%d ", HEAD->value);
  add(n1);
  printf("%d ", HEAD->next->value);
  add(n2);
  printf("%d \n", HEAD->next->next->value);

  printf("----------------\n");

  struct thread* removed0 = removeThread();
  printf("Removed: %d \n", removed0->value);
  printf("%d ", HEAD->value);
  printf("%d \n", HEAD->next->value);
  //WORKS: SEG FAULT if you try to do printf("%d \n", HEAD->next->next->value);

  struct thread* removed1 = removeThread();
  printf("Removed: %d \n", removed1->value);
  printf("%d \n", HEAD->value);
  struct thread* removed2 = removeThread();
  printf("Removed: %d \n", removed2->value);
  //WORKS: SEG FAULT if you try to do printf("%d \n", HEAD->value);

  printf("----------------\n");


  add(n0);
  add(n1);
  add(n2);
  add(n3);
  add(n4);

  printf("%d ", HEAD->value);
  printf("%d ", HEAD->next->value);
  printf("%d ", HEAD->next->next->value);
  printf("%d ", HEAD->next->next->next->value);
  printf("%d \n", HEAD->next->next->next->next->value);

  return 0;
}
