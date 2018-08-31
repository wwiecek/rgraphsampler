/* matrices.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 
*/

#ifndef MATRICES_H_DEFINED


/* ----------------------------------------------------------------------------
   Constants
*/

#define TINY  1.0e-20


/* ----------------------------------------------------------------------------
   Prototypes
*/

void   CopydMatrix (double **from, long dim1, long dim2, double **to);

void   FreedMatrix(double **M, long dim1);
void   FreeiMatrix(int    **M, long dim1);
void   FreelMatrix(long   **M, long dim1);
void   FreeulMatrix(unsigned long **M, long dim1);

double **InitdMatrix(long dim1, long dim2);
int    **InitiMatrix(long dim1, long dim2);
long   **InitlMatrix(long dim1, long dim2);
unsigned long **InitulMatrix (long dim1, long dim2);

double *InitdVector(long dim);
int    *InitiVector(long dim);
long   *InitlVector(long dim);
unsigned long *InitulVector (long dim);

void   PrintdMatrix (FILE *pFile, int dim, double **pdMat);
void   PrintiMatrix (FILE *pFile, int dim, int    **piMat);
void   PrintlMatrix (FILE *pFile, int dim, long   **plMat);
void   PrintSortediMatrix (FILE *pFile, int dim, int **piMat, int *pindex);

void   InvertMatrix_Chol (double **M, int dim);

double Determinant_LU       (double **M, int dim);
double LnDeterminant_LU     (double **M, int dim);
double LnDeterminant_Chol   (double **M, int dim);


/* ----------------------------------------------------------------------------
   Global declarations
*/

extern double **pdWorkMatrixSizeN; // need to be defined, inited and freed
                                   // by the caller


/* End */

#define MATRICES_H_DEFINED
#endif  /* _MATRICES_H_ */

