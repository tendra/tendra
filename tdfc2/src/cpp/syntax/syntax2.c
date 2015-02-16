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
#line 190 "syntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

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


#line 110 "syntax2.c"

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
#line 2052 "syntax.act"
 (ZIv) = 1 ; 
#line 135 "syntax2.c"
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
#line 1454 "syntax.act"
 (ZIa) = dspec_none ; 
#line 161 "syntax2.c"
					}
					/* END OF ACTION: access_none */
					/* BEGINNING OF ACTION: bool_false */
					{
#line 2051 "syntax.act"
 (ZIv) = 0 ; 
#line 168 "syntax2.c"
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
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIaid), 0 ) ;
    last_namespace = (ZIns) ;
#line 188 "syntax2.c"
		}
		/* END OF ACTION: namespace_id */
		/* BEGINNING OF ACTION: class_base */
		{
#line 1516 "syntax.act"

    add_base_class ( (ZIid), (ZIa), (ZIv) ) ;
#line 196 "syntax2.c"
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
#line 1610 "syntax.act"

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
#line 246 "syntax2.c"
		}
		/* END OF ACTION: declare_id */
		/* BEGINNING OF ACTION: access_check_ret */
		{
#line 1478 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 254 "syntax2.c"
		}
		/* END OF ACTION: access_check_ret */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 264 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		ZRinitialiser_Hopt (ZIc, ZId, &ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1762 "syntax.act"

    int def = init_object ( (ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 278 "syntax2.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 288 "syntax2.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1713 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 296 "syntax2.c"
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
#line 2079 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 331 "syntax2.c"
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
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 350 "syntax2.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1254 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 363 "syntax2.c"
		}
		/* END OF ACTION: exp_none */
		goto ZL0;
	}
	/*UNREACHED*/
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
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 403 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 411 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZI1255) = cv_none ; 
#line 418 "syntax2.c"
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
#line 1861 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 436 "syntax2.c"
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
#line 2052 "syntax.act"
 (ZIb) = 1 ; 
#line 481 "syntax2.c"
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
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 528 "syntax2.c"
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
#line 562 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 551 "syntax2.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1005 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 566 "syntax.act"

    CONS_exp ( (ZIe), (ZIq), (ZIp) ) ;
#line 564 "syntax2.c"
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
#line 1135 "syntax.act"
 unreached_code = 0 ; 
#line 591 "syntax2.c"
			}
			/* END OF ACTION: reach_set */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_reach */
			{
#line 1079 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 1 ) ;
#line 604 "syntax2.c"
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
#line 1136 "syntax.act"
 unreached_code = 1 ; 
#line 618 "syntax2.c"
			}
			/* END OF ACTION: reach_unset */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_unreach */
			{
#line 1083 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 0 ) ;
#line 631 "syntax2.c"
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
#line 2116 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 668 "syntax2.c"
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
#line 617 "syntax.act"

    /* n is the number of type definitions in t */
    (ZIe) = make_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 695 "syntax2.c"
		}
		/* END OF ACTION: exp_cast */
		goto ZL0;
	}
	/*UNREACHED*/
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
#line 767 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 728 "syntax2.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 770 "syntax.act"

    (ZI1280) = make_paren_exp ( (ZIa) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 742 "syntax2.c"
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
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 789 "syntax2.c"
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
#line 249 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 811 "syntax2.c"
					}
					/* END OF EXTRACT: template-type */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 223 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 824 "syntax2.c"
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
#line 500 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZIns) ;
#line 841 "syntax2.c"
		}
		/* END OF ACTION: namespace_full */
		/* BEGINNING OF ACTION: namespace_id */
		{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 850 "syntax2.c"
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
#line 1179 "syntax.act"

    (ZIcns) = ctor_begin () ;
#line 880 "syntax2.c"
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
#line 2052 "syntax.act"
 (ZIb) = 1 ; 
#line 899 "syntax2.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2051 "syntax.act"
 (ZIb) = 0 ; 
#line 910 "syntax2.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 1022 */
			/* BEGINNING OF ACTION: ctor_end */
			{
#line 1183 "syntax.act"

    (ZIe) = ctor_end ( (ZIcns), (ZIc), (ZIb) ) ;
#line 923 "syntax2.c"
			}
			/* END OF ACTION: ctor_end */
			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZId) = NULL_exp ;
#line 931 "syntax2.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: ctor_none */
			{
#line 1191 "syntax.act"

    (ZId) = NULL_exp ;
    (ZIe) = ctor_none ( (ZIc), &(ZId) ) ;
#line 944 "syntax2.c"
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
#line 249 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 986 "syntax2.c"
					}
					/* END OF EXTRACT: template-type */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 223 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 999 "syntax2.c"
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
#line 509 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1017 "syntax2.c"
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
#line 2126 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 1058 "syntax2.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIs) = NULL_type ;
#line 1068 "syntax2.c"
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
#line 1546 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 1081 "syntax2.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1573 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds2) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1092 "syntax2.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1100 "syntax2.c"
		}
		/* END OF ACTION: declarator_start */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2024 "syntax.act"

    (ZIn2) = no_type_defns - (ZIn1) ;
#line 1113 "syntax2.c"
		}
		/* END OF ACTION: diff_type_defns */
		/* BEGINNING OF ACTION: declare_except */
		{
#line 1695 "syntax.act"

    (ZId) = make_except_decl ( (ZIds2), (ZIt), (ZIid), (ZIn2) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1123 "syntax2.c"
		}
		/* END OF ACTION: declare_except */
		goto ZL0;
	}
	/*UNREACHED*/
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
#line 1701 "syntax.act"

    (ZId) = NULL_id ;
#line 1156 "syntax2.c"
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
#line 1436 "syntax.act"
 (ZIkey) = btype_class ; 
#line 1185 "syntax2.c"
			}
			/* END OF ACTION: key_class */
		}
		break;
	case 118:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct */
			{
#line 1437 "syntax.act"
 (ZIkey) = btype_struct ; 
#line 1197 "syntax2.c"
			}
			/* END OF ACTION: key_struct */
		}
		break;
	case 121:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union */
			{
#line 1438 "syntax.act"
 (ZIkey) = btype_union ; 
#line 1209 "syntax2.c"
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
#line 710 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIb), (ZIa) ) ;
#line 1250 "syntax2.c"
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
#line 562 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 1273 "syntax2.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1002 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 566 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 1286 "syntax2.c"
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
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1321 "syntax2.c"
			}
			/* END OF ACTION: qual_get */
			ZRabstract_Hdeclarator_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1335 "syntax2.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1159) ) ? (ZIq) : inject_pre_type ( (ZI1159), (ZIq), 0 ) ) ;
#line 1343 "syntax2.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 1163 */
			ZI1159 = ZIt;
			ZI1160 = ZIid;
			goto ZL2_1163;
			/* END OF INLINE: 1163 */
		}
		/*UNREACHED*/
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
#line 339 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1390 "syntax2.c"
			}
			/* END OF EXTRACT: hash-if */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: cond_hash_if */
		{
#line 1919 "syntax.act"

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
    (ZIp) = c ;
#line 1405 "syntax2.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: decl_hash_if */
		{
#line 1902 "syntax.act"

    target_decl ( lex_if, (ZIc) ) ;
#line 1413 "syntax2.c"
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
#line 1323 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 1456 "syntax2.c"
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
#line 566 "syntax.act"

    CONS_exp ( (*ZI1289), (ZIq), (ZIp) ) ;
#line 1495 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 621 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1503 "syntax2.c"
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
#line 702 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 1614 "syntax2.c"
			}
			/* END OF ACTION: exp_initialiser */
			/* BEGINNING OF ACTION: id_none */
			{
#line 461 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1624 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: ctor_initialise */
			{
#line 1187 "syntax.act"

    ctor_initialise ( (ZIcns), (ZIid), (ZIe) ) ;
#line 1632 "syntax2.c"
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
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIaid), 0 ) ;
    last_namespace = (ZIns) ;
#line 1660 "syntax2.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1669 "syntax2.c"
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
#line 543 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1696 "syntax2.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: exp_initialiser */
			{
#line 702 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 1704 "syntax2.c"
			}
			/* END OF ACTION: exp_initialiser */
			/* BEGINNING OF ACTION: ctor_initialise */
			{
#line 1187 "syntax.act"

    ctor_initialise ( (ZIcns), (ZIid), (ZIe) ) ;
#line 1712 "syntax2.c"
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
#line 566 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1749 "syntax2.c"
			}
			/* END OF ACTION: list_exp_cons */
		}
		break;
	default:
		{
			SID_LIST_EXP ZIq;

			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 562 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 1763 "syntax2.c"
			}
			/* END OF ACTION: list_exp_null */
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 566 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1771 "syntax2.c"
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
#line 821 "syntax.act"

    (ZIe) = make_set_exp ( (ZIa) ) ;
#line 1838 "syntax2.c"
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
#line 861 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 1865 "syntax2.c"
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
#line 2051 "syntax.act"
 (ZIe) = 0 ; 
#line 1941 "syntax2.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: template_params */
			{
#line 1839 "syntax.act"

    (ZIp) = template_params ( (ZIe) ) ;
    RESCAN_LEXER ;
#line 1950 "syntax2.c"
			}
			/* END OF ACTION: template_params */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1958 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1965 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: template_type */
			{
#line 1831 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 1973 "syntax2.c"
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
#line 1852 "syntax.act"

    (ZId) = make_template_param ( (ZIt1), (ZIid) ) ;
    UNUSED ( (ZIds) ) ;
#line 1994 "syntax2.c"
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
#line 2029 "syntax.act"

    in_default_arg++ ;
#line 2010 "syntax2.c"
						}
						/* END OF ACTION: default_arg_begin */
						ZRany_Hqualified_Hid (&ZIaid);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: namespace_simple */
						{
#line 509 "syntax.act"

    (ZItid) = (ZIaid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2025 "syntax2.c"
						}
						/* END OF ACTION: namespace_simple */
						/* BEGINNING OF ACTION: default_arg_end */
						{
#line 2033 "syntax.act"

    in_default_arg-- ;
#line 2033 "syntax2.c"
						}
						/* END OF ACTION: default_arg_end */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: id_none */
						{
#line 461 "syntax.act"

    (ZItid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2047 "syntax2.c"
						}
						/* END OF ACTION: id_none */
					}
					break;
				}
			}
			/* END OF INLINE: 1121 */
			/* BEGINNING OF ACTION: template_init_name */
			{
#line 1857 "syntax.act"

    init_template_param ( (ZId), (ZItid) ) ;
#line 2060 "syntax2.c"
			}
			/* END OF ACTION: template_init_name */
			/* BEGINNING OF ACTION: template_end */
			{
#line 1835 "syntax.act"

    end_template ( (ZIp) ) ;
#line 2068 "syntax2.c"
			}
			/* END OF ACTION: template_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 2076 "syntax2.c"
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
#line 1844 "syntax.act"

    (ZId) = make_type_param ( (ZIid) ) ;
#line 2114 "syntax2.c"
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
#line 2029 "syntax.act"

    in_default_arg++ ;
#line 2128 "syntax2.c"
						}
						/* END OF ACTION: default_arg_begin */
						parse_tok_type (&ZIt);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: default_arg_end */
						{
#line 2033 "syntax.act"

    in_default_arg-- ;
#line 2141 "syntax2.c"
						}
						/* END OF ACTION: default_arg_end */
						/* BEGINNING OF ACTION: type_check */
						{
#line 1332 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 2149 "syntax2.c"
						}
						/* END OF ACTION: type_check */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: type_none */
						{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 2161 "syntax2.c"
						}
						/* END OF ACTION: type_none */
					}
					break;
				}
			}
			/* END OF INLINE: 1120 */
			/* BEGINNING OF ACTION: template_init_type */
			{
#line 1848 "syntax.act"

    init_type_param ( (ZId), (ZIt) ) ;
#line 2174 "syntax2.c"
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
#line 1982 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2195 "syntax2.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: decl_none */
		{
#line 1175 "syntax.act"

    (ZId) = NULL_id ;
#line 2203 "syntax2.c"
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
#line 2079 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2235 "syntax2.c"
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
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2254 "syntax2.c"
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
	/*UNREACHED*/
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
#line 1456 "syntax.act"
 crt_access = (ZIb) ; 
#line 2289 "syntax2.c"
			}
			/* END OF ACTION: access_set */
			/* BEGINNING OF INLINE: member-specification-opt */
			goto ZL2_member_Hspecification_Hopt;
			/* END OF INLINE: member-specification-opt */
		}
		/*UNREACHED*/
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
		/*UNREACHED*/
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
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2332 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2340 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2347 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1546 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2354 "syntax2.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2365 "syntax2.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1573 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 2376 "syntax2.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 2384 "syntax2.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1482 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2392 "syntax2.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIf) = 1 ; 
#line 2399 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2407 "syntax2.c"
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
		/*UNREACHED*/
	case 26: case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1861 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2430 "syntax2.c"
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
		/*UNREACHED*/
	case 77:
		{
			TYPE ZIt1;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv1;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2455 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2462 "syntax2.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2469 "syntax2.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1673 "syntax.act"

    IGNORE empty_decl ( (ZIds), (ZIt), (ZIbt), (ZIt1), (ZIcv1), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 2480 "syntax2.c"
			}
			/* END OF ACTION: declare_member_empty */
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: member-specification-opt */
			goto ZL2_member_Hspecification_Hopt;
			/* END OF INLINE: member-specification-opt */
		}
		/*UNREACHED*/
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
#line 343 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 2516 "syntax2.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1925 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 2526 "syntax2.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1906 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 2534 "syntax2.c"
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
		/*UNREACHED*/
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
#line 392 "syntax.act"
 (ZIt) = lex_close_Hround ; 
#line 2589 "syntax2.c"
		}
		/* END OF ACTION: lex_close_round */
		/* BEGINNING OF ACTION: expected */
		{
#line 1997 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 2599 "syntax2.c"
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
#line 2037 "syntax.act"

    suppress_usage++ ;
#line 2623 "syntax2.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 2012 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 2631 "syntax2.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2016 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 2639 "syntax2.c"
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
#line 2121 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
#line 2661 "syntax2.c"
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
#line 853 "syntax.act"

    (ZIc) = make_typeid_type ( (ZIop), (ZIt), (ZIm2) ) ;
#line 2682 "syntax2.c"
				}
				/* END OF ACTION: exp_typeid_type */
				goto ZL2;
			}
			/*UNREACHED*/
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2726 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: exp_typeid_exp */
					{
#line 849 "syntax.act"

    (ZIc) = make_typeid_exp ( (ZIop), (ZIa), (ZIn2) ) ;
#line 2734 "syntax2.c"
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
#line 2041 "syntax.act"

    suppress_usage-- ;
#line 2750 "syntax2.c"
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
#line 2037 "syntax.act"

    suppress_usage++ ;
#line 2781 "syntax2.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 2012 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 2789 "syntax2.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2016 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 2797 "syntax2.c"
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
#line 398 "syntax.act"
 (ZI1416) = lex_alignof ; 
#line 2816 "syntax2.c"
					}
					/* END OF ACTION: lex_alignof */
					ZRsizeof_Hexpression (ZI1416, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2829 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2837 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2845 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2853 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2876 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2884 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2892 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2900 "syntax2.c"
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
#line 357 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2921 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 2935 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 2943 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 2951 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 2959 "syntax2.c"
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
#line 371 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 2987 "syntax2.c"
					}
					/* END OF EXTRACT: complex-type */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: btype_none */
					{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2995 "syntax2.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3002 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1323 "syntax.act"

    (ZI1430) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 3011 "syntax2.c"
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
#line 682 "syntax.act"

    (ZI1284) = make_func_cast_exp ( (ZI1430), (ZIp) ) ;
#line 3037 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1242 (ZI1284, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3050 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3058 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3066 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3074 "syntax2.c"
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
#line 630 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZI1419), (ZI1420), (ZIn) ) ;
#line 3102 "syntax2.c"
					}
					/* END OF ACTION: exp_const_cast */
					ZR1242 (ZI1273, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3115 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3123 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3131 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3139 "syntax2.c"
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
#line 656 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZI1425), (ZI1426), (ZIn) ) ;
#line 3167 "syntax2.c"
					}
					/* END OF ACTION: exp_dynamic_cast */
					ZR1242 (ZI1276, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3180 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3188 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3196 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3204 "syntax2.c"
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
#line 660 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 3223 "syntax2.c"
					}
					/* END OF ACTION: exp_ellipsis */
					ZR1242 (ZI1279, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3236 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3244 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3252 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3260 "syntax2.c"
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
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3278 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3292 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3300 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3308 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3316 "syntax2.c"
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
#line 787 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_minus_Hminus, (ZI1409) ) ;
#line 3340 "syntax2.c"
					}
					/* END OF ACTION: exp_predec */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3348 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3356 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3364 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3372 "syntax2.c"
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
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3390 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3404 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3412 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3420 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3428 "syntax2.c"
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
#line 791 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_plus_Hplus, (ZI1408) ) ;
#line 3462 "syntax2.c"
					}
					/* END OF ACTION: exp_preinc */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3470 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3478 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3486 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3494 "syntax2.c"
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
#line 804 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZI1421), (ZI1422), (ZIn) ) ;
#line 3522 "syntax2.c"
					}
					/* END OF ACTION: exp_reinterpret_cast */
					ZR1242 (ZI1274, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3535 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3543 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3551 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3559 "syntax2.c"
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
#line 405 "syntax.act"
 (ZI1415) = lex_sizeof ; 
#line 3577 "syntax2.c"
					}
					/* END OF ACTION: lex_sizeof */
					ZRsizeof_Hexpression (ZI1415, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3590 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3598 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3606 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3614 "syntax2.c"
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
#line 698 "syntax.act"

    (ZIa) = make_indir_exp ( (ZI1410) ) ;
#line 3638 "syntax2.c"
					}
					/* END OF ACTION: exp_indir */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3646 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3654 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3662 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3670 "syntax2.c"
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
#line 829 "syntax.act"

    (ZI1275) = make_static_cast_exp ( (ZI1423), (ZI1424), (ZIn) ) ;
#line 3697 "syntax2.c"
					}
					/* END OF ACTION: exp_static_cast */
					ZR1242 (ZI1275, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3710 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3718 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3726 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3734 "syntax2.c"
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
#line 833 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 3753 "syntax2.c"
					}
					/* END OF ACTION: exp_this */
					ZR1242 (ZI1278, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3766 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3774 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3782 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3790 "syntax2.c"
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
#line 406 "syntax.act"
 (ZI1418) = lex_typeid ; 
#line 3809 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3823 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3831 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3839 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3847 "syntax2.c"
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
#line 407 "syntax.act"
 (ZI1417) = lex_vtable ; 
#line 3866 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3880 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3888 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3896 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3904 "syntax2.c"
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
#line 799 "syntax.act"

    (ZIa) = make_ref_exp ( (ZI1411), 0 ) ;
#line 3940 "syntax2.c"
					}
					/* END OF ACTION: exp_ref */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 3948 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 3956 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 3964 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 3972 "syntax2.c"
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
#line 1282 "syntax.act"

    (ZI1267) = NULL_type ;
    have_type_specifier = 1 ;
#line 4004 "syntax2.c"
					}
					/* END OF ACTION: type_pre */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4011 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1323 "syntax.act"

    (ZI1428) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4020 "syntax2.c"
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
#line 682 "syntax.act"

    (ZI1282) = make_func_cast_exp ( (ZI1428), (ZIp) ) ;
#line 4046 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1242 (ZI1282, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4059 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4067 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4075 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4083 "syntax2.c"
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
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4108 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4116 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4124 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4132 "syntax2.c"
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
#line 758 "syntax.act"

    (ZIa) = make_not_exp ( (ZI1412) ) ;
#line 4168 "syntax2.c"
					}
					/* END OF ACTION: exp_not */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4176 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4184 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4192 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4200 "syntax2.c"
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
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 4225 "syntax2.c"
					}
					/* END OF ACTION: exp_identifier */
					ZR1242 (ZI1285, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4238 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4246 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4254 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4262 "syntax2.c"
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
#line 1287 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 4293 "syntax2.c"
					}
					/* END OF ACTION: type_name */
					/* BEGINNING OF ACTION: btype_none */
					{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4300 "syntax2.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4307 "syntax2.c"
					}
					/* END OF ACTION: cv_none */
					/* BEGINNING OF ACTION: type_complete */
					{
#line 1323 "syntax.act"

    (ZI1429) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4316 "syntax2.c"
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
#line 682 "syntax.act"

    (ZI1283) = make_func_cast_exp ( (ZI1429), (ZIp) ) ;
#line 4342 "syntax2.c"
					}
					/* END OF ACTION: exp_func_cast */
					ZR1242 (ZI1283, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4355 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4363 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4371 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4379 "syntax2.c"
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
#line 2051 "syntax.act"
 (ZIb) = 0 ; 
#line 4396 "syntax2.c"
					}
					/* END OF ACTION: bool_false */
					ZR1432 (&ZIb, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4409 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4417 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4425 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4433 "syntax2.c"
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
#line 391 "syntax.act"
 (ZI1413) = crt_lex_token ; 
#line 4451 "syntax2.c"
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
#line 857 "syntax.act"

    (ZIa) = make_uminus_exp ( (ZI1413), (ZI1414) ) ;
#line 4465 "syntax2.c"
					}
					/* END OF ACTION: exp_unary */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4473 "syntax2.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4481 "syntax2.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4489 "syntax2.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4497 "syntax2.c"
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
#line 2041 "syntax.act"

    suppress_usage-- ;
#line 4512 "syntax2.c"
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
#line 235 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4540 "syntax2.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4551 "syntax2.c"
			}
			/* END OF ACTION: namespace_complex */
		}
		break;
	case 1:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4565 "syntax2.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 509 "syntax.act"

    (ZIid) = (ZIuid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4576 "syntax2.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	case 3:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 227 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4590 "syntax2.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 509 "syntax.act"

    (ZIid) = (ZIuid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4601 "syntax2.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	case 6:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 241 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 4619 "syntax2.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4630 "syntax2.c"
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
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4651 "syntax2.c"
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
#line 2079 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 4696 "syntax2.c"
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
#line 1257 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 4716 "syntax2.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 1312 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 4732 "syntax2.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 1227 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 4742 "syntax2.c"
		}
		/* END OF ACTION: cv_join */
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (*ZIds1) | (ZIds2) ) ;
#line 4753 "syntax2.c"
		}
		/* END OF ACTION: dspec_join */
		goto ZL0;
	}
	/*UNREACHED*/
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
#line 1123 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4815 "syntax2.c"
		}
		/* END OF ACTION: reach_check */
		/* BEGINNING OF ACTION: stmt_try_begin */
		{
#line 1039 "syntax.act"

    (ZIa) = begin_try_stmt ( 0 ) ;
#line 4823 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_begin */
		ZRcompound_Hstatement (&ZIb);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_try_cont */
		{
#line 1051 "syntax.act"

    (ZIc) = cont_try_stmt ( (ZIa), (ZIb) ) ;
#line 4836 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_cont */
		ZRhandler_Hseq_Hopt (ZIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1134 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4848 "syntax2.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_try_end */
		{
#line 1055 "syntax.act"

    (ZIe) = end_try_stmt ( (ZIc), 0 ) ;
#line 4856 "syntax2.c"
		}
		/* END OF ACTION: stmt_try_end */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4864 "syntax2.c"
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
#line 1839 "syntax.act"

    (ZIp) = template_params ( (ZIx) ) ;
    RESCAN_LEXER ;
#line 4906 "syntax2.c"
		}
		/* END OF ACTION: template_params */
		/* BEGINNING OF ACTION: template_type */
		{
#line 1831 "syntax.act"

    (ZIt1) = make_template_type ( (ZIp), (ZIt) ) ;
#line 4914 "syntax2.c"
		}
		/* END OF ACTION: template_type */
		ZRdeclaration (ZIt1, ZIds, &ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: template_end */
		{
#line 1835 "syntax.act"

    end_template ( (ZIp) ) ;
#line 4927 "syntax2.c"
		}
		/* END OF ACTION: template_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4935 "syntax2.c"
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
#line 2131 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 4966 "syntax2.c"
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
#line 1278 "syntax.act"

    (ZI1375) = NULL_type ;
#line 4981 "syntax2.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_posn */
		{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1374) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 4990 "syntax2.c"
		}
		/* END OF ACTION: declarator_posn */
		ZR1163 (ZI1375, ZI1374, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	/*UNREACHED*/
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
#line 461 "syntax.act"

    (ZI1372) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5035 "syntax2.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIw) = 1 ; 
#line 5042 "syntax2.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1201 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1372) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 5053 "syntax2.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZI1378);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: param_end */
			{
#line 1210 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 5068 "syntax2.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 468 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1379) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5079 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1379) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5088 "syntax2.c"
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
#line 1373 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1376) ) ;
#line 5128 "syntax2.c"
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
#line 468 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1377) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5152 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1377) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5161 "syntax2.c"
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
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 5187 "syntax2.c"
			}
			/* END OF ACTION: type_build */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 5199 "syntax2.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 468 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 5210 "syntax2.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 5219 "syntax2.c"
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
