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


#ifndef EXPRESSION_INCLUDED
#define EXPRESSION_INCLUDED


/*
 *    EXPRESSION CONSTRUCTION DECLARATIONS
 *
 *    The routines in this module are used to build up the basic expressions.
 *    They, and the similar routines in statement.c and elsewhere, are the
 *    main interface between the parser and the internal processing routines.
 */

extern EXP make_and_exp(EXP, EXP);
extern EXP make_comma_exp(LIST (EXP));
extern EXP make_cond_exp(EXP, EXP, EXP);
extern EXP make_equality_exp(int, EXP, EXP);
extern EXP make_error_exp(int);
extern EXP make_index_exp(EXP, EXP);
extern EXP make_indir_exp(EXP);
extern EXP make_log_and_exp(EXP, EXP);
extern EXP make_log_or_exp(EXP, EXP);
extern EXP make_minus_exp(EXP, EXP);
extern EXP make_mult_exp(int, EXP, EXP);
extern EXP make_not_exp(EXP);
extern EXP make_or_exp(EXP, EXP);
extern EXP make_paren_exp(EXP);
extern EXP make_plus_exp(EXP, EXP);
extern EXP make_ref_exp(EXP, int);
extern EXP make_ref_object(EXP, ERROR *);
extern EXP make_relation_exp(int, EXP, EXP);
extern EXP make_rem_exp(EXP, EXP);
extern EXP make_shift_exp(int, EXP, EXP);
extern EXP make_uminus_exp(int, EXP);
extern EXP make_xor_exp(EXP, EXP);
extern EXP join_exp(EXP, EXP);

extern OFFSET make_off_mult(TYPE, EXP, int);
extern EXP make_add_ptr(TYPE, EXP, OFFSET);
extern EXP make_null_ptr(EXP, TYPE);
extern int check_div_exp(int, EXP, EXP);
extern int check_shift_exp(int, TYPE, EXP, EXP);
extern int division_mode;


#endif
