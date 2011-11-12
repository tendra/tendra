/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_STRING_INCLUDED
#define __HACKED_STRING_INCLUDED

#include_next <string.h>

#ifndef strerror
extern char *sys_errlist [] ;
#define strerror( N )   sys_errlist [ ( N ) ]
#endif

#endif
