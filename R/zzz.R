.onUnload <- function (libpath) {
  library.dynam.unload("rgraphsampler", libpath)
}

.onAttach <- function(libname, pkgname) {
  packageStartupMessage("Welcome to rgraphsampler -- prototype version -- May 2019")
  packageStartupMessage("Use vignette('rgraphsampler') for tutorial.")
}
