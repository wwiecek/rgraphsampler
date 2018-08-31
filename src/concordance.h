/* concordance.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

*/

#ifndef CONCORDANCE_H_DEFINED


/* ----------------------------------------------------------------------------
   Prototypes
*/

double Logprior_diff_concordance (int parent_node, int child_node, int diff);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals, to be defined elsewhere
extern int    **edge_requirements; // prior edge pattern matrix
extern double lambda_concord;      // exponent for concordance weighting


/* End */

#define CONCORDANCE_H_DEFINED
#endif  /* CONCORDANCE_H_DEFINED */

