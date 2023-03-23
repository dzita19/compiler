#include "struct.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util/memory_safety.h"

#include "symtab.h"

const int POINTER_SIZE = 4;

Struct* StructCreateEmpty(){
  Struct* str = malloc(sizeof(Struct));

  str->obj = 0;
  str->kind = 0;
  str->parent = 0;
  str->derived = (LinkedList){ 0, 0 };
  str->parameters = (LinkedList){ 0, 0 };
  str->attributes = 0;
  str->size = 0;
  str->align = 0;

  struct_alloc++;
  
  return str;
}

void StructDrop(Struct* str){
  LinkedListDelete(&str->parameters);

  for(Node* child = str->derived.first; child; child = child->next){
    StructDrop(child->info);
  }
  LinkedListDelete(&str->derived);

  free(str);

  struct_free++;
}

extern int dump_indent;

extern void print_indent();

void StructDump(Struct* str){
  static const char* tag_type_print[] = {
    "no tag",
    "struct",
    "union",
    "enum",
  };

  if(str == 0) {
    printf("<error-type>");
    return;
  }

  switch(str->kind){
    case STRUCT_DIRECT:
      if(str->obj->kind == OBJ_TAG){
        printf("%s ", tag_type_print[(str->obj->specifier >> 2) & 3]);
      }
      printf("%s", str->obj->name);
      break;
    case STRUCT_POINTER:
      printf("(*) to ");
      StructDump(str->parent);
      break;
    case STRUCT_ARRAY:
      if(str->attributes == 0) printf("[ ] of ");
      else printf("[%d] of ", str->attributes);
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

  if(str->kind == STRUCT_DIRECT){
    for(Node* node = str->obj->members.first; node; node = node->next){
      if(node == str->obj->members.first) printf(": ");

      Obj* member = node->info;
      StructDump(member->type);
      printf(" %s (0x%04lX)", member->name, member->address);

      if(node != str->obj->members.last) printf(", ");
    }
  }
  printf("\n");

  dump_indent++;

  for(Node* child = str->derived.first; child; child = child->next){
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
  for(Node* node = base_type->derived.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_POINTER) return derived;
  }

  Struct* pointer = StructCreateEmpty();
  pointer->kind = STRUCT_POINTER;
  pointer->type = TYPE_OBJECT;
  pointer->parent = base_type;
  pointer->size = POINTER_SIZE;
  pointer->align = POINTER_SIZE;

  Node* node = NodeCreateEmpty();
  node->info = pointer;
  LinkedListInsertLast(&base_type->derived, node);

  return pointer;
}

static Struct* DeriveFunction(Struct* base_type, LinkedList* parameters){
  for(Node* node = base_type->derived.first; node; node = node->next){
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
  function->type = TYPE_FUNCTION;
  if(base_type->kind == STRUCT_QUALIFIED) function->parent = base_type->parent;
  else function->parent = base_type;
  function->parameters = LinkedListDuplicate(parameters);
  function->size = 0;
  function->align = 0;

  Node* node = NodeCreateEmpty();
  node->info = function;
  LinkedListInsertLast(&base_type->derived, node);

  return function;
}

static Struct* DeriveArray(Struct* base_type, uint32_t length){
  for(Node* node = base_type->derived.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_ARRAY
      && derived->attributes == length) return derived;
  }

  Struct* array = StructCreateEmpty();
  array->kind = STRUCT_ARRAY;
  array->type = length == 0 ? TYPE_ARRAY_UNSPEC : TYPE_OBJECT; 
  array->parent = base_type;
  array->attributes = length;
  array->size = base_type->size * length;
  array->align = base_type->align;

  Node* node = NodeCreateEmpty();
  node->info = array;
  LinkedListInsertLast(&base_type->derived, node);

  return array;
}

static Struct* DeriveQualified(Struct* base_type, uint8_t qualifiers){
  for(Node* node = base_type->derived.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_QUALIFIED
      && derived->attributes == qualifiers) return derived;
  }

  Struct* qualified = StructCreateEmpty();
  qualified->kind = STRUCT_QUALIFIED;
  qualified->type = base_type->type == TYPE_FUNCTION ? TYPE_FUNCTION : TYPE_OBJECT;
  qualified->parent = base_type;
  qualified->attributes = qualifiers;
  qualified->size = base_type->size;
  qualified->align = base_type->align;

  Node* node = NodeCreateEmpty();
  node->info = qualified;
  LinkedListInsertLast(&base_type->derived, node);

  return qualified;
}

static Struct* Derive(Struct* base_type, Indirection indirection, LinkedList* parameters){

  switch(indirection){
    case INDIRECTION_POINTER:
      return DerivePointer(base_type);

    case INDIRECTION_FUNCTION:
      if(base_type->kind == STRUCT_ARRAY){
        printf("ERROR: Function returning array is not allowed.\n");
        return 0;
      }
      if(base_type->kind == STRUCT_FUNCTION){
        printf("ERROR: Function returning function is not allowed.\n");
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
      if(base_type->kind == STRUCT_FUNCTION){
        printf("ERROR: Array of functions is not allowed.\n");
        return 0;
      }
      if(base_type->kind == STRUCT_ARRAY && base_type->attributes == 0){
        printf("ERROR: Array of incomplete type is not allowed.\n");
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
      LinkedListDrop(parameters);
    }
    else{
      current_struct = Derive(current_struct, (Indirection)indirection->info, 0);
    }

    if(current_struct == 0) return 0;

    NodeDrop(indirection);
  }

  return current_struct;

}

StructType StructGetType(Struct* str){
  while(1){
    if(str->kind == STRUCT_DIRECT){
      return str->type;
    }
    if(str->kind == STRUCT_POINTER){
      return TYPE_OBJECT;
    }
    if(str->kind == STRUCT_FUNCTION){
      if(str->kind == STRUCT_QUALIFIED) str = str->parent;
      if(str->kind == STRUCT_DIRECT) return str->type;
    }
    if(str->kind == STRUCT_ARRAY){
      if(str->attributes == 0) return TYPE_ARRAY_UNSPEC;
    }
    str = str->parent;
  }
}

Struct* StructGetUnqualified(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) return str->parent;
  else return str;
}

Struct* StructGetParentUnqualified(Struct* str){
  return StructGetUnqualified(str->parent);
}

Struct* StructStringLiteral(){
  return DerivePointer(DeriveQualified(predefined_types_struct + INT8_T, CONST));
}

Struct* StructVoidPtr(){
  return DerivePointer(predefined_types_struct + VOID_T);
}

Struct* StructToPtr(Struct* str){
  return DerivePointer(str);
}

Struct* StructArrayToPtr(Struct* array){
  return DerivePointer(array->parent);
}

Struct* StructFunctionToPtr(Struct* function){
  return DerivePointer(function);
}

Struct* StructQualify(Struct* str, int qualifiers){
  if(qualifiers == 0) return str;

  return DeriveQualified(str, qualifiers);
}

Struct* StructGetHigherRank(Struct* str1, Struct* str2){
  str1 = StructGetUnqualified(str1);
  str2 = StructGetUnqualified(str2);

  return str1 > str2 ? str1 : str2;
}

int StructIsVoid(Struct* str){
  return str == (predefined_types_struct + VOID_T);  
}

int StructIsInteger(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  for(int i = INT8_T; i < PREDEFINED_TYPES_COUNT; i++){
    if(str == predefined_types_struct + i) return 1;
  }
  return 0;
}

int StructIsArithmetic(Struct* str){
  return StructIsInteger(str);
}

int StructIsScalar(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return StructIsArithmetic(str) || str->kind == STRUCT_POINTER;
}

int StructIsPointer(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return str->kind == STRUCT_POINTER;
}

int StructIsFunctionPtr(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return str->kind == STRUCT_POINTER && str->parent->kind == STRUCT_FUNCTION;
}

int StructIsArray(Struct* str){
  return str->kind == STRUCT_ARRAY;
}

int StructIsAggregate(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return str->kind == STRUCT_ARRAY ||
    (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_STRUCT);
}

extern int StructIsStructOrUnion(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_STRUCT)
      || (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_UNION);
}

int StructIsModifiable(Struct* str){
  if(str->type == TYPE_INCOMPLETE) return 0;

  if(str->kind == STRUCT_ARRAY) return 0;

  if(str->kind == STRUCT_DIRECT){
    if(str->obj->kind == OBJ_TAG){
      for(Node* node = str->obj->members.first; node; node = node->next){
        Obj* member = node->info;
        if(!StructIsModifiable(member->type)) return 0;
      }
      return 1;
    }
  }

  if(str->kind == STRUCT_QUALIFIED) return str->attributes & CONST;
  
  else return 1;
}

extern int StructIsCastable(Struct* from, Struct* into){
  if(from->kind == STRUCT_QUALIFIED) from = from->parent;
  if(into->kind == STRUCT_QUALIFIED) into = into->parent;
  
  if(from == into) return 1;
  if(StructIsArithmetic(from) && StructIsArithmetic(into)) return 1;
  return 0;
}