/* $Id$ */

#ifndef __HACKED_LIBC_XLOCALE__CTYPE_H
#define __HACKED_LIBC_XLOCALE__CTYPE_H

#ifdef _FREEBSD9_1
#define __NO_TLS
#include <runetype.h> /* for _RuneLocale */
#endif

#include_next <_ctype.h>

#ifdef _FREEBSD9_1
#undef __NO_TLS
#endif

#endif

