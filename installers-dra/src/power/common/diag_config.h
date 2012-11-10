/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAG_CONFIG_H
#define DIAG_CONFIG_H

/* NULL must be convertable to an OUTPUT_REC, make sure it is not a pointer */
#undef	NULL
#define	NULL			0

#include <diag/diagtypes1.h>

typedef void *OUTPUT_REC;			/* stabstring TypeNo */
typedef diag_descriptor diag_global;


extern void INSPECT_FILENAME(filename);
extern void OUTPUT_GLOBALS_TAB(void);
extern void OUTPUT_DIAG_TAGS(void);
#define NEW_DIAG_GLOBAL(x)		(x)


#endif
