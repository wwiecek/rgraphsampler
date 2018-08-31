/* degree.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 
*/

#ifndef MOTIFS_H_DEFINED


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

void   UpdateCountTriangles (int **adjacency, int i, int j, int diff,
                             long *cDiffEloops, long *cDiffFloops);
void   UpdateMotifs_if_accept (void);
void   UpdateMotifs_if_reject (void);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals, to be defined elsewhere
extern BOOL   bPriorMotif;          // flag for prior on defined motifs
extern BOOL   bsave_the_motifs_probabilities;
extern double cum_nEloops;          // cumulated number of Endless loops
extern double cum_nFloops;          // cumulated number of Frustrated loops
extern double current_motif_prior;  // motif prior density in current graph
extern double proposed_motif_prior; // motif prior density in proposed graph

extern unsigned long current_nEloops; // current number of Endless loops 
extern unsigned long current_nFloops; // current number of Frustrated loops 

extern int    diff;
extern long   diff_nEloops;         // proposed change in E loops count
extern long   diff_nFloops;         // proposed change in F loops count
extern int    nNodes;               // the number of nodes in graph

extern unsigned long iter;
extern unsigned long nBurnin;


/* End */

#define MOTIFS_H_DEFINED
#endif  /* MOTIFS_H_DEFINED */

