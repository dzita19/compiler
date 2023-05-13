#include "iteration.h"

#include "../expr/expr.h"

void WhileOpen(){
  loop_count++;
}

void DoOpen(){
  loop_count++;
}

void ForOpen(){
  loop_count++;
}


void WhileStmt(){
  loop_count--;
  
  TreeNode* node = TreeInsertNode(tree, WHILE_STMT, 2);
  UnifyStatements(1);
  Statement();

  if(node->children[0]->expr_node == 0){
    ReportError("Error in while loop condition.");
    return;
  }

  if(!StructIsScalar(node->children[0]->expr_node->type)){
    ReportError("Illegal while loop condition.");
    return;
  }

  ConvertChildToLogic(node, 0);
}

void DoWhileStmt(){
  loop_count--;
  
  TreeNode* node = TreeInsertNode(tree, DO_WHILE_STMT, 2);
  UnifyStatements(1);
  Statement();

  if(node->children[0]->expr_node == 0){
    ReportError("Error in do-while loop condition.");
    return;
  }

  if(!StructIsScalar(node->children[1]->expr_node->type)){
    ReportError("Illegal do-while loop condition.");
    return;
  }

  ConvertChildToLogic(node, 1);
}

void ForStmt(int increment){
  loop_count--;
  
  TreeNode* stmt = StackPop(&tree->stack);
  if(increment != 0){
    ExpressionStmt();
  }
  else{
    EmptyStmt();
  }
  StackPush(&tree->stack, stmt);
  TreeNode* node = TreeInsertNode(tree, FOR_STMT, 4);

  UnifyStatements(4);
  Statement();

  if(node->children[1]->production == EXPRESSION_STMT
      && node->children[1]->children[0]->expr_node == 0){
    ReportError("Error in for loop condition.");
    return;
  }

  if(node->children[1]->production == EXPRESSION_STMT
      && !StructIsScalar(node->children[1]->children[0]->expr_node->type)){
    ReportError("Illegal for loop condition.");
    return;
  }

  if(node->children[1]->production == EXPRESSION_STMT)
    ConvertChildToLogic(node->children[1], 0);
}