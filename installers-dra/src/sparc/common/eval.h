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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/eval.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: eval.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/10/10  18:32:17  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.1.1.1  1995/03/13  10:18:32  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:12  djch
 * Initial revision
 *
 * Revision 1.2  93/08/27  11:24:29  11:24:29  ra (Robert Andrews)
 * The routines oneval and set_align are now static.
 *
 * Revision 1.1  93/06/24  14:58:10  14:58:10  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef EVALDECS_INCLUDED
#define EVALDECS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "addrtypes.h"
#include "flpttypes.h"

extern bool is_zero(exp);
extern instore evaluated(exp, long, bool);
extern int next_data_lab(void);
extern long *realrep(exp);
extern long evalexp(exp);
extern mm maxmin(shape);
extern void evalone(exp, int, bool);
extern void outlab(int);

#endif /* EVALDECS_INCLUDED */
