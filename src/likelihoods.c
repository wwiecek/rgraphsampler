/* likelihoods.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>

   Define various data likelihood functions.
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexerr.h"
#include "matrices.h"
#include "random.h"
#include "likelihoods.h"


/* ----------------------------------------------------------------------------
   Update_parenthood

   Update the parenthood of a child node.
   Inputs:
     parent : the ID # of the parent node
     child: the ID # of the node for which we compute the likelihood
     diff: -1 for deletion, +1 for addition, of the parent-child link

   Beware: this changes globally the number and index of the parents of "child".
   Also: constraints on parenthood size are not checked.
*/
void Update_parenthood (int parent, int child, int diff)
{
  BOOL bFound;
  int  i, iTmp;

  // change parenthood arrays; beware of indices...
  if (diff < 0) {
    // remove parent
    if (parent == index_parents[child][nParents[child]-1]) {
      // last, just decrease the count of parents
      nParents[child] -= 1;
    }
    else {
      /* not last: first exchange with the last parent in index_parents,
         then decrease the count of parents to forget the removed parent.
         Note that this shuffles the order of parents in list */
      bFound = FALSE;
      i = -1;
      do {
        i++;
        bFound = (parent == index_parents[child][i]);
      } while (!bFound);
      iTmp = index_parents[child][i];
      index_parents[child][i] = index_parents[child][nParents[child]-1];
      index_parents[child][nParents[child]-1] = iTmp;
      nParents[child] -= 1;
    }
  }
  else {
    /* add parent at the end of index_parents array */
    index_parents[child][nParents[child]] = parent;
    nParents[child] += 1; /* potential problem if constraints on parenthood
                             size are not checked */
  }

} /* Update_parenthood */


/* ----------------------------------------------------------------------------
   Loglikelihood_diff

   Difference in (integrated) log-likelihood for a node, given a change in
   its parenthood.
   Inputs:
     parent : the ID # of the parent node
     child: the ID # of the node for which we compute the likelihood
     diff: -1 for deletion, +1 for addition, of the parent-child link
     pData : a data structure
   Output:
     logLdiff: a pointer to the difference of the loglikelihood after and
               before change.
*/
void Loglikelihood_diff (int parent, int child, int diff,
                         double **pData, double *logLdiff)
{
  if (bDBN) {
    if (bZellner)
      *logLdiff = ZLoglikelihood_node_DBN (child, pData) -
                  current_ll_node[child];
    else {
      if (bDirichlet)
        *logLdiff = DLoglikelihood_node_DBN (child, pData) -
                    current_ll_node[child];
      else
        *logLdiff = NGLoglikelihood_node_DBN (child, pData) -
                                              current_ll_node[child];
    }
  }
  else { /* BN or hypergraph */
    if (bZellner)
      *logLdiff = ZLoglikelihood_node (child, pData) -
                  current_ll_node[child];
    else {
      if (bDirichlet)
        *logLdiff = DLoglikelihood_node (child, pData) -
                    current_ll_node[child];
      else
        *logLdiff = GLoglikelihood_node (child, pData) -
                                         current_ll_node[child];
    }
  }

} /* Loglikelihood_diff */


/* ----------------------------------------------------------------------------
   Loglikelihood_full

   Full log-likelihood for a given graph (specified by its adjacency matrix).
   The arrays nParents and index_parents are supposed to be meaningfully
   initialized using the starting or current adjacency matrix.
   The likelihood of "Control" nodes, for which bAllowed_parents is FALSE,
   is nor computed (those nodes are jumped over). However, they are still used
   as parents of their children and then take as values the data they have been
   given in the input file.
   Inputs:
     N : number of nodes
     adjacency : a pointer to the adjacency matrix
     pData : a data structure
   The adjacency matrix on which it operates is global and actually not
   used here, but below (in the individual nodes likelihood calculations).

   WW modification uses component object and not the index_loop also
   simplifies a few bits; component, component_size has to be passed
   via a pointer

*/
double Loglikelihood_full (int N, double **pData, int *component,
                           int *component_size)
{
  double cumLL = 0;
  int    i, j;
  int    max_component_visited = 0;
  double tmp_loop_ll;

  /* Diagnostics:

  printf ("LL Component:");
  for (i = 0; i < nNodes; i++) printf("%d ", component[i]);
    printf ("\n");

    printf ("LL Component sizes:");
    for (i = 0; i < nNodes; i++)
      printf ("%d ", component_size[i]);
      printf ("\n");

      printf ("Data matrix:\n");
      PrintdMatrix (stdout, N, pData);
      printf ("\n");
  */

  // sum up the log-likelihoods of each node
  for (i = 0; i < N; i++) {
    if (bAllowed_parents[i]) {

      if (bDBN) {
        if (bZellner)
          current_ll_node[i] = ZLoglikelihood_node_DBN (i, pData);
        else {
          if (bDirichlet)
            current_ll_node[i] = DLoglikelihood_node_DBN (i, pData);
          else
            current_ll_node[i] = NGLoglikelihood_node_DBN (i, pData);
        }
        cumLL += current_ll_node[i];
      }
      else { /* BN or hypergraph */
        if (component_size[i] > 1) { // we are dealing with an hypernode
          if (max_component_visited < component[i]) {
            if (!CGLoglikelihood_hypernode (i, pData, component, &tmp_loop_ll))
              lexerr("hypernode too large in Loglikelihood_full\n");
            cumLL += tmp_loop_ll;
            max_component_visited = component[i];

            // store the likelihood in all relevant loops:
            for (j = i; j < N; j++)
              if (component[j] == component[i])
                current_ll_node[j] = tmp_loop_ll;
          }
        }
        else { // standard BN code
          if (bZellner)
            current_ll_node[i] = ZLoglikelihood_node (i, pData);
          else {
            if (bDirichlet)
              current_ll_node[i] = DLoglikelihood_node (i, pData);
            else
              current_ll_node[i] = GLoglikelihood_node (i, pData);
          }
          cumLL += current_ll_node[i];
        }
      }
    } /* if bAllowed_parents */
  } /* for i */

  // printf ("Loglikelihood = %f\n\n", cumLL);

  return(cumLL);

} /* Loglikelihood_full */


/* ----------------------------------------------------------------------------
   GLoglikelihood_node

   Computes the (integrated) log-likelihood of the data for one node,
   given either a normal-gamma prior and the values of its parents (taken as
   regressors X), or a constant-gamma prior.
   The normal-gamma prior hyperparameter are (see Bernardo's book appendix)
    . mu: mean of regression parameters : all null
    . precision matrix of the regression params joint distribution: 1 * I
    . alpha (shape, named alpha_normal_gamma) of the gamma distribution for
      lambda (precision of measurements)
    . beta (rate, beta_normal_gamma) of the same gamma distribution

   Inputs:
    node: node number
    pData: data array

   Output:
    integrated log-likelihood

   This function essentially
   1/ calculates data precision matrix (Sigma ^ -1 in the paper) and
   2/ passes it to the multivariate T density function (with data, df)

   This is not very clean and the code could be split in two functions:
   CGLoglikelihood_node and NGLoglikelihood_node
*/
double GLoglikelihood_node (int node, double **pData)
{
  int i;
  double ILL; /* integrated log-likelihood, returned */

  if (bHypergraph || bConstantGamma) {
    if (!CGLoglikelihood_hypernode(node, pData, dag_component, &ILL))
      lexerr("hypernode too large in GLoglikelihood_node\n");
    return(ILL);
  }
  /* That's it */

  int j, k;
  double df;

  // the vector mu of prior data expectations is null, so forget it

  // we need the data precision matrix (1 - x inv(x'x + n0) x') alpha / beta
  // see Bernardo, appendix

  // nzero is taken for now to be the identity matrix

  // store t(X) * X + n_zero in pdM1, X being the design matrix
  // X is implicit given the parents of the node considered, otherwise it
  // would have a column of 1 and the data of the parents as other columns.
  // Remember that n_zero is set to the identity matrix

  pdM1[0][0] = 1 + nData; // n_zero element 1 + n * 1

  // 1st line and 1st column of pdM1
  for (j = 0; j < nParents[node]; j++) {
    pdM1[0][j+1] = 0; // set it to n_zero off diagonal element
    for (k = 0; k < nData; k++) {
      pdM1[0][j+1] += pData[index_parents[node][j]][k];
    }
    pdM1[j+1][0] = pdM1[0][j+1];
  }

  // rest of pdM1
  for (i = 0; i < nParents[node]; i++) {
    for (j = i; j < nParents[node]; j++) {
      if (i == j)
        pdM1[i+1][j+1] = 1; // set it to n_zero diagonal element
      else
        pdM1[i+1][j+1] = 0; // set it to n_zero off diagonal element
      for (k = 0; k < nData; k++) {
        pdM1[i+1][j+1] += pData[index_parents[node][i]][k] *
                          pData[index_parents[node][j]][k];
      }
      pdM1[j+1][i+1] = pdM1[i+1][j+1];
    }
  }

  // invert t(X) * X + n_zero, that is: invert pdM1
  if (nParents[node] == 0) {
    pdM1[0][0] = 1 / pdM1[0][0];
  }
  else {
    InvertMatrix_Chol(pdM1, 1+nParents[node]);
  }

  // premultiply by X, store the result in pdM2
  for (i = 0; i < nData; i++) {
    for (j = 0; j < nParents[node]+1; j++) {
      pdM2[i][j] = pdM1[0][j]; // no need to multiply by 1
      for (k = 1; k < nParents[node]+1; k++) {
        pdM2[i][j] += pData[index_parents[node][k-1]][i] *
                      pdM1[k][j];
      }
    }
  }

  /* postmutiply by t(X), subtract from I and multiply by alpha / beta;
     use pdM1 to store the result */
  for (i = 0; i < nData; i++) {
    for (j = i; j < nData; j++) {
      if (i == j) {
        pdM1[i][j] = 1 - pdM2[i][0]; // no need to multiply by 1
      }
      else {
        pdM1[i][j] =   - pdM2[i][0]; // no need to multiply by 1
      }
      for (k = 1; k < nParents[node]+1; k++) {
        pdM1[i][j] -= pdM2[i][k] *
                      pData[index_parents[node][k-1]][j];
      }
      pdM1[i][j] *= alpha_normal_gamma / beta_normal_gamma;
      pdM1[j][i] = pdM1[i][j];
    }
  }

  // degrees of freedom
  df = 2 * alpha_normal_gamma;

  // evaluate the data density
  ILL = LnMultivariateT(pData[node], nData, pdM1, df);

  return(ILL);

} /* GLoglikelihood_node */


/* ----------------------------------------------------------------------------
   CGLoglikelihood_hypernode

   Computes the (integrated) log-likelihood of the data for one hypernode,
   the values of its parents (taken as regressors X), given a constant-gamma
   model.
   Inputs:
   . node: node number
   . pData: data array
   . component: strongly connected component object

   Calculation helpers - who is who:
   pdM1 is matrix Y of data for nodes in loop
   pdM2 is design matrix X

   pdM3 is matrix = t(X)*X
   pdM4 is matrix = inverse of t(X)*X
   pdM5 is matrix = (t(X)*X)^-1 * t(X)
   pdM6 is matrix = MLE of theta parameters
   pdM7 is matrix = Y - X*(theta MLE)

   tpd5 is matrix A0 = t(pdM7)*pdM7 =
                       t(Y - X*(theta MLE))*(Y - X*(theta MLE))

   Output:
   . dILL: pointer to the computed integrated loglikelihood
   . function value: 1 if success, 0 if data number constraint is not fulfilled
*/
int CGLoglikelihood_hypernode (int node, double **pData, int *component,
                               double *dILL)
{
  int i, j, k, num_node, num_parents, df_wishart;
  double sum;

  static int *arrayparents;
  int dim = (nNodes > nData ? nNodes : nData);
  if (!arrayparents){
    arrayparents = InitiVector(nNodes);
  }
  /* search the component array for nodes that are in the same (target) scc
     as the current (child) node */
  num_node = 0;    /* number of nodes in the target scc */
  num_parents = 0; /* number of parents of the target scc */
  for (i = 0; i < nNodes; i++) {
    if (component[i] == component[node]) { /* node i in same scc as node */

      /* if the parents of node i are not in the same scc as node i, add them
         to the list of parents */
      for (k = 0; k < nParents[i]; k++) {
        if (component[index_parents[i][k]] != component[i]) {
	  if (num_parents == 0) {
            arrayparents[num_parents] = index_parents[i][k];
            num_parents++;
	  }
          else { /* parent list non empty */
            for (j = 0; j < num_parents; j++) {
              if (arrayparents[j] == index_parents[i][k]) {
                break; /* already in list */
              }
            }
            if (j == num_parents) { /* not found, add it */
              arrayparents[num_parents] = index_parents[i][k];
              num_parents++;
            }
	  }
        }
      } /* end for k */

      /* updating Y data matrix */
      for (j = 0; j < nData; j++) {
        pdM1[j][num_node] = pData[i][j];
      }

      num_node++;
    }
  }

  /* stop if nParents of scc is >= to nData, this could happen even though
     we are limiting the size of parenthood of every node */
  if (num_parents >= nData)
    return(0);

  /* stop if the SCC size is higher than the maximum allowed  */
  if (num_node > maximum_scc_size)
    return(0);

  /* diagnostics:
  printf ("Computing hypernode likelihood with %d parents and %d nodes \n",
          num_parents, num_node);
  printf ("Component is ");
  for (i = 0; i < nNodes; i++) printf("%d ", component[i]);
  printf ("\n");
  for (i = 0; i < nNodes; i++) printf("%d", nParents[i]);
  printf ("Loop's parent list: \n");
  PrintiList (stdout, parent_list, NULL);
  for (k = num_parents - 1; k >= 0; k--) {
    printf("%d ", arrayparents[k]);
  }
  printf("\n\n"); */

  // design matrix construction
  for (i = 0; i < nData; i++)
    pdM2[i][0] = 1;

  for (k = 0; k < num_parents; k++)
    for (i = 0; i < nData; i++)
      pdM2[i][num_parents-k] = pData[arrayparents[k]][i];

  /* calculate t(X) * X, that is: tX * pdM2 */
  for (i = 0; i <= num_parents; i++) {
    for (j = 0; j <= num_parents; j++) {
      sum = 0;
      for (k = 0; k < nData; k++)
        sum = sum + (pdM2[k][i] * pdM2[k][j]); //pdM2[k][i] because it's transpose of pdM2
      pdM3[i][j] = sum;
      pdM4[i][j] = sum;
    }
  }

  if (num_parents == 0) {
    pdM4[0][0] = 1 / pdM3[0][0];
  }
  else {
    InvertMatrix_Chol(pdM4, 1+num_parents);
  }


  for (i = 0; i <= num_parents; i++) {
    for (j = 0; j < nData; j++) {
      sum = 0;
      for (k = 0; k <= num_parents; k++)
        sum = sum + (pdM4[i][k] * pdM2[j][k]); //pdM2[j][k] because it's transpose of pdM2
      pdM5[i][j] = sum;
    }
  }

  for (i = 0; i <= num_parents; i++) {
    for (j = 0; j < num_node; j++) {
      sum = 0;
      for (k = 0; k < nData; k++)
        sum = sum + pdM5[i][k] * pdM1[k][j];
      pdM6[i][j] = sum;
    }
  }

  // completion of the MLE estimator
  // computation for the (unscaled) sample variance-covariance matrix
  for (i = 0; i < nData; i++) {
    for (j = 0; j < num_node; j++) {
      sum = 0;
      for (k = 0; k <= num_parents; k++)
        sum = sum + pdM2[i][k] * pdM6[k][j];
      pdM7[i][j] = pdM1[i][j] - sum;
    }
  }

  /* sample variance covariance matrix */
  for (i = 0; i < num_node; i++) {
    for (j = 0; j < num_node; j++) {
      sum = 0;
      for (k = 0; k < nData; k++)
        sum = sum + pdM7[k][i] * pdM7[k][j]; //pdM7[k][i] is transpose of pdM7
      tpd5[i][j] = sum;

	  /* add Wishart shape kappa (identity matrix) to sample vcov matrix */
      if (i == j)
        tpd5[i][j] = tpd5[i][j] + scale_wishart_diag;
      else
        tpd5[i][j] = tpd5[i][j] + scale_wishart_offdiag;
    }
  }

  /* degrees of freedom */
  df_wishart = num_node + extra_df_wishart;

  *dILL = LnRatio (pdM3, tpd5, nData, num_node, num_parents+1, df_wishart,
                   scale_wishart_diag, scale_wishart_offdiag, nNodes);

  return(1);

} /* CGLoglikelihood_hypernode */


/* ----------------------------------------------------------------------------
   NGLoglikelihood_node_DBN

   Computes the (integrated) log-likelihood of the data for one node,
   given a normal-gamma prior and the values of its parents (taken as
   regressors X)

   This is the DBN (dynamic BN) version, where the child value at time t
   depends on its parents values at time t-1. So basically the index
   i in Data[node][i] needs to run from 1 to nData and needs to run from
   0 to nData - 1 in Data[index_parents[...]][i].

   The prior hyperparameter are (see Bernardo's book appendix)
    . mean of regression parameters : all null
    . precision matrix of the regression params joint distribution: 1 * I
    . alpha (shape, named alpha_normal_gamma) of the gamma distribution for
      lambda (precision of measurements)
    . beta (rate, beta_normal_gamma) of the same gamma distribution
   Inputs:
    node: node number
    pData: data array
*/
double NGLoglikelihood_node_DBN (int node, double **pData)
{
  int i, j, k;
  // For DBNs there are in fact n-1 data, compute it once
  int nDataM1 = nData - 1;

  double df, LL;


  // the vector mu of prior data expectations is null, so forget it

  // we need the data precision matrix (1 - x inv(x'x + n0) x') alpha / beta
  // see Bernardo, appendix

  // nzero is taken for now to be the identity matrix

  // store t(X) * X + n_zero in pdM1, X being the design matrix
  // X is implicit given the parents of the node considered, otherwise it
  // would have a column of 1 and the data of the parents as other columns.
  // Remember that n_zero is set to the identity matrix
  // Since we are in the DBN case X has only lines from 0 to nData - 1

  pdM1[0][0] = nData; // n_zero element 1 + (n - 1) * 1

  // 1st line and 1st column of pdM1
  for (j = 0; j < nParents[node]; j++) {
    pdM1[0][j+1] = 0; // set it to n_zero off diagonal element
    for (k = 0; k < nDataM1; k++) {
      pdM1[0][j+1] += pData[index_parents[node][j]][k];
    }
    pdM1[j+1][0] = pdM1[0][j+1];
  }

  // rest of pdM1
  for (i = 0; i < nParents[node]; i++) {
    for (j = i; j < nParents[node]; j++) {
      if (i == j)
        pdM1[i+1][j+1] = 1; // set it to n_zero diagonal element
      else
        pdM1[i+1][j+1] = 0;   // set it to n_zero off diagonal element
      for (k = 0; k < nDataM1; k++) {
        pdM1[i+1][j+1] += pData[index_parents[node][i]][k] *
                          pData[index_parents[node][j]][k];
      }
      pdM1[j+1][i+1] = pdM1[i+1][j+1];
    }
  }

  // invert t(X) * X + n_zero, that is: invert pdM1
  if (nParents[node] == 0) {
    pdM1[0][0] = 1 / pdM1[0][0];
  }
  else
    InvertMatrix_Chol(pdM1, 1+nParents[node]);

  // premultiply by X, store the result in pdM2
  for (i = 0; i < nDataM1; i++) {
    for (j = 0; j < nParents[node]+1; j++) {
      pdM2[i][j] = pdM1[0][j]; // no need to multiply by 1
      for (k = 1; k < nParents[node]+1; k++) {
        pdM2[i][j] += pData[index_parents[node][k-1]][i] *
                      pdM1[k][j];
      }
    }
  }

  /* postmutiply by t(X), subtract from I and multiply by alpha / beta;
     use pdM1 to store the result */
  for (i = 0; i < nDataM1; i++) {
    for (j = i; j < nDataM1; j++) {
      if (i == j) {
        pdM1[i][j] = 1 - pdM2[i][0]; // no need to multiply by 1
      }
      else {
        pdM1[i][j] =   - pdM2[i][0]; // no need to multiply by 1
      }
      for (k = 1; k < nParents[node]+1; k++) {
        pdM1[i][j] -= pdM2[i][k] *
                      pData[index_parents[node][k-1]][j];
      }
      pdM1[i][j] *= alpha_normal_gamma / beta_normal_gamma;
      pdM1[j][i] = pdM1[i][j];
    }
  }

  // degrees of freedom
  df = 2 * alpha_normal_gamma;

  // evaluate the data density, data run from index 1 to nData
  LL = LnMultivariateT(pData[node]+1, nDataM1, pdM1, df);

  return(LL);

} /* NGLoglikelihood_node_DBN */



/* ----------------------------------------------------------------------------
   This is the famous heapsort
*/
void sort(long n, double *vect)
{
  int i, j, k, l;
  double temp;

  k = (n >> 1) + 1;
  l = n;
  for (;;) {
    if (k > 1)
      temp = vect[--k - 1];
    else {
      temp = vect[l-1];
      vect[l-1] = vect[0];
      if (--l == 0) {
        vect[0] = temp;
        return;
      }
    }
    i = k;
    j = k << 1;
    while (j <= l) {
      if (j < l && vect[j-1] < vect[j]) ++j;
      if (temp < vect[j-1]) {
        vect[i-1] = vect[j-1];
        j += (i = j);
      }
      else j = l+1;
    }
    vect[i-1] = temp;
  }
} /* sort */


/* ----------------------------------------------------------------------------
   DLoglikelihood_node

   Computes the (integrated) log-likelihood of the data for one node,
   given a Dirichlet prior and multinomial data.

   Inputs:
    node: node number
    pData: data array, with levels coded 0, 1, ...

   For a good explanation see:
   - Laskey and Myers, 2003, Machine Learning, 50:175-196.
   For some more detail see:
   - Heckerman et al., 1994, in Proceedings of Tenth Conference on Uncertainty
     in Artificial Intelligence, Seattle, WA, p. 293-301. Morgan Kanfmann.
   - Heckerman et al., 1995, Machine Learning, 20, 197-243
*/
double DLoglikelihood_node (int node, double **pData)
{
  int    i, j, nConfigs;

  double LL, N_prime_ij, N_prime_ijk;

  static int    *piCardConfig      = NULL;
  static double *pdCodesP          = NULL;
  static double *pdCodesPE         = NULL;
  static double *pdCumConfigNumber = NULL;
  static double *pdIndexConfig     = NULL;

  if (!pdCodesPE) {
    pdCodesP          = InitdVector(nData);
    pdCodesPE         = InitdVector(nData);
    pdIndexConfig     = InitdVector(nData);
    piCardConfig      = InitiVector(nData);
    pdCumConfigNumber = InitdVector(nNodes);
  }

  // Dirichlet prior sample size of any given configuration of parents values.
  // case no parents or uniform:
  N_prime_ijk = 1.0;

  // another possibility, if there are parents, is to set N_prime_ijk at
  // 1 / number of configurations of parents = 1 / prod_(pDataLevels[parents]).
  // That should penalize higher number of parents
#ifdef NDEF
  for (i = 0; i < nParents[node]; i++)
    N_prime_ijk /= (double) pDataLevels[index_parents[node][i]];
    // in any case, that calculation can be omitted if pdCumConfigNumber
    // is assigned to one, below
#endif

  // marginal prior sample size on node: pDataLevels[node] * N_prime_ijk.
  // the actual detailed calculation is the sum from 1 to pDataLevels[node]
  // of the prior sample sizes for each configuration of parents
  N_prime_ij = N_prime_ijk * pDataLevels[node];

  // cumulated products of levels for configurations encoding
  pdCumConfigNumber[0] = pDataLevels[node];
  for (i = 0; i < nParents[node]; i++)
    pdCumConfigNumber[i+1] = pdCumConfigNumber[i] *
                             pDataLevels[index_parents[node][i]];

  // encoding of node and parents configurations:
  for (i = 0; i < nData; i++) {
    pdCodesPE[i] = pData[node][i];
    for (j = 0; j < nParents[node]; j++)
      pdCodesPE[i] += pData[index_parents[node][j]][i] * pdCumConfigNumber[j];
  }

  // form the codes of just the parents configurations to form the marginals
  // do this before sorting pdCodesPE!
  // sort the parents configurations if needed
  if (nParents[node] > 0) {
    for (i = 0; i < nData; i++)
      pdCodesP[i] = pdCodesPE[i] - pData[node][i];
    sort(nData, pdCodesP);
  }

  // sort the various node and parents configurations
  sort(nData, pdCodesPE);

  // count (tabulate) the nConfigs unique node and parents configurations
  j = 0;
  pdIndexConfig[j] = pdCodesPE[0];
  piCardConfig[j] = 1;
  for (i = 1; i < nData; i++) {
    if (pdCodesPE[i] == pdIndexConfig[j])
      piCardConfig[j]++;
    else {
      j++;
      pdIndexConfig[j] = pdCodesPE[i];
      piCardConfig[j] = 1;
    }
  }
  nConfigs = j + 1;

  LL = 0;

  // term for updated counts
  for (i = 0; i < nConfigs; i++)
    LL += LnGamma(N_prime_ijk + piCardConfig[i]);

  // term for prior, saving time if LnGamma is zero
  if ((N_prime_ijk != 1) && (N_prime_ijk != 2))
    LL -= nConfigs * LnGamma(N_prime_ijk);

  // now deal with the marginal terms:
  // count (tabulate) the nConfigs unique parents configurations
  if (nParents[node] == 0) {
    piCardConfig[0] = nData;
    nConfigs = 1;
  }
  else {
    j = 0;
    pdIndexConfig[j] = pdCodesP[0];
    piCardConfig[j] = 1;
    for (i = 1; i < nData; i++) {
      if (pdCodesP[i] == pdIndexConfig[j])
        piCardConfig[j]++;
      else {
        j++;
        pdIndexConfig[j] = pdCodesP[i];
        piCardConfig[j] = 1;
      }
    }
    nConfigs = j + 1;
  }

  // term for updated marginal counts
  for (i = 0; i < nConfigs; i++)
    LL -= LnGamma(N_prime_ij + piCardConfig[i]);

  // term for marginal prior, saving time if LnGamma is zero
  if ((N_prime_ij != 1) && (N_prime_ij != 2))
    LL += nConfigs * LnGamma(N_prime_ij);

  return(LL);

} /* DLoglikelihood_node */


/* ----------------------------------------------------------------------------
   DLoglikelihood_node_DBN

   Computes the (integrated) log-likelihood of the data for one node,
   given a Dirichlet prior and multinomial data.

   Inputs:
    node: node number
    pData: data array, with levels coded 0, 1, ...

   This is the DBN (dynamic BN) version, where the child value at time t
   depends on its parents values at time t-1. So basically the index
   i in Data[node][i] needs to run from 1 to nData and needs to run from
   0 to nData - 1 in Data[index_parents[...]][i].

   For a good explanation see:
   - Laskey and Myers, 2003, Machine Learning, 50:175-196.
   For some more detail see:
   - Heckerman et al., 1994, in Proceedings of Tenth Conference on Uncertainty
     in Artificial Intelligence, Seattle, WA, p. 293-301. Morgan Kanfmann.
   - Heckerman et al., 1995, Machine Learning, 20, 197-243
*/
double DLoglikelihood_node_DBN (int node, double **pData)
{
  int    i, j, nConfigs;

  double LL, N_prime_ij, N_prime_ijk;

  static int    *piCardConfig      = NULL;
  static double *pdCodesP          = NULL;
  static double *pdCodesPE         = NULL;
  static double *pdCumConfigNumber = NULL;
  static double *pdIndexConfig     = NULL;
  int     nDataM1;

  if (!pdCodesPE) {
    pdCodesP          = InitdVector(nData);
    pdCodesPE         = InitdVector(nData);
    pdIndexConfig     = InitdVector(nData);
    piCardConfig      = InitiVector(nData);
    pdCumConfigNumber = InitdVector(nNodes);

    // For DBNs there are in fact n-1 data, compute it once
    nDataM1 = nData - 1;
  }

  // Dirichlet prior sample size of any given configuration of parents values.
  // case no parents or uniform:
  N_prime_ijk = 1.0;

  // another possibility, if there are parents, is to set N_prime_ijk at
  // 1 / number of configurations of parents = 1 / prod_(pDataLevels[parents]).
  // That should penalize higher number of parents
#ifdef NDEF
  for (i = 0; i < nParents[node]; i++)
    N_prime_ijk /= (double) pDataLevels[index_parents[node][i]];
    // in any case, that calculation can be omitted if pdCumConfigNumber
    // is assigned to one, below
#endif
// if that part of code is enabled you should also enable the one below

  // marginal prior sample size on node: pDataLevels[node] * N_prime_ijk.
  // the actual detailed calculation is the sum from 1 to pDataLevels[node]
  // of the prior sample sizes for each configuration of parents
  N_prime_ij = N_prime_ijk * pDataLevels[node];

  // cumulated products of levels for configurations encoding
  pdCumConfigNumber[0] = pDataLevels[node];
  for (i = 0; i < nParents[node]; i++)
    pdCumConfigNumber[i+1] = pdCumConfigNumber[i] *
                             pDataLevels[index_parents[node][i]];

  // encoding of node and parents configurations:
  for (i = 0; i < nDataM1; i++) {
    pdCodesPE[i] = pData[node][i+1];
    for (j = 0; j < nParents[node]; j++)
      pdCodesPE[i] += pData[index_parents[node][j]][i] * pdCumConfigNumber[j];
  }

  // form the codes of just the parents configurations to form the marginals
  // do this before sorting pdCodesPE!
  // sort the parents configurations if needed
  if (nParents[node] > 0) {
    for (i = 0; i < nDataM1; i++)
      pdCodesP[i] = pdCodesPE[i] - pData[node][i+1];
    sort(nDataM1, pdCodesP);
  }

  // sort the various node and parents configurations
  sort(nDataM1, pdCodesPE);

  // count (tabulate) the nConfigs unique node and parents configurations
  j = 0;
  pdIndexConfig[j] = pdCodesPE[0];
  piCardConfig[j] = 1;
  for (i = 1; i < nDataM1; i++) {
    if (pdCodesPE[i] == pdIndexConfig[j])
      piCardConfig[j]++;
    else {
      j++;
      pdIndexConfig[j] = pdCodesPE[i];
      piCardConfig[j] = 1;
    }
  }
  nConfigs = j + 1;

  LL = 0;

  // term for updated counts
  for (i = 0; i < nConfigs; i++)
    LL += LnGamma(N_prime_ijk + piCardConfig[i]);

#ifdef NDEF
  // term for prior, saving time if LnGamma is zero
  if ((N_prime_ijk != 1) && (N_prime_ijk != 2))
    LL -= nConfigs * LnGamma(N_prime_ijk);
#endif

  // now deal with the marginal terms:
  // count (tabulate) the nConfigs unique parents configurations
  if (nParents[node] == 0) {
    piCardConfig[0] = nDataM1;
    nConfigs = 1;
  }
  else {
    j = 0;
    pdIndexConfig[j] = pdCodesP[0];
    piCardConfig[j] = 1;
    for (i = 1; i < nDataM1; i++) {
      if (pdCodesP[i] == pdIndexConfig[j])
        piCardConfig[j]++;
      else {
        j++;
        pdIndexConfig[j] = pdCodesP[i];
        piCardConfig[j] = 1;
      }
    }
    nConfigs = j + 1;
  }

  // term for updated marginal counts
  for (i = 0; i < nConfigs; i++)
    LL -= LnGamma(N_prime_ij + piCardConfig[i]);

  // term for marginal prior, saving time if LnGamma is zero
  if ((N_prime_ij != 1) && (N_prime_ij != 2))
    LL += nConfigs * LnGamma(N_prime_ij);

  return(LL);

} /* DLoglikelihood_node_DBN */


/* ----------------------------------------------------------------------------
   ZLoglikelihood_node

   Computes the (integrated) log-likelihood of the data vector Y for one node,
   given a Zellner prior and the values of its parents (taken as
   regressors X) The Zellner prior is improper and cannot be computed
   if there is the same number of or more parents than data points for
   the node considered.

   Inputs:
    node: node number
    pData: global data array, will be sliced to form Y and X

   Computation proceeds by forming
   mx = Y' * Y - g_z/(g_z + 1) * (Y' * X) * inv((X' * X)) * (X' * Y)
   where g_z is a tuning parameter
   and then
   Loglikelihood = -(eta + 1)/2 * log(g_z + 1) - n/2 * log(mx)

   were Y is the data for the node considered and X the design matrix
   (a column of 1 for the constant term and a column of data for each parent,
   the data of the parents being taken as regressors), n is the number of data
   points for node, eta is the number of parents of the node considered.

   see Celeux, Marin, Robert, 2006,
       Selection bayesienne de variables en regression lineaire,
       Journal de la Societe Francaise de Statistique, 147:59-79 (p 63 & 68)
   and Smith & Kohn, 1996,
       Nonparametric Regression using Bayesian Variable Selection,
       Journal of Econometrics 75:317–343.
*/
double ZLoglikelihood_node (int node, double **pData)
{
  int i, j, k;
  static double *pdV1  = NULL;
  static double *pdV2  = NULL;
  double mx;
  double LL;

  if (!pdV1) {
    int dim = (nNodes > nData ? nData : nNodes); /* the smallest */
    pdV1 = InitdVector(dim);
    pdV2 = InitdVector(dim);
  }

  /* start with mx = Y' * Y */
  mx = 0;
  for (i = 0; i < nData; i++) {
    mx += pData[node][i] * pData[node][i];
  }

  /* compute Y' * X */

  /* all elements of the first column of X are at 1 */
  pdV1[0] = pData[node][0];
  for (i = 1; i < nData; i++) {
    pdV1[0] += pData[node][i];
  }
  for (j = 0; j < nParents[node]; j++) {
    pdV1[j+1] = pData[node][0] * pData[index_parents[node][j]][0];
    for (i = 1; i < nData; i++) {
      pdV1[j+1] += pData[node][i] * pData[index_parents[node][j]][i];
    }
  }

  /* compute X' * X, take advantage of symmetry of the result */

  pdM1[0][0] = nData; /* n * 1 */

  for (j = 0; j < nParents[node]; j++) { /* take care of the t(X) * X line */
    pdM1[0][j+1] = 0;
    for (k = 0; k < nData; k++) {
      pdM1[0][j+1] += pData[index_parents[node][j]][k];
    }
    pdM1[j+1][0] = pdM1[0][j+1]; /* by symmetry */
  }

  for (i = 0; i < nParents[node]; i++) {
    for (j = i; j < nParents[node]; j++) {
      pdM1[i+1][j+1] = 0;
      for (k = 0; k < nData; k++) {
        pdM1[i+1][j+1] += pData[index_parents[node][i]][k] *
                          pData[index_parents[node][j]][k];
      }
      pdM1[j+1][i+1] = pdM1[i+1][j+1]; /* by symmetry */
    }
  }

  // invert X' * X, that is: invert pdM1
  if (nParents[node] == 0) {
    pdM1[0][0] = 1 / pdM1[0][0];
  }
  else
    InvertMatrix_Chol(pdM1, 1+nParents[node]);

  // do (Y' * X) * inv((X' * X)), that is pdV1 * pdM1

  for (j = 0; j <= nParents[node]; j++) {
    pdV2[j] = pdV1[0] * pdM1[0][j];
    for (i = 1; i <= nParents[node]; i++) {
      pdV2[j] += pdV1[i] * pdM1[j][i];
    }
  }

  // do (Y' * X) * inv((X' * X)) * (X' * Y), that is pdV2 * t(pdV1)

  pdV2[0] = pdV2[0] * pdV1[0];
  for (i = 1; i <= nParents[node]; i++) {
    pdV2[0] += pdV2[i] * pdV1[i];
  }

  // finish mx as mx + pdV2 * t(pdV1)
  mx = mx - gamma_zellner / (gamma_zellner + 1) * pdV2[0];

  LL = -0.5 * ((nParents[node] + 1) * log(gamma_zellner + 1) +
               (nData * log(mx)));

  return(LL);

} /* ZLoglikelihood_node */


/* ----------------------------------------------------------------------------
   ZLoglikelihood_node_DBN

   Computes the (integrated) log-likelihood of the data for one node,
   given a Zellner prior and the values of its parents (taken as
   regressors X) The Zellner prior is improper and cannot be computed
   if there is the same number of or more parents than data points for
   the node considered.

   Inputs:
    node: node number
    pData: data array

   This is the DBN (dynamic BN) version, where the child value at time t
   depends on its parents values at time t-1. So basically the index
   i in Data[node][i] needs to run from 1 to nData and needs to run from
   0 to nData - 1 in Data[index_parents[...]][i].

   Computation proceeds by forming
   mx = Y' * Y - g_z/(g_z + 1) * (Y' * X) * inv((X' * X)) * (X' * Y)
   where g_z is a tuning parameter
   and then
   Loglikelihood = -(eta + 1)/2 * log(g_z + 1) - n/2 * log(mx)

   see Celeux, Marin, Robert, 2006,
       Selection bayesienne de variables en regression lineaire,
       Journal de la Societe Francaise de Statistique, 147:59-79 (p 63 & 68)
   and Smith & Kohn, 1996,
       Nonparametric Regression using Bayesian Variable Selection,
       Journal of Econometrics 75:317–343.

   were Y are the data for the node considered and X the design matrix
   (a column of 1 for the constant term and a column of data for each parent,
   the data of the parents being taken as regressors), n is the number of data
   points for node, eta is the number of parents of the node considered.
*/
double ZLoglikelihood_node_DBN (int node, double **pData)
{
  int i, j, k;
  static double *pdV1  = NULL;
  static double *pdV2  = NULL;
  int nDataM1;
  double mx, LL;

  if (!pdV1) {
    int dim = (nNodes + 1 > nData ? nData : nNodes + 1); // the smallest
    pdV1 = InitdVector(dim);
    pdV2 = InitdVector(dim);

    // For DBNs there are in fact n-1 data, compute it once
    nDataM1 = nData - 1;
  }

  // start with mx = Y' * Y
  mx = 0;
  for (i = 1; i < nData; i++) { // shifted for DBN
    mx += pow(pData[node][i], 2);
  }

  // do Y' * X

  // all elements of the first column of X are at 1, watch the DBN shift
  pdV1[0] = pData[node][1]; // shift down
  for (i = 2; i < nData; i++) {
    pdV1[0] += pData[node][i];
  }
  for (j = 0; j < nParents[node]; j++) { // unmatching indices for DBN
    pdV1[j+1] = pData[node][1] * pData[index_parents[node][j]][0];
    for (i = 2; i < nData; i++) {
      pdV1[j+1] += pData[node][i] * pData[index_parents[node][j]][i-1];
    }
  }

  // do X' * X

  pdM1[0][0] = nDataM1; // (n - 1) * 1

  for (j = 0; j < nParents[node]; j++) { // take care of the line of t(X) * X
    pdM1[0][j+1] = 0;
    for (k = 0; k < nDataM1; k++) {
      pdM1[0][j+1] += pData[index_parents[node][j]][k];
    }
    pdM1[j+1][0] = pdM1[0][j+1];
  }

  for (i = 0; i < nParents[node]; i++) {
    for (j = i; j < nParents[node]; j++) {
      pdM1[i+1][j+1] = 0;
      for (k = 0; k < nDataM1; k++) {
        pdM1[i+1][j+1] += pData[index_parents[node][i]][k] *
                          pData[index_parents[node][j]][k];
      }
      pdM1[j+1][i+1] = pdM1[i+1][j+1];
    }
  }

  // invert X' * X, that is: invert pdM1
  if (nParents[node] == 0) {
    pdM1[0][0] = 1 / pdM1[0][0];
  }
  else
    InvertMatrix_Chol(pdM1, 1+nParents[node]);

  // do (Y' * X) * inv((X' * X)), that is pdV1 * pdM1

  for (j = 0; j <= nParents[node]; j++) {
    pdV2[j] = pdV1[0] * pdM1[0][j];
    for (i = 1; i <= nParents[node]; i++) {
      pdV2[j] += pdV1[i] * pdM1[j][i];
    }
  }

  // do (Y' * X) * inv((X' * X)) * (X' * Y), that is pdV2 * t(pdV1)

  pdV2[0] = pdV2[0] * pdV1[0];
  for (i = 1; i <= nParents[node]; i++) {
    pdV2[0] += pdV2[i] * pdV1[i];
  }

  // finish mx as mx + pdV2 * t(pdV1) just computed and stored in pdV2
  mx = mx - gamma_zellner / (gamma_zellner + 1) * pdV2[0];

  // specific to DBN: one less data point
  LL = -0.5 * ((nParents[node] + 1) * log(gamma_zellner + 1) +
               (nDataM1 * log(mx)));

  return(LL);

} /* ZLoglikelihood_node_DBN */


/* end */
