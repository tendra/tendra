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
ZR1327 PROTO_N ((ZO844))
  PROTO_T (int *ZO844)
{
    int ZI844;

    switch (CURRENT_TERMINAL) {
      case 155:
	{
	    ADVANCE_LEXER;
	    {
 (ZI844) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZI844) = 0 ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *ZO844 = ZI844;
}

void
ZR1200 PROTO_N ((ZI1198, ZO1199))
  PROTO_T (EXP ZI1198 X EXP *ZO1199)
{
    EXP ZI1199;

  ZL2_1200:;
    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    EXP ZI456;
	    EXP ZI431;

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
	    ZR624 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_or_exp ( (ZI1198), (ZI456) ) ;
	    }
	    ZI1198 = ZI431;
	    goto ZL2_1200;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1199 = ZI1198;
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
    *ZO1199 = ZI1199;
}

void
ZR614 PROTO_N ((ZO1219))
  PROTO_T (EXP *ZO1219)
{
    EXP ZI1219;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR611 (&ZI431);
	ZR1220 (ZI431, &ZI1219);
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
    *ZO1219 = ZI1219;
}

void
ZR838 PROTO_N ((ZI414, ZI689))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
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
	    goto ZL2;
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
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 134: case 147:
	{
	    ZR1089 (ZI414, ZI689);
	    if ((CURRENT_TERMINAL) == 354) {
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
	    }
	}
	break;
      case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI689) ) ;
	    }
	    ZR1052 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
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
	}
	break;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
}

void
ZR1328 PROTO_N ((ZO493))
  PROTO_T (DECL_SPEC *ZO493)
{
    DECL_SPEC ZI493;

    switch (CURRENT_TERMINAL) {
      case 142: case 143: case 144:
	{
	    ZR827 (&ZI493);
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
    *ZO493 = ZI493;
}

void
ZR737 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
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
	    EXP ZI493;
	    EXP ZI456;

	    ZR491 (&ZI493);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI456) = make_exp_stmt ( (ZI493) ) ;
	    }
	    {

    (ZI431) = bind_temporary ( (ZI456) ) ;
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
ZR1075 PROTO_N ((ZI511, ZI1073, ZI1074, ZI670, ZI558, ZI459))
  PROTO_T (BASE_TYPE *ZI511 X DECL_SPEC *ZI1073 X TYPE *ZI1074 X ACCESS_LIST *ZI670 X int *ZI558 X IDENTIFIER *ZI459)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI456;
	EXP ZI431;

	{

    /* Resolve function definitions from other declarations */
    (ZI0) = is_function_next ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    if ( (*ZI558) ) report ( crt_loc, ERR_dcl_init_bad () ) ;
	}
	{

    free_access ( &(*ZI670) ) ;
	}
	{

    (ZI456) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (*ZI459) ) ;
	}
	ZR1024 (&ZI431);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IGNORE end_function ( (*ZI459), (ZI431) ) ;
    in_class_defn = (ZI456) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
	}
	{

    end_declarator ( (*ZI459), 1 ) ;
	}
	{

    RESCAN_LEXER ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    {
	SID_LIST_EXP ZI497;
	EXP ZI431;

	{

    (ZI0) = (*ZI558) ;
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
	ZR1002 (*ZI459, &ZI497);
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
	{

    int def = init_object ( (*ZI459), (ZI431) ) ;
    if ( do_dump ) dump_declare ( (*ZI459), &decl_loc, def ) ;
	}
	{

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZI459) ) ;
    }
	}
	{

    end_declarator ( (*ZI459), 1 ) ;
	}
	ZR1076 (ZI511, ZI1073, ZI1074, ZI670);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    free_access ( &(*ZI670) ) ;
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
	    EXP ZI431;

	    ADVANCE_LEXER;
	    ZR998 (*ZI459, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = init_object ( (*ZI459), (ZI431) ) ;
    if ( do_dump ) dump_declare ( (*ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZI459) ) ;
    }
	    }
	    {

    end_declarator ( (*ZI459), 1 ) ;
	    }
	    ZR1076 (ZI511, ZI1073, ZI1074, ZI670);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI670) ) ;
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
	    EXP ZI431;

	    {

    (ZI431) = NULL_exp ;
	    }
	    {

    int def = init_object ( (*ZI459), (ZI431) ) ;
    if ( do_dump ) dump_declare ( (*ZI459), &decl_loc, def ) ;
	    }
	    {

    if ( crt_access_list.pending ) {
	IGNORE report_access ( (*ZI459) ) ;
    }
	    }
	    {

    end_declarator ( (*ZI459), 1 ) ;
	    }
	    ZR1076 (ZI511, ZI1073, ZI1074, ZI670);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    free_access ( &(*ZI670) ) ;
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
    SAVE_LEXER (354);
    return;
  ZL0:;
}

void
ZR568 PROTO_N ((ZO414, ZO551))
  PROTO_T (TYPE *ZO414 X int *ZO551)
{
    TYPE ZI414;
    int ZI551;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI554;
	BASE_TYPE ZI511;
	TYPE ZI497;
	CV_SPEC ZI783;
	TYPE ZI574;
	TYPE ZI480;

	{

    (ZI554) = no_type_defns ;
	}
	ZR873 (&ZI511, &ZI497, &ZI783);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI574) = complete_pre_type ( (ZI511), (ZI497), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR991 (&ZI480);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI414) = ( IS_NULL_type ( (ZI480) ) ? (ZI574) : inject_pre_type ( (ZI480), (ZI574), 1 ) ) ;
	}
	{

    (ZI551) = no_type_defns - (ZI554) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
    *ZO551 = ZI551;
}

void
ZR622 PROTO_N ((ZO1207))
  PROTO_T (EXP *ZO1207)
{
    EXP ZI1207;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;

	ZR620 (&ZI431);
	ZR1208 (ZI431, &ZI1207);
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
    *ZO1207 = ZI1207;
}

void
ZR1076 PROTO_N ((ZI511, ZI1073, ZI1074, ZI670))
  PROTO_T (BASE_TYPE *ZI511 X DECL_SPEC *ZI1073 X TYPE *ZI1074 X ACCESS_LIST *ZI670)
{
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    ADVANCE_LEXER;
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1009 (*ZI1073, *ZI511, *ZI1074, *ZI670);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
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
parse_exp PROTO_N ((ZO431))
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
ZR1204 PROTO_N ((ZI1202, ZO1203))
  PROTO_T (EXP ZI1202 X EXP *ZO1203)
{
    EXP ZI1203;

  ZL2_1204:;
    switch (CURRENT_TERMINAL) {
      case 80:
	{
	    EXP ZI456;
	    EXP ZI431;

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
	    ZR622 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_xor_exp ( (ZI1202), (ZI456) ) ;
	    }
	    ZI1202 = ZI431;
	    goto ZL2_1204;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1203 = ZI1202;
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
    *ZO1203 = ZI1203;
}

void
ZR687 PROTO_N ((ZI414, ZI689, ZO431))
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
	    {

    (ZI431) = NULL_exp ;
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
ZR635 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI493;

	switch (CURRENT_TERMINAL) {
	  case 149:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    {
		TYPE ZI414;
		int ZI551;

		{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
		}
		if (!ZI0)
		    goto ZL3;
		ZR548 (&ZI414, &ZI551);
		if ((CURRENT_TERMINAL) == 354) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{

    (ZI493) = make_throw_arg ( (ZI414), (ZI551) ) ;
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
	      case 285: case 298: case 329:
		{
		    ZR496 (&ZI493);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI493) = NULL_exp ;
		    }
		}
		break;
	    }
	  ZL2:;
	}
	{

    (ZI431) = make_throw_exp ( (ZI493), 1 ) ;
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
ZR953 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
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
      case 146: case 148: case 150: case 152: case 156:
      case 170: case 184: case 205: case 209: case 285:
      case 298: case 329:
	{
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
parse_stmt PROTO_N ((ZO431))
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
ZR1087 PROTO_N ((ZI689, ZI497, ZI480, ZI670, ZI720))
  PROTO_T (DECL_SPEC ZI689 X TYPE ZI497 X BASE_TYPE ZI480 X ACCESS_LIST ZI670 X int ZI720)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_1087:;
    {
	IDENTIFIER ZI459;

	ZR1084 (ZI689, ZI497, ZI480, ZI670, ZI720, &ZI459);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    end_declarator ( (ZI459), 1 ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    int ZI551;

		    ADVANCE_LEXER;
		    {
 (ZI551) = 0 ; 
		    }
		    {

    crt_templ_qualifier = 0 ;
		    }
		    ZI720 = ZI551;
		    goto ZL2_1087;
		}
		/*UNREACHED*/
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
ZR1208 PROTO_N ((ZI1206, ZO1207))
  PROTO_T (EXP ZI1206 X EXP *ZO1207)
{
    EXP ZI1207;

  ZL2_1208:;
    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    EXP ZI456;
	    EXP ZI431;

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
	    ZR620 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_and_exp ( (ZI1206), (ZI456) ) ;
	    }
	    ZI1206 = ZI431;
	    goto ZL2_1208;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1207 = ZI1206;
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
    *ZO1207 = ZI1207;
}

void
ZR548 PROTO_N ((ZO414, ZO551))
  PROTO_T (TYPE *ZO414 X int *ZO551)
{
    TYPE ZI414;
    int ZI551;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI554;
	BASE_TYPE ZI511;
	TYPE ZI497;
	CV_SPEC ZI783;
	TYPE ZI480;

	{

    (ZI554) = no_type_defns ;
	}
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
	{

    (ZI551) = no_type_defns - (ZI554) ;
	}
	{

    object_type ( (ZI414), null_tag ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
    *ZO551 = ZI551;
}

void
ZR643 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 297:
	{
	    EXP ZI493;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
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
	      case 39:
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
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
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
	      case 39:
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
ZR686 PROTO_N ((ZI414, ZI689))
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
    SAVE_LEXER (354);
    return;
  ZL0:;
}

void
ZR1028 PROTO_Z ()
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
	ZR1027 (ZI414, ZI689);
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
ZR451 PROTO_N ((ZO450))
  PROTO_T (int *ZO450)
{
    int ZI450;

    switch (CURRENT_TERMINAL) {
      case 131:
	{
	    ADVANCE_LEXER;
	    ZR1321 (&ZI450);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 140:
	{
	    ADVANCE_LEXER;
	    ZR1320 (&ZI450);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR413 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI450) = lex_func_Hop ; 
	    }
	}
	break;
      case 72:
	{
	    ADVANCE_LEXER;
	    ZR416 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI450) = lex_cond_Hop ; 
	    }
	    {

    /* Illegal overloaded operator */
    report ( crt_loc, ERR_over_oper_bad ( (ZI450) ) ) ;
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
	    ZR415 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI450) = lex_array_Hop ; 
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
      case 170: case 329:
	{
	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR1319 (&ZI450);
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
    *ZO450 = ZI450;
}

void
ZR1339 PROTO_N ((ZI414, ZI511, ZI875, ZI876, ZI911))
  PROTO_T (TYPE *ZI414 X BASE_TYPE *ZI511 X TYPE *ZI875 X CV_SPEC *ZI876 X DECL_SPEC *ZI911)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI911), (*ZI414), (*ZI511), (*ZI875), (*ZI876), last_lex_token, 1 ) ;
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
	    TYPE ZI879;
	    DECL_SPEC ZI1073;
	    TYPE ZI1074;
	    ACCESS_LIST ZI670;
	    int ZI720;
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
 (ZI720) = 1 ; 
	    }
	    {

    crt_templ_qualifier = 0 ;
	    }
	    ZR1084 (ZI1073, ZI1074, *ZI511, ZI670, ZI720, &ZI459);
	    ZR1092 (ZI511, &ZI1073, &ZI1074, &ZI670, &ZI459);
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
ZR1212 PROTO_N ((ZI1210, ZO1211))
  PROTO_T (EXP ZI1210 X EXP *ZO1211)
{
    EXP ZI1211;

  ZL2_1212:;
    switch (CURRENT_TERMINAL) {
      case 86: case 87:
	{
	    int ZI450;
	    EXP ZI456;
	    EXP ZI431;

	    {
 (ZI450) = crt_lex_token ; 
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
	    ZR617 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = make_mult_exp ( (ZI450), (ZI1210), (ZI456) ) ;
	    }
	    ZI1210 = ZI431;
	    goto ZL2_1212;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1211 = ZI1210;
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
    *ZO1211 = ZI1211;
}

void
ZR416 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
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
	int ZI414;

	{
 (ZI414) = lex_colon ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI414) ) report ( crt_loc, ERR_lex_expect ( (ZI414) ) ) ;
	}
    }
}

void
ZR498 PROTO_N ((ZO497))
  PROTO_T (SID_LIST_EXP *ZO497)
{
    SID_LIST_EXP ZI497;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI431;
	SID_LIST_EXP ZI480;

	ZR496 (&ZI431);
	ZR499 (&ZI480);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
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
ZR1467 PROTO_N ((ZI1466, ZO431))
  PROTO_T (IDENTIFIER *ZI1466 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
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

    (ZI419) = (*ZI1466) ;
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
      case 41:
	{
	    EXP ZI493;
	    EXP ZI456;

	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI493) = begin_label_stmt ( (*ZI1466), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR661 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_label_stmt ( (ZI493), (ZI456) ) ;
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
ZR1340 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ZR835 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 154:
	{
	    ZR1052 ();
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
ZR1595 PROTO_N ((ZI1594, ZO431))
  PROTO_T (EXP *ZI1594 X EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 346:
	{
	    SID_LIST_EXP ZI480;
	    SID_LIST_EXP ZI497;
	    EXP ZI493;
	    int ZI670;

	    ADVANCE_LEXER;
	    ZR648 (&ZI480);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1594), (ZI480), (ZI497) ) ;
	    }
	    {

    (ZI493) = make_comma_exp ( (ZI497) ) ;
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
	    int ZI670;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 346:
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

    (ZI431) = make_exp_stmt ( (*ZI1594) ) ;
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
ZR496 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
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
      case 146: case 148: case 150: case 152: case 156:
      case 170: case 184: case 205: case 209: case 285:
      case 298: case 329:
	{
	    EXP ZI1263;

	    ZR630 (&ZI1263);
	    ZR1264 (&ZI1263, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 149:
	{
	    ZR635 (&ZI431);
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
ZR1469 PROTO_N ((ZI1468, ZO431))
  PROTO_T (IDENTIFIER *ZI1468 X EXP *ZO431)
{
    EXP ZI431;

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

    (ZI419) = (*ZI1468) ;
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
      case 41:
	{
	    EXP ZI493;
	    EXP ZI456;

	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI493) = begin_label_stmt ( (*ZI1468), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR661 (&ZI456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI431) = end_label_stmt ( (ZI493), (ZI456) ) ;
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

/* END OF FILE */
