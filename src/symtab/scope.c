#include "scope.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/queue.h"
#include "util/memory_safety.h"

Scope* ScopeCreateEmpty(){
  Scope* scope = malloc(sizeof(Scope));

  scope->outer = 0;
  
  scope->children.first = 0;
  scope->children.last = 0;

  scope->objs.first = 0;
  scope->objs.last = 0;

  scope->type = 0;

  scope_alloc++;

  return scope;
}

void ScopeDrop(Scope* scope){
  for(Node* node = scope->objs.first; node; node = node->next){
    ObjDrop(node->info);
  }

  LinkedListDelete(&scope->objs);

  for(Node* node = scope->children.first; node; node = node->next){
    ScopeDrop(node->info);
  }
  
  LinkedListDelete(&scope->children);

  free(scope);

  scope_free++;
}

extern int dump_indent;

extern void print_indent();

void ScopeDump(Scope* scope){
  static const char* scope_type_print[] = {
    [SCOPE_FUNCTION]        = "function",
    [SCOPE_FILE]            = "file",
    [SCOPE_BLOCK]           = "block",
    [SCOPE_FUNC_PROTOTYPE]  = "function prototype",
  };
  
  dump_indent++;

  print_indent();
  printf("Scope: %s [\n", scope_type_print[scope->type]);
  for(Node* node = scope->objs.first; node; node = node->next){
    Obj* obj = node->info;
    ObjDump(obj);
  }
  
  for(Node* node = scope->children.first; node; node = node->next){
    Scope* scope = node->info;
    ScopeDump(scope);
  }

  print_indent();
  printf("]\n");

  dump_indent--;
}

void ScopeInsert(Scope* scope, Obj* obj){
  Node* node = NodeCreateEmpty();
  node->info = obj;
  LinkedListInsertLast(&scope->objs, node);
}

Obj* ScopeFind(Scope* scope, const char* symbol_name){
  for(Node* node = scope->objs.first; node; node = node->next){
    Obj* obj = node->info;
    if(obj->name == 0) continue;
    if(strcmp(obj->name, symbol_name) == 0) return obj;
  }
  return 0;
}

Obj* ScopeFindNamespace(Scope* scope, const char* symbol_name, ObjNamespace namespace){
  for(Node* node = scope->objs.first; node; node = node->next){
    Obj* obj = node->info;
    if(obj->name == 0) continue;
    if(namespaces[obj->kind] != namespace) continue;
    if(strcmp(obj->name, symbol_name) == 0) return obj;
  }
  return 0;
}