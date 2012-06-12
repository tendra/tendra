/* $Id$ */

#ifndef __HACKED_STDARG_H
#define __HACKED_STDARG_H

#ifdef _OPENBSD5_1
#ifndef __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS

typedef char * va_list;

#include_next <stdarg.h>

#else

#include_next <stdarg.h>

#endif
#endif

#endif

