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


/* 80x86/coderdecs.h */


#ifndef coder_key
#define coder_key 1

/*
 * 32-bit registers mask
 */
#define	REG_EAX		0x01
#define	REG_EDX		0x02
#define	REG_ECX		0x04
#define	REG_EBX		0x08
#define	REG_EDI		0x10
#define	REG_ESI		0x20
#define	REG_EBP		0x40
#define	REG_ESP		0x80
#define	REG_ALL_EXCEPT_EAX	(REG_EDX | REG_ECX | REG_EBX | REG_EDI | REG_ESI | REG_EBP)

/*
 * Special pseudo register to identify floating point stack
 */
#define	REG_FLSTACK	0x10000


extern void coder(where dest, ash stack, exp e);
extern int regsinuse;
extern int min_rfree;
extern int bits_in[16];
extern int max_stack;
extern int crt_ret_lab;
extern int crt_ret_lab_used;
extern outofline * odd_bits;
extern int last_odd_bit;
extern int doing_odd_bits;
extern outofline * current_odd_bit;
extern int repeat_level;
extern int not_in_params;
extern int not_in_postlude;
extern void clean_stack(void);
extern int retjmp_count;
extern float scale;
extern exp crt_proc_exp;
extern exp vc_pointer;
extern int callee_size;
extern int has_dy_callees;
extern int has_tail_call;
extern int has_same_callees;
extern int need_preserve_stack;
extern int proc_has_asm;

#ifdef NEWDIAGS
extern void diag_arg(where dest, ash stack, exp e);
#endif

#endif
