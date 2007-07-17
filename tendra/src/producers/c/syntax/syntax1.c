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



/* BEGINNING OF STATIC VARIABLES */

int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
ZR661(BASE_TYPE *ZO660)
{
    BASE_TYPE ZI660;

    switch (CURRENT_TERMINAL) {
      case 185:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_bottom ; 
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_char ; 
	    }
	}
	break;
      case 102:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_double ; 
	    }
	}
	break;
      case 106:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_float ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_int ; 
	    }
	}
	break;
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_long ; 
	    }
	}
	break;
      case 286:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_ptrdiff_t ; 
	    }
	}
	break;
      case 114:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_short ; 
	    }
	}
	break;
      case 115:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_signed ; 
	    }
	}
	break;
      case 299:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_size_t ; 
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_unsigned ; 
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_void ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    {
 (ZI660) = btype_wchar_t ; 
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
}

void
ZR892(EXP ZI890, EXP *ZO891)
{
    EXP ZI891;

  ZL2_892:;
    switch (CURRENT_TERMINAL) {
      case 80:
	{
	    EXP ZI449;
	    EXP ZI405;

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
	    ZR495 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_xor_exp ( (ZI890), (ZI449) ) ;
	    }
	    ZI890 = ZI405;
	    goto ZL2_892;
	}
	/*UNREACHED*/
      default:
	{
	    ZI891 = ZI890;
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
    *ZO891 = ZI891;
}

void
ZR717(BASE_TYPE *ZO660, TYPE *ZO396, CV_SPEC *ZO632, DECL_SPEC *ZO607)
{
    BASE_TYPE ZI660;
    TYPE ZI396;
    CV_SPEC ZI632;
    DECL_SPEC ZI607;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI690;
	TYPE ZI691;
	CV_SPEC ZI692;
	DECL_SPEC ZI718;

	ZR716 (&ZI690, &ZI691, &ZI692, &ZI718);
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
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 25: case 94: case 97: case 98:
	      case 102: case 104: case 105: case 106: case 110:
	      case 111: case 112: case 114: case 115: case 117:
	      case 118: case 120: case 121: case 122: case 123:
	      case 124: case 137: case 156: case 185: case 286:
	      case 299:
		{
		    BASE_TYPE ZI694;
		    TYPE ZI695;
		    CV_SPEC ZI696;
		    DECL_SPEC ZI720;

		    ZR717 (&ZI694, &ZI695, &ZI696, &ZI720);
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
		    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI718) & (ZI720) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI607) = ( (ZI718) | (ZI720) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI660 = ZI690;
		    ZI396 = ZI691;
		    ZI632 = ZI692;
		    ZI607 = ZI718;
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
    *ZO660 = ZI660;
    *ZO396 = ZI396;
    *ZO632 = ZI632;
    *ZO607 = ZI607;
}

void
ZR747(IDENTIFIER ZI400, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI570;

	    ADVANCE_LEXER;
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI400) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 2: case 25: case 47: case 94: case 97:
		  case 98: case 102: case 104: case 105: case 106:
		  case 110: case 111: case 112: case 114: case 115:
		  case 117: case 118: case 120: case 121: case 122:
		  case 123: case 124: case 137: case 156: case 185:
		  case 286: case 299:
		    {
			int ZI749;

			ZR745 (&ZI749);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI570) = make_func_type ( NULL_type, (ZI749), cv_c, empty_type_set ) ;
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
		  case 1: case 4:
		    {
			ZR746 ();
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI570) = make_func_type ( NULL_type, FUNC_PARAMS, cv_c, empty_type_set ) ;
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
		  case 39:
		    {
			{

    (ZI570) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZI396 = ZI570;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	}
	break;
      case 332:
	{
	    int ZI749;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI400) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR760 (&ZI749);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = make_func_type ( NULL_type, ( (ZI749) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR759 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI405) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI396) ) ;
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
    *ZO396 = ZI396;
}

void
ZR772(IDENTIFIER *ZO549)
{
    IDENTIFIER ZI549;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI660;
	TYPE ZI691;
	CV_SPEC ZI632;
	DECL_SPEC ZI718;
	TYPE ZI695;
	DECL_SPEC ZI607;
	TYPE ZI396;
	IDENTIFIER ZI400;

	ZR717 (&ZI660, &ZI691, &ZI632, &ZI718);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI607) = complete_dspec ( (ZI718), (ZI660), (ZI691), (ZI632) ) ;
    (ZI695) = complete_pre_type ( (ZI660), (ZI691), (ZI632), 0 ) ;
    have_type_specifier = 0 ;
	}
	ZR768 (ZI695, &ZI396, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI549) = make_param_decl ( (ZI607), (ZI396), (ZI400), CONTEXT_PARAMETER ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO549 = ZI549;
}

void
ZR896(EXP ZI894, EXP *ZO895)
{
    EXP ZI895;

  ZL2_896:;
    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    EXP ZI449;
	    EXP ZI405;

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
	    ZR493 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_and_exp ( (ZI894), (ZI449) ) ;
	    }
	    ZI894 = ZI405;
	    goto ZL2_896;
	}
	/*UNREACHED*/
      default:
	{
	    ZI895 = ZI894;
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
    *ZO895 = ZI895;
}

void
ZR571(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;
	EXP ZI421;
	int ZI539;
	EXP ZI449;

	ZR569 (&ZI417, &ZI421, &ZI539);
	{
	    switch (CURRENT_TERMINAL) {
	      case 28:
		{
		    int ZI570;

		    ADVANCE_LEXER;
		    {

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
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
		}
		break;
	      default:
		{
		    {

    (ZI449) = NULL_exp ;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    crt_hash_cond = (ZI421) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
 unreached_prev = (ZI539) ; 
	}
	{

    (ZI405) = end_hash_if_stmt ( (ZI417), (ZI449) ) ;
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
ZR1025(EXP *ZI1023, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;

	    ADVANCE_LEXER;
	    ZR517 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1023), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI405) = make_comma_exp ( (ZI421) ) ;
	    }
	}
	break;
      default:
	{
	    ZI405 = *ZI1023;
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
ZR658(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI671;

	ZR672 (&ZI671);
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
		    ZR1028 (&ZI671, &ZI400, &ZI396);
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
		    int ZI587;
		    IDENTIFIER ZI674;

		    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
		    }
		    {

    (ZI421) = begin_class_defn ( (ZI400), (ZI671), cinfo_none, NULL_type ) ;
    (ZI587) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
    end_base_class ( crt_class, 1 ) ;
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
		    ZR664 ();
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

    (ZI674) = end_class_defn ( (ZI421) ) ;
    in_function_defn = (ZI587) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
		    }
		    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI674) ) ;
    have_type_specifier = 1 ;
		    }
		    {

    RESCAN_LEXER ;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
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
ZR1026(EXP *ZI417, SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI424;

	    ADVANCE_LEXER;
	    ZR517 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI417), (ZI424), (ZI421) ) ;
	    }
	}
	break;
      default:
	{
	    SID_LIST_EXP ZI424;

	    {

    (ZI424) = NULL_list ( EXP ) ;
	    }
	    {

    CONS_exp ( (*ZI417), (ZI424), (ZI421) ) ;
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
ZR428(NAMESPACE ZI427, IDENTIFIER *ZO400)
{
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI429;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI429 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI429 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI429 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    HASHID nm = DEREF_hashid ( id_name ( (ZI429) ) ) ;
    (ZI400) = find_qual_id ( (ZI427), nm, 1, 0 ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO400 = ZI400;
}

void
ZR716(BASE_TYPE *ZO660, TYPE *ZO396, CV_SPEC *ZO632, DECL_SPEC *ZO607)
{
    BASE_TYPE ZI660;
    TYPE ZI396;
    CV_SPEC ZI632;
    DECL_SPEC ZI607;

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
	    {
 (ZI607) = dspec_none ; 
	    }
	}
	break;
      case 94: case 105: case 112: case 117: case 120:
      case 137:
	{
	    ZR711 (&ZI607);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZI607) ) ) ;
	    }
	    {
 (ZI660) = btype_none ; 
	    }
	    {

    (ZI396) = NULL_type ;
	    }
	    {
 (ZI632) = cv_none ; 
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
	    {
 (ZI607) = dspec_none ; 
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
    *ZO607 = ZI607;
}

void
parse_init(IDENTIFIER ZI549, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR790 (ZI549, &ZI405);
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
ZR1027(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 298:
	{
	    EXP ZI417;

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
	    EXP ZI417;

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
    *ZO405 = ZI405;
}

void
ZR900(EXP ZI898, EXP *ZO899)
{
    EXP ZI899;

  ZL2_900:;
    switch (CURRENT_TERMINAL) {
      case 86: case 87:
	{
	    int ZI461;
	    EXP ZI449;
	    EXP ZI405;

	    {
 (ZI461) = crt_lex_token ; 
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
	    ZR490 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_mult_exp ( (ZI461), (ZI898), (ZI449) ) ;
	    }
	    ZI898 = ZI405;
	    goto ZL2_900;
	}
	/*UNREACHED*/
      default:
	{
	    ZI899 = ZI898;
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
    *ZO899 = ZI899;
}

void
ZR805(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_805:;
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
	    goto ZL3;
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
	goto ZL2_805;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_dcl_dcl_semicolon () ) ;
	    }
	    goto ZL2_805;
	}
	/*UNREACHED*/
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
	    goto ZL2_805;
	}
	/*UNREACHED*/
      case 26: case 30:
	{
	    ZR808 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_805;
	    }
	}
	/*UNREACHED*/
      case 1: case 2: case 4: case 65: case 78:
	{
	    BASE_TYPE ZI660;
	    TYPE ZI691;
	    CV_SPEC ZI632;
	    DECL_SPEC ZI718;
	    TYPE ZI396;
	    DECL_SPEC ZI607;
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
    (ZI607) = complete_dspec ( (ZI718), (ZI660), (ZI691), (ZI632) ) ;
    (ZI396) = complete_pre_type ( (ZI660), (ZI691), (ZI632), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR754 (ZI396, &ZI570, &ZI400);
	    ZR821 (&ZI660, &ZI396, &ZI607, &ZI570, &ZI400);
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
	    goto ZL2_805;
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
ZR1028(BASE_TYPE *ZI671, IDENTIFIER *ZI400, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    IDENTIFIER ZI421;
	    int ZI587;
	    IDENTIFIER ZI674;

	    {

    (ZI421) = begin_class_defn ( (*ZI400), (*ZI671), cinfo_none, NULL_type ) ;
    (ZI587) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
    end_base_class ( crt_class, 1 ) ;
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
	    ZR664 ();
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

    (ZI674) = end_class_defn ( (ZI421) ) ;
    in_function_defn = (ZI587) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI674) ) ;
    have_type_specifier = 1 ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      default:
	{
	    {

    MAKE_type_pre ( cv_none, (*ZI671), qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (*ZI400) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
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
ZR756(TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI570;

	    ADVANCE_LEXER;
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
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI400;
	    int ZI749;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI400) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI400) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR760 (&ZI749);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = make_func_type ( NULL_type, ( (ZI749) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR759 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI405) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI396) ) ;
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
    *ZO396 = ZI396;
}

void
ZR1029(BASE_TYPE *ZI660, TYPE *ZI421, CV_SPEC *ZI632)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( dspec_none, NULL_type, (*ZI660), (*ZI421), (*ZI632), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 4: case 41: case 65:
      case 78:
	{
	    TYPE ZI396;

	    {

    (ZI396) = complete_pre_type ( (*ZI660), (*ZI421), (*ZI632), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR826 (ZI396, *ZI660);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			ZR827 (ZI396, *ZI660);
			switch (CURRENT_TERMINAL) {
			  case 77:
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
		  case 77:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 355:
		    RESTORE_LEXER;
		    goto ZL1;
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
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR558(EXP ZI468, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;

	ZR557 (ZI468, &ZI417);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
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
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI405) = end_compound_stmt ( (ZI468) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR798(DECL_SPEC ZI607, BASE_TYPE ZI660, TYPE ZI421)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	IDENTIFIER ZI400;
	IDENTIFIER ZI549;
	EXP ZI405;

	ZR754 (ZI421, &ZI396, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( in_weak_param ) {
	(ZI549) = make_param_decl ( (ZI607), (ZI396), (ZI400), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (ZI396) ) == type_func_tag ) {
	check_weak_func ( (ZI396), 0 ) ;
	(ZI549) = make_func_decl ( (ZI607), (ZI396), (ZI400), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZI549) = make_object_decl ( (ZI607), (ZI396), (ZI400), def ) ;
    }
    if ( IS_id_type_alias ( (ZI549) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI549) ) ) ;
	bs |= (ZI660) ;
	COPY_btype ( id_type_alias_rep ( (ZI549) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	ZR794 (ZI549, &ZI405);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    int def = init_object ( (ZI549), (ZI405) ) ;
    if ( do_dump ) dump_declare ( (ZI549), &decl_loc, def ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR904(EXP ZI902, EXP *ZO903)
{
    EXP ZI903;

  ZL2_904:;
    switch (CURRENT_TERMINAL) {
      case 48: case 63:
	{
	    int ZI461;
	    EXP ZI449;
	    EXP ZI405;

	    {
 (ZI461) = crt_lex_token ; 
	    }
	    ZR489 ();
	    ZR487 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI405) = make_equality_exp ( (ZI461), (ZI902), (ZI449) ) ;
	    }
	    ZI902 = ZI405;
	    goto ZL2_904;
	}
	/*UNREACHED*/
      default:
	{
	    ZI903 = ZI902;
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
    *ZO903 = ZI903;
}

void
ZR561(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI690;
	TYPE ZI1097;
	CV_SPEC ZI692;
	DECL_SPEC ZI1098;
	BASE_TYPE ZI660;
	TYPE ZI691;
	CV_SPEC ZI632;
	DECL_SPEC ZI718;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	ZR716 (&ZI690, &ZI1097, &ZI692, &ZI1098);
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
	ZR726 (&ZI690, &ZI1097, &ZI692, &ZI1098, &ZI660, &ZI691, &ZI632, &ZI718);
	ZR815 (&ZI660, &ZI691, &ZI632, &ZI718);
	switch (CURRENT_TERMINAL) {
	  case 77:
	    break;
	  case 355:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR416(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 23:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI405 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 210:
	{
	    ADVANCE_LEXER;
	    {

    (ZI405) = make_ellipsis_exp () ;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI400;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI405) = make_id_exp ( (ZI400) ) ;
	    }
	}
	break;
      case 65:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR415 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_paren_exp ( (ZI417) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
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
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    ZR410 (&ZI405);
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
ZR622(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 289:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    {
 unreached_code = 0 ; 
	    }
	    ZR530 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_reach_stmt ( (ZI417), 1 ) ;
	    }
	}
	break;
      case 323:
	{
	    EXP ZI417;

	    ADVANCE_LEXER;
	    {
 unreached_code = 1 ; 
	    }
	    ZR530 (&ZI417);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_reach_stmt ( (ZI417), 0 ) ;
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
ZR908(EXP ZI906, EXP *ZO907)
{
    EXP ZI907;

  ZL2_908:;
    switch (CURRENT_TERMINAL) {
      case 49: case 50: case 53: case 54:
	{
	    int ZI461;
	    EXP ZI449;
	    EXP ZI405;

	    {
 (ZI461) = crt_lex_token ; 
	    }
	    {
		switch (CURRENT_TERMINAL) {
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
		  default:
		    goto ZL1;
		}
	    }
	    ZR484 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI405) = make_relation_exp ( (ZI461), (ZI906), (ZI449) ) ;
	    }
	    ZI906 = ZI405;
	    goto ZL2_908;
	}
	/*UNREACHED*/
      default:
	{
	    ZI907 = ZI906;
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
    *ZO907 = ZI907;
}

void
ZR672(BASE_TYPE *ZO671)
{
    BASE_TYPE ZI671;

    switch (CURRENT_TERMINAL) {
      case 118:
	{
	    ADVANCE_LEXER;
	    {
 (ZI671) = btype_struct ; 
	    }
	}
	break;
      case 121:
	{
	    ADVANCE_LEXER;
	    {
 (ZI671) = btype_union ; 
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
    *ZO671 = ZI671;
}

void
ZR791(IDENTIFIER ZI549, SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI449;
	EXP ZI417;
	SID_LIST_EXP ZI424;

	ZR790 (ZI549, &ZI449);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI449), (ZI417) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1074 (&ZI549, &ZI424);
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
	    }
	}
	{

    CONS_exp ( (ZI417), (ZI424), (ZI421) ) ;
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
parse_tok_type(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI660;
	TYPE ZI421;
	CV_SPEC ZI632;
	TYPE ZI424;

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
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
}

void
ZR489(void)
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
ZR493(EXP *ZO899)
{
    EXP ZI899;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR490 (&ZI405);
	ZR900 (ZI405, &ZI899);
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
    *ZO899 = ZI899;
}

void
ZR513(EXP *ZO405)
{
    EXP ZI405;

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
	ZR1027 (&ZI405);
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
ZR912(EXP ZI910, EXP *ZO911)
{
    EXP ZI911;

  ZL2_912:;
    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR481 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_shift_exp ( lex_lshift, (ZI910), (ZI449) ) ;
	    }
	    ZI910 = ZI405;
	    goto ZL2_912;
	}
	/*UNREACHED*/
      case 75:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR481 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_shift_exp ( lex_rshift, (ZI910), (ZI449) ) ;
	    }
	    ZI910 = ZI405;
	    goto ZL2_912;
	}
	/*UNREACHED*/
      default:
	{
	    ZI911 = ZI910;
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
    *ZO911 = ZI911;
}

void
parse_type_param(IDENTIFIER *ZO549)
{
    IDENTIFIER ZI549;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
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
    *ZO549 = ZI549;
}

void
ZR1041(TYPE *ZI421, BASE_TYPE *ZI424, IDENTIFIER *ZI1040)
{
    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    EXP ZI468;
	    TYPE ZI396;

	    {

    IDENTIFIER pid = underlying_id ( (*ZI1040) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ADVANCE_LEXER;
	    ZR520 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1040) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI396) = make_bitfield_type ( (*ZI421), (*ZI424), (ZI468), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI396), (*ZI1040), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI1039;
	    TYPE ZI1033;
	    IDENTIFIER ZI400;
	    TYPE ZI396;

	    {

    (ZI1039) = NULL_type ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (*ZI1040) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR870 (ZI1039, *ZI1040, &ZI1033, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI1033) ) ? (*ZI421) : inject_pre_type ( (ZI1033), (*ZI421), 1 ) ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI396), (ZI400), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
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
ZR448(EXP *ZO923)
{
    EXP ZI923;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR416 (&ZI405);
	ZR924 (ZI405, &ZI923);
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
    *ZO923 = ZI923;
}

void
ZR556(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI1008;
	    EXP ZI1009;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    {
 (ZI1008) = lex_alignof ; 
	    }
	    ZR462 (ZI1008, &ZI1009);
	    ZR1013 (&ZI1009, &ZI1023);
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
      case 23:
	{
	    EXP ZI1020;
	    EXP ZI1021;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1020 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR924 (ZI1020, &ZI1021);
	    ZR1013 (&ZI1021, &ZI1023);
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
      case 24:
	{
	    EXP ZI417;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI417 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI405) = make_exp_stmt ( (ZI417) ) ;
	    }
	}
	break;
      case 206:
	{
	    EXP ZI1083;
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
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR460 (&ZI1083);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI963) = make_cast_exp ( type_void, (ZI1083), 0 ) ;
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
	    ZR952 (&ZI950, &ZI1023);
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
      case 210:
	{
	    EXP ZI1017;
	    EXP ZI1018;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    {

    (ZI1017) = make_ellipsis_exp () ;
	    }
	    ZR924 (ZI1017, &ZI1018);
	    ZR1013 (&ZI1018, &ZI1023);
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
      case 1:
	{
	    IDENTIFIER ZI400;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1084 (&ZI400, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 346:
	{
	    ADVANCE_LEXER;
	    ZR1080 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 255:
	{
	    EXP ZI1082;
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
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR460 (&ZI1082);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI963) = make_lit_exp ( (ZI1082) ) ;
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
	    ZR952 (&ZI950, &ZI1023);
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
      case 61:
	{
	    EXP ZI989;
	    EXP ZI990;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR459 (&ZI989);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI990) = make_prefix_exp ( lex_minus_Hminus, (ZI989) ) ;
	    }
	    ZR1013 (&ZI990, &ZI1023);
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
      case 65:
	{
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR985 (&ZI1023);
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
      case 71:
	{
	    EXP ZI986;
	    EXP ZI987;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR459 (&ZI986);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI987) = make_prefix_exp ( lex_plus_Hplus, (ZI986) ) ;
	    }
	    ZR1013 (&ZI987, &ZI1023);
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
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI405) = NULL_exp ;
	    }
	}
	break;
      case 116:
	{
	    int ZI1005;
	    EXP ZI1006;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    {
 (ZI1005) = lex_sizeof ; 
	    }
	    ZR462 (ZI1005, &ZI1006);
	    ZR1013 (&ZI1006, &ZI1023);
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
      case 78:
	{
	    EXP ZI992;
	    EXP ZI993;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ADVANCE_LEXER;
	    ZR460 (&ZI992);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI993) = make_indir_exp ( (ZI992) ) ;
	    }
	    ZR1013 (&ZI993, &ZI1023);
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
      case 4:
	{
	    IDENTIFIER ZI400;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1085 (&ZI400, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI400;
	    EXP ZI417;
	    EXP ZI449;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI417) = begin_label_stmt ( (ZI400), lex_identifier ) ;
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

    (ZI405) = end_label_stmt ( (ZI417), (ZI449) ) ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI995;
	    EXP ZI996;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

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
	    ZR1013 (&ZI996, &ZI1023);
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
      case 126:
	{
	    ZR625 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 289: case 323:
	{
	    ZR622 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 96: case 100: case 223:
	{
	    ZR531 ();
	    ZR1081 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI1075;
	    EXP ZI417;
	    int ZI539;

	    ZR512 (&ZI1075);
	    ZR1077 (&ZI1075, &ZI417);
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
      case 101: case 107: case 125:
	{
	    ZR604 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    ZR616 (&ZI405);
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
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

	    ZR410 (&ZI1011);
	    ZR924 (ZI1011, &ZI1012);
	    ZR1013 (&ZI1012, &ZI1023);
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
      case 62:
	{
	    EXP ZI998;
	    EXP ZI999;
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

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
	    ZR1013 (&ZI999, &ZI1023);
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
      case 26: case 109: case 119:
	{
	    ZR582 (&ZI405);
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
	    EXP ZI1023;
	    EXP ZI417;
	    int ZI539;

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
	    ZR1013 (&ZI1003, &ZI1023);
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
ZR664(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_664:;
    {
	BASE_TYPE ZI690;
	TYPE ZI691;
	CV_SPEC ZI692;
	BASE_TYPE ZI660;
	TYPE ZI421;
	CV_SPEC ZI632;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR688 (&ZI690, &ZI691, &ZI692);
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
	ZR701 (&ZI690, &ZI691, &ZI692, &ZI660, &ZI421, &ZI632);
	ZR1029 (&ZI660, &ZI421, &ZI632);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	} else {
	    goto ZL2_664;
	}
    }
    /*UNREACHED*/
  ZL3:;
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR916(EXP ZI914, EXP *ZO915)
{
    EXP ZI915;

  ZL2_916:;
    switch (CURRENT_TERMINAL) {
      case 59:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR478 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_minus_exp ( (ZI914), (ZI449) ) ;
	    }
	    ZI914 = ZI405;
	    goto ZL2_916;
	}
	/*UNREACHED*/
      case 69:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR478 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_plus_exp ( (ZI914), (ZI449) ) ;
	    }
	    ZI914 = ZI405;
	    goto ZL2_916;
	}
	/*UNREACHED*/
      default:
	{
	    ZI915 = ZI914;
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
    *ZO915 = ZI915;
}

void
ZR462(int ZI461, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	int ZI463;
	int ZI464;
	EXP ZI468;

	{

    suppress_usage++ ;
	}
	{

    (ZI463) = no_side_effects ;
	}
	{

    (ZI464) = no_type_defns ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 170:
		{
		    int ZI1067;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    {
 (ZI1067) = lex_alignof ; 
		    }
		    ZR462 (ZI1067, &ZI417);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 23:
		{
		    EXP ZI1103;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1103 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
		    }
		    ADVANCE_LEXER;
		    ZR924 (ZI1103, &ZI417);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 210:
		{
		    EXP ZI1104;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    {

    (ZI1104) = make_ellipsis_exp () ;
		    }
		    ZR924 (ZI1104, &ZI417);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 1:
		{
		    IDENTIFIER ZI400;
		    EXP ZI1105;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		    {

    (ZI1105) = make_id_exp ( (ZI400) ) ;
		    }
		    ZR924 (ZI1105, &ZI417);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 61:
		{
		    EXP ZI1060;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    ZR459 (&ZI1060);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_prefix_exp ( lex_minus_Hminus, (ZI1060) ) ;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 65:
		{
		    ADVANCE_LEXER;
		    ZR1069 (&ZI461, &ZI463, &ZI464, &ZI468);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 71:
		{
		    EXP ZI1059;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    ZR459 (&ZI1059);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_prefix_exp ( lex_plus_Hplus, (ZI1059) ) ;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 116:
		{
		    int ZI1066;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    {
 (ZI1066) = lex_sizeof ; 
		    }
		    ZR462 (ZI1066, &ZI417);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 78:
		{
		    EXP ZI1061;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    ZR460 (&ZI1061);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_indir_exp ( (ZI1061) ) ;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 33:
		{
		    EXP ZI1062;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

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
		    ZR460 (&ZI1062);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_ref_exp ( (ZI1062), 0 ) ;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 17: case 18: case 19: case 20: case 21:
	      case 22:
		{
		    EXP ZI1106;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ZR410 (&ZI1106);
		    ZR924 (ZI1106, &ZI417);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 62:
		{
		    EXP ZI1063;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

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
		    ZR460 (&ZI1063);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_not_exp ( (ZI1063) ) ;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
		    }
		}
		break;
	      case 43: case 59: case 69: case 85:
		{
		    int ZI1064;
		    EXP ZI1065;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    {
 (ZI1064) = crt_lex_token ; 
		    }
		    ZR470 ();
		    ZR460 (&ZI1065);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_uminus_exp ( (ZI1064), (ZI1065) ) ;
		    }
		    {

    (ZI466) = no_side_effects - (ZI463) ;
		    }
		    {

    (ZI467) = no_type_defns - (ZI464) ;
		    }
		    {

    (ZI396) = typeof_exp ( &(ZI417), (ZI466), (ZI461) ) ;
		    }
		    {

    (ZI468) = make_sizeof_exp ( (ZI396), (ZI417), (ZI467), (ZI461) ) ;
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
	ZI405 = ZI468;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO405 = ZI405;
}

void
ZR1044(TYPE *ZO856, IDENTIFIER *ZO857)
{
    TYPE ZI856;
    IDENTIFIER ZI857;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1045;
	TYPE ZI1046;
	TYPE ZI396;
	IDENTIFIER ZI400;

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
	ZR858 (ZI1046, ZI1045, &ZI396, &ZI400);
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
	ZR858 (ZI396, ZI400, &ZI856, &ZI857);
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
	    TYPE ZI396;
	    IDENTIFIER ZI400;

	    ADVANCE_LEXER;
	    ZR1044 (&ZI396, &ZI400);
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
	    ZR858 (ZI396, ZI400, &ZI856, &ZI857);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1043;
	    int ZI749;
	    TYPE ZI1049;
	    IDENTIFIER ZI1050;
	    TYPE ZI396;
	    IDENTIFIER ZI400;

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
	    ZR858 (ZI1049, ZI1050, &ZI396, &ZI400);
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
	    ZR858 (ZI396, ZI400, &ZI856, &ZI857);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;
	    TYPE ZI1047;
	    IDENTIFIER ZI1048;
	    TYPE ZI396;
	    IDENTIFIER ZI400;

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
	    ZR858 (ZI1047, ZI1048, &ZI396, &ZI400);
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
	    ZR858 (ZI396, ZI400, &ZI856, &ZI857);
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
	    IDENTIFIER ZI400;
	    TYPE ZI396;

	    ZR733 (&ZI421);
	    ZR766 (&ZI424, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 0 ) ) ;
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
	    ZR858 (ZI396, ZI400, &ZI856, &ZI857);
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
	    IDENTIFIER ZI1042;
	    TYPE ZI570;
	    TYPE ZI396;
	    IDENTIFIER ZI400;

	    {

    (ZI1042) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1042) ) ;
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
	    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR858 (ZI396, ZI400, &ZI856, &ZI857);
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
    *ZO856 = ZI856;
    *ZO857 = ZI857;
}

void
ZR920(EXP ZI918, EXP *ZO919)
{
    EXP ZI919;

  ZL2_920:;
    switch (CURRENT_TERMINAL) {
      case 44:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR460 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_mult_exp ( lex_div, (ZI918), (ZI449) ) ;
	    }
	    ZI918 = ZI405;
	    goto ZL2_920;
	}
	/*UNREACHED*/
      case 73:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR460 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_rem_exp ( (ZI918), (ZI449) ) ;
	    }
	    ZI918 = ZI405;
	    goto ZL2_920;
	}
	/*UNREACHED*/
      case 78:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR460 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_mult_exp ( lex_star, (ZI918), (ZI449) ) ;
	    }
	    ZI918 = ZI405;
	    goto ZL2_920;
	}
	/*UNREACHED*/
      default:
	{
	    ZI919 = ZI918;
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
    *ZO919 = ZI919;
}

void
ZR780(void)
{
  ZL2_780:;
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    IDENTIFIER ZI400;

	    ADVANCE_LEXER;
	    ZR779 (&ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
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
	    goto ZL2_780;
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
ZR766(TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1045;
	TYPE ZI1046;

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
	ZR858 (ZI1046, ZI1045, &ZI396, &ZI400);
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
	    ZR1044 (&ZI396, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1043;
	    int ZI749;
	    TYPE ZI1049;
	    IDENTIFIER ZI1050;

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
	    ZR858 (ZI1049, ZI1050, &ZI396, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;
	    TYPE ZI1047;
	    IDENTIFIER ZI1048;

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
	    ZR858 (ZI1047, ZI1048, &ZI396, &ZI400);
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
	    ZR766 (&ZI424, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI424) ) ? (ZI421) : inject_pre_type ( (ZI424), (ZI421), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI396) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
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
    *ZO396 = ZI396;
    *ZO400 = ZI400;
}

void
ZR625(EXP *ZO405)
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
	ZR626 (&ZI421);
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

/* END OF FILE */
