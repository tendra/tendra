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
ZR624(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;
	SID_LIST_EXP ZI421;

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

    ZI417 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    ZI417 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	ZR625 (&ZI421);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI405) = make_asm ( (ZI417), (ZI421) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR397 ();
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
ZR767(TYPE ZI421, TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1048;
	TYPE ZI1049;
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

    ZI1048 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI1048 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI1048 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI1049) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1048) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR857 (ZI1049, ZI1048, &ZI424, &ZI400);
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
	    ZR1047 (&ZI424, &ZI400);
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
	    IDENTIFIER ZI1046;
	    int ZI748;
	    TYPE ZI1052;
	    IDENTIFIER ZI1053;
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

    (ZI1046) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1046) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR759 (&ZI748);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1052) = make_func_type ( NULL_type, ( (ZI748) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
    (ZI1053) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1053) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR857 (ZI1052, ZI1053, &ZI424, &ZI400);
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
	    TYPE ZI1050;
	    IDENTIFIER ZI1051;
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
	    ZR758 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI405) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1050) ) ;
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
    (ZI1051) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1051) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR857 (ZI1050, ZI1051, &ZI424, &ZI400);
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
	    TYPE ZI1054;
	    TYPE ZI1055;
	    TYPE ZI424;

	    ZR732 (&ZI1054);
	    ZR765 (&ZI1055, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI424) = ( IS_NULL_type ( (ZI1055) ) ? (ZI1054) : inject_pre_type ( (ZI1055), (ZI1054), 0 ) ) ;
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
ZR504(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI949;

	ZR502 (&ZI949);
	ZR951 (&ZI949, &ZI405);
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
ZR837(OFFSET ZI449, TYPE ZI569, OFFSET *ZO848, TYPE *ZO849)
{
    OFFSET ZI848;
    TYPE ZI849;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_837:;
    {
	OFFSET ZI417;
	TYPE ZI396;

	ZR836 (ZI449, ZI569, &ZI417, &ZI396);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZI449 = ZI417;
		    ZI569 = ZI396;
		    goto ZL2_837;
		}
		/*UNREACHED*/
	      default:
		{
		    ZI848 = ZI417;
		    ZI849 = ZI396;
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
    *ZO848 = ZI848;
    *ZO849 = ZI849;
}

void
ZR806(EXP *ZO874)
{
    EXP ZI874;

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
	ZR805 ();
	ZR875 (ZI421, &ZI874);
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
    *ZO874 = ZI874;
}

void
ZR658(TYPE *ZO396)
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
		    ZR1056 (&ZI400, &ZI396);
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
		    IDENTIFIER ZI673;

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
		    ZR684 (&ZI421);
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

    (ZI673) = end_enum_defn ( (ZI421) ) ;
		    }
		    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI673) ) ;
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
ZR743(TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4: case 65:
	{
	    ZR752 (&ZI396, &ZI400);
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

	    ZR732 (&ZI421);
	    ZR743 (&ZI424, &ZI400);
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
ZR1056(IDENTIFIER *ZI400, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    BASE_TYPE ZI670;

	    {
 (ZI670) = btype_enum ; 
	    }
	    {

    MAKE_type_pre ( cv_none, (ZI670), qual_none, (ZI396) ) ;
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
	    IDENTIFIER ZI673;

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
	    ZR684 (&ZI421);
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

    (ZI673) = end_enum_defn ( (ZI421) ) ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI673) ) ;
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
ZR483(EXP *ZO910)
{
    EXP ZI910;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR480 (&ZI405);
	ZR911 (ZI405, &ZI910);
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
    *ZO910 = ZI910;
}

void
ZR600(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;
	EXP ZI449;

	ZR616 (&ZI417);
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
ZR679(IDENTIFIER ZI405)
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
		    ZR519 (&ZI468);
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
ZR753(TYPE ZI421, TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI424;

	ZR743 (&ZI424, &ZI400);
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
ZR793(IDENTIFIER ZI548, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR789 (ZI548, &ZI405);
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
parse_file(TYPE ZI396, DECL_SPEC ZI606)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI938;
	TYPE ZI939;
	CV_SPEC ZI940;
	DECL_SPEC ZI941;
	BASE_TYPE ZI942;
	TYPE ZI943;
	CV_SPEC ZI944;
	DECL_SPEC ZI945;
	EXP ZI405;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR715 (&ZI938, &ZI939, &ZI940, &ZI941);
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
	ZR725 (&ZI938, &ZI939, &ZI940, &ZI941, &ZI942, &ZI943, &ZI944, &ZI945);
	ZR946 (&ZI942, &ZI943, &ZI944, &ZI945, &ZI405);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    external_declaration ( (ZI405), 1 ) ;
	}
	ZR804 ();
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
	    ZR804 ();
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

	    ZR624 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI405), 1 ) ;
	    }
	    ZR804 ();
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
	    ZR807 ();
	    ZR804 ();
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
	    BASE_TYPE ZI659;
	    TYPE ZI690;
	    CV_SPEC ZI631;
	    DECL_SPEC ZI717;
	    TYPE ZI947;
	    DECL_SPEC ZI948;
	    TYPE ZI569;
	    IDENTIFIER ZI400;
	    EXP ZI405;

	    {
 (ZI659) = btype_none ; 
	    }
	    {

    (ZI690) = NULL_type ;
	    }
	    {
 (ZI631) = cv_none ; 
	    }
	    {
 (ZI717) = dspec_none ; 
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI948) = complete_dspec ( (ZI717), (ZI659), (ZI690), (ZI631) ) ;
    (ZI947) = complete_pre_type ( (ZI659), (ZI690), (ZI631), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR753 (ZI947, &ZI569, &ZI400);
	    ZR820 (&ZI659, &ZI947, &ZI948, &ZI569, &ZI400);
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
	    ZR804 ();
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
parse_offset(OFFSET ZI449, TYPE ZI569, OFFSET *ZO417, TYPE *ZO396)
{
    OFFSET ZI417;
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	OFFSET ZI468;
	TYPE ZI838;

	ZR835 (ZI449, ZI569, &ZI468, &ZI838);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZR837 (ZI468, ZI838, &ZI417, &ZI396);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    ZI417 = ZI468;
		    ZI396 = ZI838;
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
	ZI396 = ZI569;
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
	ZR519 (&ZI405);
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
ZR1060(TYPE *ZI1058, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 332:
	{
	    TYPE ZI424;

	    ZR754 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (*ZI1058) : inject_pre_type ( (ZI424), (*ZI1058), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI396 = *ZI1058;
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
ZR517(EXP *ZO405)
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
parse_param(TYPE ZI569, int ZI421, IDENTIFIER *ZO548)
{
    IDENTIFIER ZI548;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR771 (&ZI548);
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

    (ZI548) = NULL_id ;
	}
    }
  ZL0:;
    *ZO548 = ZI548;
}

void
ZR1061(TYPE *ZO860)
{
    TYPE ZI860;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 332:
	{
	    TYPE ZI396;

	    ZR754 (&ZI396);
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
	    ZR861 (ZI396, &ZI860);
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
	    TYPE ZI569;
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
	    ZR756 (&ZI569);
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
	    ZI396 = ZI569;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR861 (ZI396, &ZI860);
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
    *ZO860 = ZI860;
}

void
ZR934(EXP ZI928, EXP ZI929, int ZI930, EXP *ZO931, EXP *ZO932, int *ZO933)
{
    EXP ZI931;
    EXP ZI932;
    int ZI933;

  ZL2_934:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI421;
	    int ZI538;
	    EXP ZI468;
	    int ZI569;
	    EXP ZI449;
	    EXP ZI405;

	    ZI421 = ZI929;
	    ZI538 = ZI930;
	    {

    ZI468 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI468), c ) ;
	    }
	    {

    (ZI569) = unreached_code ;
    if ( (ZI569) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR552 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI538) ; 
	    }
	    {

    (ZI405) = cont_hash_if_stmt ( (ZI928), (ZI468), (ZI449) ) ;
	    }
	    ZI928 = ZI405;
	    ZI929 = ZI421;
	    ZI930 = ZI538;
	    goto ZL2_934;
	}
	/*UNREACHED*/
      default:
	{
	    ZI931 = ZI928;
	    ZI932 = ZI929;
	    ZI933 = ZI930;
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
    *ZO931 = ZI931;
    *ZO932 = ZI932;
    *ZO933 = ZI933;
}

void
ZR688(BASE_TYPE *ZO659, TYPE *ZO396, CV_SPEC *ZO631)
{
    BASE_TYPE ZI659;
    TYPE ZI396;
    CV_SPEC ZI631;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI689;
	TYPE ZI690;
	CV_SPEC ZI691;

	ZR687 (&ZI689, &ZI690, &ZI691);
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 25: case 97: case 98: case 102:
	      case 104: case 106: case 110: case 111: case 114:
	      case 115: case 118: case 121: case 122: case 123:
	      case 124: case 156: case 185: case 286: case 299:
		{
		    BASE_TYPE ZI693;
		    TYPE ZI694;
		    CV_SPEC ZI695;

		    ZR688 (&ZI693, &ZI694, &ZI695);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI689) & (ZI693) ) {
	(ZI659) = join_pre_types ( (ZI689), (ZI693) ) ;
    } else {
	(ZI659) = ( (ZI689) | (ZI693) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI690) ) ) {
	(ZI396) = (ZI694) ;
    } else if ( IS_NULL_type ( (ZI694) ) ) {
	(ZI396) = (ZI690) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI690), (ZI694) ) ) ;
	(ZI396) = (ZI694) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI691) & (ZI695) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI631) = ( (ZI691) | (ZI695) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI659 = ZI689;
		    ZI396 = ZI690;
		    ZI631 = ZI691;
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
    *ZO659 = ZI659;
    *ZO396 = ZI396;
    *ZO631 = ZI631;
}

void
parse_func(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR553 (&ZI405);
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
ZR754(TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 332:
	{
	    ZR760 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1058;

	    ZR732 (&ZI1058);
	    ZR1060 (&ZI1058, &ZI396);
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
ZR684(IDENTIFIER *ZI421)
{
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4:
	{
	    ZR681 (*ZI421);
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
ZR710(DECL_SPEC *ZO606)
{
    DECL_SPEC ZI606;

    switch (CURRENT_TERMINAL) {
      case 94:
	{
	    ADVANCE_LEXER;
	    {
 (ZI606) = dspec_auto ; 
	    }
	}
	break;
      case 105:
	{
	    ADVANCE_LEXER;
	    {
 (ZI606) = dspec_extern ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (ZI606) = dspec_inline ; 
	    }
	}
	break;
      case 112:
	{
	    ADVANCE_LEXER;
	    {
 (ZI606) = dspec_register ; 
	    }
	}
	break;
      case 117:
	{
	    ADVANCE_LEXER;
	    {
 (ZI606) = dspec_static ; 
	    }
	}
	break;
      case 120:
	{
	    ADVANCE_LEXER;
	    {
 (ZI606) = dspec_typedef ; 
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
    *ZO606 = ZI606;
}

void
ZR745(void)
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
	ZR779 ();
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
ZR814(BASE_TYPE *ZI659, TYPE *ZI690, CV_SPEC *ZI631, DECL_SPEC *ZI717)
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    IGNORE empty_decl ( (*ZI717), NULL_type, (*ZI659), (*ZI690), (*ZI631), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    TYPE ZI396;
	    DECL_SPEC ZI606;

	    {

    /* Complete a declaration specifier and a type */
    (ZI606) = complete_dspec ( (*ZI717), (*ZI659), (*ZI690), (*ZI631) ) ;
    (ZI396) = complete_pre_type ( (*ZI659), (*ZI690), (*ZI631), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR798 (ZI606, *ZI659, ZI396);
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
	    EXP ZI963;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI963 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR923 (ZI963, &ZI405);
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
	    EXP ZI963;

	    ADVANCE_LEXER;
	    {

    (ZI963) = make_ellipsis_exp () ;
	    }
	    ZR923 (ZI963, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI400;
	    EXP ZI963;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI963) = make_id_exp ( (ZI400) ) ;
	    }
	    ZR923 (ZI963, &ZI405);
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
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR964 (&ZI405);
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
	    EXP ZI963;

	    ZR410 (&ZI963);
	    ZR923 (ZI963, &ZI405);
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
ZR661(BASE_TYPE *ZO659, TYPE *ZO396)
{
    BASE_TYPE ZI659;
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
 (ZI659) = btype_none ; 
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
 (ZI659) = btype_none ; 
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 156:
      case 185: case 286: case 299:
	{
	    ZR660 (&ZI659);
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
	    ZR657 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI659) = btype_none ; 
	    }
	}
	break;
      case 104:
	{
	    ZR658 (&ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI659) = btype_none ; 
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
    *ZO659 = ZI659;
    *ZO396 = ZI396;
}

void
ZR761(TYPE ZI421, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 332:
	{
	    TYPE ZI424;

	    ZR754 (&ZI424);
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
ZR681(IDENTIFIER ZI405)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_681:;
    {
	ZR679 (ZI405);
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
				goto ZL2_681;
			    }
			    /*UNREACHED*/
			  case 1: case 2: case 4:
			    {
				goto ZL2_681;
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
ZR1072(int *ZI461, int *ZI463, int *ZI464, EXP *ZO468)
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
      case 206: case 210: case 298: case 324: case 346:
	{
	    EXP ZI1071;
	    EXP ZI405;
	    EXP ZI417;
	    int ZI466;
	    int ZI467;
	    TYPE ZI396;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI1071);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_paren_exp ( (ZI1071) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR923 (ZI405, &ZI417);
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
ZR599(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR537 (&ZI405);
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
ZR836(OFFSET ZI449, TYPE ZI569, OFFSET *ZO417, TYPE *ZO396)
{
    OFFSET ZI417;
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    ADVANCE_LEXER;
	    ZR835 (ZI449, ZI569, &ZI417, &ZI396);
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
	    ZR519 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    OFFSET off = offset_index ( (ZI569), (ZI405), &(ZI396) ) ;
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
ZR1073(IDENTIFIER *ZI548, SID_LIST_EXP *ZO424)
{
    SID_LIST_EXP ZI424;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 64: case 65:
      case 69: case 71: case 78: case 85: case 116:
      case 170: case 206: case 210:
	{
	    ZR790 (*ZI548, &ZI424);
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
ZR946(BASE_TYPE *ZI942, TYPE *ZI943, CV_SPEC *ZI944, DECL_SPEC *ZI945, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI945), NULL_type, (*ZI942), (*ZI943), (*ZI944), last_lex_token, 0 ) ;
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
	    DECL_SPEC ZI606;
	    TYPE ZI569;
	    IDENTIFIER ZI400;

	    {

    /* Complete a declaration specifier and a type */
    (ZI606) = complete_dspec ( (*ZI945), (*ZI942), (*ZI943), (*ZI944) ) ;
    (ZI396) = complete_pre_type ( (*ZI942), (*ZI943), (*ZI944), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR753 (ZI396, &ZI569, &ZI400);
	    ZR820 (ZI942, &ZI396, &ZI606, &ZI569, &ZI400);
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
ZR486(EXP *ZO906)
{
    EXP ZI906;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR483 (&ZI405);
	ZR907 (ZI405, &ZI906);
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
    *ZO906 = ZI906;
}

void
ZR820(BASE_TYPE *ZI659, TYPE *ZI396, DECL_SPEC *ZI606, TYPE *ZI569, IDENTIFIER *ZI400)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI548;
	int ZI449;
	EXP ZI417;

	{

    (ZI0) = function_params ( (*ZI569) ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI548) = make_func_decl ( (*ZI606), (*ZI569), (*ZI400), 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	{

    (ZI449) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (ZI548) ) ;
	}
	ZR553 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IGNORE end_function ( (ZI548), (ZI417) ) ;
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
	    IDENTIFIER ZI548;
	    EXP ZI417;

	    {

    if ( in_weak_param ) {
	(ZI548) = make_param_decl ( (*ZI606), (*ZI569), (*ZI400), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (*ZI569) ) == type_func_tag ) {
	check_weak_func ( (*ZI569), 0 ) ;
	(ZI548) = make_func_decl ( (*ZI606), (*ZI569), (*ZI400), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZI548) = make_object_decl ( (*ZI606), (*ZI569), (*ZI400), def ) ;
    }
    if ( IS_id_type_alias ( (ZI548) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI548) ) ) ;
	bs |= (*ZI659) ;
	COPY_btype ( id_type_alias_rep ( (ZI548) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR793 (ZI548, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = init_object ( (ZI548), (ZI417) ) ;
    if ( do_dump ) dump_declare ( (ZI548), &decl_loc, def ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			ZR798 (*ZI606, *ZI659, *ZI396);
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
ZR602(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 298: case 324: case 346:
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
ZR494(EXP *ZO894)
{
    EXP ZI894;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR492 (&ZI405);
	ZR895 (ZI405, &ZI894);
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
    *ZO894 = ZI894;
}

void
ZR1076(EXP *ZI1074, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 298: case 324: case 346:
	{
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;

	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1074), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI405) = make_comma_exp ( (ZI421) ) ;
	    }
	}
	break;
      default:
	{
	    ZI405 = *ZI1074;
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
ZR687(BASE_TYPE *ZO659, TYPE *ZO396, CV_SPEC *ZO631)
{
    BASE_TYPE ZI659;
    TYPE ZI396;
    CV_SPEC ZI631;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR632 (&ZI631);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI659) = btype_none ; 
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
	    ZR661 (&ZI659, &ZI396);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI631) = cv_none ; 
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
    *ZO659 = ZI659;
    *ZO396 = ZI396;
    *ZO631 = ZI631;
}

void
ZR951(EXP *ZI949, EXP *ZO405)
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
	    ZR504 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_cond_exp ( (*ZI949), (ZI417), (ZI449) ) ;
	    }
	}
	break;
      default:
	{
	    ZI405 = *ZI949;
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
ZR1079(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI1091;
	    EXP ZI1092;

	    ADVANCE_LEXER;
	    ZR415 (&ZI1091);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1092) = make_set_exp ( (ZI1091) ) ;
	    }
	    ZR1093 (&ZI1092, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 324:
	{
	    EXP ZI1088;
	    EXP ZI1089;

	    ADVANCE_LEXER;
	    ZR415 (&ZI1088);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1089) = make_unused_exp ( (ZI1088) ) ;
	    }
	    ZR1093 (&ZI1089, &ZI405);
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
ZR1080(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI468;
	    EXP ZI417;
	    EXP ZI449;

	    ADVANCE_LEXER;
	    ZR519 (&ZI468);
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
	    ZR529 (&ZI449);
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
	    ZR529 (&ZI449);
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
parse_stmt(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR529 (&ZI405);
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
ZR826(TYPE ZI421, BASE_TYPE ZI424)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_826:;
    {
	ZR825 (ZI421, ZI424);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_826;
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
ZR700(BASE_TYPE *ZI689, TYPE *ZI690, CV_SPEC *ZI691, BASE_TYPE *ZO659, TYPE *ZO396, CV_SPEC *ZO631)
{
    BASE_TYPE ZI659;
    TYPE ZI396;
    CV_SPEC ZI631;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI1033;
	TYPE ZI1034;
	CV_SPEC ZI1035;
	BASE_TYPE ZI693;
	TYPE ZI694;
	CV_SPEC ZI695;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR687 (&ZI1033, &ZI1034, &ZI1035);
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
	ZR700 (&ZI1033, &ZI1034, &ZI1035, &ZI693, &ZI694, &ZI695);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI689) & (ZI693) ) {
	(ZI659) = join_pre_types ( (*ZI689), (ZI693) ) ;
    } else {
	(ZI659) = ( (*ZI689) | (ZI693) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI690) ) ) {
	(ZI396) = (ZI694) ;
    } else if ( IS_NULL_type ( (ZI694) ) ) {
	(ZI396) = (*ZI690) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI690), (ZI694) ) ) ;
	(ZI396) = (ZI694) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI691) & (ZI695) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI631) = ( (*ZI691) | (ZI695) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI659 = *ZI689;
	    ZI396 = *ZI690;
	    ZI631 = *ZI691;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO659 = ZI659;
    *ZO396 = ZI396;
    *ZO631 = ZI631;
}

void
ZR445(TYPE *ZO396, int *ZO473)
{
    TYPE ZI396;
    int ZI473;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI463;
	BASE_TYPE ZI659;
	TYPE ZI421;
	CV_SPEC ZI631;
	TYPE ZI424;

	{

    (ZI463) = no_type_defns ;
	}
	ZR688 (&ZI659, &ZI421, &ZI631);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI424) = complete_pre_type ( (ZI659), (ZI421), (ZI631), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR761 (ZI424, &ZI396);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI473) = no_type_defns - (ZI463) ;
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
    *ZO473 = ZI473;
}

void
ZR511(EXP *ZO405)
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
ZR1082(IDENTIFIER *ZI400, EXP *ZO405)
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
	    EXP ZI1013;
	    EXP ZI1014;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    {

    (ZI1013) = make_id_exp ( (*ZI400) ) ;
	    }
	    ZR923 (ZI1013, &ZI1014);
	    ZR1015 (&ZI1014, &ZI1026);
	    ZR1028 (&ZI1026, &ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
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
	    ZR529 (&ZI449);
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
ZR805(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI606;
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
 (ZI606) = dspec_none ; 
	}
	{

    (ZI396) = NULL_type ;
	}
	ZR804 ();
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
ZR1083(IDENTIFIER *ZI400, EXP *ZO405)
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
	    ZR529 (&ZI449);
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
	ZR625 (&ZI424);
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
	    int ZI1007;
	    EXP ZI1008;

	    ADVANCE_LEXER;
	    {
 (ZI1007) = lex_alignof ; 
	    }
	    ZR462 (ZI1007, &ZI1008);
	    ZR1015 (&ZI1008, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1019;
	    EXP ZI1020;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1019 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR923 (ZI1019, &ZI1020);
	    ZR1015 (&ZI1020, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 206:
	{
	    EXP ZI417;
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
	    EXP ZI952;
	    EXP ZI949;

	    ADVANCE_LEXER;
	    ZR460 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI962) = make_cast_exp ( type_void, (ZI417), 0 ) ;
	    }
	    ZR919 (ZI962, &ZI961);
	    ZR915 (ZI961, &ZI960);
	    ZR911 (ZI960, &ZI959);
	    ZR907 (ZI959, &ZI958);
	    ZR903 (ZI958, &ZI957);
	    ZR899 (ZI957, &ZI956);
	    ZR895 (ZI956, &ZI955);
	    ZR891 (ZI955, &ZI954);
	    ZR887 (ZI954, &ZI953);
	    ZR883 (ZI953, &ZI952);
	    ZR879 (ZI952, &ZI949);
	    ZR951 (&ZI949, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 210:
	{
	    EXP ZI1016;
	    EXP ZI1017;

	    ADVANCE_LEXER;
	    {

    (ZI1016) = make_ellipsis_exp () ;
	    }
	    ZR923 (ZI1016, &ZI1017);
	    ZR1015 (&ZI1017, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI400;
	    EXP ZI1013;
	    EXP ZI1014;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1013) = make_id_exp ( (ZI400) ) ;
	    }
	    ZR923 (ZI1013, &ZI1014);
	    ZR1015 (&ZI1014, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI988;
	    EXP ZI989;

	    ADVANCE_LEXER;
	    ZR459 (&ZI988);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI989) = make_prefix_exp ( lex_minus_Hminus, (ZI988) ) ;
	    }
	    ZR1015 (&ZI989, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR984 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI985;
	    EXP ZI986;

	    ADVANCE_LEXER;
	    ZR459 (&ZI985);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI986) = make_prefix_exp ( lex_plus_Hplus, (ZI985) ) ;
	    }
	    ZR1015 (&ZI986, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 116:
	{
	    int ZI1004;
	    EXP ZI1005;

	    ADVANCE_LEXER;
	    {
 (ZI1004) = lex_sizeof ; 
	    }
	    ZR462 (ZI1004, &ZI1005);
	    ZR1015 (&ZI1005, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI991;
	    EXP ZI992;

	    ADVANCE_LEXER;
	    ZR460 (&ZI991);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI992) = make_indir_exp ( (ZI991) ) ;
	    }
	    ZR1015 (&ZI992, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI994;
	    EXP ZI995;

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
	    ZR460 (&ZI994);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI995) = make_ref_exp ( (ZI994), 0 ) ;
	    }
	    ZR1015 (&ZI995, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    EXP ZI1010;
	    EXP ZI1011;

	    ZR410 (&ZI1010);
	    ZR923 (ZI1010, &ZI1011);
	    ZR1015 (&ZI1011, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI997;
	    EXP ZI998;

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
	    ZR460 (&ZI997);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI998) = make_not_exp ( (ZI997) ) ;
	    }
	    ZR1015 (&ZI998, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI1000;
	    EXP ZI1001;
	    EXP ZI1002;

	    {
 (ZI1000) = crt_lex_token ; 
	    }
	    ZR470 ();
	    ZR460 (&ZI1001);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1002) = make_uminus_exp ( (ZI1000), (ZI1001) ) ;
	    }
	    ZR1015 (&ZI1002, &ZI405);
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
      case 206: case 210:
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
ZR500(EXP *ZO882)
{
    EXP ZI882;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR498 (&ZI405);
	ZR883 (ZI405, &ZI882);
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
    *ZO882 = ZI882;
}

void
ZR615(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 95:
	{
	    int ZI538;

	    ADVANCE_LEXER;
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
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
	    int ZI538;

	    ADVANCE_LEXER;
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
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
	    int ZI538;

	    ADVANCE_LEXER;
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR614 (&ZI405);
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
	    int ZI538;
	    EXP ZI417;

	    ADVANCE_LEXER;
	    {

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR616 (&ZI417);
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
ZR568(EXP *ZO931, EXP *ZO932, int *ZO933)
{
    EXP ZI931;
    EXP ZI932;
    int ZI933;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	EXP ZI421;
	int ZI538;
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

    (ZI538) = unreached_code ;
    if ( (ZI538) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	}
	ZR552 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI538) ; 
	}
	{

    (ZI405) = begin_hash_if_stmt ( (ZI468), (ZI417) ) ;
	}
	ZR934 (ZI405, ZI421, ZI538, &ZI931, &ZI932, &ZI933);
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
    *ZO931 = ZI931;
    *ZO932 = ZI932;
    *ZO933 = ZI933;
}

void
ZR633(CV_SPEC *ZO631)
{
    CV_SPEC ZI631;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	CV_SPEC ZI417;

	ZR632 (&ZI417);
	{
	    switch (CURRENT_TERMINAL) {
	      case 98: case 124:
		{
		    CV_SPEC ZI449;

		    ZR633 (&ZI449);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    CV_SPEC c = ( (ZI417) & (ZI449) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI631) = ( (ZI417) | (ZI449) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI631 = ZI417;
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
    *ZO631 = ZI631;
}

void
ZR964(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	int ZI473;
	EXP ZI417;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR445 (&ZI396, &ZI473);
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
	ZR460 (&ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* n is the number of type definitions in t */
    (ZI405) = make_cast_exp ( (ZI396), (ZI417), (ZI473) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 206: case 210: case 298: case 324: case 346:
	{
	    EXP ZI417;
	    EXP ZI963;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI963) = make_paren_exp ( (ZI417) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR923 (ZI963, &ZI405);
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
    *ZO405 = ZI405;
}

void
ZR553(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI468;
	int ZI548;
	EXP ZI449;
	EXP ZI538;
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
    (ZI548) = 1 ;
	}
	ZR549 (ZI468, ZI548, &ZI449);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI538) = fall_return_stmt () ;
	}
	{

    (ZI417) = add_compound_stmt ( (ZI449), (ZI538) ) ;
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
