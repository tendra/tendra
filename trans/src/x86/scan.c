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
 * referred to is the son of the given exp, and false if it is the brother.
 *
 * This is to allow exps to be represented by indices into arrays and to
 * allow the arrays to be realloced, which invalidates the use of
 * &son(to) and &next(to).
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

#define assexp(isson, p, v) if (isson)setson(p, v); else setbro(p, v)
#define contexp(isson, p)((isson)? son(p): next(p))

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
		dgf(id) = dgf(next(son(id)));
		dgf(next(son(id))) = NULL;
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
			return scan(1, ec, son(ec), unused);
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
			return scan(1, ec, son(ec), unused);
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
			IGNORE scan(1, ec, son(ec), unused);
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
			IGNORE scan(1, ec, son(ec), unused);
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
	IGNORE scan(1, toc, son(toc), 0);
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
		if (isvar(son(e))) {
			return isglob(son(e)) && !PIC_code;
		}

		return son(son(e)) != NULL &&
		       (!isglob(son(e)) || !PIC_code || sh(son(e))->tag != prokhd ||
		        (brog(son(e)) -> extnamed)) &&
		       (son(son(e))->tag != ident_tag || !isparam(son(son(e))));
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

	if (son(e)->tag == reff_tag) {
		q = son(son(e));
	} else {
		q = son (e);    /* q must be addptr - all addptrs processed here */
	}

	if ((frame_al_of_ptr(sh(son(q))) & al_includes_vcallees) &&
	    (frame_al1_of_offset(sh(next(son(q)))) & al_includes_caller_args)) {
		/* env_offset to arg requires indirection from frame pointer */
		shape pc_sh = f_pointer(f_callers_alignment(0));
		exp c = getexp(pc_sh, next(son(q)), 0, NULL, NULL, 0, 0, cont_tag);
		exp r = getexp(pc_sh, c, 1, son(q), NULL, 0, 64, reff_tag);
		setfather(r, son(q));
		son(c) = r;
		son(q) = c;
	}

	p = son(q);
	a = next(p);

	if (p->tag == name_tag && isvar(son(p)) && isglob(son(p))) {
		do1 = 0;
	}

	if (do1) {
		ccp(1, e, 1, q);
	}

	if (a->tag == offset_mult_tag && next(son(a))->tag == val_tag &&
	    (k = no(next(son(a))), k == 8 || k == 16 || k == 32 || k == 64)) {
		ccp(1, e, 1, next(son(q)));
	} else {
		ccp(1, e, 0, son(q));
	}

	if (do1) {
		cca(sto, to, 1, son(e));
		cca(sto, to, 1, next(son(son(e))));
	} else {
		cca(sto, to, 1, son(e));
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
	unsigned char  n = son(e)->tag;

	if (n == name_tag && isvar(son(son(e)))) {
		return usereg0;
	}

	if (n == cont_tag && usereg0 && shape_size(sh(e)) <= 32) {
		cont_arg(sto, to, son(e), 1);
		return 0;
	}

	if (n == reff_tag) {
		exp s = son(son(e));
		if (s->tag == name_tag) {
			if (isusereg(son(s))) {
				return 0;
			}
			if (!PIC_code && isglob(son(s)) && isvar(son(s))) {
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
		ccp(1, e, 1, son(e));
	} else {
		ccp(1, e, 1, e);
	}

	cca(sto, to, 1, son(e));

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
		return scan_for_alloca(son(t));

	case labst_tag:
		return scan_for_alloca(next(son(t)));

	case env_offset_tag:
	case string_tag:
	case name_tag:
		return 0;

	case apply_general_tag:
		if call_is_untidy(t) {
			return 1;
		}

		return scan_alloc_args(son(t));

	default:
		if (son(t) == NULL) {
			return 0;
		}

		return scan_alloc_args(son(t));
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

	return (s == name_tag && !isglob(son(e)) && !isvar(son(e))) ||
	       (s == cont_tag && son(e)->tag == name_tag &&
	        !isglob(son(son(e))) && isvar(son(son(e))));
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
		unsigned char  t = son(e)->tag;
		return (t == name_tag && isvar(son(son(e)))) ||
		       (t == cont_tag && son(son(e))->tag == name_tag &&
		        isvar(son(son(son(e))))) ||
		       (t == reff_tag && is_direct(son(son(e))));
	}

	return (s == reff_tag && is_direct(son(e))) ||
	       s == addptr_tag;
}

/* son must be indirectly addressable */
static void
indable_son(int sto, exp to, exp e)
{
	if (!is_indable(son(e))) {
		exp ec;
		cca(sto, to, 1, e);
		ec = contexp(sto, to);
		IGNORE scan(1, ec, son(ec), 0);
	} else {
		IGNORE scan(sto, to, son(e), 0);
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
	setbro(e, val8);
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
	if (son(e)->tag == name_tag) {
		if (!isglob(son(son(e)))) {
			set_intnl_call(son(son(e)));
		}

		return;
	}

	if (son(e)->tag == cont_tag && son(son(e))->tag == name_tag) {
		if (!isglob(son(son(son(e))))) {
			set_intnl_call(son(son(son(e))));
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
		setvis(son(e));
		return 1;
	}

	if (n == cont_tag && son(e)->tag == name_tag && isvar(son(son(e)))) {
		setvis(son(son(e)));
		return 1;
	}

	return n == val_tag || n == real_tag || n == null_tag ||
	       (n == reff_tag && son(e)->tag == name_tag);
}

static int
is_asm_var(exp e, int ext)
{
	unsigned char n = e->tag;

	UNUSED(ext);

	if (n == name_tag && isvar(son(e))) {
		setvis(son(e));
		return 1;
	}

	return 0;
}

void
check_asm_seq(exp e, int ext)
{
	if (e->tag == asm_tag) {
		if ((asm_string(e) && son(e)->tag == string_tag) ||
		    (asm_in(e) && is_asm_opnd(son(e), ext)) ||
		    (asm_var(e) && is_asm_var(son(e), ext))) {
			return;
		}
	}

	if (e->tag == seq_tag) {
		exp t;

		for (t = son(son(e)); ; t = next(t)) {
			check_asm_seq(t, ext);
			if (t->last) {
				break;
			}
		}

		check_asm_seq(next(son(e)), ext);
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
		if (son(e) == NULL) { /* empty make_nof */
			return 0;
		}

		scanargs(1, e, 1);
		return 0;

	case labst_tag:
		IGNORE scan(0, son(e), next(son(e)), 1);
		return 0;

	case ident_tag:
		IGNORE scan(0, son(e), next(son(e)), 0);
		IGNORE scan(1, e, son(e), 0);
		return 0;

	case seq_tag:
		scanargs(1, son(e), 1);
		IGNORE scan(0, son(e), next(son(e)), 1);
		return 0;

	case local_free_tag:
	case long_jump_tag:
	case return_to_label_tag:
		all_assable(sto, to, e);
		return 0;

	case offset_add_tag:
	case offset_subtract_tag:
		if (al2(sh(son(e))) == 1 && al2(sh(next(son(e)))) != 1) {
			make_bitfield_offset(next(son(e)), son(e), 0, sh(e));
		}

		if (al2(sh(son(e))) != 1 && al2(sh(next(son(e)))) == 1) {
			make_bitfield_offset(son(e), e, 1, sh(e));
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
		setbro(lim, son(e));
		setson(e, lim);
		e->tag = ass_tag;
		return scan(sto, to, e, usereg0);
	}

	case chvar_tag: {
		int ur = usereg0 && son(e)->tag != cont_tag;
		IGNORE all_opnd(sto, to, e, ur);
		return 0;
	}

	case test_tag:
	case absbool_tag:
		if ((sh(son(e))->tag >= shrealhd &&
		     sh(son(e))->tag <= doublehd)) {
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
			exp * bottom = &next(son(e));
			if ((*bottom)->tag == chvar_tag && shape_size(sh(son(*bottom))) <= 32 &&
			    son(*bottom)->tag != val_tag && !is_signed(sh(son(*bottom)))) {
				if (shape_size(sh(son(*bottom))) == 32) {
					setbro(son(*bottom), next(*bottom));
					*bottom = son(*bottom);
				} else {
					setsh(son(*bottom), ulongsh);
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
		if (sh(next(son(e)))->tag != slonghd &&  sh(next(son(e)))->tag != ulonghd) {
			exp ch = getexp((sh(next(son(e)))->tag & 1 ? slongsh : ulongsh),
			                e, 1, next(son(e)), NULL, 0, 0, chvar_tag);
			setbro(next(son(e)), ch);
			setbro(son(e), ch);
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
		if (!is_assable(next(son(e)))) {
			/* second argument must be assignable */
			cca(sto, to, 0, son(e));
			toc = contexp(sto, to);
			IGNORE scan(1, toc, son(toc), 1);
		} else {
			IGNORE scan(sto, to, next(son(e)), 1);
		}

		return 0;
	}

	case apply_tag:
		if (builtinproc(e)) {
			/* son must be named global */
			if (!son(e)->last) {
				IGNORE cc(sto, to, 0, son(e), notopnd, 1, 0);
			}

			return 0;
		}

		if (!son(e)->last) {
			scan_apply_args(sto, to, 0, son(e));
		}

		indable_son(sto, to, e);
		return 0;

	case apply_general_tag: {
		exp cees = next(next(son(e)));
		exp p_post = cees;	/* next(p_post) is postlude */

		while (next(p_post)->tag == ident_tag && son(next(p_post))->tag == caller_name_tag) {
			p_post = son(next(p_post));
		}

		scan(0, p_post, next(p_post), 1);
		if (son(cees) != NULL) {
			scan_apply_args(sto, to, 1, cees);
		}

		if (no(next(son(e))) != 0) {
			scan_apply_args(sto, to, 1, next(son(e)));
		}

		indable_son(sto, to, e);
		if ((cees->tag == make_dynamic_callee_tag && next(son(cees))->tag != val_tag)
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
		exp cees = next(son(e));
		has_tail_call = true;

		if (son(cees) != NULL) {
			IGNORE cc(sto, to, 1, cees, no_alloca, 1, 0);
		}

		indable_son(sto, to, e);
		if (cees->tag == make_dynamic_callee_tag && next(son(cees))->tag != val_tag) {
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
		indable_son(sto, to, e);
		return 0;

	case res_tag:
	case untidy_return_tag:
		if ((sh(son(e))->tag == cpdhd) &&
		    (son(e)->tag != cont_tag ||
		     son(son(e))->tag != name_tag ||
		     !isvar(son(son(son(e)))))) { /* gcc compatibility */
			exp ec;
			cca(sto, to, 1, e);
			ec = contexp(sto, to);
			IGNORE scan(1, ec, son(ec), 0);
			return 0;
		} else  {
			IGNORE(scan(sto, to, son(e), 1));
			return 0;
		}

	case case_tag: {
		exp toc;

		if (son(e)->tag != name_tag &&
		    (son(e)->tag != cont_tag ||
		     son(son(e))->tag != name_tag)) {
			cca(sto, to, 1, e);
			toc = contexp(sto, to);
			IGNORE scan(1, toc, son(toc), 0);
		} else {
			IGNORE scan(sto, to, son(e), 0);
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
			exp * arglist = &son(e);
			for (;;) {
				if ((*arglist)->tag == chvar_tag && shape_size(sh(son(*arglist))) <= 32 &&
				    (is_signed(sh(e)) || !is_signed(sh(son(*arglist))))) {
					if (shape_size(sh(son(*arglist))) == 32) {
						setbro(son(*arglist), next(*arglist));
						if ((*arglist)->last) {
							son(*arglist)->last = true;
						} else {
							son(*arglist)->last = false;
						}
						*arglist = son(*arglist);
					} else {
						setsh(son(*arglist), (is_signed(sh(e)) ? slongsh : ulongsh));
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
		if (!is_o(son(e)->tag) || e->tag == cont_tag) {
			exp temp;
			cca(sto, to, 1, e);
			temp = contexp(sto, to);
			return scan(1, temp, son(temp), usereg0);
		} else {
			return scan(sto, to, son(e), usereg0);
		}

	case reff_tag:
		if (son(e)->tag == addptr_tag) {
			ap_argsc(sto, to, e);
			return 0;
		}

		ccp(sto, to, 1, e);
		return 0;

	case proc_tag:
	case general_proc_tag:
		IGNORE scan(1, e, son(e), 1);
		return 0;

	case asm_tag:
		if (props(e) != 0) {
			error(ERR_INTERNAL, "~asm not in ~asm_sequence");
		}

		check_asm_seq(son(e), 0);
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

