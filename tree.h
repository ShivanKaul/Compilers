#ifndef TREE_H
#define TREE_H

typedef struct EXP {
  int yylineno;
  char *type;
  enum {id, int_lit, string_lit, float_lit, times, div, plus, minus, uminus} kind;
  union {
    char *id;
    int int_lit;
    float float_lit;
    char *string_lit;
    struct {struct EXP *left; struct EXP *right;} times;
    struct {struct EXP *left; struct EXP *right;} div;
    struct {struct EXP *left; struct EXP *right;} plus;
    struct {struct EXP *left; struct EXP *right;} minus;
    struct EXP *uminus;
  } val;
} EXP;

typedef struct PROG {
  int yylineno;
  struct DECL *decls;
  struct STMT *stmts;
} PROG;

typedef struct STMT {
  int yylineno;
  enum {assign,print,read,if_stmt,if_else_stmt, while_stmt} kind;
  union {
    struct {char *id; struct EXP *exp;} assign;
    struct EXP *printExp;
    char *readId;
    struct IF *if_stmt;
    struct IF *if_else_stmt;
    struct WHILE *while_stmt;
  } val;
  struct STMT *next;
} STMT;

typedef struct DECL {
  int yylineno;
  enum {floatK,intK,stringK} kind;
  union {
    char* floatId;
    char* stringId;
    char* intId;
  } val;
  struct DECL *next;
} DECL;

typedef struct IF {
  int yylineno;
  enum {no_else, yes_else} kind;
  union {
    struct { struct EXP *if_cond; struct STMT *then;} no_else; // stmt list?
    struct { struct EXP *if_cond; struct STMT *then; struct STMT *else_cond ;} yes_else; // stmt list?
  } val;
} IF;

typedef struct WHILE {
  int yylineno;
  struct { struct EXP *while_cond; struct STMT *do_cond;} val;
} WHILE;

 
EXP *makeEXPid(char *id);
EXP *makeEXPint_lit(int int_lit);
EXP *makeEXPfloat_lit(float float_lit);
EXP *makeEXPstring_lit(char *string_lit);
EXP *makeEXPtimes(EXP *left, EXP *right);
EXP *makeEXPdiv(EXP *left, EXP *right);
EXP *makeEXPplus(EXP *left, EXP *right);
EXP *makeEXPminus(EXP *left, EXP *right);
EXP *makeEXPUnaryMinus(EXP *exp);

PROG *makePROG(DECL *decls, STMT *stmts);

STMT *makeSTMTassign(char *id, EXP *exp);
STMT *makeSTMTread(char *id);
STMT *makeSTMTprint(EXP *exp);

STMT *makeSTMTif(EXP *exp, STMT *stmt_list);
STMT *makeSTMTifElse(EXP *exp, STMT *stmt_list, STMT *else_stmt_list);
IF *makeIFif(EXP *exp, STMT *stmt_list);
IF *makeIFifElse(EXP *exp, STMT *stmt_list, STMT *else_stmt_list);
STMT *makeSTMTwhile(EXP *exp, STMT *stmt_list);
WHILE *makeWHILE(EXP *exp, STMT *stmt_list);

DECL *makeDECLfloat(char *id);
DECL *makeDECLint(char *id);
DECL *makeDECLstring(char *id);

#endif /* !TREE_H */