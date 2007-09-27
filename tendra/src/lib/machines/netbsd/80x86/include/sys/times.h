#ifndef __HACKED_SYS_TIMES_H
#define __HACKED_SYS_TIMES_H

/* XXX: just ignore __RENAME for now, bad things may happen */
#define __RENAME(arg1)

#include_next <sys/times.h>

#endif /* __HACKED_SYS_TIMES_H */
