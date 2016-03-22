/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/install_fns.h>
#include <construct/exp.h>

#include <utility/max.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "procrec.h"
#include "code_here.h"
#include "addrtypes.h"
#include "inst_fmt.h"
#include "move.h"
#include "getregs.h"
#include "guard.h"
#include "bitsmacs.h"
#include "reg.h"
#include "regexps.h"
#include "locate.h"
#include "eval.h"
#include "muldvrem.h"
#include "proc.h"
#include "labels.h"
#include "ops.h"

/*
 * Correct possible overflows in register r
 */
static void
tidyshort
(int r, shape s)
{
	if (s->tag == ucharhd) {
		rir_ins(i_and, r, 0xff,   r);
	} else if (s->tag == uwordhd) {
		rir_ins(i_and, r, 0xffff, r);
	}
}

/*
  REMOVE AN EXPRESSION CONTAINING A REGISTER
  Given a list of expressions, seq, find one whose value is in
  register reg.  If this is found, it is removed from seq and 1
  is returned.  Otherwise 0 is returned.
*/
static bool
regremoved(exp * seq, int reg )
{
	exp s = *seq;
	exp t = bro(s);

	if (ABS(regofval(s)) == reg) {
		( *seq)= t;
		return 1;
	}

	for (;;) {
		if (ABS(regofval(t)) == reg) {
			bro(s)= bro(t);
			if (t -> last) {
				s ->last = true;
			}
			return 1;
		}

		if (t -> last) {
			return 0;
		}

		s = t;
		t = bro(t);
	}

	UNREACHED;
}

/*
 * Evaluate a commutative operation
 *
 * Evaluates reg = seq_1 @ seq_2 @ ... where @ is a binary commutative
 * operation given by rins.  sp may be used for free t-registers.
 */
static void
do_comm(exp seq, space sp, int final, ins_p rins )
{
	int r = 0;
	space nsp;
	int a1, a2;

	/* should have been optimised in scan... */
	assert(!( rins == i_add && seq->tag == neg_tag && bro(seq)-> tag != val_tag));

	/* evaluate first operand into a1 */
	a1 = reg_operand(seq, sp);

	for (;;) {
		nsp = guardreg(a1, sp);
		seq = bro(seq);

		if (seq->tag == val_tag) {
			/* next operand is a constant */
			if (seq -> last) {
				rir_ins(rins, a1, (long) no(seq), final);
				return;
			} else {
				if (r == 0) {
					r = getreg(sp.fixed);
				}
				rir_ins(rins, a1, (long) no(seq), r);
			}
		} else {
			/* evaluate next operand */
			exp sq = seq;
			ins_p ins = rins;
			a2 = reg_operand(sq, nsp);

			if (seq -> last) {
				rrr_ins(ins, a1, a2, final);
				return;
			} else {
				if (r == 0) {
					r = getreg(sp.fixed);
				}
				rrr_ins(ins, a1, a2, r);
			}
		}
		a1 = r;
	}

	UNREACHED;
}

/*
 * Evaluate a commutative operation
 *
 * The commutative operation, rrins, given by e is evaluated into d,
 * using sp to get free t-registers.
 */
int
comm_op(exp e, space sp, where d, ins_p rrins )
{
	ins_p rins = rrins;

	switch (discrim(d.answhere)) {
	case inreg: {
		int dest = regalt(d.answhere);
		bool usesdest = regremoved(&son(e), dest);
		exp seq = son(e);

		if (dest == R_G0) {
			dest = getreg(sp.fixed);
		}

		/* the destination is in a register, take care that we don't
		alter it before possible use as an operand ... */
		if (usesdest && seq -> last) {
			/* used, but there is only one other operand */
			if (seq->tag == val_tag) {
				rir_ins(rins, dest, (long) no(seq), dest);
			} else {
				rrr_ins(rins, dest, reg_operand(seq, sp), dest);
			}

			if (optop(e)) {
				tidyshort(dest, sh(e));
			}
			return dest;
		} else if (usesdest) {
			/* dest used, use temp */
			int r = getreg(sp.fixed);
			do_comm(seq, sp, r, rins);
			rrr_ins(rins, dest, r, dest);

			if (optop(e)) {
				tidyshort(dest, sh(e));
			}
			return dest;
		} else {
			/* dest not used, evaluate into dest */
			do_comm(seq, sp, dest, rins);
			if (optop(e)) {
				tidyshort(dest, sh(e));
			}
			return dest;
		}
	}

	default: {
		ans a;
		space nsp;
		int r = getreg(sp.fixed);

		setregalt(a, r);

		/* Evaluate the expression into r */
		do_comm(son(e), sp, r, rins);
		if (optop(e)) {
			tidyshort(r, sh(e));
		}

		nsp = guardreg(r, sp);
		/* ... and move into a */
		(void) move(a, d, nsp.fixed, 1);
		return r;
	}
	}

	UNREACHED;
}

/*
 * Evaluate a non-commutative operation
 *
 * The non-commutative operation, rins, given by e is evaluated
 * into dest, using sp to get free t-registers.
 */
int
non_comm_op(exp e, space sp, where dest, ins_p rins )
{
	exp l = son(e);
	exp r = bro(l);
	space nsp;

	int a1 = reg_operand(l, sp), a2;
	nsp = guardreg(a1, sp);
	a2 = reg_operand(r, nsp);

	switch (discrim(dest.answhere)) {
	case inreg: {
		int d = regalt(dest.answhere);
		if (d == R_G0) {
			d = getreg(sp.fixed);
		}

		rrr_ins(rins, a1, a2, d);
		if (optop(e)) {
			tidyshort(d, sh(e));
		}

		return d;
	}

	default: {
		ans a;
		int r1 = getreg(nsp.fixed);
		setregalt(a, r1);
		rrr_ins(rins, a1, a2, r1);

		if (optop(e)) {
			tidyshort(r1, sh(e));
		}

		nsp = guardreg(r1, sp);
		(void) move(a, dest, nsp.fixed, 1);
		return r1;
	}
	}

	UNREACHED;
}

/*
 * Evaluate a monadic operation
 *
 * The monadic operation, ins, given by e is evaluated into dest,
 * using sp to get free t-registers.
 */
int
monop(exp e, space sp, where dest, ins_p ins )
{
	int r1 = getreg(sp.fixed);
	int a1 = reg_operand(son(e), sp);

	switch (discrim(dest.answhere)) {
	case inreg: {
		int d = regalt(dest.answhere);
		if (d == R_G0) {
			d = getreg(sp.fixed);
		}

		rr_ins(ins, a1, d);
		if (optop(e)) {
			tidyshort(d, sh(e));
		}

		return d;
	}

	default: {
		ans a;
		space nsp;

		setregalt(a, r1);
		rr_ins(ins, a1, r1);
		if (optop(e)) {
			tidyshort(r1, sh(e));
		}

		nsp = guardreg(r1, sp);
		(void) move(a, dest, nsp.fixed, 1);
		return r1;
	}
	}

	UNREACHED;
}

/*
 * evaluate abs operation as
 *     move a1 -> d
 *     subcc %g0, a1 -> R_TMP
 *     bpos,a L
 *     move R_TMP -> d
 * L:
 */
int
absop(exp e, space sp, where dest )
{
	int r1  = getreg(sp.fixed);
	int a1  = reg_operand(son(e), sp);
	int lab = new_label();

	switch (discrim(dest.answhere)) {
	case inreg: {
		int d = regalt(dest.answhere);
		if (d == R_G0) {
			d = getreg(sp.fixed);
		}

		rr_ins(i_mov, a1, d);
		rrr_ins(i_subcc, R_G0, a1, R_TMP);
		br_abs(lab);
		rr_ins( i_mov, R_TMP, d);
		set_label(lab);

		if (optop(e)) {
			tidyshort(d, sh(e));
		}

		return d;
	}

	default: {
		ans a;
		space nsp;

		setregalt(a, r1);
		rr_ins(i_mov, a1, r1);
		rrr_ins(i_subcc, R_G0, a1, R_TMP);
		br_abs(lab);
		rr_ins( i_mov, R_TMP, r1);
		set_label(lab);

		if (optop(e)) {
			tidyshort(r1, sh(e));
		}

		nsp = guardreg(r1, sp);
		(void) move(a, dest, nsp.fixed, 1);
		return r1;
	}
	}

	UNREACHED;
}

/*
 * Get the address of a long double
 */
static void
quad_addr(exp e, int r, space sp )
{
	instore is;

	if (e->tag == real_tag) {
		is = evaluated(e, 0, 1);
	} else {
		where w;
		w = locate1(e, sp, sh(e), 0);

		if (discrim(w.answhere)!= notinreg) {
			error(ERR_SERIOUS,  "Illegal expression in quad_addr");
		}
		is = insalt(w.answhere);
	}

	if (is.adval) {
		error(ERR_SERIOUS,  "Illegal expression in quad_addr");
	}

	if (IS_FIXREG(is.b.base)) {
		if (is.b.offset == 0) {
			if (is.b.base != r) {
				rr_ins(i_mov, is.b.base, r);
			}
		} else {
			rir_ins(i_add, is.b.base, is.b.offset, r);
		}
	} else {
		set_ins(is.b, r);
	}
}

/*
 * Do a long double operation
 */
void
quad_op(exp a1, exp a2, space sp, where dest, int op )
{
	char *s;
	bool quad_ret = true;

	if (op < 0) {
		/* Test operations */
		quad_ret = false;
		switch (-op) {
		case 1: s = "_Q_fle,2"; break;
		case 2: s = "_Q_flt,2"; break;
		case 3: s = "_Q_fge,2"; break;
		case 4: s = "_Q_fgt,2"; break;
		case 5: s = "_Q_fne,2"; break;
		case 6: s = "_Q_feq,2"; break;

		default :
			error(ERR_SERIOUS,  "Illegal floating-point test");
		}
	} else {
		/* Binary operations */
		switch (op) {
		case fplus_tag:  s = "_Q_add,2";                    break;
		case fminus_tag: s = "_Q_sub,2";                    break;
		case fmult_tag:  s = "_Q_mul,2";                    break;
		case fdiv_tag:   s = "_Q_div,2";                    break;
		case fneg_tag:   s = "_Q_neg,1";                    break;
		case chfl_tag:   s = "_Q_stoq,1";                   break;
		case float_tag:  s = "_Q_itoq,1";                   break;
		case 100:        s = "_Q_qtod,1"; quad_ret = false; break;
		case 101:        s = "_Q_qtos,1"; quad_ret = false; break;

		/*
		 * Special case: there is no special operation for this,
		 * so it has to be performed by a code sequence
		 */
		case fabs_tag:
			error(ERR_SERIOUS, "No operation for fabs(long double)");
			s = "_Q_abs,1";
			break;

		default :
			error(ERR_SERIOUS,  "Illegal floating-point operation");
		}
	}

	if (quad_ret) {
		instore is;
		baseoff ret_addr;
		ret_addr.base = R_SP;
		ret_addr.offset = 16 * 4;
		is = insalt(dest.answhere);

		if (discrim(dest.answhere)!= notinreg) {
			is.b = mem_temp(0);
			is.adval = 1;
			/* error(ERR_SERIOUS,  "Illegal expression in quad_op"); */
		}

		if (is.adval) {
			if (IS_FIXREG(is.b.base)) {
				if (is.b.offset == 0) {
					st_ro_ins(i_st, is.b.base, ret_addr);
				} else {
					rir_ins(i_add, is.b.base, is.b.offset, R_TMP);
					st_ro_ins(i_st, R_TMP, ret_addr);
				}
			} else {
				set_ins(is.b, R_TMP);
				st_ro_ins(i_st, R_TMP, ret_addr);
			}
		} else {
			ld_ins(i_ld, is.b, R_TMP);
			st_ro_ins(i_st, R_TMP, ret_addr);
		}
	}

	/* hack for float integer */
	if (op == float_tag) {
		int r = reg_operand(a1, sp);

		if (sh(a1)-> tag == ulonghd) {
			s = "_Q_utoq,1";
		}

		if (r != R_O0) {
			rr_ins(i_mov, r, R_O0);
		}

		a1 = NULL;
	}

	/* hack for change floating variety */
	if (op == chfl_tag) {
		ans aa;
		where w;
		freg frg;
		frg.fr = getfreg(sp.flt);

		if (sh(a1)-> tag == realhd) {
			s = "_Q_dtoq,1";
			frg.dble = 1;
		} else {
			frg.dble = 0;
		}

		setfregalt(aa, frg);
		w.answhere = aa;
		w.ashwhere = ashof(sh(a1));
		(void) code_here(a1, sp, w);

		if (frg.dble) {
			stf_ins(i_std, frg.fr << 1, mem_temp(0));
			ld_ro_ins(i_ld, mem_temp(0), R_O0);
			ld_ro_ins(i_ld, mem_temp(4), R_O1);
		} else {
			stf_ins(i_st, frg.fr << 1, mem_temp(0));
			ld_ro_ins(i_ld, mem_temp(0), R_O0);
		}

		a1 = NULL;
	}

	/* put the arguments into the call registers */
	if (a1 != NULL) {
		quad_addr(a1, R_O0, sp);
		if (a2 != NULL) {
			sp = needreg(R_O0, sp);
			quad_addr(a2, R_O1, sp);
		}
	}

	/* output the actual call */
	asm_printop("call %s", s);
	asm_printop("nop");
	if (quad_ret) {
		asm_printop("unimp 16");
	}

	clear_all();
}

/*
 * Evaluate a floating point operation
 *
 * The floating point operation, ins, given by e is evaluated
 * into dest, using sp to get free t-registers.
 */
int
fop(exp e, space sp, where dest, ins_p ins )
{
	exp l = son(e);
	exp r = bro(l);
	space nsp;
	int a1, a2;

	if ((has & HAS_LONG_DOUBLE) && sh(e)-> tag == doublehd) {
		if (IsRev(e)) {
			quad_op(r, l, sp, dest, (int) e->tag);
		} else {
			quad_op(l, r, sp, dest, (int) e->tag);
		}

		return NOREG;
	}

	if (IsRev(e)) {
		/* reverse operands */
		a2 = freg_operand(r, sp, getfreg(sp.flt));
		nsp = guardfreg(a2, sp);
		a1 = freg_operand(l, nsp, getfreg(nsp.flt));
	} else {
		a1 = freg_operand(l, sp, getfreg(sp.flt));
		nsp = guardfreg(a1, sp);
		a2 = freg_operand(r, nsp, getfreg(nsp.flt));
	}

	switch (discrim(dest.answhere)) {
	case infreg: {
		freg fr;
		fr = fregalt(dest.answhere);
		rrrf_ins(ins, a1 << 1, a2 << 1, fr.fr << 1);
		return fr.dble ? -(fr.fr + 32) : (fr.fr + 32);
	}

	default: {
		ans a;
		freg fr;
		int r1 = getfreg(nsp.flt);
		fr.fr = r1;
		fr.dble = (bool) ((dest.ashwhere.ashsize == 64)? 1 : 0);
		setfregalt(a, fr);
		rrrf_ins(ins, a1 << 1, a2 << 1, r1 << 1);
		(void) move(a, dest, sp.fixed, 1);
		return fr.dble ? -(fr.fr + 32):(fr.fr + 32);
	}
	}

	UNREACHED;
}

