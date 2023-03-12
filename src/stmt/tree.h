#ifndef _TREE_H_
#define _TREE_H_

#include "yy/y.tab.h"

typedef struct TreeNode{
  int type;
  YYSTYPE info;
  int num_of_children;
  struct TreeNode* parent;
  struct TreeNode** children;
} TreeNode;

extern TreeNode* root;
extern TreeNode* TreeNodeCreate(int type, int num_of_children);
extern void TreeNodePrint();

#endif