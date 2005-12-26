/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */




#include "config.h"
#include "fmm.h"

#include "common_types.h"
#include "readglob.h"
#include "table_fns.h"
#include "basicread.h"
#include "sortmacs.h"
#ifdef NEWDIAGS
#include "exp.h"
#include "tags.h"
#include "externs.h"
#include "dg_aux.h"
#include "mark_scope.h"
#endif

#include "main_reads.h"
#include "check.h"
#include "dg_fns.h"
#include "diag_fns.h"


/* PROCEDURES */


#ifdef NEWDIAGS


exp
diag_locate(exp e)
{
	/* need contents for var locations, old diags */
	exp id = son(e);
	if (isglob (id)) {
		if (brog(id)->dec_u.dec_val.dec_var)
			e = f_contents (brog(id)->dec_u.dec_val.dec_shape, e);
	}
	else {
		if (isvar (id))
			e = f_contents (sh(son(id)), e);
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
	if (name(body) == proc_tag || name(body) == general_proc_tag)
		return body;
	body = f_dg_exp (body, f_singlestep_dg (s1));
	body = f_dg_exp (body, f_sourcepos_dg (s2));
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
	nam = f_dg_sourcestring_idname (d_tdfstring());
	acc = hold_check (d_exp());
	typ = d_diag_type();
	within_diags = was_within_diags;
	dgn = f_dg_object_name (
		nam,
		f_dg_null_sourcepos,
		typ,
		yes_exp_option (diag_locate (acc)),
		no_dg_accessibility_option);
	
	if (isparam(son(acc)) || (son(son(acc)) != nilexp &&
							  name(son(son(acc))) == chvar_tag &&
							  shape_size(sh(son(son(acc)))) < 32 &&
							  name(son(son(son(acc)))) == cont_tag &&
							  name(son(son(son(son(acc))))) == name_tag &&
							  isparam (son(son(son(son(son(acc)))))))) {
		dg_info x = dgf(body);
		if (x && x->key == DGA_PARAMS) {
			dgn->next = x->data.i_param.args;
			x->data.i_param.args = dgn;
		}
		else {
			body = f_dg_exp (body, f_params_dg (dgn, no_exp_option));
		}
	}
	else {
		body = f_dg_exp (body, f_name_decl_dg (dgn));
		mark_scope (body);
	}
	return (body);
}


exp
read_diag_type_scope(exp body)
{
	dg_idname nam;
	dg_type typ;
	dg_name dgn;
	int was_within_diags = within_diags;
	within_diags = 1;
	nam = f_dg_sourcestring_idname (d_tdfstring());
	typ = d_diag_type();
	within_diags = was_within_diags;
	dgn = f_dg_type_name (
		nam,
		f_dg_null_sourcepos,
		no_dg_accessibility_option,
		typ,
		f_false,
		no_bool_option,
		no_dg_constraint_list_option);
	body = f_dg_exp (body, f_name_decl_dg (dgn));
	mark_scope2 (body);
	return body;
}


#else

diag_info *
read_exp_to_source()
{
	diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));
	
	new->key = DIAG_INFO_SOURCE;
	new->data.source.beg 	= d_sourcemark();
	new->data.source.end 	= d_sourcemark();
	
	return new;
}

diag_info *
read_diag_id_scope()
{
	diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));
	
	new->key 		= DIAG_INFO_ID;
	new->data.id_scope.nme = d_tdfstring();
	new->data.id_scope.access = hold_check(d_exp());
	IGNORE hold(hold(new->data.id_scope.access));
	new->data.id_scope.typ = d_diag_type();
	return (new);
}

diag_info *
read_diag_type_scope()
{
	diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));
	
	new->key 		= DIAG_INFO_TYPE;
	new->data.type_scope.nme = d_tdfstring();
	new->data.type_scope.typ = d_diag_type();
	return (new);
}

diag_info *
read_diag_tag_scope()
{
	diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));
	
	new->key 		= DIAG_INFO_TAG;
	new->data.tag_scope.nme = d_tdfstring();
	new->data.tag_scope.typ = d_diag_type();
	return (new);
}


#endif
