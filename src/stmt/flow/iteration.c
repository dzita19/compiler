#include "iteration.h"

#include "../expr/expr.h"

void WhileOpen(void){
  loop_count++;
}

void DoOpen(void){
  loop_count++;
}

void ForOpen(void){
  StackPush(&stack_frame_stack, stack_frame_stack.top->info);
  SymtabOpenScope(symtab, SCOPE_BLOCK);

  StackPush(&statement_stack, 0);
  loop_count++;
}

void ForDeclaration(void){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);
  TreeInsertNode(tree, FOR_DECL, num_of_stmts);

  Statement();
}

void ForNoDeclaration(void){
  StackPop(&statement_stack);
}

void ForExpression(void){
  Statement();
}

void WhileStmt(void){
  loop_count--;
  
  TreeNode* node = TreeInsertNode(tree, WHILE_STMT, 2);

  UnifyStatements(2);

  if(node->children[0]->expr_node == 0){
    ReportError("Error in while-loop condition.");
    return;
  }

  if(StructIsArray(node->children[0]->expr_node->type)
      || StructIsFunction(node->children[0]->expr_node->type)){
    ConvertChildToPointer(node, 0);
  }

  if(!StructIsScalar(node->children[0]->expr_node->type)){
    ReportError("Illegal while-loop condition.");
    return;
  }

  ConvertChildToLogic(node, 0);
}

void DoWhileStmt(void){
  loop_count--;
  
  TreeNode* node = TreeInsertNode(tree, DO_WHILE_STMT, 2);
  
  UnifyStatements(2);

  if(node->children[1]->expr_node == 0){
    ReportError("Error in do-while-loop condition.");
    return;
  }
  
  if(StructIsArray(node->children[1]->expr_node->type)
      || StructIsFunction(node->children[1]->expr_node->type)){
    ConvertChildToPointer(node, 1);
  }

  if(!StructIsScalar(node->children[1]->expr_node->type)){
    ReportError("Illegal do-while-loop condition.");
    return;
  }

  ConvertChildToLogic(node, 1);
}

// init: 0, cond: 1, body: 2, inc: 3, ;;;;;;endfor: 4, 
void ForStmt(void){
  loop_count--;

  // reverse order of body stmt and inc stmt
  TreeNode* body_stmt = StackPop(&tree->stack);
  TreeNode* inc_stmt  = StackPop(&tree->stack);
  
  StackPush(&tree->stack, body_stmt);  
  StackPush(&tree->stack, inc_stmt);

  TreeNode* node = TreeInsertNode(tree, FOR_STMT, 4);
  
  UnifyStatements(4);
  StackPop(&stack_frame_stack);
  SymtabCloseScope(symtab);

  if((node->children[0]->production != VOID_EXPR
        && node->children[0]->production != FOR_DECL && node->children[0]->expr_node == 0)
      || (node->children[1]->production != VOID_EXPR && node->children[1]->expr_node == 0)
      || (node->children[3]->production != VOID_EXPR && node->children[3]->expr_node == 0)) {
    return;
  }

  if(node->children[0]->expr_node 
      && (StructIsArray(node->children[0]->expr_node->type)
      || StructIsFunction(node->children[0]->expr_node->type))){
    ConvertChildToPointer(node, 0);
  }
  
  if(node->children[1]->expr_node 
      && (StructIsArray(node->children[1]->expr_node->type)
      || StructIsFunction(node->children[1]->expr_node->type))){
    ConvertChildToPointer(node, 1);
  }
  if(node->children[3]->expr_node 
      && (StructIsArray(node->children[3]->expr_node->type)
      || StructIsFunction(node->children[3]->expr_node->type))){
    ConvertChildToPointer(node, 3);
  }

  if(node->children[1]->production != VOID_EXPR && !StructIsScalar(node->children[1]->expr_node->type)){
    ReportError("Illegal for-loop condition.");
    return;
  }

  if(node->children[0]->production != VOID_EXPR)
    ConvertChildToArithmetic(node, 0);
  if(node->children[1]->production != VOID_EXPR)
    ConvertChildToLogic(node, 1);
  if(node->children[3]->production != VOID_EXPR)
    ConvertChildToArithmetic(node, 3);
}