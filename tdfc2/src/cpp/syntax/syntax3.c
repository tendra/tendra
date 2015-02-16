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


#line 110 "syntax3.c"

void
ZR1431(int *ZIop, int *ZIn1, int *ZIm1, EXP *ZOc)
{
	EXP ZIc;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIt;
		int ZIm2;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_type_id_true */
		{
#line 2121 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
#line 131 "syntax3.c"
		}
		/* END OF ACTION: is_type_id_true */
		if (!ZI0)
			goto ZL2;
		ZRtype_Hid (&ZIt, &ZIm2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIa) = NULL_exp ;
#line 146 "syntax3.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: exp_sizeof */
		{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (*ZIop) ) ;
#line 154 "syntax3.c"
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
			EXP ZI1427;
			EXP ZI1280;
			EXP ZIa;
			int ZIn2;
			int ZIm2;
			TYPE ZIt;

			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 767 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 198 "syntax3.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZI1427);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 770 "syntax.act"

    (ZI1280) = make_paren_exp ( (ZI1427) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 212 "syntax3.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR1242 (ZI1280, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: diff_side_effects */
			{
#line 2020 "syntax.act"

    (ZIn2) = no_side_effects - (*ZIn1) ;
#line 232 "syntax3.c"
			}
			/* END OF ACTION: diff_side_effects */
			/* BEGINNING OF ACTION: diff_type_defns */
			{
#line 2024 "syntax.act"

    (ZIm2) = no_type_defns - (*ZIm1) ;
#line 240 "syntax3.c"
			}
			/* END OF ACTION: diff_type_defns */
			/* BEGINNING OF ACTION: type_of */
			{
#line 1328 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (*ZIop) ) ;
#line 248 "syntax3.c"
			}
			/* END OF ACTION: type_of */
			/* BEGINNING OF ACTION: exp_sizeof */
			{
#line 825 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (*ZIop) ) ;
#line 256 "syntax3.c"
			}
			/* END OF ACTION: exp_sizeof */
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
	*ZOc = ZIc;
}

void
ZRparameter_Hdeclarator_Hopt(TYPE ZIp, TYPE *ZOt, IDENTIFIER *ZOid)
{
	TYPE ZIt;
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZI1374;
		TYPE ZI1375;
		TYPE ZIq;

		/* BEGINNING OF ACTION: is_parameter */
		{
#line 2131 "syntax.act"

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
#line 292 "syntax3.c"
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
#line 307 "syntax3.c"
		}
		/* END OF ACTION: type_none */
		/* BEGINNING OF ACTION: declarator_posn */
		{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1374) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 316 "syntax3.c"
		}
		/* END OF ACTION: declarator_posn */
		ZR1163 (ZI1375, ZI1374, &ZIq, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 329 "syntax3.c"
		}
		/* END OF ACTION: type_inject */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIq;

			ADVANCE_LEXER;
			ZR1373 (&ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 352 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 332:
		{
			IDENTIFIER ZI1372;
			int ZIw;
			TYPE ZI1378;
			IDENTIFIER ZI1379;
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
#line 461 "syntax.act"

    (ZI1372) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 380 "syntax3.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIw) = 1 ; 
#line 387 "syntax3.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1201 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1372) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 398 "syntax3.c"
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
#line 413 "syntax3.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 468 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZI1379) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 424 "syntax3.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1379) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 433 "syntax3.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1163 (ZI1378, ZI1379, &ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 446 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZI1376;
			IDENTIFIER ZI1377;
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
#line 482 "syntax3.c"
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
#line 506 "syntax3.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZI1377) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 515 "syntax3.c"
			}
			/* END OF ACTION: declarator_posn */
			ZR1163 (ZI1376, ZI1377, &ZIq, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 528 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	case 10: case 11: case 33: case 78:
		{
			TYPE ZI1380;
			TYPE ZI1381;
			TYPE ZIq;

			ZRptr_Hoperator (&ZI1380);
			ZRparameter_Hdeclarator_Haux_Hopt (&ZI1381, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1399 "syntax.act"

    (ZIq) = ( IS_NULL_type ( (ZI1381) ) ? (ZI1380) : inject_pre_type ( (ZI1381), (ZI1380), 0 ) ) ;
#line 550 "syntax3.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 558 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	default:
		{
			TYPE ZIq;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIq) = NULL_type ;
#line 572 "syntax3.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: id_anon */
			{
#line 468 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 583 "syntax3.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_posn */
			{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 592 "syntax3.c"
			}
			/* END OF ACTION: declarator_posn */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 600 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
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

void
ZRasm_Hdefinition(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
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
#line 323 "syntax.act"

    ZIa = crt_token->pp_data.exp ;
#line 651 "syntax3.c"
					}
					/* END OF EXTRACT: string-exp */
					ADVANCE_LEXER;
				}
				break;
			case 20:
				{
					/* BEGINNING OF EXTRACT: wstring-exp */
					{
#line 327 "syntax.act"

    ZIa = crt_token->pp_data.exp ;
#line 664 "syntax3.c"
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
		ZR500 (&ZIp);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_asm */
		{
#line 1898 "syntax.act"

    (ZIe) = make_asm ( (ZIa), (ZIp) ) ;
#line 685 "syntax3.c"
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
ZR1432(int *ZIb, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 140:
		{
			int ZItd;
			SID_LIST_EXP ZIp;
			TYPE ZIt;
			int ZIn;
			int ZId;
			EXP ZIs;
			EXP ZIi;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_decl_begin */
			{
#line 420 "syntax.act"

    (ZItd) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
#line 733 "syntax3.c"
			}
			/* END OF ACTION: type_decl_begin */
			ZRnew_Hplace_Hand_Htype (&ZIp, &ZIt, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_decl_end */
			{
#line 426 "syntax.act"

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
#line 756 "syntax3.c"
			}
			/* END OF ACTION: type_decl_end */
			/* BEGINNING OF ACTION: exp_new_start */
			{
#line 750 "syntax.act"

    (ZIs) = begin_new_try () ;
#line 764 "syntax3.c"
			}
			/* END OF ACTION: exp_new_start */
			ZRnew_Hinitialiser_Hopt (ZIt, &ZIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_new_end */
			{
#line 754 "syntax.act"

    (ZIa) = end_new_try ( (ZIs), (ZIi) ) ;
#line 777 "syntax3.c"
			}
			/* END OF ACTION: exp_new_end */
			/* BEGINNING OF ACTION: exp_new */
			{
#line 738 "syntax.act"

    (ZIe) = make_new_exp ( (ZIt), (ZIn) + (ZId), (*ZIb), (ZIp), (ZIa) ) ;
#line 785 "syntax3.c"
			}
			/* END OF ACTION: exp_new */
		}
		break;
	case 131:
		{
			int ZIop;
			EXP ZIa;

			ZRdelete_Hoperator (&ZIop);
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_delete */
			{
#line 634 "syntax.act"

    (ZIe) = make_delete_exp ( (ZIop), (*ZIb), (ZIa) ) ;
#line 806 "syntax3.c"
			}
			/* END OF ACTION: exp_delete */
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
ZRnew_Hinitialiser_Hopt(TYPE ZIt, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			SID_LIST_EXP ZIp;

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
			/* BEGINNING OF ACTION: exp_new_init */
			{
#line 742 "syntax.act"

    (ZIe) = make_new_init ( (ZIt), (ZIp), 1 ) ;
#line 851 "syntax3.c"
			}
			/* END OF ACTION: exp_new_init */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_new_none */
			{
#line 746 "syntax.act"

    (ZIe) = make_new_init ( (ZIt), NULL_list ( EXP ), 0 ) ;
#line 863 "syntax3.c"
			}
			/* END OF ACTION: exp_new_none */
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
ZRconditional_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZI1262;

		ZRlogical_Hor_Hexpression (&ZI1262);
		ZR1264 (&ZI1262, &ZIe);
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
ZRparameter_Htail(int ZIw, TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIell;
		CV_SPEC ZIcv;
		SID_LIST_TYPE ZIex;

		ZRparameter_Hdeclaration_Hclause (&ZIell);
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
		ZRcv_Hqualifier_Hseq_Hopt (&ZIcv);
		ZRexception_Hspecification_Hopt (&ZIex);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_func */
		{
#line 1367 "syntax.act"

    CV_SPEC cv = func_linkage ( (ZIcv) ) ;
    if ( (ZIw) ) (ZIell) |= FUNC_WEAK ;
    (ZIt) = make_func_type ( NULL_type, (ZIell), cv, (ZIex) ) ;
#line 942 "syntax3.c"
		}
		/* END OF ACTION: type_func */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZR1433(int *ZOop)
{
	int ZIop;

	switch (CURRENT_TERMINAL) {
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
			ZR1434 (&ZIop);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_delete */
			{
#line 402 "syntax.act"
 (ZIop) = lex_delete ; 
#line 988 "syntax3.c"
			}
			/* END OF ACTION: lex_delete */
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
	*ZOop = ZIop;
}

void
ZR1179(TYPE ZI1173, IDENTIFIER ZI1174, int ZI1175, TYPE *ZO1176, IDENTIFIER *ZO1177, int *ZO1178)
{
	TYPE ZI1176;
	IDENTIFIER ZI1177;
	int ZI1178;

ZL2_1179:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 332:
		{
			IDENTIFIER ZIid;
			QUALIFIER ZIi;
			int ZIa;
			TYPE ZIq;
			int ZIc;
			TYPE ZIt;

			ZIid = ZI1174;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIa) = crt_templ_qualifier ;
#line 1029 "syntax3.c"
			}
			/* END OF ACTION: qual_get */
			ZRdeclarator_Htail (ZIid, &ZIq, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialiser_bad */
			{
#line 1776 "syntax.act"

    if ( (ZI1175) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 1042 "syntax3.c"
			}
			/* END OF ACTION: initialiser_bad */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1173) ) ? (ZIq) : inject_pre_type ( (ZI1173), (ZIq), 0 ) ) ;
#line 1050 "syntax3.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: qual_set */
			{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIa) ;
#line 1059 "syntax3.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF INLINE: 1179 */
			ZI1173 = ZIt;
			ZI1174 = ZIid;
			ZI1175 = ZIc;
			goto ZL2_1179;
			/* END OF INLINE: 1179 */
		}
		/*UNREACHED*/
	default:
		{
			ZI1176 = ZI1173;
			ZI1177 = ZI1174;
			ZI1178 = ZI1175;
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
	*ZO1176 = ZI1176;
	*ZO1177 = ZI1177;
	*ZO1178 = ZI1178;
}

void
ZR1434(int *ZOop)
{
	int ZIop;

	switch (CURRENT_TERMINAL) {
	case 40:
		{
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
			/* BEGINNING OF ACTION: lex_delete_array */
			{
#line 404 "syntax.act"
 (ZIop) = lex_delete_Harray ; 
#line 1115 "syntax3.c"
			}
			/* END OF ACTION: lex_delete_array */
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
	case 286: case 298: case 299: case 324:
	case 330: case 346:
		{
			EXP ZIe;

			ZRexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: anachronism_delete */
			{
#line 1957 "syntax.act"

    /* Array size in 'delete []' */
    old_delete_array ( (ZIe) ) ;
#line 1150 "syntax3.c"
			}
			/* END OF ACTION: anachronism_delete */
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
			/* BEGINNING OF ACTION: lex_delete_array */
			{
#line 404 "syntax.act"
 (ZIop) = lex_delete_Harray ; 
#line 1170 "syntax3.c"
			}
			/* END OF ACTION: lex_delete_array */
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
ZRdeclarator_Hid(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			ADVANCE_LEXER;
			ZR1348 (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1213 "syntax3.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1347 (&ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1233 "syntax3.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1346 (&ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 4:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 231 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 1253 "syntax3.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 509 "syntax.act"

    (ZIid) = (ZIuid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 1264 "syntax3.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141:
		{
			ZRunqualified_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZItid;

			ZRunqualified_Htype (&ZItid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_type */
			{
#line 1734 "syntax.act"

    (ZIid) = constr_name ( last_namespace, (ZItid) ) ;
#line 1293 "syntax3.c"
			}
			/* END OF ACTION: declarator_type */
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
parse_type(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		parse_tok_type (&ZIt);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_check */
		{
#line 1332 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 1330 "syntax3.c"
		}
		/* END OF ACTION: type_check */
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
#line 1345 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1353 "syntax3.c"
		}
		/* END OF ACTION: type_none */
	}
ZL0:;
	*ZOt = ZIt;
}

void
ZRcondition_Hdeclarator(IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIs;
		BASE_TYPE ZIb1;
		TYPE ZI1511;
		CV_SPEC ZI1512;
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;
		TYPE ZIt2;
		DECL_SPEC ZIds;
		TYPE ZIt3;
		IDENTIFIER ZIid;
		int ZIc;
		TYPE ZIt;

		/* BEGINNING OF ACTION: is_type_specifier */
		{
#line 2126 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 1391 "syntax3.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL1;
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIs) = NULL_type ;
#line 1401 "syntax3.c"
		}
		/* END OF ACTION: type_none */
		ZRtype_Hspecifier (ZIs, &ZIb1, &ZI1511, &ZI1512);
		ZR887 (&ZIb1, &ZI1511, &ZI1512, &ZIbt, &ZIt1, &ZIcv1);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1546 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 1414 "syntax3.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1573 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1425 "syntax3.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1433 "syntax3.c"
		}
		/* END OF ACTION: declarator_start */
		ZRdeclarator (ZIt2, &ZIt3, &ZIid, &ZIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: initialiser_bad */
		{
#line 1776 "syntax.act"

    if ( (ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 1446 "syntax3.c"
		}
		/* END OF ACTION: initialiser_bad */
		/* BEGINNING OF ACTION: cond_type */
		{
#line 1100 "syntax.act"

    (ZIt) = make_cond_type ( (ZIt3) ) ;
#line 1454 "syntax3.c"
		}
		/* END OF ACTION: cond_type */
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
#line 1479 "syntax3.c"
		}
		/* END OF ACTION: declare_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 1489 "syntax3.c"
		}
		/* END OF ACTION: access_check_decl */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOd = ZId;
}

void
ZRdesignator_Hlist(OFFSET ZIb, TYPE ZIs, OFFSET *ZO1154, TYPE *ZO1155)
{
	OFFSET ZI1154;
	TYPE ZI1155;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_designator_Hlist:;
	{
		OFFSET ZIa;
		TYPE ZIt;

		ZRdesignator (ZIb, ZIs, &ZIa, &ZIt);
		/* BEGINNING OF INLINE: 1153 */
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
				/*UNREACHED*/
			default:
				{
					ZI1154 = ZIa;
					ZI1155 = ZIt;
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 1153 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO1154 = ZI1154;
	*ZO1155 = ZI1155;
}

void
ZR1435(IDENTIFIER *ZIid, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 36:
		{
			NAMESPACE ZIpns;
			IDENTIFIER ZIpid;
			IDENTIFIER ZImid;
			NAMESPACE ZIns;

			ADVANCE_LEXER;
			ZRany_Hnested_Hname_Hopt (&ZIpns);
			ZRany_Hclass_Hname (&ZIpid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZImid) = check_id ( (ZIpns), (ZIpid), 0 ) ;
    last_namespace = (ZIpns) ;
#line 1576 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: namespace_name */
			{
#line 1804 "syntax.act"

    (ZIns) = find_nspace_id ( (ZImid) ) ;
#line 1584 "syntax3.c"
			}
			/* END OF ACTION: namespace_name */
			/* BEGINNING OF ACTION: qual_none */
			{
#line 551 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 1594 "syntax3.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: namespace_alias */
			{
#line 1808 "syntax.act"

    alias_namespace ( (*ZIid), (ZIns) ) ;
#line 1602 "syntax3.c"
			}
			/* END OF ACTION: namespace_alias */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1615 "syntax3.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	case 64:
		{
			DECL_SPEC ZIds;
			TYPE ZIt;

			/* BEGINNING OF ACTION: namespace_begin */
			{
#line 1787 "syntax.act"

    begin_namespace ( (*ZIid), 0 ) ;
#line 1630 "syntax3.c"
			}
			/* END OF ACTION: namespace_begin */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1637 "syntax3.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1645 "syntax3.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_end */
			{
#line 1792 "syntax.act"

    end_namespace ( 0 ) ;
#line 1671 "syntax3.c"
			}
			/* END OF ACTION: namespace_end */
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
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 1692 "syntax3.c"
			}
			/* END OF ACTION: rescan_token */
			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1700 "syntax3.c"
			}
			/* END OF ACTION: exp_none */
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
ZRany_Hqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 9:
		{
			ZRfull_Hqualified_Htype (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			ZRqualified_Htype (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 83:
		{
			ZRtop_Hqualified_Htype (&ZIid);
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
	*ZOid = ZIid;
}

void
ZRnew_Hdeclarator_Hopt(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIp;
		TYPE ZIq;

		/* BEGINNING OF ACTION: is_new_ptr_operator */
		{
#line 2101 "syntax.act"

    /* Resolve pointer declarators from expressions */
    (ZI0) = predict_ptr ( 0 ) ;
#line 1782 "syntax3.c"
		}
		/* END OF ACTION: is_new_ptr_operator */
		if (!ZI0)
			goto ZL2;
		ZRptr_Hoperator (&ZIp);
		ZRnew_Hdeclarator_Hopt (&ZIq);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_build */
		{
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 1798 "syntax3.c"
		}
		/* END OF ACTION: type_build */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 66:
		{
			ZRdirect_Hnew_Hdeclarator (&ZIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1822 "syntax3.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZRdeclaration_Hcond_Hhead(EXP *ZO1146)
{
	EXP ZI1146;

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
#line 1855 "syntax3.c"
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
#line 1870 "syntax3.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: decl_hash_if */
		{
#line 1902 "syntax.act"

    target_decl ( lex_if, (ZIc) ) ;
#line 1878 "syntax3.c"
		}
		/* END OF ACTION: decl_hash_if */
		ZRdeclaration_Hcond_Hbody ();
		ZR1147 (ZIp, &ZI1146);
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
	*ZO1146 = ZI1146;
}

void
ZRdeclarator_Haux(TYPE *ZOt, IDENTIFIER *ZOid, int *ZOc)
{
	TYPE ZIt;
	IDENTIFIER ZIid;
	int ZIc;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8:
	case 9: case 65: case 83: case 141:
		{
			ZRdirect_Hdeclarator (&ZIt, &ZIid, &ZIc);
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
			ZRdeclarator_Haux (&ZIq, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 1931 "syntax3.c"
			}
			/* END OF ACTION: type_build */
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
	*ZOt = ZIt;
	*ZOid = ZIid;
	*ZOc = ZIc;
}

void
ZRshift_Hexpression(EXP *ZO1225)
{
	EXP ZI1225;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRadditive_Hexpression (&ZIe);
		ZR1226 (ZIe, &ZI1225);
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
	*ZO1225 = ZI1225;
}

void
ZRfor_Hcond_Hstatement(EXP *ZOa, EXP *ZOe)
{
	EXP ZIa;
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZId;
		EXP ZI1602;
		EXP ZIc;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2086 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 1999 "syntax3.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: cond_start */
		{
#line 1092 "syntax.act"

    begin_cond () ;
#line 2009 "syntax3.c"
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
		ZRinitialiser_Hexpression (&ZI1602);
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
#line 2035 "syntax3.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1762 "syntax.act"

    int def = init_object ( (ZId), (ZI1602) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 2044 "syntax3.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 2054 "syntax3.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1713 "syntax.act"

    end_declarator ( (ZId), 1 ) ;
#line 2062 "syntax3.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: cond_end */
		{
#line 1095 "syntax.act"

    (ZIc) = end_cond () ;
    in_declaration-- ;
#line 2071 "syntax3.c"
		}
		/* END OF ACTION: cond_end */
		/* BEGINNING OF ACTION: bind_temporary */
		{
#line 1087 "syntax.act"

    (ZIa) = bind_temporary ( (ZIc) ) ;
#line 2079 "syntax3.c"
		}
		/* END OF ACTION: bind_temporary */
		/* BEGINNING OF ACTION: exp_location */
		{
#line 710 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIa), (ZIe) ) ;
#line 2087 "syntax3.c"
		}
		/* END OF ACTION: exp_location */
		switch (CURRENT_TERMINAL) {
		case 77:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZIa) = NULL_exp ;
#line 2110 "syntax3.c"
			}
			/* END OF ACTION: exp_none */
			/* BEGINNING OF ACTION: exp_location */
			{
#line 710 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIa), (ZIe) ) ;
#line 2118 "syntax3.c"
			}
			/* END OF ACTION: exp_location */
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
	case 286: case 298: case 299: case 324:
	case 330: case 346:
		{
			EXP ZIc;

			ZRexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 1087 "syntax.act"

    (ZIa) = bind_temporary ( (ZIc) ) ;
#line 2152 "syntax3.c"
			}
			/* END OF ACTION: bind_temporary */
			/* BEGINNING OF ACTION: exp_location */
			{
#line 710 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIa), (ZIe) ) ;
#line 2160 "syntax3.c"
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
		break;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOa = ZIa;
	*ZOe = ZIe;
}

void
ZRconversion_Hdeclarator_Hopt(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIp;
		TYPE ZIq;

		/* BEGINNING OF ACTION: is_ptr_operator */
		{
#line 2106 "syntax.act"

    /* Resolve pointer or reference declarators from expressions */
    (ZI0) = predict_ptr ( 1 ) ;
#line 2202 "syntax3.c"
		}
		/* END OF ACTION: is_ptr_operator */
		if (!ZI0)
			goto ZL2;
		ZRptr_Hoperator (&ZIp);
		ZRconversion_Hdeclarator_Hopt (&ZIq);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_build */
		{
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 0 ) ) ;
#line 2218 "syntax3.c"
		}
		/* END OF ACTION: type_build */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 2233 "syntax3.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZR1438(EXP *ZI1436, EXP *ZOe)
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
	case 330: case 346:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 566 "syntax.act"

    CONS_exp ( (*ZI1436), (ZIq), (ZIp) ) ;
#line 2283 "syntax3.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 621 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 2291 "syntax3.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	default:
		{
			ZIe = *ZI1436;
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
ZRenumerator_Hdefinition(IDENTIFIER ZIe)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZIeid;
		IDENTIFIER ZIid;
		EXP ZIc;

		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 219 "syntax.act"

    ZIeid = crt_token->pp_data.id.use ;
#line 2333 "syntax3.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: namespace-name */
					{
#line 227 "syntax.act"

    ZIeid = crt_token->pp_data.id.use ;
#line 2346 "syntax3.c"
					}
					/* END OF EXTRACT: namespace-name */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 231 "syntax.act"

    ZIeid = crt_token->pp_data.id.use ;
#line 2359 "syntax3.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 223 "syntax.act"

    ZIeid = crt_token->pp_data.id.use ;
#line 2372 "syntax3.c"
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
#line 509 "syntax.act"

    (ZIid) = (ZIeid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 2390 "syntax3.c"
		}
		/* END OF ACTION: namespace_simple */
		/* BEGINNING OF ACTION: declarator_posn */
		{
#line 1717 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 2399 "syntax3.c"
		}
		/* END OF ACTION: declarator_posn */
		ZRmember_Hspecifier_Hopt (&ZIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_enum */
		{
#line 1690 "syntax.act"

    IDENTIFIER id = constr_name ( last_namespace, (ZIid) ) ;
    IGNORE make_enumerator ( (ZIe), id, (ZIc) ) ;
#line 2413 "syntax3.c"
		}
		/* END OF ACTION: declare_enum */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRdeclarator(TYPE ZIp, TYPE *ZOt, IDENTIFIER *ZOid, int *ZOc)
{
	TYPE ZIt;
	IDENTIFIER ZIid;
	int ZIc;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIq;

		ZRdeclarator_Haux (&ZIq, &ZIid, &ZIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: template_decl */
		{
#line 1866 "syntax.act"

    if ( !IS_NULL_type ( (ZIp) ) ) template_decl ( (ZIp) ) ;
#line 2446 "syntax3.c"
		}
		/* END OF ACTION: template_decl */
		/* BEGINNING OF ACTION: type_inject */
		{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 2454 "syntax3.c"
		}
		/* END OF ACTION: type_inject */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOid = ZIid;
	*ZOc = ZIc;
}

void
ZRinitialiser_Hopt(int ZIc, IDENTIFIER ZId, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		SID_LIST_EXP ZIp;

		/* BEGINNING OF ACTION: is_true */
		{
#line 2064 "syntax.act"

    (ZI0) = (ZIc) ;
#line 2484 "syntax3.c"
		}
		/* END OF ACTION: is_true */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: rescan_init */
		{
#line 2161 "syntax.act"

    if ( crt_lex_token == lex_open_Hinit ) {
	crt_lex_token = lex_open_Hround ;
    } else {
	RESCAN_LEXER ;
    }
#line 2498 "syntax3.c"
		}
		/* END OF ACTION: rescan_init */
		ZRinitialiser_Hexp_Hlist (ZId, &ZIp);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_initialiser */
		{
#line 702 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 2511 "syntax3.c"
		}
		/* END OF ACTION: exp_initialiser */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			ZRinitialiser_Hclause (ZId, &ZIe);
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
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2543 "syntax3.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
parse_file(TYPE ZIt, DECL_SPEC ZIds)
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
		EXP ZIe;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2079 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2581 "syntax3.c"
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
#line 2600 "syntax3.c"
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
#line 2613 "syntax3.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: declare_extern */
		{
#line 1744 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2621 "syntax3.c"
		}
		/* END OF ACTION: declare_extern */
		ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
		switch (CURRENT_TERMINAL) {
		case 32:
			break;
		case 355:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
		}
		break;
	case 105:
		{
			EXP ZIe;

			ZRlinkage_Hspecification (ZIt, ZIds, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1744 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2659 "syntax3.c"
			}
			/* END OF ACTION: declare_extern */
			ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
			switch (CURRENT_TERMINAL) {
			case 32:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 134: case 147:
		{
			EXP ZIe;

			ZRtemplate_Hdeclaration (ZIt, ZIds, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1744 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2689 "syntax3.c"
			}
			/* END OF ACTION: declare_extern */
			ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
			switch (CURRENT_TERMINAL) {
			case 32:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
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
			EXP ZIe;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2720 "syntax3.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2728 "syntax3.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZI1255) = cv_none ; 
#line 2735 "syntax3.c"
			}
			/* END OF ACTION: cv_none */
			ZR1256 (&ZIt, &ZIds, &ZIbt, &ZIt1, &ZI1255, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1744 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2748 "syntax3.c"
			}
			/* END OF ACTION: declare_extern */
			ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
			switch (CURRENT_TERMINAL) {
			case 32:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 26: case 30: case 126: case 139:
	case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1861 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2773 "syntax3.c"
			}
			/* END OF ACTION: template_check */
			ZR1257 ();
			ZRdeclaration_Hseq_Hopt (ZIt, ZIds);
			switch (CURRENT_TERMINAL) {
			case 32:
				break;
			case 355:
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
#line 1975 "syntax.act"

    /* Unrecoverable syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    err = concat_error ( err, ERR_lex_abort () ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2805 "syntax3.c"
		}
		/* END OF ACTION: error_fatal */
	}
ZL0:;
}

void
ZRfunction_Hdefinition_Hbody(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIc;
		EXP ZIa;

		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 907 "syntax.act"

    (ZIc) = begin_compound_stmt ( 1 ) ;
#line 2829 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_begin */
		/* BEGINNING OF INLINE: 1027 */
		{
			switch (CURRENT_TERMINAL) {
			case 41: case 64:
				{
					ZRfunction_Hbody (ZIc, &ZIa);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 151:
				{
					EXP ZIb;

					ZRfunction_Htry_Hblock (&ZIb);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: stmt_compound_add */
					{
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZIb) ) ;
#line 2858 "syntax3.c"
					}
					/* END OF ACTION: stmt_compound_add */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 1027 */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2873 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: access_check */
		{
#line 1462 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
#line 2883 "syntax3.c"
		}
		/* END OF ACTION: access_check */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRexport_Hopt(int *ZOx)
{
	int ZIx;

	switch (CURRENT_TERMINAL) {
	case 134:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIx) = 1 ; 
#line 2908 "syntax3.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIx) = 0 ; 
#line 2919 "syntax3.c"
			}
			/* END OF ACTION: bool_false */
		}
		break;
	case 355:
		return;
	}
	*ZOx = ZIx;
}

void
parse_offset(OFFSET ZIb, TYPE ZIs, OFFSET *ZOa, TYPE *ZOt)
{
	OFFSET ZIa;
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		OFFSET ZIc;
		TYPE ZIu;

		ZRmember_Hdesignator (ZIb, ZIs, &ZIc, &ZIu);
		/* BEGINNING OF INLINE: 1132 */
		{
			switch (CURRENT_TERMINAL) {
			case 46: case 66:
				{
					ZRdesignator_Hlist (ZIc, ZIu, &ZIa, &ZIt);
					if ((CURRENT_TERMINAL) == 355) {
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
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 1132 */
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
#line 2980 "syntax3.c"
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
parse_nat(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRconstant_Hexpression (&ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
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
#line 3017 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3025 "syntax3.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZR1441(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 298:
		{
			EXP ZI1599;
			EXP ZI1600;

			ADVANCE_LEXER;
			ZRexpression (&ZI1599);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_set */
			{
#line 821 "syntax.act"

    (ZI1600) = make_set_exp ( (ZI1599) ) ;
#line 3055 "syntax3.c"
			}
			/* END OF ACTION: exp_set */
			ZR1601 (&ZI1600, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 324:
		{
			EXP ZI1596;
			EXP ZI1597;

			ADVANCE_LEXER;
			ZRexpression (&ZI1596);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 861 "syntax.act"

    (ZI1597) = make_unused_exp ( (ZI1596) ) ;
#line 3081 "syntax3.c"
			}
			/* END OF ACTION: exp_unused */
			ZR1601 (&ZI1597, &ZIe);
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
ZR1314(NAMESPACE *ZIns, IDENTIFIER *ZI1312, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			BASE_TYPE ZIbt1;
			NAMESPACE ZIns1;
			QUALIFIER ZIi;
			int ZIb;
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;
			IDENTIFIER ZIuid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 3125 "syntax3.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 3135 "syntax3.c"
			}
			/* END OF ACTION: qual_get */
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
			ZRpseudo_Hdestr_Hsuffix (&ZIid2, &ZIbt2);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 3162 "syntax3.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1312), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 3170 "syntax3.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 3179 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1312;
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
	*ZOid = ZIid;
}

void
ZRinitialiser_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRassignment_Hexpression (&ZIe);
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
parse_param(TYPE ZIs, int ZIp, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRparameter_Hdeclaration (ZIs, ZIp, &ZId);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
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
#line 3249 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: decl_none */
		{
#line 1175 "syntax.act"

    (ZId) = NULL_id ;
#line 3257 "syntax3.c"
		}
		/* END OF ACTION: decl_none */
	}
ZL0:;
	*ZOd = ZId;
}

void
ZR1442(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 96:
		{
			EXP ZIc;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_case_begin */
			{
#line 887 "syntax.act"

    (ZIa) = begin_case_stmt ( (ZIc), 0 ) ;
#line 3288 "syntax3.c"
			}
			/* END OF ACTION: stmt_case_begin */
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 1016 "syntax.act"

    unreached_fall = 0 ;
#line 3296 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_set */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_case_end */
			{
#line 891 "syntax.act"

    (ZIe) = end_case_stmt ( (ZIa), (ZIb) ) ;
#line 3316 "syntax3.c"
			}
			/* END OF ACTION: stmt_case_end */
		}
		break;
	case 100:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_default_begin */
			{
#line 936 "syntax.act"

    (ZIa) = begin_default_stmt ( 0 ) ;
#line 3332 "syntax3.c"
			}
			/* END OF ACTION: stmt_default_begin */
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 1016 "syntax.act"

    unreached_fall = 0 ;
#line 3340 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_set */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_default_end */
			{
#line 940 "syntax.act"

    (ZIe) = end_default_stmt ( (ZIa), (ZIb) ) ;
#line 3360 "syntax3.c"
			}
			/* END OF ACTION: stmt_default_end */
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
ZR1315(NAMESPACE *ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			NAMESPACE ZI1397;
			IDENTIFIER ZI1398;

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
#line 3404 "syntax3.c"
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
#line 3417 "syntax3.c"
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
#line 488 "syntax.act"

    (ZI1397) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI1397) ;
#line 3435 "syntax3.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZI1398) = check_id ( (ZI1397), (ZItid), 0 ) ;
    last_namespace = (ZI1397) ;
#line 3444 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
			ZR1400 (ZIns, &ZI1398, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 3: case 5: case 6:
	case 43: case 141: case 147:
		{
			NAMESPACE ZI1395;

			/* BEGINNING OF ACTION: namespace_global */
			{
#line 488 "syntax.act"

    (ZI1395) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI1395) ;
#line 3466 "syntax3.c"
			}
			/* END OF ACTION: namespace_global */
			ZR1396 (&ZI1395, &ZIid);
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
	*ZOid = ZIid;
}

void
ZRtype_Hspecifier_Hseq(BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIs;
		BASE_TYPE ZIb1;
		TYPE ZIt1;
		CV_SPEC ZIcv1;

		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIs) = NULL_type ;
#line 3510 "syntax3.c"
		}
		/* END OF ACTION: type_none */
		ZRtype_Hspecifier (ZIs, &ZIb1, &ZIt1, &ZIcv1);
		/* BEGINNING OF INLINE: 879 */
		{
			switch (CURRENT_TERMINAL) {
			case 2: case 7: case 8: case 9:
			case 25: case 83: case 97: case 98:
			case 102: case 104: case 106: case 110:
			case 111: case 114: case 115: case 118:
			case 121: case 122: case 123: case 124:
			case 127: case 129: case 153: case 156:
			case 185: case 286: case 299:
				{
					BASE_TYPE ZIb2;
					TYPE ZIt2;
					CV_SPEC ZIcv2;

					ZRtype_Hspecifier_Hseq (&ZIb2, &ZIt2, &ZIcv2);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: btype_join */
					{
#line 1257 "syntax.act"

    if ( (ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (ZIb1) | (ZIb2) ) ;
    }
#line 3543 "syntax3.c"
					}
					/* END OF ACTION: btype_join */
					/* BEGINNING OF ACTION: type_join */
					{
#line 1312 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 3559 "syntax3.c"
					}
					/* END OF ACTION: type_join */
					/* BEGINNING OF ACTION: cv_join */
					{
#line 1227 "syntax.act"

    CV_SPEC c = ( (ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIcv1) | (ZIcv2) ) ;
#line 3569 "syntax3.c"
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
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 879 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		NAMESPACE ZIns;
		IDENTIFIER ZItid;

		switch (CURRENT_TERMINAL) {
		case 8:
			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3617 "syntax3.c"
			}
			/* END OF EXTRACT: nested-name */
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
#line 3639 "syntax3.c"
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
#line 3652 "syntax3.c"
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
#line 495 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (ZIns) ;
#line 3669 "syntax3.c"
		}
		/* END OF ACTION: namespace_nested */
		/* BEGINNING OF ACTION: namespace_id */
		{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 3678 "syntax3.c"
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
ZRtype_Hid_Hlist(SID_LIST_TYPE *ZOp)
{
	SID_LIST_TYPE ZIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIs;
		int ZIn;
		TYPE ZIt;
		SID_LIST_TYPE ZIq;

		ZRtype_Hid (&ZIs, &ZIn);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exception_check */
		{
#line 1944 "syntax.act"

    (ZIt) = check_except_type ( (ZIs), (ZIn) ) ;
#line 3714 "syntax3.c"
		}
		/* END OF ACTION: exception_check */
		/* BEGINNING OF INLINE: 1107 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					ZR1386 (&ZIq);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: list_type_null */
					{
#line 1411 "syntax.act"

    (ZIq) = NULL_list ( TYPE ) ;
#line 3737 "syntax3.c"
					}
					/* END OF ACTION: list_type_null */
				}
				break;
			}
		}
		/* END OF INLINE: 1107 */
		/* BEGINNING OF ACTION: list_type_cons */
		{
#line 1415 "syntax.act"

    (ZIp) = cons_type_set ( (ZIq), (ZIt) ) ;
#line 3750 "syntax3.c"
		}
		/* END OF ACTION: list_type_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOp = ZIp;
}

void
ZR1317(NAMESPACE *ZIns, NAMESPACE *ZI1316, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZI1401;
			IDENTIFIER ZItid;
			IDENTIFIER ZI1402;

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
    ZI1401 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 3788 "syntax3.c"
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

    ZI1401 = crt_token->pp_data.id.use ;
#line 3801 "syntax3.c"
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
#line 495 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1316) ;
#line 3818 "syntax3.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZItid) = check_id ( (*ZI1316), (ZI1401), 0 ) ;
    last_namespace = (*ZI1316) ;
#line 3827 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZI1402) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 3836 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
			ZR1404 (ZIns, &ZI1402, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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
			IDENTIFIER ZIqid;

			ZRtemplate_Hopt (*ZI1316, &ZIq);
			ZRnested_Hid (*ZI1316, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 495 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1316) ;
#line 3865 "syntax3.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 521 "syntax.act"

    (ZIqid) = check_id ( (*ZI1316), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZI1316) ;
#line 3874 "syntax3.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIqid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 3883 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 43:
		{
			IDENTIFIER ZIid1;
			BASE_TYPE ZIbt1;
			NAMESPACE ZIns1;
			QUALIFIER ZIi;
			int ZIb;
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;
			IDENTIFIER ZIuid;

			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 495 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1316) ;
#line 3905 "syntax3.c"
			}
			/* END OF ACTION: namespace_nested */
			/* BEGINNING OF ACTION: namespace_type */
			{
#line 526 "syntax.act"

    (ZIid1) = DEREF_id ( nspace_name ( (*ZI1316) ) ) ;
#line 3913 "syntax3.c"
			}
			/* END OF ACTION: namespace_type */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 3920 "syntax3.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZI1316;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 3930 "syntax3.c"
			}
			/* END OF ACTION: qual_get */
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
			ZRpseudo_Hdestr_Hsuffix (&ZIid2, &ZIbt2);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 3957 "syntax3.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 3965 "syntax3.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 3974 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
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
ZR1190(EXP ZI1184, EXP ZI1185, int ZI1186, EXP *ZO1187, EXP *ZO1188, int *ZO1189)
{
	EXP ZI1187;
	EXP ZI1188;
	int ZI1189;

ZL2_1190:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			int ZIr;
			EXP ZIc;
			int ZIs;
			EXP ZIb;
			EXP ZIe;

			ZIp = ZI1185;
			ZIr = ZI1186;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 343 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 4017 "syntax3.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1925 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 4027 "syntax3.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 1123 "syntax.act"

    (ZIs) = unreached_code ;
    if ( (ZIs) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4043 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			ZRcompound_Hstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 1134 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4055 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_hash_elif */
			{
#line 1071 "syntax.act"

    (ZIe) = cont_hash_if_stmt ( (ZI1184), (ZIc), (ZIb) ) ;
#line 4063 "syntax3.c"
			}
			/* END OF ACTION: stmt_hash_elif */
			/* BEGINNING OF INLINE: 1190 */
			ZI1184 = ZIe;
			ZI1185 = ZIp;
			ZI1186 = ZIr;
			goto ZL2_1190;
			/* END OF INLINE: 1190 */
		}
		/*UNREACHED*/
	default:
		{
			ZI1187 = ZI1184;
			ZI1188 = ZI1185;
			ZI1189 = ZI1186;
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
	*ZO1187 = ZI1187;
	*ZO1188 = ZI1188;
	*ZO1189 = ZI1189;
}

void
ZRany_Hqualified_Hid(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			ADVANCE_LEXER;
			ZR1610 (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4119 "syntax3.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1609 (&ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4139 "syntax3.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1608 (&ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 4:
		{
			IDENTIFIER ZIuid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 231 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4159 "syntax3.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 509 "syntax.act"

    (ZIid) = (ZIuid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4170 "syntax3.c"
			}
			/* END OF ACTION: namespace_simple */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141:
		{
			ZRunqualified_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 7:
		{
			ZRunqualified_Htype (&ZIid);
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
	*ZOid = ZIid;
}

void
ZRabstract_Hdeclarator_Haux(TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 332:
		{
			ZRdirect_Habstract_Hdeclarator (&ZIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 10: case 11: case 33: case 78:
		{
			TYPE ZI1382;

			ZRptr_Hoperator (&ZI1382);
			ZR1384 (&ZI1382, &ZIt);
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
	*ZOt = ZIt;
}

void
parse_func(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRfunction_Hdefinition_Hbody (&ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
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
#line 4273 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 4281 "syntax3.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZRpseudo_Hdestr_Hsuffix(IDENTIFIER *ZOid, BASE_TYPE *ZObt)
{
	IDENTIFIER ZIid;
	BASE_TYPE ZIbt;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7:
		{
			ZRany_Hclass_Hname (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4308 "syntax3.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: id_none */
			{
#line 461 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 4330 "syntax3.c"
			}
			/* END OF ACTION: id_none */
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
	*ZObt = ZIbt;
}

void
ZRmember_Hcond_Hbody(void)
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
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 4376 "syntax3.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 4384 "syntax3.c"
		}
		/* END OF ACTION: type_none */
		ZRmember_Hspecification_Hopt (ZIt, ZIds);
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
ZR1319(NAMESPACE *ZIns, NAMESPACE *ZI1318, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			IDENTIFIER ZI1405;

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
#line 4437 "syntax3.c"
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
#line 4450 "syntax3.c"
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
    qual_namespace = (*ZI1318) ;
#line 4467 "syntax3.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZI1405) = check_id ( (*ZI1318), (ZItid), 0 ) ;
    last_namespace = (*ZI1318) ;
#line 4476 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
			ZR1407 (ZIns, &ZI1405, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
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

			ZRtemplate_Hopt (*ZI1318, &ZIq);
			ZRnested_Hid (*ZI1318, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 500 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI1318) ;
#line 4504 "syntax3.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 521 "syntax.act"

    (ZIid) = check_id ( (*ZI1318), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZI1318) ;
#line 4513 "syntax3.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 43:
		{
			IDENTIFIER ZIid1;
			BASE_TYPE ZIbt1;
			NAMESPACE ZIns1;
			QUALIFIER ZIi;
			int ZIb;
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;
			IDENTIFIER ZIuid;

			/* BEGINNING OF ACTION: namespace_full */
			{
#line 500 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI1318) ;
#line 4535 "syntax3.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_type */
			{
#line 526 "syntax.act"

    (ZIid1) = DEREF_id ( nspace_name ( (*ZI1318) ) ) ;
#line 4543 "syntax3.c"
			}
			/* END OF ACTION: namespace_type */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 4550 "syntax3.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZI1318;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 4560 "syntax3.c"
			}
			/* END OF ACTION: qual_get */
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
			ZRpseudo_Hdestr_Hsuffix (&ZIid2, &ZIbt2);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 4587 "syntax3.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 4595 "syntax3.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 4604 "syntax3.c"
			}
			/* END OF ACTION: namespace_id */
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
ZRtop_Hqualified_Htype(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZItid;
		NAMESPACE ZIns;

		switch (CURRENT_TERMINAL) {
		case 83:
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
#line 4655 "syntax3.c"
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
#line 4668 "syntax3.c"
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
#line 488 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 4686 "syntax3.c"
		}
		/* END OF ACTION: namespace_global */
		/* BEGINNING OF ACTION: namespace_id */
		{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 4695 "syntax3.c"
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
ZRstorage_Hclass_Hspecifier(DECL_SPEC *ZOds)
{
	DECL_SPEC ZIds;

	switch (CURRENT_TERMINAL) {
	case 94:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_auto */
			{
#line 1547 "syntax.act"
 (ZIds) = dspec_auto ; 
#line 4720 "syntax3.c"
			}
			/* END OF ACTION: dspec_auto */
		}
		break;
	case 105:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_extern */
			{
#line 1550 "syntax.act"
 (ZIds) = dspec_extern ; 
#line 4732 "syntax3.c"
			}
			/* END OF ACTION: dspec_extern */
		}
		break;
	case 138:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_mutable */
			{
#line 1551 "syntax.act"
 (ZIds) = dspec_mutable ; 
#line 4744 "syntax3.c"
			}
			/* END OF ACTION: dspec_mutable */
		}
		break;
	case 112:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_register */
			{
#line 1548 "syntax.act"
 (ZIds) = dspec_register ; 
#line 4756 "syntax3.c"
			}
			/* END OF ACTION: dspec_register */
		}
		break;
	case 117:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dspec_static */
			{
#line 1549 "syntax.act"
 (ZIds) = dspec_static ; 
#line 4768 "syntax3.c"
			}
			/* END OF ACTION: dspec_static */
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
	*ZOds = ZIds;
}

void
parse_id(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRany_Hqualified_Hid (&ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
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
#line 4812 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: id_none */
		{
#line 461 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 4822 "syntax3.c"
		}
		/* END OF ACTION: id_none */
	}
ZL0:;
	*ZOid = ZIid;
}

void
ZR1321(int *ZIop)
{
	switch (CURRENT_TERMINAL) {
	case 33: case 34: case 35: case 36:
	case 42: case 43: case 44: case 45:
	case 48: case 49: case 50: case 53:
	case 54: case 55: case 56: case 57:
	case 58: case 59: case 60: case 61:
	case 62: case 63: case 67: case 68:
	case 69: case 70: case 71: case 73:
	case 74: case 75: case 76: case 78:
	case 79: case 80: case 81: case 82:
	case 85: case 86: case 87:
		{
			/* BEGINNING OF INLINE: 453 */
			{
				switch (CURRENT_TERMINAL) {
				case 85:
					{
						ADVANCE_LEXER;
					}
					break;
				case 35:
					{
						ADVANCE_LEXER;
					}
					break;
				case 82:
					{
						ADVANCE_LEXER;
					}
					break;
				case 36:
					{
						ADVANCE_LEXER;
					}
					break;
				case 42:
					{
						ADVANCE_LEXER;
					}
					break;
				case 44:
					{
						ADVANCE_LEXER;
					}
					break;
				case 45:
					{
						ADVANCE_LEXER;
					}
					break;
				case 48:
					{
						ADVANCE_LEXER;
					}
					break;
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
				case 57:
					{
						ADVANCE_LEXER;
					}
					break;
				case 58:
					{
						ADVANCE_LEXER;
					}
					break;
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
				case 59:
					{
						ADVANCE_LEXER;
					}
					break;
				case 60:
					{
						ADVANCE_LEXER;
					}
					break;
				case 61:
					{
						ADVANCE_LEXER;
					}
					break;
				case 69:
					{
						ADVANCE_LEXER;
					}
					break;
				case 70:
					{
						ADVANCE_LEXER;
					}
					break;
				case 71:
					{
						ADVANCE_LEXER;
					}
					break;
				case 73:
					{
						ADVANCE_LEXER;
					}
					break;
				case 74:
					{
						ADVANCE_LEXER;
					}
					break;
				case 75:
					{
						ADVANCE_LEXER;
					}
					break;
				case 76:
					{
						ADVANCE_LEXER;
					}
					break;
				case 78:
					{
						ADVANCE_LEXER;
					}
					break;
				case 79:
					{
						ADVANCE_LEXER;
					}
					break;
				case 33:
					{
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
				case 55:
					{
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
					}
					break;
				case 56:
					{
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
					}
					break;
				case 62:
					{
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
				case 67:
					{
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
				case 80:
					{
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
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 453 */
		}
		break;
	case 41: case 46: case 83: case 84:
	case 116: case 152: case 170: case 330:
		{
			/* BEGINNING OF INLINE: 454 */
			{
				switch (CURRENT_TERMINAL) {
				case 170:
					{
						ADVANCE_LEXER;
					}
					break;
				case 41:
					{
						ADVANCE_LEXER;
					}
					break;
				case 83:
					{
						ADVANCE_LEXER;
					}
					break;
				case 46:
					{
						ADVANCE_LEXER;
					}
					break;
				case 84:
					{
						ADVANCE_LEXER;
					}
					break;
				case 116:
					{
						ADVANCE_LEXER;
					}
					break;
				case 152:
					{
						ADVANCE_LEXER;
					}
					break;
				case 330:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 454 */
			/* BEGINNING OF ACTION: error_overload */
			{
#line 1991 "syntax.act"

    /* Illegal overloaded operator */
    report ( crt_loc, ERR_over_oper_bad ( (*ZIop) ) ) ;
#line 5239 "syntax3.c"
			}
			/* END OF ACTION: error_overload */
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

/* END OF FILE */
