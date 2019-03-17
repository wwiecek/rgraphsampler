/* graph_sampler lexical parser

   Written by Frederic Bois
   22 June 2014

   Copyright (c) 2014 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   For more details
   see the GNU General Public License at <http://www.gnu.org/licenses/>
*/

/* Prologue */
%option yylineno
%{
#include <stdlib.h>
#include <limits.h>
#include "y.tab.h"
void   yyerror(const char *message);
int    lineno = 1;
double dTmp;
%}

DIGIT    [0-9]
ID       [A-Za-z][A-Za-z0-9_]*
CFNAME   \"[^"\n]*\.((bin)|(out))["\n]
FNAME    \"[^"\n]*\.dat["\n]
COMMENT  #.*
LCB      \{
RCB      \}
LPAR     \(
RPAR     \)

/* Rules */
%%

                             /* scalars */

alpha_motif                  { return alpha_motif_id; }

alpha_normal_gamma           { return alpha_normal_gamma_id; }

autocycle                    { return autocycle_id; }

bayesian_network             { return bBN_id; }

beta_motif                   { return beta_motif_id; }

beta_normal_gamma            { return beta_normal_gamma_id; }

concordance_prior            { return bPriorConcordance_id; }

convergence_check            { return bConvergence_check_id; }

data                         { return data_id; }

degree_prior                 { return bPriorDegreeNode_id; }

edge_count_prior             { return bPriorEdgeCount_id; }

edge_requirements            { return edge_requirements_id; }

end_at_iter                  { return end_at_iter_id; }

extra_df_wishart             { return extra_df_wishart_id; }

dynamic_bayesian_network     { return bDBN_id; }

file_names                   { return chain_file_names_id; }

gamma_degree                 { return gamma_degree_id; }

gamma_scc                    { return gamma_scc_id; }

gamma_zellner                { return gamma_zellner_id; }

hyper_pB                     { return hyper_pB_id; }

hypergraph                   { return bHypergraph_id; }

initial_adjacency            { return initial_adjacency_id; }

lambda_concordance           { return lambda_concord_id; }

lambda_scc                   { return lambda_scc_id; }

likelihood                   { return likelihood_id; }

maximum_scc_size             { return maximum_scc_size_id; }

motif_prior                  { return bPriorMotif_id; }

n_burn_in                    { return nBurnin_id; }

n_data                       { return nData_id; }

n_data_levels                { return nLevels_id; }

n_nodes                      { return nNodes_id; }

n_runs                       { return nRuns_id; }

n_saved_adjacency            { return n_saved_adjacency_id; }

perk_scale                   { return perk_scale_id; }

random_generator             { return rdm_generator_id; }

random_seed                  { return seed_id; }

save_best_graph              { return bsave_best_graph_id; }

save_degree_counts           { return bsave_the_degree_counts_id; }

save_edge_probabilies        { return bsave_the_edge_probabilities_id; }

save_motifs_probabilies      { return bsave_the_motifs_probabilities_id; }

save_chain                   { return bsave_the_chain_id; }

scale_wishart_diagonal       { return scale_wishart_diag_id; }

scale_wishart_offdiagonal    { return scale_wishart_offdiag_id; }

scc_prior                    { return bPriorSCC_id; }

start_at_iter                { return start_at_iter_id; }


                             /* keywords */

NA                           { return NA; }
NaN                          { return NA; }
array                        { return ARRAY; }
constant_gamma               { return CONSTANTGAMMA; }
dirichlet                    { return DIRICHLET; }
empty                        { return EMPTY; }
equanimous                   { return EQUANIMOUS; }
import_file                  { return IMPORT; }
incremental_w_chain          { return INCREMENTAL; }
full                         { return FULL; }
matrix                       { return MATRIX; }
mersenne_twister             { return MT19937; }
normal_gamma                 { return NORMALGAMMA; }
random                       { return RANDOM; }
standard_w_chain             { return STANDARD_CHAIN; }
standard_w_edgeP             { return STANDARD_EDGEP; }
tausworthe                   { return TAUS2; }
zellner                      { return ZELLNER; }

true|True|TRUE               { yylval.ival = 1; return INTEGER; }

false|False|FALSE            { yylval.ival = 0; return INTEGER; }


{DIGIT}+  { dTmp = atof(yytext);
            if (dTmp > INT_MAX) {
              if (dTmp > LONG_MAX) {
                yyerror("number too large");
              }
              else {
                yylval.lval = (long) dTmp;
                return LONG;
              }
            }
            else {
              yylval.ival = (int) dTmp;
              return INTEGER;
            }
          }

[0-9]+"."[0-9]* |
      "."[0-9]* |
         [0-9]+[eE][+-]?[0-9]+ |
[0-9]+"."[0-9]*[eE][+-]?[0-9]+ |
      "."[0-9]*[eE][+-]?[0-9]+ { yylval.dval = atof(yytext); return FLOAT; }

<<EOF>>   { // put dummy stuff here (to avoid stupid compiler warnings)
            input(); yyunput(0, "a");
            // instruct to get out
            return end_id; }

^[\n]     { lineno++; } /* skip but count */

[\n]      { lineno++; } /* skip but count */

[-+=*/\;] { return *yytext; }

{LCB}     { return L_CBRACE; }

{RCB}     { return R_CBRACE; }

{LPAR}    { return L_PARENTHESIS; }

{RPAR}    { return R_PARENTHESIS; }

[ \t\r]+  { ; } /* skip whitespace, including carriage return */

{COMMENT} { ; } /* skip comments */

{ID}      { yylval.pchar = yytext;
            // printf("Temporary variable \"%s\"\n\n", yytext);
            return IDENTIFIER; }

{CFNAME}  { yylval.pchar = yytext;
            // printf("Chain file name \"%s\"\n\n", yytext);
            return CHAINFILENAME; }

{FNAME}   { yylval.pchar = yytext;
            // printf("File name \"%s\"\n\n", yytext);
            return FILENAME; }

.         { return *yytext; } /* let yacc take care of the junk */

%% /* Epilogue */

int yywrap(void) {
  return 1;
}

/* ----------------------------------------------------------------------------
   yyerror
*/
void yyerror(const char *message) {
  fprintf(stderr, "Error, line %d: %s near '%s' - Exiting.\n\n",
          lineno, message, yytext);
  exit(0);
}

/* End. */
