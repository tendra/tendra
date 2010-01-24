/* $Id$ */

#ifndef __HACKED_ERRNO_H
#define __HACKED_ERRNO_H

#ifdef _OPENBSD4
#ifdef __BUILDING_TDF_XPG3_ERRNO_H_ENUMS
#ifndef _BSD_SOURCE
#define _BSD_SOURCE	/* for ENOTBLK */
#endif
#endif
#endif

#include_next <errno.h>

#endif

