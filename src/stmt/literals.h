#ifndef _LITERALS_H_
#define _LITERALS_H_

#include "symtab/struct.h"
#include "util/queue.h"
#include "util/memory_safety.h"

typedef struct NumLit{
  int            value;
  PredefinedType type;
} NumLit;

NumLit* NumLitCreateEmpty();
void NumLitDrop(NumLit*);

extern Queue numlit_queue;
extern Queue strlit_queue;

void hex_val(const char* str);
void oct_val(const char* str);
void dec_val(const char* str);

void simple_char_lit(const char* str);
void simple_escape_char_lit(const char* str);
void oct_char_lit(const char* str);
void hex_char_lit(const char* str);

void string_lit(const char*);

int check_identifier_type(void);

#endif