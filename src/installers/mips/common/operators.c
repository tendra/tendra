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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: operators.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/21  15:42:55  currie
 * silly reordering by as again
 *
 * Revision 1.3  1995/09/20  14:23:06  currie
 * callee-list blunder + fix for silliness in ultrix assembler
 *
 * Revision 1.2  1995/08/16  16:07:04  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* operators.c
	produces code for common operations
*/


#include "config.h"
#include "code_here.h"
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
#include "common_types.h"
#include "mips_ins.h"
#include "operators.h"
#include "psu_ops.h"

bool testover = 0;		/* always 0 for C */

static void tidyshort
    PROTO_N ( (r, s, ins) )
    PROTO_T ( int r X shape s X char* ins )
{/* corrects possible overflows of chars
				   and shorts in reg r */
  int sz = shape_size(s);
  if (sz == 32) return;
  if (!is_signed(s)) {
	rri_ins(i_and, r, r, (1<<sz)-1);
  }
  else
  if (ins == i_not || ins == i_nor) {
	rri_ins(i_sll, r, r, 32-sz);
	rri_ins(i_sra, r, r, 32-sz);
  }
}

bool regremoved
    PROTO_N ( (seq, reg) )
    PROTO_T ( exp * seq X int reg )
{
				/* given a list of expressions seq which
				   contains one whose value is in
				   register reg, removes that exp from seq
				   and delivers 1; otherwise delivers 0 */
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
    PROTO_N ( (seq, sp, final, rins) )
    PROTO_T ( exp seq X space sp X int final X char *rins )
{
				/* evaluates the fixed operation seq1 rins
				   seq 2 rins...., into reg final, using
				   sp as free t-regs */
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
	rri_ins (rins, final, a1, no (seq));
	return;
      }
      else {
	if (r == 0)
	  r = getreg (sp.fixed);
	rri_ins (rins, r, a1, no (seq));
      }
    }
    else {
      exp sq = seq;
      char *ins = rins;
      a2 = reg_operand (sq, nsp);
      /* evaluate next operand */
      if (last (seq)) {
	rrr_ins (ins, final, a1, a2);
	return;
      }
      else {
	if (r == 0)
	  r = getreg (sp.fixed);
	rrr_ins (ins, r, a1, a2);
      }
    }
    a1 = r;
  }
}


int   comm_op
    PROTO_N ( (e, sp, d, rrins) )
    PROTO_T ( exp e X space sp X where d X char *rrins )
{
				/* evaluate commutative operation rrins
				   given by e into d, using sp to get
				   t-regs */
  char *rins = rrins;


  switch (d.answhere.discrim) {
    case inreg:
      {
	int   dest = regalt (d.answhere);
	bool usesdest = regremoved (&son (e), dest);
	exp seq = son (e);
	/* the destination is in a register; take care that we dont alter
	   it before possible use as an operand .... */
	if (usesdest && last (seq)) {
				/* ...it was used, but there is only one
				   other operand */
	  if (name (seq) == val_tag) {
	    rri_ins (rins, dest, dest, no (seq));
	  }
	  else {
	    rrr_ins (rins, dest, dest, reg_operand (seq, sp));
	  }
	  tidyshort (dest, sh (e), rins);
	  return dest;
	}
	else
	  if (usesdest) {	/* ... it was used so ... */
	    int   r = getreg (sp.fixed);
	    do_comm (seq, sp, r, rins);
	    /* ... evaluate the remainder of the expression into r... */
	    rrr_ins (rins, dest, dest, r);
	    /* ... and do dest = dest rins r */
	    tidyshort (dest, sh (e), rins);
	    return dest;
	  }
	  else {		/* ... it wasn't used */
	    do_comm (seq, sp, dest, rins);
	    tidyshort (dest, sh (e), rins);
	    return dest;
	  }
      }				/* end inreg */

    default:
      {
	ans a;
	int   r = getreg (sp.fixed);
	space nsp;
        bool rok =1;
	setregalt (a, r);
	do_comm (son (e), sp, r, rins);
	/* evaluate the expression into r ... */
	if(d.answhere.discrim != notinreg) {
		tidyshort (r, sh (e), rins);
        } else rok = shape_size(sh(e))==32;
	nsp = guardreg (r, sp);
	move (a, d, nsp, 1);
	/* ... and move into a */
	return ((rok)?r:NOREG);
      }				/* notinreg */
  }				/* end switch */
}

int   non_comm_op
    PROTO_N ( (e, sp, dest, rins) )
    PROTO_T ( exp e X space sp X where dest X char *rins )
{
				/* evalate binary operation e with rins
				   into dest */
        exp l = son (e);
  exp r = bro (l);
  int   a1 = reg_operand (l, sp);
  space nsp;
  int   a2;
  char *ins = rins;


  nsp = guardreg (a1, sp);
  a2 = reg_operand (r, nsp);
  /* regs a1 and a2 contain the operands */
  switch (dest.answhere.discrim) {
    case inreg: 		/* destination in register */
      {
	int   d = regalt (dest.answhere);
	rrr_ins (ins, d, a1, a2);
	tidyshort (d, sh (e), rins);
	return d;
      }

    default: 			/* destination elsewhere */
      {
	ans a;
	int   r1 = getreg (nsp.fixed);
        int rok = 1;
	setregalt (a, r1);
	rrr_ins (ins, r1, a1, a2);
	if(dest.answhere.discrim != notinreg){
		tidyshort (r1, sh (e), rins);
	} else rok = shape_size(sh(e))==32;
	nsp = guardreg (r1, sp);
	move (a, dest, nsp, 1);
	return (rok)?r1:NOREG;
      }
  }
}

int   monop
    PROTO_N ( (e, sp, dest, ins) )
    PROTO_T ( exp e X space sp X where dest X char *ins )
{
				/* evaluate fixed monadic operation e
				   using ins into dest */
  int   r1 = getreg (sp.fixed);
  int   a1 = reg_operand (son (e), sp);
  /* operand in reg a1 */
  space nsp;
  switch (dest.answhere.discrim) {
    case inreg: 		/* destination in register */
      {
	int   d = regalt (dest.answhere);
	mon_ins (ins, d, a1);
	tidyshort (d, sh (e), ins);
	return d;
      }

    default: 			/* destination elsewhere */
      {
	ans a;
	int rok = 1;
	setregalt (a, r1);
	mon_ins (ins, r1, a1);
	if(dest.answhere.discrim != notinreg){
		tidyshort (r1, sh (e), ins);
	} else rok = shape_size(sh(e))==32;
	nsp = guardreg (r1, sp);
	move (a, dest, nsp, 1);
	return ((rok)?r1:NOREG);
      }
  }
}

int   fop
    PROTO_N ( (e, sp, dest, ins) )
    PROTO_T ( exp e X space sp X where dest X char *ins )
{
				/* evaluate floating dyadic operation e
				   using ins into dest */
        exp l = son (e);
  exp r = bro (l);
  int   a1;
  space nsp;
  int   a2;
  freg fr;

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

  if (!optop(e)) setnoreorder();

  switch (dest.answhere.discrim) {
    case infreg: 		/* dest in register */
      {
	fr = fregalt (dest.answhere);
	rrrfp_ins (ins, fr.fr << 1, a1 << 1, a2 << 1);
        break;
      }
    default: 			/* destinationelsewhere */
      {
	ans a;
	int   r1 = getfreg (nsp.flt);
	fr.fr = r1;
	fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
	setfregalt (a, fr);
	rrrfp_ins (ins, r1 << 1, a1 << 1, a2 << 1);
	move (a, dest, sp, 1);
      }
  }
  if (!optop(e)) setreorder();
  return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
}

int   fmop
    PROTO_N ( (e, sp, dest, ins) )
    PROTO_T ( exp e X space sp X where dest X char *ins )
{
				/* evaluate floating monadic operation e
				   using ins into dest */
  int   a1 = freg_operand (son (e), sp);
  freg fr;
  if (!optop(e)) setnoreorder();
  switch (dest.answhere.discrim) {
    case infreg:
      {
	fr = fregalt (dest.answhere);
	rrfp_ins (ins, fr.fr << 1, a1 << 1);
        break;
      }

    default:
      {
	ans a;
	fr.fr = getfreg(sp.flt);
	fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
	setfregalt (a, fr);
	rrfp_ins (ins, fr.fr << 1, a1 << 1);
	move (a, dest, sp, 1);
      }
  }
  if(!optop(e)) setreorder();
  return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
}
