/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>
#include <string.h>
#include <stddef.h>

#include <shared/bool.h>
#include <shared/xalloc.h>

#include <tdf/magic.h>

#include "config.h"
#include "types.h"
#include "eval.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


node *
make_nat(long n)
{
    node *p = new_node();
    p->cons = cons_no(SORT_nat, ENC_make_nat);
    p->son = new_node();
    p->son->cons = make_construct(SORT_small_tdfint);
    p->son->cons->encoding = n;
    return p;
}


node *
make_int(long n)
{
    node *p = new_node();
    if (n < 0) {
	p->cons = &true_cons;
	n = -n;
    } else {
	p->cons = &false_cons;
    }
    p->bro = new_node();
    p->bro->cons = make_construct(SORT_small_tdfint);
    p->bro->cons->encoding = n;
    return p;
}


static node *
make_signed_nat(long n)
{
    node *p = new_node();
    p->cons = cons_no(SORT_signed_nat, ENC_make_signed_nat);
    p->son = make_int(n);
    return p;
}


static node *
make_int_exp(node *sh, long n, char *val)
{
    node *p = new_node();
    p->cons = cons_no(SORT_exp, ENC_make_int);
    p->son = copy_node(sh->son);
    p->son->bro = make_signed_nat(n);
    if (val) {
	/* Assign large values */
	node *r = p->son->bro->son->bro;
	r->cons = make_construct(SORT_tdfint);
	r->cons->name = val;
    }
    p->shape = sh;
    return p;
}


static bool
is_constant(node *p, long *pn)
{
    if (p) {
	sortname s = p->cons->sortnum;
	long n = p->cons->encoding;
	if (s == SORT_exp && n == ENC_make_int) {
	    p = p->son->bro;
	    s = p->cons->sortnum;
	    n = p->cons->encoding;
	}
	if (s == SORT_signed_nat && n == ENC_make_signed_nat) {
	    /* Allow signed integer literals */
	    long negate = p->son->cons->encoding;
	    p = p->son->bro;
	    s = p->cons->sortnum;
	    n = p->cons->encoding;
	    if (negate)n = -n;
	} else if (s == SORT_nat && n == ENC_make_nat) {
	    /* Allow integer literals */
	    p = p->son;
	    s = p->cons->sortnum;
	    n = p->cons->encoding;
	} else if (s == SORT_bool) {
	    /* Allow bool literals */
	    if (n == ENC_false) {
		*pn = 0;
		return 1;
	    }
	    if (n == ENC_true) {
		*pn = 1;
		return 1;
	    }
	}
	if (s == SORT_small_tdfint) {
	    /* Small constant found */
	    *pn = n;
	    return 1;
	}
    }
    return 0;
}


static long var_max = 32;
static unsigned long *var_mask;


static bool
is_var_width(node *sh, long *pn, long *pm)
{
    if (sh && sh->cons->encoding == ENC_integer) {
	if (sh->son->cons->encoding == ENC_var_width) {
	    node *q = sh->son->son;
	    if (is_constant(q, pn)) {
		if (is_constant(q->bro, pm)) {
		    return 1;
		}
	    }
	}
    }
    return 0;
}


static char *
shift_one(long n)
{
    long i;
    char buff[100];
    switch (n % 3) {
	case 0: buff[0] = '1'; break;
	case 1: buff[0] = '2'; break;
	case 2: buff[0] = '4'; break;
    }
    for (i = 0; i < n / 3; i++) {
	buff[i + 1] = '0';
    }
    return string_copy(buff,(int)(i + 1));
}


static char *
minus_one(char *val)
{
    int i, n = (int)strlen(val);
    char *res = string_copy(val, n);
    for (i = n - 1; i >= 0; i--) {
	char c = res[i];
	if (c != '0') {
	    res[i] = c - 1;
	    break;
	}
	res[i] = '7';
    }
    if (res[0] == '0')res++;
    return res;
}


static node *
eval_exp(long op, long err, node *sh, long a, long b)
{
    long c = 0;
    long sz = 0;
    long sgn = 0;
    char *val = NULL;

    /* Check result shape */
    if (!is_var_width(sh, &sgn, &sz)) return NULL;
    if (!sgn && (a < 0 || b < 0)) return NULL;
    if (sz < 1) return NULL;
    if (sz > var_max) {
	if (sz < 256) {
	    /* Evaluate some special cases */
	    if (op == ENC_shift_left && a == 1) {
		if (!sgn && b < sz)val = shift_one(b);
	    } else if (op == ENC_negate && a == 1) {
		if (!sgn && err == ENC_wrap) {
		    val = shift_one(sz);
		    val = minus_one(val);
		}
	    } else if (op == ENC_minus && a == 0 && b == 1) {
		if (!sgn && err == ENC_wrap) {
		    val = shift_one(sz);
		    val = minus_one(val);
		}
	    }
	    if (val) return make_int_exp(sh, c, val);
	}
	return NULL;
    }

    /* Evaluate result */
    switch (op) {
	case ENC_abs: {
	    c = a;
	    if (c < 0)c = -a;
	    break;
	}
	case ENC_and: {
	    if (a < 0 || b < 0) return NULL;
	    c = (a & b);
	    break;
	}
	case ENC_change_variety: {
	    c = a;
	    break;
	}
	case ENC_div0:
	case ENC_div1:
	case ENC_div2: {
	    if (a < 0 || b <= 0) return NULL;
	    c = a / b;
	    break;
	}
	case ENC_maximum: {
	    c = (a >= b ? a : b);
	    break;
	}
	case ENC_minimum: {
	    c = (a < b ? a : b);
	    break;
	}
	case ENC_minus: {
	    c = a - b;
	    break;
	}
	case ENC_mult: {
	    c = a * b;
	    break;
	}
	case ENC_negate: {
	    c = -a;
	    break;
	}
	case ENC_not: {
	    if (sgn || err != ENC_wrap) return NULL;
	    c = ~a;
	    break;
	}
	case ENC_or: {
	    if (a < 0 || b < 0) return NULL;
	    c = (a | b);
	    break;
	}
	case ENC_plus: {
	    c = a + b;
	    break;
	}
	case ENC_rem0:
	case ENC_rem1:
	case ENC_rem2: {
	    if (a < 0 || b <= 0) return NULL;
	    c = a % b;
	    break;
	}
	case ENC_shift_left: {
	    if (sgn || err != ENC_wrap) return NULL;
	    if (b < var_max) {
		unsigned long ua = (unsigned long)a;
		unsigned long ub = (unsigned long)b;
		c = (long)(ua << ub);
	    } else {
		c = 0;
	    }
	    break;
	}
	case ENC_shift_right: {
	    if (sgn || err != ENC_wrap) return NULL;
	    if (b < var_max) {
		unsigned long ua = (unsigned long)a;
		unsigned long ub = (unsigned long)b;
		c = (long)(ua >> ub);
	    } else {
		c = 0;
	    }
	    break;
	}
	case ENC_xor: {
	    if (a < 0 || b < 0) return NULL;
	    c = (a ^ b);
	    break;
	}
	case ENC_power:
	case ENC_rotate_left:
	case ENC_rotate_right:
	default : {
	    /* NOT YET IMPLEMENTED */
	    return NULL;
	}
    }

    /* Check for overflow */
    if (sgn) {
	long v = (long)var_mask[sz - 1];
	if (c < - (v + 1) || c > v) return NULL;
    } else {
	unsigned long uc;
	unsigned long uv = var_mask[sz];
	if (c < 0) {
	    if (err != ENC_wrap) return NULL;
	    uc = (unsigned long) -c;
	    uc = ((uv - uc + 1) & uv);
	    if (uc > var_mask[var_max - 1]) {
		val = ulong_to_octal(uc);
		uc = 0;
	    }
	} else {
	    uc = (unsigned long)c;
	    if (uc > uv) {
		if (err != ENC_wrap) return NULL;
		uc &= uv;
	    }
	}
	c = (long)uc;
    }

    /* Create the result */
    return make_int_exp(sh, c, val);
}


static int
eval_test(long tst, long a, long b)
{
    int res = 0;
    switch (tst) {
	case ENC_equal:
	case ENC_not_less_than_and_not_great: {
	    if (a == b)res = 1;
	    break;
	}
	case ENC_not_equal:
	case ENC_less_than_or_greater_than: {
	    if (a != b)res = 1;
	    break;
	}
	case ENC_greater_than:
	case ENC_not_less_than_or_equal: {
	    if (a > b)res = 1;
	    break;
	}
	case ENC_greater_than_or_equal:
	case ENC_not_less_than: {
	    if (a >= b)res = 1;
	    break;
	}
	case ENC_less_than:
	case ENC_not_greater_than_or_equal: {
	    if (a < b)res = 1;
	    break;
	}
	case ENC_less_than_or_equal:
	case ENC_not_greater_than: {
	    if (a <= b)res = 1;
	    break;
	}
	default : {
	    res = -1;
	    break;
	}
    }
    return res;
}


static node *
eval_decr(node *p)
{
    if (p->cons->encoding == ENC_make_int) {
	node *sh = p->shape;
	if (sh == NULL)sh = sh_integer(p->son);
	p = p->son->bro;
	if (p->cons->encoding == ENC_make_signed_nat) {
	    if (!p->son->cons->encoding) {
		p = p->son->bro;
		if (p->cons->sortnum == SORT_tdfint) {
		    long c = 0;
		    char *val = minus_one(p->cons->name);
		    if (fits_ulong(val, 1)) {
			c = (long)octal_to_ulong(val);
			val = NULL;
		    }
		    return make_int_exp(sh, c, val);
		}
	    }
	}
    }
    return NULL;
}


static node *
eval_node(node *p)
{
    sortname s = p->cons->sortnum;
    long n = p->cons->encoding;
    if (s > 0 && n == sort_conds[s]) {
	/* Conditional constructs */
	long m = 0;
	if (is_constant(p->son, &m)) {
	    p = p->son->bro;
	    if (m == 0)p = p->bro;
	    return p->son;
	}
    }
    if (s == SORT_exp) {
	long m1 = 0, m2 = 0;
	switch (n) {
	    case ENC_make_int: {
		/* Make sure that constants have a shape */
		if (p->shape == NULL)p->shape = sh_integer(p->son);
		break;
	    }
	    case ENC_change_variety: {
		/* Allow for change_variety */
		node *r = p->son->bro;
		if (p->shape == NULL)p->shape = sh_integer(r);
		if (is_constant(r->bro, &m1)) {
		    long err = p->son->cons->encoding;
		    node *q = eval_exp(n, err, p->shape, m1, m2);
		    if (q)p = q;
		}
		break;
	    }
	    case ENC_integer_test: {
		/* Allow for integer_test */
		node *r = p->son->bro->bro->bro;
		if (is_constant(r, &m1)) {
		    if (is_constant(r->bro, &m2)) {
			long tst = p->son->bro->cons->encoding;
			int res = eval_test(tst, m1, m2);
			if (res == 0) {
			    node *q = new_node();
			    q->cons = cons_no(SORT_exp, ENC_goto);
			    q->son = copy_node(p->son->bro->bro);
			    return q;
			}
			if (res == 1) {
			    node *q = new_node();
			    q->cons = cons_no(SORT_exp, ENC_make_top);
			    return q;
			}
		    }
		}
		break;
	    }
	    case ENC_conditional: {
		/* Allow for conditional */
		node *r = p->son->bro;
		if (is_constant(r->bro, &m2)) {
		    if (is_constant(r, &m1)) {
			/* First branch terminates */
			return copy_node(r);
		    }
		    if (r->cons->encoding == ENC_goto) {
			if (eq_node(p->son, r->son)) {
			    /* First branch is a jump */
			    return copy_node(r->bro);
			}
		    }
		}
		break;
	    }
	    case ENC_sequence: {
		/* Allow for sequence */
		bool reached = 1;
		node *q = NULL;
		node *r = p->son->son;
		while (r != NULL) {
		    if (is_constant(r, &m1)) {
			if (reached)q = r;
		    } else if (r->cons->encoding == ENC_goto) {
			if (reached)q = r;
			reached = 0;
		    } else if (r->cons->encoding == ENC_make_top) {
			if (reached)q = r;
		    } else {
			return p;
		    }
		    r = r->bro;
		}
		r = p->son->bro;
		if (is_constant(r, &m1)) {
		    if (reached)q = r;
		} else if (r->cons->encoding == ENC_goto) {
		    if (reached)q = r;
		} else if (r->cons->encoding == ENC_make_top) {
		    if (reached)q = r;
		} else {
		    return p;
		}
		q = copy_node(q);
		return q;
	    }
	    case ENC_not: {
		/* Unary operations */
		node *r = p->son;
		if (is_constant(r, &m1)) {
		    long err = ENC_wrap;
		    node *q = eval_exp(n, err, r->shape, m1, m2);
		    if (q)p = q;
		}
		break;
	    }
	    case ENC_abs:
	    case ENC_negate: {
		/* Unary operations with error treatment */
		node *r = p->son->bro;
		if (is_constant(r, &m1)) {
		    long err = p->son->cons->encoding;
		    node *q = eval_exp(n, err, r->shape, m1, m2);
		    if (q)p = q;
		}
		break;
	    }
	    case ENC_and:
	    case ENC_maximum:
	    case ENC_minimum:
	    case ENC_or:
	    case ENC_rotate_left:
	    case ENC_rotate_right:
	    case ENC_shift_right:
	    case ENC_xor: {
		/* Binary operations */
		node *r = p->son;
		if (is_constant(r, &m1)) {
		    if (is_constant(r->bro, &m2)) {
			long err = ENC_wrap;
			node *q = eval_exp(n, err, r->shape, m1, m2);
			if (q)p = q;
		    }
		}
		break;
	    }
	    case ENC_minus:
	    case ENC_mult:
	    case ENC_plus:
	    case ENC_power:
	    case ENC_shift_left: {
		/* Binary operations with error treatment */
		node *r = p->son->bro;
		if (is_constant(r->bro, &m2)) {
		    if (is_constant(r, &m1)) {
			long err = p->son->cons->encoding;
			node *q = eval_exp(n, err, r->shape, m1, m2);
			if (q)p = q;
		    } else if (n == ENC_minus && m2 == 1) {
			node *q = eval_decr(r);
			if (q)p = q;
		    }
		}
		break;
	    }
	    case ENC_div0:
	    case ENC_div1:
	    case ENC_div2:
	    case ENC_rem0:
	    case ENC_rem1:
	    case ENC_rem2: {
		/* Binary operations with two error treatments */
		node *r = p->son->bro->bro;
		if (is_constant(r, &m1)) {
		    if (is_constant(r->bro, &m2)) {
			long err = p->son->bro->cons->encoding;
			node *q = eval_exp(n, err, r->shape, m1, m2);
			if (q)p = q;
		    }
		}
		break;
	    }
	}
    } else if (s == SORT_nat) {
	if (n == ENC_computed_nat) {
	    long m = 0;
	    if (is_constant(p->son, &m)) {
		if (m >= 0) return make_nat(m);
	    }
	}
    } else if (s == SORT_signed_nat) {
	if (n == ENC_computed_signed_nat) {
	    long m = 0;
	    if (is_constant(p->son, &m)) {
		return make_signed_nat(m);
	    }
	    if (p->son->cons->encoding == ENC_make_int) {
		return copy_node(p->son->son->bro);
	    }
	} else if (n == ENC_snat_from_nat) {
	    long m1 = 0, m2 = 0;
	    if (is_constant(p->son, &m1)) {
		if (is_constant(p->son->bro, &m2)) {
		    if (m1)m2 = -m2;
		    return make_signed_nat(m2);
		}
	    }
	}
    }
    return p;
}


static node *
eval_fully(node *p)
{
    if (p) {
	node *q = p->bro;
	p->son = eval_fully(p->son);
	p = eval_node(p);
	p->bro = eval_fully(q);
    }
    return p;
}


static void
eval_tokdef(construct *p)
{
    if (p->encoding != -1) {
	tok_info *info = get_tok_info(p);
	info->def = eval_fully(info->def);
    }
    return;
}


static void
eval_aldef(construct *p)
{
    if (p->encoding != -1) {
	al_tag_info *info = get_al_tag_info(p);
	info->def = eval_fully(info->def);
    }
    return;
}


static void
eval_tagdef(construct *p)
{
    if (p->encoding != -1) {
	tag_info *info = get_tag_info(p);
	info->dec = eval_fully(info->dec);
	info->def = eval_fully(info->def);
    }
    return;
}


void
eval_all(void)
{
    long i;
    unsigned long m = 0;
    var_max = CHAR_BIT * sizeof(long);
    var_mask = xmalloc_nof(unsigned long, var_max + 1);
    var_mask[0] = 0;
    for (i = 1; i <= var_max; i++) {
	m = 2 * m + 1;
	var_mask[i] = m;
    }
    init_shapes();
    apply_to_all(eval_tokdef, SORT_token);
    apply_to_all(eval_aldef, SORT_al_tag);
    apply_to_all(eval_tagdef, SORT_tag);
    return;
}
