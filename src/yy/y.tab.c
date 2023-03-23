/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "spec/parser_spec.y"

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

#line 97 "src/yy/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SRC_YY_Y_TAB_H_INCLUDED
# define YY_YY_SRC_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    CONSTANT = 259,
    STRING_LITERAL = 260,
    SIZEOF_ = 261,
    PTR_OP = 262,
    INC_OP = 263,
    DEC_OP = 264,
    LEFT_OP = 265,
    RIGHT_OP = 266,
    LE_OP = 267,
    GE_OP = 268,
    EQ_OP = 269,
    NE_OP = 270,
    AND_OP = 271,
    OR_OP = 272,
    MUL_ASSIGN = 273,
    DIV_ASSIGN = 274,
    MOD_ASSIGN = 275,
    ADD_ASSIGN = 276,
    SUB_ASSIGN = 277,
    LEFT_ASSIGN = 278,
    RIGHT_ASSIGN = 279,
    AND_ASSIGN = 280,
    XOR_ASSIGN = 281,
    OR_ASSIGN = 282,
    TYPE_NAME = 283,
    TYPEDEF_ = 284,
    EXTERN_ = 285,
    STATIC_ = 286,
    AUTO_ = 287,
    REGISTER_ = 288,
    CHAR_ = 289,
    SHORT_ = 290,
    INT_ = 291,
    LONG_ = 292,
    SIGNED_ = 293,
    UNSIGNED_ = 294,
    FLOAT_ = 295,
    DOUBLE_ = 296,
    CONST_ = 297,
    VOLATILE_ = 298,
    VOID_ = 299,
    STRUCT_ = 300,
    UNION_ = 301,
    ENUM_ = 302,
    ELLIPSIS = 303,
    CASE_ = 304,
    DEFAULT_ = 305,
    IF_ = 306,
    ELSE_ = 307,
    SWITCH_ = 308,
    WHILE_ = 309,
    DO_ = 310,
    FOR_ = 311,
    GOTO_ = 312,
    CONTINUE_ = 313,
    BREAK_ = 314,
    RETURN_ = 315
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "spec/parser_spec.y"

	long  val;
	int 	val_type;
	char* id;
	char* strlit;

#line 217 "src/yy/y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1024

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  89
/* YYNRULES -- Number of rules.  */
#define YYNRULES  237
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  392

#define YYUNDEFTOK  2
#define YYMAXUTOK   315


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,     2,     2,    74,    67,     2,
      61,    62,    68,    69,    66,    70,    65,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    80,    82,
      75,    81,    76,    79,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,    64,    77,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    83,    78,    84,    71,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    51,    52,    53,    57,    58,    59,    60,
      61,    62,    63,    64,    68,    72,    76,    80,    81,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      99,   103,   107,   108,   112,   113,   114,   115,   119,   120,
     121,   125,   126,   127,   131,   132,   133,   134,   135,   139,
     140,   141,   145,   146,   150,   151,   155,   156,   160,   161,
     165,   166,   170,   171,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   190,   191,   195,   199,
     203,   204,   208,   212,   216,   217,   218,   219,   220,   221,
     225,   226,   230,   231,   235,   236,   237,   238,   239,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   258,   259,   260,   264,   265,   269,   273,   277,   281,
     282,   286,   290,   294,   295,   296,   297,   301,   302,   306,
     307,   308,   312,   313,   314,   315,   316,   320,   324,   325,
     329,   330,   334,   335,   339,   343,   347,   348,   352,   353,
     354,   355,   356,   357,   358,   362,   366,   370,   374,   375,
     376,   377,   381,   382,   386,   387,   391,   392,   396,   397,
     398,   402,   403,   407,   411,   412,   416,   420,   421,   422,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   438,
     439,   440,   444,   445,   449,   450,   451,   452,   453,   454,
     458,   459,   460,   464,   465,   469,   473,   477,   478,   482,
     483,   487,   488,   492,   496,   500,   501,   505,   506,   510,
     511,   512,   516,   517,   518,   519,   523,   524,   525,   526,
     527,   531,   532,   536,   540,   541,   545,   546
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF_", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "TYPEDEF_", "EXTERN_", "STATIC_", "AUTO_", "REGISTER_",
  "CHAR_", "SHORT_", "INT_", "LONG_", "SIGNED_", "UNSIGNED_", "FLOAT_",
  "DOUBLE_", "CONST_", "VOLATILE_", "VOID_", "STRUCT_", "UNION_", "ENUM_",
  "ELLIPSIS", "CASE_", "DEFAULT_", "IF_", "ELSE_", "SWITCH_", "WHILE_",
  "DO_", "FOR_", "GOTO_", "CONTINUE_", "BREAK_", "RETURN_", "'('", "')'",
  "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'",
  "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='", "';'",
  "'{'", "'}'", "$accept", "primary_expression", "postfix_expression",
  "field_name", "args_open", "args_close", "argument_expression_list",
  "unary_expression", "type_open", "type_close", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "rec_expression",
  "expression", "constant_expression", "declaration",
  "redeclaration_specifiers", "full_declaration_specifiers",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "tag_name", "tag_def_open", "tag_def_close",
  "struct_declaration_list", "struct_declaration",
  "full_specifier_qualifier_list", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_specifier", "enum",
  "enumerator_list", "enumerator", "type_qualifier", "full_declarator",
  "full_declarator_initialized", "declarator", "direct_declarator",
  "declarator_name", "function_params_open", "function_params_close",
  "pointer", "type_qualifier_list", "parameter_type_list",
  "parameter_list", "parameter_declaration", "identifier_list",
  "function_param_name", "type_name", "full_abstract_declarator",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "block_open", "block_close", "block", "block_item",
  "func_body", "func_body_open", "func_body_close", "declaration_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "rec_translation_unit", "translation_unit",
  "external_declaration", "function_definition", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,    40,    41,    91,    93,    46,    44,    38,    42,    43,
      45,   126,    33,    47,    37,    60,    62,    94,   124,    63,
      58,    61,    59,   123,   125
};
# endif

#define YYPACT_NINF (-246)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-83)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     977,  -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,
    -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,
    -246,  -246,   -35,    63,   -21,   977,   977,  -246,    11,  -246,
      11,   977,   977,    39,  -246,  -246,  -246,  -246,    63,    71,
      -2,  -246,   865,  -246,    69,    12,  -246,    35,  -246,  -246,
    -246,  -246,   -30,   896,   -30,    55,  -246,  -246,  -246,    70,
    -246,  -246,    71,    63,  -246,  -246,  -246,    63,  -246,   325,
     865,   564,  -246,   635,   816,    12,   896,   896,   845,  -246,
      32,  -246,   896,    55,   -29,  -246,    78,  -246,  -246,  -246,
    -246,  -246,   104,  -246,  -246,   759,   771,   771,   759,   132,
     154,   173,   176,   547,   182,   243,   168,   175,   581,   759,
     759,   759,   759,   759,   759,   759,  -246,  -246,  -246,  -246,
     209,   403,   896,  -246,   159,   153,   219,    50,   226,   198,
     190,   193,   259,     7,  -246,  -246,   210,   202,  -246,  -246,
    -246,  -246,   407,   205,   477,  -246,  -246,  -246,  -246,  -246,
    -246,  -246,  -246,   564,  -246,  -246,  -246,  -246,  -246,   222,
    -246,    22,  -246,  -246,  -246,   225,   224,  -246,    61,  -246,
     845,  -246,  -246,  -246,  -246,   759,    56,  -246,   213,  -246,
    -246,    21,    20,  -246,   759,   547,  -246,   896,   759,  -246,
    -246,   214,   547,   759,   759,   759,   241,   618,   216,  -246,
    -246,  -246,   218,   239,  -246,  -246,  -246,  -246,  -246,  -246,
     299,  -246,  -246,  -246,   759,   299,   651,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   122,   247,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
    -246,  -246,  -246,   221,  -246,  -246,  -246,    51,  -246,    22,
     663,  -246,   921,    86,  -246,  -246,   147,  -246,   956,    55,
    -246,  -246,  -246,    32,  -246,   759,    20,  -246,  -246,  -246,
    -246,  -246,   247,   547,  -246,   248,   249,   251,   253,   618,
    -246,  -246,  -246,  -246,  -246,   252,  -246,  -246,  -246,    89,
    -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,  -246,
    -246,  -246,   122,   148,  -246,  -246,   759,  -246,  -246,  -246,
     159,   159,   153,   153,   219,   219,   219,   219,    50,    50,
     226,   198,   190,   193,   259,   237,  -246,  -246,    73,  -246,
     256,  -246,   255,  -246,   225,   147,   689,   921,  -246,  -246,
    -246,  -246,  -246,  -246,  -246,  -246,   547,   547,   547,   759,
     733,  -246,   759,  -246,  -246,   759,  -246,  -246,  -246,  -246,
    -246,  -246,   257,  -246,   225,   268,  -246,  -246,   260,   547,
     262,  -246,  -246,  -246,  -246,   547,   244,  -246,   547,  -246,
    -246,  -246
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   110,    94,    95,    96,    97,    98,   100,   101,   102,
     103,   106,   107,   104,   105,   142,   143,    99,   114,   115,
     137,   235,     0,     0,    83,    84,    86,   108,     0,   109,
       0,    88,   233,     0,   231,   234,    80,   155,     0,   158,
       0,    90,    92,    93,   144,   147,   148,     0,    85,    87,
     116,   117,   113,     0,   136,     0,    89,   232,     1,     0,
     162,   160,   159,     0,    81,   213,   215,     0,   237,     0,
       0,     0,   156,     0,     0,   146,     0,   124,     0,   119,
       0,   122,   126,     0,     0,   138,   140,   149,   163,   161,
      91,    92,     2,     3,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,   217,   205,   214,     6,
      19,    32,     0,    34,    38,    41,    44,    49,    52,    54,
      56,    58,    60,    62,    64,    76,    78,     0,   210,   209,
     194,   195,     0,     0,   207,   211,   196,   197,   198,   199,
     216,   236,     2,     0,   189,   145,   151,    32,    79,     0,
     157,   170,    83,   173,   154,     0,   164,   166,     0,   171,
       0,   123,   118,   112,   120,     0,     0,   127,   129,   144,
     125,     0,     0,   133,     0,     0,    28,     0,     0,    20,
      21,     0,     0,     0,     0,     0,     0,     0,     0,   227,
     228,   229,     0,     0,    22,    23,    24,    25,    26,    27,
       0,    12,    13,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     218,   206,   203,     0,   212,   208,   192,     0,   150,   156,
       0,   168,     0,   177,   169,   176,   178,   152,     0,     0,
     153,   111,   130,     0,   121,     0,     0,   132,   135,   139,
     141,   200,     0,     0,   202,     0,     0,     0,     0,     0,
     226,   230,     5,    14,    11,     0,    10,    16,     8,     0,
      17,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    65,   156,   177,   175,    31,     0,    35,    36,    37,
      39,    40,    42,    43,    47,    48,    45,    46,    50,    51,
      53,    55,    57,    59,    61,     0,    77,   204,     0,   190,
       0,   181,     0,   185,     0,   179,     0,     0,   165,   167,
     172,   128,   131,   134,    29,   201,     0,     0,     0,     0,
       0,     7,     0,     9,    33,     0,   191,   193,   180,   182,
     186,   183,     0,   187,     0,   219,   221,   222,     0,     0,
       0,    18,    63,   184,   188,     0,     0,   224,     0,   220,
     223,   225
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -246,  -246,  -246,   112,  -246,    33,  -246,   -69,   240,    54,
     -43,    15,    17,   -58,    13,    94,    96,    93,    95,    97,
    -246,   -68,   -23,  -246,   -96,   -47,    59,  -246,     0,   -24,
    -246,   279,  -246,   203,  -246,  -246,   313,   106,   -62,   269,
     -60,  -246,   -66,  -246,    75,  -246,  -246,   263,  -167,   230,
     -15,  -246,   -28,   -38,   -34,   -42,  -108,    -8,  -246,  -245,
    -246,    81,  -246,    82,   163,  -246,  -125,  -229,  -133,  -246,
     -97,  -246,  -246,  -246,   124,    77,  -246,   317,  -246,   245,
    -246,  -178,  -246,  -246,  -246,  -246,  -246,   357,  -246
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   119,   120,   294,   216,   298,   299,   121,   122,   316,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   159,   138,    22,    67,    24,
      40,    41,    25,    26,    27,    28,    52,    53,   173,    78,
      79,    80,    81,   176,   177,    29,    30,    84,    85,    31,
      91,    43,    44,    45,    46,   262,   164,    47,    62,   165,
     166,   167,   168,   169,   229,   264,   340,   266,   155,   257,
     139,   140,   141,   142,   252,   143,   144,    68,    69,   145,
      70,   146,   147,   148,   149,    32,    33,    34,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    48,    49,    74,   157,   158,   196,    56,    42,    75,
      59,   171,   202,   203,    50,   279,   180,   344,   174,   289,
     256,    86,   183,    37,   247,    37,   186,   189,   190,   157,
     158,    61,    23,    74,   345,    37,   265,   182,    37,    58,
     163,   157,   157,   157,   157,   157,   157,    36,   154,    86,
     162,   191,   179,    51,    89,   172,   228,   267,    37,    21,
     270,   -82,   237,   238,    63,   178,    37,   204,   205,   206,
     207,   208,   209,    72,   161,    73,   152,    93,    94,    95,
      64,    96,    97,   259,   345,   260,   248,   276,   281,    37,
      39,    21,   203,    38,    51,   284,    38,   285,   286,   287,
      39,    66,   374,   314,   172,   172,   157,   158,   271,   279,
     174,   360,   175,    15,    16,   157,   158,   338,   295,   277,
     278,   228,   273,   160,    38,   239,   240,   269,   272,   150,
     154,    39,    87,   179,   109,   339,    55,   280,   274,    39,
     110,   111,   112,   113,   114,   115,   261,   259,    86,   260,
      71,   297,   335,   263,   343,   362,   153,   366,    76,   184,
      83,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   324,
     325,   326,   327,   312,   185,   260,   355,   317,   318,   319,
      39,   157,   158,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   367,   157,   158,    72,   312,
     346,   260,   192,   342,   353,   193,   210,   211,   212,   253,
     313,   255,   233,   234,   347,    75,   336,   230,   352,   235,
     236,    59,   231,   232,   194,   163,   370,   195,   162,   373,
     241,   242,    86,   197,   162,   179,   198,   157,   320,   321,
     199,   263,   322,   323,   328,   329,    77,   200,   178,   375,
     376,   377,   161,   378,   380,   243,   384,   244,   161,    60,
     213,   245,   214,   364,   215,   246,   249,   157,   158,    77,
      77,    77,   387,    82,   250,    77,   258,   160,   389,   118,
     268,   391,    88,   275,   283,   288,   157,   382,   290,   372,
     291,   292,   293,   347,   313,   251,    82,    82,    82,   315,
     356,   357,    82,   358,   359,   154,   361,   365,   368,   369,
     385,   383,   386,   162,   388,    77,   390,   296,    92,    93,
      94,    95,   363,    96,    97,   187,   354,   330,   332,   381,
     331,   333,    90,    54,   334,   170,   181,   161,   351,   349,
     282,   350,    82,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    77,    98,    99,   100,   337,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   151,   254,    57,
      77,     0,   110,   111,   112,   113,   114,   115,     0,     0,
      82,     0,     0,     0,     0,     0,     0,   116,   117,   118,
      92,    93,    94,    95,     0,    96,    97,    82,     0,     0,
       0,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     0,    98,    99,   100,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
      92,    93,    94,    95,   227,    96,    97,     0,     0,   116,
     117,   251,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     0,    98,    99,   100,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
      92,    93,    94,    95,     0,    96,    97,     0,     0,   116,
     117,     0,     0,     0,     0,     0,     0,   152,    93,    94,
      95,     0,    96,    97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,     0,    98,    99,   100,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,   152,    93,    94,    95,   109,    96,    97,     0,   116,
     117,   110,   111,   112,   113,   114,   115,     0,   152,    93,
      94,    95,   109,    96,    97,     0,     0,   153,   110,   111,
     112,   113,   114,   115,   152,    93,    94,    95,     0,    96,
      97,     0,     0,   201,     0,     0,   152,    93,    94,    95,
       0,    96,    97,     0,     0,     0,     0,     0,     0,   109,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,   152,    93,    94,    95,   109,    96,    97,   156,
     116,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,   109,   297,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,   109,     0,     0,   341,     0,     0,
     110,   111,   112,   113,   114,   115,   152,    93,    94,    95,
       0,    96,    97,     0,     0,     0,     0,     0,     0,     0,
     109,     0,     0,   371,     0,     0,   110,   111,   112,   113,
     114,   115,   152,    93,    94,    95,     0,    96,    97,     0,
       0,     0,     0,     0,   152,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   379,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
     109,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   188,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     0,   160,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     0,   172,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     0,     0,    65,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,   348,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20
};

static const yytype_int16 yycheck[] =
{
       0,    25,    26,    45,    73,    73,   103,    31,    23,    47,
      38,    77,   108,   109,     3,   182,    82,   262,    78,   197,
     153,    55,    84,     3,    17,     3,    95,    96,    97,    98,
      98,    39,    32,    75,   263,     3,   161,    66,     3,     0,
      74,   110,   111,   112,   113,   114,   115,    82,    71,    83,
      74,    98,    80,    83,    62,    84,   122,   165,     3,     0,
     168,    82,    12,    13,    66,    80,     3,   110,   111,   112,
     113,   114,   115,    61,    74,    63,     3,     4,     5,     6,
      82,     8,     9,    61,   313,    63,    79,    66,   185,     3,
      68,    32,   188,    61,    83,   192,    61,   193,   194,   195,
      68,    42,   347,   228,    84,    84,   175,   175,   170,   276,
     170,   289,    80,    42,    43,   184,   184,    66,   214,   181,
     182,   187,    66,    62,    61,    75,    76,    66,   175,    70,
     153,    68,    62,   161,    61,    84,    30,   184,    82,    68,
      67,    68,    69,    70,    71,    72,   161,    61,   182,    63,
      81,    62,   248,   161,   262,    66,    83,    84,    52,    81,
      54,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   237,
     238,   239,   240,    61,    80,    63,   283,   230,   231,   232,
      68,   260,   260,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   338,   275,   275,    61,    61,
      63,    63,    80,   260,   276,    61,     7,     8,     9,   142,
     228,   144,    69,    70,   266,   263,   249,    68,   275,    10,
      11,   259,    73,    74,    61,   269,   344,    61,   262,   347,
      14,    15,   276,    61,   268,   273,     3,   316,   233,   234,
      82,   259,   235,   236,   241,   242,    53,    82,   273,   356,
     357,   358,   262,   359,   360,    67,   374,    77,   268,    39,
      61,    78,    63,   316,    65,    16,    66,   346,   346,    76,
      77,    78,   379,    53,    82,    82,    64,    62,   385,    84,
      66,   388,    62,    80,    80,    54,   365,   365,    82,   346,
      82,    62,     3,   345,   312,    84,    76,    77,    78,    62,
      62,    62,    82,    62,    61,   338,    64,    80,    62,    64,
      52,    64,    62,   347,    62,   122,    82,   215,     3,     4,
       5,     6,   299,     8,     9,    95,   282,   243,   245,   362,
     244,   246,    63,    30,   247,    76,    83,   347,   273,   268,
     187,   269,   122,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   170,    49,    50,    51,   253,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    70,   143,    32,
     187,    -1,    67,    68,    69,    70,    71,    72,    -1,    -1,
     170,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83,    84,
       3,     4,     5,     6,    -1,     8,     9,   187,    -1,    -1,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
       3,     4,     5,     6,    81,     8,     9,    -1,    -1,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      -1,     3,     4,     5,     6,    61,     8,     9,    -1,    82,
      83,    67,    68,    69,    70,    71,    72,    -1,     3,     4,
       5,     6,    61,     8,     9,    -1,    -1,    83,    67,    68,
      69,    70,    71,    72,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    82,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    -1,     3,     4,     5,     6,    61,     8,     9,    64,
      82,    -1,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    62,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    84,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    83,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   111,   112,   113,   114,   117,   118,   119,   120,   130,
     131,   134,   170,   171,   172,   173,    82,     3,    61,    68,
     115,   116,   135,   136,   137,   138,   139,   142,   114,   114,
       3,    83,   121,   122,   121,   122,   114,   172,     0,   137,
     134,   142,   143,    66,    82,    83,   111,   113,   162,   163,
     165,    81,    61,    63,   140,   138,   122,   118,   124,   125,
     126,   127,   134,   122,   132,   133,   139,    62,   134,   142,
     116,   135,     3,     4,     5,     6,     8,     9,    49,    50,
      51,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      67,    68,    69,    70,    71,    72,    82,    83,    84,    86,
      87,    92,    93,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   111,   155,
     156,   157,   158,   160,   161,   164,   166,   167,   168,   169,
     111,   162,     3,    83,   107,   153,    64,    92,   106,   110,
      62,   113,   114,   139,   141,   144,   145,   146,   147,   148,
     124,   127,    84,   123,   125,    80,   128,   129,   135,   137,
     127,   132,    66,   123,    81,    80,    92,    93,    61,    92,
      92,   110,    80,    61,    61,    61,   155,    61,     3,    82,
      82,    82,   109,   109,    95,    95,    95,    95,    95,    95,
       7,     8,     9,    61,    63,    65,    89,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    81,   127,   149,
      68,    73,    74,    69,    70,    10,    11,    12,    13,    75,
      76,    14,    15,    67,    77,    78,    16,    17,    79,    66,
      82,    84,   159,   160,   164,   160,   153,   154,    64,    61,
      63,   135,   140,   142,   150,   151,   152,   141,    66,    66,
     141,   123,   110,    66,    82,    80,    66,   123,   123,   133,
     110,   155,   149,    80,   155,   109,   109,   109,    54,   166,
      82,    82,    62,     3,    88,   109,    88,    62,    90,    91,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,    61,   142,   151,    62,    94,    95,    95,    95,
      96,    96,    97,    97,    98,    98,    98,    98,    99,    99,
     100,   101,   102,   103,   104,   109,   107,   159,    66,    84,
     151,    64,   110,   141,   144,   152,    63,   140,    48,   146,
     148,   129,   110,   123,    94,   155,    62,    62,    62,    61,
     166,    64,    66,    90,    95,    80,    84,   153,    62,    64,
     141,    64,   110,   141,   144,   155,   155,   155,   109,    62,
     109,   107,   106,    64,   141,    52,    62,   155,    62,   155,
      82,   155
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    90,    91,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    94,    95,    95,    96,    96,    96,    96,    97,    97,
      97,    98,    98,    98,    99,    99,    99,    99,    99,   100,
     100,   100,   101,   101,   102,   102,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   108,   108,   109,   110,
     111,   111,   112,   113,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   117,   117,   117,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   119,   119,   120,   120,   121,   122,   123,   124,
     124,   125,   126,   127,   127,   127,   127,   128,   128,   129,
     129,   129,   130,   130,   130,   130,   130,   131,   132,   132,
     133,   133,   134,   134,   135,   136,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   139,   140,   141,   142,   142,
     142,   142,   143,   143,   144,   144,   145,   145,   146,   146,
     146,   147,   147,   148,   149,   149,   150,   151,   151,   151,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   153,   154,   154,   155,   155,   155,   155,   155,   155,
     156,   156,   156,   157,   157,   158,   159,   160,   160,   161,
     161,   162,   162,   163,   164,   165,   165,   166,   166,   167,
     167,   167,   168,   168,   168,   168,   169,   169,   169,   169,
     169,   170,   170,   171,   172,   172,   173,   173
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     1,     1,     1,     3,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       2,     3,     1,     1,     1,     2,     1,     2,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     4,     2,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     2,     1,     2,     1,     1,     3,     1,
       2,     3,     5,     4,     6,     5,     2,     1,     1,     3,
       1,     3,     1,     1,     1,     3,     2,     1,     1,     3,
       4,     3,     4,     4,     3,     1,     1,     1,     1,     2,
       2,     3,     1,     2,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     1,     2,     1,     1,     1,     2,
       3,     2,     3,     3,     4,     2,     3,     3,     4,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     3,     1,     1,     1,     2,     1,
       1,     2,     3,     1,     1,     1,     2,     1,     2,     5,
       7,     5,     5,     7,     6,     7,     3,     2,     2,     2,
       3,     1,     2,     1,     1,     1,     4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 50 "spec/parser_spec.y"
                                                        { IdentifierPrimary(yylval.id); }
#line 1838 "src/yy/y.tab.c"
    break;

  case 3:
#line 51 "spec/parser_spec.y"
                                                                { ConstantPrimary(yylval.val, yylval.val_type); }
#line 1844 "src/yy/y.tab.c"
    break;

  case 4:
#line 52 "spec/parser_spec.y"
                                                { StringPrimary(yylval.strlit); }
#line 1850 "src/yy/y.tab.c"
    break;

  case 7:
#line 58 "spec/parser_spec.y"
                                                                                                                                                                { ArrayRefExpr(); }
#line 1856 "src/yy/y.tab.c"
    break;

  case 8:
#line 59 "spec/parser_spec.y"
                                                                                                                                                                { FunctionCallExpr(); }
#line 1862 "src/yy/y.tab.c"
    break;

  case 9:
#line 60 "spec/parser_spec.y"
                                                                                { FunctionCallExpr(); }
#line 1868 "src/yy/y.tab.c"
    break;

  case 10:
#line 61 "spec/parser_spec.y"
                                                                                                                                                                        { FieldRefExpr(yylval.id); }
#line 1874 "src/yy/y.tab.c"
    break;

  case 11:
#line 62 "spec/parser_spec.y"
                                                                                                                                                                { PtrRefExpr(yylval.id); }
#line 1880 "src/yy/y.tab.c"
    break;

  case 12:
#line 63 "spec/parser_spec.y"
                                                                                                                                                                                                        { IncDecExpr(POST_INC_EXPR); }
#line 1886 "src/yy/y.tab.c"
    break;

  case 13:
#line 64 "spec/parser_spec.y"
                                                                                                                                                                                                { IncDecExpr(POST_DEC_EXPR); }
#line 1892 "src/yy/y.tab.c"
    break;

  case 14:
#line 68 "spec/parser_spec.y"
                     { }
#line 1898 "src/yy/y.tab.c"
    break;

  case 15:
#line 72 "spec/parser_spec.y"
              { FunctionArgsOpen(); }
#line 1904 "src/yy/y.tab.c"
    break;

  case 16:
#line 76 "spec/parser_spec.y"
              { FunctionArgsClose(); }
#line 1910 "src/yy/y.tab.c"
    break;

  case 17:
#line 80 "spec/parser_spec.y"
                                                                                                                                                        { FunctionArg(); }
#line 1916 "src/yy/y.tab.c"
    break;

  case 18:
#line 81 "spec/parser_spec.y"
                                                                { FunctionArg(); }
#line 1922 "src/yy/y.tab.c"
    break;

  case 20:
#line 86 "spec/parser_spec.y"
                                        { IncDecExpr(PRE_INC_EXPR); }
#line 1928 "src/yy/y.tab.c"
    break;

  case 21:
#line 87 "spec/parser_spec.y"
                                        { IncDecExpr(PRE_DEC_EXPR); }
#line 1934 "src/yy/y.tab.c"
    break;

  case 22:
#line 88 "spec/parser_spec.y"
                                                        { AddressExpr(); }
#line 1940 "src/yy/y.tab.c"
    break;

  case 23:
#line 89 "spec/parser_spec.y"
                                                        { DerefExpr(); }
#line 1946 "src/yy/y.tab.c"
    break;

  case 24:
#line 90 "spec/parser_spec.y"
                                                        { UnaryExpr(UNARY_PLUS_EXPR); }
#line 1952 "src/yy/y.tab.c"
    break;

  case 25:
#line 91 "spec/parser_spec.y"
                                                        { UnaryExpr(UNARY_MINUS_EXPR); }
#line 1958 "src/yy/y.tab.c"
    break;

  case 26:
#line 92 "spec/parser_spec.y"
                                                        { BitNegExpr(); }
#line 1964 "src/yy/y.tab.c"
    break;

  case 27:
#line 93 "spec/parser_spec.y"
                                                        { LogNegExpr(); }
#line 1970 "src/yy/y.tab.c"
    break;

  case 28:
#line 94 "spec/parser_spec.y"
                                        { SizeofExpr(); }
#line 1976 "src/yy/y.tab.c"
    break;

  case 29:
#line 95 "spec/parser_spec.y"
                                                        { SizeofTypeExpr(); }
#line 1982 "src/yy/y.tab.c"
    break;

  case 30:
#line 99 "spec/parser_spec.y"
              { TypeOpen(); }
#line 1988 "src/yy/y.tab.c"
    break;

  case 31:
#line 103 "spec/parser_spec.y"
              { TypeClose(); }
#line 1994 "src/yy/y.tab.c"
    break;

  case 33:
#line 108 "spec/parser_spec.y"
                                                                { CastExpr(); }
#line 2000 "src/yy/y.tab.c"
    break;

  case 35:
#line 113 "spec/parser_spec.y"
                                                        { MulExpr(); }
#line 2006 "src/yy/y.tab.c"
    break;

  case 36:
#line 114 "spec/parser_spec.y"
                                                        { DivExpr(); }
#line 2012 "src/yy/y.tab.c"
    break;

  case 37:
#line 115 "spec/parser_spec.y"
                                                        { ModExpr(); }
#line 2018 "src/yy/y.tab.c"
    break;

  case 39:
#line 120 "spec/parser_spec.y"
                                                                { AddExpr(); }
#line 2024 "src/yy/y.tab.c"
    break;

  case 40:
#line 121 "spec/parser_spec.y"
                                                                { SubExpr(); }
#line 2030 "src/yy/y.tab.c"
    break;

  case 42:
#line 126 "spec/parser_spec.y"
                                                        { BitExpr(BIT_LEFT_EXPR); }
#line 2036 "src/yy/y.tab.c"
    break;

  case 43:
#line 127 "spec/parser_spec.y"
                                                        { BitExpr(BIT_RIGHT_EXPR); }
#line 2042 "src/yy/y.tab.c"
    break;

  case 45:
#line 132 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_LT_EXPR); }
#line 2048 "src/yy/y.tab.c"
    break;

  case 46:
#line 133 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_GT_EXPR); }
#line 2054 "src/yy/y.tab.c"
    break;

  case 47:
#line 134 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_LE_EXPR); }
#line 2060 "src/yy/y.tab.c"
    break;

  case 48:
#line 135 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_GE_EXPR); }
#line 2066 "src/yy/y.tab.c"
    break;

  case 50:
#line 140 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_EQ_EXPR); }
#line 2072 "src/yy/y.tab.c"
    break;

  case 51:
#line 141 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_NE_EXPR); }
#line 2078 "src/yy/y.tab.c"
    break;

  case 53:
#line 146 "spec/parser_spec.y"
                                                 { BitExpr(BIT_AND_EXPR); }
#line 2084 "src/yy/y.tab.c"
    break;

  case 55:
#line 151 "spec/parser_spec.y"
                                                     { BitExpr(BIT_XOR_EXPR); }
#line 2090 "src/yy/y.tab.c"
    break;

  case 57:
#line 156 "spec/parser_spec.y"
                                                              { BitExpr(BIT_OR_EXPR); }
#line 2096 "src/yy/y.tab.c"
    break;

  case 59:
#line 161 "spec/parser_spec.y"
                                                                { LogExpr(LOG_AND_EXPR); }
#line 2102 "src/yy/y.tab.c"
    break;

  case 61:
#line 166 "spec/parser_spec.y"
                                                                { LogExpr(LOG_OR_EXPR); }
#line 2108 "src/yy/y.tab.c"
    break;

  case 63:
#line 171 "spec/parser_spec.y"
                                                                          { CondExpr(); }
#line 2114 "src/yy/y.tab.c"
    break;

  case 65:
#line 176 "spec/parser_spec.y"
                                                                                        { BasicAssignExpr(); }
#line 2120 "src/yy/y.tab.c"
    break;

  case 66:
#line 177 "spec/parser_spec.y"
                                                                        { MulAssignExpr(); }
#line 2126 "src/yy/y.tab.c"
    break;

  case 67:
#line 178 "spec/parser_spec.y"
                                                                        { DivAssignExpr(); }
#line 2132 "src/yy/y.tab.c"
    break;

  case 68:
#line 179 "spec/parser_spec.y"
                                                                        { ModAssignExpr(); }
#line 2138 "src/yy/y.tab.c"
    break;

  case 69:
#line 180 "spec/parser_spec.y"
                                                                        { AddAssignExpr(); }
#line 2144 "src/yy/y.tab.c"
    break;

  case 70:
#line 181 "spec/parser_spec.y"
                                                                        { SubAssignExpr(); }
#line 2150 "src/yy/y.tab.c"
    break;

  case 71:
#line 182 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_LEFT_ASSIGN_EXPR); }
#line 2156 "src/yy/y.tab.c"
    break;

  case 72:
#line 183 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_RIGHT_ASSIGN_EXPR); }
#line 2162 "src/yy/y.tab.c"
    break;

  case 73:
#line 184 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_AND_ASSIGN_EXPR); }
#line 2168 "src/yy/y.tab.c"
    break;

  case 74:
#line 185 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_XOR_ASSIGN_EXPR); }
#line 2174 "src/yy/y.tab.c"
    break;

  case 75:
#line 186 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_OR_ASSIGN_EXPR); }
#line 2180 "src/yy/y.tab.c"
    break;

  case 76:
#line 190 "spec/parser_spec.y"
                                { CommaExprOpen(); }
#line 2186 "src/yy/y.tab.c"
    break;

  case 77:
#line 191 "spec/parser_spec.y"
                                                   { CommaExpr(); }
#line 2192 "src/yy/y.tab.c"
    break;

  case 78:
#line 195 "spec/parser_spec.y"
                         { FullExpr(); }
#line 2198 "src/yy/y.tab.c"
    break;

  case 79:
#line 199 "spec/parser_spec.y"
                                 { ConstExpression(); }
#line 2204 "src/yy/y.tab.c"
    break;

  case 80:
#line 203 "spec/parser_spec.y"
                                       { Declaration(); }
#line 2210 "src/yy/y.tab.c"
    break;

  case 81:
#line 204 "spec/parser_spec.y"
                                                               { Declaration(); }
#line 2216 "src/yy/y.tab.c"
    break;

  case 82:
#line 208 "spec/parser_spec.y"
                                 { RedeclarationSpecifiers(); }
#line 2222 "src/yy/y.tab.c"
    break;

  case 83:
#line 212 "spec/parser_spec.y"
                                 { FullDeclarationSpecifiers(); }
#line 2228 "src/yy/y.tab.c"
    break;

  case 92:
#line 230 "spec/parser_spec.y"
                          { NotFunctionDefinition(); }
#line 2234 "src/yy/y.tab.c"
    break;

  case 93:
#line 231 "spec/parser_spec.y"
                                      { NotFunctionDefinition(); }
#line 2240 "src/yy/y.tab.c"
    break;

  case 94:
#line 235 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(TYPEDEF); }
#line 2246 "src/yy/y.tab.c"
    break;

  case 95:
#line 236 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(EXTERN); }
#line 2252 "src/yy/y.tab.c"
    break;

  case 96:
#line 237 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(STATIC); }
#line 2258 "src/yy/y.tab.c"
    break;

  case 97:
#line 238 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(AUTO); }
#line 2264 "src/yy/y.tab.c"
    break;

  case 98:
#line 239 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(REGISTER); }
#line 2270 "src/yy/y.tab.c"
    break;

  case 99:
#line 243 "spec/parser_spec.y"
                                        { TypeSpecifierRef(VOID); }
#line 2276 "src/yy/y.tab.c"
    break;

  case 100:
#line 244 "spec/parser_spec.y"
                                        { TypeSpecifierRef(CHAR); }
#line 2282 "src/yy/y.tab.c"
    break;

  case 101:
#line 245 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SHORT); }
#line 2288 "src/yy/y.tab.c"
    break;

  case 102:
#line 246 "spec/parser_spec.y"
                                        { TypeSpecifierRef(INT); }
#line 2294 "src/yy/y.tab.c"
    break;

  case 103:
#line 247 "spec/parser_spec.y"
                                        { TypeSpecifierRef(LONG); }
#line 2300 "src/yy/y.tab.c"
    break;

  case 104:
#line 248 "spec/parser_spec.y"
                                        { TypeSpecifierRef(FLOAT); }
#line 2306 "src/yy/y.tab.c"
    break;

  case 105:
#line 249 "spec/parser_spec.y"
                                        { TypeSpecifierRef(DOUBLE); }
#line 2312 "src/yy/y.tab.c"
    break;

  case 106:
#line 250 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SIGNED); }
#line 2318 "src/yy/y.tab.c"
    break;

  case 107:
#line 251 "spec/parser_spec.y"
                                { TypeSpecifierRef(UNSIGNED); }
#line 2324 "src/yy/y.tab.c"
    break;

  case 110:
#line 254 "spec/parser_spec.y"
                                { IdentifierName(yylval.id); TypedefName(); }
#line 2330 "src/yy/y.tab.c"
    break;

  case 111:
#line 258 "spec/parser_spec.y"
                                                                                      { TagDefined(); }
#line 2336 "src/yy/y.tab.c"
    break;

  case 112:
#line 259 "spec/parser_spec.y"
                                                                             { TagDefined(); }
#line 2342 "src/yy/y.tab.c"
    break;

  case 113:
#line 260 "spec/parser_spec.y"
                                   { TagDeclared(); }
#line 2348 "src/yy/y.tab.c"
    break;

  case 114:
#line 264 "spec/parser_spec.y"
                        { TagTypeRef(TAG_STRUCT); }
#line 2354 "src/yy/y.tab.c"
    break;

  case 115:
#line 265 "spec/parser_spec.y"
                                { TagTypeRef(TAG_UNION); }
#line 2360 "src/yy/y.tab.c"
    break;

  case 116:
#line 269 "spec/parser_spec.y"
                     { IdentifierName(yylval.id); }
#line 2366 "src/yy/y.tab.c"
    break;

  case 117:
#line 273 "spec/parser_spec.y"
                { TagDefOpen(); }
#line 2372 "src/yy/y.tab.c"
    break;

  case 118:
#line 277 "spec/parser_spec.y"
                { }
#line 2378 "src/yy/y.tab.c"
    break;

  case 121:
#line 286 "spec/parser_spec.y"
                                                                   { Declaration(); }
#line 2384 "src/yy/y.tab.c"
    break;

  case 122:
#line 290 "spec/parser_spec.y"
                                   { FullDeclarationSpecifiers(); }
#line 2390 "src/yy/y.tab.c"
    break;

  case 132:
#line 312 "spec/parser_spec.y"
                                                                   { TagDefined(); }
#line 2396 "src/yy/y.tab.c"
    break;

  case 133:
#line 313 "spec/parser_spec.y"
                                                          { TagDefined(); }
#line 2402 "src/yy/y.tab.c"
    break;

  case 134:
#line 314 "spec/parser_spec.y"
                                                                       { TagDefined(); }
#line 2408 "src/yy/y.tab.c"
    break;

  case 135:
#line 315 "spec/parser_spec.y"
                                                              { TagDefined(); }
#line 2414 "src/yy/y.tab.c"
    break;

  case 136:
#line 316 "spec/parser_spec.y"
                        { TagDeclared(); }
#line 2420 "src/yy/y.tab.c"
    break;

  case 137:
#line 320 "spec/parser_spec.y"
                { TagTypeRef(TAG_ENUM); }
#line 2426 "src/yy/y.tab.c"
    break;

  case 140:
#line 329 "spec/parser_spec.y"
                          { EnumeratorDefault(); }
#line 2432 "src/yy/y.tab.c"
    break;

  case 141:
#line 330 "spec/parser_spec.y"
                                                  { EnumeratorCustom(); }
#line 2438 "src/yy/y.tab.c"
    break;

  case 142:
#line 334 "spec/parser_spec.y"
                                        { TypeQualifierRef(CONST); }
#line 2444 "src/yy/y.tab.c"
    break;

  case 143:
#line 335 "spec/parser_spec.y"
                                { TypeQualifierRef(VOLATILE); }
#line 2450 "src/yy/y.tab.c"
    break;

  case 144:
#line 339 "spec/parser_spec.y"
                     { Declarator(); }
#line 2456 "src/yy/y.tab.c"
    break;

  case 145:
#line 343 "spec/parser_spec.y"
                                     { DeclaratorInitialized(); }
#line 2462 "src/yy/y.tab.c"
    break;

  case 146:
#line 347 "spec/parser_spec.y"
                                    { NestedDeclarator(); }
#line 2468 "src/yy/y.tab.c"
    break;

  case 149:
#line 353 "spec/parser_spec.y"
                             { }
#line 2474 "src/yy/y.tab.c"
    break;

  case 150:
#line 354 "spec/parser_spec.y"
                                                        { ArrayLengthDeclarator(); }
#line 2480 "src/yy/y.tab.c"
    break;

  case 151:
#line 355 "spec/parser_spec.y"
                                    { ArrayVariableDeclarator(); }
#line 2486 "src/yy/y.tab.c"
    break;

  case 152:
#line 356 "spec/parser_spec.y"
                                                                                           { FunctionDeclarator(); }
#line 2492 "src/yy/y.tab.c"
    break;

  case 153:
#line 357 "spec/parser_spec.y"
                                                                                       { FunctionDeclarator(); }
#line 2498 "src/yy/y.tab.c"
    break;

  case 154:
#line 358 "spec/parser_spec.y"
                                                                       { FunctionDeclarator(); }
#line 2504 "src/yy/y.tab.c"
    break;

  case 155:
#line 362 "spec/parser_spec.y"
                     { IdentifierName(yyval.id); }
#line 2510 "src/yy/y.tab.c"
    break;

  case 156:
#line 366 "spec/parser_spec.y"
              { FunctionParamsOpen(); }
#line 2516 "src/yy/y.tab.c"
    break;

  case 157:
#line 370 "spec/parser_spec.y"
                { FunctionParamsClose(); }
#line 2522 "src/yy/y.tab.c"
    break;

  case 158:
#line 374 "spec/parser_spec.y"
              { PointerOpen(); }
#line 2528 "src/yy/y.tab.c"
    break;

  case 159:
#line 375 "spec/parser_spec.y"
                                  { PointerQualifierOpen();}
#line 2534 "src/yy/y.tab.c"
    break;

  case 160:
#line 376 "spec/parser_spec.y"
                      { Pointer(); }
#line 2540 "src/yy/y.tab.c"
    break;

  case 161:
#line 377 "spec/parser_spec.y"
                                          { PointerQualifier(); }
#line 2546 "src/yy/y.tab.c"
    break;

  case 165:
#line 387 "spec/parser_spec.y"
                                      { Ellipsis(); }
#line 2552 "src/yy/y.tab.c"
    break;

  case 168:
#line 396 "spec/parser_spec.y"
                                                      { Declaration(); }
#line 2558 "src/yy/y.tab.c"
    break;

  case 169:
#line 397 "spec/parser_spec.y"
                                                               { Declaration(); }
#line 2564 "src/yy/y.tab.c"
    break;

  case 170:
#line 398 "spec/parser_spec.y"
                                      { Declaration(); }
#line 2570 "src/yy/y.tab.c"
    break;

  case 171:
#line 402 "spec/parser_spec.y"
                              { Declaration(); }
#line 2576 "src/yy/y.tab.c"
    break;

  case 172:
#line 403 "spec/parser_spec.y"
                                                  { Declaration(); }
#line 2582 "src/yy/y.tab.c"
    break;

  case 173:
#line 407 "spec/parser_spec.y"
                          { Declarator(); }
#line 2588 "src/yy/y.tab.c"
    break;

  case 174:
#line 411 "spec/parser_spec.y"
                                   { /*TypeName();*/ }
#line 2594 "src/yy/y.tab.c"
    break;

  case 175:
#line 412 "spec/parser_spec.y"
                                                       { /*TypeName();*/ }
#line 2600 "src/yy/y.tab.c"
    break;

  case 176:
#line 416 "spec/parser_spec.y"
                              { AbstractDeclarator(); }
#line 2606 "src/yy/y.tab.c"
    break;

  case 177:
#line 420 "spec/parser_spec.y"
                  { NestedDeclarator(); }
#line 2612 "src/yy/y.tab.c"
    break;

  case 179:
#line 422 "spec/parser_spec.y"
                                             { NestedDeclarator(); }
#line 2618 "src/yy/y.tab.c"
    break;

  case 180:
#line 426 "spec/parser_spec.y"
                                      { }
#line 2624 "src/yy/y.tab.c"
    break;

  case 181:
#line 427 "spec/parser_spec.y"
                  { ArrayVariableDeclarator(); }
#line 2630 "src/yy/y.tab.c"
    break;

  case 182:
#line 428 "spec/parser_spec.y"
                                       { ArrayLengthDeclarator(); }
#line 2636 "src/yy/y.tab.c"
    break;

  case 183:
#line 429 "spec/parser_spec.y"
                                              { ArrayVariableDeclarator(); }
#line 2642 "src/yy/y.tab.c"
    break;

  case 184:
#line 430 "spec/parser_spec.y"
                                                                  { ArrayLengthDeclarator(); }
#line 2648 "src/yy/y.tab.c"
    break;

  case 185:
#line 431 "spec/parser_spec.y"
                                                     { FunctionDeclarator(); }
#line 2654 "src/yy/y.tab.c"
    break;

  case 186:
#line 432 "spec/parser_spec.y"
                                                                         { FunctionDeclarator(); }
#line 2660 "src/yy/y.tab.c"
    break;

  case 187:
#line 433 "spec/parser_spec.y"
                                                                                { FunctionDeclarator(); }
#line 2666 "src/yy/y.tab.c"
    break;

  case 188:
#line 434 "spec/parser_spec.y"
                                                                                                    { FunctionDeclarator(); }
#line 2672 "src/yy/y.tab.c"
    break;

  case 205:
#line 469 "spec/parser_spec.y"
              { BlockOpen(); }
#line 2678 "src/yy/y.tab.c"
    break;

  case 206:
#line 473 "spec/parser_spec.y"
              { BlockClose(); }
#line 2684 "src/yy/y.tab.c"
    break;

  case 213:
#line 492 "spec/parser_spec.y"
              { FuncBodyOpen(); }
#line 2690 "src/yy/y.tab.c"
    break;

  case 214:
#line 496 "spec/parser_spec.y"
              { FuncBodyClose(); }
#line 2696 "src/yy/y.tab.c"
    break;

  case 217:
#line 505 "spec/parser_spec.y"
                                                                { EmptyStmt(); }
#line 2702 "src/yy/y.tab.c"
    break;

  case 218:
#line 506 "spec/parser_spec.y"
                                { ExpressionStmt(); }
#line 2708 "src/yy/y.tab.c"
    break;

  case 233:
#line 536 "spec/parser_spec.y"
                               { TranslationUnit(); }
#line 2714 "src/yy/y.tab.c"
    break;

  case 236:
#line 545 "spec/parser_spec.y"
                                                                                 { FunctionDefinition(); }
#line 2720 "src/yy/y.tab.c"
    break;

  case 237:
#line 546 "spec/parser_spec.y"
                                                                { FunctionDefinition(); }
#line 2726 "src/yy/y.tab.c"
    break;


#line 2730 "src/yy/y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 549 "spec/parser_spec.y"

#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
