/* hypernode.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "hypernode.h"
#include "lexerr.h"
#include "matrices.h"
#include "likelihoods.h"


/*
  Simple implementation of stack for Tarjan SCC algorithm
  (--- will be updated to a linked list ---)
*/
int tarjan_stack[STACKSIZE];
int tarjan_top = -1;

int pop (void) {
  int data;
  if (tarjan_top >= 0) {
     data = tarjan_stack[tarjan_top];
     tarjan_top = tarjan_top - 1;
     return data;
  }
  else {
    printf("Could not retrieve data, tarjan_stack is empty.\n");
    return (0);
  }
}

void push (int data) {

  if (tarjan_top < STACKSIZE) {
     tarjan_top = tarjan_top + 1;
     tarjan_stack[tarjan_top] = data;
  }
  else
    printf("Could not insert data, tarjan_stack is full.\n");
}

/* End stack. */


/* ----------------------------------------------------------------------------
   LnSCCPrior

   Compute the density of a graph given the number and sizes of its strongly
   connected component. The prior on number is Poisson, the prior of sizes
   is a power law.

*/
double LnSCCPrior (int *component, int *component_size)
{
  int i, j, n_all_components, n_real_components;
  double cumLS;

  /* count components (including degenerate of size one) */
  n_all_components = 0;
  for (i = 0; i < nNodes; i++)
    if (component[i] > n_all_components)
      n_all_components++;

  /* count only the components of size superior to one and at the same time 
     cumulate the log of their sizes under a power law */
  n_real_components = 0;
  cumLS = 0;
  for (i = 0; i < n_all_components; i++) { 
    j = 0;
    while (component[j] != i+1) /* first the first occurence of SCC i */
      j++;
    if (component_size[j] > 1) {
      n_real_components++;
      cumLS += log(component_size[j]);
    }
  }

  /* return log-density of the number of SCCs of size > 1 under Poisson +
     log-density of the SCC sizes under a power law */
  return (LnPoisson(n_real_components, lambda_scc) - gamma_scc * cumLS);

} /* LnSCCPrior */


/* ----------------------------------------------------------------------------
   Strongconnect

   DFS from an vertex that is recursively used in Tarjan algorithm
   (See online for explanation of DFS used by Tarjan.)

*/
void strongconnect (int **M, int dim, int v, int *cindex,
                    int *current_component, int *current_component_index,
                    int *vindex, int *lowlink, int *ontarjan_stack)
{
  int w;

  vindex[v] = *cindex;
  lowlink[v] = *cindex;

  (*cindex)++;
  push(v);
  ontarjan_stack[v] = 1;

  for (w = 0; w < dim; w++) {
    if (M[v][w] == 1) {
      if (vindex[w] == 0) {
        strongconnect (M, dim, w, cindex, current_component,
                       current_component_index, vindex, lowlink,
                       ontarjan_stack);
        if (lowlink[v] > lowlink[w]) {
          lowlink[v] = lowlink[w];
        }
      } else if (ontarjan_stack[w] == 1) {
        if (lowlink[v] > vindex[w]) {
          lowlink[v] = vindex[w];
        }
      }
    }
  }

  if (lowlink[v] == vindex[v]) {
    do {
      w = pop();
      ontarjan_stack[w] = 0;
      current_component[w] = *current_component_index;
    } while (w != v);
    (*current_component_index)++;
  }

} /* End strongconnect. */


/* ----------------------------------------------------------------------------
   Tarjan

   Tarjan SCC algo with pointer implementation
   Inputs:
     adj,               square adjacency matrix
     dim,               number of nodes in the graph
     current_component, a vector of assignment (vertex -> loop number)

   current_component is updated too.
*/
void Tarjan (int **adj, int dim, int *current_component)
{
  int i, cindex = 1;
  int current_component_index = 0;
  int vindex[dim];
  int lowlink[dim];
  int ontarjan_stack[dim];

  for (i = 0; i < dim; i++)
    vindex[i] = lowlink[i] = 0;

  for (i = 0; i < dim; i++)
    if (vindex[i] == 0)
      strongconnect (adj, dim, i, &cindex, current_component,
                     &current_component_index, vindex, lowlink, ontarjan_stack);

} /* Tarjan */


/* ----------------------------------------------------------------------------
  Tarjan_with_sizes

  modification of the Tarjan() routine that requires one more vector,
  current_component_size

  it does the same job as Tarjan, but also fills current_components SIZES
  in a separate array + makes sure that loops are "weakly monotonic"
  (i.e. unique(current_component) in R would give {0, 1, 2, 3, ...})
*/

void Tarjan_with_sizes (int **adj, int dim, int *current_component,
                        int *current_component_size)
{
  int cindex = 1;
  int current_component_index = 0;
  int vindex[dim];
  int lowlink[dim];
  int ontarjan_stack[dim];
  int i, j;
  int current_component_clone[dim]; // unordered version of current_component
  int monotonic_counter;

  for (i = 0; i < dim; i++)
    vindex[i] = lowlink[i] = 0;

  for (i = 0; i < dim; i++) {
    current_component_size[i] = 0;
    current_component[i] = 0; /* "uninitialised" */
    if (vindex[i] == 0) {
      strongconnect (adj, dim, i, &cindex, current_component_clone,
                     &current_component_index, vindex, lowlink, ontarjan_stack);
    }
  }

  /* how slow is this loop? (probably very slow); for now we just need 
     correctness, maybe it could be done in strongconnect */
  monotonic_counter  = 1;
  for (i = 0; i < dim; i++) {
    if (current_component[i] == 0) { // if this loop not checked before
      // printf("Running monotonic for vertex %d\n", i);
      for (j = i; j < dim; j++) {
        if (current_component_clone[j] == current_component_clone[i]) {
          current_component[j] = monotonic_counter;
          /* keep track of the size of SCC that each node belongs to */
          current_component_size[i] = (current_component_size[i] + 1);
          /* printf ("current_component size for i is %d \n",
                     current_component_size[i]); */
        }
      }
      monotonic_counter += 1;
      /* printf("%d ", monotonic_counter); */
      /* now we make sure that all SCC entries have the same size */
      for (j = i; j < dim; j++) {
        if (current_component_clone[j] == current_component_clone[i]) {
          current_component_size[j] = current_component_size[i];
        }
      }
    }
  }

} /* Tarjan_with_sizes */


/* ----------------------------------------------------------------------------
  compare_ints

  Comparison function. Receives two generic (void) pointers to the items 
  under comparison.
*/
int compare_ints(const void *p, const void *q) {
  int x = *(const int *)p;
  int y = *(const int *)q;
  if (x < y)
    return -1;
  else if (x > y)
    return 1;
  return 0;
}


/* ----------------------------------------------------------------------------
  IsDAG_w_tarjan:
  check if graph is DAG with Tarjan's SCC
  uses quicksort, perhaps this should be rethought but currently 
  it is not applied anywhere
*/
BOOL IsDAG_w_tarjan(int nNodes, int **adjacency)
{
  int i;
  int component[nNodes];

  /* check if there are any self-loops */
  for (i =0; i < nNodes; i++)
    if (adjacency[i][i] == 1)
      return 0;

  Tarjan (adjacency, nNodes, component);
  qsort (component, nNodes, sizeof(int), &compare_ints);
  for (i = 1; i < nNodes; i++) {
    if (component[i] == component[i-1]) {
      return 0;
    }
  }
  return 1;

} /* IsDAG_w_tarjan */


/* ----------------------------------------------------------------------------
   UpdateLoops()
   Update scoring functions in cases where the hypernode(s) in the graph
   might have changed

   1/ Calculate the strongly connected component with Tarjan_with_sizes()
   2/ Update scoring function (i.e. difference from current marginalized
      loglikelihoos) based on a number of possible cases

   Input:
     adj,        adjacency matrix (unchanged at this stage of sampler loop)
     parent,
     child,      two vertices of the proposal (directed edge to change in adj)
     diff,       proposed addition or deletion of node (if 0 nothing happens)
     diff_loglikelihood,  variable to store score difference in
   External variables used:
     component;
     component_size;
     proposed_component;
     proposed_component_size;
     plistNodesUpdated;
     updated_ll_vector;
     current_loglikelihood;

   Assumptions:
     diff != 0
     parent and child are not on the same loop if diff = 1
     if diff = -1 we know that parent and child are on a loop (ergo size > 1)

   apart from updating diff_loglikelihood this function
   will also keep track of which nodes will need to have their loglik updated

   Algorithm follows a simple flowchart that we'll document elsehwere.
   For now see comments next to each if()
   statement - all if-else cases are numbered
*/
int UpdateLoops(int **adj, int parent, int child, int diff,
                double *diff_loglikelihood) {

  int    max_component_visited = -1;
  double tmp_loglik;
  int    i, j;
  /* compute SCC (we know that diff is != 0) */
  adj[parent][child] = !adj[parent][child];
  /* if diff == -1 we could restrict to a tiny subgraph - see below */
  Tarjan_with_sizes(adj, nNodes, proposed_component, proposed_component_size);
  adj[parent][child] = !adj[parent][child];

  /* if there is not data: stop here */
  if (!pData)
    return(1);

  /* make sure difference is 0 */
  *diff_loglikelihood = 0;

  /* 1. Addition */
  if (diff == 1) {

    if (proposed_component_size[child] == 1) {
      /* 1.1. Child is not in a loop, update likelihood by a direct call */
      if (!CGLoglikelihood_hypernode (child, pData,
                                      dag_component, diff_loglikelihood))
        return (0); /* num_parents >= nData */

      *diff_loglikelihood -= current_ll_node[child];
    }
    else {
      /* 1.2. Child is in a loop, update the supernode likelihood */
      if (!CGLoglikelihood_hypernode (child, pData, proposed_component,
                                      &tmp_loglik))
        return(0); /* num_parents >= nData */

      /* 1.2.1. Scenario where the loop expanded: (note that if
         component[parent] == component[child] we don't even call
         UpdateLoops) (therefore proposed_component equality means that
         loop structure MUST have changed) */
      if (proposed_component[parent] == proposed_component[child]) {

        /* Step 1: mark nodes to update and subtract "old" scores 
           (once for each SCC) */
        for (i = 0; i < nNodes; i++) {
          // is it on the new SCC in the proposal?
          if (proposed_component[i] == proposed_component[child]) {
            /* did we subtract this likelihood already?
               (i.e. we did subtract when visiting this particular 
               proposed_component value) */
            if (max_component_visited < component[i]) {
              *diff_loglikelihood -= current_ll_node[i];
              max_component_visited = component[i];
            }
            AddElemi(&plistNodesUpdated, i);
            updated_ll_vector[i] = tmp_loglik;
          }
        }

        // Step 2: after subtracting node and supernode likelihoods
        *diff_loglikelihood += tmp_loglik;
      }

      /* 1.2.2. Supernode didn't 'grow',
         but likelihood changes with addition of an edge
         (and we know that we're in a supernode from an earlier if check) */
      else {
        *diff_loglikelihood = tmp_loglik - current_ll_node[child];
        /* update loglikelihoods if likelihood has changed */
        if (*diff_loglikelihood != 0) {
          for (i = 0; i < nNodes; i++) {
            if (proposed_component[i] == proposed_component[child]) {
              AddElemi(&plistNodesUpdated, i);
              updated_ll_vector[i] = tmp_loglik;
            }
          }
        }
      }
    }

    /* Special case:
       if supernode is THE WHOLE GRAPH (will happen for small examples!)
       there is nothing to subtract from, we just put */
    if (proposed_component_size[child] == nNodes)
      *diff_loglikelihood = - current_loglikelihood + tmp_loglik;

  } /* end edge addition */

  /* 2. Deletion */
  if (diff == -1) {
    /* this case is similar to diff == 1 but we can a priori
       forget about vertices not in component[child] - they're not affected
       we know that component_size[child] > 1, that's the starting condition */

    /* pragmatic test first: loop HAS TO GET SMALLER to change! */

    /* 2.1. Loop shrinks */
    if (proposed_component_size[child] < component_size[child]) {
      /* go through nodes of the old (shrinking) loop: */
      for (i = 0; i < nNodes; i++) {
        if (component[i] == component[child]) {
          /* Side note: remember, that comparison component vs
             proposed_component is invalid due to index numbers not
             being 'invariant' (ie loop can stay the same, but
             Tarjan indices change) */

          // 2.1.1 Creation of a new supernode:
          if (proposed_component_size[i] > 1) {
            // check if this loop has not been created yet:
            // printf("node %d; check this %d \n", i, max_component_visited);
            if (max_component_visited < proposed_component[i]) {
              if(!CGLoglikelihood_hypernode (i, pData, proposed_component,
                                             &tmp_loglik)) {
                return (0); /* num_parents >= nData */
              }

              *diff_loglikelihood = *diff_loglikelihood + tmp_loglik;
              max_component_visited = proposed_component[i];

              /* this is ineffective but it may happen that we create a 
                 new loop created while destroying the old one */
              for (j = 0; j < nNodes; j++) {
                if (proposed_component[j] == proposed_component[i]) {
                  AddElemi(&plistNodesUpdated, j);
                  updated_ll_vector[j] = tmp_loglik;
                }
              }
            }
          }
          else {
            /* 2.1.2 "creation" of (go back to) "normal" (non-super-)node
               this will crash if we create an autoloop: */
            tmp_loglik = GLoglikelihood_node (i, pData);

            *diff_loglikelihood = *diff_loglikelihood + tmp_loglik;
            AddElemi(&plistNodesUpdated, i);
            updated_ll_vector[i] = tmp_loglik;
          }
        }
      }
      /* subtract likelihood of the (possibly) destroyed supernode */
      if (*diff_loglikelihood != 0)
        *diff_loglikelihood = *diff_loglikelihood - current_ll_node[child];
    }

    /* 2.2. Loop did not shrink: nothing needs to be done.
       *** tumbleweeds *** */
  }

  /* Diagnostics
  if (*diff_loglikelihood != 0) {
    printf("Updated vector of (integrated) log-likelihoods: ");
    for(i = 0; i < nNodes; i++) printf("%f ", updated_ll_vector[i]);
    printf("\n");
  } */

  return (1);
  
} /* UpdateLoops() */


/* End */
