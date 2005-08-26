/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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


#ifndef __INT64_h
#define __INT64_h

extern INT64	make_INT64(INT32, UINT32);
extern UINT64	make_UINT64(UINT32, UINT32);

extern INT64	__TDFUs_plus(INT64, INT64);
extern UINT64	__TDFUu_plus(UINT64, UINT64);
extern INT64	__TDFUs_minus(INT64, INT64);
extern UINT64	__TDFUu_minus(UINT64, UINT64);
extern INT64	__TDFUs_mult(INT64, INT64);
extern UINT64	__TDFUu_mult(UINT64, UINT64);
extern INT64	__TDFUs_div1(INT64, INT64);
extern INT64	__TDFUs_div2(INT64, INT64);
extern UINT64	__TDFUu_div2(UINT64, UINT64);
extern INT64	__TDFUs_rem1(INT64, INT64);
extern INT64	__TDFUs_rem2(INT64, INT64);
extern UINT64	__TDFUu_rem2(UINT64, UINT64);
extern INT64	__TDFUneg(INT64);
extern UINT64	__TDFUu_shl(UINT64, UINT32);
extern UINT64	__TDFUu_shr(UINT64, UINT32);
extern INT64	__TDFUabs(INT64);
extern INT64	__TDFUsswiden(INT32);
extern UINT64	__TDFUsuwiden(INT32);
extern UINT64	__TDFUuuwiden(UINT32);
extern INT64	__TDFUuswiden(UINT32);
extern INT32	__TDFUssshorten(INT64);
extern UINT32	__TDFUsushorten(INT64);
extern UINT32	__TDFUuushorten(UINT64);
extern INT32	__TDFUusshorten(UINT64);
extern INT64	__TDFUu642s64(UINT64);
extern UINT64	__TDFUs642u64(INT64);
extern INT64	__TDFUs_max(INT64, INT64);
extern UINT64	__TDFUu_max(UINT64, UINT64);
extern INT64	__TDFUs_min(INT64, INT64);
extern UINT64	__TDFUu_min(UINT64, UINT64);
extern int	__TDFUs_test(INT64, INT64);
extern int	__TDFUu_test(UINT64, UINT64);
extern UINT64	__TDFUand(UINT64, UINT64);
extern UINT64	__TDFUor(UINT64, UINT64);
extern UINT64	__TDFUxor(UINT64, UINT64);
extern UINT64	__TDFUnot(UINT64);

extern INT64 const_0;
extern UINT64 const_u0;
extern INT64 const_1;
extern UINT64 const_u1;

extern void INT64_print(char *,  INT64, char *);
extern void UINT64_print(char *, UINT64, char *);

#endif  /* ndef __INT64_h */
