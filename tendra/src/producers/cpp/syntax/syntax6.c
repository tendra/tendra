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
ZR1233(EXP ZI1231, EXP *ZO1232)
{
    EXP ZI1232;

  ZL2_1233:;
    switch (CURRENT_TERMINAL) {
      case 44:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR602 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_mult_exp ( lex_div, (ZI1231), (ZI457) ) ;
	    }
	    ZI1231 = ZI432;
	    goto ZL2_1233;
	}
	/*UNREACHED*/
      case 73:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR602 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_rem_exp ( (ZI1231), (ZI457) ) ;
	    }
	    ZI1231 = ZI432;
	    goto ZL2_1233;
	}
	/*UNREACHED*/
      case 78:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    ZR602 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_mult_exp ( lex_star, (ZI1231), (ZI457) ) ;
	    }
	    ZI1231 = ZI432;
	    goto ZL2_1233;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1232 = ZI1231;
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
    *ZO1232 = ZI1232;
}

void
ZR900(DECL_SPEC *ZO690)
{
    DECL_SPEC ZI690;

    switch (CURRENT_TERMINAL) {
      case 133:
	{
	    ADVANCE_LEXER;
	    {
 (ZI690) = dspec_explicit ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (ZI690) = dspec_inline ; 
	    }
	}
	break;
      case 275:
	{
	    ADVANCE_LEXER;
	    {
 (ZI690) = dspec_none ; 
	    }
	}
	break;
      case 155:
	{
	    ADVANCE_LEXER;
	    {
 (ZI690) = dspec_virtual ; 
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
    *ZO690 = ZI690;
}

void
ZR662(EXP *ZO432)
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
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1237(EXP ZI1235, EXP *ZO1236)
{
    EXP ZI1236;

  ZL2_1237:;
    switch (CURRENT_TERMINAL) {
      case 82:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    {

    in_ptr_mem_selector++ ;
	    }
	    ZR582 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_member_exp ( lex_arrow_Hstar, (ZI1235), (ZI457) ) ;
    in_ptr_mem_selector-- ;
	    }
	    ZI1235 = ZI432;
	    goto ZL2_1237;
	}
	/*UNREACHED*/
      case 84:
	{
	    EXP ZI457;
	    EXP ZI432;

	    ADVANCE_LEXER;
	    {

    in_ptr_mem_selector++ ;
	    }
	    ZR582 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = make_member_exp ( lex_dot_Hstar, (ZI1235), (ZI457) ) ;
    in_ptr_mem_selector-- ;
	    }
	    ZI1235 = ZI432;
	    goto ZL2_1237;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1236 = ZI1235;
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
    *ZO1236 = ZI1236;
}

void
ZR955(TYPE *ZO1139)
{
    TYPE ZI1139;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1384 (&ZI1139);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI420;
	    int ZI944;
	    TYPE ZI415;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI944) = 1 ; 
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
      case 66:
	{
	    EXP ZI432;
	    TYPE ZI415;

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
    MAKE_type_array ( cv_none, NULL_type, n, (ZI415) ) ;
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
ZR771(EXP ZI494)
{
  ZL2_771:;
    switch (CURRENT_TERMINAL) {
      case 128:
	{
	    ZR763 (ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_771;
	    }
	}
	/*UNREACHED*/
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
ZR1366(DECL_SPEC *ZI690, TYPE *ZI498, BASE_TYPE *ZI481, ACCESS_LIST *ZI671, int *ZI721, IDENTIFIER *ZI1365, IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    QUALIFIER ZI456;
	    int ZI457;
	    EXP ZI559;
	    TYPE ZI415;

	    {

    if ( !IS_NULL_type ( (*ZI498) ) ) template_decl ( (*ZI498) ) ;
	    }
	    {

    begin_declarator ( (*ZI1365), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    ADVANCE_LEXER;
	    ZR652 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1365) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI415) = make_bitfield_type ( (*ZI498), (*ZI481), (ZI559), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( (*ZI690), (ZI415), (*ZI1365), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZI460) = id ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(*ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      default:
	{
	    TYPE ZI1355;
	    int ZI1356;
	    TYPE ZI1348;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1086;
	    EXP ZI432;

	    {

    (ZI1355) = NULL_type ;
	    }
	    {
 (ZI1356) = 0 ; 
	    }
	    {

    begin_declarator ( (*ZI1365), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1178 (ZI1355, *ZI1365, ZI1356, &ZI1348, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (*ZI498) ) ) template_decl ( (*ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1348) ) ? (*ZI498) : inject_pre_type ( (ZI1348), (*ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (*ZI690) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1086) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1086) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (*ZI721) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1086) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (*ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(*ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1084 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1086) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
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
    *ZO460 = ZI460;
}

void
ZR739(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 101:
	{
	    unsigned ZI715;
	    int ZI671;
	    EXP ZI494;
	    EXP ZI716;
	    EXP ZI457;
	    EXP ZI740;
	    EXP ZI559;

	    ADVANCE_LEXER;
	    {
 (ZI715) = crt_condition ; 
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

    (ZI494) = begin_do_stmt () ;
	    }
	    {

    (ZI716) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR682 (ZI716, &ZI457);
	    switch (CURRENT_TERMINAL) {
	      case 125:
		break;
	      case 355:
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
	    ZR492 (&ZI740);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI559) = bind_temporary ( (ZI740) ) ;
	    }
	    {
 unreached_prev = (ZI671) ; 
	    }
	    {

    (ZI432) = end_do_stmt ( (ZI494), (ZI457), (ZI559) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 crt_condition = (ZI715) ; 
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
      case 107:
	{
	    unsigned ZI715;
	    int ZI671;
	    EXP ZI721;
	    EXP ZI494;
	    EXP ZI741;
	    EXP ZI559;
	    EXP ZI742;
	    EXP ZI690;
	    EXP ZI457;
	    EXP ZI743;
	    EXP ZI744;
	    EXP ZI745;
	    EXP ZI460;

	    ADVANCE_LEXER;
	    {
 (ZI715) = crt_condition ; 
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
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI721) = begin_for_stmt () ;
	    }
	    ZR736 (&ZI494);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI741) = init_for_stmt ( (ZI721), &(ZI494) ) ;
	    }
	    ZR737 (&ZI559, &ZI742);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI690) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR738 (&ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI743) = cond_for_stmt ( (ZI741), (ZI742), (ZI457) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI744) = inject_cond ( (ZI690), (ZI494) ) ;
	    }
	    {

    (ZI745) = inject_cond ( (ZI744), (ZI559) ) ;
	    }
	    {

    mark_compound_stmt ( (ZI745) ) ;
	    }
	    ZR682 (ZI745, &ZI460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI671) ; 
	    }
	    {

    (ZI432) = end_for_stmt ( (ZI743), (ZI460) ) ;
	    }
	    {
 crt_condition = (ZI715) ; 
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
	    unsigned ZI715;
	    int ZI671;
	    EXP ZI740;
	    EXP ZI559;
	    EXP ZI494;
	    EXP ZI716;
	    EXP ZI717;
	    EXP ZI457;

	    ADVANCE_LEXER;
	    {
 (ZI715) = crt_condition ; 
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
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR713 (&ZI740);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI559) = bind_temporary ( (ZI740) ) ;
	    }
	    {

    (ZI494) = begin_while_stmt ( (ZI559) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI716) = begin_compound_stmt ( 1 ) ;
	    }
	    {

    (ZI717) = inject_cond ( (ZI716), (ZI559) ) ;
	    }
	    ZR682 (ZI717, &ZI457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI671) ; 
	    }
	    {

    (ZI432) = end_while_stmt ( (ZI494), (ZI457) ) ;
	    }
	    {
 crt_condition = (ZI715) ; 
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
ZR640(void)
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
ZR1241(EXP ZI1239, EXP *ZO1240)
{
    EXP ZI1240;

  ZL2_1241:;
    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    EXP ZI432;

	    ADVANCE_LEXER;
	    {

    (ZI432) = make_postfix_exp ( lex_minus_Hminus, (ZI1239) ) ;
	    }
	    ZI1239 = ZI432;
	    goto ZL2_1241;
	}
	/*UNREACHED*/
      case 65:
	{
	    SID_LIST_EXP ZI498;
	    EXP ZI432;

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

    (ZI432) = make_func_exp ( (ZI1239), (ZI498), 0 ) ;
	    }
	    ZI1239 = ZI432;
	    goto ZL2_1241;
	}
	/*UNREACHED*/
      case 71:
	{
	    EXP ZI432;

	    ADVANCE_LEXER;
	    {

    (ZI432) = make_postfix_exp ( lex_plus_Hplus, (ZI1239) ) ;
	    }
	    ZI1239 = ZI432;
	    goto ZL2_1241;
	}
	/*UNREACHED*/
      case 66:
	{
	    EXP ZI457;
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
	    ZR492 (&ZI457);
	    {
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
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

    (ZI432) = make_index_exp ( (ZI1239), (ZI457) ) ;
	    }
	    ZI1239 = ZI432;
	    goto ZL2_1241;
	}
	/*UNREACHED*/
      case 35:
	{
	    EXP ZI457;
	    TYPE ZI415;
	    NAMESPACE ZI426;
	    int ZI481;
	    IDENTIFIER ZI420;
	    EXP ZI432;

	    {

    (ZI457) = begin_field_exp ( lex_arrow, (ZI1239), &(ZI415), &(ZI426) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR476 (ZI426, &ZI481);
	    ZR518 (ZI426, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_field_exp ( lex_arrow, (ZI457), (ZI415), (ZI426), (ZI420), (ZI481) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI1239 = ZI432;
	    goto ZL2_1241;
	}
	/*UNREACHED*/
      case 46:
	{
	    EXP ZI457;
	    TYPE ZI415;
	    NAMESPACE ZI426;
	    int ZI481;
	    IDENTIFIER ZI420;
	    EXP ZI432;

	    {

    (ZI457) = begin_field_exp ( lex_dot, (ZI1239), &(ZI415), &(ZI426) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR476 (ZI426, &ZI481);
	    ZR518 (ZI426, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI432) = end_field_exp ( lex_dot, (ZI457), (ZI415), (ZI426), (ZI420), (ZI481) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI1239 = ZI432;
	    goto ZL2_1241;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1240 = ZI1239;
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
    *ZO1240 = ZI1240;
}

void
ZR670(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
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
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI432) = NULL_exp ;
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
      case 286: case 299: case 330:
	{
	    EXP ZI1288;
	    EXP ZI494;
	    int ZI671;

	    ZR497 (&ZI1288);
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
ZR1078(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 139:
	{
	    ADVANCE_LEXER;
	    ZR1259 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 154:
	{
	    ADVANCE_LEXER;
	    ZR1260 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 126:
	{
	    ZR1057 (&ZI432);
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
ZR1126(OFFSET ZI457, TYPE ZI575, OFFSET *ZO494, TYPE *ZO415)
{
    OFFSET ZI494;
    TYPE ZI415;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	NAMESPACE ZI426;
	IDENTIFIER ZI420;

	{

    (ZI426) = offset_nspace ( (ZI575) ) ;
	}
	{

    RESCAN_LEXER ;
	}
	ZR518 (ZI426, &ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    OFFSET off = offset_member ( (ZI575), (ZI420), &(ZI415), (ZI426), 1 ) ;
    (ZI494) = offset_add ( (ZI457), off ) ;
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
    *ZO494 = ZI494;
    *ZO415 = ZI415;
}

void
ZR1369(DECL_SPEC *ZI690, TYPE *ZI498, BASE_TYPE *ZI481, ACCESS_LIST *ZI671, int *ZI721, IDENTIFIER *ZI1368, IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    IDENTIFIER ZI1354;
	    TYPE ZI1355;
	    int ZI1356;
	    TYPE ZI1348;
	    IDENTIFIER ZI420;
	    int ZI559;
	    TYPE ZI415;
	    int ZI1086;
	    EXP ZI432;

	    {

    (ZI1354) = constr_name ( last_namespace, (*ZI1368) ) ;
	    }
	    {

    (ZI1355) = NULL_type ;
	    }
	    {
 (ZI1356) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1354), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1178 (ZI1355, ZI1354, ZI1356, &ZI1348, &ZI420, &ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (*ZI498) ) ) template_decl ( (*ZI498) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1348) ) ? (*ZI498) : inject_pre_type ( (ZI1348), (*ZI498), 1 ) ) ;
	    }
	    {

    if ( (ZI559) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (*ZI690) ;
    if ( type_tag ( (ZI415) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI415) ) ;
	if ( ds & dspec_friend ) {
	    (ZI460) = make_friend_decl ( ds, (ZI415), (ZI420), def, 1 ) ;
	    (ZI1086) = 1 ;
	} else {
	    (ZI460) = make_func_mem_decl ( ds, (ZI415), (ZI420), def ) ;
	    (ZI1086) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (*ZI721) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI460) = make_member_decl ( ds, (ZI415), (ZI420), f ) ;
	(ZI1086) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI460) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI460) ) ) ;
	bs |= (*ZI481) ;
	COPY_btype ( id_type_alias_rep ( (ZI460) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(*ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	    ZR1084 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1086) ? init_object ( (ZI460), (ZI432) ) : init_member ( (ZI460), (ZI432) ) ) ;
    if ( do_dump ) dump_declare ( (ZI460), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
	    }
	}
	break;
      case 41:
	{
	    QUALIFIER ZI456;
	    int ZI457;
	    EXP ZI559;
	    TYPE ZI415;

	    {

    if ( !IS_NULL_type ( (*ZI498) ) ) template_decl ( (*ZI498) ) ;
	    }
	    {

    begin_declarator ( (*ZI1368), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    ADVANCE_LEXER;
	    ZR652 (&ZI559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1368) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI415) = make_bitfield_type ( (*ZI498), (*ZI481), (ZI559), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( (*ZI690), (ZI415), (*ZI1368), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZI460) = id ;
	    }
	    {

    IGNORE clear_access ( (ZI460), &(*ZI671) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI460) ) ;
    }
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
    *ZO460 = ZI460;
}

void
ZR509(IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI420 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 3: case 4:
	{
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
ZR763(EXP ZI494)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI559;
	int ZI552;
	IDENTIFIER ZI460;
	EXP ZI457;
	EXP ZI764;
	EXP ZI765;
	EXP ZI766;
	EXP ZI767;
	EXP ZI768;
	EXP ZI769;
	EXP ZI770;

	switch (CURRENT_TERMINAL) {
	  case 128:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZI559) = begin_compound_stmt ( 1 ) ;
	}
	{

    inject_try_stmt ( (ZI494) ) ;
	}
	{

    (ZI552) = no_type_defns ;
	}
	switch (CURRENT_TERMINAL) {
	  case 65:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR762 (ZI552, &ZI460);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI457) = begin_catch_stmt ( (ZI494), (ZI460) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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
	{

    (ZI764) = NULL_exp ;
	}
	{

    (ZI765) = (ZI764) ;
    in_declaration-- ;
	}
	{

    (ZI766) = add_compound_stmt ( (ZI559), (ZI765) ) ;
	}
	{

    MAKE_exp_thrown ( type_void, 1, (ZI767) ) ;
	}
	{

    (ZI768) = add_compound_stmt ( (ZI766), (ZI767) ) ;
	}
	ZR677 (ZI768, &ZI769);
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

    (ZI770) = end_compound_stmt ( (ZI769) ) ;
	}
	{

    IGNORE end_catch_stmt ( (ZI457), (ZI770) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1031(void)
{
    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	{
	    EXP ZI498;

	    ZR1030 (&ZI498);
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
			ZR1029 ();
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
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
	    {

    crt_hash_cond = (ZI498) ;
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
ZR602(EXP *ZO1236)
{
    EXP ZI1236;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI432;

	ZR582 (&ZI432);
	ZR1237 (ZI432, &ZI1236);
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
    *ZO1236 = ZI1236;
}

void
ZR476(NAMESPACE ZI426, int *ZO415)
{
    int ZI415;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    {
 (ZI415) = 0 ; 
	    }
	}
	break;
      case 147:
	{
	    {

    rescan_template ( (ZI426) ) ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI415) = 1 ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *ZO415 = ZI415;
}

void
ZR828(DECL_SPEC *ZO494)
{
    DECL_SPEC ZI494;

    switch (CURRENT_TERMINAL) {
      case 142:
	{
	    ADVANCE_LEXER;
	    {
 (ZI494) = dspec_private ; 
	    }
	}
	break;
      case 143:
	{
	    ADVANCE_LEXER;
	    {
 (ZI494) = dspec_protected ; 
	    }
	}
	break;
      case 144:
	{
	    ADVANCE_LEXER;
	    {
 (ZI494) = dspec_public ; 
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
}

void
ZR1372(TYPE *ZO1160, IDENTIFIER *ZO1161)
{
    TYPE ZI1160;
    IDENTIFIER ZI1161;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1373;
	TYPE ZI1374;
	TYPE ZI415;
	IDENTIFIER ZI420;

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
	ZR1162 (ZI415, ZI420, &ZI1160, &ZI1161);
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
	    TYPE ZI415;
	    IDENTIFIER ZI420;

	    ADVANCE_LEXER;
	    ZR1372 (&ZI415, &ZI420);
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
	    ZR1162 (ZI415, ZI420, &ZI1160, &ZI1161);
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
	    TYPE ZI415;
	    IDENTIFIER ZI420;

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
	    ZR1162 (ZI415, ZI420, &ZI1160, &ZI1161);
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
	    TYPE ZI415;
	    IDENTIFIER ZI420;

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
	    ZR1162 (ZI415, ZI420, &ZI1160, &ZI1161);
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
	    IDENTIFIER ZI420;
	    TYPE ZI415;

	    ZR927 (&ZI498);
	    ZR960 (&ZI481, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI481) ) ? (ZI498) : inject_pre_type ( (ZI481), (ZI498), 0 ) ) ;
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
	    ZR1162 (ZI415, ZI420, &ZI1160, &ZI1161);
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
	    IDENTIFIER ZI1370;
	    int ZI944;
	    TYPE ZI415;
	    IDENTIFIER ZI420;

	    {

    (ZI1370) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI944) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1370) ) ;
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
	    ZR1162 (ZI415, ZI420, &ZI1160, &ZI1161);
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
    *ZO1160 = ZI1160;
    *ZO1161 = ZI1161;
}

void
ZR1053(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 154:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR1258 ();
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

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
		    ZR652 (&ZI559);
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
		    ZR956 (ZI481, &ZI415);
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

/* END OF FILE */
