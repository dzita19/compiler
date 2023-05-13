#ifndef _STATIC_INIT_H_
#define _STATIC_INIT_H_

#include "../util/linked_list.h"

#include "obj.h"

typedef enum StaticValType{
  VAL_ARITHM,
  VAL_ADDRESS,
  VAL_STRING,
} StaticValType;

typedef struct StaticVal{
  StaticValType type;
  int size;
  int offset;
  int value;
  Obj* obj_ref;
  int string_ref;
} StaticVal;

StaticVal* StaticValCreateEmpty();
void       StaticValDrop(StaticVal*);
void       StaticValDump(StaticVal*);

void StaticValAddToList(StaticVal*, LinkedList*);

#endif