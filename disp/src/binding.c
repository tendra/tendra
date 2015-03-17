/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "binding.h"
#include "capsule.h"
#include "tdf.h"
#include "tree.h"
#include "utility.h"


/*
 * CREATE A NEW OBJECT
 *
 * This routine allocates a new object of type v.
 */
object *
new_object(long v)
{
    static object *free_objs = NULL;
    static int objs_left = 0;

    object *p;
    if (objs_left == 0) {
	objs_left = 200;
	free_objs = xmalloc_nof(object, objs_left);
    }
    objs_left--;
    p = free_objs + objs_left;
    p->named = 0;
    p->id = (var_count[v]) ++;
    p->order = -1;
    p->aux = NULL;
    if (v == var_tag) {
	var(p) = 3;
    } else if (v == var_token) {
	is_foreign(p) = 0;
	res_sort(p) = sort_unknown;
	implicit_sort(p) = sort_unknown;
	arg_sorts(p) = NULL;
    }
    return p;
}


/*
 * SPARE BINDING TABLE
 *
 * In fact only two binding tables are ever needed.  The one not in use
 * is stored in spare_bt.
 */
static binding *spare_bt = NULL;


/*
 * CREATE A NEW BINDING TABLE
 *
 * This routine allocates a new binding table and initializes its entries.
 */
binding *
new_binding_table(void)
{
    binding *bt;
    long i, n = no_variables;
    if (n == 0) return NULL;
    if (spare_bt) {
	bt = spare_bt;
	spare_bt = NULL;
	for (i = 0; i < n; i++) {
	    bt[i].max_no = 0;
	}
    } else {
	bt = xmalloc_nof(binding, n);
	for (i = 0; i < n; i++) {
	    bt[i].max_no = 0;
	    bt[i].sz = 0;
	    bt[i].table = NULL;
	}
    }
    return bt;
}


/*
 * FREE A BINDING
 *
 * The binding bt is returned to free.
 */
void
free_binding_table(binding *bt)
{
    spare_bt = bt;
    return;
}


/*
 * SET THE SIZE OF A BINDING
 *
 * The vth entry of bt is set to size n.
 */
void
set_binding_size(binding *bt, long v, long n)
{
    object **p;
    binding *b;
    long i, m = n + 10;
    if (v < 0 || v >= no_variables) {
	input_error("Illegal binding sort");
	return;
    }
    b = bt + v;
    b->max_no = n;
    if (b->sz < m) {
	p = xrealloc_nof(b->table, object *, m);
	b->sz = m;
	b->table = p;
    } else {
	p = b->table;
    }
    for (i = 0; i < b->sz; i++)p[i] = NULL;
    return;
}


/*
 * SET AN ENTRY IN A BINDING
 *
 * The nth entry of the vth entry of the binding bt is set to p.
 */
void
set_binding(binding *bt, long v, long n, object *p)
{
    binding *b;
    if (v < 0 || v >= no_variables) {
	input_error("Illegal binding sort");
	return;
    }
    b = bt + v;
    if (n >= b->max_no || n < 0) {
	out("<error>");
	input_error("Object number %ld (%s) too big", n, var_types[v]);
	while (n >= b->sz) {
	    /* Table is extended (errors only) */
	    long i, m = b->sz + 100;
	    b->sz = m;
	    b->table = xrealloc_nof(b->table, object *, m);
	    for (i = 1; i <= 100; i++)b->table[m - i] = NULL;
	}
    }
    if (b->table[n]) {
	input_error("Object %s (%s) already bound", object_name(v, n),
		      var_types[v]);
    }
    b->table[n] = p;
    return;
}


/*
 * FILL IN BLANK ENTRIES IN A BINDING
 *
 * Objects are allocated for all the entries in the binding bt which
 * are not associated with an existing object.
 */
void
complete_binding(binding *bt)
{
    long v;
    for (v = 0; v < no_variables; v++) {
	long i;
	binding *b = bt + v;
	for (i = 0; i < b->max_no; i++) {
	    if (b->table[i] == NULL) {
		b->table[i] = new_object(v);
	    }
	}
    }
    return;
}


/*
 * FIND AN ENTRY IN A BINDING
 *
 * The nth entry of the vth entry of binding bt is returned.
 */
object *
find_binding(binding *bt, long v, long n)
{
    binding *b;
    if (v < 0 || v >= no_variables) {
	input_error("Illegal binding sort");
	return NULL;
    }
    b = bt + v;
    if (n >= b->max_no || n < 0) {
	out("<error>");
	input_error("Object number %ld (%s) too big", n, var_types[v]);
    }
    if (n >= b->sz) return NULL;
    return b->table[n];
}


/*
 * OUTPUT AN OBJECT
 *
 * The object p of type v and number n is output.
 */
void
out_object(long n, object *p, long v)
{
    if (v < 0 || v >= no_variables) {
	out("<error>");
	input_error("Illegal binding sort");
	return;
    }
    if (dumb_mode) {
	word *w;
	out_string(var_types[v]);
	w = new_word(HORIZ_BRACKETS);
	out_int(n);
	end_word(w);
	return;
    }
    if (p == NULL) {
	p = find_binding(crt_binding, v, n);
	if (p == NULL) {
	    p = new_object(v);
	    set_binding(crt_binding, v, n, p);
	}
    }
    if (p->named) {
	if (p->name.simple) {
	    out(p->name.val.str);
	} else {
	    out_unique(p->name.val.uniq);
	}
	return;
    }
    out_char('~');
    out_string(var_types[v]);
    out_char('_');
    out_int(p->id);
    return;
}


/*
 * RETURN AN OBJECT NAME (FOR ERROR REPORTING)
 *
 * The name of object type v and number n is returned.
 */
char *
object_name(long v, long n)
{
    object *p;
    char *buff = xmalloc_nof(char, 1000);
    if (dumb_mode) {
	IGNORE sprintf(buff, "%ld", n);
	return buff;
    }
    p = find_binding(crt_binding, v, n);
    if (p->named) {
	if (p->name.simple) {
	    IGNORE sprintf(buff, "%s", p->name.val.str);
	} else {
	    IGNORE sprintf(buff, "unique(%ld)", p->id);
	}
    } else {
	IGNORE sprintf(buff, "%ld", p->id);
    }
    return buff;
}
