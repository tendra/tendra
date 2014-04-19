/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 93 "syntax.act"


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

	typedef char *SID_STRING;
	typedef char *SID_CHARS;
	/*typedef zone* zoneP; Done in syntax.h */
	typedef struct cmd* cmdP;
	typedef struct cmd_list* cmd_listP;
	typedef struct arg* argP;
	typedef struct args_list* args_listP;
	typedef struct TypeTupleT typetuple;

	/*
	 * This string is added to the start of each sid identifier.
	 */
	char *token_prefix = "lex_";

	/*
	 * COMPILATION MODE
	 *
	 * We allow unreached code in the automatically generated sections.
	 */
	#ifdef __TenDRA__
	#pragma TenDRA begin
	#pragma TenDRA unreachable code allow
	#endif

#line 79 "syntax.c"

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
static void ZR162(args_listP *);
static void ZRcmd_Hlist(zoneP, cmd_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, typetuple *);
static void ZR180(SID_STRING *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZRcmd(zoneP, cmdP *);
static void ZR182(zoneP *, cmd_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZR204(zoneP, cmd_listP, zoneP *, cmd_listP *);
static void ZR206(zoneP *);
static void ZR207(zoneP *);
static void ZR208(zoneP *, args_listP *, cmdP *);
static void ZRcommand_Hlist(zoneP);
static void ZR212(zoneP *, args_listP *, SID_STRING *, cmdP *);
static void ZR213(argP *, args_listP *);
static void ZR215(zoneP *, typetuple *);
static void ZRkeyword_Hdefn(zoneP);
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
		/* BEGINNING OF ACTION: E_expected_semicolon */
		{
#line 713 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
	
#line 149 "syntax.c"
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
		cmd_listP ZIentry_Hcmds;
		int ZIlendclosed;
		SID_STRING ZIe;
		cmd_listP ZIexit_Hcmds;
		zoneP ZInew_Hzone;

		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 172 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					/* BEGINNING OF EXTRACT: ident */
					{
#line 135 "syntax.act"

		ZIzid = xstrdup (tokbuf);
	
#line 188 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_expected_ident */
				{
#line 686 "syntax.act"

		(ZIzid)="";
		error(ERROR_SERIOUS, "Syntax error: expected identifier");
	
#line 207 "syntax.c"
				}
				/* END OF ACTION: E_expected_ident */
			}
		ZL2:;
		}
		/* END OF INLINE: 172 */
		/* BEGINNING OF INLINE: 174 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 15:
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
#line 709 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
	
#line 234 "syntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL4:;
		}
		/* END OF INLINE: 174 */
		ZR180 (&ZIb);
		ZR182 (&ZIz, &ZIentry_Hcmds);
		/* BEGINNING OF INLINE: 178 */
		{
			switch (CURRENT_TERMINAL) {
			case 17:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 546 "syntax.act"
 (ZIlendclosed) = 1; 
#line 253 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 18:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 546 "syntax.act"
 (ZIlendclosed) = 1; 
#line 265 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 19:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: false */
					{
#line 547 "syntax.act"
 (ZIlendclosed) = 0; 
#line 277 "syntax.c"
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
#line 692 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected range");
	
#line 297 "syntax.c"
				}
				/* END OF ACTION: E_expected_range */
				/* BEGINNING OF ACTION: false */
				{
#line 547 "syntax.act"
 (ZIlendclosed) = 0; 
#line 304 "syntax.c"
				}
				/* END OF ACTION: false */
			}
		ZL6:;
		}
		/* END OF INLINE: 178 */
		ZR180 (&ZIe);
		ZR182 (&ZIz, &ZIexit_Hcmds);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-zone */
		{
#line 553 "syntax.act"

		struct cmd *c;
		struct cmd_list *l;

		(ZInew_Hzone) = add_zone((ZIz), (ZIzid), (ZIe), (ZIlendclosed));

		(ZInew_Hzone)->exit = (ZIexit_Hcmds);
		if ((ZInew_Hzone)->exit->nb_return) {
			(ZInew_Hzone)->type = typezone_pseudo_token;
		}

		(ZInew_Hzone)->enter = (ZIentry_Hcmds);
		if ((ZInew_Hzone)->enter->nb_return) {
			(ZInew_Hzone)->type = typezone_general_zone;
		}

		c = add_cmd_pushzone((ZInew_Hzone));
		l = add_cmd_list();
		*l->tail = c;
		l->tail = &c->next;

		add_mainpass((ZIz), (ZIb), l);
	
#line 343 "syntax.c"
		}
		/* END OF ACTION: make-zone */
		switch (CURRENT_TERMINAL) {
		case 8:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcommand_Hlist (ZInew_Hzone);
		switch (CURRENT_TERMINAL) {
		case 9:
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
#line 574 "syntax.act"

		switch((ZInew_Hzone)->type) {
		case typezone_pseudo_token:
		case typezone_general_zone:
			(ZIz)->type = typezone_general_zone;
			break;
		case typezone_pure_function:
			break; /* do nothing */

		}
	
#line 378 "syntax.c"
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
		case 6:
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
#line 696 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
	
#line 412 "syntax.c"
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
		/* BEGINNING OF ACTION: E_expected_close */
		{
#line 700 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
	
#line 442 "syntax.c"
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
#line 169 "syntax.act"
 ZIa = "0123456789";                 
#line 468 "syntax.c"
					}
					/* END OF EXTRACT: digit */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: lower */
					{
#line 168 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz"; 
#line 480 "syntax.c"
					}
					/* END OF EXTRACT: lower */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: string */
					{
#line 164 "syntax.act"

		ZIa = xstrdup (tokbuf);
	
#line 494 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: upper */
					{
#line 167 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
#line 506 "syntax.c"
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
			case 13:
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
#line 194 "syntax.act"

		(ZIs) = xstrcat ((ZIa), (ZIb));
	
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
		case 30:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 135 "syntax.act"

		ZIs = xstrdup (tokbuf);
	
#line 582 "syntax.c"
			}
			/* END OF EXTRACT: ident */
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
#line 603 "syntax.act"

	   (ZI0) = tree_zoneisglobal((ZIz)->ast, (ZIz));
	
#line 599 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-type */
				{
#line 609 "syntax.act"

		NStringT str;
		struct entry *e;
		nstring_copy_cstring(&str,(ZIs));
		xfree((ZIs));
		e = table_get_entry(tree_get_table((ZIz)->ast), &str);
		if (e != NULL) {
			nstring_destroy(&str);
			/* TODO switch ? */
			if (entry_is_type(e)) {
				error(ERROR_SERIOUS, "Type %s already exists",(ZIs));
			} else if (entry_is_localname(e)) {
				error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIs),(ZIs));
			} else if (entry_is_action(e)) {
				error(ERROR_SERIOUS, "Can't create type %s, %s has already been declared as an action",(ZIs), (ZIs));
			} else {
				UNREACHED;
			}
		} else {
			table_add_type(tree_get_table((ZIz)->ast), &str, false);
		}
	
#line 629 "syntax.c"
				}
				/* END OF ACTION: make-type */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonetype */
				{
#line 682 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs));
	
#line 642 "syntax.c"
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
		/* BEGINNING OF INLINE: 214 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
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
		/* END OF INLINE: 214 */
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
#line 653 "syntax.act"

		typetuple_init(&(ZIa));
	
#line 706 "syntax.c"
		}
		/* END OF ACTION: init-tuple */
		ZR215 (&ZIz, &ZIa);
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
#line 129 "syntax.act"

		typetuple_assign(ZOa, (&ZIa));
	#line 725 "syntax.c"
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
		ZR213 (&ZIa, &ZIr);
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
ZR162(args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 6:
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
#line 282 "syntax.act"

		(ZIr)=add_args_list();
	
#line 779 "syntax.c"
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
ZRcmd_Hlist(zoneP ZI198, cmd_listP *ZO203)
{
	cmd_listP ZI203;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		cmdP ZIc;
		cmd_listP ZIl;
		zoneP ZI202;

		ZRcmd (ZI198, &ZIc);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: empty-cmd-list */
		{
#line 505 "syntax.act"

		(ZIl) = add_cmd_list();
	
#line 819 "syntax.c"
		}
		/* END OF ACTION: empty-cmd-list */
		/* BEGINNING OF ACTION: add-cmd-to-list */
		{
#line 286 "syntax.act"

		if ((ZIc) != NULL) { /* if (ZIc) == NULL, an error has already been issued.*/
			struct LocalNamesT* locals = cmdlist_localnames((ZIl));
	/*		if (((ZIl)->head !=NULL) && ((ZIc)->type==return_terminal || (ZIc)->type==do_nothing)) {
				error(ERROR_SERIOUS, "A $sid-ident or a $$ can only appear at the end of an cmd-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
			}*/
			if ((ZIl)->nb_return > 0 && (ZIc)->type!=do_nothing)
				error(ERROR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
			if ((ZIc)->type == return_terminal) {
				++((ZIl)->nb_return);
			}
			if ((ZIc)->type == action_call) {
				struct args_list* rhs;
				struct args_list* lhs;
				struct entry *ea;
				struct action *act;
				struct arg* p;
				struct TypeTupleEntryT* q;

				(ZIl)->nb_return+=(ZIc)->u.act.lhs->nb_return;
				if ((ZIl)->nb_return>1)
					error(ERROR_SERIOUS, "Only one terminal may be returned per token");
				ea = (ZIc)->u.act.called_act;
				act = entry_get_action(ea);
				rhs = (ZIc)->u.act.rhs;
				lhs = (ZIc)->u.act.lhs;

				/* CHECKING RHS COMPATIBILITY */ 
				for (p = rhs->head, q = act->in.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
						struct entry *et = NULL;
					NStringT str;
						switch (p->type) {
					case arg_ident:
							nstring_copy_cstring(&str, p->u.literal);
						et=localnames_get_type(locals, &str);
						nstring_destroy(&str);
						if (!et) {
							struct entry *e = table_get_entry(tree_get_table((ZI198)->ast), &str);
							if (!e) {
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
						et = lexer_string_type((ZI198)->ast);
						break;
					case arg_char_nb:
						/* TODO assert(lexer_char_type(ast)) */
						et = lexer_char_type((ZI198)->ast);
						break;
					case arg_terminal:
						/* TODO assert(lexer_terminal_type(ast)) */
						et = lexer_terminal_type((ZI198)->ast);
						break;
					case arg_nb_of_chars:
						/* TODO assert(lexer_terminal_type(ast)) */
						et = lexer_int_type((ZI198)->ast);
						break;
					case arg_none:
						break; /* Error already detected, do nothing and leave p->lexitype = NULL */
					case arg_ignore:
					case arg_return:
						UNREACHED;
					break;
				default:
					UNREACHED;
					break;
				}
				if (et) {
					if (q->et!=et || p->is_ref !=q->is_ref) {
							char* s1 = nstring_to_cstring(entry_key(ea));
							char* s2 = nstring_to_cstring(entry_key(et));
							char* s3 = p->is_ref ? "&" : "";
							char* s4 = nstring_to_cstring(entry_key(q->et));
							char* s5 = q->is_ref ? "&" : "";
							char* s6 = "unknown";
							char* s7 = "unknown";
							switch(p->type) {
							case arg_terminal:
								s6 = "$"; 
								s7 = p->u.literal;
								break;
							case arg_ident:
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
				if (p!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
					DEALLOCATE(s);
				}
				if (q!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
					DEALLOCATE(s);
				}

				for (p = lhs->head, q = act->out.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
						struct entry *et;
					switch (p->type) {
					case arg_ident: 
						{
							NStringT str;
							nstring_copy_cstring(&str, p->u.literal);
							et = localnames_get_type(locals, &str);
							if (!et) {
								struct entry *e= table_get_entry(tree_get_table((ZI198)->ast), &str);
								localnames_add_nstring(locals, &str, q->et);
								if (e) {
									nstring_destroy(&str);
									if (entry_is_action(e)) {
										error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
									} else if (entry_is_type(e)) {
										error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);
									}
								} else {
									table_add_local_name(tree_get_table((ZI198)->ast), &str);
								}
								if (p->is_ref) {
									char* s = nstring_to_cstring(entry_key(ea));
									error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
									DEALLOCATE(s);
								}
							} else {
								nstring_destroy(&str);
								if (!p->is_ref) {
									char* s = nstring_to_cstring(entry_key(ea));
									error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
									et=q->et; /* To avoid outputting that error more than once*/
									DEALLOCATE(s);
								}
							}
						}
						break;
					case arg_return:
						et = lexer_terminal_type((ZI198)->ast);
						q->is_ref = false;
						/* TODO assert(q->is_ref == false) */
						break;
					case arg_ignore:
						/*always acceptable */
						et = q->et;
						p->is_ref = q->is_ref;
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
					if (p->is_ref != q->is_ref) {
						/* XXX: state which action */
						if (p->is_ref) {
							error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						} else {
							error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						}
					}
				}
				if (p!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many results", s);
					DEALLOCATE(s);
				}
				if (q!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
					DEALLOCATE(s);
				}
			}
			/* TODO only append if no error */
			*(ZIl)->tail=(ZIc);
			(ZIl)->tail=&(ZIc)->next;
			(ZIl)->size++;
		}
	
#line 1037 "syntax.c"
		}
		/* END OF ACTION: add-cmd-to-list */
		ZR204 (ZI198, ZIl, &ZI202, &ZI203);
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
	*ZO203 = ZI203;
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
					/* BEGINNING OF EXTRACT: ident */
					{
#line 135 "syntax.act"

		ZIname = xstrdup (tokbuf);
	
#line 1076 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-ident */
					{
#line 198 "syntax.act"

		(ZIname) = xstrdup("");
	
#line 1090 "syntax.c"
					}
					/* END OF ACTION: empty-ident */
				}
				break;
			}
		}
		/* END OF INLINE: 125 */
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 135 "syntax.act"

		ZItype = xstrdup (tokbuf);
	
#line 1113 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 128 */
		{
			switch (CURRENT_TERMINAL) {
			case 16:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 546 "syntax.act"
 (ZIisref) = 1; 
#line 1131 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 547 "syntax.act"
 (ZIisref) = 0; 
#line 1142 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 128 */
		/* BEGINNING OF ACTION: append-tuple */
		{
#line 659 "syntax.act"

		struct entry *et;
		NStringT tstr, istr;
		nstring_copy_cstring(&tstr,(ZItype));
		nstring_copy_cstring(&istr,(ZIname));
		et = table_get_entry(tree_get_table((ZIz)->ast), &tstr);
		if (et== NULL) {
			 error(ERROR_SERIOUS, "Unknown type %s", (ZItype));
			 nstring_destroy(&istr);
		} else if (!entry_is_type(et)) {
			 error(ERROR_SERIOUS, "%s is not a type", (ZItype));
			 nstring_destroy(&istr);
		} else {
			typetuple_append((ZIa),typetupleentry_create(&istr, et, (ZIisref)));
		}
		nstring_destroy(&tstr);
		xfree((ZItype));
		xfree((ZIname));
	
#line 1172 "syntax.c"
		}
		/* END OF ACTION: append-tuple */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR180(SID_STRING *ZOe)
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
#line 703 "syntax.act"

			(ZIe) = NULL;
		error(ERROR_SERIOUS, "Syntax error: expected characters");
	
#line 1207 "syntax.c"
		}
		/* END OF ACTION: E_expected_chars */
	}
ZL0:;
	*ZOe = ZIe;
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
		case 34:
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
#line 213 "syntax.act"

		assert((ZIz) != NULL);
		assert((ZIs) != NULL);
		assert((ZIt) != NULL);

		add_prepass((ZIz), (ZIs), (ZIt));
	
#line 1249 "syntax.c"
		}
		/* END OF ACTION: make-trigraph */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZRcmd(zoneP ZIz, cmdP *ZOc)
{
	cmdP ZIc;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		args_listP ZIl;

		/* BEGINNING OF ACTION: empty-args-list */
		{
#line 282 "syntax.act"

		(ZIl)=add_args_list();
	
#line 1276 "syntax.c"
		}
		/* END OF ACTION: empty-args-list */
		ZR208 (&ZIz, &ZIl, &ZIc);
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
	*ZOc = ZIc;
}

static void
ZR182(zoneP *ZIz, cmd_listP *ZOexit_Hcmds)
{
	cmd_listP ZIexit_Hcmds;

	switch (CURRENT_TERMINAL) {
	case 10:
		{
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIexit_Hcmds);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-cmd-list */
			{
#line 505 "syntax.act"

		(ZIexit_Hcmds) = add_cmd_list();
	
#line 1317 "syntax.c"
			}
			/* END OF ACTION: empty-cmd-list */
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
	*ZOexit_Hcmds = ZIexit_Hcmds;
}

void
read_lex(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		ZRcommand_Hlist (ZIz);
		/* BEGINNING OF INLINE: 187 */
		{
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case 11:
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
#line 734 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 1365 "syntax.c"
				}
				/* END OF ACTION: syntax-error */
			}
		ZL2:;
		}
		/* END OF INLINE: 187 */
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
		case 32:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 133 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 28:
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
#line 725 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
	
#line 1417 "syntax.c"
				}
				/* END OF ACTION: E_expected_begin_action */
			}
		ZL2:;
		}
		/* END OF INLINE: 133 */
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: ident */
			{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 1432 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 134 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 29:
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
#line 729 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
	
#line 1460 "syntax.c"
				}
				/* END OF ACTION: E_expected_end_action */
			}
		ZL4:;
		}
		/* END OF INLINE: 134 */
		/* BEGINNING OF INLINE: 135 */
		{
			switch (CURRENT_TERMINAL) {
			case 15:
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
#line 653 "syntax.act"

		typetuple_init(&(ZIit));
	
#line 1494 "syntax.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 653 "syntax.act"

		typetuple_init(&(ZIot));
	
#line 1503 "syntax.c"
					}
					/* END OF ACTION: init-tuple */
				}
				break;
			}
		}
		/* END OF INLINE: 135 */
		/* BEGINNING OF ACTION: make-action */
		{
#line 632 "syntax.act"

		NStringT str;
		struct entry *e;
		nstring_copy_cstring(&str, (ZIi));
		e = table_get_entry(tree_get_table((ZIz)->ast), &str);
		if (e != NULL) {
			nstring_destroy(&str);
			/* TODO switch ? */
			if (entry_is_action(e)) {
				error(ERROR_SERIOUS, "Action %s already exists",(ZIi));
			} else if (entry_is_localname(e)) {
				error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIi),(ZIi));
			} else if (entry_is_type(e)) {
				error(ERROR_SERIOUS, "Can't create action %s, %s has already been declared as a type",(ZIi), (ZIi));
			} else {
				UNREACHED;
			}
		} else {
			table_add_action(tree_get_table((ZIz)->ast), &str , (&ZIit), (&ZIot));
		}
		xfree((ZIi));
	
#line 1536 "syntax.c"
		}
		/* END OF ACTION: make-action */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR204(zoneP ZI198, cmd_listP ZI201, zoneP *ZO202, cmd_listP *ZO203)
{
	zoneP ZI202;
	cmd_listP ZI203;

ZL2_204:;
	switch (CURRENT_TERMINAL) {
	case 20:
		{
			cmd_listP ZIl;
			cmdP ZIc;

			ZIl = ZI201;
			ADVANCE_LEXER;
			ZRcmd (ZI198, &ZIc);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-cmd-to-list */
			{
#line 286 "syntax.act"

		if ((ZIc) != NULL) { /* if (ZIc) == NULL, an error has already been issued.*/
			struct LocalNamesT* locals = cmdlist_localnames((ZIl));
	/*		if (((ZIl)->head !=NULL) && ((ZIc)->type==return_terminal || (ZIc)->type==do_nothing)) {
				error(ERROR_SERIOUS, "A $sid-ident or a $$ can only appear at the end of an cmd-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
			}*/
			if ((ZIl)->nb_return > 0 && (ZIc)->type!=do_nothing)
				error(ERROR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
			if ((ZIc)->type == return_terminal) {
				++((ZIl)->nb_return);
			}
			if ((ZIc)->type == action_call) {
				struct args_list* rhs;
				struct args_list* lhs;
				struct entry *ea;
				struct action *act;
				struct arg* p;
				struct TypeTupleEntryT* q;

				(ZIl)->nb_return+=(ZIc)->u.act.lhs->nb_return;
				if ((ZIl)->nb_return>1)
					error(ERROR_SERIOUS, "Only one terminal may be returned per token");
				ea = (ZIc)->u.act.called_act;
				act = entry_get_action(ea);
				rhs = (ZIc)->u.act.rhs;
				lhs = (ZIc)->u.act.lhs;

				/* CHECKING RHS COMPATIBILITY */ 
				for (p = rhs->head, q = act->in.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
						struct entry *et = NULL;
					NStringT str;
						switch (p->type) {
					case arg_ident:
							nstring_copy_cstring(&str, p->u.literal);
						et=localnames_get_type(locals, &str);
						nstring_destroy(&str);
						if (!et) {
							struct entry *e = table_get_entry(tree_get_table((ZI198)->ast), &str);
							if (!e) {
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
						et = lexer_string_type((ZI198)->ast);
						break;
					case arg_char_nb:
						/* TODO assert(lexer_char_type(ast)) */
						et = lexer_char_type((ZI198)->ast);
						break;
					case arg_terminal:
						/* TODO assert(lexer_terminal_type(ast)) */
						et = lexer_terminal_type((ZI198)->ast);
						break;
					case arg_nb_of_chars:
						/* TODO assert(lexer_terminal_type(ast)) */
						et = lexer_int_type((ZI198)->ast);
						break;
					case arg_none:
						break; /* Error already detected, do nothing and leave p->lexitype = NULL */
					case arg_ignore:
					case arg_return:
						UNREACHED;
					break;
				default:
					UNREACHED;
					break;
				}
				if (et) {
					if (q->et!=et || p->is_ref !=q->is_ref) {
							char* s1 = nstring_to_cstring(entry_key(ea));
							char* s2 = nstring_to_cstring(entry_key(et));
							char* s3 = p->is_ref ? "&" : "";
							char* s4 = nstring_to_cstring(entry_key(q->et));
							char* s5 = q->is_ref ? "&" : "";
							char* s6 = "unknown";
							char* s7 = "unknown";
							switch(p->type) {
							case arg_terminal:
								s6 = "$"; 
								s7 = p->u.literal;
								break;
							case arg_ident:
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
				if (p!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
					DEALLOCATE(s);
				}
				if (q!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
					DEALLOCATE(s);
				}

				for (p = lhs->head, q = act->out.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
						struct entry *et;
					switch (p->type) {
					case arg_ident: 
						{
							NStringT str;
							nstring_copy_cstring(&str, p->u.literal);
							et = localnames_get_type(locals, &str);
							if (!et) {
								struct entry *e= table_get_entry(tree_get_table((ZI198)->ast), &str);
								localnames_add_nstring(locals, &str, q->et);
								if (e) {
									nstring_destroy(&str);
									if (entry_is_action(e)) {
										error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
									} else if (entry_is_type(e)) {
										error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);
									}
								} else {
									table_add_local_name(tree_get_table((ZI198)->ast), &str);
								}
								if (p->is_ref) {
									char* s = nstring_to_cstring(entry_key(ea));
									error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
									DEALLOCATE(s);
								}
							} else {
								nstring_destroy(&str);
								if (!p->is_ref) {
									char* s = nstring_to_cstring(entry_key(ea));
									error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
									et=q->et; /* To avoid outputting that error more than once*/
									DEALLOCATE(s);
								}
							}
						}
						break;
					case arg_return:
						et = lexer_terminal_type((ZI198)->ast);
						q->is_ref = false;
						/* TODO assert(q->is_ref == false) */
						break;
					case arg_ignore:
						/*always acceptable */
						et = q->et;
						p->is_ref = q->is_ref;
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
					if (p->is_ref != q->is_ref) {
						/* XXX: state which action */
						if (p->is_ref) {
							error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						} else {
							error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						}
					}
				}
				if (p!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many results", s);
					DEALLOCATE(s);
				}
				if (q!=NULL) {
					char* s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
					DEALLOCATE(s);
				}
			}
			/* TODO only append if no error */
			*(ZIl)->tail=(ZIc);
			(ZIl)->tail=&(ZIc)->next;
			(ZIl)->size++;
		}
	
#line 1781 "syntax.c"
			}
			/* END OF ACTION: add-cmd-to-list */
			/* BEGINNING OF INLINE: 204 */
			ZI201 = ZIl;
			goto ZL2_204;
			/* END OF INLINE: 204 */
		}
		/*UNREACHED*/
	default:
		{
			ZI202 = ZI198;
			ZI203 = ZI201;
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
	*ZO202 = ZI202;
	*ZO203 = ZI203;
}

static void
ZR206(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 1823 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			ZR116 ();
			ZRnon_Hempty_Hchars (&ZIs);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-group */
			{
#line 209 "syntax.act"

		make_group ((*ZIz), (ZIi), (ZIs));
	
#line 1839 "syntax.c"
			}
			/* END OF ACTION: make-group */
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 38:
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
#line 202 "syntax.act"

		if ((*ZIz)->white_space) {
			error (ERROR_SERIOUS, "White space group already defined");
		}
		(*ZIz)->white_space = make_group((*ZIz), "white", (ZIs));
	
#line 1869 "syntax.c"
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
ZR207(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 37:
		{
			cmd_listP ZIl;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 10:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIl);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-default */
			{
#line 530 "syntax.act"

		(*ZIz)->local=(ZIl);
		if ((ZIl)->nb_return)
			(*ZIz)->type=typezone_general_zone;
	
#line 1919 "syntax.c"
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
			cmd_listP ZIl;

			ZRnon_Hempty_Hchars (&ZIs);
			switch (CURRENT_TERMINAL) {
			case 10:
				break;
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIl);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: check-cmd-list */
			{
#line 499 "syntax.act"

		if ((ZIl)->nb_return > 1) {
			error(ERROR_SERIOUS, "At most one return terminal may be specified per command list");
		}
	
#line 1958 "syntax.c"
			}
			/* END OF ACTION: check-cmd-list */
			/* BEGINNING OF ACTION: make-token */
			{
#line 516 "syntax.act"

		add_mainpass((*ZIz), (ZIs), (ZIl));
		if ((ZIl)->nb_return)
			(*ZIz)->type=typezone_general_zone;
	
#line 1969 "syntax.c"
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
ZR208(zoneP *ZIz, args_listP *ZIl, cmdP *ZOc)
{
	cmdP ZIc;

	switch (CURRENT_TERMINAL) {
	case 24:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 176 "syntax.act"

		  ZIb = add_arg(arg_char_nb, numbuf);
	
#line 2009 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 2019 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 738 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2028 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 2040 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2065 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2080 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2131 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 23:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 172 "syntax.act"

		  ZIb = add_arg(arg_charP, 0);
	
#line 2149 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 2159 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 738 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2168 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 2180 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2205 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2220 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2271 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 27:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 188 "syntax.act"

		  ZIa = add_arg(arg_ignore ,0);
	
#line 2288 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 2301 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2326 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2341 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2392 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 25:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 180 "syntax.act"

		  ZIb = add_arg(arg_nb_of_chars, 0);
	
#line 2410 "syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 2420 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 738 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2429 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 2441 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2466 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2481 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2532 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 26:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-return */
			{
#line 184 "syntax.act"

		  ZIa = add_arg(arg_return, 0);
	
#line 2549 "syntax.c"
			}
			/* END OF EXTRACT: arg-return */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 2562 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2587 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2602 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2653 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 28:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2672 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2687 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2738 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 0:
		{
			SID_STRING ZI209;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 135 "syntax.act"

		ZI209 = xstrdup (tokbuf);
	
#line 2756 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ident */
			{
#line 586 "syntax.act"

		(ZIa) = add_ident((ZI209));
	
#line 2766 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ident */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 2778 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2803 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2818 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2869 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-donothing-cmd */
			{
#line 225 "syntax.act"

		(ZIc) = add_cmd_donothing();
	
#line 2883 "syntax.c"
			}
			/* END OF ACTION: make-donothing-cmd */
		}
		break;
	case 6:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			ZRaction_Hcall_C_Clhs_Htuple1 (*ZIl);
			switch (CURRENT_TERMINAL) {
			case 7:
				break;
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2927 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 2942 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 2993 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 16:
		{
			SID_STRING ZI210;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZI210 = xstrdup (tokbuf);
	
#line 3014 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ref */
			{
#line 590 "syntax.act"

		(ZIa) = add_ref((ZI210));
	
#line 3028 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ref */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 3040 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3065 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 3080 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 3131 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 1:
		{
			SID_STRING ZI211;

			/* BEGINNING OF EXTRACT: sid-ident */
			{
#line 160 "syntax.act"

		int n;
		char *s;
		char buf[1000];
		strcpy (buf, token_prefix);
		n = (int) strlen (buf);
		for (s = tokbuf; *s; s++) {
			if (*s == '-') {
				buf[n++] = '_';
				buf[n++] = 'H';
			} else if (*s == '_') {
				buf[n++] = '_';
				buf[n++] = '_';
			} else {
				buf[n++] = *s;
			}
			if (n >= 900) {
				error (ERROR_SERIOUS, "Identifier too long");
				break;
			}
		}
		buf[n] = 0;
		ZI211 = xstrdup(buf);
	
#line 3167 "syntax.c"
			}
			/* END OF EXTRACT: sid-ident */
			ADVANCE_LEXER;
			ZR212 (ZIz, ZIl, &ZI211, &ZIc);
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
#line 164 "syntax.act"

		ZIb = xstrdup (tokbuf);
	
#line 3191 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 3201 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_arg_in_lhs */
			{
#line 742 "syntax.act"

		error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
	
#line 3210 "syntax.c"
			}
			/* END OF ACTION: E_string_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 3222 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			switch (CURRENT_TERMINAL) {
			case 12:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3247 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 3262 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 3313 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
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
	*ZOc = ZIc;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
ZL2_command_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 8: case 14: case 30: case 31:
	case 32: case 33: case 34: case 35:
	case 36:
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
#line 734 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 3365 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZR212(zoneP *ZIz, args_listP *ZIl, SID_STRING *ZI211, cmdP *ZOc)
{
	cmdP ZIc;

	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: make-terminal-cmd */
			{
#line 221 "syntax.act"

			(ZIc) = add_cmd_return((*ZI211));
	
#line 3385 "syntax.c"
			}
			/* END OF ACTION: make-terminal-cmd */
		}
		break;
	case 12:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 3402 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_terminal_in_lhs */
			{
#line 759 "syntax.act"

		error(ERROR_SERIOUS, "Terminal argument in left handside");
	
#line 3411 "syntax.c"
			}
			/* END OF ACTION: E_terminal_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 263 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(*ZIl)->nb_return++;
	
#line 3423 "syntax.c"
			}
			/* END OF ACTION: append-arg-args-list */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 28:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3442 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 277 "syntax.act"

		if ((*ZIl)->nb_return>1)
		error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
	
#line 3457 "syntax.c"
			}
			/* END OF ACTION: check-args-list */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR162 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-action-cmd */
			{
#line 231 "syntax.act"

		NStringT key;
		struct entry *ea;
		nstring_copy_cstring(&key, (ZIi));
		ea = table_get_entry(tree_get_table((*ZIz)->ast), &key);
		if (ea) {
			if (entry_is_action(ea)) {
				/* TODO: Inefficient code follows: */
				/* Checking that a name does not appear twice in an lhs*/
				struct arg* p, *q;
				for(p=(*ZIl)->head;p!=NULL;p=p->next) {
					if (p->type==arg_ident) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->type==arg_ident && !strcmp(p->u.literal, q->u.literal)) {
								char* s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
								break;
							}
						}
					}
				}
				(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
			 /* END Inefficient code*/
			} else {
				(ZIc) = NULL;
				error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
			}
		} else {
			(ZIc) = NULL;
			error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
		}
		xfree((ZIi));
	
#line 3508 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
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
	*ZOc = ZIc;
}

static void
ZR213(argP *ZIa, args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 20:
		{
			ADVANCE_LEXER;
			ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 270 "syntax.act"

		(*ZIa)->next=(ZIr)->head;
		(ZIr)->head=(*ZIa);
		if ((*ZIa)->type==arg_return)
		(ZIr)->nb_return++;
	
#line 3547 "syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 282 "syntax.act"

		(ZIr)=add_args_list();
	
#line 3560 "syntax.c"
			}
			/* END OF ACTION: empty-args-list */
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 270 "syntax.act"

		(*ZIa)->next=(ZIr)->head;
		(ZIr)->head=(*ZIa);
		if ((*ZIa)->type==arg_return)
		(ZIr)->nb_return++;
	
#line 3572 "syntax.c"
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
ZR215(zoneP *ZIz, typetuple *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 15:
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
ZRkeyword_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		SID_STRING ZIs;
		cmdP ZIc;

		switch (CURRENT_TERMINAL) {
		case 33:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 164 "syntax.act"

		ZIs = xstrdup (tokbuf);
	
#line 3637 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 10:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcmd (ZIz, &ZIc);
		/* BEGINNING OF INLINE: 168 */
		{
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 603 "syntax.act"

	   (ZI0) = tree_zoneisglobal((ZIz)->ast, (ZIz));
	
#line 3666 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-keyword */
				{
#line 536 "syntax.act"

		switch((ZIc)->type) {
		case return_terminal:
		/* Fallback is intentional */
		  add_keyword ((ZIz), (ZIs), (ZIc));
		break;
		default:
		  error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
	  }
	
#line 3684 "syntax.c"
				}
				/* END OF ACTION: make-keyword */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
				{
#line 679 "syntax.act"

		error(ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ");

	
#line 3698 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonekeyword */
			}
		ZL2:;
		}
		/* END OF INLINE: 168 */
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
	case 31:
		{
			ADVANCE_LEXER;
			ZR206 (&ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 35:
		{
			ADVANCE_LEXER;
			ZR207 (&ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			ADVANCE_LEXER;
			ZRcommand_Hlist (ZIz);
			switch (CURRENT_TERMINAL) {
			case 9:
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
	case 14:
		{
			ADVANCE_LEXER;
		}
		break;
	case 32:
		{
			ZRaction_Hdecl (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 33:
		{
			ZRkeyword_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 34:
		{
			ZRtrigraph_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 30:
		{
			ZRtype_Hdefn (ZIz);
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 36:
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
		/* BEGINNING OF INLINE: 216 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
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
		/* END OF INLINE: 216 */
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
		case 6:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 160 */
		{
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 2: case 16:
			case 23: case 24: case 25: case 26:
			case 27:
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
#line 282 "syntax.act"

		(ZIr)=add_args_list();
	
#line 3890 "syntax.c"
					}
					/* END OF ACTION: empty-args-list */
				}
				break;
			}
		}
		/* END OF INLINE: 160 */
		switch (CURRENT_TERMINAL) {
		case 7:
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
#line 522 "syntax.act"

		(ZI0) = strlen((ZIs)) > 0;
	
#line 3937 "syntax.c"
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
#line 527 "syntax.act"

			error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
	
#line 3952 "syntax.c"
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
		case 12:
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
#line 721 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
	
#line 3992 "syntax.c"
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
		/* BEGINNING OF ACTION: E_expected_arrow */
		{
#line 717 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
	
#line 4022 "syntax.c"
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
			case 24:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-nb */
					{
#line 176 "syntax.act"

		  ZIb = add_arg(arg_char_nb, numbuf);
	
#line 4050 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-nb */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4060 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 738 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4069 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 23:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-string */
					{
#line 172 "syntax.act"

		  ZIb = add_arg(arg_charP, 0);
	
#line 4084 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4094 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 738 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4103 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 27:
				{
					/* BEGINNING OF EXTRACT: arg-ignore */
					{
#line 188 "syntax.act"

		  ZIa = add_arg(arg_ignore ,0);
	
#line 4116 "syntax.c"
					}
					/* END OF EXTRACT: arg-ignore */
					ADVANCE_LEXER;
				}
				break;
			case 25:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-nb-of-chars */
					{
#line 180 "syntax.act"

		  ZIb = add_arg(arg_nb_of_chars, 0);
	
#line 4132 "syntax.c"
					}
					/* END OF EXTRACT: arg-nb-of-chars */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4142 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 738 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4151 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 26:
				{
					/* BEGINNING OF EXTRACT: arg-return */
					{
#line 184 "syntax.act"

		  ZIa = add_arg(arg_return, 0);
	
#line 4164 "syntax.c"
					}
					/* END OF EXTRACT: arg-return */
					ADVANCE_LEXER;
				}
				break;
			case 0:
				{
					SID_STRING ZIi;

					/* BEGINNING OF EXTRACT: ident */
					{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4180 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_ident */
					{
#line 586 "syntax.act"

		(ZIa) = add_ident((ZIi));
	
#line 4190 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_ident */
				}
				break;
			case 16:
				{
					SID_STRING ZIi;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 0:
						/* BEGINNING OF EXTRACT: ident */
						{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4208 "syntax.c"
						}
						/* END OF EXTRACT: ident */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_ref */
					{
#line 590 "syntax.act"

		(ZIa) = add_ref((ZIi));
	
#line 4222 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_ref */
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: sid-ident */
					{
#line 160 "syntax.act"

		int n;
		char *s;
		char buf[1000];
		strcpy (buf, token_prefix);
		n = (int) strlen (buf);
		for (s = tokbuf; *s; s++) {
			if (*s == '-') {
				buf[n++] = '_';
				buf[n++] = 'H';
			} else if (*s == '_') {
				buf[n++] = '_';
				buf[n++] = '_';
			} else {
				buf[n++] = *s;
			}
			if (n >= 900) {
				error (ERROR_SERIOUS, "Identifier too long");
				break;
			}
		}
		buf[n] = 0;
		ZIb = xstrdup(buf);
	
#line 4258 "syntax.c"
					}
					/* END OF EXTRACT: sid-ident */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4268 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_terminal_in_lhs */
					{
#line 759 "syntax.act"

		error(ERROR_SERIOUS, "Terminal argument in left handside");
	
#line 4277 "syntax.c"
					}
					/* END OF ACTION: E_terminal_in_lhs */
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: string */
					{
#line 164 "syntax.act"

		ZIb = xstrdup (tokbuf);
	
#line 4292 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4302 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_string_arg_in_lhs */
					{
#line 742 "syntax.act"

		error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
	
#line 4311 "syntax.c"
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
#line 263 "syntax.act"

		*(ZIl)->tail=(ZIa);
		(ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->type==arg_return)
		(ZIl)->nb_return++;
	
#line 4330 "syntax.c"
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
	case 24:
		{
			/* BEGINNING OF EXTRACT: arg-char-nb */
			{
#line 176 "syntax.act"

		  ZIa = add_arg(arg_char_nb, numbuf);
	
#line 4354 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-nb */
			ADVANCE_LEXER;
		}
		break;
	case 23:
		{
			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 172 "syntax.act"

		  ZIa = add_arg(arg_charP, 0);
	
#line 4368 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
		}
		break;
	case 27:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 188 "syntax.act"

		  ZIb = add_arg(arg_ignore ,0);
	
#line 4384 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4394 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_ignore_in_rhs */
			{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Ignore argument in right handside");
	
#line 4403 "syntax.c"
			}
			/* END OF ACTION: E_ignore_in_rhs */
		}
		break;
	case 25:
		{
			/* BEGINNING OF EXTRACT: arg-nb-of-chars */
			{
#line 180 "syntax.act"

		  ZIa = add_arg(arg_nb_of_chars, 0);
	
#line 4416 "syntax.c"
			}
			/* END OF EXTRACT: arg-nb-of-chars */
			ADVANCE_LEXER;
		}
		break;
	case 26:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-return */
			{
#line 184 "syntax.act"

		  ZIb = add_arg(arg_return, 0);
	
#line 4432 "syntax.c"
			}
			/* END OF EXTRACT: arg-return */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4442 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_return_in_rhs */
			{
#line 746 "syntax.act"

		error(ERROR_SERIOUS, "Return terminal argument in right handside");
	
#line 4451 "syntax.c"
			}
			/* END OF ACTION: E_return_in_rhs */
		}
		break;
	case 0:
		{
			SID_STRING ZIi;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4466 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ident */
			{
#line 586 "syntax.act"

		(ZIa) = add_ident((ZIi));
	
#line 4476 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ident */
		}
		break;
	case 16:
		{
			SID_STRING ZIi;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 135 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4494 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ref */
			{
#line 590 "syntax.act"

		(ZIa) = add_ref((ZIi));
	
#line 4508 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ref */
		}
		break;
	case 1:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: sid-ident */
			{
#line 160 "syntax.act"

		int n;
		char *s;
		char buf[1000];
		strcpy (buf, token_prefix);
		n = (int) strlen (buf);
		for (s = tokbuf; *s; s++) {
			if (*s == '-') {
				buf[n++] = '_';
				buf[n++] = 'H';
			} else if (*s == '_') {
				buf[n++] = '_';
				buf[n++] = '_';
			} else {
				buf[n++] = *s;
			}
			if (n >= 900) {
				error (ERROR_SERIOUS, "Identifier too long");
				break;
			}
		}
		buf[n] = 0;
		ZIb = xstrdup(buf);
	
#line 4544 "syntax.c"
			}
			/* END OF EXTRACT: sid-ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_terminal */
			{
#line 594 "syntax.act"

		(ZIa) = add_terminal((ZIb));
	
#line 4554 "syntax.c"
			}
			/* END OF ACTION: make_arg_terminal */
		}
		break;
	case 2:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: string */
			{
#line 164 "syntax.act"

		ZIb = xstrdup (tokbuf);
	
#line 4569 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 599 "syntax.act"

		(ZIa) = add_none();
	
#line 4579 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_in_action_rhs */
			{
#line 751 "syntax.act"

		error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusion."
			" Will be implemented with an alternate meaning once direct function calls are removed from lexi");
	
#line 4589 "syntax.c"
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

#line 762 "syntax.act"

#line 4611 "syntax.c"

/* END OF FILE */
