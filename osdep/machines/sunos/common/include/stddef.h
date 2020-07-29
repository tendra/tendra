/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_STDDEF_INCLUDED
#define __HACKED_STDDEF_INCLUDED

#include_next <stddef.h>

#undef offsetof
#include <proxy/include/offsetof.h>

#endif
