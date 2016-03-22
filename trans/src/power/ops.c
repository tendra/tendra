/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

#include <utility/max.h>

#include <main/flags.h>

#include "bitsmacs.h"
#include "procrec.h"
#include "geninst.h"
#include "instruct.h"
#include "proc.h"
#include "ops.h"
#include "make_code.h"
#include "error.h"
#include "locate.h"
#include "guard.h"

static void
tidyshort(int r, exp e)
{
	shape s = sh(e);

	switch (e->tag) {
	case and_tag: {
		exp r = bro(son(e)); /* could be a val_tag */

		if (s->tag == ucharhd && r->tag == val_tag && ((no(r) & 0xff  ) == no(r))) {
			return;
		}

		if (s->tag == uwordhd && r->tag == val_tag && ((no(r) & 0xffff) == no(r))) {
			return;
		}
	}
	}

	if (s->tag == ucharhd) {
		rir_ins(i_and, r, 0xff,   r);
	} else if (s->tag == uwordhd) {
		rir_ins(i_and, r, 0xffff, r);
	}
}

/*
 * given a list of expressions seq which contains one whose value is in
 * register reg, removes that exp from seq and delivers true;
 * otherwise delivers false
 */
static bool
regremoved(exp * seq, int reg)
{
	exp s = *seq;
	exp t = bro(s);

	if (ABS(regofval(s)) == reg) {
		*seq = t;
		return true;
	}

	for (;;) {
		if (ABS(regofval(t)) == reg) {
			bro(s) = bro(t);
			if (t->last) {
				s->last = true;
			}

			return true;
		}

		if (t->last) {
			return false;
		}

		s = t;
		t = bro(t);
	}
}

/*
 * evaluates the fixed operation seq1 rins seq 2 rins...., into reg final,
 * using sp as free t-regs
 */
static void
do_comm(exp seq, space sp, int final, Instruction_P rins)
{
	int r = 0;
	space nsp;
	int a1;
	int a2;

	/* should have been optimised in scan... */
	assert(!(rins == i_a && seq->tag == neg_tag && bro(seq)->tag != val_tag));

	/* evaluate 1st operand into a1 */
	a1 = reg_operand(seq, sp);

	for (;;) {
		nsp = guardreg(a1, sp);
		seq = bro(seq);

		if (seq->tag == val_tag) {	/* next operand is a constant */
			if (seq->last) {
				rir_ins(rins, a1, no(seq), final);
				return;
			} else {
				if (r == 0) {
					r = getreg(sp.fixed);
				}
				rir_ins(rins, a1, no(seq), r);
			}
		} else {
			exp sq = seq;
			Instruction_P ins = rins;

			a2 = reg_operand(sq, nsp);
			/* evaluate next operand */
			if (seq->last) {
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
}

/*
 * Evaluate commutative operation rrins given by e into d,
 * using sp to get t-regs
 */
int
comm_op(exp e, space sp, where d, Instruction_P rrins)
{
	Instruction_P rins = rrins;

	switch (d.answhere.discrim) {
	case inreg: {
		int dest = regalt(d.answhere);
		bool usesdest = regremoved(&son(e), dest);
		exp seq = son(e);

		/*
		 * the destination is in a register; take care that we don't alter it
		 * before possible use as an operand ....
		 */
		if (usesdest && seq->last) {
			/* used, but there is only one other operand */
			if (seq->tag == val_tag) {
				rir_ins(rins, dest, no(seq), dest);
			} else {
				rrr_ins(rins, dest, reg_operand(seq, sp), dest);
			}
			tidyshort(dest, e);
			return dest;
		} else if (usesdest) {
			/* dest used, use temp */
			int r = getreg(sp.fixed);

			do_comm(seq, sp, r, rins);
			rrr_ins(rins, dest, r, dest);
			tidyshort(dest, e);
			return dest;
		} else {
			/* dest not used, evaluate into dest */
			do_comm(seq, sp, dest, rins);
			tidyshort(dest, e);
			return dest;
		}
	}

	default: {
		ans a;
		int r = getreg(sp.fixed);
		space nsp;
		bool rok = 1;
		setregalt(a, r);
		do_comm(son(e), sp, r, rins);

		/* Evaluate the expression into r */
		if (d.answhere.discrim != notinreg) {
			tidyshort (r, e);
		} else {
			rok = shape_size(sh(e)) == 32;
		}
		nsp = guardreg(r, sp);
		move(a, d, nsp.fixed, 1);

		/* ... and move into a */
		return rok ? r : NOREG;
		}
	}
}

/* Evalate binary operation e with ins into dest */
int
non_comm_op(exp e, space sp, where dest, Instruction_P ins)
{
	exp l = son(e);
	exp r = bro(l);

	/* we can use sfi instruction */
	bool sf_imm = l->tag == val_tag && ins == i_s && IMM_SIZE(no(l));

	int a1;
	int a2;
	space nsp;

	switch (dest.answhere.discrim) {
	case inreg: {
		int d = regalt(dest.answhere);

		if (sf_imm) {
			rir_ins(i_sf, reg_operand(r, sp), no(l), d);
		} else {
			a1 = reg_operand(l, sp);
			nsp = guardreg(a1, sp);
			a2 = reg_operand(r, nsp);
			rrr_ins(ins, a1, a2, d);
		}

		tidyshort(d, e);
		return d;
	}

	default: {
		/* destination elsewhere */
		ans a;
		int r1 = getreg(sp.fixed);

		setregalt(a, r1);

		if (sf_imm) {
			rir_ins(i_sf, reg_operand(r, sp), no(l), r1);
		} else {
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

/*
 * Evaluate floating dyadic operation e using ins into dest
 */
int
fop(exp e, space sp, where dest, Instruction_P ins)
{
	exp l = son(e);
	exp r = bro(l);
	int a1;
	int a2;
	space nsp;

	if (IsRev(e)) {
		a2 = freg_operand(r, sp,  getfreg(sp.flt));
		nsp = guardfreg(a2, sp);
		a1 = freg_operand(l, nsp, getfreg(nsp.flt));
	} else {
		a1 = freg_operand(l, sp,  getfreg(sp.flt));
		nsp = guardfreg(a1, sp);
		a2 = freg_operand(r, nsp, getfreg(nsp.flt));
	}

	switch (dest.answhere.discrim) {
	case infreg: {
		/* dest in register */
		freg fr;

		fr = fregalt(dest.answhere);
		if (ERROR_TREATMENT(e)) {
			do_fop_error_jump(e, a1, a2, fr.fr); /* Floating point error jump */
		} else {
			rrrf_ins(ins, a1, a2, fr.fr);
		}

		if (fr.dble == 0 && round_after_flop) {
			rrf_ins(i_frsp, fr.fr, fr.fr);
		}

		return fr.dble ? -(fr.fr + 32) : (fr.fr + 32);
	}

	default: {
		/* destination elsewhere */
		ans a;
		freg fr;
		int r1 = getfreg(nsp.flt);

		fr.fr = r1;
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt(a, fr);

		if (ERROR_TREATMENT(e)) {
			do_fop_error_jump(e, a1, a2, fr.fr); /* Floating point error jump */
		} else {
			rrrf_ins(ins, a1, a2, r1);
		}

		if (fr.dble == 0 && round_after_flop) {
			rrf_ins(i_frsp, r1, r1);
		}

		move(a, dest, sp.fixed, 1);
		return (fr.dble) ? -(fr.fr + 32) : (fr.fr + 32);
	}
	}
}

/*
 * Evaluate floating monadic operation e using ins into dest
 */
int
fmop(exp e, space sp, where dest, Instruction_P ins)
{
	int a1 = freg_operand(son(e), sp, getfreg(sp.flt));

	switch (dest.answhere.discrim) {
	case infreg: {
		freg fr;

		fr = fregalt(dest.answhere);
		if (ERROR_TREATMENT(e)) {
			do_fmop_error_jump(e, a1, fr.fr);
		} else {
			rrf_ins(ins, a1, fr.fr);
		}

		if (fr.dble == 0 && round_after_flop) {
			rrf_ins(i_frsp, fr.fr, fr.fr);
		}

		return (fr.dble ? -(fr.fr + 32) : (fr.fr + 32));
	}

	default: {
		ans a;
		freg fr;

		fr.fr = getfreg(sp.flt);
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt(a, fr);

		if (ERROR_TREATMENT(e)) {
			do_fmop_error_jump(e, a1, fr.fr);
		} else {
			rrf_ins(ins, a1, fr.fr);
		}

		if (fr.dble == 0 && round_after_flop) {
			rrf_ins(i_frsp, fr.fr, fr.fr);
		}

		move(a, dest, sp.fixed, 1);
		return (fr.dble ? -(fr.fr + 32) : (fr.fr + 32));
	}
	}
}

