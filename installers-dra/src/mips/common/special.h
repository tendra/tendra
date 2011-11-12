/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: special.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/08/16  16:07:12  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/*specialdecs.h
*/

#include "config.h"
#include "exptypes.h"

#include "exp.h"
#include "procrectypes.h"
#include "addrtypes.h"

extern needs specialneeds(int i);
extern int specialfn(exp fn);
extern int specialmake(int n, exp par, space sp, where dest, int exitlab);
