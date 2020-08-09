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


#line 98 "syntax2.c"

void
ZRbase_Hspecifier(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		DECL_SPEC ZIa;
		int ZIv;
		NAMESPACE ZIns;
		IDENTIFIER ZIaid;
		IDENTIFIER ZIid;

		/* BEGINNING OF INLINE: 846 */
		{
			switch (CURRENT_TERMINAL) {
			case 155:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: bool_true */
					{
#line 2036 "syntax.act"
 (ZIv) = 1 ; 
#line 123 "syntax2.c"
					}
					/* END OF ACTION: bool_true */
					ZR1331 (&ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 142: case 143: case 144:
				{
					ZRaccess_Hspecifier (&ZIa);
					ZR1330 (&ZIv);
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
#line 149 "syntax2.c"
					}
					/* END OF ACTION: access_none */
					/* BEGINNING OF ACTION: bool_false */
					{
#line 2035 "syntax.act"
 (ZIv) = 0 ; 
#line 156 "syntax2.c"
					}
					/* END OF ACTION: bool_false */
				}
				break;
			}
		}
		/* END OF INLINE: 846 */
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
#line 176 "syntax2.c"
		}
		/* END OF ACTION: namespace_id */
		/* BEGINNING OF ACTION: class_base */
		{
#line 1500 "syntax.act"

    add_base_class ( (ZIid), (ZIa), (ZIv) ) ;
#line 184 "syntax2.c"
		}
		/* END OF ACTION: class_base */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRinit_Hdeclarator(DECL_SPEC ZIds, BASE_TYPE ZIbt, TYPE ZIp, ACCESS_LIST ZIr)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIt;
		IDENTIFIER ZIid;
		int ZIc;
		IDENTIFIER ZId;
		EXP ZIe;

		ZRdeclarator (ZIp, &ZIt, &ZIid, &ZIc);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_id */
		{
#line 1594 "syntax.act"

    if ( type_tag ( (ZIt) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZIt) ) ;
	(ZId) = make_func_decl ( (ZIds), (ZIt), (ZIid), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZId) = make_object_decl ( (ZIds), (ZIt), (ZIid), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIbt) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 234 "syntax2.c"
		}
		/* END OF ACTION: declare_id */
		/* BEGINNING OF ACTION: access_check_ret */
		{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 242 "syntax2.c"
		}
		/* END OF ACTION: access_check_ret */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 252 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		ZRinitialiser_Hopt (ZIc, ZId, &ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1746 "syntax.act"

    int def = init_object ( (ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 266 "syntax2.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 276 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1697 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 284 "syntax2.c"
		}
		/* END OF ACTION: declarator_end */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRdeclaration(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
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
#line 319 "syntax2.c"
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
#line 338 "syntax2.c"
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
#line 351 "syntax2.c"
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
	case 65: case 77: case 78: case 83:
	case 141:
		{
			BASE_TYPE ZIbt;
			TYPE ZIt1;
			CV_SPEC ZI1256;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 391 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 399 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZI1256) = cv_none ; 
#line 406 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			ZR1257 (&ZIt, &ZIds, &ZIbt, &ZIt1, &ZI1256, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 126: case 139: case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 424 "syntax2.c"
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
ZRinitialiser_Hexp_Hlist(IDENTIFIER ZId, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;
		SID_LIST_EXP ZIq;

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
#line 469 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF INLINE: 1006 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					ZRinitialiser_Hexp_Hlist (ZId, &ZIq);
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

    (ZIq) = NULL_list ( EXP ) ;
#line 492 "syntax2.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1006 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 550 "syntax.act"

    CONS_exp ( (ZIe), (ZIq), (ZIp) ) ;
#line 505 "syntax2.c"
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
ZR1287(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 141: case 147:
		{
			ZR1271 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 131: case 140:
		{
			int ZIb;

			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIb) = 1 ; 
#line 541 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			ZR1433 (&ZIb, &ZIe);
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
ZRcontrol_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 289:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_set */
			{
#line 1119 "syntax.act"
 unreached_code = 0 ; 
#line 579 "syntax2.c"
			}
			/* END OF ACTION: reach_set */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_reach */
			{
#line 1063 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 1 ) ;
#line 592 "syntax2.c"
			}
			/* END OF ACTION: stmt_reach */
		}
		break;
	case 323:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_unset */
			{
#line 1120 "syntax.act"
 unreached_code = 1 ; 
#line 606 "syntax2.c"
			}
			/* END OF ACTION: reach_unset */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_unreach */
			{
#line 1067 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 0 ) ;
#line 619 "syntax2.c"
			}
			/* END OF ACTION: stmt_unreach */
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
ZRfull_Hqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		NAMESPACE ZIns;
		IDENTIFIER ZItid;

		switch (CURRENT_TERMINAL) {
		case 9:
			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 656 "syntax2.c"
			}
			/* END OF EXTRACT: full-name */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
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
#line 678 "syntax2.c"
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
#line 691 "syntax2.c"
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
    qual_namespace = (ZIns) ;
#line 708 "syntax2.c"
		}
		/* END OF ACTION: namespace_full */
		/* BEGINNING OF ACTION: namespace_id */
		{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 717 "syntax2.c"
		}
		/* END OF ACTION: namespace_id */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRctor_Hinitialiser_Hopt(EXP ZIc, EXP *ZOe, EXP *ZOd)
{
	EXP ZIe;
	EXP ZId;

	switch (CURRENT_TERMINAL) {
	case 41:
		{
			NAMESPACE ZIcns;
			int ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: ctor_begin */
			{
#line 1163 "syntax.act"

    (ZIcns) = ctor_begin () ;
#line 747 "syntax2.c"
			}
			/* END OF ACTION: ctor_begin */
			/* BEGINNING OF INLINE: 1023 */
			{
				switch (CURRENT_TERMINAL) {
				case 1: case 2: case 3: case 4:
				case 7: case 8: case 9: case 65:
				case 83:
					{
						ZRmem_Hinitialiser_Hlist (ZIcns);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: bool_true */
						{
#line 2036 "syntax.act"
 (ZIb) = 1 ; 
#line 766 "syntax2.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2035 "syntax.act"
 (ZIb) = 0 ; 
#line 777 "syntax2.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 1023 */
			/* BEGINNING OF ACTION: ctor_end */
			{
#line 1167 "syntax.act"

    (ZIe) = ctor_end ( (ZIcns), (ZIc), (ZIb) ) ;
#line 790 "syntax2.c"
			}
			/* END OF ACTION: ctor_end */
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZId) = NULL_exp ;
#line 798 "syntax2.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: ctor_none */
			{
#line 1175 "syntax.act"

    (ZId) = NULL_exp ;
    (ZIe) = ctor_none ( (ZIc), &(ZId) ) ;
#line 811 "syntax2.c"
			}
			/* END OF ACTION: ctor_none */
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
	*ZOd = ZId;
}

void
ZR1289(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIt;
		int ZIn;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_type_id_false */
		{
#line 2100 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 847 "syntax2.c"
		}
		/* END OF ACTION: is_type_id_false */
		if (!ZI0)
			goto ZL2;
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
		ZRcast_Hexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_cast */
		{
#line 601 "syntax.act"

    /* n is the number of type definitions in t */
    (ZIe) = make_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 874 "syntax2.c"
		}
		/* END OF ACTION: exp_cast */
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
			EXP ZIa;
			EXP ZI1281;

			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 751 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 907 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 754 "syntax.act"

    (ZI1281) = make_paren_exp ( (ZIa) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 921 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1243 (ZI1281, &ZIe);
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
ZRunqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
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
#line 974 "syntax2.c"
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
#line 987 "syntax2.c"
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
		/* BEGINNING OF ACTION: namespace_simple */
		{
#line 493 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1005 "syntax2.c"
		}
		/* END OF ACTION: namespace_simple */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRexception_Hdeclaration(int ZIn1, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIs;
		BASE_TYPE ZIb1;
		TYPE ZI1604;
		CV_SPEC ZI1605;
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;
		TYPE ZIt2;
		DECL_SPEC ZIds2;
		TYPE ZIt;
		IDENTIFIER ZIid;
		int ZIn2;

		/* BEGINNING OF ACTION: is_type_specifier */
		{
#line 2110 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 1046 "syntax2.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIs) = NULL_type ;
#line 1056 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		ZRtype_Hspecifier (ZIs, &ZIb1, &ZI1604, &ZI1605);
		ZR888 (&ZIb1, &ZI1604, &ZI1605, &ZIbt, &ZIt1, &ZIcv1);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 1069 "syntax2.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds2) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1080 "syntax2.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1088 "syntax2.c"
		}
		/* END OF ACTION: declarator_start */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2008 "syntax.act"

    (ZIn2) = no_type_defns - (ZIn1) ;
#line 1101 "syntax2.c"
		}
		/* END OF ACTION: diff_type_defns */
		/* BEGINNING OF ACTION: declare_except */
		{
#line 1679 "syntax.act"

    (ZId) = make_except_decl ( (ZIds2), (ZIt), (ZIid), (ZIn2) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1111 "syntax2.c"
		}
		/* END OF ACTION: declare_except */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 47: case 210:
		{
			/* BEGINNING OF INLINE: ellipsis-aux */
			{
				switch (CURRENT_TERMINAL) {
				case 47:
					{
						ADVANCE_LEXER;
					}
					break;
				case 210:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: ellipsis-aux */
			/* BEGINNING OF ACTION: declare_none */
			{
#line 1685 "syntax.act"

    (ZId) = NULL_id ;
#line 1144 "syntax2.c"
			}
			/* END OF ACTION: declare_none */
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
	*ZOd = ZId;
}

void
ZRclass_Hkey(BASE_TYPE *ZOkey)
{
	BASE_TYPE ZIkey;

	switch (CURRENT_TERMINAL) {
	case 129:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_class */
			{
#line 1420 "syntax.act"
 (ZIkey) = btype_class ; 
#line 1173 "syntax2.c"
			}
			/* END OF ACTION: key_class */
		}
		break;
	case 118:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct */
			{
#line 1421 "syntax.act"
 (ZIkey) = btype_struct ; 
#line 1185 "syntax2.c"
			}
			/* END OF ACTION: key_struct */
		}
		break;
	case 121:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union */
			{
#line 1422 "syntax.act"
 (ZIkey) = btype_union ; 
#line 1197 "syntax2.c"
			}
			/* END OF ACTION: key_union */
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
	*ZOkey = ZIkey;
}

void
ZRinitialiser_Hlist(IDENTIFIER ZId, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIb;
		EXP ZIa;
		SID_LIST_EXP ZIq;

		ZRinitialiser_Hclause (ZId, &ZIb);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_location */
		{
#line 694 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIb), (ZIa) ) ;
#line 1238 "syntax2.c"
		}
		/* END OF ACTION: exp_location */
		/* BEGINNING OF INLINE: 1003 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					ZR1004 (&ZId, &ZIq);
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

    (ZIq) = NULL_list ( EXP ) ;
#line 1261 "syntax2.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1003 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 550 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1274 "syntax2.c"
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
ZRmember_Hcond_Hhead(EXP *ZO1169)
{
	EXP ZI1169;

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
#line 323 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1305 "syntax2.c"
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
#line 1320 "syntax2.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: decl_hash_if */
		{
#line 1886 "syntax.act"

    target_decl ( lex_if, (ZIc) ) ;
#line 1328 "syntax2.c"
		}
		/* END OF ACTION: decl_hash_if */
		ZRmember_Hcond_Hbody ();
		ZR1170 (ZIp, &ZI1169);
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
	*ZO1169 = ZI1169;
}

void
parse_tok_type(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZIbt;
		TYPE ZIp;
		CV_SPEC ZIcv;
		TYPE ZIq;

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
#line 1371 "syntax2.c"
		}
		/* END OF ACTION: type_complete */
		ZRabstract_Hdeclarator_Hopt (ZIq, &ZIt);
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
	*ZOt = ZIt;
}

void
ZR1164(TYPE ZI1160, IDENTIFIER ZI1161, TYPE *ZO1162, IDENTIFIER *ZO1163)
{
	TYPE ZI1162;
	IDENTIFIER ZI1163;

ZL2_1164:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 333:
		{
			IDENTIFIER ZIid;
			QUALIFIER ZIi;
			int ZIb;
			TYPE ZIq;
			TYPE ZIt;

			ZIid = ZI1161;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1411 "syntax2.c"
			}
			/* END OF ACTION: qual_get */
			ZRabstract_Hdeclarator_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1425 "syntax2.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1383 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1160) ) ? (ZIq) : inject_pre_type ( (ZI1160), (ZIq), 0 ) ) ;
#line 1433 "syntax2.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 1164 */
			ZI1160 = ZIt;
			ZI1161 = ZIid;
			goto ZL2_1164;
			/* END OF INLINE: 1164 */
		}
		UNREACHED;
	default:
		{
			ZI1162 = ZI1160;
			ZI1163 = ZI1161;
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
	*ZO1162 = ZI1162;
	*ZO1163 = ZI1163;
}

void
ZRequality_Hoperator(void)
{
	switch (CURRENT_TERMINAL) {
	case 48:
		{
			ADVANCE_LEXER;
		}
		break;
	case 63:
		{
			/* BEGINNING OF INLINE: not-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 63:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: not-eq */
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
ZRmaxmin_Hexpression(EXP *ZO1214)
{
	EXP ZI1214;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRequality_Hexpression (&ZIe);
		ZR1215 (ZIe, &ZI1214);
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
	*ZO1214 = ZI1214;
}

void
ZRmem_Hinitialiser(NAMESPACE ZIcns)
{
	switch (CURRENT_TERMINAL) {
	case 65:
		{
			SID_LIST_EXP ZIp;
			EXP ZIe;
			IDENTIFIER ZIid;

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
			/* BEGINNING OF ACTION: exp_initialiser */
			{
#line 686 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 1551 "syntax2.c"
			}
			/* END OF ACTION: exp_initialiser */
			/* BEGINNING OF ACTION: id_none */
			{
#line 445 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1561 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: ctor_initialise */
			{
#line 1171 "syntax.act"

    ctor_initialise ( (ZIcns), (ZIid), (ZIe) ) ;
#line 1569 "syntax2.c"
			}
			/* END OF ACTION: ctor_initialise */
		}
		break;
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIaid;
			IDENTIFIER ZIid;
			QUALIFIER ZIi;
			int ZIb;
			SID_LIST_EXP ZIp;
			EXP ZIe;

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
#line 1597 "syntax2.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1606 "syntax2.c"
			}
			/* END OF ACTION: qual_get */
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
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1633 "syntax2.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: exp_initialiser */
			{
#line 686 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 1641 "syntax2.c"
			}
			/* END OF ACTION: exp_initialiser */
			/* BEGINNING OF ACTION: ctor_initialise */
			{
#line 1171 "syntax.act"

    ctor_initialise ( (ZIcns), (ZIid), (ZIe) ) ;
#line 1649 "syntax2.c"
			}
			/* END OF ACTION: ctor_initialise */
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
ZR1292(EXP *ZI1290, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 42:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 550 "syntax.act"

    CONS_exp ( (*ZI1290), (ZIq), (ZIp) ) ;
#line 1687 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 605 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1695 "syntax2.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	default:
		{
			ZIe = *ZI1290;
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
ZRinset_Hflow_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 347:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR1294 (&ZIe);
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
ZR1293(EXP *ZIa, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	switch (CURRENT_TERMINAL) {
	case 42:
		{
			SID_LIST_EXP ZIq;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 550 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1767 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
		}
		break;
	default:
		{
			SID_LIST_EXP ZIq;

			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 546 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 1781 "syntax2.c"
			}
			/* END OF ACTION: list_exp_null */
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 550 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1789 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
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
ZR1294(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 298:
		{
			EXP ZIa;

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
#line 1826 "syntax2.c"
			}
			/* END OF ACTION: exp_set */
			switch (CURRENT_TERMINAL) {
			case 348:
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
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 845 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 1853 "syntax2.c"
			}
			/* END OF ACTION: exp_unused */
			switch (CURRENT_TERMINAL) {
			case 348:
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
ZRdelete_Hoperator(int *ZOop)
{
	int ZIop;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 131:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR1434 (&ZIop);
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
	*ZOop = ZIop;
}

void
parse_type_param(IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	switch (CURRENT_TERMINAL) {
	case 147:
		{
			int ZIe;
			TOKEN ZIp;
			TYPE ZIt;
			DECL_SPEC ZIds;
			TYPE ZIt1;
			IDENTIFIER ZIid;
			IDENTIFIER ZItid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIe) = 0 ; 
#line 1929 "syntax2.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: template_params */
			{
#line 1823 "syntax.act"

    (ZIp) = template_params ( (ZIe) ) ;
    RESCAN_LEXER ;
#line 1938 "syntax2.c"
			}
			/* END OF ACTION: template_params */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 1946 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1953 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: template_type */
			{
#line 1815 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 1961 "syntax2.c"
			}
			/* END OF ACTION: template_type */
			switch (CURRENT_TERMINAL) {
			case 129:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRtemplate_Hparam_Hname (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_param_name */
			{
#line 1836 "syntax.act"

    (ZId) = make_template_param ( (ZIt1), (ZIid) ) ;
    UNUSED ( (ZIds) ) ;
#line 1982 "syntax2.c"
			}
			/* END OF ACTION: template_param_name */
			/* BEGINNING OF INLINE: 1122 */
			{
				switch (CURRENT_TERMINAL) {
				case 36:
					{
						IDENTIFIER ZIaid;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: default_arg_begin */
						{
#line 2013 "syntax.act"

    in_default_arg++ ;
#line 1998 "syntax2.c"
						}
						/* END OF ACTION: default_arg_begin */
						ZRany_Hqualified_Hid (&ZIaid);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: namespace_simple */
						{
#line 493 "syntax.act"

    (ZItid) = (ZIaid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2013 "syntax2.c"
						}
						/* END OF ACTION: namespace_simple */
						/* BEGINNING OF ACTION: default_arg_end */
						{
#line 2017 "syntax.act"

    in_default_arg-- ;
#line 2021 "syntax2.c"
						}
						/* END OF ACTION: default_arg_end */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: id_none */
						{
#line 445 "syntax.act"

    (ZItid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2035 "syntax2.c"
						}
						/* END OF ACTION: id_none */
					}
					break;
				}
			}
			/* END OF INLINE: 1122 */
			/* BEGINNING OF ACTION: template_init_name */
			{
#line 1841 "syntax.act"

    init_template_param ( (ZId), (ZItid) ) ;
#line 2048 "syntax2.c"
			}
			/* END OF ACTION: template_init_name */
			/* BEGINNING OF ACTION: template_end */
			{
#line 1819 "syntax.act"

    end_template ( (ZIp) ) ;
#line 2056 "syntax2.c"
			}
			/* END OF ACTION: template_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 2064 "syntax2.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 129: case 153:
		{
			IDENTIFIER ZIid;
			TYPE ZIt;

			/* BEGINNING OF INLINE: 1120 */
			{
				switch (CURRENT_TERMINAL) {
				case 129:
					{
						ADVANCE_LEXER;
					}
					break;
				case 153:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 1120 */
			ZRtemplate_Hparam_Hname (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_param_type */
			{
#line 1828 "syntax.act"

    (ZId) = make_type_param ( (ZIid) ) ;
#line 2102 "syntax2.c"
			}
			/* END OF ACTION: template_param_type */
			/* BEGINNING OF INLINE: 1121 */
			{
				switch (CURRENT_TERMINAL) {
				case 36:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: default_arg_begin */
						{
#line 2013 "syntax.act"

    in_default_arg++ ;
#line 2116 "syntax2.c"
						}
						/* END OF ACTION: default_arg_begin */
						parse_tok_type (&ZIt);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: default_arg_end */
						{
#line 2017 "syntax.act"

    in_default_arg-- ;
#line 2129 "syntax2.c"
						}
						/* END OF ACTION: default_arg_end */
						/* BEGINNING OF ACTION: type_check */
						{
#line 1316 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 2137 "syntax2.c"
						}
						/* END OF ACTION: type_check */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: type_none */
						{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 2149 "syntax2.c"
						}
						/* END OF ACTION: type_none */
					}
					break;
				}
			}
			/* END OF INLINE: 1121 */
			/* BEGINNING OF ACTION: template_init_type */
			{
#line 1832 "syntax.act"

    init_type_param ( (ZId), (ZIt) ) ;
#line 2162 "syntax2.c"
			}
			/* END OF ACTION: template_init_type */
		}
		break;
	case 356:
		return;
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
#line 2183 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: decl_none */
		{
#line 1159 "syntax.act"

    (ZId) = NULL_id ;
#line 2191 "syntax2.c"
		}
		/* END OF ACTION: decl_none */
	}
ZL0:;
	*ZOd = ZId;
}

void
ZRmember_Hspecification_Hopt(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_member_Hspecification_Hopt:;
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
#line 2223 "syntax2.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL3;
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
#line 2242 "syntax2.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1342 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		/* BEGINNING OF INLINE: member-specification-opt */
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		} else {
			goto ZL2_member_Hspecification_Hopt;
		}
		/* END OF INLINE: member-specification-opt */
	}
	UNREACHED;
ZL3:;
	switch (CURRENT_TERMINAL) {
	case 142: case 143: case 144:
		{
			DECL_SPEC ZIb;

			ZRaccess_Hspecifier (&ZIb);
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access_set */
			{
#line 1440 "syntax.act"
 crt_access = (ZIb) ; 
#line 2277 "syntax2.c"
			}
			/* END OF ACTION: access_set */
			/* BEGINNING OF INLINE: member-specification-opt */
			goto ZL2_member_Hspecification_Hopt;
			/* END OF INLINE: member-specification-opt */
		}
		UNREACHED;
	case 134: case 147:
		{
			ZRtemplate_Hmember_Hdecl (ZIt, ZIds);
			/* BEGINNING OF INLINE: member-specification-opt */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_member_Hspecification_Hopt;
			}
			/* END OF INLINE: member-specification-opt */
		}
		UNREACHED;
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
#line 2320 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2328 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2335 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2342 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2353 "syntax2.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 2364 "syntax2.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 2372 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2380 "syntax2.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIf) = 1 ; 
#line 2387 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2395 "syntax2.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator (ZIds3, ZIt3, ZIbt, ZIr, ZIf, &ZId);
			ZR1095 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZId);
			/* BEGINNING OF INLINE: member-specification-opt */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_member_Hspecification_Hopt;
			}
			/* END OF INLINE: member-specification-opt */
		}
		UNREACHED;
	case 26: case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2418 "syntax2.c"
			}
			/* END OF ACTION: template_check */
			ZR1343 ();
			/* BEGINNING OF INLINE: member-specification-opt */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_member_Hspecification_Hopt;
			}
			/* END OF INLINE: member-specification-opt */
		}
		UNREACHED;
	case 77:
		{
			TYPE ZIt1;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv1;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2443 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2450 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2457 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1657 "syntax.act"

    IGNORE empty_decl ( (ZIds), (ZIt), (ZIbt), (ZIt1), (ZIcv1), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 2468 "syntax2.c"
			}
			/* END OF ACTION: declare_member_empty */
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: member-specification-opt */
			goto ZL2_member_Hspecification_Hopt;
			/* END OF INLINE: member-specification-opt */
		}
		UNREACHED;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRclose_Hround_Hx(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 39:
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

		/* BEGINNING OF ACTION: lex_close_round */
		{
#line 376 "syntax.act"
 (ZIt) = lex_close_Hround ; 
#line 2510 "syntax2.c"
		}
		/* END OF ACTION: lex_close_round */
		/* BEGINNING OF ACTION: expected */
		{
#line 1981 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 2520 "syntax2.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRtypeid_Hexpression(int ZIop, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		int ZIn1;
		int ZIm1;
		EXP ZIc;

		/* BEGINNING OF ACTION: sizeof_begin */
		{
#line 2021 "syntax.act"

    suppress_usage++ ;
#line 2544 "syntax2.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 1996 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 2552 "syntax2.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2000 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 2560 "syntax2.c"
		}
		/* END OF ACTION: no_type_defns */
		switch (CURRENT_TERMINAL) {
		case 65:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 558 */
		{
			{
				TYPE ZIt;
				int ZIm2;

				/* BEGINNING OF ACTION: is_type_id_true */
				{
#line 2105 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
#line 2582 "syntax2.c"
				}
				/* END OF ACTION: is_type_id_true */
				if (!ZI0)
					goto ZL3;
				ZRtype_Hid (&ZIt, &ZIm2);
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
				/* BEGINNING OF ACTION: exp_typeid_type */
				{
#line 837 "syntax.act"

    (ZIc) = make_typeid_type ( (ZIop), (ZIt), (ZIm2) ) ;
#line 2603 "syntax2.c"
				}
				/* END OF ACTION: exp_typeid_type */
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
			case 286: case 298: case 299: case 324:
			case 331: case 347:
				{
					EXP ZIa;
					int ZIn2;

					ZRexpression (&ZIa);
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
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2647 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: exp_typeid_exp */
					{
#line 833 "syntax.act"

    (ZIc) = make_typeid_exp ( (ZIop), (ZIa), (ZIn2) ) ;
#line 2655 "syntax2.c"
					}
					/* END OF ACTION: exp_typeid_exp */
				}
				break;
			default:
				goto ZL1;
			}
		ZL2:;
		}
		/* END OF INLINE: 558 */
		/* BEGINNING OF ACTION: sizeof_end */
		{
#line 2025 "syntax.act"

    suppress_usage-- ;
#line 2671 "syntax2.c"
		}
		/* END OF ACTION: sizeof_end */
		ZIe = ZIc;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1170(EXP ZI1168, EXP *ZO1169)
{
	EXP ZI1169;

ZL2_1170:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			EXP ZIc;

			ZIp = ZI1168;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 327 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 2702 "syntax2.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1909 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 2712 "syntax2.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1890 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 2720 "syntax2.c"
			}
			/* END OF ACTION: decl_hash_elif */
			ZRmember_Hcond_Hbody ();
			/* BEGINNING OF INLINE: 1170 */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				ZI1168 = ZIp;
				goto ZL2_1170;
			}
			/* END OF INLINE: 1170 */
		}
		UNREACHED;
	default:
		{
			ZI1169 = ZI1168;
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
	*ZO1169 = ZI1169;
}

void
ZRsizeof_Hexpression(int ZIop, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		int ZIn1;
		int ZIm1;
		EXP ZIc;

		/* BEGINNING OF ACTION: sizeof_begin */
		{
#line 2021 "syntax.act"

    suppress_usage++ ;
#line 2769 "syntax2.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 1996 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 2777 "syntax2.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2000 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 2785 "syntax2.c"
		}
		/* END OF ACTION: no_type_defns */
		/* BEGINNING OF INLINE: 596 */
		{
			switch (CURRENT_TERMINAL) {
			case 170:
				{
					int ZI1417;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_alignof */
					{
#line 382 "syntax.act"
 (ZI1417) = lex_alignof ; 
#line 2804 "syntax2.c"
					}
					/* END OF ACTION: lex_alignof */
					ZRsizeof_Hexpression (ZI1417, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2817 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2825 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2833 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2841 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 83:
				{
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZR1287 (&ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2864 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2872 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2880 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2888 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 23:
				{
					EXP ZI1282;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: complex-exp */
					{
#line 341 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1282 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2909 "syntax2.c"
					}
					/* END OF EXTRACT: complex-exp */
					ADVANCE_LEXER;
					ZR1243 (ZI1282, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2923 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2931 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2939 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2947 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 25:
				{
					TYPE ZI1268;
					BASE_TYPE ZIbt;
					CV_SPEC ZIcv;
					TYPE ZI1431;
					SID_LIST_EXP ZIp;
					EXP ZI1285;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: complex-type */
					{
#line 355 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1268 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 2975 "syntax2.c"
					}
					/* END OF EXTRACT: complex-type */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: btype_none */
					{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2983 "syntax2.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2990 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1307 "syntax.act"

    (ZI1431) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2999 "syntax2.c"
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

    (ZI1285) = make_func_cast_exp ( (ZI1431), (ZIp) ) ;
#line 3025 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1243 (ZI1285, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3038 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3046 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3054 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3062 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 130:
				{
					TYPE ZI1420;
					EXP ZI1421;
					int ZIn;
					EXP ZI1274;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1420, &ZI1421, &ZIn);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_const_cast */
					{
#line 614 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_const_cast_exp ( (ZI1420), (ZI1421), (ZIn) ) ;
#line 3090 "syntax2.c"
					}
					/* END OF ACTION: exp_const_cast */
					ZR1243 (ZI1274, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3103 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3111 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3119 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3127 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 132:
				{
					TYPE ZI1426;
					EXP ZI1427;
					int ZIn;
					EXP ZI1277;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1426, &ZI1427, &ZIn);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_dynamic_cast */
					{
#line 640 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1277) = make_dynamic_cast_exp ( (ZI1426), (ZI1427), (ZIn) ) ;
#line 3155 "syntax2.c"
					}
					/* END OF ACTION: exp_dynamic_cast */
					ZR1243 (ZI1277, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3168 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3176 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3184 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3192 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 210:
				{
					EXP ZI1280;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_ellipsis */
					{
#line 644 "syntax.act"

    (ZI1280) = make_ellipsis_exp () ;
#line 3211 "syntax2.c"
					}
					/* END OF ACTION: exp_ellipsis */
					ZR1243 (ZI1280, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3224 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3232 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3240 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3248 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 9:
				{
					NAMESPACE ZIns;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: full-name */
					{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3266 "syntax2.c"
					}
					/* END OF EXTRACT: full-name */
					ADVANCE_LEXER;
					ZR1270 (&ZIns, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3280 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3288 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3296 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3304 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 61:
				{
					EXP ZI1410;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1410);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_predec */
					{
#line 771 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_minus_Hminus, (ZI1410) ) ;
#line 3328 "syntax2.c"
					}
					/* END OF ACTION: exp_predec */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3336 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3344 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3352 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3360 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 8:
				{
					NAMESPACE ZIns;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: nested-name */
					{
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3378 "syntax2.c"
					}
					/* END OF EXTRACT: nested-name */
					ADVANCE_LEXER;
					ZR1269 (&ZIns, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3392 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3400 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3408 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3416 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 65:
				{
					ADVANCE_LEXER;
					ZR1432 (&ZIop, &ZIn1, &ZIm1, &ZIc);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 71:
				{
					EXP ZI1409;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1409);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_preinc */
					{
#line 775 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_plus_Hplus, (ZI1409) ) ;
#line 3450 "syntax2.c"
					}
					/* END OF ACTION: exp_preinc */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3458 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3466 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3474 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3482 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 145:
				{
					TYPE ZI1422;
					EXP ZI1423;
					int ZIn;
					EXP ZI1275;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1422, &ZI1423, &ZIn);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_reinterpret_cast */
					{
#line 788 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1275) = make_reinterp_cast_exp ( (ZI1422), (ZI1423), (ZIn) ) ;
#line 3510 "syntax2.c"
					}
					/* END OF ACTION: exp_reinterpret_cast */
					ZR1243 (ZI1275, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3523 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3531 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3539 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3547 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 116:
				{
					int ZI1416;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_sizeof */
					{
#line 389 "syntax.act"
 (ZI1416) = lex_sizeof ; 
#line 3565 "syntax2.c"
					}
					/* END OF ACTION: lex_sizeof */
					ZRsizeof_Hexpression (ZI1416, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3578 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3586 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3594 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3602 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 78:
				{
					EXP ZI1411;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1411);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_indir */
					{
#line 682 "syntax.act"

    (ZIa) = make_indir_exp ( (ZI1411) ) ;
#line 3626 "syntax2.c"
					}
					/* END OF ACTION: exp_indir */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3634 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3642 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3650 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3658 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 146:
				{
					TYPE ZI1424;
					EXP ZI1425;
					int ZIn;
					EXP ZI1276;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1424, &ZI1425, &ZIn);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_static_cast */
					{
#line 813 "syntax.act"

    (ZI1276) = make_static_cast_exp ( (ZI1424), (ZI1425), (ZIn) ) ;
#line 3685 "syntax2.c"
					}
					/* END OF ACTION: exp_static_cast */
					ZR1243 (ZI1276, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3698 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3706 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3714 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3722 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 148:
				{
					EXP ZI1279;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_this */
					{
#line 817 "syntax.act"

    (ZI1279) = make_this_exp () ;
#line 3741 "syntax2.c"
					}
					/* END OF ACTION: exp_this */
					ZR1243 (ZI1279, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3754 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3762 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3770 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3778 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 152:
				{
					int ZI1419;
					EXP ZI1273;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_typeid */
					{
#line 390 "syntax.act"
 (ZI1419) = lex_typeid ; 
#line 3797 "syntax2.c"
					}
					/* END OF ACTION: lex_typeid */
					ZRtypeid_Hexpression (ZI1419, &ZI1273);
					ZR1243 (ZI1273, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3811 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3819 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3827 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3835 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 331:
				{
					int ZI1418;
					EXP ZI1272;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_vtable */
					{
#line 391 "syntax.act"
 (ZI1418) = lex_vtable ; 
#line 3854 "syntax2.c"
					}
					/* END OF ACTION: lex_vtable */
					ZRtypeid_Hexpression (ZI1418, &ZI1272);
					ZR1243 (ZI1272, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3868 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3876 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3884 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3892 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 33:
				{
					EXP ZI1412;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

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
					ZRcast_Hexpression (&ZI1412);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_ref */
					{
#line 783 "syntax.act"

    (ZIa) = make_ref_exp ( (ZI1412), 0 ) ;
#line 3928 "syntax2.c"
					}
					/* END OF ACTION: exp_ref */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3936 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3944 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3952 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3960 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
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
					TYPE ZI1429;
					SID_LIST_EXP ZIp;
					EXP ZI1283;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

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
#line 3992 "syntax2.c"
					}
					/* END OF ACTION: type_pre */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3999 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1307 "syntax.act"

    (ZI1429) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4008 "syntax2.c"
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

    (ZI1283) = make_func_cast_exp ( (ZI1429), (ZIp) ) ;
#line 4034 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1243 (ZI1283, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4047 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4055 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4063 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4071 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 17: case 18: case 19: case 20:
			case 21: case 22: case 135: case 150:
				{
					EXP ZI1278;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRliteral (&ZI1278);
					ZR1243 (ZI1278, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4096 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4104 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4112 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4120 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 62:
				{
					EXP ZI1413;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

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
					ZRcast_Hexpression (&ZI1413);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_not */
					{
#line 742 "syntax.act"

    (ZIa) = make_not_exp ( (ZI1413) ) ;
#line 4156 "syntax2.c"
					}
					/* END OF ACTION: exp_not */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4164 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4172 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4180 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4188 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 1: case 3: case 5: case 6:
			case 141:
				{
					IDENTIFIER ZIid;
					EXP ZI1286;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRunqualified_Hid (&ZIid);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_identifier */
					{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 4213 "syntax2.c"
					}
					/* END OF ACTION: exp_identifier */
					ZR1243 (ZI1286, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4226 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4234 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4242 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4250 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 2: case 7:
				{
					IDENTIFIER ZIid;
					TYPE ZI1268;
					BASE_TYPE ZIbt;
					CV_SPEC ZIcv;
					TYPE ZI1430;
					SID_LIST_EXP ZIp;
					EXP ZI1284;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

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
#line 4281 "syntax2.c"
					}
					/* END OF ACTION: type_name */
					/* BEGINNING OF ACTION: btype_none */
					{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4288 "syntax2.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4295 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1307 "syntax.act"

    (ZI1430) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4304 "syntax2.c"
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

    (ZI1284) = make_func_cast_exp ( (ZI1430), (ZIp) ) ;
#line 4330 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1243 (ZI1284, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4343 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4351 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4359 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4367 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 131: case 140:
				{
					int ZIb;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF ACTION: bool_false */
					{
#line 2035 "syntax.act"
 (ZIb) = 0 ; 
#line 4384 "syntax2.c"
					}
					/* END OF ACTION: bool_false */
					ZR1433 (&ZIb, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4397 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4405 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4413 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4421 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 43: case 59: case 69: case 85:
				{
					int ZI1414;
					EXP ZI1415;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF ACTION: lex_crt */
					{
#line 375 "syntax.act"
 (ZI1414) = crt_lex_token ; 
#line 4439 "syntax2.c"
					}
					/* END OF ACTION: lex_crt */
					ZRunary_Hoperator ();
					ZRcast_Hexpression (&ZI1415);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_unary */
					{
#line 841 "syntax.act"

    (ZIa) = make_uminus_exp ( (ZI1414), (ZI1415) ) ;
#line 4453 "syntax2.c"
					}
					/* END OF ACTION: exp_unary */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2004 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4461 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2008 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4469 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1312 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4477 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 809 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4485 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 596 */
		/* BEGINNING OF ACTION: sizeof_end */
		{
#line 2025 "syntax.act"

    suppress_usage-- ;
#line 4500 "syntax2.c"
		}
		/* END OF ACTION: sizeof_end */
		ZIe = ZIc;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRunqualified_Hid(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 5:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 219 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4528 "syntax2.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4539 "syntax2.c"
			}
			/* END OF ACTION: namespace_complex */
		}
		break;
	case 1:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 203 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4553 "syntax2.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZIuid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4564 "syntax2.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	case 3:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 211 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4578 "syntax2.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZIuid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4589 "syntax2.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	case 6:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 225 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 4607 "syntax2.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4618 "syntax2.c"
			}
			/* END OF ACTION: namespace_complex */
		}
		break;
	case 141:
		{
			IDENTIFIER ZIuid;

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
#line 4639 "syntax2.c"
			}
			/* END OF ACTION: namespace_complex */
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
ZRtry_Hblock(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		int ZIr;
		EXP ZIa;
		EXP ZIb;
		EXP ZIc;

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
#line 4691 "syntax2.c"
		}
		/* END OF ACTION: reach_check */
		/* BEGINNING OF ACTION: stmt_try_begin */
		{
#line 1023 "syntax.act"

    (ZIa) = begin_try_stmt ( 0 ) ;
#line 4699 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_begin */
		ZRcompound_Hstatement (&ZIb);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_try_cont */
		{
#line 1035 "syntax.act"

    (ZIc) = cont_try_stmt ( (ZIa), (ZIb) ) ;
#line 4712 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_cont */
		ZRhandler_Hseq_Hopt (ZIc);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4724 "syntax2.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_try_end */
		{
#line 1039 "syntax.act"

    (ZIe) = end_try_stmt ( (ZIc), 0 ) ;
#line 4732 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_end */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4740 "syntax2.c"
		}
		/* END OF ACTION: stmt_label_clear */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR920(TYPE *ZIs, BASE_TYPE *ZIb1, TYPE *ZIt1, CV_SPEC *ZIcv1, DECL_SPEC *ZIds1, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZI1388;
		TYPE ZI1389;
		CV_SPEC ZI1390;
		DECL_SPEC ZI1391;
		BASE_TYPE ZIb2;
		TYPE ZIt2;
		CV_SPEC ZIcv2;
		DECL_SPEC ZIds2;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2063 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 4779 "syntax2.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (*ZIs, &ZI1388, &ZI1389, &ZI1390, &ZI1391);
		ZR920 (ZIs, &ZI1388, &ZI1389, &ZI1390, &ZI1391, &ZIb2, &ZIt2, &ZIcv2, &ZIds2);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: btype_join */
		{
#line 1241 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 4799 "syntax2.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 1296 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 4815 "syntax2.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 1211 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 4825 "syntax2.c"
		}
		/* END OF ACTION: cv_join */
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (*ZIds1) | (ZIds2) ) ;
#line 4836 "syntax2.c"
		}
		/* END OF ACTION: dspec_join */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			ZIbt = *ZIb1;
			ZIt = *ZIt1;
			ZIcv = *ZIcv1;
			ZIds = *ZIds1;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
	*ZOds = ZIds;
}

void
ZRtemplate_Hdeclaration(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
{
	EXP ZIe;

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
#line 4894 "syntax2.c"
		}
		/* END OF ACTION: template_params */
		/* BEGINNING OF ACTION: template_type */
		{
#line 1815 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 4902 "syntax2.c"
		}
		/* END OF ACTION: template_type */
		ZRdeclaration (ZIt1, ZIds, &ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: template_end */
		{
#line 1819 "syntax.act"

    end_template ( (ZIp) ) ;
#line 4915 "syntax2.c"
		}
		/* END OF ACTION: template_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4923 "syntax2.c"
		}
		/* END OF ACTION: rescan_token */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
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
		IDENTIFIER ZI1375;
		TYPE ZI1376;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 2115 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 4954 "syntax2.c"
		}
		/* END OF ACTION: is_parameter */
		if (!ZI0)
			goto ZL2;
		ZRdeclarator_Hid (&ZI1375);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZI1376) = NULL_type ;
#line 4969 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_posn */
		{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1375) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 4978 "syntax2.c"
		}
		/* END OF ACTION: declarator_posn */
		ZR1164 (ZI1376, ZI1375, &ZIt, &ZIid);
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
			ZR1374 (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 333:
		{
			IDENTIFIER ZI1373;
			int ZIw;
			TYPE ZI1379;
			IDENTIFIER ZI1380;

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

    (ZI1373) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5023 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIw) = 1 ; 
#line 5030 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1373) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5041 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZI1379);
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
#line 5056 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1380) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5067 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1380) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5076 "syntax2.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1164 (ZI1379, ZI1380, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZI1377;
			IDENTIFIER ZI1378;

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
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1377) ) ;
#line 5116 "syntax2.c"
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
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1378) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5140 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1378) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5149 "syntax2.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1164 (ZI1377, ZI1378, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 10: case 11: case 33: case 78:
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
#line 1383 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 5175 "syntax2.c"
			}
			/* END OF ACTION: type_build */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 5187 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5198 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5207 "syntax2.c"
			}
			/* END OF ACTION: declarator_posn */
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

/* END OF FILE */
