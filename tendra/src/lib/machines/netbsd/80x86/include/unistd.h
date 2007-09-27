#ifndef __HACKED_UNISTD_H
#define __HACKED_UNISTD_H

/* XXX: just ignore __RENAME for now, bad things may happen */
#define __RENAME(arg1)

#include_next <unistd.h>

/* XXX:
 * Lie to tspec, NetBSD does not define this on purpose,
 * see /usr/include/sys/unistd.h
 */
#ifndef _POSIX_SAVED_IDS
#define _POSIX_SAVED_IDS 0
#endif

/*XXX:
 * Missing.
 * This is marked as legacy in The Single UNIX ® Specification, Version 2
 * and subsequently removed.
 */
#ifndef _SC_PASS_MAX
#define _SC_PASS_MAX 0
#endif

#ifndef _SC_XOPEN_VERSION
#define _SC_XOPEN_VERSION 0
#endif

#endif /* __HACKED_UNISTD_H */
