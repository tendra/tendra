/* $Id$ */

#ifndef __HACKED_LIBC_ASM_GENERIC_INT_LL64_H
#define __HACKED_LIBC_ASM_GENERIC_INT_LL64_H

/* included by <signal.h> */

#if defined(_GLIBC2_11) || defined(_GLIBC2_14) || defined(_GLIBC2_15)
#define __signed__ signed
#endif

#include_next <asm-generic/int-ll64.h>

#endif

