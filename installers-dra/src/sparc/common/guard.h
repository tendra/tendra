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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/guard.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: guard.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:38  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:18  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:27  14:58:27  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef GUARDDECS_INCLUDED
#define GUARDDECS_INCLUDED

#include "procrec.h"
#include "addrtypes.h"

extern space guardreg(int, space);
extern space guardfreg(int, space);
extern space guard(where, space);
extern space needreg(int, space);
extern space needfreg(int, space);

#endif /* GUARDDECS_INCLUDED */
