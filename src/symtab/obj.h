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

#define DECLARED              0 << 0
#define DEFINED               1 << 0
#define TENTATIVE             2 << 0

#define TAG_NONE              0 << 2
#define TAG_STRUCT            1 << 2
#define TAG_UNION             2 << 2
#define TAG_ENUM              3 << 2

#define STORAGE_STATIC        0 << 2
#define STORAGE_AUTO          1 << 2

#define LINKAGE_NONE          0 << 3
#define LINKAGE_EXTERNAL      1 << 3
#define LINKAGE_INTERNAL      2 << 3

#define DEFINITION_FETCH      3 << 0
#define TAG_FETCH             3 << 2
#define STORAGE_FETCH         1 << 2
#define LINKAGE_FETCH         3 << 3

#define DEFINITION_CLEAR    ~(3 << 0)
#define TAG_CLEAR           ~(3 << 2)
#define STORAGE_CLEAR       ~(1 << 2)
#define LINKAGE_CLEAR       ~(3 << 3)

extern ObjNamespace namespaces[OBJ_KIND_COUNT];

typedef struct Struct Struct;

typedef struct Obj{
  char*       name;
  ObjKind     kind;
  int         address;
  int         specifier;  // for vars - defined, storage, linkage; for tags - defined, tag type
  Struct*     type;
  LinkedList  members;   // LinkedList(Obj*)
  LinkedList* init_vals; // LinkedList(StaticVal*)
} Obj;

extern Obj* ObjCreateEmpty();
extern void ObjDrop(Obj*); // claims ownership of the object
extern void ObjDump(Obj*);

extern Obj* ObjFindMember(Obj* obj, const char* symbol_name);

#endif