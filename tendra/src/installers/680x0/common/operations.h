/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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
 *    		 Crown Copyright (c) 1996
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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


#ifndef OPERATIONS_INCLUDED
#define OPERATIONS_INCLUDED
#include "ecodes.h"
extern bool have_cond;
extern bool D1_is_special;
extern int crt_rmode;

extern void absop(shape, where, where) ;
extern void add(shape, where, where, where) ;
extern void and(shape, where, where, where) ;
extern void bitf_to_int(exp, shape, where, ash) ;
extern void bit_test(shape, where, where) ;
extern void callins(long, exp) ;
extern void jmpins(exp) ;
extern void trap_ins(int) ;
extern void change_var_sh(shape, shape, where, where) ;
extern void change_var(shape, where, where) ;
extern bool cmp(shape, where, where, long) ;
extern void div1(shape, where, where, where) ;
extern void div2(shape, where, where, where) ;
extern void exactdiv(shape, where, where, where) ;
extern void int_to_bitf(exp, exp, ash) ;
extern void maxop(shape, where, where, where) ;
extern void minop(shape, where, where, where) ;
extern void mova(where, where) ;
extern void move(shape, where, where) ;
extern void move_const(shape, long, long, where) ;
extern void move_bytes(long, where, where, int) ;
extern void mult(shape, where, where, where) ;
extern void negate(shape, where, where) ;
extern void not(shape, where, where) ;
extern void or(shape, where, where, where) ;
extern void rem1(shape, where, where, where) ;
extern void rem2(shape, where, where, where) ;
extern void rshift(shape, where, where, where) ;
extern void shift(shape, where, where, where) ;
extern void sub(shape, where, where, where) ;
extern void xor(shape, where, where, where) ;

extern void abs_float(shape, where, where) ;
extern void change_flvar(shape, where, where) ;
extern void fl_binop(int, shape, where, where, where) ;
extern void int_to_float(shape, where, where) ;
extern void negate_float(shape, where, where) ;
extern void round_float(shape, where, where) ;

extern long range_max(shape);
extern long range_min(shape);

extern int overflow_jump;
extern int err_continue;

#define CONTINUE_ERR 2

#define set_continue(e) if (errhandle(e)==CONTINUE_ERR) err_continue = 1
#define clear_continue(e) (err_continue = 0)
#define have_continue() (err_continue != 0)
#endif
