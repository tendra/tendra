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
ZR1232 PROTO_N ((ZI1230, ZO1231))
  PROTO_T (EXP ZI1230 X EXP *ZO1231)
{
    EXP ZI1231;

  ZL2_1232:;
    switch (CURRENT_TERMINAL) {
      case 44:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR601 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_mult_exp ( lex_div, (ZI1230), (ZI456) ) ;
	    }
	    ZI1230 = ZI431;
	    goto ZL2_1232;
	}
	/*UNREACHED*/
      case 73:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR601 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_rem_exp ( (ZI1230), (ZI456) ) ;
	    }
	    ZI1230 = ZI431;
	    goto ZL2_1232;
	}
	/*UNREACHED*/
      case 78:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR601 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_mult_exp ( lex_star, (ZI1230), (ZI456) ) ;
	    }
	    ZI1230 = ZI431;
	    goto ZL2_1232;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1231 = ZI1230;
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
    *ZO1231 = ZI1231;
}

void
ZR899 PROTO_N ((ZO689))
  PROTO_T (DECL_SPEC *ZO689)
{
    DECL_SPEC ZI689;

    switch (CURRENT_TERMINAL) {
      case 133:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_explicit ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_inline ; 
	    }
	}
	break;
      case 274:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_none ; 
	    }
	}
	break;
      case 155:
	{
	    ADVANCE_LEXER;
	    {
 (ZI689) = dspec_virtual ; 
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
ZR661 PROTO_N ((ZO431))
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
	ZR687 (ZI414, ZI689, &ZI493);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI431) = (ZI493) ;
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
	    int ZI450;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_alignof ; 
	    }
	    ZR593 (ZI450, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    ZR1474 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1279;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1279 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1240 (ZI1279, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI493;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI493 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

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
	    ZR1240 (ZI1282, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    TYPE ZI414;
	    EXP ZI1460;
	    int ZI551;
	    EXP ZI1271;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1460, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1271) = make_const_cast_exp ( (ZI414), (ZI1460), (ZI551) ) ;
	    }
	    ZR1240 (ZI1271, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
      case 205:
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1453);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_cast_exp ( type_void, (ZI1453), 0 ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    TYPE ZI414;
	    EXP ZI1463;
	    int ZI551;
	    EXP ZI1274;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1463, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_dynamic_cast_exp ( (ZI414), (ZI1463), (ZI551) ) ;
	    }
	    ZR1240 (ZI1274, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
      case 209:
	{
	    EXP ZI1277;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    {

    (ZI1277) = make_ellipsis_exp () ;
	    }
	    ZR1240 (ZI1277, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    NAMESPACE ZI425;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1473 (&ZI425, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1464;

	    {

    ZI1464 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1469 (&ZI1464, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 345:
	{
	    ADVANCE_LEXER;
	    ZR1439 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI1455;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_prefix_exp ( lex_minus_Hminus, (ZI1455) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI1468;

	    {

    ZI1468 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1469 (&ZI1468, &ZI431);
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
	    ZR1472 (&ZI425, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR1286 (&ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI1454;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1454);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_prefix_exp ( lex_plus_Hplus, (ZI1454) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    TYPE ZI414;
	    EXP ZI1461;
	    int ZI551;
	    EXP ZI1272;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1461, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_reinterp_cast_exp ( (ZI414), (ZI1461), (ZI551) ) ;
	    }
	    ZR1240 (ZI1272, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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

    (ZI431) = NULL_exp ;
	    }
	}
	break;
      case 116:
	{
	    int ZI450;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_sizeof ; 
	    }
	    ZR593 (ZI450, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI1456;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_indir_exp ( (ZI1456) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI1470;

	    {

    ZI1470 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1471 (&ZI1470, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 146:
	{
	    TYPE ZI414;
	    EXP ZI1462;
	    int ZI551;
	    EXP ZI1273;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1462, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1273) = make_static_cast_exp ( (ZI414), (ZI1462), (ZI551) ) ;
	    }
	    ZR1240 (ZI1273, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

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
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1281;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI460 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = (ZI460) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
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
	    ZR1240 (ZI1281, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI1276;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    {

    (ZI1276) = make_this_exp () ;
	    }
	    ZR1240 (ZI1276, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI1466;

	    {

    ZI1466 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1467 (&ZI1466, &ZI431);
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_typeid ; 
	    }
	    ZR553 (ZI450, &ZI1270);
	    ZR1240 (ZI1270, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
      case 329:
	{
	    int ZI450;
	    EXP ZI1269;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_vtable ; 
	    }
	    ZR553 (ZI450, &ZI1269);
	    ZR1240 (ZI1269, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI1457;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

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
	    ZR581 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_ref_exp ( (ZI1457), 0 ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
      case 156: case 184: case 285: case 298:
	{
	    BASE_TYPE ZI511;
	    TYPE ZI1265;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1280;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

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
	    ZR1240 (ZI1280, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    ZR678 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 288: case 322:
	{
	    ZR776 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 96: case 100: case 222:
	{
	    ZR662 ();
	    ZR1440 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 297: case 323:
	{
	    EXP ZI1434;
	    EXP ZI493;
	    int ZI670;

	    ZR643 (&ZI1434);
	    ZR1436 (&ZI1434, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    ZR738 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    ZR752 (&ZI431);
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ZR437 (&ZI1275);
	    ZR1240 (ZI1275, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    EXP ZI1458;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

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
	    ZR581 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_not_exp ( (ZI1458) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

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
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    ZR713 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 149:
	{
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ZR635 (&ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    ZR771 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI456;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    {
 (ZI456) = 0 ; 
	    }
	    ZR1430 (&ZI456, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
	    int ZI450;
	    EXP ZI1459;
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
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR596 ();
	    ZR581 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_uminus_exp ( (ZI450), (ZI1459) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1236 PROTO_N ((ZI1234, ZO1235))
  PROTO_T (EXP ZI1234 X EXP *ZO1235)
{
    EXP ZI1235;

  ZL2_1236:;
    switch (CURRENT_TERMINAL) {
      case 82:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    {

    in_ptr_mem_selector++ ;
	    }
	    ZR581 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_member_exp ( lex_arrow_Hstar, (ZI1234), (ZI456) ) ;
    in_ptr_mem_selector-- ;
	    }
	    ZI1234 = ZI431;
	    goto ZL2_1236;
	}
	/*UNREACHED*/
      case 84:
	{
	    EXP ZI456;
	    EXP ZI431;

	    ADVANCE_LEXER;
	    {

    in_ptr_mem_selector++ ;
	    }
	    ZR581 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_member_exp ( lex_dot_Hstar, (ZI1234), (ZI456) ) ;
    in_ptr_mem_selector-- ;
	    }
	    ZI1234 = ZI431;
	    goto ZL2_1236;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1235 = ZI1234;
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
    *ZO1235 = ZI1235;
}

void
ZR954 PROTO_N ((ZO1138))
  PROTO_T (TYPE *ZO1138)
{
    TYPE ZI1138;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1383 (&ZI1138);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI419;
	    int ZI943;
	    TYPE ZI414;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 1 ; 
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
      case 66:
	{
	    EXP ZI431;
	    TYPE ZI414;

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
    MAKE_type_array ( cv_none, NULL_type, n, (ZI414) ) ;
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
ZR1365 PROTO_N ((ZI689, ZI497, ZI480, ZI670, ZI720, ZI1364, ZO459))
  PROTO_T (DECL_SPEC *ZI689 X TYPE *ZI497 X BASE_TYPE *ZI480 X ACCESS_LIST *ZI670 X int *ZI720 X IDENTIFIER *ZI1364 X IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    QUALIFIER ZI455;
	    int ZI456;
	    EXP ZI558;
	    TYPE ZI414;

	    {

    if ( !IS_NULL_type ( (*ZI497) ) ) template_decl ( (*ZI497) ) ;
	    }
	    {

    begin_declarator ( (*ZI1364), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	    }
	    ADVANCE_LEXER;
	    ZR651 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1364) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI414) = make_bitfield_type ( (*ZI497), (*ZI480), (ZI558), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( (*ZI689), (ZI414), (*ZI1364), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZI459) = id ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(*ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      default:
	{
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (*ZI1364), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, *ZI1364, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (*ZI497) ) ) template_decl ( (*ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (*ZI497) : inject_pre_type ( (ZI1347), (*ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (*ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (*ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (*ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(*ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
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
    *ZO459 = ZI459;
}

void
ZR770 PROTO_N ((ZI493))
  PROTO_T (EXP ZI493)
{
  ZL2_770:;
    switch (CURRENT_TERMINAL) {
      case 128:
	{
	    ZR762 (ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_770;
	    }
	}
	/*UNREACHED*/
      case 354:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR738 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 101:
	{
	    unsigned ZI714;
	    int ZI670;
	    EXP ZI493;
	    EXP ZI715;
	    EXP ZI456;
	    EXP ZI739;
	    EXP ZI558;

	    ADVANCE_LEXER;
	    {
 (ZI714) = crt_condition ; 
	    }
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

    (ZI493) = begin_do_stmt () ;
	    }
	    {

    (ZI715) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR681 (ZI715, &ZI456);
	    switch (CURRENT_TERMINAL) {
	      case 125:
		break;
	      case 354:
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
	    ZR491 (&ZI739);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI558) = bind_temporary ( (ZI739) ) ;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI431) = end_do_stmt ( (ZI493), (ZI456), (ZI558) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 crt_condition = (ZI714) ; 
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR418 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 107:
	{
	    unsigned ZI714;
	    int ZI670;
	    EXP ZI720;
	    EXP ZI493;
	    EXP ZI740;
	    EXP ZI558;
	    EXP ZI741;
	    EXP ZI689;
	    EXP ZI456;
	    EXP ZI742;
	    EXP ZI743;
	    EXP ZI744;
	    EXP ZI459;

	    ADVANCE_LEXER;
	    {
 (ZI714) = crt_condition ; 
	    }
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
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI720) = begin_for_stmt () ;
	    }
	    ZR735 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI740) = init_for_stmt ( (ZI720), &(ZI493) ) ;
	    }
	    ZR736 (&ZI558, &ZI741);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI689) = begin_compound_stmt ( 1 ) ;
	    }
	    ZR737 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI742) = cond_for_stmt ( (ZI740), (ZI741), (ZI456) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI743) = inject_cond ( (ZI689), (ZI493) ) ;
	    }
	    {

    (ZI744) = inject_cond ( (ZI743), (ZI558) ) ;
	    }
	    {

    mark_compound_stmt ( (ZI744) ) ;
	    }
	    ZR681 (ZI744, &ZI459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI431) = end_for_stmt ( (ZI742), (ZI459) ) ;
	    }
	    {
 crt_condition = (ZI714) ; 
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
	    unsigned ZI714;
	    int ZI670;
	    EXP ZI739;
	    EXP ZI558;
	    EXP ZI493;
	    EXP ZI715;
	    EXP ZI716;
	    EXP ZI456;

	    ADVANCE_LEXER;
	    {
 (ZI714) = crt_condition ; 
	    }
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
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR712 (&ZI739);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI558) = bind_temporary ( (ZI739) ) ;
	    }
	    {

    (ZI493) = begin_while_stmt ( (ZI558) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI715) = begin_compound_stmt ( 1 ) ;
	    }
	    {

    (ZI716) = inject_cond ( (ZI715), (ZI558) ) ;
	    }
	    ZR681 (ZI716, &ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI670) ; 
	    }
	    {

    (ZI431) = end_while_stmt ( (ZI493), (ZI456) ) ;
	    }
	    {
 crt_condition = (ZI714) ; 
	    }
	    {

    unreached_fall = 1 ;
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
ZR1240 PROTO_N ((ZI1238, ZO1239))
  PROTO_T (EXP ZI1238 X EXP *ZO1239)
{
    EXP ZI1239;

  ZL2_1240:;
    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    EXP ZI431;

	    ADVANCE_LEXER;
	    {

    (ZI431) = make_postfix_exp ( lex_minus_Hminus, (ZI1238) ) ;
	    }
	    ZI1238 = ZI431;
	    goto ZL2_1240;
	}
	/*UNREACHED*/
      case 65:
	{
	    SID_LIST_EXP ZI497;
	    EXP ZI431;

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

    (ZI431) = make_func_exp ( (ZI1238), (ZI497), 0 ) ;
	    }
	    ZI1238 = ZI431;
	    goto ZL2_1240;
	}
	/*UNREACHED*/
      case 71:
	{
	    EXP ZI431;

	    ADVANCE_LEXER;
	    {

    (ZI431) = make_postfix_exp ( lex_plus_Hplus, (ZI1238) ) ;
	    }
	    ZI1238 = ZI431;
	    goto ZL2_1240;
	}
	/*UNREACHED*/
      case 66:
	{
	    EXP ZI456;
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
	    ZR491 (&ZI456);
	    {
		if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = make_index_exp ( (ZI1238), (ZI456) ) ;
	    }
	    ZI1238 = ZI431;
	    goto ZL2_1240;
	}
	/*UNREACHED*/
      case 35:
	{
	    EXP ZI456;
	    TYPE ZI414;
	    NAMESPACE ZI425;
	    int ZI480;
	    IDENTIFIER ZI419;
	    EXP ZI431;

	    {

    (ZI456) = begin_field_exp ( lex_arrow, (ZI1238), &(ZI414), &(ZI425) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR475 (ZI425, &ZI480);
	    ZR517 (ZI425, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_field_exp ( lex_arrow, (ZI456), (ZI414), (ZI425), (ZI419), (ZI480) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI1238 = ZI431;
	    goto ZL2_1240;
	}
	/*UNREACHED*/
      case 46:
	{
	    EXP ZI456;
	    TYPE ZI414;
	    NAMESPACE ZI425;
	    int ZI480;
	    IDENTIFIER ZI419;
	    EXP ZI431;

	    {

    (ZI456) = begin_field_exp ( lex_dot, (ZI1238), &(ZI414), &(ZI425) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR475 (ZI425, &ZI480);
	    ZR517 (ZI425, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_field_exp ( lex_dot, (ZI456), (ZI414), (ZI425), (ZI419), (ZI480) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI1238 = ZI431;
	    goto ZL2_1240;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1239 = ZI1238;
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
    *ZO1239 = ZI1239;
}

void
ZR639 PROTO_Z ()
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
ZR1368 PROTO_N ((ZI689, ZI497, ZI480, ZI670, ZI720, ZI1367, ZO459))
  PROTO_T (DECL_SPEC *ZI689 X TYPE *ZI497 X BASE_TYPE *ZI480 X ACCESS_LIST *ZI670 X int *ZI720 X IDENTIFIER *ZI1367 X IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    IDENTIFIER ZI1353;
	    TYPE ZI1354;
	    int ZI1355;
	    TYPE ZI1347;
	    IDENTIFIER ZI419;
	    int ZI558;
	    TYPE ZI414;
	    int ZI1085;
	    EXP ZI431;

	    {

    (ZI1353) = constr_name ( last_namespace, (*ZI1367) ) ;
	    }
	    {

    (ZI1354) = NULL_type ;
	    }
	    {
 (ZI1355) = 0 ; 
	    }
	    {

    begin_declarator ( (ZI1353), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    ZR1177 (ZI1354, ZI1353, ZI1355, &ZI1347, &ZI419, &ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( !IS_NULL_type ( (*ZI497) ) ) template_decl ( (*ZI497) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1347) ) ? (*ZI497) : inject_pre_type ( (ZI1347), (*ZI497), 1 ) ) ;
	    }
	    {

    if ( (ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	    }
	    {

    DECL_SPEC ds = (*ZI689) ;
    if ( type_tag ( (ZI414) ) == type_func_tag ) {
	/* Look ahead for function definitions */
	int def = predict_func_defn () ;
	if ( def & !have_func_declarator ) adjust_param ( (ZI414) ) ;
	if ( ds & dspec_friend ) {
	    (ZI459) = make_friend_decl ( ds, (ZI414), (ZI419), def, 1 ) ;
	    (ZI1085) = 1 ;
	} else {
	    (ZI459) = make_func_mem_decl ( ds, (ZI414), (ZI419), def ) ;
	    (ZI1085) = 0 ;
	}
	is_function_next = def ;
    } else {
	int f = ( (*ZI720) && ( crt_lex_token == lex_semicolon ) ) ;
	(ZI459) = make_member_decl ( ds, (ZI414), (ZI419), f ) ;
	(ZI1085) = 0 ;
	is_function_next = 0 ;
    }
    if ( IS_id_type_alias ( (ZI459) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI459) ) ) ;
	bs |= (*ZI480) ;
	COPY_btype ( id_type_alias_rep ( (ZI459) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(*ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	    ZR1083 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = ( (ZI1085) ? init_object ( (ZI459), (ZI431) ) : init_member ( (ZI459), (ZI431) ) ) ;
    if ( do_dump ) dump_declare ( (ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
	    }
	}
	break;
      case 41:
	{
	    QUALIFIER ZI455;
	    int ZI456;
	    EXP ZI558;
	    TYPE ZI414;

	    {

    if ( !IS_NULL_type ( (*ZI497) ) ) template_decl ( (*ZI497) ) ;
	    }
	    {

    begin_declarator ( (*ZI1367), crt_id_qualifier, qual_namespace, 1 ) ;
	    }
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
	    }
	    ADVANCE_LEXER;
	    ZR651 (&ZI558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1367) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI414) = make_bitfield_type ( (*ZI497), (*ZI480), (ZI558), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( (*ZI689), (ZI414), (*ZI1367), 0 ) ;
    int def = init_member ( id, NULL_exp ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, def ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    is_function_next = 0 ;
    (ZI459) = id ;
	    }
	    {

    IGNORE clear_access ( (ZI459), &(*ZI670) ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (ZI459) ) ;
    }
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
    *ZO459 = ZI459;
}

void
ZR669 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 345:
	{
	    ADVANCE_LEXER;
	    ZR1439 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI431) = NULL_exp ;
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
      case 285: case 298: case 329:
	{
	    EXP ZI1287;
	    EXP ZI493;
	    int ZI670;

	    ZR496 (&ZI1287);
	    ZR1289 (&ZI1287, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
      case 297: case 323:
	{
	    EXP ZI1434;
	    EXP ZI493;
	    int ZI670;

	    ZR643 (&ZI1434);
	    ZR1436 (&ZI1434, &ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
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

    (ZI431) = make_exp_stmt ( (ZI493) ) ;
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
ZR1077 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 139:
	{
	    ADVANCE_LEXER;
	    ZR1258 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 154:
	{
	    ADVANCE_LEXER;
	    ZR1259 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 126:
	{
	    ZR1056 (&ZI431);
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
ZR1125 PROTO_N ((ZI456, ZI574, ZO493, ZO414))
  PROTO_T (OFFSET ZI456 X TYPE ZI574 X OFFSET *ZO493 X TYPE *ZO414)
{
    OFFSET ZI493;
    TYPE ZI414;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	NAMESPACE ZI425;
	IDENTIFIER ZI419;

	{

    (ZI425) = offset_nspace ( (ZI574) ) ;
	}
	{

    RESCAN_LEXER ;
	}
	ZR517 (ZI425, &ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    OFFSET off = offset_member ( (ZI574), (ZI419), &(ZI414), (ZI425), 1 ) ;
    (ZI493) = offset_add ( (ZI456), off ) ;
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
    *ZO493 = ZI493;
    *ZO414 = ZI414;
}

void
ZR508 PROTO_N ((ZO419))
  PROTO_T (IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI419 = parse_type_template ( id, args, 0 ) ;
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
ZR762 PROTO_N ((ZI493))
  PROTO_T (EXP ZI493)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI558;
	int ZI551;
	IDENTIFIER ZI459;
	EXP ZI456;
	EXP ZI763;
	EXP ZI764;
	EXP ZI765;
	EXP ZI766;
	EXP ZI767;
	EXP ZI768;
	EXP ZI769;

	switch (CURRENT_TERMINAL) {
	  case 128:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZI558) = begin_compound_stmt ( 1 ) ;
	}
	{

    inject_try_stmt ( (ZI493) ) ;
	}
	{

    (ZI551) = no_type_defns ;
	}
	switch (CURRENT_TERMINAL) {
	  case 65:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR761 (ZI551, &ZI459);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI456) = begin_catch_stmt ( (ZI493), (ZI459) ) ;
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

    COPY_int ( exp_sequence_block ( (ZI558) ), 2 ) ;
	}
	{

    (ZI763) = NULL_exp ;
	}
	{

    (ZI764) = (ZI763) ;
    in_declaration-- ;
	}
	{

    (ZI765) = add_compound_stmt ( (ZI558), (ZI764) ) ;
	}
	{

    MAKE_exp_thrown ( type_void, 1, (ZI766) ) ;
	}
	{

    (ZI767) = add_compound_stmt ( (ZI765), (ZI766) ) ;
	}
	ZR676 (ZI767, &ZI768);
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

    (ZI769) = end_compound_stmt ( (ZI768) ) ;
	}
	{

    IGNORE end_catch_stmt ( (ZI456), (ZI769) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1030 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	{
	    EXP ZI497;

	    ZR1029 (&ZI497);
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
			ZR1028 ();
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
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
	    {

    crt_hash_cond = (ZI497) ;
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
ZR601 PROTO_N ((ZO1235))
  PROTO_T (EXP *ZO1235)
{
    EXP ZI1235;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR581 (&ZI431);
	ZR1236 (ZI431, &ZI1235);
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
    *ZO1235 = ZI1235;
}

void
ZR1371 PROTO_N ((ZO1159, ZO1160))
  PROTO_T (TYPE *ZO1159 X IDENTIFIER *ZO1160)
{
    TYPE ZI1159;
    IDENTIFIER ZI1160;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI1372;
	TYPE ZI1373;
	TYPE ZI414;
	IDENTIFIER ZI419;

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
	ZR1161 (ZI414, ZI419, &ZI1159, &ZI1160);
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
	    TYPE ZI414;
	    IDENTIFIER ZI419;

	    ADVANCE_LEXER;
	    ZR1371 (&ZI414, &ZI419);
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
	    ZR1161 (ZI414, ZI419, &ZI1159, &ZI1160);
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
	    TYPE ZI414;
	    IDENTIFIER ZI419;

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
	    ZR1161 (ZI414, ZI419, &ZI1159, &ZI1160);
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
	    TYPE ZI414;
	    IDENTIFIER ZI419;

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
	    ZR1161 (ZI414, ZI419, &ZI1159, &ZI1160);
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
	    IDENTIFIER ZI419;
	    TYPE ZI414;

	    ZR926 (&ZI497);
	    ZR959 (&ZI480, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI497) : inject_pre_type ( (ZI480), (ZI497), 0 ) ) ;
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
	    ZR1161 (ZI414, ZI419, &ZI1159, &ZI1160);
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
	    IDENTIFIER ZI1369;
	    int ZI943;
	    TYPE ZI414;
	    IDENTIFIER ZI419;

	    {

    (ZI1369) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1369) ) ;
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
	    ZR1161 (ZI414, ZI419, &ZI1159, &ZI1160);
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
    *ZO1159 = ZI1159;
    *ZO1160 = ZI1160;
}

void
ZR475 PROTO_N ((ZI425, ZO414))
  PROTO_T (NAMESPACE ZI425 X int *ZO414)
{
    int ZI414;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    {
 (ZI414) = 0 ; 
	    }
	}
	break;
      case 147:
	{
	    {

    rescan_template ( (ZI425) ) ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI414) = 1 ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *ZO414 = ZI414;
}

void
ZR827 PROTO_N ((ZO493))
  PROTO_T (DECL_SPEC *ZO493)
{
    DECL_SPEC ZI493;

    switch (CURRENT_TERMINAL) {
      case 142:
	{
	    ADVANCE_LEXER;
	    {
 (ZI493) = dspec_private ; 
	    }
	}
	break;
      case 143:
	{
	    ADVANCE_LEXER;
	    {
 (ZI493) = dspec_protected ; 
	    }
	}
	break;
      case 144:
	{
	    ADVANCE_LEXER;
	    {
 (ZI493) = dspec_public ; 
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
}

void
ZR1052 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
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
	ZR1257 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

/* END OF FILE */
