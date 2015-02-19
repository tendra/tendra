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
#line 177 "syntax.act"


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


#line 97 "syntax5.c"

void
ZRmember_Hdeclarator_Hlist(DECL_SPEC ZIds, TYPE ZIp, BASE_TYPE ZIq, ACCESS_LIST ZIr, int ZIf)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_member_Hdeclarator_Hlist:;
	{
		IDENTIFIER ZId;

		ZRmember_Hdeclarator (ZIds, ZIp, ZIq, ZIr, ZIf, &ZId);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1700 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 119 "syntax5.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF INLINE: 1090 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					int ZIn;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: bool_false */
					{
#line 2038 "syntax.act"
 (ZIn) = 0 ; 
#line 134 "syntax5.c"
					}
					/* END OF ACTION: bool_false */
					/* BEGINNING OF ACTION: declarator_start */
					{
#line 1693 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 142 "syntax5.c"
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
		/* END OF INLINE: 1090 */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRtype_Hid(TYPE *ZOt, int *ZOn)
{
	TYPE ZIt;
	int ZIn;

	if ((CURRENT_TERMINAL) == 355) {
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
#line 2003 "syntax.act"

    (ZIn1) = no_type_defns ;
#line 184 "syntax5.c"
		}
		/* END OF ACTION: no_type_defns */
		ZRtype_Hspecifier_Hseq (&ZIbt, &ZIp, &ZIcv);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_complete */
		{
#line 1310 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 198 "syntax5.c"
		}
		/* END OF ACTION: type_complete */
		ZRabstract_Hdeclarator_Hopt (ZIq, &ZIt);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2011 "syntax.act"

    (ZIn) = no_type_defns - (ZIn1) ;
#line 211 "syntax5.c"
		}
		/* END OF ACTION: diff_type_defns */
		/* BEGINNING OF ACTION: type_check */
		{
#line 1319 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 219 "syntax5.c"
		}
		/* END OF ACTION: type_check */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_set */
			{
#line 808 "syntax.act"

    (ZIe) = make_set_exp ( (ZIa) ) ;
#line 260 "syntax5.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 848 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 294 "syntax5.c"
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
ZR955(EXP *ZOe)
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
	case 299: case 330:
		{
			ZRconstant_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_none */
			{
#line 568 "syntax.act"

    (ZIe) = NULL_exp ;
#line 355 "syntax5.c"
			}
			/* END OF ACTION: exp_none */
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
	*ZOe = ZIe;
}

void
ZRdeclaration_Hbasic(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZI1250;
		TYPE ZI1251;
		CV_SPEC ZI1252;
		DECL_SPEC ZI1253;
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;
		DECL_SPEC ZIds2;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2066 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 394 "syntax5.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (ZIt, &ZI1250, &ZI1251, &ZI1252, &ZI1253);
		ZR919 (&ZIt, &ZI1250, &ZI1251, &ZI1252, &ZI1253, &ZIbt, &ZIt1, &ZIcv1, &ZIds1);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1549 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 413 "syntax5.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1254 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 355) {
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
#line 1241 "syntax.act"
 (ZIbt) = btype_none ; 
#line 449 "syntax5.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZIt1) = NULL_type ;
#line 457 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1209 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 464 "syntax5.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1533 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 471 "syntax5.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1549 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 482 "syntax5.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1560 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 493 "syntax5.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 501 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1469 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 509 "syntax5.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1693 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 517 "syntax5.c"
			}
			/* END OF ACTION: declarator_start */
			ZRdeclarator (ZIt3, &ZIs, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_id */
			{
#line 1597 "syntax.act"

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
#line 547 "syntax5.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 555 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 565 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZR1077 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
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
	SAVE_LEXER (355);
	return;
ZL0:;
}

void
ZRdeclaration_Hcond_Hbody(void)
{
	if ((CURRENT_TERMINAL) == 355) {
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
#line 1533 "syntax.act"
 (ZIds) = dspec_none ; 
#line 612 "syntax5.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1265 "syntax.act"

    (ZIt) = NULL_type ;
#line 620 "syntax5.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
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
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1210(EXP ZI1208, EXP *ZO1209)
{
	EXP ZI1209;

ZL2_1210:;
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_and */
			{
#line 577 "syntax.act"

    (ZIe) = make_and_exp ( (ZI1208), (ZIb) ) ;
#line 683 "syntax5.c"
			}
			/* END OF ACTION: exp_and */
			/* BEGINNING OF INLINE: 1210 */
			ZI1208 = ZIe;
			goto ZL2_1210;
			/* END OF INLINE: 1210 */
		}
		UNREACHED;
	default:
		{
			ZI1209 = ZI1208;
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
	*ZO1209 = ZI1209;
}

void
ZRoperator_Hname(int *ZOop)
{
	int ZIop;

	switch (CURRENT_TERMINAL) {
	case 131:
		{
			ADVANCE_LEXER;
			ZR1323 (&ZIop);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 140:
		{
			ADVANCE_LEXER;
			ZR1322 (&ZIop);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 65:
		{
			ADVANCE_LEXER;
			ZRclose_Hround_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: lex_func_op */
			{
#line 387 "syntax.act"
 (ZIop) = lex_func_Hop ; 
#line 746 "syntax5.c"
			}
			/* END OF ACTION: lex_func_op */
		}
		break;
	case 72:
		{
			ADVANCE_LEXER;
			ZRcolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: lex_cond_op */
			{
#line 382 "syntax.act"
 (ZIop) = lex_cond_Hop ; 
#line 763 "syntax5.c"
			}
			/* END OF ACTION: lex_cond_op */
			/* BEGINNING OF ACTION: error_overload */
			{
#line 1978 "syntax.act"

    /* Illegal overloaded operator */
    report ( crt_loc, ERR_over_oper_bad ( (ZIop) ) ) ;
#line 772 "syntax5.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: lex_array_op */
			{
#line 386 "syntax.act"
 (ZIop) = lex_array_Hop ; 
#line 801 "syntax5.c"
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
	case 152: case 170: case 330:
		{
			/* BEGINNING OF ACTION: lex_crt */
			{
#line 378 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 823 "syntax5.c"
			}
			/* END OF ACTION: lex_crt */
			ZR1321 (&ZIop);
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
	*ZOop = ZIop;
}

void
ZRcolon_Hx(void)
{
	if ((CURRENT_TERMINAL) == 355) {
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
#line 381 "syntax.act"
 (ZIt) = lex_colon ; 
#line 870 "syntax5.c"
		}
		/* END OF ACTION: lex_colon */
		/* BEGINNING OF ACTION: expected */
		{
#line 1984 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 880 "syntax5.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRexpression_Hlist(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;
		SID_LIST_EXP ZIq;

		ZRassignment_Hexpression (&ZIe);
		ZR500 (&ZIq);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 553 "syntax.act"

    CONS_exp ( (ZIe), (ZIq), (ZIp) ) ;
#line 909 "syntax5.c"
		}
		/* END OF ACTION: list_exp_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOp = ZIp;
}

void
ZR1341(TYPE *ZIt, BASE_TYPE *ZIbt, TYPE *ZIt1, CV_SPEC *ZIcv1, DECL_SPEC *ZIds2)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1660 "syntax.act"

    IGNORE empty_decl ( (*ZIds2), (*ZIt), (*ZIbt), (*ZIt1), (*ZIcv1), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 935 "syntax5.c"
			}
			/* END OF ACTION: declare_member_empty */
			/* BEGINNING OF ACTION: access_check_class */
			{
#line 1456 "syntax.act"

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
#line 946 "syntax5.c"
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
#line 1560 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (*ZIds2), (*ZIbt), (*ZIt1), (*ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (*ZIbt), (*ZIt1), (*ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 973 "syntax5.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (*ZIt) ) ? (ZIt2) : inject_pre_type ( (*ZIt), (ZIt2), 1 ) ) ;
#line 981 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1469 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 989 "syntax5.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2039 "syntax.act"
 (ZIf) = 1 ; 
#line 996 "syntax5.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1693 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1004 "syntax5.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator (ZIds3, ZIt3, *ZIbt, ZIr, ZIf, &ZId);
			ZR1094 (ZIbt, &ZIds3, &ZIt3, &ZIr, &ZId);
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
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1214(EXP ZI1212, EXP *ZO1213)
{
	EXP ZI1213;

ZL2_1214:;
	switch (CURRENT_TERMINAL) {
	case 86: case 87:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 378 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 1043 "syntax5.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_maxmin */
			{
#line 713 "syntax.act"

    (ZIe) = make_mult_exp ( (ZIop), (ZI1212), (ZIb) ) ;
#line 1074 "syntax5.c"
			}
			/* END OF ACTION: exp_maxmin */
			/* BEGINNING OF INLINE: 1214 */
			ZI1212 = ZIe;
			goto ZL2_1214;
			/* END OF INLINE: 1214 */
		}
		UNREACHED;
	default:
		{
			ZI1213 = ZI1212;
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
	*ZO1213 = ZI1213;
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
	case 299: case 330:
		{
			EXP ZI1265;

			ZRlogical_Hor_Hexpression (&ZI1265);
			ZR1266 (&ZI1265, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 149:
		{
			ZRthrow_Hexpression (&ZIe);
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
	*ZOe = ZIe;
}

void
ZR1342(void)
{
	switch (CURRENT_TERMINAL) {
	case 26:
		{
			ZRmember_Hcond ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 154:
		{
			ZRusing_Hdeclaration ();
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
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
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
	case 286: case 299: case 330:
		{
			ZRexpression_Hlist (&ZIp);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 549 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1222 "syntax5.c"
			}
			/* END OF ACTION: list_exp_null */
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
	*ZOp = ZIp;
}

void
ZR1470(IDENTIFIER *ZI1469, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZIid) = (*ZI1469) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1277 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1274 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 1287 "syntax5.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1241 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1294 "syntax5.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1209 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1301 "syntax5.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1310 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 1310 "syntax5.c"
			}
			/* END OF ACTION: type_complete */
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
#line 669 "syntax.act"

    (ZI1283) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 1330 "syntax5.c"
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
			ZR1291 (&ZI1289, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1365 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1373 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 1381 "syntax5.c"
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
#line 538 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 1405 "syntax5.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 1011 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 1413 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 994 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZI1469), lex_identifier ) ;
#line 1421 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 998 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 1435 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_end */
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
ZRlogical_Hand_Hexpression(EXP *ZO1197)
{
	EXP ZI1197;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRinclusive_Hor_Hexpression (&ZIe);
		ZR1198 (ZIe, &ZI1197);
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
	*ZO1197 = ZI1197;
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
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1503 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_break */
			{
#line 870 "syntax.act"

    (ZIe) = make_break_stmt () ;
#line 1511 "syntax5.c"
			}
			/* END OF ACTION: stmt_break */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 1519 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
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
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1547 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_continue */
			{
#line 914 "syntax.act"

    (ZIe) = make_continue_stmt () ;
#line 1555 "syntax5.c"
			}
			/* END OF ACTION: stmt_continue */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 1563 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
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
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1591 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			ZRjump_Hlabel (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 1604 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
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
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1633 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF INLINE: 755 */
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
				case 330: case 346:
					{
						ZRexpression (&ZIa);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: exp_none */
						{
#line 568 "syntax.act"

    (ZIa) = NULL_exp ;
#line 1670 "syntax5.c"
						}
						/* END OF ACTION: exp_none */
					}
					break;
				}
			}
			/* END OF INLINE: 755 */
			/* BEGINNING OF ACTION: stmt_return */
			{
#line 1014 "syntax.act"

    (ZIe) = make_return_stmt ( (ZIa), lex_return ) ;
#line 1683 "syntax5.c"
			}
			/* END OF ACTION: stmt_return */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 1691 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
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
	*ZOe = ZIe;
}

void
ZRcast_Hoperand(TYPE *ZOt, EXP *ZOe, int *ZOn)
{
	TYPE ZIt;
	EXP ZIe;
	int ZIn;

	if ((CURRENT_TERMINAL) == 355) {
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
		case 355:
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
		case 355:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOe = ZIe;
	*ZOn = ZIn;
}

void
ZRtarget_Hcondition_Hhead(EXP *ZO1187, EXP *ZO1188, int *ZO1189)
{
	EXP ZI1187;
	EXP ZI1188;
	int ZI1189;

	if ((CURRENT_TERMINAL) == 355) {
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
#line 326 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1796 "syntax5.c"
			}
			/* END OF EXTRACT: hash-if */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: cond_hash_if */
		{
#line 1906 "syntax.act"

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
    (ZIp) = c ;
#line 1811 "syntax5.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: reach_check */
		{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1827 "syntax5.c"
		}
		/* END OF ACTION: reach_check */
		ZRcompound_Hstatement (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1121 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1839 "syntax5.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_if */
		{
#line 1054 "syntax.act"

    (ZIe) = begin_hash_if_stmt ( (ZIc), (ZIa) ) ;
#line 1847 "syntax5.c"
		}
		/* END OF ACTION: stmt_hash_if */
		ZR1190 (ZIe, ZIp, ZIr, &ZI1187, &ZI1188, &ZI1189);
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
	*ZO1187 = ZI1187;
	*ZO1188 = ZI1188;
	*ZO1189 = ZI1189;
}

void
ZRcv_Hqualifier_Hseq(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		CV_SPEC ZIa;

		ZRcv_Hqualifier (&ZIa);
		/* BEGINNING OF INLINE: 788 */
		{
			switch (CURRENT_TERMINAL) {
			case 98: case 124:
				{
					CV_SPEC ZIb;

					ZRcv_Hqualifier_Hseq (&ZIb);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: cv_join */
					{
#line 1214 "syntax.act"

    CV_SPEC c = ( (ZIa) & (ZIb) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIa) | (ZIb) ) ;
#line 1897 "syntax5.c"
					}
					/* END OF ACTION: cv_join */
				}
				break;
			default:
				{
					ZIcv = ZIa;
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 788 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

void
ZR1472(IDENTIFIER *ZI1471, EXP *ZOe)
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZIid) = (*ZI1471) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1966 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 673 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 1974 "syntax5.c"
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
			ZR1291 (&ZI1289, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2009 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2017 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 2025 "syntax5.c"
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
#line 538 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2049 "syntax5.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 1011 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 2057 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 994 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZI1471), lex_identifier ) ;
#line 2065 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 998 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 2079 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_end */
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
ZR1218(EXP ZI1216, EXP *ZO1217)
{
	EXP ZI1217;

ZL2_1218:;
	switch (CURRENT_TERMINAL) {
	case 48: case 63:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 378 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 2114 "syntax5.c"
			}
			/* END OF ACTION: lex_crt */
			ZRequality_Hoperator ();
			ZRrelational_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_equality */
			{
#line 652 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_equality_exp ( (ZIop), (ZI1216), (ZIb) ) ;
#line 2129 "syntax5.c"
			}
			/* END OF ACTION: exp_equality */
			/* BEGINNING OF INLINE: 1218 */
			ZI1216 = ZIe;
			goto ZL2_1218;
			/* END OF INLINE: 1218 */
		}
		UNREACHED;
	default:
		{
			ZI1217 = ZI1216;
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
	*ZO1217 = ZI1217;
}

void
ZRfunction_Hbody(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIb;
		EXP ZId;
		EXP ZIa;

		ZRctor_Hinitialiser_Hopt (ZIc, &ZIb, &ZId);
		/* BEGINNING OF INLINE: open-brace */
		{
			if ((CURRENT_TERMINAL) == 355) {
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
#line 898 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIb) ), 2 ) ;
#line 2190 "syntax5.c"
		}
		/* END OF ACTION: stmt_compound_block */
		ZRstatement_Hseq_Hopt (ZIb, &ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: ctor_postlude */
		{
#line 1183 "syntax.act"

    (ZIe) = ctor_postlude ( (ZIa), (ZId) ) ;
#line 2203 "syntax5.c"
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
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1346(NAMESPACE *ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 218 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2243 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 482 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 2253 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2262 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZI1343;
			IDENTIFIER ZItid;

			/* BEGINNING OF INLINE: any-type-name */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						/* BEGINNING OF EXTRACT: template-type */
						{
#line 236 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1343 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 2286 "syntax5.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "syntax.act"

    ZI1343 = crt_token->pp_data.id.use ;
#line 2299 "syntax5.c"
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
#line 482 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 2316 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZItid) = check_id ( (*ZIns), (ZI1343), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2325 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1721 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 2333 "syntax5.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 482 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 2356 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 508 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 2365 "syntax5.c"
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
ZR1601(EXP *ZI1600, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 347:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 553 "syntax.act"

    CONS_exp ( (*ZI1600), (ZIq), (ZIp) ) ;
#line 2407 "syntax5.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 608 "syntax.act"

    (ZIa) = make_comma_exp ( (ZIp) ) ;
#line 2415 "syntax5.c"
			}
			/* END OF ACTION: exp_comma */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2431 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2439 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 2447 "syntax5.c"
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
			case 347:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2484 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (*ZI1600) ) ;
#line 2492 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 2500 "syntax5.c"
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
ZR1474(IDENTIFIER *ZI1473, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	default:
		{
			IDENTIFIER ZIid;
			EXP ZIa;

			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZIid) = (*ZI1473) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2536 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 673 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 2544 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2552 "syntax5.c"
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
#line 538 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2569 "syntax5.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 1011 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 2577 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 994 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZI1473), lex_identifier ) ;
#line 2585 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 998 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 2599 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_end */
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
	*ZOe = ZIe;
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
#line 218 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2630 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 487 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 2640 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2649 "syntax5.c"
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
#line 236 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1344 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 2673 "syntax5.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "syntax.act"

    ZI1344 = crt_token->pp_data.id.use ;
#line 2686 "syntax5.c"
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
#line 487 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 2703 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZItid) = check_id ( (*ZIns), (ZI1344), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2712 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1721 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 2720 "syntax5.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 487 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 2743 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 508 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 2752 "syntax5.c"
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
ZRcv_Hqualifier_Hseq_Hopt(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 98: case 124:
		{
			ZRcv_Hqualifier_Hseq (&ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1209 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2791 "syntax5.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZOcv = ZIcv;
}

void
ZR1475(NAMESPACE *ZIns, EXP *ZOe)
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
#line 218 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2824 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 482 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZIns) ;
#line 2834 "syntax5.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 2843 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 673 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 2851 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2859 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 141: case 147:
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
			EXP ZIa;
			int ZIr;

			ZR1268 (ZIns, &ZI1454);
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
			ZR1291 (&ZI1289, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2916 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2924 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 2932 "syntax5.c"
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
ZR1348(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 4:
		{
			IDENTIFIER ZIuid;
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 218 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 2973 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 475 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 2984 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2993 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZI1345;
			NAMESPACE ZIns;
			IDENTIFIER ZItid;

			/* BEGINNING OF INLINE: any-type-name */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						/* BEGINNING OF EXTRACT: template-type */
						{
#line 236 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1345 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3018 "syntax5.c"
						}
						/* END OF EXTRACT: template-type */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "syntax.act"

    ZI1345 = crt_token->pp_data.id.use ;
#line 3031 "syntax5.c"
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
#line 475 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3049 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZItid) = check_id ( (ZIns), (ZI1345), 0 ) ;
    last_namespace = (ZIns) ;
#line 3058 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1721 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 3066 "syntax5.c"
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
#line 475 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3085 "syntax5.c"
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
#line 508 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (ZIns) ;
#line 3100 "syntax5.c"
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
ZR1094(BASE_TYPE *ZIbt, DECL_SPEC *ZIds3, TYPE *ZIt3, ACCESS_LIST *ZIr, IDENTIFIER *ZId)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		/* BEGINNING OF ACTION: is_function */
		{
#line 2061 "syntax.act"

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
#line 3131 "syntax5.c"
		}
		/* END OF ACTION: is_function */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: access_free */
		{
#line 1473 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3141 "syntax5.c"
		}
		/* END OF ACTION: access_free */
		/* BEGINNING OF ACTION: function_skip */
		{
#line 1154 "syntax.act"

    skip_function ( (*ZId) ) ;
#line 3149 "syntax5.c"
		}
		/* END OF ACTION: function_skip */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1700 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3157 "syntax5.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2136 "syntax.act"

    RESCAN_LEXER ;
#line 3165 "syntax5.c"
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
#line 1700 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3183 "syntax5.c"
			}
			/* END OF ACTION: declarator_end */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZIn) = 0 ; 
#line 3190 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1693 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3198 "syntax5.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator_Hlist (*ZIds3, *ZIt3, *ZIbt, *ZIr, ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_free */
			{
#line 1473 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3211 "syntax5.c"
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
#line 1473 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3231 "syntax5.c"
			}
			/* END OF ACTION: access_free */
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1700 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3239 "syntax5.c"
			}
			/* END OF ACTION: declarator_end */
		}
		break;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
}

void
ZRcondition(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZId;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2073 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 3274 "syntax5.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: cond_start */
		{
#line 1079 "syntax.act"

    begin_cond () ;
#line 3284 "syntax5.c"
		}
		/* END OF ACTION: cond_start */
		ZRcondition_Hdeclarator (&ZId);
		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		case 355:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRinitialiser_Hexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 3310 "syntax5.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1749 "syntax.act"

    int def = init_object ( (ZId), (ZIa) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 3319 "syntax5.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 3329 "syntax5.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1700 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 3337 "syntax5.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: cond_end */
		{
#line 1082 "syntax.act"

    (ZIe) = end_cond () ;
    in_declaration-- ;
#line 3346 "syntax5.c"
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
	case 330: case 346:
		{
			ZRexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
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
	SAVE_LEXER (355);
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
#line 218 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3406 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 487 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 3416 "syntax5.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 3425 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 673 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 3433 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3441 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 141: case 147:
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
			EXP ZIa;
			int ZIr;

			ZR1269 (ZIns, &ZI1454);
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
			ZR1291 (&ZI1289, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3498 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3506 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 3514 "syntax5.c"
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
ZR1222(EXP ZI1220, EXP *ZO1221)
{
	EXP ZI1221;

ZL2_1222:;
	switch (CURRENT_TERMINAL) {
	case 49: case 50: case 53: case 54:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 378 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 3556 "syntax5.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_relation */
			{
#line 796 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_relation_exp ( (ZIop), (ZI1220), (ZIb) ) ;
#line 3598 "syntax5.c"
			}
			/* END OF ACTION: exp_relation */
			/* BEGINNING OF INLINE: 1222 */
			ZI1220 = ZIe;
			goto ZL2_1222;
			/* END OF INLINE: 1222 */
		}
		UNREACHED;
	default:
		{
			ZI1221 = ZI1220;
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
	*ZO1221 = ZI1221;
}

void
ZR1477(EXP *ZOe)
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
#line 218 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3641 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_global */
			{
#line 475 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3652 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 491 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 3661 "syntax5.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 673 "syntax.act"

    (ZIa) = make_id_exp ( (ZIid) ) ;
#line 3669 "syntax5.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3677 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 131: case 140:
	case 141: case 147:
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
			EXP ZIa;
			int ZIr;

			ZR1286 (&ZI1454);
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
			ZR1291 (&ZI1289, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1110 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3735 "syntax5.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 939 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3743 "syntax5.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1007 "syntax.act"

    unreached_fall = 1 ;
#line 3751 "syntax5.c"
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
ZRbase_Hclause_Hopt(int *ZOt)
{
	int ZIt;

	switch (CURRENT_TERMINAL) {
	case 41:
		{
			ADVANCE_LEXER;
			ZR1328 (&ZIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2039 "syntax.act"
 (ZIt) = 1 ; 
#line 3798 "syntax5.c"
			}
			/* END OF ACTION: bool_true */
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
	*ZOt = ZIt;
}

void
ZRdirect_Hnew_Hdeclarator(TYPE *ZO1150)
{
	TYPE ZI1150;

	if ((CURRENT_TERMINAL) == 355) {
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
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_eval */
		{
#line 656 "syntax.act"

    (ZIe) = convert_reference ( (ZIa), REF_NORMAL ) ;
    (ZIe) = convert_lvalue ( (ZIe) ) ;
#line 3851 "syntax5.c"
		}
		/* END OF ACTION: exp_eval */
		/* BEGINNING OF ACTION: type_new_array */
		{
#line 1366 "syntax.act"

    /* First array bound in a new-declarator */
    NAT n = make_new_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 3861 "syntax5.c"
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
		ZR1151 (ZIt, &ZI1150);
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
	*ZO1150 = ZI1150;
}

void
ZR1605(void)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 1003 "syntax.act"

    unreached_fall = 0 ;
#line 3903 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_set */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 1003 "syntax.act"

    unreached_fall = 0 ;
#line 3915 "syntax5.c"
			}
			/* END OF ACTION: stmt_label_set */
		}
		break;
	case 355:
		return;
	}
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
#line 475 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 3941 "syntax5.c"
			}
			/* END OF ACTION: namespace_global */
		}
		break;
	case 8: case 9:
		{
			ZRnonempty_Hnested_Hname (&ZIns);
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
	*ZOns = ZIns;
}

void
ZRfall_Hcheck(void)
{
	switch (CURRENT_TERMINAL) {
	case 223:
		{
			ADVANCE_LEXER;
			ZR1605 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
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
#line 1210 "syntax.act"
 (ZIcv) = cv_const ; 
#line 4006 "syntax5.c"
			}
			/* END OF ACTION: cv_const */
		}
		break;
	case 124:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cv_volatile */
			{
#line 1211 "syntax.act"
 (ZIcv) = cv_volatile ; 
#line 4018 "syntax5.c"
			}
			/* END OF ACTION: cv_volatile */
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
	*ZOcv = ZIcv;
}

void
ZRmember_Hcond(void)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIp;

		ZRmember_Hcond_Hhead (&ZIp);
		/* BEGINNING OF INLINE: 838 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: cond_hash_else */
					{
#line 1917 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 4057 "syntax5.c"
					}
					/* END OF ACTION: cond_hash_else */
					/* BEGINNING OF ACTION: decl_hash_else */
					{
#line 1898 "syntax.act"

    target_decl ( lex_else, NULL_exp ) ;
#line 4065 "syntax5.c"
					}
					/* END OF ACTION: decl_hash_else */
					ZRmember_Hcond_Hbody ();
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 838 */
		/* BEGINNING OF ACTION: cond_hash_endif */
		{
#line 1920 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 4088 "syntax5.c"
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
#line 1902 "syntax.act"

    target_decl ( lex_endif, NULL_exp ) ;
#line 4103 "syntax5.c"
		}
		/* END OF ACTION: decl_hash_endif */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1226(EXP ZI1224, EXP *ZO1225)
{
	EXP ZI1225;

ZL2_1226:;
	switch (CURRENT_TERMINAL) {
	case 57:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRadditive_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lshift */
			{
#line 709 "syntax.act"

    (ZIe) = make_shift_exp ( lex_lshift, (ZI1224), (ZIb) ) ;
#line 4136 "syntax5.c"
			}
			/* END OF ACTION: exp_lshift */
			/* BEGINNING OF INLINE: 1226 */
			ZI1224 = ZIe;
			goto ZL2_1226;
			/* END OF INLINE: 1226 */
		}
		UNREACHED;
	case 75:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRadditive_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_rshift */
			{
#line 804 "syntax.act"

    (ZIe) = make_shift_exp ( lex_rshift, (ZI1224), (ZIb) ) ;
#line 4161 "syntax5.c"
			}
			/* END OF ACTION: exp_rshift */
			/* BEGINNING OF INLINE: 1226 */
			ZI1224 = ZIe;
			goto ZL2_1226;
			/* END OF INLINE: 1226 */
		}
		UNREACHED;
	default:
		{
			ZI1225 = ZI1224;
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
	*ZO1225 = ZI1225;
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
	case 355:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRmember_Hdeclarator(DECL_SPEC ZIds, TYPE ZIp, BASE_TYPE ZIq, ACCESS_LIST ZIr, int ZIf, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			ADVANCE_LEXER;
			ZR1348 (&ZI1355);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 4262 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 4269 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4277 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4290 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 4298 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4306 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 4339 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4347 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4357 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4371 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4381 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 5:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 222 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4404 "syntax5.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 502 "syntax.act"

    (ZI1355) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4415 "syntax5.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 4423 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 4430 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4438 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4451 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 4459 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4467 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 4500 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4508 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4518 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4532 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4542 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 9:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 255 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4565 "syntax5.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1347 (&ZIns, &ZI1355);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 4579 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 4586 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4594 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4607 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 4615 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4623 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 4656 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4664 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4674 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4688 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4698 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 1:
		{
			IDENTIFIER ZI1362;
			IDENTIFIER ZI1363;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 206 "syntax.act"

    ZI1362 = crt_token->pp_data.id.use ;
#line 4713 "syntax5.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZI1363) = (ZI1362) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4724 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1367 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1363, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 3:
		{
			IDENTIFIER ZI1365;
			IDENTIFIER ZI1366;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 214 "syntax.act"

    ZI1365 = crt_token->pp_data.id.use ;
#line 4744 "syntax5.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZI1366) = (ZI1365) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4755 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1367 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1366, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 251 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4783 "syntax5.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1346 (&ZIns, &ZI1355);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 4797 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 4804 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4812 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4825 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 4833 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4841 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 4874 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 4882 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4892 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 4906 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4916 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 65:
		{
			TYPE ZI1352;
			IDENTIFIER ZI1353;
			int ZI1354;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRdeclarator_Haux (&ZI1352, &ZI1353, &ZI1354);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZI1354) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4944 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1725 "syntax.act"

    if ( IS_NULL_type ( (ZI1352) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 4954 "syntax5.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1179 (ZI1352, ZI1353, ZI1354, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 4974 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 4982 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4990 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 5023 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5031 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5041 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5055 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5065 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 4:
		{
			IDENTIFIER ZI1359;
			IDENTIFIER ZI1360;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 218 "syntax.act"

    ZI1359 = crt_token->pp_data.id.use ;
#line 5080 "syntax5.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZI1360) = (ZI1359) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5091 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1367 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1360, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 6:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 228 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5123 "syntax5.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 502 "syntax.act"

    (ZI1355) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5134 "syntax5.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 5142 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 5149 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5157 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5170 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 5178 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5186 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 5219 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5227 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5237 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5251 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5261 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 7:
		{
			IDENTIFIER ZI1358;
			IDENTIFIER ZItid;
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 236 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1358 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5289 "syntax5.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZItid) = (ZI1358) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5300 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1721 "syntax.act"

    (ZI1355) = constr_name ( last_namespace, (ZItid) ) ;
#line 5308 "syntax5.c"
			}
			/* END OF ACTION: declarator_type */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 5316 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 5323 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5331 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5344 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 5352 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5360 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 5393 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5401 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5411 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5425 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5435 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 2:
		{
			IDENTIFIER ZI1368;
			IDENTIFIER ZI1369;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 210 "syntax.act"

    ZI1368 = crt_token->pp_data.id.use ;
#line 5450 "syntax5.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 496 "syntax.act"

    (ZI1369) = (ZI1368) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5461 "syntax5.c"
			}
			/* END OF ACTION: namespace_simple */
			ZR1370 (&ZIds, &ZIp, &ZIq, &ZIr, &ZIf, &ZI1369, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 141:
		{
			IDENTIFIER ZIuid;
			IDENTIFIER ZI1355;
			TYPE ZI1356;
			int ZI1357;
			TYPE ZI1349;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			parse_operator (&ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 502 "syntax.act"

    (ZI1355) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5496 "syntax5.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1265 "syntax.act"

    (ZI1356) = NULL_type ;
#line 5504 "syntax5.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2038 "syntax.act"
 (ZI1357) = 0 ; 
#line 5511 "syntax5.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5519 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5532 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 5540 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5548 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 5581 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5589 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5599 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5613 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5623 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	case 10: case 11: case 33: case 78:
		{
			TYPE ZI1350;
			TYPE ZI1351;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZI1349;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			ZRptr_Hoperator (&ZI1350);
			ZRdeclarator_Haux (&ZI1351, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1386 "syntax.act"

    (ZI1349) = ( IS_NULL_type ( (ZI1351) ) ? (ZI1350) : inject_pre_type ( (ZI1351), (ZI1350), 0 ) ) ;
#line 5650 "syntax5.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5658 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1382 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1349) ) ? (ZIp) : inject_pre_type ( (ZI1349), (ZIp), 1 ) ) ;
#line 5666 "syntax5.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1763 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 5674 "syntax5.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1631 "syntax.act"

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
#line 5707 "syntax5.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5715 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5725 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
			ZRmember_Hspecifier_Hopt (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_member */
			{
#line 1758 "syntax.act"

    int def = ( (ZIfr) ? init_object ( (ZId), (ZIe) ) : init_member ( (ZId), (ZIe) ) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 5739 "syntax5.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5749 "syntax5.c"
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
#line 455 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5770 "syntax5.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1853 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 5778 "syntax5.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1696 "syntax.act"

    begin_declarator ( (ZIid), crt_id_qualifier, qual_namespace, 1 ) ;
#line 5786 "syntax5.c"
			}
			/* END OF ACTION: declarator_begin */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 525 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 5795 "syntax5.c"
			}
			/* END OF ACTION: qual_get */
			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 530 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 5810 "syntax5.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_bitfield_mem */
			{
#line 1376 "syntax.act"

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZIid) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZIt) = make_bitfield_type ( (ZIp), (ZIq), (ZIc), z ) ;
#line 5821 "syntax5.c"
			}
			/* END OF ACTION: type_bitfield_mem */
			/* BEGINNING OF ACTION: declare_bitfield */
			{
#line 1667 "syntax.act"

    IDENTIFIER id = make_member_decl ( (ZIds), (ZIt), (ZIid), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZId) = id ;
#line 5835 "syntax5.c"
			}
			/* END OF ACTION: declare_bitfield */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1465 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 5843 "syntax5.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1460 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 5853 "syntax5.c"
			}
			/* END OF ACTION: access_check_decl */
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
	*ZOd = ZId;
}

/* END OF FILE */
