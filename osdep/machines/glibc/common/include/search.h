#ifndef __HACKED_LIBC_SEARCH_H
#define __HACKED_LIBC_SEARCH_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_XPG3_SEARCH_H
#pragma TenDRA incompatible type qualifier allow /* for twalk */
#endif
#endif

#include_next <search.h>

#endif

