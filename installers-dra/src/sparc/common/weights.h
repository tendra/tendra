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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/weights.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: weights.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:19:01  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:54  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:40  14:59:40  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef WEIGHTS_INCLUDED
#define WEIGHTS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "procrec.h"

extern weights add_weights(weights *, weights *);
extern weights add_wlist(double, exp);
extern weights mult_weights(double, weights *);
extern weights weightsv(double, exp);
extern wp max_weights(double, weights *, bool);

#endif /* WEIGHTS_INCLUDED */
