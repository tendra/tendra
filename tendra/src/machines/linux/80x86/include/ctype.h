#ifndef __HACKED_LINUX_CTYPE_INCLUDED
#define __HACKED_LINUX_CTYPE_INCLUDED

#include_next <ctype.h>

/* These are meant to be defined as macros */

#ifndef _toupper
#define _toupper( c )		__toupper ( c )
#endif

#ifndef _tolower
#define _tolower( c )		__tolower ( c )
#endif


#endif
