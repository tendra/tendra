/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAG_CONFIG_INCLUDED
#define DIAG_CONFIG_INCLUDED

#include <diag/diagtypes1.h>

typedef diag_descriptor diag_global;
typedef void *OUTPUT_REC;

#define NEW_DIAG_GLOBAL(x)      (x)

extern void OUTPUT_GLOBALS_TAB(void);
extern void OUTPUT_DIAG_TAGS(void);
extern void INSPECT_FILENAME(filename);

#endif
