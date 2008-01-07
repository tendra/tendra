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


#ifndef ARITH_CODES_H
#define ARITH_CODES_H


/****integer classes	| ref data_structures:RANGE
 ****			| use simple_ts.h:
 ****			| ref syntax_analysis:type specifiers
 ****			| ref tokenised objects:
 ****/ 
/*sizes*/
#define t_char		(0)		/*char*/
#define t_short		(1)		/*short*/
#define t_int		(2)			/*int*/
#define t_long		(3)		/*long*/
/*signedness*/
#define t_none		(0)		/* 0>>2 no sign*/
#define t_signed	(4)		/* 1>>2 signed*/
#define t_unsigned	(8)		/* 2>>2 unsigned*/

#define variety_filter	(3)	/*masks to leave the size of a non-tokenised integer*/
#define sign_filter	(12)	/*masks to leave the sign of a non-tokenised integer*/

#define int_range (t_int|t_signed) /*the commonly used integer type 'int'*/



/****floating_types	| ref data_structures:REALLEX
 ****			| ref data_structures:floating types
 ****			| use simple_ts.h:
 ****			| ref syntax_analysis:type specifiers
 ****			| ref data_structures:RANGE
 ****/
#define t_float		(0)	/*float*/
#define t_double	(1)	/*double*/
#define t_long_double	(2)	/*long double*/

/****arithmetic_types
 ****/
#define int_to_arith(i)(i)
#define arith_to_int(a)(a)
#define float_to_arith(f)(((f)<<3)|0x80)
#define arith_to_float(a)(((a)&0x7f)>>3)


#endif
