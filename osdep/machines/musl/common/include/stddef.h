/* $Id$ */

#ifndef __HACKED_LIBC_STDDEF_H
#define __HACKED_LIBC_STDDEF_H

#include_next <stddef.h>

/*
 * We're providing this primarily for offsetof(), because the system header
 * has the typical implementation which gives a non-constant expression.
 */

#if defined(_MUSL1_1_5)

#undef offsetof
#include <proxy/include/offsetof.h>

#endif

#endif

