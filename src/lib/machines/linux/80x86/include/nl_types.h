#ifndef __HACKED_LINUX_NL_TYPES_INCLUDED
#define __HACKED_LINUX_NL_TYPES_INCLUDED

#ifdef __BUILDING_LIBS
#define catclose	__catclose_wrong
#endif

#include_next <nl_types.h>
#if NL_SETD
#include_next <langinfo.h>
#else
#define __TDF_XPG3_LANGINFO_H
#endif

#ifdef __BUILDING_LIBS
#undef catclose
#endif

#endif
