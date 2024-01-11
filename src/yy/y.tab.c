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
    RETURN_ = 315,
    ASM_ = 316
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

#line 224 "src/yy/y.tab.c"

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
#define YYLAST   1035

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  107
/* YYNRULES -- Number of rules.  */
#define YYNRULES  257
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  418

#define YYUNDEFTOK  2
#define YYMAXUTOK   316


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
       2,     2,     2,    73,     2,     2,     2,    75,    68,     2,
      62,    63,    69,    70,    67,    71,    66,    74,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,    83,
      76,    82,    77,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    79,    85,    72,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    57,    57,    58,    59,    60,    64,    65,    66,    67,
      68,    69,    70,    71,    75,    79,    83,    87,    88,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     106,   110,   114,   115,   119,   120,   121,   122,   126,   127,
     128,   132,   133,   134,   138,   139,   140,   141,   142,   146,
     147,   148,   152,   153,   157,   158,   162,   163,   167,   168,
     172,   173,   177,   178,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   197,   198,   202,   206,
     210,   211,   215,   219,   223,   224,   225,   226,   227,   228,
     232,   233,   237,   238,   242,   243,   244,   245,   246,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   265,   266,   267,   271,   272,   276,   280,   284,   288,
     289,   293,   297,   301,   302,   303,   304,   308,   309,   313,
     319,   320,   321,   322,   323,   327,   331,   332,   336,   337,
     341,   342,   346,   350,   354,   358,   359,   363,   364,   365,
     366,   367,   368,   369,   373,   377,   381,   385,   386,   387,
     388,   392,   393,   397,   398,   402,   403,   407,   408,   409,
     413,   414,   418,   422,   423,   427,   431,   432,   433,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   449,   450,
     451,   455,   459,   463,   464,   468,   469,   470,   471,   472,
     473,   474,   478,   482,   486,   490,   491,   495,   496,   497,
     501,   505,   509,   510,   514,   515,   519,   520,   524,   528,
     532,   533,   537,   538,   542,   546,   550,   554,   555,   556,
     560,   564,   568,   572,   576,   581,   582,   586,   587,   592,
     593,   594,   595,   599,   600,   601,   602,   603,   607,   611,
     615,   616,   620,   621,   625,   626,   630,   631
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
  "DO_", "FOR_", "GOTO_", "CONTINUE_", "BREAK_", "RETURN_", "ASM_", "'('",
  "')'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'", "'~'",
  "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='",
  "';'", "'{'", "'}'", "$accept", "primary_expression",
  "postfix_expression", "field_name", "args_open", "args_close",
  "argument_expression_list", "unary_expression", "type_open",
  "type_close", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "expression_nested", "expression",
  "constant_expression", "declaration", "redeclaration_specifiers",
  "full_declaration_specifiers", "declaration_specifiers_nested",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "tag_name", "tag_def_open", "tag_def_close", "struct_declaration_list",
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
  "compound_statement", "labeled_statement", "block_open", "block_close",
  "block", "block_item", "func_body", "func_body_open", "func_body_close",
  "declaration_list", "expression_statement", "if_open", "else_open",
  "switch_open", "selection_statement", "while_open", "do_open",
  "for_open", "control_expression", "for_declaration",
  "for_no_declaration", "for_expression", "iteration_statement",
  "jump_statement", "asm_string", "inline_assembly",
  "rec_translation_unit", "translation_unit", "external_declaration",
  "function_definition", YY_NULLPTR
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
     315,   316,    40,    41,    91,    93,    46,    44,    38,    42,
      43,    45,   126,    33,    47,    37,    60,    62,    94,   124,
      63,    58,    61,    59,   123,   125
};
# endif

#define YYPACT_NINF (-270)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-203)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     968,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,   -42,    31,   -25,   968,   968,  -270,    18,  -270,
      18,   968,   968,    50,  -270,  -270,  -270,  -270,    31,    -3,
     -40,  -270,  -270,    -2,   890,   101,    88,  -270,    42,  -270,
    -270,  -270,  -270,   -21,   988,   -21,    92,  -270,  -270,  -270,
      70,  -270,  -270,    -3,    31,  -270,   595,  -270,  -270,    31,
    -270,   365,   890,  -270,   711,   854,    88,   988,   988,   574,
    -270,    31,  -270,   988,    92,   -23,  -270,    23,  -270,  -270,
    -270,  -270,    37,  -270,  -270,  -270,   782,   808,   808,   782,
     782,   782,   782,   782,   782,   782,  -270,  -270,   240,   304,
     988,  -270,   131,   185,   191,    55,   256,    77,    60,    86,
     154,    19,  -270,  -270,  -270,   595,   105,   782,  -270,  -270,
    -270,  -270,  -270,  -270,   179,   111,   125,   682,   168,  -270,
    -270,  -270,  -270,   170,   159,  -270,  -270,   164,   169,   171,
    -270,  -270,   436,   187,   507,  -270,  -270,   202,   212,  -270,
     217,   578,   226,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,   225,  -270,    28,  -270,  -270,  -270,   232,   234,  -270,
      -7,  -270,   574,  -270,  -270,  -270,  -270,   102,  -270,  -270,
    -270,  -270,    54,    22,  -270,   782,  -270,   988,   782,  -270,
    -270,   242,  -270,  -270,  -270,  -270,  -270,  -270,   300,  -270,
    -270,  -270,   782,   300,   737,   782,   782,   782,   782,   782,
     782,   782,   782,   782,   782,   782,   -16,   244,   782,   782,
     782,   782,   782,   782,   782,   782,   782,   782,   782,   782,
     782,   782,   782,   782,   782,   782,   782,  -270,    82,  -270,
     227,  -270,  -270,  -270,   229,   309,   782,  -270,   578,   578,
     578,  -270,  -270,   230,  -270,  -270,   782,   782,   782,   263,
     666,  -270,    28,   753,  -270,   910,    32,  -270,  -270,   115,
    -270,   947,    92,  -270,  -270,    31,  -270,    22,  -270,  -270,
    -270,  -270,   244,  -270,  -270,  -270,   253,  -270,  -270,  -270,
      81,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,   -16,   116,  -270,  -270,   782,  -270,  -270,
    -270,   131,   131,   185,   185,   191,   191,   191,   191,    55,
      55,   256,    77,    60,    86,   154,   238,   119,  -270,  -270,
    -270,  -270,  -270,   257,  -270,  -270,  -270,  -270,  -270,  -270,
     269,   270,   271,   273,  -270,   254,  -270,   782,   782,   275,
    -270,   274,  -270,   232,   115,   766,   910,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,   782,  -270,  -270,   782,  -270,  -270,
     258,   578,   578,   578,   782,  -270,  -270,   260,   261,  -270,
    -270,  -270,  -270,   280,  -270,   232,  -270,  -270,  -270,   284,
    -270,  -270,   277,   782,   782,  -270,  -270,  -270,   578,   264,
     285,   286,  -270,  -270,   578,   578,  -270,  -270
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
     253,   110,    94,    95,    96,    97,    98,   100,   101,   102,
     103,   106,   107,   104,   105,   140,   141,    99,   114,   115,
     135,   255,     0,     0,    83,    84,    86,   108,     0,   109,
       0,    88,   252,     0,   250,   254,    80,   154,     0,   157,
       0,    90,    92,     0,     0,   144,   146,   147,     0,    85,
      87,   116,   117,   113,     0,   134,     0,    89,   251,     1,
       0,   161,   159,   158,     0,    81,     0,   218,   220,     0,
     257,     0,     0,   155,     0,     0,   145,     0,   124,     0,
     119,     0,   122,   126,     0,     0,   136,   138,   148,   162,
     160,    91,   142,     2,     3,     4,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,   191,     6,    19,    32,
       0,    34,    38,    41,    44,    49,    52,    54,    56,    58,
      60,    62,    64,   188,    93,     0,     2,     0,   204,   224,
     226,   230,   231,   232,     0,     0,     0,     0,     0,   222,
     210,   219,    76,    78,     0,   215,   214,     0,     0,     0,
     195,   197,     0,     0,   212,   216,   196,     0,     0,   198,
       0,     0,     0,   199,   200,   201,   221,   256,   150,    32,
      79,     0,   156,   169,    83,   172,   153,     0,   163,   165,
       0,   170,     0,   123,   118,   112,   120,     0,   127,   129,
     142,   125,     0,     0,   131,     0,    28,     0,     0,    20,
      21,     0,    22,    23,    24,    25,    26,    27,     0,    12,
      13,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,     0,   203,
       0,   244,   245,   246,     0,     0,     0,   223,     0,     0,
       0,   211,   205,     0,   217,   213,     0,     0,     0,     0,
       0,   149,   155,     0,   167,     0,   176,   168,   175,   177,
     151,     0,     0,   152,   111,     0,   121,     0,   130,   133,
     137,   139,     0,     5,    14,    11,     0,    10,    16,     8,
       0,    17,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    65,   155,   176,   174,    31,     0,    35,    36,
      37,    39,    40,    42,    43,    47,    48,    45,    46,    50,
      51,    53,    55,    57,    59,    61,     0,     0,   192,   189,
     243,   247,   248,     0,    77,   207,   208,   209,   206,   233,
       0,     0,     0,     0,   236,     0,   234,   238,   238,     0,
     180,     0,   184,     0,   178,     0,     0,   164,   166,   171,
     128,   132,    29,     7,     0,     9,    33,     0,   194,   190,
       0,     0,     0,     0,     0,   235,   237,     0,     0,   179,
     181,   185,   182,     0,   186,     0,    18,    63,   249,   227,
     229,   239,     0,   238,   238,   183,   187,   225,     0,     0,
       0,     0,   228,   240,     0,     0,   242,   241
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -270,  -270,  -270,   137,  -270,    51,  -270,   -19,   259,    62,
     -31,    46,    49,    56,    57,   112,   110,   113,   117,   114,
    -270,   -66,   -61,  -270,   -95,  -107,    15,  -270,     0,   -24,
    -270,   293,  -270,    64,  -270,  -270,   330,    61,   -56,   287,
     -62,   -91,   -29,  -270,    78,  -270,  -270,   278,  -175,   190,
     -58,  -270,  -270,   -12,   -38,   -47,   -43,   -79,   -33,  -270,
    -253,  -270,    84,  -270,    85,   178,   150,  -248,  -238,  -109,
    -270,    40,  -270,  -149,  -270,  -270,  -270,  -270,  -270,  -270,
     118,    89,  -270,   306,  -270,   231,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,  -254,  -270,  -270,  -269,  -270,
    -270,  -270,  -270,  -270,  -270,   347,  -270
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   107,   108,   295,   214,   299,   300,   109,   110,   317,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   142,   143,   144,   171,   145,    22,    69,    24,
      40,    41,    25,    26,    27,    28,    53,    54,   185,    79,
      80,    81,    82,   187,   188,    29,    30,    85,    86,    31,
      42,    43,    44,   190,    46,    47,   275,   176,    48,    63,
     177,   178,   179,   180,   181,   227,   277,   278,   279,   124,
     125,   339,   248,   146,   147,   148,   149,   150,   151,   152,
     262,   153,   154,    70,    71,   155,    72,   156,   157,   408,
     158,   159,   160,   161,   162,   350,   357,   358,   387,   163,
     164,   343,   165,    32,    33,    34,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    49,    50,    75,   201,   123,    62,    57,   170,    87,
      76,    45,   269,   351,   352,    21,   247,   186,   290,   226,
     249,    51,   363,   189,   359,    37,    60,    64,   175,   194,
      90,    37,    23,    75,    37,    37,   245,    87,   364,    15,
      16,    36,   254,    65,   193,    37,   313,    21,   273,   183,
      59,   174,    92,    39,   191,   169,   172,    92,   -82,    68,
     282,   170,   184,    52,   123,   359,    39,   235,   236,   202,
     203,   204,   205,   206,   207,   173,   364,   196,   199,   200,
      66,   169,   169,   169,   169,   169,   169,   166,   291,   388,
     272,    56,   273,    38,   272,    37,   273,    39,   280,   246,
      39,   283,    52,   201,    38,   195,   226,   184,   169,   345,
     346,   347,   290,   395,    77,   274,    84,   296,    78,  -143,
     186,   287,    93,    94,    95,    96,   284,    97,    98,   170,
     402,   237,   238,    88,   410,   411,   288,   289,   242,   184,
     276,    78,    78,    78,   298,   241,    87,    78,   374,   337,
      73,   336,    74,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   243,   361,   338,  -142,   285,
     244,   349,   349,   349,    78,   355,   169,    73,   313,   365,
     273,    99,   250,  -143,  -142,   286,  -202,   100,   101,   102,
     103,   104,   105,   314,   251,   344,   362,   318,   319,   320,
     228,   233,   234,   106,   338,   229,   230,   170,   252,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   189,   378,    61,
     255,   371,   399,   400,   401,   175,   366,   256,    76,   276,
      87,   263,   257,   265,    83,   258,    78,   208,   209,   210,
     259,   174,   260,    89,   169,   231,   232,   174,   393,   412,
      60,    78,   386,   386,   266,   416,   417,    83,    83,    83,
     239,   240,   141,    83,   267,   173,   123,   321,   322,   268,
     314,   173,   323,   324,   391,   356,   376,   394,   270,   349,
     271,   325,   326,   327,   328,   172,   329,   330,   169,   170,
      83,   281,   211,   294,   212,   293,   213,   316,   386,   386,
     340,   397,   341,   396,   342,   261,   406,   353,   373,   377,
     380,   366,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   381,   382,   383,   384,   407,   385,   389,   390,
     409,   398,   174,   403,   404,   405,   169,   413,   414,   415,
     297,   375,   332,   331,   372,   197,   333,    91,   169,   335,
      55,   334,   192,   370,   182,   368,   173,   369,   126,    94,
      95,    96,    83,    97,    98,   292,   315,   379,   167,    58,
       0,   348,     0,     0,   264,     0,   225,    83,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     0,   127,   128,   129,     0,   130,   131,
     132,   133,   134,   135,   136,   137,   138,    99,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,   126,
      94,    95,    96,     0,    97,    98,     0,     0,   139,   140,
     141,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,   127,   128,   129,     0,   130,
     131,   132,   133,   134,   135,   136,   137,   138,    99,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
     126,    94,    95,    96,     0,    97,    98,     0,     0,   139,
     140,   261,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     0,   127,   128,   129,     0,
     130,   131,   132,   133,   134,   135,   136,   137,   138,    99,
       0,     0,     0,     0,     0,   100,   101,   102,   103,   104,
     105,   126,    94,    95,    96,     0,    97,    98,     0,     0,
     139,   140,     0,     0,     0,     0,     0,     0,    93,    94,
      95,    96,     1,    97,    98,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,     0,     0,     0,     0,   127,   128,   129,
       0,   130,   131,   132,   133,   134,   135,   136,   137,   138,
      99,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,   105,     0,     0,     0,     0,     0,    99,     0,   184,
       0,   139,   140,   100,   101,   102,   103,   104,   105,    93,
      94,    95,    96,     0,    97,    98,     0,     0,     0,   106,
       0,     0,     0,     0,     0,    93,    94,    95,    96,     0,
      97,    98,     0,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    93,    94,    95,    96,     0,    97,
      98,     0,     0,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
      93,    94,    95,    96,    99,    97,    98,     0,     0,   354,
     100,   101,   102,   103,   104,   105,    93,    94,    95,    96,
       0,    97,    98,     0,     0,   253,     0,     0,     0,    93,
      94,    95,    96,    99,    97,    98,   168,     0,     0,   100,
     101,   102,   103,   104,   105,    93,    94,    95,    96,     0,
      97,    98,     0,     0,     0,     0,     0,     0,     0,    99,
     298,     0,     0,     0,     0,   100,   101,   102,   103,   104,
     105,    93,    94,    95,    96,    99,    97,    98,   360,     0,
       0,   100,   101,   102,   103,   104,   105,     0,    99,     0,
       0,   392,     0,     0,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,    99,     0,     0,     0,     0,     0,
     100,   101,   102,   103,   104,   105,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     198,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,   105,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   172,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   172,    67,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,   367,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,     1,     0,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
};

static const yytype_int16 yycheck[] =
{
       0,    25,    26,    46,    99,    66,    39,    31,    74,    56,
      48,    23,   161,   267,   268,     0,   125,    79,   193,   110,
     127,     3,   275,    81,   272,     3,    38,    67,    75,    85,
      63,     3,    32,    76,     3,     3,    17,    84,   276,    42,
      43,    83,   137,    83,    67,     3,    62,    32,    64,    78,
       0,    75,    64,    69,    83,    74,    63,    69,    83,    44,
      67,   127,    85,    84,   125,   313,    69,    12,    13,   100,
     101,   102,   103,   104,   105,    75,   314,    96,    97,    98,
      82,   100,   101,   102,   103,   104,   105,    72,   195,   358,
      62,    30,    64,    62,    62,     3,    64,    69,   177,    80,
      69,   180,    84,   198,    62,    82,   197,    85,   127,   258,
     259,   260,   287,   366,    53,   173,    55,   212,    54,    82,
     182,    67,     3,     4,     5,     6,   182,     8,     9,   195,
     384,    76,    77,    63,   403,   404,   192,   193,    78,    85,
     173,    77,    78,    79,    63,    68,   193,    83,    67,    67,
      62,   246,    64,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,    79,   273,    85,    67,    67,
      16,   266,   267,   268,   110,   270,   195,    62,    62,    64,
      64,    62,     3,    82,    83,    83,    81,    68,    69,    70,
      71,    72,    73,   226,    83,   256,   275,   228,   229,   230,
      69,    10,    11,    84,    85,    74,    75,   273,    83,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   285,   337,    39,
      62,   287,   381,   382,   383,   282,   279,    67,   276,   272,
     287,   152,    83,   154,    54,    81,   182,     7,     8,     9,
      81,   275,    81,    63,   273,    70,    71,   281,   365,   408,
     272,   197,   357,   358,    62,   414,   415,    77,    78,    79,
      14,    15,    85,    83,    62,   275,   337,   231,   232,    62,
     313,   281,   233,   234,   363,   270,   317,   366,    62,   384,
      65,   235,   236,   237,   238,    63,   239,   240,   317,   365,
     110,    67,    62,     3,    64,    63,    66,    63,   403,   404,
      83,   377,    83,   374,     5,    85,   395,    54,    65,    81,
      63,   364,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    63,    63,    63,    62,    52,    83,    63,    65,
      63,    83,   366,    83,    83,    65,   365,    83,    63,    63,
     213,   300,   242,   241,   292,    96,   243,    64,   377,   245,
      30,   244,    84,   285,    77,   281,   366,   282,     3,     4,
       5,     6,   182,     8,     9,   197,   226,   337,    72,    32,
      -1,   263,    -1,    -1,   153,    -1,    82,   197,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    83,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    83,
      84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    28,     8,     9,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    62,    -1,    85,
      -1,    83,    84,    68,    69,    70,    71,    72,    73,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
       3,     4,     5,     6,    62,     8,     9,    -1,    -1,    83,
      68,    69,    70,    71,    72,    73,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    83,    -1,    -1,    -1,     3,
       4,     5,     6,    62,     8,     9,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,     3,     4,     5,     6,    62,     8,     9,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    62,    -1,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    84,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    28,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   112,   113,   114,   115,   118,   119,   120,   121,   131,
     132,   135,   189,   190,   191,   192,    83,     3,    62,    69,
     116,   117,   136,   137,   138,   139,   140,   141,   144,   115,
     115,     3,    84,   122,   123,   122,   123,   115,   191,     0,
     139,   135,   144,   145,    67,    83,    82,    84,   112,   114,
     169,   170,   172,    62,    64,   142,   140,   123,   119,   125,
     126,   127,   128,   135,   123,   133,   134,   141,    63,   135,
     144,   117,   139,     3,     4,     5,     6,     8,     9,    62,
      68,    69,    70,    71,    72,    73,    84,    87,    88,    93,
      94,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   155,   156,     3,    49,    50,    51,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    83,
      84,    85,   108,   109,   110,   112,   159,   160,   161,   162,
     163,   164,   165,   167,   168,   171,   173,   174,   176,   177,
     178,   179,   180,   185,   186,   188,   112,   169,    65,    93,
     107,   111,    63,   114,   115,   141,   143,   146,   147,   148,
     149,   150,   125,   128,    85,   124,   126,   129,   130,   136,
     139,   128,   133,    67,   124,    82,    93,    94,    62,    93,
      93,   110,    96,    96,    96,    96,    96,    96,     7,     8,
       9,    62,    64,    66,    90,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    82,   127,   151,    69,    74,
      75,    70,    71,    10,    11,    12,    13,    76,    77,    14,
      15,    68,    78,    79,    16,    17,    80,   155,   158,   111,
       3,    83,    83,    83,   110,    62,    67,    83,    81,    81,
      81,    85,   166,   167,   171,   167,    62,    62,    62,   159,
      62,    65,    62,    64,   136,   142,   144,   152,   153,   154,
     143,    67,    67,   143,   124,    67,    83,    67,   124,   124,
     134,   111,   151,    63,     3,    89,   110,    89,    63,    91,
      92,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,    62,   144,   152,    63,    95,    96,    96,
      96,    97,    97,    98,    98,    99,    99,    99,    99,   100,
     100,   101,   102,   103,   104,   105,   110,    67,    85,   157,
      83,    83,     5,   187,   108,   159,   159,   159,   166,   110,
     181,   181,   181,    54,    83,   110,   112,   182,   183,   153,
      65,   111,   143,   146,   154,    64,   142,    48,   148,   150,
     130,   124,    95,    65,    67,    91,    96,    81,   155,   157,
      63,    63,    63,    63,    62,    83,   110,   184,   184,    63,
      65,   143,    65,   111,   143,   146,   108,   107,    83,   159,
     159,   159,   181,    83,    83,    65,   143,    52,   175,    63,
     184,   184,   159,    83,    63,    63,   159,   159
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    90,    91,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      94,    95,    96,    96,    97,    97,    97,    97,    98,    98,
      98,    99,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   109,   110,   111,
     112,   112,   113,   114,   115,   115,   115,   115,   115,   115,
     116,   116,   117,   117,   118,   118,   118,   118,   118,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   121,   121,   122,   123,   124,   125,
     125,   126,   127,   128,   128,   128,   128,   129,   129,   130,
     131,   131,   131,   131,   131,   132,   133,   133,   134,   134,
     135,   135,   136,   137,   138,   139,   139,   140,   140,   140,
     140,   140,   140,   140,   141,   142,   143,   144,   144,   144,
     144,   145,   145,   146,   146,   147,   147,   148,   148,   148,
     149,   149,   150,   151,   151,   152,   153,   153,   153,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   155,   155,
     155,   156,   157,   158,   158,   159,   159,   159,   159,   159,
     159,   159,   160,   161,   162,   163,   163,   164,   164,   164,
     165,   166,   167,   167,   168,   168,   169,   169,   170,   171,
     172,   172,   173,   173,   174,   175,   176,   177,   177,   177,
     178,   179,   180,   181,   182,   183,   183,   184,   184,   185,
     185,   185,   185,   186,   186,   186,   186,   186,   187,   188,
     189,   189,   190,   190,   191,   191,   192,   192
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
       5,     4,     6,     5,     2,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     2,     1,     1,     3,     4,
       3,     4,     4,     3,     1,     1,     1,     1,     2,     2,
       3,     1,     2,     1,     3,     1,     3,     2,     2,     1,
       1,     3,     1,     1,     2,     1,     1,     1,     2,     3,
       2,     3,     3,     4,     2,     3,     3,     4,     1,     3,
       4,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     3,     3,     3,     3,
       1,     1,     1,     2,     1,     1,     2,     3,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     5,     7,     5,
       1,     1,     1,     1,     1,     2,     1,     1,     0,     5,
       7,     8,     8,     3,     2,     2,     2,     3,     1,     5,
       1,     2,     1,     0,     1,     1,     4,     3
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
#line 57 "spec/parser_spec.y"
                                                        { IdentifierPrimary(); }
#line 1869 "src/yy/y.tab.c"
    break;

  case 3:
#line 58 "spec/parser_spec.y"
                                                                { ConstantPrimary(); 	 }
#line 1875 "src/yy/y.tab.c"
    break;

  case 4:
#line 59 "spec/parser_spec.y"
                                                { StringPrimary(); 		 }
#line 1881 "src/yy/y.tab.c"
    break;

  case 7:
#line 65 "spec/parser_spec.y"
                                                                                                                                                                { ArrayRefExpr(); }
#line 1887 "src/yy/y.tab.c"
    break;

  case 8:
#line 66 "spec/parser_spec.y"
                                                                                                                                                                { FunctionCallExpr(); }
#line 1893 "src/yy/y.tab.c"
    break;

  case 9:
#line 67 "spec/parser_spec.y"
                                                                                { FunctionCallExpr(); }
#line 1899 "src/yy/y.tab.c"
    break;

  case 10:
#line 68 "spec/parser_spec.y"
                                                                                                                                                                        { FieldRefExpr(); }
#line 1905 "src/yy/y.tab.c"
    break;

  case 11:
#line 69 "spec/parser_spec.y"
                                                                                                                                                                { PtrRefExpr(); }
#line 1911 "src/yy/y.tab.c"
    break;

  case 12:
#line 70 "spec/parser_spec.y"
                                                                                                                                                                                                        { IncDecExpr(POST_INC_EXPR); }
#line 1917 "src/yy/y.tab.c"
    break;

  case 13:
#line 71 "spec/parser_spec.y"
                                                                                                                                                                                                { IncDecExpr(POST_DEC_EXPR); }
#line 1923 "src/yy/y.tab.c"
    break;

  case 14:
#line 75 "spec/parser_spec.y"
                     { }
#line 1929 "src/yy/y.tab.c"
    break;

  case 15:
#line 79 "spec/parser_spec.y"
              { FunctionArgsOpen(); }
#line 1935 "src/yy/y.tab.c"
    break;

  case 16:
#line 83 "spec/parser_spec.y"
              { FunctionArgsClose(); }
#line 1941 "src/yy/y.tab.c"
    break;

  case 17:
#line 87 "spec/parser_spec.y"
                                                                                                                                                        { FunctionArg(); }
#line 1947 "src/yy/y.tab.c"
    break;

  case 18:
#line 88 "spec/parser_spec.y"
                                                                { FunctionArg(); }
#line 1953 "src/yy/y.tab.c"
    break;

  case 20:
#line 93 "spec/parser_spec.y"
                                                      { IncDecExpr(PRE_INC_EXPR); }
#line 1959 "src/yy/y.tab.c"
    break;

  case 21:
#line 94 "spec/parser_spec.y"
                                                      { IncDecExpr(PRE_DEC_EXPR); }
#line 1965 "src/yy/y.tab.c"
    break;

  case 22:
#line 95 "spec/parser_spec.y"
                                                                      { AddressExpr(); }
#line 1971 "src/yy/y.tab.c"
    break;

  case 23:
#line 96 "spec/parser_spec.y"
                                                                      { DerefExpr(); }
#line 1977 "src/yy/y.tab.c"
    break;

  case 24:
#line 97 "spec/parser_spec.y"
                                                                      { UnaryExpr(UNARY_PLUS_EXPR); }
#line 1983 "src/yy/y.tab.c"
    break;

  case 25:
#line 98 "spec/parser_spec.y"
                                                                      { UnaryExpr(UNARY_MINUS_EXPR); }
#line 1989 "src/yy/y.tab.c"
    break;

  case 26:
#line 99 "spec/parser_spec.y"
                                                                      { BitNotExpr(); }
#line 1995 "src/yy/y.tab.c"
    break;

  case 27:
#line 100 "spec/parser_spec.y"
                                                                      { LogNotExpr(); }
#line 2001 "src/yy/y.tab.c"
    break;

  case 28:
#line 101 "spec/parser_spec.y"
                                                      { SizeofExpr(); }
#line 2007 "src/yy/y.tab.c"
    break;

  case 29:
#line 102 "spec/parser_spec.y"
                                                        { SizeofTypeExpr(); }
#line 2013 "src/yy/y.tab.c"
    break;

  case 30:
#line 106 "spec/parser_spec.y"
              { TypeOpen(); }
#line 2019 "src/yy/y.tab.c"
    break;

  case 31:
#line 110 "spec/parser_spec.y"
              { TypeClose(); }
#line 2025 "src/yy/y.tab.c"
    break;

  case 33:
#line 115 "spec/parser_spec.y"
                                                                { CastExpr(); }
#line 2031 "src/yy/y.tab.c"
    break;

  case 35:
#line 120 "spec/parser_spec.y"
                                                        { MulExpr(MUL_EXPR); }
#line 2037 "src/yy/y.tab.c"
    break;

  case 36:
#line 121 "spec/parser_spec.y"
                                                        { MulExpr(DIV_EXPR); }
#line 2043 "src/yy/y.tab.c"
    break;

  case 37:
#line 122 "spec/parser_spec.y"
                                                        { MulExpr(MOD_EXPR); }
#line 2049 "src/yy/y.tab.c"
    break;

  case 39:
#line 127 "spec/parser_spec.y"
                                                                { AddExpr(); }
#line 2055 "src/yy/y.tab.c"
    break;

  case 40:
#line 128 "spec/parser_spec.y"
                                                                { SubExpr(); }
#line 2061 "src/yy/y.tab.c"
    break;

  case 42:
#line 133 "spec/parser_spec.y"
                                                        { BitExpr(BIT_LEFT_EXPR); }
#line 2067 "src/yy/y.tab.c"
    break;

  case 43:
#line 134 "spec/parser_spec.y"
                                                        { BitExpr(BIT_RIGHT_EXPR); }
#line 2073 "src/yy/y.tab.c"
    break;

  case 45:
#line 139 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_LT_EXPR); }
#line 2079 "src/yy/y.tab.c"
    break;

  case 46:
#line 140 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_GT_EXPR); }
#line 2085 "src/yy/y.tab.c"
    break;

  case 47:
#line 141 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_LE_EXPR); }
#line 2091 "src/yy/y.tab.c"
    break;

  case 48:
#line 142 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_GE_EXPR); }
#line 2097 "src/yy/y.tab.c"
    break;

  case 50:
#line 147 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_EQ_EXPR); }
#line 2103 "src/yy/y.tab.c"
    break;

  case 51:
#line 148 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_NQ_EXPR); }
#line 2109 "src/yy/y.tab.c"
    break;

  case 53:
#line 153 "spec/parser_spec.y"
                                                 { BitExpr(BIT_AND_EXPR); }
#line 2115 "src/yy/y.tab.c"
    break;

  case 55:
#line 158 "spec/parser_spec.y"
                                                     { BitExpr(BIT_XOR_EXPR); }
#line 2121 "src/yy/y.tab.c"
    break;

  case 57:
#line 163 "spec/parser_spec.y"
                                                              { BitExpr(BIT_OR_EXPR); }
#line 2127 "src/yy/y.tab.c"
    break;

  case 59:
#line 168 "spec/parser_spec.y"
                                                                { LogExpr(LOG_AND_EXPR); }
#line 2133 "src/yy/y.tab.c"
    break;

  case 61:
#line 173 "spec/parser_spec.y"
                                                                { LogExpr(LOG_OR_EXPR); }
#line 2139 "src/yy/y.tab.c"
    break;

  case 63:
#line 178 "spec/parser_spec.y"
                                                                          { CondExpr(); }
#line 2145 "src/yy/y.tab.c"
    break;

  case 65:
#line 183 "spec/parser_spec.y"
                                                                                        { BasicAssignExpr(0); }
#line 2151 "src/yy/y.tab.c"
    break;

  case 66:
#line 184 "spec/parser_spec.y"
                                                                        { MulAssignExpr(MUL_ASSIGN_EXPR); }
#line 2157 "src/yy/y.tab.c"
    break;

  case 67:
#line 185 "spec/parser_spec.y"
                                                                        { MulAssignExpr(DIV_ASSIGN_EXPR); }
#line 2163 "src/yy/y.tab.c"
    break;

  case 68:
#line 186 "spec/parser_spec.y"
                                                                        { MulAssignExpr(MOD_ASSIGN_EXPR); }
#line 2169 "src/yy/y.tab.c"
    break;

  case 69:
#line 187 "spec/parser_spec.y"
                                                                        { AddAssignExpr(); }
#line 2175 "src/yy/y.tab.c"
    break;

  case 70:
#line 188 "spec/parser_spec.y"
                                                                        { SubAssignExpr(); }
#line 2181 "src/yy/y.tab.c"
    break;

  case 71:
#line 189 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_LEFT_ASSIGN_EXPR); }
#line 2187 "src/yy/y.tab.c"
    break;

  case 72:
#line 190 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_RIGHT_ASSIGN_EXPR); }
#line 2193 "src/yy/y.tab.c"
    break;

  case 73:
#line 191 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_AND_ASSIGN_EXPR); }
#line 2199 "src/yy/y.tab.c"
    break;

  case 74:
#line 192 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_XOR_ASSIGN_EXPR); }
#line 2205 "src/yy/y.tab.c"
    break;

  case 75:
#line 193 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_OR_ASSIGN_EXPR); }
#line 2211 "src/yy/y.tab.c"
    break;

  case 76:
#line 197 "spec/parser_spec.y"
                                { CommaExprOpen(); }
#line 2217 "src/yy/y.tab.c"
    break;

  case 77:
#line 198 "spec/parser_spec.y"
                                                      { CommaExpr(); }
#line 2223 "src/yy/y.tab.c"
    break;

  case 78:
#line 202 "spec/parser_spec.y"
                            { FullExpr(); }
#line 2229 "src/yy/y.tab.c"
    break;

  case 79:
#line 206 "spec/parser_spec.y"
                                 { ConstExpression(); }
#line 2235 "src/yy/y.tab.c"
    break;

  case 80:
#line 210 "spec/parser_spec.y"
                                       { Declaration(); }
#line 2241 "src/yy/y.tab.c"
    break;

  case 81:
#line 211 "spec/parser_spec.y"
                                                               { Declaration(); }
#line 2247 "src/yy/y.tab.c"
    break;

  case 82:
#line 215 "spec/parser_spec.y"
                                        { RedeclarationSpecifiers(); }
#line 2253 "src/yy/y.tab.c"
    break;

  case 83:
#line 219 "spec/parser_spec.y"
                                        { FullDeclarationSpecifiers(); }
#line 2259 "src/yy/y.tab.c"
    break;

  case 92:
#line 237 "spec/parser_spec.y"
                                                                                                                                        { NotFunctionDefinition(); }
#line 2265 "src/yy/y.tab.c"
    break;

  case 93:
#line 238 "spec/parser_spec.y"
                                                  { NotFunctionDefinition(); FullInitialization(); }
#line 2271 "src/yy/y.tab.c"
    break;

  case 94:
#line 242 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(TYPEDEF); }
#line 2277 "src/yy/y.tab.c"
    break;

  case 95:
#line 243 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(EXTERN); }
#line 2283 "src/yy/y.tab.c"
    break;

  case 96:
#line 244 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(STATIC); }
#line 2289 "src/yy/y.tab.c"
    break;

  case 97:
#line 245 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(AUTO); }
#line 2295 "src/yy/y.tab.c"
    break;

  case 98:
#line 246 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(REGISTER); }
#line 2301 "src/yy/y.tab.c"
    break;

  case 99:
#line 250 "spec/parser_spec.y"
                                        { TypeSpecifierRef(VOID); }
#line 2307 "src/yy/y.tab.c"
    break;

  case 100:
#line 251 "spec/parser_spec.y"
                                        { TypeSpecifierRef(CHAR); }
#line 2313 "src/yy/y.tab.c"
    break;

  case 101:
#line 252 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SHORT); }
#line 2319 "src/yy/y.tab.c"
    break;

  case 102:
#line 253 "spec/parser_spec.y"
                                        { TypeSpecifierRef(INT); }
#line 2325 "src/yy/y.tab.c"
    break;

  case 103:
#line 254 "spec/parser_spec.y"
                                        { TypeSpecifierRef(LONG); }
#line 2331 "src/yy/y.tab.c"
    break;

  case 104:
#line 255 "spec/parser_spec.y"
                                        { TypeSpecifierRef(FLOAT); }
#line 2337 "src/yy/y.tab.c"
    break;

  case 105:
#line 256 "spec/parser_spec.y"
                                        { TypeSpecifierRef(DOUBLE); }
#line 2343 "src/yy/y.tab.c"
    break;

  case 106:
#line 257 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SIGNED); }
#line 2349 "src/yy/y.tab.c"
    break;

  case 107:
#line 258 "spec/parser_spec.y"
                                { TypeSpecifierRef(UNSIGNED); }
#line 2355 "src/yy/y.tab.c"
    break;

  case 110:
#line 261 "spec/parser_spec.y"
                                { IdentifierName(); TypedefName(); }
#line 2361 "src/yy/y.tab.c"
    break;

  case 111:
#line 265 "spec/parser_spec.y"
                                                                                      { TagDefined(); }
#line 2367 "src/yy/y.tab.c"
    break;

  case 112:
#line 266 "spec/parser_spec.y"
                                                                             { TagDefined(); }
#line 2373 "src/yy/y.tab.c"
    break;

  case 113:
#line 267 "spec/parser_spec.y"
                                   { TagDeclared(); }
#line 2379 "src/yy/y.tab.c"
    break;

  case 114:
#line 271 "spec/parser_spec.y"
                          { TagTypeRef(TAG_STRUCT); }
#line 2385 "src/yy/y.tab.c"
    break;

  case 115:
#line 272 "spec/parser_spec.y"
                                { TagTypeRef(TAG_UNION); }
#line 2391 "src/yy/y.tab.c"
    break;

  case 116:
#line 276 "spec/parser_spec.y"
                     { IdentifierName(); }
#line 2397 "src/yy/y.tab.c"
    break;

  case 117:
#line 280 "spec/parser_spec.y"
                { TagDefOpen(); }
#line 2403 "src/yy/y.tab.c"
    break;

  case 118:
#line 284 "spec/parser_spec.y"
                { }
#line 2409 "src/yy/y.tab.c"
    break;

  case 121:
#line 293 "spec/parser_spec.y"
                                                              { Declaration(); }
#line 2415 "src/yy/y.tab.c"
    break;

  case 122:
#line 297 "spec/parser_spec.y"
                                          { FullDeclarationSpecifiers(); }
#line 2421 "src/yy/y.tab.c"
    break;

  case 130:
#line 319 "spec/parser_spec.y"
                                                                   { TagDefined(); }
#line 2427 "src/yy/y.tab.c"
    break;

  case 131:
#line 320 "spec/parser_spec.y"
                                                          { TagDefined(); }
#line 2433 "src/yy/y.tab.c"
    break;

  case 132:
#line 321 "spec/parser_spec.y"
                                                                       { TagDefined(); }
#line 2439 "src/yy/y.tab.c"
    break;

  case 133:
#line 322 "spec/parser_spec.y"
                                                              { TagDefined(); }
#line 2445 "src/yy/y.tab.c"
    break;

  case 134:
#line 323 "spec/parser_spec.y"
                        { TagDeclared(); }
#line 2451 "src/yy/y.tab.c"
    break;

  case 135:
#line 327 "spec/parser_spec.y"
                { TagTypeRef(TAG_ENUM); }
#line 2457 "src/yy/y.tab.c"
    break;

  case 138:
#line 336 "spec/parser_spec.y"
                          { EnumeratorDefault(); }
#line 2463 "src/yy/y.tab.c"
    break;

  case 139:
#line 337 "spec/parser_spec.y"
                                                  { EnumeratorCustom(); }
#line 2469 "src/yy/y.tab.c"
    break;

  case 140:
#line 341 "spec/parser_spec.y"
                                        { TypeQualifierRef(CONST); }
#line 2475 "src/yy/y.tab.c"
    break;

  case 141:
#line 342 "spec/parser_spec.y"
                                { TypeQualifierRef(VOLATILE); }
#line 2481 "src/yy/y.tab.c"
    break;

  case 142:
#line 346 "spec/parser_spec.y"
                            { Declarator(); }
#line 2487 "src/yy/y.tab.c"
    break;

  case 143:
#line 350 "spec/parser_spec.y"
                            { DeclaratorInitialized(); }
#line 2493 "src/yy/y.tab.c"
    break;

  case 144:
#line 354 "spec/parser_spec.y"
                            { Declarator(); IsFunctionDefinition(); }
#line 2499 "src/yy/y.tab.c"
    break;

  case 145:
#line 358 "spec/parser_spec.y"
                                    { NestedDeclarator(); }
#line 2505 "src/yy/y.tab.c"
    break;

  case 148:
#line 364 "spec/parser_spec.y"
                                    { }
#line 2511 "src/yy/y.tab.c"
    break;

  case 149:
#line 365 "spec/parser_spec.y"
                                                        { ArrayLengthDeclarator(); }
#line 2517 "src/yy/y.tab.c"
    break;

  case 150:
#line 366 "spec/parser_spec.y"
                                    { ArrayVariableDeclarator(); }
#line 2523 "src/yy/y.tab.c"
    break;

  case 151:
#line 367 "spec/parser_spec.y"
                                                                                           { FunctionDeclarator(); }
#line 2529 "src/yy/y.tab.c"
    break;

  case 152:
#line 368 "spec/parser_spec.y"
                                                                                       { FuncNonprototypeDeclarator(); }
#line 2535 "src/yy/y.tab.c"
    break;

  case 153:
#line 369 "spec/parser_spec.y"
                                                                       { FuncNonprototypeDeclarator(); }
#line 2541 "src/yy/y.tab.c"
    break;

  case 154:
#line 373 "spec/parser_spec.y"
                     { IdentifierName(); }
#line 2547 "src/yy/y.tab.c"
    break;

  case 155:
#line 377 "spec/parser_spec.y"
              { FunctionParamsOpen(); }
#line 2553 "src/yy/y.tab.c"
    break;

  case 156:
#line 381 "spec/parser_spec.y"
                { FunctionParamsClose(); }
#line 2559 "src/yy/y.tab.c"
    break;

  case 157:
#line 385 "spec/parser_spec.y"
              { PointerOpen(); }
#line 2565 "src/yy/y.tab.c"
    break;

  case 158:
#line 386 "spec/parser_spec.y"
                                  { PointerQualifierOpen();}
#line 2571 "src/yy/y.tab.c"
    break;

  case 159:
#line 387 "spec/parser_spec.y"
                      { Pointer(); }
#line 2577 "src/yy/y.tab.c"
    break;

  case 160:
#line 388 "spec/parser_spec.y"
                                          { PointerQualifier(); }
#line 2583 "src/yy/y.tab.c"
    break;

  case 164:
#line 398 "spec/parser_spec.y"
                                      { Ellipsis(); }
#line 2589 "src/yy/y.tab.c"
    break;

  case 167:
#line 407 "spec/parser_spec.y"
                                                 { Declaration(); }
#line 2595 "src/yy/y.tab.c"
    break;

  case 168:
#line 408 "spec/parser_spec.y"
                                                          { Declaration(); }
#line 2601 "src/yy/y.tab.c"
    break;

  case 169:
#line 409 "spec/parser_spec.y"
                                      { AbstractDeclarator(); Declaration(); }
#line 2607 "src/yy/y.tab.c"
    break;

  case 170:
#line 413 "spec/parser_spec.y"
                              { Declaration(); }
#line 2613 "src/yy/y.tab.c"
    break;

  case 171:
#line 414 "spec/parser_spec.y"
                                                  { Declaration(); }
#line 2619 "src/yy/y.tab.c"
    break;

  case 172:
#line 418 "spec/parser_spec.y"
                          { NonprototypeParam(); }
#line 2625 "src/yy/y.tab.c"
    break;

  case 173:
#line 422 "spec/parser_spec.y"
                                   { AbstractDeclarator(); NotFunctionDefinition(); Declaration(); }
#line 2631 "src/yy/y.tab.c"
    break;

  case 174:
#line 423 "spec/parser_spec.y"
                                                         { NotFunctionDefinition(); Declaration(); }
#line 2637 "src/yy/y.tab.c"
    break;

  case 175:
#line 427 "spec/parser_spec.y"
                                     { AbstractDeclarator(); }
#line 2643 "src/yy/y.tab.c"
    break;

  case 176:
#line 431 "spec/parser_spec.y"
                  { NestedDeclarator(); }
#line 2649 "src/yy/y.tab.c"
    break;

  case 178:
#line 433 "spec/parser_spec.y"
                                             { NestedDeclarator(); }
#line 2655 "src/yy/y.tab.c"
    break;

  case 179:
#line 437 "spec/parser_spec.y"
                                             { }
#line 2661 "src/yy/y.tab.c"
    break;

  case 180:
#line 438 "spec/parser_spec.y"
                  { ArrayVariableDeclarator(); }
#line 2667 "src/yy/y.tab.c"
    break;

  case 181:
#line 439 "spec/parser_spec.y"
                                       { ArrayLengthDeclarator(); }
#line 2673 "src/yy/y.tab.c"
    break;

  case 182:
#line 440 "spec/parser_spec.y"
                                              { ArrayVariableDeclarator(); }
#line 2679 "src/yy/y.tab.c"
    break;

  case 183:
#line 441 "spec/parser_spec.y"
                                                                  { ArrayLengthDeclarator(); }
#line 2685 "src/yy/y.tab.c"
    break;

  case 184:
#line 442 "spec/parser_spec.y"
                                                     { FuncNonprototypeDeclarator(); }
#line 2691 "src/yy/y.tab.c"
    break;

  case 185:
#line 443 "spec/parser_spec.y"
                                                                         { FunctionDeclarator(); }
#line 2697 "src/yy/y.tab.c"
    break;

  case 186:
#line 444 "spec/parser_spec.y"
                                                                                { FuncNonprototypeDeclarator(); }
#line 2703 "src/yy/y.tab.c"
    break;

  case 187:
#line 445 "spec/parser_spec.y"
                                                                                                    { FunctionDeclarator(); }
#line 2709 "src/yy/y.tab.c"
    break;

  case 188:
#line 449 "spec/parser_spec.y"
                                { Initializer(); }
#line 2715 "src/yy/y.tab.c"
    break;

  case 191:
#line 455 "spec/parser_spec.y"
              { InitializerOpen(); }
#line 2721 "src/yy/y.tab.c"
    break;

  case 192:
#line 459 "spec/parser_spec.y"
              { InitializerClose(); }
#line 2727 "src/yy/y.tab.c"
    break;

  case 202:
#line 478 "spec/parser_spec.y"
                        { Label(); }
#line 2733 "src/yy/y.tab.c"
    break;

  case 203:
#line 482 "spec/parser_spec.y"
                                    { CaseLabel(); }
#line 2739 "src/yy/y.tab.c"
    break;

  case 204:
#line 486 "spec/parser_spec.y"
                   { DefaultLabel(); }
#line 2745 "src/yy/y.tab.c"
    break;

  case 210:
#line 501 "spec/parser_spec.y"
              { BlockOpen(); }
#line 2751 "src/yy/y.tab.c"
    break;

  case 211:
#line 505 "spec/parser_spec.y"
              { BlockClose(); }
#line 2757 "src/yy/y.tab.c"
    break;

  case 218:
#line 524 "spec/parser_spec.y"
              { FuncBodyOpen(); }
#line 2763 "src/yy/y.tab.c"
    break;

  case 219:
#line 528 "spec/parser_spec.y"
              { FuncBodyClose(); }
#line 2769 "src/yy/y.tab.c"
    break;

  case 222:
#line 537 "spec/parser_spec.y"
                                                                { EmptyStmt(); }
#line 2775 "src/yy/y.tab.c"
    break;

  case 223:
#line 538 "spec/parser_spec.y"
                                { ExpressionStmt(); }
#line 2781 "src/yy/y.tab.c"
    break;

  case 224:
#line 542 "spec/parser_spec.y"
                        { IfOpen(); }
#line 2787 "src/yy/y.tab.c"
    break;

  case 225:
#line 546 "spec/parser_spec.y"
                        { ElseOpen(); }
#line 2793 "src/yy/y.tab.c"
    break;

  case 226:
#line 550 "spec/parser_spec.y"
                  { SwitchOpen(); }
#line 2799 "src/yy/y.tab.c"
    break;

  case 227:
#line 554 "spec/parser_spec.y"
                                                                                                                                                        { IfStmt(); }
#line 2805 "src/yy/y.tab.c"
    break;

  case 228:
#line 555 "spec/parser_spec.y"
                                                                                                { IfElseStmt(); }
#line 2811 "src/yy/y.tab.c"
    break;

  case 229:
#line 556 "spec/parser_spec.y"
                                                                                                                                                { SwitchStmt(); }
#line 2817 "src/yy/y.tab.c"
    break;

  case 230:
#line 560 "spec/parser_spec.y"
                        { WhileOpen(); }
#line 2823 "src/yy/y.tab.c"
    break;

  case 231:
#line 564 "spec/parser_spec.y"
                                { DoOpen(); }
#line 2829 "src/yy/y.tab.c"
    break;

  case 232:
#line 568 "spec/parser_spec.y"
                        { ForOpen(); }
#line 2835 "src/yy/y.tab.c"
    break;

  case 233:
#line 572 "spec/parser_spec.y"
                     { ControlExpression(); }
#line 2841 "src/yy/y.tab.c"
    break;

  case 234:
#line 576 "spec/parser_spec.y"
                      { ForDeclaration(); }
#line 2847 "src/yy/y.tab.c"
    break;

  case 235:
#line 581 "spec/parser_spec.y"
                         {  ForNoDeclaration(); ForExpression(); }
#line 2853 "src/yy/y.tab.c"
    break;

  case 236:
#line 582 "spec/parser_spec.y"
              { VoidExpr(); ForNoDeclaration(); ForExpression(); }
#line 2859 "src/yy/y.tab.c"
    break;

  case 237:
#line 586 "spec/parser_spec.y"
                     {  ForExpression(); }
#line 2865 "src/yy/y.tab.c"
    break;

  case 238:
#line 587 "spec/parser_spec.y"
          { VoidExpr(); ForExpression(); }
#line 2871 "src/yy/y.tab.c"
    break;

  case 239:
#line 592 "spec/parser_spec.y"
                                                                                                                                                                                                { WhileStmt(); }
#line 2877 "src/yy/y.tab.c"
    break;

  case 240:
#line 593 "spec/parser_spec.y"
                                                                                                                                                                                { DoWhileStmt(); }
#line 2883 "src/yy/y.tab.c"
    break;

  case 241:
#line 594 "spec/parser_spec.y"
                                                                                                        { ForStmt(); }
#line 2889 "src/yy/y.tab.c"
    break;

  case 242:
#line 595 "spec/parser_spec.y"
                                                                                            { ForStmt(); }
#line 2895 "src/yy/y.tab.c"
    break;

  case 243:
#line 599 "spec/parser_spec.y"
                                        { GotoStmt(); }
#line 2901 "src/yy/y.tab.c"
    break;

  case 244:
#line 600 "spec/parser_spec.y"
                                                                { ContinueStmt(); }
#line 2907 "src/yy/y.tab.c"
    break;

  case 245:
#line 601 "spec/parser_spec.y"
                                                                        { BreakStmt(); }
#line 2913 "src/yy/y.tab.c"
    break;

  case 246:
#line 602 "spec/parser_spec.y"
                                                                        { ReturnStmt(); }
#line 2919 "src/yy/y.tab.c"
    break;

  case 247:
#line 603 "spec/parser_spec.y"
                                        { ReturnExprStmt(); }
#line 2925 "src/yy/y.tab.c"
    break;

  case 248:
#line 607 "spec/parser_spec.y"
                         { StringPrimary(); }
#line 2931 "src/yy/y.tab.c"
    break;

  case 249:
#line 611 "spec/parser_spec.y"
                                      { InlineAssembly(); }
#line 2937 "src/yy/y.tab.c"
    break;

  case 252:
#line 620 "spec/parser_spec.y"
                               { TranslationUnit(); }
#line 2943 "src/yy/y.tab.c"
    break;

  case 253:
#line 621 "spec/parser_spec.y"
          { TranslationUnit(); }
#line 2949 "src/yy/y.tab.c"
    break;

  case 256:
#line 630 "spec/parser_spec.y"
                                                                                     {  }
#line 2955 "src/yy/y.tab.c"
    break;

  case 257:
#line 631 "spec/parser_spec.y"
                                                                        { }
#line 2961 "src/yy/y.tab.c"
    break;


#line 2965 "src/yy/y.tab.c"

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
#line 634 "spec/parser_spec.y"

#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	extern int row, column;
  printf("Unrecoverable syntax error: (%d,%d)\n", row, column);
	// fflush(stdout);
	// printf("\n%*s\n%*s\n", column, "^", column, s);
}
