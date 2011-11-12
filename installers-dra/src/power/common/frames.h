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
$Date: 1998/02/04 15:48:47 $
$Revision: 1.2 $
$Log: frames.h,v $
 * Revision 1.2  1998/02/04  15:48:47  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:55  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef FRAMES_H
#define FRAMES_H  1

extern void set_up_frame_pointer(procrec *,exp);
extern void set_up_frame_info(procrec *,exp);
extern long frame_offset(exp);

#endif
