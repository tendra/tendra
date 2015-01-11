/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_TIME_INCLUDED
#define __HACKED_TIME_INCLUDED

#include_next <time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC	1000000
#endif

#ifndef CLK_TCK
#define CLK_TCK		60
#endif

#endif
