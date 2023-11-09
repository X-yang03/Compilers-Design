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
  YYSYMBOL_CONST = 35,                     /* CONST  */
  YYSYMBOL_RETURN = 36,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 37,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 38,                     /* BREAK  */
  YYSYMBOL_THEN = 39,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_Stmts = 42,                     /* Stmts  */
  YYSYMBOL_Stmt = 43,                      /* Stmt  */
  YYSYMBOL_LVal = 44,                      /* LVal  */
  YYSYMBOL_AssignStmt = 45,                /* AssignStmt  */
  YYSYMBOL_BlockStmt = 46,                 /* BlockStmt  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_IfStmt = 48,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 49,                 /* WhileStmt  */
  YYSYMBOL_ContinueStmt = 50,              /* ContinueStmt  */
  YYSYMBOL_BreakStmt = 51,                 /* BreakStmt  */
  YYSYMBOL_ReturnStmt = 52,                /* ReturnStmt  */
  YYSYMBOL_ExpStmt = 53,                   /* ExpStmt  */
  YYSYMBOL_Exps = 54,                      /* Exps  */
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
  YYSYMBOL_ConstArrayInitVal = 71,         /* ConstArrayInitVal  */
  YYSYMBOL_ConstArrayInitValList = 72,     /* ConstArrayInitValList  */
  YYSYMBOL_ArrayInitVal = 73,              /* ArrayInitVal  */
  YYSYMBOL_ArrayInitValList = 74,          /* ArrayInitValList  */
  YYSYMBOL_VarDefList = 75,                /* VarDefList  */
  YYSYMBOL_VarDef = 76,                    /* VarDef  */
  YYSYMBOL_FuncDef = 77,                   /* FuncDef  */
  YYSYMBOL_78_2 = 78,                      /* $@2  */
  YYSYMBOL_79_3 = 79,                      /* $@3  */
  YYSYMBOL_FuncParams = 80,                /* FuncParams  */
  YYSYMBOL_FuncParam = 81                  /* FuncParam  */
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
#define YYFINAL  55
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  169

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    51,    51,    56,    57,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    75,    91,   108,   114,
     113,   126,   129,   134,   139,   144,   150,   156,   160,   165,
     174,   184,   189,   195,   201,   208,   211,   215,   219,   226,
     228,   232,   237,   242,   261,   263,   274,   285,   300,   302,
     314,   329,   331,   337,   344,   350,   359,   361,   366,   374,
     376,   384,   386,   393,   397,   401,   407,   411,   418,   423,
     431,   436,   443,   458,   475,   480,   483,   489,   494,   502,
     507,   510,   516,   521,   529,   534,   541,   554,   567,   582,
     599,   607,   599,   630,   635,   640,   647,   652,   669
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
  "GREATER", "GE", "ASSIGN", "EQ", "NEQ", "NOT", "CONST", "RETURN",
  "CONTINUE", "BREAK", "THEN", "$accept", "Program", "Stmts", "Stmt",
  "LVal", "AssignStmt", "BlockStmt", "$@1", "IfStmt", "WhileStmt",
  "ContinueStmt", "BreakStmt", "ReturnStmt", "ExpStmt", "Exps", "Exp",
  "Cond", "FuncRealParams", "PrimaryExp", "UnaryExp", "MulExp", "AddExp",
  "RelExp", "EqExp", "LAndExp", "LOrExp", "Type", "DeclStmt", "ArrIndices",
  "ConstDefList", "ConstDef", "ConstArrayInitVal", "ConstArrayInitValList",
  "ArrayInitVal", "ArrayInitValList", "VarDefList", "VarDef", "FuncDef",
  "$@2", "$@3", "FuncParams", "FuncParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-91)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,    44,  -121,  -121,     0,    27,  -121,  -121,  -121,   199,
    -121,  -121,   199,   199,   199,   111,   199,    58,    66,     4,
      10,  -121,    -4,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
      84,    77,  -121,  -121,  -121,   110,    15,   102,  -121,  -121,
     199,   199,   109,   199,   199,  -121,   115,    10,  -121,  -121,
    -121,   127,   119,  -121,  -121,  -121,  -121,   199,   199,  -121,
     199,   199,   199,   199,   199,    11,    57,  -121,  -121,    62,
     122,   199,   128,    15,    69,    81,   116,   118,   131,  -121,
     157,    12,   100,  -121,  -121,   129,  -121,  -121,  -121,  -121,
     110,   110,   199,    20,   134,  -121,   144,  -121,   199,  -121,
     133,    10,   199,   199,   199,   199,   199,   199,   199,   199,
      10,  -121,   199,    23,  -121,   127,  -121,  -121,   176,   111,
      24,  -121,  -121,  -121,   142,    15,    15,    15,    15,    69,
      69,    81,   116,  -121,  -121,   195,  -121,    74,  -121,  -121,
     149,   135,  -121,    10,    97,  -121,  -121,  -121,  -121,    45,
     136,   111,   143,  -121,  -121,  -121,    72,  -121,   176,   139,
    -121,   145,  -121,   195,  -121,   141,  -121,  -121,   109
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    36,    37,     0,     0,    63,    64,    65,     0,
      19,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,    35,     5,     6,     7,     8,    13,    12,     9,
      15,     0,    29,    39,    44,    48,    30,     0,    10,    11,
      34,     0,    17,     0,     0,    35,     0,     0,    40,    41,
      42,     0,     0,    24,    25,     1,     4,     0,     0,    27,
       0,     0,     0,     0,     0,    86,     0,    85,    33,     0,
       0,     0,     0,    51,    56,    59,    61,    31,     0,    38,
       0,     0,     0,    71,    26,     0,    28,    45,    46,    47,
      49,    50,     0,    88,     0,    67,     0,    43,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    66,     0,    18,    87,     0,    95,
      86,    84,    32,    68,    21,    52,    54,    53,    55,    57,
      58,    60,    62,    23,    72,     0,    70,     0,    79,    89,
       0,    91,    94,     0,     0,    74,    73,    81,    83,     0,
      96,     0,     0,    22,    76,    78,     0,    80,     0,     0,
      93,     0,    75,     0,    82,    98,    92,    77,    97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,   123,   -18,     5,  -121,    13,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,    -8,   132,  -121,  -121,    -3,
      60,   -37,    31,    67,    73,  -121,   -12,  -121,    -1,  -121,
      68,  -110,  -121,  -120,  -121,  -121,    88,  -121,  -121,  -121,
    -121,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    45,    23,    24,    47,    25,    26,
      27,    28,    29,    30,    31,    32,    72,    69,    33,    34,
      35,    36,    74,    75,    76,    77,    37,    38,    93,    82,
      83,   146,   156,   139,   149,    66,    67,    39,    94,   152,
     141,   142
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    46,    56,    51,    55,    22,    73,    73,    52,    48,
      49,    50,    43,     1,     2,     3,     4,   148,     5,     6,
       7,     8,     9,   -90,    10,    22,    11,    57,    41,    41,
      12,    13,    68,    70,   155,    63,    64,    71,   164,    44,
      71,    41,    92,   112,    14,    15,    16,    17,    18,    85,
      86,   118,    22,   167,   135,    92,    40,    87,    88,    89,
     157,    41,    56,   100,   158,   125,   126,   127,   128,    73,
      73,    73,    73,    95,    53,    97,    96,     1,     2,     3,
     113,    98,    54,   124,   117,    22,     9,   162,   137,   147,
     122,   163,   133,    59,    12,    13,   102,   103,   104,   105,
       1,     2,     3,    58,   134,    65,    22,   140,    14,     9,
     138,   144,   154,   106,   107,    22,   114,    12,    13,   115,
       6,     7,     8,    90,    91,   153,    71,   145,    79,   138,
      81,    14,    60,    61,    62,    84,   145,   129,   130,   140,
      99,   101,   108,   109,   110,   116,   119,   120,    22,   143,
     138,   123,   150,   159,   151,   145,   161,   165,    41,    10,
       1,     2,     3,     4,   168,     5,     6,     7,     8,     9,
      80,    10,   111,    11,   166,   131,    78,    12,    13,     1,
       2,     3,   132,   136,   121,   160,     0,     0,     9,     0,
     137,    14,    15,    16,    17,    18,    12,    13,     1,     2,
       3,     0,     1,     2,     3,     0,     0,     9,     0,   144,
      14,     9,     0,     0,     0,    12,    13,     0,     0,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,     0,    14
};

static const yytype_int16 yycheck[] =
{
       1,     9,    20,    15,     0,     0,    43,    44,    16,    12,
      13,    14,    12,     3,     4,     5,     6,   137,     8,     9,
      10,    11,    12,    12,    14,    20,    16,    31,    17,    17,
      20,    21,    40,    41,   144,    20,    21,    17,   158,    12,
      17,    17,    31,    31,    34,    35,    36,    37,    38,    57,
      58,    31,    47,   163,    31,    31,    12,    60,    61,    62,
      15,    17,    80,    71,    19,   102,   103,   104,   105,   106,
     107,   108,   109,    16,    16,    13,    19,     3,     4,     5,
      81,    19,    16,   101,    92,    80,    12,    15,    14,    15,
      98,    19,   110,    16,    20,    21,    27,    28,    29,    30,
       3,     4,     5,    19,   112,     3,   101,   119,    34,    12,
     118,    14,    15,    32,    33,   110,    16,    20,    21,    19,
       9,    10,    11,    63,    64,   143,    17,   135,    13,   137,
       3,    34,    22,    23,    24,    16,   144,   106,   107,   151,
      18,    13,    26,    25,    13,    16,    12,     3,   143,     7,
     158,    18,     3,    17,    19,   163,    13,    18,    17,    14,
       3,     4,     5,     6,   165,     8,     9,    10,    11,    12,
      47,    14,    15,    16,   161,   108,    44,    20,    21,     3,
       4,     5,   109,   115,    96,   151,    -1,    -1,    12,    -1,
      14,    34,    35,    36,    37,    38,    20,    21,     3,     4,
       5,    -1,     3,     4,     5,    -1,    -1,    12,    -1,    14,
      34,    12,    -1,    -1,    -1,    20,    21,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      14,    16,    20,    21,    34,    35,    36,    37,    38,    41,
      42,    43,    44,    45,    46,    48,    49,    50,    51,    52,
      53,    54,    55,    58,    59,    60,    61,    66,    67,    77,
      12,    17,    68,    12,    12,    44,    55,    47,    59,    59,
      59,    66,    55,    16,    16,     0,    43,    31,    19,    16,
      22,    23,    24,    20,    21,     3,    75,    76,    55,    57,
      55,    17,    56,    61,    62,    63,    64,    65,    56,    13,
      42,     3,    69,    70,    16,    55,    55,    59,    59,    59,
      60,    60,    31,    68,    78,    16,    19,    13,    19,    18,
      55,    13,    27,    28,    29,    30,    32,    33,    26,    25,
      13,    15,    31,    68,    16,    19,    16,    55,    31,    12,
       3,    76,    55,    18,    43,    61,    61,    61,    61,    62,
      62,    63,    64,    43,    55,    31,    70,    14,    55,    73,
      66,    80,    81,     7,    14,    55,    71,    15,    73,    74,
       3,    19,    79,    43,    15,    71,    72,    15,    19,    17,
      81,    13,    15,    19,    73,    18,    46,    71,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    45,    47,
      46,    48,    48,    49,    50,    51,    52,    53,    54,    54,
      55,    56,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    59,    60,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    62,    63,    63,    63,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    71,    71,    72,    72,    73,
      73,    73,    74,    74,    75,    75,    76,    76,    76,    76,
      78,    79,    77,    80,    80,    80,    81,    81,    81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     0,
       4,     5,     7,     5,     2,     2,     3,     2,     3,     1,
       1,     1,     3,     1,     0,     1,     1,     1,     3,     1,
       2,     2,     2,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     1,     1,     4,     3,     4,     3,
       3,     1,     3,     4,     1,     3,     2,     3,     1,     1,
       3,     2,     3,     1,     3,     1,     1,     3,     2,     4,
       0,     0,     8,     3,     1,     0,     2,     5,     4
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
#line 51 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1282 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmt  */
#line 56 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1288 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmts Stmt  */
#line 57 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1296 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 62 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1302 "src/parser.cpp"
    break;

  case 6: /* Stmt: BlockStmt  */
#line 63 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1308 "src/parser.cpp"
    break;

  case 7: /* Stmt: IfStmt  */
#line 64 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1314 "src/parser.cpp"
    break;

  case 8: /* Stmt: WhileStmt  */
#line 65 "src/parser.y"
               {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1320 "src/parser.cpp"
    break;

  case 9: /* Stmt: ReturnStmt  */
#line 66 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1326 "src/parser.cpp"
    break;

  case 10: /* Stmt: DeclStmt  */
#line 67 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1332 "src/parser.cpp"
    break;

  case 11: /* Stmt: FuncDef  */
#line 68 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1338 "src/parser.cpp"
    break;

  case 12: /* Stmt: BreakStmt  */
#line 69 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1344 "src/parser.cpp"
    break;

  case 13: /* Stmt: ContinueStmt  */
#line 70 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1350 "src/parser.cpp"
    break;

  case 14: /* Stmt: SEMICOLON  */
#line 71 "src/parser.y"
               {(yyval.stmttype) = new EmptyStmtNode() ;}
#line 1356 "src/parser.cpp"
    break;

  case 15: /* Stmt: ExpStmt  */
#line 72 "src/parser.y"
             {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1362 "src/parser.cpp"
    break;

  case 16: /* LVal: ID  */
#line 75 "src/parser.y"
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
#line 1382 "src/parser.cpp"
    break;

  case 17: /* LVal: ID ArrIndices  */
#line 91 "src/parser.y"
                  {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-1].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-1].strtype));
            delete [](char*)(yyvsp[-1].strtype);
            assert(se != nullptr);
        }
        Id* newId = new Id(se);
        newId->addIndices((ArrayindiceNode*)(yyvsp[0].stmttype));
        (yyval.exprtype) =  newId;
        delete [](yyvsp[-1].strtype);
    }
#line 1401 "src/parser.cpp"
    break;

  case 18: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 108 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1409 "src/parser.cpp"
    break;

  case 19: /* $@1: %empty  */
#line 114 "src/parser.y"
        {
            identifiers = new SymbolTable(identifiers);
        }
#line 1417 "src/parser.cpp"
    break;

  case 20: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 118 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1428 "src/parser.cpp"
    break;

  case 21: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 126 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1436 "src/parser.cpp"
    break;

  case 22: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 129 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1444 "src/parser.cpp"
    break;

  case 23: /* WhileStmt: WHILE LPAREN Cond RPAREN Stmt  */
#line 134 "src/parser.y"
                                   {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1452 "src/parser.cpp"
    break;

  case 24: /* ContinueStmt: CONTINUE SEMICOLON  */
#line 139 "src/parser.y"
                        {
        (yyval.stmttype) = new ContinueStmt();
    }
#line 1460 "src/parser.cpp"
    break;

  case 25: /* BreakStmt: BREAK SEMICOLON  */
#line 144 "src/parser.y"
                     {
        (yyval.stmttype) = new BreakStmt();
    }
#line 1468 "src/parser.cpp"
    break;

  case 26: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 150 "src/parser.y"
                        {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1476 "src/parser.cpp"
    break;

  case 27: /* ExpStmt: Exps SEMICOLON  */
#line 156 "src/parser.y"
                      {(yyval.stmttype) = (yyvsp[-1].stmttype);}
#line 1482 "src/parser.cpp"
    break;

  case 28: /* Exps: ExpStmt PARSE Exp  */
#line 160 "src/parser.y"
                         {
            ExprStmtNode* node = (ExprStmtNode*)(yyvsp[-2].stmttype);
            node->append((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1492 "src/parser.cpp"
    break;

  case 29: /* Exps: Exp  */
#line 165 "src/parser.y"
            {
            ExprStmtNode* node = new ExprStmtNode();
            node->append((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1502 "src/parser.cpp"
    break;

  case 30: /* Exp: AddExp  */
#line 174 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1508 "src/parser.cpp"
    break;

  case 31: /* Cond: LOrExp  */
#line 184 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1514 "src/parser.cpp"
    break;

  case 32: /* FuncRealParams: FuncRealParams PARSE Exp  */
#line 189 "src/parser.y"
                            {
        FuncCallParamsNode* node = (FuncCallParamsNode*) (yyvsp[-2].stmttype);
        node->append((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 1524 "src/parser.cpp"
    break;

  case 33: /* FuncRealParams: Exp  */
#line 195 "src/parser.y"
       {
        FuncCallParamsNode* node = new FuncCallParamsNode();
        node->append((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 1534 "src/parser.cpp"
    break;

  case 34: /* FuncRealParams: %empty  */
#line 201 "src/parser.y"
          {
        (yyval.stmttype) = nullptr;
    }
#line 1542 "src/parser.cpp"
    break;

  case 35: /* PrimaryExp: LVal  */
#line 208 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1550 "src/parser.cpp"
    break;

  case 36: /* PrimaryExp: INTEGER  */
#line 211 "src/parser.y"
              {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].iType));
        (yyval.exprtype) = new Constant(se);
    }
#line 1559 "src/parser.cpp"
    break;

  case 37: /* PrimaryExp: FLOATNUM  */
#line 215 "src/parser.y"
               {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType,(yyvsp[0].fType));
        (yyval.exprtype) = new Constant(se);
    }
#line 1568 "src/parser.cpp"
    break;

  case 38: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 219 "src/parser.y"
                       {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1576 "src/parser.cpp"
    break;

  case 39: /* UnaryExp: PrimaryExp  */
#line 226 "src/parser.y"
              {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1582 "src/parser.cpp"
    break;

  case 40: /* UnaryExp: ADD UnaryExp  */
#line 228 "src/parser.y"
                {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1590 "src/parser.cpp"
    break;

  case 41: /* UnaryExp: SUB UnaryExp  */
#line 232 "src/parser.y"
                {
        SymbolEntry *se = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryOpExpr(se, UnaryOpExpr::SUB, (yyvsp[0].exprtype));
    }
#line 1599 "src/parser.cpp"
    break;

  case 42: /* UnaryExp: NOT UnaryExp  */
#line 237 "src/parser.y"
                {
         SymbolEntry *se = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
         (yyval.exprtype) = new UnaryOpExpr(se, UnaryOpExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1608 "src/parser.cpp"
    break;

  case 43: /* UnaryExp: ID LPAREN FuncRealParams RPAREN  */
#line 242 "src/parser.y"
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
#line 1625 "src/parser.cpp"
    break;

  case 44: /* MulExp: UnaryExp  */
#line 261 "src/parser.y"
            {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1631 "src/parser.cpp"
    break;

  case 45: /* MulExp: MulExp MUL UnaryExp  */
#line 263 "src/parser.y"
                        {
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getType()->isInt() && (yyvsp[0].exprtype)->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1646 "src/parser.cpp"
    break;

  case 46: /* MulExp: MulExp DIV UnaryExp  */
#line 274 "src/parser.y"
                        {
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getType()->isInt() && (yyvsp[0].exprtype)->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1661 "src/parser.cpp"
    break;

  case 47: /* MulExp: MulExp MOD UnaryExp  */
#line 285 "src/parser.y"
                        {
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getType()->isInt() && (yyvsp[0].exprtype)->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1676 "src/parser.cpp"
    break;

  case 48: /* AddExp: MulExp  */
#line 300 "src/parser.y"
          {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1682 "src/parser.cpp"
    break;

  case 49: /* AddExp: AddExp ADD MulExp  */
#line 303 "src/parser.y"
    {
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getType()->isInt() && (yyvsp[0].exprtype)->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1697 "src/parser.cpp"
    break;

  case 50: /* AddExp: AddExp SUB MulExp  */
#line 315 "src/parser.y"
    {
        SymbolEntry *se;
        if((yyvsp[-2].exprtype)->getType()->isInt() && (yyvsp[0].exprtype)->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1712 "src/parser.cpp"
    break;

  case 51: /* RelExp: AddExp  */
#line 329 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1718 "src/parser.cpp"
    break;

  case 52: /* RelExp: RelExp LESS AddExp  */
#line 332 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1727 "src/parser.cpp"
    break;

  case 53: /* RelExp: RelExp GREATER AddExp  */
#line 338 "src/parser.y"
    {
        printf("greater!\n");
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATER, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1737 "src/parser.cpp"
    break;

  case 54: /* RelExp: RelExp LE AddExp  */
#line 345 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LE, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1746 "src/parser.cpp"
    break;

  case 55: /* RelExp: RelExp GE AddExp  */
#line 351 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GE, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1755 "src/parser.cpp"
    break;

  case 56: /* EqExp: RelExp  */
#line 359 "src/parser.y"
          {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1761 "src/parser.cpp"
    break;

  case 57: /* EqExp: EqExp EQ RelExp  */
#line 361 "src/parser.y"
                   {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1770 "src/parser.cpp"
    break;

  case 58: /* EqExp: EqExp NEQ RelExp  */
#line 366 "src/parser.y"
                    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1779 "src/parser.cpp"
    break;

  case 59: /* LAndExp: EqExp  */
#line 374 "src/parser.y"
          {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1785 "src/parser.cpp"
    break;

  case 60: /* LAndExp: LAndExp AND EqExp  */
#line 377 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1794 "src/parser.cpp"
    break;

  case 61: /* LOrExp: LAndExp  */
#line 384 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1800 "src/parser.cpp"
    break;

  case 62: /* LOrExp: LOrExp OR LAndExp  */
#line 387 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1809 "src/parser.cpp"
    break;

  case 63: /* Type: INT  */
#line 393 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
        currentType = TypeSystem::intType;
    }
#line 1818 "src/parser.cpp"
    break;

  case 64: /* Type: VOID  */
#line 397 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
        currentType = TypeSystem::voidType;
    }
#line 1827 "src/parser.cpp"
    break;

  case 65: /* Type: FLOAT  */
#line 401 "src/parser.y"
            {
        (yyval.type) = TypeSystem::floatType;
        currentType = TypeSystem::floatType;
    }
#line 1836 "src/parser.cpp"
    break;

  case 66: /* DeclStmt: CONST Type ConstDefList SEMICOLON  */
#line 407 "src/parser.y"
                                       { // const声明
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1844 "src/parser.cpp"
    break;

  case 67: /* DeclStmt: Type VarDefList SEMICOLON  */
#line 411 "src/parser.y"
                                { 
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1852 "src/parser.cpp"
    break;

  case 68: /* ArrIndices: ArrIndices LBRACKET Exp RBRACKET  */
#line 418 "src/parser.y"
                                         {
            ArrayindiceNode* node = (ArrayindiceNode*)(yyvsp[-3].stmttype);
            node->append((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;          
        }
#line 1862 "src/parser.cpp"
    break;

  case 69: /* ArrIndices: LBRACKET Exp RBRACKET  */
#line 423 "src/parser.y"
                              {
            ArrayindiceNode* node = new ArrayindiceNode();
            node->append((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;
        }
#line 1872 "src/parser.cpp"
    break;

  case 70: /* ConstDefList: ConstDefList PARSE ConstDef  */
#line 431 "src/parser.y"
                                 {
            DeclStmt* node = (DeclStmt*) (yyvsp[-2].stmttype);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
    }
#line 1882 "src/parser.cpp"
    break;

  case 71: /* ConstDefList: ConstDef  */
#line 436 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(true);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node; 
    }
#line 1892 "src/parser.cpp"
    break;

  case 72: /* ConstDef: ID ASSIGN Exp  */
#line 443 "src/parser.y"
                    {
        // const 必须赋初值
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
#line 1911 "src/parser.cpp"
    break;

  case 73: /* ConstDef: ID ArrIndices ASSIGN ConstArrayInitVal  */
#line 458 "src/parser.y"
                                                  {
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices((ArrayindiceNode*)(yyvsp[-2].stmttype));
            (yyval.stmttype) = new DefNode(id, (Node*)(yyvsp[0].stmttype), true, true);
        }
#line 1931 "src/parser.cpp"
    break;

  case 74: /* ConstArrayInitVal: Exp  */
#line 475 "src/parser.y"
            {
            ArrayinitNode* node = new ArrayinitNode(true);
            node->setLeafNode((ExprNode*)(yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1941 "src/parser.cpp"
    break;

  case 75: /* ConstArrayInitVal: LBRACE ConstArrayInitValList RBRACE  */
#line 480 "src/parser.y"
                                           {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 1949 "src/parser.cpp"
    break;

  case 76: /* ConstArrayInitVal: LBRACE RBRACE  */
#line 483 "src/parser.y"
                     {
            (yyval.stmttype) = new ArrayinitNode(true);
    }
#line 1957 "src/parser.cpp"
    break;

  case 77: /* ConstArrayInitValList: ConstArrayInitValList PARSE ConstArrayInitVal  */
#line 489 "src/parser.y"
                                                     {
            ArrayinitNode* node = (ArrayinitNode*)(yyvsp[-2].stmttype);
            node->append((ArrayinitNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 1967 "src/parser.cpp"
    break;

  case 78: /* ConstArrayInitValList: ConstArrayInitVal  */
#line 494 "src/parser.y"
                         {
            ArrayinitNode* newNode = new ArrayinitNode(true);
            newNode->append((ArrayinitNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = newNode;
        }
#line 1977 "src/parser.cpp"
    break;

  case 79: /* ArrayInitVal: Exp  */
#line 502 "src/parser.y"
            {
            ArrayinitNode* node = new ArrayinitNode(false);
            node->setLeafNode((ExprNode*)(yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1987 "src/parser.cpp"
    break;

  case 80: /* ArrayInitVal: LBRACE ArrayInitValList RBRACE  */
#line 507 "src/parser.y"
                                      {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 1995 "src/parser.cpp"
    break;

  case 81: /* ArrayInitVal: LBRACE RBRACE  */
#line 510 "src/parser.y"
                     {
            (yyval.stmttype) = new ArrayinitNode(false);
    }
#line 2003 "src/parser.cpp"
    break;

  case 82: /* ArrayInitValList: ArrayInitValList PARSE ArrayInitVal  */
#line 516 "src/parser.y"
                                           {
            ArrayinitNode* node = (ArrayinitNode*)(yyvsp[-2].stmttype);
            node->append((ArrayinitNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 2013 "src/parser.cpp"
    break;

  case 83: /* ArrayInitValList: ArrayInitVal  */
#line 521 "src/parser.y"
                    {
            ArrayinitNode* newNode = new ArrayinitNode(false);
            newNode->append((ArrayinitNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = newNode;
        }
#line 2023 "src/parser.cpp"
    break;

  case 84: /* VarDefList: VarDefList PARSE VarDef  */
#line 529 "src/parser.y"
                                {
            DeclStmt* node = (DeclStmt*) (yyvsp[-2].stmttype);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 2033 "src/parser.cpp"
    break;

  case 85: /* VarDefList: VarDef  */
#line 534 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(false);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 2043 "src/parser.cpp"
    break;

  case 86: /* VarDef: ID  */
#line 541 "src/parser.y"
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
#line 2061 "src/parser.cpp"
    break;

  case 87: /* VarDef: ID ASSIGN Exp  */
#line 554 "src/parser.y"
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
#line 2079 "src/parser.cpp"
    break;

  case 88: /* VarDef: ID ArrIndices  */
#line 567 "src/parser.y"
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
#line 2099 "src/parser.cpp"
    break;

  case 89: /* VarDef: ID ArrIndices ASSIGN ArrayInitVal  */
#line 582 "src/parser.y"
                                         {
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices((ArrayindiceNode*)(yyvsp[-2].stmttype));
            (yyval.stmttype) = new DefNode(id, (Node*)(yyvsp[0].stmttype), false, true);
        }
#line 2119 "src/parser.cpp"
    break;

  case 90: /* $@2: %empty  */
#line 599 "src/parser.y"
            {
        // 返回值类型是ID的type，函数定义中需要创建新的符号表
        Type *funcType;
        funcType = new FunctionType((yyvsp[-1].type),{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        identifiers = new SymbolTable(identifiers);
    }
#line 2132 "src/parser.cpp"
    break;

  case 91: /* $@3: %empty  */
#line 607 "src/parser.y"
                     {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-3].strtype));
            assert(se != nullptr);
            if((yyvsp[0].stmttype)!=nullptr){
                ((FunctionType*)(se->getType()))/*强转为Function Type*/->setparamsType/*设置参数类型*/(((FuncDefParamsNode*)(yyvsp[0].stmttype))->getParamsType());
            }   
        }
#line 2145 "src/parser.cpp"
    break;

  case 92: /* FuncDef: Type ID $@2 LPAREN FuncParams $@3 RPAREN BlockStmt  */
#line 617 "src/parser.y"
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
#line 2160 "src/parser.cpp"
    break;

  case 93: /* FuncParams: FuncParams PARSE FuncParam  */
#line 630 "src/parser.y"
                                   {
            FuncDefParamsNode* node = (FuncDefParamsNode*)(yyvsp[-2].stmttype);
            node->addNext(((DefNode*)(yyvsp[0].stmttype))->getId());
            (yyval.stmttype) = node;
        }
#line 2170 "src/parser.cpp"
    break;

  case 94: /* FuncParams: FuncParam  */
#line 635 "src/parser.y"
                  {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext(((DefNode*)(yyvsp[0].stmttype))->getId());
            (yyval.stmttype) = node;
        }
#line 2180 "src/parser.cpp"
    break;

  case 95: /* FuncParams: %empty  */
#line 640 "src/parser.y"
               {
            (yyval.stmttype) = nullptr;
        }
#line 2188 "src/parser.cpp"
    break;

  case 96: /* FuncParam: Type ID  */
#line 647 "src/parser.y"
                {
            SymbolEntry *se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 2198 "src/parser.cpp"
    break;

  case 97: /* FuncParam: Type ID LBRACKET RBRACKET ArrIndices  */
#line 652 "src/parser.y"
                                          {
            Type* arrayType = nullptr; 
            if((yyvsp[-4].type)==TypeSystem::intType){
                arrayType = new IntArrayType();
                ((IntArrayType*)arrayType)->pushBackDimension(-1);
            }
            else if((yyvsp[-4].type)==TypeSystem::floatType){
                arrayType = new FloatArrayType();
                ((FloatArrayType*)arrayType)->pushBackDimension(-1);
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices((ArrayindiceNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2220 "src/parser.cpp"
    break;

  case 98: /* FuncParam: Type ID LBRACKET RBRACKET  */
#line 669 "src/parser.y"
                                 {
            Type* arrayType = nullptr; 
            if((yyvsp[-3].type)==TypeSystem::intType){
                arrayType = new IntArrayType();
                ((IntArrayType*)arrayType)->pushBackDimension(-1);
            }
            else if((yyvsp[-3].type)==TypeSystem::floatType){
                arrayType = new FloatArrayType();
                ((FloatArrayType*)arrayType)->pushBackDimension(-1);
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            Id* id = new Id(se);
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2241 "src/parser.cpp"
    break;


#line 2245 "src/parser.cpp"

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

#line 688 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
