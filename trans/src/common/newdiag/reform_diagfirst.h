/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef reform_dg_first_key
#define reform_dg_first_key

#if DWARF
#include <dwarf/dwarf_types.h>
#endif

/* breaks type cycles */

typedef struct reform_diagdef_t    reform_diag_descriptor;
typedef struct reform_diag_type_t  *reform_diag_type;
typedef struct reform_filename_t   *reform_filename;

/*
 * This is used by common/reader to create common/diag types by the f_* API.
 */
#if DWARF
typedef dwarf_global    reform_diag_global;
#else
/* XXX: dwarf_diag_config.h has this as int! */
typedef reform_diag_descriptor reform_diag_global;
#endif

#endif
