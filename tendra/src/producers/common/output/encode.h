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


#ifndef ENCODE_INCLUDED
#define ENCODE_INCLUDED


/*
 *    BITSTREAM SIZES
 *
 *    These macros give the number of bits in a byte and the number of
 *    bytes in a bitstream.
 */

#define BYTE_SIZE		((unsigned) 8)
#define CHUNK_SIZE		((unsigned) 64)
#define CHUNK_COPY		((unsigned) 8)
#define BYTE_MASK		((unsigned) 0xff)


/*
 *    ENCODING MACROS
 *
 *    These macros give shorthands for the main encoding routines which are
 *    used in this module.  Note that A is used at least twice in each
 *    definition.
 */

#define ENC_BITS(A, B, C)\
    tdf_en_bits ((A), (unsigned) (B), (unsigned) (C))

#define ENC_BITS_2(A, B, C)\
    tdf_en_bits ((A), (unsigned) (B), (ulong) (C))

#define ENC_EXTN(A, B, C)\
    tdf_en_tdfextint ((A), (unsigned) (B), (C))

#define ENC_INT(A, B)\
    tdf_en_tdfintl ((A), (B))

#define ENC_IDENT(A, B, C)\
    tdf_en_tdfident ((A), (C), (B))

#define ENC_ALIGN(A)\
    tdf_en_align ((A))

#define ENC_BOOL(A, B)	tdf_en_tdfbool(A, B)
#define ENC_ON(A)		ENC_BITS (A, 1, 1)
#define ENC_OFF(A)		ENC_BITS (A, 1, 0)
#define ENC_OFFS(A, B)	ENC_BITS (A, B, 0)


#endif
