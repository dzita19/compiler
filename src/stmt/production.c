#include "production.h"
#include <stdlib.h>

#define REGISTER_PRODUCTION(production_type, production_name, production_callback) \
  production_names[(production_type)] = production_name; \
  production_callbacks[(production_type)] = production_callback

char* production_names[PROD_TOTAL_COUNT] = { };

void (**production_callbacks)(void* syntax_node) = 0;

void initialize_productions_table(void){
  production_callbacks = malloc(PROD_TOTAL_COUNT * sizeof(char*));

  REGISTER_PRODUCTION(TERM_IDENTIFIER, 0, 0);
  REGISTER_PRODUCTION(TERM_CONSTANT, 0, 0);
  REGISTER_PRODUCTION(TERM_STRING_LITERAL, 0, 0);

  REGISTER_PRODUCTION(PROD_PRIMARY_IDENTIFIER, "Primary identifier", 0);
  REGISTER_PRODUCTION(PROD_PRIMARY_CONSTANT, "Primary constant", 0);
  REGISTER_PRODUCTION(PROD_PRIMARY_STRING, "Primary string literal", 0);

  REGISTER_PRODUCTION(PROD_POSTFIX_ARRAYREF, "Postfix array referencing", 0);
  REGISTER_PRODUCTION(PROD_POSTFIX_INVOKE_VOID, "Postfix function invocation (no args)", 0);
  REGISTER_PRODUCTION(PROD_POSTFIX_INVOKE_ARGS, "Postfix function invocation (args)", 0);
  REGISTER_PRODUCTION(PROD_POSTFIX_FIELDREF, "Postfix field referencing", 0);
  REGISTER_PRODUCTION(PROD_POSTFIX_PTRFIELDREF, "Postfix pointer field referencing", 0);
  REGISTER_PRODUCTION(PROD_POSTFIX_INC, "Postfix increment", 0);
  REGISTER_PRODUCTION(PROD_POSTFIX_DEC, "Postfix decrement", 0);

  REGISTER_PRODUCTION(PROD_ARG_LIST_CONV, "Function argument (convergent)", 0);
  REGISTER_PRODUCTION(PROD_ARG_LIST_REC, "Function argument (recursive)", 0);

  REGISTER_PRODUCTION(PROD_PREFIX_INC, "Prefix increment", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_DEC, "Prefix decrement", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_ADDR, "Prefix address", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_DEREF, "Prefix dereferencing", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_PLUS, "Prefix plus", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_MINUS, "Prefix minus", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_BITW_NOT, "Bitwise expression: not", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_LOGIC_NOT, "Logic expression: not", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_SIZEOF_EXPR, "Prefix sizeof expression", 0);
  REGISTER_PRODUCTION(PROD_PREFIX_SIZEOF_TYPE, "Prefix sizeof type", 0);

  REGISTER_PRODUCTION(PROD_CAST, "Cast expression", 0);

  REGISTER_PRODUCTION(PROD_MUL, "Multiplication expression", 0);
  REGISTER_PRODUCTION(PROD_DIV, "Division expression", 0);
  REGISTER_PRODUCTION(PROD_MOD, "Modulo expression", 0);

  REGISTER_PRODUCTION(PROD_ADD, "Addition expression", 0);
  REGISTER_PRODUCTION(PROD_SUB, "Subtraction expression", 0);
  
  REGISTER_PRODUCTION(PROD_SHIFT_LEFT, "Shift left", 0);
  REGISTER_PRODUCTION(PROD_SHIFT_RIGHT, "Shift right", 0);

  REGISTER_PRODUCTION(PROD_RELA_LT, "Relation expression: less than", 0);
  REGISTER_PRODUCTION(PROD_RELA_GT, "Relation expression: greater than", 0);
  REGISTER_PRODUCTION(PROD_RELA_LE, "Relation expression: less equal", 0);
  REGISTER_PRODUCTION(PROD_RELA_GE, "Relation expression: less equal", 0);
  
  REGISTER_PRODUCTION(PROD_RELA_EQ, "Relation expression: equal", 0);
  REGISTER_PRODUCTION(PROD_RELA_NE, "Relation expression: not equal", 0);

  REGISTER_PRODUCTION(PROD_BITW_AND, "Bitwise expression: and", 0);

  REGISTER_PRODUCTION(PROD_BITW_XOR, "Bitwise expression: xor", 0);

  REGISTER_PRODUCTION(PROD_BITW_OR, "Bitwise expression: or", 0);

  REGISTER_PRODUCTION(PROD_LOGIC_AND, "Logic expression: and", 0);

  REGISTER_PRODUCTION(PROD_LOGIC_OR, "Logic expression: or", 0);

  REGISTER_PRODUCTION(PROD_COND_TERN, "Ternary condition expression", 0);

  REGISTER_PRODUCTION(PROD_ASSIGN_BASIC, "Assignment expression: basic", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_MUL, "Assignment expression: multiplication", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_DIV, "Assignment expression: division", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_MOD, "Assignment expression: modulo", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_ADD, "Assignment expression: addition", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_SUB, "Assignment expression: subtraction", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_LEFT, "Assignment expression: shift left", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_RIGHT, "Assignment expression: shift right", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_AND, "Assignment expression: bitwise and", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_XOR, "Assignment expression: bitwise xor", 0);
  REGISTER_PRODUCTION(PROD_ASSIGN_OR, "Assignment expression: bitwise or", 0);

  REGISTER_PRODUCTION(PROD_EXPR_SEPARATED, "Comma separated expressions", 0);

}