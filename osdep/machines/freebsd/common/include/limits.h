#ifndef __HACKED_LIBC_LIMITS_H
#define __HACKED_LIBC_LIMITS_H

#if defined(_FREEBSD8_3) || defined(_FREEBSD11_0)
#pragma TenDRA begin
#pragma TenDRA directive warning allow
#endif

#include_next <limits.h>

#if defined(_FREEBSD8_3) || defined(_FREEBSD11_0)
#pragma TenDRA end
#endif

#endif

