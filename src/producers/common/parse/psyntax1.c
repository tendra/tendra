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



/* BEGINNING OF STATIC VARIABLES */

int XI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
XR403 PROTO_N ((XO402))
  PROTO_T (SID_LIST_ID *XO402)
{
    SID_LIST_ID XI402;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER XI375;
	SID_LIST_ID XI405;

	XR399 (&XI375);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    XR832 (&XI405);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto XL1;
		    }
		}
		break;
	      default:
		{
		    {

    (XI405) = NULL_list ( IDENTIFIER ) ;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	{

    CONS_id ( (XI375), (XI405), (XI402) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO402 = XI402;
}

void
XR505 PROTO_N ((XO377))
  PROTO_T (unsigned *XO377)
{
    unsigned XI377;

    switch (CURRENT_TERMINAL) {
      case 270:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 271:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 330:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_WARN ; 
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
XR732 PROTO_N ((XO445))
  PROTO_T (unsigned *XO445)
{
    unsigned XI445;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	unsigned XI835;

	XR731 (&XI835);
	XR837 (&XI835, &XI445);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto XL1;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO445 = XI445;
}

void
XR549 PROTO_N ((XO375))
  PROTO_T (IDENTIFIER *XO375)
{
    IDENTIFIER XI375;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 250:
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
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO375 = XI375;
}

void
XR456 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TOKEN XI400;
	int XI397;
	IDENTIFIER XI409;
	IDENTIFIER XI444;

	switch (CURRENT_TERMINAL) {
	  case 311:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	XR396 (&XI400);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto XL1;
	}
	{

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
	}
	{
	    {
		{

    (XI0) = predict_operator () ;
		}
		if (!XI0)
		    goto XL3;
		{

    (XI409) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XI409) ) ;
		}
		{
 (XI397) = 0 ; 
		}
		goto XL2;
	    }
	    /*UNREACHED*/
	  XL3:;
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 3: case 4: case 307:
		{
		    XR398 (&XI397);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto XL1;
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

    XI409 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 3:
			    {
				{

    XI409 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    XI409 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    XI409 = crt_token->pp_data.id.use ;
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
	  XL2:;
	}
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
	      case 59:
		{
		    ADVANCE_LEXER;
		    {

    HASHID nm = lookup_anon () ;
    (XI444) = DEREF_id ( hashid_id ( nm ) ) ;
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

    XI444 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 3:
			    {
				{

    XI444 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    XI444 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    XI444 = crt_token->pp_data.id.use ;
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
		    XI444 = XI409;
		}
		break;
	    }
	}
	{

    IGNORE make_token_decl ( (XI400), (XI397), (XI409), (XI444) ) ;
	}
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR779 PROTO_N ((XI777, XO778))
  PROTO_T (IDENTIFIER XI777 X IDENTIFIER *XO778)
{
    IDENTIFIER XI778;

  XL2_779:;
    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    IDENTIFIER XI472;
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

    (XI375) = find_mem_token ( (XI777), (XI472) ) ;
	    }
	    XI777 = XI375;
	    goto XL2_779;
	}
	/*UNREACHED*/
      default:
	{
	    XI778 = XI777;
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
    *XO778 = XI778;
}

void
XR781 PROTO_N ((XI708))
  PROTO_T (int *XI708)
{
    switch (CURRENT_TERMINAL) {
      case 178:
	{
	    int XI377;

	    ADVANCE_LEXER;
	    XR739 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_error_sev ( (*XI708), (XI377) ) ;
	    }
	}
	break;
      case 172: case 204: case 270: case 271: case 330:
	{
	    int XI377;

	    XR509 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_error_sev ( (*XI708), (XI377) ) ;
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
XR782 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 261:
	{
	    IDENTIFIER XI375;

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

    begin_option ( (XI375) ) ;
	    }
	}
	break;
      default:
	{
	    IDENTIFIER XI375;

	    {

    (XI375) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    begin_option ( (XI375) ) ;
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
XR783 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 210:
	{
	    ADVANCE_LEXER;
	    {

    IGNORE end_decl_block ( NULL_id, 1 ) ;
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
	      case 181:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    begin_decl_block ( (XI375) ) ;
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
XR784 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 196:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_decl_cond ; 
	    }
	}
	break;
      case 256:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_cond_lvalue ; 
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
XR785 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 182:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 110:
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
 (XI708) = OPT_bitf_type ; 
	    }
	}
	break;
      case 42:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_comma_extra ; 
	    }
	}
	break;
      case 257:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 200:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_macro_redef ; 
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    XR838 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 312:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 200:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_type_redef ; 
	    }
	}
	break;
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
 (XI708) = OPT_ellipsis_extra ; 
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
XR786 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 178:
	{
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
	    {
 (XI708) = OPT_ellipsis_ident ; 
	    }
	}
	break;
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
 (XI708) = OPT_ellipsis_ident ; 
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
XR787 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 110:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 312:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR712 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 311:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 200:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_func_token_undef ; 
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
XR716 PROTO_N ((XO377, XO473))
  PROTO_T (unsigned *XO377 X unsigned *XO473)
{
    unsigned XI377;
    unsigned XI473;

    switch (CURRENT_TERMINAL) {
      case 204:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_ON ; 
	    }
	    {
 (XI473) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 65: case 172: case 330:
	{
	    unsigned XI409;
	    unsigned XI444;

	    {
		switch (CURRENT_TERMINAL) {
		  case 65:
		    {
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			  case 234:
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
 (XI409) = ( unsigned ) OPTION_ON ; 
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
	    {
		switch (CURRENT_TERMINAL) {
		  case 172:
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
	    XI473 = XI409;
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
XR788 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 246:
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
 (XI708) = OPT_interf_incompat ; 
	    }
	}
	break;
      case 253:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_link_incompat ; 
	    }
	}
	break;
      case 259:
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
 (XI708) = OPT_member_incompat ; 
	    }
	}
	break;
      case 283:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 227:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 175:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_func_incompat ; 
	    }
	}
	break;
      case 312:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 286:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_type_qual_incompat ; 
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 113:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_func_ret_void ; 
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
XR789 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 202:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 169:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
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
 (XI708) = OPT_ppdir_indent_dir ; 
	    }
	}
	break;
      case 51:
	{
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
	    switch (CURRENT_TERMINAL) {
	      case 202:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_ppdir_indent ; 
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
XR790 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 202:
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
	      case 264:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 169:
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
 (XI708) = OPT_ppdir_id ; 
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
 (XI708) = OPT_decl_none ; 
	    }
	}
	break;
      case 230:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 169:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
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
 (XI708) = OPT_hash_ident ; 
	    }
	}
	break;
      case 264:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 169:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 223:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 210:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_eof_nline ; 
	    }
	}
	break;
      case 311:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 200:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_token_undef ; 
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
XR791 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 331:
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
 (XI708) = OPT_func_weak ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI708) = OPT_func_proto ; 
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
XR792 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 202:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_ppdir_unknown ; 
	    }
	}
	break;
      case 215:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_escape_unknown ; 
	    }
	}
	break;
      case 277:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_pragma_unknown ; 
	    }
	}
	break;
      case 118:
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
	      case 121:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_decl_struct_anon ; 
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
XR793 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 244:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_init_aggregate ; 
	    }
	}
	break;
      case 118:
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
	      case 121:
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
 (XI708) = OPT_complete_struct ; 
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
XR794 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 134:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 147:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_templ_export ; 
	    }
	}
	break;
      case 227:
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
 (XI708) = OPT_func_impl ; 
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
XR408 PROTO_N ((XI406, XO402))
  PROTO_T (SID_LIST_ID XI406 X SID_LIST_ID *XO402)
{
    SID_LIST_ID XI402;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER XI409;
	SID_LIST_ID XI405;

	XR407 (XI406, &XI409);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    XR833 (&XI406, &XI405);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto XL1;
		    }
		}
		break;
	      default:
		{
		    {

    (XI405) = NULL_list ( IDENTIFIER ) ;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	{

    CONS_id ( (XI409), (XI405), (XI402) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (354);
    return;
  XL0:;
    *XO402 = XI402;
}

void
XR795 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 141:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_int_operator ; 
	    }
	}
	break;
      case 273:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_int_overflow ; 
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
XR796 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 174:
	{
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_variable ; 
	    }
	}
	break;
      case 229:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 174:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_decl_hide ; 
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
XR715 PROTO_N ((XO708, XO714))
  PROTO_T (int *XO708 X int *XO714)
{
    int XI708;
    int XI714;

    switch (CURRENT_TERMINAL) {
      case 179:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_assert ;
    (XI714) = OPT_ppdir_assert_ignore ;
	    }
	}
	break;
      case 223:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_file ;
    (XI714) = OPT_ppdir_file_ignore ;
	    }
	}
	break;
      case 230:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_ident ;
    (XI714) = OPT_ppdir_ident_ignore ;
	    }
	}
	break;
      case 237:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_import ;
    (XI714) = OPT_ppdir_import_ignore ;
	    }
	}
	break;
      case 240:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_import ;
    (XI714) = OPT_ppdir_import_ignore ;
	    }
	}
	break;
      case 316:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_unassert ;
    (XI714) = OPT_ppdir_unassert_ignore ;
	    }
	}
	break;
      case 330:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_warning ;
    (XI714) = OPT_ppdir_warning_ignore ;
	    }
	}
	break;
      case 331:
	{
	    ADVANCE_LEXER;
	    {

    (XI708) = OPT_ppdir_weak ;
    (XI714) = OPT_ppdir_weak_ignore ;
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
    *XO714 = XI714;
}

void
XR797 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 274:
	{
	    unsigned XI473;
	    unsigned XI377;
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
	    XR725 (&XI473);
	    XR506 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI708) = OPT_overload_dep ; 
	    }
	    {
 (XI714) = OPT_overload_strict ; 
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	    {

    set_option ( (XI714), (XI473) ) ;
	    }
	}
	break;
      case 196: case 256:
	{
	    int XI708;
	    unsigned XI377;

	    XR784 (&XI708);
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
XR721 PROTO_N ((XO473))
  PROTO_T (unsigned *XO473)
{
    unsigned XI473;

    switch (CURRENT_TERMINAL) {
      case 220:
	{
	    ADVANCE_LEXER;
	    {
 (XI473) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 247:
	{
	    ADVANCE_LEXER;
	    {
 (XI473) = ( unsigned ) OPTION_ON ; 
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
XR798 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 178:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 257:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 175:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_macro_arg_dir ; 
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
      case 179: case 223: case 230: case 237: case 240:
      case 316: case 330: case 331:
	{
	    int XI708;
	    int XI714;
	    unsigned XI377;
	    unsigned XI473;

	    XR715 (&XI708, &XI714);
	    XR716 (&XI377, &XI473);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI708), (XI377) ) ;
	    }
	    {

    set_option ( (XI714), (XI473) ) ;
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
XR799 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 227:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 253:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_func_linkage ; 
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
      case 253:
	{
	    EXP XI377;
	    DECL_SPEC XI409;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    XI377 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    XI377 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI409) = find_linkage ( (XI377) ) ;
	    }
	    {

    set_link_opt ( (XI409) ) ;
	    }
	}
	break;
      case 124: case 328:
	{
	    int XI708;
	    unsigned XI377;

	    {
		switch (CURRENT_TERMINAL) {
		  case 124:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 328:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {
 (XI708) = OPT_decl_volatile ; 
	    }
	    {
 (XI377) = ( unsigned ) OPTION_ON ; 
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
XR800 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 193:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_const_cond ; 
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
      case 253:
	{
	    unsigned XI377;
	    int XI708;

	    ADVANCE_LEXER;
	    XR721 (&XI377);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI708) = OPT_const_internal ; 
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
XR801 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 223:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 239:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_include_full ; 
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
      case 118: case 244:
	{
	    int XI708;
	    unsigned XI377;

	    XR793 (&XI708);
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
XR802 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 110: case 311:
	{
	    int XI708;
	    unsigned XI377;

	    XR787 (&XI708);
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
      case 134: case 227:
	{
	    int XI708;
	    unsigned XI377;

	    XR794 (&XI708);
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
XR803 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 220:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 253:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_decl_unify ; 
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
      case 241:
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
 (XI708) = OPT_concat_string ; 
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
XR804 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 244:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_init_dynamic ; 
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
      case 174: case 229:
	{
	    int XI708;
	    unsigned XI377;

	    XR796 (&XI708);
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
XR709 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    XR841 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI708) = OPT_conv ; 
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
XR805 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 257:
	{
	    int XI708;
	    unsigned XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 213:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_macro_weak ; 
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
      case 284:
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
 (XI708) = OPT_weak ; 
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
parse_preproc PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	XR771 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto XL1;
	}
	{
 (XI397) = lex_ignore_token ; 
	}
    }
    goto XL0;
  XL1:;
    {
	{
 (XI397) = lex_hash_Hpragma ; 
	}
    }
  XL0:;
    *XO397 = XI397;
}

void
XR806 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 212:
	{
	    IDENTIFIER XI375;
	    unsigned XI377;

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
		switch (CURRENT_TERMINAL) {
		  case 292:
		    {
			ADVANCE_LEXER;
			XR506 (&XI377);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    {
			{
 (XI377) = ( unsigned ) OPTION_ON ; 
			}
		    }
		    break;
		}
	    }
	    {

    use_option ( (XI375), (XI377) ) ;
	    }
	}
	break;
      case 214:
	{
	    int XI708;

	    XR757 (&XI708);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    if ( (XI708) >= 0 ) {
	no_error_args = 1 ;
	report ( crt_loc, make_error ( (XI708) ) ) ;
	no_error_args = 0 ;
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
XR807 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 214:
	{
	    int XI708;
	    EXP XI377;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 251:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI708) = OPT_VAL_maximum_error ; 
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
      case 261:
	{
	    EXP XI377;
	    unsigned XI473;
	    int XI708;
	    int XI714;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 251:
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

    XI377 = crt_token->pp_data.exp ;
			}
			break;
		      default:
			goto XL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    XR508 (&XI473);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI708) = OPT_VAL_name_limit ; 
	    }
	    {
 (XI714) = OPT_name_limit ; 
	    }
	    {

    set_value ( (XI708), (XI377), ( unsigned long ) 0 ) ;
	    }
	    {

    set_option ( (XI714), (XI473) ) ;
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
parse_tendra PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 168:
	{
	    ADVANCE_LEXER;
	    XR814 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 175:
	{
	    TYPE XI822;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_as ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI822) = type_error ;
    parse_tok_type ( &(XI822) ) ;
    object_type ( (XI822), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 178:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR811 (&XI822);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 184:
	{
	    IDENTIFIER XI375;
	    TYPE XI823;

	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {

    crt_templ_qualifier = 0 ;
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
 (XI823) = type_bottom ; 
	    }
	    {

    typedef_special ( (XI375), (XI823) ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 186:
	{
	    ADVANCE_LEXER;
	    XR815 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 190:
	{
	    ADVANCE_LEXER;
	    XR816 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 192:
	{
	    IDENTIFIER XI375;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 282:
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

    compute_promote_type ( (XI375) ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 194:
	{
	    ADVANCE_LEXER;
	    XR818 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 197:
	{
	    int XI473;

	    ADVANCE_LEXER;
	    {
 (XI473) = lex_define ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 205:
	{
	    ADVANCE_LEXER;
	    XR826 (&XI397);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 210:
	{
	    ADVANCE_LEXER;
	    {

    end_option ( 1 ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 216:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_exhaustive ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 244:
	{
	    ADVANCE_LEXER;
	    XR817 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 245:
	{
	    ADVANCE_LEXER;
	    XR819 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 246:
	{
	    int XI473;

	    ADVANCE_LEXER;
	    {
 (XI473) = crt_interface ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 266:
	{
	    int XI473;

	    ADVANCE_LEXER;
	    {
 (XI473) = lex_no_Hdef ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 276:
	{
	    int XI409;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {
 (XI409) = lex_postpone ; 
	    }
	    XR495 (XI409);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 279:
	{
	    ADVANCE_LEXER;
	    XR810 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 283:
	{
	    TYPE XI824;
	    TYPE XI448;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI824) = type_error ;
    parse_tok_type ( &(XI824) ) ;
    object_type ( (XI824), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
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
	    {

    set_promote_type ( (XI824), (XI448), ntype_ellipsis ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 290:
	{
	    int XI473;

	    ADVANCE_LEXER;
	    {
 (XI473) = lex_ignore ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 297:
	{
	    ADVANCE_LEXER;
	    XR827 (&XI397);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 305:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 117:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    XR497 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 312:
	{
	    IDENTIFIER XI375;
	    TYPE XI825;

	    ADVANCE_LEXER;
	    {

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
	    }
	    {

    crt_templ_qualifier = 0 ;
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
	      case 107:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 184:
		    {
			ADVANCE_LEXER;
			{
 (XI825) = type_bottom ; 
			}
		    }
		    break;
		  case 285:
		    {
			ADVANCE_LEXER;
			{
 (XI825) = type_ptrdiff_t ; 
			}
		    }
		    break;
		  case 298:
		    {
			ADVANCE_LEXER;
			{
 (XI825) = type_size_t ; 
			}
		    }
		    break;
		  case 156:
		    {
			ADVANCE_LEXER;
			{
 (XI825) = type_wchar_t ; 
			}
		    }
		    break;
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
			XR858 (&XI825);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto XL1;
			}
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    typedef_special ( (XI375), (XI825) ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 317:
	{
	    ADVANCE_LEXER;
	    XR820 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 321:
	{
	    int XI409;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {
 (XI409) = lex_unpostpone ; 
	    }
	    XR495 (XI409);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
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
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 250:
	{
	    IDENTIFIER XI375;
	    int XI821;

	    XR549 (&XI375);
	    switch (CURRENT_TERMINAL) {
	      case 107:
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR550 (&XI821);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    define_keyword ( (XI375), (XI821) ) ;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 259:
	{
	    XR482 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 311:
	{
	    XR456 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI397) = lex_hash_Hpragma ; 
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
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{
 (XI397) = lex_hash_Hpragma ; 
	}
    }
  XL0:;
    *XO397 = XI397;
}

/* END OF FILE */
