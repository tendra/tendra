/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/producers/cpp/syntax/syntax.sid
 * and
 *	/u/g/release/Source/src/producers/cpp/syntax/syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT

/*
    		 Crown Copyright (c) 1997, 1998
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


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
    COMPOUND TYPE ALIASES

    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;
typedef LIST ( TYPE ) SID_LIST_TYPE ;


/*
    FUNCTION DECLARATIONS

    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include "syntax.h"


/*
    COMPILATION MODE

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



void
ZR500 PROTO_N ((ZO497))
  PROTO_T (SID_LIST_EXP *ZO497)
{
    SID_LIST_EXP ZI497;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 8: case 9: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 25: case 33: case 43: case 59: case 61:
      case 62: case 65: case 69: case 71: case 78:
      case 83: case 85: case 97: case 102: case 106:
      case 110: case 111: case 114: case 115: case 116:
      case 122: case 123: case 127: case 130: case 131:
      case 132: case 135: case 140: case 141: case 145:
      case 146: case 148: case 149: case 150: case 152:
      case 156: case 170: case 184: case 205: case 209:
      case 285: case 298: case 329:
	{
	    ZR498 (&ZI497);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI497) = NULL_list ( EXP ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO497 = ZI497;
}

void
ZR1216 PROTO_N ((ZI1214, ZO1215))
  PROTO_T (EXP ZI1214 X EXP *ZO1215)
{
    EXP ZI1215;

  ZL2_1216:;
    switch (CURRENT_TERMINAL) {
      case 48: case 63:
	{
	    int ZI450;
	    EXP ZI456;
	    EXP ZI431;

	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR616 ();
	    ZR614 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI431) = make_equality_exp ( (ZI450), (ZI1214), (ZI456) ) ;
	    }
	    ZI1214 = ZI431;
	    goto ZL2_1216;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1215 = ZI1214;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1215 = ZI1215;
}

void
ZR628 PROTO_N ((ZO1195))
  PROTO_T (EXP *ZO1195)
{
    EXP ZI1195;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR626 (&ZI431);
	ZR1196 (ZI431, &ZI1195);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1195 = ZI1195;
}

void
ZR752 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 95:
	{
	    int ZI670;

	    ADVANCE_LEXER;
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI431) = make_break_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR418 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 99:
	{
	    int ZI670;

	    ADVANCE_LEXER;
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI431) = make_continue_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR418 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 108:
	{
	    int ZI670;

	    ADVANCE_LEXER;
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR751 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR418 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 113:
	{
	    int ZI670;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1: case 2: case 3: case 5: case 6:
		  case 7: case 8: case 9: case 17: case 18:
		  case 19: case 20: case 21: case 22: case 23:
		  case 25: case 33: case 43: case 59: case 61:
		  case 62: case 65: case 69: case 71: case 78:
		  case 83: case 85: case 97: case 102: case 106:
		  case 110: case 111: case 114: case 115: case 116:
		  case 122: case 123: case 127: case 130: case 131:
		  case 132: case 135: case 140: case 141: case 145:
		  case 146: case 148: case 149: case 150: case 152:
		  case 156: case 170: case 184: case 205: case 209:
		  case 285: case 297: case 298: case 323: case 329:
		  case 345:
		    {
			ZR491 (&ZI493);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZI493) = NULL_exp ;
			}
		    }
		    break;
		}
	    }
	    {

    (ZI431) = make_return_stmt ( (ZI493), lex_return ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR418 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1471 PROTO_N ((ZI1470, ZO431))
  PROTO_T (IDENTIFIER *ZI1470 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    IDENTIFIER ZI419;
	    EXP ZI493;

	    {

    (ZI419) = (*ZI1470) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI493) = make_id_exp ( (ZI419) ) ;
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	}
	break;
      case 41:
	{
	    EXP ZI493;
	    EXP ZI456;

	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI493) = begin_label_stmt ( (*ZI1470), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR661 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_label_stmt ( (ZI493), (ZI456) ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1344 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI1341;
	    IDENTIFIER ZI460;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1341 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1341 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI460) = check_id ( (*ZI425), (ZI1341), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = constr_name ( last_namespace, (ZI460) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;

	    ZR475 (*ZI425, &ZI480);
	    ZR476 (*ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR552 PROTO_N ((ZO414, ZO431, ZO551))
  PROTO_T (TYPE *ZO414 X EXP *ZO431 X int *ZO551)
{
    TYPE ZI414;
    EXP ZI431;
    int ZI551;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 53:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR548 (&ZI414, &ZI551);
	switch (CURRENT_TERMINAL) {
	  case 49:
	    break;
	  case 354:
	    RESTORE_LEXER;
	    goto ZL1;
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
	ZR491 (&ZI431);
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  case 354:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
    *ZO431 = ZI431;
    *ZO551 = ZI551;
}

void
ZR698 PROTO_N ((ZO1185, ZO1186, ZO1187))
  PROTO_T (EXP *ZO1185 X EXP *ZO1186 X int *ZO1187)
{
    EXP ZI1185;
    EXP ZI1186;
    int ZI1187;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI558;
	EXP ZI497;
	int ZI670;
	EXP ZI493;
	EXP ZI431;

	switch (CURRENT_TERMINAL) {
	  case 26:
	    {

    ZI558 = crt_token->pp_data.exp ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZI558), c ) ;
    (ZI497) = c ;
	}
	{

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	}
	ZR678 (&ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI670) ; 
	}
	{

    (ZI431) = begin_hash_if_stmt ( (ZI558), (ZI493) ) ;
	}
	ZR1188 (ZI431, ZI497, ZI670, &ZI1185, &ZI1186, &ZI1187);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1185 = ZI1185;
    *ZO1186 = ZI1186;
    *ZO1187 = ZI1187;
}

void
ZR785 PROTO_N ((ZO783))
  PROTO_T (CV_SPEC *ZO783)
{
    CV_SPEC ZI783;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	CV_SPEC ZI493;

	ZR784 (&ZI493);
	{
	    switch (CURRENT_TERMINAL) {
	      case 98: case 124:
		{
		    CV_SPEC ZI456;

		    ZR785 (&ZI456);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    CV_SPEC c = ( (ZI493) & (ZI456) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI783) = ( (ZI493) | (ZI456) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI783 = ZI493;
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO783 = ZI783;
}

void
ZR1599 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    unreached_fall = 0 ;
	    }
	}
	break;
      default:
	{
	    {

    unreached_fall = 0 ;
	    }
	}
	break;
      case 354:
	return;
    }
}

void
ZR1472 PROTO_N ((ZI425, ZO431))
  PROTO_T (NAMESPACE *ZI425 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI493;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	    {

    (ZI493) = make_id_exp ( (ZI419) ) ;
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 141: case 147:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ZR1266 (ZI425, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1345 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI1342;
	    IDENTIFIER ZI460;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1342 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1342 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI460) = check_id ( (*ZI425), (ZI1342), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = constr_name ( last_namespace, (ZI460) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;

	    ZR475 (*ZI425, &ZI480);
	    ZR476 (*ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1022 PROTO_N ((ZI558, ZO431))
  PROTO_T (EXP ZI558 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI456;
	EXP ZI459;
	EXP ZI493;

	ZR1019 (ZI558, &ZI456, &ZI459);
	{
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	{

    COPY_int ( exp_sequence_block ( (ZI456) ), 2 ) ;
	}
	ZR676 (ZI456, &ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI431) = ctor_postlude ( (ZI493), (ZI459) ) ;
	}
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
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1473 PROTO_N ((ZI425, ZO431))
  PROTO_T (NAMESPACE *ZI425 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI493;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	    {

    (ZI493) = make_id_exp ( (ZI419) ) ;
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 141: case 147:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ZR1267 (ZI425, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1346 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;
	    NAMESPACE ZI425;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI478), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI1343;
	    NAMESPACE ZI425;
	    IDENTIFIER ZI460;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1343 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1343 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    {

    (ZI460) = check_id ( (ZI425), (ZI1343), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	    {

    (ZI419) = constr_name ( last_namespace, (ZI460) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI425;
	    int ZI480;
	    IDENTIFIER ZI478;

	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    ZR475 (ZI425, &ZI480);
	    ZR476 (ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI478), (ZI480) ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1092 PROTO_N ((ZI511, ZI1073, ZI1074, ZI670, ZI459))
  PROTO_T (BASE_TYPE *ZI511 X DECL_SPEC *ZI1073 X TYPE *ZI1074 X ACCESS_LIST *ZI670 X IDENTIFIER *ZI459)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	{

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    free_access ( &(*ZI670) ) ;
	}
	{

    skip_function ( (*ZI459) ) ;
	}
	{

    end_declarator ( (*ZI459), 1 ) ;
	}
	{

    RESCAN_LEXER ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    int ZI551;

	    ADVANCE_LEXER;
	    {

    end_declarator ( (*ZI459), 1 ) ;
	    }
	    {
 (ZI551) = 0 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1087 (*ZI1073, *ZI1074, *ZI511, *ZI670, ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI670) ) ;
	    }
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
	    {

    free_access ( &(*ZI670) ) ;
	    }
	    {

    end_declarator ( (*ZI459), 1 ) ;
	    }
	}
	break;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
}

void
ZR1474 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;
	    NAMESPACE ZI425;
	    IDENTIFIER ZI419;
	    EXP ZI493;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI478), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	    {

    (ZI493) = make_id_exp ( (ZI419) ) ;
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 131: case 140: case 141: case 147:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ZR1284 (&ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1220 PROTO_N ((ZI1218, ZO1219))
  PROTO_T (EXP ZI1218 X EXP *ZO1219)
{
    EXP ZI1219;

  ZL2_1220:;
    switch (CURRENT_TERMINAL) {
      case 49: case 50: case 53: case 54:
	{
	    int ZI450;
	    EXP ZI456;
	    EXP ZI431;

	    {
 (ZI450) = crt_lex_token ; 
	    }
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
	    ZR611 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI431) = make_relation_exp ( (ZI450), (ZI1218), (ZI456) ) ;
	    }
	    ZI1218 = ZI431;
	    goto ZL2_1220;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1219 = ZI1218;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1219 = ZI1219;
}

void
ZR788 PROTO_N ((ZO783))
  PROTO_T (CV_SPEC *ZO783)
{
    CV_SPEC ZI783;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR785 (&ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI783) = cv_none ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO783 = ZI783;
}

void
ZR1602 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI460;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI460 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI460 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI460), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;

	    ZR475 (*ZI425, &ZI480);
	    ZR476 (*ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR712 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI459;
	EXP ZI493;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    begin_cond () ;
	}
	ZR1096 (&ZI459);
	switch (CURRENT_TERMINAL) {
	  case 36:
	    break;
	  case 354:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR649 (&ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	}
	{

    int def = init_object ( (ZI459), (ZI493) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	}
	{

    end_declarator ( (ZI459), 1 ) ;
	}
	{

    (ZI431) = end_cond () ;
    in_declaration-- ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 8: case 9: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 25: case 33: case 43: case 59: case 61:
      case 62: case 65: case 69: case 71: case 78:
      case 83: case 85: case 97: case 102: case 106:
      case 110: case 111: case 114: case 115: case 116:
      case 122: case 123: case 127: case 130: case 131:
      case 132: case 135: case 140: case 141: case 145:
      case 146: case 148: case 149: case 150: case 152:
      case 156: case 170: case 184: case 205: case 209:
      case 285: case 297: case 298: case 323: case 329:
      case 345:
	{
	    ZR491 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
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
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1603 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI460;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI460 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI460 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI460), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;

	    ZR475 (*ZI425, &ZI480);
	    ZR476 (*ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1604 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI478;
	    NAMESPACE ZI425;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI478), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    NAMESPACE ZI425;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI460 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI460 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI460), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI425;
	    int ZI480;
	    IDENTIFIER ZI478;

	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	    ZR475 (ZI425, &ZI480);
	    ZR476 (ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI478), (ZI480) ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR847 PROTO_N ((ZO414))
  PROTO_T (int *ZO414)
{
    int ZI414;

    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    ADVANCE_LEXER;
	    ZR1326 (&ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI414) = 1 ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
}

void
ZR990 PROTO_N ((ZO1148))
  PROTO_T (TYPE *ZO1148)
{
    TYPE ZI1148;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI493;
	EXP ZI431;
	TYPE ZI414;

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
	ZR491 (&ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI431) = convert_reference ( (ZI493), REF_NORMAL ) ;
    (ZI431) = convert_lvalue ( (ZI431) ) ;
	}
	{

    /* First array bound in a new-declarator */
    NAT n = make_new_array_dim ( (ZI431) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI414) ) ;
	}
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
	ZR1149 (ZI414, &ZI1148);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1148 = ZI1148;
}

void
ZR1224 PROTO_N ((ZI1222, ZO1223))
  PROTO_T (EXP ZI1222 X EXP *ZO1223)
{
    EXP ZI1223;

  ZL2_1224:;
    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR608 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_shift_exp ( lex_lshift, (ZI1222), (ZI456) ) ;
	    }
	    ZI1222 = ZI431;
	    goto ZL2_1224;
	}
	/*UNREACHED*/
      case 75:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR608 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_shift_exp ( lex_rshift, (ZI1222), (ZI456) ) ;
	    }
	    ZI1222 = ZI431;
	    goto ZL2_1224;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1223 = ZI1222;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1223 = ZI1223;
}

void
ZR427 PROTO_N ((ZO425))
  PROTO_T (NAMESPACE *ZO425)
{
    NAMESPACE ZI425;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    {

    (ZI425) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI425) ;
	    }
	}
	break;
      case 8: case 9:
	{
	    ZR426 (&ZI425);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO425 = ZI425;
}

void
ZR662 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 222:
	{
	    ADVANCE_LEXER;
	    ZR1599 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR784 PROTO_N ((ZO783))
  PROTO_T (CV_SPEC *ZO783)
{
    CV_SPEC ZI783;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (ZI783) = cv_const ; 
	    }
	}
	break;
      case 124:
	{
	    ADVANCE_LEXER;
	    {
 (ZI783) = cv_volatile ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO783 = ZI783;
}

void
ZR835 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI497;

	ZR834 (&ZI497);
	{
	    switch (CURRENT_TERMINAL) {
	      case 28:
		{
		    ADVANCE_LEXER;
		    {

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
		    }
		    {

    target_decl ( lex_else, NULL_exp ) ;
		    }
		    ZR833 ();
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	{

    crt_hash_cond = (ZI497) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    target_decl ( lex_endif, NULL_exp ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR596 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 85:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 59:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 69:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 43:
	{
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
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1084 PROTO_N ((ZI689, ZI497, ZI480, ZI670, ZI720, ZO459))
  PROTO_T (DECL_SPEC ZI689 X TYPE ZI497 X BASE_TYPE ZI480 X ACCESS_LIST ZI670 X int ZI720 X IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR1346 (&ZI1353);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 5:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1353) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1345 (&ZI425, &ZI1353);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1360;
	    IDENTIFIER ZI1361;

	    {

    ZI1360 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1361) = (ZI1360) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1365 (&ZI689, &ZI497, &ZI480, &ZI670, &ZI720, &ZI1361, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 3:
	{
	    IDENTIFIER ZI1363;
	    IDENTIFIER ZI1364;

	    {

    ZI1363 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1364) = (ZI1363) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1365 (&ZI689, &ZI497, &ZI480, &ZI670, &ZI720, &ZI1364, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1344 (&ZI425, &ZI1353);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 65:
	{
	    TYPE ZI1350;
	    IDENTIFIER ZI1351;
	    int ZI1352;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR940 (&ZI1350, &ZI1351, &ZI1352);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZI1352) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    if ( IS_NULL_type ( (ZI1350) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1177 (ZI1350, ZI1351, ZI1352, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 4:
	{
	    IDENTIFIER ZI1357;
	    IDENTIFIER ZI1358;

	    {

    ZI1357 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1358) = (ZI1357) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1365 (&ZI689, &ZI497, &ZI480, &ZI670, &ZI720, &ZI1358, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI478 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1353) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 7:
	{
	    IDENTIFIER ZI1356;
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1356 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI460) = (ZI1356) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1353) = constr_name ( last_namespace, (ZI460) ) ;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI1366;
	    IDENTIFIER ZI1367;

	    {

    ZI1366 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1367) = (ZI1366) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1368 (&ZI689, &ZI497, &ZI480, &ZI670, &ZI720, &ZI1367, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 141:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    parse_operator (&ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1353) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI1348;
	    TYPE ZI1349;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI1347;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    ZR926 (&ZI1348);
	    ZR940 (&ZI1349, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1347) = ( IS_NULL_type ( (ZI1349) ) ? (ZI1348) : inject_pre_type ( (ZI1349), (ZI1348), 0 ) ) ;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (ZI497) : inject_pre_type ( (ZI1347), (ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 41:
	{
	    IDENTIFIER ZI419;
	    QUALIFIER ZI455;
	    int ZI456;
	    EXP ZI558;
	    TYPE ZI414;

	    {

    HASHID nm = lookup_anon () ;
    (ZI419) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	    }
	    {

    begin_declarator ( (ZI419), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	    }
	    ADVANCE_LEXER;
	    ZR651 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZI419) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI414) = make_bitfield_type ( (ZI497), (ZI480), (ZI558), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( (ZI689), (ZI414), (ZI419), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZI459) = id ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO459 = ZI459;
}

void
ZR428 PROTO_N ((ZO425))
  PROTO_T (NAMESPACE *ZO425)
{
    NAMESPACE ZI425;

    switch (CURRENT_TERMINAL) {
      case 8: case 9: case 83:
	{
	    ZR427 (&ZI425);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI425) = NULL_nspace ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO425 = ZI425;
}

void
ZR1228 PROTO_N ((ZI1226, ZO1227))
  PROTO_T (EXP ZI1226 X EXP *ZO1227)
{
    EXP ZI1227;

  ZL2_1228:;
    switch (CURRENT_TERMINAL) {
      case 59:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR605 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_minus_exp ( (ZI1226), (ZI456) ) ;
	    }
	    ZI1226 = ZI431;
	    goto ZL2_1228;
	}
	/*UNREACHED*/
      case 69:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR605 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_plus_exp ( (ZI1226), (ZI456) ) ;
	    }
	    ZI1226 = ZI431;
	    goto ZL2_1228;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1227 = ZI1226;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1227 = ZI1227;
}

void
ZR998 PROTO_N ((ZI459, ZO431))
  PROTO_T (IDENTIFIER ZI459 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 8: case 9: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 25: case 33: case 43: case 59: case 61:
      case 62: case 65: case 69: case 71: case 78:
      case 83: case 85: case 97: case 102: case 106:
      case 110: case 111: case 114: case 115: case 116:
      case 122: case 123: case 127: case 130: case 131:
      case 132: case 135: case 140: case 141: case 145:
      case 146: case 148: case 149: case 150: case 152:
      case 156: case 170: case 184: case 205: case 209:
      case 285: case 298: case 329:
	{
	    ZR649 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 64:
	{
	    SID_LIST_EXP ZI497;

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
	    ZR1001 (&ZI459, &ZI497);
	    {
		if ((CURRENT_TERMINAL) == 354) {
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
	    {

    /* The expression type is a dummy */
    MAKE_exp_aggregate ( type_void, (ZI497), NULL_list ( OFFSET ), (ZI431) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1089 PROTO_N ((ZI414, ZI689))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI714;
	TOKEN ZI497;
	TYPE ZI875;

	ZR1110 (&ZI714);
	switch (CURRENT_TERMINAL) {
	  case 147:
	    break;
	  case 354:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZI497) = template_params ( (ZI714) ) ;
    RESCAN_LEXER ;
	}
	{

    (ZI875) = make_template_type ( (ZI497), (ZI414) ) ;
	}
	ZR838 (ZI875, ZI689);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    end_template ( (ZI497) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR608 PROTO_N ((ZO1227))
  PROTO_T (EXP *ZO1227)
{
    EXP ZI1227;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR605 (&ZI431);
	ZR1228 (ZI431, &ZI1227);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1227 = ZI1227;
}

void
ZR949 PROTO_N ((ZO1174, ZO1175, ZO1176))
  PROTO_T (TYPE *ZO1174 X IDENTIFIER *ZO1175 X int *ZO1176)
{
    TYPE ZI1174;
    IDENTIFIER ZI1175;
    int ZI1176;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI414;
	    IDENTIFIER ZI419;
	    int ZI558;

	    ADVANCE_LEXER;
	    ZR940 (&ZI414, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    if ( IS_NULL_type ( (ZI414) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1177 (ZI414, ZI419, ZI558, &ZI1174, &ZI1175, &ZI1176);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 83:
      case 141:
	{
	    IDENTIFIER ZI419;
	    TYPE ZI414;
	    int ZI558;

	    ZR942 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = NULL_type ;
	    }
	    {
 (ZI558) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI419), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI414, ZI419, ZI558, &ZI1174, &ZI1175, &ZI1176);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1174 = ZI1174;
    *ZO1175 = ZI1175;
    *ZO1176 = ZI1176;
}

void
ZR713 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 109:
	{
	    unsigned ZI714;
	    int ZI670;
	    EXP ZI558;
	    EXP ZI493;
	    EXP ZI715;
	    EXP ZI716;
	    EXP ZI456;
	    EXP ZI459;
	    EXP ZI720;

	    ADVANCE_LEXER;
	    {
 (ZI714) = crt_condition ; 
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR417 ();
	    ZR712 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = begin_if_stmt ( (ZI558) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI715) = begin_compound_stmt ( 1 ) ;
	    }
	    {

    (ZI716) = inject_cond ( (ZI715), (ZI558) ) ;
	    }
	    ZR681 (ZI716, &ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI459) = cont_if_stmt ( (ZI493), (ZI456) ) ;
	    }
	    {
		{
		    EXP ZI718;
		    EXP ZI719;

		    switch (CURRENT_TERMINAL) {
		      case 103:
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

    check_empty_stmt ( lex_else ) ;
		    }
		    {

    (ZI718) = begin_compound_stmt ( 1 ) ;
		    }
		    {

    (ZI719) = inject_cond ( (ZI718), (ZI558) ) ;
		    }
		    ZR681 (ZI719, &ZI720);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    report ( crt_loc, ERR_stmt_if_no_else () ) ;
    (ZI720) = NULL_exp ;
		    }
		}
	      ZL2:;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI431) = end_if_stmt ( (ZI459), (ZI720) ) ;
	    }
	    {
 crt_condition = (ZI714) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 119:
	{
	    int ZI670;
	    EXP ZI558;
	    EXP ZI493;
	    int ZI722;
	    EXP ZI715;
	    EXP ZI716;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR712 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = begin_switch_stmt ( (ZI558) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 216:
		    {
			ADVANCE_LEXER;
			{
 (ZI722) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI722) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI715) = begin_compound_stmt ( 1 ) ;
	    }
	    {

    (ZI716) = inject_cond ( (ZI715), (ZI558) ) ;
	    }
	    ZR681 (ZI716, &ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI431) = end_switch_stmt ( (ZI493), (ZI456), (ZI722) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 26:
	{
	    ZR699 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR491 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 8: case 9: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 25: case 33: case 43: case 59: case 61:
      case 62: case 65: case 69: case 71: case 78:
      case 83: case 85: case 97: case 102: case 106:
      case 110: case 111: case 114: case 115: case 116:
      case 122: case 123: case 127: case 130: case 131:
      case 132: case 135: case 140: case 141: case 145:
      case 146: case 148: case 149: case 150: case 152:
      case 156: case 170: case 184: case 205: case 209:
      case 285: case 298: case 329:
	{
	    EXP ZI1287;

	    ZR496 (&ZI1287);
	    ZR1289 (&ZI1287, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 297: case 323:
	{
	    EXP ZI493;
	    SID_LIST_EXP ZI480;
	    SID_LIST_EXP ZI497;

	    ZR643 (&ZI493);
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI493), (ZI480), (ZI497) ) ;
	    }
	    {

    (ZI431) = make_comma_exp ( (ZI497) ) ;
	    }
	}
	break;
      case 345:
	{
	    EXP ZI493;
	    SID_LIST_EXP ZI480;
	    SID_LIST_EXP ZI497;

	    ZR644 (&ZI493);
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI493), (ZI480), (ZI497) ) ;
	    }
	    {

    (ZI431) = make_comma_exp ( (ZI497) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR571 PROTO_N ((ZO497, ZO414, ZO551))
  PROTO_T (SID_LIST_EXP *ZO497 X TYPE *ZO414 X int *ZO551)
{
    SID_LIST_EXP ZI497;
    TYPE ZI414;
    int ZI551;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    {
		{
		    {

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
		    }
		    if (!ZI0)
			goto ZL3;
		    ZR548 (&ZI414, &ZI551);
		    switch (CURRENT_TERMINAL) {
		      case 39:
			break;
		      case 354:
			RESTORE_LEXER;
			goto ZL1;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    {

    (ZI497) = NULL_list ( EXP ) ;
		    }
		    goto ZL2;
		}
		/*UNREACHED*/
	      ZL3:;
		switch (CURRENT_TERMINAL) {
		  case 1: case 2: case 3: case 5: case 6:
		  case 7: case 8: case 9: case 17: case 18:
		  case 19: case 20: case 21: case 22: case 23:
		  case 25: case 33: case 43: case 59: case 61:
		  case 62: case 65: case 69: case 71: case 78:
		  case 83: case 85: case 97: case 102: case 106:
		  case 110: case 111: case 114: case 115: case 116:
		  case 122: case 123: case 127: case 130: case 131:
		  case 132: case 135: case 140: case 141: case 145:
		  case 146: case 148: case 149: case 150: case 152:
		  case 156: case 170: case 184: case 205: case 209:
		  case 285: case 298: case 329:
		    {
			int ZI457;
			TYPE ZI574;
			int ZI575;

			ZR498 (&ZI497);
			switch (CURRENT_TERMINAL) {
			  case 39:
			    break;
			  case 354:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    (ZI457) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
			}
			{
			    switch (CURRENT_TERMINAL) {
			      case 65:
				{
				    ADVANCE_LEXER;
				    ZR548 (&ZI574, &ZI575);
				    switch (CURRENT_TERMINAL) {
				      case 39:
					break;
				      case 354:
					RESTORE_LEXER;
					goto ZL1;
				      default:
					goto ZL1;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 2: case 7: case 8: case 9: case 25:
			      case 83: case 97: case 98: case 102: case 104:
			      case 106: case 110: case 111: case 114: case 115:
			      case 118: case 121: case 122: case 123: case 124:
			      case 127: case 129: case 153: case 156: case 184:
			      case 285: case 298:
				{
				    ZR568 (&ZI574, &ZI575);
				    if ((CURRENT_TERMINAL) == 354) {
					RESTORE_LEXER;
					goto ZL1;
				    }
				}
				break;
			      default:
				goto ZL1;
			    }
			}
			{

    have_type_declaration = (ZI457) ;
			}
			ZI414 = ZI574;
			ZI551 = ZI575;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	      ZL2:;
	    }
	}
	break;
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 98: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 124:
      case 127: case 129: case 153: case 156: case 184:
      case 285: case 298:
	{
	    ZR568 (&ZI414, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI497) = NULL_list ( EXP ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO497 = ZI497;
    *ZO414 = ZI414;
    *ZO551 = ZI551;
}

void
ZR676 PROTO_N ((ZI558, ZO431))
  PROTO_T (EXP ZI558 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_676:;
    {
	DECL_SPEC ZI689;
	TYPE ZI414;
	EXP ZI1478;
	EXP ZI493;
	EXP ZI456;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL3;
	{
 (ZI689) = dspec_none ; 
	}
	{

    (ZI414) = NULL_type ;
	}
	ZR687 (ZI414, ZI689, &ZI1478);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI493) = (ZI1478) ;
    in_declaration-- ;
	}
	{

    unreached_fall = 1 ;
	}
	{

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	}
	ZI558 = ZI456;
	goto ZL2_676;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI450;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1488;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_alignof ; 
	    }
	    ZR593 (ZI450, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1488);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1488) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 83:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR1474 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 23:
	{
	    EXP ZI1279;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1498;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1279 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1240 (ZI1279, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1498);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1498) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 24:
	{
	    EXP ZI1476;
	    EXP ZI493;
	    EXP ZI456;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1476 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI493) = make_exp_stmt ( (ZI1476) ) ;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 25:
	{
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1282;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1500;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1265 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	    {

    (ZI414) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR500 (&ZI497);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1282) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI1282, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1500);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1500) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 130:
	{
	    TYPE ZI414;
	    EXP ZI1460;
	    int ZI551;
	    EXP ZI1271;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1491;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1460, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1271) = make_const_cast_exp ( (ZI414), (ZI1460), (ZI551) ) ;
	    }
	    ZR1240 (ZI1271, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1491);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1491) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 5:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1504;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1504);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1504) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 205:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1480;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1453);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_cast_exp ( type_void, (ZI1453), 0 ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1480) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 132:
	{
	    TYPE ZI414;
	    EXP ZI1463;
	    int ZI551;
	    EXP ZI1274;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1494;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1463, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_dynamic_cast_exp ( (ZI414), (ZI1463), (ZI551) ) ;
	    }
	    ZR1240 (ZI1274, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1494);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1494) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 209:
	{
	    EXP ZI1277;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1497;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {

    (ZI1277) = make_ellipsis_exp () ;
	    }
	    ZR1240 (ZI1277, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1497);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1497) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 9:
	{
	    NAMESPACE ZI425;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1473 (&ZI425, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 1:
	{
	    IDENTIFIER ZI1464;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI1464 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1469 (&ZI1464, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 345:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR1439 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 61:
	{
	    EXP ZI1455;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1482;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_prefix_exp ( lex_minus_Hminus, (ZI1455) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1482);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1482) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 3:
	{
	    IDENTIFIER ZI1468;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI1468 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1469 (&ZI1468, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 8:
	{
	    NAMESPACE ZI425;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI425, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 65:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1479;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR1286 (&ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1479);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1479) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 71:
	{
	    EXP ZI1454;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1481;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1454);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_prefix_exp ( lex_plus_Hplus, (ZI1454) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1481);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1481) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 145:
	{
	    TYPE ZI414;
	    EXP ZI1461;
	    int ZI551;
	    EXP ZI1272;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1492;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1461, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_reinterp_cast_exp ( (ZI414), (ZI1461), (ZI551) ) ;
	    }
	    ZR1240 (ZI1272, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1492);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1492) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 77:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {

    (ZI493) = NULL_exp ;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 116:
	{
	    int ZI450;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1487;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_sizeof ; 
	    }
	    ZR593 (ZI450, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1487);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1487) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 78:
	{
	    EXP ZI1456;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1483;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_indir_exp ( (ZI1456) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1483);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1483) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 4:
	{
	    IDENTIFIER ZI1470;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI1470 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1471 (&ZI1470, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 146:
	{
	    TYPE ZI414;
	    EXP ZI1462;
	    int ZI551;
	    EXP ZI1273;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1493;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1462, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1273) = make_static_cast_exp ( (ZI414), (ZI1462), (ZI551) ) ;
	    }
	    ZR1240 (ZI1273, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1493) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 6:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1505;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI478 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1505);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1505) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 7:
	{
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1281;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1506;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI460 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = (ZI460) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1265) ) ;
    COPY_id ( type_name ( (ZI1265) ), (ZI419) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	    {

    (ZI414) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR500 (&ZI497);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1281) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI1281, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1506);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1506) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 148:
	{
	    EXP ZI1276;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1496;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {

    (ZI1276) = make_this_exp () ;
	    }
	    ZR1240 (ZI1276, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1496);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1496) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 2:
	{
	    IDENTIFIER ZI1466;
	    EXP ZI493;
	    EXP ZI456;

	    {

    ZI1466 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1467 (&ZI1466, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 152:
	{
	    int ZI450;
	    EXP ZI1270;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1490;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_typeid ; 
	    }
	    ZR553 (ZI450, &ZI1270);
	    ZR1240 (ZI1270, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1490);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1490) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 329:
	{
	    int ZI450;
	    EXP ZI1269;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1489;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_vtable ; 
	    }
	    ZR553 (ZI450, &ZI1269);
	    ZR1240 (ZI1269, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1489);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1489) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 33:
	{
	    EXP ZI1457;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1484;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

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
	    ZR581 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_ref_exp ( (ZI1457), 0 ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1484);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1484) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 184: case 285: case 298:
	{
	    BASE_TYPE ZI511;
	    TYPE ZI1265;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1280;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1499;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ZR509 (&ZI511);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1265) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	    {

    (ZI414) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR500 (&ZI497);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1280) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI1280, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1499);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1499) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 64:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR678 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 288: case 322:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR776 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 96: case 100: case 222:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR662 ();
	    ZR1440 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 297: case 323:
	{
	    EXP ZI1434;
	    EXP ZI1475;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ZR643 (&ZI1434);
	    ZR1436 (&ZI1434, &ZI1475);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1475) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 101: case 107: case 125:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR738 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 95: case 99: case 108: case 113:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR752 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
	{
	    EXP ZI1275;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1495;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ZR437 (&ZI1275);
	    ZR1240 (ZI1275, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1495);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1495) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 62:
	{
	    EXP ZI1458;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1485;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

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
	    ZR581 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_not_exp ( (ZI1458) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1485);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1485) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 141:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1503;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    parse_operator (&ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1503);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1503) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 26: case 109: case 119:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR713 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 149:
	{
	    EXP ZI1287;
	    EXP ZI1477;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    ZR635 (&ZI1287);
	    ZR1289 (&ZI1287, &ZI1477);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1477) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 151:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ZR771 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 131: case 140:
	{
	    int ZI1501;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1502;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {
 (ZI1501) = 0 ; 
	    }
	    ZR1430 (&ZI1501, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1502);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1502) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      case 43: case 59: case 69: case 85:
	{
	    int ZI450;
	    EXP ZI1459;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1486;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI456;

	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR596 ();
	    ZR581 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_uminus_exp ( (ZI450), (ZI1459) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1486);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI493) = make_exp_stmt ( (ZI1486) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI456) = add_compound_stmt ( (ZI558), (ZI493) ) ;
	    }
	    ZI558 = ZI456;
	    goto ZL2_676;
	}
	/*UNREACHED*/
      default:
	{
	    ZI431 = ZI558;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

/* END OF FILE */
