/* concordance.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

   Routines for a concordance score (measure of two graphs similarity)
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include "concordance.h"


/* ----------------------------------------------------------------------------
   Logprior_diff_concordance
 
   Computes the change in density (actually a score) due to the change
   (creation or deletion) of an edge, given three sets of edges: desired,
   undesired, neutral, as specified by edge_requirements (1, -1, 0, resp.)
   Inputs:
    parent_node
    child_node
    diff: the edge changed proposed 
     -1: deletion
      0: no change
     +1: creation
    an implicit input is lambda_concord, whose default is 1, eventually
    changed by the user.
   Returns:
    zero if neutral or agreement, else lambda_concord.
 */
double Logprior_diff_concordance (int parent_node, int child_node, int diff)
{
  if (edge_requirements[parent_node][child_node] == 0) // neutral
    return (0);
  else {
    if (edge_requirements[parent_node][child_node] == diff) {
      // change from disagreement to agreement with the prior
      return (+lambda_concord); 
    }
    else {
      // change from agreement to disagrees with the prior
      return (-lambda_concord);
    } 
  }

} /* Logprior_diff_concordance */


/* end */
