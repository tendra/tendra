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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/getregs.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: getregs.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/08/23  13:53:43  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1996/09/18  12:03:33  pwe
 * fixed PIC_code
 *
 * Revision 1.2  1995/05/26  12:58:14  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:36  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:35  djch
 * Initial revision
 *
 * Revision 1.3  93/08/27  11:25:51  11:25:51  ra (Robert Andrews)
 * Tell lint that settempregs doesn't use its argument.
 * 
 * Revision 1.2  93/07/12  15:13:35  15:13:35  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.1  93/06/24  14:58:20  14:58:20  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
/*
    Routines for choosing temporary registers.
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
    THE NEXT FIXED REGISTER TO BE ALLOCATED
*/

static int currentfix = R_FIRST ;
static long choosefix = RMASK ( R_FIRST ) ;


/*
    THE NEXT FLOATING REGISTER TO BE ALLOCATED
*/

static int currentfloat = R_FLT_FIRST ;
static long choosefloat = RMASK ( R_FLT_FIRST ) ;


/*
    INITIALIZE REGISTER ALLOCATION VARIABLES

    This is called at the start of each procedure.
*/

void settempregs 
    PROTO_N ( ( tg ) )
    PROTO_T ( exp tg ){
  currentfix = R_O0 ;
  choosefix = RMASK ( currentfix ) ;
  currentfloat = 1 ;
  choosefloat = RMASK ( currentfloat ) ;
  return ;
}


/*
  GET THE NEXT FREE TEMPORARY FIXED REGISTER

  The argument fixed gives the bitmask of all the unavailable registers.
  Avoid R_O7 until last, so it's available for PIC_code case.
*/

int getreg 
    PROTO_N ( ( fixed ) )
    PROTO_T ( long fixed ){
  int reg = -1 ;
  long start = choosefix ;
  assert ( choosefix == RMASK ( currentfix ) ) ;
  for ( ; ; ) {
    /* Check if register is free */
    if ( ( choosefix & fixed ) == 0 && currentfix != R_O7) reg = currentfix ;
    
    /* Work out the next register (cyclic) */
    if ( currentfix == R_LAST ) {
      currentfix = R_FIRST ;
      choosefix = RMASK ( R_FIRST ) ;
    } 
    else {
      currentfix++ ;
      choosefix = choosefix << 1 ;
    }
    if ( reg != -1 ) {
      /* Register found */
      assert ( IS_TREG ( reg ) ) ;
      assert ( reg != R_G0 ) ;	/* %g0 is always 0 */
      assert ( reg != R_G1 ) ;	/* %g1 is used for other purposes */
      return ( reg ) ;
    }
    if ( choosefix == start ) {
      /* Back where we started */
      if ( (fixed & RMASK (R_O7)) == 0 ) {
	return (R_O7);
      }
      fail ( "Can't allocate temporary register" ) ;
      return ( R_G1 ) ;
    }
  }
  /* NOT REACHED */
}


/*
  GET THE NEXT FREE TEMPORARY FLOATING REGISTER
  
  The argument fl gives the bitmask of all the unavailable registers.
*/

int getfreg 
    PROTO_N ( ( fl ) )
    PROTO_T ( long fl ){
  int reg = -1 ;
  long start = choosefloat ;
  assert ( choosefloat == RMASK ( currentfloat ) ) ;
  for ( ; ; ) {
    /* Check if register is free */
    if ( ( choosefloat & fl ) == 0 ) reg = currentfloat ;
    
    /* Work out the next register (cyclic) */
    if ( currentfloat == R_FLT_LAST ) {
      currentfloat = R_FLT_FIRST ;
      choosefloat = RMASK ( R_FLT_FIRST ) ;
    } 
    else {
      currentfloat++ ;
      choosefloat = choosefloat << 1 ;
    }
    if ( reg != -1 ) {
      /* Register found */
      assert ( IS_FLT_TREG ( reg ) ) ;
      return ( reg ) ;
    }
    if ( choosefloat == start ) {
      fail ( "Can't allocate temporary floating register" ) ;
      return ( 0 ) ;
    }
  }
  /* NOT REACHED */
}
