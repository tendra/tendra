/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


#ifndef MACH_OP_INCLUDED
#define MACH_OP_INCLUDED

extern bool check_op(mach_op *, int) ;
extern bool equal_op(mach_op *, mach_op *) ;
extern void free_mach_op(mach_op *) ;
extern mach_op * new_mach_op(void) ;

extern mach_op * make_bitfield_op(mach_op *, int, int) ;
extern mach_op * make_dec_sp(void) ;
extern mach_op * make_extern(char *, long) ;
extern mach_op * make_extern_data(char *, long) ;
extern mach_op * make_extern_ind(char *, long) ;
extern mach_op * make_float_data(flt *) ;
extern mach_op * make_hex_data(long) ;
extern mach_op * make_hex_value(long) ;
extern mach_op * make_inc_sp(void) ;
extern mach_op * make_ind_rel_ap(long, long) ;
extern mach_op * make_index_op(mach_op *, mach_op *, int) ;
extern mach_op * make_indirect(int, long) ;
extern mach_op * make_int_data(long) ;
extern mach_op * make_lab(long, long) ;
extern mach_op * make_lab_data(long, long) ;
extern mach_op * make_lab_diff(long, long) ;
extern mach_op * make_lab_ind(long, long) ;
extern mach_op * make_postinc(int) ;
extern mach_op * make_reg_index(int, int, long, int) ;
extern mach_op * make_reg_pair(int, int) ;
extern mach_op * make_register(int) ;
extern mach_op * make_rel_ap(long) ;

#ifndef tdf3
extern mach_op * make_rel_ap2(long) ;
extern mach_op * make_rel_sp(long) ;
extern mach_op * make_ind_rel_ap2(long, long) ;
extern mach_op * make_ind_rel_ap3(long, long) ;
extern mach_op * make_predec(int) ;
extern mach_op * make_ldisp(long) ;
#endif

extern mach_op * make_special(char *) ;
extern mach_op * make_special_data(char *) ;
extern mach_op * make_value(long) ;

extern long special_no;
extern char *special_str;

extern int tmp_reg_prefer;
extern int tmp_reg_status;
extern void avoid_tmp_reg(int) ;
extern int next_tmp_reg(void) ;
extern int tmp_reg(int, mach_op *) ;

#endif
