/* $Id$ */

#include "ansi.h"


#ifdef _OPENBSD4
#define __WRONG_BSD_EXTN_ARPA_INET_H
#define __WRONG_BSD_EXTN_NETDB_H
#define __WRONG_BSD_EXTN_NETINET_IN_H	/* TODO: i think bsd_extn.in.in_addr.s_addr in the API is wrong here */
#define __WRONG_BSD_EXTN_STRING_H	/* incompatible (const) */
#define __WRONG_BSD_EXTN_SYS_PARAM_H	/* prtial (TODO: define HZ?) */
#define __WRONG_BSD_EXTN_SYS_RESOURCE_H	/* redeclaration of caddr_t. (TODO: wrap it in a guard!) */
#define __WRONG_BSD_EXTN_SYS_SELECT_H	/* incompatible (const) */
#define __WRONG_BSD_EXTN_SYS_SOCKET_H	/* incompatible */
#define __WRONG_BSD_EXTN_SYS_UIO_H	/* incompatible */
#endif

