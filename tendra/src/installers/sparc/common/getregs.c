/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */




/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


#define SPARCTRANS_CODE
/*
 *    Routines for choosing temporary registers.
 */
#include "config.h"
#include "common_types.h"
#include "myassert.h"
#include "regmacs.h"
#include "proctypes.h"
#include "exptypes.h"
#include "procrec.h"
#include "expmacs.h"
#include "exp.h"
#include "addrtypes.h"
#include "regexps.h"
#include "tags.h"
#include "expmacs.h"
#include "bitsmacs.h"
#include "getregs.h"


/*
 *    THE NEXT FIXED REGISTER TO BE ALLOCATED
 */

static int currentfix = R_FIRST;
static long choosefix = RMASK (R_FIRST);


/*
 *    THE NEXT FLOATING REGISTER TO BE ALLOCATED
 */

static int currentfloat = R_FLT_FIRST;
static long choosefloat = RMASK (R_FLT_FIRST);


/*
 *    INITIALIZE REGISTER ALLOCATION VARIABLES
 *
 *    This is called at the start of each procedure.
 */

void
settempregs(exp tg)
{
	currentfix = R_O0;
	choosefix = RMASK (currentfix);
	currentfloat = 1;
	choosefloat = RMASK (currentfloat);
	return;
}


/*
 *  GET THE NEXT FREE TEMPORARY FIXED REGISTER
 *
 *  The argument fixed gives the bitmask of all the unavailable registers.
 *  Avoid R_O7 until last, so it's available for PIC_code case.
 */

int
getreg(long fixed)
{
	int reg = -1;
	long start = choosefix;
	assert (choosefix == RMASK (currentfix));
	for (; ;) {
		/* Check if register is free */
		if ((choosefix & fixed) == 0 && currentfix != R_O7) reg = currentfix;
		
		/* Work out the next register (cyclic) */
		if (currentfix == R_LAST) {
			currentfix = R_FIRST;
			choosefix = RMASK (R_FIRST);
		} 
		else {
			currentfix++;
			choosefix = choosefix << 1;
		}
		if (reg != -1) {
			/* Register found */
			assert (IS_TREG (reg));
			assert (reg != R_G0) ;	/* %g0 is always 0 */
			assert (reg != R_G1) ;	/* %g1 is used for other purposes */
			return (reg);
		}
		if (choosefix == start) {
			/* Back where we started */
			if ((fixed & RMASK (R_O7)) == 0) {
				return (R_O7);
			}
			fail ("Can't allocate temporary register");
			return (R_G1);
		}
	}
	/* NOT REACHED */
}


/*
 *  GET THE NEXT FREE TEMPORARY FLOATING REGISTER
 *  
 *  The argument fl gives the bitmask of all the unavailable registers.
 */

int
getfreg(long fl)
{
	int reg = -1;
	long start = choosefloat;
	assert (choosefloat == RMASK (currentfloat));
	for (; ;) {
		/* Check if register is free */
		if ((choosefloat & fl) == 0) reg = currentfloat;
		
		/* Work out the next register (cyclic) */
		if (currentfloat == R_FLT_LAST) {
			currentfloat = R_FLT_FIRST;
			choosefloat = RMASK (R_FLT_FIRST);
		} 
		else {
			currentfloat++;
			choosefloat = choosefloat << 1;
		}
		if (reg != -1) {
			/* Register found */
			assert (IS_FLT_TREG (reg));
			return (reg);
		}
		if (choosefloat == start) {
			fail ("Can't allocate temporary floating register");
			return (0);
		}
	}
	/* NOT REACHED */
}
