#ifndef __HACKED_UNISTD_INCLUDED
#define __HACKED_UNISTD_INCLUDED

#include_next <unistd.h>

#ifdef _POSIX_JOB_CONTROL
#undef _POSIX_JOB_CONTROL
#define _POSIX_JOB_CONTROL	1
#endif

#define _POSIX_SAVED_IDS	0

#ifndef _SC_XOPEN_VERSION
#define _SC_XOPEN_VERSION	0
#endif

#ifndef _SC_PASS_MAX
#define _SC_PASS_MAX		0
#endif

#endif
