#ifndef __HACKED_LIBC_BITS_SIGNUM_H
#define __HACKED_LIBC_BITS_SIGNUM_H

/* for SIG_IGN and SIG_ERR */
#if defined(_GLIBC2_3) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_12) || defined(_GLIBC2_18) || defined(_GLIBC2_19)
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-int) off
#endif

#include_next <bits/signum.h>

#if defined(_GLIBC2_3) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_12) || defined(_GLIBC2_18) || defined(_GLIBC2_19)
#pragma TenDRA end
#endif

#endif

