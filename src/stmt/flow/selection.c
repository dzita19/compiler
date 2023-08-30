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
  Node* node = 0;
  for(node = switch_frame->first; node; node = node->next){
    TreeNode* case_node = node->info;
    if(case_node->expr_node->kind == CASE_LABEL){
      if(case_node->expr_node->address == const_expr->value){
        ReportError("Case label with value %d already defined.", case_node->expr_node->address);
        ConstExprDrop(const_expr);
        return;
      }
      else if(case_node->expr_node->address > const_expr->value){
        break;
      }
    }
  }

  TreeNode* tree_node = TreeInsertNode(tree, CASE_STMT, 0);
  tree_node->expr_node = ExprNodeCreateEmpty();
  tree_node->expr_node->kind = CASE_LABEL;
  tree_node->expr_node->address = const_expr->value;

  ConstExprDrop(const_expr);

  Node* case_node = NodeCreateEmpty();
  case_node->info = tree_node;

  if(node) LinkedListInsertBefore(switch_frame, node, case_node); 
  else LinkedListInsertLast(switch_frame, case_node);
  Statement();
}

void DefaultLabel(void){
  if(switch_count == 0){
    ReportError("Default statement must be inside switch statement.");
  }

  LinkedList* switch_frame = StackPeek(&switch_stack);
  if(switch_frame->first){
    TreeNode* default_node = switch_frame->first->info;
    if(default_node->expr_node->kind == DEFAULT_LABEL){
      ReportError("Default label already defined.");
      return;
    }
  } 

  TreeNode* node = TreeInsertNode(tree, DEFAULT_STMT, 0);
  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = DEFAULT_LABEL;

  Node* default_node = NodeCreateEmpty();
  default_node->info = node;

  LinkedListInsertFirst(switch_frame, default_node);
  Statement();
}


void IfOpen(void){

}

void ElseOpen(void){

}

void SwitchOpen(void){
  switch_count++;
  LinkedList* case_list = LinkedListCreateEmpty();
  StackPush(&switch_stack, case_list);
  VectorPush(switch_archive, case_list);
}


void IfStmt(void){
  TreeNode* node = TreeInsertNode(tree, IF_STMT, 2);
  UnifyStatements(2);

  if(node->children[0]->expr_node == 0){
    ReportError("Error in if-statement condition.");
    return;
  }

  if(StructIsArray(node->children[0]->expr_node->type)
      || StructIsFunction(node->children[0]->expr_node->type)){
    ConvertChildToPointer(node, 0);
  }

  if(!StructIsScalar(node->children[0]->expr_node->type)){
    ReportError("Illegal if-statement condition.");
    return;
  }

  ConvertChildToLogic(node, 0);
}

void IfElseStmt(void){
  TreeNode* else_node = StackPop(&tree->stack);
  TreeInsertNode(tree, VOID_EXPR, 0);
  Statement();
  StackPush(&tree->stack, else_node);

  TreeNode* node = TreeInsertNode(tree, IF_ELSE_STMT, 4);
  UnifyStatements(4);
  // TreeNode* node = TreeInsertNode(tree, IF_ELSE_STMT, 3);
  // UnifyStatements(3);

  if(node->children[0]->expr_node == 0){
    ReportError("Error in if-else-statement condition.");
    return;
  }

  if(StructIsArray(node->children[0]->expr_node->type)
      || StructIsFunction(node->children[0]->expr_node->type)){
    ConvertChildToPointer(node, 0);
  }

  if(!StructIsScalar(node->children[0]->expr_node->type)){
    ReportError("Illegal if-else-statement condition.");
    return;
  }
  
  ConvertChildToLogic(node, 0);
}

void SwitchStmt(void){
  // TreeInsertNode(tree, VOID_EXPR, 0);
  // Statement();

  // TreeNode* node = TreeInsertNode(tree, SWITCH_STMT, 3);
  // UnifyStatements(3);
  TreeNode* node = TreeInsertNode(tree, SWITCH_STMT, 2);
  UnifyStatements(2);

  switch_count--;
  StackPop(&switch_stack);
  
  if(node->children[0]->expr_node == 0){
    ReportError("Error in switch-statement control expression.");
    return;
  }

  if(!StructIsArithmetic(node->children[0]->expr_node->type)){
    ReportError("Illegal switch-statement control expression.");
    return;
  }

  ConvertChildToArithmetic(node, 0);
  SubexprImplCast(node, 0, predefined_types_struct + INT32_T);
}
