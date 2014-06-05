/* $Id$ */

/* TODO: interface for diag/ to call mips local stabs */

#include <diag/diag_reform.h>

diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

void
OUTPUT_GLOBALS_TAB(void)
{
	pOUTPUT_GLOBALS_TAB();
}

void
OUTPUT_DIAG_TAGS(void)
{
	pOUTPUT_DIAG_TAGS();
}

void
INSPECT_FILENAME(filename f)
{
	pINSPECT_FILENAME(f);
}

