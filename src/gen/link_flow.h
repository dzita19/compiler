#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "stmt/tree.h"

#define JUMP_IF_TRUE  0
#define JUMP_IF_FALSE 1
#define JUMP_ALWAYS   2
#define JUMP_CASE     3

// describes only nodes that alter the flow
// do NOT allocate if node is only a target of jump
typedef struct LogicNode{
  TreeNode* if_true;
  TreeNode* if_false;
  int jump_if;
} LogicNode;

extern LogicNode* LogicNodeCreateEmpty(void);
extern void LogicNodeDump(LogicNode*);
extern void LogicNodeDrop(LogicNode*);

extern int  label_counter;

extern void LinkFlowControl(TreeNode* tree_node, int index_in_parent);

#endif