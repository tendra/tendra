#ifndef __HACKED_FLOAT_H
#define __HACKED_FLOAT_H

/*
 * glibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_GLIBC2_5) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_12) || defined(_GLIBC2_14) || defined(_GLIBC2_15) \
	|| defined(_GLIBC2_17) || defined(_GLIBC2_18) || defined(_GLIBC2_19) \
	|| defined(_GLIBC2_27) || defined(_GLIBC2_31)

#include <proxy/include/float.h>

#endif

#endif

