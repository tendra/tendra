/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include <reader/expmacs.h>
#include <reader/exptypes.h>
#include <local/localtypes.h>
#include <local/codermacs.h>
#include <local/szs_als.h>

#ifdef NEWDWARF
#include <local/dw2_config.h>

#include <reader/basicread.h>
#include <refactor/const.h>

#include <construct/machine.h>
#include <construct/shapemacs.h>
#include <construct/tags.h>
#include <construct/label_ops.h>
#include <construct/flpttypes.h>
#include <construct/f64.h>

#include <main/flags.h>

#ifdef NEWDIAGS
#include <newdiag/dg_aux.h>
#include <newdiag/dg_types.h>
#else
#include <diag/dg_aux.h>
#include <diag/dg_types.h>
#endif

#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_entries.h>
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_locdata.h>

#include "operand.h"
#include "instr386.h"
#include "instr.h"
#include "coder.h"
#include "dw2_extra.h"
#include "operand.h"
#include "reg_record.h"


extern int locals_offset; /* declared in cproc.c */


static long dwarfreg[8] = {0, 2, 1, 3, 7, 6, 5, 4};
#define dw_sp 4
#define dw_fp 5
#define retaddr 8

static long cie_pointer;
static long fde_end;
static long proc_end;

static char * sp50 = "                                                  ";

enum loctype { L_INREG = 1, L_REGOFF, L_GLOB, L_INDIRECT };

typedef struct {
  enum loctype key;
  int reg;
  char* s;
  long off;
} loc_s;

static int extra_deref;
static int locate_param;
static int has_fp;
static int no_location;




static void outsep
(void)
{
  outs(", ");
}


int dw_is_const
(exp e)
{
  switch (name(e)) {
    case val_tag:
    case null_tag:
    case real_tag:
      return 1;
    case name_tag:
      return !isdiscarded(e) && isvar(son(e));
#if 0
    case cont_tag:
      return name(son(e)) == name_tag && !isdiscarded(son(e)) &&
		!isvar(son(son(e))) && !isparam(son(son(e)));
#endif
    case reff_tag:
      return 1;
    default:
      return 0;
  }
}

exp dw_has_location
(exp e)
{
  switch (name(e)) {
    case name_tag: {
      if (isdiscarded(e) || isvar(son(e)))
	return NULL;
      return son(e);
    }
    case cont_tag: {
      do {
	e = son(e);
	if (name(e) == name_tag && isdiscarded(e))
	  return NULL;
      }
      while (name(e)!= ident_tag);
      return e;
    }
    default:
      return NULL;
  }
}


static loc_s name_to_loc(exp e);

static loc_s find_param
(exp e)
{
  switch (name(e)) {
    case name_tag:
      if (isvar(son(e)))
	extra_deref--;
      if (isparam(son(e)))
        return name_to_loc(e);
      return find_param(son(son(e)));
    case cont_tag:
      extra_deref++;	/* drop through */
    case chvar_tag:
    case chfl_tag:
      return find_param(son(e));
    default:
      break;
  }
  failer("parameter inconsistency");
  return find_param(e);
}

static loc_s name_to_loc
(exp e)
{
  loc_s l;
  exp id = son(e);
  long n_off = no(e) /8;
  if (locate_param && !isparam(id)) {
    return find_param(son(id));
#if 0
    if (name(son(id)) == name_tag && isloadparam(son(id)) && isparam(son(son(id))))
      return name_to_loc(son(id));
    if (name(son(id)) == cont_tag && name(son(son(id))) == name_tag &&
		isparam(son(son(son(id)))))
      return name_to_loc(son(son(id)));
    failer("parameter inconsistency");
#endif
  }
  if (isglob(id)) {
    l.key = L_GLOB;
    l.s = brog(id) -> dec_u.dec_val.dec_id;
    l.off = n_off;
  }
  else {
    switch (ptno(id)) {
      case local_pl: {
	l.key = L_REGOFF;
	l.reg = -1;
	l.off = (no(id) /8) + n_off;
	if (name(id))
	  l.off -= locals_offset;
	else {			/* env_off modification */
	  if (locate_param) {
	    l.reg = dw_sp;
	  }
	}
	if (has_fp && l.reg < 0)
	  l.off += 4;
	break;
      };
      case callstack_pl: {
	failer("callstack arg - location list needed");
	break;
      };
      case par_pl: {
	l.key = L_REGOFF;
	l.reg = (locate_param ? dw_sp : -1);
	l.off = (no(id) /8) +4 + n_off;
	break;
      };
      case reg_pl: {
	int z = get_reg_no(no(id));
	l.key = L_INREG;
	l.reg = (z >= first_fl_reg ? 100 + z - first_fl_reg :
					(int)dwarfreg[z]);
	break;
      };
      default:
	failer("no location for id");
	SET(l);
    }
    if (has_fp && l.reg < 0)
      l.off += 4;
  }
  return l;
}

static loc_s find_loc
(exp e)
{
  loc_s l;
  switch (name(e)) {

    case name_tag: {
      if (isdiscarded(e) || (isglob(son(e)) && no(son(e)) == 0 &&
				!(brog(son(e)) ->dec_u.dec_val.extnamed))) {
	l.key = L_INREG;
	l.reg = 0;
	no_location = 1;
	return l;
      }
      if (isvar(son(e)))
	extra_deref--;
      return name_to_loc(e);
    }

    case cont_tag:
    case contvol_tag: {
      if (name(son(e)) == name_tag) {
	if (isdiscarded(son(e)) ||
			(isglob(son(son(e))) && no(son(son(e))) == 0 &&
			 !(brog(son(son(e))) ->dec_u.dec_val.extnamed))) {
	  l.key = L_INREG;
	  l.reg = 0;
	  no_location = 1;
	  return l;
	}
	if (isvar(son(son(e))))
	  return name_to_loc(son(e));
      }
      l = find_loc(son(e));
      if (l.key == L_INREG) {
	l.key = L_REGOFF;
	l.off = 0;
      }
      else
	l.key = L_INDIRECT;
      break;
    }

    case reff_tag: {
      l = find_loc(son(e));
      if (l.key == L_GLOB || l.key == L_REGOFF)
	l.off += (no(e) /8);
      else
      if (l.key == L_INREG) {
	l.key = L_REGOFF;
	l.off = (no(e) /8);
	extra_deref--;
      }
      else
	l.key = L_INDIRECT;
      break;
    }

    case chvar_tag: {
      l = find_loc(son(e));
      break;
    }

    default:
      failer("unimplemented location condition");
      SET(l);
  }
  return l;
}

static int inreg_length
(int r, int more)
{
  int ans = 1 + more;
  if (r >= 32)
    ans += uleb128_length((unsigned long)r);
  return ans;
}

static void out_inreg
(int r, int more)
{
  if (!more) {
    if (r < 32)
      outn((long)(DW_OP_reg0 + r));
    else {
      outn((long)DW_OP_regx); outsep(); uleb128((unsigned long)r);
    }
  }
  else {
    if (r < 32)
      outn((long)(DW_OP_breg0 + r));
    else {
      outn((long)DW_OP_bregx); outsep(); uleb128((unsigned long)r);
    }
    outsep(); outn((long)0);
  }
  return;
}

static int regoff_length
(loc_s l)
{
  return 1 + sleb128_length(l.off);
}

static void out_regoff
(loc_s l)
{
  outn((long)(l.reg < 0 ? DW_OP_fbreg : DW_OP_breg0 + l.reg)); outsep();
  sleb128(l.off);
  return;
}

static int glob_length
(loc_s l)
{
  UNUSED(l);
  return 5;
}

static void out_glob
(loc_s l)
{
  outn((long)DW_OP_addr); d_outnl();
  out32(); outs(l.s);
  if (l.off) {
    outs(" + ");
    outn((long)l.off);
  }
  return;
}

static int indirect_length
(exp e)
{
  int length;
  loc_s l;
  switch (name(e)) {
    case cont_tag: {
      length = 1;
      break;
    }
    case reff_tag: {
      if (no(e) >= 0)
	length = 1 + uleb128_length((unsigned long)(no(e) /8));
      else
	length = 2 + uleb128_length((unsigned long)(-no(e) /8));
      break;
    }
    default: {
      failer("unimplemented dwarf locate");
      return 0;
    }
  }
  l = find_loc(son(e));
  switch (l.key) {
    case L_INREG: {
      length += inreg_length(l.reg, 1);
      break;
    }
    case L_REGOFF: {
      length += regoff_length(l);
      break;
    }
    case L_GLOB: {
      length += glob_length(l);
      break;
    }
    case L_INDIRECT: {
      length += indirect_length(son(e));
      break;
    }
  }
  return length;
}

static void out_indirect
(exp e)
{
  loc_s l;
  l = find_loc(e);
  switch (l.key) {
    case L_INREG: {
      out_inreg(l.reg, 1);
      outsep();
      break;
    }
    case L_REGOFF: {
      out_regoff(l);
      outsep();
      break;
    }
    case L_GLOB: {
      out_glob(l);
      d_outnl(); out8();
      break;
    }
    case L_INDIRECT: {
      out_indirect(son(e));
      outsep();
      break;
    }
  }
  switch (name(e)) {
    case cont_tag: {
      outn((long)DW_OP_deref);
      break;
    }
    case reff_tag: {
      if (no(e) >= 0) {
	outn((long)DW_OP_plus_uconst); outsep();
	uleb128((unsigned long)(no(e) /8));
      }
      else {
	outn((long)DW_OP_constu); outsep();
	uleb128((unsigned long)(-no(e) /8)); outsep();
	outn((long)DW_OP_minus);
      }
      break;
    }
  }
  return;
}


void dw2_locate_exp
(exp e, int locate_const, int cx)
{
  loc_s l;
  int length;
  int within_loclist = (cx & 1);
  locate_param = (cx & 2);
  extra_deref = locate_const;
  no_location = 0;
  l = find_loc (e);	/* may reduce extra_deref */
  length = extra_deref;
  switch (l.key) {
    case L_INREG: {
      length += inreg_length(l.reg, extra_deref);
      break;
    }
    case L_REGOFF: {
      length += regoff_length(l);
      break;
    }
    case L_GLOB: {
      length += glob_length(l);
      break;
    }
    case L_INDIRECT: {
      length += indirect_length(e);
      break;
    }
  }
  if (no_location)
    length = 0;

  if (within_loclist) {
    out16();
    outn((long)length); outnl();
    if (no_location)
      return;
    out8();
  }
  else {
    out8();
    outn((long)length);
    if (no_location) {
      outnl();
      return;
    }
    outsep();
  }
  switch (l.key) {
    case L_INREG: {
      out_inreg(l.reg, extra_deref);
      break;
    }
    case L_REGOFF: {
      out_regoff(l);
      break;
    }
    case L_GLOB: {
      out_glob(l);
      break;
    }
    case L_INDIRECT: {
      out_indirect(e);
      break;
    }
  }
  while (extra_deref) {
    if (extra_deref < 0) {
      failer("miscalculated location");
      break;
    }
#if 0
    if (locate_const)
      failer("constant location???");
#endif
    outsep();
    outn((long)DW_OP_deref);
    extra_deref--;
  }
  d_outnl();
  return;
}


void dw2_prepare_locate
(exp id)
{
			/* set local proc conditions for local locations */
  exp p = son(id);	/* proc or general proc */
  locals_offset = no(p);
  has_fp = proc_has_fp(p);
  return;
}

void dw_at_procdetails
(void)
{
			/* return address and frame base */
  out8(); outn((long)2); outsep(); outn((long)DW_OP_fbreg); outsep();
  if (has_fp) {
    outn((long)4); d_outnl();
    out8(); outn((long)1); outsep();
    outn((long)DW_OP_reg0+dw_fp); d_outnl();
  }
  else {
    outn((long)0); d_outnl();
    out8(); outn((long)0); d_outnl();
  }
  return;
}


void dw2_locate_result
(shape sha)
{
  long length = 1;
  int reg = 0;
  int indirect = 0;
  int multi = 0;
  if (is_floating(name(sha))) {
    reg = 100;
    length = inreg_length(reg, 0);
  }
  else
  if (!reg_result(sha)) {
    indirect = 1;
    length = 2;
  }
  else
  if (shape_size(sha) > 32) {
    multi = 1;
    length = 6;
  }
  out8(); outn(length); outsep();
  if (multi) {
    outn((long)DW_OP_reg0); outsep();
    outn((long)DW_OP_piece); outsep(); outn((long)4);
    outsep();
    outn((long)DW_OP_reg0+2); outsep();
    outn((long)DW_OP_piece); outsep(); outn((long)4);
  }
  else
  if (indirect) {
    outn((long)DW_OP_breg0); outsep(); outn((long)0);
  }
  else {
    out_inreg(reg, 0);
  }
  d_outnl();
  return;
}


void dw2_locate_val
(dg_where v)
{
  out8();
  switch (v.k) {
    case NO_WH: {
      outn((long)0);
      break;
    }
    case WH_STR: {
      loc_s l = { 0 };
      l.key = L_GLOB;
      l.s = v.u.s;
      l.off = v.o;
      outn((long)glob_length(l)); outsep();
      out_glob(l);
      break;
    }
    case WH_REG: {
      int r = (int)dwarfreg[v.u.l];
      outn((long)inreg_length(r, 0)); outsep();
      out_inreg(r, 0);
      break;
    }
    case WH_REGOFF: {
      loc_s l;
      l.key = L_REGOFF;
      l.reg = (int)v.u.l;
      l.off = v.o;
      if (l.reg == -2) {
	l.reg = -1;
	l.off -= locals_offset;
      }
      outn((long)regoff_length(l)); outsep();
      out_regoff(l);
      break;
    }
    default:
      failer("unexpected locate val");
  }
  d_outnl();
  return;
}


static int dw_eval_exp
(exp e, int line_started)
{
  if (line_started)
    outsep();
  else {
    out8();
    line_started = 1;
  }
  switch (name(e)) {
    case name_tag:
    case cont_tag:
    case contvol_tag:
    case reff_tag: {
      loc_s l;
      locate_param = extra_deref = no_location = 0;
      l = find_loc(e);
      if (no_location || extra_deref)
	failer("value unobtainable by DWARF expression");
      switch (l.key) {
	case L_INREG: {
	  out_inreg(l.reg, extra_deref);
	  break;
	}
	case L_REGOFF: {
	  out_regoff(l);
	  break;
	}
	case L_GLOB: {
	  out_glob(l);
	  d_outnl();
	  line_started = 0;
	  break;
	}
	case L_INDIRECT: {
	  out_indirect(e);
	  break;
	}
      }
      break;
    }
    case val_tag:
    case null_tag: {
      if (isbigval(e)) {
	flt64 x;
	int ov;
	x = flt_to_f64(no(e), is_signed(sh(e)), &ov);
	outn((long)(is_signed(sh(e))? DW_OP_const8s : DW_OP_const8u)); d_outnl();
	out32(); outn((long)(x.small)); outsep(); outn((long)(x.big)); d_outnl();
	line_started = 0;
      }
      else
      if (no(e) >= 0 && no(e) < 32)
	outn((long)(DW_OP_lit0 + no(e)));
      else
      if (is_signed(sh(e))) {
	outn((long)DW_OP_consts); outsep();
	sleb128((long)no(e));
      }
      else {
	outn((long)DW_OP_constu); outsep();
	uleb128((unsigned long)no(e));
      }
      break;
    }
    case plus_tag:
    case offset_add_tag: {
      line_started = dw_eval_exp(son(e), line_started);
      if (name(bro(son(e))) == val_tag && !is_signed(sh(e)) && !isbigval(bro(son(e)))) {
	if (line_started)
	  outsep();
	else {
	  out8();
	  line_started = 1;
	}
	outn((long)DW_OP_plus_uconst); outsep();
	uleb128((unsigned long)no(e));
      }
      else {
	line_started = dw_eval_exp(bro(son(e)), line_started);
	if (line_started)
	  outsep();
	else {
	  out8();
	  line_started = 1;
	}
	outn((long)DW_OP_plus);
      }
      break;
    }
    case minus_tag:
    case offset_subtract_tag: {
      line_started = dw_eval_exp(son(e), line_started);
      line_started = dw_eval_exp(bro(son(e)), line_started);
      if (line_started)
	outsep();
      else {
	out8();
	line_started = 1;
      }
      outn((long)DW_OP_minus);
      break;
    }
    case neg_tag:
    case offset_negate_tag: {
      line_started = dw_eval_exp(son(e), line_started);
      if (line_started)
	outsep();
      else {
	out8();
	line_started = 1;
      }
      outn((long)DW_OP_neg);
      break;
    }
    case mult_tag:
    case offset_mult_tag: {
      line_started = dw_eval_exp(son(e), line_started);
      line_started = dw_eval_exp(bro(son(e)), line_started);
      if (line_started)
	outsep();
      else {
	out8();
	line_started = 1;
      }
      outn((long)DW_OP_mul);
      break;
    }
    case div0_tag:
    case div1_tag:
    case div2_tag:
    case offset_div_by_int_tag:
    case offset_div_tag: {
      line_started = dw_eval_exp(son(e), line_started);
      line_started = dw_eval_exp(bro(son(e)), line_started);
      if (line_started)
	outsep();
      else {
	out8();
	line_started = 1;
      }
      outn((long)DW_OP_div);
      break;
    }
    default:
      failer("unsupported operation for DWARF expression");
  }
  return line_started;
}


void dw2_offset_exp
(exp e)
{
  long block_end = next_dwarf_label();
  if (name(sh(e))!= offsethd)
    failer("wrong shape for offset expression");
  dw_at_form(DW_FORM_block2); d_outnl();
  out16(); out_dwf_dist_to_label(block_end); d_outnl();
  if (dw_eval_exp(e, 0))
    d_outnl();
  if (name(sh(e)) == offsethd && al2(sh(e)) < 8) {
    out8(); outn((long)(DW_OP_lit0 + 8)); outsep();
    outn((long)DW_OP_mul); d_outnl();
  }
  out_dwf_label(block_end, 1);
  return;
}


void dw2_cie
(void)
{
  long cie_end;
  cie_pointer = next_dwarf_label();
  cie_end = next_dwarf_label();
  enter_section("debug_frame");
  outnl_comment("Common Information Entry");
  out_dwf_label(cie_pointer, 1);
  out32(); out_dwf_dist_to_label(cie_end); d_outnl();
  out32(); outn((long)DW_CIE_id); d_outnl();
  out8(); outn((long)DW_CIE_MOD_VERSION); d_outnl();
  out_string("DERA/DDC-I");
  out8(); uleb128((unsigned long)framecode_factor); d_outnl();
  out8(); sleb128((long)framedata_factor); d_outnl();
  out8 (); outn ((long)retaddr); d_outnl ();	/* return address column */
  out8(); outn((long)DW_CFA_def_cfa);
	outsep(); uleb128((unsigned long)dw_sp);
	outsep (); uleb128 ((unsigned long)0);	/* CFA is sp at entry point */
	d_outnl();
  out8(); outn((long)DW_CFA_undefined);
	outsep (); uleb128 ((unsigned long)dwarfreg [0]);	/* eax */
	d_outnl();
  out8(); outn((long)DW_CFA_undefined);
	outsep (); uleb128 ((unsigned long)dwarfreg [1]);	/* edx */
	d_outnl();
  out8(); outn((long)DW_CFA_undefined);
	outsep (); uleb128 ((unsigned long)dwarfreg [2]);	/* ecx */
	d_outnl();
  out8(); outn((long)DW_CFA_same_value);
	outsep (); uleb128 ((unsigned long)dwarfreg [3]);	/* ebx */
	d_outnl();
  out8(); outn((long)DW_CFA_same_value);
	outsep (); uleb128 ((unsigned long)dwarfreg [4]);	/* edi */
	d_outnl();
  out8(); outn((long)DW_CFA_same_value);
	outsep (); uleb128 ((unsigned long)dwarfreg [5]);	/* esi */
	d_outnl();
  out8(); outn((long)DW_CFA_same_value);
	outsep (); uleb128 ((unsigned long)dwarfreg [6]);	/* ebp */
	d_outnl();
  out8(); outn((long)DW_CFA_DD_location);
	outsep (); uleb128 ((unsigned long)dw_sp);		/* esp */
	outsep (); outn ((long)2);	/* location block */
	outsep(); outn((long)DW_OP_plus_uconst);
	outsep (); uleb128 ((unsigned long)4);	/* virtual pop return address */
	d_outnl();
  out8(); outn((long)DW_CFA_offset + retaddr);
	outsep (); uleb128 ((unsigned long)0);	/* return address */
	d_outnl();
  dot_align(PTR_SZ/8);
  out_dwf_label(cie_end, 1);
  exit_section();
  return;
}

static void short_advance
(long lo, long hi)
{
  if (lo) {
    out8(); out_dwf_label(hi, 0);  outs(" - "); out_dwf_label(lo, 0);
    outs(" + "); outn((long)DW_CFA_advance_loc); d_outnl();
  }
  else {
    out8(); outn((long)DW_CFA_set_loc); d_outnl();
    out32(); out_dwf_label(hi, 0); d_outnl();
  }
  return;
}

long dw2_start_fde
(long proc_start, long fblab)
{
  long hold_pos;
  fde_end = next_dwarf_label();
  proc_end = next_dwarf_label();
  enter_section("debug_frame");
  outnl_comment("Frame Descriptor Entry");
  out32(); out_dwf_dist_to_label(fde_end); d_outnl();
  out32(); out_dwf_label(cie_pointer, 0); d_outnl();
  out32(); out_dwf_label(proc_start, 0); d_outnl();
  out32(); out_dwf_labdiff(proc_start, proc_end); d_outnl();

  if (callee_size >= 0) {
    unsigned long pop_bytes = 4;
    int n = (remove_struct_ref && has_struct_res(crt_proc_exp))? 32 : 0;
    if ((n += callee_size)!= 0) {
      pop_bytes += (unsigned long)(n/8);
      out8(); outn((long)DW_CFA_DD_location);
	outsep(); uleb128((unsigned long)dw_sp);
	outsep(); outn((long)1 + (long)uleb128_length(pop_bytes));
	outsep(); outn((long)DW_OP_plus_uconst);
	outsep (); uleb128 (pop_bytes);	/* adjust virtual pops */
	d_outnl();
    }
  }
  else {	/* var_callees */
    int extra = (remove_struct_ref && has_struct_res(crt_proc_exp))? 2 : 0;
    out8(); outn((long)DW_CFA_DD_location);
	outsep(); uleb128((unsigned long)dw_sp);
	outsep (); outn ((long)(3 + extra));	/* location block length */
	outsep(); outn((long)DW_OP_plus_uconst);
	outsep (); uleb128 ((unsigned long)4);	/* virtual pop return address */
	outsep (); outn ((long)DW_OP_deref);	/* over callees */
	if (extra) {
	  outsep(); outn((long)DW_OP_plus_uconst);
	  outsep (); uleb128 ((unsigned long)4);	/* pop struct_res */
	}
	d_outnl();
  }

  if (!no_frame) {
    short_advance(proc_start, fblab);
    out8(); outn((long)DW_CFA_def_cfa);
	outsep(); uleb128((unsigned long)dwarfreg[6]);
	outsep (); uleb128 ((unsigned long)4);	/* CFA now relative to %ebp */
	d_outnl();
    out8 (); outn ((long)DW_CFA_offset + dwarfreg[6]); /* %ebp */
	outsep(); uleb128((unsigned long)1); d_outnl();
  }

  hold_pos = out_tell_pos();
  outs(sp50); outs(sp50); outs(sp50); outs(sp50); outs(sp50); outs(sp50); outs(sp50);
  d_outnl();

  exit_section();
  return hold_pos;
}

void dw2_fde_entry
(long dwl0, long dwl1, long dwl2, long dwl3, long dwl4, long dwl8, int space)
{
  long here = dwl0;
  unsigned long up = 0;
  if (!no_frame) {
    here = dwl1;
    ++up;
  }
  if (min_rfree & 0x8) {
    short_advance(here, dwl2);
    here = dwl2;
    out8();
    if (no_frame) {
	outn((long)DW_CFA_DD_def_cfa_inc_offset); outsep();
    }
	outn ((long)DW_CFA_offset + dwarfreg[3]); /* %ebx */
	outsep(); uleb128(++up); d_outnl();
  }
  if (min_rfree & 0x10) {
    short_advance(here, dwl3);
    here = dwl3;
    out8();
    if (no_frame) {
	outn((long)DW_CFA_DD_def_cfa_inc_offset); outsep();
    }
	outn ((long)DW_CFA_offset + dwarfreg[4]); /* %edi */
	outsep(); uleb128(++up); d_outnl();
  }
  if (min_rfree & 0x20) {
    short_advance(here, dwl4);
    here = dwl4;
    out8();
    if (no_frame) {
	outn((long)DW_CFA_DD_def_cfa_inc_offset); outsep();
    }
	outn ((long)DW_CFA_offset + dwarfreg[5]); /* %esi */
	outsep(); uleb128(++up); d_outnl();
  }
  if (no_frame && (min_rfree & 0x40)) {
    short_advance(here, dwl1);
    here = dwl1;
    out8(); outn((long)DW_CFA_DD_def_cfa_inc_offset); outsep();
	outn ((long)DW_CFA_offset + dwarfreg[6]); /* %ebp */
	outsep(); uleb128(++up); d_outnl();
  }
  if (space && no_frame) {
    short_advance(here, dwl8);
    out8(); outn((long)DW_CFA_def_cfa_offset); outsep();
	uleb128((unsigned long)space); d_outnl();
  }
  return;
}

void dw2_untidy_return
(void)
{
	/* we have pushed the return address */
  long here = set_dw_text_label();
  enter_section("debug_frame");
  out8(); outn((long)DW_CFA_set_loc); d_outnl();
  out32(); out_dwf_label(here, 0); d_outnl();
  out8(); outn((long)DW_CFA_remember_state); outsep();
  if (no_frame) {
    outn((long)DW_CFA_DD_def_cfa_inc_offset); d_outnl();
  }
  exit_section();
  return;
}

long dw2_prep_fde_restore_args
(int untidy)
{
  long here;
  if (!untidy) {
    long pos;
    enter_section("debug_frame");
    out8(); outn((long)DW_CFA_remember_state); d_outnl();
    pos = out_tell_pos();
    outs(sp50); outs(sp50); outs(sp50); outs(sp50); outs(sp50); outs(sp50);
    d_outnl();
    d_outnl();
    exit_section();
    return pos;
  }
	/* otherwise */
  here = set_dw_text_label();
  enter_section("debug_frame");
  short_advance((long)0, here);
  out8(); outn((long)DW_CFA_restore + dwarfreg[3]); d_outnl();
  out8(); outn((long)DW_CFA_restore + dwarfreg[4]); d_outnl();
  out8(); outn((long)DW_CFA_restore + dwarfreg[5]); d_outnl();
  out8(); outn((long)DW_CFA_restore + dwarfreg[6]); d_outnl();

  if (!no_frame) {	/* %ebp restored, return address pushed */
    out8(); outn((long)DW_CFA_def_cfa);
	outsep(); uleb128((unsigned long)dw_sp);
	outsep (); uleb128 ((unsigned long)0);	/* temp CFA */
	d_outnl();
    out8(); outn((long)DW_CFA_undefined);
	outsep(); uleb128((unsigned long)dw_sp);
	d_outnl();
  }
  exit_section();
  return 0;
}

void dw2_fde_restore_args
(long dwl0, long dwl1, long dwl2, long dwl3, long dwl4, int space)
{
  long here = 0;
  if (no_frame && dwl0) {
    short_advance(here, dwl0);
    here = dwl0;
    out8(); outn((long)DW_CFA_def_cfa_offset); outsep();
	uleb128((unsigned long)space); d_outnl();
  }
  if (no_frame && (min_rfree & 0x40)) {
    short_advance(here, dwl1);
    here = dwl1;
    out8(); outn((long)DW_CFA_DD_def_cfa_dec_offset); outsep();
	outn ((long)DW_CFA_restore + dwarfreg[6]); /* %ebp */
	d_outnl();
  }
  if (min_rfree & 0x20) {
    short_advance(here, dwl2);
    here = dwl2;
    out8();
    if (no_frame) {
	outn((long)DW_CFA_DD_def_cfa_dec_offset); outsep();
    }
	outn ((long)DW_CFA_restore + dwarfreg[5]); /* %esi */
	d_outnl();
  }
  if (min_rfree & 0x10) {
    short_advance(here, dwl3);
    here = dwl3;
    out8();
    if (no_frame) {
	outn((long)DW_CFA_DD_def_cfa_dec_offset); outsep();
    }
	outn ((long)DW_CFA_restore + dwarfreg[4]); /* %edi */
	d_outnl();
  }
  if (min_rfree & 0x8) {
    short_advance(here, dwl4);
    here = dwl4;
    out8();
    if (no_frame) {
	outn((long)DW_CFA_DD_def_cfa_dec_offset); outsep();
    }
	outn ((long)DW_CFA_restore + dwarfreg[3]); /* %ebx */
	d_outnl();
  }
  if (!no_frame) {
    short_advance(here, dwl1);
    here = dwl1;
    out8 (); outn ((long)DW_CFA_restore + dwarfreg[6]); /* %ebp */
	outsep(); outn((long)DW_CFA_def_cfa);
	outsep(); uleb128((unsigned long)dw_sp);
	outsep (); uleb128 ((unsigned long)0);	/* CFA is sp at entry point */
	d_outnl();
  }
  UNUSED(here);
}

void dw2_after_fde_exit
(long here)
{
  out_dwf_label(here, 1);
  enter_section("debug_frame");
  short_advance((long)0, here);
  out8(); outn((long)DW_CFA_restore_state); d_outnl();
  exit_section();
  return;
}

void dw2_track_push
(void)
{
  long here = set_dw_text_label();
  enter_section("debug_frame");
  short_advance((long)0, here);
  out8(); outn((long)DW_CFA_DD_def_cfa_inc_offset); d_outnl();
  exit_section();
  return;
}

void dw2_track_pop
(void)
{
  long here = set_dw_text_label();
  enter_section("debug_frame");
  short_advance((long)0, here);
  out8(); outn((long)DW_CFA_DD_def_cfa_dec_offset); d_outnl();
  exit_section();
  return;
}

void dw2_track_sp
(void)
{
  long here = set_dw_text_label();
  enter_section("debug_frame");
  short_advance((long)0, here);
  out8(); outn((long)DW_CFA_DD_def_cfa_fixed_offset); d_outnl();
  out32(); outn((long)((extra_stack - stack_dec) / 8));
    outs("+");
    outs(local_prefix);
    outs("disp");
    outn((long)crt_proc_id);
  d_outnl();
  exit_section();
  return;
}


void dw2_complete_fde
(void)
{
  out_dwf_label(proc_end, 1);
  enter_section("debug_frame");
  dot_align(PTR_SZ/8);
  out_dwf_label(fde_end, 1);
  exit_section();
  return;
}


void dw2_start_extra_bit
(exp body)
{
  dg_info di = new_dg_info(DGA_EXTRA);
  di->data.i_scope.start = next_dwarf_label();
  di->data.i_scope.end = next_dwarf_label();
  di->more = dgf(body);
  dgf(body) = di;
  return;
}

void dw2_end_extra_bit
(exp body)
{
  UNUSED(body);
  return;
}


static exp lab_mark_list;

static void mark_lab
(exp labst)
{
  if (!dg_labmark(labst)) {
    set_dg_labmark(labst);
    if (son(son(labst))!= NULL)
      failer("strange labst");
    son(son(labst)) = lab_mark_list;
    lab_mark_list = labst;
  }
  return;
}

static void trace_branch_aux
(exp whole, exp e)
{
  exp t;
  switch (name(e)) {
    case test_tag:
    case goto_tag: {
      if (!intnl_to(whole, pt(e)))
	mark_lab(pt(e));
      break;
    }
    case case_tag: {
      t = bro(son(e));
      for (;;) {
	if (!intnl_to(whole, pt(t)))
	  mark_lab(pt(t));
	if (last(t))break;
	t = bro(t);
      }
      break;
    }
    case labst_tag: {
      t = final_dest(e);
      if (!intnl_to(whole, t))
	mark_lab(t);
      break;
    }
    case name_tag:
    case env_offset_tag:
    case general_env_offset_tag:
      return;
  }
  t = son(e);
  if (t) {
    for (;;) {
      trace_branch_aux(whole, t);
      if (last(t) || name(e) == case_tag)break;
      t = bro(t);
    }
  }
  return;
}

void trace_dw_branch_exits
(exp e)
{
  lab_mark_list = NULL;
  trace_branch_aux(e, e);
  while (lab_mark_list) {
    exp labst = lab_mark_list;
    exp dest = final_dest(labst);
    clear_dg_labmark(labst);
    lab_mark_list = son(son(labst));
    son(son(labst)) = NULL;
    IGNORE dw_entry(dwe_break,(long)0);
    out32(); out_code_label((long)ptno(pt(son(dest)))); d_outnl();
  }
  return;
}



int dw_loc_equivalence
(exp a, exp b)
{
  return eq_where_exp(a, b, 1, 0);
}

typedef struct
{
  dg_name	nm;
  long		start;
  long		end;
} dw_regassn;

typedef struct
{
  dg_name	alloc;
  void *	share_set;
  dw_regassn	assn[2];
} dw_regdata;

#define TRACKREGS no_fixed_regs

static dw_regdata regassns[TRACKREGS];


void dw_allocated
(dg_name nm, exp id)
{
  int reg = no(id);
  if (!isglob(id) && ptno(id) == reg_pl && reg < TRACKREGS) {
    dw_close_regassn(reg, 0);
    dw_close_regassn(reg, 1);
    regassns[reg].alloc = nm;
    regassns[reg].share_set = (void *)0;
  }
  return;
}

void dw_deallocated
(dg_name nm)
{
  int i;
  for (i=0; i<TRACKREGS; i++) {
    if (regassns[i].alloc == nm) {
      dw_close_regassn(i, 0);
      dw_close_regassn(i, 1);
      regassns[i].alloc = (dg_name)0;
      regassns[i].share_set = (void *)0;
    }
  }
  return;
}

void dw_all_deallocated		/* initialisation */
(void)
{
  int i;
  for (i=0; i<TRACKREGS; i++) {
    dw_regassn * a = & (regassns[i].assn[0]);
    dw_regassn * b = & (regassns[i].assn[1]);
    regassns[i].alloc = (dg_name)0;
    regassns[i].share_set = (void *)0;
    a->start = a->end = b->start = b->end = (long)0;
  }
  return;
}


int dw_ignore_used_regassn = 0;

void dw_init_regassn
(int reg, int x)
{
  if (reg < TRACKREGS) {
    dg_name nm = find_equiv_object((!x ? crt_reg_record[reg].first_dest
				: crt_reg_record[reg].second_dest), 0);
    if (nm) {
      dw_regassn * a = & (regassns[reg].assn[x]);
      a->nm = nm;
      a->start = set_dw_text_label();
      a->end = (long)0;
    }
  }
  return;
}

void dw_used_regassn
(int reg, int x)
{
  if (reg < TRACKREGS && regassns[reg].assn[x].start)
    regassns[reg].assn[x].end = set_dw_text_label();
  return;
}

void dw_close_regassn
(int reg, int x)
{
  dw_regassn * a;
  if (dw_ignore_used_regassn || reg >= TRACKREGS)
    return;
  a = & (regassns[reg].assn[x]);
  if (a->end) {
    if (!regassns[reg].share_set) {
      regassns[reg].share_set = (void *)
		dw_new_regshare(regassns[reg].alloc, dwarfreg[reg]);
    }
    dw_add_regshare(regassns[reg].share_set, a->nm,
		a->start, a->end);
    a->end = (long)0;
    if (!regassns[reg].alloc && !regassns[reg].assn[1-x].start)
      regassns[reg].share_set = (void *)0;
  }
  a->start = (long)0;
  return;
}

#else

int dw2_dummy; /* to avoid an empty translation unit */

#endif
