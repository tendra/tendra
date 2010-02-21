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

#ifndef NAT_OPS_H_INCLUDED
#define NAT_OPS_H_INCLUDED

/* Operations for union NAT */

#pragma token PROC(EXP : NAT :) EXP : unsigned : TAG_nat #
#pragma interface TAG_nat


/* Operations for field small of union NAT */

#pragma token EXP const : unsigned : nat_small_tag #
#pragma token PROC(EXP : NAT :) EXP : int : IS_nat_small #
#pragma interface nat_small_tag IS_nat_small

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(unsigned) : nat_small_value #
#pragma interface nat_small_value

#pragma token PROC(\
	EXP : unsigned :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_small #
#pragma interface MAKE_nat_small

#pragma token PROC(\
	EXP lvalue : unsigned :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_small #
#pragma interface DECONS_nat_small

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : unsigned :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_small #
#pragma interface DESTROY_nat_small


/* Operations for field large of union NAT */

#pragma token EXP const : unsigned : nat_large_tag #
#pragma token PROC(EXP : NAT :) EXP : int : IS_nat_large #
#pragma interface nat_large_tag IS_nat_large

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(LIST(unsigned)) : nat_large_values #
#pragma interface nat_large_values

#pragma token PROC(\
	EXP : LIST(unsigned) :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_large #
#pragma interface MAKE_nat_large

#pragma token PROC(\
	EXP lvalue : LIST(unsigned) :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_large #
#pragma interface DECONS_nat_large

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : LIST(unsigned) :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_large #
#pragma interface DESTROY_nat_large


/* Operations for field calc of union NAT */

#pragma token EXP const : unsigned : nat_calc_tag #
#pragma token PROC(EXP : NAT :) EXP : int : IS_nat_calc #
#pragma interface nat_calc_tag IS_nat_calc

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(EXP) : nat_calc_value #
#pragma interface nat_calc_value

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(ulong_type) : nat_calc_tok #
#pragma interface nat_calc_tok

#pragma token PROC(\
	EXP : EXP :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_calc #
#pragma interface MAKE_nat_calc

#pragma token PROC(\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_calc #
#pragma interface DECONS_nat_calc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_calc #
#pragma interface DESTROY_nat_calc


/* Operations for field neg of union NAT */

#pragma token EXP const : unsigned : nat_neg_tag #
#pragma token PROC(EXP : NAT :) EXP : int : IS_nat_neg #
#pragma interface nat_neg_tag IS_nat_neg

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(NAT) : nat_neg_arg #
#pragma interface nat_neg_arg

#pragma token PROC(\
	EXP : NAT :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_neg #
#pragma interface MAKE_nat_neg

#pragma token PROC(\
	EXP lvalue : NAT :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_neg #
#pragma interface DECONS_nat_neg

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : NAT :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_neg #
#pragma interface DESTROY_nat_neg


/* Operations for field token of union NAT */

#pragma token EXP const : unsigned : nat_token_tag #
#pragma token PROC(EXP : NAT :) EXP : int : IS_nat_token #
#pragma interface nat_token_tag IS_nat_token

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(IDENTIFIER) : nat_token_tok #
#pragma interface nat_token_tok

#pragma token PROC(EXP : NAT :)\
    EXP : PTR(LIST(TOKEN)) : nat_token_args #
#pragma interface nat_token_args

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : LIST(TOKEN) :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_token #
#pragma interface MAKE_nat_token

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_token #
#pragma interface DECONS_nat_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_token #
#pragma interface DESTROY_nat_token


#endif
