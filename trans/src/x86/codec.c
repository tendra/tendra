/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * codec produces code for operations which produce values.
 * e is the operation and dest is where the result is to be put.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>
#include <local/code.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <reader/basicread.h>
#include <reader/readglob.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>

#include <flpt/flpt.h>

#include <utility/bits.h>

#include <main/flags.h>

#include "localtypes.h"
#include "ops.h"
#include "operand.h"
#include "make_code.h"
#include "instr.h"
#include "reg_record.h"
#include "instrs.h"
#include "codec.h"

/*
 * returns true if is_o(e) but not a possible 80386 operand
 */
bool
is_crc(exp e)
{
	/* make sure (is_o && is_crc -> !is_opnd) */
	if (e->tag == name_tag) {
		if (isvar(child(e))) {
			return !isglob(child(e)) || PIC_code;
		}

		return child(child(e)) == NULL ||
		       (isglob(child(e)) && PIC_code && sh(child(e))->tag == prokhd &&
		        !(nextg(child(e)) -> extnamed)) ||
		       (child(child(e))->tag == ident_tag && isparam(child(child(e))));
	}

	if (e->tag == reff_tag || e->tag == field_tag) {
		return true;
	}

	if (e->tag != cont_tag) {
		return false;
	}

	if (child(e)->tag == cont_tag) {
		return true;
	}

	return child(e)->tag == reff_tag &&
	       child(child(e))->tag == cont_tag;
}

/*
 * op is a procedure for encoding a unary operation.
 *
 * If a is a possible 80386 operand, uop applies this operator
 * to produce the code for a, leaving the result in dest.
 *
 * sha gives the shape for the operation.
 *
 * If a is not a possible 80386 operand, then uop produces code
 * for a to put it into eax (reg0) and then applies op to eax,
 * putting the result into dest.
 */
static
void uop(void(*op)(shape, where, where),
	shape sha, exp a, where dest, ash stack)
{
	where qw;

	if (is_o(a->tag) && !is_crc(a)) {
		(*op)(sha, mw(a, 0), dest);
		return;
	}

	if (!inmem(dest)) {
		qw.where_exp = copyexp(dest.where_exp);
	} else {
		qw.where_exp = copyexp(reg0.where_exp);
	}
	sh(qw.where_exp) = sha;
	qw.where_off = 0;
	make_code(qw, stack, a);
	(*op)(sha, qw, dest);
	retcell(qw.where_exp);
	cond1_set = false;
}

static int
no_reg_needed(exp e)
{
	if (e->tag == val_tag) {
		return 1;
	}

	if (e->tag == cont_tag &&
	    child(e)->tag == name_tag &&
	    isvar(child(child(e))) &&
	    ptno(child(child(e))) != reg_pl) {
		return 1;
	}

	if (e->tag == name_tag &&
	    !isvar(child(e)) &&
	    ptno(child(e)) != reg_pl) {
		return 1;
	}

	return 0;
}

/*
 * op is a procedure for encoding a binary operation.
 *
 * Not more than one of a and b will not be a possible 80386 operand.
 *
 * This has been ensured by scan(). If a and b are both possible 80386 operands,
 * bop applies this operator to produce the code, leaving the result in dest.
 *
 * sha gives the shape for the operation.
 *
 * If either a or b is not a possible 80386 operand, then bop produces code
 * for it to put it into eax (reg0) and then applies op to eax and the other
 * operand, putting the result into dest.
 */
void
bop(void(*op)(shape, where, where, where),
	shape sha, exp a, exp b, where dest, ash stack)
{
	where qw;

	if (!is_o(a->tag) || is_crc(a)) {
		if (!inmem(dest) && no_reg_needed(b)) {
			qw.where_exp = copyexp(dest.where_exp);
		} else {
			qw.where_exp = copyexp(reg0.where_exp);
		}
		sh(qw.where_exp) = sha;
		qw.where_off = 0;
		make_code(qw, stack, a);
		(*op)(sha, qw, mw(b, 0), dest);
		retcell(qw.where_exp);
		cond1_set = false;
		return;
	}

	if (!is_o(b->tag) || is_crc(b)) {
		if (!inmem(dest) && no_reg_needed(a)) {
			qw.where_exp = copyexp(dest.where_exp);
		} else {
			qw.where_exp = copyexp(reg0.where_exp);
		}
		sh(qw.where_exp) = sha;
		qw.where_off = 0;
		make_code(qw, stack, b);
		(*op)(sha, mw(a, 0), qw, dest);
		retcell(qw.where_exp);
		cond1_set = false;
		return;
	}

	(*op)(sha, mw(a, 0), mw(b, 0), dest);
}

/*
 * Process the binary logical operation exp.
 *
 * op is the compiling procedure for the operation. It is commutative and
 * associative, the operation takes a variable number of arguments.
 * It is therefore necessary to avoid the mistake of assigning to the
 * destination (dest) inappropriately if its value is used in the expression.
 *
 * At most one of the arguments will not be a possible 80386 operand. If there
 * is such an argument, logop precomputes it, putting the value into reg0.
 */
static void
logop(void(*op)(shape, where, where, where),
	exp e, where dest, ash stack)
{
	exp arg1 = child(e);
	exp arg2 = next(arg1);
	shape sha = sh(e);
	exp t, u;
	where qw;

	if (arg1->last) {
		make_code(dest, stack, arg1);
		return;
	}

	/* just two arguments */
	if (arg2->last) {
		bop(op, sha, arg1, arg2, dest, stack);
		return;
	}

	/*
	 * need to take care about overlap between dest and args or to avoid
	 * extra push. So use reg0.
	 */
	qw.where_exp = copyexp(reg0.where_exp);
	sh(qw.where_exp) = sha;
	qw.where_off = 0;

	/* now look for an argument which is not a possible 80386 operand */
	t = arg1;
	for (;;) {
		if (!is_o(t->tag) || is_crc(t)) {
			break;
		}

		if (t->last) {
			t = NULL;
			break;
		}

		t = next(t);
	}

	if (t == NULL) {
		/* all arguments are possible 80386 operands */
		(*op)(sha, mw(arg1, 0), mw(arg2, 0), qw);
		t = next(arg2);
		while (!t->last) {
			(*op) (sha, mw (t, 0), qw, qw);/* encode operations in turn */
			t = next(t);
		}
		(*op) (sha, mw (t, 0), qw, dest);/* encode final operation */
		retcell(qw.where_exp);
		cond1_set = false;
		return;
	}

	/* encode the single argument which is not a possible 80386 operend */
	make_code(qw, stack, t);

	/* now encode the remaining operations */
	u = arg1;
	for (;;) {
		if (t != u) {
			if (u->last || (next(u) == t && next(u)->last)) {
				(*op)(sha, mw(u, 0), qw, dest);
			} else {
				(*op)(sha, mw(u, 0), qw, qw);
			}
		}

		if (u->last) {
			break;
		}

		u = next(u);
	}

	retcell(qw.where_exp);
	cond1_set = false;
}

/*
 * Process the multiply operation exp.
 *
 * op is the compiling procedure for the operation. It is commutative and
 * associative, the operation takes a variable number of arguments.
 * It is therefore necessary to avoid the mistake of assigning to the
 * destination (dest) inappropriately if its value is used in the expression.
 *
 * At most one of the arguments will not be a possible 80386 operand. If there
 * is such an argument, it is precomputed, putting the value into reg0.
 */
static void
multop(void(*op)(shape, where, where, where),
	exp e, where dest, ash stack)
{
	exp arg1 = child(e);
	exp arg2 = next(arg1);
	exp t, u;
	where qw;

	if (arg1->last) {
		make_code(dest, stack, arg1);
		return;
	}

	/* just two arguments. */
	if (arg2->last) {
		bop(op, sh(e), arg1, arg2, dest, stack);
		return;
	}

	/*
	 * need to take care about overlap between dest and args or to avoid
	 * extra push. So use reg0.
	 */
	qw.where_exp = copyexp(reg0.where_exp);
	sh(qw.where_exp) = sh(e);
	qw.where_off = 0;

	/* now look for an argument which is not a possible 80386 operand */
	t = arg1;
	for (;;) {
		if (!is_o(t->tag) || is_crc(t)) {
			break;
		}

		if (t->last) {
			t = NULL;
			break;
		}

		t = next(t);
	}

	if (t == NULL) {
		/* all arguments are possible 80386 operands */
		(*op)(sh(e), mw(arg1, 0), mw(arg2, 0), qw);
		t = next(arg2);

		while (!t->last) {
			(*op) (sh (e), mw (t, 0), qw, qw);/* encode operations in turn */
			t = next(t);
		}

		(*op) (sh (e), mw (t, 0), qw, dest);/* encode final operation */
		retcell(qw.where_exp);
		cond1_set = false;
		return;
	}

	/* encode the single argument which is not a possible 80386 operand */
	make_code(qw, stack, t);

	/* now encode the remaining operations */
	u = arg1;
	for (;;) {
		if (t != u) {
			if (u->last || (next(u) == t && next(u)->last)) {
				(*op)(sh(e), mw(u, 0), qw, dest);
			} else {
				(*op)(sh(e), mw(u, 0), qw, qw);
			}
		}

		if (u->last) {
			break;
		}

		u = next(u);
	}

	retcell(qw.where_exp);
	cond1_set = false;
}

/*
 * if a is a negation form b-child(a) otherwise b+a in dest
 */
static void
addsub(shape sha, where a, where b, where dest, exp e)
{
	UNUSED(e);

	if (a.where_exp->tag == neg_tag) {
		sub(sha, mw(child(a.where_exp), 0), b, dest);
	} else {
		add(sha, a, b, dest);
	}
}

/*
 * codec outputs the code which evaulates e and puts the result into dest.
 *
 * encode e, putting the result into dest. stack is the current stack level
 */
void
codec(where dest, ash stack, exp e)
{
	switch (e->tag) {
	case plus_tag: {
		/* at most one of the arguments will not be a possible 80386 operand */
		exp arg1 = child(e);
		exp arg2 = next(arg1);
		exp t, u, v;
		where qw;
		exp old_overflow_e = overflow_e;

		if (arg1->last) {	/* there is only one argument */
			make_code(dest, stack, arg1);
			return;
		}

		if (!optop(e)) {
			overflow_e = e;
		}

		if (arg2->last && is_o(arg1->tag) && !is_crc(arg1) &&
		    ((is_o(arg2->tag) && !is_crc(arg2)) ||
		     (arg2->tag == neg_tag &&
		      !is_crc(child(arg2)) &&
		      is_o(child(arg2)->tag))))
		{
			/* just two arguments. */
			addsub(sh(e), mw(arg2, 0), mw(arg1, 0), dest, e);
			overflow_e = old_overflow_e;
			return;
		}

		/*
		 * need to take care about overlap between dest and args or to
		 * avoid extra push. So use reg0.
		 */
		t = arg1;
		qw.where_exp = copyexp(reg0.where_exp);
		sh(qw.where_exp) = sh(e);
		qw.where_off = 0;

		/* now look for argument which is not a possible 80386 operand */
		for (;;) {
			if ((!is_o(t->tag) || is_crc(t)) &&
			    (t->tag != neg_tag || !is_o(child(t)->tag) ||
			     is_crc(child(t)))) {
				break;
			}

			if (t->last) {
				t = NULL;
				break;
			}

			t = next(t);
		}

		if (t == NULL && arg1->tag == neg_tag &&
		    arg2->tag == neg_tag) {
			t = arg1;
		}

		/* all arguments are possible 80386 operands */
		if (t == NULL) {
			t = next(arg2);
			if (arg1->tag == neg_tag) {
				addsub(sh(e), mw(arg1, 0), mw(arg2, 0),
				       (t == e) ? dest : qw, e);
			} else {
				addsub(sh(e), mw(arg2, 0), mw(arg1, 0),
				       (t == e) ? dest : qw, e);
			}

			if (t == e) {
				overflow_e = old_overflow_e;
				return;
			}

			while (!t->last) {
				u = next(t);
				addsub(sh(e), mw(t, 0), qw, qw, e);
				t = u;
			}

			addsub(sh(e), mw(t, 0), qw, dest, e);
			overflow_e = old_overflow_e;
			return;
		}

		/* encode the argument which is not a possible 80386 operand */
		make_code(qw, stack, t);

		/* now encode the remaining operations */
		u = arg1;
		for (;;) {
			v = next(u);
			if (t != u) {
				if (u->last || (v == t && v->last)) {
					addsub(sh(e), mw(u, 0), qw, dest, e);
				} else {
					addsub(sh(e), mw(u, 0), qw, qw, e);
				}
			}

			if (u->last) {
				break;
			}

			u = v;
		}

		retcell(qw.where_exp);
		cond1_set = false;
		overflow_e = old_overflow_e;
		return;
	}

	case addptr_tag: {		/* use index operation */
		mova(mw(e, 0), dest);
		return;
	}

	case chvar_tag: {
		exp a = child(e);
		exp old_overflow_e = overflow_e;

		if (!optop(e)) {
			overflow_e = e;
		}

		if (!is_o(a->tag) || is_crc(a)) {
			/* argument is not a possible 80386 operand, so evaluate it in reg0 */
			if (inmem(dest) ||
			    (shape_size(sh(a)) == 8 && bad_from_reg(dest)) ||
			    shape_size(sh(a)) == 64)
			{
				where qw;
				qw.where_exp = copyexp(reg0.where_exp);
				sh(qw.where_exp) = sh(a);
				qw.where_off = 0;
				make_code(qw, stack, a);
				change_var_refactor(sh(e), qw, dest);
				overflow_e = old_overflow_e;
				retcell(qw.where_exp);
				cond1_set = false;
				return;
			}

			make_code(dest, stack, a);
			if (sh(e)->tag > sh(a)->tag) {
				change_var_sh(sh(e), sh(a), dest, dest);
			}

			overflow_e = old_overflow_e;
			return;
		}

		change_var_refactor(sh(e), mw(a, 0), dest);
		overflow_e = old_overflow_e;
		return;
	}

	case minus_tag: {
		exp old_overflow_e = overflow_e;
		if (!optop(e)) {
			overflow_e = e;
		}
		bop(sub, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case subptr_tag:
	case minptr_tag:
	case make_stack_limit_tag:
		bop(sub, sh(e), next(child(e)), child(e), dest, stack);
		return;

	case mult_tag:
		if (!optop(e)) {
			exp old_overflow_e = overflow_e;
			overflow_e = e;
			multop(multiply, e, dest, stack);
			overflow_e = old_overflow_e;
		} else {
			multop(mult, e, dest, stack);
		}
		return;

	case div2_tag: {
		exp old_overflow_e = overflow_e;
		if (errhandle(e)) {
			overflow_e = e;
		}
		bop(div2, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case div1_tag: {
		exp old_overflow_e = overflow_e;
		if (errhandle(e)) {
			overflow_e = e;
		}
		bop(div1, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case div0_tag: {
		exp old_overflow_e = overflow_e;
		if (errhandle(e)) {
			overflow_e = e;
		}
		bop(div0, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case neg_tag: {
		exp old_overflow_e = overflow_e;
		if (!optop(e)) {
			overflow_e = e;
		}
		uop(negate, sh(e), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case shl_tag: {
		exp old_overflow_e = overflow_e;
		overflow_e = e;
		if (!optop(e)) {
			overflow_e = e;
		}
		bop(shiftl, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case shr_tag:
		bop(shiftr, sh(e), next(child(e)), child(e), dest, stack);
		return;

	case rotl_tag:
		bop(rotatel, sh(e), next(child(e)), child(e), dest, stack);
		return;

	case rotr_tag:
		bop(rotater, sh(e), next(child(e)), child(e), dest, stack);
		return;

	case mod_tag: {
		exp old_overflow_e = overflow_e;
		if (errhandle(e)) {
			overflow_e = e;
		}
		bop(mod, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case rem2_tag: {
		exp old_overflow_e = overflow_e;
		if (errhandle(e)) {
			overflow_e = e;
		}
		bop(rem2, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case rem0_tag: {
		exp old_overflow_e = overflow_e;
		if (errhandle(e)) {
			overflow_e = e;
		}
		bop(rem0, sh(e), next(child(e)), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case round_tag: {
		shape s = sh(e);
		where d;
		d = dest;

		if (shape_size(s) < 32) {
			s = slongsh;
			if (inmem(dest)) {
				d = reg0;
			}
		}

		setup_fl_ovfl(e);

		switch (round_number(e)) {
		case 0: uop(frnd0, s, child(e), d, stack); break;
		case 1: uop(frnd1, s, child(e), d, stack); break;
		case 2: uop(frnd2, s, child(e), d, stack); break;
		case 3: uop(frnd3, s, child(e), d, stack); break;
		case 4: uop(frnd4, s, child(e), d, stack); break;
		}

		test_fl_ovfl(e, d);
		if (s->tag != sh(e)->tag) {
			exp old_overflow_e = overflow_e;
			if (!optop(e)) {
				overflow_e = e;
			}
			change_var_sh(sh(e), s, d, dest);
			overflow_e = old_overflow_e;
		}
		return;
	}

	case fplus_tag:
		setup_fl_ovfl(e);
		fl_multop(fplus_tag, sh(e), child(e), dest);
		test_fl_ovfl(e, dest);
		return;

	case fmult_tag:
		setup_fl_ovfl(e);
		fl_multop(fmult_tag, sh(e), child(e), dest);
		test_fl_ovfl(e, dest);
		return;

	case fminus_tag:
		setup_fl_ovfl(e);
		fl_binop(fminus_tag, sh(e), mw(next(child(e)), 0),
		         mw(child(e), 0), dest, next(child(e)));
		test_fl_ovfl(e, dest);
		return;

	case fdiv_tag:
		setup_fl_ovfl(e);
		fl_binop(fdiv_tag, sh(e), mw(next(child(e)), 0),
		         mw(child(e), 0), dest, next(child(e)));
		test_fl_ovfl(e, dest);
		return;

	case fneg_tag:
		setup_fl_ovfl(e);
		fl_neg(sh(e), mw(child(e), 0), dest);
		test_fl_ovfl(e, dest);
		return;

	case fabs_tag:
		setup_fl_ovfl(e);
		fl_abs(sh(e), mw(child(e), 0), dest);
		test_fl_ovfl(e, dest);
		return;

	case float_tag:
		setup_fl_ovfl(e);
		floater(sh(e), mw(child(e), 0), dest);
		test_fl_ovfl(e, dest);
		return;

	case chfl_tag:
		if (sh(e)->tag < sh(child(e))->tag) {
			setup_fl_ovfl(e);
		}

		changefl(sh(e), mw(child(e), 0), dest);
		if (sh(e)->tag < sh(child(e))->tag) {
			test_fl_ovfl(e, dest);
		}
		return;

	case and_tag:
		logop(and, e, dest, stack);
		return;

	case or_tag:
		logop(or, e, dest, stack);
		return;

	case xor_tag:
		logop(xor, e, dest, stack);
		return;

	case not_tag:
		uop(not, sh(e), child(e), dest, stack);
		return;

	case offset_pad_tag:
		if (al2(sh(child(e))) >= al2(sh(e))) {
			if (al2(sh(e)) != 1 || al2(sh(child(e))) == 1) {
				make_code(dest, stack, child(e));
			} else {
				make_code(reg0, stack, child(e));
				shiftl(slongsh, mw(zeroe, 3), reg0, dest);
			}
		} else {
			int al = al2(sh(e)) / 8;
			make_code(reg0, stack, child(e));
			if (al2(sh(child(e))) == 1) {
				add(slongsh, mw(zeroe, al * 8 - 1), reg0, reg0);
				shiftr(slongsh, mw(zeroe, 3), reg0, reg0);
			} else {
				add(slongsh, mw(zeroe, al - 1), reg0, reg0);
			}
			and (slongsh, mw(zeroe, -al), reg0, dest);
		}
		return;

	case offset_add_tag:
		bop(add, sh(e), child(e), next(child(e)), dest, stack);
		return;

	case abs_tag: {
		exp old_overflow_e = overflow_e;
		if (!optop(e)) {
			overflow_e = e;
		}
		uop(absop, sh(e), child(e), dest, stack);
		overflow_e = old_overflow_e;
		return;
	}

	case offset_max_tag:
	case max_tag:
		bop(maxop, sh(e), child(e), next(child(e)), dest, stack);
		return;

	case min_tag:
		bop(minop, sh(e), child(e), next(child(e)), dest, stack);
		return;

	case offset_subtract_tag:
		bop(sub, sh(e), next(child(e)), child(e), dest, stack);
		return;

	case offset_mult_tag:
		bop(mult, slongsh, child(e), next(child(e)), dest, stack);
		return;

	case offset_negate_tag:
		uop(negate, sh(e), child(e), dest, stack);
		return;

	case offset_div_by_int_tag:
		bop(div0, sh(e), next(child(e)), child(e), dest, stack);
		return;

	case offset_div_tag:
		if (shape_size(sh(e)) == 32) {
			bop(div0, sh(e), next(child(e)), child(e), dest, stack);
		} else if (inmem(dest)) {
			bop(div0, sh(child(e)), next(child(e)), child(e), reg0, stack);
			change_var(sh(e), reg0, dest);
		} else {
			bop(div0, sh(child(e)), next(child(e)), child(e), dest, stack);
			change_var(sh(e), dest, dest);
		}
		return;

	case absbool_tag:
		error(ERR_INTERNAL, "no setcc");
		return;

	case int_to_bitf_tag: {
		int mask = lsb_mask[shape_size(sh(e))];
		move(slongsh, mw(child(e), 0), dest);
		and (slongsh, mw(zeroe, mask), dest, dest);
		return;
	}

	case bitf_to_int_tag:
		make_code(reg0, stack, child(e));
		change_var_sh(sh(e), sh(child(e)), reg0, dest);
		return;

	case alloca_tag:
		make_code(dest, stack, e);
		return;

	case power_tag:
		error(ERR_INTERNAL, "integer power not implemented");
		return;

	case cont_tag:
		if (!newcode && sh(e)->tag == bitfhd) {
			mem_to_bits(e, sh(e), dest, stack);
			return;
		}

		FALL_THROUGH;

	default:
		if (!is_o(e->tag)) {
			/*
			 * e is not a possible 80386 operand, precompute it into reg0
			 * and move to dest
			 */
			where qw;
			qw.where_exp = copyexp(reg0.where_exp);
			sh(qw.where_exp) = sh(e);
			qw.where_off = 0;
			make_code(qw, stack, e);
			move(sh(e), qw, dest);
			retcell(qw.where_exp);
			cond1_set = false;
			return;
		}

		if (is_crc(e) && e->tag != name_tag
		    && e->tag != reff_tag && e->tag != field_tag) {
			exp s = child(e);
			exp ss = child(s);
			exp sss = ss;
			exp * p = & child(e);

			if (s->tag == reff_tag) {
				sss = child(ss);
				p = & child(s);
			}

			if (sss->tag == name_tag && ptno(child(sss)) == reg_pl) {
				move(sh(e), mw(e, 0), dest);
				return;
			} else {
				exp temp = copyexp(reg0.where_exp);
				exp preserve = *p;
				make_code(reg0, stack, *p);
				*p = temp;
				move(sh(e), mw(e, 0), dest);
				*p = preserve;	/* may still be needed for diags */
				return;
			}
		}

		if (e->tag == reff_tag &&
		    (child(e)->tag == name_tag ||
		     (child(e)->tag == cont_tag &&
		      child(child(e))->tag == name_tag)))
		{
			/* look for case when reff should be done by add */
			add(slongsh, mw(child(e), 0), mw(zeroe, no(e) / 8), dest);
			return;
		}

		if ((e->tag == name_tag && isvar(child(e))) ||
		    e->tag == reff_tag ||
		    (PIC_code && e->tag == name_tag && isglob(child(e)) &&
		     sh(child(e))->tag == prokhd &&
		     !nextg(child(e)) ->  extnamed))
		{
			if (ptno(child(e)) != nowhere_pl) {
				mova(mw(e, 0), dest);
			}
			return;
		}

		if (e->tag == clear_tag) {
			if ((sh(e)->tag >= shrealhd && sh(e)->tag <= doublehd &&
			     !inmem(dest)) || dest.where_exp->tag == apply_tag) {
				move(sh(e), fzero, dest);
			}
			return;
		}

		/* other values */

		if (e->tag != top_tag && e->tag != prof_tag) {
			move(sh(e), mw(e, 0), dest);
		} else {
			top_regsinuse = regsinuse;
		}
		return;
	}
}

