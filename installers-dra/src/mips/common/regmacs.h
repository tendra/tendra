/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: regmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* regmacs.h
    defines good numbers for registers
*/

#define maxfix 10
#define maxfloat 6

#define tempfix 0x300ff00	/* corresponds to t0-t9 regs , maxfix regs 
				*/

#define tempfloat 0x33c		/* corresponds to temp float regs,
				   maxfloat regs */
