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
    		 Crown Copyright (c) 1997, 1998

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


#ifndef TEMPLATE_INCLUDED
#define TEMPLATE_INCLUDED


/*
    TEMPLATE DECLARATIONS

    The routines in this module are concerned with the declaration of
    templates.
*/

extern void init_templates(void);
extern TOKEN template_params(int);
extern TYPE make_template_type(TOKEN, TYPE);
extern void end_template(TOKEN);
extern void template_decl(TYPE);
extern TYPE check_templ_params(TYPE, IDENTIFIER);
extern int check_templ_dargs(TYPE);
extern void check_deduced_args(IDENTIFIER, LIST(IDENTIFIER), LIST(TOKEN));
extern void redecl_template(TYPE *, TYPE *, IDENTIFIER);
extern void reset_primary_templ(TYPE, TYPE);
extern LIST(TOKEN) make_primary_args(LIST(IDENTIFIER));
extern void export_template(IDENTIFIER, int);
extern int is_exported(IDENTIFIER);

extern IDENTIFIER make_type_param(IDENTIFIER);
extern IDENTIFIER make_exp_param(TYPE, IDENTIFIER);
extern IDENTIFIER make_template_param(TYPE, IDENTIFIER);
extern void init_type_param(IDENTIFIER, TYPE);
extern void init_exp_param(IDENTIFIER, EXP);
extern void init_template_param(IDENTIFIER, IDENTIFIER);
extern IDENTIFIER find_template(IDENTIFIER, int);
extern int is_templ_decl(IDENTIFIER, TYPE);
extern int is_templ_param(IDENTIFIER);
extern int is_templ_alias(IDENTIFIER);
extern int is_templ_type(TYPE);
extern int is_templ_spec(TYPE);
extern int is_templ_depend(TYPE);
extern int is_templ_nspace(NAMESPACE);

extern PPTOKEN *skip_template_args(IDENTIFIER, int);
extern IDENTIFIER parse_id_template(IDENTIFIER, PPTOKEN *, int);
extern IDENTIFIER parse_type_template(IDENTIFIER, PPTOKEN *, int);
extern TYPE parse_typedef_templ(IDENTIFIER, PPTOKEN *);
extern TYPE deduce_type_template(IDENTIFIER, int);
extern IDENTIFIER apply_template(IDENTIFIER, LIST(TOKEN), int, int);
extern TYPE check_typename(NAMESPACE, IDENTIFIER, BASE_TYPE);
extern TYPE make_typename(NAMESPACE, IDENTIFIER);
extern TYPE find_typename(IDENTIFIER, LIST(TOKEN), BASE_TYPE, int);

extern int depends_on(TYPE, LIST(IDENTIFIER));
extern int depends_on_exp(EXP, LIST(IDENTIFIER), int);
extern int depends_on_nat(NAT, LIST(IDENTIFIER), int);
extern int depends_on_off(OFFSET, LIST(IDENTIFIER), int);
extern int depends_on_param(IDENTIFIER, LIST(IDENTIFIER));
extern int depends_on_args(LIST(TOKEN), LIST(IDENTIFIER), int, int);
extern int dependent_call(IDENTIFIER, LIST(EXP));
extern int dependent_cast(IDENTIFIER, TYPE);
extern int dependent_conv(TYPE, LIST(EXP));
extern int dependent_id(IDENTIFIER);
extern int deduce_template(TYPE, TYPE, int);
extern int eq_templ_params(LIST(IDENTIFIER), LIST(IDENTIFIER));
extern void restore_templ_params(LIST(IDENTIFIER));
extern int eq_template(TYPE, TYPE, int, int, int);
extern TYPE injected_type(TYPE, int);
extern void mark_used(EXP);
extern LIST(IDENTIFIER) any_templ_param;
extern LIST(IDENTIFIER) any_token_param;
extern NAMESPACE templ_namespace;
extern TYPE type_templ_param;
extern int allow_templ_dargs;


#endif
