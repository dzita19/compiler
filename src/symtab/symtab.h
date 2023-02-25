#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "scope.h"
#include "obj.h"

typedef struct Symtab {
  Scope* current_scope;
} Symtab;

// symtab owns all scopes inserted into it - FREE THEM!!!

extern void SymtabOpenScope(Symtab* symtab, ScopeType type);
extern void SymtabCloseScope(Symtab* symtab);
extern void SymtabInsert(Symtab* symtab, Obj* obj);
extern Obj* SymtabFind(Symtab* symtab, const char* symbol_name);
extern Obj* SymtabFindCurrentScope(Symtab* symtab, const char* symbol_name);
extern void SymtabDrop(Symtab* symtab); // doesn't claim ownership of the object

#endif