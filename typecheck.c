#include <stdio.h>
#include "typecheck.h"
#include "symbol.h"
#include <string.h>

// extern DECL *decls;

int typeCheck(STMT *stmts, DECL* decls) {
	STMT *s = stmts;

	while (s) {
		switch (s->kind) {
			case assign : {
				// check if declared and if yes then what type
				// check if declared type == current type
				char *left = symbolExists(decls, s->val.assign.id);
				if (left) {
					char *right = typeCheckEXP(decls, s->val.assign.exp);
					if (!right) return 0;
					if (!strcmp(left, "int")) { // if left is int
						if (strcmp(right, "int")) { // right is not int
							printf("INVALID: line %d: cannot assign %s into a %s\n", s->yylineno, left, right);
							return 0;
						}
					} else if (!strcmp(left, "string"))  { // left is string
						if (strcmp(right, "string")) { // right is not string
							printf("INVALID: line %d: cannot assign %s into a %s\n", s->yylineno, left, right);
							return 0;
						}
					} else if (!strcmp(left, "float")) { // left is float
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
				char* exp_type = typeCheckEXP(decls, s->val.if_else_stmt->val.yes_else.if_cond);
				if (strcmp(exp_type, "int")) { // not int
					printf("INVALID: line %d: expected int, found %s\n", s->yylineno, exp_type);
					return 0;
				}
				STMT *if_stmts = s->val.if_stmt->val.yes_else.then;
				if (!typeCheck(if_stmts, decls)) return 0;
				STMT *else_stmts = s->val.if_stmt->val.yes_else.else_cond;
				if (!typeCheck(else_stmts, decls)) return 0;
				break;
			}

			case print:
				break;

			case read:
				break;	
				
		}
		s = s->next;
	}	
	return 1;
}

char* typeCheckEXP(DECL* decls, EXP *exp) {
	switch (exp->kind) {
		case id:
			if (exp->type) {
				return exp->type;
			}
			exp->type = symbolExists(decls, exp->val.id);
			return exp->type;

		case int_lit:
			if (exp->type) return exp->type;
			exp->type = "int";
			return exp->type;

		case float_lit:
			if (exp->type) return exp->type;
			exp->type = "float";
			return exp->type;

		case string_lit:
			if (exp->type) return exp->type;
			exp->type = "string";
			return exp->type;

		case times: {
			char* left = typeCheckEXP(decls, exp->val.times.left);
			char* right = typeCheckEXP(decls, exp->val.times.right);
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
			char* left = typeCheckEXP(decls, exp->val.div.left);
			char* right = typeCheckEXP(decls, exp->val.div.right);
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
			char* left = typeCheckEXP(decls, exp->val.plus.left);
			char* right = typeCheckEXP(decls, exp->val.plus.right);
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
			char* left = typeCheckEXP(decls, exp->val.minus.left);
			char* right = typeCheckEXP(decls, exp->val.minus.right);
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
			if (exp->type) {
				return exp->type;
			}
			exp->type = typeCheckEXP(decls, exp->val.uminus);
			return exp->type;
		}
	}
	return NULL;
}