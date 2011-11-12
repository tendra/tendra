/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:49:08 $
$Revision: 1.2 $
$Log: regexps.h,v $
 * Revision 1.2  1998/02/04  15:49:08  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:12  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef	REGEXPSDECS_H
#define	REGEXPSDECS_H	1

#include "config.h"

#include "installtypes.h"
#include "memtdf.h"

/* number to add to floating point reg number for these functions */
#define	KEPT_FREG_OFFSET	32

extern void clear_all(void);
extern void clear_reg(int);
#define clear_freg(reg)		clear_reg((reg) +KEPT_FREG_OFFSET)

extern bool keep_eq_size(shape, shape);

extern ans iskept(exp);
extern ans iskept_reg(exp);
extern ans iskept_freg(exp);
extern ans iskept_inreg(exp, int);

extern int ans_reg(ans);

extern void keepexp(exp, ans);
extern void keepcont(exp, int);
extern void keepreg(exp, int);

extern bool dependson(exp, bool, exp);
extern void clear_dep_reg(exp);

#endif
