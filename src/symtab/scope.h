#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "obj.h"

typedef enum ScopeType{
  SCOPE_FUNCTION,
  SCOPE_FILE,
  SCOPE_BLOCK,
  SCOPE_FUNC_PROTOTYPE,
} ScopeType;

typedef struct Scope{
  struct Scope* outer; // points to father scope
  struct Scope* next; // points to brother scope
  struct Scope* rightmost; // points to rightmost son
  Obj* first_obj;
  Obj* last_obj;
  ScopeType type;
} Scope;

// scope owns all objs inserted into it - FREE THEM!!!

extern void ScopeInsert(Scope* scope, Obj* obj);
extern Obj* ScopeFind(Scope* scope, const char* symbol_name);
extern void ScopeDrop(Scope* scope); // doesn't claim ownership of the object

#endif