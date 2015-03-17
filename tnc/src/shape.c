/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "config.h"

#include "types.h"
#include "alignment.h"
#include "check.h"
#include "eval.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    These shapes are fixed.
*/

node *sh_bottom = null;
node *sh_proc = null;
node *sh_top = null;


/*
    This routine initializes the basic shapes above.
*/

void
init_shapes(void)
{
    if (sh_bottom == null) {
	/* Construct sh_bottom */
	sh_bottom = new_node();
	sh_bottom->cons = cons_no(SORT_shape, ENC_bottom);

	/* Construct sh_proc */
	sh_proc = new_node();
	sh_proc->cons = cons_no(SORT_shape, ENC_proc);

	/* Construct sh_top */
	sh_top = new_node();
	sh_top->cons = cons_no(SORT_shape, ENC_top);

	/* Initialize alignments */
	init_alignments();
    }
    return;
}


/*
    CREATE A NAT CORRESPONDING TO THE LENGTH OF STRING s

    This routine returns a nat giving the length of the string s or the
    null node if this cannot be found.
*/

node *
string_length(node *s)
{
    if (s->cons->encoding == ENC_make_string) {
	node *str = s->son;
	long n = str->cons->encoding;
	if (n == -1) {
	    str = str->son->bro;
	    n = str->cons->encoding;
	}
	return make_nat(n);
    }
    return null;
}


/*
    This routine makes a copy of the node p.
*/

node *
copy_node(node *p)
{
    node *q;
    if (p == null) return null;
    q = new_node();
    if (p->cons->alias) {
	q->cons = p->cons->alias;
    } else {
	q->cons = p->cons;
    }
    q->son = p->son;
    q->shape = p->shape;
    return q;
}


/*
    This routine creates an integer shape from a variety p.
*/

node *
sh_integer(node *p)
{
    node *q = new_node();
    q->cons = cons_no(SORT_shape, ENC_integer);
    q->son = new_node();
    if (p == null) {
	q->son->cons = &unknown_cons;
    } else {
	q->son->cons = p->cons;
	q->son->son = p->son;
    }
    return q;
}


/*
    This routine creates a floating shape from a floating variety p.
*/

node *
sh_floating(node *p)
{
    node *q = new_node();
    q->cons = cons_no(SORT_shape, ENC_floating);
    q->son = new_node();
    if (p == null) {
	q->son->cons = &unknown_cons;
    } else {
	q->son->cons = p->cons;
	q->son->son = p->son;
    }
    return q;
}


/*
    This routine creates a pointer shape from an alignment p or a shape p.
*/

node *
sh_pointer(node *p)
{
    node *q = new_node();
    q->cons = cons_no(SORT_shape, ENC_pointer);
    q->son = new_node();
    p = al_shape(p);
    if (p == null) {
	q->son->cons = &unknown_cons;
    } else {
	q->son->cons = p->cons;
	q->son->son = p->son;
    }
    return q;
}


/*
    This routine creates an offset shape from the alignments p and q.
*/

node *
sh_offset(node *p, node *q)
{
    node *r = new_node();
    r->cons = cons_no(SORT_shape, ENC_offset);
    r->son = new_node();
    p = al_shape(p);
    q = al_shape(q);
    al_includes(p, q);
    if (p == null) {
	r->son->cons = &unknown_cons;
    } else {
	r->son->cons = p->cons;
	r->son->son = p->son;
    }
    r->son->bro = new_node();
    if (q == null) {
	r->son->bro->cons = &unknown_cons;
    } else {
	r->son->bro->cons = q->cons;
	r->son->bro->son = q->son;
    }
    return r;
}


/*
    This routine creates an array shape consisting of n copies of
    the shape p.
*/

node *
sh_nof(node *n, node *p)
{
    node *q = new_node();
    q->cons = cons_no(SORT_shape, ENC_nof);
    q->son = new_node();
    if (n == null) {
	q->son->cons = &unknown_cons;
    } else {
	q->son->cons = n->cons;
	q->son->son = n->son;
    }
    q->son->bro = new_node();
    if (p == null) {
	q->son->bro->cons = &unknown_cons;
    } else {
	q->son->bro->cons = p->cons;
	q->son->bro->son = p->son;
    }
    return q;
}


/*
    This routine creates a bitfield shape from a bitfield variety p.
*/

node *
sh_bitfield(node *p)
{
    node *q = new_node();
    q->cons = cons_no(SORT_shape, ENC_bitfield);
    q->son = new_node();
    if (p == null) {
	q->son->cons = &unknown_cons;
    } else {
	q->son->cons = p->cons;
	q->son->son = p->son;
    }
    return q;
}


/*
    This routine creates a compound shape from an expression p.
*/

node *
sh_compound(node *p)
{
    node *q = new_node();
    q->cons = cons_no(SORT_shape, ENC_compound);
    q->son = new_node();
    if (p == null) {
	q->son->cons = &unknown_cons;
    } else {
	q->son->cons = p->cons;
	q->son->son = p->son;
    }
    return q;
}


/*
    This routine returns the normalized version of the shape p.
*/

node *
normalize(node *p)
{
    if (p == null) return null;
    if (p->cons->sortnum == SORT_shape) {
	switch (p->cons->encoding) {
	    case ENC_shape_apply_token: {
		node *q = expand_tok(p);
		if (q) return normalize(q);
		break;
	    }
	    case ENC_offset: {
		node *al1 = al_shape(p->son);
		node *al2 = al_shape(p->son->bro);
		return sh_offset(al1, al2);
	    }
	    case ENC_pointer: {
		return sh_pointer(al_shape(p->son));
	    }
	}
    }
    return copy_node(p);
}


/*
    If p is the application of a token it is replaced by the definition
    of that token.  If this is null, null is returned, otherwise the
    expansion continues until p is not a token application.
*/

node *
expand_tok(node *p)
{
    int count = 0;
    sortname s = p->cons->sortnum;
    while (p->cons->encoding == sort_tokens[s]) {
	tok_info *info = get_tok_info(p->son->cons);
	if (info->def) {
	    p = info->def;
	    if (p->cons->sortnum == SORT_completion)p = p->son;
	} else {
	    return null;
	}
	if (++count > 100) return null;
    }
    return p;
}


/*
    This routine checks the nodes p and q, which consists of shapes
    or components of shapes, are compatible.  Its action depends on
    the value of tg.  If tg is 0 or 1 then, if the shapes are compatible
    or possible compatible either p or q (whichever is more useful) is
    returned; otherwise an error is reported.  If tg is 2, the routine
    returns sh_bottom if either p or q is the shape bottom, p if p and
    q are definitely compatible, null is they are possible compatible,
    and sh_top if they are definitely not compatible.
*/

node *
check_shapes(node *p, node *q, int tg)
{
    sortname s;
    long np, nq;
    bool ok = 1;
    node *p0 = (tg == 2 ? null : p);
    node *q0 = (tg == 2 ? null : q);
    node *p1 = p;
    bool check_further = 0;

    /* If one is unknown, return the other */
    if (p == null) return q0;
    if (q == null) return p0;
    if (p->cons->sortnum == SORT_unknown) return q0;
    if (q->cons->sortnum == SORT_unknown) return p0;

    s = p->cons->sortnum;
    np = p->cons->encoding;
    nq = q->cons->encoding;

    /* Check for tokens */
    if (np == sort_tokens[s]) {
	p = expand_tok(p);
	if (p == null) {
	    if (np == nq && p1->son->cons == q->son->cons) {
		if (p1->son->son == null) return p1;
	    }
	    return q0;
	}
	np = p->cons->encoding;
    }
    if (nq == sort_tokens[s]) {
	q = expand_tok(q);
	if (q == null) return p0;
	nq = q->cons->encoding;
    }

    switch (s) {

	case SORT_shape: {
	    /* Check for bottoms */
	    if (tg == 2) {
		if (np == ENC_bottom) return sh_bottom;
		if (nq == ENC_bottom) return sh_bottom;
	    }
	    /* Don't know about or conditionals */
	    if (np == ENC_shape_cond) return q0;
	    if (nq == ENC_shape_cond) return p0;
	    if (np != nq) {
		ok = 0;
	    } else {
		switch (np) {

		    case ENC_bitfield:
		    case ENC_floating:
		    case ENC_integer:
		    case ENC_nof: {
			/* Some shapes are inspected closer */
			check_further = 1;
			break;
		    }

		    /* case ENC_pointer */
		    /* case ENC_offset */

		    case ENC_bottom:
		    case ENC_proc:
		    case ENC_top: {
			/* These are definitely compatible */
			if (tg == 2) return p1;
			break;
		    }
		}
	    }
	    break;
	}

	case SORT_bitfield_variety: {
	    /* Don't know about conditionals */
	    if (np == ENC_bfvar_cond) return q0;
	    if (nq == ENC_bfvar_cond) return p0;
	    if (np != nq) {
		ok = 0;
	    } else {
		/* Simple bitfield varieties are inspected closer */
		if (np == ENC_bfvar_bits)check_further = 1;
	    }
	    break;
	}

	case SORT_bool: {
	    /* Don't know about conditionals */
	    if (np == ENC_bool_cond) return q0;
	    if (nq == ENC_bool_cond) return p0;
	    if (np != nq)ok = 0;
	    if (tg == 2) return ok ? p1 : sh_top;
	    break;
	}

	case SORT_floating_variety: {
	    /* Don't know about conditionals */
	    if (np == ENC_flvar_cond) return q0;
	    if (nq == ENC_flvar_cond) return p0;
	    if (np != nq) {
		ok = 0;
	    } else {
		/* Simple floating varieties are inspected closer */
		if (np == ENC_flvar_parms)check_further = 1;
	    }
	    break;
	}

	case SORT_nat: {
	    /* Don't know about conditionals */
	    if (np == ENC_nat_cond) return q0;
	    if (nq == ENC_nat_cond) return p0;
	    if (np != nq) {
		ok = 0;
	    } else {
		/* Simple nats are checked */
		if (np == ENC_make_nat) {
		    if (!eq_node(p->son, q->son))ok = 0;
		    if (tg == 2) return ok ? p1 : sh_top;
		}
	    }
	    break;
	}

	case SORT_signed_nat: {
	    /* Don't know about conditionals */
	    if (np == ENC_signed_nat_cond) return q0;
	    if (nq == ENC_signed_nat_cond) return p0;
	    if (np != nq) {
		ok = 0;
	    } else {
		/* Simple signed_nats are checked */
		if (np == ENC_make_signed_nat) {
		    if (!eq_node(p->son, q->son))ok = 0;
		    if (tg == 2) return ok ? p1 : sh_top;
		}
	    }
	    break;
	}

	case SORT_variety: {
	    /* Don't know about conditionals */
	    if (np == ENC_var_cond) return q0;
	    if (nq == ENC_var_cond) return p0;
	    if (np != nq) {
		ok = 0;
	    } else {
		/* Simple varieties are inspected closer */
		if (np == ENC_var_limits)check_further = 1;
	    }
	    break;
	}

	default : {
	    is_fatal = 0;
	    input_error("Shouldn't be checking %s's", sort_name(s));
	    break;
	}
    }

    /* Check arguments if necessary */
    if (check_further) {
	node *xp = p->son;
	node *xq = q->son;
	while (xp && xq) {
	    node *c = check_shapes(xp, xq, tg);
	    if (tg == 2) {
		if (c == null) return null;
		if (c == sh_top) return sh_top;
	    }
	    xp = xp->bro;
	    xq = xq->bro;
	}
    } else {
	if (tg == 2) return null;
    }

    if (!ok) {
	/* Definitely not compatible */
	if (tg == 2) return sh_top;
	is_fatal = 0;
	if (tg) {
	    input_error("Shape of tag %s does not match declaration",
			  checking);
	} else {
	    input_error("Shape incompatibility in %s", checking);
	}
	return null;
    }
    return p1;
}


/*
    This routine returns the least upper bound of the shapes p and q.
    A return value of null means that the result is unknown.
*/

node *
lub(node *p, node *q)
{
    return check_shapes(p, q, 2);
}


/*
    The shape of the expression p is checked to be of the form indicated
    by t.  If so (or possibly so) the shape is returned, otherwise an error
    is flagged and null is returned.
*/

node *
check1(int t, node *p)
{
    long n;
    char *nm = p->cons->name;
    node *s = p->shape, *s0 = s;

    if (s == null) return null;
    if (s->cons->sortnum == SORT_unknown) return s;
    if (t >= ENC_shape_none) return s;

    n = s->cons->encoding;
    if (n == ENC_shape_apply_token) {
	s = expand_tok(s);
	if (s == null) return s0;
	n = s->cons->encoding;
    }

    if (n == ENC_shape_cond) {
	/* Don't know about conditionals */
    } else if (n != (long)t) {
	char tbuff[1000];
	construct *c = cons_no(SORT_shape, t);
	if (p->cons->encoding == ENC_exp_apply_token) {
	    IGNORE sprintf(tbuff, "%s (%s)", nm, p->son->cons->name);
	    nm = tbuff;
	}
	is_fatal = 0;
	input_error("%s argument to %s should be of %s shape",
		      nm, checking, c->name);
	return null;
    }
    return normalize(s);
}


/*
    The shapes of the expressions p and q are checked to be of the form
    indicated by t and to be compatible.  The shape or null is returned.
*/

node *
check2(int t, node *p, node *q)
{
    node *sp = check1(t, p);
    node *sq = check1(t, q);

    if (t == ENC_nof) {
	/* For arrays check for concat_nof */
	node *s = null;
	node *n = null;
	if (sp && sq) {
	    sp = expand_tok(sp);
	    sq = expand_tok(sq);
	    if (sp && sp->cons->encoding == ENC_nof &&
		 sq && sq->cons->encoding == ENC_nof) {
		/* Find base shape of array */
		s = check_shapes(sp->son->bro, sq->son->bro, 0);
		sp = expand_tok(sp->son);
		sq = expand_tok(sq->son);
		if (sp && sp->cons->encoding == ENC_make_nat &&
		     sq && sq->cons->encoding == ENC_make_nat) {
		    /* Arrays of known size - find concatenated size */
		    construct *np = sp->son->cons;
		    construct *nq = sp->son->cons;
		    if (np->sortnum == SORT_small_tdfint &&
			 nq->sortnum == SORT_small_tdfint) {
			long up = np->encoding;
			long uq = nq->encoding;
			long umax = ((long)1) << 24;
			if (up <= umax && uq <= umax) {
			    n = make_nat(up + uq);
			}
		    }
		}
	    }
	}
	return sh_nof(n, s);
    }

    return check_shapes(sp, sq, 0);
}


/*
    The shapes of the list of expressions given by p are checked to be
    of the form indicated by t and to be compatible.  The shape or
    null is returned.  If nz is true an error is flagged if p is the
    empty list.
*/

node *
checkn(int t, node *p, int nz)
{
    node *q, *r;
    if (p->cons->encoding == 0) {
	if (nz) {
	    is_fatal = 0;
	    input_error("Repeated statement in %s cannot be empty",
			  checking);
	}
	return null;
    }
    q = p->son;
    r = check1(t, q);
    while (q = q->bro, q != null) {
	node *s = check1(t, q);
	r = check_shapes(r, s, 0);
    }
    return r;
}


/*
    This routine assigns the values given by p to the formal token
    arguments given in c.  It is a prelude to expanding token applications.
    Any missing arguments are set to null.  The routine returns the list
    of previous argument values if set is true.
*/

node *
set_token_args(construct **c, node *p, int set)
{
    node *q = null;
    node *aq = null;
    if (c) {
	while (*c) {
	    tok_info *info = get_tok_info(*c);
	    if (set) {
		node *r = info->def;
		if (r) {
		    r = copy_node(r);
		    if (aq == null) {
			q = r;
		    } else {
			aq->bro = r;
		    }
		    aq = r;
		}
	    }
	    info->def = copy_node(p);
	    if (p)p = p->bro;
	    c++;
	}
    }
    return q;
}


/*
    This routine checks whether the construct c introduces a local tag or
    label.
*/

static int
is_intro_exp(construct *c)
{
    if (c->sortnum == SORT_exp) {
	switch (c->encoding) {
	    case ENC_apply_general_proc:
	    case ENC_conditional:
	    case ENC_identify:
	    case ENC_labelled:
	    case ENC_make_general_proc:
	    case ENC_make_proc:
	    case ENC_repeat:
	    case ENC_variable: {
		return 1;
	    }
	}
    }
    return 0;
}


/*
    This routine returns 4 if p is itself an application of a token, 3 if
    it is a make_label construct which introduces a new label (the intro
    flag is used to determine this) or a make_tag construct which introduces
    a new tag, 2 if it is a use of such an introduced label or tag, 1 if
    some subnode returns at least tok, and 0 otherwise.
*/

static int
contains_tokens(node *p, int intro, int tok)
{
    long n;
    node *q;
    sortname s;
    if (p == null) return 0;
    s = p->cons->sortnum;
    n = p->cons->encoding;
    switch (s) {
	case SORT_al_tag: {
	    if (n == ENC_make_al_tag) return 0;
	    intro = 0;
	    break;
	}
	case SORT_label: {
	    if (n == ENC_make_label) {
		if (intro) {
		    p->cons->alias = p->cons;
		    return 3;
		}
		if (p->cons->alias) return 2;
		return 0;
	    }
	    intro = 0;
	    break;
	}
	case SORT_tag: {
	    if (n == ENC_make_tag) {
		if (intro) {
		    p->cons->alias = p->cons;
		    return 3;
		}
		if (p->cons->alias) return 2;
		return 0;
	    }
	    intro = 0;
	    break;
	}
	case SORT_token: {
	    if (n == ENC_make_tok) return 0;
	    intro = 0;
	    break;
	}
	case SORT_exp: {
	    intro = is_intro_exp(p->cons);
	    break;
	}
	default : {
	    if (s > 0)intro = 0;
	    break;
	}
    }
    if (p->cons == &shape_of) {
	tok_info *info = get_tok_info(p->son->cons);
	q = info->def;
	if (q && q->cons->sortnum == SORT_completion)q = q->son;
	if (q && q->shape) return 4;
	p = p->son;
    }
    if (s > 0 && n == sort_tokens[s]) {
	tok_info *info = get_tok_info(p->son->cons);
	q = info->def;
	if (q) return 4;
	p = p->son;
    }
    for (q = p->son; q; q = q->bro) {
	int c = contains_tokens(q, intro, tok);
	if (c == 1 || c >= tok) return 1;
    }
    return 0;
}


/*
    The node p which has contains_tokens value c (see above) is expanded
    recursively.  def is true during the expansion of a token definition.
*/

static node *
expand_fully_aux(node *p, int c, int def)
{
    node *q;
    switch (c) {
	case 1: {
	    /* Expand arguments */
	    node *ap;
	    node *aq = null;
	    int intro = is_intro_exp(p->cons);
	    q = new_node();
	    q->cons = p->cons;
	    q->shape = p->shape;
	    for (ap = p->son; ap; ap = ap->bro) {
		node *a;
		c = contains_tokens(ap, intro, 2);
		a = expand_fully_aux(ap, c, def);
		if (aq) {
		    aq->bro = a;
		} else {
		    q->son = a;
		}
		aq = a;
	    }
	    break;
	}
	case 2: {
	    /* Tag or label usage */
	    q = copy_node(p);
	    q->son = copy_node(q->son);
	    break;
	}
	case 3: {
	    /* Tag or label declaration */
	    p->son->cons->alias = null;
	    if (def) {
		copy_construct(p->son->cons);
		q = copy_node(p);
		q->son = copy_node(q->son);
	    } else {
		q = copy_node(p);
	    }
	    break;
	}
	case 4: {
	    /* Token application */
	    construct *tok = p->son->cons;
	    tok_info *info = get_tok_info(tok);
	    q = info->def;
	    if (q) {
		if (info->depth < 100) {
		    node *prev;
		    info->depth++;
		    if (q->cons->sortnum == SORT_completion)q = q->son;
		    if (p->cons == &shape_of)q = q->shape;
		    prev = set_token_args(info->pars, p->son->son, 1);
		    c = contains_tokens(q, 0, 2);
		    q = expand_fully_aux(q, c, 1);
		    IGNORE set_token_args(info->pars, prev, 0);
		    info->depth--;
		} else {
		    is_fatal = 0;
		    input_error("Nested expansion of token %s", tok->name);
		    q = copy_node(p);
		    info->depth++;
		}
	    } else {
		q = copy_node(p);
		info->depth++;
	    }
	    break;
	}
	default : {
	    /* Simple construct */
	    q = copy_node(p);
	    break;
	}
    }
    return q;
}


/*
    All applications of tokens in p are expanded.
*/

node *
expand_fully(node *p)
{
    if (p) {
	int c = contains_tokens(p, 0, 4);
	if (c)p = expand_fully_aux(p, c, 0);
    }
    return p;
}


/*
    This routine expands all the token definitions in the definition of the
    token p.
*/

static void
expand_tokdef(construct *p)
{
    if (p->encoding != -1) {
	tok_info *info = get_tok_info(p);
	IGNORE set_token_args(info->pars,(node *)null, 0);
	info->def = expand_fully(info->def);
    }
    return;
}


/*
    This routine checks whether p is a local token all of whose uses have
    been expanded.  If so it eliminates p.
*/

static void
elim_tokdef(construct *p)
{
    if (p->encoding != -1 && p->ename == null) {
	tok_info *info = get_tok_info(p);
	if (info->depth == 0) {
	    remove_var_hash(p->name, SORT_token);
	}
    }
    return;
}


/*
    This routine expands all the token definitions in the definition of the
    alignment tag p.
*/

static void
expand_aldef(construct *p)
{
    if (p->encoding != -1) {
	al_tag_info *info = get_al_tag_info(p);
	info->def = expand_fully(info->def);
    }
    return;
}


/*
    This routine expands all the token definitions in the declaration and
    definition of the tag p.
*/

static void
expand_tagdef(construct *p)
{
    if (p->encoding != -1) {
	tag_info *info = get_tag_info(p);
	info->dec = expand_fully(info->dec);
	info->def = expand_fully(info->def);
    }
    return;
}


/*
    This routine expands all defined tokens.
*/

void
expand_all(void)
{
    apply_to_all(expand_tokdef, SORT_token);
    apply_to_all(expand_aldef, SORT_al_tag);
    apply_to_all(expand_tagdef, SORT_tag);
    apply_to_all(elim_tokdef, SORT_token);
    removals = null;
    return;
}
