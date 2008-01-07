#include "ansi.h"
#define _POSIX_C_SOURCE		2

/* Only implemented from version 2.4 */
#include <limits.h>
#ifndef _POSIX2_BC_BASE_MAX
#define __WRONG_POSIX2		1
#endif
