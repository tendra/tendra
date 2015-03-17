%{
#include "lexer.h"

#include <stdio.h>
#include <string.h>

#include "infix.h"
#include "rpn.h"
#include "lexer.h"

int tok, val;
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

int main(int argc, char *argv[]) {
	int rpn = 0;

	if (argc > 2) {
		goto usage;
	}

	if (argc == 2) {
		if (0 == strcmp(argv[1], "-r")) {
			rpn = 1;
		} else {
			goto usage;
		}
	}

	tok = yylex();

	if (rpn) {
		p_rpn_Hexpressions();
	} else {
		p_infix_Hexpressions();
	}

	return 0;

usage:
	fprintf(stderr, "usage: mcalc [-r]\n");
	return 1;
}

