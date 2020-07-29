/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _HACKED_WCHAR_H
#define _HACKED_WCHAR_H

#ifndef __NO_WCHAR_H
#include_next <wchar.h>
#else
typedef int wctype_t ;
#endif

#ifndef getwchar
#include <widec.h>
#endif

#endif
