#' get_samples
#' Turn a graph_sampler samples output file a list in R
#'
#' @param filename graph samples (adjacency matrices) file from _graph_sampler_
#'                 (typically file names ending with `graph_samples.out`)
#' @return List of adjacency matrices
#' @export

get_samples <- function(filename = "graph_samples.out") {

  # function for reading lines from graph_samples
  # if they start with text or are empty, we skip them
  # slow and stupid but works

  connection <- file(filename, open = 'r')
  lines <- readLines(connection)
  close(connection)
  # detect number of rows/cols
  detected_n <- min(which(lines == "")) - 1

  # only keep the adjacency matrices part
  adj_lines <- sapply(lines, startsWith, "0", USE.NAMES = FALSE) |
    sapply(lines, startsWith, "1", USE.NAMES = FALSE)
  adj_table <- read.table(textConnection(lines[adj_lines]))

  # SCCs
  scc_lines <- lines[sapply(lines, startsWith, "SCCs", USE.NAMES = FALSE)]
  scc <- strsplit(scc_lines, "\\(")
  #we remove first element from each list as it's just "SCCs: "
  scc <- lapply(scc, function(x) {keep_text_between_brackets(x[-1])})

  ll <- list()
  for(i in 1:(nrow(adj_table)/detected_n)) {
    ll[[i]] <- as.matrix(adj_table[1:detected_n,])
    rownames(ll[[i]]) <- NULL
    adj_table <- adj_table[(detected_n + 1):nrow(adj_table),]
  }
  # message(paste("Read", length(ll), "graphs from", filename))
  return(ll)
}
