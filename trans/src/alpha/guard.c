/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  guard.c
   
  These routines are provided to guard registers from use.
*/

#include <shared/error.h>

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
      error(ERROR_INTERNAL, "Guard ? reg ");
      break;
    }
    default:{
      error(ERROR_INTERNAL, "error in guard");
      break;
    }
  }	
  return sp;
}
