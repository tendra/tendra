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


#ifndef INIT_INCLUDED
#define INIT_INCLUDED


/*
 *    TDF INITIALISATION ENCODING ROUTINES
 *
 *    The routines in this module are concerned with the encoding of
 *    initialisation expressions.
 */

#if TDF_OUTPUT
extern BITSTREAM *enc_init_tag(BITSTREAM *, ulong, OFFSET, int, TYPE, EXP, EXP, int) ;
extern BITSTREAM *enc_init_global(BITSTREAM *, EXP, EXP, ulong, TYPE) ;
extern BITSTREAM *enc_init_local(BITSTREAM *, EXP, EXP, ulong, TYPE, EXP) ;
extern BITSTREAM *enc_assign_local(BITSTREAM *, EXP, EXP, ulong, TYPE, EXP) ;
extern BITSTREAM *enc_init_array(BITSTREAM *, EXP, NAT, TYPE) ;
extern BITSTREAM *enc_init_class(BITSTREAM *, EXP, CLASS_TYPE) ;
extern BITSTREAM *enc_term_local(BITSTREAM *, ulong, OFFSET, int, TYPE, EXP, int) ;
extern BITSTREAM *enc_term_global(BITSTREAM *, ulong, TYPE, EXP, ulong) ;
extern BITSTREAM *enc_flag_test(BITSTREAM *, ulong, unsigned, int, NTEST) ;
extern BITSTREAM *enc_destr_count(BITSTREAM *, TYPE, int) ;
extern BITSTREAM *enc_term_type(BITSTREAM *, TYPE) ;
extern BITSTREAM *enc_dealloc(BITSTREAM *, EXP, ulong) ;
extern BITSTREAM *enc_alloc(BITSTREAM *, EXP) ;
extern BITSTREAM *make_term_local(BITSTREAM *, TYPE, EXP *, int) ;
extern void make_term_global(TYPE, EXP *) ;
extern EXP make_dummy_init(TYPE) ;
extern int is_init_complex(EXP) ;
extern int in_dynamic_init;
extern int in_static_init;
#endif


#endif
