#' get_scc
#' Turn a graph_sampler samples output file a list of strongly connected components
#'
#' @param filename graph samples (adjacency matrices) file from _graph_sampler_
#'                 (typically file names ending with `graph_samples.out`)
#' @return List of strongly connected components
#' @export

get_scc <- function(filename = "graph_samples.out") {
  connection <- file(filename, open = 'r')
  lines <- readLines(connection)
  close(connection)
  # detect number of rows/cols
  detected_n_row     <- min(which(lines == "")) - 1
  detected_n_samples <- sum(startsWith(lines, "Log(prior"))

  # SCCs
  scc_lines <- sapply(lines, startsWith, "SCCs", USE.NAMES = FALSE)

  if(sum(scc_lines) == 0)
    return(list())

  scc <- strsplit(lines[scc_lines], "\\(")
  #we remove first element from each list as it's just "SCCs: "
  scc <- lapply(scc, function(x) {keep_text_between_brackets(x[-1])})
  scc

  # do.call(rbind, lapply(scc, scc_vector_from_char, detected_n_row))
}

# A few helper functions:

scc_table <- function(scc) {
  # do.call(rbind, lapply(scc, scc_vector_from_char, detected_n_row))
  do.call(rbind, lapply(scc, scc_vector_from_char, length(scc)))
}

keep_text_between_brackets <- function(x) {
  x <- gsub(".*\\(", "", x)
  x <- gsub("\\).*", "", x)
}

# given a char vector such as c("1 5 7", "2 3")
# return c(1, 2, 2, 3, 1, 4, 1)
scc_vector_from_char <- function(x, n) {
  vec <- rep(0, n)
  scc_counter <- 1
  for(j in 1:length(x)) {
    vec[as.numeric(unlist(strsplit(x[j], " ")))] <- scc_counter
    scc_counter <- scc_counter + 1
  }
  for(i in 1:n) {
    if(vec[i] == 0){
      vec[i] <- scc_counter
      scc_counter <- scc_counter + 1}
  }
  return(vec)
}
