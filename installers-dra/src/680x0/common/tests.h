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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/tests.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: tests.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:59  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:18  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:46  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.2  94/02/21  16:04:44  16:04:44  ra (Robert Andrews)
 * A couple of values which were previously bool are now int.
 *
 * Revision 1.1  93/02/22  17:16:48  17:16:48  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef TESTS_INCLUDED
#define TESTS_INCLUDED

#include "config.h"

#include "exptypes.h"
#include "installtypes.h"

extern int cc_conventions;
extern int do_sub_params;

extern bool no_side(exp);
extern bool push_arg(exp);
extern bool regable(exp);

extern bool cpd_param(shape);
extern bool is_ptr_void(shape);
extern bool issigned(shape);
extern int reg_result(shape);
extern bool varsize(shape);

#define  result_in_reg(X)	reg_result(X)

#endif
