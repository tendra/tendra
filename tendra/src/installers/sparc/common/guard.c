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
 *    These routine involve protecting registers from future use.  The
 *    type space consists of two bitmasks, one representing the fixed
 *    registers and one the floating registers.  A bit is set to indicate
 *    that the corresponding register is in use.  These guard routines
 *    just set the right bit to indicate that the given register is in
 *    use.
 */

#include "config.h"
#include "common_types.h"
#include "regmacs.h"
#include "procrec.h"
#include "addrtypes.h"
#include "tempdecs.h"
#include "comment.h"
#include "guard.h"


/*
 *    GUARD THE FIXED REGISTER r IN sp
 */

space
guardreg(int r, space sp)
{
    if (IS_TREG (r)) sp.fixed |= RMASK (r);
    return (sp);
}


/*
 *    GUARD THE FLOATING REGISTER r IN sp
 */

space
guardfreg(int r, space sp)
{
    if (IS_FLT_TREG (r)) sp.flt |= RMASK (r);
    return (sp);
}


/*
 *  GUARD THE FIXED REGISTER r IN sp
 *  This routine is like guardreg, but fails if r has already 
 *  been used.
 */

space
needreg(int r, space sp)
{
#if 0
    if (!(tempdecopt && IS_TREG (r)) &&
		(sp.fixed & RMASK (r)) != 0) {
		fail ("needreg : fixed register already in use");
    }
#endif
    return (guardreg (r, sp));
}


/*
 *    GUARD THE FLOATING REGISTER r IN sp
 *
 *    This routine is like guardfreg, but fails if r has already been used.
 */

space
needfreg(int r, space sp)
{
#if 0
    if (!(tempdecopt && IS_FLT_TREG (r)) &&
		(sp.flt & RMASK (r)) != 0) {
		fail ("needfreg : float register already in use");
    }
#endif
    return (guardfreg (r, sp));
}


/*
 *    GUARD ANY REGISTERS FROM w IN sp
 */

space
guard(where w, space sp)
{
	switch (discrim (w.answhere)) {
    case inreg : {
		/* guard fixed registers */
		int r = regalt (w.answhere);
		if (IS_TREG (r)) sp.fixed |= RMASK (r);
		return (sp);
    }
    case infreg : {
		/* guard floating registers */
		int r = fregalt (w.answhere).fr;
		if (IS_FLT_TREG (r)) sp.flt |= RMASK (r);
		return (sp);
    }
		/*	case bitad :*/
    case notinreg : {
		/* guard base register */
		int r = insalt (w.answhere).b.base;
		if (IS_TREG (r)) sp.fixed |= RMASK (r);
		return (sp);
    }
    default: {
		/* fall through to fail */
    }	
	}
	fail ("Bad guard register");
	return (sp);
}	



