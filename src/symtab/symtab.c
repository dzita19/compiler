#include "symtab.h"

#include "util/queue.h"

void SymtabOpenScope(Symtab* symtab, ScopeType type){
  Scope* new_scope = malloc(sizeof(Scope));

  new_scope->outer = symtab->current_scope;
  new_scope->next = 0;
  new_scope->rightmost = 0;

  new_scope->first_obj = 0;
  new_scope->last_obj = 0;
  new_scope->type = type;

  if(symtab->current_scope->rightmost)
    symtab->current_scope->rightmost->next = new_scope;

  symtab->current_scope = new_scope;
}

void SymtabCloseScope(Symtab* symtab){
  symtab->current_scope->outer->rightmost = symtab->current_scope;
  symtab->current_scope = symtab->current_scope->outer;
}

void SymtabInsert(Symtab* symtab, Obj* obj){
  ScopeInsert(symtab->current_scope, obj);
}

Obj* SymtabFind(Symtab* symtab, const char* symbol_name){
  for(Scope* scope = symtab->current_scope; scope; scope = scope->outer){
    Obj* obj = ScopeFind(scope, symbol_name);
    if(obj) return obj;
  } 
  return 0;
}

Obj* SymtabFindCurrentScope(Symtab* symtab, const char* symbol_name){
  return ScopeFind(symtab->current_scope, symbol_name);
}

void SymtabDrop(Symtab* symtab){
  Scope* global = symtab->current_scope;
  while(global && global->outer){
    global = global->outer;
  }

  Queue bfs_traversal = { 0, 0 };
  QueueInsert(&bfs_traversal, global);

  while(!QueueEmpty(&bfs_traversal)){
    global = (Scope*) QueueDelete(&bfs_traversal);

    ScopeDrop(global);

    free(global);
  }
}