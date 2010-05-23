#ifndef __HACKED_CTYPE_INCLUDED
#define __HACKED_CTYPE_INCLUDED

#include_next <ctype.h>

#ifndef _toupper
#define _toupper( X )   ( ( X ) + ( 'A' - 'a' ) )
#define _tolower( X )   ( ( X ) - ( 'A' - 'a' ) )
#endif

#endif
