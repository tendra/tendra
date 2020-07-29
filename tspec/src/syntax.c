/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 121 "syntax.act"



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
		"restrict",
		"const restrict",
		"volatile",
		"const volatile",
		"const restrict volatile"
	};

#line 88 "syntax.c"

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
static void ZR289(SID_TYPE *);
static void ZRdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRidentifier(SID_IDENTIFIER *);
static void ZRsubset_Hcommand(SID_COMMAND *);
static void ZRqualified_Htype(SID_TYPE *);
static void ZRabstract_Hdeclarator(SID_STRING *, SID_TYPE *);
static void ZRparameter_Hlist(SID_TYPE *);
static void ZRinternal_Hname(SID_STRING *, int *);
static void ZRmacro_Hoperator(SID_TYPE *);
static void ZRenumerator_Hlist(SID_COMMAND *);
static void ZR310(SID_STRING, SID_TYPE, SID_STRING *, SID_TYPE *);
static void ZRexternal_Hname(SID_STRING *, int *);
static void ZRtype_Hqualifier(unsigned *);
static void ZRtype_Hkey(int *);
static void ZRtype_Hqualifier_Hopt(unsigned *);
static void ZRconstant_Hvalue(SID_STRING *);
static void ZRspec_Hcommand(SID_COMMAND *);
static void ZRfunc_Hcommand(int *);
static void ZR320(SID_IDENTIFIER, SID_TYPE, SID_IDENTIFIER *, SID_TYPE *);
static void ZRarray_Hoperator(SID_TYPE *);
static void ZR322(SID_STRING *, SID_STRING *);
static void ZR323(SID_STRING *, SID_STRING *, SID_STRING *);
static void ZRmacro_Hparam_Hlist(SID_TYPE *);
static void ZR324(SID_COMMAND *);
static void ZR325(int *, SID_COMMAND *);
static void ZR326(SID_STRING *, int *, SID_IDENTIFIER *);
static void ZR327(SID_STRING *);
static void ZRenum_Hcommand(int *);
static void ZRenumerator(SID_COMMAND *);
static void ZRfield_Hdeclarator_Hlist(SID_TYPE, SID_TYPE, SID_COMMAND *);
static void ZR330(SID_STRING *, SID_STRING *);
static void ZR331(int *);
static void ZR332(int *);
static void ZRfield_Hexact(bool *);
static void ZR335(SID_TYPE *, SID_TYPE *);
static void ZRcommand_Hlist(SID_COMMAND *);
static void ZR337(SID_TYPE *);
static void ZR340(SID_STRING *, SID_TYPE *, SID_STRING *, SID_TYPE *);
static void ZRdirect_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZR341(SID_TYPE *);
static void ZRtype_Hcommand(int *);
static void ZR342(int *);
static void ZRtext_Hcommand(SID_COMMAND *);
static void ZRname_Hversion(int *);
static void ZRdirect_Habstract_Hdeclarator(SID_STRING *, SID_TYPE *);
static void ZRfield_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRvariable_Hcommand(void);
static void ZR349(SID_IDENTIFIER *, SID_IDENTIFIER *, SID_TYPE *);
static void ZR350(int *);
static void ZR351(int *);
static void ZRdefine_Hparam_Hclause(SID_STRING *);
static void ZRexp_Hcommand(int *);
static void ZR352(SID_TYPE *);
static void ZRif_Hcommand(SID_COMMAND *, SID_STRING *);
static void ZR353(SID_STRING *);
static void ZR354(SID_STRING *);
static void ZR355(SID_STRING *);
static void ZR356(SID_STRING *);
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
	case 39: case 43: case 44: case 47:
	case 48:
		{
			unsigned ZIb;

			ZRbuiltin_Htype (&ZIb);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_builtin */
			{
#line 276 "syntax.act"

		(ZIt) = basic_type ((ZIb));
	
#line 199 "syntax.c"
			}
			/* END OF ACTION: type_builtin */
		}
		break;
	case 0: case 35: case 45: case 46:
		{
			int ZItag;
			SID_STRING ZInm;

			ZRtype_Hkey (&ZItag);
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: name */
				{
#line 147 "syntax.act"
 ZInm = token_value; 
#line 216 "syntax.c"
				}
				/* END OF EXTRACT: name */
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_name */
			{
#line 280 "syntax.act"

		(ZIt) = find_type((ZInm), any_version, (ZItag), 1);
	
#line 233 "syntax.c"
			}
			/* END OF ACTION: type_name */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRparameter_Hdeclaration(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_TYPE ZIs;
		SID_STRING ZInm;
		SID_TYPE ZIp;

		ZRqualified_Htype (&ZIs);
		ZRabstract_Hdeclarator (&ZInm, &ZIp);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 276 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: param_name */
		{
#line 351 "syntax.act"

		UNUSED((ZInm));
	
#line 285 "syntax.c"
		}
		/* END OF ACTION: param_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRnat_Hdeclarator_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRidentifier (&ZIid);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_nat */
		{
#line 682 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_NAT);
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_NAT);
	
#line 322 "syntax.c"
		}
		/* END OF ACTION: declare_nat */
		/* BEGINNING OF INLINE: 252 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZRnat_Hdeclarator_Hlist (&ZIb);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 346 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 252 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 360 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRtype_Hdeclarator_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		int ZItag;
		SID_IDENTIFIER ZIid;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRtype_Hcommand (&ZItag);
		ZRidentifier (&ZIid);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_type */
		{
#line 718 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, (ZItag));
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_TYPE);
	
#line 399 "syntax.c"
		}
		/* END OF ACTION: declare_type */
		/* BEGINNING OF INLINE: 264 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZRtype_Hdeclarator_Hlist (&ZIb);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 423 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 264 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 437 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRfunction_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 57:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR337 (&ZIt);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRexp_Hdeclarator_Hlist(int ZIcmd, SID_TYPE ZIs, int ZIlv, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
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
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 288 "syntax.act"

		(ZIu) = inject_type((ZIp), (ZIs));
	
#line 506 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: type_lvalue */
		{
#line 322 "syntax.act"

		(ZIt) = make_subtype((ZIu), (ZIlv));
	
#line 515 "syntax.c"
		}
		/* END OF ACTION: type_lvalue */
		/* BEGINNING OF ACTION: declare_exp */
		{
#line 651 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, (ZIcmd));
		p->u.u_type = check_type((ZIt), (ZIcmd));
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, p, (ZIcmd));
	
#line 526 "syntax.c"
		}
		/* END OF ACTION: declare_exp */
		/* BEGINNING OF INLINE: 230 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZRexp_Hdeclarator_Hlist (ZIcmd, ZIs, ZIlv, &ZIb);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 550 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 230 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 564 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRsubset_Hkey(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ADVANCE_LEXER;
			ZR353 (&ZIkey);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: subset_both */
			{
#line 473 "syntax.act"
 (ZIkey) = "11"; 
#line 598 "syntax.c"
			}
			/* END OF ACTION: subset_both */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZRmacro_Hparam_Hdeclaration(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
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
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 288 "syntax.act"

		(ZIu) = inject_type((ZIp), (ZIs));
	
#line 642 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: type_lvalue */
		{
#line 322 "syntax.act"

		(ZIt) = make_subtype((ZIu), (ZIlv));
	
#line 651 "syntax.c"
		}
		/* END OF ACTION: type_lvalue */
		/* BEGINNING OF ACTION: param_name */
		{
#line 351 "syntax.act"

		UNUSED((ZInm));
	
#line 660 "syntax.c"
		}
		/* END OF ACTION: param_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRifdef_Hmacro_Hname(SID_STRING *ZOc)
{
	SID_STRING ZIc;

	switch (CURRENT_TERMINAL) {
	case 51:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_building */
			{
#line 393 "syntax.act"

		(ZIc) = BUILDING_MACRO;
	
#line 687 "syntax.c"
			}
			/* END OF ACTION: cond_building */
		}
		break;
	case 0:
		{
			/* BEGINNING OF EXTRACT: name */
			{
#line 147 "syntax.act"
 ZIc = token_value; 
#line 698 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
		}
		break;
	case 53:
		{
			SID_STRING ZIa;
			SID_STRING ZIb;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 149 "syntax.act"
 ZIa = token_value; 
#line 723 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 63:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 149 "syntax.act"
 ZIb = token_value; 
#line 744 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_protect */
			{
#line 397 "syntax.act"

		(ZIc) = macro_name(PROTECT_PREFIX, (ZIa), (ZIb), NULL);
	
#line 765 "syntax.c"
			}
			/* END OF ACTION: cond_protect */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRdefine_Hparam_Hlist(SID_STRING *ZOp)
{
	SID_STRING ZIp;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZI328;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: name */
			{
#line 147 "syntax.act"
 ZI328 = token_value; 
#line 800 "syntax.c"
			}
			/* END OF EXTRACT: name */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR330 (&ZI328, &ZIp);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR289(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ZRmacro_Hoperator (&ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 272 "syntax.act"

		(ZIt) = NULL;
	
#line 845 "syntax.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
	case 0: case 57:
		{
			ZRdirect_Hdeclarator (&ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 73:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRdeclarator (&ZIid, &ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 894 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZRidentifier(SID_IDENTIFIER *ZOid)
{
	SID_IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZInm;
		int ZIv;

		ZRinternal_Hname (&ZInm, &ZIv);
		ZR326 (&ZInm, &ZIv, &ZIid);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOid = ZIid;
}

static void
ZRsubset_Hcommand(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
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
		case 61:
			break;
		case 76:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: begin_subset */
		{
#line 522 "syntax.act"

		object *p = make_subset((ZIs));
		info *i = p->u.u_info;

		if (i->subset) {
			char *nm;
			object *q;

			i->api = crt_object->u.u_info->api;

			nm = subset_name(i->api, i->file, NULL);
			q = search_hash(subsets, nm, no_version);
			update_time(p, q);
		}

		(ZIa) = crt_object;
		crt_object = p;
	
#line 992 "syntax.c"
		}
		/* END OF ACTION: begin_subset */
		switch (CURRENT_TERMINAL) {
		case 55:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcommand_Hlist (&ZIb);
		switch (CURRENT_TERMINAL) {
		case 56:
			break;
		case 76:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: end_subset */
		{
#line 544 "syntax.act"

		object *p = crt_object;

		if (p != NULL) {
			p->u.u_info->elements = (ZIb);
		}

		(ZIc) = make_object(NULL, OBJ_SET);
		(ZIc)->u.u_obj = p;
		crt_object = (ZIa);
	
#line 1027 "syntax.c"
		}
		/* END OF ACTION: end_subset */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
	case 37: case 38: case 39: case 43:
	case 44: case 45: case 46: case 47:
	case 48:
		{
			SID_TYPE ZI333;

			ZRsimple_Htype (&ZI333);
			ZR335 (&ZI333, &ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 33: case 41: case 49:
		{
			unsigned ZIcv;
			SID_TYPE ZIs;

			ZRtype_Hqualifier (&ZIcv);
			ZRsimple_Htype (&ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_qualify */
			{
#line 317 "syntax.act"

		(ZIt) = make_subtype((ZIs), TYPE_QUALIFIER);
		(ZIt)->v.str = cv_qualifier[(ZIcv)];
	
#line 1078 "syntax.c"
			}
			/* END OF ACTION: type_qualify */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 73:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRabstract_Hdeclarator (&ZInm, &ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 1129 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOnm = ZInm;
	*ZOt = ZIt;
}

static void
ZRparameter_Hlist(SID_TYPE *ZOp)
{
	SID_TYPE ZIp;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_TYPE ZIt;
		SID_TYPE ZIq;

		ZRparameter_Hdeclaration (&ZIt);
		/* BEGINNING OF INLINE: 156 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZR341 (&ZIq);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: type_list_none */
					{
#line 332 "syntax.act"

		(ZIq) = NULL;
	
#line 1180 "syntax.c"
					}
					/* END OF ACTION: type_list_none */
				}
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 156 */
		/* BEGINNING OF ACTION: type_list_cons */
		{
#line 341 "syntax.act"

		(ZIp) = make_subtype ((ZIt), TYPE_LIST);
		(ZIp)->v.next = (ZIq);
	
#line 1198 "syntax.c"
		}
		/* END OF ACTION: type_list_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRinternal_Hname(SID_STRING *ZOnm, int *ZOv)
{
	SID_STRING ZInm;
	int ZIv;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: name */
			{
#line 147 "syntax.act"
 ZIa = token_value; 
#line 1228 "syntax.c"
			}
			/* END OF EXTRACT: name */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRname_Hversion (&ZIv);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: field_name */
		{
#line 425 "syntax.act"

		if (crt_field_name) {
			(ZInm) = string_printf("%s.%s", crt_field_name, (ZIa));
		} else {
			(ZInm) = (ZIa);
		}
	
#line 1251 "syntax.c"
		}
		/* END OF ACTION: field_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOnm = ZInm;
	*ZOv = ZIv;
}

static void
ZRmacro_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 57:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR352 (&ZIt);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRenumerator_Hlist(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRenumerator (&ZIa);
		/* BEGINNING OF INLINE: 223 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZRenumerator_Hlist (&ZIb);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 1328 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 223 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 1345 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR310(SID_STRING ZI306, SID_TYPE ZI307, SID_STRING *ZO308, SID_TYPE *ZO309)
{
	SID_STRING ZI308;
	SID_TYPE ZI309;

ZL2_310:;
	switch (CURRENT_TERMINAL) {
	case 59:
		{
			SID_STRING ZInm;
			SID_TYPE ZIs;
			SID_TYPE ZIt;

			ZInm = ZI306;
			ZRarray_Hoperator (&ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZI307), (ZIs));
	
#line 1383 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF INLINE: 310 */
			ZI306 = ZInm;
			ZI307 = ZIt;
			goto ZL2_310;
			/* END OF INLINE: 310 */
		}
		UNREACHED;
	default:
		{
			ZI308 = ZI306;
			ZI309 = ZI307;
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZO308 = ZI308;
	*ZO309 = ZI309;
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
#line 147 "syntax.act"
 ZIa = token_value; 
#line 1427 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
			ZRname_Hversion (&ZIv);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: field_name */
			{
#line 425 "syntax.act"

		if (crt_field_name) {
			(ZIb) = string_printf("%s.%s", crt_field_name, (ZIa));
		} else {
			(ZIb) = (ZIa);
		}
	
#line 1446 "syntax.c"
			}
			/* END OF ACTION: field_name */
			/* BEGINNING OF ACTION: token_name */
			{
#line 432 "syntax.act"

		(ZInm) = token_name((ZIb));
	
#line 1455 "syntax.c"
			}
			/* END OF ACTION: token_name */
		}
		break;
	case 2:
		{
			/* BEGINNING OF EXTRACT: string */
			{
#line 149 "syntax.act"
 ZInm = token_value; 
#line 1466 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			ZRname_Hversion (&ZIv);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_const */
			{
#line 242 "syntax.act"

		if ((ZIa) & 1) {
			error(ERR_SERIOUS, "Duplicate type qualifier");
		}

		(ZIcv) = ((ZIa) | 1);
	
#line 1517 "syntax.c"
			}
			/* END OF ACTION: cv_const */
		}
		break;
	case 41:
		{
			unsigned ZIa;

			ADVANCE_LEXER;
			ZRtype_Hqualifier_Hopt (&ZIa);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_restrict */
			{
#line 250 "syntax.act"

		if ((ZIa) & 2) {
			error(ERR_SERIOUS, "Duplicate type qualifier");
		}

		(ZIcv) = ((ZIa) | 2);
	
#line 1542 "syntax.c"
			}
			/* END OF ACTION: cv_restrict */
		}
		break;
	case 49:
		{
			unsigned ZIa;

			ADVANCE_LEXER;
			ZRtype_Hqualifier_Hopt (&ZIa);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_volatile */
			{
#line 258 "syntax.act"

		if ((ZIa) & 4) {
			error(ERR_SERIOUS, "Duplicate type qualifier");
		}

		(ZIcv) = ((ZIa) | 4);
	
#line 1567 "syntax.c"
			}
			/* END OF ACTION: cv_volatile */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 204 "syntax.act"
 (ZItag) = TYPE_ENUM_TAG;   
#line 1598 "syntax.c"
			}
			/* END OF ACTION: key_enum_tag */
		}
		break;
	case 45:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct_tag */
			{
#line 202 "syntax.act"
 (ZItag) = TYPE_STRUCT_TAG; 
#line 1610 "syntax.c"
			}
			/* END OF ACTION: key_struct_tag */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union_tag */
			{
#line 203 "syntax.act"
 (ZItag) = TYPE_UNION_TAG;  
#line 1622 "syntax.c"
			}
			/* END OF ACTION: key_union_tag */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_type */
			{
#line 201 "syntax.act"
 (ZItag) = TYPE_GENERIC;    
#line 1633 "syntax.c"
			}
			/* END OF ACTION: key_type */
		}
		break;
	case 76:
		return;
	}
	*ZOtag = ZItag;
}

static void
ZRtype_Hqualifier_Hopt(unsigned *ZOcv)
{
	unsigned ZIcv;

	switch (CURRENT_TERMINAL) {
	case 33: case 41: case 49:
		{
			ZRtype_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cv_none */
			{
#line 238 "syntax.act"

		(ZIcv) = 0;
	
#line 1667 "syntax.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

static void
ZRconstant_Hvalue(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 68:
		{
			SID_STRING ZIa;

			ADVANCE_LEXER;
			ZRconstant_Hvalue (&ZIa);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: value_not */
			{
#line 369 "syntax.act"

		(ZIs) = xstrcat("!", (ZIa));
	
#line 1705 "syntax.c"
			}
			/* END OF ACTION: value_not */
		}
		break;
	case 5:
		{
			/* BEGINNING OF EXTRACT: insert */
			{
#line 152 "syntax.act"
 ZIs = token_value; 
#line 1716 "syntax.c"
			}
			/* END OF EXTRACT: insert */
			ADVANCE_LEXER;
		}
		break;
	case 69:
		{
			SID_STRING ZIa;

			ADVANCE_LEXER;
			ZRconstant_Hvalue (&ZIa);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: value_negate */
			{
#line 365 "syntax.act"

		(ZIs) = xstrcat("-", (ZIa));
	
#line 1738 "syntax.c"
			}
			/* END OF ACTION: value_negate */
		}
		break;
	case 0:
		{
			SID_STRING ZIa;

			/* BEGINNING OF EXTRACT: name */
			{
#line 147 "syntax.act"
 ZIa = token_value; 
#line 1751 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: value_nat */
			{
#line 375 "syntax.act"

		object *p;

		p = search_hash(exps, (ZIa), any_version);
		if (p == NULL) {
			error(ERR_SERIOUS, "Undefined NAT, '%s'", (ZIa));
		} else if (p->objtype != OBJ_NAT) {
			error(ERR_SERIOUS, "'%s' is not a NAT", (ZIa));
		}

		(ZIs) = (ZIa);
	
#line 1770 "syntax.c"
			}
			/* END OF ACTION: value_nat */
		}
		break;
	case 1:
		{
			/* BEGINNING OF EXTRACT: number */
			{
#line 148 "syntax.act"
 ZIs = token_value; 
#line 1781 "syntax.c"
			}
			/* END OF EXTRACT: number */
			ADVANCE_LEXER;
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOs = ZIs;
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
#line 585 "syntax.act"

		(ZIc) = NULL;
	
#line 1815 "syntax.c"
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_define */
			{
#line 604 "syntax.act"

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
	
#line 1855 "syntax.c"
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_defmin */
			{
#line 623 "syntax.act"

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
	
#line 1895 "syntax.c"
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
			case 61:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 55:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRenumerator_Hlist (&ZIe);
			switch (CURRENT_TERMINAL) {
			case 56:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_enum */
			{
#line 639 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, (ZItag));
		t->v.obj2 = (ZIe);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_TYPE);
	
#line 1945 "syntax.c"
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: begin_field */
			{
#line 736 "syntax.act"

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
			error(ERR_SERIOUS, "Illegal field type, '%s'", (ZIid).iname);
			break;
		}
		crt_field_name = (ZIt)->u.obj->name;
	
#line 1993 "syntax.c"
			}
			/* END OF ACTION: begin_field */
			switch (CURRENT_TERMINAL) {
			case 55:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRfield_Hlist (ZIt, &ZIb);
			switch (CURRENT_TERMINAL) {
			case 56:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: end_field */
			{
#line 760 "syntax.act"

		if ((ZIe)) {
			if ((ZIt)->v.obj2) {
				char *nm = crt_field_name;
				error(ERR_SERIOUS, "Redefinition of type '%s'", nm);
			}

			if ((ZIb) == NULL) {
				error ( ERR_SERIOUS, "Empty struct/union definition" );
			} else {
				(ZIt)->v.obj2 = (ZIb);
			}

			if ((ZIa) != NULL) {
				(ZIc) = (ZIa);
			} else {
				/* This is a hack, do properly later */
				(ZIc) = make_object(NULL, OBJ_TYPE);
				(ZIc)->u.u_type = (ZIt);
				if (streq ( (ZIc)->filename, (ZIt)->u.obj->filename )) {
					(ZIt)->state = TYPE_ELSEWHERE;
				} else {
					(ZIt)->state = TYPE_ANOTHER;
				}
			}
		} else {
			(ZIc) = join_object((ZIa), (ZIb));
		}
		crt_field_name = NULL;
	
#line 2047 "syntax.c"
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
#line 504 "syntax.act"
 (ZIcmd) = OBJ_IMPLEMENT; 
#line 2063 "syntax.c"
			}
			/* END OF ACTION: cmd_implement */
			ZRsubset_Hname (&ZIs);
			ZRsubset_Hkey (&ZIkey);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: include_subset */
			{
#line 553 "syntax.act"

		object *p = make_subset((ZIs));
		update_time(crt_object, p);
		(ZIc) = make_object((ZIkey), (ZIcmd));
		(ZIc)->u.u_obj = p;
	
#line 2081 "syntax.c"
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIu) = inject_type((ZIp), (ZIs));
	
#line 2111 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: type_lvalue */
			{
#line 322 "syntax.act"

		(ZIv) = make_subtype((ZIu), (ZIlv));
	
#line 2120 "syntax.c"
			}
			/* END OF ACTION: type_lvalue */
			ZR289 (&ZIq);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIq), (ZIv));
	
#line 2134 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_macro */
			{
#line 672 "syntax.act"

		object *p;
		int cmd = OBJ_MACRO;

		if ((ZIt)->id != TYPE_PROC) {
			cmd = OBJ_EXP;
		}

		p = make_exp((ZIid).iname, (ZIid).ivers, cmd);
		p->u.u_type = check_type((ZIt), cmd);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, cmd);
	
#line 2152 "syntax.c"
			}
			/* END OF ACTION: declare_macro */
		}
		break;
	case 22:
		{
			ADVANCE_LEXER;
			ZRnat_Hdeclarator_Hlist (&ZIc);
			if ((CURRENT_TERMINAL) == 76) {
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
			ZR289 (&ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_stmt */
			{
#line 706 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_STATEMENT);
		p->u.u_type = check_type((ZIt), OBJ_STATEMENT);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_STATEMENT);
	
#line 2187 "syntax.c"
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
#line 152 "syntax.act"
 ZIs = token_value; 
#line 2205 "syntax.c"
				}
				/* END OF EXTRACT: insert */
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_token */
			{
#line 712 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_TOKEN);
		p->u.u_str = (ZIs);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_TOKEN);
	
#line 2224 "syntax.c"
			}
			/* END OF ACTION: declare_token */
		}
		break;
	case 27:
		{
			ADVANCE_LEXER;
			ZRtype_Hdeclarator_Hlist (&ZIc);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 28:
		{
			ADVANCE_LEXER;
			ZR324 (&ZIc);
			if ((CURRENT_TERMINAL) == 76) {
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
#line 505 "syntax.act"
 (ZIcmd) = OBJ_USE;       
#line 2258 "syntax.c"
			}
			/* END OF ACTION: cmd_use */
			ZR325 (&ZIcmd, &ZIc);
			if ((CURRENT_TERMINAL) == 76) {
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: key_exp */
			{
#line 218 "syntax.act"

		if ((ZIcmd) == OBJ_CONST) {
			if ((ZIlv1) == TYPE_LVALUE) {
				error(ERR_SERIOUS, "Constant can't be an lvalue");
			}
			(ZIlv) = TYPE_RVALUE;
		} else if ((ZIcmd) == OBJ_EXTERN) {
			(ZIlv) = TYPE_LVALUE;
		} else {
			(ZIlv) = (ZIlv1);
		}
	
#line 2296 "syntax.c"
			}
			/* END OF ACTION: key_exp */
			ZRqualified_Htype (&ZIt);
			ZRexp_Hdeclarator_Hlist (ZIcmd, ZIt, ZIlv, &ZIc);
			if ((CURRENT_TERMINAL) == 76) {
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 2328 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_func */
			{
#line 663 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, (ZIcmd));
		p->u.u_type = check_type((ZIt), OBJ_FUNC);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, (ZIcmd));
	
#line 2339 "syntax.c"
			}
			/* END OF ACTION: declare_func */
		}
		break;
	case 23:
		{
			ZRsubset_Hcommand (&ZIc);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRfunc_Hcommand(int *ZOcmd)
{
	int ZIcmd;

	if ((CURRENT_TERMINAL) == 76) {
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
		ZR350 (&ZIcmd);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR320(SID_IDENTIFIER ZI314, SID_TYPE ZI315, SID_IDENTIFIER *ZO318, SID_TYPE *ZO319)
{
	SID_IDENTIFIER ZI318;
	SID_TYPE ZI319;

ZL2_320:;
	switch (CURRENT_TERMINAL) {
	case 57: case 59:
		{
			SID_IDENTIFIER ZIid;

			ZIid = ZI314;
			/* BEGINNING OF INLINE: 336 */
			{
				switch (CURRENT_TERMINAL) {
				case 59:
					{
						SID_TYPE ZIs;
						SID_TYPE ZIt;

						ZRarray_Hoperator (&ZIs);
						if ((CURRENT_TERMINAL) == 76) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: type_inject */
						{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZI315), (ZIs));
	
#line 2428 "syntax.c"
						}
						/* END OF ACTION: type_inject */
						/* BEGINNING OF INLINE: 320 */
						ZI314 = ZIid;
						ZI315 = ZIt;
						goto ZL2_320;
						/* END OF INLINE: 320 */
					}
					UNREACHED;
				case 57:
					{
						SID_TYPE ZIs;
						SID_TYPE ZIt;

						ZRfunction_Hoperator (&ZIs);
						if ((CURRENT_TERMINAL) == 76) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: type_inject */
						{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZI315), (ZIs));
	
#line 2454 "syntax.c"
						}
						/* END OF ACTION: type_inject */
						/* BEGINNING OF INLINE: 320 */
						ZI314 = ZIid;
						ZI315 = ZIt;
						goto ZL2_320;
						/* END OF INLINE: 320 */
					}
					UNREACHED;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 336 */
		}
		UNREACHED;
	default:
		{
			ZI318 = ZI314;
			ZI319 = ZI315;
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZO318 = ZI318;
	*ZO319 = ZI319;
}

static void
ZRarray_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 59:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 142 */
		{
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 5: case 68:
			case 69:
				{
					ZRconstant_Hvalue (&ZIa);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: value_none */
					{
#line 361 "syntax.act"

		(ZIa) = "";
	
#line 2528 "syntax.c"
					}
					/* END OF ACTION: value_none */
				}
				break;
			}
		}
		/* END OF INLINE: 142 */
		switch (CURRENT_TERMINAL) {
		case 60:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: type_array */
		{
#line 297 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_ARRAY);
		(ZIt)->v.str = (ZIa);
	
#line 2550 "syntax.c"
		}
		/* END OF ACTION: type_array */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZR322(SID_STRING *ZIa, SID_STRING *ZOs)
{
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 63:
		{
			SID_STRING ZIb;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 149 "syntax.act"
 ZIb = token_value; 
#line 2579 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR323 (ZIa, &ZIb, &ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: api_name */
			{
#line 477 "syntax.act"

		(ZIs) = subset_name((*ZIa), NULL, NULL);
	
#line 2602 "syntax.c"
			}
			/* END OF ACTION: api_name */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZR323(SID_STRING *ZIa, SID_STRING *ZIb, SID_STRING *ZOs)
{
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	case 63:
		{
			SID_STRING ZIc;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 149 "syntax.act"
 ZIc = token_value; 
#line 2635 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_name */
			{
#line 485 "syntax.act"

		if ((*ZIb)[0] == 0) {
			(*ZIb) = NULL;
		}

		(ZIs) = subset_name((*ZIa), (*ZIb), (ZIc));
	
#line 2653 "syntax.c"
			}
			/* END OF ACTION: subset_name */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: file_name */
			{
#line 481 "syntax.act"

		(ZIs) = subset_name((*ZIa), (*ZIb), NULL);
	
#line 2666 "syntax.c"
			}
			/* END OF ACTION: file_name */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRmacro_Hparam_Hlist(SID_TYPE *ZOp)
{
	SID_TYPE ZIp;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_TYPE ZIt;
		SID_TYPE ZIq;

		ZRmacro_Hparam_Hdeclaration (&ZIt);
		/* BEGINNING OF INLINE: 164 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZRmacro_Hparam_Hlist (&ZIq);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: type_list_none */
					{
#line 332 "syntax.act"

		(ZIq) = NULL;
	
#line 2716 "syntax.c"
					}
					/* END OF ACTION: type_list_none */
				}
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 164 */
		/* BEGINNING OF ACTION: type_list_cons */
		{
#line 341 "syntax.act"

		(ZIp) = make_subtype ((ZIt), TYPE_LIST);
		(ZIp)->v.next = (ZIq);
	
#line 2734 "syntax.c"
		}
		/* END OF ACTION: type_list_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR324(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 52:
		{
			SID_TYPE ZIt;
			SID_IDENTIFIER ZIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRqualified_Htype (&ZIt);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRidentifier (&ZIid);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_promote */
			{
#line 687 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, TYPE_PROMOTE);
		type *s = expand_type((ZIt));

		switch (s->id) {
		case TYPE_INT:
		case TYPE_SIGNED:
		case TYPE_UNSIGNED:
			break;

		default:
			error(ERR_SERIOUS, "Non-integral promotion type");
			break;
		}

		t->v.next = s;
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN);
	
#line 2802 "syntax.c"
			}
			/* END OF ACTION: declare_promote */
		}
		break;
	case 54:
		{
			SID_STRING ZIs;
			SID_TYPE ZIt;
			SID_IDENTIFIER ZIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 57:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 2:
				/* BEGINNING OF EXTRACT: string */
				{
#line 149 "syntax.act"
 ZIs = token_value; 
#line 2827 "syntax.c"
				}
				/* END OF EXTRACT: string */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_special */
			{
#line 284 "syntax.act"

		(ZIt) = special_type((ZIs));
	
#line 2848 "syntax.c"
			}
			/* END OF ACTION: type_special */
			ZRidentifier (&ZIid);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_typedef */
			{
#line 723 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, TYPE_DEFINED);
		t->v.next = check_type((ZIt), OBJ_TYPE);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN);
	
#line 2864 "syntax.c"
			}
			/* END OF ACTION: declare_typedef */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 41: case 43: case 44: case 45:
	case 46: case 47: case 48: case 49:
		{
			SID_TYPE ZIs;
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIp;
			SID_TYPE ZIt;

			ZRqualified_Htype (&ZIs);
			ZRdeclarator (&ZIid, &ZIp);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 2891 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_typedef */
			{
#line 723 "syntax.act"

		type *t = make_type((ZIid).iname, (ZIid).ivers, TYPE_DEFINED);
		t->v.next = check_type((ZIt), OBJ_TYPE);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN);
	
#line 2902 "syntax.c"
			}
			/* END OF ACTION: declare_typedef */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR325(int *ZIcmd, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	switch (CURRENT_TERMINAL) {
	case 2:
		{
			SID_STRING ZIs;
			SID_STRING ZIkey;

			ZRsubset_Hname (&ZIs);
			ZRsubset_Hkey (&ZIkey);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: include_subset */
			{
#line 553 "syntax.act"

		object *p = make_subset((ZIs));
		update_time(crt_object, p);
		(ZIc) = make_object((ZIkey), (*ZIcmd));
		(ZIc)->u.u_obj = p;
	
#line 2946 "syntax.c"
			}
			/* END OF ACTION: include_subset */
		}
		break;
	case 57:
		{
			SID_STRING ZIs;
			SID_STRING ZIkey1;
			SID_STRING ZIkey;

			ZRuse_Hsubset_Hname (&ZIs);
			ZRsubset_Hkey (&ZIkey1);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: subset_next */
			{
#line 474 "syntax.act"
 (ZIkey) = xstrcat((ZIkey1), "G"); 
#line 2967 "syntax.c"
			}
			/* END OF ACTION: subset_next */
			/* BEGINNING OF ACTION: include_subset */
			{
#line 553 "syntax.act"

		object *p = make_subset((ZIs));
		update_time(crt_object, p);
		(ZIc) = make_object((ZIkey), (*ZIcmd));
		(ZIc)->u.u_obj = p;
	
#line 2979 "syntax.c"
			}
			/* END OF ACTION: include_subset */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR326(SID_STRING *ZInm, int *ZIv, SID_IDENTIFIER *ZOid)
{
	SID_IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 70:
		{
			SID_STRING ZItnm;
			int ZItv;

			ADVANCE_LEXER;
			ZRexternal_Hname (&ZItnm, &ZItv);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: make_id */
			{
#line 436 "syntax.act"

		(ZIid).iname = (*ZInm);
		(ZIid).ivers = (*ZIv);
		(ZIid).ename = (ZItnm);
		(ZIid).evers = (ZItv);
	
#line 3023 "syntax.c"
			}
			/* END OF ACTION: make_id */
		}
		break;
	default:
		{
			SID_STRING ZItnm;

			/* BEGINNING OF ACTION: token_name */
			{
#line 432 "syntax.act"

		(ZItnm) = token_name((*ZInm));
	
#line 3038 "syntax.c"
			}
			/* END OF ACTION: token_name */
			/* BEGINNING OF ACTION: make_id */
			{
#line 436 "syntax.act"

		(ZIid).iname = (*ZInm);
		(ZIid).ivers = (*ZIv);
		(ZIid).ename = (ZItnm);
		(ZIid).evers = (*ZIv);
	
#line 3050 "syntax.c"
			}
			/* END OF ACTION: make_id */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOid = ZIid;
}

static void
ZR327(SID_STRING *ZOp)
{
	SID_STRING ZIp;

	switch (CURRENT_TERMINAL) {
	case 58:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_empty */
			{
#line 407 "syntax.act"
 (ZIp) = "";   
#line 3079 "syntax.c"
			}
			/* END OF ACTION: param_empty */
		}
		break;
	case 0:
		{
			ZRdefine_Hparam_Hlist (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 204 "syntax.act"
 (ZItag) = TYPE_ENUM_TAG;   
#line 3125 "syntax.c"
			}
			/* END OF ACTION: key_enum_tag */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_enum */
			{
#line 207 "syntax.act"
 (ZItag) = TYPE_ENUM;       
#line 3136 "syntax.c"
			}
			/* END OF ACTION: key_enum */
		}
		break;
	case 76:
		return;
	}
	*ZOtag = ZItag;
}

static void
ZRenumerator(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_STRING ZIs;

		ZRidentifier (&ZIid);
		/* BEGINNING OF INLINE: 221 */
		{
			switch (CURRENT_TERMINAL) {
			case 67:
				{
					ADVANCE_LEXER;
					ZRconstant_Hvalue (&ZIs);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: value_none */
					{
#line 361 "syntax.act"

		(ZIs) = "";
	
#line 3181 "syntax.c"
					}
					/* END OF ACTION: value_none */
				}
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 221 */
		/* BEGINNING OF ACTION: declare_enumerator */
		{
#line 645 "syntax.act"

		object *p = make_exp((ZIid).iname, (ZIid).ivers, OBJ_ENUMVAL);
		p->u.u_str = (ZIs);
		(ZIc) = make_token((ZIid).ename, (ZIid).evers, p, OBJ_EXTERN);
	
#line 3200 "syntax.c"
		}
		/* END OF ACTION: declare_enumerator */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRfield_Hdeclarator_Hlist(SID_TYPE ZIm, SID_TYPE ZIs, SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_IDENTIFIER ZIid;
		SID_TYPE ZIp;
		SID_TYPE ZIt;
		SID_COMMAND ZIa;
		SID_COMMAND ZIb;

		ZRfield_Hdeclarator (&ZIid, &ZIp);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIp), (ZIs));
	
#line 3238 "syntax.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: declare_field */
		{
#line 657 "syntax.act"

		type *t = check_type((ZIt), OBJ_FIELD);
		field *f = make_field((ZIid).iname, (ZIid).ivers, (ZIm), t);
		(ZIa) = make_token((ZIid).ename, (ZIid).evers, f->obj, OBJ_FIELD);
	
#line 3249 "syntax.c"
		}
		/* END OF ACTION: declare_field */
		/* BEGINNING OF INLINE: 240 */
		{
			switch (CURRENT_TERMINAL) {
			case 63:
				{
					ADVANCE_LEXER;
					ZRfield_Hdeclarator_Hlist (ZIm, ZIs, &ZIb);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: command_none */
					{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 3273 "syntax.c"
					}
					/* END OF ACTION: command_none */
				}
				break;
			}
		}
		/* END OF INLINE: 240 */
		/* BEGINNING OF ACTION: command_join */
		{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 3287 "syntax.c"
		}
		/* END OF ACTION: command_join */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR330(SID_STRING *ZI328, SID_STRING *ZOp)
{
	SID_STRING ZIp;

	switch (CURRENT_TERMINAL) {
	case 63:
		{
			SID_STRING ZIq;

			ADVANCE_LEXER;
			ZRdefine_Hparam_Hlist (&ZIq);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: param_join */
			{
#line 410 "syntax.act"

		(ZIp) = string_printf("%s, %s", (*ZI328), (ZIq));
	
#line 3321 "syntax.c"
			}
			/* END OF ACTION: param_join */
		}
		break;
	default:
		{
			ZIp = *ZI328;
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR331(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ADVANCE_LEXER;
			ZR332 (&ZIcmd);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cmd_exp */
			{
#line 499 "syntax.act"
 (ZIcmd) = OBJ_EXP;       
#line 3364 "syntax.c"
			}
			/* END OF ACTION: cmd_exp */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR332(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 33:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_constant */
			{
#line 498 "syntax.act"
 (ZIcmd) = OBJ_CONST;     
#line 3400 "syntax.c"
			}
			/* END OF ACTION: cmd_constant */
		}
		break;
	case 36:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_exp_extern */
			{
#line 500 "syntax.act"
 (ZIcmd) = OBJ_EXTERN;    
#line 3419 "syntax.c"
			}
			/* END OF ACTION: cmd_exp_extern */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZRfield_Hexact(bool *ZOe)
{
	bool ZIe;

	switch (CURRENT_TERMINAL) {
	case 61:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: true */
			{
#line 164 "syntax.act"
 (ZIe) = 1; 
#line 3450 "syntax.c"
			}
			/* END OF ACTION: true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: false */
			{
#line 163 "syntax.act"
 (ZIe) = 0; 
#line 3461 "syntax.c"
			}
			/* END OF ACTION: false */
		}
		break;
	case 76:
		return;
	}
	*ZOe = ZIe;
}

static void
ZR335(SID_TYPE *ZI333, SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 33: case 41: case 49:
		{
			unsigned ZIcv;

			ZRtype_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_qualify */
			{
#line 317 "syntax.act"

		(ZIt) = make_subtype((*ZI333), TYPE_QUALIFIER);
		(ZIt)->v.str = cv_qualifier[(ZIcv)];
	
#line 3494 "syntax.c"
			}
			/* END OF ACTION: type_qualify */
		}
		break;
	default:
		{
			ZIt = *ZI333;
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
			case 72:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcommand_Hlist (&ZIb);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 3553 "syntax.c"
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 3576 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	case 3: case 20:
		{
			ZRvariable_Hcommand ();
			switch (CURRENT_TERMINAL) {
			case 72:
				break;
			case 76:
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
		UNREACHED;
	default:
		{
			/* BEGINNING OF ACTION: command_none */
			{
#line 514 "syntax.act"

		(ZIc) = NULL;
	
#line 3607 "syntax.c"
			}
			/* END OF ACTION: command_none */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZR337(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 58:
		{
			SID_TYPE ZIp;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_list_empty */
			{
#line 337 "syntax.act"

		error(ERR_WARN, "Empty parameter list");
		(ZIp) = NULL;
	
#line 3641 "syntax.c"
			}
			/* END OF ACTION: type_list_empty */
			/* BEGINNING OF ACTION: type_func */
			{
#line 307 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 3651 "syntax.c"
			}
			/* END OF ACTION: type_func */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 41: case 43: case 44: case 45:
	case 46: case 47: case 48: case 49:
		{
			SID_TYPE ZIp;

			ZRparameter_Hlist (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_func */
			{
#line 307 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 3681 "syntax.c"
			}
			/* END OF ACTION: type_func */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZR340(SID_STRING *ZI338, SID_TYPE *ZI339, SID_STRING *ZO308, SID_TYPE *ZO309)
{
	SID_STRING ZI308;
	SID_TYPE ZI309;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			SID_TYPE ZIs;
			SID_TYPE ZIt;

			ZRfunction_Hoperator (&ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((*ZI339), (ZIs));
	
#line 3722 "syntax.c"
			}
			/* END OF ACTION: type_inject */
			ZR310 (*ZI338, ZIt, &ZI308, &ZI309);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			ZR310 (*ZI338, *ZI339, &ZI308, &ZI309);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZO308 = ZI308;
	*ZO309 = ZI309;
}

static void
ZRdirect_Hdeclarator(SID_IDENTIFIER *ZO318, SID_TYPE *ZO319)
{
	SID_IDENTIFIER ZI318;
	SID_TYPE ZI319;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			SID_IDENTIFIER ZIid;
			SID_TYPE ZIt;

			ADVANCE_LEXER;
			ZRdeclarator (&ZIid, &ZIt);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR320 (ZIid, ZIt, &ZI318, &ZI319);
			if ((CURRENT_TERMINAL) == 76) {
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 272 "syntax.act"

		(ZIt) = NULL;
	
#line 3800 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR320 (ZIid, ZIt, &ZI318, &ZI319);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZO318 = ZI318;
	*ZO319 = ZI319;
}

static void
ZR341(SID_TYPE *ZOq)
{
	SID_TYPE ZIq;

	switch (CURRENT_TERMINAL) {
	case 66:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_list_ellipsis */
			{
#line 346 "syntax.act"

		(ZIq) = make_subtype(type_ellipsis, TYPE_LIST);
		(ZIq)->v.next = NULL;
	
#line 3840 "syntax.c"
			}
			/* END OF ACTION: type_list_ellipsis */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 41: case 43: case 44: case 45:
	case 46: case 47: case 48: case 49:
		{
			ZRparameter_Hlist (&ZIq);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOq = ZIq;
}

static void
ZRtype_Hcommand(int *ZOtag)
{
	int ZItag;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ADVANCE_LEXER;
			ZR342 (&ZItag);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 45:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct_tag */
			{
#line 202 "syntax.act"
 (ZItag) = TYPE_STRUCT_TAG; 
#line 3893 "syntax.c"
			}
			/* END OF ACTION: key_struct_tag */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union_tag */
			{
#line 203 "syntax.act"
 (ZItag) = TYPE_UNION_TAG;  
#line 3905 "syntax.c"
			}
			/* END OF ACTION: key_union_tag */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_type */
			{
#line 201 "syntax.act"
 (ZItag) = TYPE_GENERIC;    
#line 3916 "syntax.c"
			}
			/* END OF ACTION: key_type */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOtag = ZItag;
}

static void
ZR342(int *ZOtag)
{
	int ZItag;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_arith */
			{
#line 212 "syntax.act"
 (ZItag) = TYPE_ARITH;      
#line 3952 "syntax.c"
			}
			/* END OF ACTION: key_arith */
		}
		break;
	case 37:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_float */
			{
#line 211 "syntax.act"
 (ZItag) = TYPE_FLOAT;      
#line 3971 "syntax.c"
			}
			/* END OF ACTION: key_float */
		}
		break;
	case 38:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_int */
			{
#line 208 "syntax.act"
 (ZItag) = TYPE_INT;        
#line 3990 "syntax.c"
			}
			/* END OF ACTION: key_int */
		}
		break;
	case 42:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_scalar */
			{
#line 213 "syntax.act"
 (ZItag) = TYPE_SCALAR;     
#line 4009 "syntax.c"
			}
			/* END OF ACTION: key_scalar */
		}
		break;
	case 44:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_signed */
			{
#line 209 "syntax.act"
 (ZItag) = TYPE_SIGNED;     
#line 4028 "syntax.c"
			}
			/* END OF ACTION: key_signed */
		}
		break;
	case 45:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct */
			{
#line 205 "syntax.act"
 (ZItag) = TYPE_STRUCT;     
#line 4047 "syntax.c"
			}
			/* END OF ACTION: key_struct */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union */
			{
#line 206 "syntax.act"
 (ZItag) = TYPE_UNION;      
#line 4066 "syntax.c"
			}
			/* END OF ACTION: key_union */
		}
		break;
	case 47:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_unsigned */
			{
#line 210 "syntax.act"
 (ZItag) = TYPE_UNSIGNED;   
#line 4085 "syntax.c"
			}
			/* END OF ACTION: key_unsigned */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 153 "syntax.act"
 ZIs = token_value; 
#line 4117 "syntax.c"
			}
			/* END OF EXTRACT: build-insert */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_build_insert */
			{
#line 597 "syntax.act"

		(ZIc) = make_object((ZIs), OBJ_TEXT_SRC);
	
#line 4127 "syntax.c"
			}
			/* END OF ACTION: declare_build_insert */
		}
		break;
	case 4:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: comment */
			{
#line 151 "syntax.act"
 ZIs = token_value; 
#line 4140 "syntax.c"
			}
			/* END OF EXTRACT: comment */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_comment */
			{
#line 589 "syntax.act"

		(ZIc) = make_object((ZIs), OBJ_TEXT_INCL);
	
#line 4150 "syntax.c"
			}
			/* END OF ACTION: declare_comment */
		}
		break;
	case 5:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: insert */
			{
#line 152 "syntax.act"
 ZIs = token_value; 
#line 4163 "syntax.c"
			}
			/* END OF EXTRACT: insert */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_insert */
			{
#line 593 "syntax.act"

		(ZIc) = make_object((ZIs), OBJ_TEXT_INCL);
	
#line 4173 "syntax.c"
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
			/* BEGINNING OF INLINE: 295 */
			{
				switch (CURRENT_TERMINAL) {
				case 10:
					{
						ADVANCE_LEXER;
						ZRcommand_Hlist (&ZIb);
						if ((CURRENT_TERMINAL) == 76) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: command_none */
						{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 4208 "syntax.c"
						}
						/* END OF ACTION: command_none */
					}
					break;
				case 76:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 295 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: command_endif */
			{
#line 815 "syntax.act"

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
	
#line 4244 "syntax.c"
			}
			/* END OF ACTION: command_endif */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRname_Hversion(int *ZOv)
{
	int ZIv;

	switch (CURRENT_TERMINAL) {
	case 64:
		{
			SID_STRING ZIn;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 148 "syntax.act"
 ZIn = token_value; 
#line 4279 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: version_number */
			{
#line 461 "syntax.act"

		(ZIv) = atoi((ZIn));
	
#line 4293 "syntax.c"
			}
			/* END OF ACTION: version_number */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: version_none */
			{
#line 457 "syntax.act"

		(ZIv) = no_version;
	
#line 4306 "syntax.c"
			}
			/* END OF ACTION: version_none */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOv = ZIv;
}

static void
ZRdirect_Habstract_Hdeclarator(SID_STRING *ZO308, SID_TYPE *ZO309)
{
	SID_STRING ZI308;
	SID_TYPE ZI309;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZInm;
			SID_TYPE ZIt;

			/* BEGINNING OF EXTRACT: name */
			{
#line 147 "syntax.act"
 ZInm = token_value; 
#line 4338 "syntax.c"
			}
			/* END OF EXTRACT: name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_none */
			{
#line 272 "syntax.act"

		(ZIt) = NULL;
	
#line 4348 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR310 (ZInm, ZIt, &ZI308, &ZI309);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 57:
		{
			SID_STRING ZI338;
			SID_TYPE ZI339;

			ADVANCE_LEXER;
			ZRabstract_Hdeclarator (&ZI338, &ZI339);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR340 (&ZI338, &ZI339, &ZI308, &ZI309);
			if ((CURRENT_TERMINAL) == 76) {
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
#line 420 "syntax.act"

		(ZInm) = NULL;
	
#line 4393 "syntax.c"
			}
			/* END OF ACTION: name_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 272 "syntax.act"

		(ZIt) = NULL;
	
#line 4402 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR310 (ZInm, ZIt, &ZI308, &ZI309);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZO308 = ZI308;
	*ZO309 = ZI309;
}

static void
ZRfield_Hdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			SID_IDENTIFIER ZI343;
			SID_TYPE ZI344;

			ADVANCE_LEXER;
			ZRdeclarator (&ZI343, &ZI344);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR320 (ZI343, ZI344, &ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 62:
		{
			ZRbitfield_Hoperator (&ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: id_anon */
			{
#line 450 "syntax.act"

		char *nm;

		nm = string_printf ("%s%d", HIDDEN_NAME, anon_no++);
		if (crt_field_name) {
			nm = string_printf("%s.%s", crt_field_name, nm);
		}

		(ZIid).iname = nm;
		(ZIid).ivers = no_version;
		(ZIid).ename = token_name(nm);
		(ZIid).evers = no_version;
	
#line 4478 "syntax.c"
			}
			/* END OF ACTION: id_anon */
		}
		break;
	case 0:
		{
			SID_IDENTIFIER ZI347;

			ZRidentifier (&ZI347);
			ZR349 (&ZI347, &ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 73:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRdeclarator (&ZIid, &ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 4512 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 149 "syntax.act"
 ZIs = token_value; 
#line 4546 "syntax.c"
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
#line 150 "syntax.act"
 ZInm = token_value; 
#line 4564 "syntax.c"
			}
			/* END OF EXTRACT: variable */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 67:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR356 (&ZInm);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (76);
	return;
}

static void
ZR349(SID_IDENTIFIER *ZI347, SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 62:
		{
			ZRbitfield_Hoperator (&ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			ZIid = *ZI347;
		}
		break;
	default:
		{
			SID_TYPE ZI346;

			/* BEGINNING OF ACTION: type_none */
			{
#line 272 "syntax.act"

		(ZI346) = NULL;
	
#line 4620 "syntax.c"
			}
			/* END OF ACTION: type_none */
			ZR320 (*ZI347, ZI346, &ZIid, &ZIt);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZR350(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ADVANCE_LEXER;
			ZR351 (&ZIcmd);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cmd_func */
			{
#line 501 "syntax.act"
 (ZIcmd) = OBJ_FUNC;      
#line 4664 "syntax.c"
			}
			/* END OF ACTION: cmd_func */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR351(int *ZOcmd)
{
	int ZIcmd;

	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_func_extern */
			{
#line 502 "syntax.act"
 (ZIcmd) = OBJ_EXTERN;    
#line 4700 "syntax.c"
			}
			/* END OF ACTION: cmd_func_extern */
		}
		break;
	case 50:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cmd_func_weak */
			{
#line 503 "syntax.act"
 (ZIcmd) = OBJ_WEAK;      
#line 4719 "syntax.c"
			}
			/* END OF ACTION: cmd_func_weak */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZRdefine_Hparam_Hclause(SID_STRING *ZOp)
{
	SID_STRING ZIp;

	switch (CURRENT_TERMINAL) {
	case 57:
		{
			ADVANCE_LEXER;
			ZR327 (&ZIp);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: param_none */
			{
#line 406 "syntax.act"
 (ZIp) = NULL; 
#line 4759 "syntax.c"
			}
			/* END OF ACTION: param_none */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 498 "syntax.act"
 (ZIcmd) = OBJ_CONST;     
#line 4788 "syntax.c"
			}
			/* END OF ACTION: cmd_constant */
		}
		break;
	case 13:
		{
			ADVANCE_LEXER;
			ZR331 (&ZIcmd);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOcmd = ZIcmd;
}

static void
ZR352(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 58:
		{
			SID_TYPE ZIp;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_list_none */
			{
#line 332 "syntax.act"

		(ZIp) = NULL;
	
#line 4833 "syntax.c"
			}
			/* END OF ACTION: type_list_none */
			/* BEGINNING OF ACTION: type_macro */
			{
#line 312 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 4843 "syntax.c"
			}
			/* END OF ACTION: type_macro */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 40: case 41: case 43: case 44:
	case 45: case 46: case 47: case 48:
	case 49:
		{
			SID_TYPE ZIp;

			ZRmacro_Hparam_Hlist (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_macro */
			{
#line 312 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PROC);
		(ZIt)->v.next = (ZIp);
	
#line 4874 "syntax.c"
			}
			/* END OF ACTION: type_macro */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_if */
			{
#line 798 "syntax.act"

		(ZIc) = make_object ((ZIs), OBJ_IF);
		(ZIc)->u.u_iftype = CMD_IF;
	
#line 4914 "syntax.c"
			}
			/* END OF ACTION: command_if */
		}
		break;
	case 17:
		{
			ADVANCE_LEXER;
			ZRifdef_Hmacro_Hname (&ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_ifdef */
			{
#line 803 "syntax.act"

		(ZIc) = make_object ((ZIs), OBJ_IF);
		(ZIc)->u.u_iftype = CMD_IFDEF;
	
#line 4934 "syntax.c"
			}
			/* END OF ACTION: command_ifdef */
		}
		break;
	case 18:
		{
			ADVANCE_LEXER;
			ZRifdef_Hmacro_Hname (&ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_ifndef */
			{
#line 808 "syntax.act"

		(ZIc) = make_object ((ZIs), OBJ_IF);
		(ZIc)->u.u_iftype = CMD_IFNDEF;
	
#line 4954 "syntax.c"
			}
			/* END OF ACTION: command_ifndef */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
	case 68:
		{
			ADVANCE_LEXER;
			ZR354 (&ZIkey);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 71:
		{
			ADVANCE_LEXER;
			ZR355 (&ZIkey);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZR354(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 68:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_both */
			{
#line 473 "syntax.act"
 (ZIkey) = "11"; 
#line 5032 "syntax.c"
			}
			/* END OF ACTION: subset_both */
		}
		break;
	case 71:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_first */
			{
#line 471 "syntax.act"
 (ZIkey) = "10"; 
#line 5051 "syntax.c"
			}
			/* END OF ACTION: subset_first */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZR355(SID_STRING *ZOkey)
{
	SID_STRING ZIkey;

	switch (CURRENT_TERMINAL) {
	case 68:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_second */
			{
#line 472 "syntax.act"
 (ZIkey) = "01"; 
#line 5089 "syntax.c"
			}
			/* END OF ACTION: subset_second */
		}
		break;
	case 71:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 58:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: subset_none */
			{
#line 470 "syntax.act"
 (ZIkey) = "00"; 
#line 5108 "syntax.c"
			}
			/* END OF ACTION: subset_none */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOkey = ZIkey;
}

static void
ZR356(SID_STRING *ZInm)
{
	switch (CURRENT_TERMINAL) {
	case 69:
		{
			SID_STRING ZIs;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 148 "syntax.act"
 ZIs = token_value; 
#line 5141 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: variable_minus */
			{
#line 574 "syntax.act"

		set_integer((*ZInm), -atoi((ZIs)));
	
#line 5155 "syntax.c"
			}
			/* END OF ACTION: variable_minus */
		}
		break;
	case 1:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: number */
			{
#line 148 "syntax.act"
 ZIs = token_value; 
#line 5168 "syntax.c"
			}
			/* END OF EXTRACT: number */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: variable_plus */
			{
#line 570 "syntax.act"

		set_integer((*ZInm), atoi((ZIs)));
	
#line 5178 "syntax.c"
			}
			/* END OF ACTION: variable_plus */
		}
		break;
	case 2:
		{
			SID_STRING ZIs;

			/* BEGINNING OF EXTRACT: string */
			{
#line 149 "syntax.act"
 ZIs = token_value; 
#line 5191 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: variable_string */
			{
#line 566 "syntax.act"

		set_string((*ZInm), (ZIs));
	
#line 5201 "syntax.c"
			}
			/* END OF ACTION: variable_string */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (76);
	return;
}

static void
ZRbitfield_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 62:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRconstant_Hvalue (&ZIa);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_bitfield */
		{
#line 302 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_BITFIELD );
		(ZIt)->v.str = (ZIa);
	
#line 5247 "syntax.c"
		}
		/* END OF ACTION: type_bitfield */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOt = ZIt;
}

static void
ZRuse_Hsubset_Hname(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZIa;
		SID_STRING ZIb;

		switch (CURRENT_TERMINAL) {
		case 57:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 149 "syntax.act"
 ZIa = token_value; 
#line 5284 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 58:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 63:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 149 "syntax.act"
 ZIb = token_value; 
#line 5312 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: file_name */
		{
#line 481 "syntax.act"

		(ZIs) = subset_name((ZIa), (ZIb), NULL);
	
#line 5326 "syntax.c"
		}
		/* END OF ACTION: file_name */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOs = ZIs;
}

void
read_spec(SID_COMMAND *ZOc)
{
	SID_COMMAND ZIc;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		ZRsubset_Hcommand (&ZIc);
		switch (CURRENT_TERMINAL) {
		case 72:
			break;
		case 76:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 74:
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
#line 838 "syntax.act"

		error(ERR_SERIOUS, "Syntax error");
	
#line 5375 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
		/* BEGINNING OF ACTION: command_none */
		{
#line 514 "syntax.act"

		(ZIc) = NULL;
	
#line 5384 "syntax.c"
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
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 272 "syntax.act"

		(ZIt) = NULL;
	
#line 5412 "syntax.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 73:
		{
			SID_TYPE ZIp;
			SID_TYPE ZIs;

			ZRptr_Hoperator (&ZIp);
			ZRmacro_Hdeclarator (&ZIid, &ZIs);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 288 "syntax.act"

		(ZIt) = inject_type((ZIs), (ZIp));
	
#line 5434 "syntax.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOid = ZIid;
	*ZOt = ZIt;
}

static void
ZRsubset_Hname(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		SID_STRING ZIa;

		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 149 "syntax.act"
 ZIa = token_value; 
#line 5470 "syntax.c"
			}
			/* END OF EXTRACT: string */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR322 (&ZIa, &ZIs);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRbuiltin_Htype(unsigned *ZOb)
{
	unsigned ZIb;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		unsigned ZIa;
		unsigned ZIc;

		ZRtype_Hkeyword (&ZIa);
		/* BEGINNING OF INLINE: 103 */
		{
			switch (CURRENT_TERMINAL) {
			case 32: case 34: case 37: case 38:
			case 39: case 43: case 44: case 47:
			case 48:
				{
					unsigned ZId;

					ZRbuiltin_Htype (&ZId);
					if ((CURRENT_TERMINAL) == 76) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: btype_join */
					{
#line 183 "syntax.act"

		while ((ZIa) & (ZId)) {
			if ((ZIa) == BTYPE_LONG) {
				(ZIa) = BTYPE_LLONG;
			} else {
				error(ERR_SERIOUS, "Duplicate type specifier");
				break;
			}
		}

		(ZIc) = ((ZIa) | (ZId));
	
#line 5534 "syntax.c"
					}
					/* END OF ACTION: btype_join */
				}
				break;
			default:
				{
					ZIc = ZIa;
				}
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 103 */
		ZIb = ZIc;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 214 "syntax.act"
 (ZIlv) = TYPE_LVALUE;     
#line 5573 "syntax.c"
			}
			/* END OF ACTION: key_lvalue */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: key_rvalue */
			{
#line 215 "syntax.act"
 (ZIlv) = TYPE_RVALUE;     
#line 5584 "syntax.c"
			}
			/* END OF ACTION: key_rvalue */
		}
		break;
	case 76:
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
			/* BEGINNING OF INLINE: 243 */
			{
				switch (CURRENT_TERMINAL) {
				case 10:
					{
						ADVANCE_LEXER;
						ZRfield_Hlist (ZIm, &ZIb);
						if ((CURRENT_TERMINAL) == 76) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: command_none */
						{
#line 514 "syntax.act"

		(ZIb) = NULL;
	
#line 5633 "syntax.c"
						}
						/* END OF ACTION: command_none */
					}
					break;
				case 76:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 243 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: command_endif */
			{
#line 815 "syntax.act"

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
	
#line 5669 "syntax.c"
			}
			/* END OF ACTION: command_endif */
			ZRfield_Hlist (ZIm, &ZIc2);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIc1), (ZIc2));
	
#line 5683 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	case 0: case 32: case 33: case 34:
	case 35: case 37: case 38: case 39:
	case 41: case 43: case 44: case 45:
	case 46: case 47: case 48: case 49:
		{
			SID_TYPE ZIt;
			SID_COMMAND ZIa;
			SID_COMMAND ZIb;

			ZRqualified_Htype (&ZIt);
			ZRfield_Hdeclarator_Hlist (ZIm, ZIt, &ZIa);
			switch (CURRENT_TERMINAL) {
			case 72:
				break;
			case 76:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRfield_Hlist (ZIm, &ZIb);
			if ((CURRENT_TERMINAL) == 76) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: command_join */
			{
#line 518 "syntax.act"

		(ZIc) = join_object((ZIa), (ZIb));
	
#line 5720 "syntax.c"
			}
			/* END OF ACTION: command_join */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: command_none */
			{
#line 514 "syntax.act"

		(ZIc) = NULL;
	
#line 5733 "syntax.c"
			}
			/* END OF ACTION: command_none */
		}
		break;
	case 76:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
ZRptr_Hoperator(SID_TYPE *ZOt)
{
	SID_TYPE ZIt;

	if ((CURRENT_TERMINAL) == 76) {
		return;
	}
	{
		unsigned ZIcv;

		switch (CURRENT_TERMINAL) {
		case 73:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRtype_Hqualifier_Hopt (&ZIcv);
		if ((CURRENT_TERMINAL) == 76) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_ptr */
		{
#line 292 "syntax.act"

		(ZIt) = make_subtype((type *) NULL, TYPE_PTR);
		(ZIt)->v.str = cv_qualifier[(ZIcv)];
	
#line 5779 "syntax.c"
		}
		/* END OF ACTION: type_ptr */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
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
#line 172 "syntax.act"
 (ZIb) = BTYPE_CHAR;     
#line 5804 "syntax.c"
			}
			/* END OF ACTION: btype_char */
		}
		break;
	case 34:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_double */
			{
#line 179 "syntax.act"
 (ZIb) = BTYPE_DOUBLE;   
#line 5816 "syntax.c"
			}
			/* END OF ACTION: btype_double */
		}
		break;
	case 37:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_float */
			{
#line 178 "syntax.act"
 (ZIb) = BTYPE_FLOAT;    
#line 5828 "syntax.c"
			}
			/* END OF ACTION: btype_float */
		}
		break;
	case 38:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_int */
			{
#line 174 "syntax.act"
 (ZIb) = BTYPE_INT;      
#line 5840 "syntax.c"
			}
			/* END OF ACTION: btype_int */
		}
		break;
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_long */
			{
#line 175 "syntax.act"
 (ZIb) = BTYPE_LONG;     
#line 5852 "syntax.c"
			}
			/* END OF ACTION: btype_long */
		}
		break;
	case 43:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_short */
			{
#line 173 "syntax.act"
 (ZIb) = BTYPE_SHORT;    
#line 5864 "syntax.c"
			}
			/* END OF ACTION: btype_short */
		}
		break;
	case 44:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_signed */
			{
#line 176 "syntax.act"
 (ZIb) = BTYPE_SIGNED;   
#line 5876 "syntax.c"
			}
			/* END OF ACTION: btype_signed */
		}
		break;
	case 47:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_unsigned */
			{
#line 177 "syntax.act"
 (ZIb) = BTYPE_UNSIGNED; 
#line 5888 "syntax.c"
			}
			/* END OF ACTION: btype_unsigned */
		}
		break;
	case 48:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_void */
			{
#line 180 "syntax.act"
 (ZIb) = BTYPE_VOID;     
#line 5900 "syntax.c"
			}
			/* END OF ACTION: btype_void */
		}
		break;
	case 76:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (76);
	return;
ZL0:;
	*ZOb = ZIb;
}

/* BEGINNING OF TRAILER */

#line 841 "syntax.act"

#line 5922 "syntax.c"

/* END OF FILE */
