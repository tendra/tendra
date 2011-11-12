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
$Date: 1998/02/04 15:49:07 $
$Revision: 1.2 $
$Log: regable.h,v $
 * Revision 1.2  1998/02/04  15:49:07  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:57  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef REGABLEDECS_H
#define REGABLEDECS_H

#include "config.h"

#include "installtypes.h"

extern bool fixregable(exp);
extern bool floatregable(exp);
extern bool valregable(shape);

#endif /* regabledecs.h */
