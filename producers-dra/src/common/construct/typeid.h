/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TYPEID_INCLUDED
#define TYPEID_INCLUDED


/*
    RUN-TIME TYPE INFORMATION

    The routines in this module are concerned with the run-time type
    information constructs, typeid and dynamic_cast.
*/

extern TYPE find_std_type(const char *, int, int);
extern EXP make_typeid_exp(int, EXP, int);
extern EXP make_typeid_type(int, TYPE, int);
extern EXP make_dynamic_cast_exp(TYPE, EXP, int);
extern void set_std_namespace(IDENTIFIER);
extern TYPE get_type_info(int, TYPE, int);


#endif
