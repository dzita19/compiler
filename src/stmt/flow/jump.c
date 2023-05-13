#include "jump.h"

#include "../expr/expr.h"

void Label(){

}

void LabelStmt(){

}


void GotoStmt(){

}

void ContinueStmt(){
  if(loop_count == 0){
    ReportError("Continue statement must be inside a loop.");
  }

  TreeInsertNode(tree, CONTINUE_STMT, 0);
  Statement();
}

void BreakStmt(){
  if(loop_count == 0 && switch_count == 0){
    ReportError("Continue statement must be inside a loop or switch statement.");
  }

  TreeInsertNode(tree, BREAK_STMT, 0);
  Statement();
}

void ReturnStmt(){
  TreeNode* node = TreeInsertNode(tree, RETURN_STMT, 0);
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

void ReturnExprStmt(){

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