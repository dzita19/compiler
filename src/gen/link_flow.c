#include "link_flow.h"

#include "stmt/expr/expr.h"
#include "util/linked_list.h"
#include "util/stack.h"

LogicNode* LogicNodeCreateEmpty(void){
  LogicNode* logic_node = malloc(sizeof(LogicNode));
  logic_node->if_true   = 0;
  logic_node->if_false  = 0;
  logic_node->jump_if   = JUMP_ALWAYS;

  logic_node_alloc++;

  return logic_node;
}

void LogicNodeDump(LogicNode* logic_node){
  static const char* jump_if_print[] = {
    [JUMP_IF_TRUE]  = "IF TRUE",
    [JUMP_IF_FALSE] = "IF FALSE",
    [JUMP_ALWAYS]   = "ALWAYS",
  };

  if(logic_node->jump_if == JUMP_ALWAYS) printf("[LogicNode] JumpId: %d; Jump %s;", 
    logic_node ? logic_node->if_true->id  : 0,
    jump_if_print[logic_node->jump_if]);

  else printf("[LogicNode] JumpIfTrueId: %d; JumpIfFalseId: %d; Jump %s;", 
    logic_node ? logic_node->if_true->id  : 0, 
    logic_node ? logic_node->if_false->id : 0,
    jump_if_print[logic_node->jump_if]);
}

void LogicNodeDrop(LogicNode* logic_node){
  free(logic_node);
  logic_node_free++;
}


int label_counter = 0;
static TreeNode* function_body = 0;
static Stack continue_stack    = (Stack){ 0 };
static Stack break_stack       = (Stack){ 0 };

static LinkedList label_list   = (LinkedList){ 0, 0 };
static LinkedList goto_list    = (LinkedList){ 0, 0 };

static void SetJump(TreeNode** origin, TreeNode* target, int true_destination){
  *origin = target;
  if(true_destination) target->label = -1;
}

// generate linkage for conditions - takes into account if the condition is constant
static void LinkCondition(TreeNode* origin, TreeNode* if_true, TreeNode* if_false, int jump_if){

  if(origin->production == VOID_EXPR || origin->production == CONSTANT_PRIMARY){
    if((origin->production == VOID_EXPR || origin->expr_node->address != 0)
        && jump_if == JUMP_IF_TRUE){
      origin->logic_node = LogicNodeCreateEmpty();
      SetJump(&origin->logic_node->if_true , if_true, 1);
      SetJump(&origin->logic_node->if_false, if_true, 0);
      origin->logic_node->jump_if = JUMP_ALWAYS;
    }
    else if((origin->production != VOID_EXPR && origin->expr_node->address == 0)
        && jump_if == JUMP_IF_FALSE){
      origin->logic_node = LogicNodeCreateEmpty();
      SetJump(&origin->logic_node->if_true , if_false, 0);
      SetJump(&origin->logic_node->if_false, if_false, 1);
      origin->logic_node->jump_if = JUMP_ALWAYS;
    }
    origin->production = VOID_EXPR;
    ExprNodeDrop(origin->expr_node);
    origin->expr_node = 0;
  }
  else{
    origin->logic_node = LogicNodeCreateEmpty();
    SetJump(&origin->logic_node->if_true , if_true, jump_if == JUMP_IF_TRUE);
    SetJump(&origin->logic_node->if_false, if_false, jump_if == JUMP_IF_FALSE);
    origin->logic_node->jump_if = jump_if;
  }
}

static void LinkUnconditionally(TreeNode* origin, TreeNode* target){
  origin->logic_node = LogicNodeCreateEmpty();
  SetJump(&origin->logic_node->if_true , target, 1);
  SetJump(&origin->logic_node->if_false, target, 1);
  origin->logic_node->jump_if = JUMP_ALWAYS;
}

// productions that directs the uppermost jump
// conditional operator and flow control statements
static void LinkFlowLogicToArithm(TreeNode* tree_node, int index_in_parent){
  switch(tree_node->production){
  case COND_EXPR:{
    TreeNode* condition = tree_node->children[0];
    TreeNode* if_true   = tree_node->children[1];
    TreeNode* if_false  = tree_node->children[2];
    TreeNode* next_expr = tree_node->children[3];

    LinkCondition(condition, if_true, if_false, JUMP_IF_FALSE);
    LinkUnconditionally(if_true, next_expr);

  } break;

  case IF_STMT:{
    TreeNode* condition = tree_node->children[0];
    TreeNode* body      = tree_node->children[1];
    TreeNode* next_stmt = tree_node->parent->children[index_in_parent + 1];

    LinkCondition(condition, body, next_stmt, JUMP_IF_FALSE);

  } break;
  case IF_ELSE_STMT:{
    TreeNode* condition = tree_node->children[0];
    TreeNode* if_body   = tree_node->children[1];
    TreeNode* else_body = tree_node->children[2];
    TreeNode* next_stmt = tree_node->parent->children[index_in_parent + 1];

    LinkCondition(condition, if_body, else_body, JUMP_IF_FALSE);
    LinkUnconditionally(if_body, next_stmt);

  } break;
  case SWITCH_STMT:{
    TreeNode* next_stmt = tree_node->parent->children[index_in_parent + 1];

    StackPush(&break_stack, next_stmt);

  } break;

  case WHILE_STMT:{
    TreeNode* condition = tree_node->children[0];
    TreeNode* body      = tree_node->children[1];
    TreeNode* next_stmt = tree_node->parent->children[index_in_parent + 1];

    LinkCondition(condition, body, next_stmt, JUMP_IF_FALSE);
    LinkUnconditionally(body, condition);

    StackPush(&continue_stack, body);
    StackPush(&break_stack, next_stmt);

  } break;
  case DO_WHILE_STMT:{
    TreeNode* body      = tree_node->children[0];
    TreeNode* condition = tree_node->children[1];
    TreeNode* next_stmt = tree_node->parent->children[index_in_parent + 1];

    LinkCondition(condition, body, next_stmt, JUMP_IF_TRUE);
    
    StackPush(&continue_stack, condition);
    StackPush(&break_stack, next_stmt);

  } break;
  case FOR_STMT:{
    TreeNode* condition = tree_node->children[1];
    TreeNode* body      = tree_node->children[2];
    TreeNode* increment = tree_node->children[3];
    TreeNode* next_stmt = tree_node->parent->children[index_in_parent + 1];

    LinkCondition(condition, body, next_stmt, JUMP_IF_FALSE);
    LinkUnconditionally(increment, condition);

    StackPush(&continue_stack, increment); 
    StackPush(&break_stack, next_stmt);

  } break;

  case CONTINUE_STMT:{
    TreeNode* origin = tree_node;
    TreeNode* target = StackPeek(&continue_stack);
    
    LinkUnconditionally(origin, target);
    
  } break;
  case BREAK_STMT:{
    TreeNode* origin = tree_node;
    TreeNode* target = StackPeek(&break_stack);
    
    LinkUnconditionally(origin, target);

  } break;
  case RETURN_STMT:{
    TreeNode* origin = tree_node;
    TreeNode* target = function_body->children[function_body->num_of_children - 1];
    
    LinkUnconditionally(origin, target);

  } break;
  case RETURN_EXPR_STMT:{
    TreeNode* origin = tree_node;
    TreeNode* target = function_body->children[function_body->num_of_children - 1];
    
    LinkUnconditionally(origin, target);
    
  } break;

  case GOTO_STMT:{
    int found = 0;
    for(Node* curr_node = label_list.first; curr_node; curr_node = curr_node->next){
      TreeNode* curr_label = curr_node->info;
      if(curr_label->expr_node->obj_ref == tree_node->expr_node->obj_ref){
        LinkUnconditionally(tree_node, curr_label);
        found = 1;
        break;
      }
    }

    // if not resolved, add to goto list
    if(!found){
      Node* node = NodeCreateEmpty();
      node->info = tree_node;
      LinkedListInsertLast(&goto_list, node);
    }

  } break;
  case LABEL_STMT:{
    // add to label list
    Node* node = NodeCreateEmpty();
    node->info = tree_node;
    LinkedListInsertLast(&label_list, node);

    // backpatch goto statements
    for(Node* curr_node = goto_list.first; curr_node; curr_node = curr_node->next){
      TreeNode* curr_goto = curr_node->info;
      if(curr_goto->expr_node->obj_ref != tree_node->expr_node->obj_ref) continue;

      NodeDrop(LinkedListRemoveFrom(&goto_list, curr_node));
      LinkUnconditionally(curr_goto, tree_node);
    }
  } break;

  case EXPRESSION_STMT:{
    if(tree_node->children[0]->production != LOG_AND_EXPR 
        && tree_node->children[0]->production != LOG_OR_EXPR
        && tree_node->children[0]->production != LOG_NOT_EXPR) break;

    TreeNode* origin = tree_node->children[0];
    TreeNode* target = tree_node->parent->children[index_in_parent + 1];

    LinkCondition(origin, target, target, JUMP_IF_TRUE);
    // LinkUnconditionally(origin, target);
  } break;

  default: break;
  }
}

// productions that direct the jump, doesn't generate any code
// logic operators
static void LinkFlowPureLogic(TreeNode* tree_node, int index_in_parent){

  switch(tree_node->production){
  case LOG_AND_EXPR:{
    int       my_jump   = tree_node->logic_node->jump_if;
    TreeNode* my_true   = tree_node->logic_node->if_true;
    TreeNode* my_false  = tree_node->logic_node->if_false;
    TreeNode* left_son  = tree_node->children[0];
    TreeNode* right_son = tree_node->children[1];

    LinkCondition(left_son,  right_son, my_false, JUMP_IF_FALSE);
    LinkCondition(right_son, my_true,   my_false, my_jump);

  } break;
  case LOG_OR_EXPR:{
    int       my_jump   = tree_node->logic_node->jump_if;
    TreeNode* my_true   = tree_node->logic_node->if_true;
    TreeNode* my_false  = tree_node->logic_node->if_false;
    TreeNode* left_son  = tree_node->children[0];
    TreeNode* right_son = tree_node->children[1];

    LinkCondition(left_son,  my_true, right_son, JUMP_IF_TRUE);
    LinkCondition(right_son, my_true, my_false,  my_jump);

  } break;
  case LOG_NOT_EXPR:{
    int       my_jump   = tree_node->logic_node->jump_if;
    TreeNode* my_true   = tree_node->logic_node->if_true;
    TreeNode* my_false  = tree_node->logic_node->if_false;
    TreeNode* son       = tree_node->children[0];

    LinkCondition(son, my_false, my_true, my_jump == JUMP_IF_TRUE ? JUMP_IF_FALSE : JUMP_IF_TRUE);

  } break;

  case COMMA_EXPR:{
    if(tree_node->logic_node == 0) break;

    int       my_jump    = tree_node->logic_node->jump_if;
    TreeNode* my_true    = tree_node->logic_node->if_true;
    TreeNode* my_false   = tree_node->logic_node->if_false;
    TreeNode* last_child = tree_node->children[tree_node->num_of_children - 1];

    LinkCondition(last_child, my_true, my_false, my_jump);
    for(int i = 0; i < tree_node->num_of_children - 1; i++){
      LinkUnconditionally(tree_node->children[i], tree_node->children[i + 1]);
    }

  } break;

  default: break;
  }
}

// "arithmetic" part of statement links the "logic" part
// "logic" part only transfers the links to its children
// "relational" part later generates the actual jump 
void LinkFlowControl(TreeNode* tree_node, int index_in_parent){
  if(tree_node->production == FUNCTION_BODY) function_body = tree_node;

  int add_to_continue = tree_node->production == FOR_STMT
    || tree_node->production == DO_WHILE_STMT
    || tree_node->production == WHILE_STMT;
  int add_to_break = add_to_continue || tree_node->production == SWITCH_STMT;

  LinkFlowLogicToArithm(tree_node, index_in_parent);
  LinkFlowPureLogic    (tree_node, index_in_parent);

  for(int i = 0; i < tree_node->num_of_children; i++){
    LinkFlowControl(tree_node->children[i], i);
  }

  if(add_to_continue) StackPop(&continue_stack);
  if(add_to_break)    StackPop(&break_stack);

  if(tree_node->production == FUNCTION_BODY) {
    function_body = 0;
    LinkedListDelete(&label_list);
    LinkedListDelete(&goto_list);
  }
}