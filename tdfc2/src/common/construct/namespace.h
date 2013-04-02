/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef NAMESPACE_INCLUDED
#define NAMESPACE_INCLUDED


/*
    NAMESPACE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of namespaces.
*/

extern void begin_declarator(IDENTIFIER, QUALIFIER, NAMESPACE, int);
extern void end_declarator(IDENTIFIER, int);
extern void begin_namespace(IDENTIFIER, int);
extern void end_namespace(int);
extern void alias_namespace(IDENTIFIER, NAMESPACE);
extern void using_namespace(NAMESPACE);
extern int use_namespace(NAMESPACE, NAMESPACE, NAMESPACE);
extern void target_decl(int, EXP);
extern void begin_decl_block(IDENTIFIER);
extern int end_decl_block(IDENTIFIER, int);
extern void clear_decl_blocks(void);
extern NAMESPACE find_namespace(IDENTIFIER);
extern NAMESPACE find_nspace_id(IDENTIFIER);
extern int has_linkage(IDENTIFIER);

extern NAMESPACE make_namespace(IDENTIFIER, unsigned, int);
extern NAMESPACE make_global_nspace(const char *, int);
extern void uncache_namespace(NAMESPACE, int);
extern void add_namespace(NAMESPACE);
extern void remove_namespace(void);
extern void push_namespace(NAMESPACE);
extern void store_namespace(NAMESPACE);
extern NAMESPACE pop_namespace(void);
extern NAMESPACE restore_namespace(void);
extern int add_nested_nspace(NAMESPACE);
extern int remove_nested_nspace(NAMESPACE);
extern int is_subnspace(NAMESPACE, NAMESPACE);
extern void update_namespace(void);
extern void check_hiding(IDENTIFIER);
extern void init_namespace(void);

extern MEMBER search_member(NAMESPACE, HASHID, int);
extern IDENTIFIER search_id(NAMESPACE, HASHID, int, int);
extern IDENTIFIER find_id(HASHID);
extern IDENTIFIER find_type_id(HASHID, int);
extern IDENTIFIER find_qual_id(NAMESPACE, HASHID, int, int);
extern IDENTIFIER find_extern_id(HASHID, NAMESPACE, int);
extern IDENTIFIER check_id(NAMESPACE, IDENTIFIER, int);
extern IDENTIFIER type_member(MEMBER, int);
extern MEMBER update_member(NAMESPACE, MEMBER);
extern void set_type_member(MEMBER, IDENTIFIER);
extern void set_member(MEMBER, IDENTIFIER);
extern void clear_member(NAMESPACE, HASHID);
extern IDENTIFIER find_op_id(HASHID);
extern void remove_id(IDENTIFIER);

extern STACK(NAMESPACE) local_nspace_stack;
extern STACK(NAMESPACE) crt_nspace_stack;
extern STACK(NAMESPACE) namespace_stack;
extern NAMESPACE nonblock_namespace;
extern NAMESPACE nonclass_namespace;
extern NAMESPACE global_namespace;
extern NAMESPACE token_namespace;
extern NAMESPACE last_namespace;
extern NAMESPACE qual_namespace;
extern NAMESPACE crt_namespace;
extern NAMESPACE c_namespace;
extern int old_cache_lookup;
extern int cache_lookup;


#endif
