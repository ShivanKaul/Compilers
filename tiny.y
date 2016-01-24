%{
#include <stdio.h>

extern char *yytext;
extern int yylineno;
int yydebug=1;

void yyerror() {
	printf ("Syntax error before %s on %d\n", yytext, yylineno); 
}
%}

%union {
	float floatconst;
	int intconst;
	char *stringconst;
}

%token <intconst> T_int_lit
%token <stringconst> T_int
%token <floatconst> T_float_int
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

%start prog

%left '+' '-'
%left '*' '/'
%% 

/* input:
     | input line
;

line:	'\n'
    | exp '\n'
; */

prog:		next_stmt
    		| next_stmt ';'

decl:		T_var T_id ':' T_float
		| T_var T_id ':' T_int
		| T_var T_id ':' T_string

next_stmt:	stmt
	 	| next_stmt ';' stmt

stmt:		T_id '=' exp 
		| T_var T_id ':' T_float
		| T_var T_id ':' T_int
		| T_var T_id ':' T_string

exp:		T_int_lit
   		| T_string_lit
/*		| T_float_lit */
	   	| T_id
		| exp '+' exp 
		| exp '-' exp 
		| exp '*' exp
		| exp '/' exp
		| '-'  exp      %prec  '*'
	   	| error  { yyerror(); }
/*	| MINUS exp %prec NEG { $$=-$2; } */	
/*	| T_id '='  { $$=$2; } */
;

%%

int main() {
  if (yyparse())
     fprintf(stderr, "Error found.\n");
  else
     fprintf(stderr, "Successful parsing.\n");
}
