/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The main procedure here is weightsv which determines the allocation
 * of s regs. It considers which of those tags not already allocated
 * to a t reg by scan, are best put in an s register. The same conditions
 * as for t regs apply as to the suitability of the tags for registers.
 *
 * Weights estimates the usage of each tag and hence the amount that would
 * be saved if it were held in an s reg. Thus it computes break points for
 * register allocation for later use by reg_alloc.
 *
 * The type weights consists of two arrays of integers. In the first
 * array each integer corresponds to a fixpnt reg and the second arrays'
 * integers correspond to floating point regs.
 *
 * At the end of a call of weights on an ident exp the props field
 * of the ident may still contain inreg_bits or infreg_bits, set by scan, to
 * indicate that a t reg should be used. Otherwise number of ident is set up to
 * represent the break point for allocation. A similar process occurs for
 * proc parameters which have the break value in the forweights field
 * of the parapair of the corresponding procrec. This value has three
 * meanings:
 *
 *  1) The ident (or parameter) defines a fixpnt value and number of ident
 *     (forweights of parpair) is an integer brk with the interpretation that
 *     if there are at least brk fixpt s registers unallocated at this point
 *     then one will be used for this tag (parameter).
 *  2) As 1 but for floating point values.
 *  3) number of ident = 100 in which case allocate value on the
 *     stack, (this is obviously always available for parameters).
 */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/exp.h>

#include <refactor/const.h>

#include "procrec.h"
#include "bits.h"
#include "regable.h"
#include "special.h"
#include "weights.h"

static weights
weightsv(double scale, exp e);

static weights zeroweights;

/*
 * NB scale, throughout, should be a float but mips cc V2.10 compiles calls and
 * proc body inconsistently!
 */

/* sum of weights */
static weights
add_weights(weights *w1, weights *w2)
{
	weights r;
	long i;

	for (i = 0; i < wfixno; ++i) {
		r.fix[i] = w1->fix[i] + w2->fix[i];
	}

	for (i = 0; i < wfloatno; ++i) {
		r.floating[i] = w1->floating[i] + w2->floating[i];
	}

	return r;
}

/*
 * loc is the usage count of a tag, ws is the weights computed for the scope
 * of the tag and fix distinguishes between fix and float.
 *
 * This computes the weights for the declaration and a break point
 * for register allocation which gives the number of available regs for
 * which it is worthwhile to allocate this tag into a reg ("regged").
 * This proc is the source of all non-zero weights.
 *
 * NB loc may be negative since using a s-reg will involve a dump and restore
 */
static wp
max_weights(double loc, weights *ws, bool fix)
{
	long bk = wfixno + 1;
	long i;
	wp res;

	float *w = ws->fix;
	/* w[i] = greatest usage of (i+1) inner fixed tags  */

	float *pw = &res.wp_weights.fix[0];

	if (fix) {
		for (i = 0; i < wfixno; ++i) {
			if (i == 0) {
				if (loc > w[i]) {
					/* this tag has higher usage than any inner one ... */
					pw[i] = loc;
					bk = i;		/* ... so it's regged in pref to others */
				} else {
					pw[i] = w[i];
				}
			} else {
				if ((loc + w[i - 1]) > w[i]) {

					/*
					 * this tag and i inner ones have higher usage than any other (i+1)
					 * inner ones ...
					 */
					pw[i] = loc + w[i - 1];
					if (i < bk) {
						bk = i;
					}

					/*
					 * ... so it and i inner ones are regged in preference to any other
					 * (i+1) inner ones
					 */
				} else {
					pw[i] = w[i];
				}
			}
		}

		res.fix_break = bk;
	} else {
		for (i = 0; i < wfixno; ++i) {
			pw[i] = w[i];
		}
	}

#if NO_SREG
	res.fix_break = wfixno + 1;
#else
	res.fix_break = bk;
#endif

	bk = wfloatno + 1;
	w = ws->floating;
	pw = &res.wp_weights.floating[0];

	if (!fix) {
		/* same algorithm for float regs as fixed regs */
		for (i = 0; i < wfloatno; ++i) {
			if (i == 0) {
				if (loc > w[i]) {
					pw[i] = loc;
					bk = i;
				} else {
					pw[i] = w[i];
				}
			} else {
				if ((loc + w[i - 1]) > w[i]) {
					pw[i] = loc + w[i - 1];
					if (i < bk) {
						bk = i;
					}
				} else {
					pw[i] = w[i];
				}
			}
		}
	} else {
		for (i = 0; i < wfloatno; ++i) {
			pw[i] = w[i];
		}
	}

	res.float_break = bk;
	return res;
}

/* sum of  weights of list re */
static weights
add_wlist(double scale, exp re)
{
	weights w, w1;
	exp r = re;

	if (r == NULL) {
		return zeroweights;
	}

	if (r->last) {
		return weightsv(scale, r);
	}

	w = weightsv(scale, r);
	do {
		r = next(r);
		w1 = weightsv(scale, r);
		w = add_weights(&w, &w1);
	} while (!r->last);

	return w;
}

/*
 * This procedure estimates the usage of tags and parameters to help
 * determine whether they can advantageously be placed in s registers.
 *
 * The parameter scale allows more importance to be placed on usage
 * inside 'for' loops for example. The procedure reg_alloc in reg_alloc.c
 * finally determines the actual choice of s reg and recodes the number
 * field of an ident.
 */
static weights
weightsv(double scale, exp e)
{
	unsigned char n;

tailrecurse:

	n = e->tag;

	switch (n) {
	case name_tag: {
		exp s = child(e);

		if (s->tag == ident_tag && !isglob(s)) {
			if (is_floating(sh(e)->tag) && sh(e)->tag != shrealhd) {
				fno(s) += scale * 2.0;
			} else {
				fno(s) += scale;
			}
		}

		/* usage of tag stored in number of child of load_name (decl) */
		return zeroweights;
	}

	case ident_tag: {
		weights wdef;
		bool wdef_set;
		weights wbody;
		long noe;

		if (child(e) == NULL) {
			return zeroweights;
		}

		noe = no(e); /* set by scan */

#if 1
		if (isparam(e)) {
			/* initialising is a use */
			fno(e) = scale;
			wdef_set = 0;
		} else
#endif
			if (child(e)->tag == clear_tag || props(e) & defer_bit) {
				wdef = zeroweights;
				fno(e) = 0.0;
				wdef_set = 0;
			} else {
				/* maybe needs a store to initialise */
				if (is_floating(sh(child(e))->tag) && sh(child(e))->tag != shrealhd) {
					fno(e) = scale * 2.0;
				} else {
					fno(e) = scale;
				}
				wdef = weightsv(scale, child(e));
				wdef_set = 1;
			}
		/* weights for initialisation of dec */

		wbody = weightsv(scale, next(child(e)));
		/* weights of body of scan */

		if (props(e) & defer_bit) {
			/* declaration will be treated transparently
			 * in code production */
			exp t = child(e);
			exp s;

			if ((t->tag == val_tag) || (t->tag == real_tag)) { /* +++ string_tag too */
				return wbody;
			}

			while (t->tag != name_tag) {
				t = child(t);
			}

			s = child(t);
			if (s->tag == ident_tag && !isglob(t)) {
				fno(s) += fno(e);
			}
			/* usage of tag stored in number of child of load_name (decl) */

			return wbody;
		}
		/* end deferred */

		if ((props(e) & inreg_bits) == 0 && fixregable(e)) {
			wp p;

			p = max_weights(fno(e) - 2.0 * scale, &wbody, 1);

			no(e) = p.fix_break;
			if (wdef_set) {
				return add_weights(&wdef, &p.wp_weights);
			} else {
				return p.wp_weights;
			}
		} else if ((props(e) & infreg_bits) == 0 && floatregable(e)) {
			wp p;

			p = max_weights(fno(e) - 3.0 * scale, &wbody, 0);

			/*
			 * usage decreased by 3 because of dump and restore of double s-reg
			 */
			no(e) = p.float_break /* was noe */ ;
			if (wdef_set) {
				return add_weights(&wdef, &p.wp_weights);
			} else {
				return p.wp_weights;
			}
		} else {
			no(e) = noe;

			if (wdef_set) {
				return add_weights(&wdef, &wbody);
			} else {
				return wbody;
			}
		}
	}

	case rep_tag:
		e = next(child(e));
		goto tailrecurse;

	case case_tag:
		e = child(e);
		goto tailrecurse;

	case labst_tag:
		scale = fno(e) * scale;
		e = next(child(e));
		goto tailrecurse;

	case val_tag:
		return zeroweights;

	case ncopies_tag:
		scale = no(e) * scale;
		e = child(e);
		goto tailrecurse;

	case env_offset_tag:
	case general_env_offset_tag:
		return zeroweights;

	default:
		if (child(e) == NULL) {
			return zeroweights;
		}

		if (child(e)->last) {
			e = child(e);
			goto tailrecurse;
		}

		return add_wlist(scale, child(e));
	}
}

