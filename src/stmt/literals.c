#include "literals.h"

#include <stdlib.h>
#include <string.h>

Queue numlit_queue = { 0, 0 };
Queue strlit_queue = { 0, 0 };

NumLit* NumLitCreateEmpty(){
  NumLit* numlit = malloc(sizeof(NumLit));
  numlit->type = 0;
  numlit->value = 0;

  numlit_alloc++;

  return numlit;
}

void NumLitDrop(NumLit* numlit){
  free(numlit);

  numlit_free++;
}

void hex_val(const char* str){
  int val = 0;
  str += 2;
  while(*str){
    if     (*str >= '0' && *str <= '9') val = 16 * val + (*str - '0');
    else if(*str >= 'a' && *str <= 'f') val = 16 * val + (*str - 'a') + 10;
    else if(*str >= 'A' && *str <= 'F') val = 16 * val + (*str - 'A') + 10;
    else break;
    str++;
  }
  char flags = 0; // u - 0, l - 1
  while(*str){
    if     (*str == 'u' || *str == 'U') flags |= 1 << 0;
    else if(*str == 'l' || *str == 'L') flags |= 1 << 1;
    str++;
  }

  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = val;
  numlit->type = INT32_T;

  if(flags & (1 << 0)) numlit->type += 1;
  if(flags & (1 << 1)) numlit->type += 2;
  if((flags & (1 << 1)) == 0) val = (int)val;

  QueueInsert(&numlit_queue, numlit);
}

void oct_val(const char* str){
  int val = 0;
  str += 1;
  while(*str){
    if (*str >= '0' && *str <= '7') val = 8 * val + (*str - '0');
    else break;
    str++;
  }
  char flags = 0; // u - 0, l - 1
  while(*str){
    if     (*str == 'u' || *str == 'U') flags |= 1 << 0;
    else if(*str == 'l' || *str == 'L') flags |= 1 << 1;
    str++;
  }

  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = val;
  numlit->type = INT32_T;

  if(flags & (1 << 0)) numlit->type += 1;
  if(flags & (1 << 1)) numlit->type += 2;
  if((flags & (1 << 1)) == 0) val = (int)val;

  QueueInsert(&numlit_queue, numlit);
}

void dec_val(const char* str){
  int val = 0;
  while(*str){
    if (*str >= '0' && *str <= '9') val = 10 * val + (*str - '0');
    else break;
    str++;
  }
  char flags = 0; // u - 0, l - 1
  while(*str){
    if     (*str == 'u' || *str == 'U') flags |= 1 << 0;
    else if(*str == 'l' || *str == 'L') flags |= 1 << 1;
    str++;
  }

  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = val;
  numlit->type = INT32_T;

  if(flags & (1 << 0)) numlit->type += 1;
  if(flags & (1 << 1)) numlit->type += 2;
  if((flags & (1 << 1)) == 0) val = (int)val;

  QueueInsert(&numlit_queue, numlit);
}

void simple_char_lit(const char* str){
  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = str[0];
  numlit->type = INT8_T;

  QueueInsert(&numlit_queue, numlit);
}

// \\['"?\\abfnrtv]

void simple_escape_char_lit(const char* str){
  char val;

  switch(str[1]){
  case '\'': val =  '\''; break;
  case '\"': val =  '\"'; break;
  case '\?': val =  '\?'; break;
  case '\\': val =  '\\'; break;
  case 'a' : val =  '\a'; break;
  case 'b' : val =  '\b'; break;
  case 'f' : val =  '\f'; break;
  case 'n' : val =  '\n'; break;
  case 'r' : val =  '\r'; break;
  case 't' : val =  '\t'; break;
  case 'v' : val =  '\v'; break;
  default  : val =  0;
  }

  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = val;
  numlit->type = INT8_T;

  QueueInsert(&numlit_queue, numlit);
}

void oct_char_lit(const char* str){
  char c = 0;
  int cntr = 0;
  str += 1;
  while(*str){
    if(*str >= '0' && *str <= '7' && cntr++ <= 3) c = c * 8 + (*str - '0');
    else break;

    str++;
  }

  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = c;
  numlit->type = INT8_T;

  QueueInsert(&numlit_queue, numlit);
}

void hex_char_lit(const char* str){
  char c = 0;
  str += 2;
  while(*str){
    if     (*str >= '0' && *str <= '9') c = 16 * c + (*str - '0');
    else if(*str >= 'a' && *str <= 'f') c = 16 * c + (*str - 'a') + 10;
    else if(*str >= 'A' && *str <= 'F') c = 16 * c + (*str - 'A') + 10;
    else break;

    str++;
  }

  NumLit* numlit = NumLitCreateEmpty();
  numlit->value = c;
  numlit->type = INT8_T;

  QueueInsert(&numlit_queue, numlit);
}

void string_lit(const char* str){
  char* lit = StringAllocate(strlen(str) - 1);
  for(int i = 0; i < strlen(str) - 2; i++){
    lit[i] = str[i + 1];
  }
  lit[strlen(str) - 2] = 0;
  
  QueueInsert(&strlit_queue, lit);
}

#include "symtab/symtab.h"
#include "decl/declarations.h"
#include "yy/y.tab.h"

int check_identifier_type(){
	extern Symtab* symtab;
	extern Stack   type_stack;
  extern char*   yytext;

	TypeFrame* type_frame = StackPeek(&type_stack);

	// if((type_frame->type_specifiers != 0 || type_frame->current_type != 0) && initializer_expression == 0) {
	if(type_frame->identifier_expected){
		// printf("forced identifier %s\n", yytext);
		// fflush(stdout);
		return IDENTIFIER;
	}
	else{
		Obj* obj_ref = SymtabFindNamespace(symtab, yytext, NAMESPACE_ORDINARY);
		if(obj_ref == 0 || obj_ref->kind != OBJ_TYPE) return IDENTIFIER;
		else return TYPE_NAME;
	}
}