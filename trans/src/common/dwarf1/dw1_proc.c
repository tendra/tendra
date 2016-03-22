/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <main/driver.h>
#include <main/print.h>

#include <local/code.h>
#include <local/out.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/basicread.h>

#include <construct/installtypes.h>
#include <construct/dec.h>

#include <dwarf1/dw1_consts.h>
#include <dwarf1/dw1_types.h>
#include <dwarf1/dw1_type.h>
#include <dwarf1/dw1_out.h>

extern int continue_decs;

void
out_dwarf_proc_args(diag_type t)
{
	if (t->key != DIAG_TYPE_PROC) {
		error(ERR_INTERNAL, "Can't output args of non proc type");
	}

	if (t->data.proc.opt_args) {
		cont_sib_chain(TAG_unspecified_parameters);
		leave_dwarf_blk();
	}
}


void
dw1_diag_proc_begin(diag_descriptor *d_props, int global, int cname, char *pname)
{
	UNUSED(cname);
	UNUSED(pname);

	if (!d_props) {
		return;
	}

	asm_comment("Here beginneth a proc");
	if (d_props->key != DIAG_ID_KEY) {
		error(ERR_INTERNAL, "proc beg without id");
	}

	next_dwarf_lab(&(d_props->lab));
	OUT_DWARF_BEG(&(d_props->lab));

	if (global) {
		cont_sib_chain(TAG_global_subroutine);
	} else {
		cont_sib_chain(TAG_subroutine);
	}

	out_dwarf_name_attr(TDFSTRING2CHAR(d_props->data.id.name));
	out_dwarf_type_attr(d_props->data.id.new_type->data.proc.result_type);
	OUT_DWARF_ATTR(AT_low_pc);
	dwarf4(LAB2CHAR(d_props->lab.beg));
	OUT_DWARF_ATTR(AT_high_pc);
	dwarf4(LAB2CHAR(d_props->lab.end));
	leave_dwarf_blk();
	make_next_new_chain();

	/* must be OUTSIDE blk */
	out_dwarf_sourcemark(&d_props->data.id.whence);

	out_dwarf_proc_args(d_props->data.id.new_type);
	continue_decs = 1;
}


void
dw1_diag_proc_end(diag_descriptor *d_props)
{
	if (!d_props) {
		return;
	}

	asm_comment("Here endeth a proc");
	OUT_DWARF_END(& (d_props->lab));
	end_sib_chain();
}


void
dw1_diag_val_begin(diag_descriptor *d_props, int global, int cname, char *pname)
{
	UNUSED(d_props);
	UNUSED(global);
	UNUSED(cname);
	UNUSED(pname);

	asm_comment("Here beginneth a val");
}


void
dw1_diag_val_end(diag_descriptor *d_props)
{
	UNUSED(d_props);

	asm_comment("Here endeth a val");
}
