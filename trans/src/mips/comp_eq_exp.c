/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* a rather more complicated equivalence of expressions - allows sequences and
conditionals with tests which only jump to nearest conditional outlab;
initial call : comp_eq_exp(a,b,NULL,NULL)  */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/exp.h>

#include <construct/exp.h>

#include "comp_eq_exp.h"

static bool
comp_eq_explist(exp a, exp b, exp laba, exp labb)
{
	if (a==NULL) return b==NULL;
	if (b==NULL || !comp_eq_exp(a,b,laba,labb) ) return 0;
	if (a->last) return (b->last);
	if (b->last) return 0;
	return comp_eq_explist(bro(a), bro(b), laba, labb);
}


bool
comp_eq_exp(exp a, exp b, exp laba, exp labb)
{
	if (a->tag != b->tag || !eq_shape(sh(a), sh(b))) return 0;
	if (a->tag == seq_tag) {
		return (comp_eq_explist(son(son(a)), son(son(b)), laba, labb) &&
			comp_eq_exp(bro(son(a)), bro(son(b)),laba,labb) );
	}
	if (a->tag == cond_tag) {
		exp fa = son(a);
		exp fb = son(b);
	 	return (comp_eq_exp(fa,fb, bro(fa), bro(fb)) &&
	 		  comp_eq_exp(bro(son(bro(fa))), bro(son(bro(fb))), laba, labb) );
	}
	if (a->tag==test_tag) {
		return(pt(a)==laba && pt(b)==labb && props(a)==props(b) &&
			comp_eq_explist(son(a),son(b), laba, labb) );
	}
	if (a->tag==name_tag) {
		return (son(a)==son(b) && no(a)==no(b));
	}

	return (is_a(a->tag) && no(a)==no(b) &&
		 comp_eq_explist(son(a), son(b), laba, labb) );
}
