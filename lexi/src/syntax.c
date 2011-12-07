/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	/home/kate/svn/tendra17-lessfixes/obj-regen/bin/sid
 */

/* BEGINNING OF HEADER */

#line 126 "syntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/check.h>
#include <shared/string.h>

#include "adt/instruction.h"
#include "adt/keyword.h"
#include "adt/zone.h"
#include "adt/tree.h"
#include "adt/char.h"

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

typedef char *SID_STRING ;
typedef char *SID_CHARS ;
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


#line 97 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRexpected__semicolon(void);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZR146(void);
static void ZRtype_Hdefn(zoneP);
static void ZR147(void);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZR168(args_listP *);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR188(SID_STRING *);
static void ZR190(zoneP *, instructions_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZR212(zoneP, instructions_listP, zoneP *, instructions_listP *);
static void ZR214(zoneP *);
static void ZR215(zoneP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZR216(zoneP *, args_listP *, instructionP *);
static void ZRcopyright_Hstmt(zoneP);
static void ZR220(zoneP *, args_listP *, SID_STRING *, instructionP *);
static void ZR221(argP *, args_listP *);
static void ZR223(zoneP *, TypeTupleT *);
static void ZRcommand(zoneP);
static void ZRtype_Htuple_C_Ctype_Htuple1(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(SID_STRING *);
static void ZRaction_Hcall_C_Clhs_Harg(args_listP);
static void ZR121(void);
static void ZR123(void);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRexpected__semicolon(void)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 897 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 167 "syntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		SID_STRING ZIzid;
		SID_STRING ZIb;
		instructions_listP ZIentry_Hinstl;
		int ZIlendclosed;
		SID_STRING ZIe;
		instructions_listP ZIleaving_Hinstl;
		zoneP ZInew_Hzone;

		switch (CURRENT_TERMINAL) {
		case 13:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 180 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 178 "syntax.act"

    ZIzid = xstrdup ( token_buff ) ;
#line 205 "syntax.c"
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
#line 870 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 223 "syntax.c"
				}
				/* END OF ACTION: E_expected_identifier */
			}
		ZL2:;
		}
		/* END OF INLINE: 180 */
		/* BEGINNING OF INLINE: 182 */
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
#line 893 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 249 "syntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL4:;
		}
		/* END OF INLINE: 182 */
		ZR188 (&ZIb);
		ZR190 (&ZIz, &ZIentry_Hinstl);
		/* BEGINNING OF INLINE: 186 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 686 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 268 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 26:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 686 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 280 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 27:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: false */
					{
#line 687 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 292 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			case 40:
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
#line 876 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 311 "syntax.c"
				}
				/* END OF ACTION: E_expected_range */
				/* BEGINNING OF ACTION: false */
				{
#line 687 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 318 "syntax.c"
				}
				/* END OF ACTION: false */
			}
		ZL6:;
		}
		/* END OF INLINE: 186 */
		ZR188 (&ZIe);
		ZR190 (&ZIz, &ZIleaving_Hinstl);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-zone */
		{
#line 706 "syntax.act"

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
	add_mainpass((ZIz), (ZIb), inst_list);
#line 350 "syntax.c"
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
		case 40:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: update-zone-type */
		{
#line 722 "syntax.act"

	switch((ZInew_Hzone)->type) {
		case typezone_pseudo_token:
		case typezone_general_zone:
			(ZIz)->type = typezone_general_zone;
			break;
		case typezone_pure_function:
			break; /* do nothing */

	}
#line 384 "syntax.c"
		}
		/* END OF ACTION: update-zone-type */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		SID_STRING ZIa;

		/* BEGINNING OF INLINE: 107 */
		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					/* BEGINNING OF EXTRACT: digit */
					{
#line 235 "syntax.act"
 ZIa = "0123456789" ; 
#line 414 "syntax.c"
					}
					/* END OF EXTRACT: digit */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: lower */
					{
#line 234 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 426 "syntax.c"
					}
					/* END OF EXTRACT: lower */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: string */
					{
#line 223 "syntax.act"

    ZIa = xstrdup ( token_buff ) ;
#line 439 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: upper */
					{
#line 233 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 451 "syntax.c"
					}
					/* END OF EXTRACT: upper */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 107 */
		/* BEGINNING OF INLINE: 109 */
		{
			switch (CURRENT_TERMINAL) {
			case 21:
				{
					SID_STRING ZIb;

					ADVANCE_LEXER;
					ZRstring_Hplus (&ZIb);
					if ((CURRENT_TERMINAL) == 40) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: string-concat */
					{
#line 267 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 480 "syntax.c"
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
		/* END OF INLINE: 109 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZR146(void)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 880 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
#line 525 "syntax.c"
		}
		/* END OF ACTION: E_expected_open */
	}
}

static void
ZRtype_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		SID_STRING ZIs;

		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 178 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 554 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 126 */
		{
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 757 "syntax.act"

   (ZI0) = tree_zoneisglobal((ZIz)->top_level, (ZIz));
#line 570 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-type */
				{
#line 772 "syntax.act"

	NStringT str;
	EntryT* entry;
	nstring_copy_cstring(&str,(ZIs));
	xfree((ZIs));
	entry=table_get_entry(tree_get_table((ZIz)->top_level), &str);
	if(entry != NULL) {
		nstring_destroy(&str);
		/* TODO switch ? */
		if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Type %s already exists",(ZIs));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIs),(ZIs));
		else if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has already been declared as an action",(ZIs), (ZIs));
		else
			UNREACHED;
	} else {
		table_add_type(tree_get_table((ZIz)->top_level), &str, false);
	}
#line 598 "syntax.c"
				}
				/* END OF ACTION: make-type */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonetype */
				{
#line 859 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 610 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonetype */
			}
		ZL2:;
		}
		/* END OF INLINE: 126 */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZR147(void)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 884 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
#line 647 "syntax.c"
		}
		/* END OF ACTION: E_expected_close */
	}
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
ZL2_action_Hcall_C_Clhs_Htuple1:;
	{
		ZRaction_Hcall_C_Clhs_Harg (ZIl);
		/* BEGINNING OF INLINE: 222 */
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
			case 40:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 222 */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRtype_Htuple(zoneP ZIz, TypeTupleT *ZOa)
{
	TypeTupleT ZIa;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 818 "syntax.act"

	typetuple_init(&(ZIa));
#line 702 "syntax.c"
		}
		/* END OF ACTION: init-tuple */
		ZR223 (&ZIz, &ZIa);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	/* BEGINNING OF RESULT ASSIGNMENT: TYPETUPLE */
	{
#line 163 "syntax.act"

	typetuple_assign(ZOa, (&ZIa));
#line 721 "syntax.c"
	}
	/* END OF RESULT ASSIGNMENT: TYPETUPLE */
}

static void
ZRaction_Hcall_C_Crhs_Htuple1(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		argP ZIa;

		ZRaction_Hcall_C_Crhs_Harg (&ZIa);
		ZR221 (&ZIa, &ZIr);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZR168(args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 14:
		{
			ZRaction_Hcall_C_Crhs_Htuple (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 396 "syntax.act"

    (ZIr)=add_args_list();
#line 774 "syntax.c"
			}
			/* END OF ACTION: empty-args-list */
		}
		break;
	case 40:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRinstructions_Hlist(zoneP ZI206, instructions_listP *ZO211)
{
	instructions_listP ZI211;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		instructionP ZIinst;
		instructions_listP ZIinstl;
		zoneP ZI210;

		ZRinstruction (ZI206, &ZIinst);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: empty-inst-list */
		{
#line 625 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 813 "syntax.c"
		}
		/* END OF ACTION: empty-inst-list */
		/* BEGINNING OF ACTION: add-inst-to-list */
		{
#line 403 "syntax.act"

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
		if((ZIinst)->type == action_call) {
			args_list* rhs;
			args_list* lhs;
			EntryT* entryaction;
			ActionT* action;
			arg* p;
			TypeTupleEntryT* q;

			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			entryaction = (ZIinst)->u.act.called_act;
			action = entry_get_action(entryaction);
			rhs = (ZIinst)->u.act.rhs;
			lhs = (ZIinst)->u.act.lhs;

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
						EntryT* tableentry = table_get_entry(tree_get_table((ZI206)->top_level), &str);
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
							UNREACHED;
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((ZI206)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((ZI206)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((ZI206)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((ZI206)->top_level);
		 			break;
				case arg_none:
					break; /* Error already detected, do nothing and leave p->lexitype = NULL */
				case arg_ignore:
				case arg_return_terminal:
					UNREACHED;
				break;
			default:
				UNREACHED;
				break;
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						char* s6 = "unknown";
						char* s7 = "unknown";
						switch(p->type) {
						case arg_terminal:
							s6 = "$"; 
							s7 = p->u.literal;
							break;
						case arg_identifier:
							s7 = p->u.literal;
							break;
						case arg_nb_of_chars:
							s6 = "#n";
							break;
						case arg_char_nb:
							s6 = "#[number]";
							/* TODO s7=p->u.digit */;
							break;
						case arg_charP:
							s6 = "#*";
							break;
						}
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s%s\' has type \'%s%s\' when it should have type %s", s1, s6, s7, s2, s3, s4, s5);
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
						nstring_copy_cstring(&str, p->u.literal);
						entrytype = localnames_get_type(locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry(tree_get_table((ZI206)->top_level), &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name(tree_get_table((ZI206)->top_level), &str);
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
					entrytype = lexer_terminal_type((ZI206)->top_level);
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
#line 1029 "syntax.c"
		}
		/* END OF ACTION: add-inst-to-list */
		ZR212 (ZI206, ZIinstl, &ZI210, &ZI211);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZO211 = ZI211;
}

static void
ZRtype_Htuple_C_Ctype_Hname(zoneP ZIz, TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		SID_STRING ZIname;
		SID_STRING ZItype;
		int ZIisref;

		/* BEGINNING OF INLINE: 130 */
		{
			switch (CURRENT_TERMINAL) {
			case 0:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 178 "syntax.act"

    ZIname = xstrdup ( token_buff ) ;
#line 1067 "syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-identifier */
					{
#line 277 "syntax.act"

    (ZIname) = xstrdup("");
#line 1080 "syntax.c"
					}
					/* END OF ACTION: empty-identifier */
				}
				break;
			}
		}
		/* END OF INLINE: 130 */
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
#line 178 "syntax.act"

    ZItype = xstrdup ( token_buff ) ;
#line 1102 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 133 */
		{
			switch (CURRENT_TERMINAL) {
			case 24:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 686 "syntax.act"
 (ZIisref) = 1 ; 
#line 1120 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 687 "syntax.act"
 (ZIisref) = 0 ; 
#line 1131 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 133 */
		/* BEGINNING OF ACTION: append-tuple */
		{
#line 824 "syntax.act"

	EntryT* entry;
	NStringT tstr, istr;
	nstring_copy_cstring(&tstr,(ZItype));
	nstring_copy_cstring(&istr,(ZIname));
	entry = table_get_entry(tree_get_table((ZIz)->top_level), &tstr);
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
#line 1162 "syntax.c"
		}
		/* END OF ACTION: append-tuple */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		SID_STRING ZIs;
		SID_STRING ZIt;

		switch (CURRENT_TERMINAL) {
		case 9:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRstring_Hplus (&ZIs);
		ZR123 ();
		ZRstring_Hplus (&ZIt);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-trigraph */
		{
#line 315 "syntax.act"

	assert((ZIz) != NULL);
	assert((ZIs) != NULL);
	assert((ZIt) != NULL);

	add_prepass((ZIz), (ZIs), (ZIt));
#line 1205 "syntax.c"
		}
		/* END OF ACTION: make-trigraph */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZR188(SID_STRING *ZOe)
{
	SID_STRING ZIe;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		ZRnon_Hempty_Hchars (&ZIe);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_chars */
		{
#line 887 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1239 "syntax.c"
		}
		/* END OF ACTION: E_expected_chars */
	}
ZL0:;
	*ZOe = ZIe;
}

static void
ZR190(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
{
	instructions_listP ZIleaving_Hinstl;

	switch (CURRENT_TERMINAL) {
	case 18:
		{
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIleaving_Hinstl);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-inst-list */
			{
#line 625 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 1270 "syntax.c"
			}
			/* END OF ACTION: empty-inst-list */
		}
		break;
	case 40:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOleaving_Hinstl = ZIleaving_Hinstl;
}

void
read_lex(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		ZRcommand_Hlist (ZIz);
		/* BEGINNING OF INLINE: 195 */
		{
			if ((CURRENT_TERMINAL) == 40) {
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
#line 918 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1317 "syntax.c"
				}
				/* END OF ACTION: syntax-error */
			}
		ZL2:;
		}
		/* END OF INLINE: 195 */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRaction_Hdecl(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		SID_STRING ZIi;
		TypeTupleT ZIit;
		TypeTupleT ZIot;

		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 138 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 37:
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
#line 909 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
#line 1368 "syntax.c"
				}
				/* END OF ACTION: E_expected_begin_action */
			}
		ZL2:;
		}
		/* END OF INLINE: 138 */
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 1382 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 139 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 38:
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
#line 913 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
#line 1409 "syntax.c"
				}
				/* END OF ACTION: E_expected_end_action */
			}
		ZL4:;
		}
		/* END OF INLINE: 139 */
		/* BEGINNING OF INLINE: 140 */
		{
			switch (CURRENT_TERMINAL) {
			case 23:
				{
					ADVANCE_LEXER;
					ZR146 ();
					ZRtype_Htuple (ZIz, &ZIit);
					ZR147 ();
					ZR123 ();
					ZR146 ();
					ZRtype_Htuple (ZIz, &ZIot);
					ZR147 ();
					if ((CURRENT_TERMINAL) == 40) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 818 "syntax.act"

	typetuple_init(&(ZIit));
#line 1442 "syntax.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 818 "syntax.act"

	typetuple_init(&(ZIot));
#line 1450 "syntax.c"
					}
					/* END OF ACTION: init-tuple */
				}
				break;
			}
		}
		/* END OF INLINE: 140 */
		/* BEGINNING OF ACTION: make-action */
		{
#line 794 "syntax.act"

	NStringT str;
	EntryT* entry;
	nstring_copy_cstring(&str, (ZIi));
	entry=table_get_entry(tree_get_table((ZIz)->top_level), &str);
	if(entry != NULL) {
		nstring_destroy(&str);
		/* TODO switch ? */
	   	if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Action %s already exists",(ZIi));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIi),(ZIi));
		else if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Can't create action %s, %s has already been declared as a type",(ZIi), (ZIi));
		else
			UNREACHED;
	} else {
		table_add_action(tree_get_table((ZIz)->top_level), &str , (&ZIit), (&ZIot));
	}
	xfree((ZIi));
#line 1481 "syntax.c"
		}
		/* END OF ACTION: make-action */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRinstruction(zoneP ZIz, instructionP *ZOinst)
{
	instructionP ZIinst;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		args_listP ZIl;

		/* BEGINNING OF ACTION: empty-args-list */
		{
#line 396 "syntax.act"

    (ZIl)=add_args_list();
#line 1507 "syntax.c"
		}
		/* END OF ACTION: empty-args-list */
		ZR216 (&ZIz, &ZIl, &ZIinst);
		if ((CURRENT_TERMINAL) == 40) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
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
	case 36: case 39:
		{
			ZRcommand (ZIz);
			/* BEGINNING OF INLINE: command-list */
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_command_Hlist;
			}
			/* END OF INLINE: command-list */
		}
		/*UNREACHED*/
	case 40:
		return;
	default:
		break;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 918 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1557 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZR212(zoneP ZI206, instructions_listP ZI209, zoneP *ZO210, instructions_listP *ZO211)
{
	zoneP ZI210;
	instructions_listP ZI211;

ZL2_212:;
	switch (CURRENT_TERMINAL) {
	case 28:
		{
			instructions_listP ZIinstl;
			instructionP ZIinst;

			ZIinstl = ZI209;
			ADVANCE_LEXER;
			ZRinstruction (ZI206, &ZIinst);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-inst-to-list */
			{
#line 403 "syntax.act"

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
		if((ZIinst)->type == action_call) {
			args_list* rhs;
			args_list* lhs;
			EntryT* entryaction;
			ActionT* action;
			arg* p;
			TypeTupleEntryT* q;

			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			entryaction = (ZIinst)->u.act.called_act;
			action = entry_get_action(entryaction);
			rhs = (ZIinst)->u.act.rhs;
			lhs = (ZIinst)->u.act.lhs;

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
						EntryT* tableentry = table_get_entry(tree_get_table((ZI206)->top_level), &str);
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
							UNREACHED;
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((ZI206)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((ZI206)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((ZI206)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((ZI206)->top_level);
		 			break;
				case arg_none:
					break; /* Error already detected, do nothing and leave p->lexitype = NULL */
				case arg_ignore:
				case arg_return_terminal:
					UNREACHED;
				break;
			default:
				UNREACHED;
				break;
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						char* s6 = "unknown";
						char* s7 = "unknown";
						switch(p->type) {
						case arg_terminal:
							s6 = "$"; 
							s7 = p->u.literal;
							break;
						case arg_identifier:
							s7 = p->u.literal;
							break;
						case arg_nb_of_chars:
							s6 = "#n";
							break;
						case arg_char_nb:
							s6 = "#[number]";
							/* TODO s7=p->u.digit */;
							break;
						case arg_charP:
							s6 = "#*";
							break;
						}
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s%s\' has type \'%s%s\' when it should have type %s", s1, s6, s7, s2, s3, s4, s5);
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
						nstring_copy_cstring(&str, p->u.literal);
						entrytype = localnames_get_type(locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry(tree_get_table((ZI206)->top_level), &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name(tree_get_table((ZI206)->top_level), &str);
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
					entrytype = lexer_terminal_type((ZI206)->top_level);
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
#line 1796 "syntax.c"
			}
			/* END OF ACTION: add-inst-to-list */
			/* BEGINNING OF INLINE: 212 */
			ZI209 = ZIinstl;
			goto ZL2_212;
			/* END OF INLINE: 212 */
		}
		/*UNREACHED*/
	default:
		{
			ZI210 = ZI206;
			ZI211 = ZI209;
		}
		break;
	case 40:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZO210 = ZI210;
	*ZO211 = ZI211;
}

static void
ZR214(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 1837 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR121 ();
			ZRnon_Hempty_Hchars (&ZIs);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-group */
			{
#line 304 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 1852 "syntax.c"
			}
			/* END OF ACTION: make-group */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 11:
		{
			SID_STRING ZIs;

			ADVANCE_LEXER;
			ZR121 ();
			ZRstring_Hplus (&ZIs);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-white */
			{
#line 290 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 1881 "syntax.c"
			}
			/* END OF ACTION: make-white */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 40:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZR215(zoneP *ZIz)
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
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-default */
			{
#line 655 "syntax.act"

    (*ZIz)->default_instructions=(ZIinst_Hlist);
	if((ZIinst_Hlist)->nb_return_terminal)
		(*ZIz)->type=typezone_general_zone;
#line 1930 "syntax.c"
			}
			/* END OF ACTION: make-default */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 3: case 4: case 5:
		{
			SID_STRING ZIs;
			instructions_listP ZIinst_Hlist;

			ZRnon_Hempty_Hchars (&ZIs);
			switch (CURRENT_TERMINAL) {
			case 18:
				break;
			case 40:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: check-inst-list */
			{
#line 615 "syntax.act"

	if((ZIinst_Hlist)->nb_return_terminal>1)
		error(ERROR_SERIOUS, "At most one return terminal may be specified per instruction list");
#line 1967 "syntax.c"
			}
			/* END OF ACTION: check-inst-list */
			/* BEGINNING OF ACTION: make-token */
			{
#line 636 "syntax.act"

	add_mainpass((*ZIz), (ZIs), (ZIinst_Hlist));
	if((ZIinst_Hlist)->nb_return_terminal)
		(*ZIz)->type=typezone_general_zone;
#line 1977 "syntax.c"
			}
			/* END OF ACTION: make-token */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 40:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 223 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 2022 "syntax.c"
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
		/* BEGINNING OF INLINE: 176 */
		{
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 757 "syntax.act"

   (ZI0) = tree_zoneisglobal((ZIz)->top_level, (ZIz));
#line 2050 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-keyword */
				{
#line 669 "syntax.act"

    switch((ZIinst)->type) {
    case return_terminal: 
    /* Fallback is intentional */
      add_keyword ( (ZIz), (ZIs), (ZIinst) ) ;
    break;
    default:
      error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
  }
#line 2067 "syntax.c"
				}
				/* END OF ACTION: make-keyword */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
				{
#line 851 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 2080 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonekeyword */
			}
		ZL2:;
		}
		/* END OF INLINE: 176 */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZR216(zoneP *ZIz, args_listP *ZIl, instructionP *ZOinst)
{
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	case 32:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 242 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 2112 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 2121 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 922 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2129 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2140 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2164 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2178 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2228 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 31:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 238 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 2245 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 2254 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 922 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2262 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2273 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2297 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2311 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2361 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 35:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 254 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 2377 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2389 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2413 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2427 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2477 "syntax.c"
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

			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 246 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 2494 "syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 2503 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 922 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2511 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2522 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2546 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2560 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2610 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 34:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-return-terminal */
			{
#line 250 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 2626 "syntax.c"
			}
			/* END OF EXTRACT: arg-return-terminal */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2638 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2662 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2676 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2726 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 37:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2744 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2758 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2808 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 0:
		{
			SID_STRING ZI217;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 178 "syntax.act"

    ZI217 = xstrdup ( token_buff ) ;
#line 2825 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_identifier */
			{
#line 735 "syntax.act"

	(ZIa) = add_identifier_arg ((ZI217));
#line 2834 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_identifier */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2845 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2869 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2883 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 2933 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 29:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-donothing-inst */
			{
#line 332 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 2946 "syntax.c"
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
			case 40:
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2989 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3003 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 3053 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 24:
		{
			SID_STRING ZI218;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZI218 = xstrdup ( token_buff ) ;
#line 3073 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_reference */
			{
#line 739 "syntax.act"

	(ZIa) = add_reference_arg ((ZI218));
#line 3086 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_reference */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3097 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3121 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3135 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 3185 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 1:
		{
			SID_STRING ZI219;

			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 211 "syntax.act"

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
    ZI219 = xstrdup ( buff ) ;
#line 3220 "syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			ZR220 (ZIz, ZIl, &ZI219, &ZIinst);
			if ((CURRENT_TERMINAL) == 40) {
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
#line 223 "syntax.act"

    ZIb = xstrdup ( token_buff ) ;
#line 3243 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 3252 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_arg_in_lhs */
			{
#line 926 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 3260 "syntax.c"
			}
			/* END OF ACTION: E_string_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3271 "syntax.c"
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
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3295 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3309 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 3359 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 40:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZRcopyright_Hstmt(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 223 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 3407 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 116 */
		{
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 757 "syntax.act"

   (ZI0) = tree_zoneisglobal((ZIz)->top_level, (ZIz));
#line 3423 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-copyright */
				{
#line 761 "syntax.act"

	FILE *file=fopen((ZIs),"r");
	if(file) {
		tree_add_copyright_file((ZIz)->top_level, file, (ZIs));
	} else {
		error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
	}
#line 3438 "syntax.c"
				}
				/* END OF ACTION: make-copyright */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
				{
#line 855 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 3450 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonecopyright */
			}
		ZL2:;
		}
		/* END OF INLINE: 116 */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZR220(zoneP *ZIz, args_listP *ZIl, SID_STRING *ZI219, instructionP *ZOinst)
{
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: make-terminal-inst */
			{
#line 328 "syntax.act"

        (ZIinst)=add_instruction_return_terminal((*ZI219));
#line 3477 "syntax.c"
			}
			/* END OF ACTION: make-terminal-inst */
		}
		break;
	case 20:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 3493 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_terminal_in_lhs */
			{
#line 944 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 3501 "syntax.c"
			}
			/* END OF ACTION: E_terminal_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 373 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3512 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3530 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 387 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3544 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR168 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 338 "syntax.act"

	NStringT key;
	EntryT* entry;
	nstring_copy_cstring(&key, (ZIi));
	entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
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
#line 3594 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 40:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZR221(argP *ZIa, args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 28:
		{
			ADVANCE_LEXER;
			ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 380 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
#line 3632 "syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 396 "syntax.act"

    (ZIr)=add_args_list();
#line 3644 "syntax.c"
			}
			/* END OF ACTION: empty-args-list */
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 380 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
#line 3655 "syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	case 40:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZR223(zoneP *ZIz, TypeTupleT *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 23:
		{
			ZRtype_Htuple_C_Ctype_Htuple1 (*ZIz, ZIa);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 40:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRcommand(zoneP ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 7:
		{
			ADVANCE_LEXER;
			ZR214 (&ZIz);
			if ((CURRENT_TERMINAL) == 40) {
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
			case 40:
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
			ZR215 (&ZIz);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 36:
		{
			ZRaction_Hdecl (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 6:
		{
			ZRcopyright_Hstmt (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			ZRkeyword_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 9:
		{
			ZRtrigraph_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 39:
		{
			ZRtype_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 13:
		{
			ZRzone_Hdefn (ZIz);
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 40:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRtype_Htuple_C_Ctype_Htuple1(zoneP ZIz, TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
ZL2_type_Htuple_C_Ctype_Htuple1:;
	{
		ZRtype_Htuple_C_Ctype_Hname (ZIz, ZIa);
		/* BEGINNING OF INLINE: 224 */
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
			case 40:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 224 */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 40) {
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
		/* BEGINNING OF INLINE: 166 */
		{
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 2: case 24:
			case 31: case 32: case 33: case 34:
			case 35:
				{
					ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
					if ((CURRENT_TERMINAL) == 40) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-args-list */
					{
#line 396 "syntax.act"

    (ZIr)=add_args_list();
#line 3882 "syntax.c"
					}
					/* END OF ACTION: empty-args-list */
				}
				break;
			}
		}
		/* END OF INLINE: 166 */
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
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRnon_Hempty_Hchars(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		ZRstring_Hplus (&ZIs);
		/* BEGINNING OF INLINE: 113 */
		{
			if ((CURRENT_TERMINAL) == 40) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-non-empty */
				{
#line 642 "syntax.act"

	(ZI0) = strlen((ZIs)) > 0;
#line 3928 "syntax.c"
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
#line 647 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 3942 "syntax.c"
				}
				/* END OF ACTION: E_empty_character_string */
			}
		ZL2:;
		}
		/* END OF INLINE: 113 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRaction_Hcall_C_Clhs_Harg(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 40) {
		return;
	}
	{
		argP ZIa;

		/* BEGINNING OF INLINE: 153 */
		{
			switch (CURRENT_TERMINAL) {
			case 32:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-nb */
					{
#line 242 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 3979 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-nb */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 3988 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 922 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3996 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 31:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-string */
					{
#line 238 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 4010 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4019 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 922 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4027 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 35:
				{
					/* BEGINNING OF EXTRACT: arg-ignore */
					{
#line 254 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 4039 "syntax.c"
					}
					/* END OF EXTRACT: arg-ignore */
					ADVANCE_LEXER;
				}
				break;
			case 33:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-nb-of-chars */
					{
#line 246 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 4054 "syntax.c"
					}
					/* END OF EXTRACT: arg-nb-of-chars */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4063 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 922 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4071 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 34:
				{
					/* BEGINNING OF EXTRACT: arg-return-terminal */
					{
#line 250 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 4083 "syntax.c"
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
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4098 "syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_identifier */
					{
#line 735 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4107 "syntax.c"
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
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4124 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_reference */
					{
#line 739 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4137 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_reference */
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: sid-identifier */
					{
#line 211 "syntax.act"

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
    ZIb = xstrdup ( buff ) ;
#line 4172 "syntax.c"
					}
					/* END OF EXTRACT: sid-identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4181 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_terminal_in_lhs */
					{
#line 944 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 4189 "syntax.c"
					}
					/* END OF ACTION: E_terminal_in_lhs */
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: string */
					{
#line 223 "syntax.act"

    ZIb = xstrdup ( token_buff ) ;
#line 4203 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4212 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_string_arg_in_lhs */
					{
#line 926 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 4220 "syntax.c"
					}
					/* END OF ACTION: E_string_arg_in_lhs */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 153 */
		/* BEGINNING OF ACTION: append-arg-args-list */
		{
#line 373 "syntax.act"

    *(ZIl)->tail=(ZIa);
    (ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(ZIl)->nb_return_terminal++;
#line 4238 "syntax.c"
		}
		/* END OF ACTION: append-arg-args-list */
	}
	return;
ZL1:;
	SAVE_LEXER (40);
	return;
}

static void
ZR121(void)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 905 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 4271 "syntax.c"
		}
		/* END OF ACTION: E_expected_equal */
	}
}

static void
ZR123(void)
{
	if ((CURRENT_TERMINAL) == 40) {
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
#line 901 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 4300 "syntax.c"
		}
		/* END OF ACTION: E_expected_arrow */
	}
}

static void
ZRaction_Hcall_C_Crhs_Harg(argP *ZOa)
{
	argP ZIa;

	switch (CURRENT_TERMINAL) {
	case 32:
		{
			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 242 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 4319 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
		}
		break;
	case 31:
		{
			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 238 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 4332 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
		}
		break;
	case 35:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 254 "syntax.act"

      ZIb=add_arg(arg_ignore,0);
#line 4347 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4356 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_ignore_in_rhs */
			{
#line 940 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4364 "syntax.c"
			}
			/* END OF ACTION: E_ignore_in_rhs */
		}
		break;
	case 33:
		{
			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 246 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 4376 "syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
		}
		break;
	case 34:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-return-terminal */
			{
#line 250 "syntax.act"

      ZIb=add_arg(arg_return_terminal,0);
#line 4391 "syntax.c"
			}
			/* END OF EXTRACT: arg-return-terminal */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4400 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_return_terminal_in_rhs */
			{
#line 930 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4408 "syntax.c"
			}
			/* END OF ACTION: E_return_terminal_in_rhs */
		}
		break;
	case 0:
		{
			SID_STRING ZIi;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4422 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_identifier */
			{
#line 735 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4431 "syntax.c"
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
#line 178 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4448 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_reference */
			{
#line 739 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4461 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_reference */
		}
		break;
	case 1:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 211 "syntax.act"

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
    ZIb = xstrdup ( buff ) ;
#line 4496 "syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_terminal */
			{
#line 743 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4505 "syntax.c"
			}
			/* END OF ACTION: make_arg_terminal */
		}
		break;
	case 2:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: string */
			{
#line 223 "syntax.act"

    ZIb = xstrdup ( token_buff ) ;
#line 4519 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 748 "syntax.act"

	(ZIa) = add_none_arg();
#line 4528 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_in_action_rhs */
			{
#line 934 "syntax.act"

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
#line 4536 "syntax.c"
			}
			/* END OF ACTION: E_string_in_action_rhs */
		}
		break;
	case 40:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (40);
	return;
ZL0:;
	*ZOa = ZIa;
}

/* BEGINNING OF TRAILER */

#line 947 "syntax.act"

#line 4558 "syntax.c"

/* END OF FILE */
