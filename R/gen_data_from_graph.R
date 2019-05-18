#' gen_data_from_graph
#'
#' Generate random data draws from a given Bayesian network,
#' assuming with linear relationships and Gaussian noise.
#' Loops are treated as multivariate Gaussian with fixed correlation.
#'
#' @param beta square numeric matrix defining linear coefficients between nodes
#' @param alpha vector of numeric values: baseline values for each nodes
#' @param sigma positive numeric vector of same length as `alpha`: SD of normal noise for each node
#' @param ndata number of samples to generate
#' @param loop integer vector of strongly connected components, to allow for use of loops;
#'             for DAGs (default) `loop = 1:nrow(beta)`; for e.g. a 6-node graph with a 2-node
#'             SCC on nodes 3 and 4, `loop = c(1, 2, 3, 3, 4, 5)`
#' @param cor_loop correlations of nodes within loops (loops are treated as multivariate Gaussian)
#' @param scale_x numeric; scale all linear relationship by `scale_x` (including in loops)
#' @details
#' This is a convenience function to generate BNs which can be used
#' for benchmarks, visualisations etc.
#' Apart from DAGs, cyclic graphs are also allowed. In all cases _the input vertices
#' must be topologically sorted_ and loop members should be consequent vertices.
#' @author Witold Wiecek
#' @examples
#' true_adj <- matrix(c(
#' 0, 1, 0, 0,
#' 0, 0, 1, 0,
#' 0, 0, 0, 1,
#' 0, 0, 0, 0
#' ), 4, 4, byrow = TRUE)*runif(4*4, 1, 3)*sign(rnorm(4*4))
#' out <- gen_data_from_graph(true_adj, rep(0, 4), rep(1,4), 100)
#' pairs(out)
#'
#' # Something a bit bigger:
#' beta <- matrix(rbinom(10*10, 1, .2), 10, 10)
#' beta[lower.tri(beta)] <- 0 #'sorted' matrix
#' diag(beta) <- 0
#' pairs(gen_data_from_graph(beta))
#'
#' @export
#' @importFrom MASS mvrnorm

gen_data_from_graph <- function(beta, alpha = rnorm(nrow(beta)), sigma = rep(1, nrow(beta)),
                        ndata = 100, loop = 1:nrow(beta),
                        cor_loop = .5, scale_x = 1) {
  out <- matrix(1, ndata, 1)
  loop_size <- sapply(loop, function(x) sum(loop == x))
  skip <- rep(0, nrow(beta)) #indicator to skip loop members if we already gen'd data
  for(i in 1:nrow(beta)) {
    if(loop_size[i] == 1) {
      if(i > 1)
        mean <- out %*% (c(alpha[i], beta[1:(i-1), i]))
      else
        mean <- rep(alpha[1], ndata)
      out <- cbind(out, sapply(c(mean), function(x) rnorm(1, scale_x*x, sigma[i])))
    } else if (!skip[i]) {
      loop_members <- which(loop == loop[i])
      m <- length(loop_members)
      skip[loop_members] <- 1

      #simplified version:
      if(i > 1)
        mean <- out %*% (c(alpha[i], beta[1:(i-1), i]))
      else
        mean <- rep(alpha[1], ndata)

      Sigma_loop <- ((1-cor_loop)*diag(m) + cor_loop)*sigma[i]
      out <- cbind(out,
                   t(sapply(mean,
                            function(x) MASS::mvrnorm(1, scale_x*rep(x, m), Sigma_loop))))
    }
  }
  return(out[,-1])
}
