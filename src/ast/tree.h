#ifndef _TREE_H_
#define _TREE_H_

#include "yy/y.tab.h"

typedef struct treenode{
  int type;
  YYSTYPE info;
  int num_of_children;
  struct treenode** children;
} TreeNode;

extern TreeNode* root;
extern TreeNode* TreeNodeCreate(int type, int num_of_children);
extern void TreeNodePrint();

#endif