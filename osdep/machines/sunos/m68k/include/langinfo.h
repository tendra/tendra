/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_LANGINFO_INCLUDED
#define __HACKED_LANGINFO_INCLUDED

#include_next <langinfo.h>

#ifndef AM_STR
#define AM_STR 0
#endif

#ifndef PM_STR
#define PM_STR 0
#endif

#ifndef T_FMT
#define T_FMT 0
#endif

#ifndef D_FMT
#define D_FMT 0
#endif

#endif
