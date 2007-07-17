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
ZR843(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI494;
	int ZI845;
	NAMESPACE ZI426;
	IDENTIFIER ZI821;
	IDENTIFIER ZI420;

	{
	    switch (CURRENT_TERMINAL) {
	      case 155:
		{
		    ADVANCE_LEXER;
		    {
 (ZI845) = 1 ; 
		    }
		    ZR1329 (&ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 142: case 143: case 144:
		{
		    ZR828 (&ZI494);
		    ZR1328 (&ZI845);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {
 (ZI494) = dspec_none ; 
		    }
		    {
 (ZI845) = 0 ; 
		    }
		}
		break;
	    }
	}
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
	{

    add_base_class ( (ZI420), (ZI494), (ZI845) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1009(DECL_SPEC ZI690, BASE_TYPE ZI512, TYPE ZI498, ACCESS_LIST ZI671)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI415;
	IDENTIFIER ZI420;
	int ZI559;
	IDENTIFIER ZI460;
	EXP ZI432;

	ZR951 (ZI498, &ZI415, &ZI420, &ZI559);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	(ZI460) = make_func_decl ( (ZI690), (ZI415), (ZI420), def ) ;
	is_function_next = def ;
    } else {
	int def = predict_obj_defn () ;
	(ZI460) = make_object_decl ( (ZI690), (ZI415), (ZI420), def ) ;
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
	ZR1005 (ZI559, ZI460, &ZI432);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    int def = init_object ( (ZI460), (ZI432) ) ;
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
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1285(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 5: case 6:
      case 7: case 141: case 147:
	{
	    ZR1269 (&ZI432);
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
 (ZI457) = 1 ; 
	    }
	    ZR1431 (&ZI457, &ZI432);
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
ZR1034(TYPE ZI415, DECL_SPEC ZI690, EXP *ZO432)
{
    EXP ZI432;

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
	{

    (ZI432) = NULL_exp ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 105:
	{
	    ZR1063 (ZI415, ZI690, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 134: case 147:
	{
	    ZR1073 (ZI415, ZI690, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
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
	    ZR1255 (&ZI415, &ZI690, &ZI512, &ZI876, &ZI1254, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI690) ) ;
	    }
	    ZR1078 (&ZI432);
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
ZR1003(IDENTIFIER ZI460, SID_LIST_EXP *ZO498)
{
    SID_LIST_EXP ZI498;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;
	SID_LIST_EXP ZI481;

	ZR650 (&ZI432);
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
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1003 (ZI460, &ZI481);
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
	    }
	}
	{

    CONS_exp ( (ZI432), (ZI481), (ZI498) ) ;
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
ZR1287(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI415;
	int ZI552;
	EXP ZI494;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
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
	ZR582 (&ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* n is the number of type definitions in t */
    (ZI432) = make_cast_exp ( (ZI415), (ZI494), (ZI552) ) ;
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
      case 286: case 298: case 299: case 324: case 330:
      case 346:
	{
	    EXP ZI494;
	    EXP ZI1279;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR492 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1279) = make_paren_exp ( (ZI494) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1241 (ZI1279, &ZI432);
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
ZR777(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 289:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {
 unreached_code = 0 ; 
	    }
	    ZR662 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_reach_stmt ( (ZI494), 1 ) ;
	    }
	}
	break;
      case 323:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {
 unreached_code = 1 ; 
	    }
	    ZR662 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_reach_stmt ( (ZI494), 0 ) ;
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
ZR504(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	NAMESPACE ZI426;
	IDENTIFIER ZI461;

	switch (CURRENT_TERMINAL) {
	  case 9:
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

    crt_id_qualifier = qual_full ;
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
ZR1020(EXP ZI559, EXP *ZO432, EXP *ZO460)
{
    EXP ZI432;
    EXP ZI460;

    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    NAMESPACE ZI513;
	    int ZI457;

	    ADVANCE_LEXER;
	    {

    (ZI513) = ctor_begin () ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1: case 2: case 3: case 4: case 7:
		  case 8: case 9: case 65: case 83:
		    {
			ZR1018 (ZI513);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{
 (ZI457) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZI457) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    (ZI432) = ctor_end ( (ZI513), (ZI559), (ZI457) ) ;
	    }
	    {

    (ZI460) = NULL_exp ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI460) = NULL_exp ;
    (ZI432) = ctor_none ( (ZI559), &(ZI460) ) ;
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
    *ZO460 = ZI460;
}

void
ZR1162(TYPE ZI1158, IDENTIFIER ZI1159, TYPE *ZO1160, IDENTIFIER *ZO1161)
{
    TYPE ZI1160;
    IDENTIFIER ZI1161;

  ZL2_1162:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    IDENTIFIER ZI420;
	    QUALIFIER ZI456;
	    int ZI457;
	    TYPE ZI481;
	    TYPE ZI415;

	    ZI420 = ZI1159;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    ZR953 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1158) ) ? (ZI481) : inject_pre_type ( (ZI1158), (ZI481), 0 ) ) ;
	    }
	    ZI1158 = ZI415;
	    ZI1159 = ZI420;
	    goto ZL2_1162;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1160 = ZI1158;
	    ZI1161 = ZI1159;
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
    *ZO1160 = ZI1160;
    *ZO1161 = ZI1161;
}

void
ZR473(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
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

    (ZI420) = (ZI461) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
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
ZR762(int ZI555, IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI575;
	BASE_TYPE ZI875;
	TYPE ZI1598;
	CV_SPEC ZI1599;
	BASE_TYPE ZI512;
	TYPE ZI876;
	CV_SPEC ZI877;
	DECL_SPEC ZI910;
	TYPE ZI880;
	DECL_SPEC ZI912;
	TYPE ZI415;
	IDENTIFIER ZI420;
	int ZI558;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI575) = NULL_type ;
	}
	ZR873 (ZI575, &ZI875, &ZI1598, &ZI1599);
	ZR886 (&ZI875, &ZI1598, &ZI1599, &ZI512, &ZI876, &ZI877);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 (ZI910) = dspec_none ; 
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI912) = complete_dspec ( (ZI910), (ZI512), (ZI876), (ZI877) ) ;
    (ZI880) = complete_pre_type ( (ZI512), (ZI876), (ZI877), 0 ) ;
    have_type_specifier = 0 ;
	}
	{

    crt_templ_qualifier = 0 ;
	}
	ZR962 (ZI880, &ZI415, &ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI558) = no_type_defns - (ZI555) ;
	}
	{

    (ZI460) = make_except_decl ( (ZI912), (ZI415), (ZI420), (ZI558) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 47: case 210:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 47:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 210:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI460) = NULL_id ;
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
    *ZO460 = ZI460;
}

void
ZR818(BASE_TYPE *ZO817)
{
    BASE_TYPE ZI817;

    switch (CURRENT_TERMINAL) {
      case 129:
	{
	    ADVANCE_LEXER;
	    {
 (ZI817) = btype_class ; 
	    }
	}
	break;
      case 118:
	{
	    ADVANCE_LEXER;
	    {
 (ZI817) = btype_struct ; 
	    }
	}
	break;
      case 121:
	{
	    ADVANCE_LEXER;
	    {
 (ZI817) = btype_union ; 
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
    *ZO817 = ZI817;
}

void
ZR1000(IDENTIFIER ZI460, SID_LIST_EXP *ZO498)
{
    SID_LIST_EXP ZI498;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI457;
	EXP ZI494;
	SID_LIST_EXP ZI481;

	ZR999 (ZI460, &ZI457);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI457), (ZI494) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1002 (&ZI460, &ZI481);
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
	    }
	}
	{

    CONS_exp ( (ZI494), (ZI481), (ZI498) ) ;
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
ZR1290(EXP *ZI1288, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI481;
	    SID_LIST_EXP ZI498;

	    ADVANCE_LEXER;
	    ZR649 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1288), (ZI481), (ZI498) ) ;
	    }
	    {

    (ZI432) = make_comma_exp ( (ZI498) ) ;
	    }
	}
	break;
      default:
	{
	    ZI432 = *ZI1288;
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
ZR835(EXP *ZO1167)
{
    EXP ZI1167;

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
	ZR834 ();
	ZR1168 (ZI498, &ZI1167);
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
    *ZO1167 = ZI1167;
}

void
parse_tok_type(TYPE *ZO415)
{
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI512;
	TYPE ZI498;
	CV_SPEC ZI784;
	TYPE ZI481;

	ZR874 (&ZI512, &ZI498, &ZI784);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI481) = complete_pre_type ( (ZI512), (ZI498), (ZI784), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR956 (ZI481, &ZI415);
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
    *ZO415 = ZI415;
}

void
ZR1291(EXP *ZI494, SID_LIST_EXP *ZO498)
{
    SID_LIST_EXP ZI498;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI481;

	    ADVANCE_LEXER;
	    ZR649 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI494), (ZI481), (ZI498) ) ;
	    }
	}
	break;
      default:
	{
	    SID_LIST_EXP ZI481;

	    {

    (ZI481) = NULL_list ( EXP ) ;
	    }
	    {

    CONS_exp ( (*ZI494), (ZI481), (ZI498) ) ;
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
ZR617(void)
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
ZR621(EXP *ZO1212)
{
    EXP ZI1212;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR618 (&ZI432);
	ZR1213 (ZI432, &ZI1212);
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
    *ZO1212 = ZI1212;
}

void
ZR1017(NAMESPACE ZI513)
{
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    SID_LIST_EXP ZI498;
	    EXP ZI432;
	    IDENTIFIER ZI420;

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

    MAKE_exp_initialiser ( type_void, (ZI498), NULL_list ( OFFSET ), 0, 0, 0, (ZI432) ) ;
	    }
	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    ctor_initialise ( (ZI513), (ZI420), (ZI432) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83:
	{
	    NAMESPACE ZI426;
	    IDENTIFIER ZI821;
	    IDENTIFIER ZI420;
	    QUALIFIER ZI456;
	    int ZI457;
	    SID_LIST_EXP ZI498;
	    EXP ZI432;

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
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
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

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    MAKE_exp_initialiser ( type_void, (ZI498), NULL_list ( OFFSET ), 0, 0, 0, (ZI432) ) ;
	    }
	    {

    ctor_initialise ( (ZI513), (ZI420), (ZI432) ) ;
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
ZR1292(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR492 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_set_exp ( (ZI494) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 347:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 324:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR492 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_unused_exp ( (ZI494) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 347:
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
ZR645(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 346:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR1292 (&ZI432);
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
ZR584(int *ZO451)
{
    int ZI451;

    if ((CURRENT_TERMINAL) == 355) {
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
	ZR1432 (&ZI451);
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
    *ZO451 = ZI451;
}

void
parse_type_param(IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    switch (CURRENT_TERMINAL) {
      case 147:
	{
	    int ZI432;
	    TOKEN ZI498;
	    TYPE ZI415;
	    DECL_SPEC ZI690;
	    TYPE ZI876;
	    IDENTIFIER ZI420;
	    IDENTIFIER ZI461;

	    ADVANCE_LEXER;
	    {
 (ZI432) = 0 ; 
	    }
	    {

    (ZI498) = template_params ( (ZI432) ) ;
    RESCAN_LEXER ;
	    }
	    {

    (ZI415) = NULL_type ;
	    }
	    {
 (ZI690) = dspec_none ; 
	    }
	    {

    (ZI876) = make_template_type ( (ZI498), (ZI415) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 129:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1116 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI460) = make_template_param ( (ZI876), (ZI420) ) ;
    UNUSED ( (ZI690) ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 36:
		    {
			IDENTIFIER ZI821;

			ADVANCE_LEXER;
			{

    in_default_arg++ ;
			}
			ZR485 (&ZI821);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI461) = (ZI821) ;
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

    (ZI461) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
			}
		    }
		    break;
		}
	    }
	    {

    init_template_param ( (ZI460), (ZI461) ) ;
	    }
	    {

    end_template ( (ZI498) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 129: case 153:
	{
	    IDENTIFIER ZI420;
	    TYPE ZI415;

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
	    ZR1116 (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI460) = make_type_param ( (ZI420) ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 36:
		    {
			ADVANCE_LEXER;
			{

    in_default_arg++ ;
			}
			parse_tok_type (&ZI415);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    in_default_arg-- ;
			}
			{

    object_type ( (ZI415), null_tag ) ;
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
	    }
	    {

    init_type_param ( (ZI460), (ZI415) ) ;
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
ZR1168(EXP ZI1166, EXP *ZO1167)
{
    EXP ZI1167;

  ZL2_1168:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI498;
	    EXP ZI559;

	    ZI498 = ZI1166;
	    {

    ZI559 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI559), c ) ;
	    }
	    {

    target_decl ( lex_elif, (ZI559) ) ;
	    }
	    ZR834 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI1166 = ZI498;
		goto ZL2_1168;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI1167 = ZI1166;
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
    *ZO1167 = ZI1167;
}

void
ZR833(TYPE ZI415, DECL_SPEC ZI690)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_833:;
    {
	BASE_TYPE ZI1336;
	TYPE ZI1337;
	CV_SPEC ZI1338;
	DECL_SPEC ZI1339;
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
	    goto ZL3;
	ZR907 (ZI415, &ZI1336, &ZI1337, &ZI1338, &ZI1339);
	ZR918 (&ZI415, &ZI1336, &ZI1337, &ZI1338, &ZI1339, &ZI512, &ZI876, &ZI877, &ZI910);
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
	ZR1340 (&ZI415, &ZI512, &ZI876, &ZI877, &ZI912);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	} else {
	    goto ZL2_833;
	}
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 142: case 143: case 144:
	{
	    DECL_SPEC ZI457;

	    ZR828 (&ZI457);
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
	    {
 crt_access = (ZI457) ; 
	    }
	    goto ZL2_833;
	}
	/*UNREACHED*/
      case 134: case 147:
	{
	    ZR1090 (ZI415, ZI690);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_833;
	    }
	}
	/*UNREACHED*/
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 41: case 65: case 78:
      case 83: case 141:
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
	    int ZI721;
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
 (ZI721) = 1 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1085 (ZI1074, ZI1075, ZI512, ZI671, ZI721, &ZI460);
	    ZR1093 (&ZI512, &ZI1074, &ZI1075, &ZI671, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_833;
	    }
	}
	/*UNREACHED*/
      case 26: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI690) ) ;
	    }
	    ZR1341 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_833;
	    }
	}
	/*UNREACHED*/
      case 77:
	{
	    TYPE ZI876;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI877;

	    {

    (ZI876) = NULL_type ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI877) = cv_none ; 
	    }
	    {

    IGNORE empty_decl ( (ZI690), (ZI415), (ZI512), (ZI876), (ZI877), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_833;
	}
	/*UNREACHED*/
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR414(void)
{
    if ((CURRENT_TERMINAL) == 355) {
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
	int ZI415;

	{
 (ZI415) = lex_close_Hround ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI415) ) report ( crt_loc, ERR_lex_expect ( (ZI415) ) ) ;
	}
    }
}

void
ZR554(int ZI451, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI555;
	int ZI556;
	EXP ZI559;

	{

    suppress_usage++ ;
	}
	{

    (ZI555) = no_side_effects ;
	}
	{

    (ZI556) = no_type_defns ;
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
		TYPE ZI415;
		int ZI560;

		{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
		}
		if (!ZI0)
		    goto ZL3;
		ZR549 (&ZI415, &ZI560);
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

    (ZI559) = make_typeid_type ( (ZI451), (ZI415), (ZI560) ) ;
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
	      case 286: case 298: case 299: case 324: case 330:
	      case 346:
		{
		    EXP ZI494;
		    int ZI558;

		    ZR492 (&ZI494);
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

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI559) = make_typeid_exp ( (ZI451), (ZI494), (ZI558) ) ;
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
	ZI432 = ZI559;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR594(int ZI451, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI555;
	int ZI556;
	EXP ZI559;

	{

    suppress_usage++ ;
	}
	{

    (ZI555) = no_side_effects ;
	}
	{

    (ZI556) = no_type_defns ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 170:
		{
		    int ZI1415;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    {
 (ZI1415) = lex_alignof ; 
		    }
		    ZR594 (ZI1415, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 83:
		{
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR1285 (&ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 23:
		{
		    EXP ZI1280;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1280 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
		    }
		    ADVANCE_LEXER;
		    ZR1241 (ZI1280, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 25:
		{
		    TYPE ZI1266;
		    BASE_TYPE ZI512;
		    CV_SPEC ZI784;
		    TYPE ZI1429;
		    SID_LIST_EXP ZI498;
		    EXP ZI1283;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1266 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
		    }
		    ADVANCE_LEXER;
		    {
 (ZI512) = btype_none ; 
		    }
		    {
 (ZI784) = cv_none ; 
		    }
		    {

    (ZI1429) = complete_pre_type ( (ZI512), (ZI1266), (ZI784), 1 ) ;
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

    (ZI1283) = make_func_cast_exp ( (ZI1429), (ZI498) ) ;
		    }
		    ZR1241 (ZI1283, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 130:
		{
		    TYPE ZI1418;
		    EXP ZI1419;
		    int ZI552;
		    EXP ZI1272;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR553 (&ZI1418, &ZI1419, &ZI552);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_const_cast_exp ( (ZI1418), (ZI1419), (ZI552) ) ;
		    }
		    ZR1241 (ZI1272, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 132:
		{
		    TYPE ZI1424;
		    EXP ZI1425;
		    int ZI552;
		    EXP ZI1275;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR553 (&ZI1424, &ZI1425, &ZI552);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    /* n is the number of type definitions in t */
    (ZI1275) = make_dynamic_cast_exp ( (ZI1424), (ZI1425), (ZI552) ) ;
		    }
		    ZR1241 (ZI1275, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 210:
		{
		    EXP ZI1278;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    {

    (ZI1278) = make_ellipsis_exp () ;
		    }
		    ZR1241 (ZI1278, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 9:
		{
		    NAMESPACE ZI426;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    {

    ZI426 = crt_token->pp_data.ns ;
		    }
		    ADVANCE_LEXER;
		    ZR1268 (&ZI426, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 61:
		{
		    EXP ZI1408;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR582 (&ZI1408);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = make_prefix_exp ( lex_minus_Hminus, (ZI1408) ) ;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 8:
		{
		    NAMESPACE ZI426;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    {

    ZI426 = crt_token->pp_data.ns ;
		    }
		    ADVANCE_LEXER;
		    ZR1267 (&ZI426, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 65:
		{
		    ADVANCE_LEXER;
		    ZR1430 (&ZI451, &ZI555, &ZI556, &ZI559);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 71:
		{
		    EXP ZI1407;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR582 (&ZI1407);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = make_prefix_exp ( lex_plus_Hplus, (ZI1407) ) ;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 145:
		{
		    TYPE ZI1420;
		    EXP ZI1421;
		    int ZI552;
		    EXP ZI1273;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR553 (&ZI1420, &ZI1421, &ZI552);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    /* n is the number of type definitions in t */
    (ZI1273) = make_reinterp_cast_exp ( (ZI1420), (ZI1421), (ZI552) ) ;
		    }
		    ZR1241 (ZI1273, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 116:
		{
		    int ZI1414;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    {
 (ZI1414) = lex_sizeof ; 
		    }
		    ZR594 (ZI1414, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 78:
		{
		    EXP ZI1409;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR582 (&ZI1409);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = make_indir_exp ( (ZI1409) ) ;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 146:
		{
		    TYPE ZI1422;
		    EXP ZI1423;
		    int ZI552;
		    EXP ZI1274;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    ZR553 (&ZI1422, &ZI1423, &ZI552);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI1274) = make_static_cast_exp ( (ZI1422), (ZI1423), (ZI552) ) ;
		    }
		    ZR1241 (ZI1274, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 148:
		{
		    EXP ZI1277;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    {

    (ZI1277) = make_this_exp () ;
		    }
		    ZR1241 (ZI1277, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 152:
		{
		    int ZI1417;
		    EXP ZI1271;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    {
 (ZI1417) = lex_typeid ; 
		    }
		    ZR554 (ZI1417, &ZI1271);
		    ZR1241 (ZI1271, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 330:
		{
		    int ZI1416;
		    EXP ZI1270;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ADVANCE_LEXER;
		    {
 (ZI1416) = lex_vtable ; 
		    }
		    ZR554 (ZI1416, &ZI1270);
		    ZR1241 (ZI1270, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 33:
		{
		    EXP ZI1410;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

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
		    ZR582 (&ZI1410);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = make_ref_exp ( (ZI1410), 0 ) ;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 97: case 102: case 106: case 110: case 111:
	      case 114: case 115: case 122: case 123: case 127:
	      case 156: case 185: case 286: case 299:
		{
		    BASE_TYPE ZI512;
		    TYPE ZI1266;
		    CV_SPEC ZI784;
		    TYPE ZI1427;
		    SID_LIST_EXP ZI498;
		    EXP ZI1281;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ZR510 (&ZI512);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI1266) = NULL_type ;
    have_type_specifier = 1 ;
		    }
		    {
 (ZI784) = cv_none ; 
		    }
		    {

    (ZI1427) = complete_pre_type ( (ZI512), (ZI1266), (ZI784), 1 ) ;
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

    (ZI1281) = make_func_cast_exp ( (ZI1427), (ZI498) ) ;
		    }
		    ZR1241 (ZI1281, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 17: case 18: case 19: case 20: case 21:
	      case 22: case 135: case 150:
		{
		    EXP ZI1276;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ZR438 (&ZI1276);
		    ZR1241 (ZI1276, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 62:
		{
		    EXP ZI1411;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

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
		    ZR582 (&ZI1411);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = make_not_exp ( (ZI1411) ) ;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 1: case 3: case 5: case 6: case 141:
		{
		    IDENTIFIER ZI420;
		    EXP ZI1284;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ZR478 (&ZI420);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI1284) = make_id_exp ( (ZI420) ) ;
		    }
		    ZR1241 (ZI1284, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 2: case 7:
		{
		    IDENTIFIER ZI420;
		    TYPE ZI1266;
		    BASE_TYPE ZI512;
		    CV_SPEC ZI784;
		    TYPE ZI1428;
		    SID_LIST_EXP ZI498;
		    EXP ZI1282;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    ZR473 (&ZI420);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
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

    (ZI1428) = complete_pre_type ( (ZI512), (ZI1266), (ZI784), 1 ) ;
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

    (ZI1282) = make_func_cast_exp ( (ZI1428), (ZI498) ) ;
		    }
		    ZR1241 (ZI1282, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 131: case 140:
		{
		    int ZI457;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    {
 (ZI457) = 0 ; 
		    }
		    ZR1431 (&ZI457, &ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
		    }
		}
		break;
	      case 43: case 59: case 69: case 85:
		{
		    int ZI1412;
		    EXP ZI1413;
		    EXP ZI494;
		    int ZI558;
		    int ZI560;
		    TYPE ZI415;

		    {
 (ZI1412) = crt_lex_token ; 
		    }
		    ZR597 ();
		    ZR582 (&ZI1413);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI494) = make_uminus_exp ( (ZI1412), (ZI1413) ) ;
		    }
		    {

    (ZI558) = no_side_effects - (ZI555) ;
		    }
		    {

    (ZI560) = no_type_defns - (ZI556) ;
		    }
		    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (ZI451) ) ;
		    }
		    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (ZI451) ) ;
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
	ZI432 = ZI559;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR478(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    IDENTIFIER ZI479;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	}
	break;
      case 1:
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
      case 3:
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
      case 6:
	{
	    IDENTIFIER ZI479;

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
	}
	break;
      case 141:
	{
	    IDENTIFIER ZI479;

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
ZR918(TYPE *ZI575, BASE_TYPE *ZI875, TYPE *ZI876, CV_SPEC *ZI877, DECL_SPEC *ZI910, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO784, DECL_SPEC *ZO690)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI784;
    DECL_SPEC ZI690;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1386;
	TYPE ZI1387;
	CV_SPEC ZI1388;
	DECL_SPEC ZI1389;
	BASE_TYPE ZI879;
	TYPE ZI880;
	CV_SPEC ZI881;
	DECL_SPEC ZI912;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR907 (*ZI575, &ZI1386, &ZI1387, &ZI1388, &ZI1389);
	ZR918 (ZI575, &ZI1386, &ZI1387, &ZI1388, &ZI1389, &ZI879, &ZI880, &ZI881, &ZI912);
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
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZI910) & (ZI912) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI690) = ( (*ZI910) | (ZI912) ) ;
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
	    ZI690 = *ZI910;
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
    *ZO690 = ZI690;
}

void
ZR772(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI671;
	EXP ZI494;
	EXP ZI457;
	EXP ZI559;

	switch (CURRENT_TERMINAL) {
	  case 151:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZI671) = unreached_code ;
    if ( (ZI671) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	}
	{

    (ZI494) = begin_try_stmt ( 0 ) ;
	}
	ZR679 (&ZI457);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI559) = cont_try_stmt ( (ZI494), (ZI457) ) ;
	}
	ZR771 (ZI559);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI671) ; 
	}
	{

    (ZI432) = end_try_stmt ( (ZI559), 0 ) ;
	}
	{

    unreached_fall = 1 ;
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
ZR1073(TYPE ZI415, DECL_SPEC ZI690, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI715;
	TOKEN ZI498;
	TYPE ZI876;

	ZR1111 (&ZI715);
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

    (ZI498) = template_params ( (ZI715) ) ;
    RESCAN_LEXER ;
	}
	{

    (ZI876) = make_template_type ( (ZI498), (ZI415) ) ;
	}
	ZR1034 (ZI876, ZI690, &ZI432);
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
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR960(TYPE *ZO415, IDENTIFIER *ZO420)
{
    TYPE ZI415;
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1373;
	TYPE ZI1374;

	{

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR943 (&ZI1373);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI1374) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1373) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR1162 (ZI1374, ZI1373, &ZI415, &ZI420);
	if ((CURRENT_TERMINAL) == 355) {
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
	    ZR1372 (&ZI415, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1371;
	    int ZI944;
	    TYPE ZI1377;
	    IDENTIFIER ZI1378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1371) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI944) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1371) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR945 (ZI944, &ZI1377);
	    if ((CURRENT_TERMINAL) == 355) {
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
    (ZI1378) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1378) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1162 (ZI1377, ZI1378, &ZI415, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI432;
	    TYPE ZI1375;
	    IDENTIFIER ZI1376;

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
	    ZR954 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI432) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1375) ) ;
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
    (ZI1376) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1376) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1162 (ZI1375, ZI1376, &ZI415, &ZI420);
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

	    ZR927 (&ZI498);
	    ZR960 (&ZI481, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI415) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI420) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI420) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
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
    *ZO420 = ZI420;
}

void
ZR1430(int *ZI451, int *ZI555, int *ZI556, EXP *ZO559)
{
    EXP ZI559;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI415;
	int ZI560;
	EXP ZI494;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR549 (&ZI415, &ZI560);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI494) = NULL_exp ;
	}
	{

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (*ZI451) ) ;
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
      case 156: case 170: case 185: case 206: case 210:
      case 286: case 298: case 299: case 324: case 330:
      case 346:
	{
	    EXP ZI1426;
	    EXP ZI1279;
	    EXP ZI494;
	    int ZI558;
	    int ZI560;
	    TYPE ZI415;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR492 (&ZI1426);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1279) = make_paren_exp ( (ZI1426) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR1241 (ZI1279, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI558) = no_side_effects - (*ZI555) ;
	    }
	    {

    (ZI560) = no_type_defns - (*ZI556) ;
	    }
	    {

    (ZI415) = typeof_exp ( &(ZI494), (ZI558), (*ZI451) ) ;
	    }
	    {

    (ZI559) = make_sizeof_exp ( (ZI415), (ZI494), (ZI560), (*ZI451) ) ;
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
    *ZO559 = ZI559;
}

void
ZR1431(int *ZI457, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 140:
	{
	    int ZI458;
	    SID_LIST_EXP ZI498;
	    TYPE ZI415;
	    int ZI552;
	    int ZI460;
	    EXP ZI575;
	    EXP ZI456;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {

    (ZI458) = have_type_declaration ;
    have_type_declaration = TYPE_DECL_NONE ;
	    }
	    ZR572 (&ZI498, &ZI415, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
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

    (ZI575) = begin_new_try () ;
	    }
	    ZR570 (ZI415, &ZI456);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = end_new_try ( (ZI575), (ZI456) ) ;
	    }
	    {

    (ZI432) = make_new_exp ( (ZI415), (ZI552) + (ZI460), (*ZI457), (ZI498), (ZI494) ) ;
	    }
	}
	break;
      case 131:
	{
	    int ZI451;
	    EXP ZI494;

	    ZR584 (&ZI451);
	    ZR582 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_delete_exp ( (ZI451), (*ZI457), (ZI494) ) ;
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
ZR962(TYPE ZI498, TYPE *ZO415, IDENTIFIER *ZO420)
{
    TYPE ZI415;
    IDENTIFIER ZI420;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1373;
	TYPE ZI1374;
	TYPE ZI481;

	{

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR943 (&ZI1373);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI1374) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1373) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR1162 (ZI1374, ZI1373, &ZI481, &ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI481;

	    ADVANCE_LEXER;
	    ZR1372 (&ZI481, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1371;
	    int ZI944;
	    TYPE ZI1377;
	    IDENTIFIER ZI1378;
	    TYPE ZI481;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1371) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI944) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1371) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR945 (ZI944, &ZI1377);
	    if ((CURRENT_TERMINAL) == 355) {
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
    (ZI1378) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1378) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1162 (ZI1377, ZI1378, &ZI481, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI432;
	    TYPE ZI1375;
	    IDENTIFIER ZI1376;
	    TYPE ZI481;

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
	    ZR954 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI432) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1375) ) ;
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
    (ZI1376) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1376) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR1162 (ZI1375, ZI1376, &ZI481, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	    }
	}
	break;
      case 10: case 11: case 33: case 78:
	{
	    TYPE ZI1379;
	    TYPE ZI1380;
	    TYPE ZI481;

	    ZR927 (&ZI1379);
	    ZR960 (&ZI1380, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI481) = ( IS_NULL_type ( (ZI1380) ) ? (ZI1379) : inject_pre_type ( (ZI1380), (ZI1379), 0 ) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI481;

	    {

    (ZI481) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI420) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI420) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 1 ) ) ;
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
    *ZO420 = ZI420;
}

void
ZR1057(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI494;
	SID_LIST_EXP ZI498;

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

    ZI494 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    ZI494 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	ZR500 (&ZI498);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = make_asm ( (ZI494), (ZI498) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR419 ();
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
ZR1432(int *ZO451)
{
    int ZI451;

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
	    ZR1433 (&ZI451);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZI451) = lex_delete ; 
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
    *ZO451 = ZI451;
}

void
ZR1178(TYPE ZI1172, IDENTIFIER ZI1173, int ZI1174, TYPE *ZO1175, IDENTIFIER *ZO1176, int *ZO1177)
{
    TYPE ZI1175;
    IDENTIFIER ZI1176;
    int ZI1177;

  ZL2_1178:;
    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    IDENTIFIER ZI420;
	    QUALIFIER ZI456;
	    int ZI494;
	    TYPE ZI481;
	    int ZI559;
	    TYPE ZI415;

	    ZI420 = ZI1173;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI494) = crt_templ_qualifier ;
	    }
	    ZR947 (ZI420, &ZI481, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZI1174) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1172) ) ? (ZI481) : inject_pre_type ( (ZI1172), (ZI481), 0 ) ) ;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI494) ;
	    }
	    ZI1172 = ZI415;
	    ZI1173 = ZI420;
	    ZI1174 = ZI559;
	    goto ZL2_1178;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1175 = ZI1172;
	    ZI1176 = ZI1173;
	    ZI1177 = ZI1174;
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
    *ZO1175 = ZI1175;
    *ZO1176 = ZI1176;
    *ZO1177 = ZI1177;
}

void
ZR570(TYPE ZI415, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    SID_LIST_EXP ZI498;

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

    (ZI432) = make_new_init ( (ZI415), (ZI498), 1 ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI432) = make_new_init ( (ZI415), NULL_list ( EXP ), 0 ) ;
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
ZR633(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI1261;

	ZR631 (&ZI1261);
	ZR1263 (&ZI1261, &ZI432);
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
ZR945(int ZI944, TYPE *ZO415)
{
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI946;
	CV_SPEC ZI784;
	SID_LIST_TYPE ZI723;

	ZR942 (&ZI946);
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
	ZR789 (&ZI784);
	ZR940 (&ZI723);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    CV_SPEC cv = func_linkage ( (ZI784) ) ;
    if ( (ZI944) ) (ZI946) |= FUNC_WEAK ;
    (ZI415) = make_func_type ( NULL_type, (ZI946), cv, (ZI723) ) ;
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
ZR1433(int *ZO451)
{
    int ZI451;

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
 (ZI451) = lex_delete_Harray ; 
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
      case 286: case 298: case 299: case 324: case 330:
      case 346:
	{
	    EXP ZI432;

	    ZR492 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Array size in 'delete []' */
    old_delete_array ( (ZI432) ) ;
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
 (ZI451) = lex_delete_Harray ; 
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
    *ZO451 = ZI451;
}

void
ZR1434(IDENTIFIER *ZI420, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    NAMESPACE ZI1048;
	    IDENTIFIER ZI1049;
	    IDENTIFIER ZI1050;
	    NAMESPACE ZI426;

	    ADVANCE_LEXER;
	    ZR429 (&ZI1048);
	    ZR509 (&ZI1049);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1050) = check_id ( (ZI1048), (ZI1049), 0 ) ;
    last_namespace = (ZI1048) ;
	    }
	    {

    (ZI426) = find_nspace_id ( (ZI1050) ) ;
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
	    DECL_SPEC ZI690;
	    TYPE ZI415;

	    {

    begin_namespace ( (*ZI420), 0 ) ;
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
ZR943(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1347 (&ZI420);
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
	    ZR1346 (&ZI426, &ZI420);
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
	    ZR1345 (&ZI426, &ZI420);
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
	    IDENTIFIER ZI461;

	    ZR473 (&ZI461);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = constr_name ( last_namespace, (ZI461) ) ;
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

/* END OF FILE */
