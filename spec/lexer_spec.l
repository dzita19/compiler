
D			[0-9]
O			[0-7]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "y.tab.h"
#include "decl/declarations.h"
#include "stmt/literals.h"

#include "util/memory_safety.h"
#include "symtab/symtab.h"

void count();
void comment();
void one_liner();
int  check_identifier_type();

int yywrap();
%}

%%
"/*"					{ comment(); }
"//"					{ one_liner(); }

"auto"				{ count(); return(AUTO_); }
"break"				{ count(); return(BREAK_); }
"case"				{ count(); return(CASE_); }
"char"				{ count(); return(CHAR_); }
"const"				{ count(); return(CONST_); }
"continue"		{ count(); return(CONTINUE_); }
"default"			{ count(); return(DEFAULT_); }
"do"					{ count(); return(DO_); }
"double"			{ count(); return(DOUBLE_); }
"else"				{ count(); return(ELSE_); }
"enum"				{ count(); return(ENUM_); }
"extern"			{ count(); return(EXTERN_); }
"float"				{ count(); return(FLOAT_); }
"for"					{ count(); return(FOR_); }
"goto"				{ count(); return(GOTO_); }
"if"					{ count(); return(IF_); }
"int"					{ count(); return(INT_); }
"long"				{ count(); return(LONG_); }
"register"		{ count(); return(REGISTER_); }
"return"			{ count(); return(RETURN_); }
"short"				{ count(); return(SHORT_); }
"signed"			{ count(); return(SIGNED_); }
"sizeof"			{ count(); return(SIZEOF_); }
"static"			{ count(); return(STATIC_); }
"struct"			{ count(); return(STRUCT_); }
"switch"			{ count(); return(SWITCH_); }
"typedef"			{ count(); return(TYPEDEF_); }
"union"				{ count(); return(UNION_); }
"unsigned"		{ count(); return(UNSIGNED_); }
"void"				{ count(); return(VOID_); }
"volatile"		{ count(); return(VOLATILE_); }
"while"				{ count(); return(WHILE_); }
"__asm__"			{ count(); return(ASM_); }

{L}({L}|{D})*						{ count(); identifier(yytext);	return(check_identifier_type()); }

0[xX]{H}+{IS}?					{ count(); hex_val(yytext); 		return(CONSTANT); }

0{O}+{IS}?							{ count(); oct_val(yytext); 		return(CONSTANT); }

{D}+{IS}?								{ count(); dec_val(yytext); 		return(CONSTANT); }

'[^\\']'								{ count(); simple_char_lit(yytext + 1); 				return(CONSTANT); }

'\\['"?\\abfnrtv]'			{ count(); simple_escape_char_lit(yytext + 1); 	return(CONSTANT); }

'\\{O}{1,3}'						{ count(); oct_char_lit(yytext + 1); 						return(CONSTANT); }

'\\x{H}+'								{ count(); hex_char_lit(yytext + 1); 						return(CONSTANT); }

{D}+{E}{FS}?						{ count(); return(CONSTANT); }

{D}*"."{D}+({E})?{FS}?	{ count(); return(CONSTANT); }

{D}+"."{D}*({E})?{FS}?	{ count(); return(CONSTANT); }

\"([^\\"\n]|(\\['"?\\abfnrtv])|(\\{O}{1,3})|(\\x{H}+))*\" { count(); string_lit(yytext); return(STRING_LITERAL); }

"..."					{ count(); return(ELLIPSIS); }
">>="					{ count(); return(RIGHT_ASSIGN); }
"<<="					{ count(); return(LEFT_ASSIGN); }
"+="					{ count(); return(ADD_ASSIGN); }
"-="					{ count(); return(SUB_ASSIGN); }
"*="					{ count(); return(MUL_ASSIGN); }
"/="					{ count(); return(DIV_ASSIGN); }
"%="					{ count(); return(MOD_ASSIGN); }
"&="					{ count(); return(AND_ASSIGN); }
"^="					{ count(); return(XOR_ASSIGN); }
"|="					{ count(); return(OR_ASSIGN); }
">>"					{ count(); return(RIGHT_OP); }
"<<"					{ count(); return(LEFT_OP); }
"++"					{ count(); return(INC_OP); }
"--"					{ count(); return(DEC_OP); }
"->"					{ count(); return(PTR_OP); }
"&&"					{ count(); return(AND_OP); }
"||"					{ count(); return(OR_OP); }
"<="					{ count(); return(LE_OP); }
">="					{ count(); return(GE_OP); }
"=="					{ count(); return(EQ_OP); }
"!="					{ count(); return(NQ_OP); }
";"						{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","						{ count(); return(','); }
":"						{ count(); return(':'); }
"="						{ count(); return('='); }
"("						{ count(); return('('); }
")"						{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."						{ count(); return('.'); }
"&"						{ count(); return('&'); }
"!"						{ count(); return('!'); }
"~"						{ count(); return('~'); }
"-"						{ count(); return('-'); }
"+"						{ count(); return('+'); }
"*"						{ count(); return('*'); }
"/"						{ count(); return('/'); }
"%"						{ count(); return('%'); }
"<"						{ count(); return('<'); }
">"						{ count(); return('>'); }
"^"						{ count(); return('^'); }
"|"						{ count(); return('|'); }
"?"						{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.							{ count(); printf("Illegal token\n"); return(-1); }

%%

int yywrap()
{
	return(1);
}


int column = 1;
int row = 1;

const int tab_width = 2;

void comment()
{
	char c, c1;
	count();

loop:
	while ((c = input()) != '*' && c != 0) {
		if(c == '\n') {
			row++;
			column = 1;
		}
		else if (c == '\t')
			column += tab_width - (column % tab_width);
		else column++;
	}

	column++; // '*' was the last character

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	column++; // '/' was the last character

	// if (c != 0) putchar(c1);
}

void one_liner(){
	char c;
	int extend;

one_liner:
	extend = 0; // extend comment to the next line
	while((c = input()) != '\n' && c != '\0'){
		if(c == '\\') extend = 1;
		else extend = 0;

		if (c == '\t') column += tab_width - (column % tab_width);
		else column++;
	}

	column = 1;
	row++;

	if(extend) goto one_liner;
}

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n'){
			column = 1;
			row++;
		}
		else if (yytext[i] == '\t')
			column += tab_width - (column % tab_width);
		else
			column++;

}