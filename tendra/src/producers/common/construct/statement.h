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


#ifndef STATEMENT_INCLUDED
#define STATEMENT_INCLUDED


/*
 *    STATEMENT CONSTRUCTION DECLARATIONS
 *
 *    The routines in this module are used in the construction of the
 *    basic language statements.
 */

extern EXP begin_case_stmt(EXP, int);
extern EXP begin_compound_stmt(int);
extern EXP begin_default_stmt(int);
extern EXP begin_do_stmt(void);
extern EXP begin_for_stmt(void);
extern EXP begin_hash_if_stmt(EXP, EXP);
extern EXP begin_if_stmt(EXP);
extern EXP begin_switch_stmt(EXP);
extern EXP begin_while_stmt(EXP);

extern void mark_compound_stmt(EXP);
extern EXP add_compound_stmt(EXP, EXP);
extern EXP cont_hash_if_stmt(EXP, EXP, EXP);
extern EXP cont_if_stmt(EXP, EXP);
extern EXP init_for_stmt(EXP, EXP *);
extern EXP cond_for_stmt(EXP, EXP, EXP);

extern EXP end_case_stmt(EXP, EXP);
extern EXP end_compound_stmt(EXP);
extern EXP end_default_stmt(EXP, EXP);
extern EXP end_do_stmt(EXP, EXP, EXP);
extern EXP end_for_stmt(EXP, EXP);
extern EXP end_hash_if_stmt(EXP, EXP);
extern EXP end_if_stmt(EXP, EXP);
extern EXP end_switch_stmt(EXP, EXP, int);
extern EXP end_while_stmt(EXP, EXP);

extern EXP make_break_stmt(void);
extern EXP make_continue_stmt(void);
extern EXP make_decl_stmt(MEMBER, MEMBER, int *);
extern EXP make_temp_decl(MEMBER, MEMBER, EXP);
extern EXP make_exp_stmt(EXP);
extern EXP make_return_stmt(EXP, int);
extern EXP make_discard_exp(EXP);
extern EXP make_reach_stmt(EXP, int);
extern EXP fall_return_stmt(void);
extern EXP find_return_exp(EXP, IDENTIFIER *, int);
extern EXP check_return_exp(EXP, int);

extern EXP bind_temporary(EXP);
extern void begin_cond(void);
extern EXP end_cond(void);
extern EXP inject_cond(EXP, EXP);
extern TYPE make_cond_type(TYPE);
extern EXP check_cond(EXP, EXP *, int);
extern EXP check_control(EXP, EXP *, EXP *);
extern void check_empty_stmt(int);
extern EXP make_if_cond(EXP, EXP);
extern EXP make_else_cond(EXP);
extern IDENTIFIER find_case(LIST (NAT), LIST (IDENTIFIER), NAT);
extern EXP make_asm(EXP, LIST (EXP));

extern void set_parent_stmt(EXP, EXP);
extern EXP get_parent_stmt(EXP);
extern STACK (EXP) crt_loop_stack;
extern NAMESPACE block_namespace;
extern unsigned crt_condition;
extern int record_location;
extern int unreached_code;
extern int unreached_last;
extern int unreached_prev;
extern int unreached_fall;
extern int suppress_fall;
extern EXP crt_hash_cond;
extern LOCATION stmt_loc;


#endif
