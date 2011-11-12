/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:04 $
$Revision: 1.1.1.1 $
$Log: loc_signal.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:04  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/15  09:20:00  currie
 * add SIGSEGV
 *
 * Revision 1.2  1995/06/28  10:17:48  currie
 * *** empty log message ***
 *
 * Revision 1.1  1995/04/13  09:33:41  currie
 * Initial revision
 *
***********************************************************************/
#ifndef MIPS_SIGFPE
 
#define MIPS_SIGFPE  8
#define MIPS_SIGSEGV 11
#define MIPS_SIGUSR1 30

#endif
