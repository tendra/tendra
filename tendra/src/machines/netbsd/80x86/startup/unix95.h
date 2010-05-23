/* $Id$ */

#include "ansi.h"

#define _XOPEN_SOURCE	/* empty for UNIX95 */

/*
 * TODO: some of these incompatibilities are just const/not-const arguments
 * to functions, which have compatible repsentations. We ought to be able to
 * consider these equivalent by setting some #pragma in the hacked includes
 * for those.
 *
 * TODO: things to move into subsets: unistd.swap, unistd.setpgrp
 */
#ifdef _NETBSD5
#define __WRONG_UNIX95_ARPA_INET_H	/* incompatible (const, signed) */
#define __WRONG_UNIX95_TERM_H	/* not implemented */
#define __WRONG_UNIX95_CURSES_H	/* incompatible (_Bool) */
#define __WRONG_UNIX95_CURSES_H_CHTYPE	/* incompatible (_Bool) */
#define __WRONG_UNIX95_FTW_H	/* incompatible (signed) */
#define __WRONG_UNIX95_NETDB_H	/* incompatible (const) */
#define __WRONG_UNIX95_NETINET_IN_H	/* incompatible (const) */
#define __WRONG_UNIX95_POLL_H	/* incompatible (long) */
#define __WRONG_UNIX95_SIGNAL_H	/* incompatible (const) */
#define __WRONG_UNIX95_SYS_RESOURCE_H	/* incompatible (long long) */
#define __WRONG_UNIX95_SYS_SOCKET_H	/* incompatible (const) */
#define __WRONG_UNIX95_SYS_STAT_H_ST_PROTO	/* incompatible (signed) */
#define __WRONG_UNIX95_SYS_STAT_H	/* incompatible (signed) */
#define __WRONG_UNIX95_SYS_STATVFS_H	/* incompatible (signed) */
#define __WRONG_UNIX95_SYS_TIME_H	/* incompatible (long) */
#define __WRONG_UNIX95_SYS_WAIT_H	/* not implemented */
#define __WRONG_UNIX95_TERMIOS_H	/* not implemented */
#define __WRONG_UNIX95_UCONTEXT_H	/* TODO: should be possible */
#define __WRONG_UNIX95_UCONTEXT_H_SIG	/* TODO: should be possible */
#define __WRONG_UNIX95_CURSES_H	/* incompatible (_Bool) */
#define __WRONG_UNIX95_UNCTRL_H	/* incompatible (_Bool) */
#define __WRONG_UNIX95_UNISTD_H	/* incompatible (signed) */
#define __WRONG_UNIX95_UTMPX_H	/* incompatible (signed) */

#define __WRONG_UNIX95
#endif

