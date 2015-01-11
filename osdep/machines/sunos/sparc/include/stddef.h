/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_STDDEF_INCLUDED
#define __HACKED_STDDEF_INCLUDED

#include_next <stddef.h>

#ifndef offsetof
#define offsetof( __S, __M )	( ( size_t ) &( ( ( __S * ) 0 )->__M ) )
#endif

#endif
