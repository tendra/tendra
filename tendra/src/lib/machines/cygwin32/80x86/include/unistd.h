#ifndef __HACKED_UNISTD_INCLUDED
#define __HACKED_UNISTD_INCLUDED

#include_next <unistd.h>

#ifndef _POSIX_JOB_CONTROL
#define _POSIX_JOB_CONTROL	1
#endif

#ifndef _POSIX_SAVED_IDS
#define _POSIX_SAVED_IDS	1
#endif

#ifndef _SC_PASS_MAX
#define _SC_PASS_MAX		0
#endif

#ifndef _SC_STREAM_MAX
#define _SC_STREAM_MAX		0
#endif

#ifndef _SC_TZNAME_MAX
#define _SC_TZNAME_MAX		0
#endif

#ifndef _SC_XOPEN_VERSION
#define _SC_XOPEN_VERSION	0
#endif

#endif
