/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "de_types.h"
#include "de_capsule.h"
#include "de_unit.h"
#include "decode.h"
#include "fetch.h"
#include "names.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


int decode_status = -1;


bool extract_tokdecs = 0;


static long no_var;
static var_sort *vars;
long al_tag_var, tag_var, tok_var;


static construct *garbage = NULL;


binding *crt_binding;
static binding *spare_binding = NULL;


bool in_skip_pass = 0;


typedef void(*equation_func)(void);


char *capname = NULL;


static binding *
new_binding(void)
{
	binding *b;
	long i;
	long n = no_var;

	if (n == 0)
		return NULL;

	if (spare_binding) {
		b = spare_binding;
		spare_binding = NULL;

		for (i = 0; i < n; i++)
			b[i].max_no = 0;

		return b;
	}

	b = xmalloc_nof(binding, n);

	for (i = 0; i < n; i++) {
		b[i].max_no = 0;
		b[i].sz = 0;
		b[i].table = NULL;
	}

	return b;
}


static void
free_binding(binding *b)
{
	spare_binding = b;
}


static void
set_binding_size(binding *bt, long v, long n)
{
	binding *b;
	construct **p;
	long i;
	long m = n + 10;

	if (v < 0 || v >= no_var) {
		input_error("Illegal binding sort");
		return;
	}

	b = bt + v;
	b->max_no = n;
	if (b->sz < m) {
		p = xrealloc_nof(b->table, construct *, m);
		b->sz = m;
		b->table = p;
	} else
		p = b->table;

	for (i = 0; i < b->sz; i++)
		p[i] = NULL;
}


static void
complete_binding(binding *b)
{
	long v;

	for (v = 0; v < no_var; v++) {
		long i;
		binding *bv = b + v;
		sortname s = vars[v].sortnum;

		for (i = 0; i < bv->max_no; i++) {
			if (bv->table[i] == NULL) {
				construct *p = make_construct(s);

				if (extract_tokdecs) {
					/* This construct is unused - free it */
					(sort_count[s]) --;
					p->next = garbage;
					garbage = p;
				} else {
					/* Make up an internal name */
					long n = p->encoding;
					char *nm = xmalloc_nof(char, 32);

					IGNORE sprintf(nm, "~~%s_%ld", vars[v].name, n);
					p->name = nm;

					if (add_to_var_hash(p, s))
						input_error("%s has already been defined", nm);
				}

				bv->table[i] = p;
			}
		}
	}
}


static void
set_binding(binding *bt, long v, long n, construct *p)
{
	binding *b;

	if (v < 0 || v >= no_var) {
		input_error("Illegal binding sort");
		return;
	}

	b = bt + v;
	if (n >= b->max_no || n < 0) {
		input_error("Object number %ld (%s) too big", n, vars[v].name);
		return;
	}

	if (b->table[n]) {
		input_error("Object %ld (%s) already bound", n, vars[v].name);
		return;
	}

	b->table[n] = p;
}


construct *
find_binding(binding *bt, long v, long n)
{
	binding *b;

	if (v < 0 || v >= no_var) {
		input_error("Illegal binding sort");
		return NULL;
	}

	b = bt + v;
	if (n >= b->max_no || n < 0) {
		input_error("Object number %ld (%s) too big", n, vars[v].name);
		return NULL;
	}

	return b->table[n];
}


static char *
de_aligned_string(void)
{
	char *p;
	long i;
	long n = tdf_int();

	if (n != 8)
		input_error("Only 8-bit strings allowed");

	n = tdf_int();
	byte_align();
	p = xmalloc_nof(char, n + 1);

	for ( i = 0 ; i < n ; i++ )
		p [i] = (char) fetch(8);

	p[n] = 0;
	byte_align();

	return p;
}


static void
de_equation(equation_func f)
{
	long i, n;
	binding *old_binding = NULL;

	/* Read new bindings */
	n = tdf_int();

	if (n) {
		if (n != no_var)
			input_error("Number of local variables wrong");

		old_binding = crt_binding;
		crt_binding = new_binding();

		for (i = 0; i < n; i++) {
			long sz = tdf_int();
			set_binding_size(crt_binding, i, sz);
		}

		n = tdf_int();
		if (n != no_var)
			input_error("Number of linkage units wrong");

		for (i = 0; i < n; i++) {
			long j;
			long no_links = tdf_int();

			for (j = 0; j < no_links; j++) {
				long inner = tdf_int();
				long outer = tdf_int();
				construct *p = find_binding(old_binding, i, outer);

				set_binding(crt_binding, i, inner, p);
			}
		}

		complete_binding(crt_binding);
	} else {
		n = tdf_int();
		if (n)
			input_error("Number of linkage units wrong");
	}

	/* Read the actual equation */
	n = CHAR_BIT * tdf_int();
	byte_align();

	if (f == NULL)
		input_skip(n);
	else {
		long end_posn = tell_posn() + n;
		decode_status = 2;

		(*f)();
		byte_align();
		decode_status = 1;

		if (tell_posn() != end_posn)
			input_error("Unit length wrong");
	}

	/* Restore the old bindings */
	if (old_binding) {
		free_binding(crt_binding);
		crt_binding = old_binding;
	}
}


void
de_capsule(void)
{
	long i, n;
	long no_eqn;
	char **eqns;

	/* Reset variables */
	al_tag_var = -1;
	tag_var = -2;
	tok_var = -3;
	spare_binding = NULL;
	have_version = 0;
	decode_status = 0;

	/* Read magic number */
	de_magic(MAGIC_NUMBER);

	/* Read equation names */
	no_eqn = tdf_int();
	eqns = xmalloc_nof(char *, no_eqn);

	for (i = 0; i < no_eqn; i++)
		eqns[i] = de_aligned_string();

	/* Read variable sort names */
	no_var = tdf_int();
	vars = xmalloc_nof(var_sort, no_var);
	crt_binding = new_binding();

	for (i = 0; i < no_var; i++) {
		char *s = de_aligned_string();
		long sz = tdf_int();

		vars[i].name = s;

		if (strcmp(s, LINK_al_tag) == 0) {
			vars[i].sortnum = SORT_al_tag;
			al_tag_var = i;
		} else if (strcmp(s, LINK_tag) == 0) {
			vars[i].sortnum = SORT_tag;
			tag_var = i;
		} else if (strcmp(s, LINK_token) == 0) {
			vars[i].sortnum = SORT_token;
			tok_var = i;
		} else {
			vars[i].sortnum = SORT_unknown;
		}
		set_binding_size(crt_binding, i, sz);
	}

	/* Read external names */
	decode_status = 1;
	n = tdf_int();
	if (n != no_var)
		input_error("Number of variable sorts wrong");

	for (i = 0; i < no_var; i++) {
		static int un = 0;
		sortname si = vars[i].sortnum;
		long j;
		long no_links = tdf_int();
		bool reject = 0;

		if (extract_tokdecs && i != tok_var)
			reject = 1;

		for (j = 0; j < no_links; j++) {
			construct *p, *q;
			long id = tdf_int();

			n = de_external_bits();
			byte_align();
			p = make_construct(si);

			if (extract_tokdecs) {
				(sort_count[si]) --;
				p->encoding = -1;
			}

			if (n == ENC_string_extern) {
				/* Simple external name */
				bool name_ok = 1;
				node *ns = de_node("=");

				if (reject)
					free_node(ns);
				else {
					/* Check that name is a valid identifier */
					char *nm = ns->cons->name;

					if (alpha(*nm)) {
						long k;

						for (k = 1; k < ns->cons->encoding; k++) {
							char c = nm[k];

							if (!alphanum(c))
								name_ok = 0;
						}
					} else
						name_ok = 0;

					if (name_ok) {
						/* Use external name as internal name */
						p->name = nm;

						if (!is_local_name(nm)) {
							p->ename = new_node();
							p->ename->cons = &false_cons;
						}
					} else {
						/* Make up internal name */
						p->name = xmalloc_nof(char, 32);
						IGNORE sprintf(p->name, "~~extern_%d", un++);

						if (!is_local_name(nm)) {
							p->ename = new_node();
							p->ename->cons = &true_cons;
							p->ename->son = ns;
						}
					}
				}
			} else if (n == ENC_unique_extern) {
				/* Unique external name */
				node *nu = de_node("%[=]");

				if (reject)
					free_node(nu);
				else {
					/* Make up internal name */
					p->name = xmalloc_nof(char, 32);
					IGNORE sprintf(p->name, "~~extern_%d", un++);
					p->ename = new_node();
					p->ename->cons = &true_cons;
					p->ename->son = nu;
				}
			} else if (n == ENC_chain_extern) {
				/* Chain external name */
				node *nc = de_node("=i");

				if (reject)
					free_node(nc);
				else {
					/* Make up internal name */
					p->name = xmalloc_nof(char, 32);
					IGNORE sprintf(p->name, "~~extern_%d", un++);
					p->ename = new_node();
					p->ename->cons = &true_cons;
					p->ename->son = nc;
				}
			} else
				input_error("Illegal EXTERN value, %ld", n);

			/* Add construct to tables */
			if (reject) {
				set_binding(crt_binding, i, id, p);
				p->next = garbage;
				garbage = p;
			} else {
				q = add_to_var_hash(p, si);
				if (q) {
					if (!extract_tokdecs) {
						(sort_count[si]) --;

						if (q->encoding == -1)
							q->encoding = (sort_count[si]) ++;
					}

					set_binding(crt_binding, i, id, q);
					p->next = garbage;
					garbage = p;
				} else {
					set_binding(crt_binding, i, id, p);
				}
			}
		}
	}

	/* Complete the bindings */
	complete_binding(crt_binding);

	/* Read the equations */
	n = tdf_int();
	if (n != no_eqn)
		input_error("Number of equations wrong");

	for (i = 0; i < no_eqn; i++) {
		char *eq = eqns[i];
		long j;
		long no_units = tdf_int();

		if (no_units) {
			bool skip_pass = 0;
			equation_func f = NULL;

			/* Find equation decoding routine */
			if (extract_tokdecs) {
				if (strcmp(eq, LINK_tokdec_props) == 0)
					f = de_tokdec;
				else if (strcmp(eq, LINK_tokdef_props) == 0) {
					f = de_tokdef;
					in_skip_pass = 1;
				}
			} else {
				if (strcmp(eq, LINK_al_tagdef_props) == 0) {
					f = de_aldef;
				} else if (strcmp(eq, LINK_tagdec_props) == 0) {
					f = de_tagdec;
				} else if (strcmp(eq, LINK_tagdef_props) == 0) {
					f = de_tagdef;
				} else if (strcmp(eq, LINK_tokdec_props) == 0) {
					f = de_tokdec;
				} else if (strcmp(eq, LINK_tokdef_props) == 0) {
					f = de_tokdef;
					skip_pass = 1;
				} else if (strcmp(eq, LINK_version_props) == 0) {
					f = de_version;
				}
			}

			/* Skip pass */
			if (skip_pass) {
				long old_posn = tell_posn();

				in_skip_pass = 1;

				for (j = 0; j < no_units; j++)
					de_equation(f);

				in_skip_pass = 0;
				seek_posn(old_posn);
			}

			/* Main pass */
			for (j = 0; j < no_units; j++)
				de_equation(f);
			in_skip_pass = 0;
		}
	}

	/* Free unused constructs */
	free_construct(&garbage);
}


void
de_library(void)
{
	long old_posn;
	long i, no_cap;
	bool old_extract = extract_tokdecs;

	de_magic(MAGIC_LINK_NUMBER);
	IGNORE tdf_int();
	no_cap = tdf_int();
	old_posn = tell_posn();

	/* First pass - extract all token declaration */
	extract_tokdecs = 1;
	for (i = 0; i < no_cap; i++) {
		long end_posn;
		long j, n;

		decode_status = 0;
		n = tdf_int();
		if (n != 8)
			input_error("Only 8-bit strings allowed");

		n = tdf_int();
		byte_align();
		capname = xmalloc_nof(char, n + 1);

		for (j = 0; j < n; j++) {
			capname[j] = (char) fetch(8);
		}

		capname[n] = '\0';

		n = CHAR_BIT * tdf_int();
		byte_align();
		end_posn = tell_posn() + n;
		de_capsule();
		byte_align();

		if (tell_posn() != end_posn) {
			input_error("Capsule length wrong");
		}

		capname = NULL;
	}

	/* Second pass - if the first pass didn't do everything */
	extract_tokdecs = old_extract;
	if (extract_tokdecs)
		return;

	seek_posn(old_posn);

	for (i = 0; i < no_cap; i++) {
		long end_posn;
		long j, n;

		decode_status = 0;
		n = tdf_int();
		if (n != 8)
			input_error("Only 8-bit strings allowed");

		n = tdf_int();
		byte_align();
		capname = xmalloc_nof(char, n + 1);

		for (j = 0; j < n; j++) {
			capname[j] = (char) fetch(8);
		}

		capname[n] = '\0';
		n = CHAR_BIT * tdf_int();
		byte_align();
		end_posn = tell_posn() + n;
		de_capsule();
		byte_align();

		if (tell_posn() != end_posn) {
			input_error("Capsule length wrong");
		}

		capname = NULL;
	}
}
