#ifndef _HACKED_WCHAR_H
#define _HACKED_WCHAR_H

#ifndef __NO_WCHAR_H
#include_next <wchar.h>
#else
typedef int wctype_t ;
#endif

#ifndef getwchar
#include <widec.h>
#endif

#endif
