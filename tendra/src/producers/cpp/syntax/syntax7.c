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
ZR869 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI820;

	    ZR428 (&ZI425);
	    ZR508 (&ZI820);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI820), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      default:
	{
	    {

    HASHID nm = lookup_anon () ;
    (ZI419) = DEREF_id ( hashid_id ( nm ) ) ;
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
    *ZO419 = ZI419;
}

void
parse_mem_type PROTO_N ((ZO414))
  PROTO_T (TYPE *ZO414)
{
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI511;
	TYPE ZI497;
	CV_SPEC ZI783;
	TYPE ZI480;

	ZR873 (&ZI511, &ZI497, &ZI783);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI480) = complete_pre_type ( (ZI511), (ZI497), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 73:
		{
		    QUALIFIER ZI455;
		    int ZI456;
		    EXP ZI558;

		    ADVANCE_LEXER;
		    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
		    }
		    ZR651 (&ZI558);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI414) = make_bitfield_type ( (ZI480), (ZI511), (ZI558), 0 ) ;
		    }
		    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
		    }
		}
		break;
	      default:
		{
		    ZR955 (ZI480, &ZI414);
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
    *ZO414 = ZI414;
}

void
ZR1252 PROTO_N ((ZI414, ZI511, ZI875, ZI876, ZI911))
  PROTO_T (TYPE *ZI414 X BASE_TYPE *ZI511 X TYPE *ZI875 X CV_SPEC *ZI876 X DECL_SPEC *ZI911)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI911), (*ZI414), (*ZI511), (*ZI875), (*ZI876), last_lex_token, 0 ) ;
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
	    TYPE ZI879;
	    DECL_SPEC ZI1073;
	    TYPE ZI1074;
	    ACCESS_LIST ZI670;
	    TYPE ZI574;
	    IDENTIFIER ZI419;
	    int ZI558;
	    IDENTIFIER ZI459;

	    {

    /* Complete a declaration specifier and a type */
    (ZI1073) = complete_dspec ( (*ZI911), (*ZI511), (*ZI875), (*ZI876) ) ;
    (ZI879) = complete_pre_type ( (*ZI511), (*ZI875), (*ZI876), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1074) = ( IS_NULL_type ( (*ZI414) ) ? (ZI879) : inject_pre_type ( (*ZI414), (ZI879), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI670) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR950 (ZI1074, &ZI574, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI574) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI574) ) ;
	(ZI459) = make_func_decl ( (ZI1073), (ZI574), (ZI419), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI459) = make_object_decl ( (ZI1073), (ZI574), (ZI419), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (*ZI511) ;
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
	    ZR1075 (ZI511, &ZI1073, &ZI1074, &ZI670, &ZI558, &ZI459);
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
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
parse_operator PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	QUALIFIER ZI455;
	int ZI456;
	int ZI457;
	IDENTIFIER ZI460;

	switch (CURRENT_TERMINAL) {
	  case 141:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	}
	{

    (ZI457) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
	}
	{
	    {
		TYPE ZI1318;
		BASE_TYPE ZI874;
		TYPE ZI875;
		CV_SPEC ZI876;
		BASE_TYPE ZI511;
		TYPE ZI497;
		CV_SPEC ZI783;
		TYPE ZI574;
		TYPE ZI480;
		TYPE ZI414;
		int ZI459;

		{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL3;
		{

    (ZI1318) = NULL_type ;
		}
		ZR872 (ZI1318, &ZI874, &ZI875, &ZI876);
		ZR885 (&ZI874, &ZI875, &ZI876, &ZI511, &ZI497, &ZI783);
		if ((CURRENT_TERMINAL) == 354) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI574) = complete_pre_type ( (ZI511), (ZI497), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
		}
		ZR987 (&ZI480);
		if ((CURRENT_TERMINAL) == 354) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI574) : inject_pre_type ( (ZI480), (ZI574), 1 ) ) ;
		}
		{

    int td = have_type_declaration ;
    (ZI459) = 0 ;
    if ( td != TYPE_DECL_NONE ) {
	if ( td == TYPE_DECL_ELABORATE && found_elaborate_type ) {
	    /* This is allowed */
	    /* EMPTY */
	} else {
	    (ZI459) = 1 ;
	}
    }
    have_type_declaration = (ZI457) ;
		}
		{

    HASHID nm = lookup_conv ( (ZI414) ) ;
    if ( (ZI459) ) report ( crt_loc, ERR_class_conv_fct_typedef ( nm ) ) ;
    (ZI460) = DEREF_id ( hashid_id ( nm ) ) ;
    set_hashid_loc ( (ZI460), underlying_op ) ;
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
	      case 170: case 329:
		{
		    int ZI450;

		    ZR451 (&ZI450);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    have_type_declaration = (ZI457) ;
		    }
		    {

    /* op will be in its primary form */
    HASHID nm = lookup_op ( (ZI450) ) ;
    (ZI460) = DEREF_id ( hashid_id ( nm ) ) ;
    set_hashid_loc ( (ZI460), underlying_op ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	  ZL2:;
	}
	{

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	}
	ZI419 = ZI460;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1083 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR651 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI431) = NULL_exp ;
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
ZR1254 PROTO_N ((ZI414, ZI689, ZI511, ZI875, ZI1253, ZO431))
  PROTO_T (TYPE *ZI414 X DECL_SPEC *ZI689 X BASE_TYPE *ZI511 X TYPE *ZI875 X CV_SPEC *ZI1253 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI689), (*ZI414), (*ZI511), (*ZI875), (*ZI1253), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI431) = NULL_exp ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 78: case 83:
      case 141:
	{
	    DECL_SPEC ZI909;
	    DECL_SPEC ZI911;
	    TYPE ZI879;
	    DECL_SPEC ZI1073;
	    TYPE ZI1074;
	    ACCESS_LIST ZI670;
	    TYPE ZI574;
	    IDENTIFIER ZI419;
	    int ZI558;
	    IDENTIFIER ZI459;

	    {
 (ZI909) = dspec_none ; 
	    }
	    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI689) & (ZI909) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI911) = ( (*ZI689) | (ZI909) ) ;
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI1073) = complete_dspec ( (ZI911), (*ZI511), (*ZI875), (*ZI1253) ) ;
    (ZI879) = complete_pre_type ( (*ZI511), (*ZI875), (*ZI1253), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1074) = ( IS_NULL_type ( (*ZI414) ) ? (ZI879) : inject_pre_type ( (*ZI414), (ZI879), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI670) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR950 (ZI1074, &ZI574, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI574) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI574) ) ;
	(ZI459) = make_func_decl ( (ZI1073), (ZI574), (ZI419), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI459) = make_object_decl ( (ZI1073), (ZI574), (ZI419), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (*ZI511) ;
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
	    ZR1075 (ZI511, &ZI1073, &ZI1074, &ZI670, &ZI558, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = NULL_exp ;
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
ZR626 PROTO_N ((ZO1199))
  PROTO_T (EXP *ZO1199)
{
    EXP ZI1199;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR624 (&ZI431);
	ZR1200 (ZI431, &ZI1199);
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
    *ZO1199 = ZI1199;
}

void
ZR1382 PROTO_N ((ZI1380, ZO414))
  PROTO_T (TYPE *ZI1380 X TYPE *ZO414)
{
    TYPE ZI414;

    switch (CURRENT_TERMINAL) {
      case 10: case 11: case 33: case 65: case 66:
      case 78: case 331:
	{
	    TYPE ZI480;

	    ZR951 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (*ZI1380) : inject_pre_type ( (ZI480), (*ZI1380), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI414 = *ZI1380;
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
ZR1255 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 26: case 30:
	{
	    ZR1030 ();
	    if ((CURRENT_TERMINAL) == 354) {
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
	    EXP ZI431;

	    ZR1077 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
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
ZR1001 PROTO_N ((ZI459, ZO497))
  PROTO_T (IDENTIFIER *ZI459 X SID_LIST_EXP *ZO497)
{
    SID_LIST_EXP ZI497;

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
      case 152: case 156: case 170: case 184: case 205:
      case 209: case 285: case 298: case 329:
	{
	    ZR999 (*ZI459, &ZI497);
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
ZR751 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI558;

	    ADVANCE_LEXER;
	    ZR651 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_case ) ) ;
    (ZI431) = begin_case_stmt ( (ZI558), 1 ) ;
	    }
	}
	break;
      case 100:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_stmt_goto_case ( lex_default ) ) ;
    (ZI431) = begin_default_stmt ( 1 ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI419;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI419 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    ZI419 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI419 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI419 = crt_token->pp_data.id.use ;
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

    (ZI431) = make_goto_stmt ( (ZI419) ) ;
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
ZR808 PROTO_N ((ZO511, ZO414))
  PROTO_T (BASE_TYPE *ZO511 X TYPE *ZO414)
{
    BASE_TYPE ZI511;
    TYPE ZI414;

    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI414 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_none ; 
	    }
	}
	break;
      case 8: case 9: case 83:
	{
	    IDENTIFIER ZI419;

	    ZR473 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI414) ) ;
    COPY_id ( type_name ( (ZI414) ), (ZI419) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 184: case 285: case 298:
	{
	    ZR509 (&ZI511);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI419;

	    ZR472 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI414) ) ;
    COPY_id ( type_name ( (ZI414) ), (ZI419) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI511) = btype_none ; 
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
    *ZO511 = ZI511;
    *ZO414 = ZI414;
}

void
ZR1383 PROTO_N ((ZO1138))
  PROTO_T (TYPE *ZO1138)
{
    TYPE ZI1138;

    switch (CURRENT_TERMINAL) {
      case 10: case 11: case 33: case 65: case 66:
      case 78: case 331:
	{
	    TYPE ZI414;

	    ZR951 (&ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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
	    ZR1139 (ZI414, &ZI1138);
	    if ((CURRENT_TERMINAL) == 354) {
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
      case 156: case 184: case 274: case 285: case 298:
	{
	    IDENTIFIER ZI419;
	    int ZI943;
	    TYPE ZI414;

	    {

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI419) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR944 (ZI943, &ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR1139 (ZI414, &ZI1138);
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
    *ZO1138 = ZI1138;
}

void
ZR648 PROTO_N ((ZO497))
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
	    EXP ZI493;

	    ZR496 (&ZI493);
	    ZR1290 (&ZI493, &ZI497);
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

	    ZR643 (&ZI493);
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI493), (ZI480), (ZI497) ) ;
	    }
	}
	break;
      case 345:
	{
	    EXP ZI493;
	    SID_LIST_EXP ZI480;

	    ZR644 (&ZI493);
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (ZI493), (ZI480), (ZI497) ) ;
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
}

void
ZR975 PROTO_N ((ZO945))
  PROTO_T (int *ZO945)
{
    int ZI945;

  ZL2_975:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZI945) = 1 ; 
	    }
	}
	break;
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 94: case 97: case 98: case 102:
      case 104: case 105: case 106: case 110: case 111:
      case 112: case 114: case 115: case 117: case 118:
      case 120: case 121: case 122: case 123: case 124:
      case 127: case 129: case 133: case 136: case 137:
      case 138: case 153: case 155: case 156: case 184:
      case 274: case 285: case 298:
	{
	    TYPE ZI574;
	    int ZI497;
	    IDENTIFIER ZI459;

	    {

    (ZI574) = NULL_type ;
	    }
	    {

    (ZI497) = CONTEXT_PARAMETER ;
	    }
	    ZR971 (ZI574, ZI497, &ZI459);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			goto ZL2_975;
		    }
		    /*UNREACHED*/
		  case 47:
		    {
			ADVANCE_LEXER;
			{
 (ZI945) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI945) = 0 ; 
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
    *ZO945 = ZI945;
}

void
ZR1384 PROTO_N ((ZO480))
  PROTO_T (SID_LIST_TYPE *ZO480)
{
    SID_LIST_TYPE ZI480;

    switch (CURRENT_TERMINAL) {
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 98: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 124:
      case 127: case 129: case 153: case 156: case 184:
      case 285: case 298:
	{
	    ZR1104 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
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

    (ZI480) = NULL_list ( TYPE ) ;
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
    *ZO480 = ZI480;
}

void
ZR1257 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 153:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI419;
	    TYPE ZI414;

	    ADVANCE_LEXER;
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR428 (&ZI425);
	    ZR508 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = make_typename ( (ZI425), (ZI419) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
	found_elaborate_type = 1 ;
    }
    have_type_specifier = 1 ;
	    }
	    {

    using_typename ( (ZI414) ) ;
	    }
	    ZR418 ();
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

	    ZR942 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    IGNORE using_identifier ( (ZI419) ) ;
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
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR437 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 135: case 150:
	{
	    ZR436 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
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

    ZI431 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			{

    ZI431 = crt_token->pp_data.exp ;
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

    ZI431 = crt_token->pp_data.exp ;
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

    ZI431 = crt_token->pp_data.exp ;
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

    ZI431 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    ZI431 = crt_token->pp_data.exp ;
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
    *ZO431 = ZI431;
}

void
ZR939 PROTO_N ((ZO497))
  PROTO_T (SID_LIST_TYPE *ZO497)
{
    SID_LIST_TYPE ZI497;

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
    (ZI497) = univ_type_set ;
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
			ZR1104 (&ZI497);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZI497) = NULL_list ( TYPE ) ;
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

    (ZI497) = empty_type_set ;
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
parse_decl PROTO_N ((ZI414, ZI689))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI1248;
	TYPE ZI1249;
	CV_SPEC ZI1250;
	DECL_SPEC ZI1251;
	BASE_TYPE ZI511;
	TYPE ZI875;
	CV_SPEC ZI876;
	DECL_SPEC ZI909;
	DECL_SPEC ZI911;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR906 (ZI414, &ZI1248, &ZI1249, &ZI1250, &ZI1251);
	ZR917 (&ZI414, &ZI1248, &ZI1249, &ZI1250, &ZI1251, &ZI511, &ZI875, &ZI876, &ZI909);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI689) & (ZI909) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI911) = ( (ZI689) | (ZI909) ) ;
	}
	ZR1252 (&ZI414, &ZI511, &ZI875, &ZI876, &ZI911);
	if ((CURRENT_TERMINAL) == 354) {
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
	    BASE_TYPE ZI511;
	    TYPE ZI875;
	    CV_SPEC ZI876;
	    DECL_SPEC ZI909;
	    DECL_SPEC ZI911;
	    TYPE ZI879;
	    DECL_SPEC ZI1073;
	    TYPE ZI1074;
	    ACCESS_LIST ZI670;
	    TYPE ZI574;
	    IDENTIFIER ZI419;
	    int ZI558;
	    IDENTIFIER ZI459;

	    {
 (ZI511) = btype_none ; 
	    }
	    {

    (ZI875) = NULL_type ;
	    }
	    {
 (ZI876) = cv_none ; 
	    }
	    {
 (ZI909) = dspec_none ; 
	    }
	    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI689) & (ZI909) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI911) = ( (ZI689) | (ZI909) ) ;
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI1073) = complete_dspec ( (ZI911), (ZI511), (ZI875), (ZI876) ) ;
    (ZI879) = complete_pre_type ( (ZI511), (ZI875), (ZI876), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    {

    (ZI1074) = ( IS_NULL_type ( (ZI414) ) ? (ZI879) : inject_pre_type ( (ZI414), (ZI879), 1 ) ) ;
	    }
	    {

    save_access ( &(ZI670) ) ;
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR950 (ZI1074, &ZI574, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( type_tag ( (ZI574) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI574) ) ;
	(ZI459) = make_func_decl ( (ZI1073), (ZI574), (ZI419), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI459) = make_object_decl ( (ZI1073), (ZI574), (ZI419), def ) ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (ZI511) ;
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
	    ZR1075 (&ZI511, &ZI1073, &ZI1074, &ZI670, &ZI558, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
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
ZR1258 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI1040;
	    IDENTIFIER ZI419;

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
		  case 3:
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
	    {

    (ZI419) = (ZI1040) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI419) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1433 (&ZI419, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 64:
	{
	    DECL_SPEC ZI689;
	    TYPE ZI414;

	    {

    decl_loc = crt_loc ;
    begin_namespace ( NULL_id, 1 ) ;
	    }
	    {
 (ZI689) = dspec_none ; 
	    }
	    {

    (ZI414) = NULL_type ;
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
	    ZR1027 (ZI414, ZI689);
	    if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = NULL_exp ;
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
ZR1259 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 139:
	{
	    NAMESPACE ZI1047;
	    IDENTIFIER ZI1048;
	    IDENTIFIER ZI419;
	    NAMESPACE ZI425;

	    ADVANCE_LEXER;
	    ZR428 (&ZI1047);
	    ZR508 (&ZI1048);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( (ZI1047), (ZI1048), 0 ) ;
    last_namespace = (ZI1047) ;
	    }
	    {

    (ZI425) = find_nspace_id ( (ZI419) ) ;
	    }
	    {

    using_namespace ( (ZI425) ) ;
	    }
	    ZR418 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = NULL_exp ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 83:
      case 141: case 153:
	{
	    ZR1257 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = NULL_exp ;
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
ZR624 PROTO_N ((ZO1203))
  PROTO_T (EXP *ZO1203)
{
    EXP ZI1203;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR622 (&ZI431);
	ZR1204 (ZI431, &ZI1203);
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
    *ZO1203 = ZI1203;
}

void
ZR678 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI558;
	EXP ZI493;

	{

    (ZI558) = begin_compound_stmt ( 1 ) ;
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

    COPY_int ( exp_sequence_block ( (ZI558) ), 2 ) ;
	}
	ZR676 (ZI558, &ZI493);
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

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
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
    *ZO431 = ZI431;
}

void
ZR499 PROTO_N ((ZO480))
  PROTO_T (SID_LIST_EXP *ZO480)
{
    SID_LIST_EXP ZI480;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    ZR498 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI480) = NULL_list ( EXP ) ;
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
    *ZO480 = ZI480;
}

void
ZR418 PROTO_Z ()
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
	int ZI414;

	{
 (ZI414) = lex_semicolon ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI414) ) report ( crt_loc, ERR_lex_expect ( (ZI414) ) ) ;
	}
    }
}

void
ZR630 PROTO_N ((ZO1191))
  PROTO_T (EXP *ZO1191)
{
    EXP ZI1191;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR628 (&ZI431);
	ZR1192 (ZI431, &ZI1191);
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
    *ZO1191 = ZI1191;
}

void
ZR651 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI493;

	ZR632 (&ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI431) = convert_reference ( (ZI493), REF_NORMAL ) ;
    (ZI431) = convert_lvalue ( (ZI431) ) ;
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
ZR1115 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER ZI460;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    ZI460 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    ZI460 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    ZI460 = crt_token->pp_data.id.use ;
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

    (ZI419) = (ZI460) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	}
	break;
      default:
	{
	    {

    HASHID nm = lookup_anon () ;
    (ZI419) = DEREF_id ( hashid_id ( nm ) ) ;
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
    *ZO419 = ZI419;
}

void
ZR1262 PROTO_N ((ZI1260, ZO431))
  PROTO_T (EXP *ZI1260 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 72:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR491 (&ZI493);
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR496 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_cond_exp ( (*ZI1260), (ZI493), (ZI456) ) ;
	    }
	}
	break;
      default:
	{
	    ZI431 = *ZI1260;
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
ZR926 PROTO_N ((ZO497))
  PROTO_T (TYPE *ZO497)
{
    TYPE ZI497;

    switch (CURRENT_TERMINAL) {
      case 11:
	{
	    IDENTIFIER ZI419;
	    CV_SPEC ZI783;

	    {

    ZI419 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR788 (&ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CLASS_TYPE ct = find_class ( (ZI419) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZI419) ) ) ;
	MAKE_type_ptr ( (ZI783), NULL_type, (ZI497) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZI783), ct, NULL_type, (ZI497) ) ;
    }
	    }
	}
	break;
      case 10:
	{
	    IDENTIFIER ZI419;
	    CV_SPEC ZI783;

	    {

    ZI419 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR788 (&ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CLASS_TYPE ct = find_class ( (ZI419) ) ;
    if ( IS_NULL_ctype ( ct ) ) {
	report ( crt_loc, ERR_dcl_mptr_type ( (ZI419) ) ) ;
	MAKE_type_ptr ( (ZI783), NULL_type, (ZI497) ) ;
    } else {
	MAKE_type_ptr_mem ( (ZI783), ct, NULL_type, (ZI497) ) ;
    }
	    }
	}
	break;
      case 78:
	{
	    CV_SPEC ZI783;

	    ADVANCE_LEXER;
	    ZR788 (&ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    MAKE_type_ptr ( (ZI783), NULL_type, (ZI497) ) ;
	    }
	}
	break;
      case 33:
	{
	    CV_SPEC ZI783;

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
	    ZR788 (&ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Can't have const-volatile qualified references */
    if ( (ZI783) ) report ( crt_loc, ERR_dcl_ref_cv ( (ZI783) ) ) ;
    MAKE_type_ref ( cv_none, NULL_type, (ZI497) ) ;
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
}

void
ZR1264 PROTO_N ((ZI1263, ZO431))
  PROTO_T (EXP *ZI1263 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR496 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_assign_exp ( (*ZI1263), (ZI456), 0 ) ;
	    }
	}
	break;
      default:
	{
	    ZR1262 (ZI1263, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 34: case 45: case 58: case 60: case 68:
      case 70: case 74: case 76: case 79: case 81:
	{
	    int ZI450;
	    EXP ZI456;

	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR639 ();
	    ZR496 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI431) = make_become_exp ( (ZI450), (*ZI1263), (ZI456) ) ;
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
ZR845 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_845:;
    {
	ZR842 ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_845;
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
ZR1062 PROTO_N ((ZI414, ZI689, ZO431))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI558;
	DECL_SPEC ZI493;
	DECL_SPEC ZI456;
	DECL_SPEC ZI1063;
	DECL_SPEC ZI909;
	EXP ZI764;

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

    ZI558 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    ZI558 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI493) = find_linkage ( (ZI558) ) ;
	}
	{

    (ZI456) = crt_linkage ;
    crt_linkage = (ZI493) ;
    IGNORE incr_value ( OPT_VAL_external_specs ) ;
	}
	{
 (ZI1063) = ( dspec_extern | dspec_c ) ; 
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI689) & (ZI1063) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI909) = ( (ZI689) | (ZI1063) ) ;
	}
	{
	    {
		BASE_TYPE ZI1248;
		TYPE ZI1249;
		CV_SPEC ZI1250;
		DECL_SPEC ZI1251;
		BASE_TYPE ZI511;
		TYPE ZI875;
		CV_SPEC ZI876;
		DECL_SPEC ZI1600;
		DECL_SPEC ZI911;

		{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL4;
		ZR906 (ZI414, &ZI1248, &ZI1249, &ZI1250, &ZI1251);
		ZR917 (&ZI414, &ZI1248, &ZI1249, &ZI1250, &ZI1251, &ZI511, &ZI875, &ZI876, &ZI1600);
		if ((CURRENT_TERMINAL) == 354) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI909) & (ZI1600) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI911) = ( (ZI909) | (ZI1600) ) ;
		}
		ZR1252 (&ZI414, &ZI511, &ZI875, &ZI876, &ZI911);
		if ((CURRENT_TERMINAL) == 354) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI764) = NULL_exp ;
		}
		{

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI456) ;
		}
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    switch (CURRENT_TERMINAL) {
	      case 105:
		{
		    ZR1062 (ZI414, ZI909, &ZI764);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI456) ;
		    }
		}
		break;
	      case 64:
		{
		    TYPE ZI879;
		    DECL_SPEC ZI911;

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

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI909) ) ;
		    }
		    {

    (ZI879) = NULL_type ;
		    }
		    {
 (ZI911) = dspec_none ; 
		    }
		    ZR1027 (ZI879, ZI911);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI456) ;
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

    (ZI764) = NULL_exp ;
		    }
		}
		break;
	      case 134: case 147:
		{
		    ZR1072 (ZI414, ZI909, &ZI764);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI456) ;
		    }
		}
		break;
	      case 1: case 2: case 3: case 4: case 5:
	      case 6: case 7: case 8: case 9: case 10:
	      case 11: case 33: case 65: case 77: case 78:
	      case 83: case 141:
		{
		    BASE_TYPE ZI511;
		    TYPE ZI875;
		    CV_SPEC ZI1253;

		    {
 (ZI511) = btype_none ; 
		    }
		    {

    (ZI875) = NULL_type ;
		    }
		    {
 (ZI1253) = cv_none ; 
		    }
		    ZR1254 (&ZI414, &ZI909, &ZI511, &ZI875, &ZI1253, &ZI764);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI456) ;
		    }
		}
		break;
	      case 126: case 139: case 154:
		{
		    {

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI909) ) ;
		    }
		    ZR1077 (&ZI764);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    decr_value ( OPT_VAL_external_specs ) ;
    crt_linkage = (ZI456) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	  ZL3:;
	}
	ZI431 = ZI764;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR617 PROTO_N ((ZO1215))
  PROTO_T (EXP *ZO1215)
{
    EXP ZI1215;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR614 (&ZI431);
	ZR1216 (ZI431, &ZI1215);
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
    *ZO1215 = ZI1215;
}

void
ZR1009 PROTO_N ((ZI689, ZI511, ZI414, ZI670))
  PROTO_T (DECL_SPEC ZI689 X BASE_TYPE ZI511 X TYPE ZI414 X ACCESS_LIST ZI670)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_1009:;
    {
	ZR1008 (ZI689, ZI511, ZI414, ZI670);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    {

    crt_templ_qualifier = 0 ;
		    }
		    goto ZL2_1009;
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
ZR1266 PROTO_N ((ZI425, ZO1239))
  PROTO_T (NAMESPACE *ZI425 X EXP *ZO1239)
{
    EXP ZI1239;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI431;

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

    (ZI431) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI431, &ZI1239);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI431;

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
	    {

    (ZI431) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI431, &ZI1239);
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
    *ZO1239 = ZI1239;
}

void
ZR1139 PROTO_N ((ZI1137, ZO1138))
  PROTO_T (TYPE ZI1137 X TYPE *ZO1138)
{
    TYPE ZI1138;

  ZL2_1139:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    TYPE ZI480;
	    TYPE ZI414;

	    ZR952 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1137) ) ? (ZI480) : inject_pre_type ( (ZI1137), (ZI480), 0 ) ) ;
	    }
	    ZI1137 = ZI414;
	    goto ZL2_1139;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1138 = ZI1137;
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
    *ZO1138 = ZI1138;
}

void
ZR885 PROTO_N ((ZI874, ZI875, ZI876, ZO511, ZO414, ZO783))
  PROTO_T (BASE_TYPE *ZI874 X TYPE *ZI875 X CV_SPEC *ZI876 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI574;
	BASE_TYPE ZI1390;
	TYPE ZI1391;
	CV_SPEC ZI1392;
	BASE_TYPE ZI878;
	TYPE ZI879;
	CV_SPEC ZI880;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI574) = NULL_type ;
	}
	ZR872 (ZI574, &ZI1390, &ZI1391, &ZI1392);
	ZR885 (&ZI1390, &ZI1391, &ZI1392, &ZI878, &ZI879, &ZI880);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI874) & (ZI878) ) {
	(ZI511) = join_pre_types ( (*ZI874), (ZI878) ) ;
    } else {
	(ZI511) = ( (*ZI874) | (ZI878) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI875) ) ) {
	(ZI414) = (ZI879) ;
    } else if ( IS_NULL_type ( (ZI879) ) ) {
	(ZI414) = (*ZI875) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI875), (ZI879) ) ) ;
	(ZI414) = (ZI879) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI876) & (ZI880) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI783) = ( (*ZI876) | (ZI880) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI511 = *ZI874;
	    ZI414 = *ZI875;
	    ZI783 = *ZI876;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO511 = ZI511;
    *ZO414 = ZI414;
    *ZO783 = ZI783;
}

void
ZR1394 PROTO_N ((ZI1393, ZO419))
  PROTO_T (NAMESPACE *ZI1393 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;

	    ZR475 (*ZI1393, &ZI480);
	    ZR476 (*ZI1393, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( (*ZI1393), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI1393) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI519;
	    BASE_TYPE ZI520;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    {

    (ZI519) = DEREF_id ( nspace_name ( (*ZI1393) ) ) ;
	    }
	    {
 (ZI520) = btype_none ; 
	    }
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
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
	    ZR516 (&ZI522, &ZI523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    (ZI478) = make_pseudo_destr ( (ZI519), (ZI520), (ZI522), (ZI523) ) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI1393), (ZI478), 0 ) ;
    last_namespace = (*ZI1393) ;
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
ZR1267 PROTO_N ((ZI425, ZO1239))
  PROTO_T (NAMESPACE *ZI425 X EXP *ZO1239)
{
    EXP ZI1239;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI431;

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

    (ZI431) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI431, &ZI1239);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    int ZI480;
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI431;

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
	    {

    (ZI431) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI431, &ZI1239);
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
    *ZO1239 = ZI1239;
}

void
ZR1268 PROTO_N ((ZO1239))
  PROTO_T (EXP *ZO1239)
{
    EXP ZI1239;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    NAMESPACE ZI425;
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI431;

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

    (ZI431) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI431, &ZI1239);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI425;
	    int ZI480;
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI431;

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
	    {

    (ZI431) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI431, &ZI1239);
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
    *ZO1239 = ZI1239;
}

void
ZR605 PROTO_N ((ZO1231))
  PROTO_T (EXP *ZO1231)
{
    EXP ZI1231;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR601 (&ZI431);
	ZR1232 (ZI431, &ZI1231);
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
    *ZO1231 = ZI1231;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
