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
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
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
ZR1093(EXP *ZI1092, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 347:
	{
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1092), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI417) = make_comma_exp ( (ZI421) ) ;
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_exp_stmt ( (ZI417) ) ;
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
	    int ZI538;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 347:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_exp_stmt ( (*ZI1092) ) ;
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
    *ZO405 = ZI405;
}

void
ZR636(CV_SPEC *ZO631)
{
    CV_SPEC ZI631;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR633 (&ZI631);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI631) = cv_none ; 
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
    *ZO631 = ZI631;
}

void
ZR1094(void)
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
ZR530(void)
{
    switch (CURRENT_TERMINAL) {
      case 223:
	{
	    ADVANCE_LEXER;
	    ZR1094 ();
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
ZR632(CV_SPEC *ZO631)
{
    CV_SPEC ZI631;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (ZI631) = cv_const ; 
	    }
	}
	break;
      case 124:
	{
	    ADVANCE_LEXER;
	    {
 (ZI631) = cv_volatile ; 
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
    *ZO631 = ZI631;
}

void
ZR470(void)
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
ZR825(TYPE ZI421, BASE_TYPE ZI424)
{
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI1039;
	    IDENTIFIER ZI1040;
	    TYPE ZI1036;
	    IDENTIFIER ZI400;
	    TYPE ZI396;

	    ADVANCE_LEXER;
	    ZR743 (&ZI1039, &ZI1040);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI1039) ) ) {
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
	    ZR869 (ZI1039, ZI1040, &ZI1036, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI1036) ) ? (ZI421) : inject_pre_type ( (ZI1036), (ZI421), 1 ) ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI396), (ZI400), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      case 1: case 2: case 4:
	{
	    IDENTIFIER ZI1043;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI1043 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI1043 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1043 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZR1044 (&ZI421, &ZI424, &ZI1043);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1037;
	    TYPE ZI1038;
	    IDENTIFIER ZI400;
	    TYPE ZI1036;
	    TYPE ZI396;

	    ZR732 (&ZI1037);
	    ZR743 (&ZI1038, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1036) = ( IS_NULL_type ( (ZI1038) ) ? (ZI1037) : inject_pre_type ( (ZI1038), (ZI1037), 0 ) ) ;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI1036) ) ? (ZI421) : inject_pre_type ( (ZI1036), (ZI421), 1 ) ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI396), (ZI400), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      case 41:
	{
	    IDENTIFIER ZI400;
	    EXP ZI468;
	    TYPE ZI396;

	    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ADVANCE_LEXER;
	    ZR519 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZI400) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI396) = make_bitfield_type ( (ZI421), (ZI424), (ZI468), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI396), (ZI400), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
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
ZR789(IDENTIFIER ZI548, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210:
	{
	    ZR517 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 64:
	{
	    SID_LIST_EXP ZI421;

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
	    ZR1073 (&ZI548, &ZI421);
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
    MAKE_exp_aggregate ( type_void, (ZI421), NULL_list ( OFFSET ), (ZI405) ) ;
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
    *ZO405 = ZI405;
}

void
ZR480(EXP *ZO914)
{
    EXP ZI914;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR477 (&ZI405);
	ZR915 (ZI405, &ZI914);
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
    *ZO914 = ZI914;
}

void
ZR752(TYPE *ZO867, IDENTIFIER *ZO868)
{
    TYPE ZI867;
    IDENTIFIER ZI868;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI396;
	    IDENTIFIER ZI400;

	    ADVANCE_LEXER;
	    ZR743 (&ZI396, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI396) ) ) {
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
	    ZR869 (ZI396, ZI400, &ZI867, &ZI868);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 2: case 4:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI396;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI396) = NULL_type ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR869 (ZI396, ZI400, &ZI867, &ZI868);
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
    *ZO867 = ZI867;
    *ZO868 = ZI868;
}

void
ZR581(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 109:
	{
	    unsigned ZI582;
	    int ZI538;
	    EXP ZI468;
	    EXP ZI417;
	    EXP ZI583;
	    EXP ZI449;
	    EXP ZI548;
	    EXP ZI586;

	    ADVANCE_LEXER;
	    {
 (ZI582) = crt_condition ; 
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR395 ();
	    ZR415 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI417) = begin_if_stmt ( (ZI468) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI583) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR557 (ZI583, &ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI548) = cont_if_stmt ( (ZI417), (ZI449) ) ;
	    }
	    {
		{
		    EXP ZI585;

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

    (ZI585) = begin_compound_stmt ( 1 ) ;
		    }
		    ZR557 (ZI585, &ZI586);
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
    (ZI586) = NULL_exp ;
		    }
		}
	      ZL2:;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI405) = end_if_stmt ( (ZI548), (ZI586) ) ;
	    }
	    {
 crt_condition = (ZI582) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 119:
	{
	    int ZI538;
	    EXP ZI468;
	    EXP ZI417;
	    int ZI588;
	    EXP ZI583;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
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
	    ZR415 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI417) = begin_switch_stmt ( (ZI468) ) ;
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
 (ZI588) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI588) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI583) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR557 (ZI583, &ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI405) = end_switch_stmt ( (ZI417), (ZI449), (ZI588) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 26:
	{
	    ZR570 (&ZI405);
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
    *ZO405 = ZI405;
}

void
ZR415(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210:
	{
	    EXP ZI1026;

	    ZR420 (&ZI1026);
	    ZR1028 (&ZI1026, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI417;
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;

	    ZR511 (&ZI417);
	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI417), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI405) = make_comma_exp ( (ZI421) ) ;
	    }
	}
	break;
      case 346:
	{
	    EXP ZI417;
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;

	    ZR512 (&ZI417);
	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI417), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI405) = make_comma_exp ( (ZI421) ) ;
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
    *ZO405 = ZI405;
}

void
ZR549(EXP ZI468, int ZI548, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_549:;
    {
	EXP ZI417;
	EXP ZI449;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) {
	if ( !(ZI548) ) report ( crt_loc, ERR_stmt_dcl_start () ) ;
	in_declaration++ ;
    }
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR560 ();
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    in_declaration-- ;
    (ZI417) = NULL_exp ;
	}
	{

    unreached_fall = 1 ;
	}
	{

    (ZI449) = add_compound_stmt ( (ZI468), (ZI417) ) ;
	}
	ZI468 = ZI449;
	goto ZL2_549;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 24: case 26: case 33: case 43: case 59:
      case 61: case 62: case 64: case 65: case 69:
      case 71: case 77: case 78: case 85: case 95:
      case 96: case 99: case 100: case 101: case 107:
      case 108: case 109: case 113: case 116: case 119:
      case 125: case 126: case 170: case 206: case 210:
      case 223: case 289: case 298: case 323: case 324:
      case 346:
	{
	    EXP ZI417;
	    EXP ZI449;
	    int ZI550;

	    ZR529 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI449) = add_compound_stmt ( (ZI468), (ZI417) ) ;
	    }
	    {
 (ZI550) = 0 ; 
	    }
	    ZI468 = ZI449;
	    ZI548 = ZI550;
	    goto ZL2_549;
	}
	/*UNREACHED*/
      default:
	{
	    ZI405 = ZI468;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR725(BASE_TYPE *ZI689, TYPE *ZI690, CV_SPEC *ZI691, DECL_SPEC *ZI717, BASE_TYPE *ZO659, TYPE *ZO396, CV_SPEC *ZO631, DECL_SPEC *ZO606)
{
    BASE_TYPE ZI659;
    TYPE ZI396;
    CV_SPEC ZI631;
    DECL_SPEC ZI606;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1097;
	TYPE ZI1098;
	CV_SPEC ZI1099;
	DECL_SPEC ZI1100;
	BASE_TYPE ZI693;
	TYPE ZI694;
	CV_SPEC ZI695;
	DECL_SPEC ZI719;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR715 (&ZI1097, &ZI1098, &ZI1099, &ZI1100);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	ZR725 (&ZI1097, &ZI1098, &ZI1099, &ZI1100, &ZI693, &ZI694, &ZI695, &ZI719);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI689) & (ZI693) ) {
	(ZI659) = join_pre_types ( (*ZI689), (ZI693) ) ;
    } else {
	(ZI659) = ( (*ZI689) | (ZI693) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI690) ) ) {
	(ZI396) = (ZI694) ;
    } else if ( IS_NULL_type ( (ZI694) ) ) {
	(ZI396) = (*ZI690) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI690), (ZI694) ) ) ;
	(ZI396) = (ZI694) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI691) & (ZI695) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI631) = ( (*ZI691) | (ZI695) ) ;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI717) & (ZI719) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI606) = ( (*ZI717) | (ZI719) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI659 = *ZI689;
	    ZI396 = *ZI690;
	    ZI631 = *ZI691;
	    ZI606 = *ZI717;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO659 = ZI659;
    *ZO396 = ZI396;
    *ZO631 = ZI631;
    *ZO606 = ZI606;
}

void
ZR556(EXP ZI468, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    int ZI548;

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
	    {

    COPY_int ( exp_sequence_block ( (ZI468) ), 2 ) ;
    (ZI548) = 1 ;
	    }
	    ZR549 (ZI468, ZI548, &ZI405);
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
	}
	break;
      case 1: case 2: case 4: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 24: case 26: case 33: case 43: case 59:
      case 61: case 62: case 65: case 69: case 71:
      case 77: case 78: case 85: case 95: case 96:
      case 99: case 100: case 101: case 107: case 108:
      case 109: case 113: case 116: case 119: case 125:
      case 126: case 170: case 206: case 210: case 223:
      case 289: case 298: case 323: case 324: case 346:
	{
	    EXP ZI417;

	    ZR555 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = add_compound_stmt ( (ZI468), (ZI417) ) ;
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
    *ZO405 = ZI405;
}

void
ZR529(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    ZR552 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 2: case 4: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 24: case 26: case 33: case 43: case 59:
      case 61: case 62: case 65: case 69: case 71:
      case 77: case 78: case 85: case 95: case 96:
      case 99: case 100: case 101: case 107: case 108:
      case 109: case 113: case 116: case 119: case 125:
      case 126: case 170: case 206: case 210: case 223:
      case 289: case 298: case 323: case 324: case 346:
	{
	    ZR555 (&ZI405);
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
    *ZO405 = ZI405;
}

void
ZR760(TYPE *ZO860)
{
    TYPE ZI860;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1061 (&ZI860);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI400;
	    int ZI748;
	    TYPE ZI396;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI400) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI400) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR759 (&ZI748);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = make_func_type ( NULL_type, ( (ZI748) | FUNC_WEAK ), cv_c, empty_type_set ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR861 (ZI396, &ZI860);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;
	    TYPE ZI396;

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
	    ZR758 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI405) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI396) ) ;
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
	    ZR861 (ZI396, &ZI860);
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
    *ZO860 = ZI860;
}

void
ZR984(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	int ZI473;
	EXP ZI417;
	EXP ZI962;
	EXP ZI961;
	EXP ZI960;
	EXP ZI959;
	EXP ZI958;
	EXP ZI957;
	EXP ZI956;
	EXP ZI955;
	EXP ZI954;
	EXP ZI953;
	EXP ZI952;
	EXP ZI949;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR445 (&ZI396, &ZI473);
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
	ZR460 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* n is the number of type definitions in t */
    (ZI962) = make_cast_exp ( (ZI396), (ZI417), (ZI473) ) ;
	}
	ZR919 (ZI962, &ZI961);
	ZR915 (ZI961, &ZI960);
	ZR911 (ZI960, &ZI959);
	ZR907 (ZI959, &ZI958);
	ZR903 (ZI958, &ZI957);
	ZR899 (ZI957, &ZI956);
	ZR895 (ZI956, &ZI955);
	ZR891 (ZI955, &ZI954);
	ZR887 (ZI954, &ZI953);
	ZR883 (ZI953, &ZI952);
	ZR879 (ZI952, &ZI949);
	ZR951 (&ZI949, &ZI405);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 298: case 324: case 346:
	{
	    EXP ZI1022;
	    EXP ZI1023;
	    EXP ZI1024;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI1022);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1023) = make_paren_exp ( (ZI1022) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR923 (ZI1023, &ZI1024);
	    ZR1015 (&ZI1024, &ZI405);
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
    *ZO405 = ZI405;
}

void
ZR857(TYPE ZI853, IDENTIFIER ZI854, TYPE *ZO855, IDENTIFIER *ZO856)
{
    TYPE ZI855;
    IDENTIFIER ZI856;

  ZL2_857:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI424;
	    TYPE ZI396;

	    ZI400 = ZI854;
	    ZR755 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI853) ) ? (ZI424) : inject_pre_type ( (ZI853), (ZI424), 0 ) ) ;
	    }
	    ZI853 = ZI396;
	    ZI854 = ZI400;
	    goto ZL2_857;
	}
	/*UNREACHED*/
      default:
	{
	    ZI855 = ZI853;
	    ZI856 = ZI854;
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
    *ZO855 = ZI855;
    *ZO856 = ZI856;
}

void
ZR603(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 101:
	{
	    unsigned ZI582;
	    int ZI538;
	    EXP ZI417;
	    EXP ZI583;
	    EXP ZI449;
	    EXP ZI604;
	    EXP ZI468;

	    ADVANCE_LEXER;
	    {
 (ZI582) = crt_condition ; 
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI417) = begin_do_stmt () ;
	    }
	    {

    (ZI583) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR557 (ZI583, &ZI449);
	    switch (CURRENT_TERMINAL) {
	      case 125:
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
	    ZR415 (&ZI604);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI468) = bind_temporary ( (ZI604) ) ;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI405) = end_do_stmt ( (ZI417), (ZI449), (ZI468) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 crt_condition = (ZI582) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR397 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 107:
	{
	    unsigned ZI582;
	    int ZI538;
	    EXP ZI586;
	    EXP ZI417;
	    EXP ZI605;
	    EXP ZI468;
	    EXP ZI606;
	    EXP ZI449;
	    EXP ZI607;
	    EXP ZI548;

	    ADVANCE_LEXER;
	    {
 (ZI582) = crt_condition ; 
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
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
	    {

    (ZI586) = begin_for_stmt () ;
	    }
	    ZR599 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI605) = init_for_stmt ( (ZI586), &(ZI417) ) ;
	    }
	    ZR600 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI606) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR602 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI607) = cond_for_stmt ( (ZI605), (ZI468), (ZI449) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    mark_compound_stmt ( (ZI606) ) ;
	    }
	    ZR557 (ZI606, &ZI548);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI405) = end_for_stmt ( (ZI607), (ZI548) ) ;
	    }
	    {
 crt_condition = (ZI582) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 125:
	{
	    unsigned ZI582;
	    int ZI538;
	    EXP ZI604;
	    EXP ZI468;
	    EXP ZI417;
	    EXP ZI583;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    {
 (ZI582) = crt_condition ; 
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
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
	    ZR415 (&ZI604);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI468) = bind_temporary ( (ZI604) ) ;
	    }
	    {

    (ZI417) = begin_while_stmt ( (ZI468) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI583) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR557 (ZI583, &ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI405) = end_while_stmt ( (ZI417), (ZI449) ) ;
	    }
	    {
 crt_condition = (ZI582) ; 
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
    *ZO405 = ZI405;
}

void
ZR507(void)
{
    switch (CURRENT_TERMINAL) {
      case 45:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 58:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 60:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 70:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 74:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 76:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 79:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 34:
	{
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
	}
	break;
      case 68:
	{
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
	}
	break;
      case 81:
	{
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
ZR537(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 346:
	{
	    ADVANCE_LEXER;
	    ZR1079 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI405) = NULL_exp ;
	    }
	}
	break;
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210:
	{
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ZR420 (&ZI1026);
	    ZR1028 (&ZI1026, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_exp_stmt ( (ZI417) ) ;
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
      case 298: case 324:
	{
	    EXP ZI1074;
	    EXP ZI417;
	    int ZI538;

	    ZR511 (&ZI1074);
	    ZR1076 (&ZI1074, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_exp_stmt ( (ZI417) ) ;
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
    *ZO405 = ZI405;
}

void
ZR835(OFFSET ZI449, TYPE ZI569, OFFSET *ZO417, TYPE *ZO396)
{
    OFFSET ZI417;
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	NAMESPACE ZI427;
	IDENTIFIER ZI400;

	{

    (ZI427) = offset_nspace ( (ZI569) ) ;
	}
	{

    RESCAN_LEXER ;
	}
	ZR428 (ZI427, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    OFFSET off = offset_member ( (ZI569), (ZI400), &(ZI396), (ZI427), 1 ) ;
    (ZI417) = offset_add ( (ZI449), off ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO417 = ZI417;
    *ZO396 = ZI396;
}

void
ZR861(TYPE ZI859, TYPE *ZO860)
{
    TYPE ZI860;

  ZL2_861:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    TYPE ZI424;
	    TYPE ZI396;

	    ZR755 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI859) ) ? (ZI424) : inject_pre_type ( (ZI859), (ZI424), 0 ) ) ;
	    }
	    ZI859 = ZI396;
	    goto ZL2_861;
	}
	/*UNREACHED*/
      default:
	{
	    ZI860 = ZI859;
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
    *ZO860 = ZI860;
}

void
ZR807(void)
{
    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	{
	    EXP ZI421;

	    ZR806 (&ZI421);
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
			ZR805 ();
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

    crt_hash_cond = (ZI421) ;
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
ZR869(TYPE ZI865, IDENTIFIER ZI866, TYPE *ZO867, IDENTIFIER *ZO868)
{
    TYPE ZI867;
    IDENTIFIER ZI868;

  ZL2_869:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI424;
	    TYPE ZI396;

	    ZI400 = ZI866;
	    ZR746 (ZI400, &ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI865) ) ? (ZI424) : inject_pre_type ( (ZI865), (ZI424), 0 ) ) ;
	    }
	    ZI865 = ZI396;
	    ZI866 = ZI400;
	    goto ZL2_869;
	}
	/*UNREACHED*/
      default:
	{
	    ZI867 = ZI865;
	    ZI868 = ZI866;
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
    *ZO867 = ZI867;
    *ZO868 = ZI868;
}

void
parse_mem_type(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI659;
	TYPE ZI421;
	CV_SPEC ZI631;
	TYPE ZI424;

	ZR688 (&ZI659, &ZI421, &ZI631);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI424) = complete_pre_type ( (ZI659), (ZI421), (ZI631), 1 ) ;
    have_type_specifier = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 73:
		{
		    EXP ZI468;

		    ADVANCE_LEXER;
		    ZR519 (&ZI468);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI396) = make_bitfield_type ( (ZI424), (ZI659), (ZI468), 0 ) ;
		    }
		}
		break;
	      default:
		{
		    ZR761 (ZI424, &ZI396);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
}

void
ZR616(EXP *ZO417)
{
    EXP ZI417;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 298: case 324: case 346:
	{
	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI417) = NULL_exp ;
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
    *ZO417 = ZI417;
}

void
parse_operator(IDENTIFIER *ZO400)
{
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI400) = NULL_id ;
	}
    }
    *ZO400 = ZI400;
}

void
ZR498(EXP *ZO886)
{
    EXP ZI886;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR496 (&ZI405);
	ZR887 (ZI405, &ZI886);
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
    *ZO886 = ZI886;
}

void
ZR614(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI468;

	    ADVANCE_LEXER;
	    ZR519 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_case ) ) ;
    (ZI405) = begin_case_stmt ( (ZI468), 1 ) ;
	    }
	}
	break;
      case 100:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_default ) ) ;
    (ZI405) = begin_default_stmt ( 1 ) ;
	    }
	}
	break;
      case 1: case 2: case 4:
	{
	    IDENTIFIER ZI400;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI405) = make_goto_stmt ( (ZI400) ) ;
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
    *ZO405 = ZI405;
}

void
ZR875(EXP ZI873, EXP *ZO874)
{
    EXP ZI874;

  ZL2_875:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI421;
	    EXP ZI468;

	    ZI421 = ZI873;
	    {

    ZI468 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI468), c ) ;
	    }
	    {

    target_decl ( lex_elif, (ZI468) ) ;
	    }
	    ZR805 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI873 = ZI421;
		goto ZL2_875;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI874 = ZI873;
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
    *ZO874 = ZI874;
}

void
ZR516(SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210:
	{
	    EXP ZI417;

	    ZR420 (&ZI417);
	    ZR1029 (&ZI417, &ZI421);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI417;
	    SID_LIST_EXP ZI424;

	    ZR511 (&ZI417);
	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI417), (ZI424), (ZI421) ) ;
	    }
	}
	break;
      case 346:
	{
	    EXP ZI417;
	    SID_LIST_EXP ZI424;

	    ZR512 (&ZI417);
	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI417), (ZI424), (ZI421) ) ;
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
    *ZO421 = ZI421;
}

void
ZR744(int *ZO748)
{
    int ZI748;

  ZL2_744:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZI748) = 1 ; 
	    }
	}
	break;
      case 2: case 25: case 94: case 97: case 98:
      case 102: case 104: case 105: case 106: case 110:
      case 111: case 112: case 114: case 115: case 117:
      case 118: case 120: case 121: case 122: case 123:
      case 124: case 137: case 156: case 185: case 286:
      case 299:
	{
	    IDENTIFIER ZI548;

	    ZR771 (&ZI548);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			goto ZL2_744;
		    }
		    /*UNREACHED*/
		  default:
		    {
			{
 (ZI748) = 0 ; 
			}
		    }
		    break;
		  case 355:
		    RESTORE_LEXER;
		    goto ZL1;
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
    *ZO748 = ZI748;
}

void
ZR410(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 17: case 18:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 17:
		    {
			{

    ZI405 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			{

    ZI405 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	}
	break;
      case 22:
	{
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 22:
			{

    ZI405 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	}
	break;
      case 21:
	{
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    ZI405 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	}
	break;
      case 19: case 20:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    ZI405 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    ZI405 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
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
    *ZO405 = ZI405;
}

void
ZR778(IDENTIFIER *ZO400)
{
    IDENTIFIER ZI400;

    switch (CURRENT_TERMINAL) {
      case 2:
	{
	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_dcl_fct_par_typedef ( (ZI400) ) ) ;
	    }
	}
	break;
      case 1: case 4:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI400 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
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
    *ZO400 = ZI400;
}

void
parse_decl(TYPE ZI396, DECL_SPEC ZI606)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI689;
	TYPE ZI1095;
	CV_SPEC ZI691;
	DECL_SPEC ZI1096;
	BASE_TYPE ZI659;
	TYPE ZI690;
	CV_SPEC ZI631;
	DECL_SPEC ZI717;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	ZR715 (&ZI689, &ZI1095, &ZI691, &ZI1096);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	ZR725 (&ZI689, &ZI1095, &ZI691, &ZI1096, &ZI659, &ZI690, &ZI631, &ZI717);
	ZR814 (&ZI659, &ZI690, &ZI631, &ZI717);
	switch (CURRENT_TERMINAL) {
	  case 77:
	    break;
	  case 355:
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
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
    }
}

void
ZR879(EXP ZI877, EXP *ZO878)
{
    EXP ZI878;

  ZL2_879:;
    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    EXP ZI449;
	    EXP ZI405;

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
	    ZR500 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_log_or_exp ( (ZI877), (ZI449) ) ;
	    }
	    ZI877 = ZI405;
	    goto ZL2_879;
	}
	/*UNREACHED*/
      default:
	{
	    ZI878 = ZI877;
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
    *ZO878 = ZI878;
}

void
ZR625(SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    ZR422 (&ZI421);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI421) = NULL_list ( EXP ) ;
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
    *ZO421 = ZI421;
}

void
ZR496(EXP *ZO890)
{
    EXP ZI890;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR494 (&ZI405);
	ZR891 (ZI405, &ZI890);
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
    *ZO890 = ZI890;
}

void
ZR552(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	int ZI548;
	EXP ZI417;

	{

    (ZI468) = begin_compound_stmt ( 1 ) ;
	}
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
	{

    COPY_int ( exp_sequence_block ( (ZI468) ), 2 ) ;
    (ZI548) = 1 ;
	}
	ZR549 (ZI468, ZI548, &ZI417);
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

    (ZI405) = end_compound_stmt ( (ZI417) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR397(void)
{
    if ((CURRENT_TERMINAL) == 355) {
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
	int ZI396;

	{
 (ZI396) = lex_semicolon ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI396) ) report ( crt_loc, ERR_lex_expect ( (ZI396) ) ) ;
	}
    }
}

void
ZR502(EXP *ZO878)
{
    EXP ZI878;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR500 (&ZI405);
	ZR879 (ZI405, &ZI878);
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
    *ZO878 = ZI878;
}

void
ZR519(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;

	ZR504 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI405) = convert_reference ( (ZI417), REF_NORMAL ) ;
    (ZI405) = convert_lvalue ( (ZI405) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR732(TYPE *ZO421)
{
    TYPE ZI421;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	CV_SPEC ZI631;

	switch (CURRENT_TERMINAL) {
	  case 78:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR636 (&ZI631);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_type_ptr ( (ZI631), NULL_type, (ZI421) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO421 = ZI421;
}

void
ZR883(EXP ZI881, EXP *ZO882)
{
    EXP ZI882;

  ZL2_883:;
    switch (CURRENT_TERMINAL) {
      case 55:
	{
	    EXP ZI449;
	    EXP ZI405;

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
	    ZR498 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_log_and_exp ( (ZI881), (ZI449) ) ;
	    }
	    ZI881 = ZI405;
	    goto ZL2_883;
	}
	/*UNREACHED*/
      default:
	{
	    ZI882 = ZI881;
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
    *ZO882 = ZI882;
}

void
ZR756(TYPE *ZO569)
{
    TYPE ZI569;

    switch (CURRENT_TERMINAL) {
      case 2: case 25: case 47: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 137: case 156: case 185:
      case 286: case 299:
	{
	    int ZI748;

	    ZR744 (&ZI748);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI569) = make_func_type ( NULL_type, (ZI748), cv_c, empty_type_set ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI569) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
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
    *ZO569 = ZI569;
}

void
ZR489(EXP *ZO902)
{
    EXP ZI902;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR486 (&ZI405);
	ZR903 (ZI405, &ZI902);
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
    *ZO902 = ZI902;
}

void
ZR798(DECL_SPEC ZI606, BASE_TYPE ZI659, TYPE ZI396)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_798:;
    {
	ZR797 (ZI606, ZI659, ZI396);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_798;
		}
		/*UNREACHED*/
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR758(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210:
	{
	    ZR519 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI405) = NULL_exp ;
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
    *ZO405 = ZI405;
}

void
ZR759(int *ZO748)
{
    int ZI748;

    switch (CURRENT_TERMINAL) {
      case 2: case 25: case 47: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 137: case 156: case 185:
      case 286: case 299:
	{
	    ZR744 (&ZI748);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI748) = 0 ; 
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
    *ZO748 = ZI748;
}

void
ZR887(EXP ZI885, EXP *ZO886)
{
    EXP ZI886;

  ZL2_887:;
    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    EXP ZI449;
	    EXP ZI405;

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
	    ZR496 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_or_exp ( (ZI885), (ZI449) ) ;
	    }
	    ZI885 = ZI405;
	    goto ZL2_887;
	}
	/*UNREACHED*/
      default:
	{
	    ZI886 = ZI885;
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
    *ZO886 = ZI886;
}

void
ZR477(EXP *ZO918)
{
    EXP ZI918;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR460 (&ZI405);
	ZR919 (ZI405, &ZI918);
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
    *ZO918 = ZI918;
}

void
ZR1015(EXP *ZI1014, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    EXP ZI449;

	    ADVANCE_LEXER;
	    ZR420 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_assign_exp ( (*ZI1014), (ZI449), 1 ) ;
	    }
	}
	break;
      default:
	{
	    EXP ZI961;
	    EXP ZI960;
	    EXP ZI959;
	    EXP ZI958;
	    EXP ZI957;
	    EXP ZI956;
	    EXP ZI955;
	    EXP ZI954;
	    EXP ZI953;
	    EXP ZI952;
	    EXP ZI949;

	    ZR919 (*ZI1014, &ZI961);
	    ZR915 (ZI961, &ZI960);
	    ZR911 (ZI960, &ZI959);
	    ZR907 (ZI959, &ZI958);
	    ZR903 (ZI958, &ZI957);
	    ZR899 (ZI957, &ZI956);
	    ZR895 (ZI956, &ZI955);
	    ZR891 (ZI955, &ZI954);
	    ZR887 (ZI954, &ZI953);
	    ZR883 (ZI953, &ZI952);
	    ZR879 (ZI952, &ZI949);
	    ZR951 (&ZI949, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 34: case 45: case 58: case 60: case 68:
      case 70: case 74: case 76: case 79: case 81:
	{
	    int ZI461;
	    EXP ZI449;

	    {
 (ZI461) = crt_lex_token ; 
	    }
	    ZR507 ();
	    ZR420 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI405) = make_become_exp ( (ZI461), (*ZI1014), (ZI449) ) ;
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
    *ZO405 = ZI405;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
