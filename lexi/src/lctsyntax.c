/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 21 "lctsyntax.act"

/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id:$
 */
 
#include "lctsyntax.h"
#include "lctlex.h"
#include "error.h"

#define ADVANCE_LEXER ADVANCE_LCT_LEXER
#define CURRENT_TERMINAL CURRENT_LCT_TERMINAL 
#define SAVE_LEXER SAVE_LCT_LEXER
#define RESTORE_LEXER RESTORE_LCT_LEXER

/*
This will be changed to use nstring eds library as soon as it is extracted from
tld and sid 
*/
typedef mytmpstring* StringP ; 

#line 61 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRgrp_Hof_Hletters(StringP);
static void ZRletters(StringP, int *);
static void ZR49(void);
static void ZR52(void);
static void ZR53(void);
static void ZR54(void);
extern void read_lct_unit(void);
static void ZR55(void);
static void ZR65(StringP, int, StringP *, int *);
static void ZRheader_Hstmnt(void);
static void ZRtrailer_Hstmnt(void);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRgrp_Hof_Hletters(StringP ZIs)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	int ZIb;

	ZRletters (ZIs, &ZIb);
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: error-if-truncated */
	{
#line 138 "lctsyntax.act"

	if(!(ZIb))
		error(ERROR_SERIOUS, "Header or trailer too long truncated" );
#line 102 "lctsyntax.c"
	}
	/* END OF ACTION: error-if-truncated */
	/* BEGINNING OF INLINE: 37 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 8:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: E_unexpected_eof */
		    {
#line 169 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Unexpected End of File inside @{ @} block") ;
#line 116 "lctsyntax.c"
		    }
		    /* END OF ACTION: E_unexpected_eof */
		}
		break;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 37 */
    }
    return;
  ZL1:;
    SAVE_LEXER (11);
    return;
}

static void
ZRletters(StringP ZI61, int *ZO64)
{
    int ZI64;

    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	int ZIb;
	StringP ZI63;

	/* BEGINNING OF ACTION: true */
	{
#line 110 "lctsyntax.act"

	(ZIb) = 1 ;
#line 150 "lctsyntax.c"
	}
	/* END OF ACTION: true */
	ZR65 (ZI61, ZIb, &ZI63, &ZI64);
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (11);
    return;
  ZL0:;
    *ZO64 = ZI64;
}

static void
ZR49(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 3:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_define */
	{
#line 159 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '='") ;

#line 191 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_define */
    }
}

static void
ZR52(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 5:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_comma */
	{
#line 155 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ','") ;
#line 220 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_comma */
    }
}

static void
ZR53(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_code_start */
	{
#line 151 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@{'") ;
#line 249 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_code_start */
    }
}

static void
ZR54(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_code_end */
	{
#line 147 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@}'") ;
#line 278 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_code_end */
    }
}

void
read_lct_unit(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 57 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ZRheader_Hstmnt ();
		    if ((CURRENT_TERMINAL) == 11) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 57 */
	/* BEGINNING OF INLINE: 58 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    ZRtrailer_Hstmnt ();
		    if ((CURRENT_TERMINAL) == 11) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 58 */
	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E-syntax-error */
	{
#line 143 "lctsyntax.act"

	    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 341 "lctsyntax.c"
	}
	/* END OF ACTION: E-syntax-error */
    }
}

static void
ZR55(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 4:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_semicolon */
	{
#line 164 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ';'") ;
#line 370 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_semicolon */
    }
}

static void
ZR65(StringP ZI61, int ZI62, StringP *ZO63, int *ZO64)
{
    StringP ZI63;
    int ZI64;

  ZL2_65:;
    switch (CURRENT_TERMINAL) {
      case 2:
	{
	    char ZIc;
	    int ZIb3;
	    int ZIb;

	    /* BEGINNING OF EXTRACT: letter */
	    {
#line 105 "lctsyntax.act"

	ZIc = saved_lct_letter ;
#line 395 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: letter */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-letter */
	    {
#line 134 "lctsyntax.act"

	(ZIb3) = append_to_string((ZI61), (ZIc)) ;
#line 404 "lctsyntax.c"
	    }
	    /* END OF ACTION: append-letter */
	    /* BEGINNING OF ACTION: logical-or */
	    {
#line 114 "lctsyntax.act"

	(ZIb) =( (ZI62) || (ZIb3) ) ;
#line 412 "lctsyntax.c"
	    }
	    /* END OF ACTION: logical-or */
	    /* BEGINNING OF INLINE: 65 */
	    ZI62 = ZIb;
	    goto ZL2_65;
	    /* END OF INLINE: 65 */
	}
	/*UNREACHED*/
      default:
	{
	    ZI63 = ZI61;
	    ZI64 = ZI62;
	}
	break;
      case 11:
	return;
    }
    *ZO63 = ZI63;
    *ZO64 = ZI64;
}

static void
ZRheader_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	StringP ZIsc;
	StringP ZIsh;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR49 ();
	ZR53 ();
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: cfile-headerstring */
	{
#line 130 "lctsyntax.act"

	(ZIsc)=&(global_lct_parse_tree.cfileheader) ;
#line 462 "lctsyntax.c"
	}
	/* END OF ACTION: cfile-headerstring */
	ZRgrp_Hof_Hletters (ZIsc);
	ZR54 ();
	ZR52 ();
	ZR53 ();
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: hfile-headerstring */
	{
#line 126 "lctsyntax.act"

	(ZIsh)=&(global_lct_parse_tree.hfileheader) ;
#line 478 "lctsyntax.c"
	}
	/* END OF ACTION: hfile-headerstring */
	ZRgrp_Hof_Hletters (ZIsh);
	ZR54 ();
	ZR55 ();
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (11);
    return;
}

static void
ZRtrailer_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 11) {
	return;
    }
    {
	StringP ZIsc;
	StringP ZIsh;

	switch (CURRENT_TERMINAL) {
	  case 1:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR49 ();
	ZR53 ();
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: cfile-trailerstring */
	{
#line 122 "lctsyntax.act"

	(ZIsc)=&(global_lct_parse_tree.cfiletrailer) ;
#line 523 "lctsyntax.c"
	}
	/* END OF ACTION: cfile-trailerstring */
	ZRgrp_Hof_Hletters (ZIsc);
	ZR54 ();
	ZR52 ();
	ZR53 ();
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: hfile-trailerstring */
	{
#line 118 "lctsyntax.act"

	(ZIsh)=&(global_lct_parse_tree.hfiletrailer) ;
#line 539 "lctsyntax.c"
	}
	/* END OF ACTION: hfile-trailerstring */
	ZRgrp_Hof_Hletters (ZIsh);
	ZR54 ();
	ZR55 ();
	if ((CURRENT_TERMINAL) == 11) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (11);
    return;
}

/* BEGINNING OF TRAILER */

#line 172 "lctsyntax.act"


#line 561 "lctsyntax.c"

/* END OF FILE */
