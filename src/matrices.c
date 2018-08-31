/* matrices.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>

   A bunch of matrix utilities
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// #ifndef NO_LIBGSL
// #include <gsl/gsl_matrix.h>
// #include <gsl/gsl_linalg.h>
// #include <gsl/gsl_cblas.h>
// #endif

#include "lexerr.h"
#include "matrices.h"


/* ----------------------------------------------------------------------------
   CopydMatrix

   copies a rectangular matrix of doubles.

   The original matrix "from" and it's copy "to" should be initialized
   properly before.
*/
void CopydMatrix (double **from, long dim1, long dim2, double **to)
{
  register long i, j;

  if ((from == NULL) || to == NULL)
    lexerr ("both matrices passed to CopydMatrix should be initialized");

  for (i = 0; i < dim1; i++)
    for (j = 0; j < dim2; j++)
      to[i][j] = from[i][j];

} /* CopydMatrix */


/* ----------------------------------------------------------------------------
   FreedMatrix

   Free the memory taken by a matrix of doubles. Only the first dimension needs
   to be passed.
*/
void FreedMatrix (double **M, long dim1)
{
  long i;

  for (i = 0; i < dim1; i++)
    free (M[i]);
  free (M);

} /* FreedMatrix */


/* ----------------------------------------------------------------------------
   FreeiMatrix

   Free the memory taken by a matrix of integers. Only the first dimension
   needs to be passed.
*/
void FreeiMatrix (int **M, long dim1)
{
  long i;

  for (i = 0; i < dim1; i++)
    free (M[i]);
  free (M);

} /* FreeiMatrix */


/* ----------------------------------------------------------------------------
   FreelMatrix

   Free the memory taken by a matrix of long integers. Only the first dimension
   needs to be passed.
*/
void FreelMatrix (long **M, long dim1)
{
  long i;

  for (i = 0; i < dim1; i++)
    free (M[i]);
  free (M);

} /* FreelMatrix */


/* ----------------------------------------------------------------------------
   FreeulMatrix

   Free the memory taken by a matrix of unsigned long integers.
   Only the first dimension needs to be passed.
*/
void FreeulMatrix (unsigned long **M, long dim1)
{
  long i;

  for (i = 0; i < dim1; i++)
    free (M[i]);
  free (M);

} /* FreeulMatrix */


/* ----------------------------------------------------------------------------
   InitdMatrix

   initializes a rectangular matrix of doubles and fill it with zeroes.

   The pointer to the matrix is returned if no error occurs, otherwise exit.
   It is an error to call it with null dims.
*/
double **InitdMatrix (long dim1, long dim2)
{
  register long i;
  double **rgp;

  if ((dim1 == 0) || dim2 == 0)
    lexerr ("at least one zero dimension in InitdMatrix");

  if (!(rgp = (double **) malloc(dim1 * sizeof(double *))))
    lexerr ("out of memory in InitdMatrix");

  for (i = 0; i < dim1; i++)
    if (!(rgp[i] = (double *) calloc(dim2, sizeof(double))))
      lexerr ("out of memory in InitdMatrix");

  return (rgp);

} /* InitdMatrix */


/* ----------------------------------------------------------------------------
   InitdVector

   initializes a vector of double and fill it with zeroes.

   The pointer to the vector is returned if no error occurs, otherwise NULL
   is returned. It is an error to call it with dim = 0.
*/
double *InitdVector (long dim)
{
  double *rgp;

  if (dim == 0)
    lexerr ("dimension zero asked in InitdVector");

  if (!(rgp = (double *) calloc(dim, sizeof(double)))) {
    lexerr ("out of memory in InitdVector");
    return (0);
  }
  else
    return (rgp);

} /* InitdVector */


/* ----------------------------------------------------------------------------
   InitiMatrix

   initializes a rectangular matrix of integers and fill it with zeroes.

   The pointer to the matrix is returned if no error occurs, otherwise exit.
   It is an error to call it with null dims.
*/
int **InitiMatrix (long dim1, long dim2)
{
  register long i;
  int **rgp;

  if ((dim1 == 0) || dim2 == 0)
    lexerr ("at least one zero dimension in InitiMatrix");

  if (!(rgp = (int **) malloc(dim1 * sizeof(int *))))
    lexerr ("out of memory in InitiMatrix");

  for (i = 0; i < dim1; i++)
    if (!(rgp[i] = (int *) calloc(dim2, sizeof(int))))
      lexerr ("out of memory in InitiMatrix");

  return (rgp);

} /* InitiMatrix */


/* ----------------------------------------------------------------------------
   InitiVector

   initializes a vector of integers and fill it with zeroes.

   The pointer to the vector is returned if no error occurs, otherwise NULL
   is returned. It is an error to call it with dim = 0.
*/
int *InitiVector (long dim)
{
  int *rgp;

  if (dim == 0)
    lexerr ("dimension zero asked in InitiVector");

  if (!(rgp = (int *) calloc(dim, sizeof(int)))) {
    lexerr ("out of memory in InitiVector");
    return (0);
  }
  else
    return (rgp);

} /* InitiVector */


/* ----------------------------------------------------------------------------
   InitlMatrix

   initializes a rectangular matrix of long integers and fill it with zeroes.

   The pointer to the matrix is returned if no error occurs, otherwise exit.
   It is an error to call it with null dims.
*/
long **InitlMatrix (long dim1, long dim2)
{
  register long i;
  long **rgp;

  if ((dim1 == 0) || dim2 == 0)
    lexerr ("at least one zero dimension in InitlMatrix");

  if (!(rgp = (long **) malloc(dim1 * sizeof(long *))))
    lexerr ("out of memory in InitlMatrix");

  for (i = 0; i < dim1; i++)
    if (!(rgp[i] = (long *) calloc(dim2, sizeof(long))))
      lexerr ("out of memory in InitlMatrix");

  return (rgp);

} /* InitlMatrix */


/* ----------------------------------------------------------------------------
   InitulMatrix

   initializes a rectangular matrix of unsigned long integers and fill it w
   ith zeroes.

   The pointer to the matrix is returned if no error occurs, otherwise exit.
   It is an error to call it with null dims.
*/
unsigned long **InitulMatrix (long dim1, long dim2)
{
  register long i;
  unsigned long **rgp;

  if ((dim1 == 0) || dim2 == 0)
    lexerr ("at least one zero dimension in InitlMatrix");

  if (!(rgp = (unsigned long **) malloc(dim1 * sizeof(unsigned long *))))
    lexerr ("out of memory in InitulMatrix");

  for (i = 0; i < dim1; i++)
    if (!(rgp[i] = (unsigned long *) calloc(dim2, sizeof(unsigned long))))
      lexerr ("out of memory in InitulMatrix");

  return (rgp);

} /* InitulMatrix */


/* ----------------------------------------------------------------------------
   InitlVector

   initializes a vector of long integers and fill it with zeroes.

   The pointer to the vector is returned if no error occurs, otherwise NULL
   is returned. It is an error to call it with dim = 0.
*/
long *InitlVector (long dim)
{
  long *rgp;

  if (dim == 0)
    lexerr ("dimension zero asked in InitlVector");

  if (!(rgp = (long *) calloc(dim, sizeof(long)))) {
    lexerr ("out of memory in InitlVector");
    return (0);
  }
  else
    return (rgp);

} /* InitlVector */


/* ----------------------------------------------------------------------------
   InitulVector

   initializes a vector of unsigned long integers and fill it with zeroes.

   The pointer to the vector is returned if no error occurs, otherwise NULL
   is returned. It is an error to call it with dim = 0.
*/
unsigned long *InitulVector (long dim)
{
  unsigned long *rgp;

  if (dim == 0)
    lexerr ("dimension zero asked in InitlVector");

  if (!(rgp = (unsigned long *) calloc(dim, sizeof(unsigned long)))) {
    lexerr ("out of memory in InitulVector");
    return (0);
  }
  else
    return (rgp);

} /* InitulVector */


/* ----------------------------------------------------------------------------
   PrintdMatrix

   Print a square double matrix of size dim.
*/
void PrintdMatrix (FILE *pFile, int dim, double **pdMat)
{
  register int i, j;

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim-1; j++) {
      fprintf(pFile, "%g\t", pdMat[i][j]);
    }
    fprintf(pFile, "%g\n", pdMat[i][j]);
  }
  fprintf(pFile, "\n");

} /* PrintdMatrix */


/* ----------------------------------------------------------------------------
   PrintiMatrix

   Print a square integer matrix of size dim.
*/
void PrintiMatrix (FILE *pFile, int dim, int **piMat)
{
  register int i, j;

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim-1; j++) {
      fprintf(pFile, "%d ", piMat[i][j]);
    }
    fprintf(pFile, "%d\n", piMat[i][j]);
  }
  fprintf(pFile, "\n");

} /* PrintiMatrix */


/* ----------------------------------------------------------------------------
   PrintlMatrix

   Print a square long integer matrix of size dim.
*/
void PrintlMatrix (FILE *pFile, int dim, long **plMat)
{
  register int i, j;

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim-1; j++) {
      fprintf(pFile, "%ld ", plMat[i][j]);
    }
    fprintf(pFile, "%ld\n", plMat[i][j]);
  }
  fprintf(pFile, "\n");

} /* PrintlMatrix */


/* ----------------------------------------------------------------------------
   PrintSortediMatrix

   Print a square integer matrix of size dim in the order of rows and columns
   specified by pIndex.
*/
void PrintSortediMatrix (FILE *pFile, int dim, int **piMat, int *pindex)
{
  int i, j;

  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim-1; j++) {
      fprintf(pFile, "%d ", piMat[pindex[i]][pindex[j]]);
    }
    fprintf(pFile, "%d\n", piMat[pindex[i]][pindex[j]]);
  }
  fprintf(pFile, "\n");

} /* PrintSortediMatrix */


/* ----------------------------------------------------------------------------
   LU_decomposition

   Does the LU decomposition of a matrix M:
   Compute the matrices L and U such that M = LU.

   Given a matrix M[1..dim][1..dim], this routine replaces it by the LU
   decomposition of a rowwise permutation of itself. M and dim are input.
   M is output and M's lower triangle is destroyed in the process.

   The determinant sign (detsign) is output as +/- 1 depending on whether
   the number of row interchanges was even or odd, respectively.
*/
void LU_decomposition (double **M, int dim, int *detsign)
{
  register int i, j, k;
  int imax;
  double big, temp, sum, dum;
  static int old_dim = -1;
  static double *pdTmp = NULL; // stores the implicit scaling of each row

  if (old_dim != dim) {
    if (pdTmp)
      free(pdTmp);
    pdTmp = InitdVector(dim);
    old_dim = dim;
  }

  *detsign = 1;  // No row interchanges yet
  for (i = 0; i < dim; i++) {
    // Loop over rows to get the implicit scaling information
    big = 0.0;
    for (j = 0; j < dim; j++) {
      temp = fabs(M[i][j]);
      if (temp > big)
        big = temp;
    }
    if (big == 0.0) // checking for no nonzero largest element
      lexerr ("singular matrix in routine LU_decomposition");

    pdTmp[i] = 1.0 / big; // save the scaling
  } // for i

  for (j = 0; j < dim; j++) { // loop over columns of Crout's method

    for (i = 0; i < j; i++) {
      sum = M[i][j];
      for (k = 0; k < i; k++) {
        sum -= M[i][k] * M[k][j];
      }
      M[i][j] = sum;
    }

    big = 0.0; // Initialize for the search for largest pivot element

    for (i = j; i < dim; i++) {
      sum = M[i][j];
      for (k = 0; k < j; k++) {
        sum -= M[i][k] * M[k][j];
      }
      M[i][j] = sum;

      dum = pdTmp[i] * fabs(sum);
      // Is the figure of merit for the pivot better than the best so far?
      if (dum >= big) {
        big = dum;
        imax = i;
      }
    } // for i

    // Do we need to interchange rows?
    if (j != imax) { // Yes, do so...
      for (k = 0; k < dim; k++) {
        dum = M[imax][k];
        M[imax][k] = M[j][k];
        M[j][k] = dum;
      }
      *detsign = -(*detsign); // change the determinant sign
      pdTmp[imax] = pdTmp[j]; // interchange the scale factor
    } // if j

    /* if the pivot element is zero the matrix is singular
       (at least to the precision of the algorithm).
       For some applications on singular matrices,
       it is desirable to substitute TINY for zero */
    if (M[j][j] == 0.0) {
      M[j][j] = TINY;
    }

    if (j != (dim - 1)) { // finally, divide by the pivot element
      dum = 1.0 / (M[j][j]);
      for (i = j+1; i < dim; i++)
        M[i][j] *= dum;
    }
  }

} /* LU_decomposition */


/* ----------------------------------------------------------------------------
   Determinant obtained by LU_decomposition, non-gsl version
*/
double Determinant_LU (double **M, int dim)
{
  int i, detsign;
  double det;

  LU_decomposition (M, dim, &detsign);

  det = detsign;
  for (i = 0; i < dim; i++)
    det *= M[i][i];

  return (det);

} /* Determinant_LU */


/* ----------------------------------------------------------------------------
   Log-determinant obtained by LU_decomposition, non-gsl version

   Checks for positive definiteness
*/
double LnDeterminant_LU (double **M, int dim)
{
  int i, detsign;
  double lndet = 0;

  LU_decomposition (M, dim, &detsign);

  for (i = 0; i < dim; i++) {
    if (M[i][i] < 0)
      detsign *= -1;
    else
      if (M[i][i] == 0) {
        detsign = 0;
        break;
      }
    lndet += log(fabs(M[i][i]));
  }
  if (detsign <= 0) {
    printf("Error: non positive-definite matrix in LnDeterminant - "
           "Exiting.\n\n");
    exit(0);
  }

  return(lndet);

} /* LnDeterminant_LU */


/* ----------------------------------------------------------------------------
   Cholesky

   Performs a Cholesky decomposition of an Hermitian matrix M:
   Compute the matrix L such that M = LL*.

   Returns 0 if successful, -1 otherwise.
   Matrix M lower triangle is destroyed in the process.
*/
int Cholesky (double **M, double **prgdComponent, int dim)
{
  register int i, j, k;
  double dSum;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      prgdComponent[i][j] = 0.0;

  for (i = 0; i < dim; i++) {
    for (j = i; j < dim ; j++) {
      dSum = M[i][j];
      for (k = i - 1; k >= 0 ; k--)
        dSum = dSum - M[i][k] * M[j][k];

      if (i == j) {
        if (dSum <= 0.0) {
          printf ("Error: input matrix for Cholesky is not "
                  "positive definite\n");
          printf ("\ndSum = %g\n", dSum);
          exit(0);
        }
        else
          prgdComponent[i][i] = sqrt(dSum);
      }
      else
        M[j][i] = dSum / prgdComponent[i][i];
    } /* end for j */
  }

  for (i = 0; i < dim ; i++)
    for (j = i+1; j < dim ; j++)
      prgdComponent[j][i] = M[j][i];

  /* success */
  return(1);

} /* Cholesky */


/* ----------------------------------------------------------------------------
   InvertMatrix_Chol

   Inverts matrix M using Cholesky decomposition.
   Matrix M is replaced by its inverse.
*/
void InvertMatrix_Chol (double **M, int dim)
{
  register int i, j, k;
  double dSum;

  Cholesky (M, pdWorkMatrixSizeN, dim);

  /* invert pdWorkMatrixSizeN */
  for (i = 0; i < dim; i++) {
    for (j = 0; j <= i; j++) {
      dSum = (i == j ? 1.0 : 0.0);
      for (k = i - 1; k >= j; k--)
        dSum -= pdWorkMatrixSizeN[i][k] * M[j][k];
      M[j][i] = dSum / pdWorkMatrixSizeN[i][i];
    }
  }

  /* multiply by t(pdWorkMatrixSizeN) */
  for (i = dim-1; i >= 0; i--) {
    for (j = 0; j <= i; j++) {
      dSum = (i < j ? 0.0 : M[j][i]);
      for (k = i + 1; k < dim; k++)
        dSum -= pdWorkMatrixSizeN[k][i] * M[j][k];
      M[i][j] = M[j][i] = dSum / pdWorkMatrixSizeN[i][i];
    }
  }

} /* InvertMatrix_Chol */


/* ----------------------------------------------------------------------------
   Log-determinant using Cholesky decomposition

   The determinant is the sum of the squares of the diagonal elements of
   the decomposition L matrix
*/
double LnDeterminant_Chol (double **M, int dim)
{
  register int i;
  double det = 0;
  static int local_dim = 0;
  static double ** L = NULL; /* freeing it is costly; make it global? */

  if (dim > local_dim) {
    if (L) {
      for (i = 0; i < local_dim; i++)
	free(L[i]);
      free (L);
    }
    L = InitdMatrix (dim, dim);
    local_dim = dim;
  }

  Cholesky (M, L, dim);

  for (i = 0; i < dim; i++)
    det += log(L[i][i]);

  return (2 * det);

} /* LnDeterminant_Chol */


/* End */
