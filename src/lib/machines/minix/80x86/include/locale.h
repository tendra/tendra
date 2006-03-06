#ifndef __HACKED_LOCALE_INCLUDED
#define __HACKED_LOCALE_INCLUDED

#ifdef __cplusplus

#ifdef NULL
#undef NULL
#endif

extern "C" {
#endif

#include_next <locale.h>

#ifdef __cplusplus
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

#endif

#endif
