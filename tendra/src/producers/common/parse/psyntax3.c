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
XR550 PROTO_N ((XO397))
  PROTO_T (int *XO397)
{
    int XI397;

    switch (CURRENT_TERMINAL) {
      case 126:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_asm ; 
	    }
	}
	break;
      case 205:
	{
	    ADVANCE_LEXER;
	    XR852 (&XI397);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
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
      case 222:
	{
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
 (XI397) = lex_fall ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_inline ; 
	    }
	}
	break;
      case 141:
	{
	    ADVANCE_LEXER;
	    {

    (XI397) = crt_lex_token ;
    if ( (XI397) >= FIRST_SYMBOL && (XI397) <= LAST_SYMBOL ) crt_lex_token = lex_plus ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 69:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 297:
	{
	    ADVANCE_LEXER;
	    XR853 (&XI397);
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
	      case 291:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_representation ; 
	    }
	}
	break;
      case 331:
	{
	    ADVANCE_LEXER;
	    {
 (XI397) = lex_weak ; 
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

    (XI397) = find_keyword ( (XI375) ) ;
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
XR447 PROTO_N ((XO409))
  PROTO_T (DECL_SPEC *XO409)
{
    DECL_SPEC XI409;

    switch (CURRENT_TERMINAL) {
      case 142:
	{
	    ADVANCE_LEXER;
	    {
 (XI409) = dspec_private ; 
	    }
	}
	break;
      case 143:
	{
	    ADVANCE_LEXER;
	    {
 (XI409) = dspec_protected ; 
	    }
	}
	break;
      case 144:
	{
	    ADVANCE_LEXER;
	    {
 (XI409) = dspec_public ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI409) = dspec_public ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *XO409 = XI409;
}

void
XR757 PROTO_N ((XO708))
  PROTO_T (int *XO708)
{
    int XI708;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP XI448;

	switch (CURRENT_TERMINAL) {
	  case 214:
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
    (XI708) = find_error_no ( s, 0 ) ;
    if ( (XI708) == -1 ) {
	report ( preproc_loc, ERR_pragma_error_bad ( s ) ) ;
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
XR741 PROTO_N ((XO445))
  PROTO_T (unsigned *XO445)
{
    unsigned XI445;

    switch (CURRENT_TERMINAL) {
      case 178:
	{
	    ADVANCE_LEXER;
	    XR732 (&XI445);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI445) = CAST_EXPLICIT ; 
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
    *XO445 = XI445;
}

void
XR482 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE XI397;
	IDENTIFIER XI375;

	{

    in_token_decl = 1 ;
	}
	switch (CURRENT_TERMINAL) {
	  case 259:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 200:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	{

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 41:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
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

    in_token_decl = 0 ;
	}
	{

    if ( define_mem_macro ( (XI375), (XI397) ) ) no_declarations++ ;
	}
    }
    return;
  XL1:;
    SAVE_LEXER (354);
    return;
}

void
XR495 PROTO_N ((XI409))
  PROTO_T (int XI409)
{
  XL2_495:;
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

    preserve_id ( (XI375), (XI409) ) ;
	    }
	    goto XL2_495;
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
XR507 PROTO_N ((XO377))
  PROTO_T (unsigned *XO377)
{
    unsigned XI377;

    switch (CURRENT_TERMINAL) {
      case 172:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 204:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
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
XR413 PROTO_N ((XO402))
  PROTO_T (SID_LIST_ID *XO402)
{
    SID_LIST_ID XI402;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER XI375;
	SID_LIST_ID XI405;

	XR411 (&XI375);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    XR831 (&XI405);
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
XR551 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 317:
	{
	    IDENTIFIER XI375;

	    ADVANCE_LEXER;
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
      case 250:
	{
	    IDENTIFIER XI375;
	    int XI397;

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
	    XR550 (&XI397);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    define_keyword ( (XI375), (XI397) ) ;
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
XR497 PROTO_Z ()
{
  XL2_497:;
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

    preserve_id ( (XI375), lex_suspend ) ;
	    }
	    goto XL2_497;
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
XR506 PROTO_N ((XO377))
  PROTO_T (unsigned *XO377)
{
    unsigned XI377;

    switch (CURRENT_TERMINAL) {
      case 172:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 204:
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
XR753 PROTO_N ((XO444))
  PROTO_T (EXP *XO444)
{
    EXP XI444;

    switch (CURRENT_TERMINAL) {
      case 178:
	{
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
	    ADVANCE_LEXER;
	    {

    (XI444) = NULL_exp ;
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
XR446 PROTO_N ((XO444, XO445))
  PROTO_T (int *XO444 X int *XO445)
{
    int XI444;
    int XI445;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (XI444) = 0 ; 
	    }
	    {
 (XI445) = 1 ; 
	    }
	}
	break;
      case 256:
	{
	    ADVANCE_LEXER;
	    {
 (XI444) = 1 ; 
	    }
	    {
 (XI445) = 0 ; 
	    }
	}
	break;
      case 294:
	{
	    ADVANCE_LEXER;
	    {
 (XI444) = 0 ; 
	    }
	    {
 (XI445) = 0 ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI444) = 0 ; 
	    }
	    {
 (XI445) = 0 ; 
	    }
	}
	break;
      case 354:
	return;
    }
    *XO444 = XI444;
    *XO445 = XI445;
}

void
XR407 PROTO_N ((XI406, XO375))
  PROTO_T (SID_LIST_ID XI406 X IDENTIFIER *XO375)
{
    IDENTIFIER XI375;

    switch (CURRENT_TERMINAL) {
      case 217:
	{
	    IDENTIFIER XI401;

	    ADVANCE_LEXER;
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
	    {

    (XI375) = prog_tok_param ( (XI401), NULL_type, tok_exp_tag, (XI406) ) ;
	    }
	}
	break;
      case 260:
	{
	    TYPE XI397;
	    IDENTIFIER XI401;

	    ADVANCE_LEXER;
	    {

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
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
	    {

    (XI375) = prog_tok_param ( (XI401), (XI397), tok_member_tag, (XI406) ) ;
	    }
	}
	break;
      case 281:
	{
	    IDENTIFIER XI401;

	    ADVANCE_LEXER;
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
	    {

    (XI375) = prog_tok_param ( (XI401), NULL_type, tok_proc_tag, (XI406) ) ;
	    }
	}
	break;
      case 302:
	{
	    IDENTIFIER XI401;

	    ADVANCE_LEXER;
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
	    {

    (XI375) = prog_tok_param ( (XI401), NULL_type, tok_stmt_tag, (XI406) ) ;
	    }
	}
	break;
      case 313:
	{
	    TYPE XI397;

	    ADVANCE_LEXER;
	    {

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    {

    IDENTIFIER tid = DEREF_id ( type_name ( (XI397) ) ) ;
    (XI375) = prog_tok_param ( tid, (XI397), tok_type_tag, (XI406) ) ;
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
    *XO375 = XI375;
}

void
XR396 PROTO_N ((XO400))
  PROTO_T (TOKEN *XO400)
{
    TOKEN XI400;

    switch (CURRENT_TERMINAL) {
      case 176:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_arith ) ;
	    }
	}
	break;
      case 187:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_lang ) ;
	    }
	}
	break;
      case 217:
	{
	    int XI444;
	    int XI445;
	    TYPE XI397;

	    ADVANCE_LEXER;
	    XR446 (&XI444, &XI445);
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      case 354:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI400) = make_exp_token ( (XI397), (XI444), (XI445) ) ;
	    }
	}
	break;
      case 224:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_float ) ;
	    }
	}
	break;
      case 226:
	{
	    TYPE XI397;

	    ADVANCE_LEXER;
	    {

    (XI397) = type_error ;
    parse_tok_type ( &(XI397) ) ;
    object_type ( (XI397), id_function_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI400) = make_func_token ( (XI397) ) ;
	    }
	}
	break;
      case 249:
	{
	    ADVANCE_LEXER;
	    {

    MAKE_tok_snat ( NULL_nat, (XI400) ) ;
	    }
	}
	break;
      case 260:
	{
	    DECL_SPEC XI409;
	    TYPE XI397;
	    TYPE XI448;

	    ADVANCE_LEXER;
	    XR447 (&XI409);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    (XI397) = type_error ;
    parse_mem_type ( &(XI397) ) ;
    object_type ( (XI397), null_tag ) ;
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
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI400) = make_member_token ( (XI397), (XI448), (XI409) ) ;
	    }
	}
	break;
      case 262:
	{
	    ADVANCE_LEXER;
	    {

    MAKE_tok_nat ( NULL_nat, (XI400) ) ;
	    }
	}
	break;
      case 281:
	{
	    ADVANCE_LEXER;
	    XR830 (&XI400);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 295:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_scalar ) ;
	    }
	}
	break;
      case 302:
	{
	    ADVANCE_LEXER;
	    {

    MAKE_tok_stmt ( NULL_exp, (XI400) ) ;
	    }
	}
	break;
      case 304:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_struct ) ;
	    }
	}
	break;
      case 313:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_none ) ;
	    }
	}
	break;
      case 319:
	{
	    ADVANCE_LEXER;
	    {

    (XI400) = make_type_token ( btype_union ) ;
	    }
	}
	break;
      case 327:
	{
	    ADVANCE_LEXER;
	    XR829 (&XI400);
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
    *XO400 = XI400;
}

void
XR508 PROTO_N ((XO377))
  PROTO_T (unsigned *XO377)
{
    unsigned XI377;

    switch (CURRENT_TERMINAL) {
      case 330:
	{
	    ADVANCE_LEXER;
	    {
 (XI377) = ( unsigned ) OPTION_WARN ; 
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
      case 354:
	return;
    }
    *XO377 = XI377;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
