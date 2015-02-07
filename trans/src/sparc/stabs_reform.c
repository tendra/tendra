/* $Id$ */

/* TODO: interface for diag/ to call mips local stabs */

#include <reader/exp.h>

#include <construct/shape.h>
#include <construct/installtypes.h>

#include <diag3/diag_reform.h>

void stab_typedefs(void);
void stab_tagdefs(void);
void stab_collect_files(filename);

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

const struct diag3_driver diag3_driver_stabs = {
	NEW_DIAG_GLOBAL,
	stab_typedefs,
	stab_tagdefs,
	stab_collect_files
};

