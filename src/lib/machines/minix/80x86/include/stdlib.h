#ifndef __HACKED_STDLIB_INCLUDED
#define __HACKED_STDLIB_INCLUDED

#ifdef __cplusplus

#ifdef NULL
#undef NULL
#endif

extern "C" {
#endif

#include_next <stdlib.h>

#ifdef __cplusplus
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

#endif

#endif
