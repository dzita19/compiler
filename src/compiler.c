#include <stdio.h>

#include "ast/tree.h"
#include "ast/production.h"

extern FILE* yyin;
extern int yyparse();

extern TreeNode* root;

int main(){
  initialize_productions_table();

	yyin = fopen("test/testfile", "r");
	if(yyparse() == 0){
    printf("Parsing finished successfully\n");
  }
  else {
    printf("Parsing failed\n");
  }

  printf("\n");
  TreeNodePrint(root);

	return 0;
}