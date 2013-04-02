/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONSTRUCT_INCLUDED
#define CONSTRUCT_INCLUDED


/*
    CONSTRUCTOR AND DESTRUCTOR FUNCTION DECLARATIONS

    The routines in this module are concerned with constructors, destructors
    and conversion functions.
*/

extern NAMESPACE ctor_begin(void);
extern EXP ctor_end(NAMESPACE, EXP, int);
extern void ctor_initialise(NAMESPACE, IDENTIFIER, EXP);
extern EXP ctor_none(EXP, EXP *);
extern EXP ctor_postlude(EXP, EXP);
extern EXP copy_ctor(EXP, int);
extern EXP except_postlude(IDENTIFIER);

extern TYPE check_constr(TYPE, IDENTIFIER, NAMESPACE);
extern TYPE check_destr(TYPE, IDENTIFIER, NAMESPACE);
extern TYPE check_conv(TYPE, IDENTIFIER);
extern TYPE inferred_return(TYPE, IDENTIFIER);

extern IDENTIFIER find_operator(CLASS_TYPE, int);
extern IDENTIFIER make_pseudo_destr(IDENTIFIER, BASE_TYPE, IDENTIFIER,
				    BASE_TYPE);
extern CLASS_INFO implicit_decl(CLASS_TYPE, CLASS_INFO, DECL_SPEC);
extern void implicit_defn(IDENTIFIER, int);

extern EXP init_default(TYPE, EXP *, int, int, ERROR *);
extern EXP convert_constr(TYPE, LIST(EXP), ERROR *, unsigned);
extern EXP convert_conv_aux(TYPE, EXP, ERROR *, unsigned);
extern EXP convert_conv(TYPE, EXP, ERROR *, unsigned);
extern EXP convert_gen(unsigned, EXP, ERROR *);
extern EXP apply_constr(IDENTIFIER, LIST(EXP));
extern EXP add_constr_args(EXP, CLASS_TYPE, int);
extern unsigned extra_constr_args(IDENTIFIER, CLASS_TYPE);
extern EXP apply_trivial_func(IDENTIFIER, LIST(EXP));
extern EXP trivial_destr(EXP);
extern int have_constr_expl;
extern int have_conv_expl;


/*
    IMPLICIT CONSTRUCTOR IDENTIFIERS

    These values are used to represent the four member functions which
    may be implicitly declared for a class - the default constructor, the
    copy constructor, the default destructor and the copy assignment
    operator.  A dummy value for explicit constructors is provided.
*/

#define DEFAULT_USR			0
#define DEFAULT_CONSTR			1
#define DEFAULT_COPY			2
#define DEFAULT_DESTR			3
#define DEFAULT_ASSIGN			4
#define DEFAULT_DELETE			5
#define DEFAULT_PRELUDE			6


/*
    EXTRA CONSTRUCT ARGUMENT VALUES

    These values represent the extra argument which are passed to
    constructors and destructors.
*/

#define EXTRA_NONE			0
#define EXTRA_CONSTR			1

#define EXTRA_DELETE			1
#define EXTRA_DESTR			2


#endif
