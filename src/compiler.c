#include <stdio.h>

#include "stmt/stmt.h"
#include "decl/declarations.h"
#include "symtab/symtab.h"
#include "util/memory_safety.h"

extern FILE* yyin;
extern int yyparse();

extern Tree* tree;

extern Symtab* symtab;

int main(){
  declarations_init();
  stmt_init();

	yyin = fopen("test/testfile", "r");
	if(yyparse() == 0){
    printf("Parsing finished successfully\n");
  }
  else {
    printf("Parsing failed\n");
  }
  printf("\n");
  SymtabDump(symtab);

  printf("\n");
  TreeDump(tree);

  declarations_free();
  stmt_free();

  printf("\n");
  memory_safety_report();

	return 0;
}