/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: bitsmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/22  15:49:13  currie
 * added outpar
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* bitsmacs.h
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

