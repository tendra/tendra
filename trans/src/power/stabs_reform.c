/* $Id$ */

/* TODO: interface for diag/ to call mips local stabs */

#include <reader/exp.h>

#include <construct/shape.h>
#include <construct/installtypes.h>

#include <diag3/diag_reform.h>

void pOUTPUT_GLOBALS_TAB(void);
void pOUTPUT_DIAG_TAGS(void);
void pINSPECT_FILENAME(filename);

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

const struct diag3_driver diag3_driver_stabs = {
	NEW_DIAG_GLOBAL,
	pOUTPUT_GLOBALS_TAB,
	pOUTPUT_DIAG_TAGS,
	pINSPECT_FILENAME
};

