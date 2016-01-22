%{
#include <stdio.h>

extern char *yytext;
int yylineno;

void yyerror() {
   printf ("syntax error before %s on %d\n", yytext, yylineno); 
}
%}

%union {
   int intconst;
   char *stringconst;
}

%token <intconst> T_int
%token <stringconst> T_string
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

%start exp

%left '+' '-'
%left '*' '/'

%% 
exp:	T_int 
   	| T_var T_id ':' T_int
	| T_var T_id ':' T_string
	| T_id
	| exp '+' exp 
	| exp '-' exp 
	| exp '*' exp 
	| exp '/' exp 
/*	| MINUS exp %prec NEG { $$=-$2; } */	
/*	| T_id '='  { $$=$2; } */
;

%%

int main() {
  if (yyparse())
     fprintf(stderr, "Successful parsing.\n");
  else
     fprintf(stderr, "error found.\n");
}
