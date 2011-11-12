/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: locate.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/08/16  16:06:52  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* locatedecs.h
    externs from locate.c
*/

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "addrtypes.h"
#include "procrectypes.h"

extern long locals_offset;
extern long frame_size;

extern  baseoff boff(exp x);
extern  where locate(exp e, space sp, shape s, int dreg);
extern  bool simplepars;
