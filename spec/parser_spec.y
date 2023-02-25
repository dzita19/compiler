%{
	#include <stdio.h>
	#include "ast/tree.h"
	#include "ast/production.h"

	extern int yylex (void);
	void yyerror(char* s);
%}

%union{
	int num;
	char* id;
}

%token <id> IDENTIFIER
%token <num> CONSTANT

%start statement_list
%%

statement_list : %empty { root = TreeNodeCreate(PROD_STMTLIST_EMPTY, 0); }
	| statement_list statement { root = TreeNodeCreate(PROD_STMTLIST_REC, 2); }

statement : IDENTIFIER '=' expression ';' { printf("%s ", $1); TreeNodeCreate(PROD_STMT_ASSIGN, 1); }
	| type IDENTIFIER ';' { TreeNodeCreate(PROD_STMT_DECL); }

expression : term { TreeNodeCreate(PROD_EXPR_CONV, 1); }
	| expression '+' term { TreeNodeCreate(PROD_EXPR_ADD, 2); }
	| expression '-' term { TreeNodeCreate(PROD_EXPR_SUB, 2); }

term : fact { TreeNodeCreate(PROD_TERM_CONV, 1); }
	| term '*' fact { TreeNodeCreate(PROD_TERM_MUL, 2); }
	| term '/' fact { TreeNodeCreate(PROD_TERM_DIV, 2); }

fact : '(' expression ')' { TreeNodeCreate(PROD_FACT_ENCLOSED, 1); }
	| IDENTIFIER { printf("%s ", $1); TreeNodeCreate(PROD_FACT_ID, 0); }
	| CONSTANT { printf("%d ", $1); TreeNodeCreate(PROD_FACT_CONST, 0); }

%%
#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}