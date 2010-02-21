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
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
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
ZR768(TYPE ZI421, TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1045;
	TYPE ZI1046;
	TYPE ZI424;

	{

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
	}
	if (!ZI0)
	    goto ZL2;
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI1045 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI1045 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI1045 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI1046) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1045) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR858 (ZI1046, ZI1045, &ZI424, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI424;

	    ADVANCE_LEXER;
	    ZR1044 (&ZI424, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1043;
	    int ZI749;
	    TYPE ZI1049;
	    IDENTIFIER ZI1050;
	    TYPE ZI424;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1043) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1043) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR760 (&ZI749);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1049) = make_func_type ( NULL_type, ( (ZI749) | FUNC_WEAK ), cv_c, empty_type_set ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI1050) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1050) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR858 (ZI1049, ZI1050, &ZI424, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;
	    TYPE ZI1047;
	    IDENTIFIER ZI1048;
	    TYPE ZI424;

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
	    ZR759 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI405) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1047) ) ;
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
    (ZI1048) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1048) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR858 (ZI1047, ZI1048, &ZI424, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1051;
	    TYPE ZI1052;
	    TYPE ZI424;

	    ZR733 (&ZI1051);
	    ZR766 (&ZI1052, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI424) = ( IS_NULL_type ( (ZI1052) ) ? (ZI1051) : inject_pre_type ( (ZI1052), (ZI1051), 0 ) ) ;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI424;

	    {

    (ZI424) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
    *ZO400 = ZI400;
}

void
ZR924(EXP ZI922, EXP *ZO923)
{
    EXP ZI923;

  ZL2_924:;
    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    EXP ZI405;

	    ADVANCE_LEXER;
	    {

    (ZI405) = make_postfix_exp ( lex_minus_Hminus, (ZI922) ) ;
	    }
	    ZI922 = ZI405;
	    goto ZL2_924;
	}
	/*UNREACHED*/
      case 65:
	{
	    SID_LIST_EXP ZI421;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR425 (&ZI421);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_func_exp ( (ZI922), (ZI421), 0 ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZI922 = ZI405;
	    goto ZL2_924;
	}
	/*UNREACHED*/
      case 71:
	{
	    EXP ZI405;

	    ADVANCE_LEXER;
	    {

    (ZI405) = make_postfix_exp ( lex_plus_Hplus, (ZI922) ) ;
	    }
	    ZI922 = ZI405;
	    goto ZL2_924;
	}
	/*UNREACHED*/
      case 66:
	{
	    EXP ZI449;
	    EXP ZI405;

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
	    ZR415 (&ZI449);
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

    (ZI405) = make_index_exp ( (ZI922), (ZI449) ) ;
	    }
	    ZI922 = ZI405;
	    goto ZL2_924;
	}
	/*UNREACHED*/
      case 35:
	{
	    EXP ZI449;
	    TYPE ZI396;
	    NAMESPACE ZI427;
	    IDENTIFIER ZI400;
	    EXP ZI405;

	    {

    (ZI449) = begin_field_exp ( lex_arrow, (ZI922), &(ZI396), &(ZI427) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR428 (ZI427, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = end_field_exp ( lex_arrow, (ZI449), (ZI396), (ZI427), (ZI400), 0 ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI922 = ZI405;
	    goto ZL2_924;
	}
	/*UNREACHED*/
      case 46:
	{
	    EXP ZI449;
	    TYPE ZI396;
	    NAMESPACE ZI427;
	    IDENTIFIER ZI400;
	    EXP ZI405;

	    {

    (ZI449) = begin_field_exp ( lex_dot, (ZI922), &(ZI396), &(ZI427) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR428 (ZI427, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = end_field_exp ( lex_dot, (ZI449), (ZI396), (ZI427), (ZI400), 0 ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI922 = ZI405;
	    goto ZL2_924;
	}
	/*UNREACHED*/
      default:
	{
	    ZI923 = ZI922;
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
    *ZO923 = ZI923;
}

void
ZR505(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI950;

	ZR503 (&ZI950);
	ZR952 (&ZI950, &ZI405);
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
    *ZO405 = ZI405;
}

void
ZR1053(IDENTIFIER *ZI400, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    BASE_TYPE ZI671;

	    {
 (ZI671) = btype_enum ; 
	    }
	    {

    MAKE_type_pre ( cv_none, (ZI671), qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (*ZI400) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
	    }
	}
	break;
      case 64:
	{
	    IDENTIFIER ZI421;
	    IDENTIFIER ZI674;

	    {

    (ZI421) = begin_enum_defn ( (*ZI400), NULL_type ) ;
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
	    ZR685 (&ZI421);
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

    (ZI674) = end_enum_defn ( (ZI421) ) ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI674) ) ;
    have_type_specifier = 1 ;
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
    *ZO396 = ZI396;
}

void
parse_type(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	parse_tok_type (&ZI396);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    object_type ( (ZI396), null_tag ) ;
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

    (ZI396) = NULL_type ;
	}
    }
  ZL0:;
    *ZO396 = ZI396;
}

void
ZR838(OFFSET ZI449, TYPE ZI570, OFFSET *ZO849, TYPE *ZO850)
{
    OFFSET ZI849;
    TYPE ZI850;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_838:;
    {
	OFFSET ZI417;
	TYPE ZI396;

	ZR837 (ZI449, ZI570, &ZI417, &ZI396);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZI449 = ZI417;
		    ZI570 = ZI396;
		    goto ZL2_838;
		}
		/*UNREACHED*/
	      default:
		{
		    ZI849 = ZI417;
		    ZI850 = ZI396;
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO849 = ZI849;
    *ZO850 = ZI850;
}

void
ZR807(EXP *ZO875)
{
    EXP ZI875;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	EXP ZI421;

	switch (CURRENT_TERMINAL) {
	  case 26:
	    {

    ZI468 = crt_token->pp_data.exp ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZI468), c ) ;
    (ZI421) = c ;
	}
	{

    target_decl ( lex_if, (ZI468) ) ;
	}
	ZR806 ();
	ZR876 (ZI421, &ZI875);
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
    *ZO875 = ZI875;
}

void
ZR659(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 104:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 4:
		{
		    IDENTIFIER ZI400;

		    {
			switch (CURRENT_TERMINAL) {
			  case 1:
			    {
				{

    ZI400 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    ZI400 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    ZI400 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  default:
			    goto ZL1;
			}
		    }
		    ZR1053 (&ZI400, &ZI396);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 64:
		{
		    IDENTIFIER ZI400;
		    IDENTIFIER ZI421;
		    IDENTIFIER ZI674;

		    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
		    }
		    {

    (ZI421) = begin_enum_defn ( (ZI400), NULL_type ) ;
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
		    ZR685 (&ZI421);
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

    (ZI674) = end_enum_defn ( (ZI421) ) ;
		    }
		    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI674) ) ;
    have_type_specifier = 1 ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
}

void
ZR744(TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4: case 65:
	{
	    ZR753 (&ZI396, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI421;
	    TYPE ZI424;

	    ZR733 (&ZI421);
	    ZR744 (&ZI424, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 0 ) ) ;
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
    *ZO396 = ZI396;
    *ZO400 = ZI400;
}

void
ZR484(EXP *ZO911)
{
    EXP ZI911;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR481 (&ZI405);
	ZR912 (ZI405, &ZI911);
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
    *ZO911 = ZI911;
}

void
ZR601(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;
	EXP ZI449;

	ZR617 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI449) = bind_temporary ( (ZI417) ) ;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI449), (ZI405) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 77:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR1057(TYPE *ZI1055, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 332:
	{
	    TYPE ZI424;

	    ZR755 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (*ZI1055) : inject_pre_type ( (ZI424), (*ZI1055), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI396 = *ZI1055;
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
    *ZO396 = ZI396;
}

void
ZR680(IDENTIFIER ZI405)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI400;
	EXP ZI468;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 36:
		{
		    ADVANCE_LEXER;
		    ZR520 (&ZI468);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI468) = NULL_exp ;
		    }
		}
		break;
	    }
	}
	{

    IGNORE make_enumerator ( (ZI405), (ZI400), (ZI468) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR754(TYPE ZI421, TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI424;

	ZR744 (&ZI424, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
    *ZO400 = ZI400;
}

void
ZR794(IDENTIFIER ZI549, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR790 (ZI549, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI405) = NULL_exp ;
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
    *ZO405 = ZI405;
}

void
parse_file(TYPE ZI396, DECL_SPEC ZI607)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI939;
	TYPE ZI940;
	CV_SPEC ZI941;
	DECL_SPEC ZI942;
	BASE_TYPE ZI943;
	TYPE ZI944;
	CV_SPEC ZI945;
	DECL_SPEC ZI946;
	EXP ZI405;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR716 (&ZI939, &ZI940, &ZI941, &ZI942);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	ZR726 (&ZI939, &ZI940, &ZI941, &ZI942, &ZI943, &ZI944, &ZI945, &ZI946);
	ZR947 (&ZI943, &ZI944, &ZI945, &ZI946, &ZI405);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    external_declaration ( (ZI405), 1 ) ;
	}
	ZR805 ();
	switch (CURRENT_TERMINAL) {
	  case 32:
	    break;
	  case 355:
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
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_dcl_dcl_semicolon () ) ;
	    }
	    ZR805 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 126:
	{
	    EXP ZI405;

	    ZR625 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI405), 1 ) ;
	    }
	    ZR805 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 26: case 30:
	{
	    ZR808 ();
	    ZR805 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    BASE_TYPE ZI660;
	    TYPE ZI691;
	    CV_SPEC ZI632;
	    DECL_SPEC ZI718;
	    TYPE ZI948;
	    DECL_SPEC ZI949;
	    TYPE ZI570;
	    IDENTIFIER ZI400;
	    EXP ZI405;

	    {
 (ZI660) = btype_none ; 
	    }
	    {

    (ZI691) = NULL_type ;
	    }
	    {
 (ZI632) = cv_none ; 
	    }
	    {
 (ZI718) = dspec_none ; 
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI949) = complete_dspec ( (ZI718), (ZI660), (ZI691), (ZI632) ) ;
    (ZI948) = complete_pre_type ( (ZI660), (ZI691), (ZI632), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR754 (ZI948, &ZI570, &ZI400);
	    ZR821 (&ZI660, &ZI948, &ZI949, &ZI570, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = NULL_exp ;
	    }
	    {

    external_declaration ( (ZI405), 1 ) ;
	    }
	    ZR805 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 355:
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
ZR1058(TYPE *ZO861)
{
    TYPE ZI861;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 332:
	{
	    TYPE ZI396;

	    ZR755 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI396) ) ) {
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
	    ZR862 (ZI396, &ZI861);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 25: case 39: case 47: case 94:
      case 97: case 98: case 102: case 104: case 105:
      case 106: case 110: case 111: case 112: case 114:
      case 115: case 117: case 118: case 120: case 121:
      case 122: case 123: case 124: case 137: case 156:
      case 185: case 286: case 299:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI570;
	    TYPE ZI396;

	    {

    (ZI400) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI400) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR757 (&ZI570);
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
	    ZI396 = ZI570;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR862 (ZI396, &ZI861);
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
    *ZO861 = ZI861;
}

void
parse_offset(OFFSET ZI449, TYPE ZI570, OFFSET *ZO417, TYPE *ZO396)
{
    OFFSET ZI417;
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	OFFSET ZI468;
	TYPE ZI839;

	ZR836 (ZI449, ZI570, &ZI468, &ZI839);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZR838 (ZI468, ZI839, &ZI417, &ZI396);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    ZI417 = ZI468;
		    ZI396 = ZI839;
		}
		break;
	      case 355:
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
	ZI417 = ZI449;
	ZI396 = ZI570;
    }
  ZL0:;
    *ZO417 = ZI417;
    *ZO396 = ZI396;
}

void
parse_nat(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR520 (&ZI405);
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

    (ZI405) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR518(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR420 (&ZI405);
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
    *ZO405 = ZI405;
}

void
parse_param(TYPE ZI570, int ZI421, IDENTIFIER *ZO549)
{
    IDENTIFIER ZI549;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR772 (&ZI549);
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

    (ZI549) = NULL_id ;
	}
    }
  ZL0:;
    *ZO549 = ZI549;
}

void
ZR689(BASE_TYPE *ZO660, TYPE *ZO396, CV_SPEC *ZO632)
{
    BASE_TYPE ZI660;
    TYPE ZI396;
    CV_SPEC ZI632;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI690;
	TYPE ZI691;
	CV_SPEC ZI692;

	ZR688 (&ZI690, &ZI691, &ZI692);
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 25: case 97: case 98: case 102:
	      case 104: case 106: case 110: case 111: case 114:
	      case 115: case 118: case 121: case 122: case 123:
	      case 124: case 156: case 185: case 286: case 299:
		{
		    BASE_TYPE ZI694;
		    TYPE ZI695;
		    CV_SPEC ZI696;

		    ZR689 (&ZI694, &ZI695, &ZI696);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI690) & (ZI694) ) {
	(ZI660) = join_pre_types ( (ZI690), (ZI694) ) ;
    } else {
	(ZI660) = ( (ZI690) | (ZI694) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI691) ) ) {
	(ZI396) = (ZI695) ;
    } else if ( IS_NULL_type ( (ZI695) ) ) {
	(ZI396) = (ZI691) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI691), (ZI695) ) ) ;
	(ZI396) = (ZI695) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI692) & (ZI696) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI632) = ( (ZI692) | (ZI696) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI660 = ZI690;
		    ZI396 = ZI691;
		    ZI632 = ZI692;
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO660 = ZI660;
    *ZO396 = ZI396;
    *ZO632 = ZI632;
}

void
ZR935(EXP ZI929, EXP ZI930, int ZI931, EXP *ZO932, EXP *ZO933, int *ZO934)
{
    EXP ZI932;
    EXP ZI933;
    int ZI934;

  ZL2_935:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI421;
	    int ZI539;
	    EXP ZI468;
	    int ZI570;
	    EXP ZI449;
	    EXP ZI405;

	    ZI421 = ZI930;
	    ZI539 = ZI931;
	    {

    ZI468 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI468), c ) ;
	    }
	    {

    (ZI570) = unreached_code ;
    if ( (ZI570) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR553 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI539) ; 
	    }
	    {

    (ZI405) = cont_hash_if_stmt ( (ZI929), (ZI468), (ZI449) ) ;
	    }
	    ZI929 = ZI405;
	    ZI930 = ZI421;
	    ZI931 = ZI539;
	    goto ZL2_935;
	}
	/*UNREACHED*/
      default:
	{
	    ZI932 = ZI929;
	    ZI933 = ZI930;
	    ZI934 = ZI931;
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
    *ZO932 = ZI932;
    *ZO933 = ZI933;
    *ZO934 = ZI934;
}

void
parse_func(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR554 (&ZI405);
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

    (ZI405) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR755(TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    ZR761 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1055;

	    ZR733 (&ZI1055);
	    ZR1057 (&ZI1055, &ZI396);
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
    *ZO396 = ZI396;
}

void
ZR711(DECL_SPEC *ZO607)
{
    DECL_SPEC ZI607;

    switch (CURRENT_TERMINAL) {
      case 94:
	{
	    ADVANCE_LEXER;
	    {
 (ZI607) = dspec_auto ; 
	    }
	}
	break;
      case 105:
	{
	    ADVANCE_LEXER;
	    {
 (ZI607) = dspec_extern ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (ZI607) = dspec_inline ; 
	    }
	}
	break;
      case 112:
	{
	    ADVANCE_LEXER;
	    {
 (ZI607) = dspec_register ; 
	    }
	}
	break;
      case 117:
	{
	    ADVANCE_LEXER;
	    {
 (ZI607) = dspec_static ; 
	    }
	}
	break;
      case 120:
	{
	    ADVANCE_LEXER;
	    {
 (ZI607) = dspec_typedef ; 
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
    *ZO607 = ZI607;
}

void
ZR746(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI400;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	{

    IGNORE weak_param_decl ( (ZI400) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	ZR780 ();
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
ZR685(IDENTIFIER *ZI421)
{
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4:
	{
	    ZR682 (*ZI421);
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
parse_id(IDENTIFIER *ZO400)
{
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
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
	{

    (ZI400) = NULL_id ;
	}
    }
  ZL0:;
    *ZO400 = ZI400;
}

void
ZR460(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI461;

	    ADVANCE_LEXER;
	    {
 (ZI461) = lex_alignof ; 
	    }
	    ZR462 (ZI461, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI964;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI964 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR924 (ZI964, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 206:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_cast_exp ( type_void, (ZI417), 0 ) ;
	    }
	}
	break;
      case 210:
	{
	    EXP ZI964;

	    ADVANCE_LEXER;
	    {

    (ZI964) = make_ellipsis_exp () ;
	    }
	    ZR924 (ZI964, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI400;
	    EXP ZI964;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI964) = make_id_exp ( (ZI400) ) ;
	    }
	    ZR924 (ZI964, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 255:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_lit_exp ( (ZI417) ) ;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR459 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_prefix_exp ( lex_minus_Hminus, (ZI417) ) ;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR965 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR459 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_prefix_exp ( lex_plus_Hplus, (ZI417) ) ;
	    }
	}
	break;
      case 116:
	{
	    int ZI461;

	    ADVANCE_LEXER;
	    {
 (ZI461) = lex_sizeof ; 
	    }
	    ZR462 (ZI461, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_indir_exp ( (ZI417) ) ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI417;

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
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_ref_exp ( (ZI417), 0 ) ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    EXP ZI964;

	    ZR410 (&ZI964);
	    ZR924 (ZI964, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI417;

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
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_not_exp ( (ZI417) ) ;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI461;
	    EXP ZI417;

	    {
 (ZI461) = crt_lex_token ; 
	    }
	    ZR470 ();
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_uminus_exp ( (ZI461), (ZI417) ) ;
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
    *ZO405 = ZI405;
}

void
ZR662(BASE_TYPE *ZO660, TYPE *ZO396)
{
    BASE_TYPE ZI660;
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI396 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_none ; 
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI400;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI400) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI660) = btype_none ; 
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 156:
      case 185: case 286: case 299:
	{
	    ZR661 (&ZI660);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	}
	break;
      case 118: case 121:
	{
	    ZR658 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI660) = btype_none ; 
	    }
	}
	break;
      case 104:
	{
	    ZR659 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI660) = btype_none ; 
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
    *ZO660 = ZI660;
    *ZO396 = ZI396;
}

void
ZR762(TYPE ZI421, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 332:
	{
	    TYPE ZI424;

	    ZR755 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI396 = ZI421;
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
    *ZO396 = ZI396;
}

void
ZR1069(int *ZI461, int *ZI463, int *ZI464, EXP *ZO468)
{
    EXP ZI468;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	int ZI467;
	EXP ZI417;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR445 (&ZI396, &ZI467);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI417) = NULL_exp ;
	}
	{

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (*ZI461) ) ;
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
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255: case 298: case 324:
      case 346:
	{
	    EXP ZI1068;
	    EXP ZI405;
	    EXP ZI417;
	    int ZI466;
	    int ZI467;
	    TYPE ZI396;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI1068);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_paren_exp ( (ZI1068) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR924 (ZI405, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI466) = no_side_effects - (*ZI463) ;
	    }
	    {

    (ZI467) = no_type_defns - (*ZI464) ;
	    }
	    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (*ZI461) ) ;
	    }
	    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (*ZI461) ) ;
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
    *ZO468 = ZI468;
}

void
ZR815(BASE_TYPE *ZI660, TYPE *ZI691, CV_SPEC *ZI632, DECL_SPEC *ZI718)
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    IGNORE empty_decl ( (*ZI718), NULL_type, (*ZI660), (*ZI691), (*ZI632), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    TYPE ZI396;
	    DECL_SPEC ZI607;

	    {

    /* Complete a declaration specifier and a type */
    (ZI607) = complete_dspec ( (*ZI718), (*ZI660), (*ZI691), (*ZI632) ) ;
    (ZI396) = complete_pre_type ( (*ZI660), (*ZI691), (*ZI632), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR799 (ZI607, *ZI660, ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 355:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR395(void)
{
    if ((CURRENT_TERMINAL) == 355) {
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
	int ZI396;

	{
 (ZI396) = lex_open_Hround ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI396) ) report ( crt_loc, ERR_lex_expect ( (ZI396) ) ) ;
	}
    }
}

void
ZR682(IDENTIFIER ZI405)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_682:;
    {
	ZR680 (ZI405);
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
				goto ZL2_682;
			    }
			    /*UNREACHED*/
			  case 1: case 2: case 4:
			    {
				goto ZL2_682;
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
ZR600(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR538 (&ZI405);
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
    *ZO405 = ZI405;
}

void
ZR837(OFFSET ZI449, TYPE ZI570, OFFSET *ZO417, TYPE *ZO396)
{
    OFFSET ZI417;
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    ADVANCE_LEXER;
	    ZR836 (ZI449, ZI570, &ZI417, &ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;

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
	    ZR520 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    OFFSET off = offset_index ( (ZI570), (ZI405), &(ZI396) ) ;
    (ZI417) = offset_add ( (ZI449), off ) ;
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
    *ZO417 = ZI417;
    *ZO396 = ZI396;
}

void
ZR459(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI461;

	    ADVANCE_LEXER;
	    {
 (ZI461) = lex_alignof ; 
	    }
	    ZR462 (ZI461, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR459 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_prefix_exp ( lex_minus_Hminus, (ZI417) ) ;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR459 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_prefix_exp ( lex_plus_Hplus, (ZI417) ) ;
	    }
	}
	break;
      case 116:
	{
	    int ZI461;

	    ADVANCE_LEXER;
	    {
 (ZI461) = lex_sizeof ; 
	    }
	    ZR462 (ZI461, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_indir_exp ( (ZI417) ) ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI417;

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
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_ref_exp ( (ZI417), 0 ) ;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI417;

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
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_not_exp ( (ZI417) ) ;
	    }
	}
	break;
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 65: case 210:
	{
	    ZR448 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI461;
	    EXP ZI417;

	    {
 (ZI461) = crt_lex_token ; 
	    }
	    ZR470 ();
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_uminus_exp ( (ZI461), (ZI417) ) ;
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
    *ZO405 = ZI405;
}

void
ZR487(EXP *ZO907)
{
    EXP ZI907;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR484 (&ZI405);
	ZR908 (ZI405, &ZI907);
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
    *ZO907 = ZI907;
}

void
ZR1074(IDENTIFIER *ZI549, SID_LIST_EXP *ZO424)
{
    SID_LIST_EXP ZI424;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 64: case 65:
      case 69: case 71: case 78: case 85: case 116:
      case 170: case 206: case 210: case 255:
	{
	    ZR791 (*ZI549, &ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI424) = NULL_list ( EXP ) ;
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
    *ZO424 = ZI424;
}

void
ZR947(BASE_TYPE *ZI943, TYPE *ZI944, CV_SPEC *ZI945, DECL_SPEC *ZI946, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI946), NULL_type, (*ZI943), (*ZI944), (*ZI945), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI405) = NULL_exp ;
	    }
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    TYPE ZI396;
	    DECL_SPEC ZI607;
	    TYPE ZI570;
	    IDENTIFIER ZI400;

	    {

    /* Complete a declaration specifier and a type */
    (ZI607) = complete_dspec ( (*ZI946), (*ZI943), (*ZI944), (*ZI945) ) ;
    (ZI396) = complete_pre_type ( (*ZI943), (*ZI944), (*ZI945), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR754 (ZI396, &ZI570, &ZI400);
	    ZR821 (ZI943, &ZI396, &ZI607, &ZI570, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = NULL_exp ;
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
    *ZO405 = ZI405;
}

void
ZR603(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255: case 298: case 324:
      case 346:
	{
	    EXP ZI417;
	    EXP ZI449;

	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI449) = make_exp_stmt ( (ZI417) ) ;
	    }
	    {

    (ZI405) = bind_temporary ( (ZI449) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI405) = NULL_exp ;
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
    *ZO405 = ZI405;
}

void
ZR821(BASE_TYPE *ZI660, TYPE *ZI396, DECL_SPEC *ZI607, TYPE *ZI570, IDENTIFIER *ZI400)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI549;
	int ZI449;
	EXP ZI417;

	{

    (ZI0) = function_params ( (*ZI570) ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI549) = make_func_decl ( (*ZI607), (*ZI570), (*ZI400), 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	{

    (ZI449) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (ZI549) ) ;
	}
	ZR554 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IGNORE end_function ( (ZI549), (ZI417) ) ;
    in_class_defn = (ZI449) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
	}
	{

    RESCAN_LEXER ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 36: case 42: case 77:
	{
	    IDENTIFIER ZI549;
	    EXP ZI417;

	    {

    if ( in_weak_param ) {
	(ZI549) = make_param_decl ( (*ZI607), (*ZI570), (*ZI400), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (*ZI570) ) == type_func_tag ) {
	check_weak_func ( (*ZI570), 0 ) ;
	(ZI549) = make_func_decl ( (*ZI607), (*ZI570), (*ZI400), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZI549) = make_object_decl ( (*ZI607), (*ZI570), (*ZI400), def ) ;
    }
    if ( IS_id_type_alias ( (ZI549) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI549) ) ) ;
	bs |= (*ZI660) ;
	COPY_btype ( id_type_alias_rep ( (ZI549) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR794 (ZI549, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = init_object ( (ZI549), (ZI417) ) ;
    if ( do_dump ) dump_declare ( (ZI549), &decl_loc, def ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			ZR799 (*ZI607, *ZI660, *ZI396);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    break;
		}
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
ZR495(EXP *ZO895)
{
    EXP ZI895;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR493 (&ZI405);
	ZR896 (ZI405, &ZI895);
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
    *ZO895 = ZI895;
}

void
parse_exp(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR420 (&ZI405);
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

    (ZI405) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR688(BASE_TYPE *ZO660, TYPE *ZO396, CV_SPEC *ZO632)
{
    BASE_TYPE ZI660;
    TYPE ZI396;
    CV_SPEC ZI632;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR633 (&ZI632);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI660) = btype_none ; 
	    }
	    {

    (ZI396) = NULL_type ;
	    }
	}
	break;
      case 2: case 25: case 97: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 156:
      case 185: case 286: case 299:
	{
	    ZR662 (&ZI660, &ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI632) = cv_none ; 
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
    *ZO660 = ZI660;
    *ZO396 = ZI396;
    *ZO632 = ZI632;
}

void
ZR1077(EXP *ZI1075, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255: case 298: case 324:
      case 346:
	{
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;

	    ZR517 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1075), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI405) = make_comma_exp ( (ZI421) ) ;
	    }
	}
	break;
      default:
	{
	    ZI405 = *ZI1075;
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
    *ZO405 = ZI405;
}

void
ZR952(EXP *ZI950, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 72:
	{
	    EXP ZI417;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    ZR415 (&ZI417);
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
	    ZR505 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_cond_exp ( (*ZI950), (ZI417), (ZI449) ) ;
	    }
	}
	break;
      default:
	{
	    ZI405 = *ZI950;
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
    *ZO405 = ZI405;
}

void
ZR1080(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI1093;
	    EXP ZI1094;

	    ADVANCE_LEXER;
	    ZR415 (&ZI1093);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1094) = make_set_exp ( (ZI1093) ) ;
	    }
	    ZR1095 (&ZI1094, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 324:
	{
	    EXP ZI1090;
	    EXP ZI1091;

	    ADVANCE_LEXER;
	    ZR415 (&ZI1090);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1091) = make_unused_exp ( (ZI1090) ) ;
	    }
	    ZR1095 (&ZI1091, &ZI405);
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
    *ZO405 = ZI405;
}

void
parse_stmt(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR530 (&ZI405);
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

    (ZI405) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR827(TYPE ZI421, BASE_TYPE ZI424)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_827:;
    {
	ZR826 (ZI421, ZI424);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_827;
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
ZR1081(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI468;
	    EXP ZI417;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    ZR520 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI417) = begin_case_stmt ( (ZI468), 0 ) ;
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
	    ZR530 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = end_case_stmt ( (ZI417), (ZI449) ) ;
	    }
	}
	break;
      case 100:
	{
	    EXP ZI417;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    {

    (ZI417) = begin_default_stmt ( 0 ) ;
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
	    ZR530 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = end_default_stmt ( (ZI417), (ZI449) ) ;
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
    *ZO405 = ZI405;
}

void
ZR445(TYPE *ZO396, int *ZO474)
{
    TYPE ZI396;
    int ZI474;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI463;
	BASE_TYPE ZI660;
	TYPE ZI421;
	CV_SPEC ZI632;
	TYPE ZI424;

	{

    (ZI463) = no_type_defns ;
	}
	ZR689 (&ZI660, &ZI421, &ZI632);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI424) = complete_pre_type ( (ZI660), (ZI421), (ZI632), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR762 (ZI424, &ZI396);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI474) = no_type_defns - (ZI463) ;
	}
	{

    object_type ( (ZI396), null_tag ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
    *ZO474 = ZI474;
}

void
ZR512(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_set_exp ( (ZI417) ) ;
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
	    EXP ZI417;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_unused_exp ( (ZI417) ) ;
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
    *ZO405 = ZI405;
}

void
ZR701(BASE_TYPE *ZI690, TYPE *ZI691, CV_SPEC *ZI692, BASE_TYPE *ZO660, TYPE *ZO396, CV_SPEC *ZO632)
{
    BASE_TYPE ZI660;
    TYPE ZI396;
    CV_SPEC ZI632;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1030;
	TYPE ZI1031;
	CV_SPEC ZI1032;
	BASE_TYPE ZI694;
	TYPE ZI695;
	CV_SPEC ZI696;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR688 (&ZI1030, &ZI1031, &ZI1032);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	ZR701 (&ZI1030, &ZI1031, &ZI1032, &ZI694, &ZI695, &ZI696);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI690) & (ZI694) ) {
	(ZI660) = join_pre_types ( (*ZI690), (ZI694) ) ;
    } else {
	(ZI660) = ( (*ZI690) | (ZI694) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI691) ) ) {
	(ZI396) = (ZI695) ;
    } else if ( IS_NULL_type ( (ZI695) ) ) {
	(ZI396) = (*ZI691) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI691), (ZI695) ) ) ;
	(ZI396) = (ZI695) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI692) & (ZI696) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI632) = ( (*ZI692) | (ZI696) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI660 = *ZI690;
	    ZI396 = *ZI691;
	    ZI632 = *ZI692;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO660 = ZI660;
    *ZO396 = ZI396;
    *ZO632 = ZI632;
}

void
ZR806(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI607;
	TYPE ZI396;

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
 (ZI607) = dspec_none ; 
	}
	{

    (ZI396) = NULL_type ;
	}
	ZR805 ();
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
ZR1084(IDENTIFIER *ZI400, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 33: case 34: case 35: case 36: case 42:
      case 44: case 45: case 46: case 48: case 49:
      case 50: case 53: case 54: case 55: case 56:
      case 57: case 58: case 59: case 60: case 61:
      case 63: case 65: case 66: case 67: case 68:
      case 69: case 70: case 71: case 72: case 73:
      case 74: case 75: case 76: case 77: case 78:
      case 79: case 80: case 81: case 86: case 87:
	{
	    EXP ZI1014;
	    EXP ZI1015;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    {

    (ZI1014) = make_id_exp ( (*ZI400) ) ;
	    }
	    ZR924 (ZI1014, &ZI1015);
	    ZR1013 (&ZI1015, &ZI1023);
	    ZR1025 (&ZI1023, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_exp_stmt ( (ZI417) ) ;
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
	    EXP ZI417;
	    EXP ZI449;

	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI417) = begin_label_stmt ( (*ZI400), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR530 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = end_label_stmt ( (ZI417), (ZI449) ) ;
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
    *ZO405 = ZI405;
}

void
ZR1085(IDENTIFIER *ZI400, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    EXP ZI417;

	    {

    (ZI417) = make_id_exp ( (*ZI400) ) ;
	    }
	    {

    (ZI405) = make_exp_stmt ( (ZI417) ) ;
	    }
	}
	break;
      case 41:
	{
	    EXP ZI417;
	    EXP ZI449;

	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI417) = begin_label_stmt ( (*ZI400), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR530 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = end_label_stmt ( (ZI417), (ZI449) ) ;
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
    *ZO405 = ZI405;
}

void
ZR422(SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;
	SID_LIST_EXP ZI424;

	ZR420 (&ZI405);
	ZR626 (&ZI424);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    CONS_exp ( (ZI405), (ZI424), (ZI421) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO421 = ZI421;
}

void
ZR420(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI1008;
	    EXP ZI1009;

	    ADVANCE_LEXER;
	    {
 (ZI1008) = lex_alignof ; 
	    }
	    ZR462 (ZI1008, &ZI1009);
	    ZR1013 (&ZI1009, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1020;
	    EXP ZI1021;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1020 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR924 (ZI1020, &ZI1021);
	    ZR1013 (&ZI1021, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 206:
	{
	    EXP ZI417;
	    EXP ZI963;
	    EXP ZI962;
	    EXP ZI961;
	    EXP ZI960;
	    EXP ZI959;
	    EXP ZI958;
	    EXP ZI957;
	    EXP ZI956;
	    EXP ZI955;
	    EXP ZI954;
	    EXP ZI953;
	    EXP ZI950;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI963) = make_cast_exp ( type_void, (ZI417), 0 ) ;
	    }
	    ZR920 (ZI963, &ZI962);
	    ZR916 (ZI962, &ZI961);
	    ZR912 (ZI961, &ZI960);
	    ZR908 (ZI960, &ZI959);
	    ZR904 (ZI959, &ZI958);
	    ZR900 (ZI958, &ZI957);
	    ZR896 (ZI957, &ZI956);
	    ZR892 (ZI956, &ZI955);
	    ZR888 (ZI955, &ZI954);
	    ZR884 (ZI954, &ZI953);
	    ZR880 (ZI953, &ZI950);
	    ZR952 (&ZI950, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 210:
	{
	    EXP ZI1017;
	    EXP ZI1018;

	    ADVANCE_LEXER;
	    {

    (ZI1017) = make_ellipsis_exp () ;
	    }
	    ZR924 (ZI1017, &ZI1018);
	    ZR1013 (&ZI1018, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI400;
	    EXP ZI1014;
	    EXP ZI1015;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1014) = make_id_exp ( (ZI400) ) ;
	    }
	    ZR924 (ZI1014, &ZI1015);
	    ZR1013 (&ZI1015, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 255:
	{
	    EXP ZI417;
	    EXP ZI963;
	    EXP ZI962;
	    EXP ZI961;
	    EXP ZI960;
	    EXP ZI959;
	    EXP ZI958;
	    EXP ZI957;
	    EXP ZI956;
	    EXP ZI955;
	    EXP ZI954;
	    EXP ZI953;
	    EXP ZI950;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI963) = make_lit_exp ( (ZI417) ) ;
	    }
	    ZR920 (ZI963, &ZI962);
	    ZR916 (ZI962, &ZI961);
	    ZR912 (ZI961, &ZI960);
	    ZR908 (ZI960, &ZI959);
	    ZR904 (ZI959, &ZI958);
	    ZR900 (ZI958, &ZI957);
	    ZR896 (ZI957, &ZI956);
	    ZR892 (ZI956, &ZI955);
	    ZR888 (ZI955, &ZI954);
	    ZR884 (ZI954, &ZI953);
	    ZR880 (ZI953, &ZI950);
	    ZR952 (&ZI950, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI989;
	    EXP ZI990;

	    ADVANCE_LEXER;
	    ZR459 (&ZI989);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI990) = make_prefix_exp ( lex_minus_Hminus, (ZI989) ) ;
	    }
	    ZR1013 (&ZI990, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR985 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI986;
	    EXP ZI987;

	    ADVANCE_LEXER;
	    ZR459 (&ZI986);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI987) = make_prefix_exp ( lex_plus_Hplus, (ZI986) ) ;
	    }
	    ZR1013 (&ZI987, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 116:
	{
	    int ZI1005;
	    EXP ZI1006;

	    ADVANCE_LEXER;
	    {
 (ZI1005) = lex_sizeof ; 
	    }
	    ZR462 (ZI1005, &ZI1006);
	    ZR1013 (&ZI1006, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI992;
	    EXP ZI993;

	    ADVANCE_LEXER;
	    ZR460 (&ZI992);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI993) = make_indir_exp ( (ZI992) ) ;
	    }
	    ZR1013 (&ZI993, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI995;
	    EXP ZI996;

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
	    ZR460 (&ZI995);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI996) = make_ref_exp ( (ZI995), 0 ) ;
	    }
	    ZR1013 (&ZI996, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    EXP ZI1011;
	    EXP ZI1012;

	    ZR410 (&ZI1011);
	    ZR924 (ZI1011, &ZI1012);
	    ZR1013 (&ZI1012, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI998;
	    EXP ZI999;

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
	    ZR460 (&ZI998);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI999) = make_not_exp ( (ZI998) ) ;
	    }
	    ZR1013 (&ZI999, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI1001;
	    EXP ZI1002;
	    EXP ZI1003;

	    {
 (ZI1001) = crt_lex_token ; 
	    }
	    ZR470 ();
	    ZR460 (&ZI1002);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1003) = make_uminus_exp ( (ZI1001), (ZI1002) ) ;
	    }
	    ZR1013 (&ZI1003, &ZI405);
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
    *ZO405 = ZI405;
}

void
ZR425(SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 255:
	{
	    ZR422 (&ZI421);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI421) = NULL_list ( EXP ) ;
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
    *ZO421 = ZI421;
}

void
ZR501(EXP *ZO883)
{
    EXP ZI883;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR499 (&ZI405);
	ZR884 (ZI405, &ZI883);
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
    *ZO883 = ZI883;
}

void
ZR616(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 95:
	{
	    int ZI539;

	    ADVANCE_LEXER;
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_break_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR397 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 99:
	{
	    int ZI539;

	    ADVANCE_LEXER;
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI405) = make_continue_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR397 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 108:
	{
	    int ZI539;

	    ADVANCE_LEXER;
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR615 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR397 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 113:
	{
	    int ZI539;
	    EXP ZI417;

	    ADVANCE_LEXER;
	    {

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR617 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_return_stmt ( (ZI417), lex_return ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR397 ();
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
    *ZO405 = ZI405;
}

void
ZR569(EXP *ZO932, EXP *ZO933, int *ZO934)
{
    EXP ZI932;
    EXP ZI933;
    int ZI934;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	EXP ZI421;
	int ZI539;
	EXP ZI417;
	EXP ZI405;

	switch (CURRENT_TERMINAL) {
	  case 26:
	    {

    ZI468 = crt_token->pp_data.exp ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZI468), c ) ;
    (ZI421) = c ;
	}
	{

    (ZI539) = unreached_code ;
    if ( (ZI539) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	}
	ZR553 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI539) ; 
	}
	{

    (ZI405) = begin_hash_if_stmt ( (ZI468), (ZI417) ) ;
	}
	ZR935 (ZI405, ZI421, ZI539, &ZI932, &ZI933, &ZI934);
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
    *ZO932 = ZI932;
    *ZO933 = ZI933;
    *ZO934 = ZI934;
}

void
ZR634(CV_SPEC *ZO632)
{
    CV_SPEC ZI632;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	CV_SPEC ZI417;

	ZR633 (&ZI417);
	{
	    switch (CURRENT_TERMINAL) {
	      case 98: case 124:
		{
		    CV_SPEC ZI449;

		    ZR634 (&ZI449);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    CV_SPEC c = ( (ZI417) & (ZI449) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI632) = ( (ZI417) | (ZI449) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI632 = ZI417;
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO632 = ZI632;
}

void
ZR554(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	int ZI549;
	EXP ZI449;
	EXP ZI539;
	EXP ZI417;

	{

    (ZI468) = begin_compound_stmt ( 1 ) ;
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

    COPY_int ( exp_sequence_block ( (ZI468) ), 2 ) ;
    (ZI549) = 1 ;
	}
	ZR550 (ZI468, ZI549, &ZI449);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI539) = fall_return_stmt () ;
	}
	{

    (ZI417) = add_compound_stmt ( (ZI449), (ZI539) ) ;
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

    (ZI405) = end_compound_stmt ( (ZI417) ) ;
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
    *ZO405 = ZI405;
}

/* END OF FILE */
