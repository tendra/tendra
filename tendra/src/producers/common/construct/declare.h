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


#ifndef DECLARE_INCLUDED
#define DECLARE_INCLUDED


/*
    DECLARATION ROUTINE DECLARATIONS

    The routines in this module are concerned with processing declarations.
*/

extern IDENTIFIER make_object_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern IDENTIFIER make_func_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern IDENTIFIER make_param_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern IDENTIFIER weak_param_decl PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER make_member_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern IDENTIFIER make_func_mem_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern IDENTIFIER make_friend_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int, int ) ) ;

extern void check_obj_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern void check_par_decl PROTO_S ( ( TYPE, IDENTIFIER, int ) ) ;
extern void check_mem_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER ) ) ;
extern void special_func_mem PROTO_S ( ( CLASS_TYPE, IDENTIFIER, unsigned, IDENTIFIER ) ) ;
extern DECL_SPEC complete_dspec PROTO_S ( ( DECL_SPEC, BASE_TYPE, TYPE, CV_SPEC ) ) ;
extern void check_decl_nspace PROTO_S ( ( IDENTIFIER, NAMESPACE, int, NAMESPACE ) ) ;
extern IDENTIFIER empty_decl PROTO_S ( ( DECL_SPEC, TYPE, BASE_TYPE, TYPE, CV_SPEC, int, int ) ) ;
extern void typedef_special PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern void external_declaration PROTO_S ( ( EXP, int ) ) ;

extern DECL_SPEC inline_linkage ;
extern DECL_SPEC const_linkage ;
extern CV_SPEC cv_extern ;
extern int is_redeclared ;
extern LOCATION decl_loc ;


#endif
