/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/regalloc.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: regalloc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:54  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:36  djch
 * Initial revision
 *
 * Revision 1.2  93/07/05  18:25:47  18:25:47  ra (Robert Andrews)
 * Declared avoid_L7 flag.
 *
 * Revision 1.1  93/06/24  14:59:13  14:59:13  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef REGALLOC_INCLUDED
#define REGALLOC_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "proctypes.h"

extern bool avoid_L7;
extern spacereq maxspace(spacereq, spacereq);
extern spacereq regalloc(exp, int, int, long);

#endif /* REGALLOC_INCLUDED */
