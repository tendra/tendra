/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/error.h>

#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/shapemacs.h>
#include <construct/tags.h>

#include "assembler.h"
#include "expmacs.h"
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
#include "output.h"

extern void add_const(shape, long, where);

/*
    DO AN ADD BY A LOAD EFFECTIVE ADDRESS

    The m_lea instruction is used to add the constant offset to the value
    a and put the result into dest.  The flag psh is true to indicate
    that the result should be pushed onto the stack.
*/

void load_ea
(shape sha, long offset, where a, where dest, bool psh)
{
    if (have_overflow()) {
	move(sha, a, D0);
	add_const(sha, offset, D0);
	move(sha, D0, dest);
	have_cond = 0;
    } else {
	exp ra = simple_exp(dummy_tag);
	son(ra) = a.wh_exp;
	no(ra) = 8 * offset;
	if (psh) {
	    ins1(m_pea, 32L, zw(ra), 0);
	    stack_size -= 32;
	} else {
	    ins2(m_lea, 32L, 32L, zw(ra), dest, 1);
	}
	retcell(ra);
	have_cond = 0;
    }
    return;
}


/*
    INCREASE BY A CONSTANT

    The value dest is increased or decreased by the constant n.
*/

void addsub_const
(shape sha, long n, where dest, bool use_sub)
{
    int instr;
    bool negate = 0, use_quick = 0;

    long sz = shape_size(sha);
    if (n == 0) return;

    /* If destination is a value we just have to test for overflow */

    if (whereis(dest) == Value) {
       long v = nw(dest);
       if (is_signed(sha)) {
          if (use_sub)
             n = -n;
          if (v>0 && n>0) {
             if (v > range_max(sha) - n)
                test_overflow(UNCONDITIONAL);
          }
          else if (v<0 && n<0) {
             if (v < range_min(sha) - n)
                test_overflow(UNCONDITIONAL);
          }
       }
       else { /* unsigned addition */
          if (use_sub) {
             /* will v - n underflow ? */
             if ((unsigned)v < (unsigned)range_min(sha) - (unsigned)n)
                test_overflow(UNCONDITIONAL);
          }
          else {
             if ((unsigned)v > (unsigned)range_max(sha) - (unsigned)n)
                test_overflow(UNCONDITIONAL);
          }
       }
       return;
    }


    /* Destination is not just a value */

    /* If we don't have to test for overflow, we can chose wheter to add/sub */
    /* Changeing add and sub might allow us to use quick add or sub */
    if (! have_overflow()) {
       /* But -(INT_MIN) can't be represented in signed shape */
       if (n != INT_MIN) {
          if (n < 0)
             negate = 1;
          if ((n < 8) && (n > -8))
             use_quick = 1;
       }
    }
    else {
       if ((unsigned long)n < 8)
          use_quick = 1;
    }

    /* Special handling for address regs. */
    if (whereis(dest) == Areg) {
       if (use_quick) {
          have_cond = 0;
       }
       else {
          if (use_sub)
             n = -n;
          load_ea(sha, n, dest, dest, 0);
          return;
       }
    }

    /* Find appropriate ADD/SUB */
    if (negate) {
       n = -n;
       use_sub = ! use_sub;
    }

    if (use_sub) {
       if (use_quick)
          instr = ins(sz, ml_subq);
       else
          instr = ins(sz, ml_sub);
    }
    else {
       if (use_quick)
          instr = ins(sz, ml_addq);
       else
          instr = ins(sz, ml_add);
    }

    ins2n(instr, n, sz, dest, 1);
    set_cond(dest, sz);
    test_overflow(ON_SHAPE(sha));
}

void add_const
(shape sha, long n, where dest)
{
   addsub_const(sha, n, dest, 0);
}

void sub_const
(shape sha, long n, where dest)
{
   addsub_const(sha, n, dest, 1);
}

/*
    AUXILIARY ADD ROUTINE

    The value inc (of shape sha and size sz) is added to dest.
*/

static void add_aux
(shape sha, long sz, where inc, where dest)
{
    int instr;
    long whi = whereis(inc);
    long whd = whereis(dest);
    if (whd == Freg) {
	move(sha, dest, D0);
	add_aux(sha, sz, inc, D0);
	move(sha, D0, dest);
	return;
    }
    if (whi == Value) {
	long v = nw(inc);
	if (is_offset(inc.wh_exp))v /= 8;
	add_const(sha, v, dest);
	return;
    }
    if (whi == Freg) {
	move(sha, inc, D0);
	add_aux(sha, sz, D0, dest);
	return;
    }

    if (have_overflow() && whd == Areg) {
	/* Skip to end */
    } else if (whi == Dreg || whd == Dreg || whd == Areg) {
	instr = ins(sz, ml_add);
	ins2(instr, sz, sz, inc, dest, 1);
	if (whd == Areg) {
	    have_cond = 0;
	} else {
	    set_cond(dest, sz);
	}
        test_overflow(ON_SHAPE(sha));
	return;
    }
    move(sha, inc, D0);
    add_aux(sha, sz, D0, dest);
    return;
}


/*
    ADD CONSTANT ROUTINE

    The constant c is added to the value inc, and the result is stored
    in dest.
*/

static void addsub_const_3_args
(shape sha, long sz, long c, where inc, where dest, bool use_sub)
{
    if (c == 0) {
	move(sha, inc, dest);
	return;
    }
    switch (whereis(dest)) {
	case Dreg: {
	    move(sha, inc, dest);
	    addsub_const(sha, c, dest, use_sub);
	    return;
	}
	case Areg: {
	    if (whereis(inc) == Areg) {
		load_ea(sha, c, inc, dest, 0);
		return;
	    }
	    move(sha, inc, dest);
	    addsub_const(sha, c, dest, use_sub);
	    return;
	}
	default : {
	    long whi = whereis(inc);
	    if (whi == Dreg && last_use(inc)) {
		addsub_const(sha, c, inc, use_sub);
		move(sha, inc, dest);
		set_cond(dest, sz);
		return;
	    }
	    if (whi == Areg && (  name(dest.wh_exp) == apply_tag
                                 || name(dest.wh_exp) == apply_general_tag
                                 || name(dest.wh_exp) == tail_call_tag)) {
		load_ea(sha, c, inc, dest, 1);
		return;
	    }
	    addsub_const_3_args(sha, sz, c, inc, D0, use_sub);
	    move(sha, D0, dest);
	    set_cond(dest, sz);
	    return;
	}
    }
}


/*
    MAIN ADD ROUTINE

    The values a1 and a2 of shape sha are added and the result stored in
    dest.
*/

void add
(shape sha, where a1, where a2, where dest)
{
    long sz = shape_size(sha);
    long rt = shtype(sha);
    long wh1, wh2, whd;

    if (rt == Freg) {
	fl_binop(fplus_tag, sha, a1, a2, dest);
	return;
    }

    if (eq_where(a1, dest)) {
	add_aux(sha, sz, a2, dest);
	return;
    }

    if (eq_where(a2, dest)) {
	add_aux(sha, sz, a1, dest);
	return;
    }

    wh1 = whereis(a1);
    wh2 = whereis(a2);
    whd = whereis(dest);

    if (wh1 == Value) {
	long v1 = nw(a1);
	if (is_offset(a1.wh_exp))v1 /= 8;
	if (wh2 == Value && !have_overflow()) {
	    long v2 = nw(a2);
	    if (is_offset(a2.wh_exp))v2 /= 8;
	    move(sha, mnw(v1 + v2), dest);
	    return;
	}
	addsub_const_3_args(sha, sz, v1, a2, dest, 0);
	return;
    }

    if (wh2 == Value) {
	long v2 = nw(a2);
	if (is_offset(a2.wh_exp))v2 /= 8;
	addsub_const_3_args(sha, sz, v2, a1, dest, 0);
	return;
    }

    if (whd == Dreg) {
	if (!interfere(a2, dest)) {
	    move(sha, a1, dest);
	    add_aux(sha, sz, a2, dest);
	    return;
	}
	if (!interfere(a1, dest)) {
	    move(sha, a2, dest);
	    add_aux(sha, sz, a1, dest);
	    return;
	}
    }

    if (wh1 == Dreg && last_use(a1)) {
	add_aux(sha, sz, a2, a1);
	move(sha, a1, dest);
	set_cond(dest, sz);
	return;
    }

    if (wh2 == Dreg && last_use(a2)) {
	add_aux(sha, sz, a1, a2);
	move(sha, a2, dest);
	set_cond(dest, sz);
	return;
    }

    if (wh1 == Dreg) {
	move(sha, a2, D0);
	add_aux(sha, sz, a1, D0);
    } else {
	move(sha, a1, D0);
	add_aux(sha, sz, a2, D0);
    }
    move(sha, D0, dest);
    set_cond(dest, sz);
    return;
}


/*
    AUXILIARY SUBTRACT ROUTINE

    The value a is subtracted from dest.
*/

static void sub_aux
(shape sha, long sz, where a, where dest)
{
    long wha = whereis(a);
    long whd = whereis(dest);
    if (whd == Freg) {
	move(sha, dest, D0);
	sub_aux(sha, sz, a, D0);
	move(sha, D0, dest);
	return;
    }

    if (wha == Value) {
	long v = nw(a);
	if (is_offset(a.wh_exp))v /= 8;
	sub_const(sha, v, dest);
	return;
    }

    if (wha != Freg) {
	if (have_overflow() && whd == Areg) {
	    /* Skip to end */
	} else if (whd == Dreg || whd == Areg || wha == Dreg) {
	    int instr = ins(sz, ml_sub);
	    ins2(instr, sz, sz, a, dest, 1);
	    if (whd == Areg) {
		have_cond = 0;
	    } else {
		set_cond(dest, sz);
	    }
            test_overflow(ON_SHAPE(sha));
	    return;
	}
    }
    move(sha, a, D0);
    sub_aux(sha, sz, D0, dest);
    set_cond(dest, sz);
    return;
}


/*
    MAIN SUBTRACT ROUTINE

    The value a2 of shape sha is subtracted from a1 and the result is
    stored in dest.
*/

void sub
(shape sha, where a1, where a2, where dest)
{
    long sz = shape_size(sha);
    long wh1, wh2, whd;

    if (eq_where(a1, a2)) {
	move(sha, zero, dest);
	return;
    }

    if (eq_where(a2, dest) && !eq_where(dest,zero)) {
	sub_aux(sha, sz, a1, dest);
	return;
    }

    wh1 = whereis(a1);
    wh2 = whereis(a2);
    whd = whereis(dest);

    if (wh1 == Value) {
	long v1 = nw(a1);
	if (is_offset(a1.wh_exp))v1 /= 8;
	if (wh2 == Value) {
	    long v2 = nw(a2);
	    if (is_offset(a2.wh_exp))v2 /= 8;

            if (is_signed(sha)) {
               if (v2>0 && v1<0) {
                  if (-v1 > range_max(sha) - v2)
                  test_overflow(UNCONDITIONAL);
               }
               else if (v2<0 && v1>0) {
                  if (v2 < range_min(sha) + v1)
                  test_overflow(UNCONDITIONAL);
               }
            }
            else {
               if ((unsigned)v1> (unsigned)v2)
               test_overflow(UNCONDITIONAL);
            }

	    move(sha, mnw(v2 - v1), dest);
	    return;
	}
	addsub_const_3_args(sha, sz, v1, a2, dest, 1);
	return;
    }

    if (wh2 == Value && nw(a2) == 0) {
	negate(sha, a1, dest);
	return;
    }

    if ((whd == Dreg || whd == Areg) && !interfere(a1, dest)) {
	move(sha, a2, dest);
	sub_aux(sha, sz, a1, dest);
	return;
    }

    move(sha, a2, D0);
    sub_aux(sha, sz, a1, D0);
    move(sha, D0, dest);
    set_cond(dest, sz);
    return;
}


/*
    NEGATE ROUTINE

    The value a of shape sha is negated and the result is stored in dest.
*/

void negate
(shape sha, where a, where dest)
{
    int instr;
    long sz = shape_size(sha);
    long rt = shtype(sha);
    long wha = whereis(a);
    long whd = whereis(dest);

    if (rt == Freg) {
	negate_float(sha, a, dest);
	return;
    }

    if (wha == Value) {
	long c = nw(a);
        bool overflow = 0;

	if (is_offset(a.wh_exp))c /= 8;

        if (is_signed(sha)) {
           if (c < - range_max(sha))
           overflow = 1;
        }
        else {
           if (c != 0) {
              make_comment("negation of unsigned shape");
              overflow = 1;
           }
        }

        /* If there is overflow and we have an error treatment, do it */
        if (overflow && have_overflow()) {
           test_overflow(UNCONDITIONAL);
        }
        /* No, so move the value in place */
        else {
           move(sha, mnw(-c), dest);
        }

	return;
    }

    if (eq_where(a, dest) && whd != Areg) {
	instr = ins(sz, ml_neg);
	ins1(instr, sz, dest, 1);
	set_cond(dest, sz);
        test_overflow(ON_SHAPE(sha));

	return;
    }

    if (whd == Dreg) {
	move(sha, a, dest);
	negate(sha, dest, dest);
	return;
    }

    if (wha == Dreg && last_use(a)) {
	negate(sha, a, a);
	move(sha, a, dest);
	return;
    }

    move(sha, a, D0);
    negate(sha, D0, D0);
    move(sha, D0, dest);
    return;
}


/*
    AUXILIARY MULTIPLY ROUTINE

    The value dest of shape sha is multiplied by a.
*/

static void mult_aux
(shape sha, where a, where dest)
{
    bool sg = is_signed(sha);
    long sz = shape_size(sha);
    int instr = (sg ? m_mulsl : m_mulul);
    shape lsha = (sg ? slongsh : ulongsh);

    if (whereis(a) == Freg) {
	move(sha, a, D0);
	mult_aux(sha, D0, dest);
	return;
    }

    if (sz == 8 || (have_overflow() && (sz == 16))) {
	change_var_sh(lsha, sha, dest, dest);
	change_var_sh(lsha, sha, a, D0);
	ins2(instr, 32L, 32L, dest, D0, 1);
        test_overflow(ON_OVERFLOW);
	change_var_sh(sha, lsha, D0, dest);
	set_cond(dest, sz);
	return;
    }

    if (sz == 16)instr = (sg ? m_mulsw : m_muluw);

    if (whereis(dest) == Dreg) {
	if (whereis(a) == Areg) {
	    if (eq_where(dest, D0)) {
		move(sha, a, D1);
		regsinproc |= regmsk(REG_D1);
		ins2(instr, sz, sz, D1, dest, 1);
	    } else {
		move(sha, a, D0);
		ins2(instr, sz, sz, D0, dest, 1);
	    }
	} else {
	    ins2(instr, sz, sz, a, dest, 1);
	}
        test_overflow(ON_OVERFLOW);
	set_cond(dest, sz);
	return;
    }

    move(sha, dest, D0);
    if (whereis(a) == Areg) {
	move(sha, a, D1);
	regsinproc |= regmsk(REG_D1);
	ins2(instr, sz, sz, D1, D0, 1);
    } else {
	ins2(instr, sz, sz, a, D0, 1);
    }
    test_overflow(ON_OVERFLOW);
    move(sha, D0, dest);
    set_cond(dest, sz);
    return;
}


/*
    MULTIPLY USING LOAD EFFECTIVE ADDRESS

    The m_lea instruction is used to multiply a by the constant sf + 1
    where sf is 1, 2, 4 or 8.  If d is true then a further add instruction
    is used to multiply further by 2.  The result is stored in dest.
    This routine only applies to values of size 32.
*/

static void mult_clever
(where a, where dest, long sf, bool d)
{
    int r;
    where ar;
    mach_op *op1, *op2;
    if (whereis(dest) == Areg) {
	ar = dest;
	r = reg(dest.wh_regs);
    } else {
	r = next_tmp_reg();
	regsinproc |= regmsk(r);
	ar = register(r);
    }
    move(slongsh, a, ar);
    op1 = make_reg_index(r, r, 0, sf);
    op2 = make_register(r);
    make_instr(m_lea, op1, op2, regmsk(r));
    have_cond = 0;
    if (d) {
	op1 = make_register(r);
	op2 = make_register(r);
	make_instr(m_addl, op1, op2, regmsk(r));
    }
    tmp_reg_status = 1;
    move(slongsh, ar, dest);
    return;
}


/*
    MULTIPLY A REGISTER BY A POWER OF 2

    The register r is multiplied by 2 to the power of p.  The flag
    D1_used is passed on to shift_aux if necessary.
*/

static void mult_power2
(long p, where r, bool D1_used)
{
    switch (p) {
	case 0: return;
	case 1: ins2(m_addl, 32L, 32L, r, r, 1); return;
	default : {
	    shift_aux(slongsh, mnw(p), r, r, 0, D1_used);
	    return;
	}
    }
}


/*
    MULTIPLICATION UTILITY ROUTINE

    This routine is used by mult_const.  The values r1 and r2 represent
    registers.  If P denotes 2 to the power of p and Q denotes 2 to the
    power of q then :

	(a)  If first_time is true, then q will be zero and r2 will hold
	     the same value as r1.  r1 is multiplied by P - 1.

	(b)  Otherwise, r1 is set equal to ( P * Q * r1 + ( P - 1 ) * r2 ).

    The flag D1_used is passed onto mult_power2 if necessary.
*/

static void mult_utility
(long p, long q, where r1, where r2, bool D1_used, bool first_time)
{
    if (first_time) {
	switch (p) {

	    case 0 : return ;		/* Doesn't occur */
	    case 1 : return ;		/* Multiply by one */

	    case 2: {
		/* Multiply by 3 */
		ins2(m_addl, 32L, 32L, r1, r1, 1);
		ins2(m_addl, 32L, 32L, r2, r1, 1);
		return;
	    }

	    default : {
		mult_power2(p, r1, D1_used);
		ins2(m_subl, 32L, 32L, r2, r1, 1);
		return;
	    }
	}
    } else {
	switch (p) {

	    case 0: {
		/* P = 1 => r1 = ( Q * r1 ) */
		mult_power2(q, r1, D1_used);
		return;
	    }

	    case 1: {
		/* P = 2 => r1 = ( 2 * Q * r1 + r2 ) */
		mult_power2(q + 1, r1, D1_used);
		ins2(m_addl, 32L, 32L, r2, r1, 1);
		return;
	    }

	    case 2: {
		/* P = 4 => r1 = ( 4 * Q * r1 + 3 * r2 ) */
		mult_power2(q + 1, r1, D1_used);
		ins2(m_addl, 32L, 32L, r2, r1, 1);
		ins2(m_addl, 32L, 32L, r1, r1, 1);
		ins2(m_addl, 32L, 32L, r2, r1, 1);
		return;
	    }

	    default : {
		mult_power2(q, r1, D1_used);
		ins2(m_addl, 32L, 32L, r2, r1, 1);
		mult_power2(p, r1, D1_used);
		ins2(m_subl, 32L, 32L, r2, r1, 1);
		return;
	    }
	}
    }
}


/*
    MULTIPLY BY A CONSTANT

    The value a1 of shape sha is multiplied by the constant value a2
    and the result is stored in dest.  All constant multiplications
    are done by means of shifts, adds and subtracts.  Certain small
    cases and powers of 2 are dealt with separately.  The main algorithm
    is to split the constant into sections of the form 00...0011...11.
*/

static void mult_const
(shape sha, where a1, where a2, where dest)
{
    long n = nw(a2), m, p, q, n0;
    where reg1, reg2;
    bool D1_used, dont_move = 0;
    bool started = 0, first_time = 1;

    long sz = shape_size(sha);

    long wh1 = whereis(a1);
    long whd = whereis(dest);

    if (is_offset(a2.wh_exp))n /= 8;
    switch (n) {

	case 0: {
	    /* Multiply by zero = Load zero */
	    move(sha, zero, dest);
	    return;
	}

	case 1: {
	    /* Multiply by one = Move */
	    move(sha, a1, dest);
	    return;
	}

	case -1: {
	    /* Multiply by minus one = Negate */
	    negate(sha, a1, dest);
	    return;
	}

	case 2: {
	    /* Multiply by two = Add */
	    add(sha, a1, a1, dest);
	    return;
	}

	case 5: {
	    if (sz == 32) {
		mult_clever(a1, dest, 4L, 0);
		return;
	    }
	    break;
	}

	case 9: {
	    if (sz == 32) {
		mult_clever(a1, dest, 8L, 0);
		return;
	    }
	    break;
	}

	case 10: {
	    if (sz == 32) {
		mult_clever(a1, dest, 4L, 1);
		return;
	    }
	    break;
	}

	case 18: {
	    if (sz == 32) {
		mult_clever(a1, dest, 8L, 1);
		return;
	    }
	    break;
	}
    }

    /* Find two registers */
    if (whd == Dreg && !eq_where(dest, D0)) {
	reg1 = dest;
	reg2 = D0;
	D1_used = 0;
    } else {
	reg1 = D0;
	reg2 = D1;
	D1_used = 1;
    }
    if (wh1 == Dreg && !eq_where(a1, reg1)) {
	reg2 = a1;
	D1_used = 0;
	dont_move = 1;
    }

    /* Deal with multiplications of less than 32 bits */
    if (sz < 32) {
	shape lsha = (is_signed(sha)? slongsh : ulongsh);
	change_var_sh(lsha, sha, a1, reg1);
    	mult_const(lsha, reg1, a2, reg1);
	change_var_sh(sha, lsha, reg1, dest);
	return;
    }

    /* Now prepare to multiply by |n| */
    n0 = n;
    if (n < 0)n = -n;

    if (is_pow2(n)) {
	/* Powers of two are easy */
	p = log2(n);
	if (wh1 == Dreg && last_use(a1)) {
	    reg1 = a1;
	    D1_used = 0;
	} else {
	    move(sha, a1, reg1);
	}
	mult_power2(p, reg1, D1_used);
    } else {
	/* The thing we are multiplying goes in reg1 */
	move(sha, a1, reg1);
	/* Copy reg1 into reg2 if necessary */
	if (!dont_move)move(slongsh, reg1, reg2);
	if (D1_used)regsinproc |= regmsk(REG_D1);
	/* p will count consecutive ones and q consecutive zeros */
	p = 0;
	q = 0;
	/* Scan through the 31 bits of n (the sign bit is zero), MSB first */
	for (m = pow2(30); m; m >>= 1) {
	    if (m & n) {
		/* Set bit - record this */
		started = 1;
		p++;
	    } else {
		/* Reset bit - record this */
		if (p) {
		    /* We have read q 0's, then p 1's, before this 0 */
		    mult_utility(p, q, reg1, reg2, 1, first_time);
		    first_time = 0;
		    /* Restart counts */
		    p = 0;
		    q = 0;
		}
		/* Record reset bit, ignoring initial zeros */
		if (started)q++;
	    }
	}
	/* Deal with last batch of digits */
	if (p || q)mult_utility(p, q, reg1, reg2, 1, first_time);
    }
    /* Now put the result into dest - take care of sign of n now */
    if (n0 < 0) {
	negate(slongsh, reg1, dest);
    } else {
	move(slongsh, reg1, dest);
    }
    set_cond(dest, 32L);
    return;
}


/*
    MAIN MULTIPLICATION ROUTINE

    The values a1 and a2 of shape sha are multiplied and the result is
    stored in dest.
*/

void mult
(shape sha, where a1, where a2, where dest)
{
    where w;
    long wh1 = whereis(a1);
    long wh2 = whereis(a2);
    long whd = whereis(dest);

    if (!have_overflow()) {
	/* Constant multiplication */
	if (wh1 == Value) {
	    if (wh2 == Value) {
		long v1 = nw(a1);
		long v2 = nw(a2);
		if (is_offset(a1.wh_exp))v1 /= 8;
		if (is_offset(a2.wh_exp))v2 /= 8;
		move(sha, mnw(v1 * v2), dest);
		return;
	    }
	    mult_const(sha, a2, a1, dest);
	    return;
	}

	if (wh2 == Value) {
	    mult_const(sha, a1, a2, dest);
	    return;
	}
    }

    if (eq_where(a1, a2)) {
	if (whd == Dreg) {
	    move(sha, a1, dest);
	    mult_aux(sha, dest, dest);
	    return;
	} else {
	    move(sha, a1, D0);
	    mult_aux(sha, D0, D0);
	    move(sha, D0, dest);
	    return;
	}
    }

    if (eq_where(a1, dest)) {
	mult_aux(sha, a2, dest);
	return;
    }

    if (eq_where(a2, dest)) {
	mult_aux(sha, a1, dest);
	return;
    }

    if (whd == Dreg) {
	if (!interfere(a2, dest)) {
	    move(sha, a1, dest);
	    mult_aux(sha, a2, dest);
	    return;
	}
	if (!interfere(a1, dest)) {
	    move(sha, a2, dest);
	    mult_aux(sha, a1, dest);
	    return;
	}
    }

    if (shape_size(sha) == 8 ||
	((shape_size(sha) ==16) && (have_overflow()))) {
	w = D1;
	regsinproc |= regmsk(REG_D1);
    } else {
	w = D0;
    }
    if (whereis(a2) == Areg) {
	move(sha, a2, w);
	mult_aux(sha, a1, w);
	move(sha, w, dest);
    } else {
	move(sha, a1, w);
	mult_aux(sha, a2, w);
	move(sha, w, dest);
    }
    return;
}


/*
    DIVISION BY A POWER OF 2

    The value top of shape sha is divided by the constant v which is a
    power of 2.  The result is stored in dest.
*/

static void div_power2
(shape sha, long v, where top, where dest)
{
    long n = log2(v);
    if (is_signed(sha)) {
	bool sw;
	where w;
	int instr;
	long sz = shape_size(sha);
	long lab = next_lab();
	exp jt = simple_exp(0);
	ptno(jt) = lab;

	if (whereis(dest) == Dreg) {
	    w = dest;
	} else if (whereis(top) == Dreg && last_use(top)) {
	    w = top;
	} else {
	    w = D0;
	}
	move(sha, top, w);
	sw = cmp(sha, w, zero, tst_ge);
	branch(tst_ge, jt, 1, sw, 0);
	add(sha, w, mnw(v - 1), w);
	make_label(lab);
	instr = ins(sz, ml_asr);
	while (n) {
	    long m = (n > 8 ? 7 : n);
	    ins2n(instr, m, sz, w, 1);
	    n -= m;
	}
	move(sha, w, dest);
	set_cond(dest, sz);
    } else {
	shift_aux(sha, mnw(n), top, dest, 1, 0);
    }
    return;
}


/*
    REMAINDER MODULO A POWER OF 2

    The remainder of the value top of shape sha when divided by the
    constant v (which is a power of 2) is stored in dest.
*/

static void rem_power2
(shape sha, long v, where top, where dest)
{
    if (is_signed(sha)) {
	bool sw;
	where w;
	long lab = next_lab();
	long end = next_lab();
	exp jt = simple_exp(0);
	exp je = simple_exp(0);
	ptno(jt) = lab;
	ptno(je) = end;

	if (whereis(dest) == Dreg) {
	    w = dest;
	} else if (whereis(top) == Dreg && last_use(top)) {
	    w = top;
	} else {
	    w = D0;
	}
	move(sha, top, w);
	sw = cmp(sha, w, zero, tst_ge);
	branch(tst_ge, jt, 1, sw, 0);
	negate(sha, w, w);
	and(sha, mnw(v - 1), w, w);
	negate(sha, w, w);
	make_jump(m_bra, end);
	make_label(lab);
	and(sha, mnw(v - 1), w, w);
	make_label(end);
	move(sha, w, dest);
	set_cond(dest, shape_size(sha));
    } else {
	and(sha, mnw(v - 1), top, dest);
    }
    return;
}


/*
    REMAINDER MODULO A POWER OF 2 MINUS 1

    The remainder of the value top of shape sha when divided by the
    constant v (which is a power of 2 minus 1) is stored in dest.  The
    algorithm used is a modification of "casting out the nines".
*/

static bool rem_power2_1
(shape sha, long v, where top, where dest)
{
    bool sw;
    where d0, d1;
    long loop, end, tst;
    exp jloop, jend, jtst;
    bool s = is_signed(sha);

    if (s && (eq_where(top, D0) || eq_where(top, D1))) return 0;

    if (whereis(dest) == Dreg) {
	d1 = dest;
    } else {
	d1 = D1;
	regsinproc |= regmsk(REG_D1);
    }

    if (eq_where(d1, D0)) {
	d0 = D1;
	regsinproc |= regmsk(REG_D1);
    } else {
	d0 = D0;
    }

    loop = next_lab();
    jloop = simple_exp(0);
    ptno(jloop) = loop;
    end = next_lab();
    jend = simple_exp(0);
    ptno(jend) = end;
    tst = next_lab();
    jtst = simple_exp(0);
    ptno(jtst) = tst;

    move(sha, top, d1);
    if (s) {
	sw = cmp(sha, d1, zero, tst_ge);
	branch(tst_ge, jloop, s, sw, 0);
	negate(sha, d1, d1);
    }
    make_label(loop);
    move(sha, mnw(v), d0);
    sw = cmp(ulongsh, d1, d0, tst_le);
    branch(tst_le, jend, s, sw, 0);
    and(ulongsh, d1, d0, d0);
    rshift(ulongsh, mnw(log2(v + 1)), d1, d1);
    add(ulongsh, d0, d1, d1);
    make_jump(m_bra, loop);
    make_label(end);
    branch(tst_neq, jtst, s, sw, 0);
    move(sha, zero, d1);
    make_label(tst);
    if (s) {
	long ntst = next_lab();
	exp jntst = simple_exp(0);
	ptno(jntst) = ntst;
	sw = cmp(sha, top, zero, tst_ge);
	branch(tst_ge, jntst, 1, sw, 0);
	negate(sha, d1, d1);
	make_label(ntst);
    }
    have_cond = 0;
    move(sha, d1, dest);
    return 1;
}


/*
    MARKERS FOR DIVISION AND REMAINDER

    Division, remainder and combined division-remainder operations are
    all handled by a single routine.  The following values are used to
    indicate to the routine the operation type.
*/

#define  DIV		0
#define  REM		1
#define  BOTH		2


/*
    MAIN DIVISION AND REMAINDER ROUTINE

    The value top of shape sha is divided by bottom and, depending on
    the value of type, the quotient is stored in quot and the remainder
    in rem.  Which of the two possible division types used is determined
    by form : for example, if form is 1 then :

		    5 = ( -2 ) * ( -3 ) - 1

    whereas if form is 2 :

		    5 = ( -1 ) * ( -3 ) + 2

    The second form is the standard one.
*/

static void euclid
(shape sha, where bottom, where top, where quot, where rem, int type, int form)
{
    long v;
    bool b_const = 0;
    bool save_d1 = 0;
    bool d1_pending = 0;
    where qreg, rreg, breg;
    long sz = shape_size(sha);
    bool sg = is_signed(sha);
    shape lsha = (sg ? slongsh : ulongsh);

    /* The two forms are the same for unsigned division */
    if (!sg) form = 2;

    /* Deal with division by constants */
    if (name(bottom.wh_exp) == val_tag) {
	b_const = 1;
	v = nw(bottom);
	if (is_offset(bottom.wh_exp))v /= 8;
	switch (v) {

	    case 0: {
		error(ERROR_WARNING, "Division by zero");
                if (have_overflow()) {
                   test_overflow(UNCONDITIONAL);
                }
                else {
                   if (type != REM)move(sha, zero, quot);
                   if (type != DIV)move(sha, zero, rem);
                }
		return;
	    }

	    case 1: {
		if (type != REM)move(sha, top, quot);
		if (type != DIV)move(sha, zero, rem);
		return;
	    }

	    case -1: {
                if (is_signed(sha)) { /* is it really negative */
                    if (type != REM || have_overflow())negate(sha, top, quot);
                    if (type != DIV)move(sha, zero, rem);
                    return;
                }
                /* fall through */
	    }

	    default : {
		if (form != 1) {
                    if ((!is_signed(sha) || v > 0) && is_pow2(v) && sz == 32) {
                        if (type == DIV) {
			    div_power2(sha, v, top, quot);
			    return;
			}
			if (type == REM) {
			    rem_power2(sha, v, top, rem);
			    return;
			}
		    }
		    if (v > 7 && is_pow2(v + 1) && sz == 32) {
			if (type == REM &&
			     rem_power2_1(sha, v, top, rem)) {
			    return;
			}
		    }
		}
		break;
	    }
	}
    }

    /* Check on pointless divisions */
    if (eq_where(top, bottom)) {
	if (type != REM)move(sha, mnw(1), quot);
	if (type != DIV)move(sha, zero, rem);
	return;
    }

    /* Now find two registers */
    if (type == BOTH && interfere(quot, rem)) {
	qreg = D0;
	rreg = D1;
	regsinproc |= regmsk(REG_D1);
	if (D1_is_special)save_d1 = 1;
    } else {
	if (type != REM && whereis(quot) == Dreg &&
	     !interfere(quot, bottom)) {
	    qreg = quot;
	} else {
	    qreg = D0;
	}
	if (type != DIV && whereis(rem) == Dreg) {
	    if (eq_where(rem, D0)) {
		qreg = D1;
		rreg = D0;
		regsinproc |= regmsk(REG_D1);
		if (D1_is_special)save_d1 = 1;
	    } else {
		rreg = rem;
	    }
	} else {
	    if (eq_where(qreg, D0)) {
		rreg = D1;
		if (type == DIV) {
		    d1_pending = 1;
		} else {
		    regsinproc |= regmsk(REG_D1);
		    if (D1_is_special)save_d1 = 1;
		}
	    } else {
		rreg = D0;
	    }
	}
    }

    /* Save D1 if necessary */
    if (save_d1)push(slongsh, 32L, D1);
#if 0
    /* Keep the denominator in form 1 */
    if (form == 1 && !b_const)push(slongsh, 32L, bottom);
#endif
    /* Get the arguments into the correct positions */
    if (sz != 32) {
       bool d0_pushed = 0;

       make_comment("change variety top -> qreg");
       change_var_sh(lsha, sha, top, qreg);

       if (eq_where(qreg, D0)) {
          push(slongsh, 32L, D0);
          d0_pushed = 1;
       }

       make_comment("change variety bottom -> rreg");
       change_var_sh(lsha, sha, bottom, rreg);

       if (d0_pushed)
          pop(slongsh,32L,D0);

       breg = rreg;
    } else {
	move(sha, top, qreg);
	if (whereis(bottom) == Areg || whereis(bottom) == Freg) {
	    if (d1_pending) {
		regsinproc |= regmsk(REG_D1);
		if (D1_is_special) {
		    save_d1 = 1;
		    push(slongsh, 32L, D1);
		}
	    }
	    move(sha, bottom, rreg);
	    breg = rreg;
	} else {
	    breg = bottom;
	}
    }

    if (have_overflow()) {
       if (save_d1) {
          pop(slongsh,32L,D1);
       }
       cmp_zero(sha, sz, breg);
       test_overflow2(m_beq);
       if (save_d1) {
          push(slongsh,32L,D1);
       }
    }

    /* Keep the denominator in form 1 */
    if (form == 1 && !b_const)push(slongsh, 32L, breg);

    /* Create the actual division instruction */
    if (type == DIV && form != 1) {
	long qn = reg(qreg.wh_regs);
	int instr = (sg ? m_divsl : m_divul);
	mach_op *op1 = operand(32L, breg);
	mach_op *op2 = make_register(qn);
	make_instr(instr, op1, op2, regmsk(qn));
    } else {
	long qn = reg(qreg.wh_regs);
	long rn = reg(rreg.wh_regs);
	int instr = (sg ? m_divsll : m_divull);
	mach_op *op1 = operand(32L, breg);
	mach_op *op2 = make_reg_pair(rn, qn);
	make_instr(instr, op1, op2,(regmsk(qn) | regmsk(rn)));
    }
    if (have_overflow()) {
      if (save_d1) {
	pop(slongsh,32L,D1);
      }
      if (form == 1 && !b_const) {
	dec_stack(-32);
      }
      test_overflow(ON_SHAPE(sha));
      if (form == 1 && !b_const) {
	dec_stack(32);
      }


    }


    /* Apply hacks for form 1 */
    if (form == 1 && is_signed(sha)) {
	mach_op *op1, *op2;
	long lab1 = next_lab();
	long lab2 = next_lab();
	long qn = reg(qreg.wh_regs);
	long rn = reg(rreg.wh_regs);
	if (!b_const) {
	    op1 = make_indirect(REG_SP, 0);
	    make_instr(m_tstl, op1, NULL, 0);
	    make_jump(m_bge, lab1);
	}

	/* Denominator is negative ? */
	if (!(b_const && v >= 0)) {
	    op1 = make_register(rn);
	    make_instr(m_tstl, op1, NULL, 0);
	    make_jump(m_ble, lab2);
	    if (type != REM) {
		op1 = make_value(1);
		op2 = make_register(qn);
		make_instr(m_subql, op1, op2, regmsk(qn));
	    }
	    if (type != DIV) {
		if (b_const) {
		    op1 = make_value(v);
		} else {
		    op1 = make_indirect(REG_SP, 0);
		}
		op2 = make_register(rn);
		make_instr(m_addl, op1, op2, regmsk(rn));
	    }
	    if (!b_const)make_jump(m_bra, lab2);
	}

	/* Denominator is positive ? */
	if (!(b_const && v < 0)) {
	    if (!b_const)make_label(lab1);
	    op1 = make_register(rn);
	    make_instr(m_tstl, op1, NULL, 0);
	    make_jump(m_bge, lab2);
	    if (type != REM) {
		op1 = make_value(1);
		op2 = make_register(qn);
		make_instr(m_subql, op1, op2, regmsk(qn));
	    }
	    if (type != DIV) {
		if (b_const) {
		    op1 = make_value(v);
		} else {
		    op1 = make_indirect(REG_SP, 0);
		}
		op2 = make_register(rn);
		make_instr(m_addl, op1, op2, regmsk(rn));
	    }
	}

	make_label(lab2);
	if (!b_const)dec_stack(-32);
    }

    /* Move results into place */
    if (sz == 32) {
	if (type != REM)move(sha, qreg, quot);
	if (type != DIV)move(sha, rreg, rem);
    } else {
	if (type != REM)change_var_sh(sha, lsha, qreg, quot);
	if (type != DIV)change_var_sh(sha, lsha, rreg, rem);
    }

    /* Restore D1 */
    if (save_d1) {
	pop(slongsh, 32L, D1);
	debug_warning("D1 saved on stack during division");
    }
    have_cond = 0;
    return;
}


/*
    DIVISION INSTRUCTION - FORM ONE

    The value top of shape sha is divided by bottom and the result is
    stored in dest.  This is the alternative division operation.
*/

void div1
(shape sha, where bottom, where top, where dest)
{
    euclid(sha, bottom, top, dest, zero, DIV, 1);
    return;
}


/*
    DIVISION INSTRUCTION - FORM TWO

    The value top of shape sha is divided by bottom and the result is
    stored in dest.  This is the standard division operation.
*/

void div2
(shape sha, where bottom, where top, where dest)
{
    euclid(sha, bottom, top, dest, zero, DIV, 2);
    return;
}


/*
    REMAINDER INSTRUCTION - FORM ONE

    The value top of shape sha is divided by bottom and the remainder is
    stored in dest.  This is the alternative remainder operation.
*/

void rem1
(shape sha, where bottom, where top, where dest)
{
    euclid(sha, bottom, top, zero, dest, REM, 1);
    return;
}


/*
    REMAINDER INSTRUCTION - FORM TWO

    The value top of shape sha is divided by bottom and the remainder is
    stored in dest.  This is the standard remainder operation.
*/

void rem2
(shape sha, where bottom, where top, where dest)
{
    euclid(sha, bottom, top, zero, dest, REM, 2);
    return;
}


/*
    DO AN EXACT DIVISION

    The value top is divided by bottom and the result is stored in dest.
*/

void exactdiv
(shape sha, where bottom, where top, where dest)
{
    euclid(slongsh, bottom, top, dest, zero, DIV, 2);
    return;
}


/*
    DO A MAXIMUM OR MINIMUM INSTRUCTION
*/

static void maxmin
(shape sha, where a1, where a2, where dest, int tst)
{
    where d;
    bool sw;
    long lab = next_lab();
    exp jt = simple_exp(0);
    ptno(jt) = lab;
    if (whereis(dest) == Dreg && !interfere(a1, dest) &&
	 !interfere(a2, dest)) {
	d = dest;
    } else {
	d = D0;
    }
    make_comment("maxmin ...");
    move(sha, a1, d);
    sw = cmp(sha, d, a2, tst);
    branch(tst, jt, is_signed(sha), sw, 0);
    move(sha, a2, d);
    make_label(lab);
    move(sha, d, dest);
    make_comment("maxmin done");
    return;
}


/*
    DO A MAXIMUM INSTRUCTION
*/

void maxop
(shape sha, where a1, where a2, where dest)
{
    maxmin(sha, a1, a2, dest, tst_ge);
    return;
}


/*
    DO A MINIMUM INSTRUCTION
*/

void minop
(shape sha, where a1, where a2, where dest)
{
    maxmin(sha, a1, a2, dest, tst_le);
    return;
}


/*
    DO AN ABSOLUTE OPERATION
*/

void absop
(shape sha, where a, where dest)
{
    if (is_signed(sha)) {
	where d;
	bool sw;
	long lab = next_lab();
	exp jt = simple_exp(0);
	ptno(jt) = lab;
	if (whereis(dest) == Dreg) {
	    d = dest;
	} else {
	    d = D0;
	}
	move(sha, a, d);
	sw = cmp(sha, d, zero, tst_ge);
	branch(tst_ge, jt, 1, sw, 0);
	negate(sha, d, d);
	make_label(lab);
	move(sha, d, dest);
    } else {
	move(sha, a, dest);
    }
    return;
}
