#include "memory.h"
#include "tree.h"
 
extern int yylineno;

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
