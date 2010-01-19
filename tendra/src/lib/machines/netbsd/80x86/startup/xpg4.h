/* $Id$ */

#include "ansi.h"

#define _XOPEN_SOURCE	4

#ifdef _NETBSD5
#define __WRONG_XPG4_SYS_SHM_H	/* TODO: should be possible */
#define __WRONG_XPG4_UNISTD_H	/* TODO: should be possible */
#define __WRONG_XPG4_WCHAR_H	/* incompatible (arg count) */
#endif

