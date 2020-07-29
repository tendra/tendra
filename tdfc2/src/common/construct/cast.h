/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CAST_INCLUDED
#define CAST_INCLUDED


/*
    TYPE CAST DECLARATIONS

    The routines in this module are concerned with casting types.
*/

extern EXP make_lit_exp(EXP);

extern EXP make_cast_exp(TYPE, EXP, int);
extern EXP make_static_cast_exp(TYPE, EXP, int);
extern EXP make_reinterp_cast_exp(TYPE, EXP, int);
extern EXP make_const_cast_exp(TYPE, EXP, int);
extern EXP make_new_cast_exp(int, TYPE, EXP, int);
extern EXP make_func_cast_exp(TYPE, LIST(EXP));
extern EXP make_base_cast(TYPE, EXP, OFFSET);

extern EXP cast_exp(TYPE, EXP, ERROR *, unsigned);
extern EXP cast_int_int(TYPE, EXP, ERROR *, unsigned, int);
extern EXP cast_int_float(TYPE, EXP, ERROR *, unsigned);
extern EXP cast_float_float(TYPE, EXP, ERROR *, unsigned);
extern EXP cast_ptr_ptr(TYPE, EXP, ERROR *, unsigned, int, int);
extern EXP cast_ptr_mem_ptr_mem(TYPE, EXP, ERROR *, unsigned, int, int);
extern EXP cast_class_class(TYPE, EXP, ERROR *, unsigned, int);
extern EXP cast_templ_type(TYPE, EXP, unsigned);
extern void cast_away_const(unsigned, ERROR *, unsigned);
extern EXP cast_token(TYPE, EXP, ERROR *, ERROR, unsigned);
extern void allow_conversion(IDENTIFIER);


/*
    CAST IDENTIFIERS

    These values are used to identify the various classes of cast expressions
    in cast_exp and related routines.  They form a bitpattern for the static,
    reinterpret and const casts.
*/

enum {
	CAST_IMPLICIT = 0x00U,
	CAST_STATIC   = 0x01U,
	CAST_REINTERP = 0x02U,
	CAST_CONST    = 0x04U,
	CAST_BAD      = 0x08U,
	CAST_EXPLICIT = 0x0fU,
	CAST_DYNAMIC  = 0x10U,
	CAST_STANDARD = 0x20U
};


#endif
