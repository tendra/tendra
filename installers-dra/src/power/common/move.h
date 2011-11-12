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
$Date: 1998/02/04 15:48:59 $
$Revision: 1.2 $
$Log: move.h,v $
 * Revision 1.2  1998/02/04  15:48:59  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:49  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MOVEDECS_H
#define MOVEDECS_H

#include "config.h"

#include "installtypes.h"
#include "addresstypes.h"
#include "instruct.h"

extern Instruction_P i_ld_sz(int , int);
extern Instruction_P i_st_sz(int);

extern void ld_addr(instore, int);
extern int addr_reg(instore, long);

extern int move(ans , where , long , bool);

#endif /* movedecs.h */
