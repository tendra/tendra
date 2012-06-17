/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* haiku/diag_config.h */

#ifndef diag_config_key
#define diag_config_key

#include <diag/diagtypes1.h>

typedef long OUTPUT_REC;
typedef diag_descriptor diag_global;

#define INSPECT_FILENAME(x)	stab_collect_files(x)
#define NEW_DIAG_GLOBAL(x)	(x)
#define OUTPUT_DIAG_TAGS()	stab_tagdefs()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs()

#define STABS

extern void stab_collect_files(filename f);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void init_stab_aux(void);

#endif
