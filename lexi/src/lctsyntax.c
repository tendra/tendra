/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 71 "lctsyntax.act"


	#include <string.h>

	#include <shared/bool.h>
	#include <shared/check.h>
	#include <shared/xalloc.h>
	#include <shared/string.h>
	#include <shared/error.h>

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

	typedef char *         charP;
	typedef struct code *  codeP;
	typedef struct entry * entryP;
	typedef struct param * paramP;

	void
	init_lct_ast(struct lct_ast *a)
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

#line 61 "lctsyntax.c"

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
static void ZR106(charP *);
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
#line 317 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected '->'");
	
#line 160 "lctsyntax.c"
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
#line 217 "lctsyntax.act"

		(ZIin) = NULL;
	
#line 182 "lctsyntax.c"
			}
			/* END OF ACTION: init-param */
			/* BEGINNING OF ACTION: init-param */
			{
#line 217 "lctsyntax.act"

		(ZIout) = NULL;
	
#line 191 "lctsyntax.c"
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
#line 147 "lctsyntax.act"

		/* XXX: this should become just: s = <code-at>; <append-code-string>(s); */
		code_append_string((ZIc), "@");
	
#line 222 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-at */
		}
		break;
	case 15:
		{
			charP ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-ident */
			{
#line 121 "lctsyntax.act"

		ZIi = xstrdup(lct_tokbuf);
	
#line 238 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: false */
			{
#line 135 "lctsyntax.act"
 (ZIb) = 0; 
#line 246 "lctsyntax.c"
			}
			/* END OF ACTION: false */
			/* BEGINNING OF ACTION: append-code-ident */
			{
#line 155 "lctsyntax.act"

		if ((ZIe) == NULL) {
			error(ERR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
		} else {
			struct param *p, *q;

			if ((p = param_name_is_in((ZIe)->u.act->in, (ZIi))) ||
					(q = param_name_is_in((ZIe)->u.act->out, (ZIi)))) {
				if (!(ZIb)) {
					code_append_ident((ZIc), (ZIi));
				} else {
					if (p && p->is_ref) {
						code_append_ref((ZIc), (ZIi));
					} else {
						error(ERR_SERIOUS, "In code block the \'@&\' can only be used for input parameters that are references");
					}
				}
			} else {
				error(ERR_SERIOUS, "Identifier @%s is neither an input nor an output "
					"parameter of action %s", (ZIi), (ZIe)->key);
			}
		}
	
#line 275 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-ident */
		}
		break;
	case 16:
		{
			charP ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-ref */
			{
#line 125 "lctsyntax.act"

		ZIi = xstrdup(lct_tokbuf);
	
#line 291 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-ref */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: true */
			{
#line 134 "lctsyntax.act"
 (ZIb) = 1; 
#line 299 "lctsyntax.c"
			}
			/* END OF ACTION: true */
			/* BEGINNING OF ACTION: append-code-ident */
			{
#line 155 "lctsyntax.act"

		if ((ZIe) == NULL) {
			error(ERR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
		} else {
			struct param *p, *q;

			if ((p = param_name_is_in((ZIe)->u.act->in, (ZIi))) ||
					(q = param_name_is_in((ZIe)->u.act->out, (ZIi)))) {
				if (!(ZIb)) {
					code_append_ident((ZIc), (ZIi));
				} else {
					if (p && p->is_ref) {
						code_append_ref((ZIc), (ZIi));
					} else {
						error(ERR_SERIOUS, "In code block the \'@&\' can only be used for input parameters that are references");
					}
				}
			} else {
				error(ERR_SERIOUS, "Identifier @%s is neither an input nor an output "
					"parameter of action %s", (ZIi), (ZIe)->key);
			}
		}
	
#line 328 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-ident */
		}
		break;
	case 17:
		{
			charP ZIs;

			/* BEGINNING OF EXTRACT: code-string */
			{
#line 129 "lctsyntax.act"

		ZIs = lct_token_string;
	
#line 343 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-code-string */
			{
#line 151 "lctsyntax.act"

		code_append_string((ZIc), (ZIs));
	
#line 353 "lctsyntax.c"
			}
			/* END OF ACTION: append-code-string */
		}
		break;
	case 10:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: E_lone_at_in_code_block */
			{
#line 332 "lctsyntax.act"

		error(ERR_SERIOUS, "Lone @ inside @{ @} block");
	
#line 367 "lctsyntax.c"
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
#line 293 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error");
	
#line 411 "lctsyntax.c"
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
#line 309 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected ','");
	
#line 500 "lctsyntax.c"
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
		charP ZIname;
		charP ZIctype;

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
#line 325 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected ':'");
	
#line 548 "lctsyntax.c"
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
#line 179 "lctsyntax.act"

		if (strlen((ZIname)) > 0 && strlen((ZIctype)) > 0) {
			struct lxi_additional_argument *p;

			p = xmalloc(sizeof *p);
			p->name  = (ZIname);
			p->ctype = (ZIctype);
			p->next  = NULL;

			*lct_ast.arg_tail = p;
			lct_ast.arg_tail = &p->next;
		}
	
#line 576 "lctsyntax.c"
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
#line 242 "lctsyntax.act"

		(ZIe) = NULL;
	
#line 620 "lctsyntax.c"
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
#line 195 "lctsyntax.act"

		if (!lct_ast.trailersdefined) {
			lct_ast.headersdefined = 1;
			lct_ast.hfileheader = (ZIsh);
			lct_ast.cfileheader = (ZIsc);
		} else {
			error(ERR_SERIOUS, "Headers may not be redefined");
			code_destroy((ZIsc));
			code_destroy((ZIsh));
		}
	
#line 644 "lctsyntax.c"
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
#line 217 "lctsyntax.act"

		(ZIa) = NULL;
	
#line 681 "lctsyntax.c"
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
#line 304 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected  '@{'");
	
#line 727 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_code_start */
			}
		ZL2:;
		}
		/* END OF INLINE: 67 */
		/* BEGINNING OF ACTION: init-code */
		{
#line 142 "lctsyntax.act"

		(ZIc) = NULL;
	
#line 740 "lctsyntax.c"
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
#line 328 "lctsyntax.act"

		error(ERR_SERIOUS, "Unexpected End of File inside @{ @} block");
	
#line 756 "lctsyntax.c"
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
#line 296 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected  '@}'");
	
#line 789 "lctsyntax.c"
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
#line 242 "lctsyntax.act"

		(ZIe) = NULL;
	
#line 885 "lctsyntax.c"
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
#line 207 "lctsyntax.act"

		if (!lct_ast.trailersdefined) {
			lct_ast.trailersdefined = 1;
			lct_ast.hfiletrailer = (ZIsh);
			lct_ast.cfiletrailer = (ZIsc);
		} else {
			error(ERR_SERIOUS, "Trailers may not be redefined");
			code_destroy((ZIsc));
			code_destroy((ZIsh));
		}
	
#line 909 "lctsyntax.c"
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
		charP ZIn;
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
#line 232 "lctsyntax.act"

		(ZIea) = table_get_entry(&lxi_ast->table, (ZIn));
		if ((ZIea) == NULL) {
			error(ERR_SERIOUS, "Defining an undeclared action: %s", (ZIn));
		} else if ((ZIea)->kind != ENTRY_ACTION) {
			(ZIea) = NULL; /* TODO: skip to end of action */
			error(ERR_SERIOUS, "%s is not an action", (ZIn));
		}
	
#line 963 "lctsyntax.c"
		}
		/* END OF ACTION: get-entry-action */
		/* BEGINNING OF ACTION: check-action-params */
		{
#line 246 "lctsyntax.act"

		if ((ZIea)) {
			/* TODO: assert ((ZIea)->kind == ENTRY_ACTION); */
			/* TODO: check that the same name does not appear twice in the input and output tuple */

			if (param_length((ZIea)->u.act->in) != param_length((ZIin))) {
				error(ERR_SERIOUS, "Action %s declared with an incompatible number of inputs", (ZIea)->key);
			} else if (!param_match((ZIea)->u.act->in, (ZIin))) {
				error(ERR_SERIOUS, "params do not match for action %s", (ZIea)->key);
			} else {
				int allhavenames = param_assign_names((ZIea)->u.act->in, (ZIin));
				if (!allhavenames) {
					error(ERR_SERIOUS, "outputs tuples in action definition should have names");
				}
			}

			if (param_length((ZIea)->u.act->out) != param_length((ZIout))) {
				error(ERR_SERIOUS, "Action %s declared with an incompatible number of outputs", (ZIea)->key);
			} else if (!param_match((ZIea)->u.act->out, (ZIout))) {
				error(ERR_SERIOUS, "results do not match for action %s", (ZIea)->key);
			} else {
				int allhavenames = param_assign_names((ZIea)->u.act->out, (ZIout));
				if (!allhavenames) {
					error(ERR_SERIOUS, "outputs tuples in the definition of action %s should have names", (ZIea)->key);
				}
			}
		}

		param_destroy((ZIin));
		param_destroy((ZIout));
	
#line 1000 "lctsyntax.c"
		}
		/* END OF ACTION: check-action-params */
		ZRcode_Hblock (ZIea, &ZIc);
		if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-action */
		{
#line 278 "lctsyntax.act"

		if ((ZIea) == NULL) {
			code_destroy((ZIc));
		} else {
			/* TODO: assert (ZIea)->kind == ENTRY_ACTION */
			if (!(ZIea)->u.act->defined) {
				(ZIea)->u.act->defined = 1;
				(ZIea)->u.act->code    = (ZIc);
			} else {
				error(ERR_SERIOUS, "Action %s has already been defined", (ZIea)->key);
			}
		}
	
#line 1024 "lctsyntax.c"
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
		charP ZIn;
		charP ZIt;
		bool ZIisref;

		/* BEGINNING OF INLINE: 86 */
		{
			switch (CURRENT_TERMINAL) {
			case 14:
				{
					/* BEGINNING OF EXTRACT: ident */
					{
#line 117 "lctsyntax.act"

		ZIn = xstrdup(lct_tokbuf);
	
#line 1061 "lctsyntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-ident */
					{
#line 138 "lctsyntax.act"

		(ZIn) = NULL;
	
#line 1075 "lctsyntax.c"
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
#line 117 "lctsyntax.act"

		ZIt = xstrdup(lct_tokbuf);
	
#line 1098 "lctsyntax.c"
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
#line 134 "lctsyntax.act"
 (ZIisref) = 1; 
#line 1116 "lctsyntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 135 "lctsyntax.act"
 (ZIisref) = 0; 
#line 1127 "lctsyntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 89 */
		/* BEGINNING OF ACTION: append-param */
		{
#line 221 "lctsyntax.act"

		struct entry *et = table_get_entry(&lxi_ast->table, (ZIt));
		if (et == NULL) {
			error(ERR_SERIOUS, "Unknown type %s", (ZIt));
		} else if (et->kind != ENTRY_TYPE) {
			error(ERR_SERIOUS, "%s is not a type", (ZIt));
		} else {
			param_append((ZIa), (ZIn), et, (ZIisref));
		}
	
#line 1148 "lctsyntax.c"
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
#line 313 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected '='");
	
#line 1182 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_define */
	}
}

static void
ZR106(charP *ZOctype)
{
	charP ZIctype;

	if ((CURRENT_TERMINAL) == 23) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 14:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 117 "lctsyntax.act"

		ZIctype = xstrdup(lct_tokbuf);
	
#line 1205 "lctsyntax.c"
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
#line 138 "lctsyntax.act"

		(ZIctype) = NULL;
	
#line 1223 "lctsyntax.c"
		}
		/* END OF ACTION: empty-ident */
		/* BEGINNING OF ACTION: E_expected_ident */
		{
#line 301 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected  identifier");
	
#line 1232 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_ident */
	}
ZL0:;
	*ZOctype = ZIctype;
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
#line 321 "lctsyntax.act"

		error(ERR_SERIOUS, "Syntax error: expected ';'");
	
#line 1264 "lctsyntax.c"
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

#line 337 "lctsyntax.act"


#line 1310 "lctsyntax.c"

/* END OF FILE */
