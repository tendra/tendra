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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/locate.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: locate.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:42  john
 * Entered into CVS
 *
 * Revision 1.3  1994/12/01  13:47:59  djch
 * Added boff_env_offset
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:22  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:38  14:58:38  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef LOCATEDECS_INCLUDED
#define LOCATEDECS_INCLUDED

#include "exptypes.h"
#include "proctypes.h"

extern baseoff boff(exp);
extern int boff_env_offset(exp);
extern where locate(exp, space, shape, int);
extern where locate1(exp, space, shape, int);

#endif /* LOCATEDECS_INCLUDED */
