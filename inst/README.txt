TO MAKE PARSER WORK IN C YOU NEED TO
COMMENT OUT 1557 in lex.yy.c:

//input(); yyunput(0, "a");
