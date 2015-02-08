/* $Id$ */

/* TODO: interface for diag/ to call common/dwarf */

#include <reader/exp.h>

#include <diag3/diaginfo.h>
#include <diag3/diag_reform.h>

#include <dwarf1/dw1_types.h>
#include <dwarf1/dw1_gbl.h>
#include <dwarf1/dw1_out.h>

void dw1_output_diag(diag_info *d, int proc_no, exp e);
void dw1_output_end_scope(diag_info *d, exp e);

void dw1_diag_proc_begin(diag_descriptor *d_props, int global, int cname, char *pname);
void dw1_diag_proc_end(diag_descriptor *d_props);

void dw1_diag_val_begin(diag_descriptor *d_props, int global, int cname, char *pname);
void dw1_diag_val_end(diag_descriptor *d_props);

const struct diag3_driver diag3_driver_dw1 = {
	dw1_out_diagnose_prelude,
	dw1_out_diagnose_postlude,

	new_dwarf_global,
	out_dwarf_global_list,
	out_dwarf_diag_tags,
	dwarf_inspect_filename,

	dw1_output_diag,
	dw1_output_end_scope,

	dw1_diag_proc_begin,
	dw1_diag_proc_end,

	dw1_diag_val_begin,
	dw1_diag_val_end
};

