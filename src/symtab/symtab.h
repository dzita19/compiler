#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <stdint.h>
#include "scope.h"
#include "obj.h"

typedef struct Symtab {
  Scope* current_scope;
} Symtab;

extern Symtab*  SymtabCreateEmpty();
extern void     SymtabDrop(Symtab* symtab); // claims ownership of the object
extern void     SymtabDump(Symtab* symtab);

extern void SymtabOpenScope(Symtab* symtab, ScopeType type);
extern void SymtabCloseScope(Symtab* symtab);
extern void SymtabInsertScope(Symtab* symtab, Scope* scope);
extern void SymtabRemoveCurrentScope(Symtab* symtab);

extern void SymtabInsert(Symtab* symtab, Obj* obj);
extern void SymtabInsertMember(Symtab* symtab, Obj* tag, Obj* obj);

extern Obj* SymtabFind(Symtab* symtab, const char* symbol_name);
extern Obj* SymtabFindNamespace(Symtab* symtab, const char* symbol_name, ObjNamespace namespace);
extern Obj* SymtabFindCurrentScope(Symtab* symtab, const char* symbol_name);
extern Obj* SymtabFindCurrentScopeNamespace(Symtab* symtab, const char* symbol_name, ObjNamespace namespace);
extern Obj* SymtabFindMember(Symtab* symtab, const char* symbol_name, Obj* tag_obj);
extern Obj* SymtabFindPredefined(uint32_t type_specifiers);

extern Obj predefined_types_obj[PREDEFINED_TYPES_COUNT];
extern Struct predefined_types_struct[PREDEFINED_TYPES_COUNT];

#endif