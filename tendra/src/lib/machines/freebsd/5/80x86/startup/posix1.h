/*
 * $TenDRA: tendra/src/lib/machines/freebsd/5/80x86/startup/posix1.h,v 1.2 2004/01/24 13:36:15 stefanf Exp $
 */

#include "ansi.h"
#define _POSIX_SOURCE	1
#define __WRONG_POSIX1_LOCALE_H
#include <limits.h>
#undef _POSIX_CHILD_MAX
#undef _POSIX_NGROUPS_MAX
#undef _POSIX_OPEN_MAX
#undef _POSIX_PATH_MAX
