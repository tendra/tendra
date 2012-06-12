/* $Id$ */

#ifndef __HACKED_BITS_RESOURCE_H
#define __HACKED_BITS_RESOURCE_H

#if defined(_GLIBC2_5)
#ifdef __BUILDING_TDF_POSIX_SYS_WAIT_H
#pragma TenDRA begin
#pragma TenDRA extra , allow
#endif
#endif

#include_next <bits/resource.h>

#if defined(_GLIBC2_5)
#ifdef __BUILDING_TDF_POSIX_SYS_WAIT_H
#pragma TenDRA end
#endif
#endif

#endif

