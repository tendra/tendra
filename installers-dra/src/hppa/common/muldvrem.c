/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/check.h>

#include "config.h"

#include <construct/tags.h>
#include <construct/installtypes.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>

#include "exptypes.h"
#include "needscan.h"
#include "addrtypes.h"
#include "expmacs.h"
#include "exptypes.h"
#include "maxminmacs.h"
#include "proctypes.h"
#include "eval.h"
#include "move.h"
#include "oprators.h"
#include "comment.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "codehere.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "special.h"
#include "regmacs.h"
#include "needscan.h"
#include "translat.h"
#include "muldvrem.h"
#include "proc.h"
#include "out.h"


#define BITS_PER_WORD		32

#define MAX_MUL_POW2_OFFSET	2	/* max permissable X in 2**n +- X for
					 * constant multiply */

#define NOT_MUL_CONST_SIMPLE	(MAX_MUL_POW2_OFFSET+1)
 /* any constant larger than permissable X offset in 2**n +- X */

extern long trap_label(exp);
extern void comib_ins(ins_p,int,int,int);
/*
 * Utility functions.
 */

/* return bit number 0..31 from right of word of 'c' which has one bit set */
static int bit_no
(unsigned long c)
{
  int shift_const;
  unsigned long mask;

  assert(IS_POW2(c));

  for (mask = 1, shift_const = 0; mask != c; mask = mask << 1)
  {
    shift_const++;
  }

  return shift_const;
}


void clear_t_regs
(void)
{
  /* clear t-regs, i.e. GR2,GR19,GR20..,GR31, which might be modified by a
     call */
  int r;
  clear_reg(GR2);
  for (r = GR19; r < GR31+1; r++)
  {
     clear_reg(r);
  }
}


/* call millicode library procedure for complicated operation */
int call_muldivrem
(exp lhs, exp rhs, space sp, int proc)
{
    char *stub="ARGW0=GR ARGW1=GR";
    reg_operand_here(lhs, sp, ARG0);
    sp = needreg(ARG0, sp);

    reg_operand_here(rhs,sp,ARG1);
    sp = needreg(ARG1,sp);
    call_millicode(proc,RP,stub,1);

    clear_t_regs();

    /* result left in RET1 */
    return RET1;
}


/*
 * Multiply.
 */


/* generate code for multiply by constant */
static void mul_const_complex
(int src, long constval, int dest, space sp, bool sgned)
{
  struct
  {
    unsigned char bsl;		/* bit-string of 1s length */
    unsigned char shift;	/* shift from right of word */
  }      bs_tab[BITS_PER_WORD / 2];

  int bs_tab_len = 0;
  int bsl_1_tab = -1;
  int max_bsl = 0;

  comment1("multiply by %ld", constval);


  /* special case ~0 (all 1) which cannot be handled by the general algorithm */
  if (constval == ~0)
  {
    if (sgned)
    {
       assert(constval == -1);
       /* X * -1 => -X */
       rrr_ins(i_sub,c_,0,src,dest);
    }
    else
    {

      /*
       * only 2 non overflowing cases to consider 0 * ~0 == 0 1 * ~0 == ~0 ==
       * -1
       *
       * negate handles these two correctly
       */
      rrr_ins(i_sub,c_,0,src,dest);
    }
    return;
  }


  /* set up bs_tab from constval */
  {
    unsigned long c = constval;
    int bsl = 0;
    int shift;

    for (c = constval, shift = 0; shift <= BITS_PER_WORD; shift++, c >>= 1)
    {
      if (c & 1)
      {
	bsl++;
      }
      else if (bsl != 0)
      {
	/* a complete all-1s bit-string */
	assert(bs_tab_len < BITS_PER_WORD / 2);
	bs_tab[bs_tab_len].bsl = bsl;
	bs_tab[bs_tab_len].shift = shift - bsl;	/* .shift is from right */
	if (bsl == 1)
	  bsl_1_tab = bs_tab_len;
	if (bsl > max_bsl)
	  max_bsl = bsl;
	comment4("mul_const_complex: bs_tab[%d] =%d,%d c=%d", bs_tab_len, bs_tab[bs_tab_len].bsl, bs_tab[bs_tab_len].shift, c);
	bs_tab_len++;
	bsl = 0;
      }
    }
  }

  comment2("mul_const_complex: max_bsl=%d bsl_1_tab=%d", max_bsl, bsl_1_tab);

  assert(bs_tab_len > 0);	/* shouldn't be here otherwise */
  assert(max_bsl >= 1);
  assert(max_bsl <= 31);	/* shifts by 32 don't work */

  /* generate the code */
  {
    int bsl;
    int bsl_laststep_tab;
    int tmp = GR1;
    int accum;
    bool accum_init = 0;	/* set to 1 when 'accum' reg initialised */


    /* allocate regs */
    assert(src != GR1);
    assert(dest != GR1);

    if (src != dest)
      accum = dest;
    else
      accum = getreg(sp.fixed);

    assert(src != accum);


    /* +++ neg */

    /* init accum if useful */
    if (bsl_1_tab >= 0 && bs_tab[bsl_1_tab].shift != 0)
    {

      /*
       * Usefully do one of the 1 bit strings with simple shift to accum. If
       * left to general algorithm 2 instructions, shift and move/add, would
       * often be used.
       */
      assert(bs_tab[bsl_1_tab].bsl == 1);
      rrir_ins(i_shd,c_,src,0,32-bs_tab[bsl_1_tab].shift,accum);
      bs_tab[bsl_1_tab].bsl = 0;/* mark as done */
      accum_init = 1;
    }


    /* find last cond generation step, so we can move to dest at that step */
    bsl_laststep_tab = -1;

    for (bsl = max_bsl; bsl > 0; bsl--)
    {
      int i;

      for (i = 0; i < bs_tab_len; i++)
      {
	if (bs_tab[i].bsl == bsl)
	  bsl_laststep_tab = i;
      }
    }

    assert(bsl_laststep_tab != -1);


    /*
     * accumulate handle all bit strings of same length together, so
     * 'src*((2**bsl)-1)' can be shared
     */
    for (bsl = max_bsl; bsl > 0; bsl--)
    {
      bool found_bsl = 0;
      int tmp_shifted=0;
      int i;

      for (i = 0; i < bs_tab_len; i++)
      {
	if (bs_tab[i].bsl == bsl)
	{
	  int to_accum_reg;	/* reg to be added to 'accum' at end of step */
	  int step_accum_dest = (i == bsl_laststep_tab ? dest : accum);

	  assert(accum != R_NO_REG);

	  /* amount to accum into tmp reg */
	  if (bsl == 1)
	  {
	    /* accumulate src<<shift */
	    if (bs_tab[i].shift == 0)
	    {
	       /* simple add */
	       to_accum_reg = src;
	       if (accum_init)
		  rrr_ins(i_add,c_,accum,to_accum_reg,step_accum_dest);
	       else
	       {
		  rr_ins(i_copy,to_accum_reg,step_accum_dest);
		  accum_init = 1;
	       }
	    }
	    else
	    {
	       /* simple shift and add */
	       to_accum_reg = tmp;
 	       if (accum_init)
	       {
		  if (bs_tab[i].shift==1)
		     rrr_ins(i_sh1add,c_,src,accum,step_accum_dest);
		  else if (bs_tab[i].shift==2)
		     rrr_ins(i_sh2add,c_,src,accum,step_accum_dest);
		  else if (bs_tab[i].shift==3)
		     rrr_ins(i_sh3add,c_,src,accum,step_accum_dest);
		  else
		  {
		     rrir_ins(i_shd,c_,src,0,32-bs_tab[i].shift,tmp);
		     rrr_ins(i_add,c_,accum,to_accum_reg,step_accum_dest);
		  }
	       }
	       else
	       {
		  rrir_ins(i_shd,c_,src,0,32-bs_tab[i].shift,step_accum_dest);
		  accum_init = 1;
	       }
	    }
	  }
	  else
	  {			/* bsl != 1 */
	    /* accumulate (src*((2**bsl)-1))<<shift */

	    to_accum_reg = tmp;
	    if (!found_bsl)
	    {
	      if (bsl==2)
		 rrr_ins(i_sh1add,c_,src,src,tmp);
	      else
	      {
		 rrir_ins(i_shd,c_,src,0,32-bsl,tmp);
		 rrr_ins(i_sub,c_,tmp,src,tmp);
	      }
	      tmp_shifted = 0;
	      found_bsl = 1;
	    }

	    if (bs_tab[i].shift != tmp_shifted)
	    {
	      int extra_shift = bs_tab[i].shift - tmp_shifted;

	      assert(extra_shift > 0 && extra_shift <= 31);
	      rrir_ins(i_shd,c_,tmp,0,32-extra_shift,tmp);
	      tmp_shifted += extra_shift;
	    }
	    /* else tmp already shifted to correct position */

	    to_accum_reg = tmp;

	    if (accum_init)
	       rrr_ins(i_add,c_,accum,to_accum_reg,step_accum_dest);
	    else
	    {
	       rr_ins(i_copy,to_accum_reg,step_accum_dest);
	       accum_init=1;
	    }

	  }

	  if (i == bsl_laststep_tab)
	    accum = R_NO_REG;	/* error check */
	}
      }
    }

    assert(accum_init);
    assert(accum == R_NO_REG);

    /* result in dest, due to step_accum_dest above */
  }

  comment1("end multiply by %ld", constval);
}

/* is constval +ve const 2**n or 2**(n +- X) where abs(X) <= MAX_MUL_POW2_OFFSET */
static int offset_mul_const_simple
(long constval, bool sgned)
{
  int i;

  FULLCOMMENT1("offset_mul_const_simple: %ld", constval);

  if (constval < 0)
  {
    if (sgned)
      constval = -constval;
    else
      return NOT_MUL_CONST_SIMPLE;	/* very rare case */
  }

  for (i = 0; i <= MAX_MUL_POW2_OFFSET; i++)
  {
    long c;			/* power of two close to constval */

    /* check for add offsets, avoiding overflow confusion */
    c = constval - i;
    if (IS_POW2(c) && c + i == constval)
      return i;

    /* check for sub offset of 1 only, avoiding overflow confusion */
    if (i == 1)
    {
      c = constval + i;
      if (IS_POW2(c) && c - i == constval)
	return -i;
    }
  }

  return NOT_MUL_CONST_SIMPLE;
}


/* generate code for multiply by constant */
static void mul_const_simple
(int src, long constval, int dest, bool sgned)
{
  int shift_const;
  long c;			/* power of two close to constval */
  int add_sub;			/* difference from power of two: +N add, 0
				 * nop, -N sub */

  if (sgned && constval < 0)
  {
    if (constval == -1)
    {
      /* X * -1 => -X */
      rrr_ins(i_sub,c_,0,src,dest);
      return;
    }
    constval = -constval;
    rrr_ins(i_sub,c_,0,src,GR1); /* incorrect to modify source */
    src = GR1;
  }

  if (constval==1)
  {
     if (src != dest)
	rr_ins(i_copy,src,dest);
     return;
  }
  else if (constval == 2)
  {
    /* use add, which can be peep-hole optimised to addcc later */
    rrr_ins(i_add,c_,src,src,dest);
    return;
  }

  add_sub = offset_mul_const_simple(constval, sgned);
  c = constval - add_sub;

  assert(constval == c + add_sub);

  shift_const = bit_no(c);

  FULLCOMMENT3("mul_const_simple: constval=%#lx shift_const=%d add_sub=%d", constval, shift_const, add_sub);
  assert(constval == (1 << shift_const) + add_sub);

  if (add_sub == 0)
     rrir_ins(i_shd,c_,src,0,32-shift_const,dest);
  else
  {
    /* add_sub != 0 */
    ins_p i_add_sub;
    int n;			/* number of add_sub instructions */
    int inter_reg;		/* for partial result */
    int i;

    if (add_sub > 0)
    {
      i_add_sub = i_add;
      n = add_sub;
    }
    else
    {
      i_add_sub = i_sub;
      n = -add_sub;
    }

    if (src == dest)
    {
      inter_reg = GR1;	/* must preserve src for add/sub */
    }
    else
    {
      inter_reg = dest;
    }

    assert(src != inter_reg);

    rrir_ins(i_shd,c_,src,0,32-shift_const,inter_reg);

    if (i_add_sub==i_add)
    {
       i=1;
       while (i<n)
       {
	  if (i+7<n)
	  {
	     rrr_ins(i_sh3add,c_,src,inter_reg,inter_reg);
	     i+=8;
	  }
	  else if (i+3<n)
	  {
	     rrr_ins(i_sh2add,c_,src,inter_reg,inter_reg);
	     i+=4;
	  }
	  else if (i+1<n)
	  {
	     rrr_ins(i_sh1add,c_,src,inter_reg,inter_reg);
	     i+=2;
	  }
	  else
	  {
	     rrr_ins(i_add,c_,src,inter_reg,inter_reg);
	     i++;
	  }
       }
    }
    else
       for (i = 1; i < n; i++)
	   rrr_ins(i_add_sub,c_,inter_reg,src,inter_reg);

    /* final add_sub to dest reg */
    rrr_ins(i_add_sub,c_,inter_reg,src,dest);

  }
}


/* generate code for multiply by constant */
static void mul_const
(int src, long constval, int dest, space sp, bool sgned)
{
  if (constval == 0)
     /* rare case not handled by mul_const_X() */
     rr_ins(i_copy,0,dest);
  else if (offset_mul_const_simple(constval, sgned) == NOT_MUL_CONST_SIMPLE)
    mul_const_complex(src, constval, dest, sp, sgned);
  else
    mul_const_simple(src, constval, dest, sgned);
}


/*
 *   Generate code for multiply .
 */
static int do_mul_comm
(exp e, space sp, int final_reg, bool sgned)
{
  exp seq = son(e);
  exp arg2 = bro(seq);
  char *mul_proc;
  int arg = 1;
  baseoff b;
  int v;

  if (name(arg2) == val_tag)
  {
    /* const optim */
    v = reg_operand(seq, sp);
    sp = guardreg(v,sp);
    assert(last(arg2));	 /* refactor() & scan() should move const to last */
    if (final_reg == R_NO_REG)
    {
       final_reg = getreg(sp.fixed);
       sp = guardreg(final_reg, sp);
    }
    mul_const(v, no(arg2), final_reg, sp, sgned);
    return final_reg;
  }


  /* need to call .mul/.umul */

  mul_proc = (sgned ? "$$mulI" : "$$mulU");

  b=mem_temp(4);
  reg_operand_here(seq,sp,ARG0);
  st_ins(i_sw,ARG0,b);
  b=mem_temp(0);


  for (;;)
  {
    assert(!last(seq));		/* should have break out below by now */

    seq = bro(seq);
    arg++;

    FULLCOMMENT1("do_mul_comm: name(seq) = %d", name(seq));

    if (name(seq) == val_tag && offset_mul_const_simple(no(seq), sgned)!= NOT_MUL_CONST_SIMPLE)
    {
      /* const optim */
      assert(last(seq)); /* refactor() & scan() should move const to last */

      stf_ins(i_fstw,14,b);
      ld_ins(i_lw,SIGNED,b,ARG0);

      if (final_reg == R_NO_REG)
	 final_reg = RET0;
	 /* better code from mul_const if src != dest register */

      mul_const(ARG0, no(seq), final_reg, sp, sgned);

      break;
    }
    else
    {
       reg_operand_here(seq,sp,ARG0);
       if (last(seq) && b.offset<-17)
       {
	  ld_ins(i_lo,1,b,GR1);
	  b.base=GR1;
	  b.offset=0;
       }
       st_ins(i_sw,ARG0,b);
       if (arg==2)
	  ldf_ins(i_fldd,b,13);
       else
	  ldf_ins(i_fldw,b,12);
       rrrf_ins(i_xmpyu,f_,12,14,13);

       clear_t_regs();

       if (last(seq))
       {
	  stf_ins(i_fstw,14,b);
	  if (final_reg == R_NO_REG || final_reg == RET0)
	  {
	     ld_ins(i_lw,SIGNED,b,RET0);
 	     final_reg = RET0;
	  }
	  else
	     ld_ins(i_lw,SIGNED,b,final_reg);
	  break;
       }
    }
  }
  return final_reg;
}


/*
 *   Generate code for div0, div1 and div2 by calling divI or divU unless
 *   dividing by a simple constant.
 */
static int do_div
(exp e, space sp, int final_reg, bool sgned)
{
   exp seq = son(e);
   exp lhs = seq;
   exp rhs = bro(lhs);
   space nsp;
   int trap = 0;
   int sz = shape_size(sh(e));
   char *stub="ARGW0=GR ARGW1=GR";
   if (!optop(e))
      trap = trap_label(e);
   assert(last(rhs));
   /*
    *   ov_err can only occur when calculating p div1 q with p == variety's
    *   minimum and q==-1
    */
   if (name(rhs) ==val_tag)
   {
      /*   nb. div_by_zero_err handled by common code  */
      int n = no(rhs);
      if (n > 0 && IS_POW2(n))
      {
	 int lhs_reg = reg_operand(lhs, sp);
	 int shift_const = bit_no(n);
	 sp = guardreg(lhs_reg, sp);
	 if (final_reg == R_NO_REG)
	 {
	   final_reg = getreg(sp.fixed);
	 }
	 if (n==1)
	 {
	    /*
	     *   div = lhs
	     */
 	    rr_ins(i_copy,lhs_reg,final_reg);
	    return final_reg;
	 }
	 else
	 if (sgned)
	 {
	   /* signed, adjust lhs before shift */
 	   assert(shift_const > 0);/* assumed below */
	   if (n==-1 && !optop(e))
	   {
	      if (sz==8)
		 iiir_ins(i_zdepi,c_,-1,24,25,GR1);
	      else
	      if (sz==16)
		 iiir_ins(i_zdepi,c_,-1,16,17,GR1);
	      else
		 iiir_ins(i_zdepi,c_,-1,0,1,GR1);
	      cj_ins(c_eq,lhs_reg,GR1,trap);
	   }
	   if (shift_const - 1 != 0)
	   {
	      riir_ins(i_extrs,c_,lhs_reg,32-shift_const,33-shift_const,GR1);
	      rrir_ins(i_shd,c_,0,GR1,32-shift_const,GR1);
	   }
	   else
	      rrir_ins(i_shd,c_,0,lhs_reg,32-shift_const,GR1);
 	   rrr_ins(i_add,c_,lhs_reg,GR1,GR1);
	   riir_ins(i_extrs,c_,GR1,31-shift_const,32-shift_const,final_reg);
	 }
	 else
	    rrir_ins(i_shd,c_,0,lhs_reg,shift_const,final_reg);
	 return final_reg;
      }
   }

   /*  We will have to call divI or divU */

   reg_operand_here(lhs, sp, ARG0);
   nsp = guardreg(ARG0,sp);
   reg_operand_here(rhs,nsp,ARG1);


   if (!optop(e))
   {
      cj_ins(c_eq,GR0,ARG1,trap);
      if (sgned)
      {
	 comib_ins(c_neq,-1,ARG1,-16);
	 z_ins(i_nop);
	 if (sz==8)
	    iiir_ins(i_zdepi,c_,-1,24,25,GR1);
	 else
	 if (sz==16)
	    iiir_ins(i_zdepi,c_,-1,16,17,GR1);
	 else
	    iiir_ins(i_zdepi,c_,-1,0,1,GR1);
	 cj_ins(c_eq,ARG0,GR1,trap);
      }
   }

   if (name(bro(rhs)) == div1_tag && sgned)
   {
      int fin = new_label();
      baseoff b;
      b = mem_temp(0);
      rrr_ins(i_or,c_neq,0,ARG0,RET1);
      ub_ins(cmplt_N,fin);
      st_ins(i_sw,ARG0,b);
      b.offset += 4;
      st_ins(i_sw,ARG1,b);
      call_millicode(MILLI_DIVI,RP,stub,1);
      ld_ins(i_lw,1,b,ARG1);
      b.offset -= 4;
      ld_ins(i_lw,1,b,ARG0);
      rrr_ins(i_xor,c_l,ARG0,ARG1,0);
      ub_ins(cmplt_N,fin);
      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,b.offset,b.base,GR1);
      b.base = GR1; b.offset = 0;
      st_ins(i_sw,RET1,b);
      ldf_ins(i_fldd,b,13);
      rrrf_ins(i_xmpyu,f_,12,14,13);
      stf_ins(i_fstw,14,b);
      ld_ins(i_lw,1,b,ARG1);
      rrr_ins(i_comclr,c_eq,ARG0,ARG1,0);
      irr_ins(i_addi,c_,fs_,-1,RET1,RET1);
      outlab("L$$",fin);
   }
   else
   {
      call_millicode(sgned ? MILLI_DIVI : MILLI_DIVU,RP,stub,1);
   }
   clear_t_regs();
   /* result left in RET1 */
   return RET1;
}


/*
 *   Generate code for remainder using remI or remU unless  simple constant.
 */
static int do_rem
(exp e, space sp, int final_reg, bool sgned)
{
   exp seq = son(e);
   exp lhs = seq;
   exp rhs = bro(lhs);
   int p=0;
   space nsp;
   int trap = 0;
   baseoff b;
   char *stub="ARGW0=GR ARGW1=GR";
   assert(last(rhs));
   b = mem_temp(0);
   if (!optop(e))
      trap = trap_label(e);
   if (name(rhs) == val_tag)
   {
      int n = no(rhs);
      if (n==0)
      {
	 if (!optop(e))
	    ub_ins(cmplt_N,trap);
	 return GR0;
      }
      else
      if (IS_POW2(n))
      {
	 int lhs_reg = reg_operand(lhs, sp);
	 sp = guardreg(lhs_reg, sp);
	 if (final_reg == R_NO_REG)
	 {
	    final_reg = getreg(sp.fixed);
	 }
	 if (n == 1)
	 {
	    /*
	     *   rem = 0
	     */
 	    rr_ins(i_copy,0,final_reg);
	    return final_reg;
	 }
	 while (((1<< (++p)) & n) ==0);
	 if (sgned && name(bro(rhs)) == rem2_tag)
	 {
	    /*
	     *   Allow for negative lhs. Calculate lhs % n ( = 2**p ) by
	     *   anding lhs with mask, negating lhs before and after anding
	     *   if lhs<0.
	     */
	    if (lhs_reg==final_reg)
	    {
	       rrr_ins(i_or,c_g,0,lhs_reg,GR1);
	       rrr_ins(i_sub,c_,0,lhs_reg,lhs_reg);
	       riir_ins(i_dep,c_,0,31-p,32-p,lhs_reg);
	       rrr_ins(i_or,c_g,0,GR1,0);
	       rrr_ins(i_sub,c_,0,lhs_reg,lhs_reg);
	    }
	    else
	    {
	       rrr_ins(i_or,c_g,0,lhs_reg,final_reg);
	       rrr_ins(i_sub,c_,0,final_reg,final_reg);
	       riir_ins(i_dep,c_,0,31-p,32-p,final_reg);
	       rrr_ins(i_or,c_g,0,lhs_reg,0);
	       rrr_ins(i_sub,c_,0,final_reg,final_reg);
	    }
	 }
	 else
	 {
	    /*
	     *   Calculate lhs % n ( = 2**p ) by anding with mask.
	     */
	    if (lhs_reg==final_reg)
	       riir_ins(i_dep,c_,0,31-p,32-p,final_reg);
	    else
	       riir_ins(i_zdep,c_,lhs_reg,31,p,final_reg);
	 }
	 return final_reg;
      }
      else
      {
	 /*
	  *   Need to call remI or remU.
	  */
	 reg_operand_here(lhs,sp,ARG0);
	 imm_to_r(n,ARG1);
	 if (sgned)
	 {
	    call_millicode(MILLI_REMI,RP,stub,1);
	    if (name(bro(rhs)) == mod_tag)
	    {
	       if (SIMM14(n))
	       {
		  if (n>0)
		     rrr_ins(i_comclr,c_geq,RET1,0,0);
		  else
		  if (n<0)
		     rrr_ins(i_comclr,c_leq,RET1,0,0);
		  ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,n,RET1,RET1);
	       }
	       else
	       {
		  imm_to_r(n,ARG1);
		  if (n>0)
		     rrr_ins(i_comclr,c_geq,RET1,0,0);
		  else
		  if (n<0)
		     rrr_ins(i_comclr,c_leq,RET1,0,0);
		  rrr_ins(i_add,c_,ARG1,RET1,RET1);
	       }
	    }
	 }
	 else
	 {
	    call_millicode(MILLI_REMU,RP,stub,1);
	 }
	 clear_t_regs();
	 return RET1;  /* result left in RET1 */
      }
   }
   /*
    *   Need to call remI/.urem
    */
   reg_operand_here(lhs, sp, ARG0);
   nsp = guardreg(ARG0, sp);
   reg_operand_here(rhs, nsp, ARG1);
   if (!optop(e))
      cj_ins(c_eq,GR0,ARG1,trap);

   if (name(bro(rhs)) == mod_tag && sgned)
   {
      st_ins(i_sw,ARG1,b);
      call_millicode(MILLI_REMI,RP,stub,1);
      rrr_ins(i_comclr,c_eq,RET1,0,ARG1);
      ld_ins(i_lw,1,b,ARG1);
      rrr_ins(i_xor,c_geq,RET1,ARG1,0);
      rrr_ins(i_add,c_,RET1,ARG1,RET1);
   }
   else
   {
      call_millicode(sgned ? MILLI_REMI : MILLI_REMU, RP, stub,1);
   }
   clear_t_regs();
   return RET1;  /* result left in RET1 */
}


typedef int(*find_fn)(exp, space, int, bool);

/* choose regs and generate code using do_fn */
static int find_reg_and_apply
(exp e, space sp, where dest, bool sgned, find_fn do_fn)
{
  ans a;
  int dest_reg;

  /* +++ mips has tidyshort(dest, sh(e)); check not needed on HPPA */

  switch (discrim(dest.answhere))
  {
  case inreg:
    dest_reg = (*do_fn)(e, sp, regalt(dest.answhere), sgned);
    break;

  case insomereg:
    {
      int *dr = someregalt(dest.answhere);

      *dr = (*do_fn) (e, sp, R_NO_REG, sgned);	/* leave (*do_fn)() to
							 * allocate reg */
      return *dr;		/* no need for move */
    }

  default:
    dest_reg = (*do_fn) (e, sp, R_NO_REG, sgned);	/* leave (*do_fn)() to
							 * allocate reg */
  }

  assert(dest_reg != R_NO_REG);

  setregalt(a, dest_reg);
  sp = guardreg(dest_reg, sp);
  move(a, dest, sp.fixed, sgned);

  return dest_reg;
}



/* choose regs and generate code for multiply using multiply proc */
int do_mul_comm_op
(exp e, space sp, where dest, bool sgned)
{
   return find_reg_and_apply(e, sp, dest, sgned, do_mul_comm);
}


/* choose regs and generate code for divide using divide proc */
int do_div_op
(exp e, space sp, where dest, bool sgned)
{
  return find_reg_and_apply(e, sp, dest, sgned, do_div);
}


/* choose regs and generate code for rem using rem proc */
int do_rem_op
(exp e, space sp, where dest, bool sgned)
{
  return find_reg_and_apply(e, sp, dest, sgned, do_rem);
}



/* is exp mul, div or rem that may call */
bool is_muldivrem_call
(exp e)
{

  switch (name(e))
  {
     case test_tag:
     case chfl_tag:
     case round_tag:
       if (use_long_double) {
	 exp s = son(e);
	 if (name(sh(s)) ==doublehd)
	    return 1;
	 /* FALL THROUGH */
       }

     case fplus_tag:
     case fminus_tag:
     case fmult_tag:
     case fdiv_tag:
     case fneg_tag:
     case fabs_tag:
     case float_tag:
       if (use_long_double) {
	if (name(sh(e)) ==doublehd)
	   return 1;
	else
	   return 0;
       }
      return 0;

#if 0
   case chvar_tag:
     e = son(e);		/* fall through, look at arg */
#endif
      case mult_tag:
      case offset_mult_tag:
      {
	/*multneeds - simple cases don't need a call */
	exp arg2 = bro(son(e));
	if (last(arg2) && name(arg2) == val_tag)
	{
	  return 0;
	}
	return 1;
      }

    case div0_tag:
    case rem0_tag:
    case div1_tag:
    case div2_tag:
    case mod_tag:
    case rem2_tag:
    case offset_div_tag:
    case offset_div_by_int_tag:
      {
	/*remneeds, divneeds - simple cases don't need a call */
	exp arg2 = bro(son(e));

	if (last(arg2) && name(arg2) == val_tag)
	{
	  long constval = no(arg2);
	  if (constval > 0 && IS_POW2(constval))
	  {
	    return 0;
	  }
	}
	return 1;
      }
  default:
      return 0;
    }
}


/*
 * Needs estimation
 */


needs multneeds
(exp * e, exp ** at)
{
  needs n;
  exp arg1 = son(*(e));
  exp arg2 = bro(arg1);
  n = likeplus(e, at);	/* has had comm_ass() treatment */

  /* remember that mult may have more than two args after optimisation */

  if (last(arg2) && name(arg2) == val_tag)
  {

    /*
     * const optim, additional reg only needed where src and dest are same
     * reg, in which case it has already been allowed for.
     */
    return n;
  }

  /* default, call .mul */
  n.fixneeds = maxfix;
#if 1
  n.propsneeds |= hasproccall;
#endif
  return n;
}


needs divneeds
(exp * e, exp ** at)
{
  needs n;
  exp lhs = son(*(e));
  exp rhs = bro(lhs);
  n = likediv(e, at);

  assert(last(rhs));

  if (name(rhs) == val_tag)
  {
    long constval = no(rhs);

    if (constval > 0 && IS_POW2(constval))
    {
      /* const optim, replace div by positive, non-zero, 2**n by shift right */

      return n;
    }
  }

  /* default, call .div */
  n.fixneeds = maxfix;
  n.propsneeds |= hasproccall;

  return n;
}


needs remneeds
(exp * e, exp ** at)
{
  needs n;
  exp lhs = son(*(e));
  exp rhs = bro(lhs);
  n = likediv(e, at);

  assert(last(rhs));
  if (name(rhs) == val_tag)
  {
    long constval = no(rhs);

    if (constval > 0 && IS_POW2(constval))
    {
      /* const optim of rem by positive, non-zero, 2**n */

      return n;
    }
  }
  /* default, call .rem */
  n.fixneeds = maxfix;
  n.propsneeds |= hasproccall;
  return n;
}








