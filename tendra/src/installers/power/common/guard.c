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
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
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
 */





/****************************************************************
 *		 guard.c
 *
 *	These routines protect registers from future use. The type
 *involved is space which consists of two long ints with bit patterns
 *taken to represent usage of temporary fixed and floating
 *point registers. These bits are used in the procedure
 *getregs which understands a clear bit to mean that the corresponding
 *register is free for use.
 *	The procedures are widely used in make_code which may use
 *getreg to choose a register to contain the result of an expression.
 *If this expression is the first operand of a binary operation (say) then the register
 *is guarded, producing another space which will be used by make_code for the
 *second operand.

******************************************************************/

#include "config.h"
#include "codegen.h"

#include "tempdecs.h"	/* for tempdecopt */
#include "comment.h"

#include "guard.h"


/*******************************************************************
 *The integer parameter to procedures guardreg and guardfreg
 *is taken to be a register which needs to be protected. For floating point
 *registers a factor of 2 is involved. The corresponding bit in the appropriate field of the
 *space i.e fixed or float, is therefore set.
 ********************************************************************/

space
guardreg(int r, space sp)
{
	if (IS_TREG(r))
	{
		sp.fixed |= RMASK(r);
	}				/* set bit in the fixed field of sp */
	return sp;
}

space
guardfreg(int r, space sp)
{
	if (IS_FLT_TREG(r))		/* r is a floating point t reg */
	{
		sp.flt |= RMASK(r);
	}				/* set bit in the flt field of sp */
	return sp;
}


/*
 * needreg & needfreg are like guardreg & guardfreg,
 * except it is an error if the reg is alread in use.
 * Used, eg, when claiming regs that will be damaged, as in a call.
 */

space
needreg(int r, space sp)
{
	/* tempdec() can allocate t regs if dead over calls, so dont fail */
	if (!(tempdecopt && IS_TREG(r)) && (sp.fixed&RMASK(r))!=0)
	{
		COMMENT1("needreg: %d", r);
		fail("needreg: fixed reg already in use");
	}
	return guardreg(r, sp);
}

space
needfreg(int r, space sp)
{
	/* tempdec() can allocate t regs if dead over calls, so dont fail */
	if (!(tempdecopt && IS_FLT_TREG(r)) && (sp.flt&RMASK(r))!=0)
	{
		COMMENT1("needfreg: %d", r);
		fail("needfreg: float reg already in use");
	}
	return guardreg(r, sp);
}


/********************************************************************
 *The procedure guard may also protect a register involved in
 *addressing depending on the value of the parameter of type where. This is a
 *union of a fixpnt reg , a float reg and an instore value. In the latter case the
 *register involved in the addressing can be deduced from the base field of the
 *instore value. These types are defined in addresstypes.h.
 *********************************************************************/

space
guard(where w, space sp)
{
	switch (w.answhere.discrim)
	{
    case inreg:
    {
		int r = regalt(w.answhere);
		
		if (IS_TREG(r))
		{
			sp.fixed |= RMASK(r);
		}				/* guard reg */
		return sp;
    }
	case infreg:
    {
		int r = fregalt(w.answhere).fr;
		
		if (IS_FLT_TREG(r))
		{
			sp.flt |= RMASK(r);
		}				/* guard freg */
		return sp;
    }
	case notinreg:
    {
		int r = insalt(w.answhere).b.base;
		
		if (IS_TREG(r))
		{
			sp.fixed |= RMASK(r);
		}
		/* guard fixed point t reg used as base of address */
		return sp;
    }
	case insomereg:
	case insomefreg:
    {
		fail("guard: Guard ? reg");
		return sp;
    }
	default:
    {
		fail("guard: not in switch");
		return sp;
    }
	}
}
