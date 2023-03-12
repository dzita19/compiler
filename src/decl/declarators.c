#include "declarators.h"

void IdentifierName(const char* name){
  NameFrame* current_name_frame = StackPeek(&name_stack);
  current_name_frame->name = (char*)name;
}

void Declarator(){
  TypeFrame* current_type_frame = StackPeek(&type_stack);
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);
  NameFrame* current_name_frame = StackPeek(&name_stack);

  if(current_type_frame->current_type == 0){
    printf("WARNING: No type specified (assumed int).\n");
    current_type_frame->current_type = SymtabFindPredefined(INT);
  }

  if(StackEmpty(&typedef_stack)){
    Obj* obj = ObjCreateEmpty();
    obj->name = current_name_frame->name;
    obj->kind = OBJ_VAR;
    obj->type = StructProcessIndirections(
      current_type_frame->current_type->type, 
      current_type_frame->type_qualifiers,
      current_indirection_frame,
      &parameter_stack
    );
    obj->specifier = current_type_frame->storage_specifier;

    if(obj->type->kind == STRUCT_SCALAR && obj->type->attributes != 0){
      printf("Cannot instantiate incomplete type.\n");
      return;
    }
    SymtabInsert(symtab, obj);
  }
  else if(StackPeek(&typedef_stack) == 0){
    Obj* obj = ObjCreateEmpty();
    obj->name = current_name_frame->name;
    obj->kind = OBJ_VAR;
    obj->type = StructProcessIndirections(
      current_type_frame->current_type->type, 
      current_type_frame->type_qualifiers,
      current_indirection_frame,
      &parameter_stack
    ); // StructProcessIndirection alters parameter stack - it is fetched after the function!!!
    obj->specifier = current_type_frame->storage_specifier;
    if(obj->specifier != NO_STORAGE_CLASS && obj->specifier != REGISTER){
      printf("ERROR: Only register storage class allowed for function parameters.\n");
    }

    if(obj->type->attributes != 0){
      printf("ERROR: Cannot instantiate incomplete type.\n");
      return;
    }
    SymtabInsert(symtab, obj);

    LinkedList* current_parameter_frame = StackPeek(&parameter_stack);
    Node* parameter_node = NodeCreateEmpty();
    parameter_node->info = obj->type;
    LinkedListInsertLast(current_parameter_frame, parameter_node);
  }
  else{
    Obj* obj = ObjCreateEmpty();
    obj->name = current_name_frame->name;
    obj->kind = OBJ_MEMB;
    obj->type = StructProcessIndirections(
      current_type_frame->current_type->type, 
      current_type_frame->type_qualifiers,
      current_indirection_frame,
      &parameter_stack
    );

    if(obj->type->attributes != 0){
      printf("Cannot instantiate incomplete type.\n");
      return;
    }
    Obj* namespace_tag = StackPeek(&typedef_stack);
    SymtabInsertMember(symtab, namespace_tag, obj);
  }

  current_name_frame->name = 0;
}

void DeclaratorInitialized(){
  Declarator();
}

void AbstractDeclarator(){
  TypeFrame* current_type_frame = StackPeek(&type_stack);
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  if(current_type_frame->current_type == 0){
    printf("WARNING: No type specified (assumed int).\n");
    current_type_frame->current_type = SymtabFindPredefined(INT);
  }
  
  if(StackPeek(&typedef_stack) == 0){
    Struct* str = StructProcessIndirections(
      current_type_frame->current_type->type, 
      current_type_frame->type_qualifiers,
      current_indirection_frame,
      &parameter_stack
    ); // StructProcessIndirection alters parameter stack - it is fetched after the function!!!
    
    if(str->attributes != 0){
      printf("Cannot instantiate incomplete type.\n");
      return;
    }
    Node* parameter_node = NodeCreateEmpty();
    parameter_node->info = str;
    LinkedList* current_parameter_frame = StackPeek(&parameter_stack);
    LinkedListInsertLast(current_parameter_frame, parameter_node);
  }
}

void EnumeratorDefault(){
  NameFrame* current_name_frame = StackPeek(&name_stack);
  Obj* current_typedef_frame = StackPeek(&typedef_stack);

  Obj* obj = ObjCreateEmpty();
  obj->name = current_name_frame->name;
  obj->address = current_enum_constant++;
  obj->kind = OBJ_ENUM;
  obj->type = current_typedef_frame->type;

  SymtabInsert(symtab, obj);
}

void EnumeratorCustom(){
  NameFrame* current_name_frame = StackPeek(&name_stack);
  Obj* current_typedef_frame = StackPeek(&typedef_stack);

  Obj* obj = ObjCreateEmpty();
  obj->name = current_name_frame->name;
  obj->address = current_enum_constant++;
  obj->kind = OBJ_ENUM;
  obj->type = current_typedef_frame->type;

  SymtabInsert(symtab, obj);
}
