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


#line 98 "syntax4.c"

void
ZR1195(EXP ZI1193, EXP *ZO1194)
{
	EXP ZI1194;

ZL2_1195:;
	switch (CURRENT_TERMINAL) {
	case 56:
		{
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF INLINE: logical-or */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 56:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: logical-or */
			ZRlogical_Hand_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_log_or */
			{
#line 702 "syntax.act"

    (ZIe) = make_log_or_exp ( (ZI1193), (ZIb) ) ;
#line 135 "syntax4.c"
			}
			/* END OF ACTION: exp_log_or */
			/* BEGINNING OF INLINE: 1195 */
			ZI1193 = ZIe;
			goto ZL2_1195;
			/* END OF INLINE: 1195 */
		}
		UNREACHED;
	default:
		{
			ZI1194 = ZI1193;
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
	*ZO1194 = ZI1194;
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
#line 382 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 175 "syntax4.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 83:
		{
			ADVANCE_LEXER;
			ZR1287 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 23:
		{
			EXP ZI1282;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 341 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1282 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 207 "syntax4.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR1243 (ZI1282, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
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

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 355 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1268 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 237 "syntax4.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 245 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 252 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 261 "syntax4.c"
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
#line 287 "syntax4.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZI1285, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1274;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_const_cast */
			{
#line 614 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_const_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 316 "syntax4.c"
			}
			/* END OF ACTION: exp_const_cast */
			ZR1243 (ZI1274, &ZIe);
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
#line 674 "syntax.act"

    (ZIe) = make_cast_exp ( type_void, (ZIa), 0 ) ;
#line 341 "syntax4.c"
			}
			/* END OF ACTION: exp_ignore */
		}
		break;
	case 132:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1277;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dynamic_cast */
			{
#line 640 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1277) = make_dynamic_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 365 "syntax4.c"
			}
			/* END OF ACTION: exp_dynamic_cast */
			ZR1243 (ZI1277, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 210:
		{
			EXP ZI1280;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 644 "syntax.act"

    (ZI1280) = make_ellipsis_exp () ;
#line 385 "syntax4.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR1243 (ZI1280, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 9:
		{
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 404 "syntax4.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1270 (&ZIns, &ZIe);
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
#line 690 "syntax.act"

    (ZIe) = make_lit_exp ( (ZIa) ) ;
#line 430 "syntax4.c"
			}
			/* END OF ACTION: exp_lit */
		}
		break;
	case 61:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 771 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_minus_Hminus, (ZIa) ) ;
#line 450 "syntax4.c"
			}
			/* END OF ACTION: exp_predec */
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 464 "syntax4.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1269 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 65:
		{
			ADVANCE_LEXER;
			ZR1289 (&ZIe);
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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 775 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_plus_Hplus, (ZIa) ) ;
#line 500 "syntax4.c"
			}
			/* END OF ACTION: exp_preinc */
		}
		break;
	case 145:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1275;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_reinterpret_cast */
			{
#line 788 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1275) = make_reinterp_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 524 "syntax4.c"
			}
			/* END OF ACTION: exp_reinterpret_cast */
			ZR1243 (ZI1275, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 116:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 389 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 543 "syntax4.c"
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
#line 682 "syntax.act"

    (ZIe) = make_indir_exp ( (ZIa) ) ;
#line 568 "syntax4.c"
			}
			/* END OF ACTION: exp_indir */
		}
		break;
	case 146:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1276;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_static_cast */
			{
#line 813 "syntax.act"

    (ZI1276) = make_static_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 591 "syntax4.c"
			}
			/* END OF ACTION: exp_static_cast */
			ZR1243 (ZI1276, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 148:
		{
			EXP ZI1279;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 817 "syntax.act"

    (ZI1279) = make_this_exp () ;
#line 611 "syntax4.c"
			}
			/* END OF ACTION: exp_this */
			ZR1243 (ZI1279, &ZIe);
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

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 390 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 631 "syntax4.c"
			}
			/* END OF ACTION: lex_typeid */
			ZRtypeid_Hexpression (ZIop, &ZI1273);
			ZR1243 (ZI1273, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 331:
		{
			int ZIop;
			EXP ZI1272;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 391 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 652 "syntax4.c"
			}
			/* END OF ACTION: lex_vtable */
			ZRtypeid_Hexpression (ZIop, &ZI1272);
			ZR1243 (ZI1272, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 783 "syntax.act"

    (ZIe) = make_ref_exp ( (ZIa), 0 ) ;
#line 690 "syntax4.c"
			}
			/* END OF ACTION: exp_ref */
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
#line 718 "syntax4.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 725 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 734 "syntax4.c"
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
#line 760 "syntax4.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZI1283, &ZIe);
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

			ZRliteral (&ZI1278);
			ZR1243 (ZI1278, &ZIe);
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
#line 742 "syntax.act"

    (ZIe) = make_not_exp ( (ZIa) ) ;
#line 810 "syntax4.c"
			}
			/* END OF ACTION: exp_not */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141:
		{
			IDENTIFIER ZIid;
			EXP ZI1286;

			ZRunqualified_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 831 "syntax4.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1243 (ZI1286, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZIid;
			TYPE ZI1268;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1284;

			ZRunqualified_Htype (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 863 "syntax4.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 870 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 877 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 886 "syntax4.c"
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
#line 912 "syntax4.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZI1284, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 131: case 140:
		{
			int ZIb;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIb) = 0 ; 
#line 930 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
			ZR1433 (&ZIb, &ZIe);
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
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 949 "syntax4.c"
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
#line 841 "syntax.act"

    (ZIe) = make_uminus_exp ( (ZIop), (ZIa) ) ;
#line 963 "syntax4.c"
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
ZRtype_Hspecifier(TYPE ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 104:
		{
			ADVANCE_LEXER;
			ZR1328 (&ZIs, &ZIbt, &ZIt, &ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 153:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1010 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRany_Hnested_Hname_Hopt (&ZIns);
			ZRany_Hclass_Hname (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_typename */
			{
#line 1286 "syntax.act"

    (ZIt) = make_typename ( (ZIns), (ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
	found_elaborate_type = 1 ;
    }
    have_type_specifier = 1 ;
#line 1029 "syntax4.c"
			}
			/* END OF ACTION: type_typename */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1036 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1043 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 118: case 121: case 129:
		{
			BASE_TYPE ZIkey;

			ZRclass_Hkey (&ZIkey);
			ZR1327 (&ZIs, &ZIkey, &ZIbt, &ZIt, &ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 98: case 124:
		{
			ZRcv_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1071 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 1079 "syntax4.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 2: case 7: case 8: case 9:
	case 25: case 83: case 97: case 102:
	case 106: case 110: case 111: case 114:
	case 115: case 122: case 123: case 127:
	case 156: case 185: case 286: case 299:
		{
			ZRsimple_Htype_Hspecifier (&ZIbt, &ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1099 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZOcv = ZIcv;
}

void
ZRparameter_Hdeclaration_Hclause(int *ZOell)
{
	int ZIell;

	switch (CURRENT_TERMINAL) {
	case 2: case 7: case 8: case 9:
	case 25: case 47: case 83: case 94:
	case 97: case 98: case 102: case 104:
	case 105: case 106: case 110: case 111:
	case 112: case 114: case 115: case 117:
	case 118: case 120: case 121: case 122:
	case 123: case 124: case 127: case 129:
	case 133: case 136: case 137: case 138:
	case 153: case 155: case 156: case 185:
	case 275: case 286: case 299:
		{
			ZRparameter_Hdeclaration_Hlist (&ZIell);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIell) = 0 ; 
#line 1149 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
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
	*ZOell = ZIell;
}

void
ZRabstract_Hdeclarator_Hopt(TYPE ZIp, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 10: case 11: case 33: case 65:
	case 66: case 78: case 333:
		{
			TYPE ZIq;

			ZRabstract_Hdeclarator_Haux (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1186 "syntax4.c"
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
ZR1323(int *ZOop)
{
	int ZIop;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		/* BEGINNING OF ACTION: is_array */
		{
#line 2095 "syntax.act"

    /* Resolve 'operator new []' from 'operator new [3]' */
    (ZI0) = predict_array () ;
#line 1222 "syntax4.c"
		}
		/* END OF ACTION: is_array */
		if (!ZI0)
			goto ZL2;
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
		/* BEGINNING OF ACTION: lex_new_array */
		{
#line 387 "syntax.act"
 (ZIop) = lex_new_Harray ; 
#line 1249 "syntax4.c"
		}
		/* END OF ACTION: lex_new_array */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: lex_new */
			{
#line 385 "syntax.act"
 (ZIop) = lex_new ; 
#line 1263 "syntax4.c"
			}
			/* END OF ACTION: lex_new */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOop = ZIop;
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
#line 380 "syntax.act"
 (ZIt) = lex_open_Hround ; 
#line 1301 "syntax4.c"
		}
		/* END OF ACTION: lex_open_round */
		/* BEGINNING OF ACTION: expected */
		{
#line 1981 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 1311 "syntax4.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZR1324(int *ZOop)
{
	int ZIop;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		/* BEGINNING OF ACTION: is_array */
		{
#line 2095 "syntax.act"

    /* Resolve 'operator new []' from 'operator new [3]' */
    (ZI0) = predict_array () ;
#line 1332 "syntax4.c"
		}
		/* END OF ACTION: is_array */
		if (!ZI0)
			goto ZL2;
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
		/* BEGINNING OF ACTION: lex_delete_array */
		{
#line 388 "syntax.act"
 (ZIop) = lex_delete_Harray ; 
#line 1359 "syntax4.c"
		}
		/* END OF ACTION: lex_delete_array */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: lex_delete */
			{
#line 386 "syntax.act"
 (ZIop) = lex_delete ; 
#line 1373 "syntax4.c"
			}
			/* END OF ACTION: lex_delete */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOop = ZIop;
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
		/* BEGINNING OF INLINE: 870 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 1392 */
					{
						switch (CURRENT_TERMINAL) {
						case 42:
							{
								ADVANCE_LEXER;
								/* BEGINNING OF ACTION: error_comma */
								{
#line 1971 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 1414 "syntax4.c"
								}
								/* END OF ACTION: error_comma */
								/* BEGINNING OF INLINE: enumerator-list */
								goto ZL2_enumerator_Hlist;
								/* END OF INLINE: enumerator-list */
							}
							UNREACHED;
						case 1: case 2: case 3: case 4:
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
#line 1971 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 1437 "syntax4.c"
								}
								/* END OF ACTION: error_comma */
							}
							break;
						}
					}
					/* END OF INLINE: 1392 */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 870 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR1199(EXP ZI1197, EXP *ZO1198)
{
	EXP ZI1198;

ZL2_1199:;
	switch (CURRENT_TERMINAL) {
	case 55:
		{
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF INLINE: logical-and */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 55:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: logical-and */
			ZRinclusive_Hor_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_log_and */
			{
#line 698 "syntax.act"

    (ZIe) = make_log_and_exp ( (ZI1197), (ZIb) ) ;
#line 1497 "syntax4.c"
			}
			/* END OF ACTION: exp_log_and */
			/* BEGINNING OF INLINE: 1199 */
			ZI1197 = ZIe;
			goto ZL2_1199;
			/* END OF INLINE: 1199 */
		}
		UNREACHED;
	default:
		{
			ZI1198 = ZI1197;
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
	*ZO1198 = ZI1198;
}

void
ZRfor_Hinit_Hstatement(EXP *ZOe)
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
#line 1543 "syntax4.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1552 "syntax4.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 1560 "syntax4.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hbasic (ZIt, ZIds);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 565 "syntax.act"

    (ZIa) = NULL_exp ;
#line 1573 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 915 "syntax.act"

    (ZIe) = (ZIa) ;
    in_declaration-- ;
#line 1582 "syntax4.c"
		}
		/* END OF ACTION: stmt_decl */
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
	case 77: case 78: case 83: case 85:
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 116:
	case 122: case 123: case 127: case 130:
	case 131: case 132: case 135: case 140:
	case 141: case 145: case 146: case 148:
	case 149: case 150: case 152: case 156:
	case 170: case 185: case 206: case 210:
	case 255: case 286: case 298: case 299:
	case 324: case 331: case 347:
		{
			ZRexpression_Hstatement (&ZIe);
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
ZRfunction_Htry_Hblock(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		int ZIr;
		EXP ZIa;
		EXP ZIb;
		EXP ZIf;
		EXP ZIc;
		EXP ZId;

		switch (CURRENT_TERMINAL) {
		case 151:
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
#line 1661 "syntax4.c"
		}
		/* END OF ACTION: reach_check */
		/* BEGINNING OF ACTION: stmt_try_func */
		{
#line 1027 "syntax.act"

    (ZIa) = begin_try_stmt ( 1 ) ;
#line 1669 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_func */
		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 891 "syntax.act"

    (ZIb) = begin_compound_stmt ( 1 ) ;
#line 1677 "syntax4.c"
		}
		/* END OF ACTION: stmt_compound_begin */
		/* BEGINNING OF ACTION: stmt_try_inject */
		{
#line 1031 "syntax.act"

    inject_try_stmt ( (ZIa) ) ;
#line 1685 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_inject */
		ZRfunction_Hbody (ZIb, &ZIf);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 907 "syntax.act"

    (ZIc) = end_compound_stmt ( (ZIf) ) ;
#line 1698 "syntax4.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: stmt_try_cont */
		{
#line 1035 "syntax.act"

    (ZId) = cont_try_stmt ( (ZIa), (ZIc) ) ;
#line 1706 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_cont */
		ZRhandler_Hseq_Hopt (ZId);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1718 "syntax4.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_try_end */
		{
#line 1039 "syntax.act"

    (ZIe) = end_try_stmt ( (ZId), 0 ) ;
#line 1726 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_end */
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
#line 1870 "syntax.act"

    OFFSET off = offset_index ( (ZIs), (ZIe), &(ZIt) ) ;
    (ZIa) = offset_add ( (ZIb), off ) ;
#line 1783 "syntax4.c"
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
ZR1327(TYPE *ZIs, BASE_TYPE *ZIkey, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZIid;
		QUALIFIER ZIqu;
		int ZIi;
		DECL_SPEC ZIb;
		IDENTIFIER ZIp;
		int ZIf;
		int ZI1325;
		DECL_SPEC ZIds;
		TYPE ZI1326;
		IDENTIFIER ZIc;

		/* BEGINNING OF ACTION: is_class_spec */
		{
#line 2053 "syntax.act"

    /* Resolve class-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 1 ) ;
#line 1843 "syntax4.c"
		}
		/* END OF ACTION: is_class_spec */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1853 "syntax4.c"
		}
		/* END OF ACTION: declarator_start */
		ZR872 (&ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: qual_get */
		{
#line 522 "syntax.act"

    (ZIqu) = crt_id_qualifier ;
    (ZIi) = crt_templ_qualifier ;
#line 1867 "syntax4.c"
		}
		/* END OF ACTION: qual_get */
		/* BEGINNING OF ACTION: template_decl */
		{
#line 1850 "syntax.act"

    if ( !IS_NULL_type ( (*ZIs) ) ) template_decl ( (*ZIs) ) ;
#line 1875 "syntax4.c"
		}
		/* END OF ACTION: template_decl */
		/* BEGINNING OF ACTION: access_get */
		{
#line 1439 "syntax.act"
 (ZIb) = crt_access ; 
#line 1882 "syntax4.c"
		}
		/* END OF ACTION: access_get */
		/* BEGINNING OF ACTION: type_class_begin */
		{
#line 1483 "syntax.act"

    IDENTIFIER id = constr_name ( last_namespace, (ZIid) ) ;
    (ZIp) = begin_class_defn ( id, (*ZIkey), cinfo_none, (*ZIs) ) ;
    (ZIf) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
#line 1896 "syntax4.c"
		}
		/* END OF ACTION: type_class_begin */
		ZRbase_Hclause_Hopt (&ZI1325);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: class_base_end */
		{
#line 1504 "syntax.act"

    end_base_class ( crt_class, (ZI1325) ) ;
#line 1909 "syntax4.c"
		}
		/* END OF ACTION: class_base_end */
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1916 "syntax4.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZI1326) = NULL_type ;
#line 1924 "syntax4.c"
		}
		/* END OF ACTION: type_none */
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
		ZRmember_Hspecification_Hopt (ZI1326, ZIds);
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
		/* BEGINNING OF ACTION: access_check_class */
		{
#line 1453 "syntax.act"

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
#line 1966 "syntax4.c"
		}
		/* END OF ACTION: access_check_class */
		/* BEGINNING OF ACTION: type_class_end */
		{
#line 1493 "syntax.act"

    (ZIc) = end_class_defn ( (ZIp) ) ;
    in_function_defn = (ZIf) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
#line 1977 "syntax4.c"
		}
		/* END OF ACTION: type_class_end */
		/* BEGINNING OF ACTION: access_set */
		{
#line 1440 "syntax.act"
 crt_access = (ZIb) ; 
#line 1984 "syntax4.c"
		}
		/* END OF ACTION: access_set */
		/* BEGINNING OF ACTION: qual_set */
		{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIqu) ;
    crt_templ_qualifier = (ZIi) ;
#line 1993 "syntax4.c"
		}
		/* END OF ACTION: qual_set */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 2001 "syntax4.c"
		}
		/* END OF ACTION: rescan_token */
		/* BEGINNING OF ACTION: type_name */
		{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIc) ) ;
    have_type_specifier = 1 ;
#line 2011 "syntax4.c"
		}
		/* END OF ACTION: type_name */
		/* BEGINNING OF ACTION: btype_none */
		{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2018 "syntax4.c"
		}
		/* END OF ACTION: btype_none */
		/* BEGINNING OF ACTION: cv_none */
		{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2025 "syntax4.c"
		}
		/* END OF ACTION: cv_none */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIaid;
			IDENTIFIER ZIid;

			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2045 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRany_Hnested_Hname_Hopt (&ZIns);
			ZRany_Hclass_Hname (&ZIaid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIaid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2060 "syntax4.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_elaborate */
			{
#line 1277 "syntax.act"

    MAKE_type_pre ( cv_none, (*ZIkey), crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
#line 2073 "syntax4.c"
			}
			/* END OF ACTION: type_elaborate */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2080 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2087 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRrelational_Hexpression(EXP *ZO1222)
{
	EXP ZI1222;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRshift_Hexpression (&ZIe);
		ZR1223 (ZIe, &ZI1222);
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
	*ZO1222 = ZI1222;
}

void
ZRmember_Hdeclaration(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZI1338;
		TYPE ZI1339;
		CV_SPEC ZI1340;
		DECL_SPEC ZI1341;
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
#line 2154 "syntax4.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (ZIt, &ZI1338, &ZI1339, &ZI1340, &ZI1341);
		ZR920 (&ZIt, &ZI1338, &ZI1339, &ZI1340, &ZI1341, &ZIbt, &ZIt1, &ZIcv1, &ZIds1);
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
#line 2173 "syntax4.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1342 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 134: case 147:
		{
			ZRtemplate_Hmember_Hdecl (ZIt, ZIds);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 10: case 11: case 33:
	case 41: case 65: case 78: case 83:
	case 141:
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
			int ZIf;
			IDENTIFIER ZId;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2217 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2225 "syntax4.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2232 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2239 "syntax4.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2250 "syntax4.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 2261 "syntax4.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 2269 "syntax4.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2277 "syntax4.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIf) = 1 ; 
#line 2284 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2292 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator (ZIds3, ZIt3, ZIbt, ZIr, ZIf, &ZId);
			ZR1095 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2311 "syntax4.c"
			}
			/* END OF ACTION: template_check */
			ZRusing_Hdeclaration ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 77:
		{
			TYPE ZIt1;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv1;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2332 "syntax4.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2339 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2346 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1657 "syntax.act"

    IGNORE empty_decl ( (ZIds), (ZIt), (ZIbt), (ZIt1), (ZIcv1), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 2357 "syntax4.c"
			}
			/* END OF ACTION: declare_member_empty */
			ADVANCE_LEXER;
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
ZR1328(TYPE *ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZIid;
		QUALIFIER ZIqu;
		int ZIi;
		IDENTIFIER ZIp;
		IDENTIFIER ZIe;

		/* BEGINNING OF ACTION: is_enum_spec */
		{
#line 2075 "syntax.act"

    /* Resolve enum-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 0 ) ;
#line 2396 "syntax4.c"
		}
		/* END OF ACTION: is_enum_spec */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2406 "syntax4.c"
		}
		/* END OF ACTION: declarator_start */
		ZR872 (&ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: qual_get */
		{
#line 522 "syntax.act"

    (ZIqu) = crt_id_qualifier ;
    (ZIi) = crt_templ_qualifier ;
#line 2420 "syntax4.c"
		}
		/* END OF ACTION: qual_get */
		/* BEGINNING OF ACTION: type_enum_begin */
		{
#line 1508 "syntax.act"

    IDENTIFIER id = constr_name ( last_namespace, (ZIid) ) ;
    (ZIp) = begin_enum_defn ( id, (*ZIs) ) ;
    no_type_defns++ ;
#line 2430 "syntax4.c"
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
		/* BEGINNING OF INLINE: 873 */
		{
			switch (CURRENT_TERMINAL) {
			case 1: case 2: case 3: case 4:
				{
					ZRenumerator_Hlist (ZIp);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 873 */
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
		/* BEGINNING OF ACTION: access_check */
		{
#line 1446 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
#line 2483 "syntax4.c"
		}
		/* END OF ACTION: access_check */
		/* BEGINNING OF ACTION: type_enum_end */
		{
#line 1514 "syntax.act"

    (ZIe) = end_enum_defn ( (ZIp) ) ;
#line 2491 "syntax4.c"
		}
		/* END OF ACTION: type_enum_end */
		/* BEGINNING OF ACTION: qual_set */
		{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIqu) ;
    crt_templ_qualifier = (ZIi) ;
#line 2500 "syntax4.c"
		}
		/* END OF ACTION: qual_set */
		/* BEGINNING OF ACTION: type_name */
		{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIe) ) ;
    have_type_specifier = 1 ;
#line 2510 "syntax4.c"
		}
		/* END OF ACTION: type_name */
		/* BEGINNING OF ACTION: btype_none */
		{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2517 "syntax4.c"
		}
		/* END OF ACTION: btype_none */
		/* BEGINNING OF ACTION: cv_none */
		{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2524 "syntax4.c"
		}
		/* END OF ACTION: cv_none */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
		{
			BASE_TYPE ZIkey;
			NAMESPACE ZIns;
			IDENTIFIER ZIaid;
			IDENTIFIER ZIid;

			/* BEGINNING OF ACTION: key_enum */
			{
#line 1423 "syntax.act"
 (ZIkey) = btype_enum ; 
#line 2544 "syntax4.c"
			}
			/* END OF ACTION: key_enum */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2552 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRany_Hnested_Hname_Hopt (&ZIns);
			ZRany_Hclass_Hname (&ZIaid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIaid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2567 "syntax4.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_elaborate */
			{
#line 1277 "syntax.act"

    MAKE_type_pre ( cv_none, (ZIkey), crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
#line 2580 "syntax4.c"
			}
			/* END OF ACTION: type_elaborate */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2587 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2594 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRfor_Hend_Hstatement(EXP *ZOe)
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
	case 286: case 298: case 299: case 324:
	case 331: case 347:
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
#line 936 "syntax.act"

    (ZIb) = make_exp_stmt ( (ZIa) ) ;
#line 2648 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 1071 "syntax.act"

    (ZIe) = bind_temporary ( (ZIb) ) ;
#line 2656 "syntax4.c"
			}
			/* END OF ACTION: bind_temporary */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2668 "syntax4.c"
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
ZR1329(int *ZOt)
{
	int ZIt;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
	case 142: case 143: case 144: case 155:
		{
			ZRbase_Hspecifier_Hlist ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIt) = 1 ; 
#line 2703 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIt) = 0 ; 
#line 2714 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
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
ZRnew_Htype_Hid(TYPE *ZOt, int *ZOn)
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
		TYPE ZIs;
		TYPE ZIq;

		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2000 "syntax.act"

    (ZIn1) = no_type_defns ;
#line 2752 "syntax4.c"
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

    (ZIs) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2766 "syntax4.c"
		}
		/* END OF ACTION: type_complete */
		ZRnew_Hdeclarator_Hopt (&ZIq);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIs) : inject_pre_type ( (ZIq), (ZIs), 1 ) ) ;
#line 2779 "syntax4.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2008 "syntax.act"

    (ZIn) = no_type_defns - (ZIn1) ;
#line 2787 "syntax4.c"
		}
		/* END OF ACTION: diff_type_defns */
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
ZRand_Hexpression(EXP *ZO1210)
{
	EXP ZI1210;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRmaxmin_Hexpression (&ZIe);
		ZR1211 (ZIe, &ZI1210);
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
	*ZO1210 = ZI1210;
}

void
ZR1330(int *ZOv)
{
	int ZIv;

	switch (CURRENT_TERMINAL) {
	case 155:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIv) = 1 ; 
#line 2839 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIv) = 0 ; 
#line 2850 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
		}
		break;
	case 356:
		return;
	}
	*ZOv = ZIv;
}

void
ZR1203(EXP ZI1201, EXP *ZO1202)
{
	EXP ZI1202;

ZL2_1203:;
	switch (CURRENT_TERMINAL) {
	case 67:
		{
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF INLINE: or */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 67:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or */
			ZRexclusive_Hor_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_or */
			{
#line 746 "syntax.act"

    (ZIe) = make_or_exp ( (ZI1201), (ZIb) ) ;
#line 2896 "syntax4.c"
			}
			/* END OF ACTION: exp_or */
			/* BEGINNING OF INLINE: 1203 */
			ZI1201 = ZIe;
			goto ZL2_1203;
			/* END OF INLINE: 1203 */
		}
		UNREACHED;
	default:
		{
			ZI1202 = ZI1201;
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
	*ZO1202 = ZI1202;
}

void
parse_exp(EXP *ZOe)
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
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1966 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2947 "syntax4.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2955 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZR1331(DECL_SPEC *ZOa)
{
	DECL_SPEC ZIa;

	switch (CURRENT_TERMINAL) {
	case 142: case 143: case 144:
		{
			ZRaccess_Hspecifier (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: access_none */
			{
#line 1438 "syntax.act"
 (ZIa) = dspec_none ; 
#line 2984 "syntax4.c"
			}
			/* END OF ACTION: access_none */
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
	*ZOa = ZIa;
}

void
ZRdeclaration_Hnonempty(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
{
	EXP ZIe;

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
#line 3025 "syntax4.c"
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
#line 3044 "syntax4.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1255 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3057 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 105:
		{
			ZRlinkage_Hspecification (ZIt, ZIds, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 134: case 147:
		{
			ZRtemplate_Hdeclaration (ZIt, ZIds, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
#line 3106 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 3114 "syntax4.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 3121 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 3128 "syntax4.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 3139 "syntax4.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 3150 "syntax4.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 3158 "syntax4.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 3166 "syntax4.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3174 "syntax4.c"
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
#line 3204 "syntax4.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 3212 "syntax4.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 3222 "syntax4.c"
			}
			/* END OF ACTION: access_check_decl */
			ZR1078 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3235 "syntax4.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	case 126: case 139: case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 3248 "syntax4.c"
			}
			/* END OF ACTION: template_check */
			ZRdeclaration_Hother (&ZIe);
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
ZR1078(BASE_TYPE *ZIbt, DECL_SPEC *ZIds3, TYPE *ZIt3, ACCESS_LIST *ZIr, int *ZIc, IDENTIFIER *ZId)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		int ZIb;
		EXP ZIe;

		/* BEGINNING OF ACTION: is_function */
		{
#line 2058 "syntax.act"

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
#line 3285 "syntax4.c"
		}
		/* END OF ACTION: is_function */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: initialiser_bad */
		{
#line 1760 "syntax.act"

    if ( (*ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 3295 "syntax4.c"
		}
		/* END OF ACTION: initialiser_bad */
		/* BEGINNING OF ACTION: access_free */
		{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3303 "syntax4.c"
		}
		/* END OF ACTION: access_free */
		/* BEGINNING OF ACTION: function_begin */
		{
#line 1136 "syntax.act"

    (ZIb) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (*ZId) ) ;
#line 3315 "syntax4.c"
		}
		/* END OF ACTION: function_begin */
		ZRfunction_Hdefinition_Hbody (&ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: function_end */
		{
#line 1144 "syntax.act"

    IGNORE end_function ( (*ZId), (ZIe) ) ;
    in_class_defn = (ZIb) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
#line 3331 "syntax4.c"
		}
		/* END OF ACTION: function_end */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3339 "syntax4.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3347 "syntax4.c"
		}
		/* END OF ACTION: rescan_token */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	{
		SID_LIST_EXP ZIp;
		EXP ZIe;

		/* BEGINNING OF ACTION: is_true */
		{
#line 2048 "syntax.act"

    (ZI0) = (*ZIc) ;
#line 3363 "syntax4.c"
		}
		/* END OF ACTION: is_true */
		if (!ZI0)
			goto ZL3;
		/* BEGINNING OF ACTION: rescan_init */
		{
#line 2145 "syntax.act"

    if ( crt_lex_token == lex_open_Hinit ) {
	crt_lex_token = lex_open_Hround ;
    } else {
	RESCAN_LEXER ;
    }
#line 3377 "syntax4.c"
		}
		/* END OF ACTION: rescan_init */
		ZRinitialiser_Hexp_Hlist (*ZId, &ZIp);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_initialiser */
		{
#line 686 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 3390 "syntax4.c"
		}
		/* END OF ACTION: exp_initialiser */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1746 "syntax.act"

    int def = init_object ( (*ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (*ZId), &decl_loc, def ) ;
#line 3406 "syntax4.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZId) ) ;
    }
#line 3416 "syntax4.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3424 "syntax4.c"
		}
		/* END OF ACTION: declarator_end */
		ZR1079 (ZIbt, ZIds3, ZIt3, ZIr);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: access_free */
		{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3437 "syntax4.c"
		}
		/* END OF ACTION: access_free */
		switch (CURRENT_TERMINAL) {
		case 77:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		goto ZL0;
	}
	UNREACHED;
ZL3:;
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			EXP ZIe;

			ADVANCE_LEXER;
			ZRinitialiser_Hclause (*ZId, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_id */
			{
#line 1746 "syntax.act"

    int def = init_object ( (*ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (*ZId), &decl_loc, def ) ;
#line 3468 "syntax4.c"
			}
			/* END OF ACTION: initialise_id */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZId) ) ;
    }
#line 3478 "syntax4.c"
			}
			/* END OF ACTION: access_check_decl */
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3486 "syntax4.c"
			}
			/* END OF ACTION: declarator_end */
			ZR1079 (ZIbt, ZIds3, ZIt3, ZIr);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_free */
			{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3499 "syntax4.c"
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
	case 42: case 77:
		{
			EXP ZIe;

			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3520 "syntax4.c"
			}
			/* END OF ACTION: exp_none */
			/* BEGINNING OF ACTION: initialise_id */
			{
#line 1746 "syntax.act"

    int def = init_object ( (*ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (*ZId), &decl_loc, def ) ;
#line 3529 "syntax4.c"
			}
			/* END OF ACTION: initialise_id */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZId) ) ;
    }
#line 3539 "syntax4.c"
			}
			/* END OF ACTION: access_check_decl */
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1697 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3547 "syntax4.c"
			}
			/* END OF ACTION: declarator_end */
			ZR1079 (ZIbt, ZIds3, ZIt3, ZIr);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_free */
			{
#line 1470 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3560 "syntax4.c"
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
ZRthrow_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;

		switch (CURRENT_TERMINAL) {
		case 149:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 639 */
		{
			{
				TYPE ZIt;
				int ZIn;

				/* BEGINNING OF ACTION: is_type_id_false */
				{
#line 2100 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 3612 "syntax4.c"
				}
				/* END OF ACTION: is_type_id_false */
				if (!ZI0)
					goto ZL3;
				ZRtype_Hid (&ZIt, &ZIn);
				if ((CURRENT_TERMINAL) == 356) {
					RESTORE_LEXER;
					goto ZL1;
				}
				/* BEGINNING OF ACTION: exp_throw_type */
				{
#line 825 "syntax.act"

    (ZIa) = make_throw_arg ( (ZIt), (ZIn) ) ;
#line 3627 "syntax4.c"
				}
				/* END OF ACTION: exp_throw_type */
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
					ZRassignment_Hexpression (&ZIa);
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
#line 3665 "syntax4.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			}
		ZL2:;
		}
		/* END OF INLINE: 639 */
		/* BEGINNING OF ACTION: exp_throw */
		{
#line 821 "syntax.act"

    (ZIe) = make_throw_exp ( (ZIa), 1 ) ;
#line 3679 "syntax4.c"
		}
		/* END OF ACTION: exp_throw */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1079(BASE_TYPE *ZIbt, DECL_SPEC *ZIds3, TYPE *ZIt3, ACCESS_LIST *ZIr)
{
	switch (CURRENT_TERMINAL) {
	case 42:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3703 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRinit_Hdeclarator_Hlist (*ZIds3, *ZIbt, *ZIt3, *ZIr);
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
ZR1207(EXP ZI1205, EXP *ZO1206)
{
	EXP ZI1206;

ZL2_1207:;
	switch (CURRENT_TERMINAL) {
	case 80:
		{
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF INLINE: xor */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 80:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: xor */
			ZRand_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_xor */
			{
#line 849 "syntax.act"

    (ZIe) = make_xor_exp ( (ZI1205), (ZIb) ) ;
#line 3759 "syntax4.c"
			}
			/* END OF ACTION: exp_xor */
			/* BEGINNING OF INLINE: 1207 */
			ZI1205 = ZIe;
			goto ZL2_1207;
			/* END OF INLINE: 1207 */
		}
		UNREACHED;
	default:
		{
			ZI1206 = ZI1205;
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
	*ZO1206 = ZI1206;
}

void
parse_stmt(EXP *ZOe)
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
#line 3805 "syntax4.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 3814 "syntax4.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 3822 "syntax4.c"
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
#line 3836 "syntax4.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3844 "syntax4.c"
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
#line 3877 "syntax4.c"
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
#line 3912 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3920 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3928 "syntax4.c"
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
#line 3978 "syntax4.c"
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
#line 4014 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4022 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4030 "syntax4.c"
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
#line 4054 "syntax4.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4063 "syntax4.c"
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
#line 4103 "syntax4.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4111 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4118 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4127 "syntax4.c"
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
#line 4153 "syntax4.c"
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
#line 4188 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4196 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4204 "syntax4.c"
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
#line 4251 "syntax4.c"
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
#line 4286 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4294 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4302 "syntax4.c"
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
#line 4341 "syntax4.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4352 "syntax4.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 4360 "syntax4.c"
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
#line 4395 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4403 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4411 "syntax4.c"
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
#line 4454 "syntax4.c"
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
#line 4488 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4496 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4504 "syntax4.c"
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
#line 4551 "syntax4.c"
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
#line 4586 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4594 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4602 "syntax4.c"
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
#line 4640 "syntax4.c"
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
#line 4675 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4683 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4691 "syntax4.c"
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
#line 4712 "syntax4.c"
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
#line 4732 "syntax4.c"
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
#line 4784 "syntax4.c"
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
#line 4818 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4826 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4834 "syntax4.c"
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
#line 4877 "syntax4.c"
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
#line 4911 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4919 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4927 "syntax4.c"
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
#line 4948 "syntax4.c"
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
#line 4968 "syntax4.c"
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
#line 5031 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5039 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5047 "syntax4.c"
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
#line 5090 "syntax4.c"
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
#line 5124 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5132 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5140 "syntax4.c"
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
#line 5187 "syntax4.c"
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
#line 5222 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5230 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5238 "syntax4.c"
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
#line 5258 "syntax4.c"
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
#line 5288 "syntax4.c"
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
#line 5323 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5331 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5339 "syntax4.c"
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
#line 5382 "syntax4.c"
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
#line 5416 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5424 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5432 "syntax4.c"
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
#line 5453 "syntax4.c"
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
#line 5498 "syntax4.c"
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
#line 5533 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5541 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5549 "syntax4.c"
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
#line 5592 "syntax4.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5603 "syntax4.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 5611 "syntax4.c"
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
#line 5646 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5654 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5662 "syntax4.c"
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
#line 5710 "syntax4.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5721 "syntax4.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 5731 "syntax4.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 5738 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 5745 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 5754 "syntax4.c"
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
#line 5780 "syntax4.c"
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
#line 5815 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5823 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5831 "syntax4.c"
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
#line 5869 "syntax4.c"
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
#line 5904 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5912 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5920 "syntax4.c"
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
#line 5941 "syntax4.c"
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
#line 5978 "syntax4.c"
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
#line 6014 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6022 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6030 "syntax4.c"
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
#line 6068 "syntax4.c"
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
#line 6104 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6112 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6120 "syntax4.c"
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
#line 6175 "syntax4.c"
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
#line 6209 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6217 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6225 "syntax4.c"
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
#line 6276 "syntax4.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 6283 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 6292 "syntax4.c"
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
#line 6318 "syntax4.c"
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
#line 6353 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6361 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6369 "syntax4.c"
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
#line 6434 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6442 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6450 "syntax4.c"
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
#line 6534 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6542 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6550 "syntax4.c"
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
#line 6605 "syntax4.c"
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
#line 6639 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6647 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6655 "syntax4.c"
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
#line 6701 "syntax4.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 6709 "syntax4.c"
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
#line 6744 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6752 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6760 "syntax4.c"
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
#line 6806 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6814 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6822 "syntax4.c"
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
#line 6867 "syntax4.c"
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
#line 6902 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6910 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6918 "syntax4.c"
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
#line 6955 "syntax4.c"
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
#line 6969 "syntax4.c"
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
#line 7003 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 7011 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 7019 "syntax4.c"
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
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1966 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 7045 "syntax4.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 7053 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
