/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/producers/common/parse/psyntax.sid
 * and
 *	/u/g/release/Source/src/producers/common/parse/psyntax.act
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

typedef LIST ( IDENTIFIER ) SID_LIST_ID ;


/*
     DECLARE FUNCTIONS

     The function declarations are included at this point so that the
     type definitions are in scope.
*/

#include "psyntax.h"
extern void parse_tok_type PROTO_S ( ( TYPE * ) ) ;
extern void parse_mem_type PROTO_S ( ( TYPE * ) ) ;
extern void parse_operator PROTO_S ( ( IDENTIFIER * ) ) ;


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
XR808 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 215:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 273:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_escape_overflow ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20:
	{
	    EXP XI409;

	    {
		switch (CURRENT_TERMINAL) {
		  case 17: case 18:
		    {
			{
			    switch (CURRENT_TERMINAL) {
			      case 17:
				{
				    {

    XI409 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 18:
				{
				    {

    XI409 = crt_token->pp_data.exp ;
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

    XI409 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 20:
				{
				    {

    XI409 = crt_token->pp_data.exp ;
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
		  case 178:
		    {
			EXP XI444;

			ADVANCE_LEXER;
			{
			    switch (CURRENT_TERMINAL) {
			      case 17:
				{
				    {

    XI444 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 18:
				{
				    {

    XI444 = crt_token->pp_data.exp ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      default:
				goto XL1;
			    }
			}
			{

    set_character ( (XI409), (XI444) ) ;
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
		  case 204:
		    {
			EXP XI444;

			ADVANCE_LEXER;
			{

    (XI444) = NULL_exp ;
			}
			{

    set_character ( (XI409), (XI444) ) ;
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR809 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 325:
	{
	    EXP XI448;
	    int XI708;
	    EXP XI377;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    XI448 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    XI448 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    STRING s = DEREF_str ( exp_string_lit_str ( (XI448) ) ) ;
    (XI708) = find_value_no ( s, 0 ) ;
    if ( (XI708) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI377 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    set_value ( (XI708), (XI377), ( unsigned long ) 0 ) ;
	    }
	}
	break;
      case 19: case 20:
	{
	    EXP XI448;
	    int XI708;
	    unsigned XI377;

	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    XI448 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    XI448 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    STRING s = DEREF_str ( exp_string_lit_str ( (XI448) ) ) ;
    (XI708) = find_option_no ( s, 0 ) ;
    if ( (XI708) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
	    }
	    XR507 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR810 PROTO_Z ()
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
	    XR496 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR811 PROTO_N ((XI397))
  PROTO_T (TYPE *XI397)
{
    switch (CURRENT_TERMINAL) {
      case 47: case 209:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 47:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 209:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    accept_ellipsis ( (*XI397) ) ;
	    }
	}
	break;
      default:
	{
	    TYPE XI448;

	    {

    (XI448) = type_error ;
    parse_tok_type ( &(XI448) ) ;
    object_type ( (XI448), null_tag ) ;
	    }
	    {

    accept_argument ( (*XI397), (XI448) ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR812 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 186:
	{
	    TYPE XI397;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 254:
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

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    {

    set_char_lit ( (XI397) ) ;
	    }
	}
	break;
      case 255:
	{
	    int XI444;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
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
 (XI444) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (XI444) = 0 ; 
			}
		    }
		    break;
		}
	    }
	    {

    set_long_long_type ( (XI444) ) ;
	    }
	}
	break;
      case 301:
	{
	    IDENTIFIER XI375;

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

    (XI375) = NULL_id ;
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

    XI375 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 3:
				{
				    {

    XI375 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 4:
				{
				    {

    XI375 = crt_token->pp_data.id.use ;
				    }
				    ADVANCE_LEXER;
				}
				break;
			      case 2:
				{
				    {

    XI375 = crt_token->pp_data.id.use ;
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

    set_std_namespace ( (XI375) ) ;
	    }
	}
	break;
      case 303:
	{
	    CV_SPEC XI588;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 254:
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
		  case 265:
		    {
			ADVANCE_LEXER;
			{
 (XI588) = cv_none ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (XI588) = cv_const ; 
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

    set_string_qual ( (XI588) ) ;
	    }
	}
	break;
      case 156: case 285: case 298:
	{
	    BASE_TYPE XI584;
	    TYPE XI397;

	    {
		switch (CURRENT_TERMINAL) {
		  case 285:
		    {
			ADVANCE_LEXER;
			{
 (XI584) = btype_ptrdiff_t ; 
			}
		    }
		    break;
		  case 298:
		    {
			ADVANCE_LEXER;
			{
 (XI584) = btype_size_t ; 
			}
		    }
		    break;
		  case 156:
		    {
			ADVANCE_LEXER;
			{
 (XI584) = btype_wchar_t ; 
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

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    {

    set_builtin_type ( (XI584), (XI397) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR725 PROTO_N ((XO473))
  PROTO_T (unsigned *XO473)
{
    unsigned XI473;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    XR834 (&XI473);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI473) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO473 = XI473;
}

void
XR813 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 214: case 261:
	{
	    XR807 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 156: case 186: case 255: case 285: case 298:
      case 301: case 303:
	{
	    XR812 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR722 PROTO_N ((XO377, XO473))
  PROTO_T (unsigned *XO377 X unsigned *XO473)
{
    unsigned XI377;
    unsigned XI473;

    switch (CURRENT_TERMINAL) {
      case 270:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_OFF ; 
	    }
	    {
 (XI473) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 65:
	{
	    unsigned XI444;

	    ADVANCE_LEXER;
	    XR721 (&XI473);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 271:
		    {
			ADVANCE_LEXER;
			{
 (XI444) = ( unsigned ) OPTION_OFF ; 
			}
		    }
		    break;
		  case 330:
		    {
			ADVANCE_LEXER;
			{
 (XI444) = ( unsigned ) OPTION_WARN ; 
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    XI377 = XI444;
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO377 = XI377;
    *XO473 = XI473;
}

void
XR814 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 194:
	{
	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    XR494 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 47: case 209:
	{
	    int XI708;
	    unsigned XI377;

	    {
		switch (CURRENT_TERMINAL) {
		  case 47:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 209:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 231:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_ellipsis_ident ; 
	    }
	    {
 (XI377) = ( unsigned ) OPTION_OFF ; 
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR815 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 115: case 122: case 207:
	{
	    BASE_TYPE XI584;

	    {
		switch (CURRENT_TERMINAL) {
		  case 207:
		    {
			ADVANCE_LEXER;
			{
 (XI584) = btype_none ; 
			}
		    }
		    break;
		  case 115:
		    {
			ADVANCE_LEXER;
			{
 (XI584) = btype_signed ; 
			}
		    }
		    break;
		  case 122:
		    {
			ADVANCE_LEXER;
			{
 (XI584) = btype_unsigned ; 
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    set_char_sign ( (XI584) ) ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 215:
	{
	    XR808 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR816 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 311:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_token_redef ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 312:
	{
	    TYPE XI397;
	    TYPE XI448;
	    unsigned XI377;

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

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 48:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI448) = type_error ;
    parse_tok_type ( &(XI448) ) ;
    object_type ( (XI448), null_tag ) ;
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
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_compatible_type ( (XI397), (XI448), (XI377) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR817 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 269:
	{
	    int XI708;
	    unsigned XI377;

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
 (XI708) = OPT_init_struct ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI375;

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

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
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

    allow_initialiser ( (XI375) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR818 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 174:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR709 (&XI708);
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 1: case 2: case 3: case 4: case 172:
	{
	    {

    rescan_pragma ( lex_allow ) ;
    RESCAN_LEXER ;
	    }
	    XR494 ();
	    switch (CURRENT_TERMINAL) {
	      case 172:
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR819 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 254:
	{
	    int XI444;
	    int XI448;

	    ADVANCE_LEXER;
	    {

    pragma_number = 1 ;
	    }
	    XR527 (&XI444);
	    XR528 (&XI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    begin_literal ( (XI444), (XI448) ) ;
	    }
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    XR532 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 141: case 273:
	{
	    int XI708;
	    unsigned XI377;

	    XR795 (&XI708);
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR820 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 311:
	{
	    int XI473;

	    ADVANCE_LEXER;
	    {
 (XI473) = lex_undef ; 
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    XR478 (&XI473);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 250:
	{
	    IDENTIFIER XI375;

	    XR549 (&XI375);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    undef_keyword ( (XI375) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR528 PROTO_N ((XO448))
  PROTO_T (int *XO448)
{
    int XI448;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    XR849 (&XI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    XR848 (&XI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI448) = SUFFIX_NONE ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO448 = XI448;
}

void
XR494 PROTO_Z ()
{
  XL2_494:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI375;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    allow_conversion ( (XI375) ) ;
	    }
	    goto XL2_494;
	}
	/*UNREACHED*/
      case 354:
	return;
      default:
	break;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR710 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    XR828 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI708) = OPT_discard ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR712 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 107:
	{
	    ADVANCE_LEXER;
	    XR839 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI708) = OPT_infer_int ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR527 PROTO_N ((XO444))
  PROTO_T (int *XO444)
{
    int XI444;

    switch (CURRENT_TERMINAL) {
      case 195:
	{
	    ADVANCE_LEXER;
	    {
 (XI444) = BASE_DECIMAL ; 
	    }
	}
	break;
      case 228:
	{
	    ADVANCE_LEXER;
	    {
 (XI444) = BASE_HEXADECIMAL ; 
	    }
	}
	break;
      case 268:
	{
	    ADVANCE_LEXER;
	    {
 (XI444) = BASE_OCTAL ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO444 = XI444;
}

void
XR532 PROTO_Z ()
{
  XL2_532:;
    switch (CURRENT_TERMINAL) {
      case 72:
	{
	    ADVANCE_LEXER;
	    {

    add_range_literal ( NULL_exp, 1 ) ;
	    }
	    XR529 ();
	    {
		if ((CURRENT_TERMINAL) == 354) {
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
	    goto XL2_532;
	}
	/*UNREACHED*/
      case 78:
	{
	    ADVANCE_LEXER;
	    {

    add_range_literal ( NULL_exp, 0 ) ;
	    }
	    XR529 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 21:
	{
	    EXP XI377;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI377 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    add_range_literal ( (XI377), 2 ) ;
	    }
	    XR529 ();
	    {
		if ((CURRENT_TERMINAL) == 354) {
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
	    goto XL2_532;
	}
	/*UNREACHED*/
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR826 PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 174:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR710 (&XI708);
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI397) = lex_unused ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO397 = XI397;
}

void
XR731 PROTO_N ((XO445))
  PROTO_T (unsigned *XO445)
{
    unsigned XI445;

    switch (CURRENT_TERMINAL) {
      case 130:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = CAST_CONST ; 
	    }
	}
	break;
      case 145:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = CAST_REINTERP ; 
	    }
	}
	break;
      case 146:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = CAST_STATIC ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO445 = XI445;
}

void
XR827 PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 156: case 186: case 214: case 255: case 261:
      case 285: case 298: case 301: case 303:
	{
	    XR813 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI397) = lex_set ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO397 = XI397;
}

void
XR398 PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 307:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI397) = 0 ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *XO397 = XI397;
}

void
XR828 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 227:
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
 (XI708) = OPT_discard_func ; 
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
 (XI708) = OPT_discard_static ; 
	    }
	}
	break;
      case 325:
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
 (XI708) = OPT_discard_value ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR829 PROTO_N ((XO400))
  PROTO_T (TOKEN *XO400)
{
    TOKEN XI400;

    switch (CURRENT_TERMINAL) {
      case 115:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_signed | btype_int ) ;
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_unsigned | btype_int ) ;
	    }
	}
	break;
      default:
	{
	    {

    (XI400) = make_type_token ( btype_int ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    *XO400 = XI400;
}

void
XR830 PROTO_N ((XO400))
  PROTO_T (TOKEN *XO400)
{
    TOKEN XI400;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TOKEN XI409;
	    SID_LIST_ID XI402;
	    TOKEN XI444;
	    TOKEN XI406;

	    ADVANCE_LEXER;
	    {

    (XI409) = begin_proc_token () ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 176: case 187: case 217: case 224: case 226:
		  case 249: case 260: case 262: case 281: case 295:
		  case 302: case 304: case 313: case 319: case 327:
		    {
			XR413 (&XI402);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (XI402) = NULL_list ( IDENTIFIER ) ;
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

    (XI444) = cont_proc_token ( (XI409), (XI402), (XI402) ) ;
	    }
	    XR396 (&XI406);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    (XI400) = end_proc_token ( (XI444), (XI406) ) ;
	    }
	}
	break;
      case 64:
	{
	    TOKEN XI409;
	    SID_LIST_ID XI450;
	    SID_LIST_ID XI402;
	    SID_LIST_ID XI453;
	    SID_LIST_ID XI405;
	    TOKEN XI444;
	    TOKEN XI406;

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

    (XI409) = begin_proc_token () ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 176: case 187: case 217: case 224: case 226:
		  case 249: case 260: case 262: case 281: case 295:
		  case 302: case 304: case 313: case 319: case 327:
		    {
			XR403 (&XI450);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (XI450) = NULL_list ( IDENTIFIER ) ;
			}
		    }
		    break;
		}
	    }
	    XI402 = XI450;
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
		  case 217: case 260: case 281: case 302: case 313:
		    {
			XR408 (XI402, &XI453);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (XI453) = NULL_list ( IDENTIFIER ) ;
			}
		    }
		    break;
		}
	    }
	    XI405 = XI453;
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

    (XI444) = cont_proc_token ( (XI409), (XI402), (XI405) ) ;
	    }
	    XR396 (&XI406);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    (XI400) = end_proc_token ( (XI444), (XI406) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO400 = XI400;
}

void
XR831 PROTO_N ((XO405))
  PROTO_T (SID_LIST_ID *XO405)
{
    SID_LIST_ID XI405;

    switch (CURRENT_TERMINAL) {
      case 176: case 187: case 217: case 224: case 226:
      case 249: case 260: case 262: case 281: case 295:
      case 302: case 304: case 313: case 319: case 327:
	{
	    XR413 (&XI405);
	    if ((CURRENT_TERMINAL) == 354) {
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

    (XI405) = NULL_list ( IDENTIFIER ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO405 = XI405;
}

void
XR832 PROTO_N ((XO405))
  PROTO_T (SID_LIST_ID *XO405)
{
    SID_LIST_ID XI405;

    switch (CURRENT_TERMINAL) {
      case 176: case 187: case 217: case 224: case 226:
      case 249: case 260: case 262: case 281: case 295:
      case 302: case 304: case 313: case 319: case 327:
	{
	    XR403 (&XI405);
	    if ((CURRENT_TERMINAL) == 354) {
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

    (XI405) = NULL_list ( IDENTIFIER ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO405 = XI405;
}

void
XR833 PROTO_N ((XI406, XO405))
  PROTO_T (SID_LIST_ID *XI406 X SID_LIST_ID *XO405)
{
    SID_LIST_ID XI405;

    switch (CURRENT_TERMINAL) {
      case 217: case 260: case 281: case 302: case 313:
	{
	    XR408 (*XI406, &XI405);
	    if ((CURRENT_TERMINAL) == 354) {
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

    (XI405) = NULL_list ( IDENTIFIER ) ;
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO405 = XI405;
}

void
XR834 PROTO_N ((XO473))
  PROTO_T (unsigned *XO473)
{
    unsigned XI473;

    switch (CURRENT_TERMINAL) {
      case 191:
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
 (XI473) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 242:
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
 (XI473) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO473 = XI473;
}

void
XR837 PROTO_N ((XI835, XO445))
  PROTO_T (unsigned *XI835 X unsigned *XO445)
{
    unsigned XI445;

    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    unsigned XI444;

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
	    XR732 (&XI444);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI445) = ( (*XI835) | (XI444) ) ; 
	    }
	}
	break;
      default:
	{
	    XI445 = *XI835;
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO445 = XI445;
}

void
XR838 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 169:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 193:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_empty_body ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI708) = OPT_semicolon_extra ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR839 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

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
 (XI708) = OPT_infer_int_cv ; 
	    }
	}
	break;
      case 220:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 196:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_dspec_none ; 
	    }
	}
	break;
      case 227:
	{
	    ADVANCE_LEXER;
	    XR840 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR840 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 175:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_param_impl ; 
	    }
	}
	break;
      case 113:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_dspec_none_func ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR841 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

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
	    XR843 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 275:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 59:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR842 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
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
	      case 275:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 236:
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
 (XI708) = OPT_conv_ptr_void_ptr ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR411 PROTO_N ((XO375))
  PROTO_T (IDENTIFIER *XO375)
{
    IDENTIFIER XI375;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TOKEN XI400;
	int XI397;
	IDENTIFIER XI401;

	XR396 (&XI400);
	XR398 (&XI397);
	{
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 3: case 4:
		{
		    {
			switch (CURRENT_TERMINAL) {
			  case 1:
			    {
				{

    XI401 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 3:
			    {
				{

    XI401 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    XI401 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    XI401 = crt_token->pp_data.id.use ;
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
    (XI401) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	{

    (XI375) = make_tok_param ( (XI400), (XI397), (XI401) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO375 = XI375;
}

void
XR842 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 110:
	{
	    ADVANCE_LEXER;
	    XR847 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 275:
	{
	    ADVANCE_LEXER;
	    XR845 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
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
	      case 236:
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
 (XI708) = OPT_conv_ptr_ptr_void ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR843 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 104:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 236:
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
 (XI708) = OPT_conv_int_enum ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    XR846 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 275:
	{
	    ADVANCE_LEXER;
	    XR847 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR529 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    TYPE XI397;

	    ADVANCE_LEXER;
	    {

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    {

    add_type_literal ( (XI397) ) ;
	    }
	}
	break;
      case 78:
	{
	    ADVANCE_LEXER;
	    XR851 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR845 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_conv_ptr_ptr ; 
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
 (XI708) = OPT_conv_ptr_ptr_expl ; 
	    }
	}
	break;
      case 236:
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
 (XI708) = OPT_conv_ptr_ptr_impl ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR846 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_conv_int_int ; 
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
 (XI708) = OPT_conv_int_int_expl ; 
	    }
	}
	break;
      case 236:
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
 (XI708) = OPT_conv_int_int_impl ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR847 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_conv_int_ptr ; 
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
 (XI708) = OPT_conv_int_ptr_expl ; 
	    }
	}
	break;
      case 236:
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
 (XI708) = OPT_conv_int_ptr_impl ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR848 PROTO_N ((XO448))
  PROTO_T (int *XO448)
{
    int XI448;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    XR850 (&XI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI448) = SUFFIX_U ; 
	    }
	}
	break;
      case 354:
	return;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO448 = XI448;
}

void
XR849 PROTO_N ((XO448))
  PROTO_T (int *XO448)
{
    int XI448;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (XI448) = SUFFIX_LL ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI448) = SUFFIX_L ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *XO448 = XI448;
}

void
XR850 PROTO_N ((XO448))
  PROTO_T (int *XO448)
{
    int XI448;

    switch (CURRENT_TERMINAL) {
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (XI448) = SUFFIX_ULL ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI448) = SUFFIX_UL ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *XO448 = XI448;
}

void
XR851 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    unsigned XI409;

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
		  case 172: case 204: case 330:
		    {
			XR506 (&XI409);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{
 (XI409) = ( unsigned ) OPTION_ON ; 
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

    add_token_literal ( NULL_id, (XI409) ) ;
	    }
	}
	break;
      case 41: case 172: case 204: case 330:
	{
	    unsigned XI409;
	    IDENTIFIER XI375;

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
		  case 172: case 204: case 330:
		    {
			XR506 (&XI409);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{
 (XI409) = ( unsigned ) OPTION_OFF ; 
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

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    add_token_literal ( (XI375), (XI409) ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR739 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP XI448;

	switch (CURRENT_TERMINAL) {
	  case 272:
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

    XI448 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    XI448 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto XL1;
	    }
	}
	{

    STRING s = DEREF_str ( exp_string_lit_str ( (XI448) ) ) ;
    (XI708) = find_option_no ( s, 0 ) ;
    if ( (XI708) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO708 = XI708;
}

void
XR852 PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 325:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_discard ; 
	    }
	}
	break;
      case 326:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_unused ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO397 = XI397;
}

void
XR853 PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 288:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_reachable ; 
	    }
	}
	break;
      case 322:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_unreachable ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI397) = lex_set ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *XO397 = XI397;
}

void
XR399 PROTO_N ((XO375))
  PROTO_T (IDENTIFIER *XO375)
{
    IDENTIFIER XI375;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TOKEN XI400;
	int XI397;
	IDENTIFIER XI401;

	XR396 (&XI400);
	XR398 (&XI397);
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    XI401 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    {

    XI401 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    XI401 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    XI401 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	}
	{

    (XI375) = make_tok_param ( (XI400), (XI397), (XI401) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO375 = XI375;
}

void
XR509 PROTO_N ((XO377))
  PROTO_T (int *XO377)
{
    int XI377;

    switch (CURRENT_TERMINAL) {
      case 172:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = OPT_none ; 
	    }
	}
	break;
      case 204:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = OPT_error ; 
	    }
	}
	break;
      case 270:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = OPT_none ; 
	    }
	}
	break;
      case 271:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = OPT_error ; 
	    }
	}
	break;
      case 330:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = OPT_warning ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO377 = XI377;
}

void
XR496 PROTO_Z ()
{
  XL2_496:;
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI375;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    preserve_id ( (XI375), lex_preserve ) ;
	    }
	    goto XL2_496;
	}
	/*UNREACHED*/
      case 354:
	return;
      default:
	break;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR858 PROTO_N ((XO397))
  PROTO_T (TYPE *XO397)
{
    TYPE XI397;

    switch (CURRENT_TERMINAL) {
      case 280:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = type_printf ; 
	    }
	}
	break;
      case 296:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = type_scanf ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    XR859 (&XI397);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO397 = XI397;
}

void
XR859 PROTO_N ((XO397))
  PROTO_T (TYPE *XO397)
{
    TYPE XI397;

    switch (CURRENT_TERMINAL) {
      case 280:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = type_wprintf ; 
	    }
	}
	break;
      case 296:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = type_wscanf ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO397 = XI397;
}

void
XR478 PROTO_N ((XI473))
  PROTO_T (int *XI473)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  XL2_478:;
    {
	IDENTIFIER XI471;
	IDENTIFIER XI855;
	IDENTIFIER XI375;

	{

    (XI0) = predict_operator () ;
	}
	if (!XI0)
	    goto XL3;
	{

    (XI471) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XI471) ) ;
	}
	{

    (XI855) = check_id ( crt_namespace, (XI471), 0 ) ;
	}
	XR779 (XI855, &XI375);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto XL1;
	}
	{

    token_interface ( (XI375), (*XI473) ) ;
	}
	{

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	}
	goto XL2_478;
    }
    /*UNREACHED*/
  XL3:;
    switch (CURRENT_TERMINAL) {
      case 307:
	{
	    IDENTIFIER XI471;
	    IDENTIFIER XI856;
	    IDENTIFIER XI375;

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

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI856) = find_tag_token ( (XI471) ) ;
	    }
	    XR779 (XI856, &XI375);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    token_interface ( (XI375), (*XI473) ) ;
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    goto XL2_478;
	}
	/*UNREACHED*/
      case 1: case 2: case 3: case 4:
	{
	    IDENTIFIER XI471;
	    IDENTIFIER XI857;
	    IDENTIFIER XI375;

	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI857) = check_id ( crt_namespace, (XI471), 0 ) ;
	    }
	    XR779 (XI857, &XI375);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    token_interface ( (XI375), (*XI473) ) ;
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    goto XL2_478;
	}
	/*UNREACHED*/
      case 51:
	{
	    IDENTIFIER XI471;
	    IDENTIFIER XI854;
	    IDENTIFIER XI375;

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

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI471 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI854) = find_ext_token ( (XI471) ) ;
	    }
	    XR779 (XI854, &XI375);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    token_interface ( (XI375), (*XI473) ) ;
	    }
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	    }
	    goto XL2_478;
	}
	/*UNREACHED*/
      default:
	break;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR771 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 168:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 47:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 209:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 231:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_ellipsis_ident ; 
	    }
	    {
 (XI377) = ( unsigned ) OPTION_OFF ; 
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 173:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 274:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 293:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_overload_ambig ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 180:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 178:
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
 (XI708) = OPT_bool_assign ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 181:
	{
	    ADVANCE_LEXER;
	    XR782 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 182:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 273:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_bitf_overflow ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 183:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 227:
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
 (XI708) = OPT_func_block ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 128:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 171:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_wall ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 186:
	{
	    ADVANCE_LEXER;
	    XR808 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 190:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 311:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_token_redef ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 191:
	{
	    ADVANCE_LEXER;
	    XR801 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 193:
	{
	    ADVANCE_LEXER;
	    XR797 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 98:
	{
	    ADVANCE_LEXER;
	    XR800 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 194:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR709 (&XI708);
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 196:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 183:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR783 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 202:
	{
	    ADVANCE_LEXER;
	    XR798 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 203:
	{
	    IDENTIFIER XI766;
	    IDENTIFIER XI375;

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

    XI766 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI766 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI766 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI766 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 324:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 212:
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

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI375 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    directory_option ( (XI766), (XI375) ) ;
	    }
	}
	break;
      case 205:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR710 (&XI708);
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 206:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 178:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 230:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_dollar_ident ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 210:
	{
	    ADVANCE_LEXER;
	    {

    end_option ( 1 ) ;
	    }
	}
	break;
      case 104:
	{
	    int XI708;
	    unsigned XI377;

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
 (XI708) = OPT_enum_switch ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 215:
	{
	    EXP XI409;
	    EXP XI444;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 17:
		    {
			{

    XI409 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			{

    XI409 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    XR753 (&XI444);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_escape ( (XI409), (XI444) ) ;
	    }
	}
	break;
      case 133:
	{
	    unsigned XI445;
	    unsigned XI377;
	    int XI708;
	    int XI714;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 185:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR741 (&XI445);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI708) = OPT_cast_explicit ; 
	    }
	    {
 (XI714) = OPT_VAL_cast_explicit ; 
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	    {

    set_value ( (XI714), NULL_exp, ( unsigned long ) (XI445) ) ;
	    }
	}
	break;
      case 220:
	{
	    ADVANCE_LEXER;
	    XR799 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 221:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR785 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 222:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 248:
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
 (XI708) = OPT_case_fall ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 107:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 244:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 183:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_for_scope ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 225:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 104:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 196:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_enum_decl ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 227:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 275:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 178:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 275:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_conv_ptr_func ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 230:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR786 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 234:
	{
	    int XI708;
	    unsigned XI377;

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
	      case 306:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_type_tag_ignore ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 236:
	{
	    ADVANCE_LEXER;
	    XR802 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 239:
	{
	    int XI708;
	    EXP XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 201:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_VAL_include_depth ; 
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 21:
			{

    XI377 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    set_value ( (XI708), (XI377), ( unsigned long ) 0 ) ;
	    }
	}
	break;
      case 241:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR788 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 242:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 178:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 267:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_type_obj_incompl ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 243:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR789 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 244:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 269:
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
 (XI708) = OPT_init_struct ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 137:
	{
	    unsigned XI377;
	    int XI708;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 253:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR721 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI708) = OPT_inline_internal ; 
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 245:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR795 (&XI708);
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 253:
	{
	    unsigned XI377;
	    unsigned XI473;
	    int XI708;
	    int XI714;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 293:
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
	    XR722 (&XI377, &XI473);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI708) = OPT_link_resolve ; 
	    }
	    {
 (XI714) = OPT_link_internal ; 
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	    {

    set_option ( (XI714), (XI473) ) ;
	    }
	}
	break;
      case 255:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_longlong ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 263:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 189:
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
 (XI708) = OPT_nest_comment ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 265:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR790 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 141:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 278:
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
 (XI708) = OPT_paren ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 272:
	{
	    ADVANCE_LEXER;
	    XR809 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 274:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 293:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_overload_res ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 275:
	{
	    int XI708;
	    unsigned XI377;

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
 (XI708) = OPT_ptr_operator ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 284:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR791 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 294:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 311:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 178:
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
 (XI708) = OPT_token_const ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 297:
	{
	    ADVANCE_LEXER;
	    XR807 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 309:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 169:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 202:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_ppdir_text ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 148:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 256:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_this_lvalue ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 149:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_throw_bad ; 
	    }
	    XR505 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 315:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    XR792 (&XI708);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 318:
	{
	    ADVANCE_LEXER;
	    XR803 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 320:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 287:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_unmatched ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 322:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 188:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_reached ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 324:
	{
	    ADVANCE_LEXER;
	    XR806 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 326:
	{
	    ADVANCE_LEXER;
	    XR804 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 331:
	{
	    ADVANCE_LEXER;
	    XR805 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 332:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 303:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 254:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_const_string ; 
	    }
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	}
	break;
      case 214:
	{
	    int XI708;

	    XR757 (&XI708);
	    XR781 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 250: case 317:
	{
	    XR551 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto XL1;
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

/* END OF FILE */
