/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: regexps.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/12  10:59:42  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/08/16  16:07:09  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* regexpsdecs.h
*/


#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "addrtypes.h"

struct regpeept {
  ans inans;
  exp keptexp;
  bool iscont;
};

typedef struct regpeept regpeep;

extern void clear_all(void);
extern void clear_reg(int i);
extern ans iskept(exp e);
extern void keepexp(exp e, ans loc);
extern void clear_dep_reg(exp lhs);
extern void keepcont(exp e, int reg);
extern void keepreg(exp e, int reg);
extern regpeep regexps[48];
extern bool eq_sze(shape, shape);
extern bool dependson(exp, bool, exp);
