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


#line 98 "syntax8.c"

void
ZRdeclaration_Hcond(void)
{
	switch (CURRENT_TERMINAL) {
	case 30:
		{
			ADVANCE_LEXER;
		}
		break;
	case 26:
		{
			EXP ZIp;

			ZRdeclaration_Hcond_Hhead (&ZIp);
			/* BEGINNING OF INLINE: 1034 */
			{
				switch (CURRENT_TERMINAL) {
				case 28:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: cond_hash_else */
						{
#line 1914 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 125 "syntax8.c"
						}
						/* END OF ACTION: cond_hash_else */
						/* BEGINNING OF ACTION: decl_hash_else */
						{
#line 1895 "syntax.act"

    target_decl ( lex_else, NULL_exp ) ;
#line 133 "syntax8.c"
						}
						/* END OF ACTION: decl_hash_else */
						ZRdeclaration_Hcond_Hbody ();
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
			/* END OF INLINE: 1034 */
			/* BEGINNING OF ACTION: cond_hash_endif */
			{
#line 1917 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 156 "syntax8.c"
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
#line 171 "syntax8.c"
			}
			/* END OF ACTION: decl_hash_endif */
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
ZR1243(EXP ZI1241, EXP *ZO1242)
{
	EXP ZI1242;

ZL2_1243:;
	switch (CURRENT_TERMINAL) {
	case 61:
		{
			EXP ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_postdec */
			{
#line 763 "syntax.act"

    (ZIe) = make_postfix_exp ( lex_minus_Hminus, (ZI1241) ) ;
#line 204 "syntax8.c"
			}
			/* END OF ACTION: exp_postdec */
			/* BEGINNING OF INLINE: 1243 */
			ZI1241 = ZIe;
			goto ZL2_1243;
			/* END OF INLINE: 1243 */
		}
		UNREACHED;
	case 65:
		{
			SID_LIST_EXP ZIp;
			EXP ZIe;

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
			/* BEGINNING OF ACTION: exp_func */
			{
#line 662 "syntax.act"

    (ZIe) = make_func_exp ( (ZI1241), (ZIp), 0 ) ;
#line 235 "syntax8.c"
			}
			/* END OF ACTION: exp_func */
			/* BEGINNING OF INLINE: 1243 */
			ZI1241 = ZIe;
			goto ZL2_1243;
			/* END OF INLINE: 1243 */
		}
		UNREACHED;
	case 71:
		{
			EXP ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_postinc */
			{
#line 767 "syntax.act"

    (ZIe) = make_postfix_exp ( lex_plus_Hplus, (ZI1241) ) ;
#line 254 "syntax8.c"
			}
			/* END OF ACTION: exp_postinc */
			/* BEGINNING OF INLINE: 1243 */
			ZI1241 = ZIe;
			goto ZL2_1243;
			/* END OF INLINE: 1243 */
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
#line 678 "syntax.act"

    (ZIe) = make_index_exp ( (ZI1241), (ZIb) ) ;
#line 304 "syntax8.c"
			}
			/* END OF ACTION: exp_index */
			/* BEGINNING OF INLINE: 1243 */
			ZI1241 = ZIe;
			goto ZL2_1243;
			/* END OF INLINE: 1243 */
		}
		UNREACHED;
	case 35:
		{
			EXP ZIb;
			TYPE ZIt;
			NAMESPACE ZIns;
			int ZIq;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: exp_arrow_begin */
			{
#line 578 "syntax.act"

    (ZIb) = begin_field_exp ( lex_arrow, (ZI1241), &(ZIt), &(ZIns) ) ;
#line 327 "syntax8.c"
			}
			/* END OF ACTION: exp_arrow_begin */
			ADVANCE_LEXER;
			ZRtemplate_Hopt (ZIns, &ZIq);
			ZRfield_Hid_Hexpression (ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_arrow_end */
			{
#line 582 "syntax.act"

    (ZIe) = end_field_exp ( lex_arrow, (ZIb), (ZIt), (ZIns), (ZIid), (ZIq) ) ;
#line 342 "syntax8.c"
			}
			/* END OF ACTION: exp_arrow_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 350 "syntax8.c"
			}
			/* END OF ACTION: rescan_token */
			/* BEGINNING OF INLINE: 1243 */
			ZI1241 = ZIe;
			goto ZL2_1243;
			/* END OF INLINE: 1243 */
		}
		UNREACHED;
	case 46:
		{
			EXP ZIb;
			TYPE ZIt;
			NAMESPACE ZIns;
			int ZIq;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: exp_dot_begin */
			{
#line 626 "syntax.act"

    (ZIb) = begin_field_exp ( lex_dot, (ZI1241), &(ZIt), &(ZIns) ) ;
#line 373 "syntax8.c"
			}
			/* END OF ACTION: exp_dot_begin */
			ADVANCE_LEXER;
			ZRtemplate_Hopt (ZIns, &ZIq);
			ZRfield_Hid_Hexpression (ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dot_end */
			{
#line 630 "syntax.act"

    (ZIe) = end_field_exp ( lex_dot, (ZIb), (ZIt), (ZIns), (ZIid), (ZIq) ) ;
#line 388 "syntax8.c"
			}
			/* END OF ACTION: exp_dot_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 396 "syntax8.c"
			}
			/* END OF ACTION: rescan_token */
			/* BEGINNING OF INLINE: 1243 */
			ZI1241 = ZIe;
			goto ZL2_1243;
			/* END OF INLINE: 1243 */
		}
		UNREACHED;
	default:
		{
			ZI1242 = ZI1241;
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
	*ZO1242 = ZI1242;
}

void
ZRpm_Hexpression(EXP *ZO1238)
{
	EXP ZI1238;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRcast_Hexpression (&ZIe);
		ZR1239 (ZIe, &ZI1238);
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
	*ZO1238 = ZI1238;
}

void
ZR1371(DECL_SPEC *ZIds, TYPE *ZIp, BASE_TYPE *ZIq, ACCESS_LIST *ZIr, int *ZIf, IDENTIFIER *ZI1370, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	switch (CURRENT_TERMINAL) {
	default:
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

			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1718 "syntax.act"

    (ZI1356) = constr_name ( last_namespace, (*ZI1370) ) ;
#line 470 "syntax8.c"
			}
			/* END OF ACTION: declarator_type */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZI1357) = NULL_type ;
#line 478 "syntax8.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZI1358) = 0 ; 
#line 485 "syntax8.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (ZI1356), crt_id_qualifier, qual_namespace, 1 ) ;
#line 493 "syntax8.c"
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

    if ( !IS_NULL_type ( (*ZIp) ) ) template_decl ( (*ZIp) ) ;
#line 506 "syntax8.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1350) ) ? (*ZIp) : inject_pre_type ( (ZI1350), (*ZIp), 1 ) ) ;
#line 514 "syntax8.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1760 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 522 "syntax8.c"
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
#line 555 "syntax8.c"
			}
			/* END OF ACTION: declare_member */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(*ZIr) ) ;
#line 563 "syntax8.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 573 "syntax8.c"
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
#line 587 "syntax8.c"
			}
			/* END OF ACTION: initialise_member */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 597 "syntax8.c"
			}
			/* END OF ACTION: access_check_decl */
		}
		break;
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
#line 614 "syntax8.c"
			}
			/* END OF ACTION: template_decl */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1693 "syntax.act"

    begin_declarator ( (*ZI1370), crt_id_qualifier, qual_namespace, 1 ) ;
#line 622 "syntax8.c"
			}
			/* END OF ACTION: declarator_begin */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 631 "syntax8.c"
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
#line 646 "syntax8.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: type_bitfield_mem */
			{
#line 1373 "syntax.act"

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1370) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZIt) = make_bitfield_type ( (*ZIp), (*ZIq), (ZIc), z ) ;
#line 657 "syntax8.c"
			}
			/* END OF ACTION: type_bitfield_mem */
			/* BEGINNING OF ACTION: declare_bitfield */
			{
#line 1664 "syntax.act"

    IDENTIFIER id = make_member_decl ( (*ZIds), (ZIt), (*ZI1370), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZId) = id ;
#line 671 "syntax8.c"
			}
			/* END OF ACTION: declare_bitfield */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(*ZIr) ) ;
#line 679 "syntax8.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 689 "syntax8.c"
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
ZRtemplate_Hopt(NAMESPACE ZIns, int *ZOt)
{
	int ZIt;

	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIt) = 0 ; 
#line 717 "syntax8.c"
			}
			/* END OF ACTION: bool_false */
		}
		break;
	case 147:
		{
			/* BEGINNING OF ACTION: rescan_template */
			{
#line 2136 "syntax.act"

    rescan_template ( (ZIns) ) ;
#line 729 "syntax8.c"
			}
			/* END OF ACTION: rescan_template */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIt) = 1 ; 
#line 737 "syntax8.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	case 356:
		return;
	}
	*ZOt = ZIt;
}

void
ZRaccess_Hspecifier(DECL_SPEC *ZOa)
{
	DECL_SPEC ZIa;

	switch (CURRENT_TERMINAL) {
	case 142:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access_private */
			{
#line 1435 "syntax.act"
 (ZIa) = dspec_private ; 
#line 761 "syntax8.c"
			}
			/* END OF ACTION: access_private */
		}
		break;
	case 143:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access_protected */
			{
#line 1436 "syntax.act"
 (ZIa) = dspec_protected ; 
#line 773 "syntax8.c"
			}
			/* END OF ACTION: access_protected */
		}
		break;
	case 144:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access_public */
			{
#line 1437 "syntax.act"
 (ZIa) = dspec_public ; 
#line 785 "syntax8.c"
			}
			/* END OF ACTION: access_public */
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
}

void
ZRusing_Hdeclaration(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 154:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR1260 ();
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
ZR1374(TYPE *ZO1162, IDENTIFIER *ZO1163)
{
	TYPE ZI1162;
	IDENTIFIER ZI1163;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZI1375;
		TYPE ZI1376;
		TYPE ZIt;
		IDENTIFIER ZIid;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 2115 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 850 "syntax8.c"
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
#line 865 "syntax8.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_posn */
		{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1375) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 874 "syntax8.c"
		}
		/* END OF ACTION: declarator_posn */
		ZR1164 (ZI1376, ZI1375, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declarator_bad */
		{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 889 "syntax8.c"
		}
		/* END OF ACTION: declarator_bad */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR1164 (ZIt, ZIid, &ZI1162, &ZI1163);
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
			ZR1374 (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 927 "syntax8.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1164 (ZIt, ZIid, &ZI1162, &ZI1163);
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
#line 445 "syntax.act"

    (ZI1373) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 968 "syntax8.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIw) = 1 ; 
#line 975 "syntax8.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1373) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 986 "syntax8.c"
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
#line 1001 "syntax8.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1380) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1012 "syntax8.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1380) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1021 "syntax8.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1164 (ZI1379, ZI1380, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 1036 "syntax8.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1164 (ZIt, ZIid, &ZI1162, &ZI1163);
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
#line 1085 "syntax8.c"
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
#line 1109 "syntax8.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1378) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1118 "syntax8.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1164 (ZI1377, ZI1378, &ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 1133 "syntax8.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1164 (ZIt, ZIid, &ZI1162, &ZI1163);
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
#line 1383 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 1168 "syntax8.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 1178 "syntax8.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1164 (ZIt, ZIid, &ZI1162, &ZI1163);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 7: case 8: case 9:
	case 25: case 39: case 47: case 83:
	case 94: case 97: case 98: case 102:
	case 104: case 105: case 106: case 110:
	case 111: case 112: case 114: case 115:
	case 117: case 118: case 120: case 121:
	case 122: case 123: case 124: case 127:
	case 129: case 133: case 136: case 137:
	case 138: case 153: case 155: case 156:
	case 185: case 275: case 286: case 299:
		{
			IDENTIFIER ZI1372;
			int ZIw;
			TYPE ZIt;
			IDENTIFIER ZIid;

			/* BEGINNING OF ACTION: id_none */
			{
#line 445 "syntax.act"

    (ZI1372) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1218 "syntax8.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIw) = 0 ; 
#line 1225 "syntax8.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1372) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1236 "syntax8.c"
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
#line 1251 "syntax8.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1262 "syntax8.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 1271 "syntax8.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1164 (ZIt, ZIid, &ZI1162, &ZI1163);
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
	*ZO1162 = ZI1162;
	*ZO1163 = ZI1163;
}

void
parse_mem_type(TYPE *ZOt)
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
#line 1318 "syntax8.c"
		}
		/* END OF ACTION: type_complete */
		/* BEGINNING OF INLINE: 987 */
		{
			switch (CURRENT_TERMINAL) {
			case 73:
				{
					QUALIFIER ZIi;
					int ZIb;
					EXP ZIc;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: qual_get */
					{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1337 "syntax8.c"
					}
					/* END OF ACTION: qual_get */
					ZRconstant_Hexpression (&ZIc);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: type_bitfield */
					{
#line 1368 "syntax.act"

    (ZIt) = make_bitfield_type ( (ZIq), (ZIbt), (ZIc), 0 ) ;
#line 1350 "syntax8.c"
					}
					/* END OF ACTION: type_bitfield */
					/* BEGINNING OF ACTION: qual_set */
					{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1359 "syntax8.c"
					}
					/* END OF ACTION: qual_set */
				}
				break;
			default:
				{
					ZRabstract_Hdeclarator_Hopt (ZIq, &ZIt);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			}
		}
		/* END OF INLINE: 987 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZR872(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIaid;

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
#line 1409 "syntax8.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1424 "syntax8.c"
			}
			/* END OF ACTION: id_anon */
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
	*ZOid = ZIid;
}

void
parse_operator(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		QUALIFIER ZIi;
		int ZIb;
		int ZItd;
		IDENTIFIER ZItid;

		switch (CURRENT_TERMINAL) {
		case 141:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: qual_get */
		{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1467 "syntax8.c"
		}
		/* END OF ACTION: qual_get */
		/* BEGINNING OF ACTION: type_decl_begin */
		{
#line 404 "syntax.act"

    (ZItd) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
#line 1476 "syntax8.c"
		}
		/* END OF ACTION: type_decl_begin */
		/* BEGINNING OF INLINE: 460 */
		{
			{
				TYPE ZI1321;
				BASE_TYPE ZIb1;
				TYPE ZIt1;
				CV_SPEC ZIcv1;
				BASE_TYPE ZIbt;
				TYPE ZIp;
				CV_SPEC ZIcv;
				TYPE ZIs;
				TYPE ZIq;
				TYPE ZIt;
				int ZId;

				/* BEGINNING OF ACTION: is_type_specifier */
				{
#line 2110 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 1500 "syntax8.c"
				}
				/* END OF ACTION: is_type_specifier */
				if (!ZI0)
					goto ZL3;
				/* BEGINNING OF ACTION: type_none */
				{
#line 1262 "syntax.act"

    (ZI1321) = NULL_type ;
#line 1510 "syntax8.c"
				}
				/* END OF ACTION: type_none */
				ZRtype_Hspecifier (ZI1321, &ZIb1, &ZIt1, &ZIcv1);
				ZR888 (&ZIb1, &ZIt1, &ZIcv1, &ZIbt, &ZIp, &ZIcv);
				if ((CURRENT_TERMINAL) == 356) {
					RESTORE_LEXER;
					goto ZL1;
				}
				/* BEGINNING OF ACTION: type_complete */
				{
#line 1307 "syntax.act"

    (ZIs) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 1525 "syntax8.c"
				}
				/* END OF ACTION: type_complete */
				ZRconversion_Hdeclarator_Hopt (&ZIq);
				if ((CURRENT_TERMINAL) == 356) {
					RESTORE_LEXER;
					goto ZL1;
				}
				/* BEGINNING OF ACTION: type_inject */
				{
#line 1379 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIs) : inject_pre_type ( (ZIq), (ZIs), 1 ) ) ;
#line 1538 "syntax8.c"
				}
				/* END OF ACTION: type_inject */
				/* BEGINNING OF ACTION: type_decl_end */
				{
#line 410 "syntax.act"

    int td = have_type_declaration ;
    (ZId) = 0 ;
    if ( td != TYPE_DECL_NONE ) {
	if ( td == TYPE_DECL_ELABORATE && found_elaborate_type ) {
	    /* This is allowed */
	    /* EMPTY */
	} else {
	    (ZId) = 1 ;
	}
    }
    have_type_declaration = (ZItd) ;
#line 1556 "syntax8.c"
				}
				/* END OF ACTION: type_decl_end */
				/* BEGINNING OF ACTION: conversion_func */
				{
#line 434 "syntax.act"

    HASHID nm = lookup_conv ( (ZIt) ) ;
    if ( (ZId) ) report ( crt_loc, ERR_class_conv_fct_typedef ( nm ) ) ;
    (ZItid) = DEREF_id ( hashid_id ( nm ) ) ;
    set_hashid_loc ( (ZItid), underlying_op ) ;
#line 1567 "syntax8.c"
				}
				/* END OF ACTION: conversion_func */
				goto ZL2;
			}
			UNREACHED;
		ZL3:;
			switch (CURRENT_TERMINAL) {
			case 33: case 34: case 35: case 36:
			case 41: case 42: case 43: case 44:
			case 45: case 46: case 48: case 49:
			case 50: case 53: case 54: case 55:
			case 56: case 57: case 58: case 59:
			case 60: case 61: case 62: case 63:
			case 65: case 66: case 67: case 68:
			case 69: case 70: case 71: case 72:
			case 73: case 74: case 75: case 76:
			case 78: case 79: case 80: case 81:
			case 82: case 83: case 84: case 85:
			case 86: case 87: case 116: case 131:
			case 140: case 152: case 170: case 331:
				{
					int ZIop;

					ZRoperator_Hname (&ZIop);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: type_decl_quit */
					{
#line 423 "syntax.act"

    have_type_declaration = (ZItd) ;
#line 1601 "syntax8.c"
					}
					/* END OF ACTION: type_decl_quit */
					/* BEGINNING OF ACTION: operator_func */
					{
#line 428 "syntax.act"

    /* op will be in its primary form */
    HASHID nm = lookup_op ( (ZIop) ) ;
    (ZItid) = DEREF_id ( hashid_id ( nm ) ) ;
    set_hashid_loc ( (ZItid), underlying_op ) ;
#line 1612 "syntax8.c"
					}
					/* END OF ACTION: operator_func */
				}
				break;
			default:
				goto ZL1;
			}
		ZL2:;
		}
		/* END OF INLINE: 460 */
		/* BEGINNING OF ACTION: qual_set */
		{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1629 "syntax8.c"
		}
		/* END OF ACTION: qual_set */
		ZIid = ZItid;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRmember_Hspecifier_Hopt(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
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
#line 1665 "syntax8.c"
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
ZRinclusive_Hor_Hexpression(EXP *ZO1202)
{
	EXP ZI1202;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRexclusive_Hor_Hexpression (&ZIe);
		ZR1203 (ZIe, &ZI1202);
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
	*ZO1202 = ZI1202;
}

void
ZR1255(TYPE *ZIt, BASE_TYPE *ZIbt, TYPE *ZIt1, CV_SPEC *ZIcv1, DECL_SPEC *ZIds2)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			/* BEGINNING OF ACTION: declare_id_empty */
			{
#line 1615 "syntax.act"

    IGNORE empty_decl ( (*ZIds2), (*ZIt), (*ZIbt), (*ZIt1), (*ZIcv1), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 1721 "syntax8.c"
			}
			/* END OF ACTION: declare_id_empty */
			/* BEGINNING OF ACTION: access_check */
			{
#line 1446 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
#line 1731 "syntax8.c"
			}
			/* END OF ACTION: access_check */
			ADVANCE_LEXER;
		}
		break;
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 10: case 11: case 33:
	case 65: case 78: case 83: case 141:
		{
			TYPE ZIt2;
			DECL_SPEC ZIds3;
			TYPE ZIt3;
			ACCESS_LIST ZIr;
			TYPE ZIs;
			IDENTIFIER ZIid;
			int ZIc;
			IDENTIFIER ZId;

			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (*ZIds2), (*ZIbt), (*ZIt1), (*ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (*ZIbt), (*ZIt1), (*ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1759 "syntax8.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (*ZIt) ) ? (ZIt2) : inject_pre_type ( (*ZIt), (ZIt2), 1 ) ) ;
#line 1767 "syntax8.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 1775 "syntax8.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1783 "syntax8.c"
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
	bs |= (*ZIbt) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1813 "syntax8.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 1821 "syntax8.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 1831 "syntax8.c"
			}
			/* END OF ACTION: access_check_decl */
			ZR1078 (ZIbt, &ZIds3, &ZIt3, &ZIr, &ZIc, &ZId);
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
ZRjump_Hlabel(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 96:
		{
			EXP ZIc;

			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_goto_case */
			{
#line 961 "syntax.act"

    report ( crt_loc, ERR_stmt_goto_case ( lex_case ) ) ;
    (ZIe) = begin_case_stmt ( (ZIc), 1 ) ;
#line 1874 "syntax8.c"
			}
			/* END OF ACTION: stmt_goto_case */
		}
		break;
	case 100:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_goto_default */
			{
#line 966 "syntax.act"

    report ( crt_loc, ERR_stmt_goto_case ( lex_default ) ) ;
    (ZIe) = begin_default_stmt ( 1 ) ;
#line 1888 "syntax8.c"
			}
			/* END OF ACTION: stmt_goto_default */
		}
		break;
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER ZIid;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 203 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 1907 "syntax8.c"
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
#line 1920 "syntax8.c"
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
#line 1933 "syntax8.c"
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
#line 1946 "syntax8.c"
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
			/* BEGINNING OF ACTION: qual_none */
			{
#line 535 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 1964 "syntax8.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: stmt_goto */
			{
#line 956 "syntax.act"

    (ZIe) = make_goto_stmt ( (ZIid) ) ;
#line 1972 "syntax8.c"
			}
			/* END OF ACTION: stmt_goto */
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
ZRsimple_Htype_Hspecifier(BASE_TYPE *ZObt, TYPE *ZOt)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 25:
		{
			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 355 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIt = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 2009 "syntax8.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2017 "syntax8.c"
			}
			/* END OF ACTION: btype_none */
		}
		break;
	case 8: case 9: case 83:
		{
			IDENTIFIER ZIid;

			ZRany_Hqualified_Htype (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 2038 "syntax8.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2045 "syntax8.c"
			}
			/* END OF ACTION: btype_none */
		}
		break;
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 122:
	case 123: case 127: case 156: case 185:
	case 286: case 299:
		{
			ZRbase_Htype_Hspecifier (&ZIbt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_pre */
			{
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
    have_type_specifier = 1 ;
#line 2066 "syntax8.c"
			}
			/* END OF ACTION: type_pre */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZIid;

			ZRunqualified_Htype (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 2087 "syntax8.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2094 "syntax8.c"
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
ZRcomma_Hexpression_Htail(SID_LIST_EXP *ZOp)
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
			EXP ZIa;

			ZRassignment_Hexpression (&ZIa);
			ZR1293 (&ZIa, &ZIp);
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
#line 2161 "syntax8.c"
			}
			/* END OF ACTION: list_exp_cons */
		}
		break;
	case 347:
		{
			EXP ZIa;
			SID_LIST_EXP ZIq;

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
#line 2182 "syntax8.c"
			}
			/* END OF ACTION: list_exp_cons */
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
}

void
ZRparameter_Hdeclaration_Hlist(int *ZOell)
{
	int ZIell;

ZL2_parameter_Hdeclaration_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 47:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIell) = 1 ; 
#line 2214 "syntax8.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	case 2: case 7: case 8: case 9:
	case 25: case 83: case 94: case 97:
	case 98: case 102: case 104: case 105:
	case 106: case 110: case 111: case 112:
	case 114: case 115: case 117: case 118:
	case 120: case 121: case 122: case 123:
	case 124: case 127: case 129: case 133:
	case 136: case 137: case 138: case 153:
	case 155: case 156: case 185: case 275:
	case 286: case 299:
		{
			TYPE ZIs;
			int ZIp;
			IDENTIFIER ZId;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIs) = NULL_type ;
#line 2239 "syntax8.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: param_func */
			{
#line 1732 "syntax.act"

    (ZIp) = CONTEXT_PARAMETER ;
#line 2247 "syntax8.c"
			}
			/* END OF ACTION: param_func */
			ZRparameter_Hdeclaration (ZIs, ZIp, &ZId);
			/* BEGINNING OF INLINE: 979 */
			{
				switch (CURRENT_TERMINAL) {
				case 42:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: parameter-declaration-list */
						goto ZL2_parameter_Hdeclaration_Hlist;
						/* END OF INLINE: parameter-declaration-list */
					}
					UNREACHED;
				case 47:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: bool_true */
						{
#line 2036 "syntax.act"
 (ZIell) = 1 ; 
#line 2269 "syntax8.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2035 "syntax.act"
 (ZIell) = 0 ; 
#line 2280 "syntax8.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				case 356:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 979 */
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
	*ZOell = ZIell;
}

void
ZR1257(TYPE *ZIt, DECL_SPEC *ZIds, BASE_TYPE *ZIbt, TYPE *ZIt1, CV_SPEC *ZI1256, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 77:
		{
			/* BEGINNING OF ACTION: declare_id_empty */
			{
#line 1615 "syntax.act"

    IGNORE empty_decl ( (*ZIds), (*ZIt), (*ZIbt), (*ZIt1), (*ZI1256), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 2322 "syntax8.c"
			}
			/* END OF ACTION: declare_id_empty */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2331 "syntax8.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 10: case 11: case 33:
	case 65: case 78: case 83: case 141:
		{
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

			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2356 "syntax8.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (*ZIds) | (ZIds1) ) ;
#line 2367 "syntax8.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (*ZIbt), (*ZIt1), (*ZI1256) ) ;
    (ZIt2) = complete_pre_type ( (*ZIbt), (*ZIt1), (*ZI1256), 0 ) ;
    have_type_specifier = 0 ;
#line 2378 "syntax8.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (*ZIt) ) ? (ZIt2) : inject_pre_type ( (*ZIt), (ZIt2), 1 ) ) ;
#line 2386 "syntax8.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2394 "syntax8.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2402 "syntax8.c"
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
	bs |= (*ZIbt) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2432 "syntax8.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 2440 "syntax8.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 2450 "syntax8.c"
			}
			/* END OF ACTION: access_check_decl */
			ZR1078 (ZIbt, &ZIds3, &ZIt3, &ZIr, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2463 "syntax8.c"
			}
			/* END OF ACTION: exp_none */
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
ZRliteral(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 135: case 150:
		{
			ZRboolean_Hliteral (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 17: case 18:
		{
			/* BEGINNING OF INLINE: character-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 17:
					{
						/* BEGINNING OF EXTRACT: char-exp */
						{
#line 299 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 2508 "syntax8.c"
						}
						/* END OF EXTRACT: char-exp */
						ADVANCE_LEXER;
					}
					break;
				case 18:
					{
						/* BEGINNING OF EXTRACT: wchar-exp */
						{
#line 303 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 2521 "syntax8.c"
						}
						/* END OF EXTRACT: wchar-exp */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: character-literal */
		}
		break;
	case 22:
		{
			/* BEGINNING OF INLINE: floating-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 22:
						/* BEGINNING OF EXTRACT: floating-exp */
						{
#line 286 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 2546 "syntax8.c"
						}
						/* END OF EXTRACT: floating-exp */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: floating-literal */
		}
		break;
	case 21:
		{
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 282 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 2571 "syntax8.c"
						}
						/* END OF EXTRACT: integer-exp */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: integer-literal */
		}
		break;
	case 19: case 20:
		{
			/* BEGINNING OF INLINE: string-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 19:
					{
						/* BEGINNING OF EXTRACT: string-exp */
						{
#line 307 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 2596 "syntax8.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 311 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 2609 "syntax8.c"
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
ZRexception_Hspecification_Hopt(SID_LIST_TYPE *ZOp)
{
	SID_LIST_TYPE ZIp;

	switch (CURRENT_TERMINAL) {
	case 149:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 1109 */
			{
				switch (CURRENT_TERMINAL) {
				case 47:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: list_type_ellipsis */
						{
#line 1408 "syntax.act"

    report ( crt_loc, ERR_except_spec_ellipsis () ) ;
    (ZIp) = univ_type_set ;
#line 2663 "syntax8.c"
						}
						/* END OF ACTION: list_type_ellipsis */
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
						ZRtype_Hid_Hlist (&ZIp);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: list_type_null */
						{
#line 1395 "syntax.act"

    (ZIp) = NULL_list ( TYPE ) ;
#line 2690 "syntax8.c"
						}
						/* END OF ACTION: list_type_null */
					}
					break;
				}
			}
			/* END OF INLINE: 1109 */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: list_type_all */
			{
#line 1403 "syntax.act"

    (ZIp) = empty_type_set ;
#line 2714 "syntax8.c"
			}
			/* END OF ACTION: list_type_all */
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
parse_decl(TYPE ZIt, DECL_SPEC ZIds)
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
#line 2753 "syntax8.c"
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
#line 2772 "syntax8.c"
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
#line 2808 "syntax8.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2816 "syntax8.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2823 "syntax8.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2830 "syntax8.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2841 "syntax8.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 2852 "syntax8.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1379 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 2860 "syntax8.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1466 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2868 "syntax8.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2876 "syntax8.c"
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
#line 2906 "syntax8.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1462 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 2914 "syntax8.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1457 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 2924 "syntax8.c"
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
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1966 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2948 "syntax8.c"
		}
		/* END OF ACTION: error_syntax */
	}
ZL0:;
}

void
ZR1385(TYPE *ZI1383, TYPE *ZOt)
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
			/* BEGINNING OF ACTION: type_build */
			{
#line 1383 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (*ZI1383) : inject_pre_type ( (ZIq), (*ZI1383), 0 ) ) ;
#line 2976 "syntax8.c"
			}
			/* END OF ACTION: type_build */
		}
		break;
	default:
		{
			ZIt = *ZI1383;
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
ZR1258(void)
{
	switch (CURRENT_TERMINAL) {
	case 26: case 30:
		{
			ZRdeclaration_Hcond ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_check */
			{
#line 1446 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
#line 3015 "syntax8.c"
			}
			/* END OF ACTION: access_check */
		}
		break;
	case 126: case 139: case 154:
		{
			EXP ZIe;

			ZRdeclaration_Hother (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1728 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 3034 "syntax8.c"
			}
			/* END OF ACTION: declare_extern */
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
ZR1004(IDENTIFIER *ZId, SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 5:
	case 6: case 7: case 8: case 9:
	case 17: case 18: case 19: case 20:
	case 21: case 22: case 23: case 25:
	case 33: case 43: case 59: case 61:
	case 62: case 64: case 65: case 69:
	case 71: case 78: case 83: case 85:
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 116:
	case 122: case 123: case 127: case 130:
	case 131: case 132: case 135: case 140:
	case 141: case 145: case 146: case 148:
	case 149: case 150: case 152: case 156:
	case 170: case 185: case 206: case 210:
	case 255: case 286: case 299: case 331:
		{
			ZRinitialiser_Hlist (*ZId, &ZIp);
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
#line 3086 "syntax8.c"
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
ZR1386(TYPE *ZO1141)
{
	TYPE ZI1141;

	switch (CURRENT_TERMINAL) {
	case 10: case 11: case 33: case 65:
	case 66: case 78: case 333:
		{
			TYPE ZIt;

			ZRabstract_Hdeclarator_Haux (&ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1722 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 3125 "syntax8.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1142 (ZIt, &ZI1141);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 7: case 8: case 9:
	case 25: case 39: case 47: case 83:
	case 94: case 97: case 98: case 102:
	case 104: case 105: case 106: case 110:
	case 111: case 112: case 114: case 115:
	case 117: case 118: case 120: case 121:
	case 122: case 123: case 124: case 127:
	case 129: case 133: case 136: case 137:
	case 138: case 153: case 155: case 156:
	case 185: case 275: case 286: case 299:
		{
			IDENTIFIER ZIid;
			int ZIw;
			TYPE ZIt;

			/* BEGINNING OF ACTION: id_none */
			{
#line 445 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 3164 "syntax8.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIw) = 0 ; 
#line 3171 "syntax8.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 3182 "syntax8.c"
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
#line 3197 "syntax8.c"
			}
			/* END OF ACTION: param_end */
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
ZR1387(SID_LIST_TYPE *ZOq)
{
	SID_LIST_TYPE ZIq;

	switch (CURRENT_TERMINAL) {
	case 2: case 7: case 8: case 9:
	case 25: case 83: case 97: case 98:
	case 102: case 104: case 106: case 110:
	case 111: case 114: case 115: case 118:
	case 121: case 122: case 123: case 124:
	case 127: case 129: case 153: case 156:
	case 185: case 286: case 299:
		{
			ZRtype_Hid_Hlist (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1971 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3249 "syntax8.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_type_null */
			{
#line 1395 "syntax.act"

    (ZIq) = NULL_list ( TYPE ) ;
#line 3257 "syntax8.c"
			}
			/* END OF ACTION: list_type_null */
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
	*ZOq = ZIq;
}

void
ZR1260(void)
{
	switch (CURRENT_TERMINAL) {
	case 153:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIid;
			TYPE ZIt;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3289 "syntax8.c"
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
#line 3308 "syntax8.c"
			}
			/* END OF ACTION: type_typename */
			/* BEGINNING OF ACTION: using_typename */
			{
#line 1800 "syntax.act"

    using_typename ( (ZIt) ) ;
#line 3316 "syntax8.c"
			}
			/* END OF ACTION: using_typename */
			ZRsemicolon_Hx ();
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

			ZRdeclarator_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: using_identifier */
			{
#line 1796 "syntax.act"

    IGNORE using_identifier ( (ZIid) ) ;
#line 3342 "syntax8.c"
			}
			/* END OF ACTION: using_identifier */
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
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRexclusive_Hor_Hexpression(EXP *ZO1206)
{
	EXP ZI1206;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRand_Hexpression (&ZIe);
		ZR1207 (ZIe, &ZI1206);
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
	*ZO1206 = ZI1206;
}

void
ZRcompound_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIc;
		EXP ZIa;

		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 891 "syntax.act"

    (ZIc) = begin_compound_stmt ( 1 ) ;
#line 3406 "syntax8.c"
		}
		/* END OF ACTION: stmt_compound_begin */
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
#line 3427 "syntax8.c"
		}
		/* END OF ACTION: stmt_compound_block */
		ZRstatement_Hseq_Hopt (ZIc, &ZIa);
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

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3453 "syntax8.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3461 "syntax8.c"
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
ZR1261(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER ZInid;
			IDENTIFIER ZIid;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 203 "syntax.act"

    ZInid = crt_token->pp_data.id.use ;
#line 3494 "syntax8.c"
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

    ZInid = crt_token->pp_data.id.use ;
#line 3507 "syntax8.c"
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

    ZInid = crt_token->pp_data.id.use ;
#line 3520 "syntax8.c"
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

    ZInid = crt_token->pp_data.id.use ;
#line 3533 "syntax8.c"
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
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZInid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3551 "syntax8.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1701 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 3560 "syntax8.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1436 (&ZIid, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 64:
		{
			DECL_SPEC ZIds;
			TYPE ZIt;

			/* BEGINNING OF ACTION: namespace_begin_anon */
			{
#line 1781 "syntax.act"

    decl_loc = crt_loc ;
    begin_namespace ( NULL_id, 1 ) ;
#line 3581 "syntax8.c"
			}
			/* END OF ACTION: namespace_begin_anon */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 3588 "syntax8.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 3596 "syntax8.c"
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
			ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_end_anon */
			{
#line 1785 "syntax.act"

    end_namespace ( 1 ) ;
#line 3622 "syntax8.c"
			}
			/* END OF ACTION: namespace_end_anon */
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
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3643 "syntax8.c"
			}
			/* END OF ACTION: rescan_token */
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3651 "syntax8.c"
			}
			/* END OF ACTION: exp_none */
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
ZRsemicolon_Hx(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 77:
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

		/* BEGINNING OF ACTION: lex_semicolon */
		{
#line 381 "syntax.act"
 (ZIt) = lex_semicolon ; 
#line 3693 "syntax8.c"
		}
		/* END OF ACTION: lex_semicolon */
		/* BEGINNING OF ACTION: expected */
		{
#line 1981 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 3703 "syntax8.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRlogical_Hor_Hexpression(EXP *ZO1194)
{
	EXP ZI1194;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRlogical_Hand_Hexpression (&ZIe);
		ZR1195 (ZIe, &ZI1194);
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
	*ZO1194 = ZI1194;
}

void
ZRconstant_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;

		ZRconditional_Hexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_eval */
		{
#line 653 "syntax.act"

    (ZIe) = convert_reference ( (ZIa), REF_NORMAL ) ;
    (ZIe) = convert_lvalue ( (ZIe) ) ;
#line 3757 "syntax8.c"
		}
		/* END OF ACTION: exp_eval */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRtemplate_Hparam_Hname(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER ZItid;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 203 "syntax.act"

    ZItid = crt_token->pp_data.id.use ;
#line 3789 "syntax8.c"
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

    ZItid = crt_token->pp_data.id.use ;
#line 3802 "syntax8.c"
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

    ZItid = crt_token->pp_data.id.use ;
#line 3815 "syntax8.c"
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

    ZItid = crt_token->pp_data.id.use ;
#line 3828 "syntax8.c"
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
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3846 "syntax8.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: id_anon */
			{
#line 452 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 3861 "syntax8.c"
			}
			/* END OF ACTION: id_anon */
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
	*ZOid = ZIid;
}

void
ZR1262(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 139:
		{
			NAMESPACE ZIpns;
			IDENTIFIER ZIpid;
			IDENTIFIER ZIid;
			NAMESPACE ZIns;

			ADVANCE_LEXER;
			ZRany_Hnested_Hname_Hopt (&ZIpns);
			ZRany_Hclass_Hname (&ZIpid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIpns), (ZIpid), 0 ) ;
    last_namespace = (ZIpns) ;
#line 3903 "syntax8.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: namespace_name */
			{
#line 1788 "syntax.act"

    (ZIns) = find_nspace_id ( (ZIid) ) ;
#line 3911 "syntax8.c"
			}
			/* END OF ACTION: namespace_name */
			/* BEGINNING OF ACTION: using_namespace */
			{
#line 1804 "syntax.act"

    using_namespace ( (ZIns) ) ;
#line 3919 "syntax8.c"
			}
			/* END OF ACTION: using_namespace */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3932 "syntax8.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 83: case 141: case 153:
		{
			ZR1260 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3951 "syntax8.c"
			}
			/* END OF ACTION: exp_none */
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
ZR501(SID_LIST_EXP *ZOq)
{
	SID_LIST_EXP ZIq;

	switch (CURRENT_TERMINAL) {
	case 42:
		{
			ADVANCE_LEXER;
			ZRexpression_Hlist (&ZIq);
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
#line 3992 "syntax8.c"
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
	*ZOq = ZIq;
}

void
ZRptr_Hoperator(TYPE *ZOp)
{
	TYPE ZIp;

	switch (CURRENT_TERMINAL) {
	case 11:
		{
			IDENTIFIER ZIid;
			CV_SPEC ZIcv;

			/* BEGINNING OF EXTRACT: full-name-star */
			{
#line 269 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4024 "syntax8.c"
			}
			/* END OF EXTRACT: full-name-star */
			ADVANCE_LEXER;
			ZRcv_Hqualifier_Hseq_Hopt (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_ptr_mem */
			{
#line 1341 "syntax.act"

    CLASS_TYPE ct = find_class ( (ZIid) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZIid) ) ) ;
	MAKE_type_ptr ( (ZIcv), NULL_type, (ZIp) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZIcv), ct, NULL_type, (ZIp) ) ;
    }
#line 4044 "syntax8.c"
			}
			/* END OF ACTION: type_ptr_mem */
		}
		break;
	case 10:
		{
			IDENTIFIER ZIid;
			CV_SPEC ZIcv;

			/* BEGINNING OF EXTRACT: nested-name-star */
			{
#line 265 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4059 "syntax8.c"
			}
			/* END OF EXTRACT: nested-name-star */
			ADVANCE_LEXER;
			ZRcv_Hqualifier_Hseq_Hopt (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_ptr_mem */
			{
#line 1341 "syntax.act"

    CLASS_TYPE ct = find_class ( (ZIid) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZIid) ) ) ;
	MAKE_type_ptr ( (ZIcv), NULL_type, (ZIp) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZIcv), ct, NULL_type, (ZIp) ) ;
    }
#line 4079 "syntax8.c"
			}
			/* END OF ACTION: type_ptr_mem */
		}
		break;
	case 78:
		{
			CV_SPEC ZIcv;

			ADVANCE_LEXER;
			ZRcv_Hqualifier_Hseq_Hopt (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_ptr */
			{
#line 1331 "syntax.act"

    MAKE_type_ptr ( (ZIcv), NULL_type, (ZIp) ) ;
#line 4099 "syntax8.c"
			}
			/* END OF ACTION: type_ptr */
		}
		break;
	case 33:
		{
			CV_SPEC ZIcv;

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
			ZRcv_Hqualifier_Hseq_Hopt (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_ref */
			{
#line 1336 "syntax.act"

    /* Can't have const-volatile qualified references */
    if ( (ZIcv) ) report ( crt_loc, ERR_dcl_ref_cv ( (ZIcv) ) ) ;
    MAKE_type_ref ( cv_none, NULL_type, (ZIp) ) ;
#line 4133 "syntax8.c"
			}
			/* END OF ACTION: type_ref */
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
}

void
ZRbase_Hspecifier_Hlist(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_base_Hspecifier_Hlist:;
	{
		ZRbase_Hspecifier ();
		/* BEGINNING OF INLINE: 849 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: base-specifier-list */
					goto ZL2_base_Hspecifier_Hlist;
					/* END OF INLINE: base-specifier-list */
				}
				UNREACHED;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 849 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRlinkage_Hspecification(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIc;
		DECL_SPEC ZIa;
		DECL_SPEC ZIb;
		DECL_SPEC ZIds0;
		DECL_SPEC ZIds1;
		EXP ZIe1;

		switch (CURRENT_TERMINAL) {
		case 105:
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
#line 307 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 4219 "syntax8.c"
					}
					/* END OF EXTRACT: string-exp */
					ADVANCE_LEXER;
				}
				break;
			case 20:
				{
					/* BEGINNING OF EXTRACT: wstring-exp */
					{
#line 311 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 4232 "syntax8.c"
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
		/* BEGINNING OF ACTION: linkage_string */
		{
#line 1572 "syntax.act"

    (ZIa) = find_linkage ( (ZIc) ) ;
#line 4248 "syntax8.c"
		}
		/* END OF ACTION: linkage_string */
		/* BEGINNING OF ACTION: linkage_begin */
		{
#line 1576 "syntax.act"

    (ZIb) = crt_linkage ;
    crt_linkage = (ZIa) ;
    IGNORE incr_value ( OPT_VAL_external_specs ) ;
#line 4258 "syntax8.c"
		}
		/* END OF ACTION: linkage_begin */
		/* BEGINNING OF ACTION: dspec_linkage */
		{
#line 1542 "syntax.act"
 (ZIds0) = ( dspec_extern | dspec_c ) ; 
#line 4265 "syntax8.c"
		}
		/* END OF ACTION: dspec_linkage */
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds0) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds1) = ( (ZIds) | (ZIds0) ) ;
#line 4276 "syntax8.c"
		}
		/* END OF ACTION: dspec_join */
		/* BEGINNING OF INLINE: 1067 */
		{
			{
				BASE_TYPE ZI1251;
				TYPE ZI1252;
				CV_SPEC ZI1253;
				DECL_SPEC ZI1254;
				BASE_TYPE ZIbt;
				TYPE ZIt1;
				CV_SPEC ZIcv1;
				DECL_SPEC ZI1607;
				DECL_SPEC ZIds2;

				/* BEGINNING OF ACTION: is_decl_specifier */
				{
#line 2063 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 4298 "syntax8.c"
				}
				/* END OF ACTION: is_decl_specifier */
				if (!ZI0)
					goto ZL4;
				ZRdecl_Hspecifier (ZIt, &ZI1251, &ZI1252, &ZI1253, &ZI1254);
				ZR920 (&ZIt, &ZI1251, &ZI1252, &ZI1253, &ZI1254, &ZIbt, &ZIt1, &ZIcv1, &ZI1607);
				if ((CURRENT_TERMINAL) == 356) {
					RESTORE_LEXER;
					goto ZL1;
				}
				/* BEGINNING OF ACTION: dspec_join */
				{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds1) & (ZI1607) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds1) | (ZI1607) ) ;
#line 4317 "syntax8.c"
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

    (ZIe1) = NULL_exp ;
#line 4330 "syntax8.c"
				}
				/* END OF ACTION: exp_none */
				/* BEGINNING OF ACTION: linkage_end */
				{
#line 1583 "syntax.act"

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZIb) ;
#line 4339 "syntax8.c"
				}
				/* END OF ACTION: linkage_end */
				goto ZL3;
			}
			UNREACHED;
		ZL4:;
			switch (CURRENT_TERMINAL) {
			case 105:
				{
					ZRlinkage_Hspecification (ZIt, ZIds1, &ZIe1);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: linkage_end */
					{
#line 1583 "syntax.act"

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZIb) ;
#line 4360 "syntax8.c"
					}
					/* END OF ACTION: linkage_end */
				}
				break;
			case 64:
				{
					TYPE ZIt2;
					DECL_SPEC ZIds2;

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
					/* BEGINNING OF ACTION: template_check */
					{
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds1) ) ;
#line 4389 "syntax8.c"
					}
					/* END OF ACTION: template_check */
					/* BEGINNING OF ACTION: type_none */
					{
#line 1262 "syntax.act"

    (ZIt2) = NULL_type ;
#line 4397 "syntax8.c"
					}
					/* END OF ACTION: type_none */
					/* BEGINNING OF ACTION: dspec_none */
					{
#line 1530 "syntax.act"
 (ZIds2) = dspec_none ; 
#line 4404 "syntax8.c"
					}
					/* END OF ACTION: dspec_none */
					ZRdeclaration_Hseq_Hopt (ZIt2, ZIds2);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: linkage_end */
					{
#line 1583 "syntax.act"

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZIb) ;
#line 4418 "syntax8.c"
					}
					/* END OF ACTION: linkage_end */
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
					/* BEGINNING OF ACTION: exp_none */
					{
#line 565 "syntax.act"

    (ZIe1) = NULL_exp ;
#line 4439 "syntax8.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			case 134: case 147:
				{
					ZRtemplate_Hdeclaration (ZIt, ZIds1, &ZIe1);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: linkage_end */
					{
#line 1583 "syntax.act"

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZIb) ;
#line 4457 "syntax8.c"
					}
					/* END OF ACTION: linkage_end */
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
#line 4476 "syntax8.c"
					}
					/* END OF ACTION: btype_none */
					/* BEGINNING OF ACTION: type_none */
					{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 4484 "syntax8.c"
					}
					/* END OF ACTION: type_none */
					/* BEGINNING OF ACTION: cv_none */
					{
#line 1206 "syntax.act"
 (ZI1256) = cv_none ; 
#line 4491 "syntax8.c"
					}
					/* END OF ACTION: cv_none */
					ZR1257 (&ZIt, &ZIds1, &ZIbt, &ZIt1, &ZI1256, &ZIe1);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: linkage_end */
					{
#line 1583 "syntax.act"

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZIb) ;
#line 4505 "syntax8.c"
					}
					/* END OF ACTION: linkage_end */
				}
				break;
			case 126: case 139: case 154:
				{
					/* BEGINNING OF ACTION: template_check */
					{
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds1) ) ;
#line 4518 "syntax8.c"
					}
					/* END OF ACTION: template_check */
					ZRdeclaration_Hother (&ZIe1);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: linkage_end */
					{
#line 1583 "syntax.act"

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZIb) ;
#line 4532 "syntax8.c"
					}
					/* END OF ACTION: linkage_end */
				}
				break;
			default:
				goto ZL1;
			}
		ZL3:;
		}
		/* END OF INLINE: 1067 */
		ZIe = ZIe1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1265(EXP *ZI1263, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 72:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRexpression (&ZIa);
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
			ZRassignment_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_cond */
			{
#line 609 "syntax.act"

    (ZIe) = make_cond_exp ( (*ZI1263), (ZIa), (ZIb) ) ;
#line 4586 "syntax8.c"
			}
			/* END OF ACTION: exp_cond */
		}
		break;
	default:
		{
			ZIe = *ZI1263;
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
ZRequality_Hexpression(EXP *ZO1218)
{
	EXP ZI1218;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRrelational_Hexpression (&ZIe);
		ZR1219 (ZIe, &ZI1218);
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
	*ZO1218 = ZI1218;
}

void
ZRinit_Hdeclarator_Hlist(DECL_SPEC ZIds, BASE_TYPE ZIbt, TYPE ZIt, ACCESS_LIST ZIr)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_init_Hdeclarator_Hlist:;
	{
		ZRinit_Hdeclarator (ZIds, ZIbt, ZIt, ZIr);
		/* BEGINNING OF INLINE: 1013 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: declarator_start */
					{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 4653 "syntax8.c"
					}
					/* END OF ACTION: declarator_start */
					/* BEGINNING OF INLINE: init-declarator-list */
					goto ZL2_init_Hdeclarator_Hlist;
					/* END OF INLINE: init-declarator-list */
				}
				UNREACHED;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 1013 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR1267(EXP *ZI1266, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 36:
		{
			EXP ZIb;

			ADVANCE_LEXER;
			ZRassignment_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_assign */
			{
#line 591 "syntax.act"

    (ZIe) = make_assign_exp ( (*ZI1266), (ZIb), 0 ) ;
#line 4697 "syntax8.c"
			}
			/* END OF ACTION: exp_assign */
		}
		break;
	default:
		{
			ZR1265 (ZI1266, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 34: case 45: case 58: case 60:
	case 68: case 70: case 74: case 76:
	case 79: case 81:
		{
			int ZIop;
			EXP ZIb;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 4722 "syntax8.c"
			}
			/* END OF ACTION: lex_crt */
			ZRassignment_Hoperator ();
			ZRassignment_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_assign_op */
			{
#line 596 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_become_exp ( (ZIop), (*ZI1266), (ZIb) ) ;
#line 4737 "syntax8.c"
			}
			/* END OF ACTION: exp_assign_op */
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
ZRmultiplicative_Hexpression(EXP *ZO1234)
{
	EXP ZI1234;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRpm_Hexpression (&ZIe);
		ZR1235 (ZIe, &ZI1234);
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
	*ZO1234 = ZI1234;
}

void
ZR1269(NAMESPACE *ZIns, EXP *ZO1242)
{
	EXP ZI1242;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			IDENTIFIER ZIid;
			TYPE ZI1268;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZIe;

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
#line 4810 "syntax8.c"
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
#line 4823 "syntax8.c"
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
#line 4840 "syntax8.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 4849 "syntax8.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 4859 "syntax8.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4866 "syntax8.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4873 "syntax8.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4882 "syntax8.c"
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

    (ZIe) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 4908 "syntax8.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1243 (ZIe, &ZI1242);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			int ZIq;
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZIe;

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
#line 4938 "syntax8.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 4947 "syntax8.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 4955 "syntax8.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1243 (ZIe, &ZI1242);
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
	*ZO1242 = ZI1242;
}

void
ZR1142(TYPE ZI1140, TYPE *ZO1141)
{
	TYPE ZI1141;

ZL2_1142:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 333:
		{
			TYPE ZIq;
			TYPE ZIt;

			ZRabstract_Hdeclarator_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1383 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1140) ) ? (ZIq) : inject_pre_type ( (ZI1140), (ZIq), 0 ) ) ;
#line 5000 "syntax8.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 1142 */
			ZI1140 = ZIt;
			goto ZL2_1142;
			/* END OF INLINE: 1142 */
		}
		UNREACHED;
	default:
		{
			ZI1141 = ZI1140;
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
	*ZO1141 = ZI1141;
}

/* END OF FILE */
