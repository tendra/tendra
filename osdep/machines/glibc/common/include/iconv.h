/* $Id$ */

#ifndef __HACKED_LIBC_ICONV_H
#define __HACKED_LIBC_ICONV_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_XPG4_ICONV_H
#pragma TenDRA incompatible type qualifier allow /* for iconv */
#endif
#endif

#include_next <iconv.h>

#endif

