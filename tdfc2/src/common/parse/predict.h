/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PREDICT_INCLUDED
#define PREDICT_INCLUDED


/*
    PARSER LOOK-AHEAD DECLARATIONS

    The routines in this module are used to implement look-ahead functions
    within the parser in order to get round some of the more complex parsing
    problems (such as resolving between declarations and expressions).
*/

extern int predict_array(void);
extern int predict_class(int);
extern int predict_decl(void);
extern int predict_destr(NAMESPACE);
extern int predict_dspec(int);
extern int predict_func_defn(void);
extern int predict_init(void);
extern int predict_obj_defn(void);
extern int predict_operator(void);
extern int predict_param(void);
extern int predict_ptr(int);
extern int predict_template(void);
extern int predict_tspec(int);
extern int predict_typeid(int);
extern int predict_typename(void);


/*
    PARSER STATE VARIABLES

    These variables are used by the parser to store information about the
    current parser state.
*/

extern int have_type_specifier;
extern int have_type_declaration;
extern int have_func_declarator;
extern int in_function_defn;
extern int in_class_defn;
extern int in_declaration;
extern int in_default_arg;
extern int in_weak_param;
extern int in_ptr_mem_selector;
extern int in_token_decl;
extern int in_template_decl;
extern int really_in_function_defn;
extern int really_in_class_defn;
extern int is_function_next;
extern int is_constructor_next;

extern int no_side_effects;
extern int no_type_defns;
extern int have_destructor;
extern unsigned long no_declarations;
extern unsigned long no_token_defns;


/*
    FEATURE USE FLAGS

    These flags are set to indicate that certain features, which require
    the program to perform extra checks, have been used.
*/

extern int used_extern_volatile;
extern int used_register;


/*
    TYPE DECLARATION VALUES

    These macros give the various values assigned to have_type_declaration.
    If no types have been declared in a sequence of type specifiers it is
    TYPE_DECL_NONE, if an anonymous class is defined it is TYPE_DECL_ANON,
    if an elaborated type specifier is declared it is TYPE_DECL_ELABORATE,
    otherwise it is TYPE_DECL_NORMAL.
*/

enum {
	TYPE_DECL_NONE,
	TYPE_DECL_NORMAL,
	TYPE_DECL_ANON,
	TYPE_DECL_ELABORATE,
	TYPE_DECL_OVER_ELAB
};


#endif
