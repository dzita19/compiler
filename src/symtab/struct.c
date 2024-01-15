#include "struct.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util/memory_safety.h"
#include "util/logger.h"

#include "symtab.h"

// const int NONPROTOTYPE_FUNCTION   =  (1 << 0);
// const int ELLIPSIS_FUNCTION       =  (1 << 1);

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
      if(str->obj->name) printf("%s", str->obj->name);
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
      if(str->attributes & NONPROTOTYPE_FUNCTION) printf("<nonprototype>");
      else if(str->parameters.first == 0) printf("void");
      for(Node* node = str->parameters.first; node; node = node->next){
        StructDump(node->info);
        if(node->next) printf(", ");
      }
      if(str->attributes & ELLIPSIS_FUNCTION) printf(", ...");
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
      printf(" %s (%d)", member->name, member->address);

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
  if(base_type->kind == STRUCT_QUALIFIED) base_type = base_type->parent; // function cannot return qualified datatype

  int ellipsis = 0;
  if(parameters->last && parameters->last->info == 0){
    ellipsis = 1;
    NodeDrop(LinkedListRemoveLast(parameters));
  }

  for(Node* node = base_type->derived.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind != STRUCT_FUNCTION) continue;

    if(derived->attributes & NONPROTOTYPE_FUNCTION) continue;
    if((ellipsis && !(derived->attributes & ELLIPSIS_FUNCTION))
        || (!ellipsis && (derived->attributes & ELLIPSIS_FUNCTION))) continue;
    
    int found = 1;
    for(Node* param1 = derived->parameters.first,
      * param2 = parameters->first;
      param1 || param2;
      param1 = param1->next,
      param2 = param2->next){
      
      if(param1 == 0 || param2 == 0){
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
  function->attributes = ellipsis ? ELLIPSIS_FUNCTION : 0;

  Node* node = NodeCreateEmpty();
  node->info = function;
  LinkedListInsertLast(&base_type->derived, node);

  return function;
}

static Struct* DeriveNonprototype(Struct* base_type){
  if(base_type->kind == STRUCT_QUALIFIED) base_type = base_type->parent; // function cannot return qualified datatype

  for(Node* node = base_type->derived.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind != STRUCT_FUNCTION) continue;
    
    if(derived->attributes & NONPROTOTYPE_FUNCTION) return derived;
  }

  Struct* nonprototype = StructCreateEmpty();
  nonprototype->kind = STRUCT_FUNCTION;
  nonprototype->type = TYPE_FUNCTION;
  if(base_type->kind == STRUCT_QUALIFIED) nonprototype->parent = base_type->parent;
  else nonprototype->parent = base_type;
  nonprototype->attributes = NONPROTOTYPE_FUNCTION;

  Node* node = NodeCreateEmpty();
  node->info = nonprototype;
  LinkedListInsertLast(&base_type->derived, node);

  return nonprototype;
}

static Struct* DeriveArray(Struct* base_type, uint32_t length){
  for(Node* node = base_type->derived.first; node; node = node->next){
    Struct* derived = node->info;
    if(derived->kind == STRUCT_ARRAY
      && derived->attributes == length) return derived;
  }

  Struct* array = StructCreateEmpty();
  array->kind = STRUCT_ARRAY;
  array->type = base_type->type == TYPE_INCOMPLETE
    ? TYPE_INCOMPLETE
    : length == 0 ? TYPE_ARRAY_UNSPEC : TYPE_OBJECT;
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
  qualified->type = base_type->type;
  qualified->parent = base_type;
  qualified->attributes = qualifiers;
  qualified->size = base_type->size;
  qualified->align = base_type->align;

  Node* node = NodeCreateEmpty();
  node->info = qualified;
  LinkedListInsertLast(&base_type->derived, node);

  return qualified;
}

// ellipsis (if exists) is still included in parameter list - it should be skipped
static int MultipleVoidParams(LinkedList* parameters){
  int has_void = 0; // 0 - no param is processed, 1 - has a void param, 2 - has a non void param
  for(Node* node = parameters->first; node; node = node->next){
    Struct* current_param = node->info;
    if(current_param == 0) continue; // skip ellipsis
    if(has_void == 0)
      has_void = (current_param == predefined_types_struct + VOID_T) ? 1 : 2;
    else if(has_void == 1) return 1;
    else if(has_void == 2 && current_param == predefined_types_struct + VOID_T) return 1;
  }
  if(has_void == 1) NodeDrop(LinkedListRemoveFirst(parameters)); // removes only void param, ellipsis (if exists) stays
  return 0;
}

static Struct* Derive(Struct* base_type, Indirection indirection, LinkedList* parameters){

  if(parameters && MultipleVoidParams(parameters)){
    ReportError("Only one void parameter is allowed in prototyped function.");
    return 0;
  }

  switch(indirection){
    case INDIRECTION_POINTER:
      return DerivePointer(base_type);

    case INDIRECTION_FUNCTION:
      if(base_type->kind == STRUCT_ARRAY){
        ReportError("Function returning array is not allowed.");
        return 0;
      }
      if(base_type->kind == STRUCT_FUNCTION){
        ReportError("Function returning function is not allowed.");
        return 0;
      }
      return DeriveFunction(base_type, parameters);

    case INDIRECTION_NONPROTOTYPE:
      if(base_type->kind == STRUCT_ARRAY){
        ReportError("Function returning array is not allowed.");
        return 0;
      }
      if(base_type->kind == STRUCT_FUNCTION){
        ReportError("Function returning function is not allowed.");
        return 0;
      }
      return DeriveNonprototype(base_type);

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
        ReportError("Array of functions is not allowed.");
        return 0;
      }
      if(base_type->kind == STRUCT_ARRAY && base_type->attributes == 0){
        ReportError("Array of incomplete type is not allowed.");
        return 0;
      }
      return DeriveArray(base_type, indirection);
  }

}

static void StructDeriveCleanup(
  LinkedList* indirections,
  Stack* parameters_stack
){
  while(indirections->first){
    Node* indirection = LinkedListRemoveFirst(indirections);

    if((Indirection)indirection->info == INDIRECTION_FUNCTION)
      LinkedListDrop(StackPop(parameters_stack));

    NodeDrop(indirection);
  }
}

Struct* StructProcessIndirections(
  Struct* base_type,
  int base_type_qualifiers,
  LinkedList* indirections,
  Stack* parameters_stack
) {
  
  Struct* current_struct = base_type;

  if(current_struct == 0){
    StructDeriveCleanup(indirections, parameters_stack);
    return 0;
  }

  if(base_type_qualifiers)
    current_struct = Derive(current_struct, qualifiers_to_indirection[base_type_qualifiers], 0);

  while(indirections->first){
    Node* indirection = LinkedListRemoveFirst(indirections);

    if((Indirection)indirection->info == INDIRECTION_FUNCTION){
      LinkedList* parameters = StackPop(parameters_stack);
      current_struct = Derive(current_struct, (Indirection)indirection->info, parameters);
      LinkedListDrop(parameters);
    }
    else if((Indirection)indirection->info == INDIRECTION_NONPROTOTYPE){
      LinkedListDrop(StackPop(parameters_stack));
      current_struct = Derive(current_struct, (Indirection)indirection->info, 0);
    }
    else{
      current_struct = Derive(current_struct, (Indirection)indirection->info, 0);
    }

    NodeDrop(indirection);

    if(current_struct == 0) {
      StructDeriveCleanup(indirections, parameters_stack);
      return 0;
    }
  }

  return current_struct;

}

void StructCompleted(Struct* str){
  str->type = TYPE_OBJECT;
  for(Node* node = str->derived.first; node; node = node->next){
    Struct* derived = node->info;

    switch(derived->kind){
    case STRUCT_ARRAY: {
      derived->align = str->align;
      derived->size  = str->size * derived->attributes;
      if(derived->attributes != 0) StructCompleted(derived);
      else derived->type = TYPE_ARRAY_UNSPEC; // array of unspecified size cannot be completed
      break;
    }

    case STRUCT_QUALIFIED: {
      derived->align = str->align;
      derived->size  = str->size;
      StructCompleted(derived);
      break;
    }

    default: break;

    }

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
  // return DerivePointer(DeriveQualified(predefined_types_struct + INT8_T, CONST));
  return DerivePointer(predefined_types_struct + INT8_T);
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

Struct* StructGetHigherRank(Struct* str){
  str = StructGetUnqualified(str);

  if(!StructIsArithmetic(str)) return 0;
  
  if(StructIsEnum(str)) str = predefined_types_struct + INT32_T;
  int sign = (str - (predefined_types_struct + INT8_T - 1)) & 1;

  return sign
    ? predefined_types_struct + INT32_T
    : predefined_types_struct + UINT32_T;
}

Struct* StructGetExprIntType(Struct* str1, Struct* str2){
  int sign1 = (str1 - (predefined_types_struct + INT8_T - 1)) & 1;
  int sign2 = (str2 - (predefined_types_struct + INT8_T - 1)) & 1;

  int rank1 = str1 >= predefined_types_struct + INT32_T; // 0 if less than int, else 1
  int rank2 = str2 >= predefined_types_struct + INT32_T; // 0 if less than int, else 1
  
  // both are int rank
  if(rank1 == 1 && rank2 == 1){
    return sign1 && sign2 
      ? predefined_types_struct +  INT32_T 
      : predefined_types_struct + UINT32_T;
  }
  // first is higher rank
  else if(rank1 == 1){
    return sign1
      ? predefined_types_struct +  INT32_T 
      : predefined_types_struct + UINT32_T;
  }
  // second is higher rank
  else if(rank2 == 1){
    return sign2
      ? predefined_types_struct +  INT32_T 
      : predefined_types_struct + UINT32_T;
  }
  // both are below int rank
  else{
    return sign1 || sign2 
      ? predefined_types_struct +  INT32_T 
      : predefined_types_struct + UINT32_T;
  }
}

Struct* StructArrayLengthSpecification(Struct* str, uint32_t length){
  if(str->type != TYPE_ARRAY_UNSPEC) return 0;
  
  return DeriveArray(str->parent, length);
}

int StructIsVoid(Struct* str){
  return str == (predefined_types_struct + VOID_T);  
}

int StructIsVoidPtr(Struct* str){
  return str == StructVoidPtr();
}

/*int StructIsInteger(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  for(int i = INT8_T; i < PREDEFINED_TYPES_COUNT; i++){
    if(str == predefined_types_struct + i) return 1;
  }
  return 0;
}*/

int StructIsInteger(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;

  return (str >= predefined_types_struct + INT8_T && str < predefined_types_struct + PREDEFINED_TYPES_COUNT)
    || StructIsEnum(str);

  return 0;
}

int StructIsArithmetic(Struct* str){
  return StructIsInteger(str);
}

int StructIsChar(Struct* str){
  return str == predefined_types_struct + INT8_T;
}

int StructIsScalar(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return StructIsArithmetic(str) || str->kind == STRUCT_POINTER;
}

int StructIsPointer(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return str->kind == STRUCT_POINTER;
}

int StructIsPointerToObject(Struct* str){
  return StructIsPointer(str) && str->parent->type == TYPE_OBJECT;
}

int StructIsFunctionPtr(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return str->kind == STRUCT_POINTER && str->parent->kind == STRUCT_FUNCTION;
}

int StructIsArray(Struct* str){
  return str->kind == STRUCT_ARRAY;
}

int StructIsFunction(Struct* str){
  return str->kind == STRUCT_FUNCTION;
}

int StructIsPrototype(Struct* str){
  return (str->kind == STRUCT_FUNCTION) && !(str->attributes & NONPROTOTYPE_FUNCTION);
}

int StructIsNonprototype(Struct* str){
  return (str->kind == STRUCT_FUNCTION) &&  (str->attributes & NONPROTOTYPE_FUNCTION);
}

int StructIsAggregate(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return str->kind == STRUCT_ARRAY ||
    (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_STRUCT);
}

int StructIsStruct(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_STRUCT);
}

int StructIsUnion(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_UNION);
}

int StructIsStructOrUnion(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_STRUCT)
      || (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_UNION);
}

int StructIsEnum(Struct* str){
  if(str->kind == STRUCT_QUALIFIED) str = str->parent;
  return (str->kind == STRUCT_DIRECT && str->obj->kind == OBJ_TAG && (str->obj->specifier & TAG_FETCH) == TAG_ENUM);
}

int StructIsModifiable(Struct* str){
  if(str->type == TYPE_INCOMPLETE) return 0;

  if(str->kind == STRUCT_ARRAY) return 0;

  if(str->kind == STRUCT_DIRECT){
    if(str->obj->kind == OBJ_TAG){
      for(Node* node = str->obj->members.first; node; node = node->next){
        Obj* member = node->info;
        // arrays in structs are modifiable if their base type is modifiable
        if(member->type->kind == STRUCT_ARRAY && !StructIsModifiable(member->type->parent)) return 0; 
        if(member->type->kind != STRUCT_ARRAY && !StructIsModifiable(member->type)) return 0;
      }
      return 1;
    }
  }

  if(str->kind == STRUCT_QUALIFIED) return (str->attributes & CONST) == 0;
  
  return 1;
}

int StructIsCastable(Struct* from, Struct* into){
  if(from->kind == STRUCT_QUALIFIED) from = from->parent;
  if(into->kind == STRUCT_QUALIFIED) into = into->parent;
  
  if(from == into) return 1;
  if(StructIsArithmetic(from) && StructIsArithmetic(into)) return 1;
  return 0;
}

int StructIsCompatible(Struct* str1, Struct* str2){
  if(str1 == str2) return 1;
  
  if(str1->kind == STRUCT_ARRAY && str2->kind == STRUCT_ARRAY
      && str1->parent == str2->parent){ // qualified array don't exist - it's ok to take parent (not parent unqualified)
    if(str1->attributes == 0 || str2->attributes == 0) return 1;
  }

  if(str1->kind == STRUCT_FUNCTION && str2->kind == STRUCT_FUNCTION 
      && str1->parent == str2->parent){ // qualified functions don't exist - it's ok to take parent (not parent unqualified)
    
    if((str1->attributes & NONPROTOTYPE_FUNCTION)
        || (str2->attributes & NONPROTOTYPE_FUNCTION)) return 1;

    if(str1->attributes == str2->attributes){
      for(Node* param1 = str1->parameters.first, *param2 = str2->parameters.first; 
          param1 || param2; 
          param1 = param1->next, param2 = param2->next){
        if(param1 == 0 || param2 == 0) return 0;

        if(!StructIsCompatible(param1->info, param2->info)) return 0;
      }

      return 1;
    }
  }

  if(str1->kind == STRUCT_POINTER && str2->kind == STRUCT_POINTER){
    return StructIsCompatible(str1->parent, str2->parent);
  }

  return 0;
}

int StructIsCompatibleUnqualified(Struct* str1, Struct* str2){
  return StructIsCompatible(StructGetUnqualified(str1), StructGetUnqualified(str2));
}

// return 0 if error
// don't call for incompatible structs
Struct* StructComposite(Struct* str1, Struct* str2){
  if(str1 == str2) return str1;

  if(str1->kind == STRUCT_ARRAY && str2->kind == STRUCT_ARRAY
      && str1->parent == str2->parent){
    if(str1->attributes == 0) return str2;
    if(str2->attributes == 0) return str1;
  }

  if(str1->kind == STRUCT_FUNCTION && str2->kind == STRUCT_FUNCTION
      && str1->parent == str2->parent){
    
    if(str1->attributes & NONPROTOTYPE_FUNCTION) return str2;
    if(str2->attributes & NONPROTOTYPE_FUNCTION) return str1;

    if(str1->attributes == str2->attributes){ // if both have ellipsis

      LinkedList* param_list = LinkedListCreateEmpty();
      for(Node* param1 = str1->parameters.first, *param2 = str2->parameters.first; 
          param1 || param2; 
          param1 = param1->next, param2 = param2->next){
        
        Struct* composite_param = StructComposite(param1->info, param2->info);
        Node* node = NodeCreateEmpty();
        node->info = composite_param;
        LinkedListInsertLast(param_list, node);
      }
      Struct* composite = DeriveFunction(str1->parent, param_list);
      LinkedListDrop(param_list);

      return composite;
    }
  }

  if(str1->kind == STRUCT_POINTER && str2->kind == STRUCT_POINTER){
    return DerivePointer(StructComposite(str1->parent, str2->parent));
  }

  return 0;
}

AssignStatus  StructIsAssignable(Struct* dst, Struct* src, int src_is_null_ptr){
  dst = StructGetUnqualified(dst);
  src = StructGetUnqualified(src);

  if(StructIsArithmetic(dst) && StructIsArithmetic(src)){
    return ASSIGN_OK;
  }
  else if(StructIsStructOrUnion(dst) && StructIsStructOrUnion(src)
      && StructIsCompatible(dst, src)){
    return ASSIGN_OK;
  }
  else if(StructIsPointer(dst) && StructIsPointer(src)){
    Struct* pointed_src = StructGetParentUnqualified(dst);
    Struct* pointed_dst = StructGetParentUnqualified(src);

    if(StructIsCompatible(pointed_src, pointed_dst)){
      return ASSIGN_OK;
    }
    else if(StructIsVoid(pointed_src)){ // maybe shouldn't
      return ASSIGN_OK;
    }
    else if(StructIsVoid(pointed_dst)) {
      return ASSIGN_OK;
    }
    else {
      return ASSIGN_ERROR_POINTER_INCOMPATIBLE;
    }

    int qualifiers_dst = dst->parent->kind == STRUCT_QUALIFIED ? dst->parent->attributes : 0;
    int qualifiers_src = src->parent->kind == STRUCT_QUALIFIED ? src->parent->attributes : 0;

    if(qualifiers_dst != (qualifiers_dst | qualifiers_src)){
      return ASSIGN_ERROR_POINTER_QUALIFICATION;
    }
  }
  else if(StructIsPointer(dst) && src_is_null_ptr){
    return ASSIGN_OK;
  }
  else {
    return ASSIGN_ERROR_INCOMPATIBLE_TYPES;
  }
}

AssignStatus StructIsPassable(Struct* param, Struct* arg, int arg_is_null_ptr){
  param = StructGetUnqualified(param);
  arg   = StructGetUnqualified(arg);

  if(StructIsArithmetic(param) && StructIsArithmetic(arg)){
    return ASSIGN_OK;
  }
  else if(StructIsStructOrUnion(param) && StructIsStructOrUnion(arg)
      && StructIsCompatible(param, arg)){
    return ASSIGN_OK;
  }
  else if(StructIsPointer(param) && StructIsPointer(arg)){
    Struct* pointed_param = StructGetParentUnqualified(param);
    Struct* pointed_arg   = StructGetParentUnqualified(arg);
    
    if(StructIsCompatible(pointed_param, pointed_arg)){
      return ASSIGN_OK;
    }
    else if(StructIsVoid(pointed_arg)) {
      return ASSIGN_OK;
    }
    else if(StructIsVoid(pointed_param)){
      return ASSIGN_OK;
    }
    else {
      return ASSIGN_ERROR_POINTER_INCOMPATIBLE;
    }

    int qualifiers_param = param->parent->kind == STRUCT_QUALIFIED ? param->parent->attributes : 0;
    int qualifiers_arg   = arg->parent->kind   == STRUCT_QUALIFIED ? arg->parent->attributes   : 0;

    if(qualifiers_param != (qualifiers_param | qualifiers_arg)){
      return ASSIGN_ERROR_POINTER_QUALIFICATION;
    }
  }
  else if(StructIsPointer(param) && arg_is_null_ptr){
    return ASSIGN_OK;
  }
  else {
    return ASSIGN_ERROR_INCOMPATIBLE_TYPES;
  }
}