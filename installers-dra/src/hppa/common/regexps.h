/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: regexps.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:31  wfs
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
 * Revision 3.1  95/04/10  16:28:05  16:28:05  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:18:55  11:18:55  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:28:44  15:28:44  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:43:22  13:43:22  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef REGEXPS_INCLUDED
#define REGEXPS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"

typedef struct {
    ans inans;
    exp keptexp;
    bool iscont;
} regpeep;

extern bool eq_sze(shape, shape);
extern bool dependson(exp, bool, exp);
extern void clear_all(void);
extern void clear_reg(int);
extern ans iskept(exp);
extern void keepexp(exp, ans);
extern void clear_dep_reg(exp);
extern void keepcont(exp, int);
extern void keepreg(exp, int);

#define clear_freg(R)clear_reg(((R) >> 1) + 32)

#endif /* REGEXPS_INCLUDED */
