#include "jump.h"

#include "../expr/expr.h"

void Label(void){
  char* label_name = QueueDelete(&identifier_queue);

  Obj* obj_ref = ScopeFindNamespace(function_scope, label_name, NAMESPACE_LABEL);
  if(obj_ref == 0){
    obj_ref = ObjCreateEmpty();
    obj_ref->kind = OBJ_LABEL;
    obj_ref->name = label_name;
    obj_ref->specifier = DEFINED;

    ScopeInsert(function_scope, obj_ref);
  }
  else if(obj_ref->specifier == DECLARED){
    obj_ref->specifier = DEFINED;
    StringDrop(label_name);
  }
  else{
    ReportError("Label already defined in this function.");
    StringDrop(label_name);
    return;
  }

  TreeNode* node = TreeInsertNode(tree, LABEL_STMT, 0);
  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = BASIC_LABEL;
  node->expr_node->obj_ref = obj_ref;

  Statement();
}

void GotoStmt(void){
  char* label_name = QueueDelete(&identifier_queue);

  Obj* obj_ref = ScopeFindNamespace(function_scope, label_name, NAMESPACE_LABEL);
  if(obj_ref == 0){
    obj_ref = ObjCreateEmpty();
    obj_ref->kind = OBJ_LABEL;
    obj_ref->name = label_name;
    obj_ref->specifier = DECLARED;

    ScopeInsert(function_scope, obj_ref);
  }

  else{
    StringDrop(label_name);
  }

  TreeNode* node = TreeInsertNode(tree, GOTO_STMT, 0);
  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = BASIC_LABEL;
  node->expr_node->obj_ref = obj_ref;
  
  Statement();
}

void ContinueStmt(void){
  if(loop_count == 0){
    ReportError("Continue statement must be inside a loop.");
  }

  // TreeNode* node = 
  TreeInsertNode(tree, CONTINUE_STMT, 0);  
  Statement();
}

void BreakStmt(void){
  if(loop_count == 0 && switch_count == 0){
    ReportError("Continue statement must be inside a loop or switch statement.");
  }

  // TreeNode* node = 
  TreeInsertNode(tree, BREAK_STMT, 0);
  Statement();
}

void ReturnStmt(void){
  // TreeNode* node = 
  TreeInsertNode(tree, RETURN_STMT, 0);
  Statement();

  if(current_function_body == 0){
    ReportError("Unknown function type.");
    return;
  }

  Struct* return_type = StructGetParentUnqualified(current_function_body->type);

  if(!StructIsVoid(return_type)){
    ReportError("Non-void functions must return value.");
  }

}

void ReturnExprStmt(void){
  TreeNode* node = TreeInsertNode(tree, RETURN_EXPR_STMT, 1);
  Statement();

  if(current_function_body == 0){
    ReportError("Unknown function type.");
    return;
  }
  
  Struct* return_type = StructGetParentUnqualified(current_function_body->type);

  if(node->children[0]->expr_node == 0){
    ReportError("Error in return expression.");
    return;
  }

  if(StructIsArithmetic(return_type) && StructIsArithmetic(node->children[0]->expr_node->type)){
    SubexprImplCast(node, 0, return_type);
  }

  if(!StructIsCompatibleUnqualified(return_type, node->children[0]->expr_node->type)
      && !(StructIsPointer(return_type) && IsNullPointer(node->children[0]->expr_node))){
    ReportError("Illegal return type");
    return;
  }
}