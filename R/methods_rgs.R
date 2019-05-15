#' Generic print for rgs objects
#'
#' @export

print.rgs <- function(x, ...) {
  cat("rgs object with", x[["n_nodes"]], "nodes, containing", x[["n_samples"]], "samples (adjacency matrices)")
  invisible(x)
}
