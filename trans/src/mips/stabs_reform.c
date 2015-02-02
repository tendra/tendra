/* $Id$ */

/* TODO: interface for diag/ to call mips local stabs */

#include <diag3/diag_reform.h>

diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

void
OUTPUT_GLOBALS_TAB(void)
{
}

void
OUTPUT_DIAG_TAGS(void)
{
	mOUTPUT_DIAG_TAGS();
}

void
INSPECT_FILENAME(filename f)
{
	collect_files(f);
}

