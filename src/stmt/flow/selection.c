#include "selection.h"

#include "../expr/expr.h"
#include "../tree.h"


void ControlExpression(void){
  Statement();
}

void CaseLabel(void){
  if(switch_count == 0){
    ReportError("Case statement must be inside switch statement.");
  }

  ConstExpr* const_expr = StackPop(&const_expr_stack);
  if(const_expr->kind != VAL_ARITHM || !StructIsArithmetic(const_expr->type)) {
    ReportError("Case label must have constant arithmetic value.");
    ConstExprDrop(const_expr);
    return;
  }

  LinkedList* switch_frame = StackPeek(&switch_stack);
  for(Node* node = switch_frame->first; node; node = node->next){
    ExprNode* case_expr = node->info;
    if(case_expr->kind == CASE_LABEL && case_expr->address == const_expr->value){
      ReportError("Case label already defined.");
      ConstExprDrop(const_expr);
      return;
    }
  }

  TreeNode* node = TreeInsertNode(tree, CASE_STMT, 0);
  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = CASE_LABEL;
  node->expr_node->address = const_expr->value;

  ConstExprDrop(const_expr);

  Node* case_node = NodeCreateEmpty();
  case_node->info = node->expr_node;

  LinkedListInsertLast(switch_frame, case_node);
  Statement();

  /*StackNode* stack_node = tree->stack.top;
  for(int i = 0; i < (int)(long)statement_stack.top->info; i++, stack_node = stack_node->next){
    TreeNode* node = stack_node->info;
    if(node->production == INITIALIZATION){
      ReportError("Initialization cannot be skipped by case label.");
      break;
    }
  }*/
}

void DefaultLabel(void){
  if(switch_count == 0){
    ReportError("Default statement must be inside switch statement.");
  }

  LinkedList* switch_frame = StackPeek(&switch_stack);
  for(Node* node = switch_frame->first; node; node = node->next){
    ExprNode* case_expr = node->info;
    if(case_expr->kind == DEFAULT_LABEL){
      ReportError("Default label already defined.");
      return;
    }
  }

  TreeNode* node = TreeInsertNode(tree, DEFAULT_STMT, 0);
  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = DEFAULT_LABEL;

  Node* default_node = NodeCreateEmpty();
  default_node->info = node->expr_node;

  LinkedListInsertLast(switch_frame, default_node);
  Statement();

  /*StackNode* stack_node = tree->stack.top;
  for(int i = 0; i < (int)(long)statement_stack.top->info; i++, stack_node = stack_node->next){
    TreeNode* node = stack_node->info;
    if(node->production == INITIALIZATION){
      ReportError("Initialization cannot be skipped by case label.");
      break;
    }
  }*/
}


void IfOpen(void){

}

void ElseOpen(void){

}

void SwitchOpen(void){
  switch_count++;
  StackPush(&switch_stack, LinkedListCreateEmpty());
}


void IfStmt(void){
  TreeNode* node = TreeInsertNode(tree, IF_STMT, 2);
  UnifyStatements(2);

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

void IfElseStmt(void){
  TreeNode* node = TreeInsertNode(tree, IF_ELSE_STMT, 3);
  UnifyStatements(3);

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

void SwitchStmt(void){
  TreeNode* node = TreeInsertNode(tree, SWITCH_STMT, 2);
  UnifyStatements(2);

  switch_count--;
  LinkedListDrop(StackPop(&switch_stack));
  
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
