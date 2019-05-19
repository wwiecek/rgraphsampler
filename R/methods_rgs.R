#' Generic print for rgs objects
#'
#' @param x Object of class `rgs`, typically produced by [rgs()] or [get_gs_result()].
#' @export

print.rgs <- function(x, ...) {
  cat("rgs object with", x[["n_nodes"]], "nodes, containing", x[["n_samples"]], "samples (adjacency matrices)")
  invisible(x)
}
