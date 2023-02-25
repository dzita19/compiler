#include "scope.h"

void ScopeInsert(Scope* scope, Obj* obj){
  if(scope->last_obj)
    scope->last_obj->next = obj;
  else
    scope->first_obj = obj;
  scope->last_obj = obj;
}

Obj* ScopeFind(Scope* scope, const char* symbol_name){
  for(Obj* obj = scope->first_obj; obj; obj = obj->next){
    if(strcmp(obj->name, symbol_name) == 0){
      return obj;
    }
  }
  return 0;
}

void ScopeDrop(Scope* scope){
  while(scope->first_obj){
    scope->last_obj = scope->first_obj;
    scope->first_obj = scope->first_obj->next;

    ObjDrop(scope->last_obj);

    free(scope->last_obj);
  }
}