/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diag_config_key
#define diag_config_key

#include <diag/diagtypes1.h>

extern void collect_files(filename);
#define INSPECT_FILENAME(fn)collect_files(fn)


typedef void *OUTPUT_REC;
typedef diag_descriptor  diag_global;
#define OUTPUT_GLOBALS_TAB()
extern void OUTPUT_DIAG_TAGS(void);
#define NEW_DIAG_GLOBAL(x)x


#endif
