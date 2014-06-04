/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/xalloc.h>

#include <reader/exp.h>

#include <reader/code.h>
#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/sort.h>
#include <reader/main_reads.h>
#include <reader/token.h>
#include <reader/externs.h>

#include <construct/install_fns.h>
#include <construct/tags.h>

#include <main/flags.h>

#include "dg_fns.h"
#include "dg_aux.h"
#include "dg_globs.h"


dg_filename all_files = (dg_filename)0;
dg_compilation all_comp_units = (dg_compilation)0;



/*
 * This is a workaround for shared/xcalloc asserting count is non-zero, but the
 * code here possibly being able to do that. I'm unsure if it actually does or
 * not. However, I think most of these instances probably oughn't to use calloc
 * at all.
 */
static void *
dg_xcalloc(size_t count, size_t size)
{
	if (count == 0) {
		return NULL;
	}

	return xcalloc(count, size);
}

string_list
new_string_list(int n)
{
	string_list ans;
	ans.len = n;
	ans.array = (char **)dg_xcalloc(n, sizeof(char *));
	return ans;
}


string_list
add_string_list(string_list list, string elem, int index)
{
	list.array[index] = elem.ints.chars;
	return list;
}


bool_option no_bool_option;

bool_option
yes_bool_option(bool elem)
{
	bool_option res;
	res.val = elem;
	res.present = 1;
	return res;
}


void
init_bool_option(void)
{
	no_bool_option.present = 0;
	return;
}


shape_option no_shape_option;

shape_option
yes_shape_option(shape elem)
{
	shape_option res;
	res.val = elem;
	res.present = 1;
	return res;
}


void
init_shape_option(void)
{
	no_shape_option.present = 0;
	return;
}


token_option no_token_option;

token_option
yes_token_option(token elem)
{
	token_option res;
	res.val = elem;
	res.present = 1;
	return res;
}


void
init_token_option(void)
{
	no_token_option.present = 0;
	return;
}


int unit_no_of_dgtags;
dgtag_struct **unit_ind_dgtags;
dgtag_struct *unit_dgtagtab;


dg
f_dg_apply_token(token token_value, bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DG_SORT, (tokval *)0);
	return v.tk_dg;
}


dg f_dummy_dg;

dg
f_make_tag_dg(dg_tag tg, dg diag)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_INFO;
	tg->p.info = diag;
	diag->this_tag = tg;
	return diag;
}


dg
f_list_dg(dg_list args)
{
	return args;
}


dg
f_params_dg(dg_name_list params, exp_option outer_env)
{
	dg ans = new_dg_info(DGA_PARAMS);
	ans->data.i_param.args = params;
	if (outer_env.present) {
		ans->data.i_param.o_env = diaginfo_exp(outer_env.val);
	} else {
		ans->data.i_param.o_env = NULL;
	}
	ans->data.i_param.b_start = 0;
	return ans;
}


dg
f_source_language_dg(nat language)
{
	dg ans = new_dg_info(DGA_COMP);
	ans->data.i_comp.is_tag = 0;
	ans->data.i_comp.corl.comp_lang = language.nat_val.small_nat;
	return ans;
}


dg
f_compilation_dg(dg_tag comp_unit)
{
	dg ans = new_dg_info(DGA_COMP);
	ans->data.i_comp.is_tag = 1;
	ans->data.i_comp.corl.comp_tag = comp_unit;
	return ans;
}


dg
f_sourcepos_dg(dg_sourcepos span)
{
	dg ans = new_dg_info(DGA_SRC);
	ans->data.i_src.is_stmt = 0;
	ans->data.i_src.startpos = shorten_sourcepos(span);
	ans->data.i_src.endpos = end_sourcepos(span);
	return ans;
}


dg
f_name_decl_dg(dg_name dname)
{
	dg ans = new_dg_info(DGA_NAME);
	ans->data.i_nam.dnam = dname;
	return ans;
}


dg
f_lexical_block_dg(dg_idname_option idname, dg_sourcepos src_pos)
{
	dg ans = new_dg_info(DGA_SCOPE);
	ans->data.i_scope.lexname = idname_chars(idname);
	ans->data.i_scope.lexpos = shorten_sourcepos(src_pos);
	ans->data.i_scope.endpos = end_sourcepos(src_pos);
	ans->data.i_scope.begin_st = (long)0;
	return ans;
}


dg
f_inline_call_dg(dg_tag proc, dg_name_list act_params, nat_option call_kind)
{
	dg ans = new_dg_info(DGA_INL_CALL);
	ans->data.i_inl.proc = proc;
	ans->data.i_inl.args = act_params;
	if (call_kind.present) {
		ans->data.i_inl.ck = call_kind.val.nat_val.small_nat;
	} else {
		ans->data.i_inl.ck = 0;
	}
	ans->data.i_inl.resref = nildiag;
	proc->any_inl = 1;
	return ans;
}


dg
f_inline_result_dg(dg_tag inline_id)
{
	dg ans = new_dg_info(DGA_INL_RES);
	ans->data.i_res.call = inline_id;
	ans->data.i_res.res.k = NO_WH;
	ans->data.i_res.next = (dg_info)0;
	return ans;
}


dg
f_singlestep_dg(dg_sourcepos src_pos)
{
	dg ans = new_dg_info(DGA_SRC);
	ans->data.i_src.is_stmt = 1;
	ans->data.i_src.startpos = shorten_sourcepos(src_pos);
	ans->data.i_src.endpos.file = 0;
	return ans;
}


dg
f_with_dg(dg_type type, exp obtain_value)
{
	dg ans = new_dg_info(DGA_SRC);
	ans->data.i_with.w_typ = type;
	ans->data.i_with.w_exp = diaginfo_exp(obtain_value);
	return ans;
}


dg
f_exception_scope_dg(dg_tag_list handlers)
{
	dg ans = new_dg_info(DGA_X_TRY);
	ans->data.i_try.hl = handlers;
	return ans;
}


dg
f_exception_handler_dg(dg_name_option ex)
{
	dg ans = new_dg_info(DGA_X_CATCH);
	ans->data.i_catch.ex = ex;
	return ans;
}


dg
f_abortable_part_dg(dg_sourcepos src_pos, bool no_code)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_ABTL;
	ans->data.i_rvs.n_code = (no_code ? 0 : 2);
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = 0;
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = (dg_tag)0;
	ans->data.i_rvs.en = (dg_tag)0;
	return ans;
}


dg
f_accept_dg(dg_sourcepos src_pos, dg_tag entry, dg_name_list params,
	    bool no_code, dg_tag_option alt)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_ACC;
	ans->data.i_rvs.n_code = (no_code ? 0 : 2);
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = (alt ? 1 : 0);
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = alt;
	ans->data.i_rvs.en = entry;
	ans->data.i_rvs.u2.p = params;
	return ans;
}


dg
f_barrier_dg(dg_sourcepos src_pos, dg_tag entry)
{
	dg ans = new_dg_info(DGA_BAR);
	ans->data.i_bar.pos = shorten_sourcepos(src_pos);
	ans->data.i_bar.entry = entry;
	return ans;
}


dg
f_branch_dg(dg_sourcepos stmt_src_pos)
{
	dg ans = new_dg_info(DGA_BRANCH);
	ans->data.i_brn.pos = shorten_sourcepos(stmt_src_pos);
	return ans;
}


dg
f_call_dg(dg_idname_option idname, dg_sourcepos src_pos, nat_option call_kind,
	  dg_tag_option module, dg_tag_option basetype)
{
	dg ans = new_dg_info(DGA_CALL);
	ans->data.i_call.clnam = idname_chars(idname);
	ans->data.i_call.pos = shorten_sourcepos(src_pos);
	if (call_kind.present) {
		ans->data.i_call.ck = call_kind.val.nat_val.small_nat;
	} else {
		ans->data.i_call.ck = 0;
	}
	ans->data.i_call.p.k = NO_WH;
	UNUSED(module);
	UNUSED(basetype);
	return ans;
}


dg
f_destructor_dg(dg_sourcepos whence, exp_option obtain_value)
{
	dg ans = new_dg_info(DGA_DEST);
	ans->data.i_dest.pos = shorten_sourcepos(whence);
	if (obtain_value.present) {
		ans->data.i_dest.val = diaginfo_exp(obtain_value.val);
	} else {
		ans->data.i_dest.val = NULL;
	}
	return ans;
}


dg
f_inlined_dg(dg d, dg_tag origin)
{
	UNUSED(origin);
	/* inlined_dg not yet supported */
	return d;
}


dg
f_jump_dg(dg_sourcepos stmt_src_pos)
{
	dg ans = new_dg_info(DGA_JUMP);
	ans->data.i_tst.pos = shorten_sourcepos(stmt_src_pos);
	return ans;
}


dg
f_label_dg(dg_idname idname, dg_sourcepos src_pos)
{
	dg ans = new_dg_info(DGA_LAB);
	ans->data.i_scope.lexname = idname_chars(idname);
	ans->data.i_scope.lexpos = shorten_sourcepos(src_pos);
	return ans;
}


dg
f_long_jump_dg(dg_sourcepos stmt_src_pos)
{
	dg ans = new_dg_info(DGA_LJ);
	ans->data.i_lj.pos = shorten_sourcepos(stmt_src_pos);
	return ans;
}


dg
f_raise_dg(dg_sourcepos stmt_src_pos, dg_type_option ex, exp_option value)
{
	dg ans = new_dg_info(DGA_X_RAISE);
	ans->data.i_raise.pos = shorten_sourcepos(stmt_src_pos);
	ans->data.i_raise.x_typ = ex;
	if (value.present) {
		ans->data.i_raise.x_val = diaginfo_exp(value.val);
	} else {
		ans->data.i_raise.x_val = NULL;
	}
	return ans;
}


dg
f_requeue_dg(dg_sourcepos stmt_src_pos, dg_tag entry, bool with_abort)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_REQUE;
	ans->data.i_rvs.n_code = 2;
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = 0;
	ans->data.i_rvs.w_abort = with_abort;
	ans->data.i_rvs.pos = shorten_sourcepos(stmt_src_pos);
	ans->data.i_rvs.u.tg = (dg_tag)0;
	ans->data.i_rvs.en = entry;
	return ans;
}


dg
f_rts_call_dg(dg_sourcepos src_pos, nat call_kind, dg_tag_option entry,
	      dg_tag_option alt)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_RTS;
	ans->data.i_rvs.n_code = 1;
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = (alt ? 1 : 0);
	ans->data.i_rvs.kind = call_kind.nat_val.small_nat;
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = alt;
	ans->data.i_rvs.en = entry;
	return ans;
}


dg
f_select_dg(dg_sourcepos src_pos, bool async)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_SEL;
	ans->data.i_rvs.n_code = (async ? 2 : 1);
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = 0;
	ans->data.i_rvs.async = async;
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = (dg_tag)0;
	return ans;
}


dg
f_select_alternative_dg(dg_sourcepos src_pos, nat alt_kind, bool no_code,
			exp alt_value)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_ALT;
	ans->data.i_rvs.n_code = (no_code ? 0 : 2);
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = 0;
	ans->data.i_rvs.kind = alt_kind.nat_val.small_nat;
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = (dg_tag)0;
	ans->data.i_rvs.u2.e = diaginfo_exp(alt_value);
	return ans;
}


dg
f_select_guard_dg(dg_sourcepos src_pos, dg_tag alt)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_SGD;
	ans->data.i_rvs.n_code = 2;
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = (alt ? 1 : 0);
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = alt;
	return ans;
}


dg
f_statement_part_dg(dg_tag lb)
{
	dg ans = new_dg_info(DGA_BEG);
	ans->data.i_tg = lb;
	return ans;
}


dg
f_test_dg(dg_sourcepos src_pos, bool inverted)
{
	dg ans = new_dg_info(DGA_TEST);
	ans->data.i_tst.pos = shorten_sourcepos(src_pos);
	ans->data.i_tst.inv = inverted;
	return ans;
}


dg
f_triggering_alternative_dg(dg_sourcepos src_pos, nat alt_kind, bool no_code)
{
	dg ans = new_dg_info(DGA_RVS);
	ans->data.i_rvs.rvs_key = DGR_TRIG;
	ans->data.i_rvs.n_code = (no_code ? 0 : 2);
	ans->data.i_rvs.has_iv = 0;
	ans->data.i_rvs.alt = 0;
	ans->data.i_rvs.kind = alt_kind.nat_val.small_nat;
	ans->data.i_rvs.pos = shorten_sourcepos(src_pos);
	ans->data.i_rvs.u.tg = (dg_tag)0;
	return ans;
}


void
init_dg(void)
{
	return;
}


dg_comp_props f_dummy_dg_comp_props;

dg_comp_props
f_make_dg_compunit(tdfint no_labels, dg_compilation comp_unit, dg_append_list l)
{
	UNUSED(no_labels);
	UNUSED(comp_unit);
	UNUSED(l);
	return f_dummy_dg_comp_props;	/* dummy, never called */
}


void
init_dg_comp_props(void)
{
	return;
}


dg_tag f_dummy_dg_tag;

dg_tag
f_make_dg_tag(tdfint num)
{
	int index = natint(num);
	if (index >= unit_no_of_dgtags) {
		failer("make_dg_tag out of range");
	}
	return unit_ind_dgtags[index];
}


void
init_dg_tag(void)
{
	return;
}


dg_name f_dummy_dg_name;

dg_name
f_dg_name_apply_token(token token_value, bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DG_NAME_SORT, (tokval *)0);
	return v.tk_dg_name;
}


dg_name
f_dg_tag_name(dg_tag tg, dg_name nam)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_NAME;
	tg->p.nam = nam;
	if (!nam->mor) {
		extend_dg_name(nam);
	}
	nam->mor->this_tag = tg;
	return nam;
}


dg_name
f_dg_object_name(dg_idname idname, dg_sourcepos whence, dg_type type,
		 exp_option obtain_value, dg_accessibility_option accessibility)
{
	dg_name ans = new_dg_name(DGN_OBJECT);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_obj.typ = type;

	if (accessibility != DG_ACC_NONE) {
		extend_dg_name(ans);
		ans->mor->acc = accessibility;
	}
	return ans;
}


dg_name
f_dg_proc_name(dg_idname idname, dg_sourcepos whence, dg_type type,
	       exp_option obtain_value, dg_accessibility_option accessibility,
	       dg_virtuality_option virtuality, bool isinline,
	       dg_type_list_option exceptions, dg_tag_option elaboration)
{
	dg_name ans = new_dg_name(DGN_PROC);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_proc.typ = type;

	return ans;
}


dg_name
f_dg_inlined_name(dg_name nam, dg_tag origin)
{
	if (!nam->mor) {
		extend_dg_name(nam);
	}
	nam->mor->inline_ref = origin;
	return nam;
}


dg_name
f_dg_constant_name(dg_name nam)
{
	if (!nam->mor) {
		extend_dg_name(nam);
	}
	nam->mor->isconst = 1;
	return nam;
}


dg_name
f_dg_type_name(dg_idname_option idname, dg_sourcepos whence,
	       dg_accessibility_option accessibility, dg_type_option type,
	       bool new_type, bool_option ada_derived,
	       dg_constraint_list_option constraints)
{
	dg_name ans = new_dg_name(DGN_TYPE);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_typ.raw = type;
	if (idname.id_key == DG_ID_NONE) {
		ans->data.n_typ.named = type;
	} else {
		ans->data.n_typ.named = (dg_type)0;
	}
	if (accessibility != DG_ACC_NONE || new_type ||
	    (ada_derived.present && ada_derived.val)) {
		extend_dg_name(ans);
		ans->mor->acc = accessibility;
		ans->mor->isnew = new_type;
		if (ada_derived.present) {
			ans->mor->aderiv = ada_derived.val;
		}
	}
	ans->data.n_typ.constraints = constraints;
	return ans;
}


dg_name
f_dg_subunit_name(dg_tag parent, dg_name nam, nat subunit_kind,
		  dg_accessibility_option accessibility)
{
	dg_name ans = new_dg_name(DGN_SUBUNIT);
	ans->data.n_sub.parent = parent;
	ans->data.n_sub.sub = nam;
	switch (subunit_kind.nat_val.small_nat) {
	case 1:
		/* SUK_child */
		ans->data.n_sub.child = 1;
		ans->data.n_sub.split = 0;
		break;
	case 2:
		/* SUK_separate */
		ans->data.n_sub.child = 0;
		ans->data.n_sub.split = 0;
		ans->data.n_sub.acc = accessibility;
		break;
	case 3:
		/* SUK_split_module */
		ans->data.n_sub.child = 0;
		ans->data.n_sub.split = 1;
		break;
	default:
		failer("unexpected SUK_kind");
	}
	return ans;
}


dg_name
f_dg_program_name(dg_idname idname, dg_sourcepos whence, exp obtain_value)
{
	dg_name ans = new_dg_name(DGN_PROC);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_proc.typ = (dg_type)0;
	ans->data.n_proc.obtain_val = diaginfo_exp(obtain_value);
	ans->data.n_proc.params = (dg_info)0;
	extend_dg_name(ans);
	ans->mor->prognm = 1;
	return ans;
}


dg_name
f_dg_entry_family_name(dg_name proc, dg_dim family)
{
	if (!proc->mor) {
		extend_dg_name(proc);
	}
	proc->mor->en_family = (dg_dim *)xmalloc(sizeof(dg_dim));
	*(proc->mor->en_family) = family;
	return proc;
}


dg_name
f_dg_entry_name(dg_idname idname, dg_sourcepos whence, dg_type type,
		dg_accessibility_option accessibility, dg_dim_option family)
{
	dg_name ans = new_dg_name(DGN_ENTRY);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_proc.typ = type;
	if (accessibility != DG_ACC_NONE || family.d_key != DG_DIM_NONE) {
		extend_dg_name(ans);
		ans->mor->acc = accessibility;
		if (family.d_key != DG_DIM_NONE) {
			ans->mor->en_family = (dg_dim *)xmalloc(sizeof(dg_dim));
			*(ans->mor->en_family) = family;
		}
	}
	return ans;
}


dg_name
f_dg_is_spec_name(dg_name nam, bool_option is_separate)
{
	if (!nam->mor) {
		extend_dg_name(nam);
	}
	nam->mor->isspec = 1;
	if (is_separate.present && is_separate.val) {
		nam->mor->issep = 1;
	}
	return nam;
}


dg_name
f_dg_module_name(dg_idname idname, dg_sourcepos whence, dg_namelist memlist,
		 exp_option init, dg_tag_option elaboration)
{
	dg_name ans = new_dg_name(DGN_MODULE);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_mod.members = memlist.list;

	if (elaboration) {
		extend_dg_name(ans);
		ans->mor->elabn = elaboration;
	}
	return ans;
}


dg_name
f_dg_namespace_name(dg_idname idname, dg_sourcepos whence, dg_namelist members)
{
	dg_name ans = new_dg_name(DGN_NSP);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(whence);
	ans->data.n_mod.members = members.list;
	if (members.tg) {
		members.tg->p.nl = &(ans->data.n_mod.members);
	}
	ans->data.n_mod.init = NULL;
	return ans;
}


dg_name
f_dg_rep_clause_name(dg_name item, exp location)
{
	if (!item->mor) {
		extend_dg_name(item);
	}
	item->mor->repn = diaginfo_exp(location);
	return item;
}


dg_name
f_dg_spec_ref_name(dg_tag specification, dg_name nam)
{
	if (!nam->mor) {
		extend_dg_name(nam);
	}
	nam->mor->refspec = specification;
	return nam;
}


dg_name
f_dg_visibility_name(dg_tag dname, nat import_kind, dg_idname_option idname,
		     dg_sourcepos_option src_pos,
		     dg_accessibility_option accessibility, dg_type_option type)
{
	dg_name ans = new_dg_name(DGN_IMPORT);
	ans->idnam = idname;
	ans->whence = shorten_sourcepos(src_pos);
	ans->data.n_imp.import = dname;
	ans->data.n_imp.ik = import_kind.nat_val.small_nat;
	if (accessibility != DG_ACC_NONE) {
		extend_dg_name(ans);
		ans->mor->acc = accessibility;
	}
	ans->data.n_imp.i_typ = type;
	return ans;
}


void
init_dg_name(void)
{
	return;
}


dg_type f_dummy_dg_type;

dg_type
f_dg_type_apply_token(token token_value, bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DG_TYPE_SORT, (tokval *)0);
	return v.tk_dg_type;
}


dg_type
f_dg_tag_type(dg_tag tg, dg_type type)
{
	if (tg->key && tg->key != DGK_TYPE) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_TYPE;
	tg->p.typ = type;
	return type;
}


dg_type
f_dg_named_type(dg_tag dname)
{
	dg_type ans;
	if (dname->key == DGK_TYPE) {
		return dname->p.typ;
	}
	if (dname->key == DGK_NAME && dname->p.nam->key == DGN_TYPE &&
	    dname->p.nam->data.n_typ.named) {
		return dname->p.nam->data.n_typ.named;
	}
	ans = new_dg_type(DGT_TAGGED);
	ans->data.t_tag = dname;
	if (dname->key == DGK_NONE && dname->outref.k == LAB_STR) {
		dname->key = DGK_TYPE;
		dname->p.typ = ans;
		ans->outref = dname->outref;
	} else if (dname->key == DGK_NAME && dname->p.nam->key == DGN_TYPE) {
		dname->p.nam->data.n_typ.named = ans;
	}
	return ans;
}


dg_type
f_dg_is_spec_type(dg_type type)
{
	if (!type->mor) {
		extend_dg_type(type);
	}
	type->mor->isspec = 1;
	return type;
}


dg_type
f_dg_spec_ref_type(dg_tag specification, dg_type type)
{
	if (!type->mor) {
		extend_dg_type(type);
	}
	type->mor->refspec = specification;
	return type;
}


dg_type
f_dg_modular_type(dg_type rep_type, exp size)
{
	dg_type ans = new_dg_type(DGT_MOD);
	ans->data.t_adanum.rept = rep_type;
	ans->data.t_adanum.digits = diaginfo_exp(size);
	return ans;
}


dg_type
f_dg_qualified_type(dg_qualifier qualifier, dg_type type)
{
	return get_qual_dg_type(qualifier, type);
}


dg_type
f_dg_pointer_type(dg_type type, bool_option heap_only)
{
	if (heap_only.present && heap_only.val) {
		return get_qual_dg_type(DG_HPPTR_T, type);
	}
	return get_qual_dg_type(DG_PTR_T, type);
}


dg_type
f_dg_reference_type(dg_type type)
{
	return get_qual_dg_type(DG_REF_T, type);
}


dg_type
f_dg_packed_type(dg_type type, shape sha)
{
	UNUSED(sha);
	return get_qual_dg_type(DG_PACK_T, type);
}


dg_type
f_dg_array_type(dg_type element_type, exp stride, bool_option row_major,
		dg_dim_list dimensions)
{
	dg_type ans = new_dg_type(DGT_ARRAY);
	ans->data.t_arr.elem_type = element_type;
	ans->data.t_arr.stride = diaginfo_exp(stride);
	ans->data.t_arr.rowm = (row_major.present ? row_major.val : 1);
	ans->data.t_arr.dims = dimensions;
	return ans;
}


dg_type
f_dg_bitfield_type(dg_type type, bitfield_variety bv, shape sha)
{
	return get_dg_bitfield_type(type, sha, bv);
}


dg_type
f_dg_enum_type(dg_enum_list values, dg_idname_option tagname,
	       dg_sourcepos_option src_pos, shape sha, bool new_type)
{
	dg_type ans = new_dg_type(DGT_ENUM);
	ans->data.t_enum.tnam = idname_chars(tagname);
	ans->data.t_enum.tpos = shorten_sourcepos(src_pos);
	ans->data.t_enum.values = values;
	ans->data.t_enum.sha = sha;
	if (new_type) {
		extend_dg_type(ans);
		ans->mor->isnew = new_type;
	}
	return ans;
}


dg_type
f_dg_string_type(dg_tag character_type, exp lower_bound, exp length)
{
	dg_type ans = new_dg_type(DGT_STRING);
	ans->data.t_string.ct = character_type;
	ans->data.t_string.lb = diaginfo_exp(lower_bound);
	ans->data.t_string.length = diaginfo_exp(length);
	return ans;
}


dg_type
f_dg_struct_type(dg_classmem_list fields, shape_option sha,
		 dg_idname_option tagname, dg_sourcepos_option src_pos,
		 dg_varpart_option varpart, bool is_union, bool new_type)
{
	dg_type ans = new_dg_type(DGT_STRUCT);
	ans->data.t_struct.idnam = tagname;
	ans->data.t_struct.tpos = shorten_sourcepos(src_pos);
	ans->data.t_struct.is_union = is_union;
	if (sha.present) {
		ans->data.t_struct.sha = sha.val;
	} else {
		ans->data.t_struct.sha = (shape)0;
	}
	ans->data.t_struct.u.fields = fields;
	if (new_type) {
		extend_dg_type(ans);
		ans->mor->isnew = new_type;
	}
	ans->data.t_struct.vpart = varpart;
	return ans;
}


dg_type f_dg_void_type = (dg_type)0;

dg_type
f_dg_set_type(dg_type element_type, shape sha)
{
	dg_type ans = new_dg_type(DGT_CONS);
	ans->data.t_cons.c_key = DG_SET_T;
	ans->data.t_cons.typ = element_type;
	ans->data.t_cons.sha = sha;
	return ans;
}


dg_type
f_dg_subrange_type(dg_type rep_type, dg_bound low, dg_bound high)
{
	dg_type ans = new_dg_type(DGT_SUBR);
	ans->data.t_subr.d_key = DG_DIM_BOUNDS;
	ans->data.t_subr.low_ref = low.is_ref;
	ans->data.t_subr.hi_ref = high.is_ref;
	ans->data.t_subr.hi_cnt = 0;
	ans->data.t_subr.count = -1;
	ans->data.t_subr.d_typ = rep_type;
	ans->data.t_subr.sha = low.sha;
	ans->data.t_subr.lower = low.u;
	ans->data.t_subr.upper = high.u;
	return ans;
}


dg_type
f_dg_proc_type(dg_param_list params, dg_type result_type,
	       bool_option prototype, nat_option call_convention,
	       nat_option language, procprops_option prcprops)
{
	dg_type ans = new_dg_type(DGT_PROC);
	ans->data.t_proc.params = params;
	ans->data.t_proc.res_type = result_type;
	ans->data.t_proc.prps = prcprops;
	if (prototype.present) {
		ans->data.t_proc.knowpro = 1;
		ans->data.t_proc.yespro = prototype.val;
	} else {
		ans->data.t_proc.knowpro = 0;
	}
	if (call_convention.present) {
		ans->data.t_proc.ccv =
		    (unsigned)call_convention.val.nat_val.small_nat;
	} else {
		ans->data.t_proc.ccv = 0;
	}
	if (language.present) {
		ans->data.t_proc.lang =
		    (unsigned)language.val.nat_val.small_nat;
	} else {
		ans->data.t_proc.lang = 0;
	}
	return ans;
}


dg_type
f_dg_file_type(dg_type elem_type, shape sha)
{
	dg_type ans = new_dg_type(DGT_CONS);
	ans->data.t_cons.c_key = DG_FILE_T;
	ans->data.t_cons.typ = elem_type;
	ans->data.t_cons.sha = sha;
	return ans;
}


dg_type
f_dg_class_type(dg_class_base_list inheritance, dg_classmem_list members,
		dg_varpart_option varpart, dg_tag_list friends,
		shape_option sha, dg_tag_option vtable_static,
		dg_tag_option vtable_dynamic, dg_idname_option tagname,
		dg_sourcepos_option src_pos, bool is_union,
		dg_tag_option rtti_static, dg_tag_option rtti_dynamic,
		bool new_type, bool_option ada_derived)
{
	dg_type ans = new_dg_type(DGT_CLASS);
	ans->data.t_struct.idnam = tagname;
	ans->data.t_struct.tpos = shorten_sourcepos(src_pos);
	ans->data.t_struct.is_union = is_union;
	if (sha.present) {
		ans->data.t_struct.sha = sha.val;
	} else {
		ans->data.t_struct.sha = (shape)0;
	}
	ans->data.t_struct.u.cd = (class_data *)xmalloc(sizeof(class_data));
	if (new_type || (ada_derived.present && ada_derived.val)) {
		extend_dg_type(ans);
		ans->mor->isnew = new_type;
		if (ada_derived.present) {
			ans->mor->aderiv = ada_derived.val;
		}
	}
	ans->data.t_struct.u.cd->inherits = inheritance;
	ans->data.t_struct.u.cd->members = members;
	ans->data.t_struct.u.cd->friends = friends;
	ans->data.t_struct.u.cd->vt_s = vtable_static;
	ans->data.t_struct.u.cd->vt_d = vtable_dynamic;
	ans->data.t_struct.u.cd->rtti_s = rtti_static;
	ans->data.t_struct.u.cd->rtti_d = rtti_dynamic;
	ans->data.t_struct.vpart = varpart;
	return ans;
}


dg_type
f_dg_ptr_memdata_type(dg_tag cls, dg_type memtype, shape sha,
		      dg_tag_option pdm_type)
{
	dg_type ans = new_dg_type(DGT_PMEM);
	ans->data.t_pmem.pclass = cls;
	ans->data.t_pmem.memtyp = memtype;
	ans->data.t_pmem.sha = sha;
	UNUSED(pdm_type);
	return ans;
}


dg_type
f_dg_ptr_memfn_type(dg_tag cls, dg_type memtype, shape sha,
		    dg_tag_option pfn_type)
{
	dg_type ans = new_dg_type(DGT_PMEM);
	ans->data.t_pmem.pclass = cls;
	ans->data.t_pmem.memtyp = memtype;
	ans->data.t_pmem.sha = sha;
	UNUSED(pfn_type);
	return ans;
}


dg_type
f_dg_task_type(dg_idname idname, dg_sourcepos whence, dg_name_list entries,
	       dg_tag task_id, dg_tag tcb, dg_classmem_list members,
	       dg_varpart_option varpart, shape_option sha,
	       bool new_type, dg_tag_option elaboration)
{
	dg_type ans = new_dg_type(DGT_A_TASK);
	ans->data.t_struct.idnam = idname;
	ans->data.t_struct.tpos = shorten_sourcepos(whence);
	ans->data.t_struct.is_union = 0;
	if (sha.present) {
		ans->data.t_struct.sha = sha.val;
	} else {
		ans->data.t_struct.sha = (shape)0;
	}
	ans->data.t_struct.u.td = (task_data *)xmalloc(sizeof(task_data));
	if (new_type || elaboration) {
		extend_dg_type(ans);
		ans->mor->isnew = new_type;
		ans->mor->elabn = elaboration;
	}
	ans->data.t_struct.u.td->entries = entries;
	ans->data.t_struct.u.td->id = task_id;
	ans->data.t_struct.u.td->cb = tcb;
	ans->data.t_struct.u.td->members = members;
	ans->data.t_struct.vpart = varpart;
	return ans;
}


dg_type
f_dg_address_type(dg_idname idname, shape sha)
{
	dg_type ans = new_dg_type(DGT_BASIC);
	ans->data.t_bas.b_key = DG_ADR_T;
	ans->data.t_bas.tnam = idname_chars(idname);
	ans->data.t_bas.b_sh = sha;
	return ans;
}


dg_type
f_dg_boolean_type(dg_idname idname, variety var)
{
	dg_type ans = new_dg_type(DGT_BASIC);
	ans->data.t_bas.b_key = DG_BOOL_T;
	ans->data.t_bas.tnam = idname_chars(idname);
	ans->data.t_bas.b_sh = f_integer(var);
	return ans;
}


dg_type
f_dg_complex_float_type(dg_idname idname, floating_variety var)
{
	dg_type ans = new_dg_type(DGT_BASIC);
	ans->data.t_bas.b_key = DG_FLOAT_T;
	ans->data.t_bas.tnam = idname_chars(idname);
	ans->data.t_bas.b_sh = f_floating(var);
	return ans;
}


dg_type
f_dg_float_type(dg_idname idname, floating_variety var)
{
	dg_type ans = new_dg_type(DGT_BASIC);
	ans->data.t_bas.b_key = DG_FLOAT_T;
	ans->data.t_bas.tnam = idname_chars(idname);
	ans->data.t_bas.b_sh = f_floating(var);
	return ans;
}


dg_type
f_dg_floating_digits_type(dg_type rep_type, exp digits)
{
	dg_type ans = new_dg_type(DGT_FLDIG);
	ans->data.t_adanum.rept = rep_type;
	ans->data.t_adanum.digits = diaginfo_exp(digits);
	return ans;
}


dg_type
f_dg_fixed_point_type(dg_type rep_type, exp small, exp_option delta,
		      exp_option digits)
{
	dg_type ans = new_dg_type(DGT_FIXED);
	ans->data.t_adanum.rept = rep_type;
	ans->data.t_adanum.small = diaginfo_exp(small);
	if (delta.present) {
		ans->data.t_adanum.delta = diaginfo_exp(delta.val);
	} else {
		ans->data.t_adanum.delta = NULL;
	}
	if (digits.present) {
		ans->data.t_adanum.digits = diaginfo_exp(digits.val);
	} else {
		ans->data.t_adanum.digits = NULL;
	}
	return ans;
}


dg_type
f_dg_integer_type(dg_idname idname, variety var)
{
	dg_type ans = new_dg_type(DGT_BASIC);
	ans->data.t_bas.b_key = DG_INT_T;
	ans->data.t_bas.tnam = idname_chars(idname);
	ans->data.t_bas.b_sh = f_integer(var);
	return ans;
}


dg_type
f_dg_char_type(dg_idname idname, variety var)
{
	dg_type ans = new_dg_type(DGT_BASIC);
	ans->data.t_bas.b_key = DG_CHAR_T;
	ans->data.t_bas.tnam = idname_chars(idname);
	ans->data.t_bas.b_sh = f_integer(var);
	return ans;
}


dg_type
f_dg_inlined_type(dg_type type, dg_tag origin)
{
	if (!type->mor) {
		extend_dg_type(type);
	}
	type->mor->inline_ref = origin;
	return type;
}


dg_type
f_dg_synchronous_type(dg_idname idname, dg_sourcepos whence,
		      dg_name_list entries, dg_tag socb,
		      dg_classmem_list members, dg_varpart_option varpart,
		      shape_option sha, bool new_type,
		      dg_tag_option elaboration)
{
	dg_type ans = new_dg_type(DGT_A_SYNCH);
	ans->data.t_struct.idnam = idname;
	ans->data.t_struct.tpos = shorten_sourcepos(whence);
	ans->data.t_struct.is_union = 0;
	if (sha.present) {
		ans->data.t_struct.sha = sha.val;
	} else {
		ans->data.t_struct.sha = (shape)0;
	}
	ans->data.t_struct.u.td = (task_data *)xmalloc(sizeof(task_data));
	if (new_type || elaboration) {
		extend_dg_type(ans);
		ans->mor->isnew = new_type;
		ans->mor->elabn = elaboration;
	}
	ans->data.t_struct.u.td->entries = entries;
	ans->data.t_struct.u.td->id = (dg_tag)0;
	ans->data.t_struct.u.td->cb = socb;
	ans->data.t_struct.u.td->members = members;
	ans->data.t_struct.vpart = varpart;
	return ans;
}


dg_type
f_dg_unknown_type(shape sha)
{
	dg_type ans = new_dg_type(DGT_UNKNOWN);
	UNUSED(sha);
	return ans;
}


void
init_dg_type(void)
{
	return;
}


dg_class_base f_dummy_dg_class_base;

dg_class_base
f_make_dg_class_base(dg_tag base, dg_sourcepos_option whence,
		     token_option location,
		     dg_accessibility_option accessibility,
		     dg_virtuality_option virtuality)
{
	dg_class_base ans;
	ans.base = base;
	ans.pos = shorten_sourcepos(whence);
	if (location.present) {
		shape ptr_sh = f_pointer(f_alignment(ulongsh));
		ans.location = relative_exp(ptr_sh, location.val);
	} else {
		ans.location = NULL;
	}
	ans.acc = accessibility;
	ans.virt = virtuality;
	return ans;
}


void
init_dg_class_base(void)
{
	return;
}


dg_classmem f_dummy_dg_classmem;

dg_classmem
f_dg_tag_classmem(dg_tag tg, dg_classmem mem)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_CLASSMEM;
	mem.tg = tg;
	return mem;
}


dg_classmem
f_dg_field_classmem(dg_idname idname, dg_sourcepos src_pos, exp offset,
		    dg_type field_type, dg_accessibility_option accessibility,
		    bool_option discr, dg_default_option deflt)
{
	int is_discr = 0;
	dg_classmem ans;
	ans.cm_key = DG_CM_FIELD;
	ans.d.cm_f.fnam = idname_chars(idname);
	ans.d.cm_f.f_pos = shorten_sourcepos(src_pos);
	ans.d.cm_f.f_typ = field_type;
	ans.d.cm_f.f_offset = diaginfo_exp(offset);
	ans.d.cm_f.acc = accessibility;
	if (discr.present) {
		is_discr = discr.val;
	}
	ans.d.cm_f.discr = is_discr;
	ans.d.cm_f.dflt = deflt;
	ans.tg = (dg_tag)0;
	return ans;
}


dg_classmem
f_dg_function_classmem(dg_name fn, exp_option vtable_slot)
{
	dg_classmem ans;
	ans.cm_key = DG_CM_FN;
	ans.d.cm_fn.fn = fn;
	if (vtable_slot.present) {
		ans.d.cm_fn.slot = diaginfo_exp(vtable_slot.val);
	} else {
		ans.d.cm_fn.slot = NULL;
	}
	ans.tg = (dg_tag)0;
	return ans;
}


dg_classmem
f_dg_indirect_classmem(dg_idname idname, dg_sourcepos src_pos, token location,
		       dg_type cmem_type)
{
	dg_classmem ans;
	ans.cm_key = DG_CM_INDIRECT;
	ans.d.cm_ind.nam = idname_chars(idname);
	ans.d.cm_ind.pos = shorten_sourcepos(src_pos);
	ans.d.cm_ind.typ = cmem_type;
	ans.d.cm_ind.ind_loc = relative_exp(f_pointer(f_alignment(ulongsh)),
					    location);
	ans.tg = (dg_tag)0;
	return ans;
}


dg_classmem
f_dg_name_classmem(dg_name nam)
{
	dg_classmem ans;
	ans.cm_key = DG_CM_STAT;
	ans.d.cm_stat = nam;
	ans.tg = (dg_tag)0;
	return ans;
}


void
init_dg_classmem(void)
{
	return;
}


dg_qualifier f_dummy_dg_qualifier;

dg_qualifier f_dg_const_qualifier = DG_CONST_T;

dg_qualifier f_dg_volatile_qualifier = DG_VOL_T;

dg_qualifier f_dg_aliased_qualifier = DG_ALIAS_T;

dg_qualifier f_dg_class_wide_qualifier = DG_CLWID_T;

dg_qualifier f_dg_limited_qualifier = DG_LIM_T;

void
init_dg_qualifier(void)
{
	return;
}


dg_bound f_dummy_dg_bound;

dg_bound
f_dg_dynamic_bound(dg_tag bound, shape sha)
{
	dg_bound ans;
	ans.is_ref = 1;
	ans.u.tg = bound;
	ans.sha = sha;
	return ans;
}


dg_bound
f_dg_static_bound(exp bound)
{
	dg_bound ans;
	if (name(bound) != val_tag) {
		failer("not a constant");
	}
	ans.is_ref = 0;
	ans.u.x = diaginfo_exp(bound);
	ans.sha = sh(bound);
	return ans;
}


dg_bound
f_dg_unknown_bound(shape sha)
{
	dg_bound ans;
	ans.is_ref = 1;
	ans.u.tg = (dg_tag)0;
	ans.sha = sha;
	return ans;
}


void
init_dg_bound(void)
{
	return;
}


dg_dim f_dummy_dg_dim;

dg_dim
f_dg_dim_apply_token(token token_value, bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DG_DIM_SORT, (tokval *)0);
	return v.tk_dg_dim;
}


dg_dim
f_dg_tag_dim(dg_tag tg, dg_dim d)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_DIM;
	d.tg = tg;
	return d;
}


dg_dim
f_dg_bounds_dim(dg_bound low, dg_bound high, dg_type index_type)
{
	dg_dim ans;
	ans.d_key = DG_DIM_BOUNDS;
	ans.low_ref = low.is_ref;
	ans.hi_ref = high.is_ref;
	ans.hi_cnt = 0;
	ans.d_typ = index_type;
	ans.sha = low.sha;
	ans.lower = low.u;
	ans.upper = high.u;
	if (low.is_ref || high.is_ref) {
		ans.count = -1;
	} else {
		ans.count = (long)(no(son(high.u.x)) - no(son(low.u.x)) + 1);
	}
	ans.tg = (dg_tag)0;
	return ans;
}


dg_dim
f_dg_count_dim(dg_bound low, dg_bound count, dg_type index_type)
{
	dg_dim ans;
	ans.d_key = DG_DIM_BOUNDS;
	ans.low_ref = low.is_ref;
	ans.hi_ref = count.is_ref;
	ans.hi_cnt = 1;
	ans.d_typ = index_type;
	ans.sha = low.sha;
	ans.lower = low.u;
	ans.upper = count.u;
	if (count.is_ref) {
		ans.count = -1;
	} else {
		ans.count = (long)(no(son(count.u.x)));
	}
	ans.tg = (dg_tag)0;
	return ans;
}


dg_dim
f_dg_type_dim(dg_type type, nat_option n)
{
	dg_dim ans;
	ans.d_key = DG_DIM_TYPE;
	ans.d_typ = type;
	if (n.present) {
		ans.count = (long)n.val.nat_val.small_nat;
	} else {
		ans.count = -1;
	}
	ans.tg = (dg_tag)0;
	return ans;
}


dg_dim f_dg_unspecified_dim;

void
init_dg_dim(void)
{
	f_dg_unspecified_dim.d_key = DG_DIM_NONE;
	f_dg_unspecified_dim.low_ref = f_dg_unspecified_dim.hi_ref = 1;
	f_dg_unspecified_dim.hi_cnt = 0;
	f_dg_unspecified_dim.count = -1;
	f_dg_unspecified_dim.d_typ = (dg_type)0;
	f_dg_unspecified_dim.sha = f_top;
	f_dg_unspecified_dim.lower.tg = f_dg_unspecified_dim.upper.tg =
	    (dg_tag)0;
	f_dg_unspecified_dim.tg = (dg_tag)0;
	return;
}


dg_enum f_dummy_dg_enum;

dg_enum
f_make_dg_enum(exp value, dg_idname idname, dg_sourcepos src_pos)
{
	dg_enum ans;
	if (!value || name(value) != val_tag) {
		failer("enum value not const");
	}
	ans.enam = idname_chars(idname);
	ans.pos = shorten_sourcepos(src_pos);
	ans.value = diaginfo_exp(value);
	ans.is_chn = 0;
	ans.tg = (dg_tag)0;
	return ans;
}


dg_enum
f_dg_char_enum(exp value, nat idchar, dg_sourcepos src_pos)
{
	dg_enum ans;
	if (!value || name(value) != val_tag) {
		failer("enum value not const");
	}
	ans.chn = idchar.nat_val.small_nat;
	ans.pos = shorten_sourcepos(src_pos);
	ans.value = diaginfo_exp(value);
	ans.is_chn = 1;
	ans.tg = (dg_tag)0;
	return ans;
}


dg_enum
f_dg_tag_enum(dg_tag tg, dg_enum e)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_ENUM;
	e.tg = tg;
	return e;
}


void
init_dg_enum(void)
{
	return;
}

dg_param f_dummy_dg_param;

dg_param
f_dg_object_param(dg_idname_option idname, dg_sourcepos_option src_pos,
		  dg_param_mode_option mode, dg_type param_type,
		  dg_default_option deflt)
{
	dg_param ans;
	ans.pnam = idname_chars(idname);
	ans.ppos = shorten_sourcepos(src_pos);
	ans.pmode = mode;
	ans.p_typ = param_type;
	ans.p_dflt = deflt;
	return ans;
}


dg_param
f_dg_type_param(dg_idname_option idname, dg_sourcepos_option src_pos,
		dg_param_list fparams)
{
	failer("dg_type_param not yet supported");
	UNUSED(idname);
	UNUSED(src_pos);
	UNUSED(fparams);
	return f_dummy_dg_param;
}


void
init_dg_param(void)
{
	return;
}

dg_param_mode f_dummy_dg_param_mode;

dg_param_mode f_dg_in_mode = DG_IN_MODE;

dg_param_mode f_dg_out_mode = DG_OUT_MODE;

dg_param_mode f_dg_inout_mode = DG_INOUT_MODE;


void
init_dg_param_mode(void)
{
	return;
}

dg_accessibility f_dummy_dg_accessibility;

dg_accessibility f_dg_public_accessibility = DG_ACC_PUB;

dg_accessibility f_dg_private_accessibility = DG_ACC_PRIV;

dg_accessibility f_dg_protected_accessibility = DG_ACC_PROT;

dg_accessibility f_dg_local_accessibility = DG_ACC_LOC;


void
init_dg_accessibility(void)
{
	return;
}

dg_virtuality f_dummy_dg_virtuality;

dg_virtuality f_dg_virtual_virtuality = DG_VIRT_VIRT;

dg_virtuality f_dg_abstract_virtuality = DG_VIRT_PURE;


void
init_dg_virtuality(void)
{
	return;
}


dg_filename f_dummy_dg_filename;

dg_filename
f_dg_filename_apply_token(token token_value, bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DG_FILENAME_SORT, (tokval *)0);
	return v.tk_dg_filename;
}


dg_filename
f_make_dg_filename(nat date, string machine, string path, string file)
{
	return get_filename((long)(date.nat_val.small_nat), machine.ints.chars,
			    path.ints.chars, file.ints.chars);
}


void
init_dg_filename(void)
{
	return;
}


dg_sourcepos f_dummy_dg_sourcepos;

dg_sourcepos f_dg_span_sourcepos(dg_filename file, nat from_line,
				 nat from_column, dg_filename_option to_file,
				 nat to_line, nat to_column)
{
	dg_sourcepos ans;
	ans.sp_key = SP_SPAN;
	ans.file = file;
	if (!(ans.to_file = to_file)) {
		ans.to_file = file;
	}
	ans.from_line = from_line.nat_val.small_nat;
	ans.from_column = (short)from_column.nat_val.small_nat;
	ans.to_line = to_line.nat_val.small_nat;
	ans.to_column = (short)to_column.nat_val.small_nat;
	return ans;
}


dg_sourcepos
f_dg_mark_sourcepos(dg_filename file, nat line, nat column)
{
	dg_sourcepos ans;
	ans.sp_key = SP_SHORT;
	ans.file = file;
	ans.from_line = line.nat_val.small_nat;
	ans.from_column = (short)column.nat_val.small_nat;
	return ans;
}


dg_sourcepos
f_dg_file_sourcepos(dg_filename file)
{
	dg_sourcepos ans;
	ans.sp_key = SP_FILE;
	ans.file = file;
	return ans;
}


dg_sourcepos f_dg_global_sourcepos;

dg_sourcepos f_dg_null_sourcepos;

void
init_dg_sourcepos(void)
{
	f_dg_global_sourcepos.sp_key = SP_GLOB;
	f_dg_null_sourcepos.sp_key = SP_NULL;
	return;
}


dg_compilation f_dummy_dg_compilation;

dg_compilation
f_dg_tag_compilation(dg_tag tg, dg_compilation comp)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_COMP;
	tg->p.comp = comp;
	return comp;
}


dg_compilation
f_make_dg_compilation(dg_filename primary_file, string_list comp_unit_deps,
		      dg_macro_list macros, dg_filename comp_dir, nat date,
		      nat language, nat id_case, string producer,
		      string_list options, dg_namelist dnames)
{
	dg_compilation ans = (dg_compilation)xmalloc(sizeof(struct dg_comp_t));
	ans->prim_file = primary_file;
	ans->comp_deps = comp_unit_deps;
	ans->date = date.nat_val.small_nat;
	ans->language = language.nat_val.small_nat;
	ans->id_case = id_case.nat_val.small_nat;
	ans->producer = producer.ints.chars;
	ans->comp_dir = comp_dir;
	ans->options = options;
	ans->dn_list = dnames.list;
	if (dnames.tg) {
		dnames.tg->p.nl = &(ans->dn_list);
	}
	ans->another = (dg_compilation)0;
	ans->macros = macros;
	return ans;
}


void
init_dg_compilation(void)
{
	return;
}


dg_constraint f_dummy_dg_constraint;

dg_constraint
f_dg_type_constraint(dg_tag_option ref_member, dg_type type)
{
	dg_constraint ans = (dg_constraint)xcalloc(1, sizeof(struct dg_con));
	ans->refmem = ref_member;
	ans->is_val = 0;
	ans->u.typ = type;
	ans->next = (dg_constraint)0;
	return ans;
}


dg_constraint
f_dg_value_constraint(dg_tag_option ref_member, exp value)
{
	dg_constraint ans = (dg_constraint)xcalloc(1, sizeof(struct dg_con));
	ans->refmem = ref_member;
	ans->is_val = 1;
	ans->u.val = value;
	ans->next = (dg_constraint)0;
	return ans;
}


void
init_dg_constraint(void)
{
	return;
}


dg_default f_dummy_dg_default;

dg_default
f_make_dg_default(exp_option value, dg_sourcepos_option src_span)
{
	dg_default ans;
	if (value.present) {
		ans.val = diaginfo_exp(value.val);
	} else {
		ans.val = NULL;
	}
	ans.span = src_span;
	ans.lab = (long)0;
	return ans;
}


void
init_dg_default(void)
{
	return;
}


dg_idname f_dummy_dg_idname;

dg_idname
f_dg_idname_apply_token(token token_value, bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DG_IDNAME_SORT, (tokval *)0);
	return v.tk_dg_idname;
}


dg_idname
f_dg_sourcestring_idname(string src_name)
{
	dg_idname ans;
	ans.id_key = DG_ID_SRC;
	ans.idd.nam = src_name.ints.chars;
	return ans;
}


dg_idname
f_dg_anonymous_idname(string_option descr)
{
	dg_idname ans;
	ans.id_key = DG_ID_ANON;
	UNUSED(descr);
	ans.idd.nam = "";
	return ans;
}


dg_idname
f_dg_artificial_idname(string_option aname)
{
	dg_idname ans;
	ans.id_key = DG_ID_ARTFL;
	if (aname.present) {
		ans.idd.nam = aname.val.ints.chars;
	} else {
		ans.idd.nam = "";
	}
	return ans;
}


dg_idname
f_dg_instance_idname(dg_idname_option idname, dg_idname spec,
		     dg_sourcepos whence, dg_name_list aparams)
{
	dg_idname ans;
	ans.id_key = DG_ID_INST;
	ans.idd.instance = (dg_instantn *)xcalloc(1, sizeof(dg_instantn));
	ans.idd.instance->nam = idname;
	ans.idd.instance->spec = spec;
	ans.idd.instance->whence = shorten_sourcepos(whence);
	ans.idd.instance->params = aparams;
	if (ans.idd.instance->nam.id_key == DG_ID_INST ||
	    ans.idd.instance->spec.id_key == DG_ID_INST) {
		failer("multiple instantiation");
	}
	return ans;
}


dg_idname
f_dg_external_idname(string src_name)
{
	dg_idname ans;
	ans.id_key = DG_ID_EXT;
	ans.idd.nam = src_name.ints.chars;
	return ans;
}


void
init_dg_idname(void)
{
	return;
}


dg_varpart f_dummy_dg_varpart;

dg_varpart
f_dg_discrim_varpart(dg_classmem discrim, dg_variant_list variants)
{
	dg_varpart ans;
	ans.v_key = DG_V_D;
	ans.u.d = discrim;
	ans.vnts = variants;
	return ans;
}


dg_varpart
f_dg_sibl_discrim_varpart(dg_tag discrim, dg_variant_list variants)
{
	dg_varpart ans;
	ans.v_key = DG_V_S;
	ans.u.s = discrim;
	ans.vnts = variants;
	return ans;
}


dg_varpart
f_dg_undiscrim_varpart(dg_type tag_type, dg_variant_list variants)
{
	dg_varpart ans;
	ans.v_key = DG_V_T;
	ans.u.t = tag_type;
	ans.vnts = variants;
	return ans;
}


void
init_dg_varpart(void)
{
	return;
}


dg_variant f_dummy_dg_variant;

dg_variant
f_make_dg_variant(dg_discrim_list discr, dg_classmem_list fields)
{
	dg_variant ans;
	ans.discr = discr;
	ans.fields = fields;
	return ans;
}


void
init_dg_variant(void)
{
	return;
}


dg_discrim f_dummy_dg_discrim;

dg_discrim
f_make_dg_discrim(exp lower, exp upper)
{
	dg_discrim ans;
	if (name(lower) != val_tag || name(upper) != val_tag ||
	    sh(lower) != sh(upper)) {
		failer("malformed discriminant");
	}
	ans.lower = diaginfo_exp(lower);
	ans.upper = diaginfo_exp(upper);
	return ans;
}


void
init_dg_discrim(void)
{
	return;
}


dg_macro f_dummy_dg_macro;

dg_macro
f_dg_function_macro(dg_sourcepos src_pos, dg_idname idname,
		    dg_idname_list param, string def)
{
	dg_macro ans;
	ans.key = DGM_FN;
	ans.pos = shorten_sourcepos(src_pos);
	ans.u.d.nam = idname_chars(idname);
	ans.u.d.defn = def.ints.chars;
	ans.u.d.pms = param;
	return ans;
}


dg_macro
f_dg_include_macro(dg_sourcepos src_pos, dg_filename file, dg_macro_list macros)
{
	dg_macro ans;
	ans.key = DGM_INC;
	ans.pos = shorten_sourcepos(src_pos);
	ans.u.i.file = file;
	ans.u.i.macs = macros;
	return ans;
}


dg_macro
f_dg_object_macro(dg_sourcepos src_pos, dg_idname idname, string def)
{
	dg_macro ans;
	ans.key = DGM_OBJ;
	ans.pos = shorten_sourcepos(src_pos);
	ans.u.d.nam = idname_chars(idname);
	ans.u.d.defn = def.ints.chars;
	return ans;
}


dg_macro
f_dg_undef_macro(dg_sourcepos src_pos, dg_idname idname)
{
	dg_macro ans;
	ans.key = DGM_UNDEF;
	ans.pos = shorten_sourcepos(src_pos);
	ans.u.d.nam = idname_chars(idname);
	return ans;
}


void
init_dg_macro(void)
{
	return;
}


dg_list
new_dg_list(int n)
{
	UNUSED(n);
	return (dg_list) 0;
}


dg_list
add_dg_list(dg_list list, dg elem, int index)
{
	if (elem && elem->more == elem) {	/* self ref => copy */
		dg ans = new_dg_info(elem->key);
		elem = ans;
	}
	if (list) {
		dg x = list;
		while (x->more) {
			x = x->more;
		}
		x->more = elem;
		return list;
	}
	return elem;
}


dg_name_list
new_dg_name_list(int n)
{
	return (dg_name) 0;
}


dg_name_list
add_dg_name_list(dg_name_list list, dg_name elem, int index)
{
	if (list) {
		dg_name x = list;
		while (x->next) {
			x = x->next;
		}
		x->next = elem;
		return list;
	}
	return elem;
}


dg_tag_list
new_dg_tag_list(int n)
{
	dg_tag_list ans;
	ans.len = n;
	ans.array = (dg_tag *)dg_xcalloc(n, sizeof(dg_tag));
	return ans;
}


dg_tag_list
add_dg_tag_list(dg_tag_list list, dg_tag elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_type_list
new_dg_type_list(int n)
{
	dg_type_list ans;
	ans.len = n;
	ans.array = (dg_type *)dg_xcalloc(n, sizeof(dg_type));
	return ans;
}


dg_type_list
add_dg_type_list(dg_type_list list, dg_type elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_param_list
new_dg_param_list(int n)
{
	dg_param_list ans;
	ans.len = n;
	ans.array = (dg_param *)dg_xcalloc(n, sizeof(dg_param));
	return ans;
}


dg_param_list
add_dg_param_list(dg_param_list list, dg_param elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_dim_list
new_dg_dim_list(int n)
{
	dg_dim_list ans;
	ans.len = n;
	ans.array = (dg_dim *)dg_xcalloc(n, sizeof(dg_dim));
	return ans;
}


dg_dim_list
add_dg_dim_list(dg_dim_list list, dg_dim elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_enum_list
new_dg_enum_list(int n)
{
	dg_enum_list ans;
	ans.len = n;
	ans.array = (dg_enum *)dg_xcalloc(n, sizeof(dg_enum));
	return ans;
}


dg_enum_list
add_dg_enum_list(dg_enum_list list, dg_enum elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_class_base_list
new_dg_class_base_list(int n)
{
	dg_class_base_list ans;
	ans.len = n;
	ans.array = (dg_class_base *)dg_xcalloc(n, sizeof(dg_class_base));
	return ans;
}


dg_class_base_list
add_dg_class_base_list(dg_class_base_list list, dg_class_base elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_classmem_list
new_dg_classmem_list(int n)
{
	dg_classmem_list ans;
	ans.len = n;
	ans.array = (dg_classmem *)dg_xcalloc(n, sizeof(dg_classmem));
	return ans;
}


dg_classmem_list
add_dg_classmem_list(dg_classmem_list list, dg_classmem elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_variant_list
new_dg_variant_list(int n)
{
	dg_variant_list ans;
	ans.len = n;
	ans.array = (dg_variant *)dg_xcalloc(n, sizeof(dg_variant));
	return ans;
}


dg_variant_list
add_dg_variant_list(dg_variant_list list, dg_variant elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_discrim_list
new_dg_discrim_list(int n)
{
	dg_discrim_list ans;
	ans.len = n;
	ans.array = (dg_discrim *)dg_xcalloc(n, sizeof(dg_discrim));
	return ans;
}


dg_discrim_list
add_dg_discrim_list(dg_discrim_list list, dg_discrim elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_constraint_list
new_dg_constraint_list(int n)
{
	return (dg_constraint) 0;
}


dg_constraint_list
add_dg_constraint_list(dg_constraint_list list, dg_constraint elem, int index)
{
	if (list) {
		dg_constraint x = list;
		while (x->next) {
			x = x->next;
		}
		x->next = elem;
		return list;
	}
	return elem;
}


dg_namelist f_dummy_dg_namelist;

dg_namelist
f_make_dg_namelist(dg_name_list items)
{
	dg_namelist ans;
	ans.list = items;
	ans.tg = (dg_tag)0;
	return ans;
}


dg_namelist
f_dg_tag_namelist(dg_tag tg, dg_namelist nl)
{
	if (tg->key) {
		failer("dg_tag defined twice");
	}
	tg->key = DGK_NAMELIST;
	nl.tg = tg;
	return nl;
}


void
init_dg_namelist(void)
{
	return;
}


dg_append f_dummy_dg_append;

dg_append
f_dg_name_append(dg_tag tg, dg_name nam)
{
	if (tg->key != DGK_NAMELIST) {
		failer("wrong dg_tag");
	}
	*(tg->p.nl) = add_dg_name_list(*(tg->p.nl), nam, 0);
	return f_dummy_dg_append;
}


void
init_dg_append(void)
{
	return;
}


dg_append_list
new_dg_append_list(int n)
{
	return (dg_append_list) 0;
}


dg_append_list
add_dg_append_list(dg_append_list list, dg_append elem, int index)
{
	return list;
}


dg_macro_list
new_dg_macro_list(int n)
{
	dg_macro_list ans;
	ans.len = n;
	ans.array = (dg_macro *)dg_xcalloc(n, sizeof(dg_macro));
	return ans;
}


dg_macro_list
add_dg_macro_list(dg_macro_list list, dg_macro elem, int index)
{
	list.array[index] = elem;
	return list;
}


dg_idname_list
new_dg_idname_list(int n)
{
	return new_string_list(n);
}


dg_idname_list
add_dg_idname_list(dg_idname_list list, dg_idname elem, int index)
{
	list.array[index] = idname_chars(elem);
	return list;
}


dg_idname_option no_dg_idname_option;

dg_idname_option
yes_dg_idname_option(dg_idname elem)
{
	return elem;
}


void
init_dg_idname_option(void)
{
	no_dg_idname_option.id_key = DG_ID_NONE;
	no_dg_idname_option.idd.nam = "";
	return;
}


dg_name_option no_dg_name_option = (dg_name)0;

dg_name_option
yes_dg_name_option(dg_name elem)
{
	return elem;
}


void
init_dg_name_option(void)
{
	return;
}


dg_accessibility_option no_dg_accessibility_option = DG_ACC_NONE;

dg_accessibility_option
yes_dg_accessibility_option(dg_accessibility elem)
{
	return elem;
}


void
init_dg_accessibility_option(void)
{
	return;
}


dg_tag_option no_dg_tag_option = (dg_tag)0;

dg_tag_option
yes_dg_tag_option(dg_tag elem)
{
	return elem;
}


void
init_dg_tag_option(void)
{
	return;
}


dg_virtuality_option no_dg_virtuality_option = DG_VIRT_NONE;

dg_virtuality_option
yes_dg_virtuality_option(dg_virtuality elem)
{
	return elem;
}


void
init_dg_virtuality_option(void)
{
	return;
}


dg_sourcepos_option no_dg_sourcepos_option;

dg_sourcepos_option
yes_dg_sourcepos_option(dg_sourcepos elem)
{
	return elem;
}


void
init_dg_sourcepos_option(void)
{
	no_dg_sourcepos_option.sp_key = SP_NULL;
	no_short_sourcepos = shorten_sourcepos(no_dg_sourcepos_option);
	return;
}


dg_type_option no_dg_type_option = (dg_type)0;

dg_type_option
yes_dg_type_option(dg_type elem)
{
	return elem;
}


void
init_dg_type_option(void)
{
	return;
}


dg_type_list_option no_dg_type_list_option;

dg_type_list_option
yes_dg_type_list_option(dg_type_list elem)
{
	return elem;
}


void
init_dg_type_list_option(void)
{
	no_dg_type_list_option.len = -1;
	no_dg_type_list_option.array = (dg_type *)0;
	return;
}


dg_constraint_list_option no_dg_constraint_list_option = (dg_constraint)0;

dg_constraint_list_option
yes_dg_constraint_list_option(dg_constraint_list elem)
{
	return elem;
}


void
init_dg_constraint_list_option(void)
{
	return;
}


dg_varpart_option no_dg_varpart_option = (dg_varpart_option)0;

dg_varpart_option
yes_dg_varpart_option(dg_varpart elem)
{
	dg_varpart_option ans =
	    (dg_varpart_option)xcalloc(1, sizeof(dg_varpart));
	*ans = elem;
	return ans;
}


void
init_dg_varpart_option(void)
{
	return;
}


dg_param_mode_option no_dg_param_mode_option = DG_NO_MODE;

dg_param_mode_option
yes_dg_param_mode_option(dg_param_mode elem)
{
	return elem;
}


void
init_dg_param_mode_option(void)
{
	return;
}


dg_dim_option no_dg_dim_option;

dg_dim_option
yes_dg_dim_option(dg_dim elem)
{
	failer("dg_dim_option not done yet");
	return no_dg_dim_option;
}


void
init_dg_dim_option(void)
{
	return;
}


dg_filename_option no_dg_filename_option = (dg_filename)0;

dg_filename_option
yes_dg_filename_option(dg_filename elem)
{
	return elem;
}


void
init_dg_filename_option(void)
{
	return;
}


dg_default_option no_dg_default_option = (dg_default *)0;

dg_default_option
yes_dg_default_option(dg_default elem)
{
	dg_default_option ans =
	    (dg_default_option)xcalloc(1, sizeof(dg_default));
	*ans = elem;
	return ans;
}


void
init_dg_default_option(void)
{
	return;
}


void
init_capsule_dgtags(void)
{
	/* the space has been calloced in read_fns */

	int i;
	for (i = 0; i < capsule_no_of_dgtags; ++i) {
		init_dgtag(&capsule_dgtab[i]);
	}
	return;
}


void
init_unit_dgtags(int n)
{

	int i;

	unit_dgtagtab = (dgtag_struct *)dg_xcalloc(unit_no_of_dgtags - n,
						sizeof(dgtag_struct));

	for (i = 0; i < unit_no_of_dgtags - n; ++i) {
		init_dgtag(&unit_dgtagtab[i]);
	}
	return;
}


void
start_make_dg_comp_unit(int toks, int tags, int als, int dgnames)
{
	int i;

	unit_no_of_tokens = toks;
	unit_ind_tokens = (tok_define **)dg_xcalloc(unit_no_of_tokens,
						 sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i) {
		unit_ind_tokens[i] = (tok_define *)0;
	}

	unit_no_of_tags = tags;
	unit_ind_tags = (dec **)dg_xcalloc(unit_no_of_tags, sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i) {
		unit_ind_tags[i] = (dec *)0;
	}

	unit_no_of_als = als;
	unit_ind_als = (aldef **)dg_xcalloc(unit_no_of_als, sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i) {
		unit_ind_als[i] = (aldef *)0;
	}

	unit_no_of_dgtags = dgnames;
	unit_ind_dgtags = (dgtag_struct **)dg_xcalloc(unit_no_of_dgtags,
						   sizeof(dgtag_struct *));
	for (i = 0; i < unit_no_of_dgtags; ++i) {
		unit_ind_dgtags[i] = (dgtag_struct *)0;
	}

	return;
}


void
f_make_dg_comp_unit(void)
{
	int i;
	int j = 0;
	int no_of_labels;

	for (i = 0; i < unit_no_of_tokens; ++i) {
		if (unit_ind_tokens[i] == (tok_define *)0) {
			unit_ind_tokens[i] = &unit_toktab[j++];
		}
	}

	j = 0;
	for (i = 0; i < unit_no_of_tags; ++i) {
		if (unit_ind_tags[i] == (dec *)0) {
			unit_ind_tags[i] = &unit_tagtab[j++];
		}
	}

	j = 0;
	for (i = 0; i < unit_no_of_als; ++i) {
		if (unit_ind_als[i] == (aldef *)0)
			unit_ind_als[i] = &unit_altab[j++];
	}

	j=0;
	for (i = 0; i < unit_no_of_dgtags; ++i) {
		if (unit_ind_dgtags[i] == (dgtag_struct *)0) {
			unit_ind_dgtags[i] = &unit_dgtagtab[j++];
		}
	}

	{
		dg_compilation *comp_unit_ptr = &all_comp_units;
		while (*comp_unit_ptr) {
			comp_unit_ptr = &(*comp_unit_ptr)->another;
		}
		start_bytestream();
		no_of_labels = small_dtdfint();
		unit_no_of_labels = no_of_labels;
		unit_labtab = (exp *)dg_xcalloc(unit_no_of_labels, sizeof(exp));
		(*comp_unit_ptr) = d_dg_compilation();
		IGNORE d_dg_append_list();
		end_bytestream();
	}

	return;
}


void
f_make_dglink(tdfint i, tdfint ext)
{
	unit_ind_dgtags[natint(i)] = &capsule_dgtab[natint(ext)];
	return;
}


linkextern
f_make_dgtagextern(tdfint internal, external ext)
{
	dg_tag tg = &capsule_dgtab[natint(internal)];
	tg->outref.k = LAB_STR;
	tg->outref.u.s = external_to_string(ext);
	return 0;
}


exp
f_dg_exp(exp body, dg diagnostic)
{
	return body;
}


exp
read_dg_exp(exp body)
{
	dg diag;

	return NULL;
}
