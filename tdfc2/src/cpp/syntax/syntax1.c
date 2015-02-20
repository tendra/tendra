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


#line 98 "syntax1.c"

/* BEGINNING OF STATIC VARIABLES */

int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
ZR1270(EXP *ZO1241)
{
	EXP ZI1241;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			NAMESPACE ZIns;
			IDENTIFIER ZIid;
			TYPE ZI1267;
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
#line 237 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 138 "syntax1.c"
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
#line 151 "syntax1.c"
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
#line 476 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 169 "syntax1.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 178 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1275 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 188 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 195 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 202 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1311 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 211 "syntax1.c"
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

    (ZIe) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 237 "syntax1.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZIe, &ZI1241);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			NAMESPACE ZIns;
			int ZIq;
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: namespace_global */
			{
#line 476 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 263 "syntax1.c"
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
#line 509 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (ZIns) ;
#line 278 "syntax1.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 674 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 286 "syntax1.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1242 (ZIe, &ZI1241);
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
	*ZO1241 = ZI1241;
}

void
ZRbase_Htype_Hspecifier(BASE_TYPE *ZObt)
{
	BASE_TYPE ZIbt;

	switch (CURRENT_TERMINAL) {
	case 127:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_bool */
			{
#line 1236 "syntax.act"
 (ZIbt) = btype_bool ; 
#line 322 "syntax1.c"
			}
			/* END OF ACTION: btype_bool */
		}
		break;
	case 185:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_bottom */
			{
#line 1241 "syntax.act"
 (ZIbt) = btype_bottom ; 
#line 334 "syntax1.c"
			}
			/* END OF ACTION: btype_bottom */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_char */
			{
#line 1228 "syntax.act"
 (ZIbt) = btype_char ; 
#line 346 "syntax1.c"
			}
			/* END OF ACTION: btype_char */
		}
		break;
	case 102:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_double */
			{
#line 1235 "syntax.act"
 (ZIbt) = btype_double ; 
#line 358 "syntax1.c"
			}
			/* END OF ACTION: btype_double */
		}
		break;
	case 106:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_float */
			{
#line 1234 "syntax.act"
 (ZIbt) = btype_float ; 
#line 370 "syntax1.c"
			}
			/* END OF ACTION: btype_float */
		}
		break;
	case 110:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_int */
			{
#line 1230 "syntax.act"
 (ZIbt) = btype_int ; 
#line 382 "syntax1.c"
			}
			/* END OF ACTION: btype_int */
		}
		break;
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_long */
			{
#line 1231 "syntax.act"
 (ZIbt) = btype_long ; 
#line 394 "syntax1.c"
			}
			/* END OF ACTION: btype_long */
		}
		break;
	case 286:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_ptrdiff_t */
			{
#line 1239 "syntax.act"
 (ZIbt) = btype_ptrdiff_t ; 
#line 406 "syntax1.c"
			}
			/* END OF ACTION: btype_ptrdiff_t */
		}
		break;
	case 114:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_short */
			{
#line 1229 "syntax.act"
 (ZIbt) = btype_short ; 
#line 418 "syntax1.c"
			}
			/* END OF ACTION: btype_short */
		}
		break;
	case 115:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_signed */
			{
#line 1232 "syntax.act"
 (ZIbt) = btype_signed ; 
#line 430 "syntax1.c"
			}
			/* END OF ACTION: btype_signed */
		}
		break;
	case 299:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_size_t */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_size_t ; 
#line 442 "syntax1.c"
			}
			/* END OF ACTION: btype_size_t */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_unsigned */
			{
#line 1233 "syntax.act"
 (ZIbt) = btype_unsigned ; 
#line 454 "syntax1.c"
			}
			/* END OF ACTION: btype_unsigned */
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_void */
			{
#line 1240 "syntax.act"
 (ZIbt) = btype_void ; 
#line 466 "syntax1.c"
			}
			/* END OF ACTION: btype_void */
		}
		break;
	case 156:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_wchar_t */
			{
#line 1237 "syntax.act"
 (ZIbt) = btype_wchar_t ; 
#line 478 "syntax1.c"
			}
			/* END OF ACTION: btype_wchar_t */
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
	*ZObt = ZIbt;
}

void
ZRmem_Hinitialiser_Hlist(NAMESPACE ZIcns)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_mem_Hinitialiser_Hlist:;
	{
		ZRmem_Hinitialiser (ZIcns);
		/* BEGINNING OF INLINE: 1020 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: mem-initialiser-list */
					goto ZL2_mem_Hinitialiser_Hlist;
					/* END OF INLINE: mem-initialiser-list */
				}
				UNREACHED;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 1020 */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1400(NAMESPACE *ZIns, IDENTIFIER *ZI1398, IDENTIFIER *ZOid)
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
#line 1242 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 552 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 526 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 562 "syntax1.c"
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
#line 531 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 589 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 445 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1398), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 597 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 606 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1398;
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
ZRdecl_Hspecifier_Hseq(TYPE ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZIb1;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;

		ZRdecl_Hspecifier (ZIs, &ZIb1, &ZIt1, &ZIcv1, &ZIds1);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: check_decl_specifier */
		{
#line 2156 "syntax.act"

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
#line 657 "syntax1.c"
		}
		/* END OF ACTION: check_decl_specifier */
		/* BEGINNING OF INLINE: 912 */
		{
			switch (CURRENT_TERMINAL) {
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
					BASE_TYPE ZIb2;
					TYPE ZIt2;
					CV_SPEC ZIcv2;
					DECL_SPEC ZIds2;

					ZRdecl_Hspecifier_Hseq (ZIs, &ZIb2, &ZIt2, &ZIcv2, &ZIds2);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: btype_join */
					{
#line 1245 "syntax.act"

    if ( (ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (ZIb1) | (ZIb2) ) ;
    }
#line 693 "syntax1.c"
					}
					/* END OF ACTION: btype_join */
					/* BEGINNING OF ACTION: type_join */
					{
#line 1300 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 709 "syntax1.c"
					}
					/* END OF ACTION: type_join */
					/* BEGINNING OF ACTION: cv_join */
					{
#line 1215 "syntax.act"

    CV_SPEC c = ( (ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIcv1) | (ZIcv2) ) ;
#line 719 "syntax1.c"
					}
					/* END OF ACTION: cv_join */
					/* BEGINNING OF ACTION: dspec_join */
					{
#line 1550 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (ZIds1) | (ZIds2) ) ;
#line 730 "syntax1.c"
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
		/* END OF INLINE: 912 */
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
ZR1147(EXP ZI1145, EXP *ZO1146)
{
	EXP ZI1146;

ZL2_1147:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			EXP ZIc;

			ZIp = ZI1145;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 331 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 776 "syntax1.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1913 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 786 "syntax1.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1894 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 794 "syntax1.c"
			}
			/* END OF ACTION: decl_hash_elif */
			ZRdeclaration_Hcond_Hbody ();
			/* BEGINNING OF INLINE: 1147 */
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				ZI1145 = ZIp;
				goto ZL2_1147;
			}
			/* END OF INLINE: 1147 */
		}
		UNREACHED;
	default:
		{
			ZI1146 = ZI1145;
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
	*ZO1146 = ZI1146;
}

void
ZRclose_Hsquare_Hx(void)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
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
	}
	return;
ZL1:;
	{
		int ZIt;

		/* BEGINNING OF ACTION: lex_close_square */
		{
#line 381 "syntax.act"
 (ZIt) = lex_close_Hsquare_H1 ; 
#line 855 "syntax1.c"
		}
		/* END OF ACTION: lex_close_square */
		/* BEGINNING OF ACTION: expected */
		{
#line 1985 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 865 "syntax1.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRnested_Hid(NAMESPACE ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 5:
		{
			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 223 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 884 "syntax1.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
		}
		break;
	case 1:
		{
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 207 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 897 "syntax1.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
		}
		break;
	case 3:
		{
			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 215 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 910 "syntax1.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
		}
		break;
	case 6:
		{
			/* BEGINNING OF EXTRACT: template-id */
			{
#line 229 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 927 "syntax1.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
		}
		break;
	case 141:
		{
			/* BEGINNING OF ACTION: decl_nspace_begin */
			{
#line 1710 "syntax.act"

    if ( add_nested_nspace ( (ZIns) ) ) {
	RESCAN_LEXER ;
    }
#line 942 "syntax1.c"
			}
			/* END OF ACTION: decl_nspace_begin */
			parse_operator (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: decl_nspace_end */
			{
#line 1716 "syntax.act"

    if ( remove_nested_nspace ( (ZIns) ) ) {
	RESCAN_LEXER ;
    }
#line 957 "syntax1.c"
			}
			/* END OF ACTION: decl_nspace_end */
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
ZRdeclarator_Htail(IDENTIFIER ZIid, TYPE *ZOt, int *ZOc)
{
	TYPE ZIt;
	int ZIc;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 949 */
			{
				{
					/* BEGINNING OF ACTION: is_initialiser */
					{
#line 2084 "syntax.act"

    /* Resolve function-style initialisers from function declarators */
    (ZI0) = predict_init () ;
#line 994 "syntax1.c"
					}
					/* END OF ACTION: is_initialiser */
					if (!ZI0)
						goto ZL3;
					/* BEGINNING OF ACTION: bool_true */
					{
#line 2040 "syntax.act"
 (ZIc) = 1 ; 
#line 1003 "syntax1.c"
					}
					/* END OF ACTION: bool_true */
					/* BEGINNING OF ACTION: type_none */
					{
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
#line 1011 "syntax1.c"
					}
					/* END OF ACTION: type_none */
					goto ZL2;
				}
				UNREACHED;
			ZL3:;
				switch (CURRENT_TERMINAL) {
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
						int ZIw;

						/* BEGINNING OF ACTION: bool_false */
						{
#line 2039 "syntax.act"
 (ZIw) = 0 ; 
#line 1036 "syntax1.c"
						}
						/* END OF ACTION: bool_false */
						/* BEGINNING OF ACTION: param_begin */
						{
#line 1189 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1047 "syntax1.c"
						}
						/* END OF ACTION: param_begin */
						ZRparameter_Htail (ZIw, &ZIt);
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
#line 1062 "syntax1.c"
						}
						/* END OF ACTION: param_end */
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2039 "syntax.act"
 (ZIc) = 0 ; 
#line 1069 "syntax1.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				default:
					goto ZL1;
				}
			ZL2:;
			}
			/* END OF INLINE: 949 */
		}
		break;
	case 332:
		{
			int ZIw;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2040 "syntax.act"
 (ZIw) = 1 ; 
#line 1098 "syntax1.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1189 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1109 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
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
#line 1124 "syntax1.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2039 "syntax.act"
 (ZIc) = 0 ; 
#line 1131 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
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
			ZR955 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1361 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 1164 "syntax1.c"
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
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2039 "syntax.act"
 (ZIc) = 0 ; 
#line 1184 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
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
	*ZOc = ZIc;
}

void
ZRparameter_Hdeclaration(TYPE ZIs, int ZIp, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZIbt;
		TYPE ZIt1;
		CV_SPEC ZIcv1;
		DECL_SPEC ZIds1;
		TYPE ZIt2;
		DECL_SPEC ZIds2;
		TYPE ZIt;
		IDENTIFIER ZIid;
		EXP ZIe;

		ZRdecl_Hspecifier_Hseq (ZIs, &ZIbt, &ZIt1, &ZIcv1, &ZIds1);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1561 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds2) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1235 "syntax1.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1694 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1243 "syntax1.c"
		}
		/* END OF ACTION: declarator_start */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_param */
		{
#line 1626 "syntax.act"

    (ZId) = make_param_decl ( (ZIds2), (ZIt), (ZIid), (ZIp) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1258 "syntax1.c"
		}
		/* END OF ACTION: declare_param */
		/* BEGINNING OF INLINE: 974 */
		{
			switch (CURRENT_TERMINAL) {
			case 36:
				{
					EXP ZIa;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: default_arg_begin */
					{
#line 2017 "syntax.act"

    in_default_arg++ ;
#line 1274 "syntax1.c"
					}
					/* END OF ACTION: default_arg_begin */
					/* BEGINNING OF INLINE: 975 */
					{
						{
							/* BEGINNING OF ACTION: is_skipped */
							{
#line 2123 "syntax.act"

    (ZI0) = ( in_class_defn && (ZIp) == CONTEXT_PARAMETER ) ;
#line 1285 "syntax1.c"
							}
							/* END OF ACTION: is_skipped */
							if (!ZI0)
								goto ZL4;
							/* BEGINNING OF ACTION: default_arg_skip */
							{
#line 1159 "syntax.act"

    (ZIa) = skip_default_arg ( (ZId) ) ;
#line 1295 "syntax1.c"
							}
							/* END OF ACTION: default_arg_skip */
							goto ZL3;
						}
						UNREACHED;
					ZL4:;
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
								ZRinitialiser_Hexpression (&ZIa);
								if ((CURRENT_TERMINAL) == 355) {
									RESTORE_LEXER;
									goto ZL1;
								}
							}
							break;
						default:
							goto ZL1;
						}
					ZL3:;
					}
					/* END OF INLINE: 975 */
					/* BEGINNING OF ACTION: default_arg_end */
					{
#line 2021 "syntax.act"

    in_default_arg-- ;
#line 1337 "syntax1.c"
					}
					/* END OF ACTION: default_arg_end */
					ZIe = ZIa;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: exp_none */
					{
#line 569 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1350 "syntax1.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			}
		}
		/* END OF INLINE: 974 */
		/* BEGINNING OF ACTION: initialise_param */
		{
#line 1755 "syntax.act"

    init_param ( (ZId), (ZIe) ) ;
#line 1363 "syntax1.c"
		}
		/* END OF ACTION: initialise_param */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOd = ZId;
}

void
ZRboolean_Hliteral(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 135:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_false */
			{
#line 662 "syntax.act"

    (ZIe) = make_bool_exp ( BOOL_FALSE, exp_int_lit_tag ) ;
#line 1389 "syntax1.c"
			}
			/* END OF ACTION: exp_false */
		}
		break;
	case 150:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_true */
			{
#line 833 "syntax.act"

    (ZIe) = make_bool_exp ( BOOL_TRUE, exp_int_lit_tag ) ;
#line 1402 "syntax1.c"
			}
			/* END OF ACTION: exp_true */
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
ZR1404(NAMESPACE *ZIns, IDENTIFIER *ZI1402, IDENTIFIER *ZOid)
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
#line 1242 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 1441 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 526 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1451 "syntax1.c"
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
#line 531 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1478 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 445 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1402), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 1486 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 1495 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1402;
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
ZR1151(TYPE ZI1149, TYPE *ZO1150)
{
	TYPE ZI1150;

ZL2_1151:;
	switch (CURRENT_TERMINAL) {
	case 66:
		{
			EXP ZIe;
			TYPE ZIq;
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
			ZRconstant_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1361 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIq) ) ;
#line 1553 "syntax1.c"
			}
			/* END OF ACTION: type_array */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1387 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1149) ) ? (ZIq) : inject_pre_type ( (ZI1149), (ZIq), 0 ) ) ;
#line 1561 "syntax1.c"
			}
			/* END OF ACTION: type_build */
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
			/* BEGINNING OF INLINE: 1151 */
			ZI1149 = ZIt;
			goto ZL2_1151;
			/* END OF INLINE: 1151 */
		}
		UNREACHED;
	default:
		{
			ZI1150 = ZI1149;
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
	*ZO1150 = ZI1150;
}

void
ZRnonempty_Hnested_Hname(NAMESPACE *ZOns)
{
	NAMESPACE ZIns;

	switch (CURRENT_TERMINAL) {
	case 9:
		{
			/* BEGINNING OF EXTRACT: full-name */
			{
#line 256 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1612 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 488 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZIns) ;
#line 1622 "syntax1.c"
			}
			/* END OF ACTION: namespace_full */
		}
		break;
	case 8:
		{
			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1634 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 483 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (ZIns) ;
#line 1644 "syntax1.c"
			}
			/* END OF ACTION: namespace_nested */
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
ZRtarget_Hcondition(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIa;
		EXP ZIp;
		int ZIr;
		EXP ZIb;

		ZRtarget_Hcondition_Hhead (&ZIa, &ZIp, &ZIr);
		/* BEGINNING OF INLINE: 702 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					int ZIs;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: cond_hash_else */
					{
#line 1918 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 1690 "syntax1.c"
					}
					/* END OF ACTION: cond_hash_else */
					/* BEGINNING OF ACTION: reach_check */
					{
#line 1111 "syntax.act"

    (ZIs) = unreached_code ;
    if ( (ZIs) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1706 "syntax1.c"
					}
					/* END OF ACTION: reach_check */
					ZRcompound_Hstatement (&ZIb);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: stmt_none */
					{
#line 867 "syntax.act"

    (ZIb) = NULL_exp ;
#line 1723 "syntax1.c"
					}
					/* END OF ACTION: stmt_none */
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 702 */
		/* BEGINNING OF ACTION: cond_hash_endif */
		{
#line 1921 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 1739 "syntax1.c"
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
#line 1122 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1753 "syntax1.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_endif */
		{
#line 1063 "syntax.act"

    (ZIe) = end_hash_if_stmt ( (ZIa), (ZIb) ) ;
#line 1761 "syntax1.c"
		}
		/* END OF ACTION: stmt_hash_endif */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1407(NAMESPACE *ZIns, IDENTIFIER *ZI1405, IDENTIFIER *ZOid)
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
#line 1242 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 1794 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 526 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1804 "syntax1.c"
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
#line 531 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1831 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 445 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1405), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 1839 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 1848 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1405;
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
ZRfield_Hid_Hexpression(NAMESPACE ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			ADVANCE_LEXER;
			ZR1315 (&ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 9:
		{
			NAMESPACE ZI1318;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 256 "syntax.act"

    ZI1318 = crt_token->pp_data.ns ;
#line 1894 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1319 (&ZIns, &ZI1318, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			NAMESPACE ZI1316;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 252 "syntax.act"

    ZI1316 = crt_token->pp_data.ns ;
#line 1914 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1317 (&ZIns, &ZI1316, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 122:
	case 123: case 127: case 156: case 185:
	case 286: case 299:
		{
			BASE_TYPE ZIbt1;
			IDENTIFIER ZIid1;
			NAMESPACE ZIns1;
			QUALIFIER ZIi;
			int ZIb;
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;
			IDENTIFIER ZIuid;

			ZRbase_Htype_Hspecifier (&ZIbt1);
			switch (CURRENT_TERMINAL) {
			case 83:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 449 "syntax.act"

    (ZIid1) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1957 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			ZIns1 = ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 526 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1967 "syntax1.c"
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
#line 531 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1994 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 445 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 2002 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 2011 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 43:
		{
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;

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
			/* BEGINNING OF ACTION: qual_none */
			{
#line 539 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2046 "syntax1.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 445 "syntax.act"

    (ZIid) = make_pseudo_destr ( (ZIid2), (ZIbt2), (ZIid2), (ZIbt2) ) ;
#line 2054 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141:
		{
			IDENTIFIER ZIuid;

			ZRnested_Hid (ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_none */
			{
#line 539 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2076 "syntax1.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2085 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			IDENTIFIER ZI1312;

			ZRunqualified_Htype (&ZItid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 492 "syntax.act"

    (ZI1312) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2106 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
			ZR1314 (&ZIns, &ZI1312, &ZIid);
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
ZRdecl_Hspecifier(TYPE ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	switch (CURRENT_TERMINAL) {
	case 2: case 7: case 8: case 9:
	case 25: case 83: case 97: case 98:
	case 102: case 104: case 106: case 110:
	case 111: case 114: case 115: case 118:
	case 121: case 122: case 123: case 124:
	case 127: case 129: case 153: case 156:
	case 185: case 286: case 299:
		{
			ZRtype_Hspecifier (ZIs, &ZIbt, &ZIt, &ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1534 "syntax.act"
 (ZIds) = dspec_none ; 
#line 2155 "syntax1.c"
			}
			/* END OF ACTION: dspec_none */
		}
		break;
	case 94: case 105: case 112: case 117:
	case 120: case 133: case 136: case 137:
	case 138: case 155: case 275:
		{
			/* BEGINNING OF INLINE: 909 */
			{
				switch (CURRENT_TERMINAL) {
				case 136:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: dspec_friend */
						{
#line 1544 "syntax.act"
 (ZIds) = dspec_friend ; 
#line 2174 "syntax1.c"
						}
						/* END OF ACTION: dspec_friend */
					}
					break;
				case 120:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: dspec_typedef */
						{
#line 1545 "syntax.act"
 (ZIds) = dspec_typedef ; 
#line 2186 "syntax1.c"
						}
						/* END OF ACTION: dspec_typedef */
					}
					break;
				case 133: case 137: case 155: case 275:
					{
						ZRfunction_Hspecifier (&ZIds);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				case 94: case 105: case 112: case 117:
				case 138:
					{
						ZRstorage_Hclass_Hspecifier (&ZIds);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 909 */
			/* BEGINNING OF ACTION: dspec_check */
			{
#line 1556 "syntax.act"

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZIds) ) ) ;
#line 2220 "syntax1.c"
			}
			/* END OF ACTION: dspec_check */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2227 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
#line 2235 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2242 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
	*ZOds = ZIds;
}

void
parse_init(IDENTIFIER ZId, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRinitialiser_Hclause (ZId, &ZIe);
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
#line 1970 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2289 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 569 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2297 "syntax1.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZRdeclaration_Hseq_Hopt(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_declaration_Hseq_Hopt:;
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
#line 2067 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2330 "syntax1.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL3;
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
#line 2349 "syntax1.c"
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
#line 2362 "syntax1.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: declare_extern */
		{
#line 1732 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2370 "syntax1.c"
		}
		/* END OF ACTION: declare_extern */
		/* BEGINNING OF INLINE: declaration-seq-opt */
		goto ZL2_declaration_Hseq_Hopt;
		/* END OF INLINE: declaration-seq-opt */
	}
	UNREACHED;
ZL3:;
	switch (CURRENT_TERMINAL) {
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
#line 1732 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2394 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		UNREACHED;
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
#line 1732 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2416 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		UNREACHED;
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
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2439 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1266 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2447 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZI1255) = cv_none ; 
#line 2454 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			ZR1256 (&ZIt, &ZIds, &ZIbt, &ZIt1, &ZI1255, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1732 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2467 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		UNREACHED;
	case 26: case 30: case 126: case 139:
	case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1849 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2484 "syntax1.c"
			}
			/* END OF ACTION: template_check */
			ZR1257 ();
			/* BEGINNING OF INLINE: declaration-seq-opt */
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_declaration_Hseq_Hopt;
			}
			/* END OF INLINE: declaration-seq-opt */
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
ZRabstract_Hdeclarator_Htail(TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			IDENTIFIER ZIid;
			int ZIw;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 449 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2526 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2039 "syntax.act"
 (ZIw) = 0 ; 
#line 2533 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1189 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2544 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
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
#line 2559 "syntax1.c"
			}
			/* END OF ACTION: param_end */
		}
		break;
	case 332:
		{
			IDENTIFIER ZIid;
			int ZIw;

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

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2584 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2040 "syntax.act"
 (ZIw) = 1 ; 
#line 2591 "syntax1.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1189 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2602 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
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
#line 2617 "syntax1.c"
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
			ZR955 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1361 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 2650 "syntax1.c"
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
ZRscoped_Hstatement(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZI1516;
		EXP ZI1556;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2074 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 2704 "syntax1.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1534 "syntax.act"
 (ZIds) = dspec_none ; 
#line 2713 "syntax1.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1266 "syntax.act"

    (ZIt) = NULL_type ;
#line 2721 "syntax1.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZI1516);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 919 "syntax.act"

    (ZI1556) = (ZI1516) ;
    in_declaration-- ;
#line 2735 "syntax1.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 2743 "syntax1.c"
		}
		/* END OF ACTION: stmt_label_clear */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1556) ) ;
#line 2751 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2759 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 2767 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZIop;
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
			EXP ZI1527;
			int ZIr;
			EXP ZI1574;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 386 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 2802 "syntax1.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1527);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 2837 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1574) = make_exp_stmt ( (ZI1527) ) ;
#line 2845 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 2853 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1574) ) ;
#line 2868 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2876 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 2884 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 83:
		{
			EXP ZI1563;
			EXP ZIa;

			ADVANCE_LEXER;
			ZR1477 (&ZI1563);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1563) ) ;
#line 2905 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2913 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 2921 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 23:
		{
			EXP ZI1281;
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
			EXP ZI1537;
			int ZIr;
			EXP ZI1584;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 345 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2956 "syntax1.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR1242 (ZI1281, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1537);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 2992 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1584) = make_exp_stmt ( (ZI1537) ) ;
#line 3000 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3008 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1584) ) ;
#line 3023 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3031 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3039 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 24:
		{
			EXP ZI1514;
			EXP ZI1553;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-stmt */
			{
#line 352 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1514 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3058 "syntax1.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1553) = make_exp_stmt ( (ZI1514) ) ;
#line 3067 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1553) ) ;
#line 3075 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3083 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3091 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 25:
		{
			TYPE ZI1267;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1284;
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
			EXP ZI1539;
			int ZIr;
			EXP ZI1586;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 359 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 3133 "syntax1.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 3141 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3148 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1311 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 3157 "syntax1.c"
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

    (ZI1284) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 3183 "syntax1.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1284, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1539);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 3218 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1586) = make_exp_stmt ( (ZI1539) ) ;
#line 3226 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3234 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1586) ) ;
#line 3249 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3257 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3265 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 130:
		{
			TYPE ZIt;
			EXP ZI1463;
			int ZIn;
			EXP ZI1273;
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
			EXP ZI1530;
			int ZIr;
			EXP ZI1577;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1463, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_const_cast */
			{
#line 618 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZIt), (ZI1463), (ZIn) ) ;
#line 3307 "syntax1.c"
			}
			/* END OF ACTION: exp_const_cast */
			ZR1242 (ZI1273, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1530);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 3342 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1577) = make_exp_stmt ( (ZI1530) ) ;
#line 3350 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3358 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1577) ) ;
#line 3373 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3381 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3389 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 5:
		{
			IDENTIFIER ZIuid;
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
			EXP ZI1542;
			int ZIr;
			EXP ZI1589;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 223 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3423 "syntax1.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 503 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3434 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 674 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 3442 "syntax1.c"
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
			ZR1291 (&ZI1289, &ZI1542);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 3477 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1589) = make_exp_stmt ( (ZI1542) ) ;
#line 3485 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3493 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1589) ) ;
#line 3508 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3516 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3524 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 206:
		{
			EXP ZI1456;
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
			EXP ZI1519;
			int ZIr;
			EXP ZI1566;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1456);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 678 "syntax.act"

    (ZI1454) = make_cast_exp ( type_void, (ZI1456), 0 ) ;
#line 3562 "syntax1.c"
			}
			/* END OF ACTION: exp_ignore */
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
			ZR1291 (&ZI1289, &ZI1519);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 3596 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1566) = make_exp_stmt ( (ZI1519) ) ;
#line 3604 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3612 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1566) ) ;
#line 3627 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3635 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3643 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 132:
		{
			TYPE ZIt;
			EXP ZI1466;
			int ZIn;
			EXP ZI1276;
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
			EXP ZI1533;
			int ZIr;
			EXP ZI1580;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1466, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dynamic_cast */
			{
#line 644 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZIt), (ZI1466), (ZIn) ) ;
#line 3685 "syntax1.c"
			}
			/* END OF ACTION: exp_dynamic_cast */
			ZR1242 (ZI1276, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1533);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 3720 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1580) = make_exp_stmt ( (ZI1533) ) ;
#line 3728 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3736 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1580) ) ;
#line 3751 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3759 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3767 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 210:
		{
			EXP ZI1279;
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
			EXP ZI1536;
			int ZIr;
			EXP ZI1583;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 648 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 3800 "syntax1.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR1242 (ZI1279, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1536);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 3835 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1583) = make_exp_stmt ( (ZI1536) ) ;
#line 3843 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 3851 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1583) ) ;
#line 3866 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3874 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3882 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 9:
		{
			NAMESPACE ZIns;
			EXP ZI1562;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 256 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3898 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1476 (&ZIns, &ZI1562);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1562) ) ;
#line 3912 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3920 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3928 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 1:
		{
			IDENTIFIER ZI1467;
			EXP ZI1557;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 207 "syntax.act"

    ZI1467 = crt_token->pp_data.id.use ;
#line 3944 "syntax1.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1472 (&ZI1467, &ZI1557);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1557) ) ;
#line 3958 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3966 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 3974 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 346:
		{
			EXP ZI1552;
			EXP ZIa;

			ADVANCE_LEXER;
			ZR1441 (&ZI1552);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1552) ) ;
#line 3995 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4003 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4011 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 255:
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
			EXP ZI1443;
			EXP ZI1265;
			EXP ZI1289;
			EXP ZI1517;
			int ZIr;
			EXP ZI1564;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1455);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 694 "syntax.act"

    (ZI1454) = make_lit_exp ( (ZI1455) ) ;
#line 4049 "syntax1.c"
			}
			/* END OF ACTION: exp_lit */
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
			ZR1291 (&ZI1289, &ZI1517);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4083 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1564) = make_exp_stmt ( (ZI1517) ) ;
#line 4091 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4099 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1564) ) ;
#line 4114 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4122 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4130 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 61:
		{
			EXP ZI1458;
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
			EXP ZI1521;
			int ZIr;
			EXP ZI1568;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1458);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 775 "syntax.act"

    (ZI1454) = make_prefix_exp ( lex_minus_Hminus, (ZI1458) ) ;
#line 4168 "syntax1.c"
			}
			/* END OF ACTION: exp_predec */
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
			ZR1291 (&ZI1289, &ZI1521);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4202 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1568) = make_exp_stmt ( (ZI1521) ) ;
#line 4210 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4218 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1568) ) ;
#line 4233 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4241 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4249 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 3:
		{
			IDENTIFIER ZI1471;
			EXP ZI1559;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 215 "syntax.act"

    ZI1471 = crt_token->pp_data.id.use ;
#line 4265 "syntax1.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			ZR1472 (&ZI1471, &ZI1559);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1559) ) ;
#line 4279 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4287 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4295 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;
			EXP ZI1561;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4311 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1475 (&ZIns, &ZI1561);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1561) ) ;
#line 4325 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4333 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4341 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 65:
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
			EXP ZI1518;
			int ZIr;
			EXP ZI1565;
			EXP ZIa;

			ADVANCE_LEXER;
			ZR1288 (&ZI1454);
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
			ZR1291 (&ZI1289, &ZI1518);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4400 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1565) = make_exp_stmt ( (ZI1518) ) ;
#line 4408 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4416 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1565) ) ;
#line 4431 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4439 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4447 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 71:
		{
			EXP ZI1457;
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
			EXP ZI1520;
			int ZIr;
			EXP ZI1567;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1457);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 779 "syntax.act"

    (ZI1454) = make_prefix_exp ( lex_plus_Hplus, (ZI1457) ) ;
#line 4485 "syntax1.c"
			}
			/* END OF ACTION: exp_preinc */
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
			ZR1291 (&ZI1289, &ZI1520);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4519 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1567) = make_exp_stmt ( (ZI1520) ) ;
#line 4527 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4535 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1567) ) ;
#line 4550 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4558 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4566 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 145:
		{
			TYPE ZIt;
			EXP ZI1464;
			int ZIn;
			EXP ZI1274;
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
			EXP ZI1531;
			int ZIr;
			EXP ZI1578;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1464, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_reinterpret_cast */
			{
#line 792 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZIt), (ZI1464), (ZIn) ) ;
#line 4608 "syntax1.c"
			}
			/* END OF ACTION: exp_reinterpret_cast */
			ZR1242 (ZI1274, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1531);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4643 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1578) = make_exp_stmt ( (ZI1531) ) ;
#line 4651 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4659 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1578) ) ;
#line 4674 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4682 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4690 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 77:
		{
			EXP ZI1550;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_none */
			{
#line 867 "syntax.act"

    (ZI1550) = NULL_exp ;
#line 4706 "syntax1.c"
			}
			/* END OF ACTION: stmt_none */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1550) ) ;
#line 4714 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4722 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4730 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 116:
		{
			int ZIop;
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
			EXP ZI1526;
			int ZIr;
			EXP ZI1573;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 393 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 4762 "syntax1.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZIop, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1526);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4797 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1573) = make_exp_stmt ( (ZI1526) ) ;
#line 4805 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4813 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1573) ) ;
#line 4828 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4836 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4844 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 78:
		{
			EXP ZI1459;
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
			EXP ZI1522;
			int ZIr;
			EXP ZI1569;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI1459);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 686 "syntax.act"

    (ZI1454) = make_indir_exp ( (ZI1459) ) ;
#line 4882 "syntax1.c"
			}
			/* END OF ACTION: exp_indir */
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
			ZR1291 (&ZI1289, &ZI1522);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 4916 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1569) = make_exp_stmt ( (ZI1522) ) ;
#line 4924 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 4932 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1569) ) ;
#line 4947 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4955 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 4963 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 4:
		{
			IDENTIFIER ZI1473;
			EXP ZI1560;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 219 "syntax.act"

    ZI1473 = crt_token->pp_data.id.use ;
#line 4979 "syntax1.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1474 (&ZI1473, &ZI1560);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1560) ) ;
#line 4993 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5001 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5009 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 146:
		{
			TYPE ZIt;
			EXP ZI1465;
			int ZIn;
			EXP ZI1275;
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
			EXP ZI1532;
			int ZIr;
			EXP ZI1579;
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZI1465, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_static_cast */
			{
#line 817 "syntax.act"

    (ZI1275) = make_static_cast_exp ( (ZIt), (ZI1465), (ZIn) ) ;
#line 5050 "syntax1.c"
			}
			/* END OF ACTION: exp_static_cast */
			ZR1242 (ZI1275, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1532);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5085 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1579) = make_exp_stmt ( (ZI1532) ) ;
#line 5093 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5101 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1579) ) ;
#line 5116 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5124 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5132 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 6:
		{
			IDENTIFIER ZIuid;
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
			EXP ZI1543;
			int ZIr;
			EXP ZI1590;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 229 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5170 "syntax1.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 503 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5181 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 674 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 5189 "syntax1.c"
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
			ZR1291 (&ZI1289, &ZI1543);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5224 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1590) = make_exp_stmt ( (ZI1543) ) ;
#line 5232 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5240 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1590) ) ;
#line 5255 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5263 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5271 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 7:
		{
			IDENTIFIER ZItid;
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
			EXP ZI1544;
			int ZIr;
			EXP ZI1591;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 237 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5314 "syntax1.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 497 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5325 "syntax1.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1275 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 5335 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_none ; 
#line 5342 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 5349 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1311 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 5358 "syntax1.c"
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

    (ZI1283) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 5384 "syntax1.c"
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
			ZR1291 (&ZI1289, &ZI1544);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5419 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1591) = make_exp_stmt ( (ZI1544) ) ;
#line 5427 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5435 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1591) ) ;
#line 5450 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5458 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5466 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 148:
		{
			EXP ZI1278;
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
			EXP ZI1535;
			int ZIr;
			EXP ZI1582;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 821 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 5499 "syntax1.c"
			}
			/* END OF ACTION: exp_this */
			ZR1242 (ZI1278, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1535);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5534 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1582) = make_exp_stmt ( (ZI1535) ) ;
#line 5542 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5550 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1582) ) ;
#line 5565 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5573 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5581 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 2:
		{
			IDENTIFIER ZI1469;
			EXP ZI1558;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 211 "syntax.act"

    ZI1469 = crt_token->pp_data.id.use ;
#line 5597 "syntax1.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			ZR1470 (&ZI1469, &ZI1558);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1558) ) ;
#line 5611 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5619 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5627 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 152:
		{
			int ZIop;
			EXP ZI1272;
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
			EXP ZI1529;
			int ZIr;
			EXP ZI1576;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 394 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 5660 "syntax1.c"
			}
			/* END OF ACTION: lex_typeid */
			ZRtypeid_Hexpression (ZIop, &ZI1272);
			ZR1242 (ZI1272, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1529);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5696 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1576) = make_exp_stmt ( (ZI1529) ) ;
#line 5704 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5712 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1576) ) ;
#line 5727 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5735 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5743 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 330:
		{
			int ZIop;
			EXP ZI1271;
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
			EXP ZI1528;
			int ZIr;
			EXP ZI1575;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 395 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 5776 "syntax1.c"
			}
			/* END OF ACTION: lex_vtable */
			ZRtypeid_Hexpression (ZIop, &ZI1271);
			ZR1242 (ZI1271, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1528);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5812 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1575) = make_exp_stmt ( (ZI1528) ) ;
#line 5820 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5828 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1575) ) ;
#line 5843 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5851 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5859 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 33:
		{
			EXP ZI1460;
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
			EXP ZI1523;
			int ZIr;
			EXP ZI1570;
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
			ZRcast_Hexpression (&ZI1460);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 787 "syntax.act"

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
#line 5909 "syntax1.c"
			}
			/* END OF ACTION: exp_ref */
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
			ZR1291 (&ZI1289, &ZI1523);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 5943 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1570) = make_exp_stmt ( (ZI1523) ) ;
#line 5951 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 5959 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1570) ) ;
#line 5974 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5982 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 5990 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1282;
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
			EXP ZI1538;
			int ZIr;
			EXP ZI1585;
			EXP ZIa;

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
#line 6036 "syntax1.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1210 "syntax.act"
 (ZIcv) = cv_none ; 
#line 6043 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1311 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 6052 "syntax1.c"
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

    (ZI1282) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 6078 "syntax1.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1282, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1538);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 6113 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1585) = make_exp_stmt ( (ZI1538) ) ;
#line 6121 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 6129 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1585) ) ;
#line 6144 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6152 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6160 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 289: case 323:
		{
			EXP ZI1549;
			EXP ZIa;

			ZRcontrol_Hstatement (&ZI1549);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1549) ) ;
#line 6180 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6188 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6196 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 96: case 100: case 223:
		{
			EXP ZI1555;
			EXP ZIa;

			ZRfall_Hcheck ();
			ZR1442 (&ZI1555);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1555) ) ;
#line 6217 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6225 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6233 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 298: case 324:
		{
			EXP ZI1436;
			EXP ZI1513;
			int ZIr;
			EXP ZI1551;
			EXP ZIa;

			ZRflow_Hexpression (&ZI1436);
			ZR1438 (&ZI1436, &ZI1513);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 6265 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1551) = make_exp_stmt ( (ZI1513) ) ;
#line 6273 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 6281 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1551) ) ;
#line 6296 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6304 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6312 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 101: case 107: case 125:
		{
			EXP ZI1546;
			EXP ZIa;

			ZRiteration_Hstatement (&ZI1546);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1546) ) ;
#line 6332 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6340 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6348 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 95: case 99: case 108: case 113:
		{
			EXP ZI1547;
			EXP ZIa;

			ZRjump_Hstatement (&ZI1547);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1547) ) ;
#line 6368 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6376 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6384 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 17: case 18: case 19: case 20:
	case 21: case 22: case 135: case 150:
		{
			EXP ZI1277;
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
			EXP ZI1534;
			int ZIr;
			EXP ZI1581;
			EXP ZIa;

			ZRliteral (&ZI1277);
			ZR1242 (ZI1277, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1534);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 6445 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1581) = make_exp_stmt ( (ZI1534) ) ;
#line 6453 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 6461 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1581) ) ;
#line 6476 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6484 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6492 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 62:
		{
			EXP ZI1461;
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
			EXP ZI1524;
			int ZIr;
			EXP ZI1571;
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
			ZRcast_Hexpression (&ZI1461);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 746 "syntax.act"

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
#line 6542 "syntax1.c"
			}
			/* END OF ACTION: exp_not */
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
			ZR1291 (&ZI1289, &ZI1524);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 6576 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1571) = make_exp_stmt ( (ZI1524) ) ;
#line 6584 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 6592 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1571) ) ;
#line 6607 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6615 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6623 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 64:
		{
			EXP ZIa;

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
#line 899 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
#line 6650 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_block */
			ZRstatement_Hseq_Hopt (ZIc, &ZIa);
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
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6676 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6684 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 141:
		{
			IDENTIFIER ZIuid;
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
			EXP ZI1541;
			int ZIr;
			EXP ZI1588;
			EXP ZIa;

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
#line 6725 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 674 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 6733 "syntax1.c"
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
			ZR1291 (&ZI1289, &ZI1541);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 6768 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1588) = make_exp_stmt ( (ZI1541) ) ;
#line 6776 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 6784 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1588) ) ;
#line 6799 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6807 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6815 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 26: case 109: case 119:
		{
			EXP ZI1545;
			EXP ZIa;

			ZRselection_Hstatement (&ZI1545);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1545) ) ;
#line 6835 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6843 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6851 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 149:
		{
			EXP ZI1289;
			EXP ZI1515;
			int ZIr;
			EXP ZI1554;
			EXP ZIa;

			ZRthrow_Hexpression (&ZI1289);
			ZR1291 (&ZI1289, &ZI1515);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 6883 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1554) = make_exp_stmt ( (ZI1515) ) ;
#line 6891 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 6899 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1554) ) ;
#line 6914 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6922 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6930 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 151:
		{
			EXP ZI1548;
			EXP ZIa;

			ZRtry_Hblock (&ZI1548);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1548) ) ;
#line 6950 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6958 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 6966 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 131: case 140:
		{
			int ZIb;
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
			EXP ZI1540;
			int ZIr;
			EXP ZI1587;
			EXP ZIa;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2039 "syntax.act"
 (ZIb) = 0 ; 
#line 6997 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
			ZR1432 (&ZIb, &ZI1454);
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
			ZR1291 (&ZI1289, &ZI1540);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 7032 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1587) = make_exp_stmt ( (ZI1540) ) ;
#line 7040 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 7048 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1587) ) ;
#line 7063 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7071 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 7079 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 43: case 59: case 69: case 85:
		{
			int ZIop;
			EXP ZI1462;
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
			EXP ZI1525;
			int ZIr;
			EXP ZI1572;
			EXP ZIa;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 379 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 7111 "syntax1.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZI1462);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 845 "syntax.act"

    (ZI1454) = make_uminus_exp ( (ZIop), (ZI1462) ) ;
#line 7125 "syntax1.c"
			}
			/* END OF ACTION: exp_unary */
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
			ZR1291 (&ZI1289, &ZI1525);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
#line 7159 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 940 "syntax.act"

    (ZI1572) = make_exp_stmt ( (ZI1525) ) ;
#line 7167 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1008 "syntax.act"

    unreached_fall = 1 ;
#line 7175 "syntax1.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 907 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1572) ) ;
#line 7190 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7198 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 7206 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
#line 1970 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 7225 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 911 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIc) ) ;
#line 7233 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2137 "syntax.act"

    RESCAN_LEXER ;
#line 7241 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
	}
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
