/* $Id$ */

#include "ansi.h"

/*
 * TODO: Currently I think tspec accidentally generates the wrong filetype (.c)
 * for C++ APIs. So, tcc(1) misunderstands them as C. For the moment I'm just
 * disabling these, until tspec outputs the right extension.
 */
#ifdef _OPENBSD4
#define __WRONG_CPP
#endif

