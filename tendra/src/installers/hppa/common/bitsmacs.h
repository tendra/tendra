/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**/


#ifndef BITSMACS_INCLUDED
#define BITSMACS_INCLUDED


/*
 *    PROPERTIES FOR NEEDS
 */

#define morefix			0x0100
#define morefloat		0x0200
#define hasproccall		0x0400
#define usesproccall		0x0800	/* hasproccall << 1 */
#define anyproccall		0x0c00
#define long_result_bit 	0x1000
#define has_result_bit		0x2000
#define regsused		0x0d00	/* composite */
#define fregsused		0x0e00	/* composite */
#define realresult_bit		0x4000
#define longrealresult_bit  	0x8000
#define uses_res_reg_bit 	0x0002
#define dont_optimise 		0x0004
#define uses2_bit 2

/*
 *    HPPA-SPECIFIC IDENT PROPERTIES
 */

#define inreg_bits 		0x0800
#define infreg_bits 		0x1000
#define inanyreg 		0x1800
#define defer_bit 		0x2000
#define notparreg 		0x4000
#define notresreg 		0x8000
#define sreguse 		0x0200
#define inlined			0x0200
/* #define subvar 			0x0100 */

/*
 *    PROPERTIES OF REAL OPERATIONS
 */

#define SetRev(e)		props (e) |= 0x1000
#define IsRev(e)		(props (e) & 0x1000)
#define ClearRev(e)		props (e) &= ~0x1000


/*
 *    MISCELLANEOUS MACROS
 */

#define inlineassign		9
#define UNITWEIGHT		16.0


#endif /* BITSMACS_INCLUDED */

















