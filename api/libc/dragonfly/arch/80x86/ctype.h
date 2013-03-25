/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_CTYPE_INCLUDED
#define __HACKED_CTYPE_INCLUDED

#include_next <ctype.h>

#ifndef _toupper
#define _toupper(c)	__toupper(c)
#endif

#ifndef _tolower
#define _tolower(c)	__tolower(c)
#endif

#endif
