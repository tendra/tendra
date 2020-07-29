/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/externs.h>

#include <construct/exp.h>

#include <utility/bits.h>
#include <utility/max.h>

#include "tests.h"
#include "mach.h"
#include "where.h"
#include "translate.h"
#include "weights.h"

#define  AVERAGE_LOOP_LENGTH	10

/* Maximum and minimum weights */
#define  cant_use -1.0e10f

/* Numbers of available registers */
#define  wdno	16
#define  wano	16
#define  wfno	6
#define  wno	(wdno + wano + wfno)

typedef struct {
	float wts[wno];
	long d_used;
	long a_used;
	long f_used;
} weights;

typedef struct {
	weights wt;
	long bkpt;
} wp;

typedef struct elt {
	exp member;
	struct elt *next;
} explist ;

static weights
weightsv(exp e, explist *el);

/* Basic weights */
static weights zeros;

/* Current weights scale factor */
static float scale;

/*
 * Add two weight vectors
 */
static weights
add_weights(weights w1, weights w2)
{
	long i;
	weights r;
	float wa, wb;

	for (i = 0; i < wno; i++) {
		wa = w1.wts[i];
		wb = w2.wts[i];

		if (wa == cant_use || wb == cant_use) {
			r.wts[i] = cant_use;
		} else {
			r.wts[i] = wa + wb;
		}
	}

	r.d_used = MAX(w1.d_used, w2.d_used);
	r.a_used = MAX(w1.a_used, w2.a_used);
	r.f_used = MAX(w1.f_used, w2.f_used);

	return r;
}

/*
 * Initialize basic weights
 */
void
init_weights(void)
{
	long i;

	for (i = 0; i < wno; i++) {
		zeros.wts[i] = 0.0f;
	}

	zeros.d_used = -1;
	zeros.a_used = -1;
	zeros.f_used = -1;
}

/*
 * Mark a list of exps
 */
static void
markcall(explist *el, bitpattern b)
{
	explist *t;

	for (t = el; t != NULL; t = t->next) {
		props(t->member) |= b;
	}
}

/*
 * Work out weights for a declaration
 */
static wp
max_weights(long s, float locp, weights ws, int rtype)
{
	wp res;
	bool bkset = 0;
	long i, n;
	long sz = (s + 31) / 32, bk = 1;
	long q = 0;
	float *w, *pw;
	long used, total, offset;

	/* Find values for this register type */
	switch (rtype) {
	case Dreg:
		offset = 0;
		total  = wdno;
		used   = ws.d_used;
		break;

	case Areg:
		offset = wdno;
		total  = wano;
		used   = ws.a_used;
		break;

	case Freg:
		offset = wdno + wano;
		total  = wfno;
		used   = ws.f_used;
		break;

	default:
		error(ERR_FATAL, "Illegal register type");
	}

	w  = &ws.wts[offset];
	pw = &res.wt.wts[offset];
	n = used + sz + 1;
	if (n > total) {
		n = total;
	}

	/* Copy ws to res.wt */
	for (i = 0; i < wno; i++) {
		res.wt.wts[i] = ws.wts[i];
	}

	res.wt.d_used = ws.d_used;
	res.wt.a_used = ws.a_used;
	res.wt.f_used = ws.f_used;

	if (locp == cant_use) {
		for (i = 0; i < n; i++) {
			pw[i] = cant_use;
		}

		for (i = n; i < total; i++) {
			pw[i] = w[i];
		}

		switch (rtype) {
		case Dreg: res.wt.d_used = ws.d_used + sz; break;
		case Areg: res.wt.a_used = ws.a_used + sz; break;
		case Freg: res.wt.f_used = ws.f_used + sz; break;
		}

		bk = 0;
	} else {
		float loc = locp * (float) sz;
		q = -1;
		for (i = 0; i < total; i++) {
			if (w[i] == cant_use) {
				pw[i] = cant_use;
				q = i;
				continue;
			}

			if (i < sz + q) {
				pw[i] = w[i];
				continue;
			}

			if (i == sz + q) {
				if (loc >= w[i] && used <= q) {
					pw[i] = loc;
					bk = i + 1;
					bkset = 1;
				} else {
					pw[i] = w[i];
				}
			} else {
				float z = loc + w[i - sz];
				if (z >= w[i]) {
					pw[i] = z;
					if (!bkset) {
						bk = i + 1;
						bkset = 1;
					}
				} else {
					pw[i] = w[i];
				}
			}
		}
	}
	/* Set the breakpoint */
	res.bkpt = bk;
	return res;
}

/*
 * Work out weights for a list of exps
 */
static weights
add_wlist(exp re, explist *el)
{
	weights wl1, wl2;

	if (re == NULL) {
		return zeros;
	}

	wl1 = weightsv(re, el);

	while (!re->last) {
		re = bro(re);
		wl2 = weightsv(re, el);
		wl1 = add_weights(wl1, wl2);
	}

	return wl1;
}

/*
 * Is X an assignment?
 */
#define ass(X) (X->tag == ass_tag || X->tag == assvol_tag)

/*
 * Work out weights for e scaled by scale and set break points
 */
static weights
weightsv(exp e, explist *el)
{
	switch (e->tag) {
	case name_tag:
		if (!isglob(son(e))) {
			fno(son(e)) += scale;
		}

		/* Add value to the no field of the declaration */
		return zeros;

	case make_lv_tag:
		return zeros;

	case ident_tag: {
		wp p;
		long sz;
		shape sha;

		/* Starting point for pt list */
		exp t = pt(e);
		exp d = son(e);

		/* Add e to the list of exps */
		explist nel;
		nel.member = e;
		nel.next = el;

		while (isvar(e) && !isvis(e) && t != NULL) {
			/* Scan along pt list */
			if (!(t->last && bro(t)->tag == cont_tag) &&
			    !(bro(t)->last && ass(bro(bro(t)))))
				/* Make sure it will not go in register */
			{
				setvis(e);
			}
			t = pt(t);
		}

		if (d != NULL) {
			int sht;
			weights wdef, wbody;
			fno(e) = 0.0f;

			/* Work out weights for the body */
			wbody = weightsv(bro(d), &nel);

			/* Work out weights for the definition */
			if (d->tag == clear_tag) {
				wdef = zeros;
			} else {
				float old_scale = scale;
				if (d->tag == name_tag) {
					scale = fno(e);
				}
				wdef = weightsv(d, el);
				scale = old_scale;
			}

			/* Shape information */
			sha = sh(d);
			sz = shape_size(sha);
			sht = shtype(sha);

#if 0
			/* Correct producer bug */
			if (sha->tag == slonghd && d->tag == val_tag && no(d) == 0) {
				bool fix = 0;
				t = pt(e);
				while (t != NULL) {
					exp f = father(t);
					if (f->tag == cont_tag && sh(f)->tag == ptrhd) {
						fix = 1;
					}
					t = (t->last ? NULL : pt(t));
				}

				if (fix) {
					sh(d) = ptr_shape(sha);
					sht = Areg;
				}
			}
#endif

			if (isusereg(e)) {
				/* Work out breakpoint */
				p = max_weights(sz, cant_use, wbody, sht);
				no(e) = p.bkpt;
				if (no(e) == 13) {
					error(ERR_SERIOUS, "Bad breakpoint");
				}

				return add_weights(wdef, p.wt);
			}

			if (regable(e)) {
				/* Work out breakpoint */
				float loc = fno(e);
				if (d->tag == name_tag && isusereg(e)) {
					loc = (float)1.0;
				}

				p = max_weights(sz, loc, wbody, sht);
				no(e) = p.bkpt;

				return add_weights(wdef, p.wt);
			}

			no(e) = 16;
			return add_weights(wdef, wbody);
		}

		return zeros;
	}

	case labst_tag: {
		/* Add e to list of exps */
		explist nel;
		nel.member = e;
		nel.next = el;

		if (regable(e)) {
			weights wbody;
			float old_scale = scale;
			scale = fno(e);
			wbody = weightsv(bro(son(e)), &nel);
			scale = old_scale;
			return wbody;
		} else {
			return add_wlist(bro(son(e)), &nel);
		}
	}

	case rep_tag: {
		weights swl, bwl;
		swl = weightsv(son(e), el);
		bwl = weightsv(bro(son(e)), el);
		return add_weights(swl, bwl);
	}

	case compound_tag:
		return add_wlist(son(e), el);

	case untidy_return_tag:
	case case_tag:
	case res_tag:
		return weightsv(son(e), el);

	case apply_general_tag:
	case apply_tag:
	case round_tag:
	case float_tag:
		markcall(el, (bitpattern)0x80);
		return add_wlist(son(e), el);

	case ass_tag:
	case assvol_tag: {
		weights swl, bwl;
		swl = weightsv(son(e), el);
		bwl = weightsv(bro(son(e)), el);
		return add_weights(swl, bwl);
	}

	case general_proc_tag:
	case proc_tag:
		weightsv(son(e), NULL);
		return zeros;

	case env_offset_tag:
		return zeros;

	case val_tag:
	case real_tag:
		return zeros;

	case test_tag: {
		weights twl;
		twl = add_wlist(son(e), el);
		/* scale = scale * (((float) 1.0) - fno(e)); */
		return twl;
	}

	default:
		return add_wlist(son(e), el);
	}
}

/*
 * Compute weights
 */
void
comp_weights(exp e)
{
	scale = 1.0f;
	weightsv(e, NULL);
}

