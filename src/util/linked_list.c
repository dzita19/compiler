#include "linked_list.h"

void  LinkedListInsertFirst(LinkedList* list, Node* node){
  node->next = list->first;
  node->prev = 0;
  if(list->first) list->first->prev = node;
  else list->last = node;
  list->first = node;
}

void  LinkedListInsertLast (LinkedList* list, Node* node){
  node->prev = list->last;
  node->next = 0;
  if(list->last) list->last->next = node;
  else list->first = node;
  list->last = node;
}

Node* LinkedListRemoveFirst(LinkedList* list){
  Node* node = list->first;
  if(list->first == list->last) {
    list->first = 0;
    list->last = 0;
  }
  else {
    list->first = list->first->next;
    list->first->prev = 0;
  }

  node->prev = 0;
  node->next = 0;
  return node;
}

Node* LinkedListRenoveLast (LinkedList* list){
  Node* node = list->last;
  if(list->first == list->last) {
    list->first = 0;
    list->last = 0;
  }
  else{
    list->last = list->last->prev;
    list->last->next = 0;
  }
  
  node->prev = 0;
  node->next = 0;
  return node;
}