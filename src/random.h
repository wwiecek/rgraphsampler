/* random.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>
*/

#ifndef RANDOM_H_DEFINED


/* ----------------------------------------------------------------------------
   Constants
*/

#define PI           3.1415926535897932384626433
#define SEED_MIN     1.0
#define SEED_MAX     2147483646.0
#define SEED_DEFAULT 314159265.3589793


/* ----------------------------------------------------------------------------
   Type definitions
*/

#ifndef TRUE
typedef int BOOL;
#define TRUE  1
#define FALSE 0
#endif

typedef enum {
  mt19937,
  taus2
} RDM_GEN_NAMES;

typedef struct tagRANDREC {
  double seed, last;
  double mem[50];
  long switchG;
  double memGauss;
} RANDREC;


/* ----------------------------------------------------------------------------
   Prototypes
*/

double LnBB (long x, long n, int a, int b);
double lnDFNormal (double x, double mu, double sd);
double LnGamma (double x);
double LnMultivariateT (double *x, int dim,
                        double **lambda, int df);
double LnPoisson (int n, double lambda);
double LnRatio (double **x, double **vc, int dim,
		            int n_loop, int np, int hyp,
                double diag, double offdiag, int nNodes);
double LnT (double x, double mu, double lambda, int df);
double Randoms (void);
void   InitRandoms (const int rdm_gen_name, double dSeed);

extern int bInit;

/* End */

#define RANDOM_H_DEFINED
#endif  /* RANDOM_H_DEFINED */

