/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>
#include <reader/basicread.h>
#include <reader/table_fns.h>

#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/exp.h>

#include <flpt/flpt.h>

#include <main/flags.h>

#include <refactor/refactor.h>

#ifdef TDF_DIAG4
#include <reader/readglob.h>
#include <diag4/dg_aux.h>
#endif

/* All variables initialised */

int crt_labno = 0;	/* init by init_exp */
/* the list of unused returned cells */
exp freelist;	/* init by init_exp */
/* the number of unused cells in the block */
int exps_left;	/* init by init_exp */

/* the next free pointer in the block which is used if the freelist is empty */
static exp next_exp_ptr;	/* no need to init */

/*
 * The types used to record a list of blocks for reuse,
 * if separate_units is set
 */
typedef struct expalloc_cell_t {
	struct expalloc_cell_t *tl;
	exp hd;
} expalloc_cell;

static expalloc_cell *alloc_list     = NULL; /* good init for the whole run */
static expalloc_cell *alloc_freelist = NULL; /* good init for the whole run */

static char ic_buff[21];	/* no init needed */

static int current_alloc_size = 20000;

void altered(exp, exp);

exp
next_exp(void)
{
	exp res;

	if (freelist != NULL) {
		/* first try to allocate fron the freelist */
		res = freelist;
		freelist = son(freelist);
		return res;
	}

	/* if the freelist is empty we allocate from a block of exps */
	if (exps_left == 0) {
		/* if the block is empty we must allocate another */
		if (alloc_freelist) {
			/*
			 * If there is anything in this list of blocks we can reuse it and
			 * we do not need to calloc
			 */
			exps_left = current_alloc_size;
			next_exp_ptr   = alloc_freelist->hd;
			alloc_freelist = alloc_freelist->tl;
		} else {
			/* otherwise we must calloc a new block */
			exps_left = current_alloc_size;
			next_exp_ptr = xcalloc(exps_left, sizeof(struct exp_t));
			{
				/*
				 * And if we are after the start of tagdefs we put the block on to
				 * alloc_list so that it can be reused for the next unit
				 */
				expalloc_cell *temp = xmalloc(sizeof(expalloc_cell));
				temp->tl = alloc_list;
				temp->hd = next_exp_ptr;
				alloc_list = temp;
			}
		}
	}

	exps_left--;
	res = next_exp_ptr++;
	return res;
}

void
set_large_alloc(void)
{
	/* called at the start of tagdefs */
	alloc_freelist = alloc_list;
	freelist = NULL;
	exps_left = 0;
}

/*
 * Create a new exp
 */
exp
getexp(shape s, exp b, int l, exp sn, exp px, prop pr, int n, unsigned char tag)
{
	exp res;

	res = next_exp();
	sh(res)  = s;
	bro(res) = b;

	if (l) {
		res->last = true;
	} else {
		res->last = false;
	}

	son(res)    = sn;
	pt(res)     = px;
	props(res)  = pr;
	no(res)     = n;
	res->tag    = tag;
	parked(res) = 0;
#ifdef TDF_DIAG4
	dgf(res)    = NULL;
#endif

	return res;
}

exp
copyexp(exp e)
{
	exp res;

	res  = next_exp();
	*res = *e;

	return res;
}

/*
 * Makes a new shape
 */
exp
getshape(int l, alignment sn, alignment px, alignment pr, int n,
         unsigned char tag)
{
	exp res;

	res = next_exp();
	if (l) {
		res->last = true;
	} else {
		res->last = false;
	}

	res->son.ald = sn;
	res->pt.ald  = px;
	res->bro.ald = pr;

	no(res)  = n;
	res->tag = tag;

	return res;
}

/*
 * Return an exp cell to the freelist
 */
void
retcell(exp e)
{
	son(e) = freelist;
	freelist = (e);
}

/*
 * true if part is inside whole
 */
int
internal_to(exp whole, exp part)
{
	int f = 1;
	exp q;

	q = part;
	while (q != whole && q != NULL &&
	       !(q->tag == ident_tag && isglob(q))) {
		f = (int)(q->last);
		q = bro(q);
	}

	/* ascend from part until we reach either whole or top of tree */
	return f && q == whole;
}

static void kill_el(exp e, exp scope);

/*
 * Kill an exp, return it and its components to the freelist, if necessary
 * remove uses of tags and labels, and propagate changes to identity and
 * variable declarations and to labels but not outside scope.
 */
void
kill_exp(exp e, exp scope)
{
	unsigned char n;

	if (e == NULL) {
		return;
	}

	n = e->tag;

	if (n == name_tag) {
		exp q = son(e);

#ifdef TDF_DIAG4
		if (!isdiaginfo(e)) {
			--no(son(e));		/* decrease usage count */
		}
#else
		--no(son(e));		/* decrease usage count */
#endif

		while (pt(q) != e) {
			q = pt(q);
		}

		pt(q) = pt(e);		/* remove from usage list */
		if (no(son(e)) == 0 && son(son(e)) != NULL &&
			bro(son(son(e))) != NULL &&
			(scope == NULL || internal_to(scope, son(e)))) {
			IGNORE refactor(son(e), scope);
		}

		/* check the declaration if now no use */
		retcell(e);
		return;
	}

	if (n == solve_tag) {
		int looping;

		if (!son(e)->last) {
			exp t;

			t = bro(son(e));
			do {
				no(son(t)) = 0;
				looping = !t->last;
				t = bro(t);
			} while (looping);
		}

		if (pt(e) != NULL) {
			son(pt(e)) = NULL;
		}

		kill_el(son(e), scope);
		retcell(e);
		return;
	}

	if (n == ident_tag) {
		no(e)++;
		kill_el(son(e), scope);

#ifdef TDF_DIAG4
		if (diag != DIAG_NONE && pt(e)) {	/* allow diags to hold on to id */
			diag_kill_id(e);
		} else
#endif
		retcell(e);
		return;
	}

	if (n == labst_tag) {
		no(e)++;
		proc_label_count--;
		kill_el(bro(son(e)), scope);
		retcell(son(e));
		retcell(e);
		return;
	}

	if (n == case_tag) {
		exp b, nextb;

		for (b = bro(son(e)); b != NULL; b = nextb) {
			int l;

			nextb = bro(b);
			l     = b->last;

			no(son(pt(b)))--;
			if (son(b) != NULL) {
				retcell(son(b));
			}

			retcell(b);
			if (l) {
				break;
			}
		}

		kill_exp(son(e), scope);
		retcell(e);
		return;
	}

	if (n == cond_tag) {
		no(son(bro(son(e)))) = 0;
		kill_el(son(e), scope);
		retcell(e);
		return;
	}

	if (n == rep_tag) {
		if (pt(e) != NULL) {
			son(pt(e)) = NULL;
		}

		no(son(bro(son(e)))) = 0;
		kill_el(son(e), scope);
		retcell(e);
		return;
	}

	if (n == real_tag || (n == val_tag && isbigval(e))) {
		flpt_ret(no(e));
		retcell(e);
		return;
	}

	if (n == val_tag) {
		retcell(e);
		return;
	}

	if (n == env_offset_tag || n == string_tag || n == general_env_offset_tag) {
		retcell(e);
		return;
	}

	{
		exp p;

		p = pt(e);
		if (p != NULL && (props(son(p)) & 1) == 0) {
			/* decrease label usage count */
			no(son(p))--;
			if (no(son(p)) == 0 && !is_loaded_lv(p) && bro(son(p)) != NULL &&
				(scope == NULL || internal_to(scope, p))) {
				/* process if now no use of label and not doing deadvar */
				altered (p, scope);
			}
		}

		kill_el(son(e), scope);
		retcell(e);
		return;
	}
}

/*
 * Kill the arguments of a construction.
 */
static void
kill_el (exp e, exp scope)
{
	int l;
	exp next;

	if (e == NULL) {
		return;
	}

	do {
		l = (int)(e->last);
		next = bro(e);
		kill_exp(e, scope);
		e = next;
	} while (!l && e != NULL);
}

/*
 * Return the shape delivered by a conditional (or similar construct)
 * which delivers an a from one branch and a b from the other.
 */
shape
lub_shape(shape a, shape b)
{
	int asz = shape_size(a);
	int bsz = shape_size(b);

	if (a->tag == bothd) {
		return b;
	}

	if (b->tag == bothd) {
		return a;
	}

	if (asz == bsz && shape_align(a) == shape_align(b)) {
		return a;
	}

	return f_top;
}

/*
 * true if the shapes are equal
 */
int
eq_shape(shape a, shape b)
{
	if (a->tag != b->tag) {
		return 0;
	}

	if (shape_size(a) != shape_size(b) || is_signed(a) != is_signed(b) ||
	    shape_align(a) != shape_align(b) || al1(a) != al1(b)) {
		return 0;
	}

	if (a->tag == nofhd) {
		return 1;
	} else {
		return al2(a) == al2(b);
	}
}

/*
 * Source of numbers for local labels.
 */
int
next_lab(void)
{
	return crt_labno++;
}

char *
intchars(int n)
{
	char *ind;
	int r, d;

	ind = &ic_buff[19];
	ic_buff[20] = 0;
	d = (n < 0) ? -n : n;

	do {
		r = d % 10;
		d = d / 10;
		*ind = (char) (r + 48); /* CAST:jmf: must be in 48:57 */
		ind--;
	} while (d != 0);

	if (n < 0) {
		*ind = '-';
		ind--;
	}

	return ind + 1;
}

void
case_item(exp i)
{
	exp l = global_case;
	exp t = l;
	int go = 1;
	exp newhigh = (son(i) == NULL) ? i : son(i);
	exp thigh;
	exp nlow, nhigh;

	while (go && bro(t) != NULL) {
		exp j = bro(t);
		exp  highj = (son(j) == NULL) ? j : son(j);
		if (docmp_f((int)f_greater_than, i, highj)) {
			t = bro(t);
		} else {
			go = 0;
		}
	}

	if (t != l) {
		thigh = (son(t) == NULL) ? t : son(t);
	} else {
		SET(thigh);
	}

	if (bro(t) != NULL) {
		nlow = bro(t);
		nhigh = (son(bro(t)) == NULL) ? nlow : son(bro(t));
	} else {
		SET(nlow);
		SET(nhigh);
	}

	if (t != l && docmp_f((int)f_less_than_or_equal, i, thigh)) {
		error(ERR_INTERNAL, "case tags overlap");
	}
	if (bro(t) != NULL &&
	    docmp_f((int)f_greater_than_or_equal, newhigh, nlow)) {
		error(ERR_INTERNAL, "case tags overlap");
	}

	if (isbigval(i) || isbigval(newhigh)) {
		bro(i) = bro(t);
		bro(t) = i;
		return;
	}

	if (t != l && (no(i) - 1) == no(thigh) && pt(i) == pt(t)) {
		if (bro(t) != NULL && (no(newhigh) + 1) == no(nlow) &&
		    pt(i) == pt(bro(t))) {

			if (son(bro(t)) != NULL) {
				if (son(t) != NULL) {
					retcell(son(t));
				}
				son(t) = son(bro(t));
				bro(t) = bro(bro(t));
				return;
			}

			if (son(t) != NULL) {
				no(son(t)) = no(nhigh);
				bro(t) = bro(bro(t));
				return;
			}

			setson(t, getexp(slongsh, NULL, 1, NULL, NULL, 0, no(nhigh), 0));
			bro(t) = bro(bro(t));
			return;
		}

		if (son(t) != NULL) {
			no(son(t)) = no(newhigh);
			return;
		}

		setson(t, getexp(slongsh, NULL, 1, NULL, NULL, 0, no(newhigh), 0));
		return;
	}

	if (bro(t) != NULL && (no(newhigh) + 1) == no(nlow) &&
	    pt(i) == pt(bro(t))) {

		if (son(bro(t)) != NULL) {
			no(bro(t)) = no(i);
			return;
		}

		if (son(i) != NULL) {
			no(son(i)) = no(nhigh);
			bro(i) = bro(bro(t));
			bro(t) = i;
			return;
		}

		son(i) = bro(t);
		bro(i) = bro(bro(t));
		bro(t) = i;
		return;
	}

	bro(i) = bro(t);
	bro(t) = i;
}

/*
 * scan_solve is part of the process of reading a solve construction.
 * It scans the exp e, to increment the count of labels used by e.
 */
static void
scan_solve(exp e)
{
	unsigned char n = e->tag;
	switch (n) {
	case name_tag:
	case make_lv_tag:
	case env_offset_tag:
	case general_env_offset_tag:
		return;

	case clear_tag:
		return;

	case ident_tag:
		scan_solve(son(e));
		scan_solve(bro(son(e)));
		return;

	case case_tag: {
		exp t;

		for (t = son(e); !t->last; t = bro(t)) {
			exp s = son(pt(bro(t)));
			if (isvar(s)) {
				++no(s);
			}
		}

		scan_solve(son(e));
		return;
	}
	default:
		if (pt(e) != NULL) {
			exp s = son(pt(e));
			if (isvar(s)) {
				++no(s);
			}
		}

		if (son(e) != NULL) {
			exp t;

			for (t = son(e); scan_solve(t), !t->last; t = bro(t))
				;
		}

		return;
	}
}

/*
 * clean_labelled processes a labelled statement after it has been read.
 * It places the labelled statements in a good order.
 */
exp
clean_labelled(exp main, label_list placelabs)
{
	int i, crt_no;
	int go = 1;
	shape s;
	exp r, q;
	int n = placelabs.number;
	int *ord;	/* records the order in which the statemnts are to be placed */
	int ord_no;

	for (i = 0; i < n; ++i) {	/* set up the labels */
		exp l = get_lab(placelabs.elems[i]);
		exp t = son(l);
		no(t) = is_loaded_lv(l);
		setcrtsolve (t);		/* defined in expmacs = props(t) = 1 */
	}

	crt_no = 0;
	if (n == 0) {
		ord = NULL;
	} else {
		ord = xcalloc(n, sizeof(int));
	}

	ord_no = 0;
	scan_solve (main);	/* mark the labels used by the initiator */

	while (go) {
		/* continue as long as we have added a statement */
		go = 0;
		for (i = 0; i < n; ++i) {
			/* look for unprocessed but used sts */
			int j = ((i + crt_no) % n);
			exp t = get_lab(placelabs.elems[j]);

			if ((props(son(t)) & 8) == 0 && no(son(t)) != 0) {
				/* we have found an unprocessed but used statement */
				go = 1;
				props(son(t)) = 5;
				scan_solve (t);		/* now scan it to mark the things it uses */
				props(son(t)) = (prop)((props(son(t)) & 0xfb) | 8);
				ord[ord_no++] = j;
			}
		}
	}

	s = sh(main);
	for (i = 0; i < n; ++i) {
		exp lab = get_lab(placelabs.elems[i]);
		exp t = son(lab);
		if ((props(t) & 8) != 8) {
			/* remove unwanted statements */
			kill_exp (bro(t), bro(t));
		} else {
			/* form the result shape of the whole */
			s = lub_shape(s, sh(lab));
		}
	}

	r = getexp(s, NULL, 0, main, crt_repeat, 0, 0, solve_tag);
	q = main;
	for (i = 0; i < ord_no; ++i) {
		/* set up the solve with the statements in the order specified by ord */
		q->last = false;
		bro(q) = get_lab(placelabs.elems[ord[i]]);
		q = bro(q);
		props(son(q)) = (prop)(props(son(q)) & 0xfe);
	}

	son(crt_repeat) = r;
	crt_repeat = bro(crt_repeat);
	setfather(r, q);
	return r;
}

/*
 * Find the (unique) downward reference to e
 */
exp *
refto(exp f, exp e)
{
	exp *x;

	for (x = &son(f); *x != e; x = &bro(*x))
		;

	return x;
}

/*
 * Find the father of e
 */
exp
father(exp e)
{
	if (e == NULL) {
		return e;
	}

	while (!e->last) {
		e = bro(e);
	}

	return bro(e);
}

/*
 * Auxiliary routine for altered, looks up in the tree n levels, checking
 */
static void
altaux(exp e, int n, exp scope)
{
	exp f;

	if (bro(e) == NULL || e == scope || (e->tag == ident_tag && isglob(e))) {
		/* ignore if top of tree */
		return;
	}

	f = father(e);
	if (f == NULL || bro(f) == NULL || (f->tag == ident_tag && isglob(f))) {
		/* ignore if top of tree */
		return;
	}

	if (f->tag == 0) {
		altaux(f, n, scope);
		return;
	}

	if (!refactor(f, scope) && n > 1) {
		/* do check until n is exhausted */
		altaux(f, n - 1, scope);
		return;
	}
}

/*
 * e has been altered. see if any exp higher up the tree can now recognise an
 * optimisation (using check)
 */
void
altered (exp e, exp scope)
{
	altaux(e, 1, scope);
}

/*
 * Replace old by e, and (if not doing deadvar) check whether any consequential
 * optimisations are possible.
 */
void
replace(exp old, exp e, exp scope)
{
	exp f = father(old);
	exp *ref;

	ref = refto(f, old);
	if ((*ref)->last) {
		e->last = true;
	} else {
		e->last = false;
	}

	bro(e) = bro(*ref);
	*ref = e;

	if (scope == old) {
		return;
	}

	altered(e, scope);
}

/*
 * Copy a labelled statement and put links into pt so that copies of uses of
 * the original can refer to the copy.
 */
static void
copy_labst(exp e)
{
	exp t = copyexp(e);
	exp d = copyexp(son(e));
	setcopy(e);
	no(t) = 0;
	no(d) = 0;
	pt(d) = pt(e);
	pt(t) = NULL;
	pt(e) = t;
	son(t) = d;
	proc_label_count++;
}

/*
 * End the copy of a labelled statement and restore the original state.
 */
static exp
undo_labst(exp e)
{
	exp r = pt(e);
	pt(e) = pt(son(r));
	clearcopy(e);
	return r;
}

exp copy_res(exp, exp, exp);
exp copy(exp);

/*
 * Used to copy cond, repeat and solve so that copies of references to the
 * labelled statements can refer to the copies of the labelled statements.
 */
static
exp copy_cpd(exp e, exp new_record, exp var, exp lab)
{
	exp t = copyexp(e);
	exp q;
	exp j, c, s, n, k;

	if (new_record != NULL) {
		/* record the construction */
		pt(t) = new_record;
		son(new_record) = t;
	}

	/* copy the labelled statements */
	q = bro(son(e));
	copy_labst(q);
	while (!q->last) {
		q = bro(q);
		copy_labst(q);
	}

	/* copy the bodies of the labelled statments */
	q = bro(son(e));
	while (j = copy_res(bro(son(q)), var, lab), c = pt(q), bro(son(c)) = j,
	       bro(j) = c, j->last = true, !q->last) {
		q = bro(q);
	}

	/* copy the lead statement */
	s = copy_res(son(e), var, lab);
	son(t) = s;
	s->last = false;
	q = bro(son(e));
	n = s;

	/* restore the labelled statements */
	while (k = undo_labst(q), bro(n) = k, n->last = false, !q->last) {
		q = bro(q);
		n = bro(n);
	}

	n = bro(n);
	n->last = true;
	bro(n) = t;
	return t;
}

/*
 * Copy copies e and all its sub-cells recursively, amending usage counts
 * as necessary. It sets up identifier usage lists for the declarations
 * which it copies.
 */
exp
copy_res(exp e, exp var, exp lab)
{
	unsigned char n;

	if (e == NULL) {
		return e;
#ifdef TDF_DIAG4
	} else if (dgf(e) != NULL) {
		return copy_res_diag(e, dgf(e), var, lab);
#endif
	}

	n = e->tag;

	if (n == ident_tag) {
		exp t = copyexp(e);
		exp x = pt(e);		/* remember the usage list */
		exp s, bs;
		setcopy (e);		/* mark e as being copied */
		no(t) = 0;		/* clear the usage count */
		pt(e) = t;		/* record the copy in the pt field of the
			   original */
		pt(t) = NULL;		/* set the new usage list to empty */
		s = copy_res(son(e), var, lab);	/* copy the definition */
		bs = copy_res(bro(son(e)), var, lab);/* copy the body */

		son(t) = s;
		bro(s) = bs;
		bro(bs) = t;
		s->last = false;
		bs->last = true;
		pt(e) = x;		/* reset the remembered usage list */
		clearcopy (e);		/* remove the copying flag */

		if (n == ident_tag) {
			/* in case bro(son(t)) is a tuple */
			sh (t) = sh(bro(son(t)));
		}

		return t;
	}

	if (n == name_tag) {
		/* see if the corresponding declaration is being copied and pick up
		   the correct usage list */
		exp tp = (copying(son(e)) ? pt(son(e)) : son(e));
		exp r = copyexp(e);
		son(r) = tp;		/* add this use onto the correct usage
			   list */
		pt(r) = pt(tp);
		pt(tp) = r;
#ifdef TDF_DIAG4
		if (!isdiaginfo(r))
#endif
		{
			++no(tp);		/* increment the correct usage count */
			if (isglob(tp)) {
				proc_externs = 1;
			}
		}

		return r;
	}

	if (n == env_offset_tag || n == general_env_offset_tag) {
		/*
		 * See if the corresponding declaration is
		 * being copied and pick up the correct usage list
		 */
		exp tp = (copying(son(e)) ? pt(son(e)) : son(e));
		exp r = copyexp(e);
		son(r) = tp;		/* add this use onto the correct usage list */
		return r;
	}

	if (n == cond_tag) {
		exp z = copy_cpd(e, NULL, var, lab);
		return z;
	}

	if (n == rep_tag || n == solve_tag) {
		/* we have to update the repeat records */
		exp record = pt(e);
		exp z;

		if (record != NULL) {
			exp senior = bro(record);
			exp new_record = copyexp(record);

			if (senior == NULL) {
				/* XX008 */
				senior = crt_repeat;
				bro(new_record) = senior;
			}

			set_copying_solve (record);/* mark as being copied */
			pt(record) = new_record;

			if (senior != NULL) {
				/* update repeat records */
				if ((props(senior) & 1) == 1) {
					bro(new_record) = pt(senior);
				} else {
					++no(senior);
				}
			}

			z = copy_cpd(e, new_record, var, lab);
			clear_copying_solve(record);	/* unmark copying flag */
		} else {
			z = copy_cpd(e, NULL, var, lab);
		}
		return z;
	}

	if (n == case_tag) {
		exp t = copy_res(son(e), var, lab);
		exp z = copyexp(e);
		exp q = son(e);
		exp p = t;
		exp labloc, tp;

		son(z) = t;
		while (!q->last) {
			setbro(p, copyexp(bro(q)));
			if (son(bro(q)) != NULL) {
				setson(bro(p), copyexp(son(bro(q))));
			}
			labloc = pt(bro(p));
			tp = (copying(labloc)) ? pt(labloc) : labloc;
			pt(bro(p)) = tp;
			no(son(tp)) ++;
			p = bro(p);
			q = bro(q);
		}

		bro(p) = z;
		if (PIC_code) {
			proc_externs = 1;
		}

		return z;
	}

	if (n == real_tag || (n == val_tag && isbigval(e))) {
		exp z = copyexp(e);
		flpt f = new_flpt();
		flt_copy(flptnos[no(e)], &flptnos[f]);
		no(z) = f;

		if (PIC_code) {
			proc_externs = 1;
		}

		return z;
	}

	if (n == string_tag) {
		exp r = copyexp(e);

		if (PIC_code) {
			proc_externs = 1;
		}

		return r;
	}

	if (n == res_tag) {
		if (lab != NULL) {
			exp go = getexp(f_bottom, NULL, 0, NULL, lab, 0, 0, goto_tag);
			no(son(lab)) ++;

			if (son(e)->tag == clear_tag) {
#ifdef TDF_DIAG4
				if (extra_diags) {
					diag_inline_result(go);
				}
#endif
				return go;
			} else if (var == NULL) {
				exp_list el;
				exp c = copy(son(e));
				exp s;
				el.start = c;
				el.end = c;
				el.number = 1;
				s = f_sequence(el, go);
#ifdef TDF_DIAG4
				if (extra_diags) {
					diag_inline_result(go);
				}
				return diag_hold_refactor(s);	/* not inlining */
#else
				return hold_refactor(s);
#endif
			} else {
				exp ass;
				exp_list el;
				exp old_var;
				exp ident;

				/*
				 * Careful - we must not use copy on var
				 * because it belongs in the other context recurse!
				 */
				old_var = copyexp(var);

				ident = (copying(son(var))) ? pt(son(var)) : son(var);
				pt(old_var) = pt(ident);
				pt(ident) = old_var;
				++no(ident);
				ass = f_assign(old_var, copy(son(e)));
				el.start = ass;
				el.end = ass;
				el.number = 1;
#if TDF_DIAG4
				if (extra_diags) {
					diag_inline_result(bro(son(ass)));
				}
#endif
				return f_sequence(el, go);
			}
		}

		FALL_THROUGH;
	}

	{
		exp p = pt(e);
		exp z = copyexp(e);
		exp tp;

		switch (e->tag) {
		case alloca_tag:
		case apply_general_tag:
			has_alloca = 1;
			break;

		case tail_call_tag:
			has_alloca = 1;
			has_setjmp = 1;
			break;

		case current_env_tag:
			uses_crt_env = 1;
			uses_loc_address = 1;
			if (in_proc_def) {
				sh(z) = f_pointer(frame_alignment);
			}
			break;

		case untidy_return_tag:
		case local_free_all_tag:
		case long_jump_tag:
			has_setjmp = 1;
			break;
		}

		if (p != NULL) {
			/* the pt field must be a label */
			/* look to see if label is being copied and pick up right statement */
			tp = (copying(p)) ? pt(p) : p;
			pt(z) = tp;
			no(son(tp))++;	/* update label use count */
		}

		if (son(e) == NULL) {
			return z;
		}

		{
			exp t = son(e);
			exp q = copy_res(t, var, lab);
			exp ptt = q;

			while (!t->last) {	/* copy the arguments */
				setbro(ptt, copy_res(bro(t), var, lab));
				ptt->last = false;
				t = bro(t);
				ptt = bro(ptt);
			}

			son(z) = q;
			bro(ptt) = z;
			ptt->last = true;

			if (n == labst_tag || n == seq_tag) {
				/* in case bro(son(z)) is a tuple */
				sh(z) = sh(bro(son(z)));
			}

			return z;
		}
	}
}

exp
copy(exp e)
{
	return copy_res(e, NULL, NULL);
}

int
is_comm(exp e)
{
	if (no_bss) {
		return 0;
	}

	switch (e->tag) {

	case val_tag:
		return no(e) ? 0 : 1;

	case int_to_bitf_tag:
	case chvar_tag:
		return is_comm(son(e));

	case real_tag: {
		flpt f = no(e);
		return flptnos[f].sign ? 0 : 1;
	}

	case compound_tag: {
		exp t = son(e);

		if (t == NULL) {
			return 1;
		}

		for (;;) {
			t = bro(t);

			if (sh(t)->tag != bitfhd) {
				if (!is_comm(t)) {
					return 0;
				}
			} else {
				if (t->tag == val_tag) {
					if (no(t)) {
						return 0;
					}
				} else {
					if (no(son(t))) {
						return 0;
					}
				}
			}

			if (t->last) {
				return 1;
			}

			t = bro(t);
		}
		/* Not reached */
	}

	case ncopies_tag:
		return is_comm(son(e));

	case nof_tag: {
		exp t = son(e);

		if (t == NULL) {
			return 1;
		}

		for (;;) {
			if (!is_comm(t)) {
				return 0;
			}

			if (t->last) {
				return 1;
			}

			t = bro(t);
		}

		/* Not reached */
	}

	case concatnof_tag: {
		exp t = son(e);
		return is_comm(t) && is_comm(bro(t));
	}

	case clear_tag:
	case res_tag:
		return 1;

	case null_tag:
		return no(e) == 0;
	}

	return 0;
}
