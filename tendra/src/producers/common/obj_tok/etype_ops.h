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

#ifndef ETYPE_OPS_H_INCLUDED
#define ETYPE_OPS_H_INCLUDED

/* Operations for union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :) EXP : unsigned : TAG_etype #
#pragma interface TAG_etype


/* Operations for component name of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(IDENTIFIER) : etype_name #
#pragma interface etype_name

/* Operations for component info of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(CLASS_INFO) : etype_info #
#pragma interface etype_info

/* Operations for component rep of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(TYPE) : etype_rep #
#pragma interface etype_rep

/* Operations for component form of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(TYPE) : etype_form #
#pragma interface etype_form

/* Operations for component values of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(LIST(IDENTIFIER)) : etype_values #
#pragma interface etype_values

/* Operations for component value of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(EXP) : etype_value #
#pragma interface etype_value

/* Operations for component plus of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(ulong_type) : etype_plus #
#pragma interface etype_plus

/* Operations for field basic of union ENUM_TYPE */

#pragma token EXP const : unsigned : etype_basic_tag #
#pragma token PROC(EXP : ENUM_TYPE :) EXP : int : IS_etype_basic #
#pragma interface etype_basic_tag IS_etype_basic

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : CLASS_INFO :,\
	EXP : TYPE :,\
	EXP lvalue : ENUM_TYPE :\
    ) STATEMENT MAKE_etype_basic #
#pragma interface MAKE_etype_basic

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : ENUM_TYPE :\
    ) STATEMENT DECONS_etype_basic #
#pragma interface DECONS_etype_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : ENUM_TYPE :\
    ) STATEMENT DESTROY_etype_basic #
#pragma interface DESTROY_etype_basic


#endif
