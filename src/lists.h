/* lists.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

*/

#ifndef LISTS_H_DEFINED


/* ----------------------------------------------------------------------------
   Typedefs
*/

typedef struct tagLISTELEMD { /* List element record for a double */
  double dVal;
  struct tagLISTELEMD *pleInitialNext; /* Next in the list initially */
  struct tagLISTELEMD *next;           /* Next in the list */
} LISTELEMD, *PLISTELEMD;

typedef struct tagLISTELEMI { /* List element record for an integer */
  int    iVal;
  struct tagLISTELEMI *pleInitialNext; /* Next in the list initially */
  struct tagLISTELEMI *next;           /* Next in the list */
} LISTELEMI, *PLISTELEMI;

typedef struct tagLISTELEMIJ { /* List element record for a pair of integers */
  int iVal;
  int jVal;
  struct tagLISTELEMIJ *pleInitialNext; /* Next in the list initially */
  struct tagLISTELEMIJ *next;           /* Next in the list */
} LISTELEMIJ, *PLISTELEMIJ;

typedef struct tagLISTELEML { /* List element record for a long */
  long   lVal;
  struct tagLISTELEML *pleInitialNext; /* Next in the list initially */
  struct tagLISTELEML *next;           /* Next in the list */
} LISTELEML, *PLISTELEML;

typedef struct tagLISTELEMSTR { /* List element record for a string */
  char   *cVal;
  struct tagLISTELEMSTR *pleInitialNext; /* Next in the list initially */
  struct tagLISTELEMSTR *next;           /* Next in the list */
} LISTELEMSTR, *PLISTELEMSTR;

typedef struct tagLISTELEMVAR { /* List element record for a user variable */
  char  *cVal; /* symbol */
  double dVal; /* value  */
  struct tagLISTELEMVAR *pleInitialNext; /* Next in the list initially */
  struct tagLISTELEMVAR *next;           /* Next in the list */
} LISTELEMVAR, *PLISTELEMVAR;

typedef struct tagLISTD {  /* List record for doubles */
  PLISTELEMD Head;         /* First elem in list */
  PLISTELEMD Tail;         /* Last  elem in list */
  PLISTELEMD OriginalHead;
  PLISTELEMD Point_to_Head;
  long       lSize;        /* Number of elems in list */
} LISTD, *PLISTD;

typedef struct tagLISTI {  /* List record for integers */
  PLISTELEMI Head;         /* First elem in list */
  PLISTELEMI Tail;         /* Last  elem in list */
  PLISTELEMI OriginalHead;
  PLISTELEMI Point_to_Head;
  long       lSize;        /* Number of elems in list */
} LISTI, *PLISTI;

typedef struct tagLISTIJ { /* List record for pairs of integers */
  PLISTELEMIJ Head;        /* First elem in list */
  PLISTELEMIJ Tail;        /* Last  elem in list */
  PLISTELEMIJ OriginalHead;
  PLISTELEMIJ Point_to_Head;
  long        lSize;       /* Number of elems in list */
} LISTIJ, *PLISTIJ;

typedef struct tagLISTL {  /* List record for longs */
  PLISTELEML Head;         /* First elem in list */
  PLISTELEML Tail;         /* Last  elem in list */
  PLISTELEML OriginalHead;
  PLISTELEML Point_to_Head;
  long       lSize;        /* Number of elems in list */
} LISTL, *PLISTL;

typedef struct tagLISTSTR {  /* List record for strings */
  PLISTELEMSTR Head;         /* First elem in list */
  PLISTELEMSTR Tail;         /* Last  elem in list */
  PLISTELEMSTR OriginalHead;
  PLISTELEMSTR Point_to_Head;
  long         lSize;        /* Number of elems in list */
} LISTSTR, *PLISTSTR;

typedef struct tagLIStVAR {  /* List record for strings */
  PLISTELEMVAR Head;         /* First elem in list */
  PLISTELEMVAR Tail;         /* Last  elem in list */
  PLISTELEMVAR OriginalHead;
  PLISTELEMVAR Point_to_Head;
  long         lSize;        /* Number of elems in list */
} LISTVAR, *PLISTVAR;


/* ----------------------------------------------------------------------------
   Prototypes
*/

char*  CopyString (char* szIn);

void   FreedList   (PLISTD   *pplist);
void   FreeiList   (PLISTI   *pplist);
void   FreeijList  (PLISTIJ  *pplist);
void   FreelList   (PLISTL   *pplist);
void   FreeStrList (PLISTSTR *pplist);

PLISTD   InitdList   (void);
PLISTI   InitiList   (void);
PLISTIJ  InitijList  (void);
PLISTL   InitlList   (void);
PLISTSTR InitStrList (void);
PLISTVAR InitVarList (void);

int LookupVarList (PLISTVAR plist, char *cVal, double *dVal);

void   PrintdList   (FILE *pFile, PLISTELEMD   pfrom, PLISTELEMD   pto);
void   PrintiList   (FILE *pFile, PLISTELEMI   pfrom, PLISTELEMI   pto);
void   PrintijList  (FILE *pFile, PLISTELEMIJ  pfrom, PLISTELEMIJ  pto);
void   PrintStrList (FILE *pFile, PLISTELEMSTR pfrom, PLISTELEMSTR pto);
void   PrintVarList (FILE *pFile, PLISTELEMVAR pfrom, PLISTELEMVAR pto);

void   QueuedListItem   (PLISTD   plist, double dVal);
void   QueueiListItem   (PLISTI   plist, int    iVal);
void   QueueijListItem  (PLISTIJ  plist, int    iVal, int jVal);
void   QueuelListItem   (PLISTL   plist, long   lVal);
void   QueueStrListItem (PLISTSTR plist, char  *cVal);

void   UniqueQueueVarListItem (PLISTVAR plist, char  *cVal, double dVal);

void   UniqueQueueiList (PLISTELEMI *plist, int iVal); /* should be rewritten */
int    GetListSize (PLISTELEMI L);

int    PopListi (PLISTI L);
int    PopElemi (LISTELEMI **head);
void   AddElemi (PLISTELEMI *L, int elem);

/* End */

#define LISTS_H_DEFINED
#endif  /* LISTS_H_DEFINED */

