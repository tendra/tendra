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


#ifndef INSTANCE_INCLUDED
#define INSTANCE_INCLUDED


/*
    TEMPLATE INSTANTIATION ROUTINES

    The routines in this modules are concerned with template instantiation.
*/

extern IDENTIFIER deduce_func PROTO_S ( ( IDENTIFIER, TYPE, int * ) ) ;
extern IDENTIFIER deduce_args PROTO_S ( ( IDENTIFIER, LIST ( EXP ), int, int, int, ERROR * ) ) ;
extern IDENTIFIER instance_func PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), int, int ) ) ;
extern IDENTIFIER instance_type PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), int, int ) ) ;
extern DECL_SPEC define_templ_member PROTO_S ( ( IDENTIFIER, IDENTIFIER, TYPE, EXP ) ) ;
extern TYPE bind_specialise PROTO_S ( ( IDENTIFIER *, TYPE, DECL_SPEC, int, int, int ) ) ;
extern TYPE find_form PROTO_S ( ( IDENTIFIER, int * ) ) ;
extern void templ_func_decl PROTO_S ( ( IDENTIFIER ) ) ;
extern TYPE deduce_conv PROTO_S ( ( TYPE, TYPE ) ) ;
extern int bound_specialise ;

extern int compare_specs PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern void complete_class PROTO_S ( ( CLASS_TYPE, int ) ) ;
extern void define_template PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void clear_templates PROTO_S ( ( int ) ) ;
extern LIST ( IDENTIFIER ) still_pending_templates ;
extern LIST ( IDENTIFIER ) pending_templates ;
extern INSTANCE all_instances ;


#endif
