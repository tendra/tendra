/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/dw2_config.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <flpt/flpt.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#ifdef TDF_DIAG3
#include <diag3/dg_aux.h>
#include <diag3/diagglob.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/dg_aux.h>
#include <diag4/diagglob.h>
#endif

#include <dwarf2/dw2_entries.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_types.h>
#include <dwarf2/dw2_lines.h>
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_locdata.h>



long dw2_scope_start = 0;
long dw2_scope_end = 0;
bool dw_doing_branch_tests = false;

static long local_var_place;
static bool doing_abstract = false;
static bool doing_inline   = false; /* consistency check only */
static dg_info proc_dg_info = NULL;
static dg_type return_type = NULL;

static dg_default * default_span_list = NULL;

static void fail_unimplemented
(void)
{
  error(ERR_INTERNAL, "unimplemented attribute");
}

static exp find_id
    ( exp e )
{
  if (e->tag == name_tag && !isdiscarded(e) && !isvar(son(e)))
    return son(e);
  if (e->tag == cont_tag && son(e)->tag == name_tag && !isdiscarded(son(e))
		&& ( isvar(son(son(e))) || isparam(son(son(e))) ))
    return son(son(e));
  return NULL;
}


void dw_out_const
    ( exp e )
{
  switch (e->tag) {
    case real_tag: {
      int sw = (shape_size(sh(e)) <= 32 ? 0 : 1);
				/* DWARF cannot represent extended reals */
      r2l real_parts;
      real_parts = real2longs_IEEE (&flptnos[no(e)], sw);
      dw_at_form ((sw ? DW_FORM_data8 : DW_FORM_data4));
      asm_printf("\n");
      dw_at_data (4, (long)(real_parts.i1));
      if (sw)
	dw_at_data (4, (long)(real_parts.i2));
      break;
    }
    case val_tag:
    case null_tag: {
      if (isbigval(e)) {
	flt64 x;
	int ov;
	x = flt_to_f64(no(e), is_signed(sh(e)), &ov);
	dw_at_form (DW_FORM_data8); asm_printf("\n");
	dw_at_data (4, (long)(x.small));
	dw_at_data (4, (long)(x.big));
      }
      else
      if (is_signed(sh(e))) {
	dw_at_form (DW_FORM_sdata); asm_printf(", ");
	sleb128 ((long)no(e)); asm_printf("\n");
      }
      else {
	dw_at_form (DW_FORM_udata); asm_printf(", ");
	uleb128 ((unsigned long)no(e)); asm_printf("\n");
      }
      break;
    }
    default: {
      dw_at_form (DW_FORM_block1); asm_printf("\n");
      dw2_locate_exp (e, 1, 0);
    }
  }
}


void dw_out_default
    ( dg_default * d )
{
  if (d->val && dw_is_const (son(d->val)))
    dw_out_const (son(d->val));
  else
  if (d->span.sp_key != SP_SPAN) {
    dw_at_form (DW_FORM_flag); asm_printf("\n");
    dw_at_flag (1);
  }
  else {
    if (!d->lab) {
      d->lab = next_dwarf_label ();
      d->next = default_span_list;
      default_span_list = d;
    }
    dw_at_form (DW_FORM_ref_addr); asm_printf("\n");
    dw_at_address (d->lab);
  }
}


void complete_defaults
(void)
{
  while (default_span_list) {
    out_dwf_label (default_span_list->lab, 1);
    IGNORE dw_entry (dwe_span, 0);
    IGNORE dw_entry (dwe_span_strt, 0);
    dw_at_decl (shorten_sourcepos (default_span_list->span));
    IGNORE dw_entry (dwe_span_end, 0);
    dw_at_decl (end_sourcepos (default_span_list->span));
    dw_sibling_end ();
    default_span_list = default_span_list->next;
  }
}


static void out_refblock		/* Not certain this is needed! */
    ( objset * objs , int assgn )
{
  int count = 0;
  long over_lab;
  objset * p = objs;
  while (p) {
    if (p->ass == assgn)
      count++;
    p = p->next;
  }
  out16();
  if (needs_debug_align && count) {
    over_lab = next_dwarf_label();
    out_dwf_label (over_lab, 0);
    asm_printf(" - . - 2");
  }
  else
    asm_printf("%d", count * 4);
  asm_printf("\n");
  if (count) {
    p = objs;
    while (p) {
      if (p->ass == assgn)
	dw_at_ext_address (p->tag);
      p = p->next;
    }
    if (needs_debug_align) {
      out_dwf_label (over_lab, 1);
    }
  }
}


static void check_trivial
    ( exp e )
{
	UNUSED(e);

#if 0
	/* This is still far too strong; e may be anything with equivalent
		already in a register! */
  if (e && e->tag != val_tag && e->tag != name_tag &&
	(e->tag != cont_tag || son(e)->tag != name_tag) &&
	e->tag != goto_tag && e->tag != top_tag ) {
    if (e->tag == chvar_tag || e->tag == chfl_tag)
      check_trivial (son(e));
    else
      error(ERR_INTERNAL, "lost information?");
  }
#endif
}

static void output_detch (detch_info *	dl);

static detch_info * sub_detch = NULL;


static void output_info
    ( exp e , dg_info d )
{
  /* within info section */
  if (!d) {
    exp t;
    if (!e) {
      if (sub_detch)
	output_detch (sub_detch);
      return;
    }
    if (e->tag == name_tag || e->tag == env_size_tag || 
	e->tag == env_offset_tag || (t = son(e), !t))
      return;
    for (;;) {
      output_info (t, dgf(t));
      if (t->last || e->tag == case_tag) return;
      t = bro(t);
    }
  }

  switch (d->key) {

    case DGA_COMP: {
      if (!(d->data.i_comp.lo_pc)) {	/* optimised away */
	check_trivial (e);
	output_info (e, d->more);
	break;
      }
      if (d->data.i_comp.is_tag) {
	IGNORE dw_entry (dwe_for_unit, 0);
	dw_at_address (d->data.i_comp.lo_pc);
	dw_at_address (d->data.i_comp.hi_pc);
	dw_at_ext_address (d->data.i_comp.corl.comp_tag);
      }
      else {
	IGNORE dw_entry (dwe_for_lang, 0);
	dw_at_address (d->data.i_comp.lo_pc);
	dw_at_address (d->data.i_comp.hi_pc);
	dw_at_udata ((unsigned long)d->data.i_comp.corl.comp_lang);
      }
      output_info (e, d->more);
      break;
    }

    case DGA_PARAMS: {
      output_info (e, d->more);
      break;
    }

    case DGA_SRC: {
      output_info (e, d->more);
      break;
    }

    case DGA_SCOPE: {
      long old_scope1 = dw2_scope_start;
      long old_scope2 = dw2_scope_end;
      long attr1 = 0, attr2;
      char * lexname = d->data.i_scope.lexname;
      if (!doing_abstract) {
	if (!(d->data.i_scope.start)) {	/* optimised away */
	  check_trivial (e);
	  output_info (e, d->more);
	  break;
	}
	if (lexname && lexname[0])
	  attr1 |= (H_NM | H_XY);
	attr1 |= H_PC;
	if (d->data.i_scope.begin_st) {
	  if (d->data.i_scope.begin_st == (long)(-1))	/* TDF_DIAG3 */
	    d->data.i_scope.begin_st = 0;
	  else
	    attr1 |= H_BG;
	  }
      }
      dw2_scope_start = d->data.i_scope.start;
      dw2_scope_end = d->data.i_scope.end;
      attr2 = dw_entry (dwe_scope, attr1);
      if (attr2 & ~(H_NM|H_XY|H_PC|H_BG))
	fail_unimplemented ();
      if (attr2 & H_NM)
	dw_at_string (lexname);
      if (attr2 & H_XY)
	dw_at_decl (d->data.i_scope.lexpos);
      if (attr2 & H_PC) {
	dw_at_address (dw2_scope_start);
	dw_at_address (dw2_scope_end);
      }
      if (attr2 & H_BG)
	dw_at_address (d->data.i_scope.begin_st);
      output_info (e, d->more);
      dw_sibling_end ();
      dw2_scope_start = old_scope1;
      dw2_scope_end = old_scope2;
      break;
    }

    case DGA_EXTRA: {
      long old_scope1 = dw2_scope_start;
      long old_scope2 = dw2_scope_end;
      dw2_scope_start = d->data.i_scope.start;
      dw2_scope_end = d->data.i_scope.end;
      if (!doing_abstract) {
	IGNORE dw_entry (dwe_fragment, 0);
	dw_at_address (dw2_scope_start);
	dw_at_address (dw2_scope_end);
      }
      output_info (e, d->more);
      if (!doing_abstract)
	dw_sibling_end ();
      dw2_scope_start = old_scope1;
      dw2_scope_end = old_scope2;
      break;
    }

    case DGA_LAB: {
      if (!doing_abstract) {
	if (d->data.i_scope.start) {
	  IGNORE dw_entry (dwe_label, 0);
	  dw_at_string (d->data.i_scope.lexname);
	  dw_at_decl (d->data.i_scope.lexpos);
	  dw_at_address (d->data.i_scope.start);
	}
	else
	  check_trivial (e);
      }
      output_info (e, d->more);
      break;
    }

    case DGA_NAME: {
      local_var_place = d->data.i_name.scope_start;
      dw2_out_name (d->data.i_name.dname, (e ? LOCAL_NAME : DEAD_NAME));
      output_info (e, d->more);
      break;
    }

    case DGA_WITH: {
      if (!doing_abstract) {
	if (!(d->data.i_with.lo_pc) || !e) {	/* optimised away */
	  check_trivial (e);
	  output_info (e, d->more);
	  break;
	}
	IGNORE dw_entry (dwe_with, 0);
	dw_at_ext_lab (dw2_find_type_label (d->data.i_with.w_type));
	dw2_locate_exp (son(d->data.i_with.w_exp), 0, 0);
	dw_at_address (d->data.i_with.lo_pc);
	dw_at_address (d->data.i_with.hi_pc);
      }
      output_info (e, d->more);
      if (!doing_abstract) {
	dw_sibling_end ();
      }
      break;
    }

    case DGA_CALL: {
      if (doing_abstract)
        output_info (e, d->more);
      else {
	if (!(d->data.i_call.brk)) {	/* optimised away */
	  check_trivial (e);
	  output_info (e, d->more);
	  break;
	}
	IGNORE dw_entry (dwe_call, 0);
	dw_at_string (d->data.i_call.clname);
	dw_at_decl (d->data.i_call.pos);
	dw_at_udata ((unsigned long)d->data.i_call.ck);
	dw_at_address (d->data.i_call.brk);
	dw2_locate_val (d->data.i_call.p);
	output_info (e, d->more);
      }
      break;
    }

    case DGA_INL_CALL: {
      bool old_il = doing_inline;
      dg_type old_res = return_type;
      dg_name_list args = d->data.i_inl.args;
      dg_name di;
      dg_type p_t, res_t;
      long brk = d->data.i_inl.lo_pc;
      if (doing_abstract)
	break;	/* no recursion */
      di = d->data.i_inl.proc->p.name;
      p_t = find_proc_type (di->data.n_proc.type);
      res_t = p_t->data.t_proc.res_type;
      return_type = res_t;
      if (brk) {			/* sometimes lo = hi */
	IGNORE dw_entry (dwe_inl_call, 0);
	dw_at_ext_address (d->data.i_inl.proc);
	dw_at_address (d->data.i_inl.lo_pc);
	dw_at_address (d->data.i_inl.hi_pc);
      }
      else {	/* call compressed into operand, so no breakpoint */
	check_trivial (e);
	IGNORE dw_entry (dwe_inl_opnd, 0);
	dw_at_ext_address (d->data.i_inl.proc);
      }
      doing_inline = true;
      while (args) {
	dw2_out_name (args, INL_PARAM_NAME);
	args = args->next;
      }
      if (extra_diags && brk) {
	dg_info rets = d->data.i_inl.resref;
	long attr1 = H_XY, attr2;
	if (rets) {
	  attr1 |= H_PC;
	  if (res_t)
	    attr1 |= H_LC;
	}
	do {
	  attr2 = dw_entry (dwe_return, attr1);
	  if (attr2 & ~(H_XY|H_PC|H_LC))
	    fail_unimplemented ();
	  if (attr2 & H_XY)
	    dw_at_decl (di->more->end_pos);
	  if (attr2 & H_PC)
	    dw_at_address (rets->data.i_res.brk);
	  if (attr2 & H_LC)
	    dw2_locate_val (rets->data.i_res.res);
	  if (!rets)
	    break;
	  rets = rets->data.i_res.next;
	}
	while (rets);
      }
      output_info (e, d->more);
      doing_inline = old_il;
      dw_sibling_end ();
      return_type = old_res;
      break;
    }

    case DGA_INL_RES: {
      output_info (e, d->more);
      break;
    }

    case DGA_X_TRY: {
      if (!doing_abstract) {
	if (!(d->data.i_try.lo_pc)) {	/* optimised away */
	  check_trivial (e);
	  output_info (e, d->more);
	  break;
	}
	IGNORE dw_entry (dwe_try, 0);
	dw_at_address (d->data.i_try.lo_pc);
	dw_at_address (d->data.i_try.hi_pc);
      }
      output_info (e, d->more);
      if (!doing_abstract)
	dw_sibling_end ();
      break;
    }

    case DGA_X_CATCH: {
      if (!doing_abstract) {
	if (!(d->data.i_catch.lo_pc)) {	/* optimised away */
	  check_trivial (e);
	  output_info (e, d->more);
	  break;
	}
	IGNORE dw_entry (dwe_catch, 0);
	dw_at_address (d->data.i_catch.lo_pc);
	dw_at_address (d->data.i_catch.hi_pc);
	if (d->data.i_catch.ex)
	  dw2_out_name (d->data.i_catch.ex, EXCEPT_NAME);
	else
	  IGNORE dw_entry (dwe_opt_par, 0);
      }
      output_info (e, d->more);
      if (!doing_abstract)
	dw_sibling_end ();
      break;
    }

    case DGA_X_RAISE: {
      if (!doing_abstract) {
	long attr1 = H_XY, attr2;
	if (d->data.i_raise.x_type)
	  attr1 |= H_TP;
	if (d->data.i_raise.x_val)
	  attr1 |= (dw_is_const (son(d->data.i_raise.x_val)) ? H_CV : H_LC);
	attr2 = dw_entry (dwe_throw, attr1);
	if (attr2 & ~(H_XY|H_TP|H_LC|H_CV))
	  fail_unimplemented ();
	if (attr2 & H_XY)
	  dw_at_decl (d->data.i_raise.pos);
	if (attr2 & H_TP)
	  dw_at_ext_lab (dw2_find_type_label (d->data.i_raise.x_type));
	if (attr2 & H_LC)
	  dw2_locate_exp (son(d->data.i_raise.x_val), 0, 0);
	if (attr2 & H_CV)
	  dw_out_const (son(d->data.i_raise.x_val));
      }
      output_info (e, d->more);
      break;
    }

    case DGA_BRANCH: {
      if (doing_abstract)
        output_info (e, d->more);
      else {
	long brk = d->data.i_brn.brk;
	if (brk) {
	  IGNORE dw_entry (dwe_branch, 0);
	  dw_at_decl (d->data.i_brn.pos);
	  dw_at_address (brk);
	  dw_at_address (d->data.i_brn.cont);
	  trace_dw_branch_exits (e);
	}
	else {
	  check_trivial (e);
	  IGNORE dw_entry (dwe_branch_0, 0);
	  dw_at_decl (d->data.i_brn.pos);
	}
        output_info (e, d->more);
	if (brk)
	  dw_sibling_end ();
      }
      break;
    }

    case DGA_TEST: {
      if (doing_abstract)
        output_info (e, d->more);
      else {
	long brk = d->data.i_tst.brk;
	if (brk) {
	  IGNORE dw_entry (dwe_test, 0);
	  dw_at_decl (d->data.i_tst.pos);
	  dw_at_address (d->data.i_tst.brk);
	  dw_at_address (d->data.i_tst.cont);
	  dw_at_ext_lab (d->data.i_tst.jlab);
	}
	else {
	  check_trivial (e);
	  IGNORE dw_entry (dwe_test_0, 0);
	  dw_at_decl (d->data.i_tst.pos);
	}
	output_info (e, d->more);
      }
      break;
    }

    case DGA_JUMP: {
      if (doing_abstract)
        output_info (e, d->more);
      else {
	long brk = d->data.i_tst.brk;
	if (brk) {
	  IGNORE dw_entry (dwe_jump, 0);
	  dw_at_decl (d->data.i_tst.pos);
	  dw_at_address (d->data.i_tst.brk);
	  dw_at_ext_lab (d->data.i_tst.jlab);
	}
	else {
	  check_trivial (e);
	  IGNORE dw_entry (dwe_jump_0, 0);
	  dw_at_decl (d->data.i_tst.pos);
	}
	output_info (e, d->more);
      }
      break;
    }

    case DGA_LJ: {
      if (doing_abstract)
        output_info (e, d->more);
      else {
	long brk = d->data.i_lj.brk;
	if (brk) {
	  IGNORE dw_entry (dwe_lj, 0);
	  dw_at_decl (d->data.i_lj.pos);
	  dw_at_address (d->data.i_lj.brk);
	  dw2_locate_val (d->data.i_lj.j);
	}
	else {
	  check_trivial (e);
	  IGNORE dw_entry (dwe_lj_0, 0);
	  dw_at_decl (d->data.i_lj.pos);
	}
	output_info (e, d->more);
      }
      break;
    }

    case DGA_DEST: {
      if (!doing_abstract) {
	long attr1 = 0, attr2;
	if (!(d->data.i_dest.brk)) {	/* optimised away */
	  check_trivial (e);
	  output_info (e, d->more);
	  break;
	}
	if (d->data.i_dest.val) {
	  attr1 |= H_TP;
	  attr1 |= (dw_is_const (son(d->data.i_dest.val)) ? H_CV : H_LC);
	}
	attr2 = dw_entry (dwe_destruct, attr1);
	if (attr2 & ~(H_XY|H_TP|H_LC|H_CV))
	  fail_unimplemented ();
	dw_at_decl (d->data.i_dest.pos);
	dw_at_address (d->data.i_dest.brk);
	if (attr2 & H_TP)
	  dw_at_ext_lab (dw2_find_type_label (return_type));
	if (attr2 & H_LC)
	  dw2_locate_exp (son(d->data.i_dest.val), 0, 0);
	if (attr2 & H_CV)
	  dw_out_const (son(d->data.i_dest.val));
      }
      output_info (e, d->more);
      if (!doing_abstract)
	dw_sibling_end ();
      break;
    }

    case DGA_RVS: {
      if (d->data.i_rvs.has_iv)
	break;		/* inverse ref, so don't output here */
      if (!doing_abstract) {
	abbrev_entry dwe;
	int w_alt = 0, w_en = 0, w_kind = 0;
	switch (d->data.i_rvs.rvs_key) {
	  case DGR_SEL:
	    dwe = (d->data.i_rvs.async ? dwe_asynchsel : dwe_select);
	    break;
	  case DGR_ACC:
	    dwe = (d->data.i_rvs.n_code ? dwe_accept_c : dwe_accept);
	    w_alt = w_en = 1;
	    break;
	  case DGR_RTS:
	    dwe = dwe_rts;
	    w_alt = w_kind = 1;
	    if (d->data.i_rvs.en) {
	      dwe = dwe_rts_en;
	      w_en = 1;
	    }
	    break;
	  case DGR_ALT:
	    dwe = (d->data.i_rvs.n_code ? dwe_sel_alt_c : dwe_sel_alt);
	    w_kind = 1;
	    break;
	  case DGR_SGD:
	    dwe = dwe_sel_guard;
	    break;
	  case DGR_TRIG:
	    dwe = (d->data.i_rvs.n_code ? dwe_trigger_c : dwe_trigger);
	    w_kind = 1;
	    break;
	  case DGR_ABTL:
	    dwe = (d->data.i_rvs.n_code ? dwe_abort_ptc : dwe_abort_pt);
	    break;
	  case DGR_REQUE:
	    dwe = dwe_requeue;
	    w_en = 1;
	    break;
	}
	IGNORE dw_entry (dwe, 0);
	dw_at_decl (d->data.i_rvs.pos);
	if (d->data.i_rvs.n_code) {
	  dw_at_address (d->data.i_rvs.lo_pc);
	  if (d->data.i_rvs.n_code >= 2)
	    dw_at_address (d->data.i_rvs.hi_pc);
	}
	if (w_alt)
	  dw_at_flag (d->data.i_rvs.alt);
	if (w_en)
	  dw_at_ext_address (d->data.i_rvs.en);
	if (w_kind)
	  dw_at_udata ((unsigned long)d->data.i_rvs.kind);
	if (d->data.i_rvs.rvs_key == DGR_ALT)
	  dw_out_const (d->data.i_rvs.u2.e);
	if (d->data.i_rvs.rvs_key == DGR_REQUE)
	  dw_at_flag (d->data.i_rvs.w_abort);
	if (d->data.i_rvs.rvs_key == DGR_ACC && d->data.i_rvs.n_code) {
	  dg_name_list args = d->data.i_rvs.u2.p;
	  while (args) {
	    dw2_out_name (args, INL_PARAM_NAME);
	    args = args->next;
	  }
	}
	if (d->data.i_rvs.holder) {
	  dg_info inner = d->data.i_rvs.u.iv;
	  while (inner) {
	    if (!inner->data.i_rvs.has_iv)
	      error(ERR_INTERNAL, "bad RVS invert");
	    inner->data.i_rvs.has_iv = 0;
	    output_info (inner->data.i_rvs.info_e, inner);
	    inner->data.i_rvs.has_iv = 1;
	    inner = inner->data.i_rvs.u.iv;
	  }
	}
      }
      output_info (e, d->more);
      if (!doing_abstract && d->data.i_rvs.rvs_key != DGR_RTS &&
		(d->data.i_rvs.n_code || (d->data.i_rvs.rvs_key == DGR_ALT ||
			d->data.i_rvs.rvs_key == DGR_TRIG)))
	dw_sibling_end ();
      break;
    }

    case DGA_DETCH: {
      if (d->data.i_detch.posn < 0) {
	output_detch (d->data.i_detch.dl);
	output_info (e, d->more);
      }
      else {
	output_info (e, d->more);
	output_detch (d->data.i_detch.dl);
      }
      break;
    }

    case DGA_MOVD:
    case DGA_HOIST: {
      if (!doing_abstract) {
	dg_tag tag = d->data.i_movd.tag;
	if (d->this_tag)
	  set_ext_address (d->this_tag);
	if (d->data.i_movd.lo_pc) {
	  IGNORE dw_entry ((tag ? dwe_moved_r : dwe_moved), 0);
	  dw_at_udata ((unsigned long)d->data.i_movd.reason);
	  if (tag)
	    dw_at_ext_address (tag);
	  dw_at_address (d->data.i_movd.lo_pc);
	  dw_at_address (d->data.i_movd.hi_pc);
	}
	else {
	  check_trivial (e);
	  IGNORE dw_entry ((tag ? dwe_moved_xr : dwe_moved_x), 0);
	  dw_at_udata ((unsigned long)d->data.i_movd.reason);
	  if (tag)
	    dw_at_ext_address (tag);
	}
      }
      output_info (e, d->more);
      if (!doing_abstract)
	dw_sibling_end ();
      break;
    }

    case DGA_OPTIM: {
      if (!doing_abstract) {
	if (d->this_tag)
	  set_ext_address (d->this_tag);
	if (d->data.i_optim.lo_pc) {
	  IGNORE dw_entry (dwe_optim, 0);
	  dw_at_udata ((unsigned long)d->data.i_optim.reason);
	  dw_at_address (d->data.i_optim.lo_pc);
	  dw_at_address (d->data.i_optim.hi_pc);
	  out_refblock (d->data.i_optim.objs, 0);	/* unassigned refs */
	  out_refblock (d->data.i_optim.objs, 1);	/* assigned refs */
	}
	else {
	  check_trivial (e);
	  IGNORE dw_entry (dwe_moved_x, 0);
	  dw_at_udata ((unsigned long)d->data.i_movd.reason);
	}
      }
      output_info (e, d->more);
      if (!doing_abstract)
	dw_sibling_end ();
      break;
    }

    case DGA_REMVAL:
    case DGA_BEG:
    case DGA_BAR:
    case DGA_NONE: {
      output_info (e, d->more);
      break;
    }

    default:
      error(ERR_INTERNAL, "unexpected dg_info");

  }
}

static void output_detch
    ( detch_info * dl )
{
  while (dl) {
    int has_child = 0;
    int has_dest = 0;
    int reason = dl->why;
    dg_info d_src = dl->info;
    dg_info more_src = NULL;
    dg_tag tag = dl->tag;
    while (tag && tag->copy)
      tag = tag->copy;
    if (tag && tag->p.info->key == DGA_MOVD) {
      d_src = tag->p.info;
      reason = d_src->data.i_movd.reason;
      if (d_src->data.i_movd.lost)
	tag = d_src->data.i_movd.tag;
      else
	has_dest = 1;
      d_src = d_src->more;
    }
    if (has_dest) {
      if (d_src->key == DGA_SRC && !doing_abstract) {
	IGNORE dw_entry (dwe_displ_x, 0);
	dw_at_ext_address (tag);
	dw_at_decl (d_src->data.i_src.startpos);
      }
      else
      if ( !doing_abstract &&
		d_src->key != DGA_INL_RES &&
		(d_src->key != DGA_RVS || !d_src->data.i_rvs.has_iv) &&
		d_src->key != DGA_BEG && d_src->key != DGA_BAR)
      {
	IGNORE dw_entry (dwe_displaced, 0);
	dw_at_ext_address (tag);
      }
    }
    else {
      if (d_src->key == DGA_SRC && !doing_abstract) {
	IGNORE dw_entry ((tag ? dwe_absent_xr : dwe_absent_x), 0);
	dw_at_udata ((unsigned long)reason);
	if (tag)
	  dw_at_ext_address (tag);
	dw_at_decl (d_src->data.i_src.startpos);
      }
      else
      if (d_src->key == DGA_NAME)	/* included when doing_abstract */
	more_src = d_src;
      else
      if ( !doing_abstract &&
		d_src->key != DGA_INL_RES &&
		(d_src->key != DGA_RVS || !d_src->data.i_rvs.has_iv) &&
		d_src->key != DGA_BEG && d_src->key != DGA_BAR)
      {
	has_child = 1;
	more_src = d_src;
	more_src->more = NULL;
	IGNORE dw_entry ((tag ? dwe_absent_r : dwe_absent), 0);
	dw_at_udata ((unsigned long)reason);
	if (tag)
	  dw_at_ext_address (tag);
      }
    }
    {
      detch_info * old = sub_detch;
      sub_detch = dl->sub;
      output_info (NULL, more_src);
      sub_detch = old;
    }
    if (has_child)
      dw_sibling_end ();
    dl = dl->next;
  }
}


static void out_param
    ( dg_param p )
{
  /* within debug_info */
  /* used for declarations only */
  long attr1 = (H_TP | H_VP), attr2;
  if (p.pname[0])
    attr1 |= H_NM;
  if (p.ppos.file)
    attr1 |= H_XY;
#ifdef H_DX
  if (p.p_dflt) {
    if (p.p_dflt->span.sp_key == SP_SPAN ||
	(p.p_dflt->val && dw_is_const (son(p.p_dflt->val)) ))
      attr1 |= H_DF;
    else
      attr1 |= H_DX;
  }
#else
  if (p.p_dflt)
    attr1 |= H_DF;
#endif
  attr2 = dw_entry (dwe_param, attr1);
#ifdef H_DX
  if (attr2 & ~(H_NM|H_XY|H_TP|H_VP|H_DF|H_DX))
#else
  if (attr2 & ~(H_NM|H_XY|H_TP|H_VP|H_DF))
#endif
    fail_unimplemented ();
  if (attr2 & H_NM)
    dw_at_string (p.pname);
  if (attr2 & H_XY)
    dw_at_decl (p.ppos);
  if (attr2 & H_TP)
    dw_at_ext_lab (dw2_find_type_label (p.p_type));
  if (attr2 & H_VP) {
    int vp = 0;
    if (p.pmode == DG_OUT_MODE || p.pmode == DG_INOUT_MODE)
      vp = 1;
    dw_at_flag (vp);
  }
#ifdef H_DX
  if (attr2 & H_DX)
    dw_at_flag ((p.p_dflt && !(attr2 & H_DF)) ? 1 : 0);
#endif
  if (attr2 & H_DF)
    dw_out_default (p.p_dflt);
}


static void dw2_out_proc
    ( dg_name di )
{
				/* within debug_info section */
  bool old_il = doing_inline;
  bool old_ab = doing_abstract;
  long infolab = 0;
  exp id;
  dg_type p_t, res_t;
  dg_type old_res = return_type;
  long is_callable = DW_CC_normal;
  char* name;
  char* gname = "";
  long attr1, attr2;
  dg_instantn * generic = NULL;
  dg_info old_di = proc_dg_info;
  proc_dg_info = NULL;
  if (di->idname.id_key == DG_ID_INST) {
    generic = di->idname.idd.instance;
    if (generic->name.id_key == DG_ID_ANON)
      name = generic->spec.idd.name;
    else {
      name  = generic->name.idd.name;
      gname = generic->spec.idd.name;
    }
  }
  else
    name = di->idname.idd.name;
  p_t = find_proc_type (di->data.n_proc.type);
  res_t = p_t->data.t_proc.res_type;
  return_type = res_t;
  id = di->data.n_proc.obtain_val;
  if (id) {
    exp p;
    if (id->tag != hold_tag || son(id)->tag != name_tag) {
      error(ERR_INTERNAL, "wrong proc obtain_tag");
      return;
    }
    id = son(son(id));
    p = son(id);
    if (p) {
      exp t = son(p);
      dw2_prepare_locate (id);
      proc_dg_info = dgf(p);
      if (proc_dg_info && proc_dg_info->key != DGA_PRC)
	error(ERR_INTERNAL, "inconsistent proc info");
      if (proc_has_vcallees(p))
	is_callable = DW_CC_nocall;
      while (t->tag == ident_tag && isparam(t) && son(t)->tag != formal_callee_tag)
	t = bro(son(t));
      if (t->tag == ident_tag && son(t)->tag == formal_callee_tag)
	is_callable = DW_CC_nocall;
      if (brog(id)->extnamed) {
	infolab = next_dwarf_label ();
	exit_section ();
	enter_section ("debug_pubnames");
	out32 (); out_dwf_labdiff (dw_info_start, infolab); asm_printf("\n");
	out_string (name);
	exit_section ();
	enter_section ("debug_info");
      }
    }
  }

  if (p_t->data.t_proc.prps & (f_untidy | f_var_callees))
    is_callable = DW_CC_nocall;
  if (di->more && di->more->refspec)
    attr1 = H_SP | H_XY;
  else {
    attr1 = H_NM | H_XY;
    if (res_t)
      attr1 |= H_TP;
    switch (di->idname.id_key) {
      case DG_ID_EXT:
	attr1 |= H_EX;
	break;
      case DG_ID_ARTFL:
	attr1 |= H_AT;
	break;
      case DG_ID_INST:
	if (gname[0])
	  attr1 |= H_GN;
	break;
      default:
	break;
    }
    if (p_t->data.t_proc.knowpro)
      attr1 |= H_PT;
    if (p_t->data.t_proc.lang)
      attr1 |= H_LN;
    if (p_t->data.t_proc.ccv) {
      attr1 |= H_CC;
      if (p_t->data.t_proc.ccv != DW_CC_normal)
	is_callable = p_t->data.t_proc.ccv;
    }
  }
  if (is_callable | DW_CC_normal)
    attr1 |= H_CC;
  if (di->more && di->more->isspec)
    attr1 |= H_DC;
  if (di->more && di->more->issep)
    attr1 |= H_SE;
  if (di->more && di->more->acc)
    attr1 |= H_AC;
  if (di->more && di->more->virt)
    attr1 |= H_VT;
  if (di->more && di->more->vslot)
    attr1 |= H_VL;
  if (di->more && di->more->repn)
    attr1 |= H_RP;
  doing_abstract = false;
  if (di->more && di->more->this_tag) {
    set_ext_address (di->more->this_tag);
    if (di->more->this_tag->any_inl) {
      doing_abstract = true;
      attr1 |= H_IL;
    }
  }

  do {
    if (!doing_abstract && proc_dg_info) {
      if (infolab)
	out_dwf_label (infolab, 1);
      attr1 |= H_PC;
      if (proc_dg_info->data.i_prc.p &&
		proc_dg_info->data.i_prc.p->data.i_param.o_env)
	attr1 |= H_SL;
      if (di->more && di->more->elabn)
	attr1 |= H_EL;
    }

    attr2 = dw_entry (dwe_proc, attr1);

    if (attr2 & ~(H_AO|H_SP|H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|
		  H_TP|H_PT|H_IL|H_VT|H_VL|H_PC|H_SL|H_EXTN))
      fail_unimplemented ();
    if (attr2 & H_AO)
      dw_at_ext_address (di->more->this_tag);
    if (attr2 & H_SP)
      dw_at_ext_address (di->more->refspec);
    if (attr2 & H_DC)
      dw_at_flag ((di->more && di->more->isspec ? 1 : 0));
    if (attr2 & H_NM)
      dw_at_string (name);
    if (attr2 & H_XY)
      dw_at_decl (di->whence);
    if (attr2 & H_EX)
      dw_at_flag ((di->idname.id_key == DG_ID_EXT ? 1 : 0));
    if (attr2 & H_AT)
      dw_at_flag ((di->idname.id_key == DG_ID_ARTFL ? 1 : 0));
    if (attr2 & H_AC)
      dw_at_data (1, (long)(di->more ? di->more->acc : 0));
    if (attr2 & H_CC)
      dw_at_data (1, is_callable);
    if (attr2 & H_TP)
      dw_at_ext_lab (dw2_find_type_label (res_t));
    if (attr2 & H_PT)
      dw_at_flag (p_t->data.t_proc.yespro);
    if (attr2 & H_IL)
      dw_at_data (1, (long)(di->more->isinline ? DW_INL_declared_inlined :
					      DW_INL_inlined));
    if (attr2 & H_VT)
      dw_at_data (1, (long)(di->more ? di->more->virt : 0));
    if (attr2 & H_VL)
      dw2_locate_exp (son(di->more->vslot), 0, 0);
    if (attr2 & H_PC) {
      dw_at_address (proc_dg_info->data.i_prc.prc_start);
      dw_at_address (proc_dg_info->data.i_prc.prc_end);
      dw_at_procdetails ();	/* return address and frame_base */
    }
    if (attr2 & H_SL)
      dw2_locate_exp (son(proc_dg_info->data.i_prc.p->data.i_param.o_env), 1, 0);

    if (attr2 & H_EXTN) {
      long block_end = next_dwarf_label ();
      attr1 &= ~attr2;
      if (attr1 & ~(H_EL|H_GN|H_RP|H_LN|H_SE))
	fail_unimplemented ();
      out16 (); out_dwf_dist_to_label (block_end); asm_printf("\n");
      if (attr1 & H_EL) {
	set_attribute (DW_AT_DD_elaboration, DW_FORM_ref_addr);
	dw_at_ext_address (di->more->elabn);
      }
      if (attr1 & H_GN) {
	set_attribute (DW_AT_DD_generic_name, DW_FORM_string);
	dw_at_string (gname);
      }
      if (attr1 & H_RP) {
	set_attribute (DW_AT_DD_repn, 0);
	dw_out_const (son (di->more->repn));
      }
      if (attr1 & H_LN) {
	set_attribute (DW_AT_language, DW_FORM_udata);
	dw_at_udata ((unsigned long)(p_t->data.t_proc.lang));
      }
      if (attr1 & H_SE) {
	set_attribute (DW_AT_DD_separate, DW_FORM_flag);
	dw_at_flag ((di->more && di->more->issep ? 1 : 0));
      }
      set_attribute (0, 0);
      out_dwf_label (block_end, 1);
    }

    if (!doing_abstract && generic)
      dw2_out_generic (generic->params);

    if (!doing_abstract && !proc_dg_info && !di->data.n_proc.params) {
		/* must be declaration only */
      dg_param * el = p_t->data.t_proc.params.array;
      int i;
      for (i = 0; i < p_t->data.t_proc.params.len; i++)
	out_param (el[i]);
      if (p_t->data.t_proc.prps & f_var_callers)
	IGNORE dw_entry (dwe_opt_par, 0);

      if (di->more && di->more->en_family)
	dw_out_dim (*(di->more->en_family));
      dw_sibling_end ();
      break;	/* to return */
    }
    {
      dg_name param = NULL;
      dg_param * el = p_t->data.t_proc.params.array;
      int w = 0;
      if (proc_dg_info && proc_dg_info->data.i_prc.p)
	param = proc_dg_info->data.i_prc.p->data.i_param.args;
      else
      if (di->data.n_proc.params)
	param = di->data.n_proc.params->data.i_param.args;
      while (param) {
	if (param->key == DGN_OBJECT) {
	  if (w < p_t->data.t_proc.params.len)
	    param->data.n_obj.p = &(el[w]);
	  else
	    param->data.n_obj.p = NULL;
	}
	if (doing_abstract) {
	  if (!(param->more) || !(param->more->this_tag))
	    error(ERR_INTERNAL, "param inlining error");
	  param->more->inline_ref = param->more->this_tag;
	}
	dw2_out_name (param, PARAM_NAME);
	param = param->next;
	w++;
      }
    }
    if (p_t->data.t_proc.prps & f_var_callers)
      IGNORE dw_entry (dwe_opt_par, 0);

    if (!doing_abstract && di->more && di->more->exptns.len) {
      dg_type * et = di->more->exptns.array;
      int i;
      for (i = 0; i < di->more->exptns.len; i++) {
	IGNORE dw_entry (dwe_thrown_t, 0);
	dw_at_ext_lab (dw2_find_type_label (et[i]));
      }
    }
    if (di->more && di->more->en_family)
      dw_out_dim (*(di->more->en_family));
    if (proc_dg_info && proc_dg_info->data.i_prc.barrier) {
      dg_info b = proc_dg_info->data.i_prc.barrier;
      IGNORE dw_entry (dwe_barrier, 0);
      dw_at_decl (b->data.i_bar.pos);
      dw_at_address (b->data.i_bar.lo_pc);
      dw_at_address (b->data.i_bar.hi_pc);
    }

    if (!doing_abstract && extra_diags && proc_dg_info) {
      long atret1 = H_XY, atret2;
      retrec * rets = proc_dg_info->data.i_prc.returns;
      if (rets) {
	atret1 |= H_PC;
	if (res_t)
	  atret1 |= H_LC;
      }
      do {
	atret2 = dw_entry (dwe_return, atret1);
	if (atret2 & ~(H_XY|H_PC|H_LC))
	  fail_unimplemented ();
	if (atret2 & H_XY)
	  dw_at_decl (di->more->end_pos);
	if (atret2 & H_PC)
	  dw_at_address (rets->lab);
	if (atret2 & H_LC)
	  dw2_locate_result (pt(son(id)));
	if (!rets)
	  break;
	rets = rets->next;
      }
      while (rets);
    }

    if (id && (proc_dg_info || doing_abstract)) {
      output_info (son(id), (proc_dg_info ? dgf(son(id))->more : dgf(son(id))));
    }

    dw_sibling_end ();
    if (doing_abstract) {
      doing_abstract = false;
      doing_inline   = true;
      attr1 = H_AO;
    }
    else
      break;
  }
  while (proc_dg_info);

  doing_abstract = old_ab;
  doing_inline   = old_il;
  proc_dg_info = old_di;
  return_type = old_res;
}


void dw2_out_generic
    ( dg_name_list p )
{
  while (p) {
    switch (p->key) {
      case DGN_OBJECT: {
	IGNORE dw_entry (dwe_tmpl_val, 0);
	dw_at_string (idname_chars (p->idname));
	dw_at_decl (p->whence);
	dw_at_ext_lab (dw2_find_type_label (p->data.n_obj.type));
	dw_out_const (son (p->data.n_obj.obtain_val));
	break;
      }
      case DGN_TYPE: {
	IGNORE dw_entry (dwe_tmpl_type, 0);
	dw_at_string (idname_chars (p->idname));
	dw_at_decl (p->whence);
	dw_at_ext_lab (dw2_find_type_label (p->data.n_type.raw));
	break;
      }
      case DGN_PROC: {
	IGNORE dw_entry (dwe_tmpl_proc, 0);
	dw_at_string (idname_chars (p->idname));
	dw_at_decl (p->whence);
	dw_at_ext_address (p->more->refspec);
	break;
      }
      case DGN_MODULE: {
	IGNORE dw_entry (dwe_tmpl_mod, 0);
	dw_at_string (idname_chars (p->idname));
	dw_at_decl (p->whence);
	dw_at_ext_address (p->more->refspec);
	break;
      }
      default:
	break;
    }
    p = p->next;
  }
}


void dw2_out_name
    ( dg_name di , dg_nm_contex contex )
{
				/* in debug_info section */
  dg_tag inl_tag = (di->more ? di->more->inline_ref : NULL);
  if (di->more && di->more->this_tag && !di->more->this_tag->outref.k) {
    di->more->this_tag->outref.k = LAB_D;
    di->more->this_tag->outref.u.l = next_dwarf_label ();
  }

				/* EXCEPT_NAME, INSTANTN_NAME not done yet */
  if ((contex == LOCAL_NAME || contex == DEAD_NAME) && !doing_abstract) {
    if (!dw2_scope_start)
      error(ERR_INTERNAL, "missing scope");
  }

  switch (di->key) {

    case DGN_OBJECT: {
      exp x = di->data.n_obj.obtain_val;
      dg_type type = di->data.n_obj.type;
      dg_param * ppar = (contex == PARAM_NAME ? di->data.n_obj.p : NULL);
      char* name = idname_chars (di->idname);
      long attr1 = 0, attr2;
      long loclab = 0, loclabext = 0, infolab = 0;
      abbrev_entry dwe;
      if ((inl_tag && !doing_inline && !doing_abstract) || (!inl_tag && doing_inline))
	error(ERR_INTERNAL, "inline inconsistency");

      if (contex == GLOBAL_NAME && di->idname.id_key == DG_ID_EXT &&
		x && find_id (son(x))) {
	infolab = next_dwarf_label ();
	exit_section ();
	enter_section ("debug_pubnames");
	out32 (); out_dwf_labdiff (dw_info_start, infolab); asm_printf("\n");
	dw_at_string (name);
	exit_section ();
	enter_section ("debug_info");
      }

      if (contex == PARAM_NAME || contex == INL_PARAM_NAME)
	dwe = dwe_param;
      else
      if (di->more && di->more->isconst)
	dwe = dwe_constant;
      else
	dwe = dwe_variable;

      if (doing_inline)
	attr1 |= H_AO;
      else {
	if (di->more && di->more->refspec)
	  attr1 |= (H_SP | H_XY);
	else {
	  attr1 |= (H_NM | H_XY | H_TP);
	  if (contex == GLOBAL_NAME)
	    attr1 |= H_EX;
	  if (di->idname.id_key == DG_ID_ARTFL)
	    attr1 |= H_AT;
	}
	if (di->more && di->more->isspec)
	  attr1 |= H_DC;
	if (di->more && di->more->acc)
	  attr1 |= H_AC;
	if (contex == PARAM_NAME) {
	  attr1 |= H_VP;
#ifdef H_DX
	  if (ppar && ppar->p_dflt) {
	    if (ppar->p_dflt->span.sp_key == SP_SPAN ||
		(ppar->p_dflt->val && dw_is_const (son(ppar->p_dflt->val)) ))
	      attr1 |= H_DF;
	    else
	      attr1 |= H_DX;
	  }
#else
	  if (ppar && ppar->p_dflt)
	    attr1 |= H_DF;
#endif
	}
	if (di->more && di->more->repn)
	  attr1 |= H_RP;
      }
      if (!doing_abstract && !(attr1 & H_DC)) {
	if (!x)
	  error(ERR_INTERNAL, "obtain_value missing");
	if (contex == LOCAL_NAME || contex == DEAD_NAME)
	  attr1 |= H_SS;
	if (contex != DEAD_NAME && dw_is_const (son(x)))
	  attr1 |= H_CV;
	else {
	  int ll = decide_ll_type (x);
	  if (!ll && contex == PARAM_NAME)
	    ll = 1;
	  attr1 |= (ll ? H_LL : H_LC);
	  if (ll > 1)
	    attr1 |= H_LE;
	}
      }

      if (di->more && di->more->this_tag) {
	if (doing_abstract)
	  set_abstract_lab (di->more->this_tag);
	else
	  set_ext_address (di->more->this_tag);
      }
      if (infolab)
	out_dwf_label (infolab, 1);
      attr2 = dw_entry (dwe, attr1);
      if (attr2 & ~(H_AO|H_SP|H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_TP|H_VP|
#ifdef H_DX
		    H_SS|H_LC|H_LL|H_LE|H_CV|H_RP|H_DF|H_DX))
#else
		    H_SS|H_LC|H_LL|H_LE|H_CV|H_RP|H_DF))
#endif
	fail_unimplemented ();

      if (attr2 & H_AO)
	dw_at_abstract_lab (inl_tag);
      if (attr2 & H_SP)
	dw_at_ext_address (di->more->refspec);
      if (attr2 & H_DC)
	dw_at_flag ((di->more && di->more->isspec ? 1 : 0));
      if (attr2 & H_NM)
	dw_at_string (name);
      if (attr2 & H_XY)
	dw_at_decl (di->whence);
      if (attr2 & H_EX)
	dw_at_flag ((infolab ? 1 : 0));
      if (attr2 & H_AT)
	dw_at_flag ((di->idname.id_key == DG_ID_ARTFL ? 1 : 0));
      if (attr2 & H_AC)
	dw_at_data (1, (long)(di->more ? di->more->acc : 0));
      if (attr2 & H_TP)
	dw_at_ext_lab (dw2_find_type_label (type));
      if (attr2 & H_VP) {
	int vp = 0;
	if (ppar && (ppar->pmode == DG_OUT_MODE || ppar->pmode == DG_INOUT_MODE))
	  vp = 1;
	dw_at_flag (vp);
      }
#ifdef H_DX
      if (attr2 & H_DX)
	dw_at_flag ((ppar && ppar->p_dflt && !(attr2 & H_DF)) ? 1 : 0);
#endif
      if (attr2 & H_DF)
	dw_out_default (ppar->p_dflt);
      if (attr2 & H_SS)
	dw_at_distance (dw2_scope_start, local_var_place);
      if (attr2 & H_CV)
	dw_out_const (son(x));
      if (attr2 & H_LC) {
	if (contex == DEAD_NAME)
	  dw_no_locate ();
	else
	  dw2_locate_exp (son(x), 0, 0);
      }
      if (attr2 & H_LL)
	dw_at_address (loclab = next_dwarf_label ());
      if (attr2 & H_LE)
	dw_at_address (loclabext = next_dwarf_label ());
      if (attr2 & H_RP)
	dw_out_const (son (di->more->repn));

      if (loclab) {
	long lstart, lend;
#if 0
	retrec * rets = proc_dg_info->data.i_prc.returns;
	long rstart = proc_dg_info->data.i_prc.p->data.i_param.b_start, rend;
#endif
	exit_section ();
	enter_section ("debug_loc");
	out_dwf_label (loclab, 1);
	if (contex == PARAM_NAME) {
	  lstart = proc_dg_info->data.i_prc.prc_start;
	  out_loc_range (lstart, lstart, 1);
	  dw2_locate_exp (son(x), 0, 3);
	  lstart = proc_dg_info->data.i_prc.p->data.i_param.b_start;
	  lend = proc_dg_info->data.i_prc.prc_end;
	}
	else {
	  lstart = dw2_scope_start;
	  lend = dw2_scope_end;
	}
	out_obj_loclist (lstart, lend, x);
#if 0
	while (rets) {
	  if (rets->over) {
	    rend = rets->lab;
	    if (rend != rstart) {
	      out_loc_range (rstart, rend, 0);
	      dw2_locate_exp (son(x), 0, 1);
	    }
	    rstart = rets->over;
	  }
	  rets = rets->next;
	}
	rend = proc_dg_info->data.i_prc.prc_end;
	if (rend != rstart) {
	  out_loc_range (rstart, rend, 0);
	  dw2_locate_exp (son(x), 0, 1);
	}
#endif
	out32(); asm_printf("0, 0"); asm_comment("loclist end");
	if (loclabext) {
	  out_dwf_label (loclabext, 1);
	  out_obj_extloclist (lstart, lend, x);
	  out32(); asm_printf("0, 0"); asm_comment("extension end");
	}
	out_obj_shared_set (di);
	exit_section ();
	enter_section ("debug_info");
      }
      break;
    }

    case DGN_PROC: {
      dw2_out_proc (di);
      break;
    }

    case DGN_MODULE:
    case DGN_NSP: {
      char* name;
      char* gname = "";
      long attr1 = 0, attr2;
      abbrev_entry dwe;
      int has_init_code = 0;
      exp id = di->data.n_mod.init;
      dg_instantn * generic = NULL;
      dg_name mem;
      if (id && id->tag == hold_tag && son(id)->tag == name_tag) {
	id = son(son(id));
	if (son(id) && (son(id)->tag == apply_tag ||
			son(id)->tag == apply_general_tag)) {
	  dw2_prepare_locate (id);
	  if (dgf(son(id)))
	    has_init_code = 1;
	}
      }
      if (di->key == DGN_MODULE)
	dwe = dwe_module;
      else
	dwe = dwe_namespace;
      if (di->idname.id_key == DG_ID_INST) {
	generic = di->idname.idd.instance;
	if (generic->name.id_key == DG_ID_ANON)
	  name = generic->spec.idd.name;
	else {
	  name = generic->name.idd.name;
	  gname = generic->spec.idd.name;
        }
      }
      else
	name = di->idname.idd.name;
      if (doing_inline)
	attr1 |= H_AO;
      else {
	if (di->more && di->more->refspec)
	  attr1 = H_SP | H_XY;
	else {
	  attr1 = H_NM | H_XY;
	  switch (di->idname.id_key) {
	    case DG_ID_ARTFL:
	      attr1 |= H_AT;
	      break;
	    case DG_ID_INST:
	      if (gname[0])
	        attr1 |= H_GN;
	      break;
	    default:
	      break;
	  }
        }
	if (di->more && di->more->isspec)
	  attr1 |= H_DC;
	if (di->more && di->more->issep)
	  attr1 |= H_SE;
      }
      if (!doing_abstract) {
	if (has_init_code)
	  attr1 |= H_PC;
	if (di->more && di->more->elabn)
	  attr1 |= H_EL;
      }

      if (di->more && di->more->this_tag) {
	if (doing_abstract)
	  set_abstract_lab (di->more->this_tag);
	else
	  set_ext_address (di->more->this_tag);
      }
      attr2 = dw_entry (dwe, attr1);
      if (attr2 & ~(H_AO|H_SP|H_DC|H_NM|H_XY|H_AT|H_AC|H_PC|H_EXTN))
	fail_unimplemented ();

      if (attr2 & H_AO)
	dw_at_abstract_lab (inl_tag);
      if (attr2 & H_SP)
	dw_at_ext_address (di->more->refspec);
      if (attr2 & H_DC)
	dw_at_flag ((di->more && di->more->isspec ? 1 : 0));
      if (attr2 & H_NM)
	dw_at_string (name);
      if (attr2 & H_XY)
	dw_at_decl (di->whence);
      if (attr2 & H_AT)
	dw_at_flag ((di->idname.id_key == DG_ID_ARTFL ? 1 : 0));
      if (attr2 & H_AC)
	dw_at_data (1, (long)(di->more ? di->more->acc : 0));
      if (attr2 & H_PC) {
	dg_info pd = dgf(son(id));
	if (pd->key != DGA_PRC)
	  error(ERR_INTERNAL, "inconsistent proc info");
	dw_at_address (pd->data.i_prc.prc_start);
	dw_at_address (pd->data.i_prc.prc_end);
      }
      if (attr2 & H_EXTN) {
	long block_end = next_dwarf_label ();
	attr1 &= ~attr2;
	if (attr1 & ~(H_EL|H_GN|H_SE))
	  fail_unimplemented ();
	out16 (); out_dwf_dist_to_label (block_end); asm_printf("\n");
	if (attr1 & H_EL) {
	  set_attribute (DW_AT_DD_elaboration, DW_FORM_ref_addr);
	  dw_at_ext_address (di->more->elabn);
	}
	if (attr1 & H_GN) {
	  set_attribute (DW_AT_DD_generic_name, DW_FORM_string);
	  dw_at_string (gname);
	}
	if (attr1 & H_SE) {
	  set_attribute (DW_AT_DD_separate, DW_FORM_flag);
	  dw_at_flag ((di->more && di->more->issep ? 1 : 0));
	}
	set_attribute (0, 0);
	out_dwf_label (block_end, 1);
      }

      if (!doing_abstract && generic)
	dw2_out_generic (generic->params);
      mem = di->data.n_mod.members;
      while (mem) {
	dw2_out_name (mem, contex);
	mem = mem->next;
      }
      dw_sibling_end ();
      break;
    }

    case DGN_SUBUNIT: {
      dw_at_ext_address (di->data.n_sub.parent);
      if (di->data.n_sub.child) {
	if (di->data.n_sub.acc)
	  dw_at_data (1, (long)(di->data.n_sub.acc));
      }
      else
	dw_at_flag (di->data.n_sub.split);
      dw2_out_name (di->data.n_sub.sub, contex);
      dw_sibling_end ();
      break;
    }

    case DGN_IMPORT: {
      long attr1 = 0, attr2;
      char * name = idname_chars (di->idname);
      dg_type p_t = di->data.n_imp.i_type;
      int params = (p_t && p_t->key == DGT_PROC);
      if (name[0])
	attr1 |= H_NM;
      if (di->whence.file)
	attr1 |= H_XY;
      if (di->more && di->more->acc)
	attr1 |= H_AC;
      if (contex == LOCAL_NAME && !doing_abstract)
	attr1 |= H_SS;
      attr2 = dw_entry ((params ? dwe_import_p : dwe_import), attr1);
      if (attr2 & ~(H_NM|H_XY|H_AC|H_SS))
	fail_unimplemented ();
      if (attr2 & H_NM)
	dw_at_string (name);
      if (attr2 & H_XY)
	dw_at_decl (di->whence);
      if (attr2 & H_AC)
	dw_at_data (1, (long)(di->more ? di->more->acc : 0));
      dw_at_ext_address (di->data.n_imp.import);
      dw_at_udata ((unsigned long)(di->data.n_imp.ik));
      if (attr2 & H_SS)
	dw_at_distance (dw2_scope_start, local_var_place);

      if (params) {
	dg_param * el = p_t->data.t_proc.params.array;
	int i;
	for (i = 0; i < p_t->data.t_proc.params.len; i++)
	  out_param (el[i]);
	if (p_t->data.t_proc.prps & f_var_callers)
	  IGNORE dw_entry (dwe_opt_par, 0);
	dw_sibling_end ();
      }
      break;
    }

    case DGN_TYPE: {
      long attr1 = 0, attr2;
      int ada_derived = 0;
      char * name = idname_chars (di->idname);
      if (doing_inline && inl_tag)
	attr1 |= H_AO;
      else {
	if (di->more && di->more->refspec)
	  attr1 = H_SP;
	if (di->more && di->more->isspec)
	  attr1 |= H_DC;
	if (name[0])
	  attr1 |= H_NM;
	if (di->whence.file)
	  attr1 |= H_XY;
	if (di->idname.id_key == DG_ID_ARTFL)
	  attr1 |= H_AT;
	if (di->more && di->more->acc)
	  attr1 |= H_AC;
	if (di->data.n_type.raw)
	  attr1 |= H_TP;
	if (di->more && di->more->isnew)
	  attr1 |= H_NW;
	if (di->more && di->more->aderiv) {
	  attr1 |= H_AD;
	  ada_derived = 1;
	}
      }
      if ((attr1 == H_TP || (!name[0] && !(di->more && di->more->this_tag))) &&
		!(di->data.n_type.raw->outref.u.l) &&
		!di->data.n_type.constraints) {
	if (di->more && di->more->this_tag)
	  di->data.n_type.raw->outref = di->more->this_tag->outref;
	else {
	  di->data.n_type.raw->outref.u.l = next_dwarf_label();
	  di->data.n_type.raw->outref.k = LAB_D;
	}
	dw_out_type (di->data.n_type.raw);
      }
      else {
	if (di->more && di->more->this_tag) {
	  if (doing_abstract)
	    set_abstract_lab (di->more->this_tag);
	  else
	  if (!(di->more->this_tag->done)) {
	    set_ext_address (di->more->this_tag);
	    di->more->this_tag->done = 1;
	  }
	}
	attr2 = dw_entry ((di->data.n_type.constraints ? dwe_typecon :
			dwe_typedef), attr1);
	if (attr2 & ~(H_AO|H_SP|H_DC|H_NM|H_XY|H_AT|H_AC|H_TP|H_NW|H_AD))
	  fail_unimplemented ();

	if (attr2 & H_AO)
	  dw_at_abstract_lab (inl_tag);
	if (attr2 & H_SP)
	  dw_at_ext_address (di->more->refspec);
	if (attr2 & H_DC)
	  dw_at_flag ((di->more && di->more->isspec ? 1 : 0));
	if (attr2 & H_NM)
	  dw_at_string (name);
	if (attr2 & H_XY)
	  dw_at_decl (di->whence);
	if (attr2 & H_AT)
	  dw_at_flag ((di->idname.id_key == DG_ID_ARTFL ? 1 : 0));
	if (attr2 & H_AC)
	  dw_at_data (1, (long)(di->more ? di->more->acc : 0));
	if (attr2 & H_TP)
	  dw_at_ext_lab (dw2_find_type_label (di->data.n_type.raw));
	if (attr2 & H_NW)
	  dw_at_flag ((di->more && di->more->isnew ? 1 : ada_derived));
	if (attr2 & H_AD)
	  dw_at_flag (ada_derived);
      }
      if (di->data.n_type.constraints) {
	dg_constraint c = di->data.n_type.constraints;
	while (c) {
	  attr1 = (c->is_val ? H_CV : H_TP);
	  if (c->refmem)
	    attr1 |= H_RM;
	  attr2 = dw_entry (dwe_cnstraint, attr1);
	  if (attr2 & ~(H_RM|H_CV|H_TP))
	    fail_unimplemented ();
	  if (attr2 & H_RM)
	    dw_at_ext_address (c->refmem);
	  if (attr2 & H_CV)
	    dw_out_const (son(c->u.val));
	  if (attr2 & H_TP)
	    dw_at_ext_lab (dw2_find_type_label (c->u.type));
	  c = c->next;
	}
	dw_sibling_end ();
      }
      break;
    }

    case DGN_ENTRY: {
      long attr1 = 0, attr2;
      char * name = idname_chars (di->idname);
      dg_type p_t = find_proc_type (di->data.n_proc.type);
      dg_type res_t = p_t->data.t_proc.res_type;
      dg_param * el = p_t->data.t_proc.params.array;
      int i;

      attr1 = H_NM | H_XY;
      if (di->more && di->more->acc)
	attr1 |= H_AC;
      if (res_t)
	attr1 |= H_TP;
      if (di->more && di->more->repn)
	attr1 |= H_RP;
      if (di->more && di->more->this_tag)
	set_ext_address (di->more->this_tag);
      attr2 = dw_entry (dwe_entry, attr1);
      if (attr2 & ~(H_NM|H_XY|H_AC|H_TP|H_RP))
	fail_unimplemented ();
      if (attr2 & H_NM)
	dw_at_string (name);
      if (attr2 & H_XY)
	dw_at_decl (di->whence);
      if (attr2 & H_AC)
	dw_at_data (1, (long)(di->more ? di->more->acc : 0));
      if (attr2 & H_TP)
	dw_at_ext_lab (dw2_find_type_label (res_t));
      if (attr2 & H_RP) {
	dw_out_const (son (di->more->repn));
      }

      for (i = 0; i < p_t->data.t_proc.params.len; i++)
	out_param (el[i]);
      if (di->more && di->more->en_family)
	dw_out_dim (*(di->more->en_family));
      dw_sibling_end ();
      break;
    }

    default:
      error(ERR_INTERNAL, "unexpected dg_name");
  }
  if (di->more && di->more->this_tag)
    di->more->this_tag->done = 1;
}


static retrec ** returns_list;


void dw2_proc_start
    ( exp p , dg_name d )
{
  if (dgf(p))
    error(ERR_INTERNAL, "unexpected diag info for proc");
  proc_dg_info = dgf(p) = new_dg_info (DGA_PRC);
  proc_dg_info->data.i_prc.prc_start = set_dw_text_label ();
  proc_dg_info->data.i_prc.prc_end = 0;
  proc_dg_info->data.i_prc.returns = NULL;
  returns_list = &(proc_dg_info->data.i_prc.returns);
  proc_dg_info->data.i_prc.p = proc_dg_info->data.i_prc.barrier = NULL;
  if (d)
    dw2_source_mark (d->whence, 0);
}


void dw2_return_pos
    ( long over )
{
  retrec * rec = xmalloc (sizeof (retrec));
  rec->lab = set_dw_text_label ();
  rec->over = over;
  rec->next = NULL;
  *returns_list = rec;
  returns_list = &(rec->next);
  if (over)
    set_obj_rets (rec);
}


void dw2_proc_end
    ( exp p )
{
  dgf(p)->data.i_prc.prc_end = set_dw_text_label ();
  proc_dg_info = NULL;
}


static void prepare_detch
    ( detch_info * dl )
{
  while (dl) {
    int reason = dl->why;
    dg_info d = dl->info;
    dg_tag found_tag;
    if (reason >= DGD_MOVD) {
      found_tag = dl->tag;
      while (found_tag->copy)
	found_tag = found_tag->copy;
      d = found_tag->p.info;
      reason = d->data.i_movd.reason;
      d = d->more;
    }
    if (reason < DGD_MOVD) {
      switch (d->key) {
	case DGA_NAME: {
	  d->data.i_name.scope_start = set_dw_text_label ();
	  break;
	}
	case DGA_SCOPE: {
	  d->data.i_scope.start = set_dw_text_label ();
	  d->data.i_scope.end = set_dw_text_label ();
	  break;
	}
	case DGA_REMVAL: {
	  d->data.i_remval.lo_pc = set_dw_text_label ();
	  set_remval_object (d);
	  break;
	}
	default:
	  break;
      }
    }
    if (dl->sub)
      prepare_detch (dl->sub);
    dl = dl->next;
  }
}


void dw2_code_info
    ( dg_info d , void (*mcode) (void *) , void * args )
{
  if (d == NULL) {
    (*mcode)(args);
    return;
  }
  switch (d->key) {

    case DGA_PARAMS: {
      obj_list hold_pars;
      hold_pars.obj = d->data.i_param.args;
      hold_pars.islist = 1;
      hold_pars.next = NULL;
      local_objects = &hold_pars;
      set_locdata (hold_pars);
      if (proc_dg_info)
	proc_dg_info->data.i_prc.p = d;
      d->data.i_param.b_start = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      close_locdata (hold_pars);
      local_objects = NULL;
      break;
    }

    case DGA_COMP: {
      dw2_code_info (d->more, mcode, args);
      break;
    }

    case DGA_SRC: {
      if (d->data.i_src.startpos.file)
	dw2_source_mark (d->data.i_src.startpos, d->data.i_src.is_stmt);
      dw2_code_info (d->more, mcode, args);
      if (d->data.i_src.endpos.file)
	dw2_source_mark (d->data.i_src.endpos, 0);
      break;
    }

    case DGA_SCOPE:
    case DGA_EXTRA: {
      d->data.i_scope.start = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_scope.end = set_dw_text_label ();
      break;
    }

    case DGA_LAB: {
      d->data.i_scope.start = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      break;
    }

    case DGA_NAME: {
      obj_list hold_obj;
      hold_obj.obj = d->data.i_name.dname;
      hold_obj.islist = 0;
      hold_obj.next = local_objects;
      local_objects = &hold_obj;
      set_locdata (hold_obj);
      d->data.i_name.scope_start = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      close_locdata (hold_obj);
      local_objects = hold_obj.next;
      break;
    }

    case DGA_WITH: {
      d->data.i_with.lo_pc = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_with.hi_pc = set_dw_text_label ();
      break;
    }

    case DGA_CALL: {
      dg_info old = current_dg_info;
      current_dg_info = d;
      dw2_code_info (d->more, mcode, args);
      current_dg_info = old;
      break;
    }

    case DGA_INL_CALL: {
      obj_list hold_pars;
      hold_pars.obj = d->data.i_inl.args;
      hold_pars.islist = 1;
      hold_pars.next = local_objects;
      local_objects = &hold_pars;
      set_locdata (hold_pars);
      d->data.i_inl.lo_pc = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_inl.hi_pc = set_dw_text_label ();
      close_locdata (hold_pars);
      local_objects = hold_pars.next;
      break;
    }

    case DGA_INL_RES: {
      dw2_code_info (d->more, mcode, args);
      d->data.i_res.brk = set_dw_text_label ();
      d->data.i_res.res = find_diag_res (args);
      {
	dg_tag cr = d->data.i_res.call;
	dg_info * dl;
	if (cr->key != DGK_INFO || cr->p.info->key != DGA_INL_CALL)
	  error(ERR_INTERNAL, "inline result ref?");
	dl = &(cr->p.info->data.i_inl.resref);
	while (*dl) {
	  if ((*dl)==d) {
	    error(ERR_INTERNAL, "impossible cycle");
	    return;
	  }
	  dl = &((*dl)->data.i_res.next);
	}
	*dl = d;
      }
      break;
    }

    case DGA_X_TRY: {
      d->data.i_try.lo_pc = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_try.hi_pc = set_dw_text_label ();
      break;
    }

    case DGA_X_CATCH: {
      obj_list hold_obj;
      hold_obj.obj = d->data.i_catch.ex;
      hold_obj.islist = 0;
      hold_obj.next = local_objects;
      local_objects = &hold_obj;
      set_locdata (hold_obj);
      d->data.i_catch.lo_pc = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_catch.hi_pc = set_dw_text_label ();
      close_locdata (hold_obj);
      local_objects = hold_obj.next;
      break;
    }

    case DGA_X_RAISE: {
      dw2_code_info (d->more, mcode, args);
      break;
    }

    case DGA_BRANCH: {
      bool old_db = dw_doing_branch_tests;
      dw_doing_branch_tests = true;
      d->data.i_brn.brk = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_brn.cont = set_dw_text_label ();
      dw_doing_branch_tests = old_db;
      break;
    }

    case DGA_TEST:
    case DGA_JUMP:
    case DGA_LJ: {
      dg_info old = current_dg_info;
      current_dg_info = d;
      dw2_code_info (d->more, mcode, args);
      current_dg_info = old;
      break;
    }

    case DGA_BEG: {
      dg_tag tag = d->data.i_tag;
      if (tag->key != DGK_INFO || tag->p.info->key != DGA_SCOPE)
	error(ERR_INTERNAL, "statement_part_dg?");
      tag->p.info->data.i_scope.begin_st = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      break;
    }

    case DGA_DEST: {
      d->data.i_dest.brk = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      break;
    }

    case DGA_RVS: {
      obj_list hold_pars;
      hold_pars.next = local_objects;
      if (d->data.i_rvs.rvs_key == DGR_ACC && d->data.i_rvs.n_code) {
	hold_pars.obj = d->data.i_rvs.u2.p;
	hold_pars.islist = 1;
	local_objects = &hold_pars;
	set_locdata (hold_pars);
      }
      if (d->data.i_rvs.n_code)
	d->data.i_rvs.lo_pc = set_dw_text_label ();
      if (d->data.i_rvs.u.tag) {
	dg_info h;
	if (d->data.i_rvs.u.tag->key != DGK_INFO || (
		h = d->data.i_rvs.u.tag->p.info, h->key != DGA_RVS)) {
	    error(ERR_INTERNAL, "incompatible rendezvous sequence");
	    break;
	  }
	d->data.i_rvs.u.iv = h->data.i_rvs.u.iv;
	h->data.i_rvs.u.iv = d;
	h->data.i_rvs.holder = 1;
	d->data.i_rvs.info_e = current_dg_exp;
	d->data.i_rvs.has_iv = 1;
      }
      dw2_code_info (d->more, mcode, args);
      if ((unsigned int)d->data.i_rvs.n_code >= 2)
	d->data.i_rvs.hi_pc = set_dw_text_label ();
      if (d->data.i_rvs.rvs_key == DGR_ACC && d->data.i_rvs.n_code)
	close_locdata (hold_pars);
      local_objects = hold_pars.next;
      break;
    }

    case DGA_BAR: {
      d->data.i_bar.lo_pc = set_dw_text_label ();
      if (proc_dg_info) {
	proc_dg_info->data.i_prc.barrier = d;
      }
      dw2_code_info (d->more, mcode, args);
      d->data.i_bar.hi_pc = set_dw_text_label ();
      break;
    }

    case DGA_DETCH: {
      if (d->data.i_detch.posn < 0) {
	prepare_detch (d->data.i_detch.dl);
	dw2_code_info (d->more, mcode, args);
      }
      else {
	dw2_code_info (d->more, mcode, args);
	prepare_detch (d->data.i_detch.dl);
      }
      break;
    }

    case DGA_MOVD:
    case DGA_HOIST: {
      d->data.i_movd.lo_pc = set_dw_text_label ();
      dw2_code_info (d->more, mcode, args);
      d->data.i_movd.hi_pc = set_dw_text_label ();
      break;
    }

    case DGA_OPTIM: {
      d->data.i_optim.lo_pc = set_dw_text_label ();
      set_optim_objects (d, 1);
      dw2_code_info (d->more, mcode, args);
      d->data.i_optim.hi_pc = set_dw_text_label ();
      set_optim_objects (d, 0);
      break;
    }


    default:
      error(ERR_INTERNAL, "unexpected dg_info");

  }
}
