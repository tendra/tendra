/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* a rather more complicated equivalence of expressions - allows sequences and
conditionals with tests which only jump to nearest conditional outlab;
initial call : comp_eq_exp(a,b,nilexp,nilexp)  */

#include <stddef.h>

#include <local/exptypes.h>
#include <local/expmacs.h>
#include <local/exptypes.h>

#include <construct/tags.h>
#include <construct/shapemacs.h>
#include <construct/exp.h>

#include "comp_eq_exp.h"

bool
comp_eq_explist(exp a, exp b, exp laba, exp labb)
{
  if (a==nilexp) return b==nilexp;
  if (b==nilexp || !comp_eq_exp(a,b,laba,labb) ) return 0;
  if (last(a)) return last(b);
  if (last(b)) return 0;
  return comp_eq_explist(bro(a), bro(b), laba, labb);
}
	

bool
comp_eq_exp(exp a, exp b, exp laba, exp labb)
{
  if (name(a) != name(b) || !eq_shape(sh(a), sh(b))) return 0;
  if (name(a) == seq_tag) {
    return comp_eq_explist(son(son(a)), son(son(b)), laba, labb) &&
	    comp_eq_exp(bro(son(a)), bro(son(b)),laba,labb);
  }
  if (name(a) == cond_tag) {
    exp fa = son(a);
    exp fb = son(b);
    return comp_eq_exp(fa,fb, bro(fa), bro(fb)) &&
	    comp_eq_exp(bro(son(bro(fa))), bro(son(bro(fb))), laba, labb);
  }
  if (name(a)==test_tag) {
    return pt(a)==laba && pt(b)==labb && props(a)==props(b) &&
	   comp_eq_explist(son(a),son(b), laba, labb);
  }
  if (name(a)==name_tag) {
    return son(a)==son(b) && no(a)==no(b);
  }
  return is_a(name(a)) && no(a)==no(b) &&
	  comp_eq_explist(son(a), son(b), laba, labb);
}




