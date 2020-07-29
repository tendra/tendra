/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INSTANCE_INCLUDED
#define INSTANCE_INCLUDED


/*
    TEMPLATE INSTANTIATION ROUTINES

    The routines in this modules are concerned with template instantiation.
*/

extern IDENTIFIER deduce_func(IDENTIFIER, TYPE, int *);
extern IDENTIFIER deduce_args(IDENTIFIER, LIST(EXP), int, int, int, ERROR *);
extern IDENTIFIER instance_func(IDENTIFIER, LIST(TOKEN), int, int);
extern IDENTIFIER instance_type(IDENTIFIER, LIST(TOKEN), int, int);
extern DECL_SPEC define_templ_member(IDENTIFIER, IDENTIFIER, TYPE, EXP);
extern TYPE bind_specialise(IDENTIFIER *, TYPE, DECL_SPEC, int, int, int);
extern TYPE find_form(IDENTIFIER, int *);
extern void templ_func_decl(IDENTIFIER);
extern TYPE deduce_conv(TYPE, TYPE);
extern int bound_specialise;

extern int compare_specs(IDENTIFIER, IDENTIFIER);
extern void complete_class(CLASS_TYPE, int);
extern void define_template(IDENTIFIER, int);
extern void clear_templates(int);
extern LIST(IDENTIFIER) still_pending_templates;
extern LIST(IDENTIFIER) pending_templates;
extern INSTANCE all_instances;


#endif
