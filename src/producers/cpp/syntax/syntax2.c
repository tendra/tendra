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
ZR842 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	DECL_SPEC ZI493;
	int ZI844;
	NAMESPACE ZI425;
	IDENTIFIER ZI820;
	IDENTIFIER ZI419;

	{
	    switch (CURRENT_TERMINAL) {
	      case 155:
		{
		    ADVANCE_LEXER;
		    {
 (ZI844) = 1 ; 
		    }
		    ZR1328 (&ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 142: case 143: case 144:
		{
		    ZR827 (&ZI493);
		    ZR1327 (&ZI844);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {
 (ZI493) = dspec_none ; 
		    }
		    {
 (ZI844) = 0 ; 
		    }
		}
		break;
	    }
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

    add_base_class ( (ZI419), (ZI493), (ZI844) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1284 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 141: case 147:
	{
	    ZR1268 (&ZI431);
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
 (ZI456) = 1 ; 
	    }
	    ZR1430 (&ZI456, &ZI431);
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
ZR1008 PROTO_N ((ZI689, ZI511, ZI497, ZI670))
  PROTO_T (DECL_SPEC ZI689 X BASE_TYPE ZI511 X TYPE ZI497 X ACCESS_LIST ZI670)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI414;
	IDENTIFIER ZI419;
	int ZI558;
	IDENTIFIER ZI459;
	EXP ZI431;

	ZR950 (ZI497, &ZI414, &ZI419, &ZI558);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
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

    IGNORE clear_access ( (ZI459), &(ZI670) ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	}
	ZR1004 (ZI558, ZI459, &ZI431);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    int def = init_object ( (ZI459), (ZI431) ) ;
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
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1033 PROTO_N ((ZI414, ZI689, ZO431))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689 X EXP *ZO431)
{
    EXP ZI431;

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
	{

    (ZI431) = NULL_exp ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 105:
	{
	    ZR1062 (ZI414, ZI689, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 134: case 147:
	{
	    ZR1072 (ZI414, ZI689, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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
	    ZR1254 (&ZI414, &ZI689, &ZI511, &ZI875, &ZI1253, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI689) ) ;
	    }
	    ZR1077 (&ZI431);
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
ZR1286 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI414;
	int ZI551;
	EXP ZI493;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
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
	ZR581 (&ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* n is the number of type definitions in t */
    (ZI431) = make_cast_exp ( (ZI414), (ZI493), (ZI551) ) ;
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
	    EXP ZI493;
	    EXP ZI1278;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR491 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1278) = make_paren_exp ( (ZI493) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1240 (ZI1278, &ZI431);
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
ZR1002 PROTO_N ((ZI459, ZO497))
  PROTO_T (IDENTIFIER ZI459 X SID_LIST_EXP *ZO497)
{
    SID_LIST_EXP ZI497;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;
	SID_LIST_EXP ZI480;

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
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1002 (ZI459, &ZI480);
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
	    }
	}
	{

    CONS_exp ( (ZI431), (ZI480), (ZI497) ) ;
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
ZR776 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 288:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {
 unreached_code = 0 ; 
	    }
	    ZR661 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_reach_stmt ( (ZI493), 1 ) ;
	    }
	}
	break;
      case 322:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {
 unreached_code = 1 ; 
	    }
	    ZR661 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_reach_stmt ( (ZI493), 0 ) ;
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
ZR1161 PROTO_N ((ZI1157, ZI1158, ZO1159, ZO1160))
  PROTO_T (TYPE ZI1157 X IDENTIFIER ZI1158 X TYPE *ZO1159 X IDENTIFIER *ZO1160)
{
    TYPE ZI1159;
    IDENTIFIER ZI1160;

  ZL2_1161:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    IDENTIFIER ZI419;
	    QUALIFIER ZI455;
	    int ZI456;
	    TYPE ZI480;
	    TYPE ZI414;

	    ZI419 = ZI1158;
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	    }
	    ZR952 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1157) ) ? (ZI480) : inject_pre_type ( (ZI1157), (ZI480), 0 ) ) ;
	    }
	    ZI1157 = ZI414;
	    ZI1158 = ZI419;
	    goto ZL2_1161;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1159 = ZI1157;
	    ZI1160 = ZI1158;
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
    *ZO1159 = ZI1159;
    *ZO1160 = ZI1160;
}

void
ZR503 PROTO_N ((ZO419))
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
	  case 9:
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

    crt_id_qualifier = qual_full ;
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
ZR1019 PROTO_N ((ZI558, ZO431, ZO459))
  PROTO_T (EXP ZI558 X EXP *ZO431 X EXP *ZO459)
{
    EXP ZI431;
    EXP ZI459;

    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    NAMESPACE ZI512;
	    int ZI456;

	    ADVANCE_LEXER;
	    {

    (ZI512) = ctor_begin () ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1: case 2: case 3: case 4: case 7:
		  case 8: case 9: case 65: case 83:
		    {
			ZR1017 (ZI512);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{
 (ZI456) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI456) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI431) = ctor_end ( (ZI512), (ZI558), (ZI456) ) ;
	    }
	    {

    (ZI459) = NULL_exp ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI459) = NULL_exp ;
    (ZI431) = ctor_none ( (ZI558), &(ZI459) ) ;
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
    *ZO459 = ZI459;
}

void
ZR1289 PROTO_N ((ZI1287, ZO431))
  PROTO_T (EXP *ZI1287 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI480;
	    SID_LIST_EXP ZI497;

	    ADVANCE_LEXER;
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1287), (ZI480), (ZI497) ) ;
	    }
	    {

    (ZI431) = make_comma_exp ( (ZI497) ) ;
	    }
	}
	break;
      default:
	{
	    ZI431 = *ZI1287;
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
ZR472 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
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

    (ZI419) = (ZI460) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
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
ZR761 PROTO_N ((ZI554, ZO459))
  PROTO_T (int ZI554 X IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI574;
	BASE_TYPE ZI874;
	TYPE ZI1597;
	CV_SPEC ZI1598;
	BASE_TYPE ZI511;
	TYPE ZI875;
	CV_SPEC ZI876;
	DECL_SPEC ZI909;
	TYPE ZI879;
	DECL_SPEC ZI911;
	TYPE ZI414;
	IDENTIFIER ZI419;
	int ZI557;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI574) = NULL_type ;
	}
	ZR872 (ZI574, &ZI874, &ZI1597, &ZI1598);
	ZR885 (&ZI874, &ZI1597, &ZI1598, &ZI511, &ZI875, &ZI876);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI909) = dspec_none ; 
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI911) = complete_dspec ( (ZI909), (ZI511), (ZI875), (ZI876) ) ;
    (ZI879) = complete_pre_type ( (ZI511), (ZI875), (ZI876), 0 ) ;
    have_type_specifier = 0 ;
	}
	{

    crt_templ_qualifier = 0 ;
	}
	ZR961 (ZI879, &ZI414, &ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI557) = no_type_defns - (ZI554) ;
	}
	{

    (ZI459) = make_except_decl ( (ZI911), (ZI414), (ZI419), (ZI557) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 47: case 209:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 47:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 209:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI459) = NULL_id ;
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
    *ZO459 = ZI459;
}

void
ZR817 PROTO_N ((ZO816))
  PROTO_T (BASE_TYPE *ZO816)
{
    BASE_TYPE ZI816;

    switch (CURRENT_TERMINAL) {
      case 129:
	{
	    ADVANCE_LEXER;
	    {
 (ZI816) = btype_class ; 
	    }
	}
	break;
      case 118:
	{
	    ADVANCE_LEXER;
	    {
 (ZI816) = btype_struct ; 
	    }
	}
	break;
      case 121:
	{
	    ADVANCE_LEXER;
	    {
 (ZI816) = btype_union ; 
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
    *ZO816 = ZI816;
}

void
ZR999 PROTO_N ((ZI459, ZO497))
  PROTO_T (IDENTIFIER ZI459 X SID_LIST_EXP *ZO497)
{
    SID_LIST_EXP ZI497;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI456;
	EXP ZI493;
	SID_LIST_EXP ZI480;

	ZR998 (ZI459, &ZI456);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI456), (ZI493) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1001 (&ZI459, &ZI480);
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
	    }
	}
	{

    CONS_exp ( (ZI493), (ZI480), (ZI497) ) ;
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
ZR1290 PROTO_N ((ZI493, ZO497))
  PROTO_T (EXP *ZI493 X SID_LIST_EXP *ZO497)
{
    SID_LIST_EXP ZI497;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI480;

	    ADVANCE_LEXER;
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI493), (ZI480), (ZI497) ) ;
	    }
	}
	break;
      default:
	{
	    SID_LIST_EXP ZI480;

	    {

    (ZI480) = NULL_list ( EXP ) ;
	    }
	    {

    CONS_exp ( (*ZI493), (ZI480), (ZI497) ) ;
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
ZR834 PROTO_N ((ZO1166))
  PROTO_T (EXP *ZO1166)
{
    EXP ZI1166;

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
	ZR833 ();
	ZR1167 (ZI497, &ZI1166);
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
    *ZO1166 = ZI1166;
}

void
parse_tok_type PROTO_N ((ZO414))
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
	ZR955 (ZI480, &ZI414);
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
    *ZO414 = ZI414;
}

void
ZR1291 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 297:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR491 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_set_exp ( (ZI493) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 346:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 323:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR491 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_unused_exp ( (ZI493) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 346:
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
ZR616 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 48:
	{
	    ADVANCE_LEXER;
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
ZR620 PROTO_N ((ZO1211))
  PROTO_T (EXP *ZO1211)
{
    EXP ZI1211;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR617 (&ZI431);
	ZR1212 (ZI431, &ZI1211);
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
    *ZO1211 = ZI1211;
}

void
ZR1016 PROTO_N ((ZI512))
  PROTO_T (NAMESPACE ZI512)
{
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    SID_LIST_EXP ZI497;
	    EXP ZI431;
	    IDENTIFIER ZI419;

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

    MAKE_exp_initialiser ( type_void, (ZI497), NULL_list ( OFFSET ), 0, 0, 0, (ZI431) ) ;
	    }
	    {

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    ctor_initialise ( (ZI512), (ZI419), (ZI431) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI425;
	    IDENTIFIER ZI820;
	    IDENTIFIER ZI419;
	    QUALIFIER ZI455;
	    int ZI456;
	    SID_LIST_EXP ZI497;
	    EXP ZI431;

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

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
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

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    MAKE_exp_initialiser ( type_void, (ZI497), NULL_list ( OFFSET ), 0, 0, 0, (ZI431) ) ;
	    }
	    {

    ctor_initialise ( (ZI512), (ZI419), (ZI431) ) ;
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
ZR644 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 345:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR1291 (&ZI431);
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
ZR1167 PROTO_N ((ZI1165, ZO1166))
  PROTO_T (EXP ZI1165 X EXP *ZO1166)
{
    EXP ZI1166;

  ZL2_1167:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI497;
	    EXP ZI558;

	    ZI497 = ZI1165;
	    {

    ZI558 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI558), c ) ;
	    }
	    {

    target_decl ( lex_elif, (ZI558) ) ;
	    }
	    ZR833 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI1165 = ZI497;
		goto ZL2_1167;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI1166 = ZI1165;
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
    *ZO1166 = ZI1166;
}

void
ZR583 PROTO_N ((ZO450))
  PROTO_T (int *ZO450)
{
    int ZI450;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 131:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR1431 (&ZI450);
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
    *ZO450 = ZI450;
}

void
parse_type_param PROTO_N ((ZO459))
  PROTO_T (IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    switch (CURRENT_TERMINAL) {
      case 147:
	{
	    int ZI431;
	    TOKEN ZI497;
	    TYPE ZI414;
	    DECL_SPEC ZI689;
	    TYPE ZI875;
	    IDENTIFIER ZI419;
	    IDENTIFIER ZI460;

	    ADVANCE_LEXER;
	    {
 (ZI431) = 0 ; 
	    }
	    {

    (ZI497) = template_params ( (ZI431) ) ;
    RESCAN_LEXER ;
	    }
	    {

    (ZI414) = NULL_type ;
	    }
	    {
 (ZI689) = dspec_none ; 
	    }
	    {

    (ZI875) = make_template_type ( (ZI497), (ZI414) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 129:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1115 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI459) = make_template_param ( (ZI875), (ZI419) ) ;
    UNUSED ( (ZI689) ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 36:
		    {
			IDENTIFIER ZI820;

			ADVANCE_LEXER;
			{

    in_default_arg++ ;
			}
			ZR484 (&ZI820);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI460) = (ZI820) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
			}
			{

    in_default_arg-- ;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZI460) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
			}
		    }
		    break;
		}
	    }
	    {

    init_template_param ( (ZI459), (ZI460) ) ;
	    }
	    {

    end_template ( (ZI497) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 129: case 153:
	{
	    IDENTIFIER ZI419;
	    TYPE ZI414;

	    {
		switch (CURRENT_TERMINAL) {
		  case 129:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 153:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZR1115 (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI459) = make_type_param ( (ZI419) ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 36:
		    {
			ADVANCE_LEXER;
			{

    in_default_arg++ ;
			}
			parse_tok_type (&ZI414);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    in_default_arg-- ;
			}
			{

    object_type ( (ZI414), null_tag ) ;
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
	    }
	    {

    init_type_param ( (ZI459), (ZI414) ) ;
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
ZR832 PROTO_N ((ZI414, ZI689))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_832:;
    {
	BASE_TYPE ZI1335;
	TYPE ZI1336;
	CV_SPEC ZI1337;
	DECL_SPEC ZI1338;
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
	    goto ZL3;
	ZR906 (ZI414, &ZI1335, &ZI1336, &ZI1337, &ZI1338);
	ZR917 (&ZI414, &ZI1335, &ZI1336, &ZI1337, &ZI1338, &ZI511, &ZI875, &ZI876, &ZI909);
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
	ZR1339 (&ZI414, &ZI511, &ZI875, &ZI876, &ZI911);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	} else {
	    goto ZL2_832;
	}
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 142: case 143: case 144:
	{
	    DECL_SPEC ZI456;

	    ZR827 (&ZI456);
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
	    {
 crt_access = (ZI456) ; 
	    }
	    goto ZL2_832;
	}
	/*UNREACHED*/
      case 134: case 147:
	{
	    ZR1089 (ZI414, ZI689);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_832;
	    }
	}
	/*UNREACHED*/
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 41: case 65: case 78:
      case 83: case 141:
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
	    int ZI720;
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
 (ZI720) = 1 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1084 (ZI1073, ZI1074, ZI511, ZI670, ZI720, &ZI459);
	    ZR1092 (&ZI511, &ZI1073, &ZI1074, &ZI670, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_832;
	    }
	}
	/*UNREACHED*/
      case 26: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI689) ) ;
	    }
	    ZR1340 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_832;
	    }
	}
	/*UNREACHED*/
      case 77:
	{
	    TYPE ZI875;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI876;

	    {

    (ZI875) = NULL_type ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI876) = cv_none ; 
	    }
	    {

    IGNORE empty_decl ( (ZI689), (ZI414), (ZI511), (ZI875), (ZI876), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_832;
	}
	/*UNREACHED*/
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR413 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 39:
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
 (ZI414) = lex_close_Hround ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI414) ) report ( crt_loc, ERR_lex_expect ( (ZI414) ) ) ;
	}
    }
}

void
ZR553 PROTO_N ((ZI450, ZO431))
  PROTO_T (int ZI450 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI554;
	int ZI555;
	EXP ZI558;

	{

    suppress_usage++ ;
	}
	{

    (ZI554) = no_side_effects ;
	}
	{

    (ZI555) = no_type_defns ;
	}
	switch (CURRENT_TERMINAL) {
	  case 65:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    {
		TYPE ZI414;
		int ZI559;

		{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
		}
		if (!ZI0)
		    goto ZL3;
		ZR548 (&ZI414, &ZI559);
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

    (ZI558) = make_typeid_type ( (ZI450), (ZI414), (ZI559) ) ;
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
	      case 285: case 297: case 298: case 323: case 329:
	      case 345:
		{
		    EXP ZI493;
		    int ZI557;

		    ZR491 (&ZI493);
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

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI558) = make_typeid_exp ( (ZI450), (ZI493), (ZI557) ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	  ZL2:;
	}
	{

    suppress_usage-- ;
	}
	ZI431 = ZI558;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR593 PROTO_N ((ZI450, ZO431))
  PROTO_T (int ZI450 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI554;
	int ZI555;
	EXP ZI558;

	{

    suppress_usage++ ;
	}
	{

    (ZI554) = no_side_effects ;
	}
	{

    (ZI555) = no_type_defns ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 170:
		{
		    int ZI1414;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    {
 (ZI1414) = lex_alignof ; 
		    }
		    ZR593 (ZI1414, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 83:
		{
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR1284 (&ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 23:
		{
		    EXP ZI1279;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1279 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
		    }
		    ADVANCE_LEXER;
		    ZR1240 (ZI1279, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 25:
		{
		    TYPE ZI1265;
		    BASE_TYPE ZI511;
		    CV_SPEC ZI783;
		    TYPE ZI1428;
		    SID_LIST_EXP ZI497;
		    EXP ZI1282;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

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

    (ZI1428) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
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

    (ZI1282) = make_func_cast_exp ( (ZI1428), (ZI497) ) ;
		    }
		    ZR1240 (ZI1282, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 130:
		{
		    TYPE ZI1417;
		    EXP ZI1418;
		    int ZI551;
		    EXP ZI1271;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR552 (&ZI1417, &ZI1418, &ZI551);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    /* n is the number of type definitions in t */
    (ZI1271) = make_const_cast_exp ( (ZI1417), (ZI1418), (ZI551) ) ;
		    }
		    ZR1240 (ZI1271, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 132:
		{
		    TYPE ZI1423;
		    EXP ZI1424;
		    int ZI551;
		    EXP ZI1274;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR552 (&ZI1423, &ZI1424, &ZI551);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_dynamic_cast_exp ( (ZI1423), (ZI1424), (ZI551) ) ;
		    }
		    ZR1240 (ZI1274, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 209:
		{
		    EXP ZI1277;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    {

    (ZI1277) = make_ellipsis_exp () ;
		    }
		    ZR1240 (ZI1277, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 9:
		{
		    NAMESPACE ZI425;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    {

    ZI425 = crt_token->pp_data.ns ;
		    }
		    ADVANCE_LEXER;
		    ZR1267 (&ZI425, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 61:
		{
		    EXP ZI1407;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR581 (&ZI1407);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = make_prefix_exp ( lex_minus_Hminus, (ZI1407) ) ;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 8:
		{
		    NAMESPACE ZI425;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    {

    ZI425 = crt_token->pp_data.ns ;
		    }
		    ADVANCE_LEXER;
		    ZR1266 (&ZI425, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 65:
		{
		    ADVANCE_LEXER;
		    ZR1429 (&ZI450, &ZI554, &ZI555, &ZI558);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 71:
		{
		    EXP ZI1406;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR581 (&ZI1406);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = make_prefix_exp ( lex_plus_Hplus, (ZI1406) ) ;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 145:
		{
		    TYPE ZI1419;
		    EXP ZI1420;
		    int ZI551;
		    EXP ZI1272;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR552 (&ZI1419, &ZI1420, &ZI551);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_reinterp_cast_exp ( (ZI1419), (ZI1420), (ZI551) ) ;
		    }
		    ZR1240 (ZI1272, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 116:
		{
		    int ZI1413;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    {
 (ZI1413) = lex_sizeof ; 
		    }
		    ZR593 (ZI1413, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 78:
		{
		    EXP ZI1408;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR581 (&ZI1408);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = make_indir_exp ( (ZI1408) ) ;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 146:
		{
		    TYPE ZI1421;
		    EXP ZI1422;
		    int ZI551;
		    EXP ZI1273;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    ZR552 (&ZI1421, &ZI1422, &ZI551);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI1273) = make_static_cast_exp ( (ZI1421), (ZI1422), (ZI551) ) ;
		    }
		    ZR1240 (ZI1273, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 148:
		{
		    EXP ZI1276;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    {

    (ZI1276) = make_this_exp () ;
		    }
		    ZR1240 (ZI1276, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 152:
		{
		    int ZI1416;
		    EXP ZI1270;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    {
 (ZI1416) = lex_typeid ; 
		    }
		    ZR553 (ZI1416, &ZI1270);
		    ZR1240 (ZI1270, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 329:
		{
		    int ZI1415;
		    EXP ZI1269;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ADVANCE_LEXER;
		    {
 (ZI1415) = lex_vtable ; 
		    }
		    ZR553 (ZI1415, &ZI1269);
		    ZR1240 (ZI1269, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 33:
		{
		    EXP ZI1409;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

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
		    ZR581 (&ZI1409);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = make_ref_exp ( (ZI1409), 0 ) ;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
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
		    TYPE ZI1426;
		    SID_LIST_EXP ZI497;
		    EXP ZI1280;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

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

    (ZI1426) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
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

    (ZI1280) = make_func_cast_exp ( (ZI1426), (ZI497) ) ;
		    }
		    ZR1240 (ZI1280, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 17: case 18: case 19: case 20: case 21:
	      case 22: case 135: case 150:
		{
		    EXP ZI1275;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ZR437 (&ZI1275);
		    ZR1240 (ZI1275, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 62:
		{
		    EXP ZI1410;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

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
		    ZR581 (&ZI1410);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = make_not_exp ( (ZI1410) ) ;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 1: case 3: case 5: case 6: case 141:
		{
		    IDENTIFIER ZI419;
		    EXP ZI1283;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    ZR477 (&ZI419);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
		    }
		    ZR1240 (ZI1283, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 2: case 7:
		{
		    IDENTIFIER ZI419;
		    TYPE ZI1265;
		    BASE_TYPE ZI511;
		    CV_SPEC ZI783;
		    TYPE ZI1427;
		    SID_LIST_EXP ZI497;
		    EXP ZI1281;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

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

    (ZI1427) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
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

    (ZI1281) = make_func_cast_exp ( (ZI1427), (ZI497) ) ;
		    }
		    ZR1240 (ZI1281, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 131: case 140:
		{
		    int ZI456;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    {
 (ZI456) = 0 ; 
		    }
		    ZR1430 (&ZI456, &ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      case 43: case 59: case 69: case 85:
		{
		    int ZI1411;
		    EXP ZI1412;
		    EXP ZI493;
		    int ZI557;
		    int ZI559;
		    TYPE ZI414;

		    {
 (ZI1411) = crt_lex_token ; 
		    }
		    ZR596 ();
		    ZR581 (&ZI1412);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI493) = make_uminus_exp ( (ZI1411), (ZI1412) ) ;
		    }
		    {

    (ZI557) = no_side_effects - (ZI554) ;
		    }
		    {

    (ZI559) = no_type_defns - (ZI555) ;
		    }
		    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (ZI450) ) ;
		    }
		    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (ZI450) ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    suppress_usage-- ;
	}
	ZI431 = ZI558;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR917 PROTO_N ((ZI574, ZI874, ZI875, ZI876, ZI909, ZO511, ZO414, ZO783, ZO689))
  PROTO_T (TYPE *ZI574 X BASE_TYPE *ZI874 X TYPE *ZI875 X CV_SPEC *ZI876 X DECL_SPEC *ZI909 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783 X DECL_SPEC *ZO689)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;
    DECL_SPEC ZI689;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI1385;
	TYPE ZI1386;
	CV_SPEC ZI1387;
	DECL_SPEC ZI1388;
	BASE_TYPE ZI878;
	TYPE ZI879;
	CV_SPEC ZI880;
	DECL_SPEC ZI911;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR906 (*ZI574, &ZI1385, &ZI1386, &ZI1387, &ZI1388);
	ZR917 (ZI574, &ZI1385, &ZI1386, &ZI1387, &ZI1388, &ZI878, &ZI879, &ZI880, &ZI911);
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
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI909) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI689) = ( (*ZI909) | (ZI911) ) ;
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
	    ZI689 = *ZI909;
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
    *ZO689 = ZI689;
}

void
ZR477 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    IDENTIFIER ZI478;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	}
	break;
      case 1:
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
      case 3:
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
      case 6:
	{
	    IDENTIFIER ZI478;

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
	}
	break;
      case 141:
	{
	    IDENTIFIER ZI478;

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
ZR771 PROTO_N ((ZO431))
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
	EXP ZI558;

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

    (ZI493) = begin_try_stmt ( 0 ) ;
	}
	ZR678 (&ZI456);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI558) = cont_try_stmt ( (ZI493), (ZI456) ) ;
	}
	ZR770 (ZI558);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI670) ; 
	}
	{

    (ZI431) = end_try_stmt ( (ZI558), 0 ) ;
	}
	{

    unreached_fall = 1 ;
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
ZR1072 PROTO_N ((ZI414, ZI689, ZO431))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689 X EXP *ZO431)
{
    EXP ZI431;

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
	ZR1033 (ZI875, ZI689, &ZI431);
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
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1429 PROTO_N ((ZI450, ZI554, ZI555, ZO558))
  PROTO_T (int *ZI450 X int *ZI554 X int *ZI555 X EXP *ZO558)
{
    EXP ZI558;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI414;
	int ZI559;
	EXP ZI493;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR548 (&ZI414, &ZI559);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI493) = NULL_exp ;
	}
	{

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (*ZI450) ) ;
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
	    EXP ZI1425;
	    EXP ZI1278;
	    EXP ZI493;
	    int ZI557;
	    int ZI559;
	    TYPE ZI414;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR491 (&ZI1425);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1278) = make_paren_exp ( (ZI1425) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1240 (ZI1278, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI557) = no_side_effects - (*ZI554) ;
	    }
	    {

    (ZI559) = no_type_defns - (*ZI555) ;
	    }
	    {

    (ZI414) = typeof_exp ( &(ZI493), (ZI557), (*ZI450) ) ;
	    }
	    {

    (ZI558) = make_sizeof_exp ( (ZI414), (ZI493), (ZI559), (*ZI450) ) ;
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
    *ZO558 = ZI558;
}

void
ZR959 PROTO_N ((ZO414, ZO419))
  PROTO_T (TYPE *ZO414 X IDENTIFIER *ZO419)
{
    TYPE ZI414;
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI1372;
	TYPE ZI1373;

	{

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR942 (&ZI1372);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI1373) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1372) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR1161 (ZI1373, ZI1372, &ZI414, &ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1371 (&ZI414, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI1370;
	    int ZI943;
	    TYPE ZI1376;
	    IDENTIFIER ZI1377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1370) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1370) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR944 (ZI943, &ZI1376);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI1377) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1377) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1161 (ZI1376, ZI1377, &ZI414, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI431;
	    TYPE ZI1374;
	    IDENTIFIER ZI1375;

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
	    ZR953 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI431) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1374) ) ;
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
	    {

    HASHID nm = lookup_anon () ;
    (ZI1375) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1375) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1161 (ZI1374, ZI1375, &ZI414, &ZI419);
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
	    ZR959 (&ZI480, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI414) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI419) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI419) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
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
    *ZO419 = ZI419;
}

void
ZR1430 PROTO_N ((ZI456, ZO431))
  PROTO_T (int *ZI456 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 140:
	{
	    int ZI457;
	    SID_LIST_EXP ZI497;
	    TYPE ZI414;
	    int ZI551;
	    int ZI459;
	    EXP ZI574;
	    EXP ZI455;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {

    (ZI457) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
	    }
	    ZR571 (&ZI497, &ZI414, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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

    (ZI574) = begin_new_try () ;
	    }
	    ZR569 (ZI414, &ZI455);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = end_new_try ( (ZI574), (ZI455) ) ;
	    }
	    {

    (ZI431) = make_new_exp ( (ZI414), (ZI551) + (ZI459), (*ZI456), (ZI497), (ZI493) ) ;
	    }
	}
	break;
      case 131:
	{
	    int ZI450;
	    EXP ZI493;

	    ZR583 (&ZI450);
	    ZR581 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_delete_exp ( (ZI450), (*ZI456), (ZI493) ) ;
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
ZR1431 PROTO_N ((ZO450))
  PROTO_T (int *ZO450)
{
    int ZI450;

    switch (CURRENT_TERMINAL) {
      case 66:
	{
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
	    ZR1432 (&ZI450);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI450) = lex_delete ; 
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
    *ZO450 = ZI450;
}

void
ZR1177 PROTO_N ((ZI1171, ZI1172, ZI1173, ZO1174, ZO1175, ZO1176))
  PROTO_T (TYPE ZI1171 X IDENTIFIER ZI1172 X int ZI1173 X TYPE *ZO1174 X IDENTIFIER *ZO1175 X int *ZO1176)
{
    TYPE ZI1174;
    IDENTIFIER ZI1175;
    int ZI1176;

  ZL2_1177:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    IDENTIFIER ZI419;
	    QUALIFIER ZI455;
	    int ZI493;
	    TYPE ZI480;
	    int ZI558;
	    TYPE ZI414;

	    ZI419 = ZI1172;
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI493) = crt_templ_qualifier ;
	    }
	    ZR946 (ZI419, &ZI480, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZI1173) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1171) ) ? (ZI480) : inject_pre_type ( (ZI1171), (ZI480), 0 ) ) ;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI493) ;
	    }
	    ZI1171 = ZI414;
	    ZI1172 = ZI419;
	    ZI1173 = ZI558;
	    goto ZL2_1177;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1174 = ZI1171;
	    ZI1175 = ZI1172;
	    ZI1176 = ZI1173;
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
    *ZO1174 = ZI1174;
    *ZO1175 = ZI1175;
    *ZO1176 = ZI1176;
}

void
ZR961 PROTO_N ((ZI497, ZO414, ZO419))
  PROTO_T (TYPE ZI497 X TYPE *ZO414 X IDENTIFIER *ZO419)
{
    TYPE ZI414;
    IDENTIFIER ZI419;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI1372;
	TYPE ZI1373;
	TYPE ZI480;

	{

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR942 (&ZI1372);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI1373) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1372) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR1161 (ZI1373, ZI1372, &ZI480, &ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI480;

	    ADVANCE_LEXER;
	    ZR1371 (&ZI480, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI1370;
	    int ZI943;
	    TYPE ZI1376;
	    IDENTIFIER ZI1377;
	    TYPE ZI480;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1370) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1370) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR944 (ZI943, &ZI1376);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI1377) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1377) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1161 (ZI1376, ZI1377, &ZI480, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI431;
	    TYPE ZI1374;
	    IDENTIFIER ZI1375;
	    TYPE ZI480;

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
	    ZR953 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI431) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1374) ) ;
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
	    {

    HASHID nm = lookup_anon () ;
    (ZI1375) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1375) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1161 (ZI1374, ZI1375, &ZI480, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI1378;
	    TYPE ZI1379;
	    TYPE ZI480;

	    ZR926 (&ZI1378);
	    ZR959 (&ZI1379, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI480) = ( IS_NULL_type ( (ZI1379) ) ? (ZI1378) : inject_pre_type ( (ZI1379), (ZI1378), 0 ) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI480;

	    {

    (ZI480) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI419) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI419) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 1 ) ) ;
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
    *ZO419 = ZI419;
}

void
ZR1056 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI493;
	SID_LIST_EXP ZI497;

	switch (CURRENT_TERMINAL) {
	  case 126:
	    break;
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
	{
	    switch (CURRENT_TERMINAL) {
	      case 19:
		{
		    {

    ZI493 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    ZI493 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	ZR499 (&ZI497);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI431) = make_asm ( (ZI493), (ZI497) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR418 ();
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
ZR1432 PROTO_N ((ZO450))
  PROTO_T (int *ZO450)
{
    int ZI450;

    switch (CURRENT_TERMINAL) {
      case 40:
	{
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
	    {
 (ZI450) = lex_delete_Harray ; 
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
	    EXP ZI431;

	    ZR491 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Array size in 'delete []' */
    old_delete_array ( (ZI431) ) ;
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
	    {
 (ZI450) = lex_delete_Harray ; 
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
    *ZO450 = ZI450;
}

void
ZR569 PROTO_N ((ZI414, ZO431))
  PROTO_T (TYPE ZI414 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    SID_LIST_EXP ZI497;

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

    (ZI431) = make_new_init ( (ZI414), (ZI497), 1 ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI431) = make_new_init ( (ZI414), NULL_list ( EXP ), 0 ) ;
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
ZR632 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI1260;

	ZR630 (&ZI1260);
	ZR1262 (&ZI1260, &ZI431);
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
ZR944 PROTO_N ((ZI943, ZO414))
  PROTO_T (int ZI943 X TYPE *ZO414)
{
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI945;
	CV_SPEC ZI783;
	SID_LIST_TYPE ZI722;

	ZR941 (&ZI945);
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
	ZR788 (&ZI783);
	ZR939 (&ZI722);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    CV_SPEC cv = func_linkage ( (ZI783) ) ;
    if ( (ZI943) ) (ZI945) |= FUNC_WEAK ;
    (ZI414) = make_func_type ( NULL_type, (ZI945), cv, (ZI722) ) ;
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
ZR1433 PROTO_N ((ZI419, ZO431))
  PROTO_T (IDENTIFIER *ZI419 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    NAMESPACE ZI1047;
	    IDENTIFIER ZI1048;
	    IDENTIFIER ZI1049;
	    NAMESPACE ZI425;

	    ADVANCE_LEXER;
	    ZR428 (&ZI1047);
	    ZR508 (&ZI1048);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1049) = check_id ( (ZI1047), (ZI1048), 0 ) ;
    last_namespace = (ZI1047) ;
	    }
	    {

    (ZI425) = find_nspace_id ( (ZI1049) ) ;
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    alias_namespace ( (*ZI419), (ZI425) ) ;
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
      case 64:
	{
	    DECL_SPEC ZI689;
	    TYPE ZI414;

	    {

    begin_namespace ( (*ZI419), 0 ) ;
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
ZR942 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1346 (&ZI419);
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
	    ZR1345 (&ZI425, &ZI419);
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
	    ZR1344 (&ZI425, &ZI419);
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
	    IDENTIFIER ZI460;

	    ZR472 (&ZI460);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = constr_name ( last_namespace, (ZI460) ) ;
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

/* END OF FILE */
