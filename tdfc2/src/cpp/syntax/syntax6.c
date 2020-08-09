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
#line 176 "syntax.act"


/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/option.h>
#include <construct/access.h>
#include <construct/allocate.h>
#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <parse/constant.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <output/dump.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <parse/preproc.h>
#include <parse/hash.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/inttype.h>
#include <construct/label.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <construct/member.h>
#include <construct/namespace.h>
#include <parse/parse.h>
#include <parse/pragma.h>
#include <parse/predict.h>
#include <parse/preproc.h>
#include <construct/redeclare.h>
#include <construct/rewrite.h>
#include <construct/statement.h>
#include <parse/symbols.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/typeid.h>
#include <construct/variable.h>


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;
typedef LIST ( TYPE ) SID_LIST_TYPE ;


/*
    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include <syntax/syntax.h>


#line 98 "syntax6.c"

void
ZR1227(EXP ZI1225, EXP *ZO1226)
{
	EXP ZI1226;

ZL2_1227:;
	switch (CURRENT_TERMINAL) {
	case 57:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRadditive_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lshift */
			{
#line 706 "syntax.act"

    (ZIe) = make_shift_exp ( lex_lshift, (ZI1225), (ZIb) ) ;
#line 123 "syntax6.c"
			}
			/* END OF ACTION: exp_lshift */
			/* BEGINNING OF INLINE: 1227 */
			ZI1225 = ZIe;
			goto ZL2_1227;
			/* END OF INLINE: 1227 */
		}
		UNREACHED;
	case 75:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRadditive_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_rshift */
			{
#line 801 "syntax.act"

    (ZIe) = make_shift_exp ( lex_rshift, (ZI1225), (ZIb) ) ;
#line 148 "syntax6.c"
			}
			/* END OF ACTION: exp_rshift */
			/* BEGINNING OF INLINE: 1227 */
			ZI1225 = ZIe;
			goto ZL2_1227;
			/* END OF INLINE: 1227 */
		}
		UNREACHED;
	default:
		{
			ZI1226 = ZI1225;
		}
		break;
	case 356:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZO1226 = ZI1226;
}

void
ZRany_Hnested_Hname_Hopt(NAMESPACE *ZOns)
{
	NAMESPACE ZIns;

	switch (CURRENT_TERMINAL) {
	case 8: case 9: case 83:
		{
			ZRany_Hnested_Hname (&ZIns);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: namespace_none */
			{
#line 466 "syntax.act"

    (ZIns) = NULL_nspace ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 197 "syntax6.c"
			}
			/* END OF ACTION: namespace_none */
		}
		break;
	case 356:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
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
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 228 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 479 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 238 "syntax6.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 247 "syntax6.c"
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
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 270 "syntax6.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 207 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 283 "syntax6.c"
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
#line 479 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 300 "syntax6.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 309 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 479 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 332 "syntax6.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 341 "syntax6.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
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
	case 286: case 299: case 331:
		{
			ZRinitialiser_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 393 "syntax6.c"
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
			ZR1004 (&ZId, &ZIp);
			/* BEGINNING OF INLINE: close-brace */
			{
				if ((CURRENT_TERMINAL) == 356) {
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
#line 570 "syntax.act"

    /* The expression type is a dummy */
    MAKE_exp_aggregate ( type_void, (ZIp), NULL_list ( OFFSET ), (ZIe) ) ;
#line 439 "syntax6.c"
			}
			/* END OF ACTION: exp_aggregate */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRtemplate_Hmember_Hdecl(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 356) {
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
		case 356:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: template_params */
		{
#line 1823 "syntax.act"

    (ZIp) = template_params ( (ZIx) ) ;
    RESCAN_LEXER ;
#line 485 "syntax6.c"
		}
		/* END OF ACTION: template_params */
		/* BEGINNING OF ACTION: template_type */
		{
#line 1815 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 493 "syntax6.c"
		}
		/* END OF ACTION: template_type */
		ZRmember_Hdeclaration (ZIt1, ZIds);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: template_end */
		{
#line 1819 "syntax.act"

    end_template ( (ZIp) ) ;
#line 506 "syntax6.c"
		}
		/* END OF ACTION: template_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 514 "syntax6.c"
		}
		/* END OF ACTION: rescan_token */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR1610(NAMESPACE *ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 539 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 549 "syntax6.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 558 "syntax6.c"
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
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 581 "syntax6.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 207 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 594 "syntax6.c"
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
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 611 "syntax6.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 620 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 643 "syntax6.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 652 "syntax6.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRadditive_Hexpression(EXP *ZO1230)
{
	EXP ZI1230;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRmultiplicative_Hexpression (&ZIe);
		ZR1231 (ZIe, &ZI1230);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZO1230 = ZI1230;
}

void
ZRdirect_Hdeclarator(TYPE *ZO1177, IDENTIFIER *ZO1178, int *ZO1179)
{
	TYPE ZI1177;
	IDENTIFIER ZI1178;
	int ZI1179;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIt;
			IDENTIFIER ZIid;
			int ZIc;

			ADVANCE_LEXER;
			ZRdeclarator_Haux (&ZIt, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 721 "syntax6.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 731 "syntax6.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1180 (ZIt, ZIid, ZIc, &ZI1177, &ZI1178, &ZI1179);
			if ((CURRENT_TERMINAL) == 356) {
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 766 "syntax6.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIc) = 0 ; 
#line 773 "syntax6.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZIid), crt_id_qualifier, qual_namespace, 1 ) ;
#line 781 "syntax6.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZIt, ZIid, ZIc, &ZI1177, &ZI1178, &ZI1179);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZO1177 = ZI1177;
	*ZO1178 = ZI1178;
	*ZO1179 = ZI1179;
}

void
ZR1611(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 822 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 833 "syntax6.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 842 "syntax6.c"
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
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 866 "syntax6.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 207 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 879 "syntax6.c"
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
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 897 "syntax6.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 906 "syntax6.c"
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
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 925 "syntax6.c"
			}
			/* END OF ACTION: namespace_global */
			ZRtemplate_Hopt (ZIns, &ZIq);
			ZRnested_Hid (ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (ZIns) ;
#line 940 "syntax6.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOid = ZIid;
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
#line 1122 "syntax.act"
 (ZIx) = crt_condition ; 
#line 981 "syntax6.c"
			}
			/* END OF ACTION: condition_get */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 997 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			ZRopen_Hround_Hx ();
			ZRcondition (&ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_if_begin */
			{
#line 970 "syntax.act"

    (ZIa) = begin_if_stmt ( (ZIc) ) ;
#line 1011 "syntax6.c"
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
#line 891 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 1026 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			/* BEGINNING OF ACTION: cond_inject */
			{
#line 1088 "syntax.act"

    (ZIbc) = inject_cond ( (ZIbs), (ZIc) ) ;
#line 1034 "syntax6.c"
			}
			/* END OF ACTION: cond_inject */
			ZRscoped_Hstatement (ZIbc, &ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1046 "syntax6.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_if_cont */
			{
#line 974 "syntax.act"

    (ZId) = cont_if_stmt ( (ZIa), (ZIb) ) ;
#line 1054 "syntax6.c"
			}
			/* END OF ACTION: stmt_if_cont */
			/* BEGINNING OF INLINE: 720 */
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
#line 983 "syntax.act"

    check_empty_stmt ( lex_else ) ;
#line 1075 "syntax6.c"
					}
					/* END OF ACTION: stmt_else */
					/* BEGINNING OF ACTION: stmt_compound_begin */
					{
#line 891 "syntax.act"

    (ZIfs) = begin_compound_stmt ( 1 ) ;
#line 1083 "syntax6.c"
					}
					/* END OF ACTION: stmt_compound_begin */
					/* BEGINNING OF ACTION: cond_inject */
					{
#line 1088 "syntax.act"

    (ZIfc) = inject_cond ( (ZIfs), (ZIc) ) ;
#line 1091 "syntax6.c"
					}
					/* END OF ACTION: cond_inject */
					ZRscoped_Hstatement (ZIfc, &ZIf);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL3;
					}
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: stmt_no_else */
					{
#line 987 "syntax.act"

    report ( crt_loc, ERR_stmt_if_no_else () ) ;
    (ZIf) = NULL_exp ;
#line 1109 "syntax6.c"
					}
					/* END OF ACTION: stmt_no_else */
				}
			ZL2:;
			}
			/* END OF INLINE: 720 */
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1120 "syntax6.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_if_end */
			{
#line 978 "syntax.act"

    (ZIe) = end_if_stmt ( (ZId), (ZIf) ) ;
#line 1128 "syntax6.c"
			}
			/* END OF ACTION: stmt_if_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 1123 "syntax.act"
 crt_condition = (ZIx) ; 
#line 1135 "syntax6.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1143 "syntax6.c"
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
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1172 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_switch_begin */
			{
#line 1015 "syntax.act"

    (ZIa) = begin_switch_stmt ( (ZIc) ) ;
#line 1192 "syntax6.c"
			}
			/* END OF ACTION: stmt_switch_begin */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 724 */
			{
				switch (CURRENT_TERMINAL) {
				case 217:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: bool_true */
						{
#line 2036 "syntax.act"
 (ZIex) = 1 ; 
#line 1212 "syntax6.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2035 "syntax.act"
 (ZIex) = 0 ; 
#line 1223 "syntax6.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 724 */
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 891 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 1236 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			/* BEGINNING OF ACTION: cond_inject */
			{
#line 1088 "syntax.act"

    (ZIbc) = inject_cond ( (ZIbs), (ZIc) ) ;
#line 1244 "syntax6.c"
			}
			/* END OF ACTION: cond_inject */
			ZRscoped_Hstatement (ZIbc, &ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1256 "syntax6.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_switch_end */
			{
#line 1019 "syntax.act"

    (ZIe) = end_switch_stmt ( (ZIa), (ZIb), (ZIex) ) ;
#line 1264 "syntax6.c"
			}
			/* END OF ACTION: stmt_switch_end */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1272 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 26:
		{
			ZRtarget_Hcondition (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1289 "syntax6.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1231(EXP ZI1229, EXP *ZO1230)
{
	EXP ZI1230;

ZL2_1231:;
	switch (CURRENT_TERMINAL) {
	case 59:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRmultiplicative_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_minus */
			{
#line 714 "syntax.act"

    (ZIe) = make_minus_exp ( (ZI1229), (ZIb) ) ;
#line 1330 "syntax6.c"
			}
			/* END OF ACTION: exp_minus */
			/* BEGINNING OF INLINE: 1231 */
			ZI1229 = ZIe;
			goto ZL2_1231;
			/* END OF INLINE: 1231 */
		}
		UNREACHED;
	case 69:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRmultiplicative_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_plus */
			{
#line 759 "syntax.act"

    (ZIe) = make_plus_exp ( (ZI1229), (ZIb) ) ;
#line 1355 "syntax6.c"
			}
			/* END OF ACTION: exp_plus */
			/* BEGINNING OF INLINE: 1231 */
			ZI1229 = ZIe;
			goto ZL2_1231;
			/* END OF INLINE: 1231 */
		}
		UNREACHED;
	default:
		{
			ZI1230 = ZI1229;
		}
		break;
	case 356:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZO1230 = ZI1230;
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
	case 286: case 299: case 331:
		{
			EXP ZI1290;

			ZRassignment_Hexpression (&ZI1290);
			ZR1292 (&ZI1290, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 550 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1429 "syntax6.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 605 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1437 "syntax6.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	case 347:
		{
			EXP ZIa;
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRinset_Hflow_Hexpression (&ZIa);
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 550 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1459 "syntax6.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 605 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1467 "syntax6.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
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
			/* BEGINNING OF INLINE: 574 */
			{
				{
					/* BEGINNING OF ACTION: is_type_id_false */
					{
#line 2100 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 1505 "syntax6.c"
					}
					/* END OF ACTION: is_type_id_false */
					if (!ZI0)
						goto ZL3;
					ZRtype_Hid (&ZIt, &ZIn);
					switch (CURRENT_TERMINAL) {
					case 39:
						break;
					case 356:
						RESTORE_LEXER;
						goto ZL1;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: list_exp_null */
					{
#line 546 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1526 "syntax6.c"
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
				case 286: case 299: case 331:
					{
						int ZItd;
						TYPE ZIs;
						int ZIm;

						ZRexpression_Hlist (&ZIp);
						switch (CURRENT_TERMINAL) {
						case 39:
							break;
						case 356:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_decl_begin */
						{
#line 404 "syntax.act"

    (ZItd) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
#line 1571 "syntax6.c"
						}
						/* END OF ACTION: type_decl_begin */
						/* BEGINNING OF INLINE: 575 */
						{
							switch (CURRENT_TERMINAL) {
							case 65:
								{
									ADVANCE_LEXER;
									ZRtype_Hid (&ZIs, &ZIm);
									switch (CURRENT_TERMINAL) {
									case 39:
										break;
									case 356:
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
									if ((CURRENT_TERMINAL) == 356) {
										RESTORE_LEXER;
										goto ZL1;
									}
								}
								break;
							default:
								goto ZL1;
							}
						}
						/* END OF INLINE: 575 */
						/* BEGINNING OF ACTION: type_decl_quit */
						{
#line 423 "syntax.act"

    have_type_declaration = (ZItd) ;
#line 1618 "syntax6.c"
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
			/* END OF INLINE: 574 */
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 546 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1651 "syntax6.c"
			}
			/* END OF ACTION: list_exp_null */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
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

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_statement_Hseq_Hopt:;
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZI1482;
		EXP ZIa;
		EXP ZIb;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2070 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 1695 "syntax6.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL3;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1704 "syntax6.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 1712 "syntax6.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZI1482);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 915 "syntax.act"

    (ZIa) = (ZI1482) ;
    in_declaration-- ;
#line 1726 "syntax6.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1734 "syntax6.c"
		}
		/* END OF ACTION: stmt_label_clear */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1742 "syntax6.c"
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1493;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 382 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 1780 "syntax6.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1493);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1815 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1493) ) ;
#line 1823 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1831 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1846 "syntax6.c"
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
			ZR1478 (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1871 "syntax6.c"
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
			EXP ZI1282;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1503;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 341 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1282 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 1910 "syntax6.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR1243 (ZI1282, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1503);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1946 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1503) ) ;
#line 1954 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1962 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 1977 "syntax6.c"
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
			EXP ZI1480;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: complex-stmt */
			{
#line 348 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1480 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2000 "syntax6.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1480) ) ;
#line 2009 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2017 "syntax6.c"
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
			TYPE ZI1268;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1285;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1505;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 355 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1268 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 2063 "syntax6.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2071 "syntax6.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2078 "syntax6.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2087 "syntax6.c"
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
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 666 "syntax.act"

    (ZI1285) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 2113 "syntax6.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZI1285, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1505);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2148 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1505) ) ;
#line 2156 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2164 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2179 "syntax6.c"
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
			EXP ZI1464;
			int ZIn;
			EXP ZI1274;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1496;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1464, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_const_cast */
			{
#line 614 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_const_cast_exp ( (ZIt), (ZI1464), (ZIn) ) ;
#line 2225 "syntax6.c"
			}
			/* END OF ACTION: exp_const_cast */
			ZR1243 (ZI1274, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1496);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2260 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1496) ) ;
#line 2268 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2276 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2291 "syntax6.c"
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
			EXP ZI1286;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1509;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 219 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2329 "syntax6.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2340 "syntax6.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 2348 "syntax6.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1243 (ZI1286, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1509);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2383 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1509) ) ;
#line 2391 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2399 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2414 "syntax6.c"
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
			EXP ZI1457;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1485;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1457);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 674 "syntax.act"

    (ZI1455) = make_cast_exp ( type_void, (ZI1457), 0 ) ;
#line 2456 "syntax6.c"
			}
			/* END OF ACTION: exp_ignore */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1485);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2490 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1485) ) ;
#line 2498 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2506 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2521 "syntax6.c"
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
			EXP ZI1467;
			int ZIn;
			EXP ZI1277;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1499;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1467, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dynamic_cast */
			{
#line 640 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1277) = make_dynamic_cast_exp ( (ZIt), (ZI1467), (ZIn) ) ;
#line 2567 "syntax6.c"
			}
			/* END OF ACTION: exp_dynamic_cast */
			ZR1243 (ZI1277, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1499);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2602 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1499) ) ;
#line 2610 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2618 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2633 "syntax6.c"
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
			EXP ZI1280;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1502;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 644 "syntax.act"

    (ZI1280) = make_ellipsis_exp () ;
#line 2670 "syntax6.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR1243 (ZI1280, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1502);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2705 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1502) ) ;
#line 2713 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2721 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2736 "syntax6.c"
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
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 2756 "syntax6.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1477 (&ZIns, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

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
	case 1:
		{
			IDENTIFIER ZI1468;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 203 "syntax.act"

    ZI1468 = crt_token->pp_data.id.use ;
#line 2790 "syntax6.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1473 (&ZI1468, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2804 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 347:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZR1442 (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2829 "syntax6.c"
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
			EXP ZI1456;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1483;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1456);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 690 "syntax.act"

    (ZI1455) = make_lit_exp ( (ZI1456) ) ;
#line 2871 "syntax6.c"
			}
			/* END OF ACTION: exp_lit */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1483);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2905 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1483) ) ;
#line 2913 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2921 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 2936 "syntax6.c"
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
			EXP ZI1459;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1487;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1459);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 771 "syntax.act"

    (ZI1455) = make_prefix_exp ( lex_minus_Hminus, (ZI1459) ) ;
#line 2978 "syntax6.c"
			}
			/* END OF ACTION: exp_predec */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1487);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3012 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1487) ) ;
#line 3020 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3028 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3043 "syntax6.c"
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
			IDENTIFIER ZI1472;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 211 "syntax.act"

    ZI1472 = crt_token->pp_data.id.use ;
#line 3063 "syntax6.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			ZR1473 (&ZI1472, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3077 "syntax6.c"
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
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3097 "syntax6.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1476 (&ZIns, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3111 "syntax6.c"
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1484;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZR1289 (&ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1484);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3174 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1484) ) ;
#line 3182 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3190 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3205 "syntax6.c"
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
			EXP ZI1458;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1486;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1458);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 775 "syntax.act"

    (ZI1455) = make_prefix_exp ( lex_plus_Hplus, (ZI1458) ) ;
#line 3247 "syntax6.c"
			}
			/* END OF ACTION: exp_preinc */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1486);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3281 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1486) ) ;
#line 3289 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3297 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3312 "syntax6.c"
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
			EXP ZI1465;
			int ZIn;
			EXP ZI1275;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1497;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1465, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_reinterpret_cast */
			{
#line 788 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1275) = make_reinterp_cast_exp ( (ZIt), (ZI1465), (ZIn) ) ;
#line 3358 "syntax6.c"
			}
			/* END OF ACTION: exp_reinterpret_cast */
			ZR1243 (ZI1275, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1497);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3393 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1497) ) ;
#line 3401 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3409 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3424 "syntax6.c"
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
#line 863 "syntax.act"

    (ZIa) = NULL_exp ;
#line 3444 "syntax6.c"
			}
			/* END OF ACTION: stmt_none */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3452 "syntax6.c"
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1492;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 389 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 3488 "syntax6.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZIop, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1492);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3523 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1492) ) ;
#line 3531 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3539 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3554 "syntax6.c"
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
			EXP ZI1460;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1488;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1460);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 682 "syntax.act"

    (ZI1455) = make_indir_exp ( (ZI1460) ) ;
#line 3596 "syntax6.c"
			}
			/* END OF ACTION: exp_indir */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1488);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3630 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1488) ) ;
#line 3638 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3646 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3661 "syntax6.c"
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
			IDENTIFIER ZI1474;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZI1474 = crt_token->pp_data.id.use ;
#line 3681 "syntax6.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1475 (&ZI1474, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3695 "syntax6.c"
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
			EXP ZI1466;
			int ZIn;
			EXP ZI1276;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1498;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1466, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_static_cast */
			{
#line 813 "syntax.act"

    (ZI1276) = make_static_cast_exp ( (ZIt), (ZI1466), (ZIn) ) ;
#line 3740 "syntax6.c"
			}
			/* END OF ACTION: exp_static_cast */
			ZR1243 (ZI1276, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1498);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3775 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1498) ) ;
#line 3783 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3791 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3806 "syntax6.c"
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
			EXP ZI1286;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1510;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 225 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3848 "syntax6.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3859 "syntax6.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 3867 "syntax6.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1243 (ZI1286, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1510);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3902 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1510) ) ;
#line 3910 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3918 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3933 "syntax6.c"
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
			TYPE ZI1268;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1284;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1511;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3980 "syntax6.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3991 "syntax6.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 4001 "syntax6.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4008 "syntax6.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4015 "syntax6.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4024 "syntax6.c"
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
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 666 "syntax.act"

    (ZI1284) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 4050 "syntax6.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZI1284, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1511);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4085 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1511) ) ;
#line 4093 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4101 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4116 "syntax6.c"
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
			EXP ZI1279;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1501;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 817 "syntax.act"

    (ZI1279) = make_this_exp () ;
#line 4153 "syntax6.c"
			}
			/* END OF ACTION: exp_this */
			ZR1243 (ZI1279, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1501);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4188 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1501) ) ;
#line 4196 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4204 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4219 "syntax6.c"
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
			IDENTIFIER ZI1470;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 207 "syntax.act"

    ZI1470 = crt_token->pp_data.id.use ;
#line 4239 "syntax6.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			ZR1471 (&ZI1470, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4253 "syntax6.c"
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
			EXP ZI1273;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1495;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 390 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 4290 "syntax6.c"
			}
			/* END OF ACTION: lex_typeid */
			ZRtypeid_Hexpression (ZIop, &ZI1273);
			ZR1243 (ZI1273, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1495);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4326 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1495) ) ;
#line 4334 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4342 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4357 "syntax6.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	case 331:
		{
			int ZIop;
			EXP ZI1272;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1494;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 391 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 4394 "syntax6.c"
			}
			/* END OF ACTION: lex_vtable */
			ZRtypeid_Hexpression (ZIop, &ZI1272);
			ZR1243 (ZI1272, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1494);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4430 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1494) ) ;
#line 4438 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4446 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4461 "syntax6.c"
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
			EXP ZI1461;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1489;
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
			ZRcast_Hexpression (&ZI1461);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 783 "syntax.act"

    (ZI1455) = make_ref_exp ( (ZI1461), 0 ) ;
#line 4515 "syntax6.c"
			}
			/* END OF ACTION: exp_ref */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1489);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4549 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1489) ) ;
#line 4557 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4565 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4580 "syntax6.c"
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
			TYPE ZI1268;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1283;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1504;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRbase_Htype_Hspecifier (&ZIbt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_pre */
			{
#line 1266 "syntax.act"

    (ZI1268) = NULL_type ;
    have_type_specifier = 1 ;
#line 4630 "syntax6.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4637 "syntax6.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4646 "syntax6.c"
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
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_func_cast */
			{
#line 666 "syntax.act"

    (ZI1283) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 4672 "syntax6.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZI1283, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1504);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4707 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1504) ) ;
#line 4715 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4723 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4738 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4762 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4786 "syntax6.c"
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
			ZR1443 (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4811 "syntax6.c"
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
			EXP ZI1437;
			EXP ZI1479;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRflow_Hexpression (&ZI1437);
			ZR1439 (&ZI1437, &ZI1479);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4847 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1479) ) ;
#line 4855 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4863 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4878 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4902 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 4926 "syntax6.c"
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
			EXP ZI1278;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1500;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRliteral (&ZI1278);
			ZR1243 (ZI1278, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1500);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4991 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1500) ) ;
#line 4999 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5007 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5022 "syntax6.c"
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
			EXP ZI1462;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1490;
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
			ZRcast_Hexpression (&ZI1462);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 742 "syntax.act"

    (ZI1455) = make_not_exp ( (ZI1462) ) ;
#line 5076 "syntax6.c"
			}
			/* END OF ACTION: exp_not */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1490);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5110 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1490) ) ;
#line 5118 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5126 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5141 "syntax6.c"
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
			EXP ZI1286;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1508;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			parse_operator (&ZIuid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5186 "syntax6.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 5194 "syntax6.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1243 (ZI1286, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1508);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5229 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1508) ) ;
#line 5237 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5245 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5260 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5284 "syntax6.c"
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
			EXP ZI1290;
			EXP ZI1481;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			ZRthrow_Hexpression (&ZI1290);
			ZR1292 (&ZI1290, &ZI1481);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5320 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1481) ) ;
#line 5328 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5336 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5351 "syntax6.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5375 "syntax6.c"
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
			int ZI1506;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1507;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1506) = 0 ; 
#line 5410 "syntax6.c"
			}
			/* END OF ACTION: bool_false */
			ZR1433 (&ZI1506, &ZI1455);
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1507);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5445 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1507) ) ;
#line 5453 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5461 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5476 "syntax6.c"
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
			EXP ZI1463;
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
			EXP ZI1266;
			EXP ZI1290;
			EXP ZI1491;
			int ZIr;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 5512 "syntax6.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZI1463);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 841 "syntax.act"

    (ZI1455) = make_uminus_exp ( (ZIop), (ZI1463) ) ;
#line 5526 "syntax6.c"
			}
			/* END OF ACTION: exp_unary */
			ZR1239 (ZI1455, &ZI1454);
			ZR1235 (ZI1454, &ZI1453);
			ZR1231 (ZI1453, &ZI1452);
			ZR1227 (ZI1452, &ZI1451);
			ZR1223 (ZI1451, &ZI1450);
			ZR1219 (ZI1450, &ZI1449);
			ZR1215 (ZI1449, &ZI1448);
			ZR1211 (ZI1448, &ZI1447);
			ZR1207 (ZI1447, &ZI1446);
			ZR1203 (ZI1446, &ZI1445);
			ZR1199 (ZI1445, &ZI1444);
			ZR1195 (ZI1444, &ZI1266);
			ZR1267 (&ZI1266, &ZI1290);
			ZR1292 (&ZI1290, &ZI1491);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1107 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 5560 "syntax6.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIa) = make_exp_stmt ( (ZI1491) ) ;
#line 5568 "syntax6.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5576 "syntax6.c"
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
#line 903 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 5591 "syntax6.c"
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
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
