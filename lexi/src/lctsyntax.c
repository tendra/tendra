/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 80 "lctsyntax.act"


	/* $Id: lctsyntax.act 3035 2014-04-19 21:52:31Z kate $ */

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

	#include "lctsyntax.h"
	#include "lctlexer.h"
	#include "ccode.h"
	#include "ast.h"

	#define ADVANCE_LEXER ADVANCE_LCT_LEXER
	#define CURRENT_TERMINAL CURRENT_LCT_TERMINAL
	#define SAVE_LEXER SAVE_LCT_LEXER
	#define RESTORE_LEXER RESTORE_LCT_LEXER

	typedef struct CcodeT ccode;
	typedef struct entry * EntryP;
	typedef struct TypeTupleT typetuple;

	void
	init_lct_ast(struct lct_ast* a)
	{
		a->headersdefined  = 0;
		a->trailersdefined = 0;

		ccode_init(&(a->hfileheader));
		ccode_init(&(a->cfileheader));
		ccode_init(&(a->hfiletrailer));
		ccode_init(&(a->cfiletrailer));

		a->arg_head = NULL;
		a->arg_tail = &a->arg_head;
	}

	struct ast *lxi_ast;
	struct lct_ast lct_ast;

#line 70 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(typetuple *);
static void ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(typetuple *, typetuple *);
static void ZRcode_Hblock_C_Ccode_Helement(ccode *, EntryP);
static void ZRmap_Hstmnt(void);
extern void read_lct_unit(void);
static void ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1(typetuple *);
static void ZRstatement_Hlist(void);
static void ZRcode_Hblock_C_Ccode_Hbody(ccode *, EntryP);
static void ZR80(void);
static void ZRargument_Hstmnt(void);
static void ZRheader_Hstmnt(void);
static void ZRcode_Hblock(EntryP, ccode *);
static void ZRstatement(void);
static void ZRtrailer_Hstmnt(void);
static void ZRaction_Hdefinition(void);
static void ZR104(void);
static void ZR106(void);
static void ZR113(NStringT *);
static void ZR114(void);
static void ZRaction_Hdefinition_C_Ctype_Htuple(typetuple *);
static void ZR120(typetuple *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(typetuple *ZIa)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		NStringT ZIn;
		NStringT ZIt;
		bool ZIisref;

		/* BEGINNING OF INLINE: 93 */
		{
			switch (CURRENT_TERMINAL) {
			case 14:
				{
					/* BEGINNING OF EXTRACT: ident */
					{
#line 156 "lctsyntax.act"

		nstring_copy_cstring(&ZIn, lct_tokbuf);
	
#line 123 "lctsyntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-ident */
					{
#line 177 "lctsyntax.act"

		nstring_init(&(ZIn));
	
#line 137 "lctsyntax.c"
					}
					/* END OF ACTION: empty-ident */
				}
				break;
			}
		}
		/* END OF INLINE: 93 */
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
#line 156 "lctsyntax.act"

		nstring_copy_cstring(&ZIt, lct_tokbuf);
	
#line 160 "lctsyntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 96 */
		{
			switch (CURRENT_TERMINAL) {
			case 2:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 173 "lctsyntax.act"
 (ZIisref) = true ; 
#line 178 "lctsyntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 174 "lctsyntax.act"
 (ZIisref) = false ; 
#line 189 "lctsyntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 96 */
		/* BEGINNING OF ACTION: append-tuple */
		{
#line 274 "lctsyntax.act"

		struct entry *et = table_get_entry(tree_get_table(lxi_ast), (&ZIt));
		if (et== NULL) {
			 char* pt = nstring_to_cstring((&ZIt));
			 error(ERROR_SERIOUS, "Unknown type %s", pt);
			 xfree(pt);
			 nstring_destroy((&ZIn));
			 nstring_destroy((&ZIt));
		}
		else if (!entry_is_type(et)) {
		error(ERROR_SERIOUS, "%s is not a type", (&ZIt));
			nstring_destroy((&ZIt));
		}
		else {
			typetuple_append((ZIa), typetupleentry_create((&ZIn), et, (ZIisref)));
			nstring_destroy((&ZIt));
		}
	
#line 218 "lctsyntax.c"
		}
		/* END OF ACTION: append-tuple */
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(typetuple *ZOin, typetuple *ZOout)
{
	typetuple ZIin;
	typetuple ZIout;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			ADVANCE_LEXER;
			ZRaction_Hdefinition_C_Ctype_Htuple (&ZIin);
			ZR104 ();
			ZRaction_Hdefinition_C_Ctype_Htuple (&ZIout);
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 270 "lctsyntax.act"

		typetuple_init(&(ZIin));
	
#line 255 "lctsyntax.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 270 "lctsyntax.act"

		typetuple_init(&(ZIout));
	
#line 264 "lctsyntax.c"
			}
			/* END OF ACTION: init-tuple */
		}
		break;
	case 24:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (24);
	return;
ZL0:;
	*ZOin = ZIin;
	*ZOout = ZIout;
}

static void
ZRcode_Hblock_C_Ccode_Helement(ccode *ZIc, EntryP ZIe)
{
	switch (CURRENT_TERMINAL) {
	case 11:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-at */
			{
#line 185 "lctsyntax.act"

		ccode_append_at(&(*ZIc));
	
#line 294 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-at */
		}
		break;
	case 15:
		{
			NStringT ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-ident */
			{
#line 160 "lctsyntax.act"

		nstring_copy_cstring(&ZIi, lct_tokbuf);
	
#line 310 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: false */
			{
#line 174 "lctsyntax.act"
 (ZIb) = false ; 
#line 318 "lctsyntax.c"
			}
			/* END OF ACTION: false */
			/* BEGINNING OF ACTION: append-ccode-ident */
			{
#line 193 "lctsyntax.act"

		if ((ZIe)) {
			struct action* act = entry_get_action((ZIe));
			struct TypeTupleEntryT *p, *q;
			if ((p = typetuple_name_is_in(action_get_inputs(act), (&ZIi))) ||
					(q = typetuple_name_is_in(action_get_outputs(act), (&ZIi)))) {
				if (!(ZIb)) {
					ccode_append_ident((ZIc), (&ZIi));
				} else {
					if (p && p->is_ref) {
						ccode_append_ref((ZIc), (&ZIi));
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
	
#line 355 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-ident */
		}
		break;
	case 16:
		{
			NStringT ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-ref */
			{
#line 164 "lctsyntax.act"

		nstring_copy_cstring(&ZIi, lct_tokbuf);
	
#line 371 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-ref */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: true */
			{
#line 173 "lctsyntax.act"
 (ZIb) = true ; 
#line 379 "lctsyntax.c"
			}
			/* END OF ACTION: true */
			/* BEGINNING OF ACTION: append-ccode-ident */
			{
#line 193 "lctsyntax.act"

		if ((ZIe)) {
			struct action* act = entry_get_action((ZIe));
			struct TypeTupleEntryT *p, *q;
			if ((p = typetuple_name_is_in(action_get_inputs(act), (&ZIi))) ||
					(q = typetuple_name_is_in(action_get_outputs(act), (&ZIi)))) {
				if (!(ZIb)) {
					ccode_append_ident((ZIc), (&ZIi));
				} else {
					if (p && p->is_ref) {
						ccode_append_ref((ZIc), (&ZIi));
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
	
#line 416 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-ident */
		}
		break;
	case 17:
		{
			NStringT ZIs;

			/* BEGINNING OF EXTRACT: code-string */
			{
#line 168 "lctsyntax.act"

		nstring_assign(&ZIs, &lct_token_nstring);
	
#line 431 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-string */
			{
#line 189 "lctsyntax.act"

		ccode_append_string((ZIc), (&ZIs));
	
#line 441 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-string */
		}
		break;
	case 10:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: E_lone_at_in_code_block */
			{
#line 433 "lctsyntax.act"

		error(ERROR_SERIOUS, "Lone @ inside @{ @} block");
	
#line 455 "lctsyntax.c"
			}
			/* END OF ACTION: E_lone_at_in_code_block */
		}
		break;
	case 24:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRmap_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		NStringT ZIlexitype;
		NStringT ZIctype;

		switch (CURRENT_TERMINAL) {
		case 21:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 14:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 156 "lctsyntax.act"

		nstring_copy_cstring(&ZIlexitype, lct_tokbuf);
	
#line 496 "lctsyntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR104 ();
		switch (CURRENT_TERMINAL) {
		case 14:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 156 "lctsyntax.act"

		nstring_copy_cstring(&ZIctype, lct_tokbuf);
	
#line 513 "lctsyntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		case 24:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make-map */
		{
#line 293 "lctsyntax.act"

		struct entry *et= table_get_entry(tree_get_table(lxi_ast), (&ZIlexitype));
		if (et != NULL) {
			if (entry_is_type(et)) {
				struct type* t = entry_get_type(et);
				type_map(t, (&ZIctype));
			} else {
			error(ERROR_SERIOUS, "Name in maps section is not a type");
				nstring_destroy((&ZIctype));
			}
		} else {
		error(ERROR_SERIOUS, "Unknown type in mapping");
			nstring_destroy((&ZIctype));
		}
		nstring_destroy((&ZIlexitype));
	
#line 543 "lctsyntax.c"
		}
		/* END OF ACTION: make-map */
		ZR114 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

void
read_lct_unit(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		ZRstatement_Hlist ();
		switch (CURRENT_TERMINAL) {
		case 13:
			break;
		case 24:
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
#line 393 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 586 "lctsyntax.c"
		}
		/* END OF ACTION: E-syntax-error */
	}
}

static void
ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1(typetuple *ZIa)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
ZL2_action_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1:;
	{
		ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname (ZIa);
		/* BEGINNING OF INLINE: 121 */
		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: action-definition::type-tuple::type-tuple1 */
					goto ZL2_action_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1;
					/* END OF INLINE: action-definition::type-tuple::type-tuple1 */
				}
				/*UNREACHED*/
			case 24:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 121 */
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRstatement_Hlist(void)
{
ZL2_statement_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 19: case 20: case 21: case 22:
	case 23:
		{
			ZRstatement ();
			/* BEGINNING OF INLINE: statement-list */
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_statement_Hlist;
			}
			/* END OF INLINE: statement-list */
		}
		/*UNREACHED*/
	case 24:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRcode_Hblock_C_Ccode_Hbody(ccode *ZIc, EntryP ZIe)
{
ZL2_code_Hblock_C_Ccode_Hbody:;
	switch (CURRENT_TERMINAL) {
	case 10: case 11: case 15: case 16:
	case 17:
		{
			ZRcode_Hblock_C_Ccode_Helement (ZIc, ZIe);
			/* BEGINNING OF INLINE: code-block::code-body */
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_code_Hblock_C_Ccode_Hbody;
			}
			/* END OF INLINE: code-block::code-body */
		}
		/*UNREACHED*/
	case 24:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZR80(void)
{
	if ((CURRENT_TERMINAL) == 24) {
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
#line 409 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected ','");
	
#line 711 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_comma */
	}
}

static void
ZRargument_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		NStringT ZIname;
		NStringT ZIctype;

		switch (CURRENT_TERMINAL) {
		case 23:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR113 (&ZIname);
		/* BEGINNING OF INLINE: 112 */
		{
			if ((CURRENT_TERMINAL) == 24) {
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
#line 426 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected ':'");
	
#line 759 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL2:;
		}
		/* END OF INLINE: 112 */
		ZR113 (&ZIctype);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-additional-argument */
		{
#line 225 "lctsyntax.act"

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
	
#line 789 "lctsyntax.c"
		}
		/* END OF ACTION: define-additional-argument */
		ZR114 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRheader_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		EntryP ZIe;
		ccode ZIsc;
		ccode ZIsh;

		switch (CURRENT_TERMINAL) {
		case 19:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR106 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-entry */
		{
#line 329 "lctsyntax.act"

		(ZIe)=NULL;
	
#line 833 "lctsyntax.c"
		}
		/* END OF ACTION: null-entry */
		ZRcode_Hblock (ZIe, &ZIsc);
		ZR80 ();
		ZRcode_Hblock (ZIe, &ZIsh);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: set-headers */
		{
#line 243 "lctsyntax.act"

		if (!lct_ast.trailersdefined) {
			lct_ast.headersdefined = 1;
			ccode_assign(&(lct_ast.hfileheader), (&ZIsh));
			ccode_assign(&(lct_ast.cfileheader), (&ZIsc));
		} else {
		error(ERROR_SERIOUS, "Headers may not be redefined");
			ccode_destroy((&ZIsc));
			ccode_destroy((&ZIsh));
		}
	
#line 857 "lctsyntax.c"
		}
		/* END OF ACTION: set-headers */
		ZR114 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRcode_Hblock(EntryP ZIe, ccode *ZOc)
{
	ccode ZIc;

	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		/* BEGINNING OF INLINE: 69 */
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
#line 404 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected  '@{'");
	
#line 901 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_code_start */
			}
		ZL2:;
		}
		/* END OF INLINE: 69 */
		/* BEGINNING OF ACTION: init-ccode */
		{
#line 181 "lctsyntax.act"

		ccode_init(&(ZIc));
	
#line 914 "lctsyntax.c"
		}
		/* END OF ACTION: init-ccode */
		ZRcode_Hblock_C_Ccode_Hbody (&ZIc, ZIe);
		/* BEGINNING OF INLINE: 70 */
		{
			switch (CURRENT_TERMINAL) {
			case 12:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: E_unexpected_eof */
					{
#line 429 "lctsyntax.act"

		error(ERROR_SERIOUS, "Unexpected End of File inside @{ @} block");
	
#line 930 "lctsyntax.c"
					}
					/* END OF ACTION: E_unexpected_eof */
				}
				break;
			case 24:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 70 */
		/* BEGINNING OF INLINE: 71 */
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
#line 396 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected  '@}'");
	
#line 963 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_code_end */
			}
		ZL5:;
		}
		/* END OF INLINE: 71 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (24);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRstatement(void)
{
	switch (CURRENT_TERMINAL) {
	case 22:
		{
			ZRaction_Hdefinition ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 23:
		{
			ZRargument_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 19:
		{
			ZRheader_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 21:
		{
			ZRmap_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 20:
		{
			ZRtrailer_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 24:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRtrailer_Hstmnt(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		EntryP ZIe;
		ccode ZIsc;
		ccode ZIsh;

		switch (CURRENT_TERMINAL) {
		case 20:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR106 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-entry */
		{
#line 329 "lctsyntax.act"

		(ZIe)=NULL;
	
#line 1068 "lctsyntax.c"
		}
		/* END OF ACTION: null-entry */
		ZRcode_Hblock (ZIe, &ZIsc);
		ZR80 ();
		ZRcode_Hblock (ZIe, &ZIsh);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: set-trailers */
		{
#line 255 "lctsyntax.act"

		if (!(lct_ast.trailersdefined)) {
			lct_ast.trailersdefined = 1;
			ccode_assign(&(lct_ast.hfiletrailer), (&ZIsh));
			ccode_assign(&(lct_ast.cfiletrailer), (&ZIsc));
		} else {
			error(ERROR_SERIOUS, "Trailers may not be redefined");
			ccode_destroy((&ZIsc));
			ccode_destroy((&ZIsh));
		}
	
#line 1092 "lctsyntax.c"
		}
		/* END OF ACTION: set-trailers */
		ZR114 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRaction_Hdefinition(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		NStringT ZIn;
		typetuple ZIin;
		typetuple ZIout;
		EntryP ZIea;
		ccode ZIc;

		switch (CURRENT_TERMINAL) {
		case 22:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR113 (&ZIn);
		ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn (&ZIin, &ZIout);
		ZR106 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: get-entry-action */
		{
#line 311 "lctsyntax.act"

		(ZIea)=table_get_entry(tree_get_table(lxi_ast), (&ZIn));
		if ((ZIea)) {
			if (!entry_is_action((ZIea))) {
				char* pi;
				(ZIea)=NULL; /*TODO skip to end of action */
				pi = nstring_to_cstring((&ZIn));
			error(ERROR_SERIOUS, "%s is not an action", pi);
				xfree(pi);
			}
		} else {
			char* pi = nstring_to_cstring((&ZIn));
		error(ERROR_SERIOUS, "Defining an undeclared action: %s", pi);
			xfree(pi);
		}
		nstring_destroy((&ZIn));
	
#line 1154 "lctsyntax.c"
		}
		/* END OF ACTION: get-entry-action */
		/* BEGINNING OF ACTION: check-action-tuples */
		{
#line 333 "lctsyntax.act"

		if ((ZIea)) {
			/*TODO assert (entry_is_action((ZIea))); */
			/* TODO check that the same name does not appear twice in the input and output tuple */
			struct action *act = entry_get_action((ZIea));

			if (typetuple_length(action_get_inputs(act)) != typetuple_length((&ZIin))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "Action %s declared with an incompatible number of inputs", pe);
				xfree(pe);
			} else if (!typetuple_match(action_get_inputs(act), (&ZIin))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "params do not match for action %s", pe);
				xfree(pe);
			} else {
				int allhavenames = typetuple_assign_names(action_get_inputs(act), (&ZIin));
				if (!allhavenames) {
					error(ERROR_SERIOUS, "outputs tuples in action definition should have names");
				}
			}

			if (typetuple_length(action_get_outputs(act)) != typetuple_length((&ZIout))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "Action %s declared with an incompatible number of outputs", pe);
				xfree(pe);
			} else if (!typetuple_match(action_get_outputs(act), (&ZIout))) {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "results do not match for action %s", pe);
				xfree(pe);
			} else {
				int allhavenames = typetuple_assign_names(action_get_outputs(act), (&ZIout));
				if (!allhavenames) {
					char *pe = nstring_to_cstring(entry_key((ZIea)));
					error(ERROR_SERIOUS, "outputs tuples in the definition of action %s should have names", pe);
					xfree(pe);
				}
			}
		}
		typetuple_destroy((&ZIin));
		typetuple_destroy((&ZIout));
	
#line 1201 "lctsyntax.c"
		}
		/* END OF ACTION: check-action-tuples */
		ZRcode_Hblock (ZIea, &ZIc);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-action */
		{
#line 375 "lctsyntax.act"

		if ((ZIea)) {
			/* TODO: assert entry_is_action */
			struct action *act = entry_get_action((ZIea));
			if (!action_is_defined(act)) {
				action_set_define(act);
				action_set_code(act, (&ZIc));
			} else {
				char *pe = nstring_to_cstring(entry_key((ZIea)));
				error(ERROR_SERIOUS, "Action %s has already been defined", pe);
				xfree(pe);
			}
		} else {
			ccode_destroy((&ZIc));
		}
	
#line 1228 "lctsyntax.c"
		}
		/* END OF ACTION: define-action */
		ZR114 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZR104(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 1:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_arrow */
		{
#line 418 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected '->'");
	
#line 1267 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_arrow */
	}
}

static void
ZR106(void)
{
	if ((CURRENT_TERMINAL) == 24) {
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
#line 414 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected '='");

	
#line 1298 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_define */
	}
}

static void
ZR113(NStringT *ZOctype)
{
	NStringT ZIctype;

	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 14:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 156 "lctsyntax.act"

		nstring_copy_cstring(&ZIctype, lct_tokbuf);
	
#line 1321 "lctsyntax.c"
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
#line 177 "lctsyntax.act"

		nstring_init(&(ZIctype));
	
#line 1339 "lctsyntax.c"
		}
		/* END OF ACTION: empty-ident */
		/* BEGINNING OF ACTION: E_expected_ident */
		{
#line 401 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected  identifier");
	
#line 1348 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_ident */
	}
ZL0:;
	/* BEGINNING OF RESULT ASSIGNMENT: IDENT */
	{
#line 146 "lctsyntax.act"

		nstring_assign(ZOctype, (&ZIctype));
	#line 1358 "lctsyntax.c"
	}
	/* END OF RESULT ASSIGNMENT: IDENT */
}

static void
ZR114(void)
{
	if ((CURRENT_TERMINAL) == 24) {
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
#line 422 "lctsyntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected ';'");
	
#line 1387 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZRaction_Hdefinition_C_Ctype_Htuple(typetuple *ZOa)
{
	typetuple ZIa;

	if ((CURRENT_TERMINAL) == 24) {
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
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 270 "lctsyntax.act"

		typetuple_init(&(ZIa));
	
#line 1415 "lctsyntax.c"
		}
		/* END OF ACTION: init-tuple */
		ZR120 (&ZIa);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (24);
	return;
ZL0:;
	*ZOa = ZIa;
}

static void
ZR120(typetuple *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 7:
		{
			ADVANCE_LEXER;
		}
		break;
	case 0: case 14:
		{
			ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1 (ZIa);
			switch (CURRENT_TERMINAL) {
			case 7:
				break;
			case 24:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 24:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

/* BEGINNING OF TRAILER */

#line 438 "lctsyntax.act"


#line 1472 "lctsyntax.c"

/* END OF FILE */
