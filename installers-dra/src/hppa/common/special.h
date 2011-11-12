/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: special.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:36  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:28:13  16:28:13  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:19:01  11:19:01  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:28:54  15:28:54  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:44:11  13:44:11  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef SPECIAL_INCLUDED
#define SPECIAL_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exp.h"
#include "proctypes.h"
#include "addrtypes.h"

extern int specialfn(exp);
extern char *special_call_name(int);
extern needs specialneeds(int, exp, exp);
extern int specialmake(int, exp, space, where, int);
extern void call_millicode(int, int, char*, bool);
extern void import_millicode(void);

#endif /* SPECIAL_INCLUDED */
