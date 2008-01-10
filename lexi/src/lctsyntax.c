/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 9 "lctsyntax.act"

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

#line 55 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRgrp_Hof_Hletters(void);
static void ZRletters(void);
extern void read_lct_unit(void);
static void ZRheader_Hstmnt(void);
static void ZRtrailer_Hstmnt(void);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRgrp_Hof_Hletters(void)
{
    if ((CURRENT_TERMINAL) == 10) {
	return;
    }
    {
	ZRletters ();
	/* BEGINNING OF INLINE: 15 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 8:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: E_unexpected_eof */
		    {
#line 92 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Unexpected End of File inside @{ @} block") ;
#line 89 "lctsyntax.c"
		    }
		    /* END OF ACTION: E_unexpected_eof */
		}
		break;
	      case 10:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 15 */
    }
    return;
  ZL1:;
    SAVE_LEXER (10);
    return;
}

static void
ZRletters(void)
{
  ZL2_letters:;
    switch (CURRENT_TERMINAL) {
      case 2:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: letters */
	    goto ZL2_letters;
	    /* END OF INLINE: letters */
	}
	/*UNREACHED*/
      case 10:
	return;
      default:
	break;
    }
}

void
read_lct_unit(void)
{
    if ((CURRENT_TERMINAL) == 10) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 19 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ZRheader_Hstmnt ();
		    if ((CURRENT_TERMINAL) == 10) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 19 */
	/* BEGINNING OF INLINE: 20 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    ZRtrailer_Hstmnt ();
		    if ((CURRENT_TERMINAL) == 10) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 20 */
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
#line 88 "lctsyntax.act"

	    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 186 "lctsyntax.c"
	}
	/* END OF ACTION: E-syntax-error */
    }
}

static void
ZRheader_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 10) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 0:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 3:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRgrp_Hof_Hletters ();
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  case 10:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 5:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRletters ();
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  case 10:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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
    SAVE_LEXER (10);
    return;
}

static void
ZRtrailer_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 10) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 1:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 3:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRgrp_Hof_Hletters ();
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  case 10:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 5:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRletters ();
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  case 10:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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
    SAVE_LEXER (10);
    return;
}

/* BEGINNING OF TRAILER */

#line 95 "lctsyntax.act"


#line 353 "lctsyntax.c"

/* END OF FILE */
