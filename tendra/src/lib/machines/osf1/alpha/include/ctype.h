#ifndef __HACKED_CTYPE_INCLUDED
#define __HACKED_CTYPE_INCLUDED

#include_next <ctype.h>

#ifdef _toupper
#undef _toupper
#define _toupper( c )	toupper ( c )
#endif

#ifdef _tolower
#undef _tolower
#define _tolower( c )	tolower ( c )
#endif

#endif
