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
$Date: 1998/02/04 15:49:06 $
$Revision: 1.2 $
$Log: record_bit.h,v $
 * Revision 1.2  1998/02/04  15:49:06  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:51  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef RECORD_BIT_H
#define RECORD_BIT_H

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"

extern void try_record_bit(exp);
extern bool record_bit_set(exp);
#endif
