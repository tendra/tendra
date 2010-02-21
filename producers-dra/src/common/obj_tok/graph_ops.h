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

#ifndef GRAPH_OPS_H_INCLUDED
#define GRAPH_OPS_H_INCLUDED

/* Operations for union GRAPH */

#pragma token PROC(EXP : GRAPH :) EXP : unsigned : TAG_graph #
#pragma interface TAG_graph


/* Operations for component head of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(CLASS_TYPE) : graph_head #
#pragma interface graph_head

/* Operations for component access of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(DECL_SPEC) : graph_access #
#pragma interface graph_access

/* Operations for component tails of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(LIST(GRAPH)) : graph_tails #
#pragma interface graph_tails

/* Operations for component top of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(GRAPH) : graph_top #
#pragma interface graph_top

/* Operations for component equal of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(GRAPH) : graph_equal #
#pragma interface graph_equal

/* Operations for component up of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(GRAPH) : graph_up #
#pragma interface graph_up

/* Operations for component no of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(unsigned) : graph_no #
#pragma interface graph_no

/* Operations for component off of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(OFFSET) : graph_off #
#pragma interface graph_off

/* Operations for component member of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(LIST(IDENTIFIER)) : graph_member #
#pragma interface graph_member

/* Operations for component tok1 of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(ulong_type) : graph_tok1 #
#pragma interface graph_tok1

/* Operations for component tok2 of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(ulong_type) : graph_tok2 #
#pragma interface graph_tok2

/* Operations for field basic of union GRAPH */

#pragma token EXP const : unsigned : graph_basic_tag #
#pragma token PROC(EXP : GRAPH :) EXP : int : IS_graph_basic #
#pragma interface graph_basic_tag IS_graph_basic

#pragma token PROC(\
	EXP : CLASS_TYPE :,\
	EXP : DECL_SPEC :,\
	EXP lvalue : GRAPH :\
    ) STATEMENT MAKE_graph_basic #
#pragma interface MAKE_graph_basic

#pragma token PROC(\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : GRAPH :\
    ) STATEMENT DECONS_graph_basic #
#pragma interface DECONS_graph_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : GRAPH :\
    ) STATEMENT DESTROY_graph_basic #
#pragma interface DESTROY_graph_basic


#endif
