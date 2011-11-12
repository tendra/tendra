/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: codehere.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:10:59  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:48:38  wfs
 *  Preperation for August 95 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:47:27  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:47:27  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:25:52  16:25:52  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:14:30  11:14:30  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:25:19  15:25:19  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:36:04  13:36:04  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef CODEHERE_INCLUDED
#define CODEHERE_INCLUDED

#include "proctypes.h"
#include "addrtypes.h"

extern int regofval(exp);
extern int fregofval(exp);
extern void reg_operand_here(exp, space, int);
extern int reg_operand(exp, space);
extern int freg_operand(exp, space, int);
extern int code_here(exp, space, where);

#endif /* CODEHERE_INCLUDED */
