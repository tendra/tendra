/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/foralls.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/me_fns.h>

#include <main/flags.h>

#include <refactor/const.h>
#include <refactor/optimise.h>
#include <refactor/refactor.h>
#include <refactor/refactor_id.h>

#define subvar 0x100

#define topsh f_top

static exp *
ifc_ptr_position(exp e)
{
	exp *a;
	exp dad = father(e);

	if (son(dad) == e) {
		a = &son(dad);
	} else {
		exp sib = son(dad);
		while (next(sib) != e) {
			sib = next(sib);
		}
		a = &next(sib);
	}

	return a;
}

static exp *
position(exp e)
{
	exp dad = father(e);
	exp *res = &son(dad);

	while (*res != e) {
		res = &next(*res);
	}

	return res;
}

static int
incr_var(exp e)
{
	/* is e  var = var + val; */
	exp dest;
	exp src;

	if (e->tag != ass_tag) {
		return false;
	}

	dest = son(e);
	src = next(dest);

	return (dest->tag == name_tag && src->tag == plus_tag
		&& son(src)->tag == name_tag && next(son(src))->tag == val_tag
		&& next(son(src))->last && son(dest) == son(son(src))
		&& no(dest) == no(son(src)));
}


static exp alteredset = NULL;

static void
isaltered(exp ld, int always)
{
	/* make copy of name!! - can be killed later */
	exp z;
	exp nld;

	for (z = alteredset; z != NULL; z = next(z)) {
		if (son(ld) == son(son(z)) &&
		    (son(ld)->tag != proc_tag || no(ld) == no(son(z)))) {
			props(z) &= (prop)always;
			return;
		}
	}

	nld = getexp(sh(ld), alteredset, 1, son(ld), NULL, props(ld), no(ld), ld->tag);
	alteredset = getexp(NULL, alteredset, alteredset == NULL, nld, NULL, (prop)always, 0, 0);
}

static int assign_alias;
static int jump_out;

/*
 * applies f to all (var = var + val) done in piece with bool set if always done.
 * where var is non-local of piece but non-global and not aliased and all other
 * uses in piece are cont(var) also applies altered to  named variables (name_tag)
 * which are assigned to, either in toto or by indexing.
 *
 * If there are any other assign_alias is set true
 */
static void
scan_for_incr(exp e, exp piece, void(*f)(exp, int))
{
	static int everytime = true;

	switch (e->tag) {
	case name_tag:
	case env_offset_tag:
		return;

	case ass_tag: {
		exp dest = son(e);
		exp src = next(son(e));

		if (dest->tag == name_tag && isvar(son(dest)) &&
		    !isglob(son(dest)) && iscaonly(son(dest)) &&
		    src->tag == plus_tag)
		{
			exp la = son(src);
			exp ra = next(son(src));

			if (ra->last && ra->tag == val_tag && la->tag == cont_tag &&
			    son(la)->tag == name_tag && son(son(la)) == son(dest) &&
			    no(dest) == no(son(la)) && !intnl_to(piece, son(dest)))
			{
				exp p = pt(son(dest)); /*uses of var */

				for (; p != NULL; p = pt(p)) {
#ifdef TDF_DIAG4
					if (isdiaginfo(p) || p == dest || p == son(la) ||
#else
					if (p == dest || p == son(la) ||
#endif
					    (p->last && next(p)->tag == cont_tag) ||
					    incr_var(father(p)) || !intnl_to(piece, p)) {
						continue;
					}

					goto tryalias;
				}

				f(e, everytime);
				return;
			}
		}

tryalias:

		if (dest->tag == name_tag && isvar(son(dest))) {
			isaltered(dest, everytime);
		} else if (dest->tag == addptr_tag && son(dest)->tag == name_tag &&
		           isvar(son(son(dest)))) {
			isaltered(son(dest), everytime);
		} else if (dest->tag == reff_tag && son(dest)->tag == addptr_tag &&
		           son(son(dest))->tag == name_tag && isvar(son(son(son(dest))))) {
			isaltered(son(son(dest)), everytime);
		} else if (dest->tag == name_tag &&
		           (props(son(dest)) & 0x10) != 0) {
			/* const in some loop */
			exp def = son(son(dest));
			if (def->tag == reff_tag) {
				def = son(def);
			}
			if (def->tag == addptr_tag && son(def)->tag == name_tag &&
			    isvar(son(son(def)))) {
				isaltered(dest, everytime);
			} else {
				assign_alias = true;
			}
		} else {
			assign_alias = true;
		}

		scan_for_incr(dest, piece, f);
		scan_for_incr(src, piece, f);
		return;
	}

	case case_tag:
		scan_for_incr(son(e), piece, f);
		everytime = false;
		return;

	case goto_tag:
	case testbit_tag:
	case test_tag: {
		int x = intnl_to(piece, pt(e));
		if (!x) {
			jump_out = true;
		}

		if (son(e) != NULL) {
			scan_for_incr(son(e), piece, f);
		}

		everytime = (everytime && !x);
		return;
	}

	case res_tag: {
		jump_out = true;
		scan_for_incr(son(e), piece, f);
		return;
	}

	case solve_tag:
	case rep_tag:
	case cond_tag: {
		exp z = son(e);
		int et = everytime;

		for (;;) {
			scan_for_incr(z, piece, f);
			everytime = false;
			if (z->last) {
				break;
			}
			z = next(z);
		}

		everytime = et;
		return;
	}

	case apply_tag:
		assign_alias = true; /* and do default */

	default: {
		exp z;

		for (z = son(e); z != NULL; z = next(z)) {
			scan_for_incr(z, piece, f);
			if (z->last) {
				return;
			}
		}
	}
	}
}

static int
good_val(exp a, exp piece)
{
	/* result ((a is name external to piece)
	       || (a is cont(name) where all uses of name in piece is cont))
	*/
	if (a->tag == name_tag) {
		return !intnl_to(piece, son(a));
	} else if (a->tag == cont_tag && son(a)->tag == name_tag &&
	           !intnl_to(piece, son(son(a))) && !isvis(son(son(a)))) {
		exp lda = son(a);
		exp pa = pt(son(lda));

		for (; pa != NULL; pa = pt(pa)) {
#ifdef TDF_DIAG4
			if (isdiaginfo(pa) || pa == lda || no(pa) != no(lda) ||
#else
			if (pa == lda || no(pa) != no(lda) ||
#endif
			    (pa->last && next(pa)->tag == cont_tag) ||
			    !intnl_to(piece, pa))
			{
				continue;
			}

			break;
		}

		return pa == NULL;
	}

	return false;
}

static int
usage_in(exp whole, exp part)
{
	exp q = part;
	int res = 1;
	int n = (int) q->tag;

	while (q != whole && q != NULL && (n != ident_tag || (props(q) & 0x40) == 0)) {
		q = father(q);
		n = (int)q->tag;

		if (n == cond_tag || n == rep_tag || n == solve_tag) {
			res = 2;
		}
	}

	return q == whole ? res : 0;
}

/* 0 initially, -1 either no common stride or non-constant stride, otherwise
 * contains common stride. */
static int stride;

/* Applies f to all addptr(x, cont(varid)) in piece where good_index_factor(1)
 * and all addptr(x, mult(cont(varid), mval))
 * where good_index_factor(mval) and and all test(cont(varid),
 * val -> outside piece) with bool if it is done exactly once.
 *
 * If different multiply facters are detected or a multiplying factor is not
 * good then stride is set to -1 and the procedure returned from. stride holds
 * the common multiplying factor, initially being 0. where x is name external
 * to piece or x is cont(name) where name is external to piece and all uses in
 * piece are cont(name)
 *
 * NB no alias check result is no of other uses of varid in piece
 */
static int
find_common_index(exp ldname, exp piece, void(*f)(exp, int))
{
	exp p = pt(son(ldname));
	int otheruses = 0;

	/* examine each use of loop variable */
	for(; p != NULL; p = pt(p)) {
		int usagex;
		exp dad;

#ifdef TDF_DIAG4
		if (isdiaginfo(p)) {
			continue;
		}
#endif
		if (no(p) != no(ldname)) {
			continue;
		}

		usagex = usage_in(piece, p);
		if (usagex == 0) {
			continue;
		}

		otheruses++;
		if (!p->last || next(p)->tag != cont_tag) {
			continue;
		}

		dad = father(next(p));
		if (!good_index_factor(1)) {
			stride = -1;
			UNUSED(dad);
			UNUSED(f);
			return 0;
		}

		if (dad->tag == addptr_tag && next(son(dad)) == next(p) && next(p)->last) {
			if (good_val(son(dad), piece)) {
				f(dad, usagex == 1);
				otheruses--;

				if (stride == 0) {
					stride = 1;
				} else if (stride > 1) {
					stride = -1;
					UNUSED(f);
					return 0;
				}
			}
		} else if (dad->tag == offset_mult_tag && son(dad) == next(p) &&
				   next(son(dad))->tag == val_tag && dad->last) {
			exp grandad = father(dad);
			if (!good_index_factor(no(next(son(dad))) / 8)) {
				stride = -1;
				UNUSED(grandad);
				return 0;
			}

			if (grandad->tag == addptr_tag && next(son(grandad)) == dad &&
				dad->last) {
				if (good_val(son(grandad), piece)) {
					f(grandad, usagex == 1);
					otheruses--;

					if (stride == 0) {
						stride = no(next(son(dad))) / 8;
					} else if (stride != no(next(son(dad))) / 8) {
						stride = -1;
						return 0;
					}
					/*printf("stride=%d\n", stride);*/
				}
			}
		} else if ((dad->tag == test_tag || dad->tag == testbit_tag) &&
				   piece == next(son(pt(dad)))) {
			f(dad, usagex == 1);
			otheruses--;
		}
	}

	return otheruses;
}

/*
 * Applies f to all addptr(x, cont(varid)) in piece where good_pointer_factor(1)
 * and all addptr(x, mult(cont(varid), mval)) where good_pointer_factor(mval)
 * and and all test(cont(varid), val -> outside piece) with bool if it is done
 * exactly once.
 * Where x is name external to piece or x is cont(name) where name is external to
 * piece and all uses in piece are cont(name)
 *
 * NB no alias check result is no of other uses of varid in piece
 */
static int
find_pointer_opt(exp ldname, exp piece, void(*f)(exp, int))
{

	exp p = pt(son(ldname));
	int otheruses = 0;

	/* examine each use of loop variable */
	for(; p != NULL; p = pt(p)) {
		int usagex;
		exp dad;

#ifdef TDF_DIAG4
		if (isdiaginfo(p)) {
			continue;
		}
#endif
		if (no(p) != no(ldname)) {
			continue;
		}

		usagex = usage_in(piece, p);
		if (usagex == 0) {
			continue;
		}

		otheruses++;
		if (!p->last || next(p)->tag != cont_tag) {
			continue;
		}

		dad = father(next(p));
		if (dad->tag == addptr_tag && next(son(dad)) == next(p) &&
			next(p)->last && good_pointer_factor(1)) {
			if (good_val(son(dad), piece)) {
				f(dad, usagex == 1);
				otheruses--;

				if (stride == 0) {
					stride = 1;
				} else if (stride > 1) {
					stride = -1;
				}
			}
		} else if (dad->tag == offset_mult_tag && son(dad) == next(p) &&
				   simple_const(piece, next(son(dad)), false,
								!assign_alias) && dad->last &&
				   (next(son(dad))->tag != val_tag ||
					good_pointer_factor(no(next(son(dad))) / 8))) {
			exp grandad = father(dad);
			if (grandad->tag == addptr_tag && next(son(grandad)) == dad &&
				dad->last) {
				if (good_val(son(grandad), piece)) {
					int n = -1;

					f(grandad, usagex == 1);
					otheruses--;

					if (next(son(dad))->tag == val_tag) {
						n = no(next(son(dad))) / 8;
					} else if (next(son(dad))->tag == name_tag) {
						exp id = son(next(son(dad)));
						if (son(id)->tag == val_tag) {
							n = no(son(id));
						}
					}

					if (stride == 0) {
						stride = n;
					} else if (stride != n) {
						stride = -1;
					}
				}
			}
		} else if (dad->tag == test_tag && piece == next(son(pt(dad)))) {
			f(dad, usagex == 1);
			otheruses--;
		}
	}

	return otheruses;
}

/* NULL  initially */
/* son = addptr exp;
   pt = [holder with son = different occurence of addptr exp]**(no-1)
		chained through ptr
   props =1 if done exactly once
   other addptrs chained similarly through next
*/
static exp addptrs;

/* NULL initially */
/* son = test
   pt = [holder with son = different occurence of test]**(no-1)
   props = 1 if done exactly once
   other tests chained similarly through next
*/
static exp tests;

static void
collect_loopthings(exp ind, int everytime)
{
	/* builds addptrs and tests*/
	exp z;
	exp *loopthing = (ind->tag == test_tag) ? &tests : &addptrs;
	for (z = *loopthing; z != NULL; z = next(z)) {
		if (eq_exp(son(z), ind)) {
			exp n = getexp(topsh, NULL, 0, ind, pt(z), 0, 0, 0);
			pt(z) = n;
			no(z) ++;
			props(z) &= (prop)everytime;
			return;
		}
	}
	*loopthing = getexp(topsh, *loopthing, *loopthing == NULL, ind,
	                    NULL, (prop)everytime, 1, 0);
}

static exp incrs;
/* NULL initially */
/* son = (v=v+val) exp;
   pt = [holder with son = different occurence with same v]**(no-1)
		chained through pt
   props = 1 if done exactly once
   other (v=v+val)s chained similarly through next
*/

static int
maybe_incr(exp e)
{
	exp incs = incrs;

	if (e->tag == cont_tag) {
		e = son(e);
	}

	if (e->tag != name_tag) {
		return 1;
	}

	while (incs != NULL) {
		exp dest = son(son(incs));
		assert(dest->tag == name_tag);
		if (son(dest) == son(e)) {
			return 1;
		}
		incs = next(incs);
	}

	return 0;
}

static void
collect_incrs(exp incr, int everytime)
{
	/* builds incrs */
	exp z;
	for (z = incrs; z != NULL; z = next(z)) {
		if (son(son(son(z))) == son(son(incr))
		    && no(son(son(z))) == no(son(incr))) {
			exp n = getexp(topsh, NULL, 0, incr, pt(z), 0, 0, 0);
			pt(z) = n;
			no(z) ++;
			props(z) &= (prop)everytime;
			return;
		}
	}

	incrs = getexp(topsh, incrs, incrs == NULL, incr, NULL,
	               (prop)everytime, 1, 0);
}

/*
 * transforms:
 *
 * strength reduction
 * 	addptr(x, y) if x is invariant of loop
 * 			ie x = simple var
 * 			or x = cont(z) and z not altered in loop
 * 		NB difference between invariant and not altered
 *
 * incr is only incrementer
 * addptrset is holder of addptr
 * loop is rep l:body
 * exp * looppos = position(loop)
 *
 * always construct
 * 	Var X = add_ptr(x, y)
 * 		replace all add_ptrs by cont(X) in addptrset and loopbpdy
 * 		replace incr by {X = reff(inc)c(X); incr} retaining handle on incr
 * 		shift looppos to body
 *
 * 	if always done and x not altered
 * 		look for cont( ..reff(s) reff(s+inc) ...reff(s+n*inc) )
 * 		replace loop by:
 * 		   Var Ci[0..n-1] = cont(ref(s+i*inc)cont(X))
 * 		   in loop with newbody:
 * 			var Cn = cont(ref(s+n*inc)cont(X)) in
 * 				body(reffn/Cn,  incr/{ Ci=C[i+1]; incr})
 *
 * replace loop by :
 * 	Var X = add_ptr(x, y) in newbody :
 * 		replace all add_ptrs by cont(X) in addptrset and loopbpdy
 * 		replace incr by {X = reff(inc)c(X); incr} retaining handle on incr
 * 		inc is in bytes.
 *
 */
static void
extract_addptrs(exp incr, exp addptrset, exp loop, exp inc, int inci, int cons)
{
	shape shvar = f_pointer(long_to_al(shape_align(sh(son(addptrset)))));
	exp id = getexp(sh(loop), next(loop), loop->last, son(addptrset),
	                NULL, 1 /*var*/, 0, ident_tag);
	/* setsib(son(id), loop); setdad(loop, id) later */

	int i;
	exp z = addptrset;
	exp *pos;
	exp ld, ass, reff, cont, seq, dest;
	exp incr_2, prod_2, neg_prod_2, mult_2;
	setcaonly(id);

	for (i = 0; i < no(addptrset); i++) {
		/* replace addptrs by cont(ld(id)) */
		exp sz = son(z) /*the addptr */;
		cont = getexp(sh(son(id)), next(sz), sz->last, NULL, NULL, 0, 0, cont_tag);
		ld = getexp(shvar, cont, 1, id, pt(id), 0, 0, name_tag);
		pos = position(sz);

		son(cont) = ld;
		pt(id) = ld;
		no(id) ++;
		*pos = cont;
		son(z) = cont;

		if (i != 0) {
			kill_exp(sz, NULL);
		}

		z = pt(z);
	}

	next(son(id)) = loop;
	son(id)->last = false;
	pos = position(loop);
	next(loop) = id;
	loop->last = true;
	*pos = id;

	if (cons || no(inc) != 0) {
		int mult = no(inc) * inci;
		if (cons) {
			mult = inci * 8;
		}

		ld = getexp(shvar, NULL, 1, id, pt(id), 0, 0, name_tag);
		pt(id) = ld;
		no(id) ++;
		cont = getexp(sh(son(id)), NULL, 1, ld, NULL, 0, 0, cont_tag);
		next(ld) = cont;
		reff = getexp(sh(cont), NULL, 1, cont, NULL, 0, mult, reff_tag);
		next(cont) = reff;
		dest = getexp(shvar, reff, 0, id, pt(id), 0, 0, name_tag);
		pt(id) = dest;
		no(id) ++;
		ass = getexp(topsh, NULL, 1, dest, NULL, 0, 0, ass_tag);
		next(reff) = ass;
		z = getexp(topsh, incr, 0, ass, NULL, 0, 0, 0);
		next(ass) = z;
		seq = getexp(topsh, next(incr), incr->last, z, NULL, 0, 0, seq_tag);
		pos = position(incr);
		next(incr) = seq;
		incr->last = true;
		*pos = seq;
		return;
	}

	mult_2 = copy(inc);
	if (inci < 0) {
		incr_2 = getexp(sh(inc), NULL, 1, NULL, NULL, 0, -inci, val_tag);
		next(incr_2) = mult_2;
		incr_2->last = false;
		neg_prod_2 = getexp(sh(inc), NULL, 1, incr_2, NULL, 0, 0, offset_mult_tag);
		neg_prod_2 = hc(neg_prod_2, mult_2);
		prod_2 = getexp(sh(inc), NULL, 1, neg_prod_2, NULL, 0, 0, neg_tag);
		next(neg_prod_2) = prod_2;
	} else {
		incr_2 = getexp(sh(inc), NULL, 1, NULL, NULL, 0, inci, val_tag);
		next(incr_2) = mult_2;
		incr_2->last = false;
		prod_2 = getexp(sh(inc), NULL, 0, incr_2, NULL, 0, 0, offset_mult_tag);
		prod_2 = hc(prod_2, mult_2);
	}

	ld = getexp(shvar, NULL, 1, id, pt(id), 0, 0, name_tag);
	pt(id) = ld;
	no(id)++;
	cont = getexp(sh(son(id)), NULL, 0, ld, NULL, 0, 0, cont_tag);
	next(ld) = cont;
	reff = getexp(sh(son(id)), NULL, 1, cont, NULL, 0, 0, addptr_tag);
	next(cont) = prod_2;
	reff = hc(reff, prod_2);
	dest = getexp(shvar, reff, 0, id, pt(id), 0, 0, name_tag);
	pt(id) = dest;
	no(id)++;
	ass = getexp(topsh, NULL, 1, dest, NULL, 0, 0, ass_tag);
	next(reff) = ass;
	z = getexp(topsh, incr, 0, ass, NULL, 0, 0, 0);
	next(ass) = z;
	seq = getexp(topsh, next(incr), incr->last, z, NULL, 0, 0, seq_tag);
	pos = position(incr);
	next(incr) = seq;
	incr->last = true;
	*pos = seq;
}

/*
 * replace loop body by :
 *
 * Var X = loopid*stride in newbody :
 * 	replace all offset_mults by cont(X) in addptrset and loopbody
 * 	replace incr by {X = c(X)+stride; incr} retaining handle on incr
 * 	inc is in bytes.
 *
 */
static void
scale_loopid(exp loop, exp addptrset, exp incrset)
{
	exp id = getexp(sh(loop), next(loop), loop->last,
	                next(son(son(addptrset))), NULL, 1 /*var*/, 0,
	                ident_tag);
	/* setsib(son(id), loop); setdad(loop, id) later */

	exp *pos;
	exp incr = son(incrset);
	shape shvar = sh(son(next(son(incr))));
	exp ld, ass, plus, cont, seq, dest, inc, z, next;

	while (addptrset != NULL) {
		int i;
		z = addptrset;
		next = next(addptrset);
		setcaonly(id);

		for (i = 0; i < no(addptrset); i++) {
			/* replace addptrs by cont(ld(id)) */
			exp sz = next(son(son(z))) /* the offset_mult */;
			cont = getexp(sh(son(id)), next(sz), sz->last, NULL,
			              NULL, 0, 0, cont_tag);
			ld = getexp(shvar, cont, 1, id, pt(id), 0, 0, name_tag);
			pos = position(sz);
			son(cont) = ld;
			pt(id) = ld;
			no(id) ++;
			*pos = cont;
			next(son(son(z))) = cont;
			if (i != 0) {
				kill_exp(sz, NULL);
			}
			z = pt(z);

		}

		retcell(addptrset);
		addptrset = next;
	}

	next(son(id)) = loop;
	son(id)->last = false;
	pos = position(loop);
	next(loop) = id;
	loop->last = true;
	*pos = id;

	inc = getexp(sh(son(id)), NULL, 1, NULL, NULL, 0,
	             stride * 8 * no(next(son(next(son(son(incrset)))))), val_tag);
	ld = getexp(shvar, NULL, 1, id, pt(id), 0, 0, name_tag);
	pt(id) = ld;
	no(id) ++;
	cont = getexp(sh(son(id)), NULL, 0, ld, NULL, 0, 0, cont_tag);
	next(ld) = cont;
	plus = getexp(sh(cont), NULL, 1, cont, NULL, 0, 0, plus_tag);
	next(cont) = inc;
	next(inc) = plus;
	dest = getexp(shvar, plus, 0, id, pt(id), 0, 0, name_tag);
	pt(id) = dest;
	no(id) ++;
	ass = getexp(topsh, NULL, 1, dest, NULL, 0, 0, ass_tag);
	next(plus) = ass;
	z = getexp(topsh, incr, 0, ass, NULL, 0, 0, 0);
	next(ass) = z;
	seq = getexp(topsh, next(incr), incr->last, z, NULL, 0, 0, seq_tag);
	pos = position(incr);
	next(incr) = seq;
	incr->last = true;
	*pos = seq;
}

/*
 * 	son contset = cont(X);
 * 	pt = next instance
 * 	replace loopbody by Var Z = cont(X) in loopbody(cont(X)/cont(Z))
 */
static exp
inner_cont(exp loopbody, exp contset)
{
	exp z = contset;
	exp *pos;
	int i;
	exp id = getexp(sh(loopbody), next(loopbody), loopbody->last,
	                son(contset), NULL, 1/*var*/, 0, ident_tag);
	setcaonly(id);

	for (i = 0; z != NULL; i++) {
		exp ld = getexp(sh(son(son(id))), NULL, 1, id, pt(id), 0, 0,
		                name_tag);
		exp cont = getexp(sh(son(id)), next(son(z)), son(z)->last, ld,
		                  NULL, 0, 0, cont_tag);
		next(ld) = cont;
		pt(id) = ld;
		no(id) ++;
		pos = position(son(z));
		*pos = cont;
		if (i != 0) {
			kill_exp(son(z), NULL);
		}
		son(z) = cont;
		z = pt(z);
	}

	pos = position(loopbody);
	next(son(id)) = loopbody;
	son(id)->last = false;
	next(loopbody) = id;
	loopbody->last = true;
	*pos = id;

	return id;
}

/*
 * son contset = cont(X);
 * pt = next instance
 * replace loop by Var Z = cont(x) in
 * 			loop(cont(x)/cont(Z), incr/{Z=cont(lasttid); incr})
 * returning new iddec
 */
static exp
outer_cont(exp loop, exp contset, exp lastid, exp incr)
{
	exp z = contset;
	exp seq, ld, cont, dest, ass;
	exp *pos;
	int i;
	exp id = getexp(sh(loop), next(loop), loop->last, son(contset),
	                NULL, 1/*var*/, 0, ident_tag);
	setcaonly(id);
	for (i = 0; z != NULL; i++) {
		ld = getexp(sh(son(son(id))), NULL, 1, id, pt(id), 0, 0,
		            name_tag);
		cont = getexp(sh(son(id)), next(son(z)), son(z)->last, ld, NULL,
		              0, 0, cont_tag);
		next(ld) = cont;
		pt(id) = ld;
		no(id)++;
		pos = position(son(z));
		*pos = cont;
		if (i != 0) {
			kill_exp(son(z), NULL);
		}
		son(z) = cont;
		z = pt(z);
	}

	pos = position(loop);
	next(son(id)) = loop;
	son(id)->last = false;
	next(loop) = id;
	loop->last = true;
	*pos = id;

	ld = getexp(sh(son(son(id))), NULL, 1, lastid, pt(lastid), 0, 0, name_tag);
	pt(lastid) = ld;
	no(lastid)++;
	cont = getexp(sh(son(id)), NULL, 1, ld, NULL, 0, 0, cont_tag);
	next(ld) = cont;
	dest = getexp(sh(son(son(id))), cont, 0, id, pt(id), 0, 0, name_tag);
	pt(id) = dest;
	no(id)++;
	ass = getexp(topsh, NULL, 1, dest, NULL, 0, 0, ass_tag);
	next(cont) = ass;
	z = getexp(sh(incr), incr, 0, ass, NULL, 0, 0, 0);
	next(ass) = z;
	seq = getexp(sh(incr), next(incr), incr->last, z, NULL, 0, 0, seq_tag);
	pos = position(incr);
	next(incr) = seq;
	incr->last = true;
	*pos = seq;

	return id;
}

static int
unaltered(exp e, int assign_alias)
{
	exp z = alteredset;

	if (e->tag == name_tag && isvar(son(e))) {
		for (; z != NULL; z = next(z)) {
			exp dest = son(z);
			assert(dest->tag == name_tag);

			if (!isvar(son(dest))) {
				dest = son(son(dest));
				if (dest->tag == reff_tag) {
					dest = son(dest);
				}
				assert(dest->tag == addptr_tag);
				dest = son(dest);
			}

			if (son(e) == son(dest) &&
			    (son(e)->tag != proc_tag || no(e) == no(dest))) {
				return false;
			}
		}

		return iscaonly(son(e)) || !assign_alias;
	}

	return false;
}

static int
invariant(exp e, int assign_alias)
{
	return (e->tag == name_tag) ||
	       (e->tag == cont_tag && unaltered(son(e), assign_alias));
}

static int multiplier;	/* part of answer to weaken */
static int arraystep;	/* part of answer to weaken */

/*
 * applies strength reduction to addptrs in addptrset and
 * delivers the multiplying factor if suitable for unwinding
 * otherwise 0
 */
static int
weaken(exp loop, exp addptrset, exp incrset)
{
	exp incr = son(incrset);
	exp addptr = son(addptrset);
	int inci = no(next(son(next(son(incr)))));
	exp minc = next(son(addptr));
	int simple_c = 0;
	int res = -1;

	if (minc->tag == cont_tag) {
		multiplier = inci;
		arraystep = 1;
		simple_c = 1;
	} else {
		arraystep = no(next(son(minc))) >> 3;
		multiplier = inci * arraystep;
	}

	if (!invariant(son(addptr), assign_alias) || no(incrset) != 1) {
		return 0;
	}

	if (props(addptrset) && unaltered(son(addptr), assign_alias)) {
		res = 1;
	}

	extract_addptrs(incr, addptrset, loop, next(son(minc)), inci, simple_c);

	return res;
}

struct en {
	exp e;
	int disp;
};

static int
unwind(exp loop, exp contset, exp incr, int incval)
{
	exp body = next(son(next(son(loop))));
	int i, j;
	exp z = contset;
	int n = no(contset);
	int insts = 0;
	struct en *s;

	if (n == 0) {
		s = NULL;
	} else {
		s = xcalloc(n, sizeof(struct en));
	}

	for (i = 0; i < n; i++) {
		/* sort cont([reff (disp) cont(X)) into s */
		exp c = son(z);
		exp w;
		int n;
		exp next = pt(z);
		assert(c->tag == cont_tag);

		if (!c->last) {
			z = next;
			continue;
		}

		if (next(c)->tag == cont_tag) {
			n = 0;
			w = next(c);
		} else if (next(c)->tag == reff_tag && next(c)->last &&
		           next(next(c))->tag == cont_tag) {
			n = no(next(c));
			w = next(next(c));
		} else {
			z = next;
			continue;
		}

		son(z) = w;

		for (j = 0; j < insts; j++) {
			int d = s[j].disp;
			if (d == n) {
				break;
			}
			if ((incval > 0 && d < n) || (incval < 0 && d > n)) {
				/*make a hole at jth position */
				int k;
				for (k = insts - 1; k >= j; k--) {
					s[k + 1] = s[k];
				}
				s[j].e = NULL;
				insts++;
				break;
			}
		}

		if (j == insts) {
			/* add another */
			insts++;
			s[j].e = NULL;
		}

		pt(z) = s[j].e;
		s[j].e = z;
		s[j].disp = n;
		z = next;
	}

	if (insts == 0) {
		return false;
	}
	z = NULL;

	for (i = 0; i < insts; i++) {
		if (no(s[i].e) > 1) {
			z = inner_cont(body, s[i].e);
		}
		for (; i < insts - 1 && s[i].disp - incval * 8 == s[i + 1].disp;
		     i++) {
			if (z == NULL) {
				z = inner_cont(body, s[i].e);
			}
			z = outer_cont(loop, s[i + 1].e, z, son(incr));
		}
		z = NULL;
	}

	return true;
}

static int
all_before(exp addptrset, exp inc, exp body)
{
	exp z, b;
	exp w;

	for (z = inc; z != body; z = b) {
		b = next(z);
		if (z->last) {
			continue;
		}

		for (w = addptrset; w != NULL; w = pt(w)) {
			/* son(w) is internal to body - is it in next(z) ?
			 * ie after z*/
			exp s;

			for (s = son(w); s != body && s != b; s = father(s))
				;

			if (s == b) {
				return false;
			}
		}
	}

	return true;
}

/*
 * ld is copy of the id->tag assigned to safely in loop (see do_one_rep)
 * replace loop(id) by Var x := cont(id) in loop(x); id = cont(x) ni;
 */
static void
replace_var(exp ldcpy, exp loop, shape shcont)
{
	exp z;
	exp *pos;
	exp ld = getexp(sh(ldcpy), NULL, 1, son(ldcpy), pt(son(ldcpy)),
	                props(ldcpy), no(ldcpy), ldcpy->tag);
	exp def = getexp(shcont, NULL, 0, ld, NULL, 0, 0, cont_tag);
	exp varid = getexp(sh(loop), next(loop), loop->last, def, NULL,
	                   subvar | 1 /*var*/, 1, ident_tag);
	exp ldvar = getexp(sh(ld), NULL, 1, varid, NULL, 0, 0, name_tag);
	exp contvar = getexp(shcont, NULL, 1, ldvar, NULL, 0, 0, cont_tag);
	exp nld = getexp(sh(ld), contvar, 0, son(ld), ld, 0, no(ld), name_tag);
	exp ass = getexp(topsh, NULL, 1, nld, NULL, 0, 0, ass_tag);
	exp seqh = getexp(topsh, ass, 0, loop, NULL, 0, 0, 0);
	exp seq = getexp(topsh, varid, 1, seqh, NULL, 0, 0, seq_tag);

	next(ass) = seq; /*father*/
	next(contvar) = ass;/*father*/
	next(ldvar) = contvar;/*father*/
	next(ld) = def; /* father */
	pt(son(ld)) = nld;
	no(son(ld)) += 2; 	/* two new used of id */
	next(def) = seq;
	pt(varid) = ldvar;
	setcaonly(varid);

	/* now relpace all old uses of ld in loop by varid */
	for (z = pt(ld); z != NULL; z = pt(z)) {
		if (no(z) == no(ld) && intnl_to(loop, z)) {
			/* ALTERATION #1 */
			exp lu = getexp(sh(z), next(z), z->last, varid, pt(varid), 0, 0, name_tag);
			pos = position(z);
			pt(varid) = lu;
			no(varid) ++;
			kill_exp(z, NULL); /* this should not kill the def of ld! */
			*pos = lu;
		}
	}

	pos = position(loop);
	*pos = varid;
	next(loop) = seqh;
	loop->last = true;
}

static exp
limexp(exp test, exp ld)
{
	exp lh = son(test);
	exp rh = next(lh);

	if (lh->tag == cont_tag && son(lh)->tag == name_tag &&
	    son(son(lh)) == son(ld) && no(son(lh)) == no(ld)) {
		return rh;
	}

	if (rh->tag == cont_tag && son(rh)->tag == name_tag &&
	    son(son(rh)) == son(ld) && no(son(rh)) == no(ld)) {
		return lh;
	}

	return NULL;
}

static exp
limaddptr(exp arr, exp val, int m)
{
	exp naddptr = getexp(sh(arr), NULL, 0, copy(arr), NULL, 0, 0, addptr_tag);
	exp z, v;
	shape s;

	if (m == 1) {
		z = copy(val);
		next(z) = naddptr;
		z->last = true;
	} else {
		s = f_offset(al1_of(sh(naddptr)), al1_of(sh(naddptr)));
		z = getexp(s, naddptr, 1, copy(val), NULL, 0, 0, offset_mult_tag);
		v = getexp(s, z, 1, NULL, NULL, 0, m * 8, val_tag);
		next(son(z)) = v;
		son(z)->last = false;
	}

	next(son(naddptr)) = z;
	son(naddptr)->last = false;

	/* a new addptr with index replaced by val - used in limdec*/
	return naddptr;
}

static exp
limmult(exp arr, exp val, int m)
{
	exp naddptr = getexp(sh(son(arr)), NULL, 0, copy(val), NULL, 0, 0,
	                     mult_tag);
	exp v = getexp(sh(son(arr)), NULL, 1, NULL, NULL, 0, m, val_tag);

	next(v) = naddptr;
	next(son(naddptr)) = v;
	son(naddptr)->last = false;

	/* a new addptr with index replaced by val - used in limdec*/
	return naddptr;
}

static exp
limreff(exp arr, int bytedisp)
{
	exp nreff;

	if (bytedisp == 0) {
		return copy(arr);
	}

	nreff = getexp(sh(arr), NULL, 0, copy(arr), NULL, 0, bytedisp * 8, reff_tag);
	next(son(nreff)) = nreff;
	son(nreff)->last = true;

	return nreff;
}

static exp
limconst(exp arr, int bytedisp)
{
	exp nreff;

	nreff = getexp(/*sh(son(arr))*/slongsh, NULL, 1, NULL, NULL, 0, bytedisp, val_tag);
	UNUSED(arr);
	next(nreff) = nreff;

	return nreff;
}

static exp
limdec(exp adec, exp val, int mult)
{
	exp init = son(adec);
	exp bdy = next(init);
	exp ninit = (val->tag != val_tag) ? limaddptr(son(init), val, mult) :
	            limreff(son(init), mult * no(val));
	exp nb = getexp(sh(bdy), adec, 1, ninit, NULL, 0, 0, ident_tag);

	next(ninit) = bdy;
	ninit->last = false;
	next(bdy) = nb;
	bdy->last = true;
	next(init) = nb;

	return nb; /* the declaration of the limit value */
}

static void
remove_incr(exp adec, exp test, exp incr, int mult)
{
	exp le = limexp(test, son(incr));
	exp *pos;
	exp ndec = limdec(adec, le, mult);

	exp lda = getexp(f_pointer(long_to_al(shape_align(sh(son(adec))))),
	                 NULL, 1, adec, pt(adec), 0, 0, name_tag);
	exp clda = getexp(sh(son(adec)), NULL, 0, lda, NULL, 0, 0,
	                  cont_tag);
	exp ldn = getexp(sh(son(ndec)), NULL, 0, ndec, pt(ndec), 0, 0,
	                 name_tag);
	exp ntestx = getexp(sh(test), next(test), test->last, NULL, pt(test),
	                    props(test), no(test), test->tag);

	next(lda) = clda;
	pt(adec) = lda;
	no(adec)++;
	pt(ndec) = ldn;
	no(ndec)++;

	if (le->last) {
		son(ntestx) = clda;
		next(clda) = ldn;
		clda->last = false;
		next(ldn) = ntestx;
		ldn->last = true;
	} else {
		son(ntestx) = ldn;
		next(ldn) = clda;
		ldn->last = false;
		next(clda) = ntestx;
		clda->last = true;
	}

	pos = position(test);
	*pos = ntestx;
	kill_exp(test, NULL);
	incr->tag = top_tag;
	kill_exp(next(son(incr)), NULL);
	kill_exp(son(incr), NULL);
	son(incr) = NULL;
}

static void
remove_incr2(exp adec, exp test, exp incr, int mult)
{
	exp le = limexp(test, son(incr));
	exp *pos;
	exp init = son(adec);
	exp bdy = next(init);
	exp ninit, ldn, ntestx, lda, clda;

	if (le->tag != val_tag && !remove_unused_index_counters) {
		return;
	}

	lda = getexp(f_pointer(long_to_al(shape_align(sh(son(adec))))), NULL,
	             1, adec, pt(adec), 0, 0, name_tag);
	clda = getexp(/*sh(son(adec))*/slongsh, NULL, 0, lda, NULL, 0, 0, cont_tag);

	if (le->tag == val_tag) {
		ninit = limconst(son(init), mult * no(le));
		ldn = ninit;
	} else {
		exp nb;

		ninit =  limmult(son(init), le, mult);
		nb = getexp(sh(bdy), adec, 1, ninit, NULL, 0, 0, ident_tag);
		next(ninit) = bdy;
		ninit->last = false;
		next(bdy) = nb;
		bdy->last = true;
		next(init) = nb;
		ninit = nb;
		ldn = getexp(sh(son(ninit)), NULL, 0, ninit, pt(ninit), 0, 0, name_tag);

		pt(ninit) = ldn;
		no(ninit)++;
	}

	ntestx = getexp(sh(test), next(test), test->last, NULL, pt(test),
	                props(test), no(test), test->tag);
	next(lda) = clda;
	pt(adec) = lda;
	no(adec)++;

	if (le->last) {
		son(ntestx) = clda;
		next(clda) = ldn;
		clda->last = false;
		next(ldn) = ntestx;
		ldn->last = true;
	} else {
		son(ntestx) = ldn;
		next(ldn) = clda;
		ldn->last = false;
		next(clda) = ntestx;
		clda->last = true;
	}

	pos = position(test);
	*pos = ntestx;
	kill_exp(test, NULL);
	incr->tag = top_tag;
	kill_exp(next(son(incr)), NULL);
	kill_exp(son(incr), NULL);
	son(incr) = NULL;
}

static int
use_in(exp w, exp ld)
{
	switch (w->tag) {
	case name_tag:
		return (son(w) == son(ld) && no(w) == no(ld));

	case ass_tag: {
		int z = use_in(next(son(w)), ld);
		if (z != 0) {
			return z;
		}

		if (son(w)->tag == name_tag && son(son(w)) == son(ld) &&
		    no(son(w)) == no(ld)) {
			return -1;
		}

		return use_in(son(w), ld);
	}

	case goto_tag:
	case case_tag:
	case test_tag:
	case testbit_tag:
	case labst_tag:
		return 1;

	default: {
		exp z;

		for (z = son(w); z != NULL; z = next(z)) {
			int a = use_in(z, ld);
			if (a != 0 || z->last) {
				return a;
			}
		}

		return 0;
	}
	}
}

static int
suitable_test(exp tests, exp incrld, exp loop)
{
	/* is test such that one can remove the increment ? */
	exp t, p;
	exp decx = son(incrld);
	exp v;

	if (tests == NULL || no(tests) != 1 || next(tests) != NULL) {
		return 0;
	}

	t = son(tests);
	v = limexp(t, incrld);
	if (v->tag != val_tag &&
	    (!invariant(v, assign_alias) || maybe_incr(v))) {
		return 0;
	}

	while (t != loop && t->last) {
		t = next(t);
	}

	if (t != loop) {
		return 0;
	}

	while (t->tag != proc_tag && t != decx) {
		exp b = next(t);

		if (!t->last) {
			for (p = pt(decx); p != NULL; p = pt(p)) {
				if (intnl_to(b, p) && use_in(b, incrld) == 1) {
					return 0;
				}
			}
		}

		t = b;
	}

	return 1;
}

static int
do_one_rep(exp loop)
{
	exp body = next(son(next(son(loop))));
	exp z;
	int res = 0;
	exp xincrs;
	assert(loop->tag == rep_tag);
	incrs = NULL;
	alteredset = NULL;
	assign_alias = false;
	jump_out = false;
	scan_for_incr(body, loop, collect_incrs);

	if (!jump_out && sh(loop)->tag == tophd) {
		/*
		 * look to see if var assigned to in loop can be
		 * locally declared ie Rep f(z) => Var x := cont(z) in
		 * Rep f(x); z = cont x ni; ? only worth while if z is
		 * global if z is local only worthwhile if it isnt
		 * being allocated in reg anyway
		 */
		for (z = alteredset; z != NULL; z = next(z)) {
			exp a = son(z);

			if (a->tag == name_tag &&
			    (isglob(son(a)) || !isvar(son(a))) &&
			    (props(son(a)) & subvar) == 0 &&
			    (!assign_alias ||
			     (isvar(son(a)) && iscaonly(son(a)))) &&
			    !intnl_to(body, son(a))) {
				exp p;
				exp dc = son(a);
				shape shcont;

				int const_init = !isglob(dc) &&
				                 (son(dc)->tag == clear_tag ||
				                  son(dc)->tag == val_tag ||
				                  son(dc)->tag == real_tag ||
				                  (son(dc)->tag == name_tag &&
				                   !isvar(son(son(dc)))));

				for (p = pt(son(a)); p != NULL; p = pt(p)) {
					int inb;

#ifdef TDF_DIAG4
					if (isdiaginfo(p)) {
						continue;
					}
#endif

					inb = intnl_to(body, p);
					if (!inb) {
						const_init = 0;
						continue;
					}

					if (no(a) != no(p)) {
						break;
					}

					if (p->last && next(p)->tag == cont_tag) {
						shcont = sh(next(p));
						continue;
					}

					if (!p->last && next(p)->last && next(next(p))->tag == ass_tag) {
						shcont = sh(next(p));
						continue;
					}
					break;
				}

				if (p != NULL) {
					continue;
				}

				/* only uses of this id is cont or assign in body */
				if (!isvar(son(a))) {
					/* check to see whether underlying id is used in loop */
					exp w = son(son(a));
					const_init = 0;
					if (w->tag == reff_tag) {
						w = son(w);
					}

					assert(w->tag == addptr_tag);
					/* uses of underlying var */
					w = pt(son(son(w)));

					for (; w != NULL; w = pt(w)) {
						if (intnl_to(body, w)) {
							break;
						}
					}

					if (w != NULL) {
						continue;
					}
				}

				if (const_init) {
					/* can reduce scope of altered variable */
					exp dc = son(a);
					exp bd = next(son(dc));

					if (bd != loop && dc->tag == ident_tag) {
						exp brodc = next(dc);
						int ldc = dc->last;
						exp broloop = next(loop);
						int lloop = loop->last;
						exp *pos = position(dc);
						*pos = bd;

						/* replace original dec with its body.*/
						next(bd) = brodc;
						if (ldc) {
							bd->last = true;
						} else {
							bd->last = false;
						}

						/* ... and set next to that of dec */
						pos = position(loop);

						/* replace loop by dec */
						*pos = dc;

						next(dc) = broloop;
						if (lloop) {
							dc->last = true;
						} else {
							dc->last = false;
						}

						/* ... set next to that of loop, ... */
						next(son(dc)) = loop;
						next(loop) = dc;

						/* ... and make loop be body of dec */
						loop->last = true;
					}
				} else {
					/* CHECK THIS: why is it set? */
					SET(shcont);

					replace_var(a, loop, shcont);
				}
				res = true;
			}
		}
	}

	xincrs = incrs;
	while (xincrs != NULL) {
		exp incrld = son(son(xincrs));
		exp nincr = next(xincrs);

		int ou;
		exp adec = NULL;
		int elsize;
		exp incrdec = son(incrld);
		tests = NULL;
		addptrs = NULL;
		stride = 0;
		ou = find_common_index(incrld, body, collect_loopthings);

		if (stride < 1) {
			exp t;
			int i;
			int nap = 0;
			tests = NULL;
			addptrs = NULL;
			stride = 0;
			ou = find_pointer_opt(incrld, body, collect_loopthings);

			for (i = 0, t = addptrs; t != NULL; i++, t = next(t)) {
				nap += no(t);
			}

			if (i >= 3 && i == nap) {
				/* don't replace all addptrs if too many vars required ... */
				if (stride > 1) {
					/* ... but can still scale index */
					scale_loopid(loop, addptrs, xincrs);

					/* only other uses besides addptr & test are in increment */
					if (ou == 2 && suitable_test(tests,
					                  son(son(xincrs)), loop)) {
						remove_incr2(next(loop),
						             son(tests),
						             son(xincrs),
						             stride);
					}
				}
				ou += nap;
				addptrs = NULL;
			}

			while (addptrs != NULL) {
				int rw = weaken(loop, addptrs, xincrs);
				exp next = next(addptrs);
				if (rw != 0) {
					res = true;
					/* really father put in by weaken */
					adec = next(loop);
					elsize = arraystep;
				} else {
					SET(elsize);
					ou += no(addptrs);
				}

				if (rw > 0) {
					/* there is only one incr and it is
					 * safe to replace conts; however don't
					 * know whether increment is before
					 * uses - could make store-exception if
					 * it isn't */
					if (all_before(addptrs,
					               son(xincrs), body) &&
					    multiplier != 0) {
						IGNORE unwind(loop, addptrs,
						              xincrs,
						              multiplier);
					}
				}

				retcell(addptrs);
				addptrs = next;
			}

			/* only other uses (besides addptr & test) of loop var is in increment */
			if (ou == 2 && adec != NULL &&
			    suitable_test(tests, incrld, loop) &&
			    multiplier != 0 && remove_unused_counters) {
				remove_incr(adec, son(tests), son(xincrs),
				            elsize);
			}
		} else if (stride > 1) {
			scale_loopid(loop, addptrs, xincrs);

			/* only other uses besides addptr & test are in increment */
			if (ou == 2 &&
			    suitable_test(tests, son(son(xincrs)), loop)) {
				remove_incr2(next(loop), son(tests), son(xincrs),
				             stride);
			}
		}

		/* avoid n-squared factor */
		if (res && no(incrdec) < 10) {
			IGNORE refactor_id(incrdec, next(son(incrdec)));
		}

		xincrs = nincr;
	}

	while (incrs != NULL) {
		exp z = next(incrs);
		retcell(incrs);
		incrs = z;
	}

	while (alteredset != NULL) {
		exp z = next(alteredset);
		retcell(son(alteredset));
		retcell(alteredset);
		alteredset = z;
	}

	return res;
}

static void
order_loops(exp reps)
{
	/* start at outer loop ?! */
	if ((props(reps) & 0x80) == 0) {
		if (next(reps) != NULL) {
			order_loops(next(reps));
		}

		if (son(reps) != NULL && son(reps)->tag == rep_tag && no(reps) < max_loop_depth) {
			exp loop = son(reps);
			/* ALTERATION #2 - does not affect C */
			if (son(loop)->tag != top_tag) {
				/* make loop(st, b) into seq((st), loop(make_top, b))
				 * analysis assumes son(loop) = top! */
				exp st = son(loop);
				exp b = next(st);
				exp * pos = ifc_ptr_position(loop);

				exp mt = getexp(f_top, b, 0, NULL, NULL, 0, 0, top_tag);
				exp sl = getexp(f_top, loop, 0 , st, NULL, 0, 0, 0);
				exp s = getexp(sh(loop), next(loop), loop->last,
				               sl, NULL, 0, 0, seq_tag);

				next(st) = sl;
				st->last = true;
				son(loop) = mt;
				next(loop) = s;

				loop->last = true;
				*pos = s;
			}

			IGNORE do_one_rep(loop);
		}

		props(reps) |= 0x80;
	}
}

void
forall_opt(void)
{
	exp reps;

	for (reps = get_repeats(); reps != NULL; reps = pt(reps)) {
		order_loops(reps);
	}

	if (optim & OPTIM_LOOPCONSTS) {
		optim &= ~OPTIM_FORALLS;

		/* try constant extraction again */
		repeat_consts();
	}
}

