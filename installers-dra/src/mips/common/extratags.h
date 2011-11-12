/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: extratags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* these are name tags fabricated by scan or tokens*/
#ifndef EXTRATAGS
#define EXTRATAGS

#define locptr_tag 	249
#define maxlike_tag 	250
#define minlike_tag	251
#define abslike_tag	252
#define last_env_tag	253
#define refmap_tag	254

extern shape LISTsh;

#define isLIST(x) (x)==LISTsh

#endif
