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


#ifndef DERIVE_INCLUDED
#define DERIVE_INCLUDED


/*
    DERIVED CLASS TYPE DECLARATIONS

    The routines in this module are concerned with the construction of
    derived and base classes.
*/

extern void add_base_class PROTO_S ( ( IDENTIFIER, DECL_SPEC, int ) ) ;
extern void end_base_class PROTO_S ( ( CLASS_TYPE, int ) ) ;
extern GRAPH expand_graph PROTO_S ( ( GRAPH, int ) ) ;
extern GRAPH uniq_base_class PROTO_S ( ( CLASS_TYPE, ERROR * ) ) ;
extern GRAPH find_base_class PROTO_S ( ( CLASS_TYPE, CLASS_TYPE, int ) ) ;
extern CLASS_TYPE compare_base_class PROTO_S ( ( CLASS_TYPE, CLASS_TYPE, int ) ) ;
extern GRAPH direct_base_class PROTO_S ( ( CLASS_TYPE, CLASS_TYPE, ERROR * ) ) ;
extern GRAPH find_ambig_base PROTO_S ( ( GRAPH ) ) ;
extern ERROR check_ambig_base PROTO_S ( ( GRAPH ) ) ;
extern ERROR check_virt_base PROTO_S ( ( GRAPH ) ) ;
extern GRAPH find_subgraph PROTO_S ( ( GRAPH, GRAPH, GRAPH ) ) ;
extern int is_subgraph PROTO_S ( ( GRAPH, GRAPH ) ) ;
extern int eq_graph PROTO_S ( ( GRAPH, GRAPH ) ) ;
extern GRAPH min_base_class PROTO_S ( ( GRAPH ) ) ;

extern IDENTIFIER search_field PROTO_S ( ( NAMESPACE, HASHID, int, int ) ) ;
extern IDENTIFIER search_base_field PROTO_S ( ( NAMESPACE, HASHID, int, int ) ) ;
extern IDENTIFIER search_subfield PROTO_S ( ( NAMESPACE, GRAPH, IDENTIFIER ) ) ;
extern GRAPH is_subfield PROTO_S ( ( NAMESPACE, IDENTIFIER ) ) ;
extern void inherit_class PROTO_S ( ( void ) ) ;


#endif
