#include "primary.h"

#include <string.h>
#include "util/queue.h"
#include "../literals.h"

void IdentifierPrimary(){
  const char* symbol_name = QueueDelete(&identifier_queue);
  Obj* obj_ref = SymtabFindNamespace(symtab, symbol_name, NAMESPACE_ORDINARY);
  StringDrop(symbol_name);
  
  if(obj_ref == 0){
    TreeNode* node = TreeInsertNode(tree, IDENTIFIER_PRIMARY, 0);
    ReportError("Symbol not found.");
    return;
  }

  if(obj_ref->kind == OBJ_VAR){
    TreeNode* node = TreeInsertNode(tree, IDENTIFIER_PRIMARY, 0);

    ExprNode* expr_node = ExprNodeCreateEmpty();
    expr_node->type = obj_ref->type;
    expr_node->kind = (obj_ref->type->type == TYPE_FUNCTION ? FUNC_DESIGNATOR : LVALUE);
    expr_node->obj_ref  = obj_ref;

    node->expr_node = expr_node;
  }
  else if(obj_ref->kind == OBJ_ENUM){
    TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

    ExprNode* expr_node = ExprNodeCreateEmpty();
    expr_node->type = obj_ref->type;
    expr_node->kind = NUM_LITERAL;
    expr_node->address = obj_ref->address;

    node->expr_node = expr_node;
  }
  else {
    ReportError("Illegal symbol kind.");
    return;
  }
}

void ConstantPrimary(){
  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  NumLit* numlit = QueueDelete(&numlit_queue);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->type = predefined_types_struct + numlit->type;
  expr_node->kind = NUM_LITERAL;
  expr_node->address = numlit->value;

  node->expr_node = expr_node;

  NumLitDrop(numlit);
}

void StringPrimary(){
  TreeNode* node = TreeInsertNode(tree, STRING_PRIMARY, 0);

  const char* string = QueueDelete(&strlit_queue);

  int string_index = 0;
  for(int i = 0; i < string_table->size; i++){
    if(strcmp(string, string_table->content[i]) == 0){
      StringDrop(string);
      string_index = i;
    }
  }
  string_index = VectorSize(string_table);
  VectorPush(string_table, (void*)string);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->type = StructStringLiteral();
  expr_node->kind = STR_LITERAL;
  expr_node->address = string_index;

  node->expr_node = expr_node;
}