#ifndef _PRODUCTION_H_
#define _PRODUCTION_H_

typedef enum {
  PROD_STMTLIST_EMPTY,
  PROD_STMTLIST_REC,
  PROD_STMT_ASSIGN,
  PROD_STMT_EXPR,
  PROD_EXPR_CONV,
  PROD_EXPR_ADD,
  PROD_EXPR_SUB,
  PROD_TERM_CONV,
  PROD_TERM_MUL,
  PROD_TERM_DIV,
  PROD_FACT_ENCLOSED,
  PROD_FACT_ID,
  PROD_FACT_CONST,

  PROD_TOTAL_COUNT
} Production;

extern void (**production_callback)(int production_type);
extern char* production_names[];
extern void initialize_productions_table(void);

#endif