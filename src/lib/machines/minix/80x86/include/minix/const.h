#ifndef __HACKED_MINIX_CONST_INCLUDED
#define __HACKED_MINIX_CONST_INCLUDED

#ifdef __cplusplus

#ifdef NULL
#undef NULL
#endif

extern "C" {
#endif

#include_next <minix/const.h>

#ifdef __cplusplus
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

#endif

#endif
