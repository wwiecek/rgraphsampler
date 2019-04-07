/* graph_sampler.c

   Written by Frederic Bois

   Copyright (c) 2014-2018 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>

   Samples either Bayesian networks or general directed graphs by MCMC,
   given specified priors and a likelihood

   Priors are Bernoulli on edges, power on degree and
   beta-binomial on the proportion of E loops (A -> B -> C -> A) over the
   sum of E loops and F loops (A -> B <- C -> A)

   Note on indices: for a square matrix (N x N) with i indexing lines and
   j indexing columns, i and j starting at zero,
   positions z (starting at zero) corresponding to the first line are given by:
     z = i + j * N
   positions z (starting at zero) corresponding to the first column are:
     z = j + i * N
   given a position z (starting at 0) in the flattened matrix (flattened as
   (column 1, column 2...), the corresponding row i (starting at 0) is:
     i = z % N
   the corresponding column j (starting from zero) is:
     j = z / N ("/" being an integer division)
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include "graph_sampler.h"


/* ----------------------------------------------------------------------------
   Global definitions, private
*/

// stuff for basic Bernoulli prior
double **log_hyper_pB;      // point to prior edge log probability matrix
double **log_hyper_qB;      // point to prior edge 1-log probability matrix

// stuff for priors handling
double diff_logprior = 0;

// stuff for likelihood handling and computations
double diff_loglikelihood = 0;

// stuff for posterior handling
double diff_logposterior = 0;

// default input file name
static char vszFileInDefault[] = "script.txt";


/* ----------------------------------------------------------------------------
   AnnounceProgram

   Print a screen explanation of what we are doing.
*/
void AnnounceProgram (void)
{

  printf("\n");
  printf("***************************************\n");
  printf(">>> This is Graph_sampler version 3 <<<\n");
#ifdef R_FLAG
  printf(">>> -----      R edition      ----- <<<\n");
#endif
  printf("***************************************\n");
  printf("\n");

} /* AnnounceProgram */


/* ----------------------------------------------------------------------------
   CleanupMemory

   Releases (some!) pointers & resets the variables used by parser into their
   original state (e.g. RNG indicator).
*/
void CleanupMemory (void)
{

  //  printf("Attempting memory cleanup\n\n");
  if (current_degrees){
    free (current_degrees);
    current_degrees = NULL;
  }
  if(component){
    free(component);
    component = NULL;
  }
  if(component_size){
    free(component_size);
    component_size = NULL;
  }

  if(proposed_component){
    free(proposed_component);
    proposed_component = NULL;
  }
  if(proposed_component_size){
    free(proposed_component_size);
    proposed_component_size = NULL;
  }

  if(dag_component) {
    free(dag_component);
    dag_component = NULL;
  }

  if (current_ll_node) {
    free (current_ll_node);
    current_ll_node = NULL;
  }
  if(current_adj){
    FreeiMatrix(current_adj, nNodes);
    current_adj = NULL;
  }
  if(edge_requirements){
    FreeiMatrix(edge_requirements, nNodes);
    edge_requirements = NULL;
  }
  if(hyper_pB) {
    FreedMatrix(hyper_pB, nNodes);
    hyper_pB = NULL;
  }
  if(pData) {
    FreedMatrix(pData, nNodes);
    pData = NULL;
  }
  if(pDataLevels) {
    free(pDataLevels);
    pDataLevels = NULL;
  }
  if(bHasMissing) {
    free(bHasMissing);
    bHasMissing=NULL;
  }
  if(mat_sum) {
    FreedMatrix(mat_sum, nNodes);
    mat_sum = NULL;
  }

  //calculation helper matrices:
  int dim = (nNodes > nData ? nNodes : nData);
  if (bDBN)
    dim = dim + 1;
  if(pdWorkMatrixSizeN) {FreedMatrix (pdWorkMatrixSizeN, dim); pdWorkMatrixSizeN = NULL;}
  if(pdM1) { FreedMatrix(pdM1,dim); pdM1 = NULL;}
  if(pdM2) { FreedMatrix(pdM2,dim); pdM2 = NULL;}
  if(pdM3) { FreedMatrix(pdM3,dim); pdM3 = NULL;}
  if(pdM4) { FreedMatrix(pdM4,dim); pdM4 = NULL;}
  if(pdM5) { FreedMatrix(pdM5,dim); pdM5 = NULL;}
  if(pdM6) { FreedMatrix(pdM6,dim); pdM6 = NULL;}
  if(pdM7) { FreedMatrix(pdM7,dim); pdM7 = NULL;}
  if(tpd5) { FreedMatrix(tpd5,dim); tpd5 = NULL;}

  if(nParents){
    free(nParents); nParents = NULL;
  }
  if(index_parents){
    FreeiMatrix(index_parents,nNodes);
    index_parents=NULL;
  }
  if(bAllowed_parents){
    free(bAllowed_parents);
    bAllowed_parents = NULL;
  }
  if(pInvTemperatures) {
    free(pInvTemperatures);
    pInvTemperatures = NULL;
  }
  //we reset the parsed nNodes, just in case
  //something extra is run afterwards
  nNodes = 0;

  //reset RNG
  resetRNG();

  //kill the list for topological sorting
  KillTopoList();

  //set all Boolean flags to 0:
  //we should check if this isn't redundant vs parser set-up
  bData = 0; nData = 0; bNAData = 0;
  bDBN = 0; bBN = 0; bTempered=0;
  bZellner = 0; bDirichlet = 0; bConstantGamma = 0; bNormalGamma = 0;
  bHypergraph = 0; bAutocycles = 0;
  bPriorDegreeNode = 0; bPriorEdgeCount = 0; bPriorMotif = 0;
  bPriorSCC = 0; bPriorConcordance = 0;
  gamma_degree   = 1;
  n_at_targetT = 1;

  //save settings
  bsave_the_chain = FALSE;
  bsave_best_graph               = FALSE;
  bsave_the_edge_probabilities   = FALSE;
  bsave_the_degree_counts        = FALSE;
  bsave_the_motifs_probabilities = FALSE;
  bsave_some_graphs              = FALSE;

  scale_pB       = 1;
  lambda_concord = 1;
  gamma_degree   = 1;
  alpha_motif    = 1;
  beta_motif     = 1;
  lambda_scc     = 1;
  gamma_scc      = 0;

  gamma_zellner      = 1;
  alpha_normal_gamma = 1.5;
  beta_normal_gamma  = 1000;

  extra_df_wishart      = 1;
  scale_wishart_diag    = 1;
  scale_wishart_offdiag = 0;
  maximum_scc_size      = -1; /* will be checked after reading the script */

  bConvergence_std   = 0;
  bConvergence_inc   = 0;
  nConvergence_start = 0;
  nConvergence_end   = 0;

  diff_logprior = 0;
  diff_loglikelihood = 0;
  diff_logposterior = 0;

} /* CleanupMemory */

/* ----------------------------------------------------------------------------
   GetCmdLineArgs

   Retrieves filenames from the command line arguments passed to
   the program.

   The command line syntax is:

     graph_sampler [input-file [output-files prefix]]

   Missing names are replaced by defaults .
*/
void GetCmdLineArgs (int cArg, char *const *rgszArg, char **pszFileIn,
                     char **pszPrefixOut)
{
  *pszFileIn = *pszPrefixOut = (char *) NULL;

  switch (cArg) { // filenames
    case 3: // output and input file specificed
      *pszPrefixOut = rgszArg[2];
      if (strlen(rgszArg[2]) > MAXFILENAME) {
        printf("Error: output file name must be less that %d "
               "caracter long - Exiting.\n\n", MAXFILENAME);
        exit(0);
      }
      // Fall through!

    case 2: // input file specified
      *pszFileIn = rgszArg[1];
      break;

    case 1: // no file names specified
      *pszFileIn = vszFileInDefault;
      *pszPrefixOut = NULL;
      break;

    default:
      /* ShowHelp ("Usage"); */ /* disabled for now */
      exit (-1);
      break;
  } // switch

} /* GetCmdLineArgs */


/* ----------------------------------------------------------------------------
   InitArrays

   Initialize various arrays if they have not been initialized in input.
*/
void InitArrays (void)
{
  int  i, j;
  long N = nNodes * nNodes;

  /* if current_adj is not defined it is initialized here to 0 */
  if (!current_adj) {
    current_adj = InitiMatrix(nNodes, nNodes);
    printf ("Setting current_adj to default value (null matrix).\n");

    for (i = 0; i < nNodes; i++)
      for (j = 0; j < nNodes; j++)
        current_adj[i][j] = 0;
  }

  /* initialize tempered sampling variables */
  if (bTempered) {
    indexT = 0;  /* start hot */
    dCZero = 10; /* why ? */
    dNZero = 50; /* why not ?  */
    plnPi = InitdVector (nTemperatures);
  }
  else {
    indexT = 0;
    nTemperatures = 1;
  }

  /* initialize space for the best (maximum probability) adjacency matrix */
  if (bsave_best_graph) {
    best_adj = InitiMatrix(nNodes, nNodes);
    for (i = 0; i < nNodes; i++)
      memcpy(best_adj[i], current_adj[i], nNodes * sizeof(int));
  }

  /* if hyper_pB is not defined it is initialized here to scale_pB * 0.5 for
     all elements (except the diagonal for BNs and similar cases);
     this is the "equanimous" prior */
  if (!hyper_pB) {
    hyper_pB = InitdMatrix(nNodes, nNodes);

    if (scale_pB < 0) {
        printf ("Error: Bernoulli prior probabilities must be in [0,1]\n"
                "       scale cannot be negative - Exiting.\n\n");
        exit(0);
    }

    if (scale_pB > 2) {
        printf ("Error: Bernoulli prior probabilities must be in [0,1]\n"
                "       scale cannot be larger than 2 - Exiting.\n\n");
        exit(0);
    }

    if(scale_pB == 1)
      printf ("Setting hyper_pB to equanimous.\n\n");
    else
      printf ("Setting hyper_pB to equanimous with scale %g.\n\n", scale_pB);

    scale_pB = scale_pB * 0.5;
    for (i = 0; i < nNodes; i++) {
      for (j = 0; j < nNodes; j++) {
        if ((i == j) && (bBN || (bAutocycles == FALSE) || bHypergraph))
          hyper_pB[i][j] = 0.0;
        else
          hyper_pB[i][j] = scale_pB;
      }
    }
  }
  log_hyper_pB = InitdMatrix(nNodes, nNodes);
  log_hyper_qB = InitdMatrix(nNodes, nNodes);

  for (i = 0; i < nNodes; i++) { /* ith line */
    for (j = 0; j < nNodes; j++) { // jth column
      log_hyper_pB[i][j] = log(hyper_pB[i][j]);
      log_hyper_qB[i][j] = log(1 - hyper_pB[i][j]);
    }
  }

  /* initialize matrix edge_requirements to zero by default */
  if (bPriorConcordance && !edge_requirements) {
    edge_requirements = InitiMatrix(nNodes, nNodes);
    printf ("Setting edge_requirements to default value (indifference).\n");

    for (i = 0; i < nNodes; i++) {
      for (j = 0; j < nNodes; j++) {
        if ((i == j) && (bBN || (bAutocycles == FALSE) || bHypergraph))
          edge_requirements[i][j] = -1;
        else
          edge_requirements[i][j] = 0;
      }
    }
  }

  /* initialize a table of differences between the binomial log
     probabilities of the total number of edges when going up
     successive edge counts: P(n=x+1) - P(n=x) */
  if (bPriorEdgeCount == TRUE) {
    double p = expected_n_edges / (double) N;

    pdiff_binom_P = InitdVector(N);
    for (i = 0; i < N; i++) // going up
      pdiff_binom_P[i] = log( (N-(i+1)+1) / (i+1.0) * p / (1.0-p) );
  }

  /* initialize a table of the degree counts and a table for their sum */
  if (bsave_the_degree_counts) {
    degree_count    = InitdVector(nNodes + nNodes);
    cumdegree_count = InitdVector(nNodes + nNodes);
    for (i = 0; i < (nNodes+nNodes); i++) {
      degree_count[i] = 0;
      cumdegree_count[i] = 0;
    }
  }

  /* initialize motifs cumulants */
  if (bsave_the_motifs_probabilities) {
    cum_nEloops = 0;
    cum_nFloops = 0;
  }

  /* initialize a Boolean array recording which nodes have been assigned
     a zero probability of having parents (a column of zero in the binomial
     prior matrix). Those nodes are typically used as special "control"
     nodes for which the likelihood will not be computed */
  if (bBN || bDBN || bHypergraph) {
    bAllowed_parents = InitiVector(nNodes);
    for (j = 0; j < nNodes; j++) { /* for each column (node) */
      i = 0;
      while ((i < nNodes) && (hyper_pB[i][j] == 0)) {
        i++;
      }
      bAllowed_parents[j] = (i == nNodes ? FALSE : TRUE);
    } /* end for */
  } /* end if */

  /* initialize a table of parents for each node
     (this is pricy in storage, would be better with a doubly linked
     list joining the 1's of the adjacency matrix) */
  nParents = InitiVector(nNodes);
  index_parents = InitiMatrix(nNodes, nNodes);

  for (j = 0; j < nNodes; j++) {
    nParents[j] = 0;
    for (i = 0; i < nNodes; i++)
      if (current_adj[i][j]) { /* we have a parent, store it */
        index_parents[j][nParents[j]] = i;
        nParents[j] += 1;
      }
    if (bBN) {
      if (bZellner && (nParents[j] >= nData)) {
        printf ("Error: node %d has more parents than data:\n"
                "       conflict with Zellner's score - Exiting.\n\n", j);
        exit(0);
      }
      if (bConstantGamma && (nParents[j] >= nData)) {
        printf ("Error: node %d has more parents than data:\n"
                "       conflict with Constant-Gamma score - Exiting.\n\n", j);
        exit(0);
      }
    }
    else {
      if (bDBN && bZellner && (nParents[j] >= nData - 1)) {
        printf ("Error: node %d has more parents than data (minus 1):\n"
                "       conflict with Zellner's score in a DBN - Exiting."
                "\n\n", j);
        exit(0);
      }
      else if (bHypergraph && bData && (nParents[j] >= nData)) {
        printf("Error: node %d has more parents than data:\n"
               "       conflict with Constant-Gamma score - Exiting.\n\n", j);
        exit(0);
      }
    }
  }

  /* if BN, initialize the list of node for fast topological sorting
     and check acyclicity
     beware: this assumes that nParents is initialized as above */
  if ((bBN) && (!IsDAG_w_topo_list_incremental (nNodes, current_adj)))
    lexerr("initial graph is not a DAG");

  /* initialize an edge summation matrix */
  if (bsave_the_edge_probabilities) {
    edgeP_thin = (nRuns > N ? N : 1); /* remember: N is nNodes squared */
    mat_sum = InitdMatrix(nNodes, nNodes);
  }

  component               = InitiVector(nNodes);
  component_size          = InitiVector(nNodes);
  proposed_component      = InitiVector(nNodes);
  proposed_component_size = InitiVector(nNodes);
  /* get the strongly connected components and their sizes */
  if (bHypergraph)
    Tarjan_with_sizes (current_adj, nNodes, component, component_size);

  /* initialize data likelihood related stuff */
  if (bData) {

    /* initialize likelihoods for each node */
    current_ll_node = InitdVector(nNodes);

    /* initialize a working matrix to be used in InvertMatrix for example */
    int dim = (nNodes > nData ? nNodes : nData);

    if (bBN || bHypergraph){
      pdWorkMatrixSizeN = InitdMatrix(dim, dim);
      pdM1 = InitdMatrix(dim, dim);
      pdM2 = InitdMatrix(dim, dim);
    if(bHypergraph || bConstantGamma) { /* extra matrices that are only used for SCC cases   */
                                        /* ConstantGamma treats likelihood as 1-dim SCC case */
      pdM3 = InitdMatrix(dim, dim);
      pdM4 = InitdMatrix(dim, dim);
      pdM5 = InitdMatrix(dim, dim);
      pdM6 = InitdMatrix(dim, dim);
      pdM7 = InitdMatrix(dim, dim);
      tpd5 = InitdMatrix(dim, dim);
    }
  } else { /* bDBN hopefully */
    pdWorkMatrixSizeN = InitdMatrix(dim+1, dim+1);
    pdM1 = InitdMatrix(dim+1, dim+1);
    pdM2 = InitdMatrix(dim+1, dim+1);
  }

  //for DBNs we use nNodes + 1, so

    /* setup a blank component list to be used for single nodes */
    dag_component = InitiVector(nNodes);
    for (i = 0; i < nNodes; i++)
      dag_component[i] = i;

    if (bHypergraph) {
      /* when multiple likelihoods change we need to store a vector: */
      updated_ll_vector = InitdVector (nNodes);
      /* list of nodes for which likelihood will be updated */
      plistNodesUpdated = NULL;
    }

  } /* if bData */



} /* InitArrays */


/* ----------------------------------------------------------------------------
   InitGlobals

   Initialize various global variables.
*/
void InitGlobals (void)
{
  nNodes            = 0;
  current_adj       = NULL;
  edge_requirements = NULL;
  hyper_pB          = NULL;
  pData             = NULL;
  bNAData           = FALSE;
  flag_update_loops = 0;

  iN_to_print       = 1000;

} /* InitGlobals */


/* ----------------------------------------------------------------------------
   Impute

   Impute the missing data of all nodes by MCMC sampling,
   the importance ratio is computed on the nodes' Markov blanket.
*/
void Impute ()
{
  register int tmp_child, tmp_parent;
  double curr_llike, new_llike, diff_llike, sd = 0.5, data_diff;
  PLISTELEMIJ ple = plistMissing->Head;
  static BOOL bPrint;
  static unsigned long iPrint_at = 0;
  static unsigned long iPrint_interval;
  static double* pTmp;

  if (!pTmp) { /* initialize */
    pTmp = InitdVector(nNodes);
    iPrint_interval = (nRuns > iN_to_print ? nRuns / iN_to_print : 1);
  }

  for (tmp_parent = 0; tmp_parent < nNodes; tmp_parent++)
    if (bHasMissing[tmp_parent]) {

      /* scan the missing data list, find start of parent's missing data */
      while (ple && (ple->iVal != tmp_parent))
        ple = ple->next;

      if (ple == NULL)
        lexerr ("Impute() called on a node without missing data");

      if (ple == plistMissing->Head) { /* start of the list */
        /* check whether we should print */
        if (iter > iPrint_at) {
          bPrint = 1;
          iPrint_at += iPrint_interval;
        }
        else
          bPrint = 0;
      }

      do { /* impute each of "tmp_parent" missing data */

        /* sample a new value, remember the difference to undo eventually */
        data_diff = sd * (Randoms() - 0.5); /* should be an adjustable kernel */
        pData[tmp_parent][ple->jVal] += data_diff;

        /* likelihood of the tmp_parent's Markov blanket */
        /* for tmp_parent itself: */
        curr_llike = current_ll_node[tmp_parent];

        if (bBN) {
          if (bZellner)
            pTmp[tmp_parent] = ZLoglikelihood_node (tmp_parent, pData);
          else {
            if (bDirichlet)
              pTmp[tmp_parent] = DLoglikelihood_node (tmp_parent, pData);
            else
              pTmp[tmp_parent] = GLoglikelihood_node (tmp_parent, pData);
          }
        }

        if (bDBN) {
          if (bZellner)
            pTmp[tmp_parent] = ZLoglikelihood_node_DBN (tmp_parent, pData);
          else {
            if (bDirichlet)
              pTmp[tmp_parent] = DLoglikelihood_node_DBN (tmp_parent, pData);
            else
              pTmp[tmp_parent] = NGLoglikelihood_node_DBN (tmp_parent, pData);
          }
        }

        new_llike = pTmp[tmp_parent];

        /* for its tmp_children: */
        for (tmp_child = 0; tmp_child < nNodes; tmp_child++) {
          if (current_adj[tmp_parent][tmp_child]) {

            curr_llike += current_ll_node[tmp_child];

            if (bBN) {
              if (bZellner)
                pTmp[tmp_child] = ZLoglikelihood_node (tmp_child, pData);
              else {
                if (bDirichlet)
                  pTmp[tmp_child] = DLoglikelihood_node (tmp_child, pData);
                else
                  pTmp[tmp_child] = GLoglikelihood_node (tmp_child, pData);
              }
            }
            else { /* bDBN, hopefully */
              if (bZellner)
                pTmp[tmp_child] = ZLoglikelihood_node_DBN (tmp_child, pData);
              else {
                if (bDirichlet)
                  pTmp[tmp_child] = DLoglikelihood_node_DBN (tmp_child, pData);
                else
                  pTmp[tmp_child] = NGLoglikelihood_node_DBN (tmp_child, pData);
              }
            }

            new_llike += pTmp[tmp_child];
          }
        }
        /* printf ("current blanket ll: %g\n", curr_llike); */
        /* printf ("new blanket ll: %g\n", new_llike); */

        /* accept of reject */
        diff_llike = new_llike - curr_llike;
        if ((diff_llike >= 0) || (log(Randoms()) < diff_llike)) { /* accept */
          /* update likelihoods */
          current_ll_node[tmp_parent] = pTmp[tmp_parent];
          for (tmp_child = 0; tmp_child < nNodes; tmp_child++) {
            if (current_adj[tmp_parent][tmp_child])
              current_ll_node[tmp_child] = pTmp[tmp_child];
          }
          /* keep the sampled data and print it */
          if (bPrint)
            fprintf (pImputedFile, "%g\t%g\n",
                     pData[tmp_parent][ple->jVal], new_llike);
        }
        else { /* reject the sampled data */
          pData[tmp_parent][ple->jVal] -= data_diff;
          if (bPrint)
            fprintf (pImputedFile, "%g\t%g\n",
                     pData[tmp_parent][ple->jVal], curr_llike);
        }

        ple = ple->next;

      } while (ple && (ple->iVal == tmp_parent));
  } /* end for tmp_parent */

} /* Impute */


/* ----------------------------------------------------------------------------
   Logprior_diff
   Computes the difference in density, according to
   2 priors: (eventually) degree and (eventually) motif
   Inputs:
    adjacency_current:  adjacency of the current graph
    parent_node
    child_node
    diff: the edge change proposed
     -1: deletion
     +1: creation
   Outputs:
    *logPdiff: total CHANGE in prior log-density.
*/
void Logprior_diff (int **adjacency_current, int parent_node, int child_node,
                    int diff, double *logPdiff)
{

  if (bPriorConcordance)
    *logPdiff = Logprior_diff_concordance(parent_node, child_node, diff);
  else
    *logPdiff = 0;

  if (bPriorDegreeNode)
    *logPdiff += Logprior_diff_degree(parent_node, child_node, diff);

  /* prior on total edge count */
  if (bPriorEdgeCount)
    *logPdiff += Logprior_diff_edge_number(diff);

  if (bPriorMotif || bsave_the_motifs_probabilities)
    UpdateCountTriangles(adjacency_current, parent_node, child_node, diff,
                         &diff_nEloops, &diff_nFloops);

  if (bPriorMotif) {
    proposed_motif_prior = LnBB(current_nEloops + diff_nEloops,
                                current_nEloops + current_nFloops +
                                diff_nEloops + diff_nFloops,
                                alpha_motif, beta_motif);

    *logPdiff += proposed_motif_prior - current_motif_prior;
  }

  if (bPriorSCC) {
    if (flag_update_loops)
      proposed_scc_prior = LnSCCPrior(proposed_component,
                                      proposed_component_size);
    else
      proposed_scc_prior = LnSCCPrior(component, component_size);

    *logPdiff += proposed_scc_prior - current_scc_prior;
  }

} /* Logprior_diff */


/* ----------------------------------------------------------------------------
   Logprior_diff_bernoulli
   Computes the difference in density, according to
   the beta-binomial (Bernoulli) prior.
   Inputs:
    parent_node
    child_node
    diff: the edge change proposed (DO NOT CALL IT WITH DIFF == 0)
     -1: deletion
     +1: creation
   Returns:
    CHANGE in prior log-density.
*/
double Logprior_diff_bernoulli (int parent_node, int child_node, int diff)
{
  double logPdiff;

  /* prior change under Bernoulli */
  if (diff == 1)
    logPdiff = log_hyper_pB[parent_node][child_node] -
               log_hyper_qB[parent_node][child_node];
  else
    logPdiff = log_hyper_qB[parent_node][child_node] -
               log_hyper_pB[parent_node][child_node];

  return(logPdiff);

} /* Logprior_diff_bernoulli */


/* ----------------------------------------------------------------------------
   Logprior_full

   Full log-prior for a given graph (specified by its adjacency matrix)
   Inputs:
     N : number of nodes
     adjacency : a pointer to the adjacency matrix
   This assumes that some globals have been set up:
     hyper_pB
     hyper_qB
     nParents
     etc.
   It also sets up useful globals and should be called at only at start, unless
   resetting is wanted.
*/
double Logprior_full (int N, int **adjacency)
{

  int i, j, diff;
  int **budding_adj; /* temporary adjacency matrix */

  double pr = 0;     /* init prior log density */
  double cumLD;      /* sum of log degrees */
  double cumPE;      /* temporary for probability of initial edge count */

  /* Bernoulli prior on edges: always done */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (adjacency[i][j] == 1)
        pr += log_hyper_pB[i][j]; /* log(hyper_pB[i][j]) */
      else
        pr += log_hyper_qB[i][j]; /* log(1 - hyper_pB[i][j]) */

  /* concordance prior */
  if (bPriorConcordance)
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++) /* count only the disagreements */
        if (Logprior_diff_concordance(i, j, (adjacency[i][j] ? 1 : -1)) < 0)
          pr -= lambda_concord;

  /* prior on degree distribution */
  if (bsave_the_degree_counts || bPriorDegreeNode) {
    /* set up the global table for the number of edges for each node */
    current_degrees = InitiVector(N);
    for (i = 0; i < N; i++) {
      current_degrees[i] = 0;
    }

    /* compute the table for the number of edges for each node */
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) /* sum over the ith line */
        current_degrees[i] += adjacency[i][j];

      for (j = 0; j < N; j++) /* sum over the ith column */
        if (j != i) /* do not count the node itself twice */
          current_degrees[i] += adjacency[j][i];
    }
  } /* end bsave_the_degree */

  if (bPriorDegreeNode) {
    /* get the log-density of the current degrees under a power law */
    cumLD = 0; /* cumulate the log degrees */
    for (i = 0; i < N; i++) {
      if (current_degrees[i] > 1)
        cumLD += log(current_degrees[i]);
    }
    pr += -gamma_degree * cumLD;
  }

  /* this is always done: */
  current_edge_count = 0;

  /* prior on total edge count */
  if (bPriorEdgeCount) {
    /* initialize also the current edge count using nParents */
    /* start with P(n=0) */
    double p = expected_n_edges / (double) (nNodes * nNodes);
    cumPE = nNodes * nNodes * log(1 - p);
  }

  /* part of the loop is always done to keep track of the number of edges */
  /* could be conditional on a flag */
  for (i = 0; i < nNodes; i++) {
    for (j = 0; j < nParents[i]; j++) {
      if (bPriorEdgeCount)
        cumPE += Logprior_diff_edge_number(+1);
      current_edge_count++;
    }
  }

  if (bPriorEdgeCount)
    pr += cumPE;

  /* now for motifs */
  if (bsave_the_motifs_probabilities || bPriorMotif) {
    /* counters for the two loop types; global initialize !
       E loops are A->B->C->A
       F (frustrated) loops are A->B->C<-A
       they will be initalized in the following at the values for the
       current graph
       other types of motifs could be added */
    current_nEloops = 0;
    current_nFloops = 0;

    /* to count the loops we simply reconstruct the adjacency matrix given
       (starting from an empty matrix) and count the loops as they are
       being formed */
    budding_adj = InitiMatrix(N, N); /* start empty */
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
        budding_adj[i][j] = 0;

    /* note: i is always parent of j */

    diff = 1; /* be explicit: we are only looking at nodes linked to
                 each other */
    for (i = 0; i < N; i++) { /* for each node */
      for (j = 0; j < N; j++) { /* for each potential child */
        if (adjacency[i][j] == 1) { /* skip the zeros... */
          UpdateCountTriangles(budding_adj, i, j, diff,
                               &diff_nEloops, &diff_nFloops);
          budding_adj[i][j] = 1;
          current_nEloops += diff_nEloops;
          current_nFloops += diff_nFloops;
        }
      }
    }

    FreeiMatrix (budding_adj, N);

  } /* end bsave_the_motifs_probabilities */

  if (bPriorMotif) {
    /* compute prior component and store it globally because it's expensive */
    current_motif_prior = LnBB(current_nEloops,
                               current_nEloops + current_nFloops,
                               alpha_motif, beta_motif);
    pr += current_motif_prior;
  }

  if (bPriorSCC) {
    current_scc_prior = LnSCCPrior(component, component_size);
    pr += current_scc_prior;
  }

  return (pr);

} /* Logprior_full */


/* ----------------------------------------------------------------------------
   ReadScript_Bison

   Read the simulation settings from a script file. The syntax is defined
   using lex and yacc. Meaningful input is then checked and default values
   are specified.
*/
void ReadScript_Bison (char *const filename)
{
  int i, j;
  extern FILE *yyin;

  yyin = fopen(filename, "r");
  if (yyin) {
    printf("Reading from file %s.\n\n", filename);
  }
  else
    lexerr("no input file");

  /* set default values for predefined scalar variables */
  bPriorConcordance = bPriorDegreeNode = bPriorEdgeCount =
  bPriorMotif = bPriorSCC = 0;
  bNormalGamma = bConstantGamma = bDirichlet = bZellner = 0;

  scale_pB       = 1;
  lambda_concord = 1;
  gamma_degree   = 1;
  alpha_motif    = 1;
  beta_motif     = 1;
  lambda_scc     = 1;
  gamma_scc      = 0;

  gamma_zellner      = 1;
  alpha_normal_gamma = 1.5;
  beta_normal_gamma  = 1000;

  extra_df_wishart      = 1;
  scale_wishart_diag    = 1;
  scale_wishart_offdiag = 0;
  maximum_scc_size      = -1; /* will be checked after reading the script */

  bConvergence_std   = 0;
  bConvergence_inc   = 0;
  nConvergence_start = 0;
  nConvergence_end   = 0;

  iter = 1000000000;
  rdm_gen_name = mt19937; /* if gsl is available, use Mersenne twister */

  /* printf("starting script reading...\n"); */
  yyparse();

  fclose(yyin);

  /* if convergence analysis, do some checks and return immediately */
  if (bConvergence_std ||  bConvergence_inc) {
    if (bsave_the_chain                ||
        bsave_best_graph               ||
        bsave_the_edge_probabilities   ||
        bsave_the_degree_counts        ||
        bsave_the_motifs_probabilities ||
        bsave_some_graphs) {
      printf("Warning: save options will be ignored.\n\n");
      bsave_the_chain = FALSE;
      bsave_best_graph               = FALSE;
      bsave_the_edge_probabilities   = FALSE;
      bsave_the_degree_counts        = FALSE;
      bsave_the_motifs_probabilities = FALSE;
      bsave_some_graphs              = FALSE;
    }
    return;
  }

  /* check nNodes value */
  if (nNodes == 0)
    lexerr ("nNodes cannot be zero");

  /* set maximum_scc_size if the user has not done it */
  if (maximum_scc_size == -1)
    maximum_scc_size = nNodes;

  /* if N too large you have to switch to long */
  if (nNodes > sqrt(INT_MAX))
    lexerr ("nNodes too large for 'int' indexing");

  /* check graph type inconsistencies */
  if (bBN) {
    if (bAutocycles)
      lexerr ("autocycles are forbidden if bayesian_network is True");
    if (bDBN)
      lexerr ("bayesian_network and dynamic_bayesian_network are both True");
    if (bHypergraph)
      lexerr ("bayesian_network and hypergraph are both True");
  }

  if (bDBN)
    if (bHypergraph)
      lexerr ("dynamic_bayesian_network and hypergraph are both True");

  if (bHypergraph)
    if (bAutocycles)
      lexerr ("autocycles are forbidden if hypergraph is True");

  /* check priors */
  if (bBN) {
    if (bPriorConcordance && edge_requirements)
      for (i = 0; i < nNodes; i++)
        if (edge_requirements[i][i] == 1)
          lexerr ("a concordance prior on BNs cannot require an "
                  "edge on the diagonal");

    if (hyper_pB)
      for (i = 0; i < nNodes; i++)
        if (hyper_pB[i][i] > 0)
          lexerr ("a Bernoulli prior on BNs must have a null diagonal");

    if (bPriorMotif)
      lexerr ("the motifs currently implemented in graph_sampler "
              "are incompatible with BNs");

    if (bPriorSCC)
      lexerr ("Strongly connected components are incompatible with BNs");
  }

  if (bHypergraph) {
    if (bPriorConcordance && edge_requirements)
      for (i = 0; i < nNodes; i++)
        if (edge_requirements[i][i] == 1)
          lexerr ("a concordance prior on hypergraphs cannot require an "
                  "edge on the diagonal");

    if (hyper_pB)
      for (i = 0; i < nNodes; i++)
        if (hyper_pB[i][i] > 0)
          lexerr ("a Bernoulli prior on hypergraphs must have a null diagonal");
  }

  if (hyper_pB) {
    if (bPriorConcordance) {
      printf ("Warning: potential conflict: concordance and ");
      printf ("Bernoulli priors are both defined.\n");
    }

    for (i = 0; i < nNodes; i++)
      if ((hyper_pB[i][i] > 0) &&
          (bBN || (bAutocycles == FALSE) || bHypergraph))
        lexerr ("the Bernoulli prior should have a null diagonal");
  }

  /* check data and likelihood */
  bData = (nData > 0);

  if (bData && !pData)
    lexerr ("nData > 0 but data values are not provided");

  if (bData && !(bBN || bDBN || bHypergraph)) {
    lexerr ("nData > 0 but no statistical model is defined");
  }

  if (!(bDirichlet || bNormalGamma || bConstantGamma || bZellner) && (bData)) {
    lexerr ("nData > 0 but data likelihood is not defined");
  }

  /* likelihoods cannot be defined in the absence of data */
  if ((bDirichlet || bNormalGamma || bConstantGamma || bZellner) && (!bData))
    lexerr ("Likelihood specified in the absence of data");

  /* one only one type of likelihood is allowed */
  if ((bDirichlet + bNormalGamma + bConstantGamma + bZellner) > 1)
    lexerr ("Multiple specifications of likelihood are not allowed");

  /* */
  if (bHypergraph && (bDirichlet || bNormalGamma || bZellner)) {
    printf ("Warning: hypergraphs require a Constant-Gamma likelihood;\n"
            "The likelihood is set accordingly.\n\n");
    bConstantGamma = TRUE;
  }

  /* check discrete data */
  if (bDirichlet) {
    if (!pDataLevels)
      lexerr ("Dirichlet score requires that data levels be specified");

    for (i = 0; i < nNodes; i++)
      for (j = 0; j < nNodes; j++)
        if (pData[i][j] != (int) pData[i][j])
          lexerr ("Dirichlet score requires integer data");
  }

  if (bNAData && bHypergraph)
    lexerr ("Missing data are not implemented for hypergraphs");

  /* miscellaneous initializations */
  printf("Randoms initalised with seed %f \n", seed);
  InitRandoms (rdm_gen_name, seed);

  bsave_some_graphs = (n_saved_adjacency > 0);

  /* printf ("done reading script.\n"); */

} /* ReadScript_Bison */


/* ----------------------------------------------------------------------------
   SampleTemperature

  Assumes that the number of attempted temperature jumps is equal to
  the number of iterations...
*/
void SampleTemperature (void)
{
  int    i, indexT_new;
  double dPjump;
  #define MINUSLN2 -0.6931471805599452862268

  /* Robbins-Monro updating of the temperature pseudo prior */
  for (i = 0; i < nTemperatures; i++) {
    if (i == indexT)
      plnPi[i] -= dCZero / (iter + dNZero);
    else
      plnPi[i] += dCZero / (nTemperatures * (iter + dNZero));
  }

  /* update population count of current temperature */
  /* pCountTemp[indexT]++; // this is for reporting only! */

  /* propose a new inverse temperature */
  if (indexT == 0)
    indexT_new = 1;     /* move up */
  else {
    if (indexT == nTemperatures - 1)
      indexT_new = indexT - 1;   /* move down */
    else
      if (Randoms() > 0.5)       /* move randomly */
        indexT_new = indexT + 1;
      else
        indexT_new = indexT - 1;
  }

  /* compute importance ratio */
  dPjump = (pInvTemperatures[indexT_new] - pInvTemperatures[indexT]) *
           (bData ? current_logprior : current_logposterior) +
           plnPi[indexT_new] - plnPi[indexT] +
           ((indexT_new == 0) || (indexT_new == nTemperatures - 1) ?
            0 : MINUSLN2) -
           ((indexT     == 0) || (indexT     == nTemperatures - 1) ?
            0 : MINUSLN2);

  /* test the proposed temperature jump */
  if (log(Randoms()) <= dPjump)
    indexT = indexT_new;  /* jump, else stay at indexT */

}  /* SampleTemperature */


/* ----------------------------------------------------------------------------
   SetPriorHyperParam

   Set the hyper parameters of the priors by looking at some general features
   of the data.
*/
void SetPriorHyperParam (void)
{
  printf("SetPriorHyperParam to do...\n\n");
  /* for example the lambda should be commensurate or larger than the raw data
     variance . Actually check the precision story.
     The variance (precision) of the reg param should be commensurate or
     larger with the range of values those reg params can take (???) etc */

} /* SetPriorHyperParam */


/* ----------------------------------------------------------------------------
   UndoDiff

   Undoes the change in global number of parents of node "child".
*/
void UndoDiff (int parent, int child, int diff)
{
  if (diff < 0) {
    /* just add parent that was removed by increasing the count of parents */
    nParents[child] += 1;
  }
  else {
    /* remove parent that was added */
    if (diff > 0)
      nParents[child] -= 1;
  }

} /* UndoDiff */


/* ----------------------------------------------------------------------------
   UpdateBestGraph

   Update the motifs accounting tables.
*/
void UpdateBestGraph (void)
{
  int i;

  if (bsave_best_graph /* && (iter >= nBurnin) */) { /* 29/01/2018 */
    if (dBestPosterior < current_logposterior) {
      dBestPosterior  = current_logposterior;
      dBestPrior      = current_logprior;
      dBestLikelihood = current_loglikelihood;
      for (i = 0; i < nNodes; i++)
        memcpy(best_adj[i], current_adj[i], nNodes * sizeof(int));
    }
  }

} /* UpdateBestGraph */


/* ----------------------------------------------------------------------------
   UpdateEdgeP

   Cumulate the adjacency matrices in mat_sum.
   In the case of tempering it assumes that we are on the target distribution
   (indexT == nTemperatures - 1) and that should be checked before calling this
   routine.
   We 'thin', that is compute only when the adjacency matrix has been fully
   updated, for consistency and because it is costly.
*/
void UpdateEdgeP (void)
{
  int i, j;
  static BOOL bInited = FALSE;

  if (iter >= nBurnin) {
    if (bInited == FALSE) {
      for (i = 0; i < nNodes; i++)
        for (j = 0; j < nNodes; j++)
          mat_sum[i][j] = current_adj[i][j];
      n_at_targetT = 1;
      bInited = TRUE;
    }
    else {
      if (iter % edgeP_thin == 0) {
        for (i = 0; i < nNodes; i++)
          for (j = 0; j < nNodes; j++)
            mat_sum[i][j] += current_adj[i][j];
        n_at_targetT++;
      }
    }
  }

} /* UpdateEdgeP */


/* ----------------------------------------------------------------------------
*/
void gsmain (char **szFileIn, char **szPrefixOut)
//void gsmain ()
{
  BOOL   bEdge;
  int    diff_location, i;
  /* clock variables */
  double  time_eta, time_elapsed;
  time_t  time_start, time_now;

  AnnounceProgram();
  InitGlobals();
  char *inp = *szFileIn;
  char *outp = *szPrefixOut;
  ReadScript_Bison(inp);
  InitOutputs(outp);
  if (bConvergence_std ||  bConvergence_inc) {
    ConvergenceAnalysis();
    CloseOutputs(outp);
    return;
  }

  InitArrays();

  /* compute the prior of the initial network,
  that initializes also book-keeping for fast computations of priors */
  current_logprior = Logprior_full (nNodes, current_adj);


  if (current_logprior <= -DBL_MAX)
    lexerr("initial network has prior with null probability");

  if (bData) {
    /* SetPriorHyperParam(); disabled, not developed */
    current_loglikelihood = Loglikelihood_full(nNodes, pData, component,
                                               component_size);
  }
  else
    current_loglikelihood = 0;

  current_logposterior = current_logprior + current_loglikelihood;
  dBestPrior      = current_logprior;
  dBestLikelihood = current_loglikelihood;
  dBestPosterior  = current_logposterior;

  //printf("current_adj:\n");
  //PrintiMatrix(stdout, nNodes, current_adj);
  //printf("hyper_pB:\n");
  //PrintdMatrix(stdout, nNodes, hyper_pB);

  /*
  printf("nParents:");
  for (i = 0; i < nNodes; i++) printf("%d ", nParents[i]);
  printf("\n");
  if(bHypergraph){
    printf("Strongly Connected Component:");
    for (i = 0; i < nNodes; i++) printf("%d ", component[i]);
    printf("\n");

    printf("Component sizes (each node):");
    for (i = 0; i < nNodes; i++) printf("%d ", component_size[i]);
    printf ("\n");
  }
  if(current_ll_node){
    printf("Node integrated log-likelihoods:");
    for (i = 0; i < nNodes; i++) printf("%f ", current_ll_node[i]);
    printf ("\n");
    printf ("Current integrated likelihood (kept in GS): %f \n",
            current_loglikelihood);
    printf ("Current integrated likelihood (via full function): %f \n",
            Loglikelihood_full(nNodes, pData, component, component_size));
  }
  */

  /* -------------------
     The sampler is here
  */

  if (bTempered)
    printf ("Doing %lu tempered MCMC iterations.\n\n...\n\n", nRuns);
  else
    printf ("Doing %lu iterations.\n\n...\n\n", nRuns);

  /* initialize parent and child node for systematic scan */
  parent = -1;
  child  =  0;

  for (iter = 0; iter < nRuns; iter++) {
    /* be careful to stay fast in this loop */

    /* printf("\niter %lu\n", iter); */

    label_Redo_it:

    /* if BN sought but the proposed graph was not a DAG, come back here */

    /* to create a proposal graph take 2 nodes, scanning systematically */
    if (parent < (nNodes - 1)) {
      parent = parent + 1;
    }
    else {
      parent = 0;

      if (child < (nNodes - 1))
        child = child + 1;
      else {
        child = 0;

        /* note: this is NOT reached if bAutocycles is false */

        /* at a start of an adjacency matrix updating cycle
           test and eventually update the temperature */
        if (bTempered && (iter > 0))
          SampleTemperature ();

        /* and impute all missing data */
        if (bNAData)
          Impute();

      }
    }

    flag_update_loops = 0;

    /* skip the diagonal if no autocycle (as in a pure BN or hypergraph) */
    if ((bAutocycles == FALSE) && (parent == child)) {
      if (parent < (nNodes - 1)) {
        parent = parent + 1;
      }
      else {
        parent = 1;
        child  = 0;

        /* note: this is reached if bAutocycles is false */

        /* at a start of an adjacency matrix updating cycle
           test and eventually update the temperature */
        if (bTempered && (iter > 0))
          SampleTemperature ();

        /* and impute all missing data */
        if (bNAData)
          Impute();
      }
    }

    /* sample a move from the baseline Bernoulli prior */
    bEdge = (Randoms () < hyper_pB[parent][child]); /* 0 or 1 */

    //if((iter < 30) && (iter > 0))
      //printf("iter %d: parent = %d child = %d; current_adj[0][0] = %d; bEdge = %d\n",
        //     iter, parent, child, current_adj[0][0], bEdge);
      //printf("iter %d: parent = %d child = %d adj = %d bEdge = %d ",
      //       iter, parent, child, current_adj[parent][child], bEdge);

    if (bEdge == current_adj[parent][child]) {
      diff = 0;
      /* printf("no diff\n"); */
    }
    else {
      if (bEdge == 1) { /* adding an edge */
        diff = 1;


        if (bBN) {

          /* check if it's still a DAG */
          if (!Check_DAG_Edge (current_adj, parent, child))
            goto label_Redo_it; /* forget attemped move completely */

          /* for Zellner likelihood there should not be more parents than data,
             remembering that nParents has not been updated yet */
          if (bZellner && (nParents[child] == nData))
            goto label_Redo_it;

          /* for constant-gamma likelihood there should be less
             parents than data, remembering that nParents has not been
             updated yet */
          if (bConstantGamma && (nParents[child] == nData - 1))
            goto label_Redo_it;
        }
        else {
          if (bDBN) {
            if (bZellner && (nParents[child] == nData - 1))
              goto label_Redo_it;
            if (bConstantGamma && (nParents[child] == nData - 2))
              goto label_Redo_it;
          }

          if (bHypergraph) {
            /* for constant-gamma likelihood there should be less
               parents than data, even inside a loop, remembering that
               nParents has not been updated yet */
            if (bData && (nParents[child] == nData - 1))
              goto label_Redo_it; /* printf("undo\n"); } */

            Update_parenthood(parent, child, diff);

            if (component[child] != component[parent]) {
              /* printf("add off edge\n"); */
              flag_update_loops = 1;
              if (!UpdateLoops(current_adj, parent, child, diff,
                               &diff_loglikelihood)) {
                nParents[child] -= 1; /* undo diff */
                /* printf("undo\n"); */
                goto label_Redo_it;   /* forget it completely */
        }
            }
            else { /* adding an edge inside a hypernode while respecting the
                      constraint on parent's number: no update needed */
              /* printf("add in edge\n"); */
              diff_loglikelihood = 0;
            }
          } /* if hypergraph */
        }
      }
      else { /* removing an edge */
        diff = -1;

        if (bHypergraph) {

          Update_parenthood (parent, child, diff);

          if (component_size[child] > 1) { /* child was in a loop */
            if (bData && (component[child] != component[parent])) {
              /* printf("remove off edge\n"); */
              /* we removed a parent of a loop but do not break the
                 loop itself; the loop parent list is recreated in
                 CGLoglikelihood_hypernode; we do not need to update
                 adjacency matrix for the calculations or 'component'
                 since it's only a parenthood change */

              /* just store new value, we'll subtract it soon */
              if (!CGLoglikelihood_hypernode (child, pData, component,
                                              &diff_loglikelihood)) {
                nParents[child] += 1; /* undo diff */
                /* printf("undo\n"); */
                goto label_Redo_it;   /* forget it completely */
              }

              /* reminder: likelihood of the supernode is stored in
                 the current_ll_node for every member of the supernode;
                 now we need to remember which nodes will get updated */

              /* this loop should be removed in the future */
              for (i = 0; i < nNodes; i++) {
                if (component[i] == component[child]) {
                  AddElemi(&plistNodesUpdated, i);
                  updated_ll_vector[i] = diff_loglikelihood;
                }
              }

              /* diff ill */
              diff_loglikelihood -= current_ll_node[child];

            }
            else {
              /* printf("remove in edge\n"); */
              /* we removed a link within a loop: check if it was destroyed */
              flag_update_loops = 1;
              if (!UpdateLoops (current_adj, parent, child, diff,
                                &diff_loglikelihood)) {
                nParents[child] += 1; /* undo diff */
                /* printf("undo\n"); */
                goto label_Redo_it;   /* forget it completely */
              }
            }
          }
          else {
            /* child was not in a loop: normal DAG score recalculation */
            if (bData)
              Loglikelihood_diff(parent, child, diff, pData,
                                 &diff_loglikelihood);
          }
        } /* end if hypergraph */
      }
    } /* end proposal likelihood calculations */

    /* update posterior */
    if (diff != 0) { /* change */

      Logprior_diff(current_adj, parent, child, diff, &diff_logprior);

      if (bData && (bBN || bDBN)) {
        /* contraints on number of parent have been checked above */
        Update_parenthood (parent, child, diff);
        Loglikelihood_diff (parent, child, diff, pData, &diff_loglikelihood);
      }

      /* do we really need to compute the posterior if we have no data? */
      diff_logposterior = diff_logprior + diff_loglikelihood;


      if (bTempered) /* elevate to power 1/temperature */
        diff_logposterior *= pInvTemperatures[indexT];

      //if((iter < 30) && (iter > 0))
        //printf("diff!=0 logprior = %f \n", diff_logposterior);


    }
    else { /* no change */
      diff_logposterior = 0;
    }

    /* check for acceptation and proceed accordingly */
    if ((diff_logposterior >= 0) || (log(Randoms ()) < diff_logposterior)) {

      /* accept */
      /* printf("accepting\n\n"); */

      UpdateDegrees_if_accept ();

      current_edge_count = current_edge_count + diff;

      UpdateMotifs_if_accept ();

      if (bHypergraph && (diff != 0))
        current_scc_prior = proposed_scc_prior;

      /* find flattened location of the sampled edge;
         go down columns, to be compatible with R;
         must start from 1 to leave 0 as indicator of no change by convention;
         then signed by the difference between adjacency matrices */
      diff_location = (parent + child * nNodes + 1) * diff;

      /* eventually write the location to output file */
      if (bsave_the_chain) {
        SaveChain (diff_location);
        if (bTempered) /* eventually save the current inverse temperature */
          SaveInverseTemperature();
      }

      /* now we can update the graph adjacency matrix,
         the parenthood of child has been already changed */
      if (diff != 0) {
        current_adj[parent][child] = !(current_adj[parent][child]);

        /* eventually update the total prior */
        if (bTempered || bsave_best_graph || bsave_some_graphs) {
          current_logprior += diff_logprior +
                              Logprior_diff_bernoulli (parent, child, diff);
        }

        /* update SCCs
           flag_update_loops is not essential and could be replaced
           by a different condition? */
        if (flag_update_loops) {
          /* always update ALL labels, since labelling is not 'invariant' */
          for (i = 0; i < nNodes; i++) {
            component[i] = proposed_component[i];
            component_size[i] = proposed_component_size[i];
          }
        }

        /* eventually update likelihood and posterior */
        if (bData) {

          if (bTempered || bsave_best_graph || bsave_some_graphs) {
            current_loglikelihood +=  diff_loglikelihood;
            current_logposterior   = current_logprior + current_loglikelihood;
          }

          if (!plistNodesUpdated) { /* case of a single node update */
            current_ll_node[child] += diff_loglikelihood;
          }
          else { /* case of multiple nodes: */
            while (plistNodesUpdated) {
              /* grab value and free up that element */
              i = PopElemi(&plistNodesUpdated);
              current_ll_node[i] = updated_ll_vector[i];
            }
          }
        } /* end if bData */

        /* eventually update the best graph */
        if (bsave_best_graph)
          UpdateBestGraph (); /* eventually not at the lowest temperature! */

      } /* end diff != 0 */
    } /* end of accept */

    else { /* reject */

      /* printf("rejecting\n\n"); */

      /* no differences between adjacency matrices: just write out zero */
      if (bsave_the_chain) {
        SaveChain (0);
        if (bTempered) /* save the current inverse temperature */
          SaveInverseTemperature();
      }

      UpdateDegrees_if_reject();
      UpdateMotifs_if_reject();

      /* no update of adjacency or topo sort list is needed,
         but the change in parenthood of child needs to be undone */
      UndoDiff(parent, child, diff);

      /* if loops were updated, forget the list of proposed updates */
      while (plistNodesUpdated) {
        /* to free the list */
        i = PopElemi(&plistNodesUpdated);
      }
    } /* end of reject */

    /* cumulate the adjacency matrices, i.e. cumulate edge counts */
    if (bsave_the_edge_probabilities && (indexT == (nTemperatures - 1)))
      UpdateEdgeP();

    /* save eventually the graph, eventually not at the lowest temperature */
    SaveGraph();

    /* clocking */
    if (nRuns * nNodes * nData >= 1E10) { /* for long runs */
      if (iter == 0)
        time_start = clock();
      else {
        if (((iter % (nRuns/10)) == 0) || (iter == nRuns-1)) {
          time_now = clock();
          time_elapsed = (time_now - time_start) / CLOCKS_PER_SEC;
          time_eta = (time_now - time_start)*(nRuns / (double)iter - 1) /
                     CLOCKS_PER_SEC;

          if (iter == (nRuns-1)) {
            printf("%lu iterations completed in %1.f seconds.\n\n",
                   nRuns, time_elapsed);
          }
          else {
            printf("Progress: %lu %%;\telapsed: %1.f sec; "
                   "estimated remaining: %1.f sec\n\n",
                   iter/(nRuns/100), time_elapsed, time_eta);
          }
          fflush(stdout);
        }
      }
    } /* end clocking */

  } /* end iter, end of sampler */

  /* final results if asked for: */

  /* edge probability matrix */
  SaveEdgeP(pEdgeFile);

  /* best graph */
  SaveBestGraph();

  /* save cumulated degree counts */
  SaveDegreeCounts();

  /* motifs probabilities */
  SaveMotifsP(pMotifFile);

  CloseOutputs(outp);

  CleanupMemory();

  printf("Done.\n\n");


  return;

} /* end */
