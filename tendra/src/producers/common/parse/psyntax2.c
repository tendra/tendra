/*
 * Automatically generated from the files:
 *	psyntax.sid
 * and
 *	psyntax.act
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
#include "tok_ops.h"
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
#include "printf.h"
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

typedef LIST(IDENTIFIER) SID_LIST_ID;


/*
     DECLARE FUNCTIONS

     The function declarations are included at this point so that the
     type definitions are in scope.
*/

#include "psyntax.h"
extern void parse_tok_type(TYPE *);
extern void parse_mem_type(TYPE *);
extern void parse_operator(IDENTIFIER *);


/*
    COMPILATION MODE

    The output of sid is automatically generated.  Hence it is not
    necessarily appropriate to apply the same level of checking to this
    as to the rest of the program.  These pragmas describe the relaxations
    allowed for the sid output.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA variable analysis off
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif



void
XR808(void)
{
    switch (CURRENT_TERMINAL) {
      case 213:
	{
	    IDENTIFIER XI376;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 293:
		    {
			ADVANCE_LEXER;
			XR507 (&XI378);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{
 (XI378) = ( unsigned ) OPTION_ON ; 
			}
		    }
		    break;
		}
	    }
	    {

    use_option ( (XI376), (XI378) ) ;
	    }
	}
	break;
      case 215:
	{
	    int XI710;

	    XR759 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    if ( (XI710) >= 0 ) {
	no_error_args = 1 ;
	report ( crt_loc, make_error ( (XI710) ) ) ;
	no_error_args = 0 ;
    }
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR809(void)
{
    switch (CURRENT_TERMINAL) {
      case 215:
	{
	    int XI710;
	    EXP XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 252:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_VAL_maximum_error ; 
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI378 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    set_value ( (XI710), (XI378), ( unsigned long ) 0 ) ;
	    }
	}
	break;
      case 262:
	{
	    EXP XI378;
	    unsigned XI474;
	    int XI710;
	    int XI716;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 252:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI378 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    XR509 (&XI474);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI710) = OPT_VAL_name_limit ; 
	    }
	    {
 (XI716) = OPT_name_limit ; 
	    }
	    {

    set_value ( (XI710), (XI378), ( unsigned long ) 0 ) ;
	    }
	    {

    set_option ( (XI716), (XI474) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR810(void)
{
    switch (CURRENT_TERMINAL) {
      case 216:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 274:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_escape_overflow ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20:
	{
	    EXP XI410;

	    {
		switch (CURRENT_TERMINAL) {
		  case 17: case 18:
		    {
			{
			    switch (CURRENT_TERMINAL) {
			      case 17:
				{
				    {

    XI410 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 18:
				{
				    {

    XI410 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      default:
				goto XL1;
			    }
			}
		    }
		    break;
		  case 19: case 20:
		    {
			{
			    switch (CURRENT_TERMINAL) {
			      case 19:
				{
				    {

    XI410 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 20:
				{
				    {

    XI410 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      default:
				goto XL1;
			    }
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 179:
		    {
			EXP XI445;

			ADVANCE_LEXER;
			{
			    switch (CURRENT_TERMINAL) {
			      case 17:
				{
				    {

    XI445 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 18:
				{
				    {

    XI445 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      default:
				goto XL1;
			    }
			}
			{

    set_character ( (XI410), (XI445) ) ;
			}
			switch (CURRENT_TERMINAL) {
			  case 172:
			    break;
			  default:
			    goto XL1;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 205:
		    {
			EXP XI445;

			ADVANCE_LEXER;
			{

    (XI445) = NULL_exp ;
			}
			{

    set_character ( (XI410), (XI445) ) ;
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR811(void)
{
    switch (CURRENT_TERMINAL) {
      case 326:
	{
	    EXP XI449;
	    int XI710;
	    EXP XI378;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    XI449 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    XI449 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    STRING s = DEREF_str ( exp_string_lit_str ( (XI449) ) ) ;
    (XI710) = find_value_no ( s, 0 ) ;
    if ( (XI710) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI378 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    set_value ( (XI710), (XI378), ( unsigned long ) 0 ) ;
	    }
	}
	break;
      case 19: case 20:
	{
	    EXP XI449;
	    int XI710;
	    unsigned XI378;

	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    XI449 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    XI449 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    STRING s = DEREF_str ( exp_string_lit_str ( (XI449) ) ) ;
    (XI710) = find_option_no ( s, 0 ) ;
    if ( (XI710) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
	    }
	    XR508 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR812(void)
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    ADVANCE_LEXER;
	    {

    preserve_all = 1 ;
	    }
	}
	break;
      default:
	{
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    XR497 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR727(unsigned *XO474)
{
    unsigned XI474;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    XR836 (&XI474);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI474) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO474 = XI474;
}

void
XR813(TYPE *XI398)
{
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
		    goto XL1;
		}
	    }
	    {

    accept_ellipsis ( (*XI398) ) ;
	    }
	}
	break;
      default:
	{
	    TYPE XI449;

	    {

    (XI449) = type_error ;
    parse_tok_type ( &(XI449) ) ;
    object_type ( (XI449), null_tag ) ;
	    }
	    {

    accept_argument ( (*XI398), (XI449) ) ;
	    }
	}
	break;
      case 355:
	return;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR724(unsigned *XO378, unsigned *XO474)
{
    unsigned XI378;
    unsigned XI474;

    switch (CURRENT_TERMINAL) {
      case 271:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_OFF ; 
	    }
	    {
 (XI474) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 65:
	{
	    unsigned XI445;

	    ADVANCE_LEXER;
	    XR723 (&XI474);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 272:
		    {
			ADVANCE_LEXER;
			{
 (XI445) = ( unsigned ) OPTION_OFF ; 
			}
		    }
		    break;
		  case 331:
		    {
			ADVANCE_LEXER;
			{
 (XI445) = ( unsigned ) OPTION_WARN ; 
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    XI378 = XI445;
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO378 = XI378;
    *XO474 = XI474;
}

void
XR814(void)
{
    switch (CURRENT_TERMINAL) {
      case 187:
	{
	    TYPE XI398;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 255:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
	    }
	    {

    set_char_lit ( (XI398) ) ;
	    }
	}
	break;
      case 256:
	{
	    int XI445;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 313:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 111:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 111:
		    {
			ADVANCE_LEXER;
			{
 (XI445) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (XI445) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    set_long_long_type ( (XI445) ) ;
	    }
	}
	break;
      case 302:
	{
	    IDENTIFIER XI376;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 139:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 83:
		    {
			ADVANCE_LEXER;
			{

    (XI376) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
			}
		    }
		    break;
		  case 1: case 2: case 3: case 4:
		    {
			{
			    switch (CURRENT_TERMINAL) {
			      case 1:
				{
				    {

    XI376 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 3:
				{
				    {

    XI376 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 4:
				{
				    {

    XI376 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 2:
				{
				    {

    XI376 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      default:
				goto XL1;
			    }
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    set_std_namespace ( (XI376) ) ;
	    }
	}
	break;
      case 304:
	{
	    CV_SPEC XI589;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 255:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 266:
		    {
			ADVANCE_LEXER;
			{
 (XI589) = cv_none ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (XI589) = cv_const ; 
			}
		    }
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 98:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    set_string_qual ( (XI589) ) ;
	    }
	}
	break;
      case 156: case 286: case 299:
	{
	    BASE_TYPE XI585;
	    TYPE XI398;

	    {
		switch (CURRENT_TERMINAL) {
		  case 286:
		    {
			ADVANCE_LEXER;
			{
 (XI585) = btype_ptrdiff_t ; 
			}
		    }
		    break;
		  case 299:
		    {
			ADVANCE_LEXER;
			{
 (XI585) = btype_size_t ; 
			}
		    }
		    break;
		  case 156:
		    {
			ADVANCE_LEXER;
			{
 (XI585) = btype_wchar_t ; 
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
	    }
	    {

    set_builtin_type ( (XI585), (XI398) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR815(void)
{
    switch (CURRENT_TERMINAL) {
      case 215: case 262:
	{
	    XR809 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 156: case 187: case 256: case 286: case 299:
      case 302: case 304:
	{
	    XR814 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR816(void)
{
    switch (CURRENT_TERMINAL) {
      case 195:
	{
	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    XR495 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 47: case 210:
	{
	    int XI710;
	    unsigned XI378;

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
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 232:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ellipsis_ident ; 
	    }
	    {
 (XI378) = ( unsigned ) OPTION_OFF ; 
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR817(void)
{
    switch (CURRENT_TERMINAL) {
      case 115: case 122: case 208:
	{
	    BASE_TYPE XI585;

	    {
		switch (CURRENT_TERMINAL) {
		  case 208:
		    {
			ADVANCE_LEXER;
			{
 (XI585) = btype_none ; 
			}
		    }
		    break;
		  case 115:
		    {
			ADVANCE_LEXER;
			{
 (XI585) = btype_signed ; 
			}
		    }
		    break;
		  case 122:
		    {
			ADVANCE_LEXER;
			{
 (XI585) = btype_unsigned ; 
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    set_char_sign ( (XI585) ) ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 216:
	{
	    XR810 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR818(void)
{
    switch (CURRENT_TERMINAL) {
      case 312:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_token_redef ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 313:
	{
	    TYPE XI398;
	    TYPE XI449;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 48:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI449) = type_error ;
    parse_tok_type ( &(XI449) ) ;
    object_type ( (XI449), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_compatible_type ( (XI398), (XI449), (XI378) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR819(void)
{
    switch (CURRENT_TERMINAL) {
      case 270:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 118:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 44:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 121:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 94:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_init_struct ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI376;

	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 172:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    allow_initialiser ( (XI376) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR820(void)
{
    switch (CURRENT_TERMINAL) {
      case 174:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR711 (&XI710);
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 172:
	{
	    {

    rescan_pragma ( lex_allow ) ;
    RESCAN_LEXER ;
	    }
	    XR495 ();
	    switch (CURRENT_TERMINAL) {
	      case 172:
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR529(int *XO449)
{
    int XI449;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    XR851 (&XI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    XR850 (&XI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI449) = SUFFIX_NONE ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO449 = XI449;
}

void
XR821(void)
{
    switch (CURRENT_TERMINAL) {
      case 255:
	{
	    int XI445;
	    int XI449;

	    ADVANCE_LEXER;
	    {

    pragma_number = 1 ;
	    }
	    XR528 (&XI445);
	    XR529 (&XI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    begin_literal ( (XI445), (XI449) ) ;
	    }
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    XR533 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 141: case 274:
	{
	    int XI710;
	    unsigned XI378;

	    XR797 (&XI710);
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR495(void)
{
  XL2_495:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI376;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    allow_conversion ( (XI376) ) ;
	    }
	    goto XL2_495;
	}
	/*UNREACHED*/
      case 355:
	return;
      default:
	break;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR712(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    XR830 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI710) = OPT_discard ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR822(void)
{
    switch (CURRENT_TERMINAL) {
      case 312:
	{
	    int XI474;

	    ADVANCE_LEXER;
	    {
 (XI474) = lex_undef ; 
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    XR479 (&XI474);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 251:
	{
	    IDENTIFIER XI376;

	    XR550 (&XI376);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    undef_keyword ( (XI376) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR714(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 107:
	{
	    ADVANCE_LEXER;
	    XR841 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI710) = OPT_infer_int ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR528(int *XO445)
{
    int XI445;

    switch (CURRENT_TERMINAL) {
      case 196:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = BASE_DECIMAL ; 
	    }
	}
	break;
      case 229:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = BASE_HEXADECIMAL ; 
	    }
	}
	break;
      case 269:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = BASE_OCTAL ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO445 = XI445;
}

void
XR533(void)
{
  XL2_533:;
    switch (CURRENT_TERMINAL) {
      case 72:
	{
	    ADVANCE_LEXER;
	    {

    add_range_literal ( NULL_exp, 1 ) ;
	    }
	    XR530 ();
	    {
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto XL1;
		}
		{
		    switch (CURRENT_TERMINAL) {
		      case 67:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    goto XL2_533;
	}
	/*UNREACHED*/
      case 78:
	{
	    ADVANCE_LEXER;
	    {

    add_range_literal ( NULL_exp, 0 ) ;
	    }
	    XR530 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 21:
	{
	    EXP XI378;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI378 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    add_range_literal ( (XI378), 2 ) ;
	    }
	    XR530 ();
	    {
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto XL1;
		}
		{
		    switch (CURRENT_TERMINAL) {
		      case 67:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    goto XL2_533;
	}
	/*UNREACHED*/
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR733(unsigned *XO446)
{
    unsigned XI446;

    switch (CURRENT_TERMINAL) {
      case 130:
	{
	    ADVANCE_LEXER;
	    {
 (XI446) = CAST_CONST ; 
	    }
	}
	break;
      case 145:
	{
	    ADVANCE_LEXER;
	    {
 (XI446) = CAST_REINTERP ; 
	    }
	}
	break;
      case 146:
	{
	    ADVANCE_LEXER;
	    {
 (XI446) = CAST_STATIC ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO446 = XI446;
}

void
XR399(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 308:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI398) = 0 ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *XO398 = XI398;
}

void
XR828(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 174:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR712 (&XI710);
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI398) = lex_unused ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO398 = XI398;
}

void
XR829(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 156: case 187: case 215: case 256: case 262:
      case 286: case 299: case 302: case 304:
	{
	    XR815 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI398) = lex_set ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO398 = XI398;
}

void
XR830(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 228:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 113:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_discard_func ; 
	    }
	}
	break;
      case 117:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_discard_static ; 
	    }
	}
	break;
      case 326:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_discard_value ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR831(TOKEN *XO401)
{
    TOKEN XI401;

    switch (CURRENT_TERMINAL) {
      case 115:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_signed | btype_int ) ;
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_unsigned | btype_int ) ;
	    }
	}
	break;
      default:
	{
	    {

    (XI401) = make_type_token ( btype_int ) ;
	    }
	}
	break;
      case 355:
	return;
    }
    *XO401 = XI401;
}

void
XR832(TOKEN *XO401)
{
    TOKEN XI401;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TOKEN XI410;
	    SID_LIST_ID XI403;
	    TOKEN XI445;
	    TOKEN XI407;

	    ADVANCE_LEXER;
	    {

    (XI410) = begin_proc_token () ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 177: case 188: case 218: case 225: case 227:
		  case 250: case 261: case 263: case 282: case 296:
		  case 303: case 305: case 314: case 320: case 328:
		    {
			XR414 (&XI403);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (XI403) = NULL_list ( IDENTIFIER ) ;
			}
		    }
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI445) = cont_proc_token ( (XI410), (XI403), (XI403) ) ;
	    }
	    XR397 (&XI407);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    (XI401) = end_proc_token ( (XI445), (XI407) ) ;
	    }
	}
	break;
      case 64:
	{
	    TOKEN XI410;
	    SID_LIST_ID XI451;
	    SID_LIST_ID XI403;
	    SID_LIST_ID XI454;
	    SID_LIST_ID XI406;
	    TOKEN XI445;
	    TOKEN XI407;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 64:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    (XI410) = begin_proc_token () ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 177: case 188: case 218: case 225: case 227:
		  case 250: case 261: case 263: case 282: case 296:
		  case 303: case 305: case 314: case 320: case 328:
		    {
			XR404 (&XI451);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (XI451) = NULL_list ( IDENTIFIER ) ;
			}
		    }
		    break;
		}
	    }
	    XI403 = XI451;
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 67:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 218: case 261: case 282: case 303: case 314:
		    {
			XR409 (XI403, &XI454);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (XI454) = NULL_list ( IDENTIFIER ) ;
			}
		    }
		    break;
		}
	    }
	    XI406 = XI454;
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 38:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    (XI445) = cont_proc_token ( (XI410), (XI403), (XI406) ) ;
	    }
	    XR397 (&XI407);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    (XI401) = end_proc_token ( (XI445), (XI407) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO401 = XI401;
}

void
XR833(SID_LIST_ID *XO406)
{
    SID_LIST_ID XI406;

    switch (CURRENT_TERMINAL) {
      case 177: case 188: case 218: case 225: case 227:
      case 250: case 261: case 263: case 282: case 296:
      case 303: case 305: case 314: case 320: case 328:
	{
	    XR414 (&XI406);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
	    }
	    {

    (XI406) = NULL_list ( IDENTIFIER ) ;
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO406 = XI406;
}

void
XR834(SID_LIST_ID *XO406)
{
    SID_LIST_ID XI406;

    switch (CURRENT_TERMINAL) {
      case 177: case 188: case 218: case 225: case 227:
      case 250: case 261: case 263: case 282: case 296:
      case 303: case 305: case 314: case 320: case 328:
	{
	    XR404 (&XI406);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
	    }
	    {

    (XI406) = NULL_list ( IDENTIFIER ) ;
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO406 = XI406;
}

void
XR835(SID_LIST_ID *XI407, SID_LIST_ID *XO406)
{
    SID_LIST_ID XI406;

    switch (CURRENT_TERMINAL) {
      case 218: case 261: case 282: case 303: case 314:
	{
	    XR409 (*XI407, &XI406);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
	    }
	    {

    (XI406) = NULL_list ( IDENTIFIER ) ;
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO406 = XI406;
}

void
XR836(unsigned *XO474)
{
    unsigned XI474;

    switch (CURRENT_TERMINAL) {
      case 192:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI474) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 243:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI474) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO474 = XI474;
}

void
XR839(unsigned *XI837, unsigned *XO446)
{
    unsigned XI446;

    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    unsigned XI445;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 67:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    XR734 (&XI445);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI446) = ( (*XI837) | (XI445) ) ; 
	    }
	}
	break;
      default:
	{
	    XI446 = *XI837;
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO446 = XI446;
}

void
XR840(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 169:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 194:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_empty_body ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI710) = OPT_semicolon_extra ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR841(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 44:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 124:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_infer_int_cv ; 
	    }
	}
	break;
      case 221:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 197:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_dspec_none ; 
	    }
	}
	break;
      case 228:
	{
	    ADVANCE_LEXER;
	    XR842 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR412(IDENTIFIER *XO376)
{
    IDENTIFIER XI376;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TOKEN XI401;
	int XI398;
	IDENTIFIER XI402;

	XR397 (&XI401);
	XR399 (&XI398);
	{
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 3: case 4:
		{
		    {
			switch (CURRENT_TERMINAL) {
			  case 1:
			    {
				{

    XI402 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 3:
			    {
				{

    XI402 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    XI402 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    XI402 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  default:
			    goto XL1;
			}
		    }
		}
		break;
	      default:
		{
		    {

    HASHID nm = lookup_anon () ;
    (XI402) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	{

    (XI376) = make_tok_param ( (XI401), (XI398), (XI402) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO376 = XI376;
}

void
XR842(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 176:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_param_impl ; 
	    }
	}
	break;
      case 113:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_dspec_none_func ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR843(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 110:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 59:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR845 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 276:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 59:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR844 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 59:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 276:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 237:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_ptr_void_ptr ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR844(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 110:
	{
	    ADVANCE_LEXER;
	    XR849 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 276:
	{
	    ADVANCE_LEXER;
	    XR847 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 237:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_ptr_ptr_void ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR530(void)
{
    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    TYPE XI398;

	    ADVANCE_LEXER;
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
	    }
	    {

    add_type_literal ( (XI398) ) ;
	    }
	}
	break;
      case 78:
	{
	    ADVANCE_LEXER;
	    XR853 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR845(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 104:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 237:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_enum ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    XR848 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 276:
	{
	    ADVANCE_LEXER;
	    XR849 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR847(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_ptr_ptr ; 
	    }
	}
	break;
      case 133:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_ptr_ptr_expl ; 
	    }
	}
	break;
      case 237:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_ptr_ptr_impl ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR848(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_int ; 
	    }
	}
	break;
      case 133:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_int_expl ; 
	    }
	}
	break;
      case 237:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_int_impl ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR849(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_ptr ; 
	    }
	}
	break;
      case 133:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_ptr_expl ; 
	    }
	}
	break;
      case 237:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_int_ptr_impl ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR850(int *XO449)
{
    int XI449;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    XR852 (&XI449);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI449) = SUFFIX_U ; 
	    }
	}
	break;
      case 355:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO449 = XI449;
}

void
XR851(int *XO449)
{
    int XI449;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (XI449) = SUFFIX_LL ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI449) = SUFFIX_L ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *XO449 = XI449;
}

void
XR741(int *XO710)
{
    int XI710;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP XI449;

	switch (CURRENT_TERMINAL) {
	  case 273:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 19:
		{
		    {

    XI449 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    XI449 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto XL1;
	    }
	}
	{

    STRING s = DEREF_str ( exp_string_lit_str ( (XI449) ) ) ;
    (XI710) = find_option_no ( s, 0 ) ;
    if ( (XI710) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO710 = XI710;
}

void
XR852(int *XO449)
{
    int XI449;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (XI449) = SUFFIX_ULL ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI449) = SUFFIX_UL ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *XO449 = XI449;
}

void
XR853(void)
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    unsigned XI410;

	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 172: case 205: case 331:
		    {
			XR507 (&XI410);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{
 (XI410) = ( unsigned ) OPTION_ON ; 
			}
		    }
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    add_token_literal ( NULL_id, (XI410) ) ;
	    }
	}
	break;
      case 41: case 172: case 205: case 331:
	{
	    unsigned XI410;
	    IDENTIFIER XI376;

	    {

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 172: case 205: case 331:
		    {
			XR507 (&XI410);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{
 (XI410) = ( unsigned ) OPTION_OFF ; 
			}
		    }
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    add_token_literal ( (XI376), (XI410) ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR854(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 326:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_discard ; 
	    }
	}
	break;
      case 327:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_unused ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO398 = XI398;
}

void
XR400(IDENTIFIER *XO376)
{
    IDENTIFIER XI376;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TOKEN XI401;
	int XI398;
	IDENTIFIER XI402;

	XR397 (&XI401);
	XR399 (&XI398);
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    XI402 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    {

    XI402 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    XI402 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    XI402 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	}
	{

    (XI376) = make_tok_param ( (XI401), (XI398), (XI402) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO376 = XI376;
}

void
XR855(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 289:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_reachable ; 
	    }
	}
	break;
      case 323:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_unreachable ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI398) = lex_set ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *XO398 = XI398;
}

void
XR510(int *XO378)
{
    int XI378;

    switch (CURRENT_TERMINAL) {
      case 172:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = OPT_none ; 
	    }
	}
	break;
      case 205:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = OPT_error ; 
	    }
	}
	break;
      case 271:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = OPT_none ; 
	    }
	}
	break;
      case 272:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = OPT_error ; 
	    }
	}
	break;
      case 331:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = OPT_warning ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO378 = XI378;
}

void
XR497(void)
{
  XL2_497:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI376;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    preserve_id ( (XI376), lex_preserve ) ;
	    }
	    goto XL2_497;
	}
	/*UNREACHED*/
      case 355:
	return;
      default:
	break;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR860(TYPE *XO398)
{
    TYPE XI398;

    switch (CURRENT_TERMINAL) {
      case 281:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = type_printf ; 
	    }
	}
	break;
      case 297:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = type_scanf ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    XR861 (&XI398);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO398 = XI398;
}

void
XR479(int *XI474)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  XL2_479:;
    {
	IDENTIFIER XI472;
	IDENTIFIER XI857;
	IDENTIFIER XI376;

	{

    (XI0) = predict_operator () ;
	}
	if (!XI0)
	    goto XL3;
	{

    (XI472) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XI472) ) ;
	}
	{

    (XI857) = check_id ( crt_namespace, (XI472), 0 ) ;
	}
	XR781 (XI857, &XI376);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto XL1;
	}
	{

    token_interface ( (XI376), (*XI474) ) ;
	}
	{

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	}
	goto XL2_479;
    }
    /*UNREACHED*/
  XL3:;
    switch (CURRENT_TERMINAL) {
      case 308:
	{
	    IDENTIFIER XI472;
	    IDENTIFIER XI858;
	    IDENTIFIER XI376;

	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI858) = find_tag_token ( (XI472) ) ;
	    }
	    XR781 (XI858, &XI376);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    token_interface ( (XI376), (*XI474) ) ;
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    goto XL2_479;
	}
	/*UNREACHED*/
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI472;
	    IDENTIFIER XI859;
	    IDENTIFIER XI376;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI859) = check_id ( crt_namespace, (XI472), 0 ) ;
	    }
	    XR781 (XI859, &XI376);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    token_interface ( (XI376), (*XI474) ) ;
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    goto XL2_479;
	}
	/*UNREACHED*/
      case 51:
	{
	    IDENTIFIER XI472;
	    IDENTIFIER XI856;
	    IDENTIFIER XI376;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 51:
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI472 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI856) = find_ext_token ( (XI472) ) ;
	    }
	    XR781 (XI856, &XI376);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    token_interface ( (XI376), (*XI474) ) ;
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    goto XL2_479;
	}
	/*UNREACHED*/
      default:
	break;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR861(TYPE *XO398)
{
    TYPE XI398;

    switch (CURRENT_TERMINAL) {
      case 281:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = type_wprintf ; 
	    }
	}
	break;
      case 297:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = type_wscanf ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO398 = XI398;
}

void
XR773(void)
{
    switch (CURRENT_TERMINAL) {
      case 168:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
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
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 232:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ellipsis_ident ; 
	    }
	    {
 (XI378) = ( unsigned ) OPTION_OFF ; 
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 173:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 275:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 294:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_overload_ambig ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 175:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 121:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_anon_union ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 181:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 179:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 127:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_bool_assign ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 182:
	{
	    ADVANCE_LEXER;
	    XR784 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 183:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 274:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_bitf_overflow ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 184:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 228:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 117:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_func_block ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 128:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 171:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_wall ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 187:
	{
	    ADVANCE_LEXER;
	    XR810 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 191:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_token_redef ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 192:
	{
	    ADVANCE_LEXER;
	    XR803 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 194:
	{
	    ADVANCE_LEXER;
	    XR799 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 98:
	{
	    ADVANCE_LEXER;
	    XR802 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 195:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR711 (&XI710);
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 197:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 184:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR785 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 203:
	{
	    ADVANCE_LEXER;
	    XR800 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 204:
	{
	    IDENTIFIER XI768;
	    IDENTIFIER XI376;

	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI768 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI768 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI768 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI768 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 325:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 213:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI376 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    directory_option ( (XI768), (XI376) ) ;
	    }
	}
	break;
      case 206:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR712 (&XI710);
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 207:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 179:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 231:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_dollar_ident ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 211:
	{
	    ADVANCE_LEXER;
	    {

    end_option ( 1 ) ;
	    }
	}
	break;
      case 104:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 119:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_enum_switch ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 216:
	{
	    EXP XI410;
	    EXP XI445;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 17:
		    {
			{

    XI410 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			{

    XI410 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    XR755 (&XI445);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_escape ( (XI410), (XI445) ) ;
	    }
	}
	break;
      case 133:
	{
	    unsigned XI446;
	    unsigned XI378;
	    int XI710;
	    int XI716;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 186:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR743 (&XI446);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI710) = OPT_cast_explicit ; 
	    }
	    {
 (XI716) = OPT_VAL_cast_explicit ; 
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	    {

    set_value ( (XI716), NULL_exp, ( unsigned long ) (XI446) ) ;
	    }
	}
	break;
      case 221:
	{
	    ADVANCE_LEXER;
	    XR801 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 222:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR787 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 223:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 249:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 96:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_case_fall ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 107:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 245:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 184:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_for_scope ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 226:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 104:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 197:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_enum_decl ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 228:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 276:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 179:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 276:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_conv_ptr_func ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 231:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR788 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 235:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 118:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 44:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 121:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 44:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 104:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 307:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_type_tag_ignore ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 237:
	{
	    ADVANCE_LEXER;
	    XR804 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 240:
	{
	    int XI710;
	    EXP XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 202:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_VAL_include_depth ; 
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI378 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    set_value ( (XI710), (XI378), ( unsigned long ) 0 ) ;
	    }
	}
	break;
      case 242:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR790 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 243:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 313:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 179:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 268:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 313:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_type_obj_incompl ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 244:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR791 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 245:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 270:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 118:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 44:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 121:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 94:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_init_struct ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 137:
	{
	    unsigned XI378;
	    int XI710;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 254:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR723 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI710) = OPT_inline_internal ; 
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 246:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR797 (&XI710);
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 254:
	{
	    unsigned XI378;
	    unsigned XI474;
	    int XI710;
	    int XI716;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 294:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR724 (&XI378, &XI474);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI710) = OPT_link_resolve ; 
	    }
	    {
 (XI716) = OPT_link_internal ; 
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	    {

    set_option ( (XI716), (XI474) ) ;
	    }
	}
	break;
      case 256:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 313:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_longlong ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 264:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 190:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_nest_comment ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 266:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR792 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 141:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 279:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_paren ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 273:
	{
	    ADVANCE_LEXER;
	    XR811 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 275:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 294:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_overload_res ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 276:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 141:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ptr_operator ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 285:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR793 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 295:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 179:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 98:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_token_const ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 298:
	{
	    ADVANCE_LEXER;
	    XR809 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 310:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 169:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 203:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ppdir_text ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 148:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 257:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_this_lvalue ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 149:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_throw_bad ; 
	    }
	    XR506 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 316:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    XR794 (&XI710);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 319:
	{
	    ADVANCE_LEXER;
	    XR805 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 321:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 288:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_unmatched ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 323:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 189:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_reached ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 325:
	{
	    ADVANCE_LEXER;
	    XR808 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 327:
	{
	    ADVANCE_LEXER;
	    XR806 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 332:
	{
	    ADVANCE_LEXER;
	    XR807 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 333:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 304:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 255:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_const_string ; 
	    }
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	}
	break;
      case 215:
	{
	    int XI710;

	    XR759 (&XI710);
	    XR783 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 251: case 318:
	{
	    XR552 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

/* END OF FILE */
