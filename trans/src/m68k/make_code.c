/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <local/szs_als.h>
#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/installglob.h>
#include <construct/reg_result.h>

#include <utility/bits.h>
#include <utility/imath.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <refactor/optimise.h>

#include "localtypes.h"
#include "mach.h"
#include "where.h"
#include "codec.h"
#include "make_code.h"
#include "operations.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "peephole.h"
#include "tests.h"
#include "weights.h"
#include "translate.h"
#include "ops_shared.h"
#include "general_proc.h"
#include "output.h"
#include "68k_globals.h"
#include "localexpmacs.h"
#include "assembler.h"

#include "xdb_basics.h"

extern int normal_version;
static int extra_weight = 0;

/*
 * Given an ash p, representing the stack, and a shape s, this procedure
 * returns the ast correponding to the new stack formed by adding s to the
 * old stack.
 */
ast
add_shape_to_stack(ash p, shape s)
{
	ast res;
	char n = s->tag;
	long sz = shape_size(s);
	long adj = 0;

	if (n == scharhd || n == ucharhd || n == swordhd || n == uwordhd) {
		adj = SLONG_SZ - sz;
		sz = SLONG_SZ;
	}

	if (n == bitfhd) {
		sz = SLONG_SZ;
	}

	res.astoff = iround(p, param_align);
	res.astadj = adj;
	res.astash = iround(res.astoff + sz, param_align);

	return res;
}

/*
 * This routine tries to choose registers for a value of shape sha.  br
 * gives the breakpoint - the minimum number of registers which need to
 * be free for it to be worth putting this value in a register.  The big
 * flag is true to indicate that a register which is preserved across
 * procedure calls is required.  If a register can be allocated, then
 * its bitpattern is returned.  Otherwise 0 is returned.
 */
static bitpattern
alloc_reg(shape sha, int br, bool big)
{
	bitpattern mask;
	bitpattern rs = regsinuse;
	int i, start, end, rev = 0;

	int rg;
	int r = shtype(sha);

	if (r == Dreg) {
		rg = bits_in(~rs & 0x00fc);
		mask = regmsk(REG_D2);
		start =  REG_D2;
		end = REG_D7;
	} else if (r == Areg) {
		rg = bits_in(~rs & 0x3c00);
		mask = regmsk(REG_A2);
		start = REG_A2;
		end = REG_A5;

		if (br > extra_weight) {
			br -= extra_weight;
		}
	} else if (r == Freg) {
		if (round_after_flop) {
			return 0;
		}

		rg = bits_in(~rs & 0xfc0000);
		mask = regmsk(REG_FP7);
		start = REG_FP7;
		end = REG_FP2;
		rev = 1;
	} else {
		error(ERR_SERIOUS, "Illegal register type");
		return 0;
	}

	if (rg < br || rg == 0) {
		return 0;
	}

	i = start;
	for (;;) {
		if (!(rs & mask)) {
			if (big) {
				bigregs |= mask;
				if (r == Freg) {
					normal_version = 0;
				}
			}
			regsinproc |= mask;
			return mask;
		}

		if (i == end) {
			break;
		}

		if (rev) {
			i--;
			mask >>= 1;
		} else {
			i++;
			mask <<= 1;
		}
	}

	return 0;
}

/*
 * This routine returns 0 if the expression e is not a use of a reuseable
 * register, and the bitmask of the register otherwise.
 */
static long
reuse_check(exp e)
{
	exp id;

	if (e->tag != name_tag) {
		return 0;
	}

	id = son(e);
	if (isglob(id) || pt(id) != reg_pl) {
		return 0;
	}

	return reuseables & no(id);
}

/*
 * This routine checks whether or not we can use a reuseable register to
 * store def.  It returns the bitmask of a suitable register if so and 0
 * otherwise.
 */
static long
reuse(exp def)
{
	switch (def->tag) {
	case name_tag:
		return reuse_check(def);

	case plus_tag:
	case and_tag:
	case or_tag:
	case xor_tag:
	case mult_tag: {
		/* Allow at most two arguments - check both */
		exp arg1 = son(def);
		exp arg2 = bro(arg1);

		if (arg1->last) {
			return reuse_check(arg1);
		}

		if (arg2->last) {
			return reuse_check(arg1) || reuse_check(arg2);
		}

		return 0;
	}

	case chvar_tag:
	case neg_tag:
	case not_tag:
		/* Check one argument */
		return reuse_check(son(def));

	case minus_tag:
	case subptr_tag:
	case minptr_tag:
	case shl_tag:
	case shr_tag: {
		/* Check two arguments */
		exp arg1 = son(def);
		exp arg2 = bro(arg1);
		return reuse_check(arg1) || reuse_check(arg2);
	}
	}

	return 0;
}

/*
 * Or if it is, are we really careful?
 */
static bool
nouse(exp e)
{
	char n = e->tag;

	if (n == test_tag) {
		return 1;
	}

	return 0;
}

/*
 * The routine alloc_variable chooses where to put a declaration. e is the
 * declaration, def is the definition (for identity) or initialisation
 * (for variable), stack is the ash for the current stack position.
 * The place field of the result indicates where the declaration should
 * be put (reg_pl, var_pl etc. - see make_code.h).  num gives the offset
 * (for objects put on the stack) or register mask (for objects put into
 * registers).  new_stack gives the ash of the stack after this declaration.
 * is_new is a flag indicating a new declaration or a reuse of an old
 * declaration.
 */
static allocation
alloc_variable(exp e, exp def, ash stack)
{
	ast locast;
	allocation dc;
	bitpattern ru;

	unsigned char n = def->tag;
	exp s = son(def);
	exp body = bro(def);
	int br = (int)no(e);

	bool force_reg = isusereg(e);
	bool big = (props(e) & 0x80 ? 1 : 0);
	bool in_reg1 = 0, in_reg2 = 0, in_reg3 = 1;

	dc.new_stack = stack;
	dc.is_new = 1;

	if (sh(def)->tag == tophd && !isvis(e)) {
		dc.place = nowhere_pl;
		dc.num = 0;
		return dc;
	}

	if (n == name_tag) {
		in_reg1 = (!isvar(s) && (no(def) == 0 || !isglob(s)));
	} else if (n == cont_tag && s->tag == name_tag) {
		exp t = son(s);
		in_reg2 = (isvar(t) && (no(s) == 0 || !isglob(t)) &&
		           no_side(body));
	}

	if (!isvar(e) && (in_reg1 || in_reg2)) {
		/* Re-identification or contents of variable not altered in body */
		if (in_reg1) {
			dc.place = ptno(s);
#ifndef tdf3
			switch (ptno(s)) {
			case var_pl:
				dc.num = no(s) - no(def);
				break;

			case par3_pl:
			case par2_pl:
				dc.num = no(s) - no(def);
				break;

			default:
				dc.num = no(s) + no(def);
				break;
			}
#else
			if (ptno(s) == var_pl) {
				dc.num = no(s) - no(def);
			} else {
				dc.num = no(s) + no(def);
			}
#endif
		} else {
			s = son(s);
			dc.place = ptno(s);
			if (ptno(s) == var_pl) {
				dc.num = no(s) - no(son(def));
			} else {
				dc.num = no(s) + no(son(def));
			}
		}

		/* We have a declaration */
		if (dc.place == reg_pl) {
			/* If the old one was in registers, reuse it */
			dc.is_new = 0;
			return dc;
		}

		if (!force_reg) {
			if (regable(e)) {
				ru = alloc_reg(sh(def), br, big);
				if (ru) {
					dc.place = reg_pl;
					dc.num = ru;
					return dc;
				}
			}

			if (isglob(s)) {
				locast = add_shape_to_stack(stack, sh(def));
				dc.new_stack = locast.astash;
				dc.place = var_pl;
				if (locast.astadj) {
					dc.num = locast.astoff + locast.astadj;
				} else {
					dc.num = locast.astash;
				}
				return dc;
			}

			/* If there was not room, reuse the old dec */
			dc.is_new = 0;
			return dc;
		}

		if (regable(e)) {
			ru = alloc_reg(sh(def), br, big);
			if (ru) {
				dc.place = reg_pl;
				dc.num = ru;
				return dc;
			}

			if (isglob(s)) {
				locast = add_shape_to_stack(stack, sh(def));
				dc.new_stack = locast.astash;
				dc.place = var_pl;

				if (locast.astadj) {
					dc.num = locast.astoff + locast.astadj;
				} else {
					dc.num = locast.astash;
				}

				return dc;
			}

			dc.is_new = 0;
			return dc;
		}

		return dc;
	}

	if (n == apply_tag || n == apply_general_tag || n == tail_call_tag) {
		in_reg3 = reg_result(sh(def));
	}

	/* Try to allocate in registers */
	if (regable(e) && in_reg3) {
		if ((n == apply_tag || n == apply_general_tag ||
		     n == tail_call_tag) && shtype(sh(def)) != Freg &&
		    nouse(bro(def))) {
			dc.place = reg_pl;
			dc.num = regmsk(REG_D0);
			return dc;
		}

		if (is_a(n)) {
			long rg = reuse(def) & 0x3cfc;
			if (rg) {
				reuseables &= ~rg;
				dc.place = reg_pl;
				dc.num = rg;
				return dc;
			}
		}

		ru = alloc_reg(sh(def), br, big);
		if (ru) {
			dc.place = reg_pl;
			dc.num = ru;
			return dc;
		}
	}

	/* Otherwise allocate on the stack */
	locast = add_shape_to_stack(stack, sh(def));
	dc.new_stack = locast.astash;
	dc.place = var_pl;

	if (locast.astadj) {
		dc.num = locast.astoff + locast.astadj;
	} else {
		dc.num = locast.astash;
	}

	return dc;
}

/*
 * The solve statement with starter s, labelled statements l, destination
 * dest and default jump jr is processed.
 */
static void
solve(exp s, exp l, where dest, exp jr, ash stack)
{
	exp t;
	long r1;

	while (!l->last) {
		allocation dc;
		long lb = next_lab();
		exp record = simple_exp(0);

		if (props(son(bro(l))) & 2) {
			record->last = true;
		}

		no(record) = stack;
		sonno(record) = stack_dec;
		ptno(record) = lb;
		pt(son(bro(l))) = record;
		dc = alloc_variable(bro(l), son(bro(l)), stack);
		ptno(bro(l)) = dc.place;
		no(bro(l)) = dc.num;
		l = bro(l);
	}

	r1 = regsinuse;

	if (s->tag != goto_tag || pt(s) != bro(s)) {
		/* Code the starting expression */
		have_cond = 0;
		make_code(dest, stack, s);
	}

	t = s;

	do {
		regsinuse = r1;
		if (sh(t)->tag != bothd) {
			make_jump(m_bra, ptno(jr));
		}

		t = bro(t);
		if (no(son(t)) > 0) {
			make_label(ptno(pt(son(t))));
			make_code(dest, stack, t);
		}
	} while (!t->last);

	regsinuse = r1;
	have_cond = 0;
}

/*
 * The controlling number of the case statement is in the D1 register, from
 * which already has been deducted.  The list of options is given as a
 * bro-list in arg.  The routine returns the total number which has been
 * deducted from D1 at the end.
 */
static long
caser(exp arg, long already)
{
	bool sw, go = 1, diff = 0;
	exp t, jr, jt, split_at;
	shape sha = sh(arg);
	double low, high;
	double lowest = LONG_MAX, highest = LONG_MIN;
	long i, j, n, *jtab;
	long worth = 0;

	for (t = bro(arg); go && (t != NULL); t = bro(t)) {
		if (is_signed(sh(t))) {
			low = no(t);
		} else {
			low = (unsigned)no(t);
		}

		if (son(t)) {
			if (is_signed(sh(son(t)))) {
				high = no(son(t));
			} else {
				high = (unsigned)no(son(t));
			}
		} else {
			high = low;
		}

		if (low != high) {
			diff = 1;
		}

		if (low < lowest) {
			lowest = low;
		}

		if (high > highest) {
			highest = high;
		}

		worth += (low == high ? 1 : 2);
		if (bro(t) != NULL) {
			double nextlow;

			if (is_signed(sh(bro(t)))) {
				nextlow = no(bro(t));
			} else {
				nextlow = (unsigned)no(bro(t));
			}

			if ((nextlow / 2) > (high / 2) + 20) {
				split_at = t;
				go = 0;
			}
		}

#ifndef tdf3
		if (high / 2 > low / 2 + 20) {
			worth = 0;
		}
#endif
	}

	if (!go) {
		/* Split into two */
		long a;
		exp new = copyexp(arg);
		exp old_bro = bro(split_at);
		bro(new) = old_bro;
		bro(split_at) = NULL;
		split_at->last = true;

		/* Code the first half */
		a = caser(arg, already);

		/* Code the second half */
		return caser(new, a);
	}

	if (worth > 2) {
		/* Construct a jump table */
		mach_op *op1, *op2;
		long rlab = next_lab();
		long tlab = next_lab();
		long slab = next_lab();
		n = highest - lowest + 1;
		jtab = xcalloc(n, sizeof(long));

		for (i = 0; i < n; i++) {
			jtab[i] = rlab;
		}

		for (t = bro(arg); t != NULL; t = bro(t)) {
			if (is_signed(sh(t))) {
				low = no(t);
			} else {
				low = (unsigned)no(t);
			}

			if (son(t)) {
				if (is_signed(sh(son(t)))) {
					high = no(son(t));
				} else {
					high = (unsigned)no(son(t));
				}
			} else {
				high = low;
			}

			j = ptno(pt(son(pt(t))));
			for (i = low; i <= high; i++) {
				jtab[i - (long)lowest] = j;
			}
		}

		/* Move offset into D1 */
		jt = simple_exp(0);
		ptno(jt) = rlab;

		/*
		 * Subtract the lowest value (minus anything already deducted).
		 */
		sub(slongsh, mnw(lowest - already), D1, D1);
		sw = cmp(slongsh, D1, mnw(highest - lowest), tst_gr);
		branch(tst_gr, jt, 0, sw, 0);

		/* Move displacement into D0 */
#if 0
		op1 = make_reg_index(REG_ZA0, REG_D1, 0, 4);
		op1->of->plus->plus = make_lab(slab, 0);
		regsinproc |= regmsk(REG_A0);
		debug_warning("%%za0 used");
#else
		op1 = make_lab_ind(slab, 0);
		i = tmp_reg(m_lea, op1);
		op1 = make_reg_index(i, REG_D1, 0, 4);
#endif
		op2 = make_register(REG_D0);
		make_instr(m_movl, op1, op2, regmsk(REG_D0));

		/* Do the jump */
		op1 = make_reg_index(REG_PC, REG_D0, 2, 1);
		make_instr(m_jmp, op1, NULL, 0);

		/* Print out table */
		make_label(tlab);
		if (!no_align_directives) {
			make_instr(m_as_align4, NULL, NULL, 0);
		}
		make_label(slab);
		for (i = 0; i < n; i++) {
			op1 = make_lab_diff(jtab[i], tlab);
			make_instr(m_as_long, op1, NULL, 0);
		}
		make_label(rlab);

		/* Return the total number deducted from D1 */
		return lowest;
	}

	/* If 'high' is not always equal to 'low', restore value of D1 */
	if (diff) {
		add(slongsh, D1, mnw(already), D1);
		already = 0;
	}

	/* A series of jumps/comparisons */
	for (t = bro(arg); t != NULL; t = bro(t)) {
		if (is_signed(sh(t))) {
			low = no(t);
		} else {
			low = (unsigned)no(t);
		}

		if (son(t)) {
			if (is_signed(sh(son(t)))) {
				high = no(son(t));
			} else {
				high = (unsigned)no(son(t));
			}
		} else {
			high = low;
		}

		jr = pt(son(pt(t)));
		if (low == high) {
			sw = cmp(sha, D1, mnw(low - already), tst_eq);
			branch(tst_eq, jr, 1, sw, 0);
		} else {
			jt = simple_exp(0);
			ptno(jt) = next_lab();
			sw = cmp(sha, D1, mnw(low - already), tst_ls);
			branch(tst_ls, jt, is_signed(sh(t)), sw, 0);
			sw = cmp(sha, D1, mnw((unsigned)(high - already)), tst_le);
			branch(tst_le, jr, is_signed(sh(son(t))), sw, 0);
			make_label(ptno(jt));
		}
	}

	/* Return what has been subtracted from D1 */
	have_cond = 0;

	return already;
}

/*
 * RESET STACK POINTER FROM APPLICATIONS POINTER
 * sp = AP - (env_size - (sizeof(params) + sizeof(ret-addr) + sizeof(AP)))
 */
static void
reset_stack_pointer(void)
{
	mach_op *op1, *op2;
	asm_comment("reset stack pointer ...");
	update_stack();

	op1 = make_indirect(REG_AP, 0);
	op2 = op1->of->plus = new_mach_op();
	op2->type = MACH_NEG;
	op2->plus = make_ldisp(4);

	op2 = make_register(REG_SP);
	make_instr(m_lea, op1, op2, regmsk(REG_SP));

#if 0
	/* gas misinterpret lea a6@(<label>) if <label> isn't declared ?? */
	op1 = make_indirect(REG_AP, 0);
	op2 = new_mach_op();
	op1->of->plus = op2;
	/* The address of cur_proc_dec is used to form the env_size label */
	op3 = make_lab((long)cur_proc_dec, 8 + (cur_proc_callers_size + cur_proc_callees_size) / 8);
	op2->type = MACH_NEG;
	op2->plus = op3;
	op2 = make_register(REG_SP);
	make_instr(m_lea, op1, op2, regmsk(REG_SP));
#endif

	asm_comment("reset stack pointer done");
}

/*
 * This routine checks for jumps to immediately following labels.
 */
static bool
red_jump(exp e, exp la)
{
	if (!la->last && pt(e) == bro(la)) {
		return 1;
	}

	return 0;
}

/*
 * ALLOW SPACE ON STACK
 */
static ash
stack_room(ash stack, where dest, long off)
{
	exp e = dest.wh_exp;

	if (e->tag == ident_tag) {
		if (ptno(e) != var_pl) {
			return stack;
		}

		if (no(e) + off > stack) {
			stack = no(e) + off;
		}
	}

	return stack;
}

/*
 * This routine is the main coding routine for such things as identity
 * definitions and control structures.  Most of the actual expression
 * evaluation is dealt with by codec.  The expression e is coded and
 * the result put into dest.  The stack argument gives the current
 * structure of the stack.
 */
void
make_code(where dest, ash stack, exp e)
{
	bool sw;

	if (e == NULL) {
		error(ERR_SERIOUS, "Internal coding error");
		return;
	}

	switch (e->tag) {
	case ident_tag: {
		long sz;
		int dw = 0;
		allocation dc;
		bool used_once, used_twice;
		bitpattern rg = regsinproc;
		mach_ins *p = current_ins;

		/* Find the identity definition and body */
		exp def = son(e);
		exp body = bro(def);

		/* Check up on uses */
		exp x = pt(e);
		used_once = (x == NULL || pt(x) == NULL);
		used_twice = (used_once || pt(pt(x)) == NULL);

		/* Allocate space for definition */
		if (ismarked(e) && isparam(e) &&  no(e) > 2) {
			/* Rarely used procedure arguments ... */
			dc.is_new = 0;
			dc.place = par_pl;
			dc.num = no(def);
			dc.new_stack = stack;
			extra_weight++;
			dw = 1;
		} else {
			/* And the rest ... */
			dc = alloc_variable(e, def, stack);
		}

		/* Mark the declaration */
		ptno(e) = dc.place;
		no(e) = dc.num;
#ifndef tdf3
		make_visible(e);
#endif

		if (dc.place == var_pl) {
			used_stack = true;
		}

		sz = dc.new_stack;

		/* Does the definition need evaluating? */
		if (dc.is_new) {
			if (ptno(e) == nowhere_pl) {
				/*
				 * Calculate and discard value if not required
				 */
				make_code(zero, stack, def);
			} else {
				/* Encode the definition */
				if (ptno(e) == reg_pl) {
					regsindec |= dc.num;
				}

				make_code(zw(e), stack, def);
			}

			/* Modify regsinuse if a register is being used */
			if (ptno(e) == reg_pl) {
				regsindec &= ~dc.num;
				if (used_once) {
					regsinuse  |=  dc.num;
					reuseables |=  dc.num;
				} else {
					regsinuse  |=  dc.num;
					reuseables &= ~dc.num;
				}
			}

			/* Modify max_stack is the stack is being used */
			if (ptno(e) == var_pl && sz > max_stack) {
				max_stack = sz;
			}
		}

		/* Encode the body */
		make_code(dest, dc.new_stack, body);
		extra_weight -= dw;

		/* Look for peephole optimizations */
		if (dc.is_new && pt(e) == reg_pl) {
			regsinuse &= ~dc.num;
			if (!output_immediately && p && optim & OPTIM_PEEPHOLE) {
				if (used_twice && post_inc_refactor(p, no(e))) {
					regsinproc = rg;
					return;
				}
			}
		}

		return;
	}

#ifdef tdf3
	case clear_tag:
		/* Clear means do nothing */
		return;
#endif

	case seq_tag: {
		/* Sequences */
		bool no_bottom = 1;
		exp t = son(son(e));

		/* Code each sub-expression */
		while (make_code(zero, stack, t),
		       no_bottom = (sh(t)->tag != bothd),
		       !t->last) {
			t = bro(t);
		}

		/* Code the result expression if necessary */
		if (no_bottom) {
			make_code(dest, stack, bro(son(e)));
		}

		return;
	}

	case cond_tag: {
		/* Conditionals */
		long lb, r1;
		allocation dc;
		exp jr, record;
		bool is_condgoto = 0;

		/* Find the first and alternative expressions */
		exp first = son(e);
		exp alt = bro(first);

		/* Check for "if cond goto ..." */
		if (bro(son(alt))->tag == goto_tag) {
			is_condgoto = 1;
		}

		/* Find or create the label */
		if (is_condgoto) {
			record = pt(son(pt(bro(son(alt)))));
		} else {
			lb = next_lab();
			record = simple_exp(0);
			no(record) = stack;
			sonno(record) = stack_dec;
			ptno(record) = lb;
		}

		no(son(alt)) = ptno(record);
		pt(son(alt)) = record;

		/* Allocate space for the alternative expression */
		dc = alloc_variable(alt, son(alt), stack);
		ptno(alt) = dc.place;
		no(alt) = dc.num;

		/* If first is just a jump to alt, just encode alt */
		if (first->tag == goto_tag && pt(first) == alt &&
		    son(first) != NULL && sh(son(first))->tag == tophd) {
			make_code(dest, stack, bro(son(alt)));
			return;
		}

		/* Code the first expression */
		reuseables = 0;
		r1 = regsinuse;
		make_code(dest, stack, first);

		/* Restore regsinuse */
		regsinuse = r1;

		/* If alt is trivial, no further action is required */
		if (bro(son(alt))->tag == top_tag) {
			bitpattern ch = last_jump_regs;
			make_label(ptno(record));
			if (!is_condgoto && !output_immediately &&
			    last_jump == lb) {
				current_ins->changed = ch;
			}
			return;
		}

		/* No further action is required for conditional gotos */
		if (is_condgoto) {
			return;
		}

		/* If first doesn't end with a jump, add one */
		if (sh(first)->tag != bothd) {
			long lb2 = next_lab();
			jr = simple_exp(0);
			ptno(jr) = lb2;
			make_jump(m_bra, lb2);
		}

		/* Encode the alternative expression */
		reuseables = 0;
		make_label(ptno(record));
		make_code(dest, stack, alt);
		regsinuse = r1;
		reuseables = 0;

		/* Output the label for the jump added to first if necessary */
		if (sh(first)->tag != bothd) {
			make_label(ptno(jr));
			retcell(jr);
		}

		have_cond = 0;
		retcell(record);
		return;
	}

	case labst_tag: {
		/* Labelled statements */
		allocation dc;
		have_cond = 0;

		/* Is there long jump access to this label ? */
		if (is_loaded_lv(e)) {
			if (need_preserve_stack) {
				restore_stack();
			} else if (!has_alloca) {
				reset_stack_pointer();
			}
		}

		/* Allocate space */
		dc = alloc_variable(e, son(e), stack);
		if (dc.place == reg_pl) {
			regsinuse |= dc.num;
			reuseables &= ~dc.num;
		}

		/* Encode the body */
		make_code(dest, stack, bro(son(e)));

		/* Update max_stack and regsinuse */
		if (dc.place == var_pl) {
			if (dc.new_stack > max_stack) {
				max_stack = dc.new_stack;
			}
		}

		if (dc.place == reg_pl) {
			regsinuse &= (~dc.num);
		}

		return;
	}

	case rep_tag: {
		/* Loops */
		long lb;
		exp record;
		allocation dc;

		/* Find the starter and the body of the loop */
		exp start = son(e);
		exp body = bro(start);

		/* Allocate space */
		dc = alloc_variable(body, son(body), stack);
		ptno(body) = dc.place;
		no(body) = dc.num;

		/* Code the starter of the loop */
		make_code(zw(body), stack, start);

		/* Create the repeat label */
		lb = next_lab();
		make_label(lb);
		record = simple_exp(0);
		record->last = true;
		no(record) = stack;
		sonno(record) = stack_dec;
		ptno(record) = lb;
		pt(son(body)) = record;
		reuseables = 0;

		/* Encode the body of the loop */
		make_code(dest, stack, body);
		retcell(record);
		return;
	}

	case goto_tag: {
		/* Jumps */
		exp lab;

		/* Try to avoid unnecessary jumps */
		if (e->last && bro(e)->tag == seq_tag &&
		    bro(bro(e))->tag == labst_tag &&
		    red_jump(e, bro(e))) {
			return;
		}

		/* Output the jump */
		lab = pt(e);
		make_jump(m_bra, ptno(pt(son(lab))));
		reuseables = 0;
		return;
	}

	case goto_lv_tag: {
		exp dest_exp = son(e); /* destination label */
		exp cont_exp = getexp(sh(dest_exp), NULL, 1, dest_exp, NULL, 0, 0, cont_tag);
		where wh;
		mach_op *op;
		wh = zw(cont_exp);
		wh.wh_is = RegInd;
		op = operand(32, wh);
		/*epilogue(1);*/
		make_instr(m_jmp, op, NULL, ~save_msk);
		/*ins1(m_jmp,32,D0,0);*/
		return;
	}

#ifndef tdf3
	case return_to_label_tag: {
		exp dest_lab = son(e);

		asm_comment("return_to_label ...");

		move(slongsh, zw(dest_lab), A0);
		restore_regs(ALL);
		make_instr(m_jmp, operand(32, A0_p), NULL, ~save_msk);

		asm_comment("return_to_label done");
		return;
	}
#endif

	case long_jump_tag: {
		exp new_env = son(e);
		exp dest_lab = bro(new_env);
		asm_comment("long_jump");

		move(sh(dest_lab), zw(dest_lab), A0);
		move(sh(new_env), zw(new_env), A1);

		/* restore all registers but A6 or SP */
		restore_regs(NOT_A6_OR_SP);

		move(sh(new_env), A1, AP);
		make_instr(m_jmp, operand(32, A0_p), NULL, ~save_msk);
		return;
	}

	case test_tag: {
		/* Tests */
		exp qwe;
		where qw;
		bool sg = 1, sf = 0;
		int shn;

		/* Find the test number */
		long test_n = (long)props(e);

		/* Find the expressions being compared */
		exp arg1 = son(e);
		exp arg2 = bro(arg1);

		/* Find the label to be jumped to */
		exp lab_exp = pt(e);
		exp jr = pt(son(lab_exp));

		/* If arg1 is not an operand, code it into D1 */
		if (!is_o(arg1->tag)) {
			qwe = sim_exp(sh(arg1), D1);
			qw = zw(qwe);
			regsinproc |= regmsk(REG_D1);
			make_code(qw, stack, arg1);
			arg1 = qwe;
		}

		/* If arg2 is not an operand, code it into D1 */
		if (!is_o(arg2->tag)) {
			qwe = sim_exp(sh(arg2), D1);
			qw = zw(qwe);
			regsinproc |= regmsk(REG_D1);
			make_code(qw, stack, arg2);
			arg2 = qwe;
		}

		/* Look for unsigned or floating tests */
		shn = sh(arg1)->tag;
		switch (shn) {
		case ucharhd:
		case uwordhd:
		case ulonghd:
		case u64hd:
			sg = 0;
			break;

		case shrealhd:
		case realhd:
		case doublehd:
			sg = 0;
			sf = 1;
			break;
		}

		/* Certain comparisons with 1 or -1 can be changed */
		if (arg1->tag == val_tag) {
			long d = no(arg1);
			if (is_offset(arg1)) {
				d /= 8;
			}

			if (d == 1) {
				if (test_n == tst_le) {
					/* 1 <= x becomes 0 < x */
					test_n = tst_ls;
					no(arg1) = 0;
				} else if (test_n == tst_gr) {
					/* 1 > x becomes 0 >= x */
					test_n = tst_ge;
					no(arg1) = 0;
				}
			} else if (d == -1 && sg) {
				if (test_n == tst_ls) {
					/* -1 < x becomes 0 <= x */
					test_n = tst_le;
					no(arg1) = 0;
				} else if (test_n == tst_ge) {
					/* -1 >= x becomes 0 > x */
					test_n = tst_gr;
					no(arg1) = 0;
				}
			}
		}

		/* Certain other comparisons with 1 or -1 can be changed */
		if (arg2->tag == val_tag) {
			long d = no(arg2);
			if (is_offset(arg2)) {
				d /= 8;
			}

			if (d == 1) {
				if (test_n == tst_ge) {
					/* x >= 1 becomes x > 0 */
					test_n = tst_gr;
					no(arg2) = 0;
				} else if (test_n == tst_ls) {
					/* x < 1 becomes x <= 0 */
					test_n = tst_le;
					no(arg2) = 0;
				}
			} else if (d == -1 && sg) {
				if (test_n == tst_gr) {
					/* x > -1 becomes x >= 0 */
					test_n = tst_ge;
					no(arg2) = 0;
				} else if (test_n == tst_le) {
					/* x <= 1 becomes x < 0 */
					test_n = tst_ls;
					no(arg2) = 0;
				}
			}
		}

		if (shn == u64hd || shn == s64hd) {
			where w1, w2;
			w1 = zw(arg1);
			w2 = zw(arg2);

			/* compare low word (unsigned) */
			sw = cmp(ulongsh, w1, w2, test_n);
			branch(test_n, jr, sg, sw, sf);

			/* compare high word */
			w1.wh_off += 32;
			w2.wh_off += 32;

			if (sg) {
				sw = cmp(slongsh, w1, w2, test_n);
			} else {
				sw = cmp(ulongsh, w1, w2, test_n);
			}

			branch(test_n, jr, sg, sw, sf);
			return;
		}

		/* Code the comparison */
		sw = cmp(sh(arg1), zw(arg1), zw(arg2), test_n);

		/* Output the condition jump */
		branch(test_n, jr, sg, sw, sf);
		return;
	}

	case testbit_tag: {
		/* Bit tests */
		exp qwe;
		where qw;

		/* Find the arguments */
		exp arg1 = son(e);
		exp arg2 = bro(arg1);

		/* Find the label to be jumped to */
		exp lab_exp = pt(e);
		exp jr = pt(son(lab_exp));

		/* If arg1 is not an operand, code it into D1 */
		if (!is_o(arg1->tag)) {
			qwe = sim_exp(sh(arg1), D1);
			qw = zw(qwe);
			regsinproc |= regmsk(REG_D1);
			make_code(qw, stack, arg1);
			arg1 = qwe;
		}

		/* If arg2 is not an operand, code it into D1 */
		if (!is_o(arg2->tag)) {
			qwe = sim_exp(sh(arg2), D1);
			qw = zw(qwe);
			regsinproc |= regmsk(REG_D1);
			make_code(qw, stack, arg2);
			arg2 = qwe;
		}

		/* Code the test */
		bit_test(sh(arg1), zw(arg1), zw(arg2));

		/* Output the conditional jump */
		branch((long)props(e), jr, 1, 0, 0);
		return;
	}

	case ass_tag:
	case assvol_tag: {
		/* Variable assignments */
		exp assdest = son(e);
		exp assval = bro(assdest);
		asm_comment("assign ...");
		if (sh(assval)->tag == bitfhd) {
			int_to_bitf(assval, e, stack);
			return;
		}

		codec(zw(e), stack, assval);
		asm_comment("assign done");
		return;
	}

	case nof_tag: {
		shape sha;
		long crt, off;
		exp v;

		v = son(e);
		if (v == NULL) {
			return;
		}

		if (dest.wh_exp->tag == val_tag) {
			return;
		}

		sha = sh(v);
		crt = dest.wh_off;
		off = rounder(shape_size(sha), shape_align(sha));

		for (;;) {
			where wh;
			ash stack2;
			wh = mw(dest.wh_exp, crt);
			stack2 = stack_room(stack, dest, off + crt);
			make_code(wh, stack2, v);
			if (v->last) {
				return;
			}
			crt += off;
			v = bro(v);
		}

		/* Not reached */
	}

	case ncopies_tag: {
		where wh;
		long n = no(e);
		shape sha = sh(son(e));
		long sz = rounder(shape_size(sha), shape_align(sha));

		if (n == 0) {
			return;
		}

		if (dest.wh_exp->tag == val_tag) {
			return;
		}

		if (n == 1) {
			make_code(dest, stack, son(e));
			return;
		}

		if (sz == 8 || sz == 16 || sz == 32) {
			make_code(D1, stack, son(e));
			regsinproc |= regmsk(REG_D1);
			if (n <= 10) {
				long i;
				for (i = 0; i < n; i++) {
					wh = mw(dest.wh_exp, dest.wh_off + i * sz);
					move(sha, D1, wh);
				}
				return;
			} else {
				mach_op *op1, *op2;
				long lab = next_lab();
				int instr = ins(sz, ml_mov);
				mova(dest, A0);
				regsinproc |= regmsk(REG_A0);
				move(slongsh, mnw(n - 1), D0);
				make_label(lab);
				op1 = make_register(REG_D1);
				op2 = make_postinc(REG_A0);
				make_instr(instr, op1, op2, regmsk(REG_A0));
				op1 = make_register(REG_D0);
				op2 = make_lab_data(lab, 0);
				make_instr(m_dbf, op1, op2, regmsk(REG_D0));
				return;
			}
		}

		make_code(dest, stack, son(e));
		wh = mw(dest.wh_exp, dest.wh_off + sz);
		move_bytes(sz * (n - 1), dest, wh, 0);
		return;
	}

	case concatnof_tag: {
		ash stack2;
		exp a1 = son(e);
		exp a2 = bro(a1);
		long off = dest.wh_off + shape_size(sh(a1));
		make_code(dest, stack, a1);
		stack2 = stack_room(stack, dest, off);
		make_code(mw(dest.wh_exp, off), stack2, a2);
		return;
	}

#ifndef tdf3
	case apply_tag:
	case apply_general_tag:
		apply_general_proc(e, dest, stack);
		return;

	case tail_call_tag: {
		int old_stack_dec = stack_dec;
		tail_call(e, dest, stack);
		stack_dec = old_stack_dec;
		return;
	}

	case caller_tag:
		make_code(dest, stack, son(e));
		return;

	case trap_tag:
		trap_ins(no(e));
		return;
#endif

#if 0
	case apply_tag: {
		/* Procedure applications */
#ifndef tdf3
#else
		static int apply_tag_flag = 0;
#endif
		exp t;
		ash st;
		long comp_room = 0;
		long longs = 0, stkdec;
		long start_stack = stack_dec;
		bool use_push = 1, reg_res;

		/* Find the procedure and the arguments */
		exp proc = son(e);
		exp arg = (proc->last ? NULL : bro(proc));

#if 0
		/*
		 * Not a normal procedure call, but a way to specify a debuger
		 * break point.
		 */
		if ((brog(son(proc)) ->processed) &&
		    (brog(son(proc)) ->extnamed) &&
		    (streq(brog(son(proc))->name, "_TESTPOINT"))) {
			TESTPOINT();
			return;
		}
#endif

		asm_comment("Call Normal Proc");
		/* See if we can push all the arguments */
		st = 0;
		if (arg != NULL) {
			t = arg;
			while (t != NULL) {
				ast a;
				if (cpd_param(sh(t))) {
					use_push = 0;
				}
				if ((sh(t)->tag == s64hd) ||
				    (sh(t)->tag == u64hd)) {
					use_push = 0;
				}
				if (!push_arg(t)) {
					use_push = 0;
				}
				a = add_shape_to_stack(st, sh(t));
				st = a.astash;

				t = (t->last ? NULL : bro(t));
			}
		}
		longs = st;

		/* Does the result go into a register? */
		reg_res = reg_result(sh(e));
		if (!reg_res) {
			if (eq_where(dest, zero)) {
				/* Calculate room for ignored compound result */
				/* todo: use symbol instead of 32 */
				comp_room = iround(shape_size(sh(e)), 32);
			}
		}

		/* Find total amount of stack decrease */
		stkdec = longs + comp_room;

		/* Put arguments onto stack */
		if (use_push) {
			asm_comment("Push callers");
			if (comp_room) {
				/* Make room for unwanted compound result */
				dec_stack(comp_room);
				stack_dec -= comp_room;
			}

			/* Push the arguments */
			if (arg != NULL) {
				code_pars(zw(e), stack, arg);
			}
		} else {
			asm_comment("Place callers");
			/* Decrease stack */
			if (stkdec) {
				dec_stack(stkdec);
			}

			stack_dec -= stkdec;
			/* Indicate recursive calls */
			apply_tag_flag++;
			/* Encode the arguments onto the stack */
			st = 0;
			t = arg;

			while (t != NULL) {
				ast a;
				where stp;
				long adj = 0;
				char nc = sh(t)->tag;

				if (nc == scharhd || nc == ucharhd) {
					adj = 24;
				}

				if (nc == swordhd || nc == uwordhd) {
					adj = 16;
				}

				stp = mw(SP_p.wh_exp, st + adj);
				make_code(stp, stack, t);
				a = add_shape_to_stack(st, sh(t));
				st = a.astash;
				t = (t->last ? NULL : bro(t));
			}

			apply_tag_flag--;
		}
		start_stack -= stack_dec;

		/*
		 * For results which do not fit into registers a pointer to
		 * where the result is to be put is passed in in A1.
		 */
		if (!reg_res) {
			if (comp_room) {
				/*
				 * Find the space allocated for unwanted
				 * results.
				 */
				where w;
				w = mnw(longs / 8);
				add(slongsh, SP, w, A1);
			} else {
				/*
				 * Find the address of where the result is to
				 * be put.
				 */
				tmp_reg_prefer = REG_A1;
				if (apply_tag_flag) {
					/*
					 * For recursive calls we need to be
					 * very careful if the result is itself
					 * to be a procedure argument to get
					 * the right stack offset.
					 */
					long ex = extra_stack;
					long doff = dest.wh_off;
					extra_stack += start_stack;
					dest.wh_off = 0;

					if (eq_where(dest, SP_p)) {
						/* Careful! */
						dest.wh_off = doff +
						              extra_stack;
						mova(dest, A1);
						dest.wh_off = doff;
					} else {
						/* Easy */
						dest.wh_off = doff;
						mova(dest, A1);
					}
					extra_stack = ex;
				} else {
					/* Otherwise (easy) ... */
					mova(dest, A1);
				}
			}

			/* Make sure we don't reuse A1 accidently */
			avoid_tmp_reg(REG_A1);
			regsinproc |= regmsk(REG_A1);
		}

		/* Output the call instruction */
		callins(longs, son(e));
		stack_dec += stkdec;
		have_cond = 0;

		/* Throw away unwanted compound result */
		if (comp_room) {
			dec_stack(-comp_room);
			return;
		}

		/* Throw away unwanted simple result */
		if (eq_where(dest, zero)) {
			return;
		}

		/* Now move the result into place */
		if (reg_res) {
			if (shape_size(sh(e)) <= 32) {
				/* Small register results are in D0 */
				move(sh(e), D0, dest);
				return;
			} else {
				/* Larger register results are in D0 and D1 */
#ifdef SYSV_ABI
				move(sh(e), FP0, dest);
#else
				move(sh(e), D0_D1, dest);
				regsinproc |= regmsk(REG_D1);
#endif
				return;
			}
		} else {
			/*
			 * Compound results should already have been copied to
			 * the position pointed to by A1 by the called
			 * procedure and returned by it in D0, so no further
			 * action should be required by the calling procedure.
			 * Unfortunately cc doesn't always get this right for
			 * union results.
			 */
#ifdef OLD_SPEC
			if (cconv == CCONV_HP && sh(e)->tag == unhd) {
				regsinproc |= regmsk(REG_A0);
				move(slongsh, D0, A0);
				move(sh(e), A0_p, dest);
			}
#endif
			return;
		}
	}
#endif

	case alloca_tag: {
		/* Local memory allocation */
		exp s = son(e);
		where size_w;
		bool allocation_done = 0;
		used_stack = true;

		asm_comment("Allocate ...");

		/* Create a where representing the value to be allocated */

		if (s->tag == val_tag) {
			long off = no(s);
			if (!is_offset(s)) {
				off *= 8;
			}
			off = rounder(off, stack_align);

			if (checkalloc(e)) {
				size_w = mw(zeroe, off / 8);
			} else {
				/* simple allocation of constant */
				dec_stack(off);
				allocation_done = 1;
			}
		} else {
			size_w = zw(s);
		}

		/* Allocate (checked or not) */

		if (!allocation_done) {
			if (checkalloc(e)) {
				checkalloc_stack(size_w, 1);
			} else {
				sub(slongsh, size_w, SP, SP);
			}
		}

		/* The result of the construct is SP */

		if (!eq_where(dest, zero)) {
			move(sh(e), SP, dest);
		}

		have_cond = 0;

		if (need_preserve_stack) {
			save_stack();
		}

		asm_comment("Allocate done");
		return;
	}

	case last_local_tag:
		asm_comment("last_local ...");
		move(sh(e), SP, dest);
		asm_comment("last_local done");
		return;

	case local_free_tag: {
		exp base = son(e);
		exp offset = bro(base);
		exp s_a0 = sim_exp(sh(base), A0);
		where w_a0;
		w_a0 = zw(s_a0);

		asm_comment("local_free ...");

		make_code(w_a0, stack, base);

		if (offset->tag == val_tag) {
			long off = no(offset);

			if (!is_offset(offset)) {
				off *= 8;
			}
			off = rounder(off, stack_align) / 8;
			add(sh(offset), A0, zw(offset), SP);
		} else {
			exp s_d0 = sim_exp(sh(offset), D0);
			where w_d0;
			w_d0 = zw(s_d0);
			make_code(w_d0, stack, offset);
			add(sh(offset), mnw(7), D0, D0);
			and (sh(offset), D0, mnw(~7), D0);
			add(sh(offset), A0, D0, SP);
		}

		if (need_preserve_stack) {
			save_stack();
		}

		asm_comment("local_free done");

		return;
	}

	case local_free_all_tag:
		must_use_bp = true;
		asm_comment("local_free_all ...");
		reset_stack_pointer();

		if (need_preserve_stack) {
			save_stack();
		}

		asm_comment("local_free_all done");
		return;

#ifndef tdf3
	case untidy_return_tag:
#endif
	case res_tag: {
		shape rsha;

		/* Procedure results */
		have_cond = 0;

		rsha = sh(son(e));

		/* Does the result go into a register? */
		if (reg_result(rsha)) {
			if (shape_size(rsha) <= 32) {
				/* Small register results go into D0 */
				make_code(D0, stack, son(e));
			} else {
#ifdef SYSV_ABI
				make_code(FP0, stack, son(e));
#else
				/*
				 * Larger register results go into D0
				 * and D1.
				 */
				make_code(D0_D1, stack, son(e));
				regsinproc |= regmsk(REG_D1);
#endif
			}

			/* Jump to the return label */
			if (rsha->tag != bothd) {
#ifndef tdf3
				if (e->tag == untidy_return_tag) {
					untidy_return();
				} else
#endif
					make_jump(m_bra, crt_ret_lab);
			}

			return;
		}

		/*
		 * Otherwise the result has to be encoded into the
		 * position pointed to by A1 at the start of the
		 * procedure. This value was stored in A6_4. The value
		 * of this pointer is returned in D0.
		 */
		if (son(e)->tag == apply_tag ||
			son(e)->tag == apply_general_tag) {
			make_code(A6_4_p, stack, son(e));
		} else {
			codec(A6_4_p, stack, son(e));
		}

#ifdef SYSV_ABI
		move(slongsh, A6_4, A1);
#else
		move(slongsh, A6_4, D0);
#endif

		regsinproc |= regmsk(REG_A1);
#ifndef tdf3
		if (e->tag == untidy_return_tag) {
			untidy_return();
		} else
#endif
			make_jump(m_bra, crt_ret_lab);
		return;
	}

	case solve_tag: {
		/* Solve statements */
		long lb = next_lab();
		exp jr = simple_exp(0);
		ptno(jr) = lb;
		solve(son(e), son(e), dest, jr, stack);
		make_label(lb);
		retcell(jr);
		return;
	}

	case case_tag: {
		/* Case statements */
		exp d1;
		where w1;
		bool old_D1_sp = D1_is_special;
		exp arg1 = son(e);
		exp t = arg1;

		/* Mark the end of the cases */
		while (!t->last) {
			t = bro(t);
		}
		bro(t) = NULL;

		d1 = sim_exp(sh(arg1), D1);
		w1 = zw(d1);
		D1_is_special = 1;
		regsinproc |= regmsk(REG_D1);
		make_code(w1, stack, arg1);

		change_var_sh(slongsh, sh(arg1), w1, D1);
		D1_is_special = old_D1_sp;

		/* Output the case statement */
		IGNORE caser(arg1, 0L);

		retcell(d1);
		return;
	}

	case movecont_tag: {
		/* This is done by a library call to memmove */
		exp from_exp = son(e);
		exp to_exp = bro(from_exp);
		exp num_bytes = bro(to_exp);
		mach_op *op = make_extern_ind(abi == ABI_SUNOS ? "_bcopy" : "_memmove", 0);
		asm_comment("move_some ...");
		push(slongsh, 32L, D0);
		push(slongsh, 32L, D1);
		push(slongsh, 32L, zw(num_bytes));

		if (abi == ABI_SUNOS) {
			push(slongsh, 32L, zw(to_exp));
			push(slongsh, 32L, zw(from_exp));
		} else {
			push(slongsh, 32L, zw(from_exp));
			push(slongsh, 32L, zw(to_exp));
		}

		make_instr(m_call, op, NULL, 0);
		dec_stack(-96);
		pop(slongsh, 32L, D1);
		pop(slongsh, 32L, D0);
		asm_comment("move_some done");
		return;
	}

	case diagnose_tag:
		if (diag != DIAG_NONE) {
			diag_start(dno(e), e);
			make_code(dest, stack, son(e));
			diag_end(dno(e), e);
		} else {
			make_code(dest, stack, son(e));
		}
		return;

	case prof_tag:
		return;

	default:
		if (!is_a(e->tag)) {
			error(ERR_SERIOUS, "Bad operation");
			return;
		}

		if (dest.wh_exp->tag != val_tag) {
			/* All other cases are passed to codec */
			codec(dest, stack, e);
			return;
		} else if (!optop(e)) {
			/*
			 * An operation with an error jump must always be
			 * performed, even if the result is discarded.
			 */
			codec(zero, stack, e);
			return;
		}
	}
}

