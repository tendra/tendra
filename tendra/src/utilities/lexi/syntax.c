/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/utilities/lexi/syntax.sid
 * and
 *	/u/g/release/Source/src/utilities/lexi/syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


/*
    		 Crown Copyright (c) 1997
    
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
#include "char.h"
#include "error.h"
#include "lex.h"
#include "syntax.h"
#include "xalloc.h"


/*
    PARSER TYPES

    These types give the implementation of the types used in the syntax.
*/

typedef letter *SID_CHARS ;
typedef char *SID_STRING ;


/*
    SID IDENTIFIER PREFIX

    This string is added to the start of each sid identifier.
*/

char *sid_prefix = "lex_" ;


/*
    CURRENT CONDITIONAL

    This variable is used to record the current conditional.
*/

static char *crt_cond = NULL ;


/*
    COMPILATION MODE

    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif



/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRstring_Hplus PROTO_S ((SID_STRING *));
static void ZRchars PROTO_S ((SID_CHARS *));
static void ZRargs PROTO_S ((int *));
static void ZRtrigraph_Hdefn PROTO_S ((void));
static void ZR60 PROTO_S ((SID_STRING *, int *));
extern void read_lex PROTO_S ((void));
static void ZR68 PROTO_S ((void));
static void ZRcommand_Hlist PROTO_S ((void));
static void ZRkeyword_Hdefn PROTO_S ((void));
static void ZRif_Hcommand PROTO_S ((void));
static void ZRcommand PROTO_S ((void));
static void ZRtoken_Hdefn PROTO_S ((void));

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRstring_Hplus PROTO_N ((ZOs))
  PROTO_T (SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_STRING ZIa;

	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    {
 ZIa = "0123456789" ; 
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZIa = xstrcpy ( token_buff ) ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    {
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 20:
		{
		    SID_STRING ZIb;

		    ADVANCE_LEXER;
		    ZRstring_Hplus (&ZIb);
		    if ((CURRENT_TERMINAL) == 23) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
		    }
		}
		break;
	      default:
		{
		    ZIs = ZIa;
		}
		break;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (23);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRchars PROTO_N ((ZOc))
  PROTO_T (SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_STRING ZIs;

	ZRstring_Hplus (&ZIs);
	if ((CURRENT_TERMINAL) == 23) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIc) = make_string ( (ZIs) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (23);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRargs PROTO_N ((ZOa))
  PROTO_T (int *ZOa)
{
    int ZIa;

    switch (CURRENT_TERMINAL) {
      case 13:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 14:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIa) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZIa) = 0 ; 
	    }
	}
	break;
      case 23:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (23);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRtrigraph_Hdefn PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_CHARS ZIs;
	SID_STRING ZIt;

	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRchars (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  case 23:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 23) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    char *data [3] ;
    data [0] = (ZIt) ;
    data [1] = NULL ;
    data [2] = crt_cond ;
    add_char ( pre_pass, (ZIs), data ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR60 PROTO_N ((ZOi, ZOa))
  PROTO_T (SID_STRING *ZOi X int *ZOa)
{
    SID_STRING ZIi;
    int ZIa;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    ZRargs (&ZIa);
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    {

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy_v ( buff, sid_prefix ) ;
    n = ( int ) strlen ( buff ) ;
    for ( s = token_buff ; *s ; s++ ) {
	if ( *s == '-' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = 'H' ;
	} else if ( *s == '_' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = '_' ;
	} else {
	    buff [ n++ ] = *s ;
	}
	if ( n >= 900 ) {
	    error ( ERROR_SERIOUS, "Identifier too long" ) ;
	    break ;
	}
    }
    buff [n] = 0 ;
    ZIi = xstrcpy ( buff ) ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIa) = 0 ; 
	    }
	}
	break;
      case 23:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (23);
    return;
  ZL0:;
    *ZOi = ZIi;
    *ZOa = ZIa;
}

void
read_lex PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	ZRcommand_Hlist ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 18:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    error ( ERROR_SERIOUS, "Syntax error" ) ;
		}
	    }
	  ZL2:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR68 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZIi;
	    SID_CHARS ZIs;

	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 19:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRchars (&ZIs);
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    make_group ( (ZIi), (ZIs) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 10:
	{
	    SID_CHARS ZIs;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 19:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRchars (&ZIs);
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( white_space ) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    white_space = (ZIs) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 23:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZRcommand_Hlist PROTO_Z ()
{
  ZL2_command_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 6: case 7: case 8: case 9: case 11:
      case 15: case 21:
	{
	    ZRcommand ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	}
	/*UNREACHED*/
      case 23:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	{

    error ( ERROR_SERIOUS, "Syntax error" ) ;
	}
    }
}

static void
ZRkeyword_Hdefn PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_STRING ZIs;
	SID_STRING ZIi;
	int ZIa;

	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 2:
	    {

    ZIs = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR60 (&ZIi, &ZIa);
	if ((CURRENT_TERMINAL) == 23) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    char *data [3] ;
    data [0] = (ZIi) ;
    data [1] = ( (ZIa) ? "()" : NULL ) ;
    data [2] = crt_cond ;
    add_keyword ( (ZIs), data ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZRif_Hcommand PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_STRING ZIi;
	SID_STRING ZIj;

	switch (CURRENT_TERMINAL) {
	  case 11:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 13:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 14:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIj) = crt_cond ;
	}
	{

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
	}
	ZRcommand ();
	{
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 12:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
		{

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
		}
		ZRcommand ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		{

    crt_cond = (ZIj) ;
		}
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    crt_cond = (ZIj) ;
		}
	    }
	  ZL2:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZRcommand PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ADVANCE_LEXER;
	    ZR68 ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 15:
	{
	    ADVANCE_LEXER;
	    ZRcommand_Hlist ();
	    switch (CURRENT_TERMINAL) {
	      case 16:
		break;
	      case 23:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 21:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 11:
	{
	    ZRif_Hcommand ();
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 7:
	{
	    ZRkeyword_Hdefn ();
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      case 23:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 9:
	{
	    ZRtoken_Hdefn ();
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      case 23:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 8:
	{
	    ZRtrigraph_Hdefn ();
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      case 23:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 23:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZRtoken_Hdefn PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_CHARS ZIs;
	SID_STRING ZIi;
	int ZIa;

	switch (CURRENT_TERMINAL) {
	  case 9:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRchars (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  case 23:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR60 (&ZIi, &ZIa);
	if ((CURRENT_TERMINAL) == 23) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    char *data [3] ;
    data [0] = (ZIi) ;
    data [1] = ( (ZIa) ? "()" : NULL ) ;
    data [2] = crt_cond ;
    add_char ( main_pass, (ZIs), data ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
