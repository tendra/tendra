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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/oprators.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: oprators.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:50  john
 * Entered into CVS
 *
 * Revision 1.3  1994/12/01  13:50:15  djch
 * Added absop
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:29  djch
 * Initial revision
 *
 * Revision 1.3  93/09/27  14:53:36  14:53:36  ra (Robert Andrews)
 * Declared quad_op.
 *
 * Revision 1.2  93/06/29  14:30:23  14:30:23  ra (Robert Andrews)
 * Now use ins_p to represent instructions.
 *
 * Revision 1.1  93/06/24  14:58:59  14:58:59  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef OPRATORS_INCLUDED
#define OPRATORS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "addrtypes.h"

extern bool regremoved(exp *, int);
extern int comm_op(exp, space, where, ins_p);
extern int fop(exp, space, where, ins_p);
extern int monop(exp, space, where, ins_p);
extern int absop(exp, space, where);
extern int non_comm_op(exp, space, where, ins_p);
extern void do_comm(exp, space, int, ins_p);
extern void tidyshort(int, shape);

extern void quad_op(exp, exp, space, where, int);

#endif /* OPRATORS_INCLUDED */
