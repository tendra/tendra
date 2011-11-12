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
$Log: f64.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef f64_key
#define f64_key

extern flt64 flt_to_f64(flpt fp, int sg, int *ov);
extern flpt f64_to_flt(flt64 a, int sg);
extern int f64_to_flpt(flt64 a, int sg, int *pr, int sz);
extern flt64 int_to_f64(int i, int sg);
extern flt64 exp_to_f64(exp e);

#endif
