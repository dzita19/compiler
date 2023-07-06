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
  full_decl_specifiers = 0;

  TypeFrameClear(StackPeek(&type_stack));
}

// check if there is an invalid combination (custom type and type specifiers)
// if illegal combination, set current type to 0 (declarator will be ignored)
void CheckInvalidCombination(void){
  TypeFrame* type_frame = StackPeek(&type_stack);

  if(type_frame->current_type != 0 && type_frame->type_specifiers != CUSTOM_TYPE){
    ReportError("Multiple types specified.");
    type_frame->current_type = 0; // test
    return;
  }
}

void DeclarationSpecifiers(int try_redeclare){
  TypeFrame* type_frame = StackPeek(&type_stack);

  // fetch predefined type based on type specifiers (if not custom type)
  if(type_frame->current_type == 0 && type_frame->type_specifiers != 0){
    type_frame->current_type = SymtabFindPredefined(type_frame->type_specifiers);
    if(type_frame->current_type == 0) {
      ReportError("Illegal combination of type specifiers.");
    }
    return;
  }

  // if custom type, check validity and add it to symtab or update existing obj in symtab
  // if update existing obj, drop current obj
  // if valid, check invalid combinations of type spec and custom type

  if(type_frame->current_type != 0 && type_frame->current_type->kind == OBJ_TAG){
    // tag_obj is obj from current type frame - this obj is not in symtab yet
    Obj* tag_obj = type_frame->current_type;

    // if tag_obj is defined, it should be put into symtab (check for collisions in current scope)
    if((tag_obj->specifier & DEFINITION_FETCH) == DEFINED){
      Obj* obj_found = SymtabFindCurrentScopeNamespace(symtab, tag_obj->name, NAMESPACE_TAG);
      if(obj_found == 0){
        SymtabInsert(symtab, tag_obj);
        CheckInvalidCombination();
        return;
      }
      if((tag_obj->specifier & TAG_FETCH) != (obj_found->specifier & TAG_FETCH)){
        ObjDrop(type_frame->current_type);
        type_frame->current_type = 0;
        ReportError("Tag already declared with different tag type.");
        return;
      }
      if((obj_found->specifier & DEFINITION_FETCH) == DEFINED){
        ObjDrop(type_frame->current_type);
        type_frame->current_type = 0;
        ReportError("Tag already defined in this scope.");
        return;
      }
      
      // update existing obj, safely drop current obj
      obj_found->specifier  &= DEFINITION_CLEAR;
      obj_found->specifier  |= DEFINED;
      obj_found->type->size  = tag_obj->type->size;
      obj_found->type->align = tag_obj->type->align;

      obj_found->members = tag_obj->members;
      tag_obj->members = (LinkedList){ 0, 0 };

      StructCompleted(obj_found->type);

      ObjDrop(tag_obj);
      type_frame->current_type = obj_found;

      CheckInvalidCombination();
      return;
    }
    
    else{
      Obj* obj_found = try_redeclare
        ? SymtabFindCurrentScopeNamespace(symtab, tag_obj->name, NAMESPACE_TAG)
        : SymtabFindNamespace(symtab, tag_obj->name, NAMESPACE_TAG);
        
      if(obj_found == 0){
        SymtabInsert(symtab, tag_obj);
        CheckInvalidCombination();
        return;
      }
      if(((tag_obj->specifier) & TAG_FETCH) != ((obj_found->specifier) & TAG_FETCH)){
        ObjDrop(tag_obj);
        type_frame->current_type = 0;
        ReportError("Tag already declared with different tag type.");
        return;
      }

      ObjDrop(tag_obj);
      type_frame->current_type = obj_found;
      CheckInvalidCombination();
    }
  }

  // perform check for typedef
  if(type_frame->current_type != 0 && type_frame->current_type->kind == OBJ_TYPE){
    CheckInvalidCombination();
  }
}

void FullDeclarationSpecifiers(){
  full_decl_specifiers = 1;

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
    ReportError("Multiple storage class specifiers.");
    return;
  }

  type_frame->storage_specifier = specifier;
}

void TypeSpecifierRef(TypeSpecifier specifier){
  TypeFrame* type_frame = StackPeek(&type_stack);
  
  if(type_frame->type_specifiers & specifier){
    // ReportError("Type specifier already referred in this declaration.");
    type_frame->type_specifiers |= ERROR_TYPE;
    // type_frame->current_type = 0;
    return;
  }
  type_frame->type_specifiers |= specifier;
}

void TypeQualifierRef(TypeQualifier qualifier){
  TypeFrame* type_frame = StackPeek(&type_stack);
  if(full_decl_specifiers == 0) {
    type_frame->type_qualifiers |= qualifier;
  }
  else current_qualifiers |= qualifier;
} 

void TypedefName(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  NameFrame* name_frame = StackPeek(&name_stack);

  Obj* obj_ref = SymtabFindNamespace(symtab, name_frame->name, NAMESPACE_ORDINARY);
  NameFrameClear(name_frame);

  TypeSpecifierRef(CUSTOM_TYPE); // test
  if(type_frame->type_specifiers & ERROR_TYPE){
    ReportError("Multiple types specified.");
    return;
  }
  type_frame->current_type = obj_ref;
}

void TagTypeRef(int tag_type){
  NameFrame* name_frame = StackPeek(&name_stack);
  name_frame->tag_type = tag_type;

  TypeSpecifierRef(CUSTOM_TYPE); // test
}

void TagDefOpen(){
  Obj* tag_obj = TagDeclaration(DEFINED);
  StackPush(&typedef_stack, tag_obj);
  StackPush(&type_stack, TypeFrameCreateEmpty());

  if((tag_obj->specifier & TAG_FETCH) == TAG_ENUM) {
    TypeFrame* type_frame = StackPeek(&type_stack);
    type_frame->current_type = predefined_types_obj + INT32_T;
  }

  NameFrameClear(StackPeek(&name_stack));
}

void TagDefined(){
  TypeFrameDrop(StackPop(&type_stack));

  TypeFrame* type_frame = StackPeek(&type_stack);
  Obj* tag_obj = StackPop(&typedef_stack);

  if(type_frame->type_specifiers & ERROR_TYPE){
    ObjDrop(tag_obj); // test
    return;
  }
  
  if((tag_obj->specifier & TAG_FETCH) == TAG_ENUM){
    tag_obj->type->size  = (predefined_types_struct + INT32_T)->size;
    tag_obj->type->align = (predefined_types_struct + INT32_T)->align;
  }

  type_frame->current_type = tag_obj;

  StructCompleted(tag_obj->type);
  //IT IS ALSO DONE IN DECLARATION SPECIFIERS (this obj doesn't designate symtab entry yet)

  if((tag_obj->specifier & TAG_FETCH) == TAG_ENUM){
    current_enum_constant = 0;
    return;
  }

  if(tag_obj->type->align == 0) tag_obj->type->align = 1;
  tag_obj->type->size = (tag_obj->type->size + tag_obj->type->align - 1) / tag_obj->type->align * tag_obj->type->align;
}

void TagDeclared(){
  TypeFrame* type_frame = StackPeek(&type_stack);
  Obj* tag_obj = TagDeclaration(DECLARED); // obj that will eventually 
  NameFrameClear(StackPeek(&name_stack));

  if(type_frame->type_specifiers & ERROR_TYPE){
    ObjDrop(tag_obj); // test
    return;
  }
  type_frame->current_type = tag_obj;
}

void IsFunctionDefinition(void){
  nonprototype_redecl = 1;
  param_declaration_width = 0;
  // don't close func prototype scope
  Declaration();
}

void NotFunctionDefinition(void){
  param_declaration_width = 0;
  if(symtab->current_scope->type == SCOPE_FUNC_PROTOTYPE)
    SymtabRemoveCurrentScope(symtab);
}