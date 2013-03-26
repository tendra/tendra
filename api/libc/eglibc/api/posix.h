/* $Id$ */

/*
 * Copyright 2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifdef _EGLIBC2_11
#define __WRONG_POSIX_SIGNAL_H /* incompatible sigaction.sa_flags */
#endif

#ifdef _EGLIBC2_11
#define __WRONG_POSIX_STDIO_H    /* i don't know what to do about va_list */
#define __WRONG_POSIX_STDARG_H_VA_ARGS   /* i don't know what to do about va_list */
#endif

#ifdef _EGLIBC2_15
#define __WRONG_POSIX_SYS_STAT_H	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_TYPES_H_STAT_T	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_WAIT_H	/* incompatible dev_t */
#define __WRONG_POSIX_SIGNAL_H	/* incompatible dev_t */
#define __WRONG_POSIX_PWD_H	/* incompatible dev_t */
#define __WRONG_POSIX_FCNTL_H	/* incompatible dev_t */
#define __WRONG_POSIX_GRP_H	/* incompatible dev_t */
#define __WRONG_POSIX_UTIME_H	/* incompatible dev_t */
#define __WRONG_POSIX_UNISTD_H_TCPGRP	/* incompatible dev_t */
#define __WRONG_POSIX_UNISTD_H_U_PROTO	/* incompatible dev_t */
#endif

