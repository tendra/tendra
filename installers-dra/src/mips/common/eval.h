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
$Log: eval.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/10/25  13:48:21  currie
 * change to position of .glob
 *
 * Revision 1.2  1995/08/16  16:06:37  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* evaluateddecs.h
*/

#include "addrtypes.h"
#include "flpttypes.h"

extern int next_data_lab(void);
extern int next_dlab_sym(void);
extern mm maxmin(shape s);
extern instore evaluated(exp e, long l, dec * dc);
extern int  outfloat(flpt f);
extern char *fltrepr;
extern int data_lab;
