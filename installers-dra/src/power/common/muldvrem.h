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
$Date: 1998/02/04 15:49:00 $
$Revision: 1.2 $
$Log: muldvrem.h,v $
 * Revision 1.2  1998/02/04  15:49:00  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:56  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MULDVREMDECS_H
#define MULDVREMDECS_H

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"

#include "memtdf.h"
#include "procrectypes.h"


extern needs multneeds(exp *, exp **);
extern needs divneeds(exp *, exp **);
extern needs remneeds(exp *, exp **);

extern int do_mul_comm_op(exp , space , where , bool);
extern int do_div_op(exp, space , where , bool);
extern int do_rem_op(exp , space, where , bool);

#endif /* muldvremdecs.h */
