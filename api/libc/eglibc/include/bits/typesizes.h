/* $Id$ */

#ifndef __HACKED_LIBC_BITS_TYPESIZES_H
#define __HACKED_LIBC_BITS_TYPESIZES_H

/* included for dev_t for posix */

#include_next <bits/typesizes.h>

/*
 * dev_t is implemented as __u_quad_t, which is a struct containing an
 * array of two unsigned long elements. However, POSIX.1 defines it as
 * an arithmetic type. Here we replace it with unsigned long long, which
 * has compatible representation assuming no trailing padding.
 *
 * TODO: I haven't checked that our tspec specification of dev_t is correct.
 */
#if defined(_EGLIBC2_11)
#undef __DEV_T_TYPE
#define __DEV_T_TYPE unsigned long long
#endif

#endif

