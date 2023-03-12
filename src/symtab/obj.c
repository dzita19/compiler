#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include "util/memory_safety.h"

ObjNamespace namespaces[OBJ_KIND_COUNT] = {
  [OBJ_VAR]   = NAMESPACE_ORDINARY,
  [OBJ_TEMP]  = NAMESPACE_NONE,
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
  static const char* storage_class_print[] = {
    [NO_STORAGE_CLASS]  = "none",
    [TYPEDEF]           = "typedef",
    [EXTERN]            = "extern",
    [STATIC]            = "static",
    [AUTO]              = "auto",
    [REGISTER]          = "register",
  };

  static const char* tag_type_print[] = {
    [TAG_STRUCT]  = "struct",
    [TAG_UNION]   = "union",
    [TAG_ENUM]    = "enum",
  };

  static const char* obj_kind_print[] = {
    [OBJ_VAR]   = "variable",
    [OBJ_TEMP]  = "temporary",
    [OBJ_TYPE]  = "typedef",
    [OBJ_TAG]   = "tag",
    [OBJ_MEMB]  = "member",
    [OBJ_ENUM]  = "enumerator",
    [OBJ_LABEL] = "label",
  };
  
  dump_indent++;

  print_indent();
  printf("Obj: %s [\n", obj_kind_print[obj->kind]);

  dump_indent++;
  print_indent();
  printf("Name: %s; Address: %d; ", obj->name, obj->address);
  if(obj->kind == OBJ_VAR){
    printf("Storage class: %s; ", storage_class_print[obj->specifier]);
  }
  if(obj->kind == OBJ_TAG){
    printf("Tag type: %s; ", tag_type_print[obj->specifier]);
  }
  printf("\n");

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