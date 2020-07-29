/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef REDECLARE_INCLUDED
#define REDECLARE_INCLUDED


/*
    REDECLARATION ROUTINE DECLARATIONS

    The routines in this module are concerned with processing redeclarations.
*/

extern IDENTIFIER find_previous(TYPE, IDENTIFIER);
extern IDENTIFIER unify_previous(IDENTIFIER, TYPE, IDENTIFIER, int);
extern IDENTIFIER unify_subsequent(IDENTIFIER, TYPE, int);
extern IDENTIFIER unify_extern(IDENTIFIER, TYPE, NAMESPACE, LIST(IDENTIFIER));
extern IDENTIFIER hide_functions(IDENTIFIER, IDENTIFIER, int);
extern IDENTIFIER redecl_id(DECL_SPEC, TYPE, IDENTIFIER, int, int);
extern IDENTIFIER redecl_func(DECL_SPEC, TYPE, IDENTIFIER, unsigned,
			      IDENTIFIER *, int);
extern IDENTIFIER redecl_inherit(IDENTIFIER, QUALIFIER, int, int);
extern IDENTIFIER alias_id(IDENTIFIER, NAMESPACE, IDENTIFIER, int);
extern int redecl_anon_union(CLASS_TYPE, DECL_SPEC, IDENTIFIER);
extern IDENTIFIER redeclare_id(NAMESPACE, IDENTIFIER);
extern int is_anon_member(IDENTIFIER);
extern void using_typename(TYPE);
extern IDENTIFIER using_identifier(IDENTIFIER);
extern IDENTIFIER copy_id(IDENTIFIER, int);
extern int is_tagged_type(IDENTIFIER);
extern DECL_SPEC adjust_linkage(DECL_SPEC, int);
extern DECL_SPEC find_linkage(EXP);
extern string linkage_string(DECL_SPEC, CV_SPEC);
extern void c_linkage(IDENTIFIER, int);
extern DECL_SPEC new_linkage;
extern DECL_SPEC crt_linkage;


#endif
