#include "primary.h"

#include <string.h>
#include "util/queue.h"
#include "../literals.h"

void IdentifierPrimary(){
  extern void DerefExpr(void);

  const char* symbol_name = QueueDelete(&identifier_queue);
  Obj* obj_ref = SymtabFindNamespace(symtab, symbol_name, NAMESPACE_ORDINARY);
  StringDrop(symbol_name);
  
  if(obj_ref == 0){
    // TreeNode* node = 
    TreeInsertNode(tree, ADDRESS_PRIMARY, 0);
    DerefExpr();
    ReportError("Symbol not found.");
    return;
  }

  if(obj_ref->kind == OBJ_VAR){
    TreeNode* node = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

    node->expr_node = ExprNodeCreateEmpty();
    node->expr_node->type = StructToPtr(obj_ref->type);
    node->expr_node->kind = ADDRESS_OF;
    node->expr_node->obj_ref  = obj_ref;

    DerefExpr();
  }
  else if(obj_ref->kind == OBJ_ENUM){
    TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

    node->expr_node = ExprNodeCreateEmpty();
    node->expr_node->type = obj_ref->type;
    node->expr_node->kind = NUM_LITERAL;
    node->expr_node->address = obj_ref->address;
  }
  else {
    ReportError("Illegal symbol kind.");
    return;
  }
}

void ConstantPrimary(){
  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  NumLit* numlit = QueueDelete(&numlit_queue);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->type = predefined_types_struct + numlit->type;
  node->expr_node->kind = NUM_LITERAL;
  node->expr_node->address = numlit->value;

  NumLitDrop(numlit);
}

void StringPrimary(){
  TreeNode* node = TreeInsertNode(tree, STRING_PRIMARY, 0);

  const char* string = QueueDelete(&strlit_queue);

  int string_index = -1; // -1 : not found
  for(int i = 1; i < string_table->size; i++){ // first entry is reserved for static objects with no linkage
    if(strcmp(string, string_table->content[i]) == 0){
      StringDrop(string);
      string_index = i;
    }
  }
  if(string_index < 0){
    string_index = VectorSize(string_table);
    VectorPush(string_table, (void*)string);
  }

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->type = StructStringLiteral();
  node->expr_node->kind = STR_LITERAL;
  node->expr_node->string_ref = string_index;
}