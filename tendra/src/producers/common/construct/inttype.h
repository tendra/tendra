/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


#ifndef INTTYPE_INCLUDED
#define INTTYPE_INCLUDED


/*
    TYPE REPRESENTING FUNDAMENTAL TYPE INFORMATION

    This type is used to represent the fundamental information about a
    built-in type.
*/

typedef struct {
	BASE_TYPE rep;
	unsigned min_bits;
	unsigned max_bits;
	BASE_TYPE sign;
	int key;
	TYPE set;
} BASE_INFO;


/*
    INTEGRAL TYPE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of the integral C and C++ types.
*/

extern void init_itypes(int);
extern void term_itypes(void);
extern void set_char_sign(BASE_TYPE);
extern void set_promote_type(TYPE, TYPE, BUILTIN_TYPE);
extern void compute_promote_type(IDENTIFIER);
extern void set_builtin_type(BASE_TYPE, TYPE);
extern void set_long_long_type(int);
extern void set_exact_types(void);
extern unsigned find_type_size(TYPE, unsigned *, BASE_TYPE *);
extern BUILTIN_TYPE is_builtin_type(TYPE, int);
extern TYPE make_itype(INT_TYPE, INT_TYPE);
extern TYPE make_ftype(FLOAT_TYPE, FLOAT_TYPE);
extern TYPE arith_itype(TYPE, TYPE, EXP, EXP);
extern TYPE arith_ftype(TYPE, TYPE);
extern TYPE promote_itype(INT_TYPE, INT_TYPE);
extern TYPE promote_ftype(FLOAT_TYPE, FLOAT_TYPE);
extern TYPE apply_itype_token(IDENTIFIER, LIST(TOKEN));
extern TYPE apply_ftype_token(IDENTIFIER, LIST(TOKEN));
extern INT_TYPE expand_itype(INT_TYPE);
extern BASE_TYPE key_type(int);

extern LIST(TYPE) all_llong_types;
extern LIST(TYPE) all_prom_types;
extern LIST(TYPE) all_int_types;
extern BASE_INFO basetype_info[];

extern int min_builtin_cast;
extern int safe_builtin_cast;
extern int max_builtin_cast;

extern unsigned char builtin_casts[ORDER_ntype][ORDER_ntype];
#define builtin_cast(A, B)	((int)builtin_casts[A][B])


#endif
