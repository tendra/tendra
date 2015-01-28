/* $Id$ */

#ifndef __HACKED_LIBC_STDLIB_H
#define __HACKED_LIBC_STDLIB_H

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)
#pragma TenDRA begin
#pragma TenDRA directive warning allow
#endif

#include_next <stdlib.h>

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)
#pragma TenDRA end
#endif

#endif

