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


#ifndef CLASS_INCLUDED
#define CLASS_INCLUDED


/*
    CLASS AND ENUMERATION TYPE DECLARATIONS

    The routines in this module are concerned with the construction of class
    and enumeration types.
*/

extern IDENTIFIER begin_class_defn PROTO_S ( ( IDENTIFIER, BASE_TYPE, CLASS_INFO, TYPE ) ) ;
extern IDENTIFIER end_class_defn PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER find_elaborate_type PROTO_S ( ( IDENTIFIER, BASE_TYPE, TYPE, DECL_SPEC ) ) ;
extern IDENTIFIER make_class PROTO_S ( ( NAMESPACE, HASHID, BASE_TYPE, DECL_SPEC, TYPE, TYPE ) ) ;
extern CLASS_TYPE parent_class PROTO_S ( ( IDENTIFIER ) ) ;
extern CLASS_TYPE namespace_class PROTO_S ( ( NAMESPACE ) ) ;
extern void copy_members PROTO_S ( ( CLASS_TYPE, CLASS_TYPE, CLASS_INFO, int ) ) ;
extern TYPE copy_class PROTO_S ( ( TYPE, DECL_SPEC ) ) ;
extern IDENTIFIER find_copied PROTO_S ( ( IDENTIFIER, IDENTIFIER, int ) ) ;
extern ERROR class_info PROTO_S ( ( CLASS_TYPE, CLASS_INFO, int ) ) ;
extern ERROR check_trivial_class PROTO_S ( ( CLASS_TYPE ) ) ;
extern CLASS_INFO check_member_type PROTO_S ( ( CLASS_TYPE, CLASS_INFO, TYPE, int ) ) ;
extern CLASS_INFO check_class_info PROTO_S ( ( CLASS_INFO, CLASS_INFO, int, DECL_SPEC ) ) ;
extern BASE_TYPE find_class_key PROTO_S ( ( CLASS_TYPE ) ) ;
extern int equal_key PROTO_S ( ( BASE_TYPE, BASE_TYPE ) ) ;
extern TYPE make_dummy_class PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), BASE_TYPE ) ) ;
extern int is_defined PROTO_S ( ( IDENTIFIER, TYPE *, int ) ) ;
extern int is_local_nspace PROTO_S ( ( NAMESPACE ) ) ;
extern CLASS_TYPE find_class PROTO_S ( ( IDENTIFIER ) ) ;
extern TYPE make_class_type PROTO_S ( ( CLASS_TYPE ) ) ;
extern int is_empty_class PROTO_S ( ( TYPE ) ) ;

extern IDENTIFIER begin_enum_defn PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern IDENTIFIER make_enumerator PROTO_S ( ( IDENTIFIER, IDENTIFIER, EXP ) ) ;
extern IDENTIFIER find_enumerator PROTO_S ( ( ENUM_TYPE, NAT ) ) ;
extern IDENTIFIER end_enum_defn PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER make_typedef PROTO_S ( ( NAMESPACE, HASHID, TYPE, DECL_SPEC ) ) ;
extern IDENTIFIER constr_name PROTO_S ( ( NAMESPACE, IDENTIFIER ) ) ;
extern int defining_class PROTO_S ( ( CLASS_TYPE ) ) ;
extern void push_class PROTO_S ( ( CLASS_TYPE ) ) ;
extern void pop_class PROTO_S ( ( void ) ) ;
extern int found_elaborate_type ;
extern CLASS_TYPE crt_class ;


#endif
