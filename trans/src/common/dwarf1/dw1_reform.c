/* $Id$ */

/* TODO: interface for diag/ to call common/dwarf */

#include <diag3/diag_reform.h>

#include <dwarf1/dw1_types.h>
#include <dwarf1/dw1_gbl.h>

const struct diag3_driver diag3_driver_dw1 = {
	new_dwarf_global,
	out_dwarf_global_list,
	out_dwarf_diag_tags,
	dwarf_inspect_filename
};

