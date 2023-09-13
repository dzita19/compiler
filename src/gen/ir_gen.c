#include "ir_gen.h"

#include "util/array.h"
#include "stmt/tree.h"

static Obj* current_function = 0;

static void AllocateNodeLabel(TreeNode* tree_node){
  if(tree_node->label < 0) tree_node->label = ++label_counter;
}

static void GenerateNodeLabel(TreeNode* tree_node){
  if(tree_node->label == 0) return;

  AllocateNodeLabel(tree_node);
  InsertNewLabel(tree_node->label);
}

static void GenerateJump(TreeNode* tree_node){
  if(tree_node->logic_node == 0) return;

  if(tree_node->logic_node->jump_if == JUMP_ALWAYS){
    AllocateNodeLabel(tree_node->logic_node->if_true);
    InsertInstrLabel(IR_JMP, tree_node->logic_node->if_true->label);
  }
}

static int ArithmeticExprUsed(TreeNode* tree_node){
  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT
    && tree_node->parent->production != SWITCH_STMT
    && tree_node->parent->production != RETURN_EXPR_STMT) return 0;

  return 1;
}

static int IsAssignmentAddress(TreeNode* tree_node){
  switch(tree_node->parent->production){
  case ASSIGN_EXPR:
  case MUL_ASSIGN_EXPR:
  case DIV_ASSIGN_EXPR:
  case MOD_ASSIGN_EXPR:
  case ADD_ASSIGN_EXPR:
  case SUB_ASSIGN_EXPR:
  case BIT_LEFT_ASSIGN_EXPR:
  case BIT_RIGHT_ASSIGN_EXPR:
  case BIT_AND_ASSIGN_EXPR:
  case BIT_XOR_ASSIGN_EXPR: 
  case BIT_OR_ASSIGN_EXPR:

  case PRE_INC_EXPR:
  case PRE_DEC_EXPR:
  case POST_INC_EXPR:
  case POST_DEC_EXPR:
    return tree_node->parent->children[0] == tree_node;
  default:
    return 0;
  }
}



static void StructCopyToMem(TreeNode* tree_node){
  int size = tree_node->expr_node->type->size;
  int long_count = (size >> 2);
  int word_count = (size >> 1) & 1;
  int byte_count = (size >> 0) & 1;

  int offset = 0;
  for(int i = 0; i < long_count; i++){
    InsertInstrStackRead(IR_PUSHL, IR_ADDR_INDIRECT, 0, offset);
    InsertInstrStackRead(IR_STORL, IR_ADDR_INDIRECT, 2, offset);
    offset += 4;
  }
  if(word_count){
    InsertInstrStackRead(IR_PUSHW, IR_ADDR_INDIRECT, 0, offset);
    InsertInstrStackRead(IR_STORW, IR_ADDR_INDIRECT, 2, offset);
    offset += 2;
  }
  if(byte_count){
    InsertInstrStackRead(IR_PUSHB, IR_ADDR_INDIRECT, 0, offset);
    InsertInstrStackRead(IR_STORB, IR_ADDR_INDIRECT, 2, offset);
    offset += 1;
  }

  InsertInstrStackPop(IR_POP);
  InsertInstrStackPop(IR_POP);
}

static void StructCopyToArg(TreeNode* tree_node, int dst_offset){
  int size = tree_node->expr_node->type->size;
  int long_count = (size >> 2);
  int word_count = (size >> 1) & 1;
  int byte_count = (size >> 0) & 1;

  int offset = 0;
  for(int i = 0; i < long_count; i++){
    InsertInstrStackRead(IR_PUSHL, IR_ADDR_INDIRECT, 0, offset);
    InsertInstrArg(IR_STORL, IR_ADDR_INDIRECT, dst_offset + offset);
    offset += 4;
  }
  if(word_count){
    InsertInstrStackRead(IR_PUSHW, IR_ADDR_INDIRECT, 0, offset);
    InsertInstrArg(IR_STORW, IR_ADDR_INDIRECT, dst_offset + offset);
    offset += 2;
  }
  if(byte_count){
    InsertInstrStackRead(IR_PUSHB, IR_ADDR_INDIRECT, 0, offset);
    InsertInstrArg(IR_STORB, IR_ADDR_INDIRECT, dst_offset + offset);
    offset += 1;
  }

  InsertInstrStackPop(IR_POP);
}

static void ScalarCopyToArg(TreeNode* tree_node, int dst_offset){
  int size_opcode = 0;
  if     (tree_node->expr_node->type->size == 1) size_opcode = IR_STORB - IR_STORB;
  else if(tree_node->expr_node->type->size == 2) size_opcode = IR_STORW - IR_STORB;
  else if(tree_node->expr_node->type->size == 4) size_opcode = IR_STORL - IR_STORB;

  InsertInstrArg(IR_STORB + size_opcode, IR_ADDR_INDIRECT, dst_offset);
}

// offset is used only when copying structs
// +1
static void GeneratePrimary(TreeNode* tree_node){
  int size_opcode = 0;
  if     (tree_node->expr_node->type->size == 1) size_opcode = IR_DERFB - IR_DERFB;
  else if(tree_node->expr_node->type->size == 2) size_opcode = IR_DERFW - IR_DERFB;
  else if(tree_node->expr_node->type->size == 4) size_opcode = IR_DERFL - IR_DERFB;

  if(tree_node->production == ADDRESS_PRIMARY){
    InsertInstrObj(IR_PUSHB + size_opcode, IR_ADDR_DIRECT, 
      tree_node->expr_node->obj_ref, tree_node->expr_node->address);
  }
  else if(tree_node->production == CONSTANT_PRIMARY){
    InsertInstrArithm(IR_PUSHB + size_opcode, IR_ADDR_DIRECT,
      tree_node->expr_node->address);
  }
  else if(tree_node->production == STRING_PRIMARY){
    InsertInstrString(IR_PUSHB + size_opcode, IR_ADDR_DIRECT,
      tree_node->expr_node->string_ref, tree_node->expr_node->address);
  }

  if(ArithmeticExprUsed(tree_node));
  else InsertInstrStackPop(IR_POP);
}

// +0
static void GenerateDeref(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);

  if(ArithmeticExprUsed(tree_node)) {
    int size_opcode = 0;
    if     (tree_node->expr_node->type->size == 1) size_opcode = IR_DERFB - IR_DERFB;
    else if(tree_node->expr_node->type->size == 2) size_opcode = IR_DERFW - IR_DERFB;
    else if(tree_node->expr_node->type->size == 4) size_opcode = IR_DERFL - IR_DERFB;

    if(!IsAssignmentAddress(tree_node)) InsertInstrStackPop(IR_DERFB + size_opcode);
  }
  else InsertInstrStackPop(IR_POP);
}

// +0
static void GenerateFieldRef(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);

  if(ArithmeticExprUsed(tree_node)) {
    InsertInstrArithm(IR_ADD, IR_ADDR_DIRECT, tree_node->expr_node->address);
    
    int size_opcode = 0;
    if     (tree_node->expr_node->type->size == 1) size_opcode = IR_DERFB - IR_DERFB;
    else if(tree_node->expr_node->type->size == 2) size_opcode = IR_DERFW - IR_DERFB;
    else if(tree_node->expr_node->type->size == 4) size_opcode = IR_DERFL - IR_DERFB;
    
    if(!IsAssignmentAddress(tree_node)) InsertInstrStackPop(IR_DERFB + size_opcode);
  }
  else InsertInstrStackPop(IR_POP);
}

static void GenerateUnary(TreeNode* tree_node){
  switch(tree_node->production){
  case UNARY_PLUS_EXPR:  {
    GenerateIntermediate(tree_node->children[0]);
    if(ArithmeticExprUsed(tree_node)) InsertInstrNoOp(IR_NOP);
    else InsertInstrStackPop(IR_POP);
  } break;

  case UNARY_MINUS_EXPR: {
    GenerateIntermediate(tree_node->children[0]);
    if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_NEG);
    else InsertInstrStackPop(IR_POP);
  } break;

  case BIT_NOT_EXPR:     {
    GenerateIntermediate(tree_node->children[0]);
    if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_NOT);
    else InsertInstrStackPop(IR_POP);
  } break;

  case POST_INC_EXPR:    
  case POST_DEC_EXPR:    {
    GenerateIntermediate(tree_node->children[0]);

    int size = 0;
    if     (tree_node->children[0]->expr_node->type->size == 1) size = IR_DERFB - IR_DERFB;
    else if(tree_node->children[0]->expr_node->type->size == 2) size = IR_DERFW - IR_DERFB;
    else if(tree_node->children[0]->expr_node->type->size == 4) size = IR_DERFL - IR_DERFB;

    if(ArithmeticExprUsed(tree_node)) {
      InsertInstrNoOp(IR_NOP);
      InsertInstrStackPop(IR_FDRFB + size); // +1
    }
    InsertInstrStackPop(IR_DUP); // +1
    InsertInstrStackPop(IR_DERFB + size); // +0

    // cast into int32; +0
    Struct* from = StructGetUnqualified(tree_node->children[0]->expr_node->type);
    if(StructIsPointer(from)) from = predefined_types_struct + UINT32_T;

    int from_rank = (from - predefined_types_struct -  INT8_T) >> 1;
    int from_sign = (from - predefined_types_struct - UINT8_T)  & 1;

    if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
    else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
    else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
    else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);

    GenerateIntermediate(tree_node->children[1]); // +1
    if(tree_node->production == POST_INC_EXPR) InsertInstrStackPop(IR_ADD); // -1
    if(tree_node->production == POST_DEC_EXPR) InsertInstrStackPop(IR_SUB); // -1
    InsertInstrStackPop(IR_STORB + size);

    // cast into int32; +0
    if(ArithmeticExprUsed(tree_node)){
      if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
      else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
      else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
      else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
    }
  } break;
  case PRE_INC_EXPR:     
  case PRE_DEC_EXPR:     {
    GenerateIntermediate(tree_node->children[0]);

    int size = 0;
    if     (tree_node->children[0]->expr_node->type->size == 1) size = IR_DERFB - IR_DERFB;
    else if(tree_node->children[0]->expr_node->type->size == 2) size = IR_DERFW - IR_DERFB;
    else if(tree_node->children[0]->expr_node->type->size == 4) size = IR_DERFL - IR_DERFB;

    if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_DUP); // +1
    InsertInstrStackPop(IR_DUP); // +1
    InsertInstrStackPop(IR_DERFB + size); // +0

    // cast into int32; +0
    Struct* from = StructGetUnqualified(tree_node->children[0]->expr_node->type);
    if(StructIsPointer(from)) from = predefined_types_struct + UINT32_T;

    int from_rank = (from - predefined_types_struct -  INT8_T) >> 1;
    int from_sign = (from - predefined_types_struct - UINT8_T)  & 1;

    if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
    else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
    else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
    else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
    
    GenerateIntermediate(tree_node->children[1]); // +1
    if(tree_node->production == PRE_INC_EXPR) InsertInstrStackPop(IR_ADD); // -1
    if(tree_node->production == PRE_DEC_EXPR) InsertInstrStackPop(IR_SUB); // -1
    InsertInstrStackPop(IR_STORB + size); // -1
    
    if(ArithmeticExprUsed(tree_node)){
      InsertInstrStackPop(IR_DERFB + size); // +0

      // cast into int32; +0
      if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
      else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
      else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
      else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
    }
  } break;

  case CAST_EXPR:        {
    GenerateIntermediate(tree_node->children[0]);

    if(ArithmeticExprUsed(tree_node)) {
      Struct* from = StructGetUnqualified(tree_node->children[0]->expr_node->type);
      Struct* to   = StructGetUnqualified(tree_node->expr_node->type);

      if(StructIsPointer(from)) from = predefined_types_struct + UINT32_T;
      if(StructIsPointer(to))   to   = predefined_types_struct + UINT32_T;

      int from_rank = (from - predefined_types_struct -  INT8_T) >> 1;
      int to_rank   = (to   - predefined_types_struct -  INT8_T) >> 1;
      int from_sign = (from - predefined_types_struct - UINT8_T)  & 1;

      if(to_rank == 0){
        if     (from_rank == 1) InsertInstrArithm(IR_AND, IR_ADDR_DIRECT, 0xff);
        else if(from_rank == 2) InsertInstrArithm(IR_AND, IR_ADDR_DIRECT, 0xff);
      }
      else if(to_rank == 1){
        if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBW);
        else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBW);
        else if(from_rank == 2) InsertInstrArithm(IR_AND, IR_ADDR_DIRECT, 0xffff);
      }
      else if(to_rank == 2){
        if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
        else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
        else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
        else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
      }
    }
    else InsertInstrStackPop(IR_POP);

  } break;
  default: break;
  }
}

static void GenerateBinary(TreeNode* tree_node){
  int instr = IR_NOP;

  GenerateIntermediate(tree_node->children[0]);
  GenerateIntermediate(tree_node->children[1]);

  if(ArithmeticExprUsed(tree_node)){
    switch(tree_node->production){
    case MUL_EXPR: {
      int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
      if(sign) instr = IR_IMUL;
      else     instr = IR_MUL;
    } break;
    case DIV_EXPR: {
      int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
      if(sign) instr = IR_IDIV;
      else     instr = IR_DIV;
    } break;
    case MOD_EXPR: {
      int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
      if(sign) instr = IR_IMOD;
      else     instr = IR_MOD;
    } break;

    case ADD_EXPR: instr = IR_ADD; break;
    case SUB_EXPR: instr = IR_SUB; break;

    case BIT_LEFT_EXPR: {
      int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
      if(sign) instr = IR_ASL;
      else     instr = IR_LSL;
    } break;
    case BIT_RIGHT_EXPR: {
      int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
      if(sign) instr = IR_ASR;
      else     instr = IR_LSR;
    } break;

    case BIT_AND_EXPR: instr = IR_AND; break;
    case BIT_XOR_EXPR: instr = IR_XOR; break;
    case BIT_OR_EXPR:  instr = IR_OR;  break;
    default: break;
    }

    InsertInstrStackPop(instr);
  }
  else{
    InsertInstrStackPop(IR_POP);
    InsertInstrStackPop(IR_POP);
  }
}

static void GenerateFunctionCall(TreeNode* tree_node){
  CallFrame* call_frame = CallFrameCreateEmpty();
  int arg_frame_size = 0;

  Array arg_allocs = (Array){ 0, 0 }; // Array(ArgAlloc*)
  ArrayAlloc(&arg_allocs, sizeof(ArgAlloc*), tree_node->num_of_children);

  // find arg frame size
  for(int i = 1; i < tree_node->num_of_children; i++){
    TreeNode* child = tree_node->children[i];
    ArgAlloc* current_arg_alloc = GetArgAllocation(call_frame, child->expr_node->type);
    *(ArgAlloc**)ArrayGet(&arg_allocs, i) = current_arg_alloc;

    if(current_arg_alloc->mode == ARG_TO_STACK){
      arg_frame_size = current_arg_alloc->addr + child->expr_node->type->size;
    }
  }

  InsertInstrArithm(IR_ALIGN, IR_ADDR_DIRECT, arg_frame_size);

  for(int i = 1; i < tree_node->num_of_children; i++){
    TreeNode* child = tree_node->children[i];
    ArgAlloc* current_arg_alloc = *(ArgAlloc**)ArrayGet(&arg_allocs, i);

    GenerateIntermediate(child);
    if(StructIsScalar(child->expr_node->type)) ScalarCopyToArg(child, current_arg_alloc->addr);
    else StructCopyToArg(child, current_arg_alloc->addr);

    ArgAllocDrop(current_arg_alloc);
  }

  GenerateSequencePoint();

  GenerateIntermediate(tree_node->children[0]);
  InsertInstrStackPop(IR_CALL);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_GETRET); // +1
  InsertInstrArithm(IR_DEALGN, IR_ADDR_DIRECT, arg_frame_size);

  ArrayFree(&arg_allocs);
  CallFrameDrop(call_frame);
}

static void GenerateRelation(TreeNode* tree_node){
  int instr_true  = IR_NOP;
  int instr_false = IR_NOP;
  // if(tree_node->parent->production == COND_EXPR) InsertInstrNoOp(IR_LOGENT);

  GenerateIntermediate(tree_node->children[0]);
  GenerateIntermediate(tree_node->children[1]);

  int sign = (tree_node->children[0]->expr_node->type - (predefined_types_struct + UINT8_T)) & 1;

  if(sign){
    switch(tree_node->production){
    case RELA_GT_EXPR: instr_true = IR_JGT; instr_false = IR_JLE; break;
    case RELA_LT_EXPR: instr_true = IR_JLT; instr_false = IR_JGE; break;
    case RELA_GE_EXPR: instr_true = IR_JGE; instr_false = IR_JLT; break;
    case RELA_LE_EXPR: instr_true = IR_JLE; instr_false = IR_JGT; break;
    case RELA_EQ_EXPR: instr_true = IR_JEQ; instr_false = IR_JNQ; break;
    case RELA_NQ_EXPR: instr_true = IR_JNQ; instr_false = IR_JEQ; break;
    default: break;
    }
  }
  else{
    switch(tree_node->production){
    case RELA_GT_EXPR: instr_true = IR_JA;  instr_false = IR_JBE; break;
    case RELA_LT_EXPR: instr_true = IR_JB;  instr_false = IR_JAE; break;
    case RELA_GE_EXPR: instr_true = IR_JAE; instr_false = IR_JB;  break;
    case RELA_LE_EXPR: instr_true = IR_JBE; instr_false = IR_JA;  break;
    case RELA_EQ_EXPR: instr_true = IR_JEQ; instr_false = IR_JNQ; break;
    case RELA_NQ_EXPR: instr_true = IR_JNQ; instr_false = IR_JEQ; break;
    default: break;
    }
  }

  InsertInstrStackPop(IR_CMP);
  if(tree_node->logic_node->jump_if == JUMP_IF_TRUE) {
    AllocateNodeLabel(tree_node->logic_node->if_true);
    InsertInstrLabel(instr_true, tree_node->logic_node->if_true->label);
  }
  if(tree_node->logic_node->jump_if == JUMP_IF_FALSE) {
    AllocateNodeLabel(tree_node->logic_node->if_false);
    InsertInstrLabel(instr_false, tree_node->logic_node->if_false->label);
  }
}

static void GenerateLogicUnary(TreeNode* tree_node){
  // if(tree_node->parent->production == COND_EXPR) InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
}

static void GenerateLogicBinary(TreeNode* tree_node){
  // if(tree_node->parent->production == COND_EXPR) InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();
  GenerateIntermediate(tree_node->children[1]);
}

static void GenerateCond(TreeNode* tree_node){

  InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();

  GenerateIntermediate(tree_node->children[1]); // if_true
  InsertInstrStackPop(IR_VPOP);
  GenerateIntermediate(tree_node->children[2]); // if_false
  InsertInstrStackPop(IR_VPOP);

  GenerateIntermediate(tree_node->children[3]); // next_expr

  InsertInstrNoOp(IR_LOGEXT);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_COND);
}

// assign doesn't generate value if it's first node in expression statement
static void GenerateAssign(TreeNode* tree_node){
  int size_opcode = 0;
  if     (tree_node->expr_node->type->size == 1) size_opcode = IR_STORB - IR_STORB;
  else if(tree_node->expr_node->type->size == 2) size_opcode = IR_STORW - IR_STORB;
  else if(tree_node->expr_node->type->size == 4) size_opcode = IR_STORL - IR_STORB;

  GenerateIntermediate(tree_node->children[0]);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_DUP);
  GenerateIntermediate(tree_node->children[1]);

  InsertInstrStackPop(IR_STORB + size_opcode);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_DERFB + size_opcode);
}

static void GenerateArithmAssign(TreeNode* tree_node){
  int size = 0;
  if     (tree_node->children[0]->expr_node->type->size == 1) size = IR_STORB - IR_STORB;
  else if(tree_node->children[0]->expr_node->type->size == 2) size = IR_STORW - IR_STORB;
  else if(tree_node->children[0]->expr_node->type->size == 4) size = IR_STORL - IR_STORB;

  GenerateIntermediate(tree_node->children[0]);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_DUP);
  InsertInstrStackPop(IR_DUP);
  InsertInstrStackPop(IR_DERFB + size);

  // cast into int32
  Struct* from = tree_node->children[0]->expr_node->type;
  if(StructIsPointer(from)) from = predefined_types_struct + UINT32_T;

  int from_rank = (from - predefined_types_struct -  INT8_T) >> 1;
  int from_sign = (from - predefined_types_struct - UINT8_T)  & 1;

  if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
  else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
  else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
  else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);

  GenerateIntermediate(tree_node->children[1]);

  int instr = 0;
  switch(tree_node->production){
  case MUL_ASSIGN_EXPR: {
    int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
    if(sign) instr = IR_IMUL;
    else     instr = IR_MUL;
  } break;
  case DIV_ASSIGN_EXPR: {
    int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
    if(sign) instr = IR_IDIV;
    else     instr = IR_DIV;
  } break;
  case MOD_ASSIGN_EXPR: {
    int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
    if(sign) instr = IR_IMOD;
    else     instr = IR_MOD;
  } break;
  case ADD_ASSIGN_EXPR: instr = IR_ADD; break;
  case SUB_ASSIGN_EXPR: instr = IR_SUB; break;
  case BIT_LEFT_ASSIGN_EXPR: {
    int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
    if(sign) instr = IR_ASL;
    else     instr = IR_LSL;
  } break;
  case BIT_RIGHT_ASSIGN_EXPR: {
    int sign = (tree_node->expr_node->type - predefined_types_struct - UINT8_T)  & 1;
    if(sign) instr = IR_ASR;
    else     instr = IR_LSR;
  } break;
  case BIT_AND_ASSIGN_EXPR: instr = IR_AND; break;
  case BIT_XOR_ASSIGN_EXPR: instr = IR_XOR; break;
  case BIT_OR_ASSIGN_EXPR:  instr = IR_OR;  break;
  default: break;
  }

  InsertInstrStackPop(instr);

  InsertInstrStackPop(IR_STORB + size);
  if(ArithmeticExprUsed(tree_node)){
    InsertInstrStackPop(IR_DERFB + size);

    if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
    else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
    else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
    else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
  }
}

static void GenerateComma(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children - 1; i++){
    GenerateIntermediate(tree_node->children[i]);
    InsertInstrStackPop(IR_POP);
    GenerateSequencePoint();
  }
  
  GenerateIntermediate(tree_node->children[tree_node->num_of_children - 1]);
  if(ArithmeticExprUsed(tree_node));
  else InsertInstrStackPop(IR_POP);
}

// +1
static void GenerateDerefStruct(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);
  if(ArithmeticExprUsed(tree_node));
  else InsertInstrStackPop(IR_POP);
}

static void GenerateFieldRefStruct(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);
  if(ArithmeticExprUsed(tree_node)) InsertInstrArithm(IR_ADD, IR_ADDR_DIRECT, tree_node->expr_node->address);
  else InsertInstrStackPop(IR_POP);
}

static void GenerateFunctionCallStruct(TreeNode* tree_node){
  CallFrame* call_frame = CallFrameCreateEmpty();
  int arg_frame_size = 0;

  Array arg_allocs = (Array){ 0, 0 }; // Array(ArgAlloc*)
  ArrayAlloc(&arg_allocs, sizeof(ArgAlloc*), tree_node->num_of_children);

  // arg zero (address for return value)
  ArgAlloc* ret_val_addr = GetReturnAddressAllocation(call_frame);
  arg_frame_size = ret_val_addr->addr + POINTER_SIZE;

  // find arg frame size
  for(int i = 1; i < tree_node->num_of_children; i++){
    TreeNode* child = tree_node->children[i];
    ArgAlloc* current_arg_alloc = GetArgAllocation(call_frame, child->expr_node->type);
    *(ArgAlloc**)ArrayGet(&arg_allocs, i) = current_arg_alloc;

    if(current_arg_alloc->mode == ARG_TO_STACK){
      arg_frame_size = current_arg_alloc->addr + child->expr_node->type->size;
    }
  }

  InsertInstrArithm(IR_ALIGN, IR_ADDR_DIRECT, arg_frame_size);
  // duplicate return address - generated in parent function
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_DUP);

  // store return value address as arg zero
  InsertInstrArg(IR_STORL, IR_ADDR_INDIRECT, ret_val_addr->addr);

  for(int i = 1; i < tree_node->num_of_children; i++){
    TreeNode* child = tree_node->children[i];
    ArgAlloc* current_arg_alloc = *(ArgAlloc**)ArrayGet(&arg_allocs, i);

    GenerateIntermediate(child);
    if(StructIsScalar(child->expr_node->type)) ScalarCopyToArg(child, current_arg_alloc->addr);
    else StructCopyToArg(child, current_arg_alloc->addr);

    ArgAllocDrop(current_arg_alloc);
  }

  GenerateSequencePoint();

  GenerateIntermediate(tree_node->children[0]);
  InsertInstrStackPop(IR_CALL);
  InsertInstrArithm(IR_DEALGN, IR_ADDR_DIRECT, arg_frame_size);

  ArgAllocDrop(ret_val_addr);
  ArrayFree(&arg_allocs);
  CallFrameDrop(call_frame);
}

static void GenerateCondStruct(TreeNode* tree_node){
  InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();

  GenerateIntermediate(tree_node->children[1]);
  InsertInstrStackPop(IR_VPOP);
  GenerateIntermediate(tree_node->children[2]);
  InsertInstrStackPop(IR_VPOP);

  GenerateIntermediate(tree_node->children[3]);

  InsertInstrNoOp(IR_LOGEXT);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_COND); 
}

static void GenerateAssignStruct(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);
  if(ArithmeticExprUsed(tree_node)) InsertInstrStackPop(IR_DUP);
  
  GenerateIntermediate(tree_node->children[1]);

  if(tree_node->children[1]->production == FUNCTION_CALL_EXPR) InsertInstrStackPop(IR_POP); 
  else StructCopyToMem(tree_node); //  removes assignment address
}

static void GenerateCommaStruct(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children - 1; i++){
    GenerateIntermediate(tree_node->children[i]);
    InsertInstrStackPop(IR_POP);
    GenerateSequencePoint();
  }
  
  GenerateIntermediate(tree_node->children[tree_node->num_of_children - 1]);
  if(ArithmeticExprUsed(tree_node));
  else InsertInstrStackPop(IR_POP);
}

static int MergeTables(Vector* tab1, Vector* tab2){
  long size1 = tab1->size;
  long size2 = tab2->size;
  TreeNode* tab1_first = VectorGet(tab1, 0);
  TreeNode* tab2_last  = VectorGet(tab2, tab2->size - 1);
  long total_size = tab2_last->expr_node->address - tab1_first->expr_node->address + 1;

  if(3 * (size1 + size2) >= 2 * total_size){
    for(int i = 0; i < tab2->size; i++) VectorPush(tab1, VectorGet(tab2, i));
    return 1;
  }
  else return 0;
}

static void GenerateSwitchTables(TreeNode* tree_node){
  static int switch_index = 0;

  LinkedList* case_list = VectorGet(switch_archive, switch_index);
  LinkedList* tables = LinkedListCreateEmpty();
  
  Node* start_node = case_list->first;
  if(case_list->first){
    TreeNode* case_node = case_list->first->info;
    if(case_node->expr_node->kind == DEFAULT_LABEL) start_node = case_list->first->next;
  }

  // generate a table for every node
  for(Node* case_node = start_node; case_node; case_node = case_node->next){
    Node* table_node = NodeCreateEmpty();
    Vector* table = VectorInit();
    VectorPush(table, case_node->info);
    table_node->info = table;
    
    LinkedListInsertLast(tables, table_node);
  }

  int progress = 1;
  while(progress){
    progress = 0;
    for(Node* table_node = tables->first; table_node; table_node = table_node->next){
      Node* next_table_node = table_node->next;
      while(next_table_node){
        if(MergeTables(table_node->info, next_table_node->info)){
          Node* old_table_node = next_table_node;
          next_table_node = next_table_node->next;
          VectorDrop(old_table_node->info);
          NodeDrop(LinkedListRemoveFrom(tables, old_table_node));

          progress = 1;
        }
        else break;
      }
    }
  }

  // GENERATE IR
  int old_start   = 0;
  int table_start = 0;
  int table_end   = 0;

  static int table_counter = 0;

  for(Node* table_node = tables->first; table_node; table_node = table_node->next){
    Vector* table = table_node->info;
    TreeNode* first_entry = VectorGet(table, 0);
    TreeNode* last_entry  = VectorGet(table, table->size - 1);
    table_start = first_entry->expr_node->address;
    table_end   = last_entry->expr_node->address;

    if(table_node->prev) {
      InsertNewLabel(++label_counter); // generate label for every table except the first one
    }

    ++table_counter;
    InsertInstrSwitchTab(IR_TABENT, table_counter);
    for(int i = 0; i < table->size; i++){
      TreeNode* current_entry = VectorGet(table, i);
      
      // fill unspecified entries with default or next statement
      if(i > 0) {
        TreeNode* prev_entry = VectorGet(table, i - 1);
        for(int i = prev_entry->expr_node->address + 1; i < current_entry->expr_node->address; i++){
          AllocateNodeLabel(tree_node->logic_node->if_true);
          InsertInstrLabel(IR_TABLIN, tree_node->logic_node->if_true->label);
        }
      }

      // fill specified entry with value
      AllocateNodeLabel(current_entry->logic_node->if_true);
      InsertInstrLabel(IR_TABLIN, current_entry->logic_node->if_true->label);
    }
    InsertInstrSwitchTab(IR_TABEXT, table_counter);

    if(table_start > old_start) InsertInstrArithm(IR_SUB, IR_ADDR_DIRECT, table_start - old_start);
    if(table_start < old_start) InsertInstrArithm(IR_ADD, IR_ADDR_DIRECT, old_start - table_start);
    InsertInstrArithm(IR_CMP, IR_ADDR_DIRECT, table_end - table_start + 1);
    if(table_node->next) {
      InsertInstrLabel(IR_JAE, label_counter + 1); // jump to next table
    }
    else {
      AllocateNodeLabel(tree_node->logic_node->if_true);
      InsertInstrLabel(IR_JAE, tree_node->logic_node->if_true->label); // jump to next statement (default or break)
    }
    
    InsertInstrStackPop(IR_REVIV);
    InsertInstrArithm(IR_LSL, IR_ADDR_DIRECT, 2);
    InsertInstrSwitchTab(IR_ADD, table_counter);
    InsertInstr(IR_JMP, IR_ADDR_INDIRECT, IR_OP_STACK_POP, 0, 0, 0, 0);
    InsertInstrStackPop(IR_REVIV);

    old_start = table_start;
  }

  // // DUMP
  // for(Node* table_node = tables->first; table_node; table_node = table_node->next){
  //   Vector* table = table_node->info;
  //   printf("TABLE: ");
  //   for(int i = 0; i < table->size; i++){
  //     TreeNode* tree_node = VectorGet(table, i);
  //     printf("%d ", tree_node->expr_node->address);
  //   }
  //   printf("\n");
  // }

  for(Node* table_node = tables->first; table_node; table_node = table_node->next){
    VectorDrop(table_node->info);
  }
  LinkedListDrop(tables);

  switch_index++;
}

static void GenerateSwitchStatement(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();

  GenerateSwitchTables(tree_node);

  InsertInstrStackPop(IR_POP);

  GenerateIntermediate(tree_node->children[1]);
  // GenerateIntermediate(tree_node->children[2]); // generate void expr
}

static void GenerateStatementList(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
  }
}

static void GenerateStatement(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
    GenerateSequencePoint();
  }
}

static void GenerateReturnExpr(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);
  InsertInstrStackPop(IR_SETRET);
  GenerateSequencePoint();
}

static void GenerateReturnStructExpr(TreeNode* tree_node){
  InsertInstrObj(IR_PUSHL, IR_ADDR_DIRECT, tree_node->children[1]->expr_node->obj_ref, 0);
  InsertInstrStackPop(IR_DERFL);

  GenerateIntermediate(tree_node->children[0]);

  StructCopyToMem(tree_node->children[0]);

  GenerateSequencePoint();
}

static void GenerateInlineAssembly(TreeNode* tree_node){
  InsertInstrString(IR_ASM, IR_ADDR_INDIRECT, tree_node->children[0]->expr_node->string_ref, 0);
}

static void GenerateFunctionPrologue(TreeNode* tree_node){
  InsertInstrArithm(IR_ENTER, IR_ADDR_DIRECT, current_function->address);
}

static void GenerateFunctionEpilogue(TreeNode* tree_node){
  InsertInstrArithm(IR_EXIT, IR_ADDR_DIRECT, current_function->address);
}

static void GenerateFunctionBody(TreeNode* tree_node){
  current_function = tree_node->expr_node->obj_ref;

  InsertNewFunct(current_function);
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
  }
}

static void GenerateTranslationUnit(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
  }
}

void GenerateIntermediate(TreeNode* tree_node){
  GenerateNodeLabel(tree_node);

  switch(tree_node->production){
  case VOID_EXPR: break;

  case ADDRESS_PRIMARY:
  case CONSTANT_PRIMARY:
  case STRING_PRIMARY:
    GeneratePrimary(tree_node);
    break;
    
  case DEREF_EXPR:
    if(StructIsScalar(tree_node->expr_node->type)) GenerateDeref(tree_node);
    else GenerateDerefStruct(tree_node);
    break;
  case FIELD_REF_EXPR:
    // if(StructIsScalar(tree_node->expr_node->type)) GenerateDeref(tree_node, tree_node->expr_node->address);
    // else GenerateDerefStruct(tree_node, tree_node->expr_node->address);
    if(StructIsScalar(tree_node->expr_node->type)) GenerateFieldRef(tree_node);
    else GenerateFieldRefStruct(tree_node);
    break;

  case UNARY_PLUS_EXPR:
  case UNARY_MINUS_EXPR:
  case BIT_NOT_EXPR:

  case POST_INC_EXPR:
  case POST_DEC_EXPR:
  case PRE_INC_EXPR:
  case PRE_DEC_EXPR:

  case CAST_EXPR:
    GenerateUnary(tree_node);
    break;

  case MUL_EXPR:
  case DIV_EXPR:
  case MOD_EXPR:

  case ADD_EXPR:
  case SUB_EXPR:

  case BIT_LEFT_EXPR:
  case BIT_RIGHT_EXPR:

  case BIT_AND_EXPR:
  case BIT_XOR_EXPR:
  case BIT_OR_EXPR:
    GenerateBinary(tree_node);
    break;

  case FUNCTION_CALL_EXPR:{
    // function type decides - because of the calling conventions
    if(StructIsScalar(tree_node->expr_node->type) 
        || StructIsVoid(tree_node->expr_node->type)) 
      GenerateFunctionCall(tree_node);
    else GenerateFunctionCallStruct(tree_node);
  } break;

  case RELA_GT_EXPR:
  case RELA_LT_EXPR:
  case RELA_GE_EXPR:
  case RELA_LE_EXPR:
  case RELA_EQ_EXPR:
  case RELA_NQ_EXPR:
    GenerateRelation(tree_node);
    break;

  case LOG_NOT_EXPR:
    GenerateLogicUnary(tree_node);
    break;
  case LOG_AND_EXPR:
  case LOG_OR_EXPR:
    GenerateLogicBinary(tree_node);
    break;

  case COND_EXPR:
    if(StructIsScalar(tree_node->expr_node->type)) GenerateCond(tree_node);
    else GenerateCondStruct(tree_node);
    break;

  case ASSIGN_EXPR:
    if(StructIsScalar(tree_node->expr_node->type)) GenerateAssign(tree_node);
    else GenerateAssignStruct(tree_node);
    break;

  case MUL_ASSIGN_EXPR:
  case DIV_ASSIGN_EXPR:
  case MOD_ASSIGN_EXPR:
  case ADD_ASSIGN_EXPR:
  case SUB_ASSIGN_EXPR:
  case BIT_LEFT_ASSIGN_EXPR:
  case BIT_RIGHT_ASSIGN_EXPR:
  case BIT_AND_ASSIGN_EXPR: 
  case BIT_XOR_ASSIGN_EXPR: 
  case BIT_OR_ASSIGN_EXPR:
    GenerateArithmAssign(tree_node);
    break;

  case COMMA_EXPR:
    if(StructIsScalar(tree_node->expr_node->type)) GenerateComma(tree_node);
    else GenerateCommaStruct(tree_node);
    break;

  case LABEL_STMT:
  case CASE_STMT:
  case DEFAULT_STMT:
    break;

  case INITIALIZATION:
  case FOR_DECL:
  case COMPOUND_STMT:
    GenerateStatementList(tree_node);
    break;

  case EXPRESSION_STMT:
  case EMPTY_STMT:

  case IF_STMT:
  case IF_ELSE_STMT:
    GenerateStatement(tree_node);
    break;
  case SWITCH_STMT:
    GenerateSwitchStatement(tree_node);
    break;

  case WHILE_STMT:
  case DO_WHILE_STMT:
  case FOR_STMT:

  case GOTO_STMT:
  case CONTINUE_STMT:
  case BREAK_STMT:
  case RETURN_STMT:
    GenerateStatement(tree_node);
    break;

  case RETURN_EXPR_STMT:
    if(StructIsScalar(tree_node->children[0]->expr_node->type)) GenerateReturnExpr(tree_node);
    else GenerateReturnStructExpr(tree_node);
    break;

  case INLINE_ASM_STMT:
    GenerateInlineAssembly(tree_node);
    break;

  case FUNC_PROLOGUE:
    GenerateFunctionPrologue(tree_node);
    break;

  case FUNC_EPILOGUE:
    GenerateFunctionEpilogue(tree_node);
    break;

  case FUNCTION_BODY:
    GenerateFunctionBody(tree_node);
    break;

  case TRANSLATION_UNIT:
    GenerateTranslationUnit(tree_node);
    break;
  }

  GenerateJump(tree_node);
}

void GenerateSequencePoint(void){

}

#define PRINT_NOPS 0

void PrintIntermediate(void){
  extern FILE* irout;

  for(int i = 0; i < ir_sequence->size; i++){
    IrInstr* ir_instr = VectorGet(ir_sequence, i);
    if(PRINT_NOPS || ir_instr->opcode != IR_NOP) {
      IrInstrDump(ir_instr);
      fprintf(irout, "\n");
    }

    // if(i < ir_sequence->size - 1 
    //     && ((IrInstr*)VectorGet(ir_sequence, i + 1))->opcode == IR_FUNCT)
    //   fprintf(irout, "\n");
  
    if(((IrInstr*)VectorGet(ir_sequence, i))->opcode == IR_EXIT) fprintf(irout, "\n");
  }
}