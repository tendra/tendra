/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/


#define SPARCTRANS_CODE
/*
  The main procedure defined here is reg_alloc which allocates 
  registers and stack space for a procedure expression.  After the 
  application of weights to the body reg_alloc re-codes the number 
  field of each ident within it.  At the end of reg_alloc :

  1) If the props field of an ident contains inreg_bits or 
     infreg_bits and number = 0 then the value will be in a 
     t-register to be chosen in make_code,

  2) If the props contains the register bits then number of 
     the ident is a fixed point s-register number or a floating 
     point s-register number (divided by 2).

  3) Otherwise the value is on the stack and :
     number of ident = ( word displacement in locals ) * 64 + R_FP.
*/

#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "tags.h"
#include "proctypes.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "regmacs.h"
#include "comment.h"
#include "myassert.h"
#include "flags.h"
#include "proc.h"
#include "translat.h"
#include "regalloc.h"

/*
  FLAG : AVOID REGISTER L7 (USED IN PIC)
*/

bool avoid_L7 = 0 ;


/*
  MAP FIXREG NUMBER TO REAL REGISTER NUMBER
  The number n in the range 1...14 is mapped onto the corresponding
  register out of R_L0,...,R_L7,R_I5,...,R_I0.
*/

/* 
   we will see the parameters first, so won't call this until 
   the remaining Ix's are available...
*/
static int SREG_TO_REALREG 
    PROTO_N ( ( n ) )
    PROTO_T ( int n ){
  int m = ( avoid_L7 ? 7 : 8 ) ;
  int par_reg_max;
  if ( n <= m ) return ( R_L0 + ( n - 1 ) ) ;
#ifdef GENCOMPAT
  if (May_have_callees) {
#else
  if(in_general_proc) {
#endif
    if(Has_vcallees) {
      par_reg_max = R_I3;
    }
    else {
      par_reg_max = R_I4;
    }
  }
  else {
    par_reg_max = R_I5;
  }
  return par_reg_max-(n-m-1);
  /*return ( (Has_vcallees)?(R_I4-(n-m-1)):(R_I5 - ( n - m - 1 )) ) ;*/
}


/*
  ROUND b UP TO A MULTIPLE OF a
*/

#define ALIGNNEXT( b, a )      ( ( ( b ) + ( a ) - 1 ) & ~( ( a ) - 1 ) )


/*
  THE ZERO SPACEREQ
*/

spacereq zerospace = { 0, 0, 0 } ;


/*
  FIND THE MAXIMUM OF TWO SPACEREQS
  The register masks are just or'ed, the stack size is the larger of
  the two.
*/

spacereq maxspace 
    PROTO_N ( ( a, b ) )
    PROTO_T ( spacereq a X spacereq b ){
  a.fixdump |= b.fixdump ;
  a.fltdump |= b.fltdump ;
  a.stack = MAX_OF ( a.stack, b.stack ) ;
  return ( a ) ;
}


/*
  CALCULATE SPACE REQUIREMENTS FOR A PROCEDURE
  The expression e gives the procedure body, freefixed and freefloat
  are respectively the numbers to fixed and floating s-registers.
  The initial stack size is given by stack.
*/

spacereq regalloc 
    PROTO_N ( ( e, freefixed, freefloat, stack ) )
    PROTO_T ( exp e X int freefixed X int freefloat X long stack ){
  spacereq def ;
  exp s = son ( e ) ;
  unsigned char n = name ( e ) ;
  if ( n == ident_tag ) {
    int ffix = freefixed ;
    int ffloat = freefloat ;
    long st = stack ;
    spacereq body ;
    ash a ;
    assert ( freefixed >= 0 ) ;
    assert ( freefloat >= 0 ) ;
    if ( props ( e ) & defer_bit ) {
      /* the tag declared is transparent to code production */
      def = zerospace ;
    } 
    else {
      a = ashof ( sh ( s ) ) ;
#if 1
      if(name(s) != compound_tag && name(s) != nof_tag && 
	 name(s) != concatnof_tag) {
	def = regalloc ( s, freefixed, freefloat, stack ) ;
      }
      else {
	if(a.ashalign <= 32 || (stack & 0x20)==0) {
	  st = stack + ((a.ashsize + 31) & ~31);
	}
	else {
	  st = stack + 32 + ((a.ashsize+31)&~31);
	}
	def = regalloc(s,freefixed,freefloat,st);
      }
#else
      def = regalloc(s,freefixed,freefloat,stack);
#endif      
      if ( isparam ( e ) ) {
	/* ( some ) SPARC params in s-regs, reserve them here */
	int n2 = ( int ) props ( son ( e ) ) ;
	int start = no ( son ( e ) ) >> 5 ;
	if ( start <= 5 ) {
	  /* Some input registers (%i0 .. %i5) are used */
	  int nregs ;
	  /* "end" Word offset beyond end of param */
	  long sz = shape_size ( sh ( son ( e ) ) ) ;
	  int end = ( int ) ( start + ( rounder ( sz, 32 ) >> 5 ) ) ;
	  if ( end > 6 ) end = 6 ;
	  nregs = end - start ;
/*		    assert ( ( n2 - R_I0 ) == start ) ;*/
	  assert ( nregs <= 6 ) ;
	  ffix -= nregs ; /* this also prevents SREG_TO_REALREG
			     from using these regs...*/
	}	
	if ( ( props ( e ) & inreg_bits ) != 0 ) {
	  assert ( no ( e ) == n2 ) ;
	  assert ( IS_SREG ( no ( e ) ) ) ;
	  assert ( a.ashsize <= 32 ) ;
	  assert ( R_I0 <= n2 && n2 <= R_I5 ) ;
	  def.fixdump |= RMASK ( n2 ) ;
	}
	else
	  no ( e ) = 0 ;
	assert ( ffix >= 0 ) ;
      } 
      else if ( ( props ( e ) & inreg_bits ) == 0 &&
		fixregable ( e ) && no ( e ) < ffix ) {
	/* suitable for s reg, no(e) has been set up by weights */
	pset ( e, inreg_bits ) ;
	no ( e ) = SREG_TO_REALREG ( ffix ) ; /* will be in s reg */
	ffix -= 1 ;
	def.fixdump |= RMASK ( no(e) ) ;	/* was ffix */
	assert ( ffix >= 0 ) ;
	assert ( IS_SREG ( no ( e ) ) ) ;
	assert ( a.ashsize <= 32 ) ;
      } 
      else if ( ( props ( e ) & infreg_bits ) == 0 &&
		floatregable ( e ) && no ( e ) < ffloat ) {
	fail ( "regalloc : no float point s regs on SPARC" ) ;
      } 
      else if ( ( props ( e ) & inanyreg ) == 0 ) {
	if ( name ( son ( e ) ) == val_tag && !isvar ( e )
	     && !isenvoff(e)) {
	  /* must have been forced by const optimisation -
	     replace uses by the value */
	  exp t = pt ( e ) ;
	  for ( ; t != nilexp ; ) {
	    exp p = pt ( t ) ;
	    setname ( t, val_tag ) ;
	    son ( t ) = nilexp ;
	    no ( t ) = no ( son ( e ) ) ;
	    props ( t ) = 0 ;
	    pt ( t ) = nilexp ;
	    t = p ;
	  }
	  pt ( e ) = nilexp ;
	  pset ( e, defer_bit ) ;
	  def = zerospace ;
	} 
	else if ( name ( son ( e ) ) == name_tag && !isvar ( e ) 
		  & !isenvoff(e)) {
	  /* must have been forced - defer it */
	  pset ( e, defer_bit ) ;
	  def = zerospace ;
	} 
	else {	/* all envoffset MUST go on the stack */
	  /* allocate on stack */
	  /*int basereg = (Has_vcallees)?local_reg:R_FP;*/
	  int basereg = R_FP;
	  
	  assert ( ( stack & 31 ) == 0 ) ;
	  stack = ALIGNNEXT ( stack, a.ashalign ) ;
	  st = ALIGNNEXT ( stack + a.ashsize, 32 ) ;
	  assert ( st - stack >= a.ashsize ) ;
	  assert ( ( stack & 31 ) == 0 ) ;
	  def.stack = MAX_OF ( def.stack, st ) ;
	  no ( e ) = ( int ) ( stack * 2 + basereg) ;
	}
      } 
      else if ( no ( e ) == R_USE_RES_REG ) {
	/* use result register */
	assert (!isenvoff(e));
	no ( e ) = ( ( ( props ( e ) & inreg_bits ) != 0 ) ?
		     R_O0 : R_DEFER_F0 ) ;
      } 
      else {
	/* allocation of stack like regs in make_code */
	assert (!isenvoff(e));	      
      }
    }	
    body = regalloc ( bro ( s ), ffix, ffloat, st ) ;
    return ( maxspace ( body, def ) ) ;
  } 
  else if ( n == case_tag ) {
    /* recurse on all expressions in tree */
    return ( regalloc ( s, freefixed, freefloat, stack ) ) ;
  } 
  else if ( n != name_tag && n != env_offset_tag && n!= general_env_offset_tag 
	    && s != nilexp ) {
    /* recurse on all expressions in tree */
    def = regalloc ( s, freefixed, freefloat, stack ) ;
    while ( !last ( s ) ) {
      spacereq sdef ;
      s = bro ( s ) ;
      sdef = regalloc ( s, freefixed, freefloat, stack ) ;
      def = maxspace ( def, sdef ) ;
    }
    return ( def ) ;
  } 
  else {
    def = zerospace ;
    def.stack = stack ;
    return ( def ) ;
  }
  /* NOT REACHED */
}



