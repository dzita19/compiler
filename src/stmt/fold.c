#include "fold.h"

void ConstExpression(void){
  TreeNode* expr = StackPop(&tree->stack);
  ConstExpr* const_expr = ConstExprCreateEmpty();

  if(expr->production == CONSTANT_PRIMARY){
    const_expr->kind  = VAL_ARITHM;
    const_expr->value = expr->expr_node->address;
    const_expr->type = expr->expr_node->type;
  }
  else if(expr->production == ADDRESS_PRIMARY
      && (expr->expr_node->obj_ref->specifier & STORAGE_FETCH) == STORAGE_STATIC){
    const_expr->kind    = VAL_ADDRESS;
    const_expr->obj_ref = expr->expr_node->obj_ref;
    const_expr->value   = expr->expr_node->address;
    const_expr->type = expr->expr_node->type;
  }
  else if(expr->production == STRING_PRIMARY){
    const_expr->kind       = VAL_STRING;
    const_expr->string_ref = expr->expr_node->string_ref;
    const_expr->value      = expr->expr_node->address;
    const_expr->type = expr->expr_node->type;
  }

  TreeNodeDrop(expr);
  StackPush(&const_expr_stack, const_expr);
}

static int AddressAdditionFold(void){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* pointer;
  int pointer_index, value;

  if(node->children[0]->production == ADDRESS_PRIMARY
      && node->children[1]->production == CONSTANT_PRIMARY) {

    pointer = node->children[0];
    pointer_index = 0;
    value = node->children[1]->expr_node->address;
  }
  else if(node->children[1]->production == ADDRESS_PRIMARY
      && node->children[0]->production == CONSTANT_PRIMARY){

    pointer = node->children[1];
    pointer_index = 1;
    value = node->children[0]->expr_node->address;
  }
  else if(node->children[0]->production == STRING_PRIMARY
      && node->children[1]->production == CONSTANT_PRIMARY) {

    pointer = node->children[0];
    pointer_index = 0;
    value = node->children[1]->expr_node->address;
  }
  else if(node->children[1]->production == STRING_PRIMARY
      && node->children[0]->production == CONSTANT_PRIMARY){

    pointer = node->children[1];
    pointer_index = 1;
    value = node->children[0]->expr_node->address;
  }
  else return 0;

  node->children[pointer_index]->parent = node->parent;
  // node->children[pointer_index]->parent = 0;
  node->children[pointer_index] = 0;
  TreeNodeDrop(StackPop(&tree->stack));

  pointer->expr_node->address += value;
  StackPush(&tree->stack, pointer);

  return 1;
}

static int AddressSubtractionFold(void){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* pointer;
  int pointer_index, value;

  if(node->children[0]->production == ADDRESS_PRIMARY
      && node->children[1]->production == CONSTANT_PRIMARY) {

    pointer = node->children[0];
    pointer_index = 0;
    value = node->children[1]->expr_node->address;
  }
  else if(node->children[0]->production == STRING_PRIMARY
      && node->children[1]->production == CONSTANT_PRIMARY) {

    pointer = node->children[0];
    pointer_index = 0;
    value = node->children[1]->expr_node->address;
  }
  else return 0;

  node->children[pointer_index]->parent = node->parent;
  // node->children[pointer_index]->parent = 0;
  node->children[pointer_index] = 0;
  TreeNodeDrop(StackPop(&tree->stack));

  pointer->expr_node->address -= value;
  StackPush(&tree->stack, pointer);

  return 1;
}

// cast arithmetic into arithmetic or address
static int CastArithmeticFold(void){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* operand = node->children[0];

  if(operand->production != CONSTANT_PRIMARY) return 0;

  Struct* expr_type = node->expr_node->type;
  int value = operand->expr_node->address;

  TreeNodeDrop(StackPop(&tree->stack));
  TreeNode* fold = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  fold->expr_node = ExprNodeCreateEmpty();
  fold->expr_node->kind = NUM_LITERAL;
  fold->expr_node->type = expr_type;

  switch(expr_type - predefined_types_struct){
  case   INT8_T: fold->expr_node->address =   (signed char)  value; break;
  case  UINT8_T: fold->expr_node->address = (unsigned char)  value; break;
  case  INT16_T: fold->expr_node->address =   (signed short) value; break;
  case UINT16_T: fold->expr_node->address = (unsigned short) value; break;
  case  INT32_T: fold->expr_node->address =   (signed int)   value; break;
  case UINT32_T: fold->expr_node->address = (unsigned int)   value; break;
  default      : fold->expr_node->address = (unsigned int)   value; break;
  }

  return 1;
}

// cast address into address
static int CastAddressFold(void){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* operand = node->children[0];

  if(operand->production != ADDRESS_PRIMARY
    && operand->production != STRING_PRIMARY) return 0;

  if(!StructIsPointer(node->expr_node->type)) return 0; // must cast into pointer

  operand->expr_node->type = node->expr_node->type; // change type for the operand

  node->children[0] = 0;
  TreeNodeDrop(StackPop(&tree->stack));
  StackPush(&tree->stack, operand);

  return 1;
}

static int FieldRefFold(void){
  TreeNode* field_ref = StackPeek(&tree->stack);
  TreeNode* address = field_ref->children[0];

  if(address->production == ADDRESS_PRIMARY
      || address->production == CONSTANT_PRIMARY
      || address->production == STRING_PRIMARY) {

    address->expr_node->type = field_ref->expr_node->type;
    address->expr_node->address += field_ref->expr_node->address;

    field_ref->children[0] = 0;
    field_ref->parent      = 0;

    TreeNodeDrop(StackPop(&tree->stack));
    StackPush(&tree->stack, address);
    return 1;
  }
  else if(address->production == FIELD_REF_EXPR){
    address->expr_node->type = field_ref->expr_node->type;
    address->expr_node->address += field_ref->expr_node->address;

    address->parent        = 0;
    field_ref->children[0] = 0;
    field_ref->parent      = 0;

    TreeNodeDrop(StackPop(&tree->stack));
    StackPush(&tree->stack, address);
    return 1;
  }
  else return 0;
  
    
  // else if(lval->production == FIELD_REF_EXPR){
  //   lval->expr_node->type = field_ref->expr_node->type;
  //   lval->expr_node->address += field_ref->expr_node->address;

  //   lval->parent           = 0;
  //   field_ref->children[0] = 0;
  //   field_ref->parent      = 0;

  //   TreeNodeDrop(StackPop(&tree->stack));
  //   StackPush(&tree->stack, lval);
  //   return 1;
  // }
  // else return 0;
}

// returns whether the fold happened or not
static int ArithmeticUnaryFold(Production production){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* operand = node->children[0];

  if(operand->production != CONSTANT_PRIMARY) return 0;

  Struct* expr_type = node->expr_node->type;
  int value = operand->expr_node->address;

  TreeNodeDrop(StackPop(&tree->stack));
  TreeNode* fold = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  fold->expr_node = ExprNodeCreateEmpty();
  fold->expr_node->kind = NUM_LITERAL;
  fold->expr_node->type = expr_type;

  switch(production){
  case UNARY_PLUS_EXPR:
    fold->expr_node->address = +value; break;
  case UNARY_MINUS_EXPR:
    fold->expr_node->address = -value; break;
  case BIT_NOT_EXPR:
    fold->expr_node->address = ~value; break;
  case LOG_NOT_EXPR:
    fold->expr_node->address = !value; break;
  default: break;
  }

  return 1;
}

// returns whether the fold happened or not
static int ArithmeticBinaryFold(Production production){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* op1 = node->children[0];
  TreeNode* op2 = node->children[1];

  if(op1->production != CONSTANT_PRIMARY || op2->production != CONSTANT_PRIMARY) return 0;

  Struct* expr_type = node->expr_node->type;
  int value1 = op1->expr_node->address;
  int value2 = op2->expr_node->address;

  int sign = (op1->expr_node->type - (predefined_types_struct + INT8_T - 1)) & 1;

  TreeNodeDrop(StackPop(&tree->stack));
  TreeNode* fold = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  fold->expr_node = ExprNodeCreateEmpty();
  fold->expr_node->kind = NUM_LITERAL;
  fold->expr_node->type = expr_type;

  switch(production){
  case ADD_EXPR:
    fold->expr_node->address = value1 + value2;
    break;
  case SUB_EXPR:
    fold->expr_node->address = value1 - value2;
    break;

  case MUL_EXPR:
    fold->expr_node->address = value1 * value2;
    break;
  case DIV_EXPR:
    if(value2 == 0) return 0;
    if(sign) fold->expr_node->address = value1 / value2;
    else     fold->expr_node->address = (unsigned)value1 / (unsigned)value2; 
    break;
  case MOD_EXPR:
    if(value2 == 0) return 0;
    if(sign) fold->expr_node->address = value1 % value2;
    else     fold->expr_node->address = (unsigned)value1 % (unsigned)value2;
    break;

  case BIT_LEFT_EXPR:
    fold->expr_node->address = value1 << value2;
    break;
  case BIT_RIGHT_EXPR:
    if(sign) fold->expr_node->address = value1 >> value2;
    else     fold->expr_node->address = (unsigned)value1 >> (unsigned)value2;
    break;

  case RELA_GT_EXPR:
    if(sign) fold->expr_node->address = value1 > value2;
    else     fold->expr_node->address = (unsigned)value1 > (unsigned)value2;
    break;
  case RELA_LT_EXPR:
    if(sign) fold->expr_node->address = value1 < value2;
    else     fold->expr_node->address = (unsigned)value1 < (unsigned)value2;
    break;
  case RELA_GE_EXPR:
    if(sign) fold->expr_node->address = value1 >= value2;
    else     fold->expr_node->address = (unsigned)value1 >= (unsigned)value2;
    break;
  case RELA_LE_EXPR:
    if(sign) fold->expr_node->address = value1 <= value2;
    else     fold->expr_node->address = (unsigned)value1 <= (unsigned)value2;
    break;

  case RELA_EQ_EXPR:
    fold->expr_node->address = value1 == value2;
    break;
  case RELA_NQ_EXPR:
    fold->expr_node->address = value1 != value2;
    break;

  case BIT_AND_EXPR:
    fold->expr_node->address = value1 & value2;
    break;
  case BIT_XOR_EXPR:
    fold->expr_node->address = value1 ^ value2;
    break;
  case BIT_OR_EXPR:
    fold->expr_node->address = value1 | value2;
    break;

  case LOG_AND_EXPR:
    fold->expr_node->address = value1 && value2;
    break;
  case LOG_OR_EXPR:
    fold->expr_node->address = value1 || value2;
    break;

  default: break;
  }

  return 1;
}

static int ArithmeticBinaryNeutralFold(Production production){
  TreeNode* node = StackPeek(&tree->stack);

  int const_index;
  int var_index;

  if(node->children[0]->production == CONSTANT_PRIMARY) {
    const_index = 0;
    var_index = 1;
  }
  else if(node->children[1]->production == CONSTANT_PRIMARY) {
    const_index = 1;
    var_index = 0;
  }
  else return 0;

  TreeNode* constant_op = node->children[const_index];
  TreeNode* var_op = node->children[const_index == 0 ? 1 : 0];

  int sign = constant_op->expr_node->type == predefined_types_struct + INT32_T;
  int neutral_value = 0; // value that doesn't affect the result
  int fold_value    = 0; // value of operand that triggers fold
  int fold_result   = 0; // result of the fold

  int try_modes     = 0; // select if neutral or fold (or both) should be attempted

#define TRY_NEUTRAL (1 << 0)
#define TRY_FOLD    (1 << 1)

  switch(production){
  case ADD_EXPR: neutral_value = 0; try_modes = TRY_NEUTRAL; break;
  case SUB_EXPR: neutral_value = 0; try_modes = TRY_NEUTRAL; break;

  case MUL_EXPR:
    neutral_value = 1;
    fold_value    = 0;
    fold_result   = 0;
    try_modes     = TRY_NEUTRAL | TRY_FOLD; 
    break;
  case DIV_EXPR: 
    neutral_value = 1;
    try_modes     = TRY_NEUTRAL;
    break;
  case MOD_EXPR:
    fold_value    = 1;
    fold_result   = 0;
    try_modes     = TRY_FOLD;
    break;

  case BIT_LEFT_EXPR:  neutral_value = 0; try_modes = TRY_NEUTRAL; break;
  case BIT_RIGHT_EXPR: neutral_value = 0; try_modes = TRY_NEUTRAL; break;

  case RELA_GT_EXPR: // returns 0 if maximum value
    if(sign) fold_value = 0x7FFFFFFF; // maximum   signed value
    else     fold_value = 0xFFFFFFFF; // maximum unsigned value
    fold_result         = 0;
    try_modes           = TRY_FOLD;
    break;

  case RELA_LT_EXPR: // returns 0 if minimum value
    if(sign) fold_value = 0x80000000; // minimum   signed value
    else     fold_value = 0x00000000; // minimum unsigned value
    fold_result = 0;
    try_modes = TRY_FOLD;
    break;

  case RELA_GE_EXPR: // returns 1 if minimum value
    if(sign) fold_value = 0x80000000; // minimum   signed value
    else     fold_value = 0x00000000; // minimum unsigned value
    fold_result         = 1;
    try_modes           = TRY_FOLD;
    break;

  case RELA_LE_EXPR: // returns 1 if maximum value
    if(sign) fold_value = 0x7FFFFFFF; // maximum   signed value
    else     fold_value = 0xFFFFFFFF; // maximum unsigned value
    fold_result         = 1;
    try_modes           = TRY_FOLD;
    break;

  case RELA_EQ_EXPR: break;
  case RELA_NQ_EXPR: break;

  case BIT_AND_EXPR:
    neutral_value = 0xFFFFFFFF;
    fold_value    = 0x00000000;
    fold_result   = 0x00000000;
    try_modes     = TRY_NEUTRAL | TRY_FOLD;
    break;
  case BIT_XOR_EXPR:
    neutral_value = 0x00000000;
    try_modes     = TRY_NEUTRAL;
    break;
  case BIT_OR_EXPR:
    neutral_value = 0x00000000;
    fold_value    = 0xFFFFFFFF;
    fold_result   = 0xFFFFFFFF;
    try_modes     = TRY_NEUTRAL | TRY_FOLD;
    break;

  case LOG_AND_EXPR:
    neutral_value = 1;
    fold_value    = 0;
    fold_value    = 0;
    try_modes     = TRY_NEUTRAL | TRY_FOLD;
    break;
  case LOG_OR_EXPR:
    neutral_value = 0;
    fold_value    = 1;
    fold_value    = 1;
    try_modes     = TRY_NEUTRAL | TRY_FOLD;
    break;

  default: break;
  }

  // remove neutral operand
  if(constant_op->expr_node->address == neutral_value
      && (try_modes & TRY_NEUTRAL)) {
    var_op->parent = node->parent;
    // var_op->parent = 0;
    node->children[var_index] = 0;
    TreeNodeDrop(StackPop(&tree->stack));
    StackPush(&tree->stack, var_op);

    return 1;
  }

  // fold operation
  if(constant_op->expr_node->address == fold_value
      && (try_modes & TRY_FOLD)) {
    Struct* expr_type = node->expr_node->type;

    TreeNodeDrop(StackPop(&tree->stack));
    TreeNode* fold = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

    fold->expr_node = ExprNodeCreateEmpty();
    fold->expr_node->kind = NUM_LITERAL;
    fold->expr_node->type = expr_type;
    fold->expr_node->address = fold_result;

    return 1;
  }

  return 0;
}

static int LogicFold(Production production){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* op1 = node->children[0];
  TreeNode* op2 = node->children[1];

  if(op1->production != CONSTANT_PRIMARY) return 0;

  Struct* expr_type = node->expr_node->type;
  int value1 = op1->expr_node->address;

  if(production == LOG_AND_EXPR){
    // fold
    if(value1 == 0){
      TreeNodeDrop(StackPop(&tree->stack));
      TreeNode* fold = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

      fold->expr_node = ExprNodeCreateEmpty();
      fold->expr_node->kind = NUM_LITERAL;
      fold->expr_node->type = expr_type;
      fold->expr_node->address = 0;
    }
    // neutral
    else {
      op2->parent = node->parent;
      node->children[1] = 0;
      TreeNodeDrop(StackPop(&tree->stack));
      StackPush(&tree->stack, op2);

      // fold anyway
      if(op2->production == CONSTANT_PRIMARY && op2->expr_node->address != 0)
        op2->expr_node->address = 1;
    }
    return 1;
  }
  else if(production == LOG_OR_EXPR){
    // fold
    if(value1 != 0){
      TreeNodeDrop(StackPop(&tree->stack));
      TreeNode* fold = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

      fold->expr_node = ExprNodeCreateEmpty();
      fold->expr_node->kind = NUM_LITERAL;
      fold->expr_node->type = expr_type;
      fold->expr_node->address = 1;
    }
    // neutral
    else {
      op2->parent = node->parent;
      node->children[1] = 0;
      TreeNodeDrop(StackPop(&tree->stack));
      StackPush(&tree->stack, op2);

      // fold anyway
      if(op2->production == CONSTANT_PRIMARY && op2->expr_node->address != 0)
        op2->expr_node->address = 1;
    }
    return 1;
  }

  return 0;
}

static int TernaryFold(void){
  TreeNode* node = StackPeek(&tree->stack);
  TreeNode* cond     = node->children[0];
  TreeNode* if_true  = node->children[1];
  TreeNode* if_false = node->children[2];

  if(cond->production != CONSTANT_PRIMARY) return 0;
  int value = cond->expr_node->address;

  TreeNode* folded = value != 0 ? if_true : if_false;

  folded->parent = node->parent;
  // folded->parent = 0;
  node->children[value != 0 ? 1 : 2] = 0;
  TreeNodeDrop(StackPop(&tree->stack));
  StackPush(&tree->stack, folded);

  return 1;
}

void TryFold(void){
  TreeNode* node = StackPeek(&tree->stack);

  switch(node->production){
  case CAST_EXPR:{
    int folded = 0;
    folded = CastArithmeticFold();
    if(folded) break;
    folded = CastAddressFold();
    if(folded) break;
  }
  break;

  case FIELD_REF_EXPR:
    FieldRefFold();
    break;

  case UNARY_PLUS_EXPR:
  case UNARY_MINUS_EXPR:
  case BIT_NOT_EXPR:
  case LOG_NOT_EXPR:
    ArithmeticUnaryFold(node->production);
    break;

  case ADD_EXPR:
  case SUB_EXPR: {
    int folded = 0;
    if(node->production == ADD_EXPR){
      folded = AddressAdditionFold();
    }
    else{
      folded = AddressSubtractionFold();
    }
    if(folded) break;
  }
  case MUL_EXPR:
  case DIV_EXPR:
  case MOD_EXPR:

  case BIT_LEFT_EXPR:
  case BIT_RIGHT_EXPR:

  case RELA_GT_EXPR:
  case RELA_LT_EXPR:
  case RELA_GE_EXPR:
  case RELA_LE_EXPR:

  case RELA_EQ_EXPR:
  case RELA_NQ_EXPR:

  case BIT_AND_EXPR:
  case BIT_XOR_EXPR:
  case BIT_OR_EXPR: {
    int folded = 0;
    folded = ArithmeticBinaryFold(node->production);
    if(folded) break;
    folded = ArithmeticBinaryNeutralFold(node->production);
  } break;

  case LOG_AND_EXPR:
  case LOG_OR_EXPR:
    LogicFold(node->production);
    break;

  case COND_EXPR:
    TernaryFold();
    break;

  default: break;
  }
}