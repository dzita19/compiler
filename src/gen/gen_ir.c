#include "gen_ir.h"

#include "util/array.h"

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

void GeneratePrimary(TreeNode* tree_node){
  if(tree_node->production == ADDRESS_PRIMARY){
    InsertInstrObj(IR_PUSHL, IR_ADDR_DIRECT, tree_node->expr_node->obj_ref, tree_node->expr_node->address);
  }
  else if(tree_node->production == CONSTANT_PRIMARY){
    InsertInstrArithm(IR_PUSHL, IR_ADDR_DIRECT, tree_node->expr_node->address);
  }
  else if(tree_node->production == STRING_PRIMARY){
    InsertInstrString(IR_PUSHL, IR_ADDR_DIRECT, tree_node->expr_node->string_ref, tree_node->expr_node->address);
  }

  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT) InsertInstrStackPop(IR_POP);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateDeref(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);

  int size = 0;
  if     (tree_node->expr_node->type->size == 1) size = IR_DERFB - IR_DERFB;
  else if(tree_node->expr_node->type->size == 2) size = IR_DERFW - IR_DERFB;
  else if(tree_node->expr_node->type->size == 4) size = IR_DERFL - IR_DERFB;

  InsertInstrStackPop(IR_DERFB + size);

  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT) InsertInstrStackPop(IR_POP);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORB + size, offset);
  }
}

void GenerateDerefStruct(TreeNode* tree_node){

}

void GenerateUnary(TreeNode* tree_node){

  switch(tree_node->production){
  case UNARY_PLUS_EXPR:  {
    GenerateIntermediate(tree_node->children[0]);
  } break;

  case UNARY_MINUS_EXPR: {
    GenerateIntermediate(tree_node->children[0]);
    InsertInstrStackPop(IR_NEG);
  } break;

  case BIT_NOT_EXPR:     {
    GenerateIntermediate(tree_node->children[0]);
    InsertInstrStackPop(IR_NOT);
  } break;

  case POST_INC_EXPR:    
  case POST_DEC_EXPR:    
  case PRE_INC_EXPR:     
  case PRE_DEC_EXPR:     {
    GenerateIntermediate(tree_node->children[0]->children[0]); // +1

    int size = 0;
    if     (tree_node->expr_node->type->size == 1) size = IR_DERFB - IR_DERFB;
    else if(tree_node->expr_node->type->size == 2) size = IR_DERFW - IR_DERFB;
    else if(tree_node->expr_node->type->size == 4) size = IR_DERFL - IR_DERFB;

    InsertInstrStackPop(IR_DUP); // +1
    InsertInstrStackPop(IR_DERFB + size); // +0

    // cast into int32; +0
    Struct* from = tree_node->children[0]->expr_node->type;
    if(StructIsPointer(from)) from = predefined_types_struct + UINT32_T;

    int from_rank = (from - predefined_types_struct -  INT8_T) >> 1;
    int from_sign = (from - predefined_types_struct - UINT8_T)  & 1;

    if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
    else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
    else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
    else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
    
    GenerateIntermediate(tree_node->children[1]); // +1
    InsertInstrStackPop(IR_ADD); // -1
    InsertInstrStackRead(IR_STORB + size, IR_ADDR_INDIRECT, 1); // -1
    InsertInstrStackPop(IR_DERFB + size); // +0

    // cast into int32; +0
    if     (from_rank == 0 && from_sign == 0) InsertInstrStackPop(IR_ZXBL);
    else if(from_rank == 0 && from_sign == 1) InsertInstrStackPop(IR_SXBL);
    else if(from_rank == 1 && from_sign == 0) InsertInstrStackPop(IR_ZXWL);
    else if(from_rank == 1 && from_sign == 1) InsertInstrStackPop(IR_SXWL);
  } break;

  case CAST_EXPR:        {
    GenerateIntermediate(tree_node->children[0]);

    Struct* from = tree_node->expr_node->type;
    Struct* to   = tree_node->children[0]->expr_node->type;

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

  } break;
  default: break;
  }

  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT) InsertInstrStackPop(IR_POP);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateBinary(TreeNode* tree_node){
  int instr = IR_NOP;

  GenerateIntermediate(tree_node->children[0]);
  GenerateIntermediate(tree_node->children[1]);

  switch(tree_node->production){
  case MUL_EXPR: instr = IR_MUL; break;
  case DIV_EXPR: instr = IR_DIV; break;
  case MOD_EXPR: instr = IR_MOD; break;

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
  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT) InsertInstrStackPop(IR_POP);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateFunctionCall(TreeNode* tree_node){
  CallFrame* call_frame = CallFrameCreateEmpty();
  int arg_frame_size = 0;

  Array arg_allocs = (Array){ 0, 0 }; // Array(ArgAlloc*)
  ArrayAlloc(&arg_allocs, sizeof(ArgAlloc*), tree_node->num_of_children);

  // find arg frame size
  for(int i = 1; i < tree_node->num_of_children; i++){
    TreeNode* child = tree_node->children[i];
    ArgAlloc* current_arg_alloc = GetArgAllocation(call_frame, child->expr_node->type);
    *(ArgAlloc**)ArrayGet(&arg_allocs, i) = current_arg_alloc;

    if(current_arg_alloc->mode == ARG_TO_STACK)
      arg_frame_size = current_arg_alloc->addr + child->expr_node->type->size;
  }

  InsertInstrArithm(IR_ALIGN, IR_ADDR_DIRECT, arg_frame_size);

  for(int i = 1; i < tree_node->num_of_children; i++){
    TreeNode* child = tree_node->children[i];
    ArgAlloc* current_arg_alloc = *(ArgAlloc**)ArrayGet(&arg_allocs, i);

    if(current_arg_alloc->mode == ARG_TO_STACK){
      child->mem_alloc         = MemAllocCreateEmpty();
      child->mem_alloc->kind   = MEM_ALLOC_TO_ARGS;
      child->mem_alloc->offset = current_arg_alloc->addr;
    }

    GenerateIntermediate(child);
    ArgAllocDrop(current_arg_alloc);
  }

  GenerateSequencePoint();

  GenerateIntermediate(tree_node->children[0]);
  InsertInstrStackPop(IR_CALL);

  if(production_kind[tree_node->parent->production] == PRODUCTION_EXPR) InsertInstrNoOp(IR_ABIRET);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }

  ArrayFree(&arg_allocs);
  CallFrameDrop(call_frame);
}

void GenerateFunctionCallStruct(TreeNode* tree_node){

}

void GenerateRelation(TreeNode* tree_node){
  int instr_true  = IR_NOP;
  int instr_false = IR_NOP;
  if(tree_node->parent->production == COND_EXPR) InsertInstrNoOp(IR_LOGENT);

  GenerateIntermediate(tree_node->children[0]);
  GenerateIntermediate(tree_node->children[1]);

  switch(tree_node->production){
  case RELA_GT_EXPR: instr_true = IR_JGT; instr_false = IR_JLE; break;
  case RELA_LT_EXPR: instr_true = IR_JLT; instr_false = IR_JGE; break;
  case RELA_GE_EXPR: instr_true = IR_JGE; instr_false = IR_JLT; break;
  case RELA_LE_EXPR: instr_true = IR_JLE; instr_false = IR_JGT; break;
  case RELA_EQ_EXPR: instr_true = IR_JEQ; instr_false = IR_JNQ; break;
  case RELA_NQ_EXPR: instr_true = IR_JNQ; instr_false = IR_JEQ; break;
  default: break;
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

void GenerateLogicUnary(TreeNode* tree_node){
  if(tree_node->parent->production == COND_EXPR) InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
}

void GenerateLogicBinary(TreeNode* tree_node){
  if(tree_node->parent->production == COND_EXPR) InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();
  GenerateIntermediate(tree_node->children[1]);
}

void GenerateCond(TreeNode* tree_node){

  // InsertInstrNoOp(IR_LOGENT);
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();

  GenerateIntermediate(tree_node->children[1]);
  GenerateIntermediate(tree_node->children[2]);

  GenerateIntermediate(tree_node->children[3]);

  InsertInstrNoOp(IR_LOGEXT);
  InsertInstrNoOp(IR_COND);

  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT) InsertInstrStackPop(IR_POP);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateCondStruct(TreeNode* tree_node){

}

void GenerateAssign(TreeNode* tree_node){
  int size = 0;
  if     (tree_node->expr_node->type->size == 1) size = IR_STORB - IR_STORB;
  else if(tree_node->expr_node->type->size == 2) size = IR_STORW - IR_STORB;
  else if(tree_node->expr_node->type->size == 4) size = IR_STORL - IR_STORB;

  GenerateIntermediate(tree_node->children[0]->children[0]);
  if(production_kind[tree_node->parent->production] == PRODUCTION_EXPR) InsertInstrStackPop(IR_DUP);
  GenerateIntermediate(tree_node->children[1]);

  InsertInstrStackPop(IR_STORB + size);
  if(production_kind[tree_node->parent->production] == PRODUCTION_EXPR) InsertInstrStackPop(IR_DERFB + size);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateAssignStruct(TreeNode* tree_node){
  
}

void GenerateArithmAssign(TreeNode* tree_node){
  int size = 0;
  if     (tree_node->expr_node->type->size == 1) size = IR_STORB - IR_STORB;
  else if(tree_node->expr_node->type->size == 2) size = IR_STORW - IR_STORB;
  else if(tree_node->expr_node->type->size == 4) size = IR_STORL - IR_STORB;

  GenerateIntermediate(tree_node->children[0]->children[0]);
  if(production_kind[tree_node->parent->production] == PRODUCTION_EXPR) InsertInstrStackPop(IR_DUP);
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
  case MUL_ASSIGN_EXPR: instr = IR_MUL; break;
  case DIV_ASSIGN_EXPR: instr = IR_DIV; break;
  case MOD_ASSIGN_EXPR: instr = IR_MOD; break;
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
  if(production_kind[tree_node->parent->production] == PRODUCTION_EXPR) InsertInstrStackPop(IR_DERFB + size);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateComma(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children - 1; i++){
    GenerateIntermediate(tree_node->children[i]);
    if(StructIsScalar(tree_node->children[i]->expr_node->type)) InsertInstrStackPop(IR_POP);
    GenerateSequencePoint();
  }
  
  TreeNode* last_child = tree_node->children[tree_node->num_of_children - 1];
  if(tree_node->mem_alloc)
    last_child->mem_alloc = MemAllocCopy(tree_node->mem_alloc);
  
  GenerateIntermediate(last_child);

  if(production_kind[tree_node->parent->production] == PRODUCTION_STMT) InsertInstrStackPop(IR_POP);
  if(tree_node->parent->production == COND_EXPR) InsertInstrStackPop(IR_POP);
  if(tree_node->mem_alloc && tree_node->mem_alloc->kind == MEM_ALLOC_TO_ARGS){
    int offset = tree_node->mem_alloc->offset;
    InsertInstrArg(IR_STORL, offset);
  }
}

void GenerateStatementList(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
  }
}

void GenerateStatement(TreeNode* tree_node){
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
    GenerateSequencePoint();
  }
}

void GenerateReturnExpr(TreeNode* tree_node){
  GenerateIntermediate(tree_node->children[0]);
  GenerateSequencePoint();
}

void GenerateReturnStructExpr(TreeNode* tree_node){

}

void GenerateFunctionPrologue(TreeNode* tree_node){
  InsertInstrArithm(IR_ENTER, IR_ADDR_DIRECT, current_function->address);
}

void GenerateFunctionEpilogue(TreeNode* tree_node){
  InsertInstrArithm(IR_EXIT, IR_ADDR_DIRECT, current_function->address);
}

void GenerateFunctionBody(TreeNode* tree_node){
  current_function = tree_node->expr_node->obj_ref;

  InsertNewFunct(current_function);
  for(int i = 0; i < tree_node->num_of_children; i++){
    GenerateIntermediate(tree_node->children[i]);
  }
}

void GenerateTranslationUnit(TreeNode* tree_node){
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

  case FUNCTION_CALL_EXPR:
    if(StructIsScalar(tree_node->expr_node->type)) GenerateFunctionCall(tree_node);
    else GenerateFunctionCallStruct(tree_node);
    break;

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
    GenerateComma(tree_node);
    break;

  case LABEL_STMT:
  case CASE_STMT:
  case DEFAULT_STMT:
    break;

  case INITIALIZATION:
  case COMPOUND_STMT:
    GenerateStatementList(tree_node);
    break;

  case EXPRESSION_STMT:
  case EMPTY_STMT:
  case FOR_DECL:

  case IF_STMT:
  case IF_ELSE_STMT:
  case SWITCH_STMT:

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
    if(StructIsScalar(tree_node->expr_node->type)) GenerateReturnExpr(tree_node);
    else GenerateReturnStructExpr(tree_node);
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

#define PRINT_NOPS 1

void PrintIntermediate(void){
  for(int i = 0; i < ir_sequence->size; i++){
    IrInstr* ir_instr = VectorGet(ir_sequence, i);
    if(PRINT_NOPS || ir_instr->opcode != IR_NOP) IrInstrDump(ir_instr);

    extern FILE* irout;
    fprintf(irout, "\n");

    if(i < ir_sequence->size - 1 
        && ((IrInstr*)VectorGet(ir_sequence, i + 1))->opcode == IR_FUNCT)
      fprintf(irout, "\n");
  }
}