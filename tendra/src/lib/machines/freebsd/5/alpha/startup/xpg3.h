/*
 * $TenDRA$
 */

#include "ansi.h"
#pragma TenDRA incompatible type qualifier allow
#define _XOPEN_SOURCE			1
#define __semun_defined			1
#define __WRONG_XPG3_TERMIOS_H
#define __WRONG_XPG3_SYS_SEM_H

#include <limits.h>
#undef _POSIX_CHILD_MAX
#undef _POSIX_NGROUPS_MAX
#undef _POSIX_OPEN_MAX
#undef _POSIX_PATH_MAX
