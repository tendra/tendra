/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* 
   minmaxmacs.h 
   defines min, max, and abs
*/

#ifndef max
#define max(a,b) (((a)>=(b)) ? (a):(b))
#define min(a,b) (((a)<=(b)) ? (a):(b))
#define absval(a) (((a)<0) ? -(a):(a))
#endif
