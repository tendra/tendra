/* $Id$ */

/* TODO: interface for diag/ to call x86 local codeview */

#include <diag3/diag_reform.h>

diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

void
OUTPUT_GLOBALS_TAB(void)
{
	cvOUTPUT_GLOBALS_TAB();
}

void
OUTPUT_DIAG_TAGS(void)
{
	cvOUTPUT_DIAG_TAGS();
}

void
INSPECT_FILENAME(filename f)
{
	cvINSPECT_FILENAME();
}

