#include <stdio.h>
#include "pretty.h"
 
void prettyEXP(EXP *e, FILE* fp)
{ 
    switch (e->kind) {
    case id:
        fprintf(fp, "%s",e->val.id);
        break;

    case int_lit:
         fprintf(fp, "%i",e->val.int_lit);
         break;
    case float_lit:
         fprintf(fp, "%f",e->val.float_lit);
         break;
    case string_lit:
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
  }
}
