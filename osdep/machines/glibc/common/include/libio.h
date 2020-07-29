#ifndef __HACKED_LIBC_LIBIO_H
#define __HACKED_LIBC_LIBIO_H

#if defined(_GLIBC2_3) || defined(_GLIBC2_5) || defined(_GLIBC2_7) \
	|| defined(_GLIBC2_11) || defined(_GLIBC2_12)
#include <err.h>	/* for __gnuc_va_list */
#endif

#include_next <libio.h>

#endif

