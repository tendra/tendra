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
 *    		 Crown Copyright (c) 1997, 1998
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


#ifndef COMPILE_INCLUDED
#define COMPILE_INCLUDED


/*
 *    MAIN COMPILATION ROUTINES
 *
 *    The routines in this module are concerned with the main compilation
 *    actions of transforming declarations and definitions into TDF.
 */

extern void compile_variable(IDENTIFIER, int) ;
extern void compile_function(IDENTIFIER, int) ;
extern void compile_token(IDENTIFIER, int) ;
extern void compile_type(IDENTIFIER) ;
extern void compile_virtual(CLASS_TYPE, int) ;
extern void compile_asm(EXP) ;
extern void compile_comment(string, unsigned long) ;
extern void compile_preserve(IDENTIFIER) ;
extern void compile_pending(void) ;
extern void compile_weak(IDENTIFIER, IDENTIFIER) ;
extern void update_tag(IDENTIFIER, int) ;
extern LIST (IDENTIFIER) pending_funcs;

#if TDF_OUTPUT
extern void enc_tagdec(IDENTIFIER, ulong, TYPE, int) ;
extern BITSTREAM *enc_tagdec_start(IDENTIFIER, ulong, TYPE, int) ;
extern void enc_tagdec_end(BITSTREAM *) ;
extern BITSTREAM *enc_tagdef_start(IDENTIFIER, ulong, TYPE, int) ;
extern void enc_tagdef_end(BITSTREAM *) ;
extern ulong make_tagdef(IDENTIFIER, TYPE, EXP, EXP, int) ;
extern BITSTREAM *enc_variable(BITSTREAM *, IDENTIFIER, int, EXP *, EXP) ;
extern BITSTREAM *enc_access(BITSTREAM *, DECL_SPEC) ;
extern BITSTREAM *enc_tokdef_start(ulong, CONST char *, ulong *, int) ;
extern void enc_tokdef_end(ulong, BITSTREAM *) ;
extern void enc_tokdec(ulong, CONST char *) ;
extern int enc_tokdef(IDENTIFIER, int) ;
extern void enc_dynamic_init(void) ;
extern DECL_SPEC crt_func_access;
#endif


#endif
