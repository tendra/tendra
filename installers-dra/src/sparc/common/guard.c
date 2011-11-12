/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */



/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/guard.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: guard.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/08/23  13:53:45  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1996/03/20  16:14:00  john
 * Reformatting
 *
 * Revision 1.2  1995/05/26  12:58:30  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:37  john
 * Entered into CVS
 *
 * Revision 1.4  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.3  1994/05/19  08:58:10  djch
 * added empty {} to pacify tcc
 *
 * Revision 1.2  1994/05/13  12:29:31  djch
 * Incorporates improvements from expt version
 *
 * Revision 1.1  1994/05/03  14:49:37  djch
 * Initial revision
 *
 * Revision 1.2  93/08/13  14:37:04  14:37:04  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.1  93/06/24  14:58:26  14:58:26  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE

/*
    These routine involve protecting registers from future use.  The
    type space consists of two bitmasks, one representing the fixed
    registers and one the floating registers.  A bit is set to indicate
    that the corresponding register is in use.  These guard routines
    just set the right bit to indicate that the given register is in
    use.
*/

#include "config.h"
#include "regmacs.h"
#include "procrec.h"
#include "addrtypes.h"
#include "tempdecs.h"
#include "comment.h"
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
    if ( !( tempdecopt && IS_TREG ( r ) ) &&
	  ( sp.fixed & RMASK ( r ) ) != 0 ) {
	fail ( "needreg : fixed register already in use" ) ;
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
    if ( !( tempdecopt && IS_FLT_TREG ( r ) ) &&
	  ( sp.flt & RMASK ( r ) ) != 0 ) {
	fail ( "needfreg : float register already in use" ) ;
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
  fail ( "Bad guard register" ) ;
  return sp;
}	



