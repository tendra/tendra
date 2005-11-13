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


/**/


#ifndef INST_FMT_INCLUDED
#define INST_FMT_INCLUDED

#include "addrtypes.h"
#include "hppains.h"

extern char *ext_name(long);

extern void ldmb_ins(ins_p, int, int, int);
extern void ld_ins(ins_p, int, baseoff, int);

extern void st_ins(ins_p, int, baseoff);

extern void riir_ins(ins_p, ins_p, int, long, long, int);

extern void ir_ins(ins_p, ins_p, const char*, long, int);

extern void imm_to_r(long, int);

extern void set_ins(char*, baseoff, int);
extern void z_ins(ins_p);

extern void condrr_ins(char, ins_p, int, int, int, int);
extern void condri_ins(ins_p, int, long, int);

extern void extj_special_ins(const char *, int, char *, int);
extern void extj_reg_ins(ins_p, int);

extern void ret_ins(ins_p);

extern void ldf_ro_ins(ins_p, baseoff, int);
extern void ldf_rr_ins(ins_p,ins_p, int, int, int);
extern void ldf_ins(ins_p, baseoff, int);
extern void stf_ro_ins(ins_p, int, baseoff);
extern void stf_rr_ins(ins_p, int, int, int);
extern void stf_ins(ins_p, int, baseoff);

extern void rrf_ins(ins_p,ins_p,ins_p, int, int);
extern void rrrf_ins(ins_p, ins_p, int, int, int);

extern void rrf_cmp_ins(ins_p, int, int);
extern void immr_ins(ins_p, char*,char*,long,char*,int);
extern void ld_immr_ins(ins_p, char*,char*,long,char*,int,int);
extern void st_immr_ins(ins_p,int, char*,char*,long,char*,int);
extern void iiir_ins(ins_p,ins_p,int,int,int,int);
extern void bb_in(ins_p,int,int,int);
extern void rr_ins(ins_p, int, int);
extern void rrr_ins(ins_p, ins_p, int, int, int);
extern void ub_ins(const char*, int);
extern void cj_ins(const char*, int, int, int);
extern void st_ir_ins(ins_p, ins_p, int, ins_p, const char*, long, int);
extern void ld_ir_ins(ins_p, ins_p, ins_p, const char*, long, int, int);
extern void comb_ins(const char*, int, int, int);
extern void cmp_rrf_ins(ins_p, ins_p, ins_p, int, int);
extern void rrir_ins(ins_p, ins_p, int, int, long, int);
extern void cij_ins(const char*, long, int, int);
extern void irr_ins(ins_p, ins_p, ins_p, long, int, int);
extern void ld_rr_ins(ins_p, ins_p, int, int, int);
extern void r_ins(ins_p, int);
extern void out_directive(const char*, const char*);
extern void iir_ins(ins_p, ins_p, int, int, int);
extern void rir_ins(ins_p, ins_p, int, long, int);
extern const char* reg_name(int);
extern void call_ins(ins_p, char*, int, char*);
extern void outlab(char*, int);
extern void bl_in(ins_p, char*, int);
extern void ble_in(ins_p, char*, int, int);

extern void comib_ins(ins_p, int, int, int);

extern int line;
extern int lines;
extern int nLabels;

#if FS_NO_ANSI_ENVIRON
typedef long FILE_POSN;
#define SET_FILE_POSN(A, B)		fseek ((A), (B), SEEK_SET)
#define GET_FILE_POSN(A, B)		(B) = ftell ((A))
#else
typedef fpos_t FILE_POSN;
#define SET_FILE_POSN(A, B)		fsetpos ((A), &(B))
#define GET_FILE_POSN(A, B)		fgetpos ((A), &(B))
#endif

typedef struct {
	FILE_POSN fpos;     /* position in outf  */
	ins_p  ins;        /* instruction       */
	ins_p  cc;        /* condition code    */
	int    op[4];    /* operands          */
	int    lab;     /* label             */
} psuedoIn;

typedef psuedoIn *pIn;

/* #define BLOCK 131072 */

#define BLOCK 65536
#define INCR  4096

extern pIn *pCode;
extern int *labIntro;  /*  `labIntro[lab]' will record the line number on
				 		*  which label `lab' was introduced. */



#endif /* INST_FMT_INCLUDED */
