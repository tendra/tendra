/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
  Allocation of register weights

  The main procedure here is weightsv which determines the allocation
  of s-registers.  It considers which of those tags not already 
  allocated to a t-register by scan are best put in an s-register.  
  The same conditions as for t-registers apply as to the suitability
  of the tags for registers.  Weights estimates the usage of each 
  tag and hence the amount that would be saved if it were held in an
  s-register.  Thus it computes break points for register allocation
  for later use by reg_alloc.
  The type weights consists of two arrays of integers.  In the first
  array each integer corresponds to a fixed point register and the 
  second array's integers correspond to floating point registerss.  
  At the end of a call of weights on an ident exp the props field of
  the ident may still contain inreg_bits or infreg_bits, set by scan,
  to indicate that a t-register should be used.  Otherwise number of 
  ident is set up to represent the break point for allocation.  A 
  similar process occurs for procedure parameters which have the 
  break value in the forweights field of the parapair of the 
  corresponding procrec. This value has three meanings :

  1) The ident (or parameter) defines a fixed point value and 
     number of ident (forweights of parpair) is an integer brk with 
     the interpretation that if there are at least brk fixed point 
     s-registers unallocated at this point then one will be used for
     this tag (parameter).

  2) As 1 but for floating point values.

  3) number of ident = 100 in which case allocate value on the 
     stack,(this is obviously always available for parameters).
*/

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/exp.h>

#include <refactor/const.h>

#include "proctypes.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "regable.h"
#include "weights.h"

static weights 
weightsv ( double scale, exp e );

/*
    THE ZERO WEIGHT
*/

static weights zeroweights = {
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
  },
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
  }
};


/*
  ADD TWO WEIGHTS
*/

static weights
add_weights ( weights * w1, weights * w2 ){
  long i ;
  weights r ;
  for ( i = 0 ; i < wfixno ; ++i ) {
    ( r.fix ) [i] = ( w1->fix ) [i] + ( w2->fix ) [i] ;
  }
  for ( i = 0 ; i < wfloatno ; ++i ) {
    ( r.floating ) [i] = ( w1->floating ) [i] + ( w2->floating ) [i] ;
  }
  return r;
}


/*
  CALCULATE A BREAKPOINT

  loc is the usage count of a tag, ws is the weights computed for the
  scope of the tag and fix distinguishes between fix and float.  This
  routine computes the weights for the declaration and a break point
  for register allocation which gives the number of available regs 
  for which it is worthwhile to allocate this tag into a reg 
  ("regged").
  This procedure is the source of all non-zero weights.  loc may be
  negative since using a s-reg will involve a dump and restore.
*/

static wp 
max_weights ( double loc, weights * ws, bool fix ){
  long i ;
  wp res ;
  long bk = wfixno + 1 ;
  float *w = ( ws->fix ) ;
  float *pw = &( ( ( res.wp_weights ).fix ) [0] ) ;
  
    /* w [i] = greatest usage of ( i + 1 ) inner fixed tags */

  if ( fix ) {
    for ( i = 0 ; i < wfixno ; ++i ) {
      if ( i == 0 ) {
	if ( loc > w [i] ) {
	  /* this tag has higher usage than any inner one ... */
	  pw [i] = loc ;
	  /* ... so it's regged in pref to others */
	  bk = i ;
	} 
	else {
	  pw [i] = w [i] ;
	}
      } else {
	if ( ( loc + w [ i - 1 ] ) > w [i] ) {
	  /* this tag and i inner ones have higher usage than
	     any other ( i + 1 ) inner ones ...  */
	  pw [i] = loc + w [ i - 1 ] ;
	  /* ... so it and i inner ones are regged in preference
	     to any other ( i + 1 ) inner ones */
	  if ( i < bk ) bk = i ;
	} 
	else {
	  pw [i] = w [i] ;
	}
      }
    }
    res.fix_break = bk ;
  } 
  else {
    for ( i = 0 ; i < wfixno ; ++i ) {
      pw [i] = w [i] ;
    }
  }
#if NO_SREG
  res.fix_break = wfixno + 1 ;
#else
  res.fix_break = bk ;
#endif
  bk = wfloatno + 1 ;
  w = ( ws->floating ) ;
  pw = &( ( ( res.wp_weights ).floating ) [0] ) ;
  if ( !fix ) {
    /* same algorithm for float regs as fixed regs */
    for ( i = 0 ; i < wfloatno ; ++i ) {
      if ( i == 0 ) {
	if ( loc > w [i] ) {
	  pw [i] = loc ;
	  bk = i ;
	} 
	else {
	  pw [i] = w [i] ;
	}
      } 
      else {
	if ( ( loc + w [ i - 1 ] ) > w [i] ) {
	  pw [i] = loc + w [ i - 1 ] ;
	  if ( i < bk ) bk = i ;
	} 
	else {
	  pw [i] = w [i] ;
	}
      }
    }
  } 
  else {
    for ( i = 0 ; i < wfloatno ; ++i ) {
      pw [i] = w [i] ;
    }
  }
  res.float_break = bk ;
  return res;
}


/*
  ADD A WEIGHTS CORRESPONDING TO AN EXPRESSION LIST
*/
static weights 
add_wlist ( double scale, exp re ){
  exp r = re ;
  weights w, w1 ;
  if ( r == NULL ) {
    return zeroweights;
  } 
  else if ( r -> last ) {
    return weightsv ( scale, r ) ;
  } 
  else {
    w = weightsv ( scale, r ) ;
    do {
      r = bro ( r ) ;
      w1 = weightsv ( scale, r ) ;
      w = add_weights ( &w, &w1 ) ;
    } while ( ! r -> last ) ;
    return w;
  }
}


/*
  CALCULATE THE REGISTER WEIGHTS FOR AN EXPRESSION

  This procedure estimates the usage of tags and parameters to help
  determine whether they can advantageously be placed in s-registers.
  The parameter scale allows more importance to be placed on usage
  inside 'for' loops for example. The procedure reg_alloc in 	
  reg_alloc.c finally determines the actual choice of s-reg and 
  recodes the number field of an ident.
*/

static weights 
weightsv ( double scale, exp e ){
  int n ;

tailrecurse :
    n = ( int ) e->tag ;
  switch ( n ) {
  case name_tag : {
    exp s = son ( e ) ;
    if ( s->tag == ident_tag && !isglob ( s ) ) {
      if ( is_floating ( sh ( e ) -> tag ) && sh ( e ) -> tag != shrealhd ) {
	fno ( s ) += scale * 2.0 ;
      } 
      else {
	fno ( s ) += scale ;
      }
    }
	    /* usage of tag stored in number of son of load_name (decl) */
    return zeroweights;
  }
  case ident_tag : {
    if ( son ( e ) != NULL ) {
      weights wdef ;
      weights wbody ;
      int noe = no ( e ) ;	/* set by scan */
      
      /* weights for initialisation of dec */
      if ( son ( e ) -> tag == clear_tag ||
	   props ( e ) & defer_bit ) {
	wdef = zeroweights ;
	fno ( e ) = 0.0 ;
      } 
      else {
	/* maybe needs a store to initialise */
	if ( is_floating ( sh ( son ( e ) ) -> tag ) && sh ( son ( e ) ) -> tag != shrealhd ) {
	  fno ( e ) = scale * 2.0 ;
	} else {
	  fno ( e ) = scale ;
	}
	wdef = weightsv ( scale, son ( e ) ) ;
      }
      
      /* weights of body of scan */
      wbody = weightsv ( scale, bro ( son ( e ) ) ) ;
      
      if ( props ( e ) & defer_bit ) {
	/* declaration will be treated transparently in code
	   production */
	exp s ;
	exp t = son ( e ) ;
	
	if ( ( t->tag == val_tag ) ||
	     ( t->tag == real_tag ) ) {
	  /* string_tag too? */
	  return wbody;
	}
	while ( t->tag != name_tag ) {
	  t = son ( t ) ;
	}
	
	/* usage of tag stored in number of son of
	   load_name (decl) */
	s = son ( t ) ;
	if ( s->tag == ident_tag && !isglob ( t ) ) {
	  fno ( s ) += fno ( e ) ;
	}
	return wbody;
      }
      if ( ( props ( e ) & inreg_bits ) == 0 && fixregable ( e ) ) {
	/* NO decrease decrease in scale as reg windows
	   make s-regs "cost-free" */
	wp p ;
	p = max_weights ( fno ( e ), &wbody, 1 ) ;
	no ( e ) = ( int ) p.fix_break ;
	return add_weights ( &wdef, &p.wp_weights ) ;
      } else if ( ( props ( e ) & infreg_bits ) == 0 &&
		  floatregable ( e ) ) {
	/* usage decreased by 3 because of dump and restore of
	   double s-reg */
	wp p ;
	p = max_weights ( fno ( e ) - 3.0 * scale, &wbody, 0 ) ;
	no ( e ) = (int)p.float_break;
	return add_weights ( &wdef, &p.wp_weights ) ;
      } 
      else{
	no ( e ) = noe ;/* restore to value given by scan */
	return add_weights ( &wdef, &wbody ) ;
      }
    } 
    else {
      return zeroweights;
    }
  }
  case rep_tag :
    e = bro ( son ( e ) ) ;
    goto tailrecurse ;
  case case_tag :
    e = son ( e ) ;
    goto tailrecurse ;
  case labst_tag :
    scale = fno ( e ) * scale ;
    e = bro ( son ( e ) ) ;
    goto tailrecurse ;
  case val_tag :
    return zeroweights;
  case ncopies_tag :
    scale = no ( e ) * scale ;
    e = son ( e ) ;
    goto tailrecurse ;
  default : {
    if ( son ( e ) == NULL || n == env_offset_tag ) {
      return zeroweights;
    }
    if ( son ( e ) -> last ) {
      e = son ( e ) ;
      goto tailrecurse ;
    }
    return add_wlist ( scale, son ( e ) ) ;
  }
  }
}
