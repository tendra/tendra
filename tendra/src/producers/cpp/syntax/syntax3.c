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
parse_type PROTO_N ((ZO414))
  PROTO_T (TYPE *ZO414)
{
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	parse_tok_type (&ZI414);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    object_type ( (ZI414), null_tag ) ;
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

    (ZI414) = NULL_type ;
	}
    }
  ZL0:;
    *ZO414 = ZI414;
}

void
ZR1096 PROTO_N ((ZO459))
  PROTO_T (IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI574;
	BASE_TYPE ZI874;
	TYPE ZI1507;
	CV_SPEC ZI1508;
	BASE_TYPE ZI511;
	TYPE ZI875;
	CV_SPEC ZI876;
	DECL_SPEC ZI909;
	TYPE ZI879;
	DECL_SPEC ZI689;
	TYPE ZI1074;
	IDENTIFIER ZI419;
	int ZI558;
	TYPE ZI414;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	{

    (ZI574) = NULL_type ;
	}
	ZR872 (ZI574, &ZI874, &ZI1507, &ZI1508);
	ZR885 (&ZI874, &ZI1507, &ZI1508, &ZI511, &ZI875, &ZI876);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI909) = dspec_none ; 
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI689) = complete_dspec ( (ZI909), (ZI511), (ZI875), (ZI876) ) ;
    (ZI879) = complete_pre_type ( (ZI511), (ZI875), (ZI876), 0 ) ;
    have_type_specifier = 0 ;
	}
	{

    crt_templ_qualifier = 0 ;
	}
	ZR950 (ZI879, &ZI1074, &ZI419, &ZI558);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	}
	{

    (ZI414) = make_cond_type ( (ZI1074) ) ;
	}
	{

    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	(ZI459) = make_func_decl ( (ZI689), (ZI414), (ZI419), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI459) = make_object_decl ( (ZI689), (ZI414), (ZI419), def ) ;
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

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO459 = ZI459;
}

void
ZR1127 PROTO_N ((ZI456, ZI574, ZO1152, ZO1153))
  PROTO_T (OFFSET ZI456 X TYPE ZI574 X OFFSET *ZO1152 X TYPE *ZO1153)
{
    OFFSET ZI1152;
    TYPE ZI1153;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_1127:;
    {
	OFFSET ZI493;
	TYPE ZI414;

	ZR1126 (ZI456, ZI574, &ZI493, &ZI414);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZI456 = ZI493;
		    ZI574 = ZI414;
		    goto ZL2_1127;
		}
		/*UNREACHED*/
	      default:
		{
		    ZI1152 = ZI493;
		    ZI1153 = ZI414;
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
    *ZO1152 = ZI1152;
    *ZO1153 = ZI1153;
}

void
ZR473 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 9:
	{
	    ZR503 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    ZR502 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 83:
	{
	    ZR504 (&ZI419);
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
    *ZO419 = ZI419;
}

void
ZR991 PROTO_N ((ZO414))
  PROTO_T (TYPE *ZO414)
{
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI497;
	TYPE ZI480;

	{

    /* Resolve pointer declarators from expressions */
    (ZI0) = predict_ptr ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR926 (&ZI497);
	ZR991 (&ZI480);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 0 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 66:
	{
	    ZR990 (&ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI414) = NULL_type ;
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
}

void
ZR1029 PROTO_N ((ZO1144))
  PROTO_T (EXP *ZO1144)
{
    EXP ZI1144;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI558;
	EXP ZI497;

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

    target_decl ( lex_if, (ZI558) ) ;
	}
	ZR1028 ();
	ZR1145 (ZI497, &ZI1144);
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
    *ZO1144 = ZI1144;
}

void
ZR1436 PROTO_N ((ZI1434, ZO431))
  PROTO_T (EXP *ZI1434 X EXP *ZO431)
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
      case 285: case 297: case 298: case 323: case 329:
      case 345:
	{
	    SID_LIST_EXP ZI480;
	    SID_LIST_EXP ZI497;

	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1434), (ZI480), (ZI497) ) ;
	    }
	    {

    (ZI431) = make_comma_exp ( (ZI497) ) ;
	    }
	}
	break;
      default:
	{
	    ZI431 = *ZI1434;
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
ZR940 PROTO_N ((ZO414, ZO419, ZO558))
  PROTO_T (TYPE *ZO414 X IDENTIFIER *ZO419 X int *ZO558)
{
    TYPE ZI414;
    IDENTIFIER ZI419;
    int ZI558;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 65:
      case 83: case 141:
	{
	    ZR949 (&ZI414, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI497;
	    TYPE ZI480;

	    ZR926 (&ZI497);
	    ZR940 (&ZI480, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 0 ) ) ;
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
    *ZO414 = ZI414;
    *ZO419 = ZI419;
    *ZO558 = ZI558;
}

void
ZR611 PROTO_N ((ZO1223))
  PROTO_T (EXP *ZO1223)
{
    EXP ZI1223;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR608 (&ZI431);
	ZR1224 (ZI431, &ZI1223);
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
    *ZO1223 = ZI1223;
}

void
ZR736 PROTO_N ((ZO493, ZO431))
  PROTO_T (EXP *ZO493 X EXP *ZO431)
{
    EXP ZI493;
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI459;
	EXP ZI1596;
	EXP ZI558;

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
	ZR649 (&ZI1596);
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

    int def = init_object ( (ZI459), (ZI1596) ) ;
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

    (ZI558) = end_cond () ;
    in_declaration-- ;
	}
	{

    (ZI493) = bind_temporary ( (ZI558) ) ;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI493), (ZI431) ) ;
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

    (ZI493) = NULL_exp ;
	    }
	    {

    MAKE_exp_location ( type_void, crt_loc, (ZI493), (ZI431) ) ;
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
      case 156: case 170: case 184: case 205: case 209:
      case 285: case 297: case 298: case 323: case 329:
      case 345:
	{
	    EXP ZI558;

	    ZR491 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = bind_temporary ( (ZI558) ) ;
	    }
	    {

    MAKE_exp_location ( type_void, crt_loc, (ZI493), (ZI431) ) ;
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
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO493 = ZI493;
    *ZO431 = ZI431;
}

void
ZR987 PROTO_N ((ZO414))
  PROTO_T (TYPE *ZO414)
{
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI497;
	TYPE ZI480;

	{

    /* Resolve pointer or reference declarators from expressions */
    (ZI0) = predict_ptr ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR926 (&ZI497);
	ZR987 (&ZI480);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 0 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    (ZI414) = NULL_type ;
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
}

void
ZR863 PROTO_N ((ZI431))
  PROTO_T (IDENTIFIER ZI431)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI864;
	IDENTIFIER ZI419;
	EXP ZI558;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI864 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    {

    ZI864 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI864 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI864 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI419) = (ZI864) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI419) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR1083 (&ZI558);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IDENTIFIER id = constr_name ( last_namespace, (ZI419) ) ;
    IGNORE make_enumerator ( (ZI431), id, (ZI558) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR950 PROTO_N ((ZI497, ZO414, ZO419, ZO558))
  PROTO_T (TYPE ZI497 X TYPE *ZO414 X IDENTIFIER *ZO419 X int *ZO558)
{
    TYPE ZI414;
    IDENTIFIER ZI419;
    int ZI558;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI480;

	ZR940 (&ZI480, &ZI419, &ZI558);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( !IS_NULL_type ( (ZI497) ) ) template_decl ( (ZI497) ) ;
	}
	{

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
    *ZO419 = ZI419;
    *ZO558 = ZI558;
}

void
ZR1004 PROTO_N ((ZI558, ZI459, ZO431))
  PROTO_T (int ZI558 X IDENTIFIER ZI459 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	SID_LIST_EXP ZI497;

	{

    (ZI0) = (ZI558) ;
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
	ZR1002 (ZI459, &ZI497);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_exp_initialiser ( type_void, (ZI497), NULL_list ( OFFSET ), 0, 0, 0, (ZI431) ) ;
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
	    ZR998 (ZI459, &ZI431);
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
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
parse_file PROTO_N ((ZI414, ZI689))
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
	EXP ZI431;

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
	{

    (ZI431) = NULL_exp ;
	}
	{

    external_declaration ( (ZI431), 1 ) ;
	}
	ZR1027 (ZI414, ZI689);
	switch (CURRENT_TERMINAL) {
	  case 32:
	    break;
	  case 354:
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
	    EXP ZI431;

	    ZR1062 (ZI414, ZI689, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
	    }
	    ZR1027 (ZI414, ZI689);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      case 134: case 147:
	{
	    EXP ZI431;

	    ZR1072 (ZI414, ZI689, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
	    }
	    ZR1027 (ZI414, ZI689);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 77: case 78:
      case 83: case 141:
	{
	    BASE_TYPE ZI511;
	    TYPE ZI875;
	    CV_SPEC ZI1253;
	    EXP ZI431;

	    {
 (ZI511) = btype_none ; 
	    }
	    {

    (ZI875) = NULL_type ;
	    }
	    {
 (ZI1253) = cv_none ; 
	    }
	    ZR1254 (&ZI414, &ZI689, &ZI511, &ZI875, &ZI1253, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
	    }
	    ZR1027 (ZI414, ZI689);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
      case 26: case 30: case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI689) ) ;
	    }
	    ZR1255 ();
	    ZR1027 (ZI414, ZI689);
	    switch (CURRENT_TERMINAL) {
	      case 32:
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
ZR1439 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 297:
	{
	    EXP ZI1593;
	    EXP ZI1594;

	    ADVANCE_LEXER;
	    ZR491 (&ZI1593);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1594) = make_set_exp ( (ZI1593) ) ;
	    }
	    ZR1595 (&ZI1594, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 323:
	{
	    EXP ZI1590;
	    EXP ZI1591;

	    ADVANCE_LEXER;
	    ZR491 (&ZI1590);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1591) = make_unused_exp ( (ZI1590) ) ;
	    }
	    ZR1595 (&ZI1591, &ZI431);
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
ZR1312 PROTO_N ((ZI425, ZI1310, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZI1310 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI520;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    ADVANCE_LEXER;
	    {
 (ZI520) = btype_none ; 
	    }
	    ZI521 = *ZI425;
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

    (ZI478) = make_pseudo_destr ( (*ZI1310), (ZI520), (ZI522), (ZI523) ) ;
	    }
	    {

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
	    }
	}
	break;
      default:
	{
	    ZI419 = *ZI1310;
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
ZR1024 PROTO_N ((ZO431))
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
	    switch (CURRENT_TERMINAL) {
	      case 41: case 64:
		{
		    ZR1022 (ZI558, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 151:
		{
		    EXP ZI456;

		    ZR1023 (&ZI456);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI456) ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( crt_func_id ) ;
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
ZR1110 PROTO_N ((ZO714))
  PROTO_T (int *ZO714)
{
    int ZI714;

    switch (CURRENT_TERMINAL) {
      case 134:
	{
	    ADVANCE_LEXER;
	    {
 (ZI714) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI714) = 0 ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *ZO714 = ZI714;
}

void
parse_offset PROTO_N ((ZI456, ZI574, ZO493, ZO414))
  PROTO_T (OFFSET ZI456 X TYPE ZI574 X OFFSET *ZO493 X TYPE *ZO414)
{
    OFFSET ZI493;
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	OFFSET ZI558;
	TYPE ZI1128;

	ZR1125 (ZI456, ZI574, &ZI558, &ZI1128);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZR1127 (ZI558, ZI1128, &ZI493, &ZI414);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    ZI493 = ZI558;
		    ZI414 = ZI1128;
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
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	ZI493 = ZI456;
	ZI414 = ZI574;
    }
  ZL0:;
    *ZO493 = ZI493;
    *ZO414 = ZI414;
}

void
ZR1440 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI558;
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    ZR651 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = begin_case_stmt ( (ZI558), 0 ) ;
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
	    ZR661 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_case_stmt ( (ZI493), (ZI456) ) ;
	    }
	}
	break;
      case 100:
	{
	    EXP ZI493;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {

    (ZI493) = begin_default_stmt ( 0 ) ;
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
	    ZR661 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_default_stmt ( (ZI493), (ZI456) ) ;
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
ZR1313 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    NAMESPACE ZI1395;
	    IDENTIFIER ZI1396;

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

    (ZI1395) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI1395) ;
	    }
	    {

    (ZI1396) = check_id ( (ZI1395), (ZI460), 0 ) ;
    last_namespace = (ZI1395) ;
	    }
	    ZR1398 (ZI425, &ZI1396, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 43:
      case 141: case 147:
	{
	    NAMESPACE ZI1393;

	    {

    (ZI1393) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI1393) ;
	    }
	    ZR1394 (&ZI1393, &ZI419);
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
    *ZO419 = ZI419;
}

void
parse_nat PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR651 (&ZI431);
	if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR649 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR496 (&ZI431);
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
    *ZO431 = ZI431;
}

void
parse_param PROTO_N ((ZI574, ZI497, ZO459))
  PROTO_T (TYPE ZI574 X int ZI497 X IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR971 (ZI574, ZI497, &ZI459);
	if ((CURRENT_TERMINAL) == 354) {
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

    (ZI459) = NULL_id ;
	}
    }
  ZL0:;
    *ZO459 = ZI459;
}

void
ZR1315 PROTO_N ((ZI425, ZI1314, ZO419))
  PROTO_T (NAMESPACE *ZI425 X NAMESPACE *ZI1314 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI1399;
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI1400;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1399 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI1399 = crt_token->pp_data.id.use ;
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
    qual_namespace = (*ZI1314) ;
	    }
	    {

    (ZI460) = check_id ( (*ZI1314), (ZI1399), 0 ) ;
    last_namespace = (*ZI1314) ;
	    }
	    {

    (ZI1400) = check_id ( (*ZI425), (ZI460), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	    ZR1402 (ZI425, &ZI1400, &ZI419);
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
	    IDENTIFIER ZI518;

	    ZR475 (*ZI1314, &ZI480);
	    ZR476 (*ZI1314, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1314) ;
	    }
	    {

    (ZI518) = check_id ( (*ZI1314), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI1314) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI425), (ZI518), 0 ) ;
    last_namespace = (*ZI425) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI519;
	    BASE_TYPE ZI520;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (*ZI1314) ;
	    }
	    {

    (ZI519) = DEREF_id ( nspace_name ( (*ZI1314) ) ) ;
	    }
	    {
 (ZI520) = btype_none ; 
	    }
	    ZI521 = *ZI1314;
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

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
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
ZR1188 PROTO_N ((ZI1182, ZI1183, ZI1184, ZO1185, ZO1186, ZO1187))
  PROTO_T (EXP ZI1182 X EXP ZI1183 X int ZI1184 X EXP *ZO1185 X EXP *ZO1186 X int *ZO1187)
{
    EXP ZI1185;
    EXP ZI1186;
    int ZI1187;

  ZL2_1188:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI497;
	    int ZI670;
	    EXP ZI558;
	    int ZI574;
	    EXP ZI456;
	    EXP ZI431;

	    ZI497 = ZI1183;
	    ZI670 = ZI1184;
	    {

    ZI558 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI558), c ) ;
	    }
	    {

    (ZI574) = unreached_code ;
    if ( (ZI574) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR678 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI431) = cont_hash_if_stmt ( (ZI1182), (ZI558), (ZI456) ) ;
	    }
	    ZI1182 = ZI431;
	    ZI1183 = ZI497;
	    ZI1184 = ZI670;
	    goto ZL2_1188;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1185 = ZI1182;
	    ZI1186 = ZI1183;
	    ZI1187 = ZI1184;
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
    *ZO1185 = ZI1185;
    *ZO1186 = ZI1186;
    *ZO1187 = ZI1187;
}

void
ZR873 PROTO_N ((ZO511, ZO414, ZO783))
  PROTO_T (BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI574;
	BASE_TYPE ZI874;
	TYPE ZI875;
	CV_SPEC ZI876;

	{

    (ZI574) = NULL_type ;
	}
	ZR872 (ZI574, &ZI874, &ZI875, &ZI876);
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 7: case 8: case 9: case 25:
	      case 83: case 97: case 98: case 102: case 104:
	      case 106: case 110: case 111: case 114: case 115:
	      case 118: case 121: case 122: case 123: case 124:
	      case 127: case 129: case 153: case 156: case 184:
	      case 285: case 298:
		{
		    BASE_TYPE ZI878;
		    TYPE ZI879;
		    CV_SPEC ZI880;

		    ZR873 (&ZI878, &ZI879, &ZI880);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI874) & (ZI878) ) {
	(ZI511) = join_pre_types ( (ZI874), (ZI878) ) ;
    } else {
	(ZI511) = ( (ZI874) | (ZI878) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI875) ) ) {
	(ZI414) = (ZI879) ;
    } else if ( IS_NULL_type ( (ZI879) ) ) {
	(ZI414) = (ZI875) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI875), (ZI879) ) ) ;
	(ZI414) = (ZI879) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI876) & (ZI880) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI783) = ( (ZI876) | (ZI880) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI511 = ZI874;
		    ZI414 = ZI875;
		    ZI783 = ZI876;
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
    *ZO511 = ZI511;
    *ZO414 = ZI414;
    *ZO783 = ZI783;
}

void
ZR502 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	NAMESPACE ZI425;
	IDENTIFIER ZI460;

	switch (CURRENT_TERMINAL) {
	  case 8:
	    {

    ZI425 = crt_token->pp_data.ns ;
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
    qual_namespace = (ZI425) ;
	}
	{

    (ZI419) = check_id ( (ZI425), (ZI460), 0 ) ;
    last_namespace = (ZI425) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1104 PROTO_N ((ZO497))
  PROTO_T (SID_LIST_TYPE *ZO497)
{
    SID_LIST_TYPE ZI497;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI574;
	int ZI551;
	TYPE ZI414;
	SID_LIST_TYPE ZI480;

	ZR548 (&ZI574, &ZI551);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI414) = check_except_type ( (ZI574), (ZI551) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1384 (&ZI480);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI480) = NULL_list ( TYPE ) ;
		    }
		}
		break;
	    }
	}
	{

    (ZI497) = cons_type_set ( (ZI480), (ZI414) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO497 = ZI497;
}

void
ZR1317 PROTO_N ((ZI425, ZI1316, ZO419))
  PROTO_T (NAMESPACE *ZI425 X NAMESPACE *ZI1316 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI1403;

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
    qual_namespace = (*ZI1316) ;
	    }
	    {

    (ZI1403) = check_id ( (*ZI1316), (ZI460), 0 ) ;
    last_namespace = (*ZI1316) ;
	    }
	    ZR1405 (ZI425, &ZI1403, &ZI419);
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

	    ZR475 (*ZI1316, &ZI480);
	    ZR476 (*ZI1316, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI1316) ;
	    }
	    {

    (ZI419) = check_id ( (*ZI1316), (ZI478), (ZI480) ) ;
    last_namespace = (*ZI1316) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI519;
	    BASE_TYPE ZI520;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (*ZI1316) ;
	    }
	    {

    (ZI519) = DEREF_id ( nspace_name ( (*ZI1316) ) ) ;
	    }
	    {
 (ZI520) = btype_none ; 
	    }
	    ZI521 = *ZI1316;
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

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
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
ZR484 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1604 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI425;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1603 (&ZI425, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI425;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1602 (&ZI425, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4:
	{
	    IDENTIFIER ZI478;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = (ZI478) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
	{
	    ZR477 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 7:
	{
	    ZR472 (&ZI419);
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
    *ZO419 = ZI419;
}

void
ZR951 PROTO_N ((ZO414))
  PROTO_T (TYPE *ZO414)
{
    TYPE ZI414;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    ZR954 (&ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI1380;

	    ZR926 (&ZI1380);
	    ZR1382 (&ZI1380, &ZI414);
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
    *ZO414 = ZI414;
}

void
parse_func PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR1024 (&ZI431);
	if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR516 PROTO_N ((ZO419, ZO511))
  PROTO_T (IDENTIFIER *ZO419 X BASE_TYPE *ZO511)
{
    IDENTIFIER ZI419;
    BASE_TYPE ZI511;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
	{
	    ZR508 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
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
    *ZO511 = ZI511;
}

void
ZR833 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	DECL_SPEC ZI689;
	TYPE ZI414;

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
 (ZI689) = dspec_none ; 
	}
	{

    (ZI414) = NULL_type ;
	}
	ZR832 (ZI414, ZI689);
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
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1319 PROTO_N ((ZI450))
  PROTO_T (int *ZI450)
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
      case 152: case 170: case 329:
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
		  case 329:
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
    report ( crt_loc, ERR_over_oper_bad ( (*ZI450) ) ) ;
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
ZR1192 PROTO_N ((ZI1190, ZO1191))
  PROTO_T (EXP ZI1190 X EXP *ZO1191)
{
    EXP ZI1191;

  ZL2_1192:;
    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    EXP ZI456;
	    EXP ZI431;

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
	    ZR628 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_log_or_exp ( (ZI1190), (ZI456) ) ;
	    }
	    ZI1190 = ZI431;
	    goto ZL2_1192;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1191 = ZI1190;
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
    *ZO1191 = ZI1191;
}

void
ZR504 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI460;
	NAMESPACE ZI425;

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
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR894 PROTO_N ((ZO689))
  PROTO_T (DECL_SPEC *ZO689)
{
    DECL_SPEC ZI689;

    switch (CURRENT_TERMINAL) {
      case 94:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_auto ; 
	    }
	}
	break;
      case 105:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_extern ; 
	    }
	}
	break;
      case 138:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_mutable ; 
	    }
	}
	break;
      case 112:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_register ; 
	    }
	}
	break;
      case 117:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_static ; 
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
    *ZO689 = ZI689;
}

void
ZR1320 PROTO_N ((ZO450))
  PROTO_T (int *ZO450)
{
    int ZI450;

    if ((CURRENT_TERMINAL) == 354) {
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
	ZR415 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI450) = lex_new_Harray ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {
 (ZI450) = lex_new ; 
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO450 = ZI450;
}

void
parse_id PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR484 (&ZI419);
	if ((CURRENT_TERMINAL) == 354) {
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

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	}
    }
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1321 PROTO_N ((ZO450))
  PROTO_T (int *ZO450)
{
    int ZI450;

    if ((CURRENT_TERMINAL) == 354) {
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
	ZR415 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI450) = lex_delete_Harray ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {
 (ZI450) = lex_delete ; 
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO450 = ZI450;
}

void
ZR581 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI450;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_alignof ; 
	    }
	    ZR593 (ZI450, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1284 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1279;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1279 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1240 (ZI1279, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 25:
	{
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1282;

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
	    ZR1240 (ZI1282, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	{
	    TYPE ZI414;
	    EXP ZI493;
	    int ZI551;
	    EXP ZI1271;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI493, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1271) = make_const_cast_exp ( (ZI414), (ZI493), (ZI551) ) ;
	    }
	    ZR1240 (ZI1271, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 205:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_cast_exp ( type_void, (ZI493), 0 ) ;
	    }
	}
	break;
      case 132:
	{
	    TYPE ZI414;
	    EXP ZI493;
	    int ZI551;
	    EXP ZI1274;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI493, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_dynamic_cast_exp ( (ZI414), (ZI493), (ZI551) ) ;
	    }
	    ZR1240 (ZI1274, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 209:
	{
	    EXP ZI1277;

	    ADVANCE_LEXER;
	    {

    (ZI1277) = make_ellipsis_exp () ;
	    }
	    ZR1240 (ZI1277, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI425;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1267 (&ZI425, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_prefix_exp ( lex_minus_Hminus, (ZI493) ) ;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI425;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1266 (&ZI425, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1286 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_prefix_exp ( lex_plus_Hplus, (ZI493) ) ;
	    }
	}
	break;
      case 145:
	{
	    TYPE ZI414;
	    EXP ZI493;
	    int ZI551;
	    EXP ZI1272;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI493, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_reinterp_cast_exp ( (ZI414), (ZI493), (ZI551) ) ;
	    }
	    ZR1240 (ZI1272, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 116:
	{
	    int ZI450;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_sizeof ; 
	    }
	    ZR593 (ZI450, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_indir_exp ( (ZI493) ) ;
	    }
	}
	break;
      case 146:
	{
	    TYPE ZI414;
	    EXP ZI493;
	    int ZI551;
	    EXP ZI1273;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI493, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1273) = make_static_cast_exp ( (ZI414), (ZI493), (ZI551) ) ;
	    }
	    ZR1240 (ZI1273, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 148:
	{
	    EXP ZI1276;

	    ADVANCE_LEXER;
	    {

    (ZI1276) = make_this_exp () ;
	    }
	    ZR1240 (ZI1276, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 152:
	{
	    int ZI450;
	    EXP ZI1270;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_typeid ; 
	    }
	    ZR553 (ZI450, &ZI1270);
	    ZR1240 (ZI1270, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 329:
	{
	    int ZI450;
	    EXP ZI1269;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_vtable ; 
	    }
	    ZR553 (ZI450, &ZI1269);
	    ZR1240 (ZI1269, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI493;

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
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_ref_exp ( (ZI493), 0 ) ;
	    }
	}
	break;
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
	    ZR1240 (ZI1280, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
	{
	    EXP ZI1275;

	    ZR437 (&ZI1275);
	    ZR1240 (ZI1275, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI493;

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
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_not_exp ( (ZI493) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
	{
	    IDENTIFIER ZI419;
	    EXP ZI1283;

	    ZR477 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1281;

	    ZR472 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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
	    ZR1240 (ZI1281, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI456;

	    {
 (ZI456) = 0 ; 
	    }
	    ZR1430 (&ZI456, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI450;
	    EXP ZI493;

	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR596 ();
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_uminus_exp ( (ZI450), (ZI493) ) ;
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
ZR872 PROTO_N ((ZI574, ZO511, ZO414, ZO783))
  PROTO_T (TYPE ZI574 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;

    switch (CURRENT_TERMINAL) {
      case 104:
	{
	    ADVANCE_LEXER;
	    ZR1325 (&ZI574, &ZI511, &ZI414, &ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 153:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI419;

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
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	}
	break;
      case 118: case 121: case 129:
	{
	    BASE_TYPE ZI816;

	    ZR817 (&ZI816);
	    ZR1324 (&ZI574, &ZI816, &ZI511, &ZI414, &ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 98: case 124:
	{
	    ZR784 (&ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {

    (ZI414) = NULL_type ;
	    }
	}
	break;
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 102: case 106: case 110:
      case 111: case 114: case 115: case 122: case 123:
      case 127: case 156: case 184: case 285: case 298:
	{
	    ZR808 (&ZI511, &ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI783) = cv_none ; 
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
    *ZO783 = ZI783;
}

void
ZR941 PROTO_N ((ZO945))
  PROTO_T (int *ZO945)
{
    int ZI945;

    switch (CURRENT_TERMINAL) {
      case 2: case 7: case 8: case 9: case 25:
      case 47: case 83: case 94: case 97: case 98:
      case 102: case 104: case 105: case 106: case 110:
      case 111: case 112: case 114: case 115: case 117:
      case 118: case 120: case 121: case 122: case 123:
      case 124: case 127: case 129: case 133: case 136:
      case 137: case 138: case 153: case 155: case 156:
      case 184: case 274: case 285: case 298:
	{
	    ZR975 (&ZI945);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO945 = ZI945;
}

void
ZR955 PROTO_N ((ZI497, ZO414))
  PROTO_T (TYPE ZI497 X TYPE *ZO414)
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

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI414 = ZI497;
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
ZR1196 PROTO_N ((ZI1194, ZO1195))
  PROTO_T (EXP ZI1194 X EXP *ZO1195)
{
    EXP ZI1195;

  ZL2_1196:;
    switch (CURRENT_TERMINAL) {
      case 55:
	{
	    EXP ZI456;
	    EXP ZI431;

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
	    ZR626 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_log_and_exp ( (ZI1194), (ZI456) ) ;
	    }
	    ZI1194 = ZI431;
	    goto ZL2_1196;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1195 = ZI1194;
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
    *ZO1195 = ZI1195;
}

void
ZR417 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
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
	int ZI414;

	{
 (ZI414) = lex_open_Hround ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI414) ) report ( crt_loc, ERR_lex_expect ( (ZI414) ) ) ;
	}
    }
}

void
ZR1324 PROTO_N ((ZI574, ZI816, ZO511, ZO414, ZO783))
  PROTO_T (TYPE *ZI574 X BASE_TYPE *ZI816 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI419;
	QUALIFIER ZI856;
	int ZI455;
	DECL_SPEC ZI456;
	IDENTIFIER ZI497;
	int ZI720;
	int ZI1322;
	DECL_SPEC ZI689;
	TYPE ZI1323;
	IDENTIFIER ZI558;

	{

    /* Resolve class-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    crt_templ_qualifier = 0 ;
	}
	ZR869 (&ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI856) = crt_id_qualifier ;
    (ZI455) = crt_templ_qualifier ;
	}
	{

    if ( !IS_NULL_type ( (*ZI574) ) ) template_decl ( (*ZI574) ) ;
	}
	{
 (ZI456) = crt_access ; 
	}
	{

    IDENTIFIER id = constr_name ( last_namespace, (ZI419) ) ;
    (ZI497) = begin_class_defn ( id, (*ZI816), cinfo_none, (*ZI574) ) ;
    (ZI720) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
	}
	ZR847 (&ZI1322);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    end_base_class ( crt_class, (ZI1322) ) ;
	}
	{
 (ZI689) = dspec_none ; 
	}
	{

    (ZI1323) = NULL_type ;
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
	ZR832 (ZI1323, ZI689);
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

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
	}
	{

    (ZI558) = end_class_defn ( (ZI497) ) ;
    in_function_defn = (ZI720) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
	}
	{
 crt_access = (ZI456) ; 
	}
	{

    crt_id_qualifier = (ZI856) ;
    crt_templ_qualifier = (ZI455) ;
	}
	{

    RESCAN_LEXER ;
	}
	{

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI414) ) ;
    COPY_id ( type_name ( (ZI414) ), (ZI558) ) ;
    have_type_specifier = 1 ;
	}
	{
 (ZI511) = btype_none ; 
	}
	{
 (ZI783) = cv_none ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI820;
	    IDENTIFIER ZI419;

	    {

    crt_templ_qualifier = 0 ;
	    }
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
	    {

    MAKE_type_pre ( cv_none, (*ZI816), crt_id_qualifier, (ZI414) ) ;
    COPY_id ( type_name ( (ZI414) ), (ZI419) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
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
    *ZO511 = ZI511;
    *ZO414 = ZI414;
    *ZO783 = ZI783;
}

void
ZR1325 PROTO_N ((ZI574, ZO511, ZO414, ZO783))
  PROTO_T (TYPE *ZI574 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI419;
	QUALIFIER ZI856;
	int ZI455;
	IDENTIFIER ZI497;
	IDENTIFIER ZI431;

	{

    /* Resolve enum-specifiers from elaborated-type-specifiers */
    (ZI0) = predict_class ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    crt_templ_qualifier = 0 ;
	}
	ZR869 (&ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI856) = crt_id_qualifier ;
    (ZI455) = crt_templ_qualifier ;
	}
	{

    IDENTIFIER id = constr_name ( last_namespace, (ZI419) ) ;
    (ZI497) = begin_enum_defn ( id, (*ZI574) ) ;
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
		    ZR866 (ZI497);
		    if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = end_enum_defn ( (ZI497) ) ;
	}
	{

    crt_id_qualifier = (ZI856) ;
    crt_templ_qualifier = (ZI455) ;
	}
	{

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI414) ) ;
    COPY_id ( type_name ( (ZI414) ), (ZI431) ) ;
    have_type_specifier = 1 ;
	}
	{
 (ZI511) = btype_none ; 
	}
	{
 (ZI783) = cv_none ; 
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    BASE_TYPE ZI816;
	    NAMESPACE ZI425;
	    IDENTIFIER ZI820;
	    IDENTIFIER ZI419;

	    {
 (ZI816) = btype_enum ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
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
	    {

    MAKE_type_pre ( cv_none, (ZI816), crt_id_qualifier, (ZI414) ) ;
    COPY_id ( type_name ( (ZI414) ), (ZI419) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
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
    *ZO511 = ZI511;
    *ZO414 = ZI414;
    *ZO783 = ZI783;
}

void
ZR866 PROTO_N ((ZI431))
  PROTO_T (IDENTIFIER ZI431)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_866:;
    {
	ZR863 (ZI431);
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
				goto ZL2_866;
			    }
			    /*UNREACHED*/
			  case 1: case 2: case 3: case 4:
			    {
				goto ZL2_866;
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
ZR1326 PROTO_N ((ZO414))
  PROTO_T (int *ZO414)
{
    int ZI414;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83: case 142: case 143:
      case 144: case 155:
	{
	    ZR845 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI414) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI414) = 0 ; 
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
ZR735 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	DECL_SPEC ZI689;
	TYPE ZI414;
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
 (ZI689) = dspec_none ; 
	}
	{

    (ZI414) = NULL_type ;
	}
	ZR686 (ZI414, ZI689);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI493) = NULL_exp ;
	}
	{

    (ZI431) = (ZI493) ;
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
      case 152: case 156: case 170: case 184: case 205:
      case 209: case 285: case 297: case 298: case 323:
      case 329: case 345:
	{
	    ZR669 (&ZI431);
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
ZR1023 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI670;
	EXP ZI493;
	EXP ZI456;
	EXP ZI720;
	EXP ZI558;
	EXP ZI459;

	switch (CURRENT_TERMINAL) {
	  case 151:
	    break;
	  default:
	    goto ZL1;
	}
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

    (ZI493) = begin_try_stmt ( 1 ) ;
	}
	{

    (ZI456) = begin_compound_stmt ( 1 ) ;
	}
	{

    inject_try_stmt ( (ZI493) ) ;
	}
	ZR1022 (ZI456, &ZI720);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI558) = end_compound_stmt ( (ZI720) ) ;
	}
	{

    (ZI459) = cont_try_stmt ( (ZI493), (ZI558) ) ;
	}
	ZR770 (ZI459);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI670) ; 
	}
	{

    (ZI431) = end_try_stmt ( (ZI459), 0 ) ;
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
ZR1126 PROTO_N ((ZI456, ZI574, ZO493, ZO414))
  PROTO_T (OFFSET ZI456 X TYPE ZI574 X OFFSET *ZO493 X TYPE *ZO414)
{
    OFFSET ZI493;
    TYPE ZI414;

    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    ADVANCE_LEXER;
	    ZR1125 (ZI456, ZI574, &ZI493, &ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI431;

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
	    ZR651 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    OFFSET off = offset_index ( (ZI574), (ZI431), &(ZI414) ) ;
    (ZI493) = offset_add ( (ZI456), off ) ;
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
    *ZO493 = ZI493;
    *ZO414 = ZI414;
}

/* END OF FILE */
