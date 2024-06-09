/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syn.y"

#include "sem.h"
#include "lex.yy.c" 
extern Node* syntax_tree;

#line 77 "syn.tab.c"

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

#include "syn.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMI = 3,                       /* SEMI  */
  YYSYMBOL_COMMA = 4,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 5,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 6,                      /* RELOP  */
  YYSYMBOL_PLUS = 7,                       /* PLUS  */
  YYSYMBOL_MINUS = 8,                      /* MINUS  */
  YYSYMBOL_STAR = 9,                       /* STAR  */
  YYSYMBOL_DIV = 10,                       /* DIV  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_OR = 12,                        /* OR  */
  YYSYMBOL_DOT = 13,                       /* DOT  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_TYPE = 15,                      /* TYPE  */
  YYSYMBOL_LP = 16,                        /* LP  */
  YYSYMBOL_RP = 17,                        /* RP  */
  YYSYMBOL_LB = 18,                        /* LB  */
  YYSYMBOL_RB = 19,                        /* RB  */
  YYSYMBOL_LC = 20,                        /* LC  */
  YYSYMBOL_RC = 21,                        /* RC  */
  YYSYMBOL_STRUCT = 22,                    /* STRUCT  */
  YYSYMBOL_RETURN = 23,                    /* RETURN  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_FLOAT = 27,                     /* FLOAT  */
  YYSYMBOL_INT = 28,                       /* INT  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_Program = 31,                   /* Program  */
  YYSYMBOL_ExtDefList = 32,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 33,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 34,                /* ExtDecList  */
  YYSYMBOL_Specifier = 35,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 36,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 37,                    /* OptTag  */
  YYSYMBOL_Tag = 38,                       /* Tag  */
  YYSYMBOL_VarDec = 39,                    /* VarDec  */
  YYSYMBOL_FunDec = 40,                    /* FunDec  */
  YYSYMBOL_VarList = 41,                   /* VarList  */
  YYSYMBOL_ParamDec = 42,                  /* ParamDec  */
  YYSYMBOL_CompSt = 43,                    /* CompSt  */
  YYSYMBOL_StmtList = 44,                  /* StmtList  */
  YYSYMBOL_Stmt = 45,                      /* Stmt  */
  YYSYMBOL_DefList = 46,                   /* DefList  */
  YYSYMBOL_Def = 47,                       /* Def  */
  YYSYMBOL_DecList = 48,                   /* DecList  */
  YYSYMBOL_Dec = 49,                       /* Dec  */
  YYSYMBOL_Exp = 50,                       /* Exp  */
  YYSYMBOL_Args = 51                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   379

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    34,    34,    36,    37,    39,    40,    41,    42,    43,
      44,    46,    47,    48,    54,    55,    57,    58,    59,    60,
      61,    62,    70,    71,    72,    73,    74,    77,    78,    79,
      80,    81,    82,    83,    84,    87,    88,    89,    91,    98,
      99,   100,   101,   104,   105,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     128,   129,   131,   132,   134,   135,   136,   138,   139,   140,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   166,   167
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "FLOAT", "INT", "ID", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-87)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     136,    41,   -65,   -11,    70,   -65,   136,     3,   -65,   -65,
      64,    87,   -65,   -65,   -65,   -65,   -65,    56,   187,    40,
      68,    16,    56,    44,    53,    56,    44,    62,   161,   165,
     -65,    78,   -65,   -65,    44,   141,    80,   -65,   -65,   354,
      56,   -65,    91,   116,   108,     1,   -65,   -65,    48,   -65,
      56,   -65,   106,   -65,    47,   -65,   -65,   163,   163,   163,
     -65,   188,   109,   263,   -65,   -65,    61,    61,   -65,   163,
      80,   322,   -65,    44,   -65,   -65,   -65,   -65,   -65,   -65,
      -6,    -6,   308,   -65,   -65,   145,   163,   163,   163,   163,
     163,   163,   163,   163,    97,   163,   -65,    25,   119,    67,
      99,   -65,   107,    61,   207,    24,   322,   -65,   -65,   -65,
     279,   112,   322,   355,   361,   361,    -6,    -6,   348,   335,
     -65,   293,   -65,   -65,   -65,   221,   -65,   163,   -65,   163,
     -65,   -65,   -65,   -65,   -65,   -65,   163,   -65,   -65,   -65,
     -65,   235,   249,   -65,   -65,    90,   -65,    90,   113,   -65,
      90,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    14,    19,     0,     2,     0,     0,    15,    10,
      20,    60,    17,     1,     4,     9,     6,     0,    22,     0,
      11,     0,    60,     0,     0,    60,     0,     0,    36,     0,
      31,     0,     8,     5,     0,     0,     0,    22,    13,    60,
      60,     7,     0,    67,    63,    64,    18,    61,    38,    33,
       0,    37,    32,    28,     0,    29,    12,     0,     0,     0,
      87,     0,    85,     0,    24,    42,     0,     0,    16,     0,
      86,    69,    62,     0,    66,    35,    34,    30,    27,    86,
      79,    80,     0,    26,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    25,    60,     0,     0,
       0,    46,     0,     0,     0,     0,    68,    65,    78,    82,
      89,     0,    70,    73,    74,    75,    76,    77,    72,    71,
      84,     0,    59,    54,    53,     0,    56,     0,    58,     0,
      40,    44,    51,    45,    41,    39,     0,    81,    83,    52,
      47,     0,     0,    88,    55,     0,    57,     0,    48,    50,
       0,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,   125,   -65,    15,     9,   -65,   -65,   -65,   -12,
     -65,    -8,   -65,   118,   -64,   -42,    -9,   -65,   -44,   -65,
     -35,     4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    19,    23,     8,    11,    12,    20,
      21,    27,    28,   101,   102,   103,    66,    25,    44,    45,
     104,   111
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    74,    24,   105,    15,    73,    16,    94,    71,     7,
      31,    43,    95,    42,    48,     7,    47,    39,    10,    17,
      51,    54,    80,    81,    82,   134,    26,    26,   122,   107,
      37,    67,    18,    43,   106,    38,    40,    26,    26,   131,
       2,    32,    75,    33,     9,   135,    65,     3,    77,    56,
     110,   112,   113,   114,   115,   116,   117,   118,   119,    26,
     121,    43,    97,   125,    78,   -21,    35,   -21,   126,    57,
      13,     2,    34,    37,    46,    58,    36,    59,     3,    49,
     -21,    40,   -43,   127,    98,    99,    35,   100,    60,    79,
      62,    97,   141,   -21,   142,    55,    36,    37,    57,    64,
     128,   110,     2,   148,    58,   149,    59,    22,   151,     3,
      40,    72,    68,    98,    99,   129,   100,    60,    79,    62,
     123,    69,   124,    76,    57,    85,   120,    57,   130,   137,
      58,    14,    59,    58,    35,    59,    -3,     1,   150,    41,
     143,     0,     0,    60,    70,    62,    60,    79,    62,    57,
       0,     2,     0,    57,     0,    58,     0,    59,     3,    58,
       0,    59,   109,     0,     0,    50,    52,     0,    60,    61,
      62,    57,    60,    79,    62,     0,     2,    58,     0,    59,
       2,     0,    53,     3,     0,     0,     0,     3,     0,    83,
      60,    79,    62,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,     2,    29,    30,     0,   -86,    84,   132,     3,
     133,     0,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,   139,     0,   140,    95,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,   144,     0,     0,    95,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
     146,     0,   145,    95,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,     0,   147,    95,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,    95,    96,   136,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,     0,     0,    95,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,    95,   138,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,   108,    95,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     0,     0,     0,     0,
      95,    87,    88,    89,    90,    91,    92,     0,    94,     0,
       0,     0,     0,    95,    87,    88,    89,    90,    91,     0,
       0,    94,    88,    89,    90,    91,    95,     0,    94,     2,
      90,    91,     0,    95,    94,    65,     3,     0,     0,    95
};

static const yytype_int16 yycheck[] =
{
      35,    45,    11,    67,     1,     4,     3,    13,    43,     0,
      18,    23,    18,    22,    26,     6,    25,     1,    29,    16,
      28,    29,    57,    58,    59,     1,    17,    18,     3,    73,
      29,    40,    29,    45,    69,    20,    20,    28,    29,   103,
      15,     1,    50,     3,     3,    21,    21,    22,     1,    34,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    50,
      95,    73,     1,    98,    17,     1,    18,     3,     1,     8,
       0,    15,     4,    29,    21,    14,    28,    16,    22,    17,
      16,    20,    21,    16,    23,    24,    18,    26,    27,    28,
      29,     1,   127,    29,   129,    17,    28,    29,     8,    19,
       1,   136,    15,   145,    14,   147,    16,    20,   150,    22,
      20,     3,    21,    23,    24,    16,    26,    27,    28,    29,
       1,     5,     3,    17,     8,    16,    29,     8,    21,    17,
      14,     6,    16,    14,    18,    16,     0,     1,    25,    21,
     136,    -1,    -1,    27,    28,    29,    27,    28,    29,     8,
      -1,    15,    -1,     8,    -1,    14,    -1,    16,    22,    14,
      -1,    16,    17,    -1,    -1,     4,     1,    -1,    27,    28,
      29,     8,    27,    28,    29,    -1,    15,    14,    -1,    16,
      15,    -1,    17,    22,    -1,    -1,    -1,    22,    -1,     1,
      27,    28,    29,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    15,    16,    17,    -1,    18,    19,     1,    22,
       3,    -1,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,     1,    -1,     3,    18,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,     1,    -1,    -1,    18,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
       1,    -1,    17,    18,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    18,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    18,    19,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    18,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    18,    19,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    18,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      18,     6,     7,     8,     9,    10,    11,    -1,    13,    -1,
      -1,    -1,    -1,    18,     6,     7,     8,     9,    10,    -1,
      -1,    13,     7,     8,     9,    10,    18,    -1,    13,    15,
       9,    10,    -1,    18,    13,    21,    22,    -1,    -1,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    15,    22,    31,    32,    33,    35,    36,     3,
      29,    37,    38,     0,    32,     1,     3,    16,    29,    34,
      39,    40,    20,    35,    46,    47,    35,    41,    42,    16,
      17,    41,     1,     3,     4,    18,    28,    29,    34,     1,
      20,    43,    46,    39,    48,    49,    21,    46,    39,    17,
       4,    41,     1,    17,    41,    17,    34,     8,    14,    16,
      27,    28,    29,    50,    19,    21,    46,    46,    21,     5,
      28,    50,     3,     4,    48,    41,    17,     1,    17,    28,
      50,    50,    50,     1,    19,    16,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    18,    19,     1,    23,    24,
      26,    43,    44,    45,    50,    44,    50,    48,    17,    17,
      50,    51,    50,    50,    50,    50,    50,    50,    50,    50,
      29,    50,     3,     1,     3,    50,     1,    16,     1,    16,
      21,    44,     1,     3,     1,    21,     4,    17,    19,     1,
       3,    50,    50,    51,     1,    17,     1,    17,    45,    45,
      25,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    33,    33,
      33,    34,    34,    34,    35,    35,    36,    36,    36,    37,
      37,    38,    39,    39,    39,    39,    39,    40,    40,    40,
      40,    40,    40,    40,    40,    41,    41,    41,    42,    43,
      43,    43,    43,    44,    44,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      46,    46,    47,    47,    48,    48,    48,    49,    49,    49,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       2,     1,     3,     2,     1,     1,     5,     2,     4,     0,
       1,     1,     1,     4,     3,     4,     4,     4,     3,     3,
       4,     2,     3,     3,     4,     3,     1,     2,     2,     4,
       4,     4,     2,     0,     2,     2,     1,     3,     5,     7,
       5,     2,     3,     2,     2,     4,     2,     4,     2,     2,
       0,     2,     3,     2,     1,     3,     2,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     4,     3,     1,     1,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  case 2: /* Program: ExtDefList  */
#line 34 "syn.y"
                                              { syntax_tree=CreateUnterminalNode("Program",(yyloc).first_line,(yyvsp[0].type_node)); (yyval.type_node)=syntax_tree; }
#line 1372 "syn.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 36 "syn.y"
                                              { (yyval.type_node)=NULL;}
#line 1378 "syn.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 37 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ExtDefList",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1384 "syn.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 39 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ExtDef",(yyloc).first_line,(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node)); }
#line 1390 "syn.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 40 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ExtDef",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1396 "syn.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 41 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ExtDef",(yyloc).first_line,(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1402 "syn.tab.c"
    break;

  case 8: /* ExtDef: Specifier ExtDecList error  */
#line 42 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ';'");}
#line 1408 "syn.tab.c"
    break;

  case 9: /* ExtDef: Specifier error  */
#line 43 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ';'"); }
#line 1414 "syn.tab.c"
    break;

  case 10: /* ExtDef: error SEMI  */
#line 44 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).first_line,"Syntax error"); }
#line 1420 "syn.tab.c"
    break;

  case 11: /* ExtDecList: VarDec  */
#line 46 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ExtDecList",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1426 "syn.tab.c"
    break;

  case 12: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 47 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ExtDecList",(yyloc).first_line,(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node)); }
#line 1432 "syn.tab.c"
    break;

  case 13: /* ExtDecList: VarDec ExtDecList  */
#line 48 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ','"); }
#line 1438 "syn.tab.c"
    break;

  case 14: /* Specifier: TYPE  */
#line 54 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Specifier",(yyloc).first_line,(yyvsp[0].type_node)); }
#line 1444 "syn.tab.c"
    break;

  case 15: /* Specifier: StructSpecifier  */
#line 55 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Specifier",(yyloc).first_line,(yyvsp[0].type_node)); }
#line 1450 "syn.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 57 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("StructSpecifier",(yyloc).first_line,(yyvsp[-4].type_node));AddChild((yyval.type_node),(yyvsp[-3].type_node));AddChild((yyval.type_node),(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1456 "syn.tab.c"
    break;

  case 17: /* StructSpecifier: STRUCT Tag  */
#line 58 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("StructSpecifier",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1462 "syn.tab.c"
    break;

  case 18: /* StructSpecifier: STRUCT OptTag DefList RC  */
#line 59 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-2]).last_line,"Expected '{'");}
#line 1468 "syn.tab.c"
    break;

  case 19: /* OptTag: %empty  */
#line 60 "syn.y"
                                              { (yyval.type_node)=NULL;}
#line 1474 "syn.tab.c"
    break;

  case 20: /* OptTag: ID  */
#line 61 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("OptTag",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1480 "syn.tab.c"
    break;

  case 21: /* Tag: ID  */
#line 62 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("OptTag",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1486 "syn.tab.c"
    break;

  case 22: /* VarDec: ID  */
#line 70 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("VarDec",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1492 "syn.tab.c"
    break;

  case 23: /* VarDec: VarDec LB INT RB  */
#line 71 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("VarDec",(yyloc).first_line,(yyvsp[-3].type_node)); AddChild((yyval.type_node),(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1498 "syn.tab.c"
    break;

  case 24: /* VarDec: VarDec INT RB  */
#line 72 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-2]).last_line,"Expected '['");}
#line 1504 "syn.tab.c"
    break;

  case 25: /* VarDec: VarDec LB Exp RB  */
#line 73 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).first_line,"Array initial capacity must be an integer constant"); }
#line 1510 "syn.tab.c"
    break;

  case 26: /* VarDec: VarDec LB INT error  */
#line 74 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ']'");}
#line 1516 "syn.tab.c"
    break;

  case 27: /* FunDec: ID LP VarList RP  */
#line 77 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("FunDec",(yyloc).first_line,(yyvsp[-3].type_node));AddChild((yyval.type_node),(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1522 "syn.tab.c"
    break;

  case 28: /* FunDec: ID LP RP  */
#line 78 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("FunDec",(yyloc).first_line,(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1528 "syn.tab.c"
    break;

  case 29: /* FunDec: ID VarList RP  */
#line 79 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-2]).last_line,"Expected '('");}
#line 1534 "syn.tab.c"
    break;

  case 30: /* FunDec: ID LP VarList error  */
#line 80 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-1]).last_line,"Expected ')'");}
#line 1540 "syn.tab.c"
    break;

  case 31: /* FunDec: ID RP  */
#line 81 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-1]).last_line,"Expected '('");}
#line 1546 "syn.tab.c"
    break;

  case 32: /* FunDec: ID LP error  */
#line 82 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-1]).last_line,"Expected ')'");}
#line 1552 "syn.tab.c"
    break;

  case 33: /* FunDec: LP VarList RP  */
#line 83 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-2]).first_line,"Missing function name");}
#line 1558 "syn.tab.c"
    break;

  case 34: /* FunDec: ID LP error RP  */
#line 84 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-1]).first_line,"Syntax error");}
#line 1564 "syn.tab.c"
    break;

  case 35: /* VarList: ParamDec COMMA VarList  */
#line 87 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("VarList",(yyloc).first_line,(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1570 "syn.tab.c"
    break;

  case 36: /* VarList: ParamDec  */
#line 88 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("VarList",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1576 "syn.tab.c"
    break;

  case 37: /* VarList: ParamDec VarList  */
#line 89 "syn.y"
                                              { (yyval.type_node)=NULL;Error("B",(yylsp[-1]).last_line,"Expected ','");}
#line 1582 "syn.tab.c"
    break;

  case 38: /* ParamDec: Specifier VarDec  */
#line 91 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("ParamDec",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1588 "syn.tab.c"
    break;

  case 39: /* CompSt: LC DefList StmtList RC  */
#line 98 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("CompSt",(yyloc).first_line,(yyvsp[-3].type_node)); AddChild((yyval.type_node),(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1594 "syn.tab.c"
    break;

  case 40: /* CompSt: error DefList StmtList RC  */
#line 99 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-3]).first_line,"Expected '{'"); }
#line 1600 "syn.tab.c"
    break;

  case 41: /* CompSt: LC DefList StmtList error  */
#line 100 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected '}'"); }
#line 1606 "syn.tab.c"
    break;

  case 42: /* CompSt: error RC  */
#line 101 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).first_line,"Syntax error"); }
#line 1612 "syn.tab.c"
    break;

  case 43: /* StmtList: %empty  */
#line 104 "syn.y"
                                              { (yyval.type_node)=NULL;}
#line 1618 "syn.tab.c"
    break;

  case 44: /* StmtList: Stmt StmtList  */
#line 105 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("StmtList",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node)); }
#line 1624 "syn.tab.c"
    break;

  case 45: /* Stmt: Exp SEMI  */
#line 108 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Stmt",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node)); }
#line 1630 "syn.tab.c"
    break;

  case 46: /* Stmt: CompSt  */
#line 109 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Stmt",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1636 "syn.tab.c"
    break;

  case 47: /* Stmt: RETURN Exp SEMI  */
#line 110 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Stmt",(yyloc).first_line,(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1642 "syn.tab.c"
    break;

  case 48: /* Stmt: IF LP Exp RP Stmt  */
#line 111 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Stmt",(yyloc).first_line,(yyvsp[-4].type_node));AddChild((yyval.type_node),(yyvsp[-3].type_node));AddChild((yyval.type_node),(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1648 "syn.tab.c"
    break;

  case 49: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 112 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Stmt",(yyloc).first_line,(yyvsp[-6].type_node));AddChild((yyval.type_node),(yyvsp[-5].type_node));AddChild((yyval.type_node),(yyvsp[-4].type_node));AddChild((yyval.type_node),(yyvsp[-3].type_node));AddChild((yyval.type_node),(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1654 "syn.tab.c"
    break;

  case 50: /* Stmt: WHILE LP Exp RP Stmt  */
#line 113 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Stmt",(yyloc).first_line,(yyvsp[-4].type_node));AddChild((yyval.type_node),(yyvsp[-3].type_node));AddChild((yyval.type_node),(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1660 "syn.tab.c"
    break;

  case 51: /* Stmt: Exp error  */
#line 114 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ';'"); }
#line 1666 "syn.tab.c"
    break;

  case 52: /* Stmt: RETURN Exp error  */
#line 115 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ';'");}
#line 1672 "syn.tab.c"
    break;

  case 53: /* Stmt: RETURN SEMI  */
#line 116 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Return an empty expression is not allowed in C--"); }
#line 1678 "syn.tab.c"
    break;

  case 54: /* Stmt: RETURN error  */
#line 117 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ';'");}
#line 1684 "syn.tab.c"
    break;

  case 55: /* Stmt: IF LP Exp error  */
#line 118 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ')'"); }
#line 1690 "syn.tab.c"
    break;

  case 56: /* Stmt: IF error  */
#line 119 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected '('");}
#line 1696 "syn.tab.c"
    break;

  case 57: /* Stmt: WHILE LP Exp error  */
#line 120 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ')'");}
#line 1702 "syn.tab.c"
    break;

  case 58: /* Stmt: WHILE error  */
#line 121 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected '('");}
#line 1708 "syn.tab.c"
    break;

  case 59: /* Stmt: error SEMI  */
#line 122 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).first_line,"Syntax error");}
#line 1714 "syn.tab.c"
    break;

  case 60: /* DefList: %empty  */
#line 128 "syn.y"
                                              { (yyval.type_node)=NULL;}
#line 1720 "syn.tab.c"
    break;

  case 61: /* DefList: Def DefList  */
#line 129 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("DefList",(yyloc).first_line,(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1726 "syn.tab.c"
    break;

  case 62: /* Def: Specifier DecList SEMI  */
#line 131 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Def",(yyloc).first_line,(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node));AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1732 "syn.tab.c"
    break;

  case 63: /* Def: Specifier DecList  */
#line 132 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[0]).last_line,"Expected ';'");}
#line 1738 "syn.tab.c"
    break;

  case 64: /* DecList: Dec  */
#line 134 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("DecList",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1744 "syn.tab.c"
    break;

  case 65: /* DecList: Dec COMMA DecList  */
#line 135 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("DecList",(yyloc).first_line,(yyvsp[-2].type_node));AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node));}
#line 1750 "syn.tab.c"
    break;

  case 66: /* DecList: Dec DecList  */
#line 136 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected ','"); }
#line 1756 "syn.tab.c"
    break;

  case 67: /* Dec: VarDec  */
#line 138 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Dec",(yyloc).first_line,(yyvsp[0].type_node));}
#line 1762 "syn.tab.c"
    break;

  case 68: /* Dec: VarDec ASSIGNOP Exp  */
#line 139 "syn.y"
                                              { (yyval.type_node)=CreateUnterminalNode("Dec",(yyloc).first_line,(yyvsp[-2].type_node)); AddChild((yyval.type_node),(yyvsp[-1].type_node)); AddChild((yyval.type_node),(yyvsp[0].type_node)); }
#line 1768 "syn.tab.c"
    break;

  case 69: /* Dec: VarDec Exp  */
#line 140 "syn.y"
                                              { (yyval.type_node)=NULL; Error("B",(yylsp[-1]).last_line,"Expected '='"); }
#line 1774 "syn.tab.c"
    break;

  case 70: /* Exp: Exp ASSIGNOP Exp  */
#line 146 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1780 "syn.tab.c"
    break;

  case 71: /* Exp: Exp OR Exp  */
#line 147 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1786 "syn.tab.c"
    break;

  case 72: /* Exp: Exp AND Exp  */
#line 148 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1792 "syn.tab.c"
    break;

  case 73: /* Exp: Exp RELOP Exp  */
#line 149 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1798 "syn.tab.c"
    break;

  case 74: /* Exp: Exp PLUS Exp  */
#line 150 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1804 "syn.tab.c"
    break;

  case 75: /* Exp: Exp MINUS Exp  */
#line 151 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1810 "syn.tab.c"
    break;

  case 76: /* Exp: Exp STAR Exp  */
#line 152 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1816 "syn.tab.c"
    break;

  case 77: /* Exp: Exp DIV Exp  */
#line 153 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1822 "syn.tab.c"
    break;

  case 78: /* Exp: LP Exp RP  */
#line 154 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); }
#line 1828 "syn.tab.c"
    break;

  case 79: /* Exp: MINUS Exp  */
#line 155 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1834 "syn.tab.c"
    break;

  case 80: /* Exp: NOT Exp  */
#line 156 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1840 "syn.tab.c"
    break;

  case 81: /* Exp: ID LP Args RP  */
#line 157 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-3].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); }
#line 1846 "syn.tab.c"
    break;

  case 82: /* Exp: ID LP RP  */
#line 158 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); }
#line 1852 "syn.tab.c"
    break;

  case 83: /* Exp: Exp LB Exp RB  */
#line 159 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-3].type_node)); AddChild((yyval.type_node), (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); }
#line 1858 "syn.tab.c"
    break;

  case 84: /* Exp: Exp DOT ID  */
#line 160 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1864 "syn.tab.c"
    break;

  case 85: /* Exp: ID  */
#line 161 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[0].type_node)); }
#line 1870 "syn.tab.c"
    break;

  case 86: /* Exp: INT  */
#line 162 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[0].type_node)); }
#line 1876 "syn.tab.c"
    break;

  case 87: /* Exp: FLOAT  */
#line 163 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Exp", (yyloc).first_line, (yyvsp[0].type_node)); }
#line 1882 "syn.tab.c"
    break;

  case 88: /* Args: Exp COMMA Args  */
#line 166 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Args", (yyloc).first_line, (yyvsp[-2].type_node)); AddChild((yyval.type_node), (yyvsp[-1].type_node)); AddChild((yyval.type_node), (yyvsp[0].type_node)); }
#line 1888 "syn.tab.c"
    break;

  case 89: /* Args: Exp  */
#line 167 "syn.y"
                                              { (yyval.type_node) = CreateUnterminalNode("Args", (yyloc).first_line, (yyvsp[0].type_node)); }
#line 1894 "syn.tab.c"
    break;


#line 1898 "syn.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 170 "syn.y"

void yyerror(const char* msg){}
