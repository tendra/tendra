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


#line 98 "syntax1.c"

/* BEGINNING OF STATIC VARIABLES */

int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
ZR1397(NAMESPACE *ZI1396, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 1: case 3: case 5: case 6:
	case 141: case 147:
		{
			int ZIq;
			IDENTIFIER ZIuid;

			ZRtemplate_Hopt (*ZI1396, &ZIq);
			ZRnested_Hid (*ZI1396, &ZIuid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZI1396), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZI1396) ;
#line 130 "syntax1.c"
			}
			/* END OF ACTION: namespace_templ */
		}
		break;
	case 43:
		{
			IDENTIFIER ZIid1;
			BASE_TYPE ZIbt1;
			QUALIFIER ZIi;
			int ZIb;
			IDENTIFIER ZIid2;
			BASE_TYPE ZIbt2;
			IDENTIFIER ZIuid;

			/* BEGINNING OF ACTION: namespace_type */
			{
#line 510 "syntax.act"

    (ZIid1) = DEREF_id ( nspace_name ( (*ZI1396) ) ) ;
#line 150 "syntax1.c"
			}
			/* END OF ACTION: namespace_type */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 157 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 166 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 193 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 441 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 201 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZI1396), (ZIuid), 0 ) ;
    last_namespace = (*ZI1396) ;
#line 210 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
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
ZR1270(NAMESPACE *ZIns, EXP *ZO1242)
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
#line 259 "syntax1.c"
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
#line 272 "syntax1.c"
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
    qual_namespace = (*ZIns) ;
#line 289 "syntax1.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZItid), 0 ) ;
    last_namespace = (*ZIns) ;
#line 298 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 308 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 315 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 322 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 331 "syntax1.c"
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
#line 357 "syntax1.c"
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
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZIns) ;
#line 387 "syntax1.c"
			}
			/* END OF ACTION: namespace_full */
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (*ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (*ZIns) ;
#line 396 "syntax1.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 404 "syntax1.c"
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
ZRbase_Htype_Hspecifier(BASE_TYPE *ZObt)
{
	BASE_TYPE ZIbt;

	switch (CURRENT_TERMINAL) {
	case 127:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_bool */
			{
#line 1232 "syntax.act"
 (ZIbt) = btype_bool ; 
#line 440 "syntax1.c"
			}
			/* END OF ACTION: btype_bool */
		}
		break;
	case 185:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_bottom */
			{
#line 1237 "syntax.act"
 (ZIbt) = btype_bottom ; 
#line 452 "syntax1.c"
			}
			/* END OF ACTION: btype_bottom */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_char */
			{
#line 1224 "syntax.act"
 (ZIbt) = btype_char ; 
#line 464 "syntax1.c"
			}
			/* END OF ACTION: btype_char */
		}
		break;
	case 102:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_double */
			{
#line 1231 "syntax.act"
 (ZIbt) = btype_double ; 
#line 476 "syntax1.c"
			}
			/* END OF ACTION: btype_double */
		}
		break;
	case 106:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_float */
			{
#line 1230 "syntax.act"
 (ZIbt) = btype_float ; 
#line 488 "syntax1.c"
			}
			/* END OF ACTION: btype_float */
		}
		break;
	case 110:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_int */
			{
#line 1226 "syntax.act"
 (ZIbt) = btype_int ; 
#line 500 "syntax1.c"
			}
			/* END OF ACTION: btype_int */
		}
		break;
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_long */
			{
#line 1227 "syntax.act"
 (ZIbt) = btype_long ; 
#line 512 "syntax1.c"
			}
			/* END OF ACTION: btype_long */
		}
		break;
	case 286:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_ptrdiff_t */
			{
#line 1235 "syntax.act"
 (ZIbt) = btype_ptrdiff_t ; 
#line 524 "syntax1.c"
			}
			/* END OF ACTION: btype_ptrdiff_t */
		}
		break;
	case 114:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_short */
			{
#line 1225 "syntax.act"
 (ZIbt) = btype_short ; 
#line 536 "syntax1.c"
			}
			/* END OF ACTION: btype_short */
		}
		break;
	case 115:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_signed */
			{
#line 1228 "syntax.act"
 (ZIbt) = btype_signed ; 
#line 548 "syntax1.c"
			}
			/* END OF ACTION: btype_signed */
		}
		break;
	case 299:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_size_t */
			{
#line 1234 "syntax.act"
 (ZIbt) = btype_size_t ; 
#line 560 "syntax1.c"
			}
			/* END OF ACTION: btype_size_t */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_unsigned */
			{
#line 1229 "syntax.act"
 (ZIbt) = btype_unsigned ; 
#line 572 "syntax1.c"
			}
			/* END OF ACTION: btype_unsigned */
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_void */
			{
#line 1236 "syntax.act"
 (ZIbt) = btype_void ; 
#line 584 "syntax1.c"
			}
			/* END OF ACTION: btype_void */
		}
		break;
	case 156:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_wchar_t */
			{
#line 1233 "syntax.act"
 (ZIbt) = btype_wchar_t ; 
#line 596 "syntax1.c"
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
ZR1271(EXP *ZO1242)
{
	EXP ZI1242;

	switch (CURRENT_TERMINAL) {
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			NAMESPACE ZIns;
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
#line 646 "syntax1.c"
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
#line 659 "syntax1.c"
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
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 677 "syntax1.c"
			}
			/* END OF ACTION: namespace_global */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 686 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 696 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 703 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 710 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 719 "syntax1.c"
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
#line 745 "syntax1.c"
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
			NAMESPACE ZIns;
			int ZIq;
			IDENTIFIER ZIuid;
			IDENTIFIER ZIid;
			EXP ZIe;

			/* BEGINNING OF ACTION: namespace_global */
			{
#line 472 "syntax.act"

    (ZIns) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZIns) ;
#line 771 "syntax1.c"
			}
			/* END OF ACTION: namespace_global */
			ZRtemplate_Hopt (ZIns, &ZIq);
			ZRnested_Hid (ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_templ */
			{
#line 505 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), (ZIq) ) ;
    last_namespace = (ZIns) ;
#line 786 "syntax1.c"
			}
			/* END OF ACTION: namespace_templ */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZIe) = make_id_exp ( (ZIid) ) ;
#line 794 "syntax1.c"
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
ZRmem_Hinitialiser_Hlist(NAMESPACE ZIcns)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_mem_Hinitialiser_Hlist:;
	{
		ZRmem_Hinitialiser (ZIcns);
		/* BEGINNING OF INLINE: 1021 */
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
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 1021 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZRdecl_Hspecifier_Hseq(TYPE ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
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

		ZRdecl_Hspecifier (ZIs, &ZIb1, &ZIt1, &ZIcv1, &ZIds1);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: check_decl_specifier */
		{
#line 2152 "syntax.act"

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
#line 882 "syntax1.c"
		}
		/* END OF ACTION: check_decl_specifier */
		/* BEGINNING OF INLINE: 913 */
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
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: btype_join */
					{
#line 1241 "syntax.act"

    if ( (ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (ZIb1) | (ZIb2) ) ;
    }
#line 918 "syntax1.c"
					}
					/* END OF ACTION: btype_join */
					/* BEGINNING OF ACTION: type_join */
					{
#line 1296 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 934 "syntax1.c"
					}
					/* END OF ACTION: type_join */
					/* BEGINNING OF ACTION: cv_join */
					{
#line 1211 "syntax.act"

    CV_SPEC c = ( (ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIcv1) | (ZIcv2) ) ;
#line 944 "syntax1.c"
					}
					/* END OF ACTION: cv_join */
					/* BEGINNING OF ACTION: dspec_join */
					{
#line 1546 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (ZIds1) | (ZIds2) ) ;
#line 955 "syntax1.c"
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
		/* END OF INLINE: 913 */
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
ZR1401(NAMESPACE *ZIns, IDENTIFIER *ZI1399, IDENTIFIER *ZOid)
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
#line 1238 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 1004 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1014 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1041 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 441 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1399), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 1049 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 1058 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1399;
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
ZRclose_Hsquare_Hx(void)
{
	if ((CURRENT_TERMINAL) == 356) {
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
#line 377 "syntax.act"
 (ZIt) = lex_close_Hsquare_H1 ; 
#line 1109 "syntax1.c"
		}
		/* END OF ACTION: lex_close_square */
		/* BEGINNING OF ACTION: expected */
		{
#line 1981 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 1119 "syntax1.c"
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
#line 219 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 1138 "syntax1.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
		}
		break;
	case 1:
		{
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 203 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 1151 "syntax1.c"
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
#line 1164 "syntax1.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
		}
		break;
	case 6:
		{
			/* BEGINNING OF EXTRACT: template-id */
			{
#line 225 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 1181 "syntax1.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
		}
		break;
	case 141:
		{
			/* BEGINNING OF ACTION: decl_nspace_begin */
			{
#line 1706 "syntax.act"

    if ( add_nested_nspace ( (ZIns) ) ) {
	RESCAN_LEXER ;
    }
#line 1196 "syntax1.c"
			}
			/* END OF ACTION: decl_nspace_begin */
			parse_operator (&ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: decl_nspace_end */
			{
#line 1712 "syntax.act"

    if ( remove_nested_nspace ( (ZIns) ) ) {
	RESCAN_LEXER ;
    }
#line 1211 "syntax1.c"
			}
			/* END OF ACTION: decl_nspace_end */
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
ZRdeclarator_Htail(IDENTIFIER ZIid, TYPE *ZOt, int *ZOc)
{
	TYPE ZIt;
	int ZIc;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 950 */
			{
				{
					/* BEGINNING OF ACTION: is_initialiser */
					{
#line 2080 "syntax.act"

    /* Resolve function-style initialisers from function declarators */
    (ZI0) = predict_init () ;
#line 1248 "syntax1.c"
					}
					/* END OF ACTION: is_initialiser */
					if (!ZI0)
						goto ZL3;
					/* BEGINNING OF ACTION: bool_true */
					{
#line 2036 "syntax.act"
 (ZIc) = 1 ; 
#line 1257 "syntax1.c"
					}
					/* END OF ACTION: bool_true */
					/* BEGINNING OF ACTION: type_none */
					{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 1265 "syntax1.c"
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
#line 2035 "syntax.act"
 (ZIw) = 0 ; 
#line 1290 "syntax1.c"
						}
						/* END OF ACTION: bool_false */
						/* BEGINNING OF ACTION: param_begin */
						{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1301 "syntax1.c"
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
#line 1316 "syntax1.c"
						}
						/* END OF ACTION: param_end */
						/* BEGINNING OF ACTION: bool_false */
						{
#line 2035 "syntax.act"
 (ZIc) = 0 ; 
#line 1323 "syntax1.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				default:
					goto ZL1;
				}
			ZL2:;
			}
			/* END OF INLINE: 950 */
		}
		break;
	case 333:
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
#line 2036 "syntax.act"
 (ZIw) = 1 ; 
#line 1352 "syntax1.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1363 "syntax1.c"
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
#line 1378 "syntax1.c"
			}
			/* END OF ACTION: param_end */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIc) = 0 ; 
#line 1385 "syntax1.c"
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
#line 1418 "syntax1.c"
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
#line 2035 "syntax.act"
 (ZIc) = 0 ; 
#line 1438 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
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
	*ZOc = ZIc;
}

void
ZR1148(EXP ZI1146, EXP *ZO1147)
{
	EXP ZI1147;

ZL2_1148:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			EXP ZIc;

			ZIp = ZI1146;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 327 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1475 "syntax1.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1909 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 1485 "syntax1.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1890 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 1493 "syntax1.c"
			}
			/* END OF ACTION: decl_hash_elif */
			ZRdeclaration_Hcond_Hbody ();
			/* BEGINNING OF INLINE: 1148 */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				ZI1146 = ZIp;
				goto ZL2_1148;
			}
			/* END OF INLINE: 1148 */
		}
		UNREACHED;
	default:
		{
			ZI1147 = ZI1146;
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
	*ZO1147 = ZI1147;
}

void
ZRparameter_Hdeclaration(TYPE ZIs, int ZIp, IDENTIFIER *ZOd)
{
	IDENTIFIER ZId;

	if ((CURRENT_TERMINAL) == 356) {
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
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: dspec_complete */
		{
#line 1557 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds2) = complete_dspec ( (ZIds1), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 1556 "syntax1.c"
		}
		/* END OF ACTION: dspec_complete */
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1690 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1564 "syntax1.c"
		}
		/* END OF ACTION: declarator_start */
		ZRparameter_Hdeclarator_Hopt (ZIt2, &ZIt, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: declare_param */
		{
#line 1622 "syntax.act"

    (ZId) = make_param_decl ( (ZIds2), (ZIt), (ZIid), (ZIp) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 1579 "syntax1.c"
		}
		/* END OF ACTION: declare_param */
		/* BEGINNING OF INLINE: 975 */
		{
			switch (CURRENT_TERMINAL) {
			case 36:
				{
					EXP ZIa;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: default_arg_begin */
					{
#line 2013 "syntax.act"

    in_default_arg++ ;
#line 1595 "syntax1.c"
					}
					/* END OF ACTION: default_arg_begin */
					/* BEGINNING OF INLINE: 976 */
					{
						{
							/* BEGINNING OF ACTION: is_skipped */
							{
#line 2119 "syntax.act"

    (ZI0) = ( in_class_defn && (ZIp) == CONTEXT_PARAMETER ) ;
#line 1606 "syntax1.c"
							}
							/* END OF ACTION: is_skipped */
							if (!ZI0)
								goto ZL4;
							/* BEGINNING OF ACTION: default_arg_skip */
							{
#line 1155 "syntax.act"

    (ZIa) = skip_default_arg ( (ZId) ) ;
#line 1616 "syntax1.c"
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
						case 286: case 299: case 331:
							{
								ZRinitialiser_Hexpression (&ZIa);
								if ((CURRENT_TERMINAL) == 356) {
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
					/* END OF INLINE: 976 */
					/* BEGINNING OF ACTION: default_arg_end */
					{
#line 2017 "syntax.act"

    in_default_arg-- ;
#line 1658 "syntax1.c"
					}
					/* END OF ACTION: default_arg_end */
					ZIe = ZIa;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: exp_none */
					{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1671 "syntax1.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			}
		}
		/* END OF INLINE: 975 */
		/* BEGINNING OF ACTION: initialise_param */
		{
#line 1751 "syntax.act"

    init_param ( (ZId), (ZIe) ) ;
#line 1684 "syntax1.c"
		}
		/* END OF ACTION: initialise_param */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
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
#line 658 "syntax.act"

    (ZIe) = make_bool_exp ( BOOL_FALSE, exp_int_lit_tag ) ;
#line 1710 "syntax1.c"
			}
			/* END OF ACTION: exp_false */
		}
		break;
	case 150:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_true */
			{
#line 829 "syntax.act"

    (ZIe) = make_bool_exp ( BOOL_TRUE, exp_int_lit_tag ) ;
#line 1723 "syntax1.c"
			}
			/* END OF ACTION: exp_true */
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
ZR1405(NAMESPACE *ZIns, IDENTIFIER *ZI1403, IDENTIFIER *ZOid)
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
#line 1238 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 1762 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 1772 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 1799 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 441 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1403), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 1807 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 1816 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1403;
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
ZRnonempty_Hnested_Hname(NAMESPACE *ZOns)
{
	NAMESPACE ZIns;

	switch (CURRENT_TERMINAL) {
	case 9:
		{
			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1850 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_full */
			{
#line 484 "syntax.act"

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZIns) ;
#line 1860 "syntax1.c"
			}
			/* END OF ACTION: namespace_full */
		}
		break;
	case 8:
		{
			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 1872 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_nested */
			{
#line 479 "syntax.act"

    crt_id_qualifier = qual_nested ;
    qual_namespace = (ZIns) ;
#line 1882 "syntax1.c"
			}
			/* END OF ACTION: namespace_nested */
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
	*ZOns = ZIns;
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
		/* BEGINNING OF INLINE: 703 */
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					int ZIs;

					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: cond_hash_else */
					{
#line 1914 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 1928 "syntax1.c"
					}
					/* END OF ACTION: cond_hash_else */
					/* BEGINNING OF ACTION: reach_check */
					{
#line 1107 "syntax.act"

    (ZIs) = unreached_code ;
    if ( (ZIs) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1944 "syntax1.c"
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
#line 863 "syntax.act"

    (ZIb) = NULL_exp ;
#line 1961 "syntax1.c"
					}
					/* END OF ACTION: stmt_none */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 703 */
		/* BEGINNING OF ACTION: cond_hash_endif */
		{
#line 1917 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 1977 "syntax1.c"
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
#line 1118 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 1991 "syntax1.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_endif */
		{
#line 1059 "syntax.act"

    (ZIe) = end_hash_if_stmt ( (ZIa), (ZIb) ) ;
#line 1999 "syntax1.c"
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
ZR1152(TYPE ZI1150, TYPE *ZO1151)
{
	TYPE ZI1151;

ZL2_1152:;
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1357 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIq) ) ;
#line 2048 "syntax1.c"
			}
			/* END OF ACTION: type_array */
			/* BEGINNING OF ACTION: type_build */
			{
#line 1383 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1150) ) ? (ZIq) : inject_pre_type ( (ZI1150), (ZIq), 0 ) ) ;
#line 2056 "syntax1.c"
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
			/* BEGINNING OF INLINE: 1152 */
			ZI1150 = ZIt;
			goto ZL2_1152;
			/* END OF INLINE: 1152 */
		}
		UNREACHED;
	default:
		{
			ZI1151 = ZI1150;
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
	*ZO1151 = ZI1151;
}

void
ZRfield_Hid_Hexpression(NAMESPACE ZIns, IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 83:
		{
			ADVANCE_LEXER;
			ZR1316 (&ZIns, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 9:
		{
			NAMESPACE ZI1319;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZI1319 = crt_token->pp_data.ns ;
#line 2119 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1320 (&ZIns, &ZI1319, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 8:
		{
			NAMESPACE ZI1317;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 248 "syntax.act"

    ZI1317 = crt_token->pp_data.ns ;
#line 2139 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1318 (&ZIns, &ZI1317, &ZIid);
			if ((CURRENT_TERMINAL) == 356) {
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
			case 356:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 445 "syntax.act"

    (ZIid1) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2182 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			ZIns1 = ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 2192 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 2219 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 441 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (ZIid1), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 2227 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 2236 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_none */
			{
#line 535 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2271 "syntax1.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 441 "syntax.act"

    (ZIid) = make_pseudo_destr ( (ZIid2), (ZIbt2), (ZIid2), (ZIbt2) ) ;
#line 2279 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141:
		{
			IDENTIFIER ZIuid;

			ZRnested_Hid (ZIns, &ZIuid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_none */
			{
#line 535 "syntax.act"

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
#line 2301 "syntax1.c"
			}
			/* END OF ACTION: qual_none */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns), (ZIuid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2310 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZItid;
			IDENTIFIER ZI1313;

			ZRunqualified_Htype (&ZItid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZI1313) = check_id ( (ZIns), (ZItid), 0 ) ;
    last_namespace = (ZIns) ;
#line 2331 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
			ZR1315 (&ZIns, &ZI1313, &ZIid);
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 2380 "syntax1.c"
			}
			/* END OF ACTION: dspec_none */
		}
		break;
	case 94: case 105: case 112: case 117:
	case 120: case 133: case 136: case 137:
	case 138: case 155: case 275:
		{
			/* BEGINNING OF INLINE: 910 */
			{
				switch (CURRENT_TERMINAL) {
				case 136:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: dspec_friend */
						{
#line 1540 "syntax.act"
 (ZIds) = dspec_friend ; 
#line 2399 "syntax1.c"
						}
						/* END OF ACTION: dspec_friend */
					}
					break;
				case 120:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: dspec_typedef */
						{
#line 1541 "syntax.act"
 (ZIds) = dspec_typedef ; 
#line 2411 "syntax1.c"
						}
						/* END OF ACTION: dspec_typedef */
					}
					break;
				case 133: case 137: case 155: case 275:
					{
						ZRfunction_Hspecifier (&ZIds);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				case 94: case 105: case 112: case 117:
				case 138:
					{
						ZRstorage_Hclass_Hspecifier (&ZIds);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 910 */
			/* BEGINNING OF ACTION: dspec_check */
			{
#line 1552 "syntax.act"

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZIds) ) ) ;
#line 2445 "syntax1.c"
			}
			/* END OF ACTION: dspec_check */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2452 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 2460 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2467 "syntax1.c"
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
#line 1966 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2514 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 565 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2522 "syntax1.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZR1408(NAMESPACE *ZIns, IDENTIFIER *ZI1406, IDENTIFIER *ZOid)
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
#line 1238 "syntax.act"
 (ZIbt1) = btype_none ; 
#line 2551 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			ZIns1 = *ZIns;
			/* BEGINNING OF ACTION: qual_get */
			{
#line 522 "syntax.act"

    (ZIi) = crt_id_qualifier ;
    (ZIb) = crt_templ_qualifier ;
#line 2561 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: qual_set */
			{
#line 527 "syntax.act"

    crt_id_qualifier = (ZIi) ;
    crt_templ_qualifier = (ZIb) ;
#line 2588 "syntax1.c"
			}
			/* END OF ACTION: qual_set */
			/* BEGINNING OF ACTION: pseudo_destructor */
			{
#line 441 "syntax.act"

    (ZIuid) = make_pseudo_destr ( (*ZI1406), (ZIbt1), (ZIid2), (ZIbt2) ) ;
#line 2596 "syntax1.c"
			}
			/* END OF ACTION: pseudo_destructor */
			/* BEGINNING OF ACTION: namespace_id */
			{
#line 488 "syntax.act"

    (ZIid) = check_id ( (ZIns1), (ZIuid), 0 ) ;
    last_namespace = (ZIns1) ;
#line 2605 "syntax1.c"
			}
			/* END OF ACTION: namespace_id */
		}
		break;
	default:
		{
			ZIid = *ZI1406;
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
ZRdeclaration_Hseq_Hopt(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_declaration_Hseq_Hopt:;
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
		EXP ZIe;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 2063 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 2651 "syntax1.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL3;
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
#line 2670 "syntax1.c"
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
#line 2683 "syntax1.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: declare_extern */
		{
#line 1728 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2691 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1728 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2715 "syntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1728 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2737 "syntax1.c"
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
			CV_SPEC ZI1256;
			EXP ZIe;

			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2760 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1262 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2768 "syntax1.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZI1256) = cv_none ; 
#line 2775 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			ZR1257 (&ZIt, &ZIds, &ZIbt, &ZIt1, &ZI1256, &ZIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_extern */
			{
#line 1728 "syntax.act"

    external_declaration ( (ZIe), 1 ) ;
#line 2788 "syntax1.c"
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
#line 1845 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2805 "syntax1.c"
			}
			/* END OF ACTION: template_check */
			ZR1258 ();
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
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (356);
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
#line 445 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2847 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIw) = 0 ; 
#line 2854 "syntax1.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2865 "syntax1.c"
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
#line 2880 "syntax1.c"
			}
			/* END OF ACTION: param_end */
		}
		break;
	case 333:
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
#line 445 "syntax.act"

    (ZIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 2905 "syntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2036 "syntax.act"
 (ZIw) = 1 ; 
#line 2912 "syntax1.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 1185 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2923 "syntax1.c"
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
#line 2938 "syntax1.c"
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
#line 2971 "syntax1.c"
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
ZRscoped_Hstatement(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZI1517;
		EXP ZI1557;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2070 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 3025 "syntax1.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1530 "syntax.act"
 (ZIds) = dspec_none ; 
#line 3034 "syntax1.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIt) = NULL_type ;
#line 3042 "syntax1.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZI1517);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 915 "syntax.act"

    (ZI1557) = (ZI1517) ;
    in_declaration-- ;
#line 3056 "syntax1.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3064 "syntax1.c"
		}
		/* END OF ACTION: stmt_label_clear */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1557) ) ;
#line 3072 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3080 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3088 "syntax1.c"
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
			EXP ZI1528;
			int ZIr;
			EXP ZI1575;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 382 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 3123 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1528);
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
#line 3158 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1575) = make_exp_stmt ( (ZI1528) ) ;
#line 3166 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3174 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1575) ) ;
#line 3189 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3197 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3205 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 83:
		{
			EXP ZI1564;
			EXP ZIa;

			ADVANCE_LEXER;
			ZR1478 (&ZI1564);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1564) ) ;
#line 3226 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3234 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3242 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1538;
			int ZIr;
			EXP ZI1585;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 341 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1282 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3277 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1538);
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
#line 3313 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1585) = make_exp_stmt ( (ZI1538) ) ;
#line 3321 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3329 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1585) ) ;
#line 3344 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3352 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3360 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 24:
		{
			EXP ZI1515;
			EXP ZI1554;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-stmt */
			{
#line 348 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1515 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3379 "syntax1.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1554) = make_exp_stmt ( (ZI1515) ) ;
#line 3388 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1554) ) ;
#line 3396 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3404 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3412 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1540;
			int ZIr;
			EXP ZI1587;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 355 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1268 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 3454 "syntax1.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 3462 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 3469 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 3478 "syntax1.c"
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
#line 3504 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1540);
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
#line 3539 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1587) = make_exp_stmt ( (ZI1540) ) ;
#line 3547 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3555 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1587) ) ;
#line 3570 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3578 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3586 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1531;
			int ZIr;
			EXP ZI1578;
			EXP ZIa;

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
#line 3628 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1531);
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
#line 3663 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1578) = make_exp_stmt ( (ZI1531) ) ;
#line 3671 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3679 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1578) ) ;
#line 3694 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3702 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3710 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1543;
			int ZIr;
			EXP ZI1590;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 219 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 3744 "syntax1.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 3755 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 3763 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1543);
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
#line 3798 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1590) = make_exp_stmt ( (ZI1543) ) ;
#line 3806 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3814 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1590) ) ;
#line 3829 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3837 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3845 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1520;
			int ZIr;
			EXP ZI1567;
			EXP ZIa;

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
#line 3883 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1520);
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
#line 3917 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1567) = make_exp_stmt ( (ZI1520) ) ;
#line 3925 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 3933 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1567) ) ;
#line 3948 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 3956 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 3964 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1534;
			int ZIr;
			EXP ZI1581;
			EXP ZIa;

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
#line 4006 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1534);
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
#line 4041 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1581) = make_exp_stmt ( (ZI1534) ) ;
#line 4049 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4057 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1581) ) ;
#line 4072 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4080 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4088 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1537;
			int ZIr;
			EXP ZI1584;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 644 "syntax.act"

    (ZI1280) = make_ellipsis_exp () ;
#line 4121 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1537);
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
#line 4156 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1584) = make_exp_stmt ( (ZI1537) ) ;
#line 4164 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4172 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1584) ) ;
#line 4187 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4195 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4203 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 9:
		{
			NAMESPACE ZIns;
			EXP ZI1563;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 252 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4219 "syntax1.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1477 (&ZIns, &ZI1563);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1563) ) ;
#line 4233 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4241 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4249 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 1:
		{
			IDENTIFIER ZI1468;
			EXP ZI1558;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 203 "syntax.act"

    ZI1468 = crt_token->pp_data.id.use ;
#line 4265 "syntax1.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1473 (&ZI1468, &ZI1558);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1558) ) ;
#line 4279 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4287 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4295 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 347:
		{
			EXP ZI1553;
			EXP ZIa;

			ADVANCE_LEXER;
			ZR1442 (&ZI1553);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1553) ) ;
#line 4316 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4324 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4332 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1518;
			int ZIr;
			EXP ZI1565;
			EXP ZIa;

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
#line 4370 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1518);
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
#line 4404 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1565) = make_exp_stmt ( (ZI1518) ) ;
#line 4412 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4420 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1565) ) ;
#line 4435 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4443 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4451 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1522;
			int ZIr;
			EXP ZI1569;
			EXP ZIa;

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
#line 4489 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1522);
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
#line 4523 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1569) = make_exp_stmt ( (ZI1522) ) ;
#line 4531 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4539 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1569) ) ;
#line 4554 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4562 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4570 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 3:
		{
			IDENTIFIER ZI1472;
			EXP ZI1560;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 211 "syntax.act"

    ZI1472 = crt_token->pp_data.id.use ;
#line 4586 "syntax1.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			ZR1473 (&ZI1472, &ZI1560);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1560) ) ;
#line 4600 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4608 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4616 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;
			EXP ZI1562;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 248 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4632 "syntax1.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1476 (&ZIns, &ZI1562);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1562) ) ;
#line 4646 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4654 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4662 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1519;
			int ZIr;
			EXP ZI1566;
			EXP ZIa;

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
			ZR1292 (&ZI1290, &ZI1519);
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
#line 4721 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1566) = make_exp_stmt ( (ZI1519) ) ;
#line 4729 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4737 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1566) ) ;
#line 4752 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4760 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4768 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1521;
			int ZIr;
			EXP ZI1568;
			EXP ZIa;

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
#line 4806 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1521);
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
#line 4840 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1568) = make_exp_stmt ( (ZI1521) ) ;
#line 4848 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4856 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1568) ) ;
#line 4871 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 4879 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 4887 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1532;
			int ZIr;
			EXP ZI1579;
			EXP ZIa;

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
#line 4929 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1532);
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
#line 4964 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1579) = make_exp_stmt ( (ZI1532) ) ;
#line 4972 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 4980 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1579) ) ;
#line 4995 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5003 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5011 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 77:
		{
			EXP ZI1551;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_none */
			{
#line 863 "syntax.act"

    (ZI1551) = NULL_exp ;
#line 5027 "syntax1.c"
			}
			/* END OF ACTION: stmt_none */
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1551) ) ;
#line 5035 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5043 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5051 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1527;
			int ZIr;
			EXP ZI1574;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 389 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 5083 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1527);
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
#line 5118 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1574) = make_exp_stmt ( (ZI1527) ) ;
#line 5126 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5134 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1574) ) ;
#line 5149 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5157 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5165 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1523;
			int ZIr;
			EXP ZI1570;
			EXP ZIa;

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
#line 5203 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1523);
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
#line 5237 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1570) = make_exp_stmt ( (ZI1523) ) ;
#line 5245 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5253 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1570) ) ;
#line 5268 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5276 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5284 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 4:
		{
			IDENTIFIER ZI1474;
			EXP ZI1561;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 215 "syntax.act"

    ZI1474 = crt_token->pp_data.id.use ;
#line 5300 "syntax1.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1475 (&ZI1474, &ZI1561);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1561) ) ;
#line 5314 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5322 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5330 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1533;
			int ZIr;
			EXP ZI1580;
			EXP ZIa;

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
#line 5371 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1533);
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
#line 5406 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1580) = make_exp_stmt ( (ZI1533) ) ;
#line 5414 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5422 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1580) ) ;
#line 5437 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5445 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5453 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1544;
			int ZIr;
			EXP ZI1591;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 225 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5491 "syntax1.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 499 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5502 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 5510 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1544);
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
#line 5545 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1591) = make_exp_stmt ( (ZI1544) ) ;
#line 5553 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5561 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1591) ) ;
#line 5576 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5584 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5592 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1545;
			int ZIr;
			EXP ZI1592;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 233 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5635 "syntax1.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 493 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5646 "syntax1.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1271 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1268) ) ;
    COPY_id ( type_name ( (ZI1268) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 5656 "syntax1.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1238 "syntax.act"
 (ZIbt) = btype_none ; 
#line 5663 "syntax1.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 5670 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 5679 "syntax1.c"
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
#line 5705 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1545);
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
#line 5740 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1592) = make_exp_stmt ( (ZI1545) ) ;
#line 5748 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5756 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1592) ) ;
#line 5771 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5779 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5787 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1536;
			int ZIr;
			EXP ZI1583;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 817 "syntax.act"

    (ZI1279) = make_this_exp () ;
#line 5820 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1536);
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
#line 5855 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1583) = make_exp_stmt ( (ZI1536) ) ;
#line 5863 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 5871 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1583) ) ;
#line 5886 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5894 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5902 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 2:
		{
			IDENTIFIER ZI1470;
			EXP ZI1559;
			EXP ZIa;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 207 "syntax.act"

    ZI1470 = crt_token->pp_data.id.use ;
#line 5918 "syntax1.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			ZR1471 (&ZI1470, &ZI1559);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1559) ) ;
#line 5932 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 5940 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 5948 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1530;
			int ZIr;
			EXP ZI1577;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 390 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 5981 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1530);
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
#line 6017 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1577) = make_exp_stmt ( (ZI1530) ) ;
#line 6025 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6033 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1577) ) ;
#line 6048 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6056 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6064 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1529;
			int ZIr;
			EXP ZI1576;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 391 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 6097 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1529);
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
#line 6133 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1576) = make_exp_stmt ( (ZI1529) ) ;
#line 6141 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6149 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1576) ) ;
#line 6164 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6172 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6180 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1524;
			int ZIr;
			EXP ZI1571;
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
			ZRcast_Hexpression (&ZI1461);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 783 "syntax.act"

    (ZI1455) = make_ref_exp ( (ZI1461), 0 ) ;
#line 6230 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1524);
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
#line 6264 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1571) = make_exp_stmt ( (ZI1524) ) ;
#line 6272 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6280 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1571) ) ;
#line 6295 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6303 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6311 "syntax1.c"
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
			EXP ZI1539;
			int ZIr;
			EXP ZI1586;
			EXP ZIa;

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
#line 6357 "syntax1.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1206 "syntax.act"
 (ZIcv) = cv_none ; 
#line 6364 "syntax1.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1307 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1268), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 6373 "syntax1.c"
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
#line 6399 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1539);
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
#line 6434 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1586) = make_exp_stmt ( (ZI1539) ) ;
#line 6442 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6450 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1586) ) ;
#line 6465 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6473 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6481 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 289: case 323:
		{
			EXP ZI1550;
			EXP ZIa;

			ZRcontrol_Hstatement (&ZI1550);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1550) ) ;
#line 6501 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6509 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6517 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 96: case 100: case 223:
		{
			EXP ZI1556;
			EXP ZIa;

			ZRfall_Hcheck ();
			ZR1443 (&ZI1556);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1556) ) ;
#line 6538 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6546 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6554 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 298: case 324:
		{
			EXP ZI1437;
			EXP ZI1514;
			int ZIr;
			EXP ZI1552;
			EXP ZIa;

			ZRflow_Hexpression (&ZI1437);
			ZR1439 (&ZI1437, &ZI1514);
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
#line 6586 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1552) = make_exp_stmt ( (ZI1514) ) ;
#line 6594 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6602 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1552) ) ;
#line 6617 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6625 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6633 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 101: case 107: case 125:
		{
			EXP ZI1547;
			EXP ZIa;

			ZRiteration_Hstatement (&ZI1547);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1547) ) ;
#line 6653 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6661 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6669 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 95: case 99: case 108: case 113:
		{
			EXP ZI1548;
			EXP ZIa;

			ZRjump_Hstatement (&ZI1548);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1548) ) ;
#line 6689 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6697 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6705 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1535;
			int ZIr;
			EXP ZI1582;
			EXP ZIa;

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
			ZR1292 (&ZI1290, &ZI1535);
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
#line 6766 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1582) = make_exp_stmt ( (ZI1535) ) ;
#line 6774 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6782 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1582) ) ;
#line 6797 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6805 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6813 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1525;
			int ZIr;
			EXP ZI1572;
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
			ZRcast_Hexpression (&ZI1462);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 742 "syntax.act"

    (ZI1455) = make_not_exp ( (ZI1462) ) ;
#line 6863 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1525);
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
#line 6897 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1572) = make_exp_stmt ( (ZI1525) ) ;
#line 6905 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 6913 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1572) ) ;
#line 6928 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 6936 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 6944 "syntax1.c"
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
#line 895 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
#line 6971 "syntax1.c"
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
#line 6997 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7005 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1542;
			int ZIr;
			EXP ZI1589;
			EXP ZIa;

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
#line 7046 "syntax1.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 670 "syntax.act"

    (ZI1286) = make_id_exp ( (ZIid) ) ;
#line 7054 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1542);
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
#line 7089 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1589) = make_exp_stmt ( (ZI1542) ) ;
#line 7097 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 7105 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1589) ) ;
#line 7120 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7128 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7136 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 26: case 109: case 119:
		{
			EXP ZI1546;
			EXP ZIa;

			ZRselection_Hstatement (&ZI1546);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1546) ) ;
#line 7156 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7164 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7172 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 149:
		{
			EXP ZI1290;
			EXP ZI1516;
			int ZIr;
			EXP ZI1555;
			EXP ZIa;

			ZRthrow_Hexpression (&ZI1290);
			ZR1292 (&ZI1290, &ZI1516);
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
#line 7204 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1555) = make_exp_stmt ( (ZI1516) ) ;
#line 7212 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 7220 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1555) ) ;
#line 7235 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7243 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7251 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 151:
		{
			EXP ZI1549;
			EXP ZIa;

			ZRtry_Hblock (&ZI1549);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1549) ) ;
#line 7271 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7279 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7287 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1541;
			int ZIr;
			EXP ZI1588;
			EXP ZIa;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2035 "syntax.act"
 (ZIb) = 0 ; 
#line 7318 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1541);
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
#line 7353 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1588) = make_exp_stmt ( (ZI1541) ) ;
#line 7361 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 7369 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1588) ) ;
#line 7384 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7392 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7400 "syntax1.c"
			}
			/* END OF ACTION: rescan_token */
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
			EXP ZI1526;
			int ZIr;
			EXP ZI1573;
			EXP ZIa;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 375 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 7432 "syntax1.c"
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
#line 7446 "syntax1.c"
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
			ZR1292 (&ZI1290, &ZI1526);
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
#line 7480 "syntax1.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 936 "syntax.act"

    (ZI1573) = make_exp_stmt ( (ZI1526) ) ;
#line 7488 "syntax1.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1004 "syntax.act"

    unreached_fall = 1 ;
#line 7496 "syntax1.c"
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
#line 903 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIc), (ZI1573) ) ;
#line 7511 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: stmt_compound_end */
			{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 7519 "syntax1.c"
			}
			/* END OF ACTION: stmt_compound_end */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7527 "syntax1.c"
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
#line 1966 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 7546 "syntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 907 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIc) ) ;
#line 7554 "syntax1.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2133 "syntax.act"

    RESCAN_LEXER ;
#line 7562 "syntax1.c"
		}
		/* END OF ACTION: rescan_token */
	}
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
