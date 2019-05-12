#' get_gs_result
#'
#' Load information from graph_sampler output files into a single R object
#' @param file_name prefix for file names containing edge probabilities (`_edge_p.out` appended to `file_name`),
#'                  best graph (`_best_graph.out`), graph samples (`_graph_samples.out`)
#' @details Loading of samples and SCCs can also be accomplished on its own using
#'          `get_samples` and `get_scc` functions.
#'          This function is a "wrapper" for loading all relevant data.
#' @return A list object of class `rgs` containing edge probabilities, best graph, samples, SCC probabilities.
#' @author Witold Wiecek
#' @export

get_gs_result <- function(file_name, node_names = NULL) {
  # Probabilities:
  edgep    <- read.table(paste0(file_name, "_edge_p.out"))

  nnodes <- ncol(edgep)

  # Names
  if(is.null(node_names))
    node_names <- paste0("V", 1:nnodes)
  rownames(edgep) <- colnames(edgep) <- node_names

  # Best graph:
  bestg    <- read.table(paste0(file_name, "_best_graph.out"), nrows = nnodes)
  rownames(bestg) <- colnames(bestg) <- node_names

  # Samples:
  samples <- get_samples(paste0(file_name, "_graph_samples.out"))


  # SCCs:
  sccs <- get_scc(paste0(file_name, "_graph_samples.out"))

  result <- structure(list("n_nodes" = nnodes,
                           "n_samples" = length(samples),
                           "edge_pr" = edgep,
                           "best_graph" = bestg,
                           "samples" = samples,
                           "scc" = sccs,
                           "node_names" = node_names), class = "rgs")

  return(result)
}
