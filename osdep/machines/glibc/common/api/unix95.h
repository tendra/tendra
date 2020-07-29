/*
 * Copyright 2011-2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifdef _GLIBC2_14
#define __WRONG_UNIX95_NETINET_IN_H /* incompatible msghdr.msg_iovlen */
#define __WRONG_UNIX95_ARPA_INET_H /* incompatible msghdr.msg_iovlen */
#define __WRONG_UNIX95_SYS_TIME_H /* TODO: FD_ZERO conflicts with #pragma token syntax somehow */
#define __WRONG_UNIX95_STDLIB_H /* incompatible initstate */
#define __WRONG_UNIX95_SYS_SOCKET_H /* incompatible msghdr.msg_iovlen */
#define __WRONG_UNIX95_SIGNAL_H /* missing sa_sigaction (possible to work around) */
#define __WRONG_UNIX95_LIMITS_H /* missing ATEXIT_MAX (glibc provides no fixed value) */
#define __WRONG_UNIX95_UCONTEXT_H /* incompatible makecontext */
#endif

