#ifndef __HACKED_STDLIB_INCLUDED
#define __HACKED_STDLIB_INCLUDED

#ifndef __BUILDING_LIBS
#include_next <stdlib.h>
#else
typedef struct { int quot ; int rem ; } div_t ;
typedef struct { long quot ; long rem ; } ldiv_t ;
#define mblen( S, N )	mbtowc( 0, ( S ), ( N ) )
#endif

#ifndef MB_CUR_MAX
extern unsigned int _mb_cur_max ;
#define MB_CUR_MAX	_mb_cur_max
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1
#endif

#ifndef RAND_MAX
#define RAND_MAX	0x7fffffff
#endif

#ifndef atexit
#define atexit( X )	on_exit ( ( X ), ( char * ) 0 )
#endif

#endif
