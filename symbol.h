typedef struct SYMBOL {
	char* id;
	char* type;
	SYMBOL *next;
} SYMBOL;

void createSymbolTable(DECL *decls);
