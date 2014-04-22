/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 81 "lctsyntax.act"


	/* $Id: lctsyntax.act 3048 2014-04-21 13:27:55Z kate $ */

	/*
	 * Copyright 2011, The TenDRA Project.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#include <stdbool.h>

	#include <shared/xalloc.h>
	#include <shared/error.h>

	#include <exds/common.h>
	#include <exds/exception.h>
	#include <exds/dalloc.h>
	#include <exds/dstring.h>
	#include <exds/cstring.h>

	#include <adt/action.h>
	#include <adt/entry.h>
	#include <adt/param.h>

	#include "lctsyntax.h"
	#include "lctlexer.h"
	#include "code.h"
	#include "ast.h"

	#define ADVANCE_LEXER    ADVANCE_LCT_LEXER
	#define CURRENT_TERMINAL CURRENT_LCT_TERMINAL
	#define SAVE_LEXER       SAVE_LCT_LEXER
	#define RESTORE_LEXER    RESTORE_LCT_LEXER

	typedef struct code *  codeP;
	typedef struct entry * entryP;
	typedef struct param * paramP;

	void
	init_lct_ast(struct lct_ast* a)
	{
		a->headersdefined  = 0;
		a->trailersdefined = 0;

		a->hfileheader  = NULL;
		a->cfileheader  = NULL;
		a->hfiletrailer = NULL;
		a->cfiletrailer = NULL;

		a->arg_head = NULL;
		a->arg_tail = &a->arg_head;
	}

	struct ast *lxi_ast;
	struct lct_ast lct_ast;

#line 71 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRaction_Hdefinition_C_Cparam_Hlist_C_Cparam_Hlist1(paramP *);
static void ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(paramP *, paramP *);
static void ZRcode_Hblock_C_Ccode_Helement(codeP *, entryP);
extern void read_lct_unit(void);
static void ZRstatement_Hlist(void);
static void ZRcode_Hblock_C_Ccode_Hbody(codeP *, entryP);
static void ZR78(void);
static void ZRargument_Hstmnt(void);
static void ZRheader_Hstmnt(void);
static void ZRaction_Hdefinition_C_Cparam_Hlist(paramP *);
static void ZRcode_Hblock(entryP, codeP *);
static void ZRstatement(void);
static void ZRtrailer_Hstmnt(void);
static void ZRaction_Hdefinition(void);
static void ZRaction_Hdefinition_C_Cparam_Hlist_C_Cparam(paramP *);
static void ZR99(void);
static void ZR106(NStringT *);
static void ZR108(void);
static void ZR114(paramP *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRaction_Hdefinition_C_Cparam_Hlist_C_Cparam_Hlist1(paramP *ZIa)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
ZL2_action_Hdefinition_C_Cparam_Hlist_C_Cparam_Hlist1:;
	{
		ZRaction_Hdefinition_C_Cparam_Hlist_C_Cparam (ZIa);
		/* BEGINNING OF INLINE: 115 */
		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: action-definition::param-list::param-list1 */
					goto ZL2_action_Hdefinition_C_Cparam_Hlist_C_Cparam_Hlist1;
					/* END OF INLINE: action-definition::param-list::param-list1 */
				}
				/*UNREACHED*/
			case 23:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 115 */
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(paramP *ZOin, paramP *ZOout)
{
	paramP ZIin;
	paramP ZIout;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			ADVANCE_LEXER;
			ZRaction_Hdefinition_C_Cparam_Hlist (&ZIin);
			/* BEGINNING OF INLINE: 97 */
			{
				if ((CURRENT_TERMINAL) == 23) {
					RESTORE_LEXER;
					goto ZL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case 1:
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: E_expected_arrow */
					{
#line 395 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected '->'");
	
#line 170 "lctsyntax.c"
					}
					/* END OF ACTION: E_expected_arrow */
				}
			ZL2:;
			}
			/* END OF INLINE: 97 */
			ZRaction_Hdefinition_C_Cparam_Hlist (&ZIout);
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: init-param */
			{
#line 266 "lctsyntax.act"

		(ZIin) = NULL;
	
#line 192 "lctsyntax.c"
			}
			/* END OF ACTION: init-param */
			/* BEGINNING OF ACTION: init-param */
			{
#line 266 "lctsyntax.act"

		(ZIout) = NULL;
	
#line 201 "lctsyntax.c"
			}
			/* END OF ACTION: init-param */
		}
		break;
	case 23:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (23);
	return;
ZL0:;
	*ZOin = ZIin;
	*ZOout = ZIout;
}

static void
ZRcode_Hblock_C_Ccode_Helement(codeP *ZIc, entryP ZIe)
{
	switch (CURRENT_TERMINAL) {
	case 11:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-code-at */
			{
#line 186 "lctsyntax.act"

		code_append_at((ZIc));
	
#line 231 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-at */
		}
		break;
	case 15:
		{
			NStringT ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-ident */
			{
#line 161 "lctsyntax.act"

		nstring_copy_cstring(&ZIi, lct_tokbuf);
	
#line 247 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: false */
			{
#line 175 "lctsyntax.act"
 (ZIb) = false; 
#line 255 "lctsyntax.c"
			}
			/* END OF ACTION: false */
			/* BEGINNING OF ACTION: append-code-ident */
			{
#line 194 "lctsyntax.act"

		if ((ZIe)) {
			struct action* act = entry_get_action((ZIe));
			struct param *p, *q;
			if ((p = param_name_is_in(action_get_inputs(act), (&ZIi))) ||
					(q = param_name_is_in(action_get_outputs(act), (&ZIi)))) {
				if (!(ZIb)) {
					code_append_ident((ZIc), (&ZIi));
				} else {
					if (p && p->is_ref) {
						code_append_ref((ZIc), (&ZIi));
					} else {
						error(ERROR_SERIOUS, "In code block the \'@&\' can only be used for input parameters that are references");
					}
				}
			} else {
				char* pi;
				char* pe;
				pi = nstring_to_cstring((&ZIi));
				nstring_destroy((&ZIi));
				pe = nstring_to_cstring(entry_key((ZIe)));
				error(ERROR_SERIOUS, "Identifier @%s is neither an input nor an output "
							 "parameter of action %s", pi, pe );
				xfree(pi);
				xfree(pe);
			}
		} else {
			error(ERROR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
			nstring_destroy((&ZIi));
		}
	
#line 292 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-ident */
		}
		break;
	case 16:
		{
			NStringT ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-ref */
			{
#line 165 "lctsyntax.act"

		nstring_copy_cstring(&ZIi, lct_tokbuf);
	
#line 308 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-ref */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: true */
			{
#line 174 "lctsyntax.act"
 (ZIb) = true;  
#line 316 "lctsyntax.c"
			}
			/* END OF ACTION: true */
			/* BEGINNING OF ACTION: append-code-ident */
			{
#line 194 "lctsyntax.act"

		if ((ZIe)) {
			struct action* act = entry_get_action((ZIe));
			struct param *p, *q;
			if ((p = param_name_is_in(action_get_inputs(act), (&ZIi))) ||
					(q = param_name_is_in(action_get_outputs(act), (&ZIi)))) {
				if (!(ZIb)) {
					code_append_ident((ZIc), (&ZIi));
				} else {
					if (p && p->is_ref) {
						code_append_ref((ZIc), (&ZIi));
					} else {
						error(ERROR_SERIOUS, "In code block the \'@&\' can only be used for input parameters that are references");
					}
				}
			} else {
				char* pi;
				char* pe;
				pi = nstring_to_cstring((&ZIi));
				nstring_destroy((&ZIi));
				pe = nstring_to_cstring(entry_key((ZIe)));
				error(ERROR_SERIOUS, "Identifier @%s is neither an input nor an output "
							 "parameter of action %s", pi, pe );
				xfree(pi);
				xfree(pe);
			}
		} else {
			error(ERROR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
			nstring_destroy((&ZIi));
		}
	
#line 353 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-ident */
		}
		break;
	case 17:
		{
			NStringT ZIs;

			/* BEGINNING OF EXTRACT: code-string */
			{
#line 169 "lctsyntax.act"

		nstring_assign(&ZIs, &lct_token_nstring);
	
#line 368 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-code-string */
			{
#line 190 "lctsyntax.act"

		code_append_string((ZIc), (&ZIs));
	
#line 378 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-string */
		}
		break;
	case 10:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: E_lone_at_in_code_block */
			{
#line 410 "lctsyntax.act"

		error(ERROR_SERIOUS, "Lone @ inside @{ @} block");
	
#line 392 "lctsyntax.c"
			}
			/* END OF ACTION: E_lone_at_in_code_block */
		}
		break;
	case 23:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

void
read_lct_unit(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		ZRstatement_Hlist ();
		switch (CURRENT_TERMINAL) {
		case 13:
			break;
		case 23:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E-syntax-error */
		{
#line 370 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 436 "lctsyntax.c"
		}
		/* END OF ACTION: E-syntax-error */
	}
}

static void
ZRstatement_Hlist(void)
{
ZL2_statement_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 19: case 20: case 21: case 22:
		{
			ZRstatement ();
			/* BEGINNING OF INLINE: statement-list */
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_statement_Hlist;
			}
			/* END OF INLINE: statement-list */
		}
		/*UNREACHED*/
	case 23:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRcode_Hblock_C_Ccode_Hbody(codeP *ZIc, entryP ZIe)
{
ZL2_code_Hblock_C_Ccode_Hbody:;
	switch (CURRENT_TERMINAL) {
	case 10: case 11: case 15: case 16:
	case 17:
		{
			ZRcode_Hblock_C_Ccode_Helement (ZIc, ZIe);
			/* BEGINNING OF INLINE: code-block::code-body */
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_code_Hblock_C_Ccode_Hbody;
			}
			/* END OF INLINE: code-block::code-body */
		}
		/*UNREACHED*/
	case 23:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZR78(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 5:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_comma */
		{
#line 386 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected ','");
	
#line 525 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_comma */
	}
}

static void
ZRargument_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		NStringT ZIname;
		NStringT ZIctype;

		switch (CURRENT_TERMINAL) {
		case 22:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR106 (&ZIname);
		/* BEGINNING OF INLINE: 105 */
		{
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_expected_colon */
				{
#line 403 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected ':'");
	
#line 573 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL2:;
		}
		/* END OF INLINE: 105 */
		ZR106 (&ZIctype);
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-additional-argument */
		{
#line 226 "lctsyntax.act"

		if (nstring_length((&ZIname)) > 0 && nstring_length((&ZIctype)) > 0) {
			struct lxi_additional_argument *p;

			p = xmalloc(sizeof *p);
			p->name  = nstring_to_cstring((&ZIname));
			p->ctype = nstring_to_cstring((&ZIctype));
			p->next  = NULL;

			*lct_ast.arg_tail = p;
			lct_ast.arg_tail = &p->next;
		}
		nstring_destroy((&ZIname));
		nstring_destroy((&ZIctype));
	
#line 603 "lctsyntax.c"
		}
		/* END OF ACTION: define-additional-argument */
		ZR108 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRheader_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		entryP ZIe;
		codeP ZIsc;
		codeP ZIsh;

		switch (CURRENT_TERMINAL) {
		case 19:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR99 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-entry */
		{
#line 305 "lctsyntax.act"

		(ZIe) = NULL;
	
#line 647 "lctsyntax.c"
		}
		/* END OF ACTION: null-entry */
		ZRcode_Hblock (ZIe, &ZIsc);
		ZR78 ();
		ZRcode_Hblock (ZIe, &ZIsh);
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: set-headers */
		{
#line 244 "lctsyntax.act"

		if (!lct_ast.trailersdefined) {
			lct_ast.headersdefined = 1;
			lct_ast.hfileheader = (ZIsh);
			lct_ast.cfileheader = (ZIsc);
		} else {
			error(ERROR_SERIOUS, "Headers may not be redefined");
			code_destroy((ZIsc));
			code_destroy((ZIsh));
		}
	
#line 671 "lctsyntax.c"
		}
		/* END OF ACTION: set-headers */
		ZR108 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRaction_Hdefinition_C_Cparam_Hlist(paramP *ZOa)
{
	paramP ZIa;

	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 6:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: init-param */
		{
#line 266 "lctsyntax.act"

		(ZIa) = NULL;
	
#line 708 "lctsyntax.c"
		}
		/* END OF ACTION: init-param */
		ZR114 (&ZIa);
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (23);
	return;
ZL0:;
	*ZOa = ZIa;
}

static void
ZRcode_Hblock(entryP ZIe, codeP *ZOc)
{
	codeP ZIc;

	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		/* BEGINNING OF INLINE: 67 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 8:
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_expected_code_start */
				{
#line 381 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected  '@{'");
	
#line 754 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_code_start */
			}
		ZL2:;
		}
		/* END OF INLINE: 67 */
		/* BEGINNING OF ACTION: init-code */
		{
#line 182 "lctsyntax.act"

		(ZIc) = NULL;
	
#line 767 "lctsyntax.c"
		}
		/* END OF ACTION: init-code */
		ZRcode_Hblock_C_Ccode_Hbody (&ZIc, ZIe);
		/* BEGINNING OF INLINE: 68 */
		{
			switch (CURRENT_TERMINAL) {
			case 12:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: E_unexpected_eof */
					{
#line 406 "lctsyntax.act"

		error(ERROR_SERIOUS, "Unexpected End of File inside @{ @} block");
	
#line 783 "lctsyntax.c"
					}
					/* END OF ACTION: E_unexpected_eof */
				}
				break;
			case 23:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 68 */
		/* BEGINNING OF INLINE: 69 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 9:
					break;
				default:
					goto ZL6;
				}
				ADVANCE_LEXER;
			}
			goto ZL5;
		ZL6:;
			{
				/* BEGINNING OF ACTION: E_expected_code_end */
				{
#line 373 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected  '@}'");
	
#line 816 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_code_end */
			}
		ZL5:;
		}
		/* END OF INLINE: 69 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (23);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRstatement(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ZRaction_Hdefinition ();
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 22:
		{
			ZRargument_Hstmnt ();
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 19:
		{
			ZRheader_Hstmnt ();
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 20:
		{
			ZRtrailer_Hstmnt ();
			if ((CURRENT_TERMINAL) == 23) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 23:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRtrailer_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		entryP ZIe;
		codeP ZIsc;
		codeP ZIsh;

		switch (CURRENT_TERMINAL) {
		case 20:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR99 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-entry */
		{
#line 305 "lctsyntax.act"

		(ZIe) = NULL;
	
#line 912 "lctsyntax.c"
		}
		/* END OF ACTION: null-entry */
		ZRcode_Hblock (ZIe, &ZIsc);
		ZR78 ();
		ZRcode_Hblock (ZIe, &ZIsh);
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: set-trailers */
		{
#line 256 "lctsyntax.act"

		if (!lct_ast.trailersdefined) {
			lct_ast.trailersdefined = 1;
			lct_ast.hfiletrailer = (ZIsh);
			lct_ast.cfiletrailer = (ZIsc);
		} else {
			error(ERROR_SERIOUS, "Trailers may not be redefined");
			code_destroy((ZIsc));
			code_destroy((ZIsh));
		}
	
#line 936 "lctsyntax.c"
		}
		/* END OF ACTION: set-trailers */
		ZR108 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRaction_Hdefinition(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		NStringT ZIn;
		paramP ZIin;
		paramP ZIout;
		entryP ZIea;
		codeP ZIc;

		switch (CURRENT_TERMINAL) {
		case 21:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR106 (&ZIn);
		ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn (&ZIin, &ZIout);
		ZR99 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: get-entry-action */
		{
#line 287 "lctsyntax.act"

		(ZIea) = table_get_entry(tree_get_table(lxi_ast), (&ZIn));
		if ((ZIea)) {
			if (!entry_is_action((ZIea))) {
				char* pi;
				(ZIea) = NULL; /*TODO skip to end of action */
				pi = nstring_to_cstring((&ZIn));
				error(ERROR_SERIOUS, "%s is not an action", pi);
				xfree(pi);
			}
		} else {
			char *pi = nstring_to_cstring((&ZIn));
			error(ERROR_SERIOUS, "Defining an undeclared action: %s", pi);
			xfree(pi);
		}
		nstring_destroy((&ZIn));
	
#line 998 "lctsyntax.c"
		}
		/* END OF ACTION: get-entry-action */
		/* BEGINNING OF ACTION: check-action-params */
		{
#line 309 "lctsyntax.act"

		if ((ZIea)) {
			/*TODO assert (entry_is_action((ZIea))); */
			/* TODO check that the same name does not appear twice in the input and output tuple */
			struct action *act = entry_get_action((ZIea));

			if (param_length(action_get_inputs(act)) != param_length((ZIin))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "Action %s declared with an incompatible number of inputs", pe);
				xfree(pe);
			} else if (!param_match(action_get_inputs(act), (ZIin))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "params do not match for action %s", pe);
				xfree(pe);
			} else {
				int allhavenames = param_assign_names(action_get_inputs(act), (ZIin));
				if (!allhavenames) {
					error(ERROR_SERIOUS, "outputs tuples in action definition should have names");
				}
			}

			if (param_length(action_get_outputs(act)) != param_length((ZIout))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "Action %s declared with an incompatible number of outputs", pe);
				xfree(pe);
			} else if (!param_match(action_get_outputs(act), (ZIout))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "results do not match for action %s", pe);
				xfree(pe);
			} else {
				int allhavenames = param_assign_names(action_get_outputs(act), (ZIout));
				if (!allhavenames) {
					char *pe = nstring_to_cstring(entry_key((ZIea)));
					error(ERROR_SERIOUS, "outputs tuples in the definition of action %s should have names", pe);
					xfree(pe);
				}
			}
		}

		param_destroy((ZIin));
		param_destroy((ZIout));
	
#line 1046 "lctsyntax.c"
		}
		/* END OF ACTION: check-action-params */
		ZRcode_Hblock (ZIea, &ZIc);
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-action */
		{
#line 352 "lctsyntax.act"

		if ((ZIea)) {
			/* TODO: assert entry_is_action */
			struct action *act = entry_get_action((ZIea));
			if (!action_is_defined(act)) {
				action_set_define(act);
				action_set_code(act, (ZIc));
			} else {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "Action %s has already been defined", pe);
				xfree(pe);
			}
		} else {
			code_destroy((ZIc));
		}
	
#line 1073 "lctsyntax.c"
		}
		/* END OF ACTION: define-action */
		ZR108 ();
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZRaction_Hdefinition_C_Cparam_Hlist_C_Cparam(paramP *ZIa)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		NStringT ZIn;
		NStringT ZIt;
		bool ZIisref;

		/* BEGINNING OF INLINE: 86 */
		{
			switch (CURRENT_TERMINAL) {
			case 14:
				{
					/* BEGINNING OF EXTRACT: ident */
					{
#line 157 "lctsyntax.act"

		nstring_copy_cstring(&ZIn, lct_tokbuf);
	
#line 1110 "lctsyntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-ident */
					{
#line 178 "lctsyntax.act"

		nstring_init(&(ZIn));
	
#line 1124 "lctsyntax.c"
					}
					/* END OF ACTION: empty-ident */
				}
				break;
			}
		}
		/* END OF INLINE: 86 */
		switch (CURRENT_TERMINAL) {
		case 0:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 14:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 157 "lctsyntax.act"

		nstring_copy_cstring(&ZIt, lct_tokbuf);
	
#line 1147 "lctsyntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 89 */
		{
			switch (CURRENT_TERMINAL) {
			case 2:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 174 "lctsyntax.act"
 (ZIisref) = true;  
#line 1165 "lctsyntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 175 "lctsyntax.act"
 (ZIisref) = false; 
#line 1176 "lctsyntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 89 */
		/* BEGINNING OF ACTION: append-param */
		{
#line 270 "lctsyntax.act"

		struct entry *et = table_get_entry(tree_get_table(lxi_ast), (&ZIt));
		if (et== NULL) {
			 char* pt = nstring_to_cstring((&ZIt));
			 error(ERROR_SERIOUS, "Unknown type %s", pt);
			 xfree(pt);
			 nstring_destroy((&ZIn));
			 nstring_destroy((&ZIt));
		} else if (!entry_is_type(et)) {
			error(ERROR_SERIOUS, "%s is not a type", (&ZIt));
			nstring_destroy((&ZIt));
		} else {
			param_append((ZIa), (&ZIn), et, (ZIisref));
			nstring_destroy((&ZIt));
		}
	
#line 1203 "lctsyntax.c"
		}
		/* END OF ACTION: append-param */
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

static void
ZR99(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 3:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_define */
		{
#line 391 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected '='");

	
#line 1238 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_define */
	}
}

static void
ZR106(NStringT *ZOctype)
{
	NStringT ZIctype;

	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 14:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 157 "lctsyntax.act"

		nstring_copy_cstring(&ZIctype, lct_tokbuf);
	
#line 1261 "lctsyntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: empty-ident */
		{
#line 178 "lctsyntax.act"

		nstring_init(&(ZIctype));
	
#line 1279 "lctsyntax.c"
		}
		/* END OF ACTION: empty-ident */
		/* BEGINNING OF ACTION: E_expected_ident */
		{
#line 378 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected  identifier");
	
#line 1288 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_ident */
	}
ZL0:;
	/* BEGINNING OF RESULT ASSIGNMENT: IDENT */
	{
#line 147 "lctsyntax.act"

		nstring_assign(ZOctype, (&ZIctype));
	#line 1298 "lctsyntax.c"
	}
	/* END OF RESULT ASSIGNMENT: IDENT */
}

static void
ZR108(void)
{
	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 4:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_semicolon */
		{
#line 399 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected ';'");
	
#line 1327 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZR114(paramP *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 7:
		{
			ADVANCE_LEXER;
		}
		break;
	case 0: case 14:
		{
			ZRaction_Hdefinition_C_Cparam_Hlist_C_Cparam_Hlist1 (ZIa);
			switch (CURRENT_TERMINAL) {
			case 7:
				break;
			case 23:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 23:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (23);
	return;
}

/* BEGINNING OF TRAILER */

#line 415 "lctsyntax.act"


#line 1373 "lctsyntax.c"

/* END OF FILE */
