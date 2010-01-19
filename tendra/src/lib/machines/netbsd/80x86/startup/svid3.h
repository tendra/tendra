/* $Id$ */

#include "ansi.h"

#ifdef _NETBSD5
#define __WRONG_SVID3_CURSES_H	/* incompatible (_Bool) */
#define __WRONG_SVID3_ERRNO_H	/* partial */
#define __WRONG_SVID3_ETI_H	/* not implemented*/
#define __WRONG_SVID3_FORM_H	/* incompatible (_Bool) */
#define __WRONG_SVID3_MALLOC_H	/* not implemented */
#define __WRONG_SVID3_MATH_H	/* partial */
#define __WRONG_SVID3_MENU_H	/* incompatible (_Bool) */
#define __WRONG_SVID3_NETCONFIG_H	/* incompatible (const) */
#define __WRONG_SVID3_POLL_H	/* incompatible (long) */
#define __WRONG_SVID3_RPC_RPC_H	/* not implemented */
#define __WRONG_SVID3_RPC_XDR_H	/* incompatible (signed) */
#define __WRONG_SVID3_SIGNAL_H	/* partial */
#define __WRONG_SVID3_SYS_ACCT_H	/* incompatible (signed) */
#define __WRONG_SVID3_SYS_LOCK_H	/* asm */
#define __WRONG_SVID3_SYS_MMAN_H	/* incompatible (void/char) */
#define __WRONG_SVID3_SYS_MOUNT_H	/* partial */
#define __WRONG_SVID3_SYS_SHM_H	/* incompatible (signed) */
#define __WRONG_SVID3_SYS_STAT_H	/* incompatible (long) */
#define __WRONG_SVID3_SYS_STATVFS_H	/* incompatible (long) */
#define __WRONG_SVID3_SYS_SWAP_H	/* partial */
#define __WRONG_SVID3_SYS_TIME_H	/* partial */
#define __WRONG_SVID3_SYS_TYPES_H	/* partial */
#define __WRONG_SVID3_SYS_UIO_H	/* incompatible (void/char) */
#define __WRONG_SVID3_TERMIOS_H	/* not implemented */
#define __WRONG_SVID3_UCONTEXT_H	/* TODO: should be possible */
#define __WRONG_SVID3_UNISTD_H	/* partial */

#define __WRONG_SVID3
#endif

