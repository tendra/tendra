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
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef FLT_OPS_H_INCLUDED
#define FLT_OPS_H_INCLUDED

/* Operations for union FLOAT */

#pragma token PROC(EXP : FLOAT :) EXP : unsigned : TAG_flt #
#pragma interface TAG_flt


/* Operations for component tok of union FLOAT */

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(ulong_type) : flt_tok #
#pragma interface flt_tok

/* Operations for field simple of union FLOAT */

#pragma token EXP const : unsigned : flt_simple_tag #
#pragma token PROC(EXP : FLOAT :) EXP : int : IS_flt_simple #
#pragma interface flt_simple_tag IS_flt_simple

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(string) : flt_simple_int_part #
#pragma interface flt_simple_int_part

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(string) : flt_simple_frac_part #
#pragma interface flt_simple_frac_part

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(NAT) : flt_simple_exponent #
#pragma interface flt_simple_exponent

#pragma token PROC(\
	EXP : string :,\
	EXP : string :,\
	EXP : NAT :,\
	EXP lvalue : FLOAT :\
    ) STATEMENT MAKE_flt_simple #
#pragma interface MAKE_flt_simple

#pragma token PROC(\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : NAT :,\
	EXP : FLOAT :\
    ) STATEMENT DECONS_flt_simple #
#pragma interface DECONS_flt_simple

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : NAT :,\
	EXP : FLOAT :\
    ) STATEMENT DESTROY_flt_simple #
#pragma interface DESTROY_flt_simple


#endif
