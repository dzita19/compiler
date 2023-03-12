#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct node {
  void* info;
  struct node* prev;
  struct node* next;
} Node;

Node* NodeCreateEmpty();
void  NodeDrop(Node*);

typedef struct LinkedList {
  Node* first;
  Node* last;
} LinkedList;

LinkedList* LinkedListCreateEmpty();
void        LinkedListDrop(LinkedList*); // claims ownership of the object

void        LinkedListInsertFirst (LinkedList*, Node*);
void        LinkedListInsertLast  (LinkedList*, Node*);
void        LinkedListInsertAfter (LinkedList*, Node*, Node*);
void        LinkedListInsertBefore(LinkedList*, Node*, Node*);
Node*       LinkedListRemoveFirst (LinkedList*);
Node*       LinkedListRemoveLast  (LinkedList*);
Node*       LinkedListRemoveFrom  (LinkedList*, Node*);
void        LinkedListDelete      (LinkedList*);
LinkedList* LinkedListDuplicate   (LinkedList*);

#endif