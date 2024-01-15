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
  YYSYMBOL_ConstExp = 56,                  /* ConstExp  */
  YYSYMBOL_Cond = 57,                      /* Cond  */
  YYSYMBOL_FuncRealParams = 58,            /* FuncRealParams  */
  YYSYMBOL_PrimaryExp = 59,                /* PrimaryExp  */
  YYSYMBOL_UnaryExp = 60,                  /* UnaryExp  */
  YYSYMBOL_MulExp = 61,                    /* MulExp  */
  YYSYMBOL_AddExp = 62,                    /* AddExp  */
  YYSYMBOL_RelExp = 63,                    /* RelExp  */
  YYSYMBOL_EqExp = 64,                     /* EqExp  */
  YYSYMBOL_LAndExp = 65,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 66,                    /* LOrExp  */
  YYSYMBOL_Type = 67,                      /* Type  */
  YYSYMBOL_DeclStmt = 68,                  /* DeclStmt  */
  YYSYMBOL_ArrIndices = 69,                /* ArrIndices  */
  YYSYMBOL_ConstDefList = 70,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 71,                  /* ConstDef  */
  YYSYMBOL_ConstArrayInitVal = 72,         /* ConstArrayInitVal  */
  YYSYMBOL_ConstArrayInitValList = 73,     /* ConstArrayInitValList  */
  YYSYMBOL_ArrayInitVal = 74,              /* ArrayInitVal  */
  YYSYMBOL_ArrayInitValList = 75,          /* ArrayInitValList  */
  YYSYMBOL_VarDefList = 76,                /* VarDefList  */
  YYSYMBOL_VarDef = 77,                    /* VarDef  */
  YYSYMBOL_FuncDef = 78,                   /* FuncDef  */
  YYSYMBOL_79_2 = 79,                      /* $@2  */
  YYSYMBOL_80_3 = 80,                      /* $@3  */
  YYSYMBOL_FuncParams = 81,                /* FuncParams  */
  YYSYMBOL_FuncParam = 82                  /* FuncParam  */
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
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   249

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

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
       0,    51,    51,    57,    62,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    82,    98,   115,   121,
     120,   131,   136,   139,   144,   149,   154,   160,   163,   169,
     173,   178,   187,   192,   197,   202,   208,   214,   221,   224,
     228,   232,   239,   241,   245,   250,   255,   274,   276,   287,
     298,   313,   315,   327,   342,   344,   350,   357,   363,   372,
     374,   379,   387,   389,   397,   399,   406,   410,   414,   420,
     424,   431,   437,   446,   451,   458,   483,   508,   513,   516,
     522,   527,   535,   540,   543,   549,   554,   562,   567,   574,
     593,   612,   633,   656,   664,   656,   689,   694,   699,   706,
     711,   729
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
  "ConstExp", "Cond", "FuncRealParams", "PrimaryExp", "UnaryExp", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "Type", "DeclStmt",
  "ArrIndices", "ConstDefList", "ConstDef", "ConstArrayInitVal",
  "ConstArrayInitValList", "ArrayInitVal", "ArrayInitValList",
  "VarDefList", "VarDef", "FuncDef", "$@2", "$@3", "FuncParams",
  "FuncParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-94)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     135,     4,  -125,  -125,    -3,    14,  -125,  -125,  -125,   116,
      32,  -125,   116,   116,   116,    94,   177,    48,    57,    53,
     135,  -125,    40,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
      71,    76,  -125,  -125,  -125,   136,    -2,    92,  -125,  -125,
     116,   116,    91,   116,   116,  -125,   101,  -125,   135,  -125,
    -125,  -125,   126,  -125,   138,  -125,  -125,  -125,  -125,   116,
     116,  -125,   116,   116,   116,   116,   116,    37,     8,  -125,
    -125,     1,   134,    -2,   116,   144,    -2,    95,    66,   137,
     139,   148,  -125,    25,    -6,    75,  -125,  -125,   146,  -125,
    -125,  -125,  -125,   136,   136,   116,    27,   153,  -125,   163,
    -125,   116,  -125,   150,   135,   116,   116,   116,   116,   116,
     116,   116,   116,   135,  -125,   116,    55,  -125,   126,  -125,
    -125,   196,    94,    65,  -125,  -125,  -125,   170,    -2,    -2,
      -2,    -2,    95,    95,    66,   137,  -125,  -125,   215,  -125,
      97,  -125,  -125,   175,   160,  -125,   135,   171,  -125,  -125,
    -125,  -125,    50,   167,    94,   174,  -125,  -125,  -125,    51,
    -125,   196,   172,  -125,   180,  -125,   215,  -125,   178,  -125,
    -125,    91
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    39,    40,     0,     0,    66,    67,    68,     0,
      19,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     4,    38,     5,     6,     7,     8,    13,    12,     9,
      15,     0,    31,    42,    47,    51,    32,     0,    10,    11,
      37,     0,    17,     0,     0,    38,     0,    21,     0,    43,
      44,    45,     0,    28,     0,    25,    26,     1,     3,     0,
       0,    29,     0,     0,     0,     0,     0,    89,     0,    88,
      36,     0,     0,    33,     0,     0,    54,    59,    62,    64,
      34,     0,    41,     0,     0,     0,    74,    27,     0,    30,
      48,    49,    50,    52,    53,     0,    91,     0,    70,     0,
      46,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,    69,     0,    18,
      90,     0,    98,    89,    87,    35,    71,    22,    55,    57,
      56,    58,    60,    61,    63,    65,    24,    75,     0,    73,
       0,    82,    92,     0,    94,    97,     0,     0,    77,    76,
      84,    86,     0,    99,     0,     0,    23,    79,    81,     0,
      83,     0,     0,    96,     0,    78,     0,    85,   101,    95,
      80,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,   140,   -16,     2,  -125,    38,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,    -8,   -26,   152,  -125,  -125,
      -7,    61,   -31,    24,    93,   100,  -125,   -12,  -125,    -1,
    -125,    85,  -124,  -125,  -123,  -125,  -125,   107,  -125,  -125,
    -125,  -125,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    45,    23,    24,    48,    25,    26,
      27,    28,    29,    30,    31,    32,   148,    75,    71,    33,
      34,    35,    36,    77,    78,    79,    80,    37,    38,    96,
      85,    86,   149,   159,   142,   152,    68,    69,    39,    97,
     155,   144,   145
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    46,    22,    52,    58,    49,    50,    51,    54,    43,
      73,    41,    76,    76,   100,    72,    40,   151,    65,    66,
     101,    41,    22,   158,    98,   115,    44,    99,     1,     2,
       3,     4,    70,     5,     6,     7,     8,     9,   167,    10,
     114,    11,   170,    73,    74,    12,    13,    47,   103,   -93,
      22,    88,    89,    57,    41,    90,    91,    92,   121,    14,
      15,    16,    17,    18,    55,   160,   165,    58,    95,   161,
     166,    59,    74,    56,   128,   129,   130,   131,    76,    76,
      76,    76,    41,   116,    73,    22,   138,   120,   127,   137,
      60,   117,    61,   125,   118,    67,    95,   136,   109,   110,
       1,     2,     3,     6,     7,     8,    22,    73,    74,     9,
     143,   140,   150,   141,    82,    22,    73,    12,    13,     1,
       2,     3,   105,   106,   107,   108,    93,    94,     9,    84,
     156,    14,   141,   132,   133,    73,    12,    13,     1,     2,
       3,     4,   143,     5,     6,     7,     8,     9,    22,    10,
      14,    11,   102,   141,    87,    12,    13,   104,    62,    63,
      64,   113,   119,   111,   112,   122,   123,   171,   126,    14,
      15,    16,    17,    18,     1,     2,     3,   146,   153,   154,
       1,     2,     3,     9,   162,   147,   157,   164,    83,     9,
     168,    12,    13,    53,    10,    41,    81,    12,    13,     1,
       2,     3,   169,   139,   134,    14,   124,     0,     9,     0,
     140,    14,   135,   163,     0,     0,    12,    13,     1,     2,
       3,     0,     0,     0,     0,     0,     0,     9,     0,   147,
      14,     0,     0,     0,     0,    12,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14
};

static const yytype_int16 yycheck[] =
{
       1,     9,     0,    15,    20,    12,    13,    14,    16,    12,
      41,    17,    43,    44,    13,    41,    12,   140,    20,    21,
      19,    17,    20,   147,    16,    31,    12,    19,     3,     4,
       5,     6,    40,     8,     9,    10,    11,    12,   161,    14,
      15,    16,   166,    74,    17,    20,    21,    15,    74,    12,
      48,    59,    60,     0,    17,    62,    63,    64,    31,    34,
      35,    36,    37,    38,    16,    15,    15,    83,    31,    19,
      19,    31,    17,    16,   105,   106,   107,   108,   109,   110,
     111,   112,    17,    84,   115,    83,    31,    95,   104,   115,
      19,    16,    16,   101,    19,     3,    31,   113,    32,    33,
       3,     4,     5,     9,    10,    11,   104,   138,    17,    12,
     122,    14,    15,   121,    13,   113,   147,    20,    21,     3,
       4,     5,    27,    28,    29,    30,    65,    66,    12,     3,
     146,    34,   140,   109,   110,   166,    20,    21,     3,     4,
       5,     6,   154,     8,     9,    10,    11,    12,   146,    14,
      34,    16,    18,   161,    16,    20,    21,    13,    22,    23,
      24,    13,    16,    26,    25,    12,     3,   168,    18,    34,
      35,    36,    37,    38,     3,     4,     5,     7,     3,    19,
       3,     4,     5,    12,    17,    14,    15,    13,    48,    12,
      18,    20,    21,    16,    14,    17,    44,    20,    21,     3,
       4,     5,   164,   118,   111,    34,    99,    -1,    12,    -1,
      14,    34,   112,   154,    -1,    -1,    20,    21,     3,     4,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    14,
      34,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      14,    16,    20,    21,    34,    35,    36,    37,    38,    41,
      42,    43,    44,    45,    46,    48,    49,    50,    51,    52,
      53,    54,    55,    59,    60,    61,    62,    67,    68,    78,
      12,    17,    69,    12,    12,    44,    55,    15,    47,    60,
      60,    60,    67,    16,    55,    16,    16,     0,    43,    31,
      19,    16,    22,    23,    24,    20,    21,     3,    76,    77,
      55,    58,    56,    62,    17,    57,    62,    63,    64,    65,
      66,    57,    13,    42,     3,    70,    71,    16,    55,    55,
      60,    60,    60,    61,    61,    31,    69,    79,    16,    19,
      13,    19,    18,    56,    13,    27,    28,    29,    30,    32,
      33,    26,    25,    13,    15,    31,    69,    16,    19,    16,
      55,    31,    12,     3,    77,    55,    18,    43,    62,    62,
      62,    62,    63,    63,    64,    65,    43,    56,    31,    71,
      14,    55,    74,    67,    81,    82,     7,    14,    56,    72,
      15,    74,    75,     3,    19,    80,    43,    15,    72,    73,
      15,    19,    17,    82,    13,    15,    19,    74,    18,    46,
      72,    69
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    45,    47,
      46,    46,    48,    48,    49,    50,    51,    52,    52,    53,
      54,    54,    55,    56,    57,    58,    58,    58,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    61,    61,    61,
      61,    62,    62,    62,    63,    63,    63,    63,    63,    64,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    77,    79,    80,    78,    81,    81,    81,    82,
      82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     0,
       4,     2,     5,     7,     5,     2,     2,     3,     2,     2,
       3,     1,     1,     1,     1,     3,     1,     0,     1,     1,
       1,     3,     1,     2,     2,     2,     4,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     1,     1,     4,
       3,     4,     3,     3,     1,     3,     4,     1,     3,     2,
       3,     1,     1,     3,     2,     3,     1,     3,     1,     1,
       3,     2,     4,     0,     0,     8,     3,     1,     0,     2,
       5,     4
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
#line 1292 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmts Stmt  */
#line 57 "src/parser.y"
                  {
            SeqNode* node = dynamic_cast<SeqNode*>((yyvsp[-1].stmttype));
            node->addNext(dynamic_cast<StmtNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = dynamic_cast<StmtNode*>(node);
        }
#line 1302 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmt  */
#line 62 "src/parser.y"
            {
            SeqNode* node = new SeqNode();
            node->addNext(dynamic_cast<StmtNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = dynamic_cast<StmtNode*>(node);
        }
#line 1312 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 69 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1318 "src/parser.cpp"
    break;

  case 6: /* Stmt: BlockStmt  */
#line 70 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1324 "src/parser.cpp"
    break;

  case 7: /* Stmt: IfStmt  */
#line 71 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1330 "src/parser.cpp"
    break;

  case 8: /* Stmt: WhileStmt  */
#line 72 "src/parser.y"
               {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1336 "src/parser.cpp"
    break;

  case 9: /* Stmt: ReturnStmt  */
#line 73 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1342 "src/parser.cpp"
    break;

  case 10: /* Stmt: DeclStmt  */
#line 74 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1348 "src/parser.cpp"
    break;

  case 11: /* Stmt: FuncDef  */
#line 75 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1354 "src/parser.cpp"
    break;

  case 12: /* Stmt: BreakStmt  */
#line 76 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1360 "src/parser.cpp"
    break;

  case 13: /* Stmt: ContinueStmt  */
#line 77 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1366 "src/parser.cpp"
    break;

  case 14: /* Stmt: SEMICOLON  */
#line 78 "src/parser.y"
               {(yyval.stmttype) = new EmptyStmt() ;}
#line 1372 "src/parser.cpp"
    break;

  case 15: /* Stmt: ExpStmt  */
#line 79 "src/parser.y"
             {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1378 "src/parser.cpp"
    break;

  case 16: /* LVal: ID  */
#line 82 "src/parser.y"
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
        
         // std::cout<<$$->getType()->toStr();
         // std::cout<<"test"<<std::endl;
        delete [](yyvsp[0].strtype);
    }
#line 1398 "src/parser.cpp"
    break;

  case 17: /* LVal: ID ArrIndices  */
#line 98 "src/parser.y"
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
        newId->addIndices((ExprStmtNode*)(yyvsp[0].stmttype));
        (yyval.exprtype) =  newId;
        delete [](yyvsp[-1].strtype);
    }
#line 1417 "src/parser.cpp"
    break;

  case 18: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 115 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1425 "src/parser.cpp"
    break;

  case 19: /* $@1: %empty  */
#line 121 "src/parser.y"
        {
            identifiers = new SymbolTable(identifiers);
        }
#line 1433 "src/parser.cpp"
    break;

  case 20: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 125 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1444 "src/parser.cpp"
    break;

  case 21: /* BlockStmt: LBRACE RBRACE  */
#line 131 "src/parser.y"
                          {
            (yyval.stmttype) = new CompoundStmt(nullptr);
        }
#line 1452 "src/parser.cpp"
    break;

  case 22: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 136 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1460 "src/parser.cpp"
    break;

  case 23: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 139 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1468 "src/parser.cpp"
    break;

  case 24: /* WhileStmt: WHILE LPAREN Cond RPAREN Stmt  */
#line 144 "src/parser.y"
                                   {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1476 "src/parser.cpp"
    break;

  case 25: /* ContinueStmt: CONTINUE SEMICOLON  */
#line 149 "src/parser.y"
                        {
        (yyval.stmttype) = new ContinueStmt();
    }
#line 1484 "src/parser.cpp"
    break;

  case 26: /* BreakStmt: BREAK SEMICOLON  */
#line 154 "src/parser.y"
                     {
        (yyval.stmttype) = new BreakStmt();
    }
#line 1492 "src/parser.cpp"
    break;

  case 27: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 160 "src/parser.y"
                        {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1500 "src/parser.cpp"
    break;

  case 28: /* ReturnStmt: RETURN SEMICOLON  */
#line 163 "src/parser.y"
                         {
         (yyval.stmttype) = new ReturnStmt(nullptr);
    }
#line 1508 "src/parser.cpp"
    break;

  case 29: /* ExpStmt: Exps SEMICOLON  */
#line 169 "src/parser.y"
                      {(yyval.stmttype) = (yyvsp[-1].stmttype);}
#line 1514 "src/parser.cpp"
    break;

  case 30: /* Exps: ExpStmt PARSE Exp  */
#line 173 "src/parser.y"
                         {
            ExprStmtNode* node = (ExprStmtNode*)(yyvsp[-2].stmttype);
            node->addNext((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1524 "src/parser.cpp"
    break;

  case 31: /* Exps: Exp  */
#line 178 "src/parser.y"
            {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1534 "src/parser.cpp"
    break;

  case 32: /* Exp: AddExp  */
#line 187 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1540 "src/parser.cpp"
    break;

  case 33: /* ConstExp: AddExp  */
#line 192 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1546 "src/parser.cpp"
    break;

  case 34: /* Cond: LOrExp  */
#line 197 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1552 "src/parser.cpp"
    break;

  case 35: /* FuncRealParams: FuncRealParams PARSE Exp  */
#line 202 "src/parser.y"
                            {
        FuncCallParamsNode* node = (FuncCallParamsNode*) (yyvsp[-2].stmttype);
        node->addNext((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 1562 "src/parser.cpp"
    break;

  case 36: /* FuncRealParams: Exp  */
#line 208 "src/parser.y"
       {
        FuncCallParamsNode* node = new FuncCallParamsNode();
        node->addNext((yyvsp[0].exprtype));
        (yyval.stmttype) = node;
    }
#line 1572 "src/parser.cpp"
    break;

  case 37: /* FuncRealParams: %empty  */
#line 214 "src/parser.y"
          {
        (yyval.stmttype) = nullptr;
    }
#line 1580 "src/parser.cpp"
    break;

  case 38: /* PrimaryExp: LVal  */
#line 221 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1588 "src/parser.cpp"
    break;

  case 39: /* PrimaryExp: INTEGER  */
#line 224 "src/parser.y"
              {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, (yyvsp[0].iType));
        (yyval.exprtype) = new Constant(se);
    }
#line 1597 "src/parser.cpp"
    break;

  case 40: /* PrimaryExp: FLOATNUM  */
#line 228 "src/parser.y"
               {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType,(yyvsp[0].fType));
        (yyval.exprtype) = new Constant(se);
    }
#line 1606 "src/parser.cpp"
    break;

  case 41: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 232 "src/parser.y"
                       {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1614 "src/parser.cpp"
    break;

  case 42: /* UnaryExp: PrimaryExp  */
#line 239 "src/parser.y"
              {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1620 "src/parser.cpp"
    break;

  case 43: /* UnaryExp: ADD UnaryExp  */
#line 241 "src/parser.y"
                {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1628 "src/parser.cpp"
    break;

  case 44: /* UnaryExp: SUB UnaryExp  */
#line 245 "src/parser.y"
                {
        SymbolEntry *se = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
        (yyval.exprtype) = new OneOpExpr(se, OneOpExpr::SUB, (yyvsp[0].exprtype));
    }
#line 1637 "src/parser.cpp"
    break;

  case 45: /* UnaryExp: NOT UnaryExp  */
#line 250 "src/parser.y"
                {
         SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
         (yyval.exprtype) = new OneOpExpr(se, OneOpExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1646 "src/parser.cpp"
    break;

  case 46: /* UnaryExp: ID LPAREN FuncRealParams RPAREN  */
#line 255 "src/parser.y"
                                   { // 函数调用
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-3].strtype));
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(dynamic_cast<FunctionType*>(se->getType())->getRetType(), SymbolTable::getLabel());
        (yyval.exprtype) = new FuncCallNode(tmp, new Id(se), dynamic_cast<FuncCallParamsNode*>((yyvsp[-1].stmttype)));
    }
#line 1663 "src/parser.cpp"
    break;

  case 47: /* MulExp: UnaryExp  */
#line 274 "src/parser.y"
            {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1669 "src/parser.cpp"
    break;

  case 48: /* MulExp: MulExp MUL UnaryExp  */
#line 276 "src/parser.y"
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
#line 1684 "src/parser.cpp"
    break;

  case 49: /* MulExp: MulExp DIV UnaryExp  */
#line 287 "src/parser.y"
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
#line 1699 "src/parser.cpp"
    break;

  case 50: /* MulExp: MulExp MOD UnaryExp  */
#line 298 "src/parser.y"
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
#line 1714 "src/parser.cpp"
    break;

  case 51: /* AddExp: MulExp  */
#line 313 "src/parser.y"
          {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1720 "src/parser.cpp"
    break;

  case 52: /* AddExp: AddExp ADD MulExp  */
#line 316 "src/parser.y"
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
#line 1735 "src/parser.cpp"
    break;

  case 53: /* AddExp: AddExp SUB MulExp  */
#line 328 "src/parser.y"
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
#line 1750 "src/parser.cpp"
    break;

  case 54: /* RelExp: AddExp  */
#line 342 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1756 "src/parser.cpp"
    break;

  case 55: /* RelExp: RelExp LESS AddExp  */
#line 345 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1765 "src/parser.cpp"
    break;

  case 56: /* RelExp: RelExp GREATER AddExp  */
#line 351 "src/parser.y"
    {
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREAT, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1775 "src/parser.cpp"
    break;

  case 57: /* RelExp: RelExp LE AddExp  */
#line 358 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1784 "src/parser.cpp"
    break;

  case 58: /* RelExp: RelExp GE AddExp  */
#line 364 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1793 "src/parser.cpp"
    break;

  case 59: /* EqExp: RelExp  */
#line 372 "src/parser.y"
          {(yyval.exprtype)=(yyvsp[0].exprtype);}
#line 1799 "src/parser.cpp"
    break;

  case 60: /* EqExp: EqExp EQ RelExp  */
#line 374 "src/parser.y"
                   {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1808 "src/parser.cpp"
    break;

  case 61: /* EqExp: EqExp NEQ RelExp  */
#line 379 "src/parser.y"
                    {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1817 "src/parser.cpp"
    break;

  case 62: /* LAndExp: EqExp  */
#line 387 "src/parser.y"
          {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1823 "src/parser.cpp"
    break;

  case 63: /* LAndExp: LAndExp AND EqExp  */
#line 390 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1832 "src/parser.cpp"
    break;

  case 64: /* LOrExp: LAndExp  */
#line 397 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1838 "src/parser.cpp"
    break;

  case 65: /* LOrExp: LOrExp OR LAndExp  */
#line 400 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1847 "src/parser.cpp"
    break;

  case 66: /* Type: INT  */
#line 406 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
        currentType = TypeSystem::intType;
    }
#line 1856 "src/parser.cpp"
    break;

  case 67: /* Type: VOID  */
#line 410 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
        currentType = TypeSystem::voidType;
    }
#line 1865 "src/parser.cpp"
    break;

  case 68: /* Type: FLOAT  */
#line 414 "src/parser.y"
            {
        (yyval.type) = TypeSystem::floatType;
        currentType = TypeSystem::floatType;
    }
#line 1874 "src/parser.cpp"
    break;

  case 69: /* DeclStmt: CONST Type ConstDefList SEMICOLON  */
#line 420 "src/parser.y"
                                       { // const声明
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1882 "src/parser.cpp"
    break;

  case 70: /* DeclStmt: Type VarDefList SEMICOLON  */
#line 424 "src/parser.y"
                                { 
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1890 "src/parser.cpp"
    break;

  case 71: /* ArrIndices: ArrIndices LBRACKET ConstExp RBRACKET  */
#line 431 "src/parser.y"
                                              {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>((yyvsp[-3].stmttype));
            node->addNext((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;     
      
        }
#line 1901 "src/parser.cpp"
    break;

  case 72: /* ArrIndices: LBRACKET ConstExp RBRACKET  */
#line 437 "src/parser.y"
                                   {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;

        }
#line 1912 "src/parser.cpp"
    break;

  case 73: /* ConstDefList: ConstDefList PARSE ConstDef  */
#line 446 "src/parser.y"
                                 {
            DeclStmt* node = (DeclStmt*) (yyvsp[-2].stmttype);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
    }
#line 1922 "src/parser.cpp"
    break;

  case 74: /* ConstDefList: ConstDef  */
#line 451 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(true);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node; 
    }
#line 1932 "src/parser.cpp"
    break;

  case 75: /* ConstDef: ID ASSIGN ConstExp  */
#line 458 "src/parser.y"
                         {
        // const 必须赋初值
            // 首先判断是否重定义
            if(identifiers->isRedefine((yyvsp[-2].strtype))) {
                fprintf(stderr, "identifier %s redefine\n", (yyvsp[-2].strtype));
                exit(EXIT_FAILURE);
            }
            // 此处文法有改动
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::constIntType;
            }
            else{
                type = TypeSystem::constFloatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            // 类型向上转换
            (yyval.stmttype) = new DefNode(new Id(se), dynamic_cast<Node*>((yyvsp[0].exprtype)), true, false);
        

        }
#line 1961 "src/parser.cpp"
    break;

  case 76: /* ConstDef: ID ArrIndices ASSIGN ConstArrayInitVal  */
#line 483 "src/parser.y"
                                                  {
            if(identifiers->isRedefine((yyvsp[-3].strtype))) {
                fprintf(stderr, "identifier %s redefine\n", (yyvsp[-3].strtype));
                exit(EXIT_FAILURE);
            }
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = new ConstIntArrayType();
            }
            else{
                type = new ConstFloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>((yyvsp[-2].stmttype)));
            // 类型向上转换
            (yyval.stmttype) = new DefNode(id, dynamic_cast<Node*>((yyvsp[0].stmttype)), true, true);
        

        }
#line 1989 "src/parser.cpp"
    break;

  case 77: /* ConstArrayInitVal: ConstExp  */
#line 508 "src/parser.y"
                 {
            InitValNode* node = new InitValNode(true);
            node->setLeafNode(dynamic_cast<ExprNode*>((yyvsp[0].exprtype)));
            (yyval.stmttype) = node;
        }
#line 1999 "src/parser.cpp"
    break;

  case 78: /* ConstArrayInitVal: LBRACE ConstArrayInitValList RBRACE  */
#line 513 "src/parser.y"
                                           {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 2007 "src/parser.cpp"
    break;

  case 79: /* ConstArrayInitVal: LBRACE RBRACE  */
#line 516 "src/parser.y"
                     {
            (yyval.stmttype) = new InitValNode(true);
    }
#line 2015 "src/parser.cpp"
    break;

  case 80: /* ConstArrayInitValList: ConstArrayInitValList PARSE ConstArrayInitVal  */
#line 522 "src/parser.y"
                                                     {
            InitValNode* node = (InitValNode*)(yyvsp[-2].stmttype);
            node->addNext(dynamic_cast<InitValNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 2025 "src/parser.cpp"
    break;

  case 81: /* ConstArrayInitValList: ConstArrayInitVal  */
#line 527 "src/parser.y"
                         {
            InitValNode* newNode = new InitValNode(true);
            newNode->addNext((InitValNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = newNode;
        }
#line 2035 "src/parser.cpp"
    break;

  case 82: /* ArrayInitVal: Exp  */
#line 535 "src/parser.y"
            {
            InitValNode* node = new InitValNode(false);
            node->setLeafNode((ExprNode*)(yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 2045 "src/parser.cpp"
    break;

  case 83: /* ArrayInitVal: LBRACE ArrayInitValList RBRACE  */
#line 540 "src/parser.y"
                                      {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 2053 "src/parser.cpp"
    break;

  case 84: /* ArrayInitVal: LBRACE RBRACE  */
#line 543 "src/parser.y"
                     {
            (yyval.stmttype) = new InitValNode(false);
    }
#line 2061 "src/parser.cpp"
    break;

  case 85: /* ArrayInitValList: ArrayInitValList PARSE ArrayInitVal  */
#line 549 "src/parser.y"
                                           {
            InitValNode* node = (InitValNode*)(yyvsp[-2].stmttype);
            node->addNext((InitValNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 2071 "src/parser.cpp"
    break;

  case 86: /* ArrayInitValList: ArrayInitVal  */
#line 554 "src/parser.y"
                    {
            InitValNode* newNode = new InitValNode(false);
            newNode->addNext((InitValNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = newNode;
        }
#line 2081 "src/parser.cpp"
    break;

  case 87: /* VarDefList: VarDefList PARSE VarDef  */
#line 562 "src/parser.y"
                                {
            DeclStmt* node = (DeclStmt*) (yyvsp[-2].stmttype);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 2091 "src/parser.cpp"
    break;

  case 88: /* VarDefList: VarDef  */
#line 567 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(false);
            node->addNext((DefNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = node;
        }
#line 2101 "src/parser.cpp"
    break;

  case 89: /* VarDef: ID  */
#line 574 "src/parser.y"
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
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel((yyvsp[0].strtype)) == nullptr){
                identifiers->install((yyvsp[0].strtype), se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)(yyvsp[0].strtype));
                assert(identifiers->lookupOneLevel((yyvsp[0].strtype)) == nullptr);
            }
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 2125 "src/parser.cpp"
    break;

  case 90: /* VarDef: ID ASSIGN Exp  */
#line 593 "src/parser.y"
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
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel((yyvsp[-2].strtype)) == nullptr){
                identifiers->install((yyvsp[-2].strtype), se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)(yyvsp[-2].strtype));
                assert(identifiers->lookupOneLevel((yyvsp[-2].strtype)) == nullptr);
            }
            (yyval.stmttype) = new DefNode(new Id(se), (Node*)(yyvsp[0].exprtype), false, false);
        }
#line 2149 "src/parser.cpp"
    break;

  case 91: /* VarDef: ID ArrIndices  */
#line 612 "src/parser.y"
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
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel((yyvsp[-1].strtype)) == nullptr){
                identifiers->install((yyvsp[-1].strtype), se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)(yyvsp[-1].strtype));
                assert(identifiers->lookupOneLevel((yyvsp[-1].strtype)) == nullptr);
            }
            Id* id = new Id(se);
            id->addIndices((ExprStmtNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2175 "src/parser.cpp"
    break;

  case 92: /* VarDef: ID ArrIndices ASSIGN ArrayInitVal  */
#line 633 "src/parser.y"
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
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel((yyvsp[-3].strtype)) == nullptr){
                identifiers->install((yyvsp[-3].strtype), se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)(yyvsp[-3].strtype));
                assert(identifiers->lookupOneLevel((yyvsp[-3].strtype)) == nullptr);
            }
            Id* id = new Id(se);
            id->addIndices((ExprStmtNode*)(yyvsp[-2].stmttype));
            (yyval.stmttype) = new DefNode(id, (Node*)(yyvsp[0].stmttype), false, true);
        }
#line 2201 "src/parser.cpp"
    break;

  case 93: /* $@2: %empty  */
#line 656 "src/parser.y"
            {
        // 返回值类型是ID的type，函数定义中需要创建新的符号表
        Type *funcType;
        funcType = new FunctionType((yyvsp[-1].type),{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        identifiers = new SymbolTable(identifiers);
    }
#line 2214 "src/parser.cpp"
    break;

  case 94: /* $@3: %empty  */
#line 664 "src/parser.y"
                     {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-3].strtype));
            assert(se != nullptr);
            if((yyvsp[0].stmttype)!=nullptr){
                 (dynamic_cast<FunctionType*>(se->getType()))->setparamsType(
                    (dynamic_cast<FuncDefParamsNode*>((yyvsp[0].stmttype)))->getParamsType()
                );
            }   
        }
#line 2229 "src/parser.cpp"
    break;

  case 95: /* FuncDef: Type ID $@2 LPAREN FuncParams $@3 RPAREN BlockStmt  */
#line 676 "src/parser.y"
    {
         SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-6].strtype));
            assert(se != nullptr);
            (yyval.stmttype) = new FunctionDef(se, dynamic_cast<FuncDefParamsNode*>((yyvsp[-3].stmttype)), (yyvsp[0].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
            delete [](yyvsp[-6].strtype);
    }
#line 2244 "src/parser.cpp"
    break;

  case 96: /* FuncParams: FuncParams PARSE FuncParam  */
#line 689 "src/parser.y"
                                   {
            FuncDefParamsNode* node = (FuncDefParamsNode*)(yyvsp[-2].stmttype);
            node->addNext(((DefNode*)(yyvsp[0].stmttype))->getId());
            (yyval.stmttype) = node;
        }
#line 2254 "src/parser.cpp"
    break;

  case 97: /* FuncParams: FuncParam  */
#line 694 "src/parser.y"
                  {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext(((DefNode*)(yyvsp[0].stmttype))->getId());
            (yyval.stmttype) = node;
        }
#line 2264 "src/parser.cpp"
    break;

  case 98: /* FuncParams: %empty  */
#line 699 "src/parser.y"
               {
            (yyval.stmttype) = nullptr;
        }
#line 2272 "src/parser.cpp"
    break;

  case 99: /* FuncParam: Type ID  */
#line 706 "src/parser.y"
                {
            SymbolEntry *se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 2282 "src/parser.cpp"
    break;

  case 100: /* FuncParam: Type ID LBRACKET RBRACKET ArrIndices  */
#line 711 "src/parser.y"
                                          {
            Type* arrayType = nullptr; 
            if((yyvsp[-4].type)==TypeSystem::intType){
                arrayType = new IntArrayType();
            }
            else if((yyvsp[-4].type)==TypeSystem::floatType){
                arrayType = new FloatArrayType();
               
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *addDim = new ConstantSymbolEntry(TypeSystem::constIntType, -1);
            dynamic_cast<ExprStmtNode*>((yyvsp[0].stmttype))->addFirst(new Constant(addDim));
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices((ExprStmtNode*)(yyvsp[0].stmttype));
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2305 "src/parser.cpp"
    break;

  case 101: /* FuncParam: Type ID LBRACKET RBRACKET  */
#line 729 "src/parser.y"
                                 {
            Type* arrayType = nullptr; 
            if((yyvsp[-3].type)==TypeSystem::intType){
                arrayType = new IntArrayType();
            }
            else if((yyvsp[-3].type)==TypeSystem::floatType){
                arrayType = new FloatArrayType();
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *addDim = new ConstantSymbolEntry(TypeSystem::constIntType, -1);
            ExprStmtNode* indices = new ExprStmtNode();
            indices->addNext(new Constant(addDim));
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            Id* id = new Id(se);
            id->addIndices(indices);
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2328 "src/parser.cpp"
    break;


#line 2332 "src/parser.cpp"

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

#line 750 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
