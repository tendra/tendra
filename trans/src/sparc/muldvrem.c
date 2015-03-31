/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/exp.h>
#include <construct/shape.h>

#include <main/flags.h>

#include "scan.h"
#include "addrtypes.h"
#include "maxminmacs.h"
#include "proctypes.h"
#include "eval.h"
#include "move.h"
#include "oprators.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "sparcins.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "special.h"
#include "regmacs.h"
#include "translate.h"
#include "muldvrem.h"
#include "make_code.h"

/*
  NUMBER OF BITS IN A WORD
*/

#define BITS_PER_WORD		32


/*
  MULTIPLICATION LIMITS
  MAX_MUL_POW2_OFFSET is the maximum m such that 2**n +/- m is a
  simple multiplication.  NOT_MUL_CONST_SIMPLE is any value larger
  than this and is used as an error return.
*/

#define MAX_MUL_POW2_OFFSET	2
#define NOT_MUL_CONST_SIMPLE	(MAX_MUL_POW2_OFFSET + 1)


/*
  IS c A POWER OF TWO?
*/

#define IS_POW2(c)	((c)!= 0 && ((c) & ((c) - 1)) == 0)


/*
  GIVEN A POWER OF TWO, c, FIND n WHERE c = 2**n
*/

#define IS_TRAP 1

static int bit_no
(long c) {
  int n;
  unsigned long m;
  assert(IS_POW2(c));
  for (m = 1, n = 0; m != (unsigned long)c; m = m << 1)n++;
  return n;
}


/*
  VERSION OF rir_ins WITH CAST
*/

#define rcr_ins(a, b, c, d)	rir_ins(a, b,(long)(c), d)


#if 0
/*
  CLEAR REGISTERS USED BY MULTIPLICATION SYSTEM CALL ETC

  According to the System V ABI only registers %o0,...,%o7 are
  clobbered by the system calls .mul, .div etc.  However :
  1.  SunOS 4.1.1 does not follow SPARC ABI.
  2.  Even if it did, the assembler -O optimiser does not regard
  %g1..%g7 as alive after a call and so does not preserve them,
  or renumber them as needed after any call, even to .mul.
  Note that it does regard float regs alive after a call.
*/

static void clear_abi_call_muldivrem_regs
(space sp) {
  int r;
  for (r = R_O0; r != R_O7 + 1; r++) {
    /* grab remaining param regs for safety test for bad code */
    if (!(r == R_O0 || r == R_TMP || r == R_SP)) {
      /* already done or special */
      sp = needreg(r, sp);
    }
    /* clear regs modified by .mul/.umul */
    clear_reg(r);
  }
}
#endif


/*
  CLEAR REGISTERS ACTUALLY USED BY MULTIPLICATION SYSTEM CALL ETC

  This is the version of the routine above which reflect reality.
  Registers %o0,...,%o7 and %g1,...,%g_reg_max are clobbered.
*/

static void
clear_sun_call_divrem_regs(space sp) {
  int r;
  for (r = R_G1; r != R_O7 + 1;
	  r = ((r == R_G0 + g_reg_max)? R_O0 : r + 1)) {
	/* grab remaining param regs for safety test for bad code */
    if (!(r == R_O0 || r == R_TMP || r == R_SP)) {
      /* already done or special */
      sp = needreg(r, sp);
    }
    /* clear regs modified by .mul/.umul */
    clear_reg(r);
  }
}


/*
  CALL A MULTIPLICATION/DIVISION/REMAINDER SYSTEM ROUTINE
*/

static int
call_muldivrem(exp lhs, exp rhs, space sp, int proc, int err_t)
{
  int lhs_reg = -1;
  int rhs_reg = -1;
  if (err_t) {
    /* division has error treatment, so check -MAXINT-1/-1 */
    if ((sh(lhs)->tag == slonghd) &&
      ((lhs->tag!=val_tag) || (no(lhs) == -0x80000000)) &&
      ((rhs->tag!= val_tag) || (no(rhs) == -1))) {
      int ok_lab = new_label();
      lhs_reg = reg_operand(lhs,sp);
      rhs_reg = reg_operand(rhs,guardreg(lhs_reg,sp));
      if (rhs->tag == val_tag) {
	if (no(rhs)!= -1) {
	  uncond_ins(i_b,ok_lab);
	}
      }
      if (lhs->tag == val_tag) {
	if (no(lhs)!= -0x80000000) {
	  uncond_ins(i_b,ok_lab);
	}
      }
      condri_ins(i_bne,rhs_reg,-1,ok_lab);
      condri_ins(i_bne,lhs_reg,-0x80000000,ok_lab);
      if (err_t == IS_TRAP) {
	do_exception(f_overflow);
      }
      else{
	uncond_ins(i_b,-err_t);
      }
      set_label(ok_lab);
    }
  }
  if (lhs_reg != R_O0)reg_operand_here(lhs, sp, R_O0);
  sp = needreg(R_O0, sp);
  if (rhs_reg != R_O1)reg_operand_here(rhs, sp, R_O1);
  call_special_routine(proc);
  clear_sun_call_divrem_regs(sp);
  /* result left in R_O0 */
  return R_O0;
}


/*
  GENERATE CODE FOR MULTIPLICATION BY A COMPLEX CONSTANT
  This algorithm is not optimal, but it's not bad.
*/

static void mul_const_complex
(int src, long constval, int dest, space sp, bool sgned) {
  struct {
    unsigned char bsl ;		/* bit-string of 1's length */
    unsigned char shift ;		/* shift from right of word */
  } bs_tab[BITS_PER_WORD / 2];

  int bs_tab_len = 0;
  int bsl_1_tab = -1;
  int max_bsl = 0;
  /* special case ~0 cannot be handled by the general algorithm */
  if (constval == ~0) {
    if (sgned) {
      /* X * -1 => -X */
      assert(constval == -1);
      rr_ins(i_neg, src, dest);
    }
    else {
      rr_ins(i_neg, src, dest);
    }
    return;
  }
  /* set up bs_tab from constval */
  {
    unsigned long c = (unsigned long)constval;
    int bsl = 0, sby;
    for (sby = 0; sby <= BITS_PER_WORD; sby++, c >>= 1) {
      if (c & 1) {
	bsl++;
      }
      else if (bsl != 0) {
	/* a complete all-1's bit-string */
	assert(bs_tab_len < BITS_PER_WORD / 2);
	bs_tab[bs_tab_len].bsl = (unsigned char)bsl;
	bs_tab[bs_tab_len].shift = (unsigned char)(sby - bsl);
	if (bsl == 1)bsl_1_tab = bs_tab_len;
	if (bsl > max_bsl)max_bsl = bsl;
	bs_tab_len++;
	bsl = 0;
      }
    }
  }
  assert ( bs_tab_len > 0 ) ;	/* shouldn't be here otherwise */
  assert(max_bsl >= 1);
  assert ( max_bsl <= 31 ) ;	/* shifts by 32 don't work */

    /* generate the code */
  {
    int bsl;
    int bsl_laststep_tab;
    int tmp = R_TMP;
    int accum;
    bool accum_init = 0;

    /* allocate regs */
    assert(src != R_TMP);
    assert(dest != R_TMP);

    if (src != dest) {
      accum = dest;
    }
    else {
      accum = getreg(sp.fixed);
    }
    assert(src != accum);

    /* init accum if useful */
    if (bsl_1_tab >= 0 && bs_tab[bsl_1_tab].shift != 0) {
      /* Usefully do one of the 1 bit strings with simple shift to
	 accum.  If left to general algorithm 2 instructions, shift
	 and move/add, would often be used */
      assert(bs_tab[bsl_1_tab].bsl == 1);
      rcr_ins(i_sll, src, bs_tab[bsl_1_tab].shift, accum);
      bs_tab[bsl_1_tab].bsl = 0;
      accum_init = 1;
    }

    /* find last cond generation step, so we can move to dest then */
    bsl_laststep_tab = -1;
    for (bsl = max_bsl; bsl > 0; bsl--) {
      int i;
      for (i = 0; i < bs_tab_len; i++) {
	if (bs_tab[i].bsl == (unsigned char)bsl)bsl_laststep_tab = i;
      }
    }
    assert(bsl_laststep_tab != -1);

    /* accumulate handle all bit strings of same length together, so
       'src * ( ( 2 ** bsl ) - 1 )' can be shared */
    for (bsl = max_bsl; bsl > 0; bsl--) {
      int i;
      int tmp_shifted;
      bool found_bsl = 0;
      for (i = 0; i < bs_tab_len; i++) {
	if (bs_tab[i].bsl == (unsigned char)bsl) {
	  int to_accum_reg;
	  int step_accum_dest = (i == bsl_laststep_tab ?
				  dest : accum);
	  assert(accum != R_NO_REG);
	  /* amount to accum into tmp reg */
	  if (bsl == 1) {
	    /* accumulate src << shift */
	    if (bs_tab[i].shift == 0) {
	      /* simple add */
	      to_accum_reg = src;
	    }
	    else {
	      /* simple shift and add */
	      rcr_ins(i_sll, src, bs_tab[i].shift, tmp);
	      to_accum_reg = tmp;
	    }
	  }
	  else {
	    /* accumulate ( src * ( ( 2**bsl ) - 1 ) ) << shift */
	    if (!found_bsl) {
	      rcr_ins(i_sll, src, bsl, tmp);
	      rrr_ins(i_sub, tmp, src, tmp);
	      tmp_shifted = 0;
	      found_bsl = 1;
	    }
	    if (bs_tab[i].shift != (unsigned char)tmp_shifted) {
	      int extra_shift = bs_tab[i].shift - (unsigned char)tmp_shifted;
	      assert(extra_shift > 0 && extra_shift <= 31);
	      rcr_ins(i_sll, tmp, extra_shift, tmp);
	      tmp_shifted += extra_shift;
	    }
	    /* else tmp already shifted to correct position */
	    to_accum_reg = tmp;
	  }
	  /* accumulate into accum, or on last step to dest */
	  if (accum_init) {
	    rrr_ins(i_add, accum, to_accum_reg,step_accum_dest);
	  }
	  else {
	    rr_ins(i_mov, to_accum_reg, step_accum_dest);
	    accum_init = 1;
	  }
	  if (i == bsl_laststep_tab) {
	    /* error check */
	    accum = R_NO_REG;
	  }
	}
      }
    }
    assert(accum_init);
    assert(accum == R_NO_REG);
    /* result in dest, due to step_accum_dest above */
  }
}


/*
  IS A CONSTANT SIMPLE FOR MULTIPLICATION?

  A simple constant is one of the form +/- 2**n +/- m where m is at
  most MAX_MUL_POW2_OFFSET.  If constval is of this form, m is
  returned, otherwise NOT_MUL_CONST_SIMPLE is returned.
*/

static int offset_mul_const_simple
(long constval, bool sgned) {
  int i;
  if (constval < 0) {
    if (sgned) {
      constval = -constval;
    }
    else {
      /* very rare case */
      return NOT_MUL_CONST_SIMPLE;
    }
  }
  for (i = 0; i <= MAX_MUL_POW2_OFFSET; i++) {
    long c ;	/* power of two close to constval */
    /* check for add offsets, avoiding overflow confusion */
    c = constval - i;
    if (IS_POW2(c) && c + i == constval) return i;
    /* check for sub offset of 1 only, avoiding overflow confusion */
    if (i == 1) {
      c = constval + i;
      if (IS_POW2(c) && c - i == constval) return -i;
    }
  }
  return NOT_MUL_CONST_SIMPLE;
}


/*
  MULTIPLICATION BY A SIMPLE CONSTANT
*/

static void mul_const_simple
(int src, long constval, int dest, bool sgned) {
  long c ;		/* power of two close to constval */
  int add_sub ;	/* difference from power of two */
  int shift_const;

  if (sgned && constval < 0) {
    if (constval == -1) {
      /* X * -1 => -X */
      rr_ins(i_neg, src, dest);
      return;
    }
    constval = -constval;
    /* incorrect to modify source */
    rr_ins(i_neg, src, R_TMP);
    src = R_TMP;
  }

  if (constval == 1) {
    if (src != dest) {
      rr_ins(i_mov, src, dest);
    }
    return;
  }
  else if (constval == 2) {
    /* use add, which can be peephole optimised to addcc later */
    rrr_ins(i_add, src, src, dest);
    return;
  }
  add_sub = offset_mul_const_simple(constval, sgned);
  c = constval - add_sub;

  assert(constval == c + add_sub);
  shift_const = bit_no(c);
  assert(constval == (1 << shift_const) + add_sub);
  if (add_sub == 0) {
    rcr_ins(i_sll, src, shift_const, dest);
  }
  else {
    /* add_sub != 0 */
    int i;
    int n ;		/* number of add_sub instructions */
    int inter_reg ;	/* for partial result */
    ins_p i_add_sub;

    if (add_sub > 0) {
      i_add_sub = i_add;
      n = add_sub;
    }
    else {
      i_add_sub = i_sub;
      n = -add_sub;
    }
    if (src == dest) {
      /* must preserve src for add/sub */
      inter_reg = R_TMP;
    }
    else {
      inter_reg = dest;
    }
    assert(src != inter_reg);
    rcr_ins(i_sll, src, shift_const, inter_reg);
    /* all but final add_sub */
    for (i = 1; i < n; i++) {
      rrr_ins(i_add_sub, inter_reg, src, inter_reg);
    }

    /* final add_sub to dest reg */
    rrr_ins(i_add_sub, inter_reg, src, dest);
  }
}


/*
  CODE GENERATION ROUTINE FOR MULTIPLICATION BY A CONSTANT
*/

static void mul_const
(int src, long constval, int dest, space sp, bool sgned) {
  if (constval == 0) {
    /* rare case not handled by mul_const_X () */
    ir_ins(i_mov, 0, dest);
  }
  else if (offset_mul_const_simple(constval, sgned) ==
	    NOT_MUL_CONST_SIMPLE) {
    mul_const_complex(src, constval, dest, sp, sgned);
  }
  else {
    mul_const_simple(src, constval, dest, sgned);
  }
}


/*
  CODE GENERATION ROUTINE FOR MULTIPLICATION OPERATIONS
*/
static int do_mul_comm
(exp seq, space sp, int final_reg, bool sgned) {
  space nsp;
  int mul_proc;
  exp arg2 = bro(seq);
  int has_error_treatment = !optop(father(seq));
  if (arg2->tag == val_tag && !has_error_treatment) {
    /* const optim */
    int lhs_reg = reg_operand(seq, sp);
    sp = guardreg(lhs_reg, sp);
    /* check () & scan () should move const to last */
    assert(last(arg2));
    if (final_reg == R_NO_REG || final_reg == R_G0) {
      /* better code from mul_const if src != dest reg */
      final_reg = getreg(sp.fixed);
      sp = guardreg(final_reg, sp);
    }
    mul_const(lhs_reg,(long)no(arg2), final_reg, sp, sgned);
    return final_reg;
  }
  /* need to call .mul/.umul */
  mul_proc = (sgned ? SPECIAL_MUL : SPECIAL_UMUL);
  reg_operand_here(seq, sp, R_O0);
  nsp = needreg(R_O0, sp);
  for (; ;) {
    /* should have break out below by now */
    assert(!last(seq));
    seq = bro(seq);
    if (!has_error_treatment && seq->tag == val_tag &&
	 offset_mul_const_simple((long)no(seq), sgned)!=
	 NOT_MUL_CONST_SIMPLE) {
      /* const optim */
      /* check () & scan () should move const to last */
      assert(last(seq));
      if (final_reg == R_NO_REG) {
	/* better code from mul_const if src != dest reg */
	final_reg = R_O1;
      }
      mul_const(R_O0,(long)no(seq), final_reg, nsp, sgned);
      break;
    }
    else {
      reg_operand_here(seq, nsp, R_O1);
      if (has_error_treatment) {
	rrr_ins(sgned?i_smulcc:i_umulcc,R_O0,R_O1,R_O0);
      }
      else{
	call_special_routine(mul_proc);
      }
      clear_sun_call_divrem_regs(nsp);
      if (last(seq)) {
	if (final_reg == R_NO_REG || final_reg == R_G0) {
	  final_reg = R_O0;
	}
	else {
	  rr_ins(i_mov, R_O0, final_reg);
	}
	break;
      }
    }
  }
  return final_reg;
}


/*
  FLAG : ALTERNATIVE DIVISION

  There are two division and remainder operations.  In the first the
  remainder has the same sign as the denominator, and in the second
  the same sign as the numerator.  The second is the default.  This
  flag is set to indicate that the first form should be used.
*/

/* using a flag is unsafe, lest the lhs itself contains a div.
   Instead recompute otherdiv when needed*/
/*static bool other_div = 0 ;*/


/*
  CODE GENERATION ROUTINE FOR DIVISION OPERATIONS
*/

static int do_div
(exp seq, space sp, int final_reg, bool sgned) {
  int p;
  exp lhs = seq;
  exp rhs = bro(lhs);
  int has_error_treatment = !optop(father(seq)) && !error_treatment_is_trap(father(seq));
  int et;
  assert ( last ( rhs ) ) ;	/* so bro(rhs) == the div exp  */
  if (!has_error_treatment && rhs->tag == val_tag &&
       IS_POW2(no(rhs)) && no(rhs) > 0) {
    long constval = no(rhs);
    /* const optim, replace div by 2**n by shift right */
    int lhs_reg = reg_operand(lhs, sp);
    int shift_const = bit_no(constval);
    sp = guardreg(lhs_reg, sp);
    if (final_reg == R_NO_REG) {
      final_reg = getreg(sp.fixed);
      sp = guardreg(final_reg, sp);
    }
    if (constval == 1) {
      /* result always lhs */
      rr_ins(i_mov, lhs_reg, final_reg);
      return final_reg;
    }

    if (!sgned) {
				/* unsigned, easy, just shift */
      rcr_ins(i_srl, lhs_reg, shift_const, final_reg);
      return final_reg;
    }

    if (bro(rhs)->tag == div2_tag) /* shift and fix up for sgned div2 */
    {
      /* signed, adjust lhs before shift */
      int tmp_reg = R_TMP;
      assert ( shift_const > 0 ) ; /* assumed below */
      if (shift_const - 1 != 0) {
	rcr_ins(i_sra, lhs_reg, shift_const - 1, tmp_reg);
	rcr_ins(i_srl, tmp_reg, 32 - shift_const, tmp_reg);
      } else {
	rcr_ins(i_srl, lhs_reg, 32 - shift_const, tmp_reg);
      }
      rrr_ins(i_add, lhs_reg, tmp_reg, tmp_reg);
      rcr_ins(i_sra, tmp_reg, shift_const, final_reg);
      return final_reg;
    }
				/* must be signed div1, a simple shift */
    rcr_ins(i_sra, lhs_reg, shift_const, final_reg);
    return final_reg;
  }
  if(0 /*has_error_treatment*/) {
    ins_p dop;
    reg_operand_here(lhs,sp,R_O0);
    reg_operand_here(rhs,sp,R_O1);
    if (error_treatment_is_trap(father(seq))) {
      if (sgned) {
	dop = i_sdiv;
      }
      else{
	dop = i_udiv;
      }
    }
    else{
      if (sgned) {
	dop = i_sdivcc;
      }
      else{
	dop = i_udivcc;
      }
    }
    rrr_ins(dop,R_O0,R_O1,R_O0);
    return R_O0;
    /* otherwise need to call .div/.udiv */
  }
  else if (sgned && bro(rhs)->tag == div1_tag) {
    p = SPECIAL_DIV1;
  }
  else {
    p = (sgned ? SPECIAL_DIV2 : SPECIAL_UDIV2);
  }
  if (error_treatment_is_trap(father(seq))) {
    et = IS_TRAP;
  }
  else if (has_error_treatment) {
    et = -no(son(pt(father(seq))));
  }
  else {
    et = 0;
  }
  return call_muldivrem(lhs, rhs, sp, p, et);
}


/*
  CODE GENERATION ROUTINE FOR REMAINDER OPERATIONS
*/

static int do_rem
(exp seq, space sp, int final_reg, bool sgned) {
  int p;
  exp lhs = seq;
  exp rhs = bro(lhs);

  assert(last(rhs));

  if (rhs->tag == val_tag && IS_POW2(no(rhs)) && (no(rhs) > 0)) {
    long constval = no(rhs);

    /* const optim, replace rem by 2**n by and with mask */
    int lhs_reg = reg_operand(lhs, sp);
    sp = guardreg(lhs_reg, sp);

    if (final_reg == R_NO_REG) {
      final_reg = getreg(sp.fixed);
    }

    if (constval == 1) {
      /* result always 0 */
      ir_ins(i_mov, 0, final_reg);
      return final_reg;
    }
    if (!sgned) {
		/* unsigned by mask */
      rcr_ins(i_and, lhs_reg, constval - 1, final_reg);
      return final_reg;
    }
    if (bro(rhs)->tag == rem2_tag) {
      /* signed, need to allow for negative lhs. Treat l % c
	 as l - ( l / c ) * c */
      int tmp_reg = R_TMP;
      int shift_const = bit_no(constval);
      assert ( shift_const > 0 ) ; /* assumed below */
      /* do the divide, as in do_div */
      if (shift_const - 1 != 0) {
	rcr_ins(i_sra, lhs_reg, shift_const - 1, tmp_reg);
	rcr_ins(i_srl, tmp_reg, 32 - shift_const, tmp_reg);
      }
      else {
	rcr_ins(i_srl, lhs_reg, 32 - shift_const, tmp_reg);
      }
      rrr_ins(i_add, lhs_reg, tmp_reg, tmp_reg);
      rcr_ins(i_sra, tmp_reg, shift_const, tmp_reg);
		/* multiply */
      rcr_ins(i_sll, tmp_reg, shift_const, tmp_reg);
      /* subtract */
      rrr_ins(i_sub, lhs_reg, tmp_reg, final_reg);
      return final_reg;
    }
    rcr_ins(i_and, lhs_reg, constval - 1, final_reg);
    return final_reg;
  }

  /* otherwise need to call .rem/.urem */
  if (sgned && bro(rhs)->tag == mod_tag) {
    p = SPECIAL_REM1;
  }
  else {
    p = (sgned ? SPECIAL_REM2 : SPECIAL_UREM2);
  }
  return call_muldivrem(lhs, rhs, sp, p, 0);
}


/*
  FUNCTION TYPE
*/

typedef int(*find_fn)(exp, space, int, bool);


/*
  GENERATE CODE FOR e USING do_fn
*/

static int find_reg_and_apply
(exp e, space sp, where dest, bool sgned, find_fn do_fn) {
  ans a;
  int dest_reg;
  exp seq = son(e);
  /* tidyshort ( dest, sh ( e ) ) ; ??? */
  switch (discrim(dest.answhere)) {
    case inreg: {
      dest_reg = (*do_fn)(seq, sp, regalt(dest.answhere),
			    sgned);
      break;
    }
    case insomereg: {
      /* leave ( *do_fn ) () to allocate reg */
      int *dr = someregalt(dest.answhere);
      *dr = (*do_fn)(seq, sp, R_NO_REG, sgned);
      /* no need for move */
      return *dr;
    }
    default : {
      /* leave ( *do_fn ) () to allocate reg */
      dest_reg = (*do_fn)(seq, sp, R_NO_REG, sgned);
      break;
    }
  }
  assert(dest_reg != R_NO_REG);
  setregalt(a, dest_reg);
  sp = guardreg(dest_reg, sp);
  IGNORE move(a, dest, sp.fixed, sgned);
  return dest_reg;
}


/*
  GENERATE CODE FOR A MULTIPLICATION OPERATION
*/

int do_mul_comm_op
(exp e, space sp, where dest, bool sgned) {
  return find_reg_and_apply(e, sp, dest, sgned, do_mul_comm);
}


/*
  GENERATE CODE FOR A DIVISION OPERATION
*/

int do_div_op
(exp e, space sp, where dest, bool sgned) {
/*    other_div = ( bool ) ( ( e->tag == div1_tag && sgned ) ? 1 : 0 ) ;*/
  return find_reg_and_apply(e, sp, dest, sgned, do_div);
}


/*
  GENERATE CODE FOR A REMAINDER OPERATION
*/

int do_rem_op
(exp e, space sp, where dest, bool sgned) {
/*    other_div = ( bool ) ( ( e->tag == mod_tag && sgned ) ? 1 : 0 ) ;*/
  return find_reg_and_apply(e, sp, dest, sgned, do_rem);
}


/*
  IS AN EXPRESSION IMPLEMENTED BY A SYSTEM CALL?
  Multiplications, divisions and remainders, except in simple cases,
  are implemented by means of system calls.  This routine checks if
  an expression represents one of these calls.
*/

bool is_muldivrem_call
(exp e) {
  switch (e->tag) {

    case test_tag:
    case chfl_tag:
    case round_tag:
     if ((has & HAS_LONG_DOUBLE)) {
      exp s = son(e);
      if (sh(s)->tag == doublehd) return 1;
      /* FALL THROUGH */
     }
    case fplus_tag:
    case fminus_tag:
    case fmult_tag:
    case fdiv_tag:
    case fneg_tag:
    case fabs_tag:
    case float_tag:
     if ((has & HAS_LONG_DOUBLE)) {
      if (sh(e)->tag == doublehd) return 1;
      return 0;
     }
     return 0;

    case mult_tag:
    case offset_mult_tag: {
      /*multneeds - simple cases don't need a call */
      exp arg2 = bro(son(e));
      if (last(arg2) && arg2->tag == val_tag && optop(e)) {
	return 0;
      }
      return 1;
    }
    case div0_tag:
    case rem0_tag:
    case div1_tag:
    case mod_tag:
    case div2_tag:
    case rem2_tag:
    case offset_div_tag:
    case offset_div_by_int_tag: {
      /*remneeds, divneeds - simple cases don't need a call */
      exp arg2 = bro(son(e));
      if (last(arg2) && arg2->tag == val_tag && optop(e)) {
	long constval = no(arg2);
	if (constval > 0 && IS_POW2(constval))
	  return 0;
      }
      return 1;
    }
    case movecont_tag:
    return 1;			/* at present */
    default: {
      return 0;
    }
  }
}


/*
  ESTIMATE NEEDS FOR MULTIPLICATION
*/

needs multneeds
(exp * e, exp ** at) {
  needs n;
  exp arg1 = son(*e);
  exp arg2 = bro(arg1);
  n = likeplus(e, at);

  /* remember that mult may have more than two args after
     optimisation */
  if (last(arg2) && arg2->tag == val_tag && optop(*e)) {
    /* const optim, additional reg only needed where src and dest are
       same reg, in which case it has already been allowed for */
    return n;
  }
  /* default, call .mul */
  n.fixneeds = maxfix;
  pnset(n, hasproccall);
  return n;
}


/*
  ESTIMATE NEEDS FOR DIVISION
*/
needs divneeds
(exp * e, exp ** at) {
  needs n;
  exp lhs = son(*e);
  exp rhs = bro(lhs);

  assert ( last ( rhs ) ) ;	/* after likediv may not be so */

  n = likediv(e, at);
  if (rhs->tag == val_tag && optop(*e)) {
    long constval = no(rhs);
    if (constval > 0 && IS_POW2(constval)) {
      /* const optim, replace div by shift */
      return n;
    }
  }
  /* default, call .div */
  n.fixneeds = maxfix;
  pnset(n, hasproccall);
  return n;
}


/*
  ESTIMATE NEEDS FOR REMAINDER
*/
needs remneeds
(exp * e, exp ** at) {
  needs n;
  exp lhs = son(*e);
  exp rhs = bro(lhs);
  assert ( last ( rhs ) ) ;	/* after likediv may not be so */
  n = likediv(e, at);
  if (rhs->tag == val_tag && optop(*e)) {
    long constval = no(rhs);
    if (constval > 0 && IS_POW2(constval)) {
      /* const optim of rem by positive, non-zero, 2**n */
      return n;
    }
  }
  /* default, call .rem */
  n.fixneeds = maxfix;
  pnset(n, hasproccall);
  return n;
}
