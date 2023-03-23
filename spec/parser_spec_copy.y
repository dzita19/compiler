%{
	#include <stdio.h>
	#include "stmt/tree.h"
	#include "stmt/production.h"

	#include "decl/declarations.h"
	#include "decl/specifiers.h"
	#include "decl/declarators.h"
	#include "decl/indirections.h"
	#include "decl/blocks.h"

	#include "symtab/obj.h"
	#include "symtab/struct.h"

	extern int yylex (void);
	void yyerror(char* s);
%}

%union{
	int num;
	char* id;
	char* string_literal;
}
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF_
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF_ EXTERN_ STATIC_ AUTO_ REGISTER_
%token CHAR_ SHORT_ INT_ LONG_ SIGNED_ UNSIGNED_ FLOAT_ DOUBLE_ CONST_ VOLATILE_ VOID_
%token STRUCT_ UNION_ ENUM_ ELLIPSIS

%token CASE_ DEFAULT_ IF_ ELSE_ SWITCH_ WHILE_ DO_ FOR_ GOTO_ CONTINUE_ BREAK_ RETURN_

%start translation_unit
%%

primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| '&' cast_expression
	| '*' cast_expression
	| '+' cast_expression
	| '-' cast_expression
	| '~' cast_expression
	| '!' cast_expression
	| SIZEOF_ unary_expression
	| SIZEOF_ '(' type_name ')'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression '=' assignment_expression
	| unary_expression MUL_ASSIGN assignment_expression
	| unary_expression DIV_ASSIGN assignment_expression
	| unary_expression MOD_ASSIGN assignment_expression
	| unary_expression ADD_ASSIGN assignment_expression
	| unary_expression SUB_ASSIGN assignment_expression
	| unary_expression LEFT_ASSIGN assignment_expression
	| unary_expression RIGHT_ASSIGN assignment_expression
	| unary_expression AND_ASSIGN assignment_expression
	| unary_expression XOR_ASSIGN assignment_expression
	| unary_expression OR_ASSIGN assignment_expression
	;

expression
	: assignment_expression { }
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression { /*ConstantExpressionProcessor();*/ }
	;

declaration
	: declaration_specifiers ';' { NoDeclarators(); Declaration(); }
	| declaration_specifiers init_declarator_list ';' { Declaration(); }
	;

declaration_specifiers
	: storage_class_specifier	{ DeclarationSpecifiers(); }
	| storage_class_specifier declaration_specifiers
	| type_specifier	{ DeclarationSpecifiers(); }
	| type_specifier declaration_specifiers
	| type_qualifier	{ DeclarationSpecifiers(); }
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator { Declarator(); NotFunctionDefinition(); }
	| declarator '=' initializer { DeclaratorInitialized(); NotFunctionDefinition(); }
	;

storage_class_specifier
	: TYPEDEF_ 	{ StorageClassSpecifierRef(TYPEDEF); }
	| EXTERN_  	{ StorageClassSpecifierRef(EXTERN); }
	| STATIC_  	{ StorageClassSpecifierRef(STATIC); }
	| AUTO_	  	{ StorageClassSpecifierRef(AUTO); }
	| REGISTER_	{ StorageClassSpecifierRef(REGISTER); }
	;

type_specifier
	: VOID_				{ TypeSpecifierRef(VOID); }
	| CHAR_				{ TypeSpecifierRef(CHAR); }
	| SHORT_			{ TypeSpecifierRef(SHORT); }
	| INT_				{ TypeSpecifierRef(INT); }
	| LONG_				{ TypeSpecifierRef(LONG); }
	| FLOAT_			{ TypeSpecifierRef(FLOAT); }
	| DOUBLE_			{ TypeSpecifierRef(DOUBLE); }
	| SIGNED_			{ TypeSpecifierRef(SIGNED); }
	| UNSIGNED_		{ TypeSpecifierRef(UNSIGNED); }
	| struct_or_union_specifier { TypeSpecifierRef(CUSTOM_TYPE); }
	| enum_specifier						{ TypeSpecifierRef(CUSTOM_TYPE); }
	| TYPE_NAME 								{ TypeSpecifierRef(CUSTOM_TYPE); }
	;

struct_or_union_specifier
	: struct_or_union tag_name tag_def_open struct_declaration_list tag_def_close { TagDefined(); }
	| struct_or_union tag_def_open struct_declaration_list tag_def_close { TagDefined(); }
	| struct_or_union tag_name { TagDeclared(); }
	;

struct_or_union
	: STRUCT_	{ TagTypeRef(TAG_STRUCT); }
	| UNION_		{ TagTypeRef(TAG_UNION); }
	;

tag_name
	: IDENTIFIER { IdentifierName(yylval.id); }
	;

tag_def_open
	: '{'	{ TagDefOpen(); }
	;

tag_def_close
	: '}'	{ TagDefClose(); }
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' { Declaration(); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator { Declarator(); }
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: enum tag_name tag_def_open enumerator_list tag_def_close { TagDefined(); }
	| enum tag_def_open enumerator_list tag_def_close { TagDefined(); }
	| enum tag_name { TagDeclared(); }
	;

enum
	: ENUM_	{ TagTypeRef(TAG_ENUM); }
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: declarator_name { EnumeratorDefault(); }
	| declarator_name '=' constant_expression { EnumeratorCustom(); }
	;

type_qualifier
	: CONST_			{ TypeQualifierRef(CONST); }
	| VOLATILE_		{ TypeQualifierRef(VOLATILE); }
	;

declarator
	: pointer direct_declarator { NestedDeclarator(); }
	| direct_declarator
	;

direct_declarator
	: declarator_name
	| '(' declarator ')' { /*NestedDeclarator();*/ }
	| direct_declarator '[' constant_expression ']' { ArrayLengthDeclarator(); }
	| direct_declarator '[' ']' { ArrayVariableDeclarator(); }
	| direct_declarator function_params_open parameter_type_list function_params_close { FunctionDeclarator(); }
	| direct_declarator function_params_open identifier_list function_params_close { FunctionDeclarator(); }
	| direct_declarator function_params_open function_params_close { FunctionDeclarator(); }
	;

declarator_name
	: IDENTIFIER { IdentifierName(yyval.id); }
	;

function_params_open
	: '(' { FunctionParamsOpen(); }
	;

function_params_close
	: ')'	{ FunctionParamsClose(); }
	;
	
pointer
	: '*' { PointerOpen(); }
	| '*' type_qualifier_list { PointerQualifierOpen();}
	| '*' pointer { Pointer(); }
	| '*' type_qualifier_list pointer { PointerQualifier(); }
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS { Ellipsis(); }
	;

parameter_list
	: parameter_declaration { Declaration(); }
	| parameter_list ',' parameter_declaration { Declaration(); }
	;

parameter_declaration
	: declaration_specifiers declarator { Declarator(); }
	| declaration_specifiers abstract_declarator { AbstractDeclarator(); }
	| declaration_specifiers { AbstractDeclarator(); }
	;

identifier_list
	: function_param_name { Declaration(); }
	| identifier_list ',' function_param_name { Declaration(); }
	;

function_param_name
	: declarator_name { Declarator(); }
	;

type_name
	: specifier_qualifier_list { /*TypeName();*/ }
	| specifier_qualifier_list abstract_declarator { /*TypeName();*/ }
	;

abstract_declarator
	: pointer { NestedDeclarator(); }
	| direct_abstract_declarator
	| pointer direct_abstract_declarator { NestedDeclarator(); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { /*NestedDeclarator();*/ }
	| '[' ']' { ArrayVariableDeclarator(); }
	| '[' constant_expression ']'  { ArrayLengthDeclarator(); }
	| direct_abstract_declarator '[' ']'  { ArrayVariableDeclarator(); }
	| direct_abstract_declarator '[' constant_expression ']'  { ArrayLengthDeclarator(); }
	| function_params_open function_params_close { FunctionDeclarator(); }
	| function_params_open parameter_type_list function_params_close { FunctionDeclarator(); }
	| direct_abstract_declarator function_params_open function_params_close { FunctionDeclarator(); }
	| direct_abstract_declarator function_params_open parameter_type_list function_params_close { FunctionDeclarator(); }
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE_ constant_expression ':' statement
	| DEFAULT_ ':' statement
	;

compound_statement
	: block_open block_close
	| block_open block block_close
	;

block_open
	: '{' { BlockOpen(); }
	;

block_close
	: '}' { BlockClose(); }
	;

block
	: block_item
	| block_item block
	;

block_item
	: statement
	| declaration
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF_ '(' expression ')' statement
	| IF_ '(' expression ')' statement ELSE_ statement
	| SWITCH_ '(' expression ')' statement
	;

iteration_statement
	: WHILE_ '(' expression ')' statement
	| DO_ statement WHILE_ '(' expression ')' ';'
	| FOR_ '(' expression_statement expression_statement ')' statement
	| FOR_ '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO_ IDENTIFIER ';'
	| CONTINUE_ ';'
	| BREAK_ ';'
	| RETURN_ ';'
	| RETURN_ expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { FunctionDefinition(); }
	| declaration_specifiers declarator compound_statement	{ FunctionDefinition(); }
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}