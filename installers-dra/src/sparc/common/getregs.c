/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    Routines for choosing temporary registers.
*/

#include <assert.h>

#include <construct/exp.h>
#include <construct/tags.h>

#include "regexps.h"
#include "regmacs.h"
#include "proctypes.h"
#include "exptypes.h"
#include "procrec.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "expmacs.h"
#include "bitsmacs.h"
#include "getregs.h"
#include "comment.h"


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

void 
settempregs ( exp tg ){
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

int 
getreg ( long fixed ){
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
      return reg;
    }
    if ( choosefix == start ) {
      /* Back where we started */
      if ( (fixed & RMASK (R_O7)) == 0 ) {
	return R_O7;
      }
      fail ( "Can't allocate temporary register" ) ;
      return R_G1;
    }
  }
  /* NOT REACHED */
}


/*
  GET THE NEXT FREE TEMPORARY FLOATING REGISTER
  
  The argument fl gives the bitmask of all the unavailable registers.
*/

int 
getfreg ( long fl ){
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
      return reg;
    }
    if ( choosefloat == start ) {
      fail ( "Can't allocate temporary floating register" ) ;
      return 0;
    }
  }
  /* NOT REACHED */
}
