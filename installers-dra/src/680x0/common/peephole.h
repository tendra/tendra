/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/peephole.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: peephole.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:58  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:17  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:44  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:58  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:17  john
 *
 * Revision 1.2  94/02/21  16:03:24  16:03:24  ra (Robert Andrews)
 * Declare functions with no arguments using ( void ).
 *
 * Revision 1.1  93/02/22  17:16:36  17:16:36  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef PEEPHOLE_INCLUDED
#define PEEPHOLE_INCLUDED

#include "config.h"

#include "installtypes.h"

extern bitpattern callmsk;
extern void peephole(void);
extern bool post_inc_check(mach_ins *, bitpattern);

#endif
