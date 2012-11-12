/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*******************************************************************

		needscan.c

	Defines the scan through a program which reorganises it so that all
arguments of operations are suitable for later code-production. The procedure
scan evaluates the register requirements of an exp. The exps are produced
from the decoding process and the various exp -> exp transformations  in
the proc independent (common to other  translators)

******************************************************************/

#include <assert.h>

#include <shared/check.h>

#include "config.h"

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shapemacs.h>
#include <construct/flpt.h>
#include <construct/install_fns.h>
#include <construct/flags.h>

#include <refactor/const.h>
#include <reader/externs.h>
#include <refactor/optimise.h>

#include "exptypes.h"
#include "expmacs.h"
#include "new_tags.h"
#include "proctypes.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "tempdecs.h"
#include "special.h"
#include "regmacs.h"
#include "muldvrem.h"
#include "translat.h"
#include "comment.h"
#include "proc.h"
#include "frames.h"
#include "extratags.h"
#include "needscan.h"


/* used by scan to set initial parameter positions */
extern alignment long_to_al(unsigned long);
extern int specialopt(exp);

extern long notbranch[];	/* in makecode.c */
extern int nexps;

extern procrec *cpr;

static int stparam;		/* Size of parameter list in bits */
static int fixparam;		/* Next available place for param */
static int fltparam;

static bool rscope_level = 0;
static bool nonevis = 1;
static int callerfortr;

bool gen_call;
bool has_tail_call;

int maxfix, maxfloat;		/* the maximum number of t-regs */


/* advance declaration of scan */
needs scan(exp *, exp **);


/*
	needs defined in proctypes.h.

	This is a structure which has two integers giving the number of
fixed and floating point registers required to contain live values in
the expression parameters. A further field prop is used for various
flags about certain forms of exp (mainly idents and procs). The maxargs
field gives the maximum size in bits for the parameters of all the
procs called in the exp. The needs of a proc body are preserved in the
needs field of the procrec (see proctypes.h).
*/



/* return ptrexp pointing to e */
exp *ptr_position
(exp e)
{
  exp *res;
  exp dad = father(e);
  exp sib = son(dad);

  if (sib == e)
  {
    res = &son(dad);
  }
  else
  {
    while (bro(sib)!= e)
    {
      sib = bro(sib);
    }
    res = &bro(sib);
  }

  return res;
}



/***************************************************************
		cca

This procedure effectively inserts a new declaration into an exp. This
is used to stop a procedure requiring more than the available number of
registers.
****************************************************************/
void tidy_ident(exp);


void cca
(exp **to, exp *x)
{
  if (name((**to)) ==diagnose_tag)
  {
      *to = & (son((**to)));
  }
  if (x == (*to))
  {
    exp def = *(x);

    /* replace by  Let tg = def In tg Ni */
    exp id = getexp(sh(def), bro(def), last(def), def, nilexp,
		    0, 1, ident_tag);
    exp tg = getexp(sh(def), id, 1, id, nilexp,
		    0, 0, name_tag);

    pt(id) = tg;		/* use of tag */
    bro(def) = tg;		/* bro(def) is body of Let = tg */
    clearlast(def);
    *(x) = id;			/* replace pointer to x by Let */
    return;
  }
  else
  {				/* replace by Let tg = def In ato/def = tg Ni */
    exp def = *(x);
    exp ato = *(*to);
    exp id = getexp(sh(ato), bro(ato), last(ato), def, nilexp,
		    0, 1, ident_tag);
    exp tg = getexp(sh(def), bro(def), last(def), id, nilexp,
		    0, 0, name_tag);

    pt(id) = tg;		/* use of tg */
    bro(def) = ato;		/* ato is body of Let */
    clearlast(def);
    bro(ato) = id;		/* its father is Let */
    setlast(ato);
    *(*to) = id;		/* replace pointer to 'to' by Let */
    *(x) = tg;			/* replace use of x by tg */
    *to = &bro(def);		/* later replacement to same 'to' will be at
				 * body of Let */
    return;
  }
}

needs onefix = {1, 0, 0, 0};	/* needs one fix pt reg */
needs twofix = {2, 0, 0, 0};	/* needs 2 fix pt regs */
needs onefloat = {0, 1, 0, 0};	/* needs 1 flt pt regs */
needs zeroneeds = {0, 0, 0, 0};	/* has no needs */


#if 0		/* +++ optimise sharing of regs for idents */
bool subvar_use
(exp uses)
{				/* check to see if any uses of id is
				 * initialiser to subvar dec */
  for (; uses != nilexp; uses = pt(uses))
  {
    if (last(uses) && name(bro(uses)) == cont_tag)
    {
      exp c = bro(uses);

      if (!last(c) && last(bro(c)) && name(bro(bro(c))) == ident_tag)
      {
	exp id = bro(bro(c));

	if ((props(id) & subvar)!= 0 && (props(id) & inanyreg)!= 0)
	  return 1;
      }
    }
  }
  return 0;
}
#endif


/* this gives the needs for manipulating a value of shape s */
needs shapeneeds
(shape s)
{
  if (is_floating(name(s)))
    return onefloat;
  else
  {
    if (valregable(s))
    {
      return onefix;
    }
    else
    {
      /* if the shape does not fit into a reg, needs two fixed regs for moving */
      return twofix;
    }
  }
}


/*
  Transform a non-bit offset into a bit offset.
  (borrowed from trans386)
*/
static void make_bitfield_offset
(exp e, exp pe, int spe, shape sha) {
  exp omul;
  exp val8;
  if (name(e) == val_tag) {
    no(e)*= 8;
    return;
  }
  omul = getexp(sha, bro(e), (int)(last(e)), e, nilexp, 0, 0, offset_mult_tag);
  val8 = getexp(slongsh, omul, 1, nilexp, nilexp, 0, 8, val_tag);
  clearlast(e);
  setbro(e, val8);
  if (spe) {
    son(pe) = omul;
  }
  else{
    bro(pe) = omul;
  }
  return;
}


/*
 * these are basicly the expressions which cannot be accessed by a simple
 * load or store instruction
 */
bool complex
(exp e)
{				/* these are basically the expressions which
				 * cannot be accessed by a simple load or
				 * store instruction */
  if (name(e) == name_tag ||
     (name(e) == cont_tag && name(son(e)) == name_tag &&
       isvar(son(son(e))))
      || name(e) == val_tag || name(e) == real_tag)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void change_to_var
(exp e)
{
	/* change identity to variable definition */
	exp p = pt(e);
	shape ns;
	assert(name(e) ==ident_tag && !isvar(e));
	setvar(e);
	setcaonly(e);
	ns = f_pointer(f_alignment(sh(son(e))));
	while (p != nilexp) {
		exp * pos = ptr_position(p);
		exp ncont = getexp(sh(p), bro(p), last(p), p, nilexp, 0, 0,
					cont_tag);
		bro(p) = ncont; setlast(p);
		sh(p) = ns;
		*pos = ncont;
		p = pt(p);
	}
}

void change_names
(exp f, exp t, exp except)
{
	/* replace uses of ident f (!= except) to uses of t */
	exp py = pt(f);
	assert(name(f) ==ident_tag && name(t) ==ident_tag && name(except) ==name_tag);
	while (py != nilexp) {
		exp ppy = pt(py);
		if (py != except) {
			son(py) = t; /* change f to t */
			pt(py) = pt(t);
			pt(t) = py;
			no(t)++;  /* maintain usage */
		}
		py = ppy;
	}
}


void tidy_ident
(exp e)
{
	/* replace Var/Id x = Var y = e1 in { e2; contents(y)} in e3;
	   by Var x = e1 in { e2/(y=>x); e3}
	   replace Var/Id x = Id y = e1 in {e2; y} in e3
	   by Var/Id x = e1 in { e2/y=>(cont)x; e3}
	*/
	exp init; exp bdyinit; exp idy;
	exp e1;
	exp e3;
	assert(name(e) ==ident_tag);
	init = son(e);
	e3 = bro(init);
	if (name(init)!= ident_tag || isparam(e)) { return ;}
	tidy_ident(init);
	e1 = son(init);
	bdyinit = bro(e1);
	if (!isvar(init)) {
	  if (name(bdyinit) == seq_tag) {
	    	exp idy = bro(son(bdyinit));
		exp broe3;
		bool laste3;
		if (name(idy)!= name_tag || son(idy)!= init ||
			no(idy)!=0 ||
			shape_size(sh(idy))!= shape_size(sh(e1)) ||
			shape_align(sh(idy))!= shape_align(sh(e1))) {
		    return;
		}
		if (isvar(e)) {
			change_to_var(init);
		}
		change_names(init, e, idy);

		broe3 = bro(e3);
		laste3 = last(e3);
		bro(son(bdyinit)) = e3;
		bro(e3) = bdyinit; setlast(bdyinit);
				/* bdyinit is now { e2/(y=>x); e3} */
		bro(bdyinit) = broe3;
		if (laste3) { setlast(bdyinit); }
		else { clearlast(bdyinit); }
		son(e) = e1;  /* bro(e1) is bdyinit */
		return;
	  }
	  else
	  if (name(bdyinit) == name_tag && (idy = son(bdyinit)) ==init
		&& no(idy) ==0 &&
		shape_size(sh(idy)) == shape_size(sh(e1)) &&
		shape_align(sh(idy)) == shape_align(sh(e1))) {
		/* form is Var/Id x = Id y = e1 in y in e3
			=> Var x = e1 in e3 */
		bro(e1) = e3;
		son(e) = e1;
	  }
	  else return;
	}
	else {
	  if (name(bdyinit) == seq_tag) {
		exp cy = bro(son(bdyinit));
		exp broe3;
		bool laste3;
		if (name(cy)!= cont_tag) return;

		idy = son(cy);
		if (name(idy)!= name_tag || no(idy)!= 0 ||
			son(idy)!= init ||
			shape_size(sh(cy))!= shape_size(sh(e1)) ||
			shape_align(sh(cy))!= shape_align(sh(e1))) {
			return;
		}
		if (!isvar(e)) {
			change_to_var(e);
			if (isvis(init)) { setvis(e); }
			if (!iscaonly(init)) { ClearCaonly(e); }
		}

		change_names(init,e,idy);

		broe3 = bro(e3);
		laste3 = last(e3);
		bro(son(bdyinit)) = e3;
		bro(e3) = bdyinit; setlast(bdyinit);
				/* bdyinit is now { e2/(y=>x); e3} */
		bro(bdyinit) = broe3;
		if (laste3) { setlast(bdyinit); }
		else { clearlast(bdyinit); }
		son(e) = e1;  /* bro(e1) is bdyinit */
		return;
	  }
	  else
	  if (name(bdyinit) == cont_tag) {
		exp cy =  bro(son(bdyinit));
		idy = son(cy);
		if (name(idy)!= name_tag || no(idy)!= 0 ||
			son(idy)!= init ||
			shape_size(sh(cy))!= shape_size(sh(e1)) ||
			shape_align(sh(cy))!= shape_align(sh(e1))) {
			return;
		}
		/* form is Var x = Var y = e1 in cont(y) in e3
			=> Var x = e1 in e3 */
		if (!isvar(e)) {
			change_to_var(e);
			if (isvis(init)) { setvis(e); }
			if (!iscaonly(init)) { ClearCaonly(e); }
		}
		bro(e1) = e3;
		son(e) = e1;
	  }
	  else return;
	}

}


int scan_cond
(exp * e, exp outer_id)
{

	exp ste = *e;
	exp first = son(ste);
	exp labst = bro(first);
	exp second = bro(son(labst));

	assert(name(ste) ==cond_tag);

	if (name(second) ==top_tag && name(sh(first)) ==bothd && no(son(labst)) ==1
		&& name(first) ==seq_tag && name(bro(son(first))) == goto_tag) {
		/* cond is { ... test(L); ? ; goto X | L:make_top}
			if ? empty can replace by seq { ... not-test(X); make_top }
		*/
		exp l = son(son(first));
		while (!last(l)) { l = bro(l); }
		while (name(l) ==seq_tag) { l = bro(son(l)); }
		if (name(l) ==test_tag && pt(l) ==labst) {
		   settest_number(l, notbranch[test_number(l)]);
		   pt(l) = pt(bro(son(first)));
		   bro(son(first)) = second;
		   bro(second) = first; setlast(second);
		   bro(first) = bro(ste);
		   if (last(ste)) { setlast(first);} else { clearlast(first); }
		   *e = first;
		   return 1;
		}
		else return 0;
	}


	if (name(first) == seq_tag && name(second) == cond_tag
	    && no(son(labst)) == 1
	    && name(son(son(first))) == test_tag
	    && pt(son(son(first))) == labst
	    && name(son(second)) == seq_tag
	    && name(son(son(son(second)))) == test_tag) {
				/* cond is ( seq (test to L;....|
				   L:cond(seq(test;...),...) ) ..... */
	  exp test1 = son(son(first));
	  exp test2 = son(son(son(second)));
	  exp op11 = son(test1);
	  exp op21 = bro(op11);
	  exp op12 = son(test2);
	  exp op22 = bro(op12);
	  bool c1 = complex(op11);
	  bool c2 = complex(op21);

	  if (c1 && eq_exp(op11, op12)) {
				/* ....if first operands of tests are
				   same, identify them */
	    exp newid = getexp(sh(ste), bro(ste), last(ste), op11, nilexp,
		0, 2, ident_tag);
	    exp tg1 = getexp(sh(op11), op21, 0, newid, nilexp, 0, 0, name_tag);
	    exp tg2 = getexp(sh(op12), op22, 0, newid, nilexp, 0, 0, name_tag);

	    pt(newid) = tg1;
	    pt (tg1) = tg2;	/* uses of newid */
	    bro (op11) = ste; clearlast (op11);/* body of newid */
	    /* forget son test2 = son test1 */
	    bro(ste) = newid;
	    setlast (ste);	/* father body = newid */
	    son(test1) = tg1;
	    son (test2) = tg2;	/* relace 1st operands of test */
	    if (!complex(op21)) {
		/* if the second operand of 1st test is simple, then identification
			could go in a t-teg (!!!NB overloading of inlined flag!!!).... */
		setinlined(newid);
	    }
	    kill_exp(op12, op12);
	    *(e) = newid;
	    if (scan_cond(&bro(son(labst)), newid) == 2 && complex(op22)) {
		/* ... however a further use of identification means that
		   the second operand of the second test must also be simple */
		clearinlined(newid);
	    }
	    return 1;
	  }
	  else
	  if (c2 && eq_exp(op21, op22)) {
				/* ....if second operands of tests are
				   same, identify them */

	      exp newid = getexp(sh(ste), bro(ste), last(ste), op21,
		  nilexp, 0, 2, ident_tag);
	      exp tg1 = getexp(sh(op21), test1, 1,
		  newid, nilexp, 0, 0, name_tag);
	      exp tg2 = getexp(sh(op22), test2, 1, newid, nilexp,
		  0, 0, name_tag);

	      pt(newid) = tg1;
	      pt (tg1) = tg2;	/* uses of newid */
	      bro(op21) = ste; clearlast(op21);
	      /* body of newid */
	      /* forget bro son test2 = bro son test1 */
	      bro(ste) = newid;
	      setlast (ste);	/* father body = newid */
	      bro(op11) = tg1;
	      bro(op12) = tg2;
	      if (!complex(op11)) { setinlined(newid); }
	      kill_exp(op22, op22);
	      /* relace 2nd operands of test */
	      *(e) = newid;
	      if (scan_cond(&bro(son(labst)), newid) == 2 && complex(op12)) {
			clearinlined(newid);
	      }
	      return 1;
	  }
	  else
	  if (name(op12)!= name_tag
		  && name(op11) == name_tag
		  && son(op11) == outer_id
		  && eq_exp(son(outer_id), op12)
		) {		/* 1st param of test1 is already identified with
				   1st param of  test2 */
		exp tg = getexp(sh(op12), op22, 0, outer_id,
		    pt(outer_id), 0, 0, name_tag);
		pt(outer_id) = tg;
		no(outer_id) += 1;
		if (complex(op21)) { clearinlined(outer_id); }
		/* update usage of ident */
		son(test2) = tg;
		kill_exp(op12, op12);
		if (scan_cond(&bro(son(labst)), outer_id) == 2 && complex(op22)) {
			clearinlined(outer_id);
		}
		return 2;
	      }


	}
	return 0;
}

/*
 * does the scan on commutative and associative operations and may perform
 * various transformations allowed by these properties
 */
needs likeplus
(exp * e, exp ** at)
{
  needs a1;
  needs a2;
  prop pc;
  exp *br = &son(*e);
  exp prev;
  bool commuted = 0;
  exp dad = *(e);

  a1 = scan(br, at);
  /* scan the first operand - won't be a val_tag */

  do {
    exp *prevbr;
    prevbr = br;
    prev = *(br);
    br = &bro(prev);
    a2 = scan(br, at);
    /* scan the next operand ... */
    if (name(*(br))!= val_tag) {
      a1.floatneeds = MAX_OF(a1.floatneeds, a2.floatneeds);
      pc = a2.propsneeds & hasproccall;
      if (a2.fixneeds < maxfix && pc == 0)
	/* ... its evaluation  will not disturb the accumulated result */
      {
	a1.fixneeds = MAX_OF(a1.fixneeds, a2.fixneeds + 1);
	a1.propsneeds = a1.propsneeds | a2.propsneeds;
      }
      else if (a1.fixneeds < maxfix && (a1.propsneeds & hasproccall) == 0 && !commuted)
      {

	/*
	 * ...its evaluation will call a proc, so put it first
	 */
	exp op1 = son(dad);
	exp cop = *(br);
	bool lcop = last(cop);
	bro(prev) = bro(cop);
	if (lcop)
	  setlast(prev);
	bro(cop) = op1;
	clearlast(cop);
	son(dad) = cop;
	br = (prev == op1)? &bro(cop): prevbr;
	op1->commuted=1;
	cop->commuted=1;
	commuted = 1;
	a1.fixneeds = MAX_OF(a2.fixneeds, a1.fixneeds + 1);
	a1.propsneeds |= a2.propsneeds;
	a1.maxargs = MAX_OF(a1.maxargs, a2.maxargs);
      }
      else
      {

	/*
	 * evaluation would disturb accumulated result, so replace it by a
	 * newly declared tag
	 */
	FULLCOMMENT("likeplus: insert ident");
	cca(at, br);
	a1.fixneeds = MAX_OF(a1.fixneeds, 2);
	a1.propsneeds = a1.propsneeds | morefix | (pc << 1);
	a1.maxargs = MAX_OF(a1.maxargs, a2.maxargs);
      }
    }
    else
    {
      FULLCOMMENT("likeplus: val_tag");
    }
  } while (!last(*(br)));
#if 1           			/* exception handling regs */
  if (!optop(*(e)))
  {
    if (a1.fixneeds < 4)
      a1.fixneeds = 4;
  }
#endif

  return a1;
}


/* scan non-commutative fix pt operation */
needs likediv
(exp * e, exp ** at)
{
  needs l;
  needs r;
  prop pc;
  exp *arg = &son(*e);

  l = scan(arg, at);
  /* scan 1st operand */
  arg = &bro(*arg);
  r = scan(arg, at);
  /* scan second operand ... */
  l.floatneeds = MAX_OF(l.floatneeds, r.floatneeds);

  pc = r.propsneeds & hasproccall;
  if (r.fixneeds < maxfix && pc == 0)
  {
    /* fits into registers */
    l.fixneeds = MAX_OF(l.fixneeds, r.fixneeds + 1);
    l.propsneeds = l.propsneeds | r.propsneeds;
    FULLCOMMENT2("likediv: r.fixneeds(%d) < maxfix(%d) && pc == 0", r.fixneeds, maxfix);
  }
  else
  {
    /* requires new declaration of second operand */
    cca(at, arg);
    l.fixneeds = MAX_OF(l.fixneeds, 1);
    l.propsneeds = l.propsneeds | morefix | (pc << 1);
    l.maxargs = MAX_OF(l.maxargs, r.maxargs);
    FULLCOMMENT2("likediv: insert decl r.fixneeds=%d maxfix=%d", r.fixneeds, maxfix);
  }
#if 1				/* exception handling regs (from mips) */
  if (!optop(*(e)))
  {
    if (l.fixneeds < 4)
      l.fixneeds = 4;
  }
#endif
  return l;
}

needs fpop
(exp * e, exp ** at)
{
  /* scans diadic floating point operation  */
  needs l;
  needs r;
  exp op = *(e);
  prop pcr, pcl;
  exp *arg = &son(op);

  l = scan(arg, at);
  arg = &bro(*arg);
  r = scan(arg, at);
  l.fixneeds = MAX_OF(l.fixneeds, r.fixneeds);
  pcr = r.propsneeds & hasproccall;
  pcl = l.propsneeds & hasproccall;

  if (!optop(*(e)))
  {
    if (l.fixneeds < 2)
      l.fixneeds = 2;
  }

#if use_long_double
    if (name(sh(son(op))) ==doublehd)
    {
	ClearRev(op);
	arg=&son(op);
	if (!is_o(name(*arg)) || pcl)cca(at,arg);
	arg = &bro(son(op));
	if (!is_o(name(*arg)) || pcr)cca(at, arg);
	l.floatneeds = MAX_OF(l.floatneeds, r.floatneeds);
	l.maxargs = MAX_OF(l.maxargs, r.maxargs);
	pnset(l,hasproccall);
	return l;
    }
#endif

  if (r.floatneeds <= l.floatneeds && r.floatneeds < maxfloat && pcr == 0)
  {
    l.floatneeds = MAX_OF(2, MAX_OF(l.floatneeds, r.floatneeds + 1));
    l.propsneeds = l.propsneeds | r.propsneeds;
    ClearRev(op);
  }
  else if (pcl == 0 && l.floatneeds <= r.floatneeds && l.floatneeds < maxfloat)
  {
    l.floatneeds = MAX_OF(2, MAX_OF(r.floatneeds, l.floatneeds + 1));
    l.propsneeds = l.propsneeds | r.propsneeds;
    SetRev(op);
  }
  else if (r.floatneeds < maxfloat && pcr == 0)
  {
    l.floatneeds = MAX_OF(2, MAX_OF(l.floatneeds, r.floatneeds + 1));
    l.propsneeds = l.propsneeds | r.propsneeds;
    ClearRev(op);
  }
  else
  {
    cca(at, arg);
    ClearRev(op);
    l.floatneeds = MAX_OF(l.floatneeds, 2);
    l.propsneeds = l.propsneeds | morefloat | (pcr << 1);
    l.maxargs = MAX_OF(l.maxargs, r.maxargs);
  }
  return l;
}

/**********************************************************************
	maxneeds

Calculates a needs value. Each element of which is the maximum of the
corresponding elements in the two parameter needs
**********************************************************************/

needs maxneeds
(needs a, needs b)
{
  needs an;

  an.fixneeds = MAX_OF(a.fixneeds, b.fixneeds);
  an.floatneeds = MAX_OF(a.floatneeds, b.floatneeds);
  an.maxargs = MAX_OF(a.maxargs, b.maxargs);
  an.propsneeds = a.propsneeds | b.propsneeds;
  return an;
}

/**********************************************************************
	maxtup

**********************************************************************/

needs maxtup
(exp e, exp ** at)
{				/* calculates the needs of a tuple of
				 * expressions; any new declarations required
				 * by a component expression will replace the
				 * component expression */
  exp *stat = &son(e);
  needs an;

  an = zeroneeds;
  while (an = maxneeds(an, scan(stat, at)), !last(*stat))
  {
    stat = &bro(*stat);
  }
  return an;
}

bool unchanged
(exp usedname, exp ident)

 /*
  * finds if usedname is only used in cont operation or as result of ident
  * i.e. value of name is unchanged over its scope
  */
{
  exp uses = pt(usedname);

  while (uses != nilexp)
  {
    if (intnl_to(ident, uses))
    {
      if (!last(uses) || name(bro(uses))!= cont_tag)
      {
	exp z = uses;

	while (z != ident)
	{
	  if (!last(z) ||
	     (name(bro(z))!= seq_tag && name(bro(z))!= ident_tag))
	  {
	    return 0;
	  }
	  z = bro(z);
	}
      }
    }
    uses = pt(uses);
  }
  return 1;
}



/*
 * The HPPA convention for delivering a struct from a procedure is is have an
 * extra pointer parameter in the proc; this means that there always must be
 * space in the calling work-space for the result struct whether or not the
 * value is used e.g. as in f(x); or f(x).a etc. This proc is part of the
 * mechanism to determine whether it is necessary to insert a dummy
 * declaration to ensure that this space exists.
 */
bool chase
(exp sel, exp * e)
{
  bool b = 0;
  exp *one;

  switch (name(*e))
  {
  case ident_tag:
  case seq_tag:
  case rep_tag:
  case labst_tag:
    {
      b = chase(sel, &bro(son(*e)));
      break;
    }

  case solve_tag:
  case cond_tag:
    {
      one = &son(*e);
      for (;;)
      {
	b |= chase(sel, one);
	if (last(*one))
	  break;
	one = &bro(*one);
      }
      break;
    }
  case field_tag:
    {
      if (chase(*e, &son(*e)))
      {
	/* inner field has been distributed */
	exp stare = *e;
	exp ss = son(stare);

	if (!last(stare))
	    clearlast(ss);
	bro(ss) = bro(stare);
	sh(ss) = sh(stare);
	*e = ss;
	return chase(sel, e);
      }				/* ... continue to default */
    }
  default:
    {
      if ((son(sel)!= *e) && (name(sh(*e))!= bothd))
      {				/* only change if not outer */
	exp stare = *e;
	exp newsel = getexp(sh(sel), bro(stare), last(stare), stare, nilexp,
			    props(sel), no(sel), name(sel));

	*e = newsel;
	bro(stare) = newsel;
	setlast(stare);
	b = 1;
      }
    }
  }
  if (b)
    sh(*e) = sh(sel);
  return b;
}




/********************************************************************
		scan

	This procedure works out register requirements of an exp. At each
call the fix field of the needs is the number of fixpnt registers required to
contain live values to evaluate this expression. This never exceeds maxfix
because if it would have, a new declaration is introduced in the exp tree
(similarly for floating regs and maxfloat). In these cases the prop field will
contain the bits morefix (or morefloat).
	Scan also works out various things concerned with proc calls.
The maxargs field contains the max size in bits of the space required for the
parameters of all the procedures called in the exp. An exp proc call
produces a hasproccall bit in the prop field, if this is transformed as part of
the definition of a new declaration the bit is replaced by a usesproccall. The
distinction is only used in unfolding nested proc calls; SPARC requires this to
be done statically. The condition that a proc exp is a leaf (i.e no proc calls)
is that its prop contains neither bit.
	If an ident exp is suitable, scan marks the props of ident with
either inreg or infreg bits to indicate that a t reg may be used for this tag.

	A thorough understanding of needs along with other procedures
that do switch(name(exp)) requires a knowledge of the meaning of the fields
of the exp in each case.

********************************************************************/


needs scan
(exp * e, exp ** at)
{

  /*
   * e is the expression to be scanned, at is the place to put any new decs .
   * NB order of recursive calls with same at is critical
   */
  exp ste = *(e);
  int nstare = name(ste);

  nexps++;

  /* ignore diagnostic information */
#if 0
  while (nstare == diag_tag || nstare == cscope_tag || nstare == fscope_tag)
  {
    e = &son(ste);
    ste = *(e);
    nstare = name(ste);
  }
#endif

  FULLCOMMENT1("scan: %s",(int)TAG_NAME(nstare));

  switch (nstare)
  {
  case 0:
    {
      return zeroneeds;
      /* NOTREACHED */
    }

  case compound_tag:
    {
      return maxtup(ste, at);
    }

  case nof_tag:
  case concatnof_tag:
  case ncopies_tag:
      {
	needs nl;
	bool cantdo;
	exp dad;
#if 1
      if (nstare==nof_tag && son(ste) ==nilexp)
	return zeroneeds;
#endif
	if (name(ste) ==ncopies_tag && name(son(ste))!=name_tag
	    && name(son(ste))!= val_tag) {
	  nl = scan(&son(*e), at);
	  cca(at, &son(*e));
	}
	else nl = maxtup(*(e), at);
	ste = *e;
	dad = father(ste);

	if (name(dad) ==compound_tag || name(dad) == nof_tag
	    || name(dad) == concatnof_tag)
	{
	  cantdo = 0;
	}
	else
	if (last(ste))
	{
	  if (name(bro(ste)) == ass_tag)
	  {
	    exp a = son(bro(ste));
	    cantdo = (name(a)!= name_tag || !isvar(son(a)));
	  }
	  else
	  {
	    cantdo = 1;
	  }
	}
	else
	if (last(bro(ste)))
	{
	  cantdo = (name(bro(bro(ste)))!= ident_tag);
	}
	else
	{
	  cantdo = 1;
	}

	if (cantdo)
	{
	  /* can only deal with tuples in simple assignment or identity */
	  int prps = (nl.propsneeds & hasproccall) << 1;
	  cca(at, ptr_position(ste));
	  nl = shapeneeds(sh(*(e)));
	  nl.propsneeds |= morefix;
	  nl.propsneeds |= prps;
	}

	if (nl.fixneeds <2)nl.fixneeds = 2;
	return nl;
      }

  case cond_tag:
    {
#if 1
      if (scan_cond(e, nilexp)!=0)
      {
	 return scan(e, at);
      }
      /* else goto next case */
#else
      exp first = son(ste);
      exp labst = bro(first);
      exp second = bro(son(labst));
      exp t, f, v;
      if (name(first) == seq_tag && name(second) == cond_tag &&
	  name(son(son(first))) == test_tag && pt(son(son(first))) == labst
	  && name(son(second)) == seq_tag
	  && name(son(son(son(second)))) == test_tag)
      {				/* cond is ( seq (test to L;....),
				 * L:cond(seq(test;...),...) ) ..... */
	exp test1 = son(son(first));
	exp test2 = son(son(son(second)));
	bool c1 = complex(son(test1));
	bool c2 = complex(bro(son(test1)));

	if (c1 && eq_exp(son(test1), son(test2)))
	  /* ....if first operands of tests are same, identify them */
	{
	  exp o21 = bro(son(test1));
	  exp o22 = bro(son(test2));
	  exp newid = getexp(sh(ste), bro(ste), last(ste), son(test1), nilexp,
			     0, 2, ident_tag);
	  exp tg1 = getexp(sh(son(test1)), o21, 0, newid, nilexp, 0, 0, name_tag);
	  exp tg2 = getexp(sh(son(test2)), o22, 0, newid, nilexp, 0, 0, name_tag);

	  pt(newid) = tg1;
	  pt(tg1) = tg2;	/* uses of newid */
	  bro(son(test1)) = ste;
	  clearlast(son(test1));/* body of newid */
	  /* forget son test2 = son test1 */
	  bro(ste) = newid;
	  setlast(ste);		/* father body = newid */
	  son(test1) = tg1;
	  son(test2) = tg2;	/* relace 1st operands of test */
	  *(e) = newid;
	  return scan(e, at);
	}
	else if (c2 && eq_exp(bro(son(test1)), bro(son(test2))))
	  /* ....if second operands of tests are same, identify them */
	{
	  exp o21 = bro(bro(son(test1)));
	  exp o22 = bro(bro(son(test2)));
	  exp newid = getexp(sh(ste), bro(ste), last(ste), bro(son(test1)),
			     nilexp, 0, 2, ident_tag);
	  exp tg1 = getexp(sh(bro(son(test1))), o21, 1,
			   newid, nilexp, 0, 0, name_tag);
	  exp tg2 = getexp(sh(bro(son(test2))), o22, 1, newid, nilexp,
			   0, 0, name_tag);

	  pt(newid) = tg1;
	  pt(tg1) = tg2;	/* uses of newid */
	  bro(bro(son(test1))) = ste;
	  clearlast(bro(son(test1)));
	  /* body of newid */
	  /* forget bro son test2 = bro son test1 */
	  bro(ste) = newid;
	  setlast(ste);		/* father body = newid */
	  bro(son(test1)) = tg1;
	  bro(son(test2)) = tg2;
	  /* relace 2st operands of test */
	  *(e) = newid;
	  return scan(e, at);
	}
	else if (name(son(test2))!= name_tag
		 && name(son(test1)) == name_tag &&
		 name(son(son(test1))) == ident_tag && !isvar(son(son(test1)))
		 && !isglob(son(son(test1)))
		 && eq_exp(son(son(son(test1))), son(test2))
	 )
	  /* 1st param of test1 is identified with 1st param of  test2 */
	{
	  exp tg = getexp(sh(son(test1)), bro(son(test2)), 0, son(son(test1)),
			  pt(son(son(test1))), 0, 0, name_tag);

	  pt(son(son(test1))) = tg;
	  no(son(son(test1))) += 1;
	  /* update usage of ident */
	  son(test2) = tg;
	  /* and then drop into next case */
	  FULLCOMMENT("scan() cond_tag: case 3");
	}

      }				/* else goto next case */
      FULLCOMMENT("scan() cond_tag: case 4");
#endif
    }
    /* FALLTHOUGH */


  case labst_tag:
  case rep_tag:
  case solve_tag:
    {
      exp *stat;
      exp *statat;
      needs an;

      stat = &son(*e);
      statat = stat;
      an = zeroneeds;
      while (an = maxneeds(an, scan(stat, &statat)),

	     !last(*(stat)))
      {
	stat = &bro(*stat);
	statat = stat;
      }
      if ((an.propsneeds & usesproccall)!= 0)
      {
	an.propsneeds |= hasproccall;
      }
      return an;
    }

/*********************************************************************
	ident

shape of exp is body,
son is def, brother of son is body,
ptr of ident exp is chain of uses
*********************************************************************/

  case ident_tag:
  {
     needs bdy;
     needs def;
     exp stare = *(e);
     exp *arg = &bro(son(stare));
     exp t = pt(stare), s;
     shape shdef = sh(son(stare));
     bool fxregble;
     bool flregble;
     bool old_nonevis = nonevis;

     if (pt(stare) == nilexp)
     {
	/* no uses, should have caonly flag and no var flag */
	setcaonly(stare);
	clearvar(stare);
     }
     if (diagnose && (name(shdef)!=bitfhd))
	setvis(stare);
/*     if (!iscaonly(stare) || all_variables_visible)*/
     if (isvar(stare) && (!iscaonly(stare) || all_variables_visible))
     {
	setvis(stare);
     }

     if (isparam(stare))
     {
	exp def = son(stare);
	shape shdef = sh(def);
	long sz = shape_size(shdef);
	if (name(son(stare))!= formal_callee_tag)
	{
	   assert(name(def) == clear_tag);
	   /* round up bytes and halfwords to full words */
	   if (sz>0 && sz<32)
	      sz=32;
	   /* round up small (i.e. < 64 byte) structues to two words */
	   else if (sz>32 && sz<64)
	      sz=64;

	   /* parameters must be properly aligned */
	   stparam = rounder(stparam+sz,sz);

	   fixparam = ARG0+ (stparam>>5) -1;
	   fltparam = 3*(3+ (stparam>>5)) +1;

	   if (valregable(shdef) && (shape_size(shdef) ==8 ||
				      shape_size(shdef) ==16))
	      /* Right align bytes and halfwords. */
	      no(def) = stparam-32+shape_size(shdef);
	   else
	      no(def) = stparam;

	   if (is_floating(name(shdef)))
	   {
	      if (fltparam < (3*8) +1)
	      {
		 /* floating paramter passed in registers */
		 props(def) = fltparam;
		 maxfloat--;
	      }
	      else
	      {
		 /* floating parameter passed by stack */
		 props(def) = 0;
	      }
	   }
	   else
	   {
	      if (fixparam<ARG3+1)
	      {
 	         /* param reg(s) free for the param */
		 props(def) = fixparam;
		 if (name(shdef)!=cpdhd && name(shdef)!=nofhd)
		    maxfix--;
	      }
	      else
 	         props(def) = 0;	/* Pass by stack */
	  }
       }
       else
       {
	  long alp = shape_align(shdef);
	  long n = rounder(callee_sz, alp);
	  no(def) = n;
	  callee_sz = rounder(n+sz,32);
       }
    }

    nonevis &= !isvis(stare);

    /* scan the body of the identity */
    bdy = scan(arg, &arg);

    /* scan the body-scope */
    arg = &son(stare);
    def = scan(arg, &arg);
    /* scan the initialisation of tag */

    nonevis = old_nonevis;
    t = son(stare);
    s = bro(t);
    fxregble = fixregable(stare);
    flregble = floatregable(stare);

    if (isparam(stare))
    {
       if (name(son(stare)) ==formal_callee_tag)
       {
	  /* IDENT is a callee parameter. */
	  no(stare) = R_NO_REG;
       }
       else
       {
	  bool is_aggregate = (name(shdef) ==cpdhd || name(shdef) ==nofhd ||
			       name(shdef) ==s64hd || name(shdef) ==u64hd);
	  if (!is_aggregate && !isvis(stare) &&
	      !isoutpar(stare) &&
	     ((bdy.propsneeds & anyproccall) == 0 ||
	      (!has_tail_call &&
		tempdec(stare,(fxregble && bdy.fixneeds <= 2) ||
	     	                (flregble && bdy.floatneeds <= 1)))))
	  {
	     int x = props(son(stare)); /* param reg it comes in, or else 0 */
	     if (x != 0 && (props(stare) & notparreg) == 0)
	     {
		/*
		 * use input param for leaf proc, unless it is R_RESULT=ARG0
		 * and we plan to use that specially
		 */
		no(stare) = x;
		if (flregble)
		{
		   /* props(stare) |= infreg_bits; */
		   no(stare) =0;
		}
		else
		{
		   props(stare) |= inreg_bits;
		}
	     }
	     else
	     if (fxregble && bdy.fixneeds<maxfix && (bdy.propsneeds & morefix) ==0)
	     {
		no(stare) = 0;
		props(stare) |= inreg_bits;
		bdy.fixneeds += 1;
	     }
	     else
	     if (flregble && bdy.floatneeds < maxfloat && 0 && (bdy.propsneeds & morefloat) == 0)
	     {
		no(stare) = 0;
		props(stare) |= infreg_bits;
		bdy.floatneeds += 1;
	     }
	     else
		no(stare) = R_NO_REG;
	  }
	  else
	     no(stare) = R_NO_REG;
       }
    }
    else
    {
       /* NON PARAMETER */
       assert(!isparam(*e));			/* handled above */
       if (!isvis(*e) && !isparam(*e) &&
	  (bdy.propsneeds & (anyproccall | uses_res_reg_bit)) == 0
	   && (fxregble /*|| flregble*/) &&
	  (name(t) == apply_tag ||
	   (name(s) == seq_tag && name(bro(son(s))) == res_tag &&
	     name(son(bro(son(s)))) == cont_tag && isvar(stare) &&
	     name(son(son(bro(son(s))))) == name_tag &&
	     son(son(son(bro(son(s))))) == stare
	     )			/* Let a := ..; return cont a */
	   )
	)
       {
	  /* +++ integrate this with the block above, otherwise NOTREACHED */
	  /* put tag in result reg if definition is call
	   * of proc, or body ends with return tag,
	   * provided result is not used other wise */
	  FULLCOMMENT1("scan: ident_tag(%d): use result reg", EXP_NUM(stare));
	  props(stare) |= (fxregble)? inreg_bits : infreg_bits;
	  if (fxregble)
	  {
 	     props(stare) |= inreg_bits;
	     bdy.fixneeds++;
	  }
	  else
	  {
 	     props(stare) |= infreg_bits;
	  }
	  bdy.propsneeds |= uses_res_reg_bit;
	  no(stare) = R_USE_RES_REG;	/* identification  uses result reg in body */
	}
	else if (isenvoff(stare)) /* MUST go on stack */
	{
	   no(stare) = R_NO_REG;
	}
	else if (!isvar(*e) && !isparam(*e) &&
		((name(t) == reff_tag && name(son(t)) == cont_tag &&
		   name(son(son(t))) == name_tag && isvar(son(son(son(t))))
		   && !isvis(son(son(son(t)))) && !isglob(son(son(son(t))))
		   && unchanged(son(son(son(t))), stare)

	  /*
	   * reff cont variable-not assigned to in scope
	   */
		  ) ||
		 (name(t) == cont_tag && name(son(t)) == name_tag &&
	    isvar(son(son(t))) && !isvis(son(son(t))) && !isglob(son(son(t)))
		   && unchanged(son(son(t)), stare)

	  /*
	   * cont variable - not assigned to in scope
	   */
		  )
		 )
	 )
	{
	  FULLCOMMENT1("scan: ident_tag(%d): dont take space for this dec", EXP_NUM(stare));
	  props(stare) |= defer_bit;
	  /* dont take space for this dec */	}
	else if (!isvar(stare) &&
		 ((props(stare) & 0x10 /* forced in const */ ) == 0)
		 && (name(t) == name_tag || name(t) == val_tag))
	{
	  FULLCOMMENT1("scan: ident_tag(%d): dont take space for this dec (#2)", EXP_NUM(stare));
	  props(stare) |= defer_bit;
	  /* dont take space for this dec */
	}
	else if (fxregble && bdy.fixneeds < maxfix &&
		(bdy.propsneeds & morefix) == 0 &&
		((bdy.propsneeds & anyproccall) == 0
		  || tempdec(stare,((bdy.propsneeds & morefix) == 0 &&
				     bdy.fixneeds < maxfix_tregs - 2))))
	{
	  /*
	   * put this tag in some  fixpt t-reg - which will be decided  in
	   * make_code
	   */
	  FULLCOMMENT1("scan: ident_tag(%d): use fixpt t-reg", EXP_NUM(stare));
	  FULLCOMMENT2("	bdy.fixneeds=%d def.fixneeds=%d",
		       bdy.fixneeds, def.fixneeds);
	  props(stare) |= inreg_bits;
	  no(stare) = 0;
	  bdy.fixneeds += 1;
	}
	else if (bdy.floatneeds < maxfloat && (bdy.propsneeds & morefloat) == 0
		 && flregble &&
		((bdy.propsneeds & anyproccall) == 0
		  || tempdec(stare,((bdy.propsneeds & morefloat) == 0 &&
				     bdy.floatneeds < MAXFLOAT_TREGS - 1))))
	{

	  /*
	   * put this tag in some  float t-reg - which will be decided  in
	   * make_code
	   */
	  FULLCOMMENT1("scan: ident_tag(%d): use float t-reg", EXP_NUM(stare));
	  props(stare) |= infreg_bits;
	  no(stare) = 0;
	  bdy.floatneeds += 1;
	}
	else
	{
	  FULLCOMMENT1("scan: ident_tag(%d): use stack or saved reg", EXP_NUM(stare));
	  no(stare) = R_NO_REG;

	  /*
	   * allocate either on stack or saved reg
	   */
	}
      }
      bdy = maxneeds(bdy, def);
      if ((bdy.propsneeds & usesproccall)!= 0)
      {
	bdy.propsneeds |= hasproccall;
      }
      return bdy;
    }

/*********************************************************************
	sequence

shape of exp is shape of end of sequence
son is sequence holder, son of this is list of voided statements.
*********************************************************************/

  case seq_tag:
    {
      exp *arg = &bro(son(*e));
      needs an;
      exp *stat;

      an = scan(arg, &arg);
      stat = &son(son(*e));

      arg = stat;
      for (;;)
      {
	needs stneeds;

	stneeds = scan(stat, &arg);
	/* initial statements voided */
	an = maxneeds(an, stneeds);
	if (last(*(stat)))
	{
	  if ((an.propsneeds & usesproccall)!= 0)
	  {
	    an.propsneeds |= hasproccall;
	  }
	  return an;
	}
	stat = &bro(*stat);
	arg = stat;
      }

    };

/********************************************************************
	goto

shape is bottom
son is exp for value jumped with
ptr is labelled exp
*********************************************************************/

  case trap_tag:
  case goto_tag:
    {
      return zeroneeds;
    };

  case ass_tag:
  case assvol_tag:
    {
      exp *lhs = &son(*e);
      exp *rhs = &bro(*lhs);
      needs nr;
      ash a;

      nr = scan(rhs, at);
      /* scan source */

      a = ashof(sh(*(rhs)));

      if (nstare != ass_tag || a.ashsize != a.ashalign || a.ashalign == 1)
      {
	/* struct/union assign */
	if (!(a.ashsize <= 32 && a.ashsize == a.ashalign))
	  nr.fixneeds += 2;	/* memory block copy */
      }

      if (name(*(lhs)) == name_tag &&
	 (isvar(son(*(lhs))) &&
	  ((nr.propsneeds & (hasproccall | morefix)) == 0
	    && nr.fixneeds < maxfix
	   )
	  )
	)			/* simple destination */
      {
	return nr;
      }
      else
      {
	needs nl;
	prop prps = (nr.propsneeds & hasproccall) << 1;

	nl = scan(lhs, at);
	if (name(*(rhs)) == apply_tag && nstare == ass_tag &&
	   (nl.propsneeds & (uses_res_reg_bit | anyproccall)) == 0)
	{
	  /* source is proc call, so assign result reg directly */
	   /* SKIP */ ;
	}
	else if (nr.fixneeds >= maxfix || prps != 0)
	{
	  /* source and destination regs overlap, so identify source */
	  cca(at, rhs);
	  nl = shapeneeds(sh(*(rhs)));
	  nl.propsneeds |= morefix;
	  nl.propsneeds &= ~(prps >> 1);
	  nl.propsneeds |= prps;
	}
	nr.fixneeds += 1;
	return maxneeds(nl, nr);
      }
    };

  case untidy_return_tag:
  case res_tag:
    {
      ash a;
      needs x;
      shape s;
      exp *arg = &son(*e);
      /* exp r,ss,t; */
      s = sh(*(arg));
      a = ashof(s);
      props(*e) = 0;		/* clear possibility of tlrecirsion; may be
				 * set later */
      x = scan(arg, at);
      /* scan result exp ... */
      if (is_floating(name(s)) && a.ashsize <=64)  /* ... floating pt result */
      {
	x.propsneeds |= realresult_bit;
	if (name(s)!= shrealhd)
	{
	  x.propsneeds |= longrealresult_bit;
	}
	FULLCOMMENT("scan res_tag: long real/real result");
      }
      else
      {
	if (!valregable(s) && !(name(son(*e)) == top_tag)) /* .... result does not fit into reg */
	{
	  x.propsneeds |= long_result_bit;
	FULLCOMMENT("scan res_tag: struct/union result");
	}
      }

      FULLCOMMENT1("scan res_tag: result size %d", a.ashsize);
      if (a.ashsize != 0 && name(*arg) != clear_tag)  /* not a void result */
      {
	x.propsneeds|= has_result_bit;
      }

      return x;
    };


    /* spec 3.1 procedure stuff */

    case apply_general_tag: {
	exp application = *(e);
	exp *fn = &son(application);
	exp cers = bro(*fn);
	exp *cerl = &son(cers);
	long stpar = 0;

	needs nds;
	needs plnds;
	int i;

	gen_call = 1;

	nds = scan(fn, at);
	if ((nds.propsneeds & hasproccall)!= 0) {
				/* .... it must be identified */
	  cca(at, fn);
	  nds.propsneeds &= ~hasproccall;
	  nds.propsneeds |= usesproccall;
	  fn = &son(application);
	}

	for (i=0; i<no(cers); i++) {
		needs onepar;
		shape shonepar = sh(*cerl);
		exp * par = (name(*cerl) ==caller_tag)?&son(*cerl):cerl;
		int n = rounder(stpar, shape_align(shonepar));
		onepar = scan(par,at);
	    	if ((i != 0 && (onepar.propsneeds & hasproccall)!= 0) ||
	  		onepar.fixneeds+ (stpar>>5) > maxfix) {
				/* if it isn't the first parameter, and it
				   calls a proc, identify it */
	    	  cca(at, par);
	    	  nds.propsneeds |= usesproccall;
	    	  nds = maxneeds(shapeneeds(sh(*(par))), nds);
	    	  nds.maxargs = MAX_OF(nds.maxargs, onepar.maxargs);
	  	}
	  	else {
	  	  nds = maxneeds(onepar, nds);
	  	}
	  	if (name(*cerl) ==caller_tag) { no(*cerl) = n; };
	  	n = n + shape_size(shonepar);
	  	stpar = rounder(n,32);
	  	cerl = &bro(*cerl);
	}
	nds.maxargs = MAX_OF(nds.maxargs, stpar);
	nds = maxneeds(scan(&bro(bro(son(application))), at), nds);

	plnds = scan(&bro(bro(bro(son(application)))), at);




	if ((plnds.propsneeds & (anyproccall | uses2_bit))!= 0) {
		props(application) = 1;
		if (is_floating(name(sh(application))) || valregable(sh(application))) {
			cca(at, ptr_position(application));
			plnds.propsneeds |= usesproccall;
		}
	}
	else { props(application) = 0; }

	nds = maxneeds(nds, plnds);
	nds.propsneeds |= hasproccall;
	return nds;
	}

   case make_callee_list_tag: {
   	exp cees = *e;
	exp * par = &son(cees);
	needs nds;
	long stpar = 0;
	int i;
	nds = zeroneeds;
	for (i=0; i<no(cees); i++) {
		needs onepar;
		shape shonepar = sh(*par);
		int n = rounder(stpar, shape_align(shonepar));
		onepar = scan(par,at);
	    	if (((onepar.propsneeds & hasproccall)!= 0) ||
	  		onepar.fixneeds+1 > maxfix) {
				/* if it calls a proc, identify it */
	    	   cca(at, par);
	    	   nds.propsneeds |= usesproccall;
	    	   nds = maxneeds(shapeneeds(sh(*(par))), nds);
	    	   nds.maxargs = MAX_OF(nds.maxargs, onepar.maxargs);
	  	}
	  	else {
	  	  nds = maxneeds(onepar, nds);
	  	}
	  	n = n + shape_size(shonepar);
	  	stpar = rounder(n,32);
	  	par = &bro(*par);
	  }
	no(cees) = stpar;
	return nds;
   }
   case make_dynamic_callee_tag: {
	exp cees = *e;
	exp *ptr = &son(cees);
	needs ndsp;
	needs nds;
	nds = zeroneeds;
	ndsp = scan(ptr, at);
	if (((ndsp.propsneeds & hasproccall)!= 0) ||
	  		ndsp.fixneeds+1 > maxfix) {
	    	 cca(at, ptr);
	    	 nds.propsneeds |= usesproccall;
	    	 nds = maxneeds(shapeneeds(sh(*(ptr))), nds);
	    	 nds.maxargs =  MAX_OF(nds.maxargs, ndsp.maxargs);
	}
	else {
	  	nds = ndsp;
	}
	ndsp = scan(&bro(son(*e)), at);
	if (((ndsp.propsneeds & hasproccall)!= 0) ||
	  		ndsp.fixneeds+2 > maxfix) {
	    	 cca(at, &bro(son(cees)));
	    	 nds.propsneeds |= usesproccall;
	    	 nds = maxneeds(shapeneeds(sh(bro(son(*e)))), nds);
	    	 nds.maxargs = MAX_OF(nds.maxargs, ndsp.maxargs);
	}
	else {
	  	nds = maxneeds(ndsp, nds);
	}
	if (nds.fixneeds<5)nds.fixneeds = 5;
	return nds;
    }

    case same_callees_tag: {
    	needs nds;
    	nds = zeroneeds;
    	nds.fixneeds = 4;
    	return nds;
    }

    case tail_call_tag: {
	needs ndsp;
	needs nds;
	exp *fn = &son(*e);
	ndsp =  scan(fn, at);
	if (((ndsp.propsneeds & hasproccall)!= 0) ||
	  		ndsp.fixneeds+1 > maxfix) {
	    	 cca(at, fn);
	    	 nds.propsneeds |= usesproccall;
	    	 nds = maxneeds(shapeneeds(sh(*(fn))), nds);
	    	 nds.maxargs =  MAX_OF(nds.maxargs, ndsp.maxargs);
	}
	else {
	  	nds = ndsp;
	}
	gen_call = 1;
	has_tail_call = 1;

	ndsp = scan(&bro(son(*e)), at);
	nds = maxneeds(nds, ndsp);
	return nds;
   }


   case env_size_tag:
    {
      exp *arg = &son(*e);
      return scan(arg,at);
    }


  case apply_tag:
    {
      exp application = *(e);
      exp fn = son(application);
      exp *par = &bro(fn);
      exp *fnexp = &son(*e);
      int parsize = 0;
      needs nds;
      bool tlrecpos = nonevis && callerfortr && (rscope_level == 0);
      int i;
      bool notinreg = !(
#if use_long_double
			 name(sh(application)) ==shrealhd    ||
			 name(sh(application)) ==realhd      ||
#else
			 is_floating(name(sh(application))) ||
#endif
			 valregable(sh(application)));

      bool long_result_space_needed = notinreg && !(name(sh(*e)) == tophd);

      nds = scan(fnexp, at);
      /* scan the function exp ... */
      if ((nds.propsneeds & hasproccall)!= 0)
      {
	/* .... it must be identified */
	cca(at, fnexp);
	nds.propsneeds &= ~hasproccall;
	nds.propsneeds |= usesproccall;
	fn = son(application);
	par = &bro(fn);
      }

      if (name(fn)!= name_tag ||
	 (son(son(fn))!= nilexp && name(son(son(fn)))!= proc_tag))
      {
	tlrecpos = 0;
      }

      for (i = 1; !last(fn); ++i)
      {				/* scan parameters in turn ... */
	needs onepar;
	shape shpar = sh(*par);

	onepar = scan(par, at);

	if ((i != 1 && (onepar.propsneeds & hasproccall)!= 0) ||
	    onepar.fixneeds + (parsize >> 5) > maxfix)
	{

	  /*
	   * if it isn't the first parameter, and it calls a proc, identify it
	   */
	  FULLCOMMENT1("apply_tag: identifying parameter %d (1..) containing proc call",i);
	  cca(at, par);
	  nds.propsneeds |= usesproccall;
	  nds = maxneeds(shapeneeds(sh(*(par))), nds);
	  nds.maxargs = MAX_OF(nds.maxargs, onepar.maxargs);
	}
	else
	{
	  nds = maxneeds(onepar, nds);
	}

	parsize = rounder(parsize + shape_size(shpar), 32);
	/* round up bytes and halfwords */

	parsize = rounder(parsize, shape_align(shpar));
	/* parameters must be properly aligned on the stack */

	if ((!valregable(shpar) && !is_floating(name(shpar))) || parsize > 128)
	{
	  tlrecpos = 0;
	}
	if (last(*(par)))
	{
	  break;
	};
	par = &bro(*par);
      }

      if (specialopt(fn))
	nds.propsneeds |= dont_optimise; /* eg vfork */

      if ((i = specialfn(fn)) > 0)
      {				/* eg strlen */
#if 0
	nds = maxneeds(specialneeds(i), nds);
#endif
	assert("specialfn - specialneeds");
	return nds;
      }
      else if (i == -1)
      {				/* call of strcpy .... */
#if 0
	exp par2 = *(par);

	/*
	 * TEST for constant string????????????????? if (name (par2) ==
	 * eval_tag && name (son (par2)) == pack_tag && name (son (son
	 * (par2))) == string_tag) {
	 *
	 * setname (* (e), ass_tag); son (* (e)) = * (parlist); son (par2) = son
	 * (son (par2)); sh (par2) = sh (son (par2)); bro (par2) = * (e) ;
	 * bro(son(par2)) = par2;	return maxneeds (nds, twofix); }
	 */
#endif
      }

      if (tlrecpos)
      {
	exp dad = father(application);

	if (name(dad) == res_tag)
	{
	  props(dad) = 1;	/* do a tl recursion */
	}
      }

      if (long_result_space_needed)
      {
	/* find space for tuple result */
	FULLCOMMENT("apply_tag: identifying notinreg result");
	assert(name(*(ptr_position(application))) ==apply_tag);
	cca(at,ptr_position(application));
	nds.propsneeds |= usesproccall;
      }
      else
      {
	nds.propsneeds |= hasproccall;
      }
      nds.maxargs = MAX_OF(nds.maxargs, parsize);
      nds.fixneeds = MAX_OF(nds.fixneeds, 7); /* clobber %o0..%o5,%07 */
      return nds;

    }

  case val_tag:
    {
      exp s = sh(*e);
      if (name(s) == offsethd && al2(s) >= 8)
      {
	/* express disps in bytes */
	no(*e) = no(*e) >> 3;
      }
      FULLCOMMENT2("val_tag %s no=%d", SH_NAME(name(s)), no(*e));
      /* ... and continue */
    }

  case name_tag:
  case null_tag:
  case real_tag:
  case string_tag:
  case env_offset_tag: case general_env_offset_tag:
  case current_env_tag:
  case make_lv_tag:
  case last_local_tag:
  case caller_name_tag:
  case give_stack_limit_tag:
/*  case next_frame_tag:  */
    {
       if (nstare==last_local_tag)
	  cpr->Has_ll = 1;
       return shapeneeds(sh(*(e)));
    };

  case clear_tag:
  case top_tag:
  case local_free_all_tag:
  case prof_tag:
  case formal_callee_tag:
    {
      return zeroneeds;
    };

#if 0
  case rscope_tag:
    {
      needs sn;
      exp *s = &son(*e);
      exp lst;

      rscope_level++;
#if 0 /* only needed when OPTIM_TAIL is set */
      (void) last_statement(son(*e), &lst);	/* always true */
      if (name(lst) == res_tag)
      {
	/* can remove res */
	exp *pos = ptr_position(lst);
	exp t;

	bro(son(lst)) = bro(lst);
	if (last(lst))
	{
	  setlast(son(lst));
	}
	else
	{
	  clearlast(son(lst));
	}
	*pos = son(lst);
	for (t = father(*pos); name(sh(t)) == bothd; t = father(t))
	{
	  sh(t) = sh(*pos);	/* adjust ancestors to correct shape */
	}
      }
#endif
      sn = scan(s, &s);
      rscope_level--;
      return sn;
    };
#endif


  case set_stack_limit_tag:
  case abs_tag:
  case neg_tag:
  case case_tag:
  case not_tag:
  case goto_lv_tag: /* for COBOL */
  case offset_negate_tag:
  case diagnose_tag:
  case local_free_tag:
#if 1
  case return_to_label_tag:
#endif
    {
      exp *arg = &son(*e);
      return scan(arg, at);
    };

    case fneg_tag: case fabs_tag:
    case chfl_tag:
    {
      needs nds;
      exp *pste;
      nds = scan(&son(*e), at);
      pste = ptr_position(ste);
      if (!optop(*pste) && nds.fixneeds <2)nds.fixneeds = 2;
#if use_long_double
	    {
	      exp op = *pste;
	      if (name(sh(op)) == doublehd ||
		  name(sh(son(op))) == doublehd) {
		if (!is_o(name(son(op))) ||
		    pntst(nds, hasproccall)) {
		  cca(at, &son(op));
		}
		pnset(nds, hasproccall);
	      }
	    }
#endif
      return nds;
    }

  case bitf_to_int_tag:
    {
      exp *arg = &son(*e);
      needs nds;
      exp stararg;
      exp stare;
      int sizeb;

      nds = scan(arg, at);
      stararg = *(arg);
      stare = *(e);
      sizeb = ashof(sh(stararg)).ashsize;
      if ((name(stararg) == name_tag &&
	  ((sizeb == 8 && (no(stararg) & 7) == 0)
	    || (sizeb == 16 && (no(stararg) & 15) == 0)
	    || (sizeb == 32 && (no(stararg) & 31) == 0)
	   )
	  ) || (name(stararg) == cont_tag &&
	 ((name(son(stararg))!= name_tag && name(son(stararg))!= reff_tag)
	   || (sizeb == 8 && (no(son(stararg)) & 7) == 0)
	   || (sizeb == 16 && (no(son(stararg)) & 15) == 0)
	   || (sizeb == 32 && (no(son(stararg)) & 31) == 0)
	  )
		)
	)

	/*
	 * these bitsint(trimnof(X)) could be implemented by lb or lh
	 * instructions ...
	 */
      {
	int sgned = is_signed(sh(stare));
	shape ns = (sizeb == 8)?((sgned)? scharsh : ucharsh)
	:(sizeb == 16)?((sgned)? swordsh : uwordsh)
	: sh(stare);

	/* can use short loads instead of bits extractions */
	if (name(stararg) == cont_tag)
	{
	  /* make the ptr shape consistent */
	  sh(son(stararg)) = f_pointer(long_to_al(shape_align(ns)));
	}
	sh(stararg) = ns;
	setname(stare, chvar_tag);
      }
      return nds;
    }


  case int_to_bitf_tag:
    {
      exp *arg = &son(*e);
      return scan(arg, at);
    }

  case round_tag:
    {
      needs s;
      exp *arg;
      exp *pste;
      int rm = (int)round_number(*e);
      arg = &son(*e);
      s = scan(arg,at);
      pste = ptr_position(ste);
      s.fixneeds = MAX_OF(s.fixneeds,2);
      if (rm < 3 || name(sh(*pste)) == ulonghd)
      {
	 s.floatneeds = MAX_OF(s.floatneeds, 3);
      }
      else
      {
	 s.floatneeds = MAX_OF(s.floatneeds, 2);
      }
#if use_long_double
      {
	 exp op = *pste;
	 if (name(sh(son(op))) == doublehd)
	 {
	    if (!is_o(name(son(op))) ||
		    pntst(s, hasproccall))
	    {
	       cca(at, &son(op));
	    }
	    pnset(s, hasproccall);
	 }
      }
#endif
      return s;
    };

  case shl_tag:
  case shr_tag:
  case long_jump_tag:
    {
      exp *lhs = &son(*e);
      exp *rhs = &bro(*lhs);
      needs nl, nr;
      prop prps;
      if (name(*rhs) ==val_tag)
      {
	 return scan(lhs, at);
      }
      nr = scan(rhs, at);
      nl = scan(lhs, at);
      rhs = &bro(*lhs);
      prps = (nr.propsneeds & hasproccall) << 1;
      if (nr.fixneeds >= maxfix || prps != 0)
	/* if reg requirements overlap, identify second operand */
      {
	cca(at, rhs);
	nl = shapeneeds(sh(*(rhs)));
	nl.propsneeds |= morefix;
	nl.propsneeds &= ~(prps >> 1);
	nl.propsneeds |= prps;
      }
      nr.fixneeds += 1;
      return maxneeds(nl, nr);
    };


  case test_tag:
    {
      exp stare = *(e);
      exp l = son(stare);
      exp r = bro(l);

      if (!last(stare) && name(bro(stare)) == test_tag &&
	  no(stare) == no(bro(stare)) &&
	  test_number(stare) == test_number(bro(stare)) &&
	  eq_exp(l, son(bro(stare))) && eq_exp(r, bro(son(bro(stare))))
	)
      {				/* same test following in seq list - remove
				 * second test */
	if (last(bro(stare)))
	  setlast(stare);
	bro(stare) = bro(bro(stare));
      }

      if (last(stare) && name(bro(stare)) == 0	/* seq holder */
	  && name(bro(bro(stare))) == test_tag &&
	  name(bro(bro(bro(stare)))) == seq_tag &&
	  no(stare) == no(bro(bro(stare))) &&
	  test_number(stare) == test_number(bro(bro(stare))) &&
	  eq_exp(l, son(bro(bro(stare))))
	  && eq_exp(r, bro(son(bro(bro(stare)))))
	)
      {				/* same test following in seq res - void
				 * second test */
	setname(bro(bro(stare)), top_tag);
	son(bro(bro(stare))) = nilexp;
	pt(bro(bro(stare))) = nilexp;
      }

      if (name(l) == val_tag && (props(stare) == 5 || props(stare) == 6))
      {
	/* commute  const = x */
	bro(l) = stare;
	setlast(l);
	bro(r) = l;
	clearlast(r);
	son(stare) = r;
	r = l;
	l = son(stare);
      }

      if (name(l) == bitf_to_int_tag && name(r) == val_tag &&
	 (props(stare) == 5 || props(stare) == 6) &&
	 (name(son(l)) == cont_tag || name(son(l)) == name_tag))
      {				/* equality of bits against +ve consts doesnt
				 * need sign adjustment */
	long n = no(r);

	switch (name(sh(l)))
	{
	case scharhd:
	  {
	    if (n >= 0 && n <= 127)
	    {
	      sh(l) = ucharsh;
	    } break;
	  }
	case swordhd:
	  {
	    if (n >= 0 && n <= 0xffff)
	    {
	      sh(l) = uwordsh;
	    } break;
	  }

	default:;
	}
      }
      else if (is_floating(name(sh(l))))
      {
	return fpop(e, at);
      }
      else if (name(r) == val_tag && no(r) == 1
	       && (props(stare) == 3 || props(stare) == 2))
      {
	no(r) = 0;
	if (props(stare) == 3)
	{
	  props(stare) = 4;	/* branch >=1 -> branch > 0 */
	}
	else
	{
	  props(stare) = 1;	/* branch <1 -> branch <= 0 */
	}
      }
      return likediv(e, at);
    }


  case plus_tag:
    {
      /* replace any operands which are neg(..) by -, if poss */
      exp sum = *(e);
      exp list = son(sum);
      bool someneg = 0;
      bool allneg = 1;

      for (; optop(sum);)
      {
	if (name(list) == neg_tag)
	  someneg = 1;
	else
	  allneg = 0;
	if (last(list))
	  break;
	list = bro(list);
      }

      FULLCOMMENT2("scan case plus_tag,addptr_tag: allneg=%d someneg=%d", allneg, someneg);

      if (someneg)
      {
	/* there are some neg() operands */
	if (allneg)
	{
	  /* transform -..-... to -(..+.. +...) */
	  exp x;

	  /*
	   * Build a new list form operand of neg_tags, which will
	   * become plus_tag operands.
	   */
	  x = son(sum);
	  list = son(x);
	  for (;;)
	  {
	    /*
	     * 'x' moves along neg_tag's lists
	     * 'list' moves along sons of neg_tag's lists, building a new list
	     * eventually new list is made son of plus_tag
	     */

	    bro(list) = son(bro(x));
	    if (!last(x))
	    {
	      clearlast(list);
	      list = bro(list);
	      x = bro(x);
	    }
	    else
	    {
	      setlast(list);
	      bro(list) = sum;		/* set father to be */
	      son(sum) = son(son(sum)); /* set new sons of plus_tag */
	      break;
	    }
	  }

	  /*
	   * create new neg_tag to replace plus_tag,
	   * old plus_tag being the operand of the new neg_tag.
	   */
	  x = getexp(sh(sum), bro(sum), last(sum), sum, nilexp,
		     0, 0, neg_tag);

	  setlast(sum);

	  /* set father of sum, new neg_tag exp */
	  bro(sum) = x;

	  *(e) = x;
	}			/* end allneg */
	else
	{
	  /* transform to  ((..(..+..) - ..) -..) */
	  int n = 0;
	  exp brosum = bro(sum);
	  bool lastsum = last(sum);
	  exp x = son(sum);
	  exp newsum = sum;

	  list = nilexp;
	  for (;;)
	  {
	    exp nxt = bro(x);
	    bool final = last(x);

	    if (name(x) == neg_tag)
	    {
	      bro(son(x)) = list;
	      list = son(x);
	    }
	    else
	    {
	      bro(x) = newsum;
	      newsum = x;
	      if ((n++) == 0)
		setlast(newsum);
	      else
		clearlast(newsum);
	    }
	    if (final)
	      break;
	    x = nxt;
	  }

	  if (n > 1)
	  {
	    son(sum) = newsum;
	    newsum = sum;	/* use existing exp for add operations */
	  }
	  for (;;)
	  {			/* introduce - operations */
	    exp nxt = bro(list);

	    bro(newsum) = list;
	    clearlast(newsum);
	    x = getexp(sh(sum), nilexp, 0, newsum, nilexp, 0, 0, minus_tag);

	    bro(list) = x;
	    setlast(list);
	    newsum = x;
	    if ((list = nxt) == nilexp)
	      break;
	  }
	  bro(newsum) = brosum;
	  if (lastsum)
	  {
	    setlast(newsum);
	  }
	  else
	  {
	    clearlast(newsum);
	  }
	  *(e) = newsum;

	}			/* end else allneg */

	return scan(e, at);

      }				/* end someneg - else continue to next case */
    }
    /* FALLTHROUGH */


  case and_tag:
  case or_tag:
  case xor_tag:
    {
      return likeplus(e, at);
    };

  case addptr_tag:
    {
    	exp p = son(*e);
    	exp d = bro(p);
    	int fal = frame_al_of_ptr(sh(p));
    	if (fal!=0) {
    		int oal = frame_al1_of_offset(sh(d));
#if 0
    		if (((oal-1) &oal)!= 0) {
    			failer("can't cope with mixed frame offsets yet");
    		}
#endif
    		if (includes_vcallees(fal) && ((oal & 20)!= 0)) {
    			/* oal = callees and callers are offset relative to
			   FP when there are variable callees */
    		   exp ne = getexp(sh(p), d, 0, p, nilexp, 0, 0,
    		   		locptr_tag);
    		   bro(p) = ne; setlast(p);
    		   son(*e) = ne;
    		}
    	}
    	/* ... and continue */
    }

  case minus_tag:
  case subptr_tag:
  case minptr_tag:
    {
      return likediv(e, at);
    };

  case reff_tag:
  case float_tag:
  case offset_pad_tag:
  case locptr_tag:
  case chvar_tag:
    {
      exp *arg = &son(*e);
      exp *pste;
      needs nds;
      nds = shapeneeds(sh(*e));
      nds = maxneeds(scan(arg, at), nds);
      pste = ptr_position(ste);
#if use_long_double
	    {
	      exp op = *pste;
	      if (name(sh(op)) ==doublehd)
	      {
		 pnset(nds, hasproccall);
	      }
	    }
#endif
      return nds;
    };

  case cont_tag:
  case contvol_tag:
  {
    exp *arg = &son(*e);
    needs nds;

    nds = maxneeds(scan(arg, at), shapeneeds(sh(*(e))));
    nds.fixneeds = MAX_OF(nds.fixneeds, 2);
    return nds;
  };

  mult_tag_case:
  case mult_tag:
  {
    return multneeds(e, at);
  };

  case offset_mult_tag:
  case offset_div_tag:
  {
	    exp op2 = bro(son(*e));
	    shape s = sh(op2);

	    if (name(op2) == val_tag && no(op2) == 8 &&
		 name(s) == offsethd && al2(s) >= 8) {
		/* offset is one byte */
		exp op1 = son(*e);
		bro(op1) = bro(*e);
		if (last(*e)) {
		    setlast(op1);
		} else {
		    clearlast(op1);
		}
		*e = op1;
		return scan(e, at);
	    }
	    if (nstare == offset_mult_tag)goto mult_tag_case;
	    /* FALL THROUGH */
	}

#if 0
  case offset_div_tag:
  {
     exp op1 = son(*e);
     exp op2 = bro(op1);
     shape s = sh(op2);
     if (name(op2) ==val_tag  && name(s) ==offsethd
	 && al2(s) >= 8) {
       int n = no(op2) /8;
       if (n == 1) {
	 /* offset is one  byte */
	 bro(op1) = bro(*e);
	 if (last(*e)) { setlast(op1); } else {clearlast(op1); }
	 *e = op1;
	 return scan(e, at);
       }
       else
	 if (name(*e) == offset_mult_tag && n > 1 && (n& (n-1)) == 0)
	   if (name(op1) == and_tag
	      && name(son(op1)) == shr_tag &&
	      name(bro(son(op1))) ==val_tag) {
	     exp shexp = son(op1);
	     exp ac = bro(shexp);
	     exp shop1 = son(shexp);
	     exp shop2 = bro(shop1);
	     int na = no(ac);
	     if ((na& (na+1)) ==0 && name(shop2) ==val_tag) {
	       int pn = 0;
	       int ns = no(shop2);
	       int i = n;
	       while (i>1) { i >>= 1; pn++; }

	       if (ns > pn)
	       {
		 /* can do transform:
		    (((shop1>>ns) & na) * n) =>
		    shop1>>(ns-pn) & (na*n)
		      */
		 no(shop2) = ns-pn;
		 no(ac) = na*n;
		 bro(op1) = bro(*e);
		 if (last(*e))
		 {
		   setlast(op1);
		 }
		 else
		 {
		   clearlast(op1);
		 }
		 *e = op1;
		 return scan(e, at);
	       }
	     }
	   }
	   else
	   {
	     /* will do this by literal shift */
	     no(op2) = n;
	     return scan(&son(*e), at);
	   }
     }
     if (nstare == offset_mult_tag)goto mult_tag_case;
   }
#endif

    case div0_tag:
    case div2_tag:
    case offset_div_by_int_tag:
    {
	return divneeds(e, at);
    }

    case offset_add_tag:
    {
	  if ((al2(sh(son(*e))) == 1) && (al2(sh(bro(son(*e))))!= 1)) {
	    make_bitfield_offset(bro(son(*e)),son(*e),0,sh(*e));
	  }
	  if ((al2(sh(son(*e)))!= 1) && (al2(sh(bro(son(*e)))) == 1)) {
	    make_bitfield_offset(son(*e),*e,1,sh(*e));
	  }
    }
    case offset_subtract_tag:
    case component_tag:
    {
	return likediv(e, at);
    }

    case make_stack_limit_tag:
	{ needs nd;
	  nd = likediv(e, at);
	  nd.fixneeds = MAX_OF(nd.fixneeds, 2);
	  return nd;
	}

    case offset_max_tag: case max_tag: case min_tag:
	{ needs nd;
	  nd = likediv(e, at);
	  nd.fixneeds = MAX_OF(nd.fixneeds, 3);
	  return nd;
	}

    case rem0_tag:
    case rem2_tag:
    {
	return remneeds(e, at);
    }

    case div1_tag:
    {
      if (is_signed(sh(*e)) ==0)
      {
	setname(*e, div2_tag);
      }
      return divneeds(e,at);
    }

    case mod_tag:
    {
    	if (is_signed(sh(*e)) ==0)
	{
	  setname(*e, rem2_tag);
	}
    	return remneeds(e,at);
    }

  case fdiv_tag:
#if 0
    {
      exp z = *(e);
      exp a2 = bro(son(z));

      if (name(a2) == real_tag)	/* replace X/const by X*const^-1 */
      {
	flt inverse;
	flt unitflt;

	unitflt = flptnos[fone_no];
	if (flt_div(unitflt, flptnos[no(a2)], &inverse) == OKAY)
	{
	  /* a/const => a* (1.0/const) */
	  int f = new_flpt();

	  flptnos[f] = inverse;
	  no(a2) = f;
	  setname(z, fmult_tag);
	}
      }
    }
    /* FALLTHROUGH */
#endif

  case fplus_tag:
  case fminus_tag:
  case fmult_tag:
    {
      exp op = *(e);
      exp a2 = bro(son(op));

      if (!last(a2))
      {				/* + and * can have >2 parameters - make them
				 * diadic - can do better a+exp => let x = exp
				 * in a+x */
	exp opn = getexp(sh(op), op, 0, a2, nilexp, 0, 0, name(op));

	/* dont need to transfer error treatment - nans */
	exp nd = getexp(sh(op), bro(op), last(op), opn, nilexp, 0, 1,
			ident_tag);
	exp id = getexp(sh(op), op, 1, nd, nilexp, 0, 0, name_tag);

	pt(nd) = id;
	bro(son(op)) = id;
	setlast(op);
	bro(op) = nd;
	while (!last(a2))
	  a2 = bro(a2);
	bro(a2) = opn;
	*(e) = nd;
	return scan(e, at);
      }

      return fpop(e, at);
    };

  case field_tag:
    {
      needs str;
      exp *arg = &son(*e);

      if (chase(*e, arg))
      {				/* field has been distributed */
	exp stare = *e;
	exp ss = son(stare);

	if (!last(stare))
	  clearlast(ss);
	bro(ss) = bro(stare);
	sh(ss) = sh(stare);
	*e = ss;
	return scan(e, at);
      }
      str = scan(arg, at);
      return maxneeds(str, shapeneeds(sh(*(e))));
    };

/*********************************************************************
	load_proc


number is number of proc (useful for indexing)
*********************************************************************/

  case proc_tag:
  case general_proc_tag:
  {
     exp *bexp;
     exp *bat;
     needs body;
     exp stare = *(e);

     /* set number temp t-regs that can be used in proc */
     maxfix = maxfix_tregs;
     maxfloat = MAXFLOAT_TREGS;

     assert(~optim & OPTIM_TAIL);

     callerfortr = optim & OPTIM_TAIL && !proc_has_setjmp(stare) &&
		   !proc_has_alloca(stare) && !proc_has_lv(stare) &&
		   !proc_uses_crt_env(stare);

      gen_call = (name(stare) ==general_proc_tag);
      has_tail_call = 0;

      callee_sz = 0;
      stparam = 0;
      fixparam = ARG0;
      nonevis = 1;
      rscope_level = 0;

      bexp = &son(*e);
      bat = bexp;
      body = scan(bexp, &bat);
      /* scan the body of the proc */

      return body;		/* should never require this in reg in C */

  }

 case absbool_tag:
  {
    assert(~has & HAS_SETCC);
    fail("absbool_tag not covered in needs scan");
    /*NOTREACHED*/
  }

 case alloca_tag:
  {
    needs nds;
    cpr->Has_checkalloc = checkalloc(*e);
    nds = scan(&son(*e), at);
    if (nds.fixneeds < 2)
	nds.fixneeds = 2;
    hppabuiltin|= (1<<5);
    return nds;
  }


    case movecont_tag:{
	exp * d = &son(*e);
	exp * s = & bro(*d);
	exp * sz = &bro(*s);
	needs nd;
	needs ns;
	needs nsz;
	prop prps;
	nd = scan(d, at);
	ns = scan(s, at);
	nsz = scan(sz, at);
	prps = (ns.propsneeds & hasproccall) << 1;
	if (ns.fixneeds >= maxfix || prps != 0) {
			      /* if reg requirements overlap, identify
				 second operand */
	  cca(at, d);
	  ns = shapeneeds(sh(*(s)));
	  ns.propsneeds |= morefix;
	  ns.propsneeds &= ~(prps >> 1);
	  ns.propsneeds |= prps;
	}
	nd.fixneeds += 1;
	nd = maxneeds(nd, ns);
	prps= (nsz.propsneeds & hasproccall) << 1;
	if (nd.fixneeds +nsz.fixneeds >= maxfix || prps != 0) {
			      /* if reg requirements overlap, identify
				 last operand */
	  cca(at, d);
	  nsz = shapeneeds(sh(*(sz)));
	  nsz.propsneeds |= morefix;
	  nsz.propsneeds &= ~(prps >> 1);
	  nsz.propsneeds |= prps;
	}
	nd.fixneeds+=1;
	nd = maxneeds(nd,nsz);
	if (nd.fixneeds < 4)nd.fixneeds = 3;
	return nd;
     }


 case testbit_tag:
  {
    /* not in MIPS */
    fail("testbit_tag not covered in needs scan");
    /*NOTREACHED*/
  }


  default:
    {
       char s[64];
       /*Know to NOT be covered:
	 cscope_tag		(ignored)
	 diag_tag		(ignored)
	 fscope_tag		(ignored)
	 local_free_all_tag
	 local_free_tag
	 offset_pad_tag
	 testbit_tag
	 */
       FULLCOMMENT1("scan: bad nstare=%d", nstare);
       sprintf(s,"case %d not covered in needs scan",nstare);
       fail(s);
       return zeroneeds;
    }

  }
}


/* commented out return_to_label_tag and make_stack_limit_tag for puposes
of debugging until proper 4.0 libraries are built. */
