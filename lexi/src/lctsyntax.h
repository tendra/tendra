/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 102 "lctsyntax.act"


	#ifndef LCT_SYNTAX_H
	#define LCT_SYNTAX_H

	#include "code.h"
	#include "ast.h"

	struct lxi_additional_argument {
		char *name;
		char *ctype;

		struct lxi_additional_argument *next;
	};

	struct lct_ast {
		int headersdefined;
		int trailersdefined;

		struct code *hfileheader;
		struct code *cfileheader;
		struct code *hfiletrailer;
		struct code *cfiletrailer;

		struct lxi_additional_argument* arg_head;
		struct lxi_additional_argument** arg_tail;
	};

	extern struct ast *lxi_ast;
	extern struct lct_ast lct_ast;

	extern void init_lct_ast(struct lct_ast*);

#line 47 "lctsyntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_lct_unit(void);

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lct_lone_Hcode_Hat (10)
#define lct_code_Hend (9)
#define lct_code_Heof (12)
#define lct_kw_Htrailer (20)
#define lct_code_Href (16)
#define lct_comma (5)
#define lct_kw_Haction (21)
#define lct_unknown (18)
#define lct_ident (14)
#define lct_close (7)
#define lct_colon (0)
#define lct_code_Hat (11)
#define lct_arrow (1)
#define lct_open (6)
#define lct_eof (13)
#define lct_ref (2)
#define lct_semicolon (4)
#define lct_code_Hident (15)
#define lct_code_Hstring (17)
#define lct_define (3)
#define lct_kw_Hargument (22)
#define lct_code_Hstart (8)
#define lct_kw_Hheader (19)

/* BEGINNING OF TRAILER */

#line 337 "lctsyntax.act"


	#endif

#line 86 "lctsyntax.h"

/* END OF FILE */
