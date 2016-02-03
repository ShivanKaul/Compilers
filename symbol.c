#include "symbol.h"
#include "memory.h"
#include "tree.h"

void createSymbolTable(DECL *decls, SYMBOL *sym) {
	while (decls) {
		SYMBOL *s;
  		s = NEW(SYMBOL);
		
		switch (decls->kind) :
			case floatK:
				s->id = decls->floatId;
				s->type = "float";
				break;
			case stringId:
				s->id = decls->stringId;
				s->type = "string";
				break;
			case intId:
				s->id = decls->intId;
				s->type = "int";
				break;
		s->next = sym;		
		decls = decls->next;
	}

}

int checkIfSymbolExists(SYMBOL *s, )