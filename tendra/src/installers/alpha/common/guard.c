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
  guard.c
   
  These routines are provided to guard registers from use.
*/


#include "config.h"
#include "fail.h"
#include "procrecs.h"
#include "addresstypes.h"
#include "guard.h"


/*
  guardregs() and guardfregs() take two arguments : an integer 
  representing the register to be guarded and a space variable 
  representing the current status of the pool of registers.  A 
  register is guarded by setting its corresponding bit in the 
  space variable to 1.
*/
space
guardreg(int r, space sp)
{
  if ((r >= 0 && r <= 8) || (r>=16 && r<=21)||(r >= 22 && r <= 26)||(r==27)) {
				/* r is a fixed point t reg */
    sp.fixed |= (1 << r);
  }				/* set bit in the fixed field of sp */
  return sp;
}

space
guardfreg(int r, space sp)
{
  if((r==0)||(r>=10 && r<=21)||(r>=22 && r<=30))
    sp.flt |= (1<<r);
  return sp;
}


/*
   Guard takes an expression and protects the register involved 
   in the same manner as guardreg and guardfreg.  If the expression 
   is in store the register can be obtained from the base part 
   of the address.
*/
space
guard(where w, space sp)
{
  switch (w.answhere.discrim) {
    case inreg : {
      int   r = regalt (w.answhere);
      if((r>=0 && r<=8) || (r>=16 && r<=21) || (r>=22 && r<=27)) {
	sp.fixed |= (1 << r);
      }			/* guard reg */
      return sp;
    }
    case infreg : {
      int   r = fregalt (w.answhere).fr;
      if ((r<=15) ||(r>=16 && r<=21)||((r>=22) && (r<=30))) {
	sp.flt |= (1 << r);
      }			/* guard freg */
      return sp;
    }
    case notinreg : {
      int   r = insalt (w.answhere).b.base;
      if((r>=0 && r<=8) || (r>=16 && r<=21) || (r>=22 && r<=27)) {
	sp.fixed |= (1 << r);
      }
      /* guard fixed point t reg used as base of address */
      return sp;
    }
    case insomereg : 
    case insomefreg : {
      failer ("Guard ? reg ");
      break;
    }
    default:{
      failer ("error in guard\n");
      break;
    }
  }	
  return sp;
}
