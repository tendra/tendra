/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/dw2_config.h>
#include <local/szs_als.h>

#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/shape.h>
#include <construct/exp.h>
#include <construct/tags.h>

#include <main/driver.h>
#include <main/flags.h>

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#else
#include <diag/diag_fns.h>
#endif

#include <dwarf2/dw2_types.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_entries.h>
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_info.h>

#include <refactor/refactor.h>

static void fail_unimplemented
    ( long a1 , long a2 )
{
  IGNORE fprintf (stderr, "%lx  %lx\n", a1, a2);
  failer ("unimplemented attribute");
  return;
}

static dg_type needed_types = (dg_type)0;

static char * sep =  ", ";


ext_lab dw2_find_type_label
    ( dg_type t )
{
  if (!(t->outref.u.l)) {
    if (t->key == DGT_TAGGED) {
      dg_tag tg = t->data.t_tag;
      if (tg->done || tg->needed || tg->key == DGK_NONE) {
	t->outref = tg->outref;
	return t->outref;
      }
      if (tg->key == DGK_TYPE) {
	dg_type ref_t = tg->p.typ;
	t->outref = dw2_find_type_label (ref_t);
	tg->outref = t->outref;
	tg->done = 1;
	return t->outref;
      }
      if (tg->key == DGK_NAME) {
	dg_name ref_n = tg->p.nam;
	if (ref_n->key == DGN_TYPE && ref_n->idnam.id_key == DG_ID_NONE) {
	  dg_type ref_t = tg->p.nam->data.n_typ.raw;
	  t->outref = dw2_find_type_label (ref_t);
	  tg->outref = t->outref;
	  tg->done = 1;
	  return t->outref;
	}
      }
      tg->needed = 1;
      t->outref.u.l = tg->outref.u.l = next_dwarf_label();
      t->outref.k = tg->outref.k = LAB_D;
    }
    else {
      t->outref.u.l = next_dwarf_label();
      t->outref.k = LAB_D;
    }
    t->type_queue = needed_types;
    needed_types = t;
  }
  return t->outref;
}


static void out_classmem
    ( dg_classmem m )
{
  /* within info section */
  if (m.tg)
    set_ext_address (m.tg);
  switch (m.cm_key) {
    case DG_CM_FIELD: {
      dg_type f = m.d.cm_f.f_typ;
      exp off = son (m.d.cm_f.f_offset);
      dg_type base = f;
      int base_sz = 1;
      long attr1 = H_TP, attr2;
      if (m.d.cm_f.fnam[0])
	attr1 |= H_NM;
      if (m.d.cm_f.f_pos.file)
	attr1 |= H_XY;
      if (name(off) == val_tag)
	attr1 |= H_LC;
      if (f->key == DGT_BITF) {
	attr1 |= H_BF;
	base = f->data.t_bitf.expanded;
	base_sz = shape_size (f->data.t_bitf.sha);
      }
      if (m.d.cm_f.acc)
	attr1 |= H_AC;
      if (m.d.cm_f.discr)
	attr1 |= H_DS;
#ifdef H_DX
      if (m.d.cm_f.dflt) {
	if (m.d.cm_f.dflt->span.sp_key == SP_SPAN ||
	      (m.d.cm_f.dflt->val && dw_is_const (son(m.d.cm_f.dflt->val)) ))
	  attr1 |= H_DF;
	else
	  attr1 |= H_DX;
      }
#else
      if (m.d.cm_f.dflt)
	attr1 |= H_DF;
#endif

      attr2 = dw_entry (dwe_member, attr1);
#ifdef H_DX
      if (attr2 & ~(H_NM|H_XY|H_AC|H_TP|H_LC|H_BF|H_DS|H_DF|H_DX))
#else
      if (attr2 & ~(H_NM|H_XY|H_AC|H_TP|H_LC|H_BF|H_DS|H_DF))
#endif
	fail_unimplemented (attr1, attr2);
      if (attr2 & H_NM)
	dw_at_string (m.d.cm_f.fnam);
      if (attr2 & H_XY)
	dw_at_decl (m.d.cm_f.f_pos);
      if (attr2 & H_AC)
	dw_at_data (1, (long)m.d.cm_f.acc);
      if (attr2 & H_TP)
	dw_at_ext_lab (dw2_find_type_label (base));
      if (attr2 & H_LC)
	dw_locate_offset (((no (off)) & -base_sz) >> 3);
      if (attr2 & H_BF) {
	switch (endian) {
	case ENDIAN_BIG:
		dw_at_data (1, (long)(no (off) & (base_sz - 1)));
		break;
	case ENDIAN_LITTLE:
		dw_at_data (1, (long)(base_sz - f->data.t_bitf.bv.bits
					- (no (off) & (base_sz - 1))));
		break;
	}
	dw_at_data (1, (long)f->data.t_bitf.bv.bits);
      }
      if (attr2 & H_DS)
	dw_at_flag (m.d.cm_f.discr);
#ifdef H_DX
      if (attr2 & H_DX)
	dw_at_flag ((m.d.cm_f.dflt && !(attr2 & H_DF)) ? 1 : 0);
#endif
      if (attr2 & H_DF)
	dw_out_default (m.d.cm_f.dflt);
      break;
    }
    case DG_CM_FN: {
      dw2_out_name (m.d.cm_fn.fn, MEMBER_NAME);
      break;
    }
    case DG_CM_INDIRECT: {
      long attr1 = (H_TP | H_LC), attr2;
      if (m.d.cm_ind.nam[0])
	attr1 |= H_NM;
      if (m.d.cm_ind.pos.file)
	attr1 |= H_XY;
      attr2 = dw_entry (dwe_ind_mem, attr1);
      if (attr2 & ~(H_NM|H_XY|H_TP|H_LC))
	fail_unimplemented (attr1, attr2);
      if (attr2 & H_NM)
	dw_at_string (m.d.cm_ind.nam);
      if (attr2 & H_XY)
	dw_at_decl (m.d.cm_ind.pos);
      if (attr2 & H_TP)
	dw_at_ext_lab (dw2_find_type_label (m.d.cm_ind.typ));
      if (attr2 & H_LC)
	dw_locate_reloffset (son(m.d.cm_ind.ind_loc));
      break;
    }
    case DG_CM_STAT: {
      dw2_out_name (m.d.cm_stat, MEMBER_NAME);
      break;
    }
  }
  return;
}


static void out_class_data
    ( class_data * cd )
{
  /* within info section */
  exp vtable_exp = NULL;
  int i;
  for (i = 0; i < cd->inherits.len; i++) {
    dg_class_base cb;
    long attr1 = (H_TP | H_LC), attr2;
    cb = cd->inherits.array[i];
    if (cb.pos.file)
      attr1 |= H_XY;
    if (cb.acc)
      attr1 |= H_AC;
    if (cb.virt)
      attr1 |= H_VT;
    attr2 = dw_entry (dwe_inheritce, attr1);
    if (attr2 & ~(H_XY|H_TP|H_LC|H_AC|H_VT))
      fail_unimplemented (attr1, attr2);
    if (attr2 & H_XY)
      dw_at_decl (cb.pos);
    if (attr2 & H_TP)
      dw_at_ext_address (cb.base);
    if (attr2 & H_LC) {
      if (cb.location)
	dw_locate_reloffset (son(cb.location));
      else {
	out8(); outn ((long)1); outs(sep);
	outn ((long)DW_OP_nop); d_outnl();
      }
    }
    if (attr2 & H_AC)
      dw_at_data (1, (long)cb.acc);
    if (attr2 & H_VT)
      dw_at_data (1, (long)cb.virt);
  }
  for (i = 0; i < cd->friends.len; i++) {
    dg_tag f = cd->friends.array[i];
    IGNORE dw_entry (dwe_friend, (long)0);
    dw_at_ext_address (f);
  }
  if (cd->vt_s) {
    for (i = 0; i < cd->members.len; i++) {
      dg_classmem * cm = &(cd->members.array[i]);
      if (cm->cm_key == DG_CM_STAT && cm->d.cm_stat->key == DGN_OBJECT &&
	    ((cm->d.cm_stat->mor && cm->d.cm_stat->mor->this_tag == cd->vt_s)
		|| cm->tg == cd->vt_s))
	vtable_exp = cm->d.cm_stat->data.n_obj.obtain_val;
    }
    for (i = 0; i < cd->members.len; i++) {
      dg_classmem * cm = &(cd->members.array[i]);
      if (cm->cm_key == DG_CM_FN && cm->d.cm_fn.fn->key == DGN_PROC &&
		cm->d.cm_fn.fn->mor && cm->d.cm_fn.fn->mor->virt) {
	exp a, b, c;
	if (!vtable_exp || !cm->d.cm_fn.slot ||
		name(sh(son(cm->d.cm_fn.slot))) != offsethd)
	  failer ("wrong virtual function data");
	a = copy (son(vtable_exp));
	b = copy (son(cm->d.cm_fn.slot));
	c = f_add_to_ptr (a, b);
	cm->d.cm_fn.fn->mor->vslot = hold (hold_refactor(c));
      }
    }
  }
  for (i = 0; i < cd->members.len; i++) {
    out_classmem (cd->members.array[i]);
  }
  return;
}


static void out_task_sync_data
    ( task_data * td )
{
  /* within info section */
  int i;
  dg_name en = td->entries;
  while (en) {
    dw2_out_name (en, GLOBAL_NAME);
    en = en->next;
  }
  for (i = 0; i < td->members.len; i++) {
    out_classmem (td->members.array[i]);
  }
  return;
}



static void out_variant_part
    ( dg_varpart * v )
{
  /* within info section */
  int i, j;
  dg_variant * v_el = v->vnts.array;
  switch (v->v_key) {
    case DG_V_D: {
      long l = next_dwarf_label();
      IGNORE dw_entry (dwe_varpart, (long)0);
      dw_at_address (l);
      out_dwf_label (l, 1);
      out_classmem (v->u.d);
      break;
    }
    case DG_V_S: {
      IGNORE dw_entry (dwe_varpart, (long)0);
      dw_at_ext_address (v->u.s);
      break;
    }
    case DG_V_T: {
      IGNORE dw_entry (dwe_varpart_t, (long)0);
      dw_at_ext_lab (dw2_find_type_label (v->u.t));
      break;
    }
  }
  for (i = 0; i < v->vnts.len; i++) {
    dg_discrim * d_el = v_el[i].discr.array;
    dg_classmem * f_el = v_el[i].fields.array;
    if (v_el[i].discr.len == 0)
      IGNORE dw_entry (dwe_variant_0, (long)0);
    else
    if (v_el[i].discr.len == 1 && no(d_el->lower) == no(d_el->upper)) {
      IGNORE dw_entry (dwe_variant_1, (long)0);
      dw_out_const (d_el->lower);
    }
    else {
      long block_end = next_dwarf_label ();
      int ss = (name(sh(d_el->lower)) & 1);
      IGNORE dw_entry (dwe_variant_n, (long)0);
      out16 (); out_dwf_dist_to_label (block_end); d_outnl();
      for (j = 0; j < v_el[i].discr.len; j++) {
	out8 ();
	if (no(d_el[i].lower) == no(d_el[i].upper)) {
	  outn ((long)DW_DSC_label); outs (sep);
	  if (ss)
	    sleb128 ((long)no(d_el[i].lower));
	  else
	    uleb128 ((unsigned long)no(d_el[i].lower));
	}
	else {
	  outn ((long)DW_DSC_range); outs (sep);
	  if (ss) {
	    sleb128 ((long)no(d_el[i].lower));
	    outs (sep);
	    sleb128 ((long)no(d_el[i].upper));
	  }
	  else {
	    uleb128 ((unsigned long)no(d_el[i].lower));
	    outs (sep);
	    uleb128 ((unsigned long)no(d_el[i].upper));
	  }
	}
	d_outnl();
      }
      out_dwf_label (block_end, 1);
    }
    for (j = 0; j < v_el[i].fields.len; j++) {
      out_classmem (f_el[j]);
    }
    dw_sibling_end ();
  }
  dw_sibling_end ();
  return;
}


static void out_ref_bound
    ( dg_tag tg )
{
  dw_at_form (DW_FORM_ref_addr); d_outnl ();
  dw_at_ext_address (tg);
  return;
}


void dw_out_dim
    ( dg_dim d )
{
  /* within info section */
  long attr1 = 0, attr2;
  if (d.d_key == DG_DIM_TYPE) {		/* must be array dimension */
    if ((d.d_typ->key == DGT_SUBR || d.d_typ->key == DGT_ENUM) &&
		!(d.d_typ->outref.u.l)) {
      d.d_typ->outref.u.l = next_dwarf_label();
      d.d_typ->outref.k = LAB_D;
      dw_out_type (d.d_typ);
    }
    else {
      attr1 = H_TP;
      attr2 = dw_entry (dwe_typedef, attr1);
      if (attr2 != attr1)
	fail_unimplemented (attr1, attr2);
      dw_at_ext_lab (dw2_find_type_label (d.d_typ));
    }
    return;
  }
  if (d.d_typ)
    attr1 |= (H_TP | H_SZ);
  if (!d.low_ref || d.lower.tg)
    attr1 |= H_LB;
  if (!d.hi_ref || d.upper.tg)
    attr1 |= (d.hi_cnt ? H_CN : H_UB);
  attr2 = dw_entry (dwe_subr_type, attr1);
  if (attr2 & ~(H_TP|H_SZ|H_LB|H_UB|H_CN))
    fail_unimplemented (attr1, attr2);
  if (attr2 & H_TP)
    dw_at_ext_lab (dw2_find_type_label (d.d_typ));
  if (attr2 & H_SZ)
    dw_at_udata ((unsigned long)(shape_size (d.sha) >> 3));
  if (attr2 & H_LB) {
    if (d.low_ref)
      out_ref_bound (d.lower.tg);
    else
      dw_out_const (son(d.lower.x));
  }
  if (attr2 & (H_UB | H_CN)) {
    if (d.hi_ref)
      out_ref_bound (d.upper.tg);
    else
      dw_out_const (son(d.upper.x));
  }
  return;
}


void dw_out_type
    ( dg_type t )
{
  /* within info section */
  dw_set_ext_lab (t->outref);
  switch (t->key) {

    case DGT_TAGGED: {
      dg_tag tg = t->data.t_tag;
      if (tg->done || tg->key != DGK_NAME || tg->p.nam->key != DGN_TYPE) {
	failer ("unexpected out_type");
	outnl_comment ("		ERROR");
	break;
      }
      tg->done = 1;
      dw2_out_name (tg->p.nam, GLOBAL_NAME);
      break;
    }

    case DGT_BASIC: {
      shape sha = t->data.t_bas.b_sh;
      long encoding;
      switch (t->data.t_bas.b_key) {
	case DG_ADR_T:
	  encoding = DW_ATE_address;
	  break;
	case DG_BOOL_T:
	  encoding = DW_ATE_boolean;
	  break;
	case DG_CHAR_T:
	  encoding = (is_signed (sha) ? DW_ATE_signed_char : DW_ATE_unsigned_char);
	  break;
	case DG_INT_T:
	  encoding = (is_signed (sha) ? DW_ATE_signed : DW_ATE_unsigned);
	  break;
	case DG_FLOAT_T:
	  encoding = (is_floating (name(sha)) ? DW_ATE_float : DW_ATE_complex_float);
	  break;
      }
      IGNORE dw_entry (dwe_base_type, (long)0);
      dw_at_string (t->data.t_bas.tnam);
      dw_at_data (1, encoding);
      dw_at_udata ((unsigned long)(shape_size (sha) >> 3));
      break;
    }

    case DGT_QUAL: {
      abbrev_entry dwe;
      int flg = 0;
      switch (t->data.t_qual.q_key) {
	case DG_PTR_T: {
	  dwe = dwe_ptr_type;
	  break;
	}
	case DG_HPPTR_T: {
	  dwe = dwe_hpptr_t;
	  flg = 1;
	  break;
	}
	case DG_REF_T: {
	  dwe = dwe_ref_type;
	  break;
	}
	case DG_PACK_T: {
	  dwe = dwe_pack_type;
	  break;
	}
	case DG_CONST_T: {
	  dwe = dwe_cnst_type;
	  break;
	}
	case DG_VOL_T: {
	  dwe = dwe_vol_type;
	  break;
	}
	case DG_ALIAS_T: {
	  dwe = dwe_als_type;
	  break;
	}
	case DG_CLWID_T: {
	  dwe = dwe_clwd_type;
	  break;
	}
	case DG_LIM_T: {
	  dwe = dwe_lim_type;
	  break;
	}
	case N_DG_QUAL_TYPES:
	  break;	/* dummy */
      }
      IGNORE dw_entry (dwe, (long)0);
      dw_at_ext_lab (dw2_find_type_label (t->data.t_qual.typ));
      if (flg)
	dw_at_flag (flg);
      break;
    }

    case DGT_ARRAY: {
      exp stride_e = son(t->data.t_arr.stride);
      dg_dim * el = t->data.t_arr.dims.array;
      int stride_known = (name(stride_e) == val_tag);
      int size_known = stride_known;
      unsigned long tot_size = (unsigned long) no(stride_e);
      int i;
      for (i = 0; i < t->data.t_arr.dims.len && size_known; i++) {
	if (el[i].count >= 0)
	  tot_size *= (unsigned long) el[i].count;
	else
	  size_known = 0;
      }

      IGNORE dw_entry ((size_known ? dwe_arr_type : dwe_arr_dyn), (long)0);
      dw_at_ext_lab (dw2_find_type_label (t->data.t_arr.elem_type));
      if (stride_known)
	dw_out_const (stride_e);
      else
	dw2_offset_exp (stride_e);
      dw_at_data (1, (long)(t->data.t_arr.rowm ? DW_ORD_row_major : DW_ORD_col_major));
      if (size_known)
	dw_at_udata ((tot_size + 7) >> 3);

      for (i = 0; i < t->data.t_arr.dims.len; i++)
	dw_out_dim (el[i]);
      dw_sibling_end ();
      break;
    }

    case DGT_SUBR: {
      dw_out_dim (t->data.t_subr);
      break;
    }

    case DGT_ENUM: {
      long attr1 = H_SZ, attr2;
      int i;
      dg_enum * el = t->data.t_enum.values.array;
      if (t->mor && t->mor->refspec)
	attr1 |= H_SP;
      if (t->mor && t->mor->isspec)
	attr1 |= H_DC;
      if (t->data.t_enum.tnam[0])
	attr1 |= H_NM;
      if (t->data.t_enum.tpos.file)
	attr1 |= H_XY;
      if (t->mor && t->mor->isnew)
	attr1 |= H_NW;
      attr2 = dw_entry (dwe_enum_type, attr1);
      if (attr2 & ~(H_SP|H_DC|H_NM|H_XY|H_SZ|H_NW))
	fail_unimplemented (attr1, attr2);
      if (attr2 & H_SP)
	dw_at_ext_lab (dw2_find_type_label (t->mor->refspec->p.typ));
      if (attr2 & H_DC)
	dw_at_flag ((t->mor && t->mor->isspec ? 1 : 0));
      if (attr2 & H_NM)
	dw_at_string (t->data.t_enum.tnam);
      if (attr2 & H_XY)
	dw_at_decl (t->data.t_enum.tpos);
      if (attr2 & H_SZ)
	dw_at_udata ((unsigned long)(shape_size (sh (son(el[0].value))) >> 3));
      if (attr2 & H_NW)
	dw_at_flag ((t->mor && t->mor->isnew ? 1 : 0));

      for (i = 0; i < t->data.t_enum.values.len; i++) {
	if (el[i].tg)
	  set_ext_address (el[i].tg);
	if (el[i].is_chn) {
	  IGNORE dw_entry (dwe_enum_char, (long)0);
	  out8(); uleb128 ((unsigned long)el[i].chn); d_outnl();
	}
	else {
	  IGNORE dw_entry (dwe_enum_tor, (long)0);
	  dw_at_string (el[i].enam);
	}
	dw_out_const (son(el[i].value));
      }
      dw_sibling_end ();
      break;
    }

    case DGT_STRUCT:
    case DGT_CLASS:
    case DGT_A_TASK:
    case DGT_A_SYNCH: {
      abbrev_entry dwe;
      int ada_derived = 0;
      char* nam;
      char* gnam = "";
      long attr1 = 0, attr2;
      dg_instantn * generic = NULL;
      if (t->data.t_struct.is_union)
	dwe = dwe_union_t;
      else
      switch (t->key) {
	case DGT_STRUCT:
	  dwe = dwe_struct_t;
	  break;
	case DGT_CLASS:
	  dwe = dwe_class_t;
	  break;
	case DGT_A_TASK:
	  dwe = dwe_task_t;
	  break;
	default:
	  dwe = dwe_synch_t;
	  break;
      }
      if (t->data.t_struct.idnam.id_key == DG_ID_INST) {
	generic = t->data.t_struct.idnam.idd.instance;
	if (generic->nam.id_key == DG_ID_NONE ||
		generic->nam.id_key == DG_ID_ANON)
	  nam = generic->spec.idd.nam;
        else {
	  nam = generic->nam.idd.nam;
	  gnam = generic->spec.idd.nam;
	}
      }
      else
	nam = t->data.t_struct.idnam.idd.nam;

      if (t->data.t_struct.tpos.file)
	attr1 |= H_XY;
      if (t->mor && t->mor->refspec)
	attr1 |= H_SP;
      else {
	if (nam[0])
	  attr1 |= H_NM;
	if (gnam[0])
	  attr1 |= H_GN;
      }
      if (t->mor && t->mor->isspec)
	attr1 |= H_DC;
      if (t->mor && t->mor->issep)
	attr1 |= H_SE;
      if (t->data.t_struct.sha)
	attr1 |= H_SZ;
      if (t->mor && t->mor->elabn)
	attr1 |= H_EL;
      if (t->mor && t->mor->isnew)
	attr1 |= H_NW;
      if (t->mor && t->mor->aderiv) {
	attr1 |= H_AD;
	ada_derived = 1;
      }

      if (t->key == DGT_CLASS) {
	if (t->data.t_struct.u.cd->vt_s)
	  attr1 |= H_VS;
	if (t->data.t_struct.u.cd->vt_d)
	  attr1 |= H_VD;
	if (t->data.t_struct.u.cd->rtti_s)
	  attr1 |= H_RS;
	if (t->data.t_struct.u.cd->rtti_d)
	  attr1 |= H_RD;
      }
      else
      if (t->key != DGT_STRUCT) {
	if (t->data.t_struct.u.td->cb)
	  attr1 |= H_CB;
	if (t->data.t_struct.u.td->id)
	  attr1 |= H_ID;
      }

      attr2 = dw_entry (dwe, attr1);
      if (attr2 & ~(H_SP|H_DC|H_NM|H_XY|H_SZ|H_NW|H_EXTN))
	fail_unimplemented (attr1, attr2);
      if (attr2 & H_SP)
	dw_at_ext_lab (dw2_find_type_label (t->mor->refspec->p.typ));
      if (attr2 & H_DC)
	dw_at_flag ((t->mor && t->mor->isspec ? 1 : 0));
      if (attr2 & H_NM)
	dw_at_string (nam);
      if (attr2 & H_XY)
	dw_at_decl (t->data.t_struct.tpos);
      if (attr2 & H_SZ)
	dw_at_udata ((unsigned long)(shape_size (t->data.t_struct.sha) >> 3));
      if (attr2 & H_NW)
	dw_at_flag ((t->mor && t->mor->isnew ? 1 : 0));

      if (attr2 & H_EXTN) {
	long block_end = next_dwarf_label ();
	out16 (); out_dwf_dist_to_label (block_end); d_outnl();
	attr1 &= ~attr2;
	if (attr1 & H_NW) {
	  set_attribute (DW_AT_DD_newtype, DW_FORM_flag);
	  dw_at_flag ((t->mor && t->mor->isnew ? 1 : ada_derived));
	}
	if (attr1 & H_AD) {
	  set_attribute (DW_AT_DD_ada_derived, DW_FORM_flag);
	  dw_at_flag (ada_derived);
	}
	if (attr1 & H_SE) {
	  set_attribute (DW_AT_DD_ada_derived, DW_FORM_flag);
	  dw_at_flag ((t->mor && t->mor->issep ? 1 : 0));
	}
	switch (t->key) {
	  case DGT_STRUCT: {
	    fail_unimplemented (attr1, attr1);
	    break;
	  }
	  case DGT_CLASS: {
	    if (attr1 & ~(H_NW|H_VS|H_VD|H_RS|H_RD|H_EL|H_GN|H_AD))
	      fail_unimplemented (attr1, attr1);
	    if (attr1 & H_VS) {
	      set_attribute (DW_AT_DD_vtable_static, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.cd->vt_s);
	    }
	    if (attr1 & H_VD) {
	      set_attribute (DW_AT_DD_vtable_dynamic, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.cd->vt_d);
	    }
	    if (attr1 & H_RS) {
	      set_attribute (DW_AT_DD_rtti_static, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.cd->rtti_s);
	    }
	    if (attr1 & H_RD) {
	      set_attribute (DW_AT_DD_rtti_dynamic, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.cd->rtti_d);
	    }
	    break;
	  }
	  case DGT_A_TASK: {
	    if (attr1 & ~(H_NW|H_ID|H_CB|H_EL|H_GN|H_SE))
	      fail_unimplemented (attr1, attr1);
	    if (attr1 & H_ID) {
	      set_attribute (DW_AT_DD_task_id, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.td->id);
	    }
	    if (attr1 & H_CB) {
	      set_attribute (DW_AT_DD_task_control_block, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.td->cb);
	    }
	    break;
	  }
	  default: {
	    if (attr1 & ~(H_NW|H_CB|H_EL|H_GN|H_SE))
	      fail_unimplemented (attr1, attr1);
	    if (attr1 & H_CB) {
	      set_attribute (DW_AT_DD_so_control_block, DW_FORM_ref_addr);
	      dw_at_ext_address (t->data.t_struct.u.td->cb);
	    }
	    break;
	  }
	}
	if (attr1 & H_EL) {
	  set_attribute (DW_AT_DD_elaboration, DW_FORM_ref_addr);
	  dw_at_ext_address (t->mor->elabn);
	}
	if (attr1 & H_GN) {
	  set_attribute (DW_AT_DD_generic_name, DW_FORM_string);
	  dw_at_string (gnam);
	}
      }

      if (generic)
	dw2_out_generic (generic->params);
      switch (t->key) {
	case DGT_STRUCT: {
	  int i;
	  dg_classmem * el = t->data.t_struct.u.fields.array;
	  for (i = 0; i < t->data.t_struct.u.fields.len; i++)
	    out_classmem (el[i]);
	  break;
	}
	case DGT_CLASS: {
	  out_class_data (t->data.t_struct.u.cd);
	  break;
	}
	default: {
	  out_task_sync_data (t->data.t_struct.u.td);
	  break;
	}
      }
      if (t->data.t_struct.vpart)
	out_variant_part (t->data.t_struct.vpart);
      dw_sibling_end ();
      break;
    }

    case DGT_PMEM: {
      IGNORE dw_entry (dwe_ptrmem_t, (long)0);
      dw_at_ext_address (t->data.t_pmem.pclass);
      dw_at_ext_lab (dw2_find_type_label (t->data.t_pmem.memtyp));
      dw_at_udata ((unsigned long)(shape_size (t->data.t_pmem.sha) >> 3));
      break;
    }

    case DGT_CONS: {
      abbrev_entry dwe;
      long attr1 = (H_TP | H_SZ), attr2 = 0;
      if (t->data.t_cons.c_key == DG_SET_T)
	dwe = dwe_set_t;
      else
	dwe = dwe_file_t;
      if (t->mor && t->mor->refspec)
	attr1 |= H_SP;
      if (t->mor && t->mor->isspec)
	attr1 |= H_DC;
      if (t->data.t_enum.tnam[0])
      attr2 = dw_entry (dwe, attr1);
      if (attr2 & ~(H_SP|H_DC|H_TP|H_SZ))
	fail_unimplemented (attr1, attr2);
      if (attr2 & H_SP)
	dw_at_ext_lab (dw2_find_type_label (t->mor->refspec->p.typ));
      if (attr2 & H_DC)
	dw_at_flag ((t->mor && t->mor->isspec ? 1 : 0));
      if (attr2 & H_TP)
	dw_at_ext_lab (dw2_find_type_label (t->data.t_cons.typ));
      if (attr2 & H_SZ)
	dw_at_udata ((unsigned long)(shape_size (t->data.t_cons.sha) >> 3));
      break;
    }

    case DGT_PROC: {
      int i;
      dg_param * el = t->data.t_proc.params.array;
      dg_type res_t = t->data.t_proc.res_type;
      if (res_t) {
	IGNORE dw_entry (dwe_proc_type, (long)0);
	dw_at_ext_lab (dw2_find_type_label (res_t));
      }
      else
	IGNORE dw_entry (dwe_procv_t, (long)0);
      for (i = 0; i < t->data.t_proc.params.len; i++) {
	IGNORE dw_entry (dwe_formal, (long)0);
	dw_at_ext_lab (dw2_find_type_label (el[i].p_typ));
      }
      if (t->data.t_proc.prps & f_var_callers)
	IGNORE dw_entry (dwe_opt_par, (long)0);
      dw_sibling_end ();
      break;
    }

    case DGT_BITF: {
      failer ("bitfields shouldn't occur here");
      break;
    }

    case DGT_FIXED: {
      long attr1 = 0, attr2;
      if (t->data.t_adanum.delta)
	attr1 |= H_DF;
      if (t->data.t_adanum.digits)
	attr1 |= H_DS;
      attr2 = dw_entry (dwe_fixpt_t, attr1);
      if (attr2 & ~(H_DF|H_DS))
	fail_unimplemented (attr1, attr2);
      dw_at_ext_lab (dw2_find_type_label (t->data.t_adanum.rept));
      dw_out_const (son(t->data.t_adanum.small));
      if (attr2 & H_DF)
	dw_out_const (son(t->data.t_adanum.delta));
      if (attr2 & H_DS)
	dw_out_const (son(t->data.t_adanum.digits));
      break;
    }

    case DGT_FLDIG: {
      IGNORE dw_entry (dwe_fldg_t, (long)0);
      dw_at_ext_lab (dw2_find_type_label (t->data.t_adanum.rept));
      dw_out_const (son(t->data.t_adanum.digits));
      break;
    }

    case DGT_MOD: {
      IGNORE dw_entry (dwe_modular_t, (long)0);
      dw_at_ext_lab (dw2_find_type_label (t->data.t_adanum.rept));
      dw_out_const (son(t->data.t_adanum.digits));
      break;
    }

    case DGT_STRING: {
      exp l_e = son(t->data.t_string.length);	/* other fields ignored */
      if (name(l_e) == val_tag) {
	IGNORE dw_entry (dwe_stringc_t, (long)0);
	dw_at_udata ((unsigned long)no(l_e));
      }
      else {
	IGNORE dw_entry (dwe_string_t, (long)0);
	dw2_locate_exp (l_e, 0, 0);
	dw_at_udata ((unsigned long)(shape_size (sh(l_e)) >> 3));
      }
      break;
    }

    case DGT_UNKNOWN: {
      IGNORE dw_entry (dwe_unknown_t, (long)0);
      break;
    }

    default:
      failer ("illegal type");
  }
  return;
}


void dw2_out_all_types
(void)
{
  while (needed_types) {
    dg_type dt = needed_types;
    needed_types = needed_types->type_queue;
    if (dt->key != DGT_TAGGED || !dt->data.t_tag->done)
      dw_out_type (dt);
  }
  return;
}
