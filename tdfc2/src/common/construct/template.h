/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TEMPLATE_INCLUDED
#define TEMPLATE_INCLUDED


/*
    TEMPLATE DECLARATIONS

    The routines in this module are concerned with the declaration of
    templates.
*/

extern void init_templates(void);
extern TOKEN template_params(int);
extern TYPE make_template_type(TOKEN, TYPE);
extern void end_template(TOKEN);
extern void template_decl(TYPE);
extern TYPE check_templ_params(TYPE, IDENTIFIER);
extern int check_templ_dargs(TYPE);
extern void check_deduced_args(IDENTIFIER, LIST(IDENTIFIER), LIST(TOKEN));
extern void redecl_template(TYPE *, TYPE *, IDENTIFIER);
extern void reset_primary_templ(TYPE, TYPE);
extern LIST(TOKEN) make_primary_args(LIST(IDENTIFIER));
extern void export_template(IDENTIFIER, int);
extern int is_exported(IDENTIFIER);

extern IDENTIFIER make_type_param(IDENTIFIER);
extern IDENTIFIER make_exp_param(TYPE, IDENTIFIER);
extern IDENTIFIER make_template_param(TYPE, IDENTIFIER);
extern void init_type_param(IDENTIFIER, TYPE);
extern void init_exp_param(IDENTIFIER, EXP);
extern void init_template_param(IDENTIFIER, IDENTIFIER);
extern IDENTIFIER find_template(IDENTIFIER, int);
extern int is_templ_decl(IDENTIFIER, TYPE);
extern int is_templ_param(IDENTIFIER);
extern int is_templ_alias(IDENTIFIER);
extern int is_templ_type(TYPE);
extern int is_templ_spec(TYPE);
extern int is_templ_depend(TYPE);
extern int is_templ_nspace(NAMESPACE);

extern PPTOKEN *skip_template_args(IDENTIFIER, int);
extern IDENTIFIER parse_id_template(IDENTIFIER, PPTOKEN *, int);
extern IDENTIFIER parse_type_template(IDENTIFIER, PPTOKEN *, int);
extern TYPE parse_typedef_templ(IDENTIFIER, PPTOKEN *);
extern TYPE deduce_type_template(IDENTIFIER, int);
extern IDENTIFIER apply_template(IDENTIFIER, LIST(TOKEN), int, int);
extern TYPE check_typename(NAMESPACE, IDENTIFIER, BASE_TYPE);
extern TYPE make_typename(NAMESPACE, IDENTIFIER);
extern TYPE find_typename(IDENTIFIER, LIST(TOKEN), BASE_TYPE, int);

extern int depends_on(TYPE, LIST(IDENTIFIER));
extern int depends_on_exp(EXP, LIST(IDENTIFIER), int);
extern int depends_on_nat(NAT, LIST(IDENTIFIER), int);
extern int depends_on_off(OFFSET, LIST(IDENTIFIER), int);
extern int depends_on_param(IDENTIFIER, LIST(IDENTIFIER));
extern int depends_on_args(LIST(TOKEN), LIST(IDENTIFIER), int, int);
extern int dependent_call(IDENTIFIER, LIST(EXP));
extern int dependent_cast(IDENTIFIER, TYPE);
extern int dependent_conv(TYPE, LIST(EXP));
extern int dependent_id(IDENTIFIER);
extern int deduce_template(TYPE, TYPE, int);
extern int eq_templ_params(LIST(IDENTIFIER), LIST(IDENTIFIER));
extern void restore_templ_params(LIST(IDENTIFIER));
extern int eq_template(TYPE, TYPE, int, int, int);
extern TYPE injected_type(TYPE, int);
extern void mark_used(EXP);
extern LIST(IDENTIFIER) any_templ_param;
extern LIST(IDENTIFIER) any_token_param;
extern NAMESPACE templ_namespace;
extern TYPE type_templ_param;
extern int allow_templ_dargs;


#endif
