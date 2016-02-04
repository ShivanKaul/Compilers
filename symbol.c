#include "symbol.h"
#include "memory.h"
#include <string.h>


char* symbolExists(DECL *decls, char *toCheck) {
	DECL *d = decls;
	while (d) {
		switch (d->kind) {
			case floatK:
			if (!strcmp(d->val.floatId, toCheck))
				return "float";
			case intK:
			if (!strcmp(d->val.intId, toCheck))
				return "int";
			case stringK:
			if (!strcmp(d->val.stringId, toCheck))
				return "string";
		}
		d = d->next;
	}
	return NULL;
}

int printSymbolTable(DECL *decls, FILE* fp) {
	DECL *d = decls;
	while (d) {
		char *name;
		switch (d->kind) {
				case floatK:
					name = d->val.floatId;
					fprintf(fp, "%s: float\n", name);
					break;
				case intK:
					name = d->val.intId;
					fprintf(fp, "%s: int\n", name);
					break;
				case stringK:
					name = d->val.stringId;
					fprintf(fp, "%s: string\n", name);
					break;
		}
		DECL *d2 = d->next;
		if (symbolExists(d2, name)) {
			printf("INVALID: line %d: identifier %s already declared\n", d2->yylineno, name);
			return 0;
		}
		d = d->next;
	}
	return 1;
}