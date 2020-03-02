checkers: checkers.h checkers.c checkers_main.c
	clang -g -Wall checkers.c checkers_main.c -o checkers -w