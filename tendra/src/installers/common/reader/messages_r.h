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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: messages_r.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/12/04  19:49:55  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.3  1997/10/23  09:29:40  pwe
 * ANDF-DE v1.7
 *
 * Revision 1.2  1997/08/23  13:30:44  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef mess_r_key
#define mess_r_key 1



#define READ_PAST_END "read past end of encoding"
#define CANT_OPEN_FILE "can't open file"
#define ILLEGAL_CODE_al_tag "illegal code for al_tag"
#define ILLEGAL_CODE_access "illegal code for access"
#define ILLEGAL_CODE_al_tagdef "illegal code for al_tagdef"
#define ILLEGAL_CODE_alignment "illegal code for alignment"
#define ILLEGAL_CODE_bitfield_variety "illegal code for bitfield variety"
#define ILLEGAL_CODE_bool "illegal_code for bool"
#define ILLEGAL_CODE_error_treatment "illegal code for error treatment"
#define ILLEGAL_CODE_exp "illegal code for exp"
#define ILLEGAL_CODE_external "illegal code for external"
#define ILLEGAL_CODE_floating_variety "illegal code for floating variety"
#define ILLEGAL_CODE_label "illegal code for label"
#define ILLEGAL_CODE_nat "illegal code for nat"
#define ILLEGAL_CODE_ntest "illegal code for ntest"
#define ILLEGAL_CODE_rounding_mode "illegal code for rounding mode"
#define ILLEGAL_CODE_nat "illegal code for nat"
#define ILLEGAL_CODE_ntest "illegal code for ntest"
#define ILLEGAL_CODE_rounding_mode "illegal code for rounding mode"
#define ILLEGAL_CODE_shape "illegal code for shape"
#define ILLEGAL_CODE_signed_nat "illegal code for signed nat"
#define ILLEGAL_CODE_sortname "illegal code for sortname"
#define ILLEGAL_CODE_tag "illegal code for tag"
#define ILLEGAL_CODE_tagdec "illegal code for tagdec"
#define ILLEGAL_CODE_tagdef "illegal code for tagdef"
#define ILLEGAL_CODE_tokdec "illegal code for tokdec"
#define ILLEGAL_CODE_tokdef "illegal code for tokdef"
#define ILLEGAL_CODE_token "illegal code for token"
#define ILLEGAL_CODE_transfer_mode "illegal code for transfer_mode"
#define ILLEGAL_CODE_variety "illegal code for variety"
#define ILLEGAL_CODE_version "illegal code for version"
#define MULTIPLE_DEFS "multiple incompatible definitions"
#define CONTROL_EXP "illegal control expression"
#define VARIABLE_TYPE "illegal variable type"
#define LINK_TYPE "illegal link type"
#define DIV0_SHAPE "check_shape: div0"
#define UNDEFINED_TOK "use of undefined token - fatal error"
#define RECURSIVE_TOK "recursive use of token - fatal error"
#define NO_MEMORY "not enough memory to install"
#define SORT_NAME "illegal sort name"
#define NOT_COMMON_DEC "multiple declaration, but not common"
#define NOT_COMMON_DEF "multiple definition, but not common"
#define ILLEGAL_CODE_diag_descriptor "illegal code for diag_descriptor"
#define ILLEGAL_CODE_diag_type "illegal code for diag_type"
#define ILLEGAL_CODE_diag_tagdef "illegal code for diag_tagdef"
#define ILLEGAL_CODE_diag_tq "illegal code for diag_tq"
#define ILLEGAL_CODE_filename "illegal code for filename"
#define ILLEGAL_CODE_sourcemark "illegal code for sourcemark"
#define ILLEGAL_CODE_diag_tag "illegal code for diag_tag"
#define ILLEGAL_CODE_linkinfo "illegal code for linkinfo"
#define NO_BIG_STRINGS "no strings of more than 64 bits"
#define ILLEGAL_CODE_callees "illegal code for callees"
#define ILLEGAL_CODE_error_code "illegal code for error_code"
#define ILLEGAL_CODE_string "illegal code for string"
#define ILLEGAL_CODE_procprops "illegal code for procprops"
#define ILLEGAL_CODE_otagexp "illegal code for otagexp"
#define ILLEGAL_CODE_token_defn "illegal code for token_defn"

#define ILLEGAL_CODE_dg "illegal code for dg"
#define ILLEGAL_CODE_dg_accessibility "illegal code for dg_accessibility"
#define ILLEGAL_CODE_dg_actual_param "illegal code for dg_actual_param"
#define ILLEGAL_CODE_dg_append "illegal code for dg_append"
#define ILLEGAL_CODE_dg_bound "illegal code for dg_bound"
#define ILLEGAL_CODE_dg_class_base "illegal code for dg_class_base"
#define ILLEGAL_CODE_dg_classmem "illegal code for dg_classmem"
#define ILLEGAL_CODE_dg_compilation "illegal code for dg_compilation"
#define ILLEGAL_CODE_dg_constraint "illegal code for dg_constraint"
#define ILLEGAL_CODE_dg_default "illegal code for dg_default"
#define ILLEGAL_CODE_dg_dim "illegal code for dg_dim"
#define ILLEGAL_CODE_dg_discrim "illegal code for dg_discrim"
#define ILLEGAL_CODE_dg_enum "illegal code for dg_enum"
#define ILLEGAL_CODE_dg_filename "illegal code for dg_filename"
#define ILLEGAL_CODE_dg_idname "illegal code for dg_idname"
#define ILLEGAL_CODE_dg_macro "illegal code for dg_macro"
#define ILLEGAL_CODE_dg_name "illegal code for dg_name"
#define ILLEGAL_CODE_dg_namelist "illegal code for dg_namelist"
#define ILLEGAL_CODE_dg_param "illegal code for dg_param"
#define ILLEGAL_CODE_dg_param_mode "illegal code for dg_param_mode"
#define ILLEGAL_CODE_dg_qualifier "illegal code for dg_qualifier"
#define ILLEGAL_CODE_dg_sourcepos "illegal code for dg_sourcepos"
#define ILLEGAL_CODE_dg_tag "illegal code for dg_tag"
#define ILLEGAL_CODE_dg_type "illegal code for dg_type"
#define ILLEGAL_CODE_dg_variant "illegal code for dg_variant"
#define ILLEGAL_CODE_dg_varpart "illegal code for dg_varpart"
#define ILLEGAL_CODE_dg_virtuality "illegal code for dg_virtuality"

#endif
