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

#ifndef CTYPE_OPS_H_INCLUDED
#define CTYPE_OPS_H_INCLUDED

/* Operations for union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :) EXP : unsigned : TAG_ctype #
#pragma interface TAG_ctype


/* Operations for component name of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(IDENTIFIER) : ctype_name #
#pragma interface ctype_name

/* Operations for component info of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(CLASS_INFO) : ctype_info #
#pragma interface ctype_info

/* Operations for component usage of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(CLASS_USAGE) : ctype_usage #
#pragma interface ctype_usage

/* Operations for component member of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(NAMESPACE) : ctype_member #
#pragma interface ctype_member

/* Operations for component base of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(GRAPH) : ctype_base #
#pragma interface ctype_base

/* Operations for component no_bases of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(unsigned) : ctype_no_bases #
#pragma interface ctype_no_bases

/* Operations for component prev of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(TYPE) : ctype_prev #
#pragma interface ctype_prev

/* Operations for component form of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(TYPE) : ctype_form #
#pragma interface ctype_form

/* Operations for component constr of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(IDENTIFIER) : ctype_constr #
#pragma interface ctype_constr

/* Operations for component destr of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(IDENTIFIER) : ctype_destr #
#pragma interface ctype_destr

/* Operations for component virt of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(VIRTUAL) : ctype_virt #
#pragma interface ctype_virt

/* Operations for component vbase of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(LIST(GRAPH)) : ctype_vbase #
#pragma interface ctype_vbase

/* Operations for component conv of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(LIST(IDENTIFIER)) : ctype_conv #
#pragma interface ctype_conv

/* Operations for component chums of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(LIST(CLASS_TYPE)) : ctype_chums #
#pragma interface ctype_chums

/* Operations for component pals of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(LIST(IDENTIFIER)) : ctype_pals #
#pragma interface ctype_pals

/* Operations for component nest of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(LIST(IDENTIFIER)) : ctype_nest #
#pragma interface ctype_nest

/* Operations for component tok1 of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(ulong_type) : ctype_tok1 #
#pragma interface ctype_tok1

/* Operations for component tok2 of union CLASS_TYPE */

#pragma token PROC(EXP : CLASS_TYPE :)\
    EXP : PTR(ulong_type) : ctype_tok2 #
#pragma interface ctype_tok2

/* Operations for field basic of union CLASS_TYPE */

#pragma token EXP const : unsigned : ctype_basic_tag #
#pragma token PROC(EXP : CLASS_TYPE :) EXP : int : IS_ctype_basic #
#pragma interface ctype_basic_tag IS_ctype_basic

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : CLASS_INFO :,\
	EXP : CLASS_USAGE :,\
	EXP : NAMESPACE :,\
	EXP : GRAPH :,\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP lvalue : CLASS_TYPE :\
    ) STATEMENT MAKE_ctype_basic #
#pragma interface MAKE_ctype_basic

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : CLASS_USAGE :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(CLASS_TYPE) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : CLASS_TYPE :\
    ) STATEMENT DECONS_ctype_basic #
#pragma interface DECONS_ctype_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : CLASS_USAGE :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(CLASS_TYPE) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : CLASS_TYPE :\
    ) STATEMENT DESTROY_ctype_basic #
#pragma interface DESTROY_ctype_basic


#endif
