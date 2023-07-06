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

	#include "symtab/obj.h"
	#include "symtab/struct.h"

	#include "decl/declarations.h"
	#include "decl/specifiers.h"
	#include "decl/declarators.h"
	#include "decl/indirections.h"
	#include "decl/initializer.h"

	#include "stmt/fold.h"
	#include "stmt/literals.h"
	#include "stmt/stmt.h"
	#include "stmt/tree.h"

	#include "stmt/expr/expr.h"
	#include "stmt/expr/arithm.h"
	#include "stmt/expr/bitwise.h"
	#include "stmt/expr/logic.h"
	#include "stmt/expr/postfix.h"
	#include "stmt/expr/prefix.h"
	#include "stmt/expr/primary.h"

	#include "stmt/flow/iteration.h"
	#include "stmt/flow/jump.h"
	#include "stmt/flow/selection.h"

	extern int yylex (void);
	void yyerror(char* s);

#line 103 "src/yy/y.tab.c"

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
    NQ_OP = 270,
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
#line 34 "spec/parser_spec.y"

	long  val;
	int 	val_type;
	char* id;
	char* strlit;

#line 223 "src/yy/y.tab.c"

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
#define YYFINAL  59
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1032

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  254
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  410

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
       0,    56,    56,    57,    58,    59,    63,    64,    65,    66,
      67,    68,    69,    70,    74,    78,    82,    86,    87,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     105,   109,   113,   114,   118,   119,   120,   121,   125,   126,
     127,   131,   132,   133,   137,   138,   139,   140,   141,   145,
     146,   147,   151,   152,   156,   157,   161,   162,   166,   167,
     171,   172,   176,   177,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   196,   197,   201,   205,
     209,   210,   214,   218,   222,   223,   224,   225,   226,   227,
     231,   232,   236,   237,   241,   242,   243,   244,   245,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   264,   265,   266,   270,   271,   275,   279,   283,   287,
     288,   292,   296,   300,   301,   302,   303,   307,   308,   312,
     313,   314,   318,   319,   320,   321,   322,   326,   330,   331,
     335,   336,   340,   341,   345,   349,   353,   357,   358,   362,
     363,   364,   365,   366,   367,   368,   372,   376,   380,   384,
     385,   386,   387,   391,   392,   396,   397,   401,   402,   406,
     407,   408,   412,   413,   417,   421,   422,   426,   430,   431,
     432,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     448,   449,   450,   454,   458,   462,   463,   467,   468,   469,
     470,   471,   475,   479,   483,   487,   488,   489,   493,   494,
     498,   502,   506,   507,   511,   512,   513,   517,   518,   522,
     526,   530,   531,   535,   536,   540,   544,   548,   552,   553,
     554,   558,   562,   566,   570,   574,   578,   579,   584,   585,
     586,   587,   591,   592,   593,   594,   595,   599,   600,   604,
     605,   609,   610,   614,   615
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF_", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NQ_OP", "AND_OP", "OR_OP",
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
  "conditional_expression", "assignment_expression", "expression_nested",
  "expression", "constant_expression", "declaration",
  "redeclaration_specifiers", "full_declaration_specifiers",
  "declaration_specifiers_nested", "init_declarator_list",
  "init_declarator", "storage_class_specifier", "type_specifier",
  "struct_or_union_specifier", "struct_or_union", "tag_name",
  "tag_def_open", "tag_def_close", "struct_declaration_list",
  "struct_declaration", "specifier_qualifier_list",
  "specifier_qualifier_list_nested", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enum", "enumerator_list",
  "enumerator", "type_qualifier", "declarator", "declarator_initialized",
  "function_declarator", "declarator_nested", "direct_declarator",
  "declarator_name", "function_params_open", "function_params_close",
  "pointer", "type_qualifier_list", "parameter_type_list",
  "parameter_list", "parameter_declaration", "identifier_list",
  "function_param_name", "type_name", "abstract_declarator",
  "abstract_declarator_nested", "direct_abstract_declarator",
  "initializer", "initializer_open", "initializer_close",
  "initializer_list", "statement", "label", "case_label", "default_label",
  "labelation", "compound_statement", "block_open", "block_close", "block",
  "block_item", "func_body", "func_body_open", "func_body_close",
  "declaration_list", "expression_statement", "if_open", "else_open",
  "switch_open", "selection_statement", "while_open", "do_open",
  "for_open", "control_expression", "for_declaration", "for_expression",
  "iteration_statement", "jump_statement", "rec_translation_unit",
  "translation_unit", "external_declaration", "function_definition", YY_NULLPTR
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

#define YYPACT_NINF (-324)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-203)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     985,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,
    -324,  -324,   -52,    26,   -33,   985,   985,  -324,    21,  -324,
      21,   985,   985,   108,  -324,  -324,  -324,  -324,    26,   103,
     112,  -324,  -324,    59,   873,   121,     1,  -324,    32,  -324,
    -324,  -324,  -324,    93,   904,    93,   176,  -324,  -324,  -324,
     127,  -324,  -324,   103,    26,  -324,   297,  -324,  -324,    26,
    -324,   386,   873,  -324,   338,   824,     1,   904,   904,   853,
    -324,    34,  -324,   904,   176,   -28,  -324,   117,  -324,  -324,
    -324,  -324,   125,  -324,  -324,  -324,   765,   777,   777,   765,
     765,   765,   765,   765,   765,   765,  -324,  -324,   130,   455,
     904,  -324,   131,    -4,   139,    47,   230,   159,   156,   168,
     221,     9,  -324,  -324,  -324,   297,   174,   765,  -324,  -324,
    -324,  -324,  -324,  -324,   245,   182,   190,   613,  -324,  -324,
    -324,  -324,   191,   192,  -324,  -324,   200,   201,   203,  -324,
    -324,   456,   204,   526,  -324,  -324,   228,   229,  -324,   231,
     596,   243,  -324,  -324,  -324,  -324,  -324,  -324,  -324,   249,
    -324,    58,  -324,  -324,  -324,   252,   250,  -324,    30,  -324,
     853,  -324,  -324,  -324,  -324,   765,   119,  -324,   237,  -324,
    -324,    43,    17,  -324,   765,  -324,   904,   765,  -324,  -324,
     257,  -324,  -324,  -324,  -324,  -324,  -324,   318,  -324,  -324,
    -324,   765,   318,   632,   765,   765,   765,   765,   765,   765,
     765,   765,   765,   765,   765,   175,   260,   765,   765,   765,
     765,   765,   765,   765,   765,   765,   765,   765,   765,   765,
     765,   765,   765,   765,   765,   765,  -324,   104,  -324,   241,
    -324,  -324,  -324,   242,   765,  -324,  -324,  -324,  -324,  -324,
    -324,   244,  -324,  -324,   765,   765,   765,   271,   683,  -324,
      58,   728,  -324,   929,    42,  -324,  -324,    36,  -324,   964,
     176,  -324,  -324,  -324,    34,  -324,   765,    17,  -324,  -324,
    -324,  -324,   260,  -324,  -324,  -324,   263,  -324,  -324,  -324,
      54,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,   175,    67,  -324,  -324,   765,  -324,  -324,
    -324,   131,   131,    -4,    -4,   139,   139,   139,   139,    47,
      47,   230,   159,   156,   168,   221,   251,    64,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,   267,   268,   270,   272,  -324,
    -324,   765,   253,   275,  -324,   276,  -324,   252,    36,   753,
     929,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,   765,
    -324,  -324,   765,  -324,  -324,   596,   596,   596,   765,   266,
     765,  -324,  -324,  -324,  -324,   281,  -324,   252,  -324,  -324,
     282,  -324,  -324,   287,   765,   273,  -324,  -324,  -324,   596,
     274,   288,   765,  -324,  -324,   596,   291,  -324,   596,  -324
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     250,   110,    94,    95,    96,    97,    98,   100,   101,   102,
     103,   106,   107,   104,   105,   142,   143,    99,   114,   115,
     137,   252,     0,     0,    83,    84,    86,   108,     0,   109,
       0,    88,   249,     0,   247,   251,    80,   156,     0,   159,
       0,    90,    92,     0,     0,   146,   148,   149,     0,    85,
      87,   116,   117,   113,     0,   136,     0,    89,   248,     1,
       0,   163,   161,   160,     0,    81,     0,   219,   221,     0,
     254,     0,     0,   157,     0,     0,   147,     0,   124,     0,
     119,     0,   122,   126,     0,     0,   138,   140,   150,   164,
     162,    91,   144,     2,     3,     4,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,   193,     6,    19,    32,
       0,    34,    38,    41,    44,    49,    52,    54,    56,    58,
      60,    62,    64,   190,    93,     0,     2,     0,   204,   225,
     227,   231,   232,   233,     0,     0,     0,     0,   223,   210,
     220,    76,    78,     0,   215,   214,     0,     0,     0,   216,
     197,     0,     0,   212,   217,   198,     0,     0,   199,     0,
       0,     0,   200,   201,   222,   253,   152,    32,    79,     0,
     158,   171,    83,   174,   155,     0,   165,   167,     0,   172,
       0,   123,   118,   112,   120,     0,     0,   127,   129,   144,
     125,     0,     0,   133,     0,    28,     0,     0,    20,    21,
       0,    22,    23,    24,    25,    26,    27,     0,    12,    13,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   195,     0,   203,     0,
     243,   244,   245,     0,     0,   224,   205,   206,   207,   211,
     208,     0,   218,   213,     0,     0,     0,     0,   237,   151,
     157,     0,   169,     0,   178,   170,   177,   179,   153,     0,
       0,   154,   111,   130,     0,   121,     0,     0,   132,   135,
     139,   141,     0,     5,    14,    11,     0,    10,    16,     8,
       0,    17,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    65,   157,   178,   176,    31,     0,    35,    36,
      37,    39,    40,    42,    43,    47,    48,    45,    46,    50,
      51,    53,    55,    57,    59,    61,     0,     0,   194,   191,
     242,   246,    77,   209,   234,     0,     0,     0,     0,   236,
     235,   237,     0,     0,   182,     0,   186,     0,   180,     0,
       0,   166,   168,   173,   128,   131,   134,    29,     7,     0,
       9,    33,     0,   196,   192,     0,     0,     0,     0,     0,
     237,   181,   183,   187,   184,     0,   188,     0,    18,    63,
     228,   230,   238,     0,   237,     0,   185,   189,   226,     0,
       0,     0,   237,   229,   239,     0,     0,   241,     0,   240
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -324,  -324,  -324,   142,  -324,    57,  -324,   -20,   265,    70,
     -61,    29,    35,    74,    39,   123,   118,   128,   129,   132,
    -324,   -21,   -62,  -324,   -82,   -96,    14,  -324,     0,   -24,
    -324,   307,  -324,   216,  -324,  -324,   343,    88,   -11,   298,
     -63,   -85,    94,  -324,    90,  -324,  -324,   293,  -187,   208,
     -59,  -324,  -324,   -17,   -39,   -48,   -43,  -160,   -29,  -324,
    -250,  -324,    99,  -324,   101,   183,   157,  -222,  -224,  -106,
    -324,    46,  -324,  -147,  -324,  -324,  -324,  -324,  -324,  -324,
     124,    89,  -324,   312,  -324,   234,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,  -254,  -324,  -323,  -324,  -324,
    -324,  -324,   355,  -324
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   107,   108,   295,   213,   299,   300,   109,   110,   317,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   141,   142,   143,   169,   144,    22,    69,    24,
      40,    41,    25,    26,    27,    28,    53,    54,   183,    79,
      80,    81,    82,   186,   187,    29,    30,    85,    86,    31,
      42,    43,    44,   189,    46,    47,   273,   174,    48,    63,
     175,   176,   177,   178,   179,   226,   275,   276,   277,   124,
     125,   339,   247,   145,   146,   147,   148,   149,   150,   151,
     260,   152,   153,    70,    71,   154,    72,   155,   156,   399,
     157,   158,   159,   160,   161,   345,   351,   352,   162,   163,
      32,    33,    34,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    49,    50,    75,   123,   290,    45,    57,    87,    76,
      62,   346,   347,   267,    21,   278,   184,   200,   281,   246,
      37,    60,   188,   357,    51,   225,   244,   173,   379,    37,
      36,   248,    23,    75,    90,    37,    87,    37,   192,   201,
     202,   203,   204,   205,   206,    37,    21,    92,   353,   -82,
     358,   172,    92,   168,   167,   253,   182,   395,    68,   234,
     235,    37,    73,   123,    74,   230,   231,    93,    94,    95,
      96,   401,    97,    98,   193,   171,   195,   198,   199,   406,
     167,   167,   167,   167,   167,   167,   164,    38,   245,   283,
     358,   353,   170,    38,    39,    38,   280,    73,   291,   359,
     290,   182,    39,   270,    52,   271,   168,   167,    59,   287,
     387,   225,   272,   356,   185,   200,   298,   184,    56,   270,
     369,   271,   236,   237,   393,    99,    39,   182,   313,   296,
     271,   100,   101,   102,   103,   104,   105,   207,   208,   209,
      66,    77,   274,    84,    87,    15,    16,   106,   338,   232,
     233,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   336,   168,   167,   318,   319,   320,   282,
     337,    39,   181,   168,   167,   355,    52,   190,    64,    37,
     288,   289,   344,   344,   344,   284,   349,  -144,   338,    88,
     365,   210,   342,   211,    65,   212,   314,   383,   194,   227,
     386,   285,  -145,  -144,   228,   229,  -145,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   188,   240,   397,   390,   391,
     392,   373,   173,   241,   360,    76,   313,   243,   271,    87,
     261,   274,   263,    39,   238,   239,   242,    61,   249,   172,
     168,   167,   403,    60,  -202,   172,   371,   254,   407,   321,
     322,   409,    83,   385,   250,   168,   167,   323,   324,   349,
      78,    89,   251,   171,   255,   123,   366,   329,   330,   171,
     256,   257,   350,   258,   314,    83,    83,    83,   140,   264,
     265,    83,   266,    78,    78,    78,   344,   167,   349,    78,
      93,    94,    95,    96,   268,    97,    98,   388,   325,   326,
     327,   328,   349,   269,   170,   360,   279,   286,    83,   293,
     349,   294,   316,   340,   341,   348,    78,   368,   259,   375,
     376,   372,   377,   378,   398,   380,   172,   381,   168,   167,
     382,    93,    94,    95,    96,   396,    97,    98,   394,   400,
     405,   389,   167,   408,   297,   402,   404,   370,    99,   332,
     171,   196,   367,   331,   100,   101,   102,   103,   104,   105,
     333,    91,   334,    55,   364,   180,   335,   191,   362,   292,
     106,   363,   315,   374,   165,   343,   262,    58,    83,   126,
      94,    95,    96,     0,    97,    98,    78,     0,     0,    99,
       0,     0,   166,     0,    83,   100,   101,   102,   103,   104,
     105,     0,    78,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,   127,   128,   129,     0,   130,
     131,   132,   133,   134,   135,   136,   137,    99,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,   126,
      94,    95,    96,     0,    97,    98,     0,     0,   138,   139,
     140,     0,     0,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,   127,   128,   129,     0,   130,
     131,   132,   133,   134,   135,   136,   137,    99,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,   126,
      94,    95,    96,     0,    97,    98,   224,     0,   138,   139,
     259,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,   127,   128,   129,     0,   130,
     131,   132,   133,   134,   135,   136,   137,    99,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,    93,
      94,    95,    96,     0,    97,    98,     0,     0,   138,   139,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    96,
       0,    97,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    94,    95,    96,     0,
      97,    98,     0,     0,     0,     0,     0,   129,     0,   130,
     131,   132,   133,   134,   135,   136,   137,    99,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,    99,     0,     0,     0,   138,   139,
     100,   101,   102,   103,   104,   105,    93,    94,    95,    96,
       0,    97,    98,    99,   298,   252,     0,     0,     0,   100,
     101,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    93,    94,    95,    96,     0,    97,    98,     0,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,     0,
     100,   101,   102,   103,   104,   105,    93,    94,    95,    96,
       0,    97,    98,     0,     0,     0,     0,     0,    93,    94,
      95,    96,     0,    97,    98,     0,     0,     0,     0,     0,
      93,    94,    95,    96,     0,    97,    98,     0,     0,    99,
       0,     0,   354,     0,     0,   100,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    99,     0,     0,   384,     0,     0,
     100,   101,   102,   103,   104,   105,    99,    37,     0,     0,
       0,     0,   100,   101,   102,   103,   104,   105,   197,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
       0,     0,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     0,   170,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     0,     0,     0,     0,   182,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,     0,     0,     0,    67,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   361,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20
};

static const yytype_int16 yycheck[] =
{
       0,    25,    26,    46,    66,   192,    23,    31,    56,    48,
      39,   265,   266,   160,     0,   175,    79,    99,   178,   125,
       3,    38,    81,   273,     3,   110,    17,    75,   351,     3,
      82,   127,    32,    76,    63,     3,    84,     3,    66,   100,
     101,   102,   103,   104,   105,     3,    32,    64,   270,    82,
     274,    75,    69,    74,    74,   137,    84,   380,    44,    12,
      13,     3,    61,   125,    63,    69,    70,     3,     4,     5,
       6,   394,     8,     9,    85,    75,    96,    97,    98,   402,
     100,   101,   102,   103,   104,   105,    72,    61,    79,   185,
     314,   313,    62,    61,    68,    61,    66,    61,   194,    63,
     287,    84,    68,    61,    83,    63,   127,   127,     0,    66,
     360,   196,   171,   273,    80,   197,    62,   180,    30,    61,
      66,    63,    75,    76,   378,    61,    68,    84,    61,   211,
      63,    67,    68,    69,    70,    71,    72,     7,     8,     9,
      81,    53,   171,    55,   192,    42,    43,    83,    84,    10,
      11,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   245,   185,   185,   227,   228,   229,   180,
      66,    68,    78,   194,   194,   271,    83,    83,    66,     3,
     191,   192,   264,   265,   266,    66,   268,    66,    84,    62,
     286,    61,   254,    63,    82,    65,   225,   357,    81,    68,
     360,    82,    81,    82,    73,    74,    81,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   284,    67,   387,   375,   376,
     377,   337,   280,    77,   277,   274,    61,    16,    63,   287,
     151,   270,   153,    68,    14,    15,    78,    39,     3,   273,
     271,   271,   399,   270,    80,   279,   317,    66,   405,   230,
     231,   408,    54,   359,    82,   286,   286,   232,   233,   351,
      54,    63,    82,   273,    82,   337,   287,   238,   239,   279,
      80,    80,   268,    80,   313,    77,    78,    79,    84,    61,
      61,    83,    61,    77,    78,    79,   378,   317,   380,    83,
       3,     4,     5,     6,    61,     8,     9,   369,   234,   235,
     236,   237,   394,    64,    62,   358,    66,    80,   110,    62,
     402,     3,    62,    82,    82,    54,   110,    64,    84,    62,
      62,    80,    62,    61,    52,    82,   360,    62,   359,   359,
      64,     3,     4,     5,     6,    64,     8,     9,    82,    62,
      62,   372,   372,    62,   212,    82,    82,   300,    61,   241,
     360,    96,   292,   240,    67,    68,    69,    70,    71,    72,
     242,    64,   243,    30,   284,    77,   244,    84,   279,   196,
      83,   280,   225,   337,    72,   261,   152,    32,   180,     3,
       4,     5,     6,    -1,     8,     9,   180,    -1,    -1,    61,
      -1,    -1,    64,    -1,   196,    67,    68,    69,    70,    71,
      72,    -1,   196,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    82,    83,
      84,    -1,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,    -1,     8,     9,    81,    -1,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    82,    83,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    82,    83,
      67,    68,    69,    70,    71,    72,     3,     4,     5,     6,
      -1,     8,     9,    61,    62,    82,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    61,     3,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    62,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    84,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    83,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   111,   112,   113,   114,   117,   118,   119,   120,   130,
     131,   134,   185,   186,   187,   188,    82,     3,    61,    68,
     115,   116,   135,   136,   137,   138,   139,   140,   143,   114,
     114,     3,    83,   121,   122,   121,   122,   114,   187,     0,
     138,   134,   143,   144,    66,    82,    81,    83,   111,   113,
     168,   169,   171,    61,    63,   141,   139,   122,   118,   124,
     125,   126,   127,   134,   122,   132,   133,   140,    62,   134,
     143,   116,   138,     3,     4,     5,     6,     8,     9,    61,
      67,    68,    69,    70,    71,    72,    83,    86,    87,    92,
      93,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   154,   155,     3,    49,    50,    51,
      53,    54,    55,    56,    57,    58,    59,    60,    82,    83,
      84,   107,   108,   109,   111,   158,   159,   160,   161,   162,
     163,   164,   166,   167,   170,   172,   173,   175,   176,   177,
     178,   179,   183,   184,   111,   168,    64,    92,   106,   110,
      62,   113,   114,   140,   142,   145,   146,   147,   148,   149,
     124,   127,    84,   123,   125,    80,   128,   129,   135,   138,
     127,   132,    66,   123,    81,    92,    93,    61,    92,    92,
     109,    95,    95,    95,    95,    95,    95,     7,     8,     9,
      61,    63,    65,    89,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    81,   126,   150,    68,    73,    74,
      69,    70,    10,    11,    12,    13,    75,    76,    14,    15,
      67,    77,    78,    16,    17,    79,   154,   157,   110,     3,
      82,    82,    82,   109,    66,    82,    80,    80,    80,    84,
     165,   166,   170,   166,    61,    61,    61,   158,    61,    64,
      61,    63,   135,   141,   143,   151,   152,   153,   142,    66,
      66,   142,   123,   110,    66,    82,    80,    66,   123,   123,
     133,   110,   150,    62,     3,    88,   109,    88,    62,    90,
      91,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,    61,   143,   151,    62,    94,    95,    95,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    99,
      99,   100,   101,   102,   103,   104,   109,    66,    84,   156,
      82,    82,   107,   165,   109,   180,   180,   180,    54,   109,
     111,   181,   182,   152,    64,   110,   142,   145,   153,    63,
     141,    48,   147,   149,   129,   110,   123,    94,    64,    66,
      90,    95,    80,   154,   156,    62,    62,    62,    61,   182,
      82,    62,    64,   142,    64,   110,   142,   145,   107,   106,
     158,   158,   158,   180,    82,   182,    64,   142,    52,   174,
      62,   182,    82,   158,    82,    62,   182,   158,    62,   158
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
     133,   133,   134,   134,   135,   136,   137,   138,   138,   139,
     139,   139,   139,   139,   139,   139,   140,   141,   142,   143,
     143,   143,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   148,   148,   149,   150,   150,   151,   152,   152,
     152,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     154,   154,   154,   155,   156,   157,   157,   158,   158,   158,
     158,   158,   159,   160,   161,   162,   162,   162,   163,   163,
     164,   165,   166,   166,   167,   167,   167,   168,   168,   169,
     170,   171,   171,   172,   172,   173,   174,   175,   176,   176,
     176,   177,   178,   179,   180,   181,   182,   182,   183,   183,
     183,   183,   184,   184,   184,   184,   184,   185,   185,   186,
     186,   187,   187,   188,   188
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
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     4,     2,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     2,     1,     2,     1,     1,     3,     1,
       2,     3,     5,     4,     6,     5,     2,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     2,     1,     1,
       3,     4,     3,     4,     4,     3,     1,     1,     1,     1,
       2,     2,     3,     1,     2,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     1,     2,     1,     1,     1,
       2,     3,     2,     3,     3,     4,     2,     3,     3,     4,
       1,     3,     4,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     2,     2,     2,     3,
       1,     1,     1,     2,     1,     1,     1,     2,     3,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     5,     7,
       5,     1,     1,     1,     1,     1,     1,     0,     5,     7,
       9,     8,     3,     2,     2,     2,     3,     1,     2,     1,
       0,     1,     1,     4,     3
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
#line 56 "spec/parser_spec.y"
                                                        { IdentifierPrimary(); }
#line 1863 "src/yy/y.tab.c"
    break;

  case 3:
#line 57 "spec/parser_spec.y"
                                                                { ConstantPrimary(); }
#line 1869 "src/yy/y.tab.c"
    break;

  case 4:
#line 58 "spec/parser_spec.y"
                                                { StringPrimary(); }
#line 1875 "src/yy/y.tab.c"
    break;

  case 7:
#line 64 "spec/parser_spec.y"
                                                                                                                                                                { ArrayRefExpr(); }
#line 1881 "src/yy/y.tab.c"
    break;

  case 8:
#line 65 "spec/parser_spec.y"
                                                                                                                                                                { FunctionCallExpr(); }
#line 1887 "src/yy/y.tab.c"
    break;

  case 9:
#line 66 "spec/parser_spec.y"
                                                                                { FunctionCallExpr(); }
#line 1893 "src/yy/y.tab.c"
    break;

  case 10:
#line 67 "spec/parser_spec.y"
                                                                                                                                                                        { FieldRefExpr(); }
#line 1899 "src/yy/y.tab.c"
    break;

  case 11:
#line 68 "spec/parser_spec.y"
                                                                                                                                                                { PtrRefExpr(); }
#line 1905 "src/yy/y.tab.c"
    break;

  case 12:
#line 69 "spec/parser_spec.y"
                                                                                                                                                                                                        { IncDecExpr(POST_INC_EXPR); }
#line 1911 "src/yy/y.tab.c"
    break;

  case 13:
#line 70 "spec/parser_spec.y"
                                                                                                                                                                                                { IncDecExpr(POST_DEC_EXPR); }
#line 1917 "src/yy/y.tab.c"
    break;

  case 14:
#line 74 "spec/parser_spec.y"
                     { }
#line 1923 "src/yy/y.tab.c"
    break;

  case 15:
#line 78 "spec/parser_spec.y"
              { FunctionArgsOpen(); }
#line 1929 "src/yy/y.tab.c"
    break;

  case 16:
#line 82 "spec/parser_spec.y"
              { FunctionArgsClose(); }
#line 1935 "src/yy/y.tab.c"
    break;

  case 17:
#line 86 "spec/parser_spec.y"
                                                                                                                                                        { FunctionArg(); }
#line 1941 "src/yy/y.tab.c"
    break;

  case 18:
#line 87 "spec/parser_spec.y"
                                                                { FunctionArg(); }
#line 1947 "src/yy/y.tab.c"
    break;

  case 20:
#line 92 "spec/parser_spec.y"
                                        { IncDecExpr(PRE_INC_EXPR); }
#line 1953 "src/yy/y.tab.c"
    break;

  case 21:
#line 93 "spec/parser_spec.y"
                                        { IncDecExpr(PRE_DEC_EXPR); }
#line 1959 "src/yy/y.tab.c"
    break;

  case 22:
#line 94 "spec/parser_spec.y"
                                                        { AddressExpr(); }
#line 1965 "src/yy/y.tab.c"
    break;

  case 23:
#line 95 "spec/parser_spec.y"
                                                        { DerefExpr(); }
#line 1971 "src/yy/y.tab.c"
    break;

  case 24:
#line 96 "spec/parser_spec.y"
                                                        { UnaryExpr(UNARY_PLUS_EXPR); }
#line 1977 "src/yy/y.tab.c"
    break;

  case 25:
#line 97 "spec/parser_spec.y"
                                                        { UnaryExpr(UNARY_MINUS_EXPR); }
#line 1983 "src/yy/y.tab.c"
    break;

  case 26:
#line 98 "spec/parser_spec.y"
                                                        { BitNegExpr(); }
#line 1989 "src/yy/y.tab.c"
    break;

  case 27:
#line 99 "spec/parser_spec.y"
                                                        { LogNegExpr(); }
#line 1995 "src/yy/y.tab.c"
    break;

  case 28:
#line 100 "spec/parser_spec.y"
                                        { SizeofExpr(); }
#line 2001 "src/yy/y.tab.c"
    break;

  case 29:
#line 101 "spec/parser_spec.y"
                                                        { SizeofTypeExpr(); }
#line 2007 "src/yy/y.tab.c"
    break;

  case 30:
#line 105 "spec/parser_spec.y"
              { TypeOpen(); }
#line 2013 "src/yy/y.tab.c"
    break;

  case 31:
#line 109 "spec/parser_spec.y"
              { TypeClose(); }
#line 2019 "src/yy/y.tab.c"
    break;

  case 33:
#line 114 "spec/parser_spec.y"
                                                                { CastExpr(); }
#line 2025 "src/yy/y.tab.c"
    break;

  case 35:
#line 119 "spec/parser_spec.y"
                                                        { MulExpr(MUL_EXPR); }
#line 2031 "src/yy/y.tab.c"
    break;

  case 36:
#line 120 "spec/parser_spec.y"
                                                        { MulExpr(DIV_EXPR); }
#line 2037 "src/yy/y.tab.c"
    break;

  case 37:
#line 121 "spec/parser_spec.y"
                                                        { MulExpr(MOD_EXPR); }
#line 2043 "src/yy/y.tab.c"
    break;

  case 39:
#line 126 "spec/parser_spec.y"
                                                                { AddExpr(); }
#line 2049 "src/yy/y.tab.c"
    break;

  case 40:
#line 127 "spec/parser_spec.y"
                                                                { SubExpr(); }
#line 2055 "src/yy/y.tab.c"
    break;

  case 42:
#line 132 "spec/parser_spec.y"
                                                        { BitExpr(BIT_LEFT_EXPR); }
#line 2061 "src/yy/y.tab.c"
    break;

  case 43:
#line 133 "spec/parser_spec.y"
                                                        { BitExpr(BIT_RIGHT_EXPR); }
#line 2067 "src/yy/y.tab.c"
    break;

  case 45:
#line 138 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_LT_EXPR); }
#line 2073 "src/yy/y.tab.c"
    break;

  case 46:
#line 139 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_GT_EXPR); }
#line 2079 "src/yy/y.tab.c"
    break;

  case 47:
#line 140 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_LE_EXPR); }
#line 2085 "src/yy/y.tab.c"
    break;

  case 48:
#line 141 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_GE_EXPR); }
#line 2091 "src/yy/y.tab.c"
    break;

  case 50:
#line 146 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_EQ_EXPR); }
#line 2097 "src/yy/y.tab.c"
    break;

  case 51:
#line 147 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_NQ_EXPR); }
#line 2103 "src/yy/y.tab.c"
    break;

  case 53:
#line 152 "spec/parser_spec.y"
                                                 { BitExpr(BIT_AND_EXPR); }
#line 2109 "src/yy/y.tab.c"
    break;

  case 55:
#line 157 "spec/parser_spec.y"
                                                     { BitExpr(BIT_XOR_EXPR); }
#line 2115 "src/yy/y.tab.c"
    break;

  case 57:
#line 162 "spec/parser_spec.y"
                                                              { BitExpr(BIT_OR_EXPR); }
#line 2121 "src/yy/y.tab.c"
    break;

  case 59:
#line 167 "spec/parser_spec.y"
                                                                { LogExpr(LOG_AND_EXPR); }
#line 2127 "src/yy/y.tab.c"
    break;

  case 61:
#line 172 "spec/parser_spec.y"
                                                                { LogExpr(LOG_OR_EXPR); }
#line 2133 "src/yy/y.tab.c"
    break;

  case 63:
#line 177 "spec/parser_spec.y"
                                                                          { CondExpr(); }
#line 2139 "src/yy/y.tab.c"
    break;

  case 65:
#line 182 "spec/parser_spec.y"
                                                                                        { BasicAssignExpr(0); }
#line 2145 "src/yy/y.tab.c"
    break;

  case 66:
#line 183 "spec/parser_spec.y"
                                                                        { MulAssignExpr(MUL_ASSIGN_EXPR); }
#line 2151 "src/yy/y.tab.c"
    break;

  case 67:
#line 184 "spec/parser_spec.y"
                                                                        { MulAssignExpr(DIV_ASSIGN_EXPR); }
#line 2157 "src/yy/y.tab.c"
    break;

  case 68:
#line 185 "spec/parser_spec.y"
                                                                        { MulAssignExpr(MOD_ASSIGN_EXPR); }
#line 2163 "src/yy/y.tab.c"
    break;

  case 69:
#line 186 "spec/parser_spec.y"
                                                                        { AddAssignExpr(); }
#line 2169 "src/yy/y.tab.c"
    break;

  case 70:
#line 187 "spec/parser_spec.y"
                                                                        { SubAssignExpr(); }
#line 2175 "src/yy/y.tab.c"
    break;

  case 71:
#line 188 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_LEFT_ASSIGN_EXPR); }
#line 2181 "src/yy/y.tab.c"
    break;

  case 72:
#line 189 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_RIGHT_ASSIGN_EXPR); }
#line 2187 "src/yy/y.tab.c"
    break;

  case 73:
#line 190 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_AND_ASSIGN_EXPR); }
#line 2193 "src/yy/y.tab.c"
    break;

  case 74:
#line 191 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_XOR_ASSIGN_EXPR); }
#line 2199 "src/yy/y.tab.c"
    break;

  case 75:
#line 192 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_OR_ASSIGN_EXPR); }
#line 2205 "src/yy/y.tab.c"
    break;

  case 76:
#line 196 "spec/parser_spec.y"
                                { CommaExprOpen(); }
#line 2211 "src/yy/y.tab.c"
    break;

  case 77:
#line 197 "spec/parser_spec.y"
                                                      { CommaExpr(); }
#line 2217 "src/yy/y.tab.c"
    break;

  case 78:
#line 201 "spec/parser_spec.y"
                            { FullExpr(); }
#line 2223 "src/yy/y.tab.c"
    break;

  case 79:
#line 205 "spec/parser_spec.y"
                                 { ConstExpression(); }
#line 2229 "src/yy/y.tab.c"
    break;

  case 80:
#line 209 "spec/parser_spec.y"
                                       { Declaration(); }
#line 2235 "src/yy/y.tab.c"
    break;

  case 81:
#line 210 "spec/parser_spec.y"
                                                               { Declaration(); }
#line 2241 "src/yy/y.tab.c"
    break;

  case 82:
#line 214 "spec/parser_spec.y"
                                        { RedeclarationSpecifiers(); }
#line 2247 "src/yy/y.tab.c"
    break;

  case 83:
#line 218 "spec/parser_spec.y"
                                        { FullDeclarationSpecifiers(); }
#line 2253 "src/yy/y.tab.c"
    break;

  case 92:
#line 236 "spec/parser_spec.y"
                                                                                                                                        { NotFunctionDefinition(); }
#line 2259 "src/yy/y.tab.c"
    break;

  case 93:
#line 237 "spec/parser_spec.y"
                                                  { NotFunctionDefinition(); FullInitialization(); }
#line 2265 "src/yy/y.tab.c"
    break;

  case 94:
#line 241 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(TYPEDEF); }
#line 2271 "src/yy/y.tab.c"
    break;

  case 95:
#line 242 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(EXTERN); }
#line 2277 "src/yy/y.tab.c"
    break;

  case 96:
#line 243 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(STATIC); }
#line 2283 "src/yy/y.tab.c"
    break;

  case 97:
#line 244 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(AUTO); }
#line 2289 "src/yy/y.tab.c"
    break;

  case 98:
#line 245 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(REGISTER); }
#line 2295 "src/yy/y.tab.c"
    break;

  case 99:
#line 249 "spec/parser_spec.y"
                                        { TypeSpecifierRef(VOID); }
#line 2301 "src/yy/y.tab.c"
    break;

  case 100:
#line 250 "spec/parser_spec.y"
                                        { TypeSpecifierRef(CHAR); }
#line 2307 "src/yy/y.tab.c"
    break;

  case 101:
#line 251 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SHORT); }
#line 2313 "src/yy/y.tab.c"
    break;

  case 102:
#line 252 "spec/parser_spec.y"
                                        { TypeSpecifierRef(INT); }
#line 2319 "src/yy/y.tab.c"
    break;

  case 103:
#line 253 "spec/parser_spec.y"
                                        { TypeSpecifierRef(LONG); }
#line 2325 "src/yy/y.tab.c"
    break;

  case 104:
#line 254 "spec/parser_spec.y"
                                        { TypeSpecifierRef(FLOAT); }
#line 2331 "src/yy/y.tab.c"
    break;

  case 105:
#line 255 "spec/parser_spec.y"
                                        { TypeSpecifierRef(DOUBLE); }
#line 2337 "src/yy/y.tab.c"
    break;

  case 106:
#line 256 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SIGNED); }
#line 2343 "src/yy/y.tab.c"
    break;

  case 107:
#line 257 "spec/parser_spec.y"
                                { TypeSpecifierRef(UNSIGNED); }
#line 2349 "src/yy/y.tab.c"
    break;

  case 110:
#line 260 "spec/parser_spec.y"
                                { IdentifierName(); TypedefName(); }
#line 2355 "src/yy/y.tab.c"
    break;

  case 111:
#line 264 "spec/parser_spec.y"
                                                                                      { TagDefined(); }
#line 2361 "src/yy/y.tab.c"
    break;

  case 112:
#line 265 "spec/parser_spec.y"
                                                                             { TagDefined(); }
#line 2367 "src/yy/y.tab.c"
    break;

  case 113:
#line 266 "spec/parser_spec.y"
                                   { TagDeclared(); }
#line 2373 "src/yy/y.tab.c"
    break;

  case 114:
#line 270 "spec/parser_spec.y"
                        { TagTypeRef(TAG_STRUCT); }
#line 2379 "src/yy/y.tab.c"
    break;

  case 115:
#line 271 "spec/parser_spec.y"
                                { TagTypeRef(TAG_UNION); }
#line 2385 "src/yy/y.tab.c"
    break;

  case 116:
#line 275 "spec/parser_spec.y"
                     { IdentifierName(); }
#line 2391 "src/yy/y.tab.c"
    break;

  case 117:
#line 279 "spec/parser_spec.y"
                { TagDefOpen(); }
#line 2397 "src/yy/y.tab.c"
    break;

  case 118:
#line 283 "spec/parser_spec.y"
                { }
#line 2403 "src/yy/y.tab.c"
    break;

  case 121:
#line 292 "spec/parser_spec.y"
                                                              { Declaration(); }
#line 2409 "src/yy/y.tab.c"
    break;

  case 122:
#line 296 "spec/parser_spec.y"
                                          { FullDeclarationSpecifiers(); }
#line 2415 "src/yy/y.tab.c"
    break;

  case 132:
#line 318 "spec/parser_spec.y"
                                                                   { TagDefined(); }
#line 2421 "src/yy/y.tab.c"
    break;

  case 133:
#line 319 "spec/parser_spec.y"
                                                          { TagDefined(); }
#line 2427 "src/yy/y.tab.c"
    break;

  case 134:
#line 320 "spec/parser_spec.y"
                                                                       { TagDefined(); }
#line 2433 "src/yy/y.tab.c"
    break;

  case 135:
#line 321 "spec/parser_spec.y"
                                                              { TagDefined(); }
#line 2439 "src/yy/y.tab.c"
    break;

  case 136:
#line 322 "spec/parser_spec.y"
                        { TagDeclared(); }
#line 2445 "src/yy/y.tab.c"
    break;

  case 137:
#line 326 "spec/parser_spec.y"
                { TagTypeRef(TAG_ENUM); }
#line 2451 "src/yy/y.tab.c"
    break;

  case 140:
#line 335 "spec/parser_spec.y"
                          { EnumeratorDefault(); }
#line 2457 "src/yy/y.tab.c"
    break;

  case 141:
#line 336 "spec/parser_spec.y"
                                                  { EnumeratorCustom(); }
#line 2463 "src/yy/y.tab.c"
    break;

  case 142:
#line 340 "spec/parser_spec.y"
                                        { TypeQualifierRef(CONST); }
#line 2469 "src/yy/y.tab.c"
    break;

  case 143:
#line 341 "spec/parser_spec.y"
                                { TypeQualifierRef(VOLATILE); }
#line 2475 "src/yy/y.tab.c"
    break;

  case 144:
#line 345 "spec/parser_spec.y"
                            { Declarator(); }
#line 2481 "src/yy/y.tab.c"
    break;

  case 145:
#line 349 "spec/parser_spec.y"
                            { DeclaratorInitialized(); }
#line 2487 "src/yy/y.tab.c"
    break;

  case 146:
#line 353 "spec/parser_spec.y"
                            { Declarator(); IsFunctionDefinition(); }
#line 2493 "src/yy/y.tab.c"
    break;

  case 147:
#line 357 "spec/parser_spec.y"
                                    { NestedDeclarator(); }
#line 2499 "src/yy/y.tab.c"
    break;

  case 150:
#line 363 "spec/parser_spec.y"
                                    { }
#line 2505 "src/yy/y.tab.c"
    break;

  case 151:
#line 364 "spec/parser_spec.y"
                                                        { ArrayLengthDeclarator(); }
#line 2511 "src/yy/y.tab.c"
    break;

  case 152:
#line 365 "spec/parser_spec.y"
                                    { ArrayVariableDeclarator(); }
#line 2517 "src/yy/y.tab.c"
    break;

  case 153:
#line 366 "spec/parser_spec.y"
                                                                                           { FunctionDeclarator(); }
#line 2523 "src/yy/y.tab.c"
    break;

  case 154:
#line 367 "spec/parser_spec.y"
                                                                                       { FuncNonprototypeDeclarator(); }
#line 2529 "src/yy/y.tab.c"
    break;

  case 155:
#line 368 "spec/parser_spec.y"
                                                                       { FuncNonprototypeDeclarator(); }
#line 2535 "src/yy/y.tab.c"
    break;

  case 156:
#line 372 "spec/parser_spec.y"
                     { IdentifierName(); }
#line 2541 "src/yy/y.tab.c"
    break;

  case 157:
#line 376 "spec/parser_spec.y"
              { FunctionParamsOpen(); }
#line 2547 "src/yy/y.tab.c"
    break;

  case 158:
#line 380 "spec/parser_spec.y"
                { FunctionParamsClose(); }
#line 2553 "src/yy/y.tab.c"
    break;

  case 159:
#line 384 "spec/parser_spec.y"
              { PointerOpen(); }
#line 2559 "src/yy/y.tab.c"
    break;

  case 160:
#line 385 "spec/parser_spec.y"
                                  { PointerQualifierOpen();}
#line 2565 "src/yy/y.tab.c"
    break;

  case 161:
#line 386 "spec/parser_spec.y"
                      { Pointer(); }
#line 2571 "src/yy/y.tab.c"
    break;

  case 162:
#line 387 "spec/parser_spec.y"
                                          { PointerQualifier(); }
#line 2577 "src/yy/y.tab.c"
    break;

  case 166:
#line 397 "spec/parser_spec.y"
                                      { Ellipsis(); }
#line 2583 "src/yy/y.tab.c"
    break;

  case 169:
#line 406 "spec/parser_spec.y"
                                                 { Declaration(); }
#line 2589 "src/yy/y.tab.c"
    break;

  case 170:
#line 407 "spec/parser_spec.y"
                                                          { Declaration(); }
#line 2595 "src/yy/y.tab.c"
    break;

  case 171:
#line 408 "spec/parser_spec.y"
                                      { AbstractDeclarator(); Declaration(); }
#line 2601 "src/yy/y.tab.c"
    break;

  case 172:
#line 412 "spec/parser_spec.y"
                              { Declaration(); }
#line 2607 "src/yy/y.tab.c"
    break;

  case 173:
#line 413 "spec/parser_spec.y"
                                                  { Declaration(); }
#line 2613 "src/yy/y.tab.c"
    break;

  case 174:
#line 417 "spec/parser_spec.y"
                          { NonprototypeParam(); }
#line 2619 "src/yy/y.tab.c"
    break;

  case 175:
#line 421 "spec/parser_spec.y"
                                   { AbstractDeclarator(); Declaration(); }
#line 2625 "src/yy/y.tab.c"
    break;

  case 176:
#line 422 "spec/parser_spec.y"
                                                       { Declaration(); }
#line 2631 "src/yy/y.tab.c"
    break;

  case 177:
#line 426 "spec/parser_spec.y"
                                     { AbstractDeclarator(); }
#line 2637 "src/yy/y.tab.c"
    break;

  case 178:
#line 430 "spec/parser_spec.y"
                  { NestedDeclarator(); }
#line 2643 "src/yy/y.tab.c"
    break;

  case 180:
#line 432 "spec/parser_spec.y"
                                             { NestedDeclarator(); }
#line 2649 "src/yy/y.tab.c"
    break;

  case 181:
#line 436 "spec/parser_spec.y"
                                             { }
#line 2655 "src/yy/y.tab.c"
    break;

  case 182:
#line 437 "spec/parser_spec.y"
                  { ArrayVariableDeclarator(); }
#line 2661 "src/yy/y.tab.c"
    break;

  case 183:
#line 438 "spec/parser_spec.y"
                                       { ArrayLengthDeclarator(); }
#line 2667 "src/yy/y.tab.c"
    break;

  case 184:
#line 439 "spec/parser_spec.y"
                                              { ArrayVariableDeclarator(); }
#line 2673 "src/yy/y.tab.c"
    break;

  case 185:
#line 440 "spec/parser_spec.y"
                                                                  { ArrayLengthDeclarator(); }
#line 2679 "src/yy/y.tab.c"
    break;

  case 186:
#line 441 "spec/parser_spec.y"
                                                     { FuncNonprototypeDeclarator(); }
#line 2685 "src/yy/y.tab.c"
    break;

  case 187:
#line 442 "spec/parser_spec.y"
                                                                         { FunctionDeclarator(); }
#line 2691 "src/yy/y.tab.c"
    break;

  case 188:
#line 443 "spec/parser_spec.y"
                                                                                { FuncNonprototypeDeclarator(); }
#line 2697 "src/yy/y.tab.c"
    break;

  case 189:
#line 444 "spec/parser_spec.y"
                                                                                                    { FunctionDeclarator(); }
#line 2703 "src/yy/y.tab.c"
    break;

  case 190:
#line 448 "spec/parser_spec.y"
                                { Initializer(); }
#line 2709 "src/yy/y.tab.c"
    break;

  case 193:
#line 454 "spec/parser_spec.y"
              { InitializerOpen(); }
#line 2715 "src/yy/y.tab.c"
    break;

  case 194:
#line 458 "spec/parser_spec.y"
              { InitializerClose(); }
#line 2721 "src/yy/y.tab.c"
    break;

  case 202:
#line 475 "spec/parser_spec.y"
                        { Label(); }
#line 2727 "src/yy/y.tab.c"
    break;

  case 203:
#line 479 "spec/parser_spec.y"
                                    { CaseLabel(); }
#line 2733 "src/yy/y.tab.c"
    break;

  case 204:
#line 483 "spec/parser_spec.y"
                   { DefaultLabel(); }
#line 2739 "src/yy/y.tab.c"
    break;

  case 210:
#line 498 "spec/parser_spec.y"
              { BlockOpen(); }
#line 2745 "src/yy/y.tab.c"
    break;

  case 211:
#line 502 "spec/parser_spec.y"
              { BlockClose(); }
#line 2751 "src/yy/y.tab.c"
    break;

  case 219:
#line 522 "spec/parser_spec.y"
              { FuncBodyOpen(); }
#line 2757 "src/yy/y.tab.c"
    break;

  case 220:
#line 526 "spec/parser_spec.y"
              { FuncBodyClose(); }
#line 2763 "src/yy/y.tab.c"
    break;

  case 223:
#line 535 "spec/parser_spec.y"
                                                                { EmptyStmt(); }
#line 2769 "src/yy/y.tab.c"
    break;

  case 224:
#line 536 "spec/parser_spec.y"
                                { ExpressionStmt(); }
#line 2775 "src/yy/y.tab.c"
    break;

  case 225:
#line 540 "spec/parser_spec.y"
                        { IfOpen(); }
#line 2781 "src/yy/y.tab.c"
    break;

  case 226:
#line 544 "spec/parser_spec.y"
                        { ElseOpen(); }
#line 2787 "src/yy/y.tab.c"
    break;

  case 227:
#line 548 "spec/parser_spec.y"
                  { SwitchOpen(); }
#line 2793 "src/yy/y.tab.c"
    break;

  case 228:
#line 552 "spec/parser_spec.y"
                                                                                                                                                        { IfStmt(); }
#line 2799 "src/yy/y.tab.c"
    break;

  case 229:
#line 553 "spec/parser_spec.y"
                                                                                                { IfElseStmt(); }
#line 2805 "src/yy/y.tab.c"
    break;

  case 230:
#line 554 "spec/parser_spec.y"
                                                                                                                                                { SwitchStmt(); }
#line 2811 "src/yy/y.tab.c"
    break;

  case 231:
#line 558 "spec/parser_spec.y"
                        { WhileOpen(); }
#line 2817 "src/yy/y.tab.c"
    break;

  case 232:
#line 562 "spec/parser_spec.y"
                                { DoOpen(); }
#line 2823 "src/yy/y.tab.c"
    break;

  case 233:
#line 566 "spec/parser_spec.y"
                        { ForOpen(); }
#line 2829 "src/yy/y.tab.c"
    break;

  case 234:
#line 570 "spec/parser_spec.y"
                     { ControlExpression(); }
#line 2835 "src/yy/y.tab.c"
    break;

  case 235:
#line 574 "spec/parser_spec.y"
                      { ForDeclaration(); }
#line 2841 "src/yy/y.tab.c"
    break;

  case 236:
#line 578 "spec/parser_spec.y"
                     { ForExpression(); }
#line 2847 "src/yy/y.tab.c"
    break;

  case 237:
#line 579 "spec/parser_spec.y"
          { VoidExpr(); ForExpression(); }
#line 2853 "src/yy/y.tab.c"
    break;

  case 238:
#line 584 "spec/parser_spec.y"
                                                                                                                                                                                                { WhileStmt(); }
#line 2859 "src/yy/y.tab.c"
    break;

  case 239:
#line 585 "spec/parser_spec.y"
                                                                                                                                                                                { DoWhileStmt(); }
#line 2865 "src/yy/y.tab.c"
    break;

  case 240:
#line 586 "spec/parser_spec.y"
                                                                                                        { ForStmt(); }
#line 2871 "src/yy/y.tab.c"
    break;

  case 241:
#line 587 "spec/parser_spec.y"
                                                                                            { ForStmt(); }
#line 2877 "src/yy/y.tab.c"
    break;

  case 242:
#line 591 "spec/parser_spec.y"
                                        { GotoStmt(); }
#line 2883 "src/yy/y.tab.c"
    break;

  case 243:
#line 592 "spec/parser_spec.y"
                                                                { ContinueStmt(); }
#line 2889 "src/yy/y.tab.c"
    break;

  case 244:
#line 593 "spec/parser_spec.y"
                                                                        { BreakStmt(); }
#line 2895 "src/yy/y.tab.c"
    break;

  case 245:
#line 594 "spec/parser_spec.y"
                                                                        { ReturnStmt(); }
#line 2901 "src/yy/y.tab.c"
    break;

  case 246:
#line 595 "spec/parser_spec.y"
                                        { ReturnExprStmt(); }
#line 2907 "src/yy/y.tab.c"
    break;

  case 249:
#line 604 "spec/parser_spec.y"
                               { TranslationUnit(); }
#line 2913 "src/yy/y.tab.c"
    break;

  case 250:
#line 605 "spec/parser_spec.y"
          { TranslationUnit(); }
#line 2919 "src/yy/y.tab.c"
    break;

  case 253:
#line 614 "spec/parser_spec.y"
                                                                                     {  }
#line 2925 "src/yy/y.tab.c"
    break;

  case 254:
#line 615 "spec/parser_spec.y"
                                                                        { }
#line 2931 "src/yy/y.tab.c"
    break;


#line 2935 "src/yy/y.tab.c"

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
#line 618 "spec/parser_spec.y"

#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
