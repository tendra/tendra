/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: maxminmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* minmaxmacs.h 
    defines min, max, and abs
*/

#ifndef max
#define max(a,b) (((a)>=(b)) ? (a):(b))
#define min(a,b) (((a)<=(b)) ? (a):(b))
#define absval(a) (((a)<0) ? -(a):(a))
#endif
