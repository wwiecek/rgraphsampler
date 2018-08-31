/* graph_sampler.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>
*/

#ifndef GS_H_DEFINED


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #ifndef NO_LIBGSL
// #include <gsl/gsl_matrix.h>
// #include <gsl/gsl_linalg.h>
// #include <gsl/gsl_cblas.h>
// #endif

#include "concordance.h"
#include "convergence.h"
#include "degree.h"
#include "edge_number.h"
#include "lexerr.h"
#include "likelihoods.h"
#include "lists.h"
#include "matrices.h"
#include "motifs.h"
#include "outputs.h"
#include "random.h"
#include "hypernode.h"
#include "topo_sort.h"
#include "y.tab.h"


/* ----------------------------------------------------------------------------
   Macros
*/

#define Readln(_pf) ((fscanf (_pf, "%*[^\n]") < 0) ? -1: fgetc(_pf))


/* ----------------------------------------------------------------------------
   Prototypes
*/
void   AnnounceProgram (void);

void   CleanupMemory (void);

double DLoglikelihood_node (int node, double **pData);

double DLoglikelihood_node_NA (int node, double **pData);

double DLoglikelihood_node_DBN (int node, double **pData);

double DLoglikelihood_node_DBN_NA (int node, double **pData);

void   GetCmdLineArgs (int cArg, char *const *rgszArg, char **pszFileIn,
                       char **pszPrefixOut);

double GLoglikelihood_node (int node, double **pData);

double GLoglikelihood_node_NA (int node, double **pData);

double GLoglikelihood_node_DBN (int node, double **pData);

double GLoglikelihood_node_DBN_NA (int node, double **pData);

void   InitArrays (void);

void   Loglikelihood_diff (int parent, int child, int diff,
                           double **pData, double *logLdiff);
double Loglikelihood_full (int N, double **pData, int *component,
                           int *component_size);
void   Logprior_diff (int **adjacency_current,
                      int parent_node, int child_node, int diff,
                      double *logPdiff);
double Logprior_diff_bernoulli (int parent_node, int child_node, int diff);
double Logprior_full (int N, int **adjacency);

void   ReadScript_Bison (char *filename);

void   SampleTemperature (void);

void   SetPriorHyperParam (void);

void   UpdateBestGraph (void);
void   UpdateEdgeP (void);

double ZLoglikelihood_node (int node, double **pData);

double ZLoglikelihood_node_NA (int node, double **pData);

double ZLoglikelihood_node_DBN (int node, double **pData);

double ZLoglikelihood_node_DBN_NA (int node, double **pData);


/* ----------------------------------------------------------------------------
   Global declarations, shared
*/

/* basic flags and variables */
BOOL   bAutocycles;         /* A -> A edges allowed */
BOOL   bBN;                 /* sample Bayesian networks */
BOOL   bDBN;                /* sample dynamic Bayesian networks */
BOOL   bHypergraph;         /* sample hypergraphs */
int    nNodes;              /* the number of nodes in graph */
double seed;                /* random generator seed */
int    bInit;               /* 1 if RNG initialised, 0 until then */
RDM_GEN_NAMES rdm_gen_name; /* if gsl available, random generator type */

/* core computational variables */
int    **current_adj;       /* current adjacency matrix */
int    diff;                /* type of edge change (add, delete) */
int    parent, child;       /* current pair of nodes */
int    *nParents;           /* number of parents for each node */
int    **index_parents;     /* the list of current parents for each node */

/* variables for basic Bernoulli prior */
double **hyper_pB;          /* hyper parameters of the prior pairwise edges */
BOOL   *bAllowed_parents;   /* Boolean: are parents allowed for each node */

/* variables for edge concordance prior */
BOOL   bPriorConcordance;   /* flag for including a concordance prior */
int    **edge_requirements; /* prior edge pattern matrix */
double lambda_concord;      /* exponent for concordance weighting */

/* variables for prior on degree distribution */
BOOL   bPriorDegreeNode;    /* flag for including a power prior on degrees */
double *cumdegree_count;
int    *current_degrees;    /* point to a table of # of edges for each node */
double *degree_count;
double gamma_degree;        /* exponent of the degrees power prior */

/* variables for prior on number of edges */
BOOL   bPriorEdgeCount;     /* flag for a binomial prior on total edge count */
long   current_edge_count;  /* number of edges in the graph */
long   expected_n_edges;
double *pdiff_binom_P;      /* table of P(n=x+1) - P(n=x), see InitArrays */

/* variables for prior on motifs */
BOOL   bPriorMotif;          /* flag for including a prior on defined motifs */
int    alpha_motif;          /* alpha beta-binomial parameter for Eloops P */
int    beta_motif;           /* second beta-binomial parameter */
double cum_nEloops;          /* cumulated number of Endless loops */
double cum_nFloops;          /* cumulated number of Frustrated loops */
long   diff_nEloops;         /* proposed change in E loops count */
long   diff_nFloops;         /* proposed change in F loops count */
double current_motif_prior;  /* density of the motif prior in current graph */
double proposed_motif_prior; /* density of the motif prior in proposed graph */

unsigned long current_nEloops; /* current number of Endless loops */
unsigned long current_nFloops; /* current number of Frustrated loops */

/* variables for prior on strongly connected components (SCCs) */
BOOL   bPriorSCC;            /* flag for including a prior on SCCs */
double lambda_scc;           /* Poisson rate on number of SCCs */
double gamma_scc;            /* exponent of the SCC sizes power prior */
double current_scc_prior;    /* density of the scc prior in current graph */
double proposed_scc_prior;   /* density of the scc prior in proposed graph */

/* variables for priors handling */
double current_logprior;     /* current total prior density */
double dBestPrior;           /* prior of the max posterior graph  */

/* variables for likelihood handling */
double current_loglikelihood;
double dBestLikelihood;      /* likelihood of the max posterior graph */
double *current_ll_node;     /* likelihoods for each node */

/* variables for posterior handling */
double current_logposterior; /* current total posterior density */
double dBestPosterior;       /* maximum graph probability found in a run */
int    **best_adj;           /* maximum probability adjacency matrix sampled */

/* variables for (integrated) likelihoods */
BOOL   bConstantGamma;       /* Constant(improper)-Gamma score on/off */
BOOL   bNormalGamma;         /* Normal-Gamma score on/off */
BOOL   bDirichlet;           /* Dirichlet score on/off */
BOOL   bZellner;             /* Zellner score on/off */
double alpha_normal_gamma;   /* prior Gamma shape for data precision */
double beta_normal_gamma;    /* prior Gamma rate for data precision */
double gamma_zellner;        /* tuning parameter for Zellner score */

/* hypergraph variables */
int    *dag_component;       /* strongly connected component (SCC) DAG */
int    *component;           /* SCCs for current graph */
int    *component_size;      /* size of each SCC */
int    *proposed_component;  /* SCCs for proposed graph */
int    *proposed_component_size;
int    flag_update_loops;     /* flag for updating hypernodes information */
PLISTELEMI plistNodesUpdated; /* list of nodes for which ll will be updated */
double *updated_ll_vector;    /* loglikelihoods for several nodes */
double extra_df_wishart;      /* extra prior Wishart degrees of freedom  */
double scale_wishart_diag;    /* value of the diagonal elems of Wishart scale */
double scale_wishart_offdiag; /* value of the off-diag elems of Wishart scale */
int    maximum_scc_size;      /* maximum size for a SCC */

/* variables for data handling */
BOOL    bData;               /* flag the availability of data */
BOOL    bNAData;             /* flag for missing data in data matrix */
int     nData;               /* max number of data points per node in input */
double  **pData;             /* data structure (a vector of data per node) */
int     *pDataLevels;        /* number of codes per node for discrete data */
PLISTIJ plistMissing;        /* list of missing data locations */
BOOL    *bHasMissing;        /* missing data indicator for each node */

/* variables for tempering */
BOOL   bTempered;            /* flag for using tempering */
int    nTemperatures;        /* number of temperatures considered */
int    indexT;               /* current temperature */
double *pInvTemperatures;    /* array of inverse temperatures */
unsigned long n_at_targetT;  /* count of graphs sampled at target temperature */
double dCZero;               /* pseudo-prior updating parameter */
double dNZero;               /* pseudo-prior updating parameter */

double *plnPi;               /* array of temperatures pseudo-priors */

/* computational helps */
int    edgeP_thin;           /* step size for edge probability calculation */
double **mat_sum;            /* cumulated edges counts over graphs */
double **pdWorkMatrixSizeN;  /* work space */

/* MCMC parameters */
unsigned long nRuns, nBurnin, iter;

/* Convergence checking parameters */
int    bConvergence_std;   /* check convergence on an interval */
BOOL   bConvergence_inc;   /* check convergence at every step */
int    nChains;            /* number of MCMC chains to read */
char   **pChainNames;      /* vector of chain file names */

unsigned long nConvergence_start; /* iter at which to start convergence check */
unsigned long nConvergence_end;   /* iter at which to end convergence check */

#define GS_H_DEFINED
#endif

/* end */
