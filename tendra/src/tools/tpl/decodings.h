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


#ifndef DECODINGS_INCLUDED
#define DECODINGS_INCLUDED

extern unsigned int d_access(int);
extern unsigned int d_access_option(int);
extern unsigned int d_al_tag(int);
extern unsigned int d_al_tagdef(int);
extern unsigned int d_al_tagdef_list(int);
extern unsigned int d_al_tagdef_props(int);
extern unsigned int d_alignment(int);
extern unsigned int d_bitfield_variety(int);
extern unsigned int d_bool(int);
extern unsigned int d_callees(int);
extern unsigned int d_capsule(int);
extern unsigned int d_capsule_link(int);
extern unsigned int d_capsule_link_list(int);
extern unsigned int d_caselim(int);
extern unsigned int d_caselim_list(int);
extern unsigned int d_diag_descriptor(int);
extern unsigned int d_diag_descriptor_list(int);
extern unsigned int d_diag_field(int);
extern unsigned int d_diag_field_list(int);
extern unsigned int d_diag_tag(int);
extern unsigned int d_diag_tagdef(int);
extern unsigned int d_diag_tagdef_list(int);
extern unsigned int d_diag_tq(int);
extern unsigned int d_diag_type(int);
extern unsigned int d_diag_type_list(int);
extern unsigned int d_diag_type_unit(int);
extern unsigned int d_diag_unit(int);
extern unsigned int d_enum_values(int);
extern unsigned int d_enum_values_list(int);
extern unsigned int d_error_code(int);
extern unsigned int d_error_code_list(int);
extern unsigned int d_error_treatment(int);
extern unsigned int d_exp(int);
extern unsigned int d_exp_list(int);
extern unsigned int d_exp_option(int);
extern unsigned int d_extern_link(int);
extern unsigned int d_extern_link_list(int);
extern unsigned int d_external(int);
extern unsigned int d_filename(int);
extern unsigned int d_floating_variety(int);
extern unsigned int d_group(int);
extern unsigned int d_group_list(int);
extern unsigned int d_label(int);
extern unsigned int d_label_list(int);
extern unsigned int d_link(int);
extern unsigned int d_link_list(int);
extern unsigned int d_linkextern(int);
extern unsigned int d_linkextern_list(int);
extern unsigned int d_linkinfo(int);
extern unsigned int d_linkinfo_list(int);
extern unsigned int d_linkinfo_props(int);
extern unsigned int d_links(int);
extern unsigned int d_links_list(int);
extern unsigned int d_nat(int);
extern unsigned int d_nat_option(int);
extern unsigned int d_ntest(int);
extern unsigned int d_otagexp(int);
extern unsigned int d_otagexp_list(int);
extern unsigned int d_procprops(int);
extern unsigned int d_procprops_option(int);
extern unsigned int d_rounding_mode(int);
extern unsigned int d_shape(int);
extern unsigned int d_signed_nat(int);
extern unsigned int d_sortname(int);
extern unsigned int d_sortname_list(int);
extern unsigned int d_sourcemark(int);
extern unsigned int d_string(int);
extern unsigned int d_string_option(int);
extern unsigned int d_tag(int);
extern unsigned int d_tag_option(int);
extern unsigned int d_tagacc(int);
extern unsigned int d_tagacc_option(int);
extern unsigned int d_tagdec(int);
extern unsigned int d_tagdec_list(int);
extern unsigned int d_tagdec_props(int);
extern unsigned int d_tagdef(int);
extern unsigned int d_tagdef_list(int);
extern unsigned int d_tagdef_props(int);
extern unsigned int d_tagshacc(int);
extern unsigned int d_tagshacc_list(int);
extern unsigned int d_tdfident_list(int);
extern unsigned int d_tdfint_list(int);
extern unsigned int d_tokdec(int);
extern unsigned int d_tokdec_list(int);
extern unsigned int d_tokdec_props(int);
extern unsigned int d_tokdef(int);
extern unsigned int d_tokdef_list(int);
extern unsigned int d_tokdef_props(int);
extern unsigned int d_token(int);
extern unsigned int d_token_defn(int);
extern unsigned int d_tokformals(int);
extern unsigned int d_tokformals_list(int);
extern unsigned int d_transfer_mode(int);
extern unsigned int d_unique(int);
extern unsigned int d_unit(int);
extern unsigned int d_unit_list(int);
extern unsigned int d_variety(int);
extern unsigned int d_version(int);
extern unsigned int d_version_list(int);
extern unsigned int d_version_props(int);

#endif
