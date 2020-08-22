/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines the scan through a program which reorganises it so that all
 * arguments of operations are 80386 operands. 80386 specific.
 *
 * These procedures use a pair of a boolean and and exp (eg sto and to)
 * instead of a pointer to an exp. The boolean is true if the exp being
 * referred to is the child of the given exp, and false if it is the next.
 *
 * This is to allow exps to be represented by indices into arrays and to
 * allow the arrays to be realloced, which invalidates the use of
 * &child(to) and &next(to).
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/exp.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/label_ops.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include "localtypes.h"
#include "make_code.h"
#include "ops.h"
#include "scan.h"

#define assexp(ischild, p, v) if (ischild)setchild(p, v); else setnext(p, v)
#define contexp(ischild, p)((ischild)? child(p): next(p))

/*
 * Inserts an identity declaration of x at to,
 * and replaces x by a use of the identifier
 */
static void
cca(int sto, exp to, int sx, exp x)
{
	exp def, ato, id, tag;
	def = contexp(sx, x);

	/* position sensitive */
	if (def->tag == caller_tag) {
		cca(sto, to, 1, def);
		return;
	}

	ato = contexp(sto, to);
	id  = getexp(sh(ato), next(ato), (int)(ato->last), def, NULL, 0, 1, ident_tag);
	tag = getexp(sh(def), next(def), (int)(def->last), id, NULL, 0, 0, name_tag);
	pt(id) = tag;
	def->last = false;

	if (def != ato) {
		next(def) = ato;
		next(ato) = id;
		ato->last = true;
		assexp(sto, to, id);
		assexp(sx, x, tag);
	} else {
		next(def) = tag;
		next(tag) = id;
		tag->last = true;
		def->last = false;
		assexp(sto, to, id);
	}

#ifdef TDF_DIAG4
	if (diag != DIAG_NONE) {
		dgf(id) = dgf(next(child(id)));
		dgf(next(child(id))) = NULL;
	}
#endif
}

/*
 * Keeping the same to, scans along the next list e, applying cca to introduce
 * an identity declaration when doit is 1.
 *
 * Keeps count as the index position along the list in order to pass it to doit.
 *
 * If it uses cca it scans the resulting declaration, using the same to. If it
 * doesnt use cca, it scans the list element, still using the same to.
 * This keeps all operations in the same order.
 *
 * Result of cc is true if the operands are all of 80386 form. Some operations
 * are allowed to have not more than one operand not of 80386 form; this is then
 * precomputed in reg0 before the operations. This boolean result is used
 * to ensure that not more than one operand is so treated.
 */
static int
cc(int sto, exp to, int se, exp e,
	int (*doit)(exp, int, int),
	int count, int usereg0)
{
	int unused = usereg0;	/* can still use reg0 */
	exp ec = contexp(se, e);

	if (ec->last) {
		if (doit(ec, count, unused)) {
			cca(sto, to, se, e);
			ec = contexp(sto, to);
			return scan(1, ec, child(ec), unused);
		} else {
			if (unused) {
				return scan(se, e, ec, 1);
			}
			return scan(sto, to, ec, unused);
		}
	} else {
		unused = cc(sto, to, 0, ec, doit, count + 1, unused);
		/* can we still use reg0? */
		ec = contexp(se, e);
		if (doit(ec, count, unused)) {
			cca(sto, to, se, e);
			ec = contexp(sto, to);
			return scan(1, ec, child(ec), unused);
		} else {
			if (unused) {
				return scan(sto, to, ec, 1);
			}
			return scan(sto, to, ec, unused);
		}
	}
}

/*
 * Keeping the same to, scans along the next list e, applying cca to introduce
 * an identity declaration when doit is 1.
 *
 * Keeps count as the index position along the list in order to pass it to doit.
 *
 * If it uses cca it scans the resulting declaration, using the same to. If it
 * doesnt use cca, it scans the list element, still using the same to.
 * This keeps all operations in the same order.
 *
 * The difference in detail from cc supports the asymmetry of div etc.
 */
static void
cc1(int sto, exp to, int se, exp e,
	int (*doit)(exp, int, int),
	int count, int usereg0)
{
	/* can we still use reg0? */
	int unused = ((count == 1) ? usereg0 : 0);

	exp ec = contexp(se, e);
	if (ec->last) {
		if (doit(ec, count, unused)) {
			cca(sto, to, se, e);
			ec = contexp(sto, to);
			IGNORE scan(1, ec, child(ec), unused);
			return;
		} else {
			if (unused) {
				IGNORE scan(se, e, ec, 1);
				return;
			}
			IGNORE scan(sto, to, ec, unused);
			return;
		}
	} else {
		cc1(sto, to, 0, ec, doit, count + 1, unused);
		/* can we still use reg0? */
		ec = contexp(se, e);
		if (doit(ec, count, unused)) {
			cca(sto, to, se, e);
			ec = contexp(sto, to);
			IGNORE scan(1, ec, child(ec), unused);
			return;
		} else {
			if (unused) {
				IGNORE scan(se, e, ec, 1);
				return;
			}
			IGNORE scan(sto, to, ec, unused);
			return;
		}
	}
}

/*
 * Does cca and forces the declaration to use a register
 */
static void ccp
(int sto, exp to, int sx, exp x)
{
	exp toc;
	cca(sto, to, sx, x);
	toc = contexp(sto, to);
	setusereg(toc);
	IGNORE scan(1, toc, child(toc), 0);
}

/*
 * Is an operand
 */
static int
is_opnd(exp e)
{
	unsigned char  n = e->tag;

	/* make sure (is_o && is_crc -> !is_opnd) */
	if (n == name_tag) {
		if (isvar(child(e))) {
			return isglob(child(e)) && !PIC_code;
		}

		return child(child(e)) != NULL &&
		       (!isglob(child(e)) || !PIC_code || sh(child(e))->tag != prokhd ||
		        (nextg(child(e)) -> extnamed)) &&
		       (child(child(e))->tag != ident_tag || !isparam(child(child(e))));
	}

	return
	    n == val_tag || n == real_tag || n == env_size_tag ||
	    n == cont_tag ||
	    n == string_tag ||
	    n == null_tag ||
	    n == proc_tag || n == general_proc_tag;
}

/*
 * This checks the integer argument of an addptr to make sure that it is of the
 * right form, including the scale factor for the kind of operand.
 *
 * This introduces two declarations, only the inner one forces the use of
 * a register.
 *
 * This guarantees that we only load the registers as close to the actual
 * instruction as possible, since we are short of registers on the 80386
 */
static void
ap_argsc(int sto, exp to, exp e)
{
	exp p, a, q;
	int  k;
	int do1 = 1;

	if (child(e)->tag == reff_tag) {
		q = child(child(e));
	} else {
		q = child (e);    /* q must be addptr - all addptrs processed here */
	}

	if ((frame_al_of_ptr(sh(child(q))) & al_includes_vcallees) &&
	    (frame_al1_of_offset(sh(next(child(q)))) & al_includes_caller_args)) {
		/* env_offset to arg requires indirection from frame pointer */
		shape pc_sh = f_pointer(f_callers_alignment(0));
		exp c = getexp(pc_sh, next(child(q)), 0, NULL, NULL, 0, 0, cont_tag);
		exp r = getexp(pc_sh, c, 1, child(q), NULL, 0, 64, reff_tag);
		setfather(r, child(q));
		child(c) = r;
		child(q) = c;
	}

	p = child(q);
	a = next(p);

	if (p->tag == name_tag && isvar(child(p)) && isglob(child(p))) {
		do1 = 0;
	}

	if (do1) {
		ccp(1, e, 1, q);
	}

	if (a->tag == offset_mult_tag && next(child(a))->tag == val_tag &&
	    (k = no(next(child(a))), k == 8 || k == 16 || k == 32 || k == 64)) {
		ccp(1, e, 1, next(child(q)));
	} else {
		ccp(1, e, 0, child(q));
	}

	if (do1) {
		cca(sto, to, 1, child(e));
		cca(sto, to, 1, next(child(child(e))));
	} else {
		cca(sto, to, 1, child(e));
	}
}

/*
 * Checks that the argument of a cont or the destination of an assign has the
 * right form for an operand, and introduces a declaration if not.
 *
 * Continues processing with the same to.
 *
 * These arguments can contain declarations, so that we can load addresses as
 * close as possible to the instructions that use them, since we are short
 * of registers in the 80386.
 *
 * This is done by contop, during the code production.
 */
static int
cont_arg(int sto, exp to, exp e, int usereg0)
{
	unsigned char  n = child(e)->tag;

	if (n == name_tag && isvar(child(child(e)))) {
		return usereg0;
	}

	if (n == cont_tag && usereg0 && shape_size(sh(e)) <= 32) {
		cont_arg(sto, to, child(e), 1);
		return 0;
	}

	if (n == reff_tag) {
		exp s = child(child(e));
		if (s->tag == name_tag) {
			if (isusereg(child(s))) {
				return 0;
			}
			if (!PIC_code && isglob(child(s)) && isvar(child(s))) {
				return 0;
			}
		}

		if (s->tag == cont_tag && usereg0 && shape_size(sh(e)) <= 32) {
			cont_arg(sto, to, s, 1);
			return 0;
		}

		if (s->tag == addptr_tag) {
			ap_argsc(sto, to, e);
			return 0;
		}
	}

	if (n == addptr_tag) {
		ap_argsc(sto, to, e);
		return 0;
	}

	if (n == reff_tag) {
		ccp(1, e, 1, child(e));
	} else {
		ccp(1, e, 1, e);
	}

	cca(sto, to, 1, child(e));

	return 0;
}

/* Is assignable */
static int
is_assable(exp e)
{
	return is_a(e->tag) || e->tag == alloca_tag ||
	       ((e->tag == apply_tag || e->tag == apply_general_tag) &&
	        (sh(e)->tag <= ulonghd || sh(e)->tag == ptrhd));
}

/* doit routine, is not an operand */
static int
notopnd(exp t, int c, int usereg0)
{
	UNUSED(c);

	if (usereg0) {
		if (is_opnd(t)) {
			return 0;
		}

		return !is_assable(t);
	}

	return !is_opnd(t);
}

static int scan_for_alloca(exp);

static int
scan_alloc_args(exp s)
{
	if (scan_for_alloca(s)) {
		return 1;
	}

	if (s->last) {
		return 0;
	}

	return scan_alloc_args(next(s));
}

static int
scan_for_alloca(exp t)
{
	switch (t->tag) {
	case local_free_all_tag:
	case local_free_tag:
	case last_local_tag:
	case alloca_tag:
	case make_lv_tag:
		return 1;

	case case_tag:
		return scan_for_alloca(child(t));

	case labst_tag:
		return scan_for_alloca(next(child(t)));

	case env_offset_tag:
	case string_tag:
	case name_tag:
		return 0;

	case apply_general_tag:
		if call_is_untidy(t) {
			return 1;
		}

		return scan_alloc_args(child(t));

	default:
		if (child(t) == NULL) {
			return 0;
		}

		return scan_alloc_args(child(t));
	}
}

static int
no_alloca(exp t, int c, int usereg0)
{
	UNUSED(c);
	UNUSED(usereg0);

	return scan_for_alloca(t);
}

/* Uses cc, requiring all to be operands */
static void
all_opnd(int sto, exp to, exp e, int usereg0)
{
	IGNORE cc(sto, to, 1, e, notopnd, 1, usereg0);
}

/* doit routine, not assignable */
static int
notass(exp t, int i, int usereg0)
{
	UNUSED(i);
	UNUSED(usereg0);

	return !is_assable(t);
}

/* Uses cc, requiring all to be assignable */
static void
all_assable(int sto, exp to, exp e)
{
	IGNORE cc(sto, to, 1, e, notass, 1, 1);
}

/* Just used in the next routine */
static int
is_direct(exp e)
{
	unsigned char  s = e->tag;

	return (s == name_tag && !isglob(child(e)) && !isvar(child(e))) ||
	       (s == cont_tag && child(e)->tag == name_tag &&
	        !isglob(child(child(e))) && isvar(child(child(e))));
}

/* Is indirectly addressable */
static int
is_indable(exp e)
{
	unsigned char s;

	s = e->tag;
	if (s == name_tag) {
		return 1;
	}

	if (s == cont_tag) {
		unsigned char  t = child(e)->tag;
		return (t == name_tag && isvar(child(child(e)))) ||
		       (t == cont_tag && child(child(e))->tag == name_tag &&
		        isvar(child(child(child(e))))) ||
		       (t == reff_tag && is_direct(child(child(e))));
	}

	return (s == reff_tag && is_direct(child(e))) ||
	       s == addptr_tag;
}

/* child must be indirectly addressable */
static void
indable_child(int sto, exp to, exp e)
{
	if (!is_indable(child(e))) {
		exp ec;
		cca(sto, to, 1, e);
		ec = contexp(sto, to);
		IGNORE scan(1, ec, child(ec), 0);
	} else {
		IGNORE scan(sto, to, child(e), 0);
	}
}

/* Apply scan to this next list, moving "to" along it */
static void
scanargs(int st, exp e, int usereg0)
{
	exp t = e;
	exp temp;

	while (temp = contexp(st, t), IGNORE scan(st, t, temp, usereg0),
	       temp = contexp(st, t), !temp->last) {
		t = contexp(st, t);
		st = 0;
	}
}

/* doit routine for plus first arg cant be negate, others can */
static int
plusdo(exp t, int i, int usereg0)
{
	UNUSED(i);

	if (usereg0) {
		return 0;
	}

	if (t->tag == neg_tag) {
		return 0;
	}

	return !is_opnd(t);
}

/* doit routine for mult */
static int
multdo(exp t, int i, int usereg0)
{
	UNUSED(i);

	return usereg0 ? 0 : !is_opnd(t);
}

/* doit routine for and */
static int
anddo(exp t, int i, int usereg0)
{
	UNUSED(i);

	return usereg0 ? 0 : !is_opnd(t);
}

/* doit routine for xor */
static int
notado(exp t, int i, int usereg0)
{
	UNUSED(i);

	return usereg0 ? 0 : !is_opnd(t);
}

/* Change offset representation bytes to bits */
static void
make_bitfield_offset(exp e, exp pe, int spe, shape sha)
{
	exp omul;
	exp val8;

	if (e->tag == val_tag) {
		return;
	}

	omul = getexp(sha, next(e), (int)(e->last), e, NULL, 0, 0, offset_mult_tag);
	val8 = getexp(slongsh, omul, 1, NULL, NULL, 0, 8, val_tag);

	e->last = false;
	setnext(e, val8);
	assexp(spe, pe, omul);
}

static void
scan_apply_args(int spto, exp pto, int sato, exp ato)
{
	if (scan_alloc_args(contexp(sato, ato))) {
		IGNORE cc(spto, pto, sato, ato, no_alloca, 1, 0);
	} else {
		IGNORE scanargs(sato, ato, 1);
	}
}

/* Avoid registers corrupted by dynamic callees */
static void
cca_for_cees(int sto, exp to, exp e)
{
	if (child(e)->tag == name_tag) {
		if (!isglob(child(child(e)))) {
			set_intnl_call(child(child(e)));
		}

		return;
	}

	if (child(e)->tag == cont_tag && child(child(e))->tag == name_tag) {
		if (!isglob(child(child(child(e))))) {
			set_intnl_call(child(child(child(e))));
		}

		return;
	}

	cca(sto, to, 1, e);
	set_intnl_call(contexp(sto, to));
}

static int
is_asm_opnd(exp e, int ext)
{
	unsigned char n = e->tag;

	UNUSED(ext);

	if (n == name_tag) {
		setvis(child(e));
		return 1;
	}

	if (n == cont_tag && child(e)->tag == name_tag && isvar(child(child(e)))) {
		setvis(child(child(e)));
		return 1;
	}

	return n == val_tag || n == real_tag || n == null_tag ||
	       (n == reff_tag && child(e)->tag == name_tag);
}

static int
is_asm_var(exp e, int ext)
{
	unsigned char n = e->tag;

	UNUSED(ext);

	if (n == name_tag && isvar(child(e))) {
		setvis(child(e));
		return 1;
	}

	return 0;
}

void
check_asm_seq(exp e, int ext)
{
	if (e->tag == asm_tag) {
		if ((asm_string(e) && child(e)->tag == string_tag) ||
		    (asm_in(e) && is_asm_opnd(child(e), ext)) ||
		    (asm_var(e) && is_asm_var(child(e), ext))) {
			return;
		}
	}

	if (e->tag == seq_tag) {
		exp t;

		for (t = child(child(e)); ; t = next(t)) {
			check_asm_seq(t, ext);
			if (t->last) {
				break;
			}
		}

		check_asm_seq(next(child(e)), ext);
	} else if (e->tag != top_tag) {
		error(ERR_INTERNAL, "illegal ~asm");
	}
}

/* Main scan routine */
int
scan(int sto, exp to, exp e, int usereg0)
{
	switch (e->tag) {
	case prof_tag:
		return 0;

	case cond_tag:
	case rep_tag:
	case compound_tag:
	case solve_tag:
	case nof_tag:
	case concatnof_tag:
	case ncopies_tag:
#ifdef TDF_DIAG3
	case diagnose_tag:
#endif
	case caller_tag:
		if (child(e) == NULL) { /* empty make_nof */
			return 0;
		}

		scanargs(1, e, 1);
		return 0;

	case labst_tag:
		IGNORE scan(0, child(e), next(child(e)), 1);
		return 0;

	case ident_tag:
		IGNORE scan(0, child(e), next(child(e)), 0);
		IGNORE scan(1, e, child(e), 0);
		return 0;

	case seq_tag:
		scanargs(1, child(e), 1);
		IGNORE scan(0, child(e), next(child(e)), 1);
		return 0;

	case local_free_tag:
	case long_jump_tag:
	case return_to_label_tag:
		all_assable(sto, to, e);
		return 0;

	case offset_add_tag:
	case offset_subtract_tag:
		if (al2(sh(child(e))) == 1 && al2(sh(next(child(e)))) != 1) {
			make_bitfield_offset(next(child(e)), child(e), 0, sh(e));
		}

		if (al2(sh(child(e))) != 1 && al2(sh(next(child(e)))) == 1) {
			make_bitfield_offset(child(e), e, 1, sh(e));
		}

		/* all arguments except possibly one must be operands */
		IGNORE all_opnd(sto, to, e, usereg0);
		return 0;

	case offset_mult_tag:
	case alloca_tag:
	case minus_tag:
	case neg_tag:
	case not_tag:
	case offset_pad_tag:
	case offset_negate_tag:
	case offset_max_tag:
	case int_to_bitf_tag:
	case testbit_tag:
	case bitf_to_int_tag:
	case max_tag:
	case min_tag:
	case abs_tag:
		/* all arguments except possibly one must be operands */
		IGNORE all_opnd(sto, to, e, usereg0);
		return 0;

	case subptr_tag:
	case minptr_tag:
	case make_stack_limit_tag:
		IGNORE all_opnd(sto, to, e, 0);
		return 0;

	case set_stack_limit_tag: {
		exp lim = find_stlim_var();
		setnext(lim, child(e));
		setchild(e, lim);
		e->tag = ass_tag;
		return scan(sto, to, e, usereg0);
	}

	case chvar_tag: {
		int ur = usereg0 && child(e)->tag != cont_tag;
		IGNORE all_opnd(sto, to, e, ur);
		return 0;
	}

	case test_tag:
	case absbool_tag:
		if ((sh(child(e))->tag >= shrealhd &&
		     sh(child(e))->tag <= doublehd)) {
			IGNORE all_opnd (sto, to, e, 0);    /* all arguments must be operands */
		} else {
			IGNORE all_opnd(sto, to, e, usereg0);
		}

		/* all arguments except possibly one must be operands */
		return 0;

	case mod_tag:
	case rem2_tag:
	case rem0_tag:
	case div1_tag:
	case div2_tag:
	case div0_tag:
		if (sh(e)->tag == u64hd) {
			exp * bottom = &next(child(e));
			if ((*bottom)->tag == chvar_tag && shape_size(sh(child(*bottom))) <= 32 &&
			    child(*bottom)->tag != val_tag && !is_signed(sh(child(*bottom)))) {
				if (shape_size(sh(child(*bottom))) == 32) {
					setnext(child(*bottom), next(*bottom));
					*bottom = child(*bottom);
				} else {
					setsh(child(*bottom), ulongsh);
				}
			}
		}

		/* all arguments except possibly the first must be operands */
		cc1(sto, to, 1, e, notopnd, 1, usereg0);
		return 0;

	case shl_tag:
	case shr_tag:
	case rotl_tag:
	case rotr_tag:
	case offset_div_tag:
		/* all arguments except possibly the first must be operands */
		cc1(sto, to, 1, e, notopnd, 1, usereg0);
		return 0;

	case offset_div_by_int_tag:
		if (sh(next(child(e)))->tag != slonghd &&  sh(next(child(e)))->tag != ulonghd) {
			exp ch = getexp((sh(next(child(e)))->tag & 1 ? slongsh : ulongsh),
			                e, 1, next(child(e)), NULL, 0, 0, chvar_tag);
			setnext(next(child(e)), ch);
			setnext(child(e), ch);
		}

		/* all arguments except possibly the first must be operands */
		cc1(sto, to, 1, e, notopnd, 1, usereg0);
		return 0;

	case fplus_tag:
	case fminus_tag:
	case fmult_tag:
	case fdiv_tag:
	case fneg_tag:
	case fabs_tag:
	case chfl_tag:
	case float_tag:
	case round_tag:
	case movecont_tag:
		IGNORE all_opnd (sto, to, e, 0);/* all arguments must be operands */
		return 0;

	case ass_tag:
	case assvol_tag: {
		exp toc;

		if (e->tag == assvol_tag) { /* change assvol to assign */
			e->tag = ass_tag;
		}

		IGNORE cont_arg(sto, to, e, 0);
		/* special check for references */
		if (!is_assable(next(child(e)))) {
			/* second argument must be assignable */
			cca(sto, to, 0, child(e));
			toc = contexp(sto, to);
			IGNORE scan(1, toc, child(toc), 1);
		} else {
			IGNORE scan(sto, to, next(child(e)), 1);
		}

		return 0;
	}

	case apply_tag:
		if (builtinproc(e)) {
			/* child must be named global */
			if (!child(e)->last) {
				IGNORE cc(sto, to, 0, child(e), notopnd, 1, 0);
			}

			return 0;
		}

		if (!child(e)->last) {
			scan_apply_args(sto, to, 0, child(e));
		}

		indable_child(sto, to, e);
		return 0;

	case apply_general_tag: {
		exp cees = next(next(child(e)));
		exp p_post = cees;	/* next(p_post) is postlude */

		while (next(p_post)->tag == ident_tag && child(next(p_post))->tag == caller_name_tag) {
			p_post = child(next(p_post));
		}

		scan(0, p_post, next(p_post), 1);
		if (child(cees) != NULL) {
			scan_apply_args(sto, to, 1, cees);
		}

		if (no(next(child(e))) != 0) {
			scan_apply_args(sto, to, 1, next(child(e)));
		}

		indable_child(sto, to, e);
		if ((cees->tag == make_dynamic_callee_tag && next(child(cees))->tag != val_tag)
		    || (cees->tag == same_callees_tag && callee_size < 0)) {
			has_dy_callees = true;
		}

		if (cees->tag == same_callees_tag) {
			has_same_callees = true;
		}

		if (cees->tag == make_dynamic_callee_tag || cees->tag == same_callees_tag) {
			cca_for_cees(sto, to, e);
		}

		return 0;
	}

	case tail_call_tag: {
		exp cees = next(child(e));
		has_tail_call = true;

		if (child(cees) != NULL) {
			IGNORE cc(sto, to, 1, cees, no_alloca, 1, 0);
		}

		indable_child(sto, to, e);
		if (cees->tag == make_dynamic_callee_tag && next(child(cees))->tag != val_tag) {
			has_dy_callees = true;
		}

		if (cees->tag == same_callees_tag) {
			has_same_callees = true;
		}

		if (cees->tag == make_dynamic_callee_tag) {
			cca_for_cees(sto, to, e);
		}

		return 0;
	}

	case goto_lv_tag:
		indable_child(sto, to, e);
		return 0;

	case res_tag:
	case untidy_return_tag:
		if ((sh(child(e))->tag == cpdhd) &&
		    (child(e)->tag != cont_tag ||
		     child(child(e))->tag != name_tag ||
		     !isvar(child(child(child(e)))))) { /* gcc compatibility */
			exp ec;
			cca(sto, to, 1, e);
			ec = contexp(sto, to);
			IGNORE scan(1, ec, child(ec), 0);
			return 0;
		} else  {
			IGNORE(scan(sto, to, child(e), 1));
			return 0;
		}

	case case_tag: {
		exp toc;

		if (child(e)->tag != name_tag &&
		    (child(e)->tag != cont_tag ||
		     child(child(e))->tag != name_tag)) {
			cca(sto, to, 1, e);
			toc = contexp(sto, to);
			IGNORE scan(1, toc, child(toc), 0);
		} else {
			IGNORE scan(sto, to, child(e), 0);
		}

		return 0;
	}

	case plus_tag:
		IGNORE cc(sto, to, 1, e, plusdo, 1, usereg0);
		return 0;

	case addptr_tag: {
		exp f = father(e);
		exp new_r = getexp(sh(e), next(e), (int)(e->last),
		                   e, NULL, 0, 0, reff_tag);
		exp * ref = refto(f, e);
		e->last = true;
		next(e) = new_r;
		*ref = new_r;
		ap_argsc(sto, to, new_r);
		return 0;
	}

	case mult_tag: {
		if (shape_size(sh(e)) == 64 && optop(e)) {
			exp * arglist = &child(e);
			for (;;) {
				if ((*arglist)->tag == chvar_tag && shape_size(sh(child(*arglist))) <= 32 &&
				    (is_signed(sh(e)) || !is_signed(sh(child(*arglist))))) {
					if (shape_size(sh(child(*arglist))) == 32) {
						setnext(child(*arglist), next(*arglist));
						if ((*arglist)->last) {
							child(*arglist)->last = true;
						} else {
							child(*arglist)->last = false;
						}
						*arglist = child(*arglist);
					} else {
						setsh(child(*arglist), (is_signed(sh(e)) ? slongsh : ulongsh));
					}
				}
				if ((*arglist)->last) {
					break;
				}
				arglist = &next(*arglist);
			}
		}

		IGNORE cc(sto, to, 1, e, multdo, 1, usereg0);
		return 0;
	}

	case and_tag:
		IGNORE cc(sto, to, 1, e, anddo, 1, usereg0);
		return 0;

	case or_tag:
	case xor_tag:
		IGNORE cc(sto, to, 1, e, notado, 1, usereg0);
		return 0;

	case cont_tag:
	case contvol_tag:
		if (e->tag == contvol_tag) {
			e->tag = cont_tag;
		}

		return cont_arg(sto, to, e, usereg0);

	case field_tag:
		if (!is_o(child(e)->tag) || e->tag == cont_tag) {
			exp temp;
			cca(sto, to, 1, e);
			temp = contexp(sto, to);
			return scan(1, temp, child(temp), usereg0);
		} else {
			return scan(sto, to, child(e), usereg0);
		}

	case reff_tag:
		if (child(e)->tag == addptr_tag) {
			ap_argsc(sto, to, e);
			return 0;
		}

		ccp(sto, to, 1, e);
		return 0;

	case proc_tag:
	case general_proc_tag:
		IGNORE scan(1, e, child(e), 1);
		return 0;

	case asm_tag:
		if (props(e) != 0) {
			error(ERR_INTERNAL, "~asm not in ~asm_sequence");
		}

		check_asm_seq(child(e), 0);
		proc_has_asm = true;

		return 0;

	case name_tag:
		if (!is_opnd(e)) {
			return 0;
		}

		FALL_THROUGH;

	default:
		return usereg0;
	}
}

