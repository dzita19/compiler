#include "postfix.h"

#include <string.h>

// semantics of a[b] is the same as of *(a + b) - no need to add a new rule for that
void ArrayRefExpr(){
  extern void AddExpr(void);
  extern void DerefExpr(void);

  AddExpr();
  DerefExpr();
}

void FunctionCallExpr(){
  int args_count = (int)(long)StackPop(&function_call_stack);

  TreeNode* node = TreeInsertNode(tree, FUNCTION_CALL_EXPR, 1 + args_count);

  if(!CheckSubexprValidity(node, 1 + args_count)) return;

  // if(node->children[0]->expr_node->type->type == TYPE_FUNCTION){
  //   ConvertChildToPointer(node, 0);
  // }

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);

  for(int i = 1; i < node->num_of_children; i++){
    if(StructIsArray(node->children[i]->expr_node->type)
      || StructIsFunction(node->children[i]->expr_node->type)) ConvertChildToPointer(node, i);
  }

  ExprNode* function_designator = node->children[0]->expr_node;
  Struct* expr_type = 0;
  
  if(!StructIsFunctionPtr(function_designator->type)){
    ReportError("Symbol doesn't designate function.");
    return;
  }

  if((function_designator->type->parent->attributes & NONPROTOTYPE_FUNCTION) == 0){

    int arg_cntr = 1; // counts current argument - from syntax tree

    for(Node* param_node = function_designator->type->parent->parameters.first; param_node; param_node = param_node->next){
      if(arg_cntr >= node->num_of_children){ // check so you don't reference a non-existing child
        ReportError("Not enough arguments for function call.");
        return;
      }
      
      Struct* current_arg   = StructGetUnqualified(node->children[arg_cntr]->expr_node->type);
      Struct* current_param = StructGetUnqualified(param_node->info);

      if(StructIsArithmetic(current_param) && StructIsArithmetic(current_arg)){
        // all good
      }
      else if(StructIsStructOrUnion(current_param) && StructIsStructOrUnion(current_arg)
          && StructIsCompatible(current_param, current_arg)){
        // all good
      }
      else if(StructIsPointer(current_param) && StructIsPointer(current_arg)){
        Struct* pointed_param = StructGetParentUnqualified(current_param);
        Struct* pointed_arg   = StructGetParentUnqualified(current_arg);
        
        if(StructIsCompatible(pointed_param, pointed_arg)){
          // all good
        }
        else if(StructIsVoid(pointed_arg)) {
          // all good
        }
        else if(StructIsVoid(pointed_param)){
          // all good
        }
        else {
          ReportError("Incompatible argument type for function call.");
          return;
        }

        int qualifiers1 = current_param->parent->kind == STRUCT_QUALIFIED ? current_param->parent->attributes : 0;
        int qualifiers2 = current_arg->parent->kind   == STRUCT_QUALIFIED ? current_arg->parent->attributes   : 0;

        if(qualifiers1 != (qualifiers1 | qualifiers2)){
          ReportError("Pointed objects qualifications are not compatible for function call.");
          return;
        }
      }
      else if(StructIsPointer(current_param) && IsNullPointer(node->children[arg_cntr]->expr_node)){
        // all good
      }
      else {
        ReportError("Incompatible argument type for function call.");
        return;
      }
      

      // params are aligned to 4byte address
      ConvertChildToArithmetic(node, arg_cntr);
      if(StructIsArithmetic(current_param)){
        SubexprImplCast(node, arg_cntr, StructGetExprIntType(current_param, current_param));
      }
      SubexprImplCast(node, arg_cntr, current_param);

      // params are not aligned to 4byte address
      // SubexprImplCast(node, arg_cntr, current_param);

      arg_cntr++;
    }

    if(arg_cntr < node->num_of_children && (function_designator->type->parent->attributes & ELLIPSIS_FUNCTION) == 0){
      ReportError("Too many arguments for function call.");
      return;
    }

  }

  expr_type = StructGetParentUnqualified(StructGetParentUnqualified(function_designator->type));

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  if(StructIsStructOrUnion(expr_type)){

    TreeNode* fcall = StackPop(&tree->stack);

    if(rval_call_storage == 0){
      rval_call_storage = ObjCreateEmpty();
      rval_call_storage->kind = OBJ_VAR;
      rval_call_storage->specifier = LINKAGE_NONE | STORAGE_AUTO | DEFINED;
      rval_call_storage->name = StringDuplicate("$storage00");
    }

    if(rval_call_storage->type == 0 || rval_call_storage->type->size < expr_type->size){
      rval_call_storage->type = expr_type;
    }

    // push storage_obj to tree stack
    extern void DerefExpr(void);
    extern void BasicAssignExpr(int);

    TreeNode* storage_node = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

    storage_node->expr_node          = ExprNodeCreateEmpty();
    storage_node->expr_node->type    = StructToPtr(expr_type);
    storage_node->expr_node->kind    = ADDRESS_OF;
    storage_node->expr_node->obj_ref = rval_call_storage;

    DerefExpr();
    StackPush(&tree->stack, fcall);
    BasicAssignExpr(0);

    // storage_node = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

    // storage_node->expr_node = ExprNodeCreateEmpty();
    // storage_node->expr_node->type = StructToPtr(expr_type);
    // storage_node->expr_node->kind = ADDRESS_OF;
    // storage_node->expr_node->obj_ref  = rval_storage_obj;
    
    // DerefExpr();

    // CommaExprOpen();
    // CommaExpr();
    // FullExpr();
  }
}

/*static void FieldRefPropagateOffset(TreeNode* node, Struct* type, int offset){
  switch(node->production){
  case ADDRESS_PRIMARY:
  case CONSTANT_PRIMARY:
  case STRING_PRIMARY:
    node->expr_node->type = type;
    node->expr_node->address += offset;
    break;
  case DEREF_EXPR:
    if(node->children[0]->production == ADDRESS_PRIMARY
        || node->children[0]->production == CONSTANT_PRIMARY
        || node->children[0]->production == STRING_PRIMARY
        || node->children[0]->production == COND_EXPR
        || node->children[0]->production == COMMA_EXPR) {
      node->expr_node->type = type;
      FieldRefPropagateOffset(node->children[0], StructToPtr(type), offset);
    }
    else{ // deref should be parent of field ref
      node->expr_node->type = type;
      
      StackPush(&tree->stack, node->children[0]);
      node->children[0]->parent = 0;
      node->children[0] = 0;

      TreeNode* field_ref = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
      field_ref->expr_node = ExprNodeCreateEmpty();
      field_ref->expr_node->kind = RVALUE;
      field_ref->expr_node->type = StructToPtr(type);
      field_ref->expr_node->address = offset;
      
      node->children[0] = StackPop(&tree->stack);
      node->children[0]->parent = node;
    }
    break;
  case COND_EXPR:
    node->expr_node->type = type;
    FieldRefPropagateOffset(node->children[1], type, offset);
    FieldRefPropagateOffset(node->children[2], type, offset);
    break;
  case ASSIGN_EXPR: { // assign should be son of field ref
    TreeNode* old_parent = node->parent;
    int index_in_parent = 0;
    if(old_parent){
      for(index_in_parent = 0; index_in_parent < old_parent->num_of_children; index_in_parent++){
        if(old_parent->children[index_in_parent] == node) break;
      }
      node->parent = 0;
      old_parent->children[index_in_parent] = 0;

      StackPush(&tree->stack, node);
    }

    TreeNode* field_ref = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
    field_ref->expr_node = ExprNodeCreateEmpty();
    field_ref->expr_node->kind = RVALUE;
    field_ref->expr_node->type = StructToPtr(type);
    field_ref->expr_node->address = offset;

    TreeNode* deref = TreeInsertNode(tree, DEREF_EXPR, 1);
    deref->expr_node = ExprNodeCreateEmpty();
    deref->expr_node->kind = RVALUE;
    deref->expr_node->type = type;

    if(old_parent){
      StackPop(&tree->stack);

      old_parent->children[index_in_parent] = field_ref;
      field_ref->parent = old_parent;
    }
  } break;
  case COMMA_EXPR:
    node->expr_node->type = type;
    FieldRefPropagateOffset(node->children[node->num_of_children - 1], type, offset);
    break;
  default: break;
  }
}*/

void FieldRefExpr(){
  TreeNode* operand = StackPop(&tree->stack);

  if(operand->expr_node == 0) return;

  const char* member_name = QueueDelete(&identifier_queue);

  Struct* type = StructGetUnqualified(operand->expr_node->type);
  if(!StructIsStructOrUnion(type)){
    ReportError("Field can be referenced only on struct or union objects.");
    return;
  }

  Obj* tag_obj = type->obj;
  Obj* member = ObjFindMember(tag_obj, member_name);

  StringDrop(member_name);

  if(member == 0){
    ReportError("Member with name %s doesn't exist.", member_name);
    return;
  }

  if(operand->production == DEREF_EXPR){
    TreeNode* deref   = operand;
    TreeNode* address = operand->children[0];

    StackPush(&tree->stack, address);
    TreeNode* field_ref  = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
    field_ref->expr_node = ExprNodeCreateEmpty();
    field_ref->expr_node->address = member->address;
    field_ref->expr_node->kind = LVALUE;
    field_ref->expr_node->type = member->type;

    field_ref->parent  = deref;
    deref->children[0] = StackPop(&tree->stack);
    deref->parent = 0;
    deref->expr_node->type = member->type;

    StackPush(&tree->stack, deref);
  }
  else{
    StackPush(&tree->stack, operand);

    TreeNode* node  = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
    node->expr_node = ExprNodeCreateEmpty();
    node->expr_node->address = member->address;
    node->expr_node->kind = LVALUE;
    node->expr_node->type = member->type;
  }

  TryFold();

  // FieldRefPropagateOffset(node, member->type, member->address);
}

void PtrRefExpr(){
  extern void DerefExpr(void);
  extern void FieldRefExpr(void);

  DerefExpr();
  FieldRefExpr();
}

void IncDecExpr(Production production){

  InsertConstant(0);
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot increment non-modifiable or non-lvalue objects.");
    return;
  }

  Struct* type = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsScalar(type)){
    ReportError("Increment only scalar values.");
    return;
  }

  if(StructIsPointer(type)) expr_type = type;
  else expr_type = StructGetExprIntType(type, type);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  if(StructIsPointer(type)){
    node->children[1]->expr_node->address = StructGetParentUnqualified(type)->size;
  }
  else{
    node->children[1]->expr_node->address = 1;
  }
}

void FunctionArgsOpen(){
  StackPush(&function_call_stack, 0);
}

void FunctionArgsClose(){

}

void FunctionArg(){
  function_call_stack.top->info++;
}