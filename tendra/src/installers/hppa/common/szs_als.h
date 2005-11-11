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


#ifndef SZS_ALS_INCLUDED
#define SZS_ALS_INCLUDED


/*
 *    BASIC SIZES AND ALIGNMENTS
 */

#define TOP_SZ			((long) 0)
#define TOP_ALIGN		const_al1

#define PROC_SZ			((long) 32)
#define PROC_ALIGN		const_al32

#define LLVALUE_SZ		((long) 32)
#define LLVALUE_ALIGN		const_al32

#define PTR_SZ			((long) 32)
#define PTR_ALIGN		const_al32
#define PTRBIT_SZ		((long) 32)

#define OFFSET_SZ		((long) 32)
#define OFFSET_ALIGN		const_al32

#define BF_ALIGN		const_al1
#define STRUCT_ALIGN		const_al8

#define SHREAL_SZ		((long) 32)
#define SHREAL_ALIGN		const_al32

#define REAL_SZ			((long) 64)
#define REAL_ALIGN		const_al64


#if use_long_double

#define DOUBLE_SZ		((long) 128)
#define DOUBLE_ALIGN		const_al64

#else

#define DOUBLE_SZ		REAL_SZ
#define DOUBLE_ALIGN		REAL_ALIGN

#endif


#define UCHAR_SZ		((long) 8)
#define UCHAR_ALIGN		const_al8

#define SCHAR_SZ		((long) 8)
#define SCHAR_ALIGN		const_al8

#define UWORD_SZ		((long) 16)
#define UWORD_ALIGN		const_al16

#define SWORD_SZ		((long) 16)
#define SWORD_ALIGN		const_al16

#define ULONG_SZ		((long) 32)
#define ULONG_ALIGN		const_al32

#define SLONG_SZ		((long) 32)
#define SLONG_ALIGN		const_al32

#define U64_ALIGN const_al32
#define U64_SZ (long)64

#define S64_ALIGN const_al32
#define S64_SZ (long)64

#define BF_STORE_UNIT		((long) 32)
#define MAX_BF_SIZE		const_al32

#define ALLOCA_ALIGN		const_al64
#define FRAME_ALIGN		const_al32
#define VAR_PARAM_ALIGN		const_al32
#define CODE_ALIGN		const_al32
#define MIN_PAR_ALIGNMENT       const_al32

/*
 *    FLOATING POINT MANTISSA SIZES
 */

#define FLOAT_BITS		24
#define DOUBLE_BITS		53

#if use_long_double
#define LDOUBLE_BITS               113
#else
# define LDOUBLE_BITS		64
#endif

#endif /* SZS_ALS_INCLUDED */






