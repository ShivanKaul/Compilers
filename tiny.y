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
	struct PROG *prog;
	struct EXP *exp;
	struct DECL *decl;
	struct STMT *stmt;
	struct IF *if_stmt;
	struct WHILE *while_stmt;
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

%type <exp> exp
%type <stmt> stmt stmt_list
%type <prog> prog
%type <decl> decl decl_list
%type <if_stmt> if_stmt
%type <while_stmt> while_stmt

%start prog

%left '+' '-'
%left '*' '/'
%% 

prog:		decl_list stmt_list 
			{ prog = makePROG($1, $2); }

decl_list:	decl decl_list
	 		{ $$ = $1; $$->next = $2; }
	 	|
			{ $$ = NULL; }

decl:		T_var T_id ':' T_float ';'
    			{ $$ = makeDECLfloat($2); }
		| T_var T_id ':' T_int ';'
    			{ $$ = makeDECLint($2); }
		| T_var T_id ':' T_string ';'
    			{ $$ = makeDECLstring($2); }

stmt_list:	stmt stmt_list
	 		{ $$ = $1; $$->next = $2; }
		|
			{ $$ = NULL; }

stmt:		T_id '=' exp ';'
    			{ $$ = makeSTMTassign($1, $3); }
    		| T_print exp ';'
			{ $$ = makeSTMTprint($2); }
		| T_read T_id ';'
			{ $$ = makeSTMTread($2); }
		| if_stmt
			{ $$ = $1; }
		| while_stmt
			{ $$ = $1; }


if_stmt:	T_if exp T_then stmt_list T_endif
       			{ makeSTMTif($2, $4); }
		| T_if exp T_then stmt_list T_else stmt_list T_endif
			{ makeSTMTifElse($2, $4, $6); }

while_stmt:	T_while exp T_do stmt_list T_done
 	 		{ makeSTMTwhile($1, $4); }

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
