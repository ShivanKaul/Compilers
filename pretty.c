#include <stdio.h>
#include "pretty.h"
 
void prettyPROG(PROG *p, FILE* fp) {
    printf("DEBUG: pretty printing DECLS prettyPROG\n");
    prettyDECLS(p->decls, fp);
    printf("DEBUG: pretty printing of DECLS done, pretty printing STMTS now in prettyPROG\n");
    prettySTMTS(p->stmts, fp);
}

void prettyDECLS(DECL *d, FILE* fp) {
    if (d == NULL) {
        printf("DEBUG: D is null!\n");
        return;
    }

    switch (d->kind) {
        case floatK:
            fprintf(fp, "var %s : float;\n",d->val.floatId);
            break;
        case intK:
            fprintf(fp, "var %s : int;\n",d->val.intId);
            break;
        case stringK:
            fprintf(fp, "var %s : string;\n",d->val.stringId);
            break;
    }
    if (d->next != NULL) prettyDECLS(d->next, fp);
}

void prettySTMTS(STMT *s, FILE* fp) {
    if (s == NULL) {
        printf("DEBUG: S is null!\n");
        return;
    } 
    // else {
    //     printf("%s\n", s->kind);
    // }
    switch (s->kind) {
        case assign:
            fprintf(fp, "%s = ",s->val.assign.id);
            prettyEXP(s->val.assign.exp, fp);
            fprintf(fp, ";\n");
            break;
        case print:
            fprintf(fp, "print ");
            prettyEXP(s->val.printExp, fp);
            fprintf(fp, ";\n");
            break;
        case read:
            fprintf(fp, "read %s",s->val.readId);
            fprintf(fp, ";\n");
            break;
        case if_stmt:
            printf("DEBUG: Entered if_stmt of STMT\n");
            prettyIF(s->val.if_stmt, fp);
            break;
        case if_else_stmt:
            printf("DEBUG: Entered if_else_stmt of STMT\n");
            prettyIF(s->val.if_else_stmt, fp);
            break;
        case while_stmt:
            prettyWHILE(s->val.while_stmt, fp);
            break;
    }
    if (s->next != NULL) prettySTMTS(s->next, fp);
}

void prettyEXP(EXP *e, FILE* fp)
{ 
    switch (e->kind) {
    case id:
        fprintf(fp, "%s",e->val.id);
        break;

    case int_lit:
        fprintf(fp, "%d",e->val.int_lit);
        break;
    case float_lit:
        fprintf(fp, "%f",e->val.float_lit);
        break;
    case string_lit:
        printf("DEBUG: in string lit of exp\n");
        fprintf(fp, "%s",e->val.string_lit);
        break;

    case times:
        fprintf(fp, "(");
        prettyEXP(e->val.times.left, fp);
        fprintf(fp, "*");
        prettyEXP(e->val.times.right, fp);
        fprintf(fp, ")");
        break;
    case div:
        fprintf(fp, "(");
        prettyEXP(e->val.div.left, fp);
        fprintf(fp, "/");
        prettyEXP(e->val.div.right, fp);
        fprintf(fp, ")");
        break;
    case plus:
        fprintf(fp, "(");
        prettyEXP(e->val.plus.left, fp);
        fprintf(fp, "+");
        prettyEXP(e->val.plus.right, fp);
        fprintf(fp, ")");
        break;
    case minus:
        fprintf(fp, "(");
        prettyEXP(e->val.minus.left, fp);
        fprintf(fp, "-");
        prettyEXP(e->val.minus.right, fp);
        fprintf(fp, ")");
        break;
    case uminus:
        fprintf(fp, "(");
        fprintf(fp, "-");
        prettyEXP(e->val.uminus, fp);
        fprintf(fp, ")");
        break;
  }
}


void prettyWHILE(WHILE *w, FILE* fp) {
    fprintf(fp, "while ");
    prettyEXP(w->val.while_cond, fp);
    fprintf(fp, " do\n");
    prettySTMTS(w->val.do_cond, fp);
    fprintf(fp, "done\n");
}
void prettyIF(IF *i, FILE* fp) {
    printf("DEBUG: Entered prettyIF\n");

    switch (i->kind) {
        case no_else:
            printf("DEBUG: Entered no_else of prettyIF\n");
            fprintf(fp, "if ");
            prettyEXP(i->val.no_else.if_cond, fp);
            fprintf(fp, " then\n");
            prettySTMTS(i->val.no_else.then, fp);
            fprintf(fp, "endif\n");
            break;
        case yes_else:
            printf("DEBUG: Entered yes_else of prettyIF\n");

            fprintf(fp, "if ");
            prettyEXP(i->val.yes_else.if_cond, fp);
            fprintf(fp, " then\n");
            prettySTMTS(i->val.yes_else.then, fp);
            fprintf(fp, "else\n");
            prettySTMTS(i->val.yes_else.else_cond, fp);
            fprintf(fp, "endif\n");
            break;
    }
}

