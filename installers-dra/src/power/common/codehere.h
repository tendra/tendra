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
$Date: 1998/02/04 15:48:41 $
$Revision: 1.2 $
$Log: codehere.h,v $
 * Revision 1.2  1998/02/04  15:48:41  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:50  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef CODEHEREDECS_H
#define CODEHEREDECS_H

#include "procrectypes.h"
#include "addresstypes.h"

extern int regofval(exp);
extern int fregofval(exp);
extern void reg_operand_here(exp, space, int);
extern int reg_operand(exp, space);
extern int freg_operand(exp, space, int);
extern int code_here(exp, space, where);

#endif
