/* $Id$ */

#ifndef __HACKED_MACHINE__TYPES_H
#define __HACKED_MACHINE__TYPES_H

#if defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2)
#define __extension__
#endif

#include_next <machine/_types.h>

#if defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2)
#undef __extension__
#endif

#endif

