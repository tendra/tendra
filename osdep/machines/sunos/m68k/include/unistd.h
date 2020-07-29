/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_UNISTD_INCLUDED
#define __HACKED_UNISTD_INCLUDED

#include_next <unistd.h>

#ifndef _SC_XOPEN_VERSION
#define _SC_XOPEN_VERSION 	0
#endif

#ifndef _SC_PASS_MAX
#define _SC_PASS_MAX		0
#endif

#endif
