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
$Date: 1998/02/04 15:48:45 $
$Revision: 1.2 $
$Log: eval.h,v $
 * Revision 1.2  1998/02/04  15:48:45  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:35  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef EVALDECS_H
#define EVALDECS_H

#include "addresstypes.h"
#include "flpttypes.h"


extern int next_data_lab(void);

extern mm maxmin(shape);

extern instore evaluated(exp , int);
extern instore evaluated_const(exp);

extern void outlab(int);

#endif
