/* outputs.c

   Written by Frederic Bois

   Copyright (c) 2014-2017 Frederic Bois.

   This code is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the GNU General Public License at <http://www.gnu.org/licenses/> 

   Output routines.
*/


/* ----------------------------------------------------------------------------
   Inclusions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrices.h"
#include "outputs.h"
#include "graph_sampler.h"


/* ----------------------------------------------------------------------------
   CloseOutputs

   Close output files.
*/
void CloseOutputs (char *const prefixname)
{

  if (bsave_the_chain) {
    fclose(pChainFile);
    if (prefixname)
      printf("MCMC chain written to %s_results_mcmc.bin.\n\n",
              prefixname);
    else
      printf("MCMC chain written to results_mcmc.bin.\n\n");
  }

  if (bsave_the_chain && bTempered) {
    fclose(pInvTemperatureFile);
    if (prefixname)
      printf("Inverse temperatures written to"
              " %s_inverse_temperatures.out.\n\n",
              prefixname);
    else
      printf("Inverse temperatures  written to inverse_temperatures.out.\n\n");
  }

  if (bsave_the_edge_probabilities) {
    fclose(pEdgeFile);

    if (bTempered && n_at_targetT == 0) {
      printf("No sample at target temperature, "
             "edge probabilities not estimated.\n");
      if (prefixname)
        printf("File %s_edge_p.out is empty.\n\n", prefixname);
      else
        printf("File edge_p.out is empty.\n\n");
    }
    else {
      if (prefixname)
        printf("Edge probabilities written to %s_edge_p.out",
               prefixname);
      else
        printf("Edge probabilities written to edge_p.out");

      if (bTempered)
        printf("\n(with %lu samples at target temperature).\n\n", n_at_targetT);
      else
        printf(".\n\n");
    }
  }

  if (bsave_some_graphs) {
    fclose(pGraphsFile);
    if (prefixname)
      printf("%lu Random graphs written to %s_graph_samples.out.\n\n",
             n_saved_adjacency, prefixname);
    else
      printf("%lu Random graphs written to graph_samples.out.\n\n",
             n_saved_adjacency);
  }

  if (bsave_best_graph) {
    fclose(pBestFile);
    if (prefixname)
      printf("Best graph written to %s_best_graph.out.\n\n",
              prefixname);
    else
      printf("Best graph written to best_graph.out.\n\n");
  }

  if (bsave_the_degree_counts) {
    fclose(pDegreeFile);
    if (prefixname)
      printf("Degree counts written to %s_degree_count.out.\n\n",
             prefixname);
    else
      printf("Degree counts written to degree_count.out.\n\n");
  }

  if (bsave_the_motifs_probabilities) {
    fclose(pMotifFile);
    if (prefixname)
      printf("Motifs frequencies written to %s_motifs_count.out.\n\n", 
             prefixname);
    else
      printf("Motifs frequencies written to motifs_count.out.\n\n");
  }

  if (bNAData) {
    fclose(pImputedFile);
    if (prefixname)
      printf("Imputed data written to %s_missing_data.out.\n\n", 
             prefixname);
    else
      printf("Imputed data written to missing_data.out.\n\n");
  }

  if (bConvergence_std ||  bConvergence_inc) {
    fclose(pConvergenceFile);
    if (prefixname)
      printf("Convergence diagnostic written to %s_convergence.out.\n\n", 
             prefixname);
    else
      printf("Convergence diagnostic written to convergence.out.\n\n");
  }

} /* CloseOutputs */


/* ----------------------------------------------------------------------------
   CreateFileName

*/
void CreateFileName (char *const filename, char *const prefixname,
                     char *const suffixname)
{
  strcpy(filename, "");
  if (prefixname) {
    strcat(filename, prefixname);
    strcat(filename, "_");
  }
  strcat(filename, suffixname);

} /* CreateFileName */


/* ----------------------------------------------------------------------------
   InitOutputs

   Initializes various output files.
*/
void InitOutputs (char *const prefixname)
{
  char filename[MAXFILENAME+20];
   
  /* initialize an output file for the best (maximum probability) adjacency 
     matrix */
  if (bsave_best_graph) {
    CreateFileName(filename, prefixname, "best_graph.out");
    if (!(pBestFile = fopen(filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }
  }

  /* open chain output file */
  if (bsave_the_chain) {
    CreateFileName(filename, prefixname, "results_mcmc.bin");
    if (!(pChainFile = fopen(filename, "wb"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }

    /* first output the number of nodes to it */
    fwrite (&nNodes, sizeof(int), 1, pChainFile);
  }

  /* open temperature index output file */
  if (bsave_the_chain && bTempered) {
    CreateFileName(filename, prefixname, "inverse_temperatures.out");
    if (!(pInvTemperatureFile = fopen(filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }
  }

  /* open graph samples output file */
  if (bsave_some_graphs) {
    CreateFileName(filename, prefixname, "graph_samples.out");
    if (!(pGraphsFile = fopen(filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }

    /* init the print count */
    if (n_saved_adjacency < (nRuns - nBurnin)) {
      nPrintStep = (nRuns - nBurnin) / n_saved_adjacency;
    }
    else {
      nPrintStep = 1;
      n_saved_adjacency = nRuns - nBurnin;
    }
    nNextPrint = nPrintStep + nBurnin - 1;
  }

  /* open edge probabilities output file */
  if (bsave_the_edge_probabilities) {
    CreateFileName(filename, prefixname, "edge_p.out");
    if (!(pEdgeFile = fopen(filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }
  }

  /* open degrees output file */
  if (bsave_the_degree_counts) {
    CreateFileName(filename, prefixname, "degree_count.out");
    if (!(pDegreeFile = fopen(filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }

    /* print header line */
    fprintf(pDegreeFile, "degree\tcount\n");
  }

  /* open motifs output file */
  if (bsave_the_motifs_probabilities) {
    CreateFileName(filename, prefixname, "motifs_count.out");
    if (!(pMotifFile = fopen(filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }
  }

  /* open imputed data output file */
  if (bNAData) {
    CreateFileName (filename, prefixname, "missing_data.out");
    if (!(pImputedFile = fopen (filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }
    /* print header line */
    fprintf(pImputedFile, "value\tllikelihood\n");
  }

  if (bConvergence_std ||  bConvergence_inc) {
    CreateFileName (filename, prefixname, "convergence.out");
    if (!(pConvergenceFile = fopen (filename, "w"))) {
      printf("Error: cannot open %s - Exiting.\n\n", filename);
      exit (0);
    }
  }

} /* InitOutputs */


/* ----------------------------------------------------------------------------
   InitBuffer

   Initialize a small (integer) buffer for bit-packing writing or reading. 
*/
void InitBuffer (PBITBUFFER buf)
{
  buf->buffer = 0;
  buf->max_mask = 1 << (8 * sizeof(unsigned int) - 1);
  buf->mask = 1 << (8 * sizeof(unsigned int) - 1);
} /* InitBuffer */


/* ----------------------------------------------------------------------------
   ReadBitOffBuffer

   Reads a bit-pack 0/1 integer at the left of the unsigned integer buffer buf. 
   If buf is empty, it is read from the global pChainFile.
   Return values are 1 for success, 0 for reading errors or EOF.
*/
int ReadBitOffBuffer (FILE *pChainFile, PBITBUFFER buf, int *bit)
{
  /* fill buffer */
  if (buf->mask == buf->max_mask) {
    if (!fread (&(buf->buffer), sizeof(unsigned int), 1, pChainFile))
      return(0);
    /* printf("\nread %u\n\n", buf->buffer); */
  }

  /* unpack a bit */
  *bit = (buf->buffer & buf->mask ? 1 : 0);
  /* printf("%d", *bit); */
  buf->mask = buf->mask >> 1;
  if (buf->mask == 0)
    buf->mask = buf->max_mask;

  return(1);

} /* ReadBitOffBuffer */


/* ----------------------------------------------------------------------------
   Read_diff_buffered

   Reads an MCMC chain saved by diffing in packed binary format.
   See SaveChain comments on bit-packed format.
   The diff read in is ouput in *diff. 
   Return values are 1 for success, 0 if the termination code (binary 
   pair [1,0]) is found, -1 for reading errors or EOF before termination code.
*/
int Read_diff_buffered (FILE *pChainFile, PBITBUFFER buf, int *diff)
{
  int b1, b2;

  /* unpack a pair of bits */
  if (!ReadBitOffBuffer (pChainFile, buf, &b1))
    return(-1);

  if (!ReadBitOffBuffer (pChainFile, buf, &b2))
    return(-1);

  /* printf("b1: %d, b2: %d\n", b1, b2); */

  /* check the code and set diff or return value accordingly */
  if (b1) {
    if (b2)
      *diff = -1;
    else
      return(0); /* termination code */
  }
  else {
    if (b2)
      *diff = +1;
    else
      *diff =  0;
  }

  return(1);

} /* Read_diff_buffered */


/* ----------------------------------------------------------------------------
   WriteBitToBuffer

   Bit-pack a 0/1 integer at the left of the unsigned integer buffer buf. 
   If buf is full, it is written to the global pChainFile.
*/
void WriteBitToBuffer (PBITBUFFER buf, int to_out)
{
  if (to_out)
    buf->buffer = buf->buffer | buf->mask;
  /* printf("%d", (to_out ? 1 : 0)); */
  buf->mask = buf->mask >> 1;

  if (buf->mask == 0) { /* buffer buf is full */
    fwrite(buf, sizeof(unsigned int), 1, pChainFile);
    /* printf("\nwrote %u\n\n", buf->buffer); */
    buf->buffer = 0;
    buf->mask = buf->max_mask;
  }

} /* WriteBitToBuffer */


/* ----------------------------------------------------------------------------
   ReadChain

   Read a MCMC chain saved with SaveChain (packed bits format). 
   See in SaveChain how the chain is written. 
   This is provided as an example, or for debugging.
*/
void ReadChain ()
{
  unsigned long j, k;
  int           *adjacency_matrix = NULL; /* is in fact a vector */
  static        BITBUFFER buf;

  InitBuffer(&buf);
  
  printf("Opening...\n");
  if (!(pChainFile = fopen("results_mcmc.bin", "r"))) {
    printf("Error: cannot open file results_mcmc.bin - Exiting\n\n");
    exit (0);
  }

  /* read the number of nodes */
  if (!fread (&nNodes, sizeof(int), 1, pChainFile))
    lexerr("cannot read the number of nodes");
  else
    printf("\nNumber of nodes: %d.\n", nNodes);

  /* initialize the adjacency matrix (flat!) */
  adjacency_matrix = InitiVector(nNodes * nNodes);

  /* read the initial adjacency matrix */
  for (j = 0; j < nNodes * nNodes; j++)
    if (!ReadBitOffBuffer(pChainFile, &buf, &(adjacency_matrix[j])))
      lexerr("cannot read the initial adjacency matrix");

  if (nNodes < 11) {
    printf("\nReconstructed initial adjacency matrix:\n");
    for (j = 0; j < nNodes; j++) {
      for (k = 0; k < nNodes; k++)
        printf("%d ", adjacency_matrix[j+k*nNodes]);
      printf("\n");
    }
  }

  /* iterate through the file, matrix by matrix,
     coded by difference as a a bit-packed signed integer
     and reconstruct the adjacency matrix at each step */
  j = 0;
  do {
    k = Read_diff_buffered (pChainFile, &buf, &diff);
    if (k < 1) {
      if (k == 0) {
        /* printf("End of chain after %ld reads.\n", j); */
        break;
      }
      else
        lexerr ("unknown reading error");
    }

    if (diff > 0)
      adjacency_matrix[j]++;
    if (diff < 0)
      adjacency_matrix[j]--;

    j++;
    if (j == nNodes * nNodes)
      j = 0;

  } while (1); /* that is, until EOF found */

  if (nNodes < 11) {
    printf("\nReconstructed final adjacency matrix:\n");
    for (j = 0; j < nNodes; j++) {
      for (k = 0; k < nNodes; k++)
        printf("%d ", adjacency_matrix[j+k*nNodes]);
      printf("\n");
    }
  }

  free(adjacency_matrix); /* adjacency is a simple vector */
  fclose(pChainFile);

} /* ReadChain */


/* ----------------------------------------------------------------------------
   SaveChain

   Write the full adjacency matrix at start (as a bit-packed string of 
   integers) and encode integer "to_out" in two bits after that.
   The number of nodes (an integer) has already been written in the output 
   file at its initialization.
   This assumes that the adjacency matrix is scanned systematically for 
   change (so there is no need to record location). 
*/
void SaveChain (int to_out)
{
  int i, j;
  static BITBUFFER buf;

  if (iter >= nBurnin) { /* remember that iter starts at zero */

    if (iter == nBurnin) {
      InitBuffer(&buf);
      for (j = 0; j < nNodes; j++)  /* jth column */
        for (i = 0; i < nNodes; i++)  /* ith line */
          WriteBitToBuffer (&buf, current_adj[i][j]);
    }

    /* along the chain, pack to_out (-1, 0, or +1) into two bits,
       the first bit for sign, the second for change:

                change       
               Yes    No  
            +------+------+
           +|  01  |  00  |
       sign +------+------+
           -|  11  |  10  |
            +------+------+
       There is no need for two codes for no change, so code 10 is used
       to indicate chain termination.
    */

    /* write the sign (0 = "+" (edge added), 1 = "-" (edge removed) */
    WriteBitToBuffer (&buf, (to_out < 0));

    /* write the change (0 = no change, 1 = change) */
    WriteBitToBuffer (&buf, (to_out != 0));
    /* printf("b1: %d, b2: %d\n", (to_out < 0), (to_out != 0)); */

    if (iter == nRuns - 1) { /* add termination code */
      WriteBitToBuffer (&buf, 1);
      WriteBitToBuffer (&buf, 0);
      /* printf("b1: 1, b2: 0\n"); */

      /* flush buffer */
      fwrite (&buf, sizeof(unsigned int), 1, pChainFile);        
      /* printf("\nwrote %u\n\n", buf); */
    }
  } /* if iter >= nBurnin */

} /* SaveChain */


/* ----------------------------------------------------------------------------
   SaveBestGraph

   Just do that.
*/
void SaveBestGraph (void)
{
  if (bsave_best_graph) {
    PrintiMatrix (pBestFile, nNodes, best_adj);

    if (bHypergraph) {
      int i, j;
      int *component       = InitiVector(nNodes);
      int *component_size  = InitiVector(nNodes);

      /* (re)compute SCCs for the best graph */
      Tarjan_with_sizes (best_adj, nNodes, component, component_size);
      
      /* print non-degenerate components and all count components 
         (including degenerate components of size one) */
      int n_all_components = 0;
      for (i = 0; i < nNodes; i++) {
        if (component[i] > n_all_components)
          n_all_components++;
      }

      /* print the nodes associated with each non-degenerate component
         and component size */
      int size, init = 0;
      for (i = 1; i <= n_all_components; i++) { 
        j = 0;
        while (component[j] != i) /* find the first occurence of SCC i */
          j++;
        if (component_size[j] > 1) { /* if SCC i is non-degenerate */
          if (init == FALSE) {
            fprintf(pBestFile, "SCCs:");
            init = TRUE;
          }
          size = component_size[j];
          fprintf(pBestFile, " (%d", j+1); /* print first node in SCC i */
          while (j < nNodes - 1) {
            j++;
            if (component[j] == i)
              fprintf(pBestFile, " %d", j+1); /* print all nodes in SCC i */
          }
          fprintf(pBestFile, ")[%d]", size);
        }
      }
      if (init == TRUE)
        fprintf(pBestFile, "\n");
      
      free(component);
      free(component_size);
    }

    fprintf(pBestFile, "Log(prior probability):     %.12g\n", dBestPrior);

    if (bData) {
      fprintf(pBestFile, "Log(integrated likelihood): %.12g\n", 
              dBestLikelihood);
      fprintf(pBestFile, "Log(posterior probability): %.12g\n", dBestPosterior);
    }
  }
} /* SaveBestGraph */


/* ----------------------------------------------------------------------------
   SaveConvergence

   Save the results of convergence analysis to a file or stream.
*/
void SaveConvergence (FILE *outFile, double *pdmat_gmean, double *pdmat_vari,
                      double *pdmat_gvari, double *pdmat_rhat, double dmaxRhat)
{
  int j, k;

  if ((outFile != stdout) && (!bConvergence_inc)) {
    fprintf(outFile, "Convergence analysis results; Files used: ");
    for (j = 0; j < nChains; j++)
      fprintf(outFile, "%s, ", pChainNames[j]);
    if (bConvergence_std == 1) /* with chains */
      fprintf(outFile, "with samples [%ld to %ld].\n",
              nConvergence_start, nConvergence_end);
    if (bConvergence_std == 2) /* with edge probabilities */
      fprintf(outFile, "containing edge probabilities over "
                       "the whole recorded chains.\n");
  }
  
  fprintf(outFile, "\nOverall edge probabilities:\n");
  for (j = 0; j < nNodes; j++) {
    for (k = 0; k < nNodes; k++)
      fprintf(outFile, "%5.3f ", pdmat_gmean[j+k*nNodes]);
    fprintf(outFile, "\n");
  }

  fprintf(outFile, "\nIntra-chain variances:\n");
  for (j = 0; j < nNodes; j++) {
    for (k = 0; k < nNodes; k++)
      fprintf(outFile, "%5.3f ", pdmat_vari[j+k*nNodes]);
    fprintf(outFile, "\n");
  }

  fprintf(outFile, "\nInter-chain variances:\n");
  for (j = 0; j < nNodes; j++) {
    for (k = 0; k < nNodes; k++)
      fprintf(outFile, "%5.3f ", pdmat_gvari[j+k*nNodes]);
    fprintf(outFile, "\n");
  }

  fprintf(outFile, "\nConvergence R_hats:\n");
  for (j = 0; j < nNodes; j++) {
    for (k = 0; k < nNodes; k++)
      fprintf(outFile, "%5.3f ", pdmat_rhat[j+k*nNodes]);
    fprintf(outFile, "\n");
  }

  fprintf(outFile, "\nWorst R_hat: %lg\n", dmaxRhat);

} /* SaveConvergence */


/* ----------------------------------------------------------------------------
   SaveDegreeCounts

   Just do that.
*/
void SaveDegreeCounts (void)
{
  unsigned long i;

  if (bsave_the_degree_counts) {
    for (i = 0; i < (nNodes+nNodes); i++) {
      fprintf(pDegreeFile, "%ld\t%lg\n", i, cumdegree_count[i]);
    }
  }
} /* SaveDegreeCounts */


/* ----------------------------------------------------------------------------
   SaveEdgeP

   Just do that.
*/
void SaveEdgeP (FILE *outFile)
{
  int i, j;

  if (bsave_the_edge_probabilities) {

    if (bTempered) {
      if (n_at_targetT > 0)
        fprintf(outFile, "%lu samples at target temperature.\n\n", 
                         n_at_targetT);
      else {
        fprintf(outFile, "No sample at target temperature, "
                         "edge probabilities not estimated.\n\n");
        return;
      }
    }

    for (i = 0; i < nNodes; i++) {
      for (j = 0; j < nNodes-1; j++) {
        fprintf(outFile, "%.3lf\t", mat_sum[i][j] / (double) n_at_targetT);
      }
      fprintf(outFile, "%.3lf\n", mat_sum[i][j] / (double) n_at_targetT);
    }
  }

} /* SaveEdgeP */


/* ----------------------------------------------------------------------------
   SaveGraph

   Just do that.
*/
void SaveGraph (void)
{
  int i, j;

  if (bsave_some_graphs && (iter == nNextPrint)) {
    PrintiMatrix(pGraphsFile, nNodes, current_adj);

    fprintf(pGraphsFile, "Number of edges: %ld\n", current_edge_count);
    
    if (bHypergraph) {
      
      /* print non-degenerate components and all count components 
         (including degenerate components of size one) */
      int n_all_components = 0;
      for (i = 0; i < nNodes; i++) {
        if (component[i] > n_all_components)
          n_all_components++;
      }

      /* print the nodes associated with each non-degenerate component
         and component size */
      int size, init = 0;
      for (i = 1; i <= n_all_components; i++) { 
        j = 0;
        while (component[j] != i) /* find the first occurence of SCC i */
          j++;
        if (component_size[j] > 1) { /* if SCC i is non-degenerate */
          if (init == FALSE) {
            fprintf(pGraphsFile, "SCCs:");
            init = TRUE;
          }
          size = component_size[j];
          fprintf(pGraphsFile, " (%d", j+1); /* print first node in SCC i */
          while (j < nNodes - 1) {
            j++;
            if (component[j] == i)
              fprintf(pGraphsFile, " %d", j+1); /* print all nodes in SCC i */
          }
          fprintf(pGraphsFile, ")[%d]", size);
        }
      }
      if (init == TRUE)
        fprintf(pGraphsFile, "\n");
    }

    if (bTempered)
      fprintf(pGraphsFile, "Inverse temperature:        %g\n", 
              pInvTemperatures[indexT]);

    fprintf(pGraphsFile,   "Log(prior probability):     %.6g\n", 
            current_logprior);

    if (bData) {
      fprintf(pGraphsFile, "Log(integrated likelihood): %.6g\n", 
              current_loglikelihood);
      fprintf(pGraphsFile, "Log(posterior probability): %.6g\n\n\n", 
      current_logposterior);
    }
    else
      fprintf(pGraphsFile, "\n\n");

    nNextPrint += nPrintStep;
  }

} /* SaveGraph */


/* ----------------------------------------------------------------------------
   SaveInverseTemperature

   Saves in fact the index to the current inverse temperature.
*/
void SaveInverseTemperature (void)
{
  if (iter >= nBurnin) { /* remember that iter starts at zero */
    fprintf(pInvTemperatureFile, "%d\n", indexT);
  }
} /* SaveInverseTemperature */


/* ----------------------------------------------------------------------------
   SaveMotifsP

   Just do that.
*/
void SaveMotifsP (FILE * outFile)
{
  if (bsave_the_motifs_probabilities) {
    fprintf(outFile, "Endless/Frustrated triangular loops:\n");
    fprintf(outFile, "E loops count: %lg\n", cum_nEloops);
    fprintf(outFile, "F loops count: %lg\n", cum_nFloops);

    if ((cum_nEloops != 0) || (cum_nFloops != 0))
      fprintf(outFile, "E / (E + F): %lg\n\n",
             cum_nEloops / (cum_nEloops+ cum_nFloops));
    else
      fprintf(outFile, "\n");
  }

} /* SaveMotifsP */


/* end */
