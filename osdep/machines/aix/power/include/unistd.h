/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_UNISTD_INCLUDED
#define __HACKED_UNISTD_INCLUDED

#include_next <unistd.h>

#ifdef _POSIX_JOB_CONTROL
#undef _POSIX_JOB_CONTROL
#define _POSIX_JOB_CONTROL	1
#endif

#ifdef _POSIX_SAVED_IDS
#undef _POSIX_SAVED_IDS
#define _POSIX_SAVED_IDS	1
#endif

#endif
