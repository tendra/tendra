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


#ifndef IDENTIFIER_INCLUDED
#define IDENTIFIER_INCLUDED


/*
    IDENTIFIER DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of identifiers.
*/

extern void use_id PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void use_func_id PROTO_S ( ( IDENTIFIER, int, int ) ) ;
extern void reuse_id PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void define_id PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER chase_alias PROTO_S ( ( IDENTIFIER ) ) ;
extern EXP make_id_exp PROTO_S ( ( IDENTIFIER ) ) ;
extern EXP implicit_id_exp PROTO_S ( ( IDENTIFIER, int ) ) ;
extern EXP make_this_exp PROTO_S ( ( void ) ) ;
extern EXP make_this_ref PROTO_S ( ( NAMESPACE * ) ) ;
extern EXP make_this_decl PROTO_S ( ( IDENTIFIER ) ) ;
extern int is_this_exp PROTO_S ( ( EXP ) ) ;
extern IDENTIFIER this_param PROTO_S ( ( IDENTIFIER, int ) ) ;
extern EXP make_ellipsis_exp PROTO_S ( ( void ) ) ;
extern void make_ellipsis_decl PROTO_S ( ( void ) ) ;
extern IDENTIFIER ellipsis_param PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER report_ambiguous PROTO_S ( ( IDENTIFIER, int, int, int ) ) ;
extern DECL_SPEC find_ambig_dspec PROTO_S ( ( LIST ( IDENTIFIER ) ) ) ;
extern ERROR check_id_name PROTO_S ( ( IDENTIFIER, int ) ) ;
extern IDENTIFIER declare_func PROTO_S ( ( DECL_SPEC, IDENTIFIER, TYPE, TYPE *, int, LIST ( TYPE ) ) ) ;
extern QUALIFIER crt_id_qualifier ;
extern int crt_templ_qualifier ;
extern int suppress_usage ;


/*
    IDENTIFIER CONTEXTS

    These values are used to indicate the contexts for an identifier
    to check_id_name.
*/

#define CONTEXT_OBJECT			0
#define CONTEXT_FUNCTION		1
#define CONTEXT_PARAMETER		2
#define CONTEXT_MEMBER			3
#define CONTEXT_FUNC_MEMBER		4
#define CONTEXT_CLASS			5
#define CONTEXT_ENUM			6
#define CONTEXT_ENUMERATOR		7
#define CONTEXT_TEMPL_PARAM		8
#define CONTEXT_WEAK_PARAM		9


#endif
