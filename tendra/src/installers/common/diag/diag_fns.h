/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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
#ifndef diag_fns_key
#define diag_fns_key 1




extern void out_diagnose_prelude(void);
extern void out_diagnose_postlude(void);

extern void start_make_diagdef_unit(int toks, int tags, int als, int ndiags);
extern void f_make_diagdef_unit(void);


extern void init_capsule_diagtags(void);
extern void start_make_diagtype_unit(int toks, int tags, int als, int ndiagtype);
extern linkextern f_make_diagtagextern(tdfint i, external e);
extern void init_unit_diagtags(int n);


#ifdef NEWDIAGS

extern exp read_exp_to_source(exp body);
extern exp read_diag_id_scope(exp body);
extern exp read_diag_type_scope(exp body);
extern exp read_diag_tag_scope(exp body);

#else

extern diag_info * read_exp_to_source(void);
extern diag_info * read_diag_id_scope(void);
extern diag_info * read_diag_type_scope(void);
extern diag_info * read_diag_tag_scope(void);

#endif


#ifndef NEWDIAGS

extern void output_diag(diag_info * d, int proc_no, exp e);
extern void output_end_scope(diag_info * d, exp e);

extern void diag_proc_begin(diag_global * d, int global, int cname, char * pname);
extern void diag_proc_end(diag_global * d);

extern void diag_val_begin(diag_global * d, int global, int cname, char * pname);
extern void diag_val_end(diag_global * d);

#endif


extern int unit_no_of_diagtags;
extern diag_tagdef ** unit_ind_diagtags;

extern void f_make_diagtaglink(tdfint i, tdfint ext);

#ifdef NEWDIAGS
extern exp diag_locate(exp e);
#endif

#endif
