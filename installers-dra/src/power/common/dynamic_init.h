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
$Date: 1998/02/04 15:48:43 $
$Revision: 1.2 $
$Log: dynamic_init.h,v $
 * Revision 1.2  1998/02/04  15:48:43  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:21  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef DYNAMIC_INIT_H
#define DYNAMIC_INIT_H
extern void do__main_extern(void);
extern void call__main(void);
extern int proc_is_main(exp);

#endif
