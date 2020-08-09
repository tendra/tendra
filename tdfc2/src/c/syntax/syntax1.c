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


#line 96 "syntax1.c"

/* BEGINNING OF STATIC VARIABLES */

int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
ZR889(EXP ZI887, EXP *ZO888)
{
	EXP ZI888;

ZL2_889:;
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
#line 557 "syntax.act"

    (ZIe) = make_or_exp ( (ZI887), (ZIb) ) ;
#line 139 "syntax1.c"
			}
			/* END OF ACTION: exp_or */
			/* BEGINNING OF INLINE: 889 */
			ZI887 = ZIe;
			goto ZL2_889;
			/* END OF INLINE: 889 */
		}
		UNREACHED;
	default:
		{
			ZI888 = ZI887;
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
	*ZO888 = ZI888;
}

void
ZRbase_Htype_Hspecifier(BASE_TYPE *ZObt)
{
	BASE_TYPE ZIbt;

	switch (CURRENT_TERMINAL) {
	case 185:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_bottom */
			{
#line 925 "syntax.act"
 (ZIbt) = btype_bottom ; 
#line 177 "syntax1.c"
			}
			/* END OF ACTION: btype_bottom */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_char */
			{
#line 913 "syntax.act"
 (ZIbt) = btype_char ; 
#line 189 "syntax1.c"
			}
			/* END OF ACTION: btype_char */
		}
		break;
	case 102:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_double */
			{
#line 920 "syntax.act"
 (ZIbt) = btype_double ; 
#line 201 "syntax1.c"
			}
			/* END OF ACTION: btype_double */
		}
		break;
	case 106:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_float */
			{
#line 919 "syntax.act"
 (ZIbt) = btype_float ; 
#line 213 "syntax1.c"
			}
			/* END OF ACTION: btype_float */
		}
		break;
	case 110:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_int */
			{
#line 915 "syntax.act"
 (ZIbt) = btype_int ; 
#line 225 "syntax1.c"
			}
			/* END OF ACTION: btype_int */
		}
		break;
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_long */
			{
#line 916 "syntax.act"
 (ZIbt) = btype_long ; 
#line 237 "syntax1.c"
			}
			/* END OF ACTION: btype_long */
		}
		break;
	case 286:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_ptrdiff_t */
			{
#line 923 "syntax.act"
 (ZIbt) = btype_ptrdiff_t ; 
#line 249 "syntax1.c"
			}
			/* END OF ACTION: btype_ptrdiff_t */
		}
		break;
	case 114:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_short */
			{
#line 914 "syntax.act"
 (ZIbt) = btype_short ; 
#line 261 "syntax1.c"
			}
			/* END OF ACTION: btype_short */
		}
		break;
	case 115:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_signed */
			{
#line 917 "syntax.act"
 (ZIbt) = btype_signed ; 
#line 273 "syntax1.c"
			}
			/* END OF ACTION: btype_signed */
		}
		break;
	case 299:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_size_t */
			{
#line 922 "syntax.act"
 (ZIbt) = btype_size_t ; 
#line 285 "syntax1.c"
			}
			/* END OF ACTION: btype_size_t */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_unsigned */
			{
#line 918 "syntax.act"
 (ZIbt) = btype_unsigned ; 
#line 297 "syntax1.c"
			}
			/* END OF ACTION: btype_unsigned */
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_void */
			{
#line 924 "syntax.act"
 (ZIbt) = btype_void ; 
#line 309 "syntax1.c"
			}
			/* END OF ACTION: btype_void */
		}
		break;
	case 156:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_wchar_t */
			{
#line 921 "syntax.act"
 (ZIbt) = btype_wchar_t ; 
#line 321 "syntax1.c"
			}
			/* END OF ACTION: btype_wchar_t */
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
}

void
ZRdecl_Hspecifier_Hseq(BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZIb1;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;

		ZRdecl_Hspecifier (&ZIb1, &ZIt1, &ZIcv1, &ZIds1);
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
#line 369 "syntax1.c"
		}
		/* END OF ACTION: check_decl_specifier */
		/* BEGINNING OF INLINE: 720 */
		{
			switch (CURRENT_TERMINAL) {
			case 2: case 25: case 94: case 97:
			case 98: case 102: case 104: case 105:
			case 106: case 110: case 111: case 112:
			case 114: case 115: case 117: case 118:
			case 120: case 121: case 122: case 123:
			case 124: case 137: case 156: case 185:
			case 286: case 299:
				{
					BASE_TYPE ZIb2;
					TYPE ZIt2;
					CV_SPEC ZIcv2;
					DECL_SPEC ZIds2;

					ZRdecl_Hspecifier_Hseq (&ZIb2, &ZIt2, &ZIcv2, &ZIds2);
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
#line 402 "syntax1.c"
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
#line 418 "syntax1.c"
					}
					/* END OF ACTION: type_join */
					/* BEGINNING OF ACTION: cv_join */
					{
#line 900 "syntax.act"

    CV_SPEC c = ( (ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIcv1) | (ZIcv2) ) ;
#line 428 "syntax1.c"
					}
					/* END OF ACTION: cv_join */
					/* BEGINNING OF ACTION: dspec_join */
					{
#line 1124 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (ZIds1) | (ZIds2) ) ;
#line 439 "syntax1.c"
					}
					/* END OF ACTION: dspec_join */
				}
				break;
			default:
				{
					ZIbt = ZIb1;
					ZIt = ZIt1;
					ZIcv = ZIcv1;
					ZIds = ZIds1;
				}
				break;
			}
		}
		/* END OF INLINE: 720 */
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
ZR893(EXP ZI891, EXP *ZO892)
{
	EXP ZI892;

ZL2_893:;
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
#line 623 "syntax.act"

    (ZIe) = make_xor_exp ( (ZI891), (ZIb) ) ;
#line 502 "syntax1.c"
			}
			/* END OF ACTION: exp_xor */
			/* BEGINNING OF INLINE: 893 */
			ZI891 = ZIe;
			goto ZL2_893;
			/* END OF INLINE: 893 */
		}
		UNREACHED;
	default:
		{
			ZI892 = ZI891;
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
	*ZO892 = ZI892;
}

void
ZRdeclarator_Htail(IDENTIFIER ZIid, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 546 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			/* BEGINNING OF INLINE: 749 */
			{
				switch (CURRENT_TERMINAL) {
				case 2: case 25: case 47: case 94:
				case 97: case 98: case 102: case 104:
				case 105: case 106: case 110: case 111:
				case 112: case 114: case 115: case 117:
				case 118: case 120: case 121: case 122:
				case 123: case 124: case 137: case 156:
				case 185: case 286: case 299:
					{
						int ZIell;

						ZRparameter_Hdeclaration_Hlist (&ZIell);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: type_func */
						{
#line 1014 "syntax.act"

    (ZIs) = make_func_type ( NULL_type, (ZIell), cv_c, empty_type_set ) ;
#line 572 "syntax1.c"
						}
						/* END OF ACTION: type_func */
						switch (CURRENT_TERMINAL) {
						case 39:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
					}
					break;
				case 1: case 4:
					{
						ZRparameter_Hid_Hlist ();
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: type_func_old */
						{
#line 1022 "syntax.act"

    (ZIs) = make_func_type ( NULL_type, FUNC_PARAMS, cv_c, empty_type_set ) ;
#line 596 "syntax1.c"
						}
						/* END OF ACTION: type_func_old */
						switch (CURRENT_TERMINAL) {
						case 39:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
					}
					break;
				case 39:
					{
						/* BEGINNING OF ACTION: type_func_none */
						{
#line 1026 "syntax.act"

    (ZIs) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
#line 615 "syntax1.c"
						}
						/* END OF ACTION: type_func_none */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 749 */
			ZIt = ZIs;
			/* BEGINNING OF ACTION: param_end */
			{
#line 883 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 634 "syntax1.c"
			}
			/* END OF ACTION: param_end */
		}
		break;
	case 333:
		{
			int ZIell;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 659 "syntax1.c"
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

    (ZIt) = make_func_type ( NULL_type, ( (ZIell) | FUNC_WEAK ), cv_c, empty_type_set ) ;
#line 672 "syntax1.c"
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
#line 689 "syntax1.c"
			}
			/* END OF ACTION: param_end */
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
			ZR760 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1030 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 722 "syntax1.c"
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
ZRparameter_Hdeclaration(IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv;
		DECL_SPEC ZIds1;
		TYPE ZIt2;
		DECL_SPEC ZIds;
		TYPE ZIt;
		IDENTIFIER ZIid;

		ZRdecl_Hspecifier_Hseq (&ZIbt, &ZIt1, &ZIcv, &ZIds1);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1135 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv), 0 ) ;
    have_type_specifier = 0 ;
#line 784 "syntax1.c"
		}
		/* END OF ACTION: dspec_complete */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_param */
		{
#line 1184 "syntax.act"

    (ZId) = make_param_decl ( (ZIds), (ZIt), (ZIid), CONTEXT_PARAMETER ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 799 "syntax1.c"
		}
		/* END OF ACTION: declare_param */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOd = ZId;
}

void
ZR897(EXP ZI895, EXP *ZO896)
{
	EXP ZI896;

ZL2_897:;
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
#line 441 "syntax.act"

    (ZIe) = make_and_exp ( (ZI895), (ZIb) ) ;
#line 846 "syntax1.c"
			}
			/* END OF ACTION: exp_and */
			/* BEGINNING OF INLINE: 897 */
			ZI895 = ZIe;
			goto ZL2_897;
			/* END OF INLINE: 897 */
		}
		UNREACHED;
	default:
		{
			ZI896 = ZI895;
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
	*ZO896 = ZI896;
}

void
ZRtarget_Hcondition(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;
		EXP ZIp;
		int ZIr;
		EXP ZIb;

		ZRtarget_Hcondition_Hhead (&ZIa, &ZIp, &ZIr);
		/* BEGINNING OF INLINE: 573 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					int ZIs;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: cond_hash_else */
					{
#line 1319 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 899 "syntax1.c"
					}
					/* END OF ACTION: cond_hash_else */
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
#line 915 "syntax1.c"
					}
					/* END OF ACTION: reach_check */
					ZRcompound_Hstatement (&ZIb);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: stmt_none */
					{
#line 637 "syntax.act"

    (ZIb) = NULL_exp ;
#line 932 "syntax1.c"
					}
					/* END OF ACTION: stmt_none */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 573 */
		/* BEGINNING OF ACTION: cond_hash_endif */
		{
#line 1322 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 948 "syntax1.c"
		}
		/* END OF ACTION: cond_hash_endif */
		switch (CURRENT_TERMINAL) {
		case 29:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 840 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 962 "syntax1.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_endif */
		{
#line 806 "syntax.act"

    (ZIe) = end_hash_if_stmt ( (ZIa), (ZIb) ) ;
#line 970 "syntax1.c"
		}
		/* END OF ACTION: stmt_hash_endif */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRclass_Hspecifier(TYPE *ZOt)
{
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZIkey;

		ZRclass_Hkey (&ZIkey);
		/* BEGINNING OF INLINE: 674 */
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
#line 1011 "syntax1.c"
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
#line 1024 "syntax1.c"
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
#line 1037 "syntax1.c"
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
					ZR1029 (&ZIkey, &ZIid, &ZIt);
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
					int ZIf;
					IDENTIFIER ZItid;

					/* BEGINNING OF ACTION: id_anon */
					{
#line 388 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
#line 1068 "syntax1.c"
					}
					/* END OF ACTION: id_anon */
					/* BEGINNING OF ACTION: type_class_begin */
					{
#line 1076 "syntax.act"

    (ZIp) = begin_class_defn ( (ZIid), (ZIkey), cinfo_none, NULL_type ) ;
    (ZIf) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
    end_base_class ( crt_class, 1 ) ;
#line 1082 "syntax1.c"
					}
					/* END OF ACTION: type_class_begin */
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
					ZRmember_Hspecification_Hopt ();
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
					/* BEGINNING OF ACTION: type_class_end */
					{
#line 1086 "syntax.act"

    (ZItid) = end_class_defn ( (ZIp) ) ;
    in_function_defn = (ZIf) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
#line 1124 "syntax1.c"
					}
					/* END OF ACTION: type_class_end */
					/* BEGINNING OF ACTION: type_name */
					{
#line 959 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZItid) ) ;
    have_type_specifier = 1 ;
#line 1134 "syntax1.c"
					}
					/* END OF ACTION: type_name */
					/* BEGINNING OF ACTION: rescan_token */
					{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 1142 "syntax1.c"
					}
					/* END OF ACTION: rescan_token */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 674 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZR1026(EXP *ZI1024, EXP *ZOe)
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
#line 417 "syntax.act"

    CONS_exp ( (*ZI1024), (ZIq), (ZIp) ) ;
#line 1186 "syntax1.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 467 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 1194 "syntax1.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	default:
		{
			ZIe = *ZI1024;
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
ZRfield_Hid_Hexpression(NAMESPACE ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER ZIuid;

		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 1236 "syntax1.c"
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

    ZIuid = crt_token->pp_data.id.use ;
#line 1249 "syntax1.c"
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

    ZIuid = crt_token->pp_data.id.use ;
#line 1262 "syntax1.c"
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
		/* BEGINNING OF ACTION: rescan_member */
		{
#line 400 "syntax.act"

    HASHID nm = DEREF_hashid ( id_name ( (ZIuid) ) ) ;
    (ZIid) = find_qual_id ( (ZIns), nm, 1, 0 ) ;
#line 1279 "syntax1.c"
		}
		/* END OF ACTION: rescan_member */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOid = ZIid;
}

void
ZRdecl_Hspecifier(BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	switch (CURRENT_TERMINAL) {
	case 98: case 124:
		{
			ZRcv_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1311 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZIt) = NULL_type ;
#line 1319 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1114 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1326 "syntax1.c"
			}
			/* END OF ACTION: dspec_none */
		}
		break;
	case 94: case 105: case 112: case 117:
	case 120: case 137:
		{
			ZRstorage_Hclass_Hspecifier (&ZIds);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: dspec_check */
			{
#line 1130 "syntax.act"

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZIds) ) ) ;
#line 1344 "syntax1.c"
			}
			/* END OF ACTION: dspec_check */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1351 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZIt) = NULL_type ;
#line 1359 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 895 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1366 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 2: case 25: case 97: case 102:
	case 104: case 106: case 110: case 111:
	case 114: case 115: case 118: case 121:
	case 122: case 123: case 156: case 185:
	case 286: case 299:
		{
			ZRtype_Hspecifier (&ZIbt, &ZIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_none */
			{
#line 895 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1386 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1114 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1393 "syntax1.c"
			}
			/* END OF ACTION: dspec_none */
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
	*ZOds = ZIds;
}

void
parse_init(IDENTIFIER ZId, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		ZRinitialiser_Hclause (ZId, &ZIe);
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
#line 1440 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1448 "syntax1.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZR1027(EXP *ZIa, SID_LIST_EXP *ZOp)
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
#line 417 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1477 "syntax1.c"
			}
			/* END OF ACTION: list_exp_cons */
		}
		break;
	default:
		{
			SID_LIST_EXP ZIq;

			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 413 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 1491 "syntax1.c"
			}
			/* END OF ACTION: list_exp_null */
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 417 "syntax.act"

    CONS_exp ( (*ZIa), (ZIq), (ZIp) ) ;
#line 1499 "syntax1.c"
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
ZRdeclaration_Hseq_Hopt(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_declaration_Hseq_Hopt:;
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
#line 1539 "syntax1.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL3;
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
#line 1557 "syntax1.c"
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
#line 1571 "syntax1.c"
		}
		/* END OF ACTION: declare_extern */
		/* BEGINNING OF INLINE: declaration-seq-opt */
		goto ZL2_declaration_Hseq_Hopt;
		/* END OF INLINE: declaration-seq-opt */
	}
	UNREACHED;
ZL3:;
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declare_empty */
			{
#line 1181 "syntax.act"

    report ( crt_loc, ERR_dcl_dcl_semicolon () ) ;
#line 1589 "syntax1.c"
			}
			/* END OF ACTION: declare_empty */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		UNREACHED;
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
#line 1611 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		UNREACHED;
	case 26: case 30:
		{
			ZRdeclaration_Hcond ();
			/* BEGINNING OF INLINE: declaration-seq-opt */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_declaration_Hseq_Hopt;
			}
			/* END OF INLINE: declaration-seq-opt */
		}
		UNREACHED;
	case 1: case 2: case 4: case 65:
	case 78:
		{
			BASE_TYPE ZIbt;
			TYPE ZIt1;
			CV_SPEC ZIcv;
			DECL_SPEC ZIds1;
			TYPE ZIt;
			DECL_SPEC ZIds;
			TYPE ZIs;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 926 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1649 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZIt1) = NULL_type ;
#line 1657 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 895 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1664 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1114 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 1671 "syntax1.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1135 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv) ) ;
    (ZIt) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv), 0 ) ;
    have_type_specifier = 0 ;
#line 1682 "syntax1.c"
			}
			/* END OF ACTION: dspec_complete */
			ZRdeclarator (ZIt, &ZIs, &ZIid);
			ZR822 (&ZIbt, &ZIt, &ZIds, &ZIs, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1696 "syntax1.c"
			}
			/* END OF ACTION: exp_none */
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1236 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 1704 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
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
ZR1028(EXP *ZOe)
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
#line 607 "syntax.act"

    (ZIe) = make_set_exp ( (ZIa) ) ;
#line 1742 "syntax1.c"
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
#line 619 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 1769 "syntax1.c"
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
ZR901(EXP ZI899, EXP *ZO900)
{
	EXP ZI900;

ZL2_901:;
	switch (CURRENT_TERMINAL) {
	case 86: case 87:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 366 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 1811 "syntax1.c"
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
#line 541 "syntax.act"

    (ZIe) = make_mult_exp ( (ZIop), (ZI899), (ZIb) ) ;
#line 1842 "syntax1.c"
			}
			/* END OF ACTION: exp_maxmin */
			/* BEGINNING OF INLINE: 901 */
			ZI899 = ZIe;
			goto ZL2_901;
			/* END OF INLINE: 901 */
		}
		UNREACHED;
	default:
		{
			ZI900 = ZI899;
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
	*ZO900 = ZI900;
}

void
ZRabstract_Hdeclarator_Htail(TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			IDENTIFIER ZIid;
			TYPE ZIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 383 "syntax.act"

    (ZIid) = NULL_id ;
#line 1884 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1895 "syntax1.c"
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
#line 1917 "syntax1.c"
			}
			/* END OF ACTION: param_end */
		}
		break;
	case 333:
		{
			IDENTIFIER ZIid;
			int ZIell;

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

    (ZIid) = NULL_id ;
#line 1940 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 874 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1951 "syntax1.c"
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

    (ZIt) = make_func_type ( NULL_type, ( (ZIell) | FUNC_WEAK ), cv_c, empty_type_set ) ;
#line 1964 "syntax1.c"
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
#line 1981 "syntax1.c"
			}
			/* END OF ACTION: param_end */
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
			ZR760 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1030 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 2014 "syntax1.c"
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
ZR1029(BASE_TYPE *ZIkey, IDENTIFIER *ZIid, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 64:
		{
			IDENTIFIER ZIp;
			int ZIf;
			IDENTIFIER ZItid;

			/* BEGINNING OF ACTION: type_class_begin */
			{
#line 1076 "syntax.act"

    (ZIp) = begin_class_defn ( (*ZIid), (*ZIkey), cinfo_none, NULL_type ) ;
    (ZIf) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
    end_base_class ( crt_class, 1 ) ;
#line 2068 "syntax1.c"
			}
			/* END OF ACTION: type_class_begin */
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
			ZRmember_Hspecification_Hopt ();
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
			/* BEGINNING OF ACTION: type_class_end */
			{
#line 1086 "syntax.act"

    (ZItid) = end_class_defn ( (ZIp) ) ;
    in_function_defn = (ZIf) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
#line 2110 "syntax1.c"
			}
			/* END OF ACTION: type_class_end */
			/* BEGINNING OF ACTION: type_name */
			{
#line 959 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZItid) ) ;
    have_type_specifier = 1 ;
#line 2120 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 2128 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_elaborate */
			{
#line 965 "syntax.act"

    MAKE_type_pre ( cv_none, (*ZIkey), qual_none, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (*ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
#line 2145 "syntax1.c"
			}
			/* END OF ACTION: type_elaborate */
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
ZRscoped_Hstatement(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIa;

		ZRscoped_Hstmt_Hbody (ZIc, &ZIa);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 670 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2182 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 2190 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
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
#line 2205 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 670 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIc) ) ;
#line 2213 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 2221 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZR1030(BASE_TYPE *ZIbt, TYPE *ZIp, CV_SPEC *ZIcv)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1203 "syntax.act"

    IGNORE empty_decl ( dspec_none, NULL_type, (*ZIbt), (*ZIp), (*ZIcv), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 2243 "syntax1.c"
			}
			/* END OF ACTION: declare_member_empty */
			ADVANCE_LEXER;
		}
		break;
	case 1: case 2: case 4: case 41:
	case 65: case 78:
		{
			TYPE ZIt;

			/* BEGINNING OF ACTION: type_complete */
			{
#line 986 "syntax.act"

    (ZIt) = complete_pre_type ( (*ZIbt), (*ZIp), (*ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2260 "syntax1.c"
			}
			/* END OF ACTION: type_complete */
			ZRmember_Hdeclarator (ZIt, *ZIbt);
			/* BEGINNING OF INLINE: 831 */
			{
				switch (CURRENT_TERMINAL) {
				case 42:
					{
						ADVANCE_LEXER;
						ZRmember_Hdeclarator_Hlist (ZIt, *ZIbt);
						switch (CURRENT_TERMINAL) {
						case 77:
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
				case 77:
					{
						ADVANCE_LEXER;
					}
					break;
				case 356:
					RESTORE_LEXER;
					goto ZL1;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 831 */
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
ZRinit_Hdeclarator(DECL_SPEC ZIds, BASE_TYPE ZIbt, TYPE ZIp)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIt;
		IDENTIFIER ZIid;
		IDENTIFIER ZId;
		EXP ZIe;

		ZRdeclarator (ZIp, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_id */
		{
#line 1149 "syntax.act"

    if ( in_weak_param ) {
	(ZId) = make_param_decl ( (ZIds), (ZIt), (ZIid), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (ZIt) ) == type_func_tag ) {
	check_weak_func ( (ZIt), 0 ) ;
	(ZId) = make_func_decl ( (ZIds), (ZIt), (ZIid), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZId) = make_object_decl ( (ZIds), (ZIt), (ZIid), def ) ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (ZIbt) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2346 "syntax1.c"
		}
		/* END OF ACTION: declare_id */
		ZRinitialiser_Hopt (ZId, &ZIe);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1254 "syntax.act"

    int def = init_object ( (ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 2360 "syntax1.c"
		}
		/* END OF ACTION: initialise_id */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRdeclaration(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		BASE_TYPE ZIb1;
		TYPE ZI1098;
		CV_SPEC ZIcv1;
		DECL_SPEC ZI1099;
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv;
		DECL_SPEC ZIds1;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 1421 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2392 "syntax1.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL1;
		ZRdecl_Hspecifier (&ZIb1, &ZI1098, &ZIcv1, &ZI1099);
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
#line 2410 "syntax1.c"
		}
		/* END OF ACTION: check_decl_specifier */
		ZR727 (&ZIb1, &ZI1098, &ZIcv1, &ZI1099, &ZIbt, &ZIt1, &ZIcv, &ZIds1);
		ZR816 (&ZIbt, &ZIt1, &ZIcv, &ZIds1);
		switch (CURRENT_TERMINAL) {
		case 77:
			break;
		case 356:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR905(EXP ZI903, EXP *ZO904)
{
	EXP ZI904;

ZL2_905:;
	switch (CURRENT_TERMINAL) {
	case 48: case 63:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 366 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 2449 "syntax1.c"
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
#line 492 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_equality_exp ( (ZIop), (ZI903), (ZIb) ) ;
#line 2464 "syntax1.c"
			}
			/* END OF ACTION: exp_equality */
			/* BEGINNING OF INLINE: 905 */
			ZI903 = ZIe;
			goto ZL2_905;
			/* END OF INLINE: 905 */
		}
		UNREACHED;
	default:
		{
			ZI904 = ZI903;
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
	*ZO904 = ZI904;
}

void
ZRprimary_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 23:
		{
			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 332 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIe = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2505 "syntax1.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
		}
		break;
	case 210:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 487 "syntax.act"

    (ZIe) = make_ellipsis_exp () ;
#line 2519 "syntax1.c"
			}
			/* END OF ACTION: exp_ellipsis */
		}
		break;
	case 1:
		{
			IDENTIFIER ZIid;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 2533 "syntax1.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 505 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 2542 "syntax1.c"
			}
			/* END OF ACTION: exp_identifier */
		}
		break;
	case 65:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 562 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 2557 "syntax1.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 565 "syntax.act"

    (ZIe) = make_paren_exp ( (ZIa) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 2571 "syntax1.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 17: case 18: case 19: case 20:
	case 21: case 22:
		{
			ZRliteral (&ZIe);
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
#line 841 "syntax.act"
 unreached_code = 0 ; 
#line 2621 "syntax1.c"
			}
			/* END OF ACTION: reach_set */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_reach */
			{
#line 810 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 1 ) ;
#line 2634 "syntax1.c"
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
#line 842 "syntax.act"
 unreached_code = 1 ; 
#line 2648 "syntax1.c"
			}
			/* END OF ACTION: reach_unset */
			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_unreach */
			{
#line 814 "syntax.act"

    (ZIe) = make_reach_stmt ( (ZIa), 0 ) ;
#line 2661 "syntax1.c"
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
ZRclass_Hkey(BASE_TYPE *ZOkey)
{
	BASE_TYPE ZIkey;

	switch (CURRENT_TERMINAL) {
	case 118:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_struct */
			{
#line 1062 "syntax.act"
 (ZIkey) = btype_struct ; 
#line 2692 "syntax1.c"
			}
			/* END OF ACTION: key_struct */
		}
		break;
	case 121:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: key_union */
			{
#line 1063 "syntax.act"
 (ZIkey) = btype_union ; 
#line 2704 "syntax1.c"
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
#line 525 "syntax.act"

    MAKE_exp_location ( type_void, crt_loc, (ZIb), (ZIa) ) ;
#line 2745 "syntax1.c"
		}
		/* END OF ACTION: exp_location */
		/* BEGINNING OF INLINE: 793 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					ZR1075 (&ZId, &ZIq);
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
#line 413 "syntax.act"

    (ZIq) = NULL_list ( EXP ) ;
#line 2768 "syntax1.c"
					}
					/* END OF ACTION: list_exp_null */
				}
				break;
			}
		}
		/* END OF INLINE: 793 */
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 417 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 2781 "syntax1.c"
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
ZR909(EXP ZI907, EXP *ZO908)
{
	EXP ZI908;

ZL2_909:;
	switch (CURRENT_TERMINAL) {
	case 49: case 50: case 53: case 54:
		{
			int ZIop;
			EXP ZIb;
			EXP ZIe;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 366 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 2810 "syntax1.c"
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
#line 595 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_relation_exp ( (ZIop), (ZI907), (ZIb) ) ;
#line 2852 "syntax1.c"
			}
			/* END OF ACTION: exp_relation */
			/* BEGINNING OF INLINE: 909 */
			ZI907 = ZIe;
			goto ZL2_909;
			/* END OF INLINE: 909 */
		}
		UNREACHED;
	default:
		{
			ZI908 = ZI907;
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
	*ZO908 = ZI908;
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
#line 986 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2902 "syntax1.c"
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
ZRmaxmin_Hexpression(EXP *ZO900)
{
	EXP ZI900;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRequality_Hexpression (&ZIe);
		ZR901 (ZIe, &ZI900);
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
	*ZO900 = ZI900;
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
		ZR1028 (&ZIe);
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
ZR913(EXP ZI911, EXP *ZO912)
{
	EXP ZI912;

ZL2_913:;
	switch (CURRENT_TERMINAL) {
	case 57:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRadditive_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lshift */
			{
#line 537 "syntax.act"

    (ZIe) = make_shift_exp ( lex_lshift, (ZI911), (ZIb) ) ;
#line 3035 "syntax1.c"
			}
			/* END OF ACTION: exp_lshift */
			/* BEGINNING OF INLINE: 913 */
			ZI911 = ZIe;
			goto ZL2_913;
			/* END OF INLINE: 913 */
		}
		UNREACHED;
	case 75:
		{
			EXP ZIb;
			EXP ZIe;

			ADVANCE_LEXER;
			ZRadditive_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_rshift */
			{
#line 603 "syntax.act"

    (ZIe) = make_shift_exp ( lex_rshift, (ZI911), (ZIb) ) ;
#line 3060 "syntax1.c"
			}
			/* END OF ACTION: exp_rshift */
			/* BEGINNING OF INLINE: 913 */
			ZI911 = ZIe;
			goto ZL2_913;
			/* END OF INLINE: 913 */
		}
		UNREACHED;
	default:
		{
			ZI912 = ZI911;
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
	*ZO912 = ZI912;
}

void
parse_type_param(IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 3102 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: decl_none */
		{
#line 1240 "syntax.act"

    (ZId) = NULL_id ;
#line 3110 "syntax1.c"
		}
		/* END OF ACTION: decl_none */
	}
	*ZOd = ZId;
}

void
ZRpostfix_Hexpression(EXP *ZO924)
{
	EXP ZI924;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRprimary_Hexpression (&ZIe);
		ZR925 (ZIe, &ZI924);
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
	*ZO924 = ZI924;
}

void
ZRsimple_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZI1009;
			EXP ZI1010;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 369 "syntax.act"
 (ZI1009) = lex_alignof ; 
#line 3162 "syntax1.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZI1009, &ZI1010);
			ZR1014 (&ZI1010, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3185 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3193 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3201 "syntax1.c"
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
	case 23:
		{
			EXP ZI1021;
			EXP ZI1022;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 332 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1021 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3229 "syntax1.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR925 (ZI1021, &ZI1022);
			ZR1014 (&ZI1022, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3253 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3261 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3269 "syntax1.c"
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
#line 339 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIa = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3293 "syntax1.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3302 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 206:
		{
			EXP ZI1084;
			EXP ZI964;
			EXP ZI963;
			EXP ZI962;
			EXP ZI961;
			EXP ZI960;
			EXP ZI959;
			EXP ZI958;
			EXP ZI957;
			EXP ZI956;
			EXP ZI955;
			EXP ZI954;
			EXP ZI951;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1084);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 509 "syntax.act"

    (ZI964) = make_cast_exp ( type_void, (ZI1084), 0 ) ;
#line 3337 "syntax1.c"
			}
			/* END OF ACTION: exp_ignore */
			ZR921 (ZI964, &ZI963);
			ZR917 (ZI963, &ZI962);
			ZR913 (ZI962, &ZI961);
			ZR909 (ZI961, &ZI960);
			ZR905 (ZI960, &ZI959);
			ZR901 (ZI959, &ZI958);
			ZR897 (ZI958, &ZI957);
			ZR893 (ZI957, &ZI956);
			ZR889 (ZI956, &ZI955);
			ZR885 (ZI955, &ZI954);
			ZR881 (ZI954, &ZI951);
			ZR953 (&ZI951, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3370 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3378 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3386 "syntax1.c"
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
			EXP ZI1018;
			EXP ZI1019;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 487 "syntax.act"

    (ZI1018) = make_ellipsis_exp () ;
#line 3412 "syntax1.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR925 (ZI1018, &ZI1019);
			ZR1014 (&ZI1019, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3435 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3443 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3451 "syntax1.c"
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
	case 1:
		{
			IDENTIFIER ZIid;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3472 "syntax1.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1085 (&ZIid, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 347:
		{
			ADVANCE_LEXER;
			ZR1081 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 255:
		{
			EXP ZI1083;
			EXP ZI964;
			EXP ZI963;
			EXP ZI962;
			EXP ZI961;
			EXP ZI960;
			EXP ZI959;
			EXP ZI958;
			EXP ZI957;
			EXP ZI956;
			EXP ZI955;
			EXP ZI954;
			EXP ZI951;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1083);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 521 "syntax.act"

    (ZI964) = make_lit_exp ( (ZI1083) ) ;
#line 3523 "syntax1.c"
			}
			/* END OF ACTION: exp_lit */
			ZR921 (ZI964, &ZI963);
			ZR917 (ZI963, &ZI962);
			ZR913 (ZI962, &ZI961);
			ZR909 (ZI961, &ZI960);
			ZR905 (ZI960, &ZI959);
			ZR901 (ZI959, &ZI958);
			ZR897 (ZI958, &ZI957);
			ZR893 (ZI957, &ZI956);
			ZR889 (ZI956, &ZI955);
			ZR885 (ZI955, &ZI954);
			ZR881 (ZI954, &ZI951);
			ZR953 (&ZI951, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3556 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3564 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3572 "syntax1.c"
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
			EXP ZI990;
			EXP ZI991;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZI990);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 582 "syntax.act"

    (ZI991) = make_prefix_exp ( lex_minus_Hminus, (ZI990) ) ;
#line 3603 "syntax1.c"
			}
			/* END OF ACTION: exp_predec */
			ZR1014 (&ZI991, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3625 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3633 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3641 "syntax1.c"
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
	case 65:
		{
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZR986 (&ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3679 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3687 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3695 "syntax1.c"
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
			EXP ZI987;
			EXP ZI988;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZI987);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 586 "syntax.act"

    (ZI988) = make_prefix_exp ( lex_plus_Hplus, (ZI987) ) ;
#line 3726 "syntax1.c"
			}
			/* END OF ACTION: exp_preinc */
			ZR1014 (&ZI988, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3748 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3756 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3764 "syntax1.c"
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
#line 637 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3784 "syntax1.c"
			}
			/* END OF ACTION: stmt_none */
		}
		break;
	case 116:
		{
			int ZI1006;
			EXP ZI1007;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 370 "syntax.act"
 (ZI1006) = lex_sizeof ; 
#line 3802 "syntax1.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZI1006, &ZI1007);
			ZR1014 (&ZI1007, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3825 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3833 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3841 "syntax1.c"
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
			EXP ZI993;
			EXP ZI994;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI993);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 517 "syntax.act"

    (ZI994) = make_indir_exp ( (ZI993) ) ;
#line 3872 "syntax1.c"
			}
			/* END OF ACTION: exp_indir */
			ZR1014 (&ZI994, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3894 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3902 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 3910 "syntax1.c"
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
			IDENTIFIER ZIid;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 208 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3931 "syntax1.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1086 (&ZIid, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2:
		{
			IDENTIFIER ZIid;
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 200 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3953 "syntax1.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 771 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 3962 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 754 "syntax.act"

    (ZIa) = begin_label_stmt ( (ZIid), lex_identifier ) ;
#line 3970 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_begin */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 758 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 3990 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_end */
		}
		break;
	case 33:
		{
			EXP ZI996;
			EXP ZI997;
			EXP ZI1024;
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
			ZRcast_Hexpression (&ZI996);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 590 "syntax.act"

    (ZI997) = make_ref_exp ( (ZI996), 0 ) ;
#line 4026 "syntax1.c"
			}
			/* END OF ACTION: exp_ref */
			ZR1014 (&ZI997, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4048 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4056 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 4064 "syntax1.c"
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
	case 126:
		{
			ZRasm_Hdefinition (&ZIe);
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
			ZR1082 (&ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 298: case 324:
		{
			EXP ZI1076;
			EXP ZIa;
			int ZIr;

			ZRflow_Hexpression (&ZI1076);
			ZR1078 (&ZI1076, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4129 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4137 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 4145 "syntax1.c"
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
	case 21: case 22:
		{
			EXP ZI1012;
			EXP ZI1013;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			ZRliteral (&ZI1012);
			ZR925 (ZI1012, &ZI1013);
			ZR1014 (&ZI1013, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4205 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4213 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 4221 "syntax1.c"
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
			EXP ZI999;
			EXP ZI1000;
			EXP ZI1024;
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
			ZRcast_Hexpression (&ZI999);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 553 "syntax.act"

    (ZI1000) = make_not_exp ( (ZI999) ) ;
#line 4264 "syntax1.c"
			}
			/* END OF ACTION: exp_not */
			ZR1014 (&ZI1000, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4286 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4294 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 4302 "syntax1.c"
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
	case 43: case 59: case 69: case 85:
		{
			int ZI1002;
			EXP ZI1003;
			EXP ZI1004;
			EXP ZI1024;
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 366 "syntax.act"
 (ZI1002) = crt_lex_token ; 
#line 4336 "syntax1.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZI1003);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 615 "syntax.act"

    (ZI1004) = make_uminus_exp ( (ZI1002), (ZI1003) ) ;
#line 4350 "syntax1.c"
			}
			/* END OF ACTION: exp_unary */
			ZR1014 (&ZI1004, &ZI1024);
			ZR1026 (&ZI1024, &ZIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 829 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4372 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 699 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4380 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 767 "syntax.act"

    unreached_fall = 1 ;
#line 4388 "syntax1.c"
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
ZRmember_Hspecification_Hopt(void)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_member_Hspecification_Hopt:;
	{
		BASE_TYPE ZIb1;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		BASE_TYPE ZIbt;
		TYPE ZIp;
		CV_SPEC ZIcv;

		/* BEGINNING OF ACTION: is_type_specifier */
		{
#line 1446 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 4434 "syntax1.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL3;
		ZRtype_Hqualifier (&ZIb1, &ZIt1, &ZIcv1);
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
#line 4452 "syntax1.c"
		}
		/* END OF ACTION: check_decl_specifier */
		ZR702 (&ZIb1, &ZIt1, &ZIcv1, &ZIbt, &ZIp, &ZIcv);
		ZR1030 (&ZIbt, &ZIp, &ZIcv);
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
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR1042(TYPE *ZIp, BASE_TYPE *ZIq, IDENTIFIER *ZI1041)
{
	switch (CURRENT_TERMINAL) {
	case 41:
		{
			EXP ZIc;
			TYPE ZIt;

			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (*ZI1041) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 4489 "syntax1.c"
			}
			/* END OF ACTION: declarator_begin */
			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_bitfield_mem */
			{
#line 1040 "syntax.act"

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1041) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZIt) = make_bitfield_type ( (*ZIp), (*ZIq), (ZIc), z ) ;
#line 4506 "syntax1.c"
			}
			/* END OF ACTION: type_bitfield_mem */
			/* BEGINNING OF ACTION: declare_bitfield */
			{
#line 1210 "syntax.act"

    IDENTIFIER id = make_member_decl ( dspec_none, (ZIt), (*ZI1041), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4517 "syntax1.c"
			}
			/* END OF ACTION: declare_bitfield */
		}
		break;
	default:
		{
			TYPE ZI1040;
			TYPE ZI1034;
			IDENTIFIER ZIid;
			TYPE ZIt;

			/* BEGINNING OF ACTION: type_none */
			{
#line 950 "syntax.act"

    (ZI1040) = NULL_type ;
#line 4534 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1221 "syntax.act"

    IDENTIFIER pid = underlying_id ( (*ZI1041) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 4543 "syntax1.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR871 (ZI1040, *ZI1041, &ZI1034, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1046 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1034) ) ? (*ZIp) : inject_pre_type ( (ZI1034), (*ZIp), 1 ) ) ;
#line 4556 "syntax1.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1196 "syntax.act"

    IDENTIFIER id = make_member_decl ( dspec_none, (ZIt), (ZIid), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4567 "syntax1.c"
			}
			/* END OF ACTION: declare_member */
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
#line 1389 "syntax.act"

    suppress_usage++ ;
#line 4599 "syntax1.c"
		}
		/* END OF ACTION: sizeof_begin */
		/* BEGINNING OF ACTION: no_side_effects */
		{
#line 1372 "syntax.act"

    (ZIn1) = no_side_effects ;
#line 4607 "syntax1.c"
		}
		/* END OF ACTION: no_side_effects */
		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 1376 "syntax.act"

    (ZIm1) = no_type_defns ;
#line 4615 "syntax1.c"
		}
		/* END OF ACTION: no_type_defns */
		/* BEGINNING OF INLINE: 466 */
		{
			switch (CURRENT_TERMINAL) {
			case 170:
				{
					int ZI1068;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_alignof */
					{
#line 369 "syntax.act"
 (ZI1068) = lex_alignof ; 
#line 4634 "syntax1.c"
					}
					/* END OF ACTION: lex_alignof */
					ZRsizeof_Hexpression (ZI1068, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4647 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4655 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4663 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4671 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 23:
				{
					EXP ZI1104;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: complex-exp */
					{
#line 332 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1104 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 4692 "syntax1.c"
					}
					/* END OF EXTRACT: complex-exp */
					ADVANCE_LEXER;
					ZR925 (ZI1104, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4706 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4714 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4722 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4730 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 210:
				{
					EXP ZI1105;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_ellipsis */
					{
#line 487 "syntax.act"

    (ZI1105) = make_ellipsis_exp () ;
#line 4749 "syntax1.c"
					}
					/* END OF ACTION: exp_ellipsis */
					ZR925 (ZI1105, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4762 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4770 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4778 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4786 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 1:
				{
					IDENTIFIER ZIid;
					EXP ZI1106;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF EXTRACT: identifier */
					{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 4805 "syntax1.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: exp_identifier */
					{
#line 505 "syntax.act"

    (ZI1106) = make_id_exp ( (ZIid) ) ;
#line 4814 "syntax1.c"
					}
					/* END OF ACTION: exp_identifier */
					ZR925 (ZI1106, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4827 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4835 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4843 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4851 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 61:
				{
					EXP ZI1061;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRunary_Hexpression (&ZI1061);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_predec */
					{
#line 582 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_minus_Hminus, (ZI1061) ) ;
#line 4875 "syntax1.c"
					}
					/* END OF ACTION: exp_predec */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4883 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4891 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4899 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4907 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 65:
				{
					ADVANCE_LEXER;
					ZR1070 (&ZIop, &ZIn1, &ZIm1, &ZIc);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case 71:
				{
					EXP ZI1060;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRunary_Hexpression (&ZI1060);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_preinc */
					{
#line 586 "syntax.act"

    (ZIa) = make_prefix_exp ( lex_plus_Hplus, (ZI1060) ) ;
#line 4941 "syntax1.c"
					}
					/* END OF ACTION: exp_preinc */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 4949 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 4957 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 4965 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 4973 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 116:
				{
					int ZI1067;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: lex_sizeof */
					{
#line 370 "syntax.act"
 (ZI1067) = lex_sizeof ; 
#line 4991 "syntax1.c"
					}
					/* END OF ACTION: lex_sizeof */
					ZRsizeof_Hexpression (ZI1067, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 5004 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 5012 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 5020 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 5028 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 78:
				{
					EXP ZI1062;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ADVANCE_LEXER;
					ZRcast_Hexpression (&ZI1062);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_indir */
					{
#line 517 "syntax.act"

    (ZIa) = make_indir_exp ( (ZI1062) ) ;
#line 5052 "syntax1.c"
					}
					/* END OF ACTION: exp_indir */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 5060 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 5068 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 5076 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 5084 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 33:
				{
					EXP ZI1063;
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
					ZRcast_Hexpression (&ZI1063);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_ref */
					{
#line 590 "syntax.act"

    (ZIa) = make_ref_exp ( (ZI1063), 0 ) ;
#line 5120 "syntax1.c"
					}
					/* END OF ACTION: exp_ref */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 5128 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 5136 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 5144 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 5152 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 17: case 18: case 19: case 20:
			case 21: case 22:
				{
					EXP ZI1107;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					ZRliteral (&ZI1107);
					ZR925 (ZI1107, &ZIa);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 5177 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 5185 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 5193 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 5201 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 62:
				{
					EXP ZI1064;
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
					ZRcast_Hexpression (&ZI1064);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_not */
					{
#line 553 "syntax.act"

    (ZIa) = make_not_exp ( (ZI1064) ) ;
#line 5237 "syntax1.c"
					}
					/* END OF ACTION: exp_not */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 5245 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 5253 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 5261 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 5269 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			case 43: case 59: case 69: case 85:
				{
					int ZI1065;
					EXP ZI1066;
					EXP ZIa;
					int ZIn2;
					int ZIm2;
					TYPE ZIt;

					/* BEGINNING OF ACTION: lex_crt */
					{
#line 366 "syntax.act"
 (ZI1065) = crt_lex_token ; 
#line 5287 "syntax1.c"
					}
					/* END OF ACTION: lex_crt */
					ZRunary_Hoperator ();
					ZRcast_Hexpression (&ZI1066);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: exp_unary */
					{
#line 615 "syntax.act"

    (ZIa) = make_uminus_exp ( (ZI1065), (ZI1066) ) ;
#line 5301 "syntax1.c"
					}
					/* END OF ACTION: exp_unary */
					/* BEGINNING OF ACTION: diff_side_effects */
					{
#line 1380 "syntax.act"

    (ZIn2) = no_side_effects - (ZIn1) ;
#line 5309 "syntax1.c"
					}
					/* END OF ACTION: diff_side_effects */
					/* BEGINNING OF ACTION: diff_type_defns */
					{
#line 1384 "syntax.act"

    (ZIm2) = no_type_defns - (ZIm1) ;
#line 5317 "syntax1.c"
					}
					/* END OF ACTION: diff_type_defns */
					/* BEGINNING OF ACTION: type_of */
					{
#line 991 "syntax.act"

    (ZIt) = typeof_exp ( &(ZIa), (ZIn2), (ZIop) ) ;
#line 5325 "syntax1.c"
					}
					/* END OF ACTION: type_of */
					/* BEGINNING OF ACTION: exp_sizeof */
					{
#line 611 "syntax.act"

    (ZIc) = make_sizeof_exp ( (ZIt), (ZIa), (ZIm2), (ZIop) ) ;
#line 5333 "syntax1.c"
					}
					/* END OF ACTION: exp_sizeof */
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 466 */
		/* BEGINNING OF ACTION: sizeof_end */
		{
#line 1393 "syntax.act"

    suppress_usage-- ;
#line 5348 "syntax1.c"
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

/* END OF FILE */
