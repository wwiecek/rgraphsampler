/* lists.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

   A bunch of linked list utilities
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexerr.h"
#include "lists.h"


/* ----------------------------------------------------------------------------
   CopyString
   
   Creates a buffer large enough to hold the given string, copies it 
   into this buffer and returns a pointer to the buffer.
   
   Reports memory errors.
*/
char* CopyString (char* szIn)
{
  char* szBuf;

  if (szIn) {
    if ((szBuf = (char*) malloc (strlen(szIn) + 1))) {
      strncpy (szBuf, szIn, strlen(szIn));
      if (strlen(szIn) > 0)
        szBuf[strlen(szIn)]= '\0'; /* add terminating \0 */
      return (szBuf);
    }
    else
      lexerr ("out of memory in CopyString");
  }
  /* else */
  return (NULL);

} /* CopyString */


/* ----------------------------------------------------------------------------
   CopyQuotedString
   
   Creates a buffer large enough to hold the given string, copies it 
   - without the enclosing double quotes -
   into this buffer and returns a pointer to the buffer.
   
   Reports memory errors.
*/
char* CopyQuotedString (char* szIn)
{
  char* szBuf;

  if (szIn) {
    if ((szBuf = (char*) malloc (strlen(szIn) + 1))) {
      strncpy (szBuf, szIn+1, strlen(szIn) - 2);
      if ((strlen(szIn) - 2) > 0)
        szBuf[strlen(szIn) - 2]= '\0'; /* add terminating \0 */
      return (szBuf);
    }
    else
      lexerr ("out of memory in CopyQuotedString");
  }
  /* else */
  return (NULL);

} /* CopyQuotedString */


/* ----------------------------------------------------------------------------
   FreedList - for doubles

   Frees the memory allocated to a LIST, incrementing through each
   element sequentially.

   NOTE: pplist is a pointer to a LIST structure which is itself a pointer.
*/
void FreedList (PLISTD *pplist)
{
  PLISTD plist = *pplist; /* Get single pointer to work with */

  if (!plist)
    return;

  while (plist->Head) {
    plist->Tail = plist->Head;       /* Save p to current elem */
    plist->Head = plist->Head->next; /* Next list item */
    free (plist->Tail);              /* Free saved current elem */
  }

  free (plist);   /* Free the list header */
  *pplist = NULL; /* Reset the user's pointer */

} /* FreedList */


/* ----------------------------------------------------------------------------
   FreeiList - for integers

   Frees the memory allocated to a LIST, incrementing through each
   element sequentially.

   NOTE: pplist is a pointer to a LIST structure which is itself a pointer.
*/
void FreeiList (PLISTI *pplist)
{
  PLISTI plist = *pplist; /* Get single pointer to work with */

  if (!plist)
    return;

  while (plist->Head) {
    plist->Tail = plist->Head;       /* Save p to current elem */
    plist->Head = plist->Head->next; /* Next list item */
    free (plist->Tail);              /* Free saved current elem */
  }

  free (plist);   /* Free the list header */
  *pplist = NULL; /* Reset the user's pointer */

} /* FreeiList */


/* ----------------------------------------------------------------------------
   FreeijList - for pairs of integers

   Frees the memory allocated to a LIST, incrementing through each
   element sequentially.

   NOTE: pplist is a pointer to a LIST structure which is itself a pointer.
*/
void FreeijList (PLISTIJ *pplist)
{
  PLISTIJ plist = *pplist; /* Get single pointer to work with */

  if (!plist)
    return;

  while (plist->Head) {
    plist->Tail = plist->Head;       /* Save p to current elem */
    plist->Head = plist->Head->next; /* Next list item */
    free (plist->Tail);              /* Free saved current elem */
  }

  free (plist);   /* Free the list header */
  *pplist = NULL; /* Reset the user's pointer */

} /* FreeijList */


/* ----------------------------------------------------------------------------
   FreeStrList - for strings

   Frees the memory allocated to a LIST, incrementing through each
   element sequentially.

   NOTE: pplist is a pointer to a LIST structure which is itself a pointer.
*/
void FreeStrList (PLISTSTR *pplist)
{
  PLISTSTR plist = *pplist; /* Get single pointer to work with */

  if (!plist)
    return;

  while (plist->Head) {
    plist->Tail = plist->Head;       /* Save p to current elem */
    plist->Head = plist->Head->next; /* Next list item */
    free (plist->Tail);              /* Free saved current elem */
  }

  free (plist);   /* Free the list header */
  *pplist = NULL; /* Reset the user's pointer */

} /* FreeStrList */


/* ----------------------------------------------------------------------------
   InitdList - for doubles

   Initializes a list header structure and returns the pointer.
*/
PLISTD InitdList (void)
{
  /* Allocate header record */
  PLISTD plist = (PLISTD) malloc (sizeof(LISTD));

  if (plist) {                /* If allocation succeeds, */
    plist->Head = NULL;       /* .. initialize all to 0  */
    plist->Tail = NULL;
    plist->OriginalHead = NULL;
    plist->lSize = 0;
  }
  else
    lexerr ("out of memory in InitdList");

  return (plist);

} /* InitdList */


/* ----------------------------------------------------------------------------
   InitiList - for integers

   Initializes a list header structure and returns the pointer.
*/
PLISTI InitiList (void)
{
  /* allocate header record */
  PLISTI plist = (PLISTI) malloc (sizeof(LISTI));

  if (plist) {                /* If allocation succeeds, */
    plist->Head = NULL;       /* .. initialize all to 0  */
    plist->Tail = NULL;
    plist->OriginalHead = NULL;
    plist->lSize = 0;
  }
  else
    lexerr ("out of memory in InitiList");

  return (plist);

} /* InitiList */


/* ----------------------------------------------------------------------------
   InitlList - for long integers

   Initializes a list header structure and returns the pointer.
*/
PLISTL InitlList (void)
{
  /* allocate header record */
  PLISTL plist = (PLISTL) malloc (sizeof(LISTL));

  if (plist) {                /* If allocation succeeds, */
    plist->Head = NULL;       /* .. initialize all to 0  */
    plist->Tail = NULL;
    plist->OriginalHead = NULL;
    plist->lSize = 0;
  }
  else
    lexerr ("out of memory in InitlList");

  return (plist);

} /* InitlList */


/* ----------------------------------------------------------------------------
   InitijList - for pair of integers

   Initializes a list header structure and returns the pointer.
*/
PLISTIJ InitijList (void)
{
  /* Allocate header record */
  PLISTIJ plist = (PLISTIJ) malloc (sizeof(LISTIJ));

  if (plist) {                /* If allocation succeeds, */
    plist->Head = NULL;       /* .. initialize all to 0  */
    plist->Tail = NULL;
    plist->OriginalHead = NULL;
    plist->lSize = 0;
  }
  else
    lexerr ("out of memory in InitijList");

  return (plist);

} /* InitijList */


/* ----------------------------------------------------------------------------
   InitStrList - for strings

   Initializes a list header structure and returns the pointer.
*/
PLISTSTR InitStrList (void)
{
  /* Allocate header record */
  PLISTSTR plist = (PLISTSTR) malloc (sizeof(LISTSTR));

  if (plist) {                /* If allocation succeeds, */
    plist->Head = NULL;       /* .. initialize all to 0  */
    plist->Tail = NULL;
    plist->OriginalHead = NULL;
    plist->lSize = 0;
  }
  else
    lexerr ("out of memory in InitStrList");

  return (plist);

} /* InitStrList */


/* ----------------------------------------------------------------------------
   InitVarList - for user defined variables (symbols)

   Initializes a list header structure and returns the pointer.
*/
PLISTVAR InitVarList (void)
{
  /* Allocate header record */
  PLISTVAR plist = (PLISTVAR) malloc (sizeof(LISTVAR));

  if (plist) {                /* If allocation succeeds, */
    plist->Head = NULL;       /* .. initialize all to 0  */
    plist->Tail = NULL;
    plist->OriginalHead = NULL;
    plist->lSize = 0;
  }
  else
    lexerr ("out of memory in InitVarList");

  return (plist);

} /* InitVarList */


/* ----------------------------------------------------------------------------
   LookupVarList

   Check if a list item has the name cVal. If yes, copy the associated value
   in *dVal and return 1.
   If no return 0.
*/
int LookupVarList (PLISTVAR plist, char *cVal, double *dVal)
{
  PLISTELEMVAR iterator;

  if (!plist)
    return(0);
  
  iterator = plist->Head;

  do {
    if (!strcmp(iterator->cVal, cVal)) {
      *dVal = iterator->dVal;
      return(1);
    }
    else
      iterator = iterator->next;
  } while (iterator != NULL);

  return(0);

} /* LookupVarList */


/* ----------------------------------------------------------------------------
   PrintdList

   Print a list of doubles.
*/
void PrintdList (FILE *pFile, PLISTELEMD pfrom, PLISTELEMD pto)
{
  int iTotal = 0;
  PLISTELEMD ple;

  ple = pfrom;
  if (!ple) fprintf (pFile, "empty list.\n\n");
  while (ple != pto) {
    fprintf(pFile, "list node %ld, dVal %g\n", (long) ple, ple->dVal);
    iTotal += 1;
    ple = ple->next; /* increment to next elem */
  }
  fprintf (pFile, "N elements = %d\n\n", iTotal);

} /* PrintdList */


/* ----------------------------------------------------------------------------
   PrintiList

   Print a list of integers.
*/
void PrintiList (FILE *pFile, PLISTELEMI pfrom, PLISTELEMI pto)
{
  int iTotal = 0;
  PLISTELEMI ple;

  ple = pfrom;
  if (!ple) fprintf (pFile, "empty list.\n\n");
  while (ple != pto) {
    fprintf(pFile, "list node %ld, ID %d\n", (long) ple, ple->iVal);
    iTotal += 1;
    ple = ple->next; /* increment to next elem */
  }
  fprintf (pFile, "N elements = %d\n\n", iTotal);

} /* PrintiList */


/* ----------------------------------------------------------------------------
   PrintijList

   Print a list of pairs of integers.
*/
void PrintijList (FILE *pFile, PLISTELEMIJ pfrom, PLISTELEMIJ pto)
{
  int iTotal = 0;
  PLISTELEMIJ ple;

  ple = pfrom;
  if (!ple) fprintf (pFile, "empty list.\n\n");
  while (ple != pto) {
    fprintf(pFile, "list elem %ld, val (%d, %d)\n", 
            (long) ple, ple->iVal, ple->jVal);
    iTotal += 1;
    ple = ple->next; /* increment to next elem */
  }
  fprintf (pFile, "N elements = %d\n\n", iTotal);

} /* PrintijList */


/* ----------------------------------------------------------------------------
   PrintStrList

   Print a list of strings.
*/
void PrintStrList (FILE *pFile, PLISTELEMSTR pfrom, PLISTELEMSTR pto)
{
  int iTotal = 0;
  PLISTELEMSTR ple;

  ple = pfrom;
  if (!ple) fprintf (pFile, "empty list.\n\n");
  while (ple != pto) {
    fprintf(pFile, "list elem %ld, val %s\n", (long) ple, ple->cVal);
    iTotal += 1;
    ple = ple->next; /* increment to next elem */
  }
  fprintf (pFile, "N elements = %d\n\n", iTotal);

} /* PrintStrList */


/* ----------------------------------------------------------------------------
   PrintVarList

   Print a list of variables (symbol and value).
*/
void PrintVarList (FILE *pFile, PLISTELEMVAR pfrom, PLISTELEMVAR pto)
{
  int iTotal = 0;
  PLISTELEMVAR ple;

  ple = pfrom;
  if (!ple) fprintf (pFile, "empty list.\n\n");
  while (ple != pto) {
    fprintf(pFile, "list elem %ld, symbol %s, value %g\n",
            (long) ple, ple->cVal, ple->dVal);
    iTotal += 1;
    ple = ple->next; /* increment to next elem */
  }
  fprintf (pFile, "N elements = %d\n\n", iTotal);

} /* PrintVarList */


/* ----------------------------------------------------------------------------
   QueuedListItem

   Adds a new list item (of type double) to the tail of the list.
*/
void QueuedListItem (PLISTD plist, double dVal)
{
  PLISTELEMD pNewElem;

  if (!plist)
    return;

  if (!(pNewElem = (PLISTELEMD) malloc (sizeof(LISTELEMD))))
    lexerr ("out of memory in QueuedListItem");
  
  pNewElem->dVal = dVal; /* init new element */
  pNewElem->next = NULL;

  if (plist->Tail)
    plist->Tail->next = pNewElem; /* link new element */
  else
    plist->Head = pNewElem;       /* link first element */

  plist->Tail = pNewElem;         /* reset tail to new elem */
  plist->lSize++;                 /* increment size of list */

} /* QueuedListItem */


/* ----------------------------------------------------------------------------
   QueueiListItem

   Adds a new list item (of type int) to the tail of the list.
*/
void QueueiListItem (PLISTI plist, int iVal)
{
  PLISTELEMI pNewElem;

  if (!plist)
    return;

  if (!(pNewElem = (PLISTELEMI) malloc (sizeof(LISTELEMI))))
    lexerr ("out of memory in QueueiListItem");
  
  pNewElem->iVal = iVal; /* init new element */
  pNewElem->next = NULL;

  if (plist->Tail)
    plist->Tail->next = pNewElem; /* link new element */
  else
    plist->Head = pNewElem;       /* link first element */

  plist->Tail = pNewElem;         /* reset tail to new elem */
  plist->lSize++;                 /* increment size of list */

} /* QueueiListItem */


/* ----------------------------------------------------------------------------
   QueueijListItem

   Adds a new list item (pairs of integers) to the tail of the list.
*/
void QueueijListItem (PLISTIJ plist, int iVal, int jVal)
{
  PLISTELEMIJ pNewElem;

  if (!plist)
    return;

  if (!(pNewElem = (PLISTELEMIJ) malloc (sizeof(LISTELEMIJ))))
    lexerr ("out of memory in QueueijListItem");
  
  /* init new element */
  pNewElem->iVal = iVal;
  pNewElem->jVal = jVal;
  pNewElem->next = NULL;

  if (plist->Tail)
    plist->Tail->next = pNewElem; /* link new element */
  else
    plist->Head = pNewElem;       /* link first element */

  plist->Tail = pNewElem;         /* reset tail to new elem */
  plist->lSize++;                 /* increment size of list */

} /* QueueijListItem */


/* ----------------------------------------------------------------------------
   QueuelListItem

   Adds a new list item (of type long) to the tail of the list.
*/
void QueuelListItem (PLISTL plist, long lVal)
{
  PLISTELEML pNewElem;

  if (!plist)
    return;

  if (!(pNewElem = (PLISTELEML) malloc (sizeof(LISTELEML))))
    lexerr ("out of memory in QueuelListItem");
  
  pNewElem->lVal = lVal; /* init new element */
  pNewElem->next = NULL;

  if (plist->Tail)
    plist->Tail->next = pNewElem; /* link new element */
  else
    plist->Head = pNewElem;       /* link first element */

  plist->Tail = pNewElem;         /* reset tail to new elem */
  plist->lSize++;                 /* increment size of list */

} /* QueuelListItem */


/* ----------------------------------------------------------------------------
   QueueStrListItem

   Adds a new list item (of type string) to the tail of the list.
*/
void QueueStrListItem (PLISTSTR plist, char *cVal)
{
  PLISTELEMSTR pNewElem;

  if (!plist)
    return;

  if (!(pNewElem = (PLISTELEMSTR) malloc (sizeof(LISTELEMSTR))))
    lexerr ("out of memory in QueueStrListItem");

  pNewElem->cVal = CopyQuotedString(cVal); /* fill new element */
  pNewElem->next = NULL;

  if (plist->Tail)
    plist->Tail->next = pNewElem; /* link new element */
  else
    plist->Head = pNewElem;       /* link first element */

  plist->Tail = pNewElem;         /* reset tail to new elem */
  plist->lSize++;                 /* increment size of list */

} /* QueueStrListItem */


/* ----------------------------------------------------------------------------
   UniqueQueueVarListItem

   Adds a new list item (of type LISTELEMVAR) to the tail of the list, if its
   name cVal is not already in the list.
   If it is in the list, just assign the passed dVal value to the corresponding
   field.
*/
void UniqueQueueVarListItem (PLISTVAR plist, char *cVal, double dVal)
{
  PLISTELEMVAR pNewElem;

  if (!plist)
    return;

  if (!(pNewElem = (PLISTELEMVAR) malloc (sizeof(LISTELEMVAR))))
    lexerr ("out of memory in UniqueQueueVarListItem");

  if (!plist->Tail) { /* create first element */
    pNewElem->cVal = CopyString(cVal); /* store symbol */
    pNewElem->dVal = dVal;             /* store value  */
    pNewElem->next = NULL;
    plist->Head = pNewElem;
  }
  else { /* check if cVal is in the list, if not add at the end */
    PLISTELEMVAR iterator = plist->Head;
    do {
      if (!strcmp(iterator->cVal, cVal)) {
        iterator->dVal = dVal;
        return;
      }
      else
        iterator = iterator->next;
    } while (iterator != NULL);
    pNewElem->cVal = CopyString(cVal); /* store symbol */
    pNewElem->dVal = dVal;             /* store value  */
    pNewElem->next = NULL;          
    plist->Tail->next = pNewElem;
  }

  plist->Tail = pNewElem; /* reset tail to new elem */
  plist->lSize++;         /* increment size of list */

} /* UniqueQueueVarListItem */


/* ----------------------------------------------------------------------------
   UniqueQueueiList
   
   Adds a new unique list item of type int to the head of the list, if
   it is not already in the list.

   Should be rewritten, does not adhere to the lists standard.
*/
void UniqueQueueiList (PLISTELEMI *plist, int iVal)
{
  PLISTELEMI pNewElem;
  
  if (!(pNewElem = (PLISTELEMI) calloc(1, sizeof(LISTELEMI))))
    lexerr ("out of memory in UniqueQueueiList");
  
  if (*plist == NULL) {
    pNewElem->iVal = iVal;
    pNewElem->next = NULL;
  }
  else {
    PLISTELEMI iterator = *plist;
    do {
      if (iterator->iVal == iVal)
        return;
      else
        iterator = iterator->next;
    } while (iterator != NULL);
    pNewElem->iVal = iVal;
    pNewElem->next = *plist;          
  }

  *plist = pNewElem;

} /* UniqueQueueiList */


/* ----------------------------------------------------------------------------
   GetListSize
 
   Gives the size of the list.
*/
int GetListSize(PLISTELEMI L)
{
  PLISTELEMI aux;
  int size = 0;
  
  aux = L;
  while (aux != NULL) {
    size++;
    aux = aux->next;
  }

  return size;

} /* GetListSize */


/* ----------------------------------------------------------------------------
   PopListi
 
   Pops the integer value from the list. 
*/
int PopListi(PLISTI L)
{
  PLISTELEMI aux_next;
  int popped_valued;
  
  aux_next = L->Head->next;
  popped_valued = L->Head->iVal;
  free(L->Head);
  L->Head = aux_next;

  return popped_valued;

} /* PopListi */


/* ----------------------------------------------------------------------------
   PopElemi
 
   Pops the integer value from the LISTELEMI (via double pointer to ensure we 
   free up memory)
*/
int PopElemi(LISTELEMI **head)
{
  int val;
  PLISTELEMI aux_next;
  aux_next = (*head)->next;
  val = (*head)->iVal;
  free(*head); 
  *head = aux_next;

  return val;

} /* PopElemi */


/* ----------------------------------------------------------------------------
   AddElemi

   Adds a new list item of type int to the head of the list.
   It's copy of UniqueQueueiList() that doesn't search for uniques.
*/
void AddElemi (PLISTELEMI *L, int elem)
{
  PLISTELEMI p = NULL;
  
  p = (PLISTELEMI) calloc(1, sizeof(LISTELEMI));
  if (p == NULL)
    lexerr(/*MSG1,*/ "InsertList");
  
  if (*L == NULL) {
    p->iVal = elem;
    p->next = NULL;
  }
  else {
    p->iVal = elem;
    p->next = *L;          
  }

  *L = p;

} /* AddElemi */


/* end */
