/* $Id$ */

#include "ansi.h"

#ifdef _NETBSD5
#define __WRONG_BSD_EXTN_ARPA_INET_H	/* incompatible (long) */
#define __WRONG_BSD_EXTN_NETDB_H	/* incompatible (signed) */
#define __WRONG_BSD_EXTN_NETINET_IN_H	/* incompatible (long) */
#define __WRONG_BSD_EXTN_SYS_PARAM_H	/* partial */
#define __WRONG_BSD_EXTN_SYS_SELECT_H	/* TODO: should be possible */
#define __WRONG_BSD_EXTN_SYS_SOCKET_H	/* incompatible (signed) */
#define __WRONG_BSD_EXTN_SYS_UIO_H	/* incompatible (char/void) */
#endif

