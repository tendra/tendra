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


#ifndef REDECLARE_INCLUDED
#define REDECLARE_INCLUDED


/*
    REDECLARATION ROUTINE DECLARATIONS

    The routines in this module are concerned with processing redeclarations.
*/

extern IDENTIFIER find_previous PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern IDENTIFIER unify_previous PROTO_S ( ( IDENTIFIER, TYPE, IDENTIFIER, int ) ) ;
extern IDENTIFIER unify_subsequent PROTO_S ( ( IDENTIFIER, TYPE, int ) ) ;
extern IDENTIFIER unify_extern PROTO_S ( ( IDENTIFIER, TYPE, NAMESPACE, LIST ( IDENTIFIER ) ) ) ;
extern IDENTIFIER hide_functions PROTO_S ( ( IDENTIFIER, IDENTIFIER, int ) ) ;
extern IDENTIFIER redecl_id PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int, int ) ) ;
extern IDENTIFIER redecl_func PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, unsigned, IDENTIFIER *, int ) ) ;
extern IDENTIFIER redecl_inherit PROTO_S ( ( IDENTIFIER, QUALIFIER, int, int ) ) ;
extern IDENTIFIER alias_id PROTO_S ( ( IDENTIFIER, NAMESPACE, IDENTIFIER, int ) ) ;
extern int redecl_anon_union PROTO_S ( ( CLASS_TYPE, DECL_SPEC, IDENTIFIER ) ) ;
extern IDENTIFIER redeclare_id PROTO_S ( ( NAMESPACE, IDENTIFIER ) ) ;
extern int is_anon_member PROTO_S ( ( IDENTIFIER ) ) ;
extern void using_typename PROTO_S ( ( TYPE ) ) ;
extern IDENTIFIER using_identifier PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER copy_id PROTO_S ( ( IDENTIFIER, int ) ) ;
extern int is_tagged_type PROTO_S ( ( IDENTIFIER ) ) ;
extern DECL_SPEC adjust_linkage PROTO_S ( ( DECL_SPEC, int ) ) ;
extern DECL_SPEC find_linkage PROTO_S ( ( EXP ) ) ;
extern string linkage_string PROTO_S ( ( DECL_SPEC, CV_SPEC ) ) ;
extern void c_linkage PROTO_S ( ( IDENTIFIER, int ) ) ;
extern DECL_SPEC new_linkage ;
extern DECL_SPEC crt_linkage ;


#endif
