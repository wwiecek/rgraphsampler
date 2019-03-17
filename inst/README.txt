## Contents of the inst/ folder

* parser/ contains files which lex/bison use to generate .c code in src/
  These are shared for user's reference.
* test_scripts/ contain text files for the testing suite
  .bin files have been changed to extension-less files, to avoid
  automated checks from thinking that we include binaries in inst/

## Differences to graph_sampler on GNU Savannah

1) Fix to make parser run without errors in R:
TO MAKE PARSER WORK IN R YOU NEED TO
COMMENT OUT 1557 in lex.yy.c:
//input(); yyunput(0, "a");

2) Use of <R.h> to pass errors to R.

3) Use of non-GSL variant of C graph_sampler.
   Currently GSL version is not supported.
