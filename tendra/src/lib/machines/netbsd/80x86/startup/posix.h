/* $Id$ */

#include "ansi.h"

#define _POSIX_SOURCE	1

/*
 * TODO: This is really just for _POSIX_SAVED_IDS being not available. Rather
 * than eliding the entire "u_proto" subset, we ought to change the tspec API
 * definition to have just _POSIX_SAVED_IDS in its own subset, which we can
 * mark __WRONG with more granularity.
 */
#ifdef _NETBSD5
#define __WRONG_POSIX_UNISTD_H_U_PROTO
#endif

