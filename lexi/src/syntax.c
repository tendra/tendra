/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 125 "syntax.act"


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

#include <adt/action.h>
#include <adt/entry.h>
#include <adt/cmd.h>
#include <adt/keyword.h>
#include <adt/zone.h>
#include <adt/char.h>

#include "ast.h"
#include "lexer.h"
#include "syntax.h"
#include "options.h"


#define ADVANCE_LEXER ADVANCE_LXI_LEXER
#define CURRENT_TERMINAL CURRENT_LXI_TERMINAL 
#define SAVE_LEXER SAVE_LXI_LEXER
#define RESTORE_LEXER RESTORE_LXI_LEXER



/*
    PARSER TYPES

    These types give the implementation of the types used in the syntax.
*/

typedef char *SID_STRING ;
typedef char *SID_CHARS ;
/*typedef zone* zoneP; Done in syntax.h */
typedef struct cmd* cmdP ;
typedef struct cmd_list* cmd_listP ;
typedef struct arg* argP;
typedef struct args_list* args_listP;
typedef struct TypeTupleT typetuple;

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


#line 96 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRexpected__semicolon(void);
static void ZRzone_Hdefn(zoneP);
static void ZR141(void);
static void ZR142(void);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP);
static void ZRtype_Htuple(zoneP, typetuple *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZRcmd_Hlist(zoneP, cmd_listP *);
static void ZR163(args_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, typetuple *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZRcmd(zoneP, cmdP *);
static void ZR183(SID_STRING *);
static void ZR185(zoneP *, cmd_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZR207(zoneP, cmd_listP, zoneP *, cmd_listP *);
static void ZRcommand_Hlist(zoneP);
static void ZR209(zoneP *);
static void ZR210(zoneP *);
static void ZR211(zoneP *, args_listP *, cmdP *);
static void ZR215(zoneP *, args_listP *, SID_STRING *, cmdP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZR216(argP *, args_listP *);
static void ZR218(zoneP *, typetuple *);
static void ZRcommand(zoneP);
static void ZRtype_Htuple_C_Ctype_Htuple1(zoneP, typetuple *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(SID_STRING *);
static void ZR116(void);
static void ZR118(void);
static void ZRaction_Hcall_C_Clhs_Harg(args_listP);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRexpected__semicolon(void)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 21:
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
#line 882 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 165 "syntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIzid;
		SID_STRING ZIb;
		cmd_listP ZIentry_Hinstl;
		int ZIlendclosed;
		SID_STRING ZIe;
		cmd_listP ZIleaving_Hinstl;
		zoneP ZInew_Hzone;

		switch (CURRENT_TERMINAL) {
		case 12:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 175 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 177 "syntax.act"

    ZIzid = xstrdup ( token_buff ) ;
#line 203 "syntax.c"
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
#line 855 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 221 "syntax.c"
				}
				/* END OF ACTION: E_expected_identifier */
			}
		ZL2:;
		}
		/* END OF INLINE: 175 */
		/* BEGINNING OF INLINE: 177 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 22:
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
#line 878 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 247 "syntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL4:;
		}
		/* END OF INLINE: 177 */
		ZR183 (&ZIb);
		ZR185 (&ZIz, &ZIentry_Hinstl);
		/* BEGINNING OF INLINE: 181 */
		{
			switch (CURRENT_TERMINAL) {
			case 24:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 685 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 266 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 685 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 278 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 26:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: false */
					{
#line 686 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 290 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			case 39:
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
#line 861 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 309 "syntax.c"
				}
				/* END OF ACTION: E_expected_range */
				/* BEGINNING OF ACTION: false */
				{
#line 686 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 316 "syntax.c"
				}
				/* END OF ACTION: false */
			}
		ZL6:;
		}
		/* END OF INLINE: 181 */
		ZR183 (&ZIe);
		ZR185 (&ZIz, &ZIleaving_Hinstl);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-zone */
		{
#line 705 "syntax.act"

    struct cmd* inst;
    struct cmd_list* inst_list;
    (ZInew_Hzone)=add_zone((ZIz),(ZIzid),(ZIe), (ZIlendclosed) );

    (ZInew_Hzone)->exit=(ZIleaving_Hinstl);
    if((ZInew_Hzone)->exit->nb_return_terminal)
	(ZInew_Hzone)->type= typezone_pseudo_token;
    (ZInew_Hzone)->enter=(ZIentry_Hinstl);
    if((ZInew_Hzone)->enter->nb_return_terminal)
	(ZInew_Hzone)->type=typezone_general_zone;
    inst=add_cmd_pushzone((ZInew_Hzone));
    inst_list=add_cmd_list();
    *(inst_list->tail)=inst;
    inst_list->tail=&(inst->next);
	add_mainpass((ZIz), (ZIb), inst_list);
#line 348 "syntax.c"
		}
		/* END OF ACTION: make-zone */
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcommand_Hlist (ZInew_Hzone);
		switch (CURRENT_TERMINAL) {
		case 16:
			break;
		case 39:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: update-zone-type */
		{
#line 721 "syntax.act"

	switch((ZInew_Hzone)->type) {
		case typezone_pseudo_token:
		case typezone_general_zone:
			(ZIz)->type = typezone_general_zone;
			break;
		case typezone_pure_function:
			break; /* do nothing */

	}
#line 382 "syntax.c"
		}
		/* END OF ACTION: update-zone-type */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR141(void)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 13:
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
#line 865 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
#line 415 "syntax.c"
		}
		/* END OF ACTION: E_expected_open */
	}
}

static void
ZR142(void)
{
	if ((CURRENT_TERMINAL) == 39) {
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
		/* BEGINNING OF ACTION: E_expected_close */
		{
#line 869 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
#line 444 "syntax.c"
		}
		/* END OF ACTION: E_expected_close */
	}
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIa;

		/* BEGINNING OF INLINE: 104 */
		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					/* BEGINNING OF EXTRACT: digit */
					{
#line 234 "syntax.act"
 ZIa = "0123456789" ; 
#line 470 "syntax.c"
					}
					/* END OF EXTRACT: digit */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: lower */
					{
#line 233 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 482 "syntax.c"
					}
					/* END OF EXTRACT: lower */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: string */
					{
#line 222 "syntax.act"

    ZIa = xstrdup ( token_buff ) ;
#line 495 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: upper */
					{
#line 232 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 507 "syntax.c"
					}
					/* END OF EXTRACT: upper */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 104 */
		/* BEGINNING OF INLINE: 106 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					SID_STRING ZIb;

					ADVANCE_LEXER;
					ZRstring_Hplus (&ZIb);
					if ((CURRENT_TERMINAL) == 39) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: string-concat */
					{
#line 266 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 536 "syntax.c"
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
		/* END OF INLINE: 106 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRtype_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIs;

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
#line 177 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 581 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 121 */
		{
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 756 "syntax.act"

   (ZI0) = tree_zoneisglobal((ZIz)->ast, (ZIz));
#line 597 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-type */
				{
#line 762 "syntax.act"

	NStringT str;
	struct entry *e;
	nstring_copy_cstring(&str,(ZIs));
	xfree((ZIs));
	e = table_get_entry(tree_get_table((ZIz)->ast), &str);
	if(e != NULL) {
		nstring_destroy(&str);
		/* TODO switch ? */
		if(entry_is_type(e))
			error(ERROR_SERIOUS, "Type %s already exists",(ZIs));
		else if(entry_is_localname(e))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIs),(ZIs));
		else if(entry_is_action(e))
			error(ERROR_SERIOUS, "Can't create type %s, %s has already been declared as an action",(ZIs), (ZIs));
		else
			UNREACHED;
	} else {
		table_add_type(tree_get_table((ZIz)->ast), &str, false);
	}
#line 625 "syntax.c"
				}
				/* END OF ACTION: make-type */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonetype */
				{
#line 844 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 637 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonetype */
			}
		ZL2:;
		}
		/* END OF INLINE: 121 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
ZL2_action_Hcall_C_Clhs_Htuple1:;
	{
		ZRaction_Hcall_C_Clhs_Harg (ZIl);
		/* BEGINNING OF INLINE: 217 */
		{
			switch (CURRENT_TERMINAL) {
			case 27:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: action-call::lhs-tuple1 */
					goto ZL2_action_Hcall_C_Clhs_Htuple1;
					/* END OF INLINE: action-call::lhs-tuple1 */
				}
				/*UNREACHED*/
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 217 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRtype_Htuple(zoneP ZIz, typetuple *ZOa)
{
	typetuple ZIa;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 808 "syntax.act"

	typetuple_init(&(ZIa));
#line 700 "syntax.c"
		}
		/* END OF ACTION: init-tuple */
		ZR218 (&ZIz, &ZIa);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	/* BEGINNING OF RESULT ASSIGNMENT: TYPETUPLE */
	{
#line 162 "syntax.act"

	typetuple_assign(ZOa, (&ZIa));
#line 719 "syntax.c"
	}
	/* END OF RESULT ASSIGNMENT: TYPETUPLE */
}

static void
ZRaction_Hcall_C_Crhs_Htuple1(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		argP ZIa;

		ZRaction_Hcall_C_Crhs_Harg (&ZIa);
		ZR216 (&ZIa, &ZIr);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRcmd_Hlist(zoneP ZI201, cmd_listP *ZO206)
{
	cmd_listP ZI206;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		cmdP ZIinst;
		cmd_listP ZIinstl;
		zoneP ZI205;

		ZRcmd (ZI201, &ZIinst);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: empty-inst-list */
		{
#line 624 "syntax.act"

    (ZIinstl)=add_cmd_list();
#line 773 "syntax.c"
		}
		/* END OF ACTION: empty-inst-list */
		/* BEGINNING OF ACTION: add-inst-to-list */
		{
#line 402 "syntax.act"

	if((ZIinst)!=NULL) { /* if (ZIinst) == NULL, an error has already been issued.*/
		struct LocalNamesT* locals = cmdlist_localnames((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((ZIinst)->type==return_terminal || (ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an cmd-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((ZIinstl)->nb_return_terminal>0 && (ZIinst)->type!=do_nothing)
			error(ERROR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
		if((ZIinst)->type == return_terminal) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == action_call) {
			struct args_list* rhs;
			struct args_list* lhs;
			struct entry *ea;
			struct action *act;
			struct arg* p;
			struct TypeTupleEntryT* q;

			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			ea = (ZIinst)->u.act.called_act;
			act = entry_get_action(ea);
			rhs = (ZIinst)->u.act.rhs;
			lhs = (ZIinst)->u.act.lhs;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = act->in.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	struct entry *et = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.literal);
					et=localnames_get_type(locals, &str);
					nstring_destroy(&str);
					if(!et) {
						struct entry *e = table_get_entry(tree_get_table((ZI201)->ast), &str);
						if(!e) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
							et = NULL;
						} else if (entry_is_localname(e)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
							et = NULL;
						} else if (entry_is_action(e)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
							et = NULL;
						} else if (entry_is_type(e)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
							et = NULL;
						} else {
							UNREACHED;
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(ast)) */
					et = lexer_string_type((ZI201)->ast);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(ast)) */
					et = lexer_char_type((ZI201)->ast);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(ast)) */
					et = lexer_terminal_type((ZI201)->ast);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(ast)) */
					et = lexer_int_type((ZI201)->ast);
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
			if(et) {
				if( q->et!=et || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(ea));
						char* s2 = nstring_to_cstring(entry_key(et));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->et));
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
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
				DEALLOCATE(s);
			}

			for ( p = lhs->head, q = act->out.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	struct entry *et;
				switch (p->type) {
				case arg_identifier: 
					{
						NStringT str;
						nstring_copy_cstring(&str, p->u.literal);
						et = localnames_get_type(locals, &str);
						if(!et) {
							struct entry *e= table_get_entry(tree_get_table((ZI201)->ast), &str);
							localnames_add_nstring(locals, &str, q->et);
							if(e) {
								nstring_destroy(&str);
								if (entry_is_action(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name(tree_get_table((ZI201)->ast), &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								et=q->et; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					et = lexer_terminal_type((ZI201)->ast);
					q->is_reference = false;
					/* TODO assert(q->is_reference == false) */
					break;
				case arg_ignore:
					/*always acceptable */
					et = q->et;
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
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, too many results", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
				DEALLOCATE(s);
			}
		}
		/* TODO only append if no error */
		*(ZIinstl)->tail=(ZIinst);
		(ZIinstl)->tail=&(ZIinst)->next;
		++((ZIinstl)->size);
	}
#line 989 "syntax.c"
		}
		/* END OF ACTION: add-inst-to-list */
		ZR207 (ZI201, ZIinstl, &ZI205, &ZI206);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZO206 = ZI206;
}

static void
ZR163(args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 13:
		{
			ZRaction_Hcall_C_Crhs_Htuple (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 395 "syntax.act"

    (ZIr)=add_args_list();
#line 1028 "syntax.c"
			}
			/* END OF ACTION: empty-args-list */
		}
		break;
	case 39:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRtype_Htuple_C_Ctype_Hname(zoneP ZIz, typetuple *ZIa)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIname;
		SID_STRING ZItype;
		int ZIisref;

		/* BEGINNING OF INLINE: 125 */
		{
			switch (CURRENT_TERMINAL) {
			case 0:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 177 "syntax.act"

    ZIname = xstrdup ( token_buff ) ;
#line 1065 "syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-identifier */
					{
#line 276 "syntax.act"

    (ZIname) = xstrdup("");
#line 1078 "syntax.c"
					}
					/* END OF ACTION: empty-identifier */
				}
				break;
			}
		}
		/* END OF INLINE: 125 */
		switch (CURRENT_TERMINAL) {
		case 22:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 177 "syntax.act"

    ZItype = xstrdup ( token_buff ) ;
#line 1100 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 128 */
		{
			switch (CURRENT_TERMINAL) {
			case 23:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 685 "syntax.act"
 (ZIisref) = 1 ; 
#line 1118 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 686 "syntax.act"
 (ZIisref) = 0 ; 
#line 1129 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 128 */
		/* BEGINNING OF ACTION: append-tuple */
		{
#line 814 "syntax.act"

	struct entry *et;
	NStringT tstr, istr;
	nstring_copy_cstring(&tstr,(ZItype));
	nstring_copy_cstring(&istr,(ZIname));
	et = table_get_entry(tree_get_table((ZIz)->ast), &tstr);
	if(et== NULL) {
		 error(ERROR_SERIOUS, "Unknown type %s", (ZItype));
		 nstring_destroy(&istr);
	}
	else if(!entry_is_type(et)) {
		 error(ERROR_SERIOUS, "%s is not a type", (ZItype));
		 nstring_destroy(&istr);
	}
	else {
		typetuple_append((ZIa),typetupleentry_create(&istr, et, (ZIisref)));
	}
	nstring_destroy(&tstr);
	xfree((ZItype));
	xfree((ZIname));
#line 1160 "syntax.c"
		}
		/* END OF ACTION: append-tuple */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIs;
		SID_STRING ZIt;

		switch (CURRENT_TERMINAL) {
		case 8:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRstring_Hplus (&ZIs);
		ZR118 ();
		ZRstring_Hplus (&ZIt);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-trigraph */
		{
#line 314 "syntax.act"

	assert((ZIz) != NULL);
	assert((ZIs) != NULL);
	assert((ZIt) != NULL);

	add_prepass((ZIz), (ZIs), (ZIt));
#line 1203 "syntax.c"
		}
		/* END OF ACTION: make-trigraph */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRcmd(zoneP ZIz, cmdP *ZOinst)
{
	cmdP ZIinst;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		args_listP ZIl;

		/* BEGINNING OF ACTION: empty-args-list */
		{
#line 395 "syntax.act"

    (ZIl)=add_args_list();
#line 1229 "syntax.c"
		}
		/* END OF ACTION: empty-args-list */
		ZR211 (&ZIz, &ZIl, &ZIinst);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZR183(SID_STRING *ZOe)
{
	SID_STRING ZIe;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		ZRnon_Hempty_Hchars (&ZIe);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: E_expected_chars */
		{
#line 872 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1270 "syntax.c"
		}
		/* END OF ACTION: E_expected_chars */
	}
ZL0:;
	*ZOe = ZIe;
}

static void
ZR185(zoneP *ZIz, cmd_listP *ZOleaving_Hinstl)
{
	cmd_listP ZIleaving_Hinstl;

	switch (CURRENT_TERMINAL) {
	case 17:
		{
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIleaving_Hinstl);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-inst-list */
			{
#line 624 "syntax.act"

    (ZIleaving_Hinstl)=add_cmd_list();
#line 1301 "syntax.c"
			}
			/* END OF ACTION: empty-inst-list */
		}
		break;
	case 39:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOleaving_Hinstl = ZIleaving_Hinstl;
}

void
read_lex(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		ZRcommand_Hlist (ZIz);
		/* BEGINNING OF INLINE: 190 */
		{
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case 18:
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
#line 903 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1348 "syntax.c"
				}
				/* END OF ACTION: syntax-error */
			}
		ZL2:;
		}
		/* END OF INLINE: 190 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRaction_Hdecl(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIi;
		typetuple ZIit;
		typetuple ZIot;

		switch (CURRENT_TERMINAL) {
		case 35:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 133 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 36:
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
#line 894 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
#line 1399 "syntax.c"
				}
				/* END OF ACTION: E_expected_begin_action */
			}
		ZL2:;
		}
		/* END OF INLINE: 133 */
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 1413 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 134 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 37:
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
#line 898 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
#line 1440 "syntax.c"
				}
				/* END OF ACTION: E_expected_end_action */
			}
		ZL4:;
		}
		/* END OF INLINE: 134 */
		/* BEGINNING OF INLINE: 135 */
		{
			switch (CURRENT_TERMINAL) {
			case 22:
				{
					ADVANCE_LEXER;
					ZR141 ();
					ZRtype_Htuple (ZIz, &ZIit);
					ZR142 ();
					ZR118 ();
					ZR141 ();
					ZRtype_Htuple (ZIz, &ZIot);
					ZR142 ();
					if ((CURRENT_TERMINAL) == 39) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 808 "syntax.act"

	typetuple_init(&(ZIit));
#line 1473 "syntax.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 808 "syntax.act"

	typetuple_init(&(ZIot));
#line 1481 "syntax.c"
					}
					/* END OF ACTION: init-tuple */
				}
				break;
			}
		}
		/* END OF INLINE: 135 */
		/* BEGINNING OF ACTION: make-action */
		{
#line 784 "syntax.act"

	NStringT str;
	struct entry *e;
	nstring_copy_cstring(&str, (ZIi));
	e = table_get_entry(tree_get_table((ZIz)->ast), &str);
	if(e != NULL) {
		nstring_destroy(&str);
		/* TODO switch ? */
	   	if(entry_is_action(e))
			error(ERROR_SERIOUS, "Action %s already exists",(ZIi));
		else if(entry_is_localname(e))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIi),(ZIi));
		else if(entry_is_type(e))
			error(ERROR_SERIOUS, "Can't create action %s, %s has already been declared as a type",(ZIi), (ZIi));
		else
			UNREACHED;
	} else {
		table_add_action(tree_get_table((ZIz)->ast), &str , (&ZIit), (&ZIot));
	}
	xfree((ZIi));
#line 1512 "syntax.c"
		}
		/* END OF ACTION: make-action */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR207(zoneP ZI201, cmd_listP ZI204, zoneP *ZO205, cmd_listP *ZO206)
{
	zoneP ZI205;
	cmd_listP ZI206;

ZL2_207:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			cmd_listP ZIinstl;
			cmdP ZIinst;

			ZIinstl = ZI204;
			ADVANCE_LEXER;
			ZRcmd (ZI201, &ZIinst);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-inst-to-list */
			{
#line 402 "syntax.act"

	if((ZIinst)!=NULL) { /* if (ZIinst) == NULL, an error has already been issued.*/
		struct LocalNamesT* locals = cmdlist_localnames((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((ZIinst)->type==return_terminal || (ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an cmd-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((ZIinstl)->nb_return_terminal>0 && (ZIinst)->type!=do_nothing)
			error(ERROR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
		if((ZIinst)->type == return_terminal) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == action_call) {
			struct args_list* rhs;
			struct args_list* lhs;
			struct entry *ea;
			struct action *act;
			struct arg* p;
			struct TypeTupleEntryT* q;

			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			ea = (ZIinst)->u.act.called_act;
			act = entry_get_action(ea);
			rhs = (ZIinst)->u.act.rhs;
			lhs = (ZIinst)->u.act.lhs;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = act->in.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	struct entry *et = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.literal);
					et=localnames_get_type(locals, &str);
					nstring_destroy(&str);
					if(!et) {
						struct entry *e = table_get_entry(tree_get_table((ZI201)->ast), &str);
						if(!e) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
							et = NULL;
						} else if (entry_is_localname(e)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
							et = NULL;
						} else if (entry_is_action(e)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
							et = NULL;
						} else if (entry_is_type(e)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
							et = NULL;
						} else {
							UNREACHED;
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(ast)) */
					et = lexer_string_type((ZI201)->ast);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(ast)) */
					et = lexer_char_type((ZI201)->ast);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(ast)) */
					et = lexer_terminal_type((ZI201)->ast);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(ast)) */
					et = lexer_int_type((ZI201)->ast);
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
			if(et) {
				if( q->et!=et || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(ea));
						char* s2 = nstring_to_cstring(entry_key(et));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->et));
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
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
				DEALLOCATE(s);
			}

			for ( p = lhs->head, q = act->out.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	struct entry *et;
				switch (p->type) {
				case arg_identifier: 
					{
						NStringT str;
						nstring_copy_cstring(&str, p->u.literal);
						et = localnames_get_type(locals, &str);
						if(!et) {
							struct entry *e= table_get_entry(tree_get_table((ZI201)->ast), &str);
							localnames_add_nstring(locals, &str, q->et);
							if(e) {
								nstring_destroy(&str);
								if (entry_is_action(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name(tree_get_table((ZI201)->ast), &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								et=q->et; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					et = lexer_terminal_type((ZI201)->ast);
					q->is_reference = false;
					/* TODO assert(q->is_reference == false) */
					break;
				case arg_ignore:
					/*always acceptable */
					et = q->et;
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
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, too many results", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(ea));
				error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
				DEALLOCATE(s);
			}
		}
		/* TODO only append if no error */
		*(ZIinstl)->tail=(ZIinst);
		(ZIinstl)->tail=&(ZIinst)->next;
		++((ZIinstl)->size);
	}
#line 1755 "syntax.c"
			}
			/* END OF ACTION: add-inst-to-list */
			/* BEGINNING OF INLINE: 207 */
			ZI204 = ZIinstl;
			goto ZL2_207;
			/* END OF INLINE: 207 */
		}
		/*UNREACHED*/
	default:
		{
			ZI205 = ZI201;
			ZI206 = ZI204;
		}
		break;
	case 39:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZO205 = ZI205;
	*ZO206 = ZI206;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
ZL2_command_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 6: case 7: case 8: case 9:
	case 12: case 15: case 21: case 35:
	case 38:
		{
			ZRcommand (ZIz);
			/* BEGINNING OF INLINE: command-list */
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_command_Hlist;
			}
			/* END OF INLINE: command-list */
		}
		/*UNREACHED*/
	case 39:
		return;
	default:
		break;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 903 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1815 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZR209(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 1835 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR116 ();
			ZRnon_Hempty_Hchars (&ZIs);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-group */
			{
#line 303 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 1850 "syntax.c"
			}
			/* END OF ACTION: make-group */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 10:
		{
			SID_STRING ZIs;

			ADVANCE_LEXER;
			ZR116 ();
			ZRstring_Hplus (&ZIs);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-white */
			{
#line 289 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 1879 "syntax.c"
			}
			/* END OF ACTION: make-white */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 39:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR210(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 11:
		{
			cmd_listP ZIinst_Hlist;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 17:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-default */
			{
#line 654 "syntax.act"

    (*ZIz)->local=(ZIinst_Hlist);
	if((ZIinst_Hlist)->nb_return_terminal)
		(*ZIz)->type=typezone_general_zone;
#line 1928 "syntax.c"
			}
			/* END OF ACTION: make-default */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 3: case 4: case 5:
		{
			SID_STRING ZIs;
			cmd_listP ZIinst_Hlist;

			ZRnon_Hempty_Hchars (&ZIs);
			switch (CURRENT_TERMINAL) {
			case 17:
				break;
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: check-inst-list */
			{
#line 614 "syntax.act"

	if((ZIinst_Hlist)->nb_return_terminal>1)
		error(ERROR_SERIOUS, "At most one return terminal may be specified per cmd list");
#line 1965 "syntax.c"
			}
			/* END OF ACTION: check-inst-list */
			/* BEGINNING OF ACTION: make-token */
			{
#line 635 "syntax.act"

	add_mainpass((*ZIz), (ZIs), (ZIinst_Hlist));
	if((ZIinst_Hlist)->nb_return_terminal)
		(*ZIz)->type=typezone_general_zone;
#line 1975 "syntax.c"
			}
			/* END OF ACTION: make-token */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 39:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR211(zoneP *ZIz, args_listP *ZIl, cmdP *ZOinst)
{
	cmdP ZIinst;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 241 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 2014 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 2023 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 907 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2031 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2042 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2066 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2080 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2130 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 30:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 237 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 2147 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 2156 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 907 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2164 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2175 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2199 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2213 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2263 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 34:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 253 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 2279 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2291 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2315 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2329 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2379 "syntax.c"
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

			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 245 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 2396 "syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 2405 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 907 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 2413 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2424 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2448 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2462 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2512 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 33:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-return-terminal */
			{
#line 249 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 2528 "syntax.c"
			}
			/* END OF EXTRACT: arg-return-terminal */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2540 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2564 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2578 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2628 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 36:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2646 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2660 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2710 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 0:
		{
			SID_STRING ZI212;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 177 "syntax.act"

    ZI212 = xstrdup ( token_buff ) ;
#line 2727 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_identifier */
			{
#line 734 "syntax.act"

	(ZIa) = add_identifier_arg ((ZI212));
#line 2736 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_identifier */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2747 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2771 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2785 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2835 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 28:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-donothing-inst */
			{
#line 331 "syntax.act"

	(ZIinst)=add_cmd_donothing();
#line 2848 "syntax.c"
			}
			/* END OF ACTION: make-donothing-inst */
		}
		break;
	case 13:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			ZRaction_Hcall_C_Clhs_Htuple1 (*ZIl);
			switch (CURRENT_TERMINAL) {
			case 14:
				break;
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2891 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 2905 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 2955 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 23:
		{
			SID_STRING ZI213;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZI213 = xstrdup ( token_buff ) ;
#line 2975 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_reference */
			{
#line 738 "syntax.act"

	(ZIa) = add_reference_arg ((ZI213));
#line 2988 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_reference */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 2999 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3023 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3037 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 3087 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 1:
		{
			SID_STRING ZI214;

			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 210 "syntax.act"

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
    ZI214 = xstrdup ( buff ) ;
#line 3122 "syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			ZR215 (ZIz, ZIl, &ZI214, &ZIinst);
			if ((CURRENT_TERMINAL) == 39) {
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
#line 222 "syntax.act"

    ZIb = xstrdup ( token_buff ) ;
#line 3145 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 3154 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_arg_in_lhs */
			{
#line 911 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 3162 "syntax.c"
			}
			/* END OF ACTION: E_string_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3173 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 19:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3197 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3211 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 3261 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 39:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZR215(zoneP *ZIz, args_listP *ZIl, SID_STRING *ZI214, cmdP *ZOinst)
{
	cmdP ZIinst;

	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: make-terminal-inst */
			{
#line 327 "syntax.act"

        (ZIinst)=add_cmd_return_terminal((*ZI214));
#line 3292 "syntax.c"
			}
			/* END OF ACTION: make-terminal-inst */
		}
		break;
	case 19:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 3308 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_terminal_in_lhs */
			{
#line 929 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 3316 "syntax.c"
			}
			/* END OF ACTION: E_terminal_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 372 "syntax.act"

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
#line 3327 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3345 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 386 "syntax.act"

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
#line 3359 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 37:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR163 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-inst */
			{
#line 337 "syntax.act"

	NStringT key;
	struct entry *ea;
	nstring_copy_cstring(&key, (ZIi));
	ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
	if(ea) {
		if(entry_is_action(ea)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			struct arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(ea));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_cmd_action(ea,(*ZIl),(ZIr));
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
#line 3409 "syntax.c"
			}
			/* END OF ACTION: make-action-inst */
		}
		break;
	case 39:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOinst = ZIinst;
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIs;
		cmdP ZIinst;

		switch (CURRENT_TERMINAL) {
		case 7:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 222 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 3449 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 17:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcmd (ZIz, &ZIinst);
		/* BEGINNING OF INLINE: 171 */
		{
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 756 "syntax.act"

   (ZI0) = tree_zoneisglobal((ZIz)->ast, (ZIz));
#line 3477 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-keyword */
				{
#line 668 "syntax.act"

    switch((ZIinst)->type) {
    case return_terminal: 
    /* Fallback is intentional */
      add_keyword ( (ZIz), (ZIs), (ZIinst) ) ;
    break;
    default:
      error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
  }
#line 3494 "syntax.c"
				}
				/* END OF ACTION: make-keyword */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
				{
#line 841 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 3507 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonekeyword */
			}
		ZL2:;
		}
		/* END OF INLINE: 171 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR216(argP *ZIa, args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 27:
		{
			ADVANCE_LEXER;
			ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 379 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
#line 3543 "syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 395 "syntax.act"

    (ZIr)=add_args_list();
#line 3555 "syntax.c"
			}
			/* END OF ACTION: empty-args-list */
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 379 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
#line 3566 "syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	case 39:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZR218(zoneP *ZIz, typetuple *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 22:
		{
			ZRtype_Htuple_C_Ctype_Htuple1 (*ZIz, ZIa);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 39:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRcommand(zoneP ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 6:
		{
			ADVANCE_LEXER;
			ZR209 (&ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 15:
		{
			ADVANCE_LEXER;
			ZRcommand_Hlist (ZIz);
			switch (CURRENT_TERMINAL) {
			case 16:
				break;
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 21:
		{
			ADVANCE_LEXER;
		}
		break;
	case 9:
		{
			ADVANCE_LEXER;
			ZR210 (&ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 35:
		{
			ZRaction_Hdecl (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 7:
		{
			ZRkeyword_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			ZRtrigraph_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 38:
		{
			ZRtype_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 12:
		{
			ZRzone_Hdefn (ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 39:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRtype_Htuple_C_Ctype_Htuple1(zoneP ZIz, typetuple *ZIa)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
ZL2_type_Htuple_C_Ctype_Htuple1:;
	{
		ZRtype_Htuple_C_Ctype_Hname (ZIz, ZIa);
		/* BEGINNING OF INLINE: 219 */
		{
			switch (CURRENT_TERMINAL) {
			case 27:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: type-tuple::type-tuple1 */
					goto ZL2_type_Htuple_C_Ctype_Htuple1;
					/* END OF INLINE: type-tuple::type-tuple1 */
				}
				/*UNREACHED*/
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 219 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 13:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 161 */
		{
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 2: case 23:
			case 30: case 31: case 32: case 33:
			case 34:
				{
					ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
					if ((CURRENT_TERMINAL) == 39) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-args-list */
					{
#line 395 "syntax.act"

    (ZIr)=add_args_list();
#line 3783 "syntax.c"
					}
					/* END OF ACTION: empty-args-list */
				}
				break;
			}
		}
		/* END OF INLINE: 161 */
		switch (CURRENT_TERMINAL) {
		case 14:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRnon_Hempty_Hchars(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		ZRstring_Hplus (&ZIs);
		/* BEGINNING OF INLINE: 110 */
		{
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-non-empty */
				{
#line 641 "syntax.act"

	(ZI0) = strlen((ZIs)) > 0;
#line 3829 "syntax.c"
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
#line 646 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 3843 "syntax.c"
				}
				/* END OF ACTION: E_empty_character_string */
			}
		ZL2:;
		}
		/* END OF INLINE: 110 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZR116(void)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 19:
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
#line 890 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 3882 "syntax.c"
		}
		/* END OF ACTION: E_expected_equal */
	}
}

static void
ZR118(void)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 17:
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
#line 886 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 3911 "syntax.c"
		}
		/* END OF ACTION: E_expected_arrow */
	}
}

static void
ZRaction_Hcall_C_Clhs_Harg(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		argP ZIa;

		/* BEGINNING OF INLINE: 148 */
		{
			switch (CURRENT_TERMINAL) {
			case 31:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-nb */
					{
#line 241 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 3938 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-nb */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 3947 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 907 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3955 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 30:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-string */
					{
#line 237 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 3969 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 3978 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 907 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3986 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 34:
				{
					/* BEGINNING OF EXTRACT: arg-ignore */
					{
#line 253 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 3998 "syntax.c"
					}
					/* END OF EXTRACT: arg-ignore */
					ADVANCE_LEXER;
				}
				break;
			case 32:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-nb-of-chars */
					{
#line 245 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 4013 "syntax.c"
					}
					/* END OF EXTRACT: arg-nb-of-chars */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 4022 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 907 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4030 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 33:
				{
					/* BEGINNING OF EXTRACT: arg-return-terminal */
					{
#line 249 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 4042 "syntax.c"
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
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4057 "syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_identifier */
					{
#line 734 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4066 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_identifier */
				}
				break;
			case 23:
				{
					SID_STRING ZIi;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 0:
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4083 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_reference */
					{
#line 738 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4096 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_reference */
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: sid-identifier */
					{
#line 210 "syntax.act"

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
#line 4131 "syntax.c"
					}
					/* END OF EXTRACT: sid-identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 4140 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_terminal_in_lhs */
					{
#line 929 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 4148 "syntax.c"
					}
					/* END OF ACTION: E_terminal_in_lhs */
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: string */
					{
#line 222 "syntax.act"

    ZIb = xstrdup ( token_buff ) ;
#line 4162 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 4171 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_string_arg_in_lhs */
					{
#line 911 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 4179 "syntax.c"
					}
					/* END OF ACTION: E_string_arg_in_lhs */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 148 */
		/* BEGINNING OF ACTION: append-arg-args-list */
		{
#line 372 "syntax.act"

    *(ZIl)->tail=(ZIa);
    (ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(ZIl)->nb_return_terminal++;
#line 4197 "syntax.c"
		}
		/* END OF ACTION: append-arg-args-list */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRaction_Hcall_C_Crhs_Harg(argP *ZOa)
{
	argP ZIa;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 241 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 4220 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
		}
		break;
	case 30:
		{
			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 237 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 4233 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
		}
		break;
	case 34:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 253 "syntax.act"

      ZIb=add_arg(arg_ignore,0);
#line 4248 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 4257 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_ignore_in_rhs */
			{
#line 925 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4265 "syntax.c"
			}
			/* END OF ACTION: E_ignore_in_rhs */
		}
		break;
	case 32:
		{
			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 245 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 4277 "syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
		}
		break;
	case 33:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-return-terminal */
			{
#line 249 "syntax.act"

      ZIb=add_arg(arg_return_terminal,0);
#line 4292 "syntax.c"
			}
			/* END OF EXTRACT: arg-return-terminal */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 4301 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_return_terminal_in_rhs */
			{
#line 915 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4309 "syntax.c"
			}
			/* END OF ACTION: E_return_terminal_in_rhs */
		}
		break;
	case 0:
		{
			SID_STRING ZIi;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4323 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_identifier */
			{
#line 734 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4332 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_identifier */
		}
		break;
	case 23:
		{
			SID_STRING ZIi;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 177 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 4349 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_reference */
			{
#line 738 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4362 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_reference */
		}
		break;
	case 1:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 210 "syntax.act"

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
#line 4397 "syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_terminal */
			{
#line 742 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4406 "syntax.c"
			}
			/* END OF ACTION: make_arg_terminal */
		}
		break;
	case 2:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: string */
			{
#line 222 "syntax.act"

    ZIb = xstrdup ( token_buff ) ;
#line 4420 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 747 "syntax.act"

	(ZIa) = add_none_arg();
#line 4429 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_in_action_rhs */
			{
#line 919 "syntax.act"

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
#line 4437 "syntax.c"
			}
			/* END OF ACTION: E_string_in_action_rhs */
		}
		break;
	case 39:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (39);
	return;
ZL0:;
	*ZOa = ZIa;
}

/* BEGINNING OF TRAILER */

#line 932 "syntax.act"

#line 4459 "syntax.c"

/* END OF FILE */
