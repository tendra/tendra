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


#ifndef CAST_INCLUDED
#define CAST_INCLUDED


/*
    TYPE CAST DECLARATIONS

    The routines in this module are concerned with casting types.
*/

extern EXP make_cast_exp(TYPE, EXP, int);
extern EXP make_static_cast_exp(TYPE, EXP, int);
extern EXP make_reinterp_cast_exp(TYPE, EXP, int);
extern EXP make_const_cast_exp(TYPE, EXP, int);
extern EXP make_new_cast_exp(int, TYPE, EXP, int);
extern EXP make_func_cast_exp(TYPE, LIST(EXP));
extern EXP make_base_cast(TYPE, EXP, OFFSET);

extern EXP cast_exp(TYPE, EXP, ERROR *, unsigned);
extern EXP cast_int_int(TYPE, EXP, ERROR *, unsigned, int);
extern EXP cast_int_float(TYPE, EXP, ERROR *, unsigned);
extern EXP cast_float_float(TYPE, EXP, ERROR *, unsigned);
extern EXP cast_ptr_ptr(TYPE, EXP, ERROR *, unsigned, int, int);
extern EXP cast_ptr_mem_ptr_mem(TYPE, EXP, ERROR *, unsigned, int, int);
extern EXP cast_class_class(TYPE, EXP, ERROR *, unsigned, int);
extern EXP cast_templ_type(TYPE, EXP, unsigned);
extern void cast_away_const(unsigned, ERROR *, unsigned);
extern EXP cast_token(TYPE, EXP, ERROR *, ERROR, unsigned);
extern void allow_conversion(IDENTIFIER);


/*
    CAST IDENTIFIERS

    These values are used to identify the various classes of cast expressions
    in cast_exp and related routines.  They form a bitpattern for the static,
    reinterpret and const casts.
*/

#define CAST_IMPLICIT			((unsigned)0x00)
#define CAST_STATIC			((unsigned)0x01)
#define CAST_REINTERP			((unsigned)0x02)
#define CAST_CONST			((unsigned)0x04)
#define CAST_BAD			((unsigned)0x08)
#define CAST_EXPLICIT			((unsigned)0x0f)
#define CAST_DYNAMIC			((unsigned)0x10)
#define CAST_STANDARD			((unsigned)0x20)


#endif
