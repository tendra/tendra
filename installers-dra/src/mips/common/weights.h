/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:07 $
$Revision: 1.1.1.1 $
$Log: weights.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* weightsdecs.h
   externals for weights.c
*/

#include "config.h"
#include "exptypes.h"
#include "procrectypes.h"

extern  weights weightsv(double scale, exp e);
