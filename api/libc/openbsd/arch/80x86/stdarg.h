/* $Id$ */

#ifndef __HACKED_STDARG_H
#define __HACKED_STDARG_H

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5)
#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

typedef char * va_list;

#include_next <stdarg.h>

#else

#include_next <stdarg.h>

#endif
#endif

#endif

