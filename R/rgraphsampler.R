#' @export
rgraphsampler <- function(opts) {
  dir <- tempdir()
  filename <- tempfile()
  if(!(class(opts) == "list") ||
     length(opts) == 0)
    stop("opts argument should be a named list")

  # testing:
  # writeLines("n_runs    = 2E5;\nn_burn_in = 1E5;\nrandom_generator = mersenne_twister;\nrandom_seed = 49740;\nn_nodes = 30;\nautocycle = true;\ninitial_adjacency = matrix {empty};\nhyper_pB = matrix {equanimous};\ndegree_prior = true;\nsave_chain = true;\nn_saved_adjacency = 10;\nsave_best_graph = true;\n  save_edge_probabilies = true;\nsave_degree_counts = true;\nsave_motifs_probabilies = true;\n",
             # file)

  # write a complete script
  # writeLines uses sep = "\n" by default!
  fileConn <- file(filename)
  for(i in 1:length(opts))
    writeLines(paste0(names(opts)[i], "=", opts[[i]], ";"), fileConn)
  close(fileConn)

  rgs(filename, dir, "test")
}



# rgraphsampler(opts = list(
#   n_runs    = 2E5,
#   n_burn_in = 1E5,
#   random_generator = "tausworthe",
#   random_seed = 49740,
#   n_nodes = 30,
#   autocycle = "true",
#   initial_adjacency = "matrix {empty}",
#   hyper_pB = "matrix {equanimous}",
#   save_chain = "true",
#   n_saved_adjacency = 10,
#   save_best_graph = "true",
#   save_edge_probabilies = "true",
#   save_degree_counts = "true",
#   save_motifs_probabilies = "true"
# ))
