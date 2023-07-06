#include <stdio.h>

#include "stmt/stmt.h"
#include "decl/declarations.h"
#include "symtab/symtab.h"
#include "util/memory_safety.h"

extern FILE* ccout;
extern FILE* yyin;
extern int yyparse();

extern Tree* tree;
extern Symtab* symtab;

int main(int argc, char** argv){
  declarations_init();
  stmt_init();

  if(argc != 3) return 1;

	yyin = fopen(argv[1], "r");
  ccout = fopen(argv[2], "w");

  if(yyin == 0) {
    printf("Input file not found.\n");
    return 1;
  }

	if(yyparse() == 0){
    printf("Parsing finished successfully.\n");
    if(semantic_errors == 0) GenerateOutputFile();
  }
  else {
    printf("Parsing failed.\n");
  }

  fclose(yyin);
  fclose(ccout);

  printf("\n");
  SymtabDump(symtab);

  printf("\n");
  StaticObjListDump();

  printf("\n");
  StringTabDump();

  printf("\n");
  TreeDump(tree);

  declarations_free();
  stmt_free();

  printf("\n");
  memory_safety_report();

  printf("\n");
  if(semantic_errors == 0){
    printf("Semantic analysis successful.\n");
  }
  else{
    printf("Program contains semantic errors.\n");
  }

	return 0;
}