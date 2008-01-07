#ifndef __HACKED_SETJMP_INCLUDED
#define __HACKED_SETJMP_INCLUDED

#include_next <setjmp.h>

#ifdef __BUILDING_LIBS
typedef jmp_buf sigjmp_buf ;
#endif

#endif
