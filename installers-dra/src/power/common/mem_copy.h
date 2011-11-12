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
$Date: 1998/02/04 15:48:58 $
$Revision: 1.2 $
$Log: mem_copy.h,v $
 * Revision 1.2  1998/02/04  15:48:58  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:37  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MEM_COPY_H
#define MEM_COPY_H

extern void static_memory_copy(int,int,int);
extern void reverse_static_memory_copy(int,int,int);
extern void dynamic_word_memory_copy(int,int,int);
extern void dynamic_byte_memory_copy(int,int,int);
extern void reverse_dynamic_byte_memory_copy(int,int,int);
extern void reverse_dynamic_word_memory_copy(int,int,int);
#endif
