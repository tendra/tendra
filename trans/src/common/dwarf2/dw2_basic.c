/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "dw2_config.h"

#include "exptypes.h"
#include "szs_als.h"
#include "expmacs.h"

#include <reader/basicread.h>

#include <construct/tags.h>
#include <construct/flags.h>

#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_abbrev_vn.h>

#define entry_names_wanted
#include <dwarf2/dw2_entries.h>
#undef entry_names_wanted


static char *sep = ", ";


void
uleb128(unsigned long value)
{
	int byt;
	for (;;) {
		byt = value & 127;
		value >>= 7;
		if (value == 0) {
			outn((long)byt);
			return;
		}
		outn((long)byt | 128);
		outs(sep);
	}
}


int
uleb128_length(unsigned long value)
{
	int op = 1;
	for (;;) {
		value >>= 7;
		if (value == 0) {
			return op;
		}
		op++;
	}
}


void
sleb128(long value)
{
	int negative = (value < 0);
	int byt;
	for (;;) {
		byt = (unsigned long)value & 127;
		value >>= 7;
		if (negative) {
			/* sign extend, since C doesn't imply arithmetic
			 * shift */
			value |= - (1 << ((sizeof(value) * 8) - 7));
		}
		/* sign bit of byte is 2nd high order bit (0x40) */
		if (value == - (long)((byt & 0x40) != 0)) {
			outn((long)byt);
			return;
		}
		outn((long)byt | 128);
		outs(sep);
	}
}


int
sleb128_length(long value)
{
	int op = 1;
	int negative = (value < 0);
	int byt;
	for (;;) {
		byt = (unsigned long)value & 127;
		value >>= 7;
		if (negative) {
			/* sign extend, since C doesn't imply arithmetic
			 * shift */
			value |= - (1 << ((sizeof(value) * 8) - 7));
		}
		if (value == - (long)((byt & 0x40) != 0)) {
			return op;
		}
		op++;
	}
}


void
set_attribute(int nm, int form)
{
	out8();
	uleb128((unsigned long)nm);
	if (form || !nm) {
		outs(sep);
		uleb128((unsigned long) form);
	}
	d_outnl();
	return;
}

static long info_end;
static long pubnames_end;
static long aranges_end;


void
do_compunit_header(void)
{
	info_end = next_dwarf_label();
	pubnames_end = next_dwarf_label();
	aranges_end = next_dwarf_label();
	enter_section("debug_info");
	out_dwf_label(dw_info_start, 1);
	outnl_comment("Compilation Unit Header");
	out32();
	out_dwf_dist_to_label(info_end);
	d_outnl();
	out16();
	outn((long)DWARF_MOD_VERSION);
	d_outnl();
	out32();
	outs(abbrev_name);
	d_outnl();
	out8();
	outn((long)PTR_SZ/8);
	d_outnl();
	exit_section();
	enter_section("debug_pubnames");
	out32();
	out_dwf_dist_to_label(pubnames_end);
	d_outnl();
	out16();
	outn((long)DWARF_MOD_VERSION);
	d_outnl();
	out32();
	out_dwf_label(dw_info_start, 0);
	d_outnl();
	out32();
	out_dwf_labdiff(dw_info_start, info_end);
	d_outnl();
	exit_section();
	enter_section("debug_aranges");
	out32();
	out_dwf_dist_to_label(aranges_end);
	d_outnl();
	out16();
	outn((long)DWARF_MOD_VERSION);
	d_outnl();
	out32();
	out_dwf_label(dw_info_start, 0);
	d_outnl();
	out8();
	outn((long)PTR_SZ/8);
	d_outnl();
	out8();
	outn((long)0);
	d_outnl();
	dot_align(PTR_SZ/4);
	exit_section();
	return;
}


void
close_compunit_info(void)
{
	enter_section("debug_info");
	out_dwf_label(info_end, 1);
	if (needs_debug_align) {
		dot_align(4);
	}
	exit_section();
	enter_section("debug_pubnames");
	out32();
	outn((long)0);
	d_outnl();
	out_dwf_label(pubnames_end, 1);
	if (needs_debug_align) {
		dot_align(4);
	}
	exit_section();
	enter_section("debug_aranges");
	out32();
	outn((long)0);
	d_outnl();
	out32();
	outn((long)0);
	d_outnl();
	out_dwf_label(aranges_end, 1);
	exit_section();
}


void
dw_sibling_end(void)
{
	out8();
	uleb128((unsigned long)0);
	outnl_comment("sibling end");
	return;
}


void
dw_at_address(long lab)
{
	out32();
	out_dwf_label(lab, 0);
	d_outnl();
	return;
}


void
dw_at_ext_lab(ext_lab lab)
{
	out32();
	switch (lab.k) {
	case LAB_STR:
		outs(lab.u.s);
		break;
	case LAB_CODE:
		out_code_label(lab.u.l);
		break;
	case LAB_D:
		out_dwf_label(lab.u.l, 0);
		break;
	default:
		failer("unset label");
	}
	d_outnl();
	return;
}


void
dw_set_ext_lab(ext_lab lab)
{
	switch (lab.k) {
	case LAB_STR:
		out_ext_label(lab.u.s);
		break;
	case LAB_D:
		out_dwf_label(lab.u.l, 1);
		break;
	default:
		failer("unexpected set label");
	}
	return;
}


void
dw_at_ext_address(dg_tag dt)
{
	if (dt->outref.k == NO_LAB) {
		dt->outref.k = LAB_D;
		dt->outref.u.l = next_dwarf_label();
	}
	dw_at_ext_lab(dt->outref);
	return;
}


void
set_ext_address(dg_tag dt)
{
	if (dt->outref.k == NO_LAB) {
		dt->outref.k = LAB_D;
		dt->outref.u.l = next_dwarf_label();
	}
	dw_set_ext_lab(dt->outref);
	return;
}


void
dw_at_abstract_lab(dg_tag dt)
{
	if (!dt->abstract_lab) {
		dt->abstract_lab = next_dwarf_label();
	}
	out32();
	out_dwf_label(dt->abstract_lab, 0);
	d_outnl();
	return;
}


void
set_abstract_lab(dg_tag dt)
{
	if (!dt->abstract_lab) {
		dt->abstract_lab = next_dwarf_label();
	}
	out_dwf_label(dt->abstract_lab, 1);
	return;
}


void
dw_at_string(char* s)
{
	if (!s) {
		s = "";
	}
	out_string(s);
	return;
}


void
dw_at_form(int f)
{
	out8();
	uleb128((unsigned long)f);
	return;
}


void
dw_at_data(int n, long d)
{
	switch (n) {
	case 1: {
		out8();
		break;
	}
	case 2: {
		out16();
		break;
	}
	case 4: {
		out32();
		break;
	}
	default:
		failer("dwarf data size not supported");
	}
	outn(d);
	d_outnl();
	return;
}


void
dw_at_udata(unsigned long n)
{
	out8();
	uleb128(n);
	d_outnl();
	return;
}


void
dw_at_sdata(long n)
{
	out8();
	sleb128(n);
	d_outnl();
	return;
}


void
dw_at_flag(int x)
{
	out8();
	outn((long)x);
	d_outnl();
	return;
}


void
dw_at_decl(short_sourcepos p)
{
	out8();
	uleb128((unsigned long)(p.file ? p.file->index : 0));
	outs(sep);
	uleb128((unsigned long)p.line);
	outs(sep);
	uleb128((unsigned long)p.column);
	d_outnl();
	return;
}


void
dw_no_locate(void)
{
	out8();
	outn((long)0);
	outnl_comment("discarded variable");
	return;
}


void
dw_locate_offset(int n)
{
	out8();
	outn((long)(1 + uleb128_length((unsigned long)n)));
	outs(sep);
	outn((long)DW_OP_plus_uconst);
	outs(sep);
	uleb128((unsigned long)n);
	d_outnl();
	return;
}


static char *bad_refloc = "unimplemented relative location";

static int
refloc_length(exp e, exp id)
{
	switch (name(e)) {
	case name_tag:
		if (son(e) != id) {
			failer(bad_refloc);
		}
		if (no(e) == 0) {
			return 0;
		}
		return 1 + uleb128_length((unsigned long)no(e) / 8);
	case cont_tag:
		return refloc_length(son(e), id) + 1;
	case reff_tag:
		if (no(e) <0) {
			failer(bad_refloc);
		}
		return refloc_length(son(e), id) + 1 +
		       uleb128_length((unsigned long)no(e) / 8);
	default:
		failer(bad_refloc);
		return 0;
	}
}


static void
out_refloc(exp e, exp id)
{
	switch (name(e)) {
	case name_tag:
		if (son(e) != id) {
			failer(bad_refloc);
		}
		outs(sep);
		outn((long)DW_OP_plus_uconst);
		outs(sep);
		uleb128((unsigned long)no(e) /8);
		return;
	case cont_tag:
		out_refloc(son(e), id);
		outs(sep);
		outn((long)DW_OP_deref);
		return;
	case reff_tag:
		if (no(e) <0) {
			failer(bad_refloc);
		}
		out_refloc(son(e), id);
		outs(sep);
		outn((long)DW_OP_plus_uconst);
		outs(sep);
		uleb128((unsigned long)no(e) /8);
		return;
	default:
		failer(bad_refloc);
	}
}


void
dw_locate_reloffset(exp e)
{
	int length;
	if (name(e) != ident_tag) {
		failer(bad_refloc);
		return;
	}
	length = refloc_length(bro(son(e)), e);
	out8();
	if (length == 0) {
		outn((long)1);
		outs(sep);
		outn((long)DW_OP_nop);
	} else {
		outn((long)length);
		out_refloc(bro(son(e)), e);
	}
	d_outnl();
	return;
}


void
dw_at_distance(long lo, long hi)
{
	out16();
	out_dwf_labdiff(lo, hi);
	d_outnl();
	return;
}


long last_text_label = 0;

long
set_dw_text_label(void)
{
	if (any_output) {
		last_text_label = next_dwarf_label();
		out_dwf_label(last_text_label, 1);
		reset_any_output;
	}
	return last_text_label;
}


void
out_text_label(long n)
{
	out_dwf_label(n, 1);
	last_text_label = n;
	return;
}


void
out_loc_range(long start, long end, int inclusive)
{
	/* for location list */
	out32();
	out_dwf_labdiff(dw_text_start, start);
	d_outnl();
	out32();
	out_dwf_labdiff(dw_text_start, end);
	if (inclusive) {
		outs(" + ");
		outn((long)min_instr_size);
	}
	d_outnl();
	return;
}
