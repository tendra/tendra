/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: eval.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:10  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.2  1995/10/20  13:44:20  wfs
 * "set_align" and "evalone" declared for gcc compilation.
 *
 * Revision 5.1  1995/09/15  13:44:36  wfs
 * "extern long evalexp PROTO_S (( exp ))" added.
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
 * Revision 3.1  95/04/10  16:26:08  16:26:08  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:16:52  11:16:52  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:25:40  15:25:40  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:37:21  13:37:21  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef EVALDECS_INCLUDED
#define EVALDECS_INCLUDED

#include "addrtypes.h"
#include "flpttypes.h"

extern int next_data_lab(void);
extern int next_PIC_pcrel_lab(void);
extern mm maxmin(shape);
extern instore evaluated(exp, long);
extern long *realrep(exp);
extern long evalexp(exp);
extern void set_align(int);
extern void evalone(exp, int);

#endif /* EVALDECS_INCLUDED */
