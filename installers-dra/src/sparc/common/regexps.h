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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/regexps.h,v 1.2 1998/03/15 16:00:46 pwe Exp $
--------------------------------------------------------------------------
$Log: regexps.h,v $
 * Revision 1.2  1998/03/15  16:00:46  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:54  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:37  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:16  14:59:16  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
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

extern regpeep regexps[];

extern ans iskept(exp);
extern bool couldbe(exp, exp);
extern bool couldeffect(exp, exp);
extern bool dependson(exp, bool, exp);
extern bool eq_sze(shape, shape);
extern bool sim_exp(exp, exp);
extern bool sim_explist(exp, exp);
extern void clear_all(void);
extern void clear_dep_reg(exp);
extern void clear_reg(int);
extern void keepcont(exp, int);
extern void keepexp(exp, ans);
extern void keepreg(exp, int);

#define clear_freg(R)clear_reg(((R) >> 1) + 32)

#endif /* REGEXPS_INCLUDED */
