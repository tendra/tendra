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
$Date: 1998/02/04 15:48:54 $
$Revision: 1.2 $
$Log: locate.h,v $
 * Revision 1.2  1998/02/04  15:48:54  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:01:55  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef LOCATEDECS_H
#define LOCATEDECS_H

#include "exptypes.h"
#include "procrectypes.h"


extern baseoff boff(exp);
extern baseoff boff_location(int);
extern where locate(exp , space , shape , int);
extern int ENCODE_FOR_BOFF(int,int);
#define OUTPUT_CALLER_PARAMETER  1
#define INPUT_CALLER_PARAMETER   2
#define INPUT_CALLEE_PARAMETER   3
#endif
