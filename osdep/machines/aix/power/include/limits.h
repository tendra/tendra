/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_LIMITS_INCLUDED
#define __HACKED_LIMITS_INCLUDED

#include_next <limits.h>

/* Redefine these without overflow */
#ifdef INT_MIN
#undef INT_MIN
#undef LONG_MIN
#undef SCHAR_MIN
#undef SHRT_MIN
#define INT_MIN		(-INT_MAX - 1)
#define LONG_MIN	INT_MIN
#define SCHAR_MIN	(-SCHAR_MAX - 1)
#define SHRT_MIN	(-SHRT_MAX - 1)
#endif

#endif
