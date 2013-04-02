/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/xalloc.h>

#include "exptypes.h"
#include "expmacs.h"
#include "foralls.h"

#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/install_fns.h>
#include <construct/constmacs.h>
#include <construct/flags.h>
#include <construct/me_fns.h>

#include <refactor/const.h>
#include <refactor/optimise.h>
#include <refactor/refactor.h>
#include <refactor/refactor_id.h>

#define subvar 0x100

#define false 0
#define true  1

#define topsh f_top

#ifndef Assert
#define Assert(x) if (!(x)) failer(#x)
#endif

exp *
ifc_ptr_position(exp e)
{
	exp *a;
	exp dad = father(e);
	if (son(dad) == e) {
		a = &son(dad);
	} else {
		exp sib = son(dad);
		while (bro(sib) != e) {
			sib = bro(sib);
		}
		a = &bro(sib);
	}
	return a;
}


static exp *
position(exp e)
{
	exp dad = father(e);
	exp *res = &son(dad);
	while (*res != e) {
		res = &bro(*res);
	}
	return res;
}


int
incr_var(exp e)
{
	/* is e  var = var + val; */
	exp dest;
	exp src;
	if (name(e) != ass_tag) {
		return false;
	}
	dest = son(e);
	src = bro(dest);
	return (name(dest) == name_tag && name(src) == plus_tag &&
		name(son(src)) == name_tag && name(bro(son(src))) == val_tag &&
		last(bro(son(src))) && son(dest) == son(son(src)) &&
                no(dest) == no(son(src)));
}


exp alteredset = nilexp;

void
isaltered(exp ld, int always)
{
	/* make copy of name!! - can be killed later */
	exp z;
	exp nld;
	for (z = alteredset; z != nilexp; z=bro(z)) {
	     if (son(ld) == son(son(z)) &&
		 (name(son(ld)) != proc_tag || no(ld) == no(son(z)))) {
		props(z) &= (prop)always;
		return;
	     }
	}
	nld = getexp(sh(ld), alteredset, 1, son(ld), nilexp, props(ld), no(ld),
		     name(ld));
	alteredset = getexp(nilexp, alteredset, alteredset == nilexp, nld,
			    nilexp, (prop)always, 0, 0);
}


int assign_alias;
int jump_out;

void
scan_for_incr(exp e, exp piece, void(*f)(exp, int))
{
	/* applies f to all (var = var + val) done in piece with bool set if
	 * always done.  where var is non-local of piece but non-global and not
	 * aliased and all other uses in piece are cont(var) also applies
	 * altered to  named variables (name_tag) which are assigned to, either
	 * in toto or by indexing.  if there are any other assign_alias is set
	 * true */
    static int everytime = true;
    switch (name(e)) {
	case name_tag:
	case env_offset_tag:
	    return;
	case ass_tag: {
	   exp dest = son(e);
	   exp src = bro(son(e));
	   if (name(dest) == name_tag && isvar(son(dest)) &&
	       !isglob(son(dest)) && iscaonly(son(dest)) &&
	       name(src) == plus_tag) {
		exp la = son(src);
		exp ra = bro(son(src));
		if (last(ra) && name(ra) == val_tag && name(la) == cont_tag &&
	            name(son(la)) == name_tag && son(son(la)) == son(dest) &&
	            no(dest) == no(son(la)) && !intnl_to(piece, son(dest))) {
		     exp p = pt(son(dest)); /*uses of var */
		     for (; p != nilexp; p = pt(p)) {
#ifdef NEWDIAGS
			if (isdiaginfo(p) || p == dest || p == son(la) ||
#else
			if (p == dest || p == son(la) ||
#endif
			    (last(p) && name(bro(p)) == cont_tag) ||
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
	   if (name(dest) == name_tag && isvar(son(dest))) {
		isaltered(dest, everytime);
	   } else if (name(dest) == addptr_tag && name(son(dest)) == name_tag &&
		      isvar(son(son(dest)))) {
	        isaltered(son(dest), everytime);
	   } else if (name(dest) == reff_tag && name(son(dest)) == addptr_tag &&
	       name(son(son(dest))) == name_tag && isvar(son(son(son(dest))))) {
		   isaltered(son(son(dest)), everytime);
	   } else if (name(dest) == name_tag &&
		      (props(son(dest)) & 0x10) != 0) {
		   /* const in some loop */
		   exp def = son(son(dest));
		   if (name(def) == reff_tag) {
			   def = son(def);
		   }
		   if (name(def) == addptr_tag && name(son(def)) == name_tag &&
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

	case goto_tag: case testbit_tag:
	case test_tag: {
		int x = intnl_to(piece, pt(e));
		if (!x) {
			jump_out = true;
		}
		if (son(e) != nilexp) {
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
	case solve_tag: case rep_tag: case cond_tag: {
	        exp z = son(e);
		int et = everytime;
		for (;;) {
			scan_for_incr(z, piece, f);
			everytime = false;
			if (last(z)) {
				break;
			}
			z = bro(z);
		}
		everytime = et;
		return;
	}

	case apply_tag: assign_alias = true; /* and do default */
	default: {
	    exp z = son(e);
	    if (z == nilexp) {
		    return;
	    }
	    for (;;) {
		scan_for_incr(z, piece, f);
		if (last(z)) {
			return;
		}
		z = bro(z);
	    }
	}
    }
}


int
good_val(exp a, exp piece)
{
	/* result ((a is name external to piece)
           || (a is cont(name) where all uses of name in piece is cont))
	*/
     if (name(a) == name_tag) {
	return !intnl_to(piece, son(a));
     } else if (name(a) == cont_tag && name(son(a)) == name_tag &&
		!intnl_to(piece, son(son(a))) && !isvis(son(son(a)))) {
	exp lda = son(a);
	exp pa = pt(son(lda));
	for (; pa != nilexp; pa = pt(pa)) {
#ifdef NEWDIAGS
	     if (isdiaginfo(pa) || pa == lda || no(pa) != no(lda) ||
#else
	     if (pa == lda || no(pa) != no(lda) ||
#endif
		 (last(pa) && name(bro(pa)) == cont_tag) ||
		 !intnl_to(piece, pa))continue;
	     break;
	}
	return pa == nilexp;
     }
     return false;
}


int
usage_in(exp whole, exp part)
{
  exp q = part;
  int res = 1;
  int n = (int)name(q);
  while (q != whole && q != nilexp &&
	 (n != ident_tag || (props(q) & 0x40) == 0)) {
    q = father(q);
    n = (int)name(q);
    if (n == cond_tag || n == rep_tag || n == solve_tag) {
	    res=2;
    }
  }


  return q == whole ? res : 0;
}

int stride;
/* 0 initially, -1 either no common stride or non-constant stride, otherwise
 * contains common stride. */

int
find_common_index(exp ldname, exp piece, void(*f)(exp, int))
{

	/* applies f to all addptr(x, cont(varid)) in piece where
	 * good_index_factor(1) and all addptr(x, mult(cont(varid), mval))
	 * where good_index_factor(mval) and and all test(cont(varid), val ->
	 * outside piece) with bool if it is done exactly once.  if different
	 * multiply facters are detected or a multiplying factor is not good
	 * then stride is set to -1 and the procedure returned from.  stride
	 * holds the common multiplying factor, initially being 0.  where x is
	 * name external to piece or x is cont(name) where name is external to
	 * piece and all uses in piece are cont(name) NB no alias check result
	 * is no of other uses of varid in piece */
     exp p = pt(son(ldname));
     int otheruses = 0;
     /* examine each use of loop variable */
     for(; p != nilexp; p = pt(p)) {
	int usagex;
#ifdef NEWDIAGS
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
	if (last(p) && name(bro(p)) == cont_tag) {
	     exp dad = father(bro(p));
             if (!good_index_factor(1)) {
                stride = -1;
		UNUSED(dad);
		UNUSED(f);
		return 0;
	     }
	     if (name(dad) == addptr_tag && bro(son(dad)) == bro(p) &&
		 last(bro(p))) {
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
	     } else if (name(dad) == offset_mult_tag && son(dad) == bro(p) &&
			name(bro(son(dad))) == val_tag && last(dad)) {
		     exp grandad = father(dad);
                if (!good_index_factor(no(bro(son(dad))) / 8)) {
			stride = -1;
			UNUSED(grandad);
			return 0;
		}
		if (name(grandad) == addptr_tag && bro(son(grandad)) == dad &&
		    last(dad)) {
		      if (good_val(son(grandad), piece)) {
			  f(grandad, usagex == 1);
                          otheruses--;
                          if (stride == 0) {
			      stride = no(bro(son(dad))) / 8;
			  } else if (stride != no(bro(son(dad))) / 8) {
			      stride = -1;
			      return 0;
			  }
                           /*printf("stride=%d\n", stride);*/
		      }
		}
	     } else if ((name(dad) == test_tag || name(dad) == testbit_tag) &&
			piece == bro(son(pt(dad)))) {
		     f(dad, usagex == 1);
		     otheruses--;
	     }
	}
     }
      return otheruses;
}


int
find_pointer_opt(exp ldname, exp piece, void(*f)(exp, int))
{

	/* applies f to all addptr(x, cont(varid)) in piece where
	 * good_pointer_factor(1) and all addptr(x, mult(cont(varid), mval))
	 * where good_pointer_factor(mval) and and all test(cont(varid), val ->
	 * outside piece) with bool if it is done exactly once.  where x is
	 * name external to piece or x is cont(name) where name is external to
	 * piece and all uses in piece are cont(name) NB no alias check result
	 * is no of other uses of varid in piece */
     exp p = pt(son(ldname));
     int otheruses = 0;
     for(; p != nilexp; p = pt(p)) {
	/* examine each use of loop variable */
	int usagex;
#ifdef NEWDIAGS
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
	if (last(p) && name(bro(p)) == cont_tag) {
	     exp dad = father(bro(p));
	     if (name(dad) == addptr_tag && bro(son(dad)) == bro(p) &&
		 last(bro(p)) && good_pointer_factor(1)) {
		if (good_val(son(dad), piece)) {
		     f(dad, usagex == 1);
                     otheruses--;
		     if (stride == 0) {
			     stride=1;
		     } else if (stride > 1) {
			     stride = -1;
		     }
		}
	     } else if (name(dad) == offset_mult_tag && son(dad) == bro(p) &&
			simple_const(piece, bro(son(dad)), false,
				     !assign_alias) && last(dad) &&
			(name(bro(son(dad))) != val_tag ||
			 good_pointer_factor(no(bro(son(dad))) / 8))) {
		     exp grandad = father(dad);
		if (name(grandad) == addptr_tag && bro(son(grandad)) == dad &&
                    last(dad)) {
			if (good_val(son(grandad), piece)) {
			  int n = -1;
			  f(grandad, usagex == 1);
                          otheruses--;
			  if (name(bro(son(dad))) == val_tag) {
				n = no(bro(son(dad))) /8;
			  } else if (name(bro(son(dad))) == name_tag) {
				exp id = son(bro(son(dad)));
				if (name(son(id)) == val_tag) {
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
	     } else if (name(dad) == test_tag && piece == bro(son(pt(dad)))) {
		     f(dad, usagex == 1);
		     otheruses--;
	     }
	}
     }
     return otheruses;
}


exp addptrs;
/* nilexp  initially */
/* son = addptr exp;
   pt = [holder with son = different occurence of addptr exp]**(no-1)
		chained through ptr
   props =1 if done exactly once
   other addptrs chained similarly through bro
*/

exp tests;
/* nilexp initially */
/* son = test
   pt = [holder with son = different occurence of test]**(no-1)
   props = 1 if done exactly once
   other tests chained similarly through bro
*/

void
collect_loopthings(exp ind, int everytime)
{
	/* builds addptrs and tests*/
	exp z;
	exp *loopthing = (name(ind) == test_tag) ? &tests : &addptrs;
	for (z = *loopthing; z != nilexp; z = bro(z)) {
		if (eq_exp(son(z), ind)) {
			exp n = getexp(topsh, nilexp, 0, ind, pt(z), 0, 0, 0);
			pt(z) =n;
			no(z) ++;
			props(z) &= (prop)everytime;
		   	return;
		}
	}
	*loopthing = getexp(topsh, *loopthing, *loopthing == nilexp, ind,
			    nilexp, (prop)everytime, 1, 0);
}


exp incrs;
/* nilexp initially */
/* son = (v=v+val) exp;
   pt = [holder with son = different occurence with same v]**(no-1)
		chained through pt
   props = 1 if done exactly once
   other (v=v+val)s chained similarly through bro
*/

int
maybe_incr(exp e)
{
	exp incs = incrs;
	if (name(e) == cont_tag) {
		e = son(e);
	}
	if (name(e) != name_tag) {
		return 1;
	}
	while (incs != nilexp) {
		exp dest = son(son(incs));
		Assert(name(dest) == name_tag);
		if (son(dest) == son(e)) {
			return 1;
		}
		incs = bro(incs);
	}
	return 0;
}


void
collect_incrs(exp incr, int everytime)
{
	/* builds incrs */
	exp z;
	for (z = incrs; z != nilexp; z = bro(z)) {
		if (son(son(son(z))) == son(son(incr))
			&& no(son(son(z))) == no(son(incr))) {
			exp n = getexp(topsh, nilexp, 0, incr, pt(z), 0, 0, 0);
			pt(z) = n;
			no(z) ++;
			props(z) &= (prop)everytime;
		   	return;
		}
	}

	incrs = getexp(topsh, incrs, incrs == nilexp, incr, nilexp,
		       (prop)everytime, 1, 0);

}


/* transforms:

	strength reduction
		addptr(x, y) if x is invariant of loop
				ie x = simple var
				or x = cont(z) and z not altered in loop
			NB difference between invariant and not altered


*/


/* incr is only incrementer
   addptrset is holder of addptr
   loop is rep l:body
   exp * looppos = position(loop)


always construct
	Var X = add_ptr(x, y)
		replace all add_ptrs by cont(X) in addptrset and loopbpdy
		replace incr by {X = reff(inc)c(X); incr}
                                               retaining handle on incr
		shift looppos to body

	if always done and x not altered
		look for cont( ..reff(s) reff(s+inc) ...reff(s+n*inc) )
		replace loop by:
		   Var Ci[0..n-1] = cont(ref(s+i*inc)cont(X))
		   in loop with newbody:
			var Cn = cont(ref(s+n*inc)cont(X)) in
				body(reffn/Cn,  incr/{ Ci=C[i+1]; incr})

*/

static void
extract_addptrs(exp incr, exp addptrset, exp loop, exp inc, int inci, int cons)
{
	/* replace loop by :
	Var X = add_ptr(x, y) in newbody :
		replace all add_ptrs by cont(X) in addptrset and loopbpdy
		replace incr by {X = reff(inc)c(X); incr}
                                                 retaining handle on incr
		inc is in bytes.

	*/
	shape shvar = f_pointer(long_to_al(shape_align(sh(son(addptrset)))));
	exp id = getexp(sh(loop), bro(loop), last(loop), son(addptrset),
			   nilexp, 1 /*var*/, 0, ident_tag);
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
	     cont = getexp(sh(son(id)), bro(sz), last(sz), nilexp, nilexp, 0,
			   0, cont_tag);
             ld = getexp(shvar, cont, 1, id, pt(id), 0, 0, name_tag);
	     pos = position(sz);
	     son(cont) = ld;
	     pt(id) = ld;
	     no(id) ++;
	     *pos = cont;
             son(z) = cont;
	     if (i != 0) {
		     kill_exp(sz, nilexp);
	     }
	     z = pt(z);
	}

	bro(son(id)) = loop;
	clearlast(son(id));
	pos = position(loop);
        bro(loop) = id;
	setlast(loop);
	*pos = id;
	if (cons || no(inc) != 0) {
		int mult = no(inc)*inci;
		if (cons) {
			mult = inci * 8;
		}
		ld = getexp(shvar, nilexp, 1, id, pt(id), 0, 0, name_tag);
		pt(id) = ld;
		no(id) ++;
		cont = getexp(sh(son(id)), nilexp, 1, ld, nilexp, 0, 0,
			      cont_tag);
		bro(ld) = cont;
		reff = getexp(sh(cont), nilexp, 1, cont, nilexp, 0, mult,
			      reff_tag);
		bro(cont) = reff;
		dest = getexp(shvar, reff, 0, id, pt(id), 0, 0, name_tag);
		pt(id) = dest;
		no(id) ++;
		ass = getexp(topsh, nilexp, 1, dest, nilexp, 0, 0, ass_tag);
		bro(reff) = ass;
		z = getexp(topsh, incr, 0, ass, nilexp, 0, 0, 0);
		bro(ass) = z;
		seq = getexp(topsh, bro(incr), last(incr), z, nilexp, 0, 0,
			     seq_tag);
		pos = position(incr);
		bro(incr) = seq;
		setlast(incr);
		*pos = seq;
	} else{
		mult_2 = copy(inc);
		if (inci < 0) {
			incr_2 = getexp(sh(inc), nilexp, 1, nilexp, nilexp, 0,
					-inci, val_tag);
			bro(incr_2) = mult_2;
			clearlast(incr_2);
			neg_prod_2 = getexp(sh(inc), nilexp, 1, incr_2, nilexp,
					    0, 0, offset_mult_tag);
			neg_prod_2 = hc(neg_prod_2, mult_2);
			prod_2 = getexp(sh(inc), nilexp, 1, neg_prod_2, nilexp,
					0, 0, neg_tag);
			bro(neg_prod_2) = prod_2;
		} else {
			incr_2 = getexp(sh(inc), nilexp, 1, nilexp, nilexp, 0,
					inci, val_tag);
			bro(incr_2) = mult_2;
			clearlast(incr_2);
			prod_2 = getexp(sh(inc), nilexp, 0, incr_2, nilexp, 0,
					0, offset_mult_tag);
			prod_2 = hc(prod_2, mult_2);
		}
		ld = getexp(shvar, nilexp, 1, id, pt(id), 0, 0, name_tag);
		pt(id) = ld;
		no(id)++;
		cont = getexp(sh(son(id)), nilexp, 0, ld, nilexp, 0, 0,
			      cont_tag);
		bro(ld) = cont;
		reff = getexp(sh(son(id)), nilexp, 1, cont, nilexp, 0, 0,
			      addptr_tag);
		bro(cont) = prod_2;
		reff = hc(reff, prod_2);
		dest = getexp(shvar, reff, 0, id, pt(id), 0, 0, name_tag);
		pt(id) = dest;
		no(id)++;
		ass = getexp(topsh, nilexp, 1, dest, nilexp, 0, 0, ass_tag);
		bro(reff) = ass;
		z = getexp(topsh, incr, 0, ass, nilexp, 0, 0, 0);
		bro(ass) = z;
		seq = getexp(topsh, bro(incr), last(incr), z, nilexp, 0, 0,
			     seq_tag);
		pos = position(incr);
		bro(incr) = seq;
		setlast(incr);
		*pos = seq;
	}
}


static void
scale_loopid(exp loop, exp addptrset, exp incrset)
{
	/* replace loop body by :
	Var X = loopid*stride in newbody :
		replace all offset_mults by cont(X) in addptrset and loopbody
		replace incr by {X = c(X)+stride; incr}
                                                 retaining handle on incr
		inc is in bytes.

	*/
	exp id = getexp(sh(loop), bro(loop), last(loop),
			bro(son(son(addptrset))), nilexp, 1 /*var*/, 0,
			ident_tag);
			/* setsib(son(id), loop); setdad(loop, id) later */

	exp *pos;
        exp incr = son(incrset);
        shape shvar = sh(son(bro(son(incr))));
	exp ld, ass, plus, cont, seq, dest, inc, z, next;
	while (addptrset != nilexp) {
		int i;
		z = addptrset;
		next = bro(addptrset);
		setcaonly(id);
		for (i = 0; i < no(addptrset); i++) {
			/* replace addptrs by cont(ld(id)) */
			exp sz = bro(son(son(z))) /* the offset_mult */;
			cont = getexp(sh(son(id)), bro(sz), last(sz), nilexp,
				      nilexp, 0, 0, cont_tag);
			ld = getexp(shvar, cont, 1, id, pt(id), 0, 0, name_tag);
			pos = position(sz);
			son(cont) = ld;
			pt(id) = ld;
			no(id) ++;
			*pos = cont;
			bro(son(son(z))) = cont;
			if (i != 0) {
				kill_exp(sz, nilexp);
			}
			z = pt(z);

		}
		retcell(addptrset);
		addptrset = next;
	}

	bro(son(id)) = loop;
	clearlast(son(id));
	pos = position(loop);
        bro(loop) = id;
	setlast(loop);
	*pos = id;

        inc = getexp(sh(son(id)), nilexp, 1, nilexp, nilexp, 0,
		     stride * 8 * no(bro(son(bro(son(son(incrset)))))),
		     val_tag);
        ld = getexp(shvar, nilexp, 1, id, pt(id), 0, 0, name_tag);
	pt(id) = ld;
	no(id) ++;
	cont = getexp(sh(son(id)), nilexp, 0, ld, nilexp, 0, 0, cont_tag);
	bro(ld) = cont;
	plus = getexp(sh(cont), nilexp, 1, cont, nilexp, 0, 0, plus_tag);
	bro(cont) = inc;
        bro(inc) = plus;
	dest = getexp(shvar, plus, 0, id, pt(id), 0, 0, name_tag);
	pt(id) = dest;
	no(id) ++;
	ass = getexp(topsh, nilexp, 1, dest, nilexp, 0, 0, ass_tag);
	bro(plus) = ass;
	z = getexp(topsh, incr, 0, ass, nilexp, 0, 0, 0);
	bro(ass) = z;
	seq = getexp(topsh, bro(incr), last(incr), z, nilexp, 0, 0, seq_tag);
	pos = position(incr);
	bro(incr) = seq;
	setlast(incr);
	*pos = seq;
}


exp
inner_cont(exp loopbody, exp contset)
{

/*
	son contset = cont(X);
	pt = next instance
	replace loopbody by Var Z = cont(X) in loopbody(cont(X)/cont(Z))

*/

	exp z = contset;
	exp *pos;
	int i;
	exp id = getexp(sh(loopbody), bro(loopbody), last(loopbody),
			son(contset), nilexp, 1/*var*/, 0, ident_tag);
	setcaonly(id);

	for (i=0; z != nilexp; i++) {
	    exp ld = getexp(sh(son(son(id))), nilexp, 1, id, pt(id), 0, 0,
			    name_tag);
	    exp cont = getexp(sh(son(id)), bro(son(z)), last(son(z)), ld,
			      nilexp, 0, 0, cont_tag);
	    bro(ld) = cont;
	    pt(id) = ld;
	    no(id) ++;
	    pos = position(son(z));
	    *pos = cont;
	    if (i != 0) {
		    kill_exp(son(z), nilexp);
	    }
	    son(z) = cont;
	    z = pt(z);
	}

	pos = position(loopbody);
	bro(son(id)) = loopbody;
	clearlast(son(id));
	bro(loopbody) = id;
	setlast(loopbody);
	*pos = id;
	return id;
}


exp
outer_cont(exp loop, exp contset, exp lastid, exp incr)
{

/*
	son contset = cont(X);
	pt = next instance
	replace loop by Var Z = cont(x) in
			loop(cont(x)/cont(Z), incr/{Z=cont(lasttid); incr})
	returning new iddec
*/

	exp z = contset;
	exp seq, ld, cont, dest, ass;
	exp *pos;
	int i;
	exp id = getexp(sh(loop), bro(loop), last(loop), son(contset),
			nilexp, 1/*var*/, 0, ident_tag);
 	setcaonly(id);
	for (i = 0; z != nilexp; i++) {
	    ld = getexp(sh(son(son(id))), nilexp, 1, id, pt(id), 0, 0,
			name_tag);
	    cont = getexp(sh(son(id)), bro(son(z)), last(son(z)), ld, nilexp,
			  0, 0, cont_tag);
	    bro(ld) = cont;
	    pt(id) = ld;
	    no(id)++;
	    pos = position(son(z));
	    *pos = cont;
	    if (i != 0) {
		    kill_exp(son(z), nilexp);
	    }
	    son(z) = cont;
	    z = pt(z);
	}

	pos = position(loop);
	bro(son(id)) = loop;
	clearlast(son(id));
	bro(loop) = id;
	setlast(loop);
	*pos = id;


	ld = getexp(sh(son(son(id))), nilexp, 1, lastid, pt(lastid), 0, 0,
		    name_tag);
	pt(lastid) = ld;
	no(lastid)++;
	cont = getexp(sh(son(id)), nilexp, 1, ld, nilexp, 0, 0, cont_tag);
	bro(ld) = cont;
	dest = getexp(sh(son(son(id))), cont, 0, id, pt(id), 0, 0, name_tag);
	pt(id) = dest;
	no(id)++;
	ass = getexp(topsh, nilexp, 1, dest, nilexp, 0, 0, ass_tag);
	bro(cont) = ass;
 	z = getexp(sh(incr), incr, 0, ass, nilexp, 0, 0, 0);
	bro(ass) = z;
	seq = getexp(sh(incr), bro(incr), last(incr), z, nilexp, 0, 0, seq_tag);
	pos = position(incr);
	bro(incr) = seq;
	setlast(incr);
	*pos = seq;

	return id;
}


int
unaltered(exp e, int assign_alias)
{
	exp z = alteredset;
	if (name(e) == name_tag && isvar(son(e))) {
	     for (; z != nilexp; z = bro(z)) {
		exp dest = son(z);
		Assert(name(dest) == name_tag);
		if (!isvar(son(dest))) {
			dest = son(son(dest));
			if (name(dest) == reff_tag) {
				dest = son(dest);
			}
			Assert(name(dest) == addptr_tag);
			dest = son(dest);
		}
		if (son(e) == son(dest) &&
			(name(son(e)) != proc_tag || no(e) == no(dest))) {
			return false;
		}
	     }
	     return iscaonly(son(e)) || !assign_alias;
	}
	return false;
}


int
invariant(exp e, int assign_alias)
{
	return (name(e) == name_tag) ||
	       (name(e) == cont_tag && unaltered(son(e), assign_alias));
}


static int multiplier;	/*part of answer to weaken */
static int arraystep;	/*part of answer to weaken */

int
weaken(exp loop, exp addptrset, exp incrset)
{
	/* applies strength reduction to addptrs in addptrset and
		delivers the multiplying factor if suitable for unwinding
			otherwise 0
	*/
	exp incr = son(incrset);
	exp addptr = son(addptrset);
	int inci = no(bro(son(bro(son(incr)))));
	exp minc = bro(son(addptr));
        int simple_c = 0;
	int res = -1;
	if (name(minc) == cont_tag) {
		multiplier = inci;
		arraystep = 1;
                simple_c = 1;
	} else {
		arraystep = no(bro(son(minc))) >> 3;
		multiplier = inci * arraystep;
	}

	if (!invariant(son(addptr), assign_alias) || no(incrset) != 1) {
		return 0;
	}
	if (props(addptrset) && unaltered(son(addptr), assign_alias)) {
		res = 1;
	}

	extract_addptrs(incr, addptrset, loop, bro(son(minc)), inci, simple_c);
  	return res;
}


struct en{
	exp e;
	int disp;
};

int
unwind(exp loop, exp contset, exp incr, int incval)
{
	exp body = bro(son(bro(son(loop))));
	int i, j;
	exp z = contset;
	int n = no(contset);
	int insts = 0;
	struct en *s;
	if (n == 0) {
		s = NULL;
	} else {
		s = (struct en *)xcalloc(n, sizeof(struct en));
	}
	for (i=0; i<n; i++) {
	    /* sort cont([reff (disp) cont(X)) into s */
	    exp c = son(z);
	    exp w;
	    int n;
	    exp next = pt(z);
	    Assert(name(c) == cont_tag);
	    if (!last(c)) {
		    z = next;
		    continue;
	    }
	    if (name(bro(c)) == cont_tag) {
		    n = 0;
		    w = bro(c);
	    } else if (name(bro(c)) == reff_tag && last(bro(c)) &&
		       name(bro(bro(c))) == cont_tag) {
		    n = no(bro(c));
		    w = bro(bro(c));
	    } else {
		    z= next;
		    continue;
	    }

	    son(z) = w;

	    for (j=0; j <insts; j++) {
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
			s[j].e = nilexp;
			insts++;
			break;
		}
	    }
	    if (j == insts) {
		/* add another */
		insts++;
		s[j].e = nilexp;
	    };
	    pt(z) = s[j].e;
	    s[j].e = z;
	    s[j].disp= n;
	    z = next;
	}
	if (insts == 0) {
		return false;
	}
	z = nilexp;

	for (i = 0; i < insts; i++) {
	      if (no(s[i].e) > 1) {
		      z = inner_cont(body, s[i].e);
	      }
	      for (; i < insts-1 && s[i].disp - incval * 8 == s[i+1].disp;
		   i++) {
		if (z == nilexp) {
			z = inner_cont(body, s[i].e);
		}
		z = outer_cont(loop, s[i + 1].e, z, son(incr));
	      }
	      z= nilexp;
	}

	return true;
}


int
all_before(exp addptrset, exp inc, exp body)
{
     	exp z=inc;
	exp w;
     	while (z != body) {
	    exp b = bro(z);
	    if (!last(z)) {
		    for (w=addptrset; w != nilexp; w= pt(w)) {
			    /* son(w) is internal to body - is it in bro(z) ?
			     * ie after z*/
			    exp s = son(w);
			    while (s != body && s != b) {
				    s = father(s);
			    }
			    if (s == b) {
				    return false;
			    }
		    }
	    }
	    z = b;
	}
	return true;
}


void
replace_var(exp ldcpy, exp loop, shape shcont)
{
	/* ld is copy of the name(id) assigned to safely in loop
            (see do_one_rep)
	    replace loop(id) by Var x := cont(id) in loop(x); id = cont(x) ni;
	*/
	exp z;
	exp *pos;
	exp ld = getexp(sh(ldcpy), nilexp, 1, son(ldcpy), pt(son(ldcpy)),
			props(ldcpy), no(ldcpy), name(ldcpy));
	exp def = getexp(shcont, nilexp, 0, ld, nilexp, 0, 0, cont_tag);
	exp varid = getexp(sh(loop), bro(loop), last(loop), def, nilexp,
			   subvar | 1 /*var*/, 1, ident_tag);
	exp ldvar = getexp(sh(ld), nilexp, 1, varid, nilexp, 0, 0, name_tag);
	exp contvar = getexp(shcont, nilexp, 1, ldvar, nilexp, 0, 0, cont_tag);
	exp nld = getexp(sh(ld), contvar, 0, son(ld), ld, 0, no(ld), name_tag);
	exp ass = getexp(topsh, nilexp, 1, nld, nilexp, 0, 0, ass_tag);
	exp seqh = getexp(topsh, ass, 0, loop, nilexp, 0, 0, 0);
	exp seq = getexp(topsh, varid, 1, seqh, nilexp, 0, 0, seq_tag);
	bro(ass) = seq; /*father*/
	bro(contvar) = ass;/*father*/
	bro(ldvar) = contvar;/*father*/
	bro(ld) = def; /* father */
	pt(son(ld)) = nld;
	no(son(ld)) += 2; 	/* two new used of id */
	bro(def) = seq;
	pt(varid) = ldvar;
	setcaonly(varid);

	/* now relpace all old uses of ld in loop by varid */
	for (z = pt(ld); z != nilexp; z = pt(z)) {
	      if (no(z) == no(ld) && intnl_to(loop, z)) {
/* ALTERATION #1 */
		exp lu = getexp(sh(z), bro(z), last(z), varid, pt(varid), 0,
				0, name_tag);
		pos = position(z);
		pt(varid) = lu;
		no(varid) ++;
		kill_exp(z, nilexp); /* this should not kill the def of ld! */
		*pos = lu;
	      }
	}
	pos = position(loop);
	*pos = varid;
	bro(loop) = seqh;
	setlast(loop);
}


exp
limexp(exp test, exp ld)
{
	exp lh = son(test);
	exp rh = bro(lh);
	if (name(lh) == cont_tag && name(son(lh)) == name_tag &&
	    son(son(lh)) == son(ld) && no(son(lh)) == no(ld)) {
		return rh;
	}

	if (name(rh) == cont_tag && name(son(rh)) == name_tag &&
	    son(son(rh)) == son(ld) && no(son(rh)) == no(ld)) {
		return lh;
	}
	return nilexp;
}

exp
limaddptr(exp arr, exp val, int m)
{
	exp naddptr = getexp(sh(arr), nilexp, 0, copy(arr), nilexp, 0, 0,
			     addptr_tag);
	exp z, v;
        shape s;
	if (m == 1) {
	    z = copy(val);
	    bro(z) = naddptr;
	    setlast(z);
	} else {
            s = f_offset(al1_of(sh(naddptr)), al1_of(sh(naddptr)));
	    z = getexp(s, naddptr, 1, copy(val), nilexp, 0, 0, offset_mult_tag);
	    v = getexp(s, z, 1, nilexp, nilexp, 0, m*8, val_tag);
	    bro(son(z)) = v;
	    clearlast(son(z));
	}
	bro(son(naddptr)) = z;
	clearlast(son(naddptr));
	return naddptr;
	/* a new addptr with index replaced by val - used in limdec*/
}

exp
limmult(exp arr, exp val, int m)
{
	exp naddptr = getexp(sh(son(arr)), nilexp, 0, copy(val), nilexp, 0, 0,
			     mult_tag);
	exp v = getexp(sh(son(arr)), nilexp, 1, nilexp, nilexp, 0, m, val_tag);
	bro(v) = naddptr;
	bro(son(naddptr)) = v;
	clearlast(son(naddptr));
	return naddptr;
	/* a new addptr with index replaced by val - used in limdec*/
}


exp
limreff(exp arr, int bytedisp)
{
	if (bytedisp != 0) {
		exp nreff = getexp(sh(arr), nilexp, 0, copy(arr), nilexp, 0,
				   bytedisp * 8, reff_tag);
		bro(son(nreff)) = nreff;
		setlast(son(nreff));
		return nreff;
	} else {
		return copy(arr);
	}
}

exp
limconst(exp arr, int bytedisp)
{
	exp nreff = getexp(/*sh(son(arr))*/slongsh, nilexp, 1, nilexp, nilexp,
			   0, bytedisp, val_tag);
	UNUSED(arr);
	bro(nreff) = nreff;
 	return nreff;
}


exp
limdec(exp adec, exp val, int mult)
{
	exp init = son(adec);
	exp bdy = bro(init);
	exp ninit = (name(val) != val_tag) ? limaddptr(son(init), val, mult) :
		limreff(son(init), mult * no(val));
	exp nb = getexp(sh(bdy), adec, 1, ninit, nilexp, 0, 0, ident_tag);
	bro(ninit) = bdy;
	clearlast(ninit);
	bro(bdy) = nb;
	setlast(bdy);
	bro(init) = nb;
	return nb; /* the declaration of the limit value */
}


exp
limdec2(exp adec, exp val, int mult)
{
	exp init = son(adec);
	exp bdy = bro(init);
	exp ninit = (name(val) != val_tag) ? limmult(son(init), val, mult) :
		limconst(son(init), mult * no(val));
	exp nb = getexp(sh(bdy), adec, 1, ninit, nilexp, 0, 0, ident_tag);
	bro(ninit) = bdy;
	clearlast(ninit);
	bro(bdy) = nb;
	setlast(bdy);
	bro(init) = nb;
	return nb; /* the declaration of the limit value */
}


void
remove_incr(exp adec, exp test, exp incr, int mult)
{
	exp le = limexp(test, son(incr));
	exp *pos;
	exp ndec = limdec(adec, le, mult);
	exp lda = getexp(f_pointer(long_to_al(shape_align(sh(son(adec))))),
                                   nilexp, 1, adec, pt(adec), 0, 0, name_tag);
	exp clda = getexp(sh(son(adec)), nilexp, 0, lda, nilexp, 0, 0,
			  cont_tag);
	exp ldn = getexp(sh(son(ndec)), nilexp, 0, ndec, pt(ndec), 0, 0,
			 name_tag);
	exp ntestx = getexp(sh(test), bro(test), last(test), nilexp, pt(test),
			    props(test), no(test), name(test));
	bro(lda) = clda;
	pt(adec) = lda;
	no(adec)++;
	pt(ndec) = ldn;
	no(ndec)++;
	if (last(le)) {
	       son(ntestx) = clda;
	       bro(clda) = ldn;
	       clearlast(clda);
	       bro(ldn) = ntestx;
	       setlast(ldn);
	} else {
	       son(ntestx) = ldn;
	       bro(ldn) = clda;
	       clearlast(ldn);
	       bro(clda) = ntestx;
	       setlast(clda);
	}
	pos = position(test);
	*pos = ntestx;
	kill_exp(test, nilexp);
	setname(incr, top_tag);
	kill_exp(bro(son(incr)), nilexp);
	kill_exp(son(incr), nilexp);
	son(incr) = nilexp;
}


void
remove_incr2(exp adec, exp test, exp incr, int mult)
{
	exp le = limexp(test, son(incr));
	exp *pos;
	exp init = son(adec);
	exp bdy = bro(init);
	exp ninit, ldn, ntestx, lda, clda;
        if (name(le) != val_tag && !remove_unused_index_counters) {
           return;
	}
	lda = getexp(f_pointer(long_to_al(shape_align(sh(son(adec))))), nilexp,
		     1, adec, pt(adec), 0, 0, name_tag);
	clda = getexp(/*sh(son(adec))*/slongsh, nilexp, 0, lda, nilexp, 0, 0,
		      cont_tag);
        if (name(le) == val_tag) {
		ninit = limconst(son(init), mult*no(le));
		ldn = ninit;
	} else {
		exp nb;
		ninit =  limmult(son(init), le, mult);
		nb = getexp(sh(bdy), adec, 1, ninit, nilexp, 0, 0, ident_tag);
		bro(ninit) = bdy;
		clearlast(ninit);
		bro(bdy) = nb;
		setlast(bdy);
		bro(init) = nb;
		ninit = nb;
		ldn = getexp(sh(son(ninit)), nilexp, 0, ninit, pt(ninit), 0, 0,
			     name_tag);
		pt(ninit) = ldn;
		no(ninit)++;
	}
	ntestx = getexp(sh(test), bro(test), last(test), nilexp, pt(test),
			props(test), no(test), name(test));
	bro(lda) = clda;
	pt(adec) = lda;
	no(adec)++;
	if (last(le)) {
	       son(ntestx) = clda;
	       bro(clda) = ldn;
	       clearlast(clda);
	       bro(ldn) = ntestx;
	       setlast(ldn);
	} else {
	       son(ntestx) = ldn;
	       bro(ldn) = clda;
	       clearlast(ldn);
	       bro(clda) = ntestx;
	       setlast(clda);
	}
	pos = position(test);
	*pos = ntestx;
	kill_exp(test, nilexp);
	setname(incr, top_tag);
	kill_exp(bro(son(incr)), nilexp);
	kill_exp(son(incr), nilexp);
	son(incr) = nilexp;
}


int
use_in(exp w, exp ld)
{
	switch (name(w)) {
	case name_tag:
		return (son(w) == son(ld) && no(w) == no(ld));
	case ass_tag: {
		int z = use_in(bro(son(w)), ld);
		if (z != 0) {
			return z;
		}
		if (name(son(w)) == name_tag && son(son(w)) == son(ld) &&
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
		exp z = son(w);
		if (z == nilexp) {
			return 0;
		}
		for (;;) {
			int a = use_in(z, ld);
			if (a != 0 || last(z)) {
				return a;
			}
			z = bro(z);
		}
	}
	}
}


int
suitable_test(exp tests, exp incrld, exp loop)
{
	/* is test such that one can remove the increment ? */
	exp t, p;
	exp decx = son(incrld);
	exp v;
	if (tests == nilexp || no(tests) != 1 || bro(tests) != nilexp) {
		return 0;
	}
	t = son(tests);
	v = limexp(t, incrld);
	if (name(v) != val_tag &&
	    (!invariant(v, assign_alias) || maybe_incr(v))) {
		return 0;
	}
	while (t != loop && last(t)) {
		t= bro(t);
	}
	if (t != loop) {
		return 0;
	}
	while (name(t) != proc_tag && t != decx) {
		exp b = bro(t);
		if (!last(t)) {
			for (p = pt(decx); p != nilexp; p = pt(p)) {
				if (intnl_to(b, p) && use_in(b, incrld) == 1) {
					return 0;
				}
			}
		}
		t = b;
	}
	return 1;
}


int
do_one_rep(exp loop)
{
	exp body = bro(son(bro(son(loop))));
	exp z;
	int res =0;
	exp xincrs;
	Assert(name(loop) == rep_tag);
	incrs = nilexp;
	alteredset=nilexp;
	assign_alias = false;
	jump_out = false;
	scan_for_incr(body, loop, collect_incrs);
	if (!jump_out && name(sh(loop)) == tophd) {
		for (z = alteredset; z != nilexp; z = bro(z)) {
			/* look to see if var assigned to in loop can be
			 * locally declared ie Rep f(z) => Var x := cont(z) in
			 * Rep f(x); z = cont x ni; ? only worth while if z is
			 * global if z is local only worthwhile if it isnt
			 * being allocated in reg anyway
			 */
			exp a = son(z);

			if (name(a) == name_tag &&
			    (isglob(son(a)) || !isvar(son(a))) &&
			    (props(son(a)) & subvar) == 0 &&
			    (!assign_alias ||
			     (isvar(son(a)) && iscaonly(son(a)))) &&
			    !intnl_to(body, son(a))) {
				exp p;
				exp dc = son(a);
				shape shcont;
				int const_init = !isglob(dc) &&
				    (name(son(dc)) == clear_tag ||
				     name(son(dc)) == val_tag ||
				     name(son(dc)) == real_tag ||
				     (name(son(dc)) == name_tag &&
				      !isvar(son(son(dc)))));
				for (p = pt(son(a)); p != nilexp; p = pt(p)) {
#ifdef NEWDIAGS
					int inb;
					if (isdiaginfo(p)) {
						continue;
					}
					inb = intnl_to(body, p);
#else
					int inb = intnl_to(body, p);
#endif
					if (!inb) {
						const_init = 0;
						continue;
					}
					if (no(a) != no(p)) {
						break;
					}
					if (last(p) &&
					    name(bro(p)) == cont_tag) {
						shcont = sh(bro(p));
						continue;
					}
					if (!last(p) && last(bro(p)) &&
					    name(bro(bro(p))) == ass_tag) {
						shcont = sh(bro(p));
						continue;
					}
					break;
				}
				if (p != nilexp) {
					continue;
				}
				/* only uses of this id is cont or assign in
				 * body */
				if (!isvar(son(a))) {
					/*check to see whether underlying id is
					 * used in loop*/
					exp w = son(son(a));
					const_init = 0;
					if (name(w) == reff_tag) {
						w = son(w);
					}
					Assert(name(w) == addptr_tag);
					/* uses of underlying var */
					w = pt(son(son(w)));

					for (; w != nilexp; w= pt(w)) {
						if (intnl_to(body, w)) {
							break;
						}
					}
					if (w != nilexp) {
						continue;
					}
				}
				if (const_init) {
					/* can reduce scope of altered
					 * variable */
					exp dc= son(a);
					exp bd = bro(son(dc));
					if (bd != loop &&
					    name(dc) == ident_tag) {
						exp brodc = bro(dc);
						int ldc = last(dc);
						exp broloop = bro(loop);
						int lloop = last(loop);
						exp *pos = position(dc);
						*pos = bd;
						/* replace original dec with
						 * its body.*/
						bro(bd) = brodc;
						if (ldc) {
							setlast(bd);
						} else {
							clearlast(bd);
						}
						/* ... and set bro to that of
						 * dec */
						pos = position(loop);
						/* replace loop by dec */
						*pos = dc;

						bro(dc) = broloop;
						if (lloop) {
							setlast(dc);
						} else {
							clearlast(dc);
						}
						/* ... set bro to that of loop,
						 * ... */
						bro(son(dc)) = loop;
						bro(loop) = dc;
						setlast(loop);
						/* ... and make loop be body of
						 * dec */
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
	while (xincrs != nilexp) {
		exp incrld = son(son(xincrs));
		exp nincr = bro(xincrs);
		int ou;
		exp adec = nilexp;
		int elsize;
		exp incrdec = son(incrld);
		tests = nilexp;
		addptrs = nilexp;
		stride = 0;
		ou=find_common_index(incrld, body, collect_loopthings);
		if (stride < 1) {
			exp t;
			int i;
			int nap = 0;
			tests=nilexp;
			addptrs=nilexp;
			stride = 0;
			ou = find_pointer_opt(incrld, body, collect_loopthings);
			for (i = 0, t = addptrs; t != nilexp; i++, t = bro(t)) {
				nap += no(t);
			}
			if (i >= 3 && i == nap) {
				/* don't replace all addptrs if too many vars
				 * required ... */
				if (stride > 1) {
					/* ... but can still scale index */
					scale_loopid(loop, addptrs, xincrs);
					/* only other uses besides addptr &
					 * test are in increment */
					if (ou == 2 &&
					    suitable_test(tests,
							  son(son(xincrs)),
							  loop)) {
						remove_incr2(bro(loop),
							     son(tests),
							     son(xincrs),
							     stride);
					}
				}
				ou += nap;
				addptrs = nilexp;
			}
			while (addptrs != nilexp) {
				int rw = weaken(loop, addptrs, xincrs);
				exp next = bro(addptrs);
				if (rw != 0) {
					res = true;
					/* really father put in by weaken */
					adec = bro(loop);
					elsize = arraystep;
				} else {
					SET(elsize);
					ou+=no(addptrs);
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
				addptrs=next;
			}

			/* only other uses (besides addptr & test) of loop var
			 * is in increment */
			if (ou == 2 && adec != nilexp &&
			    suitable_test(tests, incrld, loop) &&
			    multiplier != 0 && remove_unused_counters) {
				remove_incr(adec, son(tests), son(xincrs),
					    elsize);
			}
		} else if (stride > 1) {
			scale_loopid(loop, addptrs, xincrs);
			/* only other uses besides addptr & test are in
			 * increment*/
			if (ou == 2 &&
			    suitable_test(tests, son(son(xincrs)), loop)) {
				remove_incr2(bro(loop), son(tests), son(xincrs),
					     stride);
			}
		}

		/* avoid n-squared factor */
		if (res && no(incrdec) < 10) {
			IGNORE refactor_id(incrdec, bro(son(incrdec)));
		}

		xincrs=nincr;
	}
	while (incrs != nilexp) {
		exp z = bro(incrs);
		retcell(incrs);
		incrs = z;
	}
	while (alteredset != nilexp) {
		exp z = bro(alteredset);
		retcell(son(alteredset));
		retcell(alteredset);
		alteredset = z;
	}
	return res;
}


void
order_loops(exp reps)
{
	/* start at outer loop ?! */
	if ((props(reps) & 0x80) == 0) {
		if (bro(reps) != nilexp) {
			order_loops(bro(reps));
		}
		if (son(reps) != nilexp && name(son(reps)) == rep_tag &&
		    no(reps) < max_loop_depth) {
			exp loop = son(reps);
			/* ALTERATION #2 - does not effect C */
			if (name(son(loop)) != top_tag) {
				/* make loop(st, b) into seq((st),
				 * loop(make_top, b)) analysis assumes
				 * son(loop) = top! */
				exp st = son(loop);
				exp b = bro(st);
				exp * pos = ifc_ptr_position(loop);
				exp mt = getexp(f_top, b, 0, nilexp, nilexp, 0,
						0, top_tag);
				exp sl = getexp(f_top, loop, 0 ,st, nilexp, 0,
						0, 0);
				exp s = getexp(sh(loop), bro(loop), last(loop),
					       sl, nilexp, 0, 0, seq_tag);

				bro(st) = sl;
				setlast(st);
				son(loop) = mt;
				bro(loop) = s;
				setlast(loop);
				*pos = s;
			}
			IGNORE do_one_rep(loop);
		}
		props(reps) |=0x80;
	}
}


void
forall_opt(void)
{
	exp reps = get_repeats();
	while (reps != nilexp) {
		order_loops(reps);
		reps = pt(reps);
	}
	if (optim & OPTIM_LOOPCONSTS) {
		optim &= ~OPTIM_FORALLS;
		/* try constant extraction again */
		repeat_consts();
	}
}
