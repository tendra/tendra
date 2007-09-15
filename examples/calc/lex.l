%{
#include "calc.h"
%}
%%

[ \t]  { /* skip */ }
[0-9]+ { val = atoi(yytext);
         return T_number;  }
"("    { return T_lparen;  }
")"    { return T_rparen;  }
"*"    { return T_mul;     }
"/"    { return T_div;     }
"%"    { return T_mod;     }
"+"    { return T_add;     }
"-"    { return T_sub;     }
"\n"   { return T_newline; }
.      { fprintf(stderr, "invalid character '%s'\n", yytext);
         return T_error;   }

%%
int yywrap(void) {
	return 1;
}
