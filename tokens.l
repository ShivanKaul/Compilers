/* includes and other arbitrary C code */
%{
	#include <stdio.h> /* for printf */
%}
/* helper definitions */
DIGIT [0-9]
/* regex + action rules come after the first %% */

/* */

%%
[ \t\n]+ printf ("white space, length %i\n", yyleng);
"*" printf ("times\n");
"/" printf ("div\n");
"+" printf ("plus\n");
"-" printf ("minus\n");
"(" printf ("left parenthesis\n");
")" printf ("right parenthesis\n");
0|([1-9]{DIGIT}*) printf ("integer constant: %s\n", yytext);
[a-zA-Z_][a-zA-Z0-9_]* printf ("identifier: %s\n", yytext);

%%
	/* user code comes after the second %% */
	main () {
		yylex ();
	}
