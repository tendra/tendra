/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <local/ash.h>
#include <local/exp.h>

#include <reader/exp.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/me_fns.h>

#include <flpt/flpt.h>

#include <utility/bits.h>
#include <utility/max.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "mach.h"
#include "where.h"
#include "codec.h"
#include "make_code.h"
#include "ops.h"
#include "mach.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "eval.h"
#include "ops_shared.h"
#include "mach_ins.h"

extern bool have_cond;

/*
 * This routine, given a where, copies the corresponding exp, and sets
 * its sh equal to the given shape.
 */
exp
sim_exp(shape sha, where w)
{
	exp e = copyexp(w.wh_exp);
	sh(e) = sha;
	return e;
}

/*
 * This routine processes the unary operation described by the routine op.
 * The operand is given by a and the result, which is of shape sha,
 * is put into dest.  The stack argument describes the current
 * state of the stack.
 */
static void
uop(void(*op)(shape, where, where), shape sha, exp a, where dest, ash stack)
{
	int old_rmode;

	/*
	 * If a is not an operand, we need to calculate its value first.
	 */
	if (!is_o(a->tag)) {
		if (whereis(dest) == Dreg) {
			/* If dest is in a D register, code a into dest */
			old_rmode = crt_rmode;
			make_code(dest, stack, a);
			crt_rmode = old_rmode;
			/* Now apply op to dest */
			(*op)(sha, dest, dest);
		} else {
			/* Code a into D1 */
			where w;
			exp e = sim_exp(sha, D1);
			w = zw(e);
			regsinproc |= regmsk(REG_D1);
			old_rmode = crt_rmode;
			make_code(w, stack, a);
			crt_rmode = old_rmode;
			/* Apply op to D1 */
			(*op)(sha, w, dest);
			retcell(e);
			if (have_cond == 3) {
				have_cond = 1;
			}
		}

		return;
	}

	/* If a is an operand, apply op directly to a */
	(*op)(sha, zw(a), dest);
}

/*
 * This routine processes the binary operation described by the routine op.
 * The operands are given by a and b and the result, which is of shape sha,
 * is put into dest. The stack argument describes the current state of the stack.
 */
static void
bop(void(*op)(shape, where, where, where), shape sha, exp a, exp b, where dest,
    ash stack)
{
	where w, t;
	bool noa = !is_o(a->tag);
	bool nob = !is_o(b->tag);

	/*
	 * If a is not an operand, we need to calculate its value first.
	 */
	if (noa) {
		if (nob) {
			/* a and b cannot both not be operands */
			error(ERR_SERIOUS, "Illegal binary operation");
		}

		t = zw(b);
		if (whereis(dest) == Dreg && !interfere(dest, t)) {
			/*
			 * If dest is in a D register which is not used in b,
			 * code a into dest.
			 */
			make_code(dest, stack, a);
			/* Apply op to dest and b */
			(*op)(sha, dest, t, dest);
		} else {
			/* Code a into D1 */
			exp e = sim_exp(sha, D1);
			w = zw(e);
			regsinproc |= regmsk(REG_D1);
			make_code(w, stack, a);
			/* Apply op to D1 and b */
			(*op)(sha, w, t, dest);
			retcell(e);
			if (have_cond == 3) {
				have_cond = 1;
			}
		}

		return;
	}

	/*
	 * If b is not an operand, we need to calculate its value first.
	 */
	if (nob) {
		t = zw(a);
		if (whereis(dest) == Dreg && !interfere(dest, t)) {
			/*
			 * If dest is in a D register which is not used in a,
			 * code b into dest.
			 */
			make_code(dest, stack, b);
			/* Apply op to a and dest */
			(*op)(sha, t, dest, dest);
		} else {
			/* Code b into D1 */
			exp e = sim_exp(sha, D1);
			w = zw(e);
			regsinproc |= regmsk(REG_D1);
			make_code(w, stack, b);
			/* Apply op to a and D1 */
			(*op)(sha, t, w, dest);
			retcell(e);
			if (have_cond == 3) {
				have_cond = 1;
			}
		}

		return;
	}

	/* If a and b are both operands, apply op directly */
	(*op)(sha, zw(a), zw(b), dest);
}

/*
 * This routine processes the logical operation described by the routine op.
 * This operation will be binary, commutative and associative. The operands
 * are given by the bro-list starting at the son of e.
 * The result is put into dest.  The stack argument describes the current
 * state of the stack.
 */
static void
logop(void(*op)(shape, where, where, where), exp e, where dest, ash stack)
{
	exp arg1 = son(e);    /* First argument */
	exp arg2 = bro(arg1); /* Second argument */
	exp t, u, v;
	where w;

	if (arg1->last) {
		/* If there is of one argument, code it into dest */
		make_code(dest, stack, arg1);
		return;
	}

	if (arg2->last) {
		/* If there are two arguments, use bop */
		bop(op, sh(e), arg1, arg2, dest, stack);
		return;
	}

	/*
	 * Three or more arguments: need to take care about overlap between
	 * dest and args, so use D1.
	 */

	regsinproc |= regmsk(REG_D1);
	v = sim_exp(sh(e), D1);
	w = zw(v);
	t = arg1;

	/*
	 * Scan the arguments. t will hold either the first non-operand,
	 * or NULL if all the arguments are operands.  There should be
	 * at most one non-operand.
	 */
	for (;;) {
		if (!is_o(t->tag)) {
			break;
		}

		if (t->last) {
			t = NULL;
			break;
		}

		t = bro(t);
	}

	/*
	 * Deal with the case where all the arguments are operands. This does:
	 * D1 = op(arg1, arg2)
	 * D1 = op(arg3, D1)
	 * D1 = op(arg4, D1)
	 * ....................
	 * dest = op (argn, D1)
	 */
	if (t == NULL) {
		/* Process the first two terms */
		(*op)(sh(e), zw(arg1), zw(arg2), w);
		t = bro(arg2);
		while (!t->last) {
			/* Process the third, fourth, ... terms */
			(*op)(sh(e), zw(t), w, w);
			t = bro(t);
		}

		/* Process the last term */
		reuseables |= regmsk(REG_D1);
		(*op)(sh(e), zw(t), w, dest);
		reuseables &= ~regmsk(REG_D1);
		retcell(v);

		if (have_cond == 3) {
			have_cond = 1;
		}
		return;
	}

	/*
	 * Deal with the case where one argument, say arg2, is a non-operand.
	 * This does:
	 * D1 = arg2
	 * D1 = op(arg1, D1)
	 * D1 = op(arg3, D1)
	 * ....................
	 * dest = op(argn, D1)
	 */
	make_code(w, stack, t);
	u = arg1;
	for (;;) {
		if (t != u) {
			if (u->last || (bro(u) == t && bro(u)->last)) {
				(*op)(sh(e), zw(u), w, dest);
			} else {
				(*op)(sh(e), zw(u), w, w);
			}
		}

		if (u->last) {
			break;
		}

		u = bro(u);
	}
	retcell(v);

	if (have_cond == 3) {
		have_cond = 1;
	}
}

/*
 * Process add and subtract.
 *
 * This routine processes the binary operation add.  It does dest = b + a.
 * The second argument, a, may be of the form neg(a1), in which case
 * we use sub.
 */
static void
addsub(shape sha, where a, where b, where dest, ash stack)
{
	exp e = a.wh_exp;

	if (e->tag == neg_tag) {
		bop(sub, sha, son(e), b.wh_exp, dest, stack);
	} else {
		bop(add, sha, e, b.wh_exp, dest, stack);
	}
}

/*
 * Some constructs only set the overflow bit for 32 bit results.
 * This checks values of other varieties to determine whether or not an
 * overflow has occured
 */
static void
check_unset_overflow(where dest, shape shp)
{
	exp max_val = getexp(shp, NULL, 0, NULL, NULL, 0, range_max(shp), val_tag);
	exp min_val = getexp(shp, NULL, 0, NULL, NULL, 0, range_min(shp), val_tag);
	bool sw;

	move(shp, dest, D0);
	if (is_signed(shp) && (shape_size(shp) < 32)) {
		ins1((shape_size(shp) == 16) ? m_extl : m_extbl, 32, D0, 1);
	}

	sw = cmp(is_signed(shp) ? slongsh : ulongsh, D0, zw(max_val), tst_gr);
	test_overflow2(branch_ins(tst_gr, sw, is_signed(shp), is_floating(shp->tag)));

	sw = cmp(is_signed(shp) ? slongsh : ulongsh, D0, zw(min_val), tst_ls);
	test_overflow2(branch_ins(tst_ls, sw, is_signed(shp), is_floating(shp->tag)));

	kill_exp(max_val, max_val);
	kill_exp(min_val, min_val);
}

/*
 * Main operation coding routine.
 *
 * This routine creates code to evaluate e, putting the result into dest.
 * The stack argument describes the current stack position.
 */
void
codec(where dest, ash stack, exp e)
{
	if (e == NULL) {
		error(ERR_SERIOUS, "Internal coding error");
		return;
	}

	switch (e->tag) {
	case plus_tag: {
		/*
		 * Addition is treated similarly to logical operations - see
		 * the routine logop above. It takes a variable number of
		 * arguments in the form of a bro-list starting with the son of
		 * e. Each argument may be of the form neg(x).
		 */
		exp arg1 = son(e);	/* First argument */
		exp arg2 = bro(arg1);	/* Second argument */
		exp s, t, u, v;
		where w;
		int prev_ov;

		if (arg1->last) {
			/* One argument */
			make_code(dest, stack, arg1);
			return;
		}

		prev_ov = set_overflow(e);

		if (arg2->last) {
			/* Two arguments */
			addsub(sh(e), zw(arg2), zw(arg1), dest, stack);
			clear_overflow(prev_ov);
			return;
		}

		/* Three or more arguments - use D1 */
		t = arg1;
		regsinproc |= regmsk(REG_D1);
		s = sim_exp(sh(e), D1);
		w = zw(s);

		/* Look for the non-operand if there is one */
		for (;;) {
			if (!is_o(t->tag) &&
			    (t->tag != neg_tag || !is_o(son(t)->tag))) {
				break;
			}
			if (t->last) {
				t = NULL;
				break;
			}
			t = bro(t);
		}
		if (t == NULL && arg1->tag == neg_tag &&
		    arg2->tag == neg_tag) {
			t = arg1;
		}

		/* Deal with the case where all the arguments are operands */
		if (t == NULL) {
			t = bro(arg2);
			/* Deal with the first two arguments */
			if (arg1->tag == neg_tag) {
				addsub(sh(e), zw(arg1), zw(arg2),
				       ((t == e) ? dest : w), stack);
			} else {
				addsub(sh(e), zw(arg2), zw(arg1),
				       ((t == e) ? dest : w), stack);
			}
			if (t == e) {
				clear_overflow(prev_ov);
				return;
			}
			/* Deal with the third, fourth, ... arguments */
			while (!t->last) {
				u = bro(t);
				addsub(sh(e), zw(t), w, w, stack);
				t = u;
			}
			/* Deal with the last argument */
			addsub(sh(e), zw(t), w, dest, stack);
			retcell(s);
			if (have_cond == 3) {
				have_cond = 1;
			}
			clear_overflow(prev_ov);
			return;
		}

		/* Deal with the case where one argument is a non-operand */
		make_code(w, stack, t);
		u = arg1;
		for (;;) {
			v = bro(u);
			if (t != u) {
				if (u->last || (v == t && v->last)) {
					addsub(sh(e), zw(u), w, dest, stack);
				} else {
					addsub(sh(e), zw(u), w, w, stack);
				}
			}
			if (u->last) {
				break;
			}
			u = v;
		}
		retcell(s);
		if (have_cond == 3) {
			have_cond = 1;
		}
		clear_overflow(prev_ov);
		return;
	}

#ifndef tdf3
	case addptr_tag: {
		asm_comment("addptr_tag ...");
		mova(zw(e), dest);
		asm_comment("addptr_tag done");
		return;
	}
#endif

	case chvar_tag: {
		/* Change variety, the son of e, a, gives the argument */
		exp a = son(e);
		int prev_ov = set_overflow(e);
		if (!is_o(a->tag)) {
			/* If a is not an operand */
			if (whereis(dest) != Dreg) {
				/*
				 * If dest is not a D register, code a into D1.
				 */
				where w;
				exp s = sim_exp(sh(a), D1);
				w = zw(s);
				regsinproc |= regmsk(REG_D1);
				make_code(w, stack, a);
				/* Preform the change variety on D1 */
				change_var(sh(e), w, dest);
				retcell(s);
				if (have_cond == 3) {
					have_cond = 1;
				}
				clear_overflow(prev_ov);
				return;
			}
			/* If dest is a D register, code a into dest */
			make_code(dest, stack, a);
			/* Preform the change variety on dest */
			change_var_sh(sh(e), sh(a), dest, dest);
			clear_overflow(prev_ov);
			return;
		}
		/* If a is an operand, call change_var directly */
		change_var(sh(e), zw(a), dest);
		clear_overflow(prev_ov);
		return;
	}

	case minus_tag: {
		/* Minus, subtract pointer etc are binary operations */
		int prev_ov = set_overflow(e);
		bop(sub, sh(e), bro(son(e)), son(e), dest, stack);
		clear_overflow(prev_ov);
		return;
	}

#ifndef tdf3
	case make_stack_limit_tag:
#endif
	case subptr_tag:
	case minptr_tag:
		/* Minus, subtract pointer etc are binary operations */
		bop(sub, sh(e), bro(son(e)), son(e), dest, stack);
		return;

	case mult_tag: {
		/* Multiply is treated as a logical operation */
		int prev_ov = set_overflow(e);
		logop(mult, e, dest, stack);
		if (!optop(e) && (sh(e)->tag != slonghd) &&
		    (sh(e)->tag != ulonghd)) {
			check_unset_overflow(dest, sh(e));
		}
		clear_overflow(prev_ov);
		return;
	}

	case div0_tag:
	case div2_tag: {
		/* Division is a binary operation */
		int prev_ov = set_overflow(e);
		bop(div2, sh(e), bro(son(e)), son(e),
		    dest, stack);
		if (!optop(e) && (sh(e)->tag != slonghd) &&
		    (sh(e)->tag != ulonghd)) {
			check_unset_overflow(dest, sh(e));
		}
		clear_overflow(prev_ov);
		return;
	}

	case div1_tag: {
		/* Division is a binary operation */
		int prev_ov = set_overflow(e);
		bop(div1, sh(e), bro(son(e)), son(e), dest, stack);
		if (!optop(e) && (sh(e)->tag != slonghd) &&
		    (sh(e)->tag != ulonghd)) {
			check_unset_overflow(dest, sh(e));
		}
		clear_overflow(prev_ov);
		return;
	}

	case neg_tag: {
		/* Negation is a unary operation */
		int prev_ov = set_overflow(e);
		uop(negate, sh(e), son(e), dest, stack);
		clear_overflow(prev_ov);
		return;
	}

	case abs_tag: {
		/* Abs is a unary operation */
		int prev_ov = set_overflow(e);
		uop(absop, sh(e), son(e), dest, stack);
		clear_overflow(prev_ov);
		return;
	}

	case shl_tag: {
		/* Shifting left is a binary operation */
		int prev_ov = set_overflow(e);
		bop(shift, sh(e), bro(son(e)), son(e), dest, stack);
		clear_overflow(prev_ov);
		return;
	}

	case shr_tag:
		/* Shifting right is a binary operation */
		bop(rshift, sh(e), bro(son(e)), son(e), dest, stack);
		return;

	case mod_tag: {
		/* Remainder is a binary operation */
		int prev_ov = set_overflow(e);
		bop(rem1, sh(e), bro(son(e)), son(e), dest, stack);
		clear_overflow(prev_ov);
		return;
	}

	case rem0_tag:
	case rem2_tag: {
		/* Remainder is a binary operation */
		int prev_ov = set_overflow(e);
		bop(rem2, sh(e), bro(son(e)), son(e), dest, stack);
		clear_overflow(prev_ov);
		return;
	}

	case round_tag: {
		/* Rounding a floating point number is a unary operation */
		int prev_ov = set_overflow(e);
		set_continue(e);
		crt_rmode = round_number(e);
		uop(round_float, sh(e), son(e), dest, stack);
		clear_overflow(prev_ov);
		clear_continue(e);
		return;
	}

	case fmult_tag: {
		/* Floating multiplication is a floating binary operation */
		exp f1 = son(e);
		exp f2 = bro(f1);
		int prev_ov = set_overflow(e);
		if (f2->last) {
			/* two arguments */
			fl_binop(fmult_tag, sh(e), zw(f1), zw(f2), dest);
		} else {
			/*
			 * More than two arguments; use %fp1. Assumes that all
			 * parameters are operands.
			 */
			where w;
			exp s = sim_exp(sh(e), FP1);
			regsinproc |= regmsk(REG_FP1);
			w = zw(s);

			fl_binop(fmult_tag, sh(e), zw(f1), zw(f2), w);
			while (!f2->last) {
				f2 = bro(f2);
				fl_binop(fmult_tag, sh(e), w, zw(f2),
				         (f2->last ? dest : w));
			}
		}

		clear_overflow(prev_ov);
		return;
	}

	case fminus_tag: {
		/* Floating subtraction is a floating binary operation */
		exp f1 = son(e);
		exp f2 = bro(f1);
		int prev_ov = set_overflow(e);
		fl_binop(fminus_tag, sh(e), zw(f2), zw(f1), dest);
		clear_overflow(prev_ov);
		return;
	}

	case fdiv_tag: {
		/* Floating division is a floating binary operation */
		exp f1 = son(e);
		exp f2 = bro(f1);
		int prev_ov = set_overflow(e);
		fl_binop(fdiv_tag, sh(e), zw(f2), zw(f1), dest);
		clear_overflow(prev_ov);
		return;
	}

	case fneg_tag: {
		/* Floating negation is simple */
		int prev_ov = set_overflow(e);
		negate_float(sh(e), zw(son(e)), dest);
		clear_overflow(prev_ov);
		return;
	}

	case fabs_tag: {
		/* Floating absolute value is simple */
		int prev_ov = set_overflow(e);
		abs_float(sh(e), zw(son(e)), dest);
		clear_overflow(prev_ov);
		return;
	}

	case float_tag: {
		/* Casting to a floating point number is simple */
		int prev_ov = set_overflow(e);
		int_to_float(sh(e), zw(son(e)), dest);
		clear_overflow(prev_ov);
		return;
	}

	case chfl_tag: {
		/* Changing a floating variety is simple */
		int prev_ov = set_overflow(e);
		change_flvar(sh(e), zw(son(e)), dest);
		clear_overflow(prev_ov);
		return;
	}

	case and_tag:
		/* And is a logical operation */
		logop( and , e, dest, stack);
		return;

	case or_tag:
		/* Or is a logical operation */
		logop( or , e, dest, stack);
		return;

	case xor_tag:
		/* Xor is a logical operation */
		logop(xor, e, dest, stack);
		return;

	case not_tag:
		/* Not is a unary operation */
		uop(not, sh(e), son(e), dest, stack);
		return;

	case absbool_tag:
		/* The setcc instruction is not used */
		error(ERR_SERIOUS, "Not implemented");
		return;

	case fplus_tag: {
		/* Floating addition is similar to integer addition */
		exp f1 = son(e);	/* First argument */
		exp f2 = bro(f1);	/* Second argument */
		exp t;
		long count_dest = 2;
		exp de = dest.wh_exp;

		int prev_ov = set_overflow(e);

		if (f1->last) {
			/* If there is only one argument things are simple */
			move(sh(e), zw(f1), dest);
			clear_overflow(prev_ov);
			return;
		}

		if (f2->last) {
			/* If there are two arguments code directly */
			if (f2->tag == fneg_tag) {
				f2 = son(f2);
				fl_binop(fminus_tag, sh(e), zw(f2),
				         zw(f1), dest);
			} else {
				fl_binop(fplus_tag, sh(e), zw(f1),
				         zw(f2), dest);
			}
			clear_overflow(prev_ov);
			return;
		}

		if (bro(f2)->last && bro(f2)->tag == real_tag &&
		    dest.wh_exp->tag != apply_tag &&
		    dest.wh_exp->tag != tail_call_tag &&
		    dest.wh_exp->tag != apply_general_tag) {
			/*
			 * If there are 3 arguments, the last of which is
			 * constant.
			 */
			if (f2->tag == fneg_tag) {
				f2 = son(f2);
				fl_binop(fminus_tag, sh(e), zw(f2), zw(f1),
				         dest);
				fl_binop(fplus_tag, sh(e), zw(bro(f2)), dest,
				         dest);
			} else {
				fl_binop(fplus_tag, sh(e), zw(f1), zw(f2),
				         dest);
				fl_binop(fplus_tag, sh(e), zw(bro(f2)), dest,
				         dest);
			}
			clear_overflow(prev_ov);
			return;
		}

		if (de->tag == ass_tag && son(de)->tag == name_tag &&
		    ((props(son(son(de))) & 0x9) == 0x9)) {
			count_dest = 0;
			t = f1;
			if (eq_where(dest, zw(t))) {
				count_dest++;
			}
			while (!t->last) {
				t = bro(t);
				if (t->tag == fneg_tag) {
					if (eq_where(zw(son(t)), dest)) {
						count_dest = 2;
					}
				} else {
					if (eq_where(zw(t), dest)) {
						count_dest++;
					}
				}
			}
		}

		if (count_dest < 2 &&
		    (dest.wh_exp->tag != apply_tag &&
		     dest.wh_exp->tag != tail_call_tag &&
		     dest.wh_exp->tag != apply_general_tag)) {
			if (count_dest == 1) {
				t = f1;
			} else {
				if (f2->tag == fneg_tag) {
					exp m = son(f2);
					fl_binop(fminus_tag, sh(e), zw(m),
					         zw(f1), dest);
				} else {
					fl_binop(fplus_tag, sh(e), zw(f1),
					         zw(f2), dest);
				}
				t = bro(f2);
			}

			for (;;) {
				where tw;
				if (t->tag == fneg_tag) {
					tw = zw(son(t));
					if (!eq_where(dest, tw)) {
						fl_binop(fminus_tag, sh(e), tw,
						         dest, dest);
					}
				} else {
					tw = zw(t);
					if (!eq_where(dest, tw)) {
						fl_binop(fplus_tag, sh(e), tw,
						         dest, dest);
					}
				}
				if (t->last) {
					break;
				}
				t = bro(t);
			}
		} else {
			if (f2->tag == fneg_tag) {
				fl_binop(fminus_tag, sh(e), zw(son(f2)),
				         zw(f1), FP0);
			} else {
				fl_binop(fplus_tag, sh(e), zw(f1), zw(f2),
				         FP0);
			}

			t = bro(f2);
			while (!t->last) {
				if (t->tag == fneg_tag) {
					fl_binop(fminus_tag, sh(e), zw(son(t)),
					         FP0, FP0);
				} else {
					fl_binop(fplus_tag, sh(e), zw(t), FP0,
					         FP0);
				}
				t = bro(t);
			}

			if (t->tag == fneg_tag) {
				fl_binop(fminus_tag, sh(e), zw(son(t)), FP0,
				         dest);
			} else {
				fl_binop(fplus_tag, sh(e), zw(t), FP0, dest);
			}
		}

		clear_overflow(prev_ov);
		return;
	}

	/*
	 * Note: in the following offset operations I have put the
	 * shape as slongsh rather than sh(e).  This is because
	 * the system stddef.h wrongly says that ptrdiff_t is unsigned
	 * and I don't trust people to put it right when making up
	 * TDF libraries.  If this was right sh(e) would be slongsh.
	 */

	case offset_add_tag:
		asm_comment("offset_add_tag...");
		/* Offset addition is a binary operation */
		bop(add, slongsh, son(e), bro(son(e)), dest, stack);
		asm_comment("offset_add_tag done");
		return;

	case offset_subtract_tag:
		/* Offset subtraction is a binary operation */
		bop(sub, slongsh, bro(son(e)), son(e), dest, stack);
		return;

	case offset_mult_tag:
		asm_comment("offset_mult_tag...");
		/* Offset multiplication is a binary operation */
		bop(mult, slongsh, son(e), bro(son(e)), dest, stack);
		asm_comment("offset_mult_tag done");
		return;

	case offset_negate_tag:
		/* Offset negation is a unary operation */
		uop(negate, slongsh, son(e), dest, stack);
		return;

	case offset_div_tag:
	case offset_div_by_int_tag:
		/* Offset division is a binary operation */
		if (sh(bro(son(e)))->tag < slonghd) {
			exp changer = me_u3(slongsh, bro(son(e)), chvar_tag);
			bro(son(e)) = changer;
		}
		bop(div2, slongsh, bro(son(e)), son(e), dest, stack);
		return;

	case offset_pad_tag: {
		/* Pad an operand */
		exp  cur_offset = son(e);
		long cur_align  = al2(sh(cur_offset));
		long next_align = al2(sh(e));

		asm_comment("offset_pad ...");

		/* does current alignment include next alignment? */

		if (cur_align  >= next_align) {
			if ((next_align != 1) || (cur_align == 1)) {
				make_code(dest, stack, cur_offset);
			} else {
				/* left shift */
				shift(sh(e), mnw(3), zw(cur_offset), dest);
			}
		} else {
			/* cur_align < next_align */
			where r;
			if (whereis(dest) == Dreg) {
				r = dest;
			} else {
				r = D1;
				regsinproc |= regmsk(REG_D1);
			}
			codec(r, stack, cur_offset);

			if (cur_align == 1) {
				add(slongsh, mnw(next_align - 1), r, r);
				and (slongsh, mnw(-next_align), r, dest);
				rshift(sh(e), mnw(3), dest, dest);
			} else {
				long al = next_align / 8;
				add(slongsh, mnw(al - 1), r, r);
				and (slongsh, mnw(-al), r, dest);
			}
		}

		asm_comment("offset_pad done");
		return;
	}

	case bitf_to_int_tag: {
		if (whereis(dest) == Dreg) {
			make_code(dest, stack, son(e));
			change_var_sh(sh(e), sh(son(e)), dest, dest);
		} else {
			regsinproc |= regmsk(REG_D1);
			make_code(D1, stack, son(e));
			change_var_sh(sh(e), sh(son(e)), D1, dest);
		}
		return;
	}

	case int_to_bitf_tag: {
		where r;
		long nbits = shape_size(sh(e));
		long mask = lsb_mask[nbits];
		r = (whereis(dest) == Dreg ? dest : D0);
		move(slongsh, zw(son(e)), r);
		and (slongsh, mnw(mask), r, dest);
		return;
	}

	case offset_max_tag:
	case max_tag:
		/* Maximum */
		bop(maxop, sh(e), son(e), bro(son(e)), dest, stack);
		return;

	case min_tag:
		/* Minimum */
		bop(minop, sh(e), son(e), bro(son(e)), dest, stack);
		return;

	case cont_tag:
		asm_comment("cont_tag ...");

		if (sh(e)->tag == bitfhd) {
			bitf_to_int(e, sh(e), dest, stack);
			return;
		}

		move(sh(e), zw(e), dest);

		asm_comment("cont_tag done");
		return;

	default:
		if (!is_o(e->tag)) {
			/* If e is not an operand, code e into a register */
			exp s;
			where w;
			if (e->tag == apply_tag
			    || e->tag == apply_general_tag
			    || e->tag == tail_call_tag) {
				s = sim_exp(sh(e), D0);
			} else {
				if (whereis(dest) == Dreg) {
					/* error(ERR_SERIOUS, "Untested optimization"); */
					s = sim_exp(sh(e), dest);
				} else {
					regsinproc |= regmsk(REG_D1);
					s = sim_exp(sh(e), D1);
				}
			}
			w = zw(s);

			make_code(w, stack, e);

			/* Move the value of this register into dest */
			move(sh(e), w, dest);
			retcell(s);
			if (have_cond == 3) {
				have_cond = 1;
			}
			return;
		}

		if (e->tag == reff_tag && shape_size(sh(e)) != 32) {
			/* Deal with pointers to bitfields */
			where d;
			/* s = sim_exp(sh(e), D0); */
			d = mw(dest.wh_exp, dest.wh_off + 32);
			if (shape_size(sh(son(e))) == 32) {
				asm_comment("Pointer to bitfield (32) ...");
				make_code(dest, stack, son(e));
				move(slongsh, mnw(no(e)), d);
				asm_comment("Pointer to bitfield (32) done");
				return;
			}
			asm_comment("Pointer to bitfield ...");
			make_code(dest, stack, son(e));
			add(slongsh, mnw(no(e)), d, d);
			asm_comment("Pointer to bitfield done");
			return;
		}

		if (e->tag == reff_tag &&
		    (son(e)->tag == name_tag ||
		     (son(e)->tag == cont_tag &&
		      son(son(e))->tag == name_tag))) {
			/* Deal with pointers with offsets */
			long off = no(e) / 8;
			asm_comment("reff_tag ...");
			add(slongsh, zw(son(e)), mnw(off), dest);
			asm_comment("reff_tag done");
			return;
		}

		if ((e->tag == name_tag && isvar(son(e))) ||
		    e->tag == reff_tag) {
			/* Deal with pointers */
			mova(zw(e), dest);
			return;
		}

		if (e->tag == clear_tag) {
			/* Deal with clear shapes */
			char sn = sh(e)->tag;
			if (sn >= shrealhd && sn <= doublehd) {
				move(sh(e), fzero, dest);
			}
#ifndef tdf3
			if (dest.wh_exp->tag == apply_tag ||
			    dest.wh_exp->tag == apply_general_tag ||
			    dest.wh_exp->tag == tail_call_tag) {
				move(sh(e), zero, dest);
			}
#endif
			return;
		}

		if (e->tag == val_tag &&
		    ((sh(e)->tag == s64hd) || sh(e)->tag == u64hd)) {
			flt64 bval;
			where w;
			bval = exp_to_f64(e);
			if (eq_where(dest, D0_D1)) {
				move_const(slongsh, 32, bval.big, D1);
				move_const(slongsh, 32, bval.small, D0);
			} else {
				w = dest;
				move_const(sh(e), 32, bval.small, w);
				w.wh_off += 32;
				move_const(sh(e), 32, bval.big, w);
			}
			return;
		}

		/* If all else fails, use move */
		if (e->tag == top_tag) {
			return;
		}

		move(sh(e), zw(e), dest);
		return;
	}
}

