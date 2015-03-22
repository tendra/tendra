/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/xalloc.h>

#include <reader/exp.h>

#include <reader/externs.h>

#include <construct/tags.h>

#include "dg_aux.h"
#include "mark_scope.h"

int doing_mark_scope = 0;

/* called by read_diag_id_scope; dgf(e) holds DIAG_INFO_ID */
void
mark_scope(exp e)
{
	dg_info d = dgf(e);
	dg_info *ptr;
	exp id;

	if (!d || d->key != DGA_NAME ||
	    d->data.i_nam.dnam->key != DGN_OBJECT) {
		return;
	}

	id = son(d->data.i_nam.dnam->data.n_obj.obtain_val);
	if (name(id) == cont_tag) {
		id = son(id);
	}

	if (name(id) != name_tag) {
		return;
	}

	id = son(id);
	if (isparam(id)) {
		return;
	}

	ptr = &(d->more);
	d = nildiag;

	while (*ptr && (*ptr)->key != DGA_SCOPE) {
		ptr = &((*ptr)->more);
	}

	if (!*ptr && name(e) == seq_tag && name(son(son(e))) == ass_tag &&
	    last(son(son(e))) && name(bro(son(e))) != ident_tag) {
		ptr = &dgf(bro(son(e)));
		while (*ptr && (*ptr)->key != DGA_SCOPE) {
			ptr = &((*ptr)->more);
		}
	}

	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	} else {
		d = f_lexical_block_dg(no_dg_idname_option, no_dg_sourcepos_option);
		d->data.i_scope.begin_st = (long)(-1);
		doing_mark_scope = 1;
	}

	/* if (isglob(id)) */ {
		d->more = dgf(e);
		dgf(e) = d;
	}
#if 0
	else {
		exp def = son(id);
		if (dgf(def) && dgf(def)->key == DGA_SRC)
			dgf(e)->data.i_nam.dnam->whence =
			    dgf(def)->data.i_src.startpos;
		d->more = dgf(id);
		dgf(id) = d;
	}
#endif
}

/* called by read_diag_type_scope; dgf(e) holds DIAG_INFO_ID */
void
mark_scope2(exp e)
{
	dg_info d = dgf(e);
	dg_info *ptr;

	if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_TYPE) {
		return;
	}

	ptr = &(d->more);
	d = nildiag;
	while (*ptr && (*ptr)->key != DGA_SCOPE) {
		ptr = &((*ptr)->more);
	}

	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	} else {
		d = f_lexical_block_dg(no_dg_idname_option,
		                       no_dg_sourcepos_option);
		d->data.i_scope.begin_st = (long)(-1);
		doing_mark_scope = 1;
	}

	d->more = dgf(e);
	dgf(e) = d;
}

void
correct_mark_scope(exp e)
{
	dg_info d = nildiag;
	dg_info *ptr = &(dgf(bro(son(e))));

	while (*ptr && (*ptr)->key != DGA_SCOPE) {
		ptr = &(*ptr)->more;
	}

	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}

	if (d) {
		d->more = dgf(e);
		dgf(e) = d;
	}
}

