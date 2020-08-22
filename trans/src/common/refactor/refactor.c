/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The routine refactor performs the bottom-up TDF-to-TDF optimising
 * transformations. When a new exp is created refactor is applied to see
 * if a recognised situation has arisen. refactor assumes that all components
 * of this new exp have already had refactor applied to them.
 * It returns 1 if it has made a change, 0 if not.
 *
 * hold_refactor holds an exp as the child of a dummy exp and then
 * applies refactor. The need for this operation is explained in the
 * overall documentation.
 *
 * eq_exp compares two exp for equality of effect.
 *
 * dochvar takes the int, i, and delivers the number which results from
 * changing its variety to that specified by the shape, t.
 */

#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <local/al.h>

#include <reader/exp.h>
#include <reader/externs.h>
#include <reader/basicread.h>
#include <reader/readglob.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>

#include <flpt/flpt.h>

#include <utility/max.h>

#include <main/flags.h>

#include <refactor/refactor_id.h>
#include <refactor/refactor.h>
#include <refactor/misc_c.h>
#include <refactor/query.h>

#ifdef TDF_DIAG4
#include <diag4/dg_aux.h>
#endif

#if defined(TRANS_X86) || defined(TRANS_HPPA)
#include <local/exp.h>
#endif

#include <refactor/refactor.h>

#include <utility/bits.h>

extern shape containedshape(int, int);

/* codes for error treaments */
#define impossible 1
#define ignore 2

ntest int_inverse_ntest[]  = { 0,  4, 3, 2, 1, 6, 5 };
ntest real_inverse_ntest[] = { 0, 10, 9, 8, 7, 6, 5, 4,  3, 2, 1, 12, 11, 14, 13 };
ntest exchange_ntest[]     = { 0,  3, 4, 1, 2, 5, 6, 9, 10, 7, 8, 11, 12, 13, 14 };

/*
 * hold_refactor holds an exp as the child of a dummy exp and then
 * applies refactor. After refactoring it retcells the dummy exp.
 *
 * puts body on a hold
 */
exp
hold(exp body)
{
	exp body_hold = next_exp();

	child(body_hold) = body;
	next(body) = body_hold;
	body->last = true;
	next(body_hold) = NULL;

	body_hold->tag = diagnose_registers ? hold_tag : 102;

	return body_hold;
}

exp
hold_refactor(exp r)
{
	exp h, sn;

	h = hold(r);
	IGNORE refactor(r, r);
	sn = child(h);
	next(sn) = NULL;
	retcell(h);

	return sn;
}

exp
hold_const_refactor(exp r)
{
	exp ans;

	bool old = all_variables_visible;
	all_variables_visible = 0;
	ans = hold_refactor(r);
	all_variables_visible = old;

	return ans;
}

/*
 * applies a change_var operation to e, to get shape s
 */
static
exp varchange(shape s, exp e)
{
	exp r;

	r = getexp(s, NULL, 0, e, NULL, 0, 0, chvar_tag);
	e->last = true;
	next(e) = r;

	return hold_refactor(r);
}

static int
flpt_power_of_2(flpt f)
{
	flt *r = &flptnos[f];
	unsigned short us = r->mant[0];
	int i;

	if ((us & (us - 1)) != 0) {
		return 0;
	}

	for (i = 1; i < MANT_SIZE; i++) {
		if (r->mant[i] != 0) {
			return 0;
		}
	}

	return 1;
}

/*
 * eq_explist compares two descendant lists of exp for equality.
 *
 * The given values, their next's, next(next)'s etc are compared until an
 * unequal pair is found or the end of one of the lists (last) is found.
 * In this case the lists are equal iff both ends have been reached.
 */
static int
eq_explist(exp al, exp bl)
{
	if (al == NULL && bl == NULL) {
		return 1;
	}

	if (al == NULL || bl == NULL) {
		return 0;
	}

	if (!eq_exp(al, bl)) {
		return 0;
	}

	if (al->last && bl->last) {
		return 1;
	}

	if (al->last || bl->last) {
		return 0;
	}

	return eq_explist(next(al), next(bl));
}

/*
 * eq_exp compares two exp for equality of effect. If the name of either
 * exp is in the side-effecting group (!is_a) the exp are not equal.
 *
 * This is a crude test, but if it says the exps are equal this is so.
 * contvol is forbidden.
 */
int
eq_exp(exp a, exp b)
{
	if (a->tag != b->tag) {
		return 0;
	}

	if (a->tag == name_tag) {
		return child(a) == child(b) && no(a) == no(b) &&
			   eq_shape(sh(a), sh(b));
	}

	if (!is_a(a->tag) || !eq_shape(sh(a), sh(b)) ||
		a->tag == contvol_tag) {
		return 0;
	}

	if (a->tag == real_tag) {
		int res = flt_cmp(flptnos[no(a)], flptnos[no(b)]);

		return res == 0;
	}

	if (a->tag == val_tag) {
		if (isbigval(a) != isbigval(b)) {
			return 0;
		}

		if (isbigval(a)) {
			int res = flt_cmp(flptnos[no(a)], flptnos[no(b)]);

			return res == 0;
		}

		if (isbigval(b)) {
			return 0;
		}

		return no(a) == no(b);
	}

	return no(a) == no(b) && eq_explist(child(a), child(b));
}

/*
 * repbycont replaces e by the exp which loads top, ie. does nothing.
 */
static void
repbycont(exp e, bool has_label, exp scope)
{
	exp n = getexp(f_top, next(e), (int) (e->last), NULL, NULL, 0, 0, top_tag);

	if (has_label) {
		no(child(pt(e)))--;
		pt(e) = NULL;
	}

#ifdef TDF_DIAG4
	dgf(n) = dgf(e);
#endif
	replace(e, n, e);
	kill_exp(e, e);

	if (scope != e) {
		altered(n, scope);
	}
}

/*
 * repbygo replaces e by a goto the label.
 */
static void
repbygo(exp e, exp lab, exp scope)
{
	exp g = getexp(f_bottom, NULL, 0, NULL, lab, 0, 0, goto_tag);
	exp n = getexp(f_top, g, 1, NULL, NULL, 0, 0, top_tag);

	child(g) = n;
	++no(child(lab));
#ifdef TDF_DIAG4
	dgf(g) = dgf(e);
#endif
	replace(e, g, e);
	kill_exp(e, e);

	if (scope != e) {
		altered(g, scope);
	}
}

/*
 * nos tests the exp t to see if it is a construction that can be
 * eliminated from a sequence. It is ignorable or has no side effect.
 */
static int nos(exp t);

static int
noslist(exp tl)
{
	if (tl == NULL) {
		return 1;
	}

	if (tl->last) {
		return nos(tl);
	}

	return nos(tl) && noslist(next(tl));
}

static int
nos(exp t)
{
	unsigned char n = t->tag;

	if (n == top_tag || n == ignorable_tag) {
		return 1;
	}

	if (n == compound_tag || n == nof_tag) {
		return noslist(child(t));
	}

	return((is_a(n) && optop(t) &&
	        ((n == name_tag && !islastuse(t)) || n == val_tag ||
	         noslist(child(t)))) || (n == ident_tag && !isenvoff(t) &&
	                               nos(child(t)) && nos(next(child(t)))));
}

static int maxes[] = {
	0, 0, 0, 127, 255, 32767, 65535, (int) 0x7fffffff, (int) 0xffffffff
};

static int mins[] = {
	0, 0, 0, -128, 0, -32768, 0, (int) 0xffffffff, 0
};

static shape *us_shape[] = {
	&f_bottom,
	&f_bottom,
	&f_top,
	&ucharsh,
	&ucharsh,
	&uwordsh,
	&uwordsh,
	&ulongsh,
	&ulongsh
};

static exp
make_test(ntest nt, exp lab, exp arg1, exp arg2, unsigned char nm)
{
	exp r;

	r = getexp(f_top, NULL, 0, arg1, lab, 0, 0, nm);
	fno(r) = (float)0.5;
	settest_number(r, (int)nt);
	setnext(arg1, arg2);
	arg1->last = false;
	++no(child(lab));
	setfather(r, arg2);

	return r;
}


static int
simple(exp e)
{
	if (e->tag == cont_tag && child(e)->tag == name_tag) {
		return 1;
	}

	if (e->tag == cont_tag && child(e)->tag == cont_tag &&
	    child(child(e))->tag == name_tag) {
		return 1;
	}

	if (e->tag == cont_tag && child(e)->tag == reff_tag &&
	    child(child(e))->tag == cont_tag &&
	    child(child(child(e)))->tag == name_tag) {
		return 1;
	}

	if (e->tag == name_tag && !isvar(child(e))) {
		return 1;
	}

	return 0;
}

static exp
tests_to_bounds(exp a, exp b)
{
	exp x = child(a);
	int na = no(next(x));
	int nb = no(next(child(b)));
	int ntemp;
	ntest nta = test_number(a);
	ntest ntb = test_number(b);
	ntest nttemp;
	exp lab = pt(a);
	shape sha = sh(x);

	if (simple(x)) {
		return NULL;
	}

	if (nta == f_greater_than) {
		if (na == maxes[sha->tag]) {
			return NULL;
		}

		nta = f_greater_than_or_equal;
		++na;
	}

	if (ntb == f_greater_than) {
		if (nb == maxes[sha->tag]) {
			return NULL;
		}

		ntb = f_greater_than_or_equal;
		++nb;
	}

	if (ntb == f_greater_than_or_equal) {
		ntemp = na;
		na = nb;
		nb = ntemp;
		nttemp = nta;
		nta = ntb;
		ntb = nttemp;
	}

	if (nta != f_greater_than_or_equal) {
		return NULL;
	}

	if (ntb != f_less_than_or_equal && ntb != f_less_than) {
		return NULL;
	}

	if (ntb == f_less_than) {
		if (nb == mins[sha->tag]) {
			return NULL;
		}

		ntb = f_less_than_or_equal;
		--nb;
	}

	UNUSED(ntb);

	if (is_signed(sha)) {
		if (nb < na) {
			return NULL;
		}
	} else {
		if ((unsigned int)nb < (unsigned int)na) {
			return NULL;
		}
	}

	no(child(lab)) -= 1; /* one is removed by kill_exp below */
	if (na == nb) {
		kill_exp(b, b);
		return make_test(f_equal, lab, x, me_shint(sha, na), test_tag);
	}

	{
		exp s = hold_refactor(me_b2(x, me_shint(sha, na), minus_tag));
		exp n = me_shint(sha, nb - na);
		shape new_sha = *us_shape[sha->tag];
		sh(s) = new_sha;
		sh(n) = new_sha;
		kill_exp(b, b);

		return make_test(f_less_than_or_equal, lab, s, n, test_tag);
	}
}

/*
 * refactor_seq carries out transformations on sequences.
 * Statements with no effect are removed.
 *
 * Anything after an unconditional goto, or any other statement
 * producing a bottom shape, is removed.
 *
 * No changes are propagated outside the exp "scope".
 */
static int
refactor_seq(exp e, exp scope)
{
	exp z = child(e);
	exp t, k, kk;
	int changed = 0;

	if (sh(next(child(e)))->tag == bothd && sh(e)->tag != bothd) {
		sh(e) = f_bottom;
		changed = 1;
	}

	while (sh(child(z))->tag == bothd || nos(child(z))) {
		if (sh(child(z))->tag == bothd) {
			if (!child(z)->last) {
				kk = next(child(z));
				while (kk != NULL) {
					k = kk;
					if (!k->last) {
						kk = next(k);
					} else {
						kk = NULL;
					}
#ifdef TDF_DIAG4
					dg_dead_code(k, child(z));
#endif
					kill_exp(k, k);
				}
			}

#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_dead_code(next(z), child(z));
				dg_whole_comp(e, child(z));
			}
#endif

			/* kill dead variable refs */
			kill_exp(next(z), next(z));

			/* before replace */
			setfather(e, z);
			replace(e, child(z), scope);
			retcell(z);
			retcell(e);

			return 1;
		}

		if (child(z)->last) {
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_rdnd_code(child(z), next(z));
				dg_whole_comp(e, next(z));
			}
#endif
			replace(e, next(z), scope);
			kill_exp(child(z), child(z));
			retcell(z);
			retcell(e);

			return 1;
		}

#ifdef TDF_DIAG4
		if (diag != DIAG_NONE) {
			dg_rdnd_code(child(z), next(child(z)));
		}
#endif

		k = child(z);
		child(z) = next(child(z));
		kill_exp(k, k);
	}

	t = child(z);
	for (;;) {
		if (t->tag == test_tag && next(child(t))->tag == val_tag &&
		    !isbigval(next(child(t))) && sh(child(t))->tag <= ulonghd) {
			exp b;
			exp bnds;
			exp *ref;

			if (t->last) {
				b = next(next(t));
				if (b->tag == test_tag &&
				    next(child(b))->tag == val_tag &&
				    !isbigval(next(child(b))) && pt(t) == pt(b) &&
				    eq_exp(child(t), child(b)))
				{
					bnds = tests_to_bounds(t, b);
					if (bnds == NULL) {
						if (changed) {
							altered(e, scope);
						}
						return 0;
					}

					if (t == child(z)) {
#ifdef TDF_DIAG4
						if (diag != DIAG_NONE) {
							dg_whole_comp(e, bnds);
						}
#endif
						replace(e, bnds, scope);
						retcell(e);
						return 1;
					}

					ref = refto(father(t), t);
					next(*ref) = next(t);
					(*ref)->last = true;
					bnds->last = true;
					next(bnds) = e;
					next(z) = bnds;
					return 0;
				} else {
					if (changed) {
						altered(e, scope);
					}

					return 0;
				}
			}

			b = next(t);
			if (b->tag == test_tag &&
			    next(child(b))->tag == val_tag &&
			    !isbigval(next(child(b))) && pt(t) == pt(b) &&
			    eq_exp(child(t), child(b)))
			{
				exp nextb = next(b);
				int lb = b->last;
				ref = refto(father(t), t);

				bnds = tests_to_bounds(t, b);
				if (bnds != NULL) {
					next(bnds) = nextb;
					if (lb) {
						bnds->last = true;
					} else {
						bnds->last = false;
					}

					*ref = bnds;
					t = bnds;
				}
			}
		}

		if (t->last) {
			if (changed) {
				altered(e, scope);
			}

			return 0;
		}

		if (sh(next(t))->tag == bothd) {
			if (!next(t)->last) {
				kk = next(next(t));
				while (kk != NULL) {
					k = kk;
					if (!k->last) {
						kk = next(k);
					} else {
						kk = NULL;
					}

#ifdef TDF_DIAG4
					if (diag != DIAG_NONE) {
						dg_dead_code(k, next(t));
					}
#endif

					kill_exp(k, k);
				}
			}

#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_dead_code(next(z), next(t));
			}
#endif

			kill_exp(next(z), next(z));
			next(z) = next(t);
			next(z)->last = true;
			next(next(z)) = e;
			t->last = true;
			next(t) = z;
			sh(e) = f_bottom;
			altered(e, scope);

			return 0;
		}

		if (nos(next(t))) {
			if (next(t)->last) {
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_rdnd_code(next(t), next(z));
				}
#endif

				kill_exp(next(t), next(t));
				t->last = true;
				next(t) = z;

				return 0;
			}

			k = next(t);
			next(t) = next(next(t));

#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_rdnd_code(k, next(t));
			}
#endif

			kill_exp(k, k);
			changed = 1;
		} else {
			t = next(t);
		}
	}

	UNREACHED;
}


/*
 * comm_ass applies the commutative and associative laws to replace e
 * by an improved version. op_tag is the operation involved.
 * If the errtreat is not ignore or impossible, no change is made.
 * C programs will always use ignore or impossible.
 *
 * All the arguments of sub-operations with the same op_tag (they will
 * anyway have the same shape) are flattened into one argument list,
 * provided that dive is 1.
 *
 * All the constants are combined into one, which is placed as the last
 * constant. The parameter "one" is the unit for the given operation
 * (0 for + , 1 for * , allones for and, 0 for or, 0 for xor) and this
 * constant is eliminated. If the operation has a zero, "has_zero" is
 * set and "zero" is the constant (0 for * , 0 for and, allones for or).
 *
 * No changes are propagated outside the exp "scope".
 *
 * If isreal is 1 the operation has real arguments and results, otherwise
 * integer.
 *
 * fn(a, b) is applicable to exps defining constants of the correct type
 * (integer or real) and delivers an exp defining a constant which is
 * the result of the op_tag applied to these constants.
 */
static int f_one(flpt f);
static int seq_distr(exp e, exp scope);

static int
comm_ass(exp e, unsigned char op_tag, void (*fn)(exp, exp, int), int one,
         int has_zero, int zero, exp scope, int dive, int isreal)
{
	exp t = child(e);	/* starting element */
	int changed = t->last;
	exp cst;		/* start the accumulated constant */
	exp cst_u = NULL;	/* holds exp representing one if created here */
	int looping;

	if (isreal) {
		cst = getexp(sh(e), NULL, 0, NULL, NULL, 0, one,
		             real_tag);
	} else {
		cst = me_shint(sh(e), one);
		if (one == -1 && shape_size(sh(e)) == 64) {
			flpt f = new_flpt();
			flt *fp = &flptnos[f];
			int i;
			fp->sign = 1;
			fp->exp = 3;
			for (i = 0; i < 4; ++i) {
				fp->mant[i] = 65535;
			}
			no(cst) = f;
			setbigval(cst);
			cst_u = cst;
		}
	}

	if (!optop(e)) {
		return 0;
	}
	do {
		/* look to see if a change will be made */
		if ((t->tag == op_tag && optop(t)) || t->tag == val_tag ||
		    t->tag == real_tag) {
			changed = 1;
		}
		looping = !t->last;
		t = next(t);
	} while (looping);

	if (changed) {
		/* continue if there will be a change */
		exp p, q;
		t = child(e);	/* start */
		q = getexp(sh(e), NULL, 0, NULL, NULL, 0, 0, op_tag);

		seterrhandle(q, errhandle(e));
		/* start the result */

		/* p is used to point to the current place where the next item
		 * will be added (as next). */
		p = q;
		do {
			while (t->tag == op_tag && optop(t) && dive) {
				t = child(t);	/* dive down same operator */
			}
			if (t->tag == val_tag || t->tag == real_tag) {
				/* accumulate constant value */
				fn (cst, t, errhandle(e));
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_detach_const(t, cst);
				}
#endif
			} else {
				/* add item at p and move p on */
				next(p) = t;
				p->last = false;
				p = next(p);
			}
			while (t->last && next(t) != e) {
				/* ascend from sub-item */
				t = next(t);
			}
		} while ((t->last) ? 0 : (t = next(t), 1));

		/* put q into correct form (we were using its next) */
		child(q) = next(q);

		if (p == q) {
			/* no items but constant */
			retcell(q);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, cst);
			}
#endif
			replace(e, cst, scope);
			retcell(e);
			return 1;
		}

		if (has_zero &&
		    ((!isreal && no(cst) == zero && !isbigval(cst)) ||
		     (isreal && flptnos[no(cst)].sign == 0))) {
			/*
			 * Zero constant. Replace by a sequence of expressions
			 * delivering the zero, so as to keep side effects.
			 */
			exp r;
			q->tag = 0;		/* use q a seq holder */
			child(q) = next(q);
			next(p) = q;
			p->last = true;
			q->last = false;
			next(q) = cst;
			r = getexp(sh(e), NULL, 0, q, NULL, 0, 0, seq_tag);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dgf(r) = dgf(e);
			}
#endif
			replace(e, hc(r, cst), scope);
			return 1;
		}

		if ((!isreal &&
		     (no(cst) != one || (isbigval(cst) && cst != cst_u))) ||
		    (isreal && cmpflpt(no(cst), one, 6))) {
			/* form result if there is a non-unit constant term */
			next(p) = cst;
			p->last = false;
			p = next(p);
			child(q) = next(q);
			next(p) = q;
			p->last = true;
			sh(q) = sh(e);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dgf(q) = dgf(e);
			}
#endif
			replace(e, q, scope);
			retcell(e);
			return 1;
		}

#ifdef TDF_DIAG4
		if (diag != DIAG_NONE) {
			dgf(e) = combine_diaginfo(dgf(e), dgf(cst));
		}
#endif
		retcell(cst);   /* there are no constants other than unit*/

		if (child(q) == p) {
			/* form result if single item and no constant */
			sh(p) = sh(e);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, p);
			}
#endif
			replace(e, hold_refactor(p), scope);
			retcell(e);
			return 1;
		}

		/* form result if no constant and more than one arg */
		next(p) = q;

		p->last = true;
		sh(q) = sh(e);
#ifdef TDF_DIAG4
		if (diag != DIAG_NONE) {
			dg_whole_comp(e, q);
		}
#endif
		replace(e, q, scope);
		retcell(e);

		return 1;
	}

	return 0;	/* return from here if no change made */
}

/*
 * dochvar takes the int, i, and delivers the number which results
 * from changing its variety to that specified by the shape, t.
 */
int
dochvar(int i, shape t)
{
	if (t->tag == bitfhd) {
		int m = lsb_mask[shape_size(t)];
		int x = i & m;

		if (is_signed(t)) {
			int sm = ((m + 1) >> 1) & x;
			x -= (sm << 1);
		}

		return x;
	}

	switch (shape_size(t)) {
	case 8:
		if (is_signed(t)) {
			int x = i & 0xff;
			if (x & 128) {
				return i | (~0xff);
			}
		}

		return i & 0xff;

	case 16:
		if (is_signed(t)) {
			int x = i & 0xffff;
			if (x & 32768) {
				return i | (~0xffff);
			}
		}

		return i & 0xffff;

	case 32:
		if (is_signed(t)) {
			int x = i & (int) 0xffffffff;
			if (x & (int) 0x80000000) {
				return i | (~ (int) 0xffffffff);
			}
		}

		return i & (int) 0xffffffff;

	case 64:
		return i;

	default:
		return i & lsb_mask[shape_size(t)];
	}
}

static void
dochvar_f(flt64 *xa, shape sha)
{
	if (shape_size(sha) == 64) {
		return;
	}

	*xa = int_to_f64(dochvar((int)xa->small, sha), is_signed(sha));
}

static void
bigres(exp a, flt64 *xp)
{
	int bg;

	dochvar_f(xp, sh(a));
	no(a) = f64_to_flpt(*xp, is_signed(sh(a)), &bg, shape_size(sh(a)));

	if (bg) {
		setbigval(a);
	} else {
		clearbigval(a);
	}
}


static int
check_size(flt64 a, int sg, int sz)
{
	int t = (int) a.small;

	if (sz > 32) {
		return 0;
	}

	if (sg && (t >> 31) == a.big &&
	    (sz == 32 || (t >> (sz - 1)) == a.big)) {
		return 0;
	}

	if (!sg && a.big == 0 && (sz == 32 || (t >> sz) == 0)) {
		return 0;
	}

	return 1;
}

/*
 * Used as a fn parameter for comm_ass q.v.
 */
static void
fplus_fn(exp ap, exp b, int et)
{
	int a = no(ap);
	int nob = no(b);
	flt resval;
	int status;

	UNUSED(et);

	status = flt_add(flptnos[a], flptnos[nob], &resval);
	if (status != OKAY) {
		error(ERR_INTERNAL, "illegal floating add constants");
	}

	flpt_round((int)f_to_nearest,
	           flpt_bits((floating_variety)(sh(b)->tag -
	                                        shrealhd)), &resval);
	flptnos[nob] = resval;
	no(ap) = nob;
}

/*
 * Used as a fn parameter for comm_ass q.v.
 */
static void
fmult_fn(exp ap, exp b, int et)
{
	int a = no(ap);
	int nob = no(b);
	flt resval;
	int status;

	UNUSED(et);

	status = flt_mul(flptnos[a], flptnos[nob], &resval);
	if (status != OKAY) {
		error(ERR_INTERNAL, "illegal floating mult constants");
	}

	flpt_round((int)f_to_nearest,
	           flpt_bits((floating_variety)(sh(b)->tag -
	                                        shrealhd)), &resval);
	flptnos[nob] = resval;
	no(ap) = nob;
}

/* Auxiliary function used for comm_ass by plus. */
static void
plus_fn(exp ap, exp b, int et)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);

	IGNORE flt_add(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */

	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	if (et != f_wrap.err_code &&
	    (ov || constovf(b) || check_size(x, sg, shape_size(sh(ap))))) {
		setconstovf(ap);
	}

	/*
	if (check & CHECK_EXTRA) {
		 if (sg && !in_proc_def &&
		    (ov || (shape_size(sh(ap)) <= 32 && check_size(x, sg, 32)))) {
		    error(ERR_INTERNAL, "constant addition out of bounds, consider using -nepc");
		    exit(EXIT_FAILURE);
	    }
	*/

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
}

/*
 * Subtract constant from constant.
 */
static void
minus_fn(exp ap, exp b, int et)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_sub(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */
	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	if (et != f_wrap.err_code &&
	    (ov || constovf(b) || check_size(x, sg, shape_size(sh(ap))))) {
		setconstovf(ap);
	}

	/*
	if (check & CHECK_EXTRA) {
		if (sg && !in_proc_def &&
		    (ov || (shape_size(sh(ap)) <= 32 && check_size(x, sg, 32)))) {
		    error(ERR_INTERNAL, "constant addition out of bounds, consider using -nepc");
		    exit(EXIT_FAILURE);
	    }
	}
	*/

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
}

/*
 * Negate a constant exp, b, producing int.
 */
static void
neg_fn(exp b)
{
	flt64 x;

	x = exp_to_f64(b);
	x.big = ~x.big;
	x.small = ~x.small;

	if (x.small == (unsigned int)0xffffffff) {
		++x.big;
	}

	++x.small;
	bigres(b, &x);
}

/*
 * Negate a constant exp, b, producing int.
 */
static void
not_fn(exp b)
{
	flt64 x;

	x = exp_to_f64(b);
	x.big = ~x.big;
	x.small = ~x.small;

	bigres(b, &x);
}

/* Auxiliary function used for comm_ass by mult */
static void
mult_fn(exp ap, exp b, int et)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);

	IGNORE flt_mul(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */

	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	if (et != f_wrap.err_code &&
	    (ov || constovf(b) || check_size(x, sg, shape_size(sh(ap))))) {
		setconstovf(ap);
	}

	if (check & CHECK_EXTRA) {
		if (sg && (ov || (shape_size(sh(ap)) <= 32 && check_size(x, sg, 32)))) {
			error(ERR_INTERNAL, "constant mult out of bounds, consider using -nepc");
			exit(EXIT_FAILURE);
		}
	}

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
}

/* Auxiliary function used for comm_ass by and */
static void
and_fn(exp ap, exp b, int et)
{
	flt64 xa, xb;

	UNUSED(et);

	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	xa.small &= xb.small;
	xa.big &= xb.big;

	bigres(ap, &xa);
}

/* Auxiliary function used for comm_ass by or */
static void
or_fn(exp ap, exp b, int et)
{
	flt64 xa, xb;

	UNUSED(et);

	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	xa.small |= xb.small;
	xa.big |= xb.big;

	bigres(ap, &xa);
}

/* Auxiliary function used for comm_ass by xor */
static void
xor_fn(exp ap, exp b, int et)
{
	flt64 xa, xb;

	UNUSED(et);

	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	xa.small ^= xb.small;
	xa.big ^= xb.big;

	bigres(ap, &xa);
}

/*
 * Not used for comm_ass
 */
static void
domaxmin(exp ap, exp b, int mx)
{
	flt64 xa, xb;
	int use_a;

	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);

	if (is_signed(sh(ap))) {
		if (xa.big > xb.big) {
			use_a = mx;
		}

		if (xa.big < xb.big) {
			use_a = !mx;
		}

		if (xa.big == xb.big) {
			if (xa.small >= xb.small) {
				use_a = mx;
			} else {
				use_a = !mx;
			}
		}
	} else {
		if ((unsigned int)xa.big > (unsigned int)xb.big) {
			use_a = mx;
		}

		if ((unsigned int)xa.big < (unsigned int)xb.big) {
			use_a = !mx;
		}

		if (xa.big == xb.big) {
			if (xa.small >= xb.small) {
				use_a = mx;
			} else {
				use_a = !mx;
			}
		}
	}

	SET(use_a);
	if (use_a) {
		bigres(ap, &xa);
	} else {
		bigres(ap, &xb);
	}
}

/*
 * Produce allones for integer length of shape of e.
 */
static int
all_ones(exp e)
{
	switch (shape_size(sh(e))) {
	case  8: return 0xff;
	case 16: return 0xffff;
	default: return 0xffffffff;
	}
}

/*
 * Obey div1 on constants
 */
static void
dodiv1(exp ap, exp b)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_div(flptnos[fa], flptnos[fb], &resval);

	/* status cannot be wrong */
	IGNORE flpt_round_to_integer((int)f_toward_smaller, &resval);

	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
}

/*
 * Obey div2 on constants
 */
static void
dodiv2(exp ap, exp b)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);

	IGNORE flt_div(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */

	IGNORE flpt_round_to_integer((int)f_toward_zero, &resval);

	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
}

/*
 * Obey mod on constants
 */
static void
domod(exp ap, exp b)
{
	exp top = copy(ap);

	dodiv1(top, b);
	mult_fn(b, top, f_wrap.err_code);
	neg_fn(b);
	plus_fn(ap, b, f_wrap.err_code);
}

/*
 * Obey rem2 on constants
 */
static void
dorem2(exp ap, exp b)
{
	exp top = copy(ap);

	dodiv2(top, b);
	mult_fn(b, top, f_wrap.err_code);
	neg_fn(b);
	plus_fn(ap, b, f_wrap.err_code);
}

/*
 * Obey shift (places signed) on constants
 */
static void
doshl(exp e)
{
	flt64 x;
	exp arg1 = child(e);
	exp arg2 = next(arg1);
	int pl = no(arg2);
	shape sha = sh(e);
	int sg = is_signed(sha);

	sh(arg1) = sh(e);

	x = exp_to_f64(arg1);

	if (e->tag == shl_tag) {
		/* shift left */
		if (isbigval(arg2) || pl >= shape_size(sha)) {
			no(arg1) = 0;
			clearbigval(arg1);
			return;
		}

		if (pl >= 32) {
			x.big = (int) (x.small << (pl - 32));
			x.small = 0;
		} else {
			x.big <<= pl;
			x.big |= (int) (x.small >> (32 - pl));
			x.small <<= pl;
		}
	} else {
		/* shift right */
		if (isbigval(arg2) || pl >= shape_size(sha)) {
			no(arg1) = 0;
			if (sg) {
				if (isbigval(arg1)) {
					if (flptnos[no(arg1)].sign == -1) {
						no(arg1) = -1;
					}
				} else if (no(arg1) < 0) {
					no(arg1) = -1;
				}
			}
			clearbigval(arg1);
			return;
		}
		if (pl >= 32) {
			if (sg) {
				x.small = (unsigned int) (x.big >> (pl - 32));
				x.big = x.big >> 31;
			} else {
				x.small = ((unsigned int)x.big) >> (pl - 32);
				x.big = 0;
			}
		} else {
			if (sg) {
				x.small >>= pl;
				x.small |= (unsigned int) (x.big << (32 - pl));
				x.big >>= pl;
			} else {
				x.small >>= pl;
				x.small |= (unsigned int) (x.big << (32 - pl));
				x.big = (int) (((unsigned int)x.big) >> pl);
			}
		}
	}
	bigres(arg1, &x);
}

/*
 * Included if target has a setcc operation, to set a bit from the
 * condition flags.
 */
static exp
absbool(exp id)
{
	/*
	 * Check if e is (let a = 0 in cond(test(L) = result; a = 1 | L:top); a)
	 * If so, return the test, otherwise NULL.
	 */
	if (isvar(id) && child(id)->tag == val_tag && no(child(id)) == 0 &&
	    !isbigval(child(id)) && no(id) == 2) {
		/* name initially 0 only used twice */
		exp bdy = next(child(id));
		if (bdy->tag == seq_tag && next(child(bdy))->tag == cont_tag &&
		    child(next(child(bdy)))->tag == name_tag &&
		    child(child(next(child(bdy)))) == id) {
			/* one use is result of sequence body */
			exp c = child(child(bdy));
#ifdef TDF_DIAG3
			if (c->tag == diagnose_tag) {
				c = child(c);
			}
#endif
			if (c->last && c->tag == cond_tag) {
				/* seq is cond=c; id */
				exp first = child(c);
				exp second = next(child(c));
				/* only one jump to else */
				if (no(child(second)) == 1 &&
				    next(child(second))->tag == top_tag &&
				    first->tag == seq_tag) {
					/* cond is (seq = first | L: top) */
					exp s = child(child(first));
					exp r = next(child(first));
					/* last of seq is id = 1 */
					/* start of seq is int test jumping to
					 * second */
					if (r->tag == ass_tag &&
					    child(r)->tag == name_tag &&
					    child(child(r)) == id &&
					    next(child(r))->tag == val_tag &&
					    !isbigval(next(child(r))) &&
					    no(next(child(r))) == 1 &&
					    s->last && s->tag == test_tag &&
					    pt(s) == second) {
						return s;
					}
				} /* cond is (seq= first | L: top) */
			} /* seq is cond=c; id */
			if (c->last && c->tag == condassign_tag) {
				/* seq is condassign = c; id */
				exp s = child(c);
				exp r = next(s);
				/* last of seq is id = 1 */
				if (child(r)->tag == name_tag &&
				    child(child(r)) == id &&
				    next(child(r))->tag == val_tag &&
				    !isbigval(next(child(r))) &&
				    no(next(child(r))) == 1) {
					return s;
				}
			} /* seq is condassign = c; id */
		} /* one use is result of sequence body */
	} /* name initially 0 only used twice */
	return NULL;
}

/*
 * Distributes the operation e into a sequence,
 * ie. if e = op(seq(d ...; c), a) produces seq(d...; op(c, a))
 */
static int
seq_distr(exp e, exp scope)
{
	exp x = child(e);
	exp y;
	if (x->last || (!x->last && next(x)->last)) {
		if (x->tag == seq_tag || x->tag == ident_tag) {
			exp b = next(child(x));
			exp r;
			if (x->tag == ident_tag) {
				clearinlined(x);
			}
			if (x->last) {
				r = me_u3(sh(e), copy(b), e->tag);
			} else {
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_restruct_code(x, next(x), +1);
				}
#endif
				r = me_b3(sh(e), copy(b), next(x), e->tag);
			}
			pt(r) = pt(e);
			no(r) = no(e);
			props(r) = props(e);
			r = hold_refactor(r);
			sh(x) = sh(e);
			replace(b, r, r);	/* dgf preserved in copy */
			kill_exp(b, b);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, x);
			}
#endif
			replace(e, x, scope);
			return 1;
		}
	}
	if (!x->last && next(x)->last) {
		y = next(x);
		if (y->tag == seq_tag || y->tag == ident_tag) {
			exp b = next(child(y));
			exp r;
			if (y->tag == ident_tag) {
				clearinlined(y);
			}
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_restruct_code(y, x, -1);
			}
#endif
			r = me_b3(sh(e), x, copy(b), e->tag);
			pt(r) = pt(e);
			no(r) = no(e);
			props(r) = props(e);
			r = hold_refactor(r);
			sh(y) = sh(e);
			replace(b, r, r);		/* dgf preserved in copy */
			kill_exp(b, b);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, y);
			}
#endif
			replace(e, y, scope);
			return 1;
		}
	}
	return 0;
}

/* Reverses (ie. nots) test numbers */
static unsigned char revtest[6] = {
	4, 3, 2, 1, 6, 5
};

/*
 * Returns sign if |f| = 1, otherwise 0.
 */
static int
f_one(flpt f)
{
	flt fconst;
	fconst = flptnos[f];

	if (fconst.mant[0] == 1 && fconst.exp == 0) {
		int i = 1;
		while (i < MANT_SIZE && fconst.mant[i] == 0) {
			++i;
		}
		if (i == MANT_SIZE) {
			return fconst.sign;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

/*
 * Applies fneg.
 */
static exp
fneg(exp e)
{
	exp n = getexp(sh(e), NULL, 0, e, NULL, 0, 0, fneg_tag);
	e->last = true;
	next(e) = n;
	return n;
}

/*
 * Applies binary floating point operations.
 */
static int
refactor_fp2(exp e, exp scope)
{
	exp a1 = child(e);
	exp a2 = next(a1);
	flpt f1, f2;
	flt resval;
	int status;

	if (a1->tag == real_tag && a2->tag == real_tag) {
		/* this will condense to a single constant */
		f1 = no(a1);
		f2 = no(a2);

		switch (e->tag) EXHAUSTIVE {
		case fplus_tag:  status = flt_add(flptnos[f1], flptnos[f2], &resval); break;
		case fminus_tag: status = flt_sub(flptnos[f1], flptnos[f2], &resval); break;
		case fmult_tag:  status = flt_mul(flptnos[f1], flptnos[f2], &resval); break;
		case fdiv_tag:   status = flt_div(flptnos[f1], flptnos[f2], &resval); break;
		}

		if (status == OKAY) {
			flpt_round((int)f_to_nearest,
			           flpt_bits((floating_variety)(sh(e)->tag - shrealhd)), &resval);
			flptnos[f1] = resval;
			flpt_ret(f2);
			replace(e, a1, scope);
			retcell(e);
			retcell(a2);
			return 1;
		} else {
			return 0;
		}
	} else {
		/* see if one arg is constant */
		exp v_arg, c_arg;

		if (a1->tag == real_tag) {
			f1 = no(a1);
			c_arg = a1;
			v_arg = a2;
		} else if (a2->tag == real_tag) {
			f1 = no(a2);
			c_arg = a2;
			v_arg = a1;
		} else {
			return 0;	/* no change possible */
		}

		switch (e->tag) {
		case fplus_tag:
			if (flptnos[f1].sign == 0) {
				/* x + 0 or 0 + x */
				flpt_ret(f1);
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return 1;
			} else {
				return 0;
			}

		case fminus_tag:
			if (flptnos[f1].sign == 0) {
				/* x - 0 or 0 - x */
				flpt_ret(f1);
				if (v_arg == a2) {
					/* 0 - x = -x */
					v_arg = fneg(v_arg);
				}
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return 1;
			} else {
				return 0;
			}

		case fmult_tag:
			if (flptnos[f1].sign == 0) {
				/* x * 0 or 0 * x */
				replace(e, c_arg, scope);
				retcell(e);
				kill_exp(v_arg, scope);
				return 1;
			} else {
				int u = f_one(f1);
				if (u == 0) {
					return 0;
				}
				/* x * 1 or x * (-1) or 1 * x or (-1) * x */
				if (u == -1) {
					v_arg = fneg(v_arg);
				}
				flpt_ret(f1);
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return 1;
			}

		case fdiv_tag:
			if (flptnos[f1].sign == 0 && v_arg == a2) {
				/* 0 / x */
				replace(e, c_arg, scope);
				retcell(e);
				kill_exp(v_arg, scope);
				return 1;
			} else {
				int u = f_one(f1);
				if (u == 0 || v_arg == a2) {
					return 0;
				}
				/* x / 1 or x / (-1) */
				if (u == -1) {
					v_arg = fneg(v_arg);
				}
				flpt_ret(f1);
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return 1;
			}
		}
	}
	return 0;
}

/*
 * Compares integer constants using the test given by test_no.
 */
static int
docmp(shape sha, unsigned char test_no, int c1, int c2)
{
	int c;
	switch (shape_size(sha)) EXHAUSTIVE {
	case 8:
		if (is_signed(sha))
		{
			int d1 = (c1 & 0x80) ? (c1 | ~0x7f) : (c1 & 0xff);
			int d2 = (c2 & 0x80) ? (c2 | ~0x7f) : (c2 & 0xff);

			switch (test_no) EXHAUSTIVE {
			case 1: c = (d1 >  d2); break;
			case 2: c = (d1 >= d2); break;
			case 3: c = (d1 <  d2); break;
			case 4: c = (d1 <= d2); break;
			case 5: c = (d1 == d2); break;
			case 6: c = (d1 != d2); break;
			}
			break;
		} else {
			unsigned char d1 = (unsigned char)(c1 & 0xff);
			unsigned char d2 = (unsigned char)(c2 & 0xff);

			switch (test_no) EXHAUSTIVE {
			case 1: c = (d1 >  d2); break;
			case 2: c = (d1 >= d2); break;
			case 3: c = (d1 <  d2); break;
			case 4: c = (d1 <= d2); break;
			case 5: c = (d1 == d2); break;
			case 6: c = (d1 != d2); break;
			}
			break;
		}
	case 16:
		if (is_signed(sha))
		{
			int d1 = (c1 & 0x8000) ? (c1 | ~0x7fff) : (c1 & 0xffff);
			int d2 = (c2 & 0x8000) ? (c2 | ~0x7fff) : (c2 & 0xffff);

			switch (test_no) EXHAUSTIVE {
			case 1: c = (d1 >  d2); break;
			case 2: c = (d1 >= d2); break;
			case 3: c = (d1 <  d2); break;
			case 4: c = (d1 <= d2); break;
			case 5: c = (d1 == d2); break;
			case 6: c = (d1 != d2); break;
			}
			break;
		} else {
			unsigned short d1 = (unsigned short)(c1 & 0xffff);
			unsigned short d2 = (unsigned short)(c2 & 0xffff);

			switch (test_no) EXHAUSTIVE {
			case 1: c = (d1 >  d2); break;
			case 2: c = (d1 >= d2); break;
			case 3: c = (d1 <  d2); break;
			case 4: c = (d1 <= d2); break;
			case 5: c = (d1 == d2); break;
			case 6: c = (d1 != d2); break;
			}
			break;
		}
	case 32:
		if (is_signed(sha))
		{
			int d1 = c1;
			int d2 = c2;

			switch (test_no) EXHAUSTIVE {
			case 1: c = (d1 >  d2); break;
			case 2: c = (d1 >= d2); break;
			case 3: c = (d1 <  d2); break;
			case 4: c = (d1 <= d2); break;
			case 5: c = (d1 == d2); break;
			case 6: c = (d1 != d2); break;
			}
			break;
		} else {
			unsigned int d1 = (unsigned int)c1;
			unsigned int d2 = (unsigned int)c2;

			switch (test_no) EXHAUSTIVE {
			case 1: c = (d1 >  d2); break;
			case 2: c = (d1 >= d2); break;
			case 3: c = (d1 <  d2); break;
			case 4: c = (d1 <= d2); break;
			case 5: c = (d1 == d2); break;
			case 6: c = (d1 != d2); break;
			}
			break;
		}
	}
	return c;
}


int
docmp_f(int test_no, exp a, exp b)
{
	shape sha = sh(a);
	flt64 xa, xb;
	int sg = is_signed(sha);
	int eq = 0;
	int less = 0;
	int gr = 0;

	if (shape_size(sh(a)) <= 32) {
		return docmp(sha, (unsigned char)test_no, no(a), no(b));
	}

	xa = exp_to_f64(a);
	xb = exp_to_f64(b);

	if (xa.big == xb.big && xa.small == xb.small) {
		eq = 1;
	}

	if (sg && !eq) {
		if (xa.big < xb.big) {
			less = 1;
		} else if (xa.big > xb.big) {
			gr = 1;
		} else {
			if (xa.small < xb.small) {
				less = 1;
			} else {
				gr = 1;
			}
		}
	} else if (!eq) {
		if ((unsigned int)xa.big < (unsigned int)xb.big) {
			less = 1;
		} else if ((unsigned int)xa.big > (unsigned int)xb.big) {
			gr = 1;
		} else {
			if (xa.small < xb.small) {
				less = 1;
			} else {
				gr = 1;
			}
		}
	}

	switch (test_no) EXHAUSTIVE {
	case 1: return gr   ;
	case 2: return gr   | eq;
	case 3: return less ;
	case 4: return less | eq;
	case 5: return        eq;
	case 6: return       !eq;
	}

	UNREACHED;
	return -1;
}

/*
 * Main bottom-to-top optimise routine Optimises e.
 * No change propagates outside scope.
 */
int
refactor(exp e, exp scope)
{
	if (is_a(e->tag)) {
		/* main op non-side effect */
		unsigned char n = e->tag;
		if (child(e) != NULL && n != name_tag && n != env_offset_tag &&
		    n != general_env_offset_tag && n != proc_tag &&
		    n != general_proc_tag) {
			exp temp = child(e);
			for (;;) {
				if (sh(temp)->tag == bothd) {
					/* unordered; temp can be first, iwc all siblings unreachable */
#ifdef TDF_DIAG4
					if (diag != DIAG_NONE) {
						exp sib = child(e);
						for (;;) {
							if (sib != temp) {
								dg_dead_code(sib, temp);
							}
							if (sib->last) {
								break;
							}
							sib = next(sib);
						}
						dg_whole_comp(e, temp);
					}
#endif
					replace(e, temp, scope);
					retcell(e);
					return 1;
				}
				if (temp->last) {
					break;
				}
				temp = next(temp);
			}
		}

		switch (e->tag) {
		case component_tag: {
			exp v = child(e);
			exp a = next(v);

			if (a->tag == val_tag) {
				exp res;
				if (no(a) == 0 &&
				    shape_size(sh(v)) ==
				    shape_size(sh(e))
				    && (optim & OPTIM_UNPAD_APPLY || v->tag != apply_tag))
				{
					/*
					 * Remove the operation if the offset is zero and the size is the same.
					 * This typically happens in selecting from a union if the component has
					 * the maximum size in the union.
					 */
					sh(v) = sh(e);
#ifdef TDF_DIAG4
					if (diag != DIAG_NONE) {
						dg_whole_comp(e, v);
					}
#endif
					replace(e, v, scope);
					retcell(a);
					retcell(e);
					return 1;
				}

				/* otherwise use field_tag */

				res = getexp(sh(e), NULL, 0, v,
				             NULL, 0, no(a),
				             field_tag);
				setfather(res, child(res));
#ifdef TDF_DIAG4
				dgf(res) = dgf(e);
#endif
				replace(e, hold_refactor(res), scope);
				retcell(e);
				retcell(a);
				return 1;
			}
			if (v->tag == cont_tag) {
				/*
				 * Replace selecting from contents by
				 * taking contents of reff selection.
				 */
				exp ap = hold_refactor(f_add_to_ptr(child(v),
				                                    a));
				ap = hold_refactor(f_contents(sh(e), ap));
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(v, ap);
					dg_whole_comp(e, ap);
				}
#endif
				replace(e, ap, scope);
				retcell(v);
				retcell(e);
				return 1;
			}
			{ /* Always remove component_tag: use a declaration */
				exp var = me_startid(sh(e), v, 1);
				exp ap, c;
				exp ob;
				ob = me_obtain(var);
				ap = hold_refactor(f_add_to_ptr(ob, a));
				c = hold_refactor(f_contents(sh(e), ap));
				var = me_complete_id(var, c);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, var);
				}
#endif
				replace(e, var, scope);
				retcell(e);
				return 1;
			}
		}

		case offset_pad_tag:
			if (child(e)->tag == val_tag && !isbigval(child(e))) {
				/* constant evaluation */
				int al = al2(sh(e));
				if (al == 0) {
					al = 1;
				}
				if (al2_of(sh(e))->al.sh_hd > nofhd) {
					al = shape_align(f_pointer(al2_of(sh(e))));
				}
#if TRANS_HPPA
				if ((al1_of(sh(e))->al.frame & 4) != 0) {
					no(child(e)) = -rounder(-no(child(e)), al);
				} else

#endif
					no(child(e)) = rounder(no(child(e)), al);
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_add_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(child(e)) &&
			    !isbigval(next(child(e)))) {
				/* both arguments constant */
				int n;
				exp a = child(e);
				exp b = next(a);

				n = no(a) + no(b);

				no(a) = n;
				sh(a) = sh(e);
				retcell(b);
				replace(e, a, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_subtract_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(child(e)) &&
			    !isbigval(next(child(e)))) {
				/* both arguments constant */
				no(child(e)) -= no(next(child(e)));
				sh(child(e)) = sh(e);
				retcell(next(child(e)));
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_negate_tag:
			if (child(e)->tag == val_tag &&
			    !isbigval(child(e))) {
				/* argument constant */
				no(child(e)) = - no(child(e));
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_max_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(child(e)) &&
			    !isbigval(next(child(e)))) {
				/* both arguments constant */
				int n1 = no(child(e));
				int n2 = no(next(child(e)));
				no(child(e)) = (n1 > n2) ? n1 : n2;
				sh(child(e)) = sh(e);
				retcell(next(child(e)));
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_mult_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(child(e)) &&
			    !isbigval(next(child(e)))) {
				/* both arguments constant */
				int n1 = no(child(e));
				int n2 = no(next(child(e)));
				no(child(e)) = n1 * n2;
				sh(child(e)) = sh(e);
				retcell(next(child(e)));
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == val_tag &&
			    !isbigval(child(e)) &&
			    no(child(e)) == 1) {
				/* multiply by 1 */
				sh(next(child(e))) = sh(e);
				replace(e, next(child(e)), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == val_tag &&
			    !isbigval(child(e)) && no(child(e)) == 0) {
				/* multiply by 0 - replace by sequence - side-effects! */
				exp_list el;
				el.start = next(child(e));
				el.end = next(child(e));
				el.number = 1;
				sh(child(e)) = sh(e);
				replace(e, f_sequence(el, child(e)),
				        scope);
				retcell(e);
				return 1;
			}

			if (next(child(e))->tag == val_tag &&
			    child(e)->tag == plus_tag) {
				/* distribute offset_mult over plus (giving offset_adds) */
				/* the plus operation */
				exp pl = child(e);

				/* the offset constant */
				exp b = next(pl);

				/* the first plus operand */
				exp x = child(pl);

				exp bx = next(x);
				exp res = hold_refactor(me_b3(sh(e), x,
				                              copy(b), offset_mult_tag));
				exp temp;
				while (bx != pl) {
					x = bx;
					bx = next(x);
					temp = hold_refactor(me_b3(sh(e),
					                           x, copy(b),
					                           offset_mult_tag));
					res = hold_refactor(me_b3(sh(e),
					                          res, temp,
					                          offset_add_tag));
				}
				retcell(b);
				replace(e, res, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_div_by_int_tag:
		case offset_div_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(child(e)) &&
			    !isbigval(next(child(e)))) {
				/* both arguments constant */
				int n1 = no(child(e));
				int n2 = no(next(child(e)));
				no(child(e)) = n1 / n2;
				sh(child(e)) = sh(e);
				retcell(next(child(e)));
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case absbool_tag: {
			exp arg1;
			exp arg2;
			ntest nt;

			if (~has & HAS_SETCC) {
				return 0;
			}

			arg1 = child(e);
			arg2 = next(arg1);
			nt = test_number(e);
			if ((arg1->tag == val_tag ||
			     arg1->tag == null_tag) &&
			    (arg2->tag == val_tag ||
			     arg2->tag == null_tag)) {
				/* argument constant */
				no(arg1) = docmp_f((int)nt, arg1, arg2);
				arg1->tag = val_tag;
				sh(arg1) = sh(e);
				clearbigval(arg1);
				retcell(arg2);
				replace(e, arg1, scope);
				retcell(e);
				return 1;
			}
			if (arg1->tag == val_tag ||
			    arg1->tag == real_tag ||
			    arg1->tag == null_tag) {
				/* constant argument always second */
				child(e) = arg2;
				next(arg2) = arg1;
				next(arg1) = e;
				arg1->last = true;
				arg2->last = false;
				nt = exchange_ntest[nt];
				settest_number(e, nt);
			}
			return 0;
		}

		/* apply commutative and associative laws */
		case plus_tag:
#if TRANS_X86
		{
			exp arg1 = child(e);
			exp arg2 = next(arg1);
			if (!optop(e)) {
				return 0;
			}
			if (arg1->tag == val_tag &&
			    arg2->tag == val_tag) {
				plus_fn(arg1, arg2, errhandle(e));
				sh(arg1) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					if (dgf(arg1)) {
						dg_detach_const(arg1,
						                e);
					}
					if (dgf(arg2)) {
						dg_detach_const(arg2,
						                e);
					}
					dgf(arg1) = dgf(e);
				}
#endif
				replace(e, arg1, scope);
				retcell(e);
				return 1;
			}
			if (arg1->tag == val_tag) {
				exp q = hold_refactor(f_plus(f_impossible,
				                             arg2, arg1));
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, q);
				}
#endif
				replace(e, q, scope);
				retcell(e);
				return 1;
			}
			if (arg2->tag == plus_tag &&
			    next(child(arg2))->tag == val_tag &&
			    optop(arg2)) {
				exp con = next(child(arg2));
				exp x = hold_refactor(f_plus(f_impossible,
				                             hold_refactor(f_plus(f_impossible,
				                                     arg1, child(arg2))), con));
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, x);
				}
#endif
				replace(e, x, scope);
				retcell(e);
				return 1;
			}
			if (arg1->tag == plus_tag &&
			    next(child(arg1))->tag == val_tag &&
			    optop(arg1)) {
				exp x = hold_refactor(f_plus(f_impossible,
				                             child(arg1),
				                             hold_refactor(f_plus(f_impossible,
				                                     arg2, next(child(arg1))))));
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, x);
				}
#endif
				replace(e, x, scope);
				retcell(e);
				return 1;
			}
			if (arg2->tag == plus_tag &&
			    arg1->tag != plus_tag && optop(arg2)) {
				exp t = next(child(arg2));
				exp x = hold_refactor(f_plus(f_impossible,
				                             hold_refactor(f_plus(f_impossible,
				                                     arg1, child(arg2))), t));
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, x);
				}
#endif
				replace(e, x, scope);
				retcell(e);
				return 1;
			}

			return seq_distr(e, scope);
		}
#else
		return comm_ass(e, plus_tag, plus_fn, 0, 0, 0, scope, 1, 0);
#endif /* TRANS_X86 */

		case fplus_tag:
			/*
			 * Apply zero, unit and constant evaluation.
			 *
			 * NB dive MUST be false, because floating point is not really
			 * commutative and associative.
			 *
			 * XXX: floating point is actually commutative, but not associative.
			 */
			return comm_ass(e, fplus_tag, fplus_fn, fzero_no, 0, 0,
			                scope, 0, 1);
		case addptr_tag:
			if ((child(e)->tag == null_tag ||
			     child(e)->tag == val_tag) &&
			    !isbigval(child(e)) && no(child(e)) == 0) {
				if (next(child(e))->tag == val_tag &&
				    !isbigval(next(child(e))) &&
				    al2(sh(next(child(e)))) > 1) {
					/* constant evaluation */
					sh(next(child(e))) = sh(e);
					no(next(child(e))) /= 8;
#ifdef TDF_DIAG4
					if (diag != DIAG_NONE) {
						dg_whole_comp(e,
						              next(child(e)));
					}
#endif
					replace(e, next(child(e)), scope);
					retcell(child(e));
					retcell(e);
					return 1;
				}
			}
#if TRANS_ALPHA
			{
				exp ptr = child(e);
				exp off = next(ptr);
				if ((al1_of(sh(off))->al.frame & 4) != 0 &&
				    !is_floating(al2_of(sh(off))->al.sh_hd)) {
					exp r = getexp(sh(ptr), off, 0,
					               ptr, NULL, 0,
					               6 * 64, reff_tag);
					sh(off) =
					    f_offset(al1_of(sh(off)),
					             long_to_al(al2(sh(off))));
					next(ptr) = r;
					ptr->last = true;
					child(e) = r;
				}
			}

#endif
			if (next(child(e))->tag == val_tag &&
			    !isbigval(next(child(e)))) {
				/* replace addptr(x, const) by refffield operation */
				exp p = child(e);
				int k = no(next(p));
				exp r;
				r = getexp(sh(e), NULL, 0, p, NULL,
				           0, k, reff_tag);
#ifdef TDF_DIAG4
				dgf(r) = dgf(e);
#endif
				replace(e, hc(r, p), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == reff_tag &&
			    shape_size(sh(e)) == 32) {
				/* replace addptr(reff[n](a), b) by reff[n](addptr(a, b)) */
				exp p = child(child(e));
				exp a = next(child(e));
				exp ap1 = getexp(sh(e), NULL, 0, p,
				                 NULL, 0, 0,
				                 addptr_tag);
				exp ap, r;
				next(p) = a;
				p->last = false;
#if TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(child(e), p);
				}
#endif
				ap = hc(ap1, a);
				r = hc(getexp(sh(e), NULL, 0, ap,
				              NULL, 0, no(child(e)),
				              reff_tag), ap);
#if TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, r);
				}
#endif
				replace(e, r, scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}
			if (next(child(e))->tag == offset_add_tag) {
				exp p = child(e);
				exp a = child(next(p));
				exp c = next(a);
				if (c->tag == val_tag &&
				    !isbigval(c)) {
					exp ap = hold_refactor(me_b3(f_pointer(long_to_al(al2(sh(a)))),
					                             p, a, addptr_tag));
					exp r = getexp(sh(e), NULL, 0,
					               ap, NULL, 0,
					               no(c), reff_tag);
					setfather(r, ap);
#ifdef TDF_DIAG4
					dgf(r) = dgf(e);
#endif
					replace(e, hold_refactor(r),
					        scope);
					retcell(e);
					return 1;
				}
				if (al1(sh(p)) == al2(sh(c))) {
					exp inner, outer;
					inner = hold_refactor(me_b3(sh(e),
					                            p, a, addptr_tag));
#ifdef TDF_DIAG4
					if (diag != DIAG_NONE) {
						dg_whole_comp(next(p),
						              inner);
					}
#endif
					outer = hold_refactor(me_b3(sh(e),
					                            inner, c, addptr_tag));
#ifdef TDF_DIAG4
					if (diag != DIAG_NONE) {
						dg_whole_comp(e, outer);
					}
					/* also represent movement of
					 * c! */
#endif
					replace(e, outer, scope);
					retcell(e);
					return 1;
				}
			}
			return 0;

		case chvar_tag:
			if (child(e)->tag == null_tag) {
				child(e)->tag = val_tag;
				no(child(e)) = value_of_null;
				clearbigval(child(e));
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == val_tag && optop(e)) {
				/* evaluate chvar(const) */
				int bg;
				flt64 x;
				shape sha = sh(e);
				x = exp_to_f64(child(e));
				/*
				if (has & HAS_64_BIT) {
					int sg = is_signed(sha);
					if (check & CHECK_EXTRA) {
						if (sg && !in_proc_def &&
						    shape_size(sha) <= 32 &&
						    check_size(x, sg, 32)) {
							error(ERR_INTERNAL, "Change_variety out of range");
							exit(EXIT_FAILURE);
						}
					}
				}
				 */
				dochvar_f(&x, sha);
				no(child(e)) = f64_to_flpt(x, is_signed(sha), &bg,
				                         shape_size(sha));
				if (bg) {
					setbigval(child(e));
				} else {
					clearbigval(child(e));
				}
				sh(child(e)) = sha;
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (eq_shape(sh(e), sh(child(e)))) {
				/* replace identity chvar by argument */
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == chvar_tag &&
			    shape_size(sh(e)) ==
			    shape_size(sh(child(child(e)))) &&
			    sh(child(e))->tag == bitfhd) {
				exp res = hold_refactor(me_u3(sh(e),
				                              child(child(e)),
				                              chvar_tag));
				replace(e, res, scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == chvar_tag &&
			    !is_signed(sh(e)) &&
			    shape_size(sh(e)) ==
			    shape_size(sh(child(e)))) {
				replace(e, hold_refactor(me_u3(sh(e),
				                               child(child(e)), chvar_tag)), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == chvar_tag &&
			    !is_signed(sh(e)) &&
			    shape_size(sh(e)) <
			    shape_size(sh(child(e))) &&
			    shape_size(sh(e)) ==
			    shape_size(sh(child(child(e))))) {
				replace(e, hold_refactor(me_u3(sh(e),
				                               child(child(e)), chvar_tag)),
				        scope);
				retcell(e);
				return 1;
			}
			if (endian == ENDIAN_LITTLE && has & HAS_BYTEREGS) {
				/* only for little enders which have byte registers */
				if ((shape_size(sh(e)) <=
				     shape_size(sh(child(e)))) && optop(e) &&
				    (child(e)->tag == name_tag ||
				     child(e)->tag == cont_tag ||
				     child(e)->tag == cond_tag)) {
					/*
					 * If the chvar operation never needs any action
					 * for a little end machine, eliminate it.
					 */
#if TRANS_X86
					if (shape_size(sh(e)) == 8) {
						if (child(e)->tag == name_tag) {
							setvis(child(child(e)));
						}
						if (child(e)->tag == cont_tag &&
						    child(child(e))->tag ==
						    name_tag) {
							setvis(child(child(child(e))));
						}
					}
#endif
					sh(child(e)) = sh(e);
					replace(e, child(e), scope);
					/* should this retcell(e) ? */
					return 1;
				}
				/* Only for little enders which have byte registers */
				if (child(e)->tag == chvar_tag &&
				    shape_size(sh(e)) <=
				    shape_size(sh(child(e)))) {
					/*
					 * If the chvar operation never needs any action
					 * for a little end machine, eliminate it.
					 */
					exp w;
					sh(child(e)) = sh(e);
					w = hold(child(e));
					IGNORE refactor(child(w), child(w));
					replace(e, child(w), scope);
					retcell(e);
					retcell(w);
					return 1;
				}
			}
			if (endian == ENDIAN_LITTLE) {
				/* Only for little enders with byte and short operations */
				if (has & HAS_BYTEOPS && shape_size(sh(e)) <=
				    shape_size(sh(child(e))) && optop(e) &&
				    sh(e)->tag != bitfhd &&
				    (child(e)->tag == plus_tag ||
				     child(e)->tag == minus_tag ||
				     child(e)->tag == and_tag ||
				     child(e)->tag == or_tag ||
				     child(e)->tag == neg_tag)) {
					/*
					 * Replace chvar(op(a ...)) by op(chvar(a)...) if the changevar
					 * requires no action on a little end machine
					 */

					exp p = child(e);
					exp r;
					exp a = child(p);
					exp n = next(a);
					int l = (int)a->last;

					/* if (optim & OPTIM_SHORTEN_OPS || shape_size(sh(e)) >= 16) */
					/* this is to avoid allocating bytes to edi/esi in 80386 !!! bad */
					{
						exp sha = sh(e);
						exp t = varchange(sha, a);
						exp q = t;

						while (!l) {
							l = (int)n->last;
							a = n;
							n = next(n);
							setnext(q, varchange(sha, a));
							q->last = false;
							q = next(q);
						}

						r = getexp(sha, NULL, 0, t, pt(p), 0, no(p), p->tag);
						seterrhandle(r, errhandle(e));
						replace(e, hc(r, q), scope);
						retcell(e);
						return 1;
					}
				}
			}
			if (child(e)->tag == ident_tag &&
			    isvar(child(e))) {
				/* distribute chvar into variable declaration of simple form */
				exp vardec = child(e);
				exp def = child(vardec);
				exp body = next(def);
				exp res;
				bool go = 1;
				exp t, u, v;
				if (body->tag != seq_tag) {
					return 0;
				}
				res = next(child(body));
				if (res->tag != cont_tag ||
				    child(res)->tag != name_tag ||
				    child(child(res)) != vardec) {
					return 0;
				}
				t = pt(vardec);
				while (t != NULL && go) {
					if (t == child(res) ||
					    (!t->last &&
					     next(next(t))->tag ==
					     ass_tag)) {
						t = pt(t);
					} else {
						go = 0;
					}
				}
				if (!go) {
					return 0;
				}
				if (def->tag == clear_tag) {
					u = copy(def);
					sh(u) = sh(e);
				} else {
					u = varchange(sh(e), copy(def));
				}
				replace(def, u, u);
				kill_exp(def, def);
				sh(res) = sh(e);
				sh(body) = sh(e);
				t = pt(vardec);
				while (t != NULL) {
					if (t != child(res)) {
						v = next(t);
						u = varchange(sh(e), copy(v));
						replace(v, u, u);
						kill_exp(v, def);
					}
					t = pt(t);
				}
				sh(vardec) = sh(e);
				replace(e, vardec, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case bitf_to_int_tag:
			if (newcode) {
				exp temp = child(e);
				int szbf = shape_size(sh(temp));
				shape sha;
				int sg = is_signed(sh(temp));
				int s;

				if (szbf <= 8) {
					sha = (sg) ? scharsh : ucharsh;
				} else if (szbf <= 16) {
					sha = (sg) ? swordsh : uwordsh;
				} else if (szbf <= 32) {
					sha = (sg) ? slongsh : ulongsh;
				} else {
					sha = (sg) ? s64sh : u64sh;
				}

				if (sh(temp)->tag == bitfhd &&
				    temp->tag == chvar_tag) {
					exp st = child(temp);
					int n = st->tag;
					if ((n == cont_tag &&
					     szbf == shape_size(sh(st))) ||
					    (n == and_tag &&
					     next(child(st))->tag == val_tag &&
					     no(next(child(st))) == (1 << szbf) - 1)
					    || (n == shr_tag &&
					        next(child(st))->tag == val_tag &&
					        no(next(child(st))) ==
					        shape_size(sh(st)) - szbf)) {
						/* arises from bfcont_tag */
						replace(e,
						        hold_refactor(me_u3(sh(e),
						                            st, chvar_tag)), scope);
						retcell(e);
						retcell(temp);
						return 1;
					}
				}


				sh(temp) = sha;

				if (sg) {
#if TRANS_ALPHA
					s = shape_size(s64sh) - szbf;
					if (s != 0) {
						temp = hold_refactor(me_u3(s64sh, temp, chvar_tag));
						temp = hold_refactor(me_b3(s64sh, temp, me_shint(s64sh, s), shl_tag));
						temp = hold_refactor(me_b3(s64sh, temp, me_shint(s64sh, s), shr_tag));
					}
#else
					s = shape_size(sha) - szbf;
					if (s != 0) {
						temp = hold_refactor(me_b3(sha, temp, me_shint(sha, s), shl_tag));
						temp = hold_refactor(me_b3(sha, temp, me_shint(sha, s), shr_tag));
					}
#endif
				} else {
					int mask = (szbf == 32) ? -1 :
					           (1 << szbf) - 1;
					temp = hold_refactor(me_b3(sha, temp, me_shint(sha, mask), and_tag));
				}

				replace(e, hold_refactor(me_u3(sh(e), temp, chvar_tag)), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case int_to_bitf_tag:
			if (newcode) {
				exp temp = child(e);
				shape sha = sh(temp);
				int szbf = shape_size(sh(e));
				int sg = is_signed(sh(e));

				if (shape_size(sh(child(e))) < szbf) {
					if (szbf <= 32) {
						sha = (sg) ? slongsh : ulongsh;
					} else {
						sha = (sg) ? s64sh : u64sh;
					}

					temp = hold_refactor(me_u3(sha, temp,
					                           chvar_tag));
				} else {
					UNUSED(sha);
				}
				temp = hold_refactor(me_u3(sh(e), temp,
				                           chvar_tag));
				replace(e, temp, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case minptr_tag: {
			exp s = child(e);
			exp b = next(s);
			if (s->tag == val_tag && b->tag == null_tag) {
				sh(s) = sh(e);
				no(s) -= no(b);
				no(s) *= 8;
				replace(e, s, scope);
				retcell(e);
				return 1;
			}
			if (s->tag == val_tag && b->tag == val_tag) {
				/* both constants */
				sh(s) = sh(e);
				no(s) -= no(next(child(e)));
				no(s) *= 8;
				replace(e, s, scope);
				retcell(e);
				return 1;
			}
			if (b->tag == null_tag && no(b) == 0) {
				sh(s) = sh(e);
				replace(e, s, scope);
				retcell(e);
				return 1;
			}
			if (s->tag == name_tag && b->tag == name_tag &&
			    child(s) == child(b)) {
				int n = no(s) - no(b);
				exp r;
				r = getexp(sh(e), NULL, 0, NULL, NULL, 0,
				           n, val_tag);
				kill_exp(s, s);
				kill_exp(b, b);
				replace(e, r, scope);
				retcell(e);
				return 1;
			}
			return 0;
		}

		case minus_tag: {
			exp z, a2, r;
			exp arg1 = child(e);
			exp arg2 = next(arg1);
			if (!optop(e)) {
				return 0;
			}
			if (arg1->tag == val_tag && arg2->tag == val_tag) {
				minus_fn(arg1, arg2, errhandle(e));
				sh(arg1) = sh(e);
				replace(e, arg1, scope);
				retcell(e);
				return 1;
			}
			/* replace a - b by a + (-b) */
			z = getexp(sh(e), NULL, 0, next(child(e)), pt(e), 0, 0,
			           neg_tag);
			seterrhandle(z, errhandle(e));
			a2 = hc(z, next(child(e)));
			r = getexp(sh(e), NULL, 0, child(e), pt(e), 0, 0,
			           plus_tag);
			seterrhandle(r, errhandle(e));
#ifdef TDF_DIAG4
			dgf(r) = dgf(e);
#endif
			next(child(e)) = a2;
			replace(e, hc(r, a2), scope);
			retcell(e);
			return 1;
		}

		case mult_tag:
			if (!optop(e)) {
				return 0;
			}
			if (next(child(e))->tag == val_tag &&
			    next(child(e))->last &&
			    child(e)->tag == plus_tag &&
			    next(child(child(e)))->tag == val_tag) {
				/*
				 * Replace mult(plus(a, const1), const2) by
				 * plus(mult(a, const2), const1*const2)
				 */
				int k = no(next(child(e))) * no(next(child(child(e))));
				exp ke = me_shint(sh(e), k);
				exp m = getexp(sh(e), NULL, 0, child(child(e)),
				               NULL, 0, 0, mult_tag);
				exp m1, pa;
				setnext(child(m), copy(next(child(e))));
				child(m)->last = false;
				m1 = hc(m, next(child(m)));
				pa = getexp(sh(e), NULL, 0, m1, NULL, 0, 0,
				            plus_tag);
				next(m1) = ke;
				m1->last = false;
				replace(e, hc(pa, ke), scope);
				retcell(e);
				return 1;
			}

			/* apply commutative and associative laws */
#if TRANS_X86
			return comm_ass(e, mult_tag, mult_fn, 1, 1, 0, scope, 0, 0);
#else
			return comm_ass(e, mult_tag, mult_fn, 1, 1, 0, scope, 1, 0);
#endif

		case subptr_tag: {
			/* replace subptr(a, b) by addptr(a, (-b)) */
			exp z = getexp(sh(e), NULL, 0, next(child(e)), NULL,
			               0, 0, neg_tag);
			exp a2 = hc(z, next(child(e)));
			exp r = getexp(sh(e), NULL, 0, child(e), NULL, 0,
			               0, addptr_tag);
			next(child(e)) = a2;
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dgf(r) = dgf(e);
			}
#endif
			replace(e, hc(r, a2), scope);
			retcell(e);
			return 1;
		}

		case neg_tag: {
			if (!optop(e)) {
				return 0;
			}
			if (child(e)->tag == val_tag) {
				/* eval for const */
				neg_fn(child(e));
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == neg_tag && optop(e) &&
			    optop(child(e))) {
				/* replace --a by a if errtreat is impossible or ignore */
				sh(child(child(e))) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(child(e), child(child(e)));
					dg_whole_comp(e, child(child(e)));
				}
#endif
				replace(e, child(child(e)), scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}
			if (child(e)->tag == plus_tag && optop(e) &&
			    optop(child(e))) {
				/*
				 * Replace negate(plus(a, b ..)) by
				 * plus(negate(a), negate(b) ..))
				 */
				exp r = getexp(sh(e), NULL, 0, NULL, NULL, 0, 0, plus_tag);
				exp t = child(child(e));
				exp p = r;
				int lst;
				do {
					exp q = hold(getexp(sh(e), NULL, 0, t, NULL, 0, 0, neg_tag));
					exp next = next(t);
					lst = (int)t->last;
					next(t) = child(q);
					t->last = true;
					IGNORE refactor(child(q), scope);
					next(p) = child(q);
					retcell(q);
					p = next(p);
					p->last = false;
					t = next;
				} while (!lst);
				child(r) = next(r);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, r);
				}
#endif
				replace(e, hc(r, p), scope);
				retcell(e);
				return 1;
			}
			return 0;
		}

		case shl_tag:
		case shr_tag:
			if (next(child(e))->tag == val_tag &&
			    no(next(child(e))) == 0) {
				/* remove zero place shift */
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag) {
				/* evaluate if both args constant */
				doshl(e);
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
#if TRANS_MIPS
			if (next(child(e))->tag == val_tag &&
			    no(next(child(e))) == shape_size(sh(e))) {
				exp s1 = copy(e);
				no(next(child(s1)))--;
				if (e->tag == shl_tag) {
					s1 = f_shift_left(f_continue, s1, me_shint(sh(next(child(e))), 1));
				} else {
					s1 = f_shift_right(s1, me_shint(sh(next(child(e))), 1));
				}
				replace(e, s1, scope);
				kill_exp(e, scope);
				return 1;
			}
#endif

			/*
			 * Only use if the shift left and shift right operations
			 * are performed by the same instruction,
			 * distinguished by the sign of the number of places.
			 */
			if (has & HAS_NEGSHIFT && e->tag == shr_tag) {
				exp places = next(child(e));
				exp r;
				exp neg = getexp(sh(places), NULL, 0, places,
				                 NULL, 0, 0, neg_tag);
				neg = hc(neg, places);
				r = getexp(sh(e), NULL, 0, child(e), NULL, 0,
				           0, shl_tag);
				next(child(e)) = neg;
				r = hc(r, neg);
				replace(e, r, scope);
				retcell(e);
				return 1;
			}

			if (e->tag == shr_tag && child(e)->tag == shl_tag &&
			    next(child(e))->tag == val_tag) {
				exp arg1 = child(e);
				int r = no(next(arg1));
				if (child(arg1)->tag == shr_tag &&
				    next(child(arg1))->tag == val_tag) {
					exp arg11 = child(arg1);
					int q = no(next(arg11));
					if (r >= q &&
					    next(child(arg11))->tag == val_tag) {
						exp x = child(arg11);
						int p = no(next(x));
						if (q >= p) {
							exp temp =
							    hold_refactor(me_b3(sh(arg1),
							                        x, me_shint(sh(arg1),
							                                    q - p), shl_tag));
							replace(child(e), temp, temp);
							/* FALL_THROUGH */
						}
					}
				} else {
					if (next(child(arg1))->tag == val_tag) {
						int q = no(next(child(arg1)));
						int se = shape_size(sh(e));
						if (q == r &&
						    (q == (se - 16) ||
						     q == (se - 8)) &&
						    is_signed(sh(arg1))) {
							shape sc = (q == se - 16) ?  swordsh : scharsh;
							exp temp1 = me_u3(sc, child(arg1), chvar_tag);
							exp temp2 = me_u3(sh(e), temp1, chvar_tag);
							replace(e, hold_refactor(temp2), scope);
							retcell(e);
							return 1;
						}
					}
				}
			}

			if (e->tag == shl_tag && child(e)->tag == and_tag &&
			    next(child(e))->tag == val_tag) {
				exp arg1 = child(e);
				exp arg2 = next(arg1); /* left_places */
				if (arg1->tag == and_tag &&
				    next(child(arg1))->tag == val_tag) {
					exp arg11 = child(arg1);
					exp arg12 = next(arg11); /* mask */
					if (arg11->tag == shr_tag &&
					    next(child(arg11))->tag == val_tag) {
						exp arg111 = child(arg11);
						/* right places */
						exp arg112 = next(arg111);

						shape sha = sh(e);
						{
							exp a = hold_refactor(me_b3(sha, arg111,
							                            me_shint(sha, no(arg12) << no(arg112)),
							                            and_tag));
							exp res;
							if (no(arg2) >= no(arg112))
								res = me_b3(sha, a, me_shint(sha, no(arg2) - no(arg112)), shl_tag);
							else
								res = me_b3(sha, a, me_shint(sha, no(arg112) - no(arg2)), shr_tag);
							replace(e, hold_refactor(res), scope);
							retcell(e);
							return 1;
						}
					}
				}
			}
			return seq_distr(e, scope);

		case mod_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag) {
				/* evaluate if both args constant */
				if (is_signed(sh(e)) && no(next(child(e))) == -1) {
					replace(e, me_shint(sh(e), 0), scope);
					retcell(e);
					return 1;
				}
				if (no(next(child(e))) != 0) {
					domod(child(e), next(child(e)));
					sh(child(e)) = sh(e);
					replace(e, child(e), scope);
					retcell(e);
					return 1;
				}
			}
			return 0;

		case rem0_tag:
		case rem2_tag:
			if (child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag) {
				/* evaluate if both args constant */

				/* some compilers get the rem2 wrong */
				if (is_signed(sh(e)) && no(next(child(e))) == -1) {
					replace(e, me_shint(sh(e), 0), scope);
					retcell(e);
					return 1;
				}
				if (no(next(child(e))) != 0) {
					dorem2(child(e), next(child(e)));
					sh(child(e)) = sh(e);
					replace(e, child(e), scope);
					retcell(e);
					return 1;
				}
			}
			return 0;

		case div1_tag:
			if (next(child(e))->tag == val_tag &&
			    no(next(child(e))) == 1) {
				/* remove divide by 1 */
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (optop(e) && child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    no(next(child(e))) != 0) {
				/* evaluate if both args constant */
				dodiv1(child(e), next(child(e)));
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case div0_tag:
		case div2_tag:
			if (next(child(e))->tag == val_tag &&
			    no(next(child(e))) == 1) {
				/* remove divide by 1 */
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			if (optop(e) && child(e)->tag == val_tag &&
			    next(child(e))->tag == val_tag &&
			    no(next(child(e))) != 0) {
				/* evaluate if both args constant */
				dodiv2(child(e), next(child(e)));
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case max_tag:
		case min_tag: {
			exp arg1 = child(e);
			exp arg2 = next(arg1);

			if (arg1->tag == val_tag && arg2->tag == val_tag) {
				domaxmin(arg1, arg2, e->tag == max_tag);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;
		}

		case chfl_tag:
			if (!optop(e)) {
				return 0;
			}

			if (sh(e)->tag == sh(child(e))->tag) {
				/* eliminate redundant chfl */
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == real_tag) {
				if (sh(e)->tag < sh(child(e))->tag) {
					flpt_round((int)f_to_nearest,
					           flpt_bits((floating_variety)(sh(e)->tag -
					                                        shrealhd)), &flptnos[no(child(e))]);
				}
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == chfl_tag &&
			    sh(child(child(e)))->tag == sh(e)->tag &&
			    sh(e)->tag < sh(child(e))->tag) {
				/*
				 * chfl(flsh1, chfl(flsh2, exp of shape flsh1))
				 * to internal exp iff flsh2 includes flsh1
				 */
				sh(child(child(e))) = sh(e);
				replace(e, child(child(e)), scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}
			return 0;

		case round_tag:
			if (!optop(e)) {
				return 0;
			}

			if (child(e)->tag == real_tag) {
				/* apply if arg constant */
				flpt f = no(child(e));
				flt64 x;
				int ov, pr;
				int sg = is_signed(sh(e));
				exp iexp;
				IGNORE flpt_round_to_integer(round_number(e),
				                             &flptnos[f]);
				x = flt_to_f64(f, sg, &ov);
				iexp = me_shint(sh(e), f64_to_flpt(x, sg, &pr,
				                                   shape_size(sh(e))));
				if (pr) {
					setbigval(iexp);
				}
				replace(e, iexp, scope);
				kill_exp(e, scope);
				return 1;
			}

			return 0;

		case float_tag:
			if (!optop(e)) {
				return 0;
			}

			if (child(e)->tag == val_tag) {
				/* apply if arg constant */
				exp arg = child(e);
				shape sha = sh(arg);
				int k = no(arg);
				int sz = shape_size(sha);
				int sg = is_signed(sha);

				if (PIC_code) {
					proc_externs = true;
				}

				if (sz == 8) {
					k = k & 0xff;
					if (sg && k >= 0x80) {
						k = (k | (int)0xffffff00);
					}
					no(arg) = floatrep(k);
				} else if (sz == 16) {
					k = k & 0xffff;
					if (sg && k >= 0x8000) {
						k = (k | (int)0xffff0000);
					}
					no(arg) = floatrep(k);
				} else if (sz == 32) {
					/* watch out for 64bits */
					if (sg) {
						no(arg) = floatrep(k);
					} else {
						no(arg) = floatrep_unsigned(uno(arg));
					}
					/* use unsigned selector for k */
				} else {
					if (!isbigval(arg)) {
						no(arg) =
						    f64_to_flt(exp_to_f64(arg),
						               is_signed(sha));
					}
					clearbigval(arg);
				}

				flpt_round((int)f_to_nearest,
				           flpt_bits((floating_variety)(sh(e)->tag -
				                                        shrealhd)), &flptnos[no(arg)]);
				arg->tag = real_tag;
				sh(arg) = sh(e);
				replace(e, arg, scope);
				retcell(e);
				return 1;
			}

			return 0;

		case fmult_tag:
			/*
			 * Apply zero, unit and constant evaluation.
			 *
			 * NB dive MUST be false, because floating point is not really
			 * commutative and associative
			 * XXX: floating point is actually commutative, but not associative
			 */

			return comm_ass(e, fmult_tag, fmult_fn, fone_no, 1,
			                fzero_no, scope, 0, 1);
		case fminus_tag:
			if (!optop(e)) {
				return 0;
			}
			/* constant evaluation */
			if (refactor_fp2(e, scope)) {
				return 1;
			}
			return 0;

		case fdiv_tag:
			if (!optop(e)) {
				return 0;
			}

			/* constant evaluation */
			if (refactor_fp2(e, scope)) {
				return 1;
			}

			if (next(child(e))->tag == real_tag &&
			    flptnos[no(next(child(e)))].sign != 0 &&
			    (!strict_fl_div ||
			     flpt_power_of_2(no(next(child(e)))))) {
				shape sha = sh(e);
				exp one;
				exp temp;
				flpt f = new_flpt();

				flt_copy(flptnos[fone_no], &flptnos[f]);
				one = getexp(sha, NULL, 0, NULL, NULL, 0,
				             f, real_tag);
				temp = hold_refactor(me_b3(sha, one, next(child(e)),
				                           fdiv_tag));
				temp = hold_refactor(me_b3(sha, child(e), temp,
				                           fmult_tag));
				seterrhandle(temp, errhandle(e));
				replace(e, temp, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case fneg_tag:
			if (!optop(e)) {
				return 0;
			}

			if (child(e)->tag == real_tag) {
				/* apply if arg constant */
				int fn = no(child(e));
				flptnos[fn].sign = -flptnos[fn].sign;
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			} else if (child(e)->tag == fneg_tag) {
				/* --a = a (should check ignore overflow) */
				replace(e, child(child(e)), scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}

			return 0;

		case fabs_tag:
			if (child(e)->tag == real_tag) {
				/* apply if arg constant */
				int fn = no(child(e));
				if (flptnos[fn].sign == -1) {
					flptnos[fn].sign = 1;
				}
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case and_tag:
			if (has & HAS_BYTEOPS &&
			    next(child(e))->tag == val_tag &&
			    no(next(child(e))) == 0xff &&
			    child(e)->tag == shr_tag &&
			    child(child(e))->tag == cont_tag) {
				exp a1 = next(child(child(e)));

				if (a1->tag == val_tag && !isbigval(a1) &&
				    (no(a1) & 0x7) == 0) {
					exp t = child(child(child(e)));
					exp r = me_u3(sh(t), t, reff_tag);
					exp c, v;

					switch (endian) {
					case ENDIAN_LITTLE:
						no(r) = no(a1);
						break;
					case ENDIAN_BIG:
						no(r) = shape_size(sh(e)) - no(a1) - 8;
						break;
					}

					r = hold_refactor(r);
					c = hold_refactor(me_u3(ucharsh, r,
					                        cont_tag));
					v = hold_refactor(me_u3(sh(e), c,
					                        chvar_tag));
					replace(e, v, scope);
					retcell(e);
					return 1;
				}
			}

			if (child(e)->tag == and_tag &&
			    next(child(e))->tag == val_tag &&
			    next(child(child(e)))->tag == val_tag &&
			    !isbigval(next(child(e))) &&
			    !isbigval(next(child(child(e))))) {
				int mask = no(next(child(e))) &
				           no(next(child(child(e))));
				exp res = hold_refactor(me_b3(sh(e), child(child(e)),
				                              me_shint(sh(e), mask), and_tag));
				replace(e, res, scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == shr_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(next(child(e))))
			{
				exp arg1 = child(e);
				exp arg2 = next(arg1); /* mask */
				int m = no(arg2);
				int sz = shape_size(sh(arg1));

				if (m > 0 && next(child(arg1))->tag == val_tag &&
				    !isbigval(next(child(arg1))) &&
				    m <= ((1 << (sz - no(next(child(arg1))))) - 1))
				{
					exp arg11 = child(arg1);
					/* right shift places */
					exp arg12 = next(arg11);

					if (arg11->tag == shl_tag &&
					    next(child(arg11))->tag == val_tag &&
					    !isbigval(next(child(arg11)))) {
						exp arg111 = child(arg11);
						/* left shift places */
						exp arg112 = next(arg111);

						if (no(arg112) <= no(arg12)) {
							exp res = hold_refactor(me_b3(sh(arg1),
							                        arg111, me_shint(sh(arg1), no(arg12) - no(arg112)),
							                        shr_tag));
							replace(arg1, res, res);
							return refactor(e, scope);
						}
					}
				}
			}

			/* apply commutative and associative laws */
			return comm_ass(e, and_tag, and_fn, all_ones(child(e)), 1,
			                0, scope, 1, 0);
		case or_tag:
			/* apply commutative and associative laws */
			if (child(e)->tag == and_tag &&
			    next(child(e))->tag == val_tag &&
			    !isbigval(next(child(e))) &&
			    next(child(child(e)))->tag)
			{
				exp arg1 = child(e);
				int q = no(next(arg1));
				exp arg11 = child(arg1);
				int p = no(next(arg11));
				if ((q | p) == (int)0xffffffff) {
					exp res = me_b3(sh(e), arg11, next(arg1),
					                or_tag);
					replace(e, hold_refactor(res), scope);
					retcell(e);
					return 1;
				}
			}

			return comm_ass(e, or_tag, or_fn, 0,
			                shape_size(sh(e)) <= 32,
			                all_ones(child(e)), scope, 1, 0);

		case xor_tag:
			/* apply commutative and associative laws */
			return comm_ass(e, xor_tag, xor_fn, 0, 0, 0, scope, 1, 0);

		case not_tag:
			if (child(e)->tag == val_tag) {
				/* eval for const */
				not_fn(child(e));
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == not_tag) {
				/* not(not(x))->x */
				sh(child(child(e))) = sh(e);
				replace(e, child(child(e)), scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}

			return 0;

		case cont_tag:
			if (promote_pars) {
				int x = al1_of(sh(child(e)))->al.sh_hd;

				if (x >= scharhd && x <= uwordhd && endian == ENDIAN_BIG) {
					int disp = shape_size(ulongsh) -
					           ((x >= swordhd) ? 16 : 8);
					exp r = getexp(f_pointer(f_alignment(sh(e))),
					               NULL, 1, child(e), NULL, 0,
					               disp, reff_tag);
					next(child(r)) = r;
					child(e) = hold_refactor(r);
					next(child(e)) = e;
					child(e)->last = true;
					return 1;
				}
			}

#ifdef TDF_DIAG3
			if (child(e)->tag == diagnose_tag) {
				exp diag = child(e);
				exp p = child(diag);
				exp r = getexp(sh(e), NULL, 0, p, NULL, 0,
				               0, cont_tag);
				exp d;
				r = hc(r, p);
				d = getexp(sh(e), NULL, 0, r, pt(diag),
				           props(diag), no(diag), diagnose_tag);
				setfather(d, r);
				replace(e, d, scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}
#endif

			return 0;

		case field_tag:
			if (child(e)->tag == compound_tag && nos(child(e))) {
				exp s = child(child(e));
				for (;;) {
					if (no(s) == no(e) &&
					    eq_shape(sh(e), sh(next(s)))) {
						replace(e, copy(next(s)), scope);
						kill_exp(e, scope);
						return 1;
					}
					if (next(s)->last) {
						break;
					}
					s = next(next(s));
				}
			}

			if (child(e)->tag == nof_tag && nos(child(e))
			    && eq_shape(sh(e), sh(child(child(e))))) {
				exp s = child(child(e));
				int sz = rounder(shape_size(sh(s)),
				                 shape_align(sh(s)));
				int n = 0;
				for (; no(e) <= n; n += sz) {
					if (no(e) == n) {
						replace(e, copy(s), scope);
						kill_exp(e, scope);
						return 1;
					}
					if (s->last) {
						break;
					}
					s = next(s);
				}
			}

			if (child(e)->tag == name_tag) {
				/* replace field on name by name with offset in
				 * no */
				no(child(e)) += no(e);
				sh(child(e)) = sh(e);
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == cont_tag) {
				/* replace field[n](cont(x)) by cont(reff[n](x)) */
				exp arg = child(child(e));
				exp rf1 = getexp(sh(arg), NULL, 0, arg,
				                 NULL, 0, no(e), reff_tag);
				exp rf = hc(rf1, arg);
				exp c = getexp(sh(e), NULL, 0, rf, NULL, 0,
				               0, cont_tag);
				replace(e, hc(c, rf), scope);
				retcell(child(e));
				retcell(e);
				return 1;
			}

			if (child(e)->tag == ident_tag && isvar(child(e)) &&
			    child(child(e))->tag == clear_tag &&
			    next(child(child(e)))->tag == seq_tag) {
				exp var = child(e);
				exp sq = next(child(var));

				if (next(child(sq))->tag == cont_tag &&
				    child(next(child(sq)))->tag == name_tag &&
				    child(child(next(child(sq)))) == var) {
					int count = 0;
					int good = 0;
					exp p = child(child(sq));
					exp q;
					exp res;

					while (p != child(sq)) {
						if (p->tag != ass_tag ||
						    child(p)->tag != name_tag ||
						    child(child(p)) != var) {
							return 0;
						}
						++count;
						if (no(child(p)) == no(e)) {
							good = 1;
						}
						p = next(p);
					}

					if ((count + 1) != no(var) || !good) {
						return 0;
					}

					p = child(child(sq));
					while (p != child(sq)) {
						q = next(p);
						if (no(child(p)) == no(e)) {
							exp tp = f_make_top();
							res = next(child(p));
							replace(p, tp, tp);
						} else {
							exp w = next(child(p));
							replace(p, w, w);
						}
						p = q;
					}

					SET(res);
					replace(next(child(sq)), res, res);
					replace(e, hold_refactor(sq), scope);
					return 1;
				}
				return 0;
			}
			return 0;

		case reff_tag:
			if (child(e)->tag == name_tag &&
			    isvar(child(child(e))) && al1(sh(e)) > 1) {
				/* replace reff on name of var by name with offset in no */
				no(child(e)) += no(e);
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			if (child(e)->tag == val_tag) {
				no(child(e)) += (no(e) / 8);
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			/* TODO: confirm mips doesnt need this */
#if 0
			if (child(e)->tag == reff_tag) {
				/* combine reff selections */
				sh(child(e)) = sh(e);
				no(child(e)) += no(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
#endif

			if (optim & OPTIM_ZEROOFFSETS && no(e) == 0 && al1(sh(e)) > 1) {
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}

			return 0;
		case bfcont_tag:
		case bfcontvol_tag: {
			exp p = child(e);
			int bsz = shape_size(sh(e));
			int rsz = al1(sh(p));
			int rsh;
			int sg = is_signed(sh(e));
			int off = no(e);
			exp ref;
			exp cont;
			exp eshift;
			shape ptr_sha;
			shape msh;
			int temp = off + bsz - 1;

			if (rsz > BF_STORE_UNIT) {
				rsz = BF_STORE_UNIT;
			}

			if (((off / 8) == (temp / 8)) &&
			    (bsz == 8 &&
			     ((endian == ENDIAN_LITTLE && (off % 8 == 0)) ||
			      (endian == ENDIAN_BIG    && ((8 - (off % 8) - bsz) == 0))))) {
				rsz = 8;
			} else if (((off / 16) == (temp / 16)) &&
			           (bsz == 16 &&
			            ((endian == ENDIAN_LITTLE && (off % 16 == 0)) ||
			             (endian == ENDIAN_BIG    &&
			              ((16 - (off % 16) - bsz) == 0))))) {
				rsz = 16;
			}
#if TRANS_ALPHA
			else if (((off / 32) == (temp / 32)) &&
			         (!sg || (al1(sh(p)) < 64) ||
			          (bsz == 32 &&
			           ((endian == ENDIAN_LITTLE && (off % 32 == 0)) ||
			            (endian == ENDIAN_BIG    &&
			             ((32 - (off % 32) - bsz) == 0)))))) {
				rsz = 32;
			}
#endif
			else {
				/* all of bitfield must be within same integer variety */
				while ((off / rsz) != (temp / rsz)) {
					rsz = rsz << 1;
				}
			}

			msh = containedshape(rsz, sg);
			ptr_sha = f_pointer(long_to_al(rsz));
			if ((off / rsz) != 0) {
				ref = me_u3(ptr_sha, p, reff_tag);
				no(ref) = (off / rsz) * rsz;
				ref = hold_refactor(ref);
			} else {
				ref = p;
			}
			switch (endian) {
			case ENDIAN_LITTLE:
				rsh = off % rsz;
				break;
			case ENDIAN_BIG:
				rsh = rsz - (off % rsz) - bsz;
				break;
			}
			cont = me_u3(msh, ref, (e->tag == bfcont_tag) ?
			             (unsigned char)cont_tag :
			             (unsigned char)contvol_tag);
			if (rsh == 0 && !sg && bsz != rsz) {
				eshift = me_b3(msh, cont,
				               me_shint(slongsh, (1 << bsz) - 1),
				               and_tag);
			} else {
				if (rsz - bsz - rsh != 0) {
					cont = me_b3(msh, cont,
					             me_shint(slongsh, rsz -
					                      bsz - rsh), shl_tag);
				}

				if (rsz - bsz != 0) {
					eshift = me_b3(msh, cont,
					               me_shint(slongsh, rsz -
					                        bsz), shr_tag);
				} else {
					eshift = cont;
				}
			}
			eshift = me_u3(sh(e), eshift, chvar_tag);

			replace(e, eshift , scope);
			retcell(e);
			return 1;
		}

		case abs_tag:
			if (child(e)->tag == val_tag) {
				if (is_signed(sh(e)) &&
				    ((isbigval(child(e)) &&
				      flptnos[no(child(e))].sign) ||
				     (!isbigval(child(e)) &&
				      no(child(e)) < 0))) {
					/* eval for const */
					if (!optop(e)) {
						return 0;
					}
					neg_fn(child(e));
				}
				sh(child(e)) = sh(e);
#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_whole_comp(e, child(e));
				}
#endif
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case fmax_tag:
		case fmin_tag: {
			bool fmin = (e->tag == fmin_tag);
			exp arg1 = child(e);
			exp arg2 = next(arg1);
			/* identify arg1 */
			exp id1 = me_startid(sh(arg1), arg1, 0);
			/* identify arg2 */
			exp id2 = me_startid(sh(arg2), arg2, 0);

			exp seq;
			exp cond;
			exp zero;
			exp lab;
			exp clear;
			exp test;

			clear = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
			               0, clear_tag);
			lab = me_b3(sh(arg2), clear, me_obtain(id2), labst_tag);
			test = me_q2(no_nat_option, f_impossible,
			             fmin ? f_less_than : f_greater_than,
			             &lab, me_obtain(id1), me_obtain(id2),
			             test_tag);
			zero = me_u3(sh(test), test, 0);
			seq = me_b3(sh(arg1), zero, me_obtain(id1), seq_tag);
			cond = me_b3(sh(arg1), seq, lab, cond_tag);
			id2 = me_complete_id(id2, cond);
			id1 = me_complete_id(id1, id2);
			replace(e, id1, scope);
			retcell(e);
			return 1;
		}

		case name_tag: {
			exp s = child(e);
			if (!isvar(s) && isglob(s) && child(s) != NULL &&
			    sh(e)->tag == sh(child(s))->tag &&
			    (child(s)->tag == val_tag ||
			     child(s)->tag == real_tag)) {
				exp c = copy(child(s));
				replace(e, c, scope);
				kill_exp(e, scope);
				return 1;
			} else {
				return 0;
			}

		}

		case fpower_tag:
		case imag_tag:
		case make_complex_tag:
			return 0;

		case rotl_tag:
		case rotr_tag:
		case env_offset_tag:
		case general_env_offset_tag:
		case proc_tag:
		case general_proc_tag:
		case top_tag:
		case val_tag:
		case real_tag:
		case current_env_tag:
		case make_lv_tag:
		case clear_tag:
		case null_tag:
		case string_tag:
		case power_tag:
		case contvol_tag:
			return 0;

		default:
			return 0;
		}
	}

	/* side effecting ops */
	switch (e->tag) {
	case compound_tag: {
		exp bse = next(child(e));
		unsigned char shn = sh(bse)->tag;
		if (bse->last && child(e)->tag == val_tag &&
		    no(child(e)) == 0 &&
		    shape_size(sh(e)) == shape_size(sh(bse)) &&
		    shn != prokhd && (shn < shrealhd || shn > doublehd)
		    && (optim & OPTIM_UNPAD_APPLY || bse->tag != apply_tag)
		   )
		{
			/*
			 * Remove the creation of a compound if it consists of a
			 * single value of the same size and provided that the component
			 * is not real (because it might be in the wrong place.
			 */
			if (bse->tag == name_tag && isvar(child(bse)) &&
			    !isglob(child(bse)) &&
			    sh(child(child(bse)))->tag >= shrealhd &&
			    sh(child(child(bse)))->tag <= doublehd) {
				setvis(child(bse));
				props(e) = (prop)(props(e) & ~0x08);
			}
			sh(bse) = sh(e);

#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, bse);
			}
#endif

			replace(e, bse, scope);
			retcell(child(e));
			retcell(e);
			return 1;
		}
	}

	if (optim & OPTIM_COMPOUNDS && in_proc_def) {
		/*
		 * Provided that the exp is inside a procedure definition we
		 * always remove compound creation and replace it by a
		 * variable declaration for the compound, assignments to
		 * the components, and deliver the compound.
		 */
		shape she = sh(e);
		exp var = me_start_clearvar(she, she);
		exp cont = getexp(she, NULL, 0, NULL, NULL, 0, 0, cont_tag);
		exp_list el;
		exp obt;
		exp t = child(e);
		exp seq;
		obt = me_obtain(var);
		child(cont) = obt;
		setfather(cont, obt);
		el = new_exp_list(0);

		for (;;) {
			exp q = next(t);	/* expression being assigned */
			exp n = next(q);
			int end = (int)q->last;
			exp ass, p, ap;
			p = me_obtain(var);
			if (sh(q)->tag != bitfhd || !newcode) {
				/* destination */
				ap = hold_refactor(f_add_to_ptr(p, t));
				ass = hold_refactor(f_assign(ap, q));
			} else {
				ass = hold_refactor(f_bitfield_assign(p, t,
				                                      q));
			}
			el = add_exp_list(el, ass, 0);
			if (end) {
				break;
			}
			t = n;
		}

		seq = f_sequence(el, cont);
#ifdef TDF_DIAG4
		if (diag != DIAG_NONE) {
			dg_whole_comp(e, var);
		}
#endif

		replace(e, me_complete_id(var, seq), scope);
		retcell(e);
		return 1;
	}

	return 0;
#ifdef TDF_DIAG3
	case diagnose_tag:
#endif
	case prof_tag:
		return 0;
	case ident_tag:
		if (sh(child(e))->tag == bothd) {
			exp s = child(e);
			exp b = next(s);
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_dead_code(b, s);
				dg_whole_comp(e, s);
			}
#endif
			kill_exp(b, b);
			replace(e, s, scope);
			retcell(e);
			return 1;
		}

		/* use if target has setcc instruction */
		if (has & HAS_SETCC) {
			exp abst = absbool(e);
			if (abst != NULL) {
#ifdef TRANS_X86
				if (sh(child(abst))->tag <= u64hd)
#endif
				{
					/* check if we can use setcc */
					exp a = copy(abst);
					a->tag = absbool_tag;
					pt(a) = NULL;
					sh(a) = sh(e);
#ifdef NEWDIAG
					if (diag != DIAG_NONE) {
						dg_whole_comp(e, a);
					}
#endif
					replace(e, a, a);
					kill_exp(e, e);
					return 0;
				}
			}
		}

		if (sh(next(child(e)))->tag != sh(e)->tag) {
			sh(e) = sh(next(child(e)));
			IGNORE refactor_id(e, scope);
			return 1;
		}
		return refactor_id(e, scope);	/* see refactor_id.c */

	case seq_tag:
		if (child(child(e)) == NULL) {
			/* remove empty seq */
			exp s = child(e);
			sh(next(s)) = sh(e);	/* unless bottom ? */

#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, next(s));
			}
#endif
			replace(e, next(s), scope);
			retcell(s);
			return 1;
		}
		return refactor_seq(e, scope);

	case cond_tag:
		if (no(child(next(child(e)))) == 0) {
			/* remove inaccessible statements */
			exp bs = next(child(e));
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_dead_code(next(child(bs)), child(e));
				dg_whole_comp(e, child(e));
			}
#endif
			replace(e, child(e), scope);
			kill_exp(bs, scope);
			retcell(e);
			return 1;
		}

		/*
		 * Replace cond which has first a simple goto to the
		 * alt by the alt (removing the label)
		 */
		if (child(e)->tag == goto_tag && pt(child(e)) == next(child(e))) {
			exp x = next(child(next(child(e))));

			/*
			 * Copy shape of cond to the alt. they should be the same,
			 * but optimisations may have changed signed to unsigned
			 * and vice versa, and these changes would otherwise be undone.
			 */
			sh(x) = sh(e);

#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_rdnd_code(child(e), x);
				dg_whole_comp(e, x);
			}
#endif
			replace(e, x, scope);
			retcell(child(next(child(e))));
			retcell(next(child(e)));
			if (child(child(e)) != NULL) {
				retcell(child(child(e)));
			}

			retcell(child(e));
			retcell(e);
			return 1;
		}

		if (child(e)->tag == seq_tag && no(child(next(child(e)))) == 1 &&
		    next(child(child(e)))->tag == goto_tag) {
			/* is e = cond(seq(..;goto m), l: x) and is only 1 use of l */
			exp t = child(child(child(e)));
			while (!t->last) {
				t = next(t);
			}
#ifdef TDF_DIAG3
			if (t->tag == diagnose_tag) {
				t = child(t);
			}
#endif
			if ((t->tag == test_tag || t->tag == testbit_tag) &&
			    pt(t) == next(child(e)) && test_number(t) <= 6) {
				/*
				 * Look at last element of sequence before goto m to see
				 * if it is a conditional jump to l. If so reverse the test,
				 * make it jump to m and remove the goto.
				 */

				settest_number(t, revtest[test_number(t) - 1]);
				pt(t) = pt(next(child(child(e))));
				sh(child(e)) = sh(next(child(next(child(e)))));
				replace(next(child(child(e))), next(child(next(child(e)))),
				        child(e));
				replace(e, child(e), scope);
				retcell(e);
				return 1;
			}
		}

		if (has & HAS_MAXMIN) {
			exp t;
			int bl = is_maxlike(e, &t);
			int ismax = 0;
			int ismin = 0;
			ntest nt;

			if (bl) {
				nt = test_number(t);
				if (nt == f_greater_than ||
				    nt == f_greater_than_or_equal) {
					ismax = 1;
				}
				if (nt == f_less_than ||
				    nt == f_less_than_or_equal) {
					ismin = 1;
				}
			} else {
				bl = is_minlike(e, &t);
				if (bl) {
					nt = test_number(t);
					if (nt == f_greater_than ||
					    nt == f_greater_than_or_equal) {
						ismin = 1;
					}
					if (nt == f_less_than ||
					    nt == f_less_than_or_equal) {
						ismax = 1;
					}
				}
			}

			if (ismax || ismin) {
				exp tq = me_b2(copy(child(t)), copy(next(child(t))),
				               (ismax) ?
				               (unsigned char)max_tag :
				               (unsigned char)min_tag);
				replace(e, hold_refactor(tq), scope);
				kill_exp(e, e);
				return 1;
			}
		}

		if (has & HAS_CONDASSIGN) {
			exp to_test;
			exp to_ass;

			if (is_condassign(e, &to_test, &to_ass) &&
			    is_floating(sh(child(to_test))->tag) ==
			    is_floating(sh(next(child(to_ass)))->tag)) {
				exp res = me_b3(sh(e), to_test, to_ass,
				                condassign_tag);
				replace(e, res, scope);
				retcell(e);
				return 1;
			}
		}

		if (next(child(next(child(e))))->tag == top_tag) {
			exp first = child(e);
			exp alt = next(first);
			int in_repeat = 0;
			if (crt_repeat != NULL &&
			    (int) (props(crt_repeat)) == 1) {
				in_repeat = 1;
			}
			if (take_out_of_line(first, alt, in_repeat, 1.0)) {
				exp t = child(child(first));
				exp tst = (is_tester(t, 0)) ? t : next(child(t));
				if (no(tst) == 1000) {
					no(tst) = 25;
				}
			}
		}
		return 0;

	case condassign_tag:
		if (~has & HAS_CONDASSIGN) {
			return 0;
		}

		if (next(child(e))->tag != ass_tag &&
		    (child(e)->tag == test_tag ||
		     child(e)->tag == testbit_tag)) {
			exp sqz = me_b3(f_top, child(child(e)), next(child(child(e))),
			                0);
			exp sq = me_b3(sh(e), sqz, next(child(e)), seq_tag);
			replace(e, hold_refactor(sq), scope);
			retcell(e);
			return 1;
		}

		if (child(e)->tag == goto_tag) {
			replace(e, getexp(f_top, NULL, 0, NULL, NULL, 0,
			                  0, top_tag), scope);
			retcell(e);
			return 1;
		}

		if (child(e)->tag == top_tag) {
			replace(e, next(child(e)), scope);
			retcell(e);
			return 1;
		}

	case goto_tag:
	case return_to_label_tag:
	case trap_tag:
		return 0;
	case ass_tag:
#if 0
		/*
		 * Prepare to replace the assignment of structure results of
		 * procedures. If it decides to do so it will put the destination
		 * in as the first parameter of the procedure.
		 */
		if (0 && redo_structfns && !reg_result(sh(next(child(e)))) &&
		    next(child(e))->tag == ident_tag &&
		    isvar (next(child(e))))
		{
			exp id = next(child(e));
			exp def = child(id);
			exp body = next(def);

			if (def->tag == clear_tag && body->tag == seq_tag) {
				if (child(child(body))->tag == apply_tag &&
				    child(child(body))->last &&
				    next(child(body))->tag == cont_tag &&
				    child(next(child(body)))->tag == name_tag &&
				    child(child(next(child(body)))) == id)
				{
					exp ap = child(child(body));
					exp p1 = next(child(ap));
					if (p1->tag == name_tag &&
					    child(p1) == id && ap->last)
					{
						/* this is the assignment of a struct result of a proc */
						exp p2 = next(child(ap));
						exp se = child(e);
						if (p2->last) {
							se->last = true;
						}

						next(se) = next(p2);
						next(child(ap)) = se;
						if (se->tag == name_tag &&
						    isvar(child(se)) &&
						    !isglob(child(se)) &&
						    shape_size(sh(id)) == shape_size(sh(child(child(se)))))
						{
							setreallyass(se);
						}

						replace(e, ap, scope);
						return 1;
					}
				}
			}
		}
#endif

		if (promote_pars) {
			int x = al1_of(sh(child(e)))->al.sh_hd;

			if (x >= scharhd && x <= uwordhd && endian == ENDIAN_BIG) {
				exp b = next(child(e));
				int disp = shape_size(ulongsh) -
				           ((x >= swordhd) ? 16 : 8);
				exp r = getexp(f_pointer(f_alignment(sh(b))),
				               NULL, 1, child(e), NULL, 0,
				               disp, reff_tag);
				next(child(r)) = r;
				child(r)->last = true;
				r = hold_refactor(r);
				next(r) = b;
				r->last = false;
				child(e) = r;
				return 1;
			}
		}

		return seq_distr(e, scope);

	case testbit_tag: {
		exp arg1 = child(e);
		exp arg2 = next(arg1);

		if (arg1->tag == val_tag && arg2->tag == val_tag &&
		    !isbigval(arg1) && !isbigval(arg2))
		{
			/* evaluate if args constant */
			int k = no(arg1) & no(arg2);
			if ((k != 0 && test_number(e) == 5) ||
			    (k == 0 && test_number(e) == 6)) {
				repbygo(e, pt(e), scope);
			} else {
				repbycont(e, 1, scope);
			}

			return 1;
		}

		if (arg1->tag == shr_tag && arg2->tag == val_tag &&
		    next(child(arg1))->tag == val_tag &&
		    !isbigval(arg2) && !isbigval(next(child(arg1))))
		{
			exp x = child(arg1);
			exp nsh = next(x);
			int places = no(nsh);
			exp res;

			sh(x) = sh(arg2);
			res = me_b3(sh(e), x,
			            me_shint(sh(arg2), no(arg2) << places), testbit_tag);
			no(res) = no(e);
			pt(res) = pt(e);
			settest_number(res, test_number(e));
			replace(e, hold_refactor(res), scope);
			retcell(e);
			return 1;
		}

		return 0;
	}

	case test_tag: {
		exp arg1, arg2;
		int n, bl;
		unsigned char nt = test_number(e);
		arg1 = child(e);
		arg2 = next(arg1);

		if (flpt_always_comparable ||
		    (sh(arg1)->tag < shrealhd || sh(arg1)->tag > doublehd))
		{
			switch (nt) {
			case  7: nt = f_greater_than;          break;
			case  8: nt = f_greater_than_or_equal; break;
			case  9: nt = f_less_than;             break;
			case 10: nt = f_less_than_or_equal;    break;
			case 11: nt = f_not_equal;             break;
			case 12: nt = f_equal;                 break;

			case 13:
				repbycont(e, 1, scope);
				return 1;

			case 14:
				repbygo(e, pt(e), scope);
				return 1;

			default:
				break;
			}
		}

		settest_number(e, nt);

		/* evaluate constant expressions */

		if ((arg1->tag == val_tag || arg1->tag == null_tag) &&
		    (arg2->tag == val_tag || arg2->tag == null_tag)) {
			/*
			 * See if we know which way to jump and replace by unconditional
			 * goto or nop. For integers.
			 */
			int c = docmp_f((int)test_number(e), arg1, arg2);

			if (c) {
				repbycont(e, 1, scope);
			} else {
				repbygo(e, pt(e), scope);
			}

			return 1;
		}

		if (test_number(e) >= 5 &&
		    ((arg1->tag == null_tag && no(arg1) == 0 &&
		      arg2->tag == name_tag && isvar(child(arg2))) ||
		     (arg2->tag == null_tag && no(arg2) == 0 &&
		      arg1->tag == name_tag && isvar(child(arg1)))))
		{
			/*
			 * If we are comparing NULL with a variable we know
			 * the way to jump.
			 */

			if (test_number(e) == 6) {
				repbycont(e, 1, scope);
			} else {
				repbygo(e, pt(e), scope);
			}

			return 1;
		}

		if (arg1->tag == real_tag && arg2->tag == real_tag &&
		    test_number(e) <= 6) {
			/* similar for reals */
			if (cmpflpt(no(arg1), no(arg2), (int) (test_number(e)))) {
				repbycont(e, 1, scope);
			} else {
				repbygo(e, pt(e), scope);
			}

			return 1;
		}

		/* end of constant expression evaluation */

		if (arg1->tag == val_tag || arg1->tag == real_tag ||
		    arg1->tag == null_tag) {
			/* constant argument always second */
			child(e) = arg2;
			next(arg2) = arg1;
			next(arg1) = e;
			arg1->last = true;
			arg2->last = false;
			arg2 = arg1;
			arg1 = child(e);
			nt = exchange_ntest[nt];
			settest_number(e, nt);
		}

		if (arg1->tag == chvar_tag && arg2->tag == chvar_tag &&
			sh(child(arg1))->tag == sh(child(arg2))->tag &&
		    shape_size(sh(child(arg1))) <= shape_size(sh(arg1)) &&
		    (optim & OPTIM_SHORTEN_OPS || shape_size(sh(arg1)) >= 16) &&
		    (is_signed(sh(child(arg1))) == is_signed(sh(arg1))))
		{
			exp ee;

#if TRANS_X86 || TRANS_HPPA
			/* optimise if both args are result of sign extension removal */
			if ((test_number(e) == f_equal ||
			     test_number(e) == f_not_equal) &&
			    sh(arg1)->tag == slonghd &&
			    child(arg1)->tag == cont_tag &&
			    child(arg2)->tag == cont_tag &&
			    shape_size(sh(child(arg1))) == 16 &&
			    child(child(arg1))->tag == name_tag &&
			    child(child(arg2))->tag == name_tag)
			{
				exp dec1 = child(child(child(arg1)));
				exp dec2 = child(child(child(arg2)));

				if (isse_opt(dec1) && isse_opt(dec2)) {
					child(e) = child(arg1);
					sh(child(arg1)) = slongsh;
					child(arg1)->last = false;
					next(child(arg1)) = child(arg2);
					sh(child(arg2)) = slongsh;
					child(arg2)->last = true;
					next(child(arg2)) = e;
					return 0;
				}
			}
#endif

			/*
			 * Arrange to do test in smallest size integers by removing
			 * chvar and altering shape of test args.
			 */
			ee = copyexp(e);
			child(ee) = child(arg1);
			next(child(arg1)) = child(arg2);
			child(arg1)->last = false;
			replace(e, hc(ee, next(child(ee))), scope);
			retcell(arg1);
			retcell(arg2);
			retcell(e);

			return 1;
		}

		if (endian == ENDIAN_LITTLE && has & HAS_BYTEOPS) {
			/* only for little enders with byte and short operations */
			if (arg2->tag == val_tag && !isbigval(arg2) && no(arg2) == 0 &&
			    arg1->tag == and_tag && test_number(e) >= 5) {
				/* e = test(val, and(a, b)) and test is == or != */
				exp r, t, q;

				if (next(child(arg1))->last) {
					if (child(arg1)->tag == chvar_tag &&
					    next(child(arg1))->tag == val_tag) {
						/* e = test(val, and(chvar(x), val)) */
						exp v = next(child(arg1));
						sh(v) = sh(child(child(arg1)));
						child(arg1) = child(child(arg1));
						child(arg1)->last = false;
						next(child(arg1)) = v;
					}

					r = getexp(f_top, NULL, 0, child(arg1), pt(e),
					           0, 0, testbit_tag);

					no(r) = no(e);
					settest_number(r, test_number(e));
					replace(e, hc(r, next(child(r))), scope);
					retcell(e);

					return 1;
				}

				for (t = child(arg1); !next(t)->last; t = next(t))
					;

				q = next(t);
				t->last = true;
				next(t) = arg1;

				r = getexp(f_top, NULL, 0, q, pt(e), 0, 0, testbit_tag);
				no(r) = no(e);
				settest_number(r, test_number(e));
				q->last = false;
				next(q) = arg1;
				arg1->last = true;
				next(arg1) = r;
				replace(e, r, scope);
				retcell(e);

				return 1;
			}

			/* use if little end machine */
			if (arg2->tag == val_tag && !isbigval(arg2) &&
			    ((arg1->tag == chvar_tag &&
			      sh(arg1)->tag > sh(child(arg1))->tag &&
			      is_signed(sh(arg1)) == is_signed(sh(child(arg1)))) ||
			     (arg1->tag == bitf_to_int_tag &&
			      child(arg1)->tag == cont_tag &&
			      (shape_size(sh(child(arg1))) == 8 ||
			       shape_size(sh(child(arg1))) == 16) &&
			      child(child(arg1))->tag == reff_tag &&
			      (no(child(child(arg1))) & 7) == 0))) {
				/* e = test(chvar(x), val) and chvar lengthens */
				n = no(arg2);

				switch (shape_size(sh(child(arg1)))) {
				case 8:
					if (is_signed(sh(child(arg1)))) {
						bl = (n >= -128) & (n <= 127);
						break;
					} else {
						bl = (n >= 0) & (n <= 255);
						break;
					}

				case 16:
					if (is_signed(sh(child(arg1)))) {
						bl = (n >= -32768) & (n <= 32767);
						break;
					} else {
						bl = (n >= 0) & (n <= 65536);
						break;
					}

				default:
					bl = 0;
					break;
				}

				if (bl) {
					exp ee = copyexp(e);
					child(ee) = child(arg1);
					next(child(arg1)) = arg2;
					child(arg1)->last = false;
					sh(arg2) = sh(child(arg1));
					replace(e, hc(ee, next(child(ee))), scope);
					retcell(arg1);
					retcell(e);
					return 1;
				}

				return 0;
			}

			if (arg2->tag == val_tag && !isbigval(arg2) && no(arg2) == 0 &&
			    test_number(e) >= 5 && arg1->tag == bitf_to_int_tag &&
			    shape_size(sh(arg1)) == 32 && child(arg1)->tag == cont_tag &&
			    child(child(arg1))->tag == reff_tag) {
				exp rf = child(child(arg1));

				if (al1(sh(child(rf))) >= 32) {
					int pos = no(rf) % 32;
					exp c = child(arg1);
					int nbits = shape_size(sh(c));
					exp r;

					no(rf) -= pos;
					sh(rf) = getshape(0, const_al32, const_al32,
					                  PTR_ALIGN, PTR_SZ, ptrhd);
					sh(c) = slongsh;

					if (no(rf) == 0) {
						sh(child(rf)) = sh(rf);
						child(c) = child(rf);
						setfather(c, child(c));
					}

					sh(arg2) = slongsh;
					no(arg2) = ~(- (1 << nbits)) << pos;

					r = getexp(f_top, NULL, 0, c, pt(e), 0, 0,
					           testbit_tag);
					no(r) = no(e);
					settest_number(r, test_number(e));
					c->last = false;
					next(c) = arg2;
					replace(e, hc(r, arg2), scope);
					retcell(e);

					return 1;
				}
			}

			if (arg1->tag == shr_tag && arg2->tag == val_tag &&
			    no(arg2) == 0 && nt >= 5) {
				exp arg11 = child(arg1);

				/* no of places shifted right */
				exp arg12 = next(arg11);

				if (arg11->tag == shl_tag && arg12->tag == val_tag) {
					exp arg111 = child(arg11);
					/* no places shifted left */
					exp arg112 = next(arg111);

					if (arg112->tag == val_tag && no(arg112) <= no(arg12)) {
						/* right shift */
						int n2 = no(arg12);
						/* left shift */
						int n12 = no(arg112);
						int sz = shape_size(sh(arg1));
						int mask = ((1 << (sz - n2)) - 1) << (n2 - n12);
						exp res = me_b3(sh(arg1), arg111,
						                me_shint(sh(arg1), mask), and_tag);
						res = hold_refactor(res);
						replace(arg1, res, res);

						return refactor(e, scope);
					}
				}
			}

			if (arg1->tag == chvar_tag && arg2->tag == val_tag &&
			    !isbigval(arg2) &&
			    shape_size(sh(arg1)) > shape_size(sh(child(arg1))) &&
			    child(arg1)->tag == cont_tag &&
			    (child(child(arg1))->tag != name_tag || !isvar(child(child(child(arg1))))))
			{
				exp q = child(arg1);
				shape sha = sh(q);
				int shsz = shape_size(sha);
				int n = no(arg2);

				if (n >= 0 &&
				    is_signed(sha) == is_signed(sh(arg1)) &&
				    ((shsz == 16 && n <= 32768) ||
				     (shsz == 8 && n <= 128)))
				{
					sh(arg2) = sha;
					child(e) = q;
					q->last = false;
					next(q) = arg2;
					retcell(arg1);
					return 1;
				}
			}
		}

		return seq_distr(e, scope);
	}

	/* eliminate dead code */
	case solve_tag: {
		exp t = child(e);
		exp q;
		int changed = 0;
		int looping;

		if (t->last) {
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, t);
			}
#endif
			replace(e, copy(t), scope);
			kill_exp(e, e);

			return 1;
		}

		if (t->tag == goto_tag && no(child(pt(t))) == 1) {
			exp lab = pt(t);

			for (q = next(t); q != e; q = next(q)) {
				if (q == lab) {
					break;
				}
			}

			if (q != e) {
				exp rep = copy(next(child(lab)));
#ifdef TDF_DIAG4
				/* note copy, in case original is removed ! */
#endif
				replace(t, rep, rep);
				kill_exp(t, t);
				t = rep;
			}
		}

		do {
			if (no(child(next(t))) == 0) {
				changed = 1;
				q = next(t);
				next(t) = next(q);

				if (q->last) {
					t->last = true;
				} else {
					t->last = false;
				}

#ifdef TDF_DIAG4
				if (diag != DIAG_NONE) {
					dg_dead_code(next(child(q)), t);
				}
#endif

				kill_exp(q, q);
				looping = !t->last;
			} else {
				looping = !next(t)->last;
				t = next(t);
			}
		} while (looping);

		if (child(e)->last) {
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(e, child(e));
			}
#endif
			replace(e, copy(child(e)), scope);
			kill_exp(e, e);
			return 1;
		}

		if (changed) {
			return 1;
		}

		return 0;
	}

	case case_tag:
		/*
		 * If we know the case argument select the right case branch and
		 * replace by goto. Knock on effect will be to eliminate dead code.
		 */
		if (child(e)->tag == val_tag) {
			exp n = child(e);
			int changed = 0;
			exp t = child(e);
			exp z;

			do {
				exp up;

				t = next(t);
				if (child(t) == NULL) {
					up = t;
				} else {
					up = child(t);
				}

				if (docmp_f((int) f_less_than_or_equal, t, n) &&
				    docmp_f((int) f_less_than_or_equal, n, up))
				{
					changed = 1;
					z = pt(t);
				}
				/*	  else
					  --no(child(pt(t)));
				 */
			} while (!t->last);

			if (!changed) {
				repbycont(e, 0, scope);
			} else {
				SET(z);
				repbygo(e, z, scope);
			}

			return 1;
		}

		return 0;

	case rep_tag:
	case apply_general_tag:
	case set_stack_limit_tag:
	case give_stack_limit_tag:
	case env_size_tag:
	case apply_tag:
	case res_tag:
	case goto_lv_tag:
	case assvol_tag:
	case local_free_all_tag:
	case local_free_tag:
	case last_local_tag:
	case long_jump_tag:
	case movecont_tag:
		return 0;

	case alloca_tag:
		if (child(e)->tag == chvar_tag &&
		    sh(child(child(e)))->tag == ulonghd) {
			replace(child(e), child(child(e)), child(e));
		}
		return 0;

	case nof_tag:
	case labst_tag:
		return 0;

	case concatnof_tag: {
		exp a1 = child(e);
		exp a2 = next(a1);
		exp r;
		nat n;

		if (a1->tag == string_tag && a2->tag == string_tag) {
			/* apply if args constant */
			char *s1 = nostr(child(e));
			char *s2 = nostr(next(child(e)));
			/* note NOT zero termination convention !! */
			int sz1, sz2, i;
			char *newstr;
			char *p2;
			shape newsh;

			sz1 = shape_size(sh(child(e)))      / 8;
			sz2 = shape_size(sh(next(child(e)))) / 8;

			if (sz1 + sz2 == 0) {
				newstr = NULL;
			} else {
				newstr = xcalloc((sz1 + sz2), sizeof(char));
			}

			p2 = &newstr[sz1];
			nat_issmall(n) = 1;
			natint(n) = sz1 + sz2;
			newsh = f_nof(n, scharsh);

			for (i = 0; i < sz1; ++i) {
				newstr[i] = s1[i];
			}

			for (i = 0; i < sz2; ++i) {
				p2[i] = s2[i];
			}

			r = getexp(newsh, NULL, 0, NULL, NULL, 0, 0, string_tag);
			nostr(r) = newstr;
			replace(e, r, scope);
			kill_exp(e, scope);

			return 1;
		}

		return 0;
	}

	case ncopies_tag:
	case ignorable_tag:
		return 0;

	case bfass_tag:
	case bfassvol_tag: {
		exp p = child(e);
		exp val = next(p);
		int bsz = shape_size(sh(val));
		int rsz;
		int rsh;
		int sg = is_signed(sh(val));
		int posmask;
		int negmask;
		int off = no(e);
		exp ref;
		exp cont;
		exp eshift;
		exp res;
		exp id;
		exp idval;
		shape ptr_sha;
		shape msh;
		int temp = off + bsz - 1;

		if (((off / 8) == (temp / 8)) && bsz <= 8
#if 0
		    (bsz == 8 &&
		     ((endian == ENDIAN_LITTLE && (off % 8 == 0)) ||
		      (endian == ENDIAN_BIG    && ((8 - (off % 8) - bsz) == 0))))
#endif
		   ) {
			rsz = 8;
			if (sg) {
				msh = scharsh;
			} else {
				msh = ucharsh;
			}
		} else if (((off / 16) == (temp / 16)) && bsz <= 16
#if 0
		           (bsz == 16 &&
		            ((endian == ENDIAN_LITTLE && (off % 16 == 0)) ||
		             (endian == ENDIAN_BIG    && ((16 - (off % 16) - bsz) == 0))))
#endif
		          ) {
			rsz = 16;
			if (sg) {
				msh = swordsh;
			} else {
				msh = uwordsh;
			}
		} else if ((off / 32) == (temp / 32)) {
			rsz = 32;
			if (sg) {
				msh = slongsh;
			} else {
				msh = ulongsh;
			}
		} else {
			rsz = 64;
			if (sg) {
				msh = s64sh;
			} else {
				msh = u64sh;
			}
		}

		ptr_sha = f_pointer(long_to_al(rsz));

		if ((off / rsz) != 0) {
			ref = me_u3(ptr_sha, p, reff_tag);
			no(ref) = (off / rsz) * rsz;
			ref = hold_refactor(ref);
		} else {
			ref = p;
		}

		id = me_startid(f_top, ref, 0);
		switch (endian) {
		case ENDIAN_LITTLE:
			rsh = off % rsz;
			break;
		case ENDIAN_BIG:
			rsh = rsz - (off % rsz) - bsz;
			break;
		}

		posmask = (bsz == 32) ? -1 : (1 << bsz) - 1;
		negmask = ~(posmask << rsh);
		cont = me_u3(msh, me_obtain(id), (e->tag == bfass_tag) ?
		             (unsigned char)cont_tag :
		             (unsigned char)contvol_tag);
		val = hold_refactor(me_u3(msh, val, chvar_tag));
		val = hold_refactor(me_b3(msh, val, me_shint(msh, posmask), and_tag));

		if (rsh != 0) {
			eshift = hold_refactor(me_b3(msh, val, me_shint(slongsh, rsh), shl_tag));
		} else {
			eshift = val;
			sh(eshift) = msh;
		}
		idval = me_startid(f_top, eshift, 0);

		if (rsz != bsz) {
			cont = me_b3(msh, cont, me_shint(msh, negmask), and_tag);
			cont = hold_refactor(me_b3(msh, cont, me_obtain(idval), or_tag));
		} else {
			kill_exp(cont, cont);
			cont = me_obtain(idval);
		}

		res = me_b3(f_top, me_obtain(id), cont,
		            (e->tag == bfass_tag) ? (unsigned char)ass_tag :
		            (unsigned char)assvol_tag);
		res = hold_refactor(me_complete_id(idval, res));
		replace(e, hold_refactor(me_complete_id(id, res)), scope);
		retcell(e);

		return 1;
	}

	default:
		return 0;
	}
}

