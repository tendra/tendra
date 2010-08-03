/* $Id$ */

#include "ansi.h"

#define _POSIX_C_SOURCE 199506L


#ifdef _OPENBSD4
#ifndef _POSIX2_C_VERSION
#define _POSIX2_C_VERSION 199209L	/* missing */
#endif
#endif

#ifdef _OPENBSD4
#define __WRONG_POSIX2_GLOB_H	/* incompatible glob_t.gl_pathc */
#define __WRONG_POSIX2_REGEX_H	/* missing REG_ENOSYS; TODO: move to subset */
#endif

