#include "ansi.h"
#define _XOPEN_SOURCE	1
#define _XOPEN_VERSION	4
#pragma TenDRA incompatible type qualifier allow

/* Only implemented from version 2.4 */
#include <limits.h>
#ifndef _POSIX2_BC_BASE_MAX
#define __WRONG_XPG4		1
#endif
