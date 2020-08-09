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


#line 98 "syntax5.c"

void
ZRmember_Hdeclarator_Hlist(DECL_SPEC ZIds, TYPE ZIp, BASE_TYPE ZIq, ACCESS_LIST ZIr, int ZIf)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_member_Hdeclarator_Hlist:;
	{
		IDENTIFIER ZId;

		ZRmember_Hdeclarator (ZIds, ZIp, ZIq, ZIr, ZIf, &ZId);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1697 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 120 "syntax5.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF INLINE: 1091 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					int ZIn;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: bool_false */
					{
#line 2035 "syntax.act"
 (ZIn) = 0 ; 
#line 135 "syntax5.c"
					}
					/* END OF ACTION: bool_false */
					/* BEGINNING OF ACTION: declarator_start */
					{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 143 "syntax5.c"
					}
					/* END OF ACTION: declarator_start */
					/* BEGINNING OF INLINE: member-declarator-list */
					ZIf = ZIn;
					goto ZL2_member_Hdeclarator_Hlist;
					/* END OF INLINE: member-declarator-list */
				}
				UNREACHED;
			default:
				break;
			}
		}
		/* END OF INLINE: 1091 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRtype_Hid(TYPE *ZOt, int *ZOn)
{
	TYPE ZIt;
	int ZIn;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		int ZIn1;
		BASE_TYPE ZIbt;
		TYPE ZIp;
		CV_SPEC ZIcv;
		TYPE ZIq;

		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2000 "syntax.act"

    (ZIn1) = no_type_defns ;
#line 185 "syntax5.c"
		}
		/* END OF ACTION: no_type_defns */
		ZRtype_Hspecifier_Hseq (&ZIbt, &ZIp, &ZIcv);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_complete */
		{
#line 1307 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 199 "syntax5.c"
		}
		/* END OF ACTION: type_complete */
		ZRabstract_Hdeclarator_Hopt (ZIq, &ZIt);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2008 "syntax.act"

    (ZIn) = no_type_defns - (ZIn1) ;
#line 212 "syntax5.c"
		}
		/* END OF ACTION: diff_type_defns */
		/* BEGINNING OF ACTION: type_check */
		{
#line 1316 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 220 "syntax5.c"
		}
		/* END OF ACTION: type_check */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOn = ZIn;
}

void
ZRflow_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 298:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_set */
			{
#line 805 "syntax.act"

    (ZIe) = make_set_exp ( (ZIa) ) ;
#line 261 "syntax5.c"
			}
			/* END OF ACTION: exp_set */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 324:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 845 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 295 "syntax5.c"
			}
			/* END OF ACTION: exp_unused */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
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
ZRdeclaration_Hbasic(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZI1251;
		TYPE ZI1252;
		CV_SPEC ZI1253;
		DECL_SPEC ZI1254;
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;
		DECL_SPEC ZIds2;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2063 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 343 "syntax5.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (ZIt, &ZI1251, &ZI1252, &ZI1253, &ZI1254);
		ZR920 (&ZIt, &ZI1251, &ZI1252, &ZI1253, &ZI1254, &ZIbt, &ZIt1, &ZIcv1, &ZIds1);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 362 "syntax5.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1255 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 10: case 11: case 33:
	case 65: case 78: case 83: case 141:
		{
			BASE_TYPE ZIbt;
			TYPE ZIt1;
			CV_SPEC ZIcv1;
			DECL_SPEC ZIds1;
			DECL_SPEC ZIds2;
			TYPE ZIt2;
			DECL_SPEC ZIds3;
			TYPE ZIt3;
			ACCESS_LIST ZIr;
			TYPE ZIs;
			IDENTIFIER ZIid;
			int ZIc;
			IDENTIFIER ZId;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 398 "syntax5.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 406 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 413 "syntax5.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 420 "syntax5.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 431 "syntax5.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 442 "syntax5.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 450 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 458 "syntax5.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 466 "syntax5.c"
			}
			/* END OF ACTION: declarator_start */
			ZRdeclarator (ZIt3, &ZIs, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_id */
			{
#line 1594 "syntax.act"

    if ( type_tag ( (ZIs) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIs) ) ;
	(ZId) = make_func_decl ( (ZIds3), (ZIs), (ZIid), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZId) = make_object_decl ( (ZIds3), (ZIs), (ZIid), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIbt) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 496 "syntax5.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 504 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 514 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZR1078 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
}

void
ZRdeclaration_Hcond_Hbody(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;

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
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 561 "syntax5.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 569 "syntax5.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
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
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR956(EXP *ZOe)
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
	case 145: case 146: case 148: case 150:
	case 152: case 156: case 170: case 185:
	case 206: case 210: case 255: case 286:
	case 299: case 331:
		{
			ZRconstant_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 633 "syntax5.c"
			}
			/* END OF ACTION: exp_none */
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
	*ZOe = ZIe;
}

void
ZR1211(EXP ZI1209, EXP *ZO1210)
{
	EXP ZI1210;

ZL2_1211:;
	switch (CURRENT_TERMINAL) {
	case 33:
		{
			EXP ZIb;
			EXP ZIe;

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
			ZRmaxmin_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_and */
			{
#line 574 "syntax.act"

    (ZIe) = make_and_exp ( (ZI1209), (ZIb) ) ;
#line 684 "syntax5.c"
			}
			/* END OF ACTION: exp_and */
			/* BEGINNING OF INLINE: 1211 */
			ZI1209 = ZIe;
			goto ZL2_1211;
			/* END OF INLINE: 1211 */
		}
		UNREACHED;
	default:
		{
			ZI1210 = ZI1209;
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
	*ZO1210 = ZI1210;
}

void
ZRoperator_Hname(int *ZOop)
{
	int ZIop;

	switch (CURRENT_TERMINAL) {
	case 131:
		{
			ADVANCE_LEXER;
			ZR1324 (&ZIop);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 140:
		{
			ADVANCE_LEXER;
			ZR1323 (&ZIop);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 65:
		{
			ADVANCE_LEXER;
			ZRclose_Hround_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: lex_func_op */
			{
#line 384 "syntax.act"
 (ZIop) = lex_func_Hop ; 
#line 747 "syntax5.c"
			}
			/* END OF ACTION: lex_func_op */
		}
		break;
	case 72:
		{
			ADVANCE_LEXER;
			ZRcolon_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: lex_cond_op */
			{
#line 379 "syntax.act"
 (ZIop) = lex_cond_Hop ; 
#line 764 "syntax5.c"
			}
			/* END OF ACTION: lex_cond_op */
			/* BEGINNING OF ACTION: error_overload */
			{
#line 1975 "syntax.act"

    /* Illegal overloaded operator */
    report ( crt_loc, ERR_over_oper_bad ( (ZIop) ) ) ;
#line 773 "syntax5.c"
			}
			/* END OF ACTION: error_overload */
		}
		break;
	case 66:
		{
			/* BEGINNING OF INLINE: open-square */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 66:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: open-square */
			ZRclose_Hsquare_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: lex_array_op */
			{
#line 383 "syntax.act"
 (ZIop) = lex_array_Hop ; 
#line 802 "syntax5.c"
			}
			/* END OF ACTION: lex_array_op */
		}
		break;
	case 33: case 34: case 35: case 36:
	case 41: case 42: case 43: case 44:
	case 45: case 46: case 48: case 49:
	case 50: case 53: case 54: case 55:
	case 56: case 57: case 58: case 59:
	case 60: case 61: case 62: case 63:
	case 67: case 68: case 69: case 70:
	case 71: case 73: case 74: case 75:
	case 76: case 78: case 79: case 80:
	case 81: case 82: case 83: case 84:
	case 85: case 86: case 87: case 116:
	case 152: case 170: case 331:
		{
			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 824 "syntax5.c"
			}
			/* END OF ACTION: lex_crt */
			ZR1322 (&ZIop);
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
	*ZOop = ZIop;
}

void
ZRcolon_Hx(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 41:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		int ZIt;

		/* BEGINNING OF ACTION: lex_colon */
		{
#line 378 "syntax.act"
 (ZIt) = lex_colon ; 
#line 871 "syntax5.c"
		}
		/* END OF ACTION: lex_colon */
		/* BEGINNING OF ACTION: expected */
		{
#line 1981 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 881 "syntax5.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRexpression_Hlist(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;
		SID_LIST_EXP ZIq;

		ZRassignment_Hexpression (&ZIe);
		ZR501 (&ZIq);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 550 "syntax.act"

    CONS_exp ( (ZIe), (ZIq), (ZIp) ) ;
#line 910 "syntax5.c"
		}
		/* END OF ACTION: list_exp_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOp = ZIp;
}

void
ZRassignment_Hexpression(EXP *ZOe)
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
	case 145: case 146: case 148: case 150:
	case 152: case 156: case 170: case 185:
	case 206: case 210: case 255: case 286:
	case 299: case 331:
		{
			EXP ZI1266;

			ZRlogical_Hor_Hexpression (&ZI1266);
			ZR1267 (&ZI1266, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 149:
		{
			ZRthrow_Hexpression (&ZIe);
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
	*ZOe = ZIe;
}

void
ZR1342(TYPE *ZIt, BASE_TYPE *ZIbt, TYPE *ZIt1, CV_SPEC *ZIcv1, DECL_SPEC *ZIds2)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1657 "syntax.act"

    IGNORE empty_decl ( (*ZIds2), (*ZIt), (*ZIbt), (*ZIt1), (*ZIcv1), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 990 "syntax5.c"
			}
			/* END OF ACTION: declare_member_empty */
			/* BEGINNING OF ACTION: access_check_class */
			{
#line 1453 "syntax.act"

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
#line 1001 "syntax5.c"
			}
			/* END OF ACTION: access_check_class */
			ADVANCE_LEXER;
		}
		break;
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 10: case 11: case 33:
	case 41: case 65: case 78: case 83:
	case 141:
		{
			TYPE ZIt2;
			DECL_SPEC ZIds3;
			TYPE ZIt3;
			ACCESS_LIST ZIr;
			int ZIf;
			IDENTIFIER ZId;

			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (*ZIds2), (*ZIbt), (*ZIt1), (*ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (*ZIbt), (*ZIt1), (*ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1028 "syntax5.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (*ZIt) ) ? (ZIt2) : inject_pre_type ( (*ZIt), (ZIt2), 1 ) ) ;
#line 1036 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 1044 "syntax5.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIf) = 1 ; 
#line 1051 "syntax5.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1059 "syntax5.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator (ZIds3, ZIt3, *ZIbt, ZIr, ZIf, &ZId);
			ZR1095 (ZIbt, &ZIds3, &ZIt3, &ZIr, &ZId);
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
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR1215(EXP ZI1213, EXP *ZO1214)
{
	EXP ZI1214;

ZL2_1215:;
	switch (CURRENT_TERMINAL) {
	case 86: case 87:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 1098 "syntax5.c"
			}
			/* END OF ACTION: lex_crt */
			/* BEGINNING OF INLINE: maxmin-operator */
			{
				switch (CURRENT_TERMINAL) {
				case 86:
					{
						ADVANCE_LEXER;
					}
					break;
				case 87:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: maxmin-operator */
			ZRequality_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_maxmin */
			{
#line 710 "syntax.act"

    (ZIe) = make_mult_exp ( (ZIop), (ZI1213), (ZIb) ) ;
#line 1129 "syntax5.c"
			}
			/* END OF ACTION: exp_maxmin */
			/* BEGINNING OF INLINE: 1215 */
			ZI1213 = ZIe;
			goto ZL2_1215;
			/* END OF INLINE: 1215 */
		}
		UNREACHED;
	default:
		{
			ZI1214 = ZI1213;
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
	*ZO1214 = ZI1214;
}

void
ZRexpression_Hlist_Hopt(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

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
			ZRexpression_Hlist (&ZIp);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 546 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1190 "syntax5.c"
			}
			/* END OF ACTION: list_exp_null */
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
	*ZOp = ZIp;
}

void
ZR1343(void)
{
	switch (CURRENT_TERMINAL) {
	case 26:
		{
			ZRmember_Hcond ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 154:
		{
			ZRusing_Hdeclaration ();
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
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRlogical_Hand_Hexpression(EXP *ZO1198)
{
	EXP ZI1198;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRinclusive_Hor_Hexpression (&ZIe);
		ZR1199 (ZIe, &ZI1198);
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
	*ZO1198 = ZI1198;
}

void
ZRjump_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 95:
		{
			int ZIr;

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
#line 1289 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_break */
			{
#line 867 "syntax.act"

    (ZIe) = make_break_stmt () ;
#line 1297 "syntax5.c"
			}
			/* END OF ACTION: stmt_break */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1305 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 99:
		{
			int ZIr;

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
#line 1333 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_continue */
			{
#line 911 "syntax.act"

    (ZIe) = make_continue_stmt () ;
#line 1341 "syntax5.c"
			}
			/* END OF ACTION: stmt_continue */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1349 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 108:
		{
			int ZIr;

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
#line 1377 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			ZRjump_Hlabel (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1390 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 113:
		{
			int ZIr;
			EXP ZIa;

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
#line 1419 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF INLINE: 756 */
			{
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
				case 286: case 298: case 299: case 324:
				case 331: case 347:
					{
						ZRexpression (&ZIa);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: exp_none */
						{
#line 565 "syntax.act"

    (ZIa) = NULL_exp ;
#line 1456 "syntax5.c"
						}
						/* END OF ACTION: exp_none */
					}
					break;
				}
			}
			/* END OF INLINE: 756 */
			/* BEGINNING OF ACTION: stmt_return */
			{
#line 1011 "syntax.act"

    (ZIe) = make_return_stmt ( (ZIa), lex_return ) ;
#line 1469 "syntax5.c"
			}
			/* END OF ACTION: stmt_return */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1477 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
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
	*ZOe = ZIe;
}

void
ZR1471(IDENTIFIER *ZI1470, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (*ZI1470) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1539 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 1549 "syntax5.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1556 "syntax5.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1563 "syntax5.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 1572 "syntax5.c"
			}
			/* END OF ACTION: type_complete */
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
#line 1592 "syntax5.c"
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
			ZR1292 (&ZI1290, &ZIa);
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
#line 1627 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1635 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1643 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 41:
		{
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: qual_none */
			{
#line 535 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 1667 "syntax5.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 1008 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 1675 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 991 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZI1470), lex_identifier ) ;
#line 1683 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 995 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 1697 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_end */
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
ZRcast_Hoperand(TYPE *ZOt, EXP *ZOe, int *ZOn)
{
	TYPE ZIt;
	EXP ZIe;
	int ZIn;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 53:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRtype_Hid (&ZIt, &ZIn);
		switch (CURRENT_TERMINAL) {
		case 49:
			break;
		case 356:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 65:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRexpression (&ZIe);
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
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOe = ZIe;
	*ZOn = ZIn;
}

void
ZRtarget_Hcondition_Hhead(EXP *ZO1188, EXP *ZO1189, int *ZO1190)
{
	EXP ZI1188;
	EXP ZI1189;
	int ZI1190;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIc;
		EXP ZIp;
		int ZIr;
		EXP ZIa;
		EXP ZIe;

		switch (CURRENT_TERMINAL) {
		case 26:
			/* BEGINNING OF EXTRACT: hash-if */
			{
#line 323 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1797 "syntax5.c"
			}
			/* END OF EXTRACT: hash-if */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: cond_hash_if */
		{
#line 1903 "syntax.act"

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
    (ZIp) = c ;
#line 1812 "syntax5.c"
		}
		/* END OF ACTION: cond_hash_if */
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
#line 1828 "syntax5.c"
		}
		/* END OF ACTION: reach_check */
		ZRcompound_Hstatement (&ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1840 "syntax5.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_if */
		{
#line 1051 "syntax.act"

    (ZIe) = begin_hash_if_stmt ( (ZIc), (ZIa) ) ;
#line 1848 "syntax5.c"
		}
		/* END OF ACTION: stmt_hash_if */
		ZR1191 (ZIe, ZIp, ZIr, &ZI1188, &ZI1189, &ZI1190);
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
	*ZO1188 = ZI1188;
	*ZO1189 = ZI1189;
	*ZO1190 = ZI1190;
}

void
ZRcv_Hqualifier_Hseq(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		CV_SPEC ZIa;

		ZRcv_Hqualifier (&ZIa);
		/* BEGINNING OF INLINE: 789 */
		{
			switch (CURRENT_TERMINAL) {
			case 98: case 124:
				{
					CV_SPEC ZIb;

					ZRcv_Hqualifier_Hseq (&ZIb);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: cv_join */
					{
#line 1211 "syntax.act"

    CV_SPEC c = ( (ZIa) & (ZIb) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIa) | (ZIb) ) ;
#line 1898 "syntax5.c"
					}
					/* END OF ACTION: cv_join */
				}
				break;
			default:
				{
					ZIcv = ZIa;
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 789 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

void
ZRfunction_Hbody(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIb;
		EXP ZId;
		EXP ZIa;

		ZRctor_Hinitialiser_Hopt (ZIc, &ZIb, &ZId);
		/* BEGINNING OF INLINE: open-brace */
		{
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
		/* BEGINNING OF ACTION: stmt_compound_block */
		{
#line 895 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIb) ), 2 ) ;
#line 1959 "syntax5.c"
		}
		/* END OF ACTION: stmt_compound_block */
		ZRstatement_Hseq_Hopt (ZIb, &ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: ctor_postlude */
		{
#line 1180 "syntax.act"

    (ZIe) = ctor_postlude ( (ZIa), (ZId) ) ;
#line 1972 "syntax5.c"
		}
		/* END OF ACTION: ctor_postlude */
		/* BEGINNING OF INLINE: close-brace */
		{
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
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1473(IDENTIFIER *ZI1472, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 33: case 34: case 35: case 36:
	case 42: case 44: case 45: case 46:
	case 48: case 49: case 50: case 53:
	case 54: case 55: case 56: case 57:
	case 58: case 59: case 60: case 61:
	case 63: case 65: case 66: case 67:
	case 68: case 69: case 70: case 71:
	case 72: case 73: case 74: case 75:
	case 76: case 77: case 78: case 79:
	case 80: case 81: case 82: case 84:
	case 86: case 87:
		{
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (*ZI1472) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2041 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 2049 "syntax5.c"
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
			ZR1292 (&ZI1290, &ZIa);
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
#line 2084 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2092 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2100 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 41:
		{
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: qual_none */
			{
#line 535 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2124 "syntax5.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 1008 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 2132 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 991 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZI1472), lex_identifier ) ;
#line 2140 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 995 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 2154 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_end */
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
ZR1219(EXP ZI1217, EXP *ZO1218)
{
	EXP ZI1218;

ZL2_1219:;
	switch (CURRENT_TERMINAL) {
	case 48: case 63:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 2189 "syntax5.c"
			}
			/* END OF ACTION: lex_crt */
			ZRequality_Hoperator ();
			ZRrelational_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_equality */
			{
#line 649 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_equality_exp ( (ZIop), (ZI1217), (ZIb) ) ;
#line 2204 "syntax5.c"
			}
			/* END OF ACTION: exp_equality */
			/* BEGINNING OF INLINE: 1219 */
			ZI1217 = ZIe;
			goto ZL2_1219;
			/* END OF INLINE: 1219 */
		}
		UNREACHED;
	default:
		{
			ZI1218 = ZI1217;
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
	*ZO1218 = ZI1218;
}

void
ZR1347(NAMESPACE *ZIns, IDENTIFIER *ZOid)
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
#line 2244 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 479 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 2254 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2263 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZI1344;
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
    ZI1344 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 2287 "syntax5.c"
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

    ZI1344 = crt_token->pp_data.id.use ;
#line 2300 "syntax5.c"
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
#line 2317 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZItid) = check_id ( (*ZIns), (ZI1344), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2326 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1718 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 2334 "syntax5.c"
			}
			/* END OF ACTION: declarator_type */
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
#line 2357 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 2366 "syntax5.c"
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
ZRcv_Hqualifier_Hseq_Hopt(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 98: case 124:
		{
			ZRcv_Hqualifier_Hseq (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2405 "syntax5.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZOcv = ZIcv;
}

void
ZR1602(EXP *ZI1601, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 348:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 550 "syntax.act"

    CONS_exp ( (*ZI1601), (ZIq), (ZIp) ) ;
#line 2445 "syntax5.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 605 "syntax.act"

    (ZIa) = make_comma_exp ( (ZIp) ) ;
#line 2453 "syntax5.c"
			}
			/* END OF ACTION: exp_comma */
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
#line 2469 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2477 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2485 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 77:
		{
			int ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 348:
				break;
			default:
				goto ZL1;
			}
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
#line 2522 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (*ZI1601) ) ;
#line 2530 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2538 "syntax5.c"
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
ZR1475(IDENTIFIER *ZI1474, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	default:
		{
			IDENTIFIER ZIid;
			EXP ZIa;

			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (*ZI1474) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2574 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 2582 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2590 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 41:
		{
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: qual_none */
			{
#line 535 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2607 "syntax5.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 1008 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 2615 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 991 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZI1474), lex_identifier ) ;
#line 2623 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 995 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 2637 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_end */
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
	*ZOe = ZIe;
}

void
ZR1348(NAMESPACE *ZIns, IDENTIFIER *ZOid)
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
#line 2668 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 2678 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2687 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZI1345;
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
    ZI1345 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 2711 "syntax5.c"
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

    ZI1345 = crt_token->pp_data.id.use ;
#line 2724 "syntax5.c"
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
#line 2741 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZItid) = check_id ( (*ZIns), (ZI1345), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2750 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1718 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 2758 "syntax5.c"
			}
			/* END OF ACTION: declarator_type */
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
#line 2781 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 2790 "syntax5.c"
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
ZRcondition(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZId;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2070 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 2828 "syntax5.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: cond_start */
		{
#line 1076 "syntax.act"

    begin_cond () ;
#line 2838 "syntax5.c"
		}
		/* END OF ACTION: cond_start */
		ZRcondition_Hdeclarator (&ZId);
		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		case 356:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRinitialiser_Hexpression (&ZIa);
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
#line 2864 "syntax5.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1746 "syntax.act"

    int def = init_object ( (ZId), (ZIa) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 2873 "syntax5.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 2883 "syntax5.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1697 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 2891 "syntax5.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: cond_end */
		{
#line 1079 "syntax.act"

    (ZIe) = end_cond () ;
    in_declaration-- ;
#line 2900 "syntax5.c"
		}
		/* END OF ACTION: cond_end */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
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
	case 286: case 298: case 299: case 324:
	case 331: case 347:
		{
			ZRexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
ZR1476(NAMESPACE *ZIns, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2960 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 479 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 2970 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2979 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 2987 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2995 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 141: case 147:
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
			EXP ZIa;
			int ZIr;

			ZR1269 (ZIns, &ZI1455);
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
			ZR1292 (&ZI1290, &ZIa);
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
#line 3052 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3060 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3068 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
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
ZR1349(IDENTIFIER *ZOid)
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
#line 3109 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3120 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 3129 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZI1346;
			NAMESPACE ZIns;
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
    ZI1346 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3154 "syntax5.c"
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

    ZI1346 = crt_token->pp_data.id.use ;
#line 3167 "syntax5.c"
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
#line 3185 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZItid) = check_id ( (ZIns), (ZI1346), 0 ) ;
    last_namespace = (ZIns) ;
#line 3194 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1718 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 3202 "syntax5.c"
			}
			/* END OF ACTION: declarator_type */
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
#line 3221 "syntax5.c"
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
#line 3236 "syntax5.c"
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
ZR1095(BASE_TYPE *ZIbt, DECL_SPEC *ZIds3, TYPE *ZIt3, ACCESS_LIST *ZIr, IDENTIFIER *ZId)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		/* BEGINNING OF ACTION: is_function */
		{
#line 2058 "syntax.act"

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
#line 3267 "syntax5.c"
		}
		/* END OF ACTION: is_function */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: access_free */
		{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3277 "syntax5.c"
		}
		/* END OF ACTION: access_free */
		/* BEGINNING OF ACTION: function_skip */
		{
#line 1151 "syntax.act"

    skip_function ( (*ZId) ) ;
#line 3285 "syntax5.c"
		}
		/* END OF ACTION: function_skip */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3293 "syntax5.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3301 "syntax5.c"
		}
		/* END OF ACTION: rescan_token */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 42:
		{
			int ZIn;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3319 "syntax5.c"
			}
			/* END OF ACTION: declarator_end */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIn) = 0 ; 
#line 3326 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3334 "syntax5.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator_Hlist (*ZIds3, *ZIt3, *ZIbt, *ZIr, ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_free */
			{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3347 "syntax5.c"
			}
			/* END OF ACTION: access_free */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access_free */
			{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3367 "syntax5.c"
			}
			/* END OF ACTION: access_free */
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3375 "syntax5.c"
			}
			/* END OF ACTION: declarator_end */
		}
		break;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
}

void
ZR1477(NAMESPACE *ZIns, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3407 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 3417 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 3426 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 3434 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3442 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 141: case 147:
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
			EXP ZIa;
			int ZIr;

			ZR1270 (ZIns, &ZI1455);
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
			ZR1292 (&ZI1290, &ZIa);
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
#line 3499 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3507 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3515 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
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
ZR1223(EXP ZI1221, EXP *ZO1222)
{
	EXP ZI1222;

ZL2_1223:;
	switch (CURRENT_TERMINAL) {
	case 49: case 50: case 53: case 54:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 3557 "syntax5.c"
			}
			/* END OF ACTION: lex_crt */
			/* BEGINNING OF INLINE: relational-operator */
			{
				switch (CURRENT_TERMINAL) {
				case 49:
					{
						ADVANCE_LEXER;
					}
					break;
				case 50:
					{
						ADVANCE_LEXER;
					}
					break;
				case 53:
					{
						ADVANCE_LEXER;
					}
					break;
				case 54:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: relational-operator */
			ZRshift_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_relation */
			{
#line 793 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_relation_exp ( (ZIop), (ZI1221), (ZIb) ) ;
#line 3599 "syntax5.c"
			}
			/* END OF ACTION: exp_relation */
			/* BEGINNING OF INLINE: 1223 */
			ZI1221 = ZIe;
			goto ZL2_1223;
			/* END OF INLINE: 1223 */
		}
		UNREACHED;
	default:
		{
			ZI1222 = ZI1221;
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
	*ZO1222 = ZI1222;
}

void
ZRbase_Hclause_Hopt(int *ZOt)
{
	int ZIt;

	switch (CURRENT_TERMINAL) {
	case 41:
		{
			ADVANCE_LEXER;
			ZR1329 (&ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIt) = 1 ; 
#line 3646 "syntax5.c"
			}
			/* END OF ACTION: bool_true */
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
	*ZOt = ZIt;
}

void
ZRdirect_Hnew_Hdeclarator(TYPE *ZO1151)
{
	TYPE ZI1151;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;
		EXP ZIe;
		TYPE ZIt;

		/* BEGINNING OF INLINE: open-square */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 66:
					break;
				default:
					goto ZL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: open-square */
		ZRexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_eval */
		{
#line 653 "syntax.act"

    (ZIe) = convert_reference ( (ZIa), REF_NORMAL ) ;
    (ZIe) = convert_lvalue ( (ZIe) ) ;
#line 3699 "syntax5.c"
		}
		/* END OF ACTION: exp_eval */
		/* BEGINNING OF ACTION: type_new_array */
		{
#line 1363 "syntax.act"

    /* First array bound in a new-declarator */
    NAT n = make_new_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 3709 "syntax5.c"
		}
		/* END OF ACTION: type_new_array */
		/* BEGINNING OF INLINE: close-square */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 40:
					break;
				default:
					goto ZL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: close-square */
		ZR1152 (ZIt, &ZI1151);
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
	*ZO1151 = ZI1151;
}

void
ZR1478(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;
			NAMESPACE ZIns;
			IDENTIFIER ZIid;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3757 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3768 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 3777 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 3785 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3793 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 131: case 140:
	case 141: case 147:
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
			EXP ZIa;
			int ZIr;

			ZR1287 (&ZI1455);
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
			ZR1292 (&ZI1290, &ZIa);
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
#line 3851 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3859 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3867 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
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
ZRany_Hnested_Hname(NAMESPACE *ZOns)
{
	NAMESPACE ZIns;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3908 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
		}
		break;
	case 8: case 9:
		{
			ZRnonempty_Hnested_Hname (&ZIns);
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
	*ZOns = ZIns;
}

void
ZRfall_Hcheck(void)
{
	switch (CURRENT_TERMINAL) {
	case 223:
		{
			ADVANCE_LEXER;
			ZR1606 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 356:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRcv_Hqualifier(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 98:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cv_const */
			{
#line 1207 "syntax.act"
 (ZIcv) = cv_const ; 
#line 3973 "syntax5.c"
			}
			/* END OF ACTION: cv_const */
		}
		break;
	case 124:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cv_volatile */
			{
#line 1208 "syntax.act"
 (ZIcv) = cv_volatile ; 
#line 3985 "syntax5.c"
			}
			/* END OF ACTION: cv_volatile */
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
	*ZOcv = ZIcv;
}

void
ZRmember_Hcond(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIp;

		ZRmember_Hcond_Hhead (&ZIp);
		/* BEGINNING OF INLINE: 839 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: cond_hash_else */
					{
#line 1914 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 4024 "syntax5.c"
					}
					/* END OF ACTION: cond_hash_else */
					/* BEGINNING OF ACTION: decl_hash_else */
					{
#line 1895 "syntax.act"

    target_decl ( lex_else, NULL_exp ) ;
#line 4032 "syntax5.c"
					}
					/* END OF ACTION: decl_hash_else */
					ZRmember_Hcond_Hbody ();
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 839 */
		/* BEGINNING OF ACTION: cond_hash_endif */
		{
#line 1917 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 4055 "syntax5.c"
		}
		/* END OF ACTION: cond_hash_endif */
		switch (CURRENT_TERMINAL) {
		case 29:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: decl_hash_endif */
		{
#line 1899 "syntax.act"

    target_decl ( lex_endif, NULL_exp ) ;
#line 4070 "syntax5.c"
		}
		/* END OF ACTION: decl_hash_endif */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR1606(void)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 1000 "syntax.act"

    unreached_fall = 0 ;
#line 4092 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_set */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 1000 "syntax.act"

    unreached_fall = 0 ;
#line 4104 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_set */
		}
		break;
	case 356:
		return;
	}
}

void
ZRunary_Hoperator(void)
{
	switch (CURRENT_TERMINAL) {
	case 85:
		{
			ADVANCE_LEXER;
		}
		break;
	case 59:
		{
			ADVANCE_LEXER;
		}
		break;
	case 69:
		{
			ADVANCE_LEXER;
		}
		break;
	case 43:
		{
			/* BEGINNING OF INLINE: compl */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 43:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: compl */
		}
		break;
	case 356:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRmember_Hdeclarator(DECL_SPEC ZIds, TYPE ZIp, BASE_TYPE ZIq, ACCESS_LIST ZIr, int ZIf, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			ADVANCE_LEXER;
			ZR1349 (&ZI1356);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 4190 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 4197 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4205 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4218 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 4226 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4234 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4267 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4275 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4285 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4299 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4309 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 5:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 219 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4332 "syntax5.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZI1356) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4343 "syntax5.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 4351 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 4358 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4366 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4379 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 4387 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4395 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4428 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4436 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4446 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4460 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4470 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 9:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4493 "syntax5.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1348 (&ZIns, &ZI1356);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 4507 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 4514 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4522 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4535 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 4543 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4551 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4584 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4592 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4602 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4616 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4626 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 1:
		{
			IDENTIFIER ZI1363;
			IDENTIFIER ZI1364;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 203 "syntax.act"

    ZI1363 = crt_token->pp_data.id.use ;
#line 4641 "syntax5.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZI1364) = (ZI1363) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4652 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1368 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1364, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 3:
		{
			IDENTIFIER ZI1366;
			IDENTIFIER ZI1367;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 211 "syntax.act"

    ZI1366 = crt_token->pp_data.id.use ;
#line 4672 "syntax5.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZI1367) = (ZI1366) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4683 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1368 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1367, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4711 "syntax5.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1347 (&ZIns, &ZI1356);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 4725 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 4732 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4740 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4753 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 4761 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4769 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4802 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4810 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4820 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4834 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4844 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 65:
		{
			TYPE ZI1353;
			IDENTIFIER ZI1354;
			int ZI1355;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRdeclarator_Haux (&ZI1353, &ZI1354, &ZI1355);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZI1355) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4872 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZI1353) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 4882 "syntax5.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1180 (ZI1353, ZI1354, ZI1355, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4902 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 4910 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4918 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4951 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4959 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4969 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4983 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4993 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 4:
		{
			IDENTIFIER ZI1360;
			IDENTIFIER ZI1361;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZI1360 = crt_token->pp_data.id.use ;
#line 5008 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZI1361) = (ZI1360) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5019 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1368 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1361, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 6:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 225 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5051 "syntax5.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZI1356) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5062 "syntax5.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 5070 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 5077 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5085 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5098 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 5106 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5114 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5147 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5155 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5165 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5179 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5189 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 7:
		{
			IDENTIFIER ZI1359;
			IDENTIFIER ZItid;
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1359 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5217 "syntax5.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZItid) = (ZI1359) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5228 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1718 "syntax.act"

    (ZI1356) = constr_name ( last_namespace, (ZItid) ) ;
#line 5236 "syntax5.c"
			}
			/* END OF ACTION: declarator_type */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 5244 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 5251 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5259 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5272 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 5280 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5288 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5321 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5329 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5339 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5353 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5363 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 2:
		{
			IDENTIFIER ZI1369;
			IDENTIFIER ZI1370;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 207 "syntax.act"

    ZI1369 = crt_token->pp_data.id.use ;
#line 5378 "syntax5.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZI1370) = (ZI1369) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5389 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1371 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1370, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 141:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZI1356;
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			parse_operator (&ZIuid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZI1356) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5424 "syntax5.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 5432 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 5439 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5447 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, ZI1356, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5460 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 5468 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5476 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5509 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5517 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5527 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5541 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5551 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 10: case 11: case 33: case 78:
		{
			TYPE ZI1351;
			TYPE ZI1352;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZI1350;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			ZRptr_Hoperator (&ZI1351);
			ZRdeclarator_Haux (&ZI1352, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1383 "syntax.act"

    (ZI1350) = ( IS_NULL_type ( (ZI1352) ) ? (ZI1351) : inject_pre_type ( (ZI1352), (ZI1351), 0 ) ) ;
#line 5578 "syntax5.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5586 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (ZIp) : inject_pre_type ( (ZI1350), (ZIp), 1 ) ) ;
#line 5594 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5602 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (ZIds) ;
    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	if ( ds & dspec_friend ) {
	    (ZId) = make_friend_decl ( ds, (ZIt), (ZIid), def, 1 ) ;
	    (ZIfr) = 1 ;
	} else {
	    (ZId) = make_func_mem_decl ( ds, (ZIt), (ZIid), def ) ;
	    (ZIfr) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5635 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5643 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5653 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1755 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5667 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5677 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 41:
		{
			IDENTIFIER ZIid;
			QUALIFIER ZIi;
			int ZIb;
			EXP ZIc;
			TYPE ZIt;

			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5698 "syntax5.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5706 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZIid), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5714 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 5723 "syntax5.c"
			}
			/* END OF ACTION: qual_get */
			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 5738 "syntax5.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_bitfield_mem */
			{
#line 1373 "syntax.act"

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZIid) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZIt) = make_bitfield_type ( (ZIp), (ZIq), (ZIc), z ) ;
#line 5749 "syntax5.c"
			}
			/* END OF ACTION: type_bitfield_mem */
			/* BEGINNING OF ACTION: declare_bitfield */
			{
#line 1664 "syntax.act"

    IDENTIFIER id = make_member_decl ( (ZIds), (ZIt), (ZIid), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZId) = id ;
#line 5763 "syntax5.c"
			}
			/* END OF ACTION: declare_bitfield */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5771 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5781 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
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
	*ZOd = ZId;
}

/* END OF FILE */
