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
#line 2 "./syntax.y"

    #include "N_tree.h"
    #include "lex.yy.c"//为了能够使用Flex中的各种函数，需要在Bison源代码中引用lex.yy.c
    struct treenode *root=NULL;
    extern int errorflag;
    int yyerror(const char *msg);

    //#define LOCAL_MACHINE 1  //用于调试，使得输出自定义的bison调试信息
    #ifdef LOCAL_MACHINE
     #define bdebug(...) printf(__VA_ARGS__)
    #else
     #define bdebug(...) assert(1)
    #endif

#line 85 "./syntax.tab.c"

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
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    PLUS = 265,
    MINUS = 266,
    STAR = 267,
    DIV = 268,
    AND = 269,
    OR = 270,
    DOT = 271,
    NOT = 272,
    TYPE = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    LOWER_THAT_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "./syntax.y"

    Tnode* node;

#line 172 "./syntax.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   423

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    44,    44,    48,    49,    53,    55,    57,    59,    60,
      61,    62,    66,    67,    71,    72,    78,    79,    80,    83,
      84,    86,    90,    91,    92,    96,    97,    98,   101,   102,
     105,   109,   110,   114,   115,   118,   119,   120,   121,   122,
     123,   125,   126,   127,   128,   131,   132,   136,   137,   140,
     141,   145,   146,   147,   150,   151,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   187,   188
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "LOWER_THAT_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     285
};
# endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   122,   -61,     9,    78,   -61,     6,   264,   -61,    63,
     -61,    24,    71,    79,   -61,   -61,   -61,   102,    63,   -61,
     106,    50,    24,    31,    81,    -9,   -61,    99,   -61,   -61,
     117,    98,   -61,   114,   -61,   117,   115,   129,   -61,    49,
      41,    -9,   118,   119,   -61,   -61,   127,   132,   -61,   123,
     -61,    -9,   157,    68,   159,    12,     2,   -61,   -61,   143,
     256,   256,   147,   256,   150,   155,   -61,   152,    41,   268,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   256,   -61,   117,
     117,   -61,   256,   136,    -1,    32,   162,   326,   282,   156,
     167,   -61,   -61,   -61,   176,   187,   256,   196,   207,   216,
     227,   236,   178,   247,   382,   -61,   -61,   340,   165,   -61,
     297,   169,   -61,   -61,   -61,   174,   354,   182,   368,   -61,
     382,   -61,   402,    -1,   -61,    -1,   -61,    32,   -61,    32,
     -61,   395,   -61,   395,   -61,   181,   311,    87,   -61,   256,
     -61,    58,    92,    87,    87,   -61,   -61,   -61,   -61,    87,
     -61,   101,   168,   -61,   -61,   -61,    87,    87,   -61,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    14,    19,     0,     2,     0,     0,    15,     0,
       9,     0,    21,     0,    17,     1,     4,    10,    22,     6,
       0,    12,     0,     0,     0,    47,    11,     0,     8,     5,
       0,     0,     7,     0,    26,     0,     0,    29,    32,     0,
       0,    47,     0,     0,    22,    13,     0,     0,    27,    30,
      25,     0,     0,    54,     0,     0,     0,    72,    73,    71,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
      48,    18,    16,    24,    23,    28,    50,     0,    49,     0,
       0,    45,     0,     0,    65,    66,     0,     0,     0,     0,
       0,    31,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    53,    52,     0,     0,    68,
      85,     0,    81,    64,    37,     0,     0,     0,     0,    74,
      56,    77,    59,    60,    78,    61,    79,    62,    80,    63,
      75,    57,    76,    58,    70,     0,     0,     0,    82,     0,
      67,     0,     0,     0,     0,    83,    69,    46,    84,     0,
      41,     0,    38,    44,    40,    42,     0,     0,    43,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   199,   -61,   179,     4,   -61,   -61,   -61,    -2,
     209,   163,   -61,    61,   154,   -11,    39,   -61,    -6,   -61,
     -60,    84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    20,    39,     8,    13,    14,    53,
      11,    36,    37,    66,    67,    68,    40,    41,    54,    55,
      69,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    85,    87,    88,     7,    21,    -3,     1,    81,     2,
       7,    98,    99,    79,    12,   102,     3,   104,   -51,    80,
     103,    82,   107,   110,     2,    24,    38,    35,    21,   116,
     118,     3,    33,    49,   120,   122,   123,   125,   127,   129,
     131,   133,    56,   136,    57,    58,    59,    25,   102,     2,
      52,    34,    60,   103,    44,    35,     3,    30,    61,    56,
      62,    57,    58,    59,    25,   -33,    43,    63,    64,    60,
      65,    31,    26,   105,   106,    61,    77,    62,    15,   110,
      70,    25,    23,    32,    63,    64,   149,    65,    56,    31,
      57,    58,    59,   151,   -20,    57,    58,    59,    60,    46,
      42,    47,    27,    60,    61,    38,    62,    81,    28,    61,
      25,    62,    29,    63,    64,    25,    65,     2,    63,    64,
      82,    65,    44,   -47,     3,    38,   147,     9,    10,   156,
     150,   152,   153,   154,    48,    50,    51,   108,   155,    57,
      58,    59,    71,    72,    31,   158,   159,    60,    86,    73,
      57,    58,    59,    61,    74,    62,   109,   115,    60,    57,
      58,    59,    83,    76,    61,    78,    62,    60,   117,    89,
      57,    58,    59,    61,    90,    62,    91,   119,    60,    57,
      58,    59,   112,   134,    61,   138,    62,    60,   121,   140,
      57,    58,    59,    61,   141,    62,   157,   124,    60,    57,
      58,    59,   143,   145,    61,    16,    62,    60,   126,    45,
      57,    58,    59,    61,    75,    62,    22,   128,    60,    57,
      58,    59,    92,   148,    61,     0,    62,    60,   130,     0,
      57,    58,    59,    61,     0,    62,     0,   132,    60,    57,
      58,    59,     0,     0,    61,     0,    62,    60,   135,     0,
      57,    58,    59,    61,     0,    62,     0,     0,    60,    57,
      58,    59,     0,     0,    61,    17,    62,    60,     0,    18,
      19,     0,     0,    61,    93,    62,    94,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,   114,   103,
      94,    95,    96,    97,    98,    99,   100,   101,   102,     0,
       0,     0,     0,   103,   139,    94,    95,    96,    97,    98,
      99,   100,   101,   102,     0,     0,     0,     0,   103,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,   103,   146,    94,    95,    96,    97,    98,    99,
     100,   101,   102,     0,     0,     0,   113,   103,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
     137,   103,    94,    95,    96,    97,    98,    99,   100,   101,
     102,     0,     0,     0,   142,   103,    94,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,   144,   103,
      94,    95,    96,    97,    98,    99,   100,   101,   102,     0,
       0,     0,     0,   103,    95,    96,    97,    98,    99,     0,
       0,   102,    96,    97,    98,    99,   103,     0,   102,     0,
       0,     0,     0,   103
};

static const yytype_int16 yycheck[] =
{
      60,    61,    62,    63,     0,     7,     0,     1,     6,    18,
       6,    12,    13,     1,     5,    16,    25,    77,     6,     7,
      21,    19,    82,    83,    18,     1,    24,    23,    30,    89,
      90,    25,     1,    35,    94,    95,    96,    97,    98,    99,
     100,   101,     1,   103,     3,     4,     5,    23,    16,    18,
       1,    20,    11,    21,     5,    51,    25,     7,    17,     1,
      19,     3,     4,     5,    23,    24,    27,    26,    27,    11,
      29,    21,    11,    79,    80,    17,     8,    19,     0,   139,
      41,    23,    19,    22,    26,    27,    28,    29,     1,    21,
       3,     4,     5,     1,    23,     3,     4,     5,    11,     1,
       1,     3,    23,    11,    17,    24,    19,     6,     6,    17,
      23,    19,     6,    26,    27,    23,    29,    18,    26,    27,
      19,    29,     5,    24,    25,    24,   137,     5,     6,    28,
     141,   142,   143,   144,    20,    20,     7,     1,   149,     3,
       4,     5,    24,    24,    21,   156,   157,    11,     1,    22,
       3,     4,     5,    17,    22,    19,    20,     1,    11,     3,
       4,     5,    19,     6,    17,     6,    19,    11,     1,    19,
       3,     4,     5,    17,    19,    19,    24,     1,    11,     3,
       4,     5,    20,     5,    17,    20,    19,    11,     1,    20,
       3,     4,     5,    17,    20,    19,    28,     1,    11,     3,
       4,     5,    20,    22,    17,     6,    19,    11,     1,    30,
       3,     4,     5,    17,    51,    19,     7,     1,    11,     3,
       4,     5,    68,   139,    17,    -1,    19,    11,     1,    -1,
       3,     4,     5,    17,    -1,    19,    -1,     1,    11,     3,
       4,     5,    -1,    -1,    17,    -1,    19,    11,     1,    -1,
       3,     4,     5,    17,    -1,    19,    -1,    -1,    11,     3,
       4,     5,    -1,    -1,    17,     1,    19,    11,    -1,     5,
       6,    -1,    -1,    17,     6,    19,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,     6,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    21,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    21,    22,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    20,    21,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    21,     9,    10,    11,    12,    13,    -1,
      -1,    16,    10,    11,    12,    13,    21,    -1,    16,    -1,
      -1,    -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    25,    32,    33,    34,    36,    37,     5,
       6,    41,     5,    38,    39,     0,    33,     1,     5,     6,
      35,    40,    41,    19,     1,    23,    44,    23,     6,     6,
       7,    21,    44,     1,    20,    36,    42,    43,    24,    36,
      47,    48,     1,    47,     5,    35,     1,     3,    20,    40,
      20,     7,     1,    40,    49,    50,     1,     3,     4,     5,
      11,    17,    19,    26,    27,    29,    44,    45,    46,    51,
      47,    24,    24,    22,    22,    42,     6,     8,     6,     1,
       7,     6,    19,    19,    51,    51,     1,    51,    51,    19,
      19,    24,    45,     6,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    21,    51,    49,    49,    51,     1,    20,
      51,    52,    20,    20,     6,     1,    51,     1,    51,     1,
      51,     1,    51,    51,     1,    51,     1,    51,     1,    51,
       1,    51,     1,    51,     5,     1,    51,    20,    20,     7,
      20,    20,    20,    20,    20,    22,    22,    46,    52,    28,
      46,     1,    46,    46,    46,    46,    28,    28,    46,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    34,    35,    35,    36,    36,    37,    37,    37,    38,
      38,    39,    40,    40,    40,    41,    41,    41,    42,    42,
      43,    44,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       2,     3,     1,     3,     1,     1,     5,     2,     5,     0,
       1,     1,     1,     4,     4,     4,     3,     4,     3,     1,
       2,     4,     2,     0,     2,     2,     1,     3,     5,     7,
       5,     5,     6,     7,     5,     2,     5,     0,     2,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     3,     4,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     3,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 44 "./syntax.y"
                                            {(yyval.node)=create_node("Program",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));root=(yyval.node);}
#line 1614 "./syntax.tab.c"
    break;

  case 3:
#line 48 "./syntax.y"
                                            {(yyval.node)=NULL;}
#line 1620 "./syntax.tab.c"
    break;

  case 4:
#line 49 "./syntax.y"
                                            {(yyval.node)=create_node("ExtDefList",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1626 "./syntax.tab.c"
    break;

  case 5:
#line 53 "./syntax.y"
                                            {(yyval.node)=create_node("ExtDef",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1632 "./syntax.tab.c"
    break;

  case 6:
#line 55 "./syntax.y"
                                            {(yyval.node)=create_node("ExtDef",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1638 "./syntax.tab.c"
    break;

  case 7:
#line 57 "./syntax.y"
                                            {(yyval.node)=create_node("ExtDef",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1644 "./syntax.tab.c"
    break;

  case 8:
#line 59 "./syntax.y"
                                            {yyerrok;}
#line 1650 "./syntax.tab.c"
    break;

  case 9:
#line 60 "./syntax.y"
                                            {yyerrok;}
#line 1656 "./syntax.tab.c"
    break;

  case 10:
#line 61 "./syntax.y"
                                            {yyerrok;}
#line 1662 "./syntax.tab.c"
    break;

  case 11:
#line 62 "./syntax.y"
                                            {bdebug("error FunDec CompSt \n");yyerrok;}
#line 1668 "./syntax.tab.c"
    break;

  case 12:
#line 66 "./syntax.y"
                                            {(yyval.node)=create_node("ExtDecList",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1674 "./syntax.tab.c"
    break;

  case 13:
#line 67 "./syntax.y"
                                            {(yyval.node)=create_node("ExtDecList",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1680 "./syntax.tab.c"
    break;

  case 14:
#line 71 "./syntax.y"
                                            {(yyval.node)=create_node("Specifier",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1686 "./syntax.tab.c"
    break;

  case 15:
#line 72 "./syntax.y"
                                            {(yyval.node)=create_node("Specifier",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1692 "./syntax.tab.c"
    break;

  case 16:
#line 78 "./syntax.y"
                                                        {(yyval.node)=create_node("StructSpecifier",0,(yyloc).first_line);Ninsert((yyval.node),5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1698 "./syntax.tab.c"
    break;

  case 17:
#line 79 "./syntax.y"
                                                        {(yyval.node)=create_node("StructSpecifier",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1704 "./syntax.tab.c"
    break;

  case 18:
#line 80 "./syntax.y"
                                                        {yyerrok;}
#line 1710 "./syntax.tab.c"
    break;

  case 19:
#line 83 "./syntax.y"
                                                        {(yyval.node)=NULL;}
#line 1716 "./syntax.tab.c"
    break;

  case 20:
#line 84 "./syntax.y"
                                                        {(yyval.node)=create_node("OptTag",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1722 "./syntax.tab.c"
    break;

  case 21:
#line 86 "./syntax.y"
                                                        {(yyval.node)=create_node("Tag",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1728 "./syntax.tab.c"
    break;

  case 22:
#line 90 "./syntax.y"
                                                        {(yyval.node)=create_node("VarDec",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1734 "./syntax.tab.c"
    break;

  case 23:
#line 91 "./syntax.y"
                                                        {(yyval.node)=create_node("VarDec",0,(yyloc).first_line);Ninsert((yyval.node),4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1740 "./syntax.tab.c"
    break;

  case 24:
#line 92 "./syntax.y"
                                                        {yyerrok;}
#line 1746 "./syntax.tab.c"
    break;

  case 25:
#line 96 "./syntax.y"
                                                        {(yyval.node)=create_node("FunDec",0,(yyloc).first_line);Ninsert((yyval.node),4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1752 "./syntax.tab.c"
    break;

  case 26:
#line 97 "./syntax.y"
                                                        {(yyval.node)=create_node("FunDec",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1758 "./syntax.tab.c"
    break;

  case 27:
#line 98 "./syntax.y"
                                                        {yyerrok;}
#line 1764 "./syntax.tab.c"
    break;

  case 28:
#line 101 "./syntax.y"
                                                        {(yyval.node)=create_node("VarList",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1770 "./syntax.tab.c"
    break;

  case 29:
#line 102 "./syntax.y"
                                                        {(yyval.node)=create_node("VarList",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1776 "./syntax.tab.c"
    break;

  case 30:
#line 105 "./syntax.y"
                                                        {(yyval.node)=create_node("ParamDec",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1782 "./syntax.tab.c"
    break;

  case 31:
#line 109 "./syntax.y"
                                                        {(yyval.node)=create_node("CompSt",0,(yyloc).first_line);Ninsert((yyval.node),4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1788 "./syntax.tab.c"
    break;

  case 32:
#line 110 "./syntax.y"
                                                        {yyerrok;}
#line 1794 "./syntax.tab.c"
    break;

  case 33:
#line 114 "./syntax.y"
                                                        {(yyval.node)=NULL;}
#line 1800 "./syntax.tab.c"
    break;

  case 34:
#line 115 "./syntax.y"
                                                        {(yyval.node)=create_node("StmtList",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1806 "./syntax.tab.c"
    break;

  case 35:
#line 118 "./syntax.y"
                                                        {(yyval.node)=create_node("Stmt",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1812 "./syntax.tab.c"
    break;

  case 36:
#line 119 "./syntax.y"
                                                        {(yyval.node)=create_node("Stmt",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1818 "./syntax.tab.c"
    break;

  case 37:
#line 120 "./syntax.y"
                                                        {(yyval.node)=create_node("Stmt",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1824 "./syntax.tab.c"
    break;

  case 38:
#line 121 "./syntax.y"
                                                        {(yyval.node)=create_node("Stmt",0,(yyloc).first_line);Ninsert((yyval.node),5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1830 "./syntax.tab.c"
    break;

  case 39:
#line 122 "./syntax.y"
                                                        {(yyval.node)=create_node("Stmt",0,(yyloc).first_line);Ninsert((yyval.node),7,(yyvsp[-6].node),(yyvsp[-5].node),(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1836 "./syntax.tab.c"
    break;

  case 40:
#line 123 "./syntax.y"
                                                        {(yyval.node)=create_node("Stmt",0,(yyloc).first_line);Ninsert((yyval.node),5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1842 "./syntax.tab.c"
    break;

  case 41:
#line 125 "./syntax.y"
                                                        {yyerrok;}
#line 1848 "./syntax.tab.c"
    break;

  case 42:
#line 126 "./syntax.y"
                                                        {yyerrok;}
#line 1854 "./syntax.tab.c"
    break;

  case 43:
#line 127 "./syntax.y"
                                                        {yyerrok;}
#line 1860 "./syntax.tab.c"
    break;

  case 44:
#line 128 "./syntax.y"
                                                        {yyerrok;}
#line 1866 "./syntax.tab.c"
    break;

  case 45:
#line 131 "./syntax.y"
                                                        {yyerrok;}
#line 1872 "./syntax.tab.c"
    break;

  case 46:
#line 132 "./syntax.y"
                                                        {yyerrok;}
#line 1878 "./syntax.tab.c"
    break;

  case 47:
#line 136 "./syntax.y"
                                            {(yyval.node)=NULL;}
#line 1884 "./syntax.tab.c"
    break;

  case 48:
#line 137 "./syntax.y"
                                            {(yyval.node)=create_node("DefList",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1890 "./syntax.tab.c"
    break;

  case 49:
#line 140 "./syntax.y"
                                            {(yyval.node)=create_node("Def",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1896 "./syntax.tab.c"
    break;

  case 50:
#line 141 "./syntax.y"
                                            {yyerrok;}
#line 1902 "./syntax.tab.c"
    break;

  case 51:
#line 145 "./syntax.y"
                                            {(yyval.node)=create_node("DecList",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1908 "./syntax.tab.c"
    break;

  case 52:
#line 146 "./syntax.y"
                                            {(yyval.node)=create_node("DecList",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1914 "./syntax.tab.c"
    break;

  case 53:
#line 147 "./syntax.y"
                                            {yyerrok;}
#line 1920 "./syntax.tab.c"
    break;

  case 54:
#line 150 "./syntax.y"
                                            {(yyval.node)=create_node("Dec",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 1926 "./syntax.tab.c"
    break;

  case 55:
#line 151 "./syntax.y"
                                            {(yyval.node)=create_node("Dec",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1932 "./syntax.tab.c"
    break;

  case 56:
#line 155 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1938 "./syntax.tab.c"
    break;

  case 57:
#line 156 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1944 "./syntax.tab.c"
    break;

  case 58:
#line 157 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1950 "./syntax.tab.c"
    break;

  case 59:
#line 158 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1956 "./syntax.tab.c"
    break;

  case 60:
#line 159 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1962 "./syntax.tab.c"
    break;

  case 61:
#line 160 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1968 "./syntax.tab.c"
    break;

  case 62:
#line 161 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1974 "./syntax.tab.c"
    break;

  case 63:
#line 162 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1980 "./syntax.tab.c"
    break;

  case 64:
#line 163 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 1986 "./syntax.tab.c"
    break;

  case 65:
#line 164 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1992 "./syntax.tab.c"
    break;

  case 66:
#line 165 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),2,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1998 "./syntax.tab.c"
    break;

  case 67:
#line 166 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2004 "./syntax.tab.c"
    break;

  case 68:
#line 167 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2010 "./syntax.tab.c"
    break;

  case 69:
#line 168 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2016 "./syntax.tab.c"
    break;

  case 70:
#line 169 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2022 "./syntax.tab.c"
    break;

  case 71:
#line 170 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 2028 "./syntax.tab.c"
    break;

  case 72:
#line 171 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 2034 "./syntax.tab.c"
    break;

  case 73:
#line 172 "./syntax.y"
                                            {(yyval.node)=create_node("Exp",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 2040 "./syntax.tab.c"
    break;

  case 74:
#line 175 "./syntax.y"
                                            {yyerrok;}
#line 2046 "./syntax.tab.c"
    break;

  case 75:
#line 176 "./syntax.y"
                                            {yyerrok;}
#line 2052 "./syntax.tab.c"
    break;

  case 76:
#line 177 "./syntax.y"
                                            {yyerrok;}
#line 2058 "./syntax.tab.c"
    break;

  case 77:
#line 178 "./syntax.y"
                                            {yyerrok;}
#line 2064 "./syntax.tab.c"
    break;

  case 78:
#line 179 "./syntax.y"
                                            {yyerrok;}
#line 2070 "./syntax.tab.c"
    break;

  case 79:
#line 180 "./syntax.y"
                                            {yyerrok;}
#line 2076 "./syntax.tab.c"
    break;

  case 80:
#line 181 "./syntax.y"
                                            {yyerrok;}
#line 2082 "./syntax.tab.c"
    break;

  case 81:
#line 182 "./syntax.y"
                                            {yyerrok;}
#line 2088 "./syntax.tab.c"
    break;

  case 82:
#line 183 "./syntax.y"
                                            {yyerrok;}
#line 2094 "./syntax.tab.c"
    break;

  case 83:
#line 184 "./syntax.y"
                                            {yyerrok;}
#line 2100 "./syntax.tab.c"
    break;

  case 84:
#line 187 "./syntax.y"
                                            {(yyval.node)=create_node("Args",0,(yyloc).first_line);Ninsert((yyval.node),3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2106 "./syntax.tab.c"
    break;

  case 85:
#line 188 "./syntax.y"
                                            {(yyval.node)=create_node("Args",0,(yyloc).first_line);Ninsert((yyval.node),1,(yyvsp[0].node));}
#line 2112 "./syntax.tab.c"
    break;


#line 2116 "./syntax.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
#line 190 "./syntax.y"

//
int lastlineno=-1;//用于记录上一次报错的行数，使得一行只报错一次即可
int onelineflag = 1;//1表示开启一行只打印一个错误，0为关闭
int yyerror(const char *msg){
       errorflag=1;
       if(!onelineflag||yylineno!=lastlineno){//如果相等说明之前报错过了，就不打印
         lastlineno=yylineno;
         fprintf(stderr,"Error type B at line %d: %s :unexpected token %s\n",yylineno,msg,yytext);
       }
}
