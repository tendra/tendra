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
/* Hack : use enquire43, with corrections, to produce these values */

#ifndef __FLOAT_INCLUDED
#define __FLOAT_INCLUDED

#define FLT_RADIX	2
#define FLT_MANT_DIG	24
#define FLT_DIG		6
#define FLT_ROUNDS	1
#define FLT_EPSILON	1.19209290e-07F
#define FLT_MIN_EXP	(-125)
#define FLT_MIN		1.17549435e-38F
#define FLT_MIN_10_EXP	(-37)
#define FLT_MAX_EXP	128
#define FLT_MAX		3.40282347e+38F
#define FLT_MAX_10_EXP	38

#define DBL_MANT_DIG	53
#define DBL_DIG		15
#define DBL_EPSILON	2.2204460492503131e-16
#define DBL_MIN_EXP	(-1021)
#define DBL_MIN		2.2250738585072014e-308
#define DBL_MIN_10_EXP	(-307)
#define DBL_MAX_EXP	1024
#define DBL_MAX		1.7976931348623157e+308
#define DBL_MAX_10_EXP	308

#define LDBL_MANT_DIG	64
#define LDBL_DIG	18
#define LDBL_EPSILON	1.0842021724855044340075E-19L
#define LDBL_MIN	3.3621031431120935062627e-4932L
#define LDBL_MIN_EXP	(-16381)
#define LDBL_MIN_10_EXP	(-4931)
#define LDBL_MAX	1.1897314953572317650212e+4932L
#define LDBL_MAX_EXP	16384
#define LDBL_MAX_10_EXP	4932

#endif
