/* edge_number.h

   Written by Frederic Bois

   Copyright (c) 2015-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 
*/

#ifndef EDGE_NUMBER_H_DEFINED


/* ----------------------------------------------------------------------------
   Prototypes
*/

double Logprior_diff_edge_number (int diff);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals defined in graph_sampler.h
extern long current_edge_count; // number of edges in the graph
extern double *pdiff_binom_P;   // table of P(n=x+1) - P(n=x), see InitArrays

/* End */

#define EDGE_NUMBER_H_DEFINED
#endif  /* EDGE_NUMBER_H_DEFINED */

