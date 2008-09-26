/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 131 "syntax.act"

/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

#include <string.h>
#include <stdio.h>

#include "exds/common.h"
#include "exds/exception.h"
#include "exds/dalloc.h"
#include "exds/dstring.h"

#include "error/error.h"
#include "xalloc/xalloc.h"

#include "char.h"
#include "adt.h"
#include "lexer.h"
#include "syntax.h"
#include "options.h"


#define ADVANCE_LEXER ADVANCE_LXI_LEXER
#define CURRENT_TERMINAL CURRENT_LXI_TERMINAL 
#define SAVE_LEXER SAVE_LXI_LEXER
#define RESTORE_LEXER RESTORE_LXI_LEXER

/* TODO see main.c; this is a work-around for the copyright file */
extern cmd_line_options options;



/*
    PARSER TYPES

    These types give the implementation of the types used in the syntax.
*/

typedef letter *SID_CHARS ;
typedef char *SID_STRING ;
/*typedef zone* zoneP; Done in syntax.h */
typedef instruction* instructionP ;
typedef instructions_list* instructions_listP ;
typedef arg* argP;
typedef args_list* args_listP;

/*
    SID IDENTIFIER PREFIX

    This string is added to the start of each sid identifier.
*/

char *token_prefix = "lex_" ;


/*
    COMPILATION MODE

    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif


#line 109 "tmp.syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRexpected__semicolon(void);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRchars(zoneP, SID_CHARS *);
static void ZR152(void);
static void ZR153(void);
static void ZR154(void);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZR175(args_listP *);
static void ZRtrigraph_Hdefn(zoneP);
extern void read_lex(zoneP);
static void ZR195(zoneP *, SID_CHARS *);
static void ZR197(zoneP *, instructions_listP *);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcopyright_Hstmt(zoneP);
static void ZR219(zoneP, instructions_listP, zoneP *, instructions_listP *);
static void ZR221(zoneP *);
static void ZR222(zoneP *);
static void ZR223(zoneP *, args_listP *, instructionP *);
static void ZR227(zoneP *, args_listP *, SID_STRING *, instructionP *);
static void ZRcommand(zoneP);
static void ZR228(argP *, args_listP *);
static void ZR230(zoneP *, TypeTupleT *);
static void ZRtype_Htuple_C_Ctype_Htuple1(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRaction_Hcall_C_Clhs_Harg(args_listP);
static void ZR125(void);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRexpected__semicolon(void)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 22:
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
#line 936 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 180 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIzid;
		SID_CHARS ZIb;
		instructions_listP ZIentry_Hinstl;
		int ZIlendclosed;
		SID_CHARS ZIe;
		instructions_listP ZIleaving_Hinstl;
		zoneP ZInew_Hzone;

		switch (CURRENT_TERMINAL) {
		case 13:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 187 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 202 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 218 "tmp.syntax.c"
					}
					/* END OF EXTRACT: identifier */
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_expected_identifier */
				{
#line 909 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 236 "tmp.syntax.c"
				}
				/* END OF ACTION: E_expected_identifier */
			}
		ZL2:;
		}
		/* END OF INLINE: 187 */
		/* BEGINNING OF INLINE: 189 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 23:
					break;
				default:
					goto ZL5;
				}
				ADVANCE_LEXER;
			}
			goto ZL4;
		ZL5:;
			{
				/* BEGINNING OF ACTION: E_expected_colon */
				{
#line 932 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 262 "tmp.syntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL4:;
		}
		/* END OF INLINE: 189 */
		ZR195 (&ZIz, &ZIb);
		ZR197 (&ZIz, &ZIentry_Hinstl);
		/* BEGINNING OF INLINE: 193 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 725 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 281 "tmp.syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 26:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 725 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 293 "tmp.syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 27:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: false */
					{
#line 726 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 305 "tmp.syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			case 41:
				RESTORE_LEXER;
				goto ZL7;
			default:
				goto ZL7;
			}
			goto ZL6;
		ZL7:;
			{
				/* BEGINNING OF ACTION: E_expected_range */
				{
#line 915 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 324 "tmp.syntax.c"
				}
				/* END OF ACTION: E_expected_range */
				/* BEGINNING OF ACTION: false */
				{
#line 726 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 331 "tmp.syntax.c"
				}
				/* END OF ACTION: false */
			}
		ZL6:;
		}
		/* END OF INLINE: 193 */
		ZR195 (&ZIz, &ZIe);
		ZR197 (&ZIz, &ZIleaving_Hinstl);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-zone */
		{
#line 745 "syntax.act"

    instruction* inst;
    instructions_list* inst_list;
    (ZInew_Hzone)=add_zone((ZIz),(ZIzid),(ZIe), (ZIlendclosed) );

    (ZInew_Hzone)->leaving_instructions=(ZIleaving_Hinstl);
    if((ZInew_Hzone)->leaving_instructions->nb_return_terminal)
	(ZInew_Hzone)->type= typezone_pseudo_token;
    (ZInew_Hzone)->entering_instructions=(ZIentry_Hinstl);
    if((ZInew_Hzone)->entering_instructions->nb_return_terminal)
	(ZInew_Hzone)->type=typezone_general_zone;
    inst=add_instruction_pushzone((ZInew_Hzone));
    inst_list=add_instructions_list();
    *(inst_list->tail)=inst;
    inst_list->tail=&(inst->next);
    add_char ( (ZIz), (ZIz)->zone_main_pass, (ZIb), inst_list, NULL ) ;
#line 363 "tmp.syntax.c"
		}
		/* END OF ACTION: make-zone */
		switch (CURRENT_TERMINAL) {
		case 16:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcommand_Hlist (ZInew_Hzone);
		switch (CURRENT_TERMINAL) {
		case 17:
			break;
		case 41:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: update-zone-type */
		{
#line 761 "syntax.act"

	switch((ZInew_Hzone)->type) {
		case typezone_pseudo_token:
		case typezone_general_zone:
			(ZIz)->type = typezone_general_zone;
			break;
		case typezone_pure_function:
			break; //do nothing

	}
#line 397 "tmp.syntax.c"
		}
		/* END OF ACTION: update-zone-type */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIa;

		/* BEGINNING OF INLINE: 112 */
		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					/* BEGINNING OF EXTRACT: digit */
					{
#line 259 "syntax.act"
 ZIa = "0123456789" ; 
#line 427 "tmp.syntax.c"
					}
					/* END OF EXTRACT: digit */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: lower */
					{
#line 258 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 439 "tmp.syntax.c"
					}
					/* END OF EXTRACT: lower */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: string */
					{
#line 247 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 452 "tmp.syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: upper */
					{
#line 257 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 464 "tmp.syntax.c"
					}
					/* END OF EXTRACT: upper */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 112 */
		/* BEGINNING OF INLINE: 114 */
		{
			switch (CURRENT_TERMINAL) {
			case 21:
				{
					SID_STRING ZIb;

					ADVANCE_LEXER;
					ZRstring_Hplus (&ZIb);
					if ((CURRENT_TERMINAL) == 41) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: string-concat */
					{
#line 298 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 493 "tmp.syntax.c"
					}
					/* END OF ACTION: string-concat */
				}
				break;
			default:
				{
					ZIs = ZIa;
				}
				break;
			}
		}
		/* END OF INLINE: 114 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRtype_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIs;

		switch (CURRENT_TERMINAL) {
		case 40:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 202 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 538 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 133 */
		{
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 796 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 554 "tmp.syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-type */
				{
#line 813 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str,(ZIs));
	xfree((ZIs));
	EntryT* entry;
	if(entry=table_get_entry((ZIz)->top_level->table, &str)) {
		nstring_destroy(&str);
		/* TODO switch ? */
		if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Type %s already exists",(ZIs));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIs),(ZIs));
		else if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has already been declared as an action",(ZIs), (ZIs));
		else
			; /* TODO assert(0): we should never reach that place*/
	} else {
		table_add_type((ZIz)->top_level->table, &str, false);
	}
#line 581 "tmp.syntax.c"
				}
				/* END OF ACTION: make-type */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonetype */
				{
#line 898 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 593 "tmp.syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonetype */
			}
		ZL2:;
		}
		/* END OF INLINE: 133 */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRchars(zoneP ZIz, SID_CHARS *ZOc)
{
	SID_CHARS ZIc;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIs;

		ZRstring_Hplus (&ZIs);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-chars */
		{
#line 319 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 628 "tmp.syntax.c"
		}
		/* END OF ACTION: make-chars */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR152(void)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 18:
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
#line 940 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 663 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_arrow */
	}
}

static void
ZR153(void)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 14:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_open */
		{
#line 919 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
#line 692 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_open */
	}
}

static void
ZR154(void)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_close */
		{
#line 923 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
#line 721 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_close */
	}
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
ZL2_action_Hcall_C_Clhs_Htuple1:;
	{
		ZRaction_Hcall_C_Clhs_Harg (ZIl);
		/* BEGINNING OF INLINE: 229 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: action-call::lhs-tuple1 */
					goto ZL2_action_Hcall_C_Clhs_Htuple1;
					/* END OF INLINE: action-call::lhs-tuple1 */
				}
				/*UNREACHED*/
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 229 */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRtype_Htuple(zoneP ZIz, TypeTupleT *ZOa)
{
	TypeTupleT ZIa;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 858 "syntax.act"

	typetuple_init(&(ZIa));
#line 776 "tmp.syntax.c"
		}
		/* END OF ACTION: init-tuple */
		ZR230 (&ZIz, &ZIa);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	/* BEGINNING OF RESULT ASSIGNMENT: TYPETUPLE */
	{
#line 187 "syntax.act"

	typetuple_assign(ZOa, (&ZIa));
#line 795 "tmp.syntax.c"
	}
	/* END OF RESULT ASSIGNMENT: TYPETUPLE */
}

static void
ZRaction_Hcall_C_Crhs_Htuple1(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		argP ZIa;

		ZRaction_Hcall_C_Crhs_Harg (&ZIa);
		ZR228 (&ZIa, &ZIr);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRinstructions_Hlist(zoneP ZI213, instructions_listP *ZO218)
{
	instructions_listP ZI218;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		instructionP ZIinst;
		instructions_listP ZIinstl;
		zoneP ZI217;

		ZRinstruction (ZI213, &ZIinst);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: empty-inst-list */
		{
#line 658 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 849 "tmp.syntax.c"
		}
		/* END OF ACTION: empty-inst-list */
		/* BEGINNING OF ACTION: add-inst-to-list */
		{
#line 455 "syntax.act"

	if((ZIinst)!=NULL) { /* if (ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT* locals = instructionslist_localnames((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((ZIinst)->type==return_terminal || (ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((ZIinstl)->nb_return_terminal>0 && (ZIinst)->type!=do_nothing)
			error(ERROR_SERIOUS, "No instruction may follow an instruction that returns a terminal");
		if((ZIinst)->type == return_terminal) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == terminal_apply_function) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == action_call) {
			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			EntryT* entryaction = (ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (ZIinst)->u.act.rhs;
			args_list* lhs = (ZIinst)->u.act.lhs;

			arg* p;
			TypeTupleEntryT* q;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.literal);
					entrytype=localnames_get_type(locals, &str);
					nstring_destroy(&str);
					if(!entrytype) {
						EntryT* tableentry = table_get_entry((ZI213)->top_level->table, &str);
						if(!tableentry) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_localname(tableentry)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_action(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_type(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
							entrytype = NULL;
						} else {
							; /* TODO assert(0) this should be unreachable*/
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((ZI213)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((ZI213)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((ZI213)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((ZI213)->top_level);
		 			break;
				case arg_none:
					break; //Error already detected, do nothing and leave p->lexitype = NULL
				case arg_chars_list:
				case arg_ignore:
				case arg_return_terminal:
					/* TODO assert(0): we should never reach this place */
				break;
			default:
				break;
				/* TODO assert(0): we should never reach this place either, doubly so*/
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s\' has type \'%s%s\' when it should have type %s", s1, p->u.literal, s2, s3, s4, s5);
						DEALLOCATE(s1);
						DEALLOCATE(s2);
						DEALLOCATE(s4);
					}
				}
			}
			if(p!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
				DEALLOCATE(s);
			}

			for ( p = lhs->head, q = action->outputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype;
				switch (p->type) {
				case arg_identifier: 
					{
						NStringT str;
						EntryT* entry; 
						nstring_copy_cstring(&str, p->u.literal);
						entrytype = localnames_get_type(locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry((ZI213)->top_level->table, &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name((ZI213)->top_level->table, &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								entrytype=q->type; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					entrytype = lexer_terminal_type((ZI213)->top_level);
					q->is_reference = false;
					/* TODO assert(q->is_reference == false) */
					break;
				case arg_ignore:
					/*always acceptable */
					entrytype=q->type;
					p->is_reference=q->is_reference;
					break;
				case arg_none:
					break;
					/* TODO asserting errored is already set */
					/* Error has already been detected */
				case arg_charP:
				case arg_char_nb:
				case arg_chars_list:
				case arg_terminal:
				case arg_nb_of_chars:
					break; /* UNREACHABLE */
				default:
					break; /* UNREACHABLE */
				}
				if(p->is_reference != q->is_reference) {
					/* XXX: state which action */
					if(p->is_reference)
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
					else
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
				}
			}
			if(p!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, too many results", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
				DEALLOCATE(s);
			}
		}
		/* TODO only append if no error */
		*(ZIinstl)->tail=(ZIinst);
		(ZIinstl)->tail=&(ZIinst)->next;
		++((ZIinstl)->size);
	}
#line 1046 "tmp.syntax.c"
		}
		/* END OF ACTION: add-inst-to-list */
		ZR219 (ZI213, ZIinstl, &ZI217, &ZI218);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZO218 = ZI218;
}

static void
ZRtype_Htuple_C_Ctype_Hname(zoneP ZIz, TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIname;
		SID_STRING ZItype;
		int ZIisref;

		/* BEGINNING OF INLINE: 137 */
		{
			switch (CURRENT_TERMINAL) {
			case 0:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 202 "syntax.act"

    ZIname = xstrcpy ( token_buff ) ;
#line 1084 "tmp.syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-identifier */
					{
#line 308 "syntax.act"

    (ZIname) = xstrcpy("");
#line 1097 "tmp.syntax.c"
					}
					/* END OF ACTION: empty-identifier */
				}
				break;
			}
		}
		/* END OF INLINE: 137 */
		switch (CURRENT_TERMINAL) {
		case 23:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 202 "syntax.act"

    ZItype = xstrcpy ( token_buff ) ;
#line 1119 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 140 */
		{
			switch (CURRENT_TERMINAL) {
			case 24:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 725 "syntax.act"
 (ZIisref) = 1 ; 
#line 1137 "tmp.syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 726 "syntax.act"
 (ZIisref) = 0 ; 
#line 1148 "tmp.syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 140 */
		/* BEGINNING OF ACTION: append-tuple */
		{
#line 863 "syntax.act"

	NStringT tstr, istr;
	nstring_copy_cstring(&tstr,(ZItype));
	nstring_copy_cstring(&istr,(ZIname));
	EntryT* entry = table_get_entry((ZIz)->top_level->table,&tstr);
	if(entry == NULL) {
		 error(ERROR_SERIOUS, "Unknown type %s", (ZItype));
		 nstring_destroy(&istr);
	}
	else if(!entry_is_type(entry)) {
		 error(ERROR_SERIOUS, "%s is not a type", (ZItype));
		 nstring_destroy(&istr);
	}
	else {
		typetuple_append((ZIa),typetupleentry_create(&istr,entry,(ZIisref)));
	}
	nstring_destroy(&tstr);
	xfree((ZItype));
	xfree((ZIname));
#line 1178 "tmp.syntax.c"
		}
		/* END OF ACTION: append-tuple */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR175(args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 14:
		{
			ZRaction_Hcall_C_Crhs_Htuple (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 441 "syntax.act"

    (ZIr)=add_args_list();
#line 1210 "tmp.syntax.c"
			}
			/* END OF ACTION: empty-args-list */
		}
		break;
	case 41:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_CHARS ZIs;
		SID_STRING ZIt;

		switch (CURRENT_TERMINAL) {
		case 9:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRchars (ZIz, &ZIs);
		ZR152 ();
		ZRstring_Hplus (&ZIt);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-trigraph */
		{
#line 357 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), NULL, (ZIt)) ;
#line 1255 "tmp.syntax.c"
		}
		/* END OF ACTION: make-trigraph */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

void
read_lex(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		ZRcommand_Hlist (ZIz);
		/* BEGINNING OF INLINE: 202 */
		{
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case 19:
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: syntax-error */
				{
#line 957 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1296 "tmp.syntax.c"
				}
				/* END OF ACTION: syntax-error */
			}
		ZL2:;
		}
		/* END OF INLINE: 202 */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR195(zoneP *ZIz, SID_CHARS *ZOe)
{
	SID_CHARS ZIe;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		ZRnon_Hempty_Hchars (*ZIz, &ZIe);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_chars */
		{
#line 926 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1334 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_chars */
	}
ZL0:;
	*ZOe = ZIe;
}

static void
ZR197(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
{
	instructions_listP ZIleaving_Hinstl;

	switch (CURRENT_TERMINAL) {
	case 18:
		{
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIleaving_Hinstl);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-inst-list */
			{
#line 658 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 1365 "tmp.syntax.c"
			}
			/* END OF ACTION: empty-inst-list */
		}
		break;
	case 41:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOleaving_Hinstl = ZIleaving_Hinstl;
}

static void
ZRaction_Hdecl(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIi;
		TypeTupleT ZIit;
		TypeTupleT ZIot;

		switch (CURRENT_TERMINAL) {
		case 37:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 145 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 38:
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_expected_begin_action */
				{
#line 948 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
#line 1418 "tmp.syntax.c"
				}
				/* END OF ACTION: E_expected_begin_action */
			}
		ZL2:;
		}
		/* END OF INLINE: 145 */
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1432 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 146 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 39:
					break;
				default:
					goto ZL5;
				}
				ADVANCE_LEXER;
			}
			goto ZL4;
		ZL5:;
			{
				/* BEGINNING OF ACTION: E_expected_end_action */
				{
#line 952 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
#line 1459 "tmp.syntax.c"
				}
				/* END OF ACTION: E_expected_end_action */
			}
		ZL4:;
		}
		/* END OF INLINE: 146 */
		/* BEGINNING OF INLINE: 147 */
		{
			switch (CURRENT_TERMINAL) {
			case 23:
				{
					ADVANCE_LEXER;
					ZR153 ();
					ZRtype_Htuple (ZIz, &ZIit);
					ZR154 ();
					ZR152 ();
					ZR153 ();
					ZRtype_Htuple (ZIz, &ZIot);
					ZR154 ();
					if ((CURRENT_TERMINAL) == 41) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 858 "syntax.act"

	typetuple_init(&(ZIit));
#line 1492 "tmp.syntax.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 858 "syntax.act"

	typetuple_init(&(ZIot));
#line 1500 "tmp.syntax.c"
					}
					/* END OF ACTION: init-tuple */
				}
				break;
			}
		}
		/* END OF INLINE: 147 */
		/* BEGINNING OF ACTION: make-action */
		{
#line 834 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str, (ZIi));
	EntryT* entry;
	if(entry=table_get_entry((ZIz)->top_level->table, &str)) {
		nstring_destroy(&str);
		/* TODO switch ? */
	   	if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Action %s already exists",(ZIi));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIi),(ZIi));
		else if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Can't create action %s, %s has already been declared as a type",(ZIi), (ZIi));
		else
			; /* TODO assert(0): we should never reach that place*/
	} else {
		table_add_action((ZIz)->top_level->table, &str , (&ZIit), (&ZIot));
	}
	xfree((ZIi));
#line 1530 "tmp.syntax.c"
		}
		/* END OF ACTION: make-action */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRinstruction(zoneP ZIz, instructionP *ZOinst)
{
	instructionP ZIinst;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		args_listP ZIl;

		/* BEGINNING OF ACTION: empty-args-list */
		{
#line 441 "syntax.act"

    (ZIl)=add_args_list();
#line 1556 "tmp.syntax.c"
		}
		/* END OF ACTION: empty-args-list */
		ZR223 (&ZIz, &ZIl, &ZIinst);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
ZL2_command_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 6: case 7: case 8: case 9:
	case 10: case 13: case 16: case 22:
	case 37: case 40:
		{
			ZRcommand (ZIz);
			/* BEGINNING OF INLINE: command-list */
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_command_Hlist;
			}
			/* END OF INLINE: command-list */
		}
		/*UNREACHED*/
	case 41:
		return;
	default:
		break;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 957 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1606 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIs;
		instructionP ZIinst;

		switch (CURRENT_TERMINAL) {
		case 8:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 247 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 1636 "tmp.syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 18:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRinstruction (ZIz, &ZIinst);
		/* BEGINNING OF INLINE: 183 */
		{
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 796 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 1664 "tmp.syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-keyword */
				{
#line 700 "syntax.act"

    switch((ZIinst)->type) {
    case terminal_apply_function:
    case pure_apply_function:
      if((ZIinst)->u.fun->args->head!=NULL) {
        error(ERROR_SERIOUS, "Syntax error: for keywords using "
	"user defined functions, "
	"the arglist must remain empty");
        break;
      }
    case return_terminal: 
    /* Fallback is intentional */
      add_keyword ( (ZIz), (ZIs), (ZIinst) ) ;
    break;
    default:
      error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
  }
#line 1689 "tmp.syntax.c"
				}
				/* END OF ACTION: make-keyword */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
				{
#line 890 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 1702 "tmp.syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonekeyword */
			}
		ZL2:;
		}
		/* END OF INLINE: 183 */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRcopyright_Hstmt(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIs;

		switch (CURRENT_TERMINAL) {
		case 6:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 20:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 247 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 1746 "tmp.syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 123 */
		{
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 796 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 1762 "tmp.syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-copyright */
				{
#line 802 "syntax.act"

	/* TODO can copyright_file be passed in somehow, other than with options as a global? */
	if(options.copyright_file==NULL) {
		options.copyright_file=fopen((ZIs),"r");
		if(!options.copyright_file) {
			error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
		}
	}
	else 
		error(ERROR_SERIOUS, "Syntax error: you can only specify one copyright file") ;
#line 1780 "tmp.syntax.c"
				}
				/* END OF ACTION: make-copyright */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
				{
#line 894 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 1792 "tmp.syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonecopyright */
			}
		ZL2:;
		}
		/* END OF INLINE: 123 */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR219(zoneP ZI213, instructions_listP ZI216, zoneP *ZO217, instructions_listP *ZO218)
{
	zoneP ZI217;
	instructions_listP ZI218;

ZL2_219:;
	switch (CURRENT_TERMINAL) {
	case 28:
		{
			instructions_listP ZIinstl;
			instructionP ZIinst;

			ZIinstl = ZI216;
			ADVANCE_LEXER;
			ZRinstruction (ZI213, &ZIinst);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-inst-to-list */
			{
#line 455 "syntax.act"

	if((ZIinst)!=NULL) { /* if (ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT* locals = instructionslist_localnames((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((ZIinst)->type==return_terminal || (ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((ZIinstl)->nb_return_terminal>0 && (ZIinst)->type!=do_nothing)
			error(ERROR_SERIOUS, "No instruction may follow an instruction that returns a terminal");
		if((ZIinst)->type == return_terminal) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == terminal_apply_function) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == action_call) {
			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			EntryT* entryaction = (ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (ZIinst)->u.act.rhs;
			args_list* lhs = (ZIinst)->u.act.lhs;

			arg* p;
			TypeTupleEntryT* q;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.literal);
					entrytype=localnames_get_type(locals, &str);
					nstring_destroy(&str);
					if(!entrytype) {
						EntryT* tableentry = table_get_entry((ZI213)->top_level->table, &str);
						if(!tableentry) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_localname(tableentry)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_action(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_type(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
							entrytype = NULL;
						} else {
							; /* TODO assert(0) this should be unreachable*/
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((ZI213)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((ZI213)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((ZI213)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((ZI213)->top_level);
		 			break;
				case arg_none:
					break; //Error already detected, do nothing and leave p->lexitype = NULL
				case arg_chars_list:
				case arg_ignore:
				case arg_return_terminal:
					/* TODO assert(0): we should never reach this place */
				break;
			default:
				break;
				/* TODO assert(0): we should never reach this place either, doubly so*/
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s\' has type \'%s%s\' when it should have type %s", s1, p->u.literal, s2, s3, s4, s5);
						DEALLOCATE(s1);
						DEALLOCATE(s2);
						DEALLOCATE(s4);
					}
				}
			}
			if(p!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
				DEALLOCATE(s);
			}

			for ( p = lhs->head, q = action->outputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype;
				switch (p->type) {
				case arg_identifier: 
					{
						NStringT str;
						EntryT* entry; 
						nstring_copy_cstring(&str, p->u.literal);
						entrytype = localnames_get_type(locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry((ZI213)->top_level->table, &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name((ZI213)->top_level->table, &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								entrytype=q->type; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					entrytype = lexer_terminal_type((ZI213)->top_level);
					q->is_reference = false;
					/* TODO assert(q->is_reference == false) */
					break;
				case arg_ignore:
					/*always acceptable */
					entrytype=q->type;
					p->is_reference=q->is_reference;
					break;
				case arg_none:
					break;
					/* TODO asserting errored is already set */
					/* Error has already been detected */
				case arg_charP:
				case arg_char_nb:
				case arg_chars_list:
				case arg_terminal:
				case arg_nb_of_chars:
					break; /* UNREACHABLE */
				default:
					break; /* UNREACHABLE */
				}
				if(p->is_reference != q->is_reference) {
					/* XXX: state which action */
					if(p->is_reference)
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
					else
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
				}
			}
			if(p!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, too many results", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
				DEALLOCATE(s);
			}
		}
		/* TODO only append if no error */
		*(ZIinstl)->tail=(ZIinst);
		(ZIinstl)->tail=&(ZIinst)->next;
		++((ZIinstl)->size);
	}
#line 2020 "tmp.syntax.c"
			}
			/* END OF ACTION: add-inst-to-list */
			/* BEGINNING OF INLINE: 219 */
			ZI216 = ZIinstl;
			goto ZL2_219;
			/* END OF INLINE: 219 */
		}
		/*UNREACHED*/
	default:
		{
			ZI217 = ZI213;
			ZI218 = ZI216;
		}
		break;
	case 41:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZO217 = ZI217;
	*ZO218 = ZI218;
}

static void
ZR221(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_CHARS ZIs;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2061 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR125 ();
			ZRchars (*ZIz, &ZIs);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-group */
			{
#line 346 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 2076 "tmp.syntax.c"
			}
			/* END OF ACTION: make-group */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 11:
		{
			SID_CHARS ZIs;

			ADVANCE_LEXER;
			ZR125 ();
			ZRchars (*ZIz, &ZIs);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-white */
			{
#line 332 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 2105 "tmp.syntax.c"
			}
			/* END OF ACTION: make-white */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 41:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR222(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 12:
		{
			instructions_listP ZIinst_Hlist;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 18:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-default */
			{
#line 688 "syntax.act"

    (*ZIz)->default_instructions=(ZIinst_Hlist);
#line 2152 "tmp.syntax.c"
			}
			/* END OF ACTION: make-default */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 3: case 4: case 5:
		{
			SID_CHARS ZIs;
			instructions_listP ZIinst_Hlist;

			ZRnon_Hempty_Hchars (*ZIz, &ZIs);
			switch (CURRENT_TERMINAL) {
			case 18:
				break;
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: check-inst-list */
			{
#line 648 "syntax.act"

	if((ZIinst_Hlist)->nb_return_terminal>1)
		error(ERROR_SERIOUS, "At most one return terminal may be specified per instruction list");
#line 2189 "tmp.syntax.c"
			}
			/* END OF ACTION: check-inst-list */
			/* BEGINNING OF ACTION: make-token */
			{
#line 669 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), (ZIinst_Hlist), NULL) ;
	if((ZIinst_Hlist)->nb_return_terminal)
		(*ZIz)->type=typezone_general_zone;
#line 2199 "tmp.syntax.c"
			}
			/* END OF ACTION: make-token */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 41:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR223(zoneP *ZIz, args_listP *ZIl, instructionP *ZOinst)
{
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-list */
			{
#line 265 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 2238 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-char-list */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 2247 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2255 "tmp.syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2266 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2290 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2304 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2353 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 33:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 273 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 2370 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 2379 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2387 "tmp.syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2398 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2422 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2436 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2485 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 32:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 269 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 2502 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 2511 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2519 "tmp.syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2530 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2554 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2568 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2617 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 36:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 285 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 2633 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2645 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2669 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2683 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2732 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 34:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 277 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 2749 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 2758 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2766 "tmp.syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2777 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2801 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2815 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2864 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 35:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-return-terminal */
			{
#line 281 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 2880 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-return-terminal */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2892 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2916 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2930 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2979 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 38:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2997 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3011 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3060 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 0:
		{
			SID_STRING ZI224;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 202 "syntax.act"

    ZI224 = xstrcpy ( token_buff ) ;
#line 3077 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_identifier */
			{
#line 774 "syntax.act"

	(ZIa) = add_identifier_arg ((ZI224));
#line 3086 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_from_identifier */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3097 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3121 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3135 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3184 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 29:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-donothing-inst */
			{
#line 378 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 3197 "tmp.syntax.c"
			}
			/* END OF ACTION: make-donothing-inst */
		}
		break;
	case 14:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			ZRaction_Hcall_C_Clhs_Htuple1 (*ZIl);
			switch (CURRENT_TERMINAL) {
			case 15:
				break;
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3240 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3254 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3303 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 24:
		{
			SID_STRING ZI225;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZI225 = xstrcpy ( token_buff ) ;
#line 3323 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_reference */
			{
#line 778 "syntax.act"

	(ZIa) = add_reference_arg ((ZI225));
#line 3336 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_from_reference */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3347 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3371 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3385 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3434 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 1:
		{
			SID_STRING ZI226;

			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 235 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
    n = ( int ) strlen ( buff ) ;
    for ( s = token_buff ; *s ; s++ ) {
	if ( *s == '-' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = 'H' ;
	} else if ( *s == '_' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = '_' ;
	} else {
	    buff [ n++ ] = *s ;
	}
	if ( n >= 900 ) {
	    error ( ERROR_SERIOUS, "Identifier too long" ) ;
	    break ;
	}
    }
    buff [n] = 0 ;
    ZI226 = xstrcpy ( buff ) ;
#line 3469 "tmp.syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			ZR227 (ZIz, ZIl, &ZI226, &ZIinst);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2:
		{
			SID_STRING ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: string */
			{
#line 247 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 3492 "tmp.syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 3501 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_arg_in_lhs */
			{
#line 965 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 3509 "tmp.syntax.c"
			}
			/* END OF ACTION: E_string_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3520 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3544 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3558 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3607 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 41:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZR227(zoneP *ZIz, args_listP *ZIl, SID_STRING *ZI226, instructionP *ZOinst)
{
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	case 20:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 3642 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_terminal_in_lhs */
			{
#line 988 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 3650 "tmp.syntax.c"
			}
			/* END OF ACTION: E_terminal_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 418 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3661 "tmp.syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3679 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 432 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3693 "tmp.syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR175 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 383 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3742 "tmp.syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	default:
		{
			args_listP ZIa;
			int ZIb;

			/* BEGINNING OF ACTION: null-args-list */
			{
#line 448 "syntax.act"

    (ZIa) = NULL ;
#line 3757 "tmp.syntax.c"
			}
			/* END OF ACTION: null-args-list */
			/* BEGINNING OF ACTION: true */
			{
#line 725 "syntax.act"
 (ZIb) = 1 ; 
#line 3764 "tmp.syntax.c"
			}
			/* END OF ACTION: true */
			/* BEGINNING OF ACTION: make-inst */
			{
#line 366 "syntax.act"

    if((ZIa)) {
    	if((ZIb))
	    (ZIinst)=add_instruction_terminalfunction((*ZI226),(ZIa));
	else
	    (ZIinst)=add_instruction_purefunction((*ZI226),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI226));
    }
#line 3780 "tmp.syntax.c"
			}
			/* END OF ACTION: make-inst */
		}
		break;
	case 41:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZRcommand(zoneP ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 7:
		{
			ADVANCE_LEXER;
			ZR221 (&ZIz);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 16:
		{
			ADVANCE_LEXER;
			ZRcommand_Hlist (ZIz);
			switch (CURRENT_TERMINAL) {
			case 17:
				break;
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 22:
		{
			ADVANCE_LEXER;
		}
		break;
	case 10:
		{
			ADVANCE_LEXER;
			ZR222 (&ZIz);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 37:
		{
			ZRaction_Hdecl (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 6:
		{
			ZRcopyright_Hstmt (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			ZRkeyword_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 9:
		{
			ZRtrigraph_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 40:
		{
			ZRtype_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 13:
		{
			ZRzone_Hdefn (ZIz);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 41:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR228(argP *ZIa, args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 28:
		{
			ADVANCE_LEXER;
			ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 425 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
#line 3933 "tmp.syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 441 "syntax.act"

    (ZIr)=add_args_list();
#line 3945 "tmp.syntax.c"
			}
			/* END OF ACTION: empty-args-list */
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 425 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
#line 3956 "tmp.syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	case 41:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZR230(zoneP *ZIz, TypeTupleT *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 23:
		{
			ZRtype_Htuple_C_Ctype_Htuple1 (*ZIz, ZIa);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 41:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRtype_Htuple_C_Ctype_Htuple1(zoneP ZIz, TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
ZL2_type_Htuple_C_Ctype_Htuple1:;
	{
		ZRtype_Htuple_C_Ctype_Hname (ZIz, ZIa);
		/* BEGINNING OF INLINE: 231 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: type-tuple::type-tuple1 */
					goto ZL2_type_Htuple_C_Ctype_Htuple1;
					/* END OF INLINE: type-tuple::type-tuple1 */
				}
				/*UNREACHED*/
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 231 */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 14:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 173 */
		{
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 2: case 24:
			case 31: case 32: case 33: case 34:
			case 35: case 36:
				{
					ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
					if ((CURRENT_TERMINAL) == 41) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-args-list */
					{
#line 441 "syntax.act"

    (ZIr)=add_args_list();
#line 4068 "tmp.syntax.c"
					}
					/* END OF ACTION: empty-args-list */
				}
				break;
			}
		}
		/* END OF INLINE: 173 */
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRnon_Hempty_Hchars(zoneP ZIz, SID_CHARS *ZOc)
{
	SID_CHARS ZIc;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		ZRchars (ZIz, &ZIc);
		/* BEGINNING OF INLINE: 121 */
		{
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-non-empty */
				{
#line 675 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 4114 "tmp.syntax.c"
				}
				/* END OF ACTION: is-non-empty */
				if (!ZI0)
					goto ZL3;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_empty_character_string */
				{
#line 680 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 4128 "tmp.syntax.c"
				}
				/* END OF ACTION: E_empty_character_string */
			}
		ZL2:;
		}
		/* END OF INLINE: 121 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRaction_Hcall_C_Clhs_Harg(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		argP ZIa;

		/* BEGINNING OF INLINE: 160 */
		{
			switch (CURRENT_TERMINAL) {
			case 31:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-list */
					{
#line 265 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 4165 "tmp.syntax.c"
					}
					/* END OF EXTRACT: arg-char-list */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4174 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4182 "tmp.syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 33:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-nb */
					{
#line 273 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 4196 "tmp.syntax.c"
					}
					/* END OF EXTRACT: arg-char-nb */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4205 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4213 "tmp.syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 32:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-string */
					{
#line 269 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 4227 "tmp.syntax.c"
					}
					/* END OF EXTRACT: arg-char-string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4236 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4244 "tmp.syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 36:
				{
					/* BEGINNING OF EXTRACT: arg-ignore */
					{
#line 285 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 4256 "tmp.syntax.c"
					}
					/* END OF EXTRACT: arg-ignore */
					ADVANCE_LEXER;
				}
				break;
			case 34:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-nb-of-chars */
					{
#line 277 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 4271 "tmp.syntax.c"
					}
					/* END OF EXTRACT: arg-nb-of-chars */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4280 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 961 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4288 "tmp.syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 35:
				{
					/* BEGINNING OF EXTRACT: arg-return-terminal */
					{
#line 281 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 4300 "tmp.syntax.c"
					}
					/* END OF EXTRACT: arg-return-terminal */
					ADVANCE_LEXER;
				}
				break;
			case 0:
				{
					SID_STRING ZIi;

					/* BEGINNING OF EXTRACT: identifier */
					{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4315 "tmp.syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_identifier */
					{
#line 774 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4324 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_from_identifier */
				}
				break;
			case 24:
				{
					SID_STRING ZIi;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 0:
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4341 "tmp.syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_reference */
					{
#line 778 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4354 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_from_reference */
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: sid-identifier */
					{
#line 235 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
    n = ( int ) strlen ( buff ) ;
    for ( s = token_buff ; *s ; s++ ) {
	if ( *s == '-' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = 'H' ;
	} else if ( *s == '_' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = '_' ;
	} else {
	    buff [ n++ ] = *s ;
	}
	if ( n >= 900 ) {
	    error ( ERROR_SERIOUS, "Identifier too long" ) ;
	    break ;
	}
    }
    buff [n] = 0 ;
    ZIb = xstrcpy ( buff ) ;
#line 4389 "tmp.syntax.c"
					}
					/* END OF EXTRACT: sid-identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4398 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_terminal_in_lhs */
					{
#line 988 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 4406 "tmp.syntax.c"
					}
					/* END OF ACTION: E_terminal_in_lhs */
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: string */
					{
#line 247 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 4420 "tmp.syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4429 "tmp.syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_string_arg_in_lhs */
					{
#line 965 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 4437 "tmp.syntax.c"
					}
					/* END OF ACTION: E_string_arg_in_lhs */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 160 */
		/* BEGINNING OF ACTION: append-arg-args-list */
		{
#line 418 "syntax.act"

    *(ZIl)->tail=(ZIa);
    (ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(ZIl)->nb_return_terminal++;
#line 4455 "tmp.syntax.c"
		}
		/* END OF ACTION: append-arg-args-list */
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR125(void)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 20:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_equal */
		{
#line 944 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 4488 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_equal */
	}
}

static void
ZRaction_Hcall_C_Crhs_Harg(argP *ZOa)
{
	argP ZIa;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-char-list */
			{
#line 265 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 4509 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-char-list */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4518 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_list_in_action_rhs */
			{
#line 979 "syntax.act"

	error(ERROR_SERIOUS, "Args of style ## are not implemented in actions right hand side. Whether they will be implemented in the future remains undecided at the moment.");
/* TODO take a decision.*/
#line 4527 "tmp.syntax.c"
			}
			/* END OF ACTION: E_sharp_list_in_action_rhs */
		}
		break;
	case 33:
		{
			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 273 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 4539 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
		}
		break;
	case 32:
		{
			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 269 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 4552 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
		}
		break;
	case 36:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 285 "syntax.act"

      ZIb=add_arg(arg_ignore,0);
#line 4567 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4576 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_ignore_in_rhs */
			{
#line 984 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4584 "tmp.syntax.c"
			}
			/* END OF ACTION: E_ignore_in_rhs */
		}
		break;
	case 34:
		{
			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 277 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 4596 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
		}
		break;
	case 35:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-return-terminal */
			{
#line 281 "syntax.act"

      ZIb=add_arg(arg_return_terminal,0);
#line 4611 "tmp.syntax.c"
			}
			/* END OF EXTRACT: arg-return-terminal */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4620 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_return_terminal_in_rhs */
			{
#line 969 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4628 "tmp.syntax.c"
			}
			/* END OF ACTION: E_return_terminal_in_rhs */
		}
		break;
	case 0:
		{
			SID_STRING ZIi;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4642 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_identifier */
			{
#line 774 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4651 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_from_identifier */
		}
		break;
	case 24:
		{
			SID_STRING ZIi;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 202 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4668 "tmp.syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_reference */
			{
#line 778 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4681 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_from_reference */
		}
		break;
	case 1:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 235 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
    n = ( int ) strlen ( buff ) ;
    for ( s = token_buff ; *s ; s++ ) {
	if ( *s == '-' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = 'H' ;
	} else if ( *s == '_' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = '_' ;
	} else {
	    buff [ n++ ] = *s ;
	}
	if ( n >= 900 ) {
	    error ( ERROR_SERIOUS, "Identifier too long" ) ;
	    break ;
	}
    }
    buff [n] = 0 ;
    ZIb = xstrcpy ( buff ) ;
#line 4716 "tmp.syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_terminal */
			{
#line 782 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4725 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_terminal */
		}
		break;
	case 2:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: string */
			{
#line 247 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 4739 "tmp.syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 787 "syntax.act"

	(ZIa) = add_none_arg();
#line 4748 "tmp.syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_in_action_rhs */
			{
#line 973 "syntax.act"

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
#line 4756 "tmp.syntax.c"
			}
			/* END OF ACTION: E_string_in_action_rhs */
		}
		break;
	case 41:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOa = ZIa;
}

/* BEGINNING OF TRAILER */

#line 991 "syntax.act"

#line 4778 "tmp.syntax.c"

/* END OF FILE */
