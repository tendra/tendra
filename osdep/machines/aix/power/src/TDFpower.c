/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

/* from float.h */
#define FP_RND_RZ		0
#define FP_RND_RN		1
#define FP_RND_RP		2
#define FP_RND_RM		3

typedef unsigned short fprnd_t;
extern fprnd_t fp_read_rnd(void);
extern fprnd_t fp_swap_rnd(fprnd_t);

/* from math.h */
extern unsigned uitrunc(double);
extern int itrunc(double);
extern double rint(double);

/* from limits.h */
#define INT_MAX			(2147483647)
#define INT_MIN			(- (INT_MAX + 1))

extern int __TDFrnd_error;
extern unsigned int __TDFrnd_unsgned(double, fprnd_t);
extern int __TDFrnd_sgned(double, fprnd_t);
extern void __TDFerr_rnd_unsgned(double, fprnd_t);
extern void __TDFerr_rnd_sgned(double, fprnd_t);

int __TDFrnd_error = 0;

unsigned int
__TDFrnd_unsgned(double f, fprnd_t rnd_mode)
{
    fprnd_t swap;
    unsigned int ret_value;
    swap = fp_swap_rnd(rnd_mode);
    ret_value = uitrunc(rint(f));
    IGNORE fp_swap_rnd(swap);
    return ret_value;
}

int
__TDFrnd_sgned(double f, fprnd_t rnd_mode)
{
    fprnd_t swap;
    int ret_value;
    swap = fp_swap_rnd(rnd_mode);
    ret_value = itrunc(rint(f));
    IGNORE fp_swap_rnd(swap);
    return ret_value;
}

void
__TDFerr_rnd_unsgned(double f, fprnd_t rnd_mode)
{
    double fmin = 0.0;
    double fmax = 4294967295.0;
    switch(rnd_mode) {
	case FP_RND_RN: {
	    fmin += -0.5;
	    fmax += 0.5;
	    if (f < fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RZ: {
	    fmin += -1.0;
	    fmax += 1.0;
	    if (f <= fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RP: {
	    fmin += -1.0;
	    if (f <= fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RM: {
	    fmax += 1.0;
	    if (f < fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
    }
    return;
}

void
__TDFerr_rnd_sgned(double f, fprnd_t rnd_mode)
{
    double fmin = -2147483648.0;
    double fmax = 2147483647.0;

    switch(rnd_mode) {
	case FP_RND_RN: {
	    fmin += -0.5;
	    fmax += 0.5;
	    if (f < fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		 __TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RZ: {
	    fmin += -1.0;
	    fmax += 1.0;
	    if (f <= fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RP: {
	    fmin += -1.0;
	    if (f <= fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RM: {
	    fmax += 1.0;
	    if (f < fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
    }
    return;
}
