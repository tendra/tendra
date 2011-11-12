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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/localtypes.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: localtypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/15  10:12:52  john
 * Minor change
 *
 * Revision 1.1.1.1  1995/03/13  10:18:42  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:21  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:35  14:58:35  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef LOCALTYPES_INCLUDED
#define LOCALTYPES_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"

typedef struct {
    int ashsize;
    int ashalign;
} ash;

extern ash ashof(shape);

typedef struct {
    bool is_special;
    exp special_exp;
} speci;

#endif /* LOCALTYPES_INCLUDED */
