#ifndef __HACKED_LIBC_SYS_SYSLIMITS_H
#define __HACKED_LIBC_SYS_SYSLIMITS_H

#if defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) \
	|| defined(_FREEBSD10_1) || defined(_FREEBSD10_2) || defined(_FREEBSD10_3) \
	|| defined(_FREEBSD10_4) \
	|| defined(_FREEBSD11_1)
#pragma TenDRA begin
#pragma TenDRA directive warning allow
#endif

#include_next <sys/syslimits.h>

#if defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(FREEBSD9_2) \
	|| defined(_FREEBSD10_1) || defined(_FREEBSD10_2) || defined(_FREEBSD10_3) \
	|| defined(_FREEBSD10_4) \
	|| defined(_FREEBSD11_1)
#pragma TenDRA end
#endif

#endif

