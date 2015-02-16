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


#line 110 "syntax1.c"

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
#line 249 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 150 "syntax1.c"
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
#line 163 "syntax1.c"
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
#line 181 "syntax1.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 190 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1287 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 200 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 207 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 214 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 223 "syntax1.c"
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

    (ZIe) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 249 "syntax1.c"
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
#line 488 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 275 "syntax1.c"
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
#line 521 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (ZIns) ;
#line 290 "syntax1.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 298 "syntax1.c"
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
#line 1248 "syntax.act"
 (ZIbt) = btype_bool ; 
#line 334 "syntax1.c"
			}
			/* END OF ACTION: btype_bool */
		}
		break;
	case 185:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_bottom */
			{
#line 1253 "syntax.act"
 (ZIbt) = btype_bottom ; 
#line 346 "syntax1.c"
			}
			/* END OF ACTION: btype_bottom */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_char */
			{
#line 1240 "syntax.act"
 (ZIbt) = btype_char ; 
#line 358 "syntax1.c"
			}
			/* END OF ACTION: btype_char */
		}
		break;
	case 102:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_double */
			{
#line 1247 "syntax.act"
 (ZIbt) = btype_double ; 
#line 370 "syntax1.c"
			}
			/* END OF ACTION: btype_double */
		}
		break;
	case 106:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_float */
			{
#line 1246 "syntax.act"
 (ZIbt) = btype_float ; 
#line 382 "syntax1.c"
			}
			/* END OF ACTION: btype_float */
		}
		break;
	case 110:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_int */
			{
#line 1242 "syntax.act"
 (ZIbt) = btype_int ; 
#line 394 "syntax1.c"
			}
			/* END OF ACTION: btype_int */
		}
		break;
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_long */
			{
#line 1243 "syntax.act"
 (ZIbt) = btype_long ; 
#line 406 "syntax1.c"
			}
			/* END OF ACTION: btype_long */
		}
		break;
	case 286:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_ptrdiff_t */
			{
#line 1251 "syntax.act"
 (ZIbt) = btype_ptrdiff_t ; 
#line 418 "syntax1.c"
			}
			/* END OF ACTION: btype_ptrdiff_t */
		}
		break;
	case 114:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_short */
			{
#line 1241 "syntax.act"
 (ZIbt) = btype_short ; 
#line 430 "syntax1.c"
			}
			/* END OF ACTION: btype_short */
		}
		break;
	case 115:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_signed */
			{
#line 1244 "syntax.act"
 (ZIbt) = btype_signed ; 
#line 442 "syntax1.c"
			}
			/* END OF ACTION: btype_signed */
		}
		break;
	case 299:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_size_t */
			{
#line 1250 "syntax.act"
 (ZIbt) = btype_size_t ; 
#line 454 "syntax1.c"
			}
			/* END OF ACTION: btype_size_t */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_unsigned */
			{
#line 1245 "syntax.act"
 (ZIbt) = btype_unsigned ; 
#line 466 "syntax1.c"
			}
			/* END OF ACTION: btype_unsigned */
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_void */
			{
#line 1252 "syntax.act"
 (ZIbt) = btype_void ; 
#line 478 "syntax1.c"
			}
			/* END OF ACTION: btype_void */
		}
		break;
	case 156:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_wchar_t */
			{
#line 1249 "syntax.act"
 (ZIbt) = btype_wchar_t ; 
#line 490 "syntax1.c"
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
				/*UNREACHED*/
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
#line 1254 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 564 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 574 "syntax1.c"
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
#line 601 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1398), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 609 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 618 "syntax1.c"
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
#line 2168 "syntax.act"

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
#line 669 "syntax1.c"
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
#line 1257 "syntax.act"

    if ( (ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (ZIb1) | (ZIb2) ) ;
    }
#line 705 "syntax1.c"
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
#line 721 "syntax1.c"
					}
					/* END OF ACTION: type_join */
					/* BEGINNING OF ACTION: cv_join */
					{
#line 1227 "syntax.act"

    CV_SPEC c = ( (ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIcv1) | (ZIcv2) ) ;
#line 731 "syntax1.c"
					}
					/* END OF ACTION: cv_join */
					/* BEGINNING OF ACTION: dspec_join */
					{
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (ZIds1) | (ZIds2) ) ;
#line 742 "syntax1.c"
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
#line 343 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 788 "syntax1.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1925 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 798 "syntax1.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1906 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 806 "syntax1.c"
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
		/*UNREACHED*/
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
#line 393 "syntax.act"
 (ZIt) = lex_close_Hsquare_H1 ; 
#line 867 "syntax1.c"
		}
		/* END OF ACTION: lex_close_square */
		/* BEGINNING OF ACTION: expected */
		{
#line 1997 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 877 "syntax1.c"
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
#line 235 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 896 "syntax1.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
		}
		break;
	case 1:
		{
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 909 "syntax1.c"
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

    ZIid = crt_token->pp_data.id.use ;
#line 922 "syntax1.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
		}
		break;
	case 6:
		{
			/* BEGINNING OF EXTRACT: template-id */
			{
#line 241 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 939 "syntax1.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
		}
		break;
	case 141:
		{
			/* BEGINNING OF ACTION: decl_nspace_begin */
			{
#line 1722 "syntax.act"

    if ( add_nested_nspace ( (ZIns) ) ) {
	RESCAN_LEXER ;
    }
#line 954 "syntax1.c"
			}
			/* END OF ACTION: decl_nspace_begin */
			parse_operator (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: decl_nspace_end */
			{
#line 1728 "syntax.act"

    if ( remove_nested_nspace ( (ZIns) ) ) {
	RESCAN_LEXER ;
    }
#line 969 "syntax1.c"
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
#line 2096 "syntax.act"

    /* Resolve function-style initialisers from function declarators */
    (ZI0) = predict_init () ;
#line 1006 "syntax1.c"
					}
					/* END OF ACTION: is_initialiser */
					if (!ZI0)
						goto ZL3;
					/* BEGINNING OF ACTION: bool_true */
					{
#line 2052 "syntax.act"
 (ZIc) = 1 ; 
#line 1015 "syntax1.c"
					}
					/* END OF ACTION: bool_true */
					/* BEGINNING OF ACTION: type_none */
					{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1023 "syntax1.c"
					}
					/* END OF ACTION: type_none */
					goto ZL2;
				}
				/*UNREACHED*/
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
#line 2051 "syntax.act"
 (ZIw) = 0 ; 
#line 1048 "syntax1.c"
						}
						/* END OF ACTION: bool_false */
						/* BEGINNING OF ACTION: param_begin */
						{
#line 1201 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1059 "syntax1.c"
						}
						/* END OF ACTION: param_begin */
						ZRparameter_Htail (ZIw, &ZIt);
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
#line 1074 "syntax1.c"
						}
						/* END OF ACTION: param_end */
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2051 "syntax.act"
 (ZIc) = 0 ; 
#line 1081 "syntax1.c"
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
#line 2052 "syntax.act"
 (ZIw) = 1 ; 
#line 1110 "syntax1.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1201 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1121 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
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
#line 1136 "syntax1.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIc) = 0 ; 
#line 1143 "syntax1.c"
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
#line 1373 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 1176 "syntax1.c"
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
#line 2051 "syntax.act"
 (ZIc) = 0 ; 
#line 1196 "syntax1.c"
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
#line 1573 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds2) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1247 "syntax1.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1255 "syntax1.c"
		}
		/* END OF ACTION: declarator_start */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_param */
		{
#line 1638 "syntax.act"

    (ZId) = make_param_decl ( (ZIds2), (ZIt), (ZIid), (ZIp) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1270 "syntax1.c"
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
#line 2029 "syntax.act"

    in_default_arg++ ;
#line 1286 "syntax1.c"
					}
					/* END OF ACTION: default_arg_begin */
					/* BEGINNING OF INLINE: 975 */
					{
						{
							/* BEGINNING OF ACTION: is_skipped */
							{
#line 2135 "syntax.act"

    (ZI0) = ( in_class_defn && (ZIp) == CONTEXT_PARAMETER ) ;
#line 1297 "syntax1.c"
							}
							/* END OF ACTION: is_skipped */
							if (!ZI0)
								goto ZL4;
							/* BEGINNING OF ACTION: default_arg_skip */
							{
#line 1171 "syntax.act"

    (ZIa) = skip_default_arg ( (ZId) ) ;
#line 1307 "syntax1.c"
							}
							/* END OF ACTION: default_arg_skip */
							goto ZL3;
						}
						/*UNREACHED*/
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
#line 2033 "syntax.act"

    in_default_arg-- ;
#line 1349 "syntax1.c"
					}
					/* END OF ACTION: default_arg_end */
					ZIe = ZIa;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: exp_none */
					{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1362 "syntax1.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			}
		}
		/* END OF INLINE: 974 */
		/* BEGINNING OF ACTION: initialise_param */
		{
#line 1767 "syntax.act"

    init_param ( (ZId), (ZIe) ) ;
#line 1375 "syntax1.c"
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
#line 674 "syntax.act"

    (ZIe) = make_bool_exp ( BOOL_FALSE, exp_int_lit_tag ) ;
#line 1401 "syntax1.c"
			}
			/* END OF ACTION: exp_false */
		}
		break;
	case 150:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_true */
			{
#line 845 "syntax.act"

    (ZIe) = make_bool_exp ( BOOL_TRUE, exp_int_lit_tag ) ;
#line 1414 "syntax1.c"
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
#line 1254 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 1453 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1463 "syntax1.c"
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
#line 1490 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1402), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 1498 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 1507 "syntax1.c"
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
#line 1373 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIq) ) ;
#line 1565 "syntax1.c"
			}
			/* END OF ACTION: type_array */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1399 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1149) ) ? (ZIq) : inject_pre_type ( (ZI1149), (ZIq), 0 ) ) ;
#line 1573 "syntax1.c"
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
		/*UNREACHED*/
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
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1624 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 500 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZIns) ;
#line 1634 "syntax1.c"
			}
			/* END OF ACTION: namespace_full */
		}
		break;
	case 8:
		{
			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1646 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 495 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (ZIns) ;
#line 1656 "syntax1.c"
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
#line 1930 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 1702 "syntax1.c"
					}
					/* END OF ACTION: cond_hash_else */
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
#line 1718 "syntax1.c"
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
#line 879 "syntax.act"

    (ZIb) = NULL_exp ;
#line 1735 "syntax1.c"
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
#line 1933 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 1751 "syntax1.c"
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
#line 1134 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1765 "syntax1.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_endif */
		{
#line 1075 "syntax.act"

    (ZIe) = end_hash_if_stmt ( (ZIa), (ZIb) ) ;
#line 1773 "syntax1.c"
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
#line 1254 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 1806 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1816 "syntax1.c"
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
#line 1843 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1405), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 1851 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 1860 "syntax1.c"
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
#line 268 "syntax.act"

    ZI1318 = crt_token->pp_data.ns ;
#line 1906 "syntax1.c"
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
#line 264 "syntax.act"

    ZI1316 = crt_token->pp_data.ns ;
#line 1926 "syntax1.c"
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
#line 461 "syntax.act"

    (ZIid1) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1969 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			ZIns1 = ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 538 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1979 "syntax1.c"
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
#line 2006 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 2014 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 2023 "syntax1.c"
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
#line 551 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2058 "syntax1.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 457 "syntax.act"

    (ZIid) = make_pseudo_destr ( (ZIid2), (ZIbt2), (ZIid2), (ZIbt2) ) ;
#line 2066 "syntax1.c"
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
#line 551 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2088 "syntax1.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 504 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2097 "syntax1.c"
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
#line 504 "syntax.act"

    (ZI1312) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2118 "syntax1.c"
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
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 2167 "syntax1.c"
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
#line 1556 "syntax.act"
 (ZIds) = dspec_friend ; 
#line 2186 "syntax1.c"
						}
						/* END OF ACTION: dspec_friend */
					}
					break;
				case 120:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: dspec_typedef */
						{
#line 1557 "syntax.act"
 (ZIds) = dspec_typedef ; 
#line 2198 "syntax1.c"
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
#line 1568 "syntax.act"

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZIds) ) ) ;
#line 2232 "syntax1.c"
			}
			/* END OF ACTION: dspec_check */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2239 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 2247 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2254 "syntax1.c"
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
#line 1982 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2301 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2309 "syntax1.c"
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
#line 2079 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2342 "syntax1.c"
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
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2361 "syntax1.c"
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
#line 2374 "syntax1.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: declare_extern */
		{
#line 1744 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2382 "syntax1.c"
		}
		/* END OF ACTION: declare_extern */
		/* BEGINNING OF INLINE: declaration-seq-opt */
		goto ZL2_declaration_Hseq_Hopt;
		/* END OF INLINE: declaration-seq-opt */
	}
	/*UNREACHED*/
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
#line 1744 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2406 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		/*UNREACHED*/
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
#line 2428 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		/*UNREACHED*/
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
#line 2451 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2459 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZI1255) = cv_none ; 
#line 2466 "syntax1.c"
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
#line 2479 "syntax1.c"
			}
			/* END OF ACTION: declare_extern */
			/* BEGINNING OF INLINE: declaration-seq-opt */
			goto ZL2_declaration_Hseq_Hopt;
			/* END OF INLINE: declaration-seq-opt */
		}
		/*UNREACHED*/
	case 26: case 30: case 126: case 139:
	case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1861 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2496 "syntax1.c"
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
#line 461 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2538 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIw) = 0 ; 
#line 2545 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1201 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2556 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
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
#line 2571 "syntax1.c"
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
#line 461 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2596 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIw) = 1 ; 
#line 2603 "syntax1.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1201 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2614 "syntax1.c"
			}
			/* END OF ACTION: param_begin */
			ZRparameter_Htail (ZIw, &ZIt);
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
#line 2629 "syntax1.c"
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
#line 1373 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 2662 "syntax1.c"
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
#line 2086 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 2716 "syntax1.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 2725 "syntax1.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 2733 "syntax1.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZI1516);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 931 "syntax.act"

    (ZI1556) = (ZI1516) ;
    in_declaration-- ;
#line 2747 "syntax1.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 2755 "syntax1.c"
		}
		/* END OF ACTION: stmt_label_clear */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1556) ) ;
#line 2763 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2771 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 2779 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
		goto ZL0;
	}
	/*UNREACHED*/
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
#line 398 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 2814 "syntax1.c"
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
#line 2849 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1574) = make_exp_stmt ( (ZI1527) ) ;
#line 2857 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 2865 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1574) ) ;
#line 2880 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2888 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 2896 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1563) ) ;
#line 2917 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2925 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 2933 "syntax1.c"
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
#line 357 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 2968 "syntax1.c"
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
#line 3004 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1584) = make_exp_stmt ( (ZI1537) ) ;
#line 3012 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3020 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1584) ) ;
#line 3035 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3043 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3051 "syntax1.c"
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
#line 364 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1514 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3070 "syntax1.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1553) = make_exp_stmt ( (ZI1514) ) ;
#line 3079 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1553) ) ;
#line 3087 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3095 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3103 "syntax1.c"
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
#line 371 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 3145 "syntax1.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 3153 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3160 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 3169 "syntax1.c"
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

    (ZI1284) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 3195 "syntax1.c"
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
#line 3230 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1586) = make_exp_stmt ( (ZI1539) ) ;
#line 3238 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3246 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1586) ) ;
#line 3261 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3269 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3277 "syntax1.c"
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
#line 630 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZIt), (ZI1463), (ZIn) ) ;
#line 3319 "syntax1.c"
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
#line 3354 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1577) = make_exp_stmt ( (ZI1530) ) ;
#line 3362 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3370 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1577) ) ;
#line 3385 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3393 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3401 "syntax1.c"
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
#line 235 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3435 "syntax1.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3446 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 3454 "syntax1.c"
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
#line 3489 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1589) = make_exp_stmt ( (ZI1542) ) ;
#line 3497 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3505 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1589) ) ;
#line 3520 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3528 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3536 "syntax1.c"
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
#line 690 "syntax.act"

    (ZI1454) = make_cast_exp ( type_void, (ZI1456), 0 ) ;
#line 3574 "syntax1.c"
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
#line 3608 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1566) = make_exp_stmt ( (ZI1519) ) ;
#line 3616 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3624 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1566) ) ;
#line 3639 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3647 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3655 "syntax1.c"
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
#line 656 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZIt), (ZI1466), (ZIn) ) ;
#line 3697 "syntax1.c"
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
#line 3732 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1580) = make_exp_stmt ( (ZI1533) ) ;
#line 3740 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3748 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1580) ) ;
#line 3763 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3771 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3779 "syntax1.c"
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
#line 660 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 3812 "syntax1.c"
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
#line 3847 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1583) = make_exp_stmt ( (ZI1536) ) ;
#line 3855 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3863 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1583) ) ;
#line 3878 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3886 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3894 "syntax1.c"
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
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 3910 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1562) ) ;
#line 3924 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3932 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3940 "syntax1.c"
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
#line 219 "syntax.act"

    ZI1467 = crt_token->pp_data.id.use ;
#line 3956 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1557) ) ;
#line 3970 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3978 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3986 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1552) ) ;
#line 4007 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4015 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4023 "syntax1.c"
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
#line 706 "syntax.act"

    (ZI1454) = make_lit_exp ( (ZI1455) ) ;
#line 4061 "syntax1.c"
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
#line 4095 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1564) = make_exp_stmt ( (ZI1517) ) ;
#line 4103 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4111 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1564) ) ;
#line 4126 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4134 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4142 "syntax1.c"
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
#line 787 "syntax.act"

    (ZI1454) = make_prefix_exp ( lex_minus_Hminus, (ZI1458) ) ;
#line 4180 "syntax1.c"
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
#line 4214 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1568) = make_exp_stmt ( (ZI1521) ) ;
#line 4222 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4230 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1568) ) ;
#line 4245 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4253 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4261 "syntax1.c"
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
#line 227 "syntax.act"

    ZI1471 = crt_token->pp_data.id.use ;
#line 4277 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1559) ) ;
#line 4291 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4299 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4307 "syntax1.c"
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
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4323 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1561) ) ;
#line 4337 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4345 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4353 "syntax1.c"
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
#line 4412 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1565) = make_exp_stmt ( (ZI1518) ) ;
#line 4420 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4428 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1565) ) ;
#line 4443 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4451 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4459 "syntax1.c"
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
#line 791 "syntax.act"

    (ZI1454) = make_prefix_exp ( lex_plus_Hplus, (ZI1457) ) ;
#line 4497 "syntax1.c"
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
#line 4531 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1567) = make_exp_stmt ( (ZI1520) ) ;
#line 4539 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4547 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1567) ) ;
#line 4562 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4570 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4578 "syntax1.c"
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
#line 804 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZIt), (ZI1464), (ZIn) ) ;
#line 4620 "syntax1.c"
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
#line 4655 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1578) = make_exp_stmt ( (ZI1531) ) ;
#line 4663 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4671 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1578) ) ;
#line 4686 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4694 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4702 "syntax1.c"
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
#line 879 "syntax.act"

    (ZI1550) = NULL_exp ;
#line 4718 "syntax1.c"
			}
			/* END OF ACTION: stmt_none */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1550) ) ;
#line 4726 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4734 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4742 "syntax1.c"
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
#line 405 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 4774 "syntax1.c"
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
#line 4809 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1573) = make_exp_stmt ( (ZI1526) ) ;
#line 4817 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4825 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1573) ) ;
#line 4840 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4848 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4856 "syntax1.c"
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
#line 698 "syntax.act"

    (ZI1454) = make_indir_exp ( (ZI1459) ) ;
#line 4894 "syntax1.c"
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
#line 4928 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1569) = make_exp_stmt ( (ZI1522) ) ;
#line 4936 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4944 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1569) ) ;
#line 4959 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4967 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 4975 "syntax1.c"
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
#line 231 "syntax.act"

    ZI1473 = crt_token->pp_data.id.use ;
#line 4991 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1560) ) ;
#line 5005 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5013 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5021 "syntax1.c"
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
#line 829 "syntax.act"

    (ZI1275) = make_static_cast_exp ( (ZIt), (ZI1465), (ZIn) ) ;
#line 5062 "syntax1.c"
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
#line 5097 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1579) = make_exp_stmt ( (ZI1532) ) ;
#line 5105 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5113 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1579) ) ;
#line 5128 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5136 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5144 "syntax1.c"
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
#line 241 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5182 "syntax1.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5193 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 5201 "syntax1.c"
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
#line 5236 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1590) = make_exp_stmt ( (ZI1543) ) ;
#line 5244 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5252 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1590) ) ;
#line 5267 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5275 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5283 "syntax1.c"
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
#line 249 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5326 "syntax1.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 509 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5337 "syntax1.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1287 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 5347 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 5354 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 5361 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 5370 "syntax1.c"
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

    (ZI1283) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 5396 "syntax1.c"
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
#line 5431 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1591) = make_exp_stmt ( (ZI1544) ) ;
#line 5439 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5447 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1591) ) ;
#line 5462 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5470 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5478 "syntax1.c"
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
#line 833 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 5511 "syntax1.c"
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
#line 5546 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1582) = make_exp_stmt ( (ZI1535) ) ;
#line 5554 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5562 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1582) ) ;
#line 5577 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5585 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5593 "syntax1.c"
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
#line 223 "syntax.act"

    ZI1469 = crt_token->pp_data.id.use ;
#line 5609 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1558) ) ;
#line 5623 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5631 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5639 "syntax1.c"
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
#line 406 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 5672 "syntax1.c"
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
#line 5708 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1576) = make_exp_stmt ( (ZI1529) ) ;
#line 5716 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5724 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1576) ) ;
#line 5739 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5747 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5755 "syntax1.c"
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
#line 407 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 5788 "syntax1.c"
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
#line 5824 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1575) = make_exp_stmt ( (ZI1528) ) ;
#line 5832 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5840 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1575) ) ;
#line 5855 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5863 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 5871 "syntax1.c"
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
#line 799 "syntax.act"

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
#line 5921 "syntax1.c"
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
#line 5955 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1570) = make_exp_stmt ( (ZI1523) ) ;
#line 5963 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5971 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1570) ) ;
#line 5986 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5994 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6002 "syntax1.c"
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
#line 1282 "syntax.act"

    (ZI1267) = NULL_type ;
    have_type_specifier = 1 ;
#line 6048 "syntax1.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 6055 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 6064 "syntax1.c"
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

    (ZI1282) = make_func_cast_exp ( (ZIt), (ZIp) ) ;
#line 6090 "syntax1.c"
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
#line 6125 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1585) = make_exp_stmt ( (ZI1538) ) ;
#line 6133 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6141 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1585) ) ;
#line 6156 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6164 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6172 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1549) ) ;
#line 6192 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6200 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6208 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1555) ) ;
#line 6229 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6237 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6245 "syntax1.c"
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
#line 6277 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1551) = make_exp_stmt ( (ZI1513) ) ;
#line 6285 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6293 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1551) ) ;
#line 6308 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6316 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6324 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1546) ) ;
#line 6344 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6352 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6360 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1547) ) ;
#line 6380 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6388 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6396 "syntax1.c"
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
#line 6457 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1581) = make_exp_stmt ( (ZI1534) ) ;
#line 6465 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6473 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1581) ) ;
#line 6488 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6496 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6504 "syntax1.c"
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
#line 758 "syntax.act"

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
#line 6554 "syntax1.c"
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
#line 6588 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1571) = make_exp_stmt ( (ZI1524) ) ;
#line 6596 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6604 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1571) ) ;
#line 6619 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6627 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6635 "syntax1.c"
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
#line 911 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
#line 6662 "syntax1.c"
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
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6688 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6696 "syntax1.c"
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
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 6737 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 6745 "syntax1.c"
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
#line 6780 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1588) = make_exp_stmt ( (ZI1541) ) ;
#line 6788 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6796 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1588) ) ;
#line 6811 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6819 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6827 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1545) ) ;
#line 6847 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6855 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6863 "syntax1.c"
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
#line 6895 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1554) = make_exp_stmt ( (ZI1515) ) ;
#line 6903 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6911 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1554) ) ;
#line 6926 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6934 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6942 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1548) ) ;
#line 6962 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6970 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 6978 "syntax1.c"
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
#line 2051 "syntax.act"
 (ZIb) = 0 ; 
#line 7009 "syntax1.c"
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
#line 7044 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1587) = make_exp_stmt ( (ZI1540) ) ;
#line 7052 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 7060 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1587) ) ;
#line 7075 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7083 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 7091 "syntax1.c"
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
#line 391 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 7123 "syntax1.c"
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
#line 857 "syntax.act"

    (ZI1454) = make_uminus_exp ( (ZIop), (ZI1462) ) ;
#line 7137 "syntax1.c"
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
#line 7171 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZI1572) = make_exp_stmt ( (ZI1525) ) ;
#line 7179 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 7187 "syntax1.c"
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
#line 919 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1572) ) ;
#line 7202 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7210 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 7218 "syntax1.c"
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
#line 1982 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 7237 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 923 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIc) ) ;
#line 7245 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 7253 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
	}
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
