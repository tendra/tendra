/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dwarf_diag_config_key
#define dwarf_diag_config_key

#if DWARF

#include <dwarf/dwarf_types.h>

typedef dwarf_type_label *OUTPUT_REC;

typedef dwarf_global diag_global;		/* used in installtypes.h */

#include <dwarf/dwarf_gbl.h>
#define OUTPUT_GLOBALS_TAB()	out_dwarf_global_list()
#define OUTPUT_DIAG_TAGS()	out_dwarf_diag_tags()
#define NEW_DIAG_GLOBAL(x)	new_dwarf_global(x)
#define INSPECT_FILENAME(fn)	dwarf_inspect_filename(fn)

#else
typedef void *OUTPUT_REC;
typedef int diag_global;
#define OUTPUT_GLOBALS_TAB()
#define OUTPUT_DIAG_TAGS()
#define NEW_DIAG_GLOBAL(x)
#define INSPECT_FILENAME(fn)
#endif

#endif
