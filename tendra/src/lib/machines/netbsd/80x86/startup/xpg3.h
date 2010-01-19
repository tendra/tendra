/* $Id$ */

#include "ansi.h"

#define _XOPEN_SOURCE	3

#ifdef _NETBSD5
#define __WRONG_XPG3_SEARCH_H	/* incompatible (const) */
#define __WRONG_XPG3_SYS_SHM_H	/* TODO: should be possible */
#define __WRONG_XPG3_SYS_SHM_H_SHM_PROTO	/* incompatible (signed) */
#define __WRONG_XPG3_TERMIOS_H	/* not implemented */
#endif

