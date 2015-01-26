/* $Id$ */

#ifndef __HACKED_FLOAT_H
#define __HACKED_FLOAT_H

/*
 * eglibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_EGLIBC2_11) || defined(_EGLIBC2_15) || defined(_EGLIBC2_19)

#include <proxy/include/float.h>

#endif

#endif

