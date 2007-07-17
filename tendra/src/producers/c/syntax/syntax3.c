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
ZR965(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	int ZI474;
	EXP ZI417;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR445 (&ZI396, &ZI474);
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
    (ZI405) = make_cast_exp ( (ZI396), (ZI417), (ZI474) ) ;
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
      case 206: case 210: case 255: case 298: case 324:
      case 346:
	{
	    EXP ZI417;
	    EXP ZI964;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI964) = make_paren_exp ( (ZI417) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR924 (ZI964, &ZI405);
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
ZR637(CV_SPEC *ZO632)
{
    CV_SPEC ZI632;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR634 (&ZI632);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI632) = cv_none ; 
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
    *ZO632 = ZI632;
}

void
ZR1095(EXP *ZI1094, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 347:
	{
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR517 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1094), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI417) = make_comma_exp ( (ZI421) ) ;
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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
	    int ZI539;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 347:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_exp_stmt ( (*ZI1094) ) ;
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
ZR1096(void)
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
ZR531(void)
{
    switch (CURRENT_TERMINAL) {
      case 223:
	{
	    ADVANCE_LEXER;
	    ZR1096 ();
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
ZR633(CV_SPEC *ZO632)
{
    CV_SPEC ZI632;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (ZI632) = cv_const ; 
	    }
	}
	break;
      case 124:
	{
	    ADVANCE_LEXER;
	    {
 (ZI632) = cv_volatile ; 
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
    *ZO632 = ZI632;
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
ZR826(TYPE ZI421, BASE_TYPE ZI424)
{
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI1036;
	    IDENTIFIER ZI1037;
	    TYPE ZI1033;
	    IDENTIFIER ZI400;
	    TYPE ZI396;

	    ADVANCE_LEXER;
	    ZR744 (&ZI1036, &ZI1037);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI1036) ) ) {
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
	    ZR870 (ZI1036, ZI1037, &ZI1033, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI1033) ) ? (ZI421) : inject_pre_type ( (ZI1033), (ZI421), 1 ) ) ;
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
	    IDENTIFIER ZI1040;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI1040 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI1040 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1040 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZR1041 (&ZI421, &ZI424, &ZI1040);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1034;
	    TYPE ZI1035;
	    IDENTIFIER ZI400;
	    TYPE ZI1033;
	    TYPE ZI396;

	    ZR733 (&ZI1034);
	    ZR744 (&ZI1035, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1033) = ( IS_NULL_type ( (ZI1035) ) ? (ZI1034) : inject_pre_type ( (ZI1035), (ZI1034), 0 ) ) ;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI1033) ) ? (ZI421) : inject_pre_type ( (ZI1033), (ZI421), 1 ) ) ;
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
	    ZR520 (&ZI468);
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
ZR790(IDENTIFIER ZI549, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255:
	{
	    ZR518 (&ZI405);
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
	    ZR1074 (&ZI549, &ZI421);
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
ZR481(EXP *ZO915)
{
    EXP ZI915;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR478 (&ZI405);
	ZR916 (ZI405, &ZI915);
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
    *ZO915 = ZI915;
}

void
ZR753(TYPE *ZO868, IDENTIFIER *ZO869)
{
    TYPE ZI868;
    IDENTIFIER ZI869;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI396;
	    IDENTIFIER ZI400;

	    ADVANCE_LEXER;
	    ZR744 (&ZI396, &ZI400);
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
	    ZR870 (ZI396, ZI400, &ZI868, &ZI869);
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
	    ZR870 (ZI396, ZI400, &ZI868, &ZI869);
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
    *ZO868 = ZI868;
    *ZO869 = ZI869;
}

void
ZR582(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 109:
	{
	    unsigned ZI583;
	    int ZI539;
	    EXP ZI468;
	    EXP ZI417;
	    EXP ZI584;
	    EXP ZI449;
	    EXP ZI549;
	    EXP ZI587;

	    ADVANCE_LEXER;
	    {
 (ZI583) = crt_condition ; 
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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

    (ZI584) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR558 (ZI584, &ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI539) ; 
	    }
	    {

    (ZI549) = cont_if_stmt ( (ZI417), (ZI449) ) ;
	    }
	    {
		{
		    EXP ZI586;

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

    (ZI586) = begin_compound_stmt ( 1 ) ;
		    }
		    ZR558 (ZI586, &ZI587);
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
    (ZI587) = NULL_exp ;
		    }
		}
	      ZL2:;
	    }
	    {
 unreached_prev = (ZI539) ; 
	    }
	    {

    (ZI405) = end_if_stmt ( (ZI549), (ZI587) ) ;
	    }
	    {
 crt_condition = (ZI583) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 119:
	{
	    int ZI539;
	    EXP ZI468;
	    EXP ZI417;
	    int ZI589;
	    EXP ZI584;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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
 (ZI589) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI589) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI584) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR558 (ZI584, &ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI539) ; 
	    }
	    {

    (ZI405) = end_switch_stmt ( (ZI417), (ZI449), (ZI589) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 26:
	{
	    ZR571 (&ZI405);
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
      case 206: case 210: case 255:
	{
	    EXP ZI1023;

	    ZR420 (&ZI1023);
	    ZR1025 (&ZI1023, &ZI405);
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

	    ZR512 (&ZI417);
	    ZR517 (&ZI424);
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

	    ZR513 (&ZI417);
	    ZR517 (&ZI424);
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
ZR550(EXP ZI468, int ZI549, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_550:;
    {
	EXP ZI417;
	EXP ZI449;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) {
	if ( !(ZI549) ) report ( crt_loc, ERR_stmt_dcl_start () ) ;
	in_declaration++ ;
    }
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR561 ();
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
	goto ZL2_550;
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
      case 223: case 255: case 289: case 298: case 323:
      case 324: case 346:
	{
	    EXP ZI417;
	    EXP ZI449;
	    int ZI551;

	    ZR530 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI449) = add_compound_stmt ( (ZI468), (ZI417) ) ;
	    }
	    {
 (ZI551) = 0 ; 
	    }
	    ZI468 = ZI449;
	    ZI549 = ZI551;
	    goto ZL2_550;
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
ZR557(EXP ZI468, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    int ZI549;

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
    (ZI549) = 1 ;
	    }
	    ZR550 (ZI468, ZI549, &ZI405);
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
      case 255: case 289: case 298: case 323: case 324:
      case 346:
	{
	    EXP ZI417;

	    ZR556 (&ZI417);
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
ZR726(BASE_TYPE *ZI690, TYPE *ZI691, CV_SPEC *ZI692, DECL_SPEC *ZI718, BASE_TYPE *ZO660, TYPE *ZO396, CV_SPEC *ZO632, DECL_SPEC *ZO607)
{
    BASE_TYPE ZI660;
    TYPE ZI396;
    CV_SPEC ZI632;
    DECL_SPEC ZI607;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1099;
	TYPE ZI1100;
	CV_SPEC ZI1101;
	DECL_SPEC ZI1102;
	BASE_TYPE ZI694;
	TYPE ZI695;
	CV_SPEC ZI696;
	DECL_SPEC ZI720;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR716 (&ZI1099, &ZI1100, &ZI1101, &ZI1102);
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
	ZR726 (&ZI1099, &ZI1100, &ZI1101, &ZI1102, &ZI694, &ZI695, &ZI696, &ZI720);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI690) & (ZI694) ) {
	(ZI660) = join_pre_types ( (*ZI690), (ZI694) ) ;
    } else {
	(ZI660) = ( (*ZI690) | (ZI694) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI691) ) ) {
	(ZI396) = (ZI695) ;
    } else if ( IS_NULL_type ( (ZI695) ) ) {
	(ZI396) = (*ZI691) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI691), (ZI695) ) ) ;
	(ZI396) = (ZI695) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI692) & (ZI696) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI632) = ( (*ZI692) | (ZI696) ) ;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI718) & (ZI720) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI607) = ( (*ZI718) | (ZI720) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI660 = *ZI690;
	    ZI396 = *ZI691;
	    ZI632 = *ZI692;
	    ZI607 = *ZI718;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO660 = ZI660;
    *ZO396 = ZI396;
    *ZO632 = ZI632;
    *ZO607 = ZI607;
}

void
ZR530(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    ZR553 (&ZI405);
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
      case 255: case 289: case 298: case 323: case 324:
      case 346:
	{
	    ZR556 (&ZI405);
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
ZR761(TYPE *ZO861)
{
    TYPE ZI861;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1058 (&ZI861);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI400;
	    int ZI749;
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
	    ZR760 (&ZI749);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = make_func_type ( NULL_type, ( (ZI749) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR862 (ZI396, &ZI861);
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
	    ZR759 (&ZI405);
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
	    ZR862 (ZI396, &ZI861);
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
    *ZO861 = ZI861;
}

void
ZR985(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	int ZI474;
	EXP ZI417;
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
	EXP ZI953;
	EXP ZI950;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR445 (&ZI396, &ZI474);
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
    (ZI963) = make_cast_exp ( (ZI396), (ZI417), (ZI474) ) ;
	}
	ZR920 (ZI963, &ZI962);
	ZR916 (ZI962, &ZI961);
	ZR912 (ZI961, &ZI960);
	ZR908 (ZI960, &ZI959);
	ZR904 (ZI959, &ZI958);
	ZR900 (ZI958, &ZI957);
	ZR896 (ZI957, &ZI956);
	ZR892 (ZI956, &ZI955);
	ZR888 (ZI955, &ZI954);
	ZR884 (ZI954, &ZI953);
	ZR880 (ZI953, &ZI950);
	ZR952 (&ZI950, &ZI405);
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
      case 206: case 210: case 255: case 298: case 324:
      case 346:
	{
	    EXP ZI1070;
	    EXP ZI1071;
	    EXP ZI1072;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI1070);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1071) = make_paren_exp ( (ZI1070) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR924 (ZI1071, &ZI1072);
	    ZR1013 (&ZI1072, &ZI405);
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
ZR858(TYPE ZI854, IDENTIFIER ZI855, TYPE *ZO856, IDENTIFIER *ZO857)
{
    TYPE ZI856;
    IDENTIFIER ZI857;

  ZL2_858:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI424;
	    TYPE ZI396;

	    ZI400 = ZI855;
	    ZR756 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI854) ) ? (ZI424) : inject_pre_type ( (ZI854), (ZI424), 0 ) ) ;
	    }
	    ZI854 = ZI396;
	    ZI855 = ZI400;
	    goto ZL2_858;
	}
	/*UNREACHED*/
      default:
	{
	    ZI856 = ZI854;
	    ZI857 = ZI855;
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
    *ZO856 = ZI856;
    *ZO857 = ZI857;
}

void
ZR604(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 101:
	{
	    unsigned ZI583;
	    int ZI539;
	    EXP ZI417;
	    EXP ZI584;
	    EXP ZI449;
	    EXP ZI605;
	    EXP ZI468;

	    ADVANCE_LEXER;
	    {
 (ZI583) = crt_condition ; 
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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

    (ZI584) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR558 (ZI584, &ZI449);
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
	    ZR415 (&ZI605);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI468) = bind_temporary ( (ZI605) ) ;
	    }
	    {
 unreached_prev = (ZI539) ; 
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
 crt_condition = (ZI583) ; 
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
	    unsigned ZI583;
	    int ZI539;
	    EXP ZI587;
	    EXP ZI417;
	    EXP ZI606;
	    EXP ZI468;
	    EXP ZI607;
	    EXP ZI449;
	    EXP ZI608;
	    EXP ZI549;

	    ADVANCE_LEXER;
	    {
 (ZI583) = crt_condition ; 
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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

    (ZI587) = begin_for_stmt () ;
	    }
	    ZR600 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI606) = init_for_stmt ( (ZI587), &(ZI417) ) ;
	    }
	    ZR601 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI607) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR603 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI608) = cond_for_stmt ( (ZI606), (ZI468), (ZI449) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    mark_compound_stmt ( (ZI607) ) ;
	    }
	    ZR558 (ZI607, &ZI549);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI539) ; 
	    }
	    {

    (ZI405) = end_for_stmt ( (ZI608), (ZI549) ) ;
	    }
	    {
 crt_condition = (ZI583) ; 
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
	    unsigned ZI583;
	    int ZI539;
	    EXP ZI605;
	    EXP ZI468;
	    EXP ZI417;
	    EXP ZI584;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    {
 (ZI583) = crt_condition ; 
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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
	    ZR415 (&ZI605);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI468) = bind_temporary ( (ZI605) ) ;
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

    (ZI584) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR558 (ZI584, &ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI539) ; 
	    }
	    {

    (ZI405) = end_while_stmt ( (ZI417), (ZI449) ) ;
	    }
	    {
 crt_condition = (ZI583) ; 
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
ZR508(void)
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
ZR538(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 346:
	{
	    ADVANCE_LEXER;
	    ZR1080 (&ZI405);
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
      case 206: case 210: case 255:
	{
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ZR420 (&ZI1023);
	    ZR1025 (&ZI1023, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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
	    EXP ZI1075;
	    EXP ZI417;
	    int ZI539;

	    ZR512 (&ZI1075);
	    ZR1077 (&ZI1075, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
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
ZR836(OFFSET ZI449, TYPE ZI570, OFFSET *ZO417, TYPE *ZO396)
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

    (ZI427) = offset_nspace ( (ZI570) ) ;
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

    OFFSET off = offset_member ( (ZI570), (ZI400), &(ZI396), (ZI427), 1 ) ;
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
ZR808(void)
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

	    ZR807 (&ZI421);
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
			ZR806 ();
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
ZR862(TYPE ZI860, TYPE *ZO861)
{
    TYPE ZI861;

  ZL2_862:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    TYPE ZI424;
	    TYPE ZI396;

	    ZR756 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI860) ) ? (ZI424) : inject_pre_type ( (ZI860), (ZI424), 0 ) ) ;
	    }
	    ZI860 = ZI396;
	    goto ZL2_862;
	}
	/*UNREACHED*/
      default:
	{
	    ZI861 = ZI860;
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
    *ZO861 = ZI861;
}

void
parse_mem_type(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI660;
	TYPE ZI421;
	CV_SPEC ZI632;
	TYPE ZI424;

	ZR689 (&ZI660, &ZI421, &ZI632);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI424) = complete_pre_type ( (ZI660), (ZI421), (ZI632), 1 ) ;
    have_type_specifier = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 73:
		{
		    EXP ZI468;

		    ADVANCE_LEXER;
		    ZR520 (&ZI468);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI396) = make_bitfield_type ( (ZI424), (ZI660), (ZI468), 0 ) ;
		    }
		}
		break;
	      default:
		{
		    ZR762 (ZI424, &ZI396);
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
ZR870(TYPE ZI866, IDENTIFIER ZI867, TYPE *ZO868, IDENTIFIER *ZO869)
{
    TYPE ZI868;
    IDENTIFIER ZI869;

  ZL2_870:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI424;
	    TYPE ZI396;

	    ZI400 = ZI867;
	    ZR747 (ZI400, &ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI866) ) ? (ZI424) : inject_pre_type ( (ZI866), (ZI424), 0 ) ) ;
	    }
	    ZI866 = ZI396;
	    ZI867 = ZI400;
	    goto ZL2_870;
	}
	/*UNREACHED*/
      default:
	{
	    ZI868 = ZI866;
	    ZI869 = ZI867;
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
    *ZO868 = ZI868;
    *ZO869 = ZI869;
}

void
ZR617(EXP *ZO417)
{
    EXP ZI417;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255: case 298: case 324:
      case 346:
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
ZR499(EXP *ZO887)
{
    EXP ZI887;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR497 (&ZI405);
	ZR888 (ZI405, &ZI887);
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
    *ZO887 = ZI887;
}

void
ZR615(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI468;

	    ADVANCE_LEXER;
	    ZR520 (&ZI468);
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
ZR517(SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255:
	{
	    EXP ZI417;

	    ZR420 (&ZI417);
	    ZR1026 (&ZI417, &ZI421);
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

	    ZR512 (&ZI417);
	    ZR517 (&ZI424);
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

	    ZR513 (&ZI417);
	    ZR517 (&ZI424);
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
ZR745(int *ZO749)
{
    int ZI749;

  ZL2_745:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZI749) = 1 ; 
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
	    IDENTIFIER ZI549;

	    ZR772 (&ZI549);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			goto ZL2_745;
		    }
		    /*UNREACHED*/
		  default:
		    {
			{
 (ZI749) = 0 ; 
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
    *ZO749 = ZI749;
}

void
ZR876(EXP ZI874, EXP *ZO875)
{
    EXP ZI875;

  ZL2_876:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI421;
	    EXP ZI468;

	    ZI421 = ZI874;
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
	    ZR806 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI874 = ZI421;
		goto ZL2_876;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI875 = ZI874;
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
    *ZO875 = ZI875;
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
ZR779(IDENTIFIER *ZO400)
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
parse_decl(TYPE ZI396, DECL_SPEC ZI607)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI690;
	TYPE ZI1097;
	CV_SPEC ZI692;
	DECL_SPEC ZI1098;
	BASE_TYPE ZI660;
	TYPE ZI691;
	CV_SPEC ZI632;
	DECL_SPEC ZI718;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	ZR716 (&ZI690, &ZI1097, &ZI692, &ZI1098);
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
	ZR726 (&ZI690, &ZI1097, &ZI692, &ZI1098, &ZI660, &ZI691, &ZI632, &ZI718);
	ZR815 (&ZI660, &ZI691, &ZI632, &ZI718);
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
ZR497(EXP *ZO891)
{
    EXP ZI891;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR495 (&ZI405);
	ZR892 (ZI405, &ZI891);
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
    *ZO891 = ZI891;
}

void
ZR553(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	int ZI549;
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
    (ZI549) = 1 ;
	}
	ZR550 (ZI468, ZI549, &ZI417);
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
ZR880(EXP ZI878, EXP *ZO879)
{
    EXP ZI879;

  ZL2_880:;
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
	    ZR501 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_log_or_exp ( (ZI878), (ZI449) ) ;
	    }
	    ZI878 = ZI405;
	    goto ZL2_880;
	}
	/*UNREACHED*/
      default:
	{
	    ZI879 = ZI878;
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
    *ZO879 = ZI879;
}

void
ZR626(SID_LIST_EXP *ZO421)
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
ZR503(EXP *ZO879)
{
    EXP ZI879;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR501 (&ZI405);
	ZR880 (ZI405, &ZI879);
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
    *ZO879 = ZI879;
}

void
ZR520(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;

	ZR505 (&ZI417);
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
ZR733(TYPE *ZO421)
{
    TYPE ZI421;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	CV_SPEC ZI632;

	switch (CURRENT_TERMINAL) {
	  case 78:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR637 (&ZI632);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_type_ptr ( (ZI632), NULL_type, (ZI421) ) ;
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
ZR884(EXP ZI882, EXP *ZO883)
{
    EXP ZI883;

  ZL2_884:;
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
	    ZR499 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_log_and_exp ( (ZI882), (ZI449) ) ;
	    }
	    ZI882 = ZI405;
	    goto ZL2_884;
	}
	/*UNREACHED*/
      default:
	{
	    ZI883 = ZI882;
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
    *ZO883 = ZI883;
}

void
ZR757(TYPE *ZO570)
{
    TYPE ZI570;

    switch (CURRENT_TERMINAL) {
      case 2: case 25: case 47: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 137: case 156: case 185:
      case 286: case 299:
	{
	    int ZI749;

	    ZR745 (&ZI749);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI570) = make_func_type ( NULL_type, (ZI749), cv_c, empty_type_set ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI570) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
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
    *ZO570 = ZI570;
}

void
ZR490(EXP *ZO903)
{
    EXP ZI903;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR487 (&ZI405);
	ZR904 (ZI405, &ZI903);
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
    *ZO903 = ZI903;
}

void
ZR799(DECL_SPEC ZI607, BASE_TYPE ZI660, TYPE ZI396)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_799:;
    {
	ZR798 (ZI607, ZI660, ZI396);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_799;
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
ZR1013(EXP *ZI1012, EXP *ZO405)
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

    (ZI405) = make_assign_exp ( (*ZI1012), (ZI449), 1 ) ;
	    }
	}
	break;
      default:
	{
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
	    EXP ZI950;

	    ZR920 (*ZI1012, &ZI962);
	    ZR916 (ZI962, &ZI961);
	    ZR912 (ZI961, &ZI960);
	    ZR908 (ZI960, &ZI959);
	    ZR904 (ZI959, &ZI958);
	    ZR900 (ZI958, &ZI957);
	    ZR896 (ZI957, &ZI956);
	    ZR892 (ZI956, &ZI955);
	    ZR888 (ZI955, &ZI954);
	    ZR884 (ZI954, &ZI953);
	    ZR880 (ZI953, &ZI950);
	    ZR952 (&ZI950, &ZI405);
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
	    ZR508 ();
	    ZR420 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI405) = make_become_exp ( (ZI461), (*ZI1012), (ZI449) ) ;
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
ZR759(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255:
	{
	    ZR520 (&ZI405);
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
ZR760(int *ZO749)
{
    int ZI749;

    switch (CURRENT_TERMINAL) {
      case 2: case 25: case 47: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 137: case 156: case 185:
      case 286: case 299:
	{
	    ZR745 (&ZI749);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI749) = 0 ; 
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
    *ZO749 = ZI749;
}

void
ZR478(EXP *ZO919)
{
    EXP ZI919;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR460 (&ZI405);
	ZR920 (ZI405, &ZI919);
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
    *ZO919 = ZI919;
}

void
ZR888(EXP ZI886, EXP *ZO887)
{
    EXP ZI887;

  ZL2_888:;
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
	    ZR497 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_or_exp ( (ZI886), (ZI449) ) ;
	    }
	    ZI886 = ZI405;
	    goto ZL2_888;
	}
	/*UNREACHED*/
      default:
	{
	    ZI887 = ZI886;
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
    *ZO887 = ZI887;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
