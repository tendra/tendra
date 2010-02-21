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
ZR553(TYPE *ZO415, EXP *ZO432, int *ZO552)
{
    TYPE ZI415;
    EXP ZI432;
    int ZI552;

    if ((CURRENT_TERMINAL) == 355) {
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
	ZR549 (&ZI415, &ZI552);
	switch (CURRENT_TERMINAL) {
	  case 49:
	    break;
	  case 355:
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
	ZR492 (&ZI432);
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
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
    *ZO432 = ZI432;
    *ZO552 = ZI552;
}

void
ZR700(EXP *ZO1187, EXP *ZO1188, int *ZO1189)
{
    EXP ZI1187;
    EXP ZI1188;
    int ZI1189;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI559;
	EXP ZI498;
	int ZI672;
	EXP ZI494;
	EXP ZI432;

	switch (CURRENT_TERMINAL) {
	  case 26:
	    {

    ZI559 = crt_token->pp_data.exp ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZI559), c ) ;
    (ZI498) = c ;
	}
	{

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	}
	ZR680 (&ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI672) ; 
	}
	{

    (ZI432) = begin_hash_if_stmt ( (ZI559), (ZI494) ) ;
	}
	ZR1190 (ZI432, ZI498, ZI672, &ZI1187, &ZI1188, &ZI1189);
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
    *ZO1187 = ZI1187;
    *ZO1188 = ZI1188;
    *ZO1189 = ZI1189;
}

void
ZR787(CV_SPEC *ZO785)
{
    CV_SPEC ZI785;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	CV_SPEC ZI494;

	ZR786 (&ZI494);
	{
	    switch (CURRENT_TERMINAL) {
	      case 98: case 124:
		{
		    CV_SPEC ZI457;

		    ZR787 (&ZI457);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    CV_SPEC c = ( (ZI494) & (ZI457) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI785) = ( (ZI494) | (ZI457) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI785 = ZI494;
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO785 = ZI785;
}

void
ZR1472(IDENTIFIER *ZI1471, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 33: case 34: case 35: case 36: case 42:
      case 44: case 45: case 46: case 48: case 49:
      case 50: case 53: case 54: case 55: case 56:
      case 57: case 58: case 59: case 60: case 61:
      case 63: case 65: case 66: case 67: case 68:
      case 69: case 70: case 71: case 72: case 73:
      case 74: case 75: case 76: case 77: case 78:
      case 79: case 80: case 81: case 82: case 84:
      case 86: case 87:
	{
	    IDENTIFIER ZI420;
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
	    EXP ZI494;
	    int ZI672;

	    {

    (ZI420) = (*ZI1471) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 41:
	{
	    EXP ZI494;
	    EXP ZI457;

	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI494) = begin_label_stmt ( (*ZI1471), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR663 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_label_stmt ( (ZI494), (ZI457) ) ;
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
    *ZO432 = ZI432;
}

void
ZR1218(EXP ZI1216, EXP *ZO1217)
{
    EXP ZI1217;

  ZL2_1218:;
    switch (CURRENT_TERMINAL) {
      case 48: case 63:
	{
	    int ZI451;
	    EXP ZI457;
	    EXP ZI432;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR618 ();
	    ZR616 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI432) = make_equality_exp ( (ZI451), (ZI1216), (ZI457) ) ;
	    }
	    ZI1216 = ZI432;
	    goto ZL2_1218;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1217 = ZI1216;
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
    *ZO1217 = ZI1217;
}

void
ZR1024(EXP ZI559, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI457;
	EXP ZI460;
	EXP ZI494;

	ZR1021 (ZI559, &ZI457, &ZI460);
	{
	    if ((CURRENT_TERMINAL) == 355) {
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

    COPY_int ( exp_sequence_block ( (ZI457) ), 2 ) ;
	}
	ZR678 (ZI457, &ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = ctor_postlude ( (ZI494), (ZI460) ) ;
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
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1346(NAMESPACE *ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI1343;
	    IDENTIFIER ZI461;

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

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI461) = check_id ( (*ZI426), (ZI1343), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = constr_name ( last_namespace, (ZI461) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI426, &ZI481);
	    ZR477 (*ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI426) ;
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
    *ZO420 = ZI420;
}

void
ZR1601(EXP *ZI1600, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 347:
	{
	    SID_LIST_EXP ZI481;
	    SID_LIST_EXP ZI498;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR650 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1600), (ZI481), (ZI498) ) ;
	    }
	    {

    (ZI494) = make_comma_exp ( (ZI498) ) ;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 77:
	{
	    int ZI672;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 347:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI432) = make_exp_stmt ( (*ZI1600) ) ;
	    }
	    {

    unreached_fall = 1 ;
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
    *ZO432 = ZI432;
}

void
ZR1474(IDENTIFIER *ZI1473, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    IDENTIFIER ZI420;
	    EXP ZI494;

	    {

    (ZI420) = (*ZI1473) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI494) = make_id_exp ( (ZI420) ) ;
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
	    }
	}
	break;
      case 41:
	{
	    EXP ZI494;
	    EXP ZI457;

	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI494) = begin_label_stmt ( (*ZI1473), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR663 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_label_stmt ( (ZI494), (ZI457) ) ;
	    }
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
    *ZO432 = ZI432;
}

void
ZR1347(NAMESPACE *ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI1344;
	    IDENTIFIER ZI461;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1344 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1344 = crt_token->pp_data.id.use ;
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
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI461) = check_id ( (*ZI426), (ZI1344), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = constr_name ( last_namespace, (ZI461) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI426, &ZI481);
	    ZR477 (*ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI426) ;
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
    *ZO420 = ZI420;
}

void
ZR790(CV_SPEC *ZO785)
{
    CV_SPEC ZI785;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR787 (&ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI785) = cv_none ; 
	    }
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
    *ZO785 = ZI785;
}

void
ZR1475(NAMESPACE *ZI426, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI494;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	    {

    (ZI494) = make_id_exp ( (ZI420) ) ;
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 141: case 147:
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
	    EXP ZI494;
	    int ZI672;

	    ZR1268 (ZI426, &ZI1454);
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
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
    *ZO432 = ZI432;
}

void
ZR1348(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;
	    NAMESPACE ZI426;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI1345;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI461;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1345 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1345 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI461) = check_id ( (ZI426), (ZI1345), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = constr_name ( last_namespace, (ZI461) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI426;
	    int ZI481;
	    IDENTIFIER ZI479;

	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    ZR476 (ZI426, &ZI481);
	    ZR477 (ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (ZI426) ;
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
    *ZO420 = ZI420;
}

void
ZR1094(BASE_TYPE *ZI512, DECL_SPEC *ZI1075, TYPE *ZI1076, ACCESS_LIST *ZI672, IDENTIFIER *ZI460)
{
    if ((CURRENT_TERMINAL) == 355) {
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

    free_access ( &(*ZI672) ) ;
	}
	{

    skip_function ( (*ZI460) ) ;
	}
	{

    end_declarator ( (*ZI460), 1 ) ;
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
	    int ZI552;

	    ADVANCE_LEXER;
	    {

    end_declarator ( (*ZI460), 1 ) ;
	    }
	    {
 (ZI552) = 0 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1089 (*ZI1075, *ZI1076, *ZI512, *ZI672, ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI672) ) ;
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

    free_access ( &(*ZI672) ) ;
	    }
	    {

    end_declarator ( (*ZI460), 1 ) ;
	    }
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
ZR714(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI460;
	EXP ZI494;

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
	ZR1098 (&ZI460);
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
	ZR651 (&ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	}
	{

    int def = init_object ( (ZI460), (ZI494) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	}
	{

    end_declarator ( (ZI460), 1 ) ;
	}
	{

    (ZI432) = end_cond () ;
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
      case 156: case 170: case 185: case 206: case 210:
      case 255: case 286: case 298: case 299: case 324:
      case 330: case 346:
	{
	    ZR492 (&ZI432);
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
    *ZO432 = ZI432;
}

void
ZR1476(NAMESPACE *ZI426, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI494;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	    {

    (ZI494) = make_id_exp ( (ZI420) ) ;
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 141: case 147:
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
	    EXP ZI494;
	    int ZI672;

	    ZR1269 (ZI426, &ZI1454);
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
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
    *ZO432 = ZI432;
}

void
ZR1222(EXP ZI1220, EXP *ZO1221)
{
    EXP ZI1221;

  ZL2_1222:;
    switch (CURRENT_TERMINAL) {
      case 49: case 50: case 53: case 54:
	{
	    int ZI451;
	    EXP ZI457;
	    EXP ZI432;

	    {
 (ZI451) = crt_lex_token ; 
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
	    ZR613 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI432) = make_relation_exp ( (ZI451), (ZI1220), (ZI457) ) ;
	    }
	    ZI1220 = ZI432;
	    goto ZL2_1222;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1221 = ZI1220;
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
    *ZO1221 = ZI1221;
}

void
ZR1477(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI420;
	    EXP ZI494;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    (ZI494) = make_id_exp ( (ZI420) ) ;
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 131: case 140: case 141: case 147:
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
	    EXP ZI494;
	    int ZI672;

	    ZR1286 (&ZI1454);
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
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
    *ZO432 = ZI432;
}

void
ZR849(int *ZO415)
{
    int ZI415;

    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    ADVANCE_LEXER;
	    ZR1328 (&ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI415) = 1 ; 
	    }
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
    *ZO415 = ZI415;
}

void
ZR992(TYPE *ZO1150)
{
    TYPE ZI1150;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI494;
	EXP ZI432;
	TYPE ZI415;

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
	ZR492 (&ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = convert_reference ( (ZI494), REF_NORMAL ) ;
    (ZI432) = convert_lvalue ( (ZI432) ) ;
	}
	{

    /* First array bound in a new-declarator */
    NAT n = make_new_array_dim ( (ZI432) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI415) ) ;
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
	ZR1151 (ZI415, &ZI1150);
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
    *ZO1150 = ZI1150;
}

void
ZR1605(void)
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
      case 355:
	return;
    }
}

void
ZR428(NAMESPACE *ZO426)
{
    NAMESPACE ZI426;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	}
	break;
      case 8: case 9:
	{
	    ZR427 (&ZI426);
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
    *ZO426 = ZI426;
}

void
ZR664(void)
{
    switch (CURRENT_TERMINAL) {
      case 223:
	{
	    ADVANCE_LEXER;
	    ZR1605 ();
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
ZR786(CV_SPEC *ZO785)
{
    CV_SPEC ZI785;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (ZI785) = cv_const ; 
	    }
	}
	break;
      case 124:
	{
	    ADVANCE_LEXER;
	    {
 (ZI785) = cv_volatile ; 
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
    *ZO785 = ZI785;
}

void
ZR837(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI498;

	ZR836 (&ZI498);
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
		    ZR835 ();
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	{

    crt_hash_cond = (ZI498) ;
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
    SAVE_LEXER (355);
    return;
}

void
ZR1226(EXP ZI1224, EXP *ZO1225)
{
    EXP ZI1225;

  ZL2_1226:;
    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR610 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_shift_exp ( lex_lshift, (ZI1224), (ZI457) ) ;
	    }
	    ZI1224 = ZI432;
	    goto ZL2_1226;
	}
	/*UNREACHED*/
      case 75:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR610 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_shift_exp ( lex_rshift, (ZI1224), (ZI457) ) ;
	    }
	    ZI1224 = ZI432;
	    goto ZL2_1226;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1225 = ZI1224;
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
    *ZO1225 = ZI1225;
}

void
ZR597(void)
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
ZR1086(DECL_SPEC ZI691, TYPE ZI498, BASE_TYPE ZI481, ACCESS_LIST ZI672, int ZI722, IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR1348 (&ZI1355);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 5:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1355) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1347 (&ZI426, &ZI1355);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1362;
	    IDENTIFIER ZI1363;

	    {

    ZI1362 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1363) = (ZI1362) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1367 (&ZI691, &ZI498, &ZI481, &ZI672, &ZI722, &ZI1363, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 3:
	{
	    IDENTIFIER ZI1365;
	    IDENTIFIER ZI1366;

	    {

    ZI1365 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1366) = (ZI1365) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1367 (&ZI691, &ZI498, &ZI481, &ZI672, &ZI722, &ZI1366, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1346 (&ZI426, &ZI1355);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 65:
	{
	    TYPE ZI1352;
	    IDENTIFIER ZI1353;
	    int ZI1354;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR942 (&ZI1352, &ZI1353, &ZI1354);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZI1354) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    if ( IS_NULL_type ( (ZI1352) ) ) {
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
	    ZR1179 (ZI1352, ZI1353, ZI1354, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 4:
	{
	    IDENTIFIER ZI1359;
	    IDENTIFIER ZI1360;

	    {

    ZI1359 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1360) = (ZI1359) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1367 (&ZI691, &ZI498, &ZI481, &ZI672, &ZI722, &ZI1360, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI479 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1355) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 7:
	{
	    IDENTIFIER ZI1358;
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1358 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI461) = (ZI1358) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1355) = constr_name ( last_namespace, (ZI461) ) ;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI1368;
	    IDENTIFIER ZI1369;

	    {

    ZI1368 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1369) = (ZI1368) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    ZR1370 (&ZI691, &ZI498, &ZI481, &ZI672, &ZI722, &ZI1369, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 141:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI1355;
	    TYPE ZI1356;
	    int ZI1357;
	    TYPE ZI1349;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    parse_operator (&ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1355) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1356) = NULL_type ;
	    }
	    {
 (ZI1357) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1355), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI1356, ZI1355, ZI1357, &ZI1349, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI1350;
	    TYPE ZI1351;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI1349;
	    TYPE ZI415;
	    int ZI1087;
	    EXP ZI432;

	    ZR928 (&ZI1350);
	    ZR942 (&ZI1351, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1349) = ( IS_NULL_type ( (ZI1351) ) ? (ZI1350) : inject_pre_type ( (ZI1351), (ZI1350), 0 ) ) ;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1349) ) ? (ZI498) : inject_pre_type ( (ZI1349), (ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (ZI691) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1087) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1087) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (ZI722) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1087) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1085 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1087) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 41:
	{
	    IDENTIFIER ZI420;
	    QUALIFIER ZI456;
	    int ZI457;
	    EXP ZI559;
	    TYPE ZI415;

	    {

    HASHID nm = lookup_anon () ;
    (ZI420) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	    }
	    {

    begin_declarator ( (ZI420), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    ADVANCE_LEXER;
	    ZR653 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZI420) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI415) = make_bitfield_type ( (ZI498), (ZI481), (ZI559), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( (ZI691), (ZI415), (ZI420), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZI460) = id ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(ZI672) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
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
    *ZO460 = ZI460;
}

void
ZR1608(NAMESPACE *ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI461;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
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
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI461), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI426, &ZI481);
	    ZR477 (*ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI426) ;
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
    *ZO420 = ZI420;
}

void
ZR429(NAMESPACE *ZO426)
{
    NAMESPACE ZI426;

    switch (CURRENT_TERMINAL) {
      case 8: case 9: case 83:
	{
	    ZR428 (&ZI426);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI426) = NULL_nspace ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
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
    *ZO426 = ZI426;
}

void
ZR1609(NAMESPACE *ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI461;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
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
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI461), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI426, &ZI481);
	    ZR477 (*ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI426) ;
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
    *ZO420 = ZI420;
}

void
ZR1000(IDENTIFIER ZI460, EXP *ZO432)
{
    EXP ZI432;

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
      case 156: case 170: case 185: case 206: case 210:
      case 255: case 286: case 299: case 330:
	{
	    ZR651 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 64:
	{
	    SID_LIST_EXP ZI498;

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
	    ZR1003 (&ZI460, &ZI498);
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
	    {

    /* The expression type is a dummy */
    MAKE_exp_aggregate ( type_void, (ZI498), NULL_list ( OFFSET ), (ZI432) ) ;
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
    *ZO432 = ZI432;
}

void
ZR1091(TYPE ZI415, DECL_SPEC ZI691)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI716;
	TOKEN ZI498;
	TYPE ZI877;

	ZR1112 (&ZI716);
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
	{

    (ZI498) = template_params ( (ZI716) ) ;
    RESCAN_LEXER ;
	}
	{

    (ZI877) = make_template_type ( (ZI498), (ZI415) ) ;
	}
	ZR840 (ZI877, ZI691);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    end_template ( (ZI498) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1610(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    IDENTIFIER ZI479;
	    NAMESPACE ZI426;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    NAMESPACE ZI426;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI461), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI426;
	    int ZI481;
	    IDENTIFIER ZI479;

	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    ZR476 (ZI426, &ZI481);
	    ZR477 (ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (ZI426) ;
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
    *ZO420 = ZI420;
}

void
ZR610(EXP *ZO1229)
{
    EXP ZI1229;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR607 (&ZI432);
	ZR1230 (ZI432, &ZI1229);
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
    *ZO1229 = ZI1229;
}

void
ZR951(TYPE *ZO1176, IDENTIFIER *ZO1177, int *ZO1178)
{
    TYPE ZI1176;
    IDENTIFIER ZI1177;
    int ZI1178;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI415;
	    IDENTIFIER ZI420;
	    int ZI559;

	    ADVANCE_LEXER;
	    ZR942 (&ZI415, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    if ( IS_NULL_type ( (ZI415) ) ) {
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
	    ZR1179 (ZI415, ZI420, ZI559, &ZI1176, &ZI1177, &ZI1178);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 83:
      case 141:
	{
	    IDENTIFIER ZI420;
	    TYPE ZI415;
	    int ZI559;

	    ZR944 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = NULL_type ;
	    }
	    {
 (ZI559) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI420), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1179 (ZI415, ZI420, ZI559, &ZI1176, &ZI1177, &ZI1178);
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
    *ZO1176 = ZI1176;
    *ZO1177 = ZI1177;
    *ZO1178 = ZI1178;
}

void
ZR1230(EXP ZI1228, EXP *ZO1229)
{
    EXP ZI1229;

  ZL2_1230:;
    switch (CURRENT_TERMINAL) {
      case 59:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR607 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_minus_exp ( (ZI1228), (ZI457) ) ;
	    }
	    ZI1228 = ZI432;
	    goto ZL2_1230;
	}
	/*UNREACHED*/
      case 69:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR607 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_plus_exp ( (ZI1228), (ZI457) ) ;
	    }
	    ZI1228 = ZI432;
	    goto ZL2_1230;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1229 = ZI1228;
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
    *ZO1229 = ZI1229;
}

void
ZR715(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 109:
	{
	    unsigned ZI716;
	    int ZI672;
	    EXP ZI559;
	    EXP ZI494;
	    EXP ZI717;
	    EXP ZI718;
	    EXP ZI457;
	    EXP ZI460;
	    EXP ZI722;

	    ADVANCE_LEXER;
	    {
 (ZI716) = crt_condition ; 
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR418 ();
	    ZR714 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = begin_if_stmt ( (ZI559) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI717) = begin_compound_stmt ( 1 ) ;
	    }
	    {

    (ZI718) = inject_cond ( (ZI717), (ZI559) ) ;
	    }
	    ZR683 (ZI718, &ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI672) ; 
	    }
	    {

    (ZI460) = cont_if_stmt ( (ZI494), (ZI457) ) ;
	    }
	    {
		{
		    EXP ZI720;
		    EXP ZI721;

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

    (ZI720) = begin_compound_stmt ( 1 ) ;
		    }
		    {

    (ZI721) = inject_cond ( (ZI720), (ZI559) ) ;
		    }
		    ZR683 (ZI721, &ZI722);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    report ( crt_loc, ERR_stmt_if_no_else () ) ;
    (ZI722) = NULL_exp ;
		    }
		}
	      ZL2:;
	    }
	    {
 unreached_prev = (ZI672) ; 
	    }
	    {

    (ZI432) = end_if_stmt ( (ZI460), (ZI722) ) ;
	    }
	    {
 crt_condition = (ZI716) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 119:
	{
	    int ZI672;
	    EXP ZI559;
	    EXP ZI494;
	    int ZI724;
	    EXP ZI717;
	    EXP ZI718;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
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
	    ZR714 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = begin_switch_stmt ( (ZI559) ) ;
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
		  case 217:
		    {
			ADVANCE_LEXER;
			{
 (ZI724) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI724) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI717) = begin_compound_stmt ( 1 ) ;
	    }
	    {

    (ZI718) = inject_cond ( (ZI717), (ZI559) ) ;
	    }
	    ZR683 (ZI718, &ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI672) ; 
	    }
	    {

    (ZI432) = end_switch_stmt ( (ZI494), (ZI457), (ZI724) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 26:
	{
	    ZR701 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    unreached_fall = 1 ;
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
    *ZO432 = ZI432;
}

void
ZR492(EXP *ZO432)
{
    EXP ZI432;

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
      case 156: case 170: case 185: case 206: case 210:
      case 255: case 286: case 299: case 330:
	{
	    EXP ZI1289;

	    ZR497 (&ZI1289);
	    ZR1291 (&ZI1289, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI494;
	    SID_LIST_EXP ZI481;
	    SID_LIST_EXP ZI498;

	    ZR645 (&ZI494);
	    ZR650 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI494), (ZI481), (ZI498) ) ;
	    }
	    {

    (ZI432) = make_comma_exp ( (ZI498) ) ;
	    }
	}
	break;
      case 346:
	{
	    EXP ZI494;
	    SID_LIST_EXP ZI481;
	    SID_LIST_EXP ZI498;

	    ZR646 (&ZI494);
	    ZR650 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI494), (ZI481), (ZI498) ) ;
	    }
	    {

    (ZI432) = make_comma_exp ( (ZI498) ) ;
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
    *ZO432 = ZI432;
}

void
ZR572(SID_LIST_EXP *ZO498, TYPE *ZO415, int *ZO552)
{
    SID_LIST_EXP ZI498;
    TYPE ZI415;
    int ZI552;

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
		    ZR549 (&ZI415, &ZI552);
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
		    {

    (ZI498) = NULL_list ( EXP ) ;
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
		  case 156: case 170: case 185: case 206: case 210:
		  case 255: case 286: case 299: case 330:
		    {
			int ZI458;
			TYPE ZI575;
			int ZI576;

			ZR499 (&ZI498);
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
			{

    (ZI458) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
			}
			{
			    switch (CURRENT_TERMINAL) {
			      case 65:
				{
				    ADVANCE_LEXER;
				    ZR549 (&ZI575, &ZI576);
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
				}
				break;
			      case 2: case 7: case 8: case 9: case 25:
			      case 83: case 97: case 98: case 102: case 104:
			      case 106: case 110: case 111: case 114: case 115:
			      case 118: case 121: case 122: case 123: case 124:
			      case 127: case 129: case 153: case 156: case 185:
			      case 286: case 299:
				{
				    ZR569 (&ZI575, &ZI576);
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
			{

    have_type_declaration = (ZI458) ;
			}
			ZI415 = ZI575;
			ZI552 = ZI576;
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
      case 127: case 129: case 153: case 156: case 185:
      case 286: case 299:
	{
	    ZR569 (&ZI415, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI498) = NULL_list ( EXP ) ;
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
    *ZO498 = ZI498;
    *ZO415 = ZI415;
    *ZO552 = ZI552;
}

void
ZR678(EXP ZI559, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_678:;
    {
	DECL_SPEC ZI691;
	TYPE ZI415;
	EXP ZI1481;
	EXP ZI494;
	EXP ZI457;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL3;
	{
 (ZI691) = dspec_none ; 
	}
	{

    (ZI415) = NULL_type ;
	}
	ZR689 (ZI415, ZI691, &ZI1481);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI494) = (ZI1481) ;
    in_declaration-- ;
	}
	{

    unreached_fall = 1 ;
	}
	{

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	}
	ZI559 = ZI457;
	goto ZL2_678;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI451;
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
	    EXP ZI1492;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_alignof ; 
	    }
	    ZR594 (ZI451, &ZI1454);
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
	    ZR1291 (&ZI1289, &ZI1492);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1492) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 83:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR1477 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1502;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1502);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1502) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 24:
	{
	    EXP ZI1479;
	    EXP ZI494;
	    EXP ZI457;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1479 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = make_exp_stmt ( (ZI1479) ) ;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 25:
	{
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
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
	    EXP ZI1504;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
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
	    {

    (ZI1284) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1504);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1504) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 130:
	{
	    TYPE ZI415;
	    EXP ZI1463;
	    int ZI552;
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
	    EXP ZI1495;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1463, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZI415), (ZI1463), (ZI552) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1495);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1495) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 5:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
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
	    EXP ZI1508;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1508);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1508) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1484;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_cast_exp ( type_void, (ZI1456), 0 ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1484);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1484) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 132:
	{
	    TYPE ZI415;
	    EXP ZI1466;
	    int ZI552;
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
	    EXP ZI1498;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1466, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZI415), (ZI1466), (ZI552) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1498);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1498) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1501;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {

    (ZI1279) = make_ellipsis_exp () ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1501);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1501) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 9:
	{
	    NAMESPACE ZI426;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1476 (&ZI426, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 1:
	{
	    IDENTIFIER ZI1467;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI1467 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI1467, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 346:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR1441 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1482;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_lit_exp ( (ZI1455) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1482);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1482) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1486;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_prefix_exp ( lex_minus_Hminus, (ZI1458) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1486);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1486) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 3:
	{
	    IDENTIFIER ZI1471;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI1471 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI1471, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 8:
	{
	    NAMESPACE ZI426;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1475 (&ZI426, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1483;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

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
	    ZR1291 (&ZI1289, &ZI1483);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1483) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1485;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_prefix_exp ( lex_plus_Hplus, (ZI1457) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1485);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1485) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 145:
	{
	    TYPE ZI415;
	    EXP ZI1464;
	    int ZI552;
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
	    EXP ZI1496;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1464, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZI415), (ZI1464), (ZI552) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1496);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1496) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 77:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {

    (ZI494) = NULL_exp ;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 116:
	{
	    int ZI451;
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
	    EXP ZI1491;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_sizeof ; 
	    }
	    ZR594 (ZI451, &ZI1454);
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
	    ZR1291 (&ZI1289, &ZI1491);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1491) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1487;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_indir_exp ( (ZI1459) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1487);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1487) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 4:
	{
	    IDENTIFIER ZI1473;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI1473 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1474 (&ZI1473, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 146:
	{
	    TYPE ZI415;
	    EXP ZI1465;
	    int ZI552;
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
	    EXP ZI1497;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1465, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1275) = make_static_cast_exp ( (ZI415), (ZI1465), (ZI552) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1497);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1497) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 6:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
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
	    EXP ZI1509;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI479 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1509);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1509) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
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
	    EXP ZI1510;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = (ZI461) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
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
	    {

    (ZI1283) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1510);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1510) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1500;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {

    (ZI1278) = make_this_exp () ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1500);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1500) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 2:
	{
	    IDENTIFIER ZI1469;
	    EXP ZI494;
	    EXP ZI457;

	    {

    ZI1469 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1470 (&ZI1469, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 152:
	{
	    int ZI451;
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
	    EXP ZI1494;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_typeid ; 
	    }
	    ZR554 (ZI451, &ZI1272);
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
	    ZR1291 (&ZI1289, &ZI1494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1494) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 330:
	{
	    int ZI451;
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
	    EXP ZI1493;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_vtable ; 
	    }
	    ZR554 (ZI451, &ZI1271);
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
	    ZR1291 (&ZI1289, &ZI1493);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1493) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1488;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

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
	    ZR582 (&ZI1460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1488);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1488) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 185: case 286: case 299:
	{
	    BASE_TYPE ZI512;
	    TYPE ZI1267;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
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
	    EXP ZI1503;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ZR510 (&ZI512);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1267) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
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
	    {

    (ZI1282) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1503);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1503) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 64:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR680 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 289: case 323:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR778 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 96: case 100: case 223:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR664 ();
	    ZR1442 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 298: case 324:
	{
	    EXP ZI1436;
	    EXP ZI1478;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ZR645 (&ZI1436);
	    ZR1438 (&ZI1436, &ZI1478);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1478) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 101: case 107: case 125:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR740 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 95: case 99: case 108: case 113:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR754 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
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
	    EXP ZI1499;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ZR438 (&ZI1277);
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
	    ZR1291 (&ZI1289, &ZI1499);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1499) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
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
	    EXP ZI1489;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

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
	    ZR582 (&ZI1461);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1489);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1489) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 141:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
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
	    EXP ZI1507;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    parse_operator (&ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1507);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1507) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 26: case 109: case 119:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR715 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 149:
	{
	    EXP ZI1289;
	    EXP ZI1480;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    ZR637 (&ZI1289);
	    ZR1291 (&ZI1289, &ZI1480);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1480) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 151:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ZR773 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 131: case 140:
	{
	    int ZI1505;
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
	    EXP ZI1506;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {
 (ZI1505) = 0 ; 
	    }
	    ZR1432 (&ZI1505, &ZI1454);
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
	    ZR1291 (&ZI1289, &ZI1506);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1506) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      case 43: case 59: case 69: case 85:
	{
	    int ZI451;
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
	    EXP ZI1490;
	    int ZI672;
	    EXP ZI494;
	    EXP ZI457;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR597 ();
	    ZR582 (&ZI1462);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_uminus_exp ( (ZI451), (ZI1462) ) ;
	    }
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
	    ZR1291 (&ZI1289, &ZI1490);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI494) = make_exp_stmt ( (ZI1490) ) ;
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

    (ZI457) = add_compound_stmt ( (ZI559), (ZI494) ) ;
	    }
	    ZI559 = ZI457;
	    goto ZL2_678;
	}
	/*UNREACHED*/
      default:
	{
	    ZI432 = ZI559;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

/* END OF FILE */
