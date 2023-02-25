#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct node {
  void* info;
  struct node* prev;
  struct node* next;
} Node;

typedef struct {
  Node* first;
  Node* last;
} LinkedList;

void  LinkedListInsertFirst(LinkedList*, Node*);
void  LinkedListInsertLast (LinkedList*, Node*);
Node* LinkedListRemoveFirst(LinkedList*);
Node* LinkedListRenoveLast (LinkedList*);

#endif