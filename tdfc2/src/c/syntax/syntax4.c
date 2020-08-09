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


#line 96 "syntax4.c"

void
ZRmember_Hdesignator(OFFSET ZIb, TYPE ZIs, OFFSET *ZOa, TYPE *ZOt)
{
	OFFSET ZIa;
	TYPE ZIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		NAMESPACE ZIns;
		IDENTIFIER ZIid;

		/* BEGINNING OF ACTION: offset_nspace */
		{
#line 1266 "syntax.act"

    (ZIns) = offset_nspace ( (ZIs) ) ;
#line 116 "syntax4.c"
		}
		/* END OF ACTION: offset_nspace */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 124 "syntax4.c"
		}
		/* END OF ACTION: rescan_token */
		ZRfield_Hid_Hexpression (ZIns, &ZIid);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: offset_member */
		{
#line 1270 "syntax.act"

    OFFSET off = offset_member ( (ZIs), (ZIid), &(ZIt), (ZIns), 1 ) ;
    (ZIa) = offset_add ( (ZIb), off ) ;
#line 138 "syntax4.c"
		}
		/* END OF ACTION: offset_member */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 146 "syntax4.c"
		}
		/* END OF ACTION: rescan_token */
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
			/* BEGINNING OF INLINE: 810 */
			{
				switch (CURRENT_TERMINAL) {
				case 28:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: cond_hash_else */
						{
#line 1319 "syntax.act"

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
#line 184 "syntax4.c"
						}
						/* END OF ACTION: cond_hash_else */
						/* BEGINNING OF ACTION: decl_hash_else */
						{
#line 1300 "syntax.act"

    target_decl ( lex_else, NULL_exp ) ;
#line 192 "syntax4.c"
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
			/* END OF INLINE: 810 */
			/* BEGINNING OF ACTION: cond_hash_endif */
			{
#line 1322 "syntax.act"

    crt_hash_cond = (ZIp) ;
#line 215 "syntax4.c"
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
#line 1304 "syntax.act"

    target_decl ( lex_endif, NULL_exp ) ;
#line 230 "syntax4.c"
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
ZR863(TYPE ZI861, TYPE *ZO862)
{
	TYPE ZI862;

ZL2_863:;
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
#line 1050 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI861) ) ? (ZIq) : inject_pre_type ( (ZI861), (ZIq), 0 ) ) ;
#line 268 "syntax4.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 863 */
			ZI861 = ZIt;
			goto ZL2_863;
			/* END OF INLINE: 863 */
		}
		UNREACHED;
	default:
		{
			ZI862 = ZI861;
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
	*ZO862 = ZI862;
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
#line 986 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 318 "syntax4.c"
		}
		/* END OF ACTION: type_complete */
		/* BEGINNING OF INLINE: 788 */
		{
			switch (CURRENT_TERMINAL) {
			case 73:
				{
					EXP ZIc;

					ADVANCE_LEXER;
					ZRconstant_Hexpression (&ZIc);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: type_bitfield */
					{
#line 1035 "syntax.act"

    (ZIt) = make_bitfield_type ( (ZIq), (ZIbt), (ZIc), 0 ) ;
#line 339 "syntax4.c"
					}
					/* END OF ACTION: type_bitfield */
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
		/* END OF INLINE: 788 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOt = ZIt;
}

void
ZR871(TYPE ZI867, IDENTIFIER ZI868, TYPE *ZO869, IDENTIFIER *ZO870)
{
	TYPE ZI869;
	IDENTIFIER ZI870;

ZL2_871:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 333:
		{
			IDENTIFIER ZIid;
			TYPE ZIq;
			TYPE ZIt;

			ZIid = ZI868;
			ZRdeclarator_Htail (ZIid, &ZIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1050 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI867) ) ? (ZIq) : inject_pre_type ( (ZI867), (ZIq), 0 ) ) ;
#line 390 "syntax4.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 871 */
			ZI867 = ZIt;
			ZI868 = ZIid;
			goto ZL2_871;
			/* END OF INLINE: 871 */
		}
		UNREACHED;
	default:
		{
			ZI869 = ZI867;
			ZI870 = ZI868;
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
	*ZO869 = ZI869;
	*ZO870 = ZI870;
}

void
ZR618(EXP *ZOa)
{
	EXP ZIa;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255: case 298:
	case 324: case 347:
		{
			ZRexpression (&ZIa);
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
#line 432 "syntax.act"

    (ZIa) = NULL_exp ;
#line 446 "syntax4.c"
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
	*ZOa = ZIa;
}

void
parse_operator(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

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
#line 479 "syntax4.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: id_none */
		{
#line 383 "syntax.act"

    (ZIid) = NULL_id ;
#line 487 "syntax4.c"
		}
		/* END OF ACTION: id_none */
	}
	*ZOid = ZIid;
}

void
ZRinclusive_Hor_Hexpression(EXP *ZO888)
{
	EXP ZI888;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRexclusive_Hor_Hexpression (&ZIe);
		ZR889 (ZIe, &ZI888);
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
	*ZO888 = ZI888;
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
#line 724 "syntax.act"

    report ( crt_loc, ERR_stmt_goto_case ( lex_case ) ) ;
    (ZIe) = begin_case_stmt ( (ZIc), 1 ) ;
#line 542 "syntax4.c"
			}
			/* END OF ACTION: stmt_goto_case */
		}
		break;
	case 100:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_goto_default */
			{
#line 729 "syntax.act"

    report ( crt_loc, ERR_stmt_goto_case ( lex_default ) ) ;
    (ZIe) = begin_default_stmt ( 1 ) ;
#line 556 "syntax4.c"
			}
			/* END OF ACTION: stmt_goto_default */
		}
		break;
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
#line 575 "syntax4.c"
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
#line 588 "syntax4.c"
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
#line 601 "syntax4.c"
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
			/* BEGINNING OF ACTION: stmt_goto */
			{
#line 719 "syntax.act"

    (ZIe) = make_goto_stmt ( (ZIid) ) ;
#line 617 "syntax4.c"
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
ZRcomma_Hexpression_Htail(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255:
		{
			EXP ZIa;

			ZRassignment_Hexpression (&ZIa);
			ZR1027 (&ZIa, &ZIp);
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
#line 417 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 674 "syntax4.c"
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
#line 417 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 695 "syntax4.c"
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
#line 1404 "syntax.act"
 (ZIell) = 1 ; 
#line 727 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	case 2: case 25: case 94: case 97:
	case 98: case 102: case 104: case 105:
	case 106: case 110: case 111: case 112:
	case 114: case 115: case 117: case 118:
	case 120: case 121: case 122: case 123:
	case 124: case 137: case 156: case 185:
	case 286: case 299:
		{
			IDENTIFIER ZId;

			ZRparameter_Hdeclaration (&ZId);
			/* BEGINNING OF INLINE: 774 */
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
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 1403 "syntax.act"
 (ZIell) = 0 ; 
#line 760 "syntax4.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				case 356:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 774 */
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
ZRliteral(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 17: case 18:
		{
			/* BEGINNING OF INLINE: character-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 17:
					{
						/* BEGINNING OF EXTRACT: char-exp */
						{
#line 290 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 804 "syntax4.c"
						}
						/* END OF EXTRACT: char-exp */
						ADVANCE_LEXER;
					}
					break;
				case 18:
					{
						/* BEGINNING OF EXTRACT: wchar-exp */
						{
#line 294 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 817 "syntax4.c"
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
#line 277 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 842 "syntax4.c"
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
#line 273 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 867 "syntax4.c"
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
#line 298 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 892 "syntax4.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 302 "syntax.act"

    ZIe = crt_token->pp_data.exp ;
#line 905 "syntax4.c"
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
ZRsecond_Hparameter_Hid(IDENTIFIER *ZOid)
{
	IDENTIFIER ZIid;

	switch (CURRENT_TERMINAL) {
	case 2:
		{
			/* BEGINNING OF EXTRACT: type-name */
			{
#line 200 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 944 "syntax4.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_weak */
			{
#line 1232 "syntax.act"

    report ( crt_loc, ERR_dcl_fct_par_typedef ( (ZIid) ) ) ;
#line 953 "syntax4.c"
			}
			/* END OF ACTION: declarator_weak */
		}
		break;
	case 1: case 4:
		{
			/* BEGINNING OF INLINE: first-parameter-id */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 196 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 970 "syntax4.c"
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
#line 983 "syntax4.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: first-parameter-id */
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
parse_decl(TYPE ZIt, DECL_SPEC ZIds)
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
#line 1031 "syntax4.c"
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
#line 1049 "syntax4.c"
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
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1347 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 1076 "syntax4.c"
		}
		/* END OF ACTION: error_syntax */
	}
}

void
ZR877(EXP ZI875, EXP *ZO876)
{
	EXP ZI876;

ZL2_877:;
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			EXP ZIp;
			EXP ZIc;

			ZIp = ZI875;
			/* BEGINNING OF EXTRACT: hash-elif */
			{
#line 318 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 1100 "syntax4.c"
			}
			/* END OF EXTRACT: hash-elif */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cond_hash_elif */
			{
#line 1314 "syntax.act"

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
#line 1110 "syntax4.c"
			}
			/* END OF ACTION: cond_hash_elif */
			/* BEGINNING OF ACTION: decl_hash_elif */
			{
#line 1295 "syntax.act"

    target_decl ( lex_elif, (ZIc) ) ;
#line 1118 "syntax4.c"
			}
			/* END OF ACTION: decl_hash_elif */
			ZRdeclaration_Hcond_Hbody ();
			/* BEGINNING OF INLINE: 877 */
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				ZI875 = ZIp;
				goto ZL2_877;
			}
			/* END OF INLINE: 877 */
		}
		UNREACHED;
	default:
		{
			ZI876 = ZI875;
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
	*ZO876 = ZI876;
}

void
ZRexclusive_Hor_Hexpression(EXP *ZO892)
{
	EXP ZI892;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRand_Hexpression (&ZIe);
		ZR893 (ZIe, &ZI892);
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
	*ZO892 = ZI892;
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
		int ZId;
		EXP ZIa;

		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 653 "syntax.act"

    (ZIc) = begin_compound_stmt ( 1 ) ;
#line 1193 "syntax4.c"
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
#line 661 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
    (ZId) = 1 ;
#line 1215 "syntax4.c"
		}
		/* END OF ACTION: stmt_compound_block */
		ZRstatement_Hseq_Hopt (ZIc, ZId, &ZIa);
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
#line 670 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 1241 "syntax4.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1465 "syntax.act"

    RESCAN_LEXER ;
#line 1249 "syntax4.c"
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
#line 368 "syntax.act"
 (ZIt) = lex_semicolon ; 
#line 1285 "syntax4.c"
		}
		/* END OF ACTION: lex_semicolon */
		/* BEGINNING OF ACTION: expected */
		{
#line 1357 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 1295 "syntax4.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZRlogical_Hor_Hexpression(EXP *ZO880)
{
	EXP ZI880;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRlogical_Hand_Hexpression (&ZIe);
		ZR881 (ZIe, &ZI880);
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
	*ZO880 = ZI880;
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
#line 496 "syntax.act"

    (ZIe) = convert_reference ( (ZIa), REF_NORMAL ) ;
    (ZIe) = convert_lvalue ( (ZIe) ) ;
#line 1349 "syntax4.c"
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
ZR881(EXP ZI879, EXP *ZO880)
{
	EXP ZI880;

ZL2_881:;
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
#line 533 "syntax.act"

    (ZIe) = make_log_or_exp ( (ZI879), (ZIb) ) ;
#line 1396 "syntax4.c"
			}
			/* END OF ACTION: exp_log_or */
			/* BEGINNING OF INLINE: 881 */
			ZI879 = ZIe;
			goto ZL2_881;
			/* END OF INLINE: 881 */
		}
		UNREACHED;
	default:
		{
			ZI880 = ZI879;
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
	*ZO880 = ZI880;
}

void
ZR627(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	switch (CURRENT_TERMINAL) {
	case 42:
		{
			ADVANCE_LEXER;
			ZRexpression_Hlist (&ZIp);
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

    (ZIp) = NULL_list ( EXP ) ;
#line 1444 "syntax4.c"
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
ZRptr_Hoperator(TYPE *ZOp)
{
	TYPE ZIp;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		CV_SPEC ZIcv;

		switch (CURRENT_TERMINAL) {
		case 78:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcv_Hqualifier_Hseq_Hopt (&ZIcv);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_ptr */
		{
#line 1010 "syntax.act"

    MAKE_type_ptr ( (ZIcv), NULL_type, (ZIp) ) ;
#line 1488 "syntax4.c"
		}
		/* END OF ACTION: type_ptr */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZOp = ZIp;
}

void
ZRequality_Hexpression(EXP *ZO904)
{
	EXP ZI904;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRrelational_Hexpression (&ZIe);
		ZR905 (ZIe, &ZI904);
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
	*ZO904 = ZI904;
}

void
ZRinit_Hdeclarator_Hlist(DECL_SPEC ZIds, BASE_TYPE ZIbt, TYPE ZIt)
{
	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
ZL2_init_Hdeclarator_Hlist:;
	{
		ZRinit_Hdeclarator (ZIds, ZIbt, ZIt);
		/* BEGINNING OF INLINE: 801 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
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
		/* END OF INLINE: 801 */
	}
	return;
ZL1:;
	SAVE_LEXER (356);
	return;
}

void
ZR885(EXP ZI883, EXP *ZO884)
{
	EXP ZI884;

ZL2_885:;
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
#line 529 "syntax.act"

    (ZIe) = make_log_and_exp ( (ZI883), (ZIb) ) ;
#line 1596 "syntax4.c"
			}
			/* END OF ACTION: exp_log_and */
			/* BEGINNING OF INLINE: 885 */
			ZI883 = ZIe;
			goto ZL2_885;
			/* END OF INLINE: 885 */
		}
		UNREACHED;
	default:
		{
			ZI884 = ZI883;
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
	*ZO884 = ZI884;
}

void
ZR758(TYPE *ZOs)
{
	TYPE ZIs;

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
#line 1647 "syntax4.c"
			}
			/* END OF ACTION: type_func */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: type_func_none */
			{
#line 1026 "syntax.act"

    (ZIs) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
#line 1659 "syntax4.c"
			}
			/* END OF ACTION: type_func_none */
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
	*ZOs = ZIs;
}

void
ZR1014(EXP *ZI1013, EXP *ZOe)
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
#line 453 "syntax.act"

    (ZIe) = make_assign_exp ( (*ZI1013), (ZIb), 1 ) ;
#line 1696 "syntax4.c"
			}
			/* END OF ACTION: exp_assign */
		}
		break;
	default:
		{
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

			ZR921 (*ZI1013, &ZI963);
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
			ZR953 (&ZI951, &ZIe);
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
#line 366 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 1744 "syntax4.c"
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
#line 458 "syntax.act"

    /* op will be in its primary form */
    (ZIe) = make_become_exp ( (ZIop), (*ZI1013), (ZIb) ) ;
#line 1759 "syntax4.c"
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
ZR760(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255:
		{
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
#line 432 "syntax.act"

    (ZIe) = NULL_exp ;
#line 1802 "syntax4.c"
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
ZRmultiplicative_Hexpression(EXP *ZO920)
{
	EXP ZI920;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		EXP ZIe;

		ZRcast_Hexpression (&ZIe);
		ZR921 (ZIe, &ZI920);
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
	*ZO920 = ZI920;
}

void
ZR761(int *ZOell)
{
	int ZIell;

	switch (CURRENT_TERMINAL) {
	case 2: case 25: case 47: case 94:
	case 97: case 98: case 102: case 104:
	case 105: case 106: case 110: case 111:
	case 112: case 114: case 115: case 117:
	case 118: case 120: case 121: case 122:
	case 123: case 124: case 137: case 156:
	case 185: case 286: case 299:
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
#line 1403 "syntax.act"
 (ZIell) = 0 ; 
#line 1871 "syntax4.c"
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

/* BEGINNING OF TRAILER */

#line 1483 "syntax.act"

#line 1891 "syntax4.c"

/* END OF FILE */
