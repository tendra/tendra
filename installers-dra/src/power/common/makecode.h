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
$Date: 1998/02/04 15:48:56 $
$Revision: 1.2 $
$Log: makecode.h,v $
 * Revision 1.2  1998/02/04  15:48:56  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:21  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MAKECODEDECS_H
#define MAKECODEDECS_H

#include "config.h"

#include "installtypes.h"
#include "procrectypes.h"
#include "exptypes.h"


extern where nowhere;
extern void adjust_to_size(int,int,int,int,int);

extern makeans make_code(exp , space , where , int);
extern prop notbranch[];
extern prop combranch[];
extern int regfrmdest(where *,space);
extern freg fregfrmdest(bool,where *, space);
#define cbranch(x)(combranch[x])
#define obranch(x)(notbranch[x])
#endif /* makecodedecs.h */



