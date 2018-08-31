/* degree.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

*/

#ifndef DEGREE_H_DEFINED


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

void   InitDegrees_tables (void);
double Logprior_diff_degree (int node1, int node2, int diff);
void   UpdateDegrees_if_accept (void);
void   UpdateDegrees_if_reject (void);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals, to be defined elsewhere
extern BOOL   bPriorDegreeNode;    // flag for power prior on degrees
extern BOOL   bsave_the_degree_counts;
extern double *cumdegree_count;
extern int    *current_degrees;    // table of # of edges for each node
extern double *degree_count;
extern int    diff;
extern double gamma_degree;        // exponent of the degrees power prior
extern int    nNodes;              // the number of nodes in graph
extern int    parent, child;

extern unsigned long iter;
extern unsigned long nBurnin;

/* End */

#define DEGREE_H_DEFINED
#endif  /* DEGREE_H_DEFINED */

