#ifndef __HACKED_LIBC_SYS_CDEFS_H
#define __HACKED_LIBC_SYS_CDEFS_H

#if defined(_FREEBSD11_0)
#pragma TenDRA begin
#pragma TenDRA option "va_macro" allow /* for __locks_exclusive(...) */
#endif

#include_next <sys/cdefs.h>

#if defined(_FREEBSD11_0)
#pragma TenDRA end
#endif

#endif

