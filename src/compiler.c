#include <stdio.h>

#include "stmt/tree.h"
#include "stmt/production.h"
#include "decl/declarations.h"
#include "symtab/symtab.h"

extern FILE* yyin;
extern int yyparse();

extern TreeNode* root;

extern Symtab* symtab;

int main(){
  initialize_productions_table();
  declarations_init();

	yyin = fopen("test/testfile", "r");
	if(yyparse() == 0){
    printf("Parsing finished successfully\n");
  }
  else {
    printf("Parsing failed\n");
  }

  printf("\n");
  /*TreeNodePrint(root);*/
  
  SymtabDump(symtab);


	return 0;
}