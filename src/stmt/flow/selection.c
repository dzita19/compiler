#include "selection.h"

#include "../expr/expr.h"
#include "../tree.h"

void CaseStmt(){
  if(switch_count == 0){
    ReportError("Case statement must be inside switch statement.");
  }

  ConstExpr* const_expr = StackPop(&const_expr_stack);

  LinkedList* switch_frame = StackPeek(&switch_stack);
  for(Node* node = switch_frame->first; node; node = node->next){
    if(node->info == (void*)(long)const_expr->value){
      ReportError("Case statement already defined.");
      break;
    }
  }

  Node* case_node = NodeCreateEmpty();
  case_node->info = (void*)(long)const_expr->value;

  LinkedListInsertLast(switch_frame, case_node);

  TreeNode* node = TreeInsertNode(tree, CASE_STMT, 1);
  
  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = CASE_LABEL;
  expr_node->address = const_expr->value;

  ConstExprDrop(const_expr);

  node->expr_node = expr_node;

  UnifyStatements(1);
  Statement();
}

void DefaultStmt(){
  if(switch_count == 0){
    ReportError("Default statement must be inside switch statement.");
  }

  const int DEFAULT_VALUE = 0x80000000;

  LinkedList* switch_frame = StackPeek(&switch_stack);
  for(Node* node = switch_frame->first; node; node = node->next){
    if(node->info == (void*)(long)DEFAULT_VALUE){
      ReportError("Default statement already defined.");
      break;
    }
  }

  Node* case_node = NodeCreateEmpty();
  case_node->info = (void*)(long)DEFAULT_VALUE;

  LinkedListInsertLast(switch_frame, case_node);

  TreeNode* node = TreeInsertNode(tree, DEFAULT_STMT, 1);
  
  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = CASE_LABEL;
  expr_node->address = DEFAULT_VALUE;

  node->expr_node = expr_node;

  UnifyStatements(1);
  Statement();
}


void IfOpen(){

}

void ElseOpen(){

}

void SwitchOpen(){
  switch_count++;
  StackPush(&switch_stack, LinkedListCreateEmpty());
}


void IfStmt(){
  TreeNode* node = TreeInsertNode(tree, IF_STMT, 2);

  UnifyStatements(1);
  Statement();

  if(node->children[0]->expr_node == 0){
    ReportError("Error in if statement condition.");
    return;
  }

  if(!StructIsScalar(node->children[0]->expr_node->type)){
    ReportError("Illegal if statement condition.");
    return;
  }

  ConvertChildToLogic(node, 0);
}

void IfElseStmt(){
  TreeNode* node = TreeInsertNode(tree, IF_ELSE_STMT, 3);

  UnifyStatements(2);
  Statement();

  if(node->children[0]->expr_node == 0){
    ReportError("Error in if-else statement condition.");
    return;
  }

  if(!StructIsScalar(node->children[0]->expr_node->type)){
    ReportError("Illegal if-else statement condition.");
    return;
  }

  ConvertChildToLogic(node, 0);
}

void SwitchStmt(){
  TreeNode* node = TreeInsertNode(tree, SWITCH_STMT, 2);

  switch_count--;
  LinkedListDrop(StackPop(&switch_stack));

  UnifyStatements(1);
  Statement();
  
  if(node->children[0]->expr_node == 0){
    ReportError("Error in switch control expression.");
    return;
  }

  if(!StructIsArithmetic(node->children[0]->expr_node->type)){
    ReportError("Illegal switch control expression.");
    return;
  }

  ConvertChildToArithmetic(node, 0);
}
