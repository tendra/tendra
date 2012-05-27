/* $Id$ */

#ifndef __HACKED_FEATURES_H
#define __HACKED_FEATURES_H

#ifdef _GLIBC2_14
#pragma TenDRA begin
#pragma TenDRA unknown directive allow /* for #warning */
#endif

#include_next <features.h>

#ifdef _GLIBC2_14
#pragma TenDRA end
#endif

#endif

