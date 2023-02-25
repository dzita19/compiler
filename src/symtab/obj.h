#ifndef _OBJ_H_
#define _OBJ_H_

#include "struct.h"

typedef enum ObjKind {
  OBJ_VAR,
  OBJ_ELEM,
  OBJ_TEMP,
  OBJ_TYPE,
  OBJ_FUNC,
  OBJ_LABEL,
  OBJ_ENUM,
} ObjKind;

typedef struct Obj{
  char* name;
  ObjKind kind;
  int storage_specifier;
  Struct* type;
  Obj* next;
} Obj;

// only OBJ_TYPE objs own structs stored inside them - FREE THEM!!!

extern void ObjDrop(Obj* obj); // doesn't claim ownership of the object

#endif