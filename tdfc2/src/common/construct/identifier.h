/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef IDENTIFIER_INCLUDED
#define IDENTIFIER_INCLUDED


/*
    IDENTIFIER DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of identifiers.
*/

extern void use_id(IDENTIFIER, int);
extern void use_func_id(IDENTIFIER, int, int);
extern void reuse_id(IDENTIFIER, int);
extern void define_id(IDENTIFIER);
extern IDENTIFIER chase_alias(IDENTIFIER);
extern EXP make_id_exp(IDENTIFIER);
extern EXP implicit_id_exp(IDENTIFIER, int);
extern EXP make_this_exp(void);
extern EXP make_this_ref(NAMESPACE *);
extern EXP make_this_decl(IDENTIFIER);
extern int is_this_exp(EXP);
extern IDENTIFIER this_param(IDENTIFIER, int);
extern EXP make_ellipsis_exp(void);
extern void make_ellipsis_decl(void);
extern IDENTIFIER ellipsis_param(IDENTIFIER);
extern IDENTIFIER report_ambiguous(IDENTIFIER, int, int, int);
extern DECL_SPEC find_ambig_dspec(LIST(IDENTIFIER));
extern ERROR check_id_name(IDENTIFIER, int);
extern IDENTIFIER declare_func(DECL_SPEC, IDENTIFIER, TYPE, TYPE *, int,
			       LIST(TYPE));
extern QUALIFIER crt_id_qualifier;
extern int crt_templ_qualifier;
extern int suppress_usage;


/*
    IDENTIFIER CONTEXTS

    These values are used to indicate the contexts for an identifier
    to check_id_name.
*/

enum {
	CONTEXT_OBJECT,
	CONTEXT_FUNCTION,
	CONTEXT_PARAMETER,
	CONTEXT_MEMBER,
	CONTEXT_FUNC_MEMBER,
	CONTEXT_CLASS,
	CONTEXT_ENUM,
	CONTEXT_ENUMERATOR,
	CONTEXT_TEMPL_PARAM,
	CONTEXT_WEAK_PARAM
};


#endif
