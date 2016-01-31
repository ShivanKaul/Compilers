#ifndef TREE_H
#define TREE_H

typedef struct EXP {
  int yylineno;
  enum {id, int_lit, string_lit, float_lit, times, div, plus, minus} kind;
  union {
    char *id;
    int int_lit;
    float float_lit;
    char *string_lit;
    struct {struct EXP *left; struct EXP *right;} times;
    struct {struct EXP *left; struct EXP *right;} div;
    struct {struct EXP *left; struct EXP *right;} plus;
    struct {struct EXP *left; struct EXP *right;} minus;
  } val;
} EXP;

// typedef struct STMT {
//   int lineno;
//   enum {idK,intconstK,timesK,divK,plusK,minusK} kind;
//   union {
//     char *idE;
//     int intconstE;
//     struct {struct EXP *left; struct EXP *right;} timesE;
//     struct {struct EXP *left; struct EXP *right;} divE;
//     struct {struct EXP *left; struct EXP *right;} plusE;
//     struct {struct EXP *left; struct EXP *right;} minusE;
//   } val;
// } STMT;

// typedef struct DECL {
//   int lineno;
//   enum {idK,intconstK,timesK,divK,plusK,minusK} kind;
//   union {
//     char *idE;
//     int intconstE;
//     struct {struct EXP *left; struct EXP *right;} timesE;
//     struct {struct EXP *left; struct EXP *right;} divE;
//     struct {struct EXP *left; struct EXP *right;} plusE;
//     struct {struct EXP *left; struct EXP *right;} minusE;
//   } val;
// } DECL;
 
EXP *makeEXPid(char *id);

EXP *makeEXPint_lit(int int_lit);
EXP *makeEXPfloat_lit(float float_lit);
EXP *makeEXPstring_lit(char *string_lit);

EXP *makeEXPtimes(EXP *left, EXP *right);

EXP *makeEXPdiv(EXP *left, EXP *right);

EXP *makeEXPplus(EXP *left, EXP *right);

EXP *makeEXPminus(EXP *left, EXP *right);

#endif /* !TREE_H */

