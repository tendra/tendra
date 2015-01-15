/* $Id$ */

#ifndef __HACKED_LIBC_BITS_SIGNUM_H
#define __HACKED_LIBC_BITS_SIGNUM_H

#if defined(_EGLIBC2_11)
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-int) off
#endif

/* for SIG_IGN and SIG_ERR */
#if defined(_EGLIBC2_15) || defined(_EGLIBC2_19)
#pragma TenDRA begin
#pragma TenDRA conversion analysis ( int-pointer explicit ) off
#endif

#include_next <bits/signum.h>

#if defined(_EGLIBC2_11) || defined(_EGLIBC2_15) || defined(_EGLIBC2_19)
#pragma TenDRA end
#endif

#endif

