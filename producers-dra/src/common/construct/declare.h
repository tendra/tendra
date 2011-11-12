/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DECLARE_INCLUDED
#define DECLARE_INCLUDED


/*
    DECLARATION ROUTINE DECLARATIONS

    The routines in this module are concerned with processing declarations.
*/

extern IDENTIFIER make_object_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern IDENTIFIER make_func_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern IDENTIFIER make_param_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern IDENTIFIER weak_param_decl(IDENTIFIER);
extern IDENTIFIER make_member_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern IDENTIFIER make_func_mem_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern IDENTIFIER make_friend_decl(DECL_SPEC, TYPE, IDENTIFIER, int, int);

extern void check_obj_decl(DECL_SPEC, TYPE, IDENTIFIER, int);
extern void check_par_decl(TYPE, IDENTIFIER, int);
extern void check_mem_decl(DECL_SPEC, TYPE, IDENTIFIER);
extern void special_func_mem(CLASS_TYPE, IDENTIFIER, unsigned, IDENTIFIER);
extern DECL_SPEC complete_dspec(DECL_SPEC, BASE_TYPE, TYPE, CV_SPEC);
extern void check_decl_nspace(IDENTIFIER, NAMESPACE, int, NAMESPACE);
extern IDENTIFIER empty_decl(DECL_SPEC, TYPE, BASE_TYPE, TYPE, CV_SPEC, int,
			     int);
extern void typedef_special(IDENTIFIER, TYPE);
extern void external_declaration(EXP, int);

extern DECL_SPEC inline_linkage;
extern DECL_SPEC const_linkage;
extern CV_SPEC cv_extern;
extern int is_redeclared;
extern LOCATION decl_loc;


#endif
