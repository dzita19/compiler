
D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"

void count();
void comment();
int yywrap();
%}

%%
"/*"					{ comment(); }

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

{L}({L}|{D})*						{ count();
	yylval.id = strdup(yytext); return(IDENTIFIER); }

0[xX]{H}+{IS}?					{ count(); return(CONSTANT); }

0{D}+{IS}?							{ count(); return(CONSTANT); }

{D}+{IS}?								{ count(); return(CONSTANT); }

L?'(\\.|[^\\'])+'				{ count(); return(CONSTANT); }

{D}+{E}{FS}?						{ count(); return(CONSTANT); }

{D}*"."{D}+({E})?{FS}?	{ count(); return(CONSTANT); }

{D}+"."{D}*({E})?{FS}?	{ count(); return(CONSTANT); }

L?\"(\\.|[^\\"])*\"			{ count(); return(STRING_LITERAL); }

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
"!="					{ count(); return(NE_OP); }
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
.			{ /* ignore bad characters */ }

%%

int yywrap()
{
	return(1);
}


void comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0);
		//putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0);
		//putchar(c1);
}

int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

}