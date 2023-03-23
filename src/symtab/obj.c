#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/memory_safety.h"

const int DECLARED          =   0 << 0,
          DEFINED           =   1 << 0,
          TENTATIVE         =   2 << 0;

const int TAG_NONE          =   0 << 2,
          TAG_STRUCT        =   1 << 2,
          TAG_UNION         =   2 << 2,
          TAG_ENUM          =   3 << 2;

const int STORAGE_STATIC    =   0 << 2,
          STORAGE_AUTO      =   1 << 2;

const int LINKAGE_NONE      =   0 << 3,
          LINKAGE_EXTERNAL  =   1 << 3,
          LINKAGE_INTERNAL  =   2 << 3;

const int DEFINITION_FETCH  =   3 << 0,
          TAG_FETCH         =   3 << 2,
          STORAGE_FETCH     =   1 << 2,
          LINKAGE_FETCH     =   3 << 3;

const int DEFINITION_CLEAR  = ~(3 << 0),
          TAG_CLEAR         = ~(3 << 2),
          STORAGE_CLEAR     = ~(1 << 2),
          LINKAGE_CLEAR     = ~(3 << 3);

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

  obj->name = 0;
  obj->kind = 0;
  obj->address = 0;
  obj->specifier = 0;
  obj->type = 0;
  obj->members.first = 0;
  obj->members.last = 0;

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
  printf("Name: %s; ", obj->name);
  if(obj->kind == OBJ_VAR){
    printf("Address: 0x%04lX; Definition: %s; Storage: %s; Linkage: %s;\n",
      obj->address,
      definition_print[(obj->specifier >> 0) & 3],
      storage_print   [(obj->specifier >> 2) & 1],
      linkage_print   [(obj->specifier >> 3) & 3]);
  }
  if(obj->kind == OBJ_ENUM){
    printf("Value: 0x%04lX;\n", obj->address);
  }
  if(obj->kind == OBJ_TAG){
    printf("Tag type: %s; Definition: %s; Size: 0x%04X; Align: 0x%04X\n",
      tag_type_print  [(obj->specifier >> 2) & 3],
      definition_print[(obj->specifier >> 0) & 3],
      obj->type->size, 
      obj->type->align);
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
  else{
    print_indent();
    printf("Type: [");

    StructDump(obj->type);
    
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