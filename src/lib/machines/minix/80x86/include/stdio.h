#ifndef __HACKED_STDIO_INCLUDED
#define __HACKED_STDIO_INCLUDED

#ifdef __cplusplus

#ifdef NULL
#undef NULL
#endif

extern "C" {
#endif

#include_next <stdio.h>

#ifdef __cplusplus
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

#endif

#endif
