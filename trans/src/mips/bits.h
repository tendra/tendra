/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    defines various good bits for props of ident and procrec
*/

/* props of needs */
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
#define uses2_bit 2

/* props of ident */
#define inreg_bits 0x800
#define infreg_bits 0x1000
#define inanyreg 0x1800
#define defer_bit 0x2000
#define notparreg 0x4000
#define subvar 0x100

#define PossParReg(e) ((props(e) & 0x400)!=0)
#define SetPossParReg(e) props(e) |= 0x400
#define ClearPossParReg(e) props(e) &= ~0x400


/* props of real operations */
#define SetRev(e) props(e) |= 0x1000
#define IsRev(e) ((props(e) & 0x1000)!=0)
#define ClearRev(e) props(e) &= ~0x1000

#define inlineassign 9


#define UNITWEIGHT 16

