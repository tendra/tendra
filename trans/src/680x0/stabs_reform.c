/* $Id$ */

/* TODO: interface for diag/ to call 680x0 local stabs */

#include <diag/diag_reform.h>

diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

void
OUTPUT_GLOBALS_TAB(void)
{
	xOUTPUT_GLOBALS_TAB();
}

void
OUTPUT_DIAG_TAGS(void)
{
	xOUTPUT_DIAG_TAGS();
}

void
INSPECT_FILENAME(filename f)
{
	xINSPECT_FILENAME(f);
}

