#include "production.h"
#include <stdlib.h>

#define REGISTER_PRODUCTION(production_type, production_name, production_callback) \
  production_names[(production_type)] = production_name; \
  production_callbacks[(production_type)] = production_callback

char* production_names[PROD_TOTAL_COUNT] = { };

void (**production_callbacks)(void* syntax_node) = 0;

static void production_statement_list_empty(void* syntax_node){
  
}

static void production_statement_list_recursive(void* syntax_node){
  
}

static void production_statement_assign(void* syntax_node){
  
}

static void production_statement_declaration(void* syntax_node){
  
}

static void production_expression_convergent(void* syntax_node){
  
}

static void production_expression_addition(void* syntax_node){
  
}

static void production_expression_subtraction(void* syntax_node){
  
}

static void production_term_convergent(void* syntax_node){
  
}

static void production_term_multiplication(void* syntax_node){
  
}

static void production_term_division(void* syntax_node){
  
}

static void production_fact_enclosed(void* syntax_node){
  
}

static void production_fact_identifier(void* syntax_node){
  
}

static void production_fact_constant(void* syntax_node){
  
}

void initialize_productions_table(void){
  production_callbacks = malloc(PROD_TOTAL_COUNT * sizeof(char*));

  REGISTER_PRODUCTION(TERM_IDENTIFIER, "TERMINAL identifier", 0);
  REGISTER_PRODUCTION(TERM_CONSTANT, "TERMINAL constant", 0);

  REGISTER_PRODUCTION(PROD_STMTLIST_EMPTY, "Statement list empty", production_statement_list_empty);
  REGISTER_PRODUCTION(PROD_STMTLIST_REC, "Statement list recursive", production_statement_list_recursive);
  REGISTER_PRODUCTION(PROD_STMT_ASSIGN, "Statement assign", production_statement_assign);
  REGISTER_PRODUCTION(PROD_STMT_DECL, "Statement declaration", production_statement_declaration);
  REGISTER_PRODUCTION(PROD_EXPR_CONV, "Expression convergent", production_expression_convergent);
  REGISTER_PRODUCTION(PROD_EXPR_ADD, "Expression addition", production_expression_addition);
  REGISTER_PRODUCTION(PROD_EXPR_SUB, "Expression subtraction", production_expression_subtraction);
  REGISTER_PRODUCTION(PROD_TERM_CONV, "Term convergent", production_term_convergent);
  REGISTER_PRODUCTION(PROD_TERM_MUL, "Term multiplication", production_term_multiplication);
  REGISTER_PRODUCTION(PROD_TERM_DIV, "Term division", production_term_division);
  REGISTER_PRODUCTION(PROD_FACT_ENCLOSED, "Factor enclosed", production_fact_enclosed);
  REGISTER_PRODUCTION(PROD_FACT_ID, "Factor identifier", production_fact_identifier);
  REGISTER_PRODUCTION(PROD_FACT_CONST, "Factor constant", production_fact_constant);
  
}