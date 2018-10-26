# @useDynLib rgraphsampler
#' @export
rgs <- function(file_in = "C:/github/graph_sampler_loop/graphsampler/tests/script_test_6.txt",
                file_out = "C:/github/rgs_testing/output_test"){
  library.dynam("rgraphsampler", "rgraphsampler", .libPaths())
  if(!file.exists(file_in))
    stop("No input file.")
  foo <- .C("gsmain",
            file_in,
            file_out)
}
