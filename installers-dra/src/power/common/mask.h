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
$Date: 1998/02/04 15:48:57 $
$Revision: 1.2 $
$Log: mask.h,v $
 * Revision 1.2  1998/02/04  15:48:57  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:27  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MASK_H
#define MASK_H
extern int left_of_mask(unsigned int);
extern int right_of_mask(unsigned int);
extern int is_a_mask(unsigned int);
#endif
