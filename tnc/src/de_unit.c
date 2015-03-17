/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"

#include "types.h"
#include "check.h"
#include "de_types.h"
#include "de_capsule.h"
#include "de_unit.h"
#include "decode.h"
#include "fetch.h"
#include "high.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


static long max_lab_no = 0;
static construct *labels;


int have_version = 0;


static void
set_up_labels(long n)
{
	long i;
	static long lno = 0;
	max_lab_no = n;

	if (n == 0) {
		labels = NULL;
		return;
	}

	labels = xmalloc_nof(construct, n);

	for (i = 0; i < n; i++) {
		char *nm = xmalloc_nof(char, 32);

		IGNORE sprintf(nm, "~~label_%ld", lno);
		labels[i].sortnum = SORT_label;
		labels[i].encoding = lno++;
		labels[i].name = nm;
		labels[i].alias = NULL;
		labels[i].next = NULL;

		if (add_to_var_hash(labels + i, SORT_label))
			input_error("Label %s already defined", nm);
	}
}


construct *
find_label(long n)
{
	if (n < 0 || n >= max_lab_no) {
		input_error("Label number %ld too big", n);
		return NULL;
	}

	return labels + n;
}


static sortname
de_sortname(bool expand)
{
	long n = de_sortname_bits();

	if (n == SORT_token && expand) {
		long i, m;
		high_sort h, *hp;
		static int made_up_sorts = 0;

		h.res = de_sortname(1);
		de_list_start();
		m = tdf_int();
		h.no_args = (int)m;
		h.args = xmalloc_nof(sortname, m);
		h.name = xmalloc_nof(char, 32);
		IGNORE sprintf(h.name, "~~sort_%d", made_up_sorts++);

		for (i = 0; i < m; i++)
			h.args[i] = de_sortname(1);

		hp = new_high_sort(&h);
		hp = unique_high_sort(hp);

		return hp->id;
	}

	if (n == SORT_foreign) {
		warning("Foreign sorts not supported");
		IGNORE de_node("X");

		return SORT_unknown;
	}

	return (sortname)n;
}


void
de_aldef(void)
{
	long i, n = tdf_int();

	set_up_labels(n);
	n = tdf_int();

	for (i = 0; i < n; i++) {
		long t;
		node *d;
		construct *p;
		al_tag_info *info;

		/* Find the definition type */
		IGNORE de_al_tagdef_bits();

		/* Find the alignment tag */
		t = tdf_int();
		p = find_binding(crt_binding, al_tag_var, t);
		info = get_al_tag_info(p);

		/* Decode the definition (an alignment) */
		d = completion(de_alignment());
		if (info->def) {
			if (!eq_node(info->def, d)) {
				is_fatal = 0;
				input_error(
				    "Alignment tag %s defined inconsistently",
				    p->name);
			}
			free_node(d);
		} else {
			info->def = d;
		}
	}
}


void
de_tagdec(void)
{
	long i, n = tdf_int();

	set_up_labels(n);
	n = tdf_int();

	for (i = 0; i < n; i++) {
		long t;
		node *d;
		bool is_var;
		construct *p;
		tag_info *info;

		/* Find the declaration type */
		long m = de_tagdec_bits();

		switch (m) {
		case ENC_make_id_tagdec:
			is_var = 0;
			break;
		case ENC_make_var_tagdec:
			is_var = 1;
			break;
		default:
			is_var = 2;
			break;
		}

		/* Find the tag */
		t = tdf_int();
		p = find_binding(crt_binding, tag_var, t);
		set_tag_type(p, is_var);
		info = get_tag_info(p);

		/* Declaration = optional access + optional string + shape from 4.0 */
		d = completion(de_node("?[u]?[X]S"));
		info->var = is_var;
		if (info->dec) {
			if (!eq_node(info->dec, d)) {
				is_fatal = 0;
				input_error("Tag %s declared inconsistently", p->name);
			}
			free_node(d);
		} else {
			info->dec = d;
		}
	}
}


void
de_tagdef(void)
{
	long i, n = tdf_int();

	set_up_labels(n);
	n = tdf_int();

	for (i = 0; i < n; i++) {
		long t;
		node *d;
		construct *p;
		tag_info *info;
		bool is_var;

		/* Find the definition type */
		long m = de_tagdef_bits();

		switch (m) {
		case ENC_make_id_tagdef:
			is_var = 0;
			break;
		case ENC_make_var_tagdef:
			is_var = 1;
			break;
		default:
			is_var = 2;
			break;
		}

		/* Find the tag */
		t = tdf_int();
		p = find_binding(crt_binding, tag_var, t);

		info = get_tag_info(p);
		if (info->dec == NULL)
			input_error("Tag %s defined but not declared", p->name);

		set_tag_type(p, is_var);

		/* Added signature in 4.0 */
		d = completion(de_node(is_var ? "?[u]?[X]x" : "?[X]x"));
		info->var = is_var;
		if (info->def) {
			if (is_var == 2) {
				node *dp = info->def;

				while (dp->bro)
					dp = dp->bro;

				dp->bro = d;
			} else {
				if (!eq_node(info->def, d)) {
					is_fatal = 0;
					input_error("Tag %s defined inconsistently",
					    p->name);
				}

				free_node(d);
			}
		} else {
			info->def = d;

			if (do_check)
				check_tagdef(p);
		}
	}
}


void
de_tokdec(void)
{
	long i, n = tdf_int();

	for (i = 0; i < n; i++) {
		long t;
		node *sig;
		char *args;
		sortname rs;
		construct *p;
		tok_info *info;

		/* Find the declaration type */
		IGNORE de_tokdec_bits();

		/* Find the token */
		t = tdf_int();
		p = find_binding(crt_binding, tok_var, t);
		info = get_tok_info(p);

		/* Deal with signature */
		sig = de_node("?[X]");

		/* Decode token sort */
		rs = de_sortname(0);

		if (rs == SORT_token) {
			long m;

			rs = de_sortname(1);
			de_list_start();
			m = tdf_int();

			if (m == 0)
				args = NULL;
			else {
				long j;
				char abuff[100], *a = abuff;

				for (j = 0; j < m; j++) {
					sortname ps = de_sortname(1);

					if (is_high(ps)) {
						sprint_high_sort(a, ps);
						while (*a)
							a++;
					} else
						*(a++) = sort_letters[ps];
				}

				*a = 0;
				args = string_copy_aux(abuff);
			}
		} else
			args = NULL;

		if (is_high(rs))
			input_error("Token %s has high-level result sort", p->name);

		set_token_sort(p, rs, args, sig);
		info->dec = 1;
	}
}


void
de_token_defn(construct *p, node *sig)
{
	long m;
	node *d;
	char *args;
	sortname rs;
	tok_info *info = get_tok_info(p);
	construct **old_pars = info->pars;

	/* Find the end of the definition */
	long end_posn = tdf_int();
	end_posn += tell_posn();

	/* Find the definition type */
	IGNORE de_token_defn_bits();

	/* Decode the token sort */
	rs = de_sortname(1);
	de_list_start();
	m = tdf_int();

	if (m == 0) {
		args = NULL;
	} else {
		long j;
		char abuff[100], *a = abuff;

		if (!in_skip_pass)
			info->pars = xmalloc_nof(construct *, m + 1);

		for (j = 0; j < m; j++) {
			/* Decode the token arguments */
			sortname ps = de_sortname(1);
			long pn = tdf_int();
			construct *q = find_binding(crt_binding, tok_var, pn);

			set_token_sort(q, ps, NULL, NULL);

			if (is_high(ps)) {
				sprint_high_sort(a, ps);

				while (*a)
					a++;
			} else
				*(a++) = sort_letters[ps];

			if (!in_skip_pass)
				info->pars[j] = q;
		}

		*a = 0;
		args = string_copy_aux(abuff);

		if (!in_skip_pass)
			info->pars[j] = NULL;
	}

	if (is_high(rs))
		input_error("Token %s has high-level result sort", p->name);

	set_token_sort(p, rs, args, sig);
	info->dec = 1;

	/* Decode the actual definition */
	if (in_skip_pass) {
		long bits = end_posn - tell_posn();
		input_skip(bits);
	} else {
		char buff[2];
		buff[0] = sort_letters[rs];
		buff[1] = 0;

		d = completion(de_node(buff));

		if (info->def) {
			if (!eq_node(info->def, d)) {
				is_fatal = 0;
				input_error("Token %s defined inconsistently",
				    p->name);
			}

			free_node(d);
			info->pars = old_pars;
		} else
			info->def = d;

		if (rs == SORT_unknown) {
			long bits = end_posn - tell_posn();
			input_skip(bits);
		}

		if (tell_posn() != end_posn)
			input_error("Token %s definition length wrong", p->name);

		if (info->pars) {
			/* Mark the formal arguments as unused */
			construct **ps;
			for (ps = info->pars; *ps; ps++) {
				info = get_tok_info(*ps);
				info->dec = 0;
			}
		}
	}
}


void
de_tokdef(void)
{
	long i, n = tdf_int();

	set_up_labels(n);
	n = tdf_int();

	for (i = 0; i < n; i++) {
		long t;
		node *sig;
		construct *p;

		/* Find the definition type */
		IGNORE de_tokdef_bits();

		/* Find the token */
		t = tdf_int();
		p = find_binding(crt_binding, tok_var, t);

		/* Deal with signature */
		sig = de_node("?[X]");

		/* Decode token definition */
		de_token_defn(p, sig);
	}
}


static void
de_version_number(void)
{
	long v1 = tdf_int();
	long v2 = tdf_int();

	if (v1 != VERSION_major || v2 > VERSION_minor)
		input_error("Illegal version number, %ld.%ld", v1, v2);

	have_version = 1;
}


void
de_version(void)
{
	long i, n = tdf_int();

	for (i = 0; i < n; i++) {
		long m = de_version_bits();

		if (m == ENC_make_version)
			de_version_number();
		else if (m == ENC_user_info)
			IGNORE de_node("X");
	}
}


void
de_magic(char *m)
{
	int i, n = (int)strlen(m);

	for (i = 0; i < n; i++) {
		long c = fetch(8);

		if (c != (long)m[i]) {
			input_error("Bad magic number");
			return;
		}
	}

	de_version_number();
	byte_align();
}
