/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/xalloc.h>

#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/main_reads.h>

#include <reader/externs.h>

#include <refactor/refactor.h>

#include <construct/exp.h>
#include <construct/tags.h>

#include "dg_aux.h"
#include "mark_scope.h"
#include "dg_fns.h"
#include "diag_fns.h"
#include "special_tok.h"

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
	    (son(son(acc)) != NULL && name(son(son(acc))) == chvar_tag &&
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

exp
read_dg_exp(exp body)
{
	dg diag;

	int was_within_diags = within_diags;
	within_diags = 1;
	diag = d_dg();
	within_diags = was_within_diags;

	return f_dg_exp(body, diag);
}

