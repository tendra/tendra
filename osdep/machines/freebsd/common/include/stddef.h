/* $Id$ */

#ifndef __HACKED_LIBC_STDDEF_H
#define __HACKED_LIBC_STDDEF_H

#include_next <stddef.h>

/*
 * We're providing this primarily for offsetof(), because the system header
 * has the typical implementation which gives a non-constant expression.
 */

#if defined(_FREEBSD9_2) \
	|| defined(_FREEBSD10_1) || defined(_FREEBSD10_2)

#undef offsetof
#include <proxy/include/offsetof.h>

#endif

#endif

