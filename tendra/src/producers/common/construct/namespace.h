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


#ifndef NAMESPACE_INCLUDED
#define NAMESPACE_INCLUDED


/*
    NAMESPACE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of namespaces.
*/

extern void begin_declarator PROTO_S ( ( IDENTIFIER, QUALIFIER, NAMESPACE, int ) ) ;
extern void end_declarator PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void begin_namespace PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void end_namespace PROTO_S ( ( int ) ) ;
extern void alias_namespace PROTO_S ( ( IDENTIFIER, NAMESPACE ) ) ;
extern void using_namespace PROTO_S ( ( NAMESPACE ) ) ;
extern int use_namespace PROTO_S ( ( NAMESPACE, NAMESPACE, NAMESPACE ) ) ;
extern void target_decl PROTO_S ( ( int, EXP ) ) ;
extern void begin_decl_block PROTO_S ( ( IDENTIFIER ) ) ;
extern int end_decl_block PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void clear_decl_blocks PROTO_S ( ( void ) ) ;
extern NAMESPACE find_namespace PROTO_S ( ( IDENTIFIER ) ) ;
extern NAMESPACE find_nspace_id PROTO_S ( ( IDENTIFIER ) ) ;
extern int has_linkage PROTO_S ( ( IDENTIFIER ) ) ;

extern NAMESPACE make_namespace PROTO_S ( ( IDENTIFIER, unsigned, int ) ) ;
extern NAMESPACE make_global_nspace PROTO_S ( ( CONST char *, int ) ) ;
extern void uncache_namespace PROTO_S ( ( NAMESPACE, int ) ) ;
extern void add_namespace PROTO_S ( ( NAMESPACE ) ) ;
extern void remove_namespace PROTO_S ( ( void ) ) ;
extern void push_namespace PROTO_S ( ( NAMESPACE ) ) ;
extern void store_namespace PROTO_S ( ( NAMESPACE ) ) ;
extern NAMESPACE pop_namespace PROTO_S ( ( void ) ) ;
extern NAMESPACE restore_namespace PROTO_S ( ( void ) ) ;
extern int add_nested_nspace PROTO_S ( ( NAMESPACE ) ) ;
extern int remove_nested_nspace PROTO_S ( ( NAMESPACE ) ) ;
extern int is_subnspace PROTO_S ( ( NAMESPACE, NAMESPACE ) ) ;
extern void update_namespace PROTO_S ( ( void ) ) ;
extern void check_hiding PROTO_S ( ( IDENTIFIER ) ) ;
extern void init_namespace PROTO_S ( ( void ) ) ;

extern MEMBER search_member PROTO_S ( ( NAMESPACE, HASHID, int ) ) ;
extern IDENTIFIER search_id PROTO_S ( ( NAMESPACE, HASHID, int, int ) ) ;
extern IDENTIFIER find_id PROTO_S ( ( HASHID ) ) ;
extern IDENTIFIER find_type_id PROTO_S ( ( HASHID, int ) ) ;
extern IDENTIFIER find_qual_id PROTO_S ( ( NAMESPACE, HASHID, int, int ) ) ;
extern IDENTIFIER find_extern_id PROTO_S ( ( HASHID, NAMESPACE, int ) ) ;
extern IDENTIFIER check_id PROTO_S ( ( NAMESPACE, IDENTIFIER, int ) ) ;
extern IDENTIFIER type_member PROTO_S ( ( MEMBER, int ) ) ;
extern MEMBER update_member PROTO_S ( ( NAMESPACE, MEMBER ) ) ;
extern void set_type_member PROTO_S ( ( MEMBER, IDENTIFIER ) ) ;
extern void set_member PROTO_S ( ( MEMBER, IDENTIFIER ) ) ;
extern void clear_member PROTO_S ( ( NAMESPACE, HASHID ) ) ;
extern IDENTIFIER find_op_id PROTO_S ( ( HASHID ) ) ;
extern void remove_id PROTO_S ( ( IDENTIFIER ) ) ;

extern STACK ( NAMESPACE ) local_nspace_stack ;
extern STACK ( NAMESPACE ) crt_nspace_stack ;
extern STACK ( NAMESPACE ) namespace_stack ;
extern NAMESPACE nonblock_namespace ;
extern NAMESPACE nonclass_namespace ;
extern NAMESPACE global_namespace ;
extern NAMESPACE token_namespace ;
extern NAMESPACE last_namespace ;
extern NAMESPACE qual_namespace ;
extern NAMESPACE crt_namespace ;
extern NAMESPACE c_namespace ;
extern int old_cache_lookup ;
extern int cache_lookup ;


#endif
