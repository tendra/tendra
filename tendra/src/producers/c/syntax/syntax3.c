/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/producers/c/syntax/syntax.sid
 * and
 *	/u/g/release/Source/src/producers/c/syntax/syntax.act
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
ZR1092 PROTO_N ((ZI1091, ZO404))
  PROTO_T (EXP *ZI1091 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 346:
	{
	    SID_LIST_EXP ZI423;
	    SID_LIST_EXP ZI420;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1091), (ZI423), (ZI420) ) ;
	    }
	    {

    (ZI416) = make_comma_exp ( (ZI420) ) ;
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_exp_stmt ( (ZI416) ) ;
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
	    int ZI537;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 346:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_exp_stmt ( (*ZI1091) ) ;
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
    *ZO404 = ZI404;
}

void
ZR1093 PROTO_Z ()
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
ZR635 PROTO_N ((ZO630))
  PROTO_T (CV_SPEC *ZO630)
{
    CV_SPEC ZI630;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR632 (&ZI630);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI630) = cv_none ; 
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
    *ZO630 = ZI630;
}

void
ZR529 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 222:
	{
	    ADVANCE_LEXER;
	    ZR1093 ();
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
ZR631 PROTO_N ((ZO630))
  PROTO_T (CV_SPEC *ZO630)
{
    CV_SPEC ZI630;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (ZI630) = cv_const ; 
	    }
	}
	break;
      case 124:
	{
	    ADVANCE_LEXER;
	    {
 (ZI630) = cv_volatile ; 
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
    *ZO630 = ZI630;
}

void
ZR469 PROTO_Z ()
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
ZR824 PROTO_N ((ZI420, ZI423))
  PROTO_T (TYPE ZI420 X BASE_TYPE ZI423)
{
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI1038;
	    IDENTIFIER ZI1039;
	    TYPE ZI1035;
	    IDENTIFIER ZI399;
	    TYPE ZI395;

	    ADVANCE_LEXER;
	    ZR742 (&ZI1038, &ZI1039);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI1038) ) ) {
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
	    ZR868 (ZI1038, ZI1039, &ZI1035, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI1035) ) ? (ZI420) : inject_pre_type ( (ZI1035), (ZI420), 1 ) ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI395), (ZI399), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      case 1: case 2: case 4:
	{
	    IDENTIFIER ZI1042;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI1042 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI1042 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1042 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZR1043 (&ZI420, &ZI423, &ZI1042);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1036;
	    TYPE ZI1037;
	    IDENTIFIER ZI399;
	    TYPE ZI1035;
	    TYPE ZI395;

	    ZR731 (&ZI1036);
	    ZR742 (&ZI1037, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1035) = ( IS_NULL_type ( (ZI1037) ) ? (ZI1036) : inject_pre_type ( (ZI1037), (ZI1036), 0 ) ) ;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI1035) ) ? (ZI420) : inject_pre_type ( (ZI1035), (ZI420), 1 ) ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI395), (ZI399), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      case 41:
	{
	    IDENTIFIER ZI399;
	    EXP ZI467;
	    TYPE ZI395;

	    {

    HASHID nm = lookup_anon () ;
    (ZI399) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ADVANCE_LEXER;
	    ZR518 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZI399) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI395) = make_bitfield_type ( (ZI420), (ZI423), (ZI467), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI395), (ZI399), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
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
ZR788 PROTO_N ((ZI547, ZO404))
  PROTO_T (IDENTIFIER ZI547 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209:
	{
	    ZR516 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 64:
	{
	    SID_LIST_EXP ZI420;

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
	    ZR1072 (&ZI547, &ZI420);
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
    MAKE_exp_aggregate ( type_void, (ZI420), NULL_list ( OFFSET ), (ZI404) ) ;
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
    *ZO404 = ZI404;
}

void
ZR479 PROTO_N ((ZO913))
  PROTO_T (EXP *ZO913)
{
    EXP ZI913;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR476 (&ZI404);
	ZR914 (ZI404, &ZI913);
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
    *ZO913 = ZI913;
}

void
ZR751 PROTO_N ((ZO866, ZO867))
  PROTO_T (TYPE *ZO866 X IDENTIFIER *ZO867)
{
    TYPE ZI866;
    IDENTIFIER ZI867;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI395;
	    IDENTIFIER ZI399;

	    ADVANCE_LEXER;
	    ZR742 (&ZI395, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI395) ) ) {
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
	    ZR868 (ZI395, ZI399, &ZI866, &ZI867);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 2: case 4:
	{
	    IDENTIFIER ZI399;
	    TYPE ZI395;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI395) = NULL_type ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR868 (ZI395, ZI399, &ZI866, &ZI867);
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
    *ZO866 = ZI866;
    *ZO867 = ZI867;
}

void
ZR580 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 109:
	{
	    unsigned ZI581;
	    int ZI537;
	    EXP ZI467;
	    EXP ZI416;
	    EXP ZI582;
	    EXP ZI448;
	    EXP ZI547;
	    EXP ZI585;

	    ADVANCE_LEXER;
	    {
 (ZI581) = crt_condition ; 
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR394 ();
	    ZR414 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI416) = begin_if_stmt ( (ZI467) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI582) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR556 (ZI582, &ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI547) = cont_if_stmt ( (ZI416), (ZI448) ) ;
	    }
	    {
		{
		    EXP ZI584;

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

    (ZI584) = begin_compound_stmt ( 1 ) ;
		    }
		    ZR556 (ZI584, &ZI585);
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
    (ZI585) = NULL_exp ;
		    }
		}
	      ZL2:;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI404) = end_if_stmt ( (ZI547), (ZI585) ) ;
	    }
	    {
 crt_condition = (ZI581) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 119:
	{
	    int ZI537;
	    EXP ZI467;
	    EXP ZI416;
	    int ZI587;
	    EXP ZI582;
	    EXP ZI448;

	    ADVANCE_LEXER;
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
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
	    ZR414 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI416) = begin_switch_stmt ( (ZI467) ) ;
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
 (ZI587) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI587) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI582) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR556 (ZI582, &ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI404) = end_switch_stmt ( (ZI416), (ZI448), (ZI587) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	}
	break;
      case 26:
	{
	    ZR569 (&ZI404);
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
    *ZO404 = ZI404;
}

void
ZR414 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209:
	{
	    EXP ZI1025;

	    ZR419 (&ZI1025);
	    ZR1027 (&ZI1025, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 297: case 323:
	{
	    EXP ZI416;
	    SID_LIST_EXP ZI423;
	    SID_LIST_EXP ZI420;

	    ZR510 (&ZI416);
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI416), (ZI423), (ZI420) ) ;
	    }
	    {

    (ZI404) = make_comma_exp ( (ZI420) ) ;
	    }
	}
	break;
      case 345:
	{
	    EXP ZI416;
	    SID_LIST_EXP ZI423;
	    SID_LIST_EXP ZI420;

	    ZR511 (&ZI416);
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI416), (ZI423), (ZI420) ) ;
	    }
	    {

    (ZI404) = make_comma_exp ( (ZI420) ) ;
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
    *ZO404 = ZI404;
}

void
ZR548 PROTO_N ((ZI467, ZI547, ZO404))
  PROTO_T (EXP ZI467 X int ZI547 X EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_548:;
    {
	EXP ZI416;
	EXP ZI448;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) {
	if ( !(ZI547) ) report ( crt_loc, ERR_stmt_dcl_start () ) ;
	in_declaration++ ;
    }
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR559 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    in_declaration-- ;
    (ZI416) = NULL_exp ;
	}
	{

    unreached_fall = 1 ;
	}
	{

    (ZI448) = add_compound_stmt ( (ZI467), (ZI416) ) ;
	}
	ZI467 = ZI448;
	goto ZL2_548;
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
      case 125: case 126: case 170: case 205: case 209:
      case 222: case 288: case 297: case 322: case 323:
      case 345:
	{
	    EXP ZI416;
	    EXP ZI448;
	    int ZI549;

	    ZR528 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI448) = add_compound_stmt ( (ZI467), (ZI416) ) ;
	    }
	    {
 (ZI549) = 0 ; 
	    }
	    ZI467 = ZI448;
	    ZI547 = ZI549;
	    goto ZL2_548;
	}
	/*UNREACHED*/
      default:
	{
	    ZI404 = ZI467;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR724 PROTO_N ((ZI688, ZI689, ZI690, ZI716, ZO658, ZO395, ZO630, ZO605))
  PROTO_T (BASE_TYPE *ZI688 X TYPE *ZI689 X CV_SPEC *ZI690 X DECL_SPEC *ZI716 X BASE_TYPE *ZO658 X TYPE *ZO395 X CV_SPEC *ZO630 X DECL_SPEC *ZO605)
{
    BASE_TYPE ZI658;
    TYPE ZI395;
    CV_SPEC ZI630;
    DECL_SPEC ZI605;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI1096;
	TYPE ZI1097;
	CV_SPEC ZI1098;
	DECL_SPEC ZI1099;
	BASE_TYPE ZI692;
	TYPE ZI693;
	CV_SPEC ZI694;
	DECL_SPEC ZI718;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR714 (&ZI1096, &ZI1097, &ZI1098, &ZI1099);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	ZR724 (&ZI1096, &ZI1097, &ZI1098, &ZI1099, &ZI692, &ZI693, &ZI694, &ZI718);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI688) & (ZI692) ) {
	(ZI658) = join_pre_types ( (*ZI688), (ZI692) ) ;
    } else {
	(ZI658) = ( (*ZI688) | (ZI692) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI689) ) ) {
	(ZI395) = (ZI693) ;
    } else if ( IS_NULL_type ( (ZI693) ) ) {
	(ZI395) = (*ZI689) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI689), (ZI693) ) ) ;
	(ZI395) = (ZI693) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI690) & (ZI694) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI630) = ( (*ZI690) | (ZI694) ) ;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI716) & (ZI718) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI605) = ( (*ZI716) | (ZI718) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI658 = *ZI688;
	    ZI395 = *ZI689;
	    ZI630 = *ZI690;
	    ZI605 = *ZI716;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO658 = ZI658;
    *ZO395 = ZI395;
    *ZO630 = ZI630;
    *ZO605 = ZI605;
}

void
ZR555 PROTO_N ((ZI467, ZO404))
  PROTO_T (EXP ZI467 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    int ZI547;

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

    COPY_int ( exp_sequence_block ( (ZI467) ), 2 ) ;
    (ZI547) = 1 ;
	    }
	    ZR548 (ZI467, ZI547, &ZI404);
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
	}
	break;
      case 1: case 2: case 4: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 24: case 26: case 33: case 43: case 59:
      case 61: case 62: case 65: case 69: case 71:
      case 77: case 78: case 85: case 95: case 96:
      case 99: case 100: case 101: case 107: case 108:
      case 109: case 113: case 116: case 119: case 125:
      case 126: case 170: case 205: case 209: case 222:
      case 288: case 297: case 322: case 323: case 345:
	{
	    EXP ZI416;

	    ZR554 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = add_compound_stmt ( (ZI467), (ZI416) ) ;
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
    *ZO404 = ZI404;
}

void
ZR528 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    ZR551 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
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
      case 126: case 170: case 205: case 209: case 222:
      case 288: case 297: case 322: case 323: case 345:
	{
	    ZR554 (&ZI404);
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
    *ZO404 = ZI404;
}

void
ZR983 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI395;
	int ZI472;
	EXP ZI416;
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
	EXP ZI951;
	EXP ZI948;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR444 (&ZI395, &ZI472);
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
	ZR459 (&ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* n is the number of type definitions in t */
    (ZI961) = make_cast_exp ( (ZI395), (ZI416), (ZI472) ) ;
	}
	ZR918 (ZI961, &ZI960);
	ZR914 (ZI960, &ZI959);
	ZR910 (ZI959, &ZI958);
	ZR906 (ZI958, &ZI957);
	ZR902 (ZI957, &ZI956);
	ZR898 (ZI956, &ZI955);
	ZR894 (ZI955, &ZI954);
	ZR890 (ZI954, &ZI953);
	ZR886 (ZI953, &ZI952);
	ZR882 (ZI952, &ZI951);
	ZR878 (ZI951, &ZI948);
	ZR950 (&ZI948, &ZI404);
	if ((CURRENT_TERMINAL) == 354) {
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
      case 205: case 209: case 297: case 323: case 345:
	{
	    EXP ZI1021;
	    EXP ZI1022;
	    EXP ZI1023;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR414 (&ZI1021);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1022) = make_paren_exp ( (ZI1021) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR922 (ZI1022, &ZI1023);
	    ZR1014 (&ZI1023, &ZI404);
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
    *ZO404 = ZI404;
}

void
ZR856 PROTO_N ((ZI852, ZI853, ZO854, ZO855))
  PROTO_T (TYPE ZI852 X IDENTIFIER ZI853 X TYPE *ZO854 X IDENTIFIER *ZO855)
{
    TYPE ZI854;
    IDENTIFIER ZI855;

  ZL2_856:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    IDENTIFIER ZI399;
	    TYPE ZI423;
	    TYPE ZI395;

	    ZI399 = ZI853;
	    ZR754 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI852) ) ? (ZI423) : inject_pre_type ( (ZI852), (ZI423), 0 ) ) ;
	    }
	    ZI852 = ZI395;
	    ZI853 = ZI399;
	    goto ZL2_856;
	}
	/*UNREACHED*/
      default:
	{
	    ZI854 = ZI852;
	    ZI855 = ZI853;
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
    *ZO854 = ZI854;
    *ZO855 = ZI855;
}

void
ZR759 PROTO_N ((ZO859))
  PROTO_T (TYPE *ZO859)
{
    TYPE ZI859;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1060 (&ZI859);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI399;
	    int ZI747;
	    TYPE ZI395;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI399) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI399) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR758 (&ZI747);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = make_func_type ( NULL_type, ( (ZI747) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR860 (ZI395, &ZI859);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI404;
	    TYPE ZI395;

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
	    ZR757 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI404) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI395) ) ;
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
	    ZR860 (ZI395, &ZI859);
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
    *ZO859 = ZI859;
}

void
ZR602 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 101:
	{
	    unsigned ZI581;
	    int ZI537;
	    EXP ZI416;
	    EXP ZI582;
	    EXP ZI448;
	    EXP ZI603;
	    EXP ZI467;

	    ADVANCE_LEXER;
	    {
 (ZI581) = crt_condition ; 
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI416) = begin_do_stmt () ;
	    }
	    {

    (ZI582) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR556 (ZI582, &ZI448);
	    switch (CURRENT_TERMINAL) {
	      case 125:
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
	    ZR414 (&ZI603);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI467) = bind_temporary ( (ZI603) ) ;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI404) = end_do_stmt ( (ZI416), (ZI448), (ZI467) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 crt_condition = (ZI581) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR396 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 107:
	{
	    unsigned ZI581;
	    int ZI537;
	    EXP ZI585;
	    EXP ZI416;
	    EXP ZI604;
	    EXP ZI467;
	    EXP ZI605;
	    EXP ZI448;
	    EXP ZI606;
	    EXP ZI547;

	    ADVANCE_LEXER;
	    {
 (ZI581) = crt_condition ; 
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
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

    (ZI585) = begin_for_stmt () ;
	    }
	    ZR598 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI604) = init_for_stmt ( (ZI585), &(ZI416) ) ;
	    }
	    ZR599 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI605) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR601 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI606) = cond_for_stmt ( (ZI604), (ZI467), (ZI448) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    mark_compound_stmt ( (ZI605) ) ;
	    }
	    ZR556 (ZI605, &ZI547);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI404) = end_for_stmt ( (ZI606), (ZI547) ) ;
	    }
	    {
 crt_condition = (ZI581) ; 
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
	    unsigned ZI581;
	    int ZI537;
	    EXP ZI603;
	    EXP ZI467;
	    EXP ZI416;
	    EXP ZI582;
	    EXP ZI448;

	    ADVANCE_LEXER;
	    {
 (ZI581) = crt_condition ; 
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
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
	    ZR414 (&ZI603);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI467) = bind_temporary ( (ZI603) ) ;
	    }
	    {

    (ZI416) = begin_while_stmt ( (ZI467) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI582) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR556 (ZI582, &ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI404) = end_while_stmt ( (ZI416), (ZI448) ) ;
	    }
	    {
 crt_condition = (ZI581) ; 
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
    *ZO404 = ZI404;
}

void
ZR506 PROTO_Z ()
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
ZR860 PROTO_N ((ZI858, ZO859))
  PROTO_T (TYPE ZI858 X TYPE *ZO859)
{
    TYPE ZI859;

  ZL2_860:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    TYPE ZI423;
	    TYPE ZI395;

	    ZR754 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI858) ) ? (ZI423) : inject_pre_type ( (ZI858), (ZI423), 0 ) ) ;
	    }
	    ZI858 = ZI395;
	    goto ZL2_860;
	}
	/*UNREACHED*/
      default:
	{
	    ZI859 = ZI858;
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
    *ZO859 = ZI859;
}

void
ZR536 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 345:
	{
	    ADVANCE_LEXER;
	    ZR1078 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI404) = NULL_exp ;
	    }
	}
	break;
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209:
	{
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ZR419 (&ZI1025);
	    ZR1027 (&ZI1025, &ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_exp_stmt ( (ZI416) ) ;
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
      case 297: case 323:
	{
	    EXP ZI1073;
	    EXP ZI416;
	    int ZI537;

	    ZR510 (&ZI1073);
	    ZR1075 (&ZI1073, &ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_exp_stmt ( (ZI416) ) ;
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
    *ZO404 = ZI404;
}

void
ZR834 PROTO_N ((ZI448, ZI568, ZO416, ZO395))
  PROTO_T (OFFSET ZI448 X TYPE ZI568 X OFFSET *ZO416 X TYPE *ZO395)
{
    OFFSET ZI416;
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	NAMESPACE ZI426;
	IDENTIFIER ZI399;

	{

    (ZI426) = offset_nspace ( (ZI568) ) ;
	}
	{

    RESCAN_LEXER ;
	}
	ZR427 (ZI426, &ZI399);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    OFFSET off = offset_member ( (ZI568), (ZI399), &(ZI395), (ZI426), 1 ) ;
    (ZI416) = offset_add ( (ZI448), off ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO416 = ZI416;
    *ZO395 = ZI395;
}

void
ZR806 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	{
	    EXP ZI420;

	    ZR805 (&ZI420);
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
			ZR804 ();
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

    crt_hash_cond = (ZI420) ;
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
ZR868 PROTO_N ((ZI864, ZI865, ZO866, ZO867))
  PROTO_T (TYPE ZI864 X IDENTIFIER ZI865 X TYPE *ZO866 X IDENTIFIER *ZO867)
{
    TYPE ZI866;
    IDENTIFIER ZI867;

  ZL2_868:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    IDENTIFIER ZI399;
	    TYPE ZI423;
	    TYPE ZI395;

	    ZI399 = ZI865;
	    ZR745 (ZI399, &ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI864) ) ? (ZI423) : inject_pre_type ( (ZI864), (ZI423), 0 ) ) ;
	    }
	    ZI864 = ZI395;
	    ZI865 = ZI399;
	    goto ZL2_868;
	}
	/*UNREACHED*/
      default:
	{
	    ZI866 = ZI864;
	    ZI867 = ZI865;
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
    *ZO866 = ZI866;
    *ZO867 = ZI867;
}

void
ZR615 PROTO_N ((ZO416))
  PROTO_T (EXP *ZO416)
{
    EXP ZI416;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209: case 297: case 323: case 345:
	{
	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI416) = NULL_exp ;
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
    *ZO416 = ZI416;
}

void
parse_mem_type PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI658;
	TYPE ZI420;
	CV_SPEC ZI630;
	TYPE ZI423;

	ZR687 (&ZI658, &ZI420, &ZI630);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI423) = complete_pre_type ( (ZI658), (ZI420), (ZI630), 1 ) ;
    have_type_specifier = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 73:
		{
		    EXP ZI467;

		    ADVANCE_LEXER;
		    ZR518 (&ZI467);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI395) = make_bitfield_type ( (ZI423), (ZI658), (ZI467), 0 ) ;
		    }
		}
		break;
	      default:
		{
		    ZR760 (ZI423, &ZI395);
		    if ((CURRENT_TERMINAL) == 354) {
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
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO395 = ZI395;
}

void
parse_operator PROTO_N ((ZO399))
  PROTO_T (IDENTIFIER *ZO399)
{
    IDENTIFIER ZI399;

    if ((CURRENT_TERMINAL) == 354) {
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

    (ZI399) = NULL_id ;
	}
    }
    *ZO399 = ZI399;
}

void
ZR497 PROTO_N ((ZO885))
  PROTO_T (EXP *ZO885)
{
    EXP ZI885;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR495 (&ZI404);
	ZR886 (ZI404, &ZI885);
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
    *ZO885 = ZI885;
}

void
ZR874 PROTO_N ((ZI872, ZO873))
  PROTO_T (EXP ZI872 X EXP *ZO873)
{
    EXP ZI873;

  ZL2_874:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI420;
	    EXP ZI467;

	    ZI420 = ZI872;
	    {

    ZI467 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI467), c ) ;
	    }
	    {

    target_decl ( lex_elif, (ZI467) ) ;
	    }
	    ZR804 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI872 = ZI420;
		goto ZL2_874;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI873 = ZI872;
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
    *ZO873 = ZI873;
}

void
ZR613 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI467;

	    ADVANCE_LEXER;
	    ZR518 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_case ) ) ;
    (ZI404) = begin_case_stmt ( (ZI467), 1 ) ;
	    }
	}
	break;
      case 100:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_default ) ) ;
    (ZI404) = begin_default_stmt ( 1 ) ;
	    }
	}
	break;
      case 1: case 2: case 4:
	{
	    IDENTIFIER ZI399;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI404) = make_goto_stmt ( (ZI399) ) ;
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
    *ZO404 = ZI404;
}

void
ZR515 PROTO_N ((ZO420))
  PROTO_T (SID_LIST_EXP *ZO420)
{
    SID_LIST_EXP ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209:
	{
	    EXP ZI416;

	    ZR419 (&ZI416);
	    ZR1028 (&ZI416, &ZI420);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 297: case 323:
	{
	    EXP ZI416;
	    SID_LIST_EXP ZI423;

	    ZR510 (&ZI416);
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI416), (ZI423), (ZI420) ) ;
	    }
	}
	break;
      case 345:
	{
	    EXP ZI416;
	    SID_LIST_EXP ZI423;

	    ZR511 (&ZI416);
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI416), (ZI423), (ZI420) ) ;
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
    *ZO420 = ZI420;
}

void
ZR743 PROTO_N ((ZO747))
  PROTO_T (int *ZO747)
{
    int ZI747;

  ZL2_743:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZI747) = 1 ; 
	    }
	}
	break;
      case 2: case 25: case 94: case 97: case 98:
      case 102: case 104: case 105: case 106: case 110:
      case 111: case 112: case 114: case 115: case 117:
      case 118: case 120: case 121: case 122: case 123:
      case 124: case 137: case 156: case 184: case 285:
      case 298:
	{
	    IDENTIFIER ZI547;

	    ZR770 (&ZI547);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			goto ZL2_743;
		    }
		    /*UNREACHED*/
		  default:
		    {
			{
 (ZI747) = 0 ; 
			}
		    }
		    break;
		  case 354:
		    RESTORE_LEXER;
		    goto ZL1;
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
    *ZO747 = ZI747;
}

void
ZR409 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 17: case 18:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 17:
		    {
			{

    ZI404 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			{

    ZI404 = crt_token->pp_data.exp ;
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

    ZI404 = crt_token->pp_data.exp ;
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

    ZI404 = crt_token->pp_data.exp ;
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

    ZI404 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    ZI404 = crt_token->pp_data.exp ;
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
    *ZO404 = ZI404;
}

void
ZR777 PROTO_N ((ZO399))
  PROTO_T (IDENTIFIER *ZO399)
{
    IDENTIFIER ZI399;

    switch (CURRENT_TERMINAL) {
      case 2:
	{
	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_dcl_fct_par_typedef ( (ZI399) ) ) ;
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

    ZI399 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI399 = crt_token->pp_data.id.use ;
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
    *ZO399 = ZI399;
}

void
parse_decl PROTO_N ((ZI395, ZI605))
  PROTO_T (TYPE ZI395 X DECL_SPEC ZI605)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI688;
	TYPE ZI1094;
	CV_SPEC ZI690;
	DECL_SPEC ZI1095;
	BASE_TYPE ZI658;
	TYPE ZI689;
	CV_SPEC ZI630;
	DECL_SPEC ZI716;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	ZR714 (&ZI688, &ZI1094, &ZI690, &ZI1095);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	ZR724 (&ZI688, &ZI1094, &ZI690, &ZI1095, &ZI658, &ZI689, &ZI630, &ZI716);
	ZR813 (&ZI658, &ZI689, &ZI630, &ZI716);
	switch (CURRENT_TERMINAL) {
	  case 77:
	    break;
	  case 354:
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
ZR878 PROTO_N ((ZI876, ZO877))
  PROTO_T (EXP ZI876 X EXP *ZO877)
{
    EXP ZI877;

  ZL2_878:;
    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    EXP ZI448;
	    EXP ZI404;

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
	    ZR499 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_log_or_exp ( (ZI876), (ZI448) ) ;
	    }
	    ZI876 = ZI404;
	    goto ZL2_878;
	}
	/*UNREACHED*/
      default:
	{
	    ZI877 = ZI876;
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
    *ZO877 = ZI877;
}

void
ZR624 PROTO_N ((ZO420))
  PROTO_T (SID_LIST_EXP *ZO420)
{
    SID_LIST_EXP ZI420;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    ZR421 (&ZI420);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI420) = NULL_list ( EXP ) ;
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
    *ZO420 = ZI420;
}

void
ZR495 PROTO_N ((ZO889))
  PROTO_T (EXP *ZO889)
{
    EXP ZI889;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR493 (&ZI404);
	ZR890 (ZI404, &ZI889);
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
    *ZO889 = ZI889;
}

void
ZR551 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI467;
	int ZI547;
	EXP ZI416;

	{

    (ZI467) = begin_compound_stmt ( 1 ) ;
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

    COPY_int ( exp_sequence_block ( (ZI467) ), 2 ) ;
    (ZI547) = 1 ;
	}
	ZR548 (ZI467, ZI547, &ZI416);
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

    (ZI404) = end_compound_stmt ( (ZI416) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR396 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
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
	int ZI395;

	{
 (ZI395) = lex_semicolon ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI395) ) report ( crt_loc, ERR_lex_expect ( (ZI395) ) ) ;
	}
    }
}

void
ZR501 PROTO_N ((ZO877))
  PROTO_T (EXP *ZO877)
{
    EXP ZI877;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR499 (&ZI404);
	ZR878 (ZI404, &ZI877);
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
    *ZO877 = ZI877;
}

void
ZR518 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI416;

	ZR503 (&ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI404) = convert_reference ( (ZI416), REF_NORMAL ) ;
    (ZI404) = convert_lvalue ( (ZI404) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR882 PROTO_N ((ZI880, ZO881))
  PROTO_T (EXP ZI880 X EXP *ZO881)
{
    EXP ZI881;

  ZL2_882:;
    switch (CURRENT_TERMINAL) {
      case 55:
	{
	    EXP ZI448;
	    EXP ZI404;

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
	    ZR497 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_log_and_exp ( (ZI880), (ZI448) ) ;
	    }
	    ZI880 = ZI404;
	    goto ZL2_882;
	}
	/*UNREACHED*/
      default:
	{
	    ZI881 = ZI880;
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
    *ZO881 = ZI881;
}

void
ZR755 PROTO_N ((ZO568))
  PROTO_T (TYPE *ZO568)
{
    TYPE ZI568;

    switch (CURRENT_TERMINAL) {
      case 2: case 25: case 47: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 137: case 156: case 184:
      case 285: case 298:
	{
	    int ZI747;

	    ZR743 (&ZI747);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI568) = make_func_type ( NULL_type, (ZI747), cv_c, empty_type_set ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI568) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
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
    *ZO568 = ZI568;
}

void
ZR731 PROTO_N ((ZO420))
  PROTO_T (TYPE *ZO420)
{
    TYPE ZI420;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	CV_SPEC ZI630;

	switch (CURRENT_TERMINAL) {
	  case 78:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR635 (&ZI630);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_type_ptr ( (ZI630), NULL_type, (ZI420) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR757 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209:
	{
	    ZR518 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI404) = NULL_exp ;
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
    *ZO404 = ZI404;
}

void
ZR488 PROTO_N ((ZO901))
  PROTO_T (EXP *ZO901)
{
    EXP ZI901;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR485 (&ZI404);
	ZR902 (ZI404, &ZI901);
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
    *ZO901 = ZI901;
}

void
ZR797 PROTO_N ((ZI605, ZI658, ZI395))
  PROTO_T (DECL_SPEC ZI605 X BASE_TYPE ZI658 X TYPE ZI395)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_797:;
    {
	ZR796 (ZI605, ZI658, ZI395);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_797;
		}
		/*UNREACHED*/
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR758 PROTO_N ((ZO747))
  PROTO_T (int *ZO747)
{
    int ZI747;

    switch (CURRENT_TERMINAL) {
      case 2: case 25: case 47: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 137: case 156: case 184:
      case 285: case 298:
	{
	    ZR743 (&ZI747);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI747) = 0 ; 
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
    *ZO747 = ZI747;
}

void
ZR886 PROTO_N ((ZI884, ZO885))
  PROTO_T (EXP ZI884 X EXP *ZO885)
{
    EXP ZI885;

  ZL2_886:;
    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    EXP ZI448;
	    EXP ZI404;

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
	    ZR495 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_or_exp ( (ZI884), (ZI448) ) ;
	    }
	    ZI884 = ZI404;
	    goto ZL2_886;
	}
	/*UNREACHED*/
      default:
	{
	    ZI885 = ZI884;
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
    *ZO885 = ZI885;
}

void
ZR1014 PROTO_N ((ZI1013, ZO404))
  PROTO_T (EXP *ZI1013 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    EXP ZI448;

	    ADVANCE_LEXER;
	    ZR419 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_assign_exp ( (*ZI1013), (ZI448), 1 ) ;
	    }
	}
	break;
      default:
	{
	    EXP ZI960;
	    EXP ZI959;
	    EXP ZI958;
	    EXP ZI957;
	    EXP ZI956;
	    EXP ZI955;
	    EXP ZI954;
	    EXP ZI953;
	    EXP ZI952;
	    EXP ZI951;
	    EXP ZI948;

	    ZR918 (*ZI1013, &ZI960);
	    ZR914 (ZI960, &ZI959);
	    ZR910 (ZI959, &ZI958);
	    ZR906 (ZI958, &ZI957);
	    ZR902 (ZI957, &ZI956);
	    ZR898 (ZI956, &ZI955);
	    ZR894 (ZI955, &ZI954);
	    ZR890 (ZI954, &ZI953);
	    ZR886 (ZI953, &ZI952);
	    ZR882 (ZI952, &ZI951);
	    ZR878 (ZI951, &ZI948);
	    ZR950 (&ZI948, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 34: case 45: case 58: case 60: case 68:
      case 70: case 74: case 76: case 79: case 81:
	{
	    int ZI460;
	    EXP ZI448;

	    {
 (ZI460) = crt_lex_token ; 
	    }
	    ZR506 ();
	    ZR419 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI404) = make_become_exp ( (ZI460), (*ZI1013), (ZI448) ) ;
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
    *ZO404 = ZI404;
}

void
ZR476 PROTO_N ((ZO917))
  PROTO_T (EXP *ZO917)
{
    EXP ZI917;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR459 (&ZI404);
	ZR918 (ZI404, &ZI917);
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
    *ZO917 = ZI917;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
