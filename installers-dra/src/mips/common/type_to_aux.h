/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:07 $
$Revision: 1.1.1.1 $
$Log: type_to_aux.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/08/16  15:38:39  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/

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
