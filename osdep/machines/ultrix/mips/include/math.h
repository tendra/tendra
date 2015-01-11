/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_MATH_INCLUDED
#define __HACKED_MATH_INCLUDED

#include_next <math.h>

/* The system definition of HUGE_VAL depends on a compiler 'feature' */
#ifdef HUGE_VAL
#undef HUGE_VAL
const static union {
    unsigned long ul [2] ;
    double dbl ;
} __huge_val = { 0x0, 0x7ff00000 } ;
#define HUGE_VAL ( __huge_val.dbl )
#endif

#endif
