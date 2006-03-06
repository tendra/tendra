#ifndef __HACKED_TIME_INCLUDED
#define __HACKED_TIME_INCLUDED

#ifdef __cplusplus

#ifdef NULL
#undef NULL
#endif

extern "C" {
#endif

#include_next <time.h>

#ifdef __cplusplus
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

#endif

#endif
