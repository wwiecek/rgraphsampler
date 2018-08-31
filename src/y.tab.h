/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 47 "gs_parser.y" /* yacc.c:1909  */

  double dval;
  int    ival;
  long   lval;
  int    ivarnum;
  double *parray;
  char   *pchar;

#line 221 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
