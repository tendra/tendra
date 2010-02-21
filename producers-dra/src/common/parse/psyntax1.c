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



/* BEGINNING OF STATIC VARIABLES */

int XI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
XR404(SID_LIST_ID *XO403)
{
    SID_LIST_ID XI403;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER XI376;
	SID_LIST_ID XI406;

	XR400 (&XI376);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    XR834 (&XI406);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		    }
		}
		break;
	      default:
		{
		    {

    (XI406) = NULL_list ( IDENTIFIER ) ;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	{

    CONS_id ( (XI376), (XI406), (XI403) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO403 = XI403;
}

void
XR506(unsigned *XO378)
{
    unsigned XI378;

    switch (CURRENT_TERMINAL) {
      case 271:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 272:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 331:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_WARN ; 
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
XR734(unsigned *XO446)
{
    unsigned XI446;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	unsigned XI837;

	XR733 (&XI837);
	XR839 (&XI837, &XI446);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto XL1;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO446 = XI446;
}

void
XR550(IDENTIFIER *XO376)
{
    IDENTIFIER XI376;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 251:
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
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO376 = XI376;
}

void
XR457(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TOKEN XI401;
	int XI398;
	IDENTIFIER XI410;
	IDENTIFIER XI445;

	switch (CURRENT_TERMINAL) {
	  case 312:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	XR397 (&XI401);
	if ((CURRENT_TERMINAL) == 355) {
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

    (XI410) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XI410) ) ;
		}
		{
 (XI398) = 0 ; 
		}
		goto XL2;
	    }
	    /*UNREACHED*/
	  XL3:;
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 3: case 4: case 308:
		{
		    XR399 (&XI398);
		    if ((CURRENT_TERMINAL) == 355) {
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

    XI410 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 3:
			    {
				{

    XI410 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    XI410 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    XI410 = crt_token->pp_data.id.use ;
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
    (XI445) = DEREF_id ( hashid_id ( nm ) ) ;
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

    XI445 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 3:
			    {
				{

    XI445 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    XI445 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    XI445 = crt_token->pp_data.id.use ;
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
		    XI445 = XI410;
		}
		break;
	    }
	}
	{

    IGNORE make_token_decl ( (XI401), (XI398), (XI410), (XI445) ) ;
	}
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR781(IDENTIFIER XI779, IDENTIFIER *XO780)
{
    IDENTIFIER XI780;

  XL2_781:;
    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    IDENTIFIER XI473;
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

    XI473 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 3:
		    {
			{

    XI473 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			{

    XI473 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    XI473 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI376) = find_mem_token ( (XI779), (XI473) ) ;
	    }
	    XI779 = XI376;
	    goto XL2_781;
	}
	/*UNREACHED*/
      default:
	{
	    XI780 = XI779;
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
    *XO780 = XI780;
}

void
XR783(int *XI710)
{
    switch (CURRENT_TERMINAL) {
      case 179:
	{
	    int XI378;

	    ADVANCE_LEXER;
	    XR741 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_error_sev ( (*XI710), (XI378) ) ;
	    }
	}
	break;
      case 172: case 205: case 271: case 272: case 331:
	{
	    int XI378;

	    XR510 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_error_sev ( (*XI710), (XI378) ) ;
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
XR784(void)
{
    switch (CURRENT_TERMINAL) {
      case 262:
	{
	    IDENTIFIER XI376;

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

    begin_option ( (XI376) ) ;
	    }
	}
	break;
      default:
	{
	    IDENTIFIER XI376;

	    {

    (XI376) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    begin_option ( (XI376) ) ;
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
XR785(void)
{
    switch (CURRENT_TERMINAL) {
      case 211:
	{
	    ADVANCE_LEXER;
	    {

    IGNORE end_decl_block ( NULL_id, 1 ) ;
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
	      case 182:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    begin_decl_block ( (XI376) ) ;
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
XR786(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 197:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_decl_cond ; 
	    }
	}
	break;
      case 257:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_cond_lvalue ; 
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
XR787(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 183:
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
	      case 313:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_bitf_type ; 
	    }
	}
	break;
      case 42:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_comma_extra ; 
	    }
	}
	break;
      case 258:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 201:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_macro_redef ; 
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    XR840 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 313:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 201:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_type_redef ; 
	    }
	}
	break;
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
 (XI710) = OPT_ellipsis_extra ; 
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
XR718(unsigned *XO378, unsigned *XO474)
{
    unsigned XI378;
    unsigned XI474;

    switch (CURRENT_TERMINAL) {
      case 205:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_ON ; 
	    }
	    {
 (XI474) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
      case 65: case 172: case 331:
	{
	    unsigned XI410;
	    unsigned XI445;

	    {
		switch (CURRENT_TERMINAL) {
		  case 65:
		    {
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			  case 235:
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
 (XI410) = ( unsigned ) OPTION_ON ; 
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
	    {
		switch (CURRENT_TERMINAL) {
		  case 172:
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
	    XI474 = XI410;
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
XR788(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 179:
	{
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
	    {
 (XI710) = OPT_ellipsis_ident ; 
	    }
	}
	break;
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
 (XI710) = OPT_ellipsis_ident ; 
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
XR789(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 110:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 313:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR714 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 312:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 201:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_func_token_undef ; 
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
XR790(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 247:
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
 (XI710) = OPT_interf_incompat ; 
	    }
	}
	break;
      case 254:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_link_incompat ; 
	    }
	}
	break;
      case 260:
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
 (XI710) = OPT_member_incompat ; 
	    }
	}
	break;
      case 284:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 228:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 176:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_func_incompat ; 
	    }
	}
	break;
      case 313:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 287:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_type_qual_incompat ; 
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
 (XI710) = OPT_func_ret_void ; 
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
XR791(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 203:
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
 (XI710) = OPT_ppdir_indent_dir ; 
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
	      case 203:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ppdir_indent ; 
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
XR792(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 203:
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
	      case 265:
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
	      case 231:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ppdir_id ; 
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
 (XI710) = OPT_decl_none ; 
	    }
	}
	break;
      case 231:
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
 (XI710) = OPT_hash_ident ; 
	    }
	}
	break;
      case 265:
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
	      case 224:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 211:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_eof_nline ; 
	    }
	}
	break;
      case 312:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 201:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_token_undef ; 
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
XR793(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 332:
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
 (XI710) = OPT_func_weak ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI710) = OPT_func_proto ; 
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
XR794(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 203:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_ppdir_unknown ; 
	    }
	}
	break;
      case 216:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_escape_unknown ; 
	    }
	}
	break;
      case 278:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_pragma_unknown ; 
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
 (XI710) = OPT_decl_struct_anon ; 
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
XR409(SID_LIST_ID XI407, SID_LIST_ID *XO403)
{
    SID_LIST_ID XI403;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER XI410;
	SID_LIST_ID XI406;

	XR408 (XI407, &XI410);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    XR835 (&XI407, &XI406);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		    }
		}
		break;
	      default:
		{
		    {

    (XI406) = NULL_list ( IDENTIFIER ) ;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	{

    CONS_id ( (XI410), (XI406), (XI403) ) ;
	}
    }
    goto XL0;
  XL1:;
    SAVE_LEXER (355);
    return;
  XL0:;
    *XO403 = XI403;
}

void
XR795(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 245:
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
 (XI710) = OPT_init_aggregate ; 
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
 (XI710) = OPT_complete_struct ; 
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
XR796(int *XO710)
{
    int XI710;

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
 (XI710) = OPT_templ_export ; 
	    }
	}
	break;
      case 228:
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
 (XI710) = OPT_func_impl ; 
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
XR717(int *XO710, int *XO716)
{
    int XI710;
    int XI716;

    switch (CURRENT_TERMINAL) {
      case 180:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_assert ;
    (XI716) = OPT_ppdir_assert_ignore ;
	    }
	}
	break;
      case 224:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_file ;
    (XI716) = OPT_ppdir_file_ignore ;
	    }
	}
	break;
      case 231:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_ident ;
    (XI716) = OPT_ppdir_ident_ignore ;
	    }
	}
	break;
      case 238:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_import ;
    (XI716) = OPT_ppdir_import_ignore ;
	    }
	}
	break;
      case 241:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_import ;
    (XI716) = OPT_ppdir_import_ignore ;
	    }
	}
	break;
      case 317:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_unassert ;
    (XI716) = OPT_ppdir_unassert_ignore ;
	    }
	}
	break;
      case 331:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_warning ;
    (XI716) = OPT_ppdir_warning_ignore ;
	    }
	}
	break;
      case 332:
	{
	    ADVANCE_LEXER;
	    {

    (XI710) = OPT_ppdir_weak ;
    (XI716) = OPT_ppdir_weak_ignore ;
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
    *XO716 = XI716;
}

void
XR797(int *XO710)
{
    int XI710;

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
 (XI710) = OPT_int_operator ; 
	    }
	}
	break;
      case 274:
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
 (XI710) = OPT_int_overflow ; 
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
XR723(unsigned *XO474)
{
    unsigned XI474;

    switch (CURRENT_TERMINAL) {
      case 221:
	{
	    ADVANCE_LEXER;
	    {
 (XI474) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 248:
	{
	    ADVANCE_LEXER;
	    {
 (XI474) = ( unsigned ) OPTION_ON ; 
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
XR798(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 174:
	{
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_variable ; 
	    }
	}
	break;
      case 230:
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
 (XI710) = OPT_decl_hide ; 
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
XR799(void)
{
    switch (CURRENT_TERMINAL) {
      case 275:
	{
	    unsigned XI474;
	    unsigned XI378;
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
	    XR727 (&XI474);
	    XR507 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI710) = OPT_overload_dep ; 
	    }
	    {
 (XI716) = OPT_overload_strict ; 
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
	    }
	    {

    set_option ( (XI716), (XI474) ) ;
	    }
	}
	break;
      case 197: case 257:
	{
	    int XI710;
	    unsigned XI378;

	    XR786 (&XI710);
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
XR800(void)
{
    switch (CURRENT_TERMINAL) {
      case 179:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 258:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 176:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_macro_arg_dir ; 
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
      case 180: case 224: case 231: case 238: case 241:
      case 317: case 331: case 332:
	{
	    int XI710;
	    int XI716;
	    unsigned XI378;
	    unsigned XI474;

	    XR717 (&XI710, &XI716);
	    XR718 (&XI378, &XI474);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    set_option ( (XI710), (XI378) ) ;
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
XR801(void)
{
    switch (CURRENT_TERMINAL) {
      case 228:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 254:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_func_linkage ; 
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
      case 254:
	{
	    EXP XI378;
	    DECL_SPEC XI410;

	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			{

    XI378 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			{

    XI378 = crt_token->pp_data.exp ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {

    (XI410) = find_linkage ( (XI378) ) ;
	    }
	    {

    set_link_opt ( (XI410) ) ;
	    }
	}
	break;
      case 124: case 329:
	{
	    int XI710;
	    unsigned XI378;

	    {
		switch (CURRENT_TERMINAL) {
		  case 124:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 329:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto XL1;
		}
	    }
	    {
 (XI710) = OPT_decl_volatile ; 
	    }
	    {
 (XI378) = ( unsigned ) OPTION_ON ; 
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
XR802(void)
{
    switch (CURRENT_TERMINAL) {
      case 194:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_const_cond ; 
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
      case 254:
	{
	    unsigned XI378;
	    int XI710;

	    ADVANCE_LEXER;
	    XR723 (&XI378);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI710) = OPT_const_internal ; 
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
XR803(void)
{
    switch (CURRENT_TERMINAL) {
      case 224:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 240:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_include_full ; 
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
      case 118: case 245:
	{
	    int XI710;
	    unsigned XI378;

	    XR795 (&XI710);
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
XR804(void)
{
    switch (CURRENT_TERMINAL) {
      case 110: case 312:
	{
	    int XI710;
	    unsigned XI378;

	    XR789 (&XI710);
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
      case 134: case 228:
	{
	    int XI710;
	    unsigned XI378;

	    XR796 (&XI710);
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
XR711(int *XO710)
{
    int XI710;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    XR843 (&XI710);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI710) = OPT_conv ; 
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
XR805(void)
{
    switch (CURRENT_TERMINAL) {
      case 221:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 254:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_decl_unify ; 
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
      case 242:
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
 (XI710) = OPT_concat_string ; 
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
parse_preproc(int *XO398)
{
    int XI398;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	XR773 ();
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto XL1;
	}
	{
 (XI398) = lex_ignore_token ; 
	}
    }
    goto XL0;
  XL1:;
    {
	{
 (XI398) = lex_hash_Hpragma ; 
	}
    }
  XL0:;
    *XO398 = XI398;
}

void
XR806(void)
{
    switch (CURRENT_TERMINAL) {
      case 245:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_init_dynamic ; 
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
      case 174: case 230:
	{
	    int XI710;
	    unsigned XI378;

	    XR798 (&XI710);
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
XR807(void)
{
    switch (CURRENT_TERMINAL) {
      case 258:
	{
	    int XI710;
	    unsigned XI378;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 214:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI710) = OPT_macro_weak ; 
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
      case 285:
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
 (XI710) = OPT_weak ; 
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
parse_tendra(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 168:
	{
	    ADVANCE_LEXER;
	    XR816 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 176:
	{
	    TYPE XI824;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_as ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI824) = type_error ;
    parse_tok_type ( &(XI824) ) ;
    object_type ( (XI824), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 179:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR813 (&XI824);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 185:
	{
	    IDENTIFIER XI376;
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
 (XI825) = type_bottom ; 
	    }
	    {

    typedef_special ( (XI376), (XI825) ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 187:
	{
	    ADVANCE_LEXER;
	    XR817 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 191:
	{
	    ADVANCE_LEXER;
	    XR818 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 193:
	{
	    IDENTIFIER XI376;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 283:
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

    compute_promote_type ( (XI376) ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 195:
	{
	    ADVANCE_LEXER;
	    XR820 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 198:
	{
	    int XI474;

	    ADVANCE_LEXER;
	    {
 (XI474) = lex_define ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 206:
	{
	    ADVANCE_LEXER;
	    XR828 (&XI398);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 211:
	{
	    ADVANCE_LEXER;
	    {

    end_option ( 1 ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 217:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_exhaustive ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 245:
	{
	    ADVANCE_LEXER;
	    XR819 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 246:
	{
	    ADVANCE_LEXER;
	    XR821 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 247:
	{
	    int XI474;

	    ADVANCE_LEXER;
	    {
 (XI474) = crt_interface ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 267:
	{
	    int XI474;

	    ADVANCE_LEXER;
	    {
 (XI474) = lex_no_Hdef ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 277:
	{
	    int XI410;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {
 (XI410) = lex_postpone ; 
	    }
	    XR496 (XI410);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 280:
	{
	    ADVANCE_LEXER;
	    XR812 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 284:
	{
	    TYPE XI826;
	    TYPE XI449;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {

    (XI826) = type_error ;
    parse_tok_type ( &(XI826) ) ;
    object_type ( (XI826), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
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
	    {

    set_promote_type ( (XI826), (XI449), ntype_ellipsis ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 291:
	{
	    int XI474;

	    ADVANCE_LEXER;
	    {
 (XI474) = lex_ignore ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 298:
	{
	    ADVANCE_LEXER;
	    XR829 (&XI398);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 306:
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
	    XR498 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 313:
	{
	    IDENTIFIER XI376;
	    TYPE XI827;

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
	      case 107:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 185:
		    {
			ADVANCE_LEXER;
			{
 (XI827) = type_bottom ; 
			}
		    }
		    break;
		  case 286:
		    {
			ADVANCE_LEXER;
			{
 (XI827) = type_ptrdiff_t ; 
			}
		    }
		    break;
		  case 299:
		    {
			ADVANCE_LEXER;
			{
 (XI827) = type_size_t ; 
			}
		    }
		    break;
		  case 156:
		    {
			ADVANCE_LEXER;
			{
 (XI827) = type_wchar_t ; 
			}
		    }
		    break;
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
			XR860 (&XI827);
			if ((CURRENT_TERMINAL) == 355) {
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

    typedef_special ( (XI376), (XI827) ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 318:
	{
	    ADVANCE_LEXER;
	    XR822 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 322:
	{
	    int XI410;

	    ADVANCE_LEXER;
	    {

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
	    }
	    {
 (XI410) = lex_unpostpone ; 
	    }
	    XR496 (XI410);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
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
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 251:
	{
	    IDENTIFIER XI376;
	    int XI823;

	    XR550 (&XI376);
	    switch (CURRENT_TERMINAL) {
	      case 107:
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    XR551 (&XI823);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    define_keyword ( (XI376), (XI823) ) ;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 260:
	{
	    XR483 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
	    }
	}
	break;
      case 312:
	{
	    XR457 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {
 (XI398) = lex_hash_Hpragma ; 
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
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{
 (XI398) = lex_hash_Hpragma ; 
	}
    }
  XL0:;
    *XO398 = XI398;
}

/* END OF FILE */
