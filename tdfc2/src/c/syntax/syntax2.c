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
#line 168 "syntax.act"



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

#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
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
#include <parse/hash.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/inttype.h>
#include <construct/label.h>
#include <parse/preproc.h>
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


/*
    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include <syntax/syntax.h>


#line 96 "syntax2.c"

void
ZR917(EXP ZI915, EXP *ZO916)
{
	EXP ZI916;

ZL2_917:;
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
#line 545 "syntax.act"

    (ZIe) = make_minus_exp ( (ZI915), (ZIb) ) ;
#line 121 "syntax2.c"
			}
			/* END OF ACTION: exp_minus */
			/* BEGINNING OF INLINE: 917 */
			ZI915 = ZIe;
			goto ZL2_917;
			/* END OF INLINE: 917 */
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
#line 570 "syntax.act"

    (ZIe) = make_plus_exp ( (ZI915), (ZIb) ) ;
#line 146 "syntax2.c"
			}
			/* END OF ACTION: exp_plus */
			/* BEGINNING OF INLINE: 917 */
			ZI915 = ZIe;
			goto ZL2_917;
			/* END OF INLINE: 917 */
		}
		UNREACHED;
	default:
		{
			ZI916 = ZI915;
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
	*ZO916 = ZI916;
}

void
ZR1045(TYPE *ZO857, IDENTIFIER *ZO858)
{
	TYPE ZI857;
	IDENTIFIER ZI858;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZI1046;
		TYPE ZI1047;
		TYPE ZIt;
		IDENTIFIER ZIid;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 1451 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 192 "syntax2.c"
		}
		/* END OF ACTION: is_parameter */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 207 "syntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 208 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 220 "syntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 200 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 233 "syntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: any-identifier */
		/* BEGINNING OF ACTION: type_none */
		{
#line 950 "syntax.act"

    (ZI1047) = NULL_type ;
#line 249 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_begin */
		{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1046) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 258 "syntax2.c"
		}
		/* END OF ACTION: declarator_begin */
		ZR859 (ZI1047, ZI1046, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declarator_bad */
		{
#line 1226 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 273 "syntax2.c"
		}
		/* END OF ACTION: declarator_bad */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR859 (ZIt, ZIid, &ZI857, &ZI858);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIt;
			IDENTIFIER ZIid;

			ADVANCE_LEXER;
			ZR1045 (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1226 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 311 "syntax2.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR859 (ZIt, ZIid, &ZI857, &ZI858);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 333:
		{
			IDENTIFIER ZI1044;
			int ZIell;
			TYPE ZI1050;
			IDENTIFIER ZI1051;
			TYPE ZIt;
			IDENTIFIER ZIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 383 "syntax.act"

    (ZI1044) = NULL_id ;
#line 350 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1044) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 361 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZR761 (&ZIell);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_func_weak */
			{
#line 1018 "syntax.act"

    (ZI1050) = make_func_type ( NULL_type, ( (ZIell) | FUNC_WEAK ), cv_c, empty_type_set ) ;
#line 374 "syntax2.c"
			}
			/* END OF ACTION: type_func_weak */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_end */
			{
#line 883 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 391 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1051) = DEREF_id ( hashid_id ( nm ) ) ;
#line 400 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1051) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 409 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZI1050, ZI1051, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1226 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 424 "syntax2.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR859 (ZIt, ZIid, &ZI857, &ZI858);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZI1048;
			IDENTIFIER ZI1049;
			TYPE ZIt;
			IDENTIFIER ZIid;

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
			ZR760 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1030 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1048) ) ;
#line 473 "syntax2.c"
			}
			/* END OF ACTION: type_array */
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
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1049) = DEREF_id ( hashid_id ( nm ) ) ;
#line 495 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1049) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 504 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZI1048, ZI1049, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1226 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 519 "syntax2.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR859 (ZIt, ZIid, &ZI857, &ZI858);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			TYPE ZIp;
			TYPE ZIq;
			IDENTIFIER ZIid;
			TYPE ZIt;

			ZRptr_Hoperator (&ZIp);
			ZRparameter_Hdeclarator_Haux_Hopt (&ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1050 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 554 "syntax2.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1226 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 564 "syntax2.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR859 (ZIt, ZIid, &ZI857, &ZI858);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 25: case 39: case 47:
	case 94: case 97: case 98: case 102:
	case 104: case 105: case 106: case 110:
	case 111: case 112: case 114: case 115:
	case 117: case 118: case 120: case 121:
	case 122: case 123: case 124: case 137:
	case 156: case 185: case 286: case 299:
		{
			IDENTIFIER ZI1043;
			TYPE ZIs;
			TYPE ZIt;
			IDENTIFIER ZIid;

			/* BEGINNING OF ACTION: id_none */
			{
#line 383 "syntax.act"

    (ZI1043) = NULL_id ;
#line 599 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1043) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 610 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZR758 (&ZIs);
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
			ZIt = ZIs;
			/* BEGINNING OF ACTION: param_end */
			{
#line 883 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 632 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
#line 641 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 650 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZIt, ZIid, &ZI857, &ZI858);
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
	*ZO857 = ZI857;
	*ZO858 = ZI858;
}

void
ZRparameter_Hid_Htail(void)
{
ZL2_parameter_Hid_Htail:;
	switch (CURRENT_TERMINAL) {
	case 42:
		{
			IDENTIFIER ZIid;

			ADVANCE_LEXER;
			ZRsecond_Hparameter_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 693 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			/* BEGINNING OF ACTION: declare_weak_param */
			{
#line 1190 "syntax.act"

    IGNORE weak_param_decl ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 703 "syntax2.c"
			}
			/* END OF ACTION: declare_weak_param */
			/* BEGINNING OF INLINE: parameter-id-tail */
			goto ZL2_parameter_Hid_Htail;
			/* END OF INLINE: parameter-id-tail */
		}
		UNREACHED;
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
ZR921(EXP ZI919, EXP *ZO920)
{
	EXP ZI920;

ZL2_921:;
	switch (CURRENT_TERMINAL) {
	case 44:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_div */
			{
#line 475 "syntax.act"

    (ZIe) = make_mult_exp ( lex_div, (ZI919), (ZIb) ) ;
#line 745 "syntax2.c"
			}
			/* END OF ACTION: exp_div */
			/* BEGINNING OF INLINE: 921 */
			ZI919 = ZIe;
			goto ZL2_921;
			/* END OF INLINE: 921 */
		}
		UNREACHED;
	case 73:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_rem */
			{
#line 599 "syntax.act"

    (ZIe) = make_rem_exp ( (ZI919), (ZIb) ) ;
#line 770 "syntax2.c"
			}
			/* END OF ACTION: exp_rem */
			/* BEGINNING OF INLINE: 921 */
			ZI919 = ZIe;
			goto ZL2_921;
			/* END OF INLINE: 921 */
		}
		UNREACHED;
	case 78:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_mult */
			{
#line 549 "syntax.act"

    (ZIe) = make_mult_exp ( lex_star, (ZI919), (ZIb) ) ;
#line 795 "syntax2.c"
			}
			/* END OF ACTION: exp_mult */
			/* BEGINNING OF INLINE: 921 */
			ZI919 = ZIe;
			goto ZL2_921;
			/* END OF INLINE: 921 */
		}
		UNREACHED;
	default:
		{
			ZI920 = ZI919;
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
	*ZO920 = ZI920;
}

void
ZRparameter_Hdeclarator_Haux_Hopt(TYPE *ZOt, IDENTIFIER *ZOid)
{
	TYPE ZIt;
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZI1046;
		TYPE ZI1047;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 1451 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 839 "syntax2.c"
		}
		/* END OF ACTION: is_parameter */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 854 "syntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 208 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 867 "syntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 200 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 880 "syntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: any-identifier */
		/* BEGINNING OF ACTION: type_none */
		{
#line 950 "syntax.act"

    (ZI1047) = NULL_type ;
#line 896 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_begin */
		{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1046) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 905 "syntax2.c"
		}
		/* END OF ACTION: declarator_begin */
		ZR859 (ZI1047, ZI1046, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			ZR1045 (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 333:
		{
			IDENTIFIER ZI1044;
			int ZIell;
			TYPE ZI1050;
			IDENTIFIER ZI1051;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 383 "syntax.act"

    (ZI1044) = NULL_id ;
#line 948 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1044) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 959 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZR761 (&ZIell);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_func_weak */
			{
#line 1018 "syntax.act"

    (ZI1050) = make_func_type ( NULL_type, ( (ZIell) | FUNC_WEAK ), cv_c, empty_type_set ) ;
#line 972 "syntax2.c"
			}
			/* END OF ACTION: type_func_weak */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_end */
			{
#line 883 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 989 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1051) = DEREF_id ( hashid_id ( nm ) ) ;
#line 998 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1051) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1007 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZI1050, ZI1051, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZI1048;
			IDENTIFIER ZI1049;

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
			ZR760 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1030 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1048) ) ;
#line 1047 "syntax2.c"
			}
			/* END OF ACTION: type_array */
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
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1049) = DEREF_id ( hashid_id ( nm ) ) ;
#line 1069 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1049) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1078 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZI1048, ZI1049, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			TYPE ZIp;
			TYPE ZIq;

			ZRptr_Hoperator (&ZIp);
			ZRparameter_Hdeclarator_Haux_Hopt (&ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1050 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 1104 "syntax2.c"
			}
			/* END OF ACTION: type_build */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZIt) = NULL_type ;
#line 1116 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
#line 1125 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1134 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOid = ZIid;
}

void
ZRasm_Hdefinition(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;
		SID_LIST_EXP ZIp;

		switch (CURRENT_TERMINAL) {
		case 126:
			break;
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
		/* BEGINNING OF INLINE: string-literal */
		{
			switch (CURRENT_TERMINAL) {
			case 19:
				{
					/* BEGINNING OF EXTRACT: string-exp */
					{
#line 298 "syntax.act"

    ZIa = crt_token->pp_data.exp ;
#line 1185 "syntax2.c"
					}
					/* END OF EXTRACT: string-exp */
					ADVANCE_LEXER;
				}
				break;
			case 20:
				{
					/* BEGINNING OF EXTRACT: wstring-exp */
					{
#line 302 "syntax.act"

    ZIa = crt_token->pp_data.exp ;
#line 1198 "syntax2.c"
					}
					/* END OF EXTRACT: wstring-exp */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: string-literal */
		ZR627 (&ZIp);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_asm */
		{
#line 1287 "syntax.act"

    (ZIe) = make_asm ( (ZIa), (ZIp) ) ;
#line 1219 "syntax2.c"
		}
		/* END OF ACTION: declare_asm */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRsemicolon_Hx ();
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
	*ZOe = ZIe;
}

void
ZRparameter_Hdeclarator_Hopt(TYPE ZIp, TYPE *ZOt, IDENTIFIER *ZOid)
{
	TYPE ZIt;
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZI1046;
		TYPE ZI1047;
		TYPE ZIq;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 1451 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 1263 "syntax2.c"
		}
		/* END OF ACTION: is_parameter */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 1278 "syntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 208 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 1291 "syntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 200 "syntax.act"

    ZI1046 = crt_token->pp_data.id.use ;
#line 1304 "syntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: any-identifier */
		/* BEGINNING OF ACTION: type_none */
		{
#line 950 "syntax.act"

    (ZI1047) = NULL_type ;
#line 1320 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_begin */
		{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1046) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1329 "syntax2.c"
		}
		/* END OF ACTION: declarator_begin */
		ZR859 (ZI1047, ZI1046, &ZIq, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1342 "syntax2.c"
		}
		/* END OF ACTION: type_inject */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIq;

			ADVANCE_LEXER;
			ZR1045 (&ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1365 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 333:
		{
			IDENTIFIER ZI1044;
			int ZIell;
			TYPE ZI1050;
			IDENTIFIER ZI1051;
			TYPE ZIq;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 383 "syntax.act"

    (ZI1044) = NULL_id ;
#line 1391 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1044) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1402 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZR761 (&ZIell);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_func_weak */
			{
#line 1018 "syntax.act"

    (ZI1050) = make_func_type ( NULL_type, ( (ZIell) | FUNC_WEAK ), cv_c, empty_type_set ) ;
#line 1415 "syntax2.c"
			}
			/* END OF ACTION: type_func_weak */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_end */
			{
#line 883 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 1432 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1051) = DEREF_id ( hashid_id ( nm ) ) ;
#line 1441 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1051) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1450 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZI1050, ZI1051, &ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1463 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZI1048;
			IDENTIFIER ZI1049;
			TYPE ZIq;

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
			ZR760 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1030 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1048) ) ;
#line 1499 "syntax2.c"
			}
			/* END OF ACTION: type_array */
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
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1049) = DEREF_id ( hashid_id ( nm ) ) ;
#line 1521 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1049) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1530 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR859 (ZI1048, ZI1049, &ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1543 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 78:
		{
			TYPE ZI1052;
			TYPE ZI1053;
			TYPE ZIq;

			ZRptr_Hoperator (&ZI1052);
			ZRparameter_Hdeclarator_Haux_Hopt (&ZI1053, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1050 "syntax.act"

    (ZIq) = ( IS_NULL_type ( (ZI1053) ) ? (ZI1052) : inject_pre_type ( (ZI1053), (ZI1052), 0 ) ) ;
#line 1565 "syntax2.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1573 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	default:
		{
			TYPE ZIq;

			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZIq) = NULL_type ;
#line 1587 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
#line 1596 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1605 "syntax2.c"
			}
			/* END OF ACTION: declarator_begin */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1613 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOid = ZIid;
}

void
ZRconditional_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZI951;

		ZRlogical_Hor_Hexpression (&ZI951);
		ZR953 (&ZI951, &ZIe);
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
	*ZOe = ZIe;
}

void
ZR925(EXP ZI923, EXP *ZO924)
{
	EXP ZI924;

ZL2_925:;
	switch (CURRENT_TERMINAL) {
	case 61:
		{
			EXP ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_postdec */
			{
#line 574 "syntax.act"

    (ZIe) = make_postfix_exp ( lex_minus_Hminus, (ZI923) ) ;
#line 1671 "syntax2.c"
			}
			/* END OF ACTION: exp_postdec */
			/* BEGINNING OF INLINE: 925 */
			ZI923 = ZIe;
			goto ZL2_925;
			/* END OF INLINE: 925 */
		}
		UNREACHED;
	case 65:
		{
			SID_LIST_EXP ZIp;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRexpression_Hlist_Hopt (&ZIp);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_func */
			{
#line 501 "syntax.act"

    (ZIe) = make_func_exp ( (ZI923), (ZIp), 0 ) ;
#line 1696 "syntax2.c"
			}
			/* END OF ACTION: exp_func */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 925 */
			ZI923 = ZIe;
			goto ZL2_925;
			/* END OF INLINE: 925 */
		}
		UNREACHED;
	case 71:
		{
			EXP ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_postinc */
			{
#line 578 "syntax.act"

    (ZIe) = make_postfix_exp ( lex_plus_Hplus, (ZI923) ) ;
#line 1722 "syntax2.c"
			}
			/* END OF ACTION: exp_postinc */
			/* BEGINNING OF INLINE: 925 */
			ZI923 = ZIe;
			goto ZL2_925;
			/* END OF INLINE: 925 */
		}
		UNREACHED;
	case 66:
		{
			EXP ZIb;
			EXP ZIe;

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
			ZRexpression (&ZIb);
			/* BEGINNING OF INLINE: close-square */
			{
				if ((CURRENT_TERMINAL) == 356) {
					RESTORE_LEXER;
					goto ZL1;
				}
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
			/* BEGINNING OF ACTION: exp_index */
			{
#line 513 "syntax.act"

    (ZIe) = make_index_exp ( (ZI923), (ZIb) ) ;
#line 1772 "syntax2.c"
			}
			/* END OF ACTION: exp_index */
			/* BEGINNING OF INLINE: 925 */
			ZI923 = ZIe;
			goto ZL2_925;
			/* END OF INLINE: 925 */
		}
		UNREACHED;
	case 35:
		{
			EXP ZIb;
			TYPE ZIt;
			NAMESPACE ZIns;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: exp_arrow_begin */
			{
#line 445 "syntax.act"

    (ZIb) = begin_field_exp ( lex_arrow, (ZI923), &(ZIt), &(ZIns) ) ;
#line 1794 "syntax2.c"
			}
			/* END OF ACTION: exp_arrow_begin */
			ADVANCE_LEXER;
			ZRfield_Hid_Hexpression (ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_arrow_end */
			{
#line 449 "syntax.act"

    (ZIe) = end_field_exp ( lex_arrow, (ZIb), (ZIt), (ZIns), (ZIid), 0 ) ;
#line 1808 "syntax2.c"
			}
			/* END OF ACTION: exp_arrow_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 1816 "syntax2.c"
			}
			/* END OF ACTION: rescan_token */
			/* BEGINNING OF INLINE: 925 */
			ZI923 = ZIe;
			goto ZL2_925;
			/* END OF INLINE: 925 */
		}
		UNREACHED;
	case 46:
		{
			EXP ZIb;
			TYPE ZIt;
			NAMESPACE ZIns;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: exp_dot_begin */
			{
#line 479 "syntax.act"

    (ZIb) = begin_field_exp ( lex_dot, (ZI923), &(ZIt), &(ZIns) ) ;
#line 1838 "syntax2.c"
			}
			/* END OF ACTION: exp_dot_begin */
			ADVANCE_LEXER;
			ZRfield_Hid_Hexpression (ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dot_end */
			{
#line 483 "syntax.act"

    (ZIe) = end_field_exp ( lex_dot, (ZIb), (ZIt), (ZIns), (ZIid), 0 ) ;
#line 1852 "syntax2.c"
			}
			/* END OF ACTION: exp_dot_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 1860 "syntax2.c"
			}
			/* END OF ACTION: rescan_token */
			/* BEGINNING OF INLINE: 925 */
			ZI923 = ZIe;
			goto ZL2_925;
			/* END OF INLINE: 925 */
		}
		UNREACHED;
	default:
		{
			ZI924 = ZI923;
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
	*ZO924 = ZI924;
}

void
parse_type(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		parse_tok_type (&ZIt);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_check */
		{
#line 995 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 1904 "syntax2.c"
		}
		/* END OF ACTION: type_check */
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 1919 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: type_none */
		{
#line 950 "syntax.act"

    (ZIt) = NULL_type ;
#line 1927 "syntax2.c"
		}
		/* END OF ACTION: type_none */
	}
ZL0:;
	*ZOt = ZIt;
}

void
ZRdesignator_Hlist(OFFSET ZIb, TYPE ZIs, OFFSET *ZO850, TYPE *ZO851)
{
	OFFSET ZI850;
	TYPE ZI851;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_designator_Hlist:;
	{
		OFFSET ZIa;
		TYPE ZIt;

		ZRdesignator (ZIb, ZIs, &ZIa, &ZIt);
		/* BEGINNING OF INLINE: 849 */
		{
			switch (CURRENT_TERMINAL) {
			case 46: case 66:
				{
					/* BEGINNING OF INLINE: designator-list */
					ZIb = ZIa;
					ZIs = ZIt;
					goto ZL2_designator_Hlist;
					/* END OF INLINE: designator-list */
				}
				UNREACHED;
			default:
				{
					ZI850 = ZIa;
					ZI851 = ZIt;
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 849 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZO850 = ZI850;
	*ZO851 = ZI851;
}

void
ZR1054(IDENTIFIER *ZIid, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	default:
		{
			BASE_TYPE ZIkey;

			/* BEGINNING OF ACTION: key_enum */
			{
#line 1064 "syntax.act"
 (ZIkey) = btype_enum ; 
#line 1998 "syntax2.c"
			}
			/* END OF ACTION: key_enum */
			/* BEGINNING OF ACTION: type_elaborate */
			{
#line 965 "syntax.act"

    MAKE_type_pre ( cv_none, (ZIkey), qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (*ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
#line 2011 "syntax2.c"
			}
			/* END OF ACTION: type_elaborate */
		}
		break;
	case 64:
		{
			IDENTIFIER ZIp;
			IDENTIFIER ZItid;

			/* BEGINNING OF ACTION: type_enum_begin */
			{
#line 1093 "syntax.act"

    (ZIp) = begin_enum_defn ( (*ZIid), NULL_type ) ;
    no_type_defns++ ;
#line 2027 "syntax2.c"
			}
			/* END OF ACTION: type_enum_begin */
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
			ZR686 (&ZIp);
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
			/* BEGINNING OF ACTION: type_enum_end */
			{
#line 1098 "syntax.act"

    (ZItid) = end_enum_defn ( (ZIp) ) ;
#line 2066 "syntax2.c"
			}
			/* END OF ACTION: type_enum_end */
			/* BEGINNING OF ACTION: type_name */
			{
#line 959 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZItid) ) ;
    have_type_specifier = 1 ;
#line 2076 "syntax2.c"
			}
			/* END OF ACTION: type_name */
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
ZRdeclaration_Hcond_Hhead(EXP *ZO876)
{
	EXP ZI876;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIc;
		EXP ZIp;

		switch (CURRENT_TERMINAL) {
		case 26:
			/* BEGINNING OF EXTRACT: hash-if */
			{
#line 314 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 2111 "syntax2.c"
			}
			/* END OF EXTRACT: hash-if */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: cond_hash_if */
		{
#line 1308 "syntax.act"

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
    (ZIp) = c ;
#line 2126 "syntax2.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: decl_hash_if */
		{
#line 1291 "syntax.act"

    target_decl ( lex_if, (ZIc) ) ;
#line 2134 "syntax2.c"
		}
		/* END OF ACTION: decl_hash_if */
		ZRdeclaration_Hcond_Hbody ();
		ZR877 (ZIp, &ZI876);
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
	*ZO876 = ZI876;
}

void
ZRenum_Hspecifier(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 104:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 685 */
		{
			switch (CURRENT_TERMINAL) {
			case 1: case 2: case 4:
				{
					IDENTIFIER ZIid;

					/* BEGINNING OF INLINE: any-identifier */
					{
						switch (CURRENT_TERMINAL) {
						case 1:
							{
								/* BEGINNING OF EXTRACT: identifier */
								{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2185 "syntax2.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 208 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2198 "syntax2.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 200 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2211 "syntax2.c"
								}
								/* END OF EXTRACT: type-name */
								ADVANCE_LEXER;
							}
							break;
						default:
							goto ZL1;
						}
					}
					/* END OF INLINE: any-identifier */
					ZR1054 (&ZIid, &ZIt);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 64:
				{
					IDENTIFIER ZIid;
					IDENTIFIER ZIp;
					IDENTIFIER ZItid;

					/* BEGINNING OF ACTION: id_anon */
					{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
#line 2241 "syntax2.c"
					}
					/* END OF ACTION: id_anon */
					/* BEGINNING OF ACTION: type_enum_begin */
					{
#line 1093 "syntax.act"

    (ZIp) = begin_enum_defn ( (ZIid), NULL_type ) ;
    no_type_defns++ ;
#line 2250 "syntax2.c"
					}
					/* END OF ACTION: type_enum_begin */
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
					ZR686 (&ZIp);
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
					/* BEGINNING OF ACTION: type_enum_end */
					{
#line 1098 "syntax.act"

    (ZItid) = end_enum_defn ( (ZIp) ) ;
#line 2289 "syntax2.c"
					}
					/* END OF ACTION: type_enum_end */
					/* BEGINNING OF ACTION: type_name */
					{
#line 959 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZItid) ) ;
    have_type_specifier = 1 ;
#line 2299 "syntax2.c"
					}
					/* END OF ACTION: type_name */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 685 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZRdeclarator_Haux(TYPE *ZOt, IDENTIFIER *ZOid)
{
	TYPE ZIt;
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 4: case 65:
		{
			ZRdirect_Hdeclarator (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			TYPE ZIp;
			TYPE ZIq;

			ZRptr_Hoperator (&ZIp);
			ZRdeclarator_Haux (&ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1050 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 2350 "syntax2.c"
			}
			/* END OF ACTION: type_build */
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
	*ZOt = ZIt;
	*ZOid = ZIid;
}

void
ZRshift_Hexpression(EXP *ZO912)
{
	EXP ZI912;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRadditive_Hexpression (&ZIe);
		ZR913 (ZIe, &ZI912);
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
	*ZO912 = ZI912;
}

void
ZRfor_Hcond_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;
		EXP ZIb;

		ZR618 (&ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: bind_temporary */
		{
#line 818 "syntax.act"

    (ZIb) = bind_temporary ( (ZIa) ) ;
#line 2417 "syntax2.c"
		}
		/* END OF ACTION: bind_temporary */
		/* BEGINNING OF ACTION: exp_location */
		{
#line 525 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIb), (ZIe) ) ;
#line 2425 "syntax2.c"
		}
		/* END OF ACTION: exp_location */
		switch (CURRENT_TERMINAL) {
		case 77:
			break;
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
	*ZOe = ZIe;
}

void
ZRenumerator_Hdefinition(IDENTIFIER ZIe)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZIid;
		EXP ZIc;

		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2464 "syntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 208 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2477 "syntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 200 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2490 "syntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: any-identifier */
		/* BEGINNING OF ACTION: declarator_begin */
		{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 2507 "syntax2.c"
		}
		/* END OF ACTION: declarator_begin */
		/* BEGINNING OF INLINE: 682 */
		{
			switch (CURRENT_TERMINAL) {
			case 36:
				{
					ADVANCE_LEXER;
					ZRconstant_Hexpression (&ZIc);
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
#line 432 "syntax.act"

    (ZIc) = NULL_exp ;
#line 2530 "syntax2.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			}
		}
		/* END OF INLINE: 682 */
		/* BEGINNING OF ACTION: declare_enum */
		{
#line 1217 "syntax.act"

    IGNORE make_enumerator ( (ZIe), (ZIid), (ZIc) ) ;
#line 2543 "syntax2.c"
		}
		/* END OF ACTION: declare_enum */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRdeclarator(TYPE ZIp, TYPE *ZOt, IDENTIFIER *ZOid)
{
	TYPE ZIt;
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIq;

		ZRdeclarator_Haux (&ZIq, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 2575 "syntax2.c"
		}
		/* END OF ACTION: type_inject */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOid = ZIid;
}

void
ZRinitialiser_Hopt(IDENTIFIER ZId, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			ZRinitialiser_Hclause (ZId, &ZIe);
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
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2611 "syntax2.c"
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
parse_file(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZI940;
		TYPE ZI941;
		CV_SPEC ZI942;
		DECL_SPEC ZI943;
		BASE_TYPE ZI944;
		TYPE ZI945;
		CV_SPEC ZI946;
		DECL_SPEC ZI947;
		EXP ZIe;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 1421 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2650 "syntax2.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (&ZI940, &ZI941, &ZI942, &ZI943);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: check_decl_specifier */
		{
#line 1472 "syntax.act"

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
#line 2668 "syntax2.c"
		}
		/* END OF ACTION: check_decl_specifier */
		ZR727 (&ZI940, &ZI941, &ZI942, &ZI943, &ZI944, &ZI945, &ZI946, &ZI947);
		ZR948 (&ZI944, &ZI945, &ZI946, &ZI947, &ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_extern */
		{
#line 1236 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2682 "syntax2.c"
		}
		/* END OF ACTION: declare_extern */
		ZRdeclaration_Hseq_Hopt ();
		switch (CURRENT_TERMINAL) {
		case 32:
			break;
		case 356:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_empty */
			{
#line 1181 "syntax.act"

    report ( crt_loc, ERR_dcl_dcl_semicolon () ) ;
#line 2714 "syntax2.c"
			}
			/* END OF ACTION: declare_empty */
			ZRdeclaration_Hseq_Hopt ();
			switch (CURRENT_TERMINAL) {
			case 32:
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
	case 126:
		{
			EXP ZIe;

			ZRasm_Hdefinition (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1236 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2744 "syntax2.c"
			}
			/* END OF ACTION: declare_extern */
			ZRdeclaration_Hseq_Hopt ();
			switch (CURRENT_TERMINAL) {
			case 32:
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
	case 26: case 30:
		{
			ZRdeclaration_Hcond ();
			ZRdeclaration_Hseq_Hopt ();
			switch (CURRENT_TERMINAL) {
			case 32:
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
	case 1: case 2: case 4: case 65:
	case 78:
		{
			BASE_TYPE ZIbt;
			TYPE ZIt1;
			CV_SPEC ZIcv;
			DECL_SPEC ZIds1;
			TYPE ZI949;
			DECL_SPEC ZI950;
			TYPE ZIs;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2793 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2801 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 895 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2808 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1114 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2815 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1135 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZI950) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv) ) ;
    (ZI949) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv), 0 ) ;
    have_type_specifier = 0 ;
#line 2826 "syntax2.c"
			}
			/* END OF ACTION: dspec_complete */
			ZRdeclarator (ZI949, &ZIs, &ZIid);
			ZR822 (&ZIbt, &ZI949, &ZI950, &ZIs, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2840 "syntax2.c"
			}
			/* END OF ACTION: exp_none */
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1236 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2848 "syntax2.c"
			}
			/* END OF ACTION: declare_extern */
			ZRdeclaration_Hseq_Hopt ();
			switch (CURRENT_TERMINAL) {
			case 32:
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
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_fatal */
		{
#line 1340 "syntax.act"

    /* Unrecoverable syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    err = concat_error ( err, ERR_lex_abort () ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2879 "syntax2.c"
		}
		/* END OF ACTION: error_fatal */
	}
ZL0:;
}

void
ZR1058(TYPE *ZI1056, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 78: case 333:
		{
			TYPE ZIq;

			ZRabstract_Hdeclarator_Haux (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1050 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (*ZI1056) : inject_pre_type ( (ZIq), (*ZI1056), 0 ) ) ;
#line 2906 "syntax2.c"
			}
			/* END OF ACTION: type_build */
		}
		break;
	default:
		{
			ZIt = *ZI1056;
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
parse_offset(OFFSET ZIb, TYPE ZIs, OFFSET *ZOa, TYPE *ZOt)
{
	OFFSET ZIa;
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		OFFSET ZIc;
		TYPE ZIu;

		ZRmember_Hdesignator (ZIb, ZIs, &ZIc, &ZIu);
		/* BEGINNING OF INLINE: 842 */
		{
			switch (CURRENT_TERMINAL) {
			case 46: case 66:
				{
					ZRdesignator_Hlist (ZIc, ZIu, &ZIa, &ZIt);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					ZIa = ZIc;
					ZIt = ZIu;
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 842 */
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2977 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		ZIa = ZIb;
		ZIt = ZIs;
	}
ZL0:;
	*ZOa = ZIa;
	*ZOt = ZIt;
}

void
ZR1059(TYPE *ZO862)
{
	TYPE ZI862;

	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 78: case 333:
		{
			TYPE ZIt;

			ZRabstract_Hdeclarator_Haux (&ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1226 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 3010 "syntax2.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR863 (ZIt, &ZI862);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 25: case 39: case 47:
	case 94: case 97: case 98: case 102:
	case 104: case 105: case 106: case 110:
	case 111: case 112: case 114: case 115:
	case 117: case 118: case 120: case 121:
	case 122: case 123: case 124: case 137:
	case 156: case 185: case 286: case 299:
		{
			IDENTIFIER ZIid;
			TYPE ZIs;
			TYPE ZIt;

			/* BEGINNING OF ACTION: id_none */
			{
#line 383 "syntax.act"

    (ZIid) = NULL_id ;
#line 3044 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 3055 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZR758 (&ZIs);
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
			ZIt = ZIs;
			/* BEGINNING OF ACTION: param_end */
			{
#line 883 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 3077 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			ZR863 (ZIt, &ZI862);
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
	*ZO862 = ZI862;
}

void
parse_nat(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		ZRconstant_Hexpression (&ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 3126 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3134 "syntax2.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZRinitialiser_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		ZRassignment_Hexpression (&ZIe);
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
	*ZOe = ZIe;
}

void
parse_param(TYPE ZIs, int ZIp, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		ZRparameter_Hdeclaration (&ZId);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 3191 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: decl_none */
		{
#line 1240 "syntax.act"

    (ZId) = NULL_id ;
#line 3199 "syntax2.c"
		}
		/* END OF ACTION: decl_none */
	}
ZL0:;
	*ZOd = ZId;
}

void
ZRtype_Hspecifier_Hseq(BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZIb1;
		TYPE ZIt1;
		CV_SPEC ZIcv1;

		ZRtype_Hqualifier (&ZIb1, &ZIt1, &ZIcv1);
		/* BEGINNING OF INLINE: 694 */
		{
			switch (CURRENT_TERMINAL) {
			case 2: case 25: case 97: case 98:
			case 102: case 104: case 106: case 110:
			case 111: case 114: case 115: case 118:
			case 121: case 122: case 123: case 124:
			case 156: case 185: case 286: case 299:
				{
					BASE_TYPE ZIb2;
					TYPE ZIt2;
					CV_SPEC ZIcv2;

					ZRtype_Hspecifier_Hseq (&ZIb2, &ZIt2, &ZIcv2);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: btype_join */
					{
#line 929 "syntax.act"

    if ( (ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (ZIb1) | (ZIb2) ) ;
    }
#line 3250 "syntax2.c"
					}
					/* END OF ACTION: btype_join */
					/* BEGINNING OF ACTION: type_join */
					{
#line 975 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 3266 "syntax2.c"
					}
					/* END OF ACTION: type_join */
					/* BEGINNING OF ACTION: cv_join */
					{
#line 900 "syntax.act"

    CV_SPEC c = ( (ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIcv1) | (ZIcv2) ) ;
#line 3276 "syntax2.c"
					}
					/* END OF ACTION: cv_join */
				}
				break;
			default:
				{
					ZIbt = ZIb1;
					ZIt = ZIt1;
					ZIcv = ZIcv1;
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 694 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZR936(EXP ZI930, EXP ZI931, int ZI932, EXP *ZO933, EXP *ZO934, int *ZO935)
{
	EXP ZI933;
	EXP ZI934;
	int ZI935;

ZL2_936:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			int ZIr;
			EXP ZIc;
			int ZIs;
			EXP ZIb;
			EXP ZIe;

			ZIp = ZI931;
			ZIr = ZI932;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 318 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 3330 "syntax2.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1314 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 3340 "syntax2.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIs) = unreached_code ;
    if ( (ZIs) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3356 "syntax2.c"
			}
			/* END OF ACTION: reach_check */
			ZRcompound_Hstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 840 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 3368 "syntax2.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_hash_elif */
			{
#line 802 "syntax.act"

    (ZIe) = cont_hash_if_stmt ( (ZI930), (ZIc), (ZIb) ) ;
#line 3376 "syntax2.c"
			}
			/* END OF ACTION: stmt_hash_elif */
			/* BEGINNING OF INLINE: 936 */
			ZI930 = ZIe;
			ZI931 = ZIp;
			ZI932 = ZIr;
			goto ZL2_936;
			/* END OF INLINE: 936 */
		}
		UNREACHED;
	default:
		{
			ZI933 = ZI930;
			ZI934 = ZI931;
			ZI935 = ZI932;
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
	*ZO933 = ZI933;
	*ZO934 = ZI934;
	*ZO935 = ZI935;
}

void
parse_func(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		ZRfunction_Hbody (&ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 3433 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3441 "syntax2.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZRabstract_Hdeclarator_Haux(TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 333:
		{
			ZRdirect_Habstract_Hdeclarator (&ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			TYPE ZI1056;

			ZRptr_Hoperator (&ZI1056);
			ZR1058 (&ZI1056, &ZIt);
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
	*ZOt = ZIt;
}

void
ZRstorage_Hclass_Hspecifier(DECL_SPEC *ZOds)
{
	DECL_SPEC ZIds;

	switch (CURRENT_TERMINAL) {
	case 94:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_auto */
			{
#line 1115 "syntax.act"
 (ZIds) = dspec_auto ; 
#line 3502 "syntax2.c"
			}
			/* END OF ACTION: dspec_auto */
		}
		break;
	case 105:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_extern */
			{
#line 1118 "syntax.act"
 (ZIds) = dspec_extern ; 
#line 3514 "syntax2.c"
			}
			/* END OF ACTION: dspec_extern */
		}
		break;
	case 137:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_inline */
			{
#line 1120 "syntax.act"
 (ZIds) = dspec_inline ; 
#line 3526 "syntax2.c"
			}
			/* END OF ACTION: dspec_inline */
		}
		break;
	case 112:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_register */
			{
#line 1116 "syntax.act"
 (ZIds) = dspec_register ; 
#line 3538 "syntax2.c"
			}
			/* END OF ACTION: dspec_register */
		}
		break;
	case 117:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_static */
			{
#line 1117 "syntax.act"
 (ZIds) = dspec_static ; 
#line 3550 "syntax2.c"
			}
			/* END OF ACTION: dspec_static */
		}
		break;
	case 120:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_typedef */
			{
#line 1119 "syntax.act"
 (ZIds) = dspec_typedef ; 
#line 3562 "syntax2.c"
			}
			/* END OF ACTION: dspec_typedef */
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
	*ZOds = ZIds;
}

void
ZRparameter_Hid_Hlist(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZIid;

		/* BEGINNING OF INLINE: first-parameter-id */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3599 "syntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 208 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3612 "syntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: first-parameter-id */
		/* BEGINNING OF ACTION: declarator_begin */
		{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 3629 "syntax2.c"
		}
		/* END OF ACTION: declarator_begin */
		/* BEGINNING OF ACTION: declare_weak_param */
		{
#line 1190 "syntax.act"

    IGNORE weak_param_decl ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 3639 "syntax2.c"
		}
		/* END OF ACTION: declare_weak_param */
		ZRparameter_Hid_Htail ();
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
parse_id(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3673 "syntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 208 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3686 "syntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 200 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3699 "syntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: any-identifier */
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 3722 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: id_none */
		{
#line 383 "syntax.act"

    (ZIid) = NULL_id ;
#line 3730 "syntax2.c"
		}
		/* END OF ACTION: id_none */
	}
ZL0:;
	*ZOid = ZIid;
}

void
ZR686(IDENTIFIER *ZIp)
{
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 4:
		{
			ZRenumerator_Hlist (*ZIp);
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
ZRcast_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 369 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 3777 "syntax2.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 23:
		{
			EXP ZI965;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 332 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI965 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3799 "syntax2.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR925 (ZI965, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 206:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 509 "syntax.act"

    (ZIe) = make_cast_exp ( type_void, (ZIa), 0 ) ;
#line 3825 "syntax2.c"
			}
			/* END OF ACTION: exp_ignore */
		}
		break;
	case 210:
		{
			EXP ZI965;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 487 "syntax.act"

    (ZI965) = make_ellipsis_exp () ;
#line 3840 "syntax2.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR925 (ZI965, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1:
		{
			IDENTIFIER ZIid;
			EXP ZI965;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3860 "syntax2.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 505 "syntax.act"

    (ZI965) = make_id_exp ( (ZIid) ) ;
#line 3869 "syntax2.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR925 (ZI965, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 255:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 521 "syntax.act"

    (ZIe) = make_lit_exp ( (ZIa) ) ;
#line 3894 "syntax2.c"
			}
			/* END OF ACTION: exp_lit */
		}
		break;
	case 61:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 582 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_minus_Hminus, (ZIa) ) ;
#line 3914 "syntax2.c"
			}
			/* END OF ACTION: exp_predec */
		}
		break;
	case 65:
		{
			ADVANCE_LEXER;
			ZR966 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 71:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 586 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_plus_Hplus, (ZIa) ) ;
#line 3944 "syntax2.c"
			}
			/* END OF ACTION: exp_preinc */
		}
		break;
	case 116:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 370 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 3958 "syntax2.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 517 "syntax.act"

    (ZIe) = make_indir_exp ( (ZIa) ) ;
#line 3983 "syntax2.c"
			}
			/* END OF ACTION: exp_indir */
		}
		break;
	case 33:
		{
			EXP ZIa;

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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 590 "syntax.act"

    (ZIe) = make_ref_exp ( (ZIa), 0 ) ;
#line 4015 "syntax2.c"
			}
			/* END OF ACTION: exp_ref */
		}
		break;
	case 17: case 18: case 19: case 20:
	case 21: case 22:
		{
			EXP ZI965;

			ZRliteral (&ZI965);
			ZR925 (ZI965, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 62:
		{
			EXP ZIa;

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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 553 "syntax.act"

    (ZIe) = make_not_exp ( (ZIa) ) ;
#line 4060 "syntax2.c"
			}
			/* END OF ACTION: exp_not */
		}
		break;
	case 43: case 59: case 69: case 85:
		{
			int ZIop;
			EXP ZIa;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 366 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 4074 "syntax2.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 615 "syntax.act"

    (ZIe) = make_uminus_exp ( (ZIop), (ZIa) ) ;
#line 4088 "syntax2.c"
			}
			/* END OF ACTION: exp_unary */
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
ZRtype_Hspecifier(BASE_TYPE *ZObt, TYPE *ZOt)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 25:
		{
			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 346 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIt = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 4125 "syntax2.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4133 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
		}
		break;
	case 2:
		{
			IDENTIFIER ZIid;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 200 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4147 "syntax2.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_name */
			{
#line 959 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 4158 "syntax2.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4165 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
		}
		break;
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 122:
	case 123: case 156: case 185: case 286:
	case 299:
		{
			ZRbase_Htype_Hspecifier (&ZIbt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_pre */
			{
#line 954 "syntax.act"

    (ZIt) = NULL_type ;
    have_type_specifier = 1 ;
#line 4186 "syntax2.c"
			}
			/* END OF ACTION: type_pre */
		}
		break;
	case 118: case 121:
		{
			ZRclass_Hspecifier (&ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4202 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
		}
		break;
	case 104:
		{
			ZRenum_Hspecifier (&ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4218 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
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
	*ZObt = ZIbt;
	*ZOt = ZIt;
}

void
ZRabstract_Hdeclarator_Hopt(TYPE ZIp, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 78: case 333:
		{
			TYPE ZIq;

			ZRabstract_Hdeclarator_Haux (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 4257 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	default:
		{
			ZIt = ZIp;
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
ZRopen_Hround_Hx(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 65:
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

		/* BEGINNING OF ACTION: lex_open_round */
		{
#line 367 "syntax.act"
 (ZIt) = lex_open_Hround ; 
#line 4302 "syntax2.c"
		}
		/* END OF ACTION: lex_open_round */
		/* BEGINNING OF ACTION: expected */
		{
#line 1357 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 4312 "syntax2.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZR1070(int *ZIop, int *ZIn1, int *ZIm1, EXP *ZOc)
{
	EXP ZIc;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIt;
		int ZIm2;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_type_id_true */
		{
#line 1441 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
#line 4337 "syntax2.c"
		}
		/* END OF ACTION: is_type_id_true */
		if (!ZI0)
			goto ZL2;
		ZRtype_Hid (&ZIt, &ZIm2);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 432 "syntax.act"

    (ZIa) = NULL_exp ;
#line 4352 "syntax2.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: exp_sizeof */
		{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (*ZIop) ) ;
#line 4360 "syntax2.c"
		}
		/* END OF ACTION: exp_sizeof */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255: case 298:
	case 324: case 347:
		{
			EXP ZI1069;
			EXP ZIe;
			EXP ZIa;
			int ZIn2;
			int ZIm2;
			TYPE ZIt;

			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 562 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 4395 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZI1069);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 565 "syntax.act"

    (ZIe) = make_paren_exp ( (ZI1069) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 4409 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR925 (ZIe, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: diff_side_effects */
			{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (*ZIn1) ;
#line 4429 "syntax2.c"
			}
			/* END OF ACTION: diff_side_effects */
			/* BEGINNING OF ACTION: diff_type_defns */
			{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (*ZIm1) ;
#line 4437 "syntax2.c"
			}
			/* END OF ACTION: diff_type_defns */
			/* BEGINNING OF ACTION: type_of */
			{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (*ZIop) ) ;
#line 4445 "syntax2.c"
			}
			/* END OF ACTION: type_of */
			/* BEGINNING OF ACTION: exp_sizeof */
			{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (*ZIop) ) ;
#line 4453 "syntax2.c"
			}
			/* END OF ACTION: exp_sizeof */
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
	*ZOc = ZIc;
}

void
ZR816(BASE_TYPE *ZIbt, TYPE *ZIt1, CV_SPEC *ZIcv, DECL_SPEC *ZIds1)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: declare_id_empty */
			{
#line 1173 "syntax.act"

    IGNORE empty_decl ( (*ZIds1), NULL_type, (*ZIbt), (*ZIt1), (*ZIcv), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 4483 "syntax2.c"
			}
			/* END OF ACTION: declare_id_empty */
		}
		break;
	case 1: case 2: case 4: case 65:
	case 78:
		{
			TYPE ZIt;
			DECL_SPEC ZIds;

			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1135 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds) = complete_dspec ( (*ZIds1), (*ZIbt), (*ZIt1), (*ZIcv) ) ;
    (ZIt) = complete_pre_type ( (*ZIbt), (*ZIt1), (*ZIcv), 0 ) ;
    have_type_specifier = 0 ;
#line 4502 "syntax2.c"
			}
			/* END OF ACTION: dspec_complete */
			ZRinit_Hdeclarator_Hlist (ZIds, *ZIbt, ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 356:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRenumerator_Hlist(IDENTIFIER ZIe)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_enumerator_Hlist:;
	{
		ZRenumerator_Hdefinition (ZIe);
		/* BEGINNING OF INLINE: 684 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 1055 */
					{
						switch (CURRENT_TERMINAL) {
						case 42:
							{
								ADVANCE_LEXER;
								/* BEGINNING OF ACTION: error_comma */
								{
#line 1352 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 4548 "syntax2.c"
								}
								/* END OF ACTION: error_comma */
								/* BEGINNING OF INLINE: enumerator-list */
								goto ZL2_enumerator_Hlist;
								/* END OF INLINE: enumerator-list */
							}
							UNREACHED;
						case 1: case 2: case 4:
							{
								/* BEGINNING OF INLINE: enumerator-list */
								goto ZL2_enumerator_Hlist;
								/* END OF INLINE: enumerator-list */
							}
							UNREACHED;
						default:
							{
								/* BEGINNING OF ACTION: error_comma */
								{
#line 1352 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 4571 "syntax2.c"
								}
								/* END OF ACTION: error_comma */
							}
							break;
						}
					}
					/* END OF INLINE: 1055 */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 684 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRfor_Hinit_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		ZRexpression_Hstatement (&ZIe);
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
	*ZOe = ZIe;
}

void
ZRdesignator(OFFSET ZIb, TYPE ZIs, OFFSET *ZOa, TYPE *ZOt)
{
	OFFSET ZIa;
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 46:
		{
			ADVANCE_LEXER;
			ZRmember_Hdesignator (ZIb, ZIs, &ZIa, &ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
			EXP ZIe;

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
			ZRconstant_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: offset_index */
			{
#line 1275 "syntax.act"

    OFFSET off = offset_index ( (ZIs), (ZIe), &(ZIt) ) ;
    (ZIa) = offset_add ( (ZIb), off ) ;
#line 4664 "syntax2.c"
			}
			/* END OF ACTION: offset_index */
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
	*ZOa = ZIa;
	*ZOt = ZIt;
}

void
ZRunary_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 369 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 4711 "syntax2.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 61:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 582 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_minus_Hminus, (ZIa) ) ;
#line 4736 "syntax2.c"
			}
			/* END OF ACTION: exp_predec */
		}
		break;
	case 71:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 586 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_plus_Hplus, (ZIa) ) ;
#line 4756 "syntax2.c"
			}
			/* END OF ACTION: exp_preinc */
		}
		break;
	case 116:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 370 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 4770 "syntax2.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 517 "syntax.act"

    (ZIe) = make_indir_exp ( (ZIa) ) ;
#line 4795 "syntax2.c"
			}
			/* END OF ACTION: exp_indir */
		}
		break;
	case 33:
		{
			EXP ZIa;

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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 590 "syntax.act"

    (ZIe) = make_ref_exp ( (ZIa), 0 ) ;
#line 4827 "syntax2.c"
			}
			/* END OF ACTION: exp_ref */
		}
		break;
	case 62:
		{
			EXP ZIa;

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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 553 "syntax.act"

    (ZIe) = make_not_exp ( (ZIa) ) ;
#line 4859 "syntax2.c"
			}
			/* END OF ACTION: exp_not */
		}
		break;
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 65: case 210:
		{
			ZRpostfix_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 43: case 59: case 69: case 85:
		{
			int ZIop;
			EXP ZIa;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 366 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 4884 "syntax2.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 615 "syntax.act"

    (ZIe) = make_uminus_exp ( (ZIop), (ZIa) ) ;
#line 4898 "syntax2.c"
			}
			/* END OF ACTION: exp_unary */
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
ZRrelational_Hexpression(EXP *ZO908)
{
	EXP ZI908;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRshift_Hexpression (&ZIe);
		ZR909 (ZIe, &ZI908);
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
	*ZO908 = ZI908;
}

void
ZRfor_Hend_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255: case 298:
	case 324: case 347:
		{
			EXP ZIa;
			EXP ZIb;

			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIb) = make_exp_stmt ( (ZIa) ) ;
#line 4969 "syntax2.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 818 "syntax.act"

    (ZIe) = bind_temporary ( (ZIb) ) ;
#line 4977 "syntax2.c"
			}
			/* END OF ACTION: bind_temporary */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_none */
			{
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 4989 "syntax2.c"
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

/* END OF FILE */
