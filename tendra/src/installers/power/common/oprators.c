/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
$Date: 1998/02/04 15:49:01 $
$Revision: 1.2 $
$Log: oprators.c,v $
 * Revision 1.2  1998/02/04  15:49:01  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/11/18  15:50:25  pwe
 * correct alias with bitfields, and case odds
 *
 * Revision 1.2  1996/10/04  16:03:10  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "myassert.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "maxminmacs.h"		/* for absval() */
#include "flags.h"
#include "instruct.h"
#include "proc.h"
#include "oprators.h"
#include "comment.h"
#include "makecode.h"
#include "error.h"

void tidyshort PROTO_N ((r,e)) PROTO_T (int r X exp e)
{
  shape s = sh(e);
  switch(name(e))
  {
   case and_tag:
    {
      exp r = bro(son(e));/* could be a val_tag */
      if(name(s)==ucharhd && name(r)==val_tag && ( (no(r) & 0xff) == no(r) ))
      {
	return;
      }
      if(name(s)==uwordhd && name(r)==val_tag && ( (no(r) & 0xffff) == no(r) ))
      {
	return;
      }
    }
  }
  
  if (name(s) == ucharhd)
  {
    rir_ins(i_and, r, 255, r);
  }
  else if (name(s) == uwordhd)
  {
    rir_ins(i_and, r, 0xffff, r);
  }
}


 /*
  * given a list of expressions seq which contains one whose value is in
  * register reg, removes that exp from seq and delivers 1; otherwise delivers 0
  */
bool regremoved PROTO_N ((seq,reg)) PROTO_T (exp * seq X int reg)
{
  exp s = *seq;
  exp t = bro(s);

  if (absval(regofval(s)) == reg)
  {
    (*seq) = t;
    return 1;
  }
  for (;;)
  {
    if (absval(regofval(t)) == reg)
    {
      bro(s) = bro(t);
      if (last(t))
	setlast(s);
      return 1;
    }
    if (last(t))
    {
      return 0;
    }
    s = t;
    t = bro(t);
  }
}


 /*
  * evaluates the fixed operation seq1 rins seq 2 rins...., into reg final,
  * using sp as free t-regs
  */
void do_comm PROTO_N ((seq,sp,final,rins)) PROTO_T (exp seq X space sp X int final X Instruction_P rins)
{
  int r = 0;
  space nsp;
  int a1;
  int a2;

  /* should have been optimised in scan... */
  ASSERT(!(rins == i_a && name(seq) == neg_tag && name(bro(seq)) != val_tag));

  /* evaluate 1st operand into a1 */
  a1 = reg_operand(seq, sp);

  for (;;)
  {
    nsp = guardreg(a1, sp);
    seq = bro(seq);
    if (name(seq) == val_tag)	/* next operand is a constant */
    {
      if (last(seq))
      {
	rir_ins(rins, a1, no(seq), final);
	return;
      }
      else
      {
	if (r == 0)
	  r = getreg(sp.fixed);
	rir_ins(rins, a1, no(seq), r);
      }
    }
    else
    {
      exp sq = seq;
      Instruction_P ins = rins;

      a2 = reg_operand(sq, nsp);
      /* evaluate next operand */
      if (last(seq))
      {
	rrr_ins(ins, a1, a2, final);
	return;
      }
      else
      {
	if (r == 0)
	  r = getreg(sp.fixed);
	rrr_ins(ins, a1, a2, r);
      }
    }
    a1 = r;
  }
}


/*
 * Evaluate commutative operation rrins given by e into d,
 * using sp to get t-regs 
 */
int comm_op PROTO_N ((e,sp,d,rrins)) PROTO_T (exp e X space sp X where d X Instruction_P rrins)
{
  Instruction_P rins = rrins;

  switch (d.answhere.discrim)
  {
  case inreg:
    {
      int dest = regalt(d.answhere);
      bool usesdest = regremoved(&son(e), dest);
      exp seq = son(e);

      /*
       * the destination is in a register; take care that we don't alter it
       * before possible use as an operand ....
       */
      if (usesdest && last(seq))
      {
	/* used, but there is only one other operand */
	if (name(seq) == val_tag)
	{
	  rir_ins(rins, dest, no(seq), dest);
	}
	else
	{
	  rrr_ins(rins, dest, reg_operand(seq, sp), dest);
	}
	tidyshort(dest, e);
	return dest;
      }
      else if (usesdest)
      {
	/* dest used, use temp */
	int r = getreg(sp.fixed);

	do_comm(seq, sp, r, rins);
	rrr_ins(rins, dest, r, dest);
	tidyshort(dest, e);
	return dest;
      }
      else
      {
	/* dest not used, evaluate into dest */
	do_comm(seq, sp, dest, rins);
	tidyshort(dest, e);
	return dest;
      }
    }				/* end inreg */
  default:
    {
      ans a;
      int r = getreg(sp.fixed);
      space nsp;
      bool rok =1;
      setregalt(a, r);
      do_comm(son(e), sp, r, rins);
      /* evaluate the expression into r ... */
      if(d.answhere.discrim != notinreg) { 
	tidyshort (r, e);
      } 
      else 
	rok = shape_size(sh(e))==32;
      nsp = guardreg(r, sp);
      move(a, d, nsp.fixed, 1);
      /* ... and move into a */
      return ((rok)?r:NOREG);
    }				/* notinreg */
  }				/* end switch */
}

/* evalate binary operation e with ins into dest */
int non_comm_op PROTO_N ((e,sp,dest,ins)) PROTO_T (exp e X space sp X where dest X Instruction_P ins)
{
  exp l = son(e);
  exp r = bro(l);
  bool sf_imm = name(l) == val_tag && ins == i_s && IMM_SIZE(no(l));
		/* we can use sfi instruction */
  int a1;
  int a2;
  space nsp;

  switch (dest.answhere.discrim)
  {
  case inreg:
    {
      int d = regalt(dest.answhere);

      if (sf_imm)
      {
	rir_ins(i_sf, reg_operand(r, sp), no(l), d);
      }
      else
      {
	a1 = reg_operand(l, sp);
	nsp = guardreg(a1, sp);
	a2 = reg_operand(r, nsp);
	rrr_ins(ins, a1, a2, d);
      }

      tidyshort(d, e);
      return d;
    }

  default:			/* destination elsewhere */
    {
      ans a;
      int r1 = getreg(sp.fixed);

      setregalt(a, r1);

      if (sf_imm)
      {
	rir_ins(i_sf, reg_operand(r, sp), no(l), r1);
      }
      else
      {
	a1 = reg_operand(l, sp);
	nsp = guardreg(a1, sp);
	a2 = reg_operand(r, nsp);
	rrr_ins(ins, a1, a2, r1);
      }

      tidyshort(r1, e);
      nsp = guardreg(r1, sp);
      move(a, dest, nsp.fixed, 1);
      return r1;
    }
  }
}

/* evaluate floating dyadic operation e using ins into dest */
int fop PROTO_N ((e,sp,dest,ins)) PROTO_T (exp e X space sp X where dest X Instruction_P ins)
{
  exp l = son(e);
  exp r = bro(l);
  int a1;
  int a2;
  space nsp;

  if (IsRev(e))
  {
    a2 = freg_operand(r, sp, getfreg(sp.flt));
    nsp = guardfreg(a2, sp);
    a1 = freg_operand(l, nsp, getfreg(nsp.flt));
  }
  else
  {
    a1 = freg_operand(l, sp, getfreg(sp.flt));
    nsp = guardfreg(a1, sp);
    a2 = freg_operand(r, nsp, getfreg(nsp.flt));
  }

  switch (dest.answhere.discrim)
  {
  case infreg:			/* dest in register */
    {
      freg fr;

      fr = fregalt(dest.answhere);
      if (ERROR_TREATMENT(e))
      {
	do_fop_error_jump(e,a1,a2,fr.fr);/* Floating point error jump */
      }
      else
      {
	rrrf_ins(ins, a1, a2, fr.fr);
      }
      if (fr.dble==0 && round_after_flop)
      {
	rrf_ins(i_frsp,fr.fr,fr.fr);
      }   
      return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
  default:			/* destination elsewhere */
    {
      ans a;
      freg fr;
      int r1 = getfreg(nsp.flt);

      fr.fr = r1;
      fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
      setfregalt(a, fr);
      if (ERROR_TREATMENT(e))
      {
	do_fop_error_jump(e,a1,a2,fr.fr);/* Floating point error jump */
      }
      else
      {
	rrrf_ins(ins, a1, a2, r1);
      }
      if (fr.dble==0 && round_after_flop)
      {
	rrf_ins(i_frsp,r1,r1);
      }   
      move(a, dest, sp.fixed, 1);
      return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
  }
}

/* evaluate floating monadic operation e using ins into dest */
int fmop PROTO_N ((e,sp,dest,ins)) PROTO_T (exp e X space sp X where dest X Instruction_P ins)
{
  int a1 = freg_operand(son(e), sp, getfreg(sp.flt));

  switch (dest.answhere.discrim)
  {
  case infreg:
    {
      freg fr;

      fr = fregalt(dest.answhere);
      if (ERROR_TREATMENT(e))
      {
	do_fmop_error_jump(e,a1,fr.fr);
      }
      else
      {
	rrf_ins(ins, a1, fr.fr);
      }
      if (fr.dble==0 && round_after_flop)
      {
	rrf_ins(i_frsp,fr.fr,fr.fr);
      }
      return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }

  default:
    {
      ans a;
      freg fr;

      fr.fr = getfreg(sp.flt);
      fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
      setfregalt(a, fr);
      if (ERROR_TREATMENT(e))
      {
	do_fmop_error_jump(e,a1,fr.fr);
      }
      else
      {
	rrf_ins(ins, a1, fr.fr);      
      }
      if (fr.dble==0 && round_after_flop)
      {
	rrf_ins(i_frsp,fr.fr,fr.fr);
      }      
      move(a, dest, sp.fixed, 1);
      return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
  }
}
