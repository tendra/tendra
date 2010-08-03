/* $Id$ */

#include "ansi.h"

#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED


#ifdef _OPENBSD4
#define __WRONG_UNIX95_ARPA_INET_H	/* incompatible type for .sin_zero */
#define __WRONG_UNIX95_CURSES_H	/* incompatible */
#define __WRONG_UNIX95_CURSES_H_CHTYPE	/* incompatible */
#define __WRONG_UNIX95_ERRNO_H	/* partial */
#define __WRONG_UNIX95_SYS_STAT_H_ST_PROTO	/* incompatible (signed) */
#define __WRONG_UNIX95_FTW_H	/* incompatible (st_proto) */
#define __WRONG_UNIX95_LIBGEN_H	/* incompatible (const) */

#define __WRONG_UNIX95
#endif

