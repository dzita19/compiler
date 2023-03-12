#ifndef _OBJ_H_
#define _OBJ_H_

#include "util/linked_list.h"
#include "struct.h"

typedef enum ObjKind {
  OBJ_VAR,
  OBJ_TEMP,
  OBJ_TYPE,
  OBJ_TAG,
  OBJ_MEMB,
  OBJ_ENUM,
  OBJ_LABEL,

  OBJ_KIND_COUNT,
} ObjKind;

typedef enum ObjNamespace{
  NAMESPACE_NONE,
  NAMESPACE_ORDINARY,
  NAMESPACE_TAG,
  NAMESPACE_MEMBER,
  NAMESPACE_LABEL,
} ObjNamespace;

typedef enum StorageClassSpecifier {
  NO_STORAGE_CLASS,
  TYPEDEF,
  EXTERN,
	STATIC,
	AUTO,
	REGISTER,
} StorageClassSpecifier;

typedef enum TagType {
  TAG_NONE,
  TAG_STRUCT,
  TAG_UNION,
  TAG_ENUM,
} TagType;

extern ObjNamespace namespaces[OBJ_KIND_COUNT];

struct Struct;

typedef struct Obj{
  char* name;
  ObjKind kind;
  int address;
  int specifier;  // for vars - storage class specifier
                  // for tags - tag type (STRUCT, UNION, ENUM);
  struct Struct* type;
  LinkedList members;
} Obj;

extern Obj* ObjCreateEmpty();
extern void ObjDrop(Obj* obj); // claims ownership of the object
extern void ObjDump(Obj* obj);

#endif