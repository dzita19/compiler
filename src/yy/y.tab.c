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
	#include "stmt/production.h"

	#include "decl/declarations.h"

	#include "symtab/obj.h"
	#include "symtab/struct.h"

	extern int yylex (void);
	void yyerror(char* s);

#line 84 "src/yy/y.tab.c"

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
#line 15 "spec/parser_spec.y"

	int num;
	char* id;
	char* string_literal;

#line 203 "src/yy/y.tab.c"

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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1087

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  220
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  374

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
       0,    36,    36,    37,    38,    39,    43,    44,    45,    46,
      47,    48,    49,    50,    54,    55,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    73,    74,    78,
      79,    80,    81,    85,    86,    87,    91,    92,    93,    97,
      98,    99,   100,   101,   105,   106,   107,   111,   112,   116,
     117,   121,   122,   126,   127,   131,   132,   136,   137,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   156,   157,   161,   165,   166,   170,   171,   172,   173,
     174,   175,   179,   180,   184,   185,   189,   190,   191,   192,
     193,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   212,   213,   214,   218,   219,   223,   227,
     231,   235,   236,   240,   244,   245,   246,   247,   251,   252,
     256,   257,   258,   262,   263,   264,   268,   272,   273,   277,
     278,   282,   283,   287,   288,   292,   293,   294,   295,   296,
     297,   298,   302,   306,   310,   314,   315,   316,   317,   321,
     322,   326,   327,   331,   332,   336,   337,   338,   342,   343,
     347,   351,   352,   356,   357,   358,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   374,   375,   376,   380,   381,
     385,   386,   387,   388,   389,   390,   394,   395,   396,   400,
     401,   402,   403,   407,   410,   413,   414,   418,   419,   423,
     424,   428,   429,   430,   434,   435,   436,   437,   441,   442,
     443,   444,   445,   449,   450,   454,   455,   459,   460,   461,
     462
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
  "argument_expression_list", "unary_expression", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "tag_name", "tag_def_open", "tag_def_close", "struct_declaration_list",
  "struct_declaration", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_specifier", "enum",
  "enumerator_list", "enumerator", "type_qualifier", "declarator",
  "direct_declarator", "declarator_name", "function_params_open",
  "function_params_close", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "function_param_name", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "block_begin", "block_end", "declaration_list",
  "statement_list", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
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

#define YYPACT_NINF (-247)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     813,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,    69,   182,  -247,    49,  1040,  1040,  -247,     2,
    -247,     2,  1040,   963,   -38,  -247,    41,   768,  -247,  -247,
     -27,  -247,  -247,   182,  -247,    68,  -247,   907,  -247,  -247,
    -247,  -247,   -52,   938,   -52,    95,  -247,  -247,  -247,    49,
    -247,   313,   963,  -247,   571,   858,   -38,  -247,  -247,  -247,
    -247,  -247,    69,  -247,   419,  -247,   963,   938,   938,   887,
    -247,    58,   938,    95,    82,  -247,    27,    30,    67,  -247,
    -247,   686,   723,   723,   756,   110,   173,   181,   198,   455,
     201,   141,   188,   208,   473,   559,   756,   756,   756,   756,
     756,   756,  -247,  -247,  -247,   190,   393,  -247,   184,    84,
     235,    37,   265,   225,   199,   223,   286,     4,  -247,  -247,
     146,  -247,  -247,  -247,  -247,   313,   383,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,   239,  -247,    10,
    -247,  -247,   242,   240,  -247,    83,  -247,  -247,   419,  -247,
    -247,  -247,   887,  -247,  -247,  -247,  -247,   756,   149,  -247,
     227,  -247,    82,    95,  -247,   756,   455,   559,  -247,   756,
    -247,  -247,   228,   455,   756,   756,   756,   255,   489,   230,
    -247,  -247,  -247,   156,   134,    -1,   248,  -247,  -247,  -247,
    -247,  -247,  -247,   310,  -247,  -247,   604,   756,   312,   756,
     756,   756,   756,   756,   756,   756,   756,   756,   756,   756,
     756,   756,   756,   756,   756,   756,   756,   756,   756,   756,
     756,   756,   756,   756,   756,   756,   756,   756,   756,   756,
    -247,  -247,   383,  -247,  -247,  -247,    10,   641,  -247,   983,
     130,  -247,     3,  -247,  1019,    95,  -247,  -247,   136,  -247,
    -247,    58,  -247,   756,  -247,  -247,  -247,  -247,   261,   455,
    -247,   164,   194,   202,   263,   489,  -247,  -247,  -247,    -1,
      40,  -247,   756,  -247,  -247,   203,  -247,   143,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,   184,   184,    84,    84,   235,   235,   235,
     235,    37,    37,   265,   225,   199,   223,   286,    -3,  -247,
    -247,   264,  -247,   266,  -247,   242,     3,   653,   983,  -247,
    -247,  -247,   401,  -247,  -247,  -247,  -247,  -247,   455,   455,
     455,   756,   674,  -247,  -247,   756,  -247,   756,  -247,  -247,
    -247,  -247,   267,  -247,   242,  -247,  -247,   273,  -247,  -247,
     209,   455,   211,  -247,  -247,  -247,  -247,   455,   245,  -247,
     455,  -247,  -247,  -247
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   142,   102,    86,    87,    88,    89,    90,    92,    93,
      94,    95,    98,    99,    96,    97,   131,   132,    91,   106,
     107,   126,     0,   145,   216,     0,    76,    78,   100,     0,
     101,     0,    80,     0,   134,   135,     0,     0,   213,   215,
       0,   149,   147,   146,    74,     0,    82,    84,    77,    79,
     108,   109,   105,     0,   125,     0,    81,   193,   195,     0,
     220,     0,     0,   143,     0,     0,   133,     1,   214,   136,
     150,   148,     0,    75,     0,   218,     0,     0,   115,     0,
     111,     0,   117,     0,     0,   127,   129,    84,     2,     3,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   199,   194,     6,    16,    27,    29,    33,    36,
      39,    44,    47,    49,    51,    53,    55,    57,    59,    71,
       0,   197,   180,   181,   189,     0,     0,   182,   183,   184,
     185,   196,   219,     2,   138,    27,    73,     0,   144,   157,
     160,   141,     0,   151,   153,     0,   158,    83,     0,   175,
      85,   217,     0,   114,   110,   104,   112,     0,     0,   118,
     120,   116,     0,     0,   124,     0,     0,     0,    25,     0,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
     209,   210,   211,     0,     0,   161,     0,    19,    20,    21,
      22,    23,    24,     0,    12,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     200,   191,     0,   198,   190,   137,   143,     0,   155,     0,
     163,   156,   164,   139,     0,     0,   140,   178,     0,   103,
     121,     0,   113,     0,   123,   128,   130,   186,     0,     0,
     188,     0,     0,     0,     0,     0,   208,   212,     5,   143,
     163,   162,     0,    11,     8,     0,    14,     0,    10,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    60,
      30,    31,    32,    34,    35,    37,    38,    42,    43,    40,
      41,    45,    46,    48,    50,    52,    54,    56,     0,    72,
     192,     0,   167,     0,   171,     0,   165,     0,     0,   152,
     154,   159,     0,   176,   119,   122,    26,   187,     0,     0,
       0,     0,     0,    28,     9,     0,     7,     0,   166,   168,
     172,   169,     0,   173,     0,   177,   179,   201,   203,   204,
       0,     0,     0,    15,    58,   170,   174,     0,     0,   206,
       0,   202,   205,   207
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -247,  -247,  -247,  -247,   -53,   -16,    62,    63,    70,    64,
      96,    98,    99,    97,   100,  -247,   -60,   -54,   -98,   -46,
       8,     0,  -247,   268,  -247,   158,  -247,  -247,   305,    87,
     -66,   262,   -62,   -31,  -247,    77,  -247,  -247,   278,   192,
      46,   -13,   -34,   -41,   -33,  -133,    -7,  -247,  -246,  -247,
     121,  -247,   122,   213,  -119,  -175,  -143,  -247,   -56,  -247,
     185,  -247,  -107,   180,   241,  -178,  -247,  -247,  -247,  -247,
     341,  -247
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   114,   115,   285,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   147,
      58,    59,    45,    46,    26,    27,    28,    29,    52,    53,
     165,    79,    80,    81,   168,   169,    30,    31,    84,    85,
      32,    33,    34,    35,   249,   151,    36,    43,   152,   153,
     154,   155,   156,   196,   321,   252,   160,   258,   131,   132,
     133,    61,   134,    62,   136,   137,   138,   139,   140,    37,
      38,    39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,    65,    66,   325,   146,    50,   193,   194,    24,    40,
     275,   145,    47,     1,    86,   257,    42,   166,   174,   253,
     159,   237,   256,    63,   150,    64,    48,    49,   241,   244,
     251,    51,    56,    65,   146,    69,    71,    25,   178,   180,
     181,   145,    86,   187,     1,    24,    87,   163,   182,   227,
     228,   171,     1,   145,   145,   145,   145,   145,   145,    87,
     279,     1,   247,   239,    63,   149,   327,    23,   170,    41,
     141,   246,     1,   247,   195,   326,   281,   347,    23,   194,
     243,   194,   354,   238,   141,    51,   271,   272,   273,    70,
     197,   198,   199,   200,   201,   202,   259,   342,     1,    82,
     166,   279,    22,   247,   159,   326,   264,   146,   175,   287,
      22,    74,   229,   230,   145,   146,   324,    23,    55,    22,
     267,   260,   145,    82,    82,    82,    23,   270,    82,   266,
      22,    44,    86,     1,    72,   320,   248,    23,   167,    77,
     318,    83,   250,   141,   189,   148,   195,   176,   173,   255,
      73,    82,   286,   223,   224,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   164,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   319,   243,   146,   280,   356,
     183,   246,   350,   247,   145,   353,   278,   203,   204,   205,
     239,   323,   332,   146,   300,   301,   302,   346,    82,   239,
     145,    78,   239,   337,   150,   261,    66,   335,    60,   328,
     333,   366,   239,    82,    16,    17,   338,    76,   240,   145,
     239,   262,    75,    40,   184,    78,    78,    78,   277,   250,
      78,   135,   185,   360,   362,   225,   226,   142,   170,   149,
      23,   206,   220,   207,   149,   208,   339,   221,   222,   186,
     239,   161,   188,    78,   340,   344,   343,   146,   239,   345,
     190,   368,   280,   370,   145,   239,   234,   239,   159,   231,
     232,   352,   357,   358,   359,   303,   304,   364,   305,   306,
     191,   363,   233,   328,   145,   311,   312,   307,   308,   309,
     310,   235,   236,   245,   148,   369,   254,   263,   269,   274,
     282,   371,   276,   283,   373,   288,    88,    89,    90,    91,
      78,    92,    93,   336,   341,   367,   348,   372,   149,   313,
     349,   365,   314,   316,   315,    78,    54,   317,   334,   162,
     157,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   172,    94,    95,    96,   265,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   330,   242,   331,    68,     0,
     106,   107,   108,   109,   110,   111,    88,    89,    90,    91,
     268,    92,    93,     0,     0,   112,    57,   113,     0,     0,
       0,     0,     0,     0,   143,    89,    90,    91,     0,    92,
      93,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,     0,   143,    89,    90,    91,     0,    92,    93,     0,
       0,     0,    94,    95,    96,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,     0,     0,    88,    89,
      90,    91,   105,    92,    93,   112,    57,   113,   106,   107,
     108,   109,   110,   111,   219,     0,   143,    89,    90,    91,
     105,    92,    93,     0,   158,   355,   106,   107,   108,   109,
     110,   111,   143,    89,    90,    91,     0,    92,    93,     0,
       0,     0,   158,     0,    94,    95,    96,     0,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,     0,     0,
       0,     0,   106,   107,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,   105,     0,     0,   112,    57,     0,
     106,   107,   108,   109,   110,   111,     0,     0,     0,     0,
     105,     0,     0,     0,     0,   192,   106,   107,   108,   109,
     110,   111,   143,    89,    90,    91,     0,    92,    93,     0,
       0,   112,     0,     0,   143,    89,    90,    91,     0,    92,
      93,     0,     0,     0,     0,     0,     0,     2,     0,     0,
       0,     0,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   143,    89,    90,
      91,     0,    92,    93,     0,     0,     0,     0,     0,     0,
     105,     0,     0,     0,     0,     0,   106,   107,   108,   109,
     110,   111,   105,     0,     0,   144,     0,     0,   106,   107,
     108,   109,   110,   111,   143,    89,    90,    91,     0,    92,
      93,     0,     0,     0,     0,     0,   143,    89,    90,    91,
       0,    92,    93,     0,     0,   105,   284,     0,     0,     0,
       0,   106,   107,   108,   109,   110,   111,   143,    89,    90,
      91,     0,    92,    93,     0,     0,     0,     0,     0,   143,
      89,    90,    91,     0,    92,    93,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   322,     0,     0,   106,   107,
     108,   109,   110,   111,   105,     0,     0,   351,     0,     0,
     106,   107,   108,   109,   110,   111,   143,    89,    90,    91,
       0,    92,    93,     0,     0,   105,   361,     0,     0,     0,
       0,   106,   107,   108,   109,   110,   111,   177,     0,     0,
       0,     0,     0,   106,   107,   108,   109,   110,   111,   143,
      89,    90,    91,     0,    92,    93,     0,     0,    67,     0,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     1,   105,     0,     0,
       0,     0,     0,   106,   107,   108,   109,   110,   111,    22,
       0,     0,     0,     0,     0,     0,    23,     0,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,     0,     0,
       0,    23,     0,     0,     0,     0,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     0,     0,     0,     0,
     148,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,   164,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     0,     0,    74,     0,
      57,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148,    57,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   329,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
       0,    34,    36,   249,    64,     3,   104,   105,     0,    22,
     188,    64,    25,     3,    55,   158,    23,    79,    84,   152,
      74,    17,   155,    61,    65,    63,    26,    27,   135,   136,
     149,    83,    32,    66,    94,    62,    43,    37,    91,    92,
      93,    94,    83,    99,     3,    37,    59,    78,    94,    12,
      13,    82,     3,   106,   107,   108,   109,   110,   111,    72,
      61,     3,    63,    66,    61,    65,    63,    68,    81,    23,
      62,    61,     3,    63,   105,   250,   195,    80,    68,   177,
     136,   179,   328,    79,    76,    83,   184,   185,   186,    43,
     106,   107,   108,   109,   110,   111,   162,   275,     3,    53,
     162,    61,    61,    63,   158,   280,   172,   167,    81,   207,
      61,    81,    75,    76,   167,   175,   249,    68,    31,    61,
     176,   167,   175,    77,    78,    79,    68,   183,    82,   175,
      61,    82,   173,     3,    66,   242,   149,    68,    80,    52,
     238,    54,   149,   135,     3,    62,   177,    80,    66,    66,
      82,   105,   206,    69,    70,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,    84,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   239,   242,   247,   195,   332,
      80,    61,   325,    63,   247,   328,    62,     7,     8,     9,
      66,   247,    66,   263,   220,   221,   222,    64,   162,    66,
     263,    53,    66,   269,   255,    66,   250,   263,    33,   252,
      84,   354,    66,   177,    42,    43,    62,    47,    82,   282,
      66,    82,    47,   246,    61,    77,    78,    79,    82,   246,
      82,    61,    61,   341,   342,    10,    11,    62,   261,   249,
      68,    61,    68,    63,   254,    65,    62,    73,    74,    61,
      66,    76,    61,   105,    62,    62,   282,   327,    66,    66,
      82,    62,   279,    62,   327,    66,    77,    66,   332,    14,
      15,   327,   338,   339,   340,   223,   224,   347,   225,   226,
      82,   345,    67,   326,   347,   231,   232,   227,   228,   229,
     230,    78,    16,    64,    62,   361,    66,    80,    80,    54,
      62,   367,    82,     3,   370,     3,     3,     4,     5,     6,
     162,     8,     9,    62,    61,    52,    62,    82,   328,   233,
      64,    64,   234,   236,   235,   177,    31,   237,   261,    77,
      72,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    83,    49,    50,    51,   173,    53,    54,    55,    56,
      57,    58,    59,    60,    61,   254,   135,   255,    37,    -1,
      67,    68,    69,    70,    71,    72,     3,     4,     5,     6,
     177,     8,     9,    -1,    -1,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    -1,    -1,     3,     4,
       5,     6,    61,     8,     9,    82,    83,    84,    67,    68,
      69,    70,    71,    72,    81,    -1,     3,     4,     5,     6,
      61,     8,     9,    -1,    83,    84,    67,    68,    69,    70,
      71,    72,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    83,    -1,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    82,    83,    -1,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    82,    67,    68,    69,    70,
      71,    72,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    82,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      69,    70,    71,    72,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    69,    70,    71,    72,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,     0,    -1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     3,    61,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      62,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    84,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    81,    -1,
      83,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    83,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    61,    68,   105,   106,   109,   110,   111,   112,
     121,   122,   125,   126,   127,   128,   131,   154,   155,   156,
     126,   125,   131,   132,    82,   107,   108,   126,   106,   106,
       3,    83,   113,   114,   113,   114,   106,    83,   105,   106,
     145,   146,   148,    61,    63,   129,   127,     0,   155,    62,
     125,   131,    66,    82,    81,   145,   148,   114,   110,   116,
     117,   118,   125,   114,   123,   124,   128,   126,     3,     4,
       5,     6,     8,     9,    49,    50,    51,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    67,    68,    69,    70,
      71,    72,    82,    84,    86,    87,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   143,   144,   145,   147,   148,   149,   150,   151,   152,
     153,   105,   145,     3,    64,    89,   101,   104,    62,   106,
     128,   130,   133,   134,   135,   136,   137,   108,    83,   102,
     141,   145,   116,   118,    84,   115,   117,    80,   119,   120,
     126,   118,   123,    66,   115,    81,    80,    61,    89,    61,
      89,    89,   104,    80,    61,    61,    61,   143,    61,     3,
      82,    82,    82,   103,   103,   118,   138,    90,    90,    90,
      90,    90,    90,     7,     8,     9,    61,    63,    65,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    81,
      68,    73,    74,    69,    70,    10,    11,    12,    13,    75,
      76,    14,    15,    67,    77,    78,    16,    17,    79,    66,
      82,   147,   149,   143,   147,    64,    61,    63,   126,   129,
     131,   139,   140,   130,    66,    66,   130,   141,   142,   115,
     104,    66,    82,    80,   115,   124,   104,   143,   138,    80,
     143,   103,   103,   103,    54,   150,    82,    82,    62,    61,
     131,   139,    62,     3,    62,    88,   102,   103,     3,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    93,
      93,    94,    94,    95,    96,    97,    98,    99,   103,   102,
     147,   139,    64,   104,   130,   133,   140,    63,   129,    48,
     135,   137,    66,    84,   120,   104,    62,   143,    62,    62,
      62,    61,   150,    90,    62,    66,    64,    80,    62,    64,
     130,    64,   104,   130,   133,    84,   141,   143,   143,   143,
     103,    62,   103,   102,   101,    64,   130,    52,    62,   143,
      62,   143,    82,   143
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    92,    92,    92,    93,    93,    93,    94,
      94,    94,    94,    94,    95,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   101,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   103,   103,   104,   105,   105,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   111,   112,   112,   113,   114,
     115,   116,   116,   117,   118,   118,   118,   118,   119,   119,
     120,   120,   120,   121,   121,   121,   122,   123,   123,   124,
     124,   125,   125,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   128,   129,   130,   131,   131,   131,   131,   132,
     132,   133,   133,   134,   134,   135,   135,   135,   136,   136,
     137,   138,   138,   139,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   141,   141,   142,   142,
     143,   143,   143,   143,   143,   143,   144,   144,   144,   145,
     145,   145,   145,   146,   147,   148,   148,   149,   149,   150,
     150,   151,   151,   151,   152,   152,   152,   152,   153,   153,
     153,   153,   153,   154,   154,   155,   155,   156,   156,   156,
     156
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     1,     4,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     5,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     2,     3,     1,     2,     1,     2,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     1,     1,     1,     1,
       1,     1,     2,     3,     2,     1,     2,     1,     1,     3,
       1,     2,     3,     5,     4,     2,     1,     1,     3,     1,
       3,     1,     1,     2,     1,     1,     3,     4,     3,     4,
       4,     3,     1,     1,     1,     1,     2,     2,     3,     1,
       2,     1,     3,     1,     3,     2,     2,     1,     1,     3,
       1,     1,     2,     1,     1,     2,     3,     2,     3,     3,
       4,     2,     3,     3,     4,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     2,
       3,     3,     4,     1,     1,     1,     2,     1,     2,     1,
       2,     5,     7,     5,     5,     7,     6,     7,     3,     2,
       2,     2,     3,     1,     2,     1,     1,     4,     3,     3,
       2
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
  case 71:
#line 156 "spec/parser_spec.y"
                                { }
#line 1820 "src/yy/y.tab.c"
    break;

  case 73:
#line 161 "spec/parser_spec.y"
                                 { /*ConstantExpressionProcessor();*/ }
#line 1826 "src/yy/y.tab.c"
    break;

  case 74:
#line 165 "spec/parser_spec.y"
                                     { Declaration(); }
#line 1832 "src/yy/y.tab.c"
    break;

  case 75:
#line 166 "spec/parser_spec.y"
                                                          { Declaration(); }
#line 1838 "src/yy/y.tab.c"
    break;

  case 76:
#line 170 "spec/parser_spec.y"
                                        { DeclarationSpecifiers(); }
#line 1844 "src/yy/y.tab.c"
    break;

  case 78:
#line 172 "spec/parser_spec.y"
                                { DeclarationSpecifiers(); }
#line 1850 "src/yy/y.tab.c"
    break;

  case 80:
#line 174 "spec/parser_spec.y"
                                { DeclarationSpecifiers(); }
#line 1856 "src/yy/y.tab.c"
    break;

  case 84:
#line 184 "spec/parser_spec.y"
                     { Declarator(); }
#line 1862 "src/yy/y.tab.c"
    break;

  case 85:
#line 185 "spec/parser_spec.y"
                                     { DeclaratorInitialized(); }
#line 1868 "src/yy/y.tab.c"
    break;

  case 86:
#line 189 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(TYPEDEF); }
#line 1874 "src/yy/y.tab.c"
    break;

  case 87:
#line 190 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(EXTERN); }
#line 1880 "src/yy/y.tab.c"
    break;

  case 88:
#line 191 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(STATIC); }
#line 1886 "src/yy/y.tab.c"
    break;

  case 89:
#line 192 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(AUTO); }
#line 1892 "src/yy/y.tab.c"
    break;

  case 90:
#line 193 "spec/parser_spec.y"
                        { StorageClassSpecifierRef(REGISTER); }
#line 1898 "src/yy/y.tab.c"
    break;

  case 91:
#line 197 "spec/parser_spec.y"
                                        { TypeSpecifierRef(VOID); }
#line 1904 "src/yy/y.tab.c"
    break;

  case 92:
#line 198 "spec/parser_spec.y"
                                        { TypeSpecifierRef(CHAR); }
#line 1910 "src/yy/y.tab.c"
    break;

  case 93:
#line 199 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SHORT); }
#line 1916 "src/yy/y.tab.c"
    break;

  case 94:
#line 200 "spec/parser_spec.y"
                                        { TypeSpecifierRef(INT); }
#line 1922 "src/yy/y.tab.c"
    break;

  case 95:
#line 201 "spec/parser_spec.y"
                                        { TypeSpecifierRef(LONG); }
#line 1928 "src/yy/y.tab.c"
    break;

  case 96:
#line 202 "spec/parser_spec.y"
                                        { TypeSpecifierRef(FLOAT); }
#line 1934 "src/yy/y.tab.c"
    break;

  case 97:
#line 203 "spec/parser_spec.y"
                                        { TypeSpecifierRef(DOUBLE); }
#line 1940 "src/yy/y.tab.c"
    break;

  case 98:
#line 204 "spec/parser_spec.y"
                                        { TypeSpecifierRef(SIGNED); }
#line 1946 "src/yy/y.tab.c"
    break;

  case 99:
#line 205 "spec/parser_spec.y"
                                { TypeSpecifierRef(UNSIGNED); }
#line 1952 "src/yy/y.tab.c"
    break;

  case 100:
#line 206 "spec/parser_spec.y"
                                    { TypeSpecifierRef(CUSTOM_TYPE); }
#line 1958 "src/yy/y.tab.c"
    break;

  case 101:
#line 207 "spec/parser_spec.y"
                                                                        { TypeSpecifierRef(CUSTOM_TYPE); }
#line 1964 "src/yy/y.tab.c"
    break;

  case 102:
#line 208 "spec/parser_spec.y"
                                                                                { TypeSpecifierRef(CUSTOM_TYPE); }
#line 1970 "src/yy/y.tab.c"
    break;

  case 103:
#line 212 "spec/parser_spec.y"
                                                                                      { TagNamedDef(); }
#line 1976 "src/yy/y.tab.c"
    break;

  case 104:
#line 213 "spec/parser_spec.y"
                                                                             { TagAnonymousDef(); }
#line 1982 "src/yy/y.tab.c"
    break;

  case 105:
#line 214 "spec/parser_spec.y"
                                   { TagNamedDecl(); }
#line 1988 "src/yy/y.tab.c"
    break;

  case 106:
#line 218 "spec/parser_spec.y"
                        { TagTypeRef(TAG_STRUCT); }
#line 1994 "src/yy/y.tab.c"
    break;

  case 107:
#line 219 "spec/parser_spec.y"
                                { TagTypeRef(TAG_UNION); }
#line 2000 "src/yy/y.tab.c"
    break;

  case 108:
#line 223 "spec/parser_spec.y"
                     { IdentifierName(yylval.id); }
#line 2006 "src/yy/y.tab.c"
    break;

  case 109:
#line 227 "spec/parser_spec.y"
                { TagDefOpen(); }
#line 2012 "src/yy/y.tab.c"
    break;

  case 110:
#line 231 "spec/parser_spec.y"
                { TagDefClose(); }
#line 2018 "src/yy/y.tab.c"
    break;

  case 113:
#line 240 "spec/parser_spec.y"
                                                              { Declaration(); }
#line 2024 "src/yy/y.tab.c"
    break;

  case 120:
#line 256 "spec/parser_spec.y"
                     { Declarator(); }
#line 2030 "src/yy/y.tab.c"
    break;

  case 123:
#line 262 "spec/parser_spec.y"
                                                                   { TagNamedDef(); }
#line 2036 "src/yy/y.tab.c"
    break;

  case 124:
#line 263 "spec/parser_spec.y"
                                                          { TagAnonymousDef(); }
#line 2042 "src/yy/y.tab.c"
    break;

  case 125:
#line 264 "spec/parser_spec.y"
                        { TagNamedDecl(); }
#line 2048 "src/yy/y.tab.c"
    break;

  case 126:
#line 268 "spec/parser_spec.y"
                { TagTypeRef(TAG_ENUM); }
#line 2054 "src/yy/y.tab.c"
    break;

  case 129:
#line 277 "spec/parser_spec.y"
                          { EnumeratorDefault(); }
#line 2060 "src/yy/y.tab.c"
    break;

  case 130:
#line 278 "spec/parser_spec.y"
                                                  { EnumeratorCustom(); }
#line 2066 "src/yy/y.tab.c"
    break;

  case 131:
#line 282 "spec/parser_spec.y"
                                        { TypeQualifierRef(CONST); }
#line 2072 "src/yy/y.tab.c"
    break;

  case 132:
#line 283 "spec/parser_spec.y"
                                { TypeQualifierRef(VOLATILE); }
#line 2078 "src/yy/y.tab.c"
    break;

  case 133:
#line 287 "spec/parser_spec.y"
                                    { NestedDeclarator(); }
#line 2084 "src/yy/y.tab.c"
    break;

  case 136:
#line 293 "spec/parser_spec.y"
                             { /*NestedDeclarator();*/ }
#line 2090 "src/yy/y.tab.c"
    break;

  case 137:
#line 294 "spec/parser_spec.y"
                                                        { ArrayLengthDeclarator(); }
#line 2096 "src/yy/y.tab.c"
    break;

  case 138:
#line 295 "spec/parser_spec.y"
                                    { ArrayVariableDeclarator(); }
#line 2102 "src/yy/y.tab.c"
    break;

  case 139:
#line 296 "spec/parser_spec.y"
                                                                                           { FunctionDeclarator(); }
#line 2108 "src/yy/y.tab.c"
    break;

  case 140:
#line 297 "spec/parser_spec.y"
                                                                                       { FunctionDeclarator(); }
#line 2114 "src/yy/y.tab.c"
    break;

  case 141:
#line 298 "spec/parser_spec.y"
                                                                       { FunctionDeclarator(); }
#line 2120 "src/yy/y.tab.c"
    break;

  case 142:
#line 302 "spec/parser_spec.y"
                     { IdentifierName(yyval.id); }
#line 2126 "src/yy/y.tab.c"
    break;

  case 143:
#line 306 "spec/parser_spec.y"
              { FunctionParamsOpen(); }
#line 2132 "src/yy/y.tab.c"
    break;

  case 144:
#line 310 "spec/parser_spec.y"
                { FunctionParamsClose(); }
#line 2138 "src/yy/y.tab.c"
    break;

  case 145:
#line 314 "spec/parser_spec.y"
              { PointerOpen(); }
#line 2144 "src/yy/y.tab.c"
    break;

  case 146:
#line 315 "spec/parser_spec.y"
                                  { PointerQualifierOpen();}
#line 2150 "src/yy/y.tab.c"
    break;

  case 147:
#line 316 "spec/parser_spec.y"
                      { Pointer(); }
#line 2156 "src/yy/y.tab.c"
    break;

  case 148:
#line 317 "spec/parser_spec.y"
                                          { PointerQualifier(); }
#line 2162 "src/yy/y.tab.c"
    break;

  case 152:
#line 327 "spec/parser_spec.y"
                                      { Ellipsis(); }
#line 2168 "src/yy/y.tab.c"
    break;

  case 153:
#line 331 "spec/parser_spec.y"
                                { Declaration(); }
#line 2174 "src/yy/y.tab.c"
    break;

  case 154:
#line 332 "spec/parser_spec.y"
                                                   { Declaration(); }
#line 2180 "src/yy/y.tab.c"
    break;

  case 155:
#line 336 "spec/parser_spec.y"
                                            { Declarator(); }
#line 2186 "src/yy/y.tab.c"
    break;

  case 156:
#line 337 "spec/parser_spec.y"
                                                     { AbstractDeclarator(); }
#line 2192 "src/yy/y.tab.c"
    break;

  case 157:
#line 338 "spec/parser_spec.y"
                                 { AbstractDeclarator(); }
#line 2198 "src/yy/y.tab.c"
    break;

  case 158:
#line 342 "spec/parser_spec.y"
                              { Declaration(); }
#line 2204 "src/yy/y.tab.c"
    break;

  case 159:
#line 343 "spec/parser_spec.y"
                                                  { Declaration(); }
#line 2210 "src/yy/y.tab.c"
    break;

  case 160:
#line 347 "spec/parser_spec.y"
                          { Declarator(); }
#line 2216 "src/yy/y.tab.c"
    break;

  case 161:
#line 351 "spec/parser_spec.y"
                                   { /*TypeName();*/ }
#line 2222 "src/yy/y.tab.c"
    break;

  case 162:
#line 352 "spec/parser_spec.y"
                                                       { /*TypeName();*/ }
#line 2228 "src/yy/y.tab.c"
    break;

  case 163:
#line 356 "spec/parser_spec.y"
                  { NestedDeclarator(); }
#line 2234 "src/yy/y.tab.c"
    break;

  case 165:
#line 358 "spec/parser_spec.y"
                                             { NestedDeclarator(); }
#line 2240 "src/yy/y.tab.c"
    break;

  case 166:
#line 362 "spec/parser_spec.y"
                                      { /*NestedDeclarator();*/ }
#line 2246 "src/yy/y.tab.c"
    break;

  case 167:
#line 363 "spec/parser_spec.y"
                  { ArrayVariableDeclarator(); }
#line 2252 "src/yy/y.tab.c"
    break;

  case 168:
#line 364 "spec/parser_spec.y"
                                       { ArrayLengthDeclarator(); }
#line 2258 "src/yy/y.tab.c"
    break;

  case 169:
#line 365 "spec/parser_spec.y"
                                              { ArrayVariableDeclarator(); }
#line 2264 "src/yy/y.tab.c"
    break;

  case 170:
#line 366 "spec/parser_spec.y"
                                                                  { ArrayLengthDeclarator(); }
#line 2270 "src/yy/y.tab.c"
    break;

  case 171:
#line 367 "spec/parser_spec.y"
                                                     { FunctionDeclarator(); }
#line 2276 "src/yy/y.tab.c"
    break;

  case 172:
#line 368 "spec/parser_spec.y"
                                                                         { FunctionDeclarator(); }
#line 2282 "src/yy/y.tab.c"
    break;

  case 173:
#line 369 "spec/parser_spec.y"
                                                                                { FunctionDeclarator(); }
#line 2288 "src/yy/y.tab.c"
    break;

  case 174:
#line 370 "spec/parser_spec.y"
                                                                                                    { FunctionDeclarator(); }
#line 2294 "src/yy/y.tab.c"
    break;


#line 2298 "src/yy/y.tab.c"

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
#line 465 "spec/parser_spec.y"

#include <stdio.h>

extern char yytext[];
extern int column;

extern FILE* yyin;

void yyerror(char* s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
