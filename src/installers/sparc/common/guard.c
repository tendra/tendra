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
#include "common_types.h"
#include "regmacs.h"
#include "procrec.h"
#include "addrtypes.h"
#include "tempdecs.h"
#include "comment.h"
#include "guard.h"


/*
    GUARD THE FIXED REGISTER r IN sp
*/

space guardreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
    if ( IS_TREG ( r ) ) sp.fixed |= RMASK ( r ) ;
    return ( sp ) ;
}


/*
    GUARD THE FLOATING REGISTER r IN sp
*/

space guardfreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
    if ( IS_FLT_TREG ( r ) ) sp.flt |= RMASK ( r ) ;
    return ( sp ) ;
}


/*
  GUARD THE FIXED REGISTER r IN sp
  This routine is like guardreg, but fails if r has already 
  been used.
*/

space needreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
#if 0
    if ( !( tempdecopt && IS_TREG ( r ) ) &&
	  ( sp.fixed & RMASK ( r ) ) != 0 ) {
	fail ( "needreg : fixed register already in use" ) ;
    }
#endif
    return ( guardreg ( r, sp ) ) ;
}


/*
    GUARD THE FLOATING REGISTER r IN sp

    This routine is like guardfreg, but fails if r has already been used.
*/

space needfreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
#if 0
    if ( !( tempdecopt && IS_FLT_TREG ( r ) ) &&
	  ( sp.flt & RMASK ( r ) ) != 0 ) {
	fail ( "needfreg : float register already in use" ) ;
    }
#endif
    return ( guardfreg ( r, sp ) ) ;
}


/*
    GUARD ANY REGISTERS FROM w IN sp
*/

space guard 
    PROTO_N ( ( w, sp ) )
    PROTO_T ( where w X space sp ){
  switch ( discrim ( w.answhere ) ) {
    case inreg : {
      /* guard fixed registers */
      int r = regalt ( w.answhere ) ;
      if ( IS_TREG ( r ) ) sp.fixed |= RMASK ( r ) ;
      return ( sp ) ;
    }
    case infreg : {
      /* guard floating registers */
      int r = fregalt ( w.answhere ).fr ;
      if ( IS_FLT_TREG ( r ) ) sp.flt |= RMASK ( r ) ;
      return ( sp ) ;
    }
    /*	case bitad :*/
    case notinreg : {
      /* guard base register */
      int r = insalt ( w.answhere ).b.base ;
      if ( IS_TREG ( r ) ) sp.fixed |= RMASK ( r ) ;
      return ( sp ) ;
    }
    default: {
      /* fall through to fail */
    }	
  }
  fail ( "Bad guard register" ) ;
  return ( sp ) ;
}	



