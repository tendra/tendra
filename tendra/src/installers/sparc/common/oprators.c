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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/oprators.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: oprators.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1997/10/10  18:32:50  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.8  1997/08/23  13:54:24  pwe
 * initial ANDF-DE
 *
 * Revision 1.7  1997/02/18  11:48:13  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.6  1996/08/27  14:54:38  pwe
 * Q_functions destroy flpt regs
 *
 * Revision 1.5  1996/03/20  16:12:37  john
 * Reformatting
 *
 * Revision 1.4  1995/07/27  16:32:04  john
 * Fix for quad op
 *
 * Revision 1.3  1995/07/14  16:33:04  john
 * Changes for new error handling
 *
 * Revision 1.2  1995/05/26  13:00:16  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:50  john
 * Entered into CVS
 *
 * Revision 1.5  1994/12/21  11:47:13  djch
 * added labeldecs.h to declare set_label
 *
 * Revision 1.4  1994/12/01  13:18:59  djch
 * Altered abs code to generate a label, and pass to br_abs. .+8 is allowed by
 * the SPARC asm manual, not by /bin/as...
 *
 * Revision 1.3  1994/11/28  16:55:06  djch
 * added code for absop to generate efficient abs code
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:47  djch
 * Initial revision
 *
 * Revision 1.5  93/09/27  14:52:20  14:52:20  ra (Robert Andrews)
 * Added quad_op, the main routine for dealing with long double
 * operations.  Modified fop to allow for long doubles.
 * 
 * Revision 1.4  93/08/27  11:34:44  11:34:44  ra (Robert Andrews)
 * A couple of lint-like changes.
 * 
 * Revision 1.3  93/07/08  18:22:32  18:22:32  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.2  93/06/29  14:30:03  14:30:03  ra (Robert Andrews)
 * Now use ins_p to represent instructions.
 * 
 * Revision 1.1  93/06/24  14:58:57  14:58:57  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "codehere.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "inst_fmt.h"
#include "move.h"
#include "maxminmacs.h"
#include "getregs.h"
#include "guard.h"
#include "tags.h"
#include "shapemacs.h"
#include "bitsmacs.h"
#include "myassert.h"
#include "externs.h"
#include "install_fns.h"
#include "regmacs.h"
#include "regexps.h"
#include "exp.h"
#include "out.h"
#include "locate.h"
#include "eval.h"
#include "muldvrem.h"
#include "proc.h"
#include "labels.h"
#include "oprators.h"

/*
    CORRECT POSSIBLE OVERFLOWS IN REGISTER r
*/

void tidyshort 
    PROTO_N ( ( r, s ) )
    PROTO_T ( int r X shape s ){
  if ( name ( s ) == ucharhd ) {
    rir_ins ( i_and, r, 0xff, r ) ;
  } else if ( name ( s ) == uwordhd ) {
    rir_ins ( i_and, r, 0xffff, r ) ;
  }
  return ;
}


/*
  REMOVE AN EXPRESSION CONTAINING A REGISTER
  Given a list of expressions, seq, find one whose value is in 
  register reg.  If this is found, it is removed from seq and 1 
  is returned.  Otherwise 0 is returned.
*/
bool regremoved 
    PROTO_N ( ( seq, reg ) )
    PROTO_T ( exp * seq X int reg ){
  exp s = *seq ;
  exp t = bro ( s ) ;
  if ( ABS_OF ( regofval ( s ) ) == reg ) {
    ( *seq ) = t ;
    return ( 1 ) ;
  }
  for ( ; ; ) {
    if ( ABS_OF ( regofval ( t ) ) == reg ) {
      bro ( s ) = bro ( t ) ;
      if ( last ( t ) ) setlast ( s ) ;
      return ( 1 ) ;
    }
    if ( last ( t ) ) return ( 0 ) ;
    s = t ;
    t = bro ( t ) ;
  }
  /* NOT REACHED */
}


/*
  EVALUATE A COMMUTATIVE OPERATION
  Evaluates reg = seq_1 @ seq_2 @ ... where @ is a binary commutative
  operation given by rins.  sp may be used for free t-registers.
*/
void do_comm 
    PROTO_N ( ( seq, sp, final, rins ) )
    PROTO_T ( exp seq X space sp X int final X ins_p rins ){
  int r = 0 ;
  space nsp ;
  int a1, a2 ;
  /* should have been optimised in scan... */
  assert ( !( rins == i_add && name ( seq ) == neg_tag &&
	      name ( bro ( seq ) ) != val_tag ) ) ;
  /* evaluate first operand into a1 */
  a1 = reg_operand ( seq, sp ) ;
  for ( ; ; ) {
    nsp = guardreg ( a1, sp ) ;
    seq = bro ( seq ) ;
    if ( name ( seq ) == val_tag ) {
      /* next operand is a constant */
      if ( last ( seq ) ) {
	rir_ins ( rins, a1, ( long ) no ( seq ), final ) ;
	return ;
      } 
      else {
	if ( r == 0 ) r = getreg ( sp.fixed ) ;
	rir_ins ( rins, a1, ( long ) no ( seq ), r ) ;
      }
    } 
    else {
      /* evaluate next operand */
      exp sq = seq ;
      ins_p ins = rins ;
      a2 = reg_operand ( sq, nsp ) ;
      if ( last ( seq ) ) {
	rrr_ins ( ins, a1, a2, final ) ;
	return ;
      } 
      else {
	if ( r == 0 ) r = getreg ( sp.fixed ) ;
	rrr_ins ( ins, a1, a2, r ) ;
      }
    }
    a1 = r ;
  }
  /* NOT REACHED */
}


/*
  EVALUATE A COMMUTATIVE OPERATION
  The commutative operation, rrins, given by e is evaluated into d,
  using sp to get free t-registers.
*/

int comm_op 
    PROTO_N ( ( e, sp, d, rrins ) )
    PROTO_T ( exp e X space sp X where d X ins_p rrins ){
  ins_p rins = rrins ;
  switch ( discrim ( d.answhere ) ) {
    case inreg : {
      int dest = regalt ( d.answhere ) ;
      bool usesdest = regremoved ( &son ( e ), dest ) ;
      exp seq = son ( e ) ;
      if(dest == R_G0) {
	dest = getreg(sp.fixed);
      }

      /* the destination is in a register, take care that we don't
	 alter it before possible use as an operand ... */
      if ( usesdest && last ( seq ) ) {
	/* used, but there is only one other operand */
	if ( name ( seq ) == val_tag ) {
	  rir_ins ( rins, dest, ( long ) no ( seq ), dest ) ;
	} 
        else {
	  rrr_ins ( rins, dest, reg_operand ( seq, sp ), dest ) ;
	}
	if(optop(e)) tidyshort ( dest, sh ( e ) ) ;
	return ( dest ) ;
      } 
      else if ( usesdest ) {
	/* dest used, use temp */
	int r = getreg ( sp.fixed ) ;
	do_comm ( seq, sp, r, rins ) ;
	rrr_ins ( rins, dest, r, dest ) ;
	if (optop(e)) tidyshort ( dest, sh ( e ) ) ;
	return ( dest ) ;
      } 
      else {
	/* dest not used, evaluate into dest */
	do_comm ( seq, sp, dest, rins ) ;
	if (optop(e)) tidyshort ( dest, sh ( e ) ) ;
	return ( dest ) ;
      }
    }
    default : {
      ans a ;
      space nsp ;
      int r = getreg ( sp.fixed ) ;
      setregalt ( a, r ) ;
      /* evaluate the expression into r ... */
      do_comm ( son ( e ), sp, r, rins ) ;
      if(optop(e)) tidyshort ( r, sh ( e ) ) ;
      nsp = guardreg ( r, sp ) ;
      /* ... and move into a */
      ( void ) move ( a, d, nsp.fixed, 1 ) ;
      return ( r ) ;
    }
  }
  /* NOT REACHED */
}


/*
  EVALUATE A NON-COMMUTATIVE OPERATION
  The non-commutative operation, rins, given by e is evaluated 
  into dest, using sp to get free t-registers.
*/
int non_comm_op 
    PROTO_N ( ( e, sp, dest, rins ) )
    PROTO_T ( exp e X space sp X where dest X ins_p rins ){
  exp l = son ( e ) ;
  exp r = bro ( l ) ;
  int a1 = reg_operand ( l, sp ), a2 ;
  space nsp ;
  nsp = guardreg ( a1, sp ) ;
  a2 = reg_operand ( r, nsp ) ;
  switch ( discrim ( dest.answhere ) ) {
    case inreg : {
      int d = regalt ( dest.answhere ) ;
      if(d == R_G0) {
	d = getreg(sp.fixed);
      }
      rrr_ins ( rins, a1, a2, d ) ;
      if(optop(e)) tidyshort ( d, sh ( e ) ) ;
      return ( d ) ;
    }
    default : {
      ans a ;
      int r1 = getreg ( nsp.fixed ) ;
      setregalt ( a, r1 ) ;
      rrr_ins ( rins, a1, a2, r1 ) ;
      if(optop(e)) tidyshort ( r1, sh ( e ) ) ;
      nsp = guardreg ( r1, sp ) ;
      ( void ) move ( a, dest, nsp.fixed, 1 ) ;
      return ( r1 ) ;
    }
  }
  /* NOT REACHED */
}


/*
  EVALUATE A MONADIC OPERATION
  The monadic operation, ins, given by e is evaluated into dest, 
  using sp to get free t-registers.
*/
int monop 
    PROTO_N ( ( e, sp, dest, ins ) )
    PROTO_T ( exp e X space sp X where dest X ins_p ins ){
  int r1 = getreg ( sp.fixed ) ;
  int a1 = reg_operand ( son ( e ), sp ) ;
  switch ( discrim ( dest.answhere ) ) {
    case inreg : {
      int d = regalt ( dest.answhere ) ;
      if (d == R_G0) d = getreg(sp.fixed);
      rr_ins ( ins, a1, d ) ;
      if(optop(e)) tidyshort ( d, sh ( e ) ) ;
      return ( d ) ;
    }
    default : {
      ans a ;
      space nsp ;
      setregalt ( a, r1 ) ;
      rr_ins ( ins, a1, r1 ) ;
      if(optop(e)) tidyshort ( r1, sh ( e ) ) ;
      nsp = guardreg ( r1, sp ) ;
      ( void ) move ( a, dest, nsp.fixed, 1 ) ;
      return ( r1 ) ;
    }
  }
  /* NOT REACHED */
}

/*
    EVALUATE abs OPERATION as
    move a1 -> d
    subcc %g0, a1 -> R_TMP
    bpos,a L
    move R_TMP -> d
L:

*/
int absop 
    PROTO_N ( ( e, sp, dest ) )
    PROTO_T ( exp e X space sp X where dest ){
  int r1 = getreg ( sp.fixed ) ;
  int a1 = reg_operand ( son ( e ), sp ) ;
  int lab = new_label();
  
  switch ( discrim ( dest.answhere ) ) {
    case inreg : {
      int d = regalt ( dest.answhere ) ;
      if (d == R_G0) {
	d = getreg(sp.fixed);
      }
      rr_ins ( i_mov, a1, d ) ;
      rrr_ins ( i_subcc, R_G0, a1, R_TMP);
      br_abs(lab);
      rr_ins( i_mov, R_TMP, d);
      set_label(lab);
      if(optop(e)) tidyshort ( d, sh ( e ) ) ;
      return ( d ) ;
    }
    default : {
      ans a ;
      space nsp ;
      setregalt ( a, r1 ) ;
      rr_ins ( i_mov, a1, r1 ) ;
      rrr_ins ( i_subcc, R_G0, a1, R_TMP);
      br_abs(lab);
      rr_ins( i_mov, R_TMP, r1);
      set_label(lab);
      if(optop(e)) tidyshort ( r1, sh ( e ) ) ;
      nsp = guardreg ( r1, sp ) ;
      ( void ) move ( a, dest, nsp.fixed, 1 ) ;
      return ( r1 ) ;
    }
  }
  /* NOT REACHED */
}


/*
  GET THE ADDRESS OF A LONG DOUBLE
*/
static void quad_addr 
    PROTO_N ( ( e, r, sp ) )
    PROTO_T ( exp e X int r X space sp ){
  instore is ;
  if ( name ( e ) == real_tag ) {
    is = evaluated ( e, 0, 1 ) ;
  } 
  else {
    where w ;
    w = locate1 ( e, sp, sh ( e ), 0 ) ;
    if ( discrim ( w.answhere ) != notinreg ) {
      fail ( "Illegal expression in quad_addr" ) ;
    }
    is = insalt ( w.answhere ) ;
  }
  if ( is.adval ) {
    fail ( "Illegal expression in quad_addr" ) ;
  }
  if ( IS_FIXREG ( is.b.base ) ) {
    if ( is.b.offset == 0 ) {
      if ( is.b.base != r ) rr_ins ( i_mov, is.b.base, r ) ;
    } 
    else {
      rir_ins ( i_add, is.b.base, is.b.offset, r ) ;
    }
  } 
  else {
    set_ins ( is.b, r ) ;
  }
  return ;
}


/*
  DO A LONG DOUBLE OPERATION
*/
void quad_op 
    PROTO_N ( ( a1, a2, sp, dest, op ) )
    PROTO_T ( exp a1 X exp a2 X space sp X where dest X int op ){
  char *s ;
  bool quad_ret = 1 ;
  if ( op < 0 ) {
    /* Test operations */
    quad_ret = 0 ;
    switch ( -op ) {
      case 1 : s = "_Q_fle,2" ; break ;
      case 2 : s = "_Q_flt,2" ; break ;
      case 3 : s = "_Q_fge,2" ; break ;
      case 4 : s = "_Q_fgt,2" ; break ;
      case 5 : s = "_Q_fne,2" ; break ;
      case 6 : s = "_Q_feq,2" ; break ;
      default : fail ( "Illegal floating-point test" ) ;
    }
  } 
  else {
    /* Binary operations */
    switch ( op ) {
      case fplus_tag : s = "_Q_add,2" ; break ;
      case fminus_tag : s = "_Q_sub,2" ; break ;
      case fmult_tag : s = "_Q_mul,2" ; break ;
      case fdiv_tag : s = "_Q_div,2" ; break ;
      case fneg_tag : s = "_Q_neg,1" ; break ;
      case chfl_tag : s = "_Q_stoq,1" ; break ;
      case float_tag : s = "_Q_itoq,1" ; break ;
      case 100 : s = "_Q_qtod,1" ; quad_ret = 0 ; break ;
      case 101 : s = "_Q_qtos,1" ; quad_ret = 0 ; break ;
      case fabs_tag : 
      /* special case: there is no special operation for 
	 this, so it has to be performed by a code sequence*/
      fail("No operation for fabs( long double )");
      s = "_Q_abs,1" ; 
      break ;
      default : fail ( "Illegal floating-point operation" ) ;
    }
  }
  if ( quad_ret ) {
    instore is ;
    baseoff ret_addr ;
    ret_addr.base = R_SP ;
    ret_addr.offset = ( 16 * 4 ) ;
    is = insalt ( dest.answhere ) ;
    if ( discrim ( dest.answhere ) != notinreg ) {
      is.b = mem_temp(0);
      is.adval = 1;
      /*fail ( "Illegal expression in quad_op" ) ;*/
    }
    if ( is.adval ) {
      if ( IS_FIXREG ( is.b.base ) ) {
	if ( is.b.offset == 0 ) {
	  st_ro_ins ( i_st, is.b.base, ret_addr ) ;
	} 
	else {
	  rir_ins ( i_add, is.b.base, is.b.offset, R_TMP ) ;
	  st_ro_ins ( i_st, R_TMP, ret_addr ) ;
	}
      } 
      else {
	set_ins ( is.b, R_TMP ) ;
	st_ro_ins ( i_st, R_TMP, ret_addr ) ;
      }
    } 
    else {
      ld_ins ( i_ld, is.b, R_TMP ) ;
      st_ro_ins ( i_st, R_TMP, ret_addr ) ;
    }
  }
  /* hack for float integer */
  if ( op == float_tag ) {
    int r = reg_operand ( a1, sp ) ;
    if ( name ( sh ( a1 ) ) == ulonghd ) s = "_Q_utoq,1" ;
    if ( r != R_O0 ) rr_ins ( i_mov, r, R_O0 ) ;
    a1 = nilexp ;
  }
  /* hack for change floating variety */
  if ( op == chfl_tag ) {
    ans aa ;
    where w ;
    freg frg ;
    frg.fr = getfreg ( sp.flt ) ;
    if ( name ( sh ( a1 ) ) == realhd ) {
      s = "_Q_dtoq,1" ;
      frg.dble = 1 ;
    } 
    else {
      frg.dble = 0 ;
    }
    setfregalt ( aa, frg ) ;
    w.answhere = aa ;
    w.ashwhere = ashof ( sh ( a1 ) ) ;
    ( void ) code_here ( a1, sp, w ) ;
    if ( frg.dble ) {
      stf_ins ( i_std, frg.fr << 1, mem_temp ( 0 ) ) ;
      ld_ro_ins ( i_ld, mem_temp ( 0 ), R_O0 ) ;
      ld_ro_ins ( i_ld, mem_temp ( 4 ), R_O1 ) ;
    } 
    else {
      stf_ins ( i_st, frg.fr << 1, mem_temp ( 0 ) ) ;
      ld_ro_ins ( i_ld, mem_temp ( 0 ), R_O0 ) ;
    }
    a1 = nilexp ;
  }
  /* put the arguments into the call registers */
  if ( a1 != nilexp ) {
    quad_addr ( a1, R_O0, sp ) ;
    if ( a2 != nilexp ) {
      sp = needreg ( R_O0, sp ) ;
      quad_addr ( a2, R_O1, sp ) ;
    }
  }
  /* output the actual call */
  outs ( "\tcall\t" ) ;
  outs ( s ) ;
  outs ( "\n\tnop\n" ) ;
  if ( quad_ret ) outs ( "\tunimp\t16\n" ) ;
  clear_all () ;
  return ;
}


/*
  EVALUATE A FLOATING POINT OPERATION
  The floating point operation, ins, given by e is evaluated 
  into dest, using sp to get free t-registers.
*/
int fop 
    PROTO_N ( ( e, sp, dest, ins ) )
    PROTO_T ( exp e X space sp X where dest X ins_p ins ){
  exp l = son ( e ) ;
  exp r = bro ( l ) ;
  space nsp ;
  int a1, a2 ;

#if use_long_double
  if ( name ( sh ( e ) ) == doublehd ) {
    if ( IsRev ( e ) ) {
      quad_op ( r, l, sp, dest, ( int ) name ( e ) ) ;
    } 
    else {
      quad_op ( l, r, sp, dest, ( int ) name ( e ) ) ;
    }
    return ( NOREG ) ;
  }
#endif
  if ( IsRev ( e ) ) {
    /* reverse operands */
    a2 = freg_operand ( r, sp, getfreg ( sp.flt ) ) ;
    nsp = guardfreg ( a2, sp ) ;
    a1 = freg_operand ( l, nsp, getfreg ( nsp.flt ) ) ;
    } 
  else {
    a1 = freg_operand ( l, sp, getfreg ( sp.flt ) ) ;
    nsp = guardfreg ( a1, sp ) ;
    a2 = freg_operand ( r, nsp, getfreg ( nsp.flt ) ) ;
  }
  switch ( discrim ( dest.answhere ) ) {
    case infreg : {
      freg fr ;
      fr = fregalt ( dest.answhere ) ;
      rrrf_ins ( ins, a1 << 1, a2 << 1, fr.fr << 1 ) ;
      return ( ( fr.dble ) ? -( fr.fr + 32 ) : ( fr.fr + 32 ) ) ;
    }
    default : {
      ans a ;
      freg fr ;
      int r1 = getfreg ( nsp.flt ) ;
      fr.fr = r1 ;
      fr.dble = ( bool ) ( ( dest.ashwhere.ashsize == 64 ) ? 1 : 0 ) ;
      setfregalt ( a, fr ) ;
      rrrf_ins ( ins, a1 << 1, a2 << 1, r1 << 1 ) ;
      ( void ) move ( a, dest, sp.fixed, 1 ) ;
      return ( ( fr.dble ) ? -( fr.fr + 32 ) : ( fr.fr + 32 ) ) ;
    }
  }
    /* NOT REACHED */
}
