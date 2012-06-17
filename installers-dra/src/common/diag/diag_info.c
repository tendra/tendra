/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/xalloc.h>

#include "config.h"

#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/sortmacs.h>
#include <reader/main_reads.h>

#include <refactor/refactor.h>

#ifdef NEWDIAGS
#include "expmacs.h"

#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/tags.h>

#include <diag/dg_aux.h>
#include <diag/mark_scope.h>
#endif

#include <diag/dg_fns.h>
#include <diag/diag_fns.h>


/* PROCEDURES */


#ifdef NEWDIAGS


exp
diag_locate(exp e)
{
	/* need contents for var locations, old diags */
	exp id = son(e);
	if (isglob(id)) {
		if (brog(id)->dec_u.dec_val.dec_var) {
			e = f_contents(brog(id)->dec_u.dec_val.dec_shape, e);
		}
	} else {
		if (isvar(id)) {
			e = f_contents(sh(son(id)), e);
		}
	}
	return e;
}


exp
read_exp_to_source(exp body)
{
	dg_sourcepos s1, s2;
	int was_within_diags = within_diags;
	within_diags = 1;
	s1 = d_sourcemark();
	s2 = d_sourcemark();
	within_diags = was_within_diags;
	if (s1.file == s2.file) {
		s2.sp_key = SP_SPAN;
		s2.to_file = s2.file;
		s2.to_line = s2.from_line;
		s2.to_column = s2.from_column;
		s2.from_line = s1.from_line;
		s2.from_column = s1.from_column;
	}
	if (name(body) == proc_tag || name(body) == general_proc_tag) {
		return body;
	}
	body = f_dg_exp(body, f_singlestep_dg(s1));
	body = f_dg_exp(body, f_sourcepos_dg(s2));
	return body;
}


exp
read_diag_id_scope(exp body)
{
	dg_idname nam;
	exp acc;
	dg_type typ;
	dg_name dgn;
	int was_within_diags = within_diags;
	within_diags = 1;
	nam = f_dg_sourcestring_idname(d_tdfstring());
	acc = hold_refactor(d_exp());
	typ = d_diag_type();
	within_diags = was_within_diags;
	dgn = f_dg_object_name(nam, f_dg_null_sourcepos, typ,
			       yes_exp_option(diag_locate(acc)),
			       no_dg_accessibility_option);

	if (isparam(son(acc)) ||
	    (son(son(acc)) != nilexp && name(son(son(acc))) == chvar_tag &&
	     shape_size(sh(son(son(acc)))) < 32 &&
	     name(son(son(son(acc)))) == cont_tag &&
	     name(son(son(son(son(acc))))) == name_tag &&
	     isparam(son(son(son(son(son(acc)))))))) {
		dg_info x = dgf(body);
		if (x && x->key == DGA_PARAMS) {
			dgn->next = x->data.i_param.args;
			x->data.i_param.args = dgn;
		} else {
			body = f_dg_exp(body, f_params_dg(dgn, no_exp_option));
		}
	} else {
		body = f_dg_exp(body, f_name_decl_dg(dgn));
		mark_scope(body);
	}
	return body;
}


exp
read_diag_type_scope(exp body)
{
	dg_idname nam;
	dg_type typ;
	dg_name dgn;
	int was_within_diags = within_diags;
	within_diags = 1;
	nam = f_dg_sourcestring_idname(d_tdfstring());
	typ = d_diag_type();
	within_diags = was_within_diags;
	dgn = f_dg_type_name(nam, f_dg_null_sourcepos,
			     no_dg_accessibility_option, typ, f_false,
			     no_bool_option, no_dg_constraint_list_option);
	body = f_dg_exp(body, f_name_decl_dg(dgn));
	mark_scope2(body);
	return body;
}


#else

diag_info *
read_exp_to_source(void)
{
	diag_info *new = (diag_info *)xcalloc(1, sizeof(diag_info));

	new->key = DIAG_INFO_SOURCE;
	new->data.source.beg = d_sourcemark();
	new->data.source.end = d_sourcemark();

	return new;
}


diag_info *
read_diag_id_scope(void)
{
	diag_info *new = (diag_info *)xcalloc(1, sizeof(diag_info));

	new->key = DIAG_INFO_ID;
	new->data.id_scope.nme = d_tdfstring();
	new->data.id_scope.access = hold_refactor(d_exp());
	IGNORE hold(hold(new->data.id_scope.access));
	new->data.id_scope.typ = d_diag_type();
	return new;
}


diag_info *
read_diag_type_scope(void)
{
	diag_info *new = (diag_info *)xcalloc(1, sizeof(diag_info));

	new->key = DIAG_INFO_TYPE;
	new->data.type_scope.nme = d_tdfstring();
	new->data.type_scope.typ = d_diag_type();
	return new;
}


diag_info *
read_diag_tag_scope(void)
{
	diag_info *new = (diag_info *)xcalloc(2, sizeof(diag_info));

	new->key = DIAG_INFO_TAG;
	new->data.tag_scope.nme = d_tdfstring();
	new->data.tag_scope.typ = d_diag_type();
	return new;
}

#endif
