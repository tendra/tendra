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


#ifndef UNIT_INCLUDED
#define UNIT_INCLUDED


/*
    TOKEN/TAG DECLARATIONS/DEFINITIONS

    This file contains the routines for decoding token declarations, token
    definitions, tag declarations, tag definitions and the standard unit
    types associated with them.
*/

extern void token_sort PROTO_S ( ( object *, sortname, char *, long ) ) ;
extern void read_no_labs PROTO_S ( ( void ) ) ;
extern void de_tagdec_props PROTO_S ( ( void ) ) ;
extern void de_tagdef_props PROTO_S ( ( void ) ) ;
extern void de_tokdec_props PROTO_S ( ( void ) ) ;
extern void de_tokdef_props PROTO_S ( ( void ) ) ;
extern void de_al_tagdef_props PROTO_S ( ( void ) ) ;
extern void de_dg_comp_props PROTO_S ( ( void ) ) ;
extern void de_diag_type_unit PROTO_S ( ( void ) ) ;
extern void de_diag_unit PROTO_S ( ( void ) ) ;
extern void de_linkinfo_props PROTO_S ( ( void ) ) ;
extern void de_version_props PROTO_S ( ( void ) ) ;
extern void de_tld2_unit PROTO_S ( ( void ) ) ;
extern void de_tld_unit PROTO_S ( ( void ) ) ;
extern void de_make_version PROTO_S ( ( char * ) ) ;
extern void de_magic PROTO_S ( ( char * ) ) ;
extern long max_lab_no ;
extern int show_usage ;
extern int diagnostics ;
extern int versions ;


/*
    UNIT USAGE INFORMATION

    These macros describe the units decoded by the routines above and
    give the flags which control their use.
*/

#define MSG_tagdec_props		"TAG DECLARATIONS"
#define MSG_tagdef_props		"TAG DEFINITIONS"
#define MSG_tokdec_props		"TOKEN DECLARATIONS"
#define MSG_tokdef_props		"TOKEN DEFINITIONS"
#define MSG_al_tagdef_props		"ALIGNMENT TAG DEFINITIONS"
#define MSG_dg_comp_props		"DIAGNOSTIC INFORMATION"
#define MSG_diag_type_unit		"DIAGNOSTIC TYPE INFORMATION"
#define MSG_diag_unit			"DIAGNOSTIC INFORMATION"
#define MSG_linkinfo_props		"LINKING INFORMATION"
#define MSG_version_props		"TDF VERSION NUMBER"
#define MSG_tld2_unit			"LINKER INFORMATION"
#define MSG_tld_unit			"LINKER INFORMATION"

#define OPT_tagdec_props		1
#define OPT_tagdef_props		1
#define OPT_tokdec_props		1
#define OPT_tokdef_props		1
#define OPT_al_tagdef_props		1
#define OPT_dg_comp_props		diagnostics
#define OPT_diag_type_unit		diagnostics
#define OPT_diag_unit			diagnostics
#define OPT_linkinfo_props		show_usage
#define OPT_version_props		versions
#define OPT_tld2_unit			show_usage
#define OPT_tld_unit			show_usage


#endif
