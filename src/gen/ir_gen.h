#ifndef _GEN_IR_H_
#define _GEN_IR_H_

#include "intermediate.h"
#include "resources.h"

extern void GenerateIntermediate(TreeNode* tree_node);
extern void GenerateSequencePoint(void);
extern void PrintIntermediate(void);

#endif