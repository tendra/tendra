/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED


/*
    TDF TOKEN DECLARATIONS

    The routines in this module are concerned with the construction of
    TDF tokens.
*/

extern IDENTIFIER make_token_decl(TOKEN, int, IDENTIFIER, IDENTIFIER);
extern IDENTIFIER make_tok_param(TOKEN, int, IDENTIFIER);
extern IDENTIFIER prog_tok_param(IDENTIFIER, TYPE, unsigned, LIST(IDENTIFIER));

extern TOKEN begin_proc_token(void);
extern TOKEN cont_proc_token(TOKEN, LIST(IDENTIFIER), LIST(IDENTIFIER));
extern TOKEN end_proc_token(TOKEN, TOKEN);
extern void set_proc_token(LIST(IDENTIFIER));

extern TOKEN make_func_token(TYPE);
extern TOKEN make_type_token(BASE_TYPE);
extern TOKEN make_exp_token(TYPE, int, int);
extern TOKEN make_member_token(TYPE, TYPE, DECL_SPEC);
extern TOKEN func_proc_token(TOKEN);
extern int type_token_key(BASE_TYPE);

extern EXP expand_exp(EXP, int, int);
extern NAT expand_nat(NAT, int, int, ERROR *);
extern OFFSET expand_offset(OFFSET, int);
extern TYPE expand_type(TYPE, int);
extern TOKEN expand_sort(TOKEN, int, int);
extern CLASS_TYPE expand_ctype(CLASS_TYPE, int, TYPE *);
extern LIST(TOKEN) expand_args(LIST(TOKEN), int, int);
extern LIST(TYPE) expand_exceptions(LIST(TYPE), int, int *);
extern TOKEN expand_templ_sort(TOKEN, int);
extern void reset_templ_sort(TOKEN);
extern int expand_anon_bitfield;

extern EXP apply_exp_token(IDENTIFIER, LIST(TOKEN), int);
extern NAT apply_nat_token(IDENTIFIER, LIST(TOKEN));
extern OFFSET apply_mem_token(IDENTIFIER, LIST(TOKEN));
extern TYPE apply_type_token(IDENTIFIER, LIST(TOKEN), IDENTIFIER);
extern TOKEN apply_token(IDENTIFIER, LIST(TOKEN));

extern IDENTIFIER find_token(IDENTIFIER);
extern IDENTIFIER find_tag_token(IDENTIFIER);
extern IDENTIFIER find_mem_token(IDENTIFIER, IDENTIFIER);
extern IDENTIFIER find_func_token(IDENTIFIER, unsigned);
extern IDENTIFIER find_ext_token(IDENTIFIER);
extern IDENTIFIER tok_member(IDENTIFIER, TYPE, int);
extern void token_interface(IDENTIFIER, int);
extern int crt_interface;


#endif
