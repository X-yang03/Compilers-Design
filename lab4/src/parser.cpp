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

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type* currentType;

#line 79 "src/parser.cpp"




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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOATNUM = 5,                   /* FLOATNUM  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_LPAREN = 12,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 13,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 15,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 16,                 /* SEMICOLON  */
  YYSYMBOL_LBRACKET = 17,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 18,                  /* RBRACKET  */
  YYSYMBOL_PARSE = 19,                     /* PARSE  */
  YYSYMBOL_ADD = 20,                       /* ADD  */
  YYSYMBOL_SUB = 21,                       /* SUB  */
  YYSYMBOL_MUL = 22,                       /* MUL  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_LESS = 27,                      /* LESS  */
  YYSYMBOL_LE = 28,                        /* LE  */
  YYSYMBOL_GREATER = 29,                   /* GREATER  */
  YYSYMBOL_GE = 30,                        /* GE  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_EQ = 32,                        /* EQ  */
  YYSYMBOL_NEQ = 33,                       /* NEQ  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_POS = 35,                       /* POS  */
  YYSYMBOL_MINUS = 36,                     /* MINUS  */
  YYSYMBOL_CONST = 37,                     /* CONST  */
  YYSYMBOL_RETURN = 38,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 39,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 40,                     /* BREAK  */
  YYSYMBOL_THEN = 41,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_Program = 43,                   /* Program  */
  YYSYMBOL_Stmts = 44,                     /* Stmts  */
  YYSYMBOL_Stmt = 45,                      /* Stmt  */
  YYSYMBOL_LVal = 46,                      /* LVal  */
  YYSYMBOL_AssignStmt = 47,                /* AssignStmt  */
  YYSYMBOL_BlockStmt = 48,                 /* BlockStmt  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_IfStmt = 50,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 51,                 /* WhileStmt  */
  YYSYMBOL_ContinueStmt = 52,              /* ContinueStmt  */
  YYSYMBOL_BreakStmt = 53,                 /* BreakStmt  */
  YYSYMBOL_ReturnStmt = 54,                /* ReturnStmt  */
  YYSYMBOL_Exp = 55,                       /* Exp  */
  YYSYMBOL_Cond = 56,                      /* Cond  */
  YYSYMBOL_FuncRealParams = 57,            /* FuncRealParams  */
  YYSYMBOL_PrimaryExp = 58,                /* PrimaryExp  */
  YYSYMBOL_UnaryExp = 59,                  /* UnaryExp  */
  YYSYMBOL_MulExp = 60,                    /* MulExp  */
  YYSYMBOL_AddExp = 61,                    /* AddExp  */
  YYSYMBOL_RelExp = 62,                    /* RelExp  */
  YYSYMBOL_EqExp = 63,                     /* EqExp  */
  YYSYMBOL_LAndExp = 64,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 65,                    /* LOrExp  */
  YYSYMBOL_Type = 66,                      /* Type  */
  YYSYMBOL_DeclStmt = 67,                  /* DeclStmt  */
  YYSYMBOL_ArrIndices = 68,                /* ArrIndices  */
  YYSYMBOL_ConstDefList = 69,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 70,                  /* ConstDef  */
  YYSYMBOL_VarDefList = 71,                /* VarDefList  */
  YYSYMBOL_VarDef = 72,                    /* VarDef  */
  YYSYMBOL_FuncDef = 73,                   /* FuncDef  */
  YYSYMBOL_74_2 = 74,                      /* $@2  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_FuncParams = 76,                /* FuncParams  */
  YYSYMBOL_FuncParam = 77                  /* FuncParam  */
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   135

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    52,    52,    57,    58,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    74,    92,    98,    97,   110,   113,
     118,   123,   128,   134,   140,   150,   155,   161,   167,   174,
     177,   181,   185,   193,   195,   199,   204,   209,   228,   230,
     234,   236,   242,   244,   250,   286,   288,   294,   301,   307,
     316,   318,   320,   325,   327,   335,   337,   344,   348,   352,
     358,   362,   376,   381,   389,   394,   401,   418,   423,   430,
     443,   457,   474,   482,   474,   505,   510,   515,   522
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "FLOATNUM", "IF", "ELSE", "WHILE", "INT", "VOID", "FLOAT", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", "LBRACKET", "RBRACKET",
  "PARSE", "ADD", "SUB", "MUL", "DIV", "MOD", "OR", "AND", "LESS", "LE",
  "GREATER", "GE", "ASSIGN", "EQ", "NEQ", "NOT", "POS", "MINUS", "CONST",
  "RETURN", "CONTINUE", "BREAK", "THEN", "$accept", "Program", "Stmts",
  "Stmt", "LVal", "AssignStmt", "BlockStmt", "$@1", "IfStmt", "WhileStmt",
  "ContinueStmt", "BreakStmt", "ReturnStmt", "Exp", "Cond",
  "FuncRealParams", "PrimaryExp", "UnaryExp", "MulExp", "AddExp", "RelExp",
  "EqExp", "LAndExp", "LOrExp", "Type", "DeclStmt", "ArrIndices",
  "ConstDefList", "ConstDef", "VarDefList", "VarDef", "FuncDef", "$@2",
  "$@3", "FuncParams", "FuncParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,   -31,     8,    19,   -31,   -31,   -31,   -31,    72,    67,
      11,    26,    35,    15,   -31,    42,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,    71,   -31,   -31,    67,    67,    15,    73,
      65,   -31,   -31,    67,    67,    67,    67,   -31,    74,   -31,
     -31,    62,   -15,   -31,   -31,   -31,   -31,    67,     2,    18,
     -31,    78,   -15,    38,    24,    68,    70,    80,     1,    69,
      27,   -31,    67,    89,   -31,   -31,   -31,   -31,    67,    67,
      67,    67,    67,    95,    67,    67,    96,   100,   -31,   111,
      15,    67,    67,    67,    67,    67,    67,    67,    67,    15,
     -31,    67,   -31,    73,   -31,    17,   -31,   -31,   -31,   -31,
      62,    62,   -31,    97,   -31,    67,    72,    -9,   -31,   109,
     -15,   -15,   -15,   -15,    38,    38,    24,    68,   -31,   -31,
     -31,   -31,    67,   -31,   101,   115,   102,   -31,    15,   -31,
     -31,   -31,    72,   107,   -31,   -31,   108,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    14,     0,     0,    57,    58,    59,    16,     0,     0,
       0,     0,     0,     2,     3,     0,     5,     6,     7,     8,
      13,    12,     9,     0,    10,    11,     0,     0,     0,     0,
      14,    30,    31,     0,     0,     0,     0,    29,     0,    33,
      38,    42,    24,    21,    22,     1,     4,     0,    69,     0,
      68,     0,    45,    50,    53,    55,    25,     0,     0,     0,
       0,    65,    28,     0,    34,    35,    36,    23,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    60,     0,    27,     0,    32,    39,    40,    41,
      43,    44,    15,     0,    70,     0,    77,    69,    67,    18,
      46,    48,    47,    49,    51,    52,    54,    56,    20,    66,
      64,    37,     0,    63,     0,     0,    73,    76,     0,    26,
      62,    78,     0,     0,    19,    75,     0,    74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,    98,   -11,     0,   -31,   -13,   -31,   -31,   -31,
     -31,   -31,   -31,   -30,   103,   -31,   -31,    28,   -21,    22,
     -26,    37,    39,   -31,    -7,   -31,   -31,   -31,    36,   -31,
      52,   -31,   -31,   -31,   -31,     3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    37,    16,    17,    28,    18,    19,
      20,    21,    22,    38,    51,    95,    39,    40,    41,    42,
      53,    54,    55,    56,    23,    24,    76,    60,    61,    49,
      50,    25,    77,   133,   126,   127
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,    29,    46,    63,     1,    71,    72,     2,    74,     3,
       4,     5,     6,    15,   -72,     7,    90,    73,     1,    74,
      26,     2,    75,     3,     4,     5,     6,    43,    15,     7,
     121,    27,    94,    75,    78,    45,   122,    79,     8,     9,
      10,    11,    44,    92,   103,   104,    93,    46,    52,    52,
     100,   101,     8,     9,    10,    11,    85,    86,    15,   114,
     115,   119,    64,    65,    66,    81,    82,    83,    84,   109,
      30,    31,    32,    47,    48,   124,    59,    62,   118,    33,
      15,     4,     5,     6,    68,    69,    70,    34,    35,    15,
      67,    80,   129,    89,    87,    88,    97,    98,    99,   125,
      91,    36,    96,   110,   111,   112,   113,    52,    52,    52,
      52,   102,   106,   105,   107,   123,   128,   134,   131,   130,
     136,   132,     7,   137,   116,   125,    58,   117,    15,   120,
      57,   108,     0,     0,     0,   135
};

static const yytype_int16 yycheck[] =
{
       0,     8,    13,    33,     3,    20,    21,     6,    17,     8,
       9,    10,    11,    13,    12,    14,    15,    47,     3,    17,
      12,     6,    31,     8,     9,    10,    11,    16,    28,    14,
      13,    12,    62,    31,    16,     0,    19,    19,    37,    38,
      39,    40,    16,    16,    74,    75,    19,    58,    26,    27,
      71,    72,    37,    38,    39,    40,    32,    33,    58,    85,
      86,    91,    34,    35,    36,    27,    28,    29,    30,    80,
       3,     4,     5,    31,     3,   105,     3,    12,    89,    12,
      80,     9,    10,    11,    22,    23,    24,    20,    21,    89,
      16,    13,   122,    13,    26,    25,    68,    69,    70,   106,
      31,    34,    13,    81,    82,    83,    84,    85,    86,    87,
      88,    16,    12,    17,     3,    18,     7,   128,     3,    18,
      13,    19,    14,   136,    87,   132,    28,    88,   128,    93,
      27,    79,    -1,    -1,    -1,   132
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     6,     8,     9,    10,    11,    14,    37,    38,
      39,    40,    43,    44,    45,    46,    47,    48,    50,    51,
      52,    53,    54,    66,    67,    73,    12,    12,    49,    66,
       3,     4,     5,    12,    20,    21,    34,    46,    55,    58,
      59,    60,    61,    16,    16,     0,    45,    31,     3,    71,
      72,    56,    61,    62,    63,    64,    65,    56,    44,     3,
      69,    70,    12,    55,    59,    59,    59,    16,    22,    23,
      24,    20,    21,    55,    17,    31,    68,    74,    16,    19,
      13,    27,    28,    29,    30,    32,    33,    26,    25,    13,
      15,    31,    16,    19,    55,    57,    13,    59,    59,    59,
      60,    60,    16,    55,    55,    17,    12,     3,    72,    45,
      61,    61,    61,    61,    62,    62,    63,    64,    45,    55,
      70,    13,    19,    18,    55,    66,    76,    77,     7,    55,
      18,     3,    19,    75,    45,    77,    13,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    46,    47,    49,    48,    50,    50,
      51,    52,    53,    54,    55,    56,    57,    57,    57,    58,
      58,    58,    58,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    61,    61,    61,    62,    62,    62,    62,    62,
      63,    63,    63,    64,    64,    65,    65,    66,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    71,    71,    72,
      72,    72,    74,    75,    73,    76,    76,    76,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     0,     4,     5,     7,
       5,     2,     2,     3,     1,     1,     3,     1,     0,     1,
       1,     1,     3,     1,     2,     2,     2,     4,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     1,     1,
       4,     3,     4,     3,     3,     1,     3,     3,     1,     1,
       3,     2,     0,     0,     8,     3,     1,     0,     2
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
#  undef YYSTACK_RELOCATE
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
  case 2: /* Program: Stmts  */
#line 52 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1240 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmt  */
#line 57 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1246 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmts Stmt  */
#line 58 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1254 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 63 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1260 "src/parser.cpp"
    break;

  case 6: /* Stmt: BlockStmt  */
#line 64 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1266 "src/parser.cpp"
    break;

  case 7: /* Stmt: IfStmt  */
#line 65 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1272 "src/parser.cpp"
    break;

  case 8: /* Stmt: WhileStmt  */
#line 66 "src/parser.y"
               {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1278 "src/parser.cpp"
    break;

  case 9: /* Stmt: ReturnStmt  */
#line 67 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1284 "src/parser.cpp"
    break;

  case 10: /* Stmt: DeclStmt  */
#line 68 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1290 "src/parser.cpp"
    break;

  case 11: /* Stmt: FuncDef  */
#line 69 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1296 "src/parser.cpp"
    break;

  case 12: /* Stmt: BreakStmt  */
#line 70 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1302 "src/parser.cpp"
    break;

  case 13: /* Stmt: ContinueStmt  */
#line 71 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1308 "src/parser.cpp"
    break;

  case 14: /* LVal: ID  */
#line 74 "src/parser.y"
         {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se);
        
        std::cout<<(yyval.exprtype)->getType()->toStr();
        std::cout<<"test"<<std::endl;
        delete [](yyvsp[0].strtype);
    }
#line 1328 "src/parser.cpp"
    break;

  case 15: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 92 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1336 "src/parser.cpp"
    break;

  case 16: /* $@1: %empty  */
#line 98 "src/parser.y"
        {
            identifiers = new SymbolTable(identifiers);
        }
#line 1344 "src/parser.cpp"
    break;

  case 17: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 102 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1355 "src/parser.cpp"
    break;

  case 18: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 110 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1363 "src/parser.cpp"
    break;

  case 19: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 113 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1371 "src/parser.cpp"
    break;

  case 20: /* WhileStmt: WHILE LPAREN Cond RPAREN Stmt  */
#line 118 "src/parser.y"
                                   {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1379 "src/parser.cpp"
    break;

  case 21: /* ContinueStmt: CONTINUE SEMICOLON  */
#line 123 "src/parser.y"
                        {
        (yyval.stmttype) = new ContinueStmt();
    }
#line 1387 "src/parser.cpp"
    break;

  case 22: /* BreakStmt: BREAK SEMICOLON  */
#line 128 "src/parser.y"
                     {
        (yyval.stmttype) = new BreakStmt();
    }
#line 1395 "src/parser.cpp"
    break;

  case 23: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 134 "src/parser.y"
                        {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1403 "src/parser.cpp"
    break;

  case 24: /* Exp: AddExp  */
#line 140 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1409 "src/parser.cpp"
    break;

  case 25: /* Cond: LOrExp  */
#line 150 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1415 "src/parser.cpp"
    break;

  case 26: /* FuncRealParams: FuncRealParams PARSE Exp  */
#line 155 "src/parser.y"
                            {
        FuncCallParamsNode* node = (FuncCallParamsNode*) (yyvsp[-2].stmttype);
        node->append((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 1425 "src/parser.cpp"
    break;

  case 27: /* FuncRealParams: Exp  */
#line 161 "src/parser.y"
       {
        FuncCallParamsNode* node = new FuncCallParamsNode();
        node->append((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 1435 "src/parser.cpp"
    break;

  case 28: /* FuncRealParams: %empty  */
#line 167 "src/parser.y"
          {
        (yyval.stmttype) = nullptr;
    }
#line 1443 "src/parser.cpp"
    break;

  case 29: /* PrimaryExp: LVal  */
#line 174 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1451 "src/parser.cpp"
    break;

  case 30: /* PrimaryExp: INTEGER  */
#line 177 "src/parser.y"
              {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].iType));
        (yyval.exprtype) = new Constant(se);
    }
#line 1460 "src/parser.cpp"
    break;

  case 31: /* PrimaryExp: FLOATNUM  */
#line 181 "src/parser.y"
               {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType,(yyvsp[0].fType));
        (yyval.exprtype) = new Constant(se);
    }
#line 1469 "src/parser.cpp"
    break;

  case 32: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 185 "src/parser.y"
                       {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1477 "src/parser.cpp"
    break;

  case 33: /* UnaryExp: PrimaryExp  */
#line 193 "src/parser.y"
              {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1483 "src/parser.cpp"
    break;

  case 34: /* UnaryExp: ADD UnaryExp  */
#line 195 "src/parser.y"
                {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1491 "src/parser.cpp"
    break;

  case 35: /* UnaryExp: SUB UnaryExp  */
#line 199 "src/parser.y"
                {
        SymbolEntry *se = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryOpExpr(se, UnaryOpExpr::SUB, (yyvsp[0].exprtype));
    }
#line 1500 "src/parser.cpp"
    break;

  case 36: /* UnaryExp: NOT UnaryExp  */
#line 204 "src/parser.y"
                {
         SymbolEntry *se = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
         (yyval.exprtype) = new UnaryOpExpr(se, UnaryOpExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1509 "src/parser.cpp"
    break;

  case 37: /* UnaryExp: ID LPAREN FuncRealParams RPAREN  */
#line 209 "src/parser.y"
                                   { // 函数调用
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-3].strtype));
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel());
        (yyval.exprtype) = new FuncCallNode(tmp, new Id(se), (FuncCallParamsNode*)(yyvsp[-1].stmttype));
    }
#line 1526 "src/parser.cpp"
    break;

  case 38: /* MulExp: UnaryExp  */
#line 228 "src/parser.y"
            {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1532 "src/parser.cpp"
    break;

  case 39: /* MulExp: MulExp MUL UnaryExp  */
#line 230 "src/parser.y"
                        {

    }
#line 1540 "src/parser.cpp"
    break;

  case 40: /* MulExp: MulExp DIV UnaryExp  */
#line 234 "src/parser.y"
                        {}
#line 1546 "src/parser.cpp"
    break;

  case 41: /* MulExp: MulExp MOD UnaryExp  */
#line 236 "src/parser.y"
                        {}
#line 1552 "src/parser.cpp"
    break;

  case 42: /* AddExp: MulExp  */
#line 242 "src/parser.y"
          {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1558 "src/parser.cpp"
    break;

  case 43: /* AddExp: AddExp ADD MulExp  */
#line 245 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1567 "src/parser.cpp"
    break;

  case 44: /* AddExp: AddExp SUB MulExp  */
#line 251 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1576 "src/parser.cpp"
    break;

  case 45: /* RelExp: AddExp  */
#line 286 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1582 "src/parser.cpp"
    break;

  case 46: /* RelExp: RelExp LESS AddExp  */
#line 289 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1591 "src/parser.cpp"
    break;

  case 47: /* RelExp: RelExp GREATER AddExp  */
#line 295 "src/parser.y"
    {
        printf("greater!\n");
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATER, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1601 "src/parser.cpp"
    break;

  case 48: /* RelExp: RelExp LE AddExp  */
#line 302 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LE, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1610 "src/parser.cpp"
    break;

  case 49: /* RelExp: RelExp GE AddExp  */
#line 308 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GE, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1619 "src/parser.cpp"
    break;

  case 50: /* EqExp: RelExp  */
#line 316 "src/parser.y"
          {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1625 "src/parser.cpp"
    break;

  case 51: /* EqExp: EqExp EQ RelExp  */
#line 318 "src/parser.y"
                   {}
#line 1631 "src/parser.cpp"
    break;

  case 52: /* EqExp: EqExp NEQ RelExp  */
#line 320 "src/parser.y"
                    {}
#line 1637 "src/parser.cpp"
    break;

  case 53: /* LAndExp: EqExp  */
#line 325 "src/parser.y"
          {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1643 "src/parser.cpp"
    break;

  case 54: /* LAndExp: LAndExp AND EqExp  */
#line 328 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1652 "src/parser.cpp"
    break;

  case 55: /* LOrExp: LAndExp  */
#line 335 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1658 "src/parser.cpp"
    break;

  case 56: /* LOrExp: LOrExp OR LAndExp  */
#line 338 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1667 "src/parser.cpp"
    break;

  case 57: /* Type: INT  */
#line 344 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
        currentType = TypeSystem::intType;
    }
#line 1676 "src/parser.cpp"
    break;

  case 58: /* Type: VOID  */
#line 348 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
        currentType = TypeSystem::voidType;
    }
#line 1685 "src/parser.cpp"
    break;

  case 59: /* Type: FLOAT  */
#line 352 "src/parser.y"
            {
        (yyval.type) = TypeSystem::floatType;
        currentType = TypeSystem::floatType;
    }
#line 1694 "src/parser.cpp"
    break;

  case 60: /* DeclStmt: CONST Type ConstDefList SEMICOLON  */
#line 358 "src/parser.y"
                                       {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1702 "src/parser.cpp"
    break;

  case 61: /* DeclStmt: Type VarDefList SEMICOLON  */
#line 362 "src/parser.y"
                                {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1710 "src/parser.cpp"
    break;

  case 62: /* ArrIndices: ArrIndices LBRACKET Exp RBRACKET  */
#line 376 "src/parser.y"
                                         {
            ArrayindiceNode* node = (ArrayindiceNode*)(yyvsp[-3].stmttype);
            node->append((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;          
        }
#line 1720 "src/parser.cpp"
    break;

  case 63: /* ArrIndices: LBRACKET Exp RBRACKET  */
#line 381 "src/parser.y"
                              {
            ArrayindiceNode* node = new ArrayindiceNode();
            node->append((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;
        }
#line 1730 "src/parser.cpp"
    break;

  case 64: /* ConstDefList: ConstDefList PARSE ConstDef  */
#line 389 "src/parser.y"
                                 {
            DeclStmt* node = (DeclStmt*) (yyvsp[-2].stmttype);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
    }
#line 1740 "src/parser.cpp"
    break;

  case 65: /* ConstDefList: ConstDef  */
#line 394 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(true);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node; 
    }
#line 1750 "src/parser.cpp"
    break;

  case 66: /* ConstDef: ID ASSIGN Exp  */
#line 401 "src/parser.y"
                    {
        //const 必须赋初值
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), (Node*)(yyvsp[0].exprtype), true, false);
        }
#line 1769 "src/parser.cpp"
    break;

  case 67: /* VarDefList: VarDefList PARSE VarDef  */
#line 418 "src/parser.y"
                                {
            DeclStmt* node = (DeclStmt*) (yyvsp[-2].stmttype);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 1779 "src/parser.cpp"
    break;

  case 68: /* VarDefList: VarDef  */
#line 423 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(false);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 1789 "src/parser.cpp"
    break;

  case 69: /* VarDef: ID  */
#line 430 "src/parser.y"
           {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 1807 "src/parser.cpp"
    break;

  case 70: /* VarDef: ID ASSIGN Exp  */
#line 443 "src/parser.y"
                      {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), (Node*)(yyvsp[0].exprtype), false, false);
        }
#line 1825 "src/parser.cpp"
    break;

  case 71: /* VarDef: ID ArrIndices  */
#line 457 "src/parser.y"
                      {
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-1].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-1].strtype), se);
            Id* id = new Id(se);
            id->addIndices((ArrayindiceNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 1845 "src/parser.cpp"
    break;

  case 72: /* $@2: %empty  */
#line 474 "src/parser.y"
            {
        // 返回值类型是ID的type，函数定义中需要创建新的符号表
        Type *funcType;
        funcType = new FunctionType((yyvsp[-1].type),{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        identifiers = new SymbolTable(identifiers);
    }
#line 1858 "src/parser.cpp"
    break;

  case 73: /* $@3: %empty  */
#line 482 "src/parser.y"
                     {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-3].strtype));
            assert(se != nullptr);
            if((yyvsp[0].stmttype)!=nullptr){
                ((FunctionType*)(se->getType()))/*强转为Function Type*/->setparamsType/*设置参数类型*/(((FuncDefParamsNode*)(yyvsp[0].stmttype))->getParamsType());
            }   
        }
#line 1871 "src/parser.cpp"
    break;

  case 74: /* FuncDef: Type ID $@2 LPAREN FuncParams $@3 RPAREN BlockStmt  */
#line 492 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-6].strtype));
        assert(se != nullptr);
        (yyval.stmttype) = new FunctionDef(se, (yyvsp[0].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-6].strtype);
    }
#line 1886 "src/parser.cpp"
    break;

  case 75: /* FuncParams: FuncParams PARSE FuncParam  */
#line 505 "src/parser.y"
                                   {
            FuncDefParamsNode* node = (FuncDefParamsNode*)(yyvsp[-2].stmttype);
            node->addNext(((DefNode*)(yyvsp[0].stmttype))->getId());
            (yyval.stmttype) = node;
        }
#line 1896 "src/parser.cpp"
    break;

  case 76: /* FuncParams: FuncParam  */
#line 510 "src/parser.y"
                  {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext(((DefNode*)(yyvsp[0].stmttype))->getId());
            (yyval.stmttype) = node;
        }
#line 1906 "src/parser.cpp"
    break;

  case 77: /* FuncParams: %empty  */
#line 515 "src/parser.y"
               {
            (yyval.stmttype) = nullptr;
        }
#line 1914 "src/parser.cpp"
    break;

  case 78: /* FuncParam: Type ID  */
#line 522 "src/parser.y"
                {
            SymbolEntry *se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 1924 "src/parser.cpp"
    break;


#line 1928 "src/parser.cpp"

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 549 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
