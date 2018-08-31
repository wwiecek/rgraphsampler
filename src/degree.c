/* degree.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

   Contains the routines needed to compute a power prior on the distribution
   of the nodes degrees.
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <math.h>

#include "degree.h"


/* ----------------------------------------------------------------------------
   InitDegrees_tables

   Initialize meaningfully the degrees accounting tables.
*/
void InitDegrees_tables (void)
{
  int  i;
  unsigned long j;
  
  for (i = 0; i < nNodes; i++)
    degree_count[current_degrees[i]] += 1;

  for (j = 0; j < (nNodes+nNodes); j++)
    cumdegree_count[j] = degree_count[j];

} /* InitDegrees_tables */


/* ----------------------------------------------------------------------------
   Logprior_diff_degree
   
   Compute the change in density under a power distribution after a given
   pairwise modification of the network
   diff: type of edge change between nodes 1 and 2
    -1: deletion,
    +1: creation.
*/
double Logprior_diff_degree (int node1, int node2, int diff)
{
  int    proposal_degrees_node1, proposal_degrees_node2;
  int    tmp1, tmp2;
  double difflog;

  if (diff == -1) { // deletion 
    proposal_degrees_node1 = current_degrees[node1] - 1;

    // preempt the zero degree case
    if (proposal_degrees_node1 == 0)
      tmp1 = 1;
    else
      tmp1 = proposal_degrees_node1;

    if (node1 != node2) {
      proposal_degrees_node2 = current_degrees[node2] - 1;

      // preempt the zero degree case
      if (proposal_degrees_node2 == 0)
        tmp2 = 1;
      else
        tmp2 = proposal_degrees_node2;

      // compute difference in log densities
      difflog = - gamma_degree * 
                  log((tmp1 * tmp2) /
                      (double) (current_degrees[node1] *
                                current_degrees[node2]));
    }
    else {
      // compute difference in log densities for the diagonal case
      difflog = - gamma_degree * log (tmp1 / (double) current_degrees[node1]);
    }
  } // end if move == 1
  else {
    // addition (diff == 1)
    proposal_degrees_node1 = current_degrees[node1] + 1;

    // preempt the zero degree case
    if (current_degrees[node1] == 0)
      tmp1 = 1;
    else
      tmp1 = current_degrees[node1];

    if (node1 != node2) {
      proposal_degrees_node2 = current_degrees[node2] + 1;

      // preempt the zero degree case
      if (current_degrees[node2] == 0)
        tmp2 = 1;
      else
        tmp2 = current_degrees[node2];

      difflog = - gamma_degree * 
                  log((proposal_degrees_node1 * proposal_degrees_node2) /
                      (double) (tmp1 * tmp2));
    }
    else {
      difflog = - gamma_degree * log (proposal_degrees_node1 / (double) tmp1);
    }
  }

  return (difflog);

} /* Logprior_diff_degree */


/* ----------------------------------------------------------------------------
   UpdateDegrees_if_accept

   Update the degrees accounting tables.
*/
void UpdateDegrees_if_accept (void)
{
  unsigned long j;
  
  if (bPriorDegreeNode || bsave_the_degree_counts) { 
    if (diff != 0) {
      current_degrees[parent] += diff;
      if (parent != child) // do not count twice
        current_degrees[child] += diff;
    }
  } // end bPriorDegreeNode

  // if required, update degree counts and cumulate them
  if (bsave_the_degree_counts) {
    if (iter >= nBurnin) {
      if (iter == nBurnin) { 
        InitDegrees_tables();
      }
      else { // update
        if (diff != 0) {
          degree_count[current_degrees[parent]] += 1;
          degree_count[current_degrees[parent] - diff] -= 1;
          if (parent != child) {
            degree_count[current_degrees[child]] += 1;
            degree_count[current_degrees[child] - diff] -= 1;
          }
        }
              
        // cumulate degree counts to estimate their probability
        for (j = 0; j < (nNodes+nNodes); j++)
          cumdegree_count[j] += degree_count[j];

      } // end update
    }
  } // end bsave
  
} /* UpdateDegrees_if_accept */


/* ----------------------------------------------------------------------------
   UpdateDegrees_if_reject

   Update the degrees accounting tables.
*/
void UpdateDegrees_if_reject (void)
{
  unsigned long j;
  
  // if required, update degree counts and cumulate them
  if (bsave_the_degree_counts) {
    if (iter >= nBurnin) {
      if (iter == nBurnin) {
        InitDegrees_tables();      
      }
      else { // cumulate degree counts to estimate their probability
        for (j = 0; j < (nNodes+nNodes); j++) {
          cumdegree_count[j] += degree_count[j];
        }
      } 
    }
  } // end bsave

} /* UpdateDegrees_if_reject */


/* end */
