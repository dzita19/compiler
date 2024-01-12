#include "declarators.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static Struct* declarator_type = 0;

int reserve_storage_stack(Struct* str){
  int current_stack_counter = (int)(long)stack_frame_stack.top->info;

  int addr = (current_stack_counter + str->align - 1) / str->align * str->align + str->size;
  current_stack_counter = addr; // + str->size;

  stack_frame_stack.top->info = (void*)(long)current_stack_counter;
  return addr; // + str->size;
}

int reserve_unnamed_static(Struct* str){
  int addr = (current_static_counter + str->align - 1) / str->align * str->align;
  current_static_counter = addr + str->size;
  return addr;
}

int reserve_storage_struct(Struct* str, Struct* parent){
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

// define, with initializer list for static objects 
static Obj* define_object(int storage, int linkage){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);
  Obj* obj;
  int add_to_static_objs = 0;
  int add_to_label_names = 0;

  if(declarator_type->type == TYPE_INCOMPLETE){
    ReportError("Cannot instantiate incomplete type.");
    return 0;
  }

  if(obj_found) {
    if(obj_found->kind != OBJ_VAR){
      ReportError("Identifier %s declared as a different kind of symbol.", obj_found->name);
      return 0;
    }
    if(!StructIsCompatible(obj_found->type, declarator_type)){
      ReportError("Identifier %s declared with incompatible type.", obj_found->name);
      return 0;
    }

    if((obj_found->specifier & DEFINITION_FETCH) == DEFINED){
      ReportError("Identifier %s already defined.", obj_found->name);
      return 0;
    }
    if((obj_found->specifier & DEFINITION_FETCH) == TENTATIVE){
      if((obj_found->specifier & LINKAGE_FETCH) != linkage){
        ReportError("Identifier %s declared with different linkage.", obj_found->name);
        return 0; 
      }

      obj_found->specifier &= DEFINITION_CLEAR;
      obj_found->specifier |= DEFINED;
    }
    if((obj_found->specifier & DEFINITION_FETCH) == DECLARED){
      if((obj_found->specifier & LINKAGE_FETCH) != linkage){
        obj_found->specifier &= LINKAGE_CLEAR;
        obj_found->specifier |= linkage;
      }

      obj_found->specifier &= DEFINITION_CLEAR;
      obj_found->specifier |= DEFINED;

      add_to_static_objs = (storage == STORAGE_STATIC);
      add_to_label_names = (linkage != LINKAGE_NONE);
    }

    obj = obj_found;
    obj->type = StructComposite(obj_found->type, declarator_type);
    obj->specifier &= DEFINITION_CLEAR;
    obj->specifier |= DEFINED;
  }
  else{
    obj = ObjCreateEmpty();
    obj->kind = OBJ_VAR;
    obj->type = declarator_type;
    obj->specifier = storage | linkage | DEFINED;
    obj->name = name_frame->name;

    name_frame->name = 0;
    SymtabInsert(symtab, obj);

    add_to_static_objs = (storage == STORAGE_STATIC);
    add_to_label_names = (linkage != LINKAGE_NONE);
  }

  if(storage == STORAGE_AUTO) obj->address = reserve_storage_stack(obj->type);
  else if(linkage == LINKAGE_NONE) obj->address = reserve_unnamed_static(obj->type);

  if(add_to_static_objs){
    obj->init_vals = LinkedListCreateEmpty();

    Node* new_node = NodeCreateEmpty();
    new_node->info = obj;

    LinkedListInsertLast(&static_obj_list, new_node);

    // add to global names
    if((obj->specifier & LINKAGE_FETCH) == LINKAGE_EXTERNAL){
      Node* new_node = NodeCreateEmpty();
      new_node->info = StringDuplicate(obj->name);

      LinkedListInsertLast(&global_name_list, new_node);
    }
  }

  if(add_to_label_names){
    // add to label names
    Node* new_node = NodeCreateEmpty();
    new_node->info = StringDuplicate(obj->name);

    LinkedListInsertLast(&label_name_list, new_node);

    // remove from extern names (if exists)
    for(Node* node = extern_name_list.first; node; node = node->next){
      char* extern_name = node->info;
      if(strcmp(obj->name, extern_name) == 0) {
        StringDrop(extern_name);
        NodeDrop(LinkedListRemoveFrom(&extern_name_list, node));
        break;
      }
    }
  }


  declarator_type = 0;

  return obj;
}

// declared or maybe define, but no initializer list
static Obj* tentative_object(int linkage){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);
  Obj* obj;
  int add_to_static_objs = 0;
  int add_to_label_names = 0;

  if(declarator_type->type == TYPE_INCOMPLETE){
    ReportError("Cannot instantiate incomplete type.");
    return 0;
  }

  if(obj_found) {
    if(obj_found->kind != OBJ_VAR){
      ReportError("Identifier %s declared as a different kind of symbol.", obj_found->name);
      return 0;
    }
    if(!StructIsCompatible(obj_found->type, declarator_type)){
      ReportError("Identifier %s declared with different type.", obj_found->name);
      return 0;
    }
    if((obj_found->specifier & DEFINITION_FETCH) == DEFINED){
      ReportError("Identifier %s already defined.", obj_found->name);
      return 0;
    }
    if((obj_found->specifier & DEFINITION_FETCH) == TENTATIVE){
      if((obj_found->specifier & LINKAGE_FETCH) != linkage){
        ReportError("Identifier %s declared with different linkage.", obj_found->name);
        return 0; 
      }
    }
    if((obj_found->specifier & DEFINITION_FETCH) == DECLARED){
      if((obj_found->specifier & LINKAGE_FETCH) != linkage){
        obj_found->specifier &= LINKAGE_CLEAR;
        obj_found->specifier |= linkage;
      }

      obj_found->specifier &= DEFINITION_CLEAR;
      obj_found->specifier |= TENTATIVE;

      add_to_static_objs = 1;
      add_to_label_names = 1;
    }

    obj_found->type = StructComposite(obj_found->type, declarator_type);
    obj = obj_found;
  }
  else{
    obj = ObjCreateEmpty();
    obj->kind = OBJ_VAR;
    obj->type = declarator_type;
    obj->specifier = STORAGE_STATIC | linkage | TENTATIVE;
    obj->name = name_frame->name;

    declarator_type = 0;
    name_frame->name = 0;
    SymtabInsert(symtab, obj);

    add_to_static_objs = 1;
    add_to_label_names = 1;
  }

  if(add_to_static_objs){
    obj->init_vals = LinkedListCreateEmpty();

    Node* new_node = NodeCreateEmpty();
    new_node->info = obj;

    LinkedListInsertLast(&static_obj_list, new_node);

    // add to global names
    if((obj->specifier & LINKAGE_FETCH) == LINKAGE_EXTERNAL){
      Node* new_node = NodeCreateEmpty();
      new_node->info = StringDuplicate(obj->name);

      LinkedListInsertLast(&global_name_list, new_node);
    }
  }

  if(add_to_label_names){
    // add to label names
    Node* new_node = NodeCreateEmpty();
    new_node->info = StringDuplicate(obj->name);

    LinkedListInsertLast(&label_name_list, new_node);

    // remove from extern names (if exists)
    for(Node* node = extern_name_list.first; node; node = node->next){
      char* extern_name = node->info;
      if(strcmp(obj->name, extern_name) == 0) {
        StringDrop(extern_name);
        NodeDrop(LinkedListRemoveFrom(&extern_name_list, node));
        break;
      }
    }
  }
  

  return obj;
}

// declare, don't define
static Obj* extern_object(){
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found){
    if(!StructIsCompatible(obj_found->type, declarator_type)){
      ReportError("Identifier %s declared with different type.", obj_found->name);
      return 0;
    }

    obj_found->type = StructComposite(obj_found->type, declarator_type);
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

  int add_to_extern_objs = 1;

  // only one extern declaration per name
  for(Node* node = extern_name_list.first; node; node = node->next){
    char* extern_name = node->info;
    if(strcmp(extern_name, obj->name) == 0){
      add_to_extern_objs = 0;
      break;
    }
  }
  
  // no need for extern declaration if any static declaration generates the symbol
  for(Node* node = label_name_list.first; node; node = node->next){
    char* label_name = node->info;
    if(strcmp(label_name, obj->name) == 0){
      add_to_extern_objs = 0;
      break;
    }
  }

  if(add_to_extern_objs){
    Node* new_node = NodeCreateEmpty();
    new_node->info = StringDuplicate(obj->name);
    LinkedListInsertLast(&extern_name_list, new_node);
  }

  return obj;
}

static Obj* declare_function(int linkage){
  NameFrame* name_frame = StackPeek(&name_stack);

  Obj* obj_found = SymtabFindNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found){
    if(obj_found->kind != OBJ_VAR){
      ReportError("Identifier %s declared as a different kind of symbol.", obj_found->name);
      return 0;
    }
    if(!StructIsCompatible(obj_found->type, declarator_type)){
      ReportError("Identifier %s declared with different type.", obj_found->name);
      return 0;
    }
    if((obj_found->specifier & LINKAGE_FETCH) != linkage){
      ReportError("Identifier %s declared with different linkage.", obj_found->name);
      return 0;
    }
    if(StructIsNonprototype(obj_found->type) && StructIsPrototype(declarator_type)
        && (obj_found->specifier & DEFINITION_FETCH) == DEFINED){
      ReportError("Function prototype redeclaration after non-prototype definition (function %s).", obj_found->name);
      return 0;
    }

    latest_function_decl = obj_found;
    obj_found->type = StructComposite(obj_found->type, declarator_type);
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
  latest_function_decl = obj;

  int add_to_extern_objs = 1;

  // only one extern declaration per name
  for(Node* node = extern_name_list.first; node; node = node->next){
    char* extern_name = node->info;
    if(strcmp(extern_name, obj->name) == 0){
      add_to_extern_objs = 0;
      break;
    }
  }

  // no need for extern declaration if any static declaration generates the symbol
  for(Node* node = label_name_list.first; node; node = node->next){
    char* label_name = node->info;
    if(strcmp(label_name, obj->name) == 0){
      add_to_extern_objs = 0;
      break;
    }
  }

  if(add_to_extern_objs){
    Node* new_node = NodeCreateEmpty();
    new_node->info = StringDuplicate(obj->name);
    LinkedListInsertLast(&extern_name_list, new_node);
  }

  return obj;
}

static Obj* declarator_variable(int initialized){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);

  if(type_frame->current_type == 0) return 0;

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  StorageClassSpecifier storage = type_frame->storage_specifier;

  if(declarator_type == 0) return 0;

  switch(declarator_type->type){
  case TYPE_OBJECT:
    if(block_level == 0 && initialized){
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_INTERNAL);
      case EXTERN:
        ReportWarning("Both extern keyword and initializer present.");
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);
      case NO_STORAGE_CLASS:
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);
      default:
        ReportError("Illegal storage class specifier for file scope.");
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
        ReportError("Illegal storage class specifier for file scope.");
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
          ReportError("Illegal initialization of extern object in block scope.");
          return 0;
        }
        break;
      case NO_STORAGE_CLASS:
      case REGISTER:
      case AUTO:
        return define_object(STORAGE_AUTO, LINKAGE_NONE);
      default:
        ReportError("Illegal storage class specifier for block scope.");
        return 0;
      }
    }
    break;

  case TYPE_FUNCTION:
    if(initialized){
      ReportError("Function cannot be initialized.");
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
        ReportError("Illegal storage class specifier for function in file scope.");
        return 0;
      }
    }
    else{
      switch(storage){
      case EXTERN:
      case NO_STORAGE_CLASS:
        return declare_function(LINKAGE_EXTERNAL);
      default:
        ReportError("Illegal storage class specifier for function in block scope.");
        return 0;
      }
    }
    break;
    
  case TYPE_INCOMPLETE:
    if(initialized){
      ReportError("Incomplete type cannot be initialized.");
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
        ReportError("Illegal storage class specifier for file scope.");
        return 0;
      }
    }
    else{
      switch(storage){
      case EXTERN:
        return extern_object();
      default:
        ReportError("Incomplete type cannot be initialized.");
      }
    }
    break;

  case TYPE_ARRAY_UNSPEC:
    if(block_level == 0 && initialized){
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_INTERNAL);
      case EXTERN:
        ReportWarning("Both extern keyword and initializer present.");
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);
      case NO_STORAGE_CLASS:
        return define_object(STORAGE_STATIC, LINKAGE_EXTERNAL);\
      default:
        ReportError("Illegal storage class specifier for file scope.");
        return 0;
      }
    }
    else if(block_level == 0 && !initialized){
      switch(storage){
      case STATIC:
        return tentative_object(LINKAGE_INTERNAL);
      case NO_STORAGE_CLASS:
        return tentative_object(LINKAGE_EXTERNAL);
      case EXTERN:
        return extern_object();
      default:
        ReportError("Illegal storage class specifier for file scope.");
        return 0;
      }
    }
    else if(initialized) {
      switch(storage){
      case STATIC:
        return define_object(STORAGE_STATIC, LINKAGE_NONE);
      case EXTERN:
        ReportError("Both extern keyword and initializer are present.");
        return 0;
      case NO_STORAGE_CLASS:
      case REGISTER:
      case AUTO:
        return define_object(STORAGE_AUTO, LINKAGE_NONE);
      default:
        ReportError("Illegal keyword.");
        return 0;
      }
    }
    else{
      switch(storage){
      case EXTERN:
        return extern_object();
      default:
        ReportError("Cannot instantiate incomplete type.");
        return 0;
    }
    break;
    }

  }

  return 0;
}

static Obj* declarator_parameter(int abstract){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);
  LinkedList* parameter_frame = StackPeek(&parameter_stack);

  if(type_frame->current_type == 0) return 0;

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  if(declarator_type == 0) return 0;

  if(StructIsArray(declarator_type)){
    declarator_type = StructArrayToPtr(declarator_type);
  }

  parameter_frame = StackPeek(&parameter_stack); // StructProcessIndirections alters this stack !!!!!!
  Node* node = NodeCreateEmpty();
  node->info = declarator_type;
  LinkedListInsertLast(parameter_frame, node);

  StorageClassSpecifier storage = type_frame->storage_specifier;

  if(declarator_type->type == TYPE_FUNCTION){
    ReportError("Function cannot be function parameter.");
    return 0;
  }

  // if(declarator_type->type == TYPE_INCOMPLETE && !StructIsVoid(declarator_type)){
  //   ReportError("Incomplete type cannot be function parameter.");
  //   return 0;
  // }

  if(StructIsVoid(declarator_type) && !abstract){
    ReportError("Function cannot have named void parameter.");
    return 0;
  }

  if(storage != NO_STORAGE_CLASS && storage != REGISTER){
    ReportError("Illegal storage class specifier for function parameter.");
    return 0;
  }

  if(name_frame->name == 0) return 0; // do not add unnamed function parameters

  Scope* param_scope = StackPeek(&param_scope_stack);
  Obj* obj_found = ScopeFindNamespace(param_scope, name_frame->name, NAMESPACE_ORDINARY);
  if(obj_found){
    ReportError("Identifier already defined in this scope.");
    return 0;
  }
  
  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = declarator_type;
  obj->specifier = STORAGE_AUTO | LINKAGE_NONE | DEFINED;
  obj->name = name_frame->name;
  obj->address = 0; // address will be set when function body is entered (because of return address location)
  // obj->address = ArgPassAllocAddr(&declaration_arg_pass, obj->type);

  declarator_type = 0;
  name_frame->name = 0;
  ScopeInsert(param_scope, obj);
  // SymtabInsert(symtab, obj);

  return obj;
}

static Obj* redeclarator_parameter(void){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  if(type_frame->current_type == 0) return 0;

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  if(declarator_type == 0) return 0;

  if(StructIsArray(declarator_type)){
    declarator_type = StructArrayToPtr(declarator_type);
  }

  StorageClassSpecifier storage = type_frame->storage_specifier;

  if(declarator_type->type == TYPE_FUNCTION){
    ReportError("Function cannot be function parameter.");
    return 0;
  }

  if(declarator_type->type == TYPE_INCOMPLETE){
    ReportError("Incomplete type cannot be function parameter.");
    return 0;
  }

  if(StructIsVoid(declarator_type)){
    ReportError("Function cannot have named void parameter.");
    return 0;
  }

  if(storage != NO_STORAGE_CLASS && storage != REGISTER){
    ReportError("Illegal storage class specifier for function parameter.");
    return 0;
  }

  // if(fdef_counter > 0) return 0;
  // if(name_frame->name == 0) return 0; // do not add unnamed function parameters

  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);
  if(obj_found == 0){
    ReportError("Parameter %s not declared in this scope.", name_frame->name);
    return 0;
  }

  if(obj_found->type != 0){
    ReportError("Parameter %s already redeclared.", name_frame->name);
    return 0;
  }

  obj_found->type = declarator_type;
  obj_found->specifier = STORAGE_AUTO | LINKAGE_NONE | DEFINED;
  obj_found->address = 0; // address will be set when function body is entered (because of return address location)
  // obj_found->address = ArgPassAllocAddr(&declaration_arg_pass, obj_found->type);

  declarator_type = 0;

  return obj_found;
}

static Obj* declarator_member(){
  Obj* typedef_obj = StackPeek(&typedef_stack);
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  if(type_frame->current_type == 0) return 0;

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  if(declarator_type == 0) return 0;

  Obj* obj_found = SymtabFindMember(symtab, name_frame->name, typedef_obj);

  if(obj_found){
    ReportError("Identifier %s already defined in this namespace.", obj_found->name);
    return 0;
  }

  if(declarator_type->type == TYPE_ARRAY_UNSPEC){
    ReportError("Incomplete array cannot be struct member.");
    return 0;
  }

  if(declarator_type->type == TYPE_INCOMPLETE){
    ReportError("Incomplete object cannot be struct member.");
    return 0;
  }

  if(declarator_type->type == TYPE_FUNCTION){
    ReportError("Function cannot be struct member.");
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

  if(type_frame->current_type == 0) return 0;
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  if(declarator_type == 0) return 0;

  if(obj_found){
    if(obj_found->kind == OBJ_TYPE){
      ReportError("Identifier %s already defined.", obj_found->name);
      return 0;
    }
    else{
      ReportError("Identifier %s already defined as object.", obj_found->name);
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

static Obj* declarator_typename(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  LinkedList* indirection_frame = StackPeek(&indirection_stack);

  extern Stack typename_stack;

  if(type_frame->current_type == 0) return 0;

  declarator_type = StructProcessIndirections(
    type_frame->current_type->type,
    type_frame->type_qualifiers,
    indirection_frame,
    &parameter_stack
  );

  // no need to return - we should pass the NULL value to typename_stack
  // if(declarator_type == 0) return;
  
  StackPush(&typename_stack, declarator_type);

  return 0;
}

void IdentifierName(){
  NameFrame* name_frame = StackPeek(&name_stack);
  if(name_frame->name) StringDrop(name_frame->name);
  name_frame->name = QueueDelete(&identifier_queue);
}

void Declarator(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  if(type_frame->current_type == 0){
    if(type_frame->type_specifiers == 0) 
      ReportError("No type specified.");
    // else error is already detected
  }

  if(type_frame->storage_specifier == TYPEDEF){
    declarator_typedef();
  }
  else if(nonprototype_redecl == 1){
    redeclarator_parameter();
  }
  else if(StackEmpty(&typedef_stack)){
    declarator_variable(0);
  }
  else if(StackPeek(&typedef_stack) == 0){
    declarator_parameter(0);
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
    if(type_frame->type_specifiers == 0) 
      ReportError("No type specified.");
    // else error is already reported
  }

  if(type_frame->storage_specifier == TYPEDEF){
    ReportError("Typedef identifier cannot be initialized.");
  }
  else if(StackEmpty(&typedef_stack)){
    current_obj_definition = declarator_variable(1);
  }

  if(name_frame->name){
    StringDrop(name_frame->name);
  }
  name_frame->name = 0;
  type_frame->identifier_expected = 0;
}

void AbstractDeclarator(){
  TypeFrame* type_frame = StackPeek(&type_stack);

  if(type_frame->current_type == 0){
    if(type_frame->type_specifiers == 0) 
      ReportError("No type specified.");
    // else error is already reported
  }

  if(StackPeek(&typedef_stack) == 0){
    declarator_parameter(1);
  }
  else{
    declarator_typename();
  }
}

void NonprototypeParam(void){
  NameFrame* name_frame = StackPeek(&name_stack);

  if(StackSize(&param_scope_stack) > 1) {
    ReportError("Identifier list can only be used in function definition.");
    return;
  }

  Scope* param_scope = StackPeek(&param_scope_stack);
  Obj* obj_found = ScopeFindNamespace(param_scope, name_frame->name, NAMESPACE_ORDINARY);
  if(obj_found){
    ReportError("Identifier %s already defined in this scope.", obj_found->name);
    return;
  }
  
  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_VAR;
  obj->type = 0;
  obj->specifier = DECLARED;
  obj->name = name_frame->name;

  name_frame->name = 0;
  ScopeInsert(param_scope, obj);
  // SymtabInsert(symtab, obj);
}

void EnumeratorDefault(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(obj_found) {
    ReportError("Identifier %s already defined.", obj_found->name);
    return;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_ENUM;
  obj->address = current_enum_constant++;
  obj->type = type_frame->current_type->type;
  obj->specifier = DEFINED;
  obj->name = name_frame->name;

  name_frame->name = 0;
  SymtabInsert(symtab, obj);

}

void EnumeratorCustom(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);
    
  Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  ConstExpr* const_expr = StackPop(&const_expr_stack);
  if(const_expr->kind != VAL_ARITHM || !StructIsArithmetic(const_expr->type)){
    ReportError("Enumerator expression is not constant.");
    ConstExprDrop(const_expr);
    return;
  }
  current_enum_constant = const_expr->value;
  ConstExprDrop(const_expr);

  if(obj_found) {
    ReportError("Identifier %s already defined.", obj_found->name);
    return;
  }

  Obj* obj = ObjCreateEmpty();
  obj->kind = OBJ_ENUM;
  obj->address = current_enum_constant++;
  obj->type = type_frame->current_type->type;
  obj->specifier = DEFINED;
  obj->name = name_frame->name;

  name_frame->name = 0;
  SymtabInsert(symtab, obj);
}