/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* operators.c
	produces code for common operations
*/

#include <stdlib.h>

#include <shared/bool.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include "code_here.h"
#include "addr.h"
#include "inst_fmt.h"
#include "move.h"
#include "getregs.h"
#include "guard.h"
#include "bits.h"
#include "mips_ins.h"
#include "ops.h"
#include "pseudo.h"

static void
tidyshort(int r, shape s, char* ins)
{
	/* corrects possible overflows of chars and shorts in reg r */
	int sz = shape_size(s);
	if (sz == 32) {
		return;
	}

	if (!is_signed(s)) {
		rri_ins(i_and, r, r, (1 << sz) - 1);
	} else if (ins == i_not || ins == i_nor) {
		rri_ins(i_sll, r, r, 32 - sz);
		rri_ins(i_sra, r, r, 32 - sz);
	}
}

/*
 * Given a list of expressions seq which contains one whose value is in
 * register reg, removes that exp from seq and delivers true;
 * otherwise delivers false
 */
static bool
regremoved(exp * seq, int reg)
{
	exp s = *seq;
	exp t = next(s);

	if (abs(regofval(s)) == reg) {
		*seq = t;
		return true;
	}

	for (;;) {
		if (abs(regofval(t)) == reg) {
			next(s) = next(t);
			if (t->last) {
				s->last = true;
			}

			return true;
		}

		if (t->last) {
			return 0;
		}

		s = t;
		t = next(t);
	}
}

/*
 * Evaluates the fixed operation seq1 rins seq 2 rins....,
 * into reg final, using sp as free t-regs
 */
static void
do_comm(exp seq, space sp, int final, char *rins)
{
	space nsp;
	int r = 0;
	int a1, a2;

	a1 = reg_operand(seq, sp);

	/* evaluate 1st operand into a1 */
	for (;;) {
		nsp = guardreg(a1, sp);
		seq = next(seq);

		if (seq->tag == val_tag) {/* next operand is a constant */
			if (seq->last) {
				rri_ins(rins, final, a1, no(seq));
				return;
			} else {
				if (r == 0) {
					r = getreg(sp.fixed);
				}
				rri_ins(rins, r, a1, no(seq));
			}
		} else {
			exp sq = seq;
			char *ins = rins;
			a2 = reg_operand(sq, nsp);
			/* evaluate next operand */
			if (seq->last) {
				rrr_ins(ins, final, a1, a2);
				return;
			} else {
				if (r == 0) {
					r = getreg(sp.fixed);
				}
				rrr_ins(ins, r, a1, a2);
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
comm_op(exp e, space sp, where d, char *rrins)
{
	char *rins = rrins;

	switch (d.answhere.discrim) {
	case inreg: {
		int dest = regalt(d.answhere);
		bool usesdest = regremoved(&child(e), dest);
		exp seq = child(e);

		/*
		 * The destination is in a register;
		 * take care that we dont alter it before possible use as an operand.
		 */
		if (usesdest && seq->last) {
			/* it was used, but there is only one other operand */
			if (seq->tag == val_tag) {
				rri_ins(rins, dest, dest, no(seq));
			} else {
				rrr_ins(rins, dest, dest, reg_operand(seq, sp));
			}
			tidyshort(dest, sh(e), rins);
			return dest;
		} else if (usesdest) {
			/* it was used so ... */
			int r = getreg(sp.fixed);
			do_comm(seq, sp, r, rins);
			/* ... evaluate the remainder of the expression into r... */
			rrr_ins(rins, dest, dest, r);
			/* ... and do dest = dest rins r */
			tidyshort(dest, sh(e), rins);
			return dest;
		} else {		/* ... it wasn't used */
			do_comm(seq, sp, dest, rins);
			tidyshort(dest, sh(e), rins);
			return dest;
		}
	}

	default: {
		ans a;
		int   r = getreg(sp.fixed);
		space nsp;
		bool rok = 1;
		setregalt(a, r);
		do_comm(child(e), sp, r, rins);

		/* evaluate the expression into r ... */
		if (d.answhere.discrim != notinreg) {
			tidyshort(r, sh(e), rins);
		} else {
			rok = shape_size(sh(e)) == 32;
		}

		nsp = guardreg(r, sp);
		move(a, d, nsp, 1);
		/* ... and move into a */
		return rok ? r : NOREG;
	}
	}
}

/*
 * Evalate binary operation e with rins into dest
 */
int
non_comm_op(exp e, space sp, where dest, char *rins)
{
	exp l = child(e);
	exp r = next(l);
	int a1 = reg_operand(l, sp);
	int a2;
	space nsp;
	char *ins = rins;

	nsp = guardreg(a1, sp);
	a2  = reg_operand(r, nsp);

	/* regs a1 and a2 contain the operands */
	switch (dest.answhere.discrim) {
	case inreg: {
		/* destination in register */
		int d = regalt(dest.answhere);
		rrr_ins(ins, d, a1, a2);
		tidyshort(d, sh(e), rins);
		return d;
	}

	default: {
		/* destination elsewhere */
		ans a;
		int r1 = getreg(nsp.fixed);
		int rok = 1;
		setregalt(a, r1);
		rrr_ins(ins, r1, a1, a2);

		if (dest.answhere.discrim != notinreg) {
			tidyshort(r1, sh(e), rins);
		} else {
			rok = shape_size(sh(e)) == 32;
		}

		nsp = guardreg(r1, sp);
		move(a, dest, nsp, 1);
		return rok ? r1 : NOREG;
	}
	}
}

/*
 * Evaluate fixed monadic operation e using ins into dest
 */
int
monop(exp e, space sp, where dest, char *ins)
{
	int r1 = getreg(sp.fixed);
	int a1 = reg_operand(child(e), sp);

	/* operand in reg a1 */
	space nsp;
	switch (dest.answhere.discrim) {
	case inreg: {
		/* destination in register */
		int d = regalt(dest.answhere);
		mon_ins(ins, d, a1);
		tidyshort(d, sh(e), ins);
		return d;
	}

	default: {
		/* destination elsewhere */
		ans a;
		int rok = 1;
		setregalt(a, r1);
		mon_ins(ins, r1, a1);

		if (dest.answhere.discrim != notinreg) {
			tidyshort(r1, sh(e), ins);
		} else {
			rok = shape_size(sh(e)) == 32;
		}

		nsp = guardreg(r1, sp);
		move(a, dest, nsp, 1);
		return rok ? r1 : NOREG;
	}
	}
}

int
fop(exp e, space sp, where dest, char *ins)
{
	/* evaluate floating dyadic operation e
	   using ins into dest */
	exp l = child(e);
	exp r = next(l);
	int a1, a2;
	space nsp;
	freg fr;

	if (IsRev(e)) {
		a2 = freg_operand(r, sp);
		nsp = guardfreg(a2, sp);
		a1 = freg_operand(l, nsp);
	} else {
		a1 = freg_operand(l, sp);
		nsp = guardfreg(a1, sp);
		a2 = freg_operand(r, nsp);
	}

	if (!optop(e)) {
		setnoreorder();
	}

	switch (dest.answhere.discrim) {
	case infreg: {
		/* dest in register */
		fr = fregalt(dest.answhere);
		rrrfp_ins(ins, fr.fr << 1, a1 << 1, a2 << 1);
		break;
	}

	default: {
		/* destinationelsewhere */
		ans a;
		int   r1 = getfreg(nsp.flt);
		fr.fr = r1;
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt(a, fr);
		rrrfp_ins(ins, r1 << 1, a1 << 1, a2 << 1);
		move(a, dest, sp, 1);
	}
	}

	if (!optop(e)) {
		setreorder();
	}

	return fr.dble ? -(fr.fr + 32) : (fr.fr + 32);
}

/*
 * Evaluate floating monadic operation e using ins into dest
 */
int
fmop(exp e, space sp, where dest, char *ins)
{
	int a1 = freg_operand(child(e), sp);
	freg fr;

	if (!optop(e)) {
		setnoreorder();
	}

	switch (dest.answhere.discrim) {
	case infreg: {
		fr = fregalt(dest.answhere);
		rrfp_ins(ins, fr.fr << 1, a1 << 1);
		break;
	}

	default: {
		ans a;

		fr.fr = getfreg(sp.flt);
		fr.dble = dest.ashwhere.ashsize == 64 ? 1 : 0;

		setfregalt(a, fr);
		rrfp_ins(ins, fr.fr << 1, a1 << 1);
		move(a, dest, sp, 1);
	}
	}

	if (!optop(e)) {
		setreorder();
	}

	return fr.dble ? -(fr.fr + 32) : (fr.fr + 32);
}

