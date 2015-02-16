/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT
#line 192 "syntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "inttype.h"
#include "label.h"
#include "lex.h"
#include "literal.h"
#include "member.h"
#include "namespace.h"
#include "parse.h"
#include "pragma.h"
#include "predict.h"
#include "preproc.h"
#include "redeclare.h"
#include "rewrite.h"
#include "statement.h"
#include "symbols.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "typeid.h"
#include "variable.h"


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;
typedef LIST ( TYPE ) SID_LIST_TYPE ;


/*
    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include "syntax.h"


/*
    The output of sid is automatically generated.  Hence it is not
    necessarily appropriate to apply the same level of checking to this
    as to the rest of the program.  These pragmas describe the relaxations
    allowed for the sid output.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA const conditional allow
#pragma TenDRA unreachable code allow
#pragma TenDRA variable analysis off
#endif


#line 112 "syntax6.c"

void
ZR1608(NAMESPACE *ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 233 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 129 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 497 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 139 "syntax6.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 506 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 148 "syntax6.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZItid;

			/* BEGINNING OF INLINE: any-type-name */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						/* BEGINNING OF EXTRACT: template-type */
						{
#line 251 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 171 "syntax6.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 225 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 184 "syntax6.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: any-type-name */
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 497 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 201 "syntax6.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 506 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 210 "syntax6.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			int ZIq;
			IDENTIFIER ZIuid;

			ZRtemplate_Hopt (*ZIns, &ZIq);
			ZRnested_Hid (*ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 497 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 233 "syntax6.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 523 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 242 "syntax6.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRany_Hnested_Hname_Hopt(NAMESPACE *ZOns)
{
	NAMESPACE ZIns;

	switch (CURRENT_TERMINAL) {
	case 8: case 9: case 83:
		{
			ZRany_Hnested_Hname (&ZIns);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: namespace_none */
			{
#line 484 "syntax.act"

    (ZIns) = NULL_nspace ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 284 "syntax6.c"
			}
			/* END OF ACTION: namespace_none */
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOns = ZIns;
}

void
ZR1609(NAMESPACE *ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 233 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 315 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 502 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 325 "syntax6.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 506 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 334 "syntax6.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZItid;

			/* BEGINNING OF INLINE: any-type-name */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						/* BEGINNING OF EXTRACT: template-type */
						{
#line 251 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 357 "syntax6.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 225 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 370 "syntax6.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: any-type-name */
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 502 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 387 "syntax6.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 506 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 396 "syntax6.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			int ZIq;
			IDENTIFIER ZIuid;

			ZRtemplate_Hopt (*ZIns, &ZIq);
			ZRnested_Hid (*ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 502 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 419 "syntax6.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 523 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 428 "syntax6.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRinitialiser_Hclause(IDENTIFIER ZId, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 8: case 9:
	case 17: case 18: case 19: case 20:
	case 21: case 22: case 23: case 25:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 83: case 85: case 97:
	case 102: case 106: case 110: case 111:
	case 114: case 115: case 116: case 122:
	case 123: case 127: case 130: case 131:
	case 132: case 135: case 140: case 141:
	case 145: case 146: case 148: case 149:
	case 150: case 152: case 156: case 170:
	case 185: case 206: case 210: case 255:
	case 286: case 299: case 330:
		{
			ZRinitialiser_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1475 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 480 "syntax6.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 64:
		{
			SID_LIST_EXP ZIp;

			/* BEGINNING OF INLINE: open-brace */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 64:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: open-brace */
			ZR1003 (&ZId, &ZIp);
			/* BEGINNING OF INLINE: close-brace */
			{
				if ((CURRENT_TERMINAL) == 355) {
					RESTORE_LEXER;
					goto ZL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case 38:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: close-brace */
			/* BEGINNING OF ACTION: exp_aggregate */
			{
#line 588 "syntax.act"

    /* The expression type is a dummy */
    MAKE_exp_aggregate ( type_void, (ZIp), NULL_list ( OFFSET ), (ZIe) ) ;
#line 526 "syntax6.c"
			}
			/* END OF ACTION: exp_aggregate */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRtemplate_Hmember_Hdecl(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIx;
		TOKEN ZIp;
		TYPE ZIt1;

		ZRexport_Hopt (&ZIx);
		switch (CURRENT_TERMINAL) {
		case 147:
			break;
		case 355:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: template_params */
		{
#line 1841 "syntax.act"

    (ZIp) = template_params ( (ZIx) ) ;
    RESCAN_LEXER ;
#line 572 "syntax6.c"
		}
		/* END OF ACTION: template_params */
		/* BEGINNING OF ACTION: template_type */
		{
#line 1833 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 580 "syntax6.c"
		}
		/* END OF ACTION: template_type */
		ZRmember_Hdeclaration (ZIt1, ZIds);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: template_end */
		{
#line 1837 "syntax.act"

    end_template ( (ZIp) ) ;
#line 593 "syntax6.c"
		}
		/* END OF ACTION: template_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2151 "syntax.act"

    RESCAN_LEXER ;
#line 601 "syntax6.c"
		}
		/* END OF ACTION: rescan_token */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1610(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 233 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 627 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 490 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 638 "syntax6.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 506 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 647 "syntax6.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			NAMESPACE ZIns;

			/* BEGINNING OF INLINE: any-type-name */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						/* BEGINNING OF EXTRACT: template-type */
						{
#line 251 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 671 "syntax6.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 225 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 684 "syntax6.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: any-type-name */
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 490 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 702 "syntax6.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 506 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 711 "syntax6.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			NAMESPACE ZIns;
			int ZIq;
			IDENTIFIER ZIuid;

			/* BEGINNING OF ACTION: namespace_global */
			{
#line 490 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 730 "syntax6.c"
			}
			/* END OF ACTION: namespace_global */
			ZRtemplate_Hopt (ZIns, &ZIq);
			ZRnested_Hid (ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 523 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (ZIns) ;
#line 745 "syntax6.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRadditive_Hexpression(EXP *ZO1229)
{
	EXP ZI1229;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRmultiplicative_Hexpression (&ZIe);
		ZR1230 (ZIe, &ZI1229);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1229 = ZI1229;
}

void
ZRdirect_Hdeclarator(TYPE *ZO1176, IDENTIFIER *ZO1177, int *ZO1178)
{
	TYPE ZI1176;
	IDENTIFIER ZI1177;
	int ZI1178;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIt;
			IDENTIFIER ZIid;
			int ZIc;

			ADVANCE_LEXER;
			ZRdeclarator_Haux (&ZIt, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1778 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 814 "syntax6.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1740 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 824 "syntax6.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1179 (ZIt, ZIid, ZIc, &ZI1176, &ZI1177, &ZI1178);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 83: case 141:
		{
			IDENTIFIER ZIid;
			TYPE ZIt;
			int ZIc;

			ZRdeclarator_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1280 "syntax.act"

    (ZIt) = NULL_type ;
#line 859 "syntax6.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2053 "syntax.act"
 (ZIc) = 0 ; 
#line 866 "syntax6.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1711 "syntax.act"

    begin_declarator ( (ZIid), crt_id_qualifier, qual_namespace, 1 ) ;
#line 874 "syntax6.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZIt, ZIid, ZIc, &ZI1176, &ZI1177, &ZI1178);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1176 = ZI1176;
	*ZO1177 = ZI1177;
	*ZO1178 = ZI1178;
}

void
ZR1230(EXP ZI1228, EXP *ZO1229)
{
	EXP ZI1229;

ZL2_1230:;
	switch (CURRENT_TERMINAL) {
	case 59:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRmultiplicative_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_minus */
			{
#line 732 "syntax.act"

    (ZIe) = make_minus_exp ( (ZI1228), (ZIb) ) ;
#line 922 "syntax6.c"
			}
			/* END OF ACTION: exp_minus */
			/* BEGINNING OF INLINE: 1230 */
			ZI1228 = ZIe;
			goto ZL2_1230;
			/* END OF INLINE: 1230 */
		}
		UNREACHED;
	case 69:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRmultiplicative_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_plus */
			{
#line 777 "syntax.act"

    (ZIe) = make_plus_exp ( (ZI1228), (ZIb) ) ;
#line 947 "syntax6.c"
			}
			/* END OF ACTION: exp_plus */
			/* BEGINNING OF INLINE: 1230 */
			ZI1228 = ZIe;
			goto ZL2_1230;
			/* END OF INLINE: 1230 */
		}
		UNREACHED;
	default:
		{
			ZI1229 = ZI1228;
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1229 = ZI1229;
}

void
ZRselection_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 109:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIc;
			EXP ZIa;
			EXP ZIbs;
			EXP ZIbc;
			EXP ZIb;
			EXP ZId;
			EXP ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 1140 "syntax.act"
 (ZIx) = crt_condition ; 
#line 995 "syntax6.c"
			}
			/* END OF ACTION: condition_get */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1011 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			ZRopen_Hround_Hx ();
			ZRcondition (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_if_begin */
			{
#line 988 "syntax.act"

    (ZIa) = begin_if_stmt ( (ZIc) ) ;
#line 1025 "syntax6.c"
			}
			/* END OF ACTION: stmt_if_begin */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 909 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 1040 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			/* BEGINNING OF ACTION: cond_inject */
			{
#line 1106 "syntax.act"

    (ZIbc) = inject_cond ( (ZIbs), (ZIc) ) ;
#line 1048 "syntax6.c"
			}
			/* END OF ACTION: cond_inject */
			ZRscoped_Hstatement (ZIbc, &ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1136 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1060 "syntax6.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_if_cont */
			{
#line 992 "syntax.act"

    (ZId) = cont_if_stmt ( (ZIa), (ZIb) ) ;
#line 1068 "syntax6.c"
			}
			/* END OF ACTION: stmt_if_cont */
			/* BEGINNING OF INLINE: 719 */
			{
				{
					EXP ZIfs;
					EXP ZIfc;

					switch (CURRENT_TERMINAL) {
					case 103:
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: stmt_else */
					{
#line 1001 "syntax.act"

    check_empty_stmt ( lex_else ) ;
#line 1089 "syntax6.c"
					}
					/* END OF ACTION: stmt_else */
					/* BEGINNING OF ACTION: stmt_compound_begin */
					{
#line 909 "syntax.act"

    (ZIfs) = begin_compound_stmt ( 1 ) ;
#line 1097 "syntax6.c"
					}
					/* END OF ACTION: stmt_compound_begin */
					/* BEGINNING OF ACTION: cond_inject */
					{
#line 1106 "syntax.act"

    (ZIfc) = inject_cond ( (ZIfs), (ZIc) ) ;
#line 1105 "syntax6.c"
					}
					/* END OF ACTION: cond_inject */
					ZRscoped_Hstatement (ZIfc, &ZIf);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL3;
					}
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: stmt_no_else */
					{
#line 1005 "syntax.act"

    report ( crt_loc, ERR_stmt_if_no_else () ) ;
    (ZIf) = NULL_exp ;
#line 1123 "syntax6.c"
					}
					/* END OF ACTION: stmt_no_else */
				}
			ZL2:;
			}
			/* END OF INLINE: 719 */
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1136 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1134 "syntax6.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_if_end */
			{
#line 996 "syntax.act"

    (ZIe) = end_if_stmt ( (ZId), (ZIf) ) ;
#line 1142 "syntax6.c"
			}
			/* END OF ACTION: stmt_if_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 1141 "syntax.act"
 crt_condition = (ZIx) ; 
#line 1149 "syntax6.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 1157 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 119:
		{
			int ZIr;
			EXP ZIc;
			EXP ZIa;
			int ZIex;
			EXP ZIbs;
			EXP ZIbc;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1186 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcondition (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_switch_begin */
			{
#line 1033 "syntax.act"

    (ZIa) = begin_switch_stmt ( (ZIc) ) ;
#line 1206 "syntax6.c"
			}
			/* END OF ACTION: stmt_switch_begin */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 723 */
			{
				switch (CURRENT_TERMINAL) {
				case 217:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: bool_true */
						{
#line 2054 "syntax.act"
 (ZIex) = 1 ; 
#line 1226 "syntax6.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2053 "syntax.act"
 (ZIex) = 0 ; 
#line 1237 "syntax6.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 723 */
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 909 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 1250 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			/* BEGINNING OF ACTION: cond_inject */
			{
#line 1106 "syntax.act"

    (ZIbc) = inject_cond ( (ZIbs), (ZIc) ) ;
#line 1258 "syntax6.c"
			}
			/* END OF ACTION: cond_inject */
			ZRscoped_Hstatement (ZIbc, &ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1136 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1270 "syntax6.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_switch_end */
			{
#line 1037 "syntax.act"

    (ZIe) = end_switch_stmt ( (ZIa), (ZIb), (ZIex) ) ;
#line 1278 "syntax6.c"
			}
			/* END OF ACTION: stmt_switch_end */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 1286 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 26:
		{
			ZRtarget_Hcondition (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 1303 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 8: case 9:
	case 17: case 18: case 19: case 20:
	case 21: case 22: case 23: case 25:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 83: case 85: case 97:
	case 102: case 106: case 110: case 111:
	case 114: case 115: case 116: case 122:
	case 123: case 127: case 130: case 131:
	case 132: case 135: case 140: case 141:
	case 145: case 146: case 148: case 149:
	case 150: case 152: case 156: case 170:
	case 185: case 206: case 210: case 255:
	case 286: case 299: case 330:
		{
			EXP ZI1289;

			ZRassignment_Hexpression (&ZI1289);
			ZR1291 (&ZI1289, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 298: case 324:
		{
			EXP ZIa;
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRflow_Hexpression (&ZIa);
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 568 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1370 "syntax6.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 623 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1378 "syntax6.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	case 346:
		{
			EXP ZIa;
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRinset_Hflow_Hexpression (&ZIa);
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 568 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1400 "syntax6.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 623 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1408 "syntax6.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRnew_Hplace_Hand_Htype(SID_LIST_EXP *ZOp, TYPE *ZOt, int *ZOn)
{
	SID_LIST_EXP ZIp;
	TYPE ZIt;
	int ZIn;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 573 */
			{
				{
					/* BEGINNING OF ACTION: is_type_id_false */
					{
#line 2118 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 1446 "syntax6.c"
					}
					/* END OF ACTION: is_type_id_false */
					if (!ZI0)
						goto ZL3;
					ZRtype_Hid (&ZIt, &ZIn);
					switch (CURRENT_TERMINAL) {
					case 39:
						break;
					case 355:
						RESTORE_LEXER;
						goto ZL1;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: list_exp_null */
					{
#line 564 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1467 "syntax6.c"
					}
					/* END OF ACTION: list_exp_null */
					goto ZL2;
				}
				UNREACHED;
			ZL3:;
				switch (CURRENT_TERMINAL) {
				case 1: case 2: case 3: case 5:
				case 6: case 7: case 8: case 9:
				case 17: case 18: case 19: case 20:
				case 21: case 22: case 23: case 25:
				case 33: case 43: case 59: case 61:
				case 62: case 65: case 69: case 71:
				case 78: case 83: case 85: case 97:
				case 102: case 106: case 110: case 111:
				case 114: case 115: case 116: case 122:
				case 123: case 127: case 130: case 131:
				case 132: case 135: case 140: case 141:
				case 145: case 146: case 148: case 149:
				case 150: case 152: case 156: case 170:
				case 185: case 206: case 210: case 255:
				case 286: case 299: case 330:
					{
						int ZItd;
						TYPE ZIs;
						int ZIm;

						ZRexpression_Hlist (&ZIp);
						switch (CURRENT_TERMINAL) {
						case 39:
							break;
						case 355:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_decl_begin */
						{
#line 422 "syntax.act"

    (ZItd) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
#line 1512 "syntax6.c"
						}
						/* END OF ACTION: type_decl_begin */
						/* BEGINNING OF INLINE: 574 */
						{
							switch (CURRENT_TERMINAL) {
							case 65:
								{
									ADVANCE_LEXER;
									ZRtype_Hid (&ZIs, &ZIm);
									switch (CURRENT_TERMINAL) {
									case 39:
										break;
									case 355:
										RESTORE_LEXER;
										goto ZL1;
									default:
										goto ZL1;
									}
									ADVANCE_LEXER;
								}
								break;
							case 2: case 7: case 8: case 9:
							case 25: case 83: case 97: case 98:
							case 102: case 104: case 106: case 110:
							case 111: case 114: case 115: case 118:
							case 121: case 122: case 123: case 124:
							case 127: case 129: case 153: case 156:
							case 185: case 286: case 299:
								{
									ZRnew_Htype_Hid (&ZIs, &ZIm);
									if ((CURRENT_TERMINAL) == 355) {
										RESTORE_LEXER;
										goto ZL1;
									}
								}
								break;
							default:
								goto ZL1;
							}
						}
						/* END OF INLINE: 574 */
						/* BEGINNING OF ACTION: type_decl_quit */
						{
#line 441 "syntax.act"

    have_type_declaration = (ZItd) ;
#line 1559 "syntax6.c"
						}
						/* END OF ACTION: type_decl_quit */
						ZIt = ZIs;
						ZIn = ZIm;
					}
					break;
				default:
					goto ZL1;
				}
			ZL2:;
			}
			/* END OF INLINE: 573 */
		}
		break;
	case 2: case 7: case 8: case 9:
	case 25: case 83: case 97: case 98:
	case 102: case 104: case 106: case 110:
	case 111: case 114: case 115: case 118:
	case 121: case 122: case 123: case 124:
	case 127: case 129: case 153: case 156:
	case 185: case 286: case 299:
		{
			ZRnew_Htype_Hid (&ZIt, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 564 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1592 "syntax6.c"
			}
			/* END OF ACTION: list_exp_null */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOp = ZIp;
	*ZOt = ZIt;
	*ZOn = ZIn;
}

void
ZRstatement_Hseq_Hopt(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_statement_Hseq_Hopt:;
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZI1481;
		EXP ZIa;
		EXP ZIb;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2088 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 1636 "syntax6.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL3;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1548 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1645 "syntax6.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1280 "syntax.act"

    (ZIt) = NULL_type ;
#line 1653 "syntax6.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZI1481);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 933 "syntax.act"

    (ZIa) = (ZI1481) ;
    in_declaration-- ;
#line 1667 "syntax6.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 1675 "syntax6.c"
		}
		/* END OF ACTION: stmt_label_clear */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1683 "syntax6.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF INLINE: statement-seq-opt */
		ZIc = ZIb;
		goto ZL2_statement_Hseq_Hopt;
		/* END OF INLINE: statement-seq-opt */
	}
	UNREACHED;
ZL3:;
	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZIop;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1492;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 400 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 1721 "syntax6.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1492);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1756 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1492) ) ;
#line 1764 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 1772 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1787 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 83:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZR1477 (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1812 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 23:
		{
			EXP ZI1281;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1502;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 359 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 1851 "syntax6.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR1242 (ZI1281, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1502);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1887 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1502) ) ;
#line 1895 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 1903 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1918 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 24:
		{
			EXP ZI1479;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: complex-stmt */
			{
#line 366 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1479 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 1941 "syntax6.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1479) ) ;
#line 1950 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1958 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 25:
		{
			TYPE ZI1267;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1284;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1504;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 373 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 2004 "syntax6.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1256 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2012 "syntax6.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1224 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2019 "syntax6.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1325 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2028 "syntax6.c"
			}
			/* END OF ACTION: type_complete */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression_Hlist_Hopt (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 684 "syntax.act"

    (ZI1284) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 2054 "syntax6.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1284, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1504);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2089 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1504) ) ;
#line 2097 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2105 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2120 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 130:
		{
			TYPE ZIt;
			EXP ZI1463;
			int ZIn;
			EXP ZI1273;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1495;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1463, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_const_cast */
			{
#line 632 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZIt), (ZI1463), (ZIn) ) ;
#line 2166 "syntax6.c"
			}
			/* END OF ACTION: exp_const_cast */
			ZR1242 (ZI1273, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1495);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2201 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1495) ) ;
#line 2209 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2217 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2232 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 5:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZI1285;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1508;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 237 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2270 "syntax6.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 517 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2281 "syntax6.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 688 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 2289 "syntax6.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1242 (ZI1285, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1508);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2324 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1508) ) ;
#line 2332 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2340 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2355 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 206:
		{
			EXP ZI1456;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1484;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1456);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 692 "syntax.act"

    (ZI1454) = make_cast_exp ( type_void, (ZI1456), 0 ) ;
#line 2397 "syntax6.c"
			}
			/* END OF ACTION: exp_ignore */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1484);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2431 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1484) ) ;
#line 2439 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2447 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2462 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 132:
		{
			TYPE ZIt;
			EXP ZI1466;
			int ZIn;
			EXP ZI1276;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1498;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1466, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dynamic_cast */
			{
#line 658 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZIt), (ZI1466), (ZIn) ) ;
#line 2508 "syntax6.c"
			}
			/* END OF ACTION: exp_dynamic_cast */
			ZR1242 (ZI1276, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1498);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2543 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1498) ) ;
#line 2551 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2559 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2574 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 210:
		{
			EXP ZI1279;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1501;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 662 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 2611 "syntax6.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR1242 (ZI1279, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1501);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2646 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1501) ) ;
#line 2654 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2662 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2677 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 9:
		{
			NAMESPACE ZIns;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 270 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 2697 "syntax6.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1476 (&ZIns, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2711 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 1:
		{
			IDENTIFIER ZI1467;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 221 "syntax.act"

    ZI1467 = crt_token->pp_data.id.use ;
#line 2731 "syntax6.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1472 (&ZI1467, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2745 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 346:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZR1441 (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2770 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 255:
		{
			EXP ZI1455;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1482;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1455);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 708 "syntax.act"

    (ZI1454) = make_lit_exp ( (ZI1455) ) ;
#line 2812 "syntax6.c"
			}
			/* END OF ACTION: exp_lit */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1482);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2846 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1482) ) ;
#line 2854 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2862 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2877 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 61:
		{
			EXP ZI1458;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1486;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1458);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 789 "syntax.act"

    (ZI1454) = make_prefix_exp ( lex_minus_Hminus, (ZI1458) ) ;
#line 2919 "syntax6.c"
			}
			/* END OF ACTION: exp_predec */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1486);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2953 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1486) ) ;
#line 2961 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 2969 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2984 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 3:
		{
			IDENTIFIER ZI1471;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 229 "syntax.act"

    ZI1471 = crt_token->pp_data.id.use ;
#line 3004 "syntax6.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			ZR1472 (&ZI1471, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3018 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 8:
		{
			NAMESPACE ZIns;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 266 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3038 "syntax6.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1475 (&ZIns, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3052 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 65:
		{
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1483;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZR1288 (&ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1483);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3115 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1483) ) ;
#line 3123 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3131 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3146 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 71:
		{
			EXP ZI1457;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1485;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1457);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 793 "syntax.act"

    (ZI1454) = make_prefix_exp ( lex_plus_Hplus, (ZI1457) ) ;
#line 3188 "syntax6.c"
			}
			/* END OF ACTION: exp_preinc */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1485);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3222 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1485) ) ;
#line 3230 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3238 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3253 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 145:
		{
			TYPE ZIt;
			EXP ZI1464;
			int ZIn;
			EXP ZI1274;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1496;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1464, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_reinterpret_cast */
			{
#line 806 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZIt), (ZI1464), (ZIn) ) ;
#line 3299 "syntax6.c"
			}
			/* END OF ACTION: exp_reinterpret_cast */
			ZR1242 (ZI1274, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1496);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3334 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1496) ) ;
#line 3342 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3350 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3365 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 77:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_none */
			{
#line 881 "syntax.act"

    (ZIa) = NULL_exp ;
#line 3385 "syntax6.c"
			}
			/* END OF ACTION: stmt_none */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3393 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 116:
		{
			int ZIop;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1491;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 407 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 3429 "syntax6.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZIop, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1491);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3464 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1491) ) ;
#line 3472 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3480 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3495 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 78:
		{
			EXP ZI1459;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1487;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1459);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 700 "syntax.act"

    (ZI1454) = make_indir_exp ( (ZI1459) ) ;
#line 3537 "syntax6.c"
			}
			/* END OF ACTION: exp_indir */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1487);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3571 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1487) ) ;
#line 3579 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3587 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3602 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 4:
		{
			IDENTIFIER ZI1473;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 233 "syntax.act"

    ZI1473 = crt_token->pp_data.id.use ;
#line 3622 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1474 (&ZI1473, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3636 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 146:
		{
			TYPE ZIt;
			EXP ZI1465;
			int ZIn;
			EXP ZI1275;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1497;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1465, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_static_cast */
			{
#line 831 "syntax.act"

    (ZI1275) = make_static_cast_exp ( (ZIt), (ZI1465), (ZIn) ) ;
#line 3681 "syntax6.c"
			}
			/* END OF ACTION: exp_static_cast */
			ZR1242 (ZI1275, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1497);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3716 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1497) ) ;
#line 3724 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3732 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3747 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 6:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZI1285;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1509;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 243 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3789 "syntax6.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 517 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3800 "syntax6.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 688 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 3808 "syntax6.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1242 (ZI1285, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1509);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3843 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1509) ) ;
#line 3851 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 3859 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3874 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 7:
		{
			IDENTIFIER ZItid;
			IDENTIFIER ZIid;
			TYPE ZI1267;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1283;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1510;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 251 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3921 "syntax6.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 511 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3932 "syntax6.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1289 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 3942 "syntax6.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1256 "syntax.act"
 (ZIbt) = btype_none ; 
#line 3949 "syntax6.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1224 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3956 "syntax6.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1325 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 3965 "syntax6.c"
			}
			/* END OF ACTION: type_complete */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression_Hlist_Hopt (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 684 "syntax.act"

    (ZI1283) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 3991 "syntax6.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1283, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1510);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4026 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1510) ) ;
#line 4034 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4042 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4057 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 148:
		{
			EXP ZI1278;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1500;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 835 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 4094 "syntax6.c"
			}
			/* END OF ACTION: exp_this */
			ZR1242 (ZI1278, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1500);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4129 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1500) ) ;
#line 4137 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4145 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4160 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 2:
		{
			IDENTIFIER ZI1469;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 225 "syntax.act"

    ZI1469 = crt_token->pp_data.id.use ;
#line 4180 "syntax6.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			ZR1470 (&ZI1469, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4194 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 152:
		{
			int ZIop;
			EXP ZI1272;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1494;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 408 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 4231 "syntax6.c"
			}
			/* END OF ACTION: lex_typeid */
			ZRtypeid_Hexpression (ZIop, &ZI1272);
			ZR1242 (ZI1272, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1494);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4267 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1494) ) ;
#line 4275 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4283 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4298 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 330:
		{
			int ZIop;
			EXP ZI1271;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1493;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 409 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 4335 "syntax6.c"
			}
			/* END OF ACTION: lex_vtable */
			ZRtypeid_Hexpression (ZIop, &ZI1271);
			ZR1242 (ZI1271, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1493);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4371 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1493) ) ;
#line 4379 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4387 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4402 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 33:
		{
			EXP ZI1460;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1488;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF INLINE: and */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 33:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: and */
			ZRcast_Hexpression (&ZI1460);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 801 "syntax.act"

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
#line 4456 "syntax6.c"
			}
			/* END OF ACTION: exp_ref */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1488);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4490 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1488) ) ;
#line 4498 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4506 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4521 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 122:
	case 123: case 127: case 156: case 185:
	case 286: case 299:
		{
			BASE_TYPE ZIbt;
			TYPE ZI1267;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1282;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1503;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRbase_Htype_Hspecifier (&ZIbt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_pre */
			{
#line 1284 "syntax.act"

    (ZI1267) = NULL_type ;
    have_type_specifier = 1 ;
#line 4571 "syntax6.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1224 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4578 "syntax6.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1325 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4587 "syntax6.c"
			}
			/* END OF ACTION: type_complete */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression_Hlist_Hopt (&ZIp);
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 684 "syntax.act"

    (ZI1282) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 4613 "syntax6.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1282, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1503);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4648 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1503) ) ;
#line 4656 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4664 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4679 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 64:
		{
			EXP ZIa;
			EXP ZIb;

			ZRcompound_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4703 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 289: case 323:
		{
			EXP ZIa;
			EXP ZIb;

			ZRcontrol_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4727 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 96: case 100: case 223:
		{
			EXP ZIa;
			EXP ZIb;

			ZRfall_Hcheck ();
			ZR1442 (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4752 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 298: case 324:
		{
			EXP ZI1436;
			EXP ZI1478;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRflow_Hexpression (&ZI1436);
			ZR1438 (&ZI1436, &ZI1478);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4788 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1478) ) ;
#line 4796 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4804 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4819 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 101: case 107: case 125:
		{
			EXP ZIa;
			EXP ZIb;

			ZRiteration_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4843 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 95: case 99: case 108: case 113:
		{
			EXP ZIa;
			EXP ZIb;

			ZRjump_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4867 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 17: case 18: case 19: case 20:
	case 21: case 22: case 135: case 150:
		{
			EXP ZI1277;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1499;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRliteral (&ZI1277);
			ZR1242 (ZI1277, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1499);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4932 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1499) ) ;
#line 4940 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 4948 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4963 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 62:
		{
			EXP ZI1461;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1489;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF INLINE: not */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 62:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: not */
			ZRcast_Hexpression (&ZI1461);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 760 "syntax.act"

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
#line 5017 "syntax6.c"
			}
			/* END OF ACTION: exp_not */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1489);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5051 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1489) ) ;
#line 5059 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 5067 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5082 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 141:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZI1285;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1507;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			parse_operator (&ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 517 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5127 "syntax6.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 688 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 5135 "syntax6.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1242 (ZI1285, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1507);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5170 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1507) ) ;
#line 5178 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 5186 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5201 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 26: case 109: case 119:
		{
			EXP ZIa;
			EXP ZIb;

			ZRselection_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5225 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 149:
		{
			EXP ZI1289;
			EXP ZI1480;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRthrow_Hexpression (&ZI1289);
			ZR1291 (&ZI1289, &ZI1480);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5261 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1480) ) ;
#line 5269 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 5277 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5292 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 151:
		{
			EXP ZIa;
			EXP ZIb;

			ZRtry_Hblock (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5316 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 131: case 140:
		{
			int ZI1505;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1506;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2053 "syntax.act"
 (ZI1505) = 0 ; 
#line 5351 "syntax6.c"
			}
			/* END OF ACTION: bool_false */
			ZR1432 (&ZI1505, &ZI1454);
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1506);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5386 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1506) ) ;
#line 5394 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 5402 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5417 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 43: case 59: case 69: case 85:
		{
			int ZIop;
			EXP ZI1462;
			EXP ZI1454;
			EXP ZI1453;
			EXP ZI1452;
			EXP ZI1451;
			EXP ZI1450;
			EXP ZI1449;
			EXP ZI1448;
			EXP ZI1447;
			EXP ZI1446;
			EXP ZI1445;
			EXP ZI1444;
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1490;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 393 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 5453 "syntax6.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZI1462);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 859 "syntax.act"

    (ZI1454) = make_uminus_exp ( (ZIop), (ZI1462) ) ;
#line 5467 "syntax6.c"
			}
			/* END OF ACTION: exp_unary */
			ZR1238 (ZI1454, &ZI1453);
			ZR1234 (ZI1453, &ZI1452);
			ZR1230 (ZI1452, &ZI1451);
			ZR1226 (ZI1451, &ZI1450);
			ZR1222 (ZI1450, &ZI1449);
			ZR1218 (ZI1449, &ZI1448);
			ZR1214 (ZI1448, &ZI1447);
			ZR1210 (ZI1447, &ZI1446);
			ZR1206 (ZI1446, &ZI1445);
			ZR1202 (ZI1445, &ZI1444);
			ZR1198 (ZI1444, &ZI1443);
			ZR1194 (ZI1443, &ZI1265);
			ZR1266 (&ZI1265, &ZI1289);
			ZR1291 (&ZI1289, &ZI1490);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1125 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5501 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 954 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1490) ) ;
#line 5509 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1022 "syntax.act"

    unreached_fall = 1 ;
#line 5517 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 921 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5532 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	default:
		{
			ZIe = ZIc;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
