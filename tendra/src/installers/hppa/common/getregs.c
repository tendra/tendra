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
 *	(1) Its Recipients shall ensure that this Notice is
 *	reproduced upon any copies or amended versions of it;
 *    
 *	(2) Any amended version of it shall be clearly marked to
 *	show both the nature of and the organisation responsible
 *	for the relevant amendment or amendments;
 *    
 *	(3) Its onward transfer from a recipient to another
 *	party shall be deemed to be that party's acceptance of
 *	these conditions;
 *    
 *	(4) DERA gives no warranty or assurance as to its
 *	quality or suitability for any purpose and DERA accepts
 *	no liability whatsoever in relation to any use to which
 *	it may be put.
 *
 * $TenDRA$
 */


/**/

#define HPPATRANS_CODE
/******************************************************************
 *		getregs.c
 *
 *	Routines for choosing temporary registers. The next free
 *register is chosen cyclically from available t regs.
 *
 *	The parameter is usually taken from a value of type space
 *(which has bits for fixed and floating regs).  A clear bit indicates
 *that the corresponding register is free for use.

******************************************************************/

#include "config.h"
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


/* next fixed reg to be allocated */
static int currentfix = R_FIRST;
static long choosefix = RMASK(R_FIRST);

/* next float reg to be allocated */
static int currentfloat = R_FLT_FIRST;
static long choosefloat = RMASK(R_FLT_FIRST);


/* reset getreg() and getfreg() back to start of sequence for proc 'tg' */
/* (help register numbers be backward compatible). */
void
settempregs(exp tg)
{
	/*ARGSUSED*/
	currentfix = GR2;
	choosefix = RMASK(currentfix);
	
	currentfloat = 1;
	choosefloat = RMASK(currentfloat);
	
}

/* get a free temporary fixed pt reg */
int
getreg(long fixed)
{
	
	/*
	 * Choose reg from set 'fixed'. Chosen in a cyclic order, to give good
	 * chance for peep-hole optimiser finding something useful lying around. Bit
	 * set in set 'fixed' means it is unavailable, we search for 0 bit.
	 */
	int reg = -1;
	long start = choosefix;
	
	
	FULLCOMMENT3("getreg: from %#x, choosefix=%#x currentfix=%d", fixed, choosefix, currentfix);
	
	/* currentfix and choosefix are in step, one the reg number, one the mask */
	assert(choosefix == RMASK(currentfix));
	
	for (;;)
	{
		if ((choosefix & fixed) == 0)
			reg = currentfix;
		
		assert(reg != GR0); 	/* hard wired to 0, shouldn't be in set */
		assert(reg != GR1);	       /* ad-hoc temporary                     */
		assert(reg != DP);        /* %dp must not be changed              */
		assert(reg != SP);       /* %sp must not be changed              */
		
		if (currentfix == R_LAST)
		{
			/* back to start */
			currentfix = R_FIRST;
			choosefix = RMASK(R_FIRST);
		}
		else
		{
			/* next reg */
			currentfix++;
			choosefix = choosefix << 1;
		}
		
		if (reg != -1)
		{
			FULLCOMMENT1("getreg: allocating %d", reg);
			assert(IS_TREG(reg));
			return reg;
		}
		if (choosefix == start)
		{
			fail("getreg: too many regs required");
			return GR0;
		}
	}
	/* NOTREACHED */
}


int
getfreg(long fl) /* get a free temporary floating reg */
{
	
	/*
	 * Choose reg from set 'fl'. Chosen in a cyclic order, to give good chance
	 * for peep-hole optimiser finding something useful lying around. Bit set in
	 * set 'float' means it is unavailable, we search for 0 bit.
	 */
	int reg = -1;
	long start = choosefloat;
	
	FULLCOMMENT3("getfreg: from %#x, choosefloat=%#x currentfloat=%d", fl, choosefloat, currentfloat);
	
	/*
	 * currentfloat and choosefloat are in step, one the reg number, one the
	 * mask
	 */
	assert(choosefloat == RMASK(currentfloat));
	
	for (;;)
	{
		if (((choosefloat & fl) == 0) && IS_FLT_TREG(currentfloat))
			reg = currentfloat;
		
		if (currentfloat == R_FLT_LAST)
		{
			/* back to start */
			currentfloat = R_FLT_FIRST;
			choosefloat = RMASK(R_FLT_FIRST);
		}
		else
		{
			/* next reg */
			currentfloat++;
			choosefloat = choosefloat << 1;
		}
		
		if (reg != -1)
		{
			FULLCOMMENT1("getfreg: allocating %d", reg);
			assert(IS_FLT_TREG(reg));
			return reg;
		}
		
		if (choosefloat == start)
		{
			fail("getfreg: too many floating point regs required");
			return 0;
		}
	}
}





















































