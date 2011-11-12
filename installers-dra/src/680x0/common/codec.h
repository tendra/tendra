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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/codec.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: codec.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:48  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:10  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:24  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:52  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:08  john
 *
 * Revision 1.1  93/02/22  17:15:18  17:15:18  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef CODEC_INCLUDED
#define CODEC_INCLUDED

#include "config.h"

#include "exptypes.h"
#include "localtypes.h"

extern void codec(where, ash, exp);
extern exp sim_exp(shape, where);

#endif
