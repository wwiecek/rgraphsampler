/* edge_number.c

   Written by Frederic Bois

   Copyright (c) 2015-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

   Routines for prior on the number of edges of the graph
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include "edge_number.h"


/* ----------------------------------------------------------------------------
   Logprior_diff_edge_number
 
   Computes the change in density due to a change
   (creation or deletion) in the number of  edges.
   Inputs:
    parent_node
    child_node
    diff: the edge changed proposed 
     -1: deletion
      0: no change
     +1: creation
    an implicit input is current_edge_count, a global variable keeping track 
    of the current number of edges.
   Returns:
    the difference in probability density of the number of edges under a 
    binomial distribution, given the change proposed. Uses the global table
    pdiff_binom_P to read the result
 */
double Logprior_diff_edge_number (int diff)
{
  if (diff == 1) {
    return ( pdiff_binom_P[current_edge_count]); 
  }
  else { // diff == -1
    return (-pdiff_binom_P[current_edge_count - 1]);
  }
} /* Logprior_diff_edge_number */


/* end */
