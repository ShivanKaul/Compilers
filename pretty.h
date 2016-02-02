#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyEXP(EXP *e, FILE* fp);
void prettyPROG(PROG *p, FILE* fp);
void prettyWHILE(WHILE *w, FILE* fp);
void prettyIF(IF *i, FILE* fp);
void prettyDECLS(DECL *d, FILE* fp);
void prettySTMTS(STMT *s, FILE* fp);


#endif /* !PRETTY_H */
