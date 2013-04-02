/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* regmacs.h
    defines good numbers for registers
*/

#define maxfix 18
#define maxfloat 15
/*
#define tempfix 0x300ff00
*/
/* corresponds to t0-t9 regs ,  maxfix regs */
#define tempfix 0x3ffff00

#define tempfloat 0x33c		/* corresponds to temp float regs,
				   maxfloat regs */
