/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 87 "syntax.act"


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
	#include <adt/arg.h>
	#include <adt/cmd.h>
	#include <adt/param.h>
	#include <adt/keyword.h>
	#include <adt/zone.h>

	#include "ast.h"
	#include "lexer.h"
	#include "syntax.h"
	#include "options.h"

	#define ADVANCE_LEXER    ADVANCE_LXI_LEXER
	#define CURRENT_TERMINAL CURRENT_LXI_TERMINAL
	#define SAVE_LEXER       SAVE_LXI_LEXER
	#define RESTORE_LEXER    RESTORE_LXI_LEXER

	typedef char *SID_STRING;
	typedef char *SID_CHARS;
	typedef struct cmd* cmdP;
	typedef struct cmd_list* cmd_listP;
	typedef struct arg* argP;
	typedef struct args_list* args_listP;
	typedef struct param * paramP;

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

#line 70 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRparam_Hlist(zoneP, paramP *);
static void ZRexpected__semicolon(void);
static void ZRparam_Hlist_C_Cparam(zoneP, paramP *);
static void ZRzone_Hdefn(zoneP);
static void ZR141(void);
static void ZR142(void);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZR162(args_listP *);
static void ZRcmd_Hlist(zoneP, cmd_listP *);
static void ZRparam_Hlist_C_Cparam_Hlist1(zoneP, paramP *);
static void ZR180(SID_STRING *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZRcmd(zoneP, cmdP *);
static void ZR182(zoneP *, cmd_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZR203(zoneP, cmd_listP, zoneP *, cmd_listP *);
static void ZR205(zoneP *);
static void ZR206(zoneP *);
static void ZR207(zoneP *, args_listP *, cmdP *);
static void ZRcommand_Hlist(zoneP);
static void ZR211(zoneP *, args_listP *, SID_STRING *, cmdP *);
static void ZR212(argP *, args_listP *);
static void ZR214(zoneP *, paramP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcommand(zoneP);
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
ZRparam_Hlist(zoneP ZIz, paramP *ZOa)
{
	paramP ZIa;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		/* BEGINNING OF ACTION: init-param */
		{
#line 668 "syntax.act"

		(ZIa) = NULL;
	
#line 131 "syntax.c"
		}
		/* END OF ACTION: init-param */
		ZR214 (&ZIz, &ZIa);
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
	*ZOa = ZIa;
}

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
#line 731 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
	
#line 172 "syntax.c"
		}
		/* END OF ACTION: E_expected_semicolon */
	}
}

static void
ZRparam_Hlist_C_Cparam(zoneP ZIz, paramP *ZIa)
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
#line 108 "syntax.act"

		ZIname = xstrdup (tokbuf);
	
#line 200 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-ident */
					{
#line 171 "syntax.act"

		(ZIname) = xstrdup("");
	
#line 214 "syntax.c"
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
#line 108 "syntax.act"

		ZItype = xstrdup (tokbuf);
	
#line 237 "syntax.c"
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
#line 556 "syntax.act"
 (ZIisref) = 1; 
#line 255 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 557 "syntax.act"
 (ZIisref) = 0; 
#line 266 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 128 */
		/* BEGINNING OF ACTION: append-param */
		{
#line 675 "syntax.act"

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
			param_append((ZIa), &istr, et, (ZIisref));
		}

		nstring_destroy(&tstr);

		xfree((ZItype));
		xfree((ZIname));
	
#line 300 "syntax.c"
		}
		/* END OF ACTION: append-param */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
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
#line 108 "syntax.act"

		ZIzid = xstrdup (tokbuf);
	
#line 343 "syntax.c"
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
#line 704 "syntax.act"

		(ZIzid)="";
		error(ERROR_SERIOUS, "Syntax error: expected identifier");
	
#line 362 "syntax.c"
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
#line 727 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
	
#line 389 "syntax.c"
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
#line 556 "syntax.act"
 (ZIlendclosed) = 1; 
#line 408 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 18:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 556 "syntax.act"
 (ZIlendclosed) = 1; 
#line 420 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 19:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: false */
					{
#line 557 "syntax.act"
 (ZIlendclosed) = 0; 
#line 432 "syntax.c"
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
#line 710 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected range");
	
#line 452 "syntax.c"
				}
				/* END OF ACTION: E_expected_range */
				/* BEGINNING OF ACTION: false */
				{
#line 557 "syntax.act"
 (ZIlendclosed) = 0; 
#line 459 "syntax.c"
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
#line 563 "syntax.act"

		struct cmd *c;
		struct cmd_list *l;

		(ZInew_Hzone) = add_zone((ZIz), (ZIzid), (ZIe), (ZIlendclosed));

		(ZInew_Hzone)->exit = (ZIexit_Hcmds);
		if ((ZInew_Hzone)->exit->return_count) {
			(ZInew_Hzone)->kind = ZONE_PSEUDO;
		}

		(ZInew_Hzone)->enter = (ZIentry_Hcmds);
		if ((ZInew_Hzone)->enter->return_count) {
			(ZInew_Hzone)->kind = ZONE_GENERAL;
		}

		c = add_cmd_push_zone((ZInew_Hzone));
		l = add_cmd_list();
		*l->tail = c;
		l->tail = &c->next;

		add_mainpass((ZIz), (ZIb), l);
	
#line 498 "syntax.c"
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
#line 584 "syntax.act"

		switch ((ZInew_Hzone)->kind) {
		case ZONE_PSEUDO:
		case ZONE_GENERAL:
			(ZIz)->kind = ZONE_GENERAL;
			break;

		case ZONE_PURE:
			/* do nothing */
			break;
		}
	
#line 534 "syntax.c"
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
#line 714 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
	
#line 568 "syntax.c"
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
#line 718 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
	
#line 598 "syntax.c"
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
#line 142 "syntax.act"
 ZIa = "0123456789";                 
#line 624 "syntax.c"
					}
					/* END OF EXTRACT: digit */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: lower */
					{
#line 141 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz"; 
#line 636 "syntax.c"
					}
					/* END OF EXTRACT: lower */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: string */
					{
#line 137 "syntax.act"

		ZIa = xstrdup (tokbuf);
	
#line 650 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: upper */
					{
#line 140 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
#line 662 "syntax.c"
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
#line 167 "syntax.act"

		(ZIs) = xstrcat ((ZIa), (ZIb));
	
#line 692 "syntax.c"
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
#line 108 "syntax.act"

		ZIs = xstrdup (tokbuf);
	
#line 738 "syntax.c"
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
#line 613 "syntax.act"

	   (ZI0) = tree_zoneisglobal((ZIz)->ast, (ZIz));
	
#line 755 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-type */
				{
#line 620 "syntax.act"

		NStringT str;
		struct entry *e;

		nstring_copy_cstring(&str,(ZIs));
		xfree((ZIs));

		e = table_get_entry(tree_get_table((ZIz)->ast), &str);
		if (e != NULL) {
			nstring_destroy(&str);
			/* TODO: switch ? */
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
			table_add_type(tree_get_table((ZIz)->ast), &str);
		}
	
#line 787 "syntax.c"
				}
				/* END OF ACTION: make-type */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonetype */
				{
#line 700 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs));
	
#line 800 "syntax.c"
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
		/* BEGINNING OF INLINE: 213 */
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
		/* END OF INLINE: 213 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
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
		ZR212 (&ZIa, &ZIr);
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
#line 261 "syntax.act"

		(ZIr)=add_args_list();
	
#line 898 "syntax.c"
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
ZRcmd_Hlist(zoneP ZI197, cmd_listP *ZO202)
{
	cmd_listP ZI202;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		cmdP ZIc;
		cmd_listP ZIl;
		zoneP ZI201;

		ZRcmd (ZI197, &ZIc);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: empty-cmd-list */
		{
#line 519 "syntax.act"

		(ZIl) = add_cmd_list();
	
#line 938 "syntax.c"
		}
		/* END OF ACTION: empty-cmd-list */
		/* BEGINNING OF ACTION: add-cmd-to-list */
		{
#line 265 "syntax.act"

		if ((ZIc) != NULL) { /* if (ZIc) == NULL, an error has already been issued.*/
			struct LocalNamesT* locals = cmdlist_localnames((ZIl));

			if ((ZIl)->return_count > 0 && (ZIc)->kind != CMD_NOOP) {
				error(ERROR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
			}

			if ((ZIc)->kind == CMD_RETURN) {
				(ZIl)->return_count++;
			}

			if ((ZIc)->kind == CMD_ACTION) {
				struct args_list *rhs;
				struct args_list *lhs;
				struct action *act;
				struct entry *ea;
				struct arg *p;
				struct param *q;

				(ZIl)->return_count += (ZIc)->u.act.lhs->return_count;
				if ((ZIl)->return_count > 1) {
					error(ERROR_SERIOUS, "Only one terminal may be returned per token");
				}

				ea  = (ZIc)->u.act.ea;
				act = entry_get_action(ea);
				rhs = (ZIc)->u.act.rhs;
				lhs = (ZIc)->u.act.lhs;

				/* CHECKING RHS COMPATIBILITY */
				for (p = rhs->head, q = act->in; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et = NULL;
					NStringT str;

					switch (p->kind) {
					case ARG_IDENT:
						nstring_copy_cstring(&str, p->u.literal);
						et=localnames_get_type(locals, &str);
						nstring_destroy(&str);
						if (!et) {
							struct entry *e = table_get_entry(tree_get_table((ZI197)->ast), &str);
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

					case ARG_CHARP:
						/* TODO: assert(lexer_string_type(ast)) */
						et = lexer_string_type((ZI197)->ast);
						break;

					case ARG_CHAR_NUM:
						/* TODO: assert(lexer_char_type(ast)) */
						et = lexer_char_type((ZI197)->ast);
						break;

					case ARG_TERMINAL:
						/* TODO: assert(lexer_terminal_type(ast)) */
						et = lexer_terminal_type((ZI197)->ast);
						break;

					case ARG_CHAR_COUNT:
						/* TODO: assert(lexer_terminal_type(ast)) */
						et = lexer_int_type((ZI197)->ast);
						break;

					case ARG_NONE:
						break; /* Error already detected, do nothing and leave p->lexitype = NULL */

					case ARG_IGNORE:
					case ARG_RETURN:
						UNREACHED;
						break;

					default:
						UNREACHED;
						break;
					}

					if (et) {
						if (q->et!=et || p->is_ref !=q->is_ref) {
							char *s1 = nstring_to_cstring(entry_key(ea));
							char *s2 = nstring_to_cstring(entry_key(et));
							char *s3 = p->is_ref ? "&" : "";
							char *s4 = nstring_to_cstring(entry_key(q->et));
							char *s5 = q->is_ref ? "&" : "";
							char *s6 = "unknown";
							char *s7 = "unknown";

							switch (p->kind) {
							case ARG_TERMINAL:
								s6 = "$";
								s7 = p->u.literal;
								break;

							case ARG_IDENT:
								s7 = p->u.literal;
								break;

							case ARG_CHAR_COUNT:
								s6 = "#n";
								break;

							case ARG_CHAR_NUM:
								s6 = "#[number]";
								/* TODO: s7=p->u.digit */;
								break;

							case ARG_CHARP:
								s6 = "#*";
								break;
							}

							error(ERROR_SERIOUS, "In call to action %s, argument \'%s%s\' has type \'%s%s\' when it should have type %s",
								s1, s6, s7, s2, s3, s4, s5);

							xfree(s1);
							xfree(s2);
							xfree(s4);
						}
					}
				}

				if (p != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
					xfree(s);
				}

				if (q != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
					xfree(s);
				}

				for (p = lhs->head, q = act->out; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et;

					switch (p->kind) {
					case ARG_IDENT: {
						NStringT str;

						nstring_copy_cstring(&str, p->u.literal);
						et = localnames_get_type(locals, &str);
						if (!et) {
							struct entry *e= table_get_entry(tree_get_table((ZI197)->ast), &str);
							localnames_add_nstring(locals, &str, q->et);
							if (e) {
								nstring_destroy(&str);
								if (entry_is_action(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);
								}
							} else {
								table_add_local_name(tree_get_table((ZI197)->ast), &str);
							}
							if (p->is_ref) {
								char *s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								xfree(s);
							}
						} else {
							nstring_destroy(&str);
							if (!p->is_ref) {
								char *s;

								s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								xfree(s);

								et = q->et; /* To avoid outputting that error more than once */
							}
						}
						break;
					}

					case ARG_RETURN:
						et = lexer_terminal_type((ZI197)->ast);
						q->is_ref = false;
						/* TODO: assert(q->is_ref == false) */
						break;

					case ARG_IGNORE:
						/* always acceptable */
						et = q->et;
						p->is_ref = q->is_ref;
						break;

					case ARG_NONE:
						break;
						/* TODO: asserting errored is already set */
						/* Error has already been detected */

					case ARG_CHARP:
					case ARG_CHAR_NUM:
					case ARG_TERMINAL:
					case ARG_CHAR_COUNT:
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

				if (p != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many results", s);
					xfree(s);
				}

				if (q != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
					xfree(s);
				}
			}

			/* TODO: only append if no error */
			*(ZIl)->tail = (ZIc);
			(ZIl)->tail = &(ZIc)->next;
			(ZIl)->size++;
		}
	
#line 1191 "syntax.c"
		}
		/* END OF ACTION: add-cmd-to-list */
		ZR203 (ZI197, ZIl, &ZI201, &ZI202);
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
	*ZO202 = ZI202;
}

static void
ZRparam_Hlist_C_Cparam_Hlist1(zoneP ZIz, paramP *ZIa)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
ZL2_param_Hlist_C_Cparam_Hlist1:;
	{
		ZRparam_Hlist_C_Cparam (ZIz, ZIa);
		/* BEGINNING OF INLINE: 215 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: param-list::param-list1 */
					goto ZL2_param_Hlist_C_Cparam_Hlist1;
					/* END OF INLINE: param-list::param-list1 */
				}
				/*UNREACHED*/
			case 39:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 215 */
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
#line 721 "syntax.act"

			(ZIe) = NULL;
		error(ERROR_SERIOUS, "Syntax error: expected characters");
	
#line 1268 "syntax.c"
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
#line 186 "syntax.act"

		assert((ZIz) != NULL);
		assert((ZIs) != NULL);
		assert((ZIt) != NULL);

		add_prepass((ZIz), (ZIs), (ZIt));
	
#line 1310 "syntax.c"
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
#line 261 "syntax.act"

		(ZIl)=add_args_list();
	
#line 1337 "syntax.c"
		}
		/* END OF ACTION: empty-args-list */
		ZR207 (&ZIz, &ZIl, &ZIc);
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
#line 519 "syntax.act"

		(ZIexit_Hcmds) = add_cmd_list();
	
#line 1378 "syntax.c"
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
#line 751 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 1426 "syntax.c"
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
		paramP ZIit;
		paramP ZIot;

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
#line 743 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
	
#line 1478 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 1493 "syntax.c"
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
#line 747 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
	
#line 1521 "syntax.c"
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
					ZRparam_Hlist (ZIz, &ZIit);
					ZR142 ();
					ZR118 ();
					ZR141 ();
					ZRparam_Hlist (ZIz, &ZIot);
					ZR142 ();
					if ((CURRENT_TERMINAL) == 39) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: init-param */
					{
#line 668 "syntax.act"

		(ZIit) = NULL;
	
#line 1555 "syntax.c"
					}
					/* END OF ACTION: init-param */
					/* BEGINNING OF ACTION: init-param */
					{
#line 668 "syntax.act"

		(ZIot) = NULL;
	
#line 1564 "syntax.c"
					}
					/* END OF ACTION: init-param */
				}
				break;
			}
		}
		/* END OF INLINE: 135 */
		/* BEGINNING OF ACTION: make-action */
		{
#line 645 "syntax.act"

		NStringT str;
		struct entry *e;

		nstring_copy_cstring(&str, (ZIi));

		e = table_get_entry(tree_get_table((ZIz)->ast), &str);
		if (e != NULL) {
			nstring_destroy(&str);
			/* TODO: switch ? */
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
			table_add_action(tree_get_table((ZIz)->ast), &str , (ZIit), (ZIot));
		}

		xfree((ZIi));
	
#line 1600 "syntax.c"
		}
		/* END OF ACTION: make-action */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR203(zoneP ZI197, cmd_listP ZI200, zoneP *ZO201, cmd_listP *ZO202)
{
	zoneP ZI201;
	cmd_listP ZI202;

ZL2_203:;
	switch (CURRENT_TERMINAL) {
	case 20:
		{
			cmd_listP ZIl;
			cmdP ZIc;

			ZIl = ZI200;
			ADVANCE_LEXER;
			ZRcmd (ZI197, &ZIc);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-cmd-to-list */
			{
#line 265 "syntax.act"

		if ((ZIc) != NULL) { /* if (ZIc) == NULL, an error has already been issued.*/
			struct LocalNamesT* locals = cmdlist_localnames((ZIl));

			if ((ZIl)->return_count > 0 && (ZIc)->kind != CMD_NOOP) {
				error(ERROR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
			}

			if ((ZIc)->kind == CMD_RETURN) {
				(ZIl)->return_count++;
			}

			if ((ZIc)->kind == CMD_ACTION) {
				struct args_list *rhs;
				struct args_list *lhs;
				struct action *act;
				struct entry *ea;
				struct arg *p;
				struct param *q;

				(ZIl)->return_count += (ZIc)->u.act.lhs->return_count;
				if ((ZIl)->return_count > 1) {
					error(ERROR_SERIOUS, "Only one terminal may be returned per token");
				}

				ea  = (ZIc)->u.act.ea;
				act = entry_get_action(ea);
				rhs = (ZIc)->u.act.rhs;
				lhs = (ZIc)->u.act.lhs;

				/* CHECKING RHS COMPATIBILITY */
				for (p = rhs->head, q = act->in; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et = NULL;
					NStringT str;

					switch (p->kind) {
					case ARG_IDENT:
						nstring_copy_cstring(&str, p->u.literal);
						et=localnames_get_type(locals, &str);
						nstring_destroy(&str);
						if (!et) {
							struct entry *e = table_get_entry(tree_get_table((ZI197)->ast), &str);
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

					case ARG_CHARP:
						/* TODO: assert(lexer_string_type(ast)) */
						et = lexer_string_type((ZI197)->ast);
						break;

					case ARG_CHAR_NUM:
						/* TODO: assert(lexer_char_type(ast)) */
						et = lexer_char_type((ZI197)->ast);
						break;

					case ARG_TERMINAL:
						/* TODO: assert(lexer_terminal_type(ast)) */
						et = lexer_terminal_type((ZI197)->ast);
						break;

					case ARG_CHAR_COUNT:
						/* TODO: assert(lexer_terminal_type(ast)) */
						et = lexer_int_type((ZI197)->ast);
						break;

					case ARG_NONE:
						break; /* Error already detected, do nothing and leave p->lexitype = NULL */

					case ARG_IGNORE:
					case ARG_RETURN:
						UNREACHED;
						break;

					default:
						UNREACHED;
						break;
					}

					if (et) {
						if (q->et!=et || p->is_ref !=q->is_ref) {
							char *s1 = nstring_to_cstring(entry_key(ea));
							char *s2 = nstring_to_cstring(entry_key(et));
							char *s3 = p->is_ref ? "&" : "";
							char *s4 = nstring_to_cstring(entry_key(q->et));
							char *s5 = q->is_ref ? "&" : "";
							char *s6 = "unknown";
							char *s7 = "unknown";

							switch (p->kind) {
							case ARG_TERMINAL:
								s6 = "$";
								s7 = p->u.literal;
								break;

							case ARG_IDENT:
								s7 = p->u.literal;
								break;

							case ARG_CHAR_COUNT:
								s6 = "#n";
								break;

							case ARG_CHAR_NUM:
								s6 = "#[number]";
								/* TODO: s7=p->u.digit */;
								break;

							case ARG_CHARP:
								s6 = "#*";
								break;
							}

							error(ERROR_SERIOUS, "In call to action %s, argument \'%s%s\' has type \'%s%s\' when it should have type %s",
								s1, s6, s7, s2, s3, s4, s5);

							xfree(s1);
							xfree(s2);
							xfree(s4);
						}
					}
				}

				if (p != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
					xfree(s);
				}

				if (q != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
					xfree(s);
				}

				for (p = lhs->head, q = act->out; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et;

					switch (p->kind) {
					case ARG_IDENT: {
						NStringT str;

						nstring_copy_cstring(&str, p->u.literal);
						et = localnames_get_type(locals, &str);
						if (!et) {
							struct entry *e= table_get_entry(tree_get_table((ZI197)->ast), &str);
							localnames_add_nstring(locals, &str, q->et);
							if (e) {
								nstring_destroy(&str);
								if (entry_is_action(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(e)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);
								}
							} else {
								table_add_local_name(tree_get_table((ZI197)->ast), &str);
							}
							if (p->is_ref) {
								char *s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								xfree(s);
							}
						} else {
							nstring_destroy(&str);
							if (!p->is_ref) {
								char *s;

								s = nstring_to_cstring(entry_key(ea));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								xfree(s);

								et = q->et; /* To avoid outputting that error more than once */
							}
						}
						break;
					}

					case ARG_RETURN:
						et = lexer_terminal_type((ZI197)->ast);
						q->is_ref = false;
						/* TODO: assert(q->is_ref == false) */
						break;

					case ARG_IGNORE:
						/* always acceptable */
						et = q->et;
						p->is_ref = q->is_ref;
						break;

					case ARG_NONE:
						break;
						/* TODO: asserting errored is already set */
						/* Error has already been detected */

					case ARG_CHARP:
					case ARG_CHAR_NUM:
					case ARG_TERMINAL:
					case ARG_CHAR_COUNT:
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

				if (p != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, too many results", s);
					xfree(s);
				}

				if (q != NULL) {
					char *s = nstring_to_cstring(entry_key(ea));
					error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
					xfree(s);
				}
			}

			/* TODO: only append if no error */
			*(ZIl)->tail = (ZIc);
			(ZIl)->tail = &(ZIc)->next;
			(ZIl)->size++;
		}
	
#line 1880 "syntax.c"
			}
			/* END OF ACTION: add-cmd-to-list */
			/* BEGINNING OF INLINE: 203 */
			ZI200 = ZIl;
			goto ZL2_203;
			/* END OF INLINE: 203 */
		}
		/*UNREACHED*/
	default:
		{
			ZI201 = ZI197;
			ZI202 = ZI200;
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
	*ZO201 = ZI201;
	*ZO202 = ZI202;
}

static void
ZR205(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 1922 "syntax.c"
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
#line 182 "syntax.act"

		make_group ((*ZIz), (ZIi), (ZIs));
	
#line 1938 "syntax.c"
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
#line 175 "syntax.act"

		if ((*ZIz)->white_space) {
			error (ERROR_SERIOUS, "White space group already defined");
		}
		(*ZIz)->white_space = make_group((*ZIz), "white", (ZIs));
	
#line 1968 "syntax.c"
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
ZR206(zoneP *ZIz)
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
#line 538 "syntax.act"

		(*ZIz)->local=(ZIl);
		if ((ZIl)->return_count) {
			(*ZIz)->kind = ZONE_GENERAL;
		}
	
#line 2019 "syntax.c"
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
#line 513 "syntax.act"

		if ((ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "At most one return terminal may be specified per command list");
		}
	
#line 2058 "syntax.c"
			}
			/* END OF ACTION: check-cmd-list */
			/* BEGINNING OF ACTION: make-token */
			{
#line 523 "syntax.act"

		add_mainpass((*ZIz), (ZIs), (ZIl));
		if ((ZIl)->return_count) {
			(*ZIz)->kind = ZONE_GENERAL;
		}
	
#line 2070 "syntax.c"
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
ZR207(zoneP *ZIz, args_listP *ZIl, cmdP *ZOc)
{
	cmdP ZIc;

	switch (CURRENT_TERMINAL) {
	case 25:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-count */
			{
#line 153 "syntax.act"

		ZIb = add_arg(ARG_CHAR_COUNT, 0);
	
#line 2110 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-count */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 2120 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2129 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 2142 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2167 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2183 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 2237 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 24:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-num */
			{
#line 149 "syntax.act"

		ZIb = add_arg(ARG_CHAR_NUM, numbuf);
	
#line 2255 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-num */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 2265 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2274 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 2287 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2312 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2328 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 2382 "syntax.c"
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
#line 145 "syntax.act"

		ZIb = add_arg(ARG_CHARP, 0);
	
#line 2400 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 2410 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2419 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 2432 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2457 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2473 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 2527 "syntax.c"
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
#line 161 "syntax.act"

		ZIa = add_arg(ARG_IGNORE ,0);
	
#line 2544 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 2558 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2583 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2599 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	case 26:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: arg-return */
			{
#line 157 "syntax.act"

		ZIa = add_arg(ARG_RETURN, 0);
	
#line 2670 "syntax.c"
			}
			/* END OF EXTRACT: arg-return */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 2684 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2709 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2725 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 2779 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2798 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2814 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 2868 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 0:
		{
			SID_STRING ZI208;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 108 "syntax.act"

		ZI208 = xstrdup (tokbuf);
	
#line 2886 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ident */
			{
#line 597 "syntax.act"

		(ZIa) = add_ident((ZI208));
	
#line 2896 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ident */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 2909 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 2934 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2950 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 3004 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-donothing-cmd */
			{
#line 198 "syntax.act"

		(ZIc) = add_cmd_donothing();
	
#line 3018 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3062 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3078 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 3132 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 16:
		{
			SID_STRING ZI209;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 108 "syntax.act"

		ZI209 = xstrdup (tokbuf);
	
#line 3153 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ref */
			{
#line 601 "syntax.act"

		(ZIa) = add_ref((ZI209));
	
#line 3167 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ref */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 3180 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3205 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3221 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 3275 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 1:
		{
			SID_STRING ZI210;

			/* BEGINNING OF EXTRACT: sid-ident */
			{
#line 133 "syntax.act"

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
		ZI210 = xstrdup(buf);
	
#line 3311 "syntax.c"
			}
			/* END OF EXTRACT: sid-ident */
			ADVANCE_LEXER;
			ZR211 (ZIz, ZIl, &ZI210, &ZIc);
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
#line 137 "syntax.act"

		ZIb = xstrdup (tokbuf);
	
#line 3335 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 3345 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_arg_in_lhs */
			{
#line 759 "syntax.act"

		error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
	
#line 3354 "syntax.c"
			}
			/* END OF ACTION: E_string_arg_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 3367 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3392 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3408 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 3462 "syntax.c"
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
#line 751 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 3514 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZR211(zoneP *ZIz, args_listP *ZIl, SID_STRING *ZI210, cmdP *ZOc)
{
	cmdP ZIc;

	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: make-terminal-cmd */
			{
#line 194 "syntax.act"

			(ZIc) = add_cmd_return((*ZI210));
	
#line 3534 "syntax.c"
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
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 3551 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_terminal_in_lhs */
			{
#line 776 "syntax.act"

		error(ERROR_SERIOUS, "Terminal argument in left handside");
	
#line 3560 "syntax.c"
			}
			/* END OF ACTION: E_terminal_in_lhs */
			/* BEGINNING OF ACTION: append-arg-args-list */
			{
#line 239 "syntax.act"

		*(*ZIl)->tail=(ZIa);
		(*ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(*ZIl)->return_count++;
		}
	
#line 3573 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 3592 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 255 "syntax.act"

		if ((*ZIl)->return_count > 1) {
			error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3608 "syntax.c"
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
#line 205 "syntax.act"

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
					if (p->kind == ARG_IDENT) {
						for(q=p->next; q!=NULL;q=q->next) {
							if (q->kind == ARG_IDENT && !strcmp(p->u.literal, q->u.literal)) {
								char *s = nstring_to_cstring(entry_key(ea));
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
	
#line 3662 "syntax.c"
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
ZR212(argP *ZIa, args_listP *ZOr)
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
#line 247 "syntax.act"

		(*ZIa)->next=(ZIr)->head;
		(ZIr)->head=(*ZIa);
		if ((*ZIa)->kind == ARG_RETURN) {
			(ZIr)->return_count++;
		}
	
#line 3702 "syntax.c"
			}
			/* END OF ACTION: args-list-push-front */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty-args-list */
			{
#line 261 "syntax.act"

		(ZIr)=add_args_list();
	
#line 3715 "syntax.c"
			}
			/* END OF ACTION: empty-args-list */
			/* BEGINNING OF ACTION: args-list-push-front */
			{
#line 247 "syntax.act"

		(*ZIa)->next=(ZIr)->head;
		(ZIr)->head=(*ZIa);
		if ((*ZIa)->kind == ARG_RETURN) {
			(ZIr)->return_count++;
		}
	
#line 3728 "syntax.c"
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
ZR214(zoneP *ZIz, paramP *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 15:
		{
			ZRparam_Hlist_C_Cparam_Hlist1 (*ZIz, ZIa);
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
#line 137 "syntax.act"

		ZIs = xstrdup (tokbuf);
	
#line 3793 "syntax.c"
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
#line 613 "syntax.act"

	   (ZI0) = tree_zoneisglobal((ZIz)->ast, (ZIz));
	
#line 3822 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-keyword */
				{
#line 545 "syntax.act"

		switch ((ZIc)->kind) {
		case CMD_RETURN:
			/* Fallback is intentional */
			add_keyword((ZIz), (ZIs), (ZIc));
			break;

		default:
		  error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
		}
	
#line 3841 "syntax.c"
				}
				/* END OF ACTION: make-keyword */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
				{
#line 697 "syntax.act"

		error(ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ");
	
#line 3854 "syntax.c"
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
			ZR205 (&ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 35:
		{
			ADVANCE_LEXER;
			ZR206 (&ZIz);
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
#line 261 "syntax.act"

		(ZIr)=add_args_list();
	
#line 4011 "syntax.c"
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
#line 530 "syntax.act"

		(ZI0) = strlen((ZIs)) > 0;
	
#line 4058 "syntax.c"
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
#line 535 "syntax.act"

		error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");
	
#line 4073 "syntax.c"
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
#line 739 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
	
#line 4113 "syntax.c"
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
#line 735 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
	
#line 4143 "syntax.c"
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
			case 25:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-count */
					{
#line 153 "syntax.act"

		ZIb = add_arg(ARG_CHAR_COUNT, 0);
	
#line 4171 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-count */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4181 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4190 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 24:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-num */
					{
#line 149 "syntax.act"

		ZIb = add_arg(ARG_CHAR_NUM, numbuf);
	
#line 4205 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-num */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4215 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4224 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 23:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-string */
					{
#line 145 "syntax.act"

		ZIb = add_arg(ARG_CHARP, 0);
	
#line 4239 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4249 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 755 "syntax.act"

		error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4258 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 27:
				{
					/* BEGINNING OF EXTRACT: arg-ignore */
					{
#line 161 "syntax.act"

		ZIa = add_arg(ARG_IGNORE ,0);
	
#line 4271 "syntax.c"
					}
					/* END OF EXTRACT: arg-ignore */
					ADVANCE_LEXER;
				}
				break;
			case 26:
				{
					/* BEGINNING OF EXTRACT: arg-return */
					{
#line 157 "syntax.act"

		ZIa = add_arg(ARG_RETURN, 0);
	
#line 4285 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4301 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_ident */
					{
#line 597 "syntax.act"

		(ZIa) = add_ident((ZIi));
	
#line 4311 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4329 "syntax.c"
						}
						/* END OF EXTRACT: ident */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_ref */
					{
#line 601 "syntax.act"

		(ZIa) = add_ref((ZIi));
	
#line 4343 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_ref */
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: sid-ident */
					{
#line 133 "syntax.act"

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
	
#line 4379 "syntax.c"
					}
					/* END OF EXTRACT: sid-ident */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4389 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_terminal_in_lhs */
					{
#line 776 "syntax.act"

		error(ERROR_SERIOUS, "Terminal argument in left handside");
	
#line 4398 "syntax.c"
					}
					/* END OF ACTION: E_terminal_in_lhs */
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: string */
					{
#line 137 "syntax.act"

		ZIb = xstrdup (tokbuf);
	
#line 4413 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4423 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_string_arg_in_lhs */
					{
#line 759 "syntax.act"

		error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
	
#line 4432 "syntax.c"
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
#line 239 "syntax.act"

		*(ZIl)->tail=(ZIa);
		(ZIl)->tail=&(ZIa)->next;
		if ((ZIa)->kind == ARG_RETURN) {
			(ZIl)->return_count++;
		}
	
#line 4452 "syntax.c"
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
	case 25:
		{
			/* BEGINNING OF EXTRACT: arg-char-count */
			{
#line 153 "syntax.act"

		ZIa = add_arg(ARG_CHAR_COUNT, 0);
	
#line 4476 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-count */
			ADVANCE_LEXER;
		}
		break;
	case 24:
		{
			/* BEGINNING OF EXTRACT: arg-char-num */
			{
#line 149 "syntax.act"

		ZIa = add_arg(ARG_CHAR_NUM, numbuf);
	
#line 4490 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-num */
			ADVANCE_LEXER;
		}
		break;
	case 23:
		{
			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 145 "syntax.act"

		ZIa = add_arg(ARG_CHARP, 0);
	
#line 4504 "syntax.c"
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
#line 161 "syntax.act"

		ZIb = add_arg(ARG_IGNORE ,0);
	
#line 4520 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4530 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_ignore_in_rhs */
			{
#line 772 "syntax.act"

		error(ERROR_SERIOUS, "Ignore argument in right handside");
	
#line 4539 "syntax.c"
			}
			/* END OF ACTION: E_ignore_in_rhs */
		}
		break;
	case 26:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-return */
			{
#line 157 "syntax.act"

		ZIb = add_arg(ARG_RETURN, 0);
	
#line 4554 "syntax.c"
			}
			/* END OF EXTRACT: arg-return */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4564 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_return_in_rhs */
			{
#line 763 "syntax.act"

		error(ERROR_SERIOUS, "Return terminal argument in right handside");
	
#line 4573 "syntax.c"
			}
			/* END OF ACTION: E_return_in_rhs */
		}
		break;
	case 0:
		{
			SID_STRING ZIi;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4588 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ident */
			{
#line 597 "syntax.act"

		(ZIa) = add_ident((ZIi));
	
#line 4598 "syntax.c"
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
#line 108 "syntax.act"

		ZIi = xstrdup (tokbuf);
	
#line 4616 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ref */
			{
#line 601 "syntax.act"

		(ZIa) = add_ref((ZIi));
	
#line 4630 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ref */
		}
		break;
	case 1:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: sid-ident */
			{
#line 133 "syntax.act"

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
	
#line 4666 "syntax.c"
			}
			/* END OF EXTRACT: sid-ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_terminal */
			{
#line 605 "syntax.act"

		(ZIa) = add_terminal((ZIb));
	
#line 4676 "syntax.c"
			}
			/* END OF ACTION: make_arg_terminal */
		}
		break;
	case 2:
		{
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: string */
			{
#line 137 "syntax.act"

		ZIb = xstrdup (tokbuf);
	
#line 4691 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 609 "syntax.act"

		(ZIa) = add_none();
	
#line 4701 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_in_action_rhs */
			{
#line 768 "syntax.act"

		error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusion."
			" Will be implemented with an alternate meaning once direct function calls are removed from lexi");
	
#line 4711 "syntax.c"
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

#line 779 "syntax.act"

#line 4733 "syntax.c"

/* END OF FILE */
