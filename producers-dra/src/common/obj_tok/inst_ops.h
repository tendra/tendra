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

#ifndef INST_OPS_H_INCLUDED
#define INST_OPS_H_INCLUDED

/* Operations for union INSTANCE */

#pragma token PROC(EXP : INSTANCE :) EXP : unsigned : TAG_inst #
#pragma interface TAG_inst


/* Operations for component form of union INSTANCE */

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(TYPE) : inst_form #
#pragma interface inst_form

/* Operations for component alias of union INSTANCE */

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(INSTANCE) : inst_alias #
#pragma interface inst_alias

/* Operations for component next of union INSTANCE */

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(INSTANCE) : inst_next #
#pragma interface inst_next

/* Operations for field templ of union INSTANCE */

#pragma token EXP const : unsigned : inst_templ_tag #
#pragma token PROC(EXP : INSTANCE :) EXP : int : IS_inst_templ #
#pragma interface inst_templ_tag IS_inst_templ

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(IDENTIFIER) : inst_templ_id #
#pragma interface inst_templ_id

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(TYPE) : inst_templ_spec #
#pragma interface inst_templ_spec

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(DECL_SPEC) : inst_templ_access #
#pragma interface inst_templ_access

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(PPTOKEN_P) : inst_templ_mode #
#pragma interface inst_templ_mode

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(LIST(IDENTIFIER)) : inst_templ_mems #
#pragma interface inst_templ_mems

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(INSTANCE) : inst_templ_prev #
#pragma interface inst_templ_prev

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : INSTANCE :,\
	EXP : IDENTIFIER :,\
	EXP : DECL_SPEC :,\
	EXP : INSTANCE :,\
	EXP lvalue : INSTANCE :\
    ) STATEMENT MAKE_inst_templ #
#pragma interface MAKE_inst_templ

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : INSTANCE :,\
	EXP : INSTANCE :\
    ) STATEMENT DECONS_inst_templ #
#pragma interface DECONS_inst_templ

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : INSTANCE :,\
	EXP : INSTANCE :\
    ) STATEMENT DESTROY_inst_templ #
#pragma interface DESTROY_inst_templ


/* Operations for field token of union INSTANCE */

#pragma token EXP const : unsigned : inst_token_tag #
#pragma token PROC(EXP : INSTANCE :) EXP : int : IS_inst_token #
#pragma interface inst_token_tag IS_inst_token

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(ulong_type) : inst_token_no #
#pragma interface inst_token_no

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : INSTANCE :,\
	EXP lvalue : INSTANCE :\
    ) STATEMENT MAKE_inst_token #
#pragma interface MAKE_inst_token

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : ulong_type :,\
	EXP : INSTANCE :\
    ) STATEMENT DECONS_inst_token #
#pragma interface DECONS_inst_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : ulong_type :,\
	EXP : INSTANCE :\
    ) STATEMENT DESTROY_inst_token #
#pragma interface DESTROY_inst_token


#endif
