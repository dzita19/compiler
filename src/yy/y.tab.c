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
	#include "decl/const_expr.h"
	#include "decl/initializer.h"

	#include "stmt/tree.h"
	#include "stmt/stmt.h"
	#include "stmt/literals.h"

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
#define YYLAST   1010

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  247
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  402

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
     231,   232,   236,   237,   241,   245,   249,   253,   254,   255,
     256,   257,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   276,   277,   278,   282,   283,   287,
     291,   295,   299,   300,   304,   308,   312,   313,   314,   315,
     319,   320,   324,   325,   326,   330,   331,   332,   333,   334,
     338,   342,   343,   347,   348,   352,   353,   357,   358,   362,
     363,   364,   365,   366,   367,   368,   372,   376,   380,   384,
     385,   386,   387,   391,   392,   396,   397,   401,   402,   406,
     407,   408,   412,   413,   417,   421,   422,   426,   430,   431,
     432,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     448,   449,   450,   454,   458,   462,   463,   467,   468,   469,
     470,   471,   472,   476,   480,   481,   482,   486,   487,   491,
     495,   499,   500,   504,   505,   509,   510,   514,   518,   522,
     523,   527,   528,   532,   536,   540,   544,   545,   546,   550,
     554,   558,   562,   563,   564,   565,   569,   570,   571,   572,
     573,   577,   578,   582,   586,   587,   591,   592
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
  "full_declarator", "full_declarator_initialized", "function_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "tag_name", "tag_def_open", "tag_def_close",
  "struct_declaration_list", "struct_declaration",
  "full_specifier_qualifier_list", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_specifier", "enum",
  "enumerator_list", "enumerator", "type_qualifier", "declarator",
  "direct_declarator", "declarator_name", "function_params_open",
  "function_params_close", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "function_param_name", "type_name",
  "full_abstract_declarator", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_open",
  "initializer_close", "initializer_list", "statement", "label",
  "labeled_statement", "compound_statement", "block_open", "block_close",
  "block", "block_item", "func_body", "func_body_open", "func_body_close",
  "declaration_list", "expression_statement", "if_open", "else_open",
  "switch_open", "selection_statement", "while_open", "do_open",
  "for_open", "iteration_statement", "jump_statement",
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
     315,    40,    41,    91,    93,    46,    44,    38,    42,    43,
      45,   126,    33,    47,    37,    60,    62,    94,   124,    63,
      58,    61,    59,   123,   125
};
# endif

#define YYPACT_NINF (-250)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-204)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     963,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,   -37,    71,     6,   963,   963,  -250,    43,  -250,
      43,   963,   963,    99,  -250,  -250,  -250,  -250,    71,    30,
       2,  -250,  -250,    46,   851,   116,    -7,  -250,    68,  -250,
    -250,  -250,  -250,    27,   882,    27,   121,  -250,  -250,  -250,
      75,  -250,  -250,    30,    71,  -250,   576,  -250,  -250,    71,
    -250,   331,   851,  -250,   630,   802,    -7,   882,   882,   831,
    -250,    21,  -250,   882,   121,   -17,  -250,    65,  -250,  -250,
    -250,  -250,   114,  -250,  -250,  -250,   745,   757,   757,   745,
     745,   745,   745,   745,   745,   745,  -250,  -250,   228,   327,
     882,  -250,    70,    64,   182,   192,   235,   133,   129,   150,
     209,    17,  -250,  -250,  -250,   576,   153,   745,   159,  -250,
    -250,  -250,  -250,  -250,   227,   162,   169,   251,  -250,  -250,
    -250,  -250,   203,   191,  -250,  -250,   204,  -250,  -250,   401,
     199,   489,  -250,  -250,   224,   226,  -250,   229,   559,   231,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,   232,  -250,    67,
    -250,  -250,  -250,   233,   222,  -250,   147,  -250,   831,  -250,
    -250,  -250,  -250,   745,   217,    13,  -250,  -250,  -250,    -1,
      24,  -250,   745,  -250,   882,   745,  -250,  -250,   236,  -250,
    -250,  -250,  -250,  -250,  -250,   297,  -250,  -250,  -250,   745,
     297,   647,   745,   745,   745,   745,   745,   745,   745,   745,
     745,   745,   745,    -4,   239,   745,   745,   745,   745,   745,
     745,   745,   745,   745,   745,   745,   745,   745,   745,   745,
     745,   745,   745,   745,  -250,    10,   225,   559,   220,  -250,
    -250,  -250,   234,   745,  -250,   559,  -250,  -250,   230,  -250,
    -250,   745,   745,   745,   250,   593,  -250,    67,   663,  -250,
     907,    58,  -250,  -250,    84,  -250,   942,   121,  -250,  -250,
    -250,   745,    21,  -250,    24,  -250,  -250,  -250,  -250,   239,
    -250,  -250,  -250,   242,  -250,  -250,  -250,   155,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
      -4,   100,  -250,  -250,   745,  -250,  -250,  -250,    70,    70,
      64,    64,   182,   182,   182,   182,   192,   192,   235,   133,
     129,   150,   209,   237,   419,  -250,  -250,   559,  -250,  -250,
    -250,  -250,  -250,  -250,   246,   247,   248,   252,   593,   253,
    -250,   260,  -250,   233,    84,   675,   907,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,   745,  -250,  -250,   745,  -250,
    -250,  -250,   559,   559,   559,   745,   717,  -250,  -250,  -250,
    -250,   261,  -250,   233,  -250,  -250,   274,  -250,  -250,   265,
     559,   268,  -250,  -250,  -250,   559,   249,  -250,   559,  -250,
    -250,  -250
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   113,    97,    98,    99,   100,   101,   103,   104,   105,
     106,   109,   110,   107,   108,   145,   146,   102,   117,   118,
     140,   245,     0,     0,    83,    84,    86,   111,     0,   112,
       0,    88,   243,     0,   241,   244,    80,   156,     0,   159,
       0,    90,    92,     0,     0,    96,   148,   149,     0,    85,
      87,   119,   120,   116,     0,   139,     0,    89,   242,     1,
       0,   163,   161,   160,     0,    81,     0,   217,   219,     0,
     247,     0,     0,   157,     0,     0,   147,     0,   127,     0,
     122,     0,   125,   129,     0,     0,   141,   143,   150,   164,
     162,    91,    94,     2,     3,     4,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,   193,     6,    19,    32,
       0,    34,    38,    41,    44,    49,    52,    54,    56,    58,
      60,    62,    64,   190,    93,     0,     2,     0,     0,   223,
     225,   229,   230,   231,     0,     0,     0,     0,   221,   209,
     218,    76,    78,     0,   214,   213,     0,   197,   198,     0,
       0,   211,   215,   199,     0,     0,   200,     0,     0,     0,
     201,   202,   220,   246,   152,    32,    79,     0,   158,   171,
      83,   174,   155,     0,   165,   167,     0,   172,     0,   126,
     121,   115,   123,     0,   132,     0,   130,    94,   128,     0,
       0,   136,     0,    28,     0,     0,    20,    21,     0,    22,
      23,    24,    25,    26,    27,     0,    12,    13,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   195,     0,     0,     0,     0,   237,
     238,   239,     0,     0,   222,     0,   210,   207,     0,   216,
     212,     0,     0,     0,     0,     0,   151,   157,     0,   169,
       0,   178,   170,   177,   179,   153,     0,     0,   154,   114,
     133,     0,     0,   124,     0,   135,   138,   142,   144,     0,
       5,    14,    11,     0,    10,    16,     8,     0,    17,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    65,
     157,   178,   176,    31,     0,    35,    36,    37,    39,    40,
      42,    43,    47,    48,    45,    46,    50,    51,    53,    55,
      57,    59,    61,     0,     0,   194,   191,     0,   206,   236,
     240,    77,   204,   208,     0,     0,     0,     0,     0,     0,
     182,     0,   186,     0,   180,     0,     0,   166,   168,   173,
     134,   131,   137,    29,     7,     0,     9,    33,     0,   196,
     192,   205,     0,     0,     0,     0,     0,   181,   183,   187,
     184,     0,   188,     0,    18,    63,   226,   228,   232,     0,
       0,     0,   185,   189,   224,     0,     0,   234,     0,   227,
     233,   235
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,  -250,   128,  -250,    44,  -250,   -61,   259,    54,
     -85,    37,    49,    29,    45,   106,   118,   139,   142,   151,
    -250,   -69,   -62,  -250,   -47,   -80,    48,  -250,     0,   -24,
    -250,   330,   -56,  -250,  -250,  -250,     8,  -250,  -250,   365,
      47,   -74,   319,   -67,   -88,   111,  -250,   115,  -250,  -250,
     328,  -167,   164,    -9,   -39,    -6,   -43,  -145,   -33,  -250,
    -249,  -250,   135,  -250,   140,   255,   193,  -229,  -218,  -115,
    -250,    85,  -250,  -150,  -250,  -250,  -250,  -250,   160,    34,
    -250,   348,  -250,   271,  -250,  -239,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,   394,  -250
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   107,   108,   292,   211,   296,   297,   109,   110,   314,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   141,   142,   143,   167,   144,    22,    69,    24,
      40,    41,    42,    43,    44,    25,    26,    27,    28,    53,
      54,   181,    79,    80,    81,    82,   185,   186,    29,    30,
      85,    86,    31,   187,    46,    47,   270,   172,    48,    63,
     173,   174,   175,   176,   177,   224,   272,   273,   274,   124,
     125,   336,   245,   145,   146,   147,   148,   149,   257,   150,
     151,    70,    71,   152,    72,   153,   154,   395,   155,   156,
     157,   158,   159,   160,   161,    32,    33,    34,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    49,    50,    75,   123,   166,    62,    57,   264,    76,
     244,   191,   182,   165,    45,   199,   200,   201,   202,   203,
     204,   353,   223,   287,    37,   184,   348,    37,   275,    60,
      90,   278,    23,    75,   242,   193,   196,   197,   349,   165,
     165,   165,   165,   165,   165,    36,    51,   246,    21,   190,
      87,   170,   198,   354,    73,    92,    74,   310,   166,   268,
      92,    37,    78,   123,    39,   284,   165,   180,    64,   171,
      37,    37,    15,    16,    37,   169,   334,    56,    87,   282,
      21,   349,    38,   180,    65,    78,    78,    78,   -82,    39,
     252,    78,    68,   354,   335,   283,   243,   338,    39,    59,
      77,   183,    84,   280,   279,   342,   223,   383,   180,   376,
      52,   182,   288,   269,   166,   285,   286,   287,    78,   267,
     162,   268,   165,   166,    37,   352,    52,    66,   267,    38,
     268,   165,    38,   228,   229,    39,   271,    88,   225,    39,
     315,   316,   317,   226,   227,    73,   192,   355,   198,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   293,   268,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   -94,   258,    87,   260,    78,   371,   351,   179,
     311,   341,   230,   231,   188,   -95,   333,   -95,   -94,   166,
     238,   360,    78,    61,   232,   233,   239,   165,   379,   168,
     362,   382,   166,   277,   344,   345,   346,   295,    83,   369,
     165,   365,   386,   387,   388,   241,   184,    89,   240,   367,
     248,   356,    76,  -203,   271,   205,   206,   207,   393,   247,
     397,    83,    83,    83,   249,   399,   170,    83,   401,   236,
     237,   250,   170,   165,    93,    94,    95,    96,    60,    97,
      98,   322,   323,   324,   325,   318,   319,   234,   235,   253,
     169,   171,   123,   254,    83,   381,   169,   311,    87,   320,
     321,   326,   327,   140,   255,   261,   166,   262,   276,   208,
     263,   209,   265,   210,   165,   168,   266,   281,   290,   385,
     291,   313,   339,   384,   347,   337,   364,   165,   372,   373,
     374,   356,    99,   375,   256,   377,   340,   368,   100,   101,
     102,   103,   104,   105,   378,   392,   394,   396,   389,   391,
     398,   400,   170,   251,   126,    94,    95,    96,   294,    97,
      98,   366,    83,   363,   328,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   194,   169,   329,    83,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,   330,
     127,   128,   129,   331,   130,   131,   132,   133,   134,   135,
     136,   137,    99,   332,    91,    55,   178,   361,   100,   101,
     102,   103,   104,   105,   126,    94,    95,    96,   222,    97,
      98,   358,   189,   138,   139,   140,   312,   359,   343,   370,
     163,   259,    93,    94,    95,    96,    58,    97,    98,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,   289,
     127,   128,   129,     0,   130,   131,   132,   133,   134,   135,
     136,   137,    99,     0,     0,     0,     0,     0,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
      99,     0,     0,   138,   139,   256,   100,   101,   102,   103,
     104,   105,   126,    94,    95,    96,     0,    97,    98,     0,
       0,     0,   106,   335,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     0,   127,   128,
     129,     0,   130,   131,   132,   133,   134,   135,   136,   137,
      99,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,   105,   126,    94,    95,    96,     0,    97,    98,     0,
       0,   138,   139,     0,     0,     0,     0,     0,     0,    93,
      94,    95,    96,     0,    97,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    96,
       0,    97,    98,     0,     0,     0,     0,     0,   127,   128,
     129,     0,   130,   131,   132,   133,   134,   135,   136,   137,
      99,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,   105,     0,    93,    94,    95,    96,    99,    97,    98,
       0,   138,   139,   100,   101,   102,   103,   104,   105,     0,
      93,    94,    95,    96,    99,    97,    98,     0,     0,   106,
     100,   101,   102,   103,   104,   105,    93,    94,    95,    96,
       0,    97,    98,     0,     0,   138,     0,     0,    93,    94,
      95,    96,     0,    97,    98,     0,     0,     0,     0,     0,
       0,    99,     0,     0,   164,     0,     0,   100,   101,   102,
     103,   104,   105,     0,     0,     0,     0,     0,    99,   295,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
      93,    94,    95,    96,    99,    97,    98,   350,     0,     0,
     100,   101,   102,   103,   104,   105,    99,     0,     0,   380,
       0,     0,   100,   101,   102,   103,   104,   105,    93,    94,
      95,    96,     0,    97,    98,     0,     0,     0,     0,     0,
      93,    94,    95,    96,     0,    97,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,   390,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    99,     0,     0,     0,
       0,     0,   100,   101,   102,   103,   104,   105,   195,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,   168,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,   180,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     0,     0,    67,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   168,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     357,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20
};

static const yytype_int16 yycheck[] =
{
       0,    25,    26,    46,    66,    74,    39,    31,   158,    48,
     125,    85,    79,    74,    23,   100,   101,   102,   103,   104,
     105,   270,   110,   190,     3,    81,   265,     3,   173,    38,
      63,   176,    32,    76,    17,    96,    97,    98,   267,   100,
     101,   102,   103,   104,   105,    82,     3,   127,     0,    66,
      56,    75,    99,   271,    61,    64,    63,    61,   127,    63,
      69,     3,    54,   125,    68,    66,   127,    84,    66,    75,
       3,     3,    42,    43,     3,    75,    66,    30,    84,    66,
      32,   310,    61,    84,    82,    77,    78,    79,    82,    68,
     137,    83,    44,   311,    84,    82,    79,   247,    68,     0,
      53,    80,    55,   183,   178,   255,   194,   356,    84,   348,
      83,   178,   192,   169,   183,   189,   190,   284,   110,    61,
      72,    63,   183,   192,     3,   270,    83,    81,    61,    61,
      63,   192,    61,    69,    70,    68,   169,    62,    68,    68,
     225,   226,   227,    73,    74,    61,    81,    63,   195,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,    61,   209,    63,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,    66,   149,   190,   151,   178,   337,   268,    78,
     223,   253,    10,    11,    83,    81,   243,    81,    82,   268,
      67,   281,   194,    39,    12,    13,    77,   268,   353,    62,
     284,   356,   281,    66,   261,   262,   263,    62,    54,   334,
     281,    66,   372,   373,   374,    16,   282,    63,    78,   314,
       3,   274,   271,    80,   267,     7,     8,     9,   383,    80,
     390,    77,    78,    79,    82,   395,   270,    83,   398,    14,
      15,    82,   276,   314,     3,     4,     5,     6,   267,     8,
       9,   232,   233,   234,   235,   228,   229,    75,    76,    66,
     270,   277,   334,    82,   110,   355,   276,   310,   284,   230,
     231,   236,   237,    84,    80,    61,   355,    61,    66,    61,
      61,    63,    61,    65,   355,    62,    64,    80,    62,   368,
       3,    62,    82,   365,    54,    80,    64,   368,    62,    62,
      62,   354,    61,    61,    84,    62,    82,    80,    67,    68,
      69,    70,    71,    72,    64,    64,    52,    62,   375,   376,
      62,    82,   356,    82,     3,     4,     5,     6,   210,     8,
       9,   297,   178,   289,   238,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    96,   356,   239,   194,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,   240,
      49,    50,    51,   241,    53,    54,    55,    56,    57,    58,
      59,    60,    61,   242,    64,    30,    77,   282,    67,    68,
      69,    70,    71,    72,     3,     4,     5,     6,    81,     8,
       9,   276,    84,    82,    83,    84,   223,   277,   258,   334,
      72,   150,     3,     4,     5,     6,    32,     8,     9,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,   194,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    82,    83,    84,    67,    68,    69,    70,
      71,    72,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    -1,     3,     4,     5,     6,    61,     8,     9,
      -1,    82,    83,    67,    68,    69,    70,    71,    72,    -1,
       3,     4,     5,     6,    61,     8,     9,    -1,    -1,    83,
      67,    68,    69,    70,    71,    72,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    82,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
       3,     4,     5,     6,    61,     8,     9,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,    61,    -1,    -1,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    61,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    62,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    84,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    83,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   111,   112,   113,   114,   120,   121,   122,   123,   133,
     134,   137,   180,   181,   182,   183,    82,     3,    61,    68,
     115,   116,   117,   118,   119,   138,   139,   140,   143,   114,
     114,     3,    83,   124,   125,   124,   125,   114,   182,     0,
     138,   137,   143,   144,    66,    82,    81,    83,   111,   113,
     166,   167,   169,    61,    63,   141,   139,   125,   121,   127,
     128,   129,   130,   137,   125,   135,   136,   140,    62,   137,
     143,   116,   138,     3,     4,     5,     6,     8,     9,    61,
      67,    68,    69,    70,    71,    72,    83,    86,    87,    92,
      93,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   154,   155,     3,    49,    50,    51,
      53,    54,    55,    56,    57,    58,    59,    60,    82,    83,
      84,   107,   108,   109,   111,   158,   159,   160,   161,   162,
     164,   165,   168,   170,   171,   173,   174,   175,   176,   177,
     178,   179,   111,   166,    64,    92,   106,   110,    62,   113,
     114,   140,   142,   145,   146,   147,   148,   149,   127,   130,
      84,   126,   128,    80,   117,   131,   132,   138,   130,   135,
      66,   126,    81,    92,    93,    61,    92,    92,   109,    95,
      95,    95,    95,    95,    95,     7,     8,     9,    61,    63,
      65,    89,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    81,   129,   150,    68,    73,    74,    69,    70,
      10,    11,    12,    13,    75,    76,    14,    15,    67,    77,
      78,    16,    17,    79,   154,   157,   110,    80,     3,    82,
      82,    82,   109,    66,    82,    80,    84,   163,   164,   168,
     164,    61,    61,    61,   158,    61,    64,    61,    63,   117,
     141,   143,   151,   152,   153,   142,    66,    66,   142,   126,
     110,    80,    66,    82,    66,   126,   126,   136,   110,   150,
      62,     3,    88,   109,    88,    62,    90,    91,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
      61,   143,   151,    62,    94,    95,    95,    95,    96,    96,
      97,    97,    98,    98,    98,    98,    99,    99,   100,   101,
     102,   103,   104,   109,    66,    84,   156,    80,   158,    82,
      82,   107,   158,   163,   109,   109,   109,    54,   170,   152,
      64,   110,   142,   145,   153,    63,   141,    48,   147,   149,
     110,   132,   126,    94,    64,    66,    90,    95,    80,   154,
     156,   158,    62,    62,    62,    61,   170,    62,    64,   142,
      64,   110,   142,   145,   107,   106,   158,   158,   158,   109,
      62,   109,    64,   142,    52,   172,    62,   158,    62,   158,
      82,   158
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
     115,   115,   116,   116,   117,   118,   119,   120,   120,   120,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   122,   123,   123,   124,
     125,   126,   127,   127,   128,   129,   130,   130,   130,   130,
     131,   131,   132,   132,   132,   133,   133,   133,   133,   133,
     134,   135,   135,   136,   136,   137,   137,   138,   138,   139,
     139,   139,   139,   139,   139,   139,   140,   141,   142,   143,
     143,   143,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   148,   148,   149,   150,   150,   151,   152,   152,
     152,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     154,   154,   154,   155,   156,   157,   157,   158,   158,   158,
     158,   158,   158,   159,   160,   160,   160,   161,   161,   162,
     163,   164,   164,   165,   165,   166,   166,   167,   168,   169,
     169,   170,   170,   171,   172,   173,   174,   174,   174,   175,
     176,   177,   178,   178,   178,   178,   179,   179,   179,   179,
     179,   180,   180,   181,   182,   182,   183,   183
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
       1,     1,     1,     1,     5,     4,     2,     1,     1,     1,
       1,     1,     1,     2,     3,     1,     2,     1,     2,     1,
       1,     3,     1,     2,     3,     5,     4,     6,     5,     2,
       1,     1,     3,     1,     3,     1,     1,     2,     1,     1,
       3,     4,     3,     4,     4,     3,     1,     1,     1,     1,
       2,     2,     3,     1,     2,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     1,     2,     1,     1,     1,
       2,     3,     2,     3,     3,     4,     2,     3,     3,     4,
       1,     3,     4,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     3,     2,     3,     1,
       1,     1,     2,     1,     1,     2,     3,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     5,     7,     5,     1,
       1,     1,     5,     7,     6,     7,     3,     2,     2,     2,
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
#line 56 "spec/parser_spec.y"
                                                        { IdentifierPrimary(); }
#line 1853 "src/yy/y.tab.c"
    break;

  case 3:
#line 57 "spec/parser_spec.y"
                                                                { ConstantPrimary(); }
#line 1859 "src/yy/y.tab.c"
    break;

  case 4:
#line 58 "spec/parser_spec.y"
                                                { StringPrimary(); }
#line 1865 "src/yy/y.tab.c"
    break;

  case 7:
#line 64 "spec/parser_spec.y"
                                                                                                                                                                { ArrayRefExpr(); }
#line 1871 "src/yy/y.tab.c"
    break;

  case 8:
#line 65 "spec/parser_spec.y"
                                                                                                                                                                { FunctionCallExpr(); }
#line 1877 "src/yy/y.tab.c"
    break;

  case 9:
#line 66 "spec/parser_spec.y"
                                                                                { FunctionCallExpr(); }
#line 1883 "src/yy/y.tab.c"
    break;

  case 10:
#line 67 "spec/parser_spec.y"
                                                                                                                                                                        { FieldRefExpr(); }
#line 1889 "src/yy/y.tab.c"
    break;

  case 11:
#line 68 "spec/parser_spec.y"
                                                                                                                                                                { PtrRefExpr(); }
#line 1895 "src/yy/y.tab.c"
    break;

  case 12:
#line 69 "spec/parser_spec.y"
                                                                                                                                                                                                        { IncDecExpr(POST_INC_EXPR); }
#line 1901 "src/yy/y.tab.c"
    break;

  case 13:
#line 70 "spec/parser_spec.y"
                                                                                                                                                                                                { IncDecExpr(POST_DEC_EXPR); }
#line 1907 "src/yy/y.tab.c"
    break;

  case 14:
#line 74 "spec/parser_spec.y"
                     { }
#line 1913 "src/yy/y.tab.c"
    break;

  case 15:
#line 78 "spec/parser_spec.y"
              { FunctionArgsOpen(); }
#line 1919 "src/yy/y.tab.c"
    break;

  case 16:
#line 82 "spec/parser_spec.y"
              { FunctionArgsClose(); }
#line 1925 "src/yy/y.tab.c"
    break;

  case 17:
#line 86 "spec/parser_spec.y"
                                                                                                                                                        { FunctionArg(); }
#line 1931 "src/yy/y.tab.c"
    break;

  case 18:
#line 87 "spec/parser_spec.y"
                                                                { FunctionArg(); }
#line 1937 "src/yy/y.tab.c"
    break;

  case 20:
#line 92 "spec/parser_spec.y"
                                        { IncDecExpr(PRE_INC_EXPR); }
#line 1943 "src/yy/y.tab.c"
    break;

  case 21:
#line 93 "spec/parser_spec.y"
                                        { IncDecExpr(PRE_DEC_EXPR); }
#line 1949 "src/yy/y.tab.c"
    break;

  case 22:
#line 94 "spec/parser_spec.y"
                                                        { AddressExpr(); }
#line 1955 "src/yy/y.tab.c"
    break;

  case 23:
#line 95 "spec/parser_spec.y"
                                                        { DerefExpr(); }
#line 1961 "src/yy/y.tab.c"
    break;

  case 24:
#line 96 "spec/parser_spec.y"
                                                        { UnaryExpr(UNARY_PLUS_EXPR); }
#line 1967 "src/yy/y.tab.c"
    break;

  case 25:
#line 97 "spec/parser_spec.y"
                                                        { UnaryExpr(UNARY_MINUS_EXPR); }
#line 1973 "src/yy/y.tab.c"
    break;

  case 26:
#line 98 "spec/parser_spec.y"
                                                        { BitNegExpr(); }
#line 1979 "src/yy/y.tab.c"
    break;

  case 27:
#line 99 "spec/parser_spec.y"
                                                        { LogNegExpr(); }
#line 1985 "src/yy/y.tab.c"
    break;

  case 28:
#line 100 "spec/parser_spec.y"
                                        { SizeofExpr(); }
#line 1991 "src/yy/y.tab.c"
    break;

  case 29:
#line 101 "spec/parser_spec.y"
                                                        { SizeofTypeExpr(); }
#line 1997 "src/yy/y.tab.c"
    break;

  case 30:
#line 105 "spec/parser_spec.y"
              { TypeOpen(); }
#line 2003 "src/yy/y.tab.c"
    break;

  case 31:
#line 109 "spec/parser_spec.y"
              { TypeClose(); }
#line 2009 "src/yy/y.tab.c"
    break;

  case 33:
#line 114 "spec/parser_spec.y"
                                                                { CastExpr(); }
#line 2015 "src/yy/y.tab.c"
    break;

  case 35:
#line 119 "spec/parser_spec.y"
                                                        { MulExpr(MUL_EXPR); }
#line 2021 "src/yy/y.tab.c"
    break;

  case 36:
#line 120 "spec/parser_spec.y"
                                                        { MulExpr(DIV_EXPR); }
#line 2027 "src/yy/y.tab.c"
    break;

  case 37:
#line 121 "spec/parser_spec.y"
                                                        { MulExpr(MOD_EXPR); }
#line 2033 "src/yy/y.tab.c"
    break;

  case 39:
#line 126 "spec/parser_spec.y"
                                                                { AddExpr(); }
#line 2039 "src/yy/y.tab.c"
    break;

  case 40:
#line 127 "spec/parser_spec.y"
                                                                { SubExpr(); }
#line 2045 "src/yy/y.tab.c"
    break;

  case 42:
#line 132 "spec/parser_spec.y"
                                                        { BitExpr(BIT_LEFT_EXPR); }
#line 2051 "src/yy/y.tab.c"
    break;

  case 43:
#line 133 "spec/parser_spec.y"
                                                        { BitExpr(BIT_RIGHT_EXPR); }
#line 2057 "src/yy/y.tab.c"
    break;

  case 45:
#line 138 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_LT_EXPR); }
#line 2063 "src/yy/y.tab.c"
    break;

  case 46:
#line 139 "spec/parser_spec.y"
                                                                        { RelationExpr(RELA_GT_EXPR); }
#line 2069 "src/yy/y.tab.c"
    break;

  case 47:
#line 140 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_LE_EXPR); }
#line 2075 "src/yy/y.tab.c"
    break;

  case 48:
#line 141 "spec/parser_spec.y"
                                                                { RelationExpr(RELA_GE_EXPR); }
#line 2081 "src/yy/y.tab.c"
    break;

  case 50:
#line 146 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_EQ_EXPR); }
#line 2087 "src/yy/y.tab.c"
    break;

  case 51:
#line 147 "spec/parser_spec.y"
                                                                { EqualityExpr(RELA_NE_EXPR); }
#line 2093 "src/yy/y.tab.c"
    break;

  case 53:
#line 152 "spec/parser_spec.y"
                                                 { BitExpr(BIT_AND_EXPR); }
#line 2099 "src/yy/y.tab.c"
    break;

  case 55:
#line 157 "spec/parser_spec.y"
                                                     { BitExpr(BIT_XOR_EXPR); }
#line 2105 "src/yy/y.tab.c"
    break;

  case 57:
#line 162 "spec/parser_spec.y"
                                                              { BitExpr(BIT_OR_EXPR); }
#line 2111 "src/yy/y.tab.c"
    break;

  case 59:
#line 167 "spec/parser_spec.y"
                                                                { LogExpr(LOG_AND_EXPR); }
#line 2117 "src/yy/y.tab.c"
    break;

  case 61:
#line 172 "spec/parser_spec.y"
                                                                { LogExpr(LOG_OR_EXPR); }
#line 2123 "src/yy/y.tab.c"
    break;

  case 63:
#line 177 "spec/parser_spec.y"
                                                                          { CondExpr(); }
#line 2129 "src/yy/y.tab.c"
    break;

  case 65:
#line 182 "spec/parser_spec.y"
                                                                                        { BasicAssignExpr(); }
#line 2135 "src/yy/y.tab.c"
    break;

  case 66:
#line 183 "spec/parser_spec.y"
                                                                        { MulAssignExpr(MUL_ASSIGN_EXPR); }
#line 2141 "src/yy/y.tab.c"
    break;

  case 67:
#line 184 "spec/parser_spec.y"
                                                                        { MulAssignExpr(DIV_ASSIGN_EXPR); }
#line 2147 "src/yy/y.tab.c"
    break;

  case 68:
#line 185 "spec/parser_spec.y"
                                                                        { MulAssignExpr(MOD_ASSIGN_EXPR); }
#line 2153 "src/yy/y.tab.c"
    break;

  case 69:
#line 186 "spec/parser_spec.y"
                                                                        { AddAssignExpr(); }
#line 2159 "src/yy/y.tab.c"
    break;

  case 70:
#line 187 "spec/parser_spec.y"
                                                                        { SubAssignExpr(); }
#line 2165 "src/yy/y.tab.c"
    break;

  case 71:
#line 188 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_LEFT_ASSIGN_EXPR); }
#line 2171 "src/yy/y.tab.c"
    break;

  case 72:
#line 189 "spec/parser_spec.y"
                                                                { BitAssignExpr(BIT_RIGHT_ASSIGN_EXPR); }
#line 2177 "src/yy/y.tab.c"
    break;

  case 73:
#line 190 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_AND_ASSIGN_EXPR); }
#line 2183 "src/yy/y.tab.c"
    break;

  case 74:
#line 191 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_XOR_ASSIGN_EXPR); }
#line 2189 "src/yy/y.tab.c"
    break;

  case 75:
#line 192 "spec/parser_spec.y"
                                                                        { BitAssignExpr(BIT_OR_ASSIGN_EXPR); }
#line 2195 "src/yy/y.tab.c"
    break;

  case 76:
#line 196 "spec/parser_spec.y"
                                { CommaExprOpen(); }
#line 2201 "src/yy/y.tab.c"
    break;

  case 77:
#line 197 "spec/parser_spec.y"
                                                   { CommaExpr(); }
#line 2207 "src/yy/y.tab.c"
    break;

  case 78:
#line 201 "spec/parser_spec.y"
                         { FullExpr(); }
#line 2213 "src/yy/y.tab.c"
    break;

  case 79:
#line 205 "spec/parser_spec.y"
                                 { ConstExpression(); }
#line 2219 "src/yy/y.tab.c"
    break;

  case 80:
#line 209 "spec/parser_spec.y"
                                       { Declaration(); }
#line 2225 "src/yy/y.tab.c"
    break;

  case 81:
#line 210 "spec/parser_spec.y"
                                                               { Declaration(); }
#line 2231 "src/yy/y.tab.c"
    break;

  case 82:
#line 214 "spec/parser_spec.y"
                                 { RedeclarationSpecifiers(); }
#line 2237 "src/yy/y.tab.c"
    break;

  case 83:
#line 218 "spec/parser_spec.y"
                                 { FullDeclarationSpecifiers(); }
#line 2243 "src/yy/y.tab.c"
    break;

  case 92:
#line 236 "spec/parser_spec.y"
                                                                                                                                                { }
#line 2249 "src/yy/y.tab.c"
    break;

  case 93:
#line 237 "spec/parser_spec.y"
                                                      { FullInitialization(); }
#line 2255 "src/yy/y.tab.c"
    break;

  case 94:
#line 241 "spec/parser_spec.y"
                     { NotFunctionDefinition(); Declarator(); }
#line 2261 "src/yy/y.tab.c"
    break;

  case 95:
#line 245 "spec/parser_spec.y"
                     { NotFunctionDefinition(); DeclaratorInitialized(); }
#line 2267 "src/yy/y.tab.c"
    break;

  case 96:
#line 249 "spec/parser_spec.y"
                     { Declarator(); NonprototypeRedeclaration(); }
#line 2273 "src/yy/y.tab.c"
    break;

  case 97:
#line 253 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(TYPEDEF); }
#line 2279 "src/yy/y.tab.c"
    break;

  case 98:
#line 254 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(EXTERN); }
#line 2285 "src/yy/y.tab.c"
    break;

  case 99:
#line 255 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(STATIC); }
#line 2291 "src/yy/y.tab.c"
    break;

  case 100:
#line 256 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(AUTO); }
#line 2297 "src/yy/y.tab.c"
    break;

  case 101:
#line 257 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(REGISTER); }
#line 2303 "src/yy/y.tab.c"
    break;

  case 102:
#line 261 "spec/parser_spec.y"
                                        { TypeSpecifierRef(VOID); }
#line 2309 "src/yy/y.tab.c"
    break;

  case 103:
#line 262 "spec/parser_spec.y"
                                        { TypeSpecifierRef(CHAR); }
#line 2315 "src/yy/y.tab.c"
    break;

  case 104:
#line 263 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SHORT); }
#line 2321 "src/yy/y.tab.c"
    break;

  case 105:
#line 264 "spec/parser_spec.y"
                                        { TypeSpecifierRef(INT); }
#line 2327 "src/yy/y.tab.c"
    break;

  case 106:
#line 265 "spec/parser_spec.y"
                                        { TypeSpecifierRef(LONG); }
#line 2333 "src/yy/y.tab.c"
    break;

  case 107:
#line 266 "spec/parser_spec.y"
                                        { TypeSpecifierRef(FLOAT); }
#line 2339 "src/yy/y.tab.c"
    break;

  case 108:
#line 267 "spec/parser_spec.y"
                                        { TypeSpecifierRef(DOUBLE); }
#line 2345 "src/yy/y.tab.c"
    break;

  case 109:
#line 268 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SIGNED); }
#line 2351 "src/yy/y.tab.c"
    break;

  case 110:
#line 269 "spec/parser_spec.y"
                                { TypeSpecifierRef(UNSIGNED); }
#line 2357 "src/yy/y.tab.c"
    break;

  case 113:
#line 272 "spec/parser_spec.y"
                                { IdentifierName(); TypedefName(); }
#line 2363 "src/yy/y.tab.c"
    break;

  case 114:
#line 276 "spec/parser_spec.y"
                                                                                      { TagDefined(); }
#line 2369 "src/yy/y.tab.c"
    break;

  case 115:
#line 277 "spec/parser_spec.y"
                                                                             { TagDefined(); }
#line 2375 "src/yy/y.tab.c"
    break;

  case 116:
#line 278 "spec/parser_spec.y"
                                   { TagDeclared(); }
#line 2381 "src/yy/y.tab.c"
    break;

  case 117:
#line 282 "spec/parser_spec.y"
                        { TagTypeRef(TAG_STRUCT); }
#line 2387 "src/yy/y.tab.c"
    break;

  case 118:
#line 283 "spec/parser_spec.y"
                                { TagTypeRef(TAG_UNION); }
#line 2393 "src/yy/y.tab.c"
    break;

  case 119:
#line 287 "spec/parser_spec.y"
                     { IdentifierName(); }
#line 2399 "src/yy/y.tab.c"
    break;

  case 120:
#line 291 "spec/parser_spec.y"
                { TagDefOpen(); }
#line 2405 "src/yy/y.tab.c"
    break;

  case 121:
#line 295 "spec/parser_spec.y"
                { }
#line 2411 "src/yy/y.tab.c"
    break;

  case 124:
#line 304 "spec/parser_spec.y"
                                                                   { Declaration(); }
#line 2417 "src/yy/y.tab.c"
    break;

  case 125:
#line 308 "spec/parser_spec.y"
                                   { FullDeclarationSpecifiers(); }
#line 2423 "src/yy/y.tab.c"
    break;

  case 135:
#line 330 "spec/parser_spec.y"
                                                                   { TagDefined(); }
#line 2429 "src/yy/y.tab.c"
    break;

  case 136:
#line 331 "spec/parser_spec.y"
                                                          { TagDefined(); }
#line 2435 "src/yy/y.tab.c"
    break;

  case 137:
#line 332 "spec/parser_spec.y"
                                                                       { TagDefined(); }
#line 2441 "src/yy/y.tab.c"
    break;

  case 138:
#line 333 "spec/parser_spec.y"
                                                              { TagDefined(); }
#line 2447 "src/yy/y.tab.c"
    break;

  case 139:
#line 334 "spec/parser_spec.y"
                        { TagDeclared(); }
#line 2453 "src/yy/y.tab.c"
    break;

  case 140:
#line 338 "spec/parser_spec.y"
                { TagTypeRef(TAG_ENUM); }
#line 2459 "src/yy/y.tab.c"
    break;

  case 143:
#line 347 "spec/parser_spec.y"
                          { EnumeratorDefault(); }
#line 2465 "src/yy/y.tab.c"
    break;

  case 144:
#line 348 "spec/parser_spec.y"
                                                  { EnumeratorCustom(); }
#line 2471 "src/yy/y.tab.c"
    break;

  case 145:
#line 352 "spec/parser_spec.y"
                                        { TypeQualifierRef(CONST); }
#line 2477 "src/yy/y.tab.c"
    break;

  case 146:
#line 353 "spec/parser_spec.y"
                                { TypeQualifierRef(VOLATILE); }
#line 2483 "src/yy/y.tab.c"
    break;

  case 147:
#line 357 "spec/parser_spec.y"
                                    { NestedDeclarator(); }
#line 2489 "src/yy/y.tab.c"
    break;

  case 150:
#line 363 "spec/parser_spec.y"
                             { }
#line 2495 "src/yy/y.tab.c"
    break;

  case 151:
#line 364 "spec/parser_spec.y"
                                                        { ArrayLengthDeclarator(); }
#line 2501 "src/yy/y.tab.c"
    break;

  case 152:
#line 365 "spec/parser_spec.y"
                                    { ArrayVariableDeclarator(); }
#line 2507 "src/yy/y.tab.c"
    break;

  case 153:
#line 366 "spec/parser_spec.y"
                                                                                           { FunctionDeclarator(); }
#line 2513 "src/yy/y.tab.c"
    break;

  case 154:
#line 367 "spec/parser_spec.y"
                                                                                       { FuncNonprototypeDeclarator(); }
#line 2519 "src/yy/y.tab.c"
    break;

  case 155:
#line 368 "spec/parser_spec.y"
                                                                       { FuncNonprototypeDeclarator(); }
#line 2525 "src/yy/y.tab.c"
    break;

  case 156:
#line 372 "spec/parser_spec.y"
                     { IdentifierName(); }
#line 2531 "src/yy/y.tab.c"
    break;

  case 157:
#line 376 "spec/parser_spec.y"
              { FunctionParamsOpen(); }
#line 2537 "src/yy/y.tab.c"
    break;

  case 158:
#line 380 "spec/parser_spec.y"
                { FunctionParamsClose(); }
#line 2543 "src/yy/y.tab.c"
    break;

  case 159:
#line 384 "spec/parser_spec.y"
              { PointerOpen(); }
#line 2549 "src/yy/y.tab.c"
    break;

  case 160:
#line 385 "spec/parser_spec.y"
                                  { PointerQualifierOpen();}
#line 2555 "src/yy/y.tab.c"
    break;

  case 161:
#line 386 "spec/parser_spec.y"
                      { Pointer(); }
#line 2561 "src/yy/y.tab.c"
    break;

  case 162:
#line 387 "spec/parser_spec.y"
                                          { PointerQualifier(); }
#line 2567 "src/yy/y.tab.c"
    break;

  case 166:
#line 397 "spec/parser_spec.y"
                                      { Ellipsis(); }
#line 2573 "src/yy/y.tab.c"
    break;

  case 169:
#line 406 "spec/parser_spec.y"
                                                      { Declaration(); }
#line 2579 "src/yy/y.tab.c"
    break;

  case 170:
#line 407 "spec/parser_spec.y"
                                                               { Declaration(); }
#line 2585 "src/yy/y.tab.c"
    break;

  case 171:
#line 408 "spec/parser_spec.y"
                                      { AbstractDeclarator(); Declaration(); }
#line 2591 "src/yy/y.tab.c"
    break;

  case 172:
#line 412 "spec/parser_spec.y"
                              { Declaration(); }
#line 2597 "src/yy/y.tab.c"
    break;

  case 173:
#line 413 "spec/parser_spec.y"
                                                  { Declaration(); }
#line 2603 "src/yy/y.tab.c"
    break;

  case 174:
#line 417 "spec/parser_spec.y"
                          { NonprototypeParam(); }
#line 2609 "src/yy/y.tab.c"
    break;

  case 175:
#line 421 "spec/parser_spec.y"
                                        { AbstractDeclarator(); }
#line 2615 "src/yy/y.tab.c"
    break;

  case 176:
#line 422 "spec/parser_spec.y"
                                                                 { /*TypeName();*/ }
#line 2621 "src/yy/y.tab.c"
    break;

  case 177:
#line 426 "spec/parser_spec.y"
                              { AbstractDeclarator(); }
#line 2627 "src/yy/y.tab.c"
    break;

  case 178:
#line 430 "spec/parser_spec.y"
                  { NestedDeclarator(); }
#line 2633 "src/yy/y.tab.c"
    break;

  case 180:
#line 432 "spec/parser_spec.y"
                                             { NestedDeclarator(); }
#line 2639 "src/yy/y.tab.c"
    break;

  case 181:
#line 436 "spec/parser_spec.y"
                                      { }
#line 2645 "src/yy/y.tab.c"
    break;

  case 182:
#line 437 "spec/parser_spec.y"
                  { ArrayVariableDeclarator(); }
#line 2651 "src/yy/y.tab.c"
    break;

  case 183:
#line 438 "spec/parser_spec.y"
                                       { ArrayLengthDeclarator(); }
#line 2657 "src/yy/y.tab.c"
    break;

  case 184:
#line 439 "spec/parser_spec.y"
                                              { ArrayVariableDeclarator(); }
#line 2663 "src/yy/y.tab.c"
    break;

  case 185:
#line 440 "spec/parser_spec.y"
                                                                  { ArrayLengthDeclarator(); }
#line 2669 "src/yy/y.tab.c"
    break;

  case 186:
#line 441 "spec/parser_spec.y"
                                                     { FuncNonprototypeDeclarator(); }
#line 2675 "src/yy/y.tab.c"
    break;

  case 187:
#line 442 "spec/parser_spec.y"
                                                                         { FunctionDeclarator(); }
#line 2681 "src/yy/y.tab.c"
    break;

  case 188:
#line 443 "spec/parser_spec.y"
                                                                                { FuncNonprototypeDeclarator(); }
#line 2687 "src/yy/y.tab.c"
    break;

  case 189:
#line 444 "spec/parser_spec.y"
                                                                                                    { FunctionDeclarator(); }
#line 2693 "src/yy/y.tab.c"
    break;

  case 190:
#line 448 "spec/parser_spec.y"
                                { Initializer(); }
#line 2699 "src/yy/y.tab.c"
    break;

  case 193:
#line 454 "spec/parser_spec.y"
              { InitializerOpen(); }
#line 2705 "src/yy/y.tab.c"
    break;

  case 194:
#line 458 "spec/parser_spec.y"
              { InitializerClose(); }
#line 2711 "src/yy/y.tab.c"
    break;

  case 203:
#line 476 "spec/parser_spec.y"
                        { IdentifierName(); Label(); }
#line 2717 "src/yy/y.tab.c"
    break;

  case 204:
#line 480 "spec/parser_spec.y"
                                                                                                                        { LabelStmt(); }
#line 2723 "src/yy/y.tab.c"
    break;

  case 205:
#line 481 "spec/parser_spec.y"
                                                                { CaseStmt(); }
#line 2729 "src/yy/y.tab.c"
    break;

  case 206:
#line 482 "spec/parser_spec.y"
                                                                                                                { DefaultStmt(); }
#line 2735 "src/yy/y.tab.c"
    break;

  case 209:
#line 491 "spec/parser_spec.y"
              { BlockOpen(); }
#line 2741 "src/yy/y.tab.c"
    break;

  case 210:
#line 495 "spec/parser_spec.y"
              { BlockClose(); }
#line 2747 "src/yy/y.tab.c"
    break;

  case 217:
#line 514 "spec/parser_spec.y"
              { FuncBodyOpen(); }
#line 2753 "src/yy/y.tab.c"
    break;

  case 218:
#line 518 "spec/parser_spec.y"
              { FuncBodyClose(); }
#line 2759 "src/yy/y.tab.c"
    break;

  case 221:
#line 527 "spec/parser_spec.y"
                                                                { EmptyStmt(); }
#line 2765 "src/yy/y.tab.c"
    break;

  case 222:
#line 528 "spec/parser_spec.y"
                                { ExpressionStmt(); }
#line 2771 "src/yy/y.tab.c"
    break;

  case 223:
#line 532 "spec/parser_spec.y"
                        { IfOpen(); }
#line 2777 "src/yy/y.tab.c"
    break;

  case 224:
#line 536 "spec/parser_spec.y"
                        { ElseOpen(); }
#line 2783 "src/yy/y.tab.c"
    break;

  case 225:
#line 540 "spec/parser_spec.y"
                  { SwitchOpen(); }
#line 2789 "src/yy/y.tab.c"
    break;

  case 226:
#line 544 "spec/parser_spec.y"
                                                                                                                                                { IfStmt(); }
#line 2795 "src/yy/y.tab.c"
    break;

  case 227:
#line 545 "spec/parser_spec.y"
                                                                                        { IfElseStmt(); }
#line 2801 "src/yy/y.tab.c"
    break;

  case 228:
#line 546 "spec/parser_spec.y"
                                                                                                                                        { SwitchStmt(); }
#line 2807 "src/yy/y.tab.c"
    break;

  case 229:
#line 550 "spec/parser_spec.y"
                { WhileOpen(); }
#line 2813 "src/yy/y.tab.c"
    break;

  case 230:
#line 554 "spec/parser_spec.y"
                                { DoOpen(); }
#line 2819 "src/yy/y.tab.c"
    break;

  case 231:
#line 558 "spec/parser_spec.y"
                        { ForOpen(); }
#line 2825 "src/yy/y.tab.c"
    break;

  case 232:
#line 562 "spec/parser_spec.y"
                                                                                                                                                                                                                        { WhileStmt(); }
#line 2831 "src/yy/y.tab.c"
    break;

  case 233:
#line 563 "spec/parser_spec.y"
                                                                                                                                                                                                        { DoWhileStmt(); }
#line 2837 "src/yy/y.tab.c"
    break;

  case 234:
#line 564 "spec/parser_spec.y"
                                                                                                                                        { ForStmt(0); }
#line 2843 "src/yy/y.tab.c"
    break;

  case 235:
#line 565 "spec/parser_spec.y"
                                                                                                        { ForStmt(1); }
#line 2849 "src/yy/y.tab.c"
    break;

  case 236:
#line 569 "spec/parser_spec.y"
                                        { GotoStmt(); }
#line 2855 "src/yy/y.tab.c"
    break;

  case 237:
#line 570 "spec/parser_spec.y"
                                                                { ContinueStmt(); }
#line 2861 "src/yy/y.tab.c"
    break;

  case 238:
#line 571 "spec/parser_spec.y"
                                                                        { BreakStmt(); }
#line 2867 "src/yy/y.tab.c"
    break;

  case 239:
#line 572 "spec/parser_spec.y"
                                                                        { ReturnStmt(); }
#line 2873 "src/yy/y.tab.c"
    break;

  case 240:
#line 573 "spec/parser_spec.y"
                                        { ReturnExprStmt(); }
#line 2879 "src/yy/y.tab.c"
    break;

  case 243:
#line 582 "spec/parser_spec.y"
                               { TranslationUnit(); }
#line 2885 "src/yy/y.tab.c"
    break;

  case 246:
#line 591 "spec/parser_spec.y"
                                                                                     {  }
#line 2891 "src/yy/y.tab.c"
    break;

  case 247:
#line 592 "spec/parser_spec.y"
                                                                        { }
#line 2897 "src/yy/y.tab.c"
    break;


#line 2901 "src/yy/y.tab.c"

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
#line 595 "spec/parser_spec.y"

#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
