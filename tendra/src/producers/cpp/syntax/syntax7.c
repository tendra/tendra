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
parse_mem_type(TYPE *ZO415)
{
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI512;
	TYPE ZI498;
	CV_SPEC ZI785;
	TYPE ZI481;

	ZR875 (&ZI512, &ZI498, &ZI785);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI481) = complete_pre_type ( (ZI512), (ZI498), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 73:
		{
		    QUALIFIER ZI456;
		    int ZI457;
		    EXP ZI559;

		    ADVANCE_LEXER;
		    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
		    }
		    ZR653 (&ZI559);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI415) = make_bitfield_type ( (ZI481), (ZI512), (ZI559), 0 ) ;
		    }
		    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
		    }
		}
		break;
	      default:
		{
		    ZR957 (ZI481, &ZI415);
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
    *ZO415 = ZI415;
}

void
ZR871(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI822;

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
	}
	break;
      default:
	{
	    {

    HASHID nm = lookup_anon () ;
    (ZI420) = DEREF_id ( hashid_id ( nm ) ) ;
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
    *ZO420 = ZI420;
}

void
parse_operator(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	QUALIFIER ZI456;
	int ZI457;
	int ZI458;
	IDENTIFIER ZI461;

	switch (CURRENT_TERMINAL) {
	  case 141:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	}
	{

    (ZI458) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
	}
	{
	    {
		TYPE ZI1320;
		BASE_TYPE ZI876;
		TYPE ZI877;
		CV_SPEC ZI878;
		BASE_TYPE ZI512;
		TYPE ZI498;
		CV_SPEC ZI785;
		TYPE ZI575;
		TYPE ZI481;
		TYPE ZI415;
		int ZI460;

		{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL3;
		{

    (ZI1320) = NULL_type ;
		}
		ZR874 (ZI1320, &ZI876, &ZI877, &ZI878);
		ZR887 (&ZI876, &ZI877, &ZI878, &ZI512, &ZI498, &ZI785);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI575) = complete_pre_type ( (ZI512), (ZI498), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
		}
		ZR989 (&ZI481);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI575) : inject_pre_type ( (ZI481), (ZI575), 1 ) ) ;
		}
		{

    int td = have_type_declaration ;
    (ZI460) = 0 ;
    if ( td != TYPE_DECL_NONE ) {
	if ( td == TYPE_DECL_ELABORATE && found_elaborate_type ) {
	    /* This is allowed */
	    /* EMPTY */
	} else {
	    (ZI460) = 1 ;
	}
    }
    have_type_declaration = (ZI458) ;
		}
		{

    HASHID nm = lookup_conv ( (ZI415) ) ;
    if ( (ZI460) ) report ( crt_loc, ERR_class_conv_fct_typedef ( nm ) ) ;
    (ZI461) = DEREF_id ( hashid_id ( nm ) ) ;
    set_hashid_loc ( (ZI461), underlying_op ) ;
		}
		goto ZL2;
	    }
	    /*UNREACHED*/
	  ZL3:;
	    switch (CURRENT_TERMINAL) {
	      case 33: case 34: case 35: case 36: case 41:
	      case 42: case 43: case 44: case 45: case 46:
	      case 48: case 49: case 50: case 53: case 54:
	      case 55: case 56: case 57: case 58: case 59:
	      case 60: case 61: case 62: case 63: case 65:
	      case 66: case 67: case 68: case 69: case 70:
	      case 71: case 72: case 73: case 74: case 75:
	      case 76: case 78: case 79: case 80: case 81:
	      case 82: case 83: case 84: case 85: case 86:
	      case 87: case 116: case 131: case 140: case 152:
	      case 170: case 330:
		{
		    int ZI451;

		    ZR452 (&ZI451);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    have_type_declaration = (ZI458) ;
		    }
		    {

    /* op will be in its primary form */
    HASHID nm = lookup_op ( (ZI451) ) ;
    (ZI461) = DEREF_id ( hashid_id ( nm ) ) ;
    set_hashid_loc ( (ZI461), underlying_op ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	  ZL2:;
	}
	{

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	}
	ZI420 = ZI461;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR1085(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR653 (&ZI432);
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
ZR1254(TYPE *ZI415, BASE_TYPE *ZI512, TYPE *ZI877, CV_SPEC *ZI878, DECL_SPEC *ZI913)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI913), (*ZI415), (*ZI512), (*ZI877), (*ZI878), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 78: case 83:
      case 141:
	{
	    TYPE ZI881;
	    DECL_SPEC ZI1075;
	    TYPE ZI1076;
	    ACCESS_LIST ZI672;
	    TYPE ZI575;
	    IDENTIFIER ZI420;
	    int ZI559;
	    IDENTIFIER ZI460;

	    {

    /* Complete a declaration specifier and a type */
    (ZI1075) = complete_dspec ( (*ZI913), (*ZI512), (*ZI877), (*ZI878) ) ;
    (ZI881) = complete_pre_type ( (*ZI512), (*ZI877), (*ZI878), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1076) = ( IS_NULL_type ( (*ZI415) ) ? (ZI881) : inject_pre_type ( (*ZI415), (ZI881), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI672) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR952 (ZI1076, &ZI575, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI575) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI575) ) ;
	(ZI460) = make_func_decl ( (ZI1075), (ZI575), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI1075), (ZI575), (ZI420), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (*ZI512) ;
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
	    ZR1077 (ZI512, &ZI1075, &ZI1076, &ZI672, &ZI559, &ZI460);
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
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR628(EXP *ZO1201)
{
    EXP ZI1201;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR626 (&ZI432);
	ZR1202 (ZI432, &ZI1201);
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
    *ZO1201 = ZI1201;
}

void
ZR753(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI559;

	    ADVANCE_LEXER;
	    ZR653 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_case ) ) ;
    (ZI432) = begin_case_stmt ( (ZI559), 1 ) ;
	    }
	}
	break;
      case 100:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_default ) ) ;
    (ZI432) = begin_default_stmt ( 1 ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI420;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI420 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    ZI420 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI420 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI420 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    (ZI432) = make_goto_stmt ( (ZI420) ) ;
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
ZR810(BASE_TYPE *ZO512, TYPE *ZO415)
{
    BASE_TYPE ZI512;
    TYPE ZI415;

    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI415 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_none ; 
	    }
	}
	break;
      case 8: case 9: case 83:
	{
	    IDENTIFIER ZI420;

	    ZR474 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI415) ) ;
    COPY_id ( type_name ( (ZI415) ), (ZI420) ) ;
    have_type_specifier = 1 ;
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

    (ZI415) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI420;

	    ZR473 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI415) ) ;
    COPY_id ( type_name ( (ZI415) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
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
}

void
ZR1256(TYPE *ZI415, DECL_SPEC *ZI691, BASE_TYPE *ZI512, TYPE *ZI877, CV_SPEC *ZI1255, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI691), (*ZI415), (*ZI512), (*ZI877), (*ZI1255), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI432) = NULL_exp ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 78: case 83:
      case 141:
	{
	    DECL_SPEC ZI911;
	    DECL_SPEC ZI913;
	    TYPE ZI881;
	    DECL_SPEC ZI1075;
	    TYPE ZI1076;
	    ACCESS_LIST ZI672;
	    TYPE ZI575;
	    IDENTIFIER ZI420;
	    int ZI559;
	    IDENTIFIER ZI460;

	    {
 (ZI911) = dspec_none ; 
	    }
	    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI691) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI913) = ( (*ZI691) | (ZI911) ) ;
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI1075) = complete_dspec ( (ZI913), (*ZI512), (*ZI877), (*ZI1255) ) ;
    (ZI881) = complete_pre_type ( (*ZI512), (*ZI877), (*ZI1255), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1076) = ( IS_NULL_type ( (*ZI415) ) ? (ZI881) : inject_pre_type ( (*ZI415), (ZI881), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI672) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR952 (ZI1076, &ZI575, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI575) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI575) ) ;
	(ZI460) = make_func_decl ( (ZI1075), (ZI575), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI1075), (ZI575), (ZI420), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (*ZI512) ;
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
	    ZR1077 (ZI512, &ZI1075, &ZI1076, &ZI672, &ZI559, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
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
ZR650(SID_LIST_EXP *ZO498)
{
    SID_LIST_EXP ZI498;

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
	    EXP ZI494;

	    ZR497 (&ZI494);
	    ZR1292 (&ZI494, &ZI498);
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

	    ZR645 (&ZI494);
	    ZR650 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI494), (ZI481), (ZI498) ) ;
	    }
	}
	break;
      case 346:
	{
	    EXP ZI494;
	    SID_LIST_EXP ZI481;

	    ZR646 (&ZI494);
	    ZR650 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI494), (ZI481), (ZI498) ) ;
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
}

void
ZR977(int *ZO947)
{
    int ZI947;

  ZL2_977:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZI947) = 1 ; 
	    }
	}
	break;
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 94: case 97: case 98: case 102:
      case 104: case 105: case 106: case 110: case 111:
      case 112: case 114: case 115: case 117: case 118:
      case 120: case 121: case 122: case 123: case 124:
      case 127: case 129: case 133: case 136: case 137:
      case 138: case 153: case 155: case 156: case 185:
      case 275: case 286: case 299:
	{
	    TYPE ZI575;
	    int ZI498;
	    IDENTIFIER ZI460;

	    {

    (ZI575) = NULL_type ;
	    }
	    {

    (ZI498) = CONTEXT_PARAMETER ;
	    }
	    ZR973 (ZI575, ZI498, &ZI460);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			goto ZL2_977;
		    }
		    /*UNREACHED*/
		  case 47:
		    {
			ADVANCE_LEXER;
			{
 (ZI947) = 1 ; 
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
    *ZO947 = ZI947;
}

void
ZR1384(TYPE *ZI1382, TYPE *ZO415)
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

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (*ZI1382) : inject_pre_type ( (ZI481), (*ZI1382), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI415 = *ZI1382;
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
ZR1257(void)
{
    switch (CURRENT_TERMINAL) {
      case 26: case 30:
	{
	    ZR1032 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
    }
	    }
	}
	break;
      case 126: case 139: case 154:
	{
	    EXP ZI432;

	    ZR1079 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
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
ZR1003(IDENTIFIER *ZI460, SID_LIST_EXP *ZO498)
{
    SID_LIST_EXP ZI498;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 8: case 9: case 17: case 18:
      case 19: case 20: case 21: case 22: case 23:
      case 25: case 33: case 43: case 59: case 61:
      case 62: case 64: case 65: case 69: case 71:
      case 78: case 83: case 85: case 97: case 102:
      case 106: case 110: case 111: case 114: case 115:
      case 116: case 122: case 123: case 127: case 130:
      case 131: case 132: case 135: case 140: case 141:
      case 145: case 146: case 148: case 149: case 150:
      case 152: case 156: case 170: case 185: case 206:
      case 210: case 255: case 286: case 299: case 330:
	{
	    ZR1001 (*ZI460, &ZI498);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI498) = NULL_list ( EXP ) ;
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
    *ZO498 = ZI498;
}

void
ZR438(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 135: case 150:
	{
	    ZR437 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 17:
		    {
			{

    ZI432 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			{

    ZI432 = crt_token->pp_data.exp ;
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

    ZI432 = crt_token->pp_data.exp ;
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

    ZI432 = crt_token->pp_data.exp ;
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

    ZI432 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    ZI432 = crt_token->pp_data.exp ;
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
    *ZO432 = ZI432;
}

void
ZR941(SID_LIST_TYPE *ZO498)
{
    SID_LIST_TYPE ZI498;

    switch (CURRENT_TERMINAL) {
      case 149:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 47:
		    {
			ADVANCE_LEXER;
			{

    report ( crt_loc, ERR_except_spec_ellipsis () ) ;
    (ZI498) = univ_type_set ;
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
			ZR1106 (&ZI498);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZI498) = NULL_list ( TYPE ) ;
			}
		    }
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      default:
	{
	    {

    (ZI498) = empty_type_set ;
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
    *ZO498 = ZI498;
}

void
parse_decl(TYPE ZI415, DECL_SPEC ZI691)
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
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 78: case 83:
      case 141:
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
	    TYPE ZI575;
	    IDENTIFIER ZI420;
	    int ZI559;
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

    crt_templ_qualifier = 0 ;
	    }
	    ZR952 (ZI1076, &ZI575, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI575) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI575) ) ;
	(ZI460) = make_func_decl ( (ZI1075), (ZI575), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI1075), (ZI575), (ZI420), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (ZI512) ;
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
	    ZR1077 (&ZI512, &ZI1075, &ZI1076, &ZI672, &ZI559, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	goto ZL1;
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
  ZL0:;
}

void
ZR1385(TYPE *ZO1140)
{
    TYPE ZI1140;

    switch (CURRENT_TERMINAL) {
      case 10: case 11: case 33: case 65: case 66:
      case 78: case 332:
	{
	    TYPE ZI415;

	    ZR953 (&ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
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
	    ZR1141 (ZI415, &ZI1140);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 7: case 8: case 9: case 25:
      case 39: case 47: case 83: case 94: case 97:
      case 98: case 102: case 104: case 105: case 106:
      case 110: case 111: case 112: case 114: case 115:
      case 117: case 118: case 120: case 121: case 122:
      case 123: case 124: case 127: case 129: case 133:
      case 136: case 137: case 138: case 153: case 155:
      case 156: case 185: case 275: case 286: case 299:
	{
	    IDENTIFIER ZI420;
	    int ZI945;
	    TYPE ZI415;

	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI945) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI420) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR946 (ZI945, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR1141 (ZI415, &ZI1140);
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
    *ZO1140 = ZI1140;
}

void
ZR1386(SID_LIST_TYPE *ZO481)
{
    SID_LIST_TYPE ZI481;

    switch (CURRENT_TERMINAL) {
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 98: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 124:
      case 127: case 129: case 153: case 156: case 185:
      case 286: case 299:
	{
	    ZR1106 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
	    }
	    {

    (ZI481) = NULL_list ( TYPE ) ;
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
    *ZO481 = ZI481;
}

void
ZR1259(void)
{
    switch (CURRENT_TERMINAL) {
      case 153:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI420;
	    TYPE ZI415;

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

    using_typename ( (ZI415) ) ;
	    }
	    ZR419 ();
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

	    ZR944 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    IGNORE using_identifier ( (ZI420) ) ;
	    }
	    ZR419 ();
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
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1260(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI1042;
	    IDENTIFIER ZI420;

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
		  case 3:
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
	    {

    (ZI420) = (ZI1042) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI420) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1435 (&ZI420, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 64:
	{
	    DECL_SPEC ZI691;
	    TYPE ZI415;

	    {

    decl_loc = crt_loc ;
    begin_namespace ( NULL_id, 1 ) ;
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

    end_namespace ( 1 ) ;
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
ZR626(EXP *ZO1205)
{
    EXP ZI1205;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR624 (&ZI432);
	ZR1206 (ZI432, &ZI1205);
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
    *ZO1205 = ZI1205;
}

void
ZR680(EXP *ZO432)
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

    COPY_int ( exp_sequence_block ( (ZI559) ), 2 ) ;
	}
	ZR678 (ZI559, &ZI494);
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

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
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
    *ZO432 = ZI432;
}

void
ZR1261(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 139:
	{
	    NAMESPACE ZI1049;
	    IDENTIFIER ZI1050;
	    IDENTIFIER ZI420;
	    NAMESPACE ZI426;

	    ADVANCE_LEXER;
	    ZR429 (&ZI1049);
	    ZR509 (&ZI1050);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI1049), (ZI1050), 0 ) ;
    last_namespace = (ZI1049) ;
	    }
	    {

    (ZI426) = find_nspace_id ( (ZI420) ) ;
	    }
	    {

    using_namespace ( (ZI426) ) ;
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
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 83:
      case 141: case 153:
	{
	    ZR1259 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
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
ZR419(void)
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
	int ZI415;

	{
 (ZI415) = lex_semicolon ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI415) ) report ( crt_loc, ERR_lex_expect ( (ZI415) ) ) ;
	}
    }
}

void
ZR632(EXP *ZO1193)
{
    EXP ZI1193;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR630 (&ZI432);
	ZR1194 (ZI432, &ZI1193);
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
    *ZO1193 = ZI1193;
}

void
ZR653(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI494;

	ZR634 (&ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = convert_reference ( (ZI494), REF_NORMAL ) ;
    (ZI432) = convert_lvalue ( (ZI432) ) ;
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
ZR1117(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI461;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
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

    (ZI420) = (ZI461) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	}
	break;
      default:
	{
	    {

    HASHID nm = lookup_anon () ;
    (ZI420) = DEREF_id ( hashid_id ( nm ) ) ;
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
    *ZO420 = ZI420;
}

void
ZR500(SID_LIST_EXP *ZO481)
{
    SID_LIST_EXP ZI481;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    ZR499 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI481) = NULL_list ( EXP ) ;
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
    *ZO481 = ZI481;
}

void
ZR928(TYPE *ZO498)
{
    TYPE ZI498;

    switch (CURRENT_TERMINAL) {
      case 11:
	{
	    IDENTIFIER ZI420;
	    CV_SPEC ZI785;

	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR790 (&ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CLASS_TYPE ct = find_class ( (ZI420) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZI420) ) ) ;
	MAKE_type_ptr ( (ZI785), NULL_type, (ZI498) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZI785), ct, NULL_type, (ZI498) ) ;
    }
	    }
	}
	break;
      case 10:
	{
	    IDENTIFIER ZI420;
	    CV_SPEC ZI785;

	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR790 (&ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CLASS_TYPE ct = find_class ( (ZI420) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZI420) ) ) ;
	MAKE_type_ptr ( (ZI785), NULL_type, (ZI498) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZI785), ct, NULL_type, (ZI498) ) ;
    }
	    }
	}
	break;
      case 78:
	{
	    CV_SPEC ZI785;

	    ADVANCE_LEXER;
	    ZR790 (&ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_ptr ( (ZI785), NULL_type, (ZI498) ) ;
	    }
	}
	break;
      case 33:
	{
	    CV_SPEC ZI785;

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
	    ZR790 (&ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Can't have const-volatile qualified references */
    if ( (ZI785) ) report ( crt_loc, ERR_dcl_ref_cv ( (ZI785) ) ) ;
    MAKE_type_ref ( cv_none, NULL_type, (ZI498) ) ;
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
}

void
ZR1264(EXP *ZI1262, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 72:
	{
	    EXP ZI494;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR492 (&ZI494);
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR497 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_cond_exp ( (*ZI1262), (ZI494), (ZI457) ) ;
	    }
	}
	break;
      default:
	{
	    ZI432 = *ZI1262;
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
ZR847(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_847:;
    {
	ZR844 ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_847;
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
ZR1064(TYPE ZI415, DECL_SPEC ZI691, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI559;
	DECL_SPEC ZI494;
	DECL_SPEC ZI457;
	DECL_SPEC ZI1065;
	DECL_SPEC ZI911;
	EXP ZI766;

	switch (CURRENT_TERMINAL) {
	  case 105:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 19:
		{
		    {

    ZI559 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    ZI559 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI494) = find_linkage ( (ZI559) ) ;
	}
	{

    (ZI457) = crt_linkage ;
    crt_linkage = (ZI494) ;
    IGNORE incr_value ( OPT_VAL_external_specs ) ;
	}
	{
 (ZI1065) = ( dspec_extern | dspec_c ) ; 
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI691) & (ZI1065) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI911) = ( (ZI691) | (ZI1065) ) ;
	}
	{
	    {
		BASE_TYPE ZI1250;
		TYPE ZI1251;
		CV_SPEC ZI1252;
		DECL_SPEC ZI1253;
		BASE_TYPE ZI512;
		TYPE ZI877;
		CV_SPEC ZI878;
		DECL_SPEC ZI1606;
		DECL_SPEC ZI913;

		{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL4;
		ZR908 (ZI415, &ZI1250, &ZI1251, &ZI1252, &ZI1253);
		ZR919 (&ZI415, &ZI1250, &ZI1251, &ZI1252, &ZI1253, &ZI512, &ZI877, &ZI878, &ZI1606);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI911) & (ZI1606) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI913) = ( (ZI911) | (ZI1606) ) ;
		}
		ZR1254 (&ZI415, &ZI512, &ZI877, &ZI878, &ZI913);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI766) = NULL_exp ;
		}
		{

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI457) ;
		}
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    switch (CURRENT_TERMINAL) {
	      case 105:
		{
		    ZR1064 (ZI415, ZI911, &ZI766);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI457) ;
		    }
		}
		break;
	      case 64:
		{
		    TYPE ZI881;
		    DECL_SPEC ZI913;

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

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI911) ) ;
		    }
		    {

    (ZI881) = NULL_type ;
		    }
		    {
 (ZI913) = dspec_none ; 
		    }
		    ZR1029 (ZI881, ZI913);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI457) ;
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

    (ZI766) = NULL_exp ;
		    }
		}
		break;
	      case 134: case 147:
		{
		    ZR1074 (ZI415, ZI911, &ZI766);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI457) ;
		    }
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

		    {
 (ZI512) = btype_none ; 
		    }
		    {

    (ZI877) = NULL_type ;
		    }
		    {
 (ZI1255) = cv_none ; 
		    }
		    ZR1256 (&ZI415, &ZI911, &ZI512, &ZI877, &ZI1255, &ZI766);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI457) ;
		    }
		}
		break;
	      case 126: case 139: case 154:
		{
		    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI911) ) ;
		    }
		    ZR1079 (&ZI766);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI457) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	  ZL3:;
	}
	ZI432 = ZI766;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR619(EXP *ZO1217)
{
    EXP ZI1217;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR616 (&ZI432);
	ZR1218 (ZI432, &ZI1217);
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
    *ZO1217 = ZI1217;
}

void
ZR1011(DECL_SPEC ZI691, BASE_TYPE ZI512, TYPE ZI415, ACCESS_LIST ZI672)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1011:;
    {
	ZR1010 (ZI691, ZI512, ZI415, ZI672);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    {

    crt_templ_qualifier = 0 ;
		    }
		    goto ZL2_1011;
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
ZR1266(EXP *ZI1265, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    EXP ZI457;

	    ADVANCE_LEXER;
	    ZR497 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_assign_exp ( (*ZI1265), (ZI457), 0 ) ;
	    }
	}
	break;
      default:
	{
	    ZR1264 (ZI1265, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 34: case 45: case 58: case 60: case 68:
      case 70: case 74: case 76: case 79: case 81:
	{
	    int ZI451;
	    EXP ZI457;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR641 ();
	    ZR497 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI432) = make_become_exp ( (ZI451), (*ZI1265), (ZI457) ) ;
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
ZR1268(NAMESPACE *ZI426, EXP *ZO1241)
{
    EXP ZI1241;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI432;

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

    (ZI432) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1242 (ZI432, &ZI1241);
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
	    IDENTIFIER ZI420;
	    EXP ZI432;

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
	    {

    (ZI432) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI432, &ZI1241);
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
ZR1141(TYPE ZI1139, TYPE *ZO1140)
{
    TYPE ZI1140;

  ZL2_1141:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    TYPE ZI481;
	    TYPE ZI415;

	    ZR954 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1139) ) ? (ZI481) : inject_pre_type ( (ZI1139), (ZI481), 0 ) ) ;
	    }
	    ZI1139 = ZI415;
	    goto ZL2_1141;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1140 = ZI1139;
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
    *ZO1140 = ZI1140;
}

void
ZR887(BASE_TYPE *ZI876, TYPE *ZI877, CV_SPEC *ZI878, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI575;
	BASE_TYPE ZI1392;
	TYPE ZI1393;
	CV_SPEC ZI1394;
	BASE_TYPE ZI880;
	TYPE ZI881;
	CV_SPEC ZI882;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI575) = NULL_type ;
	}
	ZR874 (ZI575, &ZI1392, &ZI1393, &ZI1394);
	ZR887 (&ZI1392, &ZI1393, &ZI1394, &ZI880, &ZI881, &ZI882);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI876) & (ZI880) ) {
	(ZI512) = join_pre_types ( (*ZI876), (ZI880) ) ;
    } else {
	(ZI512) = ( (*ZI876) | (ZI880) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI877) ) ) {
	(ZI415) = (ZI881) ;
    } else if ( IS_NULL_type ( (ZI881) ) ) {
	(ZI415) = (*ZI877) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI877), (ZI881) ) ) ;
	(ZI415) = (ZI881) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI878) & (ZI882) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI785) = ( (*ZI878) | (ZI882) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI512 = *ZI876;
	    ZI415 = *ZI877;
	    ZI785 = *ZI878;
	}
	break;
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
ZR607(EXP *ZO1233)
{
    EXP ZI1233;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR603 (&ZI432);
	ZR1234 (ZI432, &ZI1233);
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
    *ZO1233 = ZI1233;
}

void
ZR1396(NAMESPACE *ZI1395, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI1395, &ZI481);
	    ZR477 (*ZI1395, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (*ZI1395), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI1395) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI520;
	    BASE_TYPE ZI521;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    {

    (ZI520) = DEREF_id ( nspace_name ( (*ZI1395) ) ) ;
	    }
	    {
 (ZI521) = btype_none ; 
	    }
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

    (ZI420) = check_id ( (*ZI1395), (ZI479), 0 ) ;
    last_namespace = (*ZI1395) ;
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
ZR1269(NAMESPACE *ZI426, EXP *ZO1241)
{
    EXP ZI1241;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI432;

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

    (ZI432) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1242 (ZI432, &ZI1241);
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
	    IDENTIFIER ZI420;
	    EXP ZI432;

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
	    {

    (ZI432) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI432, &ZI1241);
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

/* BEGINNING OF TRAILER */



/* END OF FILE */
