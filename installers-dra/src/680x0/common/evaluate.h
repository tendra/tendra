/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/evaluate.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: evaluate.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:50  ma
First version.
Revision 1.2  1997/09/25 06:44:59  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:11  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:29  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:53  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:11  john
 *
 * Revision 1.1  93/02/22  17:15:34  17:15:34  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef EVALUATE_INCLUDED
#define EVALUATE_INCLUDED
#include "mach.h"
extern exp const_list;
extern long * realrep(exp);
extern void evaluate(exp, long, char *, int, int, diag_global *);
extern void eval_op(long sz, mach_op* op);

#define  make_constant(X, Y)\
    const_list = getexp(botsh, const_list, 0,(Y), nilexp, 0,(X), 0)

#endif
