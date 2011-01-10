/* $Id: posix.h 2289 2010-01-24 14:24:11Z kate $ */

#include "ansi.h"

#define _POSIX_SOURCE	1

#ifdef _HAIKU1
#define __WRONG_POSIX_LIMITS_H	/* inconsistent redefinition for _POSIX_LINK_MAX */
#endif

