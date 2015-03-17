/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

#include "obj_c/tdf.h"
#include "obj_c/cons_ops.h"
#include "obj_c/info_ops.h"
#include "obj_c/link_ops.h"
#include "obj_c/par_ops.h"
#include "obj_c/sort_ops.h"

#include "input.h"

/*
 * This table gives the mapping from sort names to sort codes.
 * Sorts not in this list, or with a sort code of zero, have sort codes
 * automatically generated for them.
 */
static struct {
	char *name;
	int code;
} sort_names[] = {
	/* Built-in sorts */
	{ "tdfint",           'i' },
	{ "tdfstring",        '$' },
	{ "tdfident",         '=' },
	{ "tdfbool",          'j' },
	{ "bitstream",        '@' },
	{ "bytestream",       '#' },

	/* Basic sorts */
	{ "access",           'u' },
	{ "alignment",        'a' },
	{ "al_tag",           'A' },
	{ "bitfield_variety", 'B' },
	{ "bool",             'b' },
	{ "callees",          'q' },
	{ "error_code",       'c' },
	{ "error_treatment",  'e' },
	{ "exp",              'x' },
	{ "floating_variety", 'f' },
	{ "label",            'l' },
	{ "nat",              'n' },
	{ "ntest",            'N' },
	{ "procprops",        'P' },
	{ "rounding_mode",    'r' },
	{ "shape",            'S' },
	{ "signed_nat",       's' },
	{ "string",           'X' },
	{ "tag",              't' },
	{ "token",            'T' },
	{ "transfer_mode",    'm' },
	{ "variety",          'v' },

	/* Unit sorts */
	{ "al_tagdef",        0   },
	{ "diag_tagdef",      0   },
	{ "external",         0   },
	{ "sortname",         '~' },
	{ "tagdec",           0   },
	{ "tagdef",           0   },
	{ "tokdec",           0   },
	{ "tokdef",           0   },

	/* Diagnostic and linkage sorts */
	{ "diag_descriptor",  'D' },
	{ "diag_tag",         'I' },
	{ "diag_tq",          'g' },
	{ "diag_type",        'd' },
	{ "filename",         'Q' },
	{ "linkinfo",         'L' },
	{ "sourcemark",       'M' },
	{ "version",          'V' },

	/* New diagnostic sorts */
	{ "dg",               'G' },
	{ "dg_accessibility", 'o' },
	{ "dg_append",        'H' },
	{ "dg_bound",         'w' },
	{ "dg_classmem",      'z' },
	{ "dg_class_base",    'y' },
	{ "dg_compilation",   'C' },
	{ "dg_dim",           'O' },
	{ "dg_discrim",       'K' },
	{ "dg_enum",          'E' },
	{ "dg_field",         'R' },
	{ "dg_filename",      'U' },
	{ "dg_idname",        'Y' },
	{ "dg_macro",         'Z' },
	{ "dg_name",          'h' },
	{ "dg_namelist",      'k' },
	{ "dg_param",         'p' },
	{ "dg_param_mode",    0   },
	{ "dg_qualifier",     0   },
	{ "dg_sourcepos",     'W' },
	{ "dg_tag",           'J' },
	{ "dg_type",          0   },
	{ "dg_variant",       0   },
	{ "dg_varpart",       0   },
	{ "dg_virtuality",    0   }
};

#define NO_BUILTIN_SORTS	6
#ifndef array_size
#define array_size(x) (sizeof (x) / sizeof *(x))
#endif
#define NO_SORTS		array_size(sort_names)

/*
 * A list of all sorts (in alphabetical order) is maintained.
 */
static LIST(SORT)all_sorts = NULL_list(SORT);

/*
 * This routine defines the sort s to be info.
 */
static void
define_sort(SORT s, SORT_INFO info, int code)
{
	static int next_code = 1;
	SORT_INFO old;

	old = DEREF_info(sort_info(s));
	if (!IS_NULL_info(old)) {
		string nm = DEREF_string(sort_name(s));
		error(ERR_SERIOUS, "Sort '%s' already defined", nm);
	}

	COPY_info(sort_info(s), info);

	if (code == 0) {
		code = next_code++;
	}

	COPY_int(sort_code(s), code);
}

/*
 * This routine looks up a sort named nm, creating it if it does not
 * already exist if create is true.
 */
SORT
find_sort(string nm, int create)
{
	SORT s;
	SORT_INFO info;
	LIST(SORT) p;
	LIST(SORT) q;
	string cnm;

	info = NULL_info;

	p = all_sorts;
	q = NULL_list(SORT);

	while (!IS_NULL_list(p)) {
		int cmp;
		string n;

		s = DEREF_sort(HEAD_list(p));
		n = DEREF_string(sort_name(s));

		cmp = strcmp(n, nm);
		if (cmp == 0) {
			return s;
		}
		if (cmp > 0) {
			break;
		}

		q = p;
		p = TAIL_list(p);
	}

	cnm = to_capitals(nm);
	MAKE_sort_basic(nm, cnm, NULL, NULL, 0, 0, 0, 0, info, s);
	if (!create) {
		error(ERR_SERIOUS, "Sort '%s' not defined", nm);
		MAKE_info_builtin(nm, info);
		define_sort(s, info, 0);
	}

	CONS_sort(s, p, p);
	if (IS_NULL_list(q)) {
		all_sorts = p;
	} else {
		COPY_list(PTR_TAIL_list(q), p);
	}

	return s;
}

/*
 * This routine marks the parameter sorts of the constructs c with the value m.
 */
void
mark_construct(CONSTRUCT c, int m)
{
	LIST(PARAMETER) p;

	if (IS_NULL_cons(c)) {
		return;
	}

	p = DEREF_list(cons_pars(c));

	while (!IS_NULL_list(p)) {
		PARAMETER a;
		SORT s;

		a = DEREF_par(HEAD_list(p));
		s = DEREF_sort(par_type(a));

		mark_sort(s, m);
		p = TAIL_list(p);
	}
}

/*
 * This routine marks the sort s and all its constructs with the value m.
 */
void
mark_sort(SORT s, int m)
{
	SORT_INFO info;
	int mark;

	mark = DEREF_int(sort_mark(s));
	if (mark == m) {
		return;
	}

	info = DEREF_info(sort_info(s));
	COPY_int(sort_mark(s), m);
	if (IS_NULL_info(info)) {
		return;
	}

	switch (TAG_info(info)) {
	case info_basic_tag: {
		LIST(CONSTRUCT) p;

		p = DEREF_list(info_basic_cons(info));
		while (!IS_NULL_list(p)) {
			CONSTRUCT c;

			c = DEREF_cons(HEAD_list(p));
			mark_construct(c, m);
			p = TAIL_list(p);
		}

		break;
	}

	case info_dummy_tag: {
		CONSTRUCT c;

		c = DEREF_cons(info_dummy_cons(info));
		mark_construct(c, m);
		break;
	}

	case info_clist_tag:
	case info_slist_tag:
	case info_option_tag: {
		SORT p;

		p = DEREF_sort(info_clist_etc_arg(info));
		mark_sort(p, m);
		break;
	}
	}
}

/*
 * This routine marks all sorts with the value m.
 */
void
mark_all_sorts(int m)
{
	LIST(SORT) p;

	for (p = all_sorts; !IS_NULL_list(p); p = TAIL_list(p)) {
		SORT s;

		s = DEREF_sort(HEAD_list(p));
		COPY_int(sort_mark(s), m);
	}
}

/*
 * This routine checks whether the string s ends in the string e.  If so
 * it returns a copy of s with this ending removed.  Otherwise it returns
 * the null string.
 */
string
ends_in(string s, string e)
{
	unsigned n = (unsigned) strlen(s);
	unsigned m = (unsigned) strlen(e);
	unsigned d;

	if (n < m) {
		return NULL;
	}

	d = n - m;
	if (streq(s + d, e)) {
		s = xstrdup(s);
		s[d] = 0;
		return s;
	}

	return NULL;
}

/*
 * This routine returns a copy of the string s with all the lower case
 * letters converted to upper case.
 */
string
to_capitals(string s)
{
	char c;
	string t;

	s = xstrdup(s);
	t = s;

	while (c = *t, c != 0) {
		if (c >= 'a' && c <= 'z') {
			*t = (char)('A' + (c - 'a'));
		}

		t++;
	}

	return s;
}

/*
 * This routine defines the basic sort s to have b bits (extended if e
 * is true) and constructs p.
 */
void
basic_sort(SORT s, unsigned b, unsigned e, LIST(CONSTRUCT)p)
{
	int code;
	SORT_INFO info;
	string n;
	size_t i;

	n = DEREF_string(sort_name(s));

	if (b == 0 && e == 0 && LENGTH_list(p) == 1) {
		/* Dummy sort */
		CONSTRUCT c;

		c = DEREF_cons(HEAD_list(p));
		MAKE_info_dummy(n, c, info);

		define_sort(s, info, 'F');

		return;
	}

	code = 0;

	for (i = NO_BUILTIN_SORTS; i < NO_SORTS; i++) {
		if (streq(n, sort_names[i].name)) {
			code = sort_names[i].code;
			break;
		}
	}

	MAKE_info_basic(n, b, e, 0, p, NULL_cons, info);

	define_sort(s, info, code);
}

/*
 * This routine creates a construct named nm with result sort s, parameter
 * sorts p and encoding e.
 */
CONSTRUCT
make_construct(string nm, unsigned e, SORT s, LIST(PARAMETER)p)
{
	CONSTRUCT c;
	unsigned kind;

	kind = KIND_simple;
	if (ends_in(nm, "_apply_token")) {
		kind = KIND_token;
	}

	if (ends_in(nm, "_cond")) {
		kind = KIND_cond;
	}

	MAKE_cons_basic(nm, e, s, p, kind, c);

	return c;
}

/*
 * This routine defines the compound sort s with standard suffix suff
 * and sort type tag.
 */
void
compound_sort(SORT s, string suff, unsigned tag, int code)
{
	SORT_INFO info;
	SORT t;
	string nm;
	string snm;

	nm  = DEREF_string(sort_name(s));
	snm = ends_in(nm, suff);
	if (!snm) {
		error(ERR_SERIOUS, "Sort '%s' doesn't end in '%s'", nm, suff);
	}

	t = find_sort(snm, 1);
	MAKE_info_clist_etc(tag, nm, t, info);
	define_sort(s, info, code);
}

/*
 * This routine searches for a construct named c in the sort s.
 */
CONSTRUCT
find_construct(SORT s, string c)
{
	SORT_INFO info;
	LIST(CONSTRUCT) p;

	info = DEREF_info(sort_info(s));
	if (IS_NULL_info(info) || !IS_info_basic(info)) {
		return NULL_cons;
	}

	for (p = DEREF_list(info_basic_cons(info)); !IS_NULL_list(p); p = TAIL_list(p)) {
		CONSTRUCT a;
		string b;

		a = DEREF_cons(HEAD_list(p));
		b = DEREF_string(cons_name(a));
		if (streq(b, c)) {
			return a;
		}
	}

	return NULL_cons;
}

/*
 * This routine sets the kind of the construct c of sort s to be kind.
 */
void
set_special(SORT s, string c, unsigned kind)
{
	CONSTRUCT a;

	a = find_construct(s, c);
	if (!IS_NULL_cons(a)) {
		COPY_unsigned(cons_kind(a), kind);
	} else {
		string nm = DEREF_string(sort_name(s));
		error(ERR_SERIOUS, "Can't find construct '%s' for sort '%s'", c, nm);
	}
}

/*
 * This routine searches for a construct of the sort s of the given kind.
 */
CONSTRUCT
get_special(SORT s, unsigned kind)
{
	SORT_INFO info;
	LIST(CONSTRUCT) p;

	info = DEREF_info(sort_info(s));
	if (IS_NULL_info(info) || !IS_info_basic(info)) {
		return NULL_cons;
	}

	for (p = DEREF_list(info_basic_cons(info)); !IS_NULL_list(p); p = TAIL_list(p)) {
		CONSTRUCT a;
		unsigned b;

		a = DEREF_cons(HEAD_list(p));
		b = DEREF_unsigned(cons_kind(a));
		if (b == kind) {
			return a;
		}
	}

	return NULL_cons;
}

/*
 * This routine defines the built-in sorts.
 */
void
builtin_sorts(void)
{
	size_t i;

	for (i = 0; i < NO_BUILTIN_SORTS; i++) {
		SORT_INFO info;
		SORT s;
		char *nm;

		nm = sort_names[i].name;
		s  = find_sort(nm, 1);

		MAKE_info_builtin(nm, info);
		define_sort(s, info, sort_names[i].code);
	}
}

/*
 * This routine checks the list of all sorts for undefined sorts,
 * returning the reordered list.
 */
LIST(SORT)
check_sorts(void)
{
	LIST(SORT) p;

	for (p = all_sorts; !IS_NULL_list(p); p = TAIL_list(p)) {
		SORT s;
		SORT_INFO info;
		LIST(CONSTRUCT) q;
		unsigned m;

		s = DEREF_sort(HEAD_list(p));
		info = DEREF_info(sort_info(s));

		if (IS_NULL_info(info)) {
			string nm = DEREF_string(sort_name(s));
			error(ERR_SERIOUS, "Sort '%s' not defined", nm);
			MAKE_info_builtin(nm, info);
			define_sort(s, info, 0);
		}

		if (!IS_info_basic(info)) {
			continue;
		}

		m = 0;

		for (q = DEREF_list(info_basic_cons(info)); !IS_NULL_list(q); q = TAIL_list(q)) {
			CONSTRUCT a;
			unsigned n;

			a = DEREF_cons(HEAD_list(q));
			n = DEREF_unsigned(cons_encode(a));
			if (n > m) {
				m = n;
			}
		}

		COPY_unsigned(info_basic_max(info), m);
	}

	return all_sorts;
}

/*
 * This routine finds all the foreign sorts.
*/

LIST(LINKAGE)
foreign_sorts(void)
{
	SORT_INFO info;
	SORT t;

	LIST(SORT) p;
	LIST(LINKAGE) q;
	LIST(PARAMETER) pars;

	unsigned e = 0;

	t = find_sort("sortname", 0);
	info = DEREF_info(sort_info(t));

	if (IS_info_basic(info)) {
		e = DEREF_unsigned(info_basic_max(info));
	}

	q    = NULL_list(LINKAGE);
	pars = NULL_list(PARAMETER);

	for (p = all_sorts; !IS_NULL_list(p); p = TAIL_list(p)) {
		string nm;
		CONSTRUCT c;
		SORT s;

		s    = DEREF_sort(HEAD_list(p));
		info = DEREF_info(sort_info(s));
		if (!IS_info_basic(info)) {
			continue;
		}

		nm = DEREF_string(sort_name(s));
		c  = get_special(s, KIND_token);

		if (!IS_NULL_cons(c)) {
			/* Sort can be tokenised */
			string snm = nm;
			if (streq(nm, "alignment")) {
				snm = "alignment_sort";
			}

			c = find_construct(t, snm);
			if (IS_NULL_cons(c)) {
				/* Doesn't have a sort name */
				LINKAGE a;

				if (streq(nm, "diag_type")) {
					snm = "diag_type";
				} else if (streq(nm, "filename")) {
					snm = "~diag_file";
				} else {
					snm = to_capitals(nm);
				}

				MAKE_cons_basic(snm, ++e, t, pars, KIND_foreign, c);
				MAKE_link_basic(snm, s, a);

				CONS_link(a, q, q);
			}
		} else {
			MAKE_cons_basic(nm, ++e, t, pars, KIND_dummy, c);
		}

		COPY_cons(info_basic_sortname(info), c);
	}

	q = REVERSE_list(q);

	return q;
}

/*
 * This routine returns the nth parameter of the construct c.
 */
PARAMETER
find_param(CONSTRUCT c, unsigned n)
{
	LIST(PARAMETER) p;

	for (p = DEREF_list(cons_pars(c)); n; p = TAIL_list(p)) {
		if (IS_NULL_list(p)) {
			string nm = DEREF_string(cons_name(c));
			error(ERR_SERIOUS, "Bad parameter number for '%s'", nm);
			return NULL_par;
		}

		n--;
	}

	return DEREF_par(HEAD_list(p));
}

