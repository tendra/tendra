#ifndef __HACKED_LIBC_ASM_SIGCONTEXT_H
#define __HACKED_LIBC_ASM_SIGCONTEXT_H

#if defined(_GLIBC2_11) || defined(_GLIBC2_14) || defined(_GLIBC2_15)
#pragma TenDRA begin
#pragma TenDRA anonymous union allow
#endif

#include_next <asm/sigcontext.h>

#if defined(_GLIBC2_11) || defined(_GLIBC2_14) || defined(_GLIBC2_15)
#pragma TenDRA end
#endif

#endif

