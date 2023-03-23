#include "declarators.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static Struct* declarator_type = 0;

static int reserve_storage_stack(Struct* str){
  int addr = (current_stack_counter + str->align - 1) / str->align * str->align;
  current_stack_counter += str->size;
  return addr;
}

static int reserve_storage_struct(Struct* str, Struct* parent){
  int addr = (parent->size + str->align - 1) / str->align * str->align;
  if(parent->align < str->align) parent->align = str->align;
  parent->size = addr + str->size;
  return addr;
}

static int reserve_storage_union(Struct* str, Struct* parent){
  if(parent->align < str->align) parent->align = str->align;
  if(parent->size < str->size)   parent->size = str->size;
  return 0;
}

static Obj* define_object(int storage, int linkage){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found) {
    printf("ERROR: Identifier already defined.\n");
    return 0;
  }

  if(StructGetType(declarator_type) == TYPE_INCOMPLETE){
    printf("ERROR: Cannot instantiate incomplete type.\n");
    return 0;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = declarator_type;
  obj->specifier = storage | linkage | DEFINED;
  obj->name = name_frame->name;

  if(storage == STORAGE_AUTO) obj->address = reserve_storage_stack(obj->type);

  declarator_type = 0;
  name_frame->name = 0;
  SymtabInsert(symtab, obj);

  return obj;
}

static Obj* tentative_object(int linkage){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found) {
    if(obj_found->type != declarator_type){
      printf("ERROR: Identifier declared with different type.\n");
      return 0;
    }
    if((obj_found->specifier & LINKAGE_FETCH) != linkage){
      printf("ERROR: Identifier declared with different linkage.\n");
      return 0;
    }
    return obj_found;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = declarator_type;
  obj->specifier = STORAGE_STATIC | linkage | TENTATIVE;
  obj->name = name_frame->name;

  declarator_type = 0;
  name_frame->name = 0;
  SymtabInsert(symtab, obj);

  return obj;
}

static Obj* extern_object(){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found){
    if(obj_found->type != declarator_type){
      printf("ERROR: Identifier declared with different type.\n");
      return 0;
    }
    return obj_found;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = declarator_type;
  obj->specifier = STORAGE_STATIC | LINKAGE_EXTERNAL | DECLARED;
  obj->name = name_frame->name;

  declarator_type = 0;
  name_frame->name = 0;
  SymtabInsert(symtab, obj);

  return obj;
}

static Obj* declare_function(int linkage){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found){
    if(obj_found->type != declarator_type){
      printf("ERROR: Identifier declared with different type.\n");
      return 0;
    }
    if(obj_found->specifier & LINKAGE_FETCH != linkage){
      printf("ERROR: Identifier declared with different linkage.\n");
      return 0;
    }
    current_function_body = obj_found;

    return obj_found;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = declarator_type;
  obj->specifier = STORAGE_STATIC | linkage | DECLARED;
  obj->name = name_frame->name;

  declarator_type = 0;
  name_frame->name = 0;
  SymtabInsert(symtab, obj);
  current_function_body = obj;

  return obj;
}

static Obj* declarator_variable(int initialized){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  StorageClassSpecifier storage = type_frame->storage_specifier;

  switch(declarator_type->type){
  case TYPE_OBJECT:
    if(block_level == 0 && initialized){
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_INTERNAL);
      case EXTERN:
        printf("WARNING: Both extern keyword and initializer present.\n");
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);
      case NO_STORAGE_CLASS:
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);
      default:
        printf("ERROR: Illegal storage class specifier for file scope.\n");
        return 0;
      }
    }
    else if(block_level == 0 && !initialized){
      switch(storage){
      case STATIC:
        return tentative_object(LINKAGE_INTERNAL);
      case EXTERN:
        return extern_object();
      case NO_STORAGE_CLASS:
        return tentative_object(LINKAGE_EXTERNAL);
      default:
        printf("ERROR: Illegal storage class specifier for file scope.\n");
        return 0;
      }
    }
    else{
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_NONE);
      case EXTERN:
        if(initialized == 0) return extern_object();
        else{
          printf("ERROR: Illegal initialization of extern object in block scope.\n");
          return 0;
        }
        break;
      case NO_STORAGE_CLASS:
      case REGISTER:
      case AUTO:
        return define_object(STORAGE_AUTO, LINKAGE_NONE);
      default:
        printf("ERROR: Illegal storage class specifier for block scope.\n");
        return 0;
      }
    }
    break;

  case TYPE_FUNCTION:
    if(initialized){
      printf("ERROR: Function cannot be initialized.\n");
      return 0;
    }
    if(block_level == 0){
      switch(storage){
      case STATIC:
        return declare_function(LINKAGE_INTERNAL);
      case EXTERN:
      case NO_STORAGE_CLASS:
        return declare_function(LINKAGE_EXTERNAL);
      default:
        printf("ERROR: Illegal storage class specifier for function in file scope.\n");
        return 0;
      }
    }
    else{
      switch(storage){
      case EXTERN:
      case NO_STORAGE_CLASS:
        return declare_function(LINKAGE_EXTERNAL);
      default:
        printf("ERROR: Illegal storage class specifier for function in block scope.\n");
        return 0;
      }
    }
    break;
    
  case TYPE_INCOMPLETE:
    if(initialized){
      printf("ERROR: Incomplete type cannot be initialized.\n");
      return 0;
    }
    if(block_level == 0){
      switch(storage){
      case STATIC:
        return tentative_object(LINKAGE_INTERNAL);
      case EXTERN:
        return extern_object();
      case NO_STORAGE_CLASS:
        return tentative_object(LINKAGE_EXTERNAL);
      default:
        printf("ERROR: Illegal storage class specifier for file scope.\n");
        return 0;
      }
    }
    else{
      switch(storage){
      case EXTERN:
        return extern_object();
      default:
        printf("ERROR: Incomplete type cannot be initialized.\n");
      }
    }
    break;

  case TYPE_ARRAY_UNSPEC:
    if(block_level == 0 && initialized){
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_INTERNAL);
      case EXTERN:
        printf("WARNING: Both extern keyword and initializer present.\n");
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);
      case NO_STORAGE_CLASS:
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);\
      default:
        printf("ERROR: Illegal storage class specifier for file scope.\n");
        return 0;
      }
    }
    else if(block_level == 0 && !initialized){
      switch(storage){
      case STATIC:
        return tentative_object(LINKAGE_INTERNAL);
      case EXTERN:
        return extern_object();
      case NO_STORAGE_CLASS:
        return tentative_object(LINKAGE_EXTERNAL);
      default:
        printf("ERROR: Illegal storage class specifier for file scope.\n");
        return 0;
      }
    }
    else if(initialized) {
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_NONE);
      case EXTERN:
        printf("ERROR: Both extern keyword and initializer are present.\n");
        return 0;
      case NO_STORAGE_CLASS:
      case REGISTER:
      case AUTO:
        return define_object(STORAGE_AUTO, LINKAGE_NONE);
      default:
        printf("ERROR: Illegal keyword.\n");
        return 0;
      }
    }
    else{
      switch(storage){
      case EXTERN:
        return extern_object();
      default:
        printf("ERROR: Cannot instantiate incomplete type.\n");
        return 0;
    }
    break;
    }

  }

}

static Obj* declarator_parameter(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);
  LinkedList* parameter_frame = StackPeek(&parameter_stack);

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  parameter_frame = StackPeek(&parameter_stack); // StructProcessIndirections alters this stack !!!!!!
  Node* node = NodeCreateEmpty();
  node->info = declarator_type;
  LinkedListInsertLast(parameter_frame, node);

  StorageClassSpecifier storage = type_frame->storage_specifier;

  if(declarator_type->type == TYPE_FUNCTION){
    printf("ERROR: Function cannot be function parameter.\n");
    return 0;
  }

  if(storage != NO_STORAGE_CLASS && storage != REGISTER){
    printf("ERROR: Illegal storage class specifier for function parameter.\n");
    return 0;
  }

  if(fdef_counter > 0) return 0;

  Obj* obj_found = ScopeFindNamespace(current_param_scope, name_frame->name, NAMESPACE_ORDINARY);
  if(obj_found){
    printf("ERROR: Identifier already defined in this scope.\n");
    return 0;
  }
  
  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = declarator_type;
  obj->specifier = STORAGE_AUTO | LINKAGE_NONE | DEFINED;
  obj->name = name_frame->name;

  declarator_type = 0;
  name_frame->name = 0;
  ScopeInsert(current_param_scope, obj);

  return obj;
}

static Obj* declarator_typename(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);
  LinkedList* parameter_frame = StackPeek(&parameter_stack);

  extern Stack typename_stack;

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );
  
  StackPush(&typename_stack, declarator_type);
}

static Obj* declarator_member(){
  Obj* typedef_obj = StackPeek(&typedef_stack);
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  Obj* obj_found = SymtabFindMember(symtab, name_frame->name, typedef_obj);

  if(obj_found){
    printf("ERROR: Identifier already defined in this namespace.\n");
    return 0;
  }

  if(declarator_type->type == TYPE_FUNCTION){
    printf("ERROR: Function cannot be function parameter.\n");
    return 0;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_MEMB;
  obj->type = declarator_type;
  obj->specifier = DEFINED;
  obj->name = name_frame->name;
  obj->address = ((typedef_obj->specifier & TAG_FETCH) == TAG_STRUCT)
    ? reserve_storage_struct(obj->type, typedef_obj->type)
    : reserve_storage_union (obj->type, typedef_obj->type);

  declarator_type = 0;
  name_frame->name = 0;
  SymtabInsertMember(symtab, typedef_obj, obj);

  return obj;
}

static Obj* declarator_typedef(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  if(obj_found){
    if(obj_found->kind == OBJ_TYPE){
      printf("ERROR: Identifier already defined.\n");
      return 0;
    }
    else{
      printf("ERROR: Identifier already defined as object.\n");
      return 0;
    }
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_TYPE;
  obj->type = declarator_type;
  obj->specifier = DEFINED;
  obj->name = name_frame->name;

  declarator_type = 0;
  name_frame->name = 0;
  SymtabInsert(symtab, obj);

  return obj;
}

void IdentifierName(const char* name){
  NameFrame* name_frame = StackPeek(&name_stack);
  if(name_frame->name){
    StringDrop(name_frame->name);
  }
  name_frame->name = (char*)name;
}

void Declarator(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  if(type_frame->current_type == 0){
    printf("WARNING: No type specified (assumed int).\n");
    type_frame->current_type = SymtabFindPredefined(INT);
  }

  if(type_frame->storage_specifier == TYPEDEF){
    declarator_typedef();
  }
  else if(StackEmpty(&typedef_stack)){
    declarator_variable(0);
  }
  else if(StackPeek(&typedef_stack) == 0){
    declarator_parameter();
  }
  else{
    declarator_member();
  }

  if(name_frame->name){
    StringDrop(name_frame->name);
  }
  name_frame->name = 0;
}

void DeclaratorInitialized(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  if(type_frame->current_type == 0){
    printf("WARNING: No type specified (assumed int).\n");
    type_frame->current_type = SymtabFindPredefined(INT);
  }

  if(type_frame->storage_specifier == TYPEDEF){
    printf("ERROR: typedef identifier cannot be initialized.\n");
  }
  else if(StackEmpty(&typedef_stack)){
    declarator_variable(1);
  }

  if(name_frame->name){
    StringDrop(name_frame->name);
  }
  name_frame->name = 0;
}

void AbstractDeclarator(){
  TypeFrame* type_frame = StackPeek(&type_stack);

  if(type_frame->current_type == 0){
    printf("WARNING: No type specified (assumed int).\n");
    type_frame->current_type = SymtabFindPredefined(INT);
  }

  if(StackPeek(&typedef_stack) == 0){
    declarator_parameter();
  }
  else{
    declarator_typename();
  }
}

void EnumeratorDefault(){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found) {
    printf("ERROR: Identifier already defined.\n");
    return;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_ENUM;
  obj->address = current_enum_constant++;
  obj->type = predefined_types_struct + INT32_T;
  obj->specifier = DEFINED;
  obj->name = name_frame->name;

  name_frame->name = 0;
  SymtabInsert(symtab, obj);

} // empty
void EnumeratorCustom(){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found) {
    printf("ERROR: Identifier already defined.\n");
    return;
  }

  ConstExpr* const_expr = StackPop(&const_expr_stack);
  current_enum_constant = const_expr->value;
  ConstExprDrop(const_expr);

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_ENUM;
  obj->address = current_enum_constant++;
  obj->type = predefined_types_struct + INT32_T;
  obj->specifier = DEFINED;
  obj->name = name_frame->name;

  name_frame->name = 0;
  SymtabInsert(symtab, obj);
} // empty