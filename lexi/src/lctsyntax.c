/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 86 "lctsyntax.act"


/* $Id: lctsyntax.act 2703 2011-12-07 16:06:44Z kate $ */

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

#include "adt/action.h"
#include "adt/entry.h"
#include "adt/tree.h"

#include "lctsyntax.h"
#include "lctlexer.h"
#include "ccode.h"

#define ADVANCE_LEXER ADVANCE_LCT_LEXER
#define CURRENT_TERMINAL CURRENT_LCT_TERMINAL 
#define SAVE_LEXER SAVE_LCT_LEXER
#define RESTORE_LEXER RESTORE_LCT_LEXER

typedef struct EntryT* EntryP;



void init_lct_parse_tree (lct_parse_tree* a) 
{
	a->headersdefined = 0;
	a->trailersdefined = 0;
	ccode_init(&(a->hfileheader)) ;
	ccode_init(&(a->cfileheader)) ;
	ccode_init(&(a->hfiletrailer)) ;
	ccode_init(&(a->cfiletrailer)) ;
	a->arg_head = NULL;
	a->arg_tail = &(a->arg_head);
}

lexer_parse_tree* lxi_top_level;
lct_parse_tree global_lct_parse_tree ;

#line 68 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(TypeTupleT *);
static void ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(TypeTupleT *, TypeTupleT *);
static void ZRcode_Hblock_C_Ccode_Helement(CcodeT *, EntryP);
static void ZRmap_Hstmnt(void);
extern void read_lct_unit(void);
static void ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1(TypeTupleT *);
static void ZRstatement_Hlist(void);
static void ZRcode_Hblock_C_Ccode_Hbody(CcodeT *, EntryP);
static void ZR80(void);
static void ZRargument_Hstmnt(void);
static void ZRheader_Hstmnt(void);
static void ZRcode_Hblock(EntryP, CcodeT *);
static void ZRstatement(void);
static void ZRtrailer_Hstmnt(void);
static void ZRaction_Hdefinition(void);
static void ZR104(void);
static void ZR107(void);
static void ZR112(NStringT *);
static void ZR113(void);
static void ZR118(TypeTupleT *);
static void ZRaction_Hdefinition_C_Ctype_Htuple(TypeTupleT *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		NStringT ZIname;
		NStringT ZItype;
		bool ZIisref;

		/* BEGINNING OF INLINE: 93 */
		{
			switch (CURRENT_TERMINAL) {
			case 19:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 161 "lctsyntax.act"

	nstring_copy_cstring(&ZIname,lct_token_buff);
#line 120 "lctsyntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-identifier */
					{
#line 193 "lctsyntax.act"
 nstring_init(&(ZIname)); 
#line 132 "lctsyntax.c"
					}
					/* END OF ACTION: empty-identifier */
				}
				break;
			}
		}
		/* END OF INLINE: 93 */
		switch (CURRENT_TERMINAL) {
		case 6:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 19:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 161 "lctsyntax.act"

	nstring_copy_cstring(&ZItype,lct_token_buff);
#line 154 "lctsyntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 96 */
		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 186 "lctsyntax.act"
 (ZIisref) = true ; 
#line 172 "lctsyntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 187 "lctsyntax.act"
 (ZIisref) = false ; 
#line 183 "lctsyntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 96 */
		/* BEGINNING OF ACTION: append-tuple */
		{
#line 291 "lctsyntax.act"

	struct EntryT* entry = table_get_entry(tree_get_table(lxi_top_level), (&ZItype));
	if(entry == NULL) {
		 char* pt = nstring_to_cstring((&ZItype));
		 error(ERROR_SERIOUS, "Unknown type %s", pt);
		 DEALLOCATE(pt);
		 nstring_destroy((&ZIname));
		 nstring_destroy((&ZItype));
	}
	else if(!entry_is_type(entry)) {
		error(ERROR_SERIOUS, "%s is not a type", (&ZItype));
		nstring_destroy((&ZItype));
	}
	else {
		typetuple_append((ZIa),typetupleentry_create((&ZIname),entry, (ZIisref)));
		nstring_destroy((&ZItype));
	}
#line 211 "lctsyntax.c"
		}
		/* END OF ACTION: append-tuple */
	}
	return;
ZL1:;
	SAVE_LEXER (24);
	return;
}

static void
ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(TypeTupleT *ZOin, TypeTupleT *ZOout)
{
	TypeTupleT ZIin;
	TypeTupleT ZIout;

	switch (CURRENT_TERMINAL) {
	case 6:
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
#line 287 "lctsyntax.act"

	typetuple_init(&(ZIin));
#line 247 "lctsyntax.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 287 "lctsyntax.act"

	typetuple_init(&(ZIout));
#line 255 "lctsyntax.c"
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
ZRcode_Hblock_C_Ccode_Helement(CcodeT *ZIc, EntryP ZIe)
{
	switch (CURRENT_TERMINAL) {
	case 16:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-at */
			{
#line 204 "lctsyntax.act"

	ccode_append_at(&(*ZIc));
#line 284 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-at */
		}
		break;
	case 20:
		{
			NStringT ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-identifier */
			{
#line 165 "lctsyntax.act"

	nstring_copy_cstring(&ZIi,lct_token_buff);
#line 299 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: false */
			{
#line 187 "lctsyntax.act"
 (ZIb) = false ; 
#line 307 "lctsyntax.c"
			}
			/* END OF ACTION: false */
			/* BEGINNING OF ACTION: append-ccode-identifier */
			{
#line 212 "lctsyntax.act"

	if((ZIe)) {
		ActionT* action = entry_get_action((ZIe));
		TypeTupleEntryT *p, *q;
	 	if ((p = typetuple_name_is_in(action_get_inputs(action),(&ZIi))) || 
	       	    (q = typetuple_name_is_in(action_get_outputs(action),(&ZIi)))) {
		   	if(!(ZIb)) {
				ccode_append_identifier((ZIc),(&ZIi));
			} else {
				if(p && p->is_reference) {
					ccode_append_reference((ZIc),(&ZIi));
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
			DEALLOCATE(pi);
			DEALLOCATE(pe);
		}
	} else {
		error(ERROR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
		nstring_destroy((&ZIi));
	}
#line 343 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-identifier */
		}
		break;
	case 21:
		{
			NStringT ZIi;
			bool ZIb;

			/* BEGINNING OF EXTRACT: code-reference */
			{
#line 169 "lctsyntax.act"

	nstring_copy_cstring(&ZIi,lct_token_buff);
#line 358 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-reference */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: true */
			{
#line 186 "lctsyntax.act"
 (ZIb) = true ; 
#line 366 "lctsyntax.c"
			}
			/* END OF ACTION: true */
			/* BEGINNING OF ACTION: append-ccode-identifier */
			{
#line 212 "lctsyntax.act"

	if((ZIe)) {
		ActionT* action = entry_get_action((ZIe));
		TypeTupleEntryT *p, *q;
	 	if ((p = typetuple_name_is_in(action_get_inputs(action),(&ZIi))) || 
	       	    (q = typetuple_name_is_in(action_get_outputs(action),(&ZIi)))) {
		   	if(!(ZIb)) {
				ccode_append_identifier((ZIc),(&ZIi));
			} else {
				if(p && p->is_reference) {
					ccode_append_reference((ZIc),(&ZIi));
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
			DEALLOCATE(pi);
			DEALLOCATE(pe);
		}
	} else {
		error(ERROR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
		nstring_destroy((&ZIi));
	}
#line 402 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-identifier */
		}
		break;
	case 22:
		{
			NStringT ZIs;

			/* BEGINNING OF EXTRACT: code-string */
			{
#line 173 "lctsyntax.act"

	nstring_assign(&ZIs, &lct_token_nstring);
#line 416 "lctsyntax.c"
			}
			/* END OF EXTRACT: code-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-string */
			{
#line 208 "lctsyntax.act"

	ccode_append_string((ZIc),(&ZIs));
#line 425 "lctsyntax.c"
			}
			/* END OF ACTION: append-ccode-string */
		}
		break;
	case 15:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: E_lone_at_in_code_block */
			{
#line 450 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Lone @ inside @{ @} block") ;
#line 438 "lctsyntax.c"
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
		case 2:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 19:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 161 "lctsyntax.act"

	nstring_copy_cstring(&ZIlexitype,lct_token_buff);
#line 478 "lctsyntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR104 ();
		switch (CURRENT_TERMINAL) {
		case 19:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 161 "lctsyntax.act"

	nstring_copy_cstring(&ZIctype,lct_token_buff);
#line 494 "lctsyntax.c"
			}
			/* END OF EXTRACT: identifier */
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
#line 310 "lctsyntax.act"

	struct EntryT* entry= table_get_entry(tree_get_table(lxi_top_level), (&ZIlexitype));
	if(entry !=NULL) {
		if(entry_is_type(entry)) {
			struct TypeT* type = entry_get_type(entry);
			type_map(type, (&ZIctype));
		} else {
			error(ERROR_SERIOUS, "Name in maps section is not a type");
			nstring_destroy((&ZIctype));
		}
	} else {
		error(ERROR_SERIOUS, "Unknown type in mapping");
		nstring_destroy((&ZIctype));
	}
	nstring_destroy((&ZIlexitype));
#line 523 "lctsyntax.c"
		}
		/* END OF ACTION: make-map */
		ZR113 ();
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
		case 18:
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
#line 409 "lctsyntax.act"

	    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 565 "lctsyntax.c"
		}
		/* END OF ACTION: E-syntax-error */
	}
}

static void
ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1(TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
ZL2_action_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1:;
	{
		ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname (ZIa);
		/* BEGINNING OF INLINE: 119 */
		{
			switch (CURRENT_TERMINAL) {
			case 10:
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
		/* END OF INLINE: 119 */
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
	case 0: case 1: case 2: case 3:
	case 4:
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
ZRcode_Hblock_C_Ccode_Hbody(CcodeT *ZIc, EntryP ZIe)
{
ZL2_code_Hblock_C_Ccode_Hbody:;
	switch (CURRENT_TERMINAL) {
	case 15: case 16: case 20: case 21:
	case 22:
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
		case 10:
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
#line 425 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ','") ;
#line 689 "lctsyntax.c"
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
		case 4:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR112 (&ZIname);
		/* BEGINNING OF INLINE: 111 */
		{
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case 6:
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
#line 442 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ':'") ;
#line 736 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL2:;
		}
		/* END OF INLINE: 111 */
		ZR112 (&ZIctype);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-additional-argument */
		{
#line 245 "lctsyntax.act"

	struct lxi_additional_argument* p;
	if(nstring_length((&ZIname))>0 && nstring_length((&ZIctype))>0) {
		p = xmalloc(sizeof(*p));
		p->name = nstring_to_cstring((&ZIname));
		p->ctype = nstring_to_cstring((&ZIctype));
		p->next = NULL ;
		*(global_lct_parse_tree.arg_tail) = p;
		global_lct_parse_tree.arg_tail = &(p->next);
	}
	nstring_destroy((&ZIname));
	nstring_destroy((&ZIctype));
#line 763 "lctsyntax.c"
		}
		/* END OF ACTION: define-additional-argument */
		ZR113 ();
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
		CcodeT ZIsc;
		CcodeT ZIsh;

		switch (CURRENT_TERMINAL) {
		case 0:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR107 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-entry */
		{
#line 346 "lctsyntax.act"

	(ZIe)=NULL;
#line 806 "lctsyntax.c"
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
#line 260 "lctsyntax.act"

	if(!global_lct_parse_tree.trailersdefined) {
		global_lct_parse_tree.headersdefined = 1;
		ccode_assign(&(global_lct_parse_tree.hfileheader),(&ZIsh)) ;
		ccode_assign(&(global_lct_parse_tree.cfileheader),(&ZIsc)) ;
	} else {
		error(ERROR_SERIOUS, "Headers may not be redefined");
		ccode_destroy((&ZIsc));
		ccode_destroy((&ZIsh));
	}
#line 829 "lctsyntax.c"
		}
		/* END OF ACTION: set-headers */
		ZR113 ();
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
ZRcode_Hblock(EntryP ZIe, CcodeT *ZOc)
{
	CcodeT ZIc;

	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		/* BEGINNING OF INLINE: 69 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 13:
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
#line 420 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@{'") ;
#line 872 "lctsyntax.c"
				}
				/* END OF ACTION: E_expected_code_start */
			}
		ZL2:;
		}
		/* END OF INLINE: 69 */
		/* BEGINNING OF ACTION: init-ccode */
		{
#line 200 "lctsyntax.act"

	ccode_init(&(ZIc));
#line 884 "lctsyntax.c"
		}
		/* END OF ACTION: init-ccode */
		ZRcode_Hblock_C_Ccode_Hbody (&ZIc, ZIe);
		/* BEGINNING OF INLINE: 70 */
		{
			switch (CURRENT_TERMINAL) {
			case 17:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: E_unexpected_eof */
					{
#line 446 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Unexpected End of File inside @{ @} block") ;
#line 899 "lctsyntax.c"
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
				case 14:
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
#line 412 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@}'") ;
#line 931 "lctsyntax.c"
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
	case 3:
		{
			ZRaction_Hdefinition ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 4:
		{
			ZRargument_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 0:
		{
			ZRheader_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2:
		{
			ZRmap_Hstmnt ();
			if ((CURRENT_TERMINAL) == 24) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1:
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
		CcodeT ZIsc;
		CcodeT ZIsh;

		switch (CURRENT_TERMINAL) {
		case 1:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR107 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-entry */
		{
#line 346 "lctsyntax.act"

	(ZIe)=NULL;
#line 1035 "lctsyntax.c"
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
#line 272 "lctsyntax.act"

	if(!(global_lct_parse_tree.trailersdefined)) {
		global_lct_parse_tree.trailersdefined = 1;
		ccode_assign(&(global_lct_parse_tree.hfiletrailer),(&ZIsh)) ;
		ccode_assign(&(global_lct_parse_tree.cfiletrailer),(&ZIsc)) ;
	} else {
		error(ERROR_SERIOUS, "Trailers may not be redefined");
		ccode_destroy((&ZIsc));
		ccode_destroy((&ZIsh));
	}
#line 1058 "lctsyntax.c"
		}
		/* END OF ACTION: set-trailers */
		ZR113 ();
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
		NStringT ZInm;
		TypeTupleT ZIin;
		TypeTupleT ZIout;
		EntryP ZIe;
		CcodeT ZIc;

		switch (CURRENT_TERMINAL) {
		case 3:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR112 (&ZInm);
		ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn (&ZIin, &ZIout);
		ZR107 ();
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: get-entry-action */
		{
#line 328 "lctsyntax.act"

	(ZIe)=table_get_entry(tree_get_table(lxi_top_level), (&ZInm));
	if((ZIe)) {
		if(!entry_is_action((ZIe))) {
			char* pi;
			(ZIe)=NULL; /*TODO skip to end of action */
			pi = nstring_to_cstring((&ZInm));
			error(ERROR_SERIOUS,"%s is not an action", pi);
			DEALLOCATE(pi);
		}
	} else {
		char* pi = nstring_to_cstring((&ZInm));		
		error(ERROR_SERIOUS,"Defining an undeclared action: %s", pi);
		DEALLOCATE(pi);
	}
	nstring_destroy((&ZInm));
#line 1119 "lctsyntax.c"
		}
		/* END OF ACTION: get-entry-action */
		/* BEGINNING OF ACTION: check-action-tuples */
		{
#line 350 "lctsyntax.act"

	if((ZIe)) {
		/*TODO assert (entry_is_action((ZIe))); */	       
		/* TODO check that the same name does not appear twice in the input and output tuple */
		ActionT* action = entry_get_action((ZIe));
		if(typetuple_length(action_get_inputs(action))!=typetuple_length((&ZIin))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS,"Action %s declared with an incompatible number of inputs", pe);
			DEALLOCATE(pe);
		} else if(!typetuple_match(action_get_inputs(action),(&ZIin))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS, "params do not match for action %s",pe);
			DEALLOCATE(pe);
		} else {
			int allhavenames = typetuple_assign_names(action_get_inputs(action),(&ZIin));
			if(!allhavenames) {
				error(ERROR_SERIOUS,"outputs tuples in action definition should have names");
			}
		}
		if(typetuple_length(action_get_outputs(action))!=typetuple_length((&ZIout))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS,"Action %s declared with an incompatible number of outputs", pe);
			DEALLOCATE(pe);
		} else if (!typetuple_match(action_get_outputs(action),(&ZIout))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS, "results do not match for action %s",pe);
			DEALLOCATE(pe);
		} else {				
			int allhavenames = typetuple_assign_names(action_get_outputs(action),(&ZIout));
			if(!allhavenames) {
				char* pe=nstring_to_cstring(entry_key((ZIe)));
				error(ERROR_SERIOUS,"outputs tuples in the definition of action %s should have names",pe);
			DEALLOCATE(pe);
			}
		}
	}
	typetuple_destroy((&ZIin));
	typetuple_destroy((&ZIout));
#line 1163 "lctsyntax.c"
		}
		/* END OF ACTION: check-action-tuples */
		ZRcode_Hblock (ZIe, &ZIc);
		if ((CURRENT_TERMINAL) == 24) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: define-action */
		{
#line 391 "lctsyntax.act"

	if((ZIe)) {
	       /*TODO assert entry_is_action */	       
	        ActionT* action = entry_get_action((ZIe));
			if(!action_is_defined(action)) {
				action_set_define(action);
				action_set_code(action, (&ZIc));
			} else {
				char* pe=nstring_to_cstring(entry_key((ZIe)));
				error(ERROR_SERIOUS,"Action %s has already been defined", pe);
				DEALLOCATE(pe);
			}
	} else {
		ccode_destroy((&ZIc));
	}
#line 1189 "lctsyntax.c"
		}
		/* END OF ACTION: define-action */
		ZR113 ();
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
		case 7:
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
#line 434 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '->'") ;
#line 1227 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_arrow */
	}
}

static void
ZR107(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 8:
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
#line 430 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '='") ;

#line 1257 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_define */
	}
}

static void
ZR112(NStringT *ZOctype)
{
	NStringT ZIctype;

	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 19:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 161 "lctsyntax.act"

	nstring_copy_cstring(&ZIctype,lct_token_buff);
#line 1279 "lctsyntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: empty-identifier */
		{
#line 193 "lctsyntax.act"
 nstring_init(&(ZIctype)); 
#line 1295 "lctsyntax.c"
		}
		/* END OF ACTION: empty-identifier */
		/* BEGINNING OF ACTION: E_expected_identifier */
		{
#line 417 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  identifier") ;
#line 1303 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	}
ZL0:;
	/* BEGINNING OF RESULT ASSIGNMENT: IDENTIFIER */
	{
#line 151 "lctsyntax.act"

	nstring_assign(ZOctype,(&ZIctype));
#line 1313 "lctsyntax.c"
	}
	/* END OF RESULT ASSIGNMENT: IDENTIFIER */
}

static void
ZR113(void)
{
	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 9:
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
#line 438 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ';'") ;
#line 1341 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZR118(TypeTupleT *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 12:
		{
			ADVANCE_LEXER;
		}
		break;
	case 6: case 19:
		{
			ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Htuple1 (ZIa);
			switch (CURRENT_TERMINAL) {
			case 12:
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

static void
ZRaction_Hdefinition_C_Ctype_Htuple(TypeTupleT *ZOa)
{
	TypeTupleT ZIa;

	if ((CURRENT_TERMINAL) == 24) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 11:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 287 "lctsyntax.act"

	typetuple_init(&(ZIa));
#line 1403 "lctsyntax.c"
		}
		/* END OF ACTION: init-tuple */
		ZR118 (&ZIa);
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

/* BEGINNING OF TRAILER */

#line 457 "lctsyntax.act"


#line 1425 "lctsyntax.c"

/* END OF FILE */
