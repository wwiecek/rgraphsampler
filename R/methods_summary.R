#' Generic summary for rgs objects
#'
#' @export

summary.rgs <- function(object, ..., digits) {
  cat("rgs object with", object[["n_nodes"]], "nodes, containing", object[["n_samples"]], "samples (adjacency matrices)")
  cat("\n-------------------------\n\n")

  # Edge probabilities
  if(object[["n_nodes"]] <= sqrt(getOption("max.print"))){
    cat("Edge probabilities:\n")
    print(object[["edge_pr"]])
  }else
    cat("Edge probabilities not displayed for graphs with more than sqrt(getOption('max.print')) nodes")

  # Avg N edges:
  avg_n_edges <- mean(unlist(lapply(object[["samples"]], sum)))
  cat("\nAverage number of edges: ",
      avg_n_edges,
      "\n\n")

  # SCCs:
  if(length(object[["scc"]]) > 0) {
    tab <- as.data.frame(sort(table(unlist(object[["scc"]])), decreasing = T))
    names(tab) <- c("SCC", "N_samples")
    if(nrow(tab) > 10){
      cat("Most frequently appearing SCCs: \n")
      print(head(tab, 10))
      cat("... ", nrow(tab), " total SCCs in the sample")
    } else {
      cat("SCCs in the sample: \n")
      print(tab)
    }
  }
}
