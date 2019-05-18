#' gen_gs_graph
#' Create adjacency matrix for a graph with edge probability and
#' given a DAG & probability of loop occurence,
#' 'uncondense' the graph by replacing condensed nodes with loops

# gen_gs_graph <- function(n, pr_edge, nloops, loop_size) {
#   adj <- matrix(0, n, n)
#   loop_counter <- rep(0, n)
#   onloop <- rep(0, n)
#   counter <- 1
#   # pr <- outdegree/n
#   for(i in 1:n){
#     for(j in 1:n) {
#       adj[i,j] <- (j > i)*rbinom(1, 1, pr_edge)
#     }
#   }
#
#   #loops are of size 3 and nodes are interchangeable, so let's say it is 3n + 1, 3n + 2, 3n + 3
#   if(nloops > 0) {
#     loop_nodes <- sample(1:(floor(n/3) - 1), nloops)
#     for(m in loop_nodes) {
#       i <- m*3
#       loop_counter[i] <- counter; loop_counter[i+1] <- counter; loop_counter[i+2] <- counter
#       onloop[i] <- 1; onloop[i+1] <- 1; onloop[i+2] <- 1;
#       counter <- counter + 1
#       adj[i,i+1]   <- 1; adj[i,i+2]   <- 1
#       adj[i+1,i]   <- 1; adj[i+1,i+2] <- 1
#       adj[i+2,i+1] <- 1; adj[i+2,i]   <- 1
#     }
#   }
#   for(i in 1:n) {
#     if(loop_counter[i] == 0) {
#       loop_counter[i] <- counter
#       counter <- counter + 1
#     }
#   }
#
#   return(
#     structure(adj,
#               loop = loop_counter,
#               onloop = onloop))
# }

