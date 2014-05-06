/* $Id$ */

#ifndef __HACKED_LIBC_SYS_SOCKET_H
#define __HACKED_LIBC_SYS_SOCKET_H

/* for off_t et al */
#if defined(_OPENBSD5_1)
#if defined(__BUILDING_TDF_XNS5_AR_SYS_SOCKET_H_SA_FAMILY_T)
#include <sys/types.h>
#endif
#endif

#include_next <sys/socket.h>

#endif

