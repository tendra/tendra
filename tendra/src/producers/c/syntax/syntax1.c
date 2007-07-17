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
ZR660(BASE_TYPE *ZO659)
{
    BASE_TYPE ZI659;

    switch (CURRENT_TERMINAL) {
      case 185:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_bottom ; 
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_char ; 
	    }
	}
	break;
      case 102:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_double ; 
	    }
	}
	break;
      case 106:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_float ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_int ; 
	    }
	}
	break;
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_long ; 
	    }
	}
	break;
      case 286:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_ptrdiff_t ; 
	    }
	}
	break;
      case 114:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_short ; 
	    }
	}
	break;
      case 115:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_signed ; 
	    }
	}
	break;
      case 299:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_size_t ; 
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_unsigned ; 
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_void ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    {
 (ZI659) = btype_wchar_t ; 
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
}

void
ZR891(EXP ZI889, EXP *ZO890)
{
    EXP ZI890;

  ZL2_891:;
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
	    ZR494 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_xor_exp ( (ZI889), (ZI449) ) ;
	    }
	    ZI889 = ZI405;
	    goto ZL2_891;
	}
	/*UNREACHED*/
      default:
	{
	    ZI890 = ZI889;
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
    *ZO890 = ZI890;
}

void
ZR716(BASE_TYPE *ZO659, TYPE *ZO396, CV_SPEC *ZO631, DECL_SPEC *ZO606)
{
    BASE_TYPE ZI659;
    TYPE ZI396;
    CV_SPEC ZI631;
    DECL_SPEC ZI606;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI689;
	TYPE ZI690;
	CV_SPEC ZI691;
	DECL_SPEC ZI717;

	ZR715 (&ZI689, &ZI690, &ZI691, &ZI717);
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
		    BASE_TYPE ZI693;
		    TYPE ZI694;
		    CV_SPEC ZI695;
		    DECL_SPEC ZI719;

		    ZR716 (&ZI693, &ZI694, &ZI695, &ZI719);
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
		    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI717) & (ZI719) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI606) = ( (ZI717) | (ZI719) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI659 = ZI689;
		    ZI396 = ZI690;
		    ZI631 = ZI691;
		    ZI606 = ZI717;
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
    *ZO659 = ZI659;
    *ZO396 = ZI396;
    *ZO631 = ZI631;
    *ZO606 = ZI606;
}

void
ZR746(IDENTIFIER ZI400, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI569;

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
			int ZI748;

			ZR744 (&ZI748);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI569) = make_func_type ( NULL_type, (ZI748), cv_c, empty_type_set ) ;
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
			ZR745 ();
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI569) = make_func_type ( NULL_type, FUNC_PARAMS, cv_c, empty_type_set ) ;
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

    (ZI569) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZI396 = ZI569;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	}
	break;
      case 332:
	{
	    int ZI748;

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
	    ZR759 (&ZI748);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = make_func_type ( NULL_type, ( (ZI748) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR758 (&ZI405);
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
ZR771(IDENTIFIER *ZO548)
{
    IDENTIFIER ZI548;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI659;
	TYPE ZI690;
	CV_SPEC ZI631;
	DECL_SPEC ZI717;
	TYPE ZI694;
	DECL_SPEC ZI606;
	TYPE ZI396;
	IDENTIFIER ZI400;

	ZR716 (&ZI659, &ZI690, &ZI631, &ZI717);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI606) = complete_dspec ( (ZI717), (ZI659), (ZI690), (ZI631) ) ;
    (ZI694) = complete_pre_type ( (ZI659), (ZI690), (ZI631), 0 ) ;
    have_type_specifier = 0 ;
	}
	ZR767 (ZI694, &ZI396, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI548) = make_param_decl ( (ZI606), (ZI396), (ZI400), CONTEXT_PARAMETER ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO548 = ZI548;
}

void
ZR895(EXP ZI893, EXP *ZO894)
{
    EXP ZI894;

  ZL2_895:;
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
	    ZR492 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_and_exp ( (ZI893), (ZI449) ) ;
	    }
	    ZI893 = ZI405;
	    goto ZL2_895;
	}
	/*UNREACHED*/
      default:
	{
	    ZI894 = ZI893;
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
    *ZO894 = ZI894;
}

void
ZR570(EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;
	EXP ZI421;
	int ZI538;
	EXP ZI449;

	ZR568 (&ZI417, &ZI421, &ZI538);
	{
	    switch (CURRENT_TERMINAL) {
	      case 28:
		{
		    int ZI569;

		    ADVANCE_LEXER;
		    {

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
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
 unreached_prev = (ZI538) ; 
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
ZR657(TYPE *ZO396)
{
    TYPE ZI396;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI670;

	ZR671 (&ZI670);
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
		    ZR1031 (&ZI670, &ZI400, &ZI396);
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
		    int ZI586;
		    IDENTIFIER ZI673;

		    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
		    }
		    {

    (ZI421) = begin_class_defn ( (ZI400), (ZI670), cinfo_none, NULL_type ) ;
    (ZI586) = in_function_defn ;
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
		    ZR663 ();
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

    (ZI673) = end_class_defn ( (ZI421) ) ;
    in_function_defn = (ZI586) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
		    }
		    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI673) ) ;
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
ZR899(EXP ZI897, EXP *ZO898)
{
    EXP ZI898;

  ZL2_899:;
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
	    ZR489 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_mult_exp ( (ZI461), (ZI897), (ZI449) ) ;
	    }
	    ZI897 = ZI405;
	    goto ZL2_899;
	}
	/*UNREACHED*/
      default:
	{
	    ZI898 = ZI897;
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
    *ZO898 = ZI898;
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
ZR715(BASE_TYPE *ZO659, TYPE *ZO396, CV_SPEC *ZO631, DECL_SPEC *ZO606)
{
    BASE_TYPE ZI659;
    TYPE ZI396;
    CV_SPEC ZI631;
    DECL_SPEC ZI606;

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
	    {
 (ZI606) = dspec_none ; 
	    }
	}
	break;
      case 94: case 105: case 112: case 117: case 120:
      case 137:
	{
	    ZR710 (&ZI606);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZI606) ) ) ;
	    }
	    {
 (ZI659) = btype_none ; 
	    }
	    {

    (ZI396) = NULL_type ;
	    }
	    {
 (ZI631) = cv_none ; 
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
	    {
 (ZI606) = dspec_none ; 
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
    *ZO606 = ZI606;
}

void
parse_init(IDENTIFIER ZI548, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR789 (ZI548, &ZI405);
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
ZR804(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_804:;
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
	    goto ZL3;
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
	goto ZL2_804;
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
	    goto ZL2_804;
	}
	/*UNREACHED*/
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
	    goto ZL2_804;
	}
	/*UNREACHED*/
      case 26: case 30:
	{
	    ZR807 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_804;
	    }
	}
	/*UNREACHED*/
      case 1: case 2: case 4: case 65: case 78:
	{
	    BASE_TYPE ZI659;
	    TYPE ZI690;
	    CV_SPEC ZI631;
	    DECL_SPEC ZI717;
	    TYPE ZI396;
	    DECL_SPEC ZI606;
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
    (ZI606) = complete_dspec ( (ZI717), (ZI659), (ZI690), (ZI631) ) ;
    (ZI396) = complete_pre_type ( (ZI659), (ZI690), (ZI631), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR753 (ZI396, &ZI569, &ZI400);
	    ZR820 (&ZI659, &ZI396, &ZI606, &ZI569, &ZI400);
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
	    goto ZL2_804;
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
ZR1028(EXP *ZI1026, EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI424;
	    SID_LIST_EXP ZI421;

	    ADVANCE_LEXER;
	    ZR516 (&ZI424);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1026), (ZI424), (ZI421) ) ;
	    }
	    {

    (ZI405) = make_comma_exp ( (ZI421) ) ;
	    }
	}
	break;
      default:
	{
	    ZI405 = *ZI1026;
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
ZR755(TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI400;
	    TYPE ZI569;

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
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI400;
	    int ZI748;

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
	    ZR759 (&ZI748);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = make_func_type ( NULL_type, ( (ZI748) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR758 (&ZI405);
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
ZR1029(EXP *ZI417, SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI424;

	    ADVANCE_LEXER;
	    ZR516 (&ZI424);
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
ZR557(EXP ZI468, EXP *ZO405)
{
    EXP ZI405;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI417;

	ZR556 (ZI468, &ZI417);
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
ZR1030(EXP *ZO405)
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
ZR903(EXP ZI901, EXP *ZO902)
{
    EXP ZI902;

  ZL2_903:;
    switch (CURRENT_TERMINAL) {
      case 48: case 63:
	{
	    int ZI461;
	    EXP ZI449;
	    EXP ZI405;

	    {
 (ZI461) = crt_lex_token ; 
	    }
	    ZR488 ();
	    ZR486 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI405) = make_equality_exp ( (ZI461), (ZI901), (ZI449) ) ;
	    }
	    ZI901 = ZI405;
	    goto ZL2_903;
	}
	/*UNREACHED*/
      default:
	{
	    ZI902 = ZI901;
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
    *ZO902 = ZI902;
}

void
ZR797(DECL_SPEC ZI606, BASE_TYPE ZI659, TYPE ZI421)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE ZI396;
	IDENTIFIER ZI400;
	IDENTIFIER ZI548;
	EXP ZI405;

	ZR753 (ZI421, &ZI396, &ZI400);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( in_weak_param ) {
	(ZI548) = make_param_decl ( (ZI606), (ZI396), (ZI400), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (ZI396) ) == type_func_tag ) {
	check_weak_func ( (ZI396), 0 ) ;
	(ZI548) = make_func_decl ( (ZI606), (ZI396), (ZI400), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZI548) = make_object_decl ( (ZI606), (ZI396), (ZI400), def ) ;
    }
    if ( IS_id_type_alias ( (ZI548) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI548) ) ) ;
	bs |= (ZI659) ;
	COPY_btype ( id_type_alias_rep ( (ZI548) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	ZR793 (ZI548, &ZI405);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    int def = init_object ( (ZI548), (ZI405) ) ;
    if ( do_dump ) dump_declare ( (ZI548), &decl_loc, def ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1031(BASE_TYPE *ZI670, IDENTIFIER *ZI400, TYPE *ZO396)
{
    TYPE ZI396;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    IDENTIFIER ZI421;
	    int ZI586;
	    IDENTIFIER ZI673;

	    {

    (ZI421) = begin_class_defn ( (*ZI400), (*ZI670), cinfo_none, NULL_type ) ;
    (ZI586) = in_function_defn ;
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
	    ZR663 ();
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

    (ZI673) = end_class_defn ( (ZI421) ) ;
    in_function_defn = (ZI586) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI396) ) ;
    COPY_id ( type_name ( (ZI396) ), (ZI673) ) ;
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

    MAKE_type_pre ( cv_none, (*ZI670), qual_none, (ZI396) ) ;
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
ZR560(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI689;
	TYPE ZI1095;
	CV_SPEC ZI691;
	DECL_SPEC ZI1096;
	BASE_TYPE ZI659;
	TYPE ZI690;
	CV_SPEC ZI631;
	DECL_SPEC ZI717;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	ZR715 (&ZI689, &ZI1095, &ZI691, &ZI1096);
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
	ZR725 (&ZI689, &ZI1095, &ZI691, &ZI1096, &ZI659, &ZI690, &ZI631, &ZI717);
	ZR814 (&ZI659, &ZI690, &ZI631, &ZI717);
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
ZR1032(BASE_TYPE *ZI659, TYPE *ZI421, CV_SPEC *ZI631)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( dspec_none, NULL_type, (*ZI659), (*ZI421), (*ZI631), last_lex_token, 1 ) ;
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

    (ZI396) = complete_pre_type ( (*ZI659), (*ZI421), (*ZI631), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR825 (ZI396, *ZI659);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			ZR826 (ZI396, *ZI659);
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
ZR621(EXP *ZO405)
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
	    ZR529 (&ZI417);
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
	    ZR529 (&ZI417);
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
ZR907(EXP ZI905, EXP *ZO906)
{
    EXP ZI906;

  ZL2_907:;
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
	    ZR483 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI405) = make_relation_exp ( (ZI461), (ZI905), (ZI449) ) ;
	    }
	    ZI905 = ZI405;
	    goto ZL2_907;
	}
	/*UNREACHED*/
      default:
	{
	    ZI906 = ZI905;
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
    *ZO906 = ZI906;
}

void
ZR671(BASE_TYPE *ZO670)
{
    BASE_TYPE ZI670;

    switch (CURRENT_TERMINAL) {
      case 118:
	{
	    ADVANCE_LEXER;
	    {
 (ZI670) = btype_struct ; 
	    }
	}
	break;
      case 121:
	{
	    ADVANCE_LEXER;
	    {
 (ZI670) = btype_union ; 
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
    *ZO670 = ZI670;
}

void
ZR790(IDENTIFIER ZI548, SID_LIST_EXP *ZO421)
{
    SID_LIST_EXP ZI421;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI449;
	EXP ZI417;
	SID_LIST_EXP ZI424;

	ZR789 (ZI548, &ZI449);
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
		    ZR1073 (&ZI548, &ZI424);
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
	BASE_TYPE ZI659;
	TYPE ZI421;
	CV_SPEC ZI631;
	TYPE ZI424;

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
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO396 = ZI396;
}

void
ZR488(void)
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
ZR492(EXP *ZO898)
{
    EXP ZI898;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR489 (&ZI405);
	ZR899 (ZI405, &ZI898);
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
    *ZO898 = ZI898;
}

void
ZR911(EXP ZI909, EXP *ZO910)
{
    EXP ZI910;

  ZL2_911:;
    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR480 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_shift_exp ( lex_lshift, (ZI909), (ZI449) ) ;
	    }
	    ZI909 = ZI405;
	    goto ZL2_911;
	}
	/*UNREACHED*/
      case 75:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR480 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_shift_exp ( lex_rshift, (ZI909), (ZI449) ) ;
	    }
	    ZI909 = ZI405;
	    goto ZL2_911;
	}
	/*UNREACHED*/
      default:
	{
	    ZI910 = ZI909;
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
    *ZO910 = ZI910;
}

void
ZR512(EXP *ZO405)
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
	ZR1030 (&ZI405);
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
parse_type_param(IDENTIFIER *ZO548)
{
    IDENTIFIER ZI548;

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

    (ZI548) = NULL_id ;
	}
    }
    *ZO548 = ZI548;
}

void
ZR448(EXP *ZO922)
{
    EXP ZI922;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI405;

	ZR416 (&ZI405);
	ZR923 (ZI405, &ZI922);
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
    *ZO922 = ZI922;
}

void
ZR555(EXP *ZO405)
{
    EXP ZI405;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI1007;
	    EXP ZI1008;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    {
 (ZI1007) = lex_alignof ; 
	    }
	    ZR462 (ZI1007, &ZI1008);
	    ZR1015 (&ZI1008, &ZI1026);
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
      case 23:
	{
	    EXP ZI1019;
	    EXP ZI1020;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1019 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR923 (ZI1019, &ZI1020);
	    ZR1015 (&ZI1020, &ZI1026);
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
	    EXP ZI1081;
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
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    ZR460 (&ZI1081);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI962) = make_cast_exp ( type_void, (ZI1081), 0 ) ;
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
	    ZR951 (&ZI949, &ZI1026);
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
      case 210:
	{
	    EXP ZI1016;
	    EXP ZI1017;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    {

    (ZI1016) = make_ellipsis_exp () ;
	    }
	    ZR923 (ZI1016, &ZI1017);
	    ZR1015 (&ZI1017, &ZI1026);
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
      case 1:
	{
	    IDENTIFIER ZI400;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1082 (&ZI400, &ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 346:
	{
	    ADVANCE_LEXER;
	    ZR1079 (&ZI405);
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
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    ZR459 (&ZI988);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI989) = make_prefix_exp ( lex_minus_Hminus, (ZI988) ) ;
	    }
	    ZR1015 (&ZI989, &ZI1026);
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
      case 65:
	{
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    ZR984 (&ZI1026);
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
      case 71:
	{
	    EXP ZI985;
	    EXP ZI986;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    ZR459 (&ZI985);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI986) = make_prefix_exp ( lex_plus_Hplus, (ZI985) ) ;
	    }
	    ZR1015 (&ZI986, &ZI1026);
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
	    int ZI1004;
	    EXP ZI1005;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    {
 (ZI1004) = lex_sizeof ; 
	    }
	    ZR462 (ZI1004, &ZI1005);
	    ZR1015 (&ZI1005, &ZI1026);
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
      case 78:
	{
	    EXP ZI991;
	    EXP ZI992;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ADVANCE_LEXER;
	    ZR460 (&ZI991);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI992) = make_indir_exp ( (ZI991) ) ;
	    }
	    ZR1015 (&ZI992, &ZI1026);
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
      case 4:
	{
	    IDENTIFIER ZI400;

	    {

    ZI400 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1083 (&ZI400, &ZI405);
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
      case 33:
	{
	    EXP ZI994;
	    EXP ZI995;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

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
	    ZR1015 (&ZI995, &ZI1026);
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
      case 126:
	{
	    ZR624 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 289: case 323:
	{
	    ZR621 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 96: case 100: case 223:
	{
	    ZR530 ();
	    ZR1080 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI1074;
	    EXP ZI417;
	    int ZI538;

	    ZR511 (&ZI1074);
	    ZR1076 (&ZI1074, &ZI417);
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
      case 101: case 107: case 125:
	{
	    ZR603 (&ZI405);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    ZR615 (&ZI405);
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
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

	    ZR410 (&ZI1010);
	    ZR923 (ZI1010, &ZI1011);
	    ZR1015 (&ZI1011, &ZI1026);
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
      case 62:
	{
	    EXP ZI997;
	    EXP ZI998;
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

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
	    ZR1015 (&ZI998, &ZI1026);
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
      case 26: case 109: case 119:
	{
	    ZR581 (&ZI405);
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
	    EXP ZI1026;
	    EXP ZI417;
	    int ZI538;

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
	    ZR1015 (&ZI1002, &ZI1026);
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
ZR663(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_663:;
    {
	BASE_TYPE ZI689;
	TYPE ZI690;
	CV_SPEC ZI691;
	BASE_TYPE ZI659;
	TYPE ZI421;
	CV_SPEC ZI631;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR687 (&ZI689, &ZI690, &ZI691);
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
	ZR700 (&ZI689, &ZI690, &ZI691, &ZI659, &ZI421, &ZI631);
	ZR1032 (&ZI659, &ZI421, &ZI631);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	} else {
	    goto ZL2_663;
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
ZR915(EXP ZI913, EXP *ZO914)
{
    EXP ZI914;

  ZL2_915:;
    switch (CURRENT_TERMINAL) {
      case 59:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR477 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_minus_exp ( (ZI913), (ZI449) ) ;
	    }
	    ZI913 = ZI405;
	    goto ZL2_915;
	}
	/*UNREACHED*/
      case 69:
	{
	    EXP ZI449;
	    EXP ZI405;

	    ADVANCE_LEXER;
	    ZR477 (&ZI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI405) = make_plus_exp ( (ZI913), (ZI449) ) ;
	    }
	    ZI913 = ZI405;
	    goto ZL2_915;
	}
	/*UNREACHED*/
      default:
	{
	    ZI914 = ZI913;
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
    *ZO914 = ZI914;
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
		    int ZI1070;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    {
 (ZI1070) = lex_alignof ; 
		    }
		    ZR462 (ZI1070, &ZI417);
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
		    EXP ZI1101;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1101 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
		    }
		    ADVANCE_LEXER;
		    ZR923 (ZI1101, &ZI417);
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
		    EXP ZI1102;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    {

    (ZI1102) = make_ellipsis_exp () ;
		    }
		    ZR923 (ZI1102, &ZI417);
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
		    EXP ZI1103;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    {

    ZI400 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		    {

    (ZI1103) = make_id_exp ( (ZI400) ) ;
		    }
		    ZR923 (ZI1103, &ZI417);
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
		    EXP ZI1063;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    ZR459 (&ZI1063);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_prefix_exp ( lex_minus_Hminus, (ZI1063) ) ;
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
		    ZR1072 (&ZI461, &ZI463, &ZI464, &ZI468);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 71:
		{
		    EXP ZI1062;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    ZR459 (&ZI1062);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_prefix_exp ( lex_plus_Hplus, (ZI1062) ) ;
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
		    int ZI1069;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    {
 (ZI1069) = lex_sizeof ; 
		    }
		    ZR462 (ZI1069, &ZI417);
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
		    EXP ZI1064;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ADVANCE_LEXER;
		    ZR460 (&ZI1064);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_indir_exp ( (ZI1064) ) ;
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
		    EXP ZI1065;
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
		    ZR460 (&ZI1065);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_ref_exp ( (ZI1065), 0 ) ;
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
		    EXP ZI1104;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    ZR410 (&ZI1104);
		    ZR923 (ZI1104, &ZI417);
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
		    EXP ZI1066;
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
		    ZR460 (&ZI1066);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_not_exp ( (ZI1066) ) ;
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
		    int ZI1067;
		    EXP ZI1068;
		    EXP ZI417;
		    int ZI466;
		    int ZI467;
		    TYPE ZI396;

		    {
 (ZI1067) = crt_lex_token ; 
		    }
		    ZR470 ();
		    ZR460 (&ZI1068);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI417) = make_uminus_exp ( (ZI1067), (ZI1068) ) ;
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
ZR1044(TYPE *ZI421, BASE_TYPE *ZI424, IDENTIFIER *ZI1043)
{
    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    EXP ZI468;
	    TYPE ZI396;

	    {

    IDENTIFIER pid = underlying_id ( (*ZI1043) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ADVANCE_LEXER;
	    ZR519 (&ZI468);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1043) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI396) = make_bitfield_type ( (*ZI421), (*ZI424), (ZI468), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI396), (*ZI1043), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI1042;
	    TYPE ZI1036;
	    IDENTIFIER ZI400;
	    TYPE ZI396;

	    {

    (ZI1042) = NULL_type ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (*ZI1043) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR869 (ZI1042, *ZI1043, &ZI1036, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI396) = ( IS_NULL_type ( (ZI1036) ) ? (*ZI421) : inject_pre_type ( (ZI1036), (*ZI421), 1 ) ) ;
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
ZR919(EXP ZI917, EXP *ZO918)
{
    EXP ZI918;

  ZL2_919:;
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

    (ZI405) = make_mult_exp ( lex_div, (ZI917), (ZI449) ) ;
	    }
	    ZI917 = ZI405;
	    goto ZL2_919;
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

    (ZI405) = make_rem_exp ( (ZI917), (ZI449) ) ;
	    }
	    ZI917 = ZI405;
	    goto ZL2_919;
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

    (ZI405) = make_mult_exp ( lex_star, (ZI917), (ZI449) ) ;
	    }
	    ZI917 = ZI405;
	    goto ZL2_919;
	}
	/*UNREACHED*/
      default:
	{
	    ZI918 = ZI917;
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
    *ZO918 = ZI918;
}

void
ZR1047(TYPE *ZO855, IDENTIFIER *ZO856)
{
    TYPE ZI855;
    IDENTIFIER ZI856;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1048;
	TYPE ZI1049;
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
	ZR857 (ZI1049, ZI1048, &ZI396, &ZI400);
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
	ZR857 (ZI396, ZI400, &ZI855, &ZI856);
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
	    ZR1047 (&ZI396, &ZI400);
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
	    ZR857 (ZI396, ZI400, &ZI855, &ZI856);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1046;
	    int ZI748;
	    TYPE ZI1052;
	    IDENTIFIER ZI1053;
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
	    ZR857 (ZI1052, ZI1053, &ZI396, &ZI400);
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
	    ZR857 (ZI396, ZI400, &ZI855, &ZI856);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;
	    TYPE ZI1050;
	    IDENTIFIER ZI1051;
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
	    ZR857 (ZI1050, ZI1051, &ZI396, &ZI400);
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
	    ZR857 (ZI396, ZI400, &ZI855, &ZI856);
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

	    ZR732 (&ZI421);
	    ZR765 (&ZI424, &ZI400);
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
	    ZR857 (ZI396, ZI400, &ZI855, &ZI856);
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
	    IDENTIFIER ZI1045;
	    TYPE ZI569;
	    TYPE ZI396;
	    IDENTIFIER ZI400;

	    {

    (ZI1045) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1045) ) ;
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
	    {

    HASHID nm = lookup_anon () ;
    (ZI400) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI400) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR857 (ZI396, ZI400, &ZI855, &ZI856);
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
    *ZO855 = ZI855;
    *ZO856 = ZI856;
}

void
ZR779(void)
{
  ZL2_779:;
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    IDENTIFIER ZI400;

	    ADVANCE_LEXER;
	    ZR778 (&ZI400);
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
	    goto ZL2_779;
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
ZR765(TYPE *ZO396, IDENTIFIER *ZO400)
{
    TYPE ZI396;
    IDENTIFIER ZI400;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER ZI1048;
	TYPE ZI1049;

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
	ZR857 (ZI1049, ZI1048, &ZI396, &ZI400);
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
	    ZR1047 (&ZI396, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI1046;
	    int ZI748;
	    TYPE ZI1052;
	    IDENTIFIER ZI1053;

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
	    ZR857 (ZI1052, ZI1053, &ZI396, &ZI400);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI405;
	    TYPE ZI1050;
	    IDENTIFIER ZI1051;

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
	    ZR857 (ZI1050, ZI1051, &ZI396, &ZI400);
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
	    ZR765 (&ZI424, &ZI400);
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
ZR923(EXP ZI921, EXP *ZO922)
{
    EXP ZI922;

  ZL2_923:;
    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    EXP ZI405;

	    ADVANCE_LEXER;
	    {

    (ZI405) = make_postfix_exp ( lex_minus_Hminus, (ZI921) ) ;
	    }
	    ZI921 = ZI405;
	    goto ZL2_923;
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

    (ZI405) = make_func_exp ( (ZI921), (ZI421), 0 ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZI921 = ZI405;
	    goto ZL2_923;
	}
	/*UNREACHED*/
      case 71:
	{
	    EXP ZI405;

	    ADVANCE_LEXER;
	    {

    (ZI405) = make_postfix_exp ( lex_plus_Hplus, (ZI921) ) ;
	    }
	    ZI921 = ZI405;
	    goto ZL2_923;
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

    (ZI405) = make_index_exp ( (ZI921), (ZI449) ) ;
	    }
	    ZI921 = ZI405;
	    goto ZL2_923;
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

    (ZI449) = begin_field_exp ( lex_arrow, (ZI921), &(ZI396), &(ZI427) ) ;
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
	    ZI921 = ZI405;
	    goto ZL2_923;
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

    (ZI449) = begin_field_exp ( lex_dot, (ZI921), &(ZI396), &(ZI427) ) ;
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
	    ZI921 = ZI405;
	    goto ZL2_923;
	}
	/*UNREACHED*/
      default:
	{
	    ZI922 = ZI921;
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
    *ZO922 = ZI922;
}

/* END OF FILE */
