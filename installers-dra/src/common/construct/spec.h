/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: spec.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef spec_key
#define spec_key 1

#include "config.h"
#include "exptypes.h"
#include "localtypes.h"

extern speci special_fn(exp a1, exp a2, shape s);

 /* a1 is the function, a2 is the arguments, s is the shape of the result.
    result.is_special is true if a special case has been recognised.
    result.special_exp is the transformed exp if is_special is true. */

#endif
