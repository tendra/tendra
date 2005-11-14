/* $TenDRA$ */

#include "ansi.h"
#pragma TenDRA extra , allow
#define _XOPEN_SOURCE		1
#define _SVID_SOURCE		1
#define _BSD_SOURCE		1
#define __SVR4_I386_ABI_L1__	1
#define __semun_defined		1

#include <limits.h>
#undef _POSIX_CHILD_MAX
#undef _POSIX_NGROUPS_MAX
#undef _POSIX_OPEN_MAX
#undef _POSIX_PATH_MAX

#define __WRONG_XPG3_SEARCH_H
#define __WRONG_XPG3_SEARCH_H_SRCH_OLD
#define __WRONG_XPG3_SEARCH_H_SRCH_PROTO
#define __WRONG_XPG3_SYS_SEM_H
#define __WRONG_XPG3_SYS_SEM_H_SEM_PROTO
#define __WRONG_XPG3_SYS_SHM_H
#define __WRONG_XPG3_SYS_SHM_H_SHM_PROTO
