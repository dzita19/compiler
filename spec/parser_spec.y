%{
	#include <stdio.h>
	#include "stmt/tree.h"

	#include "decl/declarations.h"
	#include "decl/specifiers.h"
	#include "decl/declarators.h"
	#include "decl/indirections.h"
	#include "decl/const_expr.h"

	#include "stmt/stmt.h"
	#include "stmt/literals.h"
	#include "stmt/expr/expr.h"
	#include "stmt/expr/arithm.h"
	#include "stmt/expr/bitwise.h"
	#include "stmt/expr/logic.h"
	#include "stmt/expr/postfix.h"
	#include "stmt/expr/prefix.h"
	#include "stmt/expr/primary.h"

	#include "symtab/obj.h"
	#include "symtab/struct.h"

	extern int yylex (void);
	void yyerror(char* s);
%}

%union{
	long  val;
	int 	val_type;
	char* id;
	char* strlit;
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
	: IDENTIFIER 					{ IdentifierPrimary(yylval.id); }
	| CONSTANT						{ ConstantPrimary(yylval.val, yylval.val_type); }
	| STRING_LITERAL			{ StringPrimary(yylval.strlit); }
	| '(' expression ')'	
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'															{ ArrayRefExpr(); }
	| postfix_expression args_open args_close														{ FunctionCallExpr(); }
	| postfix_expression args_open argument_expression_list args_close	{ FunctionCallExpr(); }
	| postfix_expression '.' field_name 																{ FieldRefExpr(yylval.id); }
	| postfix_expression PTR_OP field_name 															{ PtrRefExpr(yylval.id); }
	| postfix_expression INC_OP																					{ IncDecExpr(POST_INC_EXPR); }
	| postfix_expression DEC_OP 																				{ IncDecExpr(POST_DEC_EXPR); }
	;

field_name
	: IDENTIFIER { }
	;

args_open
	: '(' { FunctionArgsOpen(); }
	;

args_close
	: ')' { FunctionArgsClose(); }
	;

argument_expression_list
	: assignment_expression 															{ FunctionArg(); }
	| argument_expression_list ',' assignment_expression 	{ FunctionArg(); }
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression 	{ IncDecExpr(PRE_INC_EXPR); }
	| DEC_OP unary_expression 	{ IncDecExpr(PRE_DEC_EXPR); }
	| '&' cast_expression				{ AddressExpr(); }
	| '*' cast_expression				{ DerefExpr(); }
	| '+' cast_expression				{ UnaryExpr(UNARY_PLUS_EXPR); }
	| '-' cast_expression				{ UnaryExpr(UNARY_MINUS_EXPR); }
	| '~' cast_expression				{ BitNegExpr(); }
	| '!' cast_expression				{ LogNegExpr(); }
	| SIZEOF_ unary_expression	{ SizeofExpr(); }
	| SIZEOF_ type_open type_name type_close	{ SizeofTypeExpr(); }
	;

type_open
	: '(' { TypeOpen(); }
	;

type_close
	: ')' { TypeClose(); }
	;

cast_expression
	: unary_expression
	| type_open type_name type_close cast_expression	{ CastExpr(); }
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression	{ MulExpr(); }
	| multiplicative_expression '/' cast_expression	{ DivExpr(); }
	| multiplicative_expression '%' cast_expression	{ ModExpr(); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression	{ AddExpr(); }
	| additive_expression '-' multiplicative_expression	{ SubExpr(); }
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression	{ BitExpr(BIT_LEFT_EXPR); }
	| shift_expression RIGHT_OP additive_expression	{ BitExpr(BIT_RIGHT_EXPR); }
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression			{ RelationExpr(RELA_LT_EXPR); }
	| relational_expression '>' shift_expression			{ RelationExpr(RELA_GT_EXPR); }
	| relational_expression LE_OP shift_expression		{ RelationExpr(RELA_LE_EXPR); }
	| relational_expression GE_OP shift_expression		{ RelationExpr(RELA_GE_EXPR); }
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression	{ EqualityExpr(RELA_EQ_EXPR); }
	| equality_expression NE_OP relational_expression	{ EqualityExpr(RELA_NE_EXPR); }
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression { BitExpr(BIT_AND_EXPR); }
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression { BitExpr(BIT_XOR_EXPR); }
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression { BitExpr(BIT_OR_EXPR); }
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression	{ LogExpr(LOG_AND_EXPR); }
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression	{ LogExpr(LOG_OR_EXPR); }
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression { CondExpr(); }
	;

assignment_expression
	: conditional_expression
	| unary_expression '=' assignment_expression 					{ BasicAssignExpr(); }
	| unary_expression MUL_ASSIGN assignment_expression		{ MulAssignExpr(); }
	| unary_expression DIV_ASSIGN assignment_expression		{ DivAssignExpr(); }
	| unary_expression MOD_ASSIGN assignment_expression		{ ModAssignExpr(); }
	| unary_expression ADD_ASSIGN assignment_expression		{ AddAssignExpr(); }
	| unary_expression SUB_ASSIGN assignment_expression		{ SubAssignExpr(); }
	| unary_expression LEFT_ASSIGN assignment_expression	{ BitAssignExpr(BIT_LEFT_ASSIGN_EXPR); }
	| unary_expression RIGHT_ASSIGN assignment_expression	{ BitAssignExpr(BIT_RIGHT_ASSIGN_EXPR); }
	| unary_expression AND_ASSIGN assignment_expression		{ BitAssignExpr(BIT_AND_ASSIGN_EXPR); }
	| unary_expression XOR_ASSIGN assignment_expression		{ BitAssignExpr(BIT_XOR_ASSIGN_EXPR); }
	| unary_expression OR_ASSIGN assignment_expression		{ BitAssignExpr(BIT_OR_ASSIGN_EXPR); }
	;

rec_expression
	: assignment_expression { CommaExprOpen(); }
	| rec_expression ',' assignment_expression { CommaExpr(); }
	;

expression
	: rec_expression { FullExpr(); }
	;

constant_expression
	: conditional_expression { ConstExpression(); }
	;

declaration
	: redeclaration_specifiers ';' { Declaration(); }
	| full_declaration_specifiers init_declarator_list ';' { Declaration(); }
	;

redeclaration_specifiers
	: declaration_specifiers { RedeclarationSpecifiers(); }
	;

full_declaration_specifiers
	: declaration_specifiers { FullDeclarationSpecifiers(); }
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: full_declarator { NotFunctionDefinition(); }
	| full_declarator_initialized { NotFunctionDefinition(); }
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
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME		{ IdentifierName(yylval.id); TypedefName(); }
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
	: '}'	{ }
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: full_specifier_qualifier_list struct_declarator_list ';' { Declaration(); }
	;

full_specifier_qualifier_list
	: specifier_qualifier_list { FullDeclarationSpecifiers(); }
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
	: full_declarator
	| ':' constant_expression
	| full_declarator ':' constant_expression
	;

enum_specifier
	: enum tag_name tag_def_open enumerator_list tag_def_close { TagDefined(); }
	| enum tag_def_open enumerator_list tag_def_close { TagDefined(); }
	| enum tag_name tag_def_open enumerator_list ',' tag_def_close { TagDefined(); }
	| enum tag_def_open enumerator_list ',' tag_def_close { TagDefined(); }
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

full_declarator
	: declarator { Declarator(); }
	;

full_declarator_initialized
	: declarator '=' initializer { DeclaratorInitialized(); }
	;

declarator
	: pointer direct_declarator { NestedDeclarator(); }
	| direct_declarator
	;

direct_declarator
	: declarator_name
	| '(' declarator ')' { }
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
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: full_declaration_specifiers full_declarator { Declaration(); }
	| full_declaration_specifiers full_abstract_declarator { Declaration(); }
	| full_declaration_specifiers { Declaration(); }
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

full_abstract_declarator
	: abstract_declarator { AbstractDeclarator(); }
	;

abstract_declarator
	: pointer { NestedDeclarator(); }
	| direct_abstract_declarator
	| pointer direct_abstract_declarator { NestedDeclarator(); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { }
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

func_body
	: func_body_open func_body_close
	| func_body_open block func_body_close
	;

func_body_open
	: '{' { FuncBodyOpen(); }
	;

func_body_close
	: '}' { FuncBodyClose(); }
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

expression_statement
	: ';'						 	{ EmptyStmt(); }
	| expression ';'	{ ExpressionStmt(); }
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

rec_translation_unit
	: external_declaration
	| rec_translation_unit external_declaration
	;

translation_unit
	: rec_translation_unit { TranslationUnit(); }
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: full_declaration_specifiers full_declarator declaration_list func_body { FunctionDefinition(); }
	| full_declaration_specifiers full_declarator func_body	{ FunctionDefinition(); }
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