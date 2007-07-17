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
ZR839(TYPE ZI415, DECL_SPEC ZI690)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
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
	    goto ZL2;
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
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 134: case 147:
	{
	    ZR1090 (ZI415, ZI690);
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
	    }
	}
	break;
      case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI690) ) ;
	    }
	    ZR1053 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
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
ZR1328(int *ZO845)
{
    int ZI845;

    switch (CURRENT_TERMINAL) {
      case 155:
	{
	    ADVANCE_LEXER;
	    {
 (ZI845) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI845) = 0 ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *ZO845 = ZI845;
}

void
ZR1201(EXP ZI1199, EXP *ZO1200)
{
    EXP ZI1200;

  ZL2_1201:;
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
	    ZR625 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_or_exp ( (ZI1199), (ZI457) ) ;
	    }
	    ZI1199 = ZI432;
	    goto ZL2_1201;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1200 = ZI1199;
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
    *ZO1200 = ZI1200;
}

void
ZR738(EXP *ZO432)
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
      case 286: case 298: case 299: case 324: case 330:
      case 346:
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
ZR1329(DECL_SPEC *ZO494)
{
    DECL_SPEC ZI494;

    switch (CURRENT_TERMINAL) {
      case 142: case 143: case 144:
	{
	    ZR828 (&ZI494);
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
	CV_SPEC ZI784;
	TYPE ZI575;
	TYPE ZI481;

	{

    (ZI555) = no_type_defns ;
	}
	ZR874 (&ZI512, &ZI498, &ZI784);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI575) = complete_pre_type ( (ZI512), (ZI498), (ZI784), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR992 (&ZI481);
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
ZR623(EXP *ZO1208)
{
    EXP ZI1208;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR621 (&ZI432);
	ZR1209 (ZI432, &ZI1208);
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
    *ZO1208 = ZI1208;
}

void
ZR1076(BASE_TYPE *ZI512, DECL_SPEC *ZI1074, TYPE *ZI1075, ACCESS_LIST *ZI671, int *ZI559, IDENTIFIER *ZI460)
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

    free_access ( &(*ZI671) ) ;
	}
	{

    (ZI457) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (*ZI460) ) ;
	}
	ZR1025 (&ZI432);
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
	ZR1003 (*ZI460, &ZI498);
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
	ZR1077 (ZI512, ZI1074, ZI1075, ZI671);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    free_access ( &(*ZI671) ) ;
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
	    ZR999 (*ZI460, &ZI432);
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
	    ZR1077 (ZI512, ZI1074, ZI1075, ZI671);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI671) ) ;
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
	    ZR1077 (ZI512, ZI1074, ZI1075, ZI671);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI671) ) ;
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
ZR1077(BASE_TYPE *ZI512, DECL_SPEC *ZI1074, TYPE *ZI1075, ACCESS_LIST *ZI671)
{
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1010 (*ZI1074, *ZI512, *ZI1075, *ZI671);
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
ZR688(TYPE ZI415, DECL_SPEC ZI690, EXP *ZO432)
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
	    {

    (ZI432) = NULL_exp ;
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
ZR1205(EXP ZI1203, EXP *ZO1204)
{
    EXP ZI1204;

  ZL2_1205:;
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
	    ZR623 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_xor_exp ( (ZI1203), (ZI457) ) ;
	    }
	    ZI1203 = ZI432;
	    goto ZL2_1205;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1204 = ZI1203;
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
    *ZO1204 = ZI1204;
}

void
ZR636(EXP *ZO432)
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
	      case 286: case 299: case 330:
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
parse_stmt(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI690;
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
 (ZI690) = dspec_none ; 
	}
	{

    (ZI415) = NULL_type ;
	}
	ZR688 (ZI415, ZI690, &ZI494);
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_alignof ; 
	    }
	    ZR594 (ZI451, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR1475 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1280;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1280 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1241 (ZI1280, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    TYPE ZI1266;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI784;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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

    (ZI1283) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1241 (ZI1283, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1461;
	    int ZI552;
	    EXP ZI1272;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1461, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_const_cast_exp ( (ZI415), (ZI1461), (ZI552) ) ;
	    }
	    ZR1241 (ZI1272, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1284;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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

    (ZI1284) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1241 (ZI1284, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1454);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_cast_exp ( type_void, (ZI1454), 0 ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1464;
	    int ZI552;
	    EXP ZI1275;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1464, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1275) = make_dynamic_cast_exp ( (ZI415), (ZI1464), (ZI552) ) ;
	    }
	    ZR1241 (ZI1275, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1278;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    {

    (ZI1278) = make_ellipsis_exp () ;
	    }
	    ZR1241 (ZI1278, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR1474 (&ZI426, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1465;

	    {

    ZI1465 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1470 (&ZI1465, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 346:
	{
	    ADVANCE_LEXER;
	    ZR1440 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI1456;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_prefix_exp ( lex_minus_Hminus, (ZI1456) ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
      case 8:
	{
	    NAMESPACE ZI426;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1473 (&ZI426, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR1287 (&ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1455;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_prefix_exp ( lex_plus_Hplus, (ZI1455) ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1462;
	    int ZI552;
	    EXP ZI1273;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1462, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1273) = make_reinterp_cast_exp ( (ZI415), (ZI1462), (ZI552) ) ;
	    }
	    ZR1241 (ZI1273, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_sizeof ; 
	    }
	    ZR594 (ZI451, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1457;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_indir_exp ( (ZI1457) ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
      case 146:
	{
	    TYPE ZI415;
	    EXP ZI1463;
	    int ZI552;
	    EXP ZI1274;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1463, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1274) = make_static_cast_exp ( (ZI415), (ZI1463), (ZI552) ) ;
	    }
	    ZR1241 (ZI1274, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1284;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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

    (ZI1284) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1241 (ZI1284, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    TYPE ZI1266;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI784;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1282;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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

    (ZI1282) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1241 (ZI1282, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1277;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    {

    (ZI1277) = make_this_exp () ;
	    }
	    ZR1241 (ZI1277, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    IDENTIFIER ZI1467;

	    {

    ZI1467 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1468 (&ZI1467, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 152:
	{
	    int ZI451;
	    EXP ZI1271;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_typeid ; 
	    }
	    ZR554 (ZI451, &ZI1271);
	    ZR1241 (ZI1271, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1270;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_vtable ; 
	    }
	    ZR554 (ZI451, &ZI1270);
	    ZR1241 (ZI1270, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1458;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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
	    ZR582 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_ref_exp ( (ZI1458), 0 ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    TYPE ZI1266;
	    CV_SPEC ZI784;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1281;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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

    (ZI1281) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1241 (ZI1281, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR679 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 289: case 323:
	{
	    ZR777 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 96: case 100: case 223:
	{
	    ZR663 ();
	    ZR1441 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI1435;
	    EXP ZI494;
	    int ZI671;

	    ZR644 (&ZI1435);
	    ZR1437 (&ZI1435, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR739 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    ZR753 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
	{
	    EXP ZI1276;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ZR438 (&ZI1276);
	    ZR1241 (ZI1276, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1459;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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
	    ZR582 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_not_exp ( (ZI1459) ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1284;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

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

    (ZI1284) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1241 (ZI1284, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR714 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 149:
	{
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ZR636 (&ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR772 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI457;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    {
 (ZI457) = 0 ; 
	    }
	    ZR1431 (&ZI457, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    EXP ZI1460;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR597 ();
	    ZR582 (&ZI1460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1453) = make_uminus_exp ( (ZI451), (ZI1460) ) ;
	    }
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
ZR1088(DECL_SPEC ZI690, TYPE ZI498, BASE_TYPE ZI481, ACCESS_LIST ZI671, int ZI721)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1088:;
    {
	IDENTIFIER ZI460;

	ZR1085 (ZI690, ZI498, ZI481, ZI671, ZI721, &ZI460);
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
		    ZI721 = ZI552;
		    goto ZL2_1088;
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
ZR954(EXP *ZO432)
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
      case 170: case 185: case 206: case 210: case 286:
      case 299: case 330:
	{
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
	CV_SPEC ZI784;
	TYPE ZI481;

	{

    (ZI555) = no_type_defns ;
	}
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
ZR644(EXP *ZO432)
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
ZR1209(EXP ZI1207, EXP *ZO1208)
{
    EXP ZI1208;

  ZL2_1209:;
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
	    ZR621 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_and_exp ( (ZI1207), (ZI457) ) ;
	    }
	    ZI1207 = ZI432;
	    goto ZL2_1209;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1208 = ZI1207;
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
    *ZO1208 = ZI1208;
}

void
ZR687(TYPE ZI415, DECL_SPEC ZI690)
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
    SAVE_LEXER (355);
    return;
  ZL0:;
}

void
ZR1029(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI690;
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
 (ZI690) = dspec_none ; 
	}
	{

    (ZI415) = NULL_type ;
	}
	ZR1028 (ZI415, ZI690);
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
ZR452(int *ZO451)
{
    int ZI451;

    switch (CURRENT_TERMINAL) {
      case 131:
	{
	    ADVANCE_LEXER;
	    ZR1322 (&ZI451);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 140:
	{
	    ADVANCE_LEXER;
	    ZR1321 (&ZI451);
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
	    ZR1320 (&ZI451);
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
ZR1340(TYPE *ZI415, BASE_TYPE *ZI512, TYPE *ZI876, CV_SPEC *ZI877, DECL_SPEC *ZI912)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI912), (*ZI415), (*ZI512), (*ZI876), (*ZI877), last_lex_token, 1 ) ;
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
	    TYPE ZI880;
	    DECL_SPEC ZI1074;
	    TYPE ZI1075;
	    ACCESS_LIST ZI671;
	    int ZI721;
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
 (ZI721) = 1 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1085 (ZI1074, ZI1075, *ZI512, ZI671, ZI721, &ZI460);
	    ZR1093 (ZI512, &ZI1074, &ZI1075, &ZI671, &ZI460);
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
ZR1213(EXP ZI1211, EXP *ZO1212)
{
    EXP ZI1212;

  ZL2_1213:;
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
	    ZR618 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_mult_exp ( (ZI451), (ZI1211), (ZI457) ) ;
	    }
	    ZI1211 = ZI432;
	    goto ZL2_1213;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1212 = ZI1211;
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
    *ZO1212 = ZI1212;
}

void
ZR1468(IDENTIFIER *ZI1467, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI420;
	    TYPE ZI1266;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI784;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1282;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    {

    (ZI420) = (*ZI1467) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
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
	    ZR1241 (ZI1282, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI494) = begin_label_stmt ( (*ZI1467), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR662 (&ZI457);
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
ZR1341(void)
{
    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ZR836 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 154:
	{
	    ZR1053 ();
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
      case 170: case 185: case 206: case 210: case 286:
      case 299: case 330:
	{
	    EXP ZI1264;

	    ZR631 (&ZI1264);
	    ZR1265 (&ZI1264, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 149:
	{
	    ZR636 (&ZI432);
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
ZR1596(EXP *ZI1595, EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 347:
	{
	    SID_LIST_EXP ZI481;
	    SID_LIST_EXP ZI498;
	    EXP ZI494;
	    int ZI671;

	    ADVANCE_LEXER;
	    ZR649 (&ZI481);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1595), (ZI481), (ZI498) ) ;
	    }
	    {

    (ZI494) = make_comma_exp ( (ZI498) ) ;
	    }
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
	    int ZI671;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 347:
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

    (ZI432) = make_exp_stmt ( (*ZI1595) ) ;
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
    *ZO432 = ZI432;
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
      case 286: case 299: case 330:
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
      case 33: case 34: case 35: case 36: case 42:
      case 44: case 45: case 46: case 48: case 49:
      case 50: case 53: case 54: case 55: case 56:
      case 57: case 58: case 59: case 60: case 61:
      case 63: case 65: case 66: case 67: case 68:
      case 69: case 70: case 71: case 72: case 73:
      case 74: case 75: case 76: case 77: case 78:
      case 79: case 80: case 81: case 82: case 84:
      case 86: case 87:
	{
	    IDENTIFIER ZI420;
	    EXP ZI1284;
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
	    EXP ZI1442;
	    EXP ZI1264;
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    {

    (ZI420) = (*ZI1469) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1284) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1241 (ZI1284, &ZI1453);
	    ZR1237 (ZI1453, &ZI1452);
	    ZR1233 (ZI1452, &ZI1451);
	    ZR1229 (ZI1451, &ZI1450);
	    ZR1225 (ZI1450, &ZI1449);
	    ZR1221 (ZI1449, &ZI1448);
	    ZR1217 (ZI1448, &ZI1447);
	    ZR1213 (ZI1447, &ZI1446);
	    ZR1209 (ZI1446, &ZI1445);
	    ZR1205 (ZI1445, &ZI1444);
	    ZR1201 (ZI1444, &ZI1443);
	    ZR1197 (ZI1443, &ZI1442);
	    ZR1193 (ZI1442, &ZI1264);
	    ZR1265 (&ZI1264, &ZI1288);
	    ZR1290 (&ZI1288, &ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	    ZR662 (&ZI457);
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

/* END OF FILE */
