/* convergence.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 
*/

#ifndef CONVERGE_H_DEFINED


/* ----------------------------------------------------------------------------
   Inclusions
*/
#include <stdio.h>
#include <stdlib.h>

#include "lexerr.h"
#include "matrices.h"
#include "outputs.h"


/* ----------------------------------------------------------------------------
   Type definitions
*/

#ifndef TRUE
typedef int BOOL;
#define TRUE  1
#define FALSE 0
#endif


/* ----------------------------------------------------------------------------
   Constants
*/

#define LARGE_N  11  /* small matrices have N less than that */


/* ----------------------------------------------------------------------------
   Prototypes
*/
void ConvergenceAnalysis (void);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals, to be defined elsewhere

extern int    nNodes;               // the number of nodes in graph
extern int    bConvergence_std;     // check convergence over an interval
extern BOOL   bConvergence_inc;     // check convergence at every step
extern int    nChains;              // number of MCMC chains to read
extern char   **pChainNames;        // vector of chain file names

extern unsigned long nConvergence_start; // iter to start convergence check
extern unsigned long nConvergence_end;   // iter to end convergence check

#define GS_H_DEFINED
#endif

/* end */
