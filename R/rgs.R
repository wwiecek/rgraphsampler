#' rgs: R graph_sampler interface
#'
#' Run [`graph_sampler`](http://www.nongnu.org/graphsampler/) software from inside R.
#' @param file_in file name for a valid graphsampler input script
#' @param file_out file name (prefix) for a valid
#' @return Nothing is returned; standard graph_sampler output is printed
#'         in the terminal and output files generated as requested.
#' @details This simple function allows running C software graph_sampler
#'          inside R. All of the graph_sampler configuration is achieved
#'          by using a config script (`file_in`), which is identical to
#'          [the input for C version](http://www.nongnu.org/graphsampler/graph_sampler.html#Running-Graph_005fSampler)
#' @author Witold Wiecek
#' @useDynLib rgraphsampler
#' @export
rgs <- function(file_in = "script.txt",
                file_out = "output"){
  # library.dynam("rgraphsampler", "rgraphsampler", .libPaths())
  if(!file.exists(file_in))
    stop("No input file.")
  foo <- .C("gsmain",
            file_in,
            file_out)
}
