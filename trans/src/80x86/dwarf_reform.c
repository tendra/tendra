/* $Id$ */

/* TODO: interface for diag/ to call common/dwarf */

#include <diag/diag_reform.h>

#include <dwarf/dwarf_types.h>
#include <dwarf/dwarf_gbl.h>

dwarf_global *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return new_dwarf_global(d);
}

void
OUTPUT_GLOBALS_TAB(void)
{
	out_dwarf_global_list();
}

void
OUTPUT_DIAG_TAGS(void)
{
	out_dwarf_diag_tags();
}

void
INSPECT_FILENAME(filename f)
{
	dwarf_inspect_filename(f);
}

