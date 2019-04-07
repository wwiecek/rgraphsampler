/* likelihoods.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>
*/

#ifndef LIKELIHOODS_H_DEFINED


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include "hypernode.h"


/* ----------------------------------------------------------------------------
   Type definitions
*/

#ifndef TRUE
typedef int BOOL;
#define TRUE  1
#define FALSE 0
#endif


/* ----------------------------------------------------------------------------
   Prototypes
*/

void   Loglikelihood_diff (int parent, int child, int diff,
                           double **pData, double *logLdiff);
double Loglikelihood_full (int N, double **pData, int *component,
                           int *component_size);

int CGLoglikelihood_hypernode (int node, double **pData, int *component,
                               double *dILL);

double DLoglikelihood_node         (int node, double **pData);
double DLoglikelihood_node_DBN     (int node, double **pData);

double GLoglikelihood_node         (int node, double **pData);

double NGLoglikelihood_node_DBN    (int node, double **pData);

double ZLoglikelihood_node         (int node, double **pData);
double ZLoglikelihood_node_DBN     (int node, double **pData);

void   Update_parenthood           (int parent, int child, int diff);

void sort(long n, double *vect);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals, to be defined elsewhere

extern BOOL   bBN;                   // sample Bayesian networks
extern BOOL   bDBN;                  // sample dynamic Bayesian networks
extern BOOL   bHypergraph;           // sample hypergraphs
extern int    nNodes;                // the number of nodes in graph
extern int    *nParents;             // number of parents for each node
extern int    **index_parents;       // list of current parents for each node
extern BOOL   *bAllowed_parents;     // are parents allowed for each node? y/n
extern double *current_ll_node;      // likelihoods for each node
extern BOOL   bConstantGamma;        // Constant(improper)-Gamma score on/off
extern BOOL   bNormalGamma;          // Normal-Gamma score on/off
extern BOOL   bDirichlet;            // Dirichlet score on/off
extern BOOL   bZellner;              // Zellner score on/off
extern double alpha_normal_gamma;    // prior Gamma shape for data precision
extern double beta_normal_gamma;     // prior Gamma rate for data precision
extern double gamma_zellner;         // tuning parameter for Zellner score
extern double extra_df_wishart;      // extra prior Wishart degrees of freedom
extern double scale_wishart_diag;    // value of diag elems of Wishart scale
extern double scale_wishart_offdiag; // value of off-diag elems of Wishart scale
extern int    maximum_scc_size;

extern int    nData;               // max number of data points per node
extern int    *pDataLevels;        // number of codes per node for discrete data
extern BOOL   bNAData;             // flag for missing data in data matrix

extern int    *dag_component;      // blueprint for SCC of DAG

// matrices for calculations, pre-allocated in graph_sampler.c:
extern double **pdM1;
extern double **pdM2;
extern double **pdM3;
extern double **pdM4;
extern double **pdM5;
extern double **pdM6;
extern double **pdM7;
extern double **tpd5;

/* End */

#define LIKELIHOODS_H_DEFINED
#endif  /* LIKELIHOODS_H_DEFINED */

