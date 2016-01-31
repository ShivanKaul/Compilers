%{
#include <stdio.h>
#include "tree.h"

extern char *yytext;
extern int yylineno;
int yydebug;

extern EXP *prog;

void yyerror(const char* error) {
	fprintf(stderr, "Error before %s on %d. ", yytext, yylineno); 
}
%}

%union {
	float floatconst;
	int intconst;
	char *stringconst;
	struct EXP *exp;
	struct DECL *decl;
	struct STMT *stmt;
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
%type <exp> exp prog /* change! */

%start prog

%left '+' '-'
%left '*' '/'
%% 

prog:		decl_list stmt_list 
    		| exp /* change! */
			{ prog = $1; }

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
   			{ $$ = makeEXPint_lit ($1); }
   		| T_string_lit
			{ $$ = makeEXPstring_lit ($1); }
		| T_float_lit
			{ $$ = makeEXPfloat_lit ($1); }
	   	| T_id
			{ $$ = makeEXPid ($1); }
		| '(' exp ')'
			{ $$ = $2; }
		| exp '+' exp 
			{ $$ = makeEXPplus ($1, $3); }
		| exp '-' exp 
			{ $$ = makeEXPminus ($1, $3); }
		| exp '*' exp
			{ $$ = makeEXPtimes ($1, $3); }
		| exp '/' exp
			{ $$ = makeEXPdiv ($1, $3); }
		| '-'  exp      %prec  '*'
			{ $$ = makeEXPminus (0, $2); }
;

%%
