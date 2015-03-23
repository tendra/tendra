/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/shape.h>
#include <construct/tags.h>

#include <utility/bits.h>

#include "assembler.h"
#include "mach.h"
#include "mach_ins.h"
#include "where.h"
#include "mach_op.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "make_code.h"
#include "tests.h"
#include "operations.h"
#include "evaluate.h"
#include "utility.h"
#include "translate.h"
#include "ops_shared.h"


/*
    The logical operations, and, or and xor are handled by a single
    routine with a flag to indicate which is meant.  The flag can take
    the following values.
*/

#define  AND		0
#define  OR		1
#define  XOR		2


/*
    The value a of shape sha and size sz has the logical operator indicated
    by logop applied to it and the constant c.  The result is stored in
    dest.  instr is one of m_andl, m_orl, eorl.
*/

static void
andetc_const(int instr, shape sha, long sz, long c, where a, where dest,
	     int logop)
{
	long whd;

	/* First check that a is not a constant */
	if (whereis(a) == Value) {
		long ca = nw(a);
		switch (logop) {
		case AND:
			ca &= c;
			break;
		case OR:
			ca |= c;
			break;
		case XOR:
			ca ^= c;
			break;
		}
		move(sha, mnw(ca), dest);
		return;
	}

	/* Now look for some special values of c */
	switch (logop) {
	case AND: {
		long cc;
		if (c == 0) {
			move(sha, zero, dest);
			return;
		}
		cc = ~c;
		if (sz == 32) {
			if (cc == 0) {
				change_var(sha, a, dest);
				return;
			}
			if (is_pow2(cc)) {
				long p = log2(cc);
				if (whereis(dest) == Dreg) {
					change_var(sha, a, dest);
					ins2n(m_bclr, p, sz, dest, 1);
					have_cond = 0;
					return;
				}
			}
		}
		break;
	}
	case OR:
		if (c == 0) {
			change_var(sha, a, dest);
			return;
		}
		if (is_pow2(c)) {
			long p = log2(c);
			if (whereis(dest) == Dreg) {
				change_var(sha, a, dest);
				ins2n(m_bset, p, sz, dest, 1);
				have_cond = 0;
				return;
			}
		}
		break;
	case XOR:
		if (c == 0) {
			change_var(sha, a, dest);
			return;
		}
		break;
	}

	whd = whereis(dest);
	if (whd != Areg && eq_where(a, dest)) {
		ins2h(instr, c, sz, dest, 1);
		set_cond(dest, sz);
		return;
	}
	if (whd == Dreg) {
		change_var(sha, a, dest);
		ins2h(instr, c, sz, dest, 1);
		set_cond(dest, sz);
		return;
	}
	if (whereis(a) == Dreg && last_use(a)) {
		ins2h(instr, c, sz, a, 1);
		change_var(sha, a, dest);
		set_cond(dest, sz);
		return;
	}
	change_var(sha, a, D0);
	ins2h(instr, c, sz, D0, 1);
	move(sha, D0, dest);
	set_cond(dest, sz);
}


/*
    The values a1 and a2 of shape sha have the logical operation indicated
    by logop applied to them and the result is stored in dest.  (opb,
    opw, opl) is an ordered triple giving the byte, word and long forms of
    the appropriate machine instruction.
*/

static void
andetc(int opb, int opw, int opl, shape sha, where a1, where a2, where dest,
       int logop)
{
	int instr;
	long wha, whb, whd;
	long sz = shape_size(sha);

	if (eq_where(a1, a2)) {
		switch (logop) {
		case AND:
			move(sha, a1, dest);
			return;
		case OR:
			move(sha, a1, dest);
			return;
		case XOR:
			move(sha, zero, dest);
			return;
		}
	}

	instr = ins(sz, opb, opw, opl);

	wha = whereis(a1);
	whb = whereis(a2);

	if (wha == Freg) {
		move(sha, a1, D0);
		andetc(opb, opw, opl, sha, D0, a2, dest, logop);
		return;
	}

	if (whb == Freg) {
		move(sha, a2, D0);
		andetc(opb, opw, opl, sha, a1, D0, dest, logop);
		return;
	}

	if (wha == Value) {
		long c = nw(a1);
		andetc_const(instr, sha, sz, c, a2, dest, logop);
		return;
	}

	if (whb == Value) {
		long c = nw(a2);
		andetc_const(instr, sha, sz, c, a1, dest, logop);
		return;
	}

	whd = whereis(dest);

	if (eq_where(a1, dest) && whd != Areg) {
		if (whb == Dreg) {
			ins2(instr, sz, sz, a2, dest, 1);
			return;
		}
		if (whd == Dreg) {
			if (logop == XOR || whb == Areg) {
				if (eq_where(dest, D0)) {
					regsinproc |= regmsk(REG_D1);
					move(sha, a2, D1);
					ins2(instr, sz, sz, D1, dest, 1);
					set_cond(dest, sz);
					return;
				} else {
					move(sha, a2, D0);
					ins2(instr, sz, sz, D0, dest, 1);
					set_cond(dest, sz);
					return;
				}
			} else {
				ins2(instr, sz, sz, a2, dest, 1);
				set_cond(dest, sz);
				return;
			}
		} else {
			move(sha, a2, D0);
			ins2(instr, sz, sz, D0, dest, 1);
			set_cond(dest, sz);
			return;
		}
	}

	if (eq_where(a2, dest) && whd != Areg) {
		if (wha == Dreg) {
			ins2(instr, sz, sz, a1, dest, 1);
			set_cond(dest, sz);
			return;
		}
		if (whd == Dreg) {
			if (logop == XOR || wha == Areg || wha == Freg) {
				if (eq_where(dest, D0)) {
					regsinproc |= regmsk(REG_D1);
					move(sha, a1, D1);
					ins2(instr, sz, sz, D1, dest, 1);
				} else {
					move(sha, a1, D0);
					ins2(instr, sz, sz, D0, dest, 1);
				}
			} else {
				ins2(instr, sz, sz, a1, dest, 1);
			}
		} else {
			move(sha, a1, D0);
			ins2(instr, sz, sz, D0, dest, 1);
		}
		set_cond(dest, sz);
		return;
	}

	if (whd == Dreg) {
		if (!interfere(a2, dest)) {
			move(sha, a1, dest);
			andetc(opb, opw, opl, sha, a2, dest, dest, logop);
			return;
		}
		if (!interfere(a1, dest)) {
			move(sha, a2, dest);
			andetc(opb, opw, opl, sha, a1, dest, dest, logop);
			return;
		}
	}

	move(sha, a1, D0);
	andetc(opb, opw, opl, sha, a2, D0, D0, logop);
	move(sha, D0, dest);
}


/*
    The values a1 and a2 of shape sha are anded and the result is stored
    in dested.
*/

void
and(shape sha, where a1, where a2, where dest)
{
	andetc(ml_and, sha, a1, a2, dest, AND);
}


/*
    The values a1 and a2 of shape sha are ored and the result is stored
    in dested.
*/

void
or(shape sha, where a1, where a2, where dest)
{
	andetc(ml_or, sha, a1, a2, dest, OR);
}


/*
    The values a1 and a2 of shape sha are xored and the result is stored
    in dested.
*/

void
xor(shape sha, where a1, where a2, where dest)
{
	andetc(ml_eor, sha, a1, a2, dest, XOR);
}


/*
    The value a of shape sha is logically negated and the result is stored
    in dest.
*/

void
not(shape sha, where a, where dest)
{
	int instr;
	long sz = shape_size(sha);
	long wha = whereis(a);
	long whd = whereis(dest);

	if (wha == Value) {
		long c = nw(a);
		move(sha, mnw(~c), dest);
		return;
	}

	if (eq_where(a, dest) && whd != Areg) {
		instr = ins(sz, ml_not);
		ins1(instr, sz, dest, 1);
		set_cond(dest, sz);
		return;
	}

	if (whd == Dreg) {
		move(sha, a, dest);
		not(sha, dest, dest);
		return;
	}

	if (wha == Dreg && last_use(a)) {
		not(sha, a, a);
		move(sha, a, dest);
		return;
	}

	move(sha, a, D0);
	not(sha, D0, D0);
	move(sha, D0, dest);
}


/*
    This routine outputs a simple shift instruction, taking overflow
    into account if necessary (not right yet).
*/

static void
shift_it(shape sha, shape shb, int instr, where by, where to)
{
	long sz;

	UNUSED(shb);

	sz = shape_size(sha);
	ins2(instr, 8L, sz, by, to, 1);
	have_cond = 0;
	test_overflow(ON_OVERFLOW);
}


/*
    The value from of shape sha is shifted, either left if sw is 0, or
    right otherwise, by the value by.  The result is stored in to.
    The dont_use_D1 flag indicates that register D1 should not be used.
    It is always false for simple shifts, but may be true for certain
    multiplications which are done by shifts.
*/

void
shift_aux(shape sha, where by, where from, where to, int sw, int dont_use_D1)
{
	where w;
	long whb, wht;
	int instr, shift_plus, shift_minus;

	shape shb = sh(by.wh_exp);
	long sz = shape_size(sha);
	bool sig = is_signed(sha);

	switch (sz) {
	case 8:
		shift_plus = (sig ? m_aslb : m_lslb);
		shift_minus = (sig ? m_asrb : m_lsrb);
		break;
	case 16:
		shift_plus = (sig ? m_aslw : m_lslw);
		shift_minus = (sig ? m_asrw : m_lsrw);
		break;
	default:
		shift_plus = (sig ? m_asll : m_lsll);
		shift_minus = (sig ? m_asrl : m_lsrl);
		break;
	}

	if (sw) {
		/* Switch shift_plus and shift_minus for right shifts */
		instr = shift_plus;
		shift_plus = shift_minus;
		shift_minus = instr;
	}

	whb = whereis(by);
	wht = whereis(to);

	if (whb == Value && !have_overflow()) {
		long p = nw(by);
		if (p == 0) {
			/* A shift by 0 is a move */
			move(sha, from, to);
			return;
		}
		/* Reduce mod 64 to emulate instruction */
		p &= 0x3f;
		instr = shift_plus;
		/* Do the shift, at most eight at a time */
		if (p <= 8 || D1_is_special || dont_use_D1) {
			w = (wht == Dreg ? to : D0);
			move(sha, from, w);
			while (p) {
				long q = (p > 8 ? 7 : p);
				ins2n(instr, q, sz, w, 1);
				p -= q;
			}
			have_cond = 0;
			move(sha, w, to);
			return;
		}
		/* Fall through otherwise */
		shb = slongsh;
	}

	if (wht == Dreg) {
		if (whb == Dreg && !eq_where(by, to)) {
			move(sha, from, to);
			shift_it(sha, shb, shift_plus, by, to);
			return;
		}
		if (eq_where(D0, to)) {
			w = D1;
			regsinproc |= regmsk(REG_D1);
		} else {
			w = D0;
		}
		move(shb, by, w);
		move(sha, from, to);
		shift_it(sha, shb, shift_plus, w, to);
		return;
	}

	if (whb == Dreg) {
		if (eq_where(D0, by)) {
			w = D1;
			regsinproc |= regmsk(REG_D1);
		} else {
			w = D0;
		}
		move(sha, from, w);
		shift_it(sha, shb, shift_plus, by, w);
		move(sha, w, to);
		return;
	}

	regsinproc |= regmsk(REG_D1);
	move(shb, by, D0);
	move(sha, from, D1);
	shift_it(sha, shb, shift_plus, D0, D1);
	move(sha, D1, to);
}


/*
    The value from of shape sha is shifted left by the value by.  The
    result is stored in to.
*/

void
shift(shape sha, where by, where from, where to)
{
	shift_aux(sha, by, from, to, 0, 0);
}


/*
    The value from of shape sha is shifted right by the value by.  The
    result is stored in to.
*/

void
rshift(shape sha, where by, where from, where to)
{
	shift_aux(sha, by, from, to, 1, 0);
}


/*
    The value in the no field of e is rounded down to a multiple of 32.
    The remainder is the bitfield offset and is returned.
*/

static long
adjust_bitf(exp e)
{
	long boff = no(e)% 32;
	no(e) -= boff;
	return boff;
}


/*
    FIND POSITION OF A BITFIELD OPERATION
*/

static long
bitf_posn(exp e)
{
	char n = name(e);
	if (n == name_tag) {
		return adjust_bitf(e);
	}
	if (n == cont_tag || n == ass_tag) {
		return bitf_posn(son(e));
	}
	if (n == ident_tag) {
		return 0;
	}
	error(ERR_SERIOUS, "Illegal bitfield operation");
	return 0;
}


/*
    The bitfield e of shape sha is extracted into dest.  The current state
    of the stack is also given.
*/

void
bitf_to_int(exp e, shape sha, where dest, ash stack)
{
	where bf, d;
	exp t;
	shape dsha;

	int extend;
	int instr;

	long off, sz, bstart;
	long nbits;
	long boff;

	UNUSED(stack);

	t = dest.wh_exp;
	dsha = sh(t);

	extend = (is_signed(sha)? 1 : 0);
	instr = (extend ? m_bfexts : m_bfextu);

	nbits = shape_size(sha);
	boff = bitf_posn(e);

	off = 8 *(boff / 8);
	sz = 8 *((boff + nbits - 1) / 8) + 8 - off;
	if (sz == 24) {
		sz = 32;
		off -= 8;
	}
	bstart = boff - off;

	switch (name(t)) {
	case ident_tag:
		dsha = sh(son(t));
		break;
	case ass_tag:
		dsha = sh(bro(son(t)));
		break;
	}
	if (name(dsha) == bitfhd) {
		dsha = (extend ? slongsh : ulongsh);
	}
	if (name(dsha) == tophd) {
		error(ERR_WARN, "Top in bitfield assignment");
	}

	bf = mw(e, off);

	if (bstart == 0 && nbits == sz) {
		shape bsha;
		switch (sz) {
		case 8:
			bsha = scharsh;
			break;
		case 16:
			bsha = swordsh;
			break;
		case 32:
			bsha = slongsh;
			break;
		}
		change_var_sh(dsha, bsha, bf, dest);
		return;
	}

	if (whereis(bf) == Dreg) {
		bitpattern m = (lsmask[nbits] <<  boff);
		d = (whereis(dest) == Dreg ? dest : D0);
		and(slongsh, bf, mnw(m), d);
		if (extend) {
			long r = 32 - nbits - boff;
			if (r) {
				if (r <= 8) {
					ins2n(m_lsll, r, 32L, d, 1);
					ins2n(m_asrl, r, 32L, d, 1);
				} else {
					regsinproc |= regmsk(REG_D1);
					ins2n(m_moveq, r, 32L, D1, 1);
					ins2(m_lsll, 32L, 32L, D1, d, 1);
					ins2(m_asrl, 32L, 32L, D1, d, 1);
				}
			}
		}
		have_cond = 0;
		change_var_sh(dsha, slongsh, d, dest);
		return;
	} else {
		mach_op *op1, *op2;
		d = (whereis(dest) == Dreg ? dest : D0);
		op1 = operand(32L, bf);
		op1 = make_bitfield_op(op1,(int)bstart,(int)nbits);
		op2 = operand(32L, d);
		make_instr(instr, op1, op2, regs_changed(op2, 1));
		have_cond = 0;
		change_var_sh(dsha, slongsh, d, dest);
		return;
	}
}


/*
    The value e is inserted into the bitfield d.  The state of the stack
    is also given.
*/

void
int_to_bitf(exp e, exp d, ash stack)
{
	shape sha;
	where dest, f;

	long off, sz, bstart, bend;
	bitpattern pmask, nmask, v;
	long nbits = shape_size(sh(e));
	long boff = bitf_posn(d);

	off = 8 *(boff / 8);
	sz = 8 *((boff + nbits - 1) / 8) + 8 - off;
	if (sz == 24) {
		sz = 32;
		off -= 8;
	}
	bstart = boff - off;
	bend = sz - nbits - bstart;

	pmask = ((msmask[nbits]) >> bstart) >> (32 - sz);
	nmask = ~pmask;

	switch (sz) {
	case 8:
		nmask &= 0xff;
		sha = scharsh;
		break;
	case 16:
		nmask &= 0xffff;
		sha = swordsh;
		break;
	default:
		sha = slongsh;
		break;
	}

	if (name(e) == int_to_bitf_tag) {
		exp s = son(e);
		if (is_o(name(s))) {
			e = s;
		} else {
			regsinproc |= regmsk(REG_D1);
			make_code(D1, stack, s);
			if (shape_size(sh(s)) < 32) {
				error(ERR_WARN, "Think again!");
			}
			e = D1.wh_exp;
		}
	}

	dest = mw(d, off);

	if (bstart == 0 && nbits == sz) {
		change_var_sh(sha, sh(e), zw(e), dest);
		return;
	}

	if ((bstart + nbits > 32) || (name(e)!= val_tag)) {
		where dd;
		bitpattern ch;
		mach_op *op1, *op2;
		dd = zw(e);
		if (whereis(dd)!= Dreg || shape_size(sh(e))!= 32) {
			change_var_sh(slongsh, sh(e), dd, D0);
			dd = D0;
		}
		op1 = operand(32L, dd);
		op2 = operand(32L, dest);
		ch = regs_changed(op2, 1);
		op2 = make_bitfield_op(op2,(int)bstart,(int)nbits);
		make_instr(m_bfins, op1, op2, ch);
		have_cond = 0;
		return;
	}

	v = (bitpattern)no(e);
	v = ((v << bend) & pmask);

	if (v == 0) {
		and(sha, mnw(nmask), dest, dest);
		return;
	}

	if (v == pmask) {
		or(sha, mnw(pmask), dest, dest);
		return;
	}

	f = ((whereis(dest) == Dreg)? dest : D0);
	and(sha, mnw(nmask), dest, f);
	or(sha, mnw(v), f, dest);
}


/*
    The value a1 of shape sha is tested to see if the bits indicated by
    the value a2 are set.  If a2 is a constant power of 2 then a bit
    test operation is used.  Otherwise a1 is anded with a2 and the
    result is stored in an unwanted D-register.
*/

void
bit_test(shape sha, where a1, where a2)
{
	long sz = shape_size(sha);
	long wh1 = whereis(a1);
	long wh2 = whereis(a2);
	if (wh2 == Value) {
		if (wh1 == External || wh1 == Parameter || wh1 == RegInd) {
			long v = nw(a2);
			if (is_pow2(v)) {
				where w;
				long n = log2(v);
				long off = sz - 8 *(1 + (n / 8));
				w = mw(a1.wh_exp, a1.wh_off + off);
				ins2n(m_btstb, n % 8, 8, w, 1);
				have_cond = 0;
				return;
			}
		}
		if (wh1 == Dreg) {
			long v = nw(a2);
			if (last_use(a1)) {
				and(sha, a2, a1, a1);
				return;
			}
			if (is_pow2(v) && sz == 32) {
				long n = log2(v);
				ins2n(m_btstl, n, sz, a1, 1);
				have_cond = 0;
				return;
			}
		}
	}
	if (wh1 == Dreg && last_use(a1)) {
		and(sha, a2, a1, a1);
		return;
	}
	if (wh2 == Dreg && last_use(a2)) {
		and(sha, a1, a2, a2);
		return;
	}
	move(sha, a1, D0);
	and(sha, a2, D0, D0);
}
