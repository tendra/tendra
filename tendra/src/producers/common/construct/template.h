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

extern void init_templates PROTO_S ( ( void ) ) ;
extern TOKEN template_params PROTO_S ( ( int ) ) ;
extern TYPE make_template_type PROTO_S ( ( TOKEN, TYPE ) ) ;
extern void end_template PROTO_S ( ( TOKEN ) ) ;
extern void template_decl PROTO_S ( ( TYPE ) ) ;
extern TYPE check_templ_params PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern int check_templ_dargs PROTO_S ( ( TYPE ) ) ;
extern void check_deduced_args PROTO_S ( ( IDENTIFIER, LIST ( IDENTIFIER ), LIST ( TOKEN ) ) ) ;
extern void redecl_template PROTO_S ( ( TYPE *, TYPE *, IDENTIFIER ) ) ;
extern void reset_primary_templ PROTO_S ( ( TYPE, TYPE ) ) ;
extern LIST ( TOKEN ) make_primary_args PROTO_S ( ( LIST ( IDENTIFIER ) ) ) ;
extern void export_template PROTO_S ( ( IDENTIFIER, int ) ) ;
extern int is_exported PROTO_S ( ( IDENTIFIER ) ) ;

extern IDENTIFIER make_type_param PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER make_exp_param PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern IDENTIFIER make_template_param PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern void init_type_param PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern void init_exp_param PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern void init_template_param PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern IDENTIFIER find_template PROTO_S ( ( IDENTIFIER, int ) ) ;
extern int is_templ_decl PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern int is_templ_param PROTO_S ( ( IDENTIFIER ) ) ;
extern int is_templ_alias PROTO_S ( ( IDENTIFIER ) ) ;
extern int is_templ_type PROTO_S ( ( TYPE ) ) ;
extern int is_templ_spec PROTO_S ( ( TYPE ) ) ;
extern int is_templ_depend PROTO_S ( ( TYPE ) ) ;
extern int is_templ_nspace PROTO_S ( ( NAMESPACE ) ) ;

extern PPTOKEN *skip_template_args PROTO_S ( ( IDENTIFIER, int ) ) ;
extern IDENTIFIER parse_id_template PROTO_S ( ( IDENTIFIER, PPTOKEN *, int ) ) ;
extern IDENTIFIER parse_type_template PROTO_S ( ( IDENTIFIER, PPTOKEN *, int ) ) ;
extern TYPE parse_typedef_templ PROTO_S ( ( IDENTIFIER, PPTOKEN * ) ) ;
extern TYPE deduce_type_template PROTO_S ( ( IDENTIFIER, int ) ) ;
extern IDENTIFIER apply_template PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), int, int ) ) ;
extern TYPE check_typename PROTO_S ( ( NAMESPACE, IDENTIFIER, BASE_TYPE ) ) ;
extern TYPE make_typename PROTO_S ( ( NAMESPACE, IDENTIFIER ) ) ;
extern TYPE find_typename PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), BASE_TYPE, int ) ) ;

extern int depends_on PROTO_S ( ( TYPE, LIST ( IDENTIFIER ) ) ) ;
extern int depends_on_exp PROTO_S ( ( EXP, LIST ( IDENTIFIER ), int ) ) ;
extern int depends_on_nat PROTO_S ( ( NAT, LIST ( IDENTIFIER ), int ) ) ;
extern int depends_on_off PROTO_S ( ( OFFSET, LIST ( IDENTIFIER ), int ) ) ;
extern int depends_on_param PROTO_S ( ( IDENTIFIER, LIST ( IDENTIFIER ) ) ) ;
extern int depends_on_args PROTO_S ( ( LIST ( TOKEN ), LIST ( IDENTIFIER ), int, int ) ) ;
extern int dependent_call PROTO_S ( ( IDENTIFIER, LIST ( EXP ) ) ) ;
extern int dependent_cast PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern int dependent_conv PROTO_S ( ( TYPE, LIST ( EXP ) ) ) ;
extern int dependent_id PROTO_S ( ( IDENTIFIER ) ) ;
extern int deduce_template PROTO_S ( ( TYPE, TYPE, int ) ) ;
extern int eq_templ_params PROTO_S ( ( LIST ( IDENTIFIER ), LIST ( IDENTIFIER ) ) ) ;
extern void restore_templ_params PROTO_S ( ( LIST ( IDENTIFIER ) ) ) ;
extern int eq_template PROTO_S ( ( TYPE, TYPE, int, int, int ) ) ;
extern TYPE injected_type PROTO_S ( ( TYPE, int ) ) ;
extern void mark_used PROTO_S ( ( EXP ) ) ;
extern LIST ( IDENTIFIER ) any_templ_param ;
extern LIST ( IDENTIFIER ) any_token_param ;
extern NAMESPACE templ_namespace ;
extern TYPE type_templ_param ;
extern int allow_templ_dargs ;


#endif
