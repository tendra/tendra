/* $Id$ */

/* TODO: interface for diag/ to call mips local stabs */

#include <reader/exp.h>

#include <construct/shape.h>
#include <construct/installtypes.h>

#include <diag3/diag_reform.h>

void mOUTPUT_DIAG_TAGS(void);
void collect_files(filename);

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

static void
OUTPUT_GLOBALS_TAB(void)
{
}

const struct diag3_driver diag3_driver_stabs = {
	NEW_DIAG_GLOBAL,
	OUTPUT_GLOBALS_TAB,
	mOUTPUT_DIAG_TAGS,
	collect_files
};

