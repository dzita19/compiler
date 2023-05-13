#include "static_val.h"

#include <stdio.h>
#include <stdlib.h>

#include "../util/memory_safety.h"
#include "../util/vector.h"

StaticVal* StaticValCreateEmpty(){
  StaticVal* val = malloc(sizeof(StaticVal));
  val->type       = 0;
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

  printf("Offset: 0x%04X; Size: 0x%04X; ", val->offset, val->size);
  if(val->type == VAL_ADDRESS && val->obj_ref) {
    if((val->obj_ref->specifier & LINKAGE_FETCH) == LINKAGE_NONE)
      printf("Address of: $unnamed + 0x%04X; ", val->obj_ref->address);
    else
      printf("Address of: %s; ", val->obj_ref->name);
  }
  if(val->type == VAL_STRING) printf("String: \"%s\"; ", (char*)VectorGet(string_table, val->string_ref));
  printf("Value: 0x%04X; ", val->value);
}

void StaticValAddToList(StaticVal* val, LinkedList* list){
  Node* node;
  for(node = list->first; node; node = node->next){
    StaticVal* current_val = node->info;

    if(current_val->offset >  val->offset) break;
    if(current_val->offset == val->offset){
      current_val->value = val->value;

      StaticValDrop(val);
      return;
    }
  }

  Node* new_node = NodeCreateEmpty();
  new_node->info = val;

  if(node) LinkedListInsertBefore(list, node, new_node);
  else     LinkedListInsertLast(list, new_node);
}