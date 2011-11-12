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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/needscan.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: needscan.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/12/04  19:54:27  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.3  1995/10/31  12:47:46  john
 * Introduced min macro
 *
 * Revision 1.2  1995/05/26  13:00:08  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:50  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:28  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:56  14:58:56  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef NEEDSCAN_INCLUDED
#define NEEDSCAN_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "proctypes.h"

extern bool chase(exp, exp *);
extern bool complex(exp);
extern bool subvar_use(exp);
extern bool unchanged(exp, exp);
extern exp *ptr_position(exp);
extern needs fpop(exp *, exp **);
extern needs likediv(exp *, exp **);
extern needs likeplus(exp *, exp **);
extern needs maxneeds(needs, needs);
extern needs maxtup(exp, exp **);
extern needs scan(exp *, exp **);
extern needs shapeneeds(shape);
extern void cca(exp **, exp *);
extern void check_asm_seq(exp, int);

extern int maxfix, maxfloat;
#define max(X,Y)(X>Y)?(X):(Y)
#define min(X,Y)(X<Y)?(X):(Y)
#endif /* NEEDSCAN_INCLUDED */
