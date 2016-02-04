#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "pretty.h"
#include "typecheck.h"
#include "symbol.h"
#include "code.h"

extern int yydebug;
int yyparse();
PROG *prog;
DECL *decls;

int main(int argc, char* argv[]) {
	// Debug?
	if (argc < 2) yydebug = 0; 
	else yydebug = strcmp("-d", argv[1]) ? 0 : 1;
	if (yyparse()) {
		printf("INVALID.\n");
	}
	else {
		// parsing passed
		printf("VALID.\n");
		
		// Generate filenames
		char *file = strsep(&argv[2], ".min");
		char *pretty = malloc(strlen(file)+strlen(".pretty.min")+1);;		
		char *symbol = malloc(strlen(file)+strlen(".symbol.txt")+1);
		char *gen_code = malloc(strlen(file)+strlen(".c")+1);
		sprintf(pretty, "%s.pretty.min", file);
		sprintf(symbol, "%s.symbol.txt", file);
		sprintf(gen_code, "%s.c", file);

    	// AST
		FILE *fpPretty;
		fpPretty=fopen(pretty, "w");
		printf("DEBUG: Pretty progging in main.\n");
		prettyPROG(prog, fpPretty);
		fclose(fpPretty);

		// Symbol Table
		FILE *fpSymbolTable;
		fpSymbolTable=fopen(symbol, "w");
		printf("DEBUG: Building symbol table... "); // remove
		if (!printSymbolTable(prog->decls, fpSymbolTable)) {
			printf("DEBUG: Error in building symbol table!\n");
			return 1;
		}
		fclose(fpSymbolTable);
		printf("done!\n"); // remove

		// Type Check
		printf("DEBUG: Type checking... "); // remove
		if (!typeCheck(prog->stmts, prog->decls)) {
			return 1;
		}

		// Code gen
		printf("DEBUG: Code gen...\n"); // remove
		FILE *fpGenCode;
		fpGenCode=fopen(gen_code, "w");
		generateCode(prog, fpGenCode);
		fclose(fpGenCode);


	}
}