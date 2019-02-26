/* outputs.h

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 
*/

#ifndef OUTPUTS_H_DEFINED


/* ----------------------------------------------------------------------------
   Type definitions
*/

#ifndef TRUE
typedef int BOOL;
#define TRUE  1
#define FALSE 0
#endif

typedef struct tagBITBUFFER { /* bit-packing buffer structure */
  unsigned int buffer;
  unsigned int max_mask;
  unsigned int mask;
} BITBUFFER, *PBITBUFFER;


/* ----------------------------------------------------------------------------
   Constants
*/

#define MAXFILENAME  100


/* ----------------------------------------------------------------------------
   Global declarations
*/

// flags to turn on/off outputs and associated computations
BOOL   bsave_the_chain;
BOOL   bsave_best_graph;
BOOL   bsave_the_edge_probabilities;
BOOL   bsave_the_degree_counts;
BOOL   bsave_the_motifs_probabilities;
BOOL   bsave_some_graphs;

unsigned long nNextPrint, nPrintStep;

unsigned long n_saved_adjacency; // avoid huge numbers though!

// output files
FILE   *pChainFile;          // binary output file for the chain
FILE   *pInvTemperatureFile; // text output file for inverse temperatures
FILE   *pEdgeFile;           // text output file for the edge probabilities
FILE   *pDegreeFile;         // text output file for cumulated degree counts
FILE   *pMotifFile;          // text output file for E and F loops counts
FILE   *pGraphsFile;         // text output for random adjancency matrices
FILE   *pBestFile;           // text output for best adjancency matrices
FILE   *pImputedFile;        // text output for imputed data
FILE   *pConvergenceFile;    // text output for imputed data

// externals, to be defined elsewhere
extern BOOL   bBN;                 // sample Bayesian networks
extern BOOL   bDBN;                // sample dynamic Bayesian networks
extern BOOL   bData;               // flag the availability of data
extern BOOL   bNAData;             // flag for missing data
extern int    **best_adj;          // max probability adjacency matrix sampled
extern int    **current_adj;       // current adjacency matrix
extern double *cumdegree_count;
extern double cum_nEloops;         // cumulated number of Endless loops
extern double cum_nFloops;         // cumulated number of Frustrated loops
extern double current_logprior;
extern double current_loglikelihood;
extern double current_logposterior;
extern double dBestPrior;          /* prior of the max posterior graph */
extern double dBestLikelihood;     /* likelihood of the max posterior graph */
extern double dBestPosterior;      /* highest graph probability found */
extern double **mat_sum;           /* cumulated edges counts over graphs */
extern int    nNodes;              /* the number of nodes in graph */
extern int    bConvergence_std;    /* check convergence over an interval */
extern BOOL   bConvergence_inc;    /* check convergence at every step */

extern unsigned long iter;
extern unsigned long nBurnin;
extern unsigned long nRuns;


/* ----------------------------------------------------------------------------
   Prototypes
*/

void CloseOutputs (char *const prefixname);
void CreateFileName (char *const filename, char *const prefixname,
                     char *const suffixname);
void InitBuffer (PBITBUFFER buf);
void InitOutputs (char *const filename);
int  Read_diff_buffered (FILE *pChainFile, PBITBUFFER buf, int *diff);
int  ReadBitOffBuffer (FILE *pChainFile, PBITBUFFER buf, int *bit);
void ReadChain ();
void SaveBestGraph (void);
void SaveChain (int to_out);
void SaveConvergence (FILE *outFile, double *pdmat_gmean, double *pdmat_vari,
                      double *pdmat_gvari, double *pdmat_rhat, double dmaxRhat);
void SaveDegreeCounts (void);
void SaveEdgeP (FILE *outFile);
void SaveGraph (void);
void SaveInverseTemperature (void);
void SaveMotifsP (FILE *outFile);
void WriteBitToBuffer (PBITBUFFER buf, int to_out);

/* End */

#define OUTPUTS_H_DEFINED
#endif  /* OUTPUTS_H_DEFINED */

