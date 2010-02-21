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
ZR1328(int *ZO415)
{
    int ZI415;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4: case 7:
      case 8: case 9: case 83: case 142: case 143:
      case 144: case 155:
	{
	    ZR847 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI415) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI415) = 0 ; 
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
    *ZO415 = ZI415;
}

void
ZR739(EXP *ZO432)
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
	    EXP ZI494;
	    EXP ZI457;

	    ZR492 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI457) = make_exp_stmt ( (ZI494) ) ;
	    }
	    {

    (ZI432) = bind_temporary ( (ZI457) ) ;
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
ZR1329(int *ZO846)
{
    int ZI846;

    switch (CURRENT_TERMINAL) {
      case 155:
	{
	    ADVANCE_LEXER;
	    {
 (ZI846) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI846) = 0 ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *ZO846 = ZI846;
}

void
ZR1202(EXP ZI1200, EXP *ZO1201)
{
    EXP ZI1201;

  ZL2_1202:;
    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    EXP ZI457;
	    EXP ZI432;

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
	    ZR626 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_or_exp ( (ZI1200), (ZI457) ) ;
	    }
	    ZI1200 = ZI432;
	    goto ZL2_1202;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1201 = ZI1200;
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
    *ZO1201 = ZI1201;
}

void
ZR569(TYPE *ZO415, int *ZO552)
{
    TYPE ZI415;
    int ZI552;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI555;
	BASE_TYPE ZI512;
	TYPE ZI498;
	CV_SPEC ZI785;
	TYPE ZI575;
	TYPE ZI481;

	{

    (ZI555) = no_type_defns ;
	}
	ZR875 (&ZI512, &ZI498, &ZI785);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI575) = complete_pre_type ( (ZI512), (ZI498), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR993 (&ZI481);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI575) : inject_pre_type ( (ZI481), (ZI575), 1 ) ) ;
	}
	{

    (ZI552) = no_type_defns - (ZI555) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
    *ZO552 = ZI552;
}

void
ZR624(EXP *ZO1209)
{
    EXP ZI1209;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR622 (&ZI432);
	ZR1210 (ZI432, &ZI1209);
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
    *ZO1209 = ZI1209;
}

void
ZR1330(DECL_SPEC *ZO494)
{
    DECL_SPEC ZI494;

    switch (CURRENT_TERMINAL) {
      case 142: case 143: case 144:
	{
	    ZR829 (&ZI494);
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
    *ZO494 = ZI494;
}

void
parse_exp(EXP *ZO432)
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
ZR1077(BASE_TYPE *ZI512, DECL_SPEC *ZI1075, TYPE *ZI1076, ACCESS_LIST *ZI672, int *ZI559, IDENTIFIER *ZI460)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI457;
	EXP ZI432;

	{

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    if ( (*ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	}
	{

    free_access ( &(*ZI672) ) ;
	}
	{

    (ZI457) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (*ZI460) ) ;
	}
	ZR1026 (&ZI432);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IGNORE end_function ( (*ZI460), (ZI432) ) ;
    in_class_defn = (ZI457) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
	}
	{

    end_declarator ( (*ZI460), 1 ) ;
	}
	{

    RESCAN_LEXER ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    {
	SID_LIST_EXP ZI498;
	EXP ZI432;

	{

    (ZI0) = (*ZI559) ;
	}
	if (!ZI0)
	    goto ZL3;
	{

    if ( crt_lex_token == lex_open_Hinit ) {
	crt_lex_token = lex_open_Hround ;
    } else {
	RESCAN_LEXER ;
    }
	}
	ZR1004 (*ZI460, &ZI498);
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
	{

    int def = init_object ( (*ZI460), (ZI432) ) ;
    if ( do_dump ) dump_declare ( (*ZI460), &decl_loc, def ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZI460) ) ;
    }
	}
	{

    end_declarator ( (*ZI460), 1 ) ;
	}
	ZR1078 (ZI512, ZI1075, ZI1076, ZI672);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    free_access ( &(*ZI672) ) ;
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
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR1000 (*ZI460, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = init_object ( (*ZI460), (ZI432) ) ;
    if ( do_dump ) dump_declare ( (*ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZI460) ) ;
    }
	    }
	    {

    end_declarator ( (*ZI460), 1 ) ;
	    }
	    ZR1078 (ZI512, ZI1075, ZI1076, ZI672);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI672) ) ;
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
      case 42: case 77:
	{
	    EXP ZI432;

	    {

    (ZI432) = NULL_exp ;
	    }
	    {

    int def = init_object ( (*ZI460), (ZI432) ) ;
    if ( do_dump ) dump_declare ( (*ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZI460) ) ;
    }
	    }
	    {

    end_declarator ( (*ZI460), 1 ) ;
	    }
	    ZR1078 (ZI512, ZI1075, ZI1076, ZI672);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI672) ) ;
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
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
}

void
ZR689(TYPE ZI415, DECL_SPEC ZI691, EXP *ZO432)
{
    EXP ZI432;

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
	    ZR1064 (ZI415, ZI691, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 134: case 147:
	{
	    ZR1074 (ZI415, ZI691, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
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
	    {

    (ZI432) = NULL_exp ;
	    }
	}
	break;
      case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI691) ) ;
	    }
	    ZR1079 (&ZI432);
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
ZR1078(BASE_TYPE *ZI512, DECL_SPEC *ZI1075, TYPE *ZI1076, ACCESS_LIST *ZI672)
{
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1011 (*ZI1075, *ZI512, *ZI1076, *ZI672);
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
ZR637(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI494;

	switch (CURRENT_TERMINAL) {
	  case 149:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    {
		TYPE ZI415;
		int ZI552;

		{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL3;
		ZR549 (&ZI415, &ZI552);
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI494) = make_throw_arg ( (ZI415), (ZI552) ) ;
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
	      case 255: case 286: case 299: case 330:
		{
		    ZR497 (&ZI494);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI494) = NULL_exp ;
		    }
		}
		break;
	    }
	  ZL2:;
	}
	{

    (ZI432) = make_throw_exp ( (ZI494), 1 ) ;
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
ZR1206(EXP ZI1204, EXP *ZO1205)
{
    EXP ZI1205;

  ZL2_1206:;
    switch (CURRENT_TERMINAL) {
      case 80:
	{
	    EXP ZI457;
	    EXP ZI432;

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
	    ZR624 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_xor_exp ( (ZI1204), (ZI457) ) ;
	    }
	    ZI1204 = ZI432;
	    goto ZL2_1206;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1205 = ZI1204;
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
    *ZO1205 = ZI1205;
}

void
parse_stmt(EXP *ZO432)
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
	ZR689 (ZI415, ZI691, &ZI494);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = (ZI494) ;
    in_declaration-- ;
	}
	{

    unreached_fall = 1 ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI451;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_alignof ; 
	    }
	    ZR594 (ZI451, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1477 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1281;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1242 (ZI1281, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 24:
	{
	    EXP ZI494;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI494 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

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
	    ZR1242 (ZI1284, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 130:
	{
	    TYPE ZI415;
	    EXP ZI1463;
	    int ZI552;
	    EXP ZI1273;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1463, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZI415), (ZI1463), (ZI552) ) ;
	    }
	    ZR1242 (ZI1273, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 5:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI1285;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 206:
	{
	    EXP ZI1456;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_cast_exp ( type_void, (ZI1456), 0 ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 132:
	{
	    TYPE ZI415;
	    EXP ZI1466;
	    int ZI552;
	    EXP ZI1276;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1466, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZI415), (ZI1466), (ZI552) ) ;
	    }
	    ZR1242 (ZI1276, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 210:
	{
	    EXP ZI1279;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    {

    (ZI1279) = make_ellipsis_exp () ;
	    }
	    ZR1242 (ZI1279, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 9:
	{
	    NAMESPACE ZI426;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1476 (&ZI426, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1467;

	    {

    ZI1467 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI1467, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 346:
	{
	    ADVANCE_LEXER;
	    ZR1441 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 255:
	{
	    EXP ZI1455;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_lit_exp ( (ZI1455) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 61:
	{
	    EXP ZI1458;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_prefix_exp ( lex_minus_Hminus, (ZI1458) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 3:
	{
	    IDENTIFIER ZI1471;

	    {

    ZI1471 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI1471, &ZI432);
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
	    ZR1475 (&ZI426, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR1288 (&ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 71:
	{
	    EXP ZI1457;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_prefix_exp ( lex_plus_Hplus, (ZI1457) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 145:
	{
	    TYPE ZI415;
	    EXP ZI1464;
	    int ZI552;
	    EXP ZI1274;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1464, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZI415), (ZI1464), (ZI552) ) ;
	    }
	    ZR1242 (ZI1274, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
	    ADVANCE_LEXER;
	    {

    (ZI432) = NULL_exp ;
	    }
	}
	break;
      case 116:
	{
	    int ZI451;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_sizeof ; 
	    }
	    ZR594 (ZI451, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 78:
	{
	    EXP ZI1459;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_indir_exp ( (ZI1459) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 4:
	{
	    IDENTIFIER ZI1473;

	    {

    ZI1473 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1474 (&ZI1473, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 146:
	{
	    TYPE ZI415;
	    EXP ZI1465;
	    int ZI552;
	    EXP ZI1275;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1465, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1275) = make_static_cast_exp ( (ZI415), (ZI1465), (ZI552) ) ;
	    }
	    ZR1242 (ZI1275, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 6:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI1285;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

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
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1283;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = (ZI461) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
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
	    ZR1242 (ZI1283, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 148:
	{
	    EXP ZI1278;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    {

    (ZI1278) = make_this_exp () ;
	    }
	    ZR1242 (ZI1278, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 2:
	{
	    IDENTIFIER ZI1469;

	    {

    ZI1469 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1470 (&ZI1469, &ZI432);
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
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_typeid ; 
	    }
	    ZR554 (ZI451, &ZI1272);
	    ZR1242 (ZI1272, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 330:
	{
	    int ZI451;
	    EXP ZI1271;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_vtable ; 
	    }
	    ZR554 (ZI451, &ZI1271);
	    ZR1242 (ZI1271, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 33:
	{
	    EXP ZI1460;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

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
	    ZR582 (&ZI1460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

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
	    ZR1242 (ZI1282, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 64:
	{
	    ZR680 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 289: case 323:
	{
	    ZR778 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 96: case 100: case 223:
	{
	    ZR664 ();
	    ZR1442 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI1436;
	    EXP ZI494;
	    int ZI672;

	    ZR645 (&ZI1436);
	    ZR1438 (&ZI1436, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 101: case 107: case 125:
	{
	    ZR740 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    ZR754 (&ZI432);
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
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ZR438 (&ZI1277);
	    ZR1242 (ZI1277, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 62:
	{
	    EXP ZI1461;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

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
	    ZR582 (&ZI1461);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 141:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI1285;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

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
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 26: case 109: case 119:
	{
	    ZR715 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 149:
	{
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    ZR637 (&ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 151:
	{
	    ZR773 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI457;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    {
 (ZI457) = 0 ; 
	    }
	    ZR1432 (&ZI457, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 43: case 59: case 69: case 85:
	{
	    int ZI451;
	    EXP ZI1462;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR597 ();
	    ZR582 (&ZI1462);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_uminus_exp ( (ZI451), (ZI1462) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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

    (ZI432) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1089(DECL_SPEC ZI691, TYPE ZI498, BASE_TYPE ZI481, ACCESS_LIST ZI672, int ZI722)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1089:;
    {
	IDENTIFIER ZI460;

	ZR1086 (ZI691, ZI498, ZI481, ZI672, ZI722, &ZI460);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    end_declarator ( (ZI460), 1 ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    int ZI552;

		    ADVANCE_LEXER;
		    {
 (ZI552) = 0 ; 
		    }
		    {

    crt_templ_qualifier = 0 ;
		    }
		    ZI722 = ZI552;
		    goto ZL2_1089;
		}
		/*UNREACHED*/
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
ZR549(TYPE *ZO415, int *ZO552)
{
    TYPE ZI415;
    int ZI552;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI555;
	BASE_TYPE ZI512;
	TYPE ZI498;
	CV_SPEC ZI785;
	TYPE ZI481;

	{

    (ZI555) = no_type_defns ;
	}
	ZR875 (&ZI512, &ZI498, &ZI785);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI481) = complete_pre_type ( (ZI512), (ZI498), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR957 (ZI481, &ZI415);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI552) = no_type_defns - (ZI555) ;
	}
	{

    object_type ( (ZI415), null_tag ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
    *ZO552 = ZI552;
}

void
ZR645(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI494;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
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
	      case 39:
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
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
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
	      case 39:
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
ZR955(EXP *ZO432)
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
      case 146: case 148: case 150: case 152: case 156:
      case 170: case 185: case 206: case 210: case 255:
      case 286: case 299: case 330:
	{
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
ZR688(TYPE ZI415, DECL_SPEC ZI691)
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
    SAVE_LEXER (355);
    return;
  ZL0:;
}

void
ZR1030(void)
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
	ZR1029 (ZI415, ZI691);
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
ZR1210(EXP ZI1208, EXP *ZO1209)
{
    EXP ZI1209;

  ZL2_1210:;
    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    EXP ZI457;
	    EXP ZI432;

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
	    ZR622 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_and_exp ( (ZI1208), (ZI457) ) ;
	    }
	    ZI1208 = ZI432;
	    goto ZL2_1210;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1209 = ZI1208;
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
    *ZO1209 = ZI1209;
}

void
ZR452(int *ZO451)
{
    int ZI451;

    switch (CURRENT_TERMINAL) {
      case 131:
	{
	    ADVANCE_LEXER;
	    ZR1323 (&ZI451);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 140:
	{
	    ADVANCE_LEXER;
	    ZR1322 (&ZI451);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR414 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI451) = lex_func_Hop ; 
	    }
	}
	break;
      case 72:
	{
	    ADVANCE_LEXER;
	    ZR417 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI451) = lex_cond_Hop ; 
	    }
	    {

    /* Illegal overloaded operator */
    report ( crt_loc, ERR_over_oper_bad ( (ZI451) ) ) ;
	    }
	}
	break;
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
	    ZR416 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI451) = lex_array_Hop ; 
	    }
	}
	break;
      case 33: case 34: case 35: case 36: case 41:
      case 42: case 43: case 44: case 45: case 46:
      case 48: case 49: case 50: case 53: case 54:
      case 55: case 56: case 57: case 58: case 59:
      case 60: case 61: case 62: case 63: case 67:
      case 68: case 69: case 70: case 71: case 73:
      case 74: case 75: case 76: case 78: case 79:
      case 80: case 81: case 82: case 83: case 84:
      case 85: case 86: case 87: case 116: case 152:
      case 170: case 330:
	{
	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR1321 (&ZI451);
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
    *ZO451 = ZI451;
}

void
ZR417(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 41:
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
 (ZI415) = lex_colon ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI415) ) report ( crt_loc, ERR_lex_expect ( (ZI415) ) ) ;
	}
    }
}

void
ZR499(SID_LIST_EXP *ZO498)
{
    SID_LIST_EXP ZI498;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;
	SID_LIST_EXP ZI481;

	ZR497 (&ZI432);
	ZR500 (&ZI481);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
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
ZR1341(TYPE *ZI415, BASE_TYPE *ZI512, TYPE *ZI877, CV_SPEC *ZI878, DECL_SPEC *ZI913)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI913), (*ZI415), (*ZI512), (*ZI877), (*ZI878), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IDENTIFIER id = DEREF_id ( ctype_name ( crt_class ) ) ;
	IGNORE report_access ( id ) ;
    }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 41: case 65: case 78:
      case 83: case 141:
	{
	    TYPE ZI881;
	    DECL_SPEC ZI1075;
	    TYPE ZI1076;
	    ACCESS_LIST ZI672;
	    int ZI722;
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
 (ZI722) = 1 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1086 (ZI1075, ZI1076, *ZI512, ZI672, ZI722, &ZI460);
	    ZR1094 (ZI512, &ZI1075, &ZI1076, &ZI672, &ZI460);
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
ZR1214(EXP ZI1212, EXP *ZO1213)
{
    EXP ZI1213;

  ZL2_1214:;
    switch (CURRENT_TERMINAL) {
      case 86: case 87:
	{
	    int ZI451;
	    EXP ZI457;
	    EXP ZI432;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    {
		switch (CURRENT_TERMINAL) {
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
		  default:
		    goto ZL1;
		}
	    }
	    ZR619 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_mult_exp ( (ZI451), (ZI1212), (ZI457) ) ;
	    }
	    ZI1212 = ZI432;
	    goto ZL2_1214;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1213 = ZI1212;
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
    *ZO1213 = ZI1213;
}

void
ZR497(EXP *ZO432)
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
      case 146: case 148: case 150: case 152: case 156:
      case 170: case 185: case 206: case 210: case 255:
      case 286: case 299: case 330:
	{
	    EXP ZI1265;

	    ZR632 (&ZI1265);
	    ZR1266 (&ZI1265, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 149:
	{
	    ZR637 (&ZI432);
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
ZR1342(void)
{
    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ZR837 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 154:
	{
	    ZR1054 ();
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
ZR501(SID_LIST_EXP *ZO498)
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
	    ZR499 (&ZI498);
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
ZR1470(IDENTIFIER *ZI1469, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1283;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI494;
	    int ZI672;

	    {

    (ZI420) = (*ZI1469) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
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
	    ZR1242 (ZI1283, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI432) = make_exp_stmt ( (ZI494) ) ;
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
      case 41:
	{
	    EXP ZI494;
	    EXP ZI457;

	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI494) = begin_label_stmt ( (*ZI1469), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR663 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_label_stmt ( (ZI494), (ZI457) ) ;
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
ZR630(EXP *ZO1197)
{
    EXP ZI1197;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR628 (&ZI432);
	ZR1198 (ZI432, &ZI1197);
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
    *ZO1197 = ZI1197;
}

void
ZR754(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 95:
	{
	    int ZI672;

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

    (ZI432) = make_break_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR419 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 99:
	{
	    int ZI672;

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

    (ZI432) = make_continue_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR419 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 108:
	{
	    int ZI672;

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
	    ZR753 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR419 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 113:
	{
	    int ZI672;
	    EXP ZI494;

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
			ZR492 (&ZI494);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZI494) = NULL_exp ;
			}
		    }
		    break;
		}
	    }
	    {

    (ZI432) = make_return_stmt ( (ZI494), lex_return ) ;
	    }
	    {

    unreached_fall = 1 ;
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
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

/* END OF FILE */
