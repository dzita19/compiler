#ifndef _STATIC_INIT_H_
#define _STATIC_INIT_H_

#include "../util/linked_list.h"

#include "obj.h"

typedef enum StaticValKind{
  VAL_ERROR,
  VAL_ARITHM,
  VAL_ADDRESS,
  VAL_STRING,
} StaticValKind;

typedef struct StaticVal{
  StaticValKind kind;
  int size;
  int offset; // offset of the field from the beginning of the object
  int value; // value the field is initialized with
  Obj* obj_ref;
  int string_ref;
} StaticVal;

StaticVal* StaticValCreateEmpty();
void       StaticValDrop(StaticVal*);
void       StaticValDump(StaticVal*);

void StaticValAddToList(StaticVal*, LinkedList*);

#endif