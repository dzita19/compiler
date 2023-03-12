#include "struct.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util/memory_safety.h"

Struct* StructCreateEmpty(){
  Struct* str = malloc(sizeof(Struct));

  str->obj = 0;
  str->kind = 0;
  str->parent = 0;
  str->children.first = 0;
  str->children.last = 0;
  str->parameters.first = 0;
  str->parameters.last = 0;
  str->attributes = 0;

  struct_alloc++;
  
  return str;
}

void StructDrop(Struct* str){
  LinkedListDelete(&str->parameters);

  for(Node* child = str->children.first; child; child = child->next){
    StructDrop(child->info);
  }
  LinkedListDelete(&str->children);

  free(str);

  struct_free++;
}

extern int dump_indent;

extern void print_indent();

void StructDump(Struct* str){
  static const char* tag_type_print[] = {
    [TAG_STRUCT] = "struct",
    [TAG_UNION]  = "union",
    [TAG_ENUM]   = "enum",
  };

  switch(str->kind){
    case STRUCT_SCALAR:
      if(str->obj->kind == OBJ_TAG){
        printf("%s ", tag_type_print[str->obj->specifier]);
      }
      printf("%s", str->obj->name);
      break;
    case STRUCT_POINTER:
      printf("(*) to ");
      StructDump(str->parent);
      break;
    case STRUCT_ARRAY:
      if(str->attributes == 0) printf("[ ] of ");
      else printf("[%d]", str->attributes);
      StructDump(str->parent);
      break;
    case STRUCT_QUALIFIED:
      if(str->attributes == CONST) printf("const ");
      if(str->attributes == VOLATILE) printf("volatile ");
      if(str->attributes == (CONST | VOLATILE)) printf("const volatile ");
      StructDump(str->parent);
      break;
    case STRUCT_FUNCTION:
      printf("function(");
      for(Node* node = str->parameters.first; node; node = node->next){
        StructDump(node->info);
        if(node->next) printf(", ");
      }
      printf(") returning ");
      StructDump(str->parent);
      break;
  }
}

extern int dump_indent;
extern void print_indent();

void StructTreeDump(Struct* str){

  print_indent();
  StructDump(str);

  if(str->kind == STRUCT_SCALAR){
    for(Node* node = str->obj->members.first; node; node = node->next){
      if(node == str->obj->members.first) printf(": ");

      Obj* member = node->info;
      StructDump(member->type);
      printf(" %s", member->name);

      if(node != str->obj->members.last) printf(", ");
    }
  }
  printf("\n");

  dump_indent++;

  for(Node* child = str->children.first; child; child = child->next){
    StructTreeDump(child->info);
  }

  dump_indent--;
}

Indirection qualifiers_to_indirection[] = {
  [CONST]             = INDIRECTION_CONST,
  [VOLATILE]          = INDIRECTION_VOLATILE,
  [CONST | VOLATILE]  = INDIRECTION_CONST_VOLATILE
};

static Struct* DerivePointer(Struct* base_type){
  for(Node* node = base_type->children.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_POINTER) return derived;
  }

  Struct* pointer = StructCreateEmpty();
  pointer->kind = STRUCT_POINTER;
  pointer->parent = base_type;

  Node* node = NodeCreateEmpty();
  node->info = pointer;
  LinkedListInsertLast(&base_type->children, node);

  return pointer;
}

static Struct* DeriveFunction(Struct* base_type, LinkedList* parameters){
  for(Node* node = base_type->children.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind != STRUCT_FUNCTION) continue;
    
    int found = 1;
    for(Node* param1 = derived->parameters.first,
      * param2 = parameters->first;
      param1 || param2;
      param1 = param1->next,
      param2 = param2->next){
      
      if(param1 == 0 && param2 != 0
        || param1 != 0 && param2 == 0){
        found = 0;
        break;
      }

      //Struct* param1_struct = param1->info;
      //Struct* param2_struct = param2->info;

      if(param1->info != param2->info) {
        found = 0;
        break;
      } 
    }

    if(found) return derived;
  }

  Struct* function = StructCreateEmpty();
  function->kind = STRUCT_FUNCTION;
  function->parent = base_type;
  function->parameters = *LinkedListDuplicate(parameters);

  Node* node = NodeCreateEmpty();
  node->info = function;
  LinkedListInsertLast(&base_type->children, node);

  return function;
}

static Struct* DeriveArray(Struct* base_type, uint32_t length){
  for(Node* node = base_type->children.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_ARRAY
      && derived->attributes == length) return derived;
  }

  Struct* array = StructCreateEmpty();
  array->kind = STRUCT_ARRAY;
  array->parent = base_type;
  array->attributes = length;

  Node* node = NodeCreateEmpty();
  node->info = array;
  LinkedListInsertLast(&base_type->children, node);

  return array;
}

static Struct* DeriveQualified(Struct* base_type, uint8_t qualifiers){
  for(Node* node = base_type->children.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_QUALIFIED
      && derived->attributes == qualifiers) return derived;
  }

  Struct* qualified = StructCreateEmpty();
  qualified->kind = STRUCT_QUALIFIED;
  qualified->parent = base_type;
  qualified->attributes = qualifiers;

  Node* node = NodeCreateEmpty();
  node->info = qualified;
  LinkedListInsertLast(&base_type->children, node);

  return qualified;
}

static Struct* Derive(Struct* base_type, Indirection indirection, LinkedList* parameters){

  switch(indirection){
    case INDIRECTION_POINTER:
      return DerivePointer(base_type);

    case INDIRECTION_FUNCTION:
      if(base_type->kind == STRUCT_SCALAR && base_type->attributes != 0){
        printf("ERROR: Function returning incomplete type is not allowed./n");
        return 0;
      }
      if(base_type->kind == STRUCT_ARRAY){
        printf("ERROR: Function returning array is not allowed./n");
        return 0;
      }
      if(base_type->kind == STRUCT_FUNCTION){
        printf("ERROR: Function returning function is not allowed./n");
        return 0;
      }
      return DeriveFunction(base_type, parameters);

    case INDIRECTION_CONST:
      return DeriveQualified(base_type, CONST);

    case INDIRECTION_VOLATILE:
      return DeriveQualified(base_type, VOLATILE);

    case INDIRECTION_CONST_VOLATILE:
      return DeriveQualified(base_type, CONST | VOLATILE);

    case SEPARATOR_INACTIVE:
    case SEPARATOR_ACTIVE:
    case SEPARATOR_DISABLED:
      return base_type;

    default:
      if(base_type->kind == STRUCT_SCALAR && base_type->attributes != 0){
        printf("ERROR: Function returning incomplete type is not allowed./n");
        return 0;
      }
      if(base_type->kind == STRUCT_ARRAY && base_type->attributes == 0){
        printf("ERROR: Array of incomplete type is not allowed./n");
        return 0;
      }
      if(base_type->kind == STRUCT_FUNCTION){
        printf("ERROR: Array of functions is not allowed./n");
        return 0;
      }
      return DeriveArray(base_type, indirection);
  }

}

Struct* StructProcessIndirections(
  Struct* base_type,
  int base_type_qualifiers,
  LinkedList* indirections,
  Stack* parameters_stack
) {
  
  Struct* current_struct = base_type;
  if(base_type_qualifiers)
    current_struct = Derive(current_struct, qualifiers_to_indirection[base_type_qualifiers], 0);

  while(indirections->first){
    Node* indirection = LinkedListRemoveFirst(indirections);

    if((Indirection)indirection->info == INDIRECTION_FUNCTION){
      LinkedList* parameters = StackPop(parameters_stack);
      current_struct = Derive(current_struct, (Indirection)indirection->info, parameters);
      LinkedListDelete(parameters);
      free(parameters);
    }
    else{
      current_struct = Derive(current_struct, (Indirection)indirection->info, 0);
    }

    if(current_struct == 0) return 0;

    free(indirection);
  }

  return current_struct;

}