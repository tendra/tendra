/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    These routine involve protecting registers from future use.  The
    type space consists of two bitmasks, one representing the fixed
    registers and one the floating registers.  A bit is set to indicate
    that the corresponding register is in use.  These guard routines
    just set the right bit to indicate that the given register is in
    use.
*/

#include <shared/error.h>

#include <refactor/optimise.h>

#include "regmacs.h"
#include "procrec.h"
#include "addrtypes.h"
#include "guard.h"


/*
    GUARD THE FIXED REGISTER r IN sp
*/

space 
guardreg ( int r, space sp )
{
    if ( IS_TREG ( r ) ) sp.fixed |= RMASK ( r ) ;
    return sp;
}


/*
    GUARD THE FLOATING REGISTER r IN sp
*/

space 
guardfreg ( int r, space sp )
{
    if ( IS_FLT_TREG ( r ) ) sp.flt |= RMASK ( r ) ;
    return sp;
}


/*
  GUARD THE FIXED REGISTER r IN sp
  This routine is like guardreg, but fails if r has already 
  been used.
*/

space 
needreg ( int r, space sp )
{
#if 0
    if ( !( optim & OPTIM_TEMPDEC && IS_TREG ( r ) ) &&
	  ( sp.fixed & RMASK ( r ) ) != 0 ) {
	error(ERR_SERIOUS,  "needreg : fixed register already in use" ) ;
    }
#endif
    return guardreg ( r, sp ) ;
}


/*
    GUARD THE FLOATING REGISTER r IN sp

    This routine is like guardfreg, but fails if r has already been used.
*/

space 
needfreg ( int r, space sp )
{
#if 0
    if ( !( optim & OPTIM_TEMPDEC && IS_FLT_TREG ( r ) ) &&
	  ( sp.flt & RMASK ( r ) ) != 0 ) {
	error(ERR_SERIOUS,  "needfreg : float register already in use" ) ;
    }
#endif
    return guardfreg ( r, sp ) ;
}


/*
    GUARD ANY REGISTERS FROM w IN sp
*/

space 
guard ( where w, space sp ){
  switch ( discrim ( w.answhere ) ) {
    case inreg : {
      /* guard fixed registers */
      int r = regalt ( w.answhere ) ;
      if ( IS_TREG ( r ) ) sp.fixed |= RMASK ( r ) ;
      return sp;
    }
    case infreg : {
      /* guard floating registers */
      int r = fregalt ( w.answhere ).fr ;
      if ( IS_FLT_TREG ( r ) ) sp.flt |= RMASK ( r ) ;
      return sp;
    }
    /*	case bitad :*/
    case notinreg : {
      /* guard base register */
      int r = insalt ( w.answhere ).b.base ;
      if ( IS_TREG ( r ) ) sp.fixed |= RMASK ( r ) ;
      return sp;
    }
    default: {
      /* fall through to fail */
    }	
  }
  error(ERR_SERIOUS,  "Bad guard register" ) ;
  return sp;
}	



