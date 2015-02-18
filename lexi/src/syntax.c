/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 72 "syntax.act"


	#include <assert.h>
	#include <string.h>
	#include <stdio.h>

	#include <shared/bool.h>
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
	#include <adt/local.h>
	#include <adt/frame.h>
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
	typedef struct frame* frameP;
	typedef struct arg* argP;
	typedef struct param * paramP;

	/*
	 * This string is added to the start of each sid identifier.
	 */
	char *token_prefix = "lxi_";

#line 58 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRparam_Hlist(zoneP, paramP *);
static void ZRexpected__semicolon(void);
static void ZRparam_Hlist_C_Cparam(zoneP, paramP *);
static void ZRzone_Hdefn(zoneP);
static void ZR141(void);
static void ZR142(void);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRaction_Hcall_C_Clhs_Htuple1(argP *);
static void ZRaction_Hcall_C_Crhs_Htuple1(argP *);
static void ZR162(argP *);
static void ZRcmd_Hlist(zoneP, frameP *);
static void ZRparam_Hlist_C_Cparam_Hlist1(zoneP, paramP *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR181(SID_STRING *);
static void ZRcmd(zoneP, cmdP *);
static void ZR183(zoneP *, frameP *);
extern void read_lex(zoneP);
static void ZR202(zoneP, frameP, zoneP *, frameP *);
static void ZRaction_Hdecl(zoneP);
static void ZR204(zoneP *);
static void ZR205(zoneP *);
static void ZR206(zoneP *, argP *, cmdP *);
static void ZRcommand_Hlist(zoneP);
static void ZR210(zoneP *, argP *, SID_STRING *, cmdP *);
static void ZR213(argP *, argP *);
static void ZR215(zoneP *, paramP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcommand(zoneP);
static void ZRaction_Hcall_C_Crhs_Htuple(argP *);
static void ZRnon_Hempty_Hchars(SID_STRING *);
static void ZR116(void);
static void ZR118(void);
static void ZRaction_Hcall_C_Clhs_Harg(argP *);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static bool ZI0;

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
#line 643 "syntax.act"

		(ZIa) = NULL;
	
#line 119 "syntax.c"
		}
		/* END OF ACTION: init-param */
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
#line 695 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected semicolon \';\'");
	
#line 160 "syntax.c"
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
		bool ZIisref;

		/* BEGINNING OF INLINE: 125 */
		{
			switch (CURRENT_TERMINAL) {
			case 0:
				{
					/* BEGINNING OF EXTRACT: ident */
					{
#line 93 "syntax.act"

		ZIname = xstrdup(tokbuf);
	
#line 188 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-ident */
					{
#line 156 "syntax.act"

		(ZIname) = xstrdup("");
	
#line 202 "syntax.c"
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
#line 93 "syntax.act"

		ZItype = xstrdup(tokbuf);
	
#line 225 "syntax.c"
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
#line 531 "syntax.act"
 (ZIisref) = 1; 
#line 243 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: false */
					{
#line 532 "syntax.act"
 (ZIisref) = 0; 
#line 254 "syntax.c"
					}
					/* END OF ACTION: false */
				}
				break;
			}
		}
		/* END OF INLINE: 128 */
		/* BEGINNING OF ACTION: append-param */
		{
#line 649 "syntax.act"

		struct entry *et;

		et = table_get_entry(&(ZIz)->ast->table, (ZItype));
		if (et == NULL) {
			 error(ERR_SERIOUS, "Unknown type %s", (ZItype));
		} else if (et->kind != ENTRY_TYPE) {
			 error(ERR_SERIOUS, "%s is not a type", (ZItype));
		} else {
			param_append((ZIa), (ZIname), et, (ZIisref));
		}
	
#line 277 "syntax.c"
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
		frameP ZIenter;
		bool ZIlendclosed;
		SID_STRING ZIe;
		frameP ZIexit;
		zoneP ZInew_Hzone;

		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 173 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					/* BEGINNING OF EXTRACT: ident */
					{
#line 93 "syntax.act"

		ZIzid = xstrdup(tokbuf);
	
#line 320 "syntax.c"
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
#line 668 "syntax.act"

		(ZIzid)="";
		error(ERR_SERIOUS, "Syntax error: expected identifier");
	
#line 339 "syntax.c"
				}
				/* END OF ACTION: E_expected_ident */
			}
		ZL2:;
		}
		/* END OF INLINE: 173 */
		/* BEGINNING OF INLINE: 175 */
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
#line 691 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected colon \':\'");
	
#line 366 "syntax.c"
				}
				/* END OF ACTION: E_expected_colon */
			}
		ZL4:;
		}
		/* END OF INLINE: 175 */
		ZR181 (&ZIb);
		ZR183 (&ZIz, &ZIenter);
		/* BEGINNING OF INLINE: 179 */
		{
			switch (CURRENT_TERMINAL) {
			case 17:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 531 "syntax.act"
 (ZIlendclosed) = 1; 
#line 385 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 18:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: true */
					{
#line 531 "syntax.act"
 (ZIlendclosed) = 1; 
#line 397 "syntax.c"
					}
					/* END OF ACTION: true */
				}
				break;
			case 19:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: false */
					{
#line 532 "syntax.act"
 (ZIlendclosed) = 0; 
#line 409 "syntax.c"
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
#line 674 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected range");
	
#line 429 "syntax.c"
				}
				/* END OF ACTION: E_expected_range */
				/* BEGINNING OF ACTION: false */
				{
#line 532 "syntax.act"
 (ZIlendclosed) = 0; 
#line 436 "syntax.c"
				}
				/* END OF ACTION: false */
			}
		ZL6:;
		}
		/* END OF INLINE: 179 */
		ZR181 (&ZIe);
		ZR183 (&ZIz, &ZIexit);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-zone */
		{
#line 538 "syntax.act"

		struct cmd *c;
		struct frame *f;

		(ZInew_Hzone) = add_zone((ZIz), (ZIzid), (ZIe), (ZIlendclosed));

		(ZInew_Hzone)->exit = (ZIexit);
		if (cmd_return_count((ZInew_Hzone)->exit->cmds) != 0) {
			(ZInew_Hzone)->kind = ZONE_PSEUDO;
		}

		(ZInew_Hzone)->enter = (ZIenter);
		if (cmd_return_count((ZInew_Hzone)->enter->cmds) != 0) {
			(ZInew_Hzone)->kind = ZONE_GENERAL;
		}

		c = add_cmd_push_zone((ZInew_Hzone));
		f = add_frame();
		f->cmds = c;

		add_mainpass((ZIz), (ZIb), f);
	
#line 474 "syntax.c"
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
#line 558 "syntax.act"

		switch ((ZInew_Hzone)->kind) {
		case ZONE_PSEUDO:
		case ZONE_GENERAL:
			(ZIz)->kind = ZONE_GENERAL;
			break;

		case ZONE_PURE:
			/* do nothing */
			break;
		}
	
#line 510 "syntax.c"
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
#line 678 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected open \'(\'");
	
#line 544 "syntax.c"
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
#line 682 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected close \')\'");
	
#line 574 "syntax.c"
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
#line 127 "syntax.act"
 ZIa = "0123456789";                 
#line 600 "syntax.c"
					}
					/* END OF EXTRACT: digit */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: lower */
					{
#line 126 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz"; 
#line 612 "syntax.c"
					}
					/* END OF EXTRACT: lower */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: string */
					{
#line 122 "syntax.act"

		ZIa = xstrdup(tokbuf);
	
#line 626 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: upper */
					{
#line 125 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
#line 638 "syntax.c"
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
#line 152 "syntax.act"

		(ZIs) = xstrcat ((ZIa), (ZIb));
	
#line 668 "syntax.c"
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
#line 93 "syntax.act"

		ZIs = xstrdup(tokbuf);
	
#line 714 "syntax.c"
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
#line 587 "syntax.act"

	   (ZI0) = zone_isglobal((ZIz));
	
#line 731 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-type */
				{
#line 593 "syntax.act"

		struct entry *e;

		e = table_get_entry(&(ZIz)->ast->table, (ZIs));
		if (e != NULL) {
			switch (e->kind) {
			case ENTRY_TYPE:
				error(ERR_SERIOUS, "Type %s already exists", (ZIs));
				break;

			case ENTRY_LOCAL:
				error(ERR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.", (ZIs), (ZIs));
				break;

			case ENTRY_ACTION:
				error(ERR_SERIOUS, "Can't create type %s, %s has already been declared as an action", (ZIs), (ZIs));
				break;

			default:
				UNREACHED;
			}
		} else {
			table_add_type(&(ZIz)->ast->table, (ZIs));
		}
	
#line 764 "syntax.c"
				}
				/* END OF ACTION: make-type */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonetype */
				{
#line 664 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs));
	
#line 777 "syntax.c"
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
ZRaction_Hcall_C_Clhs_Htuple1(argP *ZIl)
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
				UNREACHED;
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
ZRaction_Hcall_C_Crhs_Htuple1(argP *ZOr)
{
	argP ZIr;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		argP ZI211;

		ZRaction_Hcall_C_Crhs_Harg (&ZI211);
		ZR213 (&ZI211, &ZIr);
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
ZR162(argP *ZOr)
{
	argP ZIr;

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
#line 242 "syntax.act"

		(ZIr) = NULL;
	
#line 875 "syntax.c"
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
ZRcmd_Hlist(zoneP ZI196, frameP *ZO201)
{
	frameP ZI201;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		cmdP ZIc;
		frameP ZIf;
		zoneP ZI200;

		ZRcmd (ZI196, &ZIc);
		if ((CURRENT_TERMINAL) == 39) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: make-frame */
		{
#line 494 "syntax.act"

		(ZIf) = add_frame();
	
#line 915 "syntax.c"
		}
		/* END OF ACTION: make-frame */
		/* BEGINNING OF ACTION: add-cmd-to-list */
		{
#line 246 "syntax.act"

		if ((ZIc) != NULL) { /* if (ZIc) == NULL, an error has already been issued.*/
			unsigned return_count;

			return_count = cmd_return_count((ZIf)->cmds);

			if (return_count > 0 && (ZIc)->kind != CMD_DISCARD) {
				error(ERR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
			}

			if ((ZIc)->kind == CMD_RETURN) {
				return_count++;
			}

			if ((ZIc)->kind == CMD_ACTION) {
				struct arg *lhs, *rhs;
				struct action *act;
				struct entry *ea;
				struct arg *p;
				struct param *q;

				return_count += arg_return_count((ZIc)->u.act.lhs);
				if (return_count > 1) {
					error(ERR_SERIOUS, "Only one terminal may be returned per token");
				}

				ea  = (ZIc)->u.act.ea;
				act = ea->u.act;
				rhs = (ZIc)->u.act.rhs;
				lhs = (ZIc)->u.act.lhs;

				/* CHECKING RHS COMPATIBILITY */
				for (p = rhs, q = act->in; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et = NULL;

					switch (p->kind) {
					case ARG_IDENT:
						et = local_find((ZIf)->locals, p->u.literal);
						if (et == NULL) {
							struct entry *e = table_get_entry(&(ZI196)->ast->table, p->u.literal);
							if (!e) {
								error(ERR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
								et = NULL;
							} else {
								switch (e->kind) {
								case ENTRY_LOCAL:
									error(ERR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
									et = NULL;
									break;

								case ENTRY_ACTION:
									error(ERR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
									et = NULL;
									break;

								case ENTRY_TYPE:
									error(ERR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
									et = NULL;
									break;

								default:
									UNREACHED;
								}
							}
						}
						break;

					case ARG_CHARP:
						/* TODO: assert(ast->lexi_string_type) */
						et = (ZI196)->ast->lexi_string_type;
						break;

					case ARG_CHAR_NUM:
						/* TODO: assert(ast->lexi_char_type) */
						et = (ZI196)->ast->lexi_char_type;
						break;

					case ARG_TERMINAL:
						/* TODO: assert(ast->lexi_terminal_type) */
						et = (ZI196)->ast->lexi_terminal_type;
						break;

					case ARG_CHAR_COUNT:
						/* TODO: assert(ast->lexi_int_type) */
						et = (ZI196)->ast->lexi_int_type;
						break;

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
							char *s3 = p->is_ref ? "&" : "";
							char *s4 = q->et->key;
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

							error(ERR_SERIOUS, "In call to action %s, argument \'%s%s\' has type \'%s%s\' when it should have type %s",
								ea->key, s6, s7, et->key, s3, s4, s5);
						}
					}
				}

				if (p != NULL) {
					error(ERR_SERIOUS, "In call to action %s, too many arguments", ea->key);
				}

				if (q != NULL) {
					error(ERR_SERIOUS, "In call to action %s, not enough arguments", ea->key);
				}

				for (p = lhs, q = act->out; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et;

					switch (p->kind) {
					case ARG_IDENT: {
						et = local_find((ZIf)->locals, p->u.literal);
						if (et == NULL) {
							struct entry *e = table_get_entry(&(ZI196)->ast->table, p->u.literal);
							/* TODO: error out if local name already exists? */
							local_add(&(ZIf)->locals, p->u.literal, q->et);
							if (e) {
								switch (e->kind) {
								case ENTRY_ACTION:
									error(ERR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
									break;

								case ENTRY_TYPE:
									error(ERR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);
									break;
								}
							} else {
								table_add_local_name(&(ZI196)->ast->table, p->u.literal);
							}
							if (p->is_ref) {
								error(ERR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables",
									ea->key, p->u.literal);
							}
						} else {
							if (!p->is_ref) {
								char *s;

								error(ERR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable",
									ea->key, p->u.literal);

								et = q->et; /* To avoid outputting that error more than once */
							}
						}
						break;
					}

					case ARG_RETURN:
						et = (ZI196)->ast->lexi_terminal_type;
						q->is_ref = 0;
						break;

					case ARG_IGNORE:
						/* always acceptable */
						et = q->et;
						p->is_ref = q->is_ref;
						break;

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
							error(ERR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						} else {
							error(ERR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						}
					}
				}

				if (p != NULL) {
					error(ERR_SERIOUS, "In call to action %s, too many results", ea->key);
				}

				if (q != NULL) {
					error(ERR_SERIOUS, "In call to action %s, not enough results", ea->key);
				}
			}

			/* TODO: only append if no error */
			{
				struct cmd **p;

				for (p = &(ZIf)->cmds; *p != NULL; p = &(*p)->next)
					;

				assert((ZIc)->next == NULL);
				(ZIc)->next = *p;
				*p = (ZIc);
			}
		}
	
#line 1157 "syntax.c"
		}
		/* END OF ACTION: add-cmd-to-list */
		ZR202 (ZI196, ZIf, &ZI200, &ZI201);
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
	*ZO201 = ZI201;
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
		/* BEGINNING OF INLINE: 216 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: param-list::param-list1 */
					goto ZL2_param_Hlist_C_Cparam_Hlist1;
					/* END OF INLINE: param-list::param-list1 */
				}
				UNREACHED;
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
#line 172 "syntax.act"

		assert((ZIz) != NULL);
		assert((ZIs) != NULL);
		assert((ZIt) != NULL);

		add_prepass((ZIz), (ZIs), (ZIt));
	
#line 1243 "syntax.c"
		}
		/* END OF ACTION: make-trigraph */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR181(SID_STRING *ZOe)
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
#line 685 "syntax.act"

			(ZIe) = NULL;
		error(ERR_SERIOUS, "Syntax error: expected characters");
	
#line 1278 "syntax.c"
		}
		/* END OF ACTION: E_expected_chars */
	}
ZL0:;
	*ZOe = ZIe;
}

static void
ZRcmd(zoneP ZIz, cmdP *ZOc)
{
	cmdP ZIc;

	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		argP ZIl;

		/* BEGINNING OF ACTION: empty-args-list */
		{
#line 242 "syntax.act"

		(ZIl) = NULL;
	
#line 1303 "syntax.c"
		}
		/* END OF ACTION: empty-args-list */
		ZR206 (&ZIz, &ZIl, &ZIc);
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
ZR183(zoneP *ZIz, frameP *ZOexit)
{
	frameP ZIexit;

	switch (CURRENT_TERMINAL) {
	case 10:
		{
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIexit);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: make-frame */
			{
#line 494 "syntax.act"

		(ZIexit) = add_frame();
	
#line 1344 "syntax.c"
			}
			/* END OF ACTION: make-frame */
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
	*ZOexit = ZIexit;
}

void
read_lex(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 39) {
		return;
	}
	{
		ZRcommand_Hlist (ZIz);
		/* BEGINNING OF INLINE: 188 */
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
#line 715 "syntax.act"

		error(ERR_SERIOUS, "Syntax error");
	
#line 1392 "syntax.c"
				}
				/* END OF ACTION: syntax-error */
			}
		ZL2:;
		}
		/* END OF INLINE: 188 */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR202(zoneP ZI196, frameP ZI199, zoneP *ZO200, frameP *ZO201)
{
	zoneP ZI200;
	frameP ZI201;

ZL2_202:;
	switch (CURRENT_TERMINAL) {
	case 20:
		{
			frameP ZIf;
			cmdP ZIc;

			ZIf = ZI199;
			ADVANCE_LEXER;
			ZRcmd (ZI196, &ZIc);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: add-cmd-to-list */
			{
#line 246 "syntax.act"

		if ((ZIc) != NULL) { /* if (ZIc) == NULL, an error has already been issued.*/
			unsigned return_count;

			return_count = cmd_return_count((ZIf)->cmds);

			if (return_count > 0 && (ZIc)->kind != CMD_DISCARD) {
				error(ERR_SERIOUS, "No cmd may follow an cmd that returns a terminal");
			}

			if ((ZIc)->kind == CMD_RETURN) {
				return_count++;
			}

			if ((ZIc)->kind == CMD_ACTION) {
				struct arg *lhs, *rhs;
				struct action *act;
				struct entry *ea;
				struct arg *p;
				struct param *q;

				return_count += arg_return_count((ZIc)->u.act.lhs);
				if (return_count > 1) {
					error(ERR_SERIOUS, "Only one terminal may be returned per token");
				}

				ea  = (ZIc)->u.act.ea;
				act = ea->u.act;
				rhs = (ZIc)->u.act.rhs;
				lhs = (ZIc)->u.act.lhs;

				/* CHECKING RHS COMPATIBILITY */
				for (p = rhs, q = act->in; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et = NULL;

					switch (p->kind) {
					case ARG_IDENT:
						et = local_find((ZIf)->locals, p->u.literal);
						if (et == NULL) {
							struct entry *e = table_get_entry(&(ZI196)->ast->table, p->u.literal);
							if (!e) {
								error(ERR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
								et = NULL;
							} else {
								switch (e->kind) {
								case ENTRY_LOCAL:
									error(ERR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
									et = NULL;
									break;

								case ENTRY_ACTION:
									error(ERR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
									et = NULL;
									break;

								case ENTRY_TYPE:
									error(ERR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
									et = NULL;
									break;

								default:
									UNREACHED;
								}
							}
						}
						break;

					case ARG_CHARP:
						/* TODO: assert(ast->lexi_string_type) */
						et = (ZI196)->ast->lexi_string_type;
						break;

					case ARG_CHAR_NUM:
						/* TODO: assert(ast->lexi_char_type) */
						et = (ZI196)->ast->lexi_char_type;
						break;

					case ARG_TERMINAL:
						/* TODO: assert(ast->lexi_terminal_type) */
						et = (ZI196)->ast->lexi_terminal_type;
						break;

					case ARG_CHAR_COUNT:
						/* TODO: assert(ast->lexi_int_type) */
						et = (ZI196)->ast->lexi_int_type;
						break;

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
							char *s3 = p->is_ref ? "&" : "";
							char *s4 = q->et->key;
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

							error(ERR_SERIOUS, "In call to action %s, argument \'%s%s\' has type \'%s%s\' when it should have type %s",
								ea->key, s6, s7, et->key, s3, s4, s5);
						}
					}
				}

				if (p != NULL) {
					error(ERR_SERIOUS, "In call to action %s, too many arguments", ea->key);
				}

				if (q != NULL) {
					error(ERR_SERIOUS, "In call to action %s, not enough arguments", ea->key);
				}

				for (p = lhs, q = act->out; p != NULL && q != NULL; p = p->next, q = q->next) {
					struct entry *et;

					switch (p->kind) {
					case ARG_IDENT: {
						et = local_find((ZIf)->locals, p->u.literal);
						if (et == NULL) {
							struct entry *e = table_get_entry(&(ZI196)->ast->table, p->u.literal);
							/* TODO: error out if local name already exists? */
							local_add(&(ZIf)->locals, p->u.literal, q->et);
							if (e) {
								switch (e->kind) {
								case ENTRY_ACTION:
									error(ERR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
									break;

								case ENTRY_TYPE:
									error(ERR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);
									break;
								}
							} else {
								table_add_local_name(&(ZI196)->ast->table, p->u.literal);
							}
							if (p->is_ref) {
								error(ERR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables",
									ea->key, p->u.literal);
							}
						} else {
							if (!p->is_ref) {
								char *s;

								error(ERR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable",
									ea->key, p->u.literal);

								et = q->et; /* To avoid outputting that error more than once */
							}
						}
						break;
					}

					case ARG_RETURN:
						et = (ZI196)->ast->lexi_terminal_type;
						q->is_ref = 0;
						break;

					case ARG_IGNORE:
						/* always acceptable */
						et = q->et;
						p->is_ref = q->is_ref;
						break;

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
							error(ERR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						} else {
							error(ERR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
						}
					}
				}

				if (p != NULL) {
					error(ERR_SERIOUS, "In call to action %s, too many results", ea->key);
				}

				if (q != NULL) {
					error(ERR_SERIOUS, "In call to action %s, not enough results", ea->key);
				}
			}

			/* TODO: only append if no error */
			{
				struct cmd **p;

				for (p = &(ZIf)->cmds; *p != NULL; p = &(*p)->next)
					;

				assert((ZIc)->next == NULL);
				(ZIc)->next = *p;
				*p = (ZIc);
			}
		}
	
#line 1665 "syntax.c"
			}
			/* END OF ACTION: add-cmd-to-list */
			/* BEGINNING OF INLINE: 202 */
			ZI199 = ZIf;
			goto ZL2_202;
			/* END OF INLINE: 202 */
		}
		UNREACHED;
	default:
		{
			ZI200 = ZI196;
			ZI201 = ZI199;
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
	*ZO200 = ZI200;
	*ZO201 = ZI201;
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
#line 707 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected begin action \'<\'");
	
#line 1730 "syntax.c"
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 1745 "syntax.c"
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
#line 711 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected end action \'>\'");
	
#line 1773 "syntax.c"
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
#line 643 "syntax.act"

		(ZIit) = NULL;
	
#line 1807 "syntax.c"
					}
					/* END OF ACTION: init-param */
					/* BEGINNING OF ACTION: init-param */
					{
#line 643 "syntax.act"

		(ZIot) = NULL;
	
#line 1816 "syntax.c"
					}
					/* END OF ACTION: init-param */
				}
				break;
			}
		}
		/* END OF INLINE: 135 */
		/* BEGINNING OF ACTION: make-action */
		{
#line 619 "syntax.act"

		struct entry *e;

		e = table_get_entry(&(ZIz)->ast->table, (ZIi));
		if (e != NULL) {
			switch (e->kind) {
			case ENTRY_ACTION:
				error(ERR_SERIOUS, "Action %s already exists", (ZIi));
				break;

			case ENTRY_LOCAL:
				error(ERR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.", (ZIi), (ZIi));
				break;

			case ENTRY_TYPE:
				error(ERR_SERIOUS, "Can't create action %s, %s has already been declared as a type", (ZIi), (ZIi));
				break;

			default:
				UNREACHED;
			}
		} else {
			table_add_action(&(ZIz)->ast->table, (ZIi), (ZIit), (ZIot));
		}
	
#line 1852 "syntax.c"
		}
		/* END OF ACTION: make-action */
	}
	return;
ZL1:;
	SAVE_LEXER (39);
	return;
}

static void
ZR204(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 1877 "syntax.c"
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
#line 168 "syntax.act"

		make_group ((*ZIz), (ZIi), (ZIs));
	
#line 1893 "syntax.c"
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
#line 160 "syntax.act"

		if ((*ZIz)->white) {
			error(ERR_SERIOUS, "White space group already defined");
		}

		(*ZIz)->white = make_group((*ZIz), "white", (ZIs));
	
#line 1924 "syntax.c"
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
ZR205(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 37:
		{
			frameP ZIf;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 10:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcmd_Hlist (*ZIz, &ZIf);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make-default */
			{
#line 513 "syntax.act"

		(*ZIz)->local = (ZIf);
		if (cmd_return_count((ZIf)->cmds)) {
			(*ZIz)->kind = ZONE_GENERAL;
		}
	
#line 1975 "syntax.c"
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
			frameP ZIf;
			cmdP ZIc;

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
			ZRcmd_Hlist (*ZIz, &ZIf);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: frame-cmds */
			{
#line 483 "syntax.act"

		assert((ZIf) != NULL);
		(ZIc) = (ZIf)->cmds;
	
#line 2014 "syntax.c"
			}
			/* END OF ACTION: frame-cmds */
			/* BEGINNING OF ACTION: check-cmds */
			{
#line 488 "syntax.act"

		if (cmd_return_count((ZIc)) > 1) {
			error(ERR_SERIOUS, "At most one return terminal may be specified per command list");
		}
	
#line 2025 "syntax.c"
			}
			/* END OF ACTION: check-cmds */
			/* BEGINNING OF ACTION: make-token */
			{
#line 498 "syntax.act"

		add_mainpass((*ZIz), (ZIs), (ZIf));
		if (cmd_return_count((ZIf)->cmds)) {
			(*ZIz)->kind = ZONE_GENERAL;
		}
	
#line 2037 "syntax.c"
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
ZR206(zoneP *ZIz, argP *ZIl, cmdP *ZOc)
{
	cmdP ZIc;

	switch (CURRENT_TERMINAL) {
	case 25:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-count */
			{
#line 138 "syntax.act"

		ZIb = add_arg(ARG_CHAR_COUNT, 0);
	
#line 2077 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-count */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 2087 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 719 "syntax.act"

		error(ERR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2096 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 2112 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2137 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2153 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2198 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 24:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-num */
			{
#line 134 "syntax.act"

		ZIb = add_arg(ARG_CHAR_NUM, numbuf);
	
#line 2216 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-num */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 2226 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 719 "syntax.act"

		error(ERR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2235 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 2251 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2276 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2292 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2337 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 23:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 130 "syntax.act"

		ZIb = add_arg(ARG_CHARP, 0);
	
#line 2355 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 2365 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
			{
#line 719 "syntax.act"

		error(ERR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 2374 "syntax.c"
			}
			/* END OF ACTION: E_sharp_arg_in_lhs */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 2390 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2415 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2431 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2476 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 27:
		{
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF EXTRACT: arg-ignore */
			{
#line 146 "syntax.act"

		ZIa = add_arg(ARG_IGNORE, 0);
	
#line 2493 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 2510 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2535 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2551 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2596 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 26:
		{
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF EXTRACT: arg-return */
			{
#line 142 "syntax.act"

		ZIa = add_arg(ARG_RETURN, 0);
	
#line 2613 "syntax.c"
			}
			/* END OF EXTRACT: arg-return */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 2630 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2655 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2671 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2716 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 28:
		{
			SID_STRING ZIi;
			argP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2735 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2751 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2796 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-discard-cmd */
			{
#line 184 "syntax.act"

		(ZIc) = add_cmd_discard();
	
#line 2810 "syntax.c"
			}
			/* END OF ACTION: make-discard-cmd */
		}
		break;
	case 0:
		{
			SID_STRING ZI207;
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF EXTRACT: ident */
			{
#line 93 "syntax.act"

		ZI207 = xstrdup(tokbuf);
	
#line 2828 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ident */
			{
#line 571 "syntax.act"

		(ZIa) = add_ident((ZI207));
	
#line 2838 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ident */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 2854 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2879 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 2895 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 2940 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 6:
		{
			SID_STRING ZIi;
			argP ZIr;

			ADVANCE_LEXER;
			ZRaction_Hcall_C_Clhs_Htuple1 (ZIl);
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 2984 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3000 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 3045 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 16:
		{
			SID_STRING ZI208;
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: ident */
				{
#line 93 "syntax.act"

		ZI208 = xstrdup(tokbuf);
	
#line 3066 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ref */
			{
#line 575 "syntax.act"

		(ZIa) = add_ref((ZI208));
	
#line 3080 "syntax.c"
			}
			/* END OF ACTION: make_arg_from_ref */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 3096 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 3121 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3137 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 3182 "syntax.c"
			}
			/* END OF ACTION: make-action-cmd */
		}
		break;
	case 1:
		{
			SID_STRING ZI209;

			/* BEGINNING OF EXTRACT: sid-ident */
			{
#line 118 "syntax.act"

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
				error (ERR_SERIOUS, "Identifier too long");
				break;
			}
		}
		buf[n] = 0;
		ZI209 = xstrdup(buf);
	
#line 3218 "syntax.c"
			}
			/* END OF EXTRACT: sid-ident */
			ADVANCE_LEXER;
			ZR210 (ZIz, ZIl, &ZI209, &ZIc);
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
			argP ZIr;

			/* BEGINNING OF EXTRACT: string */
			{
#line 122 "syntax.act"

		ZIb = xstrdup(tokbuf);
	
#line 3242 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 3252 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_arg_in_lhs */
			{
#line 723 "syntax.act"

		error(ERR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
	
#line 3261 "syntax.c"
			}
			/* END OF ACTION: E_string_arg_in_lhs */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 3277 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 3302 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3318 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 3363 "syntax.c"
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
		UNREACHED;
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
#line 715 "syntax.act"

		error(ERR_SERIOUS, "Syntax error");
	
#line 3415 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZR210(zoneP *ZIz, argP *ZIl, SID_STRING *ZI209, cmdP *ZOc)
{
	cmdP ZIc;

	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: make-terminal-cmd */
			{
#line 180 "syntax.act"

			(ZIc) = add_cmd_return((*ZI209));
	
#line 3435 "syntax.c"
			}
			/* END OF ACTION: make-terminal-cmd */
		}
		break;
	case 12:
		{
			argP ZIa;
			SID_STRING ZIi;
			argP ZIr;

			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 3452 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_terminal_in_lhs */
			{
#line 740 "syntax.act"

		error(ERR_SERIOUS, "Terminal argument in left handside");
	
#line 3461 "syntax.c"
			}
			/* END OF ACTION: E_terminal_in_lhs */
			/* BEGINNING OF ACTION: arg-append */
			{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 3477 "syntax.c"
			}
			/* END OF ACTION: arg-append */
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 3496 "syntax.c"
				}
				/* END OF EXTRACT: ident */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check-args-list */
			{
#line 236 "syntax.act"

		if (arg_return_count((*ZIl)) > 1) {
			error(ERR_SERIOUS, "There can only be one return terminal argument per action lhs");
		}
	
#line 3512 "syntax.c"
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
#line 191 "syntax.act"

		char *key;
		struct entry *ea;

		key = (ZIi);

		ea = table_get_entry(&(*ZIz)->ast->table, key);
		if (ea == NULL) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Unknown action %s", (ZIi));
		} else if (ea->kind != ENTRY_ACTION) {
			(ZIc) = NULL;
			error(ERR_SERIOUS, "Name %s is not an action", (ZIi));
		} else {
			char *dup;

			dup = arg_first_duplicate_ident((*ZIl));
			if (dup != NULL) {
				error(ERR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",
					ea->key, dup);
			}

			(ZIc) = add_cmd_action(ea, (*ZIl), (ZIr));
		}

		xfree((ZIi));
	
#line 3557 "syntax.c"
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
ZR213(argP *ZI211, argP *ZOr)
{
	argP ZIr;

	switch (CURRENT_TERMINAL) {
	case 20:
		{
			ADVANCE_LEXER;
			ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: arg-prepend */
			{
#line 227 "syntax.act"

		if ((*ZI211) != NULL) {
			assert((*ZI211)->next == NULL);

			(*ZI211)->next = (ZIr);
			(ZIr) = (*ZI211);
		}
	
#line 3598 "syntax.c"
			}
			/* END OF ACTION: arg-prepend */
		}
		break;
	default:
		{
			ZIr = *ZI211;
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
ZR215(zoneP *ZIz, paramP *ZIa)
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
#line 122 "syntax.act"

		ZIs = xstrdup(tokbuf);
	
#line 3668 "syntax.c"
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
		/* BEGINNING OF INLINE: 169 */
		{
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-global-zone */
				{
#line 587 "syntax.act"

	   (ZI0) = zone_isglobal((ZIz));
	
#line 3697 "syntax.c"
				}
				/* END OF ACTION: is-global-zone */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: make-keyword */
				{
#line 520 "syntax.act"

		switch ((ZIc)->kind) {
		case CMD_RETURN:
			/* Fallback is intentional */
			add_keyword((ZIz), (ZIs), (ZIc));
			break;

		default:
		  error(ERR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
		}
	
#line 3716 "syntax.c"
				}
				/* END OF ACTION: make-keyword */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
				{
#line 661 "syntax.act"

		error(ERR_SERIOUS, "Keywords not yet implemented in a non global zone ");
	
#line 3729 "syntax.c"
				}
				/* END OF ACTION: E_nonglobalzonekeyword */
			}
		ZL2:;
		}
		/* END OF INLINE: 169 */
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
			ZR204 (&ZIz);
			if ((CURRENT_TERMINAL) == 39) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 35:
		{
			ADVANCE_LEXER;
			ZR205 (&ZIz);
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
ZRaction_Hcall_C_Crhs_Htuple(argP *ZOr)
{
	argP ZIr;

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
#line 242 "syntax.act"

		(ZIr) = NULL;
	
#line 3886 "syntax.c"
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
#line 505 "syntax.act"

		(ZI0) = strlen((ZIs)) > 0;
	
#line 3933 "syntax.c"
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
#line 510 "syntax.act"

		error(ERR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");
	
#line 3948 "syntax.c"
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
#line 703 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected equal \'=\'");
	
#line 3988 "syntax.c"
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
#line 699 "syntax.act"

		error(ERR_SERIOUS, "Syntax error: expected arrow \'->\'");
	
#line 4018 "syntax.c"
		}
		/* END OF ACTION: E_expected_arrow */
	}
}

static void
ZRaction_Hcall_C_Clhs_Harg(argP *ZIl)
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
#line 138 "syntax.act"

		ZIb = add_arg(ARG_CHAR_COUNT, 0);
	
#line 4046 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-count */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4056 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 719 "syntax.act"

		error(ERR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4065 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 24:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-num */
					{
#line 134 "syntax.act"

		ZIb = add_arg(ARG_CHAR_NUM, numbuf);
	
#line 4080 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-num */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4090 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 719 "syntax.act"

		error(ERR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4099 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 23:
				{
					argP ZIb;

					/* BEGINNING OF EXTRACT: arg-char-string */
					{
#line 130 "syntax.act"

		ZIb = add_arg(ARG_CHARP, 0);
	
#line 4114 "syntax.c"
					}
					/* END OF EXTRACT: arg-char-string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4124 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
					{
#line 719 "syntax.act"

		error(ERR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
	
#line 4133 "syntax.c"
					}
					/* END OF ACTION: E_sharp_arg_in_lhs */
				}
				break;
			case 27:
				{
					/* BEGINNING OF EXTRACT: arg-ignore */
					{
#line 146 "syntax.act"

		ZIa = add_arg(ARG_IGNORE, 0);
	
#line 4146 "syntax.c"
					}
					/* END OF EXTRACT: arg-ignore */
					ADVANCE_LEXER;
				}
				break;
			case 26:
				{
					/* BEGINNING OF EXTRACT: arg-return */
					{
#line 142 "syntax.act"

		ZIa = add_arg(ARG_RETURN, 0);
	
#line 4160 "syntax.c"
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 4176 "syntax.c"
					}
					/* END OF EXTRACT: ident */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_ident */
					{
#line 571 "syntax.act"

		(ZIa) = add_ident((ZIi));
	
#line 4186 "syntax.c"
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 4204 "syntax.c"
						}
						/* END OF EXTRACT: ident */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_from_ref */
					{
#line 575 "syntax.act"

		(ZIa) = add_ref((ZIi));
	
#line 4218 "syntax.c"
					}
					/* END OF ACTION: make_arg_from_ref */
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: sid-ident */
					{
#line 118 "syntax.act"

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
				error (ERR_SERIOUS, "Identifier too long");
				break;
			}
		}
		buf[n] = 0;
		ZIb = xstrdup(buf);
	
#line 4254 "syntax.c"
					}
					/* END OF EXTRACT: sid-ident */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4264 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_terminal_in_lhs */
					{
#line 740 "syntax.act"

		error(ERR_SERIOUS, "Terminal argument in left handside");
	
#line 4273 "syntax.c"
					}
					/* END OF ACTION: E_terminal_in_lhs */
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					/* BEGINNING OF EXTRACT: string */
					{
#line 122 "syntax.act"

		ZIb = xstrdup(tokbuf);
	
#line 4288 "syntax.c"
					}
					/* END OF EXTRACT: string */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_arg_none */
					{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4298 "syntax.c"
					}
					/* END OF ACTION: make_arg_none */
					/* BEGINNING OF ACTION: E_string_arg_in_lhs */
					{
#line 723 "syntax.act"

		error(ERR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
	
#line 4307 "syntax.c"
					}
					/* END OF ACTION: E_string_arg_in_lhs */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 148 */
		/* BEGINNING OF ACTION: arg-append */
		{
#line 216 "syntax.act"

		if ((ZIa) != NULL) {
			struct arg **p;

			for (p = &(*ZIl); *p != NULL; p = &(*p)->next)
				;

			*p = (ZIa);
		}
	
#line 4330 "syntax.c"
		}
		/* END OF ACTION: arg-append */
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
#line 138 "syntax.act"

		ZIa = add_arg(ARG_CHAR_COUNT, 0);
	
#line 4354 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-count */
			ADVANCE_LEXER;
		}
		break;
	case 24:
		{
			/* BEGINNING OF EXTRACT: arg-char-num */
			{
#line 134 "syntax.act"

		ZIa = add_arg(ARG_CHAR_NUM, numbuf);
	
#line 4368 "syntax.c"
			}
			/* END OF EXTRACT: arg-char-num */
			ADVANCE_LEXER;
		}
		break;
	case 23:
		{
			/* BEGINNING OF EXTRACT: arg-char-string */
			{
#line 130 "syntax.act"

		ZIa = add_arg(ARG_CHARP, 0);
	
#line 4382 "syntax.c"
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
#line 146 "syntax.act"

		ZIb = add_arg(ARG_IGNORE, 0);
	
#line 4398 "syntax.c"
			}
			/* END OF EXTRACT: arg-ignore */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4408 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_ignore_in_rhs */
			{
#line 736 "syntax.act"

		error(ERR_SERIOUS, "Ignore argument in right handside");
	
#line 4417 "syntax.c"
			}
			/* END OF ACTION: E_ignore_in_rhs */
		}
		break;
	case 26:
		{
			argP ZIb;

			/* BEGINNING OF EXTRACT: arg-return */
			{
#line 142 "syntax.act"

		ZIb = add_arg(ARG_RETURN, 0);
	
#line 4432 "syntax.c"
			}
			/* END OF EXTRACT: arg-return */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4442 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_return_in_rhs */
			{
#line 727 "syntax.act"

		error(ERR_SERIOUS, "Return terminal argument in right handside");
	
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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
#line 4466 "syntax.c"
			}
			/* END OF EXTRACT: ident */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_from_ident */
			{
#line 571 "syntax.act"

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
#line 93 "syntax.act"

		ZIi = xstrdup(tokbuf);
	
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
#line 575 "syntax.act"

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
#line 118 "syntax.act"

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
				error (ERR_SERIOUS, "Identifier too long");
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
#line 579 "syntax.act"

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
#line 122 "syntax.act"

		ZIb = xstrdup(tokbuf);
	
#line 4569 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make_arg_none */
			{
#line 583 "syntax.act"

		(ZIa) = NULL;
	
#line 4579 "syntax.c"
			}
			/* END OF ACTION: make_arg_none */
			/* BEGINNING OF ACTION: E_string_in_action_rhs */
			{
#line 732 "syntax.act"

		error(ERR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusion."
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

#line 743 "syntax.act"

#line 4611 "syntax.c"

/* END OF FILE */
