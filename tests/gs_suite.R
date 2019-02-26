# replication of graph_sampler testing suite from within R
# testing for the rgs models vs results in the C version
#
# runs a folder of predefined scripts in a loop,
# then compares results against stored outputs


print("Hi!")

df <- "c:/github/rgraphsampler/inst/test_scripts/"
library(rgraphsampler)
# lf <- list.files(df, pattern=".txt$")[c(30, 29, 15)]
# lf <- list.files(df, pattern=".txt$")[16:20]
# lf <- list.files(df, pattern=".txt$")[1:17]
# lf <- list.files(df, pattern=".txt$")[c(19)]
lf <- list.files(df, pattern=".txt$")
for(file in lf) {
  print(file)
  # library(rgraphsampler)
  rgs(file_in = paste0(df, file),
      file_out = paste0("c:/github/rgs_testing/suite/temp/", file))
  # unloadNamespace("rgraphsampler")
  fileref <- gsub("script_test", "graph_samples", file)
  fileref <- gsub(".txt", "_no_gsl.ref", fileref)

  file.copy(from = paste0("c:/github/rgs_testing/suite/temp/", file, "_graph_samples.out"),
            to = paste0("c:/github/rgs_testing/suite/", fileref),
            overwrite = TRUE)

}
# unloadNamespace("rgraphsampler")

cat("-------------\n")
cat("Test results:\n")
cat("-------------\n")

for(file in lf) {
  fileref <- gsub("script_test", "graph_samples", file)
  fileref <- gsub(".txt", "_no_gsl.ref", fileref)
  cat(fileref, "\t")

  cat(all.equal(readLines(paste0("c:/github/rgs_testing/suite/", fileref)),
            readLines(paste0("c:/github/graphsampler/tests/", fileref))))
  cat("\n")
}

