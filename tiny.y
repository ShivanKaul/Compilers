%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *yytext;
extern int yylineno;
int yydebug;

void yyerror(const char* error) {
	fprintf(stderr, "Error before %s on %d. %s", yytext, yylineno, error); 
}
%}

%union {
	float floatconst;
	int intconst;
	char *stringconst;
}

/* Formatting semantic values.  */
%printer { fprintf (yyoutput, "%s", $$); } T_string_lit;
%printer { fprintf (yyoutput, "%f", $$); } T_float_lit;
%printer { fprintf (yyoutput, "%d", $$); } T_int_lit;

%token <intconst> T_int_lit
%token <stringconst> T_int
%token <floatconst> T_float_lit
%token <stringconst> T_float
%token <stringconst> T_string
%token <stringconst> T_string_lit
%token <stringconst> T_id  
%token <stringconst> T_var 
%token <stringconst> T_while  
%token <stringconst> T_do
%token <stringconst> T_done  
%token <stringconst> T_print  
%token <stringconst> T_read
%token <stringconst> T_if
%token <stringconst> T_then
%token <stringconst> T_else
%token <stringconst> T_endif

%start prog

%left '+' '-'
%left '*' '/'
%% 

prog:		decl_list stmt_list 

decl_list:	decl_list decl
	 	|

decl:		T_var T_id ':' T_float ';'
		| T_var T_id ':' T_int ';'
		| T_var T_id ':' T_string ';'

stmt_list:	stmt_list stmt
		|

stmt:		T_id '=' exp ';'
    		| T_print exp ';'
		| T_read T_id ';'
		| if_stmt
		| while_stmt

if_stmt:	T_if exp T_then stmt_list T_endif
		| T_if exp T_then stmt_list T_else stmt_list T_endif

while_stmt:	T_while exp T_do stmt_list T_done

exp:		T_int_lit
   		| T_string_lit
		| T_float_lit
	   	| T_id
		| '(' exp ')'
		| exp '+' exp 
		| exp '-' exp 
		| exp '*' exp
		| exp '/' exp
		| '-'  exp      %prec  '*'
;

%%

int main(int argc, char* argv[]) {
	// Debug?
	if (argc < 2) yydebug = 0; 
	else yydebug = strcmp("-d", argv[1]) ? 0 : 1;

	if (yyparse()) {
		printf("INVALID.\n");
	}
	else {
		printf("VALID.\n");
	}
}
