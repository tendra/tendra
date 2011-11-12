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
$Log: shapemacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef bothd

#define bothd  1
#define tophd  2
#define scharhd  3
#define ucharhd  4
#define swordhd  5
#define uwordhd  6
#define slonghd  7
#define ulonghd  8
#define s64hd 9
#define u64hd 10

#define shcomplexhd  17
#define complexhd  18
#define complexdoublehd  19
#define shrealhd  20
#define realhd  21
#define doublehd  22
#define bitfhd 23
#define prokhd  24
#define ptrhd  25
#define offsethd  26
#define sizehd  27
#define cpdhd  28

#define nofhd  29
#define tokhd  30

#define shrealfv  0
#define realfv  1
#define doublefv  2
#define shcomplexfv  3
#define complexfv  4
#define complexdoublefv  5

#define is_floating(x)	((x) >= shrealhd && (x) <= doublehd)

#endif /* bothd */
