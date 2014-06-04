/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/fbase.h>

#include <main/driver.h>

#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/flpt.h>
#include <construct/flpttypes.h>
#include <construct/shape.h>
#include <construct/tags.h>

#include "assembler.h"
#include "mach.h"
#include "mach_ins.h"
#include "where.h"
#include "mach_op.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "coder.h"
#include "tests.h"
#include "operations.h"
#include "evaluate.h"
#include "utility.h"
#include "translate.h"
#include "ops_shared.h"

/*
    GIVE PROTOTYPE FOR MFW
*/

#if (FBASE == 10)
extern where mfw(int, char *, int);
#define FBASE_10
#else
extern where mfw(int, long *, int);
#undef FBASE_10
#endif

extern int need_dummy_double;

/*
 * Test for overflow.
 *
 * freg is a Freg which is moved to a dummy memory location to force the
 * overflow (if any) before the test.
 */
void test_float_overflow_reg
(where freg, long sz)
{
   if (have_overflow()) {
      ins2(insf(sz, ml_fmove), sz, sz, freg, dummy_double_dest, 1);
      test_overflow(ON_FP_OVERFLOW);
      need_dummy_double = 1;
   }
}

/*
 * Test for overflow.
 *
 * If dest is zero, freg is moved to a memory location to force the
 * overflow (if any) before the test.
 */
void test_float_overflow
(where freg, where dest, long sz)
{
   if (have_overflow()) {
      if (eq_where(dest, zero)) {
         ins2(insf(sz, ml_fmove), sz, sz, freg, dummy_double_dest, 1);
         need_dummy_double = 1;
      }
      test_overflow(ON_FP_OVERFLOW);
   }
}

/*
 * GENERAL PURPOSE FLOATING POINT ROUTINE
 *
 * The values a1 and a2 of shape sha have the binary floating-point
 * operation indicated by the tag t applied to them and the result is
 * stored in dest.
 */
void fl_binop
(int t, shape sha, where a1, where a2, where dest)
{
    int op, op1, op2;
    bool commutes = 0;
    long sz = shape_size(sha);

    switch (t) {
	case fplus_tag: {
	    commutes = 1;
	    op1 = insf(sz, ml_fadd);
	    op2 = m_faddx;
	    break;
	}
	case fminus_tag: {
	    op1 = insf(sz, ml_fsub);
	    op2 = m_fsubx;
	    break;
	}
	case fmult_tag: {
	    commutes = 1;
	    op1 = insf(sz, ml_fmul);
	    op2 = m_fmulx;
	    break;
	}
	case fdiv_tag: {
	    op1 = insf(sz, ml_fdiv);
	    op2 = m_fdivx;
	    break;
	}
	default : {
	    error(ERROR_SERIOUS, "Illegal floating operation");
	    return;
	}
    }

    if (whereis(dest) == Freg) {
       if (eq_where(a1, dest)) {
          if (commutes) {
             op = (whereis(a2) == Freg ? op2 : op1);
             ins2(op, sz, sz, a2, dest, 1);
             if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
             test_float_overflow_reg(dest, sz);
          }
          else {
             move(sha, a2, FP0);
             ins2(op2, sz, sz, a1, FP0, 1);
             if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
             move(sha, FP0, dest);
          }
       } else {
          move(sha, a2, dest);
          op = (whereis(a1) == Freg ? op2 : op1);
          ins2(op, sz, sz, a1, dest, 1);
          if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
          test_float_overflow_reg(dest, sz);
       }
    }
    else {
       move(sha, a2, FP0);
       op = (whereis(a1) == Freg ? op2 : op1);
       ins2(op, sz, sz, a1, FP0, 1);
       if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
       move(sha, FP0, dest);
       test_float_overflow(FP0, dest, sz);
    }
    have_cond = 0;
    return;
}

/*
 * NEGATE A FLOATING-POINT NUMBER
 *
 * The floating-point value a of shape sha is negated and stored in dest.
 */
void negate_float
(shape sha, where a, where dest)
{
   if (whereis(a) == Freg) {
      if (whereis(dest) == Freg) {
         ins2(m_fnegx, 64L, 64L, a, dest, 1);
         test_float_overflow_reg(dest, 64L);
      } else {
         negate_float(sha, a, FP0);
         move(sha, FP0, dest);
      }
   }
   else {
      move(sha, a, FP0);
      negate_float(sha, FP0, FP0);
      move(sha, FP0, dest);
      test_float_overflow(FP0, dest, shape_size(sha));
   }
   have_cond = 0;
}

/*
 * FIND THE ABSOLUTE VALUE OF A FLOATING-POINT NUMBER
 *
 * The floating-point value a of shape sha is has its absolute value
 * stored in dest.
 */
void abs_float
(shape sha, where a, where dest)
{
    if (whereis(a) == Freg) {
	if (whereis(dest) == Freg) {
	    ins2(m_fabsx, 64L, 64L, a, dest, 1);
            test_float_overflow_reg(dest, 64L);
	} else {
	    abs_float(sha, a, FP0);
	    move(sha, FP0, dest);
	}
    } else {
	move(sha, a, FP0);
	abs_float(sha, FP0, FP0);
	move(sha, FP0, dest);
    }
    have_cond = 0;
}

/*
 * CHANGE FLOATING VARIETY
 *
 * The floating-point value from is converted to a value of shape sha
 * and stored in to.
 */
void change_flvar
(shape sha, where from, where to)
{
    shape shf = sh(from.wh_exp);
    if (whereis(to) == Freg) {
	if (whereis(from) == Freg) {
	    move(realsh, from, to);
	    return;
	}
	if (shape_size(shf) > shape_size(sha)) {
	    move(shf, from, to);
	    move(sha, to, D0);
	    move(sha, D0, to);
	    return;
	}
	move(shf, from, to);
	return;
    }
    if (whereis(from) == Freg) {
	move(sha, from, to);
        test_float_overflow_reg(to, shape_size(sha));
	return;
    }
    move(shf, from, FP0);
    move(sha, FP0, to);
    test_float_overflow(FP0, to, shape_size(sha));
}

/*
 * The current rounding mode for round_float.
 */
int crt_rmode = R2NEAR;

/*
 * Make floating point representing range_min(sha) - adjustment
 * Where Adjustment(adj) is 0,1,0.5 when adj is 0,1,2
 */
where get_min_limit
(shape sha, int adj)
{
   long fmd[4], min;

   if (name(sha) ==ulonghd) {
      switch (adj) {
      case 0:
         /* res = 0 */
         fmd[0] = 0;
         fmd[1] = -1;
         return mfw(0,fmd,0);
      case 1:
         /* res = -1 */
         fmd[0] = 1;
         fmd[1] = -1;
         return mfw(-1,fmd,1);
      case 2:
         /* res = - 0.5 */
         fmd[0] = 0x8000;
         fmd[1] = -1;
         return mfw(-1,fmd,-1);
      }
   }
   if (name(sha) ==slonghd) {
      switch (adj) {
      case 0:
         break;
      case 1:
         /* res = - 2**31 - 1 */
         fmd[0] = 0x8000;
         fmd[1] = 0x0001;
         fmd[2] = -1;
         return mfw(-1,fmd,1);

      case 2:
         /* res = - 2**31 - 0.5 */
         fmd[0] = 0x8000;
         fmd[1] = 0x0000;
         fmd[2] = 0x8000;
         fmd[3] = -1;
         return mfw(-1,fmd,-1);
      }
   }

   min = range_min(sha);
   switch (adj) {
   case 0:
   case 1:
      /* min - (0|1) */
      min -= adj;
      fmd[0] = (min>>16) & 0xffff;
      fmd[1] = min & 0xffff;
      fmd[2] = -1;
      return mfw((is_signed(sha) ||adj)? -1 : 0,fmd,1);
   case 2:
      /* min - 0.5 */
      min -= 1;
      fmd[0] = (min>>16) & 0xffff;
      fmd[1] = min & 0xffff;
      fmd[2] = 0x8000;
      fmd[3] = -1;
      return mfw(-1,fmd,-1);
   }

   /* Shouldn't happen */
   fmd[0] = 0;
   fmd[1] = -1;
   return mfw(0,fmd,0);
}

/*
 * Make floating point representing range_max(sha) + adjustment
 * Where Adjustment(adj) is 0,1,0.5 when adj is 0,1,2
 */
where get_max_limit
(shape sha, int adj)
{
   long fmd[6];
   long max = range_max(sha);
   if (name(sha) ==ulonghd) {
      switch (adj) {
      case 0:
         /* max */
         fmd[0] = 0xffff;
         fmd[1] = 0xffff;
         fmd[2] = -1;
         return mfw(1,fmd,1);
      case 1:
         /* max + 1 */
         fmd[0] = 1;
         fmd[1] = 0;
         fmd[2] = 0;
         fmd[3] = -1;
         return mfw(1,fmd,2);
      case 2:
         /* max + 0.5 */
         fmd[0] = 1;
         fmd[1] = 0;
         fmd[2] = 0;
         fmd[3] = 0;
         fmd[4] = 0x8000;
         fmd[5] = -1;
         return mfw(1,fmd,-1);
      }
   }
   else {
      switch (adj) {
      case 0:
      case 1:
         /* max + (0|1) */
         max += adj;
         fmd[0] = (max>>16) & 0xffff;
         fmd[1] = max & 0xffff;
         fmd[2] = -1;
         return mfw(1,fmd,1);
      case 2:
         /* max + 0.5 */
         fmd[0] = (max>>16) & 0xffff;
         fmd[1] = max & 0xffff;
         fmd[2] = 0x8000;
         fmd[3] = -1;
         return mfw(1,fmd,-1);
      }
   }

   /* Shouldn't happen */
   fmd[0] = 0xffff;
   fmd[1] = 0xffff;
   fmd[2] = -1;
   return mfw(1,fmd,1);
}

/* Test number against limit */
void check_limit
(where number, where limit, int tst)
{
   int sw, instr;
   move(realsh,limit,FP1);
   sw = cmp(realsh,number,FP1,tst);
   instr = branch_ins(tst,sw,1,1);
   test_overflow2(instr);
}

/*
 * Check that the floating point value in 'from' will, when rounded, fall
 * within the range of the integer variety given by 'sha'.
 */
static void check_float_round_overflow
(shape sha, where from, int mode)
{
  if (overflow_jump == -1) {
     make_comment("error_teatment is trap");
     return;
  }

  make_comment("check_float_round_overflow ...");

  /* Setup min and max limits & decide tests */
  switch (mode) {
  case R2PINF:
     make_comment(" (toward larger) min-1 < x <= max");
     /* error if x <= min-1 or x > max */
     check_limit(from, get_min_limit(sha,1),tst_le);
     check_limit(from, get_max_limit(sha,0),tst_gr);
     break;
  case R2NINF:
     make_comment(" (toward smaller) min <= x < max+1");
     /* error if x < min or x >= max+1 */
     check_limit(from, get_min_limit(sha,0),tst_ls);
     check_limit(from, get_max_limit(sha,1),tst_ge);
     break;
  case R2ZERO:
     make_comment(" (toward zero) min-1 < x < max+1");
     /* error if x <= min-1 or x >= max+1 */
     check_limit(from, get_min_limit(sha,1),tst_le);
     check_limit(from, get_max_limit(sha,1),tst_ge);
     break;
  case R2NEAR:
     make_comment(" (to nearest) min-0.5 <= x < max+0.5");
     /* error if x < min-0.5 or x >= max+0.5 */
     check_limit(from, get_min_limit(sha,2),tst_le);
     check_limit(from, get_max_limit(sha,2),tst_gr);
     break;
  case 4:
     make_comment(" (internal mode) min <= x <= max");
     /* error if x < min or x > max */
     check_limit(from, get_min_limit(sha,0),tst_ls);
     check_limit(from, get_max_limit(sha,0),tst_gr);
     break;
  default:
     error(ERROR_SERIOUS, "check_float_round_overflow: wrong rounding mode");
  }

  make_comment("check_float_round_overflow done");
}

bool changed_round_mode = 0;

/*
 * SET_ROUND_MODE
 *
 * Changes the default floating point rounding mode.
 * Set bits 4 & 5 of fpcr (floating point control register)
 * according to rounding mode.
 *
 * The global flag changed_round_mode is set to TRUE.
 */
void set_round_mode
(int mode)
{
/*
   if (mode == f_to_nearest && ! changed_round_mode ) return ;
*/
   changed_round_mode = 1;

   ins2(m_fmovel,32,32,RW[REG_FPCR],D0,1);

   switch (mode) {
   case R2NEAR:
      make_comment("round mode to nearest");
      /* to nearest => bit 4 = 0, bit 5 = 0 */
      ins2n(m_bclr,4,32,D0,1);
      ins2n(m_bclr,5,32,D0,1);
      break;
   case R2PINF:
      make_comment("round mode to larger");
      /* to + INF  => bit 4 =1, bit5 = 1 */
      ins2n(m_bset,4,32,D0,1);
      ins2n(m_bset,5,32,D0,1);
      break;
   case R2NINF:
      make_comment("round mode to smaller");
      /* to - INF => bit 4 = 0, bit 5 = 1 */
      ins2n(m_bclr,4,32,D0,1);
      ins2n(m_bset,5,32,D0,1);
      break;
   case R2ZERO:
      make_comment("round mode to zero");
      /* to zero => bit 4 = 1, bit 5 = 0
         This should never occur, as fintrz is always used
         for round to zero */
      ins2n(m_bset,4,32,D0,1);
      ins2n(m_bclr,5,32,D0,1);
      break;
   default:
      error(ERROR_SERIOUS, "wrong rounding mode");
   }
   ins2(m_fmovel,32,32,D0,RW[REG_FPCR],1);
}

void reset_round_mode
(void)
{
   if (changed_round_mode) {
      set_round_mode(f_to_nearest);
      changed_round_mode = 0;
   }
}

static void
float_to_unsigned(where from, where to, char *s)
{
	change_flvar(realsh, from, FP0);
	push_float(64L, FP0);
	change_flvar(realsh, from, FP0);
	push_float(64L, FP0);
#ifdef float_to_unsigned_uses_fp1
	if (mode == 4 && eq_where(from, FP1) {
		push_float(64L, FP1);
		libcall(s);
		pop_float(64L, FP1);
	} else
#endif
		libcall(s);
	dec_stack(-64);
	have_cond = 0;
	move(ulongsh, D0, to);
}

/*
 * ROUND A FLOATING POINT NUMBER TO AN INTEGER
 *
 * The floating-point value from is rounded to an integer value of shape
 * sha and stored in to.  The rounding mode is given by crt_rmode.
 */
void round_float
(shape sha, where from, where to)
{
    where fr;
    where dest;
    int mode = crt_rmode;

    if (name(sha) == ulonghd) {
        if (have_overflow()) {
            /*
             * This must be checked before a round operation is attempted
             * because out-of-range values can cause an exception
             */
            check_float_round_overflow(sha,from,mode);
        }

	if (mode == f_toward_zero|| mode == 4) {
		switch (abi) {
		case ABI_SUNOS: {
	   		where fm;
	    		long lab1 = next_lab();
	    		long lab2 = next_lab();
	    		exp jt = simple_exp(0);
	    		ptno(jt) = lab1;
	    		regsinproc |= regmsk(REG_FP1);
#ifdef FBASE_10
	    		fm = mfw(1, "2147483648", 9);
#else
	    		{
				static long fmd[] = { 32768, 0, -1 };
				fm = mfw(1, fmd, 1);
	    		}
#endif

			change_flvar(realsh, from, FP0);
			move(realsh, fm, FP1);
			regsinproc |= regmsk(REG_FP1);
			ins2_cmp(m_fcmpx, 64L, 64L, FP0, FP1, 0);
			branch(tst_gr, jt, 1, 1, 1);
			ins2(m_fsubx, 64L, 64L, FP1, FP0, regmsk(REG_FP0));

			if (whereis(to) == Dreg) {
				ins2(m_fintrzx,32L,32L,FP0,FP0,1);
				ins2(m_fmovel, 32L, 32L, FP0, to, 1);
				or(ulongsh, to, mnw((long)2147483648UL), to);
			} else {
				ins2(m_fintrzx,32L,32L,FP0,FP0,1);
				ins2(m_fmovel, 32L, 32L, FP0, D0, 1);
				or(ulongsh, D0, mnw((long)2147483648UL), D0);
				move(ulongsh, D0, to);
			}

			make_jump(m_bra, lab2);
			make_label(lab1);

			if (whereis(to) == Dreg) {
				ins2(m_fintrzx,32L,32L,FP0,FP0,1);
				ins2(m_fmovel, 32L, 32L, FP0, to, 1);
			} else {
				ins2(m_fintrzx,32L,32L,FP0,FP0,1);
				ins2(m_fmovel, 32L, 32L, FP0, D0, 1);
				move(ulongsh, D0, to);
			}
			make_label(lab2);
			have_cond = 0;
			break;
		}

		case ABI_HPUX:
			float_to_unsigned(from, to, "___fixu");
			break;

		case ABI_NEXT:
			float_to_unsigned(from, to, "__fixunsdfsi");
			break;
		}
	    return;
	}

    } else {


	if (mode == 4) {
	    /* Special case - move FP0 into the register to */
	    ins2(m_fmovel, 32L, 32L, FP0, to, 1);

            /* This might generate operand error */
            test_overflow(ON_FP_OPERAND_ERROR);

	    have_cond = 0;
	    change_var_sh(sha, slongsh, to, to);
	    return;
	}

	if (have_overflow()) {
	  /*
       * This must be checked before a round operation is attempted
	   * because out-of-range values can cause an exception.
       */
	  check_float_round_overflow(sha,from,mode);
	}

	if (mode == f_toward_zero || mode == f_to_nearest) {
	    /* Rounding to nearest or towards zero are easy */
	    int instr;
	    shape shf = sh(from.wh_exp);
	    long szf = shape_size(shf);
	    if (mode == f_toward_zero) {
		instr = m_fintrzx;
		if (whereis(from)!= Freg) {
		    instr = insf(szf, ml_fint);
		}
	    } else {
                set_round_mode(mode);
		instr = m_fintx;
		if (whereis(from)!= Freg) {
		    instr = insf(szf, ml_fintrz);
		}
	    }
	    ins2(instr, szf, szf, from, FP0, 1);
	    if (whereis(to) == Dreg) {
		dest = to;
	    } else {
		dest = D0;
	    }
	    ins2(m_fmovel, 32L, 32L, FP0, dest, 1);
	    have_cond = 0;
	    change_var_sh(sha, slongsh, dest, to);
	    return;
	}
    }

    /* Other modes : firstly find some registers */
    if (whereis(to) == Dreg) {
	dest = to;
    } else {
	dest = D0;
    }
    if (whereis(from) == Freg && !eq_where(from, FP0)) {
	fr = from;
    } else {
	shape shf = sh(from.wh_exp);
	fr = FP1;
	regsinproc |= regmsk(REG_FP1);
	move(shf, from, fr);
    }

    /* Round fr into FP0 */
    if (mode == f_toward_zero) {
       ins2(m_fintrzx, 64, 64, fr, FP0, 1);
    }
    else {
       set_round_mode(mode);
       ins2(m_fintx, 64, 64, fr, FP0, 1);
    }

    /* Move FP0 into dest */
    crt_rmode = 4;
    round_float(sha, FP0, dest);
    crt_rmode = mode;

    /* Move result into place */
    have_cond = 0;
    move(sha, dest, to);
    return;
}

/*
 * CONVERT AN INTEGER TO A FLOATING POINT NUMBER
 *
 * The integer value from is converted to a floating-point value of
 * shape sha and stored in to. Unsigned longs are difficult.
 * Error treatments are ignored (they cannot occur at present).
 */
void int_to_float
(shape sha, where from, where to)
{
    where fpr;
    shape shf = sh(from.wh_exp);
#ifdef REJECT
    fpr = (whereis(to) == Freg ? to : FP0);
#else
    fpr = FP0;
#endif
    if (name(shf) == ulonghd) {
	switch (abi) {
	case ABI_NEXT:
	case ABI_SUNOS: {
		where fm;
		long lab = next_lab();
		exp jt = simple_exp(0);
		ptno(jt) = lab;
#ifdef FBASE_10
		fm = mfw(1, "4294967296", 9);
#else
		{
		    static long fmd[] = { 1, 0, 0, -1 };
		    fm = mfw(1, fmd, 2);
		}
#endif

		if (whereis(from) == Dreg) {
			ins2(m_fmovel, 32L, 64L, from, fpr, 1);
		} else {
			move(slongsh, from, D0);
			ins2(m_fmovel, 32L, 64L, D0, fpr, 1);
		}

		branch(tst_ge, jt, 1, 1, 1);
		add(sha, fpr, fm, fpr);
		make_label(lab);
		have_cond = 0;
		move(sha, fpr, to);
		return;
	}

	case ABI_HPUX:
		if (whereis(from) == Dreg) {
		    push(slongsh, 32L, from);
		} else {
		    move(shf, from, D0);
		    push(slongsh, 32L, D0);
		}
		libcall("___floatu");
		dec_stack(-32);
		have_cond = 0;
		move(realsh, D0_D1, fpr);
		move(sha, fpr, to);
		return;
	}
    }

    if (name(shf) == slonghd && whereis(from) == Dreg) {
	ins2(m_fmovel, 32L, 64L, from, fpr, 1);
    } else {
	change_var_sh(slongsh, shf, from, D0);
	ins2(m_fmovel, 32L, 64L, D0, fpr, 1);
    }
    move(sha, fpr, to);
    have_cond = 0;
    return;
}
