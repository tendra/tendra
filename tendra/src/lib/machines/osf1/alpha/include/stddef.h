#ifndef __HACKED_STDDEF_INCLUDED
#define __HACKED_STDDEF_INCLUDED

#include_next <stddef.h>

#undef offsetof
#define offsetof( __S, __M )	( ( size_t ) &( ( ( __S * ) 0 )->__M ) )

#endif
