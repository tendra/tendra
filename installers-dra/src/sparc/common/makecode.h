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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/makecode.h,v 1.2 1998/03/11 11:03:56 pwe Exp $
--------------------------------------------------------------------------
$Log: makecode.h,v $
 * Revision 1.2  1998/03/11  11:03:56  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1997/03/24  17:09:31  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.6  1995/09/19  14:31:05  john
 * Moved error_treatment_is_trap macro from makecode.c
 *
 * Revision 1.5  1995/09/15  16:16:32  john
 * New exception handling
 *
 * Revision 1.4  1995/07/14  16:32:13  john
 * Additions for new error handling
 *
 * Revision 1.3  1995/06/14  15:34:45  john
 * Added do_exception prototype
 *
 * Revision 1.2  1995/05/26  12:59:30  john
 * Changes for new spec (3.1)
 *
 * Revision 1.1.1.1  1995/03/13  10:18:43  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:23  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:42  14:58:42  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef MAKECODE_INCLUDED
#define MAKECODE_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "proctypes.h"
#include "exptypes.h"

extern where nowhere;
extern bool last_param(exp);
extern int use_subvar(exp);
extern makeans make_code(exp, space, where, int);
extern void checknan(exp, int);
extern void setnovolatile(void);
extern void setvolatile(void);
extern void load_reg(exp,int,space);
extern void do_exception(int);

#ifdef NEWDIAGS
extern void diag_arg(exp, space, where);
#endif

/*
#define TDF_HANDLER "__TDFhandler"
#define TDF_STACKLIM "__TDFstacklim"
*/

/*
  Identify a 'trap' error handler.  This uses the system exception
  mechanism.
*/
#define error_treatment_is_trap(x)((errhandle(x) &3) ==3)


#if ADDUNDERSCORE
#define TDF_HANDLER "___sparc_errhandler"
#define TDF_STACKLIM "___sparc_stack_limit"
#else
#define TDF_HANDLER "__sparc_errhandler"
#define TDF_STACKLIM "__sparc_stack_limit"
#endif /* ADDUNDERSCORE */

#endif /* MAKECODE_INCLUDED */
