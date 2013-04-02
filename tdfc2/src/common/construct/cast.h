/* $Id$ */

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

#define CAST_IMPLICIT			((unsigned)0x00)
#define CAST_STATIC			((unsigned)0x01)
#define CAST_REINTERP			((unsigned)0x02)
#define CAST_CONST			((unsigned)0x04)
#define CAST_BAD			((unsigned)0x08)
#define CAST_EXPLICIT			((unsigned)0x0f)
#define CAST_DYNAMIC			((unsigned)0x10)
#define CAST_STANDARD			((unsigned)0x20)


#endif
