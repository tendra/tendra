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


/* 	$Id: guard.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: guard.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

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
space guardreg
    PROTO_N ( ( r,sp ) )
    PROTO_T ( int r X space sp )
{
  if ((r >= 0 && r <= 8) || (r>=16 && r<=21)||(r >= 22 && r <= 26)||(r==27)) {
				/* r is a fixed point t reg */
    sp.fixed |= (1 << r);
  }				/* set bit in the fixed field of sp */
  return sp;
}

space guardfreg
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
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
space guard
    PROTO_N ( ( w,sp ) )
    PROTO_T ( where w X space sp )
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
