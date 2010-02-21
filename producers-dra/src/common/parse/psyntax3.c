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
XR551(int *XO398)
{
    int XI398;

    switch (CURRENT_TERMINAL) {
      case 126:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_asm ; 
	    }
	}
	break;
      case 206:
	{
	    ADVANCE_LEXER;
	    XR854 (&XI398);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
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
      case 223:
	{
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
 (XI398) = lex_fall ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_inline ; 
	    }
	}
	break;
      case 141:
	{
	    ADVANCE_LEXER;
	    {

    (XI398) = crt_lex_token ;
    if ( (XI398) >= FIRST_SYMBOL && (XI398) <= LAST_SYMBOL ) crt_lex_token = lex_plus ;
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
      case 298:
	{
	    ADVANCE_LEXER;
	    XR855 (&XI398);
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
	      case 292:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_representation ; 
	    }
	}
	break;
      case 332:
	{
	    ADVANCE_LEXER;
	    {
 (XI398) = lex_weak ; 
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

    (XI398) = find_keyword ( (XI376) ) ;
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
XR448(DECL_SPEC *XO410)
{
    DECL_SPEC XI410;

    switch (CURRENT_TERMINAL) {
      case 142:
	{
	    ADVANCE_LEXER;
	    {
 (XI410) = dspec_private ; 
	    }
	}
	break;
      case 143:
	{
	    ADVANCE_LEXER;
	    {
 (XI410) = dspec_protected ; 
	    }
	}
	break;
      case 144:
	{
	    ADVANCE_LEXER;
	    {
 (XI410) = dspec_public ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI410) = dspec_public ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *XO410 = XI410;
}

void
XR759(int *XO710)
{
    int XI710;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP XI449;

	switch (CURRENT_TERMINAL) {
	  case 215:
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
    (XI710) = find_error_no ( s, 0 ) ;
    if ( (XI710) == -1 ) {
	report ( preproc_loc, ERR_pragma_error_bad ( s ) ) ;
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
XR483(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	TYPE XI398;
	IDENTIFIER XI376;

	{

    in_token_decl = 1 ;
	}
	switch (CURRENT_TERMINAL) {
	  case 260:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 201:
	    break;
	  default:
	    goto XL1;
	}
	ADVANCE_LEXER;
	{

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
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

    in_token_decl = 0 ;
	}
	{

    if ( define_mem_macro ( (XI376), (XI398) ) ) no_declarations++ ;
	}
    }
    return;
  XL1:;
    SAVE_LEXER (355);
    return;
}

void
XR496(int XI410)
{
  XL2_496:;
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

    preserve_id ( (XI376), (XI410) ) ;
	    }
	    goto XL2_496;
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
XR743(unsigned *XO446)
{
    unsigned XI446;

    switch (CURRENT_TERMINAL) {
      case 179:
	{
	    ADVANCE_LEXER;
	    XR734 (&XI446);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      default:
	{
	    {
 (XI446) = CAST_EXPLICIT ; 
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
    *XO446 = XI446;
}

void
XR508(unsigned *XO378)
{
    unsigned XI378;

    switch (CURRENT_TERMINAL) {
      case 172:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 205:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_ON ; 
	    }
	}
	break;
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
XR414(SID_LIST_ID *XO403)
{
    SID_LIST_ID XI403;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	IDENTIFIER XI376;
	SID_LIST_ID XI406;

	XR412 (&XI376);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    XR833 (&XI406);
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
XR552(void)
{
    switch (CURRENT_TERMINAL) {
      case 318:
	{
	    IDENTIFIER XI376;

	    ADVANCE_LEXER;
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
      case 251:
	{
	    IDENTIFIER XI376;
	    int XI398;

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
	    XR551 (&XI398);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    define_keyword ( (XI376), (XI398) ) ;
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
XR498(void)
{
  XL2_498:;
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

    preserve_id ( (XI376), lex_suspend ) ;
	    }
	    goto XL2_498;
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
XR507(unsigned *XO378)
{
    unsigned XI378;

    switch (CURRENT_TERMINAL) {
      case 172:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_OFF ; 
	    }
	}
	break;
      case 205:
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
XR447(int *XO445, int *XO446)
{
    int XI445;
    int XI446;

    switch (CURRENT_TERMINAL) {
      case 98:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = 0 ; 
	    }
	    {
 (XI446) = 1 ; 
	    }
	}
	break;
      case 257:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = 1 ; 
	    }
	    {
 (XI446) = 0 ; 
	    }
	}
	break;
      case 295:
	{
	    ADVANCE_LEXER;
	    {
 (XI445) = 0 ; 
	    }
	    {
 (XI446) = 0 ; 
	    }
	}
	break;
      default:
	{
	    {
 (XI445) = 0 ; 
	    }
	    {
 (XI446) = 0 ; 
	    }
	}
	break;
      case 355:
	return;
    }
    *XO445 = XI445;
    *XO446 = XI446;
}

void
XR755(EXP *XO445)
{
    EXP XI445;

    switch (CURRENT_TERMINAL) {
      case 179:
	{
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
	    ADVANCE_LEXER;
	    {

    (XI445) = NULL_exp ;
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
XR408(SID_LIST_ID XI407, IDENTIFIER *XO376)
{
    IDENTIFIER XI376;

    switch (CURRENT_TERMINAL) {
      case 218:
	{
	    IDENTIFIER XI402;

	    ADVANCE_LEXER;
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
	    {

    (XI376) = prog_tok_param ( (XI402), NULL_type, tok_exp_tag, (XI407) ) ;
	    }
	}
	break;
      case 261:
	{
	    TYPE XI398;
	    IDENTIFIER XI402;

	    ADVANCE_LEXER;
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
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
	    {

    (XI376) = prog_tok_param ( (XI402), (XI398), tok_member_tag, (XI407) ) ;
	    }
	}
	break;
      case 282:
	{
	    IDENTIFIER XI402;

	    ADVANCE_LEXER;
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
	    {

    (XI376) = prog_tok_param ( (XI402), NULL_type, tok_proc_tag, (XI407) ) ;
	    }
	}
	break;
      case 303:
	{
	    IDENTIFIER XI402;

	    ADVANCE_LEXER;
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
	    {

    (XI376) = prog_tok_param ( (XI402), NULL_type, tok_stmt_tag, (XI407) ) ;
	    }
	}
	break;
      case 314:
	{
	    TYPE XI398;

	    ADVANCE_LEXER;
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
	    }
	    {

    IDENTIFIER tid = DEREF_id ( type_name ( (XI398) ) ) ;
    (XI376) = prog_tok_param ( tid, (XI398), tok_type_tag, (XI407) ) ;
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
    *XO376 = XI376;
}

void
XR397(TOKEN *XO401)
{
    TOKEN XI401;

    switch (CURRENT_TERMINAL) {
      case 177:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_arith ) ;
	    }
	}
	break;
      case 188:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_lang ) ;
	    }
	}
	break;
      case 218:
	{
	    int XI445;
	    int XI446;
	    TYPE XI398;

	    ADVANCE_LEXER;
	    XR447 (&XI445, &XI446);
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      case 355:
		RESTORE_LEXER;
		goto XL1;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI401) = make_exp_token ( (XI398), (XI445), (XI446) ) ;
	    }
	}
	break;
      case 225:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_float ) ;
	    }
	}
	break;
      case 227:
	{
	    TYPE XI398;

	    ADVANCE_LEXER;
	    {

    (XI398) = type_error ;
    parse_tok_type ( &(XI398) ) ;
    object_type ( (XI398), id_function_tag ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI401) = make_func_token ( (XI398) ) ;
	    }
	}
	break;
      case 250:
	{
	    ADVANCE_LEXER;
	    {

    MAKE_tok_snat ( NULL_nat, (XI401) ) ;
	    }
	}
	break;
      case 261:
	{
	    DECL_SPEC XI410;
	    TYPE XI398;
	    TYPE XI449;

	    ADVANCE_LEXER;
	    XR448 (&XI410);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	    {

    (XI398) = type_error ;
    parse_mem_type ( &(XI398) ) ;
    object_type ( (XI398), null_tag ) ;
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
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto XL1;
	    }
	    ADVANCE_LEXER;
	    {

    (XI401) = make_member_token ( (XI398), (XI449), (XI410) ) ;
	    }
	}
	break;
      case 263:
	{
	    ADVANCE_LEXER;
	    {

    MAKE_tok_nat ( NULL_nat, (XI401) ) ;
	    }
	}
	break;
      case 282:
	{
	    ADVANCE_LEXER;
	    XR832 (&XI401);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto XL1;
	    }
	}
	break;
      case 296:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_scalar ) ;
	    }
	}
	break;
      case 303:
	{
	    ADVANCE_LEXER;
	    {

    MAKE_tok_stmt ( NULL_exp, (XI401) ) ;
	    }
	}
	break;
      case 305:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_struct ) ;
	    }
	}
	break;
      case 314:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_none ) ;
	    }
	}
	break;
      case 320:
	{
	    ADVANCE_LEXER;
	    {

    (XI401) = make_type_token ( btype_union ) ;
	    }
	}
	break;
      case 328:
	{
	    ADVANCE_LEXER;
	    XR831 (&XI401);
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
    *XO401 = XI401;
}

void
XR509(unsigned *XO378)
{
    unsigned XI378;

    switch (CURRENT_TERMINAL) {
      case 331:
	{
	    ADVANCE_LEXER;
	    {
 (XI378) = ( unsigned ) OPTION_WARN ; 
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
      case 355:
	return;
    }
    *XO378 = XI378;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
