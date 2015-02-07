/* $Id$ */

/* TODO: interface for diag/ to call x86 local codeview */

#include <diag3/diag_reform.h>

void cvOUTPUT_GLOBALS_TAB(void);
void cvOUTPUT_DIAG_TAGS(void);
void cvINSPECT_FILENAME(filename);

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

const struct diag3_driver diag3_driver_cv = {
	NEW_DIAG_GLOBAL,
	cvOUTPUT_GLOBALS_TAB,
	cvOUTPUT_DIAG_TAGS,
	cvINSPECT_FILENAME
};

