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
#include "common_types.h"
#include "dw2_config.h"
#include "dw2_basic.h"
#include "dw2_codes.h"
#include "dw2_iface.h"
#include "szs_als.h"
#include "tags.h"
#include "basicread.h"
#include "dw2_abbrev_vn.h"


#define entry_names_wanted
#include "dw2_entries.h"
#undef entry_names_wanted


static char * sep = ", ";


void
uleb128(unsigned long value)
{
	int byt;
	for (;;) {
		byt = value & 127;
		value >>= 7;
		if (value == 0) {
			outn ((long)byt);
			return;
		}
		outn ((long)byt | 128);
		outs (sep);
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
		byt = (unsigned long) value & 127;
		value >>= 7;
		if (negative)
			/* sign extend, since C doesn't imply arithmetic shift */
			value |= - (1 << ((sizeof(value)*8) - 7));
		/* sign bit of byte is 2nd high order bit (0x40) */
		if (value == - (long) ((byt & 0x40) != 0)) {
			outn ((long)byt);
			return;
		}
		outn ((long)byt | 128);
		outs (sep);
	}
}

int
sleb128_length(long value)
{
	int op = 1;
	int negative = (value < 0);
	int byt;
	for (;;) {
		byt = (unsigned long) value & 127;
		value >>= 7;
		if (negative)
			/* sign extend, since C doesn't imply arithmetic shift */
			value |= - (1 << ((sizeof(value)*8) - 7));
		if (value == - (long) ((byt & 0x40) != 0)) {
			return op;
		}
		op++;
	}
}

void
set_attribute(int nm, int form)
{
	out8 (); uleb128 ((unsigned long)nm);
	if (form || !nm) {
		outs (sep); uleb128 ((unsigned long) form);
	}
	d_outnl ();
	return;
}

static long info_end;
static long pubnames_end;
static long aranges_end;


void
do_compunit_header()
{
	info_end = next_dwarf_label ();
	pubnames_end = next_dwarf_label ();
	aranges_end = next_dwarf_label ();
	enter_section ("debug_info");
	out_dwf_label (dw_info_start, 1);
	outnl_comment("Compilation Unit Header");
	out32 (); out_dwf_dist_to_label (info_end); d_outnl ();
	out16 (); outn ((long)DWARF_MOD_VERSION); d_outnl ();
	out32 (); outs (abbrev_name); d_outnl ();
	out8 (); outn ((long)PTR_SZ/8); d_outnl ();
	exit_section ();
	enter_section ("debug_pubnames");
	out32 (); out_dwf_dist_to_label (pubnames_end); d_outnl ();
	out16 (); outn ((long)DWARF_MOD_VERSION); d_outnl ();
	out32 (); out_dwf_label (dw_info_start, 0); d_outnl ();
	out32 (); out_dwf_labdiff (dw_info_start, info_end); d_outnl ();
	exit_section ();
	enter_section ("debug_aranges");
	out32 (); out_dwf_dist_to_label (aranges_end); d_outnl ();
	out16 (); outn ((long)DWARF_MOD_VERSION); d_outnl ();
	out32 (); out_dwf_label (dw_info_start, 0); d_outnl ();
	out8 (); outn ((long)PTR_SZ/8); d_outnl ();
	out8 (); outn ((long)0); d_outnl ();
	dot_align (PTR_SZ/4);
	exit_section ();
	return;
}

void
close_compunit_info()
{
	enter_section ("debug_info");
	out_dwf_label (info_end, 1);
#ifdef NEEDS_DEBUG_ALIGN
	dot_align (4);
#endif
	exit_section ();
	enter_section ("debug_pubnames");
	out32 (); outn ((long)0); d_outnl ();
	out_dwf_label (pubnames_end, 1);
#ifdef NEEDS_DEBUG_ALIGN
	dot_align (4);
#endif
	exit_section ();
	enter_section ("debug_aranges");
	out32 (); outn ((long)0); d_outnl ();
	out32 (); outn ((long)0); d_outnl ();
	out_dwf_label (aranges_end, 1);
	exit_section ();
}


void
dw_sibling_end()
{
	out8 (); uleb128 ((unsigned long)0); 
	outnl_comment ("sibling end");
	return;
}

void
dw_at_address(long lab)
{
	out32 (); out_dwf_label (lab, 0); d_outnl ();
	return;
}

void
dw_at_ext_lab(ext_lab lab)
{
	out32 ();
	switch (lab.k) {
    case LAB_STR:
		outs (lab.u.s);
		break;
    case LAB_CODE:
		out_code_label (lab.u.l);
		break;
    case LAB_D:
		out_dwf_label (lab.u.l, 0);
		break;
    default:
		failer ("unset label");
	}
	d_outnl ();
	return;
}

void
dw_set_ext_lab(ext_lab lab)
{
	switch (lab.k) {
    case LAB_STR:
		out_ext_label (lab.u.s);
		break;
    case LAB_D:
		out_dwf_label (lab.u.l, 1);
		break;
    default:
		failer ("unexpected set label");
	}
	return;
}

void
dw_at_ext_address(dg_tag dt)
{
	if (dt->outref.k == NO_LAB) {
		dt->outref.k = LAB_D;
		dt->outref.u.l = next_dwarf_label ();
	}
	dw_at_ext_lab (dt->outref);
	return;
}

void
set_ext_address(dg_tag dt)
{
	if (dt->outref.k == NO_LAB) {
		dt->outref.k = LAB_D;
		dt->outref.u.l = next_dwarf_label ();
	}
	dw_set_ext_lab (dt->outref);
	return;
}

void
dw_at_abstract_lab(dg_tag dt)
{
	if (!dt->abstract_lab)
		dt->abstract_lab = next_dwarf_label ();
	out32 ();
	out_dwf_label (dt->abstract_lab, 0);
	d_outnl ();
	return;
}

void
set_abstract_lab(dg_tag dt)
{
	if (!dt->abstract_lab)
		dt->abstract_lab = next_dwarf_label ();
	out_dwf_label (dt->abstract_lab, 1);
	return;
}

void
dw_at_string(char* s)
{
	if (!s) s = "";
	out_string (s);
	return;
}

void
dw_at_form(int f)
{
	out8 ();
	uleb128 ((unsigned long)f);
	return;
}

void
dw_at_data(int n, long d)
{
	switch (n) {
    case 1: {
		out8 ();
		break;
    }
    case 2: {
		out16 ();
		break;
    }
    case 4: {
		out32 ();
		break;
    }
    default:
		failer ("dwarf data size not supported");
	}
	outn (d); d_outnl ();
	return;
}

void
dw_at_udata(unsigned long n)
{
	out8 (); uleb128 (n); d_outnl ();
	return;
}

void
dw_at_sdata(long n)
{
	out8 (); sleb128 (n); d_outnl ();
	return;
}

void
dw_at_flag(int x)
{
	out8 (); outn ((long)x); d_outnl ();
	return;
}

void
dw_at_decl(short_sourcepos p)
{
	out8 (); uleb128 ((unsigned long)(p.file ? p.file->index : 0));
	outs(sep); uleb128 ((unsigned long)p.line);
	outs(sep); uleb128 ((unsigned long)p.column);
	d_outnl ();
	return;
}

void
dw_no_locate()
{
	out8 (); outn ((long)0);
	outnl_comment ("discarded variable");
	return;
}

void
dw_locate_offset(int n)
{
	out8(); outn ((long)(1 + uleb128_length((unsigned long)n))); outs(sep);
	outn ((long)DW_OP_plus_uconst); outs (sep);
	uleb128 ((unsigned long)n); d_outnl ();
	return;
}

static char* bad_refloc = "unimplemented relative location";

static int
refloc_length(exp e, exp id)
{
	switch (name(e)) {
    case name_tag: {
		if (son(e) != id)
			failer (bad_refloc);
		if (no(e) == 0)
			return (0);
		return (1 + uleb128_length((unsigned long)no(e)/8));
    }
    case cont_tag: {
		return (refloc_length (son(e), id) + 1);
    }
    case reff_tag: {
		if (no(e)<0)
			failer (bad_refloc);
		return (refloc_length (son(e), id) + 1 +
				uleb128_length((unsigned long)no(e)/8));
    }
    default: {
		failer (bad_refloc);
		return (0);
    }
	}
}

static void
out_refloc(exp e, exp id)
{
	switch (name(e)) {
    case name_tag: {
		if (son(e) != id)
			failer (bad_refloc);
		outs (sep); outn ((long)DW_OP_plus_uconst);
		outs (sep); uleb128 ((unsigned long)no(e)/8);
		return;
    }
    case cont_tag: {
		out_refloc (son(e), id);
		outs (sep); outn ((long)DW_OP_deref);
		return;
    }
    case reff_tag: {
		if (no(e)<0)
			failer (bad_refloc);
		out_refloc (son(e), id);
		outs (sep); outn ((long)DW_OP_plus_uconst);
		outs (sep); uleb128 ((unsigned long)no(e)/8);
		return;
    }
    default:
		failer (bad_refloc);
	}
}

void
dw_locate_reloffset(exp e)
{
	int length;
	if (name(e) != ident_tag) {
		failer (bad_refloc);
		return;
	}
	length = refloc_length (bro(son(e)), e);
	out8();
	if (length == 0) {
		outn ((long)1);
		outs(sep); outn ((long)DW_OP_nop);
	}
	else {
		outn ((long)length);
		out_refloc (bro(son(e)), e);
	}
	d_outnl ();
	return;
}

void
dw_at_distance(long lo, long hi)
{
	out16 (); out_dwf_labdiff (lo, hi); d_outnl ();
	return;
}

long last_text_label = 0;

long
set_dw_text_label()
{
	if (any_output) {
		last_text_label = next_dwarf_label ();
		out_dwf_label (last_text_label, 1);
		reset_any_output;
	}
	return last_text_label;
}

void
out_text_label(long n)
{
	out_dwf_label (n, 1);
	last_text_label = n;
	return;
}

void
out_loc_range(long start, long end, int inclusive)
{
	/* for location list */
	out32 (); out_dwf_labdiff (dw_text_start, start); d_outnl ();
	out32 (); out_dwf_labdiff (dw_text_start, end);
	if (inclusive) {
		outs (" + ");
		outn ((long)min_instr_size);
	}
	d_outnl ();
	return;
}
