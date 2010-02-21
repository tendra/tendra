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

#ifndef MEMBER_OPS_H_INCLUDED
#define MEMBER_OPS_H_INCLUDED

/* Operations for union MEMBER */

#pragma token PROC(EXP : MEMBER :) EXP : unsigned : TAG_member #
#pragma interface TAG_member


/* Operations for component id of union MEMBER */

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(IDENTIFIER) : member_id #
#pragma interface member_id

/* Operations for component alt of union MEMBER */

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(IDENTIFIER) : member_alt #
#pragma interface member_alt

/* Operations for component next of union MEMBER */

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(MEMBER) : member_next #
#pragma interface member_next

/* Operations for field small of union MEMBER */

#pragma token EXP const : unsigned : member_small_tag #
#pragma token PROC(EXP : MEMBER :) EXP : int : IS_member_small #
#pragma interface member_small_tag IS_member_small

#pragma token PROC(\
	EXP : MEMBER :,\
	EXP lvalue : MEMBER :\
    ) STATEMENT MAKE_member_small #
#pragma interface MAKE_member_small

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DECONS_member_small #
#pragma interface DECONS_member_small

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DESTROY_member_small #
#pragma interface DESTROY_member_small


/* Operations for field large of union MEMBER */

#pragma token EXP const : unsigned : member_large_tag #
#pragma token PROC(EXP : MEMBER :) EXP : int : IS_member_large #
#pragma interface member_large_tag IS_member_large

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(MEMBER) : member_large_tnext #
#pragma interface member_large_tnext

#pragma token PROC(\
	EXP : MEMBER :,\
	EXP : MEMBER :,\
	EXP lvalue : MEMBER :\
    ) STATEMENT MAKE_member_large #
#pragma interface MAKE_member_large

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DECONS_member_large #
#pragma interface DECONS_member_large

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DESTROY_member_large #
#pragma interface DESTROY_member_large


#endif
