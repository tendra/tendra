/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "codetypes.h"

#include "dg_first.h"

#include "diaginfo.h"
#include "exptypes.h"
#include "installtypes.h"
#include "dg_types.h"		/* NEW DIAGS */
#include "diagtypes.h"		/* OLD DIAGS */


extern long add_type_to_aux(diag_type, long);

/*
converts a TDF shape into an AUXU (see sym.h) and adds it to the auxillary table for the file number given as parameter as required by the MIPS symbol table.
*/
