/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
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
 */



/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/


#ifndef SZS_ALS_H
#define SZS_ALS_H

/*
 * BASIC SIZE AND ALIGNMENTS IN BITS
 */

#define  TOP_SZ			((long) 0)
#define  TOP_ALIGN		const_al1

#define  SCHAR_SZ		((long) 8)
#define  SCHAR_ALIGN		const_al8

#define  UCHAR_SZ		((long) 8)
#define  UCHAR_ALIGN		const_al8

#define  SWORD_SZ		((long) 16)
#define  SWORD_ALIGN		const_al16

#define  UWORD_SZ		((long) 16)
#define  UWORD_ALIGN		const_al16

#define  SLONG_SZ		((long) 32)
#define  SLONG_ALIGN		const_al32

#define  ULONG_SZ		((long) 32)
#define  ULONG_ALIGN		const_al32

/* 64 bit foxed points not used */
#define  S64_SZ                 ((long) 64)
#define  S64_ALIGN              const_al32

#define  U64_SZ                 ((long) 64)
#define  U64_ALIGN              const_al32


/* floating point */

#define  SHREAL_SZ		((long) 32)
#define  SHREAL_ALIGN		const_al32

/*
 * RS/6000 IBM & GNU C compiler align double (64 bit floating point) at 32bit,
 * hardware loads in 1 extra cycle.
 */
#define  REAL_SZ		((long) 64)
#define  REAL_ALIGN		const_al32

/* no good 128 bit floating point support RS/6000 */
#define  DOUBLE_SZ		((long) 64)
#define  DOUBLE_ALIGN		const_al32

#define  STRUCT_ALIGN		const_al8

#define  BF_ALIGN		const_al1
#define  BF_STORE_UNIT		((long) 32)
#define  MAX_BF_SIZE		const_al32

#define  PROC_SZ		((long) 32)
#define  PROC_ALIGN		const_al32

#define  PTR_SZ			((long) 32)
#define  PTR_ALIGN		const_al32

#define  PTRBIT_SZ		((long) 32)

#define  OFFSET_SZ		((long) 32)
#define  OFFSET_ALIGN		const_al32

/* LL is local label */
#define  LLVALUE_SZ		((long) 32)
#define  LLVALUE_ALIGN		const_al32



#define ALLOCA_ALIGN		const_al64
#define FRAME_ALIGN		const_al32
#define VAR_PARAM_ALIGN		const_al32
#define CODE_ALIGN		const_al32
/*
 * FLOATING POINT MANTISSA SIZES
 */

#define FLOAT_BITS		24
#define DOUBLE_BITS		53
#define LDOUBLE_BITS		113

#define MIN_PAR_ALIGNMENT       const_al32
#endif

