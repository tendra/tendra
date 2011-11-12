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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/muldvrem.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: muldvrem.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/04/17  08:25:59  john
 * Changed div2 trap treatment
 *
 * Revision 1.1.1.1  1995/03/13  10:18:46  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:26  djch
 * Initial revision
 *
 * Revision 1.3  93/09/27  14:50:54  14:50:54  ra (Robert Andrews)
 * Declare clear_sun_call_divrem_regs.
 *
 * Revision 1.2  93/07/12  15:16:34  15:16:34  ra (Robert Andrews)
 * The final argument of call_muldivrem is now one of the SPECIAL values
 * from special.h.
 *
 * Revision 1.1  93/06/24  14:58:51  14:58:51  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef MULDVREM_INCLUDED
#define MULDVREM_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "exptypes.h"

extern bool is_muldivrem_call(exp);
extern int call_muldivrem(exp, exp, space, int, int);

extern needs multneeds(exp *, exp **);
extern needs divneeds(exp *, exp **);
extern needs remneeds(exp *, exp **);

extern int do_mul_comm_op(exp, space, where, bool);
extern int do_div_op(exp, space, where, bool);
extern int do_rem_op(exp, space, where, bool);

extern void clear_sun_call_divrem_regs(space);

#endif /* MULDVREM_INCLUDED */
