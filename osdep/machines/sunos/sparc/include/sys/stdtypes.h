/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_SYS_STDTYPES_INCLUDED
#define __HACKED_SYS_STDTYPES_INCLUDED

#define size_t __size_t_wrong

#include_next <sys/stdtypes.h>

#undef size_t
typedef unsigned size_t ;

#endif
