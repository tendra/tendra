/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SYMTAB_TYPETOAUX_H
#define SYMTAB_TYPETOAUX_H

#include <tdf/nat.h>

#include <reader/exp.h>

#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#include <diag3/dg_types.h>  /* TDF_DIAG4 */
#include <diag3/diagtypes.h>	/* TDF_DIAG3 */

#include <construct/installtypes.h>

/*
 * Convert a TDF shape into an AUXU (see sym.h) and adds it to the auxillary
 * table for the file number given as parameter as required by the symbol table.
 */
long add_type_to_aux(diag_type, long);

#endif

