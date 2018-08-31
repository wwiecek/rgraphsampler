/* convergence.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/>
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include "convergence.h"


/* ----------------------------------------------------------------------------
   Read_chain

   Check the convergence of a set of MCMC chains, using Gelman and Rubin Rhat
   criterion. The binary chain files are used.
   The array parameters pdmat_gmean and pdmat_vari are initialized and filled.
*/
void Read_chain (FILE **rgpFiles, double **pdmat_gmean, double **pdmat_vari)
{
  unsigned long i, j, k, l, m, N;
  int           nTmp, diff;
  BOOL          stop;
  int           *pimat_adj = NULL;
  unsigned long *plmat_sum, *plmat_gsum;
  double        *pdmat_mean;

  /* print on screen the samples to read */
  if (nConvergence_end == 0)
    printf("Reading samples [%ld to final].\n", nConvergence_start);
  else
    printf("Reading samples [%ld to %ld].\n", nConvergence_start,
           nConvergence_end);

  /* open the files and read the number of nodes */
  for (i = 0; i < nChains; i++) {

    if (!(rgpFiles[i] = fopen(pChainNames[i], "r"))) {
      printf ("\nError: cannot open file %s - Exiting\n\n", pChainNames[i]);
      exit (0);
    }

    printf ("\nReading chain file %s.\n", pChainNames[i]);

    /* read the number of nodes */
    if (!fread (&nTmp, sizeof(int), 1, rgpFiles[i]))
      lexerr("cannot read the number of nodes");

    if ((nNodes != 0) && (nTmp != nNodes)) {
      printf ("\nDimension: %d\n", nTmp); 
      lexerr("nNodes specified and found differ (or differ between chains)");
    }
    else
      nNodes = nTmp;

  } /* for each file */

  /* now that we have nNodes set or checked, initialize working arrays */
  pimat_adj  = InitiVector(nNodes * nNodes);
  pdmat_mean = InitdVector(nNodes * nNodes);

  plmat_sum  = InitulVector(nNodes * nNodes);
  plmat_gsum = InitulVector(nNodes * nNodes);
  
  *pdmat_gmean = InitdVector(nNodes * nNodes); /* is a parameter */
  *pdmat_vari  = InitdVector(nNodes * nNodes); /* is a parameter */

  static BITBUFFER buf;
  
  for (i = 0; i < nChains; i++) {

    /* read the initial adjacency matrix (flat) */

    InitBuffer(&buf);
    
    for (j = 0; j < nNodes * nNodes; j++)
      if (!ReadBitOffBuffer(rgpFiles[i], &buf, &(pimat_adj[j])))
        lexerr("cannot read the initial adjacency matrix");

    if (nNodes < LARGE_N) { /* for small matrices */
      printf("\nChain %ld initial adjacency matrix:\n", i+1);
      for (j = 0; j < nNodes; j++) {
        for (k = 0; k < nNodes; k++)
          printf("%d ", pimat_adj[j+k*nNodes]);
        printf("\n");
      }
    }

    /* initialize an edge summation matrix if starting at iteration zero */
    if (nConvergence_start == 0)
      for (j = 0; j < nNodes * nNodes; j++) 
        plmat_sum[j] = pimat_adj[j];

    /* iterate through the file, matrix by matrix,
       coded by difference as signed integer 
       and reconstruct the adjacency matrix at each step */

    j = m = 0;
    stop = FALSE;

    do {

      k = Read_diff_buffered(rgpFiles[i], &buf, &diff);
      if (k < 1) {
        if (k == 0) {
          printf("End of chain after %ld reads, proceeding with that...\n", j);
          break;
        }
        else
          lexerr ("unknown reading error");
      }

      if (diff > 0)
        pimat_adj[m]++;
      if (diff < 0)
        pimat_adj[m]--;

      /* cumulate the adjacency matrices, i.e. cumulate edge counts */
      if ((j + 1) == nConvergence_start) 
        for (l = 0; l < nNodes * nNodes; l++)
          plmat_sum[l] = pimat_adj[l];
      else
        if ((j + 1) > nConvergence_start)
          for (l = 0; l < nNodes * nNodes; l++)
            plmat_sum[l] = plmat_sum[l] + pimat_adj[l];

      j++;
      m++;
      if (m == nNodes * nNodes)
        m = 0;

      if ((nConvergence_end != 0) && (j == nConvergence_end))
	stop = TRUE;

    } while (!stop);

    nConvergence_end = j;

    /* close file */
    fclose (rgpFiles[i]);

    if (i == 0)
      N = nConvergence_end - nConvergence_start + 1;
    else {
      if ((nConvergence_end - nConvergence_start + 1) != N)
        lexerr("chain length differ");
    }
    
    /* edge probability matrix estimate: */
    for (l = 0; l < nNodes * nNodes; l++)
      pdmat_mean[l] = plmat_sum[l] / (double) N;

    if (nNodes < LARGE_N) { /* for small matrices */
      printf("\nEdge probabilities for chain %ld:\n", i+1);
      for (j = 0; j < nNodes; j++) {
        for (k = 0; k < nNodes; k++)
          printf("%5.3f ", pdmat_mean[j+k*nNodes]);
        printf("\n");
      }
    }

    /* cumulate the variances of each probability (equal to (mean)(1 - mean)) */
    for (l = 0; l < nNodes * nNodes; l++)
      (*pdmat_vari)[l] = (*pdmat_vari)[l] + pdmat_mean[l] * (1 - pdmat_mean[l]);

    /* accumulate sums to form the inter-chain variance */
    for (l = 0; l < nNodes * nNodes; l++) {
      plmat_gsum[l] = plmat_gsum[l] + plmat_sum[l];
    }

  } /* end for i files */

  /* inter-chain means */
  for (l = 0; l < nNodes * nNodes; l++)
    (*pdmat_gmean)[l] = plmat_gsum[l] / (nChains * (double) N);

  /* free local working arrays */
  free(pimat_adj);
  free(plmat_sum);
  free(plmat_gsum);
  free(pdmat_mean);

} /* Read_chain */


/* ----------------------------------------------------------------------------
   Read_edgeP

   Check the convergence of a set of MCMC chains, using Gelman and Rubin Rhat
   criterion. Edge probabilities files are used.
   The array parameters pdmat_gmean and pdmat_vari are initialized and filled.
*/
void Read_edgeP (FILE **rgpFiles, double **pdmat_gmean, double **pdmat_vari)
{
  unsigned long i, j, k;
  double        *pdmat_mean;

  /* initialize working matrices (vectors in fact!) */
  pdmat_mean = InitdVector (nNodes * nNodes);

  /* start and end user values are ignored */
  if (nConvergence_start != 0)
    printf("Warning: convergence from edge probabilities ignores "
	   "start_at_iter.\n");
  if (nConvergence_end != 0)  
    printf("Warning: convergence from edge probabilities ignores "
	   "end_at_iter.\n");

  if (nNodes == 0)
    lexerr("when convergence from edge probabilities, n_nodes must be given");
  
  /* now that we have nNodes set or checked, initialize working arrays */
  *pdmat_gmean = InitdVector(nNodes * nNodes); /* is a parameter */
  *pdmat_vari  = InitdVector(nNodes * nNodes); /* is a parameter */

  /* open the files */
  for (i = 0; i < nChains; i++)
    if (!(rgpFiles[i] = fopen(pChainNames[i], "r"))) {
      printf ("\nError: cannot open file %s - Exiting\n\n", pChainNames[i]);
      exit (0);
    }

  /* read each file */
  for (i = 0; i < nChains; i++) {

    printf ("\nReading edge probabilities in file %s.\n", pChainNames[i]);

    for (j = 0; j < nNodes; j++)
      for (k = 0; k < nNodes; k++)
        if (fscanf(rgpFiles[i], "%lg", &(pdmat_mean[j+k*nNodes])) != 1)
          lexerr("unable to read all edge probabilities from file");

    /* close file */
    fclose (rgpFiles[i]);

    if (nNodes < LARGE_N) { /* for small matrices */
      printf("\nEdge probabilities for chain %ld:\n", i+1);
      for (j = 0; j < nNodes; j++) {
        for (k = 0; k < nNodes; k++)
          printf("%5.3f ", pdmat_mean[j+k*nNodes]);
        printf("\n");
      }
    }

    /* cumulate the variances of each probability (equal to (mean)(1 - mean)) */
    for (j = 0; j < nNodes * nNodes; j++)
      (*pdmat_vari)[j] = (*pdmat_vari)[j] + pdmat_mean[j] * (1 - pdmat_mean[j]);

    /* accumulate edge probabilities to form their average across chains */
    if (i == 0)
      for (j = 0; j < nNodes * nNodes; j++)
        (*pdmat_gmean)[j] = pdmat_mean[j];
    else
      for (j = 0; j < nNodes * nNodes; j++)
        (*pdmat_gmean)[j] = (*pdmat_gmean)[j] + pdmat_mean[j];

  } /* end for i files */

  /* inter-chain means */
  for (j = 0; j < nNodes * nNodes; j++)
    (*pdmat_gmean)[j] = (*pdmat_gmean)[j] / ((double) nChains);

  /* free local working arrays */
  free(pdmat_mean);

} /* Read_edgeP */


/* ----------------------------------------------------------------------------
   Convergence_incremental

   Check the convergence of a set of MCMC chains, using Gelman and Rubin Rhat
   criterion, at each iteration.
   The array parameters pdmat_gmean, pdmat_vari, pdmat_gvari, and pdmat_rhat
   are initialized and filled, but used only internally.
*/
void Convergence_incremental (FILE **rgpFiles)
{
  unsigned long i, j, k, l, m, N;
  int           nTmp, diff;
  BOOL          stop;
  double        dmaxRhat;

  unsigned long *plmat_gsum;
  double        *pdmat_vari;
  double        *pdmat_gmean;
  double        *pdmat_gvari;
  double        *pdmat_rhat;

  int           **pimat_adj;
  unsigned long **plmat_sum;
  double        **pdmat_mean;

  static PBITBUFFER bufs;
  if (!(bufs = (BITBUFFER *) calloc(nChains, sizeof(BITBUFFER))))
    lexerr ("out of memory in Convergence_incremental");
  for (i = 0; i < nChains; i++)
    InitBuffer(&(bufs[i]));

  /* print on screen the samples to read */
  if (nConvergence_end == 0)
    printf("Reading samples [%ld to final].\n", nConvergence_start);
  else
    printf("Reading samples [%ld to %ld].\n", nConvergence_start,
           nConvergence_end);

  /* write convergence output file header */
  fprintf(pConvergenceFile, "Convergence analysis results; Files used: ");
  for (j = 0; j < nChains; j++)
    fprintf(pConvergenceFile, "%s, ", pChainNames[j]);
  if (nConvergence_end == 0)
    fprintf(pConvergenceFile, "with samples [%ld to final].\n\n",
            nConvergence_start);
  else
    fprintf(pConvergenceFile, "with samples [%ld to %ld].\n\n",
            nConvergence_start, nConvergence_end);

  fprintf(pConvergenceFile, "iter\tmaxRhat\n");

  /* open the files and read the number of nodes */
  for (i = 0; i < nChains; i++) {

    if (!(rgpFiles[i] = fopen(pChainNames[i], "r"))) {
      printf ("\nError: cannot open file %s - Exiting\n\n", pChainNames[i]);
      exit (0);
    }

    printf ("\nReading chain file %s.\n", pChainNames[i]);

    /* read the number of nodes */
    if (!fread (&nTmp, sizeof(int), 1, rgpFiles[i]))
      lexerr("cannot read the number of nodes");

    if ((nNodes != 0) && (nTmp != nNodes)) {
      printf ("\nDimension: %d\n", nTmp); 
      lexerr("nNodes specified and found differ (or differ between chains)");
    }
    else
      nNodes = nTmp;

  } /* for each file */

  /* now that we have nNodes set or checked, initialize working arrays */
  pimat_adj   = InitiMatrix(nChains, nNodes * nNodes);
  pdmat_mean  = InitdMatrix(nChains, nNodes * nNodes);

  plmat_sum   = InitulMatrix(nChains, nNodes * nNodes);

  pdmat_vari  = InitdVector(nNodes * nNodes);
  pdmat_gmean = InitdVector(nNodes * nNodes);
  pdmat_gvari = InitdVector(nNodes * nNodes);
  pdmat_rhat  = InitdVector(nNodes * nNodes);

  plmat_gsum  = InitulVector(nNodes * nNodes);
  
  for (i = 0; i < nChains; i++) {

    /* read the initial adjacency matrix (flat!) */
    /* packed bit format version */
    for (j = 0; j < nNodes * nNodes; j++)
      if (!ReadBitOffBuffer(rgpFiles[i], &(bufs[i]), &(pimat_adj[i][j])))
        lexerr("cannot read the initial adjacency matrix");

    if (nNodes < LARGE_N) { /* for small matrices */
      printf("\nChain %ld initial adjacency matrix:\n", i+1);
      for (j = 0; j < nNodes; j++) {
        for (k = 0; k < nNodes; k++)
          printf("%d ", pimat_adj[i][j+k*nNodes]);
        printf("\n");
      }
    }

    /* initialize an edge summation matrix if starting at iteration zero */
    if (nConvergence_start == 0)
      for (j = 0; j < nNodes * nNodes; j++) 
        plmat_sum[i][j] = pimat_adj[i][j];

  } /* for each file */

  /* iterate through the files, like in parallel, matrix by matrix,
     coded by difference as signed integer 
     and reconstruct the adjacency matrices at each step */

  j = m = 0;
  stop = FALSE;

  do {

    /* read the adjacency matrices changes */
    for (i = 0; i < nChains; i++) {

      k = Read_diff_buffered(rgpFiles[i], &(bufs[i]), &diff);
      if (k < 1) {
        if (k == 0) {
          printf("End of shortest chain after %ld reads, "
                 "proceeding with that...\n", j);
          break;
        }
        else
          lexerr ("unknown reading error");
      }

      if (diff > 0)
        pimat_adj[i][m]++;
      if (diff < 0)
        pimat_adj[i][m]--;

      /* cumulate the adjacency matrices, i.e. cumulate edge counts */
      if ((j + 1) == nConvergence_start) 
        for (l = 0; l < nNodes * nNodes; l++)
          plmat_sum[i][l] = pimat_adj[i][l];
      else
        if ((j + 1) > nConvergence_start)
          for (l = 0; l < nNodes * nNodes; l++)
            plmat_sum[i][l] += pimat_adj[i][l];

    } /* for chain i */

    j++; /* one more iteration read */
    m++;
    if (m == nNodes * nNodes)
      m = 0;

    N = j - nConvergence_start + 1;

    if (N > 0) {
      for (i = 0; i < nChains; i++) {
        for (l = 0; l < nNodes * nNodes; l++) {
          /* edge probability matrices */
          pdmat_mean[i][l] = plmat_sum[i][l] / (double) N;

          /* cumulate the intra-chain variances (equal to (mean)(1 - mean)) */
          if (i == 0)
            pdmat_vari[l] = pdmat_mean[i][l] * (1 - pdmat_mean[i][l]);
          else
            pdmat_vari[l] += pdmat_mean[i][l] * (1 - pdmat_mean[i][l]);
        }
      } /* for i chains */

      /* intra-chain variance */
      for (l = 0; l < nNodes * nNodes; l++) {
        pdmat_vari[l] = pdmat_vari[l] / nChains;
      }

      /* accumulate sums to form the inter-chain mean and variance */
      for (l = 0; l < nNodes * nNodes; l++) {
        plmat_gsum[l] = plmat_sum[0][l];
      }
      for (i = 1; i < nChains; i++) {
        for (l = 0; l < nNodes * nNodes; l++) {
          plmat_gsum[l] += plmat_sum[i][l];
        }
      }

      /* inter-chain means */
      for (l = 0; l < nNodes * nNodes; l++)
        pdmat_gmean[l] = plmat_gsum[l] / (nChains * (double) N);

      /* inter-chain variance */
      for (l = 0; l < nNodes * nNodes; l++) {
        pdmat_gvari[l] = pdmat_gmean[l] * (1 - pdmat_gmean[l]);
      }

      /* R_hat ratio of inter over intra-chain variances */
      dmaxRhat = 0;
      for (l = 0; l < nNodes * nNodes; l++) {
        // do not do the diagonal for BNs
        if (!((l % (nNodes+1) == 0) && bBN)) {
          if (pdmat_vari[l] != 0)
            pdmat_rhat[l] = pdmat_gvari[l] / pdmat_vari[l];
          else { /* zero intra-chain variance */
            if (pdmat_gvari[l] == 0)
              pdmat_rhat[l] =  1;
            else
              pdmat_rhat[l] = -1; /* means infinite */
          }

          if (pdmat_rhat[l] > dmaxRhat) 
            dmaxRhat = pdmat_rhat[l];
        }
	else
          pdmat_rhat[l] = 1;
      } /* for l */

      /* write max Rhat to convergence output file */
      fprintf(pConvergenceFile, "%ld\t%g\n", j, dmaxRhat);

    } /* if N > 0) */

    if ((nConvergence_end != 0) && (j == nConvergence_end))
      stop = TRUE;

  } while (!stop);

  SaveConvergence(stdout, pdmat_gmean, pdmat_vari, pdmat_gvari,
                  pdmat_rhat, dmaxRhat);

  SaveConvergence(pConvergenceFile, pdmat_gmean, pdmat_vari, pdmat_gvari,
                  pdmat_rhat, dmaxRhat);

  /* close input files */
  for (i = 0; i < nChains; i++)
    fclose (rgpFiles[i]);

  FreeiMatrix(pimat_adj,  nNodes);
  FreedMatrix(pdmat_mean, nNodes);

  FreeulMatrix(plmat_sum,  nNodes);
  
  free(pdmat_vari);
  free(plmat_gsum);
  free(pdmat_gmean);
  free(pdmat_gvari);
  free(pdmat_rhat);
  free(bufs);

} /* Convergence_incremental */


/* ----------------------------------------------------------------------------
   ConvergenceAnalysis

   Check the convergence of a set of MCMC chains, using Gelman and Rubin Rhat
   criterion.
*/
void ConvergenceAnalysis (void)
{
  unsigned long l;
  double        dmaxRhat;

  double *pdmat_gmean = NULL, *pdmat_vari = NULL;
  double *pdmat_gvari = NULL, *pdmat_rhat = NULL;

  FILE   **rgpFiles; /* Array of files to process */

  /* allocate space for the files pointers */
  if (!(rgpFiles = (FILE**) malloc(nChains * sizeof(FILE*))))
    lexerr("out of memory");

  /* orient to different convergence checks */
  if (bConvergence_inc) {
    printf("Checking convergence incrementally.\n\n");

    Convergence_incremental(rgpFiles);
  }
  else {
    printf("Checking convergence.\n\n");

    if (bConvergence_std == 1)
      Read_chain(rgpFiles, &pdmat_gmean, &pdmat_vari);

    if (bConvergence_std == 2)
      Read_edgeP (rgpFiles, &pdmat_gmean, &pdmat_vari);

    /* now that we have nNodes set or checked, initialize working arrays */
    pdmat_gvari = InitdVector(nNodes * nNodes);
    pdmat_rhat  = InitdVector(nNodes * nNodes);

    for (l = 0; l < nNodes * nNodes; l++) {
      /* intra-chain variances */
      pdmat_vari[l] = pdmat_vari[l] / nChains;

      /* inter-chain variances */
      pdmat_gvari[l] = pdmat_gmean[l] * (1 - pdmat_gmean[l]);
    }

    /* R_hat ratios of inter over intra-chain variances */
    dmaxRhat = 0;
    for (l = 0; l < nNodes * nNodes; l++) {
      // do not do the diagonal for BNs
      if (!((l % (nNodes+1) == 0) && bBN)) {
        if (pdmat_vari[l] != 0)
          pdmat_rhat[l] = pdmat_gvari[l] / pdmat_vari[l];
        else { /* zero intra-chain variance */
          if (pdmat_gvari[l] == 0)
            pdmat_rhat[l] =  1;
          else
            pdmat_rhat[l] = -1; /* means infinite */
        }

        if (pdmat_rhat[l] > dmaxRhat) 
          dmaxRhat = pdmat_rhat[l];
      }
      else
        pdmat_rhat[l] = 1;
    } /* for l */
  
    /* write the results */
    SaveConvergence(pConvergenceFile, pdmat_gmean, pdmat_vari, pdmat_gvari,
                    pdmat_rhat, dmaxRhat);
    if (nNodes < LARGE_N) /* for small matrices, print to the console */
      SaveConvergence(stdout, pdmat_gmean, pdmat_vari, pdmat_gvari, pdmat_rhat,
                      dmaxRhat);

    free(pdmat_gmean);
    free(pdmat_vari);
    free(pdmat_gvari);
    free(pdmat_rhat);
  }

  free(rgpFiles);

  printf("\nDone.\n\n");

} /* ConvergenceAnalysis */


/* end */

