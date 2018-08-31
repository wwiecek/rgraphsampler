/* hypernode.h

   Written by Frederic Bois

   Copyright (c) 2014-2016 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 
*/

#define STACKSIZE 1000
#ifndef PATHS_H_DEFINED

/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "lists.h"
#include "random.h"


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

int    pop ();
void   push (int data);
double LnSCCPrior (int *component, int *component_size);
void   strongconnect (int **M, int dim, int v, int *cindex,
                      int *current_component, int *current_component_index, 
                      int *vindex, int *lowlink, int *onstack);
void   Tarjan (int **adj, int dim, int *current_component);
void   Tarjan_with_sizes (int **adj, int dim, int *current_component,
                          int *current_component_size);
int    compare_ints (const void *p, const void *q);
int    UpdateLoops (int **adj, int parent, int child, int diff,
                    double *diff_loglikelihood);


/* ----------------------------------------------------------------------------
   Global declarations
*/

extern int         nNodes;         // total number of nodes
extern int       **index_parents;  // list of current parents for each node
extern double    **pData;          // array of nodes, a vector of data per node

extern int        *component;               // Tarjan SCC vector
extern int        *component_size;          // Tarjan SCC vector
extern int        *proposed_component;      // Tarjan SCC vector
extern int        *proposed_component_size; // Tarjan SCC vector
extern PLISTELEMI  plistNodesUpdated;       // list of nodes where score
                                            // updated (got on/off loops)

extern double      lambda_scc;              // Poisson rate on number of SCCs
extern double      gamma_scc;               // exponent of the SCC sizes prior

extern double     *updated_ll_vector;       // updated values of score
extern double      current_loglikelihood;   // current score


#define PATHS_H_DEFINED
#endif

/* end */
