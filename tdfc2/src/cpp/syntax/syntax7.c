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


#line 98 "syntax7.c"

void
ZRfunction_Hspecifier(DECL_SPEC *ZOds)
{
	DECL_SPEC ZIds;

	switch (CURRENT_TERMINAL) {
	case 133:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_explicit */
			{
#line 1538 "syntax.act"
 (ZIds) = dspec_explicit ; 
#line 113 "syntax7.c"
			}
			/* END OF ACTION: dspec_explicit */
		}
		break;
	case 137:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_inline */
			{
#line 1536 "syntax.act"
 (ZIds) = dspec_inline ; 
#line 125 "syntax7.c"
			}
			/* END OF ACTION: dspec_inline */
		}
		break;
	case 275:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_overload */
			{
#line 1539 "syntax.act"
 (ZIds) = dspec_none ; 
#line 137 "syntax7.c"
			}
			/* END OF ACTION: dspec_overload */
		}
		break;
	case 155:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_virtual */
			{
#line 1537 "syntax.act"
 (ZIds) = dspec_virtual ; 
#line 149 "syntax7.c"
			}
			/* END OF ACTION: dspec_virtual */
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
ZR1235(EXP ZI1233, EXP *ZO1234)
{
	EXP ZI1234;

ZL2_1235:;
	switch (CURRENT_TERMINAL) {
	case 44:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRpm_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_div */
			{
#line 622 "syntax.act"

    (ZIe) = make_mult_exp ( lex_div, (ZI1233), (ZIb) ) ;
#line 190 "syntax7.c"
			}
			/* END OF ACTION: exp_div */
			/* BEGINNING OF INLINE: 1235 */
			ZI1233 = ZIe;
			goto ZL2_1235;
			/* END OF INLINE: 1235 */
		}
		UNREACHED;
	case 73:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRpm_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_rem */
			{
#line 797 "syntax.act"

    (ZIe) = make_rem_exp ( (ZI1233), (ZIb) ) ;
#line 215 "syntax7.c"
			}
			/* END OF ACTION: exp_rem */
			/* BEGINNING OF INLINE: 1235 */
			ZI1233 = ZIe;
			goto ZL2_1235;
			/* END OF INLINE: 1235 */
		}
		UNREACHED;
	case 78:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRpm_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_mult */
			{
#line 718 "syntax.act"

    (ZIe) = make_mult_exp ( lex_star, (ZI1233), (ZIb) ) ;
#line 240 "syntax7.c"
			}
			/* END OF ACTION: exp_mult */
			/* BEGINNING OF INLINE: 1235 */
			ZI1233 = ZIe;
			goto ZL2_1235;
			/* END OF INLINE: 1235 */
		}
		UNREACHED;
	default:
		{
			ZI1234 = ZI1233;
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
	*ZO1234 = ZI1234;
}

void
ZRstatement(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2070 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 286 "syntax7.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 295 "syntax7.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 303 "syntax7.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 915 "syntax.act"

    (ZIe) = (ZIa) ;
    in_declaration-- ;
#line 317 "syntax7.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 325 "syntax7.c"
		}
		/* END OF ACTION: stmt_label_clear */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 382 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 358 "syntax7.c"
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
#line 393 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 401 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 409 "syntax7.c"
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
	case 83:
		{
			ADVANCE_LEXER;
			ZR1478 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 341 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1282 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 459 "syntax7.c"
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
#line 495 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 503 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 511 "syntax7.c"
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
	case 24:
		{
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-stmt */
			{
#line 348 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIa = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 535 "syntax7.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 544 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 355 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1268 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 584 "syntax7.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 592 "syntax7.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 599 "syntax7.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 608 "syntax7.c"
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
#line 634 "syntax7.c"
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
#line 669 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 677 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 685 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 732 "syntax7.c"
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
#line 767 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 775 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 783 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 219 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 822 "syntax7.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 833 "syntax7.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 841 "syntax7.c"
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
#line 876 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 884 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 892 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 935 "syntax7.c"
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
#line 969 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 977 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 985 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 1032 "syntax7.c"
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
#line 1067 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1075 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1083 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 644 "syntax.act"

    (ZI1280) = make_ellipsis_exp () ;
#line 1121 "syntax7.c"
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
#line 1156 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1164 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1172 "syntax7.c"
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
	case 9:
		{
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1193 "syntax7.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1477 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1:
		{
			IDENTIFIER ZI1468;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 203 "syntax.act"

    ZI1468 = crt_token->pp_data.id.use ;
#line 1213 "syntax7.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1473 (&ZI1468, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 347:
		{
			ADVANCE_LEXER;
			ZR1442 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
			EXP ZIa;
			int ZIr;

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
#line 1265 "syntax7.c"
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
#line 1299 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1307 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1315 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 1358 "syntax7.c"
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
#line 1392 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1400 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1408 "syntax7.c"
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
	case 3:
		{
			IDENTIFIER ZI1472;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 211 "syntax.act"

    ZI1472 = crt_token->pp_data.id.use ;
#line 1429 "syntax7.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			ZR1473 (&ZI1472, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1449 "syntax7.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1476 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
			EXP ZIa;
			int ZIr;

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
#line 1512 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1520 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1528 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 1571 "syntax7.c"
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
#line 1605 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1613 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1621 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 1668 "syntax7.c"
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
#line 1703 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1711 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1719 "syntax7.c"
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
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_none */
			{
#line 863 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1739 "syntax7.c"
			}
			/* END OF ACTION: stmt_none */
		}
		break;
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 389 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 1769 "syntax7.c"
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
#line 1804 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1812 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1820 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 1863 "syntax7.c"
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
#line 1897 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1905 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 1913 "syntax7.c"
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
	case 4:
		{
			IDENTIFIER ZI1474;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZI1474 = crt_token->pp_data.id.use ;
#line 1934 "syntax7.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1475 (&ZI1474, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
			EXP ZIa;
			int ZIr;

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
#line 1979 "syntax7.c"
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
#line 2014 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2022 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2030 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 225 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 2073 "syntax7.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2084 "syntax7.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 2092 "syntax7.c"
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
#line 2127 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2135 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2143 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 2191 "syntax7.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2202 "syntax7.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 2212 "syntax7.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2219 "syntax7.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2226 "syntax7.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2235 "syntax7.c"
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
#line 2261 "syntax7.c"
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
#line 2296 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2304 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2312 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 817 "syntax.act"

    (ZI1279) = make_this_exp () ;
#line 2350 "syntax7.c"
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
#line 2385 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2393 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2401 "syntax7.c"
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
	case 2:
		{
			IDENTIFIER ZI1470;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 207 "syntax.act"

    ZI1470 = crt_token->pp_data.id.use ;
#line 2422 "syntax7.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			ZR1471 (&ZI1470, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 390 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 2459 "syntax7.c"
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
#line 2495 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2503 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2511 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 391 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 2549 "syntax7.c"
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
#line 2585 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2593 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2601 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 2656 "syntax7.c"
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
#line 2690 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2698 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2706 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 2757 "syntax7.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2764 "syntax7.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2773 "syntax7.c"
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
#line 2799 "syntax7.c"
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
#line 2834 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2842 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2850 "syntax7.c"
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
	case 64:
		{
			ZRcompound_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 289: case 323:
		{
			ZRcontrol_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 96: case 100: case 223:
		{
			ZRfall_Hcheck ();
			ZR1443 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 298: case 324:
		{
			EXP ZI1437;
			EXP ZIa;
			int ZIr;

			ZRflow_Hexpression (&ZI1437);
			ZR1439 (&ZI1437, &ZIa);
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
#line 2915 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2923 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 2931 "syntax7.c"
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
	case 101: case 107: case 125:
		{
			ZRiteration_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 95: case 99: case 108: case 113:
		{
			ZRjump_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
			EXP ZIa;
			int ZIr;

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
#line 3015 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3023 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3031 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 3086 "syntax7.c"
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
#line 3120 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3128 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3136 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

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
#line 3182 "syntax7.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 3190 "syntax7.c"
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
#line 3225 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3233 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3241 "syntax7.c"
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
	case 26: case 109: case 119:
		{
			ZRselection_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 149:
		{
			EXP ZI1290;
			EXP ZIa;
			int ZIr;

			ZRthrow_Hexpression (&ZI1290);
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
#line 3287 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3295 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3303 "syntax7.c"
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
	case 151:
		{
			ZRtry_Hblock (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 131: case 140:
		{
			int ZIb;
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

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIb) = 0 ; 
#line 3348 "syntax7.c"
			}
			/* END OF ACTION: bool_false */
			ZR1433 (&ZIb, &ZI1455);
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
#line 3383 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3391 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3399 "syntax7.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 3436 "syntax7.c"
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
#line 3450 "syntax7.c"
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
#line 3484 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3492 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3500 "syntax7.c"
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
ZRdirect_Habstract_Hdeclarator(TYPE *ZO1141)
{
	TYPE ZI1141;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			ZR1386 (&ZI1141);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 333:
		{
			IDENTIFIER ZIid;
			int ZIw;
			TYPE ZIt;

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
#line 445 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 3560 "syntax7.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIw) = 1 ; 
#line 3567 "syntax7.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 3578 "syntax7.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: param_end */
			{
#line 1194 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 3593 "syntax7.c"
			}
			/* END OF ACTION: param_end */
			ZR1142 (ZIt, &ZI1141);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
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
			ZR956 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1357 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 3632 "syntax7.c"
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
			ZR1142 (ZIt, &ZI1141);
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
	*ZO1141 = ZI1141;
}

void
ZRhandler_Hseq_Hopt(EXP ZIa)
{
ZL2_handler_Hseq_Hopt:;
	switch (CURRENT_TERMINAL) {
	case 128:
		{
			ZRhandler (ZIa);
			/* BEGINNING OF INLINE: handler-seq-opt */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_handler_Hseq_Hopt;
			}
			/* END OF INLINE: handler-seq-opt */
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
ZR1239(EXP ZI1237, EXP *ZO1238)
{
	EXP ZI1238;

ZL2_1239:;
	switch (CURRENT_TERMINAL) {
	case 82:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ptr_mem */
			{
#line 780 "syntax.act"

    in_ptr_mem_selector++ ;
#line 3715 "syntax7.c"
			}
			/* END OF ACTION: exp_ptr_mem */
			ZRcast_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_arrow_star */
			{
#line 586 "syntax.act"

    (ZIe) = make_member_exp ( lex_arrow_Hstar, (ZI1237), (ZIb) ) ;
    in_ptr_mem_selector-- ;
#line 3729 "syntax7.c"
			}
			/* END OF ACTION: exp_arrow_star */
			/* BEGINNING OF INLINE: 1239 */
			ZI1237 = ZIe;
			goto ZL2_1239;
			/* END OF INLINE: 1239 */
		}
		UNREACHED;
	case 84:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ptr_mem */
			{
#line 780 "syntax.act"

    in_ptr_mem_selector++ ;
#line 3749 "syntax7.c"
			}
			/* END OF ACTION: exp_ptr_mem */
			ZRcast_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dot_star */
			{
#line 634 "syntax.act"

    (ZIe) = make_member_exp ( lex_dot_Hstar, (ZI1237), (ZIb) ) ;
    in_ptr_mem_selector-- ;
#line 3763 "syntax7.c"
			}
			/* END OF ACTION: exp_dot_star */
			/* BEGINNING OF INLINE: 1239 */
			ZI1237 = ZIe;
			goto ZL2_1239;
			/* END OF INLINE: 1239 */
		}
		UNREACHED;
	default:
		{
			ZI1238 = ZI1237;
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
	*ZO1238 = ZI1238;
}

void
ZRiteration_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 101:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIa;
			EXP ZIbs;
			EXP ZIb;
			EXP ZIc0;
			EXP ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 1122 "syntax.act"
 (ZIx) = crt_condition ; 
#line 3809 "syntax7.c"
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
#line 3825 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_do_begin */
			{
#line 928 "syntax.act"

    (ZIa) = begin_do_stmt () ;
#line 3833 "syntax7.c"
			}
			/* END OF ACTION: stmt_do_begin */
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 891 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 3841 "syntax7.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRscoped_Hstatement (ZIbs, &ZIb);
			switch (CURRENT_TERMINAL) {
			case 125:
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
			ZRexpression (&ZIc0);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 1071 "syntax.act"

    (ZIc) = bind_temporary ( (ZIc0) ) ;
#line 3872 "syntax7.c"
			}
			/* END OF ACTION: bind_temporary */
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 3879 "syntax7.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_do_end */
			{
#line 932 "syntax.act"

    (ZIe) = end_do_stmt ( (ZIa), (ZIb), (ZIc) ) ;
#line 3887 "syntax7.c"
			}
			/* END OF ACTION: stmt_do_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_set */
			{
#line 1123 "syntax.act"
 crt_condition = (ZIx) ; 
#line 3901 "syntax7.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3909 "syntax7.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 107:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIf;
			EXP ZIa;
			EXP ZIg;
			EXP ZIc;
			EXP ZIcp;
			EXP ZIds;
			EXP ZIb;
			EXP ZIh;
			EXP ZIda;
			EXP ZIdc;
			EXP ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 1122 "syntax.act"
 (ZIx) = crt_condition ; 
#line 3940 "syntax7.c"
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
#line 3956 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_for_begin */
			{
#line 940 "syntax.act"

    (ZIf) = begin_for_stmt () ;
#line 3971 "syntax7.c"
			}
			/* END OF ACTION: stmt_for_begin */
			ZRfor_Hinit_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_for_init */
			{
#line 944 "syntax.act"

    (ZIg) = init_for_stmt ( (ZIf), &(ZIa) ) ;
#line 3984 "syntax7.c"
			}
			/* END OF ACTION: stmt_for_init */
			ZRfor_Hcond_Hstatement (&ZIc, &ZIcp);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 891 "syntax.act"

    (ZIds) = begin_compound_stmt ( 1 ) ;
#line 3997 "syntax7.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRfor_Hend_Hstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_for_cond */
			{
#line 948 "syntax.act"

    (ZIh) = cond_for_stmt ( (ZIg), (ZIcp), (ZIb) ) ;
#line 4010 "syntax7.c"
			}
			/* END OF ACTION: stmt_for_cond */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: init_inject */
			{
#line 1096 "syntax.act"

    (ZIda) = inject_cond ( (ZIds), (ZIa) ) ;
#line 4025 "syntax7.c"
			}
			/* END OF ACTION: init_inject */
			/* BEGINNING OF ACTION: loop_inject */
			{
#line 1092 "syntax.act"

    (ZIdc) = inject_cond ( (ZIda), (ZIc) ) ;
#line 4033 "syntax7.c"
			}
			/* END OF ACTION: loop_inject */
			/* BEGINNING OF ACTION: stmt_compound_mark */
			{
#line 899 "syntax.act"

    mark_compound_stmt ( (ZIdc) ) ;
#line 4041 "syntax7.c"
			}
			/* END OF ACTION: stmt_compound_mark */
			ZRscoped_Hstatement (ZIdc, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4053 "syntax7.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_for_end */
			{
#line 952 "syntax.act"

    (ZIe) = end_for_stmt ( (ZIh), (ZId) ) ;
#line 4061 "syntax7.c"
			}
			/* END OF ACTION: stmt_for_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 1123 "syntax.act"
 crt_condition = (ZIx) ; 
#line 4068 "syntax7.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4076 "syntax7.c"
			}
			/* END OF ACTION: stmt_label_clear */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4084 "syntax7.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 125:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIc0;
			EXP ZIc;
			EXP ZIa;
			EXP ZIbs;
			EXP ZIbc;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 1122 "syntax.act"
 (ZIx) = crt_condition ; 
#line 4105 "syntax7.c"
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
#line 4121 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcondition (&ZIc0);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 1071 "syntax.act"

    (ZIc) = bind_temporary ( (ZIc0) ) ;
#line 4141 "syntax7.c"
			}
			/* END OF ACTION: bind_temporary */
			/* BEGINNING OF ACTION: stmt_while_begin */
			{
#line 1043 "syntax.act"

    (ZIa) = begin_while_stmt ( (ZIc) ) ;
#line 4149 "syntax7.c"
			}
			/* END OF ACTION: stmt_while_begin */
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
#line 4164 "syntax7.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			/* BEGINNING OF ACTION: loop_inject */
			{
#line 1092 "syntax.act"

    (ZIbc) = inject_cond ( (ZIbs), (ZIc) ) ;
#line 4172 "syntax7.c"
			}
			/* END OF ACTION: loop_inject */
			ZRscoped_Hstatement (ZIbc, &ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4184 "syntax7.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_while_end */
			{
#line 1047 "syntax.act"

    (ZIe) = end_while_stmt ( (ZIa), (ZIb) ) ;
#line 4192 "syntax7.c"
			}
			/* END OF ACTION: stmt_while_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 1123 "syntax.act"
 crt_condition = (ZIx) ; 
#line 4199 "syntax7.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4207 "syntax7.c"
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
ZRassignment_Hoperator(void)
{
	switch (CURRENT_TERMINAL) {
	case 45:
		{
			ADVANCE_LEXER;
		}
		break;
	case 58:
		{
			ADVANCE_LEXER;
		}
		break;
	case 60:
		{
			ADVANCE_LEXER;
		}
		break;
	case 70:
		{
			ADVANCE_LEXER;
		}
		break;
	case 74:
		{
			ADVANCE_LEXER;
		}
		break;
	case 76:
		{
			ADVANCE_LEXER;
		}
		break;
	case 79:
		{
			ADVANCE_LEXER;
		}
		break;
	case 34:
		{
			/* BEGINNING OF INLINE: and-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 34:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: and-eq */
		}
		break;
	case 68:
		{
			/* BEGINNING OF INLINE: or-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 68:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or-eq */
		}
		break;
	case 81:
		{
			/* BEGINNING OF INLINE: xor-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 81:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: xor-eq */
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
ZR1368(DECL_SPEC *ZIds, TYPE *ZIp, BASE_TYPE *ZIq, ACCESS_LIST *ZIr, int *ZIf, IDENTIFIER *ZI1367, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	switch (CURRENT_TERMINAL) {
	case 41:
		{
			QUALIFIER ZIi;
			int ZIb;
			EXP ZIc;
			TYPE ZIt;

			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (*ZIp) ) ) template_decl ( (*ZIp) ) ;
#line 4344 "syntax7.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (*ZI1367), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4352 "syntax7.c"
			}
			/* END OF ACTION: declarator_begin */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 4361 "syntax7.c"
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
#line 4376 "syntax7.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_bitfield_mem */
			{
#line 1373 "syntax.act"

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1367) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZIt) = make_bitfield_type ( (*ZIp), (*ZIq), (ZIc), z ) ;
#line 4387 "syntax7.c"
			}
			/* END OF ACTION: type_bitfield_mem */
			/* BEGINNING OF ACTION: declare_bitfield */
			{
#line 1664 "syntax.act"

    IDENTIFIER id = make_member_decl ( (*ZIds), (ZIt), (*ZI1367), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZId) = id ;
#line 4401 "syntax7.c"
			}
			/* END OF ACTION: declare_bitfield */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(*ZIr) ) ;
#line 4409 "syntax7.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4419 "syntax7.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
	default:
		{
			TYPE ZI1357;
			int ZI1358;
			TYPE ZI1350;
			IDENTIFIER ZIid;
			int ZIc;
			TYPE ZIt;
			int ZIfr;
			EXP ZIe;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 4440 "syntax7.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 4447 "syntax7.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (*ZI1367), crt_id_qualifier, qual_namespace, 1 ) ;
#line 4455 "syntax7.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR1180 (ZI1357, *ZI1367, ZI1358, &ZI1350, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_decl */
			{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (*ZIp) ) ) template_decl ( (*ZIp) ) ;
#line 4468 "syntax7.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (*ZIp) : inject_pre_type ( (ZI1350), (*ZIp), 1 ) ) ;
#line 4476 "syntax7.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 4484 "syntax7.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1628 "syntax.act"

    DECL_SPEC ds = (*ZIds) ;
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
	int f = ( (*ZIf) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZId) = make_member_decl ( ds, (ZIt), (ZIid), f ) ;
	(ZIfr) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (*ZIq) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4517 "syntax7.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(*ZIr) ) ;
#line 4525 "syntax7.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4535 "syntax7.c"
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
#line 4549 "syntax7.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 4559 "syntax7.c"
			}
			/* END OF ACTION: access_check_decl */
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
	*ZOd = ZId;
}

void
ZRexpression_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 347:
		{
			ADVANCE_LEXER;
			ZR1442 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_none */
			{
#line 863 "syntax.act"

    (ZIe) = NULL_exp ;
#line 4599 "syntax7.c"
			}
			/* END OF ACTION: stmt_none */
		}
		break;
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
			EXP ZIa;
			int ZIr;

			ZRassignment_Hexpression (&ZI1290);
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
#line 4643 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4651 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4659 "syntax7.c"
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
	case 298: case 324:
		{
			EXP ZI1437;
			EXP ZIa;
			int ZIr;

			ZRflow_Hexpression (&ZI1437);
			ZR1439 (&ZI1437, &ZIa);
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
#line 4696 "syntax7.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4704 "syntax7.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4712 "syntax7.c"
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
ZRdeclaration_Hother(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 139:
		{
			ADVANCE_LEXER;
			ZR1261 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 154:
		{
			ADVANCE_LEXER;
			ZR1262 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 126:
		{
			ZRasm_Hdefinition (&ZIe);
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
ZRmember_Hdesignator(OFFSET ZIb, TYPE ZIs, OFFSET *ZOa, TYPE *ZOt)
{
	OFFSET ZIa;
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		NAMESPACE ZIns;
		IDENTIFIER ZIid;

		/* BEGINNING OF ACTION: offset_nspace */
		{
#line 1861 "syntax.act"

    (ZIns) = offset_nspace ( (ZIs) ) ;
#line 4803 "syntax7.c"
		}
		/* END OF ACTION: offset_nspace */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4811 "syntax7.c"
		}
		/* END OF ACTION: rescan_token */
		ZRfield_Hid_Hexpression (ZIns, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: offset_member */
		{
#line 1865 "syntax.act"

    OFFSET off = offset_member ( (ZIs), (ZIid), &(ZIt), (ZIns), 1 ) ;
    (ZIa) = offset_add ( (ZIb), off ) ;
#line 4825 "syntax7.c"
		}
		/* END OF ACTION: offset_member */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4833 "syntax7.c"
		}
		/* END OF ACTION: rescan_token */
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
ZRany_Hclass_Hname(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 7:
		{
			/* BEGINNING OF EXTRACT: template-type */
			{
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 4863 "syntax7.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
		}
		break;
	case 1: case 2: case 3: case 4:
		{
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 203 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4881 "syntax7.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 211 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4894 "syntax7.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 215 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4907 "syntax7.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 207 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4920 "syntax7.c"
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
ZRhandler(EXP ZIa)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIc;
		int ZIn;
		IDENTIFIER ZId;
		EXP ZIb;
		EXP ZIe0;
		EXP ZIe1;
		EXP ZIc1;
		EXP ZIe2;
		EXP ZIc2;
		EXP ZIc3;
		EXP ZIc4;

		switch (CURRENT_TERMINAL) {
		case 128:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 891 "syntax.act"

    (ZIc) = begin_compound_stmt ( 1 ) ;
#line 4977 "syntax7.c"
		}
		/* END OF ACTION: stmt_compound_begin */
		/* BEGINNING OF ACTION: stmt_try_inject */
		{
#line 1031 "syntax.act"

    inject_try_stmt ( (ZIa) ) ;
#line 4985 "syntax7.c"
		}
		/* END OF ACTION: stmt_try_inject */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2000 "syntax.act"

    (ZIn) = no_type_defns ;
#line 4993 "syntax7.c"
		}
		/* END OF ACTION: no_type_defns */
		switch (CURRENT_TERMINAL) {
		case 65:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRexception_Hdeclaration (ZIn, &ZId);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_catch_begin */
		{
#line 879 "syntax.act"

    (ZIb) = begin_catch_stmt ( (ZIa), (ZId) ) ;
#line 5013 "syntax7.c"
		}
		/* END OF ACTION: stmt_catch_begin */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
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
		/* BEGINNING OF ACTION: stmt_compound_block */
		{
#line 895 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
#line 5041 "syntax7.c"
		}
		/* END OF ACTION: stmt_compound_block */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 565 "syntax.act"

    (ZIe0) = NULL_exp ;
#line 5049 "syntax7.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 915 "syntax.act"

    (ZIe1) = (ZIe0) ;
    in_declaration-- ;
#line 5058 "syntax7.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 903 "syntax.act"

    (ZIc1) = add_compound_stmt ( (ZIc), (ZIe1) ) ;
#line 5066 "syntax7.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF ACTION: stmt_caught */
		{
#line 887 "syntax.act"

    MAKE_exp_thrown ( type_void, 1, (ZIe2) ) ;
#line 5074 "syntax7.c"
		}
		/* END OF ACTION: stmt_caught */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 903 "syntax.act"

    (ZIc2) = add_compound_stmt ( (ZIc1), (ZIe2) ) ;
#line 5082 "syntax7.c"
		}
		/* END OF ACTION: stmt_compound_add */
		ZRstatement_Hseq_Hopt (ZIc2, &ZIc3);
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
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 907 "syntax.act"

    (ZIc4) = end_compound_stmt ( (ZIc3) ) ;
#line 5108 "syntax7.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: stmt_catch_end */
		{
#line 883 "syntax.act"

    IGNORE end_catch_stmt ( (ZIb), (ZIc4) ) ;
#line 5116 "syntax7.c"
		}
		/* END OF ACTION: stmt_catch_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5124 "syntax7.c"
		}
		/* END OF ACTION: rescan_token */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

/* END OF FILE */
