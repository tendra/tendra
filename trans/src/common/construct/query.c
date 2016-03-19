/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/query.h>

static bool
invariant_to_apply(exp e);

bool
is_tester(exp e, int eq)
{
	if (e->tag == test_tag || e->tag == testbit_tag) {
		if (!eq || test_number(e) == f_equal) {
			return true;
		}
	}
	return false;
}


/* looks for things like
	(a ~ b) ? a : b
	puts test in t - can make use of delay-slot
*/
bool
is_maxlike(exp x, exp *t)
{
	exp op1, op2, z, l, w;
	if (x->tag != cond_tag) {
		goto flab0;
	}
	{
		exp xC = son(x);
		if (xC->tag != seq_tag) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			{
				exp xCCC = son(xCC);
				*t = xCCC;
				if (xCCC->tag != test_tag) {
					goto flab0;
				}
				l=pt(*t);
				{
					exp xCCCC = son(xCCC);
					op1 = xCCCC;
					if (!(!is_floating(sh(op1)->tag))) {
						goto flab0;
					}
					if (xCCCC->last) {
						goto flab0;
					}
					xCCCC = bro(xCCCC);
					op2 = xCCCC;
					if (!xCCCC->last) {
						goto flab0;
					}
				}
				if (!xCCC->last) {
					goto flab0;
				}
			}
			if (xCC->last) {
				goto flab0;
			}
			xCC = bro(xCC);
			z = xCC;
			if (!(comp_eq_exp(z, op1, NULL,NULL))) {
				goto flab0;
			}
			if (!xCC->last) {
				goto flab0;
			}
		}
		if (xC->last) {
			goto flab0;
		}
		xC = bro(xC);
		if (l != xC) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			z = xCC;
			if (!(no(z) == 1)) {
				goto flab0;
			}
			if (xCC->last) {
				goto flab0;
			}
			xCC = bro(xCC);
			w = xCC;
			if (!(comp_eq_exp(w, op2, NULL, NULL))) {
				goto flab0;
			}
			if (!xCC->last) {
				goto flab0;
			}
		}
		if (!xC->last) {
			goto flab0;
		}
	}
	return true;
flab0:
	return false;
}


/* looks for things like
	(a ~ b) ? b : a
	puts test in t - can make use of delay-slot
*/
bool
is_minlike(exp x, exp *t)
{
	exp op1, op2, z, l, w;
	if (x->tag != cond_tag) {
		goto flab0;
	}
	{
		exp xC = son(x);
		if (xC->tag != seq_tag) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			{
				exp xCCC = son(xCC);
				*t = xCCC;
				if (xCCC->tag != test_tag) {
					goto flab0;
				}
				l=pt(*t);
				{
					exp xCCCC = son(xCCC);
					op1 = xCCCC;
					if (!(!is_floating(sh(op1)->tag))) {
						goto flab0;
					}
					if (xCCCC->last) {
						goto flab0;
					}
					xCCCC = bro(xCCCC);
					op2 = xCCCC;
					if (!xCCCC->last) {
						goto flab0;
					}
				}
				if (!xCCC->last) {
					goto flab0;
				}
			}
			if (xCC->last) {
				goto flab0;
			}
			xCC = bro(xCC);
			z = xCC;
			if (!(comp_eq_exp(z, op2,NULL,NULL))) {
				goto flab0;
			}
			if (!xCC->last) {
				goto flab0;
			}
		}
		if (xC->last) {
			goto flab0;
		}
		xC = bro(xC);
		if (l != xC) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			z = xCC;
			if (!(no(z) == 1)) {
				goto flab0;
			}
			if (xCC->last) {
				goto flab0;
			}
			xCC = bro(xCC);
			w = xCC;
			if (!(comp_eq_exp(w, op1,NULL,NULL))) {
				goto flab0;
			}
			if (!xCC->last) {
				goto flab0;
			}
		}
		if (!xC->last) {
			goto flab0;
		}
	}
	return true;
flab0:
	return false;
}

/* looks for things like
	(a~0) ? a:-a
*/
bool
is_abslike(exp x, exp *t)
{
  exp op, l, z, w;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op = xCCCC;
          if (xCCCC->last) goto flab0;
          xCCCC = bro(xCCCC);
          if (xCCCC->tag != val_tag || no(xCCCC) != 0) goto flab0;
          if(!xCCCC->last) goto flab0;
        }
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op,NULL,NULL))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      if (xCC->tag != neg_tag) goto flab0;
      { exp xCCC = son(xCC);
        w = xCCC;
        if (!(comp_eq_exp(op, w,NULL,NULL))) goto flab0;
        if(!xCCC->last) goto flab0;
      }
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return true;
  flab0: return false;
}

bool
is_fabslike(exp x, exp *t)
{
  exp op, l, z, w;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op = xCCCC;
          if (xCCCC->last) goto flab0;
          xCCCC = bro(xCCCC);
          if (xCCCC->tag != val_tag || no(xCCCC) != 0) goto flab0;
          if(!xCCCC->last) goto flab0;
        }
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(eq_exp(z, op))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      if (xCC->tag != fneg_tag) goto flab0;
      { exp xCCC = son(xCC);
        w = xCCC;
        if (!(eq_exp(op, w))) goto flab0;
        if(!xCCC->last) goto flab0;
      }
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return true;
  flab0: return false;
}

bool
is_condassign(exp e, exp *to_test, exp *to_ass)
{
	exp arg1 = son(e);
	exp arg2 = bro(arg1);
	exp z;
	exp st;
	exp ass;
	exp val;
	if (arg1->tag != seq_tag) {
		return false;
	}

	z = son(arg1);
	st = son(z);
	ass = bro(z);

	if (no(son(arg2)) != 1 || bro(son(arg2))->tag != top_tag) {
		return false;
	}
	if (st->tag != test_tag && st->tag != testbit_tag) {
		return false;
	}
	if (!st->last) {
		return false;
	}
	if (ass->tag != ass_tag) {
		return false;
	}
	if (son(ass)->tag != name_tag || !isvar(son(son(ass)))) {
		return false;
	}

	val = bro(son(ass));
	*to_test = st;
	*to_ass = ass;
	if (val->tag == val_tag) {
		return true;
	}

	return false;
}

/* a rather more complicated equivalence of expressions - allows sequences and
conditionals with tests which only jump to nearest conditional outlab;
initial call : comp_eq_exp(a,b,NULL,NULL)  */

static bool
comp_eq_explist(exp a, exp b, exp laba, exp labb)
{
	if (a == NULL) return b == NULL;
	if (b == NULL || !comp_eq_exp(a,b,laba,labb)) return 0;
	if (a->last) return b->last;
	if (b->last) return 0;
	return comp_eq_explist(bro(a), bro(b), laba, labb);
}


bool
comp_eq_exp(exp a, exp b, exp laba, exp labb)
{
	if (a->tag != b->tag || !eq_shape(sh(a), sh(b))) {
		return 0;
	}
	if (a->tag == seq_tag) {
		return(comp_eq_explist(son(son(a)), son(son(b)), laba,
					  labb) &&
		       comp_eq_exp(bro(son(a)), bro(son(b)),laba,labb));
	}
	if (a->tag == cond_tag) {
		exp fa = son(a);
		exp fb = son(b);
		return(comp_eq_exp(fa,fb, bro(fa), bro(fb)) &&
		       comp_eq_exp(bro(son(bro(fa))), bro(son(bro(fb))),
				      laba, labb));
	}
	if (a->tag ==test_tag) {
		return(pt(a) ==laba && pt(b) ==labb && props(a) ==props(b) &&
		       comp_eq_explist(son(a),son(b), laba, labb));
	}
	if (a->tag ==name_tag) {
		return son(a) == son(b) && no(a) == no(b);
	}

	return is_a(a->tag) && no(a) ==no(b) &&
	       comp_eq_explist(son(a), son(b), laba, labb);
}

/*
Pattern in oddtest.pat
this is intended to be the pattern for:
	if (test) fexp 1 else fexp -1
to transform to:
	fexp ( (absbool(test) <<1) -1))
where f is any sequence of unary operators including identity
*/


static bool
oddunary(exp x, exp y, exp *v)
{
  exp z;
  *v = x;
  if (x->tag != val_tag) goto flab1;
  if (!(y->tag==val_tag && ((no(x)==1 && no(y)==-1) || (no(x)==-1 && no(y)==1) ))) goto flab1;
  goto tlab1;
  flab1:
  if (x->tag != y->tag) goto flab0;
  { exp xC = son(x);
    z = xC;
    if (!(z!=NULL && z->last && son(y) != NULL && oddunary(z, son(y),v))) goto flab0;
    if(!xC->last) goto flab0;
  }
  tlab1:
  return true;
  flab0: return false;
}

bool
oddtest(exp x, exp *t, exp *f, exp *v)
{
  exp l, z, g;
  if (x->tag != cond_tag) goto flab0;
  { exp xC = son(x);
    if (xC->tag != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (xCCC->tag != test_tag) goto flab0;
        l =pt(*t);
        if(!xCCC->last) goto flab0;
      }
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      *f = xCC;
      if(!xCC->last) goto flab0;
    }
    if (xC->last) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (xCC->last) goto flab0;
      xCC = bro(xCC);
      g = xCC;
      if (!(oddunary(*f,g,v))) goto flab0;
      if(!xCC->last) goto flab0;
    }
    if(!xC->last) goto flab0;
  }
  return true;
  flab0: return false;
}

