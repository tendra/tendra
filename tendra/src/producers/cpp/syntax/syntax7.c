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
ZR870(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI821;

	    ZR429 (&ZI426);
	    ZR509 (&ZI821);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI821), 0 ) ;
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
ZR1253(TYPE *ZI415, BASE_TYPE *ZI512, TYPE *ZI876, CV_SPEC *ZI877, DECL_SPEC *ZI912)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI912), (*ZI415), (*ZI512), (*ZI876), (*ZI877), last_lex_token, 0 ) ;
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
	    TYPE ZI880;
	    DECL_SPEC ZI1074;
	    TYPE ZI1075;
	    ACCESS_LIST ZI671;
	    TYPE ZI575;
	    IDENTIFIER ZI420;
	    int ZI559;
	    IDENTIFIER ZI460;

	    {

    /* Complete a declaration specifier and a type */
    (ZI1074) = complete_dspec ( (*ZI912), (*ZI512), (*ZI876), (*ZI877) ) ;
    (ZI880) = complete_pre_type ( (*ZI512), (*ZI876), (*ZI877), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1075) = ( IS_NULL_type ( (*ZI415) ) ? (ZI880) : inject_pre_type ( (*ZI415), (ZI880), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI671) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR951 (ZI1075, &ZI575, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI575) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI575) ) ;
	(ZI460) = make_func_decl ( (ZI1074), (ZI575), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI1074), (ZI575), (ZI420), def ) ;
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

    IGNORE clear_access ( (ZI460), &(ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1076 (ZI512, &ZI1074, &ZI1075, &ZI671, &ZI559, &ZI460);
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
		TYPE ZI1319;
		BASE_TYPE ZI875;
		TYPE ZI876;
		CV_SPEC ZI877;
		BASE_TYPE ZI512;
		TYPE ZI498;
		CV_SPEC ZI784;
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

    (ZI1319) = NULL_type ;
		}
		ZR873 (ZI1319, &ZI875, &ZI876, &ZI877);
		ZR886 (&ZI875, &ZI876, &ZI877, &ZI512, &ZI498, &ZI784);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI575) = complete_pre_type ( (ZI512), (ZI498), (ZI784), 1 ) ;
    have_type_specifier = 0 ;
		}
		ZR988 (&ZI481);
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
ZR1084(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR652 (&ZI432);
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
ZR627(EXP *ZO1200)
{
    EXP ZI1200;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR625 (&ZI432);
	ZR1201 (ZI432, &ZI1200);
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
    *ZO1200 = ZI1200;
}

void
ZR1255(TYPE *ZI415, DECL_SPEC *ZI690, BASE_TYPE *ZI512, TYPE *ZI876, CV_SPEC *ZI1254, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI690), (*ZI415), (*ZI512), (*ZI876), (*ZI1254), last_lex_token, 0 ) ;
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
	    DECL_SPEC ZI910;
	    DECL_SPEC ZI912;
	    TYPE ZI880;
	    DECL_SPEC ZI1074;
	    TYPE ZI1075;
	    ACCESS_LIST ZI671;
	    TYPE ZI575;
	    IDENTIFIER ZI420;
	    int ZI559;
	    IDENTIFIER ZI460;

	    {
 (ZI910) = dspec_none ; 
	    }
	    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI690) & (ZI910) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI912) = ( (*ZI690) | (ZI910) ) ;
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI1074) = complete_dspec ( (ZI912), (*ZI512), (*ZI876), (*ZI1254) ) ;
    (ZI880) = complete_pre_type ( (*ZI512), (*ZI876), (*ZI1254), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1075) = ( IS_NULL_type ( (*ZI415) ) ? (ZI880) : inject_pre_type ( (*ZI415), (ZI880), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI671) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR951 (ZI1075, &ZI575, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI575) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI575) ) ;
	(ZI460) = make_func_decl ( (ZI1074), (ZI575), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI1074), (ZI575), (ZI420), def ) ;
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

    IGNORE clear_access ( (ZI460), &(ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1076 (ZI512, &ZI1074, &ZI1075, &ZI671, &ZI559, &ZI460);
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
ZR752(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI559;

	    ADVANCE_LEXER;
	    ZR652 (&ZI559);
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
ZR809(BASE_TYPE *ZO512, TYPE *ZO415)
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
ZR1383(TYPE *ZI1381, TYPE *ZO415)
{
    TYPE ZI415;

    switch (CURRENT_TERMINAL) {
      case 10: case 11: case 33: case 65: case 66:
      case 78: case 332:
	{
	    TYPE ZI481;

	    ZR952 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (*ZI1381) : inject_pre_type ( (ZI481), (*ZI1381), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI415 = *ZI1381;
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
ZR1256(void)
{
    switch (CURRENT_TERMINAL) {
      case 26: case 30:
	{
	    ZR1031 ();
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

	    ZR1078 (&ZI432);
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
ZR1002(IDENTIFIER *ZI460, SID_LIST_EXP *ZO498)
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
      case 210: case 286: case 299: case 330:
	{
	    ZR1000 (*ZI460, &ZI498);
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
ZR649(SID_LIST_EXP *ZO498)
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
      case 286: case 299: case 330:
	{
	    EXP ZI494;

	    ZR497 (&ZI494);
	    ZR1291 (&ZI494, &ZI498);
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

	    ZR644 (&ZI494);
	    ZR649 (&ZI481);
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

	    ZR645 (&ZI494);
	    ZR649 (&ZI481);
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
ZR976(int *ZO946)
{
    int ZI946;

  ZL2_976:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZI946) = 1 ; 
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
	    ZR972 (ZI575, ZI498, &ZI460);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			goto ZL2_976;
		    }
		    /*UNREACHED*/
		  case 47:
		    {
			ADVANCE_LEXER;
			{
 (ZI946) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI946) = 0 ; 
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
    *ZO946 = ZI946;
}

void
ZR1384(TYPE *ZO1139)
{
    TYPE ZI1139;

    switch (CURRENT_TERMINAL) {
      case 10: case 11: case 33: case 65: case 66:
      case 78: case 332:
	{
	    TYPE ZI415;

	    ZR952 (&ZI415);
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
	    ZR1140 (ZI415, &ZI1139);
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
	    int ZI944;
	    TYPE ZI415;

	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI944) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI420) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR945 (ZI944, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR1140 (ZI415, &ZI1139);
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
    *ZO1139 = ZI1139;
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
ZR940(SID_LIST_TYPE *ZO498)
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
			ZR1105 (&ZI498);
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
parse_decl(TYPE ZI415, DECL_SPEC ZI690)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1249;
	TYPE ZI1250;
	CV_SPEC ZI1251;
	DECL_SPEC ZI1252;
	BASE_TYPE ZI512;
	TYPE ZI876;
	CV_SPEC ZI877;
	DECL_SPEC ZI910;
	DECL_SPEC ZI912;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR907 (ZI415, &ZI1249, &ZI1250, &ZI1251, &ZI1252);
	ZR918 (&ZI415, &ZI1249, &ZI1250, &ZI1251, &ZI1252, &ZI512, &ZI876, &ZI877, &ZI910);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI690) & (ZI910) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI912) = ( (ZI690) | (ZI910) ) ;
	}
	ZR1253 (&ZI415, &ZI512, &ZI876, &ZI877, &ZI912);
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
	    TYPE ZI876;
	    CV_SPEC ZI877;
	    DECL_SPEC ZI910;
	    DECL_SPEC ZI912;
	    TYPE ZI880;
	    DECL_SPEC ZI1074;
	    TYPE ZI1075;
	    ACCESS_LIST ZI671;
	    TYPE ZI575;
	    IDENTIFIER ZI420;
	    int ZI559;
	    IDENTIFIER ZI460;

	    {
 (ZI512) = btype_none ; 
	    }
	    {

    (ZI876) = NULL_type ;
	    }
	    {
 (ZI877) = cv_none ; 
	    }
	    {
 (ZI910) = dspec_none ; 
	    }
	    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI690) & (ZI910) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI912) = ( (ZI690) | (ZI910) ) ;
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI1074) = complete_dspec ( (ZI912), (ZI512), (ZI876), (ZI877) ) ;
    (ZI880) = complete_pre_type ( (ZI512), (ZI876), (ZI877), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1075) = ( IS_NULL_type ( (ZI415) ) ? (ZI880) : inject_pre_type ( (ZI415), (ZI880), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI671) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR951 (ZI1075, &ZI575, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI575) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI575) ) ;
	(ZI460) = make_func_decl ( (ZI1074), (ZI575), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI1074), (ZI575), (ZI420), def ) ;
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

    IGNORE clear_access ( (ZI460), &(ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1076 (&ZI512, &ZI1074, &ZI1075, &ZI671, &ZI559, &ZI460);
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
ZR1385(SID_LIST_TYPE *ZO481)
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
	    ZR1105 (&ZI481);
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
ZR1258(void)
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

	    ZR943 (&ZI420);
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
ZR1259(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI1041;
	    IDENTIFIER ZI420;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI1041 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    ZI1041 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI1041 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1041 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI420) = (ZI1041) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI420) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1434 (&ZI420, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 64:
	{
	    DECL_SPEC ZI690;
	    TYPE ZI415;

	    {

    decl_loc = crt_loc ;
    begin_namespace ( NULL_id, 1 ) ;
	    }
	    {
 (ZI690) = dspec_none ; 
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
	    ZR1028 (ZI415, ZI690);
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
ZR1260(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 139:
	{
	    NAMESPACE ZI1048;
	    IDENTIFIER ZI1049;
	    IDENTIFIER ZI420;
	    NAMESPACE ZI426;

	    ADVANCE_LEXER;
	    ZR429 (&ZI1048);
	    ZR509 (&ZI1049);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI1048), (ZI1049), 0 ) ;
    last_namespace = (ZI1048) ;
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
	    ZR1258 ();
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
ZR625(EXP *ZO1204)
{
    EXP ZI1204;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR623 (&ZI432);
	ZR1205 (ZI432, &ZI1204);
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
    *ZO1204 = ZI1204;
}

void
ZR679(EXP *ZO432)
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
	ZR677 (ZI559, &ZI494);
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
ZR631(EXP *ZO1192)
{
    EXP ZI1192;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR629 (&ZI432);
	ZR1193 (ZI432, &ZI1192);
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
    *ZO1192 = ZI1192;
}

void
ZR652(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI494;

	ZR633 (&ZI494);
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
ZR1116(IDENTIFIER *ZO420)
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
ZR1263(EXP *ZI1261, EXP *ZO432)
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

    (ZI432) = make_cond_exp ( (*ZI1261), (ZI494), (ZI457) ) ;
	    }
	}
	break;
      default:
	{
	    ZI432 = *ZI1261;
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
ZR927(TYPE *ZO498)
{
    TYPE ZI498;

    switch (CURRENT_TERMINAL) {
      case 11:
	{
	    IDENTIFIER ZI420;
	    CV_SPEC ZI784;

	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR789 (&ZI784);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CLASS_TYPE ct = find_class ( (ZI420) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZI420) ) ) ;
	MAKE_type_ptr ( (ZI784), NULL_type, (ZI498) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZI784), ct, NULL_type, (ZI498) ) ;
    }
	    }
	}
	break;
      case 10:
	{
	    IDENTIFIER ZI420;
	    CV_SPEC ZI784;

	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR789 (&ZI784);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CLASS_TYPE ct = find_class ( (ZI420) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZI420) ) ) ;
	MAKE_type_ptr ( (ZI784), NULL_type, (ZI498) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZI784), ct, NULL_type, (ZI498) ) ;
    }
	    }
	}
	break;
      case 78:
	{
	    CV_SPEC ZI784;

	    ADVANCE_LEXER;
	    ZR789 (&ZI784);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_ptr ( (ZI784), NULL_type, (ZI498) ) ;
	    }
	}
	break;
      case 33:
	{
	    CV_SPEC ZI784;

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
	    ZR789 (&ZI784);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Can't have const-volatile qualified references */
    if ( (ZI784) ) report ( crt_loc, ERR_dcl_ref_cv ( (ZI784) ) ) ;
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
ZR846(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_846:;
    {
	ZR843 ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_846;
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
ZR1063(TYPE ZI415, DECL_SPEC ZI690, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI559;
	DECL_SPEC ZI494;
	DECL_SPEC ZI457;
	DECL_SPEC ZI1064;
	DECL_SPEC ZI910;
	EXP ZI765;

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
 (ZI1064) = ( dspec_extern | dspec_c ) ; 
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI690) & (ZI1064) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI910) = ( (ZI690) | (ZI1064) ) ;
	}
	{
	    {
		BASE_TYPE ZI1249;
		TYPE ZI1250;
		CV_SPEC ZI1251;
		DECL_SPEC ZI1252;
		BASE_TYPE ZI512;
		TYPE ZI876;
		CV_SPEC ZI877;
		DECL_SPEC ZI1601;
		DECL_SPEC ZI912;

		{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL4;
		ZR907 (ZI415, &ZI1249, &ZI1250, &ZI1251, &ZI1252);
		ZR918 (&ZI415, &ZI1249, &ZI1250, &ZI1251, &ZI1252, &ZI512, &ZI876, &ZI877, &ZI1601);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI910) & (ZI1601) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI912) = ( (ZI910) | (ZI1601) ) ;
		}
		ZR1253 (&ZI415, &ZI512, &ZI876, &ZI877, &ZI912);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI765) = NULL_exp ;
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
		    ZR1063 (ZI415, ZI910, &ZI765);
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
		    TYPE ZI880;
		    DECL_SPEC ZI912;

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
    UNUSED ( (ZI910) ) ;
		    }
		    {

    (ZI880) = NULL_type ;
		    }
		    {
 (ZI912) = dspec_none ; 
		    }
		    ZR1028 (ZI880, ZI912);
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

    (ZI765) = NULL_exp ;
		    }
		}
		break;
	      case 134: case 147:
		{
		    ZR1073 (ZI415, ZI910, &ZI765);
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
		    TYPE ZI876;
		    CV_SPEC ZI1254;

		    {
 (ZI512) = btype_none ; 
		    }
		    {

    (ZI876) = NULL_type ;
		    }
		    {
 (ZI1254) = cv_none ; 
		    }
		    ZR1255 (&ZI415, &ZI910, &ZI512, &ZI876, &ZI1254, &ZI765);
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
    UNUSED ( (ZI910) ) ;
		    }
		    ZR1078 (&ZI765);
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
	ZI432 = ZI765;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1265(EXP *ZI1264, EXP *ZO432)
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

    (ZI432) = make_assign_exp ( (*ZI1264), (ZI457), 0 ) ;
	    }
	}
	break;
      default:
	{
	    ZR1263 (ZI1264, &ZI432);
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
	    ZR640 ();
	    ZR497 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI432) = make_become_exp ( (ZI451), (*ZI1264), (ZI457) ) ;
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
ZR618(EXP *ZO1216)
{
    EXP ZI1216;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR615 (&ZI432);
	ZR1217 (ZI432, &ZI1216);
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
    *ZO1216 = ZI1216;
}

void
ZR1010(DECL_SPEC ZI690, BASE_TYPE ZI512, TYPE ZI415, ACCESS_LIST ZI671)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1010:;
    {
	ZR1009 (ZI690, ZI512, ZI415, ZI671);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    {

    crt_templ_qualifier = 0 ;
		    }
		    goto ZL2_1010;
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
ZR1267(NAMESPACE *ZI426, EXP *ZO1240)
{
    EXP ZI1240;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1266;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI784;
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

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1266) ) ;
    COPY_id ( type_name ( (ZI1266) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI784) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1266), (ZI784), 1 ) ;
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
	    ZR1241 (ZI432, &ZI1240);
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
	    ZR1241 (ZI432, &ZI1240);
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
    *ZO1240 = ZI1240;
}

void
ZR1140(TYPE ZI1138, TYPE *ZO1139)
{
    TYPE ZI1139;

  ZL2_1140:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    TYPE ZI481;
	    TYPE ZI415;

	    ZR953 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1138) ) ? (ZI481) : inject_pre_type ( (ZI1138), (ZI481), 0 ) ) ;
	    }
	    ZI1138 = ZI415;
	    goto ZL2_1140;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1139 = ZI1138;
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
    *ZO1139 = ZI1139;
}

void
ZR886(BASE_TYPE *ZI875, TYPE *ZI876, CV_SPEC *ZI877, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO784)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI784;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI575;
	BASE_TYPE ZI1391;
	TYPE ZI1392;
	CV_SPEC ZI1393;
	BASE_TYPE ZI879;
	TYPE ZI880;
	CV_SPEC ZI881;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI575) = NULL_type ;
	}
	ZR873 (ZI575, &ZI1391, &ZI1392, &ZI1393);
	ZR886 (&ZI1391, &ZI1392, &ZI1393, &ZI879, &ZI880, &ZI881);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI875) & (ZI879) ) {
	(ZI512) = join_pre_types ( (*ZI875), (ZI879) ) ;
    } else {
	(ZI512) = ( (*ZI875) | (ZI879) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI876) ) ) {
	(ZI415) = (ZI880) ;
    } else if ( IS_NULL_type ( (ZI880) ) ) {
	(ZI415) = (*ZI876) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI876), (ZI880) ) ) ;
	(ZI415) = (ZI880) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI877) & (ZI881) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI784) = ( (*ZI877) | (ZI881) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI512 = *ZI875;
	    ZI415 = *ZI876;
	    ZI784 = *ZI877;
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
    *ZO784 = ZI784;
}

void
ZR1395(NAMESPACE *ZI1394, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI481;
	    IDENTIFIER ZI479;

	    ZR476 (*ZI1394, &ZI481);
	    ZR477 (*ZI1394, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (*ZI1394), (ZI479), (ZI481) ) ;
    last_namespace = (*ZI1394) ;
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

    (ZI520) = DEREF_id ( nspace_name ( (*ZI1394) ) ) ;
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

    (ZI420) = check_id ( (*ZI1394), (ZI479), 0 ) ;
    last_namespace = (*ZI1394) ;
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
ZR1268(NAMESPACE *ZI426, EXP *ZO1240)
{
    EXP ZI1240;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1266;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI784;
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

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1266) ) ;
    COPY_id ( type_name ( (ZI1266) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI784) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1266), (ZI784), 1 ) ;
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
	    ZR1241 (ZI432, &ZI1240);
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
	    ZR1241 (ZI432, &ZI1240);
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
    *ZO1240 = ZI1240;
}

void
ZR606(EXP *ZO1232)
{
    EXP ZI1232;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR602 (&ZI432);
	ZR1233 (ZI432, &ZI1232);
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
    *ZO1232 = ZI1232;
}

void
ZR1269(EXP *ZO1240)
{
    EXP ZI1240;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI420;
	    TYPE ZI1266;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI784;
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

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI461), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1266) ) ;
    COPY_id ( type_name ( (ZI1266) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI784) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1266), (ZI784), 1 ) ;
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
	    ZR1241 (ZI432, &ZI1240);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI426;
	    int ZI481;
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI432;

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
	    {

    (ZI432) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1241 (ZI432, &ZI1240);
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
    *ZO1240 = ZI1240;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
