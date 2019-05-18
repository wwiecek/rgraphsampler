/* topo_sort.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>

   Routines to check graph acyclicity using topological sorting.
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <stdio.h>
#include <stdlib.h>

#include "lexerr.h"
#include "lists.h"
#include "matrices.h"
#include "topo_sort.h"


/* ----------------------------------------------------------------------------
   Global definitions
*/

/* stuff for acyclicity checking */
PLISTI plistNodes = NULL;   /* a list of the nodes for topological sorting, to
                               check for acyclicity */


/* ----------------------------------------------------------------------------
   Check_DAG_Edge

   Check if an edge added to a DAG (whose topologically sorted node
   are in the global plistNodes), still gives a DAG.
   If yes, the (global!) list is resorted.
*/
BOOL Check_DAG_Edge (int **adjacency, int parent, int child)
{
  BOOL       bDo_Sort, bChild_found;
  PLISTELEMI ple, ple2, ple3;
  PLISTELEMI ple_interval_head, ple_interval_tail;

  /* check whether we need to resort the nodes between parent and child */

  /* find child in the list */
  plistNodes->Point_to_Head->next = plistNodes->Head;
  ple_interval_head = plistNodes->Point_to_Head;
  ple = plistNodes->Head;
  bChild_found = FALSE;
  while (ple) {
    if (ple->iVal == parent) {
      if (bChild_found) {
        bDo_Sort = TRUE;
        ple_interval_tail = ple->next;
      }
      else {
        bDo_Sort = FALSE;
      }
      break;
    }
    else {
      if (ple->iVal == child) {
        bChild_found = TRUE;
      }
      else {
        if (!bChild_found)
          ple_interval_head = ple;
      }
    }

    ple = ple->next; /* increment to next list item */

  } /* end while */

  /* if parent was after child we need to sort */
  if (bDo_Sort) {
    ple = ple_interval_head->next;

    while (ple->next != ple_interval_tail) {

      if (nParents[ple->next->iVal] == 0) {
        /* really no parents for ple->next, move it 1st in sublist */

        ple3 = ple_interval_head->next; /* old 1st */
        ple_interval_head->next = ple->next; /* move 1st */

        if (ple3 == plistNodes->Head) { /* update head list eventually */
          plistNodes->Head = ple->next;
	  if (plistNodes->Head == NULL)
	    printf("NULL\n");
        }

        ple->next = ple->next->next; /* link ple the one after the moved */
        ple_interval_head->next->next = ple3; /* link new 1st to old 1st */
        ple_interval_head = ple_interval_head->next; /* update head */
      }
      else { /* painful checking */

        ple2 = ple_interval_head->next; /* will run down columns */
        while (ple2 != ple_interval_tail) {

          /* check parenthood of current_node ple in the sublist */
          if (adjacency[ple2->iVal][ple->next->iVal])
            break; /* a parent: stop */

          ple2 = ple2->next;

        } /* end while ple2 */

        if (ple2 == ple_interval_tail) {
          /* no parents for ple->next, move it 1st in sublist */

          ple3 = ple_interval_head->next; /* old 1st */
          ple_interval_head->next = ple->next; /* move 1st */

          if (ple3 == plistNodes->Head) { /* update head list eventually */
            plistNodes->Head = ple->next;
            if (plistNodes->Head == NULL)
	      printf("NULL\n");
          }

          ple->next = ple->next->next; /* link ple the one after the moved */
          ple_interval_head->next->next = ple3; /* link new 1st to old 1st */
          ple_interval_head = ple_interval_head->next; /* update head */
        }
        else { /* ple->next has at least one parent */

          if (ple->next->next == ple_interval_tail)
            /* we could not move the parent... */
            return(FALSE);

          ple = ple->next;
        }
      }
    } /* end while ple */
  } /* end if bDo_Sort */

  return(TRUE);

} /* Check_DAG_Edge */


/* ----------------------------------------------------------------------------
   InitTopoList

   Initializes a linked list of nodes. We start implicitly with a null graph,
   so the nodes are in natural order.
*/
void InitTopoList (int nNodes)
{
  int        i;
  PLISTELEMI ple;

  plistNodes = InitiList();
  for (i = 0; i < nNodes; i++) {
    QueueiListItem (plistNodes, i); /* init queue to natural order */
  }

  /* record original chaining to restore it at next call */
  plistNodes->OriginalHead = plistNodes->Head;
  ple = plistNodes->Head;
  while (ple) {
    ple->pleInitialNext = ple->next;
    ple = ple->next; /* increment to next elem */
  }

  /* initialize a additional list head */
  if (!(plistNodes->Point_to_Head = (PLISTELEMI) malloc (sizeof(LISTELEMI))))
    lexerr ("out of memory in InitTopoList");

} /* InitTopoList */


/* ----------------------------------------------------------------------------
   KillTopoList

   Clear up memory taken by the private global plistNodes.
*/
void KillTopoList ()
{
  FreeiList(&plistNodes);
} /* KillTopoList */


/* ----------------------------------------------------------------------------
   IsDAG_w_topo

   Check if an adjacency matrix is a DAG (can be sorted topologically).
   Return TRUE if it's a DAG.
*/
BOOL IsDAG_w_topo (int nNodes, int **adjacency)
{
  int i, j;
  int n_isol = 0;
  int n_isol_old;
  static int *is_in = NULL;

  if (!is_in)
    is_in = InitiVector(nNodes);

  /* initialize */
  for (i = 0; i < nNodes; i++) {
    is_in[i] = 1;
  }

  /* quick check the diagonal and symmetries */
  for (i = 0; i < nNodes; i++)
    for (j = 0; j < nNodes; j++)
      if ((adjacency[i][j] == 1) && (adjacency[j][i] == 1)) {
        return(FALSE);
      }

  /* first remove the isolated nodes */
  for (i = 0; i < nNodes; i++) {
    j = 0;
    while ((j < nNodes) && (!adjacency[i][j]) && (!adjacency[j][i])) {
      /* no child, continue */
      j++;
    }
    if (j == nNodes) {
      is_in[i] = -1;
      n_isol++;
    }
  }

  /* the empty graph is a DAG... */
  if (n_isol == nNodes) {
    return (TRUE);
  }

  n_isol_old = n_isol;

  again:

  /* then, among the remaining there should be at least one without parents,
     so with an empty column */
  for (i = 0; i < nNodes; i++) {
    if (is_in[i] > 0) {
      j = 0;
      while ((is_in[j] < 0) || ((j < nNodes) && (adjacency[j][i] == 0))) {
        /* jump over or no child, continue */
        j++;
      }
      if (j == nNodes) { /* there is an empty column */
        is_in[i] = -1;
        n_isol++;
      }
    }
  } /* end for i */
  if (n_isol > n_isol_old) {
    if (n_isol == nNodes) {
      return (TRUE);
    }
    else {
      n_isol_old = n_isol;
      goto again;
    }
  }
  else { /* endless loop */
    return (FALSE);
  }

} /* IsDAG_w_topo */


/* ----------------------------------------------------------------------------
   IsDAG_w_topo_list

   Check if an adjacency matrix is a DAG (can be sorted topologically).
   Return TRUE if it's a DAG. Uses a linked list of nodes.
*/
BOOL IsDAG_w_topo_list (int nNodes, int **adjacency)
{
  int i;
  int n_isol = 0;
  int n_isol_old;

  PLISTELEMI ple, ple2, lastKept;

  if (!plistNodes) {
    InitTopoList(nNodes);
  }
  else { /* just restore the original list chain */
    plistNodes->Head = plistNodes->OriginalHead;
    ple = plistNodes->Head;
    while (ple) {
      ple->next = ple->pleInitialNext;
      ple = ple->next;
    }
  }

  /* check the diagonal because the algorithm will not find problems there */
  for (i = 0; i < nNodes; i++)
    if (adjacency[i][i] == 1)
      return(FALSE);

  n_isol_old = n_isol;

  again:

  /* in the current graph remove nodes without parents,
     so with an empty column */
  ple = lastKept = plistNodes->Head;
  while (ple) {
    ple2 = plistNodes->Head; /* will run down columns */
    while (ple2) { /* check parenthood of current_node i */
      if (adjacency[ple2->iVal][ple->iVal])
        break; /* a parent: stop */
      ple2 = ple2->next;
    }
    if (ple2 == NULL) { /* no parents, remove from list */
      n_isol++;
      lastKept->next = ple->next;
      if (ple == plistNodes->Head) { /* update head eventually */
        plistNodes->Head = ple->next;
      }
    }
    else { /* ple has parents, keep it */
      lastKept = ple;
    }

    ple = ple->next; /* increment to the next element of the list */
  }

  if (n_isol > n_isol_old) {
    if (n_isol == nNodes) {
      return(TRUE);
    }
    else {
      n_isol_old = n_isol;
      goto again;
    }
  }
  else { /* endless loop */
    return(FALSE);
  }

} /* IsDAG_w_topo_list */


/* ----------------------------------------------------------------------------
   IsDAG_w_topo_list_incremental

   Check if an adjacency matrix is a DAG (can be sorted topologically).
   Return TRUE if it's a DAG. Uses a linked list of nodes and works
   incrementally, adding edges one at a time.
   The list plistNodes gets sorted in the process.
*/
BOOL IsDAG_w_topo_list_incremental (int nNodes, int **adjacency)
{
  int        i, j;
  PLISTELEMI ple;

  if (!plistNodes) {
    InitTopoList(nNodes);
  }
  else { /* just restore the original list chain */
    plistNodes->Head = plistNodes->OriginalHead;
    ple = plistNodes->Head;
    while (ple) {
      ple->next = ple->pleInitialNext;
      ple = ple->next;
    }
  }

  /* scan the adjacency matrix, adding the edges one by one */
  for (i = 0; i < nNodes; i++) {
    for (j = 0; j < nNodes; j++) {
      if (adjacency[i][j]) { /* an edge to add */

        if (i == j) { /* on the diagonal... */
          return (FALSE);
        }

        if (!Check_DAG_Edge(adjacency, i, j))
          return (FALSE);

      } /* end if adjacency */
    } /* end for j */
  } /* end for i */

  return (TRUE);

} /* IsDAG_w_topo_list_incremental */


/* end */
