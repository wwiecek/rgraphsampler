#' get_gs_result
#'
#' Load information from graph_sampler output files into a single R object
#' @param file_name prefix for file names containing edge probabilities (`_edge_p.out` appended to `file_name`),
#'                  best graph (`_best_graph.out`), graph samples (`_graph_samples.out`)
#' @param node_names a character vector with names of nodes to be used in plots and summaries; if NULL,
#'                   defaults to V1, V2, V3, ...
#' @details Loading of samples and SCCs can also be accomplished on its own using
#'          `get_samples` and `get_scc` functions.
#'          This function is a "wrapper" for loading all relevant data.
#' @return A list object of class `rgs` containing edge probabilities, best graph, samples, SCC probabilities.
#' @author Witold Wiecek
#' @importFrom utils head
#' @importFrom utils read.table
#' @export

get_gs_result <- function(file_name, node_names = NULL) {

  # 1/ Probabilities
  # If using tempering, 1st line will have temperatures info
  # So we skip it
  edgep_file <- paste0(file_name, "_edge_p.out")
  first_line <- readLines(edgep_file, 1)
  edgep    <- utils::read.table(edgep_file,
                         skip = 1*grepl("temperature", first_line))
  nnodes <- ncol(edgep)

  # 2/ Names
  if(is.null(node_names))
    node_names <- paste0("V", 1:nnodes)
  rownames(edgep) <- colnames(edgep) <- node_names

  # 3/ Best graph
  bestg    <- utils::read.table(paste0(file_name, "_best_graph.out"), nrows = nnodes)
  rownames(bestg) <- colnames(bestg) <- node_names

  # 4/ Samples
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
