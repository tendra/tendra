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


#line 110 "syntax4.c"

void
ZR1194(EXP ZI1192, EXP *ZO1193)
{
	EXP ZI1193;

ZL2_1194:;
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_log_or */
			{
#line 718 "syntax.act"

    (ZIe) = make_log_or_exp ( (ZI1192), (ZIb) ) ;
#line 147 "syntax4.c"
			}
			/* END OF ACTION: exp_log_or */
			/* BEGINNING OF INLINE: 1194 */
			ZI1192 = ZIe;
			goto ZL2_1194;
			/* END OF INLINE: 1194 */
		}
		/*UNREACHED*/
	default:
		{
			ZI1193 = ZI1192;
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
	*ZO1193 = ZI1193;
}

void
ZR1322(int *ZOop)
{
	int ZIop;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		/* BEGINNING OF ACTION: is_array */
		{
#line 2111 "syntax.act"

    /* Resolve 'operator new []' from 'operator new [3]' */
    (ZI0) = predict_array () ;
#line 187 "syntax4.c"
		}
		/* END OF ACTION: is_array */
		if (!ZI0)
			goto ZL2;
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
		ZRclose_Hsquare_Hx ();
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: lex_new_array */
		{
#line 403 "syntax.act"
 (ZIop) = lex_new_Harray ; 
#line 214 "syntax4.c"
		}
		/* END OF ACTION: lex_new_array */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: lex_new */
			{
#line 401 "syntax.act"
 (ZIop) = lex_new ; 
#line 228 "syntax4.c"
			}
			/* END OF ACTION: lex_new */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOop = ZIop;
}

void
ZRcast_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 398 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 257 "syntax4.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 83:
		{
			ADVANCE_LEXER;
			ZR1286 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 23:
		{
			EXP ZI1281;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 357 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 289 "syntax4.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR1242 (ZI1281, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 371 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 319 "syntax4.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 327 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 334 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 343 "syntax4.c"
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
#line 369 "syntax4.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1284, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1273;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_const_cast */
			{
#line 630 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 398 "syntax4.c"
			}
			/* END OF ACTION: exp_const_cast */
			ZR1242 (ZI1273, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 206:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 690 "syntax.act"

    (ZIe) = make_cast_exp ( type_void, (ZIa), 0 ) ;
#line 423 "syntax4.c"
			}
			/* END OF ACTION: exp_ignore */
		}
		break;
	case 132:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1276;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_dynamic_cast */
			{
#line 656 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 447 "syntax4.c"
			}
			/* END OF ACTION: exp_dynamic_cast */
			ZR1242 (ZI1276, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 210:
		{
			EXP ZI1279;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 660 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 467 "syntax4.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR1242 (ZI1279, &ZIe);
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
#line 486 "syntax4.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1269 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 255:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 706 "syntax.act"

    (ZIe) = make_lit_exp ( (ZIa) ) ;
#line 512 "syntax4.c"
			}
			/* END OF ACTION: exp_lit */
		}
		break;
	case 61:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 787 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_minus_Hminus, (ZIa) ) ;
#line 532 "syntax4.c"
			}
			/* END OF ACTION: exp_predec */
		}
		break;
	case 8:
		{
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: nested-name */
			{
#line 264 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 546 "syntax4.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1268 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 65:
		{
			ADVANCE_LEXER;
			ZR1288 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 71:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 791 "syntax.act"

    (ZIe) = make_prefix_exp ( lex_plus_Hplus, (ZIa) ) ;
#line 582 "syntax4.c"
			}
			/* END OF ACTION: exp_preinc */
		}
		break;
	case 145:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1274;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_reinterpret_cast */
			{
#line 804 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 606 "syntax4.c"
			}
			/* END OF ACTION: exp_reinterpret_cast */
			ZR1242 (ZI1274, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 116:
		{
			int ZIop;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 405 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 625 "syntax4.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZIop, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 698 "syntax.act"

    (ZIe) = make_indir_exp ( (ZIa) ) ;
#line 650 "syntax4.c"
			}
			/* END OF ACTION: exp_indir */
		}
		break;
	case 146:
		{
			TYPE ZIt;
			EXP ZIa;
			int ZIn;
			EXP ZI1275;

			ADVANCE_LEXER;
			ZRcast_Hoperand (&ZIt, &ZIa, &ZIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_static_cast */
			{
#line 829 "syntax.act"

    (ZI1275) = make_static_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 673 "syntax4.c"
			}
			/* END OF ACTION: exp_static_cast */
			ZR1242 (ZI1275, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 148:
		{
			EXP ZI1278;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 833 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 693 "syntax4.c"
			}
			/* END OF ACTION: exp_this */
			ZR1242 (ZI1278, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 152:
		{
			int ZIop;
			EXP ZI1272;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 406 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 713 "syntax4.c"
			}
			/* END OF ACTION: lex_typeid */
			ZRtypeid_Hexpression (ZIop, &ZI1272);
			ZR1242 (ZI1272, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 330:
		{
			int ZIop;
			EXP ZI1271;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 407 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 734 "syntax4.c"
			}
			/* END OF ACTION: lex_vtable */
			ZRtypeid_Hexpression (ZIop, &ZI1271);
			ZR1242 (ZI1271, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 33:
		{
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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 799 "syntax.act"

    (ZIe) = make_ref_exp ( (ZIa), 0 ) ;
#line 772 "syntax4.c"
			}
			/* END OF ACTION: exp_ref */
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
#line 800 "syntax4.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 807 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 816 "syntax4.c"
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
#line 842 "syntax4.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1282, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 17: case 18: case 19: case 20:
	case 21: case 22: case 135: case 150:
		{
			EXP ZI1277;

			ZRliteral (&ZI1277);
			ZR1242 (ZI1277, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 62:
		{
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
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 758 "syntax.act"

    (ZIe) = make_not_exp ( (ZIa) ) ;
#line 892 "syntax4.c"
			}
			/* END OF ACTION: exp_not */
		}
		break;
	case 1: case 3: case 5: case 6:
	case 141:
		{
			IDENTIFIER ZIid;
			EXP ZI1285;

			ZRunqualified_Hid (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 913 "syntax4.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR1242 (ZI1285, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 7:
		{
			IDENTIFIER ZIid;
			TYPE ZI1267;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv;
			TYPE ZIt;
			SID_LIST_EXP ZIp;
			EXP ZI1283;

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
#line 945 "syntax4.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 952 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 959 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 968 "syntax4.c"
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
#line 994 "syntax4.c"
			}
			/* END OF ACTION: exp_func_cast */
			ZR1242 (ZI1283, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 131: case 140:
		{
			int ZIb;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIb) = 0 ; 
#line 1012 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
			ZR1432 (&ZIb, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 43: case 59: case 69: case 85:
		{
			int ZIop;
			EXP ZIa;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 391 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 1031 "syntax4.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 857 "syntax.act"

    (ZIe) = make_uminus_exp ( (ZIop), (ZIa) ) ;
#line 1045 "syntax4.c"
			}
			/* END OF ACTION: exp_unary */
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
ZRtype_Hspecifier(TYPE ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 104:
		{
			ADVANCE_LEXER;
			ZR1327 (&ZIs, &ZIbt, &ZIt, &ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 153:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1092 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRany_Hnested_Hname_Hopt (&ZIns);
			ZRany_Hclass_Hname (&ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_typename */
			{
#line 1302 "syntax.act"

    (ZIt) = make_typename ( (ZIns), (ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
	found_elaborate_type = 1 ;
    }
    have_type_specifier = 1 ;
#line 1111 "syntax4.c"
			}
			/* END OF ACTION: type_typename */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1118 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1125 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 118: case 121: case 129:
		{
			BASE_TYPE ZIkey;

			ZRclass_Hkey (&ZIkey);
			ZR1326 (&ZIs, &ZIkey, &ZIbt, &ZIt, &ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 98: case 124:
		{
			ZRcv_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1153 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1161 "syntax4.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 2: case 7: case 8: case 9:
	case 25: case 83: case 97: case 102:
	case 106: case 110: case 111: case 114:
	case 115: case 122: case 123: case 127:
	case 156: case 185: case 286: case 299:
		{
			ZRsimple_Htype_Hspecifier (&ZIbt, &ZIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1181 "syntax4.c"
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
}

void
ZRparameter_Hdeclaration_Hclause(int *ZOell)
{
	int ZIell;

	switch (CURRENT_TERMINAL) {
	case 2: case 7: case 8: case 9:
	case 25: case 47: case 83: case 94:
	case 97: case 98: case 102: case 104:
	case 105: case 106: case 110: case 111:
	case 112: case 114: case 115: case 117:
	case 118: case 120: case 121: case 122:
	case 123: case 124: case 127: case 129:
	case 133: case 136: case 137: case 138:
	case 153: case 155: case 156: case 185:
	case 275: case 286: case 299:
		{
			ZRparameter_Hdeclaration_Hlist (&ZIell);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIell) = 0 ; 
#line 1231 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
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
	*ZOell = ZIell;
}

void
ZRabstract_Hdeclarator_Hopt(TYPE ZIp, TYPE *ZOt)
{
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 10: case 11: case 33: case 65:
	case 66: case 78: case 332:
		{
			TYPE ZIq;

			ZRabstract_Hdeclarator_Haux (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIp) : inject_pre_type ( (ZIq), (ZIp), 1 ) ) ;
#line 1268 "syntax4.c"
			}
			/* END OF ACTION: type_inject */
		}
		break;
	default:
		{
			ZIt = ZIp;
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
	*ZOt = ZIt;
}

void
ZR1323(int *ZOop)
{
	int ZIop;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		/* BEGINNING OF ACTION: is_array */
		{
#line 2111 "syntax.act"

    /* Resolve 'operator new []' from 'operator new [3]' */
    (ZI0) = predict_array () ;
#line 1304 "syntax4.c"
		}
		/* END OF ACTION: is_array */
		if (!ZI0)
			goto ZL2;
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
		ZRclose_Hsquare_Hx ();
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: lex_delete_array */
		{
#line 404 "syntax.act"
 (ZIop) = lex_delete_Harray ; 
#line 1331 "syntax4.c"
		}
		/* END OF ACTION: lex_delete_array */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: lex_delete */
			{
#line 402 "syntax.act"
 (ZIop) = lex_delete ; 
#line 1345 "syntax4.c"
			}
			/* END OF ACTION: lex_delete */
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOop = ZIop;
}

void
ZRopen_Hround_Hx(void)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 65:
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

		/* BEGINNING OF ACTION: lex_open_round */
		{
#line 396 "syntax.act"
 (ZIt) = lex_open_Hround ; 
#line 1383 "syntax4.c"
		}
		/* END OF ACTION: lex_open_round */
		/* BEGINNING OF ACTION: expected */
		{
#line 1997 "syntax.act"

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZIt) ) report ( crt_loc, ERR_lex_expect ( (ZIt) ) ) ;
#line 1393 "syntax4.c"
		}
		/* END OF ACTION: expected */
	}
}

void
ZR1198(EXP ZI1196, EXP *ZO1197)
{
	EXP ZI1197;

ZL2_1198:;
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_log_and */
			{
#line 714 "syntax.act"

    (ZIe) = make_log_and_exp ( (ZI1196), (ZIb) ) ;
#line 1434 "syntax4.c"
			}
			/* END OF ACTION: exp_log_and */
			/* BEGINNING OF INLINE: 1198 */
			ZI1196 = ZIe;
			goto ZL2_1198;
			/* END OF INLINE: 1198 */
		}
		/*UNREACHED*/
	default:
		{
			ZI1197 = ZI1196;
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
	*ZO1197 = ZI1197;
}

void
ZRenumerator_Hlist(IDENTIFIER ZIe)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_enumerator_Hlist:;
	{
		ZRenumerator_Hdefinition (ZIe);
		/* BEGINNING OF INLINE: 869 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 1391 */
					{
						switch (CURRENT_TERMINAL) {
						case 42:
							{
								ADVANCE_LEXER;
								/* BEGINNING OF ACTION: error_comma */
								{
#line 1987 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 1486 "syntax4.c"
								}
								/* END OF ACTION: error_comma */
								/* BEGINNING OF INLINE: enumerator-list */
								goto ZL2_enumerator_Hlist;
								/* END OF INLINE: enumerator-list */
							}
							/*UNREACHED*/
						case 1: case 2: case 3: case 4:
							{
								/* BEGINNING OF INLINE: enumerator-list */
								goto ZL2_enumerator_Hlist;
								/* END OF INLINE: enumerator-list */
							}
							/*UNREACHED*/
						default:
							{
								/* BEGINNING OF ACTION: error_comma */
								{
#line 1987 "syntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 1509 "syntax4.c"
								}
								/* END OF ACTION: error_comma */
							}
							break;
						}
					}
					/* END OF INLINE: 1391 */
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 869 */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1326(TYPE *ZIs, BASE_TYPE *ZIkey, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZIid;
		QUALIFIER ZIqu;
		int ZIi;
		DECL_SPEC ZIb;
		IDENTIFIER ZIp;
		int ZIf;
		int ZI1324;
		DECL_SPEC ZIds;
		TYPE ZI1325;
		IDENTIFIER ZIc;

		/* BEGINNING OF ACTION: is_class_spec */
		{
#line 2069 "syntax.act"

    /* Resolve class-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 1 ) ;
#line 1562 "syntax4.c"
		}
		/* END OF ACTION: is_class_spec */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1572 "syntax4.c"
		}
		/* END OF ACTION: declarator_start */
		ZR871 (&ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: qual_get */
		{
#line 538 "syntax.act"

    (ZIqu) = crt_id_qualifier ;
    (ZIi) = crt_templ_qualifier ;
#line 1586 "syntax4.c"
		}
		/* END OF ACTION: qual_get */
		/* BEGINNING OF ACTION: template_decl */
		{
#line 1866 "syntax.act"

    if ( !IS_NULL_type ( (*ZIs) ) ) template_decl ( (*ZIs) ) ;
#line 1594 "syntax4.c"
		}
		/* END OF ACTION: template_decl */
		/* BEGINNING OF ACTION: access_get */
		{
#line 1455 "syntax.act"
 (ZIb) = crt_access ; 
#line 1601 "syntax4.c"
		}
		/* END OF ACTION: access_get */
		/* BEGINNING OF ACTION: type_class_begin */
		{
#line 1499 "syntax.act"

    IDENTIFIER id = constr_name ( last_namespace, (ZIid) ) ;
    (ZIp) = begin_class_defn ( id, (*ZIkey), cinfo_none, (*ZIs) ) ;
    (ZIf) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
#line 1615 "syntax4.c"
		}
		/* END OF ACTION: type_class_begin */
		ZRbase_Hclause_Hopt (&ZI1324);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: class_base_end */
		{
#line 1520 "syntax.act"

    end_base_class ( crt_class, (ZI1324) ) ;
#line 1628 "syntax4.c"
		}
		/* END OF ACTION: class_base_end */
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1635 "syntax4.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZI1325) = NULL_type ;
#line 1643 "syntax4.c"
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
		ZRmember_Hspecification_Hopt (ZI1325, ZIds);
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
		/* BEGINNING OF ACTION: access_check_class */
		{
#line 1469 "syntax.act"

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
#line 1685 "syntax4.c"
		}
		/* END OF ACTION: access_check_class */
		/* BEGINNING OF ACTION: type_class_end */
		{
#line 1509 "syntax.act"

    (ZIc) = end_class_defn ( (ZIp) ) ;
    in_function_defn = (ZIf) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
#line 1696 "syntax4.c"
		}
		/* END OF ACTION: type_class_end */
		/* BEGINNING OF ACTION: access_set */
		{
#line 1456 "syntax.act"
 crt_access = (ZIb) ; 
#line 1703 "syntax4.c"
		}
		/* END OF ACTION: access_set */
		/* BEGINNING OF ACTION: qual_set */
		{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIqu) ;
    crt_templ_qualifier = (ZIi) ;
#line 1712 "syntax4.c"
		}
		/* END OF ACTION: qual_set */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 1720 "syntax4.c"
		}
		/* END OF ACTION: rescan_token */
		/* BEGINNING OF ACTION: type_name */
		{
#line 1287 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIc) ) ;
    have_type_specifier = 1 ;
#line 1730 "syntax4.c"
		}
		/* END OF ACTION: type_name */
		/* BEGINNING OF ACTION: btype_none */
		{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1737 "syntax4.c"
		}
		/* END OF ACTION: btype_none */
		/* BEGINNING OF ACTION: cv_none */
		{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1744 "syntax4.c"
		}
		/* END OF ACTION: cv_none */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
		{
			NAMESPACE ZIns;
			IDENTIFIER ZIaid;
			IDENTIFIER ZIid;

			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 1764 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
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
#line 1779 "syntax4.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_elaborate */
			{
#line 1293 "syntax.act"

    MAKE_type_pre ( cv_none, (*ZIkey), crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
#line 1792 "syntax4.c"
			}
			/* END OF ACTION: type_elaborate */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 1799 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 1806 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRfor_Hinit_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2086 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 1845 "syntax4.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1854 "syntax4.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 1862 "syntax4.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hbasic (ZIt, ZIds);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIa) = NULL_exp ;
#line 1875 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 931 "syntax.act"

    (ZIe) = (ZIa) ;
    in_declaration-- ;
#line 1884 "syntax4.c"
		}
		/* END OF ACTION: stmt_decl */
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
	case 77: case 78: case 83: case 85:
	case 97: case 102: case 106: case 110:
	case 111: case 114: case 115: case 116:
	case 122: case 123: case 127: case 130:
	case 131: case 132: case 135: case 140:
	case 141: case 145: case 146: case 148:
	case 149: case 150: case 152: case 156:
	case 170: case 185: case 206: case 210:
	case 255: case 286: case 298: case 299:
	case 324: case 330: case 346:
		{
			ZRexpression_Hstatement (&ZIe);
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
ZRfunction_Htry_Hblock(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIr;
		EXP ZIa;
		EXP ZIb;
		EXP ZIf;
		EXP ZIc;
		EXP ZId;

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
#line 1963 "syntax4.c"
		}
		/* END OF ACTION: reach_check */
		/* BEGINNING OF ACTION: stmt_try_func */
		{
#line 1043 "syntax.act"

    (ZIa) = begin_try_stmt ( 1 ) ;
#line 1971 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_func */
		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 907 "syntax.act"

    (ZIb) = begin_compound_stmt ( 1 ) ;
#line 1979 "syntax4.c"
		}
		/* END OF ACTION: stmt_compound_begin */
		/* BEGINNING OF ACTION: stmt_try_inject */
		{
#line 1047 "syntax.act"

    inject_try_stmt ( (ZIa) ) ;
#line 1987 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_inject */
		ZRfunction_Hbody (ZIb, &ZIf);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 923 "syntax.act"

    (ZIc) = end_compound_stmt ( (ZIf) ) ;
#line 2000 "syntax4.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: stmt_try_cont */
		{
#line 1051 "syntax.act"

    (ZId) = cont_try_stmt ( (ZIa), (ZIc) ) ;
#line 2008 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_cont */
		ZRhandler_Hseq_Hopt (ZId);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 1134 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 2020 "syntax4.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_try_end */
		{
#line 1055 "syntax.act"

    (ZIe) = end_try_stmt ( (ZId), 0 ) ;
#line 2028 "syntax4.c"
		}
		/* END OF ACTION: stmt_try_end */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRdesignator(OFFSET ZIb, TYPE ZIs, OFFSET *ZOa, TYPE *ZOt)
{
	OFFSET ZIa;
	TYPE ZIt;

	switch (CURRENT_TERMINAL) {
	case 46:
		{
			ADVANCE_LEXER;
			ZRmember_Hdesignator (ZIb, ZIs, &ZIa, &ZIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			ZRconstant_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: offset_index */
			{
#line 1886 "syntax.act"

    OFFSET off = offset_index ( (ZIs), (ZIe), &(ZIt) ) ;
    (ZIa) = offset_add ( (ZIb), off ) ;
#line 2085 "syntax4.c"
			}
			/* END OF ACTION: offset_index */
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
	*ZOa = ZIa;
	*ZOt = ZIt;
}

void
ZR1327(TYPE *ZIs, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZIid;
		QUALIFIER ZIqu;
		int ZIi;
		IDENTIFIER ZIp;
		IDENTIFIER ZIe;

		/* BEGINNING OF ACTION: is_enum_spec */
		{
#line 2091 "syntax.act"

    /* Resolve enum-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 0 ) ;
#line 2140 "syntax4.c"
		}
		/* END OF ACTION: is_enum_spec */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: declarator_start */
		{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2150 "syntax4.c"
		}
		/* END OF ACTION: declarator_start */
		ZR871 (&ZIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: qual_get */
		{
#line 538 "syntax.act"

    (ZIqu) = crt_id_qualifier ;
    (ZIi) = crt_templ_qualifier ;
#line 2164 "syntax4.c"
		}
		/* END OF ACTION: qual_get */
		/* BEGINNING OF ACTION: type_enum_begin */
		{
#line 1524 "syntax.act"

    IDENTIFIER id = constr_name ( last_namespace, (ZIid) ) ;
    (ZIp) = begin_enum_defn ( id, (*ZIs) ) ;
    no_type_defns++ ;
#line 2174 "syntax4.c"
		}
		/* END OF ACTION: type_enum_begin */
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
		/* BEGINNING OF INLINE: 872 */
		{
			switch (CURRENT_TERMINAL) {
			case 1: case 2: case 3: case 4:
				{
					ZRenumerator_Hlist (ZIp);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 872 */
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
		/* BEGINNING OF ACTION: access_check */
		{
#line 1462 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
#line 2227 "syntax4.c"
		}
		/* END OF ACTION: access_check */
		/* BEGINNING OF ACTION: type_enum_end */
		{
#line 1530 "syntax.act"

    (ZIe) = end_enum_defn ( (ZIp) ) ;
#line 2235 "syntax4.c"
		}
		/* END OF ACTION: type_enum_end */
		/* BEGINNING OF ACTION: qual_set */
		{
#line 543 "syntax.act"

    crt_id_qualifier = (ZIqu) ;
    crt_templ_qualifier = (ZIi) ;
#line 2244 "syntax4.c"
		}
		/* END OF ACTION: qual_set */
		/* BEGINNING OF ACTION: type_name */
		{
#line 1287 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIe) ) ;
    have_type_specifier = 1 ;
#line 2254 "syntax4.c"
		}
		/* END OF ACTION: type_name */
		/* BEGINNING OF ACTION: btype_none */
		{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2261 "syntax4.c"
		}
		/* END OF ACTION: btype_none */
		/* BEGINNING OF ACTION: cv_none */
		{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2268 "syntax4.c"
		}
		/* END OF ACTION: cv_none */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
		{
			BASE_TYPE ZIkey;
			NAMESPACE ZIns;
			IDENTIFIER ZIaid;
			IDENTIFIER ZIid;

			/* BEGINNING OF ACTION: key_enum */
			{
#line 1439 "syntax.act"
 (ZIkey) = btype_enum ; 
#line 2288 "syntax4.c"
			}
			/* END OF ACTION: key_enum */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2296 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
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
#line 2311 "syntax4.c"
			}
			/* END OF ACTION: namespace_id */
			/* BEGINNING OF ACTION: type_elaborate */
			{
#line 1293 "syntax.act"

    MAKE_type_pre ( cv_none, (ZIkey), crt_id_qualifier, (ZIt) ) ;
    COPY_id ( type_name ( (ZIt) ), (ZIid) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
#line 2324 "syntax4.c"
			}
			/* END OF ACTION: type_elaborate */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2331 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2338 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
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
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRrelational_Hexpression(EXP *ZO1221)
{
	EXP ZI1221;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRshift_Hexpression (&ZIe);
		ZR1222 (ZIe, &ZI1221);
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
	*ZO1221 = ZI1221;
}

void
ZRmember_Hdeclaration(TYPE ZIt, DECL_SPEC ZIds)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
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
#line 2405 "syntax4.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
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
#line 2424 "syntax4.c"
		}
		/* END OF ACTION: dspec_join */
		ZR1341 (&ZIt, &ZIbt, &ZIt1, &ZIcv1, &ZIds2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 134: case 147:
		{
			ZRtemplate_Hmember_Hdecl (ZIt, ZIds);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
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
#line 2468 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2476 "syntax4.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2483 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1546 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 2490 "syntax4.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 2501 "syntax4.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1573 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 2512 "syntax4.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 2520 "syntax4.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1482 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 2528 "syntax4.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIf) = 1 ; 
#line 2535 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 2543 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRmember_Hdeclarator (ZIds3, ZIt3, ZIbt, ZIr, ZIf, &ZId);
			ZR1094 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1861 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 2562 "syntax4.c"
			}
			/* END OF ACTION: template_check */
			ZRusing_Hdeclaration ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 77:
		{
			TYPE ZIt1;
			BASE_TYPE ZIbt;
			CV_SPEC ZIcv1;

			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 2583 "syntax4.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 2590 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 2597 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: declare_member_empty */
			{
#line 1673 "syntax.act"

    IGNORE empty_decl ( (ZIds), (ZIt), (ZIbt), (ZIt1), (ZIcv1), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
#line 2608 "syntax4.c"
			}
			/* END OF ACTION: declare_member_empty */
			ADVANCE_LEXER;
		}
		break;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
}

void
ZR1328(int *ZOt)
{
	int ZIt;

	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
	case 7: case 8: case 9: case 83:
	case 142: case 143: case 144: case 155:
		{
			ZRbase_Hspecifier_Hlist ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIt) = 1 ; 
#line 2643 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIt) = 0 ; 
#line 2654 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
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
	*ZOt = ZIt;
}

void
ZRfor_Hend_Hstatement(EXP *ZOe)
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
			EXP ZIa;
			EXP ZIb;

			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIb) = make_exp_stmt ( (ZIa) ) ;
#line 2706 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 1087 "syntax.act"

    (ZIe) = bind_temporary ( (ZIb) ) ;
#line 2714 "syntax4.c"
			}
			/* END OF ACTION: bind_temporary */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 2726 "syntax4.c"
			}
			/* END OF ACTION: exp_none */
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
ZR1329(int *ZOv)
{
	int ZIv;

	switch (CURRENT_TERMINAL) {
	case 155:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 2052 "syntax.act"
 (ZIv) = 1 ; 
#line 2755 "syntax4.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIv) = 0 ; 
#line 2766 "syntax4.c"
			}
			/* END OF ACTION: bool_false */
		}
		break;
	case 355:
		return;
	}
	*ZOv = ZIv;
}

void
ZR1202(EXP ZI1200, EXP *ZO1201)
{
	EXP ZI1201;

ZL2_1202:;
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_or */
			{
#line 762 "syntax.act"

    (ZIe) = make_or_exp ( (ZI1200), (ZIb) ) ;
#line 2812 "syntax4.c"
			}
			/* END OF ACTION: exp_or */
			/* BEGINNING OF INLINE: 1202 */
			ZI1200 = ZIe;
			goto ZL2_1202;
			/* END OF INLINE: 1202 */
		}
		/*UNREACHED*/
	default:
		{
			ZI1201 = ZI1200;
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
	*ZO1201 = ZI1201;
}

void
ZRnew_Htype_Hid(TYPE *ZOt, int *ZOn)
{
	TYPE ZIt;
	int ZIn;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIn1;
		BASE_TYPE ZIbt;
		TYPE ZIp;
		CV_SPEC ZIcv;
		TYPE ZIs;
		TYPE ZIq;

		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 2016 "syntax.act"

    (ZIn1) = no_type_defns ;
#line 2859 "syntax4.c"
		}
		/* END OF ACTION: no_type_defns */
		ZRtype_Hspecifier_Hseq (&ZIbt, &ZIp, &ZIcv);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_complete */
		{
#line 1323 "syntax.act"

    (ZIs) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 2873 "syntax4.c"
		}
		/* END OF ACTION: type_complete */
		ZRnew_Hdeclarator_Hopt (&ZIq);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_inject */
		{
#line 1395 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZIq) ) ? (ZIs) : inject_pre_type ( (ZIq), (ZIs), 1 ) ) ;
#line 2886 "syntax4.c"
		}
		/* END OF ACTION: type_inject */
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 2024 "syntax.act"

    (ZIn) = no_type_defns - (ZIn1) ;
#line 2894 "syntax4.c"
		}
		/* END OF ACTION: diff_type_defns */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOn = ZIn;
}

void
ZRand_Hexpression(EXP *ZO1209)
{
	EXP ZI1209;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRmaxmin_Hexpression (&ZIe);
		ZR1210 (ZIe, &ZI1209);
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
	*ZO1209 = ZI1209;
}

void
ZR1330(DECL_SPEC *ZOa)
{
	DECL_SPEC ZIa;

	switch (CURRENT_TERMINAL) {
	case 142: case 143: case 144:
		{
			ZRaccess_Hspecifier (&ZIa);
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
#line 2954 "syntax4.c"
			}
			/* END OF ACTION: access_none */
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
	*ZOa = ZIa;
}

void
parse_exp(EXP *ZOe)
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
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1982 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 2996 "syntax4.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3004 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZR1077(BASE_TYPE *ZIbt, DECL_SPEC *ZIds3, TYPE *ZIt3, ACCESS_LIST *ZIr, int *ZIc, IDENTIFIER *ZId)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIb;
		EXP ZIe;

		/* BEGINNING OF ACTION: is_function */
		{
#line 2074 "syntax.act"

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
#line 3028 "syntax4.c"
		}
		/* END OF ACTION: is_function */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: initialiser_bad */
		{
#line 1776 "syntax.act"

    if ( (*ZIc) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
#line 3038 "syntax4.c"
		}
		/* END OF ACTION: initialiser_bad */
		/* BEGINNING OF ACTION: access_free */
		{
#line 1486 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3046 "syntax4.c"
		}
		/* END OF ACTION: access_free */
		/* BEGINNING OF ACTION: function_begin */
		{
#line 1152 "syntax.act"

    (ZIb) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (*ZId) ) ;
#line 3058 "syntax4.c"
		}
		/* END OF ACTION: function_begin */
		ZRfunction_Hdefinition_Hbody (&ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: function_end */
		{
#line 1160 "syntax.act"

    IGNORE end_function ( (*ZId), (ZIe) ) ;
    in_class_defn = (ZIb) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
#line 3074 "syntax4.c"
		}
		/* END OF ACTION: function_end */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1713 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3082 "syntax4.c"
		}
		/* END OF ACTION: declarator_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 2149 "syntax.act"

    RESCAN_LEXER ;
#line 3090 "syntax4.c"
		}
		/* END OF ACTION: rescan_token */
		goto ZL0;
	}
	/*UNREACHED*/
ZL2:;
	{
		SID_LIST_EXP ZIp;
		EXP ZIe;

		/* BEGINNING OF ACTION: is_true */
		{
#line 2064 "syntax.act"

    (ZI0) = (*ZIc) ;
#line 3106 "syntax4.c"
		}
		/* END OF ACTION: is_true */
		if (!ZI0)
			goto ZL3;
		/* BEGINNING OF ACTION: rescan_init */
		{
#line 2161 "syntax.act"

    if ( crt_lex_token == lex_open_Hinit ) {
	crt_lex_token = lex_open_Hround ;
    } else {
	RESCAN_LEXER ;
    }
#line 3120 "syntax4.c"
		}
		/* END OF ACTION: rescan_init */
		ZRinitialiser_Hexp_Hlist (*ZId, &ZIp);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_initialiser */
		{
#line 702 "syntax.act"

    MAKE_exp_initialiser ( type_void, (ZIp), NULL_list ( OFFSET ), 0, 0, 0, (ZIe) ) ;
#line 3133 "syntax4.c"
		}
		/* END OF ACTION: exp_initialiser */
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: initialise_id */
		{
#line 1762 "syntax.act"

    int def = init_object ( (*ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (*ZId), &decl_loc, def ) ;
#line 3149 "syntax4.c"
		}
		/* END OF ACTION: initialise_id */
		/* BEGINNING OF ACTION: access_check_decl */
		{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZId) ) ;
    }
#line 3159 "syntax4.c"
		}
		/* END OF ACTION: access_check_decl */
		/* BEGINNING OF ACTION: declarator_end */
		{
#line 1713 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3167 "syntax4.c"
		}
		/* END OF ACTION: declarator_end */
		ZR1078 (ZIbt, ZIds3, ZIt3, ZIr);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: access_free */
		{
#line 1486 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3180 "syntax4.c"
		}
		/* END OF ACTION: access_free */
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
ZL3:;
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			EXP ZIe;

			ADVANCE_LEXER;
			ZRinitialiser_Hclause (*ZId, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_id */
			{
#line 1762 "syntax.act"

    int def = init_object ( (*ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (*ZId), &decl_loc, def ) ;
#line 3211 "syntax4.c"
			}
			/* END OF ACTION: initialise_id */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZId) ) ;
    }
#line 3221 "syntax4.c"
			}
			/* END OF ACTION: access_check_decl */
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1713 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3229 "syntax4.c"
			}
			/* END OF ACTION: declarator_end */
			ZR1078 (ZIbt, ZIds3, ZIt3, ZIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_free */
			{
#line 1486 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3242 "syntax4.c"
			}
			/* END OF ACTION: access_free */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 42: case 77:
		{
			EXP ZIe;

			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3263 "syntax4.c"
			}
			/* END OF ACTION: exp_none */
			/* BEGINNING OF ACTION: initialise_id */
			{
#line 1762 "syntax.act"

    int def = init_object ( (*ZId), (ZIe) ) ;
    if ( do_dump ) dump_declare ( (*ZId), &decl_loc, def ) ;
#line 3272 "syntax4.c"
			}
			/* END OF ACTION: initialise_id */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZId) ) ;
    }
#line 3282 "syntax4.c"
			}
			/* END OF ACTION: access_check_decl */
			/* BEGINNING OF ACTION: declarator_end */
			{
#line 1713 "syntax.act"

    end_declarator ( (*ZId), 1 ) ;
#line 3290 "syntax4.c"
			}
			/* END OF ACTION: declarator_end */
			ZR1078 (ZIbt, ZIds3, ZIt3, ZIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: access_free */
			{
#line 1486 "syntax.act"

    free_access ( &(*ZIr) ) ;
#line 3303 "syntax4.c"
			}
			/* END OF ACTION: access_free */
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
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
}

void
ZRdeclaration_Hnonempty(TYPE ZIt, DECL_SPEC ZIds, EXP *ZOe)
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
#line 3350 "syntax4.c"
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
#line 3369 "syntax4.c"
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
#line 3382 "syntax4.c"
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
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 3431 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 1278 "syntax.act"

    (ZIt1) = NULL_type ;
#line 3439 "syntax4.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv1) = cv_none ; 
#line 3446 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: dspec_none */
			{
#line 1546 "syntax.act"
 (ZIds1) = dspec_none ; 
#line 3453 "syntax4.c"
			}
			/* END OF ACTION: dspec_none */
			/* BEGINNING OF ACTION: dspec_join */
			{
#line 1562 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZIds) & (ZIds1) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds2) = ( (ZIds) | (ZIds1) ) ;
#line 3464 "syntax4.c"
			}
			/* END OF ACTION: dspec_join */
			/* BEGINNING OF ACTION: dspec_complete */
			{
#line 1573 "syntax.act"

    /* Complete a declaration specifier and a type */
    (ZIds3) = complete_dspec ( (ZIds2), (ZIbt), (ZIt1), (ZIcv1) ) ;
    (ZIt2) = complete_pre_type ( (ZIbt), (ZIt1), (ZIcv1), 0 ) ;
    have_type_specifier = 0 ;
#line 3475 "syntax4.c"
			}
			/* END OF ACTION: dspec_complete */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1395 "syntax.act"

    (ZIt3) = ( IS_NULL_type ( (ZIt) ) ? (ZIt2) : inject_pre_type ( (ZIt), (ZIt2), 1 ) ) ;
#line 3483 "syntax4.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: access_return */
			{
#line 1482 "syntax.act"

    save_access ( &(ZIr) ) ;
#line 3491 "syntax4.c"
			}
			/* END OF ACTION: access_return */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3499 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRdeclarator (ZIt3, &ZIs, &ZIid, &ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declare_id */
			{
#line 1610 "syntax.act"

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
#line 3529 "syntax4.c"
			}
			/* END OF ACTION: declare_id */
			/* BEGINNING OF ACTION: access_check_ret */
			{
#line 1478 "syntax.act"

    IGNORE clear_access ( (ZId), &(ZIr) ) ;
#line 3537 "syntax4.c"
			}
			/* END OF ACTION: access_check_ret */
			/* BEGINNING OF ACTION: access_check_decl */
			{
#line 1473 "syntax.act"

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZId) ) ;
    }
#line 3547 "syntax4.c"
			}
			/* END OF ACTION: access_check_decl */
			ZR1077 (&ZIbt, &ZIds3, &ZIt3, &ZIr, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_none */
			{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 3560 "syntax4.c"
			}
			/* END OF ACTION: exp_none */
		}
		break;
	case 126: case 139: case 154:
		{
			/* BEGINNING OF ACTION: template_check */
			{
#line 1861 "syntax.act"

    if ( !IS_NULL_type ( (ZIt) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZIds) ) ;
#line 3573 "syntax4.c"
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
ZR1078(BASE_TYPE *ZIbt, DECL_SPEC *ZIds3, TYPE *ZIt3, ACCESS_LIST *ZIr)
{
	switch (CURRENT_TERMINAL) {
	case 42:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 1706 "syntax.act"

    crt_templ_qualifier = 0 ;
#line 3606 "syntax4.c"
			}
			/* END OF ACTION: declarator_start */
			ZRinit_Hdeclarator_Hlist (*ZIds3, *ZIbt, *ZIt3, *ZIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRthrow_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIa;

		switch (CURRENT_TERMINAL) {
		case 149:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 638 */
		{
			{
				TYPE ZIt;
				int ZIn;

				/* BEGINNING OF ACTION: is_type_id_false */
				{
#line 2116 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 3657 "syntax4.c"
				}
				/* END OF ACTION: is_type_id_false */
				if (!ZI0)
					goto ZL3;
				ZRtype_Hid (&ZIt, &ZIn);
				if ((CURRENT_TERMINAL) == 355) {
					RESTORE_LEXER;
					goto ZL1;
				}
				/* BEGINNING OF ACTION: exp_throw_type */
				{
#line 841 "syntax.act"

    (ZIa) = make_throw_arg ( (ZIt), (ZIn) ) ;
#line 3672 "syntax4.c"
				}
				/* END OF ACTION: exp_throw_type */
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
			case 286: case 299: case 330:
				{
					ZRassignment_Hexpression (&ZIa);
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

    (ZIa) = NULL_exp ;
#line 3710 "syntax4.c"
					}
					/* END OF ACTION: exp_none */
				}
				break;
			}
		ZL2:;
		}
		/* END OF INLINE: 638 */
		/* BEGINNING OF ACTION: exp_throw */
		{
#line 837 "syntax.act"

    (ZIe) = make_throw_exp ( (ZIa), 1 ) ;
#line 3724 "syntax4.c"
		}
		/* END OF ACTION: exp_throw */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1206(EXP ZI1204, EXP *ZO1205)
{
	EXP ZI1205;

ZL2_1206:;
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_xor */
			{
#line 865 "syntax.act"

    (ZIe) = make_xor_exp ( (ZI1204), (ZIb) ) ;
#line 3771 "syntax4.c"
			}
			/* END OF ACTION: exp_xor */
			/* BEGINNING OF INLINE: 1206 */
			ZI1204 = ZIe;
			goto ZL2_1206;
			/* END OF INLINE: 1206 */
		}
		/*UNREACHED*/
	default:
		{
			ZI1205 = ZI1204;
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
	*ZO1205 = ZI1205;
}

void
parse_stmt(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 2086 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
#line 3817 "syntax4.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1546 "syntax.act"
 (ZIds) = dspec_none ; 
#line 3826 "syntax4.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 1278 "syntax.act"

    (ZIt) = NULL_type ;
#line 3834 "syntax4.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hnonempty (ZIt, ZIds, &ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 931 "syntax.act"

    (ZIe) = (ZIa) ;
    in_declaration-- ;
#line 3848 "syntax4.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3856 "syntax4.c"
		}
		/* END OF ACTION: stmt_label_clear */
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 398 "syntax.act"
 (ZIop) = lex_alignof ; 
#line 3889 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 3924 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 3932 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 3940 "syntax4.c"
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
	case 83:
		{
			ADVANCE_LEXER;
			ZR1477 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 357 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 3990 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4026 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4034 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4042 "syntax4.c"
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
#line 364 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIa = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 4066 "syntax4.c"
			}
			/* END OF EXTRACT: complex-stmt */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4075 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: complex-type */
			{
#line 371 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
#line 4115 "syntax4.c"
			}
			/* END OF EXTRACT: complex-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 4123 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 4130 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 4139 "syntax4.c"
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
#line 4165 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4200 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4208 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4216 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 4263 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4298 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4306 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4314 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: destructor-name */
			{
#line 235 "syntax.act"

    ZIuid = crt_token->pp_data.id.use ;
#line 4353 "syntax4.c"
			}
			/* END OF EXTRACT: destructor-name */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 4364 "syntax4.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 4372 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4407 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4415 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4423 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 4466 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4500 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4508 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4516 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 4563 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4598 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4606 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4614 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 660 "syntax.act"

    (ZI1279) = make_ellipsis_exp () ;
#line 4652 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4687 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4695 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4703 "syntax4.c"
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
	case 9:
		{
			NAMESPACE ZIns;

			/* BEGINNING OF EXTRACT: full-name */
			{
#line 268 "syntax.act"

    ZIns = crt_token->pp_data.ns ;
#line 4724 "syntax4.c"
			}
			/* END OF EXTRACT: full-name */
			ADVANCE_LEXER;
			ZR1476 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1:
		{
			IDENTIFIER ZI1467;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZI1467 = crt_token->pp_data.id.use ;
#line 4744 "syntax4.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZR1472 (&ZI1467, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 346:
		{
			ADVANCE_LEXER;
			ZR1441 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

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
#line 4796 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4830 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4838 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4846 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 4889 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 4923 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4931 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 4939 "syntax4.c"
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
	case 3:
		{
			IDENTIFIER ZI1471;

			/* BEGINNING OF EXTRACT: namespace-name */
			{
#line 227 "syntax.act"

    ZI1471 = crt_token->pp_data.id.use ;
#line 4960 "syntax4.c"
			}
			/* END OF EXTRACT: namespace-name */
			ADVANCE_LEXER;
			ZR1472 (&ZI1471, &ZIe);
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
#line 4980 "syntax4.c"
			}
			/* END OF EXTRACT: nested-name */
			ADVANCE_LEXER;
			ZR1475 (&ZIns, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5043 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5051 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5059 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 5102 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5136 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5144 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5152 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 5199 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5234 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5242 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5250 "syntax4.c"
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
#line 879 "syntax.act"

    (ZIe) = NULL_exp ;
#line 5270 "syntax4.c"
			}
			/* END OF ACTION: stmt_none */
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 405 "syntax.act"
 (ZIop) = lex_sizeof ; 
#line 5300 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5335 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5343 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5351 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 5394 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5428 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5436 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5444 "syntax4.c"
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
			IDENTIFIER ZI1473;

			/* BEGINNING OF EXTRACT: statement-name */
			{
#line 231 "syntax.act"

    ZI1473 = crt_token->pp_data.id.use ;
#line 5465 "syntax4.c"
			}
			/* END OF EXTRACT: statement-name */
			ADVANCE_LEXER;
			ZR1474 (&ZI1473, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

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
#line 5510 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5545 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5553 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5561 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: template-id */
			{
#line 241 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZIuid = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5604 "syntax4.c"
			}
			/* END OF EXTRACT: template-id */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_complex */
			{
#line 515 "syntax.act"

    (ZIid) = check_id ( NULL_nspace, (ZIuid), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5615 "syntax4.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 5623 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5658 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5666 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5674 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF EXTRACT: template-type */
			{
#line 249 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZItid = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
#line 5722 "syntax4.c"
			}
			/* END OF EXTRACT: template-type */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: namespace_simple */
			{
#line 509 "syntax.act"

    (ZIid) = (ZItid) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
#line 5733 "syntax4.c"
			}
			/* END OF ACTION: namespace_simple */
			/* BEGINNING OF ACTION: type_name */
			{
#line 1287 "syntax.act"

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZIid) ) ;
    have_type_specifier = 1 ;
#line 5743 "syntax4.c"
			}
			/* END OF ACTION: type_name */
			/* BEGINNING OF ACTION: btype_none */
			{
#line 1254 "syntax.act"
 (ZIbt) = btype_none ; 
#line 5750 "syntax4.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 5757 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 5766 "syntax4.c"
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
#line 5792 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5827 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5835 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5843 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_this */
			{
#line 833 "syntax.act"

    (ZI1278) = make_this_exp () ;
#line 5881 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 5916 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 5924 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 5932 "syntax4.c"
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
	case 2:
		{
			IDENTIFIER ZI1469;

			/* BEGINNING OF EXTRACT: type-name */
			{
#line 223 "syntax.act"

    ZI1469 = crt_token->pp_data.id.use ;
#line 5953 "syntax4.c"
			}
			/* END OF EXTRACT: type-name */
			ADVANCE_LEXER;
			ZR1470 (&ZI1469, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_typeid */
			{
#line 406 "syntax.act"
 (ZIop) = lex_typeid ; 
#line 5990 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6026 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6034 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6042 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_vtable */
			{
#line 407 "syntax.act"
 (ZIop) = lex_vtable ; 
#line 6080 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6116 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6124 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6132 "syntax4.c"
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
			ZRcast_Hexpression (&ZI1460);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 799 "syntax.act"

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
#line 6187 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6221 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6229 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6237 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 6288 "syntax4.c"
			}
			/* END OF ACTION: type_pre */
			/* BEGINNING OF ACTION: cv_none */
			{
#line 1222 "syntax.act"
 (ZIcv) = cv_none ; 
#line 6295 "syntax4.c"
			}
			/* END OF ACTION: cv_none */
			/* BEGINNING OF ACTION: type_complete */
			{
#line 1323 "syntax.act"

    (ZIt) = complete_pre_type ( (ZIbt), (ZI1267), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 6304 "syntax4.c"
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
#line 6330 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6365 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6373 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6381 "syntax4.c"
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
	case 64:
		{
			ZRcompound_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 289: case 323:
		{
			ZRcontrol_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 96: case 100: case 223:
		{
			ZRfall_Hcheck ();
			ZR1442 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 298: case 324:
		{
			EXP ZI1436;
			EXP ZIa;
			int ZIr;

			ZRflow_Hexpression (&ZI1436);
			ZR1438 (&ZI1436, &ZIa);
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
#line 6446 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6454 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6462 "syntax4.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 95: case 99: case 108: case 113:
		{
			ZRjump_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6546 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6554 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6562 "syntax4.c"
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
			ZRcast_Hexpression (&ZI1461);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 758 "syntax.act"

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
#line 6617 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6651 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6659 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6667 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

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
#line 6713 "syntax4.c"
			}
			/* END OF ACTION: namespace_complex */
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 686 "syntax.act"

    (ZI1285) = make_id_exp ( (ZIid) ) ;
#line 6721 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6756 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6764 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6772 "syntax4.c"
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
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 149:
		{
			EXP ZI1289;
			EXP ZIa;
			int ZIr;

			ZRthrow_Hexpression (&ZI1289);
			ZR1291 (&ZI1289, &ZIa);
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
#line 6818 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6826 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6834 "syntax4.c"
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
	case 151:
		{
			ZRtry_Hblock (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: bool_false */
			{
#line 2051 "syntax.act"
 (ZIb) = 0 ; 
#line 6879 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 6914 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 6922 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 6930 "syntax4.c"
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
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 391 "syntax.act"
 (ZIop) = crt_lex_token ; 
#line 6967 "syntax4.c"
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
#line 6981 "syntax4.c"
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
			ZR1291 (&ZI1289, &ZIa);
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
#line 7015 "syntax4.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 952 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 7023 "syntax4.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 1020 "syntax.act"

    unreached_fall = 1 ;
#line 7031 "syntax4.c"
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
#line 7057 "syntax4.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 581 "syntax.act"

    (ZIe) = NULL_exp ;
#line 7065 "syntax4.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
