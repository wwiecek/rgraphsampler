/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 15 "gs_parser.y" /* yacc.c:339  */

 /* includes */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include "graph_sampler.h"  /* includes global variables to pass to main */
 #include "lexerr.h"
 #include "matrices.h"
 #include "lists.h"

 /* prototypes */
 int  yylex(void);
 void yyerror(const char *message);
 
 extern int yylineno; /* from lexer */
 
 /* local variables */
 double*      pmat = 0x0;
 PLISTI       plistindic = NULL;
 PLISTELEMI   pleindic;
 PLISTD       plist = NULL;
 PLISTELEMD   ple;
 PLISTSTR     pstrlist = NULL;
 PLISTELEMSTR pstrle;
 PLISTVAR     pvarlist = NULL;
 double       average;
 int          count;
 int          dim1, dim2;
 int          i, j;
 char         *current_var;


#line 100 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    alpha_motif_id = 258,
    autocycle_id = 259,
    alpha_normal_gamma_id = 260,
    bBN_id = 261,
    bConvergence_check_id = 262,
    bDBN_id = 263,
    bDirichlet_id = 264,
    beta_motif_id = 265,
    beta_normal_gamma_id = 266,
    bHypergraph_id = 267,
    bNormalGamma_id = 268,
    bPriorConcordance_id = 269,
    bPriorDegreeNode_id = 270,
    bPriorEdgeCount_id = 271,
    bPriorMotif_id = 272,
    bPriorSCC_id = 273,
    bZellner_id = 274,
    bsave_best_graph_id = 275,
    bsave_the_chain_id = 276,
    bsave_the_degree_counts_id = 277,
    bsave_the_edge_probabilities_id = 278,
    bsave_the_motifs_probabilities_id = 279,
    end_at_iter_id = 280,
    end_id = 281,
    extra_df_wishart_id = 282,
    gamma_degree_id = 283,
    gamma_scc_id = 284,
    gamma_zellner_id = 285,
    lambda_concord_id = 286,
    lambda_scc_id = 287,
    likelihood_id = 288,
    maximum_scc_size_id = 289,
    n_saved_adjacency_id = 290,
    nBurnin_id = 291,
    nData_id = 292,
    nNodes_id = 293,
    nRuns_id = 294,
    rdm_generator_id = 295,
    scale_wishart_diag_id = 296,
    scale_wishart_offdiag_id = 297,
    seed_id = 298,
    start_at_iter_id = 299,
    chain_file_names_id = 300,
    nLevels_id = 301,
    perk_scale_id = 302,
    data_id = 303,
    edge_requirements_id = 304,
    hyper_pB_id = 305,
    initial_adjacency_id = 306,
    INTEGER = 307,
    LONG = 308,
    FLOAT = 309,
    ARRAY = 310,
    CONSTANTGAMMA = 311,
    DIRICHLET = 312,
    EMPTY = 313,
    EQUANIMOUS = 314,
    FULL = 315,
    IMPORT = 316,
    INCREMENTAL = 317,
    L_CBRACE = 318,
    L_PARENTHESIS = 319,
    MATRIX = 320,
    MT19937 = 321,
    NA = 322,
    NORMALGAMMA = 323,
    RANDOM = 324,
    R_CBRACE = 325,
    R_PARENTHESIS = 326,
    STANDARD_CHAIN = 327,
    STANDARD_EDGEP = 328,
    TAUS2 = 329,
    ZELLNER = 330,
    IDENTIFIER = 331,
    CHAINFILENAME = 332,
    FILENAME = 333,
    UMINUS = 334
  };
#endif
/* Tokens.  */
#define alpha_motif_id 258
#define autocycle_id 259
#define alpha_normal_gamma_id 260
#define bBN_id 261
#define bConvergence_check_id 262
#define bDBN_id 263
#define bDirichlet_id 264
#define beta_motif_id 265
#define beta_normal_gamma_id 266
#define bHypergraph_id 267
#define bNormalGamma_id 268
#define bPriorConcordance_id 269
#define bPriorDegreeNode_id 270
#define bPriorEdgeCount_id 271
#define bPriorMotif_id 272
#define bPriorSCC_id 273
#define bZellner_id 274
#define bsave_best_graph_id 275
#define bsave_the_chain_id 276
#define bsave_the_degree_counts_id 277
#define bsave_the_edge_probabilities_id 278
#define bsave_the_motifs_probabilities_id 279
#define end_at_iter_id 280
#define end_id 281
#define extra_df_wishart_id 282
#define gamma_degree_id 283
#define gamma_scc_id 284
#define gamma_zellner_id 285
#define lambda_concord_id 286
#define lambda_scc_id 287
#define likelihood_id 288
#define maximum_scc_size_id 289
#define n_saved_adjacency_id 290
#define nBurnin_id 291
#define nData_id 292
#define nNodes_id 293
#define nRuns_id 294
#define rdm_generator_id 295
#define scale_wishart_diag_id 296
#define scale_wishart_offdiag_id 297
#define seed_id 298
#define start_at_iter_id 299
#define chain_file_names_id 300
#define nLevels_id 301
#define perk_scale_id 302
#define data_id 303
#define edge_requirements_id 304
#define hyper_pB_id 305
#define initial_adjacency_id 306
#define INTEGER 307
#define LONG 308
#define FLOAT 309
#define ARRAY 310
#define CONSTANTGAMMA 311
#define DIRICHLET 312
#define EMPTY 313
#define EQUANIMOUS 314
#define FULL 315
#define IMPORT 316
#define INCREMENTAL 317
#define L_CBRACE 318
#define L_PARENTHESIS 319
#define MATRIX 320
#define MT19937 321
#define NA 322
#define NORMALGAMMA 323
#define RANDOM 324
#define R_CBRACE 325
#define R_PARENTHESIS 326
#define STANDARD_CHAIN 327
#define STANDARD_EDGEP 328
#define TAUS2 329
#define ZELLNER 330
#define IDENTIFIER 331
#define CHAINFILENAME 332
#define FILENAME 333
#define UMINUS 334

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 50 "gs_parser.y" /* yacc.c:355  */

  double dval;
  int    ival;
  long   lval;
  int    ivarnum;
  double *parray;
  char   *pchar;

#line 307 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 324 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  242

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    81,    80,    86,    79,     2,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    84,
       2,    85,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   163,   164,   165,   166,   167,   171,   182,
     188,   192,   196,   198,   200,   202,   204,   206,   210,   214,
     218,   222,   226,   230,   234,   236,   238,   240,   242,   247,
     252,   257,   258,   260,   262,   269,   276,   283,   290,   292,
     304,   306,   308,   310,   312,   317,   321,   323,   327,   331,
     333,   337,   338,   340,   344,   345,   347,   351,   363,   388,
     402,   421,   445,   469,   493,   505,   517,   529,   541,   569,
     637,   714,   742,   765,   791,   795,   798,   802,   808,   815,
     819,   824,   828,   832,   836,   840,   843,   847,   848,   849,
     850,   855,   856,   857,   858,   860,   861
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "alpha_motif_id", "autocycle_id",
  "alpha_normal_gamma_id", "bBN_id", "bConvergence_check_id", "bDBN_id",
  "bDirichlet_id", "beta_motif_id", "beta_normal_gamma_id",
  "bHypergraph_id", "bNormalGamma_id", "bPriorConcordance_id",
  "bPriorDegreeNode_id", "bPriorEdgeCount_id", "bPriorMotif_id",
  "bPriorSCC_id", "bZellner_id", "bsave_best_graph_id",
  "bsave_the_chain_id", "bsave_the_degree_counts_id",
  "bsave_the_edge_probabilities_id", "bsave_the_motifs_probabilities_id",
  "end_at_iter_id", "end_id", "extra_df_wishart_id", "gamma_degree_id",
  "gamma_scc_id", "gamma_zellner_id", "lambda_concord_id", "lambda_scc_id",
  "likelihood_id", "maximum_scc_size_id", "n_saved_adjacency_id",
  "nBurnin_id", "nData_id", "nNodes_id", "nRuns_id", "rdm_generator_id",
  "scale_wishart_diag_id", "scale_wishart_offdiag_id", "seed_id",
  "start_at_iter_id", "chain_file_names_id", "nLevels_id", "perk_scale_id",
  "data_id", "edge_requirements_id", "hyper_pB_id", "initial_adjacency_id",
  "INTEGER", "LONG", "FLOAT", "ARRAY", "CONSTANTGAMMA", "DIRICHLET",
  "EMPTY", "EQUANIMOUS", "FULL", "IMPORT", "INCREMENTAL", "L_CBRACE",
  "L_PARENTHESIS", "MATRIX", "MT19937", "NA", "NORMALGAMMA", "RANDOM",
  "R_CBRACE", "R_PARENTHESIS", "STANDARD_CHAIN", "STANDARD_EDGEP", "TAUS2",
  "ZELLNER", "IDENTIFIER", "CHAINFILENAME", "FILENAME", "'-'", "'+'",
  "'*'", "'/'", "UMINUS", "';'", "'='", "','", "$accept", "program",
  "user_var", "statement", "end", "matrix_declaration",
  "array_declaration", "list", "list_w_NA", "str", "str_list", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,    45,
      43,    42,    47,   334,    59,    61,    44
};
# endif

#define YYPACT_NINF -82

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-82)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -82,    56,   -82,   -81,   -35,    24,    31,    61,    62,    68,
      77,    83,    84,    85,    88,   100,   101,   102,   104,   107,
     114,   115,   116,   119,   122,   125,   -82,   134,   137,   143,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   -82,   -82,   168,   -40,   -82,    33,    39,   144,
     144,   144,   144,   -19,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,    99,   144,
     144,   144,   144,   144,   144,   -25,   144,   144,   144,   144,
     174,   175,   199,   -14,   190,    96,   191,   144,   -82,   -82,
     -82,   -82,   -82,   -82,   144,   -82,   144,   136,   136,   136,
     136,   -82,   -82,   -82,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   -82,   -82,
     -82,   -82,   136,   136,   136,   136,   136,   136,   -82,   -82,
     136,   136,   136,   136,   194,   195,   196,   197,   198,   200,
     201,   202,   145,   203,   136,   132,   -82,   144,   144,   144,
     144,   185,   144,   144,   189,    58,   144,   189,   112,   130,
      75,   -82,    32,    32,   -82,   -82,   -82,   -41,   -34,   136,
     -28,   -82,   204,   -82,    38,   136,    45,   205,   206,    66,
     207,   208,   209,   210,    72,   -82,   192,   -82,   144,   -82,
     -82,   -82,   126,   -82,   -82,   140,   -82,   212,   -82,   -82,
     -82,   -82,   -82,   136,   -82,   136,   144,   211,   136,   187,
     144,   136
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     5,     0,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,    87,    88,    89,     0,    90,     0,    51,    10,    31,
      11,    14,    12,    13,    17,    28,    52,    32,    18,    29,
      45,    47,    48,    50,    53,    30,    20,    19,    22,    21,
      23,    16,    34,    49,    54,    33,    46,    55,    25,    24,
      26,    27,    37,    38,    40,    56,    44,    39,    43,    42,
      35,    36,    41,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,     0,    95,     0,     0,     0,
       0,    86,    76,    76,    83,    81,    76,    83,    76,     0,
      76,    96,    92,    91,    93,    94,    84,     0,     0,    74,
       0,    82,     0,    78,     0,    77,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,    72,     0,    73,
      70,    69,     0,    62,    68,    64,    63,     0,    59,    60,
      61,    58,    85,    75,    80,    79,     0,     0,    66,    65,
       0,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -45,   -82,    86,
     -82,   -59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    54,    55,    56,    57,    58,   198,   204,   202,
     197,   199
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     117,   118,   119,   120,    59,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   215,
     152,   153,   154,   155,   156,   157,   217,   160,   161,   162,
     163,   158,   219,   121,   108,   216,   172,   167,   174,   159,
      60,   168,   218,   122,   123,   175,     2,   176,   218,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,   221,    61,
     111,   112,   113,   179,   180,   223,    62,   109,   192,   193,
     194,   195,   114,   110,   222,   203,   205,   111,   112,   113,
     194,   218,    52,   211,   115,   212,   226,   116,   200,   114,
      53,   206,   231,   209,   213,   214,    63,    64,   111,   112,
     113,   115,   218,    65,   116,   148,   149,   170,   218,   233,
     114,   171,    66,   235,   111,   112,   113,   150,    67,    68,
      69,   208,   115,    70,   151,   116,   114,   238,   111,   112,
     113,   241,   111,   112,   113,    71,    72,    73,   115,    74,
     114,   116,    75,   234,   114,   210,   111,   112,   113,    76,
      77,    78,   115,   191,    79,   116,   115,    80,   114,   116,
      81,   177,   178,   179,   180,   177,   178,   179,   180,    82,
     115,   236,    83,   116,   177,   178,   189,   180,    84,   164,
     165,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   166,   169,   173,   181,   182,   183,
     184,   185,   196,   186,   187,   188,   190,   201,   240,   232,
     227,   237,     0,   207,   220,   224,   225,     0,   228,   229,
     230,   239
};

static const yytype_int16 yycheck[] =
{
      59,    60,    61,    62,    85,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    70,
      89,    90,    91,    92,    93,    94,    70,    96,    97,    98,
      99,    66,    70,    62,    84,    86,   105,    61,   107,    74,
      85,    65,    86,    72,    73,   114,     0,   116,    86,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    70,    85,
      52,    53,    54,    81,    82,    70,    85,    84,   177,   178,
     179,   180,    64,    84,    86,    67,   185,    52,    53,    54,
     189,    86,    76,    58,    76,    60,    70,    79,   183,    64,
      84,   186,    70,   188,    69,   190,    85,    85,    52,    53,
      54,    76,    86,    85,    79,    56,    57,    61,    86,   218,
      64,    65,    85,   222,    52,    53,    54,    68,    85,    85,
      85,    59,    76,    85,    75,    79,    64,   236,    52,    53,
      54,   240,    52,    53,    54,    85,    85,    85,    76,    85,
      64,    79,    85,    67,    64,    65,    52,    53,    54,    85,
      85,    85,    76,    71,    85,    79,    76,    85,    64,    79,
      85,    79,    80,    81,    82,    79,    80,    81,    82,    85,
      76,    81,    85,    79,    79,    80,    81,    82,    85,    55,
      55,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    55,    65,    65,    63,    63,    63,
      63,    63,    77,    63,    63,    63,    63,    78,    81,    77,
      63,    59,    -1,   187,    70,    70,    70,    -1,    70,    70,
      70,    70
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    88,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    76,    84,    89,    90,    91,    92,    93,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    84,    84,
      84,    52,    53,    54,    64,    76,    79,    98,    98,    98,
      98,    62,    72,    73,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    56,    57,
      68,    75,    98,    98,    98,    98,    98,    98,    66,    74,
      98,    98,    98,    98,    55,    55,    55,    61,    65,    65,
      61,    65,    98,    65,    98,    98,    98,    79,    80,    81,
      82,    63,    63,    63,    63,    63,    63,    63,    63,    81,
      63,    71,    98,    98,    98,    98,    77,    97,    94,    98,
      94,    78,    96,    67,    95,    98,    94,    96,    59,    94,
      65,    58,    60,    69,    94,    70,    86,    70,    86,    70,
      70,    70,    86,    70,    70,    70,    70,    63,    70,    70,
      70,    70,    77,    98,    67,    98,    81,    59,    98,    70,
      81,    98
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    88,    88,    88,    88,    88,    89,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      95,    95,    96,    96,    97,    97,    97,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     3,     2,     2,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     6,     6,
       6,     6,     6,     6,     6,     8,     8,    10,     6,     6,
       6,     6,     6,     6,     1,     3,     0,     1,     1,     3,
       3,     0,     1,     0,     1,     3,     0,     1,     1,     1,
       1,     3,     3,     3,     3,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 8:
#line 171 "gs_parser.y" /* yacc.c:1646  */
    {
   // printf("Found user variable \"%s\"\n", $1);
   // printf ("yylval.pchar: %s\n", yylval.pchar);
   if (!pvarlist) pvarlist = InitVarList();
   UniqueQueueVarListItem (pvarlist, (yyvsp[0].pchar), 0);
   current_var = CopyString((yyvsp[0].pchar));
   // PrintVarList(stdout, pvarlist->Head, NULL);
 }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 182 "gs_parser.y" /* yacc.c:1646  */
    {
   // printf("Executing \"%s\"\n", $1);
   // printf ("current_var %s\n", current_var);
   UniqueQueueVarListItem (pvarlist, current_var, (yyvsp[0].dval)); }
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 188 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bAutocycles = (yyvsp[0].dval);
   else yyerror("autocycles should be 0 or 1"); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 192 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bBN = (yyvsp[0].dval);
   else yyerror("bBN should be 0 or 1"); }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 196 "gs_parser.y" /* yacc.c:1646  */
    { bConvergence_std = 1; }
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 198 "gs_parser.y" /* yacc.c:1646  */
    { bConvergence_std = 2; }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 200 "gs_parser.y" /* yacc.c:1646  */
    { bConvergence_inc = 1; }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 202 "gs_parser.y" /* yacc.c:1646  */
    { nConvergence_start = (yyvsp[0].dval); }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 204 "gs_parser.y" /* yacc.c:1646  */
    { nConvergence_end   = (yyvsp[0].dval); }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 206 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bDBN = (yyvsp[0].dval);
   else yyerror("bDBN should be 0 or 1"); }
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 210 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bHypergraph = (yyvsp[0].dval);
   else yyerror("hypergraph should be 0 or 1"); }
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 214 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bsave_the_chain = (yyvsp[0].dval);
   else yyerror("bsave_the_chain should be 0 or 1"); }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 218 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bsave_best_graph = (yyvsp[0].dval);
   else yyerror("bsave_best_graph should be 0 or 1"); }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 222 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bsave_the_edge_probabilities = (yyvsp[0].dval);
   else yyerror("bsave_the_edge_probabilities should be 0 or 1"); }
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 226 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bsave_the_degree_counts = (yyvsp[0].dval);
   else yyerror("bsave_the_degree_counts should be 0 or 1"); }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 230 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bsave_the_motifs_probabilities = (yyvsp[0].dval);
   else yyerror("bsave_the_motifs_probabilities should be 0 or 1"); }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 234 "gs_parser.y" /* yacc.c:1646  */
    { bDirichlet = 1; }
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 236 "gs_parser.y" /* yacc.c:1646  */
    { bConstantGamma = 1; }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 238 "gs_parser.y" /* yacc.c:1646  */
    { bNormalGamma = 1; }
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 240 "gs_parser.y" /* yacc.c:1646  */
    { bZellner = 1; }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 242 "gs_parser.y" /* yacc.c:1646  */
    {
   printf ("Deprecated syntax, you should use likelihood = <KEYWORD>.\n");
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bDirichlet = (yyvsp[0].dval);
   else yyerror("bDirichlet should be 0 or 1"); }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 247 "gs_parser.y" /* yacc.c:1646  */
    {
   printf ("Deprecated syntax, you should use likelihood = <KEYWORD>.\n");
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bNormalGamma = (yyvsp[0].dval);
   else yyerror("normal_gamma_score should be 0 or 1"); }
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 252 "gs_parser.y" /* yacc.c:1646  */
    {
   printf ("Deprecated syntax, you should use likelihood = <KEYWORD>.\n");
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bZellner = (yyvsp[0].dval);
   else yyerror("bZellner should be 0 or 1"); }
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 257 "gs_parser.y" /* yacc.c:1646  */
    { alpha_normal_gamma = (yyvsp[0].dval); }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 258 "gs_parser.y" /* yacc.c:1646  */
    {  beta_normal_gamma = (yyvsp[0].dval); }
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 260 "gs_parser.y" /* yacc.c:1646  */
    { gamma_zellner = (yyvsp[0].dval); }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 262 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) < 0) || (((yyvsp[0].dval) - (int)(yyvsp[0].dval)) != 0)) {
     yyerror("extra_df_wishart should be a positive or null integer");
   }
   else
     extra_df_wishart = (yyvsp[0].dval); }
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 269 "gs_parser.y" /* yacc.c:1646  */
    {
   if ((yyvsp[0].dval) < 0) {
     yyerror("scale_wishart_diagonal should be positive");
   }
   else
     scale_wishart_diag = (yyvsp[0].dval); }
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 276 "gs_parser.y" /* yacc.c:1646  */
    {
   if ((yyvsp[0].dval) < 0) {
     yyerror("scale_wishart_offdiagonal should be positive");
   }
   else
     scale_wishart_offdiag = (yyvsp[0].dval); }
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 283 "gs_parser.y" /* yacc.c:1646  */
    {
   if ((yyvsp[0].dval) < 0) {
     yyerror("maximum_scc_size should be positive");
   }
   else
     maximum_scc_size = (yyvsp[0].dval); }
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 290 "gs_parser.y" /* yacc.c:1646  */
    { n_saved_adjacency = (yyvsp[0].dval); }
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 292 "gs_parser.y" /* yacc.c:1646  */
    {
   if ((yyvsp[0].dval) > LONG_MAX) {
     fprintf(stderr, "Error: nRuns requested > %lu - Exiting.\n\n", ULONG_MAX);
     exit(0);
   }
   else {
     if ((yyvsp[0].dval) < 1)
       yyerror("nRuns must be > 0");
     else
       nRuns = (unsigned long) (yyvsp[0].dval);
   } }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 304 "gs_parser.y" /* yacc.c:1646  */
    { nBurnin           = (yyvsp[0].dval); }
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 306 "gs_parser.y" /* yacc.c:1646  */
    { seed              = (yyvsp[0].dval); }
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 308 "gs_parser.y" /* yacc.c:1646  */
    { rdm_gen_name = taus2; }
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 310 "gs_parser.y" /* yacc.c:1646  */
    { rdm_gen_name = mt19937; }
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 312 "gs_parser.y" /* yacc.c:1646  */
    {
   if (nNodes)  {yyerror("n_nodes cannot be reassigned"); }
   if ((yyvsp[0].dval) == 0) {yyerror("n_nodes cannot be zero");       }
   nNodes = (yyvsp[0].dval); }
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 317 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bPriorConcordance = (yyvsp[0].dval);
   else yyerror("bPriorConcordance should be 0 or 1"); }
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 321 "gs_parser.y" /* yacc.c:1646  */
    { lambda_concord = (yyvsp[0].dval); }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 323 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bPriorDegreeNode = (yyvsp[0].dval);
   else yyerror("bPriorDegreeNode should be 0 or 1"); }
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 327 "gs_parser.y" /* yacc.c:1646  */
    {
   bPriorEdgeCount = TRUE;
   expected_n_edges = (yyvsp[0].dval); }
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 331 "gs_parser.y" /* yacc.c:1646  */
    { gamma_degree = (yyvsp[0].dval); }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 333 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bPriorMotif = (yyvsp[0].dval);
   else yyerror("bPriorMotif should be 0 or 1"); }
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 337 "gs_parser.y" /* yacc.c:1646  */
    { alpha_motif = (yyvsp[0].dval); }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 338 "gs_parser.y" /* yacc.c:1646  */
    { beta_motif  = (yyvsp[0].dval); }
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 340 "gs_parser.y" /* yacc.c:1646  */
    {
   if (((yyvsp[0].dval) == 0) || ((yyvsp[0].dval) == 1)) bPriorSCC = (yyvsp[0].dval);
   else yyerror("bPriorSCC should be 0 or 1"); }
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 344 "gs_parser.y" /* yacc.c:1646  */
    { gamma_scc  = (yyvsp[0].dval); }
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 345 "gs_parser.y" /* yacc.c:1646  */
    { lambda_scc = (yyvsp[0].dval); }
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 347 "gs_parser.y" /* yacc.c:1646  */
    { nData = (yyvsp[0].dval); }
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 351 "gs_parser.y" /* yacc.c:1646  */
    {
  // printf("Reach end of input file.\n\n");
  /* check that each defined variable is used */
  /* for (i = 0; i < MAXNUSERVAR; i++) */
  /*   if (is_defined[i] && !is_used[i]) */
  //    lexerr("some user-defined variables are not used");
  return (0);
 }
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 363 "gs_parser.y" /* yacc.c:1646  */
    {

   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (plist->lSize != (nNodes * nNodes)) /* problem */
     yyerror("initial adjacency should have n_nodes by n_nodes elements");

   if (!current_adj)
    current_adj = InitiMatrix(nNodes, nNodes);
   else
    yyerror("initial adjacency redefinition is not allowed");

   ple = plist->Head;
   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nNodes; j++) {
       if ((ple->dVal != 0) && (ple->dVal != 1))
         yyerror("adjacency matrix elements can only be 0 or 1");
       current_adj[i][j] = (int) ple->dVal;
       ple = ple->next;
     }
   }
   FreedList(&plist);
 }
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 388 "gs_parser.y" /* yacc.c:1646  */
    { /* empty graph */
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (!current_adj)
    current_adj = InitiMatrix(nNodes, nNodes);
   else
    yyerror("initial_adjacency redefinition is not allowed");

   for (i = 0; i < nNodes; i++)
     for (j = 0; j < nNodes; j++)
       current_adj[i][j] = 0;
 }
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 402 "gs_parser.y" /* yacc.c:1646  */
    { /* full graph */
   if (!nNodes)
     yyerror("n_nodes must be set before defining matrices");

   if (!current_adj)
     current_adj = InitiMatrix(nNodes, nNodes);
   else
     yyerror("initial_adjacency redefinition is not allowed");

   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nNodes; j++) {
       if ((i == j) && (bBN))
         current_adj[i][j] = 0;
       else
         current_adj[i][j] = 1;
     }
   }
 }
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 421 "gs_parser.y" /* yacc.c:1646  */
    {
   /* random graph */
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (!seed)
    yyerror("random seed must be set before defining a random matrix");
   else InitRandoms(rdm_gen_name, seed);

   if (!current_adj)
    current_adj = InitiMatrix(nNodes, nNodes);
   else
    yyerror("initial_adjacency redefinition is not allowed");

   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nNodes; j++) {
       if ((i == j) && (bBN || (bAutocycles == FALSE) || bHypergraph))
         current_adj[i][j] = 0;
       else
         current_adj[i][j] = round(Randoms());
     }
   }
 }
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 445 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (plist->lSize !=  (nNodes * nNodes)) /* problem */
    yyerror("edge_requirements should have n_nodes elements");

   if (!edge_requirements)
    edge_requirements = InitiMatrix(nNodes, nNodes);
   else
    yyerror("edge_requirements redefinition is not allowed");

   ple = plist->Head;
   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nNodes; j++) {
       if ((ple->dVal != 0) && (fabs(ple->dVal) != 1))
         yyerror("edge_requirements elements can only be -1, 0 or 1");
       edge_requirements[i][j] = (int) ple->dVal;
       ple = ple->next;
     }
   }
   FreedList(&plist);
 }
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 469 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (plist->lSize != (nNodes * nNodes)) /* problem */
    yyerror("hyper_pB should have n_nodes elements");

   if (!hyper_pB)
    hyper_pB = InitdMatrix(nNodes, nNodes);
   else
    yyerror("hyper_pB redefinition is not allowed");

   ple = plist->Head;
   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nNodes; j++) {
       if ((ple->dVal < 0) || (ple->dVal > 1))
         yyerror("Bernoulli prior probabilities have to be in [0,1]");
       hyper_pB[i][j] = ple->dVal;
       ple = ple->next;
     }
   }
   FreedList(&plist);
 }
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 493 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* do nothing: scale_pB defaults to 1 and equanimous is the default and
      will be initialized in InitArrays */

 }
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 505 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* init scale_pB and do nothing else because equanimous is the default and
      will be initialized in InitArrays */
   scale_pB = (yyvsp[-5].dval);
 }
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 517 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* init scale_pB and do nothing else because equanimous is the default and
      will be initialized in InitArrays */
   scale_pB = (yyvsp[0].dval);
 }
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 529 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* init scale_pB and do nothing else because equanimous is the default and
      will be initialized in InitArrays */
   scale_pB = (yyvsp[-7].dval) * (yyvsp[0].dval);
 }
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 541 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (!hyper_pB)
    hyper_pB = InitdMatrix(nNodes, nNodes);
   else
    yyerror("hyper_pB redefinition is not allowed");

   pstrle = pstrlist->Head;
   FILE *priorfile;
   priorfile = fopen(pstrle->cVal, "r");
   if (!priorfile)
     yyerror("prior specification file could not be opened");

   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nNodes; j++)
       if (!fscanf(priorfile, "%lg", &(hyper_pB[i][j]))) {
         yyerror("cannot read all imported prior specification");
       }
       else {
         if ((hyper_pB[i][j] < 0) || (hyper_pB[i][j] > 1))
           yyerror("Bernoulli prior probabilities have to be in [0,1]");
       }
   }
   fclose(priorfile);
 }
#line 2214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 569 "gs_parser.y" /* yacc.c:1646  */
    {
   if (!nNodes)
     yyerror("n_nodes must be set before defining matrices");

   if (!nData)
     yyerror("n_data must be set before defining data values");

   if (plist->lSize != (nNodes * nData)) /* problem */
     yyerror("Data should have n_nodes * n_data elements");

   if (!pData) {
     /* init global data array */
     pData = InitdMatrix(nNodes, nData);
     /* init a global list of the missing data coordinates */
     plistMissing = InitijList();
     /* init missing data indicator array (a flag per node) */
     bHasMissing = InitiVector(nNodes);
   }
   else
     yyerror("Data redefinition is not allowed");

   if (bNAData)
     printf("Missing data will be imputed.\n\n");

   ple = plist->Head;
   pleindic = plistindic->Head;
   for (i = 0; i < nNodes; i++) {
     count = average = 0; /* reset */
     for (j = 0; j < nData; j++) {
       if (pleindic->iVal == 1) { /* data is missing */
         QueueijListItem(plistMissing, i, j); /* store location in queue */
         bHasMissing[i] = TRUE;
       }
       else {
         pData[i][j] = ple->dVal;
         average = average + pData[i][j]; /* cumulate */
         count += 1;
       }
       ple = ple->next;
       pleindic = pleindic->next;
     } /* for j data */

     /* avoid useless work */
     if (bHasMissing[i] == TRUE) {
       /* compute the actual average on non-missing data for node i */
       if (count == 0) {
         printf("Warning: node %d has all data missing.\n", i+1);
         average = 0; /* arbitrary */
       }
       else {
         average = average / count;
       }

       /* impute average */
       PLISTELEMIJ pleIter = plistMissing->Head;
       while (pleIter) {
         if (pleIter->iVal == i)
           pData[i][pleIter->jVal] = average;
         pleIter = pleIter->next;
       }
     } /* if bHasMissing */
   } /* for ith node */

   FreedList(&plist);
   FreeiList(&plistindic);
   
 }
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 637 "gs_parser.y" /* yacc.c:1646  */
    {

   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (!nData)
    yyerror("n_data must be set before defining data values");

   if (!pData) {
     /* init global data array */
     pData = InitdMatrix(nNodes, nData);
     /* init a global list of the missing data coordinates */
     plistMissing = InitijList();
     /* init missing data indicator array (a flag per node) */
     bHasMissing = InitiVector(nNodes);
   }
   else
     yyerror("Data redefinition is not allowed");

   pstrle = pstrlist->Head;
   FILE *datafile;
   datafile = fopen(pstrle->cVal, "r");
   if (!datafile)
     yyerror("data file could not be opened");

   char sztmp[4];
   for (i = 0; i < nNodes; i++) {
     count = average = 0; /* reset */
     for (j = 0; j < nData; j++) {
       if (fscanf(datafile, "%lg", &(pData[i][j])) < 1) {
         yyerror("cannot read all data required");
       }
       else { /* data read in OK */
         /* hack to check for nan */
         snprintf(sztmp, 4, "%g", pData[i][j]);
         if (!strcmp(sztmp, "nan")) { /* data is missing */
           if (!bNAData)
             printf("Missing data will be imputed.\n\n");           
           bNAData = TRUE;
           QueueijListItem(plistMissing, i, j); /* store location in queue */
           bHasMissing[i] = TRUE;
         }
         else {
           average = average + pData[i][j]; /* cumulate */
           count += 1;
         }
       }
     } /* for j data */

     /* avoid useless work */
     if (bHasMissing[i] == TRUE) {
       /* compute the actual average on non-missing data for node i */
       if (count == 0) {
         printf("Warning: node %d has all data missing.\n", i+1);
         average = 0; /* arbitrary */
       }
       else {
         average = average / count;
       }

       /* impute average */
       PLISTELEMIJ pleIter = plistMissing->Head;
       while (pleIter) {
         if (pleIter->iVal == i)
           pData[i][pleIter->jVal] = average;
         pleIter = pleIter->next;
       }
     } /* if bHasMissing */
   } /* for ith node */
 
   fclose(datafile);

 }
#line 2364 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 714 "gs_parser.y" /* yacc.c:1646  */
    {

   nChains = pstrlist->lSize; // printf("nChains = %d\n", nChains); 

   if (nChains == 0)
     yyerror("empty file list");

   if (nChains == 1)
     yyerror("convergence cannot be checked on only one chain");

   if (!pChainNames) {
     if (!(pChainNames = (char**) calloc(nChains, sizeof(char*)))) {
      yyerror("out of memory in Parser");
     }
   }
   else
    yyerror("chain files list redefinition is not allowed");

   pstrle = pstrlist->Head;
   for (i = 0; i < nChains; i++) {
     // printf ("pstrle->cVal: %s\n", pstrle->cVal);
     pChainNames[i] = pstrle->cVal;
     // printf ("pChainNames[%d]: %s\n", i, pChainNames[i]);
     pstrle = pstrle->next;
   }
   FreeStrList(&pstrlist);
 }
#line 2396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 742 "gs_parser.y" /* yacc.c:1646  */
    {

   if (!nNodes)
    yyerror("n_nodes must be set before defining data levels");

   if (plist->lSize != (nNodes)) /* problem */
     yyerror("data levels array should have n_nodes elements");

   if (!pDataLevels)
    pDataLevels = InitiVector(nNodes);
   else
    yyerror("data levels redefinition is not allowed");

   ple = plist->Head;
   for (i = 0; i < nNodes; i++) {
     if ((ple->dVal != (int) ple->dVal) || (ple->dVal < 1))
       yyerror("data levels elements must be strictly positive integers");
     pDataLevels[i] = (int) ple->dVal;
     ple = ple->next;
   }
   FreedList(&plist);
 }
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 765 "gs_parser.y" /* yacc.c:1646  */
    {

   bTempered = TRUE;

   nTemperatures = plist->lSize;

   if (nTemperatures < 2)
     yyerror("at least two values must be defined in perk_scale");

   if (!pInvTemperatures)
    pInvTemperatures = InitdVector(nTemperatures);
   else
    yyerror("perk_scale redefinition is not allowed");

   ple = plist->Head;
   for (i = 0; i < nTemperatures; i++) {
     if ((ple->dVal < 0) || (ple->dVal > 1))
       yyerror("inverse temperatures must belong to [0,1]");
     pInvTemperatures[i] = (double) ple->dVal;
     ple = ple->next;
   }
   FreedList(&plist);
 }
#line 2451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 791 "gs_parser.y" /* yacc.c:1646  */
    {
   plist = InitdList();
   QueuedListItem (plist, (yyvsp[0].dval));
 }
#line 2460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 795 "gs_parser.y" /* yacc.c:1646  */
    {
   QueuedListItem (plist, (yyvsp[0].dval));
 }
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 798 "gs_parser.y" /* yacc.c:1646  */
    { yyerror("empty list"); }
#line 2474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 802 "gs_parser.y" /* yacc.c:1646  */
    {
   plist = InitdList();
   QueuedListItem (plist, (yyvsp[0].dval));
   plistindic = InitiList();
   QueueiListItem (plistindic, 0); /* normal number */
 }
#line 2485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 808 "gs_parser.y" /* yacc.c:1646  */
    {
   plist = InitdList();
   QueuedListItem (plist, 0);      /* arbitrary zero, will be imputed */
   plistindic = InitiList();
   QueueiListItem (plistindic, 1); /* flag missing data */
   bNAData = TRUE;
 }
#line 2497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 815 "gs_parser.y" /* yacc.c:1646  */
    {
   QueuedListItem (plist, (yyvsp[0].dval));
   QueueiListItem (plistindic, 0); /* normal number */
 }
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 819 "gs_parser.y" /* yacc.c:1646  */
    {
   QueuedListItem (plist, 0);      /* arbitrary zero, will be imputed */
   QueueiListItem (plistindic, 1); /* flag missing data */
   bNAData = TRUE;
 }
#line 2516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 824 "gs_parser.y" /* yacc.c:1646  */
    { yyerror("empty list"); }
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 828 "gs_parser.y" /* yacc.c:1646  */
    {
   pstrlist = InitStrList();
   QueueStrListItem (pstrlist, (yyvsp[0].pchar));
 }
#line 2531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 832 "gs_parser.y" /* yacc.c:1646  */
    { yyerror("empty list"); }
#line 2537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 836 "gs_parser.y" /* yacc.c:1646  */
    {
   pstrlist = InitStrList();
   QueueStrListItem (pstrlist, (yyvsp[0].pchar));
 }
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 840 "gs_parser.y" /* yacc.c:1646  */
    {
   QueueStrListItem (pstrlist, (yyvsp[0].pchar));
 }
#line 2554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 843 "gs_parser.y" /* yacc.c:1646  */
    { yyerror("empty list"); }
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 847 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (int)  (yyvsp[0].ival); }
#line 2566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 848 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (long) (yyvsp[0].lval); }
#line 2572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 849 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (yyvsp[0].dval); }
#line 2578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 850 "gs_parser.y" /* yacc.c:1646  */
    {
   // printf("$1: %s\n", $1);
   if (!LookupVarList (pvarlist, (yyvsp[0].pchar), &((yyval.dval))))
     yyerror("undefined variable found");
   }
#line 2588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 855 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (yyvsp[-2].dval) + (yyvsp[0].dval); }
#line 2594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 856 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (yyvsp[-2].dval) - (yyvsp[0].dval); }
#line 2600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 857 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (yyvsp[-2].dval) * (yyvsp[0].dval); }
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 858 "gs_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].dval) == 0) { yyerror("division by zero"); }
                   else (yyval.dval) = (yyvsp[-2].dval) / (double) (yyvsp[0].dval); }
#line 2613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 860 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = -(yyvsp[0].dval); }
#line 2619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 861 "gs_parser.y" /* yacc.c:1646  */
    { (yyval.dval) = (yyvsp[-1].dval); }
#line 2625 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2629 "y.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 866 "gs_parser.y" /* yacc.c:1906  */


void lexerr(const char *message)
{
  fprintf(stderr, "Error: %s - Exiting.\n\n", message);
  exit(0);
}

/* End */
