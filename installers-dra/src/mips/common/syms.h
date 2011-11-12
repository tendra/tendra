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
$Log: syms.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* symsdecs.h

*/

#include "config.h"

#include "installtypes.h"

extern int *symnos;
extern int *tempsnos;

extern int symnoforext(dec * t, int filen);
extern int symnoforstart(int i, int filen);
extern int symnoforend(dec * ex, int filen);
extern int symnofordata(int data_lab);
