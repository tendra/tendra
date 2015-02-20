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
#line 178 "syntax.act"


/* $Id$ */

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
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		DECL_SPEC ZIa;
		int ZIv;
		NAMESPACE ZIns;
		IDENTIFIER ZIaid;
		IDENTIFIER ZIid;

		/* BEGINNING OF INLINE: 845 */
		{
			switch (CURRENT_TERMINAL) {
			case 155:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: bool_true */
					{
#line 2040 "syntax.act"
 (ZIv) = 1 ; 
#line 123 "syntax2.c"
					}
					/* END OF ACTION: bool_true */
					ZR1330 (&ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 142: case 143: case 144:
				{
					ZRaccess_Hspecifier (&ZIa);
					ZR1329 (&ZIv);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: access_none */
					{
#line 1442 "syntax.act"
 (ZIa) = dspec_none ; 
#line 149 "syntax2.c"
					}
					/* END OF ACTION: access_none */
					/* BEGINNING OF ACTION: bool_false */
					{
#line 2039 "syntax.act"
 (ZIv) = 0 ; 
#line 156 "syntax2.c"
					}
					/* END OF ACTION: bool_false */
				}
				break;
			}
		}
		/* END OF INLINE: 845 */
		ZRany_Hnested_Hname_Hopt (&ZIns);
		ZRany_Hclass_Hname (&ZIaid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: namespace_id */
		{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIaid), 0 ) ;
    last_namespace = (ZIns) ;
#line 176 "syntax2.c"
		}
		/* END OF ACTION: namespace_id */
		/* BEGINNING OF ACTION: class_base */
		{
#line 1504 "syntax.act"

    add_base_class ( (ZIid), (ZIa), (ZIv) ) ;
#line 184 "syntax2.c"
		}
		/* END OF ACTION: class_base */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRinit_Hdeclarator(DECL_SPEC ZIds, BASE_TYPE ZIbt, TYPE ZIp, ACCESS_LIST ZIr)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIt;
		IDENTIFIER ZIid;
		int ZIc;
		IDENTIFIER ZId;
		EXP ZIe;

		ZRdeclarator (ZIp, &ZIt, &ZIid, &ZIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_id */
		{
#line 1598 "syntax.act"

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
#line 1466 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 242 "syntax2.c"
		}
		/* END OF ACTION: access_check_ret */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1461 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 252 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		ZRinitialiser_Hopt (ZIc, ZId, &ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1750 "syntax.act"

    int def = init_object ( (ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 266 "syntax2.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1461 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 276 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1701 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 284 "syntax2.c"
		}
		/* END OF ACTION: declarator_end */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRdeclaration(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
{
	EXP ZIe;

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
#line 2067 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 319 "syntax2.c"
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
#line 1550 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 338 "syntax2.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1254 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 569 "syntax.act"

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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 134: case 147:
		{
			ZRtemplate_Hdeclaration (ZIt, ZIds, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
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
			CV_SPEC ZI1255;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 391 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1266 "syntax.act"

    (ZIt1) = NULL_type ;
#line 399 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZI1255) = cv_none ; 
#line 406 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			ZR1256 (&ZIt, &ZIds, &ZIbt, &ZIt1, &ZI1255, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 126: case 139: case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1849 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 424 "syntax2.c"
			}
			/* END OF ACTION: template_check */
			ZRdeclaration_Hother (&ZIe);
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
ZR1286(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 141: case 147:
		{
			ZR1270 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
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
#line 2040 "syntax.act"
 (ZIb) = 1 ; 
#line 469 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			ZR1432 (&ZIb, &ZIe);
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
ZRinitialiser_Hexp_Hlist(IDENTIFIER ZId, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;
		SID_LIST_EXP ZIq;

		ZRinitialiser_Hexpression (&ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1461 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 516 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF INLINE: 1005 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					ZRinitialiser_Hexp_Hlist (ZId, &ZIq);
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
#line 550 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 539 "syntax2.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1005 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 554 "syntax.act"

    CONS_exp ( (ZIe), (ZIq), (ZIp) ) ;
#line 552 "syntax2.c"
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
#line 1123 "syntax.act"
 unreached_code = 0 ; 
#line 579 "syntax2.c"
			}
			/* END OF ACTION: reach_set */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_reach */
			{
#line 1067 "syntax.act"

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
#line 1124 "syntax.act"
 unreached_code = 1 ; 
#line 606 "syntax2.c"
			}
			/* END OF ACTION: reach_unset */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_unreach */
			{
#line 1071 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 0 ) ;
#line 619 "syntax2.c"
			}
			/* END OF ACTION: stmt_unreach */
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
ZR1288(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIt;
		int ZIn;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_type_id_false */
		{
#line 2104 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 656 "syntax2.c"
		}
		/* END OF ACTION: is_type_id_false */
		if (!ZI0)
			goto ZL2;
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
		ZRcast_Hexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_cast */
		{
#line 605 "syntax.act"

    /* n is the number of type definitions in t */
    (ZIe) = make_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 683 "syntax2.c"
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
	case 330: case 346:
		{
			EXP ZIa;
			EXP ZI1280;

			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 755 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 716 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 758 "syntax.act"

    (ZI1280) = make_paren_exp ( (ZIa) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 730 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1242 (ZI1280, &ZIe);
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
ZRfull_Hqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		NAMESPACE ZIns;
		IDENTIFIER ZItid;

		switch (CURRENT_TERMINAL) {
		case 9:
			/* BEGINNING OF EXTRACT: full-name */
			{
#line 256 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 777 "syntax2.c"
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
#line 237 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 799 "syntax2.c"
					}
					/* END OF EXTRACT: template-type */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 211 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 812 "syntax2.c"
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
#line 488 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZIns) ;
#line 829 "syntax2.c"
		}
		/* END OF ACTION: namespace_full */
		/* BEGINNING OF ACTION: namespace_id */
		{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 838 "syntax2.c"
		}
		/* END OF ACTION: namespace_id */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
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
#line 1167 "syntax.act"

    (ZIcns) = ctor_begin () ;
#line 868 "syntax2.c"
			}
			/* END OF ACTION: ctor_begin */
			/* BEGINNING OF INLINE: 1022 */
			{
				switch (CURRENT_TERMINAL) {
				case 1: case 2: case 3: case 4:
				case 7: case 8: case 9: case 65:
				case 83:
					{
						ZRmem_Hinitialiser_Hlist (ZIcns);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: bool_true */
						{
#line 2040 "syntax.act"
 (ZIb) = 1 ; 
#line 887 "syntax2.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2039 "syntax.act"
 (ZIb) = 0 ; 
#line 898 "syntax2.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 1022 */
			/* BEGINNING OF ACTION: ctor_end */
			{
#line 1171 "syntax.act"

    (ZIe) = ctor_end ( (ZIcns), (ZIc), (ZIb) ) ;
#line 911 "syntax2.c"
			}
			/* END OF ACTION: ctor_end */
			/* BEGINNING OF ACTION: exp_none */
			{
#line 569 "syntax.act"

    (ZId) = NULL_exp ;
#line 919 "syntax2.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: ctor_none */
			{
#line 1179 "syntax.act"

    (ZId) = NULL_exp ;
    (ZIe) = ctor_none ( (ZIc), &(ZId) ) ;
#line 932 "syntax2.c"
			}
			/* END OF ACTION: ctor_none */
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
	*ZOd = ZId;
}

void
ZRunqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
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
#line 237 "syntax.act"

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
#line 211 "syntax.act"

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
#line 497 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1005 "syntax2.c"
		}
		/* END OF ACTION: namespace_simple */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRexception_Hdeclaration(int ZIn1, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIs;
		BASE_TYPE ZIb1;
		TYPE ZI1603;
		CV_SPEC ZI1604;
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
#line 2114 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 1046 "syntax2.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: type_none */
		{
#line 1266 "syntax.act"

    (ZIs) = NULL_type ;
#line 1056 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		ZRtype_Hspecifier (ZIs, &ZIb1, &ZI1603, &ZI1604);
		ZR887 (&ZIb1, &ZI1603, &ZI1604, &ZIbt, &ZIt1, &ZIcv1);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1534 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 1069 "syntax2.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1561 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds2) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1080 "syntax2.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1694 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1088 "syntax2.c"
		}
		/* END OF ACTION: declarator_start */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2012 "syntax.act"

    (ZIn2) = no_type_defns - (ZIn1) ;
#line 1101 "syntax2.c"
		}
		/* END OF ACTION: diff_type_defns */
		/* BEGINNING OF ACTION: declare_except */
		{
#line 1683 "syntax.act"

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
#line 1689 "syntax.act"

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
	SAVE_LEXER (355);
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
#line 1424 "syntax.act"
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
#line 1425 "syntax.act"
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
#line 1426 "syntax.act"
 (ZIkey) = btype_union ; 
#line 1197 "syntax2.c"
			}
			/* END OF ACTION: key_union */
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
	*ZOkey = ZIkey;
}

void
ZRinitialiser_Hlist(IDENTIFIER ZId, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIb;
		EXP ZIa;
		SID_LIST_EXP ZIq;

		ZRinitialiser_Hclause (ZId, &ZIb);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_location */
		{
#line 698 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIb), (ZIa) ) ;
#line 1238 "syntax2.c"
		}
		/* END OF ACTION: exp_location */
		/* BEGINNING OF INLINE: 1002 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					ZR1003 (&ZId, &ZIq);
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
#line 550 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 1261 "syntax2.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1002 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 554 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1274 "syntax2.c"
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
ZR1163(TYPE ZI1159, IDENTIFIER ZI1160, TYPE *ZO1161, IDENTIFIER *ZO1162)
{
	TYPE ZI1161;
	IDENTIFIER ZI1162;

ZL2_1163:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 332:
		{
			IDENTIFIER ZIid;
			QUALIFIER ZIi;
			int ZIb;
			TYPE ZIq;
			TYPE ZIt;

			ZIid = ZI1160;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 526 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1309 "syntax2.c"
			}
			/* END OF ACTION: qual_get */
			ZRabstract_Hdeclarator_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 531 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1323 "syntax2.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1387 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1159) ) ? (ZIq) : inject_pre_type ( (ZI1159), (ZIq), 0 ) ) ;
#line 1331 "syntax2.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 1163 */
			ZI1159 = ZIt;
			ZI1160 = ZIid;
			goto ZL2_1163;
			/* END OF INLINE: 1163 */
		}
		UNREACHED;
	default:
		{
			ZI1161 = ZI1159;
			ZI1162 = ZI1160;
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
	*ZO1161 = ZI1161;
	*ZO1162 = ZI1162;
}

void
ZRmember_Hcond_Hhead(EXP *ZO1168)
{
	EXP ZI1168;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIc;
		EXP ZIp;

		switch (CURRENT_TERMINAL) {
		case 26:
			/* BEGINNING OF EXTRACT: hash-if */
			{
#line 327 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1378 "syntax2.c"
			}
			/* END OF EXTRACT: hash-if */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: cond_hash_if */
		{
#line 1907 "syntax.act"

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
    (ZIp) = c ;
#line 1393 "syntax2.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: decl_hash_if */
		{
#line 1890 "syntax.act"

    target_decl ( lex_if, (ZIc) ) ;
#line 1401 "syntax2.c"
		}
		/* END OF ACTION: decl_hash_if */
		ZRmember_Hcond_Hbody ();
		ZR1169 (ZIp, &ZI1168);
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
	*ZO1168 = ZI1168;
}

void
parse_tok_type(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZIbt;
		TYPE ZIp;
		CV_SPEC ZIcv;
		TYPE ZIq;

		ZRtype_Hspecifier_Hseq (&ZIbt, &ZIp, &ZIcv);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_complete */
		{
#line 1311 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 1444 "syntax2.c"
		}
		/* END OF ACTION: type_complete */
		ZRabstract_Hdeclarator_Hopt (ZIq, &ZIt);
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
	*ZOt = ZIt;
}

void
ZR1291(EXP *ZI1289, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 42:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 554 "syntax.act"

    CONS_exp ( (*ZI1289), (ZIq), (ZIp) ) ;
#line 1483 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 609 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1491 "syntax2.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	default:
		{
			ZIe = *ZI1289;
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
ZRmaxmin_Hexpression(EXP *ZO1213)
{
	EXP ZI1213;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRequality_Hexpression (&ZIe);
		ZR1214 (ZIe, &ZI1213);
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
	*ZO1213 = ZI1213;
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
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_initialiser */
			{
#line 690 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 1602 "syntax2.c"
			}
			/* END OF ACTION: exp_initialiser */
			/* BEGINNING OF ACTION: id_none */
			{
#line 449 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1612 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: ctor_initialise */
			{
#line 1175 "syntax.act"

    ctor_initialise ( (ZIcns), (ZIid), (ZIe) ) ;
#line 1620 "syntax2.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIaid), 0 ) ;
    last_namespace = (ZIns) ;
#line 1648 "syntax2.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 526 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1657 "syntax2.c"
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
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: qual_set */
			{
#line 531 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1684 "syntax2.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: exp_initialiser */
			{
#line 690 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 1692 "syntax2.c"
			}
			/* END OF ACTION: exp_initialiser */
			/* BEGINNING OF ACTION: ctor_initialise */
			{
#line 1175 "syntax.act"

    ctor_initialise ( (ZIcns), (ZIid), (ZIe) ) ;
#line 1700 "syntax2.c"
			}
			/* END OF ACTION: ctor_initialise */
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
ZR1292(EXP *ZIa, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	switch (CURRENT_TERMINAL) {
	case 42:
		{
			SID_LIST_EXP ZIq;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 554 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1737 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
		}
		break;
	default:
		{
			SID_LIST_EXP ZIq;

			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 550 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 1751 "syntax2.c"
			}
			/* END OF ACTION: list_exp_null */
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 554 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1759 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
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
ZRinset_Hflow_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 346:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR1293 (&ZIe);
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
	*ZOe = ZIe;
}

void
ZR1293(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 298:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_set */
			{
#line 809 "syntax.act"

    (ZIe) = make_set_exp ( (ZIa) ) ;
#line 1826 "syntax2.c"
			}
			/* END OF ACTION: exp_set */
			switch (CURRENT_TERMINAL) {
			case 347:
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 849 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 1853 "syntax2.c"
			}
			/* END OF ACTION: exp_unused */
			switch (CURRENT_TERMINAL) {
			case 347:
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
ZRdelete_Hoperator(int *ZOop)
{
	int ZIop;

	if ((CURRENT_TERMINAL) == 355) {
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
		ZR1433 (&ZIop);
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
#line 2039 "syntax.act"
 (ZIe) = 0 ; 
#line 1929 "syntax2.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: template_params */
			{
#line 1827 "syntax.act"

    (ZIp) = template_params ( (ZIe) ) ;
    RESCAN_LEXER ;
#line 1938 "syntax2.c"
			}
			/* END OF ACTION: template_params */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
#line 1946 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1534 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1953 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: template_type */
			{
#line 1819 "syntax.act"

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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_param_name */
			{
#line 1840 "syntax.act"

    (ZId) = make_template_param ( (ZIt1), (ZIid) ) ;
    UNUSED ( (ZIds) ) ;
#line 1982 "syntax2.c"
			}
			/* END OF ACTION: template_param_name */
			/* BEGINNING OF INLINE: 1121 */
			{
				switch (CURRENT_TERMINAL) {
				case 36:
					{
						IDENTIFIER ZIaid;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: default_arg_begin */
						{
#line 2017 "syntax.act"

    in_default_arg++ ;
#line 1998 "syntax2.c"
						}
						/* END OF ACTION: default_arg_begin */
						ZRany_Hqualified_Hid (&ZIaid);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: namespace_simple */
						{
#line 497 "syntax.act"

    (ZItid) = (ZIaid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2013 "syntax2.c"
						}
						/* END OF ACTION: namespace_simple */
						/* BEGINNING OF ACTION: default_arg_end */
						{
#line 2021 "syntax.act"

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
#line 449 "syntax.act"

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
			/* END OF INLINE: 1121 */
			/* BEGINNING OF ACTION: template_init_name */
			{
#line 1845 "syntax.act"

    init_template_param ( (ZId), (ZItid) ) ;
#line 2048 "syntax2.c"
			}
			/* END OF ACTION: template_init_name */
			/* BEGINNING OF ACTION: template_end */
			{
#line 1823 "syntax.act"

    end_template ( (ZIp) ) ;
#line 2056 "syntax2.c"
			}
			/* END OF ACTION: template_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

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

			/* BEGINNING OF INLINE: 1119 */
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
			/* END OF INLINE: 1119 */
			ZRtemplate_Hparam_Hname (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: template_param_type */
			{
#line 1832 "syntax.act"

    (ZId) = make_type_param ( (ZIid) ) ;
#line 2102 "syntax2.c"
			}
			/* END OF ACTION: template_param_type */
			/* BEGINNING OF INLINE: 1120 */
			{
				switch (CURRENT_TERMINAL) {
				case 36:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: default_arg_begin */
						{
#line 2017 "syntax.act"

    in_default_arg++ ;
#line 2116 "syntax2.c"
						}
						/* END OF ACTION: default_arg_begin */
						parse_tok_type (&ZIt);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: default_arg_end */
						{
#line 2021 "syntax.act"

    in_default_arg-- ;
#line 2129 "syntax2.c"
						}
						/* END OF ACTION: default_arg_end */
						/* BEGINNING OF ACTION: type_check */
						{
#line 1320 "syntax.act"

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
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
#line 2149 "syntax2.c"
						}
						/* END OF ACTION: type_none */
					}
					break;
				}
			}
			/* END OF INLINE: 1120 */
			/* BEGINNING OF ACTION: template_init_type */
			{
#line 1836 "syntax.act"

    init_type_param ( (ZId), (ZIt) ) ;
#line 2162 "syntax2.c"
			}
			/* END OF ACTION: template_init_type */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1970 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2183 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: decl_none */
		{
#line 1163 "syntax.act"

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
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_member_Hspecification_Hopt:;
	{
		BASE_TYPE ZI1337;
		TYPE ZI1338;
		CV_SPEC ZI1339;
		DECL_SPEC ZI1340;
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;
		DECL_SPEC ZIds2;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2067 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2223 "syntax2.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL3;
		ZRdecl_Hspecifier (ZIt, &ZI1337, &ZI1338, &ZI1339, &ZI1340);
		ZR919 (&ZIt, &ZI1337, &ZI1338, &ZI1339, &ZI1340, &ZIbt, &ZIt1, &ZIcv1, &ZIds1);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1550 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2242 "syntax2.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1341 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		/* BEGINNING OF INLINE: member-specification-opt */
		if ((CURRENT_TERMINAL) == 355) {
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
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access_set */
			{
#line 1444 "syntax.act"
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
			if ((CURRENT_TERMINAL) == 355) {
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
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2320 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1266 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2328 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2335 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1534 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2342 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1550 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2353 "syntax2.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1561 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 2364 "syntax2.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1383 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 2372 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1470 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2380 "syntax2.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2040 "syntax.act"
 (ZIf) = 1 ; 
#line 2387 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1694 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2395 "syntax2.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator (ZIds3, ZIt3, ZIbt, ZIr, ZIf, &ZId);
			ZR1094 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZId);
			/* BEGINNING OF INLINE: member-specification-opt */
			if ((CURRENT_TERMINAL) == 355) {
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
#line 1849 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2418 "syntax2.c"
			}
			/* END OF ACTION: template_check */
			ZR1342 ();
			/* BEGINNING OF INLINE: member-specification-opt */
			if ((CURRENT_TERMINAL) == 355) {
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
#line 1266 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2443 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2450 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2457 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1661 "syntax.act"

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
	SAVE_LEXER (355);
	return;
}

void
ZR1169(EXP ZI1167, EXP *ZO1168)
{
	EXP ZI1168;

ZL2_1169:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			EXP ZIc;

			ZIp = ZI1167;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 331 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 2504 "syntax2.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1913 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 2514 "syntax2.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1894 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 2522 "syntax2.c"
			}
			/* END OF ACTION: decl_hash_elif */
			ZRmember_Hcond_Hbody ();
			/* BEGINNING OF INLINE: 1169 */
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				ZI1167 = ZIp;
				goto ZL2_1169;
			}
			/* END OF INLINE: 1169 */
		}
		UNREACHED;
	default:
		{
			ZI1168 = ZI1167;
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
	*ZO1168 = ZI1168;
}

void
ZRclose_Hround_Hx(void)
{
	if ((CURRENT_TERMINAL) == 355) {
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
#line 380 "syntax.act"
 (ZIt) = lex_close_Hround ; 
#line 2577 "syntax2.c"
		}
		/* END OF ACTION: lex_close_round */
		/* BEGINNING OF ACTION: expected */
		{
#line 1985 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 2587 "syntax2.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRtypeid_Hexpression(int ZIop, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIn1;
		int ZIm1;
		EXP ZIc;

		/* BEGINNING OF ACTION: sizeof_begin */
		{
#line 2025 "syntax.act"

    suppress_usage++ ;
#line 2611 "syntax2.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 2000 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 2619 "syntax2.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2004 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 2627 "syntax2.c"
		}
		/* END OF ACTION: no_type_defns */
		switch (CURRENT_TERMINAL) {
		case 65:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 557 */
		{
			{
				TYPE ZIt;
				int ZIm2;

				/* BEGINNING OF ACTION: is_type_id_true */
				{
#line 2109 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
#line 2649 "syntax2.c"
				}
				/* END OF ACTION: is_type_id_true */
				if (!ZI0)
					goto ZL3;
				ZRtype_Hid (&ZIt, &ZIm2);
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
				/* BEGINNING OF ACTION: exp_typeid_type */
				{
#line 841 "syntax.act"

    (ZIc) = make_typeid_type ( (ZIop), (ZIt), (ZIm2) ) ;
#line 2670 "syntax2.c"
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
			case 330: case 346:
				{
					EXP ZIa;
					int ZIn2;

					ZRexpression (&ZIa);
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
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2714 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: exp_typeid_exp */
					{
#line 837 "syntax.act"

    (ZIc) = make_typeid_exp ( (ZIop), (ZIa), (ZIn2) ) ;
#line 2722 "syntax2.c"
					}
					/* END OF ACTION: exp_typeid_exp */
				}
				break;
			default:
				goto ZL1;
			}
		ZL2:;
		}
		/* END OF INLINE: 557 */
		/* BEGINNING OF ACTION: sizeof_end */
		{
#line 2029 "syntax.act"

    suppress_usage-- ;
#line 2738 "syntax2.c"
		}
		/* END OF ACTION: sizeof_end */
		ZIe = ZIc;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRsizeof_Hexpression(int ZIop, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIn1;
		int ZIm1;
		EXP ZIc;

		/* BEGINNING OF ACTION: sizeof_begin */
		{
#line 2025 "syntax.act"

    suppress_usage++ ;
#line 2769 "syntax2.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 2000 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 2777 "syntax2.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2004 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 2785 "syntax2.c"
		}
		/* END OF ACTION: no_type_defns */
		/* BEGINNING OF INLINE: 595 */
		{
			switch (CURRENT_TERMINAL) {
			case 170:
				{
					int ZI1416;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_alignof */
					{
#line 386 "syntax.act"
 (ZI1416) = lex_alignof ; 
#line 2804 "syntax2.c"
					}
					/* END OF ACTION: lex_alignof */
					ZRsizeof_Hexpression (ZI1416, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2817 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2825 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2833 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
					ZR1286 (&ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2864 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2872 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2880 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2888 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 23:
				{
					EXP ZI1281;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: complex-exp */
					{
#line 345 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2909 "syntax2.c"
					}
					/* END OF EXTRACT: complex-exp */
					ADVANCE_LEXER;
					ZR1242 (ZI1281, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2923 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2931 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2939 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2947 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 25:
				{
					TYPE ZI1267;
					BASE_TYPE ZIbt;
					CV_SPEC ZIcv;
					TYPE ZI1430;
					SID_LIST_EXP ZIp;
					EXP ZI1284;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: complex-type */
					{
#line 359 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 2975 "syntax2.c"
					}
					/* END OF EXTRACT: complex-type */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: btype_none */
					{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2983 "syntax2.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2990 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1311 "syntax.act"

    (ZI1430) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
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
					case 355:
						RESTORE_LEXER;
						goto ZL1;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_func_cast */
					{
#line 670 "syntax.act"

    (ZI1284) = make_func_cast_exp ( (ZI1430), (ZIp) ) ;
#line 3025 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1242 (ZI1284, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3038 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3046 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3054 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3062 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 130:
				{
					TYPE ZI1419;
					EXP ZI1420;
					int ZIn;
					EXP ZI1273;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1419, &ZI1420, &ZIn);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_const_cast */
					{
#line 618 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZI1419), (ZI1420), (ZIn) ) ;
#line 3090 "syntax2.c"
					}
					/* END OF ACTION: exp_const_cast */
					ZR1242 (ZI1273, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3103 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3111 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3119 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3127 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 132:
				{
					TYPE ZI1425;
					EXP ZI1426;
					int ZIn;
					EXP ZI1276;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1425, &ZI1426, &ZIn);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_dynamic_cast */
					{
#line 644 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZI1425), (ZI1426), (ZIn) ) ;
#line 3155 "syntax2.c"
					}
					/* END OF ACTION: exp_dynamic_cast */
					ZR1242 (ZI1276, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3168 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3176 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3184 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3192 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 210:
				{
					EXP ZI1279;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_ellipsis */
					{
#line 648 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 3211 "syntax2.c"
					}
					/* END OF ACTION: exp_ellipsis */
					ZR1242 (ZI1279, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3224 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3232 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3240 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
#line 256 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3266 "syntax2.c"
					}
					/* END OF EXTRACT: full-name */
					ADVANCE_LEXER;
					ZR1269 (&ZIns, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3280 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3288 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3296 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3304 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 61:
				{
					EXP ZI1409;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1409);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_predec */
					{
#line 775 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_minus_Hminus, (ZI1409) ) ;
#line 3328 "syntax2.c"
					}
					/* END OF ACTION: exp_predec */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3336 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3344 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3352 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3378 "syntax2.c"
					}
					/* END OF EXTRACT: nested-name */
					ADVANCE_LEXER;
					ZR1268 (&ZIns, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3392 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3400 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3408 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3416 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 65:
				{
					ADVANCE_LEXER;
					ZR1431 (&ZIop, &ZIn1, &ZIm1, &ZIc);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 71:
				{
					EXP ZI1408;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1408);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_preinc */
					{
#line 779 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_plus_Hplus, (ZI1408) ) ;
#line 3450 "syntax2.c"
					}
					/* END OF ACTION: exp_preinc */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3458 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3466 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3474 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3482 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 145:
				{
					TYPE ZI1421;
					EXP ZI1422;
					int ZIn;
					EXP ZI1274;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1421, &ZI1422, &ZIn);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_reinterpret_cast */
					{
#line 792 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZI1421), (ZI1422), (ZIn) ) ;
#line 3510 "syntax2.c"
					}
					/* END OF ACTION: exp_reinterpret_cast */
					ZR1242 (ZI1274, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3523 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3531 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3539 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3547 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 116:
				{
					int ZI1415;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_sizeof */
					{
#line 393 "syntax.act"
 (ZI1415) = lex_sizeof ; 
#line 3565 "syntax2.c"
					}
					/* END OF ACTION: lex_sizeof */
					ZRsizeof_Hexpression (ZI1415, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3578 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3586 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3594 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3602 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 78:
				{
					EXP ZI1410;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1410);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_indir */
					{
#line 686 "syntax.act"

    (ZIa) = make_indir_exp ( (ZI1410) ) ;
#line 3626 "syntax2.c"
					}
					/* END OF ACTION: exp_indir */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3634 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3642 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3650 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3658 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 146:
				{
					TYPE ZI1423;
					EXP ZI1424;
					int ZIn;
					EXP ZI1275;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hoperand (&ZI1423, &ZI1424, &ZIn);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_static_cast */
					{
#line 817 "syntax.act"

    (ZI1275) = make_static_cast_exp ( (ZI1423), (ZI1424), (ZIn) ) ;
#line 3685 "syntax2.c"
					}
					/* END OF ACTION: exp_static_cast */
					ZR1242 (ZI1275, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3698 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3706 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3714 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3722 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 148:
				{
					EXP ZI1278;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_this */
					{
#line 821 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 3741 "syntax2.c"
					}
					/* END OF ACTION: exp_this */
					ZR1242 (ZI1278, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3754 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3762 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3770 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3778 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 152:
				{
					int ZI1418;
					EXP ZI1272;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_typeid */
					{
#line 394 "syntax.act"
 (ZI1418) = lex_typeid ; 
#line 3797 "syntax2.c"
					}
					/* END OF ACTION: lex_typeid */
					ZRtypeid_Hexpression (ZI1418, &ZI1272);
					ZR1242 (ZI1272, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3811 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3819 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3827 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3835 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 330:
				{
					int ZI1417;
					EXP ZI1271;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_vtable */
					{
#line 395 "syntax.act"
 (ZI1417) = lex_vtable ; 
#line 3854 "syntax2.c"
					}
					/* END OF ACTION: lex_vtable */
					ZRtypeid_Hexpression (ZI1417, &ZI1271);
					ZR1242 (ZI1271, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3868 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3876 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3884 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3892 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 33:
				{
					EXP ZI1411;
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
					ZRcast_Hexpression (&ZI1411);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_ref */
					{
#line 787 "syntax.act"

    (ZIa) = make_ref_exp ( (ZI1411), 0 ) ;
#line 3928 "syntax2.c"
					}
					/* END OF ACTION: exp_ref */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3936 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3944 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3952 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
					TYPE ZI1267;
					CV_SPEC ZIcv;
					TYPE ZI1428;
					SID_LIST_EXP ZIp;
					EXP ZI1282;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRbase_Htype_Hspecifier (&ZIbt);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: type_pre */
					{
#line 1270 "syntax.act"

    (ZI1267) = NULL_type ;
    have_type_specifier = 1 ;
#line 3992 "syntax2.c"
					}
					/* END OF ACTION: type_pre */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3999 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1311 "syntax.act"

    (ZI1428) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
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
					case 355:
						RESTORE_LEXER;
						goto ZL1;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_func_cast */
					{
#line 670 "syntax.act"

    (ZI1282) = make_func_cast_exp ( (ZI1428), (ZIp) ) ;
#line 4034 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1242 (ZI1282, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4047 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4055 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4063 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4071 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 17: case 18: case 19: case 20:
			case 21: case 22: case 135: case 150:
				{
					EXP ZI1277;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRliteral (&ZI1277);
					ZR1242 (ZI1277, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4096 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4104 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4112 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4120 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 62:
				{
					EXP ZI1412;
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
					ZRcast_Hexpression (&ZI1412);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_not */
					{
#line 746 "syntax.act"

    (ZIa) = make_not_exp ( (ZI1412) ) ;
#line 4156 "syntax2.c"
					}
					/* END OF ACTION: exp_not */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4164 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4172 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4180 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
					EXP ZI1285;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRunqualified_Hid (&ZIid);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_identifier */
					{
#line 674 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 4213 "syntax2.c"
					}
					/* END OF ACTION: exp_identifier */
					ZR1242 (ZI1285, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4226 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4234 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4242 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4250 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 2: case 7:
				{
					IDENTIFIER ZIid;
					TYPE ZI1267;
					BASE_TYPE ZIbt;
					CV_SPEC ZIcv;
					TYPE ZI1429;
					SID_LIST_EXP ZIp;
					EXP ZI1283;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRunqualified_Htype (&ZIid);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: type_name */
					{
#line 1275 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 4281 "syntax2.c"
					}
					/* END OF ACTION: type_name */
					/* BEGINNING OF ACTION: btype_none */
					{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4288 "syntax2.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4295 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1311 "syntax.act"

    (ZI1429) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
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
					case 355:
						RESTORE_LEXER;
						goto ZL1;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_func_cast */
					{
#line 670 "syntax.act"

    (ZI1283) = make_func_cast_exp ( (ZI1429), (ZIp) ) ;
#line 4330 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1242 (ZI1283, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4343 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4351 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4359 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
#line 2039 "syntax.act"
 (ZIb) = 0 ; 
#line 4384 "syntax2.c"
					}
					/* END OF ACTION: bool_false */
					ZR1432 (&ZIb, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4397 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4405 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4413 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4421 "syntax2.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 43: case 59: case 69: case 85:
				{
					int ZI1413;
					EXP ZI1414;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF ACTION: lex_crt */
					{
#line 379 "syntax.act"
 (ZI1413) = crt_lex_token ; 
#line 4439 "syntax2.c"
					}
					/* END OF ACTION: lex_crt */
					ZRunary_Hoperator ();
					ZRcast_Hexpression (&ZI1414);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_unary */
					{
#line 845 "syntax.act"

    (ZIa) = make_uminus_exp ( (ZI1413), (ZI1414) ) ;
#line 4453 "syntax2.c"
					}
					/* END OF ACTION: exp_unary */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2008 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4461 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2012 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4469 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1316 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4477 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 813 "syntax.act"

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
		/* END OF INLINE: 595 */
		/* BEGINNING OF ACTION: sizeof_end */
		{
#line 2029 "syntax.act"

    suppress_usage-- ;
#line 4500 "syntax2.c"
		}
		/* END OF ACTION: sizeof_end */
		ZIe = ZIc;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
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
#line 223 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4528 "syntax2.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 503 "syntax.act"

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
#line 207 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4553 "syntax2.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 497 "syntax.act"

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
#line 215 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4578 "syntax2.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 497 "syntax.act"

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
#line 229 "syntax.act"

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
#line 503 "syntax.act"

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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 503 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4639 "syntax2.c"
			}
			/* END OF ACTION: namespace_complex */
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
ZR919(TYPE *ZIs, BASE_TYPE *ZIb1, TYPE *ZIt1, CV_SPEC *ZIcv1, DECL_SPEC *ZIds1, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZI1387;
		TYPE ZI1388;
		CV_SPEC ZI1389;
		DECL_SPEC ZI1390;
		BASE_TYPE ZIb2;
		TYPE ZIt2;
		CV_SPEC ZIcv2;
		DECL_SPEC ZIds2;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2067 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 4684 "syntax2.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (*ZIs, &ZI1387, &ZI1388, &ZI1389, &ZI1390);
		ZR919 (ZIs, &ZI1387, &ZI1388, &ZI1389, &ZI1390, &ZIb2, &ZIt2, &ZIcv2, &ZIds2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: btype_join */
		{
#line 1245 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 4704 "syntax2.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 1300 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 4720 "syntax2.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 1215 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 4730 "syntax2.c"
		}
		/* END OF ACTION: cv_join */
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1550 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (*ZIds1) | (ZIds2) ) ;
#line 4741 "syntax2.c"
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
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
	*ZOds = ZIds;
}

void
ZRtry_Hblock(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
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
#line 1111 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4803 "syntax2.c"
		}
		/* END OF ACTION: reach_check */
		/* BEGINNING OF ACTION: stmt_try_begin */
		{
#line 1027 "syntax.act"

    (ZIa) = begin_try_stmt ( 0 ) ;
#line 4811 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_begin */
		ZRcompound_Hstatement (&ZIb);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_try_cont */
		{
#line 1039 "syntax.act"

    (ZIc) = cont_try_stmt ( (ZIa), (ZIb) ) ;
#line 4824 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_cont */
		ZRhandler_Hseq_Hopt (ZIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1122 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4836 "syntax2.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_try_end */
		{
#line 1043 "syntax.act"

    (ZIe) = end_try_stmt ( (ZIc), 0 ) ;
#line 4844 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_end */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4852 "syntax2.c"
		}
		/* END OF ACTION: stmt_label_clear */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRtemplate_Hdeclaration(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
{
	EXP ZIe;

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
#line 1827 "syntax.act"

    (ZIp) = template_params ( (ZIx) ) ;
    RESCAN_LEXER ;
#line 4894 "syntax2.c"
		}
		/* END OF ACTION: template_params */
		/* BEGINNING OF ACTION: template_type */
		{
#line 1819 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 4902 "syntax2.c"
		}
		/* END OF ACTION: template_type */
		ZRdeclaration (ZIt1, ZIds, &ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: template_end */
		{
#line 1823 "syntax.act"

    end_template ( (ZIp) ) ;
#line 4915 "syntax2.c"
		}
		/* END OF ACTION: template_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4923 "syntax2.c"
		}
		/* END OF ACTION: rescan_token */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRparameter_Hdeclarator_Haux_Hopt(TYPE *ZOt, IDENTIFIER *ZOid)
{
	TYPE ZIt;
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZI1374;
		TYPE ZI1375;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 2119 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 4954 "syntax2.c"
		}
		/* END OF ACTION: is_parameter */
		if (!ZI0)
			goto ZL2;
		ZRdeclarator_Hid (&ZI1374);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_none */
		{
#line 1266 "syntax.act"

    (ZI1375) = NULL_type ;
#line 4969 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_posn */
		{
#line 1705 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1374) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 4978 "syntax2.c"
		}
		/* END OF ACTION: declarator_posn */
		ZR1163 (ZI1375, ZI1374, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
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
			ZR1373 (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 332:
		{
			IDENTIFIER ZI1372;
			int ZIw;
			TYPE ZI1378;
			IDENTIFIER ZI1379;

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
#line 449 "syntax.act"

    (ZI1372) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5023 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2040 "syntax.act"
 (ZIw) = 1 ; 
#line 5030 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1189 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1372) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5041 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZI1378);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: param_end */
			{
#line 1198 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 5056 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 456 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1379) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5067 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1705 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1379) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5076 "syntax2.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1163 (ZI1378, ZI1379, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZI1376;
			IDENTIFIER ZI1377;

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
			ZR955 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1361 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1376) ) ;
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
#line 456 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1377) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5140 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1705 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1377) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5149 "syntax2.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1163 (ZI1376, ZI1377, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1387 "syntax.act"

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
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
#line 5187 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 456 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5198 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1705 "syntax.act"

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
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOid = ZIid;
}

/* END OF FILE */
