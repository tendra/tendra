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
$Date: 1998/02/04 15:49:02 $
$Revision: 1.2 $
$Log: oprators.h,v $
 * Revision 1.2  1998/02/04  15:49:02  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:14  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef OPRATORSDECS_H
#define OPRATORSDECS_H

#include "exptypes.h"
#include "addresstypes.h"



extern int comm_op(exp , space , where , Instruction_P);
extern int non_comm_op(exp , space , where , Instruction_P);


extern int fop(exp , space , where , Instruction_P);
extern int fmop(exp , space , where , Instruction_P);
extern void tidyshort(int,exp);

#endif /* opratorsdecs.h */
