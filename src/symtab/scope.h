#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "obj.h"

#include "util/linked_list.h"

typedef enum ScopeType{
  SCOPE_FUNCTION,
  SCOPE_FILE,
  SCOPE_BLOCK,
  SCOPE_FUNC_PROTOTYPE,
} ScopeType;

typedef struct Scope{
  struct Scope* outer; // points to father scope
  LinkedList    children;
  LinkedList    objs;
  ScopeType     type;
} Scope;

// scope owns all objs inserted into it - FREE THEM!!!

extern Scope* ScopeCreateEmpty();
extern void   ScopeDrop(Scope* scope); // claims ownership of the object
extern void   ScopeDump(Scope* scope);

extern void ScopeInsert(Scope* scope, Obj* obj);
extern Obj* ScopeFind(Scope* scope, const char* symbol_name);
extern Obj* ScopeFindNamespace(Scope* scope, const char* symbol_name, ObjNamespace namespace);

#endif