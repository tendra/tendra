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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/

#ifndef dg_aux_key
#define dg_aux_key

extern dg_name new_dg_name(dg_name_key k);
extern dg_type new_dg_type(dg_type_key k);
extern dg_info new_dg_info(dg_info_key k);
extern void extend_dg_name(dg_name nm);
extern void extend_dg_type(dg_type nm);
extern void init_dgtag(dg_tag tg);
extern dg_tag gen_tg_tag(void);
extern dg_type get_qual_dg_type(dg_qual_type_key qual, dg_type typ);
extern dg_type get_dg_bitfield_type(dg_type typ, shape sha, bitfield_variety bv);
extern char * idname_chars(dg_idname nam);
extern dg_filename get_filename(long dat, char * host, char * path, char * name);
extern short_sourcepos shorten_sourcepos(dg_sourcepos pos);
extern short_sourcepos end_sourcepos(dg_sourcepos pos);
extern dg_type find_proc_type(dg_type t);

extern exp diaginfo_exp(exp e);

#ifdef NEWDIAGS

extern void diag_kill_id(exp id);
extern void set_obj_ref(dg_name nm);
extern exp copy_res_diag(exp e, dg_info d, exp var, exp lab);
extern exp diag_hold_check(exp e);
extern void start_diag_inlining(exp e, dg_name dn);
extern void end_diag_inlining(exp e, dg_name dn);
extern dg_info combine_diaginfo(dg_info d1, dg_info d2);
extern void diag_inline_result(exp e);
extern void dg_whole_comp(exp whole, exp comp);
extern void dg_complete_inline(exp whole, exp comp);
extern void dg_dead_code(exp dead, exp prev);
extern void dg_rdnd_code(exp rdnd, exp next);
extern void dg_detach_const(exp part, exp whole);
extern void dg_rem_ass(exp ass);
extern void dg_restruct_code(exp outer, exp inner, int posn);
extern void dg_extracted(exp nm, exp old);
extern void strip_dg_context(exp e);
extern void make_optim_dg(int reason, exp e);
extern exp copy_dg_separate(exp e);

#endif

extern exp relative_exp(shape s, token t);

#endif
