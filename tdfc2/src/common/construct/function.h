/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FUNCTION_INCLUDED
#define FUNCTION_INCLUDED


/*
    FUNCTION DECLARATIONS

    The routines in this module are concerned with the construction and
    application of functions.
*/

extern void begin_function(IDENTIFIER);
extern EXP end_function(IDENTIFIER, EXP);
extern void begin_param(IDENTIFIER);
extern void end_param(void);
extern void adjust_param(TYPE);
extern int function_params(TYPE);
extern TYPE make_param_type(TYPE, int);
extern TYPE make_func_type(TYPE, int, CV_SPEC, LIST(TYPE));
extern CV_SPEC func_linkage(CV_SPEC);
extern void member_func_type(CLASS_TYPE, unsigned, TYPE);
extern void check_weak_func(TYPE, int);
extern void decl_func_type(IDENTIFIER, TYPE, int);
extern TYPE find_func_type(TYPE);
extern TYPE redecl_func_type(IDENTIFIER, TYPE, TYPE, int, int);
extern EXP apply_func_id(IDENTIFIER, QUALIFIER, GRAPH, LIST(EXP));
extern LIST(EXP) convert_args(LIST(EXP));
extern EXP make_func_exp(EXP, LIST(EXP), int);
extern EXP check_inline(IDENTIFIER, LIST(EXP), TYPE);
extern TYPE check_main(TYPE, HASHID);
extern void recheck_main(IDENTIFIER);
extern int pass_complex_type(TYPE);
extern unsigned min_no_args(TYPE);
extern void func_type_defn(int);
extern ERROR check_param_type(IDENTIFIER, TYPE);
extern TYPE check_ret_type(TYPE, ERROR *, int);
extern int check_func_dargs(TYPE, int, int);
extern void object_type(TYPE, unsigned);


/*
    FUNCTION VARIABLES

    These variables are used to store information about the current
    function definition.
*/

extern IDENTIFIER crt_func_id;
extern TYPE crt_func_return;
extern int crt_func_complex;
extern IDENTIFIER main_function;


/*
    FUNCTION TYPES

    The various kinds of functions are given by combinations of the
    following values, which are stored in the ellipsis field of the
    corresponding function type.  In C++ the only possibilities are
    FUNC_NONE and FUNC_ELLIPSIS indicating whether or not the function
    is declared with ellipsis; the fact that these have the values 0 and
    1 is used.  In C non-prototype functions introduce other kinds of
    function:

	FUNC_NO_PARAMS		no type information,
	FUNC_WEAK_PARAMS	weak prototype or non-prototype definition,
	FUNC_WEAK_ARGS		implicit weak prototype.

    During type construction the following values are used:

	FUNC_NO_PARAMS		no type information,
	FUNC_PARAMS		non-prototype definition,
	FUNC_WEAK		weak prototype.
*/

enum {
	FUNC_NONE        = 0,
	FUNC_ELLIPSIS    = 1,
	FUNC_WEAK        = 2,
	FUNC_PARAMS      = 4,
	FUNC_NO_PARAMS   = 8,
	FUNC_WEAK_PARAMS = (FUNC_WEAK | FUNC_PARAMS),
	FUNC_WEAK_ARGS   = (FUNC_WEAK),
	FUNC_VAR_PARAMS  = (FUNC_ELLIPSIS | FUNC_NO_PARAMS),
	FUNC_NON_PROTO   = (FUNC_WEAK | FUNC_PARAMS | FUNC_NO_PARAMS)
};


#endif
