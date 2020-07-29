/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CLASS_INCLUDED
#define CLASS_INCLUDED


/*
    CLASS AND ENUMERATION TYPE DECLARATIONS

    The routines in this module are concerned with the construction of class
    and enumeration types.
*/

extern IDENTIFIER begin_class_defn(IDENTIFIER, BASE_TYPE, CLASS_INFO, TYPE);
extern IDENTIFIER end_class_defn(IDENTIFIER);
extern IDENTIFIER find_elaborate_type(IDENTIFIER, BASE_TYPE, TYPE, DECL_SPEC);
extern IDENTIFIER make_class(NAMESPACE, HASHID, BASE_TYPE, DECL_SPEC, TYPE,
			     TYPE);
extern CLASS_TYPE parent_class(IDENTIFIER);
extern CLASS_TYPE namespace_class(NAMESPACE);
extern void copy_members(CLASS_TYPE, CLASS_TYPE, CLASS_INFO, int);
extern TYPE copy_class(TYPE, DECL_SPEC);
extern IDENTIFIER find_copied(IDENTIFIER, IDENTIFIER, int);
extern ERROR class_info(CLASS_TYPE, CLASS_INFO, int);
extern ERROR check_trivial_class(CLASS_TYPE);
extern CLASS_INFO check_member_type(CLASS_TYPE, CLASS_INFO, TYPE, int);
extern CLASS_INFO check_class_info(CLASS_INFO, CLASS_INFO, int, DECL_SPEC);
extern BASE_TYPE find_class_key(CLASS_TYPE);
extern int equal_key(BASE_TYPE, BASE_TYPE);
extern TYPE make_dummy_class(IDENTIFIER, LIST(TOKEN), BASE_TYPE);
extern int is_defined(IDENTIFIER, TYPE *, int);
extern int is_local_nspace(NAMESPACE);
extern CLASS_TYPE find_class(IDENTIFIER);
extern TYPE make_class_type(CLASS_TYPE);
extern int is_empty_class(TYPE);

extern IDENTIFIER begin_enum_defn(IDENTIFIER, TYPE);
extern IDENTIFIER make_enumerator(IDENTIFIER, IDENTIFIER, EXP);
extern IDENTIFIER find_enumerator(ENUM_TYPE, NAT);
extern IDENTIFIER end_enum_defn(IDENTIFIER);
extern IDENTIFIER make_typedef(NAMESPACE, HASHID, TYPE, DECL_SPEC);
extern IDENTIFIER constr_name(NAMESPACE, IDENTIFIER);
extern int defining_class(CLASS_TYPE);
extern void push_class(CLASS_TYPE);
extern void pop_class(void);
extern int found_elaborate_type;
extern CLASS_TYPE crt_class;


#endif
