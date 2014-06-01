/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/exptypes.h>
#include <local/expmacs.h>

/* TODO: stopgap until outs() is centralised */
#if TRANS_80x86
#include "assembler.h"
#include <local/localflags.h>
#include <local/out.h>
#endif

/* TODO: stopgap until outs() is centralised */
#if TRANS_SPARC
#include <local/out.h>
#endif

#include <reader/natmacs.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/readglob.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/machine.h>

#include <linkinfo/messages_li.h>

#include <utility/prefix.h>

#include <main/flags.h>

int use_link_stuff;
weak_cell *weak_list;

/* PROCEDURES */

extern void out_rename(char *, char *);

linkinfo
f_make_weak_defn(exp e1, exp e2)
{
	if (use_link_stuff) {
#if TRANS_80x86 || TRANS_SPARC
		weak_cell *wc = (weak_cell *)xmalloc(sizeof(weak_cell));

		wc->weak_id = brog(son(e1))->dec_u.dec_val.dec_id;
		wc->val_id = brog(son(e2))->dec_u.dec_val.dec_id;
		brog(son(e2))->dec_u.dec_val.isweak = 1;
		wc->next = weak_list;
		weak_list = wc;
#endif
	}

	kill_exp(e1, e1);
	kill_exp(e2, e2);
	return 0;
}


linkinfo
f_make_weak_symbol(tdfstring id, exp e)
{
	if (use_link_stuff) {
#if TRANS_80x86 || TRANS_SPARC
		char **lid = &brog(son(e))->dec_u.dec_val.dec_id;
		char *nid = add_prefix(name_prefix, id.ints.chars);
		brog(son(e))->dec_u.dec_val.isweak = 1;
		brog(son(e))->dec_u.dec_val.extnamed = 1;
		outs(".weak ");
		outs(nid);
		outnl();
		out_rename(*lid, nid);
		*lid = nid;
#endif
	}

	kill_exp(e, e);
	return 0;
}


linkinfo
f_make_comment(tdfstring id)
{
	if (use_link_stuff) {
#if TRANS_80x86 || TRANS_SPARC
		outs(".ident \"");
		outs(add_prefix(name_prefix, id.ints.chars));
		outs("\"");
		outnl();
#endif
	}

	return 0;
}


linkinfo
f_static_name_def(exp e, tdfstring id)
{
	char **oldid = &brog(son(e))->dec_u.dec_val.dec_id;
	char *newid = add_prefix(name_prefix, id.ints.chars);

	if (name(e) != name_tag || !isglob(son(e))) {
		failer(ILLEGAL_STATIC);
		kill_exp(e, e);
		return 0;
	}

	if (separate_units) {
		failer(INCOMPATIBLE_U);
	} else {
		out_rename(*oldid, newid);
	}

	*oldid = newid;
	kill_exp(e, e);
	return 0;
}


void
init_linkinfo(void)
{
	return;
}


linkinfo f_dummy_linkinfo;

linkinfo_list
new_linkinfo_list(int n)
{
	UNUSED(n);
	return 0;
}


linkinfo_list
add_linkinfo_list(linkinfo_list list, linkinfo elem, int index)
{
	UNUSED(list);
	UNUSED(elem);
	UNUSED(index);
	return 0;
}


void
start_make_linkinfo_unit(int no_of_tokens, int no_of_tags, int no_of_als,
			 int no_of_diagtypes)
{
	int i;
	UNUSED(no_of_diagtypes);

	unit_no_of_tokens = no_of_tokens;
	if (unit_no_of_tokens == 0) {
		unit_ind_tokens = NULL;
	} else {
		unit_ind_tokens = (tok_define **)xcalloc(unit_no_of_tokens,
							 sizeof(tok_define *));
	}
	for (i = 0; i < unit_no_of_tokens; ++i) {
		unit_ind_tokens[i] = (tok_define *)0;
	}

	unit_no_of_tags = no_of_tags;
	if (unit_no_of_tags == 0) {
		unit_ind_tags = NULL;
	} else {
		unit_ind_tags = (dec **)xcalloc(unit_no_of_tags, sizeof(dec *));
	}
	for (i = 0; i < unit_no_of_tags; ++i) {
		unit_ind_tags[i] = (dec *)0;
	}

	unit_no_of_als = no_of_als;
	if (unit_no_of_als == 0) {
		unit_ind_als = NULL;
	} else {
		unit_ind_als = (aldef **)xcalloc(unit_no_of_als, sizeof(aldef *));
	}
	for (i = 0; i < unit_no_of_als; ++i) {
		unit_ind_als[i] = (aldef *)0;
	}

	return;
}


int
f_make_linkinfo_unit(void)
{
	int i;
	int j = 0;
	int no_of_labels;
	for (i = 0; i < unit_no_of_tokens; ++i) {
		if (unit_ind_tokens[i] == (tok_define *)0)
			unit_ind_tokens[i] = &unit_toktab[j++];
	}
	j = 0;
	for (i = 0; i < unit_no_of_tags; ++i) {
		if (unit_ind_tags[i] == (dec *)0)
			unit_ind_tags[i] = &unit_tagtab[j++];
	}
	j = 0;
	for (i = 0; i < unit_no_of_als; ++i) {
		if (unit_ind_als[i] == (aldef *)0)
			unit_ind_als[i] = &unit_altab[j++];
	}
	start_bytestream();
	no_of_labels = small_dtdfint();
	unit_no_of_labels = no_of_labels;
	if (unit_no_of_labels == 0) {
		unit_labtab = NULL;
	} else {
		unit_labtab = (exp *)xcalloc(unit_no_of_labels, sizeof(exp));
	}
	IGNORE d_linkinfo_list();
	end_bytestream();

	xfree((void *)unit_ind_tokens);
	xfree((void *)unit_ind_tags);
	xfree((void *)unit_ind_als);
	xfree((void *)unit_labtab);
	xfree((void *)unit_toktab);
	xfree((void *)unit_tagtab);

	return 0;
}


linkinfo_props
f_make_linkinfos(tdfint nl, linkinfo_list tds)
{
	UNUSED(nl);
	UNUSED(tds);
	return 0;
}
