/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/codehere.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: codehere.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:28  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:05  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:01  14:58:01  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
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
