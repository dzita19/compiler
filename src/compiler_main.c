#include <stdio.h>

#include "stmt/stmt.h"
#include "decl/declarations.h"
#include "symtab/symtab.h"
#include "util/memory_safety.h"
#include <string.h>

extern FILE* ccout;
extern FILE* yyin;
extern int yyparse();
extern const char* input_path_name;

extern Tree* tree;
extern Symtab* symtab;

#define CMD_PARSE_ERROR (-1)
#define CMD_PARSE_INPUT   0
#define CMD_PARSE_OUTPUT  1

static const char* input_path    = NULL;
static const char* output_path   = NULL;
static int         parse_state   = CMD_PARSE_INPUT;
static int         debug_enabled = 0;
static int         omit_output   = 0;

static void ParseCmdArgs(int argc, char** argv){
  for(int i = 1; i < argc; i++){
    switch(parse_state){
    case CMD_PARSE_ERROR: break;

    case CMD_PARSE_INPUT:{
      if(strcmp(argv[i], "-o") == 0){
        parse_state = CMD_PARSE_OUTPUT;
      }
      else if(strcmp(argv[i], "-dbg") == 0){
        debug_enabled = 1;
      }
      else if(strcmp(argv[i], "-omit-output") == 0) {
        omit_output = 1;
      }
      else{
        if(input_path == 0) input_path = argv[i];
        else parse_state = CMD_PARSE_ERROR;
      }
    } break;

    case CMD_PARSE_OUTPUT:{
      if     (strcmp(argv[i], "-o")   == 0) parse_state = CMD_PARSE_ERROR;
      else if(strcmp(argv[i], "-dbg") == 0) parse_state = CMD_PARSE_ERROR;
      else if(strcmp(argv[i], "-omit-output") == 0) parse_state = CMD_PARSE_ERROR;
      else{
        if(output_path == 0) {
          output_path = argv[i];
          parse_state = CMD_PARSE_INPUT;
        }
        else parse_state = CMD_PARSE_ERROR;
      }
    } break;
    }
  }
}

int main(int argc, char** argv){

  ParseCmdArgs(argc, argv);

  if(input_path == NULL || output_path == NULL){
    parse_state = CMD_PARSE_ERROR;
  }
  
  if(parse_state != CMD_PARSE_INPUT) {
    printf("Invalid arguments.\n");
    printf("Recommended input: -o <output_file> <input_file> [*flags*]\n"
           "\tFlags:          -dbg (debug output)\n");
    return 1;
  }
  
  input_path_name = input_path;
	yyin = fopen(input_path, "r");

  if(yyin == NULL) {
    printf("Input file %s not found.\n", input_path);
    return 1;
  }

  declarations_init();
  stmt_init();

	if(yyparse() == 0){
    if(debug_enabled) printf("Parsing finished successfully.\n");
    if(semantic_errors == 0) {
      ccout = fopen(output_path, "w");
      if(ccout == NULL){
        printf("Output file cannot be generated.\n");
        return 1;
      }
      if(!omit_output) GenerateOutputFile();
    }
  }
  else {
    if(debug_enabled) printf("Parsing failed.\n");
    semantic_errors = 1;
  }

  fclose(yyin);
  if(ccout) fclose(ccout);

  if(debug_enabled){
    printf("\n");
    SymtabDump(symtab);

    printf("\n");
    StaticObjListDump();

    printf("\n");
    LabelNameListDump();

    printf("\n");
    GlobalNameListDump();

    printf("\n");
    ExternNameListDump();

    printf("\n");
    StringTabDump();

    printf("\n");
    TreeDump(tree);
  }

  declarations_free();
  stmt_free();

  if(debug_enabled){
    printf("\n");
    memory_safety_report();
    printf("\n");

    if(semantic_errors == 0){
      printf("Semantic analysis successful.\n");
    }
    else{
      printf("Program contains semantic errors.\n");
    }
  }

	return semantic_errors;
}