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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/move.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: move.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:44  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:25  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:48  14:58:48  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef MOVEDECS_INCLUDED
#define MOVEDECS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "addrtypes.h"
#include "sparcins.h"

extern ins_p i_ld_sz(int, int);
extern ins_p i_st_sz(int);

extern void ld_addr(instore, int);
extern int addr_reg(instore, long);

extern int move(ans, where, long, bool);

#endif /* MOVEDECS_INCLUDED */
