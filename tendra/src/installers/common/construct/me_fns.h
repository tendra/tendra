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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/



extern exp me_u1(error_treatment ov_err, exp arg1, unsigned char nm);
extern exp me_u2(exp arg1, unsigned char nm);
extern exp me_u3(shape sha, exp arg1, unsigned char nm);
extern exp me_b1(error_treatment ov_err, exp arg1, exp arg2, unsigned char nm);
extern exp me_b2(exp arg1, exp arg2, unsigned char nm);
extern exp me_b3(shape sha, exp arg1, exp arg2, unsigned char nm);
extern exp me_b4(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2, unsigned char nm);
extern exp me_c1(shape sha, error_treatment ov_err, exp arg1, unsigned char nm);
extern exp me_c2(shape sha, exp arg1, unsigned char nm);
extern exp me_l1(shape sha, unsigned char nm);
extern exp me_q1(nat_option prob, ntest nt, label dest, exp arg1,
				 exp arg2, unsigned char nm);
extern exp me_q2(nat_option prob, error_treatment err, ntest nt,
				 label dest, exp arg1, exp arg2, unsigned char nm);
extern exp me_q1_aux(nat_option prob, ntest nt, exp lab,
					 exp arg1, exp arg2, unsigned char nm);
extern exp me_q2_aux(nat_option prob, error_treatment err,
					 ntest nt, exp lab, exp arg1, exp arg2, unsigned char nm);
extern exp me_shint(shape sha, int i);
extern exp me_obtain(exp id);
extern exp me_startid(shape sha, exp def, int isv);
extern exp me_start_clearvar(shape idsh, shape initsh);
extern exp me_complete_id(exp id, exp body);
extern void note_repeat(exp r);
extern alignment long_to_al(int n);
extern int is_integer(shape s);
extern int is_float(shape s);
extern int is_complex(shape s);
extern exp me_null(shape sha, int i, unsigned char nm);
extern floating_variety float_to_complex_var(floating_variety f);
extern floating_variety complex_to_float_var(floating_variety s);

extern void clear_exp_list(exp_list el);
/* defined in install_fns.c */
