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


#ifndef flpt_key
#define flpt_key 1



#include "flpttypes.h"

extern  void init_flpt(void);
extern  void more_flpts(void);
extern  flpt new_flpt(void);
extern  void flpt_ret(flpt f);
extern  int cmpflpt(flpt a, flpt b, int testno);
extern  flpt floatrep(int n);
extern  flpt floatrep_unsigned(unsigned int n);
extern  flt * flptnos;

/* floatingpoint functions - are these needed externally??? */
extern  void flt_zero(flt * f);
extern  void flt_copy(flt f, flt * res);
extern int  flt_add(flt f1, flt f2, flt * res);
extern int  flt_sub(flt f1, flt f2, flt * res);
extern int  flt_mul(flt f1, flt f2, flt * res);
extern int  flt_div(flt f1, flt f2, flt * res);
extern int  flt_cmp(flt f1, flt f2);
extern  void flt_round(flt f, flt * res);
extern  void flt_trunc(flt f, flt * res);
extern void flpt_newdig(unsigned int dig, flt * res, int base);
extern void flpt_scale(int decexp, flt * res, int base);
extern void flpt_round(int rdnmd, int pos, flt * res);
extern int flpt_bits(floating_variety fv);
extern int flpt_round_to_integer(int rndmd, flt * f);

#if FBASE != 10
extern r2l real2longs_IEEE(flt * f, int sw);
#endif

extern int fzero_no;
extern int fone_no;

#endif

