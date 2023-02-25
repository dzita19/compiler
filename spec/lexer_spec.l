
D			[0-9]
L			[a-zA-Z_]

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"
#include "ast/tree.h"

void count();
void comment();
int yywrap();
%}

%%
"/*"			{ comment(); }

{L}({L}|{D})*		{ count(); yylval.id = strdup(yytext); return(IDENTIFIER); }
{D}+		{ count(); yylval.num = atoi(yytext); return(CONSTANT); }

";"			{ count(); return(';'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }

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
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
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

	//ECHO;
}