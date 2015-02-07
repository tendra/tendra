/* $Id$ */

/* TODO: interface for diag/ to call m68k local stabs */

#include <reader/exp.h>

#include <construct/shape.h>
#include <construct/installtypes.h>

#include <diag3/diag_reform.h>

void xOUTPUT_GLOBALS_TAB(void);
void xOUTPUT_DIAG_TAGS(void);
void xINSPECT_FILENAME(filename);

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

const struct diag3_driver diag3_driver_stabs = {
	NEW_DIAG_GLOBAL,
	xOUTPUT_GLOBALS_TAB,
	xOUTPUT_DIAG_TAGS,
	xINSPECT_FILENAME
};

