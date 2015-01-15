/* $Id$ */

#ifndef __HACKED_FLOAT_H
#define __HACKED_FLOAT_H

/*
 * eglibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_EGLIBC2_19)

#define FLT_RADIX       2 /* b */
#define FLT_ROUNDS      -1

#define FLT_DIG         6               /* floor((p-1) * log10(b)) + (b == 10) */
#define FLT_EPSILON     1.19209290E-07F /* b**(1 - p) */
#define FLT_MANT_DIG    24              /* p */
#define FLT_MAX         3.40282347E+38F /* (1 - b**(-p)) * b**emax */
#define FLT_MAX_10_EXP  38              /* floor(log10((1 - b**(-p)) * b**emax)) */
#define FLT_MAX_EXP     128             /* emax */
#define FLT_MIN         1.17549435E-38F /* b**(emin - 1) */
#define FLT_MIN_10_EXP  (-37)           /* ceil(log10(b**(emin - 1))) */
#define FLT_MIN_EXP     (-125)          /* emin */

#define DBL_DIG         15
#define DBL_EPSILON     2.2204460492503131E-16
#define DBL_MANT_DIG    53
#define DBL_MAX         1.7976931348623157E+308
#define DBL_MAX_10_EXP  308
#define DBL_MAX_EXP     1024
#define DBL_MIN         2.2250738585072014E-308
#define DBL_MIN_10_EXP  (-307)
#define DBL_MIN_EXP     (-1021)
 
#define LDBL_DIG        18
#define LDBL_EPSILON    1.08420217248550443401e-19L
#define LDBL_MANT_DIG   64
#define LDBL_MAX        1.18973149535723176502e+4932L
#define LDBL_MAX_10_EXP 4932
#define LDBL_MAX_EXP    16384
#define LDBL_MIN        3.36210314311209350626e-4932L
#define LDBL_MIN_10_EXP (-4931)
#define LDBL_MIN_EXP    (-16381)

#endif

#endif

