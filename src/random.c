/* random.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>

   Pseudo-random number generating routines and probability densities.
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// #ifndef NO_LIBGSL
// #include <gsl/gsl_rng.h>
// #endif

#include "random.h"
#include "matrices.h"


/* ----------------------------------------------------------------------------
   LnBB

   Log-density of the beta-binomial distribution
*/
double LnBB (long x, long n, int a, int b)
{
  if (a == 1)
    return (// term C(n,x)
            lgamma(n+1) - lgamma(n-x+1)
            // numerator Beta(x+a,n-x+b)
            + lgamma(n-x+b) - lgamma(n+1+b)
            // denominator Beta(a,b)
            + log(b));
  else
    return (// term C(n,x)
            lgamma(n+1) - lgamma(x+1) - lgamma(n-x+1)
            // numerator Beta(x+a,n-x+b)
            + lgamma(x+a) + lgamma(n-x+b) - lgamma(n+a+b)
            // denominator Beta(a,b)
            - lgamma(a) - lgamma(b) + lgamma(a+b));
} /* LnBB */


/* ----------------------------------------------------------------------------
   lnDFNormal
   the log of the normal density function
   0.9189385332046 is log(sqrt(2*PI))
*/
double lnDFNormal (double x, double mu, double sd)
{
  if (sd <= 0.0) {
    printf ("Error: negative or null SD in lnDFNormal\n");
    exit (0);
  }

  return ( -0.9189385332046 - log (sd) - 0.5 * pow ((mu - x)/sd, 2) );
}


/* ----------------------------------------------------------------------------
   LnGamma

   A function to return the natural log of the Gamma function of x.
   Adapted from the algorithm described in the book Numerical Recipes by
   Press et al.
   It can be used to compute factorials since ln(n!) = LnGamma(n + 1)
*/
double LnGamma (double x)
{
  double dSeries, dTemp;

  if ((x == 1) || (x == 2))
    return 0;

  dSeries = 1.000000000190015 +
            76.18009172947146   /  x      -
    86.50532032141677   / (x + 1) +
    24.01409824083091   / (x + 2) -
    1.231739572450155   / (x + 3) +
    1.20865097386617E-3 / (x + 4) -
    5.39523938495E-6    / (x + 5);

  dTemp = x + 4.5;
  dTemp = -dTemp + (x - 0.5) * log (dTemp) + log (2.50662827465 * dSeries);
  return dTemp;

} /* LnGamma */


/* ----------------------------------------------------------------------------
   LnMultivariateT

   Log-density of the multivariate t distribution
   Inputs:
   x: random variable (vector)
   dim: dimension of x
   mu: mean vector, here supposed  to be null.
   lambda: precision (inverse of variance) matrix (will be partly destroyed
           by LU here)
   df: degrees of freedom

   Saves the constant in case to speed up (likely) repeated calls with the
   same df.
*/
double LnMultivariateT (double *x, int dim, /* double *mu, */
                        double **lambda, int df)
{
  static int    stored_df = -1;
  static double stored_constant;
  int           i, j;
  double        dtmp1, dtmp2, log_det;

  /* first term, with ratio of 2 Gamma functions */
  if (df != stored_df) {
    stored_df = df;
    stored_constant = LnGamma((df + dim) * 0.5) - LnGamma(df * 0.5) -
                      dim * 0.5 * log(df * PI);
  }

  /* (x_i - mu)' * Lambda * (x_i - mu) */
  dtmp1 = 0;
  for (j = 0; j < dim; j++) {
    dtmp2 = 0;
    for (i = 0; i < dim; i++) {
      dtmp2 += (x[i] /* - mu[i] */) * lambda[i][j];
    }
    dtmp1 += dtmp2 * ( x[j] /* - mu[j] */ );
  }

  /* determinant of Lambda */
  /* log_det = LnDeterminant_LU (lambda, dim); */
  /* a more stable and a bit faster way should be: */
  log_det = LnDeterminant_Chol (lambda, dim);

  /* remember: this is det of the inverse of Sigma = det(Sigma)^-1)
     hence + 0.5 * log_det in the next line as we need |Sigma|^(-1/2)) */

  return stored_constant + 0.5 * log_det -
         (df + dim) * 0.5 * log(1 + dtmp1 / df);

} /* LnMultivariateT */


/* ----------------------------------------------------------------------------
   LnPoisson

   Return the natural log of the Poisson density of variate n, with rate
   lambda.
*/
double LnPoisson (int n, double lambda)
{
  return (n * log(lambda) - lambda - LnGamma(n + 1));
} /* LnPoisson */


/* ----------------------------------------------------------------------------
   LnRatio

   Log-density of the ratio for prior predictive for loops
   Corresponds to log(C'0) calculation in the paper

   Inputs (notation as in the paper):
   x: random variable (matrix of order p x p)
   vc: sample variance covariance matrix (order m x m)
   n: dimension (number of data points) of x
   m: number of nodes involved in a loop
   k: number of parents + 1
   q: degree of freedom of the Wishart distribution on precision matrix
      (implicitly the scale matrix is the identity matrix, so its
      determinant is 1).

   Constraints:
   q >= m
*/
double LnRatio (double **x, double **vc, int n, int m, int k, int q,
                double diag, double offdiag, int nNodes)
{
  double c0;
  int    i, p;
  double log_det, log_det1;
  static double **kappa; //Inv-Wishart matrix parameter

  /* printf("n loop %d, k %d, q %d \n", m, k, q); */

  p = q + n - k; /* p = IW parameter + n datapoints - n parents - 1 */
  c0 = 0; /* constant term */

  /* Calculate q/2 * log(det(kappa))... if needed */
  if(offdiag != 0.0) {
    if(!kappa) { //initialise kappa (but only if off-diag != 0)
      kappa = InitdMatrix(nNodes, nNodes);
      for(i = 0; i < nNodes; i++) {
        for(int j =0; j < nNodes; j++) {
          if(i==j) { kappa[i][j] = diag;
          } else { kappa[i][j] = offdiag; }
        }
      }
    }
    //we could store det kappa's of different sizes, but for now let's live with this!
    c0 += 0.5 * q * LnDeterminant_Chol(kappa, m);
  } else if(diag != 1.0) { //if there's only diagonal, no need for LnDet()
    c0 += 0.5 * q * m * log(diag);
  }
  /* Calculate MultivariateGamma_Nloop(p) - MultivariateGamma_Nloop(q) */
  for (i = 1; i <= m; i++) {
    c0 += LnGamma((p * 0.5) + (1 - i) * 0.5);
    // printf("c0 (after addition of LnGamma) = %f \n", c0);
    c0 -= LnGamma((q * 0.5) + (1 - i) * 0.5);
    // printf("c0 (after subtraction of LnGamma) = %f \n", c0);
  }

  /* Calculate powers (log-transformed) of 2 and 2Pi */
  c0 += (m * (k - n) * 0.5 * log(2 * PI)) +
        ((m * (n - k) * 0.5) * log(2));
  // printf("c0 (after addition of powers of 2 and 2Pi) = %f \n", c0);

  /* Calculate log determinants of (X'X) and (VC + I) */
  log_det = LnDeterminant_Chol (x, k);

  log_det1 = LnDeterminant_Chol (vc, m);

  return c0 - (m * 0.5 * log_det) - (p * 0.5 * log_det1);

} /* LnRatio */


/* ----------------------------------------------------------------------------
   LnT

   Log-density of the univariate t distribution
   Inputs:
   x: random variable
   mu: mean
   lambda: precision (inverse of variance)
   df: degrees of freedom

   Saves df in case to speed up (likely) repeated calls with the same df.
*/
double LnT (double x, double mu, double lambda, int df)
{
  static int stored_df = -1;
  static double stored_constant;
  double dtmp = (x - mu);

  if (df != stored_df) {
    stored_df = df;
    stored_constant = LnGamma((df + 1) * 0.5) - LnGamma(df * 0.5) -
                      0.5 * log(df * PI);
  }

  return stored_constant + 0.5 * log(lambda) - (df + 1) * 0.5 *
         log(1 + lambda * dtmp * dtmp / df);

} /* LnT */


/* ----------------------------------------------------------------------------
   We have two versions of Randoms() depending whether we use gsl or not
*/


/* ----------------------------------------------------------------------------
   Global definition, private
*/

static RANDREC  vRandRec;
//static int bInit = 0;

/* ----------------------------------------------------------------------------
   Randoms, standalone version

   A decent random number generator, so you don't have to use
   the (probably not so good) system supplied standard C version.

   Randoms() returns random numbers between 0 and 1. The minimum
   returned value is 1/m and the maximum 1 - 1/m. The generator can
   be initialized with InitRandom().

   This generator should be correct on any system for which the
   representattion of reals uses at least a 32-bit mantissa, including
   the sign bit. Its period is about 2^31.

   From PARK SK, MILLER KW: Random number generators: good ones are
   hard to find.  Commun. ACM 1988; 31: 1192. (Version Real 2).
*/
double Randoms (void)
{
#define a  16807.0
#define m  2147483647.0
#define q  127773.0   // m Div a
#define r  2836.0     // m Mod a

  double hi, test;

  hi = (long)(vRandRec.seed / q);
  test = a * (vRandRec.seed - q * hi) - r * hi;

  if (test > 0.0)
    vRandRec.seed = test;
  else
    vRandRec.seed = test + m;

  return (vRandRec.seed / m);

#undef a
#undef m
#undef q
#undef r

} /* Randoms, non-gsl version */


/* ----------------------------------------------------------------------------
   InitRandoms, non-gsl version

   Sets vRandRec.seed to given dSeed, silently corrects an invalid dSeed.
*/
void InitRandoms (const int rdm_gen_name, double dSeed)
{
  if (!bInit) { // initialize
    int bCorrected = 0;

    if (dSeed == 0.0) {
      dSeed = SEED_DEFAULT;
      bCorrected++;
    }

    if (dSeed < 0)
      dSeed = -dSeed; // Don't announce this correction

    if (dSeed < SEED_MIN) {
      dSeed = SEED_MIN + (dSeed/SEED_MIN) / (SEED_MAX-SEED_MIN);
      bCorrected++;
    }

    if (dSeed > SEED_MAX) {
      dSeed = SEED_MIN + (SEED_MAX/dSeed) / (SEED_MAX-SEED_MIN);
      bCorrected++;
    }

    assert ((/* Invalid Seed */ dSeed >= SEED_MIN && dSeed <= SEED_MAX));

    // Assign valid seed

    if (bCorrected)
      printf ("SetSeed():  corrected out of range random number seed\n"
              "Seed must lie in the range [%g, %g]\n"
              "New seed --> %g\n", SEED_MIN, SEED_MAX, dSeed);

    vRandRec.seed = dSeed;

    printf ("GSL not available, "
            "using Park and Miller random number generator.\n\n");

    // next calls to InitRandoms will do nothing
    bInit = 1;
  }

} /* InitRandoms, non-gsl version */



/* end */
