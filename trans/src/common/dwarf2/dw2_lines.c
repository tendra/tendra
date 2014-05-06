/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <string.h>

#include <shared/check.h>

#include <construct/flags.h>

#include <local/dw2_config.h>

#ifdef NEWDIAGS
#include <newdiag/dg_globs.h>
#else
#include <diag/dg_globs.h>
#endif

#include <dwarf2/dw2_lines.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_iface.h>

#include <local/szs_als.h>


/* values used in statement program prologue */

#define n_statprog_ops 9
static short statprog_op_args[n_statprog_ops] = {
	0, 1, 1, 1, 1, 0, 0, 0, 1
};

#define default_is_stmt 0
#define opcode_base	(n_statprog_ops + 1)

/* VARIABLES */

static long current_ad_label = -1;
static long current_ad_count = -1;
static long current_file = 1;
static long current_line = 1;
static long current_col = 0;
static long current_is_stmt = 0;
static long prev_ad_label = -1;
static long prev_ad_count = -1;
static long prev_file = 1;
static long prev_line = 1;
static long prev_col = 0;
static long prev_is_stmt = default_is_stmt;

static char *sep = ", ";


void
do_statprog_prologue(long l_start, long l_end)
{
	dg_filename f_list = all_files;
	dg_filename f_trace;
	int i;
	long prologue_end = next_dwarf_label();
	enter_section("debug_line");
	outnl_comment("Statement Program Prologue");
	out_dwf_label(l_start, 1);
	out32();
	out_dwf_dist_to_label(l_end);
	d_outnl();
	out16();
	outn((long)DWARF_MOD_VERSION);
	d_outnl();
	out32();
	out_dwf_dist_to_label(prologue_end);
	d_outnl();
	out8();
	outn((long)min_instr_size);
	d_outnl();
	out8();
	outn((long)default_is_stmt);
	d_outnl();
	out8();
	outn((long)dw_line_base);
	d_outnl();
	out8();
	outn((long)dw_line_range);
	d_outnl();
	out8();
	outn((long)opcode_base);
	d_outnl();
	out8();
	for (i = 1 ;; i++) {
		outn((long)statprog_op_args[i-1]);
		if (i == n_statprog_ops) {
			break;
		}
		outs(sep);
	}
	d_outnl();
	f_list = all_files;
	i = 0;
	while (f_list) {
		/* output directories */
		f_trace = all_files;
		while (f_trace != f_list) {
			if (!strcmp(f_list->file_path, f_trace->file_path) &&
			    !strcmp(f_list->file_host, f_trace->file_host)) {
				break;
			}
			f_trace = f_trace->another;
		}
		if (f_trace == f_list) {
			if (f_list->file_path[0] || f_list->file_host[0]) {
				dw_out_path(f_list, 0);
				f_list->index = ++i;
			} else {
				f_list->index = 0;
			}
		} else {
			f_list->index = f_trace->index;
		}
		f_list = f_list->another;
	}
	/* end of directories */
	out_string ("");
	f_list = all_files;
	i = 0;
	while (f_list) {
		/* output file names */
		if (f_list->file_name[0]) {
			time_t t = (time_t)f_list->file_dat;
			out_string(f_list->file_name);
			out8();
			uleb128((unsigned long)f_list->index);	/* directory */
			d_outnl();
			out8();
			uleb128((unsigned long)(f_list->file_dat));
			outnl_comment(ctime(&t));
			out8();
			uleb128((unsigned long)0);	/* unknown length */
			d_outnl();
			f_list->index = ++i;
		} else {
			f_list->index = 0;
		}
		f_list = f_list->another;
	}
	/* end of file names */
	out_string ("");
	out_dwf_label(prologue_end, 1);
	exit_section();
	dw2_cie();
	return;
}


static void
ext_opcode(int op, long arg_length, long align_lab)
{
	out8();
	outn((long)0);
	outs(sep);
	if (needs_debug_align && align_lab) {
		out_dwf_label(align_lab, 0);
		outs (" - . - 1");		/* OK for arg_length < 127 */
	} else
		uleb128((unsigned long)arg_length + 1);
	outs(sep);
	outn((long)op);
	d_outnl();
	UNUSED(align_lab);
}


static void
update_statprog(void)
{
	long lineinc = current_line - prev_line;
	long ad_inc = 0;
	long special;
	if (current_ad_label < 0)
		return;
	enter_section("debug_line");
	if (prev_ad_label < 0) {
		long align_lab = 0;
		if (needs_debug_align) {
			align_lab = next_dwarf_label();
		}
		ext_opcode(DW_LNE_set_address, (long)PTR_SZ / 8, align_lab);
		out32();
		out_dwf_label(current_ad_label, 0);
		if (current_ad_count) {
			outs(" + ");
			outn(current_ad_count * min_instr_size);
		}
		d_outnl();
		if (needs_debug_align) {
			out_dwf_label(align_lab, 1);
		}
	} else if (prev_ad_label != current_ad_label) {
		out8();
		outn((long)DW_LNS_fixed_advance_pc);
		d_outnl();
		out16();
		out_dwf_label(current_ad_label, 0);
		outs(" - ");
		out_dwf_label(prev_ad_label, 0);
		if (current_ad_count != prev_ad_count) {
			outs(" + ");
			outn((current_ad_count - prev_ad_count) *
			     min_instr_size);
		}
		d_outnl();
	} else {
		ad_inc = current_ad_count - prev_ad_count;
	}
	prev_ad_label = current_ad_label;
	prev_ad_count = current_ad_count;
	if (current_file != prev_file) {
		out8();
		outn((long)DW_LNS_set_file);
		outs(sep);
		uleb128((unsigned long)current_file);
		d_outnl();
		prev_file = current_file;
	}
	if (current_is_stmt != prev_is_stmt) {
		out8();
		outn((long)DW_LNS_negate_stmt);
		d_outnl();
		prev_is_stmt = current_is_stmt;
	}
	if (current_col != prev_col) {
		out8();
		outn((long)DW_LNS_set_column);
		outs(sep);
		uleb128((unsigned long)current_col);
		d_outnl();
		prev_col = current_col;
	}
	if (lineinc < dw_line_base ||
	    lineinc >= (dw_line_base + dw_line_range)) {
		out8();
		outn((long)DW_LNS_advance_line);
		outs(sep);
		sleb128(lineinc);
		d_outnl();
		lineinc = 0;
	}
	special = (lineinc - dw_line_base) + (dw_line_range * ad_inc) +
	    opcode_base;
	if (special > 255) {
		out8();
		outn((long)DW_LNS_advance_pc);
		outs(sep);
		uleb128((unsigned long)ad_inc);
		d_outnl();
		special = (lineinc - dw_line_base) + opcode_base;
	}
	out8();
	if (special == (opcode_base - dw_line_base)) {
		outn((long)DW_LNS_copy);
	} else {
		outn(special);
	}
	outnl_comment_i("Line", current_line);
	prev_line = current_line;
	exit_section();
	return;
}


void
dw2_source_mark(short_sourcepos pos, int is_stmt)
{
	/* must be within text segment */
	long newlab = 0;
	if (current_ad_label < 0 || current_ad_label != last_text_label ||
	    instr_count < 0) {
		newlab = set_dw_text_label();
	}
	if (newlab || instr_count != current_ad_count ||
	    pos.file->index != current_file) {
		update_statprog();
	}
	if (newlab) {
		current_ad_label = newlab;
	}
	current_ad_count = instr_count;
	current_file = pos.file->index;
	current_line = pos.line;
	current_col = (long)pos.column;
	current_is_stmt = (long)is_stmt;
	return;
}


void
dw2_start_basic_block(void)
{
	/* must be within text segment */
	long newlab = 0;
	if (current_ad_label < 0 || current_ad_label != last_text_label ||
	    instr_count < 0) {
		newlab = set_dw_text_label();
	}
	if (newlab || instr_count) {
		update_statprog();
	}
	if (newlab) {
		current_ad_label = newlab;
	}
	current_ad_count = instr_count;
	enter_section("debug_line");
	out8();
	outn((long)DW_LNS_set_basic_block);
	d_outnl();
	exit_section();
	return;
}


void
close_statprog(long l_end)
{
	if (current_ad_label < 0 || current_ad_label != last_text_label ||
	    instr_count < 0) {
		current_ad_label = set_dw_text_label();
	}
	current_ad_count = instr_count;
	update_statprog();
	enter_section("debug_line");
	ext_opcode(DW_LNE_end_sequence, (long)0, (long)0);
	out_dwf_label(l_end, 1);
	exit_section();
	return;
}
