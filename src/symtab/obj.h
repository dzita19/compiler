#ifndef _OBJ_H_
#define _OBJ_H_

#include "util/linked_list.h"
#include "struct.h"

typedef enum ObjKind {
  OBJ_VAR,
  OBJ_MEMB,
  OBJ_TYPE,
  OBJ_TAG,
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

extern const int  DECLARED,
                  DEFINED,
                  TENTATIVE;

extern const int  TAG_NONE,
                  TAG_STRUCT,
                  TAG_UNION,
                  TAG_ENUM;

extern const int  STORAGE_STATIC,
                  STORAGE_AUTO;

extern const int  LINKAGE_NONE,
                  LINKAGE_EXTERNAL,
                  LINKAGE_INTERNAL;

extern const int  DEFINITION_FETCH,
                  TAG_FETCH,
                  STORAGE_FETCH,
                  LINKAGE_FETCH;

extern const int  DEFINITION_CLEAR,
                  TAG_CLEAR,
                  STORAGE_CLEAR,
                  LINKAGE_CLEAR;

extern ObjNamespace namespaces[OBJ_KIND_COUNT];

struct Struct;

typedef struct Obj{
  char* name;
  ObjKind kind;
  long address;
  int specifier;  // for vars - defined, storage, linkage
                  // for tags - defined, tag type
  struct Struct* type;
  LinkedList members;
} Obj;

extern Obj* ObjCreateEmpty();
extern void ObjDrop(Obj*); // claims ownership of the object
extern void ObjDump(Obj*);

extern Obj* ObjFindMember(Obj* obj, const char* symbol_name);

#endif