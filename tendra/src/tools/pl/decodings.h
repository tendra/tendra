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

extern unsigned int d_access PROTO_S ( ( int ) ) ;
extern unsigned int d_access_option PROTO_S ( ( int ) ) ;
extern unsigned int d_al_tag PROTO_S ( ( int ) ) ;
extern unsigned int d_al_tagdef PROTO_S ( ( int ) ) ;
extern unsigned int d_al_tagdef_list PROTO_S ( ( int ) ) ;
extern unsigned int d_al_tagdef_props PROTO_S ( ( int ) ) ;
extern unsigned int d_alignment PROTO_S ( ( int ) ) ;
extern unsigned int d_bitfield_variety PROTO_S ( ( int ) ) ;
extern unsigned int d_bool PROTO_S ( ( int ) ) ;
extern unsigned int d_callees PROTO_S ( ( int ) ) ;
extern unsigned int d_capsule PROTO_S ( ( int ) ) ;
extern unsigned int d_capsule_link PROTO_S ( ( int ) ) ;
extern unsigned int d_capsule_link_list PROTO_S ( ( int ) ) ;
extern unsigned int d_caselim PROTO_S ( ( int ) ) ;
extern unsigned int d_caselim_list PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_descriptor PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_descriptor_list PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_field PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_field_list PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_tag PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_tagdef PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_tagdef_list PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_tq PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_type PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_type_list PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_type_unit PROTO_S ( ( int ) ) ;
extern unsigned int d_diag_unit PROTO_S ( ( int ) ) ;
extern unsigned int d_enum_values PROTO_S ( ( int ) ) ;
extern unsigned int d_enum_values_list PROTO_S ( ( int ) ) ;
extern unsigned int d_error_code PROTO_S ( ( int ) ) ;
extern unsigned int d_error_code_list PROTO_S ( ( int ) ) ;
extern unsigned int d_error_treatment PROTO_S ( ( int ) ) ;
extern unsigned int d_exp PROTO_S ( ( int ) ) ;
extern unsigned int d_exp_list PROTO_S ( ( int ) ) ;
extern unsigned int d_exp_option PROTO_S ( ( int ) ) ;
extern unsigned int d_extern_link PROTO_S ( ( int ) ) ;
extern unsigned int d_extern_link_list PROTO_S ( ( int ) ) ;
extern unsigned int d_external PROTO_S ( ( int ) ) ;
extern unsigned int d_filename PROTO_S ( ( int ) ) ;
extern unsigned int d_floating_variety PROTO_S ( ( int ) ) ;
extern unsigned int d_group PROTO_S ( ( int ) ) ;
extern unsigned int d_group_list PROTO_S ( ( int ) ) ;
extern unsigned int d_label PROTO_S ( ( int ) ) ;
extern unsigned int d_label_list PROTO_S ( ( int ) ) ;
extern unsigned int d_link PROTO_S ( ( int ) ) ;
extern unsigned int d_link_list PROTO_S ( ( int ) ) ;
extern unsigned int d_linkextern PROTO_S ( ( int ) ) ;
extern unsigned int d_linkextern_list PROTO_S ( ( int ) ) ;
extern unsigned int d_linkinfo PROTO_S ( ( int ) ) ;
extern unsigned int d_linkinfo_list PROTO_S ( ( int ) ) ;
extern unsigned int d_linkinfo_props PROTO_S ( ( int ) ) ;
extern unsigned int d_links PROTO_S ( ( int ) ) ;
extern unsigned int d_links_list PROTO_S ( ( int ) ) ;
extern unsigned int d_nat PROTO_S ( ( int ) ) ;
extern unsigned int d_nat_option PROTO_S ( ( int ) ) ;
extern unsigned int d_ntest PROTO_S ( ( int ) ) ;
extern unsigned int d_otagexp PROTO_S ( ( int ) ) ;
extern unsigned int d_otagexp_list PROTO_S ( ( int ) ) ;
extern unsigned int d_procprops PROTO_S ( ( int ) ) ;
extern unsigned int d_procprops_option PROTO_S ( ( int ) ) ;
extern unsigned int d_rounding_mode PROTO_S ( ( int ) ) ;
extern unsigned int d_shape PROTO_S ( ( int ) ) ;
extern unsigned int d_signed_nat PROTO_S ( ( int ) ) ;
extern unsigned int d_sortname PROTO_S ( ( int ) ) ;
extern unsigned int d_sortname_list PROTO_S ( ( int ) ) ;
extern unsigned int d_sourcemark PROTO_S ( ( int ) ) ;
extern unsigned int d_string PROTO_S ( ( int ) ) ;
extern unsigned int d_string_option PROTO_S ( ( int ) ) ;
extern unsigned int d_tag PROTO_S ( ( int ) ) ;
extern unsigned int d_tag_option PROTO_S ( ( int ) ) ;
extern unsigned int d_tagacc PROTO_S ( ( int ) ) ;
extern unsigned int d_tagacc_option PROTO_S ( ( int ) ) ;
extern unsigned int d_tagdec PROTO_S ( ( int ) ) ;
extern unsigned int d_tagdec_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tagdec_props PROTO_S ( ( int ) ) ;
extern unsigned int d_tagdef PROTO_S ( ( int ) ) ;
extern unsigned int d_tagdef_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tagdef_props PROTO_S ( ( int ) ) ;
extern unsigned int d_tagshacc PROTO_S ( ( int ) ) ;
extern unsigned int d_tagshacc_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tdfident_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tdfint_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tokdec PROTO_S ( ( int ) ) ;
extern unsigned int d_tokdec_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tokdec_props PROTO_S ( ( int ) ) ;
extern unsigned int d_tokdef PROTO_S ( ( int ) ) ;
extern unsigned int d_tokdef_list PROTO_S ( ( int ) ) ;
extern unsigned int d_tokdef_props PROTO_S ( ( int ) ) ;
extern unsigned int d_token PROTO_S ( ( int ) ) ;
extern unsigned int d_token_defn PROTO_S ( ( int ) ) ;
extern unsigned int d_tokformals PROTO_S ( ( int ) ) ;
extern unsigned int d_tokformals_list PROTO_S ( ( int ) ) ;
extern unsigned int d_transfer_mode PROTO_S ( ( int ) ) ;
extern unsigned int d_unique PROTO_S ( ( int ) ) ;
extern unsigned int d_unit PROTO_S ( ( int ) ) ;
extern unsigned int d_unit_list PROTO_S ( ( int ) ) ;
extern unsigned int d_variety PROTO_S ( ( int ) ) ;
extern unsigned int d_version PROTO_S ( ( int ) ) ;
extern unsigned int d_version_list PROTO_S ( ( int ) ) ;
extern unsigned int d_version_props PROTO_S ( ( int ) ) ;

#endif
