#ifndef __HACKED_LIBC_FEATURES_H
#define __HACKED_LIBC_FEATURES_H

#if defined(_GLIBC2_12) || defined(_GLIBC2_14) || defined(_GLIBC2_15) \
	|| defined(_GLIBC2_17) || defined(_GLIBC2_18) || defined(_GLIBC2_19) \
	|| defined(_GLIBC2_23) || defined(_GLIBC2_27) \
	|| defined(_GLIBC2_30) || defined(_GLIBC2_31)
#pragma TenDRA begin
#pragma TenDRA directive warning allow
#endif

#include_next <features.h>

#if defined(_GLIBC2_12) || defined(_GLIBC2_14) || defined(_GLIBC2_15) \
	|| defined(_GLIBC2_17) || defined(_GLIBC2_18) || defined(_GLIBC2_19) \
	|| defined(_GLIBC2_23) || defined(_GLIBC2_27) \
	|| defined(_GLIBC2_30) || defined(_GLIBC2_31)
#pragma TenDRA end
#endif

#endif

