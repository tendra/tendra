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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/weights.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: weights.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/08/23  13:54:46  pwe
 * initial ANDF-DE
 *
 * Revision 1.2  1995/05/26  13:02:31  john
 * Change for new spec
 *
 * Revision 1.1.1.1  1995/03/13  10:19:00  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:50:02  djch
 * Initial revision
 *
 * Revision 1.4  94/02/21  16:14:22  16:14:22  ra (Robert Andrews)
 * Correct a stupid error which crept in somewhere.
 * 
 * Revision 1.3  93/08/27  11:40:50  11:40:50  ra (Robert Andrews)
 * A couple of explicit integer casts.
 * 
 * Revision 1.2  93/08/13  14:49:05  14:49:05  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.1  93/06/24  14:59:39  14:59:39  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
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
#include "config.h"
#include "common_types.h"
#include "exptypes.h"
#include "expmacs.h"
#include "codetypes.h"
#include "installtypes.h"
#include "const.h"
#include "exp.h"
#include "tags.h"
#include "proctypes.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "comment.h"
#include "shapemacs.h"
#include "special.h"
#include "weights.h"


/*
    THE ZERO WEIGHT
*/

weights zeroweights = {
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

weights add_weights 
    PROTO_N ( ( w1, w2 ) )
    PROTO_T ( weights * w1 X weights * w2 ){
  long i ;
  weights r ;
  for ( i = 0 ; i < wfixno ; ++i ) {
    ( r.fix ) [i] = ( w1->fix ) [i] + ( w2->fix ) [i] ;
  }
  for ( i = 0 ; i < wfloatno ; ++i ) {
    ( r.floating ) [i] = ( w1->floating ) [i] + ( w2->floating ) [i] ;
  }
  return ( r ) ;
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

wp max_weights 
    PROTO_N ( ( loc, ws, fix ) )
    PROTO_T ( double loc X weights * ws X bool fix ){
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
  return ( res ) ;
}


/*
  MULTIPLY A WEIGHT BY A SCALAR
*/
weights mult_weights 
    PROTO_N ( ( m, ws ) )
    PROTO_T ( double m X weights * ws ){
  long i ;
  weights res ;
  float *w = ws->fix ;
  float *r = &( res.fix ) [0] ;
  for ( i = 0 ; i < wfixno ; ++i ) {
    r [i] = w [i] * m ;
  }
  w = ws->floating ;
  r = &( res.floating ) [0] ;
  for ( i = 0 ; i < wfloatno ; ++i ) {
    r [i] = w [i] * m ;
  }
  return ( res ) ;
}


/*
  ADD A WEIGHTS CORRESPONDING TO AN EXPRESSION LIST
*/
weights add_wlist 
    PROTO_N ( ( scale, re ) )
    PROTO_T ( double scale X exp re ){
  exp r = re ;
  weights w, w1 ;
  if ( r == nilexp ) {
    return ( zeroweights ) ;
  } 
  else if ( last ( r ) ) {
    return ( weightsv ( scale, r ) ) ;
  } 
  else {
    w = weightsv ( scale, r ) ;
    do {
      r = bro ( r ) ;
      w1 = weightsv ( scale, r ) ;
      w = add_weights ( &w, &w1 ) ;
    } while ( !last ( r ) ) ;
    return ( w ) ;
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

weights weightsv 
    PROTO_N ( ( scale, e ) )
    PROTO_T ( double scale X exp e ){
  int n ;

tailrecurse :
    n = ( int ) name ( e ) ;
  switch ( n ) {
  case name_tag : {
    exp s = son ( e ) ;
    if ( name ( s ) == ident_tag && !isglob ( s ) ) {
      if ( is_floating ( name ( sh ( e ) ) ) &&
	   name ( sh ( e ) ) != shrealhd ) {
	fno ( s ) += scale * 2.0 ;
      } 
      else {
	fno ( s ) += scale ;
      }
    }
	    /* usage of tag stored in number of son of load_name (decl) */
    return ( zeroweights ) ;
  }
  case ident_tag : {
    if ( son ( e ) != nilexp ) {
      weights wdef ;
      weights wbody ;
      int noe = no ( e ) ;	/* set by scan */
      
      /* weights for initialisation of dec */
      if ( name ( son ( e ) ) == clear_tag ||
	   props ( e ) & defer_bit ) {
	wdef = zeroweights ;
	fno ( e ) = 0.0 ;
      } 
      else {
	/* maybe needs a store to initialise */
	if ( is_floating ( name ( sh ( son ( e ) ) ) ) &&
	     name ( sh ( son ( e ) ) ) != shrealhd ) {
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
	
	if ( ( name ( t ) == val_tag ) ||
	     ( name ( t ) == real_tag ) ) {
	  /* string_tag too? */
	  return ( wbody ) ;
	}
	while ( name ( t ) != name_tag ) {
	  t = son ( t ) ;
	}
	
	/* usage of tag stored in number of son of
	   load_name (decl) */
	s = son ( t ) ;
	if ( name ( s ) == ident_tag && !isglob ( t ) ) {
	  fno ( s ) += fno ( e ) ;
	}
	return ( wbody ) ;
      }
      if ( ( props ( e ) & inreg_bits ) == 0 && fixregable ( e ) ) {
	/* NO decrease decrease in scale as reg windows
	   make s-regs "cost-free" */
	wp p ;
	p = max_weights ( fno ( e ), &wbody, 1 ) ;
	no ( e ) = ( int ) p.fix_break ;
	return ( add_weights ( &wdef, &p.wp_weights ) ) ;
      } else if ( ( props ( e ) & infreg_bits ) == 0 &&
		  floatregable ( e ) ) {
	/* usage decreased by 3 because of dump and restore of
	   double s-reg */
	wp p ;
	p = max_weights ( fno ( e ) - 3.0 * scale, &wbody, 0 ) ;
	no ( e ) = (int)p.float_break;
	return ( add_weights ( &wdef, &p.wp_weights ) ) ;
      } 
      else{
	no ( e ) = noe ;/* restore to value given by scan */
	return ( add_weights ( &wdef, &wbody ) ) ;
      }
    } 
    else {
      return ( zeroweights ) ;
    }
  }
  case rep_tag : {
    e = bro ( son ( e ) ) ;
    goto tailrecurse ;
  }
  case case_tag : {
    e = son ( e ) ;
    goto tailrecurse ;
  }
  case labst_tag : {
    scale = fno ( e ) * scale ;
    e = bro ( son ( e ) ) ;
    goto tailrecurse ;
  }
  case val_tag : {
    return ( zeroweights ) ;
  }
  case ncopies_tag : {
    scale = no ( e ) * scale ;
    e = son ( e ) ;
    goto tailrecurse ;
  }
  default : {
    if ( son ( e ) == nilexp || n == env_offset_tag ) {
      return ( zeroweights ) ;
    }
    if ( last ( son ( e ) ) ) {
      e = son ( e ) ;
      goto tailrecurse ;
    }
    return ( add_wlist ( scale, son ( e ) ) ) ;
  }
  }
}
