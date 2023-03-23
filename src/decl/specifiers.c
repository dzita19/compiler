#include "specifiers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static Obj* TagDeclaration(int defined){
  NameFrame* name_frame = StackPeek(&name_stack);

  Obj* tag_obj = ObjCreateEmpty();
  tag_obj->name = name_frame->name;
  tag_obj->kind = OBJ_TAG;
  tag_obj->specifier = defined | name_frame->tag_type;

  Struct* tag_str = StructCreateEmpty();
  tag_str->obj = tag_obj;
  tag_str->kind = STRUCT_DIRECT;
  tag_str->type = TYPE_INCOMPLETE;

  tag_obj->type = tag_str;

  name_frame->name = 0;
  
  return tag_obj;
}

void Declaration(){
  TypeFrameClear(StackPeek(&type_stack));
}

void DeclarationSpecifiers(int try_redeclare){
  TypeFrame* type_frame = StackPeek(&type_stack);

  if(type_frame->current_type != 0 && type_frame->type_specifiers != 0){
    printf("ERROR: Illegal combination of custom type and type specifier(s).\n");
    return;
  }

  if(type_frame->type_specifiers != 0){
    type_frame->current_type = SymtabFindPredefined(type_frame->type_specifiers);
    if(type_frame->current_type == 0) {
      printf("ERROR: Illegal combination of type specifiers.\n");
      return;
    }
  }

  if(type_frame->current_type != 0 && type_frame->current_type->kind == OBJ_TAG){
    Obj* tag_obj = type_frame->current_type;

    if((tag_obj->specifier & DEFINITION_FETCH) == DEFINED){
      Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, tag_obj->name, NAMESPACE_TAG);
      if(obj_found == 0){
        SymtabInsert(symtab, tag_obj);
        return;
      }
      if(((tag_obj->specifier) & TAG_FETCH) != ((obj_found->specifier) & TAG_FETCH)){
        type_frame->current_type = 0;
        printf("ERROR: Tag already declared with different tag type.\n");
        return;
      }
      if((obj_found->specifier & DEFINITION_FETCH) == DEFINED){
        type_frame->current_type = 0;
        printf("ERROR: Tag already defined in this scope.\n");
        return;
      }
      
      obj_found->specifier  &= DEFINITION_CLEAR;
      obj_found->specifier  |= DEFINED;
      obj_found->type->type  = TYPE_OBJECT;
      obj_found->type->size  = tag_obj->type->size;
      obj_found->type->align = tag_obj->type->align;

      obj_found->members = tag_obj->members;
      tag_obj->members = (LinkedList){ 0, 0 };

      ObjDrop(tag_obj);
      type_frame->current_type = obj_found;
      return;
    }

    else if(try_redeclare){
      Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, tag_obj->name, NAMESPACE_TAG);
      if(obj_found == 0){
        SymtabInsert(symtab, tag_obj);
        return;
      }
      if(((tag_obj->specifier) & TAG_FETCH) != ((obj_found->specifier) & TAG_FETCH)){
        type_frame->current_type = 0;
        printf("ERROR: Tag already declared with different tag type.\n");
        return;
      }
    }

    else{
      Obj* obj_found = SymtabFindNamespace(symtab, tag_obj->name, NAMESPACE_TAG);
      if(obj_found == 0){
        SymtabInsert(symtab, tag_obj);
        return;
      }
      if(((tag_obj->specifier) & TAG_FETCH) != ((obj_found->specifier) & TAG_FETCH)){
        type_frame->current_type = 0;
        printf("ERROR: Tag already declared with different tag type.\n");
        return;
      }

      ObjDrop(tag_obj);
      type_frame->current_type = obj_found;
    }
  }
}

void FullDeclarationSpecifiers(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  
  int try_redeclare = 0;
  DeclarationSpecifiers(try_redeclare);
}

void RedeclarationSpecifiers(){
  TypeFrame* type_frame = StackPeek(&type_stack);
 
  int try_redeclare = type_frame->storage_specifier == NO_STORAGE_CLASS && (type_frame->type_qualifiers == 0);

  DeclarationSpecifiers(try_redeclare);
}

void StorageClassSpecifierRef(StorageClassSpecifier specifier){
  TypeFrame* type_frame = StackPeek(&type_stack);

  if(type_frame->storage_specifier != NO_STORAGE_CLASS){
    printf("ERROR: Multiple storage class specifiers.\n");
    return;
  }

  type_frame->storage_specifier = specifier;
}

void TypeSpecifierRef(TypeSpecifier specifier){
  TypeFrame* type_frame = StackPeek(&type_stack);
  
  if(type_frame->type_specifiers & specifier){
    printf("ERROR: Type specifier already referred in this declaration.\n");
    return;
  }
  type_frame->type_specifiers |= specifier;
}

void TypeQualifierRef(TypeQualifier qualifier){
  current_qualifiers |= qualifier;
} 

void TypedefName(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  Obj* obj_ref = SymtabFindNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);

  if(type_frame->type_specifiers != 0){
    printf("ERROR: Illegal combination of custom type and specifier(s).\n");
    return;
  }
  type_frame->current_type = obj_ref;
  NameFrameClear(name_frame);
}

void TagTypeRef(int tag_type){
  NameFrame* name_frame = StackPeek(&name_stack);
  name_frame->tag_type = tag_type;
}

void TagDefOpen(){
  Obj* tag_obj = TagDeclaration(DEFINED);
  StackPush(&typedef_stack, tag_obj);

  NameFrameClear(StackPeek(&name_stack));
}

void TagDefined(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  Obj* tag_obj = StackPop(&typedef_stack);

  if(type_frame->current_type != 0){
    printf("ERROR: Type already declared.\n");
    return;
  }

  type_frame->current_type = tag_obj;
  tag_obj->type->type = TYPE_OBJECT;

  if((tag_obj->specifier & TAG_FETCH) == TAG_ENUM){
    current_enum_constant = 0;
    return;
  }

  tag_obj->type->size = (tag_obj->type->size + tag_obj->type->align - 1) / tag_obj->type->align * tag_obj->type->align;
}

void TagDeclared(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  Obj* tag_obj = TagDeclaration(DECLARED);

  if(type_frame->current_type != 0){
    printf("ERROR: Type already declared.\n");
    return;
  }
  type_frame->current_type = tag_obj;
  NameFrameClear(StackPeek(&name_stack));
}