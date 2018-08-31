/* graph_sampler grammar file

   Written by Frederic Bois

   Copyright (c) 2014-2018 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   For more details
   see the GNU General Public License at <http://www.gnu.org/licenses/>
*/

/* == Prologue ============================================================= */
%{
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
 PLISTD       plist = NULL;
 PLISTELEMD   ple;
 PLISTSTR     pstrlist = NULL;
 PLISTELEMSTR pstrle;
 PLISTVAR     pvarlist = NULL;
 int          count;
 int          dim1, dim2;
 int          i, j;
 char         *current_var;

%}

/* redefine yylval to extend it */
%union {
  double dval;
  int    ival;
  long   lval;
  int    ivarnum;
  double *parray;
  char   *pchar;
}

/* Specific declarations */

/* scalars */
%token <ivarnum> alpha_motif_id
%token <ivarnum> autocycle_id
%token <ivarnum> alpha_normal_gamma_id
%token <ivarnum> bBN_id
%token <ivarnum> bConvergence_check_id
%token <ivarnum> bDBN_id
%token <ivarnum> bDirichlet_id
%token <ivarnum> beta_motif_id
%token <ivarnum> beta_normal_gamma_id
%token <ivarnum> bHypergraph_id
%token <ivarnum> bNormalGamma_id
%token <ivarnum> bPriorConcordance_id
%token <ivarnum> bPriorDegreeNode_id
%token <ivarnum> bPriorEdgeCount_id
%token <ivarnum> bPriorMotif_id
%token <ivarnum> bPriorSCC_id
%token <ivarnum> bZellner_id
%token <ivarnum> bsave_best_graph_id
%token <ivarnum> bsave_the_chain_id
%token <ivarnum> bsave_the_degree_counts_id
%token <ivarnum> bsave_the_edge_probabilities_id
%token <ivarnum> bsave_the_motifs_probabilities_id
%token <ivarnum> end_at_iter_id
%token <ivarnum> end_id
%token <ivarnum> extra_df_wishart_id
%token <ivarnum> gamma_degree_id
%token <ivarnum> gamma_scc_id
%token <ivarnum> gamma_zellner_id
%token <ivarnum> lambda_concord_id
%token <ivarnum> lambda_scc_id
%token <ivarnum> likelihood_id
%token <ivarnum> maximum_scc_size_id
%token <ivarnum> n_saved_adjacency_id
%token <ivarnum> nBurnin_id
%token <ivarnum> nData_id
%token <ivarnum> nNodes_id
%token <ivarnum> nRuns_id
%token <ivarnum> rdm_generator_id
%token <ivarnum> scale_wishart_diag_id
%token <ivarnum> scale_wishart_offdiag_id
%token <ivarnum> seed_id
%token <ivarnum> start_at_iter_id

/* arrays */
%token <ivarnum> chain_file_names_id
%token <ivarnum> nLevels_id
%token <ivarnum> perk_scale_id

/* matrices */
%token <ivarnum> data_id
%token <ivarnum> edge_requirements_id
%token <ivarnum> hyper_pB_id
%token <ivarnum> initial_adjacency_id

/* Non-specific declarations and keywords */
%token <ival>    INTEGER
%token <lval>    LONG
%token <dval>    FLOAT

%token <ivarnum> ARRAY
%token <ivarnum> CONSTANTGAMMA
%token <ivarnum> DIRICHLET
%token <ivarnum> EMPTY
%token <ivarnum> EQUANIMOUS
%token <ivarnum> FULL
%token <ivarnum> IMPORT
%token <ivarnum> INCREMENTAL
%token <ivarnum> L_CBRACE
%token <ivarnum> L_PARENTHESIS
%token <ivarnum> MATRIX
%token <ivarnum> MT19937
%token <ivarnum> NA
%token <ivarnum> NORMALGAMMA
%token <ivarnum> RANDOM
%token <ivarnum> R_CBRACE
%token <ivarnum> R_PARENTHESIS
%token <ivarnum> STANDARD_CHAIN
%token <ivarnum> STANDARD_EDGEP
%token <ivarnum> TAUS2
%token <ivarnum> ZELLNER

%token <pchar>   IDENTIFIER
%token <pchar>   CHAINFILENAME
%token <pchar>   FILENAME

%type <dval>   expr
%type <parray> list
%type <pchar>  str
%type <pchar>  str_list
%type <pchar>  user_var

%left '-' '+'
%left '*' '/'
%nonassoc UMINUS


/* == Grammar rules ======================================================== */
%%

program:
 program statement ';'
 | program matrix_declaration ';'
 | program array_declaration ';'
 | program ';'
 | program end
 |
;

user_var:
 IDENTIFIER {
   // printf("Found user variable \"%s\"\n", $1);
   // printf ("yylval.pchar: %s\n", yylval.pchar);
   if (!pvarlist) pvarlist = InitVarList();
   UniqueQueueVarListItem (pvarlist, $1, 0);
   current_var = CopyString($1);
   // PrintVarList(stdout, pvarlist->Head, NULL);
 }
;

statement:
 user_var '=' expr {
   // printf("Executing \"%s\"\n", $1);
   // printf ("current_var %s\n", current_var);
   UniqueQueueVarListItem (pvarlist, current_var, $3); }
   // PrintVarList(stdout, pvarlist->Head, NULL); }

 | autocycle_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bAutocycles = $3;
   else yyerror("autocycles should be 0 or 1"); }

 | bBN_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bBN = $3;
   else yyerror("bBN should be 0 or 1"); }

 | bConvergence_check_id '=' STANDARD_CHAIN { bConvergence_std = 1; }

 | bConvergence_check_id '=' STANDARD_EDGEP { bConvergence_std = 2; }

 | bConvergence_check_id '=' INCREMENTAL { bConvergence_inc = 1; }

 | start_at_iter_id '=' expr { nConvergence_start = $3; }

 | end_at_iter_id   '=' expr { nConvergence_end   = $3; }

 | bDBN_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bDBN = $3;
   else yyerror("bDBN should be 0 or 1"); }

 | bHypergraph_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bHypergraph = $3;
   else yyerror("hypergraph should be 0 or 1"); }

 | bsave_the_chain_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bsave_the_chain = $3;
   else yyerror("bsave_the_chain should be 0 or 1"); }

 | bsave_best_graph_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bsave_best_graph = $3;
   else yyerror("bsave_best_graph should be 0 or 1"); }

 | bsave_the_edge_probabilities_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bsave_the_edge_probabilities = $3;
   else yyerror("bsave_the_edge_probabilities should be 0 or 1"); }

 | bsave_the_degree_counts_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bsave_the_degree_counts = $3;
   else yyerror("bsave_the_degree_counts should be 0 or 1"); }

 | bsave_the_motifs_probabilities_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bsave_the_motifs_probabilities = $3;
   else yyerror("bsave_the_motifs_probabilities should be 0 or 1"); }

 | likelihood_id '=' DIRICHLET     { bDirichlet = 1; }

 | likelihood_id '=' CONSTANTGAMMA { bConstantGamma = 1; }

 | likelihood_id '=' NORMALGAMMA   { bNormalGamma = 1; }

 | likelihood_id '=' ZELLNER       { bZellner = 1; }

 | bDirichlet_id '=' expr {
   printf ("Deprecated syntax, you should use likelihood = <KEYWORD>.\n");
   if (($3 == 0) || ($3 == 1)) bDirichlet = $3;
   else yyerror("bDirichlet should be 0 or 1"); }

 | bNormalGamma_id '=' expr {
   printf ("Deprecated syntax, you should use likelihood = <KEYWORD>.\n");
   if (($3 == 0) || ($3 == 1)) bNormalGamma = $3;
   else yyerror("normal_gamma_score should be 0 or 1"); }

 | bZellner_id '=' expr {
   printf ("Deprecated syntax, you should use likelihood = <KEYWORD>.\n");
   if (($3 == 0) || ($3 == 1)) bZellner = $3;
   else yyerror("bZellner should be 0 or 1"); }

 | alpha_normal_gamma_id    '=' expr { alpha_normal_gamma = $3; }
 | beta_normal_gamma_id     '=' expr {  beta_normal_gamma = $3; }

 | gamma_zellner_id         '=' expr { gamma_zellner = $3; }

 | extra_df_wishart_id      '=' expr {
   if (($3 < 0) || (($3 - (int)$3) != 0)) {
     yyerror("extra_df_wishart should be a positive or null integer");
   }
   else
     extra_df_wishart = $3; }

 | scale_wishart_diag_id    '=' expr {
   if ($3 < 0) {
     yyerror("scale_wishart_diagonal should be positive");
   }
   else
     scale_wishart_diag = $3; }

 | scale_wishart_offdiag_id '=' expr {
   if ($3 < 0) {
     yyerror("scale_wishart_offdiagonal should be positive");
   }
   else
     scale_wishart_offdiag = $3; }

 | maximum_scc_size_id '=' expr {
   if ($3 < 0) {
     yyerror("maximum_scc_size should be positive");
   }
   else
     maximum_scc_size = $3; }

 | n_saved_adjacency_id     '=' expr { n_saved_adjacency = $3; }

 | nRuns_id                 '=' expr {
   if ($3 > LONG_MAX) {
     fprintf(stderr, "Error: nRuns requested > %lu - Exiting.\n\n", ULONG_MAX);
     exit(0);
   }
   else {
     if ($3 < 1)
       yyerror("nRuns must be > 0");
     else
       nRuns = (unsigned long) $3;
   } }

 | nBurnin_id               '=' expr { nBurnin           = $3; }

 | seed_id                  '=' expr { seed              = $3; }

 | rdm_generator_id         '=' TAUS2   { rdm_gen_name = taus2; }

 | rdm_generator_id         '=' MT19937 { rdm_gen_name = mt19937; }

 | nNodes_id            '=' expr {
   //if (nNodes)  {yyerror("n_nodes cannot be reassigned"); }
   if ($3 == 0) {yyerror("n_nodes cannot be zero");       }
   nNodes            = $3; }

 | bPriorConcordance_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bPriorConcordance = $3;
   else yyerror("bPriorConcordance should be 0 or 1"); }

 | lambda_concord_id '=' expr { lambda_concord = $3; }

 | bPriorDegreeNode_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bPriorDegreeNode = $3;
   else yyerror("bPriorDegreeNode should be 0 or 1"); }

 | bPriorEdgeCount_id '=' expr {
   bPriorEdgeCount = TRUE;
   expected_n_edges = $3; }

 | gamma_degree_id '=' expr { gamma_degree = $3; }

 | bPriorMotif_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bPriorMotif = $3;
   else yyerror("bPriorMotif should be 0 or 1"); }

 | alpha_motif_id '=' expr { alpha_motif = $3; }
 | beta_motif_id  '=' expr { beta_motif  = $3; }

 | bPriorSCC_id '=' expr {
   if (($3 == 0) || ($3 == 1)) bPriorSCC = $3;
   else yyerror("bPriorSCC should be 0 or 1"); }

 | gamma_scc_id  '=' expr { gamma_scc  = $3; }
 | lambda_scc_id '=' expr { lambda_scc = $3; }

 | nData_id '=' expr { nData = $3; }

;

end: end_id {
  // printf("Reach end of input file.\n\n");
  /* check that each defined variable is used */
  /* for (i = 0; i < MAXNUSERVAR; i++) */
  /*   if (is_defined[i] && !is_used[i]) */
  //    lexerr("some user-defined variables are not used");
  return (0);
 }
;

matrix_declaration: /* syntax: matrix{list} */

 initial_adjacency_id '=' MATRIX L_CBRACE list R_CBRACE {

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

 | initial_adjacency_id '=' MATRIX L_CBRACE EMPTY R_CBRACE { /* empty graph */
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

 | initial_adjacency_id '=' MATRIX L_CBRACE FULL R_CBRACE { /* full graph */
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

 | initial_adjacency_id '=' MATRIX L_CBRACE RANDOM R_CBRACE {
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

 | edge_requirements_id '=' MATRIX L_CBRACE list R_CBRACE {
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
 } /* end edge_requirements */

 | hyper_pB_id '=' MATRIX L_CBRACE list R_CBRACE {
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
 } /* end hyper_pB */

 | hyper_pB_id '=' MATRIX L_CBRACE EQUANIMOUS R_CBRACE {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* do nothing: scale_pB defaults to 1 and equanimous is the default and
      will be initialized in InitArrays */

 } /* end hyper_pB equanimous */

 | hyper_pB_id '=' expr '*' MATRIX L_CBRACE EQUANIMOUS R_CBRACE {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* init scale_pB and do nothing else because equanimous is the default and
      will be initialized in InitArrays */
   //scale_pB = $3;
 } /* end hyper_pB scalar * equanimous */

 | hyper_pB_id '=' MATRIX L_CBRACE EQUANIMOUS R_CBRACE '*' expr {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* init scale_pB and do nothing else because equanimous is the default and
      will be initialized in InitArrays */
   //scale_pB = $8;
 } /* end hyper_pB equanimous * scalar */

 | hyper_pB_id '=' expr '*' MATRIX L_CBRACE EQUANIMOUS R_CBRACE '*' expr {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (hyper_pB)
    yyerror("hyper_pB redefinition is not allowed");

   /* init scale_pB and do nothing else because equanimous is the default and
      will be initialized in InitArrays */
   //scale_pB = $3 * $10;
 } /* end hyper_pB scalar * equanimous * scalar */

 | hyper_pB_id '=' IMPORT L_CBRACE str R_CBRACE {
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
 } /* end imported hyper_pB */

 | data_id '=' MATRIX L_CBRACE list_w_NA R_CBRACE {
   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (!nData)
    yyerror("n_data must be set before defining data values");

   if (plist->lSize != (nNodes * nData)) /* problem */
    yyerror("Data should have n_nodes * n_data elements");

   if (!pData)
    pData = InitdMatrix(nNodes, nData);
   else
    yyerror("Data redefinition is not allowed");

   ple = plist->Head;
   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nData; j++) {
       pData[i][j] = ple->dVal;
       ple = ple->next;
     }
   }
   FreedList(&plist);
 } /* end explicit Data matrix */

 | data_id '=' IMPORT L_CBRACE str R_CBRACE {

   if (!nNodes)
    yyerror("n_nodes must be set before defining matrices");

   if (!nData)
    yyerror("n_data must be set before defining data values");

   if (!pData)
    pData = InitdMatrix(nNodes, nData);
   else
    yyerror("Data redefinition is not allowed");

   pstrle = pstrlist->Head;
   FILE *datafile;
   datafile = fopen(pstrle->cVal, "r");
   if (!datafile)
     yyerror("data file could not be opened");

   for (i = 0; i < nNodes; i++) {
     for (j = 0; j < nData; j++) {
       if (fscanf(datafile, "%lg", &(pData[i][j])) < 1) {
         yyerror("cannot read all data required");
       }
       else {
         if (isnan(pData[i][j]))
           bNAData = TRUE;
       }
     }
   }

   fclose(datafile);

 } /* end imported Data matrix */
;

array_declaration: /* syntax: array{list} */

 chain_file_names_id '=' ARRAY L_CBRACE str_list R_CBRACE {

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

 | nLevels_id '=' ARRAY L_CBRACE list R_CBRACE {

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

 | perk_scale_id '=' ARRAY L_CBRACE list R_CBRACE {

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
;

list:
 expr {
   plist = InitdList();
   QueuedListItem (plist, $1);
 }
 | list ',' expr {
   QueuedListItem (plist, $3);
 }
 | { yyerror("empty list"); }
;

list_w_NA:
 expr {
   plist = InitdList();
   QueuedListItem (plist, $1);
 }
 | NA {
   plist = InitdList();
   QueuedListItem (plist, nan("")); /* C99 IEEE floating point standard */
   bNAData = TRUE;
 }
 | list_w_NA ',' expr {
   QueuedListItem (plist, $3);
 }
 | list_w_NA ',' NA   {
   QueuedListItem (plist, nan("")); /* C99 IEEE floating point standard */
   bNAData = TRUE;
 }
 | { yyerror("empty list"); }
;

str:
 FILENAME {
   pstrlist = InitStrList();
   QueueStrListItem (pstrlist, $1);
 }
 | { yyerror("empty list"); }
;

str_list:
 CHAINFILENAME {
   pstrlist = InitStrList();
   QueueStrListItem (pstrlist, $1);
 }
 | str_list ',' CHAINFILENAME {
   QueueStrListItem (pstrlist, $3);
 }
 | { yyerror("empty list"); }
;

expr:
 INTEGER         { $$ = (int)  $1; }
 | LONG          { $$ = (long) $1; }
 | FLOAT         { $$ = $1; }
 | IDENTIFIER    {
   // printf("$1: %s\n", $1);
   if (!LookupVarList (pvarlist, $1, &($$)))
     yyerror("undefined variable found");
   }
 | expr '+' expr { $$ = $1 + $3; }
 | expr '-' expr { $$ = $1 - $3; }
 | expr '*' expr { $$ = $1 * $3; }
 | expr '/' expr { if ($3 == 0) { yyerror("division by zero"); }
                   else $$ = $1 / (double) $3; }
 | '-' expr %prec UMINUS { $$ = -$2; }
 | L_PARENTHESIS expr R_PARENTHESIS  { $$ = $2; }
;


/* == Epilogue ============================================================= */
%%

void lexerr(const char *message)
{
  fprintf(stderr, "Error: %s - Exiting.\n\n", message);
  exit(0);
}

/* End */
