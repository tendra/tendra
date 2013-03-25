/* $Id$ */

/*
 * Copyright 2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifdef _GLIBC2_3
#define __WRONG_POSIX_SIGNAL_H /* incompatible sigaction.sa_flags */
#endif

#ifdef _GLIBC2_3
#define __WRONG_POSIX_STDIO_H    /* i don't know what to do about va_list */
#define __WRONG_POSIX_STDARG_H_VA_ARGS   /* i don't know what to do about va_list */
#endif

