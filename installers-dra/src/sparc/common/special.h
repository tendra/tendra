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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/special.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: special.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:58  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:42  djch
 * Initial revision
 *
 * Revision 1.3  93/07/14  11:23:08  11:23:08  ra (Robert Andrews)
 * Declare library_key.
 *
 * Revision 1.2  93/07/12  15:20:07  15:20:07  ra (Robert Andrews)
 * Added support for special_routines.
 *
 * Revision 1.1  93/06/24  14:59:29  14:59:29  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef SPECIAL_INCLUDED
#define SPECIAL_INCLUDED

#include "exp.h"
#include "proctypes.h"
#include "addrtypes.h"

extern char *special_call_name(int);
extern int specialfn(exp);
extern int specialmake(int, exp, space, where, int);
extern int specialopt(exp);
extern needs specialneeds(int, exp, exp);
extern speci special_fn(exp, exp, shape);

extern int library_key;
extern void call_special_routine(int);
extern void output_special_routines(void);

#define SPECIAL_MUL	0
#define SPECIAL_UMUL	1
#define SPECIAL_DIV2	2
#define SPECIAL_UDIV2	3
#define SPECIAL_REM2	4
#define SPECIAL_UREM2	5
#define SPECIAL_DIV1	6
#define SPECIAL_REM1	7

#endif /* SPECIAL_INCLUDED */
