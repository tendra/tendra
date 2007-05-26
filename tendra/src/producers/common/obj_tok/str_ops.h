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

#ifndef STR_OPS_H_INCLUDED
#define STR_OPS_H_INCLUDED

/* Operations for union STRING */

#pragma token PROC(EXP : STRING :) EXP : unsigned : TAG_str #
#pragma interface TAG_str


/* Operations for component next of union STRING */

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(STRING) : str_next #
#pragma interface str_next

/* Operations for field simple of union STRING */

#pragma token EXP const : unsigned : str_simple_tag #
#pragma token PROC(EXP : STRING :) EXP : int : IS_str_simple #
#pragma interface str_simple_tag IS_str_simple

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(ulong_type) : str_simple_len #
#pragma interface str_simple_len

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(string) : str_simple_text #
#pragma interface str_simple_text

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(unsigned) : str_simple_kind #
#pragma interface str_simple_kind

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(ulong_type) : str_simple_tok #
#pragma interface str_simple_tok

#pragma token PROC(\
	EXP : ulong_type :,\
	EXP : string :,\
	EXP : unsigned :,\
	EXP lvalue : STRING :\
    ) STATEMENT MAKE_str_simple #
#pragma interface MAKE_str_simple

#pragma token PROC(\
	EXP lvalue : STRING :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : ulong_type :,\
	EXP : STRING :\
    ) STATEMENT DECONS_str_simple #
#pragma interface DECONS_str_simple

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : STRING :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : ulong_type :,\
	EXP : STRING :\
    ) STATEMENT DESTROY_str_simple #
#pragma interface DESTROY_str_simple


#endif
