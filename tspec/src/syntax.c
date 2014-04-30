/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 130 "syntax.act"


	/* $Id$ */

	/*
	 * Copyright 2011, The TenDRA Project.
	 * Copyright 1997, United Kingdom Secretary of State for Defence.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#include <time.h>
	#include <stddef.h>
	#include <string.h>

	#include <shared/bool.h>
	#include <shared/check.h>
	#include <shared/error.h>
	#include <shared/string.h>

	#include "object.h"
	#include "hash.h"
	#include "lex.h"
	#include "name.h"
	#include "syntax.h"
	#include "type.h"
	#include "utility.h"
	#include "variable.h"

	/*
	 * PARSER TYPES
	 *
	 * These types give the implementations of the various types used
	 * in the syntax.
	 */

	typedef char *SID_STRING;
	typedef type *SID_TYPE;

	typedef struct {
		char *iname;
		char *ename;
		int ivers;
		int evers;
	} SID_IDENTIFIER;

	/*
	 * CURRENT FIELD NAME
	 *
	 * The name of the current structure is stored during a +FIELD
	 * construct.
	 */

	static char *crt_field_name = NULL;
	static int anon_no = 0;

	/*
	 * CV-QUALIFIER NAMES
	 *
	 * This table gives the mapping between the values used to represent
	 * cv-qualifiers in the parser and the qualifier names used in the
	 * internal representation.
	 */

	static char *cv_qualifier [] = {
		NULL,
		"const",
		"volatile",
		"const volatile"
	};

	/*
	 * COMPILATION MODE
	 *
	 * We allow unreached code in the automatically generated sections.
	 */

	#if FS_TENDRA
	#pragma TenDRA begin
	#pragma TenDRA unreachable code allow
	#pragma TenDRA variable analysis off
	#endif

#line 97 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRsimple_Htype(SID_TYPE *);
static void ZRparameter_Hdeclaration(SID_TYPE *);
static void ZRnat_Hdeclarator_Hlist(SID_COMMAND *);
static void ZRtype_Hdeclarator_Hlist(SID_COMMAND *);
static void ZRfunction_Hoperator(SID_TYPE *);
static void ZRexp_Hdeclarator_Hlist(int, SID_TYPE, int, SID_COMMAND *);
static void ZRsubset_Hkey(SID_STRING *);
static void ZRmacro_Hparam_Hdeclaration(SID_TYPE *);
static void ZRifdef_Hmacro_Hname(SID_STRING *);
static void ZRdefine_Hparam_Hlist(SID_STRING *);
static void ZR287(SID_TYPE *);
static void ZRdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRidentifier(SID_IDENTIFIER *);
static void ZRsubset_Hcommand(SID_COMMAND *);
static void ZRqualified_Htype(SID_TYPE *);
static void ZRabstract_Hdeclarator(SID_STRING *, SID_TYPE *);
static void ZRparameter_Hlist(SID_TYPE *);
static void ZRinternal_Hname(SID_STRING *, int *);
static void ZR308(SID_STRING, SID_TYPE, SID_STRING *, SID_TYPE *);
static void ZRmacro_Hoperator(SID_TYPE *);
static void ZRenumerator_Hlist(SID_COMMAND *);
static void ZRexternal_Hname(SID_STRING *, int *);
static void ZRtype_Hqualifier(unsigned *);
static void ZRtype_Hkey(int *);
static void ZRtype_Hqualifier_Hopt(unsigned *);
static void ZRconstant_Hvalue(SID_STRING *);
static void ZR318(SID_IDENTIFIER, SID_TYPE, SID_IDENTIFIER *, SID_TYPE *);
static void ZRspec_Hcommand(SID_COMMAND *);
static void ZRfunc_Hcommand(int *);
static void ZR320(SID_STRING *, SID_STRING *);
static void ZR321(SID_STRING *, SID_STRING *, SID_STRING *);
static void ZRarray_Hoperator(SID_TYPE *);
static void ZR322(SID_COMMAND *);
static void ZR323(int *, SID_COMMAND *);
static void ZRmacro_Hparam_Hlist(SID_TYPE *);
static void ZR324(SID_STRING *, int *, SID_IDENTIFIER *);
static void ZR325(SID_STRING *);
static void ZR328(SID_STRING *, SID_STRING *);
static void ZRenum_Hcommand(int *);
static void ZRenumerator(SID_COMMAND *);
static void ZR329(int *);
static void ZRfield_Hdeclarator_Hlist(SID_TYPE, SID_TYPE, SID_COMMAND *);
static void ZR330(int *);
static void ZRfield_Hexact(bool *);
static void ZR333(SID_TYPE *, SID_TYPE *);
static void ZR335(SID_TYPE *);
static void ZRcommand_Hlist(SID_COMMAND *);
static void ZR338(SID_STRING *, SID_TYPE *, SID_STRING *, SID_TYPE *);
static void ZR339(SID_TYPE *);
static void ZR340(int *);
static void ZRdirect_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRtype_Hcommand(int *);
static void ZRtext_Hcommand(SID_COMMAND *);
static void ZR347(SID_IDENTIFIER *, SID_IDENTIFIER *, SID_TYPE *);
static void ZRname_Hversion(int *);
static void ZR348(int *);
static void ZRdirect_Habstract_Hdeclarator(SID_STRING *, SID_TYPE *);
static void ZRfield_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRvariable_Hcommand(void);
static void ZR349(int *);
static void ZR350(SID_TYPE *);
static void ZR351(SID_STRING *);
static void ZRdefine_Hparam_Hclause(SID_STRING *);
static void ZRexp_Hcommand(int *);
static void ZR352(SID_STRING *);
static void ZRif_Hcommand(SID_COMMAND *, SID_STRING *);
static void ZR353(SID_STRING *);
static void ZR354(SID_STRING *);
static void ZRbitfield_Hoperator(SID_TYPE *);
static void ZRuse_Hsubset_Hname(SID_STRING *);
extern void read_spec(SID_COMMAND *);
static void ZRmacro_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRsubset_Hname(SID_STRING *);
static void ZRbuiltin_Htype(unsigned *);
static void ZRobject_Hqualifier(int *);
static void ZRfield_Hlist(SID_TYPE, SID_COMMAND *);
static void ZRptr_Hoperator(SID_TYPE *);
static void ZRtype_Hkeyword(unsigned *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRsimple_Htype(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 32: case 34: case 37: case 38:
	case 39: case 42: case 43: case 46:
	case 47:
		{
			unsigned ZIb;

			ZRbuiltin_Htype (&ZIb);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_builtin */
			{
#line 277 "syntax.act"

		(ZIt) = basic_type ((ZIb));
	
#line 208 "syntax.c"
			}
			/* END OF ACTION: type_builtin */
		}
		break;
	case 0: case 35: case 44: case 45:
		{
			int ZItag;
			SID_STRING ZInm;

			ZRtype_Hkey (&ZItag);
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: name */
				{
#line 156 "syntax.act"
 ZInm = token_value; 
#line 225 "syntax.c"
				}
				/* END OF EXTRACT: name */
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_name */
			{
#line 281 "syntax.act"

		(ZIt) = find_type((ZInm), any_version, (ZItag), 1);
	
#line 242 "syntax.c"
			}
			/* END OF ACTION: type_name */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRparameter_Hdeclaration(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_TYPE ZIs;
		SID_STRING ZInm;
		SID_TYPE ZIp;

		ZRqualified_Htype (&ZIs);
		ZRabstract_Hdeclarator (&ZInm, &ZIp);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 285 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: param_name */
		{
#line 352 "syntax.act"

		UNUSED((ZInm));
	
#line 294 "syntax.c"
		}
		/* END OF ACTION: param_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRnat_Hdeclarator_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRidentifier (&ZIid);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_nat */
		{
#line 678 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_NAT);
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_NAT);
	
#line 331 "syntax.c"
		}
		/* END OF ACTION: declare_nat */
		/* BEGINNING OF INLINE: 250 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZRnat_Hdeclarator_Hlist (&ZIb);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 355 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 250 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 369 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRtype_Hdeclarator_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		int ZItag;
		SID_IDENTIFIER ZIid;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRtype_Hcommand (&ZItag);
		ZRidentifier (&ZIid);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_type */
		{
#line 714 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, (ZItag));
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_TYPE);
	
#line 408 "syntax.c"
		}
		/* END OF ACTION: declare_type */
		/* BEGINNING OF INLINE: 262 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZRtype_Hdeclarator_Hlist (&ZIb);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 432 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 262 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 446 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRfunction_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 56:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR335 (&ZIt);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRexp_Hdeclarator_Hlist(int ZIcmd, SID_TYPE ZIs, int ZIlv, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_TYPE ZIp;
		SID_TYPE ZIu;
		SID_TYPE ZIt;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRdeclarator (&ZIid, &ZIp);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 289 "syntax.act"

		(ZIu) = inject_type((ZIp), (ZIs));
	
#line 515 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: type_lvalue */
		{
#line 323 "syntax.act"

		(ZIt) = make_subtype((ZIu), (ZIlv));
	
#line 524 "syntax.c"
		}
		/* END OF ACTION: type_lvalue */
		/* BEGINNING OF ACTION: declare_exp */
		{
#line 647 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, (ZIcmd));
		p->u.u_type = check_type((ZIt), (ZIcmd));
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, p, (ZIcmd));
	
#line 535 "syntax.c"
		}
		/* END OF ACTION: declare_exp */
		/* BEGINNING OF INLINE: 228 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZRexp_Hdeclarator_Hlist (ZIcmd, ZIs, ZIlv, &ZIb);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 559 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 228 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 573 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRsubset_Hkey(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			ADVANCE_LEXER;
			ZR351 (&ZIkey);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: subset_both */
			{
#line 474 "syntax.act"
 (ZIkey) = "11"; 
#line 607 "syntax.c"
			}
			/* END OF ACTION: subset_both */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZRmacro_Hparam_Hdeclaration(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		int ZIlv;
		SID_TYPE ZIs;
		SID_STRING ZInm;
		SID_TYPE ZIp;
		SID_TYPE ZIu;

		ZRobject_Hqualifier (&ZIlv);
		ZRqualified_Htype (&ZIs);
		ZRabstract_Hdeclarator (&ZInm, &ZIp);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 289 "syntax.act"

		(ZIu) = inject_type((ZIp), (ZIs));
	
#line 651 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: type_lvalue */
		{
#line 323 "syntax.act"

		(ZIt) = make_subtype((ZIu), (ZIlv));
	
#line 660 "syntax.c"
		}
		/* END OF ACTION: type_lvalue */
		/* BEGINNING OF ACTION: param_name */
		{
#line 352 "syntax.act"

		UNUSED((ZInm));
	
#line 669 "syntax.c"
		}
		/* END OF ACTION: param_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRifdef_Hmacro_Hname(SID_STRING *ZOc)
{
	SID_STRING ZIc;

	switch (CURRENT_TERMINAL) {
	case 50:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_building */
			{
#line 394 "syntax.act"

		(ZIc) = BUILDING_MACRO;
	
#line 696 "syntax.c"
			}
			/* END OF ACTION: cond_building */
		}
		break;
	case 0:
		{
			/* BEGINNING OF EXTRACT: name */
			{
#line 156 "syntax.act"
 ZIc = token_value; 
#line 707 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
		}
		break;
	case 52:
		{
			SID_STRING ZIa;
			SID_STRING ZIb;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 56:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 158 "syntax.act"
 ZIa = token_value; 
#line 732 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 62:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 158 "syntax.act"
 ZIb = token_value; 
#line 753 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_protect */
			{
#line 398 "syntax.act"

		(ZIc) = macro_name(PROTECT_PREFIX, (ZIa), (ZIb), NULL);
	
#line 774 "syntax.c"
			}
			/* END OF ACTION: cond_protect */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRdefine_Hparam_Hlist(SID_STRING *ZOp)
{
	SID_STRING ZIp;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZI326;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: name */
			{
#line 156 "syntax.act"
 ZI326 = token_value; 
#line 809 "syntax.c"
			}
			/* END OF EXTRACT: name */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR328 (&ZI326, &ZIp);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR287(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			ZRmacro_Hoperator (&ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 273 "syntax.act"

		(ZIt) = NULL;
	
#line 854 "syntax.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 0: case 56:
		{
			ZRdirect_Hdeclarator (&ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 72:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRdeclarator (&ZIid, &ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 903 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZRidentifier(SID_IDENTIFIER *ZOid)
{
	SID_IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZInm;
		int ZIv;

		ZRinternal_Hname (&ZInm, &ZIv);
		ZR324 (&ZInm, &ZIv, &ZIid);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOid = ZIid;
}

static void
ZRsubset_Hcommand(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZIs;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		switch (CURRENT_TERMINAL) {
		case 23:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRsubset_Hname (&ZIs);
		switch (CURRENT_TERMINAL) {
		case 60:
			break;
		case 75:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: begin_subset */
		{
#line 523 "syntax.act"

		object *p = make_subset((ZIs));
		info *i = p->u.u_info;

		if (i->subset) {
			char *nm = subset_name(i->api, i->file, NULL);
			object *q = search_hash(subsets, nm, no_version);
			update_time(p, q);
		}

		(ZIa) = crt_object;
		crt_object = p;
	
#line 996 "syntax.c"
		}
		/* END OF ACTION: begin_subset */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcommand_Hlist (&ZIb);
		switch (CURRENT_TERMINAL) {
		case 55:
			break;
		case 75:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: end_subset */
		{
#line 540 "syntax.act"

		object *p = crt_object;

		if (p != NULL) {
			p->u.u_info->elements = (ZIb);
		}

		(ZIc) = make_object(NULL, OBJ_SET);
		(ZIc)->u.u_obj = p;
		crt_object = (ZIa);
	
#line 1031 "syntax.c"
		}
		/* END OF ACTION: end_subset */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRqualified_Htype(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 0: case 32: case 34: case 35:
	case 37: case 38: case 39: case 42:
	case 43: case 44: case 45: case 46:
	case 47:
		{
			SID_TYPE ZI331;

			ZRsimple_Htype (&ZI331);
			ZR333 (&ZI331, &ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 33: case 48:
		{
			unsigned ZIcv;
			SID_TYPE ZIs;

			ZRtype_Hqualifier (&ZIcv);
			ZRsimple_Htype (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_qualify */
			{
#line 318 "syntax.act"

		(ZIt) = make_subtype((ZIs), TYPE_QUALIFIER);
		(ZIt)->v.str = cv_qualifier[(ZIcv)];
	
#line 1082 "syntax.c"
			}
			/* END OF ACTION: type_qualify */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRabstract_Hdeclarator(SID_STRING *ZOnm, SID_TYPE *ZOt)
{
	SID_STRING ZInm;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	default:
		{
			ZRdirect_Habstract_Hdeclarator (&ZInm, &ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 72:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRabstract_Hdeclarator (&ZInm, &ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 1133 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOnm = ZInm;
	*ZOt = ZIt;
}

static void
ZRparameter_Hlist(SID_TYPE *ZOp)
{
	SID_TYPE ZIp;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_TYPE ZIt;
		SID_TYPE ZIq;

		ZRparameter_Hdeclaration (&ZIt);
		/* BEGINNING OF INLINE: 154 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZR339 (&ZIq);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: type_list_none */
					{
#line 333 "syntax.act"

		(ZIq) = NULL;
	
#line 1184 "syntax.c"
					}
					/* END OF ACTION: type_list_none */
				}
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 154 */
		/* BEGINNING OF ACTION: type_list_cons */
		{
#line 342 "syntax.act"

		(ZIp) = make_subtype ((ZIt), TYPE_LIST);
		(ZIp)->v.next = (ZIq);
	
#line 1202 "syntax.c"
		}
		/* END OF ACTION: type_list_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRinternal_Hname(SID_STRING *ZOnm, int *ZOv)
{
	SID_STRING ZInm;
	int ZIv;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: name */
			{
#line 156 "syntax.act"
 ZIa = token_value; 
#line 1232 "syntax.c"
			}
			/* END OF EXTRACT: name */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRname_Hversion (&ZIv);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: field_name */
		{
#line 426 "syntax.act"

		if (crt_field_name) {
			(ZInm) = string_printf("%s.%s", crt_field_name, (ZIa));
		} else {
			(ZInm) = (ZIa);
		}
	
#line 1255 "syntax.c"
		}
		/* END OF ACTION: field_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOnm = ZInm;
	*ZOv = ZIv;
}

static void
ZR308(SID_STRING ZI304, SID_TYPE ZI305, SID_STRING *ZO306, SID_TYPE *ZO307)
{
	SID_STRING ZI306;
	SID_TYPE ZI307;

ZL2_308:;
	switch (CURRENT_TERMINAL) {
	case 58:
		{
			SID_STRING ZInm;
			SID_TYPE ZIs;
			SID_TYPE ZIt;

			ZInm = ZI304;
			ZRarray_Hoperator (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZI305), (ZIs));
	
#line 1294 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF INLINE: 308 */
			ZI304 = ZInm;
			ZI305 = ZIt;
			goto ZL2_308;
			/* END OF INLINE: 308 */
		}
		/*UNREACHED*/
	default:
		{
			ZI306 = ZI304;
			ZI307 = ZI305;
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZO306 = ZI306;
	*ZO307 = ZI307;
}

static void
ZRmacro_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 56:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR350 (&ZIt);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRenumerator_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRenumerator (&ZIa);
		/* BEGINNING OF INLINE: 221 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZRenumerator_Hlist (&ZIb);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 1386 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 221 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 1403 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRexternal_Hname(SID_STRING *ZOnm, int *ZOv)
{
	SID_STRING ZInm;
	int ZIv;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIa;
			SID_STRING ZIb;

			/* BEGINNING OF EXTRACT: name */
			{
#line 156 "syntax.act"
 ZIa = token_value; 
#line 1431 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
			ZRname_Hversion (&ZIv);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: field_name */
			{
#line 426 "syntax.act"

		if (crt_field_name) {
			(ZIb) = string_printf("%s.%s", crt_field_name, (ZIa));
		} else {
			(ZIb) = (ZIa);
		}
	
#line 1450 "syntax.c"
			}
			/* END OF ACTION: field_name */
			/* BEGINNING OF ACTION: token_name */
			{
#line 433 "syntax.act"

		(ZInm) = token_name((ZIb));
	
#line 1459 "syntax.c"
			}
			/* END OF ACTION: token_name */
		}
		break;
	case 2:
		{
			/* BEGINNING OF EXTRACT: string */
			{
#line 158 "syntax.act"
 ZInm = token_value; 
#line 1470 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			ZRname_Hversion (&ZIv);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOnm = ZInm;
	*ZOv = ZIv;
}

static void
ZRtype_Hqualifier(unsigned *ZOcv)
{
	unsigned ZIcv;

	switch (CURRENT_TERMINAL) {
	case 33:
		{
			unsigned ZIa;

			ADVANCE_LEXER;
			ZRtype_Hqualifier_Hopt (&ZIa);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_const */
			{
#line 251 "syntax.act"

		if ((ZIa) & 1) {
			error(ERROR_SERIOUS, "Duplicate type qualifier");
		}

		(ZIcv) = ((ZIa) | 1);
	
#line 1521 "syntax.c"
			}
			/* END OF ACTION: cv_const */
		}
		break;
	case 48:
		{
			unsigned ZIa;

			ADVANCE_LEXER;
			ZRtype_Hqualifier_Hopt (&ZIa);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_volatile */
			{
#line 259 "syntax.act"

		if ((ZIa) & 2) {
			error(ERROR_SERIOUS, "Duplicate type qualifier");
		}

		(ZIcv) = ((ZIa) | 2);
	
#line 1546 "syntax.c"
			}
			/* END OF ACTION: cv_volatile */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

static void
ZRtype_Hkey(int *ZOtag)
{
	int ZItag;

	switch (CURRENT_TERMINAL) {
	case 35:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_enum_tag */
			{
#line 213 "syntax.act"
 (ZItag) = TYPE_ENUM_TAG;   
#line 1577 "syntax.c"
			}
			/* END OF ACTION: key_enum_tag */
		}
		break;
	case 44:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct_tag */
			{
#line 211 "syntax.act"
 (ZItag) = TYPE_STRUCT_TAG; 
#line 1589 "syntax.c"
			}
			/* END OF ACTION: key_struct_tag */
		}
		break;
	case 45:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union_tag */
			{
#line 212 "syntax.act"
 (ZItag) = TYPE_UNION_TAG;  
#line 1601 "syntax.c"
			}
			/* END OF ACTION: key_union_tag */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_type */
			{
#line 210 "syntax.act"
 (ZItag) = TYPE_GENERIC;    
#line 1612 "syntax.c"
			}
			/* END OF ACTION: key_type */
		}
		break;
	case 75:
		return;
	}
	*ZOtag = ZItag;
}

static void
ZRtype_Hqualifier_Hopt(unsigned *ZOcv)
{
	unsigned ZIcv;

	switch (CURRENT_TERMINAL) {
	case 33: case 48:
		{
			ZRtype_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cv_none */
			{
#line 247 "syntax.act"

		(ZIcv) = 0;
	
#line 1646 "syntax.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

static void
ZRconstant_Hvalue(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 67:
		{
			SID_STRING ZIa;

			ADVANCE_LEXER;
			ZRconstant_Hvalue (&ZIa);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: value_not */
			{
#line 370 "syntax.act"

		(ZIs) = xstrcat("!", (ZIa));
	
#line 1684 "syntax.c"
			}
			/* END OF ACTION: value_not */
		}
		break;
	case 5:
		{
			/* BEGINNING OF EXTRACT: insert */
			{
#line 161 "syntax.act"
 ZIs = token_value; 
#line 1695 "syntax.c"
			}
			/* END OF EXTRACT: insert */
			ADVANCE_LEXER;
		}
		break;
	case 68:
		{
			SID_STRING ZIa;

			ADVANCE_LEXER;
			ZRconstant_Hvalue (&ZIa);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: value_negate */
			{
#line 366 "syntax.act"

		(ZIs) = xstrcat("-", (ZIa));
	
#line 1717 "syntax.c"
			}
			/* END OF ACTION: value_negate */
		}
		break;
	case 0:
		{
			SID_STRING ZIa;

			/* BEGINNING OF EXTRACT: name */
			{
#line 156 "syntax.act"
 ZIa = token_value; 
#line 1730 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: value_nat */
			{
#line 376 "syntax.act"

		object *p;

		p = search_hash(exps, (ZIa), any_version);
		if (p == NULL) {
			error(ERROR_SERIOUS, "Undefined NAT, '%s'", (ZIa));
		} else if (p->objtype != OBJ_NAT) {
			error(ERROR_SERIOUS, "'%s' is not a NAT", (ZIa));
		}

		(ZIs) = (ZIa);
	
#line 1749 "syntax.c"
			}
			/* END OF ACTION: value_nat */
		}
		break;
	case 1:
		{
			/* BEGINNING OF EXTRACT: number */
			{
#line 157 "syntax.act"
 ZIs = token_value; 
#line 1760 "syntax.c"
			}
			/* END OF EXTRACT: number */
			ADVANCE_LEXER;
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZR318(SID_IDENTIFIER ZI312, SID_TYPE ZI313, SID_IDENTIFIER *ZO316, SID_TYPE *ZO317)
{
	SID_IDENTIFIER ZI316;
	SID_TYPE ZI317;

ZL2_318:;
	switch (CURRENT_TERMINAL) {
	case 56: case 58:
		{
			SID_IDENTIFIER ZIid;

			ZIid = ZI312;
			/* BEGINNING OF INLINE: 334 */
			{
				switch (CURRENT_TERMINAL) {
				case 58:
					{
						SID_TYPE ZIs;
						SID_TYPE ZIt;

						ZRarray_Hoperator (&ZIs);
						if ((CURRENT_TERMINAL) == 75) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: type_inject */
						{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZI313), (ZIs));
	
#line 1811 "syntax.c"
						}
						/* END OF ACTION: type_inject */
						/* BEGINNING OF INLINE: 318 */
						ZI312 = ZIid;
						ZI313 = ZIt;
						goto ZL2_318;
						/* END OF INLINE: 318 */
					}
					/*UNREACHED*/
				case 56:
					{
						SID_TYPE ZIs;
						SID_TYPE ZIt;

						ZRfunction_Hoperator (&ZIs);
						if ((CURRENT_TERMINAL) == 75) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: type_inject */
						{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZI313), (ZIs));
	
#line 1837 "syntax.c"
						}
						/* END OF ACTION: type_inject */
						/* BEGINNING OF INLINE: 318 */
						ZI312 = ZIid;
						ZI313 = ZIt;
						goto ZL2_318;
						/* END OF INLINE: 318 */
					}
					/*UNREACHED*/
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 334 */
		}
		/*UNREACHED*/
	default:
		{
			ZI316 = ZI312;
			ZI317 = ZI313;
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZO316 = ZI316;
	*ZO317 = ZI317;
}

static void
ZRspec_Hcommand(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 7:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_base */
			{
#line 581 "syntax.act"

		(ZIc) = NULL;
	
#line 1887 "syntax.c"
			}
			/* END OF ACTION: declare_base */
		}
		break;
	case 9:
		{
			SID_IDENTIFIER ZIid;
			SID_STRING ZIp;
			SID_STRING ZIs;

			ADVANCE_LEXER;
			ZRidentifier (&ZIid);
			ZRdefine_Hparam_Hclause (&ZIp);
			ZRconstant_Hvalue (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_define */
			{
#line 600 "syntax.act"

		char *def;
		object *p;

		p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_DEFINE);
		if ((ZIp)) {
			if (*(ZIp)) {
				def = string_printf ("( %s ) %s", (ZIp), (ZIs));
			} else {
				def = string_printf("() %s", (ZIs));
			}
		} else {
			def = string_printf(" %s", (ZIs));
		}

		p->u.u_str = def;
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_EXTERN);
	
#line 1927 "syntax.c"
			}
			/* END OF ACTION: declare_define */
		}
		break;
	case 30:
		{
			SID_IDENTIFIER ZIid;
			SID_STRING ZIp;
			SID_STRING ZIs;

			ADVANCE_LEXER;
			ZRidentifier (&ZIid);
			ZRdefine_Hparam_Hclause (&ZIp);
			ZRconstant_Hvalue (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_defmin */
			{
#line 619 "syntax.act"

		char *def;
		object *p;

		p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_DEFMIN);
		if ((ZIp)) {
			if ( *(ZIp) ) {
				def = string_printf("( %s ) %s", (ZIp), (ZIs));
			} else {
				def = string_printf("() %s", (ZIs));
			}
		} else {
			def = string_printf(" %s", (ZIs));
		}

		p->u.u_str = def;
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_EXTERN);
	
#line 1967 "syntax.c"
			}
			/* END OF ACTION: declare_defmin */
		}
		break;
	case 12:
		{
			int ZItag;
			SID_IDENTIFIER ZIid;
			SID_COMMAND ZIe;

			ADVANCE_LEXER;
			ZRenum_Hcommand (&ZItag);
			ZRidentifier (&ZIid);
			switch (CURRENT_TERMINAL) {
			case 60:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRenumerator_Hlist (&ZIe);
			switch (CURRENT_TERMINAL) {
			case 55:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_enum */
			{
#line 635 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, (ZItag));
		t->v.obj2 = (ZIe);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_TYPE);
	
#line 2017 "syntax.c"
			}
			/* END OF ACTION: declare_enum */
		}
		break;
	case 14:
		{
			int ZItag;
			SID_IDENTIFIER ZIid;
			bool ZIe;
			SID_TYPE ZIt;
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;

			ADVANCE_LEXER;
			ZRtype_Hcommand (&ZItag);
			ZRidentifier (&ZIid);
			ZRfield_Hexact (&ZIe);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: begin_field */
			{
#line 732 "syntax.act"

		(ZIt) = find_type ((ZIid).iname, any_version, (ZItag), 0);
		if ((ZIt) == NULL) {
			(ZIt) = make_type((ZIid).iname, (ZIid).ivers, (ZItag));
			(ZIa) = make_token((ZIid).ename, (ZIid).evers, (ZIt)->u.obj, OBJ_TYPE);
		} else {
			(ZIa) = NULL;
		}

		(ZIt) = expand_type((ZIt));
		switch ((ZIt)->id) {
		case TYPE_STRUCT:
		case TYPE_UNION:
		case TYPE_STRUCT_TAG:
		case TYPE_UNION_TAG:
			break;

		default:
			error(ERROR_SERIOUS, "Illegal field type, '%s'", (ZIid).iname);
			break;
		}
		crt_field_name = (ZIt)->u.obj->name;
	
#line 2065 "syntax.c"
			}
			/* END OF ACTION: begin_field */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRfield_Hlist (ZIt, &ZIb);
			switch (CURRENT_TERMINAL) {
			case 55:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: end_field */
			{
#line 756 "syntax.act"

		if ((ZIe)) {
			if ((ZIt)->v.obj2) {
				char *nm = crt_field_name;
				error(ERROR_SERIOUS, "Redefinition of type '%s'", nm);
			}

			if ((ZIb) == NULL) {
				error ( ERROR_SERIOUS, "Empty struct/union definition" );
			} else {
				(ZIt)->v.obj2 = (ZIb);
			}

			if ((ZIa) != NULL) {
				(ZIc) = (ZIa);
			} else {
				/* This is a hack, do properly later */
				(ZIc) = make_object(NULL, OBJ_TYPE);
				(ZIc)->u.u_type = (ZIt);
				if (0 == strcmp ( (ZIc)->filename, (ZIt)->u.obj->filename )) {
					(ZIt)->state = 1;
				} else {
					(ZIt)->state = 3;
				}
			}
		} else {
			(ZIc) = join_object((ZIa), (ZIb));
		}
		crt_field_name = NULL;
	
#line 2119 "syntax.c"
			}
			/* END OF ACTION: end_field */
		}
		break;
	case 19:
		{
			int ZIcmd;
			SID_STRING ZIs;
			SID_STRING ZIkey;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_implement */
			{
#line 505 "syntax.act"
 (ZIcmd) = OBJ_IMPLEMENT; 
#line 2135 "syntax.c"
			}
			/* END OF ACTION: cmd_implement */
			ZRsubset_Hname (&ZIs);
			ZRsubset_Hkey (&ZIkey);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: include_subset */
			{
#line 549 "syntax.act"

		object *p = make_subset((ZIs));
		update_time(crt_object, p);
		(ZIc) = make_object((ZIkey), (ZIcmd));
		(ZIc)->u.u_obj = p;
	
#line 2153 "syntax.c"
			}
			/* END OF ACTION: include_subset */
		}
		break;
	case 21:
		{
			int ZIlv;
			SID_TYPE ZIs;
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIp;
			SID_TYPE ZIu;
			SID_TYPE ZIv;
			SID_TYPE ZIq;
			SID_TYPE ZIt;

			ADVANCE_LEXER;
			ZRobject_Hqualifier (&ZIlv);
			ZRqualified_Htype (&ZIs);
			ZRmacro_Hdeclarator (&ZIid, &ZIp);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIu) = inject_type((ZIp), (ZIs));
	
#line 2183 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: type_lvalue */
			{
#line 323 "syntax.act"

		(ZIv) = make_subtype((ZIu), (ZIlv));
	
#line 2192 "syntax.c"
			}
			/* END OF ACTION: type_lvalue */
			ZR287 (&ZIq);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIq), (ZIv));
	
#line 2206 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_macro */
			{
#line 668 "syntax.act"

		object *p;
		int cmd = OBJ_MACRO;

		if ((ZIt)->id != TYPE_PROC) {
			cmd = OBJ_EXP;
		}

		p = make_exp((ZIid).iname, (ZIid).ivers, cmd);
		p->u.u_type = check_type((ZIt), cmd);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, cmd);
	
#line 2224 "syntax.c"
			}
			/* END OF ACTION: declare_macro */
		}
		break;
	case 22:
		{
			ADVANCE_LEXER;
			ZRnat_Hdeclarator_Hlist (&ZIc);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 24:
		{
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIt;

			ADVANCE_LEXER;
			ZRidentifier (&ZIid);
			ZR287 (&ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_stmt */
			{
#line 702 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_STATEMENT);
		p->u.u_type = check_type((ZIt), OBJ_STATEMENT);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_STATEMENT);
	
#line 2259 "syntax.c"
			}
			/* END OF ACTION: declare_stmt */
		}
		break;
	case 26:
		{
			SID_IDENTIFIER ZIid;
			SID_STRING ZIs;

			ADVANCE_LEXER;
			ZRidentifier (&ZIid);
			switch (CURRENT_TERMINAL) {
			case 5:
				/* BEGINNING OF EXTRACT: insert */
				{
#line 161 "syntax.act"
 ZIs = token_value; 
#line 2277 "syntax.c"
				}
				/* END OF EXTRACT: insert */
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_token */
			{
#line 708 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_TOKEN);
		p->u.u_str = (ZIs);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_TOKEN);
	
#line 2296 "syntax.c"
			}
			/* END OF ACTION: declare_token */
		}
		break;
	case 27:
		{
			ADVANCE_LEXER;
			ZRtype_Hdeclarator_Hlist (&ZIc);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 28:
		{
			ADVANCE_LEXER;
			ZR322 (&ZIc);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 29:
		{
			int ZIcmd;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_use */
			{
#line 506 "syntax.act"
 (ZIcmd) = OBJ_USE;       
#line 2330 "syntax.c"
			}
			/* END OF ACTION: cmd_use */
			ZR323 (&ZIcmd, &ZIc);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8: case 13:
		{
			int ZIcmd;
			int ZIlv1;
			int ZIlv;
			SID_TYPE ZIt;

			ZRexp_Hcommand (&ZIcmd);
			ZRobject_Hqualifier (&ZIlv1);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: key_exp */
			{
#line 227 "syntax.act"

		if ((ZIcmd) == OBJ_CONST) {
			if ((ZIlv1) == TYPE_LVALUE) {
				error(ERROR_SERIOUS, "Constant can't be an lvalue");
			}
			(ZIlv) = TYPE_RVALUE;
		} else if ((ZIcmd) == OBJ_EXTERN) {
			(ZIlv) = TYPE_LVALUE;
		} else {
			(ZIlv) = (ZIlv1);
		}
	
#line 2368 "syntax.c"
			}
			/* END OF ACTION: key_exp */
			ZRqualified_Htype (&ZIt);
			ZRexp_Hdeclarator_Hlist (ZIcmd, ZIt, ZIlv, &ZIc);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 15:
		{
			int ZIcmd;
			SID_TYPE ZIs;
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIp;
			SID_TYPE ZIt;

			ZRfunc_Hcommand (&ZIcmd);
			ZRqualified_Htype (&ZIs);
			ZRdeclarator (&ZIid, &ZIp);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 2400 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_func */
			{
#line 659 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, (ZIcmd));
		p->u.u_type = check_type((ZIt), OBJ_FUNC);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, (ZIcmd));
	
#line 2411 "syntax.c"
			}
			/* END OF ACTION: declare_func */
		}
		break;
	case 23:
		{
			ZRsubset_Hcommand (&ZIc);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRfunc_Hcommand(int *ZOcmd)
{
	int ZIcmd;

	if ((CURRENT_TERMINAL) == 75) {
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
		ZR348 (&ZIcmd);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR320(SID_STRING *ZIa, SID_STRING *ZOs)
{
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 62:
		{
			SID_STRING ZIb;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 158 "syntax.act"
 ZIb = token_value; 
#line 2485 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR321 (ZIa, &ZIb, &ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: api_name */
			{
#line 478 "syntax.act"

		(ZIs) = subset_name((*ZIa), NULL, NULL);
	
#line 2508 "syntax.c"
			}
			/* END OF ACTION: api_name */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZR321(SID_STRING *ZIa, SID_STRING *ZIb, SID_STRING *ZOs)
{
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 62:
		{
			SID_STRING ZIc;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 158 "syntax.act"
 ZIc = token_value; 
#line 2541 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_name */
			{
#line 486 "syntax.act"

		if ((*ZIb)[0] == 0) {
			(*ZIb) = NULL;
		}

		(ZIs) = subset_name((*ZIa), (*ZIb), (ZIc));
	
#line 2559 "syntax.c"
			}
			/* END OF ACTION: subset_name */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: file_name */
			{
#line 482 "syntax.act"

		(ZIs) = subset_name((*ZIa), (*ZIb), NULL);
	
#line 2572 "syntax.c"
			}
			/* END OF ACTION: file_name */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRarray_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 58:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 140 */
		{
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 5: case 67:
			case 68:
				{
					ZRconstant_Hvalue (&ZIa);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: value_none */
					{
#line 362 "syntax.act"

		(ZIa) = "";
	
#line 2627 "syntax.c"
					}
					/* END OF ACTION: value_none */
				}
				break;
			}
		}
		/* END OF INLINE: 140 */
		switch (CURRENT_TERMINAL) {
		case 59:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: type_array */
		{
#line 298 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_ARRAY);
		(ZIt)->v.str = (ZIa);
	
#line 2649 "syntax.c"
		}
		/* END OF ACTION: type_array */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZR322(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 51:
		{
			SID_TYPE ZIt;
			SID_IDENTIFIER ZIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 56:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRqualified_Htype (&ZIt);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRidentifier (&ZIid);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_promote */
			{
#line 683 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, TYPE_PROMOTE);
		type *s = expand_type((ZIt));

		switch (s->id) {
		case TYPE_INT:
		case TYPE_SIGNED:
		case TYPE_UNSIGNED:
			break;

		default:
			error(ERROR_SERIOUS, "Non-integral promotion type");
			break;
		}

		t->v.next = s;
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN);
	
#line 2717 "syntax.c"
			}
			/* END OF ACTION: declare_promote */
		}
		break;
	case 53:
		{
			SID_STRING ZIs;
			SID_TYPE ZIt;
			SID_IDENTIFIER ZIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 56:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 158 "syntax.act"
 ZIs = token_value; 
#line 2742 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_special */
			{
#line 285 "syntax.act"

		(ZIt) = special_type((ZIs));
	
#line 2763 "syntax.c"
			}
			/* END OF ACTION: type_special */
			ZRidentifier (&ZIid);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_typedef */
			{
#line 719 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, TYPE_DEFINED);
		t->v.next = check_type((ZIt), OBJ_TYPE);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN);
	
#line 2779 "syntax.c"
			}
			/* END OF ACTION: declare_typedef */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 42: case 43: case 44: case 45:
	case 46: case 47: case 48:
		{
			SID_TYPE ZIs;
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIp;
			SID_TYPE ZIt;

			ZRqualified_Htype (&ZIs);
			ZRdeclarator (&ZIid, &ZIp);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 2806 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_typedef */
			{
#line 719 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, TYPE_DEFINED);
		t->v.next = check_type((ZIt), OBJ_TYPE);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN);
	
#line 2817 "syntax.c"
			}
			/* END OF ACTION: declare_typedef */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR323(int *ZIcmd, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 2:
		{
			SID_STRING ZIs;
			SID_STRING ZIkey;

			ZRsubset_Hname (&ZIs);
			ZRsubset_Hkey (&ZIkey);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: include_subset */
			{
#line 549 "syntax.act"

		object *p = make_subset((ZIs));
		update_time(crt_object, p);
		(ZIc) = make_object((ZIkey), (*ZIcmd));
		(ZIc)->u.u_obj = p;
	
#line 2861 "syntax.c"
			}
			/* END OF ACTION: include_subset */
		}
		break;
	case 56:
		{
			SID_STRING ZIs;
			SID_STRING ZIkey1;
			SID_STRING ZIkey;

			ZRuse_Hsubset_Hname (&ZIs);
			ZRsubset_Hkey (&ZIkey1);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subset_next */
			{
#line 475 "syntax.act"
 (ZIkey) = xstrcat((ZIkey1), "G"); 
#line 2882 "syntax.c"
			}
			/* END OF ACTION: subset_next */
			/* BEGINNING OF ACTION: include_subset */
			{
#line 549 "syntax.act"

		object *p = make_subset((ZIs));
		update_time(crt_object, p);
		(ZIc) = make_object((ZIkey), (*ZIcmd));
		(ZIc)->u.u_obj = p;
	
#line 2894 "syntax.c"
			}
			/* END OF ACTION: include_subset */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRmacro_Hparam_Hlist(SID_TYPE *ZOp)
{
	SID_TYPE ZIp;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_TYPE ZIt;
		SID_TYPE ZIq;

		ZRmacro_Hparam_Hdeclaration (&ZIt);
		/* BEGINNING OF INLINE: 162 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZRmacro_Hparam_Hlist (&ZIq);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: type_list_none */
					{
#line 333 "syntax.act"

		(ZIq) = NULL;
	
#line 2946 "syntax.c"
					}
					/* END OF ACTION: type_list_none */
				}
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 162 */
		/* BEGINNING OF ACTION: type_list_cons */
		{
#line 342 "syntax.act"

		(ZIp) = make_subtype ((ZIt), TYPE_LIST);
		(ZIp)->v.next = (ZIq);
	
#line 2964 "syntax.c"
		}
		/* END OF ACTION: type_list_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR324(SID_STRING *ZInm, int *ZIv, SID_IDENTIFIER *ZOid)
{
	SID_IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 69:
		{
			SID_STRING ZItnm;
			int ZItv;

			ADVANCE_LEXER;
			ZRexternal_Hname (&ZItnm, &ZItv);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make_id */
			{
#line 437 "syntax.act"

		(ZIid).iname = (*ZInm);
		(ZIid).ivers = (*ZIv);
		(ZIid).ename = (ZItnm);
		(ZIid).evers = (ZItv);
	
#line 3002 "syntax.c"
			}
			/* END OF ACTION: make_id */
		}
		break;
	default:
		{
			SID_STRING ZItnm;

			/* BEGINNING OF ACTION: token_name */
			{
#line 433 "syntax.act"

		(ZItnm) = token_name((*ZInm));
	
#line 3017 "syntax.c"
			}
			/* END OF ACTION: token_name */
			/* BEGINNING OF ACTION: make_id */
			{
#line 437 "syntax.act"

		(ZIid).iname = (*ZInm);
		(ZIid).ivers = (*ZIv);
		(ZIid).ename = (ZItnm);
		(ZIid).evers = (*ZIv);
	
#line 3029 "syntax.c"
			}
			/* END OF ACTION: make_id */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOid = ZIid;
}

static void
ZR325(SID_STRING *ZOp)
{
	SID_STRING ZIp;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_empty */
			{
#line 408 "syntax.act"
 (ZIp) = "";   
#line 3058 "syntax.c"
			}
			/* END OF ACTION: param_empty */
		}
		break;
	case 0:
		{
			ZRdefine_Hparam_Hlist (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR328(SID_STRING *ZI326, SID_STRING *ZOp)
{
	SID_STRING ZIp;

	switch (CURRENT_TERMINAL) {
	case 62:
		{
			SID_STRING ZIq;

			ADVANCE_LEXER;
			ZRdefine_Hparam_Hlist (&ZIq);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: param_join */
			{
#line 411 "syntax.act"

		(ZIp) = string_printf("%s, %s", (*ZI326), (ZIq));
	
#line 3113 "syntax.c"
			}
			/* END OF ACTION: param_join */
		}
		break;
	default:
		{
			ZIp = *ZI326;
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRenum_Hcommand(int *ZOtag)
{
	int ZItag;

	switch (CURRENT_TERMINAL) {
	case 35:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_enum_tag */
			{
#line 213 "syntax.act"
 (ZItag) = TYPE_ENUM_TAG;   
#line 3147 "syntax.c"
			}
			/* END OF ACTION: key_enum_tag */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_enum */
			{
#line 216 "syntax.act"
 (ZItag) = TYPE_ENUM;       
#line 3158 "syntax.c"
			}
			/* END OF ACTION: key_enum */
		}
		break;
	case 75:
		return;
	}
	*ZOtag = ZItag;
}

static void
ZRenumerator(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_STRING ZIs;

		ZRidentifier (&ZIid);
		/* BEGINNING OF INLINE: 219 */
		{
			switch (CURRENT_TERMINAL) {
			case 66:
				{
					ADVANCE_LEXER;
					ZRconstant_Hvalue (&ZIs);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: value_none */
					{
#line 362 "syntax.act"

		(ZIs) = "";
	
#line 3203 "syntax.c"
					}
					/* END OF ACTION: value_none */
				}
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 219 */
		/* BEGINNING OF ACTION: declare_enumerator */
		{
#line 641 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_ENUMVAL);
		p->u.u_str = (ZIs);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_EXTERN);
	
#line 3222 "syntax.c"
		}
		/* END OF ACTION: declare_enumerator */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR329(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			ADVANCE_LEXER;
			ZR330 (&ZIcmd);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cmd_exp */
			{
#line 500 "syntax.act"
 (ZIcmd) = OBJ_EXP;       
#line 3256 "syntax.c"
			}
			/* END OF ACTION: cmd_exp */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZRfield_Hdeclarator_Hlist(SID_TYPE ZIm, SID_TYPE ZIs, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_TYPE ZIp;
		SID_TYPE ZIt;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRfield_Hdeclarator (&ZIid, &ZIp);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 3298 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: declare_field */
		{
#line 653 "syntax.act"

		type *t = check_type((ZIt), OBJ_FIELD);
		field *f = make_field((ZIid).iname, (ZIid).ivers, (ZIm), t);
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, f->obj, OBJ_FIELD);
	
#line 3309 "syntax.c"
		}
		/* END OF ACTION: declare_field */
		/* BEGINNING OF INLINE: 238 */
		{
			switch (CURRENT_TERMINAL) {
			case 62:
				{
					ADVANCE_LEXER;
					ZRfield_Hdeclarator_Hlist (ZIm, ZIs, &ZIb);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 3333 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 238 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 3347 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR330(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 33:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_constant */
			{
#line 499 "syntax.act"
 (ZIcmd) = OBJ_CONST;     
#line 3379 "syntax.c"
			}
			/* END OF ACTION: cmd_constant */
		}
		break;
	case 36:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_exp_extern */
			{
#line 501 "syntax.act"
 (ZIcmd) = OBJ_EXTERN;    
#line 3398 "syntax.c"
			}
			/* END OF ACTION: cmd_exp_extern */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZRfield_Hexact(bool *ZOe)
{
	bool ZIe;

	switch (CURRENT_TERMINAL) {
	case 60:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: true */
			{
#line 173 "syntax.act"
 (ZIe) = 1; 
#line 3429 "syntax.c"
			}
			/* END OF ACTION: true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: false */
			{
#line 172 "syntax.act"
 (ZIe) = 0; 
#line 3440 "syntax.c"
			}
			/* END OF ACTION: false */
		}
		break;
	case 75:
		return;
	}
	*ZOe = ZIe;
}

static void
ZR333(SID_TYPE *ZI331, SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 33: case 48:
		{
			unsigned ZIcv;

			ZRtype_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_qualify */
			{
#line 318 "syntax.act"

		(ZIt) = make_subtype((*ZI331), TYPE_QUALIFIER);
		(ZIt)->v.str = cv_qualifier[(ZIcv)];
	
#line 3473 "syntax.c"
			}
			/* END OF ACTION: type_qualify */
		}
		break;
	default:
		{
			ZIt = *ZI331;
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZR335(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			SID_TYPE ZIp;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_list_empty */
			{
#line 338 "syntax.act"

		error(ERROR_WARNING, "Empty parameter list");
		(ZIp) = NULL;
	
#line 3512 "syntax.c"
			}
			/* END OF ACTION: type_list_empty */
			/* BEGINNING OF ACTION: type_func */
			{
#line 308 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 3522 "syntax.c"
			}
			/* END OF ACTION: type_func */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 42: case 43: case 44: case 45:
	case 46: case 47: case 48:
		{
			SID_TYPE ZIp;

			ZRparameter_Hlist (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_func */
			{
#line 308 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 3552 "syntax.c"
			}
			/* END OF ACTION: type_func */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRcommand_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

ZL2_command_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 7: case 8: case 9: case 12:
	case 13: case 14: case 15: case 19:
	case 21: case 22: case 23: case 24:
	case 26: case 27: case 28: case 29:
	case 30:
		{
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;

			ZRspec_Hcommand (&ZIa);
			switch (CURRENT_TERMINAL) {
			case 71:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcommand_Hlist (&ZIb);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 3608 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	case 4: case 5: case 6: case 16:
	case 17: case 18:
		{
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;

			ZRtext_Hcommand (&ZIa);
			ZRcommand_Hlist (&ZIb);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 3631 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	case 3: case 20:
		{
			ZRvariable_Hcommand ();
			switch (CURRENT_TERMINAL) {
			case 71:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: command-list */
			goto ZL2_command_Hlist;
			/* END OF INLINE: command-list */
		}
		/*UNREACHED*/
	default:
		{
			/* BEGINNING OF ACTION: command_none */
			{
#line 515 "syntax.act"

		(ZIc) = NULL;
	
#line 3662 "syntax.c"
			}
			/* END OF ACTION: command_none */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR338(SID_STRING *ZI336, SID_TYPE *ZI337, SID_STRING *ZO306, SID_TYPE *ZO307)
{
	SID_STRING ZI306;
	SID_TYPE ZI307;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			SID_TYPE ZIs;
			SID_TYPE ZIt;

			ZRfunction_Hoperator (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((*ZI337), (ZIs));
	
#line 3701 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			ZR308 (*ZI336, ZIt, &ZI306, &ZI307);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			ZR308 (*ZI336, *ZI337, &ZI306, &ZI307);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZO306 = ZI306;
	*ZO307 = ZI307;
}

static void
ZR339(SID_TYPE *ZOq)
{
	SID_TYPE ZIq;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_list_ellipsis */
			{
#line 347 "syntax.act"

		(ZIq) = make_subtype(type_ellipsis, TYPE_LIST);
		(ZIq)->v.next = NULL;
	
#line 3748 "syntax.c"
			}
			/* END OF ACTION: type_list_ellipsis */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 42: case 43: case 44: case 45:
	case 46: case 47: case 48:
		{
			ZRparameter_Hlist (&ZIq);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
ZR340(int *ZOtag)
{
	int ZItag;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_arith */
			{
#line 221 "syntax.act"
 (ZItag) = TYPE_ARITH;      
#line 3798 "syntax.c"
			}
			/* END OF ACTION: key_arith */
		}
		break;
	case 37:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_float */
			{
#line 220 "syntax.act"
 (ZItag) = TYPE_FLOAT;      
#line 3817 "syntax.c"
			}
			/* END OF ACTION: key_float */
		}
		break;
	case 38:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_int */
			{
#line 217 "syntax.act"
 (ZItag) = TYPE_INT;        
#line 3836 "syntax.c"
			}
			/* END OF ACTION: key_int */
		}
		break;
	case 41:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_scalar */
			{
#line 222 "syntax.act"
 (ZItag) = TYPE_SCALAR;     
#line 3855 "syntax.c"
			}
			/* END OF ACTION: key_scalar */
		}
		break;
	case 43:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_signed */
			{
#line 218 "syntax.act"
 (ZItag) = TYPE_SIGNED;     
#line 3874 "syntax.c"
			}
			/* END OF ACTION: key_signed */
		}
		break;
	case 44:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct */
			{
#line 214 "syntax.act"
 (ZItag) = TYPE_STRUCT;     
#line 3893 "syntax.c"
			}
			/* END OF ACTION: key_struct */
		}
		break;
	case 45:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union */
			{
#line 215 "syntax.act"
 (ZItag) = TYPE_UNION;      
#line 3912 "syntax.c"
			}
			/* END OF ACTION: key_union */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_unsigned */
			{
#line 219 "syntax.act"
 (ZItag) = TYPE_UNSIGNED;   
#line 3931 "syntax.c"
			}
			/* END OF ACTION: key_unsigned */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOtag = ZItag;
}

static void
ZRdirect_Hdeclarator(SID_IDENTIFIER *ZO316, SID_TYPE *ZO317)
{
	SID_IDENTIFIER ZI316;
	SID_TYPE ZI317;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIt;

			ADVANCE_LEXER;
			ZRdeclarator (&ZIid, &ZIt);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR318 (ZIid, ZIt, &ZI316, &ZI317);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 0:
		{
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIt;

			ZRidentifier (&ZIid);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 273 "syntax.act"

		(ZIt) = NULL;
	
#line 3996 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR318 (ZIid, ZIt, &ZI316, &ZI317);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZO316 = ZI316;
	*ZO317 = ZI317;
}

static void
ZRtype_Hcommand(int *ZOtag)
{
	int ZItag;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			ADVANCE_LEXER;
			ZR340 (&ZItag);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 44:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct_tag */
			{
#line 211 "syntax.act"
 (ZItag) = TYPE_STRUCT_TAG; 
#line 4043 "syntax.c"
			}
			/* END OF ACTION: key_struct_tag */
		}
		break;
	case 45:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union_tag */
			{
#line 212 "syntax.act"
 (ZItag) = TYPE_UNION_TAG;  
#line 4055 "syntax.c"
			}
			/* END OF ACTION: key_union_tag */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_type */
			{
#line 210 "syntax.act"
 (ZItag) = TYPE_GENERIC;    
#line 4066 "syntax.c"
			}
			/* END OF ACTION: key_type */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOtag = ZItag;
}

static void
ZRtext_Hcommand(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 6:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: build-insert */
			{
#line 162 "syntax.act"
 ZIs = token_value; 
#line 4096 "syntax.c"
			}
			/* END OF EXTRACT: build-insert */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_build_insert */
			{
#line 593 "syntax.act"

		(ZIc) = make_object((ZIs), OBJ_TEXT_SRC);
	
#line 4106 "syntax.c"
			}
			/* END OF ACTION: declare_build_insert */
		}
		break;
	case 4:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: comment */
			{
#line 160 "syntax.act"
 ZIs = token_value; 
#line 4119 "syntax.c"
			}
			/* END OF EXTRACT: comment */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_comment */
			{
#line 585 "syntax.act"

		(ZIc) = make_object((ZIs), OBJ_TEXT_INCL);
	
#line 4129 "syntax.c"
			}
			/* END OF ACTION: declare_comment */
		}
		break;
	case 5:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: insert */
			{
#line 161 "syntax.act"
 ZIs = token_value; 
#line 4142 "syntax.c"
			}
			/* END OF EXTRACT: insert */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_insert */
			{
#line 589 "syntax.act"

		(ZIc) = make_object((ZIs), OBJ_TEXT_INCL);
	
#line 4152 "syntax.c"
			}
			/* END OF ACTION: declare_insert */
		}
		break;
	case 16: case 17: case 18:
		{
			SID_COMMAND ZIi;
			SID_STRING ZIs;
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;

			ZRif_Hcommand (&ZIi, &ZIs);
			ZRcommand_Hlist (&ZIa);
			/* BEGINNING OF INLINE: 293 */
			{
				switch (CURRENT_TERMINAL) {
				case 10:
					{
						ADVANCE_LEXER;
						ZRcommand_Hlist (&ZIb);
						if ((CURRENT_TERMINAL) == 75) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: command_none */
						{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 4187 "syntax.c"
						}
						/* END OF ACTION: command_none */
					}
					break;
				case 75:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 293 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: command_endif */
			{
#line 811 "syntax.act"

		object *p, *q;

		p = join_object ( (ZIi), (ZIa) );
		if ((ZIb)) {
			q = make_object ( (ZIs), OBJ_IF );
			q->u.u_iftype = CMD_ELSE;
			p = join_object ( p, q );
			p = join_object ( p, (ZIb) );
		}

		q = make_object ( (ZIs), OBJ_IF );
		q->u.u_iftype = CMD_ENDIF;
		(ZIc) = join_object ( p, q );
	
#line 4223 "syntax.c"
			}
			/* END OF ACTION: command_endif */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR347(SID_IDENTIFIER *ZI345, SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 61:
		{
			ZRbitfield_Hoperator (&ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			ZIid = *ZI345;
		}
		break;
	default:
		{
			SID_TYPE ZI344;

			/* BEGINNING OF ACTION: type_none */
			{
#line 273 "syntax.act"

		(ZI344) = NULL;
	
#line 4268 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR318 (*ZI345, ZI344, &ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZRname_Hversion(int *ZOv)
{
	int ZIv;

	switch (CURRENT_TERMINAL) {
	case 63:
		{
			SID_STRING ZIn;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 157 "syntax.act"
 ZIn = token_value; 
#line 4307 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: version_number */
			{
#line 462 "syntax.act"

		(ZIv) = atoi((ZIn));
	
#line 4321 "syntax.c"
			}
			/* END OF ACTION: version_number */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: version_none */
			{
#line 458 "syntax.act"

		(ZIv) = no_version;
	
#line 4334 "syntax.c"
			}
			/* END OF ACTION: version_none */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOv = ZIv;
}

static void
ZR348(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			ADVANCE_LEXER;
			ZR349 (&ZIcmd);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cmd_func */
			{
#line 502 "syntax.act"
 (ZIcmd) = OBJ_FUNC;      
#line 4372 "syntax.c"
			}
			/* END OF ACTION: cmd_func */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZRdirect_Habstract_Hdeclarator(SID_STRING *ZO306, SID_TYPE *ZO307)
{
	SID_STRING ZI306;
	SID_TYPE ZI307;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZInm;
			SID_TYPE ZIt;

			/* BEGINNING OF EXTRACT: name */
			{
#line 156 "syntax.act"
 ZInm = token_value; 
#line 4404 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_none */
			{
#line 273 "syntax.act"

		(ZIt) = NULL;
	
#line 4414 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR308 (ZInm, ZIt, &ZI306, &ZI307);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 56:
		{
			SID_STRING ZI336;
			SID_TYPE ZI337;

			ADVANCE_LEXER;
			ZRabstract_Hdeclarator (&ZI336, &ZI337);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR338 (&ZI336, &ZI337, &ZI306, &ZI307);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			SID_STRING ZInm;
			SID_TYPE ZIt;

			/* BEGINNING OF ACTION: name_none */
			{
#line 421 "syntax.act"

		(ZInm) = NULL;
	
#line 4459 "syntax.c"
			}
			/* END OF ACTION: name_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 273 "syntax.act"

		(ZIt) = NULL;
	
#line 4468 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR308 (ZInm, ZIt, &ZI306, &ZI307);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZO306 = ZI306;
	*ZO307 = ZI307;
}

static void
ZRfield_Hdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			SID_IDENTIFIER ZI341;
			SID_TYPE ZI342;

			ADVANCE_LEXER;
			ZRdeclarator (&ZI341, &ZI342);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR318 (ZI341, ZI342, &ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 61:
		{
			ZRbitfield_Hoperator (&ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: id_anon */
			{
#line 451 "syntax.act"

		char *nm;

		nm = string_printf ("%s%d", HIDDEN_NAME, anon_no++);
		if (crt_field_name) {
			nm = string_printf("%s.%s", crt_field_name, nm);
		}

		(ZIid).iname = nm;
		(ZIid).ivers = no_version;
		(ZIid).ename = token_name(nm);
		(ZIid).evers = no_version;
	
#line 4544 "syntax.c"
			}
			/* END OF ACTION: id_anon */
		}
		break;
	case 0:
		{
			SID_IDENTIFIER ZI345;

			ZRidentifier (&ZI345);
			ZR347 (&ZI345, &ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 72:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRdeclarator (&ZIid, &ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 4578 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZRvariable_Hcommand(void)
{
	switch (CURRENT_TERMINAL) {
	case 20:
		{
			SID_STRING ZIs;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 158 "syntax.act"
 ZIs = token_value; 
#line 4612 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 3:
		{
			SID_STRING ZInm;

			/* BEGINNING OF EXTRACT: variable */
			{
#line 159 "syntax.act"
 ZInm = token_value; 
#line 4630 "syntax.c"
			}
			/* END OF EXTRACT: variable */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 66:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR354 (&ZInm);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (75);
	return;
}

static void
ZR349(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_func_extern */
			{
#line 503 "syntax.act"
 (ZIcmd) = OBJ_EXTERN;    
#line 4679 "syntax.c"
			}
			/* END OF ACTION: cmd_func_extern */
		}
		break;
	case 49:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_func_weak */
			{
#line 504 "syntax.act"
 (ZIcmd) = OBJ_WEAK;      
#line 4698 "syntax.c"
			}
			/* END OF ACTION: cmd_func_weak */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR350(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			SID_TYPE ZIp;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_list_none */
			{
#line 333 "syntax.act"

		(ZIp) = NULL;
	
#line 4733 "syntax.c"
			}
			/* END OF ACTION: type_list_none */
			/* BEGINNING OF ACTION: type_macro */
			{
#line 313 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 4743 "syntax.c"
			}
			/* END OF ACTION: type_macro */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 40: case 42: case 43: case 44:
	case 45: case 46: case 47: case 48:
		{
			SID_TYPE ZIp;

			ZRmacro_Hparam_Hlist (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_macro */
			{
#line 313 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 4773 "syntax.c"
			}
			/* END OF ACTION: type_macro */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZR351(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 67:
		{
			ADVANCE_LEXER;
			ZR352 (&ZIkey);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 70:
		{
			ADVANCE_LEXER;
			ZR353 (&ZIkey);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZRdefine_Hparam_Hclause(SID_STRING *ZOp)
{
	SID_STRING ZIp;

	switch (CURRENT_TERMINAL) {
	case 56:
		{
			ADVANCE_LEXER;
			ZR325 (&ZIp);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: param_none */
			{
#line 407 "syntax.act"
 (ZIp) = NULL; 
#line 4852 "syntax.c"
			}
			/* END OF ACTION: param_none */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRexp_Hcommand(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 8:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_constant */
			{
#line 499 "syntax.act"
 (ZIcmd) = OBJ_CONST;     
#line 4881 "syntax.c"
			}
			/* END OF ACTION: cmd_constant */
		}
		break;
	case 13:
		{
			ADVANCE_LEXER;
			ZR329 (&ZIcmd);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR352(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 67:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_both */
			{
#line 474 "syntax.act"
 (ZIkey) = "11"; 
#line 4929 "syntax.c"
			}
			/* END OF ACTION: subset_both */
		}
		break;
	case 70:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_first */
			{
#line 472 "syntax.act"
 (ZIkey) = "10"; 
#line 4948 "syntax.c"
			}
			/* END OF ACTION: subset_first */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZRif_Hcommand(SID_COMMAND *ZOc, SID_STRING *ZOs)
{
	SID_COMMAND ZIc;
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 16:
		{
			ADVANCE_LEXER;
			ZRconstant_Hvalue (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_if */
			{
#line 794 "syntax.act"

		(ZIc) = make_object ((ZIs), OBJ_IF);
		(ZIc)->u.u_iftype = CMD_IF;
	
#line 4988 "syntax.c"
			}
			/* END OF ACTION: command_if */
		}
		break;
	case 17:
		{
			ADVANCE_LEXER;
			ZRifdef_Hmacro_Hname (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_ifdef */
			{
#line 799 "syntax.act"

		(ZIc) = make_object ((ZIs), OBJ_IF);
		(ZIc)->u.u_iftype = CMD_IFDEF;
	
#line 5008 "syntax.c"
			}
			/* END OF ACTION: command_ifdef */
		}
		break;
	case 18:
		{
			ADVANCE_LEXER;
			ZRifdef_Hmacro_Hname (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_ifndef */
			{
#line 804 "syntax.act"

		(ZIc) = make_object ((ZIs), OBJ_IF);
		(ZIc)->u.u_iftype = CMD_IFNDEF;
	
#line 5028 "syntax.c"
			}
			/* END OF ACTION: command_ifndef */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
	*ZOs = ZIs;
}

static void
ZR353(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 67:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_second */
			{
#line 473 "syntax.act"
 (ZIkey) = "01"; 
#line 5067 "syntax.c"
			}
			/* END OF ACTION: subset_second */
		}
		break;
	case 70:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_none */
			{
#line 471 "syntax.act"
 (ZIkey) = "00"; 
#line 5086 "syntax.c"
			}
			/* END OF ACTION: subset_none */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZR354(SID_STRING *ZInm)
{
	switch (CURRENT_TERMINAL) {
	case 68:
		{
			SID_STRING ZIs;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 157 "syntax.act"
 ZIs = token_value; 
#line 5119 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: variable_minus */
			{
#line 570 "syntax.act"

		set_integer((*ZInm), -atoi((ZIs)));
	
#line 5133 "syntax.c"
			}
			/* END OF ACTION: variable_minus */
		}
		break;
	case 1:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: number */
			{
#line 157 "syntax.act"
 ZIs = token_value; 
#line 5146 "syntax.c"
			}
			/* END OF EXTRACT: number */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: variable_plus */
			{
#line 566 "syntax.act"

		set_integer((*ZInm), atoi((ZIs)));
	
#line 5156 "syntax.c"
			}
			/* END OF ACTION: variable_plus */
		}
		break;
	case 2:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: string */
			{
#line 158 "syntax.act"
 ZIs = token_value; 
#line 5169 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: variable_string */
			{
#line 562 "syntax.act"

		set_string((*ZInm), (ZIs));
	
#line 5179 "syntax.c"
			}
			/* END OF ACTION: variable_string */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (75);
	return;
}

static void
ZRbitfield_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 61:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRconstant_Hvalue (&ZIa);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_bitfield */
		{
#line 303 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_BITFIELD );
		(ZIt)->v.str = (ZIa);
	
#line 5225 "syntax.c"
		}
		/* END OF ACTION: type_bitfield */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRuse_Hsubset_Hname(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZIa;
		SID_STRING ZIb;

		switch (CURRENT_TERMINAL) {
		case 56:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 158 "syntax.act"
 ZIa = token_value; 
#line 5262 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 57:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 62:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 158 "syntax.act"
 ZIb = token_value; 
#line 5290 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: file_name */
		{
#line 482 "syntax.act"

		(ZIs) = subset_name((ZIa), (ZIb), NULL);
	
#line 5304 "syntax.c"
		}
		/* END OF ACTION: file_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOs = ZIs;
}

void
read_spec(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		ZRsubset_Hcommand (&ZIc);
		switch (CURRENT_TERMINAL) {
		case 71:
			break;
		case 75:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 73:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 834 "syntax.act"

		error(ERROR_SERIOUS, "Syntax error");
	
#line 5353 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
		/* BEGINNING OF ACTION: command_none */
		{
#line 515 "syntax.act"

		(ZIc) = NULL;
	
#line 5362 "syntax.c"
		}
		/* END OF ACTION: command_none */
	}
ZL0:;
	*ZOc = ZIc;
}

static void
ZRmacro_Hdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			ZRidentifier (&ZIid);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 273 "syntax.act"

		(ZIt) = NULL;
	
#line 5390 "syntax.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 72:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRmacro_Hdeclarator (&ZIid, &ZIs);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 289 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 5412 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZRsubset_Hname(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 158 "syntax.act"
 ZIa = token_value; 
#line 5448 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR320 (&ZIa, &ZIs);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRbuiltin_Htype(unsigned *ZOb)
{
	unsigned ZIb;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		unsigned ZIa;
		unsigned ZIc;

		ZRtype_Hkeyword (&ZIa);
		/* BEGINNING OF INLINE: 102 */
		{
			switch (CURRENT_TERMINAL) {
			case 32: case 34: case 37: case 38:
			case 39: case 42: case 43: case 46:
			case 47:
				{
					unsigned ZId;

					ZRbuiltin_Htype (&ZId);
					if ((CURRENT_TERMINAL) == 75) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: btype_join */
					{
#line 192 "syntax.act"

		while ((ZIa) & (ZId)) {
			if ((ZIa) == BTYPE_LONG && allow_long_long) {
				(ZIa) = BTYPE_LLONG;
			} else {
				error(ERROR_SERIOUS, "Duplicate type specifier");
				break;
			}
		}

		(ZIc) = ((ZIa) | (ZId));
	
#line 5512 "syntax.c"
					}
					/* END OF ACTION: btype_join */
				}
				break;
			default:
				{
					ZIc = ZIa;
				}
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 102 */
		ZIb = ZIc;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOb = ZIb;
}

static void
ZRobject_Hqualifier(int *ZOlv)
{
	int ZIlv;

	switch (CURRENT_TERMINAL) {
	case 40:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_lvalue */
			{
#line 223 "syntax.act"
 (ZIlv) = TYPE_LVALUE;     
#line 5551 "syntax.c"
			}
			/* END OF ACTION: key_lvalue */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_rvalue */
			{
#line 224 "syntax.act"
 (ZIlv) = TYPE_RVALUE;     
#line 5562 "syntax.c"
			}
			/* END OF ACTION: key_rvalue */
		}
		break;
	case 75:
		return;
	}
	*ZOlv = ZIlv;
}

static void
ZRfield_Hlist(SID_TYPE ZIm, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 16: case 17: case 18:
		{
			SID_COMMAND ZIi;
			SID_STRING ZIs;
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;
			SID_COMMAND ZIc1;
			SID_COMMAND ZIc2;

			ZRif_Hcommand (&ZIi, &ZIs);
			ZRfield_Hlist (ZIm, &ZIa);
			/* BEGINNING OF INLINE: 241 */
			{
				switch (CURRENT_TERMINAL) {
				case 10:
					{
						ADVANCE_LEXER;
						ZRfield_Hlist (ZIm, &ZIb);
						if ((CURRENT_TERMINAL) == 75) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: command_none */
						{
#line 515 "syntax.act"

		(ZIb) = NULL;
	
#line 5611 "syntax.c"
						}
						/* END OF ACTION: command_none */
					}
					break;
				case 75:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 241 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: command_endif */
			{
#line 811 "syntax.act"

		object *p, *q;

		p = join_object ( (ZIi), (ZIa) );
		if ((ZIb)) {
			q = make_object ( (ZIs), OBJ_IF );
			q->u.u_iftype = CMD_ELSE;
			p = join_object ( p, q );
			p = join_object ( p, (ZIb) );
		}

		q = make_object ( (ZIs), OBJ_IF );
		q->u.u_iftype = CMD_ENDIF;
		(ZIc1) = join_object ( p, q );
	
#line 5647 "syntax.c"
			}
			/* END OF ACTION: command_endif */
			ZRfield_Hlist (ZIm, &ZIc2);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIc1), (ZIc2));
	
#line 5661 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 42: case 43: case 44: case 45:
	case 46: case 47: case 48:
		{
			SID_TYPE ZIt;
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;

			ZRqualified_Htype (&ZIt);
			ZRfield_Hdeclarator_Hlist (ZIm, ZIt, &ZIa);
			switch (CURRENT_TERMINAL) {
			case 71:
				break;
			case 75:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRfield_Hlist (ZIm, &ZIb);
			if ((CURRENT_TERMINAL) == 75) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 519 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 5698 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: command_none */
			{
#line 515 "syntax.act"

		(ZIc) = NULL;
	
#line 5711 "syntax.c"
			}
			/* END OF ACTION: command_none */
		}
		break;
	case 75:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRptr_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 75) {
		return;
	}
	{
		unsigned ZIcv;

		switch (CURRENT_TERMINAL) {
		case 72:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRtype_Hqualifier_Hopt (&ZIcv);
		if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_ptr */
		{
#line 293 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PTR);
		(ZIt)->v.str = cv_qualifier[(ZIcv)];
	
#line 5757 "syntax.c"
		}
		/* END OF ACTION: type_ptr */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRtype_Hkeyword(unsigned *ZOb)
{
	unsigned ZIb;

	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_char */
			{
#line 181 "syntax.act"
 (ZIb) = BTYPE_CHAR;     
#line 5782 "syntax.c"
			}
			/* END OF ACTION: btype_char */
		}
		break;
	case 34:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_double */
			{
#line 188 "syntax.act"
 (ZIb) = BTYPE_DOUBLE;   
#line 5794 "syntax.c"
			}
			/* END OF ACTION: btype_double */
		}
		break;
	case 37:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_float */
			{
#line 187 "syntax.act"
 (ZIb) = BTYPE_FLOAT;    
#line 5806 "syntax.c"
			}
			/* END OF ACTION: btype_float */
		}
		break;
	case 38:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_int */
			{
#line 183 "syntax.act"
 (ZIb) = BTYPE_INT;      
#line 5818 "syntax.c"
			}
			/* END OF ACTION: btype_int */
		}
		break;
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_long */
			{
#line 184 "syntax.act"
 (ZIb) = BTYPE_LONG;     
#line 5830 "syntax.c"
			}
			/* END OF ACTION: btype_long */
		}
		break;
	case 42:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_short */
			{
#line 182 "syntax.act"
 (ZIb) = BTYPE_SHORT;    
#line 5842 "syntax.c"
			}
			/* END OF ACTION: btype_short */
		}
		break;
	case 43:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_signed */
			{
#line 185 "syntax.act"
 (ZIb) = BTYPE_SIGNED;   
#line 5854 "syntax.c"
			}
			/* END OF ACTION: btype_signed */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_unsigned */
			{
#line 186 "syntax.act"
 (ZIb) = BTYPE_UNSIGNED; 
#line 5866 "syntax.c"
			}
			/* END OF ACTION: btype_unsigned */
		}
		break;
	case 47:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_void */
			{
#line 189 "syntax.act"
 (ZIb) = BTYPE_VOID;     
#line 5878 "syntax.c"
			}
			/* END OF ACTION: btype_void */
		}
		break;
	case 75:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (75);
	return;
ZL0:;
	*ZOb = ZIb;
}

/* BEGINNING OF TRAILER */

#line 837 "syntax.act"

#line 5900 "syntax.c"

/* END OF FILE */
