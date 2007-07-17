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
ZR1129(OFFSET ZI457, TYPE ZI575, OFFSET *ZO1154, TYPE *ZO1155)
{
    OFFSET ZI1154;
    TYPE ZI1155;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1129:;
    {
	OFFSET ZI494;
	TYPE ZI415;

	ZR1128 (ZI457, ZI575, &ZI494, &ZI415);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZI457 = ZI494;
		    ZI575 = ZI415;
		    goto ZL2_1129;
		}
		/*UNREACHED*/
	      default:
		{
		    ZI1154 = ZI494;
		    ZI1155 = ZI415;
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
    *ZO1154 = ZI1154;
    *ZO1155 = ZI1155;
}

void
ZR1435(IDENTIFIER *ZI420, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    NAMESPACE ZI1049;
	    IDENTIFIER ZI1050;
	    IDENTIFIER ZI1051;
	    NAMESPACE ZI426;

	    ADVANCE_LEXER;
	    ZR429 (&ZI1049);
	    ZR509 (&ZI1050);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1051) = check_id ( (ZI1049), (ZI1050), 0 ) ;
    last_namespace = (ZI1049) ;
	    }
	    {

    (ZI426) = find_nspace_id ( (ZI1051) ) ;
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    alias_namespace ( (*ZI420), (ZI426) ) ;
	    }
	    ZR419 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = NULL_exp ;
	    }
	}
	break;
      case 64:
	{
	    DECL_SPEC ZI691;
	    TYPE ZI415;

	    {

    begin_namespace ( (*ZI420), 0 ) ;
	    }
	    {
 (ZI691) = dspec_none ; 
	    }
	    {

    (ZI415) = NULL_type ;
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
	    ZR1029 (ZI415, ZI691);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_namespace ( 0 ) ;
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
	    {

    RESCAN_LEXER ;
	    }
	    {

    (ZI432) = NULL_exp ;
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
ZR474(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 9:
	{
	    ZR504 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    ZR503 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 83:
	{
	    ZR505 (&ZI420);
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
    *ZO420 = ZI420;
}

void
ZR993(TYPE *ZO415)
{
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI498;
	TYPE ZI481;

	{

    /* Resolve pointer declarators from expressions */
    (ZI0) = predict_ptr ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR928 (&ZI498);
	ZR993 (&ZI481);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 0 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 66:
	{
	    ZR992 (&ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI415) = NULL_type ;
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
}

void
ZR1031(EXP *ZO1146)
{
    EXP ZI1146;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI559;
	EXP ZI498;

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

    target_decl ( lex_if, (ZI559) ) ;
	}
	ZR1030 ();
	ZR1147 (ZI498, &ZI1146);
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
    *ZO1146 = ZI1146;
}

void
ZR942(TYPE *ZO415, IDENTIFIER *ZO420, int *ZO559)
{
    TYPE ZI415;
    IDENTIFIER ZI420;
    int ZI559;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 65:
      case 83: case 141:
	{
	    ZR951 (&ZI415, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI498;
	    TYPE ZI481;

	    ZR928 (&ZI498);
	    ZR942 (&ZI481, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 0 ) ) ;
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
    *ZO415 = ZI415;
    *ZO420 = ZI420;
    *ZO559 = ZI559;
}

void
ZR613(EXP *ZO1225)
{
    EXP ZI1225;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR610 (&ZI432);
	ZR1226 (ZI432, &ZI1225);
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
    *ZO1225 = ZI1225;
}

void
ZR738(EXP *ZO494, EXP *ZO432)
{
    EXP ZI494;
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI460;
	EXP ZI1602;
	EXP ZI559;

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
	ZR651 (&ZI1602);
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

    int def = init_object ( (ZI460), (ZI1602) ) ;
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

    (ZI559) = end_cond () ;
    in_declaration-- ;
	}
	{

    (ZI494) = bind_temporary ( (ZI559) ) ;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI494), (ZI432) ) ;
	}
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
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI494) = NULL_exp ;
	    }
	    {

    MAKE_exp_location ( type_void, crt_loc, (ZI494), (ZI432) ) ;
	    }
	}
	break;
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
	    EXP ZI559;

	    ZR492 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = bind_temporary ( (ZI559) ) ;
	    }
	    {

    MAKE_exp_location ( type_void, crt_loc, (ZI494), (ZI432) ) ;
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
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO494 = ZI494;
    *ZO432 = ZI432;
}

void
ZR989(TYPE *ZO415)
{
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI498;
	TYPE ZI481;

	{

    /* Resolve pointer or reference declarators from expressions */
    (ZI0) = predict_ptr ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR928 (&ZI498);
	ZR989 (&ZI481);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 0 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    (ZI415) = NULL_type ;
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
}

void
ZR1438(EXP *ZI1436, EXP *ZO432)
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
      case 255: case 286: case 298: case 299: case 324:
      case 330: case 346:
	{
	    SID_LIST_EXP ZI481;
	    SID_LIST_EXP ZI498;

	    ZR650 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1436), (ZI481), (ZI498) ) ;
	    }
	    {

    (ZI432) = make_comma_exp ( (ZI498) ) ;
	    }
	}
	break;
      default:
	{
	    ZI432 = *ZI1436;
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
ZR865(IDENTIFIER ZI432)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI866;
	IDENTIFIER ZI420;
	EXP ZI559;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI866 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    {

    ZI866 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI866 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI866 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI420) = (ZI866) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI420) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR1085 (&ZI559);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IDENTIFIER id = constr_name ( last_namespace, (ZI420) ) ;
    IGNORE make_enumerator ( (ZI432), id, (ZI559) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR952(TYPE ZI498, TYPE *ZO415, IDENTIFIER *ZO420, int *ZO559)
{
    TYPE ZI415;
    IDENTIFIER ZI420;
    int ZI559;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI481;

	ZR942 (&ZI481, &ZI420, &ZI559);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( !IS_NULL_type ( (ZI498) ) ) template_decl ( (ZI498) ) ;
	}
	{

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
    *ZO420 = ZI420;
    *ZO559 = ZI559;
}

void
ZR1006(int ZI559, IDENTIFIER ZI460, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	SID_LIST_EXP ZI498;

	{

    (ZI0) = (ZI559) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    if ( crt_lex_token == lex_open_Hinit ) {
	crt_lex_token = lex_open_Hround ;
    } else {
	RESCAN_LEXER ;
    }
	}
	ZR1004 (ZI460, &ZI498);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_exp_initialiser ( type_void, (ZI498), NULL_list ( OFFSET ), 0, 0, 0, (ZI432) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR1000 (ZI460, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI432) = NULL_exp ;
	    }
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

void
parse_file(TYPE ZI415, DECL_SPEC ZI691)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1250;
	TYPE ZI1251;
	CV_SPEC ZI1252;
	DECL_SPEC ZI1253;
	BASE_TYPE ZI512;
	TYPE ZI877;
	CV_SPEC ZI878;
	DECL_SPEC ZI911;
	DECL_SPEC ZI913;
	EXP ZI432;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR908 (ZI415, &ZI1250, &ZI1251, &ZI1252, &ZI1253);
	ZR919 (&ZI415, &ZI1250, &ZI1251, &ZI1252, &ZI1253, &ZI512, &ZI877, &ZI878, &ZI911);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI691) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI913) = ( (ZI691) | (ZI911) ) ;
	}
	ZR1254 (&ZI415, &ZI512, &ZI877, &ZI878, &ZI913);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = NULL_exp ;
	}
	{

    external_declaration ( (ZI432), 1 ) ;
	}
	ZR1029 (ZI415, ZI691);
	switch (CURRENT_TERMINAL) {
	  case 32:
	    break;
	  case 355:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 105:
	{
	    EXP ZI432;

	    ZR1064 (ZI415, ZI691, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
	    }
	    ZR1029 (ZI415, ZI691);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      case 134: case 147:
	{
	    EXP ZI432;

	    ZR1074 (ZI415, ZI691, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
	    }
	    ZR1029 (ZI415, ZI691);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 77: case 78:
      case 83: case 141:
	{
	    BASE_TYPE ZI512;
	    TYPE ZI877;
	    CV_SPEC ZI1255;
	    EXP ZI432;

	    {
 (ZI512) = btype_none ; 
	    }
	    {

    (ZI877) = NULL_type ;
	    }
	    {
 (ZI1255) = cv_none ; 
	    }
	    ZR1256 (&ZI415, &ZI691, &ZI512, &ZI877, &ZI1255, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
	    }
	    ZR1029 (ZI415, ZI691);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      case 26: case 30: case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI691) ) ;
	    }
	    ZR1257 ();
	    ZR1029 (ZI415, ZI691);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    /* Unrecoverable syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    err = concat_error ( err, ERR_lex_abort () ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
    }
  ZL0:;
}

void
ZR1026(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI559;
	EXP ZI494;

	{

    (ZI559) = begin_compound_stmt ( 1 ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 41: case 64:
		{
		    ZR1024 (ZI559, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 151:
		{
		    EXP ZI457;

		    ZR1025 (&ZI457);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI457) ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
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
ZR1112(int *ZO716)
{
    int ZI716;

    switch (CURRENT_TERMINAL) {
      case 134:
	{
	    ADVANCE_LEXER;
	    {
 (ZI716) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI716) = 0 ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *ZO716 = ZI716;
}

void
parse_offset(OFFSET ZI457, TYPE ZI575, OFFSET *ZO494, TYPE *ZO415)
{
    OFFSET ZI494;
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	OFFSET ZI559;
	TYPE ZI1130;

	ZR1127 (ZI457, ZI575, &ZI559, &ZI1130);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZR1129 (ZI559, ZI1130, &ZI494, &ZI415);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    ZI494 = ZI559;
		    ZI415 = ZI1130;
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
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	ZI494 = ZI457;
	ZI415 = ZI575;
    }
  ZL0:;
    *ZO494 = ZI494;
    *ZO415 = ZI415;
}

void
parse_nat(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR653 (&ZI432);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI432) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1441(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI1599;
	    EXP ZI1600;

	    ADVANCE_LEXER;
	    ZR492 (&ZI1599);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1600) = make_set_exp ( (ZI1599) ) ;
	    }
	    ZR1601 (&ZI1600, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 324:
	{
	    EXP ZI1596;
	    EXP ZI1597;

	    ADVANCE_LEXER;
	    ZR492 (&ZI1596);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1597) = make_unused_exp ( (ZI1596) ) ;
	    }
	    ZR1601 (&ZI1597, &ZI432);
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
    *ZO432 = ZI432;
}

void
ZR1314(NAMESPACE *ZI426, IDENTIFIER *ZI1312, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI521;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    ADVANCE_LEXER;
	    {
 (ZI521) = btype_none ; 
	    }
	    ZI522 = *ZI426;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
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
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (*ZI1312), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
	    }
	}
	break;
      default:
	{
	    ZI420 = *ZI1312;
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
    *ZO420 = ZI420;
}

void
ZR651(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR497 (&ZI432);
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
    *ZO432 = ZI432;
}

void
parse_param(TYPE ZI575, int ZI498, IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR973 (ZI575, ZI498, &ZI460);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI460) = NULL_id ;
	}
    }
  ZL0:;
    *ZO460 = ZI460;
}

void
ZR1442(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI559;
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR653 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = begin_case_stmt ( (ZI559), 0 ) ;
	    }
	    {

    unreached_fall = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR663 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_case_stmt ( (ZI494), (ZI457) ) ;
	    }
	}
	break;
      case 100:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {

    (ZI494) = begin_default_stmt ( 0 ) ;
	    }
	    {

    unreached_fall = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR663 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_default_stmt ( (ZI494), (ZI457) ) ;
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
ZR1315(NAMESPACE *ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    NAMESPACE ZI1397;
	    IDENTIFIER ZI1398;

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

    (ZI1397) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI1397) ;
	    }
	    {

    (ZI1398) = check_id ( (ZI1397), (ZI461), 0 ) ;
    last_namespace = (ZI1397) ;
	    }
	    ZR1400 (ZI426, &ZI1398, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 43:
      case 141: case 147:
	{
	    NAMESPACE ZI1395;

	    {

    (ZI1395) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI1395) ;
	    }
	    ZR1396 (&ZI1395, &ZI420);
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
    *ZO420 = ZI420;
}

void
ZR875(BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI575;
	BASE_TYPE ZI876;
	TYPE ZI877;
	CV_SPEC ZI878;

	{

    (ZI575) = NULL_type ;
	}
	ZR874 (ZI575, &ZI876, &ZI877, &ZI878);
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 7: case 8: case 9: case 25:
	      case 83: case 97: case 98: case 102: case 104:
	      case 106: case 110: case 111: case 114: case 115:
	      case 118: case 121: case 122: case 123: case 124:
	      case 127: case 129: case 153: case 156: case 185:
	      case 286: case 299:
		{
		    BASE_TYPE ZI880;
		    TYPE ZI881;
		    CV_SPEC ZI882;

		    ZR875 (&ZI880, &ZI881, &ZI882);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI876) & (ZI880) ) {
	(ZI512) = join_pre_types ( (ZI876), (ZI880) ) ;
    } else {
	(ZI512) = ( (ZI876) | (ZI880) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI877) ) ) {
	(ZI415) = (ZI881) ;
    } else if ( IS_NULL_type ( (ZI881) ) ) {
	(ZI415) = (ZI877) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI877), (ZI881) ) ) ;
	(ZI415) = (ZI881) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI878) & (ZI882) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI785) = ( (ZI878) | (ZI882) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI512 = ZI876;
		    ZI415 = ZI877;
		    ZI785 = ZI878;
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
    *ZO512 = ZI512;
    *ZO415 = ZI415;
    *ZO785 = ZI785;
}

void
ZR503(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	NAMESPACE ZI426;
	IDENTIFIER ZI461;

	switch (CURRENT_TERMINAL) {
	  case 8:
	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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
    qual_namespace = (ZI426) ;
	}
	{

    (ZI420) = check_id ( (ZI426), (ZI461), 0 ) ;
    last_namespace = (ZI426) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR1106(SID_LIST_TYPE *ZO498)
{
    SID_LIST_TYPE ZI498;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI575;
	int ZI552;
	TYPE ZI415;
	SID_LIST_TYPE ZI481;

	ZR549 (&ZI575, &ZI552);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI415) = check_except_type ( (ZI575), (ZI552) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1386 (&ZI481);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI481) = NULL_list ( TYPE ) ;
		    }
		}
		break;
	    }
	}
	{

    (ZI498) = cons_type_set ( (ZI481), (ZI415) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO498 = ZI498;
}

void
ZR1317(NAMESPACE *ZI426, NAMESPACE *ZI1316, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI1401;
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI1402;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1401 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1401 = crt_token->pp_data.id.use ;
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
    qual_namespace = (*ZI1316) ;
	    }
	    {

    (ZI461) = check_id ( (*ZI1316), (ZI1401), 0 ) ;
    last_namespace = (*ZI1316) ;
	    }
	    {

    (ZI1402) = check_id ( (*ZI426), (ZI461), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	    ZR1404 (ZI426, &ZI1402, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI519;

	    ZR476 (*ZI1316, &ZI481);
	    ZR477 (*ZI1316, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1316) ;
	    }
	    {

    (ZI519) = check_id ( (*ZI1316), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI1316) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI426), (ZI519), 0 ) ;
    last_namespace = (*ZI426) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI520;
	    BASE_TYPE ZI521;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1316) ;
	    }
	    {

    (ZI520) = DEREF_id ( nspace_name ( (*ZI1316) ) ) ;
	    }
	    {
 (ZI521) = btype_none ; 
	    }
	    ZI522 = *ZI1316;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
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
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (ZI520), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
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
ZR1190(EXP ZI1184, EXP ZI1185, int ZI1186, EXP *ZO1187, EXP *ZO1188, int *ZO1189)
{
    EXP ZI1187;
    EXP ZI1188;
    int ZI1189;

  ZL2_1190:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI498;
	    int ZI672;
	    EXP ZI559;
	    int ZI575;
	    EXP ZI457;
	    EXP ZI432;

	    ZI498 = ZI1185;
	    ZI672 = ZI1186;
	    {

    ZI559 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI559), c ) ;
	    }
	    {

    (ZI575) = unreached_code ;
    if ( (ZI575) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR680 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI672) ; 
	    }
	    {

    (ZI432) = cont_hash_if_stmt ( (ZI1184), (ZI559), (ZI457) ) ;
	    }
	    ZI1184 = ZI432;
	    ZI1185 = ZI498;
	    ZI1186 = ZI672;
	    goto ZL2_1190;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1187 = ZI1184;
	    ZI1188 = ZI1185;
	    ZI1189 = ZI1186;
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
    *ZO1187 = ZI1187;
    *ZO1188 = ZI1188;
    *ZO1189 = ZI1189;
}

void
ZR485(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1610 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI426;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1609 (&ZI426, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI426;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1608 (&ZI426, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4:
	{
	    IDENTIFIER ZI479;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = (ZI479) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
	{
	    ZR478 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 7:
	{
	    ZR473 (&ZI420);
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
    *ZO420 = ZI420;
}

void
ZR953(TYPE *ZO415)
{
    TYPE ZI415;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    ZR956 (&ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI1382;

	    ZR928 (&ZI1382);
	    ZR1384 (&ZI1382, &ZI415);
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
    *ZO415 = ZI415;
}

void
parse_func(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR1026 (&ZI432);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI432) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR517(IDENTIFIER *ZO420, BASE_TYPE *ZO512)
{
    IDENTIFIER ZI420;
    BASE_TYPE ZI512;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
	{
	    ZR509 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 185: case 286: case 299:
	{
	    ZR510 (&ZI512);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
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
    *ZO512 = ZI512;
}

void
ZR835(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI691;
	TYPE ZI415;

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
 (ZI691) = dspec_none ; 
	}
	{

    (ZI415) = NULL_type ;
	}
	ZR834 (ZI415, ZI691);
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
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1319(NAMESPACE *ZI426, NAMESPACE *ZI1318, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI1405;

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
    qual_namespace = (*ZI1318) ;
	    }
	    {

    (ZI1405) = check_id ( (*ZI1318), (ZI461), 0 ) ;
    last_namespace = (*ZI1318) ;
	    }
	    ZR1407 (ZI426, &ZI1405, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI1318, &ZI481);
	    ZR477 (*ZI1318, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI1318) ;
	    }
	    {

    (ZI420) = check_id ( (*ZI1318), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI1318) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI520;
	    BASE_TYPE ZI521;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI1318) ;
	    }
	    {

    (ZI520) = DEREF_id ( nspace_name ( (*ZI1318) ) ) ;
	    }
	    {
 (ZI521) = btype_none ; 
	    }
	    ZI522 = *ZI1318;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
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
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (ZI520), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
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
ZR505(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI461;
	NAMESPACE ZI426;

	switch (CURRENT_TERMINAL) {
	  case 83:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR896(DECL_SPEC *ZO691)
{
    DECL_SPEC ZI691;

    switch (CURRENT_TERMINAL) {
      case 94:
	{
	    ADVANCE_LEXER;
	    {
 (ZI691) = dspec_auto ; 
	    }
	}
	break;
      case 105:
	{
	    ADVANCE_LEXER;
	    {
 (ZI691) = dspec_extern ; 
	    }
	}
	break;
      case 138:
	{
	    ADVANCE_LEXER;
	    {
 (ZI691) = dspec_mutable ; 
	    }
	}
	break;
      case 112:
	{
	    ADVANCE_LEXER;
	    {
 (ZI691) = dspec_register ; 
	    }
	}
	break;
      case 117:
	{
	    ADVANCE_LEXER;
	    {
 (ZI691) = dspec_static ; 
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
    *ZO691 = ZI691;
}

void
parse_id(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR485 (&ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	}
    }
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR1321(int *ZI451)
{
    switch (CURRENT_TERMINAL) {
      case 33: case 34: case 35: case 36: case 42:
      case 43: case 44: case 45: case 48: case 49:
      case 50: case 53: case 54: case 55: case 56:
      case 57: case 58: case 59: case 60: case 61:
      case 62: case 63: case 67: case 68: case 69:
      case 70: case 71: case 73: case 74: case 75:
      case 76: case 78: case 79: case 80: case 81:
      case 82: case 85: case 86: case 87:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 85:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 35:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 82:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 36:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 42:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 44:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 45:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 48:
		    {
			ADVANCE_LEXER;
		    }
		    break;
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
		  case 57:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 58:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 86:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 87:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 59:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 60:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 61:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 69:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 70:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 71:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 73:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 74:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 75:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 76:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 78:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 79:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 33:
		    {
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
		  case 55:
		    {
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
		    }
		    break;
		  case 56:
		    {
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
		    }
		    break;
		  case 62:
		    {
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
		    }
		    break;
		  case 63:
		    {
			{
			    {
				switch (CURRENT_TERMINAL) {
				  case 63:
				    break;
				  default:
				    goto ZL1;
				}
				ADVANCE_LEXER;
			    }
			}
		    }
		    break;
		  case 67:
		    {
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
		  case 80:
		    {
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
		  default:
		    goto ZL1;
		}
	    }
	}
	break;
      case 41: case 46: case 83: case 84: case 116:
      case 152: case 170: case 330:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 170:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 41:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 83:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 46:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 84:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 116:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 152:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 330:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    /* Illegal overloaded operator */
    report ( crt_loc, ERR_over_oper_bad ( (*ZI451) ) ) ;
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
ZR1194(EXP ZI1192, EXP *ZO1193)
{
    EXP ZI1193;

  ZL2_1194:;
    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    EXP ZI457;
	    EXP ZI432;

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
	    ZR630 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_log_or_exp ( (ZI1192), (ZI457) ) ;
	    }
	    ZI1192 = ZI432;
	    goto ZL2_1194;
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
ZR1322(int *ZO451)
{
    int ZI451;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	{

    /* Resolve 'operator new []' from 'operator new [3]' */
    (ZI0) = predict_array () ;
	}
	if (!ZI0)
	    goto ZL2;
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
	ZR416 ();
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI451) = lex_new_Harray ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {
 (ZI451) = lex_new ; 
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO451 = ZI451;
}

void
ZR582(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI451;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_alignof ; 
	    }
	    ZR594 (ZI451, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1286 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1281;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1242 (ZI1281, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 25:
	{
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1284;

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
	    ZR1242 (ZI1284, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	{
	    TYPE ZI415;
	    EXP ZI494;
	    int ZI552;
	    EXP ZI1273;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI494, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZI415), (ZI494), (ZI552) ) ;
	    }
	    ZR1242 (ZI1273, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 206:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_cast_exp ( type_void, (ZI494), 0 ) ;
	    }
	}
	break;
      case 132:
	{
	    TYPE ZI415;
	    EXP ZI494;
	    int ZI552;
	    EXP ZI1276;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI494, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZI415), (ZI494), (ZI552) ) ;
	    }
	    ZR1242 (ZI1276, &ZI432);
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
	    {

    (ZI1279) = make_ellipsis_exp () ;
	    }
	    ZR1242 (ZI1279, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI426;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1269 (&ZI426, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 255:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_lit_exp ( (ZI494) ) ;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_prefix_exp ( lex_minus_Hminus, (ZI494) ) ;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI426;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1268 (&ZI426, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1288 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_prefix_exp ( lex_plus_Hplus, (ZI494) ) ;
	    }
	}
	break;
      case 145:
	{
	    TYPE ZI415;
	    EXP ZI494;
	    int ZI552;
	    EXP ZI1274;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI494, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZI415), (ZI494), (ZI552) ) ;
	    }
	    ZR1242 (ZI1274, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 116:
	{
	    int ZI451;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_sizeof ; 
	    }
	    ZR594 (ZI451, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_indir_exp ( (ZI494) ) ;
	    }
	}
	break;
      case 146:
	{
	    TYPE ZI415;
	    EXP ZI494;
	    int ZI552;
	    EXP ZI1275;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI494, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1275) = make_static_cast_exp ( (ZI415), (ZI494), (ZI552) ) ;
	    }
	    ZR1242 (ZI1275, &ZI432);
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
	    {

    (ZI1278) = make_this_exp () ;
	    }
	    ZR1242 (ZI1278, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 152:
	{
	    int ZI451;
	    EXP ZI1272;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_typeid ; 
	    }
	    ZR554 (ZI451, &ZI1272);
	    ZR1242 (ZI1272, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 330:
	{
	    int ZI451;
	    EXP ZI1271;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_vtable ; 
	    }
	    ZR554 (ZI451, &ZI1271);
	    ZR1242 (ZI1271, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI494;

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
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_ref_exp ( (ZI494), 0 ) ;
	    }
	}
	break;
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
	    ZR1242 (ZI1282, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
	{
	    EXP ZI1277;

	    ZR438 (&ZI1277);
	    ZR1242 (ZI1277, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI494;

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
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_not_exp ( (ZI494) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
	{
	    IDENTIFIER ZI420;
	    EXP ZI1285;

	    ZR478 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1283;

	    ZR473 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
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
	    ZR1242 (ZI1283, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI457;

	    {
 (ZI457) = 0 ; 
	    }
	    ZR1432 (&ZI457, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI451;
	    EXP ZI494;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR597 ();
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_uminus_exp ( (ZI451), (ZI494) ) ;
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
ZR874(TYPE ZI575, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;

    switch (CURRENT_TERMINAL) {
      case 104:
	{
	    ADVANCE_LEXER;
	    ZR1327 (&ZI575, &ZI512, &ZI415, &ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 153:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI420;

	    ADVANCE_LEXER;
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR429 (&ZI426);
	    ZR509 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = make_typename ( (ZI426), (ZI420) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
	found_elaborate_type = 1 ;
    }
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	}
	break;
      case 118: case 121: case 129:
	{
	    BASE_TYPE ZI818;

	    ZR819 (&ZI818);
	    ZR1326 (&ZI575, &ZI818, &ZI512, &ZI415, &ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 98: case 124:
	{
	    ZR786 (&ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {

    (ZI415) = NULL_type ;
	    }
	}
	break;
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 102: case 106: case 110:
      case 111: case 114: case 115: case 122: case 123:
      case 127: case 156: case 185: case 286: case 299:
	{
	    ZR810 (&ZI512, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI785) = cv_none ; 
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
    *ZO512 = ZI512;
    *ZO415 = ZI415;
    *ZO785 = ZI785;
}

void
ZR943(int *ZO947)
{
    int ZI947;

    switch (CURRENT_TERMINAL) {
      case 2: case 7: case 8: case 9: case 25:
      case 47: case 83: case 94: case 97: case 98:
      case 102: case 104: case 105: case 106: case 110:
      case 111: case 112: case 114: case 115: case 117:
      case 118: case 120: case 121: case 122: case 123:
      case 124: case 127: case 129: case 133: case 136:
      case 137: case 138: case 153: case 155: case 156:
      case 185: case 275: case 286: case 299:
	{
	    ZR977 (&ZI947);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI947) = 0 ; 
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
    *ZO947 = ZI947;
}

void
ZR957(TYPE ZI498, TYPE *ZO415)
{
    TYPE ZI415;

    switch (CURRENT_TERMINAL) {
      case 10: case 11: case 33: case 65: case 66:
      case 78: case 332:
	{
	    TYPE ZI481;

	    ZR953 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI415 = ZI498;
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
ZR1323(int *ZO451)
{
    int ZI451;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	{

    /* Resolve 'operator new []' from 'operator new [3]' */
    (ZI0) = predict_array () ;
	}
	if (!ZI0)
	    goto ZL2;
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
	ZR416 ();
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI451) = lex_delete_Harray ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {
 (ZI451) = lex_delete ; 
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO451 = ZI451;
}

void
ZR418(void)
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
	int ZI415;

	{
 (ZI415) = lex_open_Hround ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI415) ) report ( crt_loc, ERR_lex_expect ( (ZI415) ) ) ;
	}
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
	    EXP ZI457;
	    EXP ZI432;

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
	    ZR628 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_log_and_exp ( (ZI1196), (ZI457) ) ;
	    }
	    ZI1196 = ZI432;
	    goto ZL2_1198;
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
ZR868(IDENTIFIER ZI432)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_868:;
    {
	ZR865 (ZI432);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 42:
			    {
				ADVANCE_LEXER;
				{

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
				}
				goto ZL2_868;
			    }
			    /*UNREACHED*/
			  case 1: case 2: case 3: case 4:
			    {
				goto ZL2_868;
			    }
			    /*UNREACHED*/
			  default:
			    {
				{

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
				}
			    }
			    break;
			}
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
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1326(TYPE *ZI575, BASE_TYPE *ZI818, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI420;
	QUALIFIER ZI858;
	int ZI456;
	DECL_SPEC ZI457;
	IDENTIFIER ZI498;
	int ZI722;
	int ZI1324;
	DECL_SPEC ZI691;
	TYPE ZI1325;
	IDENTIFIER ZI559;

	{

    /* Resolve class-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    crt_templ_qualifier = 0 ;
	}
	ZR871 (&ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI858) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	}
	{

    if ( !IS_NULL_type ( (*ZI575) ) ) template_decl ( (*ZI575) ) ;
	}
	{
 (ZI457) = crt_access ; 
	}
	{

    IDENTIFIER id = constr_name ( last_namespace, (ZI420) ) ;
    (ZI498) = begin_class_defn ( id, (*ZI818), cinfo_none, (*ZI575) ) ;
    (ZI722) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
	}
	ZR849 (&ZI1324);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    end_base_class ( crt_class, (ZI1324) ) ;
	}
	{
 (ZI691) = dspec_none ; 
	}
	{

    (ZI1325) = NULL_type ;
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
	ZR834 (ZI1325, ZI691);
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

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
	}
	{

    (ZI559) = end_class_defn ( (ZI498) ) ;
    in_function_defn = (ZI722) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
	}
	{
 crt_access = (ZI457) ; 
	}
	{

    crt_id_qualifier = (ZI858) ;
    crt_templ_qualifier = (ZI456) ;
	}
	{

    RESCAN_LEXER ;
	}
	{

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI415) ) ;
    COPY_id ( type_name ( (ZI415) ), (ZI559) ) ;
    have_type_specifier = 1 ;
	}
	{
 (ZI512) = btype_none ; 
	}
	{
 (ZI785) = cv_none ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI822;
	    IDENTIFIER ZI420;

	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR429 (&ZI426);
	    ZR509 (&ZI822);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI822), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    MAKE_type_pre ( cv_none, (*ZI818), crt_id_qualifier, (ZI415) ) ;
    COPY_id ( type_name ( (ZI415) ), (ZI420) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
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
    *ZO512 = ZI512;
    *ZO415 = ZI415;
    *ZO785 = ZI785;
}

void
ZR737(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI691;
	TYPE ZI415;
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
 (ZI691) = dspec_none ; 
	}
	{

    (ZI415) = NULL_type ;
	}
	ZR688 (ZI415, ZI691);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI494) = NULL_exp ;
	}
	{

    (ZI432) = (ZI494) ;
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
      case 62: case 65: case 69: case 71: case 77:
      case 78: case 83: case 85: case 97: case 102:
      case 106: case 110: case 111: case 114: case 115:
      case 116: case 122: case 123: case 127: case 130:
      case 131: case 132: case 135: case 140: case 141:
      case 145: case 146: case 148: case 149: case 150:
      case 152: case 156: case 170: case 185: case 206:
      case 210: case 255: case 286: case 298: case 299:
      case 324: case 330: case 346:
	{
	    ZR671 (&ZI432);
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
ZR1025(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI672;
	EXP ZI494;
	EXP ZI457;
	EXP ZI722;
	EXP ZI559;
	EXP ZI460;

	switch (CURRENT_TERMINAL) {
	  case 151:
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

    (ZI494) = begin_try_stmt ( 1 ) ;
	}
	{

    (ZI457) = begin_compound_stmt ( 1 ) ;
	}
	{

    inject_try_stmt ( (ZI494) ) ;
	}
	ZR1024 (ZI457, &ZI722);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI559) = end_compound_stmt ( (ZI722) ) ;
	}
	{

    (ZI460) = cont_try_stmt ( (ZI494), (ZI559) ) ;
	}
	ZR772 (ZI460);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI672) ; 
	}
	{

    (ZI432) = end_try_stmt ( (ZI460), 0 ) ;
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
ZR1128(OFFSET ZI457, TYPE ZI575, OFFSET *ZO494, TYPE *ZO415)
{
    OFFSET ZI494;
    TYPE ZI415;

    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    ADVANCE_LEXER;
	    ZR1127 (ZI457, ZI575, &ZI494, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI432;

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
	    ZR653 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    OFFSET off = offset_index ( (ZI575), (ZI432), &(ZI415) ) ;
    (ZI494) = offset_add ( (ZI457), off ) ;
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
    *ZO494 = ZI494;
    *ZO415 = ZI415;
}

void
ZR1327(TYPE *ZI575, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI420;
	QUALIFIER ZI858;
	int ZI456;
	IDENTIFIER ZI498;
	IDENTIFIER ZI432;

	{

    /* Resolve enum-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    crt_templ_qualifier = 0 ;
	}
	ZR871 (&ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI858) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	}
	{

    IDENTIFIER id = constr_name ( last_namespace, (ZI420) ) ;
    (ZI498) = begin_enum_defn ( id, (*ZI575) ) ;
    no_type_defns++ ;
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
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 3: case 4:
		{
		    ZR868 (ZI498);
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
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
	}
	{

    (ZI432) = end_enum_defn ( (ZI498) ) ;
	}
	{

    crt_id_qualifier = (ZI858) ;
    crt_templ_qualifier = (ZI456) ;
	}
	{

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI415) ) ;
    COPY_id ( type_name ( (ZI415) ), (ZI432) ) ;
    have_type_specifier = 1 ;
	}
	{
 (ZI512) = btype_none ; 
	}
	{
 (ZI785) = cv_none ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    BASE_TYPE ZI818;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI822;
	    IDENTIFIER ZI420;

	    {
 (ZI818) = btype_enum ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR429 (&ZI426);
	    ZR509 (&ZI822);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI822), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    MAKE_type_pre ( cv_none, (ZI818), crt_id_qualifier, (ZI415) ) ;
    COPY_id ( type_name ( (ZI415) ), (ZI420) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
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
    *ZO512 = ZI512;
    *ZO415 = ZI415;
    *ZO785 = ZI785;
}

void
ZR616(EXP *ZO1221)
{
    EXP ZI1221;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR613 (&ZI432);
	ZR1222 (ZI432, &ZI1221);
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
ZR840(TYPE ZI415, DECL_SPEC ZI691)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1337;
	TYPE ZI1338;
	CV_SPEC ZI1339;
	DECL_SPEC ZI1340;
	BASE_TYPE ZI512;
	TYPE ZI877;
	CV_SPEC ZI878;
	DECL_SPEC ZI911;
	DECL_SPEC ZI913;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR908 (ZI415, &ZI1337, &ZI1338, &ZI1339, &ZI1340);
	ZR919 (&ZI415, &ZI1337, &ZI1338, &ZI1339, &ZI1340, &ZI512, &ZI877, &ZI878, &ZI911);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI691) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI913) = ( (ZI691) | (ZI911) ) ;
	}
	ZR1341 (&ZI415, &ZI512, &ZI877, &ZI878, &ZI913);
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
	    ZR1091 (ZI415, ZI691);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 41: case 65: case 78:
      case 83: case 141:
	{
	    BASE_TYPE ZI512;
	    TYPE ZI877;
	    CV_SPEC ZI878;
	    DECL_SPEC ZI911;
	    DECL_SPEC ZI913;
	    TYPE ZI881;
	    DECL_SPEC ZI1075;
	    TYPE ZI1076;
	    ACCESS_LIST ZI672;
	    int ZI722;
	    IDENTIFIER ZI460;

	    {
 (ZI512) = btype_none ; 
	    }
	    {

    (ZI877) = NULL_type ;
	    }
	    {
 (ZI878) = cv_none ; 
	    }
	    {
 (ZI911) = dspec_none ; 
	    }
	    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI691) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI913) = ( (ZI691) | (ZI911) ) ;
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI1075) = complete_dspec ( (ZI913), (ZI512), (ZI877), (ZI878) ) ;
    (ZI881) = complete_pre_type ( (ZI512), (ZI877), (ZI878), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1076) = ( IS_NULL_type ( (ZI415) ) ? (ZI881) : inject_pre_type ( (ZI415), (ZI881), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI672) ) ;
	    }
	    {
 (ZI722) = 1 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1086 (ZI1075, ZI1076, ZI512, ZI672, ZI722, &ZI460);
	    ZR1094 (&ZI512, &ZI1075, &ZI1076, &ZI672, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI691) ) ;
	    }
	    ZR1054 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 77:
	{
	    TYPE ZI877;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI878;

	    {

    (ZI877) = NULL_type ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI878) = cv_none ; 
	    }
	    {

    IGNORE empty_decl ( (ZI691), (ZI415), (ZI512), (ZI877), (ZI878), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
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

/* END OF FILE */
