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
$Date: 1998/02/04 15:49:01 $
$Revision: 1.2 $
$Log: needscan.h,v $
 * Revision 1.2  1998/02/04  15:49:01  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/10/14  17:32:01  pwe
 * include called callees in env_size
 *
 * Revision 1.2  1996/10/04  16:03:07  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef NEEDSCANDECS_H
#define NEEDSCANDECS_H

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"


extern int maxfix, maxfloat;
extern long callee_size;
extern long max_callees;
extern bool gen_call;
extern long no_of_returns;

extern needs likeplus(exp *, exp **);
extern needs likeminus(exp *, exp **);
extern needs scan(exp *, exp **);

#endif /* needscandecs.h */
