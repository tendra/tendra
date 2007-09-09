/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 30 "syntax.act"

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

#include <string.h>

#include "char.h"
#include "shared/error.h"
#include "lex.h"
#include "syntax.h"
#include "shared/xalloc.h"


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


#line 95 "tmp.syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRstring_Hplus(SID_STRING *);
static void ZRchars(SID_CHARS *);
static void ZRargs(int *);
static void ZRtrigraph_Hdefn(void);
static void ZR60(SID_STRING *, int *);
extern void read_lex(void);
static void ZR68(void);
static void ZRcommand_Hlist(void);
static void ZRkeyword_Hdefn(void);
static void ZRif_Hcommand(void);
static void ZRcommand(void);
static void ZRtoken_Hdefn(void);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	SID_STRING ZIa;

	/* BEGINNING OF INLINE: 44 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 218 "syntax.act"
 ZIa = "0123456789" ; 
#line 137 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: digit */
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    /* BEGINNING OF EXTRACT: lower */
		    {
#line 217 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 149 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: lower */
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    /* BEGINNING OF EXTRACT: string */
		    {
#line 205 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 162 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: string */
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    /* BEGINNING OF EXTRACT: upper */
		    {
#line 216 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 174 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 44 */
	/* BEGINNING OF INLINE: 46 */
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
		    /* BEGINNING OF ACTION: string-concat */
		    {
#line 230 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 203 "tmp.syntax.c"
		    }
		    /* END OF ACTION: string-concat */
		}
		break;
	      default:
		{
		    ZIs = ZIa;
		}
		break;
	    }
	}
	/* END OF INLINE: 46 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (23);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRchars(SID_CHARS *ZOc)
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
	/* BEGINNING OF ACTION: make-chars */
	{
#line 242 "syntax.act"

    (ZIc) = make_string ( (ZIs) ) ;
#line 246 "tmp.syntax.c"
	}
	/* END OF ACTION: make-chars */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (23);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRargs(int *ZOa)
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
	    /* BEGINNING OF ACTION: true */
	    {
#line 379 "syntax.act"
 (ZIa) = 1 ; 
#line 278 "tmp.syntax.c"
	    }
	    /* END OF ACTION: true */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: false */
	    {
#line 380 "syntax.act"
 (ZIa) = 0 ; 
#line 289 "tmp.syntax.c"
	    }
	    /* END OF ACTION: false */
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
ZRtrigraph_Hdefn(void)
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
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 280 "syntax.act"

    char *data [3] ;
    data [0] = (ZIt) ;
    data [1] = NULL ;
    data [2] = crt_cond ;
    add_char ( pre_pass, (ZIs), data ) ;
#line 347 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR60(SID_STRING *ZOi, int *ZOa)
{
    SID_STRING ZIi;
    int ZIa;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 160 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 371 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
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
	    /* BEGINNING OF EXTRACT: sid-identifier */
	    {
#line 172 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, sid_prefix ) ;
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
#line 410 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: false */
	    {
#line 380 "syntax.act"
 (ZIa) = 0 ; 
#line 418 "tmp.syntax.c"
	    }
	    /* END OF ACTION: false */
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
read_lex(void)
{
    if ((CURRENT_TERMINAL) == 23) {
	return;
    }
    {
	ZRcommand_Hlist ();
	/* BEGINNING OF INLINE: 67 */
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
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 389 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 468 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 67 */
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZR68(void)
{
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZIi;
	    SID_CHARS ZIs;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 160 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 496 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
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
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 269 "syntax.act"

    make_group ( (ZIi), (ZIs) ) ;
#line 517 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-group */
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
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 255 "syntax.act"

    if ( white_space ) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    white_space = (ZIs) ;
#line 554 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-white */
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
ZRcommand_Hlist(void)
{
  ZL2_command_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 6: case 7: case 8: case 9: case 11:
      case 15: case 21:
	{
	    ZRcommand ();
	    /* BEGINNING OF INLINE: command-list */
	    if ((CURRENT_TERMINAL) == 23) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	    /* END OF INLINE: command-list */
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
	/* BEGINNING OF ACTION: syntax-error */
	{
#line 389 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 609 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZRkeyword_Hdefn(void)
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
	    /* BEGINNING OF EXTRACT: string */
	    {
#line 205 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 640 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
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
	/* BEGINNING OF ACTION: make-keyword */
	{
#line 310 "syntax.act"

    char *data [3] ;
    data [0] = (ZIi) ;
    data [1] = ( (ZIa) ? "()" : NULL ) ;
    data [2] = crt_cond ;
    add_keyword ( (ZIs), data ) ;
#line 669 "tmp.syntax.c"
	}
	/* END OF ACTION: make-keyword */
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZRif_Hcommand(void)
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
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 160 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 710 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
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
	/* BEGINNING OF ACTION: get-condition */
	{
#line 357 "syntax.act"

    (ZIj) = crt_cond ;
#line 730 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 325 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 742 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand ();
	/* BEGINNING OF INLINE: 65 */
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
		/* BEGINNING OF ACTION: compl-condition */
		{
#line 340 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 771 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand ();
		if ((CURRENT_TERMINAL) == 23) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 368 "syntax.act"

    crt_cond = (ZIj) ;
#line 784 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 368 "syntax.act"

    crt_cond = (ZIj) ;
#line 796 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 65 */
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

static void
ZRcommand(void)
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
ZRtoken_Hdefn(void)
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
	/* BEGINNING OF ACTION: make-token */
	{
#line 295 "syntax.act"

    char *data [3] ;
    data [0] = (ZIi) ;
    data [1] = ( (ZIa) ? "()" : NULL ) ;
    data [2] = crt_cond ;
    add_char ( main_pass, (ZIs), data ) ;
#line 953 "tmp.syntax.c"
	}
	/* END OF ACTION: make-token */
    }
    return;
  ZL1:;
    SAVE_LEXER (23);
    return;
}

/* BEGINNING OF TRAILER */

#line 394 "syntax.act"

#line 967 "tmp.syntax.c"

/* END OF FILE */
