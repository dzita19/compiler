#include "specifiers.h"

void Declaration(){
  TypeFrameClear(StackPeek(&type_stack));
}

void DeclarationSpecifiers(){
  TypeFrame* current_type_frame = StackPeek(&type_stack);

  current_type_frame->type_qualifiers = current_qualifiers;
  current_qualifiers = 0;
}

void StorageClassSpecifierRef(StorageClassSpecifier specifier){
  TypeFrame* current_type_frame = StackPeek(&type_stack);

  if(current_type_frame->storage_specifier != NO_STORAGE_CLASS){
    printf("ERROR: Multiple storage class specifiers.\n");
    return;
  }

  current_type_frame->storage_specifier = specifier;
}

void TypeSpecifierRef(TypeSpecifier specifier){
  TypeFrame* current_type_frame = StackPeek(&type_stack);

  if(current_type_frame->type_specifiers & specifier){
    printf("ERROR: Duplicate specifier in declaration.\n");
    return;
  }

  current_type_frame->type_specifiers |= specifier;
  if(current_type_frame->type_specifiers & CUSTOM_TYPE) {
    if(current_type_frame->type_qualifiers & ~CUSTOM_TYPE) {
      printf("ERROR: Illegal combination of type specifier(s) and custom type.\n");
      return;
    }

    NameFrame* current_name_frame = StackPeek(&name_stack);
    
    // tagged types are processed in specialized fuctions: tag named def, tag named decl, tag anonymous def
    if(current_name_frame->type == TAG_NONE){
      Obj* type_ref = SymtabFindNamespace(symtab, current_name_frame->name, NAMESPACE_ORDINARY);

      if(type_ref->kind != OBJ_TYPE){
        printf("ERROR: Referenced symbol does not designate type.\n");
        return;
      }
      
      current_type_frame->current_type = type_ref;
    }

    NameFrameClear(current_name_frame);
  }
  else{
    current_type_frame->current_type = SymtabFindPredefined(current_type_frame->type_specifiers);

    if(current_type_frame == 0){
      printf("ERROR: Illegal combination of type specifiers.\n");
      return;
    }
  }
}

void TypeQualifierRef(TypeQualifier qualifier){
  current_qualifiers |= qualifier;
}

void TagTypeRef(TagType type){
  NameFrame* current_name_frame = StackPeek(&name_stack);
  current_name_frame->type = type;
}

void TagDefOpen(){
  NameFrame* current_name_frame = StackPeek(&name_stack);
  Obj* declaration = SymtabFindCurrentScopeNamespace(symtab, current_name_frame->name, NAMESPACE_TAG);

  // if already declared, then obj and struct are already allocated
  if(declaration){
    if(declaration->specifier != current_name_frame->type){
      printf("ERROR: Invalid tag type in declaration.\n");
      return;
    }

    if(declaration->type->attributes == 0){
      printf("ERROR: Illegal redefinition of struct tag.\n");
      return;
    }

    if(declaration->type->attributes == 2){
      printf("ERROR: Nested redefinition of struct tag.\n");
      return;
    }

    StackPush(&typedef_stack, declaration);
  }
  else{
    Obj* tag_obj = ObjCreateEmpty();
    tag_obj->name = current_name_frame->name;
    tag_obj->kind = OBJ_TAG;
    tag_obj->specifier = current_name_frame->type;

    Struct* tag_str = StructCreateEmpty();
    tag_str->obj = tag_obj;
    tag_str->kind = STRUCT_SCALAR;
    tag_str->attributes = 2; // currently defined

    tag_obj->type = tag_str;

    SymtabInsert(symtab, tag_obj);
    
    StackPush(&typedef_stack, tag_obj);
  }

  StackPush(&name_stack, NameFrameCreateEmpty());
}

void TagDefClose(){
  StackPop(&name_stack);
}

void TagNamedDef(){
  Obj* str_defined = StackPop(&typedef_stack);

  NameFrame* current_name_frame = StackPeek(&name_stack);
  TypeFrame* current_type_frame = StackPeek(&type_stack);
  current_type_frame->current_type = str_defined;
  current_type_frame->current_type->type->attributes = 0; // completed
}

void TagNamedDecl(){
  TypeFrame* current_type_frame = StackPeek(&type_stack);
  NameFrame* current_name_frame = StackPeek(&name_stack);

  Obj* obj_ref = SymtabFindNamespace(symtab, current_name_frame->name, NAMESPACE_TAG);

  if(obj_ref == 0){
    Obj* tag_obj = ObjCreateEmpty();
    tag_obj->name = current_name_frame->name;
    tag_obj->kind = OBJ_TAG;
    tag_obj->specifier = current_name_frame->type;

    Struct* tag_str = StructCreateEmpty();
    tag_str->obj = tag_obj;
    tag_str->kind = STRUCT_SCALAR;
    tag_str->attributes = 1; // uncompleted

    tag_obj->type = tag_str;

    SymtabInsert(symtab, tag_obj);
  }
  else if(obj_ref->specifier != current_name_frame->type){
    printf("ERROR: Invalid tag type in declaration.\n");
    return;
  }

  current_type_frame->current_type = obj_ref;
}

void TagAnonymousDef(){
  Obj* str_defined = StackPop(&typedef_stack);

  NameFrame* current_name_frame = StackPeek(&name_stack);
  TypeFrame* current_type_frame = StackPeek(&type_stack);
  current_type_frame->current_type = str_defined;
  current_type_frame->current_type->type->attributes = 0; // completed
}
