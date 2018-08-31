/* motifs.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

   Routines for a beta-binomial prior on the proportion of E loops 
   (A -> B -> C -> A) over the sum of E loops and F loops (A -> B <- C -> A)
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include "motifs.h"


/* ----------------------------------------------------------------------------
   UpdateCountTriangles
   
   computes the change in of E and F loops counts that
   would occur in adjacency if move was implemented at position (i,j)
   Inputs:
    adjacency: an adjacency matrix
    i : node 1, parent
    j : node 2, child
    diff: the edge change proposed
     -1: deletion
     +1: creation
   Outputs
    cDiffnEloops and cDiff_nFloops: the change in counts of E and F loops
*/
void UpdateCountTriangles (int **adjacency, int i, int j, int diff,
                           long *cDiffEloops, long *cDiffFloops)
{
  int k;

  *cDiffEloops = 0;
  *cDiffFloops = 0;

  if (i != j) { // autoloops are NOT considered
    for (k = 0; k < nNodes; k++) {
      if ((k != i) && (k != j)) { // i <-> j <-> j does not count a loop

        if (adjacency[k][i] == 1) { // k -> i
          if (adjacency[k][j] == 1) { // k -> j

            if (diff == 1) // creation
              *cDiffFloops += 1;
            else           // deletion
              *cDiffFloops -= 1;
          }
          if (adjacency[j][k] == 1) { // j -> k

            if (diff == 1) // creation
              *cDiffEloops += 1;
            else           // deletion
              *cDiffEloops -= 1;
          }
        } // end of k -> i

        if (adjacency[i][k] == 1) { // i -> k
          if (adjacency[k][j] == 1) { // k -> j

            if (diff == 1) // creation
              *cDiffFloops += 1;
            else           // deletion
              *cDiffFloops -= 1;
          }
          if (adjacency[j][k] == 1) { // j -> k

            if (diff == 1) // creation
              *cDiffFloops += 1;
            else           // deletion
              *cDiffFloops -= 1;
          }
        } // end of i -> k

      } // end k != j
    } // end of for k
  } // end i != j

} /* UpdateCountTriangles */


/* ----------------------------------------------------------------------------
   UpdateMotifs_if_accept

   Update the motifs accounting tables.
*/
void UpdateMotifs_if_accept (void)
{
  if (bPriorMotif || bsave_the_motifs_probabilities) { 
    if (diff != 0) {
      current_nEloops += diff_nEloops;
      current_nFloops += diff_nFloops;
      current_motif_prior = proposed_motif_prior;
    }

    // if required for printing, update motif counts
    if (bsave_the_motifs_probabilities) {
      if (iter >= nBurnin) {
        cum_nEloops += current_nEloops;
        cum_nFloops += current_nFloops;
      }
    } // end bsave
  } // end bPriorMotif

} /* UpdateMotifs_if_accept */


/* ----------------------------------------------------------------------------
   UpdateMotifs_if_reject

   Update the motifs accounting tables.
*/
void UpdateMotifs_if_reject (void)
{
  if (bsave_the_motifs_probabilities) {
    if (iter >= nBurnin) {
      cum_nEloops += current_nEloops;
      cum_nFloops += current_nFloops;
    }
  } // end bsave

} /* UpdateMotifs_if_reject */


/* end */
