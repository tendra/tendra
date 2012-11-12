/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/************************************************************************
 *                         const.c
 *  This file defines the routines which implement the TDF-to-TDF
 *  optimising transformation which removes constant expressions from
 *  program fragments (typically loops).
 *
 *  The type maxconst returns information about the expression under
 *  consideration. The field self is true if the expression as a whole is
 *  constant within the program fragment under consideration. If the
 *  entire expression is not constant (self is false) then the field cont
 *  is a list of the sub-expressions which are constant within the
 *  specified region.
 *
 *  The type maxconst is defined in consttypes.h
 *
 *  The principal procedures defined here are mc_list, repeat_consts and
 *  return_repeats. They are described below.
 *
 *  Also used externally is intnl_to.
 *
 ************************************************************************/

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"

#include "exptypes.h"
#include "expmacs.h"

#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/consttypes.h>
#include <construct/constmacs.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>
#include <construct/installglob.h>
#include <construct/is_worth.h>
#include <construct/flpt.h>
#include <construct/flpttypes.h>
#include <construct/messages_c.h>
#include <construct/me_fns.h>

#include <refactor/refactor.h>
#include <refactor/refactor_id.h>
#include <refactor/const.h>

#ifdef NEWDIAGS
#include <newdiag/dg_aux.h>
#endif


/* MACROS */

#define false 0
#define true  1
#define MAXUSE 16
#define VERYBIGUSAGE 100
#define MEMINC 64
#define nilmem	((memlist *)0)

/* IDENTITIES */

static maxconst self_const = {
  true, nilexp
},
/* the entire expression is constant */
    no_consts = {
  false, nilexp
};
/* no part of the expression is constant */

/* VARIABLES */
/* All variables initialised */

typedef struct _memlist {
  exp dec;
  int res;
  struct _memlist *next;
}   memlist;

		/* no need to init mem and fmem */
static memlist *mem = nilmem,	/* current list of frequent identifiers */
   *fmem = nilmem;		/* list of free cells */

static prop cond_flag = 0;	/* pushed value */
/* 1 => inside cond(..);  2 => after test() in cond() */

static int arg_is_reff;		/* no init needed */
/* arg is reffield, so contents doesn't need guarding */

#define globmax 100
static int glob_index;
static exp glob_dest[globmax];

static int has_lj_dest;


/* PROCEDURES */

exp get_repeats(void);

static int
find_glob(exp e)
{
  int i;
  for (i = 0; i < glob_index; i++)
    if (glob_dest[i] == e)
      return 1;
  return 0;
}

/************************************************************************
 *  ret_constlist returns the elements of a constants-list
 ************************************************************************/
static void
ret_constlist(exp head)
{
  if (head != nilexp) {
    exp limit = pt(head), t = son(head), n;
    retcell(head);
    while (t != limit) {
      n = bro(t);
      retcell(t);
      t = n;
    }
    retcell(t);
  }
  return;
}

static maxconst max_const(exp, exp, int);
/* declaration - max_const and mc_list are mutually recursive */



/************************************************************************
 *  mc_list examines a list of expressions, and for each of them
 *  extracts the largest expressions which are constant within the
 *  region of interest.
 *
 *  Parameters:
 *        whole   the program region under consideration
 *        e       the first expression in the list. Expressions are
 *                linked via the brother field.
 *        ass_ok  all assignments in this region are to simple unaliassed
 *                variables
 *        good    if this is true AND all the expressions in the list are
 *                constant then the value self_const is returned.
 ************************************************************************/

static
maxconst mc_list(exp whole, exp e, int ass_ok, int good)
{
  exp t = e;
  int contin = true;
  maxconst mc, result;

  result.self = good;
  result.cont = nilexp;

  do {
    /* NB - t may be killed within max_const (offset_mult) */
    /* so remember next one in list */
    exp next_t = bro(t);
    if (last(t)) {
      contin = false;
    }
    mc = max_const(whole, t, ass_ok);

    if (mc.self) {
      /* the whole of t is constant */
      /* make a list element */
      exp w = getexp(f_bottom, nilexp, false, t, nilexp, cond_flag,
		       0, 0);
      if (result.cont == nilexp) {/* first item - start a list */
	result.cont = getexp(f_bottom, nilexp, false, w, w, 0,  0, 0);
      } else {			/* add this to list */
	bro(pt(result.cont)) = w;
	pt(result.cont) = w;
      }
    } else {
      result.self = false;	/* some part of e is not constant */
      if (mc.cont != nilexp) {	/* but t has constants in it */
	if (result.cont != nilexp) {	/* add them to list */
	  bro(pt(result.cont)) = son(mc.cont);
	  pt(result.cont) = pt(mc.cont);
	  retcell(mc.cont);
	} else {		/* list was empty - start list */
	  result.cont = mc.cont;
	}
      }
    }

    t = next_t;
  } while (contin);

  if (result.self) {
    ret_constlist(result.cont);
    return self_const;
  }
  return result;
}


/************************************************************************
 *  intnl_to returns true if part is contained in whole
 ************************************************************************/

int
intnl_to(exp whole, exp part)
{
  exp q = part;

  while (q != whole && q != nilexp && name(q) != hold_tag &&
	 name(q) != hold2_tag && (name(q) != ident_tag || !isglob(q))) {
    q = father(q);
  }

  return q == whole;
}

/* heavily used idents are kept in lookup list */

static int not_assigned_to(exp, exp);

static int
not_ass2(exp vardec, exp piece)
{
  /*
   * this replaces used_in with stronger test - see changes in assigns_alias
   */
  exp t = pt(vardec);
  exp q;
  exp upwards = t;

  do {				/* test each use of the identifier */
    q = t;
    while (q != nilexp && q != piece && q != vardec &&
	   name(q) != rep_tag && (name(q) != ident_tag || !isglob(q))) {
      upwards = q;
      q = bro(q);
    }

    if (q != nilexp && q != piece && name(q) == rep_tag) {
      /* q has got to a repeat, so */
      /* scan up repeat_list structure for holder of piece */
      exp h = pt(q), hp = pt(piece);
      while (h != nilexp && h != hp) {
	h = bro(h);
      }
      if (h == hp) {
	/* q was within piece */
	q = piece;
	upwards = son(q);
	while (!last(upwards)) {
	  upwards = bro(upwards);
	}
      } else {
	q = nilexp;
      }
    }
    /* ascend from the use until we reach either vardec or piece */
    if (q == piece && last (upwards)) {	/* the use was in piece */
      if (isreallyass(t)) {
        return false;
      }
      if (!last(t) && last(bro(t)) &&
	(name(bro(bro(t))) == ass_tag || name(bro(bro(t))) == assvol_tag)) {
	return false;		/* the use was an assignment */
      }
      if (!last(t) && last(bro(t)) && name(bro(bro(t))) == ident_tag) {
	/* use in declaration */
	if (!isvar(bro(bro(t))) && !not_assigned_to(bro(bro(t)), bro(t))) {
	  return false;
	}
      } else {
	exp dad = father(t);
	if (name(dad) == addptr_tag && son(dad) == t) {
	  /* use in subscript .... */
	  if (!last(dad) && last(bro(dad)) &&
	     (name(bro(bro(dad))) == ass_tag ||
	       name(bro(bro(dad))) == assvol_tag)) {
	    return false;		/* the use was an assignment */
	  }
	  if (!last(dad) && last(bro(dad)) &&
	      name(bro(bro(dad))) == ident_tag) {
	    /* ... which is identified */
	    if (!isvar(bro(bro(dad))) &&
		!not_assigned_to(bro(bro(dad)), bro(dad))) {
	      return false;
	    }
	  }
	}
      }
    }
    t = pt(t);
  } while (t != nilexp);
  return true;
}


static int
not_assigned_to(exp vardec, exp body)
{
  if (no(vardec) > VERYBIGUSAGE) {
    return false;
  }

  if (no(vardec) > MAXUSE) {
    /* when a variable is used many times the result from not_ass2 */
    /* is saved in an ordered list to avoid n-squared run-times    */
    memlist *ptr = mem;
    /* is this declaration known? */
    /* NOTE: memory is cleared after each repeat is processed */
    /* so any in memory refer to the current repeat */
    while (ptr != nilmem && (ptr->dec) != vardec)
      ptr = ptr->next;
    if (ptr == nilmem) {
      memlist **pp = &mem;
      /* insert with heavier used decs first */
      while (*pp != nilmem && no((*pp) ->dec) > no(vardec)) {
	pp = & ((*pp) ->next);
      }
      if (fmem == nilmem) {
	/* add some cells onto the free list */
	memlist **fpp = &fmem;
	int i;
	*fpp = (memlist *)xcalloc(MEMINC, sizeof(memlist));
	for (i = 0; i < MEMINC; ++i) {
	 (*fpp) ->next = (*fpp) + 1;
	  fpp = & ((*fpp) ->next);
	}
	*fpp = nilmem;
      }
      /* get a cell from the free list */
      ptr = fmem;
      fmem = ptr->next;
      /* remember this vardec */
      ptr->dec = vardec;
      ptr->res = not_ass2(vardec, body);
      /* put cell into mem list */
      ptr->next = *pp;
      *pp = ptr;
    }
    return ptr->res;
  } else {
    /* default case - identifier not heavily used */
    return not_ass2(vardec, body);
  }
}



/************************************************************************
 *  max_const extracts the largest expressions which are constant within
 *  the region of interest.
 *
 *  Parameters:
 *        whole   the program region under consideration
 *        e       the expression under consideration
 *        ass_ok  all assignments in this region are to simple unaliassed
 *                variables
 ************************************************************************/

static maxconst
max_const(exp whole, exp e, int ass_ok)
{
  switch (name(e)) {
  case labst_tag:
    return mc_list(whole, bro(son(e)), ass_ok, false);

  case contvol_tag:
  case case_tag:
  case goto_tag:
  case apply_general_tag:
  case tail_call_tag:
    return no_consts;

  case fdiv_tag: {
    maxconst mc;
    maxconst mct;
    mc = max_const(whole, bro(son(e)), ass_ok);
    mct = mc_list(whole, son(e), ass_ok, optop(e));
    if (mct.self) {
      return mct;
    }

    if (mc.self && !strict_fl_div && optop(e)) {
      flpt f = new_flpt();
      exp funit;
      exp temp1;
      exp temp2;
      flt_copy(flptnos[fone_no], &flptnos[f]);
      funit = getexp(sh(e), nilexp, 0, nilexp, nilexp, 0, f, real_tag);
      temp1 = me_b3(sh(e), funit, bro(son(e)), fdiv_tag);
      temp2 = me_b3(sh(e), son(e), temp1, fmult_tag);

#ifdef NEWDIAGS
      dgf(temp2) = dgf(e);
#endif
      replace(e, temp2, temp2);
      return max_const(whole, temp2, ass_ok);
    } else {
      return mct;
    }
  }


  case cond_tag: {
      prop old_cond_flag = cond_flag;
      maxconst mc;
      if (cond_flag == 0) {
	cond_flag = 1;
      }
      mc = mc_list(whole, son(e), ass_ok, false);
      cond_flag = old_cond_flag;
      return mc;
  }

  case test_tag:{
      maxconst mc;
      mc = mc_list(whole, son(e), ass_ok, false);
      if (cond_flag == 1) {
	cond_flag = 2;
      }
      return mc;
  }

  case val_tag:
  case proc_tag:
  case env_offset_tag:
  case general_env_offset_tag:
    return self_const;

  case name_tag:
    if (intnl_to(whole, son(e))) {
      return no_consts;		/* internal const - may change */
    } else {
      return self_const;	/* external constant */
    }

  case cont_tag:
    if ((name(son(e)) == name_tag) && isvar(son(son(e)))) {
      /* so e is extracting the contents of a variable */
      exp var = son(son(e));

      if (!intnl_to(whole, var) && (not_assigned_to(var, whole))
	  && ass_ok) {
	/*
	 * variable declared external to whole, and NEVER assigned to in
	 * whole
	 */
	if (iscaonly(var)) {
	  return self_const;
	}
	if (isglob(var) && !find_glob(var)) {
	  return self_const;
	}
	return no_consts;
      } else {
	return no_consts;
      }
    } else {
      return mc_list(whole, son(e), ass_ok, ass_ok);
    }

  case plus_tag:
  case and_tag:
  case or_tag:
  case xor_tag:
  case mult_tag: {
      maxconst mc;

      mc = mc_list(whole, son(e), ass_ok, optop(e));

      if (mc.cont != nilexp && pt(mc.cont) != son(mc.cont) && optop(e)) {
	/* more than 1 item in list */
	exp limit = pt(mc.cont), h = son(mc.cont), arg, this, last_h;
	int arg_count = 0;
	int tot_args = 1;
	this = son(e);
	while (!last(this)) {
	  this = bro(this);
	  ++tot_args;
	}

	/* remember for which operator these are arguments */
	/* NB - some items may not be args of this operator */
	while (h != nilexp) {
	  this = son(h);
	  arg = son(e);
	  while (arg != nilexp && arg != this) {
	    arg = (last(arg)? nilexp : bro(arg));
	  }
	  if (arg != nilexp) {
	    /* it's an argument of this operator */
	    ++arg_count;
	    pt(h) = e;
	    last_h = h;
	  }
	  h = (h == limit ? nilexp : bro(h));
	}
	/* remove reference to operator if only 1 arg is const */
	if (arg_count != tot_args && arg_count > 0) {
	  SET(last_h);
	  pt(last_h) = nilexp;
	}
      }
      return mc;
  }

  case addptr_tag: {
      exp p = son(e);
      maxconst mc, mx;

      /* find the root pointer */
      while (name(p) == addptr_tag) {
	p = son(p);
      }

      mc = max_const(whole, p, ass_ok);
      ret_constlist(mc.cont);

      if (mc.self) {
	/* root pointer is constant in this context */
	exp c_list = nilexp, v_list = nilexp, x, cph, *list;

	/* construct list of ALL constant parts */
	/* initial list element will hold const. ptr */
	cph = getexp(f_bottom, nilexp, false, nilexp, nilexp,
		      0,  0, 0);
	mc.self = false;	/* assume, for moment */
	mc.cont = getexp(f_bottom, nilexp, false, cph, cph,
			  0,  0, 0);

	/* return up the chain, testing the offsets */
	while (p != e) {
	  mx = max_const(whole, bro(p), ass_ok);
	  p = bro(p);		/* p is now the offset */

	  /* add offset to appropriate list */
	  list = (mx.self)? &c_list : &v_list;
	  *list = getexp(nilexp, *list, 0, p, nilexp, 0,  0, 0);

	  if (mx.cont != nilexp) {
	    /* the offset is not constant, but PARTS of it are */

	    /* remove any "negate(name(...))" */
	    exp lim = pt(mx.cont), h = son(mx.cont);
	    while (h != nilexp) {
	      if (name(son(h)) == neg_tag && name(son(son(h))) == name_tag) {
		no(h) = -1;	/* set "done" flag */
	      }
	      h = (h == lim ? nilexp : bro(h));
	    }

	    /* add constant parts to mc */
	    bro(pt(mx.cont)) = son(mc.cont);
	    son(mc.cont) = son(mx.cont);
	    retcell(mx.cont);
	  }
	  p = bro(p);		/* p is now the next higher operation */
	}

	if (v_list == nilexp) {
	  /* whole addptr expression is constant */
	  /* return c_list elements */
	  while (c_list != nilexp) {
	    x = c_list;
	    c_list = bro(c_list);
	    retcell(x);
	  }

	  ret_constlist(mc.cont);

	  return self_const;
	}
	/* go down the chain of addptrs, rearranging offsets */
	/* NB - assumes addptr is strictly diadic, so "last" */
	/* flags are already correct		       */

	/* put non-constant offsets at the higher levels */
	while (v_list != nilexp) {
	  /* put next offset in 2nd argument position */
	  x = son(p);
	  bro(x) = son(v_list);
	  bro(bro(x)) = p;
	  p = x;		/* point to 1st argument */
	  /* traverse v_list, returning elements */
	  x = v_list;
	  v_list = bro(x);
	  retcell(x);
	}

	/* the rest is constant - add it to mc.cont */
	son(cph) = p;

	/* and put constant offsets at the lower levels */
	while (c_list != nilexp) {
	  /* put next offset in 2nd argument position */
	  x = son(p);
	  bro(x) = son(c_list);
	  bro(bro(x)) = p;
	  p = x;		/* point to 1st argument */
	  /* traverse c_list, returning elements */
	  x = c_list;
	  c_list = bro(x);
	  retcell(x);
	}

	return mc;
      } else {
	return mc_list(whole, son(e), ass_ok, true);
      }
  }

  case offset_mult_tag: {
      exp arg1 = son(e);
      exp arg2 = bro(arg1);
      maxconst mc1, mc2;
      shape ofsh = sh(e);
      mc1 = max_const(whole, arg1, ass_ok);
      mc2 = max_const(whole, arg2, ass_ok);
      if (mc1.self && mc2.self) {
	return self_const;
      }
      if (mc2.self && mc1.cont != nilexp) {
	/**********************************************************
         * the offset is const, and arg1 has some constant parts
         * so transform:
         *   offset_mult((a*b),K)
         * to:
         *   offset_mult(a,offset_mult(b,K))
         * rearranged so that the constant factors are grouped
         * with K so that the largest possible structure can be
         * extracted as constant
         *********************************************************/
	exp klist = nilexp, nklist = nilexp;
	exp *ref;
	exp m_res;
	int j;
	ret_constlist(mc1.cont);
	if (name(arg1) == mult_tag) {
	  exp m_arg = son(arg1);
	  /* sort into const and varying args */
	  while (m_arg != nilexp) {
	    mc1 = max_const(whole, m_arg, ass_ok);
	    if (mc1.self) {
	      /* add to constant operand list */
	      klist = getexp(nilexp, klist, false, m_arg, nilexp,
			      0,  0, 0);
	    } else {
	      /* add to non-constant operand list */
	      nklist = getexp(nilexp, nklist, false, m_arg, nilexp,
			       0,  0, 0);
	      ret_constlist(mc1.cont);
	    }
	    if (last(m_arg)) {
	      m_arg = nilexp;
	    } else {
	      m_arg = bro(m_arg);
	    }
	  }
	  /* build offset_mult chain with const parts innermost */
	  m_res = copy(arg2);
	  for (j = 0; j < 2; ++j) {
	    exp *list = (j == 0)? &klist : &nklist;
	    /* use klist, and then nklist */
	    while (*list != nilexp) {
	      exp z = *list;
	      exp a1 = copy(son(z));
	      exp offmul = getexp(ofsh, nilexp, false, a1, nilexp,
				   0,  0, offset_mult_tag);
	      setbro(a1, m_res);
	      clearlast(a1);
	      setbro(m_res, offmul);
	      setlast(m_res);
	      m_res = hold_refactor(offmul);
	      *list = bro(z);
	      retcell(z);
	    }
	  }
	  /* insert m_res - kill left overs */
	  ref = refto(father(e), e);
	  if (last(*ref)) {
	    setlast(m_res);
	  } else {
	    clearlast(m_res);
	  }
	  bro(m_res) = bro(*ref);
	  *ref = m_res;
	  kill_exp(e, e);
	} else {
	  m_res = e;
	}
	return mc_list(whole, son(m_res), ass_ok, true);
      }
      /* default action */
      return mc_list(whole, son(e), ass_ok, true);
  }

  default:
    if (son(e) == nilexp) {
      return self_const;
    } else {
      return mc_list(whole, son(e), ass_ok, is_a(name(e)) && optop(e));
    }
  }
}


/************************************************************************
 *  do_this_k
 *    replaces simple and compound constants in list by uses of a
 *    newly declared constant.
 *  Parameters:
 *        kdec    declaration of this new constant
 *        patn    pattern to look for
 *                NB where safe_eval has NOT been used,
 *                   patn is son(kdec)
 *        list    list of constant expresion holders
 *        limit   last constant holder in list
 ************************************************************************/

void do_this_k(exp kdec, exp patn, exp list, exp limit);

void
do_this_k(exp kdec, exp patn, exp list, exp limit)
{
  exp t = list;
  int scan = true;
  exp arglist = nilexp, ap;
  int nargs = 0;

  if (pt(list) != nilexp) {
    /* build required argument list */
    exp p = son(patn);
    while (p != nilexp) {
      exp arg_h = getexp(nilexp, arglist, 0, p, nilexp, 0, 0, 0);
      arglist = arg_h;
      ++nargs;
      p = (last(p)? nilexp : bro(p));
    }
  }
  while (scan) {
    if (no(t) == 0) {

      if (pt(t) == nilexp && eq_exp(son(t), patn)) {
	/* simple correspondence */
	exp e = son(t);
	exp f = father(e);
	exp tagt = getexp(sh(e), bro(e), (int)(last(e)),
			   kdec, pt(kdec), 0,  0, name_tag);
	pt(kdec) = tagt;
	++no(kdec);
#ifdef NEWDIAGS
	if (diagnose) {
	  dg_extracted(tagt, *(refto(f, e)));
	}
#endif
	*(refto(f, e)) = tagt;
	no(t) = -1;		/* dealt with */
	kill_exp(son(t), son(t));
      } else if (pt(t) != nilexp && name(pt(t)) == name(patn)) {
	/* try for complex match - at least the operator is correct */
	/* check errtreat ??? */
	int scan2 = true;
	int matched = 0;
	exp t2 = t, op = pt(t);


	while (matched >= 0 && scan2) {
	  if (no(t2) == 0 && pt(t2) == op) {
	    /* find match in argument list */
	    ap = arglist;

	    while (ap != nilexp &&
		  (pt(ap) != nilexp || !eq_exp(son(t2), son(ap)))) {
	      ap = bro(ap);
	    }

	    if (ap == nilexp) {
	      matched = -1;
	    } else {
	      pt(ap) = t2;
	      ++matched;
	    }
	  }
	  if (t2 == limit) {
	    scan2 = false;
	  } else {
	    t2 = bro(t2);
	  }
	}

	if (matched == nargs) {
	  exp prev_arg = nilexp, oparg = son(op), cc;
	  int last_arg;

	  cc = getexp(sh(son(kdec)), op, 1, kdec, pt(kdec), 0,
		        0, name_tag);
	  pt(kdec) = cc;
	  ++no(kdec);

	  while (oparg != nilexp) {
	    last_arg = (int)last(oparg);
	    ap = arglist;
	    while (ap != nilexp && son(pt(ap)) != oparg) {
	      ap = bro(ap);
	    }
	    if (ap == nilexp) {
	      /* this is one of the other args of op */
	      if (prev_arg == nilexp) {
		son(op) = oparg;
	      } else {
		bro(prev_arg) = oparg;
	      }
	      clearlast(oparg);
	      prev_arg = oparg;
	    }
	    oparg = (last_arg ? nilexp : bro(oparg));
	  }

	  /* now add combined constant */
	  bro(prev_arg) = cc;

	  /* mark those dealt with & clear arglist */
	  ap = arglist;
	  while (ap != nilexp) {
	    exp deadarg = son(pt(ap));
	    no(pt(ap)) = -1;
	    son(pt(ap)) = nilexp;
	    pt(ap) = nilexp;
	    kill_exp(deadarg, deadarg);
	    ap = bro(ap);
	  }
	}
      }
    }
    if (t == limit) {
      scan = false;
    } else {
      t = bro(t);
    }
  }

  /* return arglist */
  while (arglist != nilexp) {
    ap = bro(arglist);
    retcell(arglist);
    arglist = ap;
  }
}

/************************************************************************
 *  safe_arg
 *
 * insert run-time checks on this argument - see safe_eval
 *
 *  Parameters:
 *        e	argument to be tested
 *        esc	label: jump to this if e is:
 *			pointer and nil
 *			numeric and zero
 ************************************************************************/

static exp
safe_arg(exp e, exp esc)
{
  exp decl = getexp(sh(e), nilexp, 0, e, nilexp,
		     0,  0, ident_tag);
  exp v1, v2, z, s, konst, tst;

  /* make the unsafe value for this shape */
  switch (name(sh(e))) {
  case ptrhd:
    konst = me_null(sh(e), ptr_null, null_tag);
    break;
  case scharhd:
  case ucharhd:
  case swordhd:
  case uwordhd:
  case slonghd:
  case ulonghd:
  case s64hd:
  case u64hd:
    konst = getexp(sh(e), nilexp, 0, nilexp, nilexp, 0,  0, val_tag);
    break;
  case shrealhd:
  case realhd:
  case doublehd: {
      flpt f = new_flpt();
      int i;
      for (i = 0; i < MANT_SIZE; ++i) {
	(flptnos[f].mant)[i] = 0;
      }
      flptnos[f].exp = 0;
      flptnos[f].sign = 0;
      konst = getexp(sh(e), nilexp, 0, nilexp, nilexp, 0, f, real_tag);
      break;
  }
  case offsethd:
    konst = f_offset_zero(f_alignment(sh(e)));
    break;
  default:
      SET(konst);
      failer(BAD_SHAPE);
  }

  v1 = getexp(sh(e), nilexp, 0, decl, pt(decl), 0,  0, name_tag);
  pt(decl) = v1;
  ++no(decl);
  v2 = getexp(sh(e), nilexp, 1, decl, pt(decl), 0,  0, name_tag);
  pt(decl) = v2;
  ++no(decl);

  tst = getexp(f_top, nilexp, 0, v1, esc, 0,
		 0, test_tag);
  settest_number(tst, f_not_equal);
  ++no(son(esc));
  setbro(v1, konst);
  tst = hc(tst, konst);

  z = getexp(f_top, v2, 0, tst, nilexp, 0,  0, 0);
  setbro(tst, z);
  setlast(tst);
  s = getexp(sh(e), decl, 1, z, nilexp, 0,  0, seq_tag);
  setbro(e, s);
  clearlast(e);
  s = hc(s, v2);

  return hc(decl, s);
}


/************************************************************************
 *  safe_eval	ensure that the evaluation of e cannot fail
 *
 * insert run-time checks into the evaluation of this expression - this is
 * only used when a constant is extracted from inside a conditional inside
 * a loop. Where this happens, the extraction of the constant and its
 * unconditional evaluation outside the loop can result in program failure
 * when the program would not otherwise have failed.
 * This should be called with "escape_route" as nilexp - this marks the
 * outermost call of safe_eval, and causes the contruction of a label for
 * the code to escape to if a "dangerous" value is encountered during
 * evaluation of the constant. If at the end of the outermost call the label
 * has been used, then there is a possibility of failure during evaluation
 * and code is generated to supply a "safe" value when the label is reached.
 *
 * dangerous operations are:
 *	contents of NIL
 *	reffield of NIL (indirectly, when its contents are taken)
 *	division by zero (any variety; includes mod and rem)
 * Note that checking the result of reffield for NIL is a waste of time
 * since any offset from NIL will make the result different from NIL.
 *
 *
 *  Parameters:
 *        e		expression being evaluated
 *        escape_route	label: jump to this if evaluation would fail
 ************************************************************************/

static exp
safe_eval(exp e, exp escape_route)
{
  exp esc_lab, res;

  if (escape_route == nilexp) {
    /* this is outermost call - construct escape label */
    exp z = getexp(f_top, nilexp, 0, nilexp, nilexp, 0,  0, clear_tag);
    esc_lab = getexp(sh(e), nilexp, 0, z, nilexp,
		      0,  0, labst_tag);
  } else {
    esc_lab = escape_route;
  }

  switch (name(e)) {
  case ident_tag:
  case cond_tag:
  case rep_tag:
  case solve_tag:
  case case_tag:
      failer(CONSTC_ERROR);
      return nilexp;
  case name_tag:
  case env_offset_tag:
  case general_env_offset_tag:
  case real_tag:
    res = copy(e);
    break;
  case div0_tag:
  case div1_tag:
  case div2_tag:
  case fdiv_tag:
  case mod_tag:
  case rem2_tag:
  case rem0_tag:
  case offset_div_tag:
  case offset_div_by_int_tag: {
      exp arg1 = safe_eval(son(e), esc_lab);
      exp arg2 = safe_eval(bro(son(e)), esc_lab);
      res = copyexp(e);
      setson(res, arg1);
      arg2 = safe_arg(arg2, esc_lab);
      setbro(arg1, arg2);
      clearlast(arg1);
      res = hc(res, arg2);
      break;
  }
  case cont_tag: {
      exp arg = son(e);
      if (name(arg) == name_tag &&
	(isglob(son(arg)) || isvar(son(arg))))
	res = copy(e);
      else {
	arg = safe_eval(arg, esc_lab);
	if (!arg_is_reff)
	  arg = safe_arg(arg, esc_lab);
	res = copyexp(e);
	setson(res, arg);
	res = hc(res, arg);
      }
      break;
  }
  case reff_tag: {
      exp arg = son(e);
      if (name(arg) == name_tag && isglob(son(arg)))
	res = copy(e);
      else {
	arg = safe_eval(arg, esc_lab);
	if (!arg_is_reff)
	  arg = safe_arg(arg, esc_lab);
	res = copyexp(e);
	setson(res, arg);
	res = hc(res, arg);
      }
      break;
  }
  default: {
      exp k = copyexp(e);
      exp arg = son(e);
      exp p;
      if (arg == nilexp) {
	res = k;
	break;
      }
      p = safe_eval(arg, esc_lab);
      setson(k, p);
      while (!last(arg)) {
	exp safe = safe_eval(bro(arg), esc_lab);
	setbro(p, safe);
	clearlast(p);
	p = bro(p);
	arg = bro(arg);
      }
      res = hc(k, p);
      break;
  }
  }

  arg_is_reff = (name(e) == reff_tag);
  if (escape_route != nilexp) {
    return res;		/* this was an inner call */
  }

  if (no(son(esc_lab)) == 0) {
    /* the escape route is not used - inherently safe */
    retcell(son(esc_lab));
    retcell(esc_lab);
    return res;
  } else {
    /* the escape route was used - construct conditional */
    exp cond = getexp(sh(e), nilexp, 0, res, nilexp,
		       0,  0, cond_tag);
    exp safe;
    safe = getexp(sh(e), nilexp, 1, nilexp, nilexp,
		   0,  0, clear_tag);
    setbro(son(esc_lab), safe);
    IGNORE hc(esc_lab, safe);
    setbro(res, esc_lab);
    clearlast(res);
    IGNORE hc(cond, esc_lab);
    return cond;
  }
}


/************************************************************************
 *  extract_consts
 *
 *  Parameters:
 *        issn         loop is son(rf) else bro(rf)
 *        rf           EXP holding loop
 *        list_head    exp containing list of constant expressions
 *                     this must not be empty
 ************************************************************************/

static void
look_for_caonly(exp e)
{
  if (name(e) == name_tag) {
    if (isvar(son(e))) {
      clearcaonly(son(e));
    }
    return;
  }
  if (name(e) == addptr_tag) {
    look_for_caonly(son(e));
  }
  if (name(e) == seq_tag || name(e) == ident_tag) {
    look_for_caonly(bro(son(e)));
  }
  return;
}


static int
extract_consts(int issn, exp rf, exp list_head)
{
  exp val;
  int changed = 0;		/* result; will be true if we make a change */
  exp t = son(list_head);	/* first in list */
  exp limit = pt (list_head);	/* last in list */
  int contin = true;

  do {
    if (issn) {
      val = son(rf);
    } else {
      val = bro(rf);
    }
    if (no(t) != 0) {
      /* this has been dealt with previously - just * check for end */
      contin = (t != limit);
    } else {
      /* this has not been absorbed by a previous constant */

      exp e;
      int force = 0;

      if (pt(t) == nilexp) {
	/* simple constant - no brothers */
	exp f;
	e = son(t);
	f = father(e);



	/* ?????????????????? */
	if (!last(e) && last(bro(e)) && (name(f) == ident_tag) && !isvar(f)) {
	  /* this is an in-register constant declaration */
	  /* so remove the force register bit from f so  */
	  /* that it becomes a simple renaming           */
	  clearusereg(f);
	  /* and set the force register bit for the      */
	  /* outer declaration                           */
	  force = 1;
	}
#ifdef NEWDIAGS
	e = copy_dg_separate (e);	/* original may remain in use */
#else
	e = copy(e);
#endif
	/* so son(t) can be killed or used in declaration */
      } else {
	/* the next few consts are args of the same operator */
	exp op = pt(t), new_c, prev = nilexp, c_arg = nilexp, t2 = t;
	int scan = true;

	new_c = copyexp(op);

	while (scan) {
	  if (no(t2) == 0 && pt(t2) == op) {
#ifdef NEWDIAGS
	    c_arg = copy_dg_separate(son(t2));
					/* original may remain in use */
#else
	    c_arg = copy(son(t2));
#endif
	    if (prev == nilexp) {
	      son(new_c) = c_arg;
	    } else {
	      bro(prev) = c_arg;
	      clearlast(prev);
	    }
	    prev = c_arg;
	  }
	  if (t2 == limit) {
	    scan = false;
	  } else {
	    t2 = bro(t2);
	  }
	}

	e = hc(new_c, c_arg);
      }

      if (is_worth(e)) {
	/* declare new constant */
	exp konst;
	exp newdec;
	int kill_e = false;
#ifdef NEWDIAGS
	if (diagnose) {
	  strip_dg_context(e);
	}
#endif
	if (props(t) > 1) {
	  /* this const. is in a conditional in the loop */
	  /* ensure that extraction from loop does not cause a failure */
	  kill_e = true;
	  konst = safe_eval(e, nilexp);
	} else {
	  konst = e;
	}
	newdec = getexp(sh(val), bro(val),
		(int)(last(val)), konst, nilexp, 0,  0, ident_tag);
	if (has_lj_dest) {
	  setvis(newdec);
	}
	if (force && isvis(father(e))) {
	  setvis(newdec);
	} else {
#ifdef TRANS_MIPS
	  setusereg(newdec);
#else
	  if (force) {
	    setusereg(newdec);
	  }
#endif
	}

	if (name(sh(konst)) == ptrhd) {
	  look_for_caonly(konst);
	}

	bro(konst) = val;
	clearlast(konst);
	bro(val) = newdec;
	setlast(val);
	if (issn) {
	  son(rf) = newdec;
	} else {
	  bro(rf) = newdec;
	}

#ifdef NEWDIAGS
	if (diagnose) {
	  make_optim_dg(DGD_EXTRACT, newdec);
	}
#endif
	do_this_k(newdec, e, t, limit);
	if (kill_e) {
	  kill_exp(e, e);
	}
	changed = 1;		/* have made a change */
      } else {
	kill_exp(e, e);
      }
    }

    if (t == limit) {
      /* that was the last in the list */
      contin = false;
    } else {
      exp n = bro(t);
      retcell(t);
      t = n;
    }
  } while (contin);

  retcell(t);

  retcell(list_head);
  return changed;
}


/************************************************************************
 *  assigns_alias
 *
 *  scans e - returns true if any aliased variables are assigned to
 *
 *
 ************************************************************************/

int named_dest(exp dest);

int
named_dest(exp dest)
{
  switch (name(dest)) {
  case name_tag:
      if (isvar(son(dest))) {
	if (iscaonly(son(dest))) {
	  return true;
	}
	if (isglob(son(dest))) {
	  if (find_glob(son(dest))) {
	    return true;
	  }
	  if (glob_index == globmax) {
	    return false;
	  }
	  glob_dest[glob_index++] = son(dest);
	  return true;
	}
      } else if (!isvar(son(dest)) && son(son(dest)) != nilexp) {
	return named_dest(son(son(dest)));
      }
      return false;
  case addptr_tag:
  case reff_tag:
      /* Should we look at bro son to see if it contains an assignment ??? */
      return false;
  default:
    return false;
  }
}

int
assigns_alias(exp e)
{
  switch (name(e)) {
  case assvol_tag:
  case ass_tag: {
      exp dest = son(e);

      if (!named_dest(son(e))) {
	/* LHS may be aliassed */
	return true;
      } else {
	/* check RHS for assignments */
	return assigns_alias(bro(dest));
      }
    }

  case name_tag:
  case env_offset_tag:
  case general_env_offset_tag:
    return false;

  case case_tag:
    return assigns_alias(son(e));
    /* NB - must only look at first son */

  case bfass_tag:
  case apply_tag:
    return true;		/* pessimist! */

  default: {
      int aa = false;
      exp s = son(e);

      while ((s != nilexp) && !aa) {
	aa = assigns_alias(s);
	if (aa || last(s))
	  s = nilexp;
	else
	  s = bro(s);
      }

      return aa;
  }
  }
}


/************************************************************************
 *  scan_for_lv
 *
 *  scans e - returns true if any label may be long jump destination
 *
 *
 ************************************************************************/

static int
scan_for_lv(exp e)
{
  switch (name(e)) {
  case make_lv_tag:
    return true;

  case name_tag:
  case env_offset_tag:
  case general_env_offset_tag:
    return false;

  default: {
      int aa = false;
      exp s = son(e);

      while ((s != nilexp) && !aa) {
	aa = scan_for_lv(s);
	if (aa || last(s)) {
	  s = nilexp;
	} else {
	  s = bro(s);
	}
      }

      return aa;
  }
  }
}


/************************************************************************
 *  repeat_consts
 *
 *  calls extract_consts on each element of the list of repeat loops
 ************************************************************************/

void
repeat_consts(void)
{
  exp reps = get_repeats();

  while (reps != nilexp) {
    if (son(reps) != nilexp && name(son(reps)) == rep_tag
	&& no(reps) < max_loop_depth) {
      exp loop = son(reps);
      exp sts = bro(son(loop));
      int no_alias;
      maxconst mx;
      exp consts;

      /* put old identifier memory list into its free list */
      memlist **mptr = &mem;

      glob_index = 0;
      no_alias = !assigns_alias(sts);
      while (*mptr != nilmem) {
	mptr = & ((*mptr) ->next);
      }
      *mptr = fmem;
      fmem = mem;
      mem = nilmem;

      mx = mc_list(loop, sts, no_alias, false);

      consts = mx.cont;
      /* NB - false forces a list to be produced */

      if (no_alias) {
	set_noalias (reps);	/* preserve for forall processing */
      }

      if (consts != nilexp) {
	exp rr;
	int sn;
	exp fa = father(loop);
	if (son(fa) == loop) {
	  sn = 1;
	  rr = fa;
	} else {
	  sn = 0;
	  rr = son(fa);
	  while (bro(rr) != loop && !last(rr)) {
	    rr = bro(rr);
	  }
	}
	if (sn || bro(rr) == loop) {
	  while (name(fa) != proc_tag && name(fa) != general_proc_tag &&
		 name(fa) != hold_tag && name(fa) != hold2_tag) {
	    fa = father(fa);
	  }
	  if (name(fa) != hold_tag && name(fa) != hold2_tag) {
	    if (proc_uses_crt_env(fa)) {
	      has_lj_dest = scan_for_lv(sts);
	    } else {
	      has_lj_dest = 0;
	    }
	    IGNORE extract_consts(sn, rr, consts);
	  }
	}
      }
    }
    reps = pt(reps);
  }
}


/************************************************************************
 *  get_repeats
 *
 *  calculates maximum distance of every repeat from a leaf node
 *  (this allows repeat processing to be restricted to inner loops)
 *  returns the repeat_list
 ************************************************************************/

exp
get_repeats(void)
{
  if (repeat_list != nilexp && !is_dist(repeat_list)) {
    exp reps = repeat_list;

    while (reps != nilexp) {
      if (no(reps) == 0) {
	/* this is a leaf node */
	/* no(x) is used in dexp to count directly nested loops */
	int dist = 0;
	exp sup = reps;
	do {
	  set_dist (sup);	/* no(x) is now max dist to leaf */
	  no(sup) = dist;
	  if (son(sup) != nilexp && name(son(sup)) == rep_tag) {
	    ++dist;		/* only repeats are significant */
	  }
	  sup = bro(sup);	/* go to enclosing repeat */
	} while (sup != nilexp && (!is_dist(sup) || no(sup) < dist));
      }
      reps = pt(reps);
    }
  }
  return repeat_list;
}


/************************************************************************
 *  return_repeats
 *
 *  returns the storage used by repeat_list
 ************************************************************************/

void
return_repeats(void)
{
  exp reps = repeat_list;

  while (reps != nilexp) {
    exp next = pt(reps);
    retcell(reps);
    reps = next;
  }
  repeat_list = nilexp;
}
