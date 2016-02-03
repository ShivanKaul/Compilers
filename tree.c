#include "memory.h"
#include "tree.h"
#include <stdio.h> // for debugging

 
extern int yylineno;

PROG *makePROG(DECL *decls, STMT *stmts) { 
  printf("DEBUG: Making prog\n");
  PROG *e;
  e = NEW(PROG);
  e->yylineno = yylineno;
  e->decls = decls;
  e->stmts = stmts;
  return e;
}


STMT *makeSTMTassign(char *id, EXP *exp) { 
  STMT *e;
  e = NEW(STMT);
  e->yylineno = yylineno;
  e->kind = assign;
  e->val.assign.id = id;
  e->val.assign.exp = exp;
  return e;
}
STMT *makeSTMTread(char *id)
{ STMT *e;
  e = NEW(STMT);
  e->yylineno = yylineno;
  e->kind = read;
  e->val.assign.id = id;
  return e;
}
STMT *makeSTMTprint(EXP *exp)
{ STMT *e;
  e = NEW(STMT);
  e->yylineno = yylineno;
  e->kind = print;
  e->val.printExp = exp;
  return e;
}
STMT *makeSTMTif(EXP *exp, STMT *stmt_list) { 
  printf("DEBUG: STMT: Making IF\n");
  STMT *e;
  e = NEW(STMT);
  e->yylineno = yylineno;
  e->kind = if_stmt;
  e->val.if_stmt = makeIFif(exp, stmt_list);
  return e;
}
STMT *makeSTMTifElse(EXP *exp, STMT *stmt_list, STMT *else_stmt_list) { 
  printf("DEBUG: SMT: Making IF else\n");
  STMT *e;
  e = NEW(STMT);
  e->yylineno = yylineno;
  e->kind = if_else_stmt;
  e->val.if_else_stmt = makeIFifElse(exp, stmt_list, else_stmt_list);
  return e;
}
IF *makeIFif(EXP *exp, STMT *stmt_list) { 
  printf("DEBUG: IF: Making IF\n");
  IF *e;
  e = NEW(IF);
  e->yylineno = yylineno;
  e->kind = no_else;
  e->val.no_else.if_cond = exp;
  e->val.no_else.then = stmt_list;
  return e;
}
IF *makeIFifElse(EXP *exp, STMT *stmt_list, STMT *else_stmt_list) {
  printf("DEBUG: IF: Making IF ELSE\n");
  IF *e;
  e = NEW(IF);
  e->yylineno = yylineno;
  e->kind = yes_else;
  e->val.yes_else.if_cond = exp;
  e->val.yes_else.then = stmt_list;
  e->val.yes_else.else_cond = else_stmt_list;
  return e;
}
STMT *makeSTMTwhile(EXP *exp, STMT *stmt_list)
{ STMT *e;
  e = NEW(STMT);
  e->kind = while_stmt;
  e->yylineno = yylineno;
  e->val.while_stmt = makeWHILE(exp, stmt_list);
  return e;
}
WHILE *makeWHILE(EXP *exp, STMT *stmt_list)
{ WHILE *e;
  e = NEW(WHILE);
  e->yylineno = yylineno;
  e->val.while_cond = exp;
  e->val.do_cond = stmt_list;
  return e;
}

DECL *makeDECLfloat(char *id) {
  printf("DEBUG: Making float decl\n");

  DECL *e;
  e = NEW(DECL);
  e->yylineno = yylineno;
  e->kind = floatK;
  e->val.floatId = id;
  return e;
}
DECL *makeDECLint(char *id) {
  printf("DEBUG: Making int decl\n");
  DECL *e;
  e = NEW(DECL);
  e->yylineno = yylineno;
  e->kind = intK;
  e->val.intId = id;
  return e;
}
DECL *makeDECLstring(char *id) {
  printf("DEBUG: Making string decl\n");

  DECL *e;
  e = NEW(DECL);
  e->yylineno = yylineno;
  e->kind = stringK;
  e->val.stringId = id;
  return e;
}


EXP *makeEXPid(char *lit)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = id;
  e->val.id = lit;
  return e;
}

EXP *makeEXPint_lit(int lit)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = int_lit;
  e->val.int_lit = lit;
  return e;
}
EXP *makeEXPfloat_lit(float lit)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = float_lit;
  e->val.float_lit = lit;
  return e;
}
EXP *makeEXPstring_lit(char *lit)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = string_lit;
  e->val.string_lit = lit;
  return e;
}

EXP *makeEXPtimes(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = times;
  e->val.times.left = left;
  e->val.times.right = right;
  return e;
}

EXP *makeEXPdiv(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = div;
  e->val.div.left = left;
  e->val.div.right = right;
  return e; 
}

EXP *makeEXPplus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = plus;
  e->val.plus.left = left;
  e->val.plus.right = right;
  return e;
}

EXP *makeEXPminus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = minus;
  e->val.minus.left = left;
  e->val.minus.right = right;
  return e;
}
EXP *makeEXPUnaryMinus(EXP *exp)
{ EXP *e;
  e = NEW(EXP);
  e->yylineno = yylineno;
  e->kind = uminus;
  e->val.uminus = exp;
  return e;
}


