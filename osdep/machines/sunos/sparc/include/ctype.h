/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_CTYPE_INCLUDED
#define __HACKED_CTYPE_INCLUDED

#include_next <ctype.h>

#ifndef _toupper
#define _toupper( X )   ( ( X ) + ( 'A' - 'a' ) )
#define _tolower( X )   ( ( X ) - ( 'A' - 'a' ) )
#endif

#endif
