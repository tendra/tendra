/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef BITMACS_H
#define BITMACS_H

/*
 * props of needs 
 */
#define morefix 0x100
#define morefloat 0x200
#define hasproccall 0x400
#define usesproccall 0x800	/* hasproccall << 1 */
#define anyproccall 0xc00
#define long_result_bit 0x1000
#define has_result_bit 0x2000
#define regsused 0xd00		/* morefix | usesproccall | hasproccall */
#define fregsused 0xe00		/* morefix | usesproccall | hasproccall */
#define realresult_bit  0x4000
#define longrealresult_bit  0x8000
#define uses_R_RESULT_bit 0x2
#define uses_FR_RESULT_bit 0x1

/*
 * props of ident 
 * (16 bits available, lower 8 used by common code) 
 */
/* #define subvar       0x0100  redefined as this in foralls.c*/
#define inreg_bits   0x0800
#define infreg_bits  0x1000
#define inanyreg     0x1800
#define defer_bit    0x2000
#define notparreg    0x4000
#define notresreg    0x8000
#define vararg_bit   0x0400 /* Set for the last ident param if vararg */
/*
 * props of real operations 
 */
#define SetRev(e)	(props(e) |= 0x1000)
#define IsRev(e)	((props(e) & 0x1000)!=0)
#define ClearRev(e)	(props(e) &= ~0x1000)

#endif /* bitmacs.h */
