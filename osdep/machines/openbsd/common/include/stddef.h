/* $Id$ */

#ifndef __HACKED_LIBC_STDDEF_H
#define __HACKED_LIBC_STDDEF_H

#include_next <stddef.h>

/*
 * We're providing this primarily for offsetof(), because the system header
 * has the typical implementation which gives a non-constant expression.
 */

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)

#undef offsetof
#include <proxy/include/offsetof.h>

#endif

#endif

