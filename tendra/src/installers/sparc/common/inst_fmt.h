/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


#ifndef INST_FMT_INCLUDED
#define INST_FMT_INCLUDED

#include "addrtypes.h"
#include "sparcins.h"

/* special registers */
#define YREG	65
#define FSR	33

extern char *ext_name(int) ;

extern void ld_ro_ins(ins_p, baseoff, int) ;
extern void ld_rr_ins(ins_p, int, int, int) ;
extern void ld_ins(ins_p, baseoff, int) ;

extern void st_ro_ins(ins_p, int, baseoff) ;
extern void st_rr_ins(ins_p, int, int, int) ;
extern void st_ins(ins_p, int, baseoff) ;

extern void rrr_ins(ins_p, int, int, int) ;
extern void rir_ins(ins_p, int, long, int) ;
extern void rr_ins(ins_p, int, int) ;
extern void ir_ins(ins_p, long, int) ;
extern void lr_ins(int, int) ;

extern void set_ins(baseoff, int) ;
extern void z_ins(ins_p) ;
extern void unimp_ins(long) ;

extern void condrr_ins(ins_p, int, int, int) ;
extern void condri_ins(ins_p, int, long, int) ;
extern void fmaxminrr_ins(ins_p,int,int,int,int);
extern void maxminrr_ins(ins_p, int, int, int) ;
extern void maxminri_ins(ins_p, int, long, int) ;
extern void uncond_ins(ins_p, int) ;
extern void br_ins(ins_p, int) ;
extern void br_abs(int);
extern void lngjmp(int,int,int);

extern void extj_ins(ins_p, baseoff, int) ;
extern void extj_ins_without_delay(ins_p, baseoff, int) ;

extern void extj_special_ins(ins_p, CONST char * CONST, int) ;
extern void extj_special_ins_no_delay(ins_p, CONST char * CONST, int) ;
extern void extj_reg_ins(ins_p, int, int) ;
extern void extj_reg_ins_no_delay(ins_p, int, int) ;

extern void ret_ins(ins_p) ;
extern void ret_restore_ins(void) ;
extern void stret_restore_ins(void) ;

extern void ldf_ro_ins(ins_p, baseoff, int) ;
extern void ldf_rr_ins(ins_p, int, int, int) ;
extern void ldf_ins(ins_p, baseoff, int) ;
extern void stf_ro_ins(ins_p, int, baseoff) ;
extern void stf_rr_ins(ins_p, int, int, int) ;
extern void stf_ins(ins_p, int, baseoff) ;

extern void rrf_ins(ins_p, int, int) ;
extern void rrrf_ins(ins_p, int, int, int) ;

extern void rrf_cmp_ins(ins_p, int, int) ;
extern void fbr_ins(ins_p, int) ;

extern void out_asm_reg(int, int) ;
extern void out_asm_boff(baseoff, long) ;

#endif /* INST_FMT_INCLUDED */
