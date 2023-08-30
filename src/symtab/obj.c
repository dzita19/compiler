#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/memory_safety.h"

#include "static_val.h"

ObjNamespace namespaces[OBJ_KIND_COUNT] = {
  [OBJ_VAR]   = NAMESPACE_ORDINARY,
  [OBJ_TYPE]  = NAMESPACE_ORDINARY,
  [OBJ_TAG]   = NAMESPACE_TAG,
  [OBJ_MEMB]  = NAMESPACE_MEMBER,
  [OBJ_ENUM]  = NAMESPACE_ORDINARY,
  [OBJ_LABEL] = NAMESPACE_LABEL,
};

Obj* ObjCreateEmpty(){
  Obj* obj = malloc(sizeof(Obj));

  obj->name      = 0;
  obj->kind      = 0;
  obj->address   = 0;
  obj->specifier = 0;
  obj->type      = 0;
  obj->members   = (LinkedList){ 0, 0 };
  obj->init_vals = 0;

  obj_alloc++;

  return obj;
}

void ObjDrop(Obj* obj){
  if(obj->kind == OBJ_TAG) StructDrop(obj->type);

  if(obj->name) {
    StringDrop(obj->name);
  }

  for(Node* node = obj->members.first; node; node = node->next){
    ObjDrop(node->info);
  }
  LinkedListDelete(&obj->members);

  if(obj->init_vals){
    for(Node* node = obj->init_vals->first; node; node = node->next){
      StaticValDrop(node->info);
    }
    LinkedListDrop(obj->init_vals);
  }

  free(obj);

  obj_free++;
}

extern int dump_indent;

extern void print_indent();

void ObjDump(Obj* obj){

  static const char* obj_kind_print[] = {
    [OBJ_VAR]   = "variable",
    [OBJ_TYPE]  = "typedef",
    [OBJ_TAG]   = "tag",
    [OBJ_MEMB]  = "member",
    [OBJ_ENUM]  = "enumerator",
    [OBJ_LABEL] = "label",
  };

  static const char* definition_print[] = {
    "declared",
    "defined",
    "tentative",
  };

  static const char* tag_type_print[] = {
    "no tag",
    "struct",
    "union",
    "enum",
  };

  static const char* storage_print[] = {
    "static",
    "auto",
  };

  static const char* linkage_print[] = {
    "none",
    "external",
    "internal",
  };
  
  dump_indent++;

  print_indent();
  printf("Obj: %s [\n", obj_kind_print[obj->kind]);

  dump_indent++;
  print_indent();
  if(obj->name) printf("Name: %s; ", obj->name);
  else printf("Name: $empty; ");

  if(obj->kind == OBJ_VAR){
    if(obj->address >= 0) printf("Address: %d; ",  +obj->address);
    else                  printf("Address: -%d; ", -obj->address);
    printf("Definition: %s; Storage: %s; Linkage: %s;\n",
      definition_print[(obj->specifier >> 0) & 3],
      storage_print   [(obj->specifier >> 2) & 1],
      linkage_print   [(obj->specifier >> 3) & 3]);
  }
  else if(obj->kind == OBJ_ENUM){
    if(obj->address >= 0) printf("Value: %d;\n",  +obj->address);
    else                  printf("Value: -%d;\n", -obj->address);
  }
  else if(obj->kind == OBJ_TAG){
    printf("Tag type: %s; Definition: %s; Size: %d; Align: %d\n",
      tag_type_print  [(obj->specifier >> 2) & 3],
      definition_print[(obj->specifier >> 0) & 3],
      obj->type->size, 
      obj->type->align);
  }
  else if(obj->kind == OBJ_LABEL){
    printf("Definition: %s;\n", definition_print[(obj->specifier >> 0) & 3]);
  }
  else{
    printf("\n");
  }

  if(obj->kind == OBJ_TAG){
    print_indent();
    printf("Type: [\n");

    dump_indent++;
    StructTreeDump(obj->type);
    dump_indent--;

    print_indent();
    printf("]\n");
  }
  else if(obj->kind != OBJ_LABEL){
    print_indent();
    printf("Type: [");

    StructDump(obj->type);
    
    printf("]\n");
  }

  if(obj->init_vals){
    print_indent();
    printf("Initialized to:[\n");

    dump_indent++;
    for(Node* node = obj->init_vals->first; node; node = node->next){
      print_indent();
      StaticValDump(node->info);
      printf("\n");
    }
    dump_indent--;
    
    print_indent();
    printf("]\n");
  }

  dump_indent--;

  print_indent();
  printf("]\n");

  dump_indent--;
}

extern Obj* ObjFindMember(Obj* obj, const char* symbol_name){
  for(Node* node = obj->members.first; node; node = node->next){
    Obj* member = node->info;
    if(strcmp(member->name, symbol_name) == 0) return member;
  }
  return 0;
}