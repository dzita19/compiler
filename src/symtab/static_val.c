#include "static_val.h"

#include <stdio.h>
#include <stdlib.h>

#include "../util/memory_safety.h"
#include "../util/vector.h"

StaticVal* StaticValCreateEmpty(){
  StaticVal* val = malloc(sizeof(StaticVal));
  val->kind       = 0;
  val->size       = 0;
  val->offset     = 0;
  val->value      = 0;
  val->obj_ref    = 0;
  val->string_ref = 0;

  static_val_alloc++;

  return val;
}

void StaticValDrop(StaticVal* val){
  free(val);

  static_val_free++;
}

extern int dump_indent;

extern void print_indent();

void StaticValDump(StaticVal* val){
  extern Vector* string_table;

  printf("Offset: %d; Size: %d; ", val->offset, val->size);
  if(val->kind == VAL_ADDRESS && val->obj_ref) {
    if((val->obj_ref->specifier & LINKAGE_FETCH) == LINKAGE_NONE)
      printf("Address of: $unnamed + %d; ", val->obj_ref->address);
    else
      printf("Address of: %s; ", val->obj_ref->name);
  }
  if(val->kind == VAL_STRING) printf("String: \"%s\"; ", (char*)VectorGet(string_table, val->string_ref));
  if(val->value >= 0) printf("Value: %d; ",  +val->value);
  else                printf("Value: -%d; ", -val->value);
}

void StaticValAddToList(StaticVal* new_val, LinkedList* list){
  Node* node = list->first;
  while(node){
    StaticVal* current_val = node->info;

    int a0 = new_val->offset;
    int a1 = new_val->offset + new_val->size;

    int b0 = current_val->offset;
    int b1 = current_val->offset + current_val->size;

    if((a0 <= b0 && a1 > b0) || (a1 >= b1 && a0 < b0)){
      Node* old = node;
      node = node->next;
      StaticValDrop(current_val);
      NodeDrop(LinkedListRemoveFrom(list, old));
    }
    else if(a0 >= b1) node = node->next;
    else if(a1 <= b0) break; 
  }

  Node* new_node = NodeCreateEmpty();
  new_node->info = new_val;

  if(node) LinkedListInsertBefore(list, node, new_node);
  else     LinkedListInsertLast(list, new_node);
}