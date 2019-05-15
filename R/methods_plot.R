#' Generic plots for rgs objects
#'
#' @export

plot.rgs <- function(x, y, ...) {
  # Best graph
  bestg_ig <- igraph::graph_from_adjacency_matrix(as.matrix(x$best_graph), mode = "directed")
  bestg_ig <- igraph::set_vertex_attr(bestg_ig, value = x$node_names, name = "name")

  # Set layout for all graphs
  default_layout <- igraph::layout.auto(bestg_ig)

  plot(bestg_ig, main = "Best graph", layout = default_layout, ...)

  # Edge probabilities
  pr <- as.matrix(x$edge_pr)
  pr[pr < y] <- 0
  edgep_ig <- igraph::graph_from_adjacency_matrix(pr, weighted = T, mode = "directed")
  edgep_ig <- igraph::set_vertex_attr(edgep_ig, value = x$node_names, name = "name")
  plot(edgep_ig, main = "Edge probabilities", layout = default_layout,
       edge.width=E(edgep_ig)$weight*5,
       ...)

  # SCCs (if present)
  if(length(x$scc) > 0) {
    scc_adj <- 0*as.matrix(x$edge_pr)
    # Add relative frequency of SCCs to an empty adj matrix:
    tab <- as.data.frame(table(unlist(x$scc)))
    for(i in 1:nrow(tab)) {
      cscc <- as.character(tab$Var1[i])
      cval <- tab$Freq[i]/x$n_samples
      if(cval < y)
        cval <- 0
      scc_members <- as.numeric(unlist(strsplit(cscc, " ")))
      l <- length(scc_members)
      scc_adj[scc_members[l], scc_members[1]] <- max(scc_adj[scc_members[l], scc_members[1]], cval)
      for(j in 2:l)
        scc_adj[scc_members[j-1], scc_members[j]] <- max(scc_adj[scc_members[j-1], scc_members[j]], cval)
    }
    scc_ig <- igraph::graph_from_adjacency_matrix(scc_adj, weighted = T, mode = "directed")
    scc_ig <- igraph::set_vertex_attr(scc_ig, value = x$node_names, name = "name")
    plot(scc_ig, main = "SCC", layout = default_layout,
         edge.width=E(edgep_ig)$weight, ...)
  }
}
