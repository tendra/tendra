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


/* 	$Id: operators.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: operators.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $";
#endif /* lint */

/* 
   operators.c
   produces code for common operations

   to do : add support for VAX floating types.
*/

/*
$Log: operators.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/06/19  15:15:03  john
 * Fix for discarded operations
 *
 * Revision 1.5  1995/09/29  07:55:05  john
 * Fixed condition for setting Has_no_vcallers
 *
 * Revision 1.4  1995/08/21  08:46:01  john
 * Changed include files
 *
 * Revision 1.3  1995/06/21  14:25:32  john
 * Reformatting
 *
 * Revision 1.2  1995/05/16  10:54:12  john
 * Cosmetic change
 *
 * Revision 1.1.1.1  1995/03/23  10:39:15  john
 * Entered into CVS
 *
 * Revision 1.9  1995/01/26  13:45:57  john
 * Removed unused variable
 *
 * Revision 1.8  1995/01/12  15:12:36  john
 * Removed dead code
 *
*/

#include "config.h"
#include "code_here.h"
#include "expmacs.h"
#include "addresstypes.h"
#include "inst_fmt.h"
#include "move.h"
#include "maxminmacs.h"
#include "getregs.h"
#include "guard.h"
#include "tags.h"
#include "shapemacs.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "alpha_ins.h"
#include "f64.h"
#include "reg_defs.h"
#include "cross.h"
#include "operators.h"
bool testover = 0;		/* always 0 for C */

void tidyshort
    PROTO_N ( ( r, s ) )
    PROTO_T ( int r X shape s )
{
  /* corrects possible overflows of chars
     and shorts in reg r */
  if (name (s) == ucharhd) {
    operate_fmt_immediate (i_and, r,255,r);
  }
  else
    if (name (s) == uwordhd) {
      operate_fmt_immediate (i_and, r,0xffff,r);
    }
}


/* 
   given a list of expressions seq which
   contains one whose value is in 
   register reg, removes that exp from seq
   and delivers 1; otherwise delivers 0 
*/
bool regremoved
    PROTO_N ( ( seq, reg ) )
    PROTO_T ( exp *seq X int reg )
{
  exp s = *seq;
  exp t = bro (s);
  if (abs (regofval (s)) == reg) {
    (*seq) = t;
    return 1;
  }
  for (;;) {
    if (abs (regofval (t)) == reg) {
      bro (s) = bro (t);
      if (last (t))
	setlast (s);
      return 1;
    }
    if (last (t)) {
      return 0;
    }
    s = t;
    t = bro (t);
  }
}


void do_comm
    PROTO_N ( ( seq, sp, final, rins ) )
    PROTO_T ( exp seq X space sp X int final X instruction rins )
{
  int   r = 0;
  space nsp;
  int   a1;
  int   a2;
  a1 = reg_operand (seq, sp);
  /* evaluate 1st operand into a1 */
  for (;;) {
    nsp = guardreg (a1, sp);
    seq = bro (seq);
    if (name (seq) == val_tag) {/* next operand is a constant */
      if (last (seq)) {
	if(isbigval(seq)){
	  int ov;
	  flt64 res;
	  INT64 ires;
	  res = flt_to_f64(no(seq),is_signed(sh(seq)),&ov);
	  ires = flt64_to_INT64(res);
	  operate_fmt_big_immediate(rins,a1,ires,final);
	}
	else
	  operate_fmt_immediate (rins,a1,no(seq),final);
	return;
      }
      else {
	if (r == 0)
	  r = getreg (sp.fixed);
	if(isbigval(seq)){
	  int ov;
	  flt64 res;
	  INT64 ires;
	  res = flt_to_f64(no(seq),is_signed(sh(seq)),&ov);
	  ires = flt64_to_INT64(res);
	  operate_fmt_big_immediate(rins,a1,ires,r);
	}
	else
	  operate_fmt_immediate(rins,a1,no(seq),r);
      }
    }
    else {
      exp sq = seq;
      instruction ins = rins;
      a2 = reg_operand (sq, nsp);
      /* evaluate next operand */
      if (last (seq)) {
	operate_fmt(ins,a1,a2,final);
	return;
      }
      else {
	if (r == 0)
	  r = getreg (sp.fixed);
	operate_fmt (ins,a1, a2,r);
      }
    }
    a1 = r;
  }
  return;
}

/* 
   evaluate commutative operation rrins given by e into d, using 
   sp to get t-regs 
*/
int comm_op
    PROTO_N ( ( e, sp, d, rrins ) )
    PROTO_T ( exp e X space sp X where d X instruction rrins )
{
  instruction rins = rrins;
  switch (d.answhere.discrim) {
    case inreg: {
      int   dest = regalt (d.answhere);
      bool usesdest = regremoved (&son (e), dest);
      exp seq = son (e);
      if(dest == NO_REG) {
	dest = getreg(sp.fixed);
      }
      
      /* the destination is in a register; take care that 
	 we dont alter it before possible use as an operand .... */
      if (usesdest && last (seq)) {
	/* ...it was used, but there is only one
	   other operand */
	if (name (seq) == val_tag) {
	  operate_fmt_immediate (rins, dest, no (seq),dest);
	}
	else {
	  operate_fmt (rins, dest,reg_operand (seq, sp),dest);
	}
	tidyshort (dest, sh (e));
	return dest;
      }
      else if (usesdest) {	/* ... it was used so ... */
        int   r = getreg (sp.fixed);
	do_comm (seq, sp, r, rins);
	/* ... evaluate the remainder of the expression into r... */
	operate_fmt (rins, dest, r,dest);
	/* ... and do dest = dest rins r */
	tidyshort (dest, sh (e));
	return dest;
      }
      else {		/* ... it wasn't used */
	do_comm (seq, sp, dest, rins);
	tidyshort (dest, sh (e));
	return dest;
      }	
    }					/* end inreg */
    default:{
      ans a;
      int   r = getreg (sp.fixed);
      space nsp;
      setregalt (a, r);
      do_comm (son (e), sp, r, rins);
      /* evaluate the expression into r ... */
      tidyshort (r, sh (e));
      nsp = guardreg (r, sp);
      move (a, d, nsp, 1);
      /* ... and move into a */
      return r;
    }				/* notinreg */
  }	      			/* end switch */
}



int non_comm_op
    PROTO_N ( ( e, sp, dest, rins ) )
    PROTO_T ( exp e X space sp X where dest X instruction rins )
{
  /* evalate binary operation e with rins
     into dest */
  exp l = son (e);
  exp r = bro (l);
  int   a1 = reg_operand (l, sp);
  space nsp;
  int   a2;
  instruction ins = rins;
  nsp = guardreg (a1, sp);
  a2 = reg_operand (r, nsp);
  /* regs a1 and a2 contain the operands */
  switch (dest.answhere.discrim) {
    case inreg: {
      int   d = regalt (dest.answhere);
      if(d!=NO_REG){
	operate_fmt(ins,a1,a2,d);
	tidyshort (d, sh (e));
      }
      return d;
    }
    default:{
      ans a;
      int   r1 = getreg (nsp.fixed);
      setregalt (a, r1);
      operate_fmt (ins, a1,a2,r1);
      tidyshort (r1, sh (e));
      nsp = guardreg (r1, sp);
      move (a, dest, nsp, 1);
      return r1;
    }
  }
}



/* evaluate floating dyadic operation e using ins into dest */
int fop
    PROTO_N ( ( e, sp, dest, ins ) )
    PROTO_T ( exp e X space sp X where dest X instruction ins )
{
  exp l = son (e);
  exp r = bro (l);
  int   a1;
  space nsp;
  int   a2;
  
  if (IsRev(e)) {
    a2 = freg_operand (r, sp);
    nsp = guardfreg (a2, sp);
    a1 = freg_operand(l, nsp);
  }
  else {
    a1 = freg_operand (l, sp);
    nsp = guardfreg (a1, sp);
    a2 = freg_operand(r, nsp);
  }
  switch (dest.answhere.discrim) {
    case infreg:{ 		/* dest in register */
      freg fr;
      fr = fregalt (dest.answhere);
      float_op(ins,a1,a2,fr.fr);
      return((fr.type==IEEE_double)?-(fr.fr+32):(fr.fr+32));
    }
    default:{ 			/* destination elsewhere */
      ans a;
      freg fr;
      int   r1 = getfreg (nsp.flt);
      fr.fr = r1;
      if(dest.ashwhere.ashsize==64)
	fr.type=IEEE_double;
      else
	fr.type=IEEE_single;
      setfregalt (a, fr);
      
      float_op(ins,a1,a2,r1);
#if 1
      if(dest.answhere.discrim == insomefreg){
	*dest.answhere.val.somefregans.fr = r1;
	dest.answhere.val.somefregans.type = fr.type;
      }
      else{
#endif
	move (a, dest, sp, 1);
#if 1
      }
#endif
      return ((fr.type==IEEE_double)?-(fr.fr+32):(fr.fr+32));
    }
  }
}






