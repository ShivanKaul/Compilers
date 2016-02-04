#include <stdio.h>
#include "typecheck.h"
#include "symbol.h"
#include <string.h>

// extern DECL *decls;

int typeCheck(STMT *stmts, DECL* decls) {
	STMT *s = stmts;

	printf("DEBUG: In typecheck function.\n");
	while (s) {
		switch (s->kind) {
			case assign : {
				// check if declared and if yes then what type
				// check if declared type == current type
				char *left = symbolExists(decls, s->val.assign.id);
				if (left) {
					printf("DEBUG: Symbol %s exists!\n", s->val.assign.id);
					char *right = typeCheckEXP(decls, s->val.assign.exp);
					if (!right) return 0;
					if (!strcmp(left, "int")) { // if left is int
						printf("DEBUG: left is %s\n", left);
						printf("DEBUG: right is %s\n", right);
						if (strcmp(right, "int")) { // right is not int
							printf("INVALID: line %d: cannot assign %s into a %s\n", s->yylineno, left, right);
							return 0;
						}
					} else if (!strcmp(left, "string"))  { // left is string
						printf("DEBUG: left is %s\n", left);
						printf("DEBUG: right is %s\n", right); 
						if (strcmp(right, "string")) { // right is not string
							printf("INVALID: line %d: cannot assign %s into a %s\n", s->yylineno, left, right);
							return 0;
						}
					} else if (!strcmp(left, "float")) { // left is float
						printf("DEBUG: left is %s\n", left);
						printf("DEBUG: right is %s\n", right);
						if (!strcmp(right, "string")) { // right is string
							printf("INVALID: line %d: cannot assign %s into a %s\n", s->yylineno, left, right);
							return 0;
						}
					}
				} else {
						printf("INVALID: line %d: %s not declared.\n", s->yylineno, s->val.assign.id);
						return 0;
				}
				break;
			}
			case if_stmt: {
				printf("DEBUG: if stmt encountered\n");
				char* exp_type = typeCheckEXP(decls, s->val.if_stmt->val.no_else.if_cond);
				if (strcmp(exp_type, "int")) { // not int
					printf("INVALID: line %d: expected int, found %s\n", s->yylineno, exp_type);
					return 0;
				}
				STMT *if_stmts = s->val.if_stmt->val.no_else.then;
				if (!typeCheck(if_stmts, decls)) return 0;
				break;
			}

			case while_stmt: {
				printf("DEBUG: while stmt encountered\n");
				char* exp_type = typeCheckEXP(decls, s->val.while_stmt->val.while_cond);
				if (strcmp(exp_type, "int")) { // not int
					printf("INVALID: line %d: expected int, found %s\n", s->yylineno, exp_type);
					return 0;
				}
				STMT *dos = s->val.while_stmt->val.do_cond;
				if (!typeCheck(dos, decls)) return 0;
				break;
			}

			case if_else_stmt: {
				printf("DEBUG: if else stmt encountered\n");
				char* exp_type = typeCheckEXP(decls, s->val.if_else_stmt->val.yes_else.if_cond);
				if (strcmp(exp_type, "int")) { // not int
					printf("INVALID: line %d: expected int, found %s\n", s->yylineno, exp_type);
					return 0;
				}
				printf("DEBUG: hurrah, exp is int!\n");
				STMT *if_stmts = s->val.if_stmt->val.yes_else.then;
				if (!typeCheck(if_stmts, decls)) return 0;
				printf("DEBUG: if stmts are fine, now checking else stmts\n");
				STMT *else_stmts = s->val.if_stmt->val.yes_else.else_cond;
				if (!typeCheck(else_stmts, decls)) return 0;
				break;
			}

			case print:
				break;

			case read:
				break;	
				
		}
		printf("DEBUG: Checking next stmt\n");
		s = s->next;
	}	
	return 1;
}

char* typeCheckEXP(DECL* decls, EXP *exp) {
	printf("DEBUG: type checking EXP.\n");
	switch (exp->kind) {
		case id:
			printf("DEBUG: in id case of typeCheckEXP.\n");
			if (exp->type) {
				printf("DEBUG: id type already determined: %s\n", exp->type);
				return exp->type;
			}
			printf("DEBUG: id type not yet determined!\n");
			exp->type = symbolExists(decls, exp->val.id);
			printf("DEBUG: found ID type %s\n", exp->type);
			return exp->type;

		case int_lit:
			printf("DEBUG: in int_lit case of typeCheckEXP.\n");
			if (exp->type) return exp->type;
			exp->type = "int";
			return exp->type;

		case float_lit:
			if (exp->type) return exp->type;
			exp->type = "float";
			return exp->type;

		case string_lit:
			printf("DEBUG: in string_lit case of typeCheckEXP.\n");
			if (exp->type) return exp->type;
			exp->type = "string";
			return exp->type;

		case times: {
			printf("DEBUG: In times.\n");
			char* left = typeCheckEXP(decls, exp->val.times.left);
			char* right = typeCheckEXP(decls, exp->val.times.right);
			printf("DEBUG: left is %s and right is %s\n", left, right);
			if (!strcmp(left, "int")) { // if left is int
				if (!strcmp(right, "int")) { // right is int
					exp->type = "int";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, right);
				return NULL;
			} else if (!strcmp(left, "float"))  {
				if (!strcmp(right, "int")) { // right is int
					exp->type = "float";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
				return NULL;
			} else {
				printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
			}
			break;
		}

		case div: {
			printf("DEBUG: In div.\n");
			char* left = typeCheckEXP(decls, exp->val.div.left);
			char* right = typeCheckEXP(decls, exp->val.div.right);
			printf("DEBUG: left is %s and right is %s\n", left, right);
			if (!strcmp(left, "int")) { // if left is int
				if (!strcmp(right, "int")) { // right is int
					exp->type = "int";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, right);
				return NULL;
			} else if (!strcmp(left, "float"))  {
				if (!strcmp(right, "int")) { // right is int
					exp->type = "float";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
				return NULL;
			} else {
				printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
			}
			break;
		}

		case plus: {
			printf("DEBUG: In div.\n");
			char* left = typeCheckEXP(decls, exp->val.plus.left);
			char* right = typeCheckEXP(decls, exp->val.plus.right);
			printf("DEBUG: left is %s and right is %s\n", left, right);
			if (!strcmp(left, "int")) { // if left is int
				if (!strcmp(right, "int")) { // right is int
					exp->type = "int";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, right);
				return NULL;
			} else if (!strcmp(left, "float"))  {
				if (!strcmp(right, "int")) { // right is int
					exp->type = "float";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
				return NULL;
			} else {
				// left is string
				if (strcmp(right, "string")) { // right is not string
					printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
				} else {
					exp->type = "string";
					return exp->type;
				}
				
			}
			break;
		}

		case minus: {
			printf("DEBUG: In div.\n");
			char* left = typeCheckEXP(decls, exp->val.minus.left);
			char* right = typeCheckEXP(decls, exp->val.minus.right);
			printf("DEBUG: left is %s and right is %s\n", left, right);
			if (!strcmp(left, "int")) { // if left is int
				if (!strcmp(right, "int")) { // right is int
					exp->type = "int";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, right);
				return NULL;
			} else if (!strcmp(left, "float"))  {
				if (!strcmp(right, "int")) { // right is int
					exp->type = "float";
					return exp->type;
				}
				else if (!strcmp(right, "float")) { // right is float
					exp->type = "float";
					return exp->type;
				}
				else printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
				return NULL;
			} else {
				// left is string
				if (strcmp(right, "string")) { // right is not string
					printf("INVALID: line %d: Cannot operate on a %s\n", exp->yylineno, left);
				} else {
					exp->type = "string";
					return exp->type;
				}
				
			}
			break;
		}

		case uminus: {
			printf("DEBUG: uminus\n");
			if (exp->type) {
				printf("DEBUG: id type already determined: %s\n", exp->type);
				return exp->type;
			}
			exp->type = typeCheckEXP(decls, exp->val.uminus);
			return exp->type;
		}
	}
	return NULL;
}