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


#ifndef STRUCT_INCLUDED
#define STRUCT_INCLUDED


/*
 *    TDF CLASS ENCODING ROUTINES
 *
 *    The routines in this module are concerned with the mappings of classes
 *    to TDF SHAPEs.
 */

#if TDF_OUTPUT
extern ulong compile_class(CLASS_TYPE) ;
extern BITSTREAM *enc_null_class(BITSTREAM *, CLASS_TYPE) ;
extern BITSTREAM *enc_ctor_init(BITSTREAM *, EXP) ;
extern BITSTREAM *enc_member(BITSTREAM *, IDENTIFIER) ;
extern BITSTREAM *enc_al_ctype(BITSTREAM *, CLASS_TYPE) ;
extern BITSTREAM *enc_ctype(BITSTREAM *, CLASS_TYPE) ;
extern BITSTREAM *enc_base(BITSTREAM *, GRAPH, int) ;
extern BITSTREAM *enc_add_base(BITSTREAM *, OFFSET, OFFSET) ;
extern BITSTREAM *enc_end_base(BITSTREAM *, OFFSET, OFFSET) ;
extern BITSTREAM *enc_rtti_type(BITSTREAM *, TYPE, int) ;
extern BITSTREAM *enc_rtti_exp(BITSTREAM *, EXP) ;
extern BITSTREAM *enc_dyn_cast(BITSTREAM *, EXP) ;
extern BITSTREAM *enc_vtable_shape(BITSTREAM *, ulong) ;
extern ulong virtual_no(IDENTIFIER, VIRTUAL) ;
extern void define_vtable(CLASS_TYPE, int, int) ;
extern void compile_incompl(void) ;
extern IDENTIFIER dummy_type_name;
extern OFFSET off_size_t;
extern ulong size_dummy_vtab;
extern TYPE ptr_dummy_class;
extern TYPE ptr_dummy_vtab;
extern TYPE dummy_class;
extern TYPE dummy_count;
extern TYPE dummy_vtab;
extern TYPE dummy_func;
#endif


#endif
