/* topo_sort.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>
*/

#ifndef TOPO_H_DEFINED


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

BOOL   Check_DAG_Edge (int **adjacency, int parent, int child);
void   InitTopoList (int nNodes);
void   KillTopoList ();
BOOL   IsDAG_w_topo_list_incremental (int nNodes, int **adjacency);


/* ----------------------------------------------------------------------------
   Global declarations
*/

// externals, to be defined elsewhere
extern int    *nParents;           // number of parents for each node


/* End */

#define TOPO_H_DEFINED
#endif  /* TOPO_H_DEFINED */

