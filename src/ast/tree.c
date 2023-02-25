#include "tree.h"
#include "production.h"

#include "util/stack.h"

static Stack stack = { 0 };
TreeNode* root = 0;

TreeNode* TreeNodeCreate(int type, int num_of_children){
  TreeNode* node = malloc(sizeof(TreeNode));

  printf("NODE CREATED: %s\n", production_names[type]);

  node->type = type;
  node->num_of_children = num_of_children;
  if(num_of_children)
    node->children = malloc(sizeof(TreeNode*) * num_of_children);
  else node->children = 0;

  for(int i = num_of_children - 1; i >= 0; i--){
    node->children[i] = StackPop(&stack);
  }

  StackPush(&stack, node);
  return node;
}

// preorder
void TreeNodePrint(TreeNode* root){
  Stack preorder_stack = { 0 };
  StackPush(&preorder_stack, root);

  int indent = 0;
  while(preorder_stack.top){
    root = StackPop(&preorder_stack);

    if(!root) continue;
    if(root == -1) { indent++; continue; }
    if(root == -2) { indent--; continue; }

    for(int i = 0; i < indent; i++) printf("  ");
    printf("+%s\n", production_names[root->type]);

    StackPush(&preorder_stack, (void*)-2);
    for(int i = root->num_of_children - 1; i >= 0; i--){
      StackPush(&preorder_stack, root->children[i]);
    }  
    StackPush(&preorder_stack, (void*)-1);
  }
}