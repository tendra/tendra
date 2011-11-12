/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: extratags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:14  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/09/15  15:37:42  wfs
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/15  14:54:11  wfs
 * Initial revision
 *
 * Revision 1.1  1995/09/15  14:54:11  wfs
 * Initial revision
 *
*/

/* these are name tags fabricated by scan */
#ifndef EXTRATAGS_H
#define EXTRATAGS_H

#define locptr_tag 	249
#define maxlike_tag 	250
#define minlike_tag	251
#define abslike_tag	252
#define last_env_tag	253
#define refmap_tag	254

extern shape LISTsh;

#define isLIST(x) (x)==LISTsh
#endif
