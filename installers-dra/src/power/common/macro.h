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
$Date: 1998/02/04 15:48:55 $
$Revision: 1.2 $
$Log: macro.h,v $
 * Revision 1.2  1998/02/04  15:48:55  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:11  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MACRO_H
#define MACRO_H

extern char * reg_macro(int);
extern char * freg_macro(int);
extern char * cr_macro(int);
extern char * spr_macro(int);
extern void init_macros(void);
extern int do_macros;

#endif
