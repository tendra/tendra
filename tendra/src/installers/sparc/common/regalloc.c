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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/regalloc.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: regalloc.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1997/08/23  13:54:34  pwe
 * initial ANDF-DE
 *
 * Revision 1.8  1997/03/26  13:04:52  pwe
 * general proc compatibility
 *
 * Revision 1.7  1996/08/22  16:47:15  pwe
 * correct accessing for double params
 *
 * Revision 1.6  1995/11/07  09:53:31  john
 * Change to general procs
 *
 * Revision 1.5  1995/10/24  17:16:15  john
 * Fixed stupid mistake in register allocation
 *
 * Revision 1.4  1995/09/22  13:07:17  john
 * Protected local reg
 *
 * Revision 1.3  1995/08/22  15:29:15  john
 * Change to compound_tag
 *
 * Revision 1.2  1995/05/26  13:01:29  john
 * Change for new spec
 *
 * Revision 1.1.1.1  1995/03/13  10:18:53  john
 * Entered into CVS
 *
 * Revision 1.4  1994/12/01  13:25:47  djch
 * Alter allocator to ensure env_offset'd go on the stack.
 *
 * Revision 1.3  1994/10/26  13:44:54  djch
 * *** empty log message ***
 *
 * Revision 1.2  1994/05/03  15:10:48  djch
 * From the expt version, fixes bug where fixdump sometimes got real reg numbers,
 * sometimes sreg numbers
 *
 * Revision 1.2  1994/05/03  15:10:48  djch
 * From the expt version, fixes bug where fixdump sometimes got real reg numbers,
 * sometimes sreg numbers
 *
 * Revision 1.2  94/02/15  11:20:27  djch
 * fixed wrong bit set in fixdump for inreg_bits exps, added comments
 * 
 * Revision 1.1  94/01/13  12:13:56  djch
 * Initial revision
 * 
 * Revision 1.4  93/08/27  11:36:44  11:36:44  ra (Robert Andrews)
 * A couple of lint-like changes.  Use of pset etc to set properties.
 * 
 * Revision 1.3  93/08/13  14:44:36  14:44:36  ra (Robert Andrews)
 * Reformatted comment.
 * 
 * Revision 1.2  93/07/05  18:24:39  18:24:39  ra (Robert Andrews)
 * Reformatted file.  Added support for PIC by means of the avoid_L7
 * flag which causes register L7 not to be allocated.
 * 
 * Revision 1.1  93/06/24  14:59:11  14:59:11  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


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



