#include "symtab.h"

#include <stdio.h>
#include <stdlib.h>
#include "util/queue.h"
#include "util/memory_safety.h"

Symtab* SymtabCreateEmpty(){
  Symtab* symtab = malloc(sizeof(Symtab));
  symtab->current_scope = 0;

  symtab_alloc++;

  return symtab;
}

void SymtabDropPredefined(Symtab* symtab){
  for(int i = 0; i < sizeof(predefined_types_struct) / sizeof(*predefined_types_struct); i++){
    for(Node* node = predefined_types_struct[i].derived.first; node; node = node->next){
      StructDrop(node->info);
    }
    LinkedListDelete(&predefined_types_struct[i].derived);
  }
}

void SymtabDrop(Symtab* symtab){
  Scope* global = symtab->current_scope;
  while(global && global->outer){
    global = global->outer;
  }

  SymtabDropPredefined(symtab);
  ScopeDrop(global);

  free(symtab);

  symtab_free++;
}

int dump_indent = 0;

void print_indent(){
  for(int i = 0; i < dump_indent; i++) printf(" ");
}

static void SymtabDumpPredefined(){
  dump_indent++;
  print_indent();
  printf("Predefined types:\n");
  for(int i = 0; i < sizeof(predefined_types_struct) / sizeof(*predefined_types_struct); i++){
    StructTreeDump(predefined_types_struct + i);
  }
  dump_indent--;
}

void SymtabDump(Symtab* symtab){
  /*Scope* global_scope = symtab->current_scope;
  while(global_scope->outer){
    global_scope = global_scope->outer;
  }*/

  printf("Symtab: [\n");
  SymtabDumpPredefined();
  printf("\n");
  ScopeDump(symtab->current_scope);
  printf("]\n");
}

void SymtabOpenScope(Symtab* symtab, ScopeType type){
  Scope* new_scope = ScopeCreateEmpty();
  new_scope->outer = symtab->current_scope;
  new_scope->type = type;

  if(symtab->current_scope == 0){
    symtab->current_scope = new_scope;
    return;
  }

  Node* node = NodeCreateEmpty();
  node->info = new_scope;
  LinkedListInsertLast(&symtab->current_scope->children, node);

  symtab->current_scope = new_scope;
}

void SymtabCloseScope(Symtab* symtab){
  symtab->current_scope = symtab->current_scope->outer;
}

void SymtabInsertScope(Symtab* symtab, Scope* scope){
  scope->outer = symtab->current_scope;

  if(symtab->current_scope == 0){
    symtab->current_scope = scope;
    return;
  }

  Node* node = NodeCreateEmpty();
  node->info = scope;
  LinkedListInsertLast(&symtab->current_scope->children, node);

  symtab->current_scope = scope;
}

void SymtabRemoveCurrentScope(Symtab* symtab){
  Scope* outer = symtab->current_scope->outer;
  for(Node* node = outer->children.first; node; node = node->next){
    Scope* inner = node->info;
    if(inner == symtab->current_scope) {
      NodeDrop(LinkedListRemoveFrom(&outer->children, node));
      ScopeDrop(inner);
      break;
    }
  }
  symtab->current_scope = outer;
}

void SymtabInsert(Symtab* symtab, Obj* obj){
  ScopeInsert(symtab->current_scope, obj);
}

void SymtabInsertMember(Symtab* symtab, Obj* tag, Obj* obj){
  Node* node = NodeCreateEmpty();
  node->info = obj;

  LinkedListInsertLast(&tag->members, node);
}

Obj* SymtabFind(Symtab* symtab, const char* symbol_name){
  for(Scope* scope = symtab->current_scope; scope; scope = scope->outer){
    Obj* obj = ScopeFind(scope, symbol_name);
    if(obj) return obj;
  } 
  return 0;
}

Obj* SymtabFindNamespace(Symtab* symtab, const char* symbol_name, ObjNamespace namespace){
  for(Scope* scope = symtab->current_scope; scope; scope = scope->outer){
    Obj* obj = ScopeFindNamespace(scope, symbol_name, namespace);
    if(obj) return obj;
  } 
  return 0;
}

Obj* SymtabFindCurrentScope(Symtab* symtab, const char* symbol_name){
  return ScopeFind(symtab->current_scope, symbol_name);
}

Obj* SymtabFindCurrentScopeNamespace(Symtab* symtab, const char* symbol_name, ObjNamespace namespace){
  return ScopeFindNamespace(symtab->current_scope, symbol_name, namespace);
}

Obj* SymtabFindMember(Symtab* symtab, const char* symbol_name, Obj* tag_obj){
  return ObjFindMember(tag_obj, symbol_name);
}

Obj predefined_types_obj[PREDEFINED_TYPES_COUNT] = {
  [  VOID_T] = {   "void", OBJ_TYPE, 0, 0, predefined_types_struct +   VOID_T, { 0, 0 } },
  [  INT8_T] = {   "int8", OBJ_TYPE, 0, 0, predefined_types_struct +   INT8_T, { 0, 0 } },
  [ UINT8_T] = {  "uint8", OBJ_TYPE, 0, 0, predefined_types_struct +  UINT8_T, { 0, 0 } },
  [ INT16_T] = {  "int16", OBJ_TYPE, 0, 0, predefined_types_struct +  INT16_T, { 0, 0 } },
  [UINT16_T] = { "uint16", OBJ_TYPE, 0, 0, predefined_types_struct + UINT16_T, { 0, 0 } },
  [ INT32_T] = {  "int32", OBJ_TYPE, 0, 0, predefined_types_struct +  INT32_T, { 0, 0 } },
  [UINT32_T] = { "uint32", OBJ_TYPE, 0, 0, predefined_types_struct + UINT32_T, { 0, 0 } },
  [ INT64_T] = {  "int64", OBJ_TYPE, 0, 0, predefined_types_struct +  INT64_T, { 0, 0 } },
  [UINT64_T] = { "uint64", OBJ_TYPE, 0, 0, predefined_types_struct + UINT64_T, { 0, 0 } },
};

Struct predefined_types_struct[PREDEFINED_TYPES_COUNT] = {
  [  VOID_T] = { predefined_types_obj +   VOID_T, STRUCT_DIRECT, TYPE_INCOMPLETE, 0, { 0, 0 }, { 0, 0 }, 0, 0, 0 },
  [  INT8_T] = { predefined_types_obj +   INT8_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 1, 1 },
  [ UINT8_T] = { predefined_types_obj +  UINT8_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 1, 1 },
  [ INT16_T] = { predefined_types_obj +  INT16_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 2, 2 },
  [UINT16_T] = { predefined_types_obj + UINT16_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 2, 2 },
  [ INT32_T] = { predefined_types_obj +  INT32_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 4, 4 },
  [UINT32_T] = { predefined_types_obj + UINT32_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 4, 4 },
  [ INT64_T] = { predefined_types_obj +  INT64_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 4, 4 },
  [UINT64_T] = { predefined_types_obj + UINT64_T, STRUCT_DIRECT, TYPE_OBJECT,     0, { 0, 0 }, { 0, 0 }, 0, 4, 4 },
};

Obj* SymtabFindPredefined(uint32_t type_specifiers){
  switch(type_specifiers){
    case VOID:
      return predefined_types_obj + VOID_T;
    case CHAR:
    case SIGNED | CHAR:
      return predefined_types_obj + INT8_T;
    case UNSIGNED | CHAR:
      return predefined_types_obj + UINT8_T;
    case SHORT:
    case SIGNED | SHORT:
    case SHORT | INT:
    case SIGNED | SHORT | INT:
      return predefined_types_obj + INT16_T;
    case UNSIGNED | SHORT:
    case UNSIGNED | SHORT | INT:
      return predefined_types_obj + UINT16_T;
    case INT:
    case SIGNED:
    case SIGNED | INT:
    case LONG:
    case SIGNED | LONG:
    case LONG | INT:
    case SIGNED | LONG | INT:
      return predefined_types_obj + INT32_T;
    case UNSIGNED:
    case UNSIGNED | INT:
    case UNSIGNED | LONG:
    case UNSIGNED | LONG | INT:
      return predefined_types_obj + UINT32_T;
    default:
      return 0;
  }
}